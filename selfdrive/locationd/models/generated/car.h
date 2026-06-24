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
void car_err_fun(double *nom_x, double *delta_x, double *out_6972961942535496334);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2104979621458798626);
void car_H_mod_fun(double *state, double *out_2779658660641459178);
void car_f_fun(double *state, double dt, double *out_1847838116479859502);
void car_F_fun(double *state, double dt, double *out_8278586360493195906);
void car_h_25(double *state, double *unused, double *out_4623448408360880072);
void car_H_25(double *state, double *unused, double *out_2013210898559251929);
void car_h_24(double *state, double *unused, double *out_5136059034754269087);
void car_H_24(double *state, double *unused, double *out_7286705181472264523);
void car_h_30(double *state, double *unused, double *out_5183418188630129660);
void car_H_30(double *state, double *unused, double *out_2514485431568356269);
void car_h_26(double *state, double *unused, double *out_8220204240074462345);
void car_H_26(double *state, double *unused, double *out_1728292420314804295);
void car_h_27(double *state, double *unused, double *out_6443570481160411950);
void car_H_27(double *state, double *unused, double *out_4689248743368781180);
void car_h_29(double *state, double *unused, double *out_4239908335728467225);
void car_H_29(double *state, double *unused, double *out_2004254087253964085);
void car_h_28(double *state, double *unused, double *out_8966387541104806981);
void car_H_28(double *state, double *unused, double *out_7086653104323494659);
void car_h_31(double *state, double *unused, double *out_8508687616659686337);
void car_H_31(double *state, double *unused, double *out_2354500522548155771);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}