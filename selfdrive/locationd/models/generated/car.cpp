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
void err_fun(double *nom_x, double *delta_x, double *out_4175267327343220067) {
   out_4175267327343220067[0] = delta_x[0] + nom_x[0];
   out_4175267327343220067[1] = delta_x[1] + nom_x[1];
   out_4175267327343220067[2] = delta_x[2] + nom_x[2];
   out_4175267327343220067[3] = delta_x[3] + nom_x[3];
   out_4175267327343220067[4] = delta_x[4] + nom_x[4];
   out_4175267327343220067[5] = delta_x[5] + nom_x[5];
   out_4175267327343220067[6] = delta_x[6] + nom_x[6];
   out_4175267327343220067[7] = delta_x[7] + nom_x[7];
   out_4175267327343220067[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8001717605441520298) {
   out_8001717605441520298[0] = -nom_x[0] + true_x[0];
   out_8001717605441520298[1] = -nom_x[1] + true_x[1];
   out_8001717605441520298[2] = -nom_x[2] + true_x[2];
   out_8001717605441520298[3] = -nom_x[3] + true_x[3];
   out_8001717605441520298[4] = -nom_x[4] + true_x[4];
   out_8001717605441520298[5] = -nom_x[5] + true_x[5];
   out_8001717605441520298[6] = -nom_x[6] + true_x[6];
   out_8001717605441520298[7] = -nom_x[7] + true_x[7];
   out_8001717605441520298[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7971983971871194008) {
   out_7971983971871194008[0] = 1.0;
   out_7971983971871194008[1] = 0.0;
   out_7971983971871194008[2] = 0.0;
   out_7971983971871194008[3] = 0.0;
   out_7971983971871194008[4] = 0.0;
   out_7971983971871194008[5] = 0.0;
   out_7971983971871194008[6] = 0.0;
   out_7971983971871194008[7] = 0.0;
   out_7971983971871194008[8] = 0.0;
   out_7971983971871194008[9] = 0.0;
   out_7971983971871194008[10] = 1.0;
   out_7971983971871194008[11] = 0.0;
   out_7971983971871194008[12] = 0.0;
   out_7971983971871194008[13] = 0.0;
   out_7971983971871194008[14] = 0.0;
   out_7971983971871194008[15] = 0.0;
   out_7971983971871194008[16] = 0.0;
   out_7971983971871194008[17] = 0.0;
   out_7971983971871194008[18] = 0.0;
   out_7971983971871194008[19] = 0.0;
   out_7971983971871194008[20] = 1.0;
   out_7971983971871194008[21] = 0.0;
   out_7971983971871194008[22] = 0.0;
   out_7971983971871194008[23] = 0.0;
   out_7971983971871194008[24] = 0.0;
   out_7971983971871194008[25] = 0.0;
   out_7971983971871194008[26] = 0.0;
   out_7971983971871194008[27] = 0.0;
   out_7971983971871194008[28] = 0.0;
   out_7971983971871194008[29] = 0.0;
   out_7971983971871194008[30] = 1.0;
   out_7971983971871194008[31] = 0.0;
   out_7971983971871194008[32] = 0.0;
   out_7971983971871194008[33] = 0.0;
   out_7971983971871194008[34] = 0.0;
   out_7971983971871194008[35] = 0.0;
   out_7971983971871194008[36] = 0.0;
   out_7971983971871194008[37] = 0.0;
   out_7971983971871194008[38] = 0.0;
   out_7971983971871194008[39] = 0.0;
   out_7971983971871194008[40] = 1.0;
   out_7971983971871194008[41] = 0.0;
   out_7971983971871194008[42] = 0.0;
   out_7971983971871194008[43] = 0.0;
   out_7971983971871194008[44] = 0.0;
   out_7971983971871194008[45] = 0.0;
   out_7971983971871194008[46] = 0.0;
   out_7971983971871194008[47] = 0.0;
   out_7971983971871194008[48] = 0.0;
   out_7971983971871194008[49] = 0.0;
   out_7971983971871194008[50] = 1.0;
   out_7971983971871194008[51] = 0.0;
   out_7971983971871194008[52] = 0.0;
   out_7971983971871194008[53] = 0.0;
   out_7971983971871194008[54] = 0.0;
   out_7971983971871194008[55] = 0.0;
   out_7971983971871194008[56] = 0.0;
   out_7971983971871194008[57] = 0.0;
   out_7971983971871194008[58] = 0.0;
   out_7971983971871194008[59] = 0.0;
   out_7971983971871194008[60] = 1.0;
   out_7971983971871194008[61] = 0.0;
   out_7971983971871194008[62] = 0.0;
   out_7971983971871194008[63] = 0.0;
   out_7971983971871194008[64] = 0.0;
   out_7971983971871194008[65] = 0.0;
   out_7971983971871194008[66] = 0.0;
   out_7971983971871194008[67] = 0.0;
   out_7971983971871194008[68] = 0.0;
   out_7971983971871194008[69] = 0.0;
   out_7971983971871194008[70] = 1.0;
   out_7971983971871194008[71] = 0.0;
   out_7971983971871194008[72] = 0.0;
   out_7971983971871194008[73] = 0.0;
   out_7971983971871194008[74] = 0.0;
   out_7971983971871194008[75] = 0.0;
   out_7971983971871194008[76] = 0.0;
   out_7971983971871194008[77] = 0.0;
   out_7971983971871194008[78] = 0.0;
   out_7971983971871194008[79] = 0.0;
   out_7971983971871194008[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_1960663178760025601) {
   out_1960663178760025601[0] = state[0];
   out_1960663178760025601[1] = state[1];
   out_1960663178760025601[2] = state[2];
   out_1960663178760025601[3] = state[3];
   out_1960663178760025601[4] = state[4];
   out_1960663178760025601[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_1960663178760025601[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_1960663178760025601[7] = state[7];
   out_1960663178760025601[8] = state[8];
}
void F_fun(double *state, double dt, double *out_893498683805935900) {
   out_893498683805935900[0] = 1;
   out_893498683805935900[1] = 0;
   out_893498683805935900[2] = 0;
   out_893498683805935900[3] = 0;
   out_893498683805935900[4] = 0;
   out_893498683805935900[5] = 0;
   out_893498683805935900[6] = 0;
   out_893498683805935900[7] = 0;
   out_893498683805935900[8] = 0;
   out_893498683805935900[9] = 0;
   out_893498683805935900[10] = 1;
   out_893498683805935900[11] = 0;
   out_893498683805935900[12] = 0;
   out_893498683805935900[13] = 0;
   out_893498683805935900[14] = 0;
   out_893498683805935900[15] = 0;
   out_893498683805935900[16] = 0;
   out_893498683805935900[17] = 0;
   out_893498683805935900[18] = 0;
   out_893498683805935900[19] = 0;
   out_893498683805935900[20] = 1;
   out_893498683805935900[21] = 0;
   out_893498683805935900[22] = 0;
   out_893498683805935900[23] = 0;
   out_893498683805935900[24] = 0;
   out_893498683805935900[25] = 0;
   out_893498683805935900[26] = 0;
   out_893498683805935900[27] = 0;
   out_893498683805935900[28] = 0;
   out_893498683805935900[29] = 0;
   out_893498683805935900[30] = 1;
   out_893498683805935900[31] = 0;
   out_893498683805935900[32] = 0;
   out_893498683805935900[33] = 0;
   out_893498683805935900[34] = 0;
   out_893498683805935900[35] = 0;
   out_893498683805935900[36] = 0;
   out_893498683805935900[37] = 0;
   out_893498683805935900[38] = 0;
   out_893498683805935900[39] = 0;
   out_893498683805935900[40] = 1;
   out_893498683805935900[41] = 0;
   out_893498683805935900[42] = 0;
   out_893498683805935900[43] = 0;
   out_893498683805935900[44] = 0;
   out_893498683805935900[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_893498683805935900[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_893498683805935900[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_893498683805935900[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_893498683805935900[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_893498683805935900[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_893498683805935900[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_893498683805935900[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_893498683805935900[53] = -9.8100000000000005*dt;
   out_893498683805935900[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_893498683805935900[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_893498683805935900[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_893498683805935900[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_893498683805935900[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_893498683805935900[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_893498683805935900[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_893498683805935900[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_893498683805935900[62] = 0;
   out_893498683805935900[63] = 0;
   out_893498683805935900[64] = 0;
   out_893498683805935900[65] = 0;
   out_893498683805935900[66] = 0;
   out_893498683805935900[67] = 0;
   out_893498683805935900[68] = 0;
   out_893498683805935900[69] = 0;
   out_893498683805935900[70] = 1;
   out_893498683805935900[71] = 0;
   out_893498683805935900[72] = 0;
   out_893498683805935900[73] = 0;
   out_893498683805935900[74] = 0;
   out_893498683805935900[75] = 0;
   out_893498683805935900[76] = 0;
   out_893498683805935900[77] = 0;
   out_893498683805935900[78] = 0;
   out_893498683805935900[79] = 0;
   out_893498683805935900[80] = 1;
}
void h_25(double *state, double *unused, double *out_3235092958161781685) {
   out_3235092958161781685[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4449003321881702331) {
   out_4449003321881702331[0] = 0;
   out_4449003321881702331[1] = 0;
   out_4449003321881702331[2] = 0;
   out_4449003321881702331[3] = 0;
   out_4449003321881702331[4] = 0;
   out_4449003321881702331[5] = 0;
   out_4449003321881702331[6] = 1;
   out_4449003321881702331[7] = 0;
   out_4449003321881702331[8] = 0;
}
void h_24(double *state, double *unused, double *out_5426063249126145013) {
   out_5426063249126145013[0] = state[4];
   out_5426063249126145013[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4845648626235561826) {
   out_4845648626235561826[0] = 0;
   out_4845648626235561826[1] = 0;
   out_4845648626235561826[2] = 0;
   out_4845648626235561826[3] = 0;
   out_4845648626235561826[4] = 1;
   out_4845648626235561826[5] = 0;
   out_4845648626235561826[6] = 0;
   out_4845648626235561826[7] = 0;
   out_4845648626235561826[8] = 0;
   out_4845648626235561826[9] = 0;
   out_4845648626235561826[10] = 0;
   out_4845648626235561826[11] = 0;
   out_4845648626235561826[12] = 0;
   out_4845648626235561826[13] = 0;
   out_4845648626235561826[14] = 1;
   out_4845648626235561826[15] = 0;
   out_4845648626235561826[16] = 0;
   out_4845648626235561826[17] = 0;
}
void h_30(double *state, double *unused, double *out_9056203919707109802) {
   out_9056203919707109802[0] = state[4];
}
void H_30(double *state, double *unused, double *out_1930670363374453704) {
   out_1930670363374453704[0] = 0;
   out_1930670363374453704[1] = 0;
   out_1930670363374453704[2] = 0;
   out_1930670363374453704[3] = 0;
   out_1930670363374453704[4] = 1;
   out_1930670363374453704[5] = 0;
   out_1930670363374453704[6] = 0;
   out_1930670363374453704[7] = 0;
   out_1930670363374453704[8] = 0;
}
void h_26(double *state, double *unused, double *out_6243651816437256419) {
   out_6243651816437256419[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8190506640755758555) {
   out_8190506640755758555[0] = 0;
   out_8190506640755758555[1] = 0;
   out_8190506640755758555[2] = 0;
   out_8190506640755758555[3] = 0;
   out_8190506640755758555[4] = 0;
   out_8190506640755758555[5] = 0;
   out_8190506640755758555[6] = 0;
   out_8190506640755758555[7] = 1;
   out_8190506640755758555[8] = 0;
}
void h_27(double *state, double *unused, double *out_3838408842838259202) {
   out_3838408842838259202[0] = state[3];
}
void H_27(double *state, double *unused, double *out_292923707809489513) {
   out_292923707809489513[0] = 0;
   out_292923707809489513[1] = 0;
   out_292923707809489513[2] = 0;
   out_292923707809489513[3] = 1;
   out_292923707809489513[4] = 0;
   out_292923707809489513[5] = 0;
   out_292923707809489513[6] = 0;
   out_292923707809489513[7] = 0;
   out_292923707809489513[8] = 0;
}
void h_29(double *state, double *unused, double *out_259894455441112662) {
   out_259894455441112662[0] = state[1];
}
void H_29(double *state, double *unused, double *out_1420439019060061520) {
   out_1420439019060061520[0] = 0;
   out_1420439019060061520[1] = 1;
   out_1420439019060061520[2] = 0;
   out_1420439019060061520[3] = 0;
   out_1420439019060061520[4] = 0;
   out_1420439019060061520[5] = 0;
   out_1420439019060061520[6] = 0;
   out_1420439019060061520[7] = 0;
   out_1420439019060061520[8] = 0;
}
void h_28(double *state, double *unused, double *out_5143560329168581563) {
   out_5143560329168581563[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6502838036129592094) {
   out_6502838036129592094[0] = 1;
   out_6502838036129592094[1] = 0;
   out_6502838036129592094[2] = 0;
   out_6502838036129592094[3] = 0;
   out_6502838036129592094[4] = 0;
   out_6502838036129592094[5] = 0;
   out_6502838036129592094[6] = 0;
   out_6502838036129592094[7] = 0;
   out_6502838036129592094[8] = 0;
}
void h_31(double *state, double *unused, double *out_2959898895877275796) {
   out_2959898895877275796[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4418357360004741903) {
   out_4418357360004741903[0] = 0;
   out_4418357360004741903[1] = 0;
   out_4418357360004741903[2] = 0;
   out_4418357360004741903[3] = 0;
   out_4418357360004741903[4] = 0;
   out_4418357360004741903[5] = 0;
   out_4418357360004741903[6] = 0;
   out_4418357360004741903[7] = 0;
   out_4418357360004741903[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_4175267327343220067) {
  err_fun(nom_x, delta_x, out_4175267327343220067);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8001717605441520298) {
  inv_err_fun(nom_x, true_x, out_8001717605441520298);
}
void car_H_mod_fun(double *state, double *out_7971983971871194008) {
  H_mod_fun(state, out_7971983971871194008);
}
void car_f_fun(double *state, double dt, double *out_1960663178760025601) {
  f_fun(state,  dt, out_1960663178760025601);
}
void car_F_fun(double *state, double dt, double *out_893498683805935900) {
  F_fun(state,  dt, out_893498683805935900);
}
void car_h_25(double *state, double *unused, double *out_3235092958161781685) {
  h_25(state, unused, out_3235092958161781685);
}
void car_H_25(double *state, double *unused, double *out_4449003321881702331) {
  H_25(state, unused, out_4449003321881702331);
}
void car_h_24(double *state, double *unused, double *out_5426063249126145013) {
  h_24(state, unused, out_5426063249126145013);
}
void car_H_24(double *state, double *unused, double *out_4845648626235561826) {
  H_24(state, unused, out_4845648626235561826);
}
void car_h_30(double *state, double *unused, double *out_9056203919707109802) {
  h_30(state, unused, out_9056203919707109802);
}
void car_H_30(double *state, double *unused, double *out_1930670363374453704) {
  H_30(state, unused, out_1930670363374453704);
}
void car_h_26(double *state, double *unused, double *out_6243651816437256419) {
  h_26(state, unused, out_6243651816437256419);
}
void car_H_26(double *state, double *unused, double *out_8190506640755758555) {
  H_26(state, unused, out_8190506640755758555);
}
void car_h_27(double *state, double *unused, double *out_3838408842838259202) {
  h_27(state, unused, out_3838408842838259202);
}
void car_H_27(double *state, double *unused, double *out_292923707809489513) {
  H_27(state, unused, out_292923707809489513);
}
void car_h_29(double *state, double *unused, double *out_259894455441112662) {
  h_29(state, unused, out_259894455441112662);
}
void car_H_29(double *state, double *unused, double *out_1420439019060061520) {
  H_29(state, unused, out_1420439019060061520);
}
void car_h_28(double *state, double *unused, double *out_5143560329168581563) {
  h_28(state, unused, out_5143560329168581563);
}
void car_H_28(double *state, double *unused, double *out_6502838036129592094) {
  H_28(state, unused, out_6502838036129592094);
}
void car_h_31(double *state, double *unused, double *out_2959898895877275796) {
  h_31(state, unused, out_2959898895877275796);
}
void car_H_31(double *state, double *unused, double *out_4418357360004741903) {
  H_31(state, unused, out_4418357360004741903);
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
