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
void err_fun(double *nom_x, double *delta_x, double *out_7839106046248465839) {
   out_7839106046248465839[0] = delta_x[0] + nom_x[0];
   out_7839106046248465839[1] = delta_x[1] + nom_x[1];
   out_7839106046248465839[2] = delta_x[2] + nom_x[2];
   out_7839106046248465839[3] = delta_x[3] + nom_x[3];
   out_7839106046248465839[4] = delta_x[4] + nom_x[4];
   out_7839106046248465839[5] = delta_x[5] + nom_x[5];
   out_7839106046248465839[6] = delta_x[6] + nom_x[6];
   out_7839106046248465839[7] = delta_x[7] + nom_x[7];
   out_7839106046248465839[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_31659364612209693) {
   out_31659364612209693[0] = -nom_x[0] + true_x[0];
   out_31659364612209693[1] = -nom_x[1] + true_x[1];
   out_31659364612209693[2] = -nom_x[2] + true_x[2];
   out_31659364612209693[3] = -nom_x[3] + true_x[3];
   out_31659364612209693[4] = -nom_x[4] + true_x[4];
   out_31659364612209693[5] = -nom_x[5] + true_x[5];
   out_31659364612209693[6] = -nom_x[6] + true_x[6];
   out_31659364612209693[7] = -nom_x[7] + true_x[7];
   out_31659364612209693[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6082546015176302038) {
   out_6082546015176302038[0] = 1.0;
   out_6082546015176302038[1] = 0.0;
   out_6082546015176302038[2] = 0.0;
   out_6082546015176302038[3] = 0.0;
   out_6082546015176302038[4] = 0.0;
   out_6082546015176302038[5] = 0.0;
   out_6082546015176302038[6] = 0.0;
   out_6082546015176302038[7] = 0.0;
   out_6082546015176302038[8] = 0.0;
   out_6082546015176302038[9] = 0.0;
   out_6082546015176302038[10] = 1.0;
   out_6082546015176302038[11] = 0.0;
   out_6082546015176302038[12] = 0.0;
   out_6082546015176302038[13] = 0.0;
   out_6082546015176302038[14] = 0.0;
   out_6082546015176302038[15] = 0.0;
   out_6082546015176302038[16] = 0.0;
   out_6082546015176302038[17] = 0.0;
   out_6082546015176302038[18] = 0.0;
   out_6082546015176302038[19] = 0.0;
   out_6082546015176302038[20] = 1.0;
   out_6082546015176302038[21] = 0.0;
   out_6082546015176302038[22] = 0.0;
   out_6082546015176302038[23] = 0.0;
   out_6082546015176302038[24] = 0.0;
   out_6082546015176302038[25] = 0.0;
   out_6082546015176302038[26] = 0.0;
   out_6082546015176302038[27] = 0.0;
   out_6082546015176302038[28] = 0.0;
   out_6082546015176302038[29] = 0.0;
   out_6082546015176302038[30] = 1.0;
   out_6082546015176302038[31] = 0.0;
   out_6082546015176302038[32] = 0.0;
   out_6082546015176302038[33] = 0.0;
   out_6082546015176302038[34] = 0.0;
   out_6082546015176302038[35] = 0.0;
   out_6082546015176302038[36] = 0.0;
   out_6082546015176302038[37] = 0.0;
   out_6082546015176302038[38] = 0.0;
   out_6082546015176302038[39] = 0.0;
   out_6082546015176302038[40] = 1.0;
   out_6082546015176302038[41] = 0.0;
   out_6082546015176302038[42] = 0.0;
   out_6082546015176302038[43] = 0.0;
   out_6082546015176302038[44] = 0.0;
   out_6082546015176302038[45] = 0.0;
   out_6082546015176302038[46] = 0.0;
   out_6082546015176302038[47] = 0.0;
   out_6082546015176302038[48] = 0.0;
   out_6082546015176302038[49] = 0.0;
   out_6082546015176302038[50] = 1.0;
   out_6082546015176302038[51] = 0.0;
   out_6082546015176302038[52] = 0.0;
   out_6082546015176302038[53] = 0.0;
   out_6082546015176302038[54] = 0.0;
   out_6082546015176302038[55] = 0.0;
   out_6082546015176302038[56] = 0.0;
   out_6082546015176302038[57] = 0.0;
   out_6082546015176302038[58] = 0.0;
   out_6082546015176302038[59] = 0.0;
   out_6082546015176302038[60] = 1.0;
   out_6082546015176302038[61] = 0.0;
   out_6082546015176302038[62] = 0.0;
   out_6082546015176302038[63] = 0.0;
   out_6082546015176302038[64] = 0.0;
   out_6082546015176302038[65] = 0.0;
   out_6082546015176302038[66] = 0.0;
   out_6082546015176302038[67] = 0.0;
   out_6082546015176302038[68] = 0.0;
   out_6082546015176302038[69] = 0.0;
   out_6082546015176302038[70] = 1.0;
   out_6082546015176302038[71] = 0.0;
   out_6082546015176302038[72] = 0.0;
   out_6082546015176302038[73] = 0.0;
   out_6082546015176302038[74] = 0.0;
   out_6082546015176302038[75] = 0.0;
   out_6082546015176302038[76] = 0.0;
   out_6082546015176302038[77] = 0.0;
   out_6082546015176302038[78] = 0.0;
   out_6082546015176302038[79] = 0.0;
   out_6082546015176302038[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6850955649577617071) {
   out_6850955649577617071[0] = state[0];
   out_6850955649577617071[1] = state[1];
   out_6850955649577617071[2] = state[2];
   out_6850955649577617071[3] = state[3];
   out_6850955649577617071[4] = state[4];
   out_6850955649577617071[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6850955649577617071[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6850955649577617071[7] = state[7];
   out_6850955649577617071[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6972181184240044918) {
   out_6972181184240044918[0] = 1;
   out_6972181184240044918[1] = 0;
   out_6972181184240044918[2] = 0;
   out_6972181184240044918[3] = 0;
   out_6972181184240044918[4] = 0;
   out_6972181184240044918[5] = 0;
   out_6972181184240044918[6] = 0;
   out_6972181184240044918[7] = 0;
   out_6972181184240044918[8] = 0;
   out_6972181184240044918[9] = 0;
   out_6972181184240044918[10] = 1;
   out_6972181184240044918[11] = 0;
   out_6972181184240044918[12] = 0;
   out_6972181184240044918[13] = 0;
   out_6972181184240044918[14] = 0;
   out_6972181184240044918[15] = 0;
   out_6972181184240044918[16] = 0;
   out_6972181184240044918[17] = 0;
   out_6972181184240044918[18] = 0;
   out_6972181184240044918[19] = 0;
   out_6972181184240044918[20] = 1;
   out_6972181184240044918[21] = 0;
   out_6972181184240044918[22] = 0;
   out_6972181184240044918[23] = 0;
   out_6972181184240044918[24] = 0;
   out_6972181184240044918[25] = 0;
   out_6972181184240044918[26] = 0;
   out_6972181184240044918[27] = 0;
   out_6972181184240044918[28] = 0;
   out_6972181184240044918[29] = 0;
   out_6972181184240044918[30] = 1;
   out_6972181184240044918[31] = 0;
   out_6972181184240044918[32] = 0;
   out_6972181184240044918[33] = 0;
   out_6972181184240044918[34] = 0;
   out_6972181184240044918[35] = 0;
   out_6972181184240044918[36] = 0;
   out_6972181184240044918[37] = 0;
   out_6972181184240044918[38] = 0;
   out_6972181184240044918[39] = 0;
   out_6972181184240044918[40] = 1;
   out_6972181184240044918[41] = 0;
   out_6972181184240044918[42] = 0;
   out_6972181184240044918[43] = 0;
   out_6972181184240044918[44] = 0;
   out_6972181184240044918[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6972181184240044918[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6972181184240044918[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6972181184240044918[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6972181184240044918[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6972181184240044918[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6972181184240044918[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6972181184240044918[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6972181184240044918[53] = -9.8100000000000005*dt;
   out_6972181184240044918[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6972181184240044918[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6972181184240044918[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6972181184240044918[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6972181184240044918[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6972181184240044918[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6972181184240044918[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6972181184240044918[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6972181184240044918[62] = 0;
   out_6972181184240044918[63] = 0;
   out_6972181184240044918[64] = 0;
   out_6972181184240044918[65] = 0;
   out_6972181184240044918[66] = 0;
   out_6972181184240044918[67] = 0;
   out_6972181184240044918[68] = 0;
   out_6972181184240044918[69] = 0;
   out_6972181184240044918[70] = 1;
   out_6972181184240044918[71] = 0;
   out_6972181184240044918[72] = 0;
   out_6972181184240044918[73] = 0;
   out_6972181184240044918[74] = 0;
   out_6972181184240044918[75] = 0;
   out_6972181184240044918[76] = 0;
   out_6972181184240044918[77] = 0;
   out_6972181184240044918[78] = 0;
   out_6972181184240044918[79] = 0;
   out_6972181184240044918[80] = 1;
}
void h_25(double *state, double *unused, double *out_6429787098118084800) {
   out_6429787098118084800[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3171009832621012341) {
   out_3171009832621012341[0] = 0;
   out_3171009832621012341[1] = 0;
   out_3171009832621012341[2] = 0;
   out_3171009832621012341[3] = 0;
   out_3171009832621012341[4] = 0;
   out_3171009832621012341[5] = 0;
   out_3171009832621012341[6] = 1;
   out_3171009832621012341[7] = 0;
   out_3171009832621012341[8] = 0;
}
void h_24(double *state, double *unused, double *out_6701597119184761045) {
   out_6701597119184761045[0] = state[4];
   out_6701597119184761045[1] = state[5];
}
void H_24(double *state, double *unused, double *out_998360233615512775) {
   out_998360233615512775[0] = 0;
   out_998360233615512775[1] = 0;
   out_998360233615512775[2] = 0;
   out_998360233615512775[3] = 0;
   out_998360233615512775[4] = 1;
   out_998360233615512775[5] = 0;
   out_998360233615512775[6] = 0;
   out_998360233615512775[7] = 0;
   out_998360233615512775[8] = 0;
   out_998360233615512775[9] = 0;
   out_998360233615512775[10] = 0;
   out_998360233615512775[11] = 0;
   out_998360233615512775[12] = 0;
   out_998360233615512775[13] = 0;
   out_998360233615512775[14] = 1;
   out_998360233615512775[15] = 0;
   out_998360233615512775[16] = 0;
   out_998360233615512775[17] = 0;
}
void h_30(double *state, double *unused, double *out_5049641810910434322) {
   out_5049641810910434322[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8359043899596922520) {
   out_8359043899596922520[0] = 0;
   out_8359043899596922520[1] = 0;
   out_8359043899596922520[2] = 0;
   out_8359043899596922520[3] = 0;
   out_8359043899596922520[4] = 1;
   out_8359043899596922520[5] = 0;
   out_8359043899596922520[6] = 0;
   out_8359043899596922520[7] = 0;
   out_8359043899596922520[8] = 0;
}
void h_26(double *state, double *unused, double *out_1349399706503414824) {
   out_1349399706503414824[0] = state[7];
}
void H_26(double *state, double *unused, double *out_570493486253043883) {
   out_570493486253043883[0] = 0;
   out_570493486253043883[1] = 0;
   out_570493486253043883[2] = 0;
   out_570493486253043883[3] = 0;
   out_570493486253043883[4] = 0;
   out_570493486253043883[5] = 0;
   out_570493486253043883[6] = 0;
   out_570493486253043883[7] = 1;
   out_570493486253043883[8] = 0;
}
void h_27(double *state, double *unused, double *out_1467407100436791568) {
   out_1467407100436791568[0] = state[3];
}
void H_27(double *state, double *unused, double *out_866907573677347360) {
   out_866907573677347360[0] = 0;
   out_866907573677347360[1] = 0;
   out_866907573677347360[2] = 0;
   out_866907573677347360[3] = 1;
   out_866907573677347360[4] = 0;
   out_866907573677347360[5] = 0;
   out_866907573677347360[6] = 0;
   out_866907573677347360[7] = 0;
   out_866907573677347360[8] = 0;
}
void h_29(double *state, double *unused, double *out_5993151663812096757) {
   out_5993151663812096757[0] = state[1];
}
void H_29(double *state, double *unused, double *out_846455153192203673) {
   out_846455153192203673[0] = 0;
   out_846455153192203673[1] = 1;
   out_846455153192203673[2] = 0;
   out_846455153192203673[3] = 0;
   out_846455153192203673[4] = 0;
   out_846455153192203673[5] = 0;
   out_846455153192203673[6] = 0;
   out_846455153192203673[7] = 0;
   out_846455153192203673[8] = 0;
}
void h_28(double *state, double *unused, double *out_1136998220371906083) {
   out_1136998220371906083[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1117175118373122578) {
   out_1117175118373122578[0] = 1;
   out_1117175118373122578[1] = 0;
   out_1117175118373122578[2] = 0;
   out_1117175118373122578[3] = 0;
   out_1117175118373122578[4] = 0;
   out_1117175118373122578[5] = 0;
   out_1117175118373122578[6] = 0;
   out_1117175118373122578[7] = 0;
   out_1117175118373122578[8] = 0;
}
void h_31(double *state, double *unused, double *out_4228999089596618364) {
   out_4228999089596618364[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3201655794497972769) {
   out_3201655794497972769[0] = 0;
   out_3201655794497972769[1] = 0;
   out_3201655794497972769[2] = 0;
   out_3201655794497972769[3] = 0;
   out_3201655794497972769[4] = 0;
   out_3201655794497972769[5] = 0;
   out_3201655794497972769[6] = 0;
   out_3201655794497972769[7] = 0;
   out_3201655794497972769[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7839106046248465839) {
  err_fun(nom_x, delta_x, out_7839106046248465839);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_31659364612209693) {
  inv_err_fun(nom_x, true_x, out_31659364612209693);
}
void car_H_mod_fun(double *state, double *out_6082546015176302038) {
  H_mod_fun(state, out_6082546015176302038);
}
void car_f_fun(double *state, double dt, double *out_6850955649577617071) {
  f_fun(state,  dt, out_6850955649577617071);
}
void car_F_fun(double *state, double dt, double *out_6972181184240044918) {
  F_fun(state,  dt, out_6972181184240044918);
}
void car_h_25(double *state, double *unused, double *out_6429787098118084800) {
  h_25(state, unused, out_6429787098118084800);
}
void car_H_25(double *state, double *unused, double *out_3171009832621012341) {
  H_25(state, unused, out_3171009832621012341);
}
void car_h_24(double *state, double *unused, double *out_6701597119184761045) {
  h_24(state, unused, out_6701597119184761045);
}
void car_H_24(double *state, double *unused, double *out_998360233615512775) {
  H_24(state, unused, out_998360233615512775);
}
void car_h_30(double *state, double *unused, double *out_5049641810910434322) {
  h_30(state, unused, out_5049641810910434322);
}
void car_H_30(double *state, double *unused, double *out_8359043899596922520) {
  H_30(state, unused, out_8359043899596922520);
}
void car_h_26(double *state, double *unused, double *out_1349399706503414824) {
  h_26(state, unused, out_1349399706503414824);
}
void car_H_26(double *state, double *unused, double *out_570493486253043883) {
  H_26(state, unused, out_570493486253043883);
}
void car_h_27(double *state, double *unused, double *out_1467407100436791568) {
  h_27(state, unused, out_1467407100436791568);
}
void car_H_27(double *state, double *unused, double *out_866907573677347360) {
  H_27(state, unused, out_866907573677347360);
}
void car_h_29(double *state, double *unused, double *out_5993151663812096757) {
  h_29(state, unused, out_5993151663812096757);
}
void car_H_29(double *state, double *unused, double *out_846455153192203673) {
  H_29(state, unused, out_846455153192203673);
}
void car_h_28(double *state, double *unused, double *out_1136998220371906083) {
  h_28(state, unused, out_1136998220371906083);
}
void car_H_28(double *state, double *unused, double *out_1117175118373122578) {
  H_28(state, unused, out_1117175118373122578);
}
void car_h_31(double *state, double *unused, double *out_4228999089596618364) {
  h_31(state, unused, out_4228999089596618364);
}
void car_H_31(double *state, double *unused, double *out_3201655794497972769) {
  H_31(state, unused, out_3201655794497972769);
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
