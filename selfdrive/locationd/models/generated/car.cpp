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
void err_fun(double *nom_x, double *delta_x, double *out_6201369500890241283) {
   out_6201369500890241283[0] = delta_x[0] + nom_x[0];
   out_6201369500890241283[1] = delta_x[1] + nom_x[1];
   out_6201369500890241283[2] = delta_x[2] + nom_x[2];
   out_6201369500890241283[3] = delta_x[3] + nom_x[3];
   out_6201369500890241283[4] = delta_x[4] + nom_x[4];
   out_6201369500890241283[5] = delta_x[5] + nom_x[5];
   out_6201369500890241283[6] = delta_x[6] + nom_x[6];
   out_6201369500890241283[7] = delta_x[7] + nom_x[7];
   out_6201369500890241283[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6748403134246456124) {
   out_6748403134246456124[0] = -nom_x[0] + true_x[0];
   out_6748403134246456124[1] = -nom_x[1] + true_x[1];
   out_6748403134246456124[2] = -nom_x[2] + true_x[2];
   out_6748403134246456124[3] = -nom_x[3] + true_x[3];
   out_6748403134246456124[4] = -nom_x[4] + true_x[4];
   out_6748403134246456124[5] = -nom_x[5] + true_x[5];
   out_6748403134246456124[6] = -nom_x[6] + true_x[6];
   out_6748403134246456124[7] = -nom_x[7] + true_x[7];
   out_6748403134246456124[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2042585132715859694) {
   out_2042585132715859694[0] = 1.0;
   out_2042585132715859694[1] = 0.0;
   out_2042585132715859694[2] = 0.0;
   out_2042585132715859694[3] = 0.0;
   out_2042585132715859694[4] = 0.0;
   out_2042585132715859694[5] = 0.0;
   out_2042585132715859694[6] = 0.0;
   out_2042585132715859694[7] = 0.0;
   out_2042585132715859694[8] = 0.0;
   out_2042585132715859694[9] = 0.0;
   out_2042585132715859694[10] = 1.0;
   out_2042585132715859694[11] = 0.0;
   out_2042585132715859694[12] = 0.0;
   out_2042585132715859694[13] = 0.0;
   out_2042585132715859694[14] = 0.0;
   out_2042585132715859694[15] = 0.0;
   out_2042585132715859694[16] = 0.0;
   out_2042585132715859694[17] = 0.0;
   out_2042585132715859694[18] = 0.0;
   out_2042585132715859694[19] = 0.0;
   out_2042585132715859694[20] = 1.0;
   out_2042585132715859694[21] = 0.0;
   out_2042585132715859694[22] = 0.0;
   out_2042585132715859694[23] = 0.0;
   out_2042585132715859694[24] = 0.0;
   out_2042585132715859694[25] = 0.0;
   out_2042585132715859694[26] = 0.0;
   out_2042585132715859694[27] = 0.0;
   out_2042585132715859694[28] = 0.0;
   out_2042585132715859694[29] = 0.0;
   out_2042585132715859694[30] = 1.0;
   out_2042585132715859694[31] = 0.0;
   out_2042585132715859694[32] = 0.0;
   out_2042585132715859694[33] = 0.0;
   out_2042585132715859694[34] = 0.0;
   out_2042585132715859694[35] = 0.0;
   out_2042585132715859694[36] = 0.0;
   out_2042585132715859694[37] = 0.0;
   out_2042585132715859694[38] = 0.0;
   out_2042585132715859694[39] = 0.0;
   out_2042585132715859694[40] = 1.0;
   out_2042585132715859694[41] = 0.0;
   out_2042585132715859694[42] = 0.0;
   out_2042585132715859694[43] = 0.0;
   out_2042585132715859694[44] = 0.0;
   out_2042585132715859694[45] = 0.0;
   out_2042585132715859694[46] = 0.0;
   out_2042585132715859694[47] = 0.0;
   out_2042585132715859694[48] = 0.0;
   out_2042585132715859694[49] = 0.0;
   out_2042585132715859694[50] = 1.0;
   out_2042585132715859694[51] = 0.0;
   out_2042585132715859694[52] = 0.0;
   out_2042585132715859694[53] = 0.0;
   out_2042585132715859694[54] = 0.0;
   out_2042585132715859694[55] = 0.0;
   out_2042585132715859694[56] = 0.0;
   out_2042585132715859694[57] = 0.0;
   out_2042585132715859694[58] = 0.0;
   out_2042585132715859694[59] = 0.0;
   out_2042585132715859694[60] = 1.0;
   out_2042585132715859694[61] = 0.0;
   out_2042585132715859694[62] = 0.0;
   out_2042585132715859694[63] = 0.0;
   out_2042585132715859694[64] = 0.0;
   out_2042585132715859694[65] = 0.0;
   out_2042585132715859694[66] = 0.0;
   out_2042585132715859694[67] = 0.0;
   out_2042585132715859694[68] = 0.0;
   out_2042585132715859694[69] = 0.0;
   out_2042585132715859694[70] = 1.0;
   out_2042585132715859694[71] = 0.0;
   out_2042585132715859694[72] = 0.0;
   out_2042585132715859694[73] = 0.0;
   out_2042585132715859694[74] = 0.0;
   out_2042585132715859694[75] = 0.0;
   out_2042585132715859694[76] = 0.0;
   out_2042585132715859694[77] = 0.0;
   out_2042585132715859694[78] = 0.0;
   out_2042585132715859694[79] = 0.0;
   out_2042585132715859694[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4209455390444840494) {
   out_4209455390444840494[0] = state[0];
   out_4209455390444840494[1] = state[1];
   out_4209455390444840494[2] = state[2];
   out_4209455390444840494[3] = state[3];
   out_4209455390444840494[4] = state[4];
   out_4209455390444840494[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4209455390444840494[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4209455390444840494[7] = state[7];
   out_4209455390444840494[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2724900345805544233) {
   out_2724900345805544233[0] = 1;
   out_2724900345805544233[1] = 0;
   out_2724900345805544233[2] = 0;
   out_2724900345805544233[3] = 0;
   out_2724900345805544233[4] = 0;
   out_2724900345805544233[5] = 0;
   out_2724900345805544233[6] = 0;
   out_2724900345805544233[7] = 0;
   out_2724900345805544233[8] = 0;
   out_2724900345805544233[9] = 0;
   out_2724900345805544233[10] = 1;
   out_2724900345805544233[11] = 0;
   out_2724900345805544233[12] = 0;
   out_2724900345805544233[13] = 0;
   out_2724900345805544233[14] = 0;
   out_2724900345805544233[15] = 0;
   out_2724900345805544233[16] = 0;
   out_2724900345805544233[17] = 0;
   out_2724900345805544233[18] = 0;
   out_2724900345805544233[19] = 0;
   out_2724900345805544233[20] = 1;
   out_2724900345805544233[21] = 0;
   out_2724900345805544233[22] = 0;
   out_2724900345805544233[23] = 0;
   out_2724900345805544233[24] = 0;
   out_2724900345805544233[25] = 0;
   out_2724900345805544233[26] = 0;
   out_2724900345805544233[27] = 0;
   out_2724900345805544233[28] = 0;
   out_2724900345805544233[29] = 0;
   out_2724900345805544233[30] = 1;
   out_2724900345805544233[31] = 0;
   out_2724900345805544233[32] = 0;
   out_2724900345805544233[33] = 0;
   out_2724900345805544233[34] = 0;
   out_2724900345805544233[35] = 0;
   out_2724900345805544233[36] = 0;
   out_2724900345805544233[37] = 0;
   out_2724900345805544233[38] = 0;
   out_2724900345805544233[39] = 0;
   out_2724900345805544233[40] = 1;
   out_2724900345805544233[41] = 0;
   out_2724900345805544233[42] = 0;
   out_2724900345805544233[43] = 0;
   out_2724900345805544233[44] = 0;
   out_2724900345805544233[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2724900345805544233[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2724900345805544233[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2724900345805544233[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2724900345805544233[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2724900345805544233[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2724900345805544233[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2724900345805544233[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2724900345805544233[53] = -9.8100000000000005*dt;
   out_2724900345805544233[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2724900345805544233[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2724900345805544233[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2724900345805544233[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2724900345805544233[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2724900345805544233[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2724900345805544233[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2724900345805544233[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2724900345805544233[62] = 0;
   out_2724900345805544233[63] = 0;
   out_2724900345805544233[64] = 0;
   out_2724900345805544233[65] = 0;
   out_2724900345805544233[66] = 0;
   out_2724900345805544233[67] = 0;
   out_2724900345805544233[68] = 0;
   out_2724900345805544233[69] = 0;
   out_2724900345805544233[70] = 1;
   out_2724900345805544233[71] = 0;
   out_2724900345805544233[72] = 0;
   out_2724900345805544233[73] = 0;
   out_2724900345805544233[74] = 0;
   out_2724900345805544233[75] = 0;
   out_2724900345805544233[76] = 0;
   out_2724900345805544233[77] = 0;
   out_2724900345805544233[78] = 0;
   out_2724900345805544233[79] = 0;
   out_2724900345805544233[80] = 1;
}
void h_25(double *state, double *unused, double *out_2892803162940124204) {
   out_2892803162940124204[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4054323233890514922) {
   out_4054323233890514922[0] = 0;
   out_4054323233890514922[1] = 0;
   out_4054323233890514922[2] = 0;
   out_4054323233890514922[3] = 0;
   out_4054323233890514922[4] = 0;
   out_4054323233890514922[5] = 0;
   out_4054323233890514922[6] = 1;
   out_4054323233890514922[7] = 0;
   out_4054323233890514922[8] = 0;
}
void h_24(double *state, double *unused, double *out_2360383510230698975) {
   out_2360383510230698975[0] = state[4];
   out_2360383510230698975[1] = state[5];
}
void H_24(double *state, double *unused, double *out_1828615449911646360) {
   out_1828615449911646360[0] = 0;
   out_1828615449911646360[1] = 0;
   out_1828615449911646360[2] = 0;
   out_1828615449911646360[3] = 0;
   out_1828615449911646360[4] = 1;
   out_1828615449911646360[5] = 0;
   out_1828615449911646360[6] = 0;
   out_1828615449911646360[7] = 0;
   out_1828615449911646360[8] = 0;
   out_1828615449911646360[9] = 0;
   out_1828615449911646360[10] = 0;
   out_1828615449911646360[11] = 0;
   out_1828615449911646360[12] = 0;
   out_1828615449911646360[13] = 0;
   out_1828615449911646360[14] = 1;
   out_1828615449911646360[15] = 0;
   out_1828615449911646360[16] = 0;
   out_1828615449911646360[17] = 0;
}
void h_30(double *state, double *unused, double *out_801115166891129847) {
   out_801115166891129847[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2862367107601101833) {
   out_2862367107601101833[0] = 0;
   out_2862367107601101833[1] = 0;
   out_2862367107601101833[2] = 0;
   out_2862367107601101833[3] = 0;
   out_2862367107601101833[4] = 1;
   out_2862367107601101833[5] = 0;
   out_2862367107601101833[6] = 0;
   out_2862367107601101833[7] = 0;
   out_2862367107601101833[8] = 0;
}
void h_26(double *state, double *unused, double *out_1833676042436215552) {
   out_1833676042436215552[0] = state[7];
}
void H_26(double *state, double *unused, double *out_749797264129714321) {
   out_749797264129714321[0] = 0;
   out_749797264129714321[1] = 0;
   out_749797264129714321[2] = 0;
   out_749797264129714321[3] = 0;
   out_749797264129714321[4] = 0;
   out_749797264129714321[5] = 0;
   out_749797264129714321[6] = 0;
   out_749797264129714321[7] = 1;
   out_749797264129714321[8] = 0;
}
void h_27(double *state, double *unused, double *out_512631790305905855) {
   out_512631790305905855[0] = state[3];
}
void H_27(double *state, double *unused, double *out_687603795800676922) {
   out_687603795800676922[0] = 0;
   out_687603795800676922[1] = 0;
   out_687603795800676922[2] = 0;
   out_687603795800676922[3] = 1;
   out_687603795800676922[4] = 0;
   out_687603795800676922[5] = 0;
   out_687603795800676922[6] = 0;
   out_687603795800676922[7] = 0;
   out_687603795800676922[8] = 0;
}
void h_29(double *state, double *unused, double *out_355445121954776710) {
   out_355445121954776710[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3372598451915494017) {
   out_3372598451915494017[0] = 0;
   out_3372598451915494017[1] = 1;
   out_3372598451915494017[2] = 0;
   out_3372598451915494017[3] = 0;
   out_3372598451915494017[4] = 0;
   out_3372598451915494017[5] = 0;
   out_3372598451915494017[6] = 0;
   out_3372598451915494017[7] = 0;
   out_3372598451915494017[8] = 0;
}
void h_28(double *state, double *unused, double *out_4713758757429658086) {
   out_4713758757429658086[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6108157948138404685) {
   out_6108157948138404685[0] = 1;
   out_6108157948138404685[1] = 0;
   out_6108157948138404685[2] = 0;
   out_6108157948138404685[3] = 0;
   out_6108157948138404685[4] = 0;
   out_6108157948138404685[5] = 0;
   out_6108157948138404685[6] = 0;
   out_6108157948138404685[7] = 0;
   out_6108157948138404685[8] = 0;
}
void h_31(double *state, double *unused, double *out_744646365313898146) {
   out_744646365313898146[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3022352016621302331) {
   out_3022352016621302331[0] = 0;
   out_3022352016621302331[1] = 0;
   out_3022352016621302331[2] = 0;
   out_3022352016621302331[3] = 0;
   out_3022352016621302331[4] = 0;
   out_3022352016621302331[5] = 0;
   out_3022352016621302331[6] = 0;
   out_3022352016621302331[7] = 0;
   out_3022352016621302331[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_6201369500890241283) {
  err_fun(nom_x, delta_x, out_6201369500890241283);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6748403134246456124) {
  inv_err_fun(nom_x, true_x, out_6748403134246456124);
}
void car_H_mod_fun(double *state, double *out_2042585132715859694) {
  H_mod_fun(state, out_2042585132715859694);
}
void car_f_fun(double *state, double dt, double *out_4209455390444840494) {
  f_fun(state,  dt, out_4209455390444840494);
}
void car_F_fun(double *state, double dt, double *out_2724900345805544233) {
  F_fun(state,  dt, out_2724900345805544233);
}
void car_h_25(double *state, double *unused, double *out_2892803162940124204) {
  h_25(state, unused, out_2892803162940124204);
}
void car_H_25(double *state, double *unused, double *out_4054323233890514922) {
  H_25(state, unused, out_4054323233890514922);
}
void car_h_24(double *state, double *unused, double *out_2360383510230698975) {
  h_24(state, unused, out_2360383510230698975);
}
void car_H_24(double *state, double *unused, double *out_1828615449911646360) {
  H_24(state, unused, out_1828615449911646360);
}
void car_h_30(double *state, double *unused, double *out_801115166891129847) {
  h_30(state, unused, out_801115166891129847);
}
void car_H_30(double *state, double *unused, double *out_2862367107601101833) {
  H_30(state, unused, out_2862367107601101833);
}
void car_h_26(double *state, double *unused, double *out_1833676042436215552) {
  h_26(state, unused, out_1833676042436215552);
}
void car_H_26(double *state, double *unused, double *out_749797264129714321) {
  H_26(state, unused, out_749797264129714321);
}
void car_h_27(double *state, double *unused, double *out_512631790305905855) {
  h_27(state, unused, out_512631790305905855);
}
void car_H_27(double *state, double *unused, double *out_687603795800676922) {
  H_27(state, unused, out_687603795800676922);
}
void car_h_29(double *state, double *unused, double *out_355445121954776710) {
  h_29(state, unused, out_355445121954776710);
}
void car_H_29(double *state, double *unused, double *out_3372598451915494017) {
  H_29(state, unused, out_3372598451915494017);
}
void car_h_28(double *state, double *unused, double *out_4713758757429658086) {
  h_28(state, unused, out_4713758757429658086);
}
void car_H_28(double *state, double *unused, double *out_6108157948138404685) {
  H_28(state, unused, out_6108157948138404685);
}
void car_h_31(double *state, double *unused, double *out_744646365313898146) {
  h_31(state, unused, out_744646365313898146);
}
void car_H_31(double *state, double *unused, double *out_3022352016621302331) {
  H_31(state, unused, out_3022352016621302331);
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
