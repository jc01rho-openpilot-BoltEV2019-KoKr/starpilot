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
void car_err_fun(double *nom_x, double *delta_x, double *out_7371356248284686223);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3965605218365756510);
void car_H_mod_fun(double *state, double *out_2474093599384348200);
void car_f_fun(double *state, double dt, double *out_2271815562821462998);
void car_F_fun(double *state, double dt, double *out_7600503497871632413);
void car_h_25(double *state, double *unused, double *out_2245281936356175607);
void car_H_25(double *state, double *unused, double *out_7377785424569013040);
void car_h_24(double *state, double *unused, double *out_5229861498965331368);
void car_H_24(double *state, double *unused, double *out_4493386842549020475);
void car_h_30(double *state, double *unused, double *out_9036311057795238262);
void car_H_30(double *state, double *unused, double *out_8550625690633289949);
void car_h_26(double *state, double *unused, double *out_8466923163012650919);
void car_H_26(double *state, double *unused, double *out_7764432679379737975);
void car_h_27(double *state, double *unused, double *out_2036281904887484901);
void car_H_27(double *state, double *unused, double *out_6327031619449346732);
void car_h_29(double *state, double *unused, double *out_7562339341438508014);
void car_H_29(double *state, double *unused, double *out_8040394346318897765);
void car_h_28(double *state, double *unused, double *out_2481951949823838038);
void car_H_28(double *state, double *unused, double *out_5323950710321123277);
void car_h_31(double *state, double *unused, double *out_5123667467256710023);
void car_H_31(double *state, double *unused, double *out_7408431386445973468);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}