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
void car_err_fun(double *nom_x, double *delta_x, double *out_2605865889076671127);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6092587495462394066);
void car_H_mod_fun(double *state, double *out_5416567318777544442);
void car_f_fun(double *state, double dt, double *out_8892385645104681966);
void car_F_fun(double *state, double dt, double *out_8140915848168938492);
void car_h_25(double *state, double *unused, double *out_7505552333880797139);
void car_H_25(double *state, double *unused, double *out_1893586668788052765);
void car_h_24(double *state, double *unused, double *out_6517755359246205097);
void car_H_24(double *state, double *unused, double *out_1664338930014270371);
void car_h_30(double *state, double *unused, double *out_5415134303277731364);
void car_H_30(double *state, double *unused, double *out_2022925615931292835);
void car_h_26(double *state, double *unused, double *out_6358644156179393799);
void car_H_26(double *state, double *unused, double *out_5635089987662108989);
void car_h_27(double *state, double *unused, double *out_2535534920184527824);
void car_H_27(double *state, double *unused, double *out_4197688927731717746);
void car_h_29(double *state, double *unused, double *out_443846924135533467);
void car_H_29(double *state, double *unused, double *out_1512694271616900651);
void car_h_28(double *state, double *unused, double *out_7537208187845373469);
void car_H_28(double *state, double *unused, double *out_6595093288686431225);
void car_h_31(double *state, double *unused, double *out_6103587875730340171);
void car_H_31(double *state, double *unused, double *out_1862940706911092337);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}