#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_9170572944906816852);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4867215415263963768);
void pose_H_mod_fun(double *state, double *out_1396735664605592698);
void pose_f_fun(double *state, double dt, double *out_916482441408583797);
void pose_F_fun(double *state, double dt, double *out_5639772936950525263);
void pose_h_4(double *state, double *unused, double *out_5848855439961291946);
void pose_H_4(double *state, double *unused, double *out_3290246568201368788);
void pose_h_10(double *state, double *unused, double *out_3954090448202517665);
void pose_H_10(double *state, double *unused, double *out_1376781969837987839);
void pose_h_13(double *state, double *unused, double *out_8116870387044428464);
void pose_H_13(double *state, double *unused, double *out_77972742869035987);
void pose_h_14(double *state, double *unused, double *out_2879136579664093334);
void pose_H_14(double *state, double *unused, double *out_672994288138115741);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}