#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7704133318394013706);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5732870200970735889);
void pose_H_mod_fun(double *state, double *out_5613029472060395452);
void pose_f_fun(double *state, double dt, double *out_3560257805552383557);
void pose_F_fun(double *state, double dt, double *out_8405700866591566947);
void pose_h_4(double *state, double *unused, double *out_6714333113820678959);
void pose_H_4(double *state, double *unused, double *out_6985632794897197443);
void pose_h_10(double *state, double *unused, double *out_1436740119579277140);
void pose_H_10(double *state, double *unused, double *out_1336760473497929829);
void pose_h_13(double *state, double *unused, double *out_8610784800470542827);
void pose_H_13(double *state, double *unused, double *out_8248837453480021372);
void pose_h_14(double *state, double *unused, double *out_7905030664698657319);
void pose_H_14(double *state, double *unused, double *out_6550516268252313844);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}