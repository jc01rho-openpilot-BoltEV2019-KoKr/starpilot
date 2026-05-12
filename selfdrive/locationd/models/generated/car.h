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
void car_err_fun(double *nom_x, double *delta_x, double *out_3886210737280219279);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_9203878995777804762);
void car_H_mod_fun(double *state, double *out_8506196822923476348);
void car_f_fun(double *state, double dt, double *out_2212415948681408961);
void car_F_fun(double *state, double dt, double *out_8605893895722033804);
void car_h_25(double *state, double *unused, double *out_80606407557009467);
void car_H_25(double *state, double *unused, double *out_2019209217812215463);
void car_h_24(double *state, double *unused, double *out_8156817116559759487);
void car_H_24(double *state, double *unused, double *out_7208855968256979762);
void car_h_30(double *state, double *unused, double *out_7682658849263662974);
void car_H_30(double *state, double *unused, double *out_6546905547939823661);
void car_h_26(double *state, double *unused, double *out_2046248304577196316);
void car_H_26(double *state, double *unused, double *out_5760712536686271687);
void car_h_27(double *state, double *unused, double *out_4505967322855241000);
void car_H_27(double *state, double *unused, double *out_8721668859740248572);
void car_h_29(double *state, double *unused, double *out_1934047599768798804);
void car_H_29(double *state, double *unused, double *out_6036674203625431477);
void car_h_28(double *state, double *unused, double *out_3899689496788985653);
void car_H_28(double *state, double *unused, double *out_7327670853014589565);
void car_h_31(double *state, double *unused, double *out_40967961750261831);
void car_H_31(double *state, double *unused, double *out_6386920638919623163);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}