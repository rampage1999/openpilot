#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7473524147338108814);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1225327672199224143);
void pose_H_mod_fun(double *state, double *out_962358481072545828);
void pose_f_fun(double *state, double dt, double *out_8886629790052716118);
void pose_F_fun(double *state, double dt, double *out_8669821383571928839);
void pose_h_4(double *state, double *unused, double *out_5054205481177388779);
void pose_H_4(double *state, double *unused, double *out_8540023926579184446);
void pose_h_10(double *state, double *unused, double *out_5695429124193662539);
void pose_H_10(double *state, double *unused, double *out_2647901277076076620);
void pose_h_13(double *state, double *unused, double *out_4567101886999322894);
void pose_H_13(double *state, double *unused, double *out_6694446321798034369);
void pose_h_14(double *state, double *unused, double *out_8069458685978663356);
void pose_H_14(double *state, double *unused, double *out_5943479290790882641);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}