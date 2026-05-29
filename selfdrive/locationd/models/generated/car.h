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
void car_err_fun(double *nom_x, double *delta_x, double *out_7214711627163091402);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_911828672798028438);
void car_H_mod_fun(double *state, double *out_149552472482575511);
void car_f_fun(double *state, double dt, double *out_4547528931834134293);
void car_F_fun(double *state, double dt, double *out_3560058468708809121);
void car_h_25(double *state, double *unused, double *out_1132582605868503102);
void car_H_25(double *state, double *unused, double *out_9104003375314738868);
void car_h_24(double *state, double *unused, double *out_8381470974523360630);
void car_H_24(double *state, double *unused, double *out_4357494048348229834);
void car_h_30(double *state, double *unused, double *out_975395937517373957);
void car_H_30(double *state, double *unused, double *out_2426050356903195993);
void car_h_26(double *state, double *unused, double *out_4026277330143471688);
void car_H_26(double *state, double *unused, double *out_5362500056440682644);
void car_h_27(double *state, double *unused, double *out_990245959502812892);
void car_H_27(double *state, double *unused, double *out_4600813668703620904);
void car_h_29(double *state, double *unused, double *out_8450804723751701217);
void car_H_29(double *state, double *unused, double *out_1915819012588803809);
void car_h_28(double *state, double *unused, double *out_2847713298477492018);
void car_H_28(double *state, double *unused, double *out_7050168661066849105);
void car_h_31(double *state, double *unused, double *out_857388543583997213);
void car_H_31(double *state, double *unused, double *out_9134649337191699296);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}