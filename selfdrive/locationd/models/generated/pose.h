#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_521051683878790646);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_210058828153721645);
void pose_H_mod_fun(double *state, double *out_4312613236564964080);
void pose_f_fun(double *state, double dt, double *out_7807614062433422920);
void pose_F_fun(double *state, double dt, double *out_54869773676509633);
void pose_h_4(double *state, double *unused, double *out_3501775823039351379);
void pose_H_4(double *state, double *unused, double *out_8084420446408871652);
void pose_h_10(double *state, double *unused, double *out_8571708459300677945);
void pose_H_10(double *state, double *unused, double *out_2059745207116816931);
void pose_h_13(double *state, double *unused, double *out_6791205246269589213);
void pose_H_13(double *state, double *unused, double *out_8649022366090715756);
void pose_h_14(double *state, double *unused, double *out_8615295986968492388);
void pose_H_14(double *state, double *unused, double *out_5001632014113499356);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}