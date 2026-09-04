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
void car_err_fun(double *nom_x, double *delta_x, double *out_8341138954345272666);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1053229851557441146);
void car_H_mod_fun(double *state, double *out_1742832659992124751);
void car_f_fun(double *state, double dt, double *out_418888185766452101);
void car_F_fun(double *state, double dt, double *out_7332131154779998147);
void car_h_25(double *state, double *unused, double *out_2120117969057149735);
void car_H_25(double *state, double *unused, double *out_6108633137067025220);
void car_h_24(double *state, double *unused, double *out_7094254727358861625);
void car_H_24(double *state, double *unused, double *out_8334340921045893782);
void car_h_30(double *state, double *unused, double *out_4035329226783510394);
void car_H_30(double *state, double *unused, double *out_5421420595150909641);
void car_h_26(double *state, double *unused, double *out_3432013342107032877);
void car_H_26(double *state, double *unused, double *out_2367129818192968996);
void car_h_27(double *state, double *unused, double *out_4789453276872201226);
void car_H_27(double *state, double *unused, double *out_7596183906951334552);
void car_h_29(double *state, double *unused, double *out_8533129359367326134);
void car_H_29(double *state, double *unused, double *out_4911189250836517457);
void car_h_28(double *state, double *unused, double *out_212219990788644419);
void car_H_28(double *state, double *unused, double *out_4054798422819135457);
void car_h_31(double *state, double *unused, double *out_6046731432492005227);
void car_H_31(double *state, double *unused, double *out_6139279098943985648);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}