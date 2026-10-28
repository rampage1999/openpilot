#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_7684675897828251505);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3271762021836241551);
void car_H_mod_fun(double *state, double *out_4260954534327965905);
void car_f_fun(double *state, double dt, double *out_711772556810715790);
void car_F_fun(double *state, double dt, double *out_8730794660587298664);
void car_h_25(double *state, double *unused, double *out_3773573229349324741);
void car_H_25(double *state, double *unused, double *out_7688766579491555760);
void car_h_24(double *state, double *unused, double *out_4360966448843904663);
void car_H_24(double *state, double *unused, double *out_5073411746684302737);
void car_h_30(double *state, double *unused, double *out_2381873966491335388);
void car_H_30(double *state, double *unused, double *out_3161070249363947562);
void car_h_26(double *state, double *unused, double *out_1031620099980839346);
void car_H_26(double *state, double *unused, double *out_3947263260617499536);
void car_h_27(double *state, double *unused, double *out_6586125332619178124);
void car_H_27(double *state, double *unused, double *out_5384664320547890779);
void car_h_29(double *state, double *unused, double *out_6310931270334672235);
void car_H_29(double *state, double *unused, double *out_3671301593678339746);
void car_h_28(double *state, double *unused, double *out_5982809447942700607);
void car_H_28(double *state, double *unused, double *out_1411097423391190828);
void car_h_31(double *state, double *unused, double *out_3824533343459351328);
void car_H_31(double *state, double *unused, double *out_3321055158384148060);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}