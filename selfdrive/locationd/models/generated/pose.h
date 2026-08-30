#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3122087598286484509);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6671609920081726507);
void pose_H_mod_fun(double *state, double *out_6807142630278803635);
void pose_f_fun(double *state, double dt, double *out_6438279809192142379);
void pose_F_fun(double *state, double dt, double *out_8719681830852947447);
void pose_h_4(double *state, double *unused, double *out_2598619130748282794);
void pose_H_4(double *state, double *unused, double *out_2137219035779017707);
void pose_h_10(double *state, double *unused, double *out_7728804711762559661);
void pose_H_10(double *state, double *unused, double *out_3682779017075027073);
void pose_h_13(double *state, double *unused, double *out_8746038974809318358);
void pose_H_13(double *state, double *unused, double *out_1075054789553315094);
void pose_h_14(double *state, double *unused, double *out_4279600364142536095);
void pose_H_14(double *state, double *unused, double *out_5220007468074390003);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}