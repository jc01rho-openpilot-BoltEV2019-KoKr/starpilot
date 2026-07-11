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
void err_fun(double *nom_x, double *delta_x, double *out_1054824998219177113) {
   out_1054824998219177113[0] = delta_x[0] + nom_x[0];
   out_1054824998219177113[1] = delta_x[1] + nom_x[1];
   out_1054824998219177113[2] = delta_x[2] + nom_x[2];
   out_1054824998219177113[3] = delta_x[3] + nom_x[3];
   out_1054824998219177113[4] = delta_x[4] + nom_x[4];
   out_1054824998219177113[5] = delta_x[5] + nom_x[5];
   out_1054824998219177113[6] = delta_x[6] + nom_x[6];
   out_1054824998219177113[7] = delta_x[7] + nom_x[7];
   out_1054824998219177113[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8618844445394053899) {
   out_8618844445394053899[0] = -nom_x[0] + true_x[0];
   out_8618844445394053899[1] = -nom_x[1] + true_x[1];
   out_8618844445394053899[2] = -nom_x[2] + true_x[2];
   out_8618844445394053899[3] = -nom_x[3] + true_x[3];
   out_8618844445394053899[4] = -nom_x[4] + true_x[4];
   out_8618844445394053899[5] = -nom_x[5] + true_x[5];
   out_8618844445394053899[6] = -nom_x[6] + true_x[6];
   out_8618844445394053899[7] = -nom_x[7] + true_x[7];
   out_8618844445394053899[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_9083000739620874267) {
   out_9083000739620874267[0] = 1.0;
   out_9083000739620874267[1] = 0.0;
   out_9083000739620874267[2] = 0.0;
   out_9083000739620874267[3] = 0.0;
   out_9083000739620874267[4] = 0.0;
   out_9083000739620874267[5] = 0.0;
   out_9083000739620874267[6] = 0.0;
   out_9083000739620874267[7] = 0.0;
   out_9083000739620874267[8] = 0.0;
   out_9083000739620874267[9] = 0.0;
   out_9083000739620874267[10] = 1.0;
   out_9083000739620874267[11] = 0.0;
   out_9083000739620874267[12] = 0.0;
   out_9083000739620874267[13] = 0.0;
   out_9083000739620874267[14] = 0.0;
   out_9083000739620874267[15] = 0.0;
   out_9083000739620874267[16] = 0.0;
   out_9083000739620874267[17] = 0.0;
   out_9083000739620874267[18] = 0.0;
   out_9083000739620874267[19] = 0.0;
   out_9083000739620874267[20] = 1.0;
   out_9083000739620874267[21] = 0.0;
   out_9083000739620874267[22] = 0.0;
   out_9083000739620874267[23] = 0.0;
   out_9083000739620874267[24] = 0.0;
   out_9083000739620874267[25] = 0.0;
   out_9083000739620874267[26] = 0.0;
   out_9083000739620874267[27] = 0.0;
   out_9083000739620874267[28] = 0.0;
   out_9083000739620874267[29] = 0.0;
   out_9083000739620874267[30] = 1.0;
   out_9083000739620874267[31] = 0.0;
   out_9083000739620874267[32] = 0.0;
   out_9083000739620874267[33] = 0.0;
   out_9083000739620874267[34] = 0.0;
   out_9083000739620874267[35] = 0.0;
   out_9083000739620874267[36] = 0.0;
   out_9083000739620874267[37] = 0.0;
   out_9083000739620874267[38] = 0.0;
   out_9083000739620874267[39] = 0.0;
   out_9083000739620874267[40] = 1.0;
   out_9083000739620874267[41] = 0.0;
   out_9083000739620874267[42] = 0.0;
   out_9083000739620874267[43] = 0.0;
   out_9083000739620874267[44] = 0.0;
   out_9083000739620874267[45] = 0.0;
   out_9083000739620874267[46] = 0.0;
   out_9083000739620874267[47] = 0.0;
   out_9083000739620874267[48] = 0.0;
   out_9083000739620874267[49] = 0.0;
   out_9083000739620874267[50] = 1.0;
   out_9083000739620874267[51] = 0.0;
   out_9083000739620874267[52] = 0.0;
   out_9083000739620874267[53] = 0.0;
   out_9083000739620874267[54] = 0.0;
   out_9083000739620874267[55] = 0.0;
   out_9083000739620874267[56] = 0.0;
   out_9083000739620874267[57] = 0.0;
   out_9083000739620874267[58] = 0.0;
   out_9083000739620874267[59] = 0.0;
   out_9083000739620874267[60] = 1.0;
   out_9083000739620874267[61] = 0.0;
   out_9083000739620874267[62] = 0.0;
   out_9083000739620874267[63] = 0.0;
   out_9083000739620874267[64] = 0.0;
   out_9083000739620874267[65] = 0.0;
   out_9083000739620874267[66] = 0.0;
   out_9083000739620874267[67] = 0.0;
   out_9083000739620874267[68] = 0.0;
   out_9083000739620874267[69] = 0.0;
   out_9083000739620874267[70] = 1.0;
   out_9083000739620874267[71] = 0.0;
   out_9083000739620874267[72] = 0.0;
   out_9083000739620874267[73] = 0.0;
   out_9083000739620874267[74] = 0.0;
   out_9083000739620874267[75] = 0.0;
   out_9083000739620874267[76] = 0.0;
   out_9083000739620874267[77] = 0.0;
   out_9083000739620874267[78] = 0.0;
   out_9083000739620874267[79] = 0.0;
   out_9083000739620874267[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2939712332855985662) {
   out_2939712332855985662[0] = state[0];
   out_2939712332855985662[1] = state[1];
   out_2939712332855985662[2] = state[2];
   out_2939712332855985662[3] = state[3];
   out_2939712332855985662[4] = state[4];
   out_2939712332855985662[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2939712332855985662[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2939712332855985662[7] = state[7];
   out_2939712332855985662[8] = state[8];
}
void F_fun(double *state, double dt, double *out_9197210553723469698) {
   out_9197210553723469698[0] = 1;
   out_9197210553723469698[1] = 0;
   out_9197210553723469698[2] = 0;
   out_9197210553723469698[3] = 0;
   out_9197210553723469698[4] = 0;
   out_9197210553723469698[5] = 0;
   out_9197210553723469698[6] = 0;
   out_9197210553723469698[7] = 0;
   out_9197210553723469698[8] = 0;
   out_9197210553723469698[9] = 0;
   out_9197210553723469698[10] = 1;
   out_9197210553723469698[11] = 0;
   out_9197210553723469698[12] = 0;
   out_9197210553723469698[13] = 0;
   out_9197210553723469698[14] = 0;
   out_9197210553723469698[15] = 0;
   out_9197210553723469698[16] = 0;
   out_9197210553723469698[17] = 0;
   out_9197210553723469698[18] = 0;
   out_9197210553723469698[19] = 0;
   out_9197210553723469698[20] = 1;
   out_9197210553723469698[21] = 0;
   out_9197210553723469698[22] = 0;
   out_9197210553723469698[23] = 0;
   out_9197210553723469698[24] = 0;
   out_9197210553723469698[25] = 0;
   out_9197210553723469698[26] = 0;
   out_9197210553723469698[27] = 0;
   out_9197210553723469698[28] = 0;
   out_9197210553723469698[29] = 0;
   out_9197210553723469698[30] = 1;
   out_9197210553723469698[31] = 0;
   out_9197210553723469698[32] = 0;
   out_9197210553723469698[33] = 0;
   out_9197210553723469698[34] = 0;
   out_9197210553723469698[35] = 0;
   out_9197210553723469698[36] = 0;
   out_9197210553723469698[37] = 0;
   out_9197210553723469698[38] = 0;
   out_9197210553723469698[39] = 0;
   out_9197210553723469698[40] = 1;
   out_9197210553723469698[41] = 0;
   out_9197210553723469698[42] = 0;
   out_9197210553723469698[43] = 0;
   out_9197210553723469698[44] = 0;
   out_9197210553723469698[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_9197210553723469698[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_9197210553723469698[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_9197210553723469698[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_9197210553723469698[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_9197210553723469698[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_9197210553723469698[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_9197210553723469698[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_9197210553723469698[53] = -9.8100000000000005*dt;
   out_9197210553723469698[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_9197210553723469698[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_9197210553723469698[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9197210553723469698[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9197210553723469698[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_9197210553723469698[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_9197210553723469698[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_9197210553723469698[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9197210553723469698[62] = 0;
   out_9197210553723469698[63] = 0;
   out_9197210553723469698[64] = 0;
   out_9197210553723469698[65] = 0;
   out_9197210553723469698[66] = 0;
   out_9197210553723469698[67] = 0;
   out_9197210553723469698[68] = 0;
   out_9197210553723469698[69] = 0;
   out_9197210553723469698[70] = 1;
   out_9197210553723469698[71] = 0;
   out_9197210553723469698[72] = 0;
   out_9197210553723469698[73] = 0;
   out_9197210553723469698[74] = 0;
   out_9197210553723469698[75] = 0;
   out_9197210553723469698[76] = 0;
   out_9197210553723469698[77] = 0;
   out_9197210553723469698[78] = 0;
   out_9197210553723469698[79] = 0;
   out_9197210553723469698[80] = 1;
}
void h_25(double *state, double *unused, double *out_7502443551709492094) {
   out_7502443551709492094[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2585977779730844316) {
   out_2585977779730844316[0] = 0;
   out_2585977779730844316[1] = 0;
   out_2585977779730844316[2] = 0;
   out_2585977779730844316[3] = 0;
   out_2585977779730844316[4] = 0;
   out_2585977779730844316[5] = 0;
   out_2585977779730844316[6] = 1;
   out_2585977779730844316[7] = 0;
   out_2585977779730844316[8] = 0;
}
void h_24(double *state, double *unused, double *out_4099652252284200208) {
   out_4099652252284200208[0] = state[4];
   out_4099652252284200208[1] = state[5];
}
void H_24(double *state, double *unused, double *out_2115520297687505592) {
   out_2115520297687505592[0] = 0;
   out_2115520297687505592[1] = 0;
   out_2115520297687505592[2] = 0;
   out_2115520297687505592[3] = 0;
   out_2115520297687505592[4] = 1;
   out_2115520297687505592[5] = 0;
   out_2115520297687505592[6] = 0;
   out_2115520297687505592[7] = 0;
   out_2115520297687505592[8] = 0;
   out_2115520297687505592[9] = 0;
   out_2115520297687505592[10] = 0;
   out_2115520297687505592[11] = 0;
   out_2115520297687505592[12] = 0;
   out_2115520297687505592[13] = 0;
   out_2115520297687505592[14] = 1;
   out_2115520297687505592[15] = 0;
   out_2115520297687505592[16] = 0;
   out_2115520297687505592[17] = 0;
}
void h_30(double *state, double *unused, double *out_7659630220060621239) {
   out_7659630220060621239[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2456638832587604246) {
   out_2456638832587604246[0] = 0;
   out_2456638832587604246[1] = 0;
   out_2456638832587604246[2] = 0;
   out_2456638832587604246[3] = 0;
   out_2456638832587604246[4] = 1;
   out_2456638832587604246[5] = 0;
   out_2456638832587604246[6] = 0;
   out_2456638832587604246[7] = 0;
   out_2456638832587604246[8] = 0;
}
void h_26(double *state, double *unused, double *out_2198951171844088969) {
   out_2198951171844088969[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1155525539143211908) {
   out_1155525539143211908[0] = 0;
   out_1155525539143211908[1] = 0;
   out_1155525539143211908[2] = 0;
   out_1155525539143211908[3] = 0;
   out_1155525539143211908[4] = 0;
   out_1155525539143211908[5] = 0;
   out_1155525539143211908[6] = 0;
   out_1155525539143211908[7] = 1;
   out_1155525539143211908[8] = 0;
}
void h_27(double *state, double *unused, double *out_5981920524318766290) {
   out_5981920524318766290[0] = state[3];
}
void H_27(double *state, double *unused, double *out_281875520787179335) {
   out_281875520787179335[0] = 0;
   out_281875520787179335[1] = 0;
   out_281875520787179335[2] = 0;
   out_281875520787179335[3] = 1;
   out_281875520787179335[4] = 0;
   out_281875520787179335[5] = 0;
   out_281875520787179335[6] = 0;
   out_281875520787179335[7] = 0;
   out_281875520787179335[8] = 0;
}
void h_29(double *state, double *unused, double *out_1781344732501906151) {
   out_1781344732501906151[0] = state[1];
}
void H_29(double *state, double *unused, double *out_1431487206082371698) {
   out_1431487206082371698[0] = 0;
   out_1431487206082371698[1] = 1;
   out_1431487206082371698[2] = 0;
   out_1431487206082371698[3] = 0;
   out_1431487206082371698[4] = 0;
   out_1431487206082371698[5] = 0;
   out_1431487206082371698[6] = 0;
   out_1431487206082371698[7] = 0;
   out_1431487206082371698[8] = 0;
}
void h_28(double *state, double *unused, double *out_2565647234669696274) {
   out_2565647234669696274[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6513886223151902272) {
   out_6513886223151902272[0] = 1;
   out_6513886223151902272[1] = 0;
   out_6513886223151902272[2] = 0;
   out_6513886223151902272[3] = 0;
   out_6513886223151902272[4] = 0;
   out_6513886223151902272[5] = 0;
   out_6513886223151902272[6] = 0;
   out_6513886223151902272[7] = 0;
   out_6513886223151902272[8] = 0;
}
void h_31(double *state, double *unused, double *out_7751082483008271581) {
   out_7751082483008271581[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2616623741607804744) {
   out_2616623741607804744[0] = 0;
   out_2616623741607804744[1] = 0;
   out_2616623741607804744[2] = 0;
   out_2616623741607804744[3] = 0;
   out_2616623741607804744[4] = 0;
   out_2616623741607804744[5] = 0;
   out_2616623741607804744[6] = 0;
   out_2616623741607804744[7] = 0;
   out_2616623741607804744[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_1054824998219177113) {
  err_fun(nom_x, delta_x, out_1054824998219177113);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8618844445394053899) {
  inv_err_fun(nom_x, true_x, out_8618844445394053899);
}
void car_H_mod_fun(double *state, double *out_9083000739620874267) {
  H_mod_fun(state, out_9083000739620874267);
}
void car_f_fun(double *state, double dt, double *out_2939712332855985662) {
  f_fun(state,  dt, out_2939712332855985662);
}
void car_F_fun(double *state, double dt, double *out_9197210553723469698) {
  F_fun(state,  dt, out_9197210553723469698);
}
void car_h_25(double *state, double *unused, double *out_7502443551709492094) {
  h_25(state, unused, out_7502443551709492094);
}
void car_H_25(double *state, double *unused, double *out_2585977779730844316) {
  H_25(state, unused, out_2585977779730844316);
}
void car_h_24(double *state, double *unused, double *out_4099652252284200208) {
  h_24(state, unused, out_4099652252284200208);
}
void car_H_24(double *state, double *unused, double *out_2115520297687505592) {
  H_24(state, unused, out_2115520297687505592);
}
void car_h_30(double *state, double *unused, double *out_7659630220060621239) {
  h_30(state, unused, out_7659630220060621239);
}
void car_H_30(double *state, double *unused, double *out_2456638832587604246) {
  H_30(state, unused, out_2456638832587604246);
}
void car_h_26(double *state, double *unused, double *out_2198951171844088969) {
  h_26(state, unused, out_2198951171844088969);
}
void car_H_26(double *state, double *unused, double *out_1155525539143211908) {
  H_26(state, unused, out_1155525539143211908);
}
void car_h_27(double *state, double *unused, double *out_5981920524318766290) {
  h_27(state, unused, out_5981920524318766290);
}
void car_H_27(double *state, double *unused, double *out_281875520787179335) {
  H_27(state, unused, out_281875520787179335);
}
void car_h_29(double *state, double *unused, double *out_1781344732501906151) {
  h_29(state, unused, out_1781344732501906151);
}
void car_H_29(double *state, double *unused, double *out_1431487206082371698) {
  H_29(state, unused, out_1431487206082371698);
}
void car_h_28(double *state, double *unused, double *out_2565647234669696274) {
  h_28(state, unused, out_2565647234669696274);
}
void car_H_28(double *state, double *unused, double *out_6513886223151902272) {
  H_28(state, unused, out_6513886223151902272);
}
void car_h_31(double *state, double *unused, double *out_7751082483008271581) {
  h_31(state, unused, out_7751082483008271581);
}
void car_H_31(double *state, double *unused, double *out_2616623741607804744) {
  H_31(state, unused, out_2616623741607804744);
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
