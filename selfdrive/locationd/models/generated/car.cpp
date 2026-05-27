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
void err_fun(double *nom_x, double *delta_x, double *out_6442273530103712235) {
   out_6442273530103712235[0] = delta_x[0] + nom_x[0];
   out_6442273530103712235[1] = delta_x[1] + nom_x[1];
   out_6442273530103712235[2] = delta_x[2] + nom_x[2];
   out_6442273530103712235[3] = delta_x[3] + nom_x[3];
   out_6442273530103712235[4] = delta_x[4] + nom_x[4];
   out_6442273530103712235[5] = delta_x[5] + nom_x[5];
   out_6442273530103712235[6] = delta_x[6] + nom_x[6];
   out_6442273530103712235[7] = delta_x[7] + nom_x[7];
   out_6442273530103712235[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8945695091662043361) {
   out_8945695091662043361[0] = -nom_x[0] + true_x[0];
   out_8945695091662043361[1] = -nom_x[1] + true_x[1];
   out_8945695091662043361[2] = -nom_x[2] + true_x[2];
   out_8945695091662043361[3] = -nom_x[3] + true_x[3];
   out_8945695091662043361[4] = -nom_x[4] + true_x[4];
   out_8945695091662043361[5] = -nom_x[5] + true_x[5];
   out_8945695091662043361[6] = -nom_x[6] + true_x[6];
   out_8945695091662043361[7] = -nom_x[7] + true_x[7];
   out_8945695091662043361[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_515428113062222019) {
   out_515428113062222019[0] = 1.0;
   out_515428113062222019[1] = 0.0;
   out_515428113062222019[2] = 0.0;
   out_515428113062222019[3] = 0.0;
   out_515428113062222019[4] = 0.0;
   out_515428113062222019[5] = 0.0;
   out_515428113062222019[6] = 0.0;
   out_515428113062222019[7] = 0.0;
   out_515428113062222019[8] = 0.0;
   out_515428113062222019[9] = 0.0;
   out_515428113062222019[10] = 1.0;
   out_515428113062222019[11] = 0.0;
   out_515428113062222019[12] = 0.0;
   out_515428113062222019[13] = 0.0;
   out_515428113062222019[14] = 0.0;
   out_515428113062222019[15] = 0.0;
   out_515428113062222019[16] = 0.0;
   out_515428113062222019[17] = 0.0;
   out_515428113062222019[18] = 0.0;
   out_515428113062222019[19] = 0.0;
   out_515428113062222019[20] = 1.0;
   out_515428113062222019[21] = 0.0;
   out_515428113062222019[22] = 0.0;
   out_515428113062222019[23] = 0.0;
   out_515428113062222019[24] = 0.0;
   out_515428113062222019[25] = 0.0;
   out_515428113062222019[26] = 0.0;
   out_515428113062222019[27] = 0.0;
   out_515428113062222019[28] = 0.0;
   out_515428113062222019[29] = 0.0;
   out_515428113062222019[30] = 1.0;
   out_515428113062222019[31] = 0.0;
   out_515428113062222019[32] = 0.0;
   out_515428113062222019[33] = 0.0;
   out_515428113062222019[34] = 0.0;
   out_515428113062222019[35] = 0.0;
   out_515428113062222019[36] = 0.0;
   out_515428113062222019[37] = 0.0;
   out_515428113062222019[38] = 0.0;
   out_515428113062222019[39] = 0.0;
   out_515428113062222019[40] = 1.0;
   out_515428113062222019[41] = 0.0;
   out_515428113062222019[42] = 0.0;
   out_515428113062222019[43] = 0.0;
   out_515428113062222019[44] = 0.0;
   out_515428113062222019[45] = 0.0;
   out_515428113062222019[46] = 0.0;
   out_515428113062222019[47] = 0.0;
   out_515428113062222019[48] = 0.0;
   out_515428113062222019[49] = 0.0;
   out_515428113062222019[50] = 1.0;
   out_515428113062222019[51] = 0.0;
   out_515428113062222019[52] = 0.0;
   out_515428113062222019[53] = 0.0;
   out_515428113062222019[54] = 0.0;
   out_515428113062222019[55] = 0.0;
   out_515428113062222019[56] = 0.0;
   out_515428113062222019[57] = 0.0;
   out_515428113062222019[58] = 0.0;
   out_515428113062222019[59] = 0.0;
   out_515428113062222019[60] = 1.0;
   out_515428113062222019[61] = 0.0;
   out_515428113062222019[62] = 0.0;
   out_515428113062222019[63] = 0.0;
   out_515428113062222019[64] = 0.0;
   out_515428113062222019[65] = 0.0;
   out_515428113062222019[66] = 0.0;
   out_515428113062222019[67] = 0.0;
   out_515428113062222019[68] = 0.0;
   out_515428113062222019[69] = 0.0;
   out_515428113062222019[70] = 1.0;
   out_515428113062222019[71] = 0.0;
   out_515428113062222019[72] = 0.0;
   out_515428113062222019[73] = 0.0;
   out_515428113062222019[74] = 0.0;
   out_515428113062222019[75] = 0.0;
   out_515428113062222019[76] = 0.0;
   out_515428113062222019[77] = 0.0;
   out_515428113062222019[78] = 0.0;
   out_515428113062222019[79] = 0.0;
   out_515428113062222019[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_1011805063482308945) {
   out_1011805063482308945[0] = state[0];
   out_1011805063482308945[1] = state[1];
   out_1011805063482308945[2] = state[2];
   out_1011805063482308945[3] = state[3];
   out_1011805063482308945[4] = state[4];
   out_1011805063482308945[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_1011805063482308945[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_1011805063482308945[7] = state[7];
   out_1011805063482308945[8] = state[8];
}
void F_fun(double *state, double dt, double *out_5888946012615310003) {
   out_5888946012615310003[0] = 1;
   out_5888946012615310003[1] = 0;
   out_5888946012615310003[2] = 0;
   out_5888946012615310003[3] = 0;
   out_5888946012615310003[4] = 0;
   out_5888946012615310003[5] = 0;
   out_5888946012615310003[6] = 0;
   out_5888946012615310003[7] = 0;
   out_5888946012615310003[8] = 0;
   out_5888946012615310003[9] = 0;
   out_5888946012615310003[10] = 1;
   out_5888946012615310003[11] = 0;
   out_5888946012615310003[12] = 0;
   out_5888946012615310003[13] = 0;
   out_5888946012615310003[14] = 0;
   out_5888946012615310003[15] = 0;
   out_5888946012615310003[16] = 0;
   out_5888946012615310003[17] = 0;
   out_5888946012615310003[18] = 0;
   out_5888946012615310003[19] = 0;
   out_5888946012615310003[20] = 1;
   out_5888946012615310003[21] = 0;
   out_5888946012615310003[22] = 0;
   out_5888946012615310003[23] = 0;
   out_5888946012615310003[24] = 0;
   out_5888946012615310003[25] = 0;
   out_5888946012615310003[26] = 0;
   out_5888946012615310003[27] = 0;
   out_5888946012615310003[28] = 0;
   out_5888946012615310003[29] = 0;
   out_5888946012615310003[30] = 1;
   out_5888946012615310003[31] = 0;
   out_5888946012615310003[32] = 0;
   out_5888946012615310003[33] = 0;
   out_5888946012615310003[34] = 0;
   out_5888946012615310003[35] = 0;
   out_5888946012615310003[36] = 0;
   out_5888946012615310003[37] = 0;
   out_5888946012615310003[38] = 0;
   out_5888946012615310003[39] = 0;
   out_5888946012615310003[40] = 1;
   out_5888946012615310003[41] = 0;
   out_5888946012615310003[42] = 0;
   out_5888946012615310003[43] = 0;
   out_5888946012615310003[44] = 0;
   out_5888946012615310003[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_5888946012615310003[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_5888946012615310003[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5888946012615310003[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5888946012615310003[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_5888946012615310003[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_5888946012615310003[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_5888946012615310003[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_5888946012615310003[53] = -9.8100000000000005*dt;
   out_5888946012615310003[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_5888946012615310003[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_5888946012615310003[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5888946012615310003[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5888946012615310003[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_5888946012615310003[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_5888946012615310003[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_5888946012615310003[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5888946012615310003[62] = 0;
   out_5888946012615310003[63] = 0;
   out_5888946012615310003[64] = 0;
   out_5888946012615310003[65] = 0;
   out_5888946012615310003[66] = 0;
   out_5888946012615310003[67] = 0;
   out_5888946012615310003[68] = 0;
   out_5888946012615310003[69] = 0;
   out_5888946012615310003[70] = 1;
   out_5888946012615310003[71] = 0;
   out_5888946012615310003[72] = 0;
   out_5888946012615310003[73] = 0;
   out_5888946012615310003[74] = 0;
   out_5888946012615310003[75] = 0;
   out_5888946012615310003[76] = 0;
   out_5888946012615310003[77] = 0;
   out_5888946012615310003[78] = 0;
   out_5888946012615310003[79] = 0;
   out_5888946012615310003[80] = 1;
}
void h_25(double *state, double *unused, double *out_765665439417021084) {
   out_765665439417021084[0] = state[6];
}
void H_25(double *state, double *unused, double *out_10093670861925307) {
   out_10093670861925307[0] = 0;
   out_10093670861925307[1] = 0;
   out_10093670861925307[2] = 0;
   out_10093670861925307[3] = 0;
   out_10093670861925307[4] = 0;
   out_10093670861925307[5] = 0;
   out_10093670861925307[6] = 1;
   out_10093670861925307[7] = 0;
   out_10093670861925307[8] = 0;
}
void h_24(double *state, double *unused, double *out_7010003887632078552) {
   out_7010003887632078552[0] = state[4];
   out_7010003887632078552[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8784986078674096201) {
   out_8784986078674096201[0] = 0;
   out_8784986078674096201[1] = 0;
   out_8784986078674096201[2] = 0;
   out_8784986078674096201[3] = 0;
   out_8784986078674096201[4] = 1;
   out_8784986078674096201[5] = 0;
   out_8784986078674096201[6] = 0;
   out_8784986078674096201[7] = 0;
   out_8784986078674096201[8] = 0;
   out_8784986078674096201[9] = 0;
   out_8784986078674096201[10] = 0;
   out_8784986078674096201[11] = 0;
   out_8784986078674096201[12] = 0;
   out_8784986078674096201[13] = 0;
   out_8784986078674096201[14] = 1;
   out_8784986078674096201[15] = 0;
   out_8784986078674096201[16] = 0;
   out_8784986078674096201[17] = 0;
}
void h_30(double *state, double *unused, double *out_3713391429772506045) {
   out_3713391429772506045[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6906596670629691448) {
   out_6906596670629691448[0] = 0;
   out_6906596670629691448[1] = 0;
   out_6906596670629691448[2] = 0;
   out_6906596670629691448[3] = 0;
   out_6906596670629691448[4] = 1;
   out_6906596670629691448[5] = 0;
   out_6906596670629691448[6] = 0;
   out_6906596670629691448[7] = 0;
   out_6906596670629691448[8] = 0;
}
void h_26(double *state, double *unused, double *out_6525943533042359428) {
   out_6525943533042359428[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3751596989735981531) {
   out_3751596989735981531[0] = 0;
   out_3751596989735981531[1] = 0;
   out_3751596989735981531[2] = 0;
   out_3751596989735981531[3] = 0;
   out_3751596989735981531[4] = 0;
   out_3751596989735981531[5] = 0;
   out_3751596989735981531[6] = 0;
   out_3751596989735981531[7] = 1;
   out_3751596989735981531[8] = 0;
}
void h_27(double *state, double *unused, double *out_3564565336305065623) {
   out_3564565336305065623[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4731833358829266537) {
   out_4731833358829266537[0] = 0;
   out_4731833358829266537[1] = 0;
   out_4731833358829266537[2] = 0;
   out_4731833358829266537[3] = 1;
   out_4731833358829266537[4] = 0;
   out_4731833358829266537[5] = 0;
   out_4731833358829266537[6] = 0;
   out_4731833358829266537[7] = 0;
   out_4731833358829266537[8] = 0;
}
void h_29(double *state, double *unused, double *out_4316707314448983562) {
   out_4316707314448983562[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7416828014944083632) {
   out_7416828014944083632[0] = 0;
   out_7416828014944083632[1] = 1;
   out_7416828014944083632[2] = 0;
   out_7416828014944083632[3] = 0;
   out_7416828014944083632[4] = 0;
   out_7416828014944083632[5] = 0;
   out_7416828014944083632[6] = 0;
   out_7416828014944083632[7] = 0;
   out_7416828014944083632[8] = 0;
}
void h_28(double *state, double *unused, double *out_8899254898098344240) {
   out_8899254898098344240[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2063928385109815070) {
   out_2063928385109815070[0] = 1;
   out_2063928385109815070[1] = 0;
   out_2063928385109815070[2] = 0;
   out_2063928385109815070[3] = 0;
   out_2063928385109815070[4] = 0;
   out_2063928385109815070[5] = 0;
   out_2063928385109815070[6] = 0;
   out_2063928385109815070[7] = 0;
   out_2063928385109815070[8] = 0;
}
void h_31(double *state, double *unused, double *out_7115607211337028101) {
   out_7115607211337028101[0] = state[8];
}
void H_31(double *state, double *unused, double *out_20552291015035121) {
   out_20552291015035121[0] = 0;
   out_20552291015035121[1] = 0;
   out_20552291015035121[2] = 0;
   out_20552291015035121[3] = 0;
   out_20552291015035121[4] = 0;
   out_20552291015035121[5] = 0;
   out_20552291015035121[6] = 0;
   out_20552291015035121[7] = 0;
   out_20552291015035121[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_6442273530103712235) {
  err_fun(nom_x, delta_x, out_6442273530103712235);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8945695091662043361) {
  inv_err_fun(nom_x, true_x, out_8945695091662043361);
}
void car_H_mod_fun(double *state, double *out_515428113062222019) {
  H_mod_fun(state, out_515428113062222019);
}
void car_f_fun(double *state, double dt, double *out_1011805063482308945) {
  f_fun(state,  dt, out_1011805063482308945);
}
void car_F_fun(double *state, double dt, double *out_5888946012615310003) {
  F_fun(state,  dt, out_5888946012615310003);
}
void car_h_25(double *state, double *unused, double *out_765665439417021084) {
  h_25(state, unused, out_765665439417021084);
}
void car_H_25(double *state, double *unused, double *out_10093670861925307) {
  H_25(state, unused, out_10093670861925307);
}
void car_h_24(double *state, double *unused, double *out_7010003887632078552) {
  h_24(state, unused, out_7010003887632078552);
}
void car_H_24(double *state, double *unused, double *out_8784986078674096201) {
  H_24(state, unused, out_8784986078674096201);
}
void car_h_30(double *state, double *unused, double *out_3713391429772506045) {
  h_30(state, unused, out_3713391429772506045);
}
void car_H_30(double *state, double *unused, double *out_6906596670629691448) {
  H_30(state, unused, out_6906596670629691448);
}
void car_h_26(double *state, double *unused, double *out_6525943533042359428) {
  h_26(state, unused, out_6525943533042359428);
}
void car_H_26(double *state, double *unused, double *out_3751596989735981531) {
  H_26(state, unused, out_3751596989735981531);
}
void car_h_27(double *state, double *unused, double *out_3564565336305065623) {
  h_27(state, unused, out_3564565336305065623);
}
void car_H_27(double *state, double *unused, double *out_4731833358829266537) {
  H_27(state, unused, out_4731833358829266537);
}
void car_h_29(double *state, double *unused, double *out_4316707314448983562) {
  h_29(state, unused, out_4316707314448983562);
}
void car_H_29(double *state, double *unused, double *out_7416828014944083632) {
  H_29(state, unused, out_7416828014944083632);
}
void car_h_28(double *state, double *unused, double *out_8899254898098344240) {
  h_28(state, unused, out_8899254898098344240);
}
void car_H_28(double *state, double *unused, double *out_2063928385109815070) {
  H_28(state, unused, out_2063928385109815070);
}
void car_h_31(double *state, double *unused, double *out_7115607211337028101) {
  h_31(state, unused, out_7115607211337028101);
}
void car_H_31(double *state, double *unused, double *out_20552291015035121) {
  H_31(state, unused, out_20552291015035121);
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
