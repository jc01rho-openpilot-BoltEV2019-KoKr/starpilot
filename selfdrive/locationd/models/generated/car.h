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
void car_err_fun(double *nom_x, double *delta_x, double *out_5591921399563932369);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_806607420895539823);
void car_H_mod_fun(double *state, double *out_5676707820504431668);
void car_f_fun(double *state, double dt, double *out_4844917589263296834);
void car_F_fun(double *state, double dt, double *out_4636534629313466670);
void car_h_25(double *state, double *unused, double *out_5482647601852736049);
void car_H_25(double *state, double *unused, double *out_7866344428020455108);
void car_h_24(double *state, double *unused, double *out_6159121467458312716);
void car_H_24(double *state, double *unused, double *out_3137725052700380188);
void car_h_30(double *state, double *unused, double *out_5757841664137241938);
void car_H_30(double *state, double *unused, double *out_7995683375163695178);
void car_h_26(double *state, double *unused, double *out_6701351517038904373);
void car_H_26(double *state, double *unused, double *out_6838896326815040284);
void car_h_27(double *state, double *unused, double *out_7962423204195969922);
void car_H_27(double *state, double *unused, double *out_8276297386745431527);
void car_h_29(double *state, double *unused, double *out_2721055612692909253);
void car_H_29(double *state, double *unused, double *out_6562934659875880494);
void car_h_28(double *state, double *unused, double *out_8408093249132323059);
void car_H_28(double *state, double *unused, double *out_1480535642806349920);
void car_h_31(double *state, double *unused, double *out_4467435790593075575);
void car_H_31(double *state, double *unused, double *out_7835698466143494680);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}