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
void car_err_fun(double *nom_x, double *delta_x, double *out_8558166113930061773);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2269670274683655268);
void car_H_mod_fun(double *state, double *out_6407701768448647232);
void car_f_fun(double *state, double dt, double *out_648904423540471901);
void car_F_fun(double *state, double dt, double *out_7503564954401744509);
void car_h_25(double *state, double *unused, double *out_7864801379551668384);
void car_H_25(double *state, double *unused, double *out_7135350480076239544);
void car_h_24(double *state, double *unused, double *out_7538847613518647590);
void car_H_24(double *state, double *unused, double *out_3868719000644595752);
void car_h_30(double *state, double *unused, double *out_8021988047902797529);
void car_H_30(double *state, double *unused, double *out_6783697263505703874);
void car_h_26(double *state, double *unused, double *out_4978851268883674033);
void car_H_26(double *state, double *unused, double *out_7569890274759255848);
void car_h_27(double *state, double *unused, double *out_5096858662817050777);
void car_H_27(double *state, double *unused, double *out_9007291334689647091);
void car_h_29(double *state, double *unused, double *out_998555364537678913);
void car_H_29(double *state, double *unused, double *out_7293928607820096058);
void car_h_28(double *state, double *unused, double *out_8372706475564507366);
void car_H_28(double *state, double *unused, double *out_9189185194324129307);
void car_h_31(double *state, double *unused, double *out_180008667128300757);
void car_H_31(double *state, double *unused, double *out_6943682172525904372);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}