#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_5399608859025573007);
void live_err_fun(double *nom_x, double *delta_x, double *out_5108375337402324381);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_3098727881771865040);
void live_H_mod_fun(double *state, double *out_8085635969819740497);
void live_f_fun(double *state, double dt, double *out_623876751526014962);
void live_F_fun(double *state, double dt, double *out_363282873502398966);
void live_h_4(double *state, double *unused, double *out_6390899320889962599);
void live_H_4(double *state, double *unused, double *out_6602504709790569844);
void live_h_9(double *state, double *unused, double *out_4183880885289153055);
void live_H_9(double *state, double *unused, double *out_6361315063160979199);
void live_h_10(double *state, double *unused, double *out_976623482051852456);
void live_H_10(double *state, double *unused, double *out_8039326971173179009);
void live_h_12(double *state, double *unused, double *out_8096970660246383949);
void live_H_12(double *state, double *unused, double *out_1583048301758608049);
void live_h_35(double *state, double *unused, double *out_3739615015963405424);
void live_H_35(double *state, double *unused, double *out_3235842652417962468);
void live_h_32(double *state, double *unused, double *out_78279947368908369);
void live_H_32(double *state, double *unused, double *out_2565461719789650090);
void live_h_13(double *state, double *unused, double *out_5811343064699704999);
void live_H_13(double *state, double *unused, double *out_1406307166050427206);
void live_h_14(double *state, double *unused, double *out_4183880885289153055);
void live_H_14(double *state, double *unused, double *out_6361315063160979199);
void live_h_33(double *state, double *unused, double *out_8103396478043874306);
void live_H_33(double *state, double *unused, double *out_85285647779104864);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}