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
void car_err_fun(double *nom_x, double *delta_x, double *out_498208489621428851);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4444663366868356470);
void car_H_mod_fun(double *state, double *out_7541478269573606270);
void car_f_fun(double *state, double dt, double *out_1277839580894917185);
void car_F_fun(double *state, double dt, double *out_4666375696316270306);
void car_h_25(double *state, double *unused, double *out_3690425473857376286);
void car_H_25(double *state, double *unused, double *out_5740460659069369969);
void car_h_24(double *state, double *unused, double *out_7535816884758147684);
void car_H_24(double *state, double *unused, double *out_3034431748742800925);
void car_h_30(double *state, double *unused, double *out_6875045949098126145);
void car_H_30(double *state, double *unused, double *out_5611121711926129899);
void car_h_26(double *state, double *unused, double *out_5656067370877563135);
void car_H_26(double *state, double *unused, double *out_1998957340195313745);
void car_h_27(double *state, double *unused, double *out_8692098741518221931);
void car_H_27(double *state, double *unused, double *out_3436358400125704988);
void car_h_29(double *state, double *unused, double *out_8967292803802727820);
void car_H_29(double *state, double *unused, double *out_6121353056240522083);
void car_h_28(double *state, double *unused, double *out_3876359844632614597);
void car_H_28(double *state, double *unused, double *out_3686625944821480206);
void car_h_31(double *state, double *unused, double *out_52975945603353936);
void car_H_31(double *state, double *unused, double *out_5771106620946330397);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}