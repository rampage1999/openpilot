#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_8069274513708895969);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6148460760368505675);
void pose_H_mod_fun(double *state, double *out_3716754627317504890);
void pose_f_fun(double *state, double dt, double *out_4855167580946130027);
void pose_F_fun(double *state, double dt, double *out_4420770900431173050);
void pose_h_4(double *state, double *unused, double *out_169586844375619970);
void pose_H_4(double *state, double *unused, double *out_2962593625262792283);
void pose_h_10(double *state, double *unused, double *out_8793925764545223572);
void pose_H_10(double *state, double *unused, double *out_2626145331746833569);
void pose_h_13(double *state, double *unused, double *out_4090467412018967888);
void pose_H_13(double *state, double *unused, double *out_6796349088565316307);
void pose_h_14(double *state, double *unused, double *out_8363622320862145642);
void pose_H_14(double *state, double *unused, double *out_6045382057558164579);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}