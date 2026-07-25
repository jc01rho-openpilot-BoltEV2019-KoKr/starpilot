#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2803054085873220166);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_870718263858356541);
void pose_H_mod_fun(double *state, double *out_245560868528396178);
void pose_f_fun(double *state, double dt, double *out_8465405656783528291);
void pose_F_fun(double *state, double dt, double *out_5153518595662752782);
void pose_h_4(double *state, double *unused, double *out_3441983837194168135);
void pose_H_4(double *state, double *unused, double *out_3792847385831294211);
void pose_h_10(double *state, double *unused, double *out_6864246601547225854);
void pose_H_10(double *state, double *unused, double *out_5871577252215708993);
void pose_h_13(double *state, double *unused, double *out_3325053226247216097);
void pose_H_13(double *state, double *unused, double *out_580573560498961410);
void pose_h_14(double *state, double *unused, double *out_7213076452181803827);
void pose_H_14(double *state, double *unused, double *out_170393470508190318);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}