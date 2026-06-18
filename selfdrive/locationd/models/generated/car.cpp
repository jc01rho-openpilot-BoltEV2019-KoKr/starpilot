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
void err_fun(double *nom_x, double *delta_x, double *out_822107927183758870) {
   out_822107927183758870[0] = delta_x[0] + nom_x[0];
   out_822107927183758870[1] = delta_x[1] + nom_x[1];
   out_822107927183758870[2] = delta_x[2] + nom_x[2];
   out_822107927183758870[3] = delta_x[3] + nom_x[3];
   out_822107927183758870[4] = delta_x[4] + nom_x[4];
   out_822107927183758870[5] = delta_x[5] + nom_x[5];
   out_822107927183758870[6] = delta_x[6] + nom_x[6];
   out_822107927183758870[7] = delta_x[7] + nom_x[7];
   out_822107927183758870[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4567978126636007906) {
   out_4567978126636007906[0] = -nom_x[0] + true_x[0];
   out_4567978126636007906[1] = -nom_x[1] + true_x[1];
   out_4567978126636007906[2] = -nom_x[2] + true_x[2];
   out_4567978126636007906[3] = -nom_x[3] + true_x[3];
   out_4567978126636007906[4] = -nom_x[4] + true_x[4];
   out_4567978126636007906[5] = -nom_x[5] + true_x[5];
   out_4567978126636007906[6] = -nom_x[6] + true_x[6];
   out_4567978126636007906[7] = -nom_x[7] + true_x[7];
   out_4567978126636007906[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4866635074780860371) {
   out_4866635074780860371[0] = 1.0;
   out_4866635074780860371[1] = 0.0;
   out_4866635074780860371[2] = 0.0;
   out_4866635074780860371[3] = 0.0;
   out_4866635074780860371[4] = 0.0;
   out_4866635074780860371[5] = 0.0;
   out_4866635074780860371[6] = 0.0;
   out_4866635074780860371[7] = 0.0;
   out_4866635074780860371[8] = 0.0;
   out_4866635074780860371[9] = 0.0;
   out_4866635074780860371[10] = 1.0;
   out_4866635074780860371[11] = 0.0;
   out_4866635074780860371[12] = 0.0;
   out_4866635074780860371[13] = 0.0;
   out_4866635074780860371[14] = 0.0;
   out_4866635074780860371[15] = 0.0;
   out_4866635074780860371[16] = 0.0;
   out_4866635074780860371[17] = 0.0;
   out_4866635074780860371[18] = 0.0;
   out_4866635074780860371[19] = 0.0;
   out_4866635074780860371[20] = 1.0;
   out_4866635074780860371[21] = 0.0;
   out_4866635074780860371[22] = 0.0;
   out_4866635074780860371[23] = 0.0;
   out_4866635074780860371[24] = 0.0;
   out_4866635074780860371[25] = 0.0;
   out_4866635074780860371[26] = 0.0;
   out_4866635074780860371[27] = 0.0;
   out_4866635074780860371[28] = 0.0;
   out_4866635074780860371[29] = 0.0;
   out_4866635074780860371[30] = 1.0;
   out_4866635074780860371[31] = 0.0;
   out_4866635074780860371[32] = 0.0;
   out_4866635074780860371[33] = 0.0;
   out_4866635074780860371[34] = 0.0;
   out_4866635074780860371[35] = 0.0;
   out_4866635074780860371[36] = 0.0;
   out_4866635074780860371[37] = 0.0;
   out_4866635074780860371[38] = 0.0;
   out_4866635074780860371[39] = 0.0;
   out_4866635074780860371[40] = 1.0;
   out_4866635074780860371[41] = 0.0;
   out_4866635074780860371[42] = 0.0;
   out_4866635074780860371[43] = 0.0;
   out_4866635074780860371[44] = 0.0;
   out_4866635074780860371[45] = 0.0;
   out_4866635074780860371[46] = 0.0;
   out_4866635074780860371[47] = 0.0;
   out_4866635074780860371[48] = 0.0;
   out_4866635074780860371[49] = 0.0;
   out_4866635074780860371[50] = 1.0;
   out_4866635074780860371[51] = 0.0;
   out_4866635074780860371[52] = 0.0;
   out_4866635074780860371[53] = 0.0;
   out_4866635074780860371[54] = 0.0;
   out_4866635074780860371[55] = 0.0;
   out_4866635074780860371[56] = 0.0;
   out_4866635074780860371[57] = 0.0;
   out_4866635074780860371[58] = 0.0;
   out_4866635074780860371[59] = 0.0;
   out_4866635074780860371[60] = 1.0;
   out_4866635074780860371[61] = 0.0;
   out_4866635074780860371[62] = 0.0;
   out_4866635074780860371[63] = 0.0;
   out_4866635074780860371[64] = 0.0;
   out_4866635074780860371[65] = 0.0;
   out_4866635074780860371[66] = 0.0;
   out_4866635074780860371[67] = 0.0;
   out_4866635074780860371[68] = 0.0;
   out_4866635074780860371[69] = 0.0;
   out_4866635074780860371[70] = 1.0;
   out_4866635074780860371[71] = 0.0;
   out_4866635074780860371[72] = 0.0;
   out_4866635074780860371[73] = 0.0;
   out_4866635074780860371[74] = 0.0;
   out_4866635074780860371[75] = 0.0;
   out_4866635074780860371[76] = 0.0;
   out_4866635074780860371[77] = 0.0;
   out_4866635074780860371[78] = 0.0;
   out_4866635074780860371[79] = 0.0;
   out_4866635074780860371[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_982026265070027710) {
   out_982026265070027710[0] = state[0];
   out_982026265070027710[1] = state[1];
   out_982026265070027710[2] = state[2];
   out_982026265070027710[3] = state[3];
   out_982026265070027710[4] = state[4];
   out_982026265070027710[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_982026265070027710[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_982026265070027710[7] = state[7];
   out_982026265070027710[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1254446333762572024) {
   out_1254446333762572024[0] = 1;
   out_1254446333762572024[1] = 0;
   out_1254446333762572024[2] = 0;
   out_1254446333762572024[3] = 0;
   out_1254446333762572024[4] = 0;
   out_1254446333762572024[5] = 0;
   out_1254446333762572024[6] = 0;
   out_1254446333762572024[7] = 0;
   out_1254446333762572024[8] = 0;
   out_1254446333762572024[9] = 0;
   out_1254446333762572024[10] = 1;
   out_1254446333762572024[11] = 0;
   out_1254446333762572024[12] = 0;
   out_1254446333762572024[13] = 0;
   out_1254446333762572024[14] = 0;
   out_1254446333762572024[15] = 0;
   out_1254446333762572024[16] = 0;
   out_1254446333762572024[17] = 0;
   out_1254446333762572024[18] = 0;
   out_1254446333762572024[19] = 0;
   out_1254446333762572024[20] = 1;
   out_1254446333762572024[21] = 0;
   out_1254446333762572024[22] = 0;
   out_1254446333762572024[23] = 0;
   out_1254446333762572024[24] = 0;
   out_1254446333762572024[25] = 0;
   out_1254446333762572024[26] = 0;
   out_1254446333762572024[27] = 0;
   out_1254446333762572024[28] = 0;
   out_1254446333762572024[29] = 0;
   out_1254446333762572024[30] = 1;
   out_1254446333762572024[31] = 0;
   out_1254446333762572024[32] = 0;
   out_1254446333762572024[33] = 0;
   out_1254446333762572024[34] = 0;
   out_1254446333762572024[35] = 0;
   out_1254446333762572024[36] = 0;
   out_1254446333762572024[37] = 0;
   out_1254446333762572024[38] = 0;
   out_1254446333762572024[39] = 0;
   out_1254446333762572024[40] = 1;
   out_1254446333762572024[41] = 0;
   out_1254446333762572024[42] = 0;
   out_1254446333762572024[43] = 0;
   out_1254446333762572024[44] = 0;
   out_1254446333762572024[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1254446333762572024[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1254446333762572024[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1254446333762572024[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1254446333762572024[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1254446333762572024[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1254446333762572024[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1254446333762572024[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1254446333762572024[53] = -9.8100000000000005*dt;
   out_1254446333762572024[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1254446333762572024[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1254446333762572024[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1254446333762572024[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1254446333762572024[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1254446333762572024[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1254446333762572024[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1254446333762572024[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1254446333762572024[62] = 0;
   out_1254446333762572024[63] = 0;
   out_1254446333762572024[64] = 0;
   out_1254446333762572024[65] = 0;
   out_1254446333762572024[66] = 0;
   out_1254446333762572024[67] = 0;
   out_1254446333762572024[68] = 0;
   out_1254446333762572024[69] = 0;
   out_1254446333762572024[70] = 1;
   out_1254446333762572024[71] = 0;
   out_1254446333762572024[72] = 0;
   out_1254446333762572024[73] = 0;
   out_1254446333762572024[74] = 0;
   out_1254446333762572024[75] = 0;
   out_1254446333762572024[76] = 0;
   out_1254446333762572024[77] = 0;
   out_1254446333762572024[78] = 0;
   out_1254446333762572024[79] = 0;
   out_1254446333762572024[80] = 1;
}
void h_25(double *state, double *unused, double *out_3612384322752044911) {
   out_3612384322752044911[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4326553151131376866) {
   out_4326553151131376866[0] = 0;
   out_4326553151131376866[1] = 0;
   out_4326553151131376866[2] = 0;
   out_4326553151131376866[3] = 0;
   out_4326553151131376866[4] = 0;
   out_4326553151131376866[5] = 0;
   out_4326553151131376866[6] = 1;
   out_4326553151131376866[7] = 0;
   out_4326553151131376866[8] = 0;
}
void h_24(double *state, double *unused, double *out_5341613571554885336) {
   out_5341613571554885336[0] = state[4];
   out_5341613571554885336[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2100845367152508304) {
   out_2100845367152508304[0] = 0;
   out_2100845367152508304[1] = 0;
   out_2100845367152508304[2] = 0;
   out_2100845367152508304[3] = 0;
   out_2100845367152508304[4] = 1;
   out_2100845367152508304[5] = 0;
   out_2100845367152508304[6] = 0;
   out_2100845367152508304[7] = 0;
   out_2100845367152508304[8] = 0;
   out_2100845367152508304[9] = 0;
   out_2100845367152508304[10] = 0;
   out_2100845367152508304[11] = 0;
   out_2100845367152508304[12] = 0;
   out_2100845367152508304[13] = 0;
   out_2100845367152508304[14] = 1;
   out_2100845367152508304[15] = 0;
   out_2100845367152508304[16] = 0;
   out_2100845367152508304[17] = 0;
}
void h_30(double *state, double *unused, double *out_3337190260467539022) {
   out_3337190260467539022[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4455892098274616936) {
   out_4455892098274616936[0] = 0;
   out_4455892098274616936[1] = 0;
   out_4455892098274616936[2] = 0;
   out_4455892098274616936[3] = 0;
   out_4455892098274616936[4] = 1;
   out_4455892098274616936[5] = 0;
   out_4455892098274616936[6] = 0;
   out_4455892098274616936[7] = 0;
   out_4455892098274616936[8] = 0;
}
void h_26(double *state, double *unused, double *out_2004676975418491541) {
   out_2004676975418491541[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8068056470005433090) {
   out_8068056470005433090[0] = 0;
   out_8068056470005433090[1] = 0;
   out_8068056470005433090[2] = 0;
   out_8068056470005433090[3] = 0;
   out_8068056470005433090[4] = 0;
   out_8068056470005433090[5] = 0;
   out_8068056470005433090[6] = 0;
   out_8068056470005433090[7] = 1;
   out_8068056470005433090[8] = 0;
}
void h_27(double *state, double *unused, double *out_1389288944908800734) {
   out_1389288944908800734[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6630655410075041847) {
   out_6630655410075041847[0] = 0;
   out_6630655410075041847[1] = 0;
   out_6630655410075041847[2] = 0;
   out_6630655410075041847[3] = 1;
   out_6630655410075041847[4] = 0;
   out_6630655410075041847[5] = 0;
   out_6630655410075041847[6] = 0;
   out_6630655410075041847[7] = 0;
   out_6630655410075041847[8] = 0;
}
void h_29(double *state, double *unused, double *out_1664483007193306623) {
   out_1664483007193306623[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3945660753960224752) {
   out_3945660753960224752[0] = 0;
   out_3945660753960224752[1] = 1;
   out_3945660753960224752[2] = 0;
   out_3945660753960224752[3] = 0;
   out_3945660753960224752[4] = 0;
   out_3945660753960224752[5] = 0;
   out_3945660753960224752[6] = 0;
   out_3945660753960224752[7] = 0;
   out_3945660753960224752[8] = 0;
}
void h_28(double *state, double *unused, double *out_990882427725417615) {
   out_990882427725417615[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1982030482394898501) {
   out_1982030482394898501[0] = 1;
   out_1982030482394898501[1] = 0;
   out_1982030482394898501[2] = 0;
   out_1982030482394898501[3] = 0;
   out_1982030482394898501[4] = 0;
   out_1982030482394898501[5] = 0;
   out_1982030482394898501[6] = 0;
   out_1982030482394898501[7] = 0;
   out_1982030482394898501[8] = 0;
}
void h_31(double *state, double *unused, double *out_7249833851006067261) {
   out_7249833851006067261[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4295907189254416438) {
   out_4295907189254416438[0] = 0;
   out_4295907189254416438[1] = 0;
   out_4295907189254416438[2] = 0;
   out_4295907189254416438[3] = 0;
   out_4295907189254416438[4] = 0;
   out_4295907189254416438[5] = 0;
   out_4295907189254416438[6] = 0;
   out_4295907189254416438[7] = 0;
   out_4295907189254416438[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_822107927183758870) {
  err_fun(nom_x, delta_x, out_822107927183758870);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4567978126636007906) {
  inv_err_fun(nom_x, true_x, out_4567978126636007906);
}
void car_H_mod_fun(double *state, double *out_4866635074780860371) {
  H_mod_fun(state, out_4866635074780860371);
}
void car_f_fun(double *state, double dt, double *out_982026265070027710) {
  f_fun(state,  dt, out_982026265070027710);
}
void car_F_fun(double *state, double dt, double *out_1254446333762572024) {
  F_fun(state,  dt, out_1254446333762572024);
}
void car_h_25(double *state, double *unused, double *out_3612384322752044911) {
  h_25(state, unused, out_3612384322752044911);
}
void car_H_25(double *state, double *unused, double *out_4326553151131376866) {
  H_25(state, unused, out_4326553151131376866);
}
void car_h_24(double *state, double *unused, double *out_5341613571554885336) {
  h_24(state, unused, out_5341613571554885336);
}
void car_H_24(double *state, double *unused, double *out_2100845367152508304) {
  H_24(state, unused, out_2100845367152508304);
}
void car_h_30(double *state, double *unused, double *out_3337190260467539022) {
  h_30(state, unused, out_3337190260467539022);
}
void car_H_30(double *state, double *unused, double *out_4455892098274616936) {
  H_30(state, unused, out_4455892098274616936);
}
void car_h_26(double *state, double *unused, double *out_2004676975418491541) {
  h_26(state, unused, out_2004676975418491541);
}
void car_H_26(double *state, double *unused, double *out_8068056470005433090) {
  H_26(state, unused, out_8068056470005433090);
}
void car_h_27(double *state, double *unused, double *out_1389288944908800734) {
  h_27(state, unused, out_1389288944908800734);
}
void car_H_27(double *state, double *unused, double *out_6630655410075041847) {
  H_27(state, unused, out_6630655410075041847);
}
void car_h_29(double *state, double *unused, double *out_1664483007193306623) {
  h_29(state, unused, out_1664483007193306623);
}
void car_H_29(double *state, double *unused, double *out_3945660753960224752) {
  H_29(state, unused, out_3945660753960224752);
}
void car_h_28(double *state, double *unused, double *out_990882427725417615) {
  h_28(state, unused, out_990882427725417615);
}
void car_H_28(double *state, double *unused, double *out_1982030482394898501) {
  H_28(state, unused, out_1982030482394898501);
}
void car_h_31(double *state, double *unused, double *out_7249833851006067261) {
  h_31(state, unused, out_7249833851006067261);
}
void car_H_31(double *state, double *unused, double *out_4295907189254416438) {
  H_31(state, unused, out_4295907189254416438);
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
