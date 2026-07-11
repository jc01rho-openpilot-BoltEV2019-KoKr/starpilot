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
void err_fun(double *nom_x, double *delta_x, double *out_6125726627663246664) {
   out_6125726627663246664[0] = delta_x[0] + nom_x[0];
   out_6125726627663246664[1] = delta_x[1] + nom_x[1];
   out_6125726627663246664[2] = delta_x[2] + nom_x[2];
   out_6125726627663246664[3] = delta_x[3] + nom_x[3];
   out_6125726627663246664[4] = delta_x[4] + nom_x[4];
   out_6125726627663246664[5] = delta_x[5] + nom_x[5];
   out_6125726627663246664[6] = delta_x[6] + nom_x[6];
   out_6125726627663246664[7] = delta_x[7] + nom_x[7];
   out_6125726627663246664[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_87606233557452672) {
   out_87606233557452672[0] = -nom_x[0] + true_x[0];
   out_87606233557452672[1] = -nom_x[1] + true_x[1];
   out_87606233557452672[2] = -nom_x[2] + true_x[2];
   out_87606233557452672[3] = -nom_x[3] + true_x[3];
   out_87606233557452672[4] = -nom_x[4] + true_x[4];
   out_87606233557452672[5] = -nom_x[5] + true_x[5];
   out_87606233557452672[6] = -nom_x[6] + true_x[6];
   out_87606233557452672[7] = -nom_x[7] + true_x[7];
   out_87606233557452672[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1571740516032572076) {
   out_1571740516032572076[0] = 1.0;
   out_1571740516032572076[1] = 0.0;
   out_1571740516032572076[2] = 0.0;
   out_1571740516032572076[3] = 0.0;
   out_1571740516032572076[4] = 0.0;
   out_1571740516032572076[5] = 0.0;
   out_1571740516032572076[6] = 0.0;
   out_1571740516032572076[7] = 0.0;
   out_1571740516032572076[8] = 0.0;
   out_1571740516032572076[9] = 0.0;
   out_1571740516032572076[10] = 1.0;
   out_1571740516032572076[11] = 0.0;
   out_1571740516032572076[12] = 0.0;
   out_1571740516032572076[13] = 0.0;
   out_1571740516032572076[14] = 0.0;
   out_1571740516032572076[15] = 0.0;
   out_1571740516032572076[16] = 0.0;
   out_1571740516032572076[17] = 0.0;
   out_1571740516032572076[18] = 0.0;
   out_1571740516032572076[19] = 0.0;
   out_1571740516032572076[20] = 1.0;
   out_1571740516032572076[21] = 0.0;
   out_1571740516032572076[22] = 0.0;
   out_1571740516032572076[23] = 0.0;
   out_1571740516032572076[24] = 0.0;
   out_1571740516032572076[25] = 0.0;
   out_1571740516032572076[26] = 0.0;
   out_1571740516032572076[27] = 0.0;
   out_1571740516032572076[28] = 0.0;
   out_1571740516032572076[29] = 0.0;
   out_1571740516032572076[30] = 1.0;
   out_1571740516032572076[31] = 0.0;
   out_1571740516032572076[32] = 0.0;
   out_1571740516032572076[33] = 0.0;
   out_1571740516032572076[34] = 0.0;
   out_1571740516032572076[35] = 0.0;
   out_1571740516032572076[36] = 0.0;
   out_1571740516032572076[37] = 0.0;
   out_1571740516032572076[38] = 0.0;
   out_1571740516032572076[39] = 0.0;
   out_1571740516032572076[40] = 1.0;
   out_1571740516032572076[41] = 0.0;
   out_1571740516032572076[42] = 0.0;
   out_1571740516032572076[43] = 0.0;
   out_1571740516032572076[44] = 0.0;
   out_1571740516032572076[45] = 0.0;
   out_1571740516032572076[46] = 0.0;
   out_1571740516032572076[47] = 0.0;
   out_1571740516032572076[48] = 0.0;
   out_1571740516032572076[49] = 0.0;
   out_1571740516032572076[50] = 1.0;
   out_1571740516032572076[51] = 0.0;
   out_1571740516032572076[52] = 0.0;
   out_1571740516032572076[53] = 0.0;
   out_1571740516032572076[54] = 0.0;
   out_1571740516032572076[55] = 0.0;
   out_1571740516032572076[56] = 0.0;
   out_1571740516032572076[57] = 0.0;
   out_1571740516032572076[58] = 0.0;
   out_1571740516032572076[59] = 0.0;
   out_1571740516032572076[60] = 1.0;
   out_1571740516032572076[61] = 0.0;
   out_1571740516032572076[62] = 0.0;
   out_1571740516032572076[63] = 0.0;
   out_1571740516032572076[64] = 0.0;
   out_1571740516032572076[65] = 0.0;
   out_1571740516032572076[66] = 0.0;
   out_1571740516032572076[67] = 0.0;
   out_1571740516032572076[68] = 0.0;
   out_1571740516032572076[69] = 0.0;
   out_1571740516032572076[70] = 1.0;
   out_1571740516032572076[71] = 0.0;
   out_1571740516032572076[72] = 0.0;
   out_1571740516032572076[73] = 0.0;
   out_1571740516032572076[74] = 0.0;
   out_1571740516032572076[75] = 0.0;
   out_1571740516032572076[76] = 0.0;
   out_1571740516032572076[77] = 0.0;
   out_1571740516032572076[78] = 0.0;
   out_1571740516032572076[79] = 0.0;
   out_1571740516032572076[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_7904413896065989389) {
   out_7904413896065989389[0] = state[0];
   out_7904413896065989389[1] = state[1];
   out_7904413896065989389[2] = state[2];
   out_7904413896065989389[3] = state[3];
   out_7904413896065989389[4] = state[4];
   out_7904413896065989389[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_7904413896065989389[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_7904413896065989389[7] = state[7];
   out_7904413896065989389[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6516583174049416628) {
   out_6516583174049416628[0] = 1;
   out_6516583174049416628[1] = 0;
   out_6516583174049416628[2] = 0;
   out_6516583174049416628[3] = 0;
   out_6516583174049416628[4] = 0;
   out_6516583174049416628[5] = 0;
   out_6516583174049416628[6] = 0;
   out_6516583174049416628[7] = 0;
   out_6516583174049416628[8] = 0;
   out_6516583174049416628[9] = 0;
   out_6516583174049416628[10] = 1;
   out_6516583174049416628[11] = 0;
   out_6516583174049416628[12] = 0;
   out_6516583174049416628[13] = 0;
   out_6516583174049416628[14] = 0;
   out_6516583174049416628[15] = 0;
   out_6516583174049416628[16] = 0;
   out_6516583174049416628[17] = 0;
   out_6516583174049416628[18] = 0;
   out_6516583174049416628[19] = 0;
   out_6516583174049416628[20] = 1;
   out_6516583174049416628[21] = 0;
   out_6516583174049416628[22] = 0;
   out_6516583174049416628[23] = 0;
   out_6516583174049416628[24] = 0;
   out_6516583174049416628[25] = 0;
   out_6516583174049416628[26] = 0;
   out_6516583174049416628[27] = 0;
   out_6516583174049416628[28] = 0;
   out_6516583174049416628[29] = 0;
   out_6516583174049416628[30] = 1;
   out_6516583174049416628[31] = 0;
   out_6516583174049416628[32] = 0;
   out_6516583174049416628[33] = 0;
   out_6516583174049416628[34] = 0;
   out_6516583174049416628[35] = 0;
   out_6516583174049416628[36] = 0;
   out_6516583174049416628[37] = 0;
   out_6516583174049416628[38] = 0;
   out_6516583174049416628[39] = 0;
   out_6516583174049416628[40] = 1;
   out_6516583174049416628[41] = 0;
   out_6516583174049416628[42] = 0;
   out_6516583174049416628[43] = 0;
   out_6516583174049416628[44] = 0;
   out_6516583174049416628[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6516583174049416628[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6516583174049416628[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6516583174049416628[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6516583174049416628[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6516583174049416628[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6516583174049416628[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6516583174049416628[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6516583174049416628[53] = -9.8100000000000005*dt;
   out_6516583174049416628[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6516583174049416628[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6516583174049416628[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6516583174049416628[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6516583174049416628[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6516583174049416628[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6516583174049416628[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6516583174049416628[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6516583174049416628[62] = 0;
   out_6516583174049416628[63] = 0;
   out_6516583174049416628[64] = 0;
   out_6516583174049416628[65] = 0;
   out_6516583174049416628[66] = 0;
   out_6516583174049416628[67] = 0;
   out_6516583174049416628[68] = 0;
   out_6516583174049416628[69] = 0;
   out_6516583174049416628[70] = 1;
   out_6516583174049416628[71] = 0;
   out_6516583174049416628[72] = 0;
   out_6516583174049416628[73] = 0;
   out_6516583174049416628[74] = 0;
   out_6516583174049416628[75] = 0;
   out_6516583174049416628[76] = 0;
   out_6516583174049416628[77] = 0;
   out_6516583174049416628[78] = 0;
   out_6516583174049416628[79] = 0;
   out_6516583174049416628[80] = 1;
}
void h_25(double *state, double *unused, double *out_6845996924949086281) {
   out_6845996924949086281[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4925282443857457875) {
   out_4925282443857457875[0] = 0;
   out_4925282443857457875[1] = 0;
   out_4925282443857457875[2] = 0;
   out_4925282443857457875[3] = 0;
   out_4925282443857457875[4] = 0;
   out_4925282443857457875[5] = 0;
   out_4925282443857457875[6] = 1;
   out_4925282443857457875[7] = 0;
   out_4925282443857457875[8] = 0;
}
void h_24(double *state, double *unused, double *out_76787194833890602) {
   out_76787194833890602[0] = state[4];
   out_76787194833890602[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2493109189819469018) {
   out_2493109189819469018[0] = 0;
   out_2493109189819469018[1] = 0;
   out_2493109189819469018[2] = 0;
   out_2493109189819469018[3] = 0;
   out_2493109189819469018[4] = 1;
   out_2493109189819469018[5] = 0;
   out_2493109189819469018[6] = 0;
   out_2493109189819469018[7] = 0;
   out_2493109189819469018[8] = 0;
   out_2493109189819469018[9] = 0;
   out_2493109189819469018[10] = 0;
   out_2493109189819469018[11] = 0;
   out_2493109189819469018[12] = 0;
   out_2493109189819469018[13] = 0;
   out_2493109189819469018[14] = 1;
   out_2493109189819469018[15] = 0;
   out_2493109189819469018[16] = 0;
   out_2493109189819469018[17] = 0;
}
void h_30(double *state, double *unused, double *out_7304198287107647943) {
   out_7304198287107647943[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8993765299724485543) {
   out_8993765299724485543[0] = 0;
   out_8993765299724485543[1] = 0;
   out_8993765299724485543[2] = 0;
   out_8993765299724485543[3] = 0;
   out_8993765299724485543[4] = 1;
   out_8993765299724485543[5] = 0;
   out_8993765299724485543[6] = 0;
   out_8993765299724485543[7] = 0;
   out_8993765299724485543[8] = 0;
}
void h_26(double *state, double *unused, double *out_6360688434205985508) {
   out_6360688434205985508[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8666785762731514099) {
   out_8666785762731514099[0] = 0;
   out_8666785762731514099[1] = 0;
   out_8666785762731514099[2] = 0;
   out_8666785762731514099[3] = 0;
   out_8666785762731514099[4] = 0;
   out_8666785762731514099[5] = 0;
   out_8666785762731514099[6] = 0;
   out_8666785762731514099[7] = 1;
   out_8666785762731514099[8] = 0;
}
void h_27(double *state, double *unused, double *out_2448044843667457269) {
   out_2448044843667457269[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6819001987924060632) {
   out_6819001987924060632[0] = 0;
   out_6819001987924060632[1] = 0;
   out_6819001987924060632[2] = 0;
   out_6819001987924060632[3] = 1;
   out_6819001987924060632[4] = 0;
   out_6819001987924060632[5] = 0;
   out_6819001987924060632[6] = 0;
   out_6819001987924060632[7] = 0;
   out_6819001987924060632[8] = 0;
}
void h_29(double *state, double *unused, double *out_2302525019446802298) {
   out_2302525019446802298[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8942747429670673889) {
   out_8942747429670673889[0] = 0;
   out_8942747429670673889[1] = 1;
   out_8942747429670673889[2] = 0;
   out_8942747429670673889[3] = 0;
   out_8942747429670673889[4] = 0;
   out_8942747429670673889[5] = 0;
   out_8942747429670673889[6] = 0;
   out_8942747429670673889[7] = 0;
   out_8942747429670673889[8] = 0;
}
void h_28(double *state, double *unused, double *out_2553628423993388376) {
   out_2553628423993388376[0] = state[0];
}
void H_28(double *state, double *unused, double *out_4421597626969347153) {
   out_4421597626969347153[0] = 1;
   out_4421597626969347153[1] = 0;
   out_4421597626969347153[2] = 0;
   out_4421597626969347153[3] = 0;
   out_4421597626969347153[4] = 0;
   out_4421597626969347153[5] = 0;
   out_4421597626969347153[6] = 0;
   out_4421597626969347153[7] = 0;
   out_4421597626969347153[8] = 0;
}
void h_31(double *state, double *unused, double *out_7359576434127226352) {
   out_7359576434127226352[0] = state[8];
}
void H_31(double *state, double *unused, double *out_9153750208744686041) {
   out_9153750208744686041[0] = 0;
   out_9153750208744686041[1] = 0;
   out_9153750208744686041[2] = 0;
   out_9153750208744686041[3] = 0;
   out_9153750208744686041[4] = 0;
   out_9153750208744686041[5] = 0;
   out_9153750208744686041[6] = 0;
   out_9153750208744686041[7] = 0;
   out_9153750208744686041[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_6125726627663246664) {
  err_fun(nom_x, delta_x, out_6125726627663246664);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_87606233557452672) {
  inv_err_fun(nom_x, true_x, out_87606233557452672);
}
void car_H_mod_fun(double *state, double *out_1571740516032572076) {
  H_mod_fun(state, out_1571740516032572076);
}
void car_f_fun(double *state, double dt, double *out_7904413896065989389) {
  f_fun(state,  dt, out_7904413896065989389);
}
void car_F_fun(double *state, double dt, double *out_6516583174049416628) {
  F_fun(state,  dt, out_6516583174049416628);
}
void car_h_25(double *state, double *unused, double *out_6845996924949086281) {
  h_25(state, unused, out_6845996924949086281);
}
void car_H_25(double *state, double *unused, double *out_4925282443857457875) {
  H_25(state, unused, out_4925282443857457875);
}
void car_h_24(double *state, double *unused, double *out_76787194833890602) {
  h_24(state, unused, out_76787194833890602);
}
void car_H_24(double *state, double *unused, double *out_2493109189819469018) {
  H_24(state, unused, out_2493109189819469018);
}
void car_h_30(double *state, double *unused, double *out_7304198287107647943) {
  h_30(state, unused, out_7304198287107647943);
}
void car_H_30(double *state, double *unused, double *out_8993765299724485543) {
  H_30(state, unused, out_8993765299724485543);
}
void car_h_26(double *state, double *unused, double *out_6360688434205985508) {
  h_26(state, unused, out_6360688434205985508);
}
void car_H_26(double *state, double *unused, double *out_8666785762731514099) {
  H_26(state, unused, out_8666785762731514099);
}
void car_h_27(double *state, double *unused, double *out_2448044843667457269) {
  h_27(state, unused, out_2448044843667457269);
}
void car_H_27(double *state, double *unused, double *out_6819001987924060632) {
  H_27(state, unused, out_6819001987924060632);
}
void car_h_29(double *state, double *unused, double *out_2302525019446802298) {
  h_29(state, unused, out_2302525019446802298);
}
void car_H_29(double *state, double *unused, double *out_8942747429670673889) {
  H_29(state, unused, out_8942747429670673889);
}
void car_h_28(double *state, double *unused, double *out_2553628423993388376) {
  h_28(state, unused, out_2553628423993388376);
}
void car_H_28(double *state, double *unused, double *out_4421597626969347153) {
  H_28(state, unused, out_4421597626969347153);
}
void car_h_31(double *state, double *unused, double *out_7359576434127226352) {
  h_31(state, unused, out_7359576434127226352);
}
void car_H_31(double *state, double *unused, double *out_9153750208744686041) {
  H_31(state, unused, out_9153750208744686041);
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
