#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3650099251769799718);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4549899801136771746);
void pose_H_mod_fun(double *state, double *out_6815214623410224821);
void pose_f_fun(double *state, double dt, double *out_4724171785691844407);
void pose_F_fun(double *state, double dt, double *out_638456415896569458);
void pose_h_4(double *state, double *unused, double *out_3715383509872023288);
void pose_H_4(double *state, double *unused, double *out_7859722240455419223);
void pose_h_10(double *state, double *unused, double *out_1493881979826544307);
void pose_H_10(double *state, double *unused, double *out_8226181140571901267);
void pose_h_13(double *state, double *unused, double *out_820596947016455055);
void pose_H_13(double *state, double *unused, double *out_4647448415123086422);
void pose_h_14(double *state, double *unused, double *out_7488710011373447915);
void pose_H_14(double *state, double *unused, double *out_3896481384115934694);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}