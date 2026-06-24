#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1493079546624007114);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4580499654968994478);
void pose_H_mod_fun(double *state, double *out_8273119377234766952);
void pose_f_fun(double *state, double dt, double *out_2742900412262200056);
void pose_F_fun(double *state, double dt, double *out_1250059419478269226);
void pose_h_4(double *state, double *unused, double *out_6706399028598537324);
void pose_H_4(double *state, double *unused, double *out_1435428464391795526);
void pose_h_10(double *state, double *unused, double *out_3193952299746834757);
void pose_H_10(double *state, double *unused, double *out_1464924797507750077);
void pose_h_13(double *state, double *unused, double *out_7802893222450228438);
void pose_H_13(double *state, double *unused, double *out_1776845360940537275);
void pose_h_14(double *state, double *unused, double *out_7652212324095214333);
void pose_H_14(double *state, double *unused, double *out_2527812391947689003);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}