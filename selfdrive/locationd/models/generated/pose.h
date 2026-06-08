#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_8979246808243312501);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6182129478777519212);
void pose_H_mod_fun(double *state, double *out_5496809482113736276);
void pose_f_fun(double *state, double dt, double *out_76749327147481970);
void pose_F_fun(double *state, double dt, double *out_7773273273846026145);
void pose_h_4(double *state, double *unused, double *out_8836590006675901483);
void pose_H_4(double *state, double *unused, double *out_8771031560904685529);
void pose_h_10(double *state, double *unused, double *out_7833049906299002536);
void pose_H_10(double *state, double *unused, double *out_1676230657278343882);
void pose_h_13(double *state, double *unused, double *out_8788718686171382623);
void pose_H_13(double *state, double *unused, double *out_5558757735572352728);
void pose_h_14(double *state, double *unused, double *out_4044191392879282830);
void pose_H_14(double *state, double *unused, double *out_4807790704565201000);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}