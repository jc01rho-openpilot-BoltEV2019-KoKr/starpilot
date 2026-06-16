#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_7709214462285076644);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_181432404984807710);
void car_H_mod_fun(double *state, double *out_8282876149494425233);
void car_f_fun(double *state, double dt, double *out_1683945396559752472);
void car_F_fun(double *state, double dt, double *out_239932902801011581);
void car_h_25(double *state, double *unused, double *out_2505292091765311779);
void car_H_25(double *state, double *unused, double *out_910312076417812004);
void car_h_24(double *state, double *unused, double *out_484124202729088643);
void car_H_24(double *state, double *unused, double *out_1315395707561056558);
void car_h_30(double *state, double *unused, double *out_2556252205875338366);
void car_H_30(double *state, double *unused, double *out_6006378265073804751);
void car_h_26(double *state, double *unused, double *out_1841699875406290646);
void car_H_26(double *state, double *unused, double *out_4651815395291868228);
void car_h_27(double *state, double *unused, double *out_3893749425648537367);
void car_H_27(double *state, double *unused, double *out_3831614953273379840);
void car_h_29(double *state, double *unused, double *out_7782159421710663313);
void car_H_29(double *state, double *unused, double *out_6516609609388196935);
void car_h_28(double *state, double *unused, double *out_5061493226724679104);
void car_H_28(double *state, double *unused, double *out_1434210592318666361);
void car_h_31(double *state, double *unused, double *out_7444791300680499845);
void car_H_31(double *state, double *unused, double *out_879666114540851576);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}