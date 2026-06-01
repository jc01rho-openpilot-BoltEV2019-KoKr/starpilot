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
void car_err_fun(double *nom_x, double *delta_x, double *out_1626624007171975298);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3841721694315715550);
void car_H_mod_fun(double *state, double *out_7646044064038577504);
void car_f_fun(double *state, double dt, double *out_3692802059814366209);
void car_F_fun(double *state, double dt, double *out_6278869713612932388);
void car_h_25(double *state, double *unused, double *out_1903293770744417105);
void car_H_25(double *state, double *unused, double *out_1607511783758736875);
void car_h_24(double *state, double *unused, double *out_3019943109680816786);
void car_H_24(double *state, double *unused, double *out_565137815246762691);
void car_h_30(double *state, double *unused, double *out_5540743298998439455);
void car_H_30(double *state, double *unused, double *out_4125844742265985502);
void car_h_26(double *state, double *unused, double *out_539070031337593810);
void car_H_26(double *state, double *unused, double *out_2133991535115319349);
void car_h_27(double *state, double *unused, double *out_7078675401262423660);
void car_H_27(double *state, double *unused, double *out_1951081430465560591);
void car_h_29(double *state, double *unused, double *out_4597233446096777020);
void car_H_29(double *state, double *unused, double *out_4636076086580377686);
void car_h_28(double *state, double *unused, double *out_2077002133601578015);
void car_H_28(double *state, double *unused, double *out_446322930489152888);
void car_h_31(double *state, double *unused, double *out_7817026797415165478);
void car_H_31(double *state, double *unused, double *out_2760199637348670825);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}