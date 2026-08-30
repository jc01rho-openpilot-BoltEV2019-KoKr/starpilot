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
void car_err_fun(double *nom_x, double *delta_x, double *out_1982741958495934934);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1965858196176103805);
void car_H_mod_fun(double *state, double *out_7322816943518629238);
void car_f_fun(double *state, double dt, double *out_6429621653186063469);
void car_F_fun(double *state, double dt, double *out_4451613020495234820);
void car_h_25(double *state, double *unused, double *out_5140546513771631716);
void car_H_25(double *state, double *unused, double *out_1930738904278685141);
void car_h_24(double *state, double *unused, double *out_867003127290538570);
void car_H_24(double *state, double *unused, double *out_4156446688257553703);
void car_h_30(double *state, double *unused, double *out_5297733182122760861);
void car_H_30(double *state, double *unused, double *out_8847429245770301896);
void car_h_26(double *state, double *unused, double *out_8147337623925945110);
void car_H_26(double *state, double *unused, double *out_1810764414595371083);
void car_h_27(double *state, double *unused, double *out_217345790508090885);
void car_H_27(double *state, double *unused, double *out_6672665933969876985);
void car_h_29(double *state, double *unused, double *out_675547152666652547);
void car_H_29(double *state, double *unused, double *out_9089083483624857536);
void car_h_28(double *state, double *unused, double *out_4927544272607556652);
void car_H_28(double *state, double *unused, double *out_123095809969204622);
void car_h_31(double *state, double *unused, double *out_2544246198651735911);
void car_H_31(double *state, double *unused, double *out_1961384866155645569);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}