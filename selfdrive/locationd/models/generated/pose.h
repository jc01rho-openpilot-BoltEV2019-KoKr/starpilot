#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7365448194845582757);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1967800537697910635);
void pose_H_mod_fun(double *state, double *out_8390959249454907977);
void pose_f_fun(double *state, double dt, double *out_9042230065077868228);
void pose_F_fun(double *state, double dt, double *out_3211704972733304042);
void pose_h_4(double *state, double *unused, double *out_4618547932677025290);
void pose_H_4(double *state, double *unused, double *out_8857837342371745535);
void pose_h_10(double *state, double *unused, double *out_286079926766125973);
void pose_H_10(double *state, double *unused, double *out_2479119896376040884);
void pose_h_13(double *state, double *unused, double *out_829945007780659418);
void pose_H_13(double *state, double *unused, double *out_5755151268035282057);
void pose_h_14(double *state, double *unused, double *out_1492834352067073969);
void pose_H_14(double *state, double *unused, double *out_6506118299042433785);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}