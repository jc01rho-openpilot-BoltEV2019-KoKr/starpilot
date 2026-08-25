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
void err_fun(double *nom_x, double *delta_x, double *out_7084348270501559549) {
   out_7084348270501559549[0] = delta_x[0] + nom_x[0];
   out_7084348270501559549[1] = delta_x[1] + nom_x[1];
   out_7084348270501559549[2] = delta_x[2] + nom_x[2];
   out_7084348270501559549[3] = delta_x[3] + nom_x[3];
   out_7084348270501559549[4] = delta_x[4] + nom_x[4];
   out_7084348270501559549[5] = delta_x[5] + nom_x[5];
   out_7084348270501559549[6] = delta_x[6] + nom_x[6];
   out_7084348270501559549[7] = delta_x[7] + nom_x[7];
   out_7084348270501559549[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_693097121251649199) {
   out_693097121251649199[0] = -nom_x[0] + true_x[0];
   out_693097121251649199[1] = -nom_x[1] + true_x[1];
   out_693097121251649199[2] = -nom_x[2] + true_x[2];
   out_693097121251649199[3] = -nom_x[3] + true_x[3];
   out_693097121251649199[4] = -nom_x[4] + true_x[4];
   out_693097121251649199[5] = -nom_x[5] + true_x[5];
   out_693097121251649199[6] = -nom_x[6] + true_x[6];
   out_693097121251649199[7] = -nom_x[7] + true_x[7];
   out_693097121251649199[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1623843232183312219) {
   out_1623843232183312219[0] = 1.0;
   out_1623843232183312219[1] = 0.0;
   out_1623843232183312219[2] = 0.0;
   out_1623843232183312219[3] = 0.0;
   out_1623843232183312219[4] = 0.0;
   out_1623843232183312219[5] = 0.0;
   out_1623843232183312219[6] = 0.0;
   out_1623843232183312219[7] = 0.0;
   out_1623843232183312219[8] = 0.0;
   out_1623843232183312219[9] = 0.0;
   out_1623843232183312219[10] = 1.0;
   out_1623843232183312219[11] = 0.0;
   out_1623843232183312219[12] = 0.0;
   out_1623843232183312219[13] = 0.0;
   out_1623843232183312219[14] = 0.0;
   out_1623843232183312219[15] = 0.0;
   out_1623843232183312219[16] = 0.0;
   out_1623843232183312219[17] = 0.0;
   out_1623843232183312219[18] = 0.0;
   out_1623843232183312219[19] = 0.0;
   out_1623843232183312219[20] = 1.0;
   out_1623843232183312219[21] = 0.0;
   out_1623843232183312219[22] = 0.0;
   out_1623843232183312219[23] = 0.0;
   out_1623843232183312219[24] = 0.0;
   out_1623843232183312219[25] = 0.0;
   out_1623843232183312219[26] = 0.0;
   out_1623843232183312219[27] = 0.0;
   out_1623843232183312219[28] = 0.0;
   out_1623843232183312219[29] = 0.0;
   out_1623843232183312219[30] = 1.0;
   out_1623843232183312219[31] = 0.0;
   out_1623843232183312219[32] = 0.0;
   out_1623843232183312219[33] = 0.0;
   out_1623843232183312219[34] = 0.0;
   out_1623843232183312219[35] = 0.0;
   out_1623843232183312219[36] = 0.0;
   out_1623843232183312219[37] = 0.0;
   out_1623843232183312219[38] = 0.0;
   out_1623843232183312219[39] = 0.0;
   out_1623843232183312219[40] = 1.0;
   out_1623843232183312219[41] = 0.0;
   out_1623843232183312219[42] = 0.0;
   out_1623843232183312219[43] = 0.0;
   out_1623843232183312219[44] = 0.0;
   out_1623843232183312219[45] = 0.0;
   out_1623843232183312219[46] = 0.0;
   out_1623843232183312219[47] = 0.0;
   out_1623843232183312219[48] = 0.0;
   out_1623843232183312219[49] = 0.0;
   out_1623843232183312219[50] = 1.0;
   out_1623843232183312219[51] = 0.0;
   out_1623843232183312219[52] = 0.0;
   out_1623843232183312219[53] = 0.0;
   out_1623843232183312219[54] = 0.0;
   out_1623843232183312219[55] = 0.0;
   out_1623843232183312219[56] = 0.0;
   out_1623843232183312219[57] = 0.0;
   out_1623843232183312219[58] = 0.0;
   out_1623843232183312219[59] = 0.0;
   out_1623843232183312219[60] = 1.0;
   out_1623843232183312219[61] = 0.0;
   out_1623843232183312219[62] = 0.0;
   out_1623843232183312219[63] = 0.0;
   out_1623843232183312219[64] = 0.0;
   out_1623843232183312219[65] = 0.0;
   out_1623843232183312219[66] = 0.0;
   out_1623843232183312219[67] = 0.0;
   out_1623843232183312219[68] = 0.0;
   out_1623843232183312219[69] = 0.0;
   out_1623843232183312219[70] = 1.0;
   out_1623843232183312219[71] = 0.0;
   out_1623843232183312219[72] = 0.0;
   out_1623843232183312219[73] = 0.0;
   out_1623843232183312219[74] = 0.0;
   out_1623843232183312219[75] = 0.0;
   out_1623843232183312219[76] = 0.0;
   out_1623843232183312219[77] = 0.0;
   out_1623843232183312219[78] = 0.0;
   out_1623843232183312219[79] = 0.0;
   out_1623843232183312219[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_1622952619636770739) {
   out_1622952619636770739[0] = state[0];
   out_1622952619636770739[1] = state[1];
   out_1622952619636770739[2] = state[2];
   out_1622952619636770739[3] = state[3];
   out_1622952619636770739[4] = state[4];
   out_1622952619636770739[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_1622952619636770739[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_1622952619636770739[7] = state[7];
   out_1622952619636770739[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7142842168519911469) {
   out_7142842168519911469[0] = 1;
   out_7142842168519911469[1] = 0;
   out_7142842168519911469[2] = 0;
   out_7142842168519911469[3] = 0;
   out_7142842168519911469[4] = 0;
   out_7142842168519911469[5] = 0;
   out_7142842168519911469[6] = 0;
   out_7142842168519911469[7] = 0;
   out_7142842168519911469[8] = 0;
   out_7142842168519911469[9] = 0;
   out_7142842168519911469[10] = 1;
   out_7142842168519911469[11] = 0;
   out_7142842168519911469[12] = 0;
   out_7142842168519911469[13] = 0;
   out_7142842168519911469[14] = 0;
   out_7142842168519911469[15] = 0;
   out_7142842168519911469[16] = 0;
   out_7142842168519911469[17] = 0;
   out_7142842168519911469[18] = 0;
   out_7142842168519911469[19] = 0;
   out_7142842168519911469[20] = 1;
   out_7142842168519911469[21] = 0;
   out_7142842168519911469[22] = 0;
   out_7142842168519911469[23] = 0;
   out_7142842168519911469[24] = 0;
   out_7142842168519911469[25] = 0;
   out_7142842168519911469[26] = 0;
   out_7142842168519911469[27] = 0;
   out_7142842168519911469[28] = 0;
   out_7142842168519911469[29] = 0;
   out_7142842168519911469[30] = 1;
   out_7142842168519911469[31] = 0;
   out_7142842168519911469[32] = 0;
   out_7142842168519911469[33] = 0;
   out_7142842168519911469[34] = 0;
   out_7142842168519911469[35] = 0;
   out_7142842168519911469[36] = 0;
   out_7142842168519911469[37] = 0;
   out_7142842168519911469[38] = 0;
   out_7142842168519911469[39] = 0;
   out_7142842168519911469[40] = 1;
   out_7142842168519911469[41] = 0;
   out_7142842168519911469[42] = 0;
   out_7142842168519911469[43] = 0;
   out_7142842168519911469[44] = 0;
   out_7142842168519911469[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7142842168519911469[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7142842168519911469[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7142842168519911469[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7142842168519911469[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7142842168519911469[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7142842168519911469[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7142842168519911469[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7142842168519911469[53] = -9.8100000000000005*dt;
   out_7142842168519911469[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7142842168519911469[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7142842168519911469[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7142842168519911469[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7142842168519911469[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7142842168519911469[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7142842168519911469[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7142842168519911469[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7142842168519911469[62] = 0;
   out_7142842168519911469[63] = 0;
   out_7142842168519911469[64] = 0;
   out_7142842168519911469[65] = 0;
   out_7142842168519911469[66] = 0;
   out_7142842168519911469[67] = 0;
   out_7142842168519911469[68] = 0;
   out_7142842168519911469[69] = 0;
   out_7142842168519911469[70] = 1;
   out_7142842168519911469[71] = 0;
   out_7142842168519911469[72] = 0;
   out_7142842168519911469[73] = 0;
   out_7142842168519911469[74] = 0;
   out_7142842168519911469[75] = 0;
   out_7142842168519911469[76] = 0;
   out_7142842168519911469[77] = 0;
   out_7142842168519911469[78] = 0;
   out_7142842168519911469[79] = 0;
   out_7142842168519911469[80] = 1;
}
void h_25(double *state, double *unused, double *out_7699167154037203435) {
   out_7699167154037203435[0] = state[6];
}
void H_25(double *state, double *unused, double *out_1899137417806179458) {
   out_1899137417806179458[0] = 0;
   out_1899137417806179458[1] = 0;
   out_1899137417806179458[2] = 0;
   out_1899137417806179458[3] = 0;
   out_1899137417806179458[4] = 0;
   out_1899137417806179458[5] = 0;
   out_1899137417806179458[6] = 1;
   out_1899137417806179458[7] = 0;
   out_1899137417806179458[8] = 0;
}
void h_24(double *state, double *unused, double *out_5775267180984789848) {
   out_5775267180984789848[0] = state[4];
   out_5775267180984789848[1] = state[5];
}
void H_24(double *state, double *unused, double *out_273512181199320108) {
   out_273512181199320108[0] = 0;
   out_273512181199320108[1] = 0;
   out_273512181199320108[2] = 0;
   out_273512181199320108[3] = 0;
   out_273512181199320108[4] = 1;
   out_273512181199320108[5] = 0;
   out_273512181199320108[6] = 0;
   out_273512181199320108[7] = 0;
   out_273512181199320108[8] = 0;
   out_273512181199320108[9] = 0;
   out_273512181199320108[10] = 0;
   out_273512181199320108[11] = 0;
   out_273512181199320108[12] = 0;
   out_273512181199320108[13] = 0;
   out_273512181199320108[14] = 1;
   out_273512181199320108[15] = 0;
   out_273512181199320108[16] = 0;
   out_273512181199320108[17] = 0;
}
void h_30(double *state, double *unused, double *out_940710322681338449) {
   out_940710322681338449[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8815827759297796213) {
   out_8815827759297796213[0] = 0;
   out_8815827759297796213[1] = 0;
   out_8815827759297796213[2] = 0;
   out_8815827759297796213[3] = 0;
   out_8815827759297796213[4] = 1;
   out_8815827759297796213[5] = 0;
   out_8815827759297796213[6] = 0;
   out_8815827759297796213[7] = 0;
   out_8815827759297796213[8] = 0;
}
void h_26(double *state, double *unused, double *out_1922794416016636561) {
   out_1922794416016636561[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1842365901067876766) {
   out_1842365901067876766[0] = 0;
   out_1842365901067876766[1] = 0;
   out_1842365901067876766[2] = 0;
   out_1842365901067876766[3] = 0;
   out_1842365901067876766[4] = 0;
   out_1842365901067876766[5] = 0;
   out_1842365901067876766[6] = 0;
   out_1842365901067876766[7] = 1;
   out_1842365901067876766[8] = 0;
}
void h_27(double *state, double *unused, double *out_3098231746361013839) {
   out_3098231746361013839[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6641064447497371302) {
   out_6641064447497371302[0] = 0;
   out_6641064447497371302[1] = 0;
   out_6641064447497371302[2] = 0;
   out_6641064447497371302[3] = 1;
   out_6641064447497371302[4] = 0;
   out_6641064447497371302[5] = 0;
   out_6641064447497371302[6] = 0;
   out_6641064447497371302[7] = 0;
   out_6641064447497371302[8] = 0;
}
void h_29(double *state, double *unused, double *out_539217781893008511) {
   out_539217781893008511[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4927701720627820269) {
   out_4927701720627820269[0] = 0;
   out_4927701720627820269[1] = 1;
   out_4927701720627820269[2] = 0;
   out_4927701720627820269[3] = 0;
   out_4927701720627820269[4] = 0;
   out_4927701720627820269[5] = 0;
   out_4927701720627820269[6] = 0;
   out_4927701720627820269[7] = 0;
   out_4927701720627820269[8] = 0;
}
void h_28(double *state, double *unused, double *out_822702928747961705) {
   out_822702928747961705[0] = state[0];
}
void H_28(double *state, double *unused, double *out_154697296441710305) {
   out_154697296441710305[0] = 1;
   out_154697296441710305[1] = 0;
   out_154697296441710305[2] = 0;
   out_154697296441710305[3] = 0;
   out_154697296441710305[4] = 0;
   out_154697296441710305[5] = 0;
   out_154697296441710305[6] = 0;
   out_154697296441710305[7] = 0;
   out_154697296441710305[8] = 0;
}
void h_31(double *state, double *unused, double *out_6649273621392976317) {
   out_6649273621392976317[0] = state[8];
}
void H_31(double *state, double *unused, double *out_1929783379683139886) {
   out_1929783379683139886[0] = 0;
   out_1929783379683139886[1] = 0;
   out_1929783379683139886[2] = 0;
   out_1929783379683139886[3] = 0;
   out_1929783379683139886[4] = 0;
   out_1929783379683139886[5] = 0;
   out_1929783379683139886[6] = 0;
   out_1929783379683139886[7] = 0;
   out_1929783379683139886[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7084348270501559549) {
  err_fun(nom_x, delta_x, out_7084348270501559549);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_693097121251649199) {
  inv_err_fun(nom_x, true_x, out_693097121251649199);
}
void car_H_mod_fun(double *state, double *out_1623843232183312219) {
  H_mod_fun(state, out_1623843232183312219);
}
void car_f_fun(double *state, double dt, double *out_1622952619636770739) {
  f_fun(state,  dt, out_1622952619636770739);
}
void car_F_fun(double *state, double dt, double *out_7142842168519911469) {
  F_fun(state,  dt, out_7142842168519911469);
}
void car_h_25(double *state, double *unused, double *out_7699167154037203435) {
  h_25(state, unused, out_7699167154037203435);
}
void car_H_25(double *state, double *unused, double *out_1899137417806179458) {
  H_25(state, unused, out_1899137417806179458);
}
void car_h_24(double *state, double *unused, double *out_5775267180984789848) {
  h_24(state, unused, out_5775267180984789848);
}
void car_H_24(double *state, double *unused, double *out_273512181199320108) {
  H_24(state, unused, out_273512181199320108);
}
void car_h_30(double *state, double *unused, double *out_940710322681338449) {
  h_30(state, unused, out_940710322681338449);
}
void car_H_30(double *state, double *unused, double *out_8815827759297796213) {
  H_30(state, unused, out_8815827759297796213);
}
void car_h_26(double *state, double *unused, double *out_1922794416016636561) {
  h_26(state, unused, out_1922794416016636561);
}
void car_H_26(double *state, double *unused, double *out_1842365901067876766) {
  H_26(state, unused, out_1842365901067876766);
}
void car_h_27(double *state, double *unused, double *out_3098231746361013839) {
  h_27(state, unused, out_3098231746361013839);
}
void car_H_27(double *state, double *unused, double *out_6641064447497371302) {
  H_27(state, unused, out_6641064447497371302);
}
void car_h_29(double *state, double *unused, double *out_539217781893008511) {
  h_29(state, unused, out_539217781893008511);
}
void car_H_29(double *state, double *unused, double *out_4927701720627820269) {
  H_29(state, unused, out_4927701720627820269);
}
void car_h_28(double *state, double *unused, double *out_822702928747961705) {
  h_28(state, unused, out_822702928747961705);
}
void car_H_28(double *state, double *unused, double *out_154697296441710305) {
  H_28(state, unused, out_154697296441710305);
}
void car_h_31(double *state, double *unused, double *out_6649273621392976317) {
  h_31(state, unused, out_6649273621392976317);
}
void car_H_31(double *state, double *unused, double *out_1929783379683139886) {
  H_31(state, unused, out_1929783379683139886);
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
