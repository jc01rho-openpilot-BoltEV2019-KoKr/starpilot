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
void car_err_fun(double *nom_x, double *delta_x, double *out_7084348270501559549);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_693097121251649199);
void car_H_mod_fun(double *state, double *out_1623843232183312219);
void car_f_fun(double *state, double dt, double *out_1622952619636770739);
void car_F_fun(double *state, double dt, double *out_7142842168519911469);
void car_h_25(double *state, double *unused, double *out_7699167154037203435);
void car_H_25(double *state, double *unused, double *out_1899137417806179458);
void car_h_24(double *state, double *unused, double *out_5775267180984789848);
void car_H_24(double *state, double *unused, double *out_273512181199320108);
void car_h_30(double *state, double *unused, double *out_940710322681338449);
void car_H_30(double *state, double *unused, double *out_8815827759297796213);
void car_h_26(double *state, double *unused, double *out_1922794416016636561);
void car_H_26(double *state, double *unused, double *out_1842365901067876766);
void car_h_27(double *state, double *unused, double *out_3098231746361013839);
void car_H_27(double *state, double *unused, double *out_6641064447497371302);
void car_h_29(double *state, double *unused, double *out_539217781893008511);
void car_H_29(double *state, double *unused, double *out_4927701720627820269);
void car_h_28(double *state, double *unused, double *out_822702928747961705);
void car_H_28(double *state, double *unused, double *out_154697296441710305);
void car_h_31(double *state, double *unused, double *out_6649273621392976317);
void car_H_31(double *state, double *unused, double *out_1929783379683139886);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}