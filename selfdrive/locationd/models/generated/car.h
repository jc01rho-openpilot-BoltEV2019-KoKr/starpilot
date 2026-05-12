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
void car_err_fun(double *nom_x, double *delta_x, double *out_6549097700781342010);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8354153438521949351);
void car_H_mod_fun(double *state, double *out_6316391371516646855);
void car_f_fun(double *state, double dt, double *out_683944865460236824);
void car_F_fun(double *state, double dt, double *out_6256536759651096133);
void car_h_25(double *state, double *unused, double *out_630446739146494899);
void car_H_25(double *state, double *unused, double *out_2937164476280667524);
void car_h_24(double *state, double *unused, double *out_766963748656106214);
void car_H_24(double *state, double *unused, double *out_764514877275167958);
void car_h_30(double *state, double *unused, double *out_2365946185687416261);
void car_H_30(double *state, double *unused, double *out_8592889255937267337);
void car_h_26(double *state, double *unused, double *out_4488774751058732255);
void car_H_26(double *state, double *unused, double *out_804338842593388700);
void car_h_27(double *state, double *unused, double *out_4371226528514350746);
void car_H_27(double *state, double *unused, double *out_7679091505971859368);
void car_h_29(double *state, double *unused, double *out_8008676056768373096);
void car_H_29(double *state, double *unused, double *out_5965728779102308335);
void car_h_28(double *state, double *unused, double *out_5855520433291817842);
void car_H_28(double *state, double *unused, double *out_883329762032777761);
void car_h_31(double *state, double *unused, double *out_2247938791754039517);
void car_H_31(double *state, double *unused, double *out_2967810438157627952);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}