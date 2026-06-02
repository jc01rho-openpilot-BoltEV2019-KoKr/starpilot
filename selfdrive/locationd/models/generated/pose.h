#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_842964569186968919);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7637995249051351300);
void pose_H_mod_fun(double *state, double *out_8306889626903079841);
void pose_f_fun(double *state, double dt, double *out_5013225008344736149);
void pose_F_fun(double *state, double dt, double *out_8990818239492707931);
void pose_h_4(double *state, double *unused, double *out_4553534383789500912);
void pose_H_4(double *state, double *unused, double *out_637472039154741501);
void pose_h_10(double *state, double *unused, double *out_5896232866039695568);
void pose_H_10(double *state, double *unused, double *out_6470002192212990620);
void pose_h_13(double *state, double *unused, double *out_5564060116117934481);
void pose_H_13(double *state, double *unused, double *out_2574801786177591300);
void pose_h_14(double *state, double *unused, double *out_9129729305013669813);
void pose_H_14(double *state, double *unused, double *out_3325768817184743028);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}