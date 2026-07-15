#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7322678164781620542);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6351713798129038522);
void pose_H_mod_fun(double *state, double *out_7181373993335857162);
void pose_f_fun(double *state, double dt, double *out_1544031639553813882);
void pose_F_fun(double *state, double dt, double *out_4307246870374060335);
void pose_h_4(double *state, double *unused, double *out_2329964328807098264);
void pose_H_4(double *state, double *unused, double *out_3409566783491949590);
void pose_h_10(double *state, double *unused, double *out_1764029327220956455);
void pose_H_10(double *state, double *unused, double *out_5084421046690710562);
void pose_h_13(double *state, double *unused, double *out_7799867727264054991);
void pose_H_13(double *state, double *unused, double *out_2844964863810105486);
void pose_h_14(double *state, double *unused, double *out_3740143774591228770);
void pose_H_14(double *state, double *unused, double *out_6492355215787321886);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}