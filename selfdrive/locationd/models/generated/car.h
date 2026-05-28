#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_5406094264205448922);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7302786751934147898);
void car_H_mod_fun(double *state, double *out_8564810489090289784);
void car_f_fun(double *state, double dt, double *out_7344896958720977953);
void car_F_fun(double *state, double dt, double *out_4577316669100378715);
void car_h_25(double *state, double *unused, double *out_6986192086353969465);
void car_H_25(double *state, double *unused, double *out_628377736821947453);
void car_h_24(double *state, double *unused, double *out_434665502247836674);
void car_H_24(double *state, double *unused, double *out_2801027335827447019);
void car_h_30(double *state, double *unused, double *out_4915078315896353947);
void car_H_30(double *state, double *unused, double *out_6288312604669669302);
void car_h_26(double *state, double *unused, double *out_4943503076008356261);
void car_H_26(double *state, double *unused, double *out_4369881055696003677);
void car_h_27(double *state, double *unused, double *out_1984518818693123820);
void car_H_27(double *state, double *unused, double *out_2932479995765612434);
void car_h_29(double *state, double *unused, double *out_963207171662361141);
void car_H_29(double *state, double *unused, double *out_4645842722635163467);
void car_h_28(double *state, double *unused, double *out_1002434725357825708);
void car_H_28(double *state, double *unused, double *out_2682212451069837216);
void car_h_31(double *state, double *unused, double *out_7261386148638475354);
void car_H_31(double *state, double *unused, double *out_597731774944987025);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}