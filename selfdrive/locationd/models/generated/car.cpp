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
void err_fun(double *nom_x, double *delta_x, double *out_3886210737280219279) {
   out_3886210737280219279[0] = delta_x[0] + nom_x[0];
   out_3886210737280219279[1] = delta_x[1] + nom_x[1];
   out_3886210737280219279[2] = delta_x[2] + nom_x[2];
   out_3886210737280219279[3] = delta_x[3] + nom_x[3];
   out_3886210737280219279[4] = delta_x[4] + nom_x[4];
   out_3886210737280219279[5] = delta_x[5] + nom_x[5];
   out_3886210737280219279[6] = delta_x[6] + nom_x[6];
   out_3886210737280219279[7] = delta_x[7] + nom_x[7];
   out_3886210737280219279[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_9203878995777804762) {
   out_9203878995777804762[0] = -nom_x[0] + true_x[0];
   out_9203878995777804762[1] = -nom_x[1] + true_x[1];
   out_9203878995777804762[2] = -nom_x[2] + true_x[2];
   out_9203878995777804762[3] = -nom_x[3] + true_x[3];
   out_9203878995777804762[4] = -nom_x[4] + true_x[4];
   out_9203878995777804762[5] = -nom_x[5] + true_x[5];
   out_9203878995777804762[6] = -nom_x[6] + true_x[6];
   out_9203878995777804762[7] = -nom_x[7] + true_x[7];
   out_9203878995777804762[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8506196822923476348) {
   out_8506196822923476348[0] = 1.0;
   out_8506196822923476348[1] = 0.0;
   out_8506196822923476348[2] = 0.0;
   out_8506196822923476348[3] = 0.0;
   out_8506196822923476348[4] = 0.0;
   out_8506196822923476348[5] = 0.0;
   out_8506196822923476348[6] = 0.0;
   out_8506196822923476348[7] = 0.0;
   out_8506196822923476348[8] = 0.0;
   out_8506196822923476348[9] = 0.0;
   out_8506196822923476348[10] = 1.0;
   out_8506196822923476348[11] = 0.0;
   out_8506196822923476348[12] = 0.0;
   out_8506196822923476348[13] = 0.0;
   out_8506196822923476348[14] = 0.0;
   out_8506196822923476348[15] = 0.0;
   out_8506196822923476348[16] = 0.0;
   out_8506196822923476348[17] = 0.0;
   out_8506196822923476348[18] = 0.0;
   out_8506196822923476348[19] = 0.0;
   out_8506196822923476348[20] = 1.0;
   out_8506196822923476348[21] = 0.0;
   out_8506196822923476348[22] = 0.0;
   out_8506196822923476348[23] = 0.0;
   out_8506196822923476348[24] = 0.0;
   out_8506196822923476348[25] = 0.0;
   out_8506196822923476348[26] = 0.0;
   out_8506196822923476348[27] = 0.0;
   out_8506196822923476348[28] = 0.0;
   out_8506196822923476348[29] = 0.0;
   out_8506196822923476348[30] = 1.0;
   out_8506196822923476348[31] = 0.0;
   out_8506196822923476348[32] = 0.0;
   out_8506196822923476348[33] = 0.0;
   out_8506196822923476348[34] = 0.0;
   out_8506196822923476348[35] = 0.0;
   out_8506196822923476348[36] = 0.0;
   out_8506196822923476348[37] = 0.0;
   out_8506196822923476348[38] = 0.0;
   out_8506196822923476348[39] = 0.0;
   out_8506196822923476348[40] = 1.0;
   out_8506196822923476348[41] = 0.0;
   out_8506196822923476348[42] = 0.0;
   out_8506196822923476348[43] = 0.0;
   out_8506196822923476348[44] = 0.0;
   out_8506196822923476348[45] = 0.0;
   out_8506196822923476348[46] = 0.0;
   out_8506196822923476348[47] = 0.0;
   out_8506196822923476348[48] = 0.0;
   out_8506196822923476348[49] = 0.0;
   out_8506196822923476348[50] = 1.0;
   out_8506196822923476348[51] = 0.0;
   out_8506196822923476348[52] = 0.0;
   out_8506196822923476348[53] = 0.0;
   out_8506196822923476348[54] = 0.0;
   out_8506196822923476348[55] = 0.0;
   out_8506196822923476348[56] = 0.0;
   out_8506196822923476348[57] = 0.0;
   out_8506196822923476348[58] = 0.0;
   out_8506196822923476348[59] = 0.0;
   out_8506196822923476348[60] = 1.0;
   out_8506196822923476348[61] = 0.0;
   out_8506196822923476348[62] = 0.0;
   out_8506196822923476348[63] = 0.0;
   out_8506196822923476348[64] = 0.0;
   out_8506196822923476348[65] = 0.0;
   out_8506196822923476348[66] = 0.0;
   out_8506196822923476348[67] = 0.0;
   out_8506196822923476348[68] = 0.0;
   out_8506196822923476348[69] = 0.0;
   out_8506196822923476348[70] = 1.0;
   out_8506196822923476348[71] = 0.0;
   out_8506196822923476348[72] = 0.0;
   out_8506196822923476348[73] = 0.0;
   out_8506196822923476348[74] = 0.0;
   out_8506196822923476348[75] = 0.0;
   out_8506196822923476348[76] = 0.0;
   out_8506196822923476348[77] = 0.0;
   out_8506196822923476348[78] = 0.0;
   out_8506196822923476348[79] = 0.0;
   out_8506196822923476348[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2212415948681408961) {
   out_2212415948681408961[0] = state[0];
   out_2212415948681408961[1] = state[1];
   out_2212415948681408961[2] = state[2];
   out_2212415948681408961[3] = state[3];
   out_2212415948681408961[4] = state[4];
   out_2212415948681408961[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2212415948681408961[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2212415948681408961[7] = state[7];
   out_2212415948681408961[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8605893895722033804) {
   out_8605893895722033804[0] = 1;
   out_8605893895722033804[1] = 0;
   out_8605893895722033804[2] = 0;
   out_8605893895722033804[3] = 0;
   out_8605893895722033804[4] = 0;
   out_8605893895722033804[5] = 0;
   out_8605893895722033804[6] = 0;
   out_8605893895722033804[7] = 0;
   out_8605893895722033804[8] = 0;
   out_8605893895722033804[9] = 0;
   out_8605893895722033804[10] = 1;
   out_8605893895722033804[11] = 0;
   out_8605893895722033804[12] = 0;
   out_8605893895722033804[13] = 0;
   out_8605893895722033804[14] = 0;
   out_8605893895722033804[15] = 0;
   out_8605893895722033804[16] = 0;
   out_8605893895722033804[17] = 0;
   out_8605893895722033804[18] = 0;
   out_8605893895722033804[19] = 0;
   out_8605893895722033804[20] = 1;
   out_8605893895722033804[21] = 0;
   out_8605893895722033804[22] = 0;
   out_8605893895722033804[23] = 0;
   out_8605893895722033804[24] = 0;
   out_8605893895722033804[25] = 0;
   out_8605893895722033804[26] = 0;
   out_8605893895722033804[27] = 0;
   out_8605893895722033804[28] = 0;
   out_8605893895722033804[29] = 0;
   out_8605893895722033804[30] = 1;
   out_8605893895722033804[31] = 0;
   out_8605893895722033804[32] = 0;
   out_8605893895722033804[33] = 0;
   out_8605893895722033804[34] = 0;
   out_8605893895722033804[35] = 0;
   out_8605893895722033804[36] = 0;
   out_8605893895722033804[37] = 0;
   out_8605893895722033804[38] = 0;
   out_8605893895722033804[39] = 0;
   out_8605893895722033804[40] = 1;
   out_8605893895722033804[41] = 0;
   out_8605893895722033804[42] = 0;
   out_8605893895722033804[43] = 0;
   out_8605893895722033804[44] = 0;
   out_8605893895722033804[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8605893895722033804[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8605893895722033804[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8605893895722033804[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8605893895722033804[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8605893895722033804[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8605893895722033804[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8605893895722033804[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8605893895722033804[53] = -9.8100000000000005*dt;
   out_8605893895722033804[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8605893895722033804[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8605893895722033804[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8605893895722033804[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8605893895722033804[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8605893895722033804[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8605893895722033804[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8605893895722033804[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8605893895722033804[62] = 0;
   out_8605893895722033804[63] = 0;
   out_8605893895722033804[64] = 0;
   out_8605893895722033804[65] = 0;
   out_8605893895722033804[66] = 0;
   out_8605893895722033804[67] = 0;
   out_8605893895722033804[68] = 0;
   out_8605893895722033804[69] = 0;
   out_8605893895722033804[70] = 1;
   out_8605893895722033804[71] = 0;
   out_8605893895722033804[72] = 0;
   out_8605893895722033804[73] = 0;
   out_8605893895722033804[74] = 0;
   out_8605893895722033804[75] = 0;
   out_8605893895722033804[76] = 0;
   out_8605893895722033804[77] = 0;
   out_8605893895722033804[78] = 0;
   out_8605893895722033804[79] = 0;
   out_8605893895722033804[80] = 1;
}
void h_25(double *state, double *unused, double *out_80606407557009467) {
   out_80606407557009467[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2019209217812215463) {
   out_2019209217812215463[0] = 0;
   out_2019209217812215463[1] = 0;
   out_2019209217812215463[2] = 0;
   out_2019209217812215463[3] = 0;
   out_2019209217812215463[4] = 0;
   out_2019209217812215463[5] = 0;
   out_2019209217812215463[6] = 1;
   out_2019209217812215463[7] = 0;
   out_2019209217812215463[8] = 0;
}
void h_24(double *state, double *unused, double *out_8156817116559759487) {
   out_8156817116559759487[0] = state[4];
   out_8156817116559759487[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7208855968256979762) {
   out_7208855968256979762[0] = 0;
   out_7208855968256979762[1] = 0;
   out_7208855968256979762[2] = 0;
   out_7208855968256979762[3] = 0;
   out_7208855968256979762[4] = 1;
   out_7208855968256979762[5] = 0;
   out_7208855968256979762[6] = 0;
   out_7208855968256979762[7] = 0;
   out_7208855968256979762[8] = 0;
   out_7208855968256979762[9] = 0;
   out_7208855968256979762[10] = 0;
   out_7208855968256979762[11] = 0;
   out_7208855968256979762[12] = 0;
   out_7208855968256979762[13] = 0;
   out_7208855968256979762[14] = 1;
   out_7208855968256979762[15] = 0;
   out_7208855968256979762[16] = 0;
   out_7208855968256979762[17] = 0;
}
void h_30(double *state, double *unused, double *out_7682658849263662974) {
   out_7682658849263662974[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6546905547939823661) {
   out_6546905547939823661[0] = 0;
   out_6546905547939823661[1] = 0;
   out_6546905547939823661[2] = 0;
   out_6546905547939823661[3] = 0;
   out_6546905547939823661[4] = 1;
   out_6546905547939823661[5] = 0;
   out_6546905547939823661[6] = 0;
   out_6546905547939823661[7] = 0;
   out_6546905547939823661[8] = 0;
}
void h_26(double *state, double *unused, double *out_2046248304577196316) {
   out_2046248304577196316[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5760712536686271687) {
   out_5760712536686271687[0] = 0;
   out_5760712536686271687[1] = 0;
   out_5760712536686271687[2] = 0;
   out_5760712536686271687[3] = 0;
   out_5760712536686271687[4] = 0;
   out_5760712536686271687[5] = 0;
   out_5760712536686271687[6] = 0;
   out_5760712536686271687[7] = 1;
   out_5760712536686271687[8] = 0;
}
void h_27(double *state, double *unused, double *out_4505967322855241000) {
   out_4505967322855241000[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8721668859740248572) {
   out_8721668859740248572[0] = 0;
   out_8721668859740248572[1] = 0;
   out_8721668859740248572[2] = 0;
   out_8721668859740248572[3] = 1;
   out_8721668859740248572[4] = 0;
   out_8721668859740248572[5] = 0;
   out_8721668859740248572[6] = 0;
   out_8721668859740248572[7] = 0;
   out_8721668859740248572[8] = 0;
}
void h_29(double *state, double *unused, double *out_1934047599768798804) {
   out_1934047599768798804[0] = state[1];
}
void H_29(double *state, double *unused, double *out_6036674203625431477) {
   out_6036674203625431477[0] = 0;
   out_6036674203625431477[1] = 1;
   out_6036674203625431477[2] = 0;
   out_6036674203625431477[3] = 0;
   out_6036674203625431477[4] = 0;
   out_6036674203625431477[5] = 0;
   out_6036674203625431477[6] = 0;
   out_6036674203625431477[7] = 0;
   out_6036674203625431477[8] = 0;
}
void h_28(double *state, double *unused, double *out_3899689496788985653) {
   out_3899689496788985653[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7327670853014589565) {
   out_7327670853014589565[0] = 1;
   out_7327670853014589565[1] = 0;
   out_7327670853014589565[2] = 0;
   out_7327670853014589565[3] = 0;
   out_7327670853014589565[4] = 0;
   out_7327670853014589565[5] = 0;
   out_7327670853014589565[6] = 0;
   out_7327670853014589565[7] = 0;
   out_7327670853014589565[8] = 0;
}
void h_31(double *state, double *unused, double *out_40967961750261831) {
   out_40967961750261831[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6386920638919623163) {
   out_6386920638919623163[0] = 0;
   out_6386920638919623163[1] = 0;
   out_6386920638919623163[2] = 0;
   out_6386920638919623163[3] = 0;
   out_6386920638919623163[4] = 0;
   out_6386920638919623163[5] = 0;
   out_6386920638919623163[6] = 0;
   out_6386920638919623163[7] = 0;
   out_6386920638919623163[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_3886210737280219279) {
  err_fun(nom_x, delta_x, out_3886210737280219279);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_9203878995777804762) {
  inv_err_fun(nom_x, true_x, out_9203878995777804762);
}
void car_H_mod_fun(double *state, double *out_8506196822923476348) {
  H_mod_fun(state, out_8506196822923476348);
}
void car_f_fun(double *state, double dt, double *out_2212415948681408961) {
  f_fun(state,  dt, out_2212415948681408961);
}
void car_F_fun(double *state, double dt, double *out_8605893895722033804) {
  F_fun(state,  dt, out_8605893895722033804);
}
void car_h_25(double *state, double *unused, double *out_80606407557009467) {
  h_25(state, unused, out_80606407557009467);
}
void car_H_25(double *state, double *unused, double *out_2019209217812215463) {
  H_25(state, unused, out_2019209217812215463);
}
void car_h_24(double *state, double *unused, double *out_8156817116559759487) {
  h_24(state, unused, out_8156817116559759487);
}
void car_H_24(double *state, double *unused, double *out_7208855968256979762) {
  H_24(state, unused, out_7208855968256979762);
}
void car_h_30(double *state, double *unused, double *out_7682658849263662974) {
  h_30(state, unused, out_7682658849263662974);
}
void car_H_30(double *state, double *unused, double *out_6546905547939823661) {
  H_30(state, unused, out_6546905547939823661);
}
void car_h_26(double *state, double *unused, double *out_2046248304577196316) {
  h_26(state, unused, out_2046248304577196316);
}
void car_H_26(double *state, double *unused, double *out_5760712536686271687) {
  H_26(state, unused, out_5760712536686271687);
}
void car_h_27(double *state, double *unused, double *out_4505967322855241000) {
  h_27(state, unused, out_4505967322855241000);
}
void car_H_27(double *state, double *unused, double *out_8721668859740248572) {
  H_27(state, unused, out_8721668859740248572);
}
void car_h_29(double *state, double *unused, double *out_1934047599768798804) {
  h_29(state, unused, out_1934047599768798804);
}
void car_H_29(double *state, double *unused, double *out_6036674203625431477) {
  H_29(state, unused, out_6036674203625431477);
}
void car_h_28(double *state, double *unused, double *out_3899689496788985653) {
  h_28(state, unused, out_3899689496788985653);
}
void car_H_28(double *state, double *unused, double *out_7327670853014589565) {
  H_28(state, unused, out_7327670853014589565);
}
void car_h_31(double *state, double *unused, double *out_40967961750261831) {
  h_31(state, unused, out_40967961750261831);
}
void car_H_31(double *state, double *unused, double *out_6386920638919623163) {
  H_31(state, unused, out_6386920638919623163);
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
