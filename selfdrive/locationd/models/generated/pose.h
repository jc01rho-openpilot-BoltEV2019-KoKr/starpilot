#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_9183838211698085113);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7880707634176237912);
void pose_H_mod_fun(double *state, double *out_4757006295873358620);
void pose_f_fun(double *state, double dt, double *out_9118920386528411329);
void pose_F_fun(double *state, double dt, double *out_388070008261359487);
void pose_h_4(double *state, double *unused, double *out_424143301988092518);
void pose_H_4(double *state, double *unused, double *out_6650517199469134710);
void pose_h_10(double *state, double *unused, double *out_5429944465818265103);
void pose_H_10(double *state, double *unused, double *out_6328749297458135702);
void pose_h_13(double *state, double *unused, double *out_7408027604108256403);
void pose_H_13(double *state, double *unused, double *out_3438243374136801909);
void pose_h_14(double *state, double *unused, double *out_1915359263866192008);
void pose_H_14(double *state, double *unused, double *out_2687276343129650181);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}