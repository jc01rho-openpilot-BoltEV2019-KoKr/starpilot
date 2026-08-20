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
void car_err_fun(double *nom_x, double *delta_x, double *out_3745689373699638561);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2400897459040094715);
void car_H_mod_fun(double *state, double *out_7767655668809768572);
void car_f_fun(double *state, double dt, double *out_3612821593330881774);
void car_F_fun(double *state, double dt, double *out_2179834667538047746);
void car_h_25(double *state, double *unused, double *out_6182136655387767236);
void car_H_25(double *state, double *unused, double *out_2863963843625103732);
void car_h_24(double *state, double *unused, double *out_7699556082354746130);
void car_H_24(double *state, double *unused, double *out_8991184345786785929);
void car_h_30(double *state, double *unused, double *out_3234410665032282275);
void car_H_30(double *state, double *unused, double *out_345630885117855105);
void car_h_26(double *state, double *unused, double *out_8236083932693127920);
void car_H_26(double *state, double *unused, double *out_6605467162499159956);
void car_h_27(double *state, double *unused, double *out_5200052562052469124);
void car_H_27(double *state, double *unused, double *out_1877963186066088112);
void car_h_29(double *state, double *unused, double *out_1767262602628563370);
void car_H_29(double *state, double *unused, double *out_164600459196537079);
void car_h_28(double *state, double *unused, double *out_8284311513975789260);
void car_H_28(double *state, double *unused, double *out_4917798557872993495);
void car_h_31(double *state, double *unused, double *out_588698570962583700);
void car_H_31(double *state, double *unused, double *out_7231675264732511432);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}