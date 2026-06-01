#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_1277882425838003162);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5395183656796766);
void pose_H_mod_fun(double *state, double *out_4641299731180659481);
void pose_f_fun(double *state, double dt, double *out_4475655607956648045);
void pose_F_fun(double *state, double dt, double *out_1490364464464661376);
void pose_h_4(double *state, double *unused, double *out_4985239385195179173);
void pose_H_4(double *state, double *unused, double *out_2821601005274362620);
void pose_h_10(double *state, double *unused, double *out_5766917160067306951);
void pose_H_10(double *state, double *unused, double *out_393429258268914973);
void pose_h_13(double *state, double *unused, double *out_7359463090555700335);
void pose_H_13(double *state, double *unused, double *out_6033874830606695421);
void pose_h_14(double *state, double *unused, double *out_1914760434129654014);
void pose_H_14(double *state, double *unused, double *out_261187427021009676);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}