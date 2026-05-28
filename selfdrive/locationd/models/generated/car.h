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
void car_err_fun(double *nom_x, double *delta_x, double *out_2249508041139738373);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4788524825292355547);
void car_H_mod_fun(double *state, double *out_5143375091155045702);
void car_f_fun(double *state, double dt, double *out_223721292699517100);
void car_F_fun(double *state, double dt, double *out_6998880572782646555);
void car_h_25(double *state, double *unused, double *out_6606540369410235194);
void car_H_25(double *state, double *unused, double *out_8666423729800410850);
void car_h_24(double *state, double *unused, double *out_4049880123285190269);
void car_H_24(double *state, double *unused, double *out_5108498130998087714);
void car_h_30(double *state, double *unused, double *out_164294856940115742);
void car_H_30(double *state, double *unused, double *out_1749733388308794095);
void car_h_26(double *state, double *unused, double *out_767610741616593259);
void car_H_26(double *state, double *unused, double *out_6038817025035084542);
void car_h_27(double *state, double *unused, double *out_9132294156050629254);
void car_H_27(double *state, double *unused, double *out_3924496700109219006);
void car_h_29(double *state, double *unused, double *out_2543614691308571426);
void car_H_29(double *state, double *unused, double *out_5637859426978770039);
void car_h_28(double *state, double *unused, double *out_3987404092934981717);
void car_H_28(double *state, double *unused, double *out_7726485629661251003);
void car_h_31(double *state, double *unused, double *out_6594936115065281760);
void car_H_31(double *state, double *unused, double *out_8635777767923450422);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}