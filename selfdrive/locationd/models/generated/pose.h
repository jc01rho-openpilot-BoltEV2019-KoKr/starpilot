#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1308154946342484284);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8706500607592261698);
void pose_H_mod_fun(double *state, double *out_1512473366161392308);
void pose_f_fun(double *state, double dt, double *out_7813170452072968754);
void pose_F_fun(double *state, double dt, double *out_5083828130456064396);
void pose_h_4(double *state, double *unused, double *out_8720432154848991493);
void pose_H_4(double *state, double *unused, double *out_4091132023239463575);
void pose_h_10(double *state, double *unused, double *out_682446449180910309);
void pose_H_10(double *state, double *unused, double *out_4919001356891757040);
void pose_h_13(double *state, double *unused, double *out_2860834984953274042);
void pose_H_13(double *state, double *unused, double *out_7303405848571796376);
void pose_h_14(double *state, double *unused, double *out_6283645208607536870);
void pose_H_14(double *state, double *unused, double *out_1008343590944091279);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}