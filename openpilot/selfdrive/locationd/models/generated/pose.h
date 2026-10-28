#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3590467737713675004);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_837876479050183132);
void pose_H_mod_fun(double *state, double *out_5781655979714254891);
void pose_f_fun(double *state, double dt, double *out_2390805150352098946);
void pose_F_fun(double *state, double dt, double *out_3481270369411220980);
void pose_h_4(double *state, double *unused, double *out_7159453629796036478);
void pose_H_4(double *state, double *unused, double *out_6817006287243338004);
void pose_h_10(double *state, double *unused, double *out_8919665046689555279);
void pose_H_10(double *state, double *unused, double *out_5719523531190417023);
void pose_h_13(double *state, double *unused, double *out_6831827799770286357);
void pose_H_13(double *state, double *unused, double *out_8417463961133880811);
void pose_h_14(double *state, double *unused, double *out_5444267422335175417);
void pose_H_14(double *state, double *unused, double *out_7666496930126729083);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}