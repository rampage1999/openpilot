#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_498208489621428851) {
   out_498208489621428851[0] = delta_x[0] + nom_x[0];
   out_498208489621428851[1] = delta_x[1] + nom_x[1];
   out_498208489621428851[2] = delta_x[2] + nom_x[2];
   out_498208489621428851[3] = delta_x[3] + nom_x[3];
   out_498208489621428851[4] = delta_x[4] + nom_x[4];
   out_498208489621428851[5] = delta_x[5] + nom_x[5];
   out_498208489621428851[6] = delta_x[6] + nom_x[6];
   out_498208489621428851[7] = delta_x[7] + nom_x[7];
   out_498208489621428851[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4444663366868356470) {
   out_4444663366868356470[0] = -nom_x[0] + true_x[0];
   out_4444663366868356470[1] = -nom_x[1] + true_x[1];
   out_4444663366868356470[2] = -nom_x[2] + true_x[2];
   out_4444663366868356470[3] = -nom_x[3] + true_x[3];
   out_4444663366868356470[4] = -nom_x[4] + true_x[4];
   out_4444663366868356470[5] = -nom_x[5] + true_x[5];
   out_4444663366868356470[6] = -nom_x[6] + true_x[6];
   out_4444663366868356470[7] = -nom_x[7] + true_x[7];
   out_4444663366868356470[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7541478269573606270) {
   out_7541478269573606270[0] = 1.0;
   out_7541478269573606270[1] = 0.0;
   out_7541478269573606270[2] = 0.0;
   out_7541478269573606270[3] = 0.0;
   out_7541478269573606270[4] = 0.0;
   out_7541478269573606270[5] = 0.0;
   out_7541478269573606270[6] = 0.0;
   out_7541478269573606270[7] = 0.0;
   out_7541478269573606270[8] = 0.0;
   out_7541478269573606270[9] = 0.0;
   out_7541478269573606270[10] = 1.0;
   out_7541478269573606270[11] = 0.0;
   out_7541478269573606270[12] = 0.0;
   out_7541478269573606270[13] = 0.0;
   out_7541478269573606270[14] = 0.0;
   out_7541478269573606270[15] = 0.0;
   out_7541478269573606270[16] = 0.0;
   out_7541478269573606270[17] = 0.0;
   out_7541478269573606270[18] = 0.0;
   out_7541478269573606270[19] = 0.0;
   out_7541478269573606270[20] = 1.0;
   out_7541478269573606270[21] = 0.0;
   out_7541478269573606270[22] = 0.0;
   out_7541478269573606270[23] = 0.0;
   out_7541478269573606270[24] = 0.0;
   out_7541478269573606270[25] = 0.0;
   out_7541478269573606270[26] = 0.0;
   out_7541478269573606270[27] = 0.0;
   out_7541478269573606270[28] = 0.0;
   out_7541478269573606270[29] = 0.0;
   out_7541478269573606270[30] = 1.0;
   out_7541478269573606270[31] = 0.0;
   out_7541478269573606270[32] = 0.0;
   out_7541478269573606270[33] = 0.0;
   out_7541478269573606270[34] = 0.0;
   out_7541478269573606270[35] = 0.0;
   out_7541478269573606270[36] = 0.0;
   out_7541478269573606270[37] = 0.0;
   out_7541478269573606270[38] = 0.0;
   out_7541478269573606270[39] = 0.0;
   out_7541478269573606270[40] = 1.0;
   out_7541478269573606270[41] = 0.0;
   out_7541478269573606270[42] = 0.0;
   out_7541478269573606270[43] = 0.0;
   out_7541478269573606270[44] = 0.0;
   out_7541478269573606270[45] = 0.0;
   out_7541478269573606270[46] = 0.0;
   out_7541478269573606270[47] = 0.0;
   out_7541478269573606270[48] = 0.0;
   out_7541478269573606270[49] = 0.0;
   out_7541478269573606270[50] = 1.0;
   out_7541478269573606270[51] = 0.0;
   out_7541478269573606270[52] = 0.0;
   out_7541478269573606270[53] = 0.0;
   out_7541478269573606270[54] = 0.0;
   out_7541478269573606270[55] = 0.0;
   out_7541478269573606270[56] = 0.0;
   out_7541478269573606270[57] = 0.0;
   out_7541478269573606270[58] = 0.0;
   out_7541478269573606270[59] = 0.0;
   out_7541478269573606270[60] = 1.0;
   out_7541478269573606270[61] = 0.0;
   out_7541478269573606270[62] = 0.0;
   out_7541478269573606270[63] = 0.0;
   out_7541478269573606270[64] = 0.0;
   out_7541478269573606270[65] = 0.0;
   out_7541478269573606270[66] = 0.0;
   out_7541478269573606270[67] = 0.0;
   out_7541478269573606270[68] = 0.0;
   out_7541478269573606270[69] = 0.0;
   out_7541478269573606270[70] = 1.0;
   out_7541478269573606270[71] = 0.0;
   out_7541478269573606270[72] = 0.0;
   out_7541478269573606270[73] = 0.0;
   out_7541478269573606270[74] = 0.0;
   out_7541478269573606270[75] = 0.0;
   out_7541478269573606270[76] = 0.0;
   out_7541478269573606270[77] = 0.0;
   out_7541478269573606270[78] = 0.0;
   out_7541478269573606270[79] = 0.0;
   out_7541478269573606270[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_1277839580894917185) {
   out_1277839580894917185[0] = state[0];
   out_1277839580894917185[1] = state[1];
   out_1277839580894917185[2] = state[2];
   out_1277839580894917185[3] = state[3];
   out_1277839580894917185[4] = state[4];
   out_1277839580894917185[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_1277839580894917185[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_1277839580894917185[7] = state[7];
   out_1277839580894917185[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4666375696316270306) {
   out_4666375696316270306[0] = 1;
   out_4666375696316270306[1] = 0;
   out_4666375696316270306[2] = 0;
   out_4666375696316270306[3] = 0;
   out_4666375696316270306[4] = 0;
   out_4666375696316270306[5] = 0;
   out_4666375696316270306[6] = 0;
   out_4666375696316270306[7] = 0;
   out_4666375696316270306[8] = 0;
   out_4666375696316270306[9] = 0;
   out_4666375696316270306[10] = 1;
   out_4666375696316270306[11] = 0;
   out_4666375696316270306[12] = 0;
   out_4666375696316270306[13] = 0;
   out_4666375696316270306[14] = 0;
   out_4666375696316270306[15] = 0;
   out_4666375696316270306[16] = 0;
   out_4666375696316270306[17] = 0;
   out_4666375696316270306[18] = 0;
   out_4666375696316270306[19] = 0;
   out_4666375696316270306[20] = 1;
   out_4666375696316270306[21] = 0;
   out_4666375696316270306[22] = 0;
   out_4666375696316270306[23] = 0;
   out_4666375696316270306[24] = 0;
   out_4666375696316270306[25] = 0;
   out_4666375696316270306[26] = 0;
   out_4666375696316270306[27] = 0;
   out_4666375696316270306[28] = 0;
   out_4666375696316270306[29] = 0;
   out_4666375696316270306[30] = 1;
   out_4666375696316270306[31] = 0;
   out_4666375696316270306[32] = 0;
   out_4666375696316270306[33] = 0;
   out_4666375696316270306[34] = 0;
   out_4666375696316270306[35] = 0;
   out_4666375696316270306[36] = 0;
   out_4666375696316270306[37] = 0;
   out_4666375696316270306[38] = 0;
   out_4666375696316270306[39] = 0;
   out_4666375696316270306[40] = 1;
   out_4666375696316270306[41] = 0;
   out_4666375696316270306[42] = 0;
   out_4666375696316270306[43] = 0;
   out_4666375696316270306[44] = 0;
   out_4666375696316270306[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4666375696316270306[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4666375696316270306[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4666375696316270306[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4666375696316270306[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4666375696316270306[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4666375696316270306[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4666375696316270306[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4666375696316270306[53] = -9.8100000000000005*dt;
   out_4666375696316270306[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4666375696316270306[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4666375696316270306[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4666375696316270306[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4666375696316270306[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4666375696316270306[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4666375696316270306[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4666375696316270306[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4666375696316270306[62] = 0;
   out_4666375696316270306[63] = 0;
   out_4666375696316270306[64] = 0;
   out_4666375696316270306[65] = 0;
   out_4666375696316270306[66] = 0;
   out_4666375696316270306[67] = 0;
   out_4666375696316270306[68] = 0;
   out_4666375696316270306[69] = 0;
   out_4666375696316270306[70] = 1;
   out_4666375696316270306[71] = 0;
   out_4666375696316270306[72] = 0;
   out_4666375696316270306[73] = 0;
   out_4666375696316270306[74] = 0;
   out_4666375696316270306[75] = 0;
   out_4666375696316270306[76] = 0;
   out_4666375696316270306[77] = 0;
   out_4666375696316270306[78] = 0;
   out_4666375696316270306[79] = 0;
   out_4666375696316270306[80] = 1;
}
void h_25(double *state, double *unused, double *out_3690425473857376286) {
   out_3690425473857376286[0] = state[6];
}
void H_25(double *state, double *unused, double *out_5740460659069369969) {
   out_5740460659069369969[0] = 0;
   out_5740460659069369969[1] = 0;
   out_5740460659069369969[2] = 0;
   out_5740460659069369969[3] = 0;
   out_5740460659069369969[4] = 0;
   out_5740460659069369969[5] = 0;
   out_5740460659069369969[6] = 1;
   out_5740460659069369969[7] = 0;
   out_5740460659069369969[8] = 0;
}
void h_24(double *state, double *unused, double *out_7535816884758147684) {
   out_7535816884758147684[0] = state[4];
   out_7535816884758147684[1] = state[5];
}
void H_24(double *state, double *unused, double *out_3034431748742800925) {
   out_3034431748742800925[0] = 0;
   out_3034431748742800925[1] = 0;
   out_3034431748742800925[2] = 0;
   out_3034431748742800925[3] = 0;
   out_3034431748742800925[4] = 1;
   out_3034431748742800925[5] = 0;
   out_3034431748742800925[6] = 0;
   out_3034431748742800925[7] = 0;
   out_3034431748742800925[8] = 0;
   out_3034431748742800925[9] = 0;
   out_3034431748742800925[10] = 0;
   out_3034431748742800925[11] = 0;
   out_3034431748742800925[12] = 0;
   out_3034431748742800925[13] = 0;
   out_3034431748742800925[14] = 1;
   out_3034431748742800925[15] = 0;
   out_3034431748742800925[16] = 0;
   out_3034431748742800925[17] = 0;
}
void h_30(double *state, double *unused, double *out_6875045949098126145) {
   out_6875045949098126145[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5611121711926129899) {
   out_5611121711926129899[0] = 0;
   out_5611121711926129899[1] = 0;
   out_5611121711926129899[2] = 0;
   out_5611121711926129899[3] = 0;
   out_5611121711926129899[4] = 1;
   out_5611121711926129899[5] = 0;
   out_5611121711926129899[6] = 0;
   out_5611121711926129899[7] = 0;
   out_5611121711926129899[8] = 0;
}
void h_26(double *state, double *unused, double *out_5656067370877563135) {
   out_5656067370877563135[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1998957340195313745) {
   out_1998957340195313745[0] = 0;
   out_1998957340195313745[1] = 0;
   out_1998957340195313745[2] = 0;
   out_1998957340195313745[3] = 0;
   out_1998957340195313745[4] = 0;
   out_1998957340195313745[5] = 0;
   out_1998957340195313745[6] = 0;
   out_1998957340195313745[7] = 1;
   out_1998957340195313745[8] = 0;
}
void h_27(double *state, double *unused, double *out_8692098741518221931) {
   out_8692098741518221931[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3436358400125704988) {
   out_3436358400125704988[0] = 0;
   out_3436358400125704988[1] = 0;
   out_3436358400125704988[2] = 0;
   out_3436358400125704988[3] = 1;
   out_3436358400125704988[4] = 0;
   out_3436358400125704988[5] = 0;
   out_3436358400125704988[6] = 0;
   out_3436358400125704988[7] = 0;
   out_3436358400125704988[8] = 0;
}
void h_29(double *state, double *unused, double *out_8967292803802727820) {
   out_8967292803802727820[0] = state[1];
}
void H_29(double *state, double *unused, double *out_6121353056240522083) {
   out_6121353056240522083[0] = 0;
   out_6121353056240522083[1] = 1;
   out_6121353056240522083[2] = 0;
   out_6121353056240522083[3] = 0;
   out_6121353056240522083[4] = 0;
   out_6121353056240522083[5] = 0;
   out_6121353056240522083[6] = 0;
   out_6121353056240522083[7] = 0;
   out_6121353056240522083[8] = 0;
}
void h_28(double *state, double *unused, double *out_3876359844632614597) {
   out_3876359844632614597[0] = state[0];
}
void H_28(double *state, double *unused, double *out_3686625944821480206) {
   out_3686625944821480206[0] = 1;
   out_3686625944821480206[1] = 0;
   out_3686625944821480206[2] = 0;
   out_3686625944821480206[3] = 0;
   out_3686625944821480206[4] = 0;
   out_3686625944821480206[5] = 0;
   out_3686625944821480206[6] = 0;
   out_3686625944821480206[7] = 0;
   out_3686625944821480206[8] = 0;
}
void h_31(double *state, double *unused, double *out_52975945603353936) {
   out_52975945603353936[0] = state[8];
}
void H_31(double *state, double *unused, double *out_5771106620946330397) {
   out_5771106620946330397[0] = 0;
   out_5771106620946330397[1] = 0;
   out_5771106620946330397[2] = 0;
   out_5771106620946330397[3] = 0;
   out_5771106620946330397[4] = 0;
   out_5771106620946330397[5] = 0;
   out_5771106620946330397[6] = 0;
   out_5771106620946330397[7] = 0;
   out_5771106620946330397[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_498208489621428851) {
  err_fun(nom_x, delta_x, out_498208489621428851);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4444663366868356470) {
  inv_err_fun(nom_x, true_x, out_4444663366868356470);
}
void car_H_mod_fun(double *state, double *out_7541478269573606270) {
  H_mod_fun(state, out_7541478269573606270);
}
void car_f_fun(double *state, double dt, double *out_1277839580894917185) {
  f_fun(state,  dt, out_1277839580894917185);
}
void car_F_fun(double *state, double dt, double *out_4666375696316270306) {
  F_fun(state,  dt, out_4666375696316270306);
}
void car_h_25(double *state, double *unused, double *out_3690425473857376286) {
  h_25(state, unused, out_3690425473857376286);
}
void car_H_25(double *state, double *unused, double *out_5740460659069369969) {
  H_25(state, unused, out_5740460659069369969);
}
void car_h_24(double *state, double *unused, double *out_7535816884758147684) {
  h_24(state, unused, out_7535816884758147684);
}
void car_H_24(double *state, double *unused, double *out_3034431748742800925) {
  H_24(state, unused, out_3034431748742800925);
}
void car_h_30(double *state, double *unused, double *out_6875045949098126145) {
  h_30(state, unused, out_6875045949098126145);
}
void car_H_30(double *state, double *unused, double *out_5611121711926129899) {
  H_30(state, unused, out_5611121711926129899);
}
void car_h_26(double *state, double *unused, double *out_5656067370877563135) {
  h_26(state, unused, out_5656067370877563135);
}
void car_H_26(double *state, double *unused, double *out_1998957340195313745) {
  H_26(state, unused, out_1998957340195313745);
}
void car_h_27(double *state, double *unused, double *out_8692098741518221931) {
  h_27(state, unused, out_8692098741518221931);
}
void car_H_27(double *state, double *unused, double *out_3436358400125704988) {
  H_27(state, unused, out_3436358400125704988);
}
void car_h_29(double *state, double *unused, double *out_8967292803802727820) {
  h_29(state, unused, out_8967292803802727820);
}
void car_H_29(double *state, double *unused, double *out_6121353056240522083) {
  H_29(state, unused, out_6121353056240522083);
}
void car_h_28(double *state, double *unused, double *out_3876359844632614597) {
  h_28(state, unused, out_3876359844632614597);
}
void car_H_28(double *state, double *unused, double *out_3686625944821480206) {
  H_28(state, unused, out_3686625944821480206);
}
void car_h_31(double *state, double *unused, double *out_52975945603353936) {
  h_31(state, unused, out_52975945603353936);
}
void car_H_31(double *state, double *unused, double *out_5771106620946330397) {
  H_31(state, unused, out_5771106620946330397);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
