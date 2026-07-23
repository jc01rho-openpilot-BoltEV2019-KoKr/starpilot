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
void err_fun(double *nom_x, double *delta_x, double *out_2798728055434719104) {
   out_2798728055434719104[0] = delta_x[0] + nom_x[0];
   out_2798728055434719104[1] = delta_x[1] + nom_x[1];
   out_2798728055434719104[2] = delta_x[2] + nom_x[2];
   out_2798728055434719104[3] = delta_x[3] + nom_x[3];
   out_2798728055434719104[4] = delta_x[4] + nom_x[4];
   out_2798728055434719104[5] = delta_x[5] + nom_x[5];
   out_2798728055434719104[6] = delta_x[6] + nom_x[6];
   out_2798728055434719104[7] = delta_x[7] + nom_x[7];
   out_2798728055434719104[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5158994837086933641) {
   out_5158994837086933641[0] = -nom_x[0] + true_x[0];
   out_5158994837086933641[1] = -nom_x[1] + true_x[1];
   out_5158994837086933641[2] = -nom_x[2] + true_x[2];
   out_5158994837086933641[3] = -nom_x[3] + true_x[3];
   out_5158994837086933641[4] = -nom_x[4] + true_x[4];
   out_5158994837086933641[5] = -nom_x[5] + true_x[5];
   out_5158994837086933641[6] = -nom_x[6] + true_x[6];
   out_5158994837086933641[7] = -nom_x[7] + true_x[7];
   out_5158994837086933641[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8807292285450126459) {
   out_8807292285450126459[0] = 1.0;
   out_8807292285450126459[1] = 0.0;
   out_8807292285450126459[2] = 0.0;
   out_8807292285450126459[3] = 0.0;
   out_8807292285450126459[4] = 0.0;
   out_8807292285450126459[5] = 0.0;
   out_8807292285450126459[6] = 0.0;
   out_8807292285450126459[7] = 0.0;
   out_8807292285450126459[8] = 0.0;
   out_8807292285450126459[9] = 0.0;
   out_8807292285450126459[10] = 1.0;
   out_8807292285450126459[11] = 0.0;
   out_8807292285450126459[12] = 0.0;
   out_8807292285450126459[13] = 0.0;
   out_8807292285450126459[14] = 0.0;
   out_8807292285450126459[15] = 0.0;
   out_8807292285450126459[16] = 0.0;
   out_8807292285450126459[17] = 0.0;
   out_8807292285450126459[18] = 0.0;
   out_8807292285450126459[19] = 0.0;
   out_8807292285450126459[20] = 1.0;
   out_8807292285450126459[21] = 0.0;
   out_8807292285450126459[22] = 0.0;
   out_8807292285450126459[23] = 0.0;
   out_8807292285450126459[24] = 0.0;
   out_8807292285450126459[25] = 0.0;
   out_8807292285450126459[26] = 0.0;
   out_8807292285450126459[27] = 0.0;
   out_8807292285450126459[28] = 0.0;
   out_8807292285450126459[29] = 0.0;
   out_8807292285450126459[30] = 1.0;
   out_8807292285450126459[31] = 0.0;
   out_8807292285450126459[32] = 0.0;
   out_8807292285450126459[33] = 0.0;
   out_8807292285450126459[34] = 0.0;
   out_8807292285450126459[35] = 0.0;
   out_8807292285450126459[36] = 0.0;
   out_8807292285450126459[37] = 0.0;
   out_8807292285450126459[38] = 0.0;
   out_8807292285450126459[39] = 0.0;
   out_8807292285450126459[40] = 1.0;
   out_8807292285450126459[41] = 0.0;
   out_8807292285450126459[42] = 0.0;
   out_8807292285450126459[43] = 0.0;
   out_8807292285450126459[44] = 0.0;
   out_8807292285450126459[45] = 0.0;
   out_8807292285450126459[46] = 0.0;
   out_8807292285450126459[47] = 0.0;
   out_8807292285450126459[48] = 0.0;
   out_8807292285450126459[49] = 0.0;
   out_8807292285450126459[50] = 1.0;
   out_8807292285450126459[51] = 0.0;
   out_8807292285450126459[52] = 0.0;
   out_8807292285450126459[53] = 0.0;
   out_8807292285450126459[54] = 0.0;
   out_8807292285450126459[55] = 0.0;
   out_8807292285450126459[56] = 0.0;
   out_8807292285450126459[57] = 0.0;
   out_8807292285450126459[58] = 0.0;
   out_8807292285450126459[59] = 0.0;
   out_8807292285450126459[60] = 1.0;
   out_8807292285450126459[61] = 0.0;
   out_8807292285450126459[62] = 0.0;
   out_8807292285450126459[63] = 0.0;
   out_8807292285450126459[64] = 0.0;
   out_8807292285450126459[65] = 0.0;
   out_8807292285450126459[66] = 0.0;
   out_8807292285450126459[67] = 0.0;
   out_8807292285450126459[68] = 0.0;
   out_8807292285450126459[69] = 0.0;
   out_8807292285450126459[70] = 1.0;
   out_8807292285450126459[71] = 0.0;
   out_8807292285450126459[72] = 0.0;
   out_8807292285450126459[73] = 0.0;
   out_8807292285450126459[74] = 0.0;
   out_8807292285450126459[75] = 0.0;
   out_8807292285450126459[76] = 0.0;
   out_8807292285450126459[77] = 0.0;
   out_8807292285450126459[78] = 0.0;
   out_8807292285450126459[79] = 0.0;
   out_8807292285450126459[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_547624329025478730) {
   out_547624329025478730[0] = state[0];
   out_547624329025478730[1] = state[1];
   out_547624329025478730[2] = state[2];
   out_547624329025478730[3] = state[3];
   out_547624329025478730[4] = state[4];
   out_547624329025478730[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_547624329025478730[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_547624329025478730[7] = state[7];
   out_547624329025478730[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6298604141859123794) {
   out_6298604141859123794[0] = 1;
   out_6298604141859123794[1] = 0;
   out_6298604141859123794[2] = 0;
   out_6298604141859123794[3] = 0;
   out_6298604141859123794[4] = 0;
   out_6298604141859123794[5] = 0;
   out_6298604141859123794[6] = 0;
   out_6298604141859123794[7] = 0;
   out_6298604141859123794[8] = 0;
   out_6298604141859123794[9] = 0;
   out_6298604141859123794[10] = 1;
   out_6298604141859123794[11] = 0;
   out_6298604141859123794[12] = 0;
   out_6298604141859123794[13] = 0;
   out_6298604141859123794[14] = 0;
   out_6298604141859123794[15] = 0;
   out_6298604141859123794[16] = 0;
   out_6298604141859123794[17] = 0;
   out_6298604141859123794[18] = 0;
   out_6298604141859123794[19] = 0;
   out_6298604141859123794[20] = 1;
   out_6298604141859123794[21] = 0;
   out_6298604141859123794[22] = 0;
   out_6298604141859123794[23] = 0;
   out_6298604141859123794[24] = 0;
   out_6298604141859123794[25] = 0;
   out_6298604141859123794[26] = 0;
   out_6298604141859123794[27] = 0;
   out_6298604141859123794[28] = 0;
   out_6298604141859123794[29] = 0;
   out_6298604141859123794[30] = 1;
   out_6298604141859123794[31] = 0;
   out_6298604141859123794[32] = 0;
   out_6298604141859123794[33] = 0;
   out_6298604141859123794[34] = 0;
   out_6298604141859123794[35] = 0;
   out_6298604141859123794[36] = 0;
   out_6298604141859123794[37] = 0;
   out_6298604141859123794[38] = 0;
   out_6298604141859123794[39] = 0;
   out_6298604141859123794[40] = 1;
   out_6298604141859123794[41] = 0;
   out_6298604141859123794[42] = 0;
   out_6298604141859123794[43] = 0;
   out_6298604141859123794[44] = 0;
   out_6298604141859123794[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6298604141859123794[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6298604141859123794[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6298604141859123794[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6298604141859123794[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6298604141859123794[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6298604141859123794[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6298604141859123794[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6298604141859123794[53] = -9.8100000000000005*dt;
   out_6298604141859123794[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6298604141859123794[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6298604141859123794[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6298604141859123794[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6298604141859123794[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6298604141859123794[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6298604141859123794[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6298604141859123794[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6298604141859123794[62] = 0;
   out_6298604141859123794[63] = 0;
   out_6298604141859123794[64] = 0;
   out_6298604141859123794[65] = 0;
   out_6298604141859123794[66] = 0;
   out_6298604141859123794[67] = 0;
   out_6298604141859123794[68] = 0;
   out_6298604141859123794[69] = 0;
   out_6298604141859123794[70] = 1;
   out_6298604141859123794[71] = 0;
   out_6298604141859123794[72] = 0;
   out_6298604141859123794[73] = 0;
   out_6298604141859123794[74] = 0;
   out_6298604141859123794[75] = 0;
   out_6298604141859123794[76] = 0;
   out_6298604141859123794[77] = 0;
   out_6298604141859123794[78] = 0;
   out_6298604141859123794[79] = 0;
   out_6298604141859123794[80] = 1;
}
void h_25(double *state, double *unused, double *out_5598542368802412337) {
   out_5598542368802412337[0] = state[6];
}
void H_25(double *state, double *unused, double *out_446263562347187920) {
   out_446263562347187920[0] = 0;
   out_446263562347187920[1] = 0;
   out_446263562347187920[2] = 0;
   out_446263562347187920[3] = 0;
   out_446263562347187920[4] = 0;
   out_446263562347187920[5] = 0;
   out_446263562347187920[6] = 1;
   out_446263562347187920[7] = 0;
   out_446263562347187920[8] = 0;
}
void h_24(double *state, double *unused, double *out_281619709901739940) {
   out_281619709901739940[0] = state[4];
   out_281619709901739940[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4300245764619321114) {
   out_4300245764619321114[0] = 0;
   out_4300245764619321114[1] = 0;
   out_4300245764619321114[2] = 0;
   out_4300245764619321114[3] = 0;
   out_4300245764619321114[4] = 1;
   out_4300245764619321114[5] = 0;
   out_4300245764619321114[6] = 0;
   out_4300245764619321114[7] = 0;
   out_4300245764619321114[8] = 0;
   out_4300245764619321114[9] = 0;
   out_4300245764619321114[10] = 0;
   out_4300245764619321114[11] = 0;
   out_4300245764619321114[12] = 0;
   out_4300245764619321114[13] = 0;
   out_4300245764619321114[14] = 1;
   out_4300245764619321114[15] = 0;
   out_4300245764619321114[16] = 0;
   out_4300245764619321114[17] = 0;
}
void h_30(double *state, double *unused, double *out_6077366478556788343) {
   out_6077366478556788343[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7362953903838804675) {
   out_7362953903838804675[0] = 0;
   out_7362953903838804675[1] = 0;
   out_7362953903838804675[2] = 0;
   out_7362953903838804675[3] = 0;
   out_7362953903838804675[4] = 1;
   out_7362953903838804675[5] = 0;
   out_7362953903838804675[6] = 0;
   out_7362953903838804675[7] = 0;
   out_7362953903838804675[8] = 0;
}
void h_26(double *state, double *unused, double *out_714876495074943436) {
   out_714876495074943436[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3295239756526868304) {
   out_3295239756526868304[0] = 0;
   out_3295239756526868304[1] = 0;
   out_3295239756526868304[2] = 0;
   out_3295239756526868304[3] = 0;
   out_3295239756526868304[4] = 0;
   out_3295239756526868304[5] = 0;
   out_3295239756526868304[6] = 0;
   out_3295239756526868304[7] = 1;
   out_3295239756526868304[8] = 0;
}
void h_27(double *state, double *unused, double *out_3197767095463584803) {
   out_3197767095463584803[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5188190592038379764) {
   out_5188190592038379764[0] = 0;
   out_5188190592038379764[1] = 0;
   out_5188190592038379764[2] = 0;
   out_5188190592038379764[3] = 1;
   out_5188190592038379764[4] = 0;
   out_5188190592038379764[5] = 0;
   out_5188190592038379764[6] = 0;
   out_5188190592038379764[7] = 0;
   out_5188190592038379764[8] = 0;
}
void h_29(double *state, double *unused, double *out_9093529782405306684) {
   out_9093529782405306684[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7873185248153196859) {
   out_7873185248153196859[0] = 0;
   out_7873185248153196859[1] = 1;
   out_7873185248153196859[2] = 0;
   out_7873185248153196859[3] = 0;
   out_7873185248153196859[4] = 0;
   out_7873185248153196859[5] = 0;
   out_7873185248153196859[6] = 0;
   out_7873185248153196859[7] = 0;
   out_7873185248153196859[8] = 0;
}
void h_28(double *state, double *unused, double *out_8199440363124430448) {
   out_8199440363124430448[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2790786231083666285) {
   out_2790786231083666285[0] = 1;
   out_2790786231083666285[1] = 0;
   out_2790786231083666285[2] = 0;
   out_2790786231083666285[3] = 0;
   out_2790786231083666285[4] = 0;
   out_2790786231083666285[5] = 0;
   out_2790786231083666285[6] = 0;
   out_2790786231083666285[7] = 0;
   out_2790786231083666285[8] = 0;
}
void h_31(double *state, double *unused, double *out_5441355700451283192) {
   out_5441355700451283192[0] = state[8];
}
void H_31(double *state, double *unused, double *out_476909524224148348) {
   out_476909524224148348[0] = 0;
   out_476909524224148348[1] = 0;
   out_476909524224148348[2] = 0;
   out_476909524224148348[3] = 0;
   out_476909524224148348[4] = 0;
   out_476909524224148348[5] = 0;
   out_476909524224148348[6] = 0;
   out_476909524224148348[7] = 0;
   out_476909524224148348[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2798728055434719104) {
  err_fun(nom_x, delta_x, out_2798728055434719104);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5158994837086933641) {
  inv_err_fun(nom_x, true_x, out_5158994837086933641);
}
void car_H_mod_fun(double *state, double *out_8807292285450126459) {
  H_mod_fun(state, out_8807292285450126459);
}
void car_f_fun(double *state, double dt, double *out_547624329025478730) {
  f_fun(state,  dt, out_547624329025478730);
}
void car_F_fun(double *state, double dt, double *out_6298604141859123794) {
  F_fun(state,  dt, out_6298604141859123794);
}
void car_h_25(double *state, double *unused, double *out_5598542368802412337) {
  h_25(state, unused, out_5598542368802412337);
}
void car_H_25(double *state, double *unused, double *out_446263562347187920) {
  H_25(state, unused, out_446263562347187920);
}
void car_h_24(double *state, double *unused, double *out_281619709901739940) {
  h_24(state, unused, out_281619709901739940);
}
void car_H_24(double *state, double *unused, double *out_4300245764619321114) {
  H_24(state, unused, out_4300245764619321114);
}
void car_h_30(double *state, double *unused, double *out_6077366478556788343) {
  h_30(state, unused, out_6077366478556788343);
}
void car_H_30(double *state, double *unused, double *out_7362953903838804675) {
  H_30(state, unused, out_7362953903838804675);
}
void car_h_26(double *state, double *unused, double *out_714876495074943436) {
  h_26(state, unused, out_714876495074943436);
}
void car_H_26(double *state, double *unused, double *out_3295239756526868304) {
  H_26(state, unused, out_3295239756526868304);
}
void car_h_27(double *state, double *unused, double *out_3197767095463584803) {
  h_27(state, unused, out_3197767095463584803);
}
void car_H_27(double *state, double *unused, double *out_5188190592038379764) {
  H_27(state, unused, out_5188190592038379764);
}
void car_h_29(double *state, double *unused, double *out_9093529782405306684) {
  h_29(state, unused, out_9093529782405306684);
}
void car_H_29(double *state, double *unused, double *out_7873185248153196859) {
  H_29(state, unused, out_7873185248153196859);
}
void car_h_28(double *state, double *unused, double *out_8199440363124430448) {
  h_28(state, unused, out_8199440363124430448);
}
void car_H_28(double *state, double *unused, double *out_2790786231083666285) {
  H_28(state, unused, out_2790786231083666285);
}
void car_h_31(double *state, double *unused, double *out_5441355700451283192) {
  h_31(state, unused, out_5441355700451283192);
}
void car_H_31(double *state, double *unused, double *out_476909524224148348) {
  H_31(state, unused, out_476909524224148348);
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
