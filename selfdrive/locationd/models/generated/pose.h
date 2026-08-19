#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7828077856483360191);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_978622641958652250);
void pose_H_mod_fun(double *state, double *out_7441553898687288237);
void pose_f_fun(double *state, double dt, double *out_8648120814934185415);
void pose_F_fun(double *state, double dt, double *out_5073381682457521558);
void pose_h_4(double *state, double *unused, double *out_2401275546657747080);
void pose_H_4(double *state, double *unused, double *out_1593472091935329516);
void pose_h_10(double *state, double *unused, double *out_7020895229304053766);
void pose_H_10(double *state, double *unused, double *out_299233475658510513);
void pose_h_13(double *state, double *unused, double *out_2810480351238834931);
void pose_H_13(double *state, double *unused, double *out_4805745917267662317);
void pose_h_14(double *state, double *unused, double *out_6318162405249945056);
void pose_H_14(double *state, double *unused, double *out_5556712948274814045);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}