#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5135933030950096940);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4473434694497561565);
void pose_H_mod_fun(double *state, double *out_4955206330411314418);
void pose_f_fun(double *state, double dt, double *out_1052805527796842003);
void pose_F_fun(double *state, double dt, double *out_5871869036335399812);
void pose_h_4(double *state, double *unused, double *out_921118668651624411);
void pose_H_4(double *state, double *unused, double *out_3989155335646506924);
void pose_h_10(double *state, double *unused, double *out_8738369372345178390);
void pose_H_10(double *state, double *unused, double *out_2875729590105375124);
void pose_h_13(double *state, double *unused, double *out_1766623406694503914);
void pose_H_13(double *state, double *unused, double *out_776881510314174123);
void pose_h_14(double *state, double *unused, double *out_4485852814658279598);
void pose_H_14(double *state, double *unused, double *out_4424271862291390523);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}