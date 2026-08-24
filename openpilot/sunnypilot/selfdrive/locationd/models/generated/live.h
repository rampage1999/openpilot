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
void live_H(double *in_vec, double *out_5944438352768695112);
void live_err_fun(double *nom_x, double *delta_x, double *out_2022920556967402000);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_838496141674065837);
void live_H_mod_fun(double *state, double *out_6188057407023569105);
void live_f_fun(double *state, double dt, double *out_1719595184395026895);
void live_F_fun(double *state, double dt, double *out_8969651437444752940);
void live_h_4(double *state, double *unused, double *out_4211599813535022415);
void live_H_4(double *state, double *unused, double *out_8670081026691459995);
void live_h_9(double *state, double *unused, double *out_4981956442067406222);
void live_H_9(double *state, double *unused, double *out_8911270673321050640);
void live_h_10(double *state, double *unused, double *out_897935477022336920);
void live_H_10(double *state, double *unused, double *out_7415350335965552326);
void live_h_12(double *state, double *unused, double *out_7515228109471249434);
void live_H_12(double *state, double *unused, double *out_4757206638986129826);
void live_h_35(double *state, double *unused, double *out_3750043675606491623);
void live_H_35(double *state, double *unused, double *out_2011643606661116117);
void live_h_32(double *state, double *unused, double *out_6069419539321922357);
void live_H_32(double *state, double *unused, double *out_772014557757301476);
void live_h_13(double *state, double *unused, double *out_2131988458609269632);
void live_H_13(double *state, double *unused, double *out_1094763673324122811);
void live_h_14(double *state, double *unused, double *out_4981956442067406222);
void live_H_14(double *state, double *unused, double *out_8911270673321050640);
void live_h_33(double *state, double *unused, double *out_7460893379396893988);
void live_H_33(double *state, double *unused, double *out_3259443985006626641);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}