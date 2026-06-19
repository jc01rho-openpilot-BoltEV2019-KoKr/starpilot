#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_4423077432163082570);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3066625947211960781);
void pose_H_mod_fun(double *state, double *out_7899193355677302719);
void pose_f_fun(double *state, double dt, double *out_1767716959874096227);
void pose_F_fun(double *state, double dt, double *out_5946100134082923473);
void pose_h_4(double *state, double *unused, double *out_7895468860031348123);
void pose_H_4(double *state, double *unused, double *out_4699468911280290176);
void pose_h_10(double *state, double *unused, double *out_7051420194440758803);
void pose_H_10(double *state, double *unused, double *out_181799554460224071);
void pose_h_13(double *state, double *unused, double *out_1850536561694260921);
void pose_H_13(double *state, double *unused, double *out_7911742736612622977);
void pose_h_14(double *state, double *unused, double *out_8940417508633322111);
void pose_H_14(double *state, double *unused, double *out_8662709767619774705);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}