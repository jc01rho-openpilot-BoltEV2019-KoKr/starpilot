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
void err_fun(double *nom_x, double *delta_x, double *out_3955673683859984289) {
   out_3955673683859984289[0] = delta_x[0] + nom_x[0];
   out_3955673683859984289[1] = delta_x[1] + nom_x[1];
   out_3955673683859984289[2] = delta_x[2] + nom_x[2];
   out_3955673683859984289[3] = delta_x[3] + nom_x[3];
   out_3955673683859984289[4] = delta_x[4] + nom_x[4];
   out_3955673683859984289[5] = delta_x[5] + nom_x[5];
   out_3955673683859984289[6] = delta_x[6] + nom_x[6];
   out_3955673683859984289[7] = delta_x[7] + nom_x[7];
   out_3955673683859984289[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8970258583381717138) {
   out_8970258583381717138[0] = -nom_x[0] + true_x[0];
   out_8970258583381717138[1] = -nom_x[1] + true_x[1];
   out_8970258583381717138[2] = -nom_x[2] + true_x[2];
   out_8970258583381717138[3] = -nom_x[3] + true_x[3];
   out_8970258583381717138[4] = -nom_x[4] + true_x[4];
   out_8970258583381717138[5] = -nom_x[5] + true_x[5];
   out_8970258583381717138[6] = -nom_x[6] + true_x[6];
   out_8970258583381717138[7] = -nom_x[7] + true_x[7];
   out_8970258583381717138[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4831252241531258142) {
   out_4831252241531258142[0] = 1.0;
   out_4831252241531258142[1] = 0.0;
   out_4831252241531258142[2] = 0.0;
   out_4831252241531258142[3] = 0.0;
   out_4831252241531258142[4] = 0.0;
   out_4831252241531258142[5] = 0.0;
   out_4831252241531258142[6] = 0.0;
   out_4831252241531258142[7] = 0.0;
   out_4831252241531258142[8] = 0.0;
   out_4831252241531258142[9] = 0.0;
   out_4831252241531258142[10] = 1.0;
   out_4831252241531258142[11] = 0.0;
   out_4831252241531258142[12] = 0.0;
   out_4831252241531258142[13] = 0.0;
   out_4831252241531258142[14] = 0.0;
   out_4831252241531258142[15] = 0.0;
   out_4831252241531258142[16] = 0.0;
   out_4831252241531258142[17] = 0.0;
   out_4831252241531258142[18] = 0.0;
   out_4831252241531258142[19] = 0.0;
   out_4831252241531258142[20] = 1.0;
   out_4831252241531258142[21] = 0.0;
   out_4831252241531258142[22] = 0.0;
   out_4831252241531258142[23] = 0.0;
   out_4831252241531258142[24] = 0.0;
   out_4831252241531258142[25] = 0.0;
   out_4831252241531258142[26] = 0.0;
   out_4831252241531258142[27] = 0.0;
   out_4831252241531258142[28] = 0.0;
   out_4831252241531258142[29] = 0.0;
   out_4831252241531258142[30] = 1.0;
   out_4831252241531258142[31] = 0.0;
   out_4831252241531258142[32] = 0.0;
   out_4831252241531258142[33] = 0.0;
   out_4831252241531258142[34] = 0.0;
   out_4831252241531258142[35] = 0.0;
   out_4831252241531258142[36] = 0.0;
   out_4831252241531258142[37] = 0.0;
   out_4831252241531258142[38] = 0.0;
   out_4831252241531258142[39] = 0.0;
   out_4831252241531258142[40] = 1.0;
   out_4831252241531258142[41] = 0.0;
   out_4831252241531258142[42] = 0.0;
   out_4831252241531258142[43] = 0.0;
   out_4831252241531258142[44] = 0.0;
   out_4831252241531258142[45] = 0.0;
   out_4831252241531258142[46] = 0.0;
   out_4831252241531258142[47] = 0.0;
   out_4831252241531258142[48] = 0.0;
   out_4831252241531258142[49] = 0.0;
   out_4831252241531258142[50] = 1.0;
   out_4831252241531258142[51] = 0.0;
   out_4831252241531258142[52] = 0.0;
   out_4831252241531258142[53] = 0.0;
   out_4831252241531258142[54] = 0.0;
   out_4831252241531258142[55] = 0.0;
   out_4831252241531258142[56] = 0.0;
   out_4831252241531258142[57] = 0.0;
   out_4831252241531258142[58] = 0.0;
   out_4831252241531258142[59] = 0.0;
   out_4831252241531258142[60] = 1.0;
   out_4831252241531258142[61] = 0.0;
   out_4831252241531258142[62] = 0.0;
   out_4831252241531258142[63] = 0.0;
   out_4831252241531258142[64] = 0.0;
   out_4831252241531258142[65] = 0.0;
   out_4831252241531258142[66] = 0.0;
   out_4831252241531258142[67] = 0.0;
   out_4831252241531258142[68] = 0.0;
   out_4831252241531258142[69] = 0.0;
   out_4831252241531258142[70] = 1.0;
   out_4831252241531258142[71] = 0.0;
   out_4831252241531258142[72] = 0.0;
   out_4831252241531258142[73] = 0.0;
   out_4831252241531258142[74] = 0.0;
   out_4831252241531258142[75] = 0.0;
   out_4831252241531258142[76] = 0.0;
   out_4831252241531258142[77] = 0.0;
   out_4831252241531258142[78] = 0.0;
   out_4831252241531258142[79] = 0.0;
   out_4831252241531258142[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2508158103842919927) {
   out_2508158103842919927[0] = state[0];
   out_2508158103842919927[1] = state[1];
   out_2508158103842919927[2] = state[2];
   out_2508158103842919927[3] = state[3];
   out_2508158103842919927[4] = state[4];
   out_2508158103842919927[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2508158103842919927[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2508158103842919927[7] = state[7];
   out_2508158103842919927[8] = state[8];
}
void F_fun(double *state, double dt, double *out_619119889307979727) {
   out_619119889307979727[0] = 1;
   out_619119889307979727[1] = 0;
   out_619119889307979727[2] = 0;
   out_619119889307979727[3] = 0;
   out_619119889307979727[4] = 0;
   out_619119889307979727[5] = 0;
   out_619119889307979727[6] = 0;
   out_619119889307979727[7] = 0;
   out_619119889307979727[8] = 0;
   out_619119889307979727[9] = 0;
   out_619119889307979727[10] = 1;
   out_619119889307979727[11] = 0;
   out_619119889307979727[12] = 0;
   out_619119889307979727[13] = 0;
   out_619119889307979727[14] = 0;
   out_619119889307979727[15] = 0;
   out_619119889307979727[16] = 0;
   out_619119889307979727[17] = 0;
   out_619119889307979727[18] = 0;
   out_619119889307979727[19] = 0;
   out_619119889307979727[20] = 1;
   out_619119889307979727[21] = 0;
   out_619119889307979727[22] = 0;
   out_619119889307979727[23] = 0;
   out_619119889307979727[24] = 0;
   out_619119889307979727[25] = 0;
   out_619119889307979727[26] = 0;
   out_619119889307979727[27] = 0;
   out_619119889307979727[28] = 0;
   out_619119889307979727[29] = 0;
   out_619119889307979727[30] = 1;
   out_619119889307979727[31] = 0;
   out_619119889307979727[32] = 0;
   out_619119889307979727[33] = 0;
   out_619119889307979727[34] = 0;
   out_619119889307979727[35] = 0;
   out_619119889307979727[36] = 0;
   out_619119889307979727[37] = 0;
   out_619119889307979727[38] = 0;
   out_619119889307979727[39] = 0;
   out_619119889307979727[40] = 1;
   out_619119889307979727[41] = 0;
   out_619119889307979727[42] = 0;
   out_619119889307979727[43] = 0;
   out_619119889307979727[44] = 0;
   out_619119889307979727[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_619119889307979727[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_619119889307979727[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_619119889307979727[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_619119889307979727[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_619119889307979727[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_619119889307979727[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_619119889307979727[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_619119889307979727[53] = -9.8100000000000005*dt;
   out_619119889307979727[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_619119889307979727[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_619119889307979727[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_619119889307979727[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_619119889307979727[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_619119889307979727[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_619119889307979727[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_619119889307979727[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_619119889307979727[62] = 0;
   out_619119889307979727[63] = 0;
   out_619119889307979727[64] = 0;
   out_619119889307979727[65] = 0;
   out_619119889307979727[66] = 0;
   out_619119889307979727[67] = 0;
   out_619119889307979727[68] = 0;
   out_619119889307979727[69] = 0;
   out_619119889307979727[70] = 1;
   out_619119889307979727[71] = 0;
   out_619119889307979727[72] = 0;
   out_619119889307979727[73] = 0;
   out_619119889307979727[74] = 0;
   out_619119889307979727[75] = 0;
   out_619119889307979727[76] = 0;
   out_619119889307979727[77] = 0;
   out_619119889307979727[78] = 0;
   out_619119889307979727[79] = 0;
   out_619119889307979727[80] = 1;
}
void h_25(double *state, double *unused, double *out_7300303321148015441) {
   out_7300303321148015441[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3882131319502775933) {
   out_3882131319502775933[0] = 0;
   out_3882131319502775933[1] = 0;
   out_3882131319502775933[2] = 0;
   out_3882131319502775933[3] = 0;
   out_3882131319502775933[4] = 0;
   out_3882131319502775933[5] = 0;
   out_3882131319502775933[6] = 1;
   out_3882131319502775933[7] = 0;
   out_3882131319502775933[8] = 0;
}
void h_24(double *state, double *unused, double *out_7158441455227347179) {
   out_7158441455227347179[0] = state[4];
   out_7158441455227347179[1] = state[5];
}
void H_24(double *state, double *unused, double *out_1656423535523907371) {
   out_1656423535523907371[0] = 0;
   out_1656423535523907371[1] = 0;
   out_1656423535523907371[2] = 0;
   out_1656423535523907371[3] = 0;
   out_1656423535523907371[4] = 1;
   out_1656423535523907371[5] = 0;
   out_1656423535523907371[6] = 0;
   out_1656423535523907371[7] = 0;
   out_1656423535523907371[8] = 0;
   out_1656423535523907371[9] = 0;
   out_1656423535523907371[10] = 0;
   out_1656423535523907371[11] = 0;
   out_1656423535523907371[12] = 0;
   out_1656423535523907371[13] = 0;
   out_1656423535523907371[14] = 1;
   out_1656423535523907371[15] = 0;
   out_1656423535523907371[16] = 0;
   out_1656423535523907371[17] = 0;
}
void h_30(double *state, double *unused, double *out_7508991224307513825) {
   out_7508991224307513825[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3034559021988840822) {
   out_3034559021988840822[0] = 0;
   out_3034559021988840822[1] = 0;
   out_3034559021988840822[2] = 0;
   out_3034559021988840822[3] = 0;
   out_3034559021988840822[4] = 1;
   out_3034559021988840822[5] = 0;
   out_3034559021988840822[6] = 0;
   out_3034559021988840822[7] = 0;
   out_3034559021988840822[8] = 0;
}
void h_26(double *state, double *unused, double *out_5818543389571832865) {
   out_5818543389571832865[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7623634638376832157) {
   out_7623634638376832157[0] = 0;
   out_7623634638376832157[1] = 0;
   out_7623634638376832157[2] = 0;
   out_7623634638376832157[3] = 0;
   out_7623634638376832157[4] = 0;
   out_7623634638376832157[5] = 0;
   out_7623634638376832157[6] = 0;
   out_7623634638376832157[7] = 1;
   out_7623634638376832157[8] = 0;
}
void h_27(double *state, double *unused, double *out_4263517269703682756) {
   out_4263517269703682756[0] = state[3];
}
void H_27(double *state, double *unused, double *out_859795710188415911) {
   out_859795710188415911[0] = 0;
   out_859795710188415911[1] = 0;
   out_859795710188415911[2] = 0;
   out_859795710188415911[3] = 1;
   out_859795710188415911[4] = 0;
   out_859795710188415911[5] = 0;
   out_859795710188415911[6] = 0;
   out_859795710188415911[7] = 0;
   out_859795710188415911[8] = 0;
}
void h_29(double *state, double *unused, double *out_2507317956646668180) {
   out_2507317956646668180[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3544790366303233006) {
   out_3544790366303233006[0] = 0;
   out_3544790366303233006[1] = 1;
   out_3544790366303233006[2] = 0;
   out_3544790366303233006[3] = 0;
   out_3544790366303233006[4] = 0;
   out_3544790366303233006[5] = 0;
   out_3544790366303233006[6] = 0;
   out_3544790366303233006[7] = 0;
   out_3544790366303233006[8] = 0;
}
void h_28(double *state, double *unused, double *out_8661469350985311768) {
   out_8661469350985311768[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1537608650766297568) {
   out_1537608650766297568[0] = 1;
   out_1537608650766297568[1] = 0;
   out_1537608650766297568[2] = 0;
   out_1537608650766297568[3] = 0;
   out_1537608650766297568[4] = 0;
   out_1537608650766297568[5] = 0;
   out_1537608650766297568[6] = 0;
   out_1537608650766297568[7] = 0;
   out_1537608650766297568[8] = 0;
}
void h_31(double *state, double *unused, double *out_7025109258863509552) {
   out_7025109258863509552[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3851485357625815505) {
   out_3851485357625815505[0] = 0;
   out_3851485357625815505[1] = 0;
   out_3851485357625815505[2] = 0;
   out_3851485357625815505[3] = 0;
   out_3851485357625815505[4] = 0;
   out_3851485357625815505[5] = 0;
   out_3851485357625815505[6] = 0;
   out_3851485357625815505[7] = 0;
   out_3851485357625815505[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_3955673683859984289) {
  err_fun(nom_x, delta_x, out_3955673683859984289);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8970258583381717138) {
  inv_err_fun(nom_x, true_x, out_8970258583381717138);
}
void car_H_mod_fun(double *state, double *out_4831252241531258142) {
  H_mod_fun(state, out_4831252241531258142);
}
void car_f_fun(double *state, double dt, double *out_2508158103842919927) {
  f_fun(state,  dt, out_2508158103842919927);
}
void car_F_fun(double *state, double dt, double *out_619119889307979727) {
  F_fun(state,  dt, out_619119889307979727);
}
void car_h_25(double *state, double *unused, double *out_7300303321148015441) {
  h_25(state, unused, out_7300303321148015441);
}
void car_H_25(double *state, double *unused, double *out_3882131319502775933) {
  H_25(state, unused, out_3882131319502775933);
}
void car_h_24(double *state, double *unused, double *out_7158441455227347179) {
  h_24(state, unused, out_7158441455227347179);
}
void car_H_24(double *state, double *unused, double *out_1656423535523907371) {
  H_24(state, unused, out_1656423535523907371);
}
void car_h_30(double *state, double *unused, double *out_7508991224307513825) {
  h_30(state, unused, out_7508991224307513825);
}
void car_H_30(double *state, double *unused, double *out_3034559021988840822) {
  H_30(state, unused, out_3034559021988840822);
}
void car_h_26(double *state, double *unused, double *out_5818543389571832865) {
  h_26(state, unused, out_5818543389571832865);
}
void car_H_26(double *state, double *unused, double *out_7623634638376832157) {
  H_26(state, unused, out_7623634638376832157);
}
void car_h_27(double *state, double *unused, double *out_4263517269703682756) {
  h_27(state, unused, out_4263517269703682756);
}
void car_H_27(double *state, double *unused, double *out_859795710188415911) {
  H_27(state, unused, out_859795710188415911);
}
void car_h_29(double *state, double *unused, double *out_2507317956646668180) {
  h_29(state, unused, out_2507317956646668180);
}
void car_H_29(double *state, double *unused, double *out_3544790366303233006) {
  H_29(state, unused, out_3544790366303233006);
}
void car_h_28(double *state, double *unused, double *out_8661469350985311768) {
  h_28(state, unused, out_8661469350985311768);
}
void car_H_28(double *state, double *unused, double *out_1537608650766297568) {
  H_28(state, unused, out_1537608650766297568);
}
void car_h_31(double *state, double *unused, double *out_7025109258863509552) {
  h_31(state, unused, out_7025109258863509552);
}
void car_H_31(double *state, double *unused, double *out_3851485357625815505) {
  H_31(state, unused, out_3851485357625815505);
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
