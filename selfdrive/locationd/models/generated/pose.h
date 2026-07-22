#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_607652414837750033);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4916314802659989276);
void pose_H_mod_fun(double *state, double *out_1887258982449267152);
void pose_f_fun(double *state, double dt, double *out_2681276694689160944);
void pose_F_fun(double *state, double dt, double *out_6011099377550215473);
void pose_h_4(double *state, double *unused, double *out_5478412217433972001);
void pose_H_4(double *state, double *unused, double *out_3085206464332165256);
void pose_h_10(double *state, double *unused, double *out_5861828944145935890);
void pose_H_10(double *state, double *unused, double *out_1460352446362739633);
void pose_h_13(double *state, double *unused, double *out_6845339361600931042);
void pose_H_13(double *state, double *unused, double *out_6297480289664498057);
void pose_h_14(double *state, double *unused, double *out_6355309693456612665);
void pose_H_14(double *state, double *unused, double *out_2418032036792960);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}