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
void car_err_fun(double *nom_x, double *delta_x, double *out_3959736040406304353);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7899142377712818401);
void car_H_mod_fun(double *state, double *out_8853016966935855995);
void car_f_fun(double *state, double dt, double *out_8070155753173713130);
void car_F_fun(double *state, double dt, double *out_2319703520718919116);
void car_h_25(double *state, double *unused, double *out_4616275488682323747);
void car_H_25(double *state, double *unused, double *out_7903896044907373786);
void car_h_24(double *state, double *unused, double *out_1240821179762925085);
void car_H_24(double *state, double *unused, double *out_4345970446105050650);
void car_h_30(double *state, double *unused, double *out_978825960428301397);
void car_H_30(double *state, double *unused, double *out_8033234992050613856);
void car_h_26(double *state, double *unused, double *out_35316107526638962);
void car_H_26(double *state, double *unused, double *out_6801344709928121606);
void car_h_27(double *state, double *unused, double *out_8256782726505873065);
void car_H_27(double *state, double *unused, double *out_8238745769858512849);
void car_h_29(double *state, double *unused, double *out_4022847307232544248);
void car_H_29(double *state, double *unused, double *out_7523003647736221672);
void car_h_28(double *state, double *unused, double *out_3255109458845027420);
void car_H_28(double *state, double *unused, double *out_5841341408903799370);
void car_h_31(double *state, double *unused, double *out_6638919472171716073);
void car_H_31(double *state, double *unused, double *out_7873250083030413358);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}