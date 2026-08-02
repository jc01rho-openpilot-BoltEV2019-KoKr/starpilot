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
void car_err_fun(double *nom_x, double *delta_x, double *out_2600768462618711997);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7259494313163356603);
void car_H_mod_fun(double *state, double *out_1493188658696786749);
void car_f_fun(double *state, double dt, double *out_5943509684037993570);
void car_F_fun(double *state, double dt, double *out_6240971521964326149);
void car_h_25(double *state, double *unused, double *out_6066332368842429215);
void car_H_25(double *state, double *unused, double *out_4603719707909587867);
void car_h_24(double *state, double *unused, double *out_3848779066424665825);
void car_H_24(double *state, double *unused, double *out_2378011923930719305);
void car_h_30(double *state, double *unused, double *out_6341526431126935104);
void car_H_30(double *state, double *unused, double *out_2312970633582028888);
void car_h_26(double *state, double *unused, double *out_7509270232203076841);
void car_H_26(double *state, double *unused, double *out_8345223026783644091);
void car_h_27(double *state, double *unused, double *out_4731066531555788059);
void car_H_27(double *state, double *unused, double *out_138207321781603977);
void car_h_29(double *state, double *unused, double *out_869383055127286407);
void car_H_29(double *state, double *unused, double *out_2823201977896421072);
void car_h_28(double *state, double *unused, double *out_2023156983307100891);
void car_H_28(double *state, double *unused, double *out_2259197039173109502);
void car_h_31(double *state, double *unused, double *out_2428882840588406865);
void car_H_31(double *state, double *unused, double *out_4573073746032627439);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}