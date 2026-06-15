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
void car_err_fun(double *nom_x, double *delta_x, double *out_7743770409471347977);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5655670642369359584);
void car_H_mod_fun(double *state, double *out_6127138549200260168);
void car_f_fun(double *state, double dt, double *out_7372877337496608143);
void car_F_fun(double *state, double dt, double *out_6312844150465459340);
void car_h_25(double *state, double *unused, double *out_5527658313899534193);
void car_H_25(double *state, double *unused, double *out_6632472991400556880);
void car_h_24(double *state, double *unused, double *out_8053196144855152976);
void car_H_24(double *state, double *unused, double *out_5238699275717476635);
void car_h_30(double *state, double *unused, double *out_5715869802824031453);
void car_H_30(double *state, double *unused, double *out_4897580740817377981);
void car_h_26(double *state, double *unused, double *out_1526064504003558173);
void car_H_26(double *state, double *unused, double *out_2890969672526500656);
void car_h_27(double *state, double *unused, double *out_8564444365343866878);
void car_H_27(double *state, double *unused, double *out_7072344052617802892);
void car_h_29(double *state, double *unused, double *out_683171714589817693);
void car_H_29(double *state, double *unused, double *out_4387349396502985797);
void car_h_28(double *state, double *unused, double *out_8938789855464022303);
void car_H_28(double *state, double *unused, double *out_8976995660137035245);
void car_h_31(double *state, double *unused, double *out_6331257833333722260);
void car_H_31(double *state, double *unused, double *out_6663118953277517308);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}