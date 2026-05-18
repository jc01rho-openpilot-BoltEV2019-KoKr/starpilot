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
void car_err_fun(double *nom_x, double *delta_x, double *out_587611173581676283);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8120728011522269919);
void car_H_mod_fun(double *state, double *out_4001675034436284807);
void car_f_fun(double *state, double dt, double *out_6995360374056238489);
void car_F_fun(double *state, double dt, double *out_5620828310005666299);
void car_h_25(double *state, double *unused, double *out_5932710635121359621);
void car_H_25(double *state, double *unused, double *out_4507009476636581519);
void car_h_24(double *state, double *unused, double *out_8960081603047522700);
void car_H_24(double *state, double *unused, double *out_7364162790481451996);
void car_h_30(double *state, double *unused, double *out_6293656255741178026);
void car_H_30(double *state, double *unused, double *out_7023044255581353342);
void car_h_26(double *state, double *unused, double *out_7151414550307527945);
void car_H_26(double *state, double *unused, double *out_765506157762525295);
void car_h_27(double *state, double *unused, double *out_7512360170927346350);
void car_H_27(double *state, double *unused, double *out_9197807567381778253);
void car_h_29(double *state, double *unused, double *out_3171118645961532825);
void car_H_29(double *state, double *unused, double *out_6512812911266961158);
void car_h_28(double *state, double *unused, double *out_8329978581973507615);
void car_H_28(double *state, double *unused, double *out_2453174762388691756);
void car_h_31(double *state, double *unused, double *out_222736560719300508);
void car_H_31(double *state, double *unused, double *out_4537655438513541947);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}