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
void car_err_fun(double *nom_x, double *delta_x, double *out_6442273530103712235);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8945695091662043361);
void car_H_mod_fun(double *state, double *out_515428113062222019);
void car_f_fun(double *state, double dt, double *out_1011805063482308945);
void car_F_fun(double *state, double dt, double *out_5888946012615310003);
void car_h_25(double *state, double *unused, double *out_765665439417021084);
void car_H_25(double *state, double *unused, double *out_10093670861925307);
void car_h_24(double *state, double *unused, double *out_7010003887632078552);
void car_H_24(double *state, double *unused, double *out_8784986078674096201);
void car_h_30(double *state, double *unused, double *out_3713391429772506045);
void car_H_30(double *state, double *unused, double *out_6906596670629691448);
void car_h_26(double *state, double *unused, double *out_6525943533042359428);
void car_H_26(double *state, double *unused, double *out_3751596989735981531);
void car_h_27(double *state, double *unused, double *out_3564565336305065623);
void car_H_27(double *state, double *unused, double *out_4731833358829266537);
void car_h_29(double *state, double *unused, double *out_4316707314448983562);
void car_H_29(double *state, double *unused, double *out_7416828014944083632);
void car_h_28(double *state, double *unused, double *out_8899254898098344240);
void car_H_28(double *state, double *unused, double *out_2063928385109815070);
void car_h_31(double *state, double *unused, double *out_7115607211337028101);
void car_H_31(double *state, double *unused, double *out_20552291015035121);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}