#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_4294292118997978771);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4013254910072164359);
void pose_H_mod_fun(double *state, double *out_896657555631845271);
void pose_f_fun(double *state, double dt, double *out_8443743878960458350);
void pose_F_fun(double *state, double dt, double *out_8213357667145446301);
void pose_h_4(double *state, double *unused, double *out_70651799205578182);
void pose_H_4(double *state, double *unused, double *out_6049175940670926006);
void pose_h_10(double *state, double *unused, double *out_3996731865855353315);
void pose_H_10(double *state, double *unused, double *out_1029675721885226562);
void pose_h_13(double *state, double *unused, double *out_5486873982549130902);
void pose_H_13(double *state, double *unused, double *out_9185294307706292809);
void pose_h_14(double *state, double *unused, double *out_5889763171134805790);
void pose_H_14(double *state, double *unused, double *out_8434327276699141081);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}