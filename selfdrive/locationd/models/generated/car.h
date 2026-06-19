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
void car_err_fun(double *nom_x, double *delta_x, double *out_7228457580426239955);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1737471906525172971);
void car_H_mod_fun(double *state, double *out_2159575818972962605);
void car_f_fun(double *state, double dt, double *out_1819714955702057293);
void car_F_fun(double *state, double dt, double *out_5560137472532626832);
void car_h_25(double *state, double *unused, double *out_3269510566889334287);
void car_H_25(double *state, double *unused, double *out_5144733109508563382);
void car_h_24(double *state, double *unused, double *out_2726228600494227622);
void car_H_24(double *state, double *unused, double *out_9127056260906331280);
void car_h_30(double *state, double *unused, double *out_6537356030101675445);
void car_H_30(double *state, double *unused, double *out_2626400151001314755);
void car_h_26(double *state, double *unused, double *out_4474244609179175358);
void car_H_26(double *state, double *unused, double *out_1840207139747762781);
void car_h_27(double *state, double *unused, double *out_4356237215245798614);
void car_H_27(double *state, double *unused, double *out_4801163462801739666);
void car_h_29(double *state, double *unused, double *out_5593846177200013010);
void car_H_29(double *state, double *unused, double *out_2116168806686922571);
void car_h_28(double *state, double *unused, double *out_6655363424035052189);
void car_H_28(double *state, double *unused, double *out_7198567823756453145);
void car_h_31(double *state, double *unused, double *out_8813639528518401468);
void car_H_31(double *state, double *unused, double *out_8934299543093580534);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}