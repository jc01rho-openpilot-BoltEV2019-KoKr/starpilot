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
void car_err_fun(double *nom_x, double *delta_x, double *out_3403548426686276780);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8258286328329043480);
void car_H_mod_fun(double *state, double *out_1856540843006378518);
void car_f_fun(double *state, double dt, double *out_2705110536690145384);
void car_F_fun(double *state, double dt, double *out_8630494868968096727);
void car_h_25(double *state, double *unused, double *out_5878308228618872770);
void car_H_25(double *state, double *unused, double *out_8100833558474599855);
void car_h_24(double *state, double *unused, double *out_4629452303819786169);
void car_H_24(double *state, double *unused, double *out_6363587363837183863);
void car_h_30(double *state, double *unused, double *out_892526997731478166);
void car_H_30(double *state, double *unused, double *out_5582500599967351228);
void car_h_26(double *state, double *unused, double *out_275216803344663571);
void car_H_26(double *state, double *unused, double *out_6604407196360895537);
void car_h_27(double *state, double *unused, double *out_8170483763809049834);
void car_H_27(double *state, double *unused, double *out_7757263911767776139);
void car_h_29(double *state, double *unused, double *out_289211113055000649);
void car_H_29(double *state, double *unused, double *out_5072269255652959044);
void car_h_28(double *state, double *unused, double *out_9189533661544037455);
void car_H_28(double *state, double *unused, double *out_8292075800987061998);
void car_h_31(double *state, double *unused, double *out_1637137513985633787);
void car_H_31(double *state, double *unused, double *out_5978199094127544061);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}