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
void err_fun(double *nom_x, double *delta_x, double *out_2249508041139738373) {
   out_2249508041139738373[0] = delta_x[0] + nom_x[0];
   out_2249508041139738373[1] = delta_x[1] + nom_x[1];
   out_2249508041139738373[2] = delta_x[2] + nom_x[2];
   out_2249508041139738373[3] = delta_x[3] + nom_x[3];
   out_2249508041139738373[4] = delta_x[4] + nom_x[4];
   out_2249508041139738373[5] = delta_x[5] + nom_x[5];
   out_2249508041139738373[6] = delta_x[6] + nom_x[6];
   out_2249508041139738373[7] = delta_x[7] + nom_x[7];
   out_2249508041139738373[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4788524825292355547) {
   out_4788524825292355547[0] = -nom_x[0] + true_x[0];
   out_4788524825292355547[1] = -nom_x[1] + true_x[1];
   out_4788524825292355547[2] = -nom_x[2] + true_x[2];
   out_4788524825292355547[3] = -nom_x[3] + true_x[3];
   out_4788524825292355547[4] = -nom_x[4] + true_x[4];
   out_4788524825292355547[5] = -nom_x[5] + true_x[5];
   out_4788524825292355547[6] = -nom_x[6] + true_x[6];
   out_4788524825292355547[7] = -nom_x[7] + true_x[7];
   out_4788524825292355547[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5143375091155045702) {
   out_5143375091155045702[0] = 1.0;
   out_5143375091155045702[1] = 0.0;
   out_5143375091155045702[2] = 0.0;
   out_5143375091155045702[3] = 0.0;
   out_5143375091155045702[4] = 0.0;
   out_5143375091155045702[5] = 0.0;
   out_5143375091155045702[6] = 0.0;
   out_5143375091155045702[7] = 0.0;
   out_5143375091155045702[8] = 0.0;
   out_5143375091155045702[9] = 0.0;
   out_5143375091155045702[10] = 1.0;
   out_5143375091155045702[11] = 0.0;
   out_5143375091155045702[12] = 0.0;
   out_5143375091155045702[13] = 0.0;
   out_5143375091155045702[14] = 0.0;
   out_5143375091155045702[15] = 0.0;
   out_5143375091155045702[16] = 0.0;
   out_5143375091155045702[17] = 0.0;
   out_5143375091155045702[18] = 0.0;
   out_5143375091155045702[19] = 0.0;
   out_5143375091155045702[20] = 1.0;
   out_5143375091155045702[21] = 0.0;
   out_5143375091155045702[22] = 0.0;
   out_5143375091155045702[23] = 0.0;
   out_5143375091155045702[24] = 0.0;
   out_5143375091155045702[25] = 0.0;
   out_5143375091155045702[26] = 0.0;
   out_5143375091155045702[27] = 0.0;
   out_5143375091155045702[28] = 0.0;
   out_5143375091155045702[29] = 0.0;
   out_5143375091155045702[30] = 1.0;
   out_5143375091155045702[31] = 0.0;
   out_5143375091155045702[32] = 0.0;
   out_5143375091155045702[33] = 0.0;
   out_5143375091155045702[34] = 0.0;
   out_5143375091155045702[35] = 0.0;
   out_5143375091155045702[36] = 0.0;
   out_5143375091155045702[37] = 0.0;
   out_5143375091155045702[38] = 0.0;
   out_5143375091155045702[39] = 0.0;
   out_5143375091155045702[40] = 1.0;
   out_5143375091155045702[41] = 0.0;
   out_5143375091155045702[42] = 0.0;
   out_5143375091155045702[43] = 0.0;
   out_5143375091155045702[44] = 0.0;
   out_5143375091155045702[45] = 0.0;
   out_5143375091155045702[46] = 0.0;
   out_5143375091155045702[47] = 0.0;
   out_5143375091155045702[48] = 0.0;
   out_5143375091155045702[49] = 0.0;
   out_5143375091155045702[50] = 1.0;
   out_5143375091155045702[51] = 0.0;
   out_5143375091155045702[52] = 0.0;
   out_5143375091155045702[53] = 0.0;
   out_5143375091155045702[54] = 0.0;
   out_5143375091155045702[55] = 0.0;
   out_5143375091155045702[56] = 0.0;
   out_5143375091155045702[57] = 0.0;
   out_5143375091155045702[58] = 0.0;
   out_5143375091155045702[59] = 0.0;
   out_5143375091155045702[60] = 1.0;
   out_5143375091155045702[61] = 0.0;
   out_5143375091155045702[62] = 0.0;
   out_5143375091155045702[63] = 0.0;
   out_5143375091155045702[64] = 0.0;
   out_5143375091155045702[65] = 0.0;
   out_5143375091155045702[66] = 0.0;
   out_5143375091155045702[67] = 0.0;
   out_5143375091155045702[68] = 0.0;
   out_5143375091155045702[69] = 0.0;
   out_5143375091155045702[70] = 1.0;
   out_5143375091155045702[71] = 0.0;
   out_5143375091155045702[72] = 0.0;
   out_5143375091155045702[73] = 0.0;
   out_5143375091155045702[74] = 0.0;
   out_5143375091155045702[75] = 0.0;
   out_5143375091155045702[76] = 0.0;
   out_5143375091155045702[77] = 0.0;
   out_5143375091155045702[78] = 0.0;
   out_5143375091155045702[79] = 0.0;
   out_5143375091155045702[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_223721292699517100) {
   out_223721292699517100[0] = state[0];
   out_223721292699517100[1] = state[1];
   out_223721292699517100[2] = state[2];
   out_223721292699517100[3] = state[3];
   out_223721292699517100[4] = state[4];
   out_223721292699517100[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_223721292699517100[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_223721292699517100[7] = state[7];
   out_223721292699517100[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6998880572782646555) {
   out_6998880572782646555[0] = 1;
   out_6998880572782646555[1] = 0;
   out_6998880572782646555[2] = 0;
   out_6998880572782646555[3] = 0;
   out_6998880572782646555[4] = 0;
   out_6998880572782646555[5] = 0;
   out_6998880572782646555[6] = 0;
   out_6998880572782646555[7] = 0;
   out_6998880572782646555[8] = 0;
   out_6998880572782646555[9] = 0;
   out_6998880572782646555[10] = 1;
   out_6998880572782646555[11] = 0;
   out_6998880572782646555[12] = 0;
   out_6998880572782646555[13] = 0;
   out_6998880572782646555[14] = 0;
   out_6998880572782646555[15] = 0;
   out_6998880572782646555[16] = 0;
   out_6998880572782646555[17] = 0;
   out_6998880572782646555[18] = 0;
   out_6998880572782646555[19] = 0;
   out_6998880572782646555[20] = 1;
   out_6998880572782646555[21] = 0;
   out_6998880572782646555[22] = 0;
   out_6998880572782646555[23] = 0;
   out_6998880572782646555[24] = 0;
   out_6998880572782646555[25] = 0;
   out_6998880572782646555[26] = 0;
   out_6998880572782646555[27] = 0;
   out_6998880572782646555[28] = 0;
   out_6998880572782646555[29] = 0;
   out_6998880572782646555[30] = 1;
   out_6998880572782646555[31] = 0;
   out_6998880572782646555[32] = 0;
   out_6998880572782646555[33] = 0;
   out_6998880572782646555[34] = 0;
   out_6998880572782646555[35] = 0;
   out_6998880572782646555[36] = 0;
   out_6998880572782646555[37] = 0;
   out_6998880572782646555[38] = 0;
   out_6998880572782646555[39] = 0;
   out_6998880572782646555[40] = 1;
   out_6998880572782646555[41] = 0;
   out_6998880572782646555[42] = 0;
   out_6998880572782646555[43] = 0;
   out_6998880572782646555[44] = 0;
   out_6998880572782646555[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6998880572782646555[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6998880572782646555[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6998880572782646555[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6998880572782646555[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6998880572782646555[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6998880572782646555[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6998880572782646555[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6998880572782646555[53] = -9.8100000000000005*dt;
   out_6998880572782646555[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6998880572782646555[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6998880572782646555[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6998880572782646555[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6998880572782646555[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6998880572782646555[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6998880572782646555[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6998880572782646555[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6998880572782646555[62] = 0;
   out_6998880572782646555[63] = 0;
   out_6998880572782646555[64] = 0;
   out_6998880572782646555[65] = 0;
   out_6998880572782646555[66] = 0;
   out_6998880572782646555[67] = 0;
   out_6998880572782646555[68] = 0;
   out_6998880572782646555[69] = 0;
   out_6998880572782646555[70] = 1;
   out_6998880572782646555[71] = 0;
   out_6998880572782646555[72] = 0;
   out_6998880572782646555[73] = 0;
   out_6998880572782646555[74] = 0;
   out_6998880572782646555[75] = 0;
   out_6998880572782646555[76] = 0;
   out_6998880572782646555[77] = 0;
   out_6998880572782646555[78] = 0;
   out_6998880572782646555[79] = 0;
   out_6998880572782646555[80] = 1;
}
void h_25(double *state, double *unused, double *out_6606540369410235194) {
   out_6606540369410235194[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8666423729800410850) {
   out_8666423729800410850[0] = 0;
   out_8666423729800410850[1] = 0;
   out_8666423729800410850[2] = 0;
   out_8666423729800410850[3] = 0;
   out_8666423729800410850[4] = 0;
   out_8666423729800410850[5] = 0;
   out_8666423729800410850[6] = 1;
   out_8666423729800410850[7] = 0;
   out_8666423729800410850[8] = 0;
}
void h_24(double *state, double *unused, double *out_4049880123285190269) {
   out_4049880123285190269[0] = state[4];
   out_4049880123285190269[1] = state[5];
}
void H_24(double *state, double *unused, double *out_5108498130998087714) {
   out_5108498130998087714[0] = 0;
   out_5108498130998087714[1] = 0;
   out_5108498130998087714[2] = 0;
   out_5108498130998087714[3] = 0;
   out_5108498130998087714[4] = 1;
   out_5108498130998087714[5] = 0;
   out_5108498130998087714[6] = 0;
   out_5108498130998087714[7] = 0;
   out_5108498130998087714[8] = 0;
   out_5108498130998087714[9] = 0;
   out_5108498130998087714[10] = 0;
   out_5108498130998087714[11] = 0;
   out_5108498130998087714[12] = 0;
   out_5108498130998087714[13] = 0;
   out_5108498130998087714[14] = 1;
   out_5108498130998087714[15] = 0;
   out_5108498130998087714[16] = 0;
   out_5108498130998087714[17] = 0;
}
void h_30(double *state, double *unused, double *out_164294856940115742) {
   out_164294856940115742[0] = state[4];
}
void H_30(double *state, double *unused, double *out_1749733388308794095) {
   out_1749733388308794095[0] = 0;
   out_1749733388308794095[1] = 0;
   out_1749733388308794095[2] = 0;
   out_1749733388308794095[3] = 0;
   out_1749733388308794095[4] = 1;
   out_1749733388308794095[5] = 0;
   out_1749733388308794095[6] = 0;
   out_1749733388308794095[7] = 0;
   out_1749733388308794095[8] = 0;
}
void h_26(double *state, double *unused, double *out_767610741616593259) {
   out_767610741616593259[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6038817025035084542) {
   out_6038817025035084542[0] = 0;
   out_6038817025035084542[1] = 0;
   out_6038817025035084542[2] = 0;
   out_6038817025035084542[3] = 0;
   out_6038817025035084542[4] = 0;
   out_6038817025035084542[5] = 0;
   out_6038817025035084542[6] = 0;
   out_6038817025035084542[7] = 1;
   out_6038817025035084542[8] = 0;
}
void h_27(double *state, double *unused, double *out_9132294156050629254) {
   out_9132294156050629254[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3924496700109219006) {
   out_3924496700109219006[0] = 0;
   out_3924496700109219006[1] = 0;
   out_3924496700109219006[2] = 0;
   out_3924496700109219006[3] = 1;
   out_3924496700109219006[4] = 0;
   out_3924496700109219006[5] = 0;
   out_3924496700109219006[6] = 0;
   out_3924496700109219006[7] = 0;
   out_3924496700109219006[8] = 0;
}
void h_29(double *state, double *unused, double *out_2543614691308571426) {
   out_2543614691308571426[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5637859426978770039) {
   out_5637859426978770039[0] = 0;
   out_5637859426978770039[1] = 1;
   out_5637859426978770039[2] = 0;
   out_5637859426978770039[3] = 0;
   out_5637859426978770039[4] = 0;
   out_5637859426978770039[5] = 0;
   out_5637859426978770039[6] = 0;
   out_5637859426978770039[7] = 0;
   out_5637859426978770039[8] = 0;
}
void h_28(double *state, double *unused, double *out_3987404092934981717) {
   out_3987404092934981717[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7726485629661251003) {
   out_7726485629661251003[0] = 1;
   out_7726485629661251003[1] = 0;
   out_7726485629661251003[2] = 0;
   out_7726485629661251003[3] = 0;
   out_7726485629661251003[4] = 0;
   out_7726485629661251003[5] = 0;
   out_7726485629661251003[6] = 0;
   out_7726485629661251003[7] = 0;
   out_7726485629661251003[8] = 0;
}
void h_31(double *state, double *unused, double *out_6594936115065281760) {
   out_6594936115065281760[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8635777767923450422) {
   out_8635777767923450422[0] = 0;
   out_8635777767923450422[1] = 0;
   out_8635777767923450422[2] = 0;
   out_8635777767923450422[3] = 0;
   out_8635777767923450422[4] = 0;
   out_8635777767923450422[5] = 0;
   out_8635777767923450422[6] = 0;
   out_8635777767923450422[7] = 0;
   out_8635777767923450422[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2249508041139738373) {
  err_fun(nom_x, delta_x, out_2249508041139738373);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4788524825292355547) {
  inv_err_fun(nom_x, true_x, out_4788524825292355547);
}
void car_H_mod_fun(double *state, double *out_5143375091155045702) {
  H_mod_fun(state, out_5143375091155045702);
}
void car_f_fun(double *state, double dt, double *out_223721292699517100) {
  f_fun(state,  dt, out_223721292699517100);
}
void car_F_fun(double *state, double dt, double *out_6998880572782646555) {
  F_fun(state,  dt, out_6998880572782646555);
}
void car_h_25(double *state, double *unused, double *out_6606540369410235194) {
  h_25(state, unused, out_6606540369410235194);
}
void car_H_25(double *state, double *unused, double *out_8666423729800410850) {
  H_25(state, unused, out_8666423729800410850);
}
void car_h_24(double *state, double *unused, double *out_4049880123285190269) {
  h_24(state, unused, out_4049880123285190269);
}
void car_H_24(double *state, double *unused, double *out_5108498130998087714) {
  H_24(state, unused, out_5108498130998087714);
}
void car_h_30(double *state, double *unused, double *out_164294856940115742) {
  h_30(state, unused, out_164294856940115742);
}
void car_H_30(double *state, double *unused, double *out_1749733388308794095) {
  H_30(state, unused, out_1749733388308794095);
}
void car_h_26(double *state, double *unused, double *out_767610741616593259) {
  h_26(state, unused, out_767610741616593259);
}
void car_H_26(double *state, double *unused, double *out_6038817025035084542) {
  H_26(state, unused, out_6038817025035084542);
}
void car_h_27(double *state, double *unused, double *out_9132294156050629254) {
  h_27(state, unused, out_9132294156050629254);
}
void car_H_27(double *state, double *unused, double *out_3924496700109219006) {
  H_27(state, unused, out_3924496700109219006);
}
void car_h_29(double *state, double *unused, double *out_2543614691308571426) {
  h_29(state, unused, out_2543614691308571426);
}
void car_H_29(double *state, double *unused, double *out_5637859426978770039) {
  H_29(state, unused, out_5637859426978770039);
}
void car_h_28(double *state, double *unused, double *out_3987404092934981717) {
  h_28(state, unused, out_3987404092934981717);
}
void car_H_28(double *state, double *unused, double *out_7726485629661251003) {
  H_28(state, unused, out_7726485629661251003);
}
void car_h_31(double *state, double *unused, double *out_6594936115065281760) {
  h_31(state, unused, out_6594936115065281760);
}
void car_H_31(double *state, double *unused, double *out_8635777767923450422) {
  H_31(state, unused, out_8635777767923450422);
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
