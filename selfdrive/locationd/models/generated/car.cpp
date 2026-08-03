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
void err_fun(double *nom_x, double *delta_x, double *out_1506475022093702388) {
   out_1506475022093702388[0] = delta_x[0] + nom_x[0];
   out_1506475022093702388[1] = delta_x[1] + nom_x[1];
   out_1506475022093702388[2] = delta_x[2] + nom_x[2];
   out_1506475022093702388[3] = delta_x[3] + nom_x[3];
   out_1506475022093702388[4] = delta_x[4] + nom_x[4];
   out_1506475022093702388[5] = delta_x[5] + nom_x[5];
   out_1506475022093702388[6] = delta_x[6] + nom_x[6];
   out_1506475022093702388[7] = delta_x[7] + nom_x[7];
   out_1506475022093702388[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_9143363731815594717) {
   out_9143363731815594717[0] = -nom_x[0] + true_x[0];
   out_9143363731815594717[1] = -nom_x[1] + true_x[1];
   out_9143363731815594717[2] = -nom_x[2] + true_x[2];
   out_9143363731815594717[3] = -nom_x[3] + true_x[3];
   out_9143363731815594717[4] = -nom_x[4] + true_x[4];
   out_9143363731815594717[5] = -nom_x[5] + true_x[5];
   out_9143363731815594717[6] = -nom_x[6] + true_x[6];
   out_9143363731815594717[7] = -nom_x[7] + true_x[7];
   out_9143363731815594717[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_9131407703981301731) {
   out_9131407703981301731[0] = 1.0;
   out_9131407703981301731[1] = 0.0;
   out_9131407703981301731[2] = 0.0;
   out_9131407703981301731[3] = 0.0;
   out_9131407703981301731[4] = 0.0;
   out_9131407703981301731[5] = 0.0;
   out_9131407703981301731[6] = 0.0;
   out_9131407703981301731[7] = 0.0;
   out_9131407703981301731[8] = 0.0;
   out_9131407703981301731[9] = 0.0;
   out_9131407703981301731[10] = 1.0;
   out_9131407703981301731[11] = 0.0;
   out_9131407703981301731[12] = 0.0;
   out_9131407703981301731[13] = 0.0;
   out_9131407703981301731[14] = 0.0;
   out_9131407703981301731[15] = 0.0;
   out_9131407703981301731[16] = 0.0;
   out_9131407703981301731[17] = 0.0;
   out_9131407703981301731[18] = 0.0;
   out_9131407703981301731[19] = 0.0;
   out_9131407703981301731[20] = 1.0;
   out_9131407703981301731[21] = 0.0;
   out_9131407703981301731[22] = 0.0;
   out_9131407703981301731[23] = 0.0;
   out_9131407703981301731[24] = 0.0;
   out_9131407703981301731[25] = 0.0;
   out_9131407703981301731[26] = 0.0;
   out_9131407703981301731[27] = 0.0;
   out_9131407703981301731[28] = 0.0;
   out_9131407703981301731[29] = 0.0;
   out_9131407703981301731[30] = 1.0;
   out_9131407703981301731[31] = 0.0;
   out_9131407703981301731[32] = 0.0;
   out_9131407703981301731[33] = 0.0;
   out_9131407703981301731[34] = 0.0;
   out_9131407703981301731[35] = 0.0;
   out_9131407703981301731[36] = 0.0;
   out_9131407703981301731[37] = 0.0;
   out_9131407703981301731[38] = 0.0;
   out_9131407703981301731[39] = 0.0;
   out_9131407703981301731[40] = 1.0;
   out_9131407703981301731[41] = 0.0;
   out_9131407703981301731[42] = 0.0;
   out_9131407703981301731[43] = 0.0;
   out_9131407703981301731[44] = 0.0;
   out_9131407703981301731[45] = 0.0;
   out_9131407703981301731[46] = 0.0;
   out_9131407703981301731[47] = 0.0;
   out_9131407703981301731[48] = 0.0;
   out_9131407703981301731[49] = 0.0;
   out_9131407703981301731[50] = 1.0;
   out_9131407703981301731[51] = 0.0;
   out_9131407703981301731[52] = 0.0;
   out_9131407703981301731[53] = 0.0;
   out_9131407703981301731[54] = 0.0;
   out_9131407703981301731[55] = 0.0;
   out_9131407703981301731[56] = 0.0;
   out_9131407703981301731[57] = 0.0;
   out_9131407703981301731[58] = 0.0;
   out_9131407703981301731[59] = 0.0;
   out_9131407703981301731[60] = 1.0;
   out_9131407703981301731[61] = 0.0;
   out_9131407703981301731[62] = 0.0;
   out_9131407703981301731[63] = 0.0;
   out_9131407703981301731[64] = 0.0;
   out_9131407703981301731[65] = 0.0;
   out_9131407703981301731[66] = 0.0;
   out_9131407703981301731[67] = 0.0;
   out_9131407703981301731[68] = 0.0;
   out_9131407703981301731[69] = 0.0;
   out_9131407703981301731[70] = 1.0;
   out_9131407703981301731[71] = 0.0;
   out_9131407703981301731[72] = 0.0;
   out_9131407703981301731[73] = 0.0;
   out_9131407703981301731[74] = 0.0;
   out_9131407703981301731[75] = 0.0;
   out_9131407703981301731[76] = 0.0;
   out_9131407703981301731[77] = 0.0;
   out_9131407703981301731[78] = 0.0;
   out_9131407703981301731[79] = 0.0;
   out_9131407703981301731[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_384729614673600146) {
   out_384729614673600146[0] = state[0];
   out_384729614673600146[1] = state[1];
   out_384729614673600146[2] = state[2];
   out_384729614673600146[3] = state[3];
   out_384729614673600146[4] = state[4];
   out_384729614673600146[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_384729614673600146[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_384729614673600146[7] = state[7];
   out_384729614673600146[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7440730494263305444) {
   out_7440730494263305444[0] = 1;
   out_7440730494263305444[1] = 0;
   out_7440730494263305444[2] = 0;
   out_7440730494263305444[3] = 0;
   out_7440730494263305444[4] = 0;
   out_7440730494263305444[5] = 0;
   out_7440730494263305444[6] = 0;
   out_7440730494263305444[7] = 0;
   out_7440730494263305444[8] = 0;
   out_7440730494263305444[9] = 0;
   out_7440730494263305444[10] = 1;
   out_7440730494263305444[11] = 0;
   out_7440730494263305444[12] = 0;
   out_7440730494263305444[13] = 0;
   out_7440730494263305444[14] = 0;
   out_7440730494263305444[15] = 0;
   out_7440730494263305444[16] = 0;
   out_7440730494263305444[17] = 0;
   out_7440730494263305444[18] = 0;
   out_7440730494263305444[19] = 0;
   out_7440730494263305444[20] = 1;
   out_7440730494263305444[21] = 0;
   out_7440730494263305444[22] = 0;
   out_7440730494263305444[23] = 0;
   out_7440730494263305444[24] = 0;
   out_7440730494263305444[25] = 0;
   out_7440730494263305444[26] = 0;
   out_7440730494263305444[27] = 0;
   out_7440730494263305444[28] = 0;
   out_7440730494263305444[29] = 0;
   out_7440730494263305444[30] = 1;
   out_7440730494263305444[31] = 0;
   out_7440730494263305444[32] = 0;
   out_7440730494263305444[33] = 0;
   out_7440730494263305444[34] = 0;
   out_7440730494263305444[35] = 0;
   out_7440730494263305444[36] = 0;
   out_7440730494263305444[37] = 0;
   out_7440730494263305444[38] = 0;
   out_7440730494263305444[39] = 0;
   out_7440730494263305444[40] = 1;
   out_7440730494263305444[41] = 0;
   out_7440730494263305444[42] = 0;
   out_7440730494263305444[43] = 0;
   out_7440730494263305444[44] = 0;
   out_7440730494263305444[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7440730494263305444[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7440730494263305444[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7440730494263305444[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7440730494263305444[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7440730494263305444[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7440730494263305444[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7440730494263305444[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7440730494263305444[53] = -9.8100000000000005*dt;
   out_7440730494263305444[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7440730494263305444[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7440730494263305444[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7440730494263305444[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7440730494263305444[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7440730494263305444[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7440730494263305444[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7440730494263305444[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7440730494263305444[62] = 0;
   out_7440730494263305444[63] = 0;
   out_7440730494263305444[64] = 0;
   out_7440730494263305444[65] = 0;
   out_7440730494263305444[66] = 0;
   out_7440730494263305444[67] = 0;
   out_7440730494263305444[68] = 0;
   out_7440730494263305444[69] = 0;
   out_7440730494263305444[70] = 1;
   out_7440730494263305444[71] = 0;
   out_7440730494263305444[72] = 0;
   out_7440730494263305444[73] = 0;
   out_7440730494263305444[74] = 0;
   out_7440730494263305444[75] = 0;
   out_7440730494263305444[76] = 0;
   out_7440730494263305444[77] = 0;
   out_7440730494263305444[78] = 0;
   out_7440730494263305444[79] = 0;
   out_7440730494263305444[80] = 1;
}
void h_25(double *state, double *unused, double *out_4252950562849966829) {
   out_4252950562849966829[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6221318096935853377) {
   out_6221318096935853377[0] = 0;
   out_6221318096935853377[1] = 0;
   out_6221318096935853377[2] = 0;
   out_6221318096935853377[3] = 0;
   out_6221318096935853377[4] = 0;
   out_6221318096935853377[5] = 0;
   out_6221318096935853377[6] = 1;
   out_6221318096935853377[7] = 0;
   out_6221318096935853377[8] = 0;
}
void h_24(double *state, double *unused, double *out_3680087672280189791) {
   out_3680087672280189791[0] = state[4];
   out_3680087672280189791[1] = state[5];
}
void H_24(double *state, double *unused, double *out_9166284664138259719) {
   out_9166284664138259719[0] = 0;
   out_9166284664138259719[1] = 0;
   out_9166284664138259719[2] = 0;
   out_9166284664138259719[3] = 0;
   out_9166284664138259719[4] = 1;
   out_9166284664138259719[5] = 0;
   out_9166284664138259719[6] = 0;
   out_9166284664138259719[7] = 0;
   out_9166284664138259719[8] = 0;
   out_9166284664138259719[9] = 0;
   out_9166284664138259719[10] = 0;
   out_9166284664138259719[11] = 0;
   out_9166284664138259719[12] = 0;
   out_9166284664138259719[13] = 0;
   out_9166284664138259719[14] = 1;
   out_9166284664138259719[15] = 0;
   out_9166284664138259719[16] = 0;
   out_9166284664138259719[17] = 0;
}
void h_30(double *state, double *unused, double *out_7996626645345091737) {
   out_7996626645345091737[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7697729646646090041) {
   out_7697729646646090041[0] = 0;
   out_7697729646646090041[1] = 0;
   out_7697729646646090041[2] = 0;
   out_7697729646646090041[3] = 0;
   out_7697729646646090041[4] = 1;
   out_7697729646646090041[5] = 0;
   out_7697729646646090041[6] = 0;
   out_7697729646646090041[7] = 0;
   out_7697729646646090041[8] = 0;
}
void h_26(double *state, double *unused, double *out_3034246647663798505) {
   out_3034246647663798505[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8483922657899642015) {
   out_8483922657899642015[0] = 0;
   out_8483922657899642015[1] = 0;
   out_8483922657899642015[2] = 0;
   out_8483922657899642015[3] = 0;
   out_8483922657899642015[4] = 0;
   out_8483922657899642015[5] = 0;
   out_8483922657899642015[6] = 0;
   out_8483922657899642015[7] = 1;
   out_8483922657899642015[8] = 0;
}
void h_27(double *state, double *unused, double *out_3649634678173489312) {
   out_3649634678173489312[0] = state[3];
}
void H_27(double *state, double *unused, double *out_5522966334845665130) {
   out_5522966334845665130[0] = 0;
   out_5522966334845665130[1] = 0;
   out_5522966334845665130[2] = 0;
   out_5522966334845665130[3] = 1;
   out_5522966334845665130[4] = 0;
   out_5522966334845665130[5] = 0;
   out_5522966334845665130[6] = 0;
   out_5522966334845665130[7] = 0;
   out_5522966334845665130[8] = 0;
}
void h_29(double *state, double *unused, double *out_3374440615888983423) {
   out_3374440615888983423[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8207960990960482225) {
   out_8207960990960482225[0] = 0;
   out_8207960990960482225[1] = 1;
   out_8207960990960482225[2] = 0;
   out_8207960990960482225[3] = 0;
   out_8207960990960482225[4] = 0;
   out_8207960990960482225[5] = 0;
   out_8207960990960482225[6] = 0;
   out_8207960990960482225[7] = 0;
   out_8207960990960482225[8] = 0;
}
void h_28(double *state, double *unused, double *out_1352038589487356333) {
   out_1352038589487356333[0] = state[0];
}
void H_28(double *state, double *unused, double *out_3125561973890951651) {
   out_3125561973890951651[0] = 1;
   out_3125561973890951651[1] = 0;
   out_3125561973890951651[2] = 0;
   out_3125561973890951651[3] = 0;
   out_3125561973890951651[4] = 0;
   out_3125561973890951651[5] = 0;
   out_3125561973890951651[6] = 0;
   out_3125561973890951651[7] = 0;
   out_3125561973890951651[8] = 0;
}
void h_31(double *state, double *unused, double *out_8114634039278468481) {
   out_8114634039278468481[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7857714555666290539) {
   out_7857714555666290539[0] = 0;
   out_7857714555666290539[1] = 0;
   out_7857714555666290539[2] = 0;
   out_7857714555666290539[3] = 0;
   out_7857714555666290539[4] = 0;
   out_7857714555666290539[5] = 0;
   out_7857714555666290539[6] = 0;
   out_7857714555666290539[7] = 0;
   out_7857714555666290539[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_1506475022093702388) {
  err_fun(nom_x, delta_x, out_1506475022093702388);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_9143363731815594717) {
  inv_err_fun(nom_x, true_x, out_9143363731815594717);
}
void car_H_mod_fun(double *state, double *out_9131407703981301731) {
  H_mod_fun(state, out_9131407703981301731);
}
void car_f_fun(double *state, double dt, double *out_384729614673600146) {
  f_fun(state,  dt, out_384729614673600146);
}
void car_F_fun(double *state, double dt, double *out_7440730494263305444) {
  F_fun(state,  dt, out_7440730494263305444);
}
void car_h_25(double *state, double *unused, double *out_4252950562849966829) {
  h_25(state, unused, out_4252950562849966829);
}
void car_H_25(double *state, double *unused, double *out_6221318096935853377) {
  H_25(state, unused, out_6221318096935853377);
}
void car_h_24(double *state, double *unused, double *out_3680087672280189791) {
  h_24(state, unused, out_3680087672280189791);
}
void car_H_24(double *state, double *unused, double *out_9166284664138259719) {
  H_24(state, unused, out_9166284664138259719);
}
void car_h_30(double *state, double *unused, double *out_7996626645345091737) {
  h_30(state, unused, out_7996626645345091737);
}
void car_H_30(double *state, double *unused, double *out_7697729646646090041) {
  H_30(state, unused, out_7697729646646090041);
}
void car_h_26(double *state, double *unused, double *out_3034246647663798505) {
  h_26(state, unused, out_3034246647663798505);
}
void car_H_26(double *state, double *unused, double *out_8483922657899642015) {
  H_26(state, unused, out_8483922657899642015);
}
void car_h_27(double *state, double *unused, double *out_3649634678173489312) {
  h_27(state, unused, out_3649634678173489312);
}
void car_H_27(double *state, double *unused, double *out_5522966334845665130) {
  H_27(state, unused, out_5522966334845665130);
}
void car_h_29(double *state, double *unused, double *out_3374440615888983423) {
  h_29(state, unused, out_3374440615888983423);
}
void car_H_29(double *state, double *unused, double *out_8207960990960482225) {
  H_29(state, unused, out_8207960990960482225);
}
void car_h_28(double *state, double *unused, double *out_1352038589487356333) {
  h_28(state, unused, out_1352038589487356333);
}
void car_H_28(double *state, double *unused, double *out_3125561973890951651) {
  H_28(state, unused, out_3125561973890951651);
}
void car_h_31(double *state, double *unused, double *out_8114634039278468481) {
  h_31(state, unused, out_8114634039278468481);
}
void car_H_31(double *state, double *unused, double *out_7857714555666290539) {
  H_31(state, unused, out_7857714555666290539);
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
