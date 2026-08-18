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
void car_err_fun(double *nom_x, double *delta_x, double *out_4175267327343220067);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8001717605441520298);
void car_H_mod_fun(double *state, double *out_7971983971871194008);
void car_f_fun(double *state, double dt, double *out_1960663178760025601);
void car_F_fun(double *state, double dt, double *out_893498683805935900);
void car_h_25(double *state, double *unused, double *out_3235092958161781685);
void car_H_25(double *state, double *unused, double *out_4449003321881702331);
void car_h_24(double *state, double *unused, double *out_5426063249126145013);
void car_H_24(double *state, double *unused, double *out_4845648626235561826);
void car_h_30(double *state, double *unused, double *out_9056203919707109802);
void car_H_30(double *state, double *unused, double *out_1930670363374453704);
void car_h_26(double *state, double *unused, double *out_6243651816437256419);
void car_H_26(double *state, double *unused, double *out_8190506640755758555);
void car_h_27(double *state, double *unused, double *out_3838408842838259202);
void car_H_27(double *state, double *unused, double *out_292923707809489513);
void car_h_29(double *state, double *unused, double *out_259894455441112662);
void car_H_29(double *state, double *unused, double *out_1420439019060061520);
void car_h_28(double *state, double *unused, double *out_5143560329168581563);
void car_H_28(double *state, double *unused, double *out_6502838036129592094);
void car_h_31(double *state, double *unused, double *out_2959898895877275796);
void car_H_31(double *state, double *unused, double *out_4418357360004741903);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}