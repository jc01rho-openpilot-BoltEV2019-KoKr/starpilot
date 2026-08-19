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
void err_fun(double *nom_x, double *delta_x, double *out_555027713999943867) {
   out_555027713999943867[0] = delta_x[0] + nom_x[0];
   out_555027713999943867[1] = delta_x[1] + nom_x[1];
   out_555027713999943867[2] = delta_x[2] + nom_x[2];
   out_555027713999943867[3] = delta_x[3] + nom_x[3];
   out_555027713999943867[4] = delta_x[4] + nom_x[4];
   out_555027713999943867[5] = delta_x[5] + nom_x[5];
   out_555027713999943867[6] = delta_x[6] + nom_x[6];
   out_555027713999943867[7] = delta_x[7] + nom_x[7];
   out_555027713999943867[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7816877518147233589) {
   out_7816877518147233589[0] = -nom_x[0] + true_x[0];
   out_7816877518147233589[1] = -nom_x[1] + true_x[1];
   out_7816877518147233589[2] = -nom_x[2] + true_x[2];
   out_7816877518147233589[3] = -nom_x[3] + true_x[3];
   out_7816877518147233589[4] = -nom_x[4] + true_x[4];
   out_7816877518147233589[5] = -nom_x[5] + true_x[5];
   out_7816877518147233589[6] = -nom_x[6] + true_x[6];
   out_7816877518147233589[7] = -nom_x[7] + true_x[7];
   out_7816877518147233589[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4533074481319696241) {
   out_4533074481319696241[0] = 1.0;
   out_4533074481319696241[1] = 0.0;
   out_4533074481319696241[2] = 0.0;
   out_4533074481319696241[3] = 0.0;
   out_4533074481319696241[4] = 0.0;
   out_4533074481319696241[5] = 0.0;
   out_4533074481319696241[6] = 0.0;
   out_4533074481319696241[7] = 0.0;
   out_4533074481319696241[8] = 0.0;
   out_4533074481319696241[9] = 0.0;
   out_4533074481319696241[10] = 1.0;
   out_4533074481319696241[11] = 0.0;
   out_4533074481319696241[12] = 0.0;
   out_4533074481319696241[13] = 0.0;
   out_4533074481319696241[14] = 0.0;
   out_4533074481319696241[15] = 0.0;
   out_4533074481319696241[16] = 0.0;
   out_4533074481319696241[17] = 0.0;
   out_4533074481319696241[18] = 0.0;
   out_4533074481319696241[19] = 0.0;
   out_4533074481319696241[20] = 1.0;
   out_4533074481319696241[21] = 0.0;
   out_4533074481319696241[22] = 0.0;
   out_4533074481319696241[23] = 0.0;
   out_4533074481319696241[24] = 0.0;
   out_4533074481319696241[25] = 0.0;
   out_4533074481319696241[26] = 0.0;
   out_4533074481319696241[27] = 0.0;
   out_4533074481319696241[28] = 0.0;
   out_4533074481319696241[29] = 0.0;
   out_4533074481319696241[30] = 1.0;
   out_4533074481319696241[31] = 0.0;
   out_4533074481319696241[32] = 0.0;
   out_4533074481319696241[33] = 0.0;
   out_4533074481319696241[34] = 0.0;
   out_4533074481319696241[35] = 0.0;
   out_4533074481319696241[36] = 0.0;
   out_4533074481319696241[37] = 0.0;
   out_4533074481319696241[38] = 0.0;
   out_4533074481319696241[39] = 0.0;
   out_4533074481319696241[40] = 1.0;
   out_4533074481319696241[41] = 0.0;
   out_4533074481319696241[42] = 0.0;
   out_4533074481319696241[43] = 0.0;
   out_4533074481319696241[44] = 0.0;
   out_4533074481319696241[45] = 0.0;
   out_4533074481319696241[46] = 0.0;
   out_4533074481319696241[47] = 0.0;
   out_4533074481319696241[48] = 0.0;
   out_4533074481319696241[49] = 0.0;
   out_4533074481319696241[50] = 1.0;
   out_4533074481319696241[51] = 0.0;
   out_4533074481319696241[52] = 0.0;
   out_4533074481319696241[53] = 0.0;
   out_4533074481319696241[54] = 0.0;
   out_4533074481319696241[55] = 0.0;
   out_4533074481319696241[56] = 0.0;
   out_4533074481319696241[57] = 0.0;
   out_4533074481319696241[58] = 0.0;
   out_4533074481319696241[59] = 0.0;
   out_4533074481319696241[60] = 1.0;
   out_4533074481319696241[61] = 0.0;
   out_4533074481319696241[62] = 0.0;
   out_4533074481319696241[63] = 0.0;
   out_4533074481319696241[64] = 0.0;
   out_4533074481319696241[65] = 0.0;
   out_4533074481319696241[66] = 0.0;
   out_4533074481319696241[67] = 0.0;
   out_4533074481319696241[68] = 0.0;
   out_4533074481319696241[69] = 0.0;
   out_4533074481319696241[70] = 1.0;
   out_4533074481319696241[71] = 0.0;
   out_4533074481319696241[72] = 0.0;
   out_4533074481319696241[73] = 0.0;
   out_4533074481319696241[74] = 0.0;
   out_4533074481319696241[75] = 0.0;
   out_4533074481319696241[76] = 0.0;
   out_4533074481319696241[77] = 0.0;
   out_4533074481319696241[78] = 0.0;
   out_4533074481319696241[79] = 0.0;
   out_4533074481319696241[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5039337670867030572) {
   out_5039337670867030572[0] = state[0];
   out_5039337670867030572[1] = state[1];
   out_5039337670867030572[2] = state[2];
   out_5039337670867030572[3] = state[3];
   out_5039337670867030572[4] = state[4];
   out_5039337670867030572[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5039337670867030572[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5039337670867030572[7] = state[7];
   out_5039337670867030572[8] = state[8];
}
void F_fun(double *state, double dt, double *out_5181832378332727216) {
   out_5181832378332727216[0] = 1;
   out_5181832378332727216[1] = 0;
   out_5181832378332727216[2] = 0;
   out_5181832378332727216[3] = 0;
   out_5181832378332727216[4] = 0;
   out_5181832378332727216[5] = 0;
   out_5181832378332727216[6] = 0;
   out_5181832378332727216[7] = 0;
   out_5181832378332727216[8] = 0;
   out_5181832378332727216[9] = 0;
   out_5181832378332727216[10] = 1;
   out_5181832378332727216[11] = 0;
   out_5181832378332727216[12] = 0;
   out_5181832378332727216[13] = 0;
   out_5181832378332727216[14] = 0;
   out_5181832378332727216[15] = 0;
   out_5181832378332727216[16] = 0;
   out_5181832378332727216[17] = 0;
   out_5181832378332727216[18] = 0;
   out_5181832378332727216[19] = 0;
   out_5181832378332727216[20] = 1;
   out_5181832378332727216[21] = 0;
   out_5181832378332727216[22] = 0;
   out_5181832378332727216[23] = 0;
   out_5181832378332727216[24] = 0;
   out_5181832378332727216[25] = 0;
   out_5181832378332727216[26] = 0;
   out_5181832378332727216[27] = 0;
   out_5181832378332727216[28] = 0;
   out_5181832378332727216[29] = 0;
   out_5181832378332727216[30] = 1;
   out_5181832378332727216[31] = 0;
   out_5181832378332727216[32] = 0;
   out_5181832378332727216[33] = 0;
   out_5181832378332727216[34] = 0;
   out_5181832378332727216[35] = 0;
   out_5181832378332727216[36] = 0;
   out_5181832378332727216[37] = 0;
   out_5181832378332727216[38] = 0;
   out_5181832378332727216[39] = 0;
   out_5181832378332727216[40] = 1;
   out_5181832378332727216[41] = 0;
   out_5181832378332727216[42] = 0;
   out_5181832378332727216[43] = 0;
   out_5181832378332727216[44] = 0;
   out_5181832378332727216[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_5181832378332727216[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_5181832378332727216[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5181832378332727216[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5181832378332727216[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_5181832378332727216[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_5181832378332727216[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_5181832378332727216[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_5181832378332727216[53] = -9.8100000000000005*dt;
   out_5181832378332727216[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_5181832378332727216[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_5181832378332727216[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5181832378332727216[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5181832378332727216[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_5181832378332727216[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_5181832378332727216[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_5181832378332727216[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5181832378332727216[62] = 0;
   out_5181832378332727216[63] = 0;
   out_5181832378332727216[64] = 0;
   out_5181832378332727216[65] = 0;
   out_5181832378332727216[66] = 0;
   out_5181832378332727216[67] = 0;
   out_5181832378332727216[68] = 0;
   out_5181832378332727216[69] = 0;
   out_5181832378332727216[70] = 1;
   out_5181832378332727216[71] = 0;
   out_5181832378332727216[72] = 0;
   out_5181832378332727216[73] = 0;
   out_5181832378332727216[74] = 0;
   out_5181832378332727216[75] = 0;
   out_5181832378332727216[76] = 0;
   out_5181832378332727216[77] = 0;
   out_5181832378332727216[78] = 0;
   out_5181832378332727216[79] = 0;
   out_5181832378332727216[80] = 1;
}
void h_25(double *state, double *unused, double *out_9064502358369772671) {
   out_9064502358369772671[0] = state[6];
}
void H_25(double *state, double *unused, double *out_9009977767205190535) {
   out_9009977767205190535[0] = 0;
   out_9009977767205190535[1] = 0;
   out_9009977767205190535[2] = 0;
   out_9009977767205190535[3] = 0;
   out_9009977767205190535[4] = 0;
   out_9009977767205190535[5] = 0;
   out_9009977767205190535[6] = 1;
   out_9009977767205190535[7] = 0;
   out_9009977767205190535[8] = 0;
}
void h_24(double *state, double *unused, double *out_4315668618686905201) {
   out_4315668618686905201[0] = state[4];
   out_4315668618686905201[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4579303311377586733) {
   out_4579303311377586733[0] = 0;
   out_4579303311377586733[1] = 0;
   out_4579303311377586733[2] = 0;
   out_4579303311377586733[3] = 0;
   out_4579303311377586733[4] = 1;
   out_4579303311377586733[5] = 0;
   out_4579303311377586733[6] = 0;
   out_4579303311377586733[7] = 0;
   out_4579303311377586733[8] = 0;
   out_4579303311377586733[9] = 0;
   out_4579303311377586733[10] = 0;
   out_4579303311377586733[11] = 0;
   out_4579303311377586733[12] = 0;
   out_4579303311377586733[13] = 0;
   out_4579303311377586733[14] = 1;
   out_4579303311377586733[15] = 0;
   out_4579303311377586733[16] = 0;
   out_4579303311377586733[17] = 0;
}
void h_30(double *state, double *unused, double *out_8507922675073509890) {
   out_8507922675073509890[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2093287425713573780) {
   out_2093287425713573780[0] = 0;
   out_2093287425713573780[1] = 0;
   out_2093287425713573780[2] = 0;
   out_2093287425713573780[3] = 0;
   out_2093287425713573780[4] = 1;
   out_2093287425713573780[5] = 0;
   out_2093287425713573780[6] = 0;
   out_2093287425713573780[7] = 0;
   out_2093287425713573780[8] = 0;
}
void h_26(double *state, double *unused, double *out_4180836484642303770) {
   out_4180836484642303770[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5695262987630304857) {
   out_5695262987630304857[0] = 0;
   out_5695262987630304857[1] = 0;
   out_5695262987630304857[2] = 0;
   out_5695262987630304857[3] = 0;
   out_5695262987630304857[4] = 0;
   out_5695262987630304857[5] = 0;
   out_5695262987630304857[6] = 0;
   out_5695262987630304857[7] = 1;
   out_5695262987630304857[8] = 0;
}
void h_27(double *state, double *unused, double *out_4062829090708927026) {
   out_4062829090708927026[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4268050737513998691) {
   out_4268050737513998691[0] = 0;
   out_4268050737513998691[1] = 0;
   out_4268050737513998691[2] = 0;
   out_4268050737513998691[3] = 1;
   out_4268050737513998691[4] = 0;
   out_4268050737513998691[5] = 0;
   out_4268050737513998691[6] = 0;
   out_4268050737513998691[7] = 0;
   out_4268050737513998691[8] = 0;
}
void h_29(double *state, double *unused, double *out_7564412822171847455) {
   out_7564412822171847455[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5981413464383549724) {
   out_5981413464383549724[0] = 0;
   out_5981413464383549724[1] = 1;
   out_5981413464383549724[2] = 0;
   out_5981413464383549724[3] = 0;
   out_5981413464383549724[4] = 0;
   out_5981413464383549724[5] = 0;
   out_5981413464383549724[6] = 0;
   out_5981413464383549724[7] = 0;
   out_5981413464383549724[8] = 0;
}
void h_28(double *state, double *unused, double *out_1579900780372029809) {
   out_1579900780372029809[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7382931592256471318) {
   out_7382931592256471318[0] = 1;
   out_7382931592256471318[1] = 0;
   out_7382931592256471318[2] = 0;
   out_7382931592256471318[3] = 0;
   out_7382931592256471318[4] = 0;
   out_7382931592256471318[5] = 0;
   out_7382931592256471318[6] = 0;
   out_7382931592256471318[7] = 0;
   out_7382931592256471318[8] = 0;
}
void h_31(double *state, double *unused, double *out_6613551970606485049) {
   out_6613551970606485049[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8979331805328230107) {
   out_8979331805328230107[0] = 0;
   out_8979331805328230107[1] = 0;
   out_8979331805328230107[2] = 0;
   out_8979331805328230107[3] = 0;
   out_8979331805328230107[4] = 0;
   out_8979331805328230107[5] = 0;
   out_8979331805328230107[6] = 0;
   out_8979331805328230107[7] = 0;
   out_8979331805328230107[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_555027713999943867) {
  err_fun(nom_x, delta_x, out_555027713999943867);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7816877518147233589) {
  inv_err_fun(nom_x, true_x, out_7816877518147233589);
}
void car_H_mod_fun(double *state, double *out_4533074481319696241) {
  H_mod_fun(state, out_4533074481319696241);
}
void car_f_fun(double *state, double dt, double *out_5039337670867030572) {
  f_fun(state,  dt, out_5039337670867030572);
}
void car_F_fun(double *state, double dt, double *out_5181832378332727216) {
  F_fun(state,  dt, out_5181832378332727216);
}
void car_h_25(double *state, double *unused, double *out_9064502358369772671) {
  h_25(state, unused, out_9064502358369772671);
}
void car_H_25(double *state, double *unused, double *out_9009977767205190535) {
  H_25(state, unused, out_9009977767205190535);
}
void car_h_24(double *state, double *unused, double *out_4315668618686905201) {
  h_24(state, unused, out_4315668618686905201);
}
void car_H_24(double *state, double *unused, double *out_4579303311377586733) {
  H_24(state, unused, out_4579303311377586733);
}
void car_h_30(double *state, double *unused, double *out_8507922675073509890) {
  h_30(state, unused, out_8507922675073509890);
}
void car_H_30(double *state, double *unused, double *out_2093287425713573780) {
  H_30(state, unused, out_2093287425713573780);
}
void car_h_26(double *state, double *unused, double *out_4180836484642303770) {
  h_26(state, unused, out_4180836484642303770);
}
void car_H_26(double *state, double *unused, double *out_5695262987630304857) {
  H_26(state, unused, out_5695262987630304857);
}
void car_h_27(double *state, double *unused, double *out_4062829090708927026) {
  h_27(state, unused, out_4062829090708927026);
}
void car_H_27(double *state, double *unused, double *out_4268050737513998691) {
  H_27(state, unused, out_4268050737513998691);
}
void car_h_29(double *state, double *unused, double *out_7564412822171847455) {
  h_29(state, unused, out_7564412822171847455);
}
void car_H_29(double *state, double *unused, double *out_5981413464383549724) {
  H_29(state, unused, out_5981413464383549724);
}
void car_h_28(double *state, double *unused, double *out_1579900780372029809) {
  h_28(state, unused, out_1579900780372029809);
}
void car_H_28(double *state, double *unused, double *out_7382931592256471318) {
  H_28(state, unused, out_7382931592256471318);
}
void car_h_31(double *state, double *unused, double *out_6613551970606485049) {
  h_31(state, unused, out_6613551970606485049);
}
void car_H_31(double *state, double *unused, double *out_8979331805328230107) {
  H_31(state, unused, out_8979331805328230107);
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
