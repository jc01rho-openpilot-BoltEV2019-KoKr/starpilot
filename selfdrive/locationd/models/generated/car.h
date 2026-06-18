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
void car_err_fun(double *nom_x, double *delta_x, double *out_7839106046248465839);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_31659364612209693);
void car_H_mod_fun(double *state, double *out_6082546015176302038);
void car_f_fun(double *state, double dt, double *out_6850955649577617071);
void car_F_fun(double *state, double dt, double *out_6972181184240044918);
void car_h_25(double *state, double *unused, double *out_6429787098118084800);
void car_H_25(double *state, double *unused, double *out_3171009832621012341);
void car_h_24(double *state, double *unused, double *out_6701597119184761045);
void car_H_24(double *state, double *unused, double *out_998360233615512775);
void car_h_30(double *state, double *unused, double *out_5049641810910434322);
void car_H_30(double *state, double *unused, double *out_8359043899596922520);
void car_h_26(double *state, double *unused, double *out_1349399706503414824);
void car_H_26(double *state, double *unused, double *out_570493486253043883);
void car_h_27(double *state, double *unused, double *out_1467407100436791568);
void car_H_27(double *state, double *unused, double *out_866907573677347360);
void car_h_29(double *state, double *unused, double *out_5993151663812096757);
void car_H_29(double *state, double *unused, double *out_846455153192203673);
void car_h_28(double *state, double *unused, double *out_1136998220371906083);
void car_H_28(double *state, double *unused, double *out_1117175118373122578);
void car_h_31(double *state, double *unused, double *out_4228999089596618364);
void car_H_31(double *state, double *unused, double *out_3201655794497972769);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}