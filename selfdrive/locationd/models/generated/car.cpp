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
void err_fun(double *nom_x, double *delta_x, double *out_8341138954345272666) {
   out_8341138954345272666[0] = delta_x[0] + nom_x[0];
   out_8341138954345272666[1] = delta_x[1] + nom_x[1];
   out_8341138954345272666[2] = delta_x[2] + nom_x[2];
   out_8341138954345272666[3] = delta_x[3] + nom_x[3];
   out_8341138954345272666[4] = delta_x[4] + nom_x[4];
   out_8341138954345272666[5] = delta_x[5] + nom_x[5];
   out_8341138954345272666[6] = delta_x[6] + nom_x[6];
   out_8341138954345272666[7] = delta_x[7] + nom_x[7];
   out_8341138954345272666[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1053229851557441146) {
   out_1053229851557441146[0] = -nom_x[0] + true_x[0];
   out_1053229851557441146[1] = -nom_x[1] + true_x[1];
   out_1053229851557441146[2] = -nom_x[2] + true_x[2];
   out_1053229851557441146[3] = -nom_x[3] + true_x[3];
   out_1053229851557441146[4] = -nom_x[4] + true_x[4];
   out_1053229851557441146[5] = -nom_x[5] + true_x[5];
   out_1053229851557441146[6] = -nom_x[6] + true_x[6];
   out_1053229851557441146[7] = -nom_x[7] + true_x[7];
   out_1053229851557441146[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1742832659992124751) {
   out_1742832659992124751[0] = 1.0;
   out_1742832659992124751[1] = 0.0;
   out_1742832659992124751[2] = 0.0;
   out_1742832659992124751[3] = 0.0;
   out_1742832659992124751[4] = 0.0;
   out_1742832659992124751[5] = 0.0;
   out_1742832659992124751[6] = 0.0;
   out_1742832659992124751[7] = 0.0;
   out_1742832659992124751[8] = 0.0;
   out_1742832659992124751[9] = 0.0;
   out_1742832659992124751[10] = 1.0;
   out_1742832659992124751[11] = 0.0;
   out_1742832659992124751[12] = 0.0;
   out_1742832659992124751[13] = 0.0;
   out_1742832659992124751[14] = 0.0;
   out_1742832659992124751[15] = 0.0;
   out_1742832659992124751[16] = 0.0;
   out_1742832659992124751[17] = 0.0;
   out_1742832659992124751[18] = 0.0;
   out_1742832659992124751[19] = 0.0;
   out_1742832659992124751[20] = 1.0;
   out_1742832659992124751[21] = 0.0;
   out_1742832659992124751[22] = 0.0;
   out_1742832659992124751[23] = 0.0;
   out_1742832659992124751[24] = 0.0;
   out_1742832659992124751[25] = 0.0;
   out_1742832659992124751[26] = 0.0;
   out_1742832659992124751[27] = 0.0;
   out_1742832659992124751[28] = 0.0;
   out_1742832659992124751[29] = 0.0;
   out_1742832659992124751[30] = 1.0;
   out_1742832659992124751[31] = 0.0;
   out_1742832659992124751[32] = 0.0;
   out_1742832659992124751[33] = 0.0;
   out_1742832659992124751[34] = 0.0;
   out_1742832659992124751[35] = 0.0;
   out_1742832659992124751[36] = 0.0;
   out_1742832659992124751[37] = 0.0;
   out_1742832659992124751[38] = 0.0;
   out_1742832659992124751[39] = 0.0;
   out_1742832659992124751[40] = 1.0;
   out_1742832659992124751[41] = 0.0;
   out_1742832659992124751[42] = 0.0;
   out_1742832659992124751[43] = 0.0;
   out_1742832659992124751[44] = 0.0;
   out_1742832659992124751[45] = 0.0;
   out_1742832659992124751[46] = 0.0;
   out_1742832659992124751[47] = 0.0;
   out_1742832659992124751[48] = 0.0;
   out_1742832659992124751[49] = 0.0;
   out_1742832659992124751[50] = 1.0;
   out_1742832659992124751[51] = 0.0;
   out_1742832659992124751[52] = 0.0;
   out_1742832659992124751[53] = 0.0;
   out_1742832659992124751[54] = 0.0;
   out_1742832659992124751[55] = 0.0;
   out_1742832659992124751[56] = 0.0;
   out_1742832659992124751[57] = 0.0;
   out_1742832659992124751[58] = 0.0;
   out_1742832659992124751[59] = 0.0;
   out_1742832659992124751[60] = 1.0;
   out_1742832659992124751[61] = 0.0;
   out_1742832659992124751[62] = 0.0;
   out_1742832659992124751[63] = 0.0;
   out_1742832659992124751[64] = 0.0;
   out_1742832659992124751[65] = 0.0;
   out_1742832659992124751[66] = 0.0;
   out_1742832659992124751[67] = 0.0;
   out_1742832659992124751[68] = 0.0;
   out_1742832659992124751[69] = 0.0;
   out_1742832659992124751[70] = 1.0;
   out_1742832659992124751[71] = 0.0;
   out_1742832659992124751[72] = 0.0;
   out_1742832659992124751[73] = 0.0;
   out_1742832659992124751[74] = 0.0;
   out_1742832659992124751[75] = 0.0;
   out_1742832659992124751[76] = 0.0;
   out_1742832659992124751[77] = 0.0;
   out_1742832659992124751[78] = 0.0;
   out_1742832659992124751[79] = 0.0;
   out_1742832659992124751[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_418888185766452101) {
   out_418888185766452101[0] = state[0];
   out_418888185766452101[1] = state[1];
   out_418888185766452101[2] = state[2];
   out_418888185766452101[3] = state[3];
   out_418888185766452101[4] = state[4];
   out_418888185766452101[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_418888185766452101[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_418888185766452101[7] = state[7];
   out_418888185766452101[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7332131154779998147) {
   out_7332131154779998147[0] = 1;
   out_7332131154779998147[1] = 0;
   out_7332131154779998147[2] = 0;
   out_7332131154779998147[3] = 0;
   out_7332131154779998147[4] = 0;
   out_7332131154779998147[5] = 0;
   out_7332131154779998147[6] = 0;
   out_7332131154779998147[7] = 0;
   out_7332131154779998147[8] = 0;
   out_7332131154779998147[9] = 0;
   out_7332131154779998147[10] = 1;
   out_7332131154779998147[11] = 0;
   out_7332131154779998147[12] = 0;
   out_7332131154779998147[13] = 0;
   out_7332131154779998147[14] = 0;
   out_7332131154779998147[15] = 0;
   out_7332131154779998147[16] = 0;
   out_7332131154779998147[17] = 0;
   out_7332131154779998147[18] = 0;
   out_7332131154779998147[19] = 0;
   out_7332131154779998147[20] = 1;
   out_7332131154779998147[21] = 0;
   out_7332131154779998147[22] = 0;
   out_7332131154779998147[23] = 0;
   out_7332131154779998147[24] = 0;
   out_7332131154779998147[25] = 0;
   out_7332131154779998147[26] = 0;
   out_7332131154779998147[27] = 0;
   out_7332131154779998147[28] = 0;
   out_7332131154779998147[29] = 0;
   out_7332131154779998147[30] = 1;
   out_7332131154779998147[31] = 0;
   out_7332131154779998147[32] = 0;
   out_7332131154779998147[33] = 0;
   out_7332131154779998147[34] = 0;
   out_7332131154779998147[35] = 0;
   out_7332131154779998147[36] = 0;
   out_7332131154779998147[37] = 0;
   out_7332131154779998147[38] = 0;
   out_7332131154779998147[39] = 0;
   out_7332131154779998147[40] = 1;
   out_7332131154779998147[41] = 0;
   out_7332131154779998147[42] = 0;
   out_7332131154779998147[43] = 0;
   out_7332131154779998147[44] = 0;
   out_7332131154779998147[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7332131154779998147[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7332131154779998147[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7332131154779998147[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7332131154779998147[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7332131154779998147[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7332131154779998147[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7332131154779998147[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7332131154779998147[53] = -9.8100000000000005*dt;
   out_7332131154779998147[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7332131154779998147[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7332131154779998147[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7332131154779998147[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7332131154779998147[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7332131154779998147[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7332131154779998147[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7332131154779998147[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7332131154779998147[62] = 0;
   out_7332131154779998147[63] = 0;
   out_7332131154779998147[64] = 0;
   out_7332131154779998147[65] = 0;
   out_7332131154779998147[66] = 0;
   out_7332131154779998147[67] = 0;
   out_7332131154779998147[68] = 0;
   out_7332131154779998147[69] = 0;
   out_7332131154779998147[70] = 1;
   out_7332131154779998147[71] = 0;
   out_7332131154779998147[72] = 0;
   out_7332131154779998147[73] = 0;
   out_7332131154779998147[74] = 0;
   out_7332131154779998147[75] = 0;
   out_7332131154779998147[76] = 0;
   out_7332131154779998147[77] = 0;
   out_7332131154779998147[78] = 0;
   out_7332131154779998147[79] = 0;
   out_7332131154779998147[80] = 1;
}
void h_25(double *state, double *unused, double *out_2120117969057149735) {
   out_2120117969057149735[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6108633137067025220) {
   out_6108633137067025220[0] = 0;
   out_6108633137067025220[1] = 0;
   out_6108633137067025220[2] = 0;
   out_6108633137067025220[3] = 0;
   out_6108633137067025220[4] = 0;
   out_6108633137067025220[5] = 0;
   out_6108633137067025220[6] = 1;
   out_6108633137067025220[7] = 0;
   out_6108633137067025220[8] = 0;
}
void h_24(double *state, double *unused, double *out_7094254727358861625) {
   out_7094254727358861625[0] = state[4];
   out_7094254727358861625[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8334340921045893782) {
   out_8334340921045893782[0] = 0;
   out_8334340921045893782[1] = 0;
   out_8334340921045893782[2] = 0;
   out_8334340921045893782[3] = 0;
   out_8334340921045893782[4] = 1;
   out_8334340921045893782[5] = 0;
   out_8334340921045893782[6] = 0;
   out_8334340921045893782[7] = 0;
   out_8334340921045893782[8] = 0;
   out_8334340921045893782[9] = 0;
   out_8334340921045893782[10] = 0;
   out_8334340921045893782[11] = 0;
   out_8334340921045893782[12] = 0;
   out_8334340921045893782[13] = 0;
   out_8334340921045893782[14] = 1;
   out_8334340921045893782[15] = 0;
   out_8334340921045893782[16] = 0;
   out_8334340921045893782[17] = 0;
}
void h_30(double *state, double *unused, double *out_4035329226783510394) {
   out_4035329226783510394[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5421420595150909641) {
   out_5421420595150909641[0] = 0;
   out_5421420595150909641[1] = 0;
   out_5421420595150909641[2] = 0;
   out_5421420595150909641[3] = 0;
   out_5421420595150909641[4] = 1;
   out_5421420595150909641[5] = 0;
   out_5421420595150909641[6] = 0;
   out_5421420595150909641[7] = 0;
   out_5421420595150909641[8] = 0;
}
void h_26(double *state, double *unused, double *out_3432013342107032877) {
   out_3432013342107032877[0] = state[7];
}
void H_26(double *state, double *unused, double *out_2367129818192968996) {
   out_2367129818192968996[0] = 0;
   out_2367129818192968996[1] = 0;
   out_2367129818192968996[2] = 0;
   out_2367129818192968996[3] = 0;
   out_2367129818192968996[4] = 0;
   out_2367129818192968996[5] = 0;
   out_2367129818192968996[6] = 0;
   out_2367129818192968996[7] = 1;
   out_2367129818192968996[8] = 0;
}
void h_27(double *state, double *unused, double *out_4789453276872201226) {
   out_4789453276872201226[0] = state[3];
}
void H_27(double *state, double *unused, double *out_7596183906951334552) {
   out_7596183906951334552[0] = 0;
   out_7596183906951334552[1] = 0;
   out_7596183906951334552[2] = 0;
   out_7596183906951334552[3] = 1;
   out_7596183906951334552[4] = 0;
   out_7596183906951334552[5] = 0;
   out_7596183906951334552[6] = 0;
   out_7596183906951334552[7] = 0;
   out_7596183906951334552[8] = 0;
}
void h_29(double *state, double *unused, double *out_8533129359367326134) {
   out_8533129359367326134[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4911189250836517457) {
   out_4911189250836517457[0] = 0;
   out_4911189250836517457[1] = 1;
   out_4911189250836517457[2] = 0;
   out_4911189250836517457[3] = 0;
   out_4911189250836517457[4] = 0;
   out_4911189250836517457[5] = 0;
   out_4911189250836517457[6] = 0;
   out_4911189250836517457[7] = 0;
   out_4911189250836517457[8] = 0;
}
void h_28(double *state, double *unused, double *out_212219990788644419) {
   out_212219990788644419[0] = state[0];
}
void H_28(double *state, double *unused, double *out_4054798422819135457) {
   out_4054798422819135457[0] = 1;
   out_4054798422819135457[1] = 0;
   out_4054798422819135457[2] = 0;
   out_4054798422819135457[3] = 0;
   out_4054798422819135457[4] = 0;
   out_4054798422819135457[5] = 0;
   out_4054798422819135457[6] = 0;
   out_4054798422819135457[7] = 0;
   out_4054798422819135457[8] = 0;
}
void h_31(double *state, double *unused, double *out_6046731432492005227) {
   out_6046731432492005227[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6139279098943985648) {
   out_6139279098943985648[0] = 0;
   out_6139279098943985648[1] = 0;
   out_6139279098943985648[2] = 0;
   out_6139279098943985648[3] = 0;
   out_6139279098943985648[4] = 0;
   out_6139279098943985648[5] = 0;
   out_6139279098943985648[6] = 0;
   out_6139279098943985648[7] = 0;
   out_6139279098943985648[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_8341138954345272666) {
  err_fun(nom_x, delta_x, out_8341138954345272666);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1053229851557441146) {
  inv_err_fun(nom_x, true_x, out_1053229851557441146);
}
void car_H_mod_fun(double *state, double *out_1742832659992124751) {
  H_mod_fun(state, out_1742832659992124751);
}
void car_f_fun(double *state, double dt, double *out_418888185766452101) {
  f_fun(state,  dt, out_418888185766452101);
}
void car_F_fun(double *state, double dt, double *out_7332131154779998147) {
  F_fun(state,  dt, out_7332131154779998147);
}
void car_h_25(double *state, double *unused, double *out_2120117969057149735) {
  h_25(state, unused, out_2120117969057149735);
}
void car_H_25(double *state, double *unused, double *out_6108633137067025220) {
  H_25(state, unused, out_6108633137067025220);
}
void car_h_24(double *state, double *unused, double *out_7094254727358861625) {
  h_24(state, unused, out_7094254727358861625);
}
void car_H_24(double *state, double *unused, double *out_8334340921045893782) {
  H_24(state, unused, out_8334340921045893782);
}
void car_h_30(double *state, double *unused, double *out_4035329226783510394) {
  h_30(state, unused, out_4035329226783510394);
}
void car_H_30(double *state, double *unused, double *out_5421420595150909641) {
  H_30(state, unused, out_5421420595150909641);
}
void car_h_26(double *state, double *unused, double *out_3432013342107032877) {
  h_26(state, unused, out_3432013342107032877);
}
void car_H_26(double *state, double *unused, double *out_2367129818192968996) {
  H_26(state, unused, out_2367129818192968996);
}
void car_h_27(double *state, double *unused, double *out_4789453276872201226) {
  h_27(state, unused, out_4789453276872201226);
}
void car_H_27(double *state, double *unused, double *out_7596183906951334552) {
  H_27(state, unused, out_7596183906951334552);
}
void car_h_29(double *state, double *unused, double *out_8533129359367326134) {
  h_29(state, unused, out_8533129359367326134);
}
void car_H_29(double *state, double *unused, double *out_4911189250836517457) {
  H_29(state, unused, out_4911189250836517457);
}
void car_h_28(double *state, double *unused, double *out_212219990788644419) {
  h_28(state, unused, out_212219990788644419);
}
void car_H_28(double *state, double *unused, double *out_4054798422819135457) {
  H_28(state, unused, out_4054798422819135457);
}
void car_h_31(double *state, double *unused, double *out_6046731432492005227) {
  h_31(state, unused, out_6046731432492005227);
}
void car_H_31(double *state, double *unused, double *out_6139279098943985648) {
  H_31(state, unused, out_6139279098943985648);
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
