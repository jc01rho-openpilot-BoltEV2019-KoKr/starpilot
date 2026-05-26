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
void err_fun(double *nom_x, double *delta_x, double *out_7371356248284686223) {
   out_7371356248284686223[0] = delta_x[0] + nom_x[0];
   out_7371356248284686223[1] = delta_x[1] + nom_x[1];
   out_7371356248284686223[2] = delta_x[2] + nom_x[2];
   out_7371356248284686223[3] = delta_x[3] + nom_x[3];
   out_7371356248284686223[4] = delta_x[4] + nom_x[4];
   out_7371356248284686223[5] = delta_x[5] + nom_x[5];
   out_7371356248284686223[6] = delta_x[6] + nom_x[6];
   out_7371356248284686223[7] = delta_x[7] + nom_x[7];
   out_7371356248284686223[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3965605218365756510) {
   out_3965605218365756510[0] = -nom_x[0] + true_x[0];
   out_3965605218365756510[1] = -nom_x[1] + true_x[1];
   out_3965605218365756510[2] = -nom_x[2] + true_x[2];
   out_3965605218365756510[3] = -nom_x[3] + true_x[3];
   out_3965605218365756510[4] = -nom_x[4] + true_x[4];
   out_3965605218365756510[5] = -nom_x[5] + true_x[5];
   out_3965605218365756510[6] = -nom_x[6] + true_x[6];
   out_3965605218365756510[7] = -nom_x[7] + true_x[7];
   out_3965605218365756510[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2474093599384348200) {
   out_2474093599384348200[0] = 1.0;
   out_2474093599384348200[1] = 0.0;
   out_2474093599384348200[2] = 0.0;
   out_2474093599384348200[3] = 0.0;
   out_2474093599384348200[4] = 0.0;
   out_2474093599384348200[5] = 0.0;
   out_2474093599384348200[6] = 0.0;
   out_2474093599384348200[7] = 0.0;
   out_2474093599384348200[8] = 0.0;
   out_2474093599384348200[9] = 0.0;
   out_2474093599384348200[10] = 1.0;
   out_2474093599384348200[11] = 0.0;
   out_2474093599384348200[12] = 0.0;
   out_2474093599384348200[13] = 0.0;
   out_2474093599384348200[14] = 0.0;
   out_2474093599384348200[15] = 0.0;
   out_2474093599384348200[16] = 0.0;
   out_2474093599384348200[17] = 0.0;
   out_2474093599384348200[18] = 0.0;
   out_2474093599384348200[19] = 0.0;
   out_2474093599384348200[20] = 1.0;
   out_2474093599384348200[21] = 0.0;
   out_2474093599384348200[22] = 0.0;
   out_2474093599384348200[23] = 0.0;
   out_2474093599384348200[24] = 0.0;
   out_2474093599384348200[25] = 0.0;
   out_2474093599384348200[26] = 0.0;
   out_2474093599384348200[27] = 0.0;
   out_2474093599384348200[28] = 0.0;
   out_2474093599384348200[29] = 0.0;
   out_2474093599384348200[30] = 1.0;
   out_2474093599384348200[31] = 0.0;
   out_2474093599384348200[32] = 0.0;
   out_2474093599384348200[33] = 0.0;
   out_2474093599384348200[34] = 0.0;
   out_2474093599384348200[35] = 0.0;
   out_2474093599384348200[36] = 0.0;
   out_2474093599384348200[37] = 0.0;
   out_2474093599384348200[38] = 0.0;
   out_2474093599384348200[39] = 0.0;
   out_2474093599384348200[40] = 1.0;
   out_2474093599384348200[41] = 0.0;
   out_2474093599384348200[42] = 0.0;
   out_2474093599384348200[43] = 0.0;
   out_2474093599384348200[44] = 0.0;
   out_2474093599384348200[45] = 0.0;
   out_2474093599384348200[46] = 0.0;
   out_2474093599384348200[47] = 0.0;
   out_2474093599384348200[48] = 0.0;
   out_2474093599384348200[49] = 0.0;
   out_2474093599384348200[50] = 1.0;
   out_2474093599384348200[51] = 0.0;
   out_2474093599384348200[52] = 0.0;
   out_2474093599384348200[53] = 0.0;
   out_2474093599384348200[54] = 0.0;
   out_2474093599384348200[55] = 0.0;
   out_2474093599384348200[56] = 0.0;
   out_2474093599384348200[57] = 0.0;
   out_2474093599384348200[58] = 0.0;
   out_2474093599384348200[59] = 0.0;
   out_2474093599384348200[60] = 1.0;
   out_2474093599384348200[61] = 0.0;
   out_2474093599384348200[62] = 0.0;
   out_2474093599384348200[63] = 0.0;
   out_2474093599384348200[64] = 0.0;
   out_2474093599384348200[65] = 0.0;
   out_2474093599384348200[66] = 0.0;
   out_2474093599384348200[67] = 0.0;
   out_2474093599384348200[68] = 0.0;
   out_2474093599384348200[69] = 0.0;
   out_2474093599384348200[70] = 1.0;
   out_2474093599384348200[71] = 0.0;
   out_2474093599384348200[72] = 0.0;
   out_2474093599384348200[73] = 0.0;
   out_2474093599384348200[74] = 0.0;
   out_2474093599384348200[75] = 0.0;
   out_2474093599384348200[76] = 0.0;
   out_2474093599384348200[77] = 0.0;
   out_2474093599384348200[78] = 0.0;
   out_2474093599384348200[79] = 0.0;
   out_2474093599384348200[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2271815562821462998) {
   out_2271815562821462998[0] = state[0];
   out_2271815562821462998[1] = state[1];
   out_2271815562821462998[2] = state[2];
   out_2271815562821462998[3] = state[3];
   out_2271815562821462998[4] = state[4];
   out_2271815562821462998[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2271815562821462998[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2271815562821462998[7] = state[7];
   out_2271815562821462998[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7600503497871632413) {
   out_7600503497871632413[0] = 1;
   out_7600503497871632413[1] = 0;
   out_7600503497871632413[2] = 0;
   out_7600503497871632413[3] = 0;
   out_7600503497871632413[4] = 0;
   out_7600503497871632413[5] = 0;
   out_7600503497871632413[6] = 0;
   out_7600503497871632413[7] = 0;
   out_7600503497871632413[8] = 0;
   out_7600503497871632413[9] = 0;
   out_7600503497871632413[10] = 1;
   out_7600503497871632413[11] = 0;
   out_7600503497871632413[12] = 0;
   out_7600503497871632413[13] = 0;
   out_7600503497871632413[14] = 0;
   out_7600503497871632413[15] = 0;
   out_7600503497871632413[16] = 0;
   out_7600503497871632413[17] = 0;
   out_7600503497871632413[18] = 0;
   out_7600503497871632413[19] = 0;
   out_7600503497871632413[20] = 1;
   out_7600503497871632413[21] = 0;
   out_7600503497871632413[22] = 0;
   out_7600503497871632413[23] = 0;
   out_7600503497871632413[24] = 0;
   out_7600503497871632413[25] = 0;
   out_7600503497871632413[26] = 0;
   out_7600503497871632413[27] = 0;
   out_7600503497871632413[28] = 0;
   out_7600503497871632413[29] = 0;
   out_7600503497871632413[30] = 1;
   out_7600503497871632413[31] = 0;
   out_7600503497871632413[32] = 0;
   out_7600503497871632413[33] = 0;
   out_7600503497871632413[34] = 0;
   out_7600503497871632413[35] = 0;
   out_7600503497871632413[36] = 0;
   out_7600503497871632413[37] = 0;
   out_7600503497871632413[38] = 0;
   out_7600503497871632413[39] = 0;
   out_7600503497871632413[40] = 1;
   out_7600503497871632413[41] = 0;
   out_7600503497871632413[42] = 0;
   out_7600503497871632413[43] = 0;
   out_7600503497871632413[44] = 0;
   out_7600503497871632413[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7600503497871632413[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7600503497871632413[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7600503497871632413[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7600503497871632413[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7600503497871632413[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7600503497871632413[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7600503497871632413[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7600503497871632413[53] = -9.8100000000000005*dt;
   out_7600503497871632413[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7600503497871632413[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7600503497871632413[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7600503497871632413[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7600503497871632413[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7600503497871632413[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7600503497871632413[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7600503497871632413[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7600503497871632413[62] = 0;
   out_7600503497871632413[63] = 0;
   out_7600503497871632413[64] = 0;
   out_7600503497871632413[65] = 0;
   out_7600503497871632413[66] = 0;
   out_7600503497871632413[67] = 0;
   out_7600503497871632413[68] = 0;
   out_7600503497871632413[69] = 0;
   out_7600503497871632413[70] = 1;
   out_7600503497871632413[71] = 0;
   out_7600503497871632413[72] = 0;
   out_7600503497871632413[73] = 0;
   out_7600503497871632413[74] = 0;
   out_7600503497871632413[75] = 0;
   out_7600503497871632413[76] = 0;
   out_7600503497871632413[77] = 0;
   out_7600503497871632413[78] = 0;
   out_7600503497871632413[79] = 0;
   out_7600503497871632413[80] = 1;
}
void h_25(double *state, double *unused, double *out_2245281936356175607) {
   out_2245281936356175607[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7377785424569013040) {
   out_7377785424569013040[0] = 0;
   out_7377785424569013040[1] = 0;
   out_7377785424569013040[2] = 0;
   out_7377785424569013040[3] = 0;
   out_7377785424569013040[4] = 0;
   out_7377785424569013040[5] = 0;
   out_7377785424569013040[6] = 1;
   out_7377785424569013040[7] = 0;
   out_7377785424569013040[8] = 0;
}
void h_24(double *state, double *unused, double *out_5229861498965331368) {
   out_5229861498965331368[0] = state[4];
   out_5229861498965331368[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4493386842549020475) {
   out_4493386842549020475[0] = 0;
   out_4493386842549020475[1] = 0;
   out_4493386842549020475[2] = 0;
   out_4493386842549020475[3] = 0;
   out_4493386842549020475[4] = 1;
   out_4493386842549020475[5] = 0;
   out_4493386842549020475[6] = 0;
   out_4493386842549020475[7] = 0;
   out_4493386842549020475[8] = 0;
   out_4493386842549020475[9] = 0;
   out_4493386842549020475[10] = 0;
   out_4493386842549020475[11] = 0;
   out_4493386842549020475[12] = 0;
   out_4493386842549020475[13] = 0;
   out_4493386842549020475[14] = 1;
   out_4493386842549020475[15] = 0;
   out_4493386842549020475[16] = 0;
   out_4493386842549020475[17] = 0;
}
void h_30(double *state, double *unused, double *out_9036311057795238262) {
   out_9036311057795238262[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8550625690633289949) {
   out_8550625690633289949[0] = 0;
   out_8550625690633289949[1] = 0;
   out_8550625690633289949[2] = 0;
   out_8550625690633289949[3] = 0;
   out_8550625690633289949[4] = 1;
   out_8550625690633289949[5] = 0;
   out_8550625690633289949[6] = 0;
   out_8550625690633289949[7] = 0;
   out_8550625690633289949[8] = 0;
}
void h_26(double *state, double *unused, double *out_8466923163012650919) {
   out_8466923163012650919[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7764432679379737975) {
   out_7764432679379737975[0] = 0;
   out_7764432679379737975[1] = 0;
   out_7764432679379737975[2] = 0;
   out_7764432679379737975[3] = 0;
   out_7764432679379737975[4] = 0;
   out_7764432679379737975[5] = 0;
   out_7764432679379737975[6] = 0;
   out_7764432679379737975[7] = 1;
   out_7764432679379737975[8] = 0;
}
void h_27(double *state, double *unused, double *out_2036281904887484901) {
   out_2036281904887484901[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6327031619449346732) {
   out_6327031619449346732[0] = 0;
   out_6327031619449346732[1] = 0;
   out_6327031619449346732[2] = 0;
   out_6327031619449346732[3] = 1;
   out_6327031619449346732[4] = 0;
   out_6327031619449346732[5] = 0;
   out_6327031619449346732[6] = 0;
   out_6327031619449346732[7] = 0;
   out_6327031619449346732[8] = 0;
}
void h_29(double *state, double *unused, double *out_7562339341438508014) {
   out_7562339341438508014[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8040394346318897765) {
   out_8040394346318897765[0] = 0;
   out_8040394346318897765[1] = 1;
   out_8040394346318897765[2] = 0;
   out_8040394346318897765[3] = 0;
   out_8040394346318897765[4] = 0;
   out_8040394346318897765[5] = 0;
   out_8040394346318897765[6] = 0;
   out_8040394346318897765[7] = 0;
   out_8040394346318897765[8] = 0;
}
void h_28(double *state, double *unused, double *out_2481951949823838038) {
   out_2481951949823838038[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5323950710321123277) {
   out_5323950710321123277[0] = 1;
   out_5323950710321123277[1] = 0;
   out_5323950710321123277[2] = 0;
   out_5323950710321123277[3] = 0;
   out_5323950710321123277[4] = 0;
   out_5323950710321123277[5] = 0;
   out_5323950710321123277[6] = 0;
   out_5323950710321123277[7] = 0;
   out_5323950710321123277[8] = 0;
}
void h_31(double *state, double *unused, double *out_5123667467256710023) {
   out_5123667467256710023[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7408431386445973468) {
   out_7408431386445973468[0] = 0;
   out_7408431386445973468[1] = 0;
   out_7408431386445973468[2] = 0;
   out_7408431386445973468[3] = 0;
   out_7408431386445973468[4] = 0;
   out_7408431386445973468[5] = 0;
   out_7408431386445973468[6] = 0;
   out_7408431386445973468[7] = 0;
   out_7408431386445973468[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7371356248284686223) {
  err_fun(nom_x, delta_x, out_7371356248284686223);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3965605218365756510) {
  inv_err_fun(nom_x, true_x, out_3965605218365756510);
}
void car_H_mod_fun(double *state, double *out_2474093599384348200) {
  H_mod_fun(state, out_2474093599384348200);
}
void car_f_fun(double *state, double dt, double *out_2271815562821462998) {
  f_fun(state,  dt, out_2271815562821462998);
}
void car_F_fun(double *state, double dt, double *out_7600503497871632413) {
  F_fun(state,  dt, out_7600503497871632413);
}
void car_h_25(double *state, double *unused, double *out_2245281936356175607) {
  h_25(state, unused, out_2245281936356175607);
}
void car_H_25(double *state, double *unused, double *out_7377785424569013040) {
  H_25(state, unused, out_7377785424569013040);
}
void car_h_24(double *state, double *unused, double *out_5229861498965331368) {
  h_24(state, unused, out_5229861498965331368);
}
void car_H_24(double *state, double *unused, double *out_4493386842549020475) {
  H_24(state, unused, out_4493386842549020475);
}
void car_h_30(double *state, double *unused, double *out_9036311057795238262) {
  h_30(state, unused, out_9036311057795238262);
}
void car_H_30(double *state, double *unused, double *out_8550625690633289949) {
  H_30(state, unused, out_8550625690633289949);
}
void car_h_26(double *state, double *unused, double *out_8466923163012650919) {
  h_26(state, unused, out_8466923163012650919);
}
void car_H_26(double *state, double *unused, double *out_7764432679379737975) {
  H_26(state, unused, out_7764432679379737975);
}
void car_h_27(double *state, double *unused, double *out_2036281904887484901) {
  h_27(state, unused, out_2036281904887484901);
}
void car_H_27(double *state, double *unused, double *out_6327031619449346732) {
  H_27(state, unused, out_6327031619449346732);
}
void car_h_29(double *state, double *unused, double *out_7562339341438508014) {
  h_29(state, unused, out_7562339341438508014);
}
void car_H_29(double *state, double *unused, double *out_8040394346318897765) {
  H_29(state, unused, out_8040394346318897765);
}
void car_h_28(double *state, double *unused, double *out_2481951949823838038) {
  h_28(state, unused, out_2481951949823838038);
}
void car_H_28(double *state, double *unused, double *out_5323950710321123277) {
  H_28(state, unused, out_5323950710321123277);
}
void car_h_31(double *state, double *unused, double *out_5123667467256710023) {
  h_31(state, unused, out_5123667467256710023);
}
void car_H_31(double *state, double *unused, double *out_7408431386445973468) {
  H_31(state, unused, out_7408431386445973468);
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
