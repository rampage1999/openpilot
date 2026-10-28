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
void live_H(double *in_vec, double *out_7854270559929094551);
void live_err_fun(double *nom_x, double *delta_x, double *out_162539938841333917);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_5518685372429813110);
void live_H_mod_fun(double *state, double *out_4625924059861847414);
void live_f_fun(double *state, double dt, double *out_2994205473474413385);
void live_F_fun(double *state, double dt, double *out_2844093457209449540);
void live_h_4(double *state, double *unused, double *out_3371753902809698213);
void live_H_4(double *state, double *unused, double *out_4217898238061637445);
void live_h_9(double *state, double *unused, double *out_7102884147448571977);
void live_H_9(double *state, double *unused, double *out_4459087884691228090);
void live_h_10(double *state, double *unused, double *out_4663701319730798453);
void live_H_10(double *state, double *unused, double *out_715372899241233556);
void live_h_12(double *state, double *unused, double *out_8386573161429914465);
void live_H_12(double *state, double *unused, double *out_9209389427615952376);
void live_h_35(double *state, double *unused, double *out_849249085118243914);
void live_H_35(double *state, double *unused, double *out_7584560295434244821);
void live_h_32(double *state, double *unused, double *out_7766582212629369604);
void live_H_32(double *state, double *unused, double *out_7715725080374985290);
void live_h_13(double *state, double *unused, double *out_1499200986241463371);
void live_H_13(double *state, double *unused, double *out_2275018033639827678);
void live_h_14(double *state, double *unused, double *out_7102884147448571977);
void live_H_14(double *state, double *unused, double *out_4459087884691228090);
void live_h_33(double *state, double *unused, double *out_728840461053728098);
void live_H_33(double *state, double *unused, double *out_7711626773636449191);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}