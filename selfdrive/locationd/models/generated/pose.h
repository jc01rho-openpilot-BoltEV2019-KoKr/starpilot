#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_8230036097863094971);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8741051770711475830);
void pose_H_mod_fun(double *state, double *out_1900632188772248703);
void pose_f_fun(double *state, double dt, double *out_3077738493587277525);
void pose_F_fun(double *state, double dt, double *out_474426866180563475);
void pose_h_4(double *state, double *unused, double *out_616527671886839495);
void pose_H_4(double *state, double *unused, double *out_702684706889350599);
void pose_h_10(double *state, double *unused, double *out_767369525646024651);
void pose_H_10(double *state, double *unused, double *out_8347276505705953254);
void pose_h_13(double *state, double *unused, double *out_7518652466578138352);
void pose_H_13(double *state, double *unused, double *out_2509589118442982202);
void pose_h_14(double *state, double *unused, double *out_7727744869207997497);
void pose_H_14(double *state, double *unused, double *out_8183830522169091023);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}