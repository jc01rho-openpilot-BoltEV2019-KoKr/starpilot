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
void car_err_fun(double *nom_x, double *delta_x, double *out_9028291241411164041);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4666000221593499497);
void car_H_mod_fun(double *state, double *out_1234525725193622425);
void car_f_fun(double *state, double dt, double *out_5744399634248528082);
void car_F_fun(double *state, double dt, double *out_1994809722497824627);
void car_h_25(double *state, double *unused, double *out_4913819377999097610);
void car_H_25(double *state, double *unused, double *out_6138217550378287265);
void car_h_24(double *state, double *unused, double *out_7436088339947871774);
void car_H_24(double *state, double *unused, double *out_8315431973985437238);
void car_h_30(double *state, double *unused, double *out_7861545368354582571);
void car_H_30(double *state, double *unused, double *out_8656550508885535892);
void car_h_26(double *state, double *unused, double *out_4585697555607125982);
void car_H_26(double *state, double *unused, double *out_2396714231504231041);
void car_h_27(double *state, double *unused, double *out_7430405259977259616);
void car_H_27(double *state, double *unused, double *out_6481787197085110981);
void car_h_29(double *state, double *unused, double *out_3792955731723237266);
void car_H_29(double *state, double *unused, double *out_9166781853199928076);
void car_h_28(double *state, double *unused, double *out_7979552762287959315);
void car_H_28(double *state, double *unused, double *out_4084382836130397502);
void car_h_31(double *state, double *unused, double *out_494689836007543994);
void car_H_31(double *state, double *unused, double *out_1770506129270879565);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}