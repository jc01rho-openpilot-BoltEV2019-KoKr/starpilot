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
void err_fun(double *nom_x, double *delta_x, double *out_8449647197806450456) {
   out_8449647197806450456[0] = delta_x[0] + nom_x[0];
   out_8449647197806450456[1] = delta_x[1] + nom_x[1];
   out_8449647197806450456[2] = delta_x[2] + nom_x[2];
   out_8449647197806450456[3] = delta_x[3] + nom_x[3];
   out_8449647197806450456[4] = delta_x[4] + nom_x[4];
   out_8449647197806450456[5] = delta_x[5] + nom_x[5];
   out_8449647197806450456[6] = delta_x[6] + nom_x[6];
   out_8449647197806450456[7] = delta_x[7] + nom_x[7];
   out_8449647197806450456[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5810954439872327790) {
   out_5810954439872327790[0] = -nom_x[0] + true_x[0];
   out_5810954439872327790[1] = -nom_x[1] + true_x[1];
   out_5810954439872327790[2] = -nom_x[2] + true_x[2];
   out_5810954439872327790[3] = -nom_x[3] + true_x[3];
   out_5810954439872327790[4] = -nom_x[4] + true_x[4];
   out_5810954439872327790[5] = -nom_x[5] + true_x[5];
   out_5810954439872327790[6] = -nom_x[6] + true_x[6];
   out_5810954439872327790[7] = -nom_x[7] + true_x[7];
   out_5810954439872327790[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_618486876633759422) {
   out_618486876633759422[0] = 1.0;
   out_618486876633759422[1] = 0.0;
   out_618486876633759422[2] = 0.0;
   out_618486876633759422[3] = 0.0;
   out_618486876633759422[4] = 0.0;
   out_618486876633759422[5] = 0.0;
   out_618486876633759422[6] = 0.0;
   out_618486876633759422[7] = 0.0;
   out_618486876633759422[8] = 0.0;
   out_618486876633759422[9] = 0.0;
   out_618486876633759422[10] = 1.0;
   out_618486876633759422[11] = 0.0;
   out_618486876633759422[12] = 0.0;
   out_618486876633759422[13] = 0.0;
   out_618486876633759422[14] = 0.0;
   out_618486876633759422[15] = 0.0;
   out_618486876633759422[16] = 0.0;
   out_618486876633759422[17] = 0.0;
   out_618486876633759422[18] = 0.0;
   out_618486876633759422[19] = 0.0;
   out_618486876633759422[20] = 1.0;
   out_618486876633759422[21] = 0.0;
   out_618486876633759422[22] = 0.0;
   out_618486876633759422[23] = 0.0;
   out_618486876633759422[24] = 0.0;
   out_618486876633759422[25] = 0.0;
   out_618486876633759422[26] = 0.0;
   out_618486876633759422[27] = 0.0;
   out_618486876633759422[28] = 0.0;
   out_618486876633759422[29] = 0.0;
   out_618486876633759422[30] = 1.0;
   out_618486876633759422[31] = 0.0;
   out_618486876633759422[32] = 0.0;
   out_618486876633759422[33] = 0.0;
   out_618486876633759422[34] = 0.0;
   out_618486876633759422[35] = 0.0;
   out_618486876633759422[36] = 0.0;
   out_618486876633759422[37] = 0.0;
   out_618486876633759422[38] = 0.0;
   out_618486876633759422[39] = 0.0;
   out_618486876633759422[40] = 1.0;
   out_618486876633759422[41] = 0.0;
   out_618486876633759422[42] = 0.0;
   out_618486876633759422[43] = 0.0;
   out_618486876633759422[44] = 0.0;
   out_618486876633759422[45] = 0.0;
   out_618486876633759422[46] = 0.0;
   out_618486876633759422[47] = 0.0;
   out_618486876633759422[48] = 0.0;
   out_618486876633759422[49] = 0.0;
   out_618486876633759422[50] = 1.0;
   out_618486876633759422[51] = 0.0;
   out_618486876633759422[52] = 0.0;
   out_618486876633759422[53] = 0.0;
   out_618486876633759422[54] = 0.0;
   out_618486876633759422[55] = 0.0;
   out_618486876633759422[56] = 0.0;
   out_618486876633759422[57] = 0.0;
   out_618486876633759422[58] = 0.0;
   out_618486876633759422[59] = 0.0;
   out_618486876633759422[60] = 1.0;
   out_618486876633759422[61] = 0.0;
   out_618486876633759422[62] = 0.0;
   out_618486876633759422[63] = 0.0;
   out_618486876633759422[64] = 0.0;
   out_618486876633759422[65] = 0.0;
   out_618486876633759422[66] = 0.0;
   out_618486876633759422[67] = 0.0;
   out_618486876633759422[68] = 0.0;
   out_618486876633759422[69] = 0.0;
   out_618486876633759422[70] = 1.0;
   out_618486876633759422[71] = 0.0;
   out_618486876633759422[72] = 0.0;
   out_618486876633759422[73] = 0.0;
   out_618486876633759422[74] = 0.0;
   out_618486876633759422[75] = 0.0;
   out_618486876633759422[76] = 0.0;
   out_618486876633759422[77] = 0.0;
   out_618486876633759422[78] = 0.0;
   out_618486876633759422[79] = 0.0;
   out_618486876633759422[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8508843375909038975) {
   out_8508843375909038975[0] = state[0];
   out_8508843375909038975[1] = state[1];
   out_8508843375909038975[2] = state[2];
   out_8508843375909038975[3] = state[3];
   out_8508843375909038975[4] = state[4];
   out_8508843375909038975[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8508843375909038975[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8508843375909038975[7] = state[7];
   out_8508843375909038975[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2668986513863288583) {
   out_2668986513863288583[0] = 1;
   out_2668986513863288583[1] = 0;
   out_2668986513863288583[2] = 0;
   out_2668986513863288583[3] = 0;
   out_2668986513863288583[4] = 0;
   out_2668986513863288583[5] = 0;
   out_2668986513863288583[6] = 0;
   out_2668986513863288583[7] = 0;
   out_2668986513863288583[8] = 0;
   out_2668986513863288583[9] = 0;
   out_2668986513863288583[10] = 1;
   out_2668986513863288583[11] = 0;
   out_2668986513863288583[12] = 0;
   out_2668986513863288583[13] = 0;
   out_2668986513863288583[14] = 0;
   out_2668986513863288583[15] = 0;
   out_2668986513863288583[16] = 0;
   out_2668986513863288583[17] = 0;
   out_2668986513863288583[18] = 0;
   out_2668986513863288583[19] = 0;
   out_2668986513863288583[20] = 1;
   out_2668986513863288583[21] = 0;
   out_2668986513863288583[22] = 0;
   out_2668986513863288583[23] = 0;
   out_2668986513863288583[24] = 0;
   out_2668986513863288583[25] = 0;
   out_2668986513863288583[26] = 0;
   out_2668986513863288583[27] = 0;
   out_2668986513863288583[28] = 0;
   out_2668986513863288583[29] = 0;
   out_2668986513863288583[30] = 1;
   out_2668986513863288583[31] = 0;
   out_2668986513863288583[32] = 0;
   out_2668986513863288583[33] = 0;
   out_2668986513863288583[34] = 0;
   out_2668986513863288583[35] = 0;
   out_2668986513863288583[36] = 0;
   out_2668986513863288583[37] = 0;
   out_2668986513863288583[38] = 0;
   out_2668986513863288583[39] = 0;
   out_2668986513863288583[40] = 1;
   out_2668986513863288583[41] = 0;
   out_2668986513863288583[42] = 0;
   out_2668986513863288583[43] = 0;
   out_2668986513863288583[44] = 0;
   out_2668986513863288583[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2668986513863288583[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2668986513863288583[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2668986513863288583[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2668986513863288583[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2668986513863288583[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2668986513863288583[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2668986513863288583[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2668986513863288583[53] = -9.8100000000000005*dt;
   out_2668986513863288583[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2668986513863288583[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2668986513863288583[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2668986513863288583[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2668986513863288583[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2668986513863288583[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2668986513863288583[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2668986513863288583[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2668986513863288583[62] = 0;
   out_2668986513863288583[63] = 0;
   out_2668986513863288583[64] = 0;
   out_2668986513863288583[65] = 0;
   out_2668986513863288583[66] = 0;
   out_2668986513863288583[67] = 0;
   out_2668986513863288583[68] = 0;
   out_2668986513863288583[69] = 0;
   out_2668986513863288583[70] = 1;
   out_2668986513863288583[71] = 0;
   out_2668986513863288583[72] = 0;
   out_2668986513863288583[73] = 0;
   out_2668986513863288583[74] = 0;
   out_2668986513863288583[75] = 0;
   out_2668986513863288583[76] = 0;
   out_2668986513863288583[77] = 0;
   out_2668986513863288583[78] = 0;
   out_2668986513863288583[79] = 0;
   out_2668986513863288583[80] = 1;
}
void h_25(double *state, double *unused, double *out_4860957648027245326) {
   out_4860957648027245326[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6932876854201394115) {
   out_6932876854201394115[0] = 0;
   out_6932876854201394115[1] = 0;
   out_6932876854201394115[2] = 0;
   out_6932876854201394115[3] = 0;
   out_6932876854201394115[4] = 0;
   out_6932876854201394115[5] = 0;
   out_6932876854201394115[6] = 1;
   out_6932876854201394115[7] = 0;
   out_6932876854201394115[8] = 0;
}
void h_24(double *state, double *unused, double *out_8219518906691440912) {
   out_8219518906691440912[0] = state[4];
   out_8219518906691440912[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6462419372158055391) {
   out_6462419372158055391[0] = 0;
   out_6462419372158055391[1] = 0;
   out_6462419372158055391[2] = 0;
   out_6462419372158055391[3] = 0;
   out_6462419372158055391[4] = 1;
   out_6462419372158055391[5] = 0;
   out_6462419372158055391[6] = 0;
   out_6462419372158055391[7] = 0;
   out_6462419372158055391[8] = 0;
   out_6462419372158055391[9] = 0;
   out_6462419372158055391[10] = 0;
   out_6462419372158055391[11] = 0;
   out_6462419372158055391[12] = 0;
   out_6462419372158055391[13] = 0;
   out_6462419372158055391[14] = 1;
   out_6462419372158055391[15] = 0;
   out_6462419372158055391[16] = 0;
   out_6462419372158055391[17] = 0;
}
void h_30(double *state, double *unused, double *out_1502636330274570535) {
   out_1502636330274570535[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6803537907058154045) {
   out_6803537907058154045[0] = 0;
   out_6803537907058154045[1] = 0;
   out_6803537907058154045[2] = 0;
   out_6803537907058154045[3] = 0;
   out_6803537907058154045[4] = 1;
   out_6803537907058154045[5] = 0;
   out_6803537907058154045[6] = 0;
   out_6803537907058154045[7] = 0;
   out_6803537907058154045[8] = 0;
}
void h_26(double *state, double *unused, double *out_899320445598093018) {
   out_899320445598093018[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3191373535327337891) {
   out_3191373535327337891[0] = 0;
   out_3191373535327337891[1] = 0;
   out_3191373535327337891[2] = 0;
   out_3191373535327337891[3] = 0;
   out_3191373535327337891[4] = 0;
   out_3191373535327337891[5] = 0;
   out_3191373535327337891[6] = 0;
   out_3191373535327337891[7] = 1;
   out_3191373535327337891[8] = 0;
}
void h_27(double *state, double *unused, double *out_6028701449103387063) {
   out_6028701449103387063[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4628774595257729134) {
   out_4628774595257729134[0] = 0;
   out_4628774595257729134[1] = 0;
   out_4628774595257729134[2] = 0;
   out_4628774595257729134[3] = 1;
   out_4628774595257729134[4] = 0;
   out_4628774595257729134[5] = 0;
   out_4628774595257729134[6] = 0;
   out_4628774595257729134[7] = 0;
   out_4628774595257729134[8] = 0;
}
void h_29(double *state, double *unused, double *out_1056966285338217398) {
   out_1056966285338217398[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7313769251372546229) {
   out_7313769251372546229[0] = 0;
   out_7313769251372546229[1] = 1;
   out_7313769251372546229[2] = 0;
   out_7313769251372546229[3] = 0;
   out_7313769251372546229[4] = 0;
   out_7313769251372546229[5] = 0;
   out_7313769251372546229[6] = 0;
   out_7313769251372546229[7] = 0;
   out_7313769251372546229[8] = 0;
}
void h_28(double *state, double *unused, double *out_1027028181442541418) {
   out_1027028181442541418[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2166987148681352473) {
   out_2166987148681352473[0] = 1;
   out_2166987148681352473[1] = 0;
   out_2166987148681352473[2] = 0;
   out_2166987148681352473[3] = 0;
   out_2166987148681352473[4] = 0;
   out_2166987148681352473[5] = 0;
   out_2166987148681352473[6] = 0;
   out_2166987148681352473[7] = 0;
   out_2166987148681352473[8] = 0;
}
void h_31(double *state, double *unused, double *out_4928004927850595483) {
   out_4928004927850595483[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6963522816078354543) {
   out_6963522816078354543[0] = 0;
   out_6963522816078354543[1] = 0;
   out_6963522816078354543[2] = 0;
   out_6963522816078354543[3] = 0;
   out_6963522816078354543[4] = 0;
   out_6963522816078354543[5] = 0;
   out_6963522816078354543[6] = 0;
   out_6963522816078354543[7] = 0;
   out_6963522816078354543[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_8449647197806450456) {
  err_fun(nom_x, delta_x, out_8449647197806450456);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5810954439872327790) {
  inv_err_fun(nom_x, true_x, out_5810954439872327790);
}
void car_H_mod_fun(double *state, double *out_618486876633759422) {
  H_mod_fun(state, out_618486876633759422);
}
void car_f_fun(double *state, double dt, double *out_8508843375909038975) {
  f_fun(state,  dt, out_8508843375909038975);
}
void car_F_fun(double *state, double dt, double *out_2668986513863288583) {
  F_fun(state,  dt, out_2668986513863288583);
}
void car_h_25(double *state, double *unused, double *out_4860957648027245326) {
  h_25(state, unused, out_4860957648027245326);
}
void car_H_25(double *state, double *unused, double *out_6932876854201394115) {
  H_25(state, unused, out_6932876854201394115);
}
void car_h_24(double *state, double *unused, double *out_8219518906691440912) {
  h_24(state, unused, out_8219518906691440912);
}
void car_H_24(double *state, double *unused, double *out_6462419372158055391) {
  H_24(state, unused, out_6462419372158055391);
}
void car_h_30(double *state, double *unused, double *out_1502636330274570535) {
  h_30(state, unused, out_1502636330274570535);
}
void car_H_30(double *state, double *unused, double *out_6803537907058154045) {
  H_30(state, unused, out_6803537907058154045);
}
void car_h_26(double *state, double *unused, double *out_899320445598093018) {
  h_26(state, unused, out_899320445598093018);
}
void car_H_26(double *state, double *unused, double *out_3191373535327337891) {
  H_26(state, unused, out_3191373535327337891);
}
void car_h_27(double *state, double *unused, double *out_6028701449103387063) {
  h_27(state, unused, out_6028701449103387063);
}
void car_H_27(double *state, double *unused, double *out_4628774595257729134) {
  H_27(state, unused, out_4628774595257729134);
}
void car_h_29(double *state, double *unused, double *out_1056966285338217398) {
  h_29(state, unused, out_1056966285338217398);
}
void car_H_29(double *state, double *unused, double *out_7313769251372546229) {
  H_29(state, unused, out_7313769251372546229);
}
void car_h_28(double *state, double *unused, double *out_1027028181442541418) {
  h_28(state, unused, out_1027028181442541418);
}
void car_H_28(double *state, double *unused, double *out_2166987148681352473) {
  H_28(state, unused, out_2166987148681352473);
}
void car_h_31(double *state, double *unused, double *out_4928004927850595483) {
  h_31(state, unused, out_4928004927850595483);
}
void car_H_31(double *state, double *unused, double *out_6963522816078354543) {
  H_31(state, unused, out_6963522816078354543);
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
