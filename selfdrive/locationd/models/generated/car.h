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
void car_err_fun(double *nom_x, double *delta_x, double *out_3329877133651101623);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7760882190653564987);
void car_H_mod_fun(double *state, double *out_1773647306661711299);
void car_f_fun(double *state, double dt, double *out_8265395554005205627);
void car_F_fun(double *state, double dt, double *out_5121501708015469294);
void car_h_25(double *state, double *unused, double *out_1871114119926472838);
void car_H_25(double *state, double *unused, double *out_1749401331983653849);
void car_h_24(double *state, double *unused, double *out_4177328874243606255);
void car_H_24(double *state, double *unused, double *out_1808524266818669287);
void car_h_30(double *state, double *unused, double *out_6625546561337267154);
void car_H_30(double *state, double *unused, double *out_5167289009507962906);
void car_h_26(double *state, double *unused, double *out_8545349699624827873);
void car_H_26(double *state, double *unused, double *out_5490904650857710073);
void car_h_27(double *state, double *unused, double *out_3470753115959557725);
void car_H_27(double *state, double *unused, double *out_2992525697707537995);
void car_h_29(double *state, double *unused, double *out_7569056414238929589);
void car_H_29(double *state, double *unused, double *out_1279162970837986962);
void car_h_28(double *state, double *unused, double *out_6507539167403890410);
void car_H_28(double *state, double *unused, double *out_3803236046231543612);
void car_h_31(double *state, double *unused, double *out_5594040852719868954);
void car_H_31(double *state, double *unused, double *out_1718755370106693421);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}