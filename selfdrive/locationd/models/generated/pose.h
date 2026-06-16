#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6392571160168570842);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_70108598084165787);
void pose_H_mod_fun(double *state, double *out_7031029695439970094);
void pose_f_fun(double *state, double dt, double *out_4622611615613940133);
void pose_F_fun(double *state, double dt, double *out_542246045313485722);
void pose_h_4(double *state, double *unused, double *out_6293306196609579881);
void pose_H_4(double *state, double *unused, double *out_1878511310400889359);
void pose_h_10(double *state, double *unused, double *out_8801939057301033560);
void pose_H_10(double *state, double *unused, double *out_2335330326985309171);
void pose_h_13(double *state, double *unused, double *out_442641261201264592);
void pose_H_13(double *state, double *unused, double *out_5712266773703413383);
void pose_h_14(double *state, double *unused, double *out_6788275849684674744);
void pose_H_14(double *state, double *unused, double *out_4961299742696261655);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}