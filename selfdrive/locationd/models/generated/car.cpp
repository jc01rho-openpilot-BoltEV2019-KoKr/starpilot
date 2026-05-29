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
void err_fun(double *nom_x, double *delta_x, double *out_4317163891516196670) {
   out_4317163891516196670[0] = delta_x[0] + nom_x[0];
   out_4317163891516196670[1] = delta_x[1] + nom_x[1];
   out_4317163891516196670[2] = delta_x[2] + nom_x[2];
   out_4317163891516196670[3] = delta_x[3] + nom_x[3];
   out_4317163891516196670[4] = delta_x[4] + nom_x[4];
   out_4317163891516196670[5] = delta_x[5] + nom_x[5];
   out_4317163891516196670[6] = delta_x[6] + nom_x[6];
   out_4317163891516196670[7] = delta_x[7] + nom_x[7];
   out_4317163891516196670[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8278424519720112087) {
   out_8278424519720112087[0] = -nom_x[0] + true_x[0];
   out_8278424519720112087[1] = -nom_x[1] + true_x[1];
   out_8278424519720112087[2] = -nom_x[2] + true_x[2];
   out_8278424519720112087[3] = -nom_x[3] + true_x[3];
   out_8278424519720112087[4] = -nom_x[4] + true_x[4];
   out_8278424519720112087[5] = -nom_x[5] + true_x[5];
   out_8278424519720112087[6] = -nom_x[6] + true_x[6];
   out_8278424519720112087[7] = -nom_x[7] + true_x[7];
   out_8278424519720112087[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_319627375497114494) {
   out_319627375497114494[0] = 1.0;
   out_319627375497114494[1] = 0.0;
   out_319627375497114494[2] = 0.0;
   out_319627375497114494[3] = 0.0;
   out_319627375497114494[4] = 0.0;
   out_319627375497114494[5] = 0.0;
   out_319627375497114494[6] = 0.0;
   out_319627375497114494[7] = 0.0;
   out_319627375497114494[8] = 0.0;
   out_319627375497114494[9] = 0.0;
   out_319627375497114494[10] = 1.0;
   out_319627375497114494[11] = 0.0;
   out_319627375497114494[12] = 0.0;
   out_319627375497114494[13] = 0.0;
   out_319627375497114494[14] = 0.0;
   out_319627375497114494[15] = 0.0;
   out_319627375497114494[16] = 0.0;
   out_319627375497114494[17] = 0.0;
   out_319627375497114494[18] = 0.0;
   out_319627375497114494[19] = 0.0;
   out_319627375497114494[20] = 1.0;
   out_319627375497114494[21] = 0.0;
   out_319627375497114494[22] = 0.0;
   out_319627375497114494[23] = 0.0;
   out_319627375497114494[24] = 0.0;
   out_319627375497114494[25] = 0.0;
   out_319627375497114494[26] = 0.0;
   out_319627375497114494[27] = 0.0;
   out_319627375497114494[28] = 0.0;
   out_319627375497114494[29] = 0.0;
   out_319627375497114494[30] = 1.0;
   out_319627375497114494[31] = 0.0;
   out_319627375497114494[32] = 0.0;
   out_319627375497114494[33] = 0.0;
   out_319627375497114494[34] = 0.0;
   out_319627375497114494[35] = 0.0;
   out_319627375497114494[36] = 0.0;
   out_319627375497114494[37] = 0.0;
   out_319627375497114494[38] = 0.0;
   out_319627375497114494[39] = 0.0;
   out_319627375497114494[40] = 1.0;
   out_319627375497114494[41] = 0.0;
   out_319627375497114494[42] = 0.0;
   out_319627375497114494[43] = 0.0;
   out_319627375497114494[44] = 0.0;
   out_319627375497114494[45] = 0.0;
   out_319627375497114494[46] = 0.0;
   out_319627375497114494[47] = 0.0;
   out_319627375497114494[48] = 0.0;
   out_319627375497114494[49] = 0.0;
   out_319627375497114494[50] = 1.0;
   out_319627375497114494[51] = 0.0;
   out_319627375497114494[52] = 0.0;
   out_319627375497114494[53] = 0.0;
   out_319627375497114494[54] = 0.0;
   out_319627375497114494[55] = 0.0;
   out_319627375497114494[56] = 0.0;
   out_319627375497114494[57] = 0.0;
   out_319627375497114494[58] = 0.0;
   out_319627375497114494[59] = 0.0;
   out_319627375497114494[60] = 1.0;
   out_319627375497114494[61] = 0.0;
   out_319627375497114494[62] = 0.0;
   out_319627375497114494[63] = 0.0;
   out_319627375497114494[64] = 0.0;
   out_319627375497114494[65] = 0.0;
   out_319627375497114494[66] = 0.0;
   out_319627375497114494[67] = 0.0;
   out_319627375497114494[68] = 0.0;
   out_319627375497114494[69] = 0.0;
   out_319627375497114494[70] = 1.0;
   out_319627375497114494[71] = 0.0;
   out_319627375497114494[72] = 0.0;
   out_319627375497114494[73] = 0.0;
   out_319627375497114494[74] = 0.0;
   out_319627375497114494[75] = 0.0;
   out_319627375497114494[76] = 0.0;
   out_319627375497114494[77] = 0.0;
   out_319627375497114494[78] = 0.0;
   out_319627375497114494[79] = 0.0;
   out_319627375497114494[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6613977481805234540) {
   out_6613977481805234540[0] = state[0];
   out_6613977481805234540[1] = state[1];
   out_6613977481805234540[2] = state[2];
   out_6613977481805234540[3] = state[3];
   out_6613977481805234540[4] = state[4];
   out_6613977481805234540[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6613977481805234540[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6613977481805234540[7] = state[7];
   out_6613977481805234540[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3393066705725541618) {
   out_3393066705725541618[0] = 1;
   out_3393066705725541618[1] = 0;
   out_3393066705725541618[2] = 0;
   out_3393066705725541618[3] = 0;
   out_3393066705725541618[4] = 0;
   out_3393066705725541618[5] = 0;
   out_3393066705725541618[6] = 0;
   out_3393066705725541618[7] = 0;
   out_3393066705725541618[8] = 0;
   out_3393066705725541618[9] = 0;
   out_3393066705725541618[10] = 1;
   out_3393066705725541618[11] = 0;
   out_3393066705725541618[12] = 0;
   out_3393066705725541618[13] = 0;
   out_3393066705725541618[14] = 0;
   out_3393066705725541618[15] = 0;
   out_3393066705725541618[16] = 0;
   out_3393066705725541618[17] = 0;
   out_3393066705725541618[18] = 0;
   out_3393066705725541618[19] = 0;
   out_3393066705725541618[20] = 1;
   out_3393066705725541618[21] = 0;
   out_3393066705725541618[22] = 0;
   out_3393066705725541618[23] = 0;
   out_3393066705725541618[24] = 0;
   out_3393066705725541618[25] = 0;
   out_3393066705725541618[26] = 0;
   out_3393066705725541618[27] = 0;
   out_3393066705725541618[28] = 0;
   out_3393066705725541618[29] = 0;
   out_3393066705725541618[30] = 1;
   out_3393066705725541618[31] = 0;
   out_3393066705725541618[32] = 0;
   out_3393066705725541618[33] = 0;
   out_3393066705725541618[34] = 0;
   out_3393066705725541618[35] = 0;
   out_3393066705725541618[36] = 0;
   out_3393066705725541618[37] = 0;
   out_3393066705725541618[38] = 0;
   out_3393066705725541618[39] = 0;
   out_3393066705725541618[40] = 1;
   out_3393066705725541618[41] = 0;
   out_3393066705725541618[42] = 0;
   out_3393066705725541618[43] = 0;
   out_3393066705725541618[44] = 0;
   out_3393066705725541618[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3393066705725541618[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3393066705725541618[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3393066705725541618[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3393066705725541618[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3393066705725541618[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3393066705725541618[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3393066705725541618[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3393066705725541618[53] = -9.8100000000000005*dt;
   out_3393066705725541618[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3393066705725541618[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3393066705725541618[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3393066705725541618[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3393066705725541618[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3393066705725541618[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3393066705725541618[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3393066705725541618[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3393066705725541618[62] = 0;
   out_3393066705725541618[63] = 0;
   out_3393066705725541618[64] = 0;
   out_3393066705725541618[65] = 0;
   out_3393066705725541618[66] = 0;
   out_3393066705725541618[67] = 0;
   out_3393066705725541618[68] = 0;
   out_3393066705725541618[69] = 0;
   out_3393066705725541618[70] = 1;
   out_3393066705725541618[71] = 0;
   out_3393066705725541618[72] = 0;
   out_3393066705725541618[73] = 0;
   out_3393066705725541618[74] = 0;
   out_3393066705725541618[75] = 0;
   out_3393066705725541618[76] = 0;
   out_3393066705725541618[77] = 0;
   out_3393066705725541618[78] = 0;
   out_3393066705725541618[79] = 0;
   out_3393066705725541618[80] = 1;
}
void h_25(double *state, double *unused, double *out_3694283988136956896) {
   out_3694283988136956896[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8933928472300199885) {
   out_8933928472300199885[0] = 0;
   out_8933928472300199885[1] = 0;
   out_8933928472300199885[2] = 0;
   out_8933928472300199885[3] = 0;
   out_8933928472300199885[4] = 0;
   out_8933928472300199885[5] = 0;
   out_8933928472300199885[6] = 1;
   out_8933928472300199885[7] = 0;
   out_8933928472300199885[8] = 0;
}
void h_24(double *state, double *unused, double *out_878940354647202481) {
   out_878940354647202481[0] = state[4];
   out_878940354647202481[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7287107817430483169) {
   out_7287107817430483169[0] = 0;
   out_7287107817430483169[1] = 0;
   out_7287107817430483169[2] = 0;
   out_7287107817430483169[3] = 0;
   out_7287107817430483169[4] = 1;
   out_7287107817430483169[5] = 0;
   out_7287107817430483169[6] = 0;
   out_7287107817430483169[7] = 0;
   out_7287107817430483169[8] = 0;
   out_7287107817430483169[9] = 0;
   out_7287107817430483169[10] = 0;
   out_7287107817430483169[11] = 0;
   out_7287107817430483169[12] = 0;
   out_7287107817430483169[13] = 0;
   out_7287107817430483169[14] = 1;
   out_7287107817430483169[15] = 0;
   out_7287107817430483169[16] = 0;
   out_7287107817430483169[17] = 0;
}
void h_30(double *state, double *unused, double *out_9220341424687980009) {
   out_9220341424687980009[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2596125259917734976) {
   out_2596125259917734976[0] = 0;
   out_2596125259917734976[1] = 0;
   out_2596125259917734976[2] = 0;
   out_2596125259917734976[3] = 0;
   out_2596125259917734976[4] = 1;
   out_2596125259917734976[5] = 0;
   out_2596125259917734976[6] = 0;
   out_2596125259917734976[7] = 0;
   out_2596125259917734976[8] = 0;
}
void h_26(double *state, double *unused, double *out_4022405810528928524) {
   out_4022405810528928524[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5192425153426143661) {
   out_5192425153426143661[0] = 0;
   out_5192425153426143661[1] = 0;
   out_5192425153426143661[2] = 0;
   out_5192425153426143661[3] = 0;
   out_5192425153426143661[4] = 0;
   out_5192425153426143661[5] = 0;
   out_5192425153426143661[6] = 0;
   out_5192425153426143661[7] = 1;
   out_5192425153426143661[8] = 0;
}
void h_27(double *state, double *unused, double *out_4139954033073310033) {
   out_4139954033073310033[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4770888571718159887) {
   out_4770888571718159887[0] = 0;
   out_4770888571718159887[1] = 0;
   out_4770888571718159887[2] = 0;
   out_4770888571718159887[3] = 1;
   out_4770888571718159887[4] = 0;
   out_4770888571718159887[5] = 0;
   out_4770888571718159887[6] = 0;
   out_4770888571718159887[7] = 0;
   out_4770888571718159887[8] = 0;
}
void h_29(double *state, double *unused, double *out_6621997328212873956) {
   out_6621997328212873956[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2085893915603342792) {
   out_2085893915603342792[0] = 0;
   out_2085893915603342792[1] = 1;
   out_2085893915603342792[2] = 0;
   out_2085893915603342792[3] = 0;
   out_2085893915603342792[4] = 0;
   out_2085893915603342792[5] = 0;
   out_2085893915603342792[6] = 0;
   out_2085893915603342792[7] = 0;
   out_2085893915603342792[8] = 0;
}
void h_28(double *state, double *unused, double *out_8099632253155620528) {
   out_8099632253155620528[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7168292932672873366) {
   out_7168292932672873366[0] = 1;
   out_7168292932672873366[1] = 0;
   out_7168292932672873366[2] = 0;
   out_7168292932672873366[3] = 0;
   out_7168292932672873366[4] = 0;
   out_7168292932672873366[5] = 0;
   out_7168292932672873366[6] = 0;
   out_7168292932672873366[7] = 0;
   out_7168292932672873366[8] = 0;
}
void h_31(double *state, double *unused, double *out_5443433296546894286) {
   out_5443433296546894286[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8964574434177160313) {
   out_8964574434177160313[0] = 0;
   out_8964574434177160313[1] = 0;
   out_8964574434177160313[2] = 0;
   out_8964574434177160313[3] = 0;
   out_8964574434177160313[4] = 0;
   out_8964574434177160313[5] = 0;
   out_8964574434177160313[6] = 0;
   out_8964574434177160313[7] = 0;
   out_8964574434177160313[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_4317163891516196670) {
  err_fun(nom_x, delta_x, out_4317163891516196670);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8278424519720112087) {
  inv_err_fun(nom_x, true_x, out_8278424519720112087);
}
void car_H_mod_fun(double *state, double *out_319627375497114494) {
  H_mod_fun(state, out_319627375497114494);
}
void car_f_fun(double *state, double dt, double *out_6613977481805234540) {
  f_fun(state,  dt, out_6613977481805234540);
}
void car_F_fun(double *state, double dt, double *out_3393066705725541618) {
  F_fun(state,  dt, out_3393066705725541618);
}
void car_h_25(double *state, double *unused, double *out_3694283988136956896) {
  h_25(state, unused, out_3694283988136956896);
}
void car_H_25(double *state, double *unused, double *out_8933928472300199885) {
  H_25(state, unused, out_8933928472300199885);
}
void car_h_24(double *state, double *unused, double *out_878940354647202481) {
  h_24(state, unused, out_878940354647202481);
}
void car_H_24(double *state, double *unused, double *out_7287107817430483169) {
  H_24(state, unused, out_7287107817430483169);
}
void car_h_30(double *state, double *unused, double *out_9220341424687980009) {
  h_30(state, unused, out_9220341424687980009);
}
void car_H_30(double *state, double *unused, double *out_2596125259917734976) {
  H_30(state, unused, out_2596125259917734976);
}
void car_h_26(double *state, double *unused, double *out_4022405810528928524) {
  h_26(state, unused, out_4022405810528928524);
}
void car_H_26(double *state, double *unused, double *out_5192425153426143661) {
  H_26(state, unused, out_5192425153426143661);
}
void car_h_27(double *state, double *unused, double *out_4139954033073310033) {
  h_27(state, unused, out_4139954033073310033);
}
void car_H_27(double *state, double *unused, double *out_4770888571718159887) {
  H_27(state, unused, out_4770888571718159887);
}
void car_h_29(double *state, double *unused, double *out_6621997328212873956) {
  h_29(state, unused, out_6621997328212873956);
}
void car_H_29(double *state, double *unused, double *out_2085893915603342792) {
  H_29(state, unused, out_2085893915603342792);
}
void car_h_28(double *state, double *unused, double *out_8099632253155620528) {
  h_28(state, unused, out_8099632253155620528);
}
void car_H_28(double *state, double *unused, double *out_7168292932672873366) {
  H_28(state, unused, out_7168292932672873366);
}
void car_h_31(double *state, double *unused, double *out_5443433296546894286) {
  h_31(state, unused, out_5443433296546894286);
}
void car_H_31(double *state, double *unused, double *out_8964574434177160313) {
  H_31(state, unused, out_8964574434177160313);
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
