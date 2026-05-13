#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1909500707924070274);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4767002163824434397);
void pose_H_mod_fun(double *state, double *out_2632577706224621837);
void pose_f_fun(double *state, double dt, double *out_2193527682870666897);
void pose_F_fun(double *state, double dt, double *out_7071521444289373248);
void pose_h_4(double *state, double *unused, double *out_67509566290800345);
void pose_H_4(double *state, double *unused, double *out_3215504100527336884);
void pose_h_10(double *state, double *unused, double *out_2077999983659095687);
void pose_H_10(double *state, double *unused, double *out_1146830641480722290);
void pose_h_13(double *state, double *unused, double *out_7759616382768276568);
void pose_H_13(double *state, double *unused, double *out_3230275195004083);
void pose_h_14(double *state, double *unused, double *out_3709581126101699448);
void pose_H_14(double *state, double *unused, double *out_3650620627172220483);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}