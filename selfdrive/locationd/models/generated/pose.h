#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6169503642516981710);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2781558835044378693);
void pose_H_mod_fun(double *state, double *out_4498457996676133449);
void pose_f_fun(double *state, double dt, double *out_3471362747861957887);
void pose_F_fun(double *state, double dt, double *out_2324287403941072643);
void pose_h_4(double *state, double *unused, double *out_3295127809911230665);
void pose_H_4(double *state, double *unused, double *out_8270265206520041021);
void pose_h_10(double *state, double *unused, double *out_3863591942336910664);
void pose_H_10(double *state, double *unused, double *out_6343727255885996060);
void pose_h_13(double *state, double *unused, double *out_3880954183827223653);
void pose_H_13(double *state, double *unused, double *out_6964205041857177794);
void pose_h_14(double *state, double *unused, double *out_8209348319732836111);
void pose_H_14(double *state, double *unused, double *out_5187476774224668725);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}