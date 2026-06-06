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
void err_fun(double *nom_x, double *delta_x, double *out_8558166113930061773) {
   out_8558166113930061773[0] = delta_x[0] + nom_x[0];
   out_8558166113930061773[1] = delta_x[1] + nom_x[1];
   out_8558166113930061773[2] = delta_x[2] + nom_x[2];
   out_8558166113930061773[3] = delta_x[3] + nom_x[3];
   out_8558166113930061773[4] = delta_x[4] + nom_x[4];
   out_8558166113930061773[5] = delta_x[5] + nom_x[5];
   out_8558166113930061773[6] = delta_x[6] + nom_x[6];
   out_8558166113930061773[7] = delta_x[7] + nom_x[7];
   out_8558166113930061773[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2269670274683655268) {
   out_2269670274683655268[0] = -nom_x[0] + true_x[0];
   out_2269670274683655268[1] = -nom_x[1] + true_x[1];
   out_2269670274683655268[2] = -nom_x[2] + true_x[2];
   out_2269670274683655268[3] = -nom_x[3] + true_x[3];
   out_2269670274683655268[4] = -nom_x[4] + true_x[4];
   out_2269670274683655268[5] = -nom_x[5] + true_x[5];
   out_2269670274683655268[6] = -nom_x[6] + true_x[6];
   out_2269670274683655268[7] = -nom_x[7] + true_x[7];
   out_2269670274683655268[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_6407701768448647232) {
   out_6407701768448647232[0] = 1.0;
   out_6407701768448647232[1] = 0.0;
   out_6407701768448647232[2] = 0.0;
   out_6407701768448647232[3] = 0.0;
   out_6407701768448647232[4] = 0.0;
   out_6407701768448647232[5] = 0.0;
   out_6407701768448647232[6] = 0.0;
   out_6407701768448647232[7] = 0.0;
   out_6407701768448647232[8] = 0.0;
   out_6407701768448647232[9] = 0.0;
   out_6407701768448647232[10] = 1.0;
   out_6407701768448647232[11] = 0.0;
   out_6407701768448647232[12] = 0.0;
   out_6407701768448647232[13] = 0.0;
   out_6407701768448647232[14] = 0.0;
   out_6407701768448647232[15] = 0.0;
   out_6407701768448647232[16] = 0.0;
   out_6407701768448647232[17] = 0.0;
   out_6407701768448647232[18] = 0.0;
   out_6407701768448647232[19] = 0.0;
   out_6407701768448647232[20] = 1.0;
   out_6407701768448647232[21] = 0.0;
   out_6407701768448647232[22] = 0.0;
   out_6407701768448647232[23] = 0.0;
   out_6407701768448647232[24] = 0.0;
   out_6407701768448647232[25] = 0.0;
   out_6407701768448647232[26] = 0.0;
   out_6407701768448647232[27] = 0.0;
   out_6407701768448647232[28] = 0.0;
   out_6407701768448647232[29] = 0.0;
   out_6407701768448647232[30] = 1.0;
   out_6407701768448647232[31] = 0.0;
   out_6407701768448647232[32] = 0.0;
   out_6407701768448647232[33] = 0.0;
   out_6407701768448647232[34] = 0.0;
   out_6407701768448647232[35] = 0.0;
   out_6407701768448647232[36] = 0.0;
   out_6407701768448647232[37] = 0.0;
   out_6407701768448647232[38] = 0.0;
   out_6407701768448647232[39] = 0.0;
   out_6407701768448647232[40] = 1.0;
   out_6407701768448647232[41] = 0.0;
   out_6407701768448647232[42] = 0.0;
   out_6407701768448647232[43] = 0.0;
   out_6407701768448647232[44] = 0.0;
   out_6407701768448647232[45] = 0.0;
   out_6407701768448647232[46] = 0.0;
   out_6407701768448647232[47] = 0.0;
   out_6407701768448647232[48] = 0.0;
   out_6407701768448647232[49] = 0.0;
   out_6407701768448647232[50] = 1.0;
   out_6407701768448647232[51] = 0.0;
   out_6407701768448647232[52] = 0.0;
   out_6407701768448647232[53] = 0.0;
   out_6407701768448647232[54] = 0.0;
   out_6407701768448647232[55] = 0.0;
   out_6407701768448647232[56] = 0.0;
   out_6407701768448647232[57] = 0.0;
   out_6407701768448647232[58] = 0.0;
   out_6407701768448647232[59] = 0.0;
   out_6407701768448647232[60] = 1.0;
   out_6407701768448647232[61] = 0.0;
   out_6407701768448647232[62] = 0.0;
   out_6407701768448647232[63] = 0.0;
   out_6407701768448647232[64] = 0.0;
   out_6407701768448647232[65] = 0.0;
   out_6407701768448647232[66] = 0.0;
   out_6407701768448647232[67] = 0.0;
   out_6407701768448647232[68] = 0.0;
   out_6407701768448647232[69] = 0.0;
   out_6407701768448647232[70] = 1.0;
   out_6407701768448647232[71] = 0.0;
   out_6407701768448647232[72] = 0.0;
   out_6407701768448647232[73] = 0.0;
   out_6407701768448647232[74] = 0.0;
   out_6407701768448647232[75] = 0.0;
   out_6407701768448647232[76] = 0.0;
   out_6407701768448647232[77] = 0.0;
   out_6407701768448647232[78] = 0.0;
   out_6407701768448647232[79] = 0.0;
   out_6407701768448647232[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_648904423540471901) {
   out_648904423540471901[0] = state[0];
   out_648904423540471901[1] = state[1];
   out_648904423540471901[2] = state[2];
   out_648904423540471901[3] = state[3];
   out_648904423540471901[4] = state[4];
   out_648904423540471901[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_648904423540471901[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_648904423540471901[7] = state[7];
   out_648904423540471901[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7503564954401744509) {
   out_7503564954401744509[0] = 1;
   out_7503564954401744509[1] = 0;
   out_7503564954401744509[2] = 0;
   out_7503564954401744509[3] = 0;
   out_7503564954401744509[4] = 0;
   out_7503564954401744509[5] = 0;
   out_7503564954401744509[6] = 0;
   out_7503564954401744509[7] = 0;
   out_7503564954401744509[8] = 0;
   out_7503564954401744509[9] = 0;
   out_7503564954401744509[10] = 1;
   out_7503564954401744509[11] = 0;
   out_7503564954401744509[12] = 0;
   out_7503564954401744509[13] = 0;
   out_7503564954401744509[14] = 0;
   out_7503564954401744509[15] = 0;
   out_7503564954401744509[16] = 0;
   out_7503564954401744509[17] = 0;
   out_7503564954401744509[18] = 0;
   out_7503564954401744509[19] = 0;
   out_7503564954401744509[20] = 1;
   out_7503564954401744509[21] = 0;
   out_7503564954401744509[22] = 0;
   out_7503564954401744509[23] = 0;
   out_7503564954401744509[24] = 0;
   out_7503564954401744509[25] = 0;
   out_7503564954401744509[26] = 0;
   out_7503564954401744509[27] = 0;
   out_7503564954401744509[28] = 0;
   out_7503564954401744509[29] = 0;
   out_7503564954401744509[30] = 1;
   out_7503564954401744509[31] = 0;
   out_7503564954401744509[32] = 0;
   out_7503564954401744509[33] = 0;
   out_7503564954401744509[34] = 0;
   out_7503564954401744509[35] = 0;
   out_7503564954401744509[36] = 0;
   out_7503564954401744509[37] = 0;
   out_7503564954401744509[38] = 0;
   out_7503564954401744509[39] = 0;
   out_7503564954401744509[40] = 1;
   out_7503564954401744509[41] = 0;
   out_7503564954401744509[42] = 0;
   out_7503564954401744509[43] = 0;
   out_7503564954401744509[44] = 0;
   out_7503564954401744509[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7503564954401744509[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7503564954401744509[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7503564954401744509[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7503564954401744509[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7503564954401744509[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7503564954401744509[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7503564954401744509[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7503564954401744509[53] = -9.8100000000000005*dt;
   out_7503564954401744509[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7503564954401744509[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7503564954401744509[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7503564954401744509[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7503564954401744509[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7503564954401744509[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7503564954401744509[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7503564954401744509[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7503564954401744509[62] = 0;
   out_7503564954401744509[63] = 0;
   out_7503564954401744509[64] = 0;
   out_7503564954401744509[65] = 0;
   out_7503564954401744509[66] = 0;
   out_7503564954401744509[67] = 0;
   out_7503564954401744509[68] = 0;
   out_7503564954401744509[69] = 0;
   out_7503564954401744509[70] = 1;
   out_7503564954401744509[71] = 0;
   out_7503564954401744509[72] = 0;
   out_7503564954401744509[73] = 0;
   out_7503564954401744509[74] = 0;
   out_7503564954401744509[75] = 0;
   out_7503564954401744509[76] = 0;
   out_7503564954401744509[77] = 0;
   out_7503564954401744509[78] = 0;
   out_7503564954401744509[79] = 0;
   out_7503564954401744509[80] = 1;
}
void h_25(double *state, double *unused, double *out_7864801379551668384) {
   out_7864801379551668384[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7135350480076239544) {
   out_7135350480076239544[0] = 0;
   out_7135350480076239544[1] = 0;
   out_7135350480076239544[2] = 0;
   out_7135350480076239544[3] = 0;
   out_7135350480076239544[4] = 0;
   out_7135350480076239544[5] = 0;
   out_7135350480076239544[6] = 1;
   out_7135350480076239544[7] = 0;
   out_7135350480076239544[8] = 0;
}
void h_24(double *state, double *unused, double *out_7538847613518647590) {
   out_7538847613518647590[0] = state[4];
   out_7538847613518647590[1] = state[5];
}
void H_24(double *state, double *unused, double *out_3868719000644595752) {
   out_3868719000644595752[0] = 0;
   out_3868719000644595752[1] = 0;
   out_3868719000644595752[2] = 0;
   out_3868719000644595752[3] = 0;
   out_3868719000644595752[4] = 1;
   out_3868719000644595752[5] = 0;
   out_3868719000644595752[6] = 0;
   out_3868719000644595752[7] = 0;
   out_3868719000644595752[8] = 0;
   out_3868719000644595752[9] = 0;
   out_3868719000644595752[10] = 0;
   out_3868719000644595752[11] = 0;
   out_3868719000644595752[12] = 0;
   out_3868719000644595752[13] = 0;
   out_3868719000644595752[14] = 1;
   out_3868719000644595752[15] = 0;
   out_3868719000644595752[16] = 0;
   out_3868719000644595752[17] = 0;
}
void h_30(double *state, double *unused, double *out_8021988047902797529) {
   out_8021988047902797529[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6783697263505703874) {
   out_6783697263505703874[0] = 0;
   out_6783697263505703874[1] = 0;
   out_6783697263505703874[2] = 0;
   out_6783697263505703874[3] = 0;
   out_6783697263505703874[4] = 1;
   out_6783697263505703874[5] = 0;
   out_6783697263505703874[6] = 0;
   out_6783697263505703874[7] = 0;
   out_6783697263505703874[8] = 0;
}
void h_26(double *state, double *unused, double *out_4978851268883674033) {
   out_4978851268883674033[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7569890274759255848) {
   out_7569890274759255848[0] = 0;
   out_7569890274759255848[1] = 0;
   out_7569890274759255848[2] = 0;
   out_7569890274759255848[3] = 0;
   out_7569890274759255848[4] = 0;
   out_7569890274759255848[5] = 0;
   out_7569890274759255848[6] = 0;
   out_7569890274759255848[7] = 1;
   out_7569890274759255848[8] = 0;
}
void h_27(double *state, double *unused, double *out_5096858662817050777) {
   out_5096858662817050777[0] = state[3];
}
void H_27(double *state, double *unused, double *out_9007291334689647091) {
   out_9007291334689647091[0] = 0;
   out_9007291334689647091[1] = 0;
   out_9007291334689647091[2] = 0;
   out_9007291334689647091[3] = 1;
   out_9007291334689647091[4] = 0;
   out_9007291334689647091[5] = 0;
   out_9007291334689647091[6] = 0;
   out_9007291334689647091[7] = 0;
   out_9007291334689647091[8] = 0;
}
void h_29(double *state, double *unused, double *out_998555364537678913) {
   out_998555364537678913[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7293928607820096058) {
   out_7293928607820096058[0] = 0;
   out_7293928607820096058[1] = 1;
   out_7293928607820096058[2] = 0;
   out_7293928607820096058[3] = 0;
   out_7293928607820096058[4] = 0;
   out_7293928607820096058[5] = 0;
   out_7293928607820096058[6] = 0;
   out_7293928607820096058[7] = 0;
   out_7293928607820096058[8] = 0;
}
void h_28(double *state, double *unused, double *out_8372706475564507366) {
   out_8372706475564507366[0] = state[0];
}
void H_28(double *state, double *unused, double *out_9189185194324129307) {
   out_9189185194324129307[0] = 1;
   out_9189185194324129307[1] = 0;
   out_9189185194324129307[2] = 0;
   out_9189185194324129307[3] = 0;
   out_9189185194324129307[4] = 0;
   out_9189185194324129307[5] = 0;
   out_9189185194324129307[6] = 0;
   out_9189185194324129307[7] = 0;
   out_9189185194324129307[8] = 0;
}
void h_31(double *state, double *unused, double *out_180008667128300757) {
   out_180008667128300757[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6943682172525904372) {
   out_6943682172525904372[0] = 0;
   out_6943682172525904372[1] = 0;
   out_6943682172525904372[2] = 0;
   out_6943682172525904372[3] = 0;
   out_6943682172525904372[4] = 0;
   out_6943682172525904372[5] = 0;
   out_6943682172525904372[6] = 0;
   out_6943682172525904372[7] = 0;
   out_6943682172525904372[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_8558166113930061773) {
  err_fun(nom_x, delta_x, out_8558166113930061773);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2269670274683655268) {
  inv_err_fun(nom_x, true_x, out_2269670274683655268);
}
void car_H_mod_fun(double *state, double *out_6407701768448647232) {
  H_mod_fun(state, out_6407701768448647232);
}
void car_f_fun(double *state, double dt, double *out_648904423540471901) {
  f_fun(state,  dt, out_648904423540471901);
}
void car_F_fun(double *state, double dt, double *out_7503564954401744509) {
  F_fun(state,  dt, out_7503564954401744509);
}
void car_h_25(double *state, double *unused, double *out_7864801379551668384) {
  h_25(state, unused, out_7864801379551668384);
}
void car_H_25(double *state, double *unused, double *out_7135350480076239544) {
  H_25(state, unused, out_7135350480076239544);
}
void car_h_24(double *state, double *unused, double *out_7538847613518647590) {
  h_24(state, unused, out_7538847613518647590);
}
void car_H_24(double *state, double *unused, double *out_3868719000644595752) {
  H_24(state, unused, out_3868719000644595752);
}
void car_h_30(double *state, double *unused, double *out_8021988047902797529) {
  h_30(state, unused, out_8021988047902797529);
}
void car_H_30(double *state, double *unused, double *out_6783697263505703874) {
  H_30(state, unused, out_6783697263505703874);
}
void car_h_26(double *state, double *unused, double *out_4978851268883674033) {
  h_26(state, unused, out_4978851268883674033);
}
void car_H_26(double *state, double *unused, double *out_7569890274759255848) {
  H_26(state, unused, out_7569890274759255848);
}
void car_h_27(double *state, double *unused, double *out_5096858662817050777) {
  h_27(state, unused, out_5096858662817050777);
}
void car_H_27(double *state, double *unused, double *out_9007291334689647091) {
  H_27(state, unused, out_9007291334689647091);
}
void car_h_29(double *state, double *unused, double *out_998555364537678913) {
  h_29(state, unused, out_998555364537678913);
}
void car_H_29(double *state, double *unused, double *out_7293928607820096058) {
  H_29(state, unused, out_7293928607820096058);
}
void car_h_28(double *state, double *unused, double *out_8372706475564507366) {
  h_28(state, unused, out_8372706475564507366);
}
void car_H_28(double *state, double *unused, double *out_9189185194324129307) {
  H_28(state, unused, out_9189185194324129307);
}
void car_h_31(double *state, double *unused, double *out_180008667128300757) {
  h_31(state, unused, out_180008667128300757);
}
void car_H_31(double *state, double *unused, double *out_6943682172525904372) {
  H_31(state, unused, out_6943682172525904372);
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
