#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5206974560936582462);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8580851081509816390);
void pose_H_mod_fun(double *state, double *out_310958725680718826);
void pose_f_fun(double *state, double dt, double *out_8333876756213369009);
void pose_F_fun(double *state, double dt, double *out_8736875160637463263);
void pose_h_4(double *state, double *unused, double *out_5158761943134929654);
void pose_H_4(double *state, double *unused, double *out_4082765935524626398);
void pose_h_10(double *state, double *unused, double *out_563005185308758885);
void pose_H_10(double *state, double *unused, double *out_7993288058010589722);
void pose_h_13(double *state, double *unused, double *out_1191809301965979441);
void pose_H_13(double *state, double *unused, double *out_7295039760856959199);
void pose_h_14(double *state, double *unused, double *out_8501358265546490714);
void pose_H_14(double *state, double *unused, double *out_999977503229254102);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}