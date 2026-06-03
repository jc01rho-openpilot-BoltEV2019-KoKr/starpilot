#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_616508134330162473);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3534488348241865019);
void pose_H_mod_fun(double *state, double *out_5384152065241129084);
void pose_f_fun(double *state, double dt, double *out_1966290028419981018);
void pose_F_fun(double *state, double dt, double *out_8500986371107107872);
void pose_h_4(double *state, double *unused, double *out_5400718070291809963);
void pose_H_4(double *state, double *unused, double *out_9155959275085036656);
void pose_h_10(double *state, double *unused, double *out_2963274022918519597);
void pose_H_10(double *state, double *unused, double *out_5627581855619872909);
void pose_h_13(double *state, double *unused, double *out_6005618121794927988);
void pose_H_13(double *state, double *unused, double *out_1680153590307814031);
void pose_h_14(double *state, double *unused, double *out_5652518326669022365);
void pose_H_14(double *state, double *unused, double *out_6073170842789664360);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}