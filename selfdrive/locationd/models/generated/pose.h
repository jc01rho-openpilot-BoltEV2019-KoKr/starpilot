#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_8940459122146932400);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3384987028755125218);
void pose_H_mod_fun(double *state, double *out_5245124330854285834);
void pose_f_fun(double *state, double dt, double *out_6830900184565569763);
void pose_F_fun(double *state, double dt, double *out_5118094281500581129);
void pose_h_4(double *state, double *unused, double *out_4935070827926002458);
void pose_H_4(double *state, double *unused, double *out_6443071812737183938);
void pose_h_10(double *state, double *unused, double *out_2021668210924663063);
void pose_H_10(double *state, double *unused, double *out_7830124823924821015);
void pose_h_13(double *state, double *unused, double *out_7135402855206141384);
void pose_H_13(double *state, double *unused, double *out_8791398435640034877);
void pose_h_14(double *state, double *unused, double *out_7043440464612625298);
void pose_H_14(double *state, double *unused, double *out_3360283380441811642);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}