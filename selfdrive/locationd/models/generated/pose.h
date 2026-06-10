#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5797775412313342444);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6978859077859564623);
void pose_H_mod_fun(double *state, double *out_7486978165612535736);
void pose_f_fun(double *state, double dt, double *out_7331794505583909673);
void pose_F_fun(double *state, double dt, double *out_6844171548938607295);
void pose_h_4(double *state, double *unused, double *out_7129002449097779903);
void pose_H_4(double *state, double *unused, double *out_1457383500445285606);
void pose_h_10(double *state, double *unused, double *out_3148302492513217557);
void pose_H_10(double *state, double *unused, double *out_4488407256990316453);
void pose_h_13(double *state, double *unused, double *out_3993880518003112603);
void pose_H_13(double *state, double *unused, double *out_1754890324887047195);
void pose_h_14(double *state, double *unused, double *out_318727471713913742);
void pose_H_14(double *state, double *unused, double *out_4540171932740657902);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}