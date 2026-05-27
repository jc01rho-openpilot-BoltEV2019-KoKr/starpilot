#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5735299356181127199);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1848486118618361424);
void pose_H_mod_fun(double *state, double *out_3441620345746718845);
void pose_f_fun(double *state, double dt, double *out_5548337699276970526);
void pose_F_fun(double *state, double dt, double *out_6716874081947285130);
void pose_h_4(double *state, double *unused, double *out_6172444408937598103);
void pose_H_4(double *state, double *unused, double *out_5296575886336270293);
void pose_h_10(double *state, double *unused, double *out_2819440341260442129);
void pose_H_10(double *state, double *unused, double *out_5042249891606824417);
void pose_h_13(double *state, double *unused, double *out_3164753833559588683);
void pose_H_13(double *state, double *unused, double *out_8508849711668603094);
void pose_h_14(double *state, double *unused, double *out_3107433859522874355);
void pose_H_14(double *state, double *unused, double *out_2213787454040897997);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}