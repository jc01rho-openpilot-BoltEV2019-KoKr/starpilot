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
void car_err_fun(double *nom_x, double *delta_x, double *out_9086440322595224646);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7805211099664095660);
void car_H_mod_fun(double *state, double *out_2822454019109077104);
void car_f_fun(double *state, double dt, double *out_1333075080878653623);
void car_F_fun(double *state, double dt, double *out_8557949136162757558);
void car_h_25(double *state, double *unused, double *out_5666050874031952366);
void car_H_25(double *state, double *unused, double *out_3274454347497297512);
void car_h_24(double *state, double *unused, double *out_7890691293906506169);
void car_H_24(double *state, double *unused, double *out_5447103946502797078);
void car_h_30(double *state, double *unused, double *out_5390856811747446477);
void car_H_30(double *state, double *unused, double *out_3642235993994319243);
void car_h_26(double *state, double *unused, double *out_4304130163390982150);
void car_H_26(double *state, double *unused, double *out_7015957666371353736);
void car_h_27(double *state, double *unused, double *out_5777930495884533471);
void car_H_27(double *state, double *unused, double *out_1467472682193894332);
void car_h_29(double *state, double *unused, double *out_4787540927070968960);
void car_H_29(double *state, double *unused, double *out_245890044675656701);
void car_h_28(double *state, double *unused, double *out_6006244842257137284);
void car_H_28(double *state, double *unused, double *out_5328289061745187275);
void car_h_31(double *state, double *unused, double *out_5508864205680823221);
void car_H_31(double *state, double *unused, double *out_3243808385620337084);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}