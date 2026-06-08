#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6891956137394554809);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_352074767866048570);
void pose_H_mod_fun(double *state, double *out_57344037476075931);
void pose_f_fun(double *state, double dt, double *out_8328845329683204295);
void pose_F_fun(double *state, double dt, double *out_6465495001911852221);
void pose_h_4(double *state, double *unused, double *out_7442631847161232120);
void pose_H_4(double *state, double *unused, double *out_8142960846497148836);
void pose_h_10(double *state, double *unused, double *out_6865183365695080269);
void pose_H_10(double *state, double *unused, double *out_456103805919410821);
void pose_h_13(double *state, double *unused, double *out_2130091715364414233);
void pose_H_13(double *state, double *unused, double *out_2693152018895701851);
void pose_h_14(double *state, double *unused, double *out_2314638522999502046);
void pose_H_14(double *state, double *unused, double *out_6340542370872918251);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}