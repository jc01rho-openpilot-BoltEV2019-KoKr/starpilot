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
void car_err_fun(double *nom_x, double *delta_x, double *out_4317163891516196670);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8278424519720112087);
void car_H_mod_fun(double *state, double *out_319627375497114494);
void car_f_fun(double *state, double dt, double *out_6613977481805234540);
void car_F_fun(double *state, double dt, double *out_3393066705725541618);
void car_h_25(double *state, double *unused, double *out_3694283988136956896);
void car_H_25(double *state, double *unused, double *out_8933928472300199885);
void car_h_24(double *state, double *unused, double *out_878940354647202481);
void car_H_24(double *state, double *unused, double *out_7287107817430483169);
void car_h_30(double *state, double *unused, double *out_9220341424687980009);
void car_H_30(double *state, double *unused, double *out_2596125259917734976);
void car_h_26(double *state, double *unused, double *out_4022405810528928524);
void car_H_26(double *state, double *unused, double *out_5192425153426143661);
void car_h_27(double *state, double *unused, double *out_4139954033073310033);
void car_H_27(double *state, double *unused, double *out_4770888571718159887);
void car_h_29(double *state, double *unused, double *out_6621997328212873956);
void car_H_29(double *state, double *unused, double *out_2085893915603342792);
void car_h_28(double *state, double *unused, double *out_8099632253155620528);
void car_H_28(double *state, double *unused, double *out_7168292932672873366);
void car_h_31(double *state, double *unused, double *out_5443433296546894286);
void car_H_31(double *state, double *unused, double *out_8964574434177160313);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}