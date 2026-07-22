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
void err_fun(double *nom_x, double *delta_x, double *out_8290791895352476901) {
   out_8290791895352476901[0] = delta_x[0] + nom_x[0];
   out_8290791895352476901[1] = delta_x[1] + nom_x[1];
   out_8290791895352476901[2] = delta_x[2] + nom_x[2];
   out_8290791895352476901[3] = delta_x[3] + nom_x[3];
   out_8290791895352476901[4] = delta_x[4] + nom_x[4];
   out_8290791895352476901[5] = delta_x[5] + nom_x[5];
   out_8290791895352476901[6] = delta_x[6] + nom_x[6];
   out_8290791895352476901[7] = delta_x[7] + nom_x[7];
   out_8290791895352476901[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3328957974600116526) {
   out_3328957974600116526[0] = -nom_x[0] + true_x[0];
   out_3328957974600116526[1] = -nom_x[1] + true_x[1];
   out_3328957974600116526[2] = -nom_x[2] + true_x[2];
   out_3328957974600116526[3] = -nom_x[3] + true_x[3];
   out_3328957974600116526[4] = -nom_x[4] + true_x[4];
   out_3328957974600116526[5] = -nom_x[5] + true_x[5];
   out_3328957974600116526[6] = -nom_x[6] + true_x[6];
   out_3328957974600116526[7] = -nom_x[7] + true_x[7];
   out_3328957974600116526[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_5003844791385944482) {
   out_5003844791385944482[0] = 1.0;
   out_5003844791385944482[1] = 0.0;
   out_5003844791385944482[2] = 0.0;
   out_5003844791385944482[3] = 0.0;
   out_5003844791385944482[4] = 0.0;
   out_5003844791385944482[5] = 0.0;
   out_5003844791385944482[6] = 0.0;
   out_5003844791385944482[7] = 0.0;
   out_5003844791385944482[8] = 0.0;
   out_5003844791385944482[9] = 0.0;
   out_5003844791385944482[10] = 1.0;
   out_5003844791385944482[11] = 0.0;
   out_5003844791385944482[12] = 0.0;
   out_5003844791385944482[13] = 0.0;
   out_5003844791385944482[14] = 0.0;
   out_5003844791385944482[15] = 0.0;
   out_5003844791385944482[16] = 0.0;
   out_5003844791385944482[17] = 0.0;
   out_5003844791385944482[18] = 0.0;
   out_5003844791385944482[19] = 0.0;
   out_5003844791385944482[20] = 1.0;
   out_5003844791385944482[21] = 0.0;
   out_5003844791385944482[22] = 0.0;
   out_5003844791385944482[23] = 0.0;
   out_5003844791385944482[24] = 0.0;
   out_5003844791385944482[25] = 0.0;
   out_5003844791385944482[26] = 0.0;
   out_5003844791385944482[27] = 0.0;
   out_5003844791385944482[28] = 0.0;
   out_5003844791385944482[29] = 0.0;
   out_5003844791385944482[30] = 1.0;
   out_5003844791385944482[31] = 0.0;
   out_5003844791385944482[32] = 0.0;
   out_5003844791385944482[33] = 0.0;
   out_5003844791385944482[34] = 0.0;
   out_5003844791385944482[35] = 0.0;
   out_5003844791385944482[36] = 0.0;
   out_5003844791385944482[37] = 0.0;
   out_5003844791385944482[38] = 0.0;
   out_5003844791385944482[39] = 0.0;
   out_5003844791385944482[40] = 1.0;
   out_5003844791385944482[41] = 0.0;
   out_5003844791385944482[42] = 0.0;
   out_5003844791385944482[43] = 0.0;
   out_5003844791385944482[44] = 0.0;
   out_5003844791385944482[45] = 0.0;
   out_5003844791385944482[46] = 0.0;
   out_5003844791385944482[47] = 0.0;
   out_5003844791385944482[48] = 0.0;
   out_5003844791385944482[49] = 0.0;
   out_5003844791385944482[50] = 1.0;
   out_5003844791385944482[51] = 0.0;
   out_5003844791385944482[52] = 0.0;
   out_5003844791385944482[53] = 0.0;
   out_5003844791385944482[54] = 0.0;
   out_5003844791385944482[55] = 0.0;
   out_5003844791385944482[56] = 0.0;
   out_5003844791385944482[57] = 0.0;
   out_5003844791385944482[58] = 0.0;
   out_5003844791385944482[59] = 0.0;
   out_5003844791385944482[60] = 1.0;
   out_5003844791385944482[61] = 0.0;
   out_5003844791385944482[62] = 0.0;
   out_5003844791385944482[63] = 0.0;
   out_5003844791385944482[64] = 0.0;
   out_5003844791385944482[65] = 0.0;
   out_5003844791385944482[66] = 0.0;
   out_5003844791385944482[67] = 0.0;
   out_5003844791385944482[68] = 0.0;
   out_5003844791385944482[69] = 0.0;
   out_5003844791385944482[70] = 1.0;
   out_5003844791385944482[71] = 0.0;
   out_5003844791385944482[72] = 0.0;
   out_5003844791385944482[73] = 0.0;
   out_5003844791385944482[74] = 0.0;
   out_5003844791385944482[75] = 0.0;
   out_5003844791385944482[76] = 0.0;
   out_5003844791385944482[77] = 0.0;
   out_5003844791385944482[78] = 0.0;
   out_5003844791385944482[79] = 0.0;
   out_5003844791385944482[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2539953356409783064) {
   out_2539953356409783064[0] = state[0];
   out_2539953356409783064[1] = state[1];
   out_2539953356409783064[2] = state[2];
   out_2539953356409783064[3] = state[3];
   out_2539953356409783064[4] = state[4];
   out_2539953356409783064[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2539953356409783064[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2539953356409783064[7] = state[7];
   out_2539953356409783064[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7655677773978689580) {
   out_7655677773978689580[0] = 1;
   out_7655677773978689580[1] = 0;
   out_7655677773978689580[2] = 0;
   out_7655677773978689580[3] = 0;
   out_7655677773978689580[4] = 0;
   out_7655677773978689580[5] = 0;
   out_7655677773978689580[6] = 0;
   out_7655677773978689580[7] = 0;
   out_7655677773978689580[8] = 0;
   out_7655677773978689580[9] = 0;
   out_7655677773978689580[10] = 1;
   out_7655677773978689580[11] = 0;
   out_7655677773978689580[12] = 0;
   out_7655677773978689580[13] = 0;
   out_7655677773978689580[14] = 0;
   out_7655677773978689580[15] = 0;
   out_7655677773978689580[16] = 0;
   out_7655677773978689580[17] = 0;
   out_7655677773978689580[18] = 0;
   out_7655677773978689580[19] = 0;
   out_7655677773978689580[20] = 1;
   out_7655677773978689580[21] = 0;
   out_7655677773978689580[22] = 0;
   out_7655677773978689580[23] = 0;
   out_7655677773978689580[24] = 0;
   out_7655677773978689580[25] = 0;
   out_7655677773978689580[26] = 0;
   out_7655677773978689580[27] = 0;
   out_7655677773978689580[28] = 0;
   out_7655677773978689580[29] = 0;
   out_7655677773978689580[30] = 1;
   out_7655677773978689580[31] = 0;
   out_7655677773978689580[32] = 0;
   out_7655677773978689580[33] = 0;
   out_7655677773978689580[34] = 0;
   out_7655677773978689580[35] = 0;
   out_7655677773978689580[36] = 0;
   out_7655677773978689580[37] = 0;
   out_7655677773978689580[38] = 0;
   out_7655677773978689580[39] = 0;
   out_7655677773978689580[40] = 1;
   out_7655677773978689580[41] = 0;
   out_7655677773978689580[42] = 0;
   out_7655677773978689580[43] = 0;
   out_7655677773978689580[44] = 0;
   out_7655677773978689580[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7655677773978689580[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7655677773978689580[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7655677773978689580[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7655677773978689580[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7655677773978689580[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7655677773978689580[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7655677773978689580[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7655677773978689580[53] = -9.8100000000000005*dt;
   out_7655677773978689580[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7655677773978689580[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7655677773978689580[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7655677773978689580[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7655677773978689580[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7655677773978689580[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7655677773978689580[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7655677773978689580[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7655677773978689580[62] = 0;
   out_7655677773978689580[63] = 0;
   out_7655677773978689580[64] = 0;
   out_7655677773978689580[65] = 0;
   out_7655677773978689580[66] = 0;
   out_7655677773978689580[67] = 0;
   out_7655677773978689580[68] = 0;
   out_7655677773978689580[69] = 0;
   out_7655677773978689580[70] = 1;
   out_7655677773978689580[71] = 0;
   out_7655677773978689580[72] = 0;
   out_7655677773978689580[73] = 0;
   out_7655677773978689580[74] = 0;
   out_7655677773978689580[75] = 0;
   out_7655677773978689580[76] = 0;
   out_7655677773978689580[77] = 0;
   out_7655677773978689580[78] = 0;
   out_7655677773978689580[79] = 0;
   out_7655677773978689580[80] = 1;
}
void h_25(double *state, double *unused, double *out_1727643108219156348) {
   out_1727643108219156348[0] = state[6];
}
void H_25(double *state, double *unused, double *out_5770292553468151731) {
   out_5770292553468151731[0] = 0;
   out_5770292553468151731[1] = 0;
   out_5770292553468151731[2] = 0;
   out_5770292553468151731[3] = 0;
   out_5770292553468151731[4] = 0;
   out_5770292553468151731[5] = 0;
   out_5770292553468151731[6] = 1;
   out_5770292553468151731[7] = 0;
   out_5770292553468151731[8] = 0;
}
void h_24(double *state, double *unused, double *out_4524050476975214784) {
   out_4524050476975214784[0] = state[4];
   out_4524050476975214784[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6475418840390238459) {
   out_6475418840390238459[0] = 0;
   out_6475418840390238459[1] = 0;
   out_6475418840390238459[2] = 0;
   out_6475418840390238459[3] = 0;
   out_6475418840390238459[4] = 1;
   out_6475418840390238459[5] = 0;
   out_6475418840390238459[6] = 0;
   out_6475418840390238459[7] = 0;
   out_6475418840390238459[8] = 0;
   out_6475418840390238459[9] = 0;
   out_6475418840390238459[10] = 0;
   out_6475418840390238459[11] = 0;
   out_6475418840390238459[12] = 0;
   out_6475418840390238459[13] = 0;
   out_6475418840390238459[14] = 1;
   out_6475418840390238459[15] = 0;
   out_6475418840390238459[16] = 0;
   out_6475418840390238459[17] = 0;
}
void h_30(double *state, double *unused, double *out_90439028039008013) {
   out_90439028039008013[0] = state[4];
}
void H_30(double *state, double *unused, double *out_8148755190113791687) {
   out_8148755190113791687[0] = 0;
   out_8148755190113791687[1] = 0;
   out_8148755190113791687[2] = 0;
   out_8148755190113791687[3] = 0;
   out_8148755190113791687[4] = 1;
   out_8148755190113791687[5] = 0;
   out_8148755190113791687[6] = 0;
   out_8148755190113791687[7] = 0;
   out_8148755190113791687[8] = 0;
}
void h_26(double *state, double *unused, double *out_1938532702514813353) {
   out_1938532702514813353[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8934948201367343661) {
   out_8934948201367343661[0] = 0;
   out_8934948201367343661[1] = 0;
   out_8934948201367343661[2] = 0;
   out_8934948201367343661[3] = 0;
   out_8934948201367343661[4] = 0;
   out_8934948201367343661[5] = 0;
   out_8934948201367343661[6] = 0;
   out_8934948201367343661[7] = 1;
   out_8934948201367343661[8] = 0;
}
void h_27(double *state, double *unused, double *out_2553920733024504160) {
   out_2553920733024504160[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8074394812411816712) {
   out_8074394812411816712[0] = 0;
   out_8074394812411816712[1] = 0;
   out_8074394812411816712[2] = 0;
   out_8074394812411816712[3] = 1;
   out_8074394812411816712[4] = 0;
   out_8074394812411816712[5] = 0;
   out_8074394812411816712[6] = 0;
   out_8074394812411816712[7] = 0;
   out_8074394812411816712[8] = 0;
}
void h_29(double *state, double *unused, double *out_1033948880940670448) {
   out_1033948880940670448[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8658986534428183871) {
   out_8658986534428183871[0] = 0;
   out_8658986534428183871[1] = 1;
   out_8658986534428183871[2] = 0;
   out_8658986534428183871[3] = 0;
   out_8658986534428183871[4] = 0;
   out_8658986534428183871[5] = 0;
   out_8658986534428183871[6] = 0;
   out_8658986534428183871[7] = 0;
   out_8658986534428183871[8] = 0;
}
void h_28(double *state, double *unused, double *out_3913548264033873988) {
   out_3913548264033873988[0] = state[0];
}
void H_28(double *state, double *unused, double *out_3576587517358653297) {
   out_3576587517358653297[0] = 1;
   out_3576587517358653297[1] = 0;
   out_3576587517358653297[2] = 0;
   out_3576587517358653297[3] = 0;
   out_3576587517358653297[4] = 0;
   out_3576587517358653297[5] = 0;
   out_3576587517358653297[6] = 0;
   out_3576587517358653297[7] = 0;
   out_3576587517358653297[8] = 0;
}
void h_31(double *state, double *unused, double *out_7253700544770179461) {
   out_7253700544770179461[0] = state[8];
}
void H_31(double *state, double *unused, double *out_5739646591591191303) {
   out_5739646591591191303[0] = 0;
   out_5739646591591191303[1] = 0;
   out_5739646591591191303[2] = 0;
   out_5739646591591191303[3] = 0;
   out_5739646591591191303[4] = 0;
   out_5739646591591191303[5] = 0;
   out_5739646591591191303[6] = 0;
   out_5739646591591191303[7] = 0;
   out_5739646591591191303[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_8290791895352476901) {
  err_fun(nom_x, delta_x, out_8290791895352476901);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3328957974600116526) {
  inv_err_fun(nom_x, true_x, out_3328957974600116526);
}
void car_H_mod_fun(double *state, double *out_5003844791385944482) {
  H_mod_fun(state, out_5003844791385944482);
}
void car_f_fun(double *state, double dt, double *out_2539953356409783064) {
  f_fun(state,  dt, out_2539953356409783064);
}
void car_F_fun(double *state, double dt, double *out_7655677773978689580) {
  F_fun(state,  dt, out_7655677773978689580);
}
void car_h_25(double *state, double *unused, double *out_1727643108219156348) {
  h_25(state, unused, out_1727643108219156348);
}
void car_H_25(double *state, double *unused, double *out_5770292553468151731) {
  H_25(state, unused, out_5770292553468151731);
}
void car_h_24(double *state, double *unused, double *out_4524050476975214784) {
  h_24(state, unused, out_4524050476975214784);
}
void car_H_24(double *state, double *unused, double *out_6475418840390238459) {
  H_24(state, unused, out_6475418840390238459);
}
void car_h_30(double *state, double *unused, double *out_90439028039008013) {
  h_30(state, unused, out_90439028039008013);
}
void car_H_30(double *state, double *unused, double *out_8148755190113791687) {
  H_30(state, unused, out_8148755190113791687);
}
void car_h_26(double *state, double *unused, double *out_1938532702514813353) {
  h_26(state, unused, out_1938532702514813353);
}
void car_H_26(double *state, double *unused, double *out_8934948201367343661) {
  H_26(state, unused, out_8934948201367343661);
}
void car_h_27(double *state, double *unused, double *out_2553920733024504160) {
  h_27(state, unused, out_2553920733024504160);
}
void car_H_27(double *state, double *unused, double *out_8074394812411816712) {
  H_27(state, unused, out_8074394812411816712);
}
void car_h_29(double *state, double *unused, double *out_1033948880940670448) {
  h_29(state, unused, out_1033948880940670448);
}
void car_H_29(double *state, double *unused, double *out_8658986534428183871) {
  H_29(state, unused, out_8658986534428183871);
}
void car_h_28(double *state, double *unused, double *out_3913548264033873988) {
  h_28(state, unused, out_3913548264033873988);
}
void car_H_28(double *state, double *unused, double *out_3576587517358653297) {
  H_28(state, unused, out_3576587517358653297);
}
void car_h_31(double *state, double *unused, double *out_7253700544770179461) {
  h_31(state, unused, out_7253700544770179461);
}
void car_H_31(double *state, double *unused, double *out_5739646591591191303) {
  H_31(state, unused, out_5739646591591191303);
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
