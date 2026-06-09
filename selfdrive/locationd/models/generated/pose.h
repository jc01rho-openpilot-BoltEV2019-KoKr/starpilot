#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5518524982420716050);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4331401110135306651);
void pose_H_mod_fun(double *state, double *out_3835336694818914681);
void pose_f_fun(double *state, double dt, double *out_4487166249411202898);
void pose_F_fun(double *state, double dt, double *out_5041909296412759665);
void pose_h_4(double *state, double *unused, double *out_6410794677621402397);
void pose_H_4(double *state, double *unused, double *out_7109558773609863934);
void pose_h_10(double *state, double *unused, double *out_7278806369328538184);
void pose_H_10(double *state, double *unused, double *out_6138938714751040661);
void pose_h_13(double *state, double *unused, double *out_8268474279687789459);
void pose_H_13(double *state, double *unused, double *out_3897284948277531133);
void pose_h_14(double *state, double *unused, double *out_6172142331242380649);
void pose_H_14(double *state, double *unused, double *out_3146317917270379405);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}