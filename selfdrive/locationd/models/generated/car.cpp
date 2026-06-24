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
void err_fun(double *nom_x, double *delta_x, double *out_6972961942535496334) {
   out_6972961942535496334[0] = delta_x[0] + nom_x[0];
   out_6972961942535496334[1] = delta_x[1] + nom_x[1];
   out_6972961942535496334[2] = delta_x[2] + nom_x[2];
   out_6972961942535496334[3] = delta_x[3] + nom_x[3];
   out_6972961942535496334[4] = delta_x[4] + nom_x[4];
   out_6972961942535496334[5] = delta_x[5] + nom_x[5];
   out_6972961942535496334[6] = delta_x[6] + nom_x[6];
   out_6972961942535496334[7] = delta_x[7] + nom_x[7];
   out_6972961942535496334[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2104979621458798626) {
   out_2104979621458798626[0] = -nom_x[0] + true_x[0];
   out_2104979621458798626[1] = -nom_x[1] + true_x[1];
   out_2104979621458798626[2] = -nom_x[2] + true_x[2];
   out_2104979621458798626[3] = -nom_x[3] + true_x[3];
   out_2104979621458798626[4] = -nom_x[4] + true_x[4];
   out_2104979621458798626[5] = -nom_x[5] + true_x[5];
   out_2104979621458798626[6] = -nom_x[6] + true_x[6];
   out_2104979621458798626[7] = -nom_x[7] + true_x[7];
   out_2104979621458798626[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2779658660641459178) {
   out_2779658660641459178[0] = 1.0;
   out_2779658660641459178[1] = 0.0;
   out_2779658660641459178[2] = 0.0;
   out_2779658660641459178[3] = 0.0;
   out_2779658660641459178[4] = 0.0;
   out_2779658660641459178[5] = 0.0;
   out_2779658660641459178[6] = 0.0;
   out_2779658660641459178[7] = 0.0;
   out_2779658660641459178[8] = 0.0;
   out_2779658660641459178[9] = 0.0;
   out_2779658660641459178[10] = 1.0;
   out_2779658660641459178[11] = 0.0;
   out_2779658660641459178[12] = 0.0;
   out_2779658660641459178[13] = 0.0;
   out_2779658660641459178[14] = 0.0;
   out_2779658660641459178[15] = 0.0;
   out_2779658660641459178[16] = 0.0;
   out_2779658660641459178[17] = 0.0;
   out_2779658660641459178[18] = 0.0;
   out_2779658660641459178[19] = 0.0;
   out_2779658660641459178[20] = 1.0;
   out_2779658660641459178[21] = 0.0;
   out_2779658660641459178[22] = 0.0;
   out_2779658660641459178[23] = 0.0;
   out_2779658660641459178[24] = 0.0;
   out_2779658660641459178[25] = 0.0;
   out_2779658660641459178[26] = 0.0;
   out_2779658660641459178[27] = 0.0;
   out_2779658660641459178[28] = 0.0;
   out_2779658660641459178[29] = 0.0;
   out_2779658660641459178[30] = 1.0;
   out_2779658660641459178[31] = 0.0;
   out_2779658660641459178[32] = 0.0;
   out_2779658660641459178[33] = 0.0;
   out_2779658660641459178[34] = 0.0;
   out_2779658660641459178[35] = 0.0;
   out_2779658660641459178[36] = 0.0;
   out_2779658660641459178[37] = 0.0;
   out_2779658660641459178[38] = 0.0;
   out_2779658660641459178[39] = 0.0;
   out_2779658660641459178[40] = 1.0;
   out_2779658660641459178[41] = 0.0;
   out_2779658660641459178[42] = 0.0;
   out_2779658660641459178[43] = 0.0;
   out_2779658660641459178[44] = 0.0;
   out_2779658660641459178[45] = 0.0;
   out_2779658660641459178[46] = 0.0;
   out_2779658660641459178[47] = 0.0;
   out_2779658660641459178[48] = 0.0;
   out_2779658660641459178[49] = 0.0;
   out_2779658660641459178[50] = 1.0;
   out_2779658660641459178[51] = 0.0;
   out_2779658660641459178[52] = 0.0;
   out_2779658660641459178[53] = 0.0;
   out_2779658660641459178[54] = 0.0;
   out_2779658660641459178[55] = 0.0;
   out_2779658660641459178[56] = 0.0;
   out_2779658660641459178[57] = 0.0;
   out_2779658660641459178[58] = 0.0;
   out_2779658660641459178[59] = 0.0;
   out_2779658660641459178[60] = 1.0;
   out_2779658660641459178[61] = 0.0;
   out_2779658660641459178[62] = 0.0;
   out_2779658660641459178[63] = 0.0;
   out_2779658660641459178[64] = 0.0;
   out_2779658660641459178[65] = 0.0;
   out_2779658660641459178[66] = 0.0;
   out_2779658660641459178[67] = 0.0;
   out_2779658660641459178[68] = 0.0;
   out_2779658660641459178[69] = 0.0;
   out_2779658660641459178[70] = 1.0;
   out_2779658660641459178[71] = 0.0;
   out_2779658660641459178[72] = 0.0;
   out_2779658660641459178[73] = 0.0;
   out_2779658660641459178[74] = 0.0;
   out_2779658660641459178[75] = 0.0;
   out_2779658660641459178[76] = 0.0;
   out_2779658660641459178[77] = 0.0;
   out_2779658660641459178[78] = 0.0;
   out_2779658660641459178[79] = 0.0;
   out_2779658660641459178[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_1847838116479859502) {
   out_1847838116479859502[0] = state[0];
   out_1847838116479859502[1] = state[1];
   out_1847838116479859502[2] = state[2];
   out_1847838116479859502[3] = state[3];
   out_1847838116479859502[4] = state[4];
   out_1847838116479859502[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_1847838116479859502[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_1847838116479859502[7] = state[7];
   out_1847838116479859502[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8278586360493195906) {
   out_8278586360493195906[0] = 1;
   out_8278586360493195906[1] = 0;
   out_8278586360493195906[2] = 0;
   out_8278586360493195906[3] = 0;
   out_8278586360493195906[4] = 0;
   out_8278586360493195906[5] = 0;
   out_8278586360493195906[6] = 0;
   out_8278586360493195906[7] = 0;
   out_8278586360493195906[8] = 0;
   out_8278586360493195906[9] = 0;
   out_8278586360493195906[10] = 1;
   out_8278586360493195906[11] = 0;
   out_8278586360493195906[12] = 0;
   out_8278586360493195906[13] = 0;
   out_8278586360493195906[14] = 0;
   out_8278586360493195906[15] = 0;
   out_8278586360493195906[16] = 0;
   out_8278586360493195906[17] = 0;
   out_8278586360493195906[18] = 0;
   out_8278586360493195906[19] = 0;
   out_8278586360493195906[20] = 1;
   out_8278586360493195906[21] = 0;
   out_8278586360493195906[22] = 0;
   out_8278586360493195906[23] = 0;
   out_8278586360493195906[24] = 0;
   out_8278586360493195906[25] = 0;
   out_8278586360493195906[26] = 0;
   out_8278586360493195906[27] = 0;
   out_8278586360493195906[28] = 0;
   out_8278586360493195906[29] = 0;
   out_8278586360493195906[30] = 1;
   out_8278586360493195906[31] = 0;
   out_8278586360493195906[32] = 0;
   out_8278586360493195906[33] = 0;
   out_8278586360493195906[34] = 0;
   out_8278586360493195906[35] = 0;
   out_8278586360493195906[36] = 0;
   out_8278586360493195906[37] = 0;
   out_8278586360493195906[38] = 0;
   out_8278586360493195906[39] = 0;
   out_8278586360493195906[40] = 1;
   out_8278586360493195906[41] = 0;
   out_8278586360493195906[42] = 0;
   out_8278586360493195906[43] = 0;
   out_8278586360493195906[44] = 0;
   out_8278586360493195906[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8278586360493195906[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8278586360493195906[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8278586360493195906[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8278586360493195906[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8278586360493195906[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8278586360493195906[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8278586360493195906[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8278586360493195906[53] = -9.8100000000000005*dt;
   out_8278586360493195906[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8278586360493195906[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8278586360493195906[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8278586360493195906[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8278586360493195906[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8278586360493195906[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8278586360493195906[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8278586360493195906[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8278586360493195906[62] = 0;
   out_8278586360493195906[63] = 0;
   out_8278586360493195906[64] = 0;
   out_8278586360493195906[65] = 0;
   out_8278586360493195906[66] = 0;
   out_8278586360493195906[67] = 0;
   out_8278586360493195906[68] = 0;
   out_8278586360493195906[69] = 0;
   out_8278586360493195906[70] = 1;
   out_8278586360493195906[71] = 0;
   out_8278586360493195906[72] = 0;
   out_8278586360493195906[73] = 0;
   out_8278586360493195906[74] = 0;
   out_8278586360493195906[75] = 0;
   out_8278586360493195906[76] = 0;
   out_8278586360493195906[77] = 0;
   out_8278586360493195906[78] = 0;
   out_8278586360493195906[79] = 0;
   out_8278586360493195906[80] = 1;
}
void h_25(double *state, double *unused, double *out_4623448408360880072) {
   out_4623448408360880072[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2013210898559251929) {
   out_2013210898559251929[0] = 0;
   out_2013210898559251929[1] = 0;
   out_2013210898559251929[2] = 0;
   out_2013210898559251929[3] = 0;
   out_2013210898559251929[4] = 0;
   out_2013210898559251929[5] = 0;
   out_2013210898559251929[6] = 1;
   out_2013210898559251929[7] = 0;
   out_2013210898559251929[8] = 0;
}
void h_24(double *state, double *unused, double *out_5136059034754269087) {
   out_5136059034754269087[0] = state[4];
   out_5136059034754269087[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7286705181472264523) {
   out_7286705181472264523[0] = 0;
   out_7286705181472264523[1] = 0;
   out_7286705181472264523[2] = 0;
   out_7286705181472264523[3] = 0;
   out_7286705181472264523[4] = 1;
   out_7286705181472264523[5] = 0;
   out_7286705181472264523[6] = 0;
   out_7286705181472264523[7] = 0;
   out_7286705181472264523[8] = 0;
   out_7286705181472264523[9] = 0;
   out_7286705181472264523[10] = 0;
   out_7286705181472264523[11] = 0;
   out_7286705181472264523[12] = 0;
   out_7286705181472264523[13] = 0;
   out_7286705181472264523[14] = 1;
   out_7286705181472264523[15] = 0;
   out_7286705181472264523[16] = 0;
   out_7286705181472264523[17] = 0;
}
void h_30(double *state, double *unused, double *out_5183418188630129660) {
   out_5183418188630129660[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2514485431568356269) {
   out_2514485431568356269[0] = 0;
   out_2514485431568356269[1] = 0;
   out_2514485431568356269[2] = 0;
   out_2514485431568356269[3] = 0;
   out_2514485431568356269[4] = 1;
   out_2514485431568356269[5] = 0;
   out_2514485431568356269[6] = 0;
   out_2514485431568356269[7] = 0;
   out_2514485431568356269[8] = 0;
}
void h_26(double *state, double *unused, double *out_8220204240074462345) {
   out_8220204240074462345[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1728292420314804295) {
   out_1728292420314804295[0] = 0;
   out_1728292420314804295[1] = 0;
   out_1728292420314804295[2] = 0;
   out_1728292420314804295[3] = 0;
   out_1728292420314804295[4] = 0;
   out_1728292420314804295[5] = 0;
   out_1728292420314804295[6] = 0;
   out_1728292420314804295[7] = 1;
   out_1728292420314804295[8] = 0;
}
void h_27(double *state, double *unused, double *out_6443570481160411950) {
   out_6443570481160411950[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4689248743368781180) {
   out_4689248743368781180[0] = 0;
   out_4689248743368781180[1] = 0;
   out_4689248743368781180[2] = 0;
   out_4689248743368781180[3] = 1;
   out_4689248743368781180[4] = 0;
   out_4689248743368781180[5] = 0;
   out_4689248743368781180[6] = 0;
   out_4689248743368781180[7] = 0;
   out_4689248743368781180[8] = 0;
}
void h_29(double *state, double *unused, double *out_4239908335728467225) {
   out_4239908335728467225[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2004254087253964085) {
   out_2004254087253964085[0] = 0;
   out_2004254087253964085[1] = 1;
   out_2004254087253964085[2] = 0;
   out_2004254087253964085[3] = 0;
   out_2004254087253964085[4] = 0;
   out_2004254087253964085[5] = 0;
   out_2004254087253964085[6] = 0;
   out_2004254087253964085[7] = 0;
   out_2004254087253964085[8] = 0;
}
void h_28(double *state, double *unused, double *out_8966387541104806981) {
   out_8966387541104806981[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7086653104323494659) {
   out_7086653104323494659[0] = 1;
   out_7086653104323494659[1] = 0;
   out_7086653104323494659[2] = 0;
   out_7086653104323494659[3] = 0;
   out_7086653104323494659[4] = 0;
   out_7086653104323494659[5] = 0;
   out_7086653104323494659[6] = 0;
   out_7086653104323494659[7] = 0;
   out_7086653104323494659[8] = 0;
}
void h_31(double *state, double *unused, double *out_8508687616659686337) {
   out_8508687616659686337[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2354500522548155771) {
   out_2354500522548155771[0] = 0;
   out_2354500522548155771[1] = 0;
   out_2354500522548155771[2] = 0;
   out_2354500522548155771[3] = 0;
   out_2354500522548155771[4] = 0;
   out_2354500522548155771[5] = 0;
   out_2354500522548155771[6] = 0;
   out_2354500522548155771[7] = 0;
   out_2354500522548155771[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_6972961942535496334) {
  err_fun(nom_x, delta_x, out_6972961942535496334);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2104979621458798626) {
  inv_err_fun(nom_x, true_x, out_2104979621458798626);
}
void car_H_mod_fun(double *state, double *out_2779658660641459178) {
  H_mod_fun(state, out_2779658660641459178);
}
void car_f_fun(double *state, double dt, double *out_1847838116479859502) {
  f_fun(state,  dt, out_1847838116479859502);
}
void car_F_fun(double *state, double dt, double *out_8278586360493195906) {
  F_fun(state,  dt, out_8278586360493195906);
}
void car_h_25(double *state, double *unused, double *out_4623448408360880072) {
  h_25(state, unused, out_4623448408360880072);
}
void car_H_25(double *state, double *unused, double *out_2013210898559251929) {
  H_25(state, unused, out_2013210898559251929);
}
void car_h_24(double *state, double *unused, double *out_5136059034754269087) {
  h_24(state, unused, out_5136059034754269087);
}
void car_H_24(double *state, double *unused, double *out_7286705181472264523) {
  H_24(state, unused, out_7286705181472264523);
}
void car_h_30(double *state, double *unused, double *out_5183418188630129660) {
  h_30(state, unused, out_5183418188630129660);
}
void car_H_30(double *state, double *unused, double *out_2514485431568356269) {
  H_30(state, unused, out_2514485431568356269);
}
void car_h_26(double *state, double *unused, double *out_8220204240074462345) {
  h_26(state, unused, out_8220204240074462345);
}
void car_H_26(double *state, double *unused, double *out_1728292420314804295) {
  H_26(state, unused, out_1728292420314804295);
}
void car_h_27(double *state, double *unused, double *out_6443570481160411950) {
  h_27(state, unused, out_6443570481160411950);
}
void car_H_27(double *state, double *unused, double *out_4689248743368781180) {
  H_27(state, unused, out_4689248743368781180);
}
void car_h_29(double *state, double *unused, double *out_4239908335728467225) {
  h_29(state, unused, out_4239908335728467225);
}
void car_H_29(double *state, double *unused, double *out_2004254087253964085) {
  H_29(state, unused, out_2004254087253964085);
}
void car_h_28(double *state, double *unused, double *out_8966387541104806981) {
  h_28(state, unused, out_8966387541104806981);
}
void car_H_28(double *state, double *unused, double *out_7086653104323494659) {
  H_28(state, unused, out_7086653104323494659);
}
void car_h_31(double *state, double *unused, double *out_8508687616659686337) {
  h_31(state, unused, out_8508687616659686337);
}
void car_H_31(double *state, double *unused, double *out_2354500522548155771) {
  H_31(state, unused, out_2354500522548155771);
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
