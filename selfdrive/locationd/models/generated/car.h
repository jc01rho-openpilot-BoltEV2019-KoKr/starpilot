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
void car_err_fun(double *nom_x, double *delta_x, double *out_648770422652277661);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8433637752559620590);
void car_H_mod_fun(double *state, double *out_8422599956511423720);
void car_f_fun(double *state, double dt, double *out_9124674145630526498);
void car_F_fun(double *state, double dt, double *out_7980063177758984153);
void car_h_25(double *state, double *unused, double *out_7427457988301314284);
void car_H_25(double *state, double *unused, double *out_770588269400813517);
void car_h_24(double *state, double *unused, double *out_3062542313716558558);
void car_H_24(double *state, double *unused, double *out_5590909774056801780);
void car_h_30(double *state, double *unused, double *out_1260343948330179981);
void car_H_30(double *state, double *unused, double *out_899927216544053587);
void car_h_26(double *state, double *unused, double *out_4488267301164684189);
void car_H_26(double *state, double *unused, double *out_4512091588274869741);
void car_h_27(double *state, double *unused, double *out_6340731339944849957);
void car_H_27(double *state, double *unused, double *out_3074690528344478498);
void car_h_29(double *state, double *unused, double *out_8468563205510679309);
void car_H_29(double *state, double *unused, double *out_389695872229661403);
void car_h_28(double *state, double *unused, double *out_7104339466103856014);
void car_H_28(double *state, double *unused, double *out_8576291801425991511);
void car_h_31(double *state, double *unused, double *out_2522625404144497340);
void car_H_31(double *state, double *unused, double *out_739942307523853089);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}