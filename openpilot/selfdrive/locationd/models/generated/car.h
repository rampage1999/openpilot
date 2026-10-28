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
void car_err_fun(double *nom_x, double *delta_x, double *out_4931480917654989094);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3720263356718088627);
void car_H_mod_fun(double *state, double *out_3363066837680760103);
void car_f_fun(double *state, double dt, double *out_4944182737255861326);
void car_F_fun(double *state, double dt, double *out_8132899872810809472);
void car_h_25(double *state, double *unused, double *out_3833826360218994353);
void car_H_25(double *state, double *unused, double *out_3133956122209269848);
void car_h_24(double *state, double *unused, double *out_6340901608858722494);
void car_H_24(double *state, double *unused, double *out_3604413604252608572);
void car_h_30(double *state, double *unused, double *out_196376831964972003);
void car_H_30(double *state, double *unused, double *out_3263295069352509918);
void car_h_26(double *state, double *unused, double *out_2840409219479360682);
void car_H_26(double *state, double *unused, double *out_6875459441083326072);
void car_h_27(double *state, double *unused, double *out_6438231681027692004);
void car_H_27(double *state, double *unused, double *out_5438058381152934829);
void car_h_29(double *state, double *unused, double *out_4805296435695873642);
void car_H_29(double *state, double *unused, double *out_7151421108022485862);
void car_h_28(double *state, double *unused, double *out_9058900054364317296);
void car_H_28(double *state, double *unused, double *out_6212923948617535180);
void car_h_31(double *state, double *unused, double *out_6731645062736508078);
void car_H_31(double *state, double *unused, double *out_3103310160332309420);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}