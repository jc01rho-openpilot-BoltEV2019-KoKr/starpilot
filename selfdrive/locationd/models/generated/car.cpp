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
void err_fun(double *nom_x, double *delta_x, double *out_1626624007171975298) {
   out_1626624007171975298[0] = delta_x[0] + nom_x[0];
   out_1626624007171975298[1] = delta_x[1] + nom_x[1];
   out_1626624007171975298[2] = delta_x[2] + nom_x[2];
   out_1626624007171975298[3] = delta_x[3] + nom_x[3];
   out_1626624007171975298[4] = delta_x[4] + nom_x[4];
   out_1626624007171975298[5] = delta_x[5] + nom_x[5];
   out_1626624007171975298[6] = delta_x[6] + nom_x[6];
   out_1626624007171975298[7] = delta_x[7] + nom_x[7];
   out_1626624007171975298[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3841721694315715550) {
   out_3841721694315715550[0] = -nom_x[0] + true_x[0];
   out_3841721694315715550[1] = -nom_x[1] + true_x[1];
   out_3841721694315715550[2] = -nom_x[2] + true_x[2];
   out_3841721694315715550[3] = -nom_x[3] + true_x[3];
   out_3841721694315715550[4] = -nom_x[4] + true_x[4];
   out_3841721694315715550[5] = -nom_x[5] + true_x[5];
   out_3841721694315715550[6] = -nom_x[6] + true_x[6];
   out_3841721694315715550[7] = -nom_x[7] + true_x[7];
   out_3841721694315715550[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7646044064038577504) {
   out_7646044064038577504[0] = 1.0;
   out_7646044064038577504[1] = 0.0;
   out_7646044064038577504[2] = 0.0;
   out_7646044064038577504[3] = 0.0;
   out_7646044064038577504[4] = 0.0;
   out_7646044064038577504[5] = 0.0;
   out_7646044064038577504[6] = 0.0;
   out_7646044064038577504[7] = 0.0;
   out_7646044064038577504[8] = 0.0;
   out_7646044064038577504[9] = 0.0;
   out_7646044064038577504[10] = 1.0;
   out_7646044064038577504[11] = 0.0;
   out_7646044064038577504[12] = 0.0;
   out_7646044064038577504[13] = 0.0;
   out_7646044064038577504[14] = 0.0;
   out_7646044064038577504[15] = 0.0;
   out_7646044064038577504[16] = 0.0;
   out_7646044064038577504[17] = 0.0;
   out_7646044064038577504[18] = 0.0;
   out_7646044064038577504[19] = 0.0;
   out_7646044064038577504[20] = 1.0;
   out_7646044064038577504[21] = 0.0;
   out_7646044064038577504[22] = 0.0;
   out_7646044064038577504[23] = 0.0;
   out_7646044064038577504[24] = 0.0;
   out_7646044064038577504[25] = 0.0;
   out_7646044064038577504[26] = 0.0;
   out_7646044064038577504[27] = 0.0;
   out_7646044064038577504[28] = 0.0;
   out_7646044064038577504[29] = 0.0;
   out_7646044064038577504[30] = 1.0;
   out_7646044064038577504[31] = 0.0;
   out_7646044064038577504[32] = 0.0;
   out_7646044064038577504[33] = 0.0;
   out_7646044064038577504[34] = 0.0;
   out_7646044064038577504[35] = 0.0;
   out_7646044064038577504[36] = 0.0;
   out_7646044064038577504[37] = 0.0;
   out_7646044064038577504[38] = 0.0;
   out_7646044064038577504[39] = 0.0;
   out_7646044064038577504[40] = 1.0;
   out_7646044064038577504[41] = 0.0;
   out_7646044064038577504[42] = 0.0;
   out_7646044064038577504[43] = 0.0;
   out_7646044064038577504[44] = 0.0;
   out_7646044064038577504[45] = 0.0;
   out_7646044064038577504[46] = 0.0;
   out_7646044064038577504[47] = 0.0;
   out_7646044064038577504[48] = 0.0;
   out_7646044064038577504[49] = 0.0;
   out_7646044064038577504[50] = 1.0;
   out_7646044064038577504[51] = 0.0;
   out_7646044064038577504[52] = 0.0;
   out_7646044064038577504[53] = 0.0;
   out_7646044064038577504[54] = 0.0;
   out_7646044064038577504[55] = 0.0;
   out_7646044064038577504[56] = 0.0;
   out_7646044064038577504[57] = 0.0;
   out_7646044064038577504[58] = 0.0;
   out_7646044064038577504[59] = 0.0;
   out_7646044064038577504[60] = 1.0;
   out_7646044064038577504[61] = 0.0;
   out_7646044064038577504[62] = 0.0;
   out_7646044064038577504[63] = 0.0;
   out_7646044064038577504[64] = 0.0;
   out_7646044064038577504[65] = 0.0;
   out_7646044064038577504[66] = 0.0;
   out_7646044064038577504[67] = 0.0;
   out_7646044064038577504[68] = 0.0;
   out_7646044064038577504[69] = 0.0;
   out_7646044064038577504[70] = 1.0;
   out_7646044064038577504[71] = 0.0;
   out_7646044064038577504[72] = 0.0;
   out_7646044064038577504[73] = 0.0;
   out_7646044064038577504[74] = 0.0;
   out_7646044064038577504[75] = 0.0;
   out_7646044064038577504[76] = 0.0;
   out_7646044064038577504[77] = 0.0;
   out_7646044064038577504[78] = 0.0;
   out_7646044064038577504[79] = 0.0;
   out_7646044064038577504[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3692802059814366209) {
   out_3692802059814366209[0] = state[0];
   out_3692802059814366209[1] = state[1];
   out_3692802059814366209[2] = state[2];
   out_3692802059814366209[3] = state[3];
   out_3692802059814366209[4] = state[4];
   out_3692802059814366209[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3692802059814366209[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3692802059814366209[7] = state[7];
   out_3692802059814366209[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6278869713612932388) {
   out_6278869713612932388[0] = 1;
   out_6278869713612932388[1] = 0;
   out_6278869713612932388[2] = 0;
   out_6278869713612932388[3] = 0;
   out_6278869713612932388[4] = 0;
   out_6278869713612932388[5] = 0;
   out_6278869713612932388[6] = 0;
   out_6278869713612932388[7] = 0;
   out_6278869713612932388[8] = 0;
   out_6278869713612932388[9] = 0;
   out_6278869713612932388[10] = 1;
   out_6278869713612932388[11] = 0;
   out_6278869713612932388[12] = 0;
   out_6278869713612932388[13] = 0;
   out_6278869713612932388[14] = 0;
   out_6278869713612932388[15] = 0;
   out_6278869713612932388[16] = 0;
   out_6278869713612932388[17] = 0;
   out_6278869713612932388[18] = 0;
   out_6278869713612932388[19] = 0;
   out_6278869713612932388[20] = 1;
   out_6278869713612932388[21] = 0;
   out_6278869713612932388[22] = 0;
   out_6278869713612932388[23] = 0;
   out_6278869713612932388[24] = 0;
   out_6278869713612932388[25] = 0;
   out_6278869713612932388[26] = 0;
   out_6278869713612932388[27] = 0;
   out_6278869713612932388[28] = 0;
   out_6278869713612932388[29] = 0;
   out_6278869713612932388[30] = 1;
   out_6278869713612932388[31] = 0;
   out_6278869713612932388[32] = 0;
   out_6278869713612932388[33] = 0;
   out_6278869713612932388[34] = 0;
   out_6278869713612932388[35] = 0;
   out_6278869713612932388[36] = 0;
   out_6278869713612932388[37] = 0;
   out_6278869713612932388[38] = 0;
   out_6278869713612932388[39] = 0;
   out_6278869713612932388[40] = 1;
   out_6278869713612932388[41] = 0;
   out_6278869713612932388[42] = 0;
   out_6278869713612932388[43] = 0;
   out_6278869713612932388[44] = 0;
   out_6278869713612932388[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6278869713612932388[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6278869713612932388[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6278869713612932388[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6278869713612932388[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6278869713612932388[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6278869713612932388[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6278869713612932388[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6278869713612932388[53] = -9.8100000000000005*dt;
   out_6278869713612932388[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6278869713612932388[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6278869713612932388[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6278869713612932388[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6278869713612932388[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6278869713612932388[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6278869713612932388[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6278869713612932388[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6278869713612932388[62] = 0;
   out_6278869713612932388[63] = 0;
   out_6278869713612932388[64] = 0;
   out_6278869713612932388[65] = 0;
   out_6278869713612932388[66] = 0;
   out_6278869713612932388[67] = 0;
   out_6278869713612932388[68] = 0;
   out_6278869713612932388[69] = 0;
   out_6278869713612932388[70] = 1;
   out_6278869713612932388[71] = 0;
   out_6278869713612932388[72] = 0;
   out_6278869713612932388[73] = 0;
   out_6278869713612932388[74] = 0;
   out_6278869713612932388[75] = 0;
   out_6278869713612932388[76] = 0;
   out_6278869713612932388[77] = 0;
   out_6278869713612932388[78] = 0;
   out_6278869713612932388[79] = 0;
   out_6278869713612932388[80] = 1;
}
void h_25(double *state, double *unused, double *out_1903293770744417105) {
   out_1903293770744417105[0] = state[6];
}
void H_25(double *state, double *unused, double *out_1607511783758736875) {
   out_1607511783758736875[0] = 0;
   out_1607511783758736875[1] = 0;
   out_1607511783758736875[2] = 0;
   out_1607511783758736875[3] = 0;
   out_1607511783758736875[4] = 0;
   out_1607511783758736875[5] = 0;
   out_1607511783758736875[6] = 1;
   out_1607511783758736875[7] = 0;
   out_1607511783758736875[8] = 0;
}
void h_24(double *state, double *unused, double *out_3019943109680816786) {
   out_3019943109680816786[0] = state[4];
   out_3019943109680816786[1] = state[5];
}
void H_24(double *state, double *unused, double *out_565137815246762691) {
   out_565137815246762691[0] = 0;
   out_565137815246762691[1] = 0;
   out_565137815246762691[2] = 0;
   out_565137815246762691[3] = 0;
   out_565137815246762691[4] = 1;
   out_565137815246762691[5] = 0;
   out_565137815246762691[6] = 0;
   out_565137815246762691[7] = 0;
   out_565137815246762691[8] = 0;
   out_565137815246762691[9] = 0;
   out_565137815246762691[10] = 0;
   out_565137815246762691[11] = 0;
   out_565137815246762691[12] = 0;
   out_565137815246762691[13] = 0;
   out_565137815246762691[14] = 1;
   out_565137815246762691[15] = 0;
   out_565137815246762691[16] = 0;
   out_565137815246762691[17] = 0;
}
void h_30(double *state, double *unused, double *out_5540743298998439455) {
   out_5540743298998439455[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4125844742265985502) {
   out_4125844742265985502[0] = 0;
   out_4125844742265985502[1] = 0;
   out_4125844742265985502[2] = 0;
   out_4125844742265985502[3] = 0;
   out_4125844742265985502[4] = 1;
   out_4125844742265985502[5] = 0;
   out_4125844742265985502[6] = 0;
   out_4125844742265985502[7] = 0;
   out_4125844742265985502[8] = 0;
}
void h_26(double *state, double *unused, double *out_539070031337593810) {
   out_539070031337593810[0] = state[7];
}
void H_26(double *state, double *unused, double *out_2133991535115319349) {
   out_2133991535115319349[0] = 0;
   out_2133991535115319349[1] = 0;
   out_2133991535115319349[2] = 0;
   out_2133991535115319349[3] = 0;
   out_2133991535115319349[4] = 0;
   out_2133991535115319349[5] = 0;
   out_2133991535115319349[6] = 0;
   out_2133991535115319349[7] = 1;
   out_2133991535115319349[8] = 0;
}
void h_27(double *state, double *unused, double *out_7078675401262423660) {
   out_7078675401262423660[0] = state[3];
}
void H_27(double *state, double *unused, double *out_1951081430465560591) {
   out_1951081430465560591[0] = 0;
   out_1951081430465560591[1] = 0;
   out_1951081430465560591[2] = 0;
   out_1951081430465560591[3] = 1;
   out_1951081430465560591[4] = 0;
   out_1951081430465560591[5] = 0;
   out_1951081430465560591[6] = 0;
   out_1951081430465560591[7] = 0;
   out_1951081430465560591[8] = 0;
}
void h_29(double *state, double *unused, double *out_4597233446096777020) {
   out_4597233446096777020[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4636076086580377686) {
   out_4636076086580377686[0] = 0;
   out_4636076086580377686[1] = 1;
   out_4636076086580377686[2] = 0;
   out_4636076086580377686[3] = 0;
   out_4636076086580377686[4] = 0;
   out_4636076086580377686[5] = 0;
   out_4636076086580377686[6] = 0;
   out_4636076086580377686[7] = 0;
   out_4636076086580377686[8] = 0;
}
void h_28(double *state, double *unused, double *out_2077002133601578015) {
   out_2077002133601578015[0] = state[0];
}
void H_28(double *state, double *unused, double *out_446322930489152888) {
   out_446322930489152888[0] = 1;
   out_446322930489152888[1] = 0;
   out_446322930489152888[2] = 0;
   out_446322930489152888[3] = 0;
   out_446322930489152888[4] = 0;
   out_446322930489152888[5] = 0;
   out_446322930489152888[6] = 0;
   out_446322930489152888[7] = 0;
   out_446322930489152888[8] = 0;
}
void h_31(double *state, double *unused, double *out_7817026797415165478) {
   out_7817026797415165478[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2760199637348670825) {
   out_2760199637348670825[0] = 0;
   out_2760199637348670825[1] = 0;
   out_2760199637348670825[2] = 0;
   out_2760199637348670825[3] = 0;
   out_2760199637348670825[4] = 0;
   out_2760199637348670825[5] = 0;
   out_2760199637348670825[6] = 0;
   out_2760199637348670825[7] = 0;
   out_2760199637348670825[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_1626624007171975298) {
  err_fun(nom_x, delta_x, out_1626624007171975298);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3841721694315715550) {
  inv_err_fun(nom_x, true_x, out_3841721694315715550);
}
void car_H_mod_fun(double *state, double *out_7646044064038577504) {
  H_mod_fun(state, out_7646044064038577504);
}
void car_f_fun(double *state, double dt, double *out_3692802059814366209) {
  f_fun(state,  dt, out_3692802059814366209);
}
void car_F_fun(double *state, double dt, double *out_6278869713612932388) {
  F_fun(state,  dt, out_6278869713612932388);
}
void car_h_25(double *state, double *unused, double *out_1903293770744417105) {
  h_25(state, unused, out_1903293770744417105);
}
void car_H_25(double *state, double *unused, double *out_1607511783758736875) {
  H_25(state, unused, out_1607511783758736875);
}
void car_h_24(double *state, double *unused, double *out_3019943109680816786) {
  h_24(state, unused, out_3019943109680816786);
}
void car_H_24(double *state, double *unused, double *out_565137815246762691) {
  H_24(state, unused, out_565137815246762691);
}
void car_h_30(double *state, double *unused, double *out_5540743298998439455) {
  h_30(state, unused, out_5540743298998439455);
}
void car_H_30(double *state, double *unused, double *out_4125844742265985502) {
  H_30(state, unused, out_4125844742265985502);
}
void car_h_26(double *state, double *unused, double *out_539070031337593810) {
  h_26(state, unused, out_539070031337593810);
}
void car_H_26(double *state, double *unused, double *out_2133991535115319349) {
  H_26(state, unused, out_2133991535115319349);
}
void car_h_27(double *state, double *unused, double *out_7078675401262423660) {
  h_27(state, unused, out_7078675401262423660);
}
void car_H_27(double *state, double *unused, double *out_1951081430465560591) {
  H_27(state, unused, out_1951081430465560591);
}
void car_h_29(double *state, double *unused, double *out_4597233446096777020) {
  h_29(state, unused, out_4597233446096777020);
}
void car_H_29(double *state, double *unused, double *out_4636076086580377686) {
  H_29(state, unused, out_4636076086580377686);
}
void car_h_28(double *state, double *unused, double *out_2077002133601578015) {
  h_28(state, unused, out_2077002133601578015);
}
void car_H_28(double *state, double *unused, double *out_446322930489152888) {
  H_28(state, unused, out_446322930489152888);
}
void car_h_31(double *state, double *unused, double *out_7817026797415165478) {
  h_31(state, unused, out_7817026797415165478);
}
void car_H_31(double *state, double *unused, double *out_2760199637348670825) {
  H_31(state, unused, out_2760199637348670825);
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
