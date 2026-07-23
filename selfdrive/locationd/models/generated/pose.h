#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5522943408677507622);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4295983432349839383);
void pose_H_mod_fun(double *state, double *out_4346696932482416909);
void pose_f_fun(double *state, double dt, double *out_6102158893978946471);
void pose_F_fun(double *state, double dt, double *out_2499898042682651457);
void pose_h_4(double *state, double *unused, double *out_3279047988568344132);
void pose_H_4(double *state, double *unused, double *out_5899742257253909940);
void pose_h_10(double *state, double *unused, double *out_9007933995216703840);
void pose_H_10(double *state, double *unused, double *out_2326992144684427807);
void pose_h_13(double *state, double *unused, double *out_8858214994014047499);
void pose_H_13(double *state, double *unused, double *out_1710888951062790989);
void pose_h_14(double *state, double *unused, double *out_7751194400543680936);
void pose_H_14(double *state, double *unused, double *out_1936501400914425411);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}