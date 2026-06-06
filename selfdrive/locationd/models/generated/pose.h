#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3524911542636248309);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_9101758542759318568);
void pose_H_mod_fun(double *state, double *out_202451455870783186);
void pose_f_fun(double *state, double dt, double *out_3404078345216964699);
void pose_F_fun(double *state, double dt, double *out_9161898751948597001);
void pose_h_4(double *state, double *unused, double *out_3298849734810867951);
void pose_H_4(double *state, double *unused, double *out_3476673534661732439);
void pose_h_10(double *state, double *unused, double *out_1490778051551919602);
void pose_H_10(double *state, double *unused, double *out_3065010150012391749);
void pose_h_13(double *state, double *unused, double *out_2293000846655251698);
void pose_H_13(double *state, double *unused, double *out_4133957673654968490);
void pose_h_14(double *state, double *unused, double *out_6732417031145183728);
void pose_H_14(double *state, double *unused, double *out_486567321677752090);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}