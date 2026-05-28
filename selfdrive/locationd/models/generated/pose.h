#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6989025868442055132);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3172938755845140042);
void pose_H_mod_fun(double *state, double *out_3225867917449183727);
void pose_f_fun(double *state, double dt, double *out_2533972772359230172);
void pose_F_fun(double *state, double dt, double *out_3663800095301942537);
void pose_h_4(double *state, double *unused, double *out_223446469702120852);
void pose_H_4(double *state, double *unused, double *out_4324406006264935836);
void pose_h_10(double *state, double *unused, double *out_2753848967308463071);
void pose_H_10(double *state, double *unused, double *out_1159288756680005657);
void pose_h_13(double *state, double *unused, double *out_4379566868646893753);
void pose_H_13(double *state, double *unused, double *out_8158161469567459860);
void pose_h_14(double *state, double *unused, double *out_8438977474921151403);
void pose_H_14(double *state, double *unused, double *out_7407194438560308132);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}