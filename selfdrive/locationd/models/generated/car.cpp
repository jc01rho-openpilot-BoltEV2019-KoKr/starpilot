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
void err_fun(double *nom_x, double *delta_x, double *out_2057434223379957831) {
   out_2057434223379957831[0] = delta_x[0] + nom_x[0];
   out_2057434223379957831[1] = delta_x[1] + nom_x[1];
   out_2057434223379957831[2] = delta_x[2] + nom_x[2];
   out_2057434223379957831[3] = delta_x[3] + nom_x[3];
   out_2057434223379957831[4] = delta_x[4] + nom_x[4];
   out_2057434223379957831[5] = delta_x[5] + nom_x[5];
   out_2057434223379957831[6] = delta_x[6] + nom_x[6];
   out_2057434223379957831[7] = delta_x[7] + nom_x[7];
   out_2057434223379957831[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4924816816161575884) {
   out_4924816816161575884[0] = -nom_x[0] + true_x[0];
   out_4924816816161575884[1] = -nom_x[1] + true_x[1];
   out_4924816816161575884[2] = -nom_x[2] + true_x[2];
   out_4924816816161575884[3] = -nom_x[3] + true_x[3];
   out_4924816816161575884[4] = -nom_x[4] + true_x[4];
   out_4924816816161575884[5] = -nom_x[5] + true_x[5];
   out_4924816816161575884[6] = -nom_x[6] + true_x[6];
   out_4924816816161575884[7] = -nom_x[7] + true_x[7];
   out_4924816816161575884[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8615316232539034437) {
   out_8615316232539034437[0] = 1.0;
   out_8615316232539034437[1] = 0.0;
   out_8615316232539034437[2] = 0.0;
   out_8615316232539034437[3] = 0.0;
   out_8615316232539034437[4] = 0.0;
   out_8615316232539034437[5] = 0.0;
   out_8615316232539034437[6] = 0.0;
   out_8615316232539034437[7] = 0.0;
   out_8615316232539034437[8] = 0.0;
   out_8615316232539034437[9] = 0.0;
   out_8615316232539034437[10] = 1.0;
   out_8615316232539034437[11] = 0.0;
   out_8615316232539034437[12] = 0.0;
   out_8615316232539034437[13] = 0.0;
   out_8615316232539034437[14] = 0.0;
   out_8615316232539034437[15] = 0.0;
   out_8615316232539034437[16] = 0.0;
   out_8615316232539034437[17] = 0.0;
   out_8615316232539034437[18] = 0.0;
   out_8615316232539034437[19] = 0.0;
   out_8615316232539034437[20] = 1.0;
   out_8615316232539034437[21] = 0.0;
   out_8615316232539034437[22] = 0.0;
   out_8615316232539034437[23] = 0.0;
   out_8615316232539034437[24] = 0.0;
   out_8615316232539034437[25] = 0.0;
   out_8615316232539034437[26] = 0.0;
   out_8615316232539034437[27] = 0.0;
   out_8615316232539034437[28] = 0.0;
   out_8615316232539034437[29] = 0.0;
   out_8615316232539034437[30] = 1.0;
   out_8615316232539034437[31] = 0.0;
   out_8615316232539034437[32] = 0.0;
   out_8615316232539034437[33] = 0.0;
   out_8615316232539034437[34] = 0.0;
   out_8615316232539034437[35] = 0.0;
   out_8615316232539034437[36] = 0.0;
   out_8615316232539034437[37] = 0.0;
   out_8615316232539034437[38] = 0.0;
   out_8615316232539034437[39] = 0.0;
   out_8615316232539034437[40] = 1.0;
   out_8615316232539034437[41] = 0.0;
   out_8615316232539034437[42] = 0.0;
   out_8615316232539034437[43] = 0.0;
   out_8615316232539034437[44] = 0.0;
   out_8615316232539034437[45] = 0.0;
   out_8615316232539034437[46] = 0.0;
   out_8615316232539034437[47] = 0.0;
   out_8615316232539034437[48] = 0.0;
   out_8615316232539034437[49] = 0.0;
   out_8615316232539034437[50] = 1.0;
   out_8615316232539034437[51] = 0.0;
   out_8615316232539034437[52] = 0.0;
   out_8615316232539034437[53] = 0.0;
   out_8615316232539034437[54] = 0.0;
   out_8615316232539034437[55] = 0.0;
   out_8615316232539034437[56] = 0.0;
   out_8615316232539034437[57] = 0.0;
   out_8615316232539034437[58] = 0.0;
   out_8615316232539034437[59] = 0.0;
   out_8615316232539034437[60] = 1.0;
   out_8615316232539034437[61] = 0.0;
   out_8615316232539034437[62] = 0.0;
   out_8615316232539034437[63] = 0.0;
   out_8615316232539034437[64] = 0.0;
   out_8615316232539034437[65] = 0.0;
   out_8615316232539034437[66] = 0.0;
   out_8615316232539034437[67] = 0.0;
   out_8615316232539034437[68] = 0.0;
   out_8615316232539034437[69] = 0.0;
   out_8615316232539034437[70] = 1.0;
   out_8615316232539034437[71] = 0.0;
   out_8615316232539034437[72] = 0.0;
   out_8615316232539034437[73] = 0.0;
   out_8615316232539034437[74] = 0.0;
   out_8615316232539034437[75] = 0.0;
   out_8615316232539034437[76] = 0.0;
   out_8615316232539034437[77] = 0.0;
   out_8615316232539034437[78] = 0.0;
   out_8615316232539034437[79] = 0.0;
   out_8615316232539034437[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8159180570289535402) {
   out_8159180570289535402[0] = state[0];
   out_8159180570289535402[1] = state[1];
   out_8159180570289535402[2] = state[2];
   out_8159180570289535402[3] = state[3];
   out_8159180570289535402[4] = state[4];
   out_8159180570289535402[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8159180570289535402[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8159180570289535402[7] = state[7];
   out_8159180570289535402[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8855850861951736689) {
   out_8855850861951736689[0] = 1;
   out_8855850861951736689[1] = 0;
   out_8855850861951736689[2] = 0;
   out_8855850861951736689[3] = 0;
   out_8855850861951736689[4] = 0;
   out_8855850861951736689[5] = 0;
   out_8855850861951736689[6] = 0;
   out_8855850861951736689[7] = 0;
   out_8855850861951736689[8] = 0;
   out_8855850861951736689[9] = 0;
   out_8855850861951736689[10] = 1;
   out_8855850861951736689[11] = 0;
   out_8855850861951736689[12] = 0;
   out_8855850861951736689[13] = 0;
   out_8855850861951736689[14] = 0;
   out_8855850861951736689[15] = 0;
   out_8855850861951736689[16] = 0;
   out_8855850861951736689[17] = 0;
   out_8855850861951736689[18] = 0;
   out_8855850861951736689[19] = 0;
   out_8855850861951736689[20] = 1;
   out_8855850861951736689[21] = 0;
   out_8855850861951736689[22] = 0;
   out_8855850861951736689[23] = 0;
   out_8855850861951736689[24] = 0;
   out_8855850861951736689[25] = 0;
   out_8855850861951736689[26] = 0;
   out_8855850861951736689[27] = 0;
   out_8855850861951736689[28] = 0;
   out_8855850861951736689[29] = 0;
   out_8855850861951736689[30] = 1;
   out_8855850861951736689[31] = 0;
   out_8855850861951736689[32] = 0;
   out_8855850861951736689[33] = 0;
   out_8855850861951736689[34] = 0;
   out_8855850861951736689[35] = 0;
   out_8855850861951736689[36] = 0;
   out_8855850861951736689[37] = 0;
   out_8855850861951736689[38] = 0;
   out_8855850861951736689[39] = 0;
   out_8855850861951736689[40] = 1;
   out_8855850861951736689[41] = 0;
   out_8855850861951736689[42] = 0;
   out_8855850861951736689[43] = 0;
   out_8855850861951736689[44] = 0;
   out_8855850861951736689[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8855850861951736689[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8855850861951736689[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8855850861951736689[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8855850861951736689[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8855850861951736689[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8855850861951736689[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8855850861951736689[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8855850861951736689[53] = -9.8100000000000005*dt;
   out_8855850861951736689[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8855850861951736689[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8855850861951736689[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8855850861951736689[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8855850861951736689[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8855850861951736689[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8855850861951736689[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8855850861951736689[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8855850861951736689[62] = 0;
   out_8855850861951736689[63] = 0;
   out_8855850861951736689[64] = 0;
   out_8855850861951736689[65] = 0;
   out_8855850861951736689[66] = 0;
   out_8855850861951736689[67] = 0;
   out_8855850861951736689[68] = 0;
   out_8855850861951736689[69] = 0;
   out_8855850861951736689[70] = 1;
   out_8855850861951736689[71] = 0;
   out_8855850861951736689[72] = 0;
   out_8855850861951736689[73] = 0;
   out_8855850861951736689[74] = 0;
   out_8855850861951736689[75] = 0;
   out_8855850861951736689[76] = 0;
   out_8855850861951736689[77] = 0;
   out_8855850861951736689[78] = 0;
   out_8855850861951736689[79] = 0;
   out_8855850861951736689[80] = 1;
}
void h_25(double *state, double *unused, double *out_7057179500116168670) {
   out_7057179500116168670[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8109981790338737725) {
   out_8109981790338737725[0] = 0;
   out_8109981790338737725[1] = 0;
   out_8109981790338737725[2] = 0;
   out_8109981790338737725[3] = 0;
   out_8109981790338737725[4] = 0;
   out_8109981790338737725[5] = 0;
   out_8109981790338737725[6] = 1;
   out_8109981790338737725[7] = 0;
   out_8109981790338737725[8] = 0;
}
void h_24(double *state, double *unused, double *out_6854320894517861807) {
   out_6854320894517861807[0] = state[4];
   out_6854320894517861807[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8607899164193499822) {
   out_8607899164193499822[0] = 0;
   out_8607899164193499822[1] = 0;
   out_8607899164193499822[2] = 0;
   out_8607899164193499822[3] = 0;
   out_8607899164193499822[4] = 1;
   out_8607899164193499822[5] = 0;
   out_8607899164193499822[6] = 0;
   out_8607899164193499822[7] = 0;
   out_8607899164193499822[8] = 0;
   out_8607899164193499822[9] = 0;
   out_8607899164193499822[10] = 0;
   out_8607899164193499822[11] = 0;
   out_8607899164193499822[12] = 0;
   out_8607899164193499822[13] = 0;
   out_8607899164193499822[14] = 1;
   out_8607899164193499822[15] = 0;
   out_8607899164193499822[16] = 0;
   out_8607899164193499822[17] = 0;
}
void h_30(double *state, double *unused, double *out_3929005809344494621) {
   out_3929005809344494621[0] = state[4];
}
void H_30(double *state, double *unused, double *out_1193291448847120970) {
   out_1193291448847120970[0] = 0;
   out_1193291448847120970[1] = 0;
   out_1193291448847120970[2] = 0;
   out_1193291448847120970[3] = 0;
   out_1193291448847120970[4] = 1;
   out_1193291448847120970[5] = 0;
   out_1193291448847120970[6] = 0;
   out_1193291448847120970[7] = 0;
   out_1193291448847120970[8] = 0;
}
void h_26(double *state, double *unused, double *out_6807016989944022268) {
   out_6807016989944022268[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6595258964496757667) {
   out_6595258964496757667[0] = 0;
   out_6595258964496757667[1] = 0;
   out_6595258964496757667[2] = 0;
   out_6595258964496757667[3] = 0;
   out_6595258964496757667[4] = 0;
   out_6595258964496757667[5] = 0;
   out_6595258964496757667[6] = 0;
   out_6595258964496757667[7] = 1;
   out_6595258964496757667[8] = 0;
}
void h_27(double *state, double *unused, double *out_2055506232455323025) {
   out_2055506232455323025[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3368054760647545881) {
   out_3368054760647545881[0] = 0;
   out_3368054760647545881[1] = 0;
   out_3368054760647545881[2] = 0;
   out_3368054760647545881[3] = 1;
   out_3368054760647545881[4] = 0;
   out_3368054760647545881[5] = 0;
   out_3368054760647545881[6] = 0;
   out_3368054760647545881[7] = 0;
   out_3368054760647545881[8] = 0;
}
void h_29(double *state, double *unused, double *out_7581563669006346138) {
   out_7581563669006346138[0] = state[1];
}
void H_29(double *state, double *unused, double *out_683060104532728786) {
   out_683060104532728786[0] = 0;
   out_683060104532728786[1] = 1;
   out_683060104532728786[2] = 0;
   out_683060104532728786[3] = 0;
   out_683060104532728786[4] = 0;
   out_683060104532728786[5] = 0;
   out_683060104532728786[6] = 0;
   out_683060104532728786[7] = 0;
   out_683060104532728786[8] = 0;
}
void h_28(double *state, double *unused, double *out_7985581021610001938) {
   out_7985581021610001938[0] = state[0];
}
void H_28(double *state, double *unused, double *out_5765459121602259360) {
   out_5765459121602259360[0] = 1;
   out_5765459121602259360[1] = 0;
   out_5765459121602259360[2] = 0;
   out_5765459121602259360[3] = 0;
   out_5765459121602259360[4] = 0;
   out_5765459121602259360[5] = 0;
   out_5765459121602259360[6] = 0;
   out_5765459121602259360[7] = 0;
   out_5765459121602259360[8] = 0;
}
void h_31(double *state, double *unused, double *out_706085756704503771) {
   out_706085756704503771[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8079335828461777297) {
   out_8079335828461777297[0] = 0;
   out_8079335828461777297[1] = 0;
   out_8079335828461777297[2] = 0;
   out_8079335828461777297[3] = 0;
   out_8079335828461777297[4] = 0;
   out_8079335828461777297[5] = 0;
   out_8079335828461777297[6] = 0;
   out_8079335828461777297[7] = 0;
   out_8079335828461777297[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_2057434223379957831) {
  err_fun(nom_x, delta_x, out_2057434223379957831);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4924816816161575884) {
  inv_err_fun(nom_x, true_x, out_4924816816161575884);
}
void car_H_mod_fun(double *state, double *out_8615316232539034437) {
  H_mod_fun(state, out_8615316232539034437);
}
void car_f_fun(double *state, double dt, double *out_8159180570289535402) {
  f_fun(state,  dt, out_8159180570289535402);
}
void car_F_fun(double *state, double dt, double *out_8855850861951736689) {
  F_fun(state,  dt, out_8855850861951736689);
}
void car_h_25(double *state, double *unused, double *out_7057179500116168670) {
  h_25(state, unused, out_7057179500116168670);
}
void car_H_25(double *state, double *unused, double *out_8109981790338737725) {
  H_25(state, unused, out_8109981790338737725);
}
void car_h_24(double *state, double *unused, double *out_6854320894517861807) {
  h_24(state, unused, out_6854320894517861807);
}
void car_H_24(double *state, double *unused, double *out_8607899164193499822) {
  H_24(state, unused, out_8607899164193499822);
}
void car_h_30(double *state, double *unused, double *out_3929005809344494621) {
  h_30(state, unused, out_3929005809344494621);
}
void car_H_30(double *state, double *unused, double *out_1193291448847120970) {
  H_30(state, unused, out_1193291448847120970);
}
void car_h_26(double *state, double *unused, double *out_6807016989944022268) {
  h_26(state, unused, out_6807016989944022268);
}
void car_H_26(double *state, double *unused, double *out_6595258964496757667) {
  H_26(state, unused, out_6595258964496757667);
}
void car_h_27(double *state, double *unused, double *out_2055506232455323025) {
  h_27(state, unused, out_2055506232455323025);
}
void car_H_27(double *state, double *unused, double *out_3368054760647545881) {
  H_27(state, unused, out_3368054760647545881);
}
void car_h_29(double *state, double *unused, double *out_7581563669006346138) {
  h_29(state, unused, out_7581563669006346138);
}
void car_H_29(double *state, double *unused, double *out_683060104532728786) {
  H_29(state, unused, out_683060104532728786);
}
void car_h_28(double *state, double *unused, double *out_7985581021610001938) {
  h_28(state, unused, out_7985581021610001938);
}
void car_H_28(double *state, double *unused, double *out_5765459121602259360) {
  H_28(state, unused, out_5765459121602259360);
}
void car_h_31(double *state, double *unused, double *out_706085756704503771) {
  h_31(state, unused, out_706085756704503771);
}
void car_H_31(double *state, double *unused, double *out_8079335828461777297) {
  H_31(state, unused, out_8079335828461777297);
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
