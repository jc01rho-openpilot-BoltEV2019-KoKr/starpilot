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
void car_err_fun(double *nom_x, double *delta_x, double *out_2567017903067559466);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1749285410370024184);
void car_H_mod_fun(double *state, double *out_8979551951706364182);
void car_f_fun(double *state, double dt, double *out_3674179640817441392);
void car_F_fun(double *state, double dt, double *out_258925546890284745);
void car_h_25(double *state, double *unused, double *out_5262304077966076166);
void car_H_25(double *state, double *unused, double *out_4563500296818522594);
void car_h_24(double *state, double *unused, double *out_2894074188837958464);
void car_H_24(double *state, double *unused, double *out_2012071509772995507);
void car_h_30(double *state, double *unused, double *out_9005980160461201074);
void car_H_30(double *state, double *unused, double *out_2045167338311273967);
void car_h_26(double *state, double *unused, double *out_8837448028571873025);
void car_H_26(double *state, double *unused, double *out_1258974327057721993);
void car_h_27(double *state, double *unused, double *out_6785398478329626304);
void car_H_27(double *state, double *unused, double *out_178426732872669250);
void car_h_29(double *state, double *unused, double *out_8023896067125902962);
void car_H_29(double *state, double *unused, double *out_1534935993996881783);
void car_h_28(double *state, double *unused, double *out_5617654677253484567);
void car_H_28(double *state, double *unused, double *out_6617335011066412357);
void car_h_31(double *state, double *unused, double *out_9123987554394577818);
void car_H_31(double *state, double *unused, double *out_4532854334941562166);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}