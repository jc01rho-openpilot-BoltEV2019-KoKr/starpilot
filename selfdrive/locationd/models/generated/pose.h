#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7536058918625145808);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6294980525542920357);
void pose_H_mod_fun(double *state, double *out_1208523344993905378);
void pose_f_fun(double *state, double dt, double *out_828336908542161324);
void pose_F_fun(double *state, double dt, double *out_5703387388084628727);
void pose_h_4(double *state, double *unused, double *out_2600666041609585625);
void pose_H_4(double *state, double *unused, double *out_2406470826876803482);
void pose_h_10(double *state, double *unused, double *out_2042730394265084466);
void pose_H_10(double *state, double *unused, double *out_6010400890176312817);
void pose_h_13(double *state, double *unused, double *out_3259369495818676553);
void pose_H_13(double *state, double *unused, double *out_5618744652209136283);
void pose_h_14(double *state, double *unused, double *out_1539412177960834763);
void pose_H_14(double *state, double *unused, double *out_676317605418568814);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}