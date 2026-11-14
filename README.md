![](https://user-images.githubusercontent.com/47793918/233812617-beab2e71-57b9-479e-8bff-c3931347ca40.png)

## 🌞 What is sunnypilot?
[sunnypilot](https://github.com/sunnyhaibin/sunnypilot) is a fork of comma.ai's openpilot, an open source driver assistance system. sunnypilot offers the user a unique driving experience for over 300+ supported car makes and models with modified behaviors of driving assist engagements. sunnypilot complies with comma.ai's safety rules as accurately as possible.

## 💭 Join our Community Forum
Join the official sunnypilot community forum to stay up to date with all the latest features and be a part of shaping the future of sunnypilot!
* https://community.sunnypilot.ai/

## Documentation
https://docs.sunnypilot.ai/ is your one stop shop for everything from features to installation to FAQ about the sunnypilot

## 🚘 Running on a dedicated device in a car
First, check out this list of items you'll need to [get started](https://community.sunnypilot.ai/t/getting-started-using-sunnypilot-in-your-supported-car/251).

## Installation
Next, refer to the sunnypilot community forum for [installation instructions](https://community.sunnypilot.ai/t/read-before-installing-sunnypilot/254), as well as a complete list of [Recommended Branch Installations](https://community.sunnypilot.ai/t/recommended-branch-installations/235).

## 🚗 Tesla Model S / Model X (HW1) support

This branch adds support for first-generation Autopilot (HW1) Tesla Model S (2014-16) and Model X (2014-16) on top of sunnypilot.

* Branch: `tesla-hw1-port`
* Installer: `https://installer.comma.ai/rampage1999/tesla-hw1-port`
* Platforms: `TESLA_MODEL_S_HW1`, `TESLA_MODEL_X_HW1`
* Harness: Tesla Model S/X HW1 connector, harness box, long OBD-C cable, USB-C coupler

What the port contains:

* HW1 platform configs, fingerprints and CarDocs entries in opendbc
* Legacy Tesla CAN parsing (`teslacan_legacy.py`, `tesla_can.dbc`) for the pre-Autopilot signal layout, plus `tesla_raven_party.dbc`
* Bosch radar support for HW1 cars (`radar_interface.py`)
* A dedicated panda safety mode, `tesla_legacy.h`, with HW1 ignition handling
* sunnypilot car list / carstate extensions and torque overrides for the legacy platforms
* locationd, calibrationd and paramsd adjustments for the slower legacy sensor set
* AP1 blind-spot levels from `0x399` with a 1 s latch per side (levels 1/2 = car, 0/3 SNA ignored)
* AP1 hands-on pause: firm EPAS torque withholds lateral without dropping cruise and resumes 0.3 s after the driver lets go
* AP1 regen-sized comfort braking: 1.0 m/s² lead-approach cost so regen does the work before friction brakes join
* AP1 accel shaping: 2.5 m/s³ rising, 2.0→8 m/s³ brake onset, −1.0 standstill floor, gas-neutral frame
* Follows the car's own speed-limit signs: the Mobileye `DAS_fusedSpeedLimit` on `AutopilotStatus` (0x399) now reaches `carStateSP.speedLimit`, and with `SpeedLimitMode=assist` + `SpeedLimitPolicy=car_state_priority` a sign change moves the set speed (and the cluster set speed) to the new limit
* Tools: `tools/bogpilot-fingerprint` (PII-safe rlog → fingerprint export) and `tools/driver-mover` (driver-monitoring overlay video)

Verified on a 2014-16 Model S: the car fingerprints as `TESLA_MODEL_S_HW1`, `dashcamOnly` is false, and openpilot engaged and drove the car with no alerts logged in the route.

⚠️ HW1 support is experimental. Legacy CAN is slower and this platform has far less testing than HW2+/HW3 cars. Treat every drive as a test drive, keep your hands on the wheel and be ready to take over immediately.

## 🎆 Pull Requests
We welcome both pull requests and issues on GitHub. Bug fixes are encouraged.

Pull requests should be against the most current `master` branch.

## 📊 User Data

By default, sunnypilot uploads the driving data to comma servers. You can also access your data through [comma connect](https://connect.comma.ai/).

sunnypilot is open source software. The user is free to disable data collection if they wish to do so.

sunnypilot logs the road-facing camera, CAN, GPS, IMU, magnetometer, thermal sensors, crashes, and operating system logs.
The driver-facing camera and microphone are only logged if you explicitly opt-in in settings.

By using this software, you understand that use of this software or its related services will generate certain types of user data, which may be logged and stored at the sole discretion of comma. By accepting this agreement, you grant an irrevocable, perpetual, worldwide right to comma for the use of this data.

## Licensing

sunnypilot is released under the [MIT License](LICENSE). This repository includes original work as well as significant portions of code derived from [openpilot by comma.ai](https://github.com/commaai/openpilot), which is also released under the MIT license with additional disclaimers.

The original openpilot license notice, including comma.ai’s indemnification and alpha software disclaimer, is reproduced below as required:

> openpilot is released under the MIT license. Some parts of the software are released under other licenses as specified.
>
> Any user of this software shall indemnify and hold harmless Comma.ai, Inc. and its directors, officers, employees, agents, stockholders, affiliates, subcontractors and customers from and against all allegations, claims, actions, suits, demands, damages, liabilities, obligations, losses, settlements, judgments, costs and expenses (including without limitation attorneys’ fees and costs) which arise out of, relate to or result from any use of this software by user.
>
> **THIS IS ALPHA QUALITY SOFTWARE FOR RESEARCH PURPOSES ONLY. THIS IS NOT A PRODUCT.
> YOU ARE RESPONSIBLE FOR COMPLYING WITH LOCAL LAWS AND REGULATIONS.
> NO WARRANTY EXPRESSED OR IMPLIED.**

For full license terms, please see the [`LICENSE`](LICENSE) file.

## 💰 Support sunnypilot
If you find any of the features useful, consider becoming a [sponsor on GitHub](https://github.com/sponsors/sunnyhaibin) to support future feature development and improvements.


By becoming a sponsor, you will gain access to exclusive content, early access to new features, and the opportunity to directly influence the project's development.


<h3>GitHub Sponsor</h3>

<a href="https://github.com/sponsors/sunnyhaibin">
  <img src="https://user-images.githubusercontent.com/47793918/244135584-9800acbd-69fd-4b2b-bec9-e5fa2d85c817.png" alt="Become a Sponsor" width="300" style="max-width: 100%; height: auto;">
</a>
<br>

<h3>PayPal</h3>

<a href="https://paypal.me/sunnyhaibin0850" target="_blank">
<img src="https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif" alt="PayPal this" title="PayPal - The safer, easier way to pay online!" border="0" />
</a>
<br></br>

Your continuous love and support are greatly appreciated! Enjoy 🥰

<span>-</span> Jason, Founder of sunnypilot
