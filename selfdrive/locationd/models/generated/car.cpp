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
void err_fun(double *nom_x, double *delta_x, double *out_5591921399563932369) {
   out_5591921399563932369[0] = delta_x[0] + nom_x[0];
   out_5591921399563932369[1] = delta_x[1] + nom_x[1];
   out_5591921399563932369[2] = delta_x[2] + nom_x[2];
   out_5591921399563932369[3] = delta_x[3] + nom_x[3];
   out_5591921399563932369[4] = delta_x[4] + nom_x[4];
   out_5591921399563932369[5] = delta_x[5] + nom_x[5];
   out_5591921399563932369[6] = delta_x[6] + nom_x[6];
   out_5591921399563932369[7] = delta_x[7] + nom_x[7];
   out_5591921399563932369[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_806607420895539823) {
   out_806607420895539823[0] = -nom_x[0] + true_x[0];
   out_806607420895539823[1] = -nom_x[1] + true_x[1];
   out_806607420895539823[2] = -nom_x[2] + true_x[2];
   out_806607420895539823[3] = -nom_x[3] + true_x[3];
   out_806607420895539823[4] = -nom_x[4] + true_x[4];
   out_806607420895539823[5] = -nom_x[5] + true_x[5];
   out_806607420895539823[6] = -nom_x[6] + true_x[6];
   out_806607420895539823[7] = -nom_x[7] + true_x[7];
   out_806607420895539823[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5676707820504431668) {
   out_5676707820504431668[0] = 1.0;
   out_5676707820504431668[1] = 0.0;
   out_5676707820504431668[2] = 0.0;
   out_5676707820504431668[3] = 0.0;
   out_5676707820504431668[4] = 0.0;
   out_5676707820504431668[5] = 0.0;
   out_5676707820504431668[6] = 0.0;
   out_5676707820504431668[7] = 0.0;
   out_5676707820504431668[8] = 0.0;
   out_5676707820504431668[9] = 0.0;
   out_5676707820504431668[10] = 1.0;
   out_5676707820504431668[11] = 0.0;
   out_5676707820504431668[12] = 0.0;
   out_5676707820504431668[13] = 0.0;
   out_5676707820504431668[14] = 0.0;
   out_5676707820504431668[15] = 0.0;
   out_5676707820504431668[16] = 0.0;
   out_5676707820504431668[17] = 0.0;
   out_5676707820504431668[18] = 0.0;
   out_5676707820504431668[19] = 0.0;
   out_5676707820504431668[20] = 1.0;
   out_5676707820504431668[21] = 0.0;
   out_5676707820504431668[22] = 0.0;
   out_5676707820504431668[23] = 0.0;
   out_5676707820504431668[24] = 0.0;
   out_5676707820504431668[25] = 0.0;
   out_5676707820504431668[26] = 0.0;
   out_5676707820504431668[27] = 0.0;
   out_5676707820504431668[28] = 0.0;
   out_5676707820504431668[29] = 0.0;
   out_5676707820504431668[30] = 1.0;
   out_5676707820504431668[31] = 0.0;
   out_5676707820504431668[32] = 0.0;
   out_5676707820504431668[33] = 0.0;
   out_5676707820504431668[34] = 0.0;
   out_5676707820504431668[35] = 0.0;
   out_5676707820504431668[36] = 0.0;
   out_5676707820504431668[37] = 0.0;
   out_5676707820504431668[38] = 0.0;
   out_5676707820504431668[39] = 0.0;
   out_5676707820504431668[40] = 1.0;
   out_5676707820504431668[41] = 0.0;
   out_5676707820504431668[42] = 0.0;
   out_5676707820504431668[43] = 0.0;
   out_5676707820504431668[44] = 0.0;
   out_5676707820504431668[45] = 0.0;
   out_5676707820504431668[46] = 0.0;
   out_5676707820504431668[47] = 0.0;
   out_5676707820504431668[48] = 0.0;
   out_5676707820504431668[49] = 0.0;
   out_5676707820504431668[50] = 1.0;
   out_5676707820504431668[51] = 0.0;
   out_5676707820504431668[52] = 0.0;
   out_5676707820504431668[53] = 0.0;
   out_5676707820504431668[54] = 0.0;
   out_5676707820504431668[55] = 0.0;
   out_5676707820504431668[56] = 0.0;
   out_5676707820504431668[57] = 0.0;
   out_5676707820504431668[58] = 0.0;
   out_5676707820504431668[59] = 0.0;
   out_5676707820504431668[60] = 1.0;
   out_5676707820504431668[61] = 0.0;
   out_5676707820504431668[62] = 0.0;
   out_5676707820504431668[63] = 0.0;
   out_5676707820504431668[64] = 0.0;
   out_5676707820504431668[65] = 0.0;
   out_5676707820504431668[66] = 0.0;
   out_5676707820504431668[67] = 0.0;
   out_5676707820504431668[68] = 0.0;
   out_5676707820504431668[69] = 0.0;
   out_5676707820504431668[70] = 1.0;
   out_5676707820504431668[71] = 0.0;
   out_5676707820504431668[72] = 0.0;
   out_5676707820504431668[73] = 0.0;
   out_5676707820504431668[74] = 0.0;
   out_5676707820504431668[75] = 0.0;
   out_5676707820504431668[76] = 0.0;
   out_5676707820504431668[77] = 0.0;
   out_5676707820504431668[78] = 0.0;
   out_5676707820504431668[79] = 0.0;
   out_5676707820504431668[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4844917589263296834) {
   out_4844917589263296834[0] = state[0];
   out_4844917589263296834[1] = state[1];
   out_4844917589263296834[2] = state[2];
   out_4844917589263296834[3] = state[3];
   out_4844917589263296834[4] = state[4];
   out_4844917589263296834[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4844917589263296834[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4844917589263296834[7] = state[7];
   out_4844917589263296834[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4636534629313466670) {
   out_4636534629313466670[0] = 1;
   out_4636534629313466670[1] = 0;
   out_4636534629313466670[2] = 0;
   out_4636534629313466670[3] = 0;
   out_4636534629313466670[4] = 0;
   out_4636534629313466670[5] = 0;
   out_4636534629313466670[6] = 0;
   out_4636534629313466670[7] = 0;
   out_4636534629313466670[8] = 0;
   out_4636534629313466670[9] = 0;
   out_4636534629313466670[10] = 1;
   out_4636534629313466670[11] = 0;
   out_4636534629313466670[12] = 0;
   out_4636534629313466670[13] = 0;
   out_4636534629313466670[14] = 0;
   out_4636534629313466670[15] = 0;
   out_4636534629313466670[16] = 0;
   out_4636534629313466670[17] = 0;
   out_4636534629313466670[18] = 0;
   out_4636534629313466670[19] = 0;
   out_4636534629313466670[20] = 1;
   out_4636534629313466670[21] = 0;
   out_4636534629313466670[22] = 0;
   out_4636534629313466670[23] = 0;
   out_4636534629313466670[24] = 0;
   out_4636534629313466670[25] = 0;
   out_4636534629313466670[26] = 0;
   out_4636534629313466670[27] = 0;
   out_4636534629313466670[28] = 0;
   out_4636534629313466670[29] = 0;
   out_4636534629313466670[30] = 1;
   out_4636534629313466670[31] = 0;
   out_4636534629313466670[32] = 0;
   out_4636534629313466670[33] = 0;
   out_4636534629313466670[34] = 0;
   out_4636534629313466670[35] = 0;
   out_4636534629313466670[36] = 0;
   out_4636534629313466670[37] = 0;
   out_4636534629313466670[38] = 0;
   out_4636534629313466670[39] = 0;
   out_4636534629313466670[40] = 1;
   out_4636534629313466670[41] = 0;
   out_4636534629313466670[42] = 0;
   out_4636534629313466670[43] = 0;
   out_4636534629313466670[44] = 0;
   out_4636534629313466670[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4636534629313466670[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4636534629313466670[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4636534629313466670[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4636534629313466670[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4636534629313466670[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4636534629313466670[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4636534629313466670[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4636534629313466670[53] = -9.8100000000000005*dt;
   out_4636534629313466670[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4636534629313466670[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4636534629313466670[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4636534629313466670[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4636534629313466670[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4636534629313466670[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4636534629313466670[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4636534629313466670[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4636534629313466670[62] = 0;
   out_4636534629313466670[63] = 0;
   out_4636534629313466670[64] = 0;
   out_4636534629313466670[65] = 0;
   out_4636534629313466670[66] = 0;
   out_4636534629313466670[67] = 0;
   out_4636534629313466670[68] = 0;
   out_4636534629313466670[69] = 0;
   out_4636534629313466670[70] = 1;
   out_4636534629313466670[71] = 0;
   out_4636534629313466670[72] = 0;
   out_4636534629313466670[73] = 0;
   out_4636534629313466670[74] = 0;
   out_4636534629313466670[75] = 0;
   out_4636534629313466670[76] = 0;
   out_4636534629313466670[77] = 0;
   out_4636534629313466670[78] = 0;
   out_4636534629313466670[79] = 0;
   out_4636534629313466670[80] = 1;
}
void h_25(double *state, double *unused, double *out_5482647601852736049) {
   out_5482647601852736049[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7866344428020455108) {
   out_7866344428020455108[0] = 0;
   out_7866344428020455108[1] = 0;
   out_7866344428020455108[2] = 0;
   out_7866344428020455108[3] = 0;
   out_7866344428020455108[4] = 0;
   out_7866344428020455108[5] = 0;
   out_7866344428020455108[6] = 1;
   out_7866344428020455108[7] = 0;
   out_7866344428020455108[8] = 0;
}
void h_24(double *state, double *unused, double *out_6159121467458312716) {
   out_6159121467458312716[0] = state[4];
   out_6159121467458312716[1] = state[5];
}
void H_24(double *state, double *unused, double *out_3137725052700380188) {
   out_3137725052700380188[0] = 0;
   out_3137725052700380188[1] = 0;
   out_3137725052700380188[2] = 0;
   out_3137725052700380188[3] = 0;
   out_3137725052700380188[4] = 1;
   out_3137725052700380188[5] = 0;
   out_3137725052700380188[6] = 0;
   out_3137725052700380188[7] = 0;
   out_3137725052700380188[8] = 0;
   out_3137725052700380188[9] = 0;
   out_3137725052700380188[10] = 0;
   out_3137725052700380188[11] = 0;
   out_3137725052700380188[12] = 0;
   out_3137725052700380188[13] = 0;
   out_3137725052700380188[14] = 1;
   out_3137725052700380188[15] = 0;
   out_3137725052700380188[16] = 0;
   out_3137725052700380188[17] = 0;
}
void h_30(double *state, double *unused, double *out_5757841664137241938) {
   out_5757841664137241938[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7995683375163695178) {
   out_7995683375163695178[0] = 0;
   out_7995683375163695178[1] = 0;
   out_7995683375163695178[2] = 0;
   out_7995683375163695178[3] = 0;
   out_7995683375163695178[4] = 1;
   out_7995683375163695178[5] = 0;
   out_7995683375163695178[6] = 0;
   out_7995683375163695178[7] = 0;
   out_7995683375163695178[8] = 0;
}
void h_26(double *state, double *unused, double *out_6701351517038904373) {
   out_6701351517038904373[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6838896326815040284) {
   out_6838896326815040284[0] = 0;
   out_6838896326815040284[1] = 0;
   out_6838896326815040284[2] = 0;
   out_6838896326815040284[3] = 0;
   out_6838896326815040284[4] = 0;
   out_6838896326815040284[5] = 0;
   out_6838896326815040284[6] = 0;
   out_6838896326815040284[7] = 1;
   out_6838896326815040284[8] = 0;
}
void h_27(double *state, double *unused, double *out_7962423204195969922) {
   out_7962423204195969922[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8276297386745431527) {
   out_8276297386745431527[0] = 0;
   out_8276297386745431527[1] = 0;
   out_8276297386745431527[2] = 0;
   out_8276297386745431527[3] = 1;
   out_8276297386745431527[4] = 0;
   out_8276297386745431527[5] = 0;
   out_8276297386745431527[6] = 0;
   out_8276297386745431527[7] = 0;
   out_8276297386745431527[8] = 0;
}
void h_29(double *state, double *unused, double *out_2721055612692909253) {
   out_2721055612692909253[0] = state[1];
}
void H_29(double *state, double *unused, double *out_6562934659875880494) {
   out_6562934659875880494[0] = 0;
   out_6562934659875880494[1] = 1;
   out_6562934659875880494[2] = 0;
   out_6562934659875880494[3] = 0;
   out_6562934659875880494[4] = 0;
   out_6562934659875880494[5] = 0;
   out_6562934659875880494[6] = 0;
   out_6562934659875880494[7] = 0;
   out_6562934659875880494[8] = 0;
}
void h_28(double *state, double *unused, double *out_8408093249132323059) {
   out_8408093249132323059[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1480535642806349920) {
   out_1480535642806349920[0] = 1;
   out_1480535642806349920[1] = 0;
   out_1480535642806349920[2] = 0;
   out_1480535642806349920[3] = 0;
   out_1480535642806349920[4] = 0;
   out_1480535642806349920[5] = 0;
   out_1480535642806349920[6] = 0;
   out_1480535642806349920[7] = 0;
   out_1480535642806349920[8] = 0;
}
void h_31(double *state, double *unused, double *out_4467435790593075575) {
   out_4467435790593075575[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7835698466143494680) {
   out_7835698466143494680[0] = 0;
   out_7835698466143494680[1] = 0;
   out_7835698466143494680[2] = 0;
   out_7835698466143494680[3] = 0;
   out_7835698466143494680[4] = 0;
   out_7835698466143494680[5] = 0;
   out_7835698466143494680[6] = 0;
   out_7835698466143494680[7] = 0;
   out_7835698466143494680[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_5591921399563932369) {
  err_fun(nom_x, delta_x, out_5591921399563932369);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_806607420895539823) {
  inv_err_fun(nom_x, true_x, out_806607420895539823);
}
void car_H_mod_fun(double *state, double *out_5676707820504431668) {
  H_mod_fun(state, out_5676707820504431668);
}
void car_f_fun(double *state, double dt, double *out_4844917589263296834) {
  f_fun(state,  dt, out_4844917589263296834);
}
void car_F_fun(double *state, double dt, double *out_4636534629313466670) {
  F_fun(state,  dt, out_4636534629313466670);
}
void car_h_25(double *state, double *unused, double *out_5482647601852736049) {
  h_25(state, unused, out_5482647601852736049);
}
void car_H_25(double *state, double *unused, double *out_7866344428020455108) {
  H_25(state, unused, out_7866344428020455108);
}
void car_h_24(double *state, double *unused, double *out_6159121467458312716) {
  h_24(state, unused, out_6159121467458312716);
}
void car_H_24(double *state, double *unused, double *out_3137725052700380188) {
  H_24(state, unused, out_3137725052700380188);
}
void car_h_30(double *state, double *unused, double *out_5757841664137241938) {
  h_30(state, unused, out_5757841664137241938);
}
void car_H_30(double *state, double *unused, double *out_7995683375163695178) {
  H_30(state, unused, out_7995683375163695178);
}
void car_h_26(double *state, double *unused, double *out_6701351517038904373) {
  h_26(state, unused, out_6701351517038904373);
}
void car_H_26(double *state, double *unused, double *out_6838896326815040284) {
  H_26(state, unused, out_6838896326815040284);
}
void car_h_27(double *state, double *unused, double *out_7962423204195969922) {
  h_27(state, unused, out_7962423204195969922);
}
void car_H_27(double *state, double *unused, double *out_8276297386745431527) {
  H_27(state, unused, out_8276297386745431527);
}
void car_h_29(double *state, double *unused, double *out_2721055612692909253) {
  h_29(state, unused, out_2721055612692909253);
}
void car_H_29(double *state, double *unused, double *out_6562934659875880494) {
  H_29(state, unused, out_6562934659875880494);
}
void car_h_28(double *state, double *unused, double *out_8408093249132323059) {
  h_28(state, unused, out_8408093249132323059);
}
void car_H_28(double *state, double *unused, double *out_1480535642806349920) {
  H_28(state, unused, out_1480535642806349920);
}
void car_h_31(double *state, double *unused, double *out_4467435790593075575) {
  h_31(state, unused, out_4467435790593075575);
}
void car_H_31(double *state, double *unused, double *out_7835698466143494680) {
  H_31(state, unused, out_7835698466143494680);
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
