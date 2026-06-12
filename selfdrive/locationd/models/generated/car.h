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
void car_err_fun(double *nom_x, double *delta_x, double *out_6201369500890241283);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6748403134246456124);
void car_H_mod_fun(double *state, double *out_2042585132715859694);
void car_f_fun(double *state, double dt, double *out_4209455390444840494);
void car_F_fun(double *state, double dt, double *out_2724900345805544233);
void car_h_25(double *state, double *unused, double *out_2892803162940124204);
void car_H_25(double *state, double *unused, double *out_4054323233890514922);
void car_h_24(double *state, double *unused, double *out_2360383510230698975);
void car_H_24(double *state, double *unused, double *out_1828615449911646360);
void car_h_30(double *state, double *unused, double *out_801115166891129847);
void car_H_30(double *state, double *unused, double *out_2862367107601101833);
void car_h_26(double *state, double *unused, double *out_1833676042436215552);
void car_H_26(double *state, double *unused, double *out_749797264129714321);
void car_h_27(double *state, double *unused, double *out_512631790305905855);
void car_H_27(double *state, double *unused, double *out_687603795800676922);
void car_h_29(double *state, double *unused, double *out_355445121954776710);
void car_H_29(double *state, double *unused, double *out_3372598451915494017);
void car_h_28(double *state, double *unused, double *out_4713758757429658086);
void car_H_28(double *state, double *unused, double *out_6108157948138404685);
void car_h_31(double *state, double *unused, double *out_744646365313898146);
void car_H_31(double *state, double *unused, double *out_3022352016621302331);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}