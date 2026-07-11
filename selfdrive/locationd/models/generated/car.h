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
void car_err_fun(double *nom_x, double *delta_x, double *out_6125726627663246664);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_87606233557452672);
void car_H_mod_fun(double *state, double *out_1571740516032572076);
void car_f_fun(double *state, double dt, double *out_7904413896065989389);
void car_F_fun(double *state, double dt, double *out_6516583174049416628);
void car_h_25(double *state, double *unused, double *out_6845996924949086281);
void car_H_25(double *state, double *unused, double *out_4925282443857457875);
void car_h_24(double *state, double *unused, double *out_76787194833890602);
void car_H_24(double *state, double *unused, double *out_2493109189819469018);
void car_h_30(double *state, double *unused, double *out_7304198287107647943);
void car_H_30(double *state, double *unused, double *out_8993765299724485543);
void car_h_26(double *state, double *unused, double *out_6360688434205985508);
void car_H_26(double *state, double *unused, double *out_8666785762731514099);
void car_h_27(double *state, double *unused, double *out_2448044843667457269);
void car_H_27(double *state, double *unused, double *out_6819001987924060632);
void car_h_29(double *state, double *unused, double *out_2302525019446802298);
void car_H_29(double *state, double *unused, double *out_8942747429670673889);
void car_h_28(double *state, double *unused, double *out_2553628423993388376);
void car_H_28(double *state, double *unused, double *out_4421597626969347153);
void car_h_31(double *state, double *unused, double *out_7359576434127226352);
void car_H_31(double *state, double *unused, double *out_9153750208744686041);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}