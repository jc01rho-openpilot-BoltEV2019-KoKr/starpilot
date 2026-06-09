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
void car_err_fun(double *nom_x, double *delta_x, double *out_2644531489535461779);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1100504365402285318);
void car_H_mod_fun(double *state, double *out_6242485690446211568);
void car_f_fun(double *state, double dt, double *out_3248907569765849539);
void car_F_fun(double *state, double dt, double *out_8360719243632448897);
void car_h_25(double *state, double *unused, double *out_8500141102228074854);
void car_H_25(double *state, double *unused, double *out_2719505040456719891);
void car_h_24(double *state, double *unused, double *out_7897313667940812561);
void car_H_24(double *state, double *unused, double *out_838420558345603245);
void car_h_30(double *state, double *unused, double *out_808885686797625580);
void car_H_30(double *state, double *unused, double *out_4197185301034896864);
void car_h_26(double *state, double *unused, double *out_4192787580863220065);
void car_H_26(double *state, double *unused, double *out_6461008359330776115);
void car_h_27(double *state, double *unused, double *out_5889273078412295556);
void car_H_27(double *state, double *unused, double *out_2022421989234471953);
void car_h_29(double *state, double *unused, double *out_5810558954458471225);
void car_H_29(double *state, double *unused, double *out_4707416645349289048);
void car_h_28(double *state, double *unused, double *out_926893080731002324);
void car_H_28(double *state, double *unused, double *out_4773339754704609654);
void car_h_31(double *state, double *unused, double *out_2974083665677051741);
void car_H_31(double *state, double *unused, double *out_2688859078579759463);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}