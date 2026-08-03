#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5763415234273933913);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1417325942549329712);
void pose_H_mod_fun(double *state, double *out_7849761791714406524);
void pose_f_fun(double *state, double dt, double *out_4127372900134371769);
void pose_F_fun(double *state, double dt, double *out_6790734299023463428);
void pose_h_4(double *state, double *unused, double *out_7856717095735989173);
void pose_H_4(double *state, double *unused, double *out_6651814309831508420);
void pose_h_10(double *state, double *unused, double *out_7802819887885526758);
void pose_H_10(double *state, double *unused, double *out_2391217134998665876);
void pose_h_13(double *state, double *unused, double *out_7948582274063627909);
void pose_H_13(double *state, double *unused, double *out_3439540484499175619);
void pose_h_14(double *state, double *unused, double *out_223099352326779878);
void pose_H_14(double *state, double *unused, double *out_8712141331582670900);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}