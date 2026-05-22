#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2276930388742637984);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5553036191683273841);
void pose_H_mod_fun(double *state, double *out_9138325999640393464);
void pose_f_fun(double *state, double dt, double *out_1147502803036589913);
void pose_F_fun(double *state, double dt, double *out_5222045031026609980);
void pose_h_4(double *state, double *unused, double *out_9011768275853426182);
void pose_H_4(double *state, double *unused, double *out_3460336267317199431);
void pose_h_10(double *state, double *unused, double *out_678012550926290311);
void pose_H_10(double *state, double *unused, double *out_4795577018961183743);
void pose_h_13(double *state, double *unused, double *out_7050071971782529116);
void pose_H_13(double *state, double *unused, double *out_6672610092649532232);
void pose_h_14(double *state, double *unused, double *out_2771996280971910329);
void pose_H_14(double *state, double *unused, double *out_7423577123656683960);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}