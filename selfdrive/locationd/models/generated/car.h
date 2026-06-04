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
void car_err_fun(double *nom_x, double *delta_x, double *out_2057434223379957831);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4924816816161575884);
void car_H_mod_fun(double *state, double *out_8615316232539034437);
void car_f_fun(double *state, double dt, double *out_8159180570289535402);
void car_F_fun(double *state, double dt, double *out_8855850861951736689);
void car_h_25(double *state, double *unused, double *out_7057179500116168670);
void car_H_25(double *state, double *unused, double *out_8109981790338737725);
void car_h_24(double *state, double *unused, double *out_6854320894517861807);
void car_H_24(double *state, double *unused, double *out_8607899164193499822);
void car_h_30(double *state, double *unused, double *out_3929005809344494621);
void car_H_30(double *state, double *unused, double *out_1193291448847120970);
void car_h_26(double *state, double *unused, double *out_6807016989944022268);
void car_H_26(double *state, double *unused, double *out_6595258964496757667);
void car_h_27(double *state, double *unused, double *out_2055506232455323025);
void car_H_27(double *state, double *unused, double *out_3368054760647545881);
void car_h_29(double *state, double *unused, double *out_7581563669006346138);
void car_H_29(double *state, double *unused, double *out_683060104532728786);
void car_h_28(double *state, double *unused, double *out_7985581021610001938);
void car_H_28(double *state, double *unused, double *out_5765459121602259360);
void car_h_31(double *state, double *unused, double *out_706085756704503771);
void car_H_31(double *state, double *unused, double *out_8079335828461777297);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}