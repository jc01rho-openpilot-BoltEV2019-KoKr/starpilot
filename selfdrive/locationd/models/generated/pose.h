#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2423125642091007723);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1501585610038659930);
void pose_H_mod_fun(double *state, double *out_313504174478215792);
void pose_f_fun(double *state, double dt, double *out_8978916703249748052);
void pose_F_fun(double *state, double dt, double *out_3060487946531646253);
void pose_h_4(double *state, double *unused, double *out_2072690755108230087);
void pose_H_4(double *state, double *unused, double *out_440656827576496815);
void pose_h_10(double *state, double *unused, double *out_3685903144892211871);
void pose_H_10(double *state, double *unused, double *out_7274933657249705055);
void pose_h_13(double *state, double *unused, double *out_7605941513603236476);
void pose_H_13(double *state, double *unused, double *out_3652930652908829616);
void pose_h_14(double *state, double *unused, double *out_732635666688386653);
void pose_H_14(double *state, double *unused, double *out_4403897683915981344);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}