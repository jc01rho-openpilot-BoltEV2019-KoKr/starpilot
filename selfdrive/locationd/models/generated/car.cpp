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
void err_fun(double *nom_x, double *delta_x, double *out_3329877133651101623) {
   out_3329877133651101623[0] = delta_x[0] + nom_x[0];
   out_3329877133651101623[1] = delta_x[1] + nom_x[1];
   out_3329877133651101623[2] = delta_x[2] + nom_x[2];
   out_3329877133651101623[3] = delta_x[3] + nom_x[3];
   out_3329877133651101623[4] = delta_x[4] + nom_x[4];
   out_3329877133651101623[5] = delta_x[5] + nom_x[5];
   out_3329877133651101623[6] = delta_x[6] + nom_x[6];
   out_3329877133651101623[7] = delta_x[7] + nom_x[7];
   out_3329877133651101623[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7760882190653564987) {
   out_7760882190653564987[0] = -nom_x[0] + true_x[0];
   out_7760882190653564987[1] = -nom_x[1] + true_x[1];
   out_7760882190653564987[2] = -nom_x[2] + true_x[2];
   out_7760882190653564987[3] = -nom_x[3] + true_x[3];
   out_7760882190653564987[4] = -nom_x[4] + true_x[4];
   out_7760882190653564987[5] = -nom_x[5] + true_x[5];
   out_7760882190653564987[6] = -nom_x[6] + true_x[6];
   out_7760882190653564987[7] = -nom_x[7] + true_x[7];
   out_7760882190653564987[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1773647306661711299) {
   out_1773647306661711299[0] = 1.0;
   out_1773647306661711299[1] = 0.0;
   out_1773647306661711299[2] = 0.0;
   out_1773647306661711299[3] = 0.0;
   out_1773647306661711299[4] = 0.0;
   out_1773647306661711299[5] = 0.0;
   out_1773647306661711299[6] = 0.0;
   out_1773647306661711299[7] = 0.0;
   out_1773647306661711299[8] = 0.0;
   out_1773647306661711299[9] = 0.0;
   out_1773647306661711299[10] = 1.0;
   out_1773647306661711299[11] = 0.0;
   out_1773647306661711299[12] = 0.0;
   out_1773647306661711299[13] = 0.0;
   out_1773647306661711299[14] = 0.0;
   out_1773647306661711299[15] = 0.0;
   out_1773647306661711299[16] = 0.0;
   out_1773647306661711299[17] = 0.0;
   out_1773647306661711299[18] = 0.0;
   out_1773647306661711299[19] = 0.0;
   out_1773647306661711299[20] = 1.0;
   out_1773647306661711299[21] = 0.0;
   out_1773647306661711299[22] = 0.0;
   out_1773647306661711299[23] = 0.0;
   out_1773647306661711299[24] = 0.0;
   out_1773647306661711299[25] = 0.0;
   out_1773647306661711299[26] = 0.0;
   out_1773647306661711299[27] = 0.0;
   out_1773647306661711299[28] = 0.0;
   out_1773647306661711299[29] = 0.0;
   out_1773647306661711299[30] = 1.0;
   out_1773647306661711299[31] = 0.0;
   out_1773647306661711299[32] = 0.0;
   out_1773647306661711299[33] = 0.0;
   out_1773647306661711299[34] = 0.0;
   out_1773647306661711299[35] = 0.0;
   out_1773647306661711299[36] = 0.0;
   out_1773647306661711299[37] = 0.0;
   out_1773647306661711299[38] = 0.0;
   out_1773647306661711299[39] = 0.0;
   out_1773647306661711299[40] = 1.0;
   out_1773647306661711299[41] = 0.0;
   out_1773647306661711299[42] = 0.0;
   out_1773647306661711299[43] = 0.0;
   out_1773647306661711299[44] = 0.0;
   out_1773647306661711299[45] = 0.0;
   out_1773647306661711299[46] = 0.0;
   out_1773647306661711299[47] = 0.0;
   out_1773647306661711299[48] = 0.0;
   out_1773647306661711299[49] = 0.0;
   out_1773647306661711299[50] = 1.0;
   out_1773647306661711299[51] = 0.0;
   out_1773647306661711299[52] = 0.0;
   out_1773647306661711299[53] = 0.0;
   out_1773647306661711299[54] = 0.0;
   out_1773647306661711299[55] = 0.0;
   out_1773647306661711299[56] = 0.0;
   out_1773647306661711299[57] = 0.0;
   out_1773647306661711299[58] = 0.0;
   out_1773647306661711299[59] = 0.0;
   out_1773647306661711299[60] = 1.0;
   out_1773647306661711299[61] = 0.0;
   out_1773647306661711299[62] = 0.0;
   out_1773647306661711299[63] = 0.0;
   out_1773647306661711299[64] = 0.0;
   out_1773647306661711299[65] = 0.0;
   out_1773647306661711299[66] = 0.0;
   out_1773647306661711299[67] = 0.0;
   out_1773647306661711299[68] = 0.0;
   out_1773647306661711299[69] = 0.0;
   out_1773647306661711299[70] = 1.0;
   out_1773647306661711299[71] = 0.0;
   out_1773647306661711299[72] = 0.0;
   out_1773647306661711299[73] = 0.0;
   out_1773647306661711299[74] = 0.0;
   out_1773647306661711299[75] = 0.0;
   out_1773647306661711299[76] = 0.0;
   out_1773647306661711299[77] = 0.0;
   out_1773647306661711299[78] = 0.0;
   out_1773647306661711299[79] = 0.0;
   out_1773647306661711299[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8265395554005205627) {
   out_8265395554005205627[0] = state[0];
   out_8265395554005205627[1] = state[1];
   out_8265395554005205627[2] = state[2];
   out_8265395554005205627[3] = state[3];
   out_8265395554005205627[4] = state[4];
   out_8265395554005205627[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8265395554005205627[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8265395554005205627[7] = state[7];
   out_8265395554005205627[8] = state[8];
}
void F_fun(double *state, double dt, double *out_5121501708015469294) {
   out_5121501708015469294[0] = 1;
   out_5121501708015469294[1] = 0;
   out_5121501708015469294[2] = 0;
   out_5121501708015469294[3] = 0;
   out_5121501708015469294[4] = 0;
   out_5121501708015469294[5] = 0;
   out_5121501708015469294[6] = 0;
   out_5121501708015469294[7] = 0;
   out_5121501708015469294[8] = 0;
   out_5121501708015469294[9] = 0;
   out_5121501708015469294[10] = 1;
   out_5121501708015469294[11] = 0;
   out_5121501708015469294[12] = 0;
   out_5121501708015469294[13] = 0;
   out_5121501708015469294[14] = 0;
   out_5121501708015469294[15] = 0;
   out_5121501708015469294[16] = 0;
   out_5121501708015469294[17] = 0;
   out_5121501708015469294[18] = 0;
   out_5121501708015469294[19] = 0;
   out_5121501708015469294[20] = 1;
   out_5121501708015469294[21] = 0;
   out_5121501708015469294[22] = 0;
   out_5121501708015469294[23] = 0;
   out_5121501708015469294[24] = 0;
   out_5121501708015469294[25] = 0;
   out_5121501708015469294[26] = 0;
   out_5121501708015469294[27] = 0;
   out_5121501708015469294[28] = 0;
   out_5121501708015469294[29] = 0;
   out_5121501708015469294[30] = 1;
   out_5121501708015469294[31] = 0;
   out_5121501708015469294[32] = 0;
   out_5121501708015469294[33] = 0;
   out_5121501708015469294[34] = 0;
   out_5121501708015469294[35] = 0;
   out_5121501708015469294[36] = 0;
   out_5121501708015469294[37] = 0;
   out_5121501708015469294[38] = 0;
   out_5121501708015469294[39] = 0;
   out_5121501708015469294[40] = 1;
   out_5121501708015469294[41] = 0;
   out_5121501708015469294[42] = 0;
   out_5121501708015469294[43] = 0;
   out_5121501708015469294[44] = 0;
   out_5121501708015469294[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_5121501708015469294[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_5121501708015469294[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5121501708015469294[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5121501708015469294[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_5121501708015469294[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_5121501708015469294[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_5121501708015469294[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_5121501708015469294[53] = -9.8100000000000005*dt;
   out_5121501708015469294[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_5121501708015469294[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_5121501708015469294[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5121501708015469294[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5121501708015469294[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_5121501708015469294[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_5121501708015469294[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_5121501708015469294[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5121501708015469294[62] = 0;
   out_5121501708015469294[63] = 0;
   out_5121501708015469294[64] = 0;
   out_5121501708015469294[65] = 0;
   out_5121501708015469294[66] = 0;
   out_5121501708015469294[67] = 0;
   out_5121501708015469294[68] = 0;
   out_5121501708015469294[69] = 0;
   out_5121501708015469294[70] = 1;
   out_5121501708015469294[71] = 0;
   out_5121501708015469294[72] = 0;
   out_5121501708015469294[73] = 0;
   out_5121501708015469294[74] = 0;
   out_5121501708015469294[75] = 0;
   out_5121501708015469294[76] = 0;
   out_5121501708015469294[77] = 0;
   out_5121501708015469294[78] = 0;
   out_5121501708015469294[79] = 0;
   out_5121501708015469294[80] = 1;
}
void h_25(double *state, double *unused, double *out_1871114119926472838) {
   out_1871114119926472838[0] = state[6];
}
void H_25(double *state, double *unused, double *out_1749401331983653849) {
   out_1749401331983653849[0] = 0;
   out_1749401331983653849[1] = 0;
   out_1749401331983653849[2] = 0;
   out_1749401331983653849[3] = 0;
   out_1749401331983653849[4] = 0;
   out_1749401331983653849[5] = 0;
   out_1749401331983653849[6] = 1;
   out_1749401331983653849[7] = 0;
   out_1749401331983653849[8] = 0;
}
void h_24(double *state, double *unused, double *out_4177328874243606255) {
   out_4177328874243606255[0] = state[4];
   out_4177328874243606255[1] = state[5];
}
void H_24(double *state, double *unused, double *out_1808524266818669287) {
   out_1808524266818669287[0] = 0;
   out_1808524266818669287[1] = 0;
   out_1808524266818669287[2] = 0;
   out_1808524266818669287[3] = 0;
   out_1808524266818669287[4] = 1;
   out_1808524266818669287[5] = 0;
   out_1808524266818669287[6] = 0;
   out_1808524266818669287[7] = 0;
   out_1808524266818669287[8] = 0;
   out_1808524266818669287[9] = 0;
   out_1808524266818669287[10] = 0;
   out_1808524266818669287[11] = 0;
   out_1808524266818669287[12] = 0;
   out_1808524266818669287[13] = 0;
   out_1808524266818669287[14] = 1;
   out_1808524266818669287[15] = 0;
   out_1808524266818669287[16] = 0;
   out_1808524266818669287[17] = 0;
}
void h_30(double *state, double *unused, double *out_6625546561337267154) {
   out_6625546561337267154[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5167289009507962906) {
   out_5167289009507962906[0] = 0;
   out_5167289009507962906[1] = 0;
   out_5167289009507962906[2] = 0;
   out_5167289009507962906[3] = 0;
   out_5167289009507962906[4] = 1;
   out_5167289009507962906[5] = 0;
   out_5167289009507962906[6] = 0;
   out_5167289009507962906[7] = 0;
   out_5167289009507962906[8] = 0;
}
void h_26(double *state, double *unused, double *out_8545349699624827873) {
   out_8545349699624827873[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5490904650857710073) {
   out_5490904650857710073[0] = 0;
   out_5490904650857710073[1] = 0;
   out_5490904650857710073[2] = 0;
   out_5490904650857710073[3] = 0;
   out_5490904650857710073[4] = 0;
   out_5490904650857710073[5] = 0;
   out_5490904650857710073[6] = 0;
   out_5490904650857710073[7] = 1;
   out_5490904650857710073[8] = 0;
}
void h_27(double *state, double *unused, double *out_3470753115959557725) {
   out_3470753115959557725[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2992525697707537995) {
   out_2992525697707537995[0] = 0;
   out_2992525697707537995[1] = 0;
   out_2992525697707537995[2] = 0;
   out_2992525697707537995[3] = 1;
   out_2992525697707537995[4] = 0;
   out_2992525697707537995[5] = 0;
   out_2992525697707537995[6] = 0;
   out_2992525697707537995[7] = 0;
   out_2992525697707537995[8] = 0;
}
void h_29(double *state, double *unused, double *out_7569056414238929589) {
   out_7569056414238929589[0] = state[1];
}
void H_29(double *state, double *unused, double *out_1279162970837986962) {
   out_1279162970837986962[0] = 0;
   out_1279162970837986962[1] = 1;
   out_1279162970837986962[2] = 0;
   out_1279162970837986962[3] = 0;
   out_1279162970837986962[4] = 0;
   out_1279162970837986962[5] = 0;
   out_1279162970837986962[6] = 0;
   out_1279162970837986962[7] = 0;
   out_1279162970837986962[8] = 0;
}
void h_28(double *state, double *unused, double *out_6507539167403890410) {
   out_6507539167403890410[0] = state[0];
}
void H_28(double *state, double *unused, double *out_3803236046231543612) {
   out_3803236046231543612[0] = 1;
   out_3803236046231543612[1] = 0;
   out_3803236046231543612[2] = 0;
   out_3803236046231543612[3] = 0;
   out_3803236046231543612[4] = 0;
   out_3803236046231543612[5] = 0;
   out_3803236046231543612[6] = 0;
   out_3803236046231543612[7] = 0;
   out_3803236046231543612[8] = 0;
}
void h_31(double *state, double *unused, double *out_5594040852719868954) {
   out_5594040852719868954[0] = state[8];
}
void H_31(double *state, double *unused, double *out_1718755370106693421) {
   out_1718755370106693421[0] = 0;
   out_1718755370106693421[1] = 0;
   out_1718755370106693421[2] = 0;
   out_1718755370106693421[3] = 0;
   out_1718755370106693421[4] = 0;
   out_1718755370106693421[5] = 0;
   out_1718755370106693421[6] = 0;
   out_1718755370106693421[7] = 0;
   out_1718755370106693421[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_3329877133651101623) {
  err_fun(nom_x, delta_x, out_3329877133651101623);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7760882190653564987) {
  inv_err_fun(nom_x, true_x, out_7760882190653564987);
}
void car_H_mod_fun(double *state, double *out_1773647306661711299) {
  H_mod_fun(state, out_1773647306661711299);
}
void car_f_fun(double *state, double dt, double *out_8265395554005205627) {
  f_fun(state,  dt, out_8265395554005205627);
}
void car_F_fun(double *state, double dt, double *out_5121501708015469294) {
  F_fun(state,  dt, out_5121501708015469294);
}
void car_h_25(double *state, double *unused, double *out_1871114119926472838) {
  h_25(state, unused, out_1871114119926472838);
}
void car_H_25(double *state, double *unused, double *out_1749401331983653849) {
  H_25(state, unused, out_1749401331983653849);
}
void car_h_24(double *state, double *unused, double *out_4177328874243606255) {
  h_24(state, unused, out_4177328874243606255);
}
void car_H_24(double *state, double *unused, double *out_1808524266818669287) {
  H_24(state, unused, out_1808524266818669287);
}
void car_h_30(double *state, double *unused, double *out_6625546561337267154) {
  h_30(state, unused, out_6625546561337267154);
}
void car_H_30(double *state, double *unused, double *out_5167289009507962906) {
  H_30(state, unused, out_5167289009507962906);
}
void car_h_26(double *state, double *unused, double *out_8545349699624827873) {
  h_26(state, unused, out_8545349699624827873);
}
void car_H_26(double *state, double *unused, double *out_5490904650857710073) {
  H_26(state, unused, out_5490904650857710073);
}
void car_h_27(double *state, double *unused, double *out_3470753115959557725) {
  h_27(state, unused, out_3470753115959557725);
}
void car_H_27(double *state, double *unused, double *out_2992525697707537995) {
  H_27(state, unused, out_2992525697707537995);
}
void car_h_29(double *state, double *unused, double *out_7569056414238929589) {
  h_29(state, unused, out_7569056414238929589);
}
void car_H_29(double *state, double *unused, double *out_1279162970837986962) {
  H_29(state, unused, out_1279162970837986962);
}
void car_h_28(double *state, double *unused, double *out_6507539167403890410) {
  h_28(state, unused, out_6507539167403890410);
}
void car_H_28(double *state, double *unused, double *out_3803236046231543612) {
  H_28(state, unused, out_3803236046231543612);
}
void car_h_31(double *state, double *unused, double *out_5594040852719868954) {
  h_31(state, unused, out_5594040852719868954);
}
void car_H_31(double *state, double *unused, double *out_1718755370106693421) {
  H_31(state, unused, out_1718755370106693421);
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
