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
void err_fun(double *nom_x, double *delta_x, double *out_5325374827696631328) {
   out_5325374827696631328[0] = delta_x[0] + nom_x[0];
   out_5325374827696631328[1] = delta_x[1] + nom_x[1];
   out_5325374827696631328[2] = delta_x[2] + nom_x[2];
   out_5325374827696631328[3] = delta_x[3] + nom_x[3];
   out_5325374827696631328[4] = delta_x[4] + nom_x[4];
   out_5325374827696631328[5] = delta_x[5] + nom_x[5];
   out_5325374827696631328[6] = delta_x[6] + nom_x[6];
   out_5325374827696631328[7] = delta_x[7] + nom_x[7];
   out_5325374827696631328[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_263695042767338590) {
   out_263695042767338590[0] = -nom_x[0] + true_x[0];
   out_263695042767338590[1] = -nom_x[1] + true_x[1];
   out_263695042767338590[2] = -nom_x[2] + true_x[2];
   out_263695042767338590[3] = -nom_x[3] + true_x[3];
   out_263695042767338590[4] = -nom_x[4] + true_x[4];
   out_263695042767338590[5] = -nom_x[5] + true_x[5];
   out_263695042767338590[6] = -nom_x[6] + true_x[6];
   out_263695042767338590[7] = -nom_x[7] + true_x[7];
   out_263695042767338590[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2663737869404174494) {
   out_2663737869404174494[0] = 1.0;
   out_2663737869404174494[1] = 0.0;
   out_2663737869404174494[2] = 0.0;
   out_2663737869404174494[3] = 0.0;
   out_2663737869404174494[4] = 0.0;
   out_2663737869404174494[5] = 0.0;
   out_2663737869404174494[6] = 0.0;
   out_2663737869404174494[7] = 0.0;
   out_2663737869404174494[8] = 0.0;
   out_2663737869404174494[9] = 0.0;
   out_2663737869404174494[10] = 1.0;
   out_2663737869404174494[11] = 0.0;
   out_2663737869404174494[12] = 0.0;
   out_2663737869404174494[13] = 0.0;
   out_2663737869404174494[14] = 0.0;
   out_2663737869404174494[15] = 0.0;
   out_2663737869404174494[16] = 0.0;
   out_2663737869404174494[17] = 0.0;
   out_2663737869404174494[18] = 0.0;
   out_2663737869404174494[19] = 0.0;
   out_2663737869404174494[20] = 1.0;
   out_2663737869404174494[21] = 0.0;
   out_2663737869404174494[22] = 0.0;
   out_2663737869404174494[23] = 0.0;
   out_2663737869404174494[24] = 0.0;
   out_2663737869404174494[25] = 0.0;
   out_2663737869404174494[26] = 0.0;
   out_2663737869404174494[27] = 0.0;
   out_2663737869404174494[28] = 0.0;
   out_2663737869404174494[29] = 0.0;
   out_2663737869404174494[30] = 1.0;
   out_2663737869404174494[31] = 0.0;
   out_2663737869404174494[32] = 0.0;
   out_2663737869404174494[33] = 0.0;
   out_2663737869404174494[34] = 0.0;
   out_2663737869404174494[35] = 0.0;
   out_2663737869404174494[36] = 0.0;
   out_2663737869404174494[37] = 0.0;
   out_2663737869404174494[38] = 0.0;
   out_2663737869404174494[39] = 0.0;
   out_2663737869404174494[40] = 1.0;
   out_2663737869404174494[41] = 0.0;
   out_2663737869404174494[42] = 0.0;
   out_2663737869404174494[43] = 0.0;
   out_2663737869404174494[44] = 0.0;
   out_2663737869404174494[45] = 0.0;
   out_2663737869404174494[46] = 0.0;
   out_2663737869404174494[47] = 0.0;
   out_2663737869404174494[48] = 0.0;
   out_2663737869404174494[49] = 0.0;
   out_2663737869404174494[50] = 1.0;
   out_2663737869404174494[51] = 0.0;
   out_2663737869404174494[52] = 0.0;
   out_2663737869404174494[53] = 0.0;
   out_2663737869404174494[54] = 0.0;
   out_2663737869404174494[55] = 0.0;
   out_2663737869404174494[56] = 0.0;
   out_2663737869404174494[57] = 0.0;
   out_2663737869404174494[58] = 0.0;
   out_2663737869404174494[59] = 0.0;
   out_2663737869404174494[60] = 1.0;
   out_2663737869404174494[61] = 0.0;
   out_2663737869404174494[62] = 0.0;
   out_2663737869404174494[63] = 0.0;
   out_2663737869404174494[64] = 0.0;
   out_2663737869404174494[65] = 0.0;
   out_2663737869404174494[66] = 0.0;
   out_2663737869404174494[67] = 0.0;
   out_2663737869404174494[68] = 0.0;
   out_2663737869404174494[69] = 0.0;
   out_2663737869404174494[70] = 1.0;
   out_2663737869404174494[71] = 0.0;
   out_2663737869404174494[72] = 0.0;
   out_2663737869404174494[73] = 0.0;
   out_2663737869404174494[74] = 0.0;
   out_2663737869404174494[75] = 0.0;
   out_2663737869404174494[76] = 0.0;
   out_2663737869404174494[77] = 0.0;
   out_2663737869404174494[78] = 0.0;
   out_2663737869404174494[79] = 0.0;
   out_2663737869404174494[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8230420991833863893) {
   out_8230420991833863893[0] = state[0];
   out_8230420991833863893[1] = state[1];
   out_8230420991833863893[2] = state[2];
   out_8230420991833863893[3] = state[3];
   out_8230420991833863893[4] = state[4];
   out_8230420991833863893[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8230420991833863893[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8230420991833863893[7] = state[7];
   out_8230420991833863893[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2756618938696411588) {
   out_2756618938696411588[0] = 1;
   out_2756618938696411588[1] = 0;
   out_2756618938696411588[2] = 0;
   out_2756618938696411588[3] = 0;
   out_2756618938696411588[4] = 0;
   out_2756618938696411588[5] = 0;
   out_2756618938696411588[6] = 0;
   out_2756618938696411588[7] = 0;
   out_2756618938696411588[8] = 0;
   out_2756618938696411588[9] = 0;
   out_2756618938696411588[10] = 1;
   out_2756618938696411588[11] = 0;
   out_2756618938696411588[12] = 0;
   out_2756618938696411588[13] = 0;
   out_2756618938696411588[14] = 0;
   out_2756618938696411588[15] = 0;
   out_2756618938696411588[16] = 0;
   out_2756618938696411588[17] = 0;
   out_2756618938696411588[18] = 0;
   out_2756618938696411588[19] = 0;
   out_2756618938696411588[20] = 1;
   out_2756618938696411588[21] = 0;
   out_2756618938696411588[22] = 0;
   out_2756618938696411588[23] = 0;
   out_2756618938696411588[24] = 0;
   out_2756618938696411588[25] = 0;
   out_2756618938696411588[26] = 0;
   out_2756618938696411588[27] = 0;
   out_2756618938696411588[28] = 0;
   out_2756618938696411588[29] = 0;
   out_2756618938696411588[30] = 1;
   out_2756618938696411588[31] = 0;
   out_2756618938696411588[32] = 0;
   out_2756618938696411588[33] = 0;
   out_2756618938696411588[34] = 0;
   out_2756618938696411588[35] = 0;
   out_2756618938696411588[36] = 0;
   out_2756618938696411588[37] = 0;
   out_2756618938696411588[38] = 0;
   out_2756618938696411588[39] = 0;
   out_2756618938696411588[40] = 1;
   out_2756618938696411588[41] = 0;
   out_2756618938696411588[42] = 0;
   out_2756618938696411588[43] = 0;
   out_2756618938696411588[44] = 0;
   out_2756618938696411588[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2756618938696411588[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2756618938696411588[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2756618938696411588[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2756618938696411588[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2756618938696411588[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2756618938696411588[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2756618938696411588[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2756618938696411588[53] = -9.8100000000000005*dt;
   out_2756618938696411588[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2756618938696411588[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2756618938696411588[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2756618938696411588[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2756618938696411588[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2756618938696411588[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2756618938696411588[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2756618938696411588[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2756618938696411588[62] = 0;
   out_2756618938696411588[63] = 0;
   out_2756618938696411588[64] = 0;
   out_2756618938696411588[65] = 0;
   out_2756618938696411588[66] = 0;
   out_2756618938696411588[67] = 0;
   out_2756618938696411588[68] = 0;
   out_2756618938696411588[69] = 0;
   out_2756618938696411588[70] = 1;
   out_2756618938696411588[71] = 0;
   out_2756618938696411588[72] = 0;
   out_2756618938696411588[73] = 0;
   out_2756618938696411588[74] = 0;
   out_2756618938696411588[75] = 0;
   out_2756618938696411588[76] = 0;
   out_2756618938696411588[77] = 0;
   out_2756618938696411588[78] = 0;
   out_2756618938696411588[79] = 0;
   out_2756618938696411588[80] = 1;
}
void h_25(double *state, double *unused, double *out_2585399580963523364) {
   out_2585399580963523364[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4993569966627829866) {
   out_4993569966627829866[0] = 0;
   out_4993569966627829866[1] = 0;
   out_4993569966627829866[2] = 0;
   out_4993569966627829866[3] = 0;
   out_4993569966627829866[4] = 0;
   out_4993569966627829866[5] = 0;
   out_4993569966627829866[6] = 1;
   out_4993569966627829866[7] = 0;
   out_4993569966627829866[8] = 0;
}
void h_24(double *state, double *unused, double *out_7866369606921911129) {
   out_7866369606921911129[0] = state[4];
   out_7866369606921911129[1] = state[5];
}
void H_24(double *state, double *unused, double *out_124755101600123014) {
   out_124755101600123014[0] = 0;
   out_124755101600123014[1] = 0;
   out_124755101600123014[2] = 0;
   out_124755101600123014[3] = 0;
   out_124755101600123014[4] = 1;
   out_124755101600123014[5] = 0;
   out_124755101600123014[6] = 0;
   out_124755101600123014[7] = 0;
   out_124755101600123014[8] = 0;
   out_124755101600123014[9] = 0;
   out_124755101600123014[10] = 0;
   out_124755101600123014[11] = 0;
   out_124755101600123014[12] = 0;
   out_124755101600123014[13] = 0;
   out_124755101600123014[14] = 1;
   out_124755101600123014[15] = 0;
   out_124755101600123014[16] = 0;
   out_124755101600123014[17] = 0;
}
void h_30(double *state, double *unused, double *out_1052049947290498986) {
   out_1052049947290498986[0] = state[4];
}
void H_30(double *state, double *unused, double *out_465873636500221668) {
   out_465873636500221668[0] = 0;
   out_465873636500221668[1] = 0;
   out_465873636500221668[2] = 0;
   out_465873636500221668[3] = 0;
   out_465873636500221668[4] = 1;
   out_465873636500221668[5] = 0;
   out_465873636500221668[6] = 0;
   out_465873636500221668[7] = 0;
   out_465873636500221668[8] = 0;
}
void h_26(double *state, double *unused, double *out_3137755351529974294) {
   out_3137755351529974294[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1252066647753773642) {
   out_1252066647753773642[0] = 0;
   out_1252066647753773642[1] = 0;
   out_1252066647753773642[2] = 0;
   out_1252066647753773642[3] = 0;
   out_1252066647753773642[4] = 0;
   out_1252066647753773642[5] = 0;
   out_1252066647753773642[6] = 0;
   out_1252066647753773642[7] = 1;
   out_1252066647753773642[8] = 0;
}
void h_27(double *state, double *unused, double *out_3292885906595191724) {
   out_3292885906595191724[0] = state[3];
}
void H_27(double *state, double *unused, double *out_2689467707684164885) {
   out_2689467707684164885[0] = 0;
   out_2689467707684164885[1] = 0;
   out_2689467707684164885[2] = 0;
   out_2689467707684164885[3] = 1;
   out_2689467707684164885[4] = 0;
   out_2689467707684164885[5] = 0;
   out_2689467707684164885[6] = 0;
   out_2689467707684164885[7] = 0;
   out_2689467707684164885[8] = 0;
}
void h_29(double *state, double *unused, double *out_5346991570123350160) {
   out_5346991570123350160[0] = state[1];
}
void H_29(double *state, double *unused, double *out_976104980814613852) {
   out_976104980814613852[0] = 0;
   out_976104980814613852[1] = 1;
   out_976104980814613852[2] = 0;
   out_976104980814613852[3] = 0;
   out_976104980814613852[4] = 0;
   out_976104980814613852[5] = 0;
   out_976104980814613852[6] = 0;
   out_976104980814613852[7] = 0;
   out_976104980814613852[8] = 0;
}
void h_28(double *state, double *unused, double *out_6565695485309518484) {
   out_6565695485309518484[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2939735252379940103) {
   out_2939735252379940103[0] = 1;
   out_2939735252379940103[1] = 0;
   out_2939735252379940103[2] = 0;
   out_2939735252379940103[3] = 0;
   out_2939735252379940103[4] = 0;
   out_2939735252379940103[5] = 0;
   out_2939735252379940103[6] = 0;
   out_2939735252379940103[7] = 0;
   out_2939735252379940103[8] = 0;
}
void h_31(double *state, double *unused, double *out_7496068987004855670) {
   out_7496068987004855670[0] = state[8];
}
void H_31(double *state, double *unused, double *out_625858545520422166) {
   out_625858545520422166[0] = 0;
   out_625858545520422166[1] = 0;
   out_625858545520422166[2] = 0;
   out_625858545520422166[3] = 0;
   out_625858545520422166[4] = 0;
   out_625858545520422166[5] = 0;
   out_625858545520422166[6] = 0;
   out_625858545520422166[7] = 0;
   out_625858545520422166[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_5325374827696631328) {
  err_fun(nom_x, delta_x, out_5325374827696631328);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_263695042767338590) {
  inv_err_fun(nom_x, true_x, out_263695042767338590);
}
void car_H_mod_fun(double *state, double *out_2663737869404174494) {
  H_mod_fun(state, out_2663737869404174494);
}
void car_f_fun(double *state, double dt, double *out_8230420991833863893) {
  f_fun(state,  dt, out_8230420991833863893);
}
void car_F_fun(double *state, double dt, double *out_2756618938696411588) {
  F_fun(state,  dt, out_2756618938696411588);
}
void car_h_25(double *state, double *unused, double *out_2585399580963523364) {
  h_25(state, unused, out_2585399580963523364);
}
void car_H_25(double *state, double *unused, double *out_4993569966627829866) {
  H_25(state, unused, out_4993569966627829866);
}
void car_h_24(double *state, double *unused, double *out_7866369606921911129) {
  h_24(state, unused, out_7866369606921911129);
}
void car_H_24(double *state, double *unused, double *out_124755101600123014) {
  H_24(state, unused, out_124755101600123014);
}
void car_h_30(double *state, double *unused, double *out_1052049947290498986) {
  h_30(state, unused, out_1052049947290498986);
}
void car_H_30(double *state, double *unused, double *out_465873636500221668) {
  H_30(state, unused, out_465873636500221668);
}
void car_h_26(double *state, double *unused, double *out_3137755351529974294) {
  h_26(state, unused, out_3137755351529974294);
}
void car_H_26(double *state, double *unused, double *out_1252066647753773642) {
  H_26(state, unused, out_1252066647753773642);
}
void car_h_27(double *state, double *unused, double *out_3292885906595191724) {
  h_27(state, unused, out_3292885906595191724);
}
void car_H_27(double *state, double *unused, double *out_2689467707684164885) {
  H_27(state, unused, out_2689467707684164885);
}
void car_h_29(double *state, double *unused, double *out_5346991570123350160) {
  h_29(state, unused, out_5346991570123350160);
}
void car_H_29(double *state, double *unused, double *out_976104980814613852) {
  H_29(state, unused, out_976104980814613852);
}
void car_h_28(double *state, double *unused, double *out_6565695485309518484) {
  h_28(state, unused, out_6565695485309518484);
}
void car_H_28(double *state, double *unused, double *out_2939735252379940103) {
  H_28(state, unused, out_2939735252379940103);
}
void car_h_31(double *state, double *unused, double *out_7496068987004855670) {
  h_31(state, unused, out_7496068987004855670);
}
void car_H_31(double *state, double *unused, double *out_625858545520422166) {
  H_31(state, unused, out_625858545520422166);
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
