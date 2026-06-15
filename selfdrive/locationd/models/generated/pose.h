#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7337273534871130421);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7370167163616029780);
void pose_H_mod_fun(double *state, double *out_1839001963735438802);
void pose_f_fun(double *state, double dt, double *out_3683398569821655413);
void pose_F_fun(double *state, double dt, double *out_3094277237620606525);
void pose_h_4(double *state, double *unused, double *out_8966126842197524709);
void pose_H_4(double *state, double *unused, double *out_641054481852540698);
void pose_h_10(double *state, double *unused, double *out_7218356862001512524);
void pose_H_10(double *state, double *unused, double *out_6416512439383232257);
void pose_h_13(double *state, double *unused, double *out_4665077883382816557);
void pose_H_13(double *state, double *unused, double *out_2571219343479792103);
void pose_h_14(double *state, double *unused, double *out_6885640217960215473);
void pose_H_14(double *state, double *unused, double *out_3723842914147912994);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}