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
void car_err_fun(double *nom_x, double *delta_x, double *out_3955673683859984289);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8970258583381717138);
void car_H_mod_fun(double *state, double *out_4831252241531258142);
void car_f_fun(double *state, double dt, double *out_2508158103842919927);
void car_F_fun(double *state, double dt, double *out_619119889307979727);
void car_h_25(double *state, double *unused, double *out_7300303321148015441);
void car_H_25(double *state, double *unused, double *out_3882131319502775933);
void car_h_24(double *state, double *unused, double *out_7158441455227347179);
void car_H_24(double *state, double *unused, double *out_1656423535523907371);
void car_h_30(double *state, double *unused, double *out_7508991224307513825);
void car_H_30(double *state, double *unused, double *out_3034559021988840822);
void car_h_26(double *state, double *unused, double *out_5818543389571832865);
void car_H_26(double *state, double *unused, double *out_7623634638376832157);
void car_h_27(double *state, double *unused, double *out_4263517269703682756);
void car_H_27(double *state, double *unused, double *out_859795710188415911);
void car_h_29(double *state, double *unused, double *out_2507317956646668180);
void car_H_29(double *state, double *unused, double *out_3544790366303233006);
void car_h_28(double *state, double *unused, double *out_8661469350985311768);
void car_H_28(double *state, double *unused, double *out_1537608650766297568);
void car_h_31(double *state, double *unused, double *out_7025109258863509552);
void car_H_31(double *state, double *unused, double *out_3851485357625815505);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}