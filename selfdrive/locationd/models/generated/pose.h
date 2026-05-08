#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2526150130430510074);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3515561648914426109);
void pose_H_mod_fun(double *state, double *out_6056162720073724257);
void pose_f_fun(double *state, double dt, double *out_8780284750928315681);
void pose_F_fun(double *state, double dt, double *out_1516035527731464330);
void pose_h_4(double *state, double *unused, double *out_4492721189395603550);
void pose_H_4(double *state, double *unused, double *out_4858215238190826153);
void pose_h_10(double *state, double *unused, double *out_558240635521768637);
void pose_H_10(double *state, double *unused, double *out_7377176961528777036);
void pose_h_13(double *state, double *unused, double *out_3864223786954470726);
void pose_H_13(double *state, double *unused, double *out_1645941412858493352);
void pose_h_14(double *state, double *unused, double *out_2242454366414003666);
void pose_H_14(double *state, double *unused, double *out_7941003670486198449);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}