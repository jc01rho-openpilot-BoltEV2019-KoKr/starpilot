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
void car_err_fun(double *nom_x, double *delta_x, double *out_4271848112759039807);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2031572598342150124);
void car_H_mod_fun(double *state, double *out_177684180657030354);
void car_f_fun(double *state, double dt, double *out_6521764996120993087);
void car_F_fun(double *state, double dt, double *out_4624398414228863854);
void car_h_25(double *state, double *unused, double *out_5192262937518193843);
void car_H_25(double *state, double *unused, double *out_6857380300493335265);
void car_h_24(double *state, double *unused, double *out_6066922532331985124);
void car_H_24(double *state, double *unused, double *out_4684730701487835699);
void car_h_30(double *state, double *unused, double *out_3741631544889310676);
void car_H_30(double *state, double *unused, double *out_9071030814708967724);
void car_h_26(double *state, double *unused, double *out_7702349825027175161);
void car_H_26(double *state, double *unused, double *out_3115876981619279041);
void car_h_27(double *state, double *unused, double *out_2155476886073861158);
void car_H_27(double *state, double *unused, double *out_7200949947200158981);
void car_h_29(double *state, double *unused, double *out_8743304812550156321);
void car_H_29(double *state, double *unused, double *out_8560799470394575540);
void car_h_28(double *state, double *unused, double *out_1211967033172198723);
void car_H_28(double *state, double *unused, double *out_4803545586245445502);
void car_h_31(double *state, double *unused, double *out_6483645909841006837);
void car_H_31(double *state, double *unused, double *out_2489668879385927565);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}