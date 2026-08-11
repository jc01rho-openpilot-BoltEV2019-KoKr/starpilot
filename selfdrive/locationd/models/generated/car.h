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
void car_err_fun(double *nom_x, double *delta_x, double *out_3114295045279175255);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_2774429114405664516);
void car_H_mod_fun(double *state, double *out_6080875852390524285);
void car_f_fun(double *state, double dt, double *out_6417706388998195307);
void car_F_fun(double *state, double dt, double *out_883841085229346789);
void car_h_25(double *state, double *unused, double *out_2855412773557287240);
void car_H_25(double *state, double *unused, double *out_2557895202401032608);
void car_h_24(double *state, double *unused, double *out_8685899773420353243);
void car_H_24(double *state, double *unused, double *out_1000030396401290528);
void car_h_30(double *state, double *unused, double *out_3732415152919007923);
void car_H_30(double *state, double *unused, double *out_4358795139090584147);
void car_h_26(double *state, double *unused, double *out_665536928362621089);
void car_H_26(double *state, double *unused, double *out_6299398521275088832);
void car_h_27(double *state, double *unused, double *out_3247106662175907150);
void car_H_27(double *state, double *unused, double *out_2184031827290159236);
void car_h_29(double *state, double *unused, double *out_9044190215692984337);
void car_H_29(double *state, double *unused, double *out_470669100420608203);
void car_h_28(double *state, double *unused, double *out_8248779929836752795);
void car_H_28(double *state, double *unused, double *out_4611729916648922371);
void car_h_31(double *state, double *unused, double *out_6008698651335733946);
void car_H_31(double *state, double *unused, double *out_2527249240524072180);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}