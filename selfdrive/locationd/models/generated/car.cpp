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
void err_fun(double *nom_x, double *delta_x, double *out_2503888728252844227) {
   out_2503888728252844227[0] = delta_x[0] + nom_x[0];
   out_2503888728252844227[1] = delta_x[1] + nom_x[1];
   out_2503888728252844227[2] = delta_x[2] + nom_x[2];
   out_2503888728252844227[3] = delta_x[3] + nom_x[3];
   out_2503888728252844227[4] = delta_x[4] + nom_x[4];
   out_2503888728252844227[5] = delta_x[5] + nom_x[5];
   out_2503888728252844227[6] = delta_x[6] + nom_x[6];
   out_2503888728252844227[7] = delta_x[7] + nom_x[7];
   out_2503888728252844227[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3671647430606809601) {
   out_3671647430606809601[0] = -nom_x[0] + true_x[0];
   out_3671647430606809601[1] = -nom_x[1] + true_x[1];
   out_3671647430606809601[2] = -nom_x[2] + true_x[2];
   out_3671647430606809601[3] = -nom_x[3] + true_x[3];
   out_3671647430606809601[4] = -nom_x[4] + true_x[4];
   out_3671647430606809601[5] = -nom_x[5] + true_x[5];
   out_3671647430606809601[6] = -nom_x[6] + true_x[6];
   out_3671647430606809601[7] = -nom_x[7] + true_x[7];
   out_3671647430606809601[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3172612914634759799) {
   out_3172612914634759799[0] = 1.0;
   out_3172612914634759799[1] = 0.0;
   out_3172612914634759799[2] = 0.0;
   out_3172612914634759799[3] = 0.0;
   out_3172612914634759799[4] = 0.0;
   out_3172612914634759799[5] = 0.0;
   out_3172612914634759799[6] = 0.0;
   out_3172612914634759799[7] = 0.0;
   out_3172612914634759799[8] = 0.0;
   out_3172612914634759799[9] = 0.0;
   out_3172612914634759799[10] = 1.0;
   out_3172612914634759799[11] = 0.0;
   out_3172612914634759799[12] = 0.0;
   out_3172612914634759799[13] = 0.0;
   out_3172612914634759799[14] = 0.0;
   out_3172612914634759799[15] = 0.0;
   out_3172612914634759799[16] = 0.0;
   out_3172612914634759799[17] = 0.0;
   out_3172612914634759799[18] = 0.0;
   out_3172612914634759799[19] = 0.0;
   out_3172612914634759799[20] = 1.0;
   out_3172612914634759799[21] = 0.0;
   out_3172612914634759799[22] = 0.0;
   out_3172612914634759799[23] = 0.0;
   out_3172612914634759799[24] = 0.0;
   out_3172612914634759799[25] = 0.0;
   out_3172612914634759799[26] = 0.0;
   out_3172612914634759799[27] = 0.0;
   out_3172612914634759799[28] = 0.0;
   out_3172612914634759799[29] = 0.0;
   out_3172612914634759799[30] = 1.0;
   out_3172612914634759799[31] = 0.0;
   out_3172612914634759799[32] = 0.0;
   out_3172612914634759799[33] = 0.0;
   out_3172612914634759799[34] = 0.0;
   out_3172612914634759799[35] = 0.0;
   out_3172612914634759799[36] = 0.0;
   out_3172612914634759799[37] = 0.0;
   out_3172612914634759799[38] = 0.0;
   out_3172612914634759799[39] = 0.0;
   out_3172612914634759799[40] = 1.0;
   out_3172612914634759799[41] = 0.0;
   out_3172612914634759799[42] = 0.0;
   out_3172612914634759799[43] = 0.0;
   out_3172612914634759799[44] = 0.0;
   out_3172612914634759799[45] = 0.0;
   out_3172612914634759799[46] = 0.0;
   out_3172612914634759799[47] = 0.0;
   out_3172612914634759799[48] = 0.0;
   out_3172612914634759799[49] = 0.0;
   out_3172612914634759799[50] = 1.0;
   out_3172612914634759799[51] = 0.0;
   out_3172612914634759799[52] = 0.0;
   out_3172612914634759799[53] = 0.0;
   out_3172612914634759799[54] = 0.0;
   out_3172612914634759799[55] = 0.0;
   out_3172612914634759799[56] = 0.0;
   out_3172612914634759799[57] = 0.0;
   out_3172612914634759799[58] = 0.0;
   out_3172612914634759799[59] = 0.0;
   out_3172612914634759799[60] = 1.0;
   out_3172612914634759799[61] = 0.0;
   out_3172612914634759799[62] = 0.0;
   out_3172612914634759799[63] = 0.0;
   out_3172612914634759799[64] = 0.0;
   out_3172612914634759799[65] = 0.0;
   out_3172612914634759799[66] = 0.0;
   out_3172612914634759799[67] = 0.0;
   out_3172612914634759799[68] = 0.0;
   out_3172612914634759799[69] = 0.0;
   out_3172612914634759799[70] = 1.0;
   out_3172612914634759799[71] = 0.0;
   out_3172612914634759799[72] = 0.0;
   out_3172612914634759799[73] = 0.0;
   out_3172612914634759799[74] = 0.0;
   out_3172612914634759799[75] = 0.0;
   out_3172612914634759799[76] = 0.0;
   out_3172612914634759799[77] = 0.0;
   out_3172612914634759799[78] = 0.0;
   out_3172612914634759799[79] = 0.0;
   out_3172612914634759799[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_7316960543418142517) {
   out_7316960543418142517[0] = state[0];
   out_7316960543418142517[1] = state[1];
   out_7316960543418142517[2] = state[2];
   out_7316960543418142517[3] = state[3];
   out_7316960543418142517[4] = state[4];
   out_7316960543418142517[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_7316960543418142517[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_7316960543418142517[7] = state[7];
   out_7316960543418142517[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1492910262171570578) {
   out_1492910262171570578[0] = 1;
   out_1492910262171570578[1] = 0;
   out_1492910262171570578[2] = 0;
   out_1492910262171570578[3] = 0;
   out_1492910262171570578[4] = 0;
   out_1492910262171570578[5] = 0;
   out_1492910262171570578[6] = 0;
   out_1492910262171570578[7] = 0;
   out_1492910262171570578[8] = 0;
   out_1492910262171570578[9] = 0;
   out_1492910262171570578[10] = 1;
   out_1492910262171570578[11] = 0;
   out_1492910262171570578[12] = 0;
   out_1492910262171570578[13] = 0;
   out_1492910262171570578[14] = 0;
   out_1492910262171570578[15] = 0;
   out_1492910262171570578[16] = 0;
   out_1492910262171570578[17] = 0;
   out_1492910262171570578[18] = 0;
   out_1492910262171570578[19] = 0;
   out_1492910262171570578[20] = 1;
   out_1492910262171570578[21] = 0;
   out_1492910262171570578[22] = 0;
   out_1492910262171570578[23] = 0;
   out_1492910262171570578[24] = 0;
   out_1492910262171570578[25] = 0;
   out_1492910262171570578[26] = 0;
   out_1492910262171570578[27] = 0;
   out_1492910262171570578[28] = 0;
   out_1492910262171570578[29] = 0;
   out_1492910262171570578[30] = 1;
   out_1492910262171570578[31] = 0;
   out_1492910262171570578[32] = 0;
   out_1492910262171570578[33] = 0;
   out_1492910262171570578[34] = 0;
   out_1492910262171570578[35] = 0;
   out_1492910262171570578[36] = 0;
   out_1492910262171570578[37] = 0;
   out_1492910262171570578[38] = 0;
   out_1492910262171570578[39] = 0;
   out_1492910262171570578[40] = 1;
   out_1492910262171570578[41] = 0;
   out_1492910262171570578[42] = 0;
   out_1492910262171570578[43] = 0;
   out_1492910262171570578[44] = 0;
   out_1492910262171570578[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1492910262171570578[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1492910262171570578[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1492910262171570578[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1492910262171570578[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1492910262171570578[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1492910262171570578[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1492910262171570578[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1492910262171570578[53] = -9.8100000000000005*dt;
   out_1492910262171570578[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1492910262171570578[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1492910262171570578[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1492910262171570578[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1492910262171570578[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1492910262171570578[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1492910262171570578[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1492910262171570578[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1492910262171570578[62] = 0;
   out_1492910262171570578[63] = 0;
   out_1492910262171570578[64] = 0;
   out_1492910262171570578[65] = 0;
   out_1492910262171570578[66] = 0;
   out_1492910262171570578[67] = 0;
   out_1492910262171570578[68] = 0;
   out_1492910262171570578[69] = 0;
   out_1492910262171570578[70] = 1;
   out_1492910262171570578[71] = 0;
   out_1492910262171570578[72] = 0;
   out_1492910262171570578[73] = 0;
   out_1492910262171570578[74] = 0;
   out_1492910262171570578[75] = 0;
   out_1492910262171570578[76] = 0;
   out_1492910262171570578[77] = 0;
   out_1492910262171570578[78] = 0;
   out_1492910262171570578[79] = 0;
   out_1492910262171570578[80] = 1;
}
void h_25(double *state, double *unused, double *out_595544251427276973) {
   out_595544251427276973[0] = state[6];
}
void H_25(double *state, double *unused, double *out_350435724010605349) {
   out_350435724010605349[0] = 0;
   out_350435724010605349[1] = 0;
   out_350435724010605349[2] = 0;
   out_350435724010605349[3] = 0;
   out_350435724010605349[4] = 0;
   out_350435724010605349[5] = 0;
   out_350435724010605349[6] = 1;
   out_350435724010605349[7] = 0;
   out_350435724010605349[8] = 0;
}
void h_24(double *state, double *unused, double *out_2954294579100300160) {
   out_2954294579100300160[0] = state[4];
   out_2954294579100300160[1] = state[5];
}
void H_24(double *state, double *unused, double *out_3207489874791717787) {
   out_3207489874791717787[0] = 0;
   out_3207489874791717787[1] = 0;
   out_3207489874791717787[2] = 0;
   out_3207489874791717787[3] = 0;
   out_3207489874791717787[4] = 1;
   out_3207489874791717787[5] = 0;
   out_3207489874791717787[6] = 0;
   out_3207489874791717787[7] = 0;
   out_3207489874791717787[8] = 0;
   out_3207489874791717787[9] = 0;
   out_3207489874791717787[10] = 0;
   out_3207489874791717787[11] = 0;
   out_3207489874791717787[12] = 0;
   out_3207489874791717787[13] = 0;
   out_3207489874791717787[14] = 1;
   out_3207489874791717787[15] = 0;
   out_3207489874791717787[16] = 0;
   out_3207489874791717787[17] = 0;
}
void h_30(double *state, double *unused, double *out_4457227727855778625) {
   out_4457227727855778625[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2167897234496643278) {
   out_2167897234496643278[0] = 0;
   out_2167897234496643278[1] = 0;
   out_2167897234496643278[2] = 0;
   out_2167897234496643278[3] = 0;
   out_2167897234496643278[4] = 1;
   out_2167897234496643278[5] = 0;
   out_2167897234496643278[6] = 0;
   out_2167897234496643278[7] = 0;
   out_2167897234496643278[8] = 0;
}
void h_26(double *state, double *unused, double *out_6778606859599551480) {
   out_6778606859599551480[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4091939042884661573) {
   out_4091939042884661573[0] = 0;
   out_4091939042884661573[1] = 0;
   out_4091939042884661573[2] = 0;
   out_4091939042884661573[3] = 0;
   out_4091939042884661573[4] = 0;
   out_4091939042884661573[5] = 0;
   out_4091939042884661573[6] = 0;
   out_4091939042884661573[7] = 1;
   out_4091939042884661573[8] = 0;
}
void h_27(double *state, double *unused, double *out_2871073069040329107) {
   out_2871073069040329107[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4391491305680586495) {
   out_4391491305680586495[0] = 0;
   out_4391491305680586495[1] = 0;
   out_4391491305680586495[2] = 0;
   out_4391491305680586495[3] = 1;
   out_4391491305680586495[4] = 0;
   out_4391491305680586495[5] = 0;
   out_4391491305680586495[6] = 0;
   out_4391491305680586495[7] = 0;
   out_4391491305680586495[8] = 0;
}
void h_29(double *state, double *unused, double *out_8987843078192927346) {
   out_8987843078192927346[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2678128578811035462) {
   out_2678128578811035462[0] = 0;
   out_2678128578811035462[1] = 1;
   out_2678128578811035462[2] = 0;
   out_2678128578811035462[3] = 0;
   out_2678128578811035462[4] = 0;
   out_2678128578811035462[5] = 0;
   out_2678128578811035462[6] = 0;
   out_2678128578811035462[7] = 0;
   out_2678128578811035462[8] = 0;
}
void h_28(double *state, double *unused, double *out_3384751652918718147) {
   out_3384751652918718147[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2404270438258495112) {
   out_2404270438258495112[0] = 1;
   out_2404270438258495112[1] = 0;
   out_2404270438258495112[2] = 0;
   out_2404270438258495112[3] = 0;
   out_2404270438258495112[4] = 0;
   out_2404270438258495112[5] = 0;
   out_2404270438258495112[6] = 0;
   out_2404270438258495112[7] = 0;
   out_2404270438258495112[8] = 0;
}
void h_31(double *state, double *unused, double *out_1973413530269387393) {
   out_1973413530269387393[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4718147145118013049) {
   out_4718147145118013049[0] = 0;
   out_4718147145118013049[1] = 0;
   out_4718147145118013049[2] = 0;
   out_4718147145118013049[3] = 0;
   out_4718147145118013049[4] = 0;
   out_4718147145118013049[5] = 0;
   out_4718147145118013049[6] = 0;
   out_4718147145118013049[7] = 0;
   out_4718147145118013049[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2503888728252844227) {
  err_fun(nom_x, delta_x, out_2503888728252844227);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3671647430606809601) {
  inv_err_fun(nom_x, true_x, out_3671647430606809601);
}
void car_H_mod_fun(double *state, double *out_3172612914634759799) {
  H_mod_fun(state, out_3172612914634759799);
}
void car_f_fun(double *state, double dt, double *out_7316960543418142517) {
  f_fun(state,  dt, out_7316960543418142517);
}
void car_F_fun(double *state, double dt, double *out_1492910262171570578) {
  F_fun(state,  dt, out_1492910262171570578);
}
void car_h_25(double *state, double *unused, double *out_595544251427276973) {
  h_25(state, unused, out_595544251427276973);
}
void car_H_25(double *state, double *unused, double *out_350435724010605349) {
  H_25(state, unused, out_350435724010605349);
}
void car_h_24(double *state, double *unused, double *out_2954294579100300160) {
  h_24(state, unused, out_2954294579100300160);
}
void car_H_24(double *state, double *unused, double *out_3207489874791717787) {
  H_24(state, unused, out_3207489874791717787);
}
void car_h_30(double *state, double *unused, double *out_4457227727855778625) {
  h_30(state, unused, out_4457227727855778625);
}
void car_H_30(double *state, double *unused, double *out_2167897234496643278) {
  H_30(state, unused, out_2167897234496643278);
}
void car_h_26(double *state, double *unused, double *out_6778606859599551480) {
  h_26(state, unused, out_6778606859599551480);
}
void car_H_26(double *state, double *unused, double *out_4091939042884661573) {
  H_26(state, unused, out_4091939042884661573);
}
void car_h_27(double *state, double *unused, double *out_2871073069040329107) {
  h_27(state, unused, out_2871073069040329107);
}
void car_H_27(double *state, double *unused, double *out_4391491305680586495) {
  H_27(state, unused, out_4391491305680586495);
}
void car_h_29(double *state, double *unused, double *out_8987843078192927346) {
  h_29(state, unused, out_8987843078192927346);
}
void car_H_29(double *state, double *unused, double *out_2678128578811035462) {
  H_29(state, unused, out_2678128578811035462);
}
void car_h_28(double *state, double *unused, double *out_3384751652918718147) {
  h_28(state, unused, out_3384751652918718147);
}
void car_H_28(double *state, double *unused, double *out_2404270438258495112) {
  H_28(state, unused, out_2404270438258495112);
}
void car_h_31(double *state, double *unused, double *out_1973413530269387393) {
  h_31(state, unused, out_1973413530269387393);
}
void car_H_31(double *state, double *unused, double *out_4718147145118013049) {
  H_31(state, unused, out_4718147145118013049);
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
