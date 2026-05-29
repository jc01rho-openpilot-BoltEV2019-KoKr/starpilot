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
void err_fun(double *nom_x, double *delta_x, double *out_7214711627163091402) {
   out_7214711627163091402[0] = delta_x[0] + nom_x[0];
   out_7214711627163091402[1] = delta_x[1] + nom_x[1];
   out_7214711627163091402[2] = delta_x[2] + nom_x[2];
   out_7214711627163091402[3] = delta_x[3] + nom_x[3];
   out_7214711627163091402[4] = delta_x[4] + nom_x[4];
   out_7214711627163091402[5] = delta_x[5] + nom_x[5];
   out_7214711627163091402[6] = delta_x[6] + nom_x[6];
   out_7214711627163091402[7] = delta_x[7] + nom_x[7];
   out_7214711627163091402[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_911828672798028438) {
   out_911828672798028438[0] = -nom_x[0] + true_x[0];
   out_911828672798028438[1] = -nom_x[1] + true_x[1];
   out_911828672798028438[2] = -nom_x[2] + true_x[2];
   out_911828672798028438[3] = -nom_x[3] + true_x[3];
   out_911828672798028438[4] = -nom_x[4] + true_x[4];
   out_911828672798028438[5] = -nom_x[5] + true_x[5];
   out_911828672798028438[6] = -nom_x[6] + true_x[6];
   out_911828672798028438[7] = -nom_x[7] + true_x[7];
   out_911828672798028438[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_149552472482575511) {
   out_149552472482575511[0] = 1.0;
   out_149552472482575511[1] = 0.0;
   out_149552472482575511[2] = 0.0;
   out_149552472482575511[3] = 0.0;
   out_149552472482575511[4] = 0.0;
   out_149552472482575511[5] = 0.0;
   out_149552472482575511[6] = 0.0;
   out_149552472482575511[7] = 0.0;
   out_149552472482575511[8] = 0.0;
   out_149552472482575511[9] = 0.0;
   out_149552472482575511[10] = 1.0;
   out_149552472482575511[11] = 0.0;
   out_149552472482575511[12] = 0.0;
   out_149552472482575511[13] = 0.0;
   out_149552472482575511[14] = 0.0;
   out_149552472482575511[15] = 0.0;
   out_149552472482575511[16] = 0.0;
   out_149552472482575511[17] = 0.0;
   out_149552472482575511[18] = 0.0;
   out_149552472482575511[19] = 0.0;
   out_149552472482575511[20] = 1.0;
   out_149552472482575511[21] = 0.0;
   out_149552472482575511[22] = 0.0;
   out_149552472482575511[23] = 0.0;
   out_149552472482575511[24] = 0.0;
   out_149552472482575511[25] = 0.0;
   out_149552472482575511[26] = 0.0;
   out_149552472482575511[27] = 0.0;
   out_149552472482575511[28] = 0.0;
   out_149552472482575511[29] = 0.0;
   out_149552472482575511[30] = 1.0;
   out_149552472482575511[31] = 0.0;
   out_149552472482575511[32] = 0.0;
   out_149552472482575511[33] = 0.0;
   out_149552472482575511[34] = 0.0;
   out_149552472482575511[35] = 0.0;
   out_149552472482575511[36] = 0.0;
   out_149552472482575511[37] = 0.0;
   out_149552472482575511[38] = 0.0;
   out_149552472482575511[39] = 0.0;
   out_149552472482575511[40] = 1.0;
   out_149552472482575511[41] = 0.0;
   out_149552472482575511[42] = 0.0;
   out_149552472482575511[43] = 0.0;
   out_149552472482575511[44] = 0.0;
   out_149552472482575511[45] = 0.0;
   out_149552472482575511[46] = 0.0;
   out_149552472482575511[47] = 0.0;
   out_149552472482575511[48] = 0.0;
   out_149552472482575511[49] = 0.0;
   out_149552472482575511[50] = 1.0;
   out_149552472482575511[51] = 0.0;
   out_149552472482575511[52] = 0.0;
   out_149552472482575511[53] = 0.0;
   out_149552472482575511[54] = 0.0;
   out_149552472482575511[55] = 0.0;
   out_149552472482575511[56] = 0.0;
   out_149552472482575511[57] = 0.0;
   out_149552472482575511[58] = 0.0;
   out_149552472482575511[59] = 0.0;
   out_149552472482575511[60] = 1.0;
   out_149552472482575511[61] = 0.0;
   out_149552472482575511[62] = 0.0;
   out_149552472482575511[63] = 0.0;
   out_149552472482575511[64] = 0.0;
   out_149552472482575511[65] = 0.0;
   out_149552472482575511[66] = 0.0;
   out_149552472482575511[67] = 0.0;
   out_149552472482575511[68] = 0.0;
   out_149552472482575511[69] = 0.0;
   out_149552472482575511[70] = 1.0;
   out_149552472482575511[71] = 0.0;
   out_149552472482575511[72] = 0.0;
   out_149552472482575511[73] = 0.0;
   out_149552472482575511[74] = 0.0;
   out_149552472482575511[75] = 0.0;
   out_149552472482575511[76] = 0.0;
   out_149552472482575511[77] = 0.0;
   out_149552472482575511[78] = 0.0;
   out_149552472482575511[79] = 0.0;
   out_149552472482575511[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4547528931834134293) {
   out_4547528931834134293[0] = state[0];
   out_4547528931834134293[1] = state[1];
   out_4547528931834134293[2] = state[2];
   out_4547528931834134293[3] = state[3];
   out_4547528931834134293[4] = state[4];
   out_4547528931834134293[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4547528931834134293[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4547528931834134293[7] = state[7];
   out_4547528931834134293[8] = state[8];
}
void F_fun(double *state, double dt, double *out_3560058468708809121) {
   out_3560058468708809121[0] = 1;
   out_3560058468708809121[1] = 0;
   out_3560058468708809121[2] = 0;
   out_3560058468708809121[3] = 0;
   out_3560058468708809121[4] = 0;
   out_3560058468708809121[5] = 0;
   out_3560058468708809121[6] = 0;
   out_3560058468708809121[7] = 0;
   out_3560058468708809121[8] = 0;
   out_3560058468708809121[9] = 0;
   out_3560058468708809121[10] = 1;
   out_3560058468708809121[11] = 0;
   out_3560058468708809121[12] = 0;
   out_3560058468708809121[13] = 0;
   out_3560058468708809121[14] = 0;
   out_3560058468708809121[15] = 0;
   out_3560058468708809121[16] = 0;
   out_3560058468708809121[17] = 0;
   out_3560058468708809121[18] = 0;
   out_3560058468708809121[19] = 0;
   out_3560058468708809121[20] = 1;
   out_3560058468708809121[21] = 0;
   out_3560058468708809121[22] = 0;
   out_3560058468708809121[23] = 0;
   out_3560058468708809121[24] = 0;
   out_3560058468708809121[25] = 0;
   out_3560058468708809121[26] = 0;
   out_3560058468708809121[27] = 0;
   out_3560058468708809121[28] = 0;
   out_3560058468708809121[29] = 0;
   out_3560058468708809121[30] = 1;
   out_3560058468708809121[31] = 0;
   out_3560058468708809121[32] = 0;
   out_3560058468708809121[33] = 0;
   out_3560058468708809121[34] = 0;
   out_3560058468708809121[35] = 0;
   out_3560058468708809121[36] = 0;
   out_3560058468708809121[37] = 0;
   out_3560058468708809121[38] = 0;
   out_3560058468708809121[39] = 0;
   out_3560058468708809121[40] = 1;
   out_3560058468708809121[41] = 0;
   out_3560058468708809121[42] = 0;
   out_3560058468708809121[43] = 0;
   out_3560058468708809121[44] = 0;
   out_3560058468708809121[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_3560058468708809121[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_3560058468708809121[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3560058468708809121[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_3560058468708809121[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_3560058468708809121[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_3560058468708809121[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_3560058468708809121[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_3560058468708809121[53] = -9.8100000000000005*dt;
   out_3560058468708809121[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_3560058468708809121[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_3560058468708809121[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3560058468708809121[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3560058468708809121[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_3560058468708809121[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_3560058468708809121[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_3560058468708809121[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_3560058468708809121[62] = 0;
   out_3560058468708809121[63] = 0;
   out_3560058468708809121[64] = 0;
   out_3560058468708809121[65] = 0;
   out_3560058468708809121[66] = 0;
   out_3560058468708809121[67] = 0;
   out_3560058468708809121[68] = 0;
   out_3560058468708809121[69] = 0;
   out_3560058468708809121[70] = 1;
   out_3560058468708809121[71] = 0;
   out_3560058468708809121[72] = 0;
   out_3560058468708809121[73] = 0;
   out_3560058468708809121[74] = 0;
   out_3560058468708809121[75] = 0;
   out_3560058468708809121[76] = 0;
   out_3560058468708809121[77] = 0;
   out_3560058468708809121[78] = 0;
   out_3560058468708809121[79] = 0;
   out_3560058468708809121[80] = 1;
}
void h_25(double *state, double *unused, double *out_1132582605868503102) {
   out_1132582605868503102[0] = state[6];
}
void H_25(double *state, double *unused, double *out_9104003375314738868) {
   out_9104003375314738868[0] = 0;
   out_9104003375314738868[1] = 0;
   out_9104003375314738868[2] = 0;
   out_9104003375314738868[3] = 0;
   out_9104003375314738868[4] = 0;
   out_9104003375314738868[5] = 0;
   out_9104003375314738868[6] = 1;
   out_9104003375314738868[7] = 0;
   out_9104003375314738868[8] = 0;
}
void h_24(double *state, double *unused, double *out_8381470974523360630) {
   out_8381470974523360630[0] = state[4];
   out_8381470974523360630[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4357494048348229834) {
   out_4357494048348229834[0] = 0;
   out_4357494048348229834[1] = 0;
   out_4357494048348229834[2] = 0;
   out_4357494048348229834[3] = 0;
   out_4357494048348229834[4] = 1;
   out_4357494048348229834[5] = 0;
   out_4357494048348229834[6] = 0;
   out_4357494048348229834[7] = 0;
   out_4357494048348229834[8] = 0;
   out_4357494048348229834[9] = 0;
   out_4357494048348229834[10] = 0;
   out_4357494048348229834[11] = 0;
   out_4357494048348229834[12] = 0;
   out_4357494048348229834[13] = 0;
   out_4357494048348229834[14] = 1;
   out_4357494048348229834[15] = 0;
   out_4357494048348229834[16] = 0;
   out_4357494048348229834[17] = 0;
}
void h_30(double *state, double *unused, double *out_975395937517373957) {
   out_975395937517373957[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2426050356903195993) {
   out_2426050356903195993[0] = 0;
   out_2426050356903195993[1] = 0;
   out_2426050356903195993[2] = 0;
   out_2426050356903195993[3] = 0;
   out_2426050356903195993[4] = 1;
   out_2426050356903195993[5] = 0;
   out_2426050356903195993[6] = 0;
   out_2426050356903195993[7] = 0;
   out_2426050356903195993[8] = 0;
}
void h_26(double *state, double *unused, double *out_4026277330143471688) {
   out_4026277330143471688[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5362500056440682644) {
   out_5362500056440682644[0] = 0;
   out_5362500056440682644[1] = 0;
   out_5362500056440682644[2] = 0;
   out_5362500056440682644[3] = 0;
   out_5362500056440682644[4] = 0;
   out_5362500056440682644[5] = 0;
   out_5362500056440682644[6] = 0;
   out_5362500056440682644[7] = 1;
   out_5362500056440682644[8] = 0;
}
void h_27(double *state, double *unused, double *out_990245959502812892) {
   out_990245959502812892[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4600813668703620904) {
   out_4600813668703620904[0] = 0;
   out_4600813668703620904[1] = 0;
   out_4600813668703620904[2] = 0;
   out_4600813668703620904[3] = 1;
   out_4600813668703620904[4] = 0;
   out_4600813668703620904[5] = 0;
   out_4600813668703620904[6] = 0;
   out_4600813668703620904[7] = 0;
   out_4600813668703620904[8] = 0;
}
void h_29(double *state, double *unused, double *out_8450804723751701217) {
   out_8450804723751701217[0] = state[1];
}
void H_29(double *state, double *unused, double *out_1915819012588803809) {
   out_1915819012588803809[0] = 0;
   out_1915819012588803809[1] = 1;
   out_1915819012588803809[2] = 0;
   out_1915819012588803809[3] = 0;
   out_1915819012588803809[4] = 0;
   out_1915819012588803809[5] = 0;
   out_1915819012588803809[6] = 0;
   out_1915819012588803809[7] = 0;
   out_1915819012588803809[8] = 0;
}
void h_28(double *state, double *unused, double *out_2847713298477492018) {
   out_2847713298477492018[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7050168661066849105) {
   out_7050168661066849105[0] = 1;
   out_7050168661066849105[1] = 0;
   out_7050168661066849105[2] = 0;
   out_7050168661066849105[3] = 0;
   out_7050168661066849105[4] = 0;
   out_7050168661066849105[5] = 0;
   out_7050168661066849105[6] = 0;
   out_7050168661066849105[7] = 0;
   out_7050168661066849105[8] = 0;
}
void h_31(double *state, double *unused, double *out_857388543583997213) {
   out_857388543583997213[0] = state[8];
}
void H_31(double *state, double *unused, double *out_9134649337191699296) {
   out_9134649337191699296[0] = 0;
   out_9134649337191699296[1] = 0;
   out_9134649337191699296[2] = 0;
   out_9134649337191699296[3] = 0;
   out_9134649337191699296[4] = 0;
   out_9134649337191699296[5] = 0;
   out_9134649337191699296[6] = 0;
   out_9134649337191699296[7] = 0;
   out_9134649337191699296[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7214711627163091402) {
  err_fun(nom_x, delta_x, out_7214711627163091402);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_911828672798028438) {
  inv_err_fun(nom_x, true_x, out_911828672798028438);
}
void car_H_mod_fun(double *state, double *out_149552472482575511) {
  H_mod_fun(state, out_149552472482575511);
}
void car_f_fun(double *state, double dt, double *out_4547528931834134293) {
  f_fun(state,  dt, out_4547528931834134293);
}
void car_F_fun(double *state, double dt, double *out_3560058468708809121) {
  F_fun(state,  dt, out_3560058468708809121);
}
void car_h_25(double *state, double *unused, double *out_1132582605868503102) {
  h_25(state, unused, out_1132582605868503102);
}
void car_H_25(double *state, double *unused, double *out_9104003375314738868) {
  H_25(state, unused, out_9104003375314738868);
}
void car_h_24(double *state, double *unused, double *out_8381470974523360630) {
  h_24(state, unused, out_8381470974523360630);
}
void car_H_24(double *state, double *unused, double *out_4357494048348229834) {
  H_24(state, unused, out_4357494048348229834);
}
void car_h_30(double *state, double *unused, double *out_975395937517373957) {
  h_30(state, unused, out_975395937517373957);
}
void car_H_30(double *state, double *unused, double *out_2426050356903195993) {
  H_30(state, unused, out_2426050356903195993);
}
void car_h_26(double *state, double *unused, double *out_4026277330143471688) {
  h_26(state, unused, out_4026277330143471688);
}
void car_H_26(double *state, double *unused, double *out_5362500056440682644) {
  H_26(state, unused, out_5362500056440682644);
}
void car_h_27(double *state, double *unused, double *out_990245959502812892) {
  h_27(state, unused, out_990245959502812892);
}
void car_H_27(double *state, double *unused, double *out_4600813668703620904) {
  H_27(state, unused, out_4600813668703620904);
}
void car_h_29(double *state, double *unused, double *out_8450804723751701217) {
  h_29(state, unused, out_8450804723751701217);
}
void car_H_29(double *state, double *unused, double *out_1915819012588803809) {
  H_29(state, unused, out_1915819012588803809);
}
void car_h_28(double *state, double *unused, double *out_2847713298477492018) {
  h_28(state, unused, out_2847713298477492018);
}
void car_H_28(double *state, double *unused, double *out_7050168661066849105) {
  H_28(state, unused, out_7050168661066849105);
}
void car_h_31(double *state, double *unused, double *out_857388543583997213) {
  h_31(state, unused, out_857388543583997213);
}
void car_H_31(double *state, double *unused, double *out_9134649337191699296) {
  H_31(state, unused, out_9134649337191699296);
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
