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
void car_err_fun(double *nom_x, double *delta_x, double *out_4102855695027319146);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_375370046560025251);
void car_H_mod_fun(double *state, double *out_4142214806030893418);
void car_f_fun(double *state, double dt, double *out_1332366097619626209);
void car_F_fun(double *state, double dt, double *out_2970389157093285155);
void car_h_25(double *state, double *unused, double *out_3102286071066017000);
void car_H_25(double *state, double *unused, double *out_7624833147842353287);
void car_h_24(double *state, double *unused, double *out_423096547607875781);
void car_H_24(double *state, double *unused, double *out_5399125363863484725);
void car_h_30(double *state, double *unused, double *out_3668549155284333936);
void car_H_30(double *state, double *unused, double *out_708142806350736532);
void car_h_26(double *state, double *unused, double *out_7985951944793485901);
void car_H_26(double *state, double *unused, double *out_7080407606993142105);
void car_h_27(double *state, double *unused, double *out_8103959338726862645);
void car_H_27(double *state, double *unused, double *out_2882906118151161443);
void car_h_29(double *state, double *unused, double *out_6653327946097979478);
void car_H_29(double *state, double *unused, double *out_197911462036344348);
void car_h_28(double *state, double *unused, double *out_5499554017918164994);
void car_H_28(double *state, double *unused, double *out_8768076211619308566);
void car_h_31(double *state, double *unused, double *out_7581192745822862175);
void car_H_31(double *state, double *unused, double *out_7594187185965392859);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}