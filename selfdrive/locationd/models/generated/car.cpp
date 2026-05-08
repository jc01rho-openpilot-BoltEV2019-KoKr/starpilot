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
void err_fun(double *nom_x, double *delta_x, double *out_2567017903067559466) {
   out_2567017903067559466[0] = delta_x[0] + nom_x[0];
   out_2567017903067559466[1] = delta_x[1] + nom_x[1];
   out_2567017903067559466[2] = delta_x[2] + nom_x[2];
   out_2567017903067559466[3] = delta_x[3] + nom_x[3];
   out_2567017903067559466[4] = delta_x[4] + nom_x[4];
   out_2567017903067559466[5] = delta_x[5] + nom_x[5];
   out_2567017903067559466[6] = delta_x[6] + nom_x[6];
   out_2567017903067559466[7] = delta_x[7] + nom_x[7];
   out_2567017903067559466[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1749285410370024184) {
   out_1749285410370024184[0] = -nom_x[0] + true_x[0];
   out_1749285410370024184[1] = -nom_x[1] + true_x[1];
   out_1749285410370024184[2] = -nom_x[2] + true_x[2];
   out_1749285410370024184[3] = -nom_x[3] + true_x[3];
   out_1749285410370024184[4] = -nom_x[4] + true_x[4];
   out_1749285410370024184[5] = -nom_x[5] + true_x[5];
   out_1749285410370024184[6] = -nom_x[6] + true_x[6];
   out_1749285410370024184[7] = -nom_x[7] + true_x[7];
   out_1749285410370024184[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8979551951706364182) {
   out_8979551951706364182[0] = 1.0;
   out_8979551951706364182[1] = 0.0;
   out_8979551951706364182[2] = 0.0;
   out_8979551951706364182[3] = 0.0;
   out_8979551951706364182[4] = 0.0;
   out_8979551951706364182[5] = 0.0;
   out_8979551951706364182[6] = 0.0;
   out_8979551951706364182[7] = 0.0;
   out_8979551951706364182[8] = 0.0;
   out_8979551951706364182[9] = 0.0;
   out_8979551951706364182[10] = 1.0;
   out_8979551951706364182[11] = 0.0;
   out_8979551951706364182[12] = 0.0;
   out_8979551951706364182[13] = 0.0;
   out_8979551951706364182[14] = 0.0;
   out_8979551951706364182[15] = 0.0;
   out_8979551951706364182[16] = 0.0;
   out_8979551951706364182[17] = 0.0;
   out_8979551951706364182[18] = 0.0;
   out_8979551951706364182[19] = 0.0;
   out_8979551951706364182[20] = 1.0;
   out_8979551951706364182[21] = 0.0;
   out_8979551951706364182[22] = 0.0;
   out_8979551951706364182[23] = 0.0;
   out_8979551951706364182[24] = 0.0;
   out_8979551951706364182[25] = 0.0;
   out_8979551951706364182[26] = 0.0;
   out_8979551951706364182[27] = 0.0;
   out_8979551951706364182[28] = 0.0;
   out_8979551951706364182[29] = 0.0;
   out_8979551951706364182[30] = 1.0;
   out_8979551951706364182[31] = 0.0;
   out_8979551951706364182[32] = 0.0;
   out_8979551951706364182[33] = 0.0;
   out_8979551951706364182[34] = 0.0;
   out_8979551951706364182[35] = 0.0;
   out_8979551951706364182[36] = 0.0;
   out_8979551951706364182[37] = 0.0;
   out_8979551951706364182[38] = 0.0;
   out_8979551951706364182[39] = 0.0;
   out_8979551951706364182[40] = 1.0;
   out_8979551951706364182[41] = 0.0;
   out_8979551951706364182[42] = 0.0;
   out_8979551951706364182[43] = 0.0;
   out_8979551951706364182[44] = 0.0;
   out_8979551951706364182[45] = 0.0;
   out_8979551951706364182[46] = 0.0;
   out_8979551951706364182[47] = 0.0;
   out_8979551951706364182[48] = 0.0;
   out_8979551951706364182[49] = 0.0;
   out_8979551951706364182[50] = 1.0;
   out_8979551951706364182[51] = 0.0;
   out_8979551951706364182[52] = 0.0;
   out_8979551951706364182[53] = 0.0;
   out_8979551951706364182[54] = 0.0;
   out_8979551951706364182[55] = 0.0;
   out_8979551951706364182[56] = 0.0;
   out_8979551951706364182[57] = 0.0;
   out_8979551951706364182[58] = 0.0;
   out_8979551951706364182[59] = 0.0;
   out_8979551951706364182[60] = 1.0;
   out_8979551951706364182[61] = 0.0;
   out_8979551951706364182[62] = 0.0;
   out_8979551951706364182[63] = 0.0;
   out_8979551951706364182[64] = 0.0;
   out_8979551951706364182[65] = 0.0;
   out_8979551951706364182[66] = 0.0;
   out_8979551951706364182[67] = 0.0;
   out_8979551951706364182[68] = 0.0;
   out_8979551951706364182[69] = 0.0;
   out_8979551951706364182[70] = 1.0;
   out_8979551951706364182[71] = 0.0;
   out_8979551951706364182[72] = 0.0;
   out_8979551951706364182[73] = 0.0;
   out_8979551951706364182[74] = 0.0;
   out_8979551951706364182[75] = 0.0;
   out_8979551951706364182[76] = 0.0;
   out_8979551951706364182[77] = 0.0;
   out_8979551951706364182[78] = 0.0;
   out_8979551951706364182[79] = 0.0;
   out_8979551951706364182[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3674179640817441392) {
   out_3674179640817441392[0] = state[0];
   out_3674179640817441392[1] = state[1];
   out_3674179640817441392[2] = state[2];
   out_3674179640817441392[3] = state[3];
   out_3674179640817441392[4] = state[4];
   out_3674179640817441392[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3674179640817441392[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3674179640817441392[7] = state[7];
   out_3674179640817441392[8] = state[8];
}
void F_fun(double *state, double dt, double *out_258925546890284745) {
   out_258925546890284745[0] = 1;
   out_258925546890284745[1] = 0;
   out_258925546890284745[2] = 0;
   out_258925546890284745[3] = 0;
   out_258925546890284745[4] = 0;
   out_258925546890284745[5] = 0;
   out_258925546890284745[6] = 0;
   out_258925546890284745[7] = 0;
   out_258925546890284745[8] = 0;
   out_258925546890284745[9] = 0;
   out_258925546890284745[10] = 1;
   out_258925546890284745[11] = 0;
   out_258925546890284745[12] = 0;
   out_258925546890284745[13] = 0;
   out_258925546890284745[14] = 0;
   out_258925546890284745[15] = 0;
   out_258925546890284745[16] = 0;
   out_258925546890284745[17] = 0;
   out_258925546890284745[18] = 0;
   out_258925546890284745[19] = 0;
   out_258925546890284745[20] = 1;
   out_258925546890284745[21] = 0;
   out_258925546890284745[22] = 0;
   out_258925546890284745[23] = 0;
   out_258925546890284745[24] = 0;
   out_258925546890284745[25] = 0;
   out_258925546890284745[26] = 0;
   out_258925546890284745[27] = 0;
   out_258925546890284745[28] = 0;
   out_258925546890284745[29] = 0;
   out_258925546890284745[30] = 1;
   out_258925546890284745[31] = 0;
   out_258925546890284745[32] = 0;
   out_258925546890284745[33] = 0;
   out_258925546890284745[34] = 0;
   out_258925546890284745[35] = 0;
   out_258925546890284745[36] = 0;
   out_258925546890284745[37] = 0;
   out_258925546890284745[38] = 0;
   out_258925546890284745[39] = 0;
   out_258925546890284745[40] = 1;
   out_258925546890284745[41] = 0;
   out_258925546890284745[42] = 0;
   out_258925546890284745[43] = 0;
   out_258925546890284745[44] = 0;
   out_258925546890284745[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_258925546890284745[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_258925546890284745[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_258925546890284745[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_258925546890284745[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_258925546890284745[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_258925546890284745[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_258925546890284745[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_258925546890284745[53] = -9.8100000000000005*dt;
   out_258925546890284745[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_258925546890284745[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_258925546890284745[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_258925546890284745[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_258925546890284745[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_258925546890284745[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_258925546890284745[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_258925546890284745[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_258925546890284745[62] = 0;
   out_258925546890284745[63] = 0;
   out_258925546890284745[64] = 0;
   out_258925546890284745[65] = 0;
   out_258925546890284745[66] = 0;
   out_258925546890284745[67] = 0;
   out_258925546890284745[68] = 0;
   out_258925546890284745[69] = 0;
   out_258925546890284745[70] = 1;
   out_258925546890284745[71] = 0;
   out_258925546890284745[72] = 0;
   out_258925546890284745[73] = 0;
   out_258925546890284745[74] = 0;
   out_258925546890284745[75] = 0;
   out_258925546890284745[76] = 0;
   out_258925546890284745[77] = 0;
   out_258925546890284745[78] = 0;
   out_258925546890284745[79] = 0;
   out_258925546890284745[80] = 1;
}
void h_25(double *state, double *unused, double *out_5262304077966076166) {
   out_5262304077966076166[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4563500296818522594) {
   out_4563500296818522594[0] = 0;
   out_4563500296818522594[1] = 0;
   out_4563500296818522594[2] = 0;
   out_4563500296818522594[3] = 0;
   out_4563500296818522594[4] = 0;
   out_4563500296818522594[5] = 0;
   out_4563500296818522594[6] = 1;
   out_4563500296818522594[7] = 0;
   out_4563500296818522594[8] = 0;
}
void h_24(double *state, double *unused, double *out_2894074188837958464) {
   out_2894074188837958464[0] = state[4];
   out_2894074188837958464[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2012071509772995507) {
   out_2012071509772995507[0] = 0;
   out_2012071509772995507[1] = 0;
   out_2012071509772995507[2] = 0;
   out_2012071509772995507[3] = 0;
   out_2012071509772995507[4] = 1;
   out_2012071509772995507[5] = 0;
   out_2012071509772995507[6] = 0;
   out_2012071509772995507[7] = 0;
   out_2012071509772995507[8] = 0;
   out_2012071509772995507[9] = 0;
   out_2012071509772995507[10] = 0;
   out_2012071509772995507[11] = 0;
   out_2012071509772995507[12] = 0;
   out_2012071509772995507[13] = 0;
   out_2012071509772995507[14] = 1;
   out_2012071509772995507[15] = 0;
   out_2012071509772995507[16] = 0;
   out_2012071509772995507[17] = 0;
}
void h_30(double *state, double *unused, double *out_9005980160461201074) {
   out_9005980160461201074[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2045167338311273967) {
   out_2045167338311273967[0] = 0;
   out_2045167338311273967[1] = 0;
   out_2045167338311273967[2] = 0;
   out_2045167338311273967[3] = 0;
   out_2045167338311273967[4] = 1;
   out_2045167338311273967[5] = 0;
   out_2045167338311273967[6] = 0;
   out_2045167338311273967[7] = 0;
   out_2045167338311273967[8] = 0;
}
void h_26(double *state, double *unused, double *out_8837448028571873025) {
   out_8837448028571873025[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1258974327057721993) {
   out_1258974327057721993[0] = 0;
   out_1258974327057721993[1] = 0;
   out_1258974327057721993[2] = 0;
   out_1258974327057721993[3] = 0;
   out_1258974327057721993[4] = 0;
   out_1258974327057721993[5] = 0;
   out_1258974327057721993[6] = 0;
   out_1258974327057721993[7] = 1;
   out_1258974327057721993[8] = 0;
}
void h_27(double *state, double *unused, double *out_6785398478329626304) {
   out_6785398478329626304[0] = state[3];
}
void H_27(double *state, double *unused, double *out_178426732872669250) {
   out_178426732872669250[0] = 0;
   out_178426732872669250[1] = 0;
   out_178426732872669250[2] = 0;
   out_178426732872669250[3] = 1;
   out_178426732872669250[4] = 0;
   out_178426732872669250[5] = 0;
   out_178426732872669250[6] = 0;
   out_178426732872669250[7] = 0;
   out_178426732872669250[8] = 0;
}
void h_29(double *state, double *unused, double *out_8023896067125902962) {
   out_8023896067125902962[0] = state[1];
}
void H_29(double *state, double *unused, double *out_1534935993996881783) {
   out_1534935993996881783[0] = 0;
   out_1534935993996881783[1] = 1;
   out_1534935993996881783[2] = 0;
   out_1534935993996881783[3] = 0;
   out_1534935993996881783[4] = 0;
   out_1534935993996881783[5] = 0;
   out_1534935993996881783[6] = 0;
   out_1534935993996881783[7] = 0;
   out_1534935993996881783[8] = 0;
}
void h_28(double *state, double *unused, double *out_5617654677253484567) {
   out_5617654677253484567[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6617335011066412357) {
   out_6617335011066412357[0] = 1;
   out_6617335011066412357[1] = 0;
   out_6617335011066412357[2] = 0;
   out_6617335011066412357[3] = 0;
   out_6617335011066412357[4] = 0;
   out_6617335011066412357[5] = 0;
   out_6617335011066412357[6] = 0;
   out_6617335011066412357[7] = 0;
   out_6617335011066412357[8] = 0;
}
void h_31(double *state, double *unused, double *out_9123987554394577818) {
   out_9123987554394577818[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4532854334941562166) {
   out_4532854334941562166[0] = 0;
   out_4532854334941562166[1] = 0;
   out_4532854334941562166[2] = 0;
   out_4532854334941562166[3] = 0;
   out_4532854334941562166[4] = 0;
   out_4532854334941562166[5] = 0;
   out_4532854334941562166[6] = 0;
   out_4532854334941562166[7] = 0;
   out_4532854334941562166[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2567017903067559466) {
  err_fun(nom_x, delta_x, out_2567017903067559466);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1749285410370024184) {
  inv_err_fun(nom_x, true_x, out_1749285410370024184);
}
void car_H_mod_fun(double *state, double *out_8979551951706364182) {
  H_mod_fun(state, out_8979551951706364182);
}
void car_f_fun(double *state, double dt, double *out_3674179640817441392) {
  f_fun(state,  dt, out_3674179640817441392);
}
void car_F_fun(double *state, double dt, double *out_258925546890284745) {
  F_fun(state,  dt, out_258925546890284745);
}
void car_h_25(double *state, double *unused, double *out_5262304077966076166) {
  h_25(state, unused, out_5262304077966076166);
}
void car_H_25(double *state, double *unused, double *out_4563500296818522594) {
  H_25(state, unused, out_4563500296818522594);
}
void car_h_24(double *state, double *unused, double *out_2894074188837958464) {
  h_24(state, unused, out_2894074188837958464);
}
void car_H_24(double *state, double *unused, double *out_2012071509772995507) {
  H_24(state, unused, out_2012071509772995507);
}
void car_h_30(double *state, double *unused, double *out_9005980160461201074) {
  h_30(state, unused, out_9005980160461201074);
}
void car_H_30(double *state, double *unused, double *out_2045167338311273967) {
  H_30(state, unused, out_2045167338311273967);
}
void car_h_26(double *state, double *unused, double *out_8837448028571873025) {
  h_26(state, unused, out_8837448028571873025);
}
void car_H_26(double *state, double *unused, double *out_1258974327057721993) {
  H_26(state, unused, out_1258974327057721993);
}
void car_h_27(double *state, double *unused, double *out_6785398478329626304) {
  h_27(state, unused, out_6785398478329626304);
}
void car_H_27(double *state, double *unused, double *out_178426732872669250) {
  H_27(state, unused, out_178426732872669250);
}
void car_h_29(double *state, double *unused, double *out_8023896067125902962) {
  h_29(state, unused, out_8023896067125902962);
}
void car_H_29(double *state, double *unused, double *out_1534935993996881783) {
  H_29(state, unused, out_1534935993996881783);
}
void car_h_28(double *state, double *unused, double *out_5617654677253484567) {
  h_28(state, unused, out_5617654677253484567);
}
void car_H_28(double *state, double *unused, double *out_6617335011066412357) {
  H_28(state, unused, out_6617335011066412357);
}
void car_h_31(double *state, double *unused, double *out_9123987554394577818) {
  h_31(state, unused, out_9123987554394577818);
}
void car_H_31(double *state, double *unused, double *out_4532854334941562166) {
  H_31(state, unused, out_4532854334941562166);
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
