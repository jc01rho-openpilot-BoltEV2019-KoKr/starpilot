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
void err_fun(double *nom_x, double *delta_x, double *out_648770422652277661) {
   out_648770422652277661[0] = delta_x[0] + nom_x[0];
   out_648770422652277661[1] = delta_x[1] + nom_x[1];
   out_648770422652277661[2] = delta_x[2] + nom_x[2];
   out_648770422652277661[3] = delta_x[3] + nom_x[3];
   out_648770422652277661[4] = delta_x[4] + nom_x[4];
   out_648770422652277661[5] = delta_x[5] + nom_x[5];
   out_648770422652277661[6] = delta_x[6] + nom_x[6];
   out_648770422652277661[7] = delta_x[7] + nom_x[7];
   out_648770422652277661[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8433637752559620590) {
   out_8433637752559620590[0] = -nom_x[0] + true_x[0];
   out_8433637752559620590[1] = -nom_x[1] + true_x[1];
   out_8433637752559620590[2] = -nom_x[2] + true_x[2];
   out_8433637752559620590[3] = -nom_x[3] + true_x[3];
   out_8433637752559620590[4] = -nom_x[4] + true_x[4];
   out_8433637752559620590[5] = -nom_x[5] + true_x[5];
   out_8433637752559620590[6] = -nom_x[6] + true_x[6];
   out_8433637752559620590[7] = -nom_x[7] + true_x[7];
   out_8433637752559620590[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8422599956511423720) {
   out_8422599956511423720[0] = 1.0;
   out_8422599956511423720[1] = 0.0;
   out_8422599956511423720[2] = 0.0;
   out_8422599956511423720[3] = 0.0;
   out_8422599956511423720[4] = 0.0;
   out_8422599956511423720[5] = 0.0;
   out_8422599956511423720[6] = 0.0;
   out_8422599956511423720[7] = 0.0;
   out_8422599956511423720[8] = 0.0;
   out_8422599956511423720[9] = 0.0;
   out_8422599956511423720[10] = 1.0;
   out_8422599956511423720[11] = 0.0;
   out_8422599956511423720[12] = 0.0;
   out_8422599956511423720[13] = 0.0;
   out_8422599956511423720[14] = 0.0;
   out_8422599956511423720[15] = 0.0;
   out_8422599956511423720[16] = 0.0;
   out_8422599956511423720[17] = 0.0;
   out_8422599956511423720[18] = 0.0;
   out_8422599956511423720[19] = 0.0;
   out_8422599956511423720[20] = 1.0;
   out_8422599956511423720[21] = 0.0;
   out_8422599956511423720[22] = 0.0;
   out_8422599956511423720[23] = 0.0;
   out_8422599956511423720[24] = 0.0;
   out_8422599956511423720[25] = 0.0;
   out_8422599956511423720[26] = 0.0;
   out_8422599956511423720[27] = 0.0;
   out_8422599956511423720[28] = 0.0;
   out_8422599956511423720[29] = 0.0;
   out_8422599956511423720[30] = 1.0;
   out_8422599956511423720[31] = 0.0;
   out_8422599956511423720[32] = 0.0;
   out_8422599956511423720[33] = 0.0;
   out_8422599956511423720[34] = 0.0;
   out_8422599956511423720[35] = 0.0;
   out_8422599956511423720[36] = 0.0;
   out_8422599956511423720[37] = 0.0;
   out_8422599956511423720[38] = 0.0;
   out_8422599956511423720[39] = 0.0;
   out_8422599956511423720[40] = 1.0;
   out_8422599956511423720[41] = 0.0;
   out_8422599956511423720[42] = 0.0;
   out_8422599956511423720[43] = 0.0;
   out_8422599956511423720[44] = 0.0;
   out_8422599956511423720[45] = 0.0;
   out_8422599956511423720[46] = 0.0;
   out_8422599956511423720[47] = 0.0;
   out_8422599956511423720[48] = 0.0;
   out_8422599956511423720[49] = 0.0;
   out_8422599956511423720[50] = 1.0;
   out_8422599956511423720[51] = 0.0;
   out_8422599956511423720[52] = 0.0;
   out_8422599956511423720[53] = 0.0;
   out_8422599956511423720[54] = 0.0;
   out_8422599956511423720[55] = 0.0;
   out_8422599956511423720[56] = 0.0;
   out_8422599956511423720[57] = 0.0;
   out_8422599956511423720[58] = 0.0;
   out_8422599956511423720[59] = 0.0;
   out_8422599956511423720[60] = 1.0;
   out_8422599956511423720[61] = 0.0;
   out_8422599956511423720[62] = 0.0;
   out_8422599956511423720[63] = 0.0;
   out_8422599956511423720[64] = 0.0;
   out_8422599956511423720[65] = 0.0;
   out_8422599956511423720[66] = 0.0;
   out_8422599956511423720[67] = 0.0;
   out_8422599956511423720[68] = 0.0;
   out_8422599956511423720[69] = 0.0;
   out_8422599956511423720[70] = 1.0;
   out_8422599956511423720[71] = 0.0;
   out_8422599956511423720[72] = 0.0;
   out_8422599956511423720[73] = 0.0;
   out_8422599956511423720[74] = 0.0;
   out_8422599956511423720[75] = 0.0;
   out_8422599956511423720[76] = 0.0;
   out_8422599956511423720[77] = 0.0;
   out_8422599956511423720[78] = 0.0;
   out_8422599956511423720[79] = 0.0;
   out_8422599956511423720[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_9124674145630526498) {
   out_9124674145630526498[0] = state[0];
   out_9124674145630526498[1] = state[1];
   out_9124674145630526498[2] = state[2];
   out_9124674145630526498[3] = state[3];
   out_9124674145630526498[4] = state[4];
   out_9124674145630526498[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_9124674145630526498[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_9124674145630526498[7] = state[7];
   out_9124674145630526498[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7980063177758984153) {
   out_7980063177758984153[0] = 1;
   out_7980063177758984153[1] = 0;
   out_7980063177758984153[2] = 0;
   out_7980063177758984153[3] = 0;
   out_7980063177758984153[4] = 0;
   out_7980063177758984153[5] = 0;
   out_7980063177758984153[6] = 0;
   out_7980063177758984153[7] = 0;
   out_7980063177758984153[8] = 0;
   out_7980063177758984153[9] = 0;
   out_7980063177758984153[10] = 1;
   out_7980063177758984153[11] = 0;
   out_7980063177758984153[12] = 0;
   out_7980063177758984153[13] = 0;
   out_7980063177758984153[14] = 0;
   out_7980063177758984153[15] = 0;
   out_7980063177758984153[16] = 0;
   out_7980063177758984153[17] = 0;
   out_7980063177758984153[18] = 0;
   out_7980063177758984153[19] = 0;
   out_7980063177758984153[20] = 1;
   out_7980063177758984153[21] = 0;
   out_7980063177758984153[22] = 0;
   out_7980063177758984153[23] = 0;
   out_7980063177758984153[24] = 0;
   out_7980063177758984153[25] = 0;
   out_7980063177758984153[26] = 0;
   out_7980063177758984153[27] = 0;
   out_7980063177758984153[28] = 0;
   out_7980063177758984153[29] = 0;
   out_7980063177758984153[30] = 1;
   out_7980063177758984153[31] = 0;
   out_7980063177758984153[32] = 0;
   out_7980063177758984153[33] = 0;
   out_7980063177758984153[34] = 0;
   out_7980063177758984153[35] = 0;
   out_7980063177758984153[36] = 0;
   out_7980063177758984153[37] = 0;
   out_7980063177758984153[38] = 0;
   out_7980063177758984153[39] = 0;
   out_7980063177758984153[40] = 1;
   out_7980063177758984153[41] = 0;
   out_7980063177758984153[42] = 0;
   out_7980063177758984153[43] = 0;
   out_7980063177758984153[44] = 0;
   out_7980063177758984153[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7980063177758984153[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7980063177758984153[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7980063177758984153[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7980063177758984153[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7980063177758984153[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7980063177758984153[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7980063177758984153[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7980063177758984153[53] = -9.8100000000000005*dt;
   out_7980063177758984153[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7980063177758984153[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7980063177758984153[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7980063177758984153[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7980063177758984153[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7980063177758984153[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7980063177758984153[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7980063177758984153[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7980063177758984153[62] = 0;
   out_7980063177758984153[63] = 0;
   out_7980063177758984153[64] = 0;
   out_7980063177758984153[65] = 0;
   out_7980063177758984153[66] = 0;
   out_7980063177758984153[67] = 0;
   out_7980063177758984153[68] = 0;
   out_7980063177758984153[69] = 0;
   out_7980063177758984153[70] = 1;
   out_7980063177758984153[71] = 0;
   out_7980063177758984153[72] = 0;
   out_7980063177758984153[73] = 0;
   out_7980063177758984153[74] = 0;
   out_7980063177758984153[75] = 0;
   out_7980063177758984153[76] = 0;
   out_7980063177758984153[77] = 0;
   out_7980063177758984153[78] = 0;
   out_7980063177758984153[79] = 0;
   out_7980063177758984153[80] = 1;
}
void h_25(double *state, double *unused, double *out_7427457988301314284) {
   out_7427457988301314284[0] = state[6];
}
void H_25(double *state, double *unused, double *out_770588269400813517) {
   out_770588269400813517[0] = 0;
   out_770588269400813517[1] = 0;
   out_770588269400813517[2] = 0;
   out_770588269400813517[3] = 0;
   out_770588269400813517[4] = 0;
   out_770588269400813517[5] = 0;
   out_770588269400813517[6] = 1;
   out_770588269400813517[7] = 0;
   out_770588269400813517[8] = 0;
}
void h_24(double *state, double *unused, double *out_3062542313716558558) {
   out_3062542313716558558[0] = state[4];
   out_3062542313716558558[1] = state[5];
}
void H_24(double *state, double *unused, double *out_5590909774056801780) {
   out_5590909774056801780[0] = 0;
   out_5590909774056801780[1] = 0;
   out_5590909774056801780[2] = 0;
   out_5590909774056801780[3] = 0;
   out_5590909774056801780[4] = 1;
   out_5590909774056801780[5] = 0;
   out_5590909774056801780[6] = 0;
   out_5590909774056801780[7] = 0;
   out_5590909774056801780[8] = 0;
   out_5590909774056801780[9] = 0;
   out_5590909774056801780[10] = 0;
   out_5590909774056801780[11] = 0;
   out_5590909774056801780[12] = 0;
   out_5590909774056801780[13] = 0;
   out_5590909774056801780[14] = 1;
   out_5590909774056801780[15] = 0;
   out_5590909774056801780[16] = 0;
   out_5590909774056801780[17] = 0;
}
void h_30(double *state, double *unused, double *out_1260343948330179981) {
   out_1260343948330179981[0] = state[4];
}
void H_30(double *state, double *unused, double *out_899927216544053587) {
   out_899927216544053587[0] = 0;
   out_899927216544053587[1] = 0;
   out_899927216544053587[2] = 0;
   out_899927216544053587[3] = 0;
   out_899927216544053587[4] = 1;
   out_899927216544053587[5] = 0;
   out_899927216544053587[6] = 0;
   out_899927216544053587[7] = 0;
   out_899927216544053587[8] = 0;
}
void h_26(double *state, double *unused, double *out_4488267301164684189) {
   out_4488267301164684189[0] = state[7];
}
void H_26(double *state, double *unused, double *out_4512091588274869741) {
   out_4512091588274869741[0] = 0;
   out_4512091588274869741[1] = 0;
   out_4512091588274869741[2] = 0;
   out_4512091588274869741[3] = 0;
   out_4512091588274869741[4] = 0;
   out_4512091588274869741[5] = 0;
   out_4512091588274869741[6] = 0;
   out_4512091588274869741[7] = 1;
   out_4512091588274869741[8] = 0;
}
void h_27(double *state, double *unused, double *out_6340731339944849957) {
   out_6340731339944849957[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3074690528344478498) {
   out_3074690528344478498[0] = 0;
   out_3074690528344478498[1] = 0;
   out_3074690528344478498[2] = 0;
   out_3074690528344478498[3] = 1;
   out_3074690528344478498[4] = 0;
   out_3074690528344478498[5] = 0;
   out_3074690528344478498[6] = 0;
   out_3074690528344478498[7] = 0;
   out_3074690528344478498[8] = 0;
}
void h_29(double *state, double *unused, double *out_8468563205510679309) {
   out_8468563205510679309[0] = state[1];
}
void H_29(double *state, double *unused, double *out_389695872229661403) {
   out_389695872229661403[0] = 0;
   out_389695872229661403[1] = 1;
   out_389695872229661403[2] = 0;
   out_389695872229661403[3] = 0;
   out_389695872229661403[4] = 0;
   out_389695872229661403[5] = 0;
   out_389695872229661403[6] = 0;
   out_389695872229661403[7] = 0;
   out_389695872229661403[8] = 0;
}
void h_28(double *state, double *unused, double *out_7104339466103856014) {
   out_7104339466103856014[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8576291801425991511) {
   out_8576291801425991511[0] = 1;
   out_8576291801425991511[1] = 0;
   out_8576291801425991511[2] = 0;
   out_8576291801425991511[3] = 0;
   out_8576291801425991511[4] = 0;
   out_8576291801425991511[5] = 0;
   out_8576291801425991511[6] = 0;
   out_8576291801425991511[7] = 0;
   out_8576291801425991511[8] = 0;
}
void h_31(double *state, double *unused, double *out_2522625404144497340) {
   out_2522625404144497340[0] = state[8];
}
void H_31(double *state, double *unused, double *out_739942307523853089) {
   out_739942307523853089[0] = 0;
   out_739942307523853089[1] = 0;
   out_739942307523853089[2] = 0;
   out_739942307523853089[3] = 0;
   out_739942307523853089[4] = 0;
   out_739942307523853089[5] = 0;
   out_739942307523853089[6] = 0;
   out_739942307523853089[7] = 0;
   out_739942307523853089[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_648770422652277661) {
  err_fun(nom_x, delta_x, out_648770422652277661);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8433637752559620590) {
  inv_err_fun(nom_x, true_x, out_8433637752559620590);
}
void car_H_mod_fun(double *state, double *out_8422599956511423720) {
  H_mod_fun(state, out_8422599956511423720);
}
void car_f_fun(double *state, double dt, double *out_9124674145630526498) {
  f_fun(state,  dt, out_9124674145630526498);
}
void car_F_fun(double *state, double dt, double *out_7980063177758984153) {
  F_fun(state,  dt, out_7980063177758984153);
}
void car_h_25(double *state, double *unused, double *out_7427457988301314284) {
  h_25(state, unused, out_7427457988301314284);
}
void car_H_25(double *state, double *unused, double *out_770588269400813517) {
  H_25(state, unused, out_770588269400813517);
}
void car_h_24(double *state, double *unused, double *out_3062542313716558558) {
  h_24(state, unused, out_3062542313716558558);
}
void car_H_24(double *state, double *unused, double *out_5590909774056801780) {
  H_24(state, unused, out_5590909774056801780);
}
void car_h_30(double *state, double *unused, double *out_1260343948330179981) {
  h_30(state, unused, out_1260343948330179981);
}
void car_H_30(double *state, double *unused, double *out_899927216544053587) {
  H_30(state, unused, out_899927216544053587);
}
void car_h_26(double *state, double *unused, double *out_4488267301164684189) {
  h_26(state, unused, out_4488267301164684189);
}
void car_H_26(double *state, double *unused, double *out_4512091588274869741) {
  H_26(state, unused, out_4512091588274869741);
}
void car_h_27(double *state, double *unused, double *out_6340731339944849957) {
  h_27(state, unused, out_6340731339944849957);
}
void car_H_27(double *state, double *unused, double *out_3074690528344478498) {
  H_27(state, unused, out_3074690528344478498);
}
void car_h_29(double *state, double *unused, double *out_8468563205510679309) {
  h_29(state, unused, out_8468563205510679309);
}
void car_H_29(double *state, double *unused, double *out_389695872229661403) {
  H_29(state, unused, out_389695872229661403);
}
void car_h_28(double *state, double *unused, double *out_7104339466103856014) {
  h_28(state, unused, out_7104339466103856014);
}
void car_H_28(double *state, double *unused, double *out_8576291801425991511) {
  H_28(state, unused, out_8576291801425991511);
}
void car_h_31(double *state, double *unused, double *out_2522625404144497340) {
  h_31(state, unused, out_2522625404144497340);
}
void car_H_31(double *state, double *unused, double *out_739942307523853089) {
  H_31(state, unused, out_739942307523853089);
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
