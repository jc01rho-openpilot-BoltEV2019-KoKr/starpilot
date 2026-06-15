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
void car_err_fun(double *nom_x, double *delta_x, double *out_885257502884011965);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6192379265473109268);
void car_H_mod_fun(double *state, double *out_1067171112169386981);
void car_f_fun(double *state, double dt, double *out_6825209250572789160);
void car_F_fun(double *state, double dt, double *out_1474779246882826642);
void car_h_25(double *state, double *unused, double *out_4524197194175300932);
void car_H_25(double *state, double *unused, double *out_8126017113742850256);
void car_h_24(double *state, double *unused, double *out_7846417075360830243);
void car_H_24(double *state, double *unused, double *out_5500405455310713097);
void car_h_30(double *state, double *unused, double *out_4249003131890795043);
void car_H_30(double *state, double *unused, double *out_8255356060886090326);
void car_h_26(double *state, double *unused, double *out_4941641912900521878);
void car_H_26(double *state, double *unused, double *out_6579223641092645136);
void car_h_27(double *state, double *unused, double *out_8854285503439050117);
void car_H_27(double *state, double *unused, double *out_8016624701023036379);
void car_h_29(double *state, double *unused, double *out_6762597507390055760);
void car_H_29(double *state, double *unused, double *out_7745124716571698142);
void car_h_28(double *state, double *unused, double *out_4366551354435176552);
void car_H_28(double *state, double *unused, double *out_5619220340068322900);
void car_h_31(double *state, double *unused, double *out_4613520090508550250);
void car_H_31(double *state, double *unused, double *out_8095371151865889828);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}