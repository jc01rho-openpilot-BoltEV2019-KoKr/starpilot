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
void err_fun(double *nom_x, double *delta_x, double *out_885257502884011965) {
   out_885257502884011965[0] = delta_x[0] + nom_x[0];
   out_885257502884011965[1] = delta_x[1] + nom_x[1];
   out_885257502884011965[2] = delta_x[2] + nom_x[2];
   out_885257502884011965[3] = delta_x[3] + nom_x[3];
   out_885257502884011965[4] = delta_x[4] + nom_x[4];
   out_885257502884011965[5] = delta_x[5] + nom_x[5];
   out_885257502884011965[6] = delta_x[6] + nom_x[6];
   out_885257502884011965[7] = delta_x[7] + nom_x[7];
   out_885257502884011965[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6192379265473109268) {
   out_6192379265473109268[0] = -nom_x[0] + true_x[0];
   out_6192379265473109268[1] = -nom_x[1] + true_x[1];
   out_6192379265473109268[2] = -nom_x[2] + true_x[2];
   out_6192379265473109268[3] = -nom_x[3] + true_x[3];
   out_6192379265473109268[4] = -nom_x[4] + true_x[4];
   out_6192379265473109268[5] = -nom_x[5] + true_x[5];
   out_6192379265473109268[6] = -nom_x[6] + true_x[6];
   out_6192379265473109268[7] = -nom_x[7] + true_x[7];
   out_6192379265473109268[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1067171112169386981) {
   out_1067171112169386981[0] = 1.0;
   out_1067171112169386981[1] = 0.0;
   out_1067171112169386981[2] = 0.0;
   out_1067171112169386981[3] = 0.0;
   out_1067171112169386981[4] = 0.0;
   out_1067171112169386981[5] = 0.0;
   out_1067171112169386981[6] = 0.0;
   out_1067171112169386981[7] = 0.0;
   out_1067171112169386981[8] = 0.0;
   out_1067171112169386981[9] = 0.0;
   out_1067171112169386981[10] = 1.0;
   out_1067171112169386981[11] = 0.0;
   out_1067171112169386981[12] = 0.0;
   out_1067171112169386981[13] = 0.0;
   out_1067171112169386981[14] = 0.0;
   out_1067171112169386981[15] = 0.0;
   out_1067171112169386981[16] = 0.0;
   out_1067171112169386981[17] = 0.0;
   out_1067171112169386981[18] = 0.0;
   out_1067171112169386981[19] = 0.0;
   out_1067171112169386981[20] = 1.0;
   out_1067171112169386981[21] = 0.0;
   out_1067171112169386981[22] = 0.0;
   out_1067171112169386981[23] = 0.0;
   out_1067171112169386981[24] = 0.0;
   out_1067171112169386981[25] = 0.0;
   out_1067171112169386981[26] = 0.0;
   out_1067171112169386981[27] = 0.0;
   out_1067171112169386981[28] = 0.0;
   out_1067171112169386981[29] = 0.0;
   out_1067171112169386981[30] = 1.0;
   out_1067171112169386981[31] = 0.0;
   out_1067171112169386981[32] = 0.0;
   out_1067171112169386981[33] = 0.0;
   out_1067171112169386981[34] = 0.0;
   out_1067171112169386981[35] = 0.0;
   out_1067171112169386981[36] = 0.0;
   out_1067171112169386981[37] = 0.0;
   out_1067171112169386981[38] = 0.0;
   out_1067171112169386981[39] = 0.0;
   out_1067171112169386981[40] = 1.0;
   out_1067171112169386981[41] = 0.0;
   out_1067171112169386981[42] = 0.0;
   out_1067171112169386981[43] = 0.0;
   out_1067171112169386981[44] = 0.0;
   out_1067171112169386981[45] = 0.0;
   out_1067171112169386981[46] = 0.0;
   out_1067171112169386981[47] = 0.0;
   out_1067171112169386981[48] = 0.0;
   out_1067171112169386981[49] = 0.0;
   out_1067171112169386981[50] = 1.0;
   out_1067171112169386981[51] = 0.0;
   out_1067171112169386981[52] = 0.0;
   out_1067171112169386981[53] = 0.0;
   out_1067171112169386981[54] = 0.0;
   out_1067171112169386981[55] = 0.0;
   out_1067171112169386981[56] = 0.0;
   out_1067171112169386981[57] = 0.0;
   out_1067171112169386981[58] = 0.0;
   out_1067171112169386981[59] = 0.0;
   out_1067171112169386981[60] = 1.0;
   out_1067171112169386981[61] = 0.0;
   out_1067171112169386981[62] = 0.0;
   out_1067171112169386981[63] = 0.0;
   out_1067171112169386981[64] = 0.0;
   out_1067171112169386981[65] = 0.0;
   out_1067171112169386981[66] = 0.0;
   out_1067171112169386981[67] = 0.0;
   out_1067171112169386981[68] = 0.0;
   out_1067171112169386981[69] = 0.0;
   out_1067171112169386981[70] = 1.0;
   out_1067171112169386981[71] = 0.0;
   out_1067171112169386981[72] = 0.0;
   out_1067171112169386981[73] = 0.0;
   out_1067171112169386981[74] = 0.0;
   out_1067171112169386981[75] = 0.0;
   out_1067171112169386981[76] = 0.0;
   out_1067171112169386981[77] = 0.0;
   out_1067171112169386981[78] = 0.0;
   out_1067171112169386981[79] = 0.0;
   out_1067171112169386981[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6825209250572789160) {
   out_6825209250572789160[0] = state[0];
   out_6825209250572789160[1] = state[1];
   out_6825209250572789160[2] = state[2];
   out_6825209250572789160[3] = state[3];
   out_6825209250572789160[4] = state[4];
   out_6825209250572789160[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6825209250572789160[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6825209250572789160[7] = state[7];
   out_6825209250572789160[8] = state[8];
}
void F_fun(double *state, double dt, double *out_1474779246882826642) {
   out_1474779246882826642[0] = 1;
   out_1474779246882826642[1] = 0;
   out_1474779246882826642[2] = 0;
   out_1474779246882826642[3] = 0;
   out_1474779246882826642[4] = 0;
   out_1474779246882826642[5] = 0;
   out_1474779246882826642[6] = 0;
   out_1474779246882826642[7] = 0;
   out_1474779246882826642[8] = 0;
   out_1474779246882826642[9] = 0;
   out_1474779246882826642[10] = 1;
   out_1474779246882826642[11] = 0;
   out_1474779246882826642[12] = 0;
   out_1474779246882826642[13] = 0;
   out_1474779246882826642[14] = 0;
   out_1474779246882826642[15] = 0;
   out_1474779246882826642[16] = 0;
   out_1474779246882826642[17] = 0;
   out_1474779246882826642[18] = 0;
   out_1474779246882826642[19] = 0;
   out_1474779246882826642[20] = 1;
   out_1474779246882826642[21] = 0;
   out_1474779246882826642[22] = 0;
   out_1474779246882826642[23] = 0;
   out_1474779246882826642[24] = 0;
   out_1474779246882826642[25] = 0;
   out_1474779246882826642[26] = 0;
   out_1474779246882826642[27] = 0;
   out_1474779246882826642[28] = 0;
   out_1474779246882826642[29] = 0;
   out_1474779246882826642[30] = 1;
   out_1474779246882826642[31] = 0;
   out_1474779246882826642[32] = 0;
   out_1474779246882826642[33] = 0;
   out_1474779246882826642[34] = 0;
   out_1474779246882826642[35] = 0;
   out_1474779246882826642[36] = 0;
   out_1474779246882826642[37] = 0;
   out_1474779246882826642[38] = 0;
   out_1474779246882826642[39] = 0;
   out_1474779246882826642[40] = 1;
   out_1474779246882826642[41] = 0;
   out_1474779246882826642[42] = 0;
   out_1474779246882826642[43] = 0;
   out_1474779246882826642[44] = 0;
   out_1474779246882826642[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_1474779246882826642[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_1474779246882826642[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1474779246882826642[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_1474779246882826642[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_1474779246882826642[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_1474779246882826642[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_1474779246882826642[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_1474779246882826642[53] = -9.8100000000000005*dt;
   out_1474779246882826642[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_1474779246882826642[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_1474779246882826642[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1474779246882826642[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1474779246882826642[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_1474779246882826642[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_1474779246882826642[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_1474779246882826642[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_1474779246882826642[62] = 0;
   out_1474779246882826642[63] = 0;
   out_1474779246882826642[64] = 0;
   out_1474779246882826642[65] = 0;
   out_1474779246882826642[66] = 0;
   out_1474779246882826642[67] = 0;
   out_1474779246882826642[68] = 0;
   out_1474779246882826642[69] = 0;
   out_1474779246882826642[70] = 1;
   out_1474779246882826642[71] = 0;
   out_1474779246882826642[72] = 0;
   out_1474779246882826642[73] = 0;
   out_1474779246882826642[74] = 0;
   out_1474779246882826642[75] = 0;
   out_1474779246882826642[76] = 0;
   out_1474779246882826642[77] = 0;
   out_1474779246882826642[78] = 0;
   out_1474779246882826642[79] = 0;
   out_1474779246882826642[80] = 1;
}
void h_25(double *state, double *unused, double *out_4524197194175300932) {
   out_4524197194175300932[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8126017113742850256) {
   out_8126017113742850256[0] = 0;
   out_8126017113742850256[1] = 0;
   out_8126017113742850256[2] = 0;
   out_8126017113742850256[3] = 0;
   out_8126017113742850256[4] = 0;
   out_8126017113742850256[5] = 0;
   out_8126017113742850256[6] = 1;
   out_8126017113742850256[7] = 0;
   out_8126017113742850256[8] = 0;
}
void h_24(double *state, double *unused, double *out_7846417075360830243) {
   out_7846417075360830243[0] = state[4];
   out_7846417075360830243[1] = state[5];
}
void H_24(double *state, double *unused, double *out_5500405455310713097) {
   out_5500405455310713097[0] = 0;
   out_5500405455310713097[1] = 0;
   out_5500405455310713097[2] = 0;
   out_5500405455310713097[3] = 0;
   out_5500405455310713097[4] = 1;
   out_5500405455310713097[5] = 0;
   out_5500405455310713097[6] = 0;
   out_5500405455310713097[7] = 0;
   out_5500405455310713097[8] = 0;
   out_5500405455310713097[9] = 0;
   out_5500405455310713097[10] = 0;
   out_5500405455310713097[11] = 0;
   out_5500405455310713097[12] = 0;
   out_5500405455310713097[13] = 0;
   out_5500405455310713097[14] = 1;
   out_5500405455310713097[15] = 0;
   out_5500405455310713097[16] = 0;
   out_5500405455310713097[17] = 0;
}
void h_30(double *state, double *unused, double *out_4249003131890795043) {
   out_4249003131890795043[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8255356060886090326) {
   out_8255356060886090326[0] = 0;
   out_8255356060886090326[1] = 0;
   out_8255356060886090326[2] = 0;
   out_8255356060886090326[3] = 0;
   out_8255356060886090326[4] = 1;
   out_8255356060886090326[5] = 0;
   out_8255356060886090326[6] = 0;
   out_8255356060886090326[7] = 0;
   out_8255356060886090326[8] = 0;
}
void h_26(double *state, double *unused, double *out_4941641912900521878) {
   out_4941641912900521878[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6579223641092645136) {
   out_6579223641092645136[0] = 0;
   out_6579223641092645136[1] = 0;
   out_6579223641092645136[2] = 0;
   out_6579223641092645136[3] = 0;
   out_6579223641092645136[4] = 0;
   out_6579223641092645136[5] = 0;
   out_6579223641092645136[6] = 0;
   out_6579223641092645136[7] = 1;
   out_6579223641092645136[8] = 0;
}
void h_27(double *state, double *unused, double *out_8854285503439050117) {
   out_8854285503439050117[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8016624701023036379) {
   out_8016624701023036379[0] = 0;
   out_8016624701023036379[1] = 0;
   out_8016624701023036379[2] = 0;
   out_8016624701023036379[3] = 1;
   out_8016624701023036379[4] = 0;
   out_8016624701023036379[5] = 0;
   out_8016624701023036379[6] = 0;
   out_8016624701023036379[7] = 0;
   out_8016624701023036379[8] = 0;
}
void h_29(double *state, double *unused, double *out_6762597507390055760) {
   out_6762597507390055760[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7745124716571698142) {
   out_7745124716571698142[0] = 0;
   out_7745124716571698142[1] = 1;
   out_7745124716571698142[2] = 0;
   out_7745124716571698142[3] = 0;
   out_7745124716571698142[4] = 0;
   out_7745124716571698142[5] = 0;
   out_7745124716571698142[6] = 0;
   out_7745124716571698142[7] = 0;
   out_7745124716571698142[8] = 0;
}
void h_28(double *state, double *unused, double *out_4366551354435176552) {
   out_4366551354435176552[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5619220340068322900) {
   out_5619220340068322900[0] = 1;
   out_5619220340068322900[1] = 0;
   out_5619220340068322900[2] = 0;
   out_5619220340068322900[3] = 0;
   out_5619220340068322900[4] = 0;
   out_5619220340068322900[5] = 0;
   out_5619220340068322900[6] = 0;
   out_5619220340068322900[7] = 0;
   out_5619220340068322900[8] = 0;
}
void h_31(double *state, double *unused, double *out_4613520090508550250) {
   out_4613520090508550250[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8095371151865889828) {
   out_8095371151865889828[0] = 0;
   out_8095371151865889828[1] = 0;
   out_8095371151865889828[2] = 0;
   out_8095371151865889828[3] = 0;
   out_8095371151865889828[4] = 0;
   out_8095371151865889828[5] = 0;
   out_8095371151865889828[6] = 0;
   out_8095371151865889828[7] = 0;
   out_8095371151865889828[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_885257502884011965) {
  err_fun(nom_x, delta_x, out_885257502884011965);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6192379265473109268) {
  inv_err_fun(nom_x, true_x, out_6192379265473109268);
}
void car_H_mod_fun(double *state, double *out_1067171112169386981) {
  H_mod_fun(state, out_1067171112169386981);
}
void car_f_fun(double *state, double dt, double *out_6825209250572789160) {
  f_fun(state,  dt, out_6825209250572789160);
}
void car_F_fun(double *state, double dt, double *out_1474779246882826642) {
  F_fun(state,  dt, out_1474779246882826642);
}
void car_h_25(double *state, double *unused, double *out_4524197194175300932) {
  h_25(state, unused, out_4524197194175300932);
}
void car_H_25(double *state, double *unused, double *out_8126017113742850256) {
  H_25(state, unused, out_8126017113742850256);
}
void car_h_24(double *state, double *unused, double *out_7846417075360830243) {
  h_24(state, unused, out_7846417075360830243);
}
void car_H_24(double *state, double *unused, double *out_5500405455310713097) {
  H_24(state, unused, out_5500405455310713097);
}
void car_h_30(double *state, double *unused, double *out_4249003131890795043) {
  h_30(state, unused, out_4249003131890795043);
}
void car_H_30(double *state, double *unused, double *out_8255356060886090326) {
  H_30(state, unused, out_8255356060886090326);
}
void car_h_26(double *state, double *unused, double *out_4941641912900521878) {
  h_26(state, unused, out_4941641912900521878);
}
void car_H_26(double *state, double *unused, double *out_6579223641092645136) {
  H_26(state, unused, out_6579223641092645136);
}
void car_h_27(double *state, double *unused, double *out_8854285503439050117) {
  h_27(state, unused, out_8854285503439050117);
}
void car_H_27(double *state, double *unused, double *out_8016624701023036379) {
  H_27(state, unused, out_8016624701023036379);
}
void car_h_29(double *state, double *unused, double *out_6762597507390055760) {
  h_29(state, unused, out_6762597507390055760);
}
void car_H_29(double *state, double *unused, double *out_7745124716571698142) {
  H_29(state, unused, out_7745124716571698142);
}
void car_h_28(double *state, double *unused, double *out_4366551354435176552) {
  h_28(state, unused, out_4366551354435176552);
}
void car_H_28(double *state, double *unused, double *out_5619220340068322900) {
  H_28(state, unused, out_5619220340068322900);
}
void car_h_31(double *state, double *unused, double *out_4613520090508550250) {
  h_31(state, unused, out_4613520090508550250);
}
void car_H_31(double *state, double *unused, double *out_8095371151865889828) {
  H_31(state, unused, out_8095371151865889828);
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
