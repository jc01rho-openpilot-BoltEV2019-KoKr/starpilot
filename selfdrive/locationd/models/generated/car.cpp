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
void err_fun(double *nom_x, double *delta_x, double *out_5406094264205448922) {
   out_5406094264205448922[0] = delta_x[0] + nom_x[0];
   out_5406094264205448922[1] = delta_x[1] + nom_x[1];
   out_5406094264205448922[2] = delta_x[2] + nom_x[2];
   out_5406094264205448922[3] = delta_x[3] + nom_x[3];
   out_5406094264205448922[4] = delta_x[4] + nom_x[4];
   out_5406094264205448922[5] = delta_x[5] + nom_x[5];
   out_5406094264205448922[6] = delta_x[6] + nom_x[6];
   out_5406094264205448922[7] = delta_x[7] + nom_x[7];
   out_5406094264205448922[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7302786751934147898) {
   out_7302786751934147898[0] = -nom_x[0] + true_x[0];
   out_7302786751934147898[1] = -nom_x[1] + true_x[1];
   out_7302786751934147898[2] = -nom_x[2] + true_x[2];
   out_7302786751934147898[3] = -nom_x[3] + true_x[3];
   out_7302786751934147898[4] = -nom_x[4] + true_x[4];
   out_7302786751934147898[5] = -nom_x[5] + true_x[5];
   out_7302786751934147898[6] = -nom_x[6] + true_x[6];
   out_7302786751934147898[7] = -nom_x[7] + true_x[7];
   out_7302786751934147898[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8564810489090289784) {
   out_8564810489090289784[0] = 1.0;
   out_8564810489090289784[1] = 0.0;
   out_8564810489090289784[2] = 0.0;
   out_8564810489090289784[3] = 0.0;
   out_8564810489090289784[4] = 0.0;
   out_8564810489090289784[5] = 0.0;
   out_8564810489090289784[6] = 0.0;
   out_8564810489090289784[7] = 0.0;
   out_8564810489090289784[8] = 0.0;
   out_8564810489090289784[9] = 0.0;
   out_8564810489090289784[10] = 1.0;
   out_8564810489090289784[11] = 0.0;
   out_8564810489090289784[12] = 0.0;
   out_8564810489090289784[13] = 0.0;
   out_8564810489090289784[14] = 0.0;
   out_8564810489090289784[15] = 0.0;
   out_8564810489090289784[16] = 0.0;
   out_8564810489090289784[17] = 0.0;
   out_8564810489090289784[18] = 0.0;
   out_8564810489090289784[19] = 0.0;
   out_8564810489090289784[20] = 1.0;
   out_8564810489090289784[21] = 0.0;
   out_8564810489090289784[22] = 0.0;
   out_8564810489090289784[23] = 0.0;
   out_8564810489090289784[24] = 0.0;
   out_8564810489090289784[25] = 0.0;
   out_8564810489090289784[26] = 0.0;
   out_8564810489090289784[27] = 0.0;
   out_8564810489090289784[28] = 0.0;
   out_8564810489090289784[29] = 0.0;
   out_8564810489090289784[30] = 1.0;
   out_8564810489090289784[31] = 0.0;
   out_8564810489090289784[32] = 0.0;
   out_8564810489090289784[33] = 0.0;
   out_8564810489090289784[34] = 0.0;
   out_8564810489090289784[35] = 0.0;
   out_8564810489090289784[36] = 0.0;
   out_8564810489090289784[37] = 0.0;
   out_8564810489090289784[38] = 0.0;
   out_8564810489090289784[39] = 0.0;
   out_8564810489090289784[40] = 1.0;
   out_8564810489090289784[41] = 0.0;
   out_8564810489090289784[42] = 0.0;
   out_8564810489090289784[43] = 0.0;
   out_8564810489090289784[44] = 0.0;
   out_8564810489090289784[45] = 0.0;
   out_8564810489090289784[46] = 0.0;
   out_8564810489090289784[47] = 0.0;
   out_8564810489090289784[48] = 0.0;
   out_8564810489090289784[49] = 0.0;
   out_8564810489090289784[50] = 1.0;
   out_8564810489090289784[51] = 0.0;
   out_8564810489090289784[52] = 0.0;
   out_8564810489090289784[53] = 0.0;
   out_8564810489090289784[54] = 0.0;
   out_8564810489090289784[55] = 0.0;
   out_8564810489090289784[56] = 0.0;
   out_8564810489090289784[57] = 0.0;
   out_8564810489090289784[58] = 0.0;
   out_8564810489090289784[59] = 0.0;
   out_8564810489090289784[60] = 1.0;
   out_8564810489090289784[61] = 0.0;
   out_8564810489090289784[62] = 0.0;
   out_8564810489090289784[63] = 0.0;
   out_8564810489090289784[64] = 0.0;
   out_8564810489090289784[65] = 0.0;
   out_8564810489090289784[66] = 0.0;
   out_8564810489090289784[67] = 0.0;
   out_8564810489090289784[68] = 0.0;
   out_8564810489090289784[69] = 0.0;
   out_8564810489090289784[70] = 1.0;
   out_8564810489090289784[71] = 0.0;
   out_8564810489090289784[72] = 0.0;
   out_8564810489090289784[73] = 0.0;
   out_8564810489090289784[74] = 0.0;
   out_8564810489090289784[75] = 0.0;
   out_8564810489090289784[76] = 0.0;
   out_8564810489090289784[77] = 0.0;
   out_8564810489090289784[78] = 0.0;
   out_8564810489090289784[79] = 0.0;
   out_8564810489090289784[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_7344896958720977953) {
   out_7344896958720977953[0] = state[0];
   out_7344896958720977953[1] = state[1];
   out_7344896958720977953[2] = state[2];
   out_7344896958720977953[3] = state[3];
   out_7344896958720977953[4] = state[4];
   out_7344896958720977953[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_7344896958720977953[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_7344896958720977953[7] = state[7];
   out_7344896958720977953[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4577316669100378715) {
   out_4577316669100378715[0] = 1;
   out_4577316669100378715[1] = 0;
   out_4577316669100378715[2] = 0;
   out_4577316669100378715[3] = 0;
   out_4577316669100378715[4] = 0;
   out_4577316669100378715[5] = 0;
   out_4577316669100378715[6] = 0;
   out_4577316669100378715[7] = 0;
   out_4577316669100378715[8] = 0;
   out_4577316669100378715[9] = 0;
   out_4577316669100378715[10] = 1;
   out_4577316669100378715[11] = 0;
   out_4577316669100378715[12] = 0;
   out_4577316669100378715[13] = 0;
   out_4577316669100378715[14] = 0;
   out_4577316669100378715[15] = 0;
   out_4577316669100378715[16] = 0;
   out_4577316669100378715[17] = 0;
   out_4577316669100378715[18] = 0;
   out_4577316669100378715[19] = 0;
   out_4577316669100378715[20] = 1;
   out_4577316669100378715[21] = 0;
   out_4577316669100378715[22] = 0;
   out_4577316669100378715[23] = 0;
   out_4577316669100378715[24] = 0;
   out_4577316669100378715[25] = 0;
   out_4577316669100378715[26] = 0;
   out_4577316669100378715[27] = 0;
   out_4577316669100378715[28] = 0;
   out_4577316669100378715[29] = 0;
   out_4577316669100378715[30] = 1;
   out_4577316669100378715[31] = 0;
   out_4577316669100378715[32] = 0;
   out_4577316669100378715[33] = 0;
   out_4577316669100378715[34] = 0;
   out_4577316669100378715[35] = 0;
   out_4577316669100378715[36] = 0;
   out_4577316669100378715[37] = 0;
   out_4577316669100378715[38] = 0;
   out_4577316669100378715[39] = 0;
   out_4577316669100378715[40] = 1;
   out_4577316669100378715[41] = 0;
   out_4577316669100378715[42] = 0;
   out_4577316669100378715[43] = 0;
   out_4577316669100378715[44] = 0;
   out_4577316669100378715[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4577316669100378715[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4577316669100378715[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4577316669100378715[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4577316669100378715[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4577316669100378715[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4577316669100378715[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4577316669100378715[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4577316669100378715[53] = -9.8100000000000005*dt;
   out_4577316669100378715[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4577316669100378715[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4577316669100378715[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4577316669100378715[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4577316669100378715[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4577316669100378715[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4577316669100378715[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4577316669100378715[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4577316669100378715[62] = 0;
   out_4577316669100378715[63] = 0;
   out_4577316669100378715[64] = 0;
   out_4577316669100378715[65] = 0;
   out_4577316669100378715[66] = 0;
   out_4577316669100378715[67] = 0;
   out_4577316669100378715[68] = 0;
   out_4577316669100378715[69] = 0;
   out_4577316669100378715[70] = 1;
   out_4577316669100378715[71] = 0;
   out_4577316669100378715[72] = 0;
   out_4577316669100378715[73] = 0;
   out_4577316669100378715[74] = 0;
   out_4577316669100378715[75] = 0;
   out_4577316669100378715[76] = 0;
   out_4577316669100378715[77] = 0;
   out_4577316669100378715[78] = 0;
   out_4577316669100378715[79] = 0;
   out_4577316669100378715[80] = 1;
}
void h_25(double *state, double *unused, double *out_6986192086353969465) {
   out_6986192086353969465[0] = state[6];
}
void H_25(double *state, double *unused, double *out_628377736821947453) {
   out_628377736821947453[0] = 0;
   out_628377736821947453[1] = 0;
   out_628377736821947453[2] = 0;
   out_628377736821947453[3] = 0;
   out_628377736821947453[4] = 0;
   out_628377736821947453[5] = 0;
   out_628377736821947453[6] = 1;
   out_628377736821947453[7] = 0;
   out_628377736821947453[8] = 0;
}
void h_24(double *state, double *unused, double *out_434665502247836674) {
   out_434665502247836674[0] = state[4];
   out_434665502247836674[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2801027335827447019) {
   out_2801027335827447019[0] = 0;
   out_2801027335827447019[1] = 0;
   out_2801027335827447019[2] = 0;
   out_2801027335827447019[3] = 0;
   out_2801027335827447019[4] = 1;
   out_2801027335827447019[5] = 0;
   out_2801027335827447019[6] = 0;
   out_2801027335827447019[7] = 0;
   out_2801027335827447019[8] = 0;
   out_2801027335827447019[9] = 0;
   out_2801027335827447019[10] = 0;
   out_2801027335827447019[11] = 0;
   out_2801027335827447019[12] = 0;
   out_2801027335827447019[13] = 0;
   out_2801027335827447019[14] = 1;
   out_2801027335827447019[15] = 0;
   out_2801027335827447019[16] = 0;
   out_2801027335827447019[17] = 0;
}
void h_30(double *state, double *unused, double *out_4915078315896353947) {
   out_4915078315896353947[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6288312604669669302) {
   out_6288312604669669302[0] = 0;
   out_6288312604669669302[1] = 0;
   out_6288312604669669302[2] = 0;
   out_6288312604669669302[3] = 0;
   out_6288312604669669302[4] = 1;
   out_6288312604669669302[5] = 0;
   out_6288312604669669302[6] = 0;
   out_6288312604669669302[7] = 0;
   out_6288312604669669302[8] = 0;
}
void h_26(double *state, double *unused, double *out_4943503076008356261) {
   out_4943503076008356261[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4369881055696003677) {
   out_4369881055696003677[0] = 0;
   out_4369881055696003677[1] = 0;
   out_4369881055696003677[2] = 0;
   out_4369881055696003677[3] = 0;
   out_4369881055696003677[4] = 0;
   out_4369881055696003677[5] = 0;
   out_4369881055696003677[6] = 0;
   out_4369881055696003677[7] = 1;
   out_4369881055696003677[8] = 0;
}
void h_27(double *state, double *unused, double *out_1984518818693123820) {
   out_1984518818693123820[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2932479995765612434) {
   out_2932479995765612434[0] = 0;
   out_2932479995765612434[1] = 0;
   out_2932479995765612434[2] = 0;
   out_2932479995765612434[3] = 1;
   out_2932479995765612434[4] = 0;
   out_2932479995765612434[5] = 0;
   out_2932479995765612434[6] = 0;
   out_2932479995765612434[7] = 0;
   out_2932479995765612434[8] = 0;
}
void h_29(double *state, double *unused, double *out_963207171662361141) {
   out_963207171662361141[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4645842722635163467) {
   out_4645842722635163467[0] = 0;
   out_4645842722635163467[1] = 1;
   out_4645842722635163467[2] = 0;
   out_4645842722635163467[3] = 0;
   out_4645842722635163467[4] = 0;
   out_4645842722635163467[5] = 0;
   out_4645842722635163467[6] = 0;
   out_4645842722635163467[7] = 0;
   out_4645842722635163467[8] = 0;
}
void h_28(double *state, double *unused, double *out_1002434725357825708) {
   out_1002434725357825708[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2682212451069837216) {
   out_2682212451069837216[0] = 1;
   out_2682212451069837216[1] = 0;
   out_2682212451069837216[2] = 0;
   out_2682212451069837216[3] = 0;
   out_2682212451069837216[4] = 0;
   out_2682212451069837216[5] = 0;
   out_2682212451069837216[6] = 0;
   out_2682212451069837216[7] = 0;
   out_2682212451069837216[8] = 0;
}
void h_31(double *state, double *unused, double *out_7261386148638475354) {
   out_7261386148638475354[0] = state[8];
}
void H_31(double *state, double *unused, double *out_597731774944987025) {
   out_597731774944987025[0] = 0;
   out_597731774944987025[1] = 0;
   out_597731774944987025[2] = 0;
   out_597731774944987025[3] = 0;
   out_597731774944987025[4] = 0;
   out_597731774944987025[5] = 0;
   out_597731774944987025[6] = 0;
   out_597731774944987025[7] = 0;
   out_597731774944987025[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_5406094264205448922) {
  err_fun(nom_x, delta_x, out_5406094264205448922);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7302786751934147898) {
  inv_err_fun(nom_x, true_x, out_7302786751934147898);
}
void car_H_mod_fun(double *state, double *out_8564810489090289784) {
  H_mod_fun(state, out_8564810489090289784);
}
void car_f_fun(double *state, double dt, double *out_7344896958720977953) {
  f_fun(state,  dt, out_7344896958720977953);
}
void car_F_fun(double *state, double dt, double *out_4577316669100378715) {
  F_fun(state,  dt, out_4577316669100378715);
}
void car_h_25(double *state, double *unused, double *out_6986192086353969465) {
  h_25(state, unused, out_6986192086353969465);
}
void car_H_25(double *state, double *unused, double *out_628377736821947453) {
  H_25(state, unused, out_628377736821947453);
}
void car_h_24(double *state, double *unused, double *out_434665502247836674) {
  h_24(state, unused, out_434665502247836674);
}
void car_H_24(double *state, double *unused, double *out_2801027335827447019) {
  H_24(state, unused, out_2801027335827447019);
}
void car_h_30(double *state, double *unused, double *out_4915078315896353947) {
  h_30(state, unused, out_4915078315896353947);
}
void car_H_30(double *state, double *unused, double *out_6288312604669669302) {
  H_30(state, unused, out_6288312604669669302);
}
void car_h_26(double *state, double *unused, double *out_4943503076008356261) {
  h_26(state, unused, out_4943503076008356261);
}
void car_H_26(double *state, double *unused, double *out_4369881055696003677) {
  H_26(state, unused, out_4369881055696003677);
}
void car_h_27(double *state, double *unused, double *out_1984518818693123820) {
  h_27(state, unused, out_1984518818693123820);
}
void car_H_27(double *state, double *unused, double *out_2932479995765612434) {
  H_27(state, unused, out_2932479995765612434);
}
void car_h_29(double *state, double *unused, double *out_963207171662361141) {
  h_29(state, unused, out_963207171662361141);
}
void car_H_29(double *state, double *unused, double *out_4645842722635163467) {
  H_29(state, unused, out_4645842722635163467);
}
void car_h_28(double *state, double *unused, double *out_1002434725357825708) {
  h_28(state, unused, out_1002434725357825708);
}
void car_H_28(double *state, double *unused, double *out_2682212451069837216) {
  H_28(state, unused, out_2682212451069837216);
}
void car_h_31(double *state, double *unused, double *out_7261386148638475354) {
  h_31(state, unused, out_7261386148638475354);
}
void car_H_31(double *state, double *unused, double *out_597731774944987025) {
  H_31(state, unused, out_597731774944987025);
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
