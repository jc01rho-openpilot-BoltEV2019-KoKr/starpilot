#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_4926409855120774640);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6187782627613179741);
void pose_H_mod_fun(double *state, double *out_5486902536301149939);
void pose_f_fun(double *state, double dt, double *out_8359863438222097271);
void pose_F_fun(double *state, double dt, double *out_174815157734899050);
void pose_h_4(double *state, double *unused, double *out_388088547893374228);
void pose_H_4(double *state, double *unused, double *out_3526081883612534553);
void pose_h_10(double *state, double *unused, double *out_3651567794159293424);
void pose_H_10(double *state, double *unused, double *out_7553527708872310168);
void pose_h_13(double *state, double *unused, double *out_5975295746890546976);
void pose_H_13(double *state, double *unused, double *out_6738355708944867354);
void pose_h_14(double *state, double *unused, double *out_7017148445173920389);
void pose_H_14(double *state, double *unused, double *out_7489322739952019082);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}