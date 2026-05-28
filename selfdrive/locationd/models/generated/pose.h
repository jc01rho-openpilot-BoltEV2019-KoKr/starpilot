#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6497612872484174174);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1975580934350294204);
void pose_H_mod_fun(double *state, double *out_4617418789543565628);
void pose_f_fun(double *state, double dt, double *out_9094503671864348345);
void pose_F_fun(double *state, double dt, double *out_1312959600226932432);
void pose_h_4(double *state, double *unused, double *out_6400948089178504221);
void pose_H_4(double *state, double *unused, double *out_3419471307660667524);
void pose_h_10(double *state, double *unused, double *out_8540054287512262719);
void pose_H_10(double *state, double *unused, double *out_5231659216258162963);
void pose_h_13(double *state, double *unused, double *out_7953441679753433349);
void pose_H_13(double *state, double *unused, double *out_207197482328334723);
void pose_h_14(double *state, double *unused, double *out_8785755176393893631);
void pose_H_14(double *state, double *unused, double *out_543769548678817005);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}