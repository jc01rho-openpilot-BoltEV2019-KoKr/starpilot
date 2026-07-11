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
void car_err_fun(double *nom_x, double *delta_x, double *out_1054824998219177113);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8618844445394053899);
void car_H_mod_fun(double *state, double *out_9083000739620874267);
void car_f_fun(double *state, double dt, double *out_2939712332855985662);
void car_F_fun(double *state, double dt, double *out_9197210553723469698);
void car_h_25(double *state, double *unused, double *out_7502443551709492094);
void car_H_25(double *state, double *unused, double *out_2585977779730844316);
void car_h_24(double *state, double *unused, double *out_4099652252284200208);
void car_H_24(double *state, double *unused, double *out_2115520297687505592);
void car_h_30(double *state, double *unused, double *out_7659630220060621239);
void car_H_30(double *state, double *unused, double *out_2456638832587604246);
void car_h_26(double *state, double *unused, double *out_2198951171844088969);
void car_H_26(double *state, double *unused, double *out_1155525539143211908);
void car_h_27(double *state, double *unused, double *out_5981920524318766290);
void car_H_27(double *state, double *unused, double *out_281875520787179335);
void car_h_29(double *state, double *unused, double *out_1781344732501906151);
void car_H_29(double *state, double *unused, double *out_1431487206082371698);
void car_h_28(double *state, double *unused, double *out_2565647234669696274);
void car_H_28(double *state, double *unused, double *out_6513886223151902272);
void car_h_31(double *state, double *unused, double *out_7751082483008271581);
void car_H_31(double *state, double *unused, double *out_2616623741607804744);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}