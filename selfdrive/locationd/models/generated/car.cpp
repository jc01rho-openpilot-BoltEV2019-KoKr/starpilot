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
void err_fun(double *nom_x, double *delta_x, double *out_2600768462618711997) {
   out_2600768462618711997[0] = delta_x[0] + nom_x[0];
   out_2600768462618711997[1] = delta_x[1] + nom_x[1];
   out_2600768462618711997[2] = delta_x[2] + nom_x[2];
   out_2600768462618711997[3] = delta_x[3] + nom_x[3];
   out_2600768462618711997[4] = delta_x[4] + nom_x[4];
   out_2600768462618711997[5] = delta_x[5] + nom_x[5];
   out_2600768462618711997[6] = delta_x[6] + nom_x[6];
   out_2600768462618711997[7] = delta_x[7] + nom_x[7];
   out_2600768462618711997[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7259494313163356603) {
   out_7259494313163356603[0] = -nom_x[0] + true_x[0];
   out_7259494313163356603[1] = -nom_x[1] + true_x[1];
   out_7259494313163356603[2] = -nom_x[2] + true_x[2];
   out_7259494313163356603[3] = -nom_x[3] + true_x[3];
   out_7259494313163356603[4] = -nom_x[4] + true_x[4];
   out_7259494313163356603[5] = -nom_x[5] + true_x[5];
   out_7259494313163356603[6] = -nom_x[6] + true_x[6];
   out_7259494313163356603[7] = -nom_x[7] + true_x[7];
   out_7259494313163356603[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1493188658696786749) {
   out_1493188658696786749[0] = 1.0;
   out_1493188658696786749[1] = 0.0;
   out_1493188658696786749[2] = 0.0;
   out_1493188658696786749[3] = 0.0;
   out_1493188658696786749[4] = 0.0;
   out_1493188658696786749[5] = 0.0;
   out_1493188658696786749[6] = 0.0;
   out_1493188658696786749[7] = 0.0;
   out_1493188658696786749[8] = 0.0;
   out_1493188658696786749[9] = 0.0;
   out_1493188658696786749[10] = 1.0;
   out_1493188658696786749[11] = 0.0;
   out_1493188658696786749[12] = 0.0;
   out_1493188658696786749[13] = 0.0;
   out_1493188658696786749[14] = 0.0;
   out_1493188658696786749[15] = 0.0;
   out_1493188658696786749[16] = 0.0;
   out_1493188658696786749[17] = 0.0;
   out_1493188658696786749[18] = 0.0;
   out_1493188658696786749[19] = 0.0;
   out_1493188658696786749[20] = 1.0;
   out_1493188658696786749[21] = 0.0;
   out_1493188658696786749[22] = 0.0;
   out_1493188658696786749[23] = 0.0;
   out_1493188658696786749[24] = 0.0;
   out_1493188658696786749[25] = 0.0;
   out_1493188658696786749[26] = 0.0;
   out_1493188658696786749[27] = 0.0;
   out_1493188658696786749[28] = 0.0;
   out_1493188658696786749[29] = 0.0;
   out_1493188658696786749[30] = 1.0;
   out_1493188658696786749[31] = 0.0;
   out_1493188658696786749[32] = 0.0;
   out_1493188658696786749[33] = 0.0;
   out_1493188658696786749[34] = 0.0;
   out_1493188658696786749[35] = 0.0;
   out_1493188658696786749[36] = 0.0;
   out_1493188658696786749[37] = 0.0;
   out_1493188658696786749[38] = 0.0;
   out_1493188658696786749[39] = 0.0;
   out_1493188658696786749[40] = 1.0;
   out_1493188658696786749[41] = 0.0;
   out_1493188658696786749[42] = 0.0;
   out_1493188658696786749[43] = 0.0;
   out_1493188658696786749[44] = 0.0;
   out_1493188658696786749[45] = 0.0;
   out_1493188658696786749[46] = 0.0;
   out_1493188658696786749[47] = 0.0;
   out_1493188658696786749[48] = 0.0;
   out_1493188658696786749[49] = 0.0;
   out_1493188658696786749[50] = 1.0;
   out_1493188658696786749[51] = 0.0;
   out_1493188658696786749[52] = 0.0;
   out_1493188658696786749[53] = 0.0;
   out_1493188658696786749[54] = 0.0;
   out_1493188658696786749[55] = 0.0;
   out_1493188658696786749[56] = 0.0;
   out_1493188658696786749[57] = 0.0;
   out_1493188658696786749[58] = 0.0;
   out_1493188658696786749[59] = 0.0;
   out_1493188658696786749[60] = 1.0;
   out_1493188658696786749[61] = 0.0;
   out_1493188658696786749[62] = 0.0;
   out_1493188658696786749[63] = 0.0;
   out_1493188658696786749[64] = 0.0;
   out_1493188658696786749[65] = 0.0;
   out_1493188658696786749[66] = 0.0;
   out_1493188658696786749[67] = 0.0;
   out_1493188658696786749[68] = 0.0;
   out_1493188658696786749[69] = 0.0;
   out_1493188658696786749[70] = 1.0;
   out_1493188658696786749[71] = 0.0;
   out_1493188658696786749[72] = 0.0;
   out_1493188658696786749[73] = 0.0;
   out_1493188658696786749[74] = 0.0;
   out_1493188658696786749[75] = 0.0;
   out_1493188658696786749[76] = 0.0;
   out_1493188658696786749[77] = 0.0;
   out_1493188658696786749[78] = 0.0;
   out_1493188658696786749[79] = 0.0;
   out_1493188658696786749[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5943509684037993570) {
   out_5943509684037993570[0] = state[0];
   out_5943509684037993570[1] = state[1];
   out_5943509684037993570[2] = state[2];
   out_5943509684037993570[3] = state[3];
   out_5943509684037993570[4] = state[4];
   out_5943509684037993570[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5943509684037993570[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5943509684037993570[7] = state[7];
   out_5943509684037993570[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6240971521964326149) {
   out_6240971521964326149[0] = 1;
   out_6240971521964326149[1] = 0;
   out_6240971521964326149[2] = 0;
   out_6240971521964326149[3] = 0;
   out_6240971521964326149[4] = 0;
   out_6240971521964326149[5] = 0;
   out_6240971521964326149[6] = 0;
   out_6240971521964326149[7] = 0;
   out_6240971521964326149[8] = 0;
   out_6240971521964326149[9] = 0;
   out_6240971521964326149[10] = 1;
   out_6240971521964326149[11] = 0;
   out_6240971521964326149[12] = 0;
   out_6240971521964326149[13] = 0;
   out_6240971521964326149[14] = 0;
   out_6240971521964326149[15] = 0;
   out_6240971521964326149[16] = 0;
   out_6240971521964326149[17] = 0;
   out_6240971521964326149[18] = 0;
   out_6240971521964326149[19] = 0;
   out_6240971521964326149[20] = 1;
   out_6240971521964326149[21] = 0;
   out_6240971521964326149[22] = 0;
   out_6240971521964326149[23] = 0;
   out_6240971521964326149[24] = 0;
   out_6240971521964326149[25] = 0;
   out_6240971521964326149[26] = 0;
   out_6240971521964326149[27] = 0;
   out_6240971521964326149[28] = 0;
   out_6240971521964326149[29] = 0;
   out_6240971521964326149[30] = 1;
   out_6240971521964326149[31] = 0;
   out_6240971521964326149[32] = 0;
   out_6240971521964326149[33] = 0;
   out_6240971521964326149[34] = 0;
   out_6240971521964326149[35] = 0;
   out_6240971521964326149[36] = 0;
   out_6240971521964326149[37] = 0;
   out_6240971521964326149[38] = 0;
   out_6240971521964326149[39] = 0;
   out_6240971521964326149[40] = 1;
   out_6240971521964326149[41] = 0;
   out_6240971521964326149[42] = 0;
   out_6240971521964326149[43] = 0;
   out_6240971521964326149[44] = 0;
   out_6240971521964326149[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6240971521964326149[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6240971521964326149[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6240971521964326149[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6240971521964326149[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6240971521964326149[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6240971521964326149[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6240971521964326149[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6240971521964326149[53] = -9.8100000000000005*dt;
   out_6240971521964326149[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6240971521964326149[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6240971521964326149[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6240971521964326149[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6240971521964326149[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6240971521964326149[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6240971521964326149[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6240971521964326149[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6240971521964326149[62] = 0;
   out_6240971521964326149[63] = 0;
   out_6240971521964326149[64] = 0;
   out_6240971521964326149[65] = 0;
   out_6240971521964326149[66] = 0;
   out_6240971521964326149[67] = 0;
   out_6240971521964326149[68] = 0;
   out_6240971521964326149[69] = 0;
   out_6240971521964326149[70] = 1;
   out_6240971521964326149[71] = 0;
   out_6240971521964326149[72] = 0;
   out_6240971521964326149[73] = 0;
   out_6240971521964326149[74] = 0;
   out_6240971521964326149[75] = 0;
   out_6240971521964326149[76] = 0;
   out_6240971521964326149[77] = 0;
   out_6240971521964326149[78] = 0;
   out_6240971521964326149[79] = 0;
   out_6240971521964326149[80] = 1;
}
void h_25(double *state, double *unused, double *out_6066332368842429215) {
   out_6066332368842429215[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4603719707909587867) {
   out_4603719707909587867[0] = 0;
   out_4603719707909587867[1] = 0;
   out_4603719707909587867[2] = 0;
   out_4603719707909587867[3] = 0;
   out_4603719707909587867[4] = 0;
   out_4603719707909587867[5] = 0;
   out_4603719707909587867[6] = 1;
   out_4603719707909587867[7] = 0;
   out_4603719707909587867[8] = 0;
}
void h_24(double *state, double *unused, double *out_3848779066424665825) {
   out_3848779066424665825[0] = state[4];
   out_3848779066424665825[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2378011923930719305) {
   out_2378011923930719305[0] = 0;
   out_2378011923930719305[1] = 0;
   out_2378011923930719305[2] = 0;
   out_2378011923930719305[3] = 0;
   out_2378011923930719305[4] = 1;
   out_2378011923930719305[5] = 0;
   out_2378011923930719305[6] = 0;
   out_2378011923930719305[7] = 0;
   out_2378011923930719305[8] = 0;
   out_2378011923930719305[9] = 0;
   out_2378011923930719305[10] = 0;
   out_2378011923930719305[11] = 0;
   out_2378011923930719305[12] = 0;
   out_2378011923930719305[13] = 0;
   out_2378011923930719305[14] = 1;
   out_2378011923930719305[15] = 0;
   out_2378011923930719305[16] = 0;
   out_2378011923930719305[17] = 0;
}
void h_30(double *state, double *unused, double *out_6341526431126935104) {
   out_6341526431126935104[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2312970633582028888) {
   out_2312970633582028888[0] = 0;
   out_2312970633582028888[1] = 0;
   out_2312970633582028888[2] = 0;
   out_2312970633582028888[3] = 0;
   out_2312970633582028888[4] = 1;
   out_2312970633582028888[5] = 0;
   out_2312970633582028888[6] = 0;
   out_2312970633582028888[7] = 0;
   out_2312970633582028888[8] = 0;
}
void h_26(double *state, double *unused, double *out_7509270232203076841) {
   out_7509270232203076841[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8345223026783644091) {
   out_8345223026783644091[0] = 0;
   out_8345223026783644091[1] = 0;
   out_8345223026783644091[2] = 0;
   out_8345223026783644091[3] = 0;
   out_8345223026783644091[4] = 0;
   out_8345223026783644091[5] = 0;
   out_8345223026783644091[6] = 0;
   out_8345223026783644091[7] = 1;
   out_8345223026783644091[8] = 0;
}
void h_27(double *state, double *unused, double *out_4731066531555788059) {
   out_4731066531555788059[0] = state[3];
}
void H_27(double *state, double *unused, double *out_138207321781603977) {
   out_138207321781603977[0] = 0;
   out_138207321781603977[1] = 0;
   out_138207321781603977[2] = 0;
   out_138207321781603977[3] = 1;
   out_138207321781603977[4] = 0;
   out_138207321781603977[5] = 0;
   out_138207321781603977[6] = 0;
   out_138207321781603977[7] = 0;
   out_138207321781603977[8] = 0;
}
void h_29(double *state, double *unused, double *out_869383055127286407) {
   out_869383055127286407[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2823201977896421072) {
   out_2823201977896421072[0] = 0;
   out_2823201977896421072[1] = 1;
   out_2823201977896421072[2] = 0;
   out_2823201977896421072[3] = 0;
   out_2823201977896421072[4] = 0;
   out_2823201977896421072[5] = 0;
   out_2823201977896421072[6] = 0;
   out_2823201977896421072[7] = 0;
   out_2823201977896421072[8] = 0;
}
void h_28(double *state, double *unused, double *out_2023156983307100891) {
   out_2023156983307100891[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2259197039173109502) {
   out_2259197039173109502[0] = 1;
   out_2259197039173109502[1] = 0;
   out_2259197039173109502[2] = 0;
   out_2259197039173109502[3] = 0;
   out_2259197039173109502[4] = 0;
   out_2259197039173109502[5] = 0;
   out_2259197039173109502[6] = 0;
   out_2259197039173109502[7] = 0;
   out_2259197039173109502[8] = 0;
}
void h_31(double *state, double *unused, double *out_2428882840588406865) {
   out_2428882840588406865[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4573073746032627439) {
   out_4573073746032627439[0] = 0;
   out_4573073746032627439[1] = 0;
   out_4573073746032627439[2] = 0;
   out_4573073746032627439[3] = 0;
   out_4573073746032627439[4] = 0;
   out_4573073746032627439[5] = 0;
   out_4573073746032627439[6] = 0;
   out_4573073746032627439[7] = 0;
   out_4573073746032627439[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2600768462618711997) {
  err_fun(nom_x, delta_x, out_2600768462618711997);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7259494313163356603) {
  inv_err_fun(nom_x, true_x, out_7259494313163356603);
}
void car_H_mod_fun(double *state, double *out_1493188658696786749) {
  H_mod_fun(state, out_1493188658696786749);
}
void car_f_fun(double *state, double dt, double *out_5943509684037993570) {
  f_fun(state,  dt, out_5943509684037993570);
}
void car_F_fun(double *state, double dt, double *out_6240971521964326149) {
  F_fun(state,  dt, out_6240971521964326149);
}
void car_h_25(double *state, double *unused, double *out_6066332368842429215) {
  h_25(state, unused, out_6066332368842429215);
}
void car_H_25(double *state, double *unused, double *out_4603719707909587867) {
  H_25(state, unused, out_4603719707909587867);
}
void car_h_24(double *state, double *unused, double *out_3848779066424665825) {
  h_24(state, unused, out_3848779066424665825);
}
void car_H_24(double *state, double *unused, double *out_2378011923930719305) {
  H_24(state, unused, out_2378011923930719305);
}
void car_h_30(double *state, double *unused, double *out_6341526431126935104) {
  h_30(state, unused, out_6341526431126935104);
}
void car_H_30(double *state, double *unused, double *out_2312970633582028888) {
  H_30(state, unused, out_2312970633582028888);
}
void car_h_26(double *state, double *unused, double *out_7509270232203076841) {
  h_26(state, unused, out_7509270232203076841);
}
void car_H_26(double *state, double *unused, double *out_8345223026783644091) {
  H_26(state, unused, out_8345223026783644091);
}
void car_h_27(double *state, double *unused, double *out_4731066531555788059) {
  h_27(state, unused, out_4731066531555788059);
}
void car_H_27(double *state, double *unused, double *out_138207321781603977) {
  H_27(state, unused, out_138207321781603977);
}
void car_h_29(double *state, double *unused, double *out_869383055127286407) {
  h_29(state, unused, out_869383055127286407);
}
void car_H_29(double *state, double *unused, double *out_2823201977896421072) {
  H_29(state, unused, out_2823201977896421072);
}
void car_h_28(double *state, double *unused, double *out_2023156983307100891) {
  h_28(state, unused, out_2023156983307100891);
}
void car_H_28(double *state, double *unused, double *out_2259197039173109502) {
  H_28(state, unused, out_2259197039173109502);
}
void car_h_31(double *state, double *unused, double *out_2428882840588406865) {
  h_31(state, unused, out_2428882840588406865);
}
void car_H_31(double *state, double *unused, double *out_4573073746032627439) {
  H_31(state, unused, out_4573073746032627439);
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
