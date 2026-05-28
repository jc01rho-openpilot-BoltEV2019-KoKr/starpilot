#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6079659893886918220);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5200837164005369107);
void pose_H_mod_fun(double *state, double *out_1320875044412644660);
void pose_f_fun(double *state, double dt, double *out_4957392939814811366);
void pose_F_fun(double *state, double dt, double *out_3660031818732653459);
void pose_h_4(double *state, double *unused, double *out_4354770932396622955);
void pose_H_4(double *state, double *unused, double *out_3140573770318941521);
void pose_h_10(double *state, double *unused, double *out_8942219874713773227);
void pose_H_10(double *state, double *unused, double *out_5705253479912587073);
void pose_h_13(double *state, double *unused, double *out_5867183224538439243);
void pose_H_13(double *state, double *unused, double *out_71700055013391280);
void pose_h_14(double *state, double *unused, double *out_4155160495787210910);
void pose_H_14(double *state, double *unused, double *out_822667086020543008);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}