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
void car_err_fun(double *nom_x, double *delta_x, double *out_4080197981179722536);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3164357961811210311);
void car_H_mod_fun(double *state, double *out_4408837966520463957);
void car_f_fun(double *state, double dt, double *out_5836050664863580465);
void car_F_fun(double *state, double dt, double *out_584824642242628871);
void car_h_25(double *state, double *unused, double *out_3846550558690327557);
void car_H_25(double *state, double *unused, double *out_3533529222181460977);
void car_h_24(double *state, double *unused, double *out_5575782566501311775);
void car_H_24(double *state, double *unused, double *out_24396376620862159);
void car_h_30(double *state, double *unused, double *out_6794276549045812518);
void car_H_30(double *state, double *unused, double *out_1015196263674212350);
void car_h_26(double *state, double *unused, double *out_9048062203855041447);
void car_H_26(double *state, double *unused, double *out_229003252420660376);
void car_h_27(double *state, double *unused, double *out_5135418613316513208);
void car_H_27(double *state, double *unused, double *out_3189959575474637261);
void car_h_29(double *state, double *unused, double *out_5850766696144150083);
void car_H_29(double *state, double *unused, double *out_504964919359820166);
void car_h_28(double *state, double *unused, double *out_133745345655667563);
void car_H_28(double *state, double *unused, double *out_5587363936429350740);
void car_h_31(double *state, double *unused, double *out_4672202664478170413);
void car_H_31(double *state, double *unused, double *out_7901240643288868677);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}