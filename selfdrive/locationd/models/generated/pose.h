#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5340642756295943636);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6968876690248087810);
void pose_H_mod_fun(double *state, double *out_3389862186663429553);
void pose_f_fun(double *state, double dt, double *out_4802700997878092668);
void pose_F_fun(double *state, double dt, double *out_8725044315227912670);
void pose_h_4(double *state, double *unused, double *out_1359340648735360631);
void pose_H_4(double *state, double *unused, double *out_4587809668546327657);
void pose_h_10(double *state, double *unused, double *out_6036145492114111302);
void pose_H_10(double *state, double *unused, double *out_7466880812702133914);
void pose_h_13(double *state, double *unused, double *out_863073697323037062);
void pose_H_13(double *state, double *unused, double *out_7800083493878660458);
void pose_h_14(double *state, double *unused, double *out_1770197321873156194);
void pose_H_14(double *state, double *unused, double *out_1505021236250955361);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}