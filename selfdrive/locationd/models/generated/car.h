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
void car_err_fun(double *nom_x, double *delta_x, double *out_1506475022093702388);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_9143363731815594717);
void car_H_mod_fun(double *state, double *out_9131407703981301731);
void car_f_fun(double *state, double dt, double *out_384729614673600146);
void car_F_fun(double *state, double dt, double *out_7440730494263305444);
void car_h_25(double *state, double *unused, double *out_4252950562849966829);
void car_H_25(double *state, double *unused, double *out_6221318096935853377);
void car_h_24(double *state, double *unused, double *out_3680087672280189791);
void car_H_24(double *state, double *unused, double *out_9166284664138259719);
void car_h_30(double *state, double *unused, double *out_7996626645345091737);
void car_H_30(double *state, double *unused, double *out_7697729646646090041);
void car_h_26(double *state, double *unused, double *out_3034246647663798505);
void car_H_26(double *state, double *unused, double *out_8483922657899642015);
void car_h_27(double *state, double *unused, double *out_3649634678173489312);
void car_H_27(double *state, double *unused, double *out_5522966334845665130);
void car_h_29(double *state, double *unused, double *out_3374440615888983423);
void car_H_29(double *state, double *unused, double *out_8207960990960482225);
void car_h_28(double *state, double *unused, double *out_1352038589487356333);
void car_H_28(double *state, double *unused, double *out_3125561973890951651);
void car_h_31(double *state, double *unused, double *out_8114634039278468481);
void car_H_31(double *state, double *unused, double *out_7857714555666290539);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}