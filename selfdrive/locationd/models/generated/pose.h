#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2815596288453817821);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8761485569796980977);
void pose_H_mod_fun(double *state, double *out_9016812017969752156);
void pose_f_fun(double *state, double dt, double *out_5314151849166190903);
void pose_F_fun(double *state, double dt, double *out_3978107798910374878);
void pose_h_4(double *state, double *unused, double *out_6702643113920812120);
void pose_H_4(double *state, double *unused, double *out_1181133811394856104);
void pose_h_10(double *state, double *unused, double *out_329728007611436907);
void pose_H_10(double *state, double *unused, double *out_8047171094370826367);
void pose_h_13(double *state, double *unused, double *out_8195155792174923791);
void pose_H_13(double *state, double *unused, double *out_2031140013937476697);
void pose_h_14(double *state, double *unused, double *out_3839043433562085237);
void pose_H_14(double *state, double *unused, double *out_2782107044944628425);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}