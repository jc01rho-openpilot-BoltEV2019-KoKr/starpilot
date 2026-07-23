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
void car_err_fun(double *nom_x, double *delta_x, double *out_2798728055434719104);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5158994837086933641);
void car_H_mod_fun(double *state, double *out_8807292285450126459);
void car_f_fun(double *state, double dt, double *out_547624329025478730);
void car_F_fun(double *state, double dt, double *out_6298604141859123794);
void car_h_25(double *state, double *unused, double *out_5598542368802412337);
void car_H_25(double *state, double *unused, double *out_446263562347187920);
void car_h_24(double *state, double *unused, double *out_281619709901739940);
void car_H_24(double *state, double *unused, double *out_4300245764619321114);
void car_h_30(double *state, double *unused, double *out_6077366478556788343);
void car_H_30(double *state, double *unused, double *out_7362953903838804675);
void car_h_26(double *state, double *unused, double *out_714876495074943436);
void car_H_26(double *state, double *unused, double *out_3295239756526868304);
void car_h_27(double *state, double *unused, double *out_3197767095463584803);
void car_H_27(double *state, double *unused, double *out_5188190592038379764);
void car_h_29(double *state, double *unused, double *out_9093529782405306684);
void car_H_29(double *state, double *unused, double *out_7873185248153196859);
void car_h_28(double *state, double *unused, double *out_8199440363124430448);
void car_H_28(double *state, double *unused, double *out_2790786231083666285);
void car_h_31(double *state, double *unused, double *out_5441355700451283192);
void car_H_31(double *state, double *unused, double *out_476909524224148348);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}