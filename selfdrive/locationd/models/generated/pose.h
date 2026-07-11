#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3926294361318359623);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5231104082209692226);
void pose_H_mod_fun(double *state, double *out_5646756432622182646);
void pose_f_fun(double *state, double dt, double *out_1137320570887410122);
void pose_F_fun(double *state, double dt, double *out_2697011094328554799);
void pose_h_4(double *state, double *unused, double *out_1053451418042427012);
void pose_H_4(double *state, double *unused, double *out_7540267336217958736);
void pose_h_10(double *state, double *unused, double *out_3684376753725260505);
void pose_H_10(double *state, double *unused, double *out_5090252371717073425);
void pose_h_13(double *state, double *unused, double *out_5749954067458841209);
void pose_H_13(double *state, double *unused, double *out_4327993510885625935);
void pose_h_14(double *state, double *unused, double *out_9151671114827748167);
void pose_H_14(double *state, double *unused, double *out_3577026479878474207);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}