#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2235485331980533535);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6263710841243713274);
void pose_H_mod_fun(double *state, double *out_874056645799517577);
void pose_f_fun(double *state, double dt, double *out_7518635824214998963);
void pose_F_fun(double *state, double dt, double *out_2943843104528284461);
void pose_h_4(double *state, double *unused, double *out_7392043206358300323);
void pose_H_4(double *state, double *unused, double *out_5488683682728833941);
void pose_h_10(double *state, double *unused, double *out_1893443682310766933);
void pose_H_10(double *state, double *unused, double *out_4002633890361339640);
void pose_h_13(double *state, double *unused, double *out_950850480842812453);
void pose_H_13(double *state, double *unused, double *out_8700957508061166742);
void pose_h_14(double *state, double *unused, double *out_2845286380404369143);
void pose_H_14(double *state, double *unused, double *out_2405895250433461645);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}