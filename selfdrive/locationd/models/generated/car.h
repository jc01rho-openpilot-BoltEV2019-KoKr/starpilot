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
void car_err_fun(double *nom_x, double *delta_x, double *out_822107927183758870);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4567978126636007906);
void car_H_mod_fun(double *state, double *out_4866635074780860371);
void car_f_fun(double *state, double dt, double *out_982026265070027710);
void car_F_fun(double *state, double dt, double *out_1254446333762572024);
void car_h_25(double *state, double *unused, double *out_3612384322752044911);
void car_H_25(double *state, double *unused, double *out_4326553151131376866);
void car_h_24(double *state, double *unused, double *out_5341613571554885336);
void car_H_24(double *state, double *unused, double *out_2100845367152508304);
void car_h_30(double *state, double *unused, double *out_3337190260467539022);
void car_H_30(double *state, double *unused, double *out_4455892098274616936);
void car_h_26(double *state, double *unused, double *out_2004676975418491541);
void car_H_26(double *state, double *unused, double *out_8068056470005433090);
void car_h_27(double *state, double *unused, double *out_1389288944908800734);
void car_H_27(double *state, double *unused, double *out_6630655410075041847);
void car_h_29(double *state, double *unused, double *out_1664483007193306623);
void car_H_29(double *state, double *unused, double *out_3945660753960224752);
void car_h_28(double *state, double *unused, double *out_990882427725417615);
void car_H_28(double *state, double *unused, double *out_1982030482394898501);
void car_h_31(double *state, double *unused, double *out_7249833851006067261);
void car_H_31(double *state, double *unused, double *out_4295907189254416438);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}