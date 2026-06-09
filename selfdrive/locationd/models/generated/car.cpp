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
void err_fun(double *nom_x, double *delta_x, double *out_2644531489535461779) {
   out_2644531489535461779[0] = delta_x[0] + nom_x[0];
   out_2644531489535461779[1] = delta_x[1] + nom_x[1];
   out_2644531489535461779[2] = delta_x[2] + nom_x[2];
   out_2644531489535461779[3] = delta_x[3] + nom_x[3];
   out_2644531489535461779[4] = delta_x[4] + nom_x[4];
   out_2644531489535461779[5] = delta_x[5] + nom_x[5];
   out_2644531489535461779[6] = delta_x[6] + nom_x[6];
   out_2644531489535461779[7] = delta_x[7] + nom_x[7];
   out_2644531489535461779[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1100504365402285318) {
   out_1100504365402285318[0] = -nom_x[0] + true_x[0];
   out_1100504365402285318[1] = -nom_x[1] + true_x[1];
   out_1100504365402285318[2] = -nom_x[2] + true_x[2];
   out_1100504365402285318[3] = -nom_x[3] + true_x[3];
   out_1100504365402285318[4] = -nom_x[4] + true_x[4];
   out_1100504365402285318[5] = -nom_x[5] + true_x[5];
   out_1100504365402285318[6] = -nom_x[6] + true_x[6];
   out_1100504365402285318[7] = -nom_x[7] + true_x[7];
   out_1100504365402285318[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6242485690446211568) {
   out_6242485690446211568[0] = 1.0;
   out_6242485690446211568[1] = 0.0;
   out_6242485690446211568[2] = 0.0;
   out_6242485690446211568[3] = 0.0;
   out_6242485690446211568[4] = 0.0;
   out_6242485690446211568[5] = 0.0;
   out_6242485690446211568[6] = 0.0;
   out_6242485690446211568[7] = 0.0;
   out_6242485690446211568[8] = 0.0;
   out_6242485690446211568[9] = 0.0;
   out_6242485690446211568[10] = 1.0;
   out_6242485690446211568[11] = 0.0;
   out_6242485690446211568[12] = 0.0;
   out_6242485690446211568[13] = 0.0;
   out_6242485690446211568[14] = 0.0;
   out_6242485690446211568[15] = 0.0;
   out_6242485690446211568[16] = 0.0;
   out_6242485690446211568[17] = 0.0;
   out_6242485690446211568[18] = 0.0;
   out_6242485690446211568[19] = 0.0;
   out_6242485690446211568[20] = 1.0;
   out_6242485690446211568[21] = 0.0;
   out_6242485690446211568[22] = 0.0;
   out_6242485690446211568[23] = 0.0;
   out_6242485690446211568[24] = 0.0;
   out_6242485690446211568[25] = 0.0;
   out_6242485690446211568[26] = 0.0;
   out_6242485690446211568[27] = 0.0;
   out_6242485690446211568[28] = 0.0;
   out_6242485690446211568[29] = 0.0;
   out_6242485690446211568[30] = 1.0;
   out_6242485690446211568[31] = 0.0;
   out_6242485690446211568[32] = 0.0;
   out_6242485690446211568[33] = 0.0;
   out_6242485690446211568[34] = 0.0;
   out_6242485690446211568[35] = 0.0;
   out_6242485690446211568[36] = 0.0;
   out_6242485690446211568[37] = 0.0;
   out_6242485690446211568[38] = 0.0;
   out_6242485690446211568[39] = 0.0;
   out_6242485690446211568[40] = 1.0;
   out_6242485690446211568[41] = 0.0;
   out_6242485690446211568[42] = 0.0;
   out_6242485690446211568[43] = 0.0;
   out_6242485690446211568[44] = 0.0;
   out_6242485690446211568[45] = 0.0;
   out_6242485690446211568[46] = 0.0;
   out_6242485690446211568[47] = 0.0;
   out_6242485690446211568[48] = 0.0;
   out_6242485690446211568[49] = 0.0;
   out_6242485690446211568[50] = 1.0;
   out_6242485690446211568[51] = 0.0;
   out_6242485690446211568[52] = 0.0;
   out_6242485690446211568[53] = 0.0;
   out_6242485690446211568[54] = 0.0;
   out_6242485690446211568[55] = 0.0;
   out_6242485690446211568[56] = 0.0;
   out_6242485690446211568[57] = 0.0;
   out_6242485690446211568[58] = 0.0;
   out_6242485690446211568[59] = 0.0;
   out_6242485690446211568[60] = 1.0;
   out_6242485690446211568[61] = 0.0;
   out_6242485690446211568[62] = 0.0;
   out_6242485690446211568[63] = 0.0;
   out_6242485690446211568[64] = 0.0;
   out_6242485690446211568[65] = 0.0;
   out_6242485690446211568[66] = 0.0;
   out_6242485690446211568[67] = 0.0;
   out_6242485690446211568[68] = 0.0;
   out_6242485690446211568[69] = 0.0;
   out_6242485690446211568[70] = 1.0;
   out_6242485690446211568[71] = 0.0;
   out_6242485690446211568[72] = 0.0;
   out_6242485690446211568[73] = 0.0;
   out_6242485690446211568[74] = 0.0;
   out_6242485690446211568[75] = 0.0;
   out_6242485690446211568[76] = 0.0;
   out_6242485690446211568[77] = 0.0;
   out_6242485690446211568[78] = 0.0;
   out_6242485690446211568[79] = 0.0;
   out_6242485690446211568[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3248907569765849539) {
   out_3248907569765849539[0] = state[0];
   out_3248907569765849539[1] = state[1];
   out_3248907569765849539[2] = state[2];
   out_3248907569765849539[3] = state[3];
   out_3248907569765849539[4] = state[4];
   out_3248907569765849539[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3248907569765849539[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3248907569765849539[7] = state[7];
   out_3248907569765849539[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8360719243632448897) {
   out_8360719243632448897[0] = 1;
   out_8360719243632448897[1] = 0;
   out_8360719243632448897[2] = 0;
   out_8360719243632448897[3] = 0;
   out_8360719243632448897[4] = 0;
   out_8360719243632448897[5] = 0;
   out_8360719243632448897[6] = 0;
   out_8360719243632448897[7] = 0;
   out_8360719243632448897[8] = 0;
   out_8360719243632448897[9] = 0;
   out_8360719243632448897[10] = 1;
   out_8360719243632448897[11] = 0;
   out_8360719243632448897[12] = 0;
   out_8360719243632448897[13] = 0;
   out_8360719243632448897[14] = 0;
   out_8360719243632448897[15] = 0;
   out_8360719243632448897[16] = 0;
   out_8360719243632448897[17] = 0;
   out_8360719243632448897[18] = 0;
   out_8360719243632448897[19] = 0;
   out_8360719243632448897[20] = 1;
   out_8360719243632448897[21] = 0;
   out_8360719243632448897[22] = 0;
   out_8360719243632448897[23] = 0;
   out_8360719243632448897[24] = 0;
   out_8360719243632448897[25] = 0;
   out_8360719243632448897[26] = 0;
   out_8360719243632448897[27] = 0;
   out_8360719243632448897[28] = 0;
   out_8360719243632448897[29] = 0;
   out_8360719243632448897[30] = 1;
   out_8360719243632448897[31] = 0;
   out_8360719243632448897[32] = 0;
   out_8360719243632448897[33] = 0;
   out_8360719243632448897[34] = 0;
   out_8360719243632448897[35] = 0;
   out_8360719243632448897[36] = 0;
   out_8360719243632448897[37] = 0;
   out_8360719243632448897[38] = 0;
   out_8360719243632448897[39] = 0;
   out_8360719243632448897[40] = 1;
   out_8360719243632448897[41] = 0;
   out_8360719243632448897[42] = 0;
   out_8360719243632448897[43] = 0;
   out_8360719243632448897[44] = 0;
   out_8360719243632448897[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8360719243632448897[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8360719243632448897[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8360719243632448897[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8360719243632448897[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8360719243632448897[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8360719243632448897[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8360719243632448897[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8360719243632448897[53] = -9.8100000000000005*dt;
   out_8360719243632448897[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8360719243632448897[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8360719243632448897[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8360719243632448897[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8360719243632448897[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8360719243632448897[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8360719243632448897[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8360719243632448897[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8360719243632448897[62] = 0;
   out_8360719243632448897[63] = 0;
   out_8360719243632448897[64] = 0;
   out_8360719243632448897[65] = 0;
   out_8360719243632448897[66] = 0;
   out_8360719243632448897[67] = 0;
   out_8360719243632448897[68] = 0;
   out_8360719243632448897[69] = 0;
   out_8360719243632448897[70] = 1;
   out_8360719243632448897[71] = 0;
   out_8360719243632448897[72] = 0;
   out_8360719243632448897[73] = 0;
   out_8360719243632448897[74] = 0;
   out_8360719243632448897[75] = 0;
   out_8360719243632448897[76] = 0;
   out_8360719243632448897[77] = 0;
   out_8360719243632448897[78] = 0;
   out_8360719243632448897[79] = 0;
   out_8360719243632448897[80] = 1;
}
void h_25(double *state, double *unused, double *out_8500141102228074854) {
   out_8500141102228074854[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2719505040456719891) {
   out_2719505040456719891[0] = 0;
   out_2719505040456719891[1] = 0;
   out_2719505040456719891[2] = 0;
   out_2719505040456719891[3] = 0;
   out_2719505040456719891[4] = 0;
   out_2719505040456719891[5] = 0;
   out_2719505040456719891[6] = 1;
   out_2719505040456719891[7] = 0;
   out_2719505040456719891[8] = 0;
}
void h_24(double *state, double *unused, double *out_7897313667940812561) {
   out_7897313667940812561[0] = state[4];
   out_7897313667940812561[1] = state[5];
}
void H_24(double *state, double *unused, double *out_838420558345603245) {
   out_838420558345603245[0] = 0;
   out_838420558345603245[1] = 0;
   out_838420558345603245[2] = 0;
   out_838420558345603245[3] = 0;
   out_838420558345603245[4] = 1;
   out_838420558345603245[5] = 0;
   out_838420558345603245[6] = 0;
   out_838420558345603245[7] = 0;
   out_838420558345603245[8] = 0;
   out_838420558345603245[9] = 0;
   out_838420558345603245[10] = 0;
   out_838420558345603245[11] = 0;
   out_838420558345603245[12] = 0;
   out_838420558345603245[13] = 0;
   out_838420558345603245[14] = 1;
   out_838420558345603245[15] = 0;
   out_838420558345603245[16] = 0;
   out_838420558345603245[17] = 0;
}
void h_30(double *state, double *unused, double *out_808885686797625580) {
   out_808885686797625580[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4197185301034896864) {
   out_4197185301034896864[0] = 0;
   out_4197185301034896864[1] = 0;
   out_4197185301034896864[2] = 0;
   out_4197185301034896864[3] = 0;
   out_4197185301034896864[4] = 1;
   out_4197185301034896864[5] = 0;
   out_4197185301034896864[6] = 0;
   out_4197185301034896864[7] = 0;
   out_4197185301034896864[8] = 0;
}
void h_26(double *state, double *unused, double *out_4192787580863220065) {
   out_4192787580863220065[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6461008359330776115) {
   out_6461008359330776115[0] = 0;
   out_6461008359330776115[1] = 0;
   out_6461008359330776115[2] = 0;
   out_6461008359330776115[3] = 0;
   out_6461008359330776115[4] = 0;
   out_6461008359330776115[5] = 0;
   out_6461008359330776115[6] = 0;
   out_6461008359330776115[7] = 1;
   out_6461008359330776115[8] = 0;
}
void h_27(double *state, double *unused, double *out_5889273078412295556) {
   out_5889273078412295556[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2022421989234471953) {
   out_2022421989234471953[0] = 0;
   out_2022421989234471953[1] = 0;
   out_2022421989234471953[2] = 0;
   out_2022421989234471953[3] = 1;
   out_2022421989234471953[4] = 0;
   out_2022421989234471953[5] = 0;
   out_2022421989234471953[6] = 0;
   out_2022421989234471953[7] = 0;
   out_2022421989234471953[8] = 0;
}
void h_29(double *state, double *unused, double *out_5810558954458471225) {
   out_5810558954458471225[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4707416645349289048) {
   out_4707416645349289048[0] = 0;
   out_4707416645349289048[1] = 1;
   out_4707416645349289048[2] = 0;
   out_4707416645349289048[3] = 0;
   out_4707416645349289048[4] = 0;
   out_4707416645349289048[5] = 0;
   out_4707416645349289048[6] = 0;
   out_4707416645349289048[7] = 0;
   out_4707416645349289048[8] = 0;
}
void h_28(double *state, double *unused, double *out_926893080731002324) {
   out_926893080731002324[0] = state[0];
}
void H_28(double *state, double *unused, double *out_4773339754704609654) {
   out_4773339754704609654[0] = 1;
   out_4773339754704609654[1] = 0;
   out_4773339754704609654[2] = 0;
   out_4773339754704609654[3] = 0;
   out_4773339754704609654[4] = 0;
   out_4773339754704609654[5] = 0;
   out_4773339754704609654[6] = 0;
   out_4773339754704609654[7] = 0;
   out_4773339754704609654[8] = 0;
}
void h_31(double *state, double *unused, double *out_2974083665677051741) {
   out_2974083665677051741[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2688859078579759463) {
   out_2688859078579759463[0] = 0;
   out_2688859078579759463[1] = 0;
   out_2688859078579759463[2] = 0;
   out_2688859078579759463[3] = 0;
   out_2688859078579759463[4] = 0;
   out_2688859078579759463[5] = 0;
   out_2688859078579759463[6] = 0;
   out_2688859078579759463[7] = 0;
   out_2688859078579759463[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2644531489535461779) {
  err_fun(nom_x, delta_x, out_2644531489535461779);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1100504365402285318) {
  inv_err_fun(nom_x, true_x, out_1100504365402285318);
}
void car_H_mod_fun(double *state, double *out_6242485690446211568) {
  H_mod_fun(state, out_6242485690446211568);
}
void car_f_fun(double *state, double dt, double *out_3248907569765849539) {
  f_fun(state,  dt, out_3248907569765849539);
}
void car_F_fun(double *state, double dt, double *out_8360719243632448897) {
  F_fun(state,  dt, out_8360719243632448897);
}
void car_h_25(double *state, double *unused, double *out_8500141102228074854) {
  h_25(state, unused, out_8500141102228074854);
}
void car_H_25(double *state, double *unused, double *out_2719505040456719891) {
  H_25(state, unused, out_2719505040456719891);
}
void car_h_24(double *state, double *unused, double *out_7897313667940812561) {
  h_24(state, unused, out_7897313667940812561);
}
void car_H_24(double *state, double *unused, double *out_838420558345603245) {
  H_24(state, unused, out_838420558345603245);
}
void car_h_30(double *state, double *unused, double *out_808885686797625580) {
  h_30(state, unused, out_808885686797625580);
}
void car_H_30(double *state, double *unused, double *out_4197185301034896864) {
  H_30(state, unused, out_4197185301034896864);
}
void car_h_26(double *state, double *unused, double *out_4192787580863220065) {
  h_26(state, unused, out_4192787580863220065);
}
void car_H_26(double *state, double *unused, double *out_6461008359330776115) {
  H_26(state, unused, out_6461008359330776115);
}
void car_h_27(double *state, double *unused, double *out_5889273078412295556) {
  h_27(state, unused, out_5889273078412295556);
}
void car_H_27(double *state, double *unused, double *out_2022421989234471953) {
  H_27(state, unused, out_2022421989234471953);
}
void car_h_29(double *state, double *unused, double *out_5810558954458471225) {
  h_29(state, unused, out_5810558954458471225);
}
void car_H_29(double *state, double *unused, double *out_4707416645349289048) {
  H_29(state, unused, out_4707416645349289048);
}
void car_h_28(double *state, double *unused, double *out_926893080731002324) {
  h_28(state, unused, out_926893080731002324);
}
void car_H_28(double *state, double *unused, double *out_4773339754704609654) {
  H_28(state, unused, out_4773339754704609654);
}
void car_h_31(double *state, double *unused, double *out_2974083665677051741) {
  h_31(state, unused, out_2974083665677051741);
}
void car_H_31(double *state, double *unused, double *out_2688859078579759463) {
  H_31(state, unused, out_2688859078579759463);
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
