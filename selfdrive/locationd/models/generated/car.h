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
void car_err_fun(double *nom_x, double *delta_x, double *out_8339538066892951453);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1869575881362213489);
void car_H_mod_fun(double *state, double *out_4134445094065349854);
void car_f_fun(double *state, double dt, double *out_1187519494066628558);
void car_F_fun(double *state, double dt, double *out_638221139616797346);
void car_h_25(double *state, double *unused, double *out_6007362445110034756);
void car_H_25(double *state, double *unused, double *out_5119110753731964525);
void car_h_24(double *state, double *unused, double *out_5449620096162801389);
void car_H_24(double *state, double *unused, double *out_2946461154726464959);
void car_h_30(double *state, double *unused, double *out_2369912916856012406);
void car_H_30(double *state, double *unused, double *out_7637443712239213152);
void car_h_26(double *state, double *unused, double *out_6836290203325307661);
void car_H_26(double *state, double *unused, double *out_1377607434857908301);
void car_h_27(double *state, double *unused, double *out_2710474474758657570);
void car_H_27(double *state, double *unused, double *out_8585706290286395247);
void car_h_29(double *state, double *unused, double *out_1542363084005055587);
void car_H_29(double *state, double *unused, double *out_8147675056553605336);
void car_h_28(double *state, double *unused, double *out_7712147742419503215);
void car_H_28(double *state, double *unused, double *out_3065276039484074762);
void car_h_31(double *state, double *unused, double *out_6282556507394540645);
void car_H_31(double *state, double *unused, double *out_5149756715608924953);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}