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
void err_fun(double *nom_x, double *delta_x, double *out_587611173581676283) {
   out_587611173581676283[0] = delta_x[0] + nom_x[0];
   out_587611173581676283[1] = delta_x[1] + nom_x[1];
   out_587611173581676283[2] = delta_x[2] + nom_x[2];
   out_587611173581676283[3] = delta_x[3] + nom_x[3];
   out_587611173581676283[4] = delta_x[4] + nom_x[4];
   out_587611173581676283[5] = delta_x[5] + nom_x[5];
   out_587611173581676283[6] = delta_x[6] + nom_x[6];
   out_587611173581676283[7] = delta_x[7] + nom_x[7];
   out_587611173581676283[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8120728011522269919) {
   out_8120728011522269919[0] = -nom_x[0] + true_x[0];
   out_8120728011522269919[1] = -nom_x[1] + true_x[1];
   out_8120728011522269919[2] = -nom_x[2] + true_x[2];
   out_8120728011522269919[3] = -nom_x[3] + true_x[3];
   out_8120728011522269919[4] = -nom_x[4] + true_x[4];
   out_8120728011522269919[5] = -nom_x[5] + true_x[5];
   out_8120728011522269919[6] = -nom_x[6] + true_x[6];
   out_8120728011522269919[7] = -nom_x[7] + true_x[7];
   out_8120728011522269919[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4001675034436284807) {
   out_4001675034436284807[0] = 1.0;
   out_4001675034436284807[1] = 0.0;
   out_4001675034436284807[2] = 0.0;
   out_4001675034436284807[3] = 0.0;
   out_4001675034436284807[4] = 0.0;
   out_4001675034436284807[5] = 0.0;
   out_4001675034436284807[6] = 0.0;
   out_4001675034436284807[7] = 0.0;
   out_4001675034436284807[8] = 0.0;
   out_4001675034436284807[9] = 0.0;
   out_4001675034436284807[10] = 1.0;
   out_4001675034436284807[11] = 0.0;
   out_4001675034436284807[12] = 0.0;
   out_4001675034436284807[13] = 0.0;
   out_4001675034436284807[14] = 0.0;
   out_4001675034436284807[15] = 0.0;
   out_4001675034436284807[16] = 0.0;
   out_4001675034436284807[17] = 0.0;
   out_4001675034436284807[18] = 0.0;
   out_4001675034436284807[19] = 0.0;
   out_4001675034436284807[20] = 1.0;
   out_4001675034436284807[21] = 0.0;
   out_4001675034436284807[22] = 0.0;
   out_4001675034436284807[23] = 0.0;
   out_4001675034436284807[24] = 0.0;
   out_4001675034436284807[25] = 0.0;
   out_4001675034436284807[26] = 0.0;
   out_4001675034436284807[27] = 0.0;
   out_4001675034436284807[28] = 0.0;
   out_4001675034436284807[29] = 0.0;
   out_4001675034436284807[30] = 1.0;
   out_4001675034436284807[31] = 0.0;
   out_4001675034436284807[32] = 0.0;
   out_4001675034436284807[33] = 0.0;
   out_4001675034436284807[34] = 0.0;
   out_4001675034436284807[35] = 0.0;
   out_4001675034436284807[36] = 0.0;
   out_4001675034436284807[37] = 0.0;
   out_4001675034436284807[38] = 0.0;
   out_4001675034436284807[39] = 0.0;
   out_4001675034436284807[40] = 1.0;
   out_4001675034436284807[41] = 0.0;
   out_4001675034436284807[42] = 0.0;
   out_4001675034436284807[43] = 0.0;
   out_4001675034436284807[44] = 0.0;
   out_4001675034436284807[45] = 0.0;
   out_4001675034436284807[46] = 0.0;
   out_4001675034436284807[47] = 0.0;
   out_4001675034436284807[48] = 0.0;
   out_4001675034436284807[49] = 0.0;
   out_4001675034436284807[50] = 1.0;
   out_4001675034436284807[51] = 0.0;
   out_4001675034436284807[52] = 0.0;
   out_4001675034436284807[53] = 0.0;
   out_4001675034436284807[54] = 0.0;
   out_4001675034436284807[55] = 0.0;
   out_4001675034436284807[56] = 0.0;
   out_4001675034436284807[57] = 0.0;
   out_4001675034436284807[58] = 0.0;
   out_4001675034436284807[59] = 0.0;
   out_4001675034436284807[60] = 1.0;
   out_4001675034436284807[61] = 0.0;
   out_4001675034436284807[62] = 0.0;
   out_4001675034436284807[63] = 0.0;
   out_4001675034436284807[64] = 0.0;
   out_4001675034436284807[65] = 0.0;
   out_4001675034436284807[66] = 0.0;
   out_4001675034436284807[67] = 0.0;
   out_4001675034436284807[68] = 0.0;
   out_4001675034436284807[69] = 0.0;
   out_4001675034436284807[70] = 1.0;
   out_4001675034436284807[71] = 0.0;
   out_4001675034436284807[72] = 0.0;
   out_4001675034436284807[73] = 0.0;
   out_4001675034436284807[74] = 0.0;
   out_4001675034436284807[75] = 0.0;
   out_4001675034436284807[76] = 0.0;
   out_4001675034436284807[77] = 0.0;
   out_4001675034436284807[78] = 0.0;
   out_4001675034436284807[79] = 0.0;
   out_4001675034436284807[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6995360374056238489) {
   out_6995360374056238489[0] = state[0];
   out_6995360374056238489[1] = state[1];
   out_6995360374056238489[2] = state[2];
   out_6995360374056238489[3] = state[3];
   out_6995360374056238489[4] = state[4];
   out_6995360374056238489[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6995360374056238489[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6995360374056238489[7] = state[7];
   out_6995360374056238489[8] = state[8];
}
void F_fun(double *state, double dt, double *out_5620828310005666299) {
   out_5620828310005666299[0] = 1;
   out_5620828310005666299[1] = 0;
   out_5620828310005666299[2] = 0;
   out_5620828310005666299[3] = 0;
   out_5620828310005666299[4] = 0;
   out_5620828310005666299[5] = 0;
   out_5620828310005666299[6] = 0;
   out_5620828310005666299[7] = 0;
   out_5620828310005666299[8] = 0;
   out_5620828310005666299[9] = 0;
   out_5620828310005666299[10] = 1;
   out_5620828310005666299[11] = 0;
   out_5620828310005666299[12] = 0;
   out_5620828310005666299[13] = 0;
   out_5620828310005666299[14] = 0;
   out_5620828310005666299[15] = 0;
   out_5620828310005666299[16] = 0;
   out_5620828310005666299[17] = 0;
   out_5620828310005666299[18] = 0;
   out_5620828310005666299[19] = 0;
   out_5620828310005666299[20] = 1;
   out_5620828310005666299[21] = 0;
   out_5620828310005666299[22] = 0;
   out_5620828310005666299[23] = 0;
   out_5620828310005666299[24] = 0;
   out_5620828310005666299[25] = 0;
   out_5620828310005666299[26] = 0;
   out_5620828310005666299[27] = 0;
   out_5620828310005666299[28] = 0;
   out_5620828310005666299[29] = 0;
   out_5620828310005666299[30] = 1;
   out_5620828310005666299[31] = 0;
   out_5620828310005666299[32] = 0;
   out_5620828310005666299[33] = 0;
   out_5620828310005666299[34] = 0;
   out_5620828310005666299[35] = 0;
   out_5620828310005666299[36] = 0;
   out_5620828310005666299[37] = 0;
   out_5620828310005666299[38] = 0;
   out_5620828310005666299[39] = 0;
   out_5620828310005666299[40] = 1;
   out_5620828310005666299[41] = 0;
   out_5620828310005666299[42] = 0;
   out_5620828310005666299[43] = 0;
   out_5620828310005666299[44] = 0;
   out_5620828310005666299[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_5620828310005666299[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_5620828310005666299[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5620828310005666299[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5620828310005666299[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_5620828310005666299[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_5620828310005666299[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_5620828310005666299[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_5620828310005666299[53] = -9.8100000000000005*dt;
   out_5620828310005666299[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_5620828310005666299[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_5620828310005666299[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5620828310005666299[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5620828310005666299[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_5620828310005666299[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_5620828310005666299[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_5620828310005666299[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5620828310005666299[62] = 0;
   out_5620828310005666299[63] = 0;
   out_5620828310005666299[64] = 0;
   out_5620828310005666299[65] = 0;
   out_5620828310005666299[66] = 0;
   out_5620828310005666299[67] = 0;
   out_5620828310005666299[68] = 0;
   out_5620828310005666299[69] = 0;
   out_5620828310005666299[70] = 1;
   out_5620828310005666299[71] = 0;
   out_5620828310005666299[72] = 0;
   out_5620828310005666299[73] = 0;
   out_5620828310005666299[74] = 0;
   out_5620828310005666299[75] = 0;
   out_5620828310005666299[76] = 0;
   out_5620828310005666299[77] = 0;
   out_5620828310005666299[78] = 0;
   out_5620828310005666299[79] = 0;
   out_5620828310005666299[80] = 1;
}
void h_25(double *state, double *unused, double *out_5932710635121359621) {
   out_5932710635121359621[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4507009476636581519) {
   out_4507009476636581519[0] = 0;
   out_4507009476636581519[1] = 0;
   out_4507009476636581519[2] = 0;
   out_4507009476636581519[3] = 0;
   out_4507009476636581519[4] = 0;
   out_4507009476636581519[5] = 0;
   out_4507009476636581519[6] = 1;
   out_4507009476636581519[7] = 0;
   out_4507009476636581519[8] = 0;
}
void h_24(double *state, double *unused, double *out_8960081603047522700) {
   out_8960081603047522700[0] = state[4];
   out_8960081603047522700[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7364162790481451996) {
   out_7364162790481451996[0] = 0;
   out_7364162790481451996[1] = 0;
   out_7364162790481451996[2] = 0;
   out_7364162790481451996[3] = 0;
   out_7364162790481451996[4] = 1;
   out_7364162790481451996[5] = 0;
   out_7364162790481451996[6] = 0;
   out_7364162790481451996[7] = 0;
   out_7364162790481451996[8] = 0;
   out_7364162790481451996[9] = 0;
   out_7364162790481451996[10] = 0;
   out_7364162790481451996[11] = 0;
   out_7364162790481451996[12] = 0;
   out_7364162790481451996[13] = 0;
   out_7364162790481451996[14] = 1;
   out_7364162790481451996[15] = 0;
   out_7364162790481451996[16] = 0;
   out_7364162790481451996[17] = 0;
}
void h_30(double *state, double *unused, double *out_6293656255741178026) {
   out_6293656255741178026[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7023044255581353342) {
   out_7023044255581353342[0] = 0;
   out_7023044255581353342[1] = 0;
   out_7023044255581353342[2] = 0;
   out_7023044255581353342[3] = 0;
   out_7023044255581353342[4] = 1;
   out_7023044255581353342[5] = 0;
   out_7023044255581353342[6] = 0;
   out_7023044255581353342[7] = 0;
   out_7023044255581353342[8] = 0;
}
void h_26(double *state, double *unused, double *out_7151414550307527945) {
   out_7151414550307527945[0] = state[7];
}
void H_26(double *state, double *unused, double *out_765506157762525295) {
   out_765506157762525295[0] = 0;
   out_765506157762525295[1] = 0;
   out_765506157762525295[2] = 0;
   out_765506157762525295[3] = 0;
   out_765506157762525295[4] = 0;
   out_765506157762525295[5] = 0;
   out_765506157762525295[6] = 0;
   out_765506157762525295[7] = 1;
   out_765506157762525295[8] = 0;
}
void h_27(double *state, double *unused, double *out_7512360170927346350) {
   out_7512360170927346350[0] = state[3];
}
void H_27(double *state, double *unused, double *out_9197807567381778253) {
   out_9197807567381778253[0] = 0;
   out_9197807567381778253[1] = 0;
   out_9197807567381778253[2] = 0;
   out_9197807567381778253[3] = 1;
   out_9197807567381778253[4] = 0;
   out_9197807567381778253[5] = 0;
   out_9197807567381778253[6] = 0;
   out_9197807567381778253[7] = 0;
   out_9197807567381778253[8] = 0;
}
void h_29(double *state, double *unused, double *out_3171118645961532825) {
   out_3171118645961532825[0] = state[1];
}
void H_29(double *state, double *unused, double *out_6512812911266961158) {
   out_6512812911266961158[0] = 0;
   out_6512812911266961158[1] = 1;
   out_6512812911266961158[2] = 0;
   out_6512812911266961158[3] = 0;
   out_6512812911266961158[4] = 0;
   out_6512812911266961158[5] = 0;
   out_6512812911266961158[6] = 0;
   out_6512812911266961158[7] = 0;
   out_6512812911266961158[8] = 0;
}
void h_28(double *state, double *unused, double *out_8329978581973507615) {
   out_8329978581973507615[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2453174762388691756) {
   out_2453174762388691756[0] = 1;
   out_2453174762388691756[1] = 0;
   out_2453174762388691756[2] = 0;
   out_2453174762388691756[3] = 0;
   out_2453174762388691756[4] = 0;
   out_2453174762388691756[5] = 0;
   out_2453174762388691756[6] = 0;
   out_2453174762388691756[7] = 0;
   out_2453174762388691756[8] = 0;
}
void h_31(double *state, double *unused, double *out_222736560719300508) {
   out_222736560719300508[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4537655438513541947) {
   out_4537655438513541947[0] = 0;
   out_4537655438513541947[1] = 0;
   out_4537655438513541947[2] = 0;
   out_4537655438513541947[3] = 0;
   out_4537655438513541947[4] = 0;
   out_4537655438513541947[5] = 0;
   out_4537655438513541947[6] = 0;
   out_4537655438513541947[7] = 0;
   out_4537655438513541947[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_587611173581676283) {
  err_fun(nom_x, delta_x, out_587611173581676283);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8120728011522269919) {
  inv_err_fun(nom_x, true_x, out_8120728011522269919);
}
void car_H_mod_fun(double *state, double *out_4001675034436284807) {
  H_mod_fun(state, out_4001675034436284807);
}
void car_f_fun(double *state, double dt, double *out_6995360374056238489) {
  f_fun(state,  dt, out_6995360374056238489);
}
void car_F_fun(double *state, double dt, double *out_5620828310005666299) {
  F_fun(state,  dt, out_5620828310005666299);
}
void car_h_25(double *state, double *unused, double *out_5932710635121359621) {
  h_25(state, unused, out_5932710635121359621);
}
void car_H_25(double *state, double *unused, double *out_4507009476636581519) {
  H_25(state, unused, out_4507009476636581519);
}
void car_h_24(double *state, double *unused, double *out_8960081603047522700) {
  h_24(state, unused, out_8960081603047522700);
}
void car_H_24(double *state, double *unused, double *out_7364162790481451996) {
  H_24(state, unused, out_7364162790481451996);
}
void car_h_30(double *state, double *unused, double *out_6293656255741178026) {
  h_30(state, unused, out_6293656255741178026);
}
void car_H_30(double *state, double *unused, double *out_7023044255581353342) {
  H_30(state, unused, out_7023044255581353342);
}
void car_h_26(double *state, double *unused, double *out_7151414550307527945) {
  h_26(state, unused, out_7151414550307527945);
}
void car_H_26(double *state, double *unused, double *out_765506157762525295) {
  H_26(state, unused, out_765506157762525295);
}
void car_h_27(double *state, double *unused, double *out_7512360170927346350) {
  h_27(state, unused, out_7512360170927346350);
}
void car_H_27(double *state, double *unused, double *out_9197807567381778253) {
  H_27(state, unused, out_9197807567381778253);
}
void car_h_29(double *state, double *unused, double *out_3171118645961532825) {
  h_29(state, unused, out_3171118645961532825);
}
void car_H_29(double *state, double *unused, double *out_6512812911266961158) {
  H_29(state, unused, out_6512812911266961158);
}
void car_h_28(double *state, double *unused, double *out_8329978581973507615) {
  h_28(state, unused, out_8329978581973507615);
}
void car_H_28(double *state, double *unused, double *out_2453174762388691756) {
  H_28(state, unused, out_2453174762388691756);
}
void car_h_31(double *state, double *unused, double *out_222736560719300508) {
  h_31(state, unused, out_222736560719300508);
}
void car_H_31(double *state, double *unused, double *out_4537655438513541947) {
  H_31(state, unused, out_4537655438513541947);
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
