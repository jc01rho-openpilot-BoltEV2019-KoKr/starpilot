#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_4154280524256563890);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5487211563177375728);
void pose_H_mod_fun(double *state, double *out_6762039440372011872);
void pose_f_fun(double *state, double dt, double *out_2487690271541209027);
void pose_F_fun(double *state, double dt, double *out_950182517979020623);
void pose_h_4(double *state, double *unused, double *out_1064982969821053038);
void pose_H_4(double *state, double *unused, double *out_1976156791710977266);
void pose_h_10(double *state, double *unused, double *out_9039008373436645978);
void pose_H_10(double *state, double *unused, double *out_6832717040485250243);
void pose_h_13(double *state, double *unused, double *out_6939466162668529956);
void pose_H_13(double *state, double *unused, double *out_2540758711392821370);
void pose_h_14(double *state, double *unused, double *out_542665533068743617);
void pose_H_14(double *state, double *unused, double *out_1106631640584395030);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}