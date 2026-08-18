#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2182435369834896236);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2883166859334089197);
void pose_H_mod_fun(double *state, double *out_671491409411989589);
void pose_f_fun(double *state, double dt, double *out_7919031781502386377);
void pose_F_fun(double *state, double dt, double *out_7380360880106775220);
void pose_h_4(double *state, double *unused, double *out_4702057929225754412);
void pose_H_4(double *state, double *unused, double *out_3100315800431917983);
void pose_h_10(double *state, double *unused, double *out_1901997026290432130);
void pose_H_10(double *state, double *unused, double *out_5200655737232907775);
void pose_h_13(double *state, double *unused, double *out_6749072148499604094);
void pose_H_13(double *state, double *unused, double *out_6312589625764250784);
void pose_h_14(double *state, double *unused, double *out_7677380843386584152);
void pose_H_14(double *state, double *unused, double *out_17527368136545687);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}