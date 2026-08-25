#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2551549382290402050);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3575109948453160374);
void pose_H_mod_fun(double *state, double *out_2954011976512996711);
void pose_f_fun(double *state, double dt, double *out_4081841541460951824);
void pose_F_fun(double *state, double dt, double *out_2326707394449301144);
void pose_h_4(double *state, double *unused, double *out_5242858642703077087);
void pose_H_4(double *state, double *unused, double *out_1660615060416319653);
void pose_h_10(double *state, double *unused, double *out_8287724405821980303);
void pose_H_10(double *state, double *unused, double *out_8634670991932313772);
void pose_h_13(double *state, double *unused, double *out_936388540160520926);
void pose_H_13(double *state, double *unused, double *out_4872888885748652454);
void pose_h_14(double *state, double *unused, double *out_3784911557802666238);
void pose_H_14(double *state, double *unused, double *out_5623855916755804182);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}