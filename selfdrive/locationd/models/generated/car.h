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
void car_err_fun(double *nom_x, double *delta_x, double *out_5399948258775111327);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_538771626761939485);
void car_H_mod_fun(double *state, double *out_6102609910614786292);
void car_f_fun(double *state, double dt, double *out_667706195184437986);
void car_F_fun(double *state, double dt, double *out_157487213156187863);
void car_h_25(double *state, double *unused, double *out_7616837909277052709);
void car_H_25(double *state, double *unused, double *out_8821153513105273647);
void car_h_24(double *state, double *unused, double *out_3643618505328510339);
void car_H_24(double *state, double *unused, double *out_5263227914302950511);
void car_h_30(double *state, double *unused, double *out_6577068605668785750);
void car_H_30(double *state, double *unused, double *out_8950492460248513717);
void car_h_26(double *state, double *unused, double *out_5973752720992308233);
void car_H_26(double *state, double *unused, double *out_5884087241730221745);
void car_h_27(double *state, double *unused, double *out_8560347762178715144);
void car_H_27(double *state, double *unused, double *out_7321488301660612988);
void car_h_29(double *state, double *unused, double *out_1246518834812294588);
void car_H_29(double *state, double *unused, double *out_5608125574791061955);
void car_h_28(double *state, double *unused, double *out_7957031877502237627);
void car_H_28(double *state, double *unused, double *out_7571755846356388206);
void car_h_31(double *state, double *unused, double *out_7192456636178476557);
void car_H_31(double *state, double *unused, double *out_8790507551228313219);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}