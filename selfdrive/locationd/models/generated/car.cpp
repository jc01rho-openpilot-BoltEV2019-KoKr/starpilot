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
void err_fun(double *nom_x, double *delta_x, double *out_4189395199092511703) {
   out_4189395199092511703[0] = delta_x[0] + nom_x[0];
   out_4189395199092511703[1] = delta_x[1] + nom_x[1];
   out_4189395199092511703[2] = delta_x[2] + nom_x[2];
   out_4189395199092511703[3] = delta_x[3] + nom_x[3];
   out_4189395199092511703[4] = delta_x[4] + nom_x[4];
   out_4189395199092511703[5] = delta_x[5] + nom_x[5];
   out_4189395199092511703[6] = delta_x[6] + nom_x[6];
   out_4189395199092511703[7] = delta_x[7] + nom_x[7];
   out_4189395199092511703[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5755129993245429730) {
   out_5755129993245429730[0] = -nom_x[0] + true_x[0];
   out_5755129993245429730[1] = -nom_x[1] + true_x[1];
   out_5755129993245429730[2] = -nom_x[2] + true_x[2];
   out_5755129993245429730[3] = -nom_x[3] + true_x[3];
   out_5755129993245429730[4] = -nom_x[4] + true_x[4];
   out_5755129993245429730[5] = -nom_x[5] + true_x[5];
   out_5755129993245429730[6] = -nom_x[6] + true_x[6];
   out_5755129993245429730[7] = -nom_x[7] + true_x[7];
   out_5755129993245429730[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3130611196753066809) {
   out_3130611196753066809[0] = 1.0;
   out_3130611196753066809[1] = 0.0;
   out_3130611196753066809[2] = 0.0;
   out_3130611196753066809[3] = 0.0;
   out_3130611196753066809[4] = 0.0;
   out_3130611196753066809[5] = 0.0;
   out_3130611196753066809[6] = 0.0;
   out_3130611196753066809[7] = 0.0;
   out_3130611196753066809[8] = 0.0;
   out_3130611196753066809[9] = 0.0;
   out_3130611196753066809[10] = 1.0;
   out_3130611196753066809[11] = 0.0;
   out_3130611196753066809[12] = 0.0;
   out_3130611196753066809[13] = 0.0;
   out_3130611196753066809[14] = 0.0;
   out_3130611196753066809[15] = 0.0;
   out_3130611196753066809[16] = 0.0;
   out_3130611196753066809[17] = 0.0;
   out_3130611196753066809[18] = 0.0;
   out_3130611196753066809[19] = 0.0;
   out_3130611196753066809[20] = 1.0;
   out_3130611196753066809[21] = 0.0;
   out_3130611196753066809[22] = 0.0;
   out_3130611196753066809[23] = 0.0;
   out_3130611196753066809[24] = 0.0;
   out_3130611196753066809[25] = 0.0;
   out_3130611196753066809[26] = 0.0;
   out_3130611196753066809[27] = 0.0;
   out_3130611196753066809[28] = 0.0;
   out_3130611196753066809[29] = 0.0;
   out_3130611196753066809[30] = 1.0;
   out_3130611196753066809[31] = 0.0;
   out_3130611196753066809[32] = 0.0;
   out_3130611196753066809[33] = 0.0;
   out_3130611196753066809[34] = 0.0;
   out_3130611196753066809[35] = 0.0;
   out_3130611196753066809[36] = 0.0;
   out_3130611196753066809[37] = 0.0;
   out_3130611196753066809[38] = 0.0;
   out_3130611196753066809[39] = 0.0;
   out_3130611196753066809[40] = 1.0;
   out_3130611196753066809[41] = 0.0;
   out_3130611196753066809[42] = 0.0;
   out_3130611196753066809[43] = 0.0;
   out_3130611196753066809[44] = 0.0;
   out_3130611196753066809[45] = 0.0;
   out_3130611196753066809[46] = 0.0;
   out_3130611196753066809[47] = 0.0;
   out_3130611196753066809[48] = 0.0;
   out_3130611196753066809[49] = 0.0;
   out_3130611196753066809[50] = 1.0;
   out_3130611196753066809[51] = 0.0;
   out_3130611196753066809[52] = 0.0;
   out_3130611196753066809[53] = 0.0;
   out_3130611196753066809[54] = 0.0;
   out_3130611196753066809[55] = 0.0;
   out_3130611196753066809[56] = 0.0;
   out_3130611196753066809[57] = 0.0;
   out_3130611196753066809[58] = 0.0;
   out_3130611196753066809[59] = 0.0;
   out_3130611196753066809[60] = 1.0;
   out_3130611196753066809[61] = 0.0;
   out_3130611196753066809[62] = 0.0;
   out_3130611196753066809[63] = 0.0;
   out_3130611196753066809[64] = 0.0;
   out_3130611196753066809[65] = 0.0;
   out_3130611196753066809[66] = 0.0;
   out_3130611196753066809[67] = 0.0;
   out_3130611196753066809[68] = 0.0;
   out_3130611196753066809[69] = 0.0;
   out_3130611196753066809[70] = 1.0;
   out_3130611196753066809[71] = 0.0;
   out_3130611196753066809[72] = 0.0;
   out_3130611196753066809[73] = 0.0;
   out_3130611196753066809[74] = 0.0;
   out_3130611196753066809[75] = 0.0;
   out_3130611196753066809[76] = 0.0;
   out_3130611196753066809[77] = 0.0;
   out_3130611196753066809[78] = 0.0;
   out_3130611196753066809[79] = 0.0;
   out_3130611196753066809[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5961640813003379683) {
   out_5961640813003379683[0] = state[0];
   out_5961640813003379683[1] = state[1];
   out_5961640813003379683[2] = state[2];
   out_5961640813003379683[3] = state[3];
   out_5961640813003379683[4] = state[4];
   out_5961640813003379683[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5961640813003379683[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5961640813003379683[7] = state[7];
   out_5961640813003379683[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2654082016279909676) {
   out_2654082016279909676[0] = 1;
   out_2654082016279909676[1] = 0;
   out_2654082016279909676[2] = 0;
   out_2654082016279909676[3] = 0;
   out_2654082016279909676[4] = 0;
   out_2654082016279909676[5] = 0;
   out_2654082016279909676[6] = 0;
   out_2654082016279909676[7] = 0;
   out_2654082016279909676[8] = 0;
   out_2654082016279909676[9] = 0;
   out_2654082016279909676[10] = 1;
   out_2654082016279909676[11] = 0;
   out_2654082016279909676[12] = 0;
   out_2654082016279909676[13] = 0;
   out_2654082016279909676[14] = 0;
   out_2654082016279909676[15] = 0;
   out_2654082016279909676[16] = 0;
   out_2654082016279909676[17] = 0;
   out_2654082016279909676[18] = 0;
   out_2654082016279909676[19] = 0;
   out_2654082016279909676[20] = 1;
   out_2654082016279909676[21] = 0;
   out_2654082016279909676[22] = 0;
   out_2654082016279909676[23] = 0;
   out_2654082016279909676[24] = 0;
   out_2654082016279909676[25] = 0;
   out_2654082016279909676[26] = 0;
   out_2654082016279909676[27] = 0;
   out_2654082016279909676[28] = 0;
   out_2654082016279909676[29] = 0;
   out_2654082016279909676[30] = 1;
   out_2654082016279909676[31] = 0;
   out_2654082016279909676[32] = 0;
   out_2654082016279909676[33] = 0;
   out_2654082016279909676[34] = 0;
   out_2654082016279909676[35] = 0;
   out_2654082016279909676[36] = 0;
   out_2654082016279909676[37] = 0;
   out_2654082016279909676[38] = 0;
   out_2654082016279909676[39] = 0;
   out_2654082016279909676[40] = 1;
   out_2654082016279909676[41] = 0;
   out_2654082016279909676[42] = 0;
   out_2654082016279909676[43] = 0;
   out_2654082016279909676[44] = 0;
   out_2654082016279909676[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2654082016279909676[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2654082016279909676[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2654082016279909676[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2654082016279909676[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2654082016279909676[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2654082016279909676[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2654082016279909676[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2654082016279909676[53] = -9.8100000000000005*dt;
   out_2654082016279909676[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2654082016279909676[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2654082016279909676[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2654082016279909676[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2654082016279909676[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2654082016279909676[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2654082016279909676[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2654082016279909676[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2654082016279909676[62] = 0;
   out_2654082016279909676[63] = 0;
   out_2654082016279909676[64] = 0;
   out_2654082016279909676[65] = 0;
   out_2654082016279909676[66] = 0;
   out_2654082016279909676[67] = 0;
   out_2654082016279909676[68] = 0;
   out_2654082016279909676[69] = 0;
   out_2654082016279909676[70] = 1;
   out_2654082016279909676[71] = 0;
   out_2654082016279909676[72] = 0;
   out_2654082016279909676[73] = 0;
   out_2654082016279909676[74] = 0;
   out_2654082016279909676[75] = 0;
   out_2654082016279909676[76] = 0;
   out_2654082016279909676[77] = 0;
   out_2654082016279909676[78] = 0;
   out_2654082016279909676[79] = 0;
   out_2654082016279909676[80] = 1;
}
void h_25(double *state, double *unused, double *out_3340180793096633183) {
   out_3340180793096633183[0] = state[6];
}
void H_25(double *state, double *unused, double *out_4434950306945038429) {
   out_4434950306945038429[0] = 0;
   out_4434950306945038429[1] = 0;
   out_4434950306945038429[2] = 0;
   out_4434950306945038429[3] = 0;
   out_4434950306945038429[4] = 0;
   out_4434950306945038429[5] = 0;
   out_4434950306945038429[6] = 1;
   out_4434950306945038429[7] = 0;
   out_4434950306945038429[8] = 0;
}
void h_24(double *state, double *unused, double *out_7854800018825826791) {
   out_7854800018825826791[0] = state[4];
   out_7854800018825826791[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6607599905950537995) {
   out_6607599905950537995[0] = 0;
   out_6607599905950537995[1] = 0;
   out_6607599905950537995[2] = 0;
   out_6607599905950537995[3] = 0;
   out_6607599905950537995[4] = 1;
   out_6607599905950537995[5] = 0;
   out_6607599905950537995[6] = 0;
   out_6607599905950537995[7] = 0;
   out_6607599905950537995[8] = 0;
   out_6607599905950537995[9] = 0;
   out_6607599905950537995[10] = 0;
   out_6607599905950537995[11] = 0;
   out_6607599905950537995[12] = 0;
   out_6607599905950537995[13] = 0;
   out_6607599905950537995[14] = 1;
   out_6607599905950537995[15] = 0;
   out_6607599905950537995[16] = 0;
   out_6607599905950537995[17] = 0;
}
void h_30(double *state, double *unused, double *out_3104430337924860088) {
   out_3104430337924860088[0] = state[4];
}
void H_30(double *state, double *unused, double *out_1916617348437789802) {
   out_1916617348437789802[0] = 0;
   out_1916617348437789802[1] = 0;
   out_1916617348437789802[2] = 0;
   out_1916617348437789802[3] = 0;
   out_1916617348437789802[4] = 1;
   out_1916617348437789802[5] = 0;
   out_1916617348437789802[6] = 0;
   out_1916617348437789802[7] = 0;
   out_1916617348437789802[8] = 0;
}
void h_26(double *state, double *unused, double *out_4544914835386474254) {
   out_4544914835386474254[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8176453625819094653) {
   out_8176453625819094653[0] = 0;
   out_8176453625819094653[1] = 0;
   out_8176453625819094653[2] = 0;
   out_8176453625819094653[3] = 0;
   out_8176453625819094653[4] = 0;
   out_8176453625819094653[5] = 0;
   out_8176453625819094653[6] = 0;
   out_8176453625819094653[7] = 1;
   out_8176453625819094653[8] = 0;
}
void h_27(double *state, double *unused, double *out_4426907441453097510) {
   out_4426907441453097510[0] = state[3];
}
void H_27(double *state, double *unused, double *out_306976722746153415) {
   out_306976722746153415[0] = 0;
   out_306976722746153415[1] = 0;
   out_306976722746153415[2] = 0;
   out_306976722746153415[3] = 1;
   out_306976722746153415[4] = 0;
   out_306976722746153415[5] = 0;
   out_306976722746153415[6] = 0;
   out_306976722746153415[7] = 0;
   out_306976722746153415[8] = 0;
}
void h_29(double *state, double *unused, double *out_2160920485023197653) {
   out_2160920485023197653[0] = state[1];
}
void H_29(double *state, double *unused, double *out_1406386004123397618) {
   out_1406386004123397618[0] = 0;
   out_1406386004123397618[1] = 1;
   out_1406386004123397618[2] = 0;
   out_1406386004123397618[3] = 0;
   out_1406386004123397618[4] = 0;
   out_1406386004123397618[5] = 0;
   out_1406386004123397618[6] = 0;
   out_1406386004123397618[7] = 0;
   out_1406386004123397618[8] = 0;
}
void h_28(double *state, double *unused, double *out_7017073928463388327) {
   out_7017073928463388327[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6488785021192928192) {
   out_6488785021192928192[0] = 1;
   out_6488785021192928192[1] = 0;
   out_6488785021192928192[2] = 0;
   out_6488785021192928192[3] = 0;
   out_6488785021192928192[4] = 0;
   out_6488785021192928192[5] = 0;
   out_6488785021192928192[6] = 0;
   out_6488785021192928192[7] = 0;
   out_6488785021192928192[8] = 0;
}
void h_31(double *state, double *unused, double *out_5156479888167106809) {
   out_5156479888167106809[0] = state[8];
}
void H_31(double *state, double *unused, double *out_4404304345068078001) {
   out_4404304345068078001[0] = 0;
   out_4404304345068078001[1] = 0;
   out_4404304345068078001[2] = 0;
   out_4404304345068078001[3] = 0;
   out_4404304345068078001[4] = 0;
   out_4404304345068078001[5] = 0;
   out_4404304345068078001[6] = 0;
   out_4404304345068078001[7] = 0;
   out_4404304345068078001[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_4189395199092511703) {
  err_fun(nom_x, delta_x, out_4189395199092511703);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5755129993245429730) {
  inv_err_fun(nom_x, true_x, out_5755129993245429730);
}
void car_H_mod_fun(double *state, double *out_3130611196753066809) {
  H_mod_fun(state, out_3130611196753066809);
}
void car_f_fun(double *state, double dt, double *out_5961640813003379683) {
  f_fun(state,  dt, out_5961640813003379683);
}
void car_F_fun(double *state, double dt, double *out_2654082016279909676) {
  F_fun(state,  dt, out_2654082016279909676);
}
void car_h_25(double *state, double *unused, double *out_3340180793096633183) {
  h_25(state, unused, out_3340180793096633183);
}
void car_H_25(double *state, double *unused, double *out_4434950306945038429) {
  H_25(state, unused, out_4434950306945038429);
}
void car_h_24(double *state, double *unused, double *out_7854800018825826791) {
  h_24(state, unused, out_7854800018825826791);
}
void car_H_24(double *state, double *unused, double *out_6607599905950537995) {
  H_24(state, unused, out_6607599905950537995);
}
void car_h_30(double *state, double *unused, double *out_3104430337924860088) {
  h_30(state, unused, out_3104430337924860088);
}
void car_H_30(double *state, double *unused, double *out_1916617348437789802) {
  H_30(state, unused, out_1916617348437789802);
}
void car_h_26(double *state, double *unused, double *out_4544914835386474254) {
  h_26(state, unused, out_4544914835386474254);
}
void car_H_26(double *state, double *unused, double *out_8176453625819094653) {
  H_26(state, unused, out_8176453625819094653);
}
void car_h_27(double *state, double *unused, double *out_4426907441453097510) {
  h_27(state, unused, out_4426907441453097510);
}
void car_H_27(double *state, double *unused, double *out_306976722746153415) {
  H_27(state, unused, out_306976722746153415);
}
void car_h_29(double *state, double *unused, double *out_2160920485023197653) {
  h_29(state, unused, out_2160920485023197653);
}
void car_H_29(double *state, double *unused, double *out_1406386004123397618) {
  H_29(state, unused, out_1406386004123397618);
}
void car_h_28(double *state, double *unused, double *out_7017073928463388327) {
  h_28(state, unused, out_7017073928463388327);
}
void car_H_28(double *state, double *unused, double *out_6488785021192928192) {
  H_28(state, unused, out_6488785021192928192);
}
void car_h_31(double *state, double *unused, double *out_5156479888167106809) {
  h_31(state, unused, out_5156479888167106809);
}
void car_H_31(double *state, double *unused, double *out_4404304345068078001) {
  H_31(state, unused, out_4404304345068078001);
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
