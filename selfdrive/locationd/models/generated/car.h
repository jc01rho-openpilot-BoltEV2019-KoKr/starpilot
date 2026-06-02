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
void car_err_fun(double *nom_x, double *delta_x, double *out_4189395199092511703);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5755129993245429730);
void car_H_mod_fun(double *state, double *out_3130611196753066809);
void car_f_fun(double *state, double dt, double *out_5961640813003379683);
void car_F_fun(double *state, double dt, double *out_2654082016279909676);
void car_h_25(double *state, double *unused, double *out_3340180793096633183);
void car_H_25(double *state, double *unused, double *out_4434950306945038429);
void car_h_24(double *state, double *unused, double *out_7854800018825826791);
void car_H_24(double *state, double *unused, double *out_6607599905950537995);
void car_h_30(double *state, double *unused, double *out_3104430337924860088);
void car_H_30(double *state, double *unused, double *out_1916617348437789802);
void car_h_26(double *state, double *unused, double *out_4544914835386474254);
void car_H_26(double *state, double *unused, double *out_8176453625819094653);
void car_h_27(double *state, double *unused, double *out_4426907441453097510);
void car_H_27(double *state, double *unused, double *out_306976722746153415);
void car_h_29(double *state, double *unused, double *out_2160920485023197653);
void car_H_29(double *state, double *unused, double *out_1406386004123397618);
void car_h_28(double *state, double *unused, double *out_7017073928463388327);
void car_H_28(double *state, double *unused, double *out_6488785021192928192);
void car_h_31(double *state, double *unused, double *out_5156479888167106809);
void car_H_31(double *state, double *unused, double *out_4404304345068078001);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}