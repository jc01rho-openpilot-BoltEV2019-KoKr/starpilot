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
void err_fun(double *nom_x, double *delta_x, double *out_6549097700781342010) {
   out_6549097700781342010[0] = delta_x[0] + nom_x[0];
   out_6549097700781342010[1] = delta_x[1] + nom_x[1];
   out_6549097700781342010[2] = delta_x[2] + nom_x[2];
   out_6549097700781342010[3] = delta_x[3] + nom_x[3];
   out_6549097700781342010[4] = delta_x[4] + nom_x[4];
   out_6549097700781342010[5] = delta_x[5] + nom_x[5];
   out_6549097700781342010[6] = delta_x[6] + nom_x[6];
   out_6549097700781342010[7] = delta_x[7] + nom_x[7];
   out_6549097700781342010[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8354153438521949351) {
   out_8354153438521949351[0] = -nom_x[0] + true_x[0];
   out_8354153438521949351[1] = -nom_x[1] + true_x[1];
   out_8354153438521949351[2] = -nom_x[2] + true_x[2];
   out_8354153438521949351[3] = -nom_x[3] + true_x[3];
   out_8354153438521949351[4] = -nom_x[4] + true_x[4];
   out_8354153438521949351[5] = -nom_x[5] + true_x[5];
   out_8354153438521949351[6] = -nom_x[6] + true_x[6];
   out_8354153438521949351[7] = -nom_x[7] + true_x[7];
   out_8354153438521949351[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6316391371516646855) {
   out_6316391371516646855[0] = 1.0;
   out_6316391371516646855[1] = 0.0;
   out_6316391371516646855[2] = 0.0;
   out_6316391371516646855[3] = 0.0;
   out_6316391371516646855[4] = 0.0;
   out_6316391371516646855[5] = 0.0;
   out_6316391371516646855[6] = 0.0;
   out_6316391371516646855[7] = 0.0;
   out_6316391371516646855[8] = 0.0;
   out_6316391371516646855[9] = 0.0;
   out_6316391371516646855[10] = 1.0;
   out_6316391371516646855[11] = 0.0;
   out_6316391371516646855[12] = 0.0;
   out_6316391371516646855[13] = 0.0;
   out_6316391371516646855[14] = 0.0;
   out_6316391371516646855[15] = 0.0;
   out_6316391371516646855[16] = 0.0;
   out_6316391371516646855[17] = 0.0;
   out_6316391371516646855[18] = 0.0;
   out_6316391371516646855[19] = 0.0;
   out_6316391371516646855[20] = 1.0;
   out_6316391371516646855[21] = 0.0;
   out_6316391371516646855[22] = 0.0;
   out_6316391371516646855[23] = 0.0;
   out_6316391371516646855[24] = 0.0;
   out_6316391371516646855[25] = 0.0;
   out_6316391371516646855[26] = 0.0;
   out_6316391371516646855[27] = 0.0;
   out_6316391371516646855[28] = 0.0;
   out_6316391371516646855[29] = 0.0;
   out_6316391371516646855[30] = 1.0;
   out_6316391371516646855[31] = 0.0;
   out_6316391371516646855[32] = 0.0;
   out_6316391371516646855[33] = 0.0;
   out_6316391371516646855[34] = 0.0;
   out_6316391371516646855[35] = 0.0;
   out_6316391371516646855[36] = 0.0;
   out_6316391371516646855[37] = 0.0;
   out_6316391371516646855[38] = 0.0;
   out_6316391371516646855[39] = 0.0;
   out_6316391371516646855[40] = 1.0;
   out_6316391371516646855[41] = 0.0;
   out_6316391371516646855[42] = 0.0;
   out_6316391371516646855[43] = 0.0;
   out_6316391371516646855[44] = 0.0;
   out_6316391371516646855[45] = 0.0;
   out_6316391371516646855[46] = 0.0;
   out_6316391371516646855[47] = 0.0;
   out_6316391371516646855[48] = 0.0;
   out_6316391371516646855[49] = 0.0;
   out_6316391371516646855[50] = 1.0;
   out_6316391371516646855[51] = 0.0;
   out_6316391371516646855[52] = 0.0;
   out_6316391371516646855[53] = 0.0;
   out_6316391371516646855[54] = 0.0;
   out_6316391371516646855[55] = 0.0;
   out_6316391371516646855[56] = 0.0;
   out_6316391371516646855[57] = 0.0;
   out_6316391371516646855[58] = 0.0;
   out_6316391371516646855[59] = 0.0;
   out_6316391371516646855[60] = 1.0;
   out_6316391371516646855[61] = 0.0;
   out_6316391371516646855[62] = 0.0;
   out_6316391371516646855[63] = 0.0;
   out_6316391371516646855[64] = 0.0;
   out_6316391371516646855[65] = 0.0;
   out_6316391371516646855[66] = 0.0;
   out_6316391371516646855[67] = 0.0;
   out_6316391371516646855[68] = 0.0;
   out_6316391371516646855[69] = 0.0;
   out_6316391371516646855[70] = 1.0;
   out_6316391371516646855[71] = 0.0;
   out_6316391371516646855[72] = 0.0;
   out_6316391371516646855[73] = 0.0;
   out_6316391371516646855[74] = 0.0;
   out_6316391371516646855[75] = 0.0;
   out_6316391371516646855[76] = 0.0;
   out_6316391371516646855[77] = 0.0;
   out_6316391371516646855[78] = 0.0;
   out_6316391371516646855[79] = 0.0;
   out_6316391371516646855[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_683944865460236824) {
   out_683944865460236824[0] = state[0];
   out_683944865460236824[1] = state[1];
   out_683944865460236824[2] = state[2];
   out_683944865460236824[3] = state[3];
   out_683944865460236824[4] = state[4];
   out_683944865460236824[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_683944865460236824[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_683944865460236824[7] = state[7];
   out_683944865460236824[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6256536759651096133) {
   out_6256536759651096133[0] = 1;
   out_6256536759651096133[1] = 0;
   out_6256536759651096133[2] = 0;
   out_6256536759651096133[3] = 0;
   out_6256536759651096133[4] = 0;
   out_6256536759651096133[5] = 0;
   out_6256536759651096133[6] = 0;
   out_6256536759651096133[7] = 0;
   out_6256536759651096133[8] = 0;
   out_6256536759651096133[9] = 0;
   out_6256536759651096133[10] = 1;
   out_6256536759651096133[11] = 0;
   out_6256536759651096133[12] = 0;
   out_6256536759651096133[13] = 0;
   out_6256536759651096133[14] = 0;
   out_6256536759651096133[15] = 0;
   out_6256536759651096133[16] = 0;
   out_6256536759651096133[17] = 0;
   out_6256536759651096133[18] = 0;
   out_6256536759651096133[19] = 0;
   out_6256536759651096133[20] = 1;
   out_6256536759651096133[21] = 0;
   out_6256536759651096133[22] = 0;
   out_6256536759651096133[23] = 0;
   out_6256536759651096133[24] = 0;
   out_6256536759651096133[25] = 0;
   out_6256536759651096133[26] = 0;
   out_6256536759651096133[27] = 0;
   out_6256536759651096133[28] = 0;
   out_6256536759651096133[29] = 0;
   out_6256536759651096133[30] = 1;
   out_6256536759651096133[31] = 0;
   out_6256536759651096133[32] = 0;
   out_6256536759651096133[33] = 0;
   out_6256536759651096133[34] = 0;
   out_6256536759651096133[35] = 0;
   out_6256536759651096133[36] = 0;
   out_6256536759651096133[37] = 0;
   out_6256536759651096133[38] = 0;
   out_6256536759651096133[39] = 0;
   out_6256536759651096133[40] = 1;
   out_6256536759651096133[41] = 0;
   out_6256536759651096133[42] = 0;
   out_6256536759651096133[43] = 0;
   out_6256536759651096133[44] = 0;
   out_6256536759651096133[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6256536759651096133[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6256536759651096133[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6256536759651096133[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6256536759651096133[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6256536759651096133[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6256536759651096133[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6256536759651096133[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6256536759651096133[53] = -9.8100000000000005*dt;
   out_6256536759651096133[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6256536759651096133[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6256536759651096133[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6256536759651096133[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6256536759651096133[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6256536759651096133[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6256536759651096133[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6256536759651096133[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6256536759651096133[62] = 0;
   out_6256536759651096133[63] = 0;
   out_6256536759651096133[64] = 0;
   out_6256536759651096133[65] = 0;
   out_6256536759651096133[66] = 0;
   out_6256536759651096133[67] = 0;
   out_6256536759651096133[68] = 0;
   out_6256536759651096133[69] = 0;
   out_6256536759651096133[70] = 1;
   out_6256536759651096133[71] = 0;
   out_6256536759651096133[72] = 0;
   out_6256536759651096133[73] = 0;
   out_6256536759651096133[74] = 0;
   out_6256536759651096133[75] = 0;
   out_6256536759651096133[76] = 0;
   out_6256536759651096133[77] = 0;
   out_6256536759651096133[78] = 0;
   out_6256536759651096133[79] = 0;
   out_6256536759651096133[80] = 1;
}
void h_25(double *state, double *unused, double *out_630446739146494899) {
   out_630446739146494899[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2937164476280667524) {
   out_2937164476280667524[0] = 0;
   out_2937164476280667524[1] = 0;
   out_2937164476280667524[2] = 0;
   out_2937164476280667524[3] = 0;
   out_2937164476280667524[4] = 0;
   out_2937164476280667524[5] = 0;
   out_2937164476280667524[6] = 1;
   out_2937164476280667524[7] = 0;
   out_2937164476280667524[8] = 0;
}
void h_24(double *state, double *unused, double *out_766963748656106214) {
   out_766963748656106214[0] = state[4];
   out_766963748656106214[1] = state[5];
}
void H_24(double *state, double *unused, double *out_764514877275167958) {
   out_764514877275167958[0] = 0;
   out_764514877275167958[1] = 0;
   out_764514877275167958[2] = 0;
   out_764514877275167958[3] = 0;
   out_764514877275167958[4] = 1;
   out_764514877275167958[5] = 0;
   out_764514877275167958[6] = 0;
   out_764514877275167958[7] = 0;
   out_764514877275167958[8] = 0;
   out_764514877275167958[9] = 0;
   out_764514877275167958[10] = 0;
   out_764514877275167958[11] = 0;
   out_764514877275167958[12] = 0;
   out_764514877275167958[13] = 0;
   out_764514877275167958[14] = 1;
   out_764514877275167958[15] = 0;
   out_764514877275167958[16] = 0;
   out_764514877275167958[17] = 0;
}
void h_30(double *state, double *unused, double *out_2365946185687416261) {
   out_2365946185687416261[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8592889255937267337) {
   out_8592889255937267337[0] = 0;
   out_8592889255937267337[1] = 0;
   out_8592889255937267337[2] = 0;
   out_8592889255937267337[3] = 0;
   out_8592889255937267337[4] = 1;
   out_8592889255937267337[5] = 0;
   out_8592889255937267337[6] = 0;
   out_8592889255937267337[7] = 0;
   out_8592889255937267337[8] = 0;
}
void h_26(double *state, double *unused, double *out_4488774751058732255) {
   out_4488774751058732255[0] = state[7];
}
void H_26(double *state, double *unused, double *out_804338842593388700) {
   out_804338842593388700[0] = 0;
   out_804338842593388700[1] = 0;
   out_804338842593388700[2] = 0;
   out_804338842593388700[3] = 0;
   out_804338842593388700[4] = 0;
   out_804338842593388700[5] = 0;
   out_804338842593388700[6] = 0;
   out_804338842593388700[7] = 1;
   out_804338842593388700[8] = 0;
}
void h_27(double *state, double *unused, double *out_4371226528514350746) {
   out_4371226528514350746[0] = state[3];
}
void H_27(double *state, double *unused, double *out_7679091505971859368) {
   out_7679091505971859368[0] = 0;
   out_7679091505971859368[1] = 0;
   out_7679091505971859368[2] = 0;
   out_7679091505971859368[3] = 1;
   out_7679091505971859368[4] = 0;
   out_7679091505971859368[5] = 0;
   out_7679091505971859368[6] = 0;
   out_7679091505971859368[7] = 0;
   out_7679091505971859368[8] = 0;
}
void h_29(double *state, double *unused, double *out_8008676056768373096) {
   out_8008676056768373096[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5965728779102308335) {
   out_5965728779102308335[0] = 0;
   out_5965728779102308335[1] = 1;
   out_5965728779102308335[2] = 0;
   out_5965728779102308335[3] = 0;
   out_5965728779102308335[4] = 0;
   out_5965728779102308335[5] = 0;
   out_5965728779102308335[6] = 0;
   out_5965728779102308335[7] = 0;
   out_5965728779102308335[8] = 0;
}
void h_28(double *state, double *unused, double *out_5855520433291817842) {
   out_5855520433291817842[0] = state[0];
}
void H_28(double *state, double *unused, double *out_883329762032777761) {
   out_883329762032777761[0] = 1;
   out_883329762032777761[1] = 0;
   out_883329762032777761[2] = 0;
   out_883329762032777761[3] = 0;
   out_883329762032777761[4] = 0;
   out_883329762032777761[5] = 0;
   out_883329762032777761[6] = 0;
   out_883329762032777761[7] = 0;
   out_883329762032777761[8] = 0;
}
void h_31(double *state, double *unused, double *out_2247938791754039517) {
   out_2247938791754039517[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2967810438157627952) {
   out_2967810438157627952[0] = 0;
   out_2967810438157627952[1] = 0;
   out_2967810438157627952[2] = 0;
   out_2967810438157627952[3] = 0;
   out_2967810438157627952[4] = 0;
   out_2967810438157627952[5] = 0;
   out_2967810438157627952[6] = 0;
   out_2967810438157627952[7] = 0;
   out_2967810438157627952[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_6549097700781342010) {
  err_fun(nom_x, delta_x, out_6549097700781342010);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8354153438521949351) {
  inv_err_fun(nom_x, true_x, out_8354153438521949351);
}
void car_H_mod_fun(double *state, double *out_6316391371516646855) {
  H_mod_fun(state, out_6316391371516646855);
}
void car_f_fun(double *state, double dt, double *out_683944865460236824) {
  f_fun(state,  dt, out_683944865460236824);
}
void car_F_fun(double *state, double dt, double *out_6256536759651096133) {
  F_fun(state,  dt, out_6256536759651096133);
}
void car_h_25(double *state, double *unused, double *out_630446739146494899) {
  h_25(state, unused, out_630446739146494899);
}
void car_H_25(double *state, double *unused, double *out_2937164476280667524) {
  H_25(state, unused, out_2937164476280667524);
}
void car_h_24(double *state, double *unused, double *out_766963748656106214) {
  h_24(state, unused, out_766963748656106214);
}
void car_H_24(double *state, double *unused, double *out_764514877275167958) {
  H_24(state, unused, out_764514877275167958);
}
void car_h_30(double *state, double *unused, double *out_2365946185687416261) {
  h_30(state, unused, out_2365946185687416261);
}
void car_H_30(double *state, double *unused, double *out_8592889255937267337) {
  H_30(state, unused, out_8592889255937267337);
}
void car_h_26(double *state, double *unused, double *out_4488774751058732255) {
  h_26(state, unused, out_4488774751058732255);
}
void car_H_26(double *state, double *unused, double *out_804338842593388700) {
  H_26(state, unused, out_804338842593388700);
}
void car_h_27(double *state, double *unused, double *out_4371226528514350746) {
  h_27(state, unused, out_4371226528514350746);
}
void car_H_27(double *state, double *unused, double *out_7679091505971859368) {
  H_27(state, unused, out_7679091505971859368);
}
void car_h_29(double *state, double *unused, double *out_8008676056768373096) {
  h_29(state, unused, out_8008676056768373096);
}
void car_H_29(double *state, double *unused, double *out_5965728779102308335) {
  H_29(state, unused, out_5965728779102308335);
}
void car_h_28(double *state, double *unused, double *out_5855520433291817842) {
  h_28(state, unused, out_5855520433291817842);
}
void car_H_28(double *state, double *unused, double *out_883329762032777761) {
  H_28(state, unused, out_883329762032777761);
}
void car_h_31(double *state, double *unused, double *out_2247938791754039517) {
  h_31(state, unused, out_2247938791754039517);
}
void car_H_31(double *state, double *unused, double *out_2967810438157627952) {
  H_31(state, unused, out_2967810438157627952);
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
