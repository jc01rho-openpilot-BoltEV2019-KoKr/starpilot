#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_8123935570106658818);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7916605304970807670);
void pose_H_mod_fun(double *state, double *out_1602815725505969341);
void pose_f_fun(double *state, double dt, double *out_6941148323357631663);
void pose_F_fun(double *state, double dt, double *out_8174317485626071951);
void pose_h_4(double *state, double *unused, double *out_5523365294760256360);
void pose_H_4(double *state, double *unused, double *out_848654723451256734);
void pose_h_10(double *state, double *unused, double *out_1239079208898706284);
void pose_H_10(double *state, double *unused, double *out_1001724707531765931);
void pose_h_13(double *state, double *unused, double *out_7307670055393162069);
void pose_H_13(double *state, double *unused, double *out_6761976484865444195);
void pose_h_14(double *state, double *unused, double *out_7233663736752442507);
void pose_H_14(double *state, double *unused, double *out_3114586132888227795);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}