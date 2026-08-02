#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_327274557709511665);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4344179942375735738);
void pose_H_mod_fun(double *state, double *out_8315920796386777796);
void pose_f_fun(double *state, double dt, double *out_1706853749310621885);
void pose_F_fun(double *state, double dt, double *out_3565612569828347872);
void pose_h_4(double *state, double *unused, double *out_6256833977858620129);
void pose_H_4(double *state, double *unused, double *out_7117973314503879692);
void pose_h_10(double *state, double *unused, double *out_8339904701560037775);
void pose_H_10(double *state, double *unused, double *out_4285286583568518818);
void pose_h_13(double *state, double *unused, double *out_4092510433385355744);
void pose_H_13(double *state, double *unused, double *out_3905699489171546891);
void pose_h_14(double *state, double *unused, double *out_1965285751179212564);
void pose_H_14(double *state, double *unused, double *out_8245982326910299628);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}