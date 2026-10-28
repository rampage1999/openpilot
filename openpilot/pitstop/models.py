import asyncio
import json
import logging
import os

from aiohttp import web

from openpilot.sunnypilot.models.fetcher import ModelFetcher
from openpilot.sunnypilot.models.helpers import ACTIVE_BUNDLE_KEYS, get_active_bundle
from openpilot.sunnypilot.models.model_name import DEFAULT_MODEL
from openpilot.common.params import Params
from openpilot.common.hardware.usb import CHESTNUT_STATE_LABELS, CHESTNUT_USABLE_STATES, get_chestnut_hardware_state, get_usb_state
from openpilot.selfdrive.modeld.helpers import chestnut_model_available
from openpilot.system.hardware.hw import Paths

logger = logging.getLogger("pitstop")


class ModelMixin:

  def _require_offroad(self):
    if not self.params.get_bool("IsOffroad"):
      raise web.HTTPConflict(text="Model changes are only allowed while the car is offroad")

  def _chestnut_present(self) -> bool:
    # Same signal ModelManagerSP uses. helpers.chestnut_present() also requires the
    # firmware product string, so pitstop would disagree while firmware is mismatched.
    ds = self._device_state
    return bool(ds.chestnutPresent) if ds is not None else False

  def _active_source_bundles(self):
    fetcher = ModelFetcher(self.params)
    source = ModelFetcher.active_source(self._chestnut_present())
    return fetcher.get_bundles_for_source(source), source

  async def _active_source_bundles_async(self):
    loop = asyncio.get_running_loop()
    return await loop.run_in_executor(None, self._active_source_bundles)

  def _chestnut_hw(self):
    try:
      usb_state = get_usb_state()
    except Exception:
      usb_state = []
    return get_chestnut_hardware_state(usb_state, getattr(self, "_chestnut_state", None),
                                        chestnut_model_available(self.params), self.params.get_bool("ChestnutActive"))

  @staticmethod
  def _model_file_cached(model_dir, fname):
    return (os.path.isfile(os.path.join(model_dir, fname)) or
            os.path.isfile(os.path.join(model_dir, fname + '.chunkmanifest')))

  @staticmethod
  def _bundle_files(bundle) -> set:
    files = set()
    for m in getattr(bundle, 'models', []):
      if getattr(getattr(m, 'artifact', None), 'fileName', None):
        files.add(m.artifact.fileName)
      if getattr(getattr(m, 'metadata', None), 'fileName', None):
        files.add(m.metadata.fileName)
    return files

  async def handle_models_list(self, request):
    try:
      bundles, source = await self._active_source_bundles_async()
      hw = self._chestnut_hw() if source == "chestnut" else None
      unavailable_reason = None
      if hw is not None and hw.state not in CHESTNUT_USABLE_STATES:
        unavailable_reason = CHESTNUT_STATE_LABELS[hw.state]
      model_dir = Paths.model_root()
      result = []
      for b in bundles:
        d = b.to_dict()
        files = self._bundle_files(b)
        d['isCached'] = bool(files) and all(
          self._model_file_cached(model_dir, f) for f in files
        )
        d['cachedFiles'] = [f for f in files if self._model_file_cached(model_dir, f)]
        if unavailable_reason is not None:
          d['unavailableReason'] = unavailable_reason
        result.append(d)
      return web.json_response(result)
    except Exception as e:
      logger.exception("Failed to list models")
      return web.json_response({"error": str(e)}, status=500)

  async def handle_models_delete(self, request):
    self._require_offroad()
    name = request.match_info.get("name", "")
    if not name:
      raise web.HTTPBadRequest(text="Missing bundle name")
    try:
      fetcher = ModelFetcher(self.params)
      bundles = fetcher.get_available_bundles()
    except Exception as e:
      raise web.HTTPInternalServerError(text=str(e)) from e
    bundle = next((b for b in bundles if b.internalName == name), None)
    if bundle is None:
      raise web.HTTPNotFound(text=f"Bundle '{name}' not found")
    model_dir = Paths.model_root()
    files = self._bundle_files(bundle)
    deleted = []
    for fname in files:
      base = os.path.join(model_dir, fname)
      if os.path.isfile(base):
        os.remove(base)
        deleted.append(fname)
      manifest = base + '.chunkmanifest'
      if os.path.isfile(manifest):
        try:
          num_chunks = int(open(manifest).read().strip())
        except Exception:
          num_chunks = 0
        os.remove(manifest)
        deleted.append(fname + '.chunkmanifest')
        for i in range(num_chunks):
          chunk = f"{base}.chunk{i+1:02d}of{num_chunks:02d}"
          if os.path.isfile(chunk):
            try:
              os.remove(chunk)
              deleted.append(os.path.basename(chunk))
            except Exception as e:
              logger.warning(f"[MODEL] failed to remove chunk {chunk}: {e}")
    logger.info(f"[MODEL] deleted {name} ({len(deleted)} files)")
    return web.json_response({"status": "ok", "deleted": deleted, "bundle": name})

  async def handle_models_active(self, request):
    source = ModelFetcher.active_source(self._chestnut_present())
    active = get_active_bundle(self.params, chestnut=(source == "chestnut"))
    result = active.to_dict() if active is not None else {"internalName": DEFAULT_MODEL, "displayName": DEFAULT_MODEL, "isDefault": True}
    result["activeSource"] = source
    return web.json_response(result)

  async def handle_models_select(self, request):
    self._require_offroad()
    try:
      body = await request.json()
    except Exception:
      raise web.HTTPBadRequest(text="Invalid JSON") from None
    index = body.get("index")
    if index is None:
      raise web.HTTPBadRequest(text="Missing 'index'")
    index = int(index)
    bundles, _source = await self._active_source_bundles_async()
    bundle = next((b for b in bundles if b.index == index), None)
    if bundle is None:
      raise web.HTTPBadRequest(text=f"index {index} not in the current model catalog "
                                     f"(chestnut_present={self._chestnut_present()}); refresh the list and retry")
    if not bundle.ref:
      raise web.HTTPInternalServerError(text=f"Bundle '{bundle.internalName}' has no ref; cannot select")
    self.params.put("ModelManager_DownloadRef", bundle.ref)
    logger.info(f"[MODEL] selected index {index} (ref={bundle.ref})")
    return web.json_response({"status": "ok", "index": index, "ref": bundle.ref})

  async def handle_models_select_default(self, request):
    self._require_offroad()
    source = ModelFetcher.active_source(self._chestnut_present())
    self.params.remove(ACTIVE_BUNDLE_KEYS[source])
    logger.info(f"[MODEL] reset to default ({source})")
    return web.json_response({"status": "ok"})

  async def handle_models_progress(self, request):
    if self._model_state is None:
      return web.json_response({"error": "no model state"}, status=503)
    state = self._model_state.to_dict()
    return web.json_response({
      "selectedBundle": state.get("selectedBundle"),
      "activeBundle": state.get("activeBundle"),
      "availableBundles": state.get("availableBundles", []),
    })

  async def handle_models_cancel(self, request):
    self.params.remove("ModelManager_DownloadRef")
    logger.info("[MODEL] download cancelled")
    return web.json_response({"status": "ok"})

  async def handle_models_refresh(self, request):
    for _source, suffix in ModelFetcher.MODEL_SOURCES.values():
      self.params.remove(f"ModelManager_LastSyncTime{suffix}")
    logger.info("[MODEL] refresh triggered")
    return web.json_response({"status": "ok"})

  async def handle_models_cache_clear(self, request):
    self._require_offroad()
    self.params.put_bool("ModelManager_ClearCache", True)
    logger.info("[MODEL] cache clear requested")
    return web.json_response({"status": "ok"})

  async def handle_models_favorites(self, request):
    if request.method == "GET":
      raw_b = self.params.get("ModelManager_Favs")
      raw = raw_b.decode("utf-8", errors="replace") if isinstance(raw_b, bytes) else ""
      refs = [r for r in raw.split(";") if r] if raw else []
      return web.json_response(refs)
    else:
      try:
        body = await request.json()
      except Exception:
        raise web.HTTPBadRequest(text="Invalid JSON") from None
      refs = body.get("refs", [])
      self.params.put("ModelManager_Favs", ";".join(refs))
      logger.info(f"[MODEL] favorites saved ({len(refs)} refs)")
      return web.json_response({"status": "ok", "count": len(refs)})
