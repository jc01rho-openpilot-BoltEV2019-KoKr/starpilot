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
void car_err_fun(double *nom_x, double *delta_x, double *out_555027713999943867);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7816877518147233589);
void car_H_mod_fun(double *state, double *out_4533074481319696241);
void car_f_fun(double *state, double dt, double *out_5039337670867030572);
void car_F_fun(double *state, double dt, double *out_5181832378332727216);
void car_h_25(double *state, double *unused, double *out_9064502358369772671);
void car_H_25(double *state, double *unused, double *out_9009977767205190535);
void car_h_24(double *state, double *unused, double *out_4315668618686905201);
void car_H_24(double *state, double *unused, double *out_4579303311377586733);
void car_h_30(double *state, double *unused, double *out_8507922675073509890);
void car_H_30(double *state, double *unused, double *out_2093287425713573780);
void car_h_26(double *state, double *unused, double *out_4180836484642303770);
void car_H_26(double *state, double *unused, double *out_5695262987630304857);
void car_h_27(double *state, double *unused, double *out_4062829090708927026);
void car_H_27(double *state, double *unused, double *out_4268050737513998691);
void car_h_29(double *state, double *unused, double *out_7564412822171847455);
void car_H_29(double *state, double *unused, double *out_5981413464383549724);
void car_h_28(double *state, double *unused, double *out_1579900780372029809);
void car_H_28(double *state, double *unused, double *out_7382931592256471318);
void car_h_31(double *state, double *unused, double *out_6613551970606485049);
void car_H_31(double *state, double *unused, double *out_8979331805328230107);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}