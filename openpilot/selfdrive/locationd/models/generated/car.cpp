#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

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
void err_fun(double *nom_x, double *delta_x, double *out_7684675897828251505) {
   out_7684675897828251505[0] = delta_x[0] + nom_x[0];
   out_7684675897828251505[1] = delta_x[1] + nom_x[1];
   out_7684675897828251505[2] = delta_x[2] + nom_x[2];
   out_7684675897828251505[3] = delta_x[3] + nom_x[3];
   out_7684675897828251505[4] = delta_x[4] + nom_x[4];
   out_7684675897828251505[5] = delta_x[5] + nom_x[5];
   out_7684675897828251505[6] = delta_x[6] + nom_x[6];
   out_7684675897828251505[7] = delta_x[7] + nom_x[7];
   out_7684675897828251505[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3271762021836241551) {
   out_3271762021836241551[0] = -nom_x[0] + true_x[0];
   out_3271762021836241551[1] = -nom_x[1] + true_x[1];
   out_3271762021836241551[2] = -nom_x[2] + true_x[2];
   out_3271762021836241551[3] = -nom_x[3] + true_x[3];
   out_3271762021836241551[4] = -nom_x[4] + true_x[4];
   out_3271762021836241551[5] = -nom_x[5] + true_x[5];
   out_3271762021836241551[6] = -nom_x[6] + true_x[6];
   out_3271762021836241551[7] = -nom_x[7] + true_x[7];
   out_3271762021836241551[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4260954534327965905) {
   out_4260954534327965905[0] = 1.0;
   out_4260954534327965905[1] = 0.0;
   out_4260954534327965905[2] = 0.0;
   out_4260954534327965905[3] = 0.0;
   out_4260954534327965905[4] = 0.0;
   out_4260954534327965905[5] = 0.0;
   out_4260954534327965905[6] = 0.0;
   out_4260954534327965905[7] = 0.0;
   out_4260954534327965905[8] = 0.0;
   out_4260954534327965905[9] = 0.0;
   out_4260954534327965905[10] = 1.0;
   out_4260954534327965905[11] = 0.0;
   out_4260954534327965905[12] = 0.0;
   out_4260954534327965905[13] = 0.0;
   out_4260954534327965905[14] = 0.0;
   out_4260954534327965905[15] = 0.0;
   out_4260954534327965905[16] = 0.0;
   out_4260954534327965905[17] = 0.0;
   out_4260954534327965905[18] = 0.0;
   out_4260954534327965905[19] = 0.0;
   out_4260954534327965905[20] = 1.0;
   out_4260954534327965905[21] = 0.0;
   out_4260954534327965905[22] = 0.0;
   out_4260954534327965905[23] = 0.0;
   out_4260954534327965905[24] = 0.0;
   out_4260954534327965905[25] = 0.0;
   out_4260954534327965905[26] = 0.0;
   out_4260954534327965905[27] = 0.0;
   out_4260954534327965905[28] = 0.0;
   out_4260954534327965905[29] = 0.0;
   out_4260954534327965905[30] = 1.0;
   out_4260954534327965905[31] = 0.0;
   out_4260954534327965905[32] = 0.0;
   out_4260954534327965905[33] = 0.0;
   out_4260954534327965905[34] = 0.0;
   out_4260954534327965905[35] = 0.0;
   out_4260954534327965905[36] = 0.0;
   out_4260954534327965905[37] = 0.0;
   out_4260954534327965905[38] = 0.0;
   out_4260954534327965905[39] = 0.0;
   out_4260954534327965905[40] = 1.0;
   out_4260954534327965905[41] = 0.0;
   out_4260954534327965905[42] = 0.0;
   out_4260954534327965905[43] = 0.0;
   out_4260954534327965905[44] = 0.0;
   out_4260954534327965905[45] = 0.0;
   out_4260954534327965905[46] = 0.0;
   out_4260954534327965905[47] = 0.0;
   out_4260954534327965905[48] = 0.0;
   out_4260954534327965905[49] = 0.0;
   out_4260954534327965905[50] = 1.0;
   out_4260954534327965905[51] = 0.0;
   out_4260954534327965905[52] = 0.0;
   out_4260954534327965905[53] = 0.0;
   out_4260954534327965905[54] = 0.0;
   out_4260954534327965905[55] = 0.0;
   out_4260954534327965905[56] = 0.0;
   out_4260954534327965905[57] = 0.0;
   out_4260954534327965905[58] = 0.0;
   out_4260954534327965905[59] = 0.0;
   out_4260954534327965905[60] = 1.0;
   out_4260954534327965905[61] = 0.0;
   out_4260954534327965905[62] = 0.0;
   out_4260954534327965905[63] = 0.0;
   out_4260954534327965905[64] = 0.0;
   out_4260954534327965905[65] = 0.0;
   out_4260954534327965905[66] = 0.0;
   out_4260954534327965905[67] = 0.0;
   out_4260954534327965905[68] = 0.0;
   out_4260954534327965905[69] = 0.0;
   out_4260954534327965905[70] = 1.0;
   out_4260954534327965905[71] = 0.0;
   out_4260954534327965905[72] = 0.0;
   out_4260954534327965905[73] = 0.0;
   out_4260954534327965905[74] = 0.0;
   out_4260954534327965905[75] = 0.0;
   out_4260954534327965905[76] = 0.0;
   out_4260954534327965905[77] = 0.0;
   out_4260954534327965905[78] = 0.0;
   out_4260954534327965905[79] = 0.0;
   out_4260954534327965905[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_711772556810715790) {
   out_711772556810715790[0] = state[0];
   out_711772556810715790[1] = state[1];
   out_711772556810715790[2] = state[2];
   out_711772556810715790[3] = state[3];
   out_711772556810715790[4] = state[4];
   out_711772556810715790[5] = dt*(stiffness_front*(-state[2] - state[3] + state[7])*state[0]/state[1] + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/state[4] + ((-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/state[4] - state[4])*state[6] - 9.8100000000000005*state[8]) + state[5];
   out_711772556810715790[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_711772556810715790[7] = state[7];
   out_711772556810715790[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8730794660587298664) {
   out_8730794660587298664[0] = 1;
   out_8730794660587298664[1] = 0;
   out_8730794660587298664[2] = 0;
   out_8730794660587298664[3] = 0;
   out_8730794660587298664[4] = 0;
   out_8730794660587298664[5] = 0;
   out_8730794660587298664[6] = 0;
   out_8730794660587298664[7] = 0;
   out_8730794660587298664[8] = 0;
   out_8730794660587298664[9] = 0;
   out_8730794660587298664[10] = 1;
   out_8730794660587298664[11] = 0;
   out_8730794660587298664[12] = 0;
   out_8730794660587298664[13] = 0;
   out_8730794660587298664[14] = 0;
   out_8730794660587298664[15] = 0;
   out_8730794660587298664[16] = 0;
   out_8730794660587298664[17] = 0;
   out_8730794660587298664[18] = 0;
   out_8730794660587298664[19] = 0;
   out_8730794660587298664[20] = 1;
   out_8730794660587298664[21] = 0;
   out_8730794660587298664[22] = 0;
   out_8730794660587298664[23] = 0;
   out_8730794660587298664[24] = 0;
   out_8730794660587298664[25] = 0;
   out_8730794660587298664[26] = 0;
   out_8730794660587298664[27] = 0;
   out_8730794660587298664[28] = 0;
   out_8730794660587298664[29] = 0;
   out_8730794660587298664[30] = 1;
   out_8730794660587298664[31] = 0;
   out_8730794660587298664[32] = 0;
   out_8730794660587298664[33] = 0;
   out_8730794660587298664[34] = 0;
   out_8730794660587298664[35] = 0;
   out_8730794660587298664[36] = 0;
   out_8730794660587298664[37] = 0;
   out_8730794660587298664[38] = 0;
   out_8730794660587298664[39] = 0;
   out_8730794660587298664[40] = 1;
   out_8730794660587298664[41] = 0;
   out_8730794660587298664[42] = 0;
   out_8730794660587298664[43] = 0;
   out_8730794660587298664[44] = 0;
   out_8730794660587298664[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/state[1] + (-stiffness_front - stiffness_rear)*state[5]/state[4] + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/state[4]);
   out_8730794660587298664[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/pow(state[1], 2);
   out_8730794660587298664[47] = -dt*stiffness_front*state[0]/state[1];
   out_8730794660587298664[48] = -dt*stiffness_front*state[0]/state[1];
   out_8730794660587298664[49] = dt*(-(-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/pow(state[4], 2) + (-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/pow(state[4], 2) - 1)*state[6]);
   out_8730794660587298664[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/state[4] + 1;
   out_8730794660587298664[51] = dt*((-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/state[4] - state[4]);
   out_8730794660587298664[52] = dt*stiffness_front*state[0]/state[1];
   out_8730794660587298664[53] = -9.8100000000000005*dt;
   out_8730794660587298664[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8730794660587298664[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8730794660587298664[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8730794660587298664[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8730794660587298664[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8730794660587298664[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8730794660587298664[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8730794660587298664[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8730794660587298664[62] = 0;
   out_8730794660587298664[63] = 0;
   out_8730794660587298664[64] = 0;
   out_8730794660587298664[65] = 0;
   out_8730794660587298664[66] = 0;
   out_8730794660587298664[67] = 0;
   out_8730794660587298664[68] = 0;
   out_8730794660587298664[69] = 0;
   out_8730794660587298664[70] = 1;
   out_8730794660587298664[71] = 0;
   out_8730794660587298664[72] = 0;
   out_8730794660587298664[73] = 0;
   out_8730794660587298664[74] = 0;
   out_8730794660587298664[75] = 0;
   out_8730794660587298664[76] = 0;
   out_8730794660587298664[77] = 0;
   out_8730794660587298664[78] = 0;
   out_8730794660587298664[79] = 0;
   out_8730794660587298664[80] = 1;
}
void h_25(double *state, double *unused, double *out_3773573229349324741) {
   out_3773573229349324741[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7688766579491555760) {
   out_7688766579491555760[0] = 0;
   out_7688766579491555760[1] = 0;
   out_7688766579491555760[2] = 0;
   out_7688766579491555760[3] = 0;
   out_7688766579491555760[4] = 0;
   out_7688766579491555760[5] = 0;
   out_7688766579491555760[6] = 1;
   out_7688766579491555760[7] = 0;
   out_7688766579491555760[8] = 0;
}
void h_24(double *state, double *unused, double *out_4360966448843904663) {
   out_4360966448843904663[0] = state[4];
   out_4360966448843904663[1] = state[5];
}
void H_24(double *state, double *unused, double *out_5073411746684302737) {
   out_5073411746684302737[0] = 0;
   out_5073411746684302737[1] = 0;
   out_5073411746684302737[2] = 0;
   out_5073411746684302737[3] = 0;
   out_5073411746684302737[4] = 1;
   out_5073411746684302737[5] = 0;
   out_5073411746684302737[6] = 0;
   out_5073411746684302737[7] = 0;
   out_5073411746684302737[8] = 0;
   out_5073411746684302737[9] = 0;
   out_5073411746684302737[10] = 0;
   out_5073411746684302737[11] = 0;
   out_5073411746684302737[12] = 0;
   out_5073411746684302737[13] = 0;
   out_5073411746684302737[14] = 1;
   out_5073411746684302737[15] = 0;
   out_5073411746684302737[16] = 0;
   out_5073411746684302737[17] = 0;
}
void h_30(double *state, double *unused, double *out_2381873966491335388) {
   out_2381873966491335388[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3161070249363947562) {
   out_3161070249363947562[0] = 0;
   out_3161070249363947562[1] = 0;
   out_3161070249363947562[2] = 0;
   out_3161070249363947562[3] = 0;
   out_3161070249363947562[4] = 1;
   out_3161070249363947562[5] = 0;
   out_3161070249363947562[6] = 0;
   out_3161070249363947562[7] = 0;
   out_3161070249363947562[8] = 0;
}
void h_26(double *state, double *unused, double *out_1031620099980839346) {
   out_1031620099980839346[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3947263260617499536) {
   out_3947263260617499536[0] = 0;
   out_3947263260617499536[1] = 0;
   out_3947263260617499536[2] = 0;
   out_3947263260617499536[3] = 0;
   out_3947263260617499536[4] = 0;
   out_3947263260617499536[5] = 0;
   out_3947263260617499536[6] = 0;
   out_3947263260617499536[7] = 1;
   out_3947263260617499536[8] = 0;
}
void h_27(double *state, double *unused, double *out_6586125332619178124) {
   out_6586125332619178124[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5384664320547890779) {
   out_5384664320547890779[0] = 0;
   out_5384664320547890779[1] = 0;
   out_5384664320547890779[2] = 0;
   out_5384664320547890779[3] = 1;
   out_5384664320547890779[4] = 0;
   out_5384664320547890779[5] = 0;
   out_5384664320547890779[6] = 0;
   out_5384664320547890779[7] = 0;
   out_5384664320547890779[8] = 0;
}
void h_29(double *state, double *unused, double *out_6310931270334672235) {
   out_6310931270334672235[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3671301593678339746) {
   out_3671301593678339746[0] = 0;
   out_3671301593678339746[1] = 1;
   out_3671301593678339746[2] = 0;
   out_3671301593678339746[3] = 0;
   out_3671301593678339746[4] = 0;
   out_3671301593678339746[5] = 0;
   out_3671301593678339746[6] = 0;
   out_3671301593678339746[7] = 0;
   out_3671301593678339746[8] = 0;
}
void h_28(double *state, double *unused, double *out_5982809447942700607) {
   out_5982809447942700607[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1411097423391190828) {
   out_1411097423391190828[0] = 1;
   out_1411097423391190828[1] = 0;
   out_1411097423391190828[2] = 0;
   out_1411097423391190828[3] = 0;
   out_1411097423391190828[4] = 0;
   out_1411097423391190828[5] = 0;
   out_1411097423391190828[6] = 0;
   out_1411097423391190828[7] = 0;
   out_1411097423391190828[8] = 0;
}
void h_31(double *state, double *unused, double *out_3824533343459351328) {
   out_3824533343459351328[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3321055158384148060) {
   out_3321055158384148060[0] = 0;
   out_3321055158384148060[1] = 0;
   out_3321055158384148060[2] = 0;
   out_3321055158384148060[3] = 0;
   out_3321055158384148060[4] = 0;
   out_3321055158384148060[5] = 0;
   out_3321055158384148060[6] = 0;
   out_3321055158384148060[7] = 0;
   out_3321055158384148060[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7684675897828251505) {
  err_fun(nom_x, delta_x, out_7684675897828251505);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3271762021836241551) {
  inv_err_fun(nom_x, true_x, out_3271762021836241551);
}
void car_H_mod_fun(double *state, double *out_4260954534327965905) {
  H_mod_fun(state, out_4260954534327965905);
}
void car_f_fun(double *state, double dt, double *out_711772556810715790) {
  f_fun(state,  dt, out_711772556810715790);
}
void car_F_fun(double *state, double dt, double *out_8730794660587298664) {
  F_fun(state,  dt, out_8730794660587298664);
}
void car_h_25(double *state, double *unused, double *out_3773573229349324741) {
  h_25(state, unused, out_3773573229349324741);
}
void car_H_25(double *state, double *unused, double *out_7688766579491555760) {
  H_25(state, unused, out_7688766579491555760);
}
void car_h_24(double *state, double *unused, double *out_4360966448843904663) {
  h_24(state, unused, out_4360966448843904663);
}
void car_H_24(double *state, double *unused, double *out_5073411746684302737) {
  H_24(state, unused, out_5073411746684302737);
}
void car_h_30(double *state, double *unused, double *out_2381873966491335388) {
  h_30(state, unused, out_2381873966491335388);
}
void car_H_30(double *state, double *unused, double *out_3161070249363947562) {
  H_30(state, unused, out_3161070249363947562);
}
void car_h_26(double *state, double *unused, double *out_1031620099980839346) {
  h_26(state, unused, out_1031620099980839346);
}
void car_H_26(double *state, double *unused, double *out_3947263260617499536) {
  H_26(state, unused, out_3947263260617499536);
}
void car_h_27(double *state, double *unused, double *out_6586125332619178124) {
  h_27(state, unused, out_6586125332619178124);
}
void car_H_27(double *state, double *unused, double *out_5384664320547890779) {
  H_27(state, unused, out_5384664320547890779);
}
void car_h_29(double *state, double *unused, double *out_6310931270334672235) {
  h_29(state, unused, out_6310931270334672235);
}
void car_H_29(double *state, double *unused, double *out_3671301593678339746) {
  H_29(state, unused, out_3671301593678339746);
}
void car_h_28(double *state, double *unused, double *out_5982809447942700607) {
  h_28(state, unused, out_5982809447942700607);
}
void car_H_28(double *state, double *unused, double *out_1411097423391190828) {
  H_28(state, unused, out_1411097423391190828);
}
void car_h_31(double *state, double *unused, double *out_3824533343459351328) {
  h_31(state, unused, out_3824533343459351328);
}
void car_H_31(double *state, double *unused, double *out_3321055158384148060) {
  H_31(state, unused, out_3321055158384148060);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
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
