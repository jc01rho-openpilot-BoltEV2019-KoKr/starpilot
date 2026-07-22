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
void car_err_fun(double *nom_x, double *delta_x, double *out_8290791895352476901);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3328957974600116526);
void car_H_mod_fun(double *state, double *out_5003844791385944482);
void car_f_fun(double *state, double dt, double *out_2539953356409783064);
void car_F_fun(double *state, double dt, double *out_7655677773978689580);
void car_h_25(double *state, double *unused, double *out_1727643108219156348);
void car_H_25(double *state, double *unused, double *out_5770292553468151731);
void car_h_24(double *state, double *unused, double *out_4524050476975214784);
void car_H_24(double *state, double *unused, double *out_6475418840390238459);
void car_h_30(double *state, double *unused, double *out_90439028039008013);
void car_H_30(double *state, double *unused, double *out_8148755190113791687);
void car_h_26(double *state, double *unused, double *out_1938532702514813353);
void car_H_26(double *state, double *unused, double *out_8934948201367343661);
void car_h_27(double *state, double *unused, double *out_2553920733024504160);
void car_H_27(double *state, double *unused, double *out_8074394812411816712);
void car_h_29(double *state, double *unused, double *out_1033948880940670448);
void car_H_29(double *state, double *unused, double *out_8658986534428183871);
void car_h_28(double *state, double *unused, double *out_3913548264033873988);
void car_H_28(double *state, double *unused, double *out_3576587517358653297);
void car_h_31(double *state, double *unused, double *out_7253700544770179461);
void car_H_31(double *state, double *unused, double *out_5739646591591191303);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}