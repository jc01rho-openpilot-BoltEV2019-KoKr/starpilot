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
void car_err_fun(double *nom_x, double *delta_x, double *out_5325374827696631328);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_263695042767338590);
void car_H_mod_fun(double *state, double *out_2663737869404174494);
void car_f_fun(double *state, double dt, double *out_8230420991833863893);
void car_F_fun(double *state, double dt, double *out_2756618938696411588);
void car_h_25(double *state, double *unused, double *out_2585399580963523364);
void car_H_25(double *state, double *unused, double *out_4993569966627829866);
void car_h_24(double *state, double *unused, double *out_7866369606921911129);
void car_H_24(double *state, double *unused, double *out_124755101600123014);
void car_h_30(double *state, double *unused, double *out_1052049947290498986);
void car_H_30(double *state, double *unused, double *out_465873636500221668);
void car_h_26(double *state, double *unused, double *out_3137755351529974294);
void car_H_26(double *state, double *unused, double *out_1252066647753773642);
void car_h_27(double *state, double *unused, double *out_3292885906595191724);
void car_H_27(double *state, double *unused, double *out_2689467707684164885);
void car_h_29(double *state, double *unused, double *out_5346991570123350160);
void car_H_29(double *state, double *unused, double *out_976104980814613852);
void car_h_28(double *state, double *unused, double *out_6565695485309518484);
void car_H_28(double *state, double *unused, double *out_2939735252379940103);
void car_h_31(double *state, double *unused, double *out_7496068987004855670);
void car_H_31(double *state, double *unused, double *out_625858545520422166);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}