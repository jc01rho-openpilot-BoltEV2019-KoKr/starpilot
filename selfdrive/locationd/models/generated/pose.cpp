#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_5518524982420716050) {
   out_5518524982420716050[0] = delta_x[0] + nom_x[0];
   out_5518524982420716050[1] = delta_x[1] + nom_x[1];
   out_5518524982420716050[2] = delta_x[2] + nom_x[2];
   out_5518524982420716050[3] = delta_x[3] + nom_x[3];
   out_5518524982420716050[4] = delta_x[4] + nom_x[4];
   out_5518524982420716050[5] = delta_x[5] + nom_x[5];
   out_5518524982420716050[6] = delta_x[6] + nom_x[6];
   out_5518524982420716050[7] = delta_x[7] + nom_x[7];
   out_5518524982420716050[8] = delta_x[8] + nom_x[8];
   out_5518524982420716050[9] = delta_x[9] + nom_x[9];
   out_5518524982420716050[10] = delta_x[10] + nom_x[10];
   out_5518524982420716050[11] = delta_x[11] + nom_x[11];
   out_5518524982420716050[12] = delta_x[12] + nom_x[12];
   out_5518524982420716050[13] = delta_x[13] + nom_x[13];
   out_5518524982420716050[14] = delta_x[14] + nom_x[14];
   out_5518524982420716050[15] = delta_x[15] + nom_x[15];
   out_5518524982420716050[16] = delta_x[16] + nom_x[16];
   out_5518524982420716050[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4331401110135306651) {
   out_4331401110135306651[0] = -nom_x[0] + true_x[0];
   out_4331401110135306651[1] = -nom_x[1] + true_x[1];
   out_4331401110135306651[2] = -nom_x[2] + true_x[2];
   out_4331401110135306651[3] = -nom_x[3] + true_x[3];
   out_4331401110135306651[4] = -nom_x[4] + true_x[4];
   out_4331401110135306651[5] = -nom_x[5] + true_x[5];
   out_4331401110135306651[6] = -nom_x[6] + true_x[6];
   out_4331401110135306651[7] = -nom_x[7] + true_x[7];
   out_4331401110135306651[8] = -nom_x[8] + true_x[8];
   out_4331401110135306651[9] = -nom_x[9] + true_x[9];
   out_4331401110135306651[10] = -nom_x[10] + true_x[10];
   out_4331401110135306651[11] = -nom_x[11] + true_x[11];
   out_4331401110135306651[12] = -nom_x[12] + true_x[12];
   out_4331401110135306651[13] = -nom_x[13] + true_x[13];
   out_4331401110135306651[14] = -nom_x[14] + true_x[14];
   out_4331401110135306651[15] = -nom_x[15] + true_x[15];
   out_4331401110135306651[16] = -nom_x[16] + true_x[16];
   out_4331401110135306651[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3835336694818914681) {
   out_3835336694818914681[0] = 1.0;
   out_3835336694818914681[1] = 0.0;
   out_3835336694818914681[2] = 0.0;
   out_3835336694818914681[3] = 0.0;
   out_3835336694818914681[4] = 0.0;
   out_3835336694818914681[5] = 0.0;
   out_3835336694818914681[6] = 0.0;
   out_3835336694818914681[7] = 0.0;
   out_3835336694818914681[8] = 0.0;
   out_3835336694818914681[9] = 0.0;
   out_3835336694818914681[10] = 0.0;
   out_3835336694818914681[11] = 0.0;
   out_3835336694818914681[12] = 0.0;
   out_3835336694818914681[13] = 0.0;
   out_3835336694818914681[14] = 0.0;
   out_3835336694818914681[15] = 0.0;
   out_3835336694818914681[16] = 0.0;
   out_3835336694818914681[17] = 0.0;
   out_3835336694818914681[18] = 0.0;
   out_3835336694818914681[19] = 1.0;
   out_3835336694818914681[20] = 0.0;
   out_3835336694818914681[21] = 0.0;
   out_3835336694818914681[22] = 0.0;
   out_3835336694818914681[23] = 0.0;
   out_3835336694818914681[24] = 0.0;
   out_3835336694818914681[25] = 0.0;
   out_3835336694818914681[26] = 0.0;
   out_3835336694818914681[27] = 0.0;
   out_3835336694818914681[28] = 0.0;
   out_3835336694818914681[29] = 0.0;
   out_3835336694818914681[30] = 0.0;
   out_3835336694818914681[31] = 0.0;
   out_3835336694818914681[32] = 0.0;
   out_3835336694818914681[33] = 0.0;
   out_3835336694818914681[34] = 0.0;
   out_3835336694818914681[35] = 0.0;
   out_3835336694818914681[36] = 0.0;
   out_3835336694818914681[37] = 0.0;
   out_3835336694818914681[38] = 1.0;
   out_3835336694818914681[39] = 0.0;
   out_3835336694818914681[40] = 0.0;
   out_3835336694818914681[41] = 0.0;
   out_3835336694818914681[42] = 0.0;
   out_3835336694818914681[43] = 0.0;
   out_3835336694818914681[44] = 0.0;
   out_3835336694818914681[45] = 0.0;
   out_3835336694818914681[46] = 0.0;
   out_3835336694818914681[47] = 0.0;
   out_3835336694818914681[48] = 0.0;
   out_3835336694818914681[49] = 0.0;
   out_3835336694818914681[50] = 0.0;
   out_3835336694818914681[51] = 0.0;
   out_3835336694818914681[52] = 0.0;
   out_3835336694818914681[53] = 0.0;
   out_3835336694818914681[54] = 0.0;
   out_3835336694818914681[55] = 0.0;
   out_3835336694818914681[56] = 0.0;
   out_3835336694818914681[57] = 1.0;
   out_3835336694818914681[58] = 0.0;
   out_3835336694818914681[59] = 0.0;
   out_3835336694818914681[60] = 0.0;
   out_3835336694818914681[61] = 0.0;
   out_3835336694818914681[62] = 0.0;
   out_3835336694818914681[63] = 0.0;
   out_3835336694818914681[64] = 0.0;
   out_3835336694818914681[65] = 0.0;
   out_3835336694818914681[66] = 0.0;
   out_3835336694818914681[67] = 0.0;
   out_3835336694818914681[68] = 0.0;
   out_3835336694818914681[69] = 0.0;
   out_3835336694818914681[70] = 0.0;
   out_3835336694818914681[71] = 0.0;
   out_3835336694818914681[72] = 0.0;
   out_3835336694818914681[73] = 0.0;
   out_3835336694818914681[74] = 0.0;
   out_3835336694818914681[75] = 0.0;
   out_3835336694818914681[76] = 1.0;
   out_3835336694818914681[77] = 0.0;
   out_3835336694818914681[78] = 0.0;
   out_3835336694818914681[79] = 0.0;
   out_3835336694818914681[80] = 0.0;
   out_3835336694818914681[81] = 0.0;
   out_3835336694818914681[82] = 0.0;
   out_3835336694818914681[83] = 0.0;
   out_3835336694818914681[84] = 0.0;
   out_3835336694818914681[85] = 0.0;
   out_3835336694818914681[86] = 0.0;
   out_3835336694818914681[87] = 0.0;
   out_3835336694818914681[88] = 0.0;
   out_3835336694818914681[89] = 0.0;
   out_3835336694818914681[90] = 0.0;
   out_3835336694818914681[91] = 0.0;
   out_3835336694818914681[92] = 0.0;
   out_3835336694818914681[93] = 0.0;
   out_3835336694818914681[94] = 0.0;
   out_3835336694818914681[95] = 1.0;
   out_3835336694818914681[96] = 0.0;
   out_3835336694818914681[97] = 0.0;
   out_3835336694818914681[98] = 0.0;
   out_3835336694818914681[99] = 0.0;
   out_3835336694818914681[100] = 0.0;
   out_3835336694818914681[101] = 0.0;
   out_3835336694818914681[102] = 0.0;
   out_3835336694818914681[103] = 0.0;
   out_3835336694818914681[104] = 0.0;
   out_3835336694818914681[105] = 0.0;
   out_3835336694818914681[106] = 0.0;
   out_3835336694818914681[107] = 0.0;
   out_3835336694818914681[108] = 0.0;
   out_3835336694818914681[109] = 0.0;
   out_3835336694818914681[110] = 0.0;
   out_3835336694818914681[111] = 0.0;
   out_3835336694818914681[112] = 0.0;
   out_3835336694818914681[113] = 0.0;
   out_3835336694818914681[114] = 1.0;
   out_3835336694818914681[115] = 0.0;
   out_3835336694818914681[116] = 0.0;
   out_3835336694818914681[117] = 0.0;
   out_3835336694818914681[118] = 0.0;
   out_3835336694818914681[119] = 0.0;
   out_3835336694818914681[120] = 0.0;
   out_3835336694818914681[121] = 0.0;
   out_3835336694818914681[122] = 0.0;
   out_3835336694818914681[123] = 0.0;
   out_3835336694818914681[124] = 0.0;
   out_3835336694818914681[125] = 0.0;
   out_3835336694818914681[126] = 0.0;
   out_3835336694818914681[127] = 0.0;
   out_3835336694818914681[128] = 0.0;
   out_3835336694818914681[129] = 0.0;
   out_3835336694818914681[130] = 0.0;
   out_3835336694818914681[131] = 0.0;
   out_3835336694818914681[132] = 0.0;
   out_3835336694818914681[133] = 1.0;
   out_3835336694818914681[134] = 0.0;
   out_3835336694818914681[135] = 0.0;
   out_3835336694818914681[136] = 0.0;
   out_3835336694818914681[137] = 0.0;
   out_3835336694818914681[138] = 0.0;
   out_3835336694818914681[139] = 0.0;
   out_3835336694818914681[140] = 0.0;
   out_3835336694818914681[141] = 0.0;
   out_3835336694818914681[142] = 0.0;
   out_3835336694818914681[143] = 0.0;
   out_3835336694818914681[144] = 0.0;
   out_3835336694818914681[145] = 0.0;
   out_3835336694818914681[146] = 0.0;
   out_3835336694818914681[147] = 0.0;
   out_3835336694818914681[148] = 0.0;
   out_3835336694818914681[149] = 0.0;
   out_3835336694818914681[150] = 0.0;
   out_3835336694818914681[151] = 0.0;
   out_3835336694818914681[152] = 1.0;
   out_3835336694818914681[153] = 0.0;
   out_3835336694818914681[154] = 0.0;
   out_3835336694818914681[155] = 0.0;
   out_3835336694818914681[156] = 0.0;
   out_3835336694818914681[157] = 0.0;
   out_3835336694818914681[158] = 0.0;
   out_3835336694818914681[159] = 0.0;
   out_3835336694818914681[160] = 0.0;
   out_3835336694818914681[161] = 0.0;
   out_3835336694818914681[162] = 0.0;
   out_3835336694818914681[163] = 0.0;
   out_3835336694818914681[164] = 0.0;
   out_3835336694818914681[165] = 0.0;
   out_3835336694818914681[166] = 0.0;
   out_3835336694818914681[167] = 0.0;
   out_3835336694818914681[168] = 0.0;
   out_3835336694818914681[169] = 0.0;
   out_3835336694818914681[170] = 0.0;
   out_3835336694818914681[171] = 1.0;
   out_3835336694818914681[172] = 0.0;
   out_3835336694818914681[173] = 0.0;
   out_3835336694818914681[174] = 0.0;
   out_3835336694818914681[175] = 0.0;
   out_3835336694818914681[176] = 0.0;
   out_3835336694818914681[177] = 0.0;
   out_3835336694818914681[178] = 0.0;
   out_3835336694818914681[179] = 0.0;
   out_3835336694818914681[180] = 0.0;
   out_3835336694818914681[181] = 0.0;
   out_3835336694818914681[182] = 0.0;
   out_3835336694818914681[183] = 0.0;
   out_3835336694818914681[184] = 0.0;
   out_3835336694818914681[185] = 0.0;
   out_3835336694818914681[186] = 0.0;
   out_3835336694818914681[187] = 0.0;
   out_3835336694818914681[188] = 0.0;
   out_3835336694818914681[189] = 0.0;
   out_3835336694818914681[190] = 1.0;
   out_3835336694818914681[191] = 0.0;
   out_3835336694818914681[192] = 0.0;
   out_3835336694818914681[193] = 0.0;
   out_3835336694818914681[194] = 0.0;
   out_3835336694818914681[195] = 0.0;
   out_3835336694818914681[196] = 0.0;
   out_3835336694818914681[197] = 0.0;
   out_3835336694818914681[198] = 0.0;
   out_3835336694818914681[199] = 0.0;
   out_3835336694818914681[200] = 0.0;
   out_3835336694818914681[201] = 0.0;
   out_3835336694818914681[202] = 0.0;
   out_3835336694818914681[203] = 0.0;
   out_3835336694818914681[204] = 0.0;
   out_3835336694818914681[205] = 0.0;
   out_3835336694818914681[206] = 0.0;
   out_3835336694818914681[207] = 0.0;
   out_3835336694818914681[208] = 0.0;
   out_3835336694818914681[209] = 1.0;
   out_3835336694818914681[210] = 0.0;
   out_3835336694818914681[211] = 0.0;
   out_3835336694818914681[212] = 0.0;
   out_3835336694818914681[213] = 0.0;
   out_3835336694818914681[214] = 0.0;
   out_3835336694818914681[215] = 0.0;
   out_3835336694818914681[216] = 0.0;
   out_3835336694818914681[217] = 0.0;
   out_3835336694818914681[218] = 0.0;
   out_3835336694818914681[219] = 0.0;
   out_3835336694818914681[220] = 0.0;
   out_3835336694818914681[221] = 0.0;
   out_3835336694818914681[222] = 0.0;
   out_3835336694818914681[223] = 0.0;
   out_3835336694818914681[224] = 0.0;
   out_3835336694818914681[225] = 0.0;
   out_3835336694818914681[226] = 0.0;
   out_3835336694818914681[227] = 0.0;
   out_3835336694818914681[228] = 1.0;
   out_3835336694818914681[229] = 0.0;
   out_3835336694818914681[230] = 0.0;
   out_3835336694818914681[231] = 0.0;
   out_3835336694818914681[232] = 0.0;
   out_3835336694818914681[233] = 0.0;
   out_3835336694818914681[234] = 0.0;
   out_3835336694818914681[235] = 0.0;
   out_3835336694818914681[236] = 0.0;
   out_3835336694818914681[237] = 0.0;
   out_3835336694818914681[238] = 0.0;
   out_3835336694818914681[239] = 0.0;
   out_3835336694818914681[240] = 0.0;
   out_3835336694818914681[241] = 0.0;
   out_3835336694818914681[242] = 0.0;
   out_3835336694818914681[243] = 0.0;
   out_3835336694818914681[244] = 0.0;
   out_3835336694818914681[245] = 0.0;
   out_3835336694818914681[246] = 0.0;
   out_3835336694818914681[247] = 1.0;
   out_3835336694818914681[248] = 0.0;
   out_3835336694818914681[249] = 0.0;
   out_3835336694818914681[250] = 0.0;
   out_3835336694818914681[251] = 0.0;
   out_3835336694818914681[252] = 0.0;
   out_3835336694818914681[253] = 0.0;
   out_3835336694818914681[254] = 0.0;
   out_3835336694818914681[255] = 0.0;
   out_3835336694818914681[256] = 0.0;
   out_3835336694818914681[257] = 0.0;
   out_3835336694818914681[258] = 0.0;
   out_3835336694818914681[259] = 0.0;
   out_3835336694818914681[260] = 0.0;
   out_3835336694818914681[261] = 0.0;
   out_3835336694818914681[262] = 0.0;
   out_3835336694818914681[263] = 0.0;
   out_3835336694818914681[264] = 0.0;
   out_3835336694818914681[265] = 0.0;
   out_3835336694818914681[266] = 1.0;
   out_3835336694818914681[267] = 0.0;
   out_3835336694818914681[268] = 0.0;
   out_3835336694818914681[269] = 0.0;
   out_3835336694818914681[270] = 0.0;
   out_3835336694818914681[271] = 0.0;
   out_3835336694818914681[272] = 0.0;
   out_3835336694818914681[273] = 0.0;
   out_3835336694818914681[274] = 0.0;
   out_3835336694818914681[275] = 0.0;
   out_3835336694818914681[276] = 0.0;
   out_3835336694818914681[277] = 0.0;
   out_3835336694818914681[278] = 0.0;
   out_3835336694818914681[279] = 0.0;
   out_3835336694818914681[280] = 0.0;
   out_3835336694818914681[281] = 0.0;
   out_3835336694818914681[282] = 0.0;
   out_3835336694818914681[283] = 0.0;
   out_3835336694818914681[284] = 0.0;
   out_3835336694818914681[285] = 1.0;
   out_3835336694818914681[286] = 0.0;
   out_3835336694818914681[287] = 0.0;
   out_3835336694818914681[288] = 0.0;
   out_3835336694818914681[289] = 0.0;
   out_3835336694818914681[290] = 0.0;
   out_3835336694818914681[291] = 0.0;
   out_3835336694818914681[292] = 0.0;
   out_3835336694818914681[293] = 0.0;
   out_3835336694818914681[294] = 0.0;
   out_3835336694818914681[295] = 0.0;
   out_3835336694818914681[296] = 0.0;
   out_3835336694818914681[297] = 0.0;
   out_3835336694818914681[298] = 0.0;
   out_3835336694818914681[299] = 0.0;
   out_3835336694818914681[300] = 0.0;
   out_3835336694818914681[301] = 0.0;
   out_3835336694818914681[302] = 0.0;
   out_3835336694818914681[303] = 0.0;
   out_3835336694818914681[304] = 1.0;
   out_3835336694818914681[305] = 0.0;
   out_3835336694818914681[306] = 0.0;
   out_3835336694818914681[307] = 0.0;
   out_3835336694818914681[308] = 0.0;
   out_3835336694818914681[309] = 0.0;
   out_3835336694818914681[310] = 0.0;
   out_3835336694818914681[311] = 0.0;
   out_3835336694818914681[312] = 0.0;
   out_3835336694818914681[313] = 0.0;
   out_3835336694818914681[314] = 0.0;
   out_3835336694818914681[315] = 0.0;
   out_3835336694818914681[316] = 0.0;
   out_3835336694818914681[317] = 0.0;
   out_3835336694818914681[318] = 0.0;
   out_3835336694818914681[319] = 0.0;
   out_3835336694818914681[320] = 0.0;
   out_3835336694818914681[321] = 0.0;
   out_3835336694818914681[322] = 0.0;
   out_3835336694818914681[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4487166249411202898) {
   out_4487166249411202898[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4487166249411202898[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4487166249411202898[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4487166249411202898[3] = dt*state[12] + state[3];
   out_4487166249411202898[4] = dt*state[13] + state[4];
   out_4487166249411202898[5] = dt*state[14] + state[5];
   out_4487166249411202898[6] = state[6];
   out_4487166249411202898[7] = state[7];
   out_4487166249411202898[8] = state[8];
   out_4487166249411202898[9] = state[9];
   out_4487166249411202898[10] = state[10];
   out_4487166249411202898[11] = state[11];
   out_4487166249411202898[12] = state[12];
   out_4487166249411202898[13] = state[13];
   out_4487166249411202898[14] = state[14];
   out_4487166249411202898[15] = state[15];
   out_4487166249411202898[16] = state[16];
   out_4487166249411202898[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5041909296412759665) {
   out_5041909296412759665[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5041909296412759665[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5041909296412759665[2] = 0;
   out_5041909296412759665[3] = 0;
   out_5041909296412759665[4] = 0;
   out_5041909296412759665[5] = 0;
   out_5041909296412759665[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5041909296412759665[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5041909296412759665[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5041909296412759665[9] = 0;
   out_5041909296412759665[10] = 0;
   out_5041909296412759665[11] = 0;
   out_5041909296412759665[12] = 0;
   out_5041909296412759665[13] = 0;
   out_5041909296412759665[14] = 0;
   out_5041909296412759665[15] = 0;
   out_5041909296412759665[16] = 0;
   out_5041909296412759665[17] = 0;
   out_5041909296412759665[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5041909296412759665[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5041909296412759665[20] = 0;
   out_5041909296412759665[21] = 0;
   out_5041909296412759665[22] = 0;
   out_5041909296412759665[23] = 0;
   out_5041909296412759665[24] = 0;
   out_5041909296412759665[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5041909296412759665[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5041909296412759665[27] = 0;
   out_5041909296412759665[28] = 0;
   out_5041909296412759665[29] = 0;
   out_5041909296412759665[30] = 0;
   out_5041909296412759665[31] = 0;
   out_5041909296412759665[32] = 0;
   out_5041909296412759665[33] = 0;
   out_5041909296412759665[34] = 0;
   out_5041909296412759665[35] = 0;
   out_5041909296412759665[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5041909296412759665[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5041909296412759665[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5041909296412759665[39] = 0;
   out_5041909296412759665[40] = 0;
   out_5041909296412759665[41] = 0;
   out_5041909296412759665[42] = 0;
   out_5041909296412759665[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5041909296412759665[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5041909296412759665[45] = 0;
   out_5041909296412759665[46] = 0;
   out_5041909296412759665[47] = 0;
   out_5041909296412759665[48] = 0;
   out_5041909296412759665[49] = 0;
   out_5041909296412759665[50] = 0;
   out_5041909296412759665[51] = 0;
   out_5041909296412759665[52] = 0;
   out_5041909296412759665[53] = 0;
   out_5041909296412759665[54] = 0;
   out_5041909296412759665[55] = 0;
   out_5041909296412759665[56] = 0;
   out_5041909296412759665[57] = 1;
   out_5041909296412759665[58] = 0;
   out_5041909296412759665[59] = 0;
   out_5041909296412759665[60] = 0;
   out_5041909296412759665[61] = 0;
   out_5041909296412759665[62] = 0;
   out_5041909296412759665[63] = 0;
   out_5041909296412759665[64] = 0;
   out_5041909296412759665[65] = 0;
   out_5041909296412759665[66] = dt;
   out_5041909296412759665[67] = 0;
   out_5041909296412759665[68] = 0;
   out_5041909296412759665[69] = 0;
   out_5041909296412759665[70] = 0;
   out_5041909296412759665[71] = 0;
   out_5041909296412759665[72] = 0;
   out_5041909296412759665[73] = 0;
   out_5041909296412759665[74] = 0;
   out_5041909296412759665[75] = 0;
   out_5041909296412759665[76] = 1;
   out_5041909296412759665[77] = 0;
   out_5041909296412759665[78] = 0;
   out_5041909296412759665[79] = 0;
   out_5041909296412759665[80] = 0;
   out_5041909296412759665[81] = 0;
   out_5041909296412759665[82] = 0;
   out_5041909296412759665[83] = 0;
   out_5041909296412759665[84] = 0;
   out_5041909296412759665[85] = dt;
   out_5041909296412759665[86] = 0;
   out_5041909296412759665[87] = 0;
   out_5041909296412759665[88] = 0;
   out_5041909296412759665[89] = 0;
   out_5041909296412759665[90] = 0;
   out_5041909296412759665[91] = 0;
   out_5041909296412759665[92] = 0;
   out_5041909296412759665[93] = 0;
   out_5041909296412759665[94] = 0;
   out_5041909296412759665[95] = 1;
   out_5041909296412759665[96] = 0;
   out_5041909296412759665[97] = 0;
   out_5041909296412759665[98] = 0;
   out_5041909296412759665[99] = 0;
   out_5041909296412759665[100] = 0;
   out_5041909296412759665[101] = 0;
   out_5041909296412759665[102] = 0;
   out_5041909296412759665[103] = 0;
   out_5041909296412759665[104] = dt;
   out_5041909296412759665[105] = 0;
   out_5041909296412759665[106] = 0;
   out_5041909296412759665[107] = 0;
   out_5041909296412759665[108] = 0;
   out_5041909296412759665[109] = 0;
   out_5041909296412759665[110] = 0;
   out_5041909296412759665[111] = 0;
   out_5041909296412759665[112] = 0;
   out_5041909296412759665[113] = 0;
   out_5041909296412759665[114] = 1;
   out_5041909296412759665[115] = 0;
   out_5041909296412759665[116] = 0;
   out_5041909296412759665[117] = 0;
   out_5041909296412759665[118] = 0;
   out_5041909296412759665[119] = 0;
   out_5041909296412759665[120] = 0;
   out_5041909296412759665[121] = 0;
   out_5041909296412759665[122] = 0;
   out_5041909296412759665[123] = 0;
   out_5041909296412759665[124] = 0;
   out_5041909296412759665[125] = 0;
   out_5041909296412759665[126] = 0;
   out_5041909296412759665[127] = 0;
   out_5041909296412759665[128] = 0;
   out_5041909296412759665[129] = 0;
   out_5041909296412759665[130] = 0;
   out_5041909296412759665[131] = 0;
   out_5041909296412759665[132] = 0;
   out_5041909296412759665[133] = 1;
   out_5041909296412759665[134] = 0;
   out_5041909296412759665[135] = 0;
   out_5041909296412759665[136] = 0;
   out_5041909296412759665[137] = 0;
   out_5041909296412759665[138] = 0;
   out_5041909296412759665[139] = 0;
   out_5041909296412759665[140] = 0;
   out_5041909296412759665[141] = 0;
   out_5041909296412759665[142] = 0;
   out_5041909296412759665[143] = 0;
   out_5041909296412759665[144] = 0;
   out_5041909296412759665[145] = 0;
   out_5041909296412759665[146] = 0;
   out_5041909296412759665[147] = 0;
   out_5041909296412759665[148] = 0;
   out_5041909296412759665[149] = 0;
   out_5041909296412759665[150] = 0;
   out_5041909296412759665[151] = 0;
   out_5041909296412759665[152] = 1;
   out_5041909296412759665[153] = 0;
   out_5041909296412759665[154] = 0;
   out_5041909296412759665[155] = 0;
   out_5041909296412759665[156] = 0;
   out_5041909296412759665[157] = 0;
   out_5041909296412759665[158] = 0;
   out_5041909296412759665[159] = 0;
   out_5041909296412759665[160] = 0;
   out_5041909296412759665[161] = 0;
   out_5041909296412759665[162] = 0;
   out_5041909296412759665[163] = 0;
   out_5041909296412759665[164] = 0;
   out_5041909296412759665[165] = 0;
   out_5041909296412759665[166] = 0;
   out_5041909296412759665[167] = 0;
   out_5041909296412759665[168] = 0;
   out_5041909296412759665[169] = 0;
   out_5041909296412759665[170] = 0;
   out_5041909296412759665[171] = 1;
   out_5041909296412759665[172] = 0;
   out_5041909296412759665[173] = 0;
   out_5041909296412759665[174] = 0;
   out_5041909296412759665[175] = 0;
   out_5041909296412759665[176] = 0;
   out_5041909296412759665[177] = 0;
   out_5041909296412759665[178] = 0;
   out_5041909296412759665[179] = 0;
   out_5041909296412759665[180] = 0;
   out_5041909296412759665[181] = 0;
   out_5041909296412759665[182] = 0;
   out_5041909296412759665[183] = 0;
   out_5041909296412759665[184] = 0;
   out_5041909296412759665[185] = 0;
   out_5041909296412759665[186] = 0;
   out_5041909296412759665[187] = 0;
   out_5041909296412759665[188] = 0;
   out_5041909296412759665[189] = 0;
   out_5041909296412759665[190] = 1;
   out_5041909296412759665[191] = 0;
   out_5041909296412759665[192] = 0;
   out_5041909296412759665[193] = 0;
   out_5041909296412759665[194] = 0;
   out_5041909296412759665[195] = 0;
   out_5041909296412759665[196] = 0;
   out_5041909296412759665[197] = 0;
   out_5041909296412759665[198] = 0;
   out_5041909296412759665[199] = 0;
   out_5041909296412759665[200] = 0;
   out_5041909296412759665[201] = 0;
   out_5041909296412759665[202] = 0;
   out_5041909296412759665[203] = 0;
   out_5041909296412759665[204] = 0;
   out_5041909296412759665[205] = 0;
   out_5041909296412759665[206] = 0;
   out_5041909296412759665[207] = 0;
   out_5041909296412759665[208] = 0;
   out_5041909296412759665[209] = 1;
   out_5041909296412759665[210] = 0;
   out_5041909296412759665[211] = 0;
   out_5041909296412759665[212] = 0;
   out_5041909296412759665[213] = 0;
   out_5041909296412759665[214] = 0;
   out_5041909296412759665[215] = 0;
   out_5041909296412759665[216] = 0;
   out_5041909296412759665[217] = 0;
   out_5041909296412759665[218] = 0;
   out_5041909296412759665[219] = 0;
   out_5041909296412759665[220] = 0;
   out_5041909296412759665[221] = 0;
   out_5041909296412759665[222] = 0;
   out_5041909296412759665[223] = 0;
   out_5041909296412759665[224] = 0;
   out_5041909296412759665[225] = 0;
   out_5041909296412759665[226] = 0;
   out_5041909296412759665[227] = 0;
   out_5041909296412759665[228] = 1;
   out_5041909296412759665[229] = 0;
   out_5041909296412759665[230] = 0;
   out_5041909296412759665[231] = 0;
   out_5041909296412759665[232] = 0;
   out_5041909296412759665[233] = 0;
   out_5041909296412759665[234] = 0;
   out_5041909296412759665[235] = 0;
   out_5041909296412759665[236] = 0;
   out_5041909296412759665[237] = 0;
   out_5041909296412759665[238] = 0;
   out_5041909296412759665[239] = 0;
   out_5041909296412759665[240] = 0;
   out_5041909296412759665[241] = 0;
   out_5041909296412759665[242] = 0;
   out_5041909296412759665[243] = 0;
   out_5041909296412759665[244] = 0;
   out_5041909296412759665[245] = 0;
   out_5041909296412759665[246] = 0;
   out_5041909296412759665[247] = 1;
   out_5041909296412759665[248] = 0;
   out_5041909296412759665[249] = 0;
   out_5041909296412759665[250] = 0;
   out_5041909296412759665[251] = 0;
   out_5041909296412759665[252] = 0;
   out_5041909296412759665[253] = 0;
   out_5041909296412759665[254] = 0;
   out_5041909296412759665[255] = 0;
   out_5041909296412759665[256] = 0;
   out_5041909296412759665[257] = 0;
   out_5041909296412759665[258] = 0;
   out_5041909296412759665[259] = 0;
   out_5041909296412759665[260] = 0;
   out_5041909296412759665[261] = 0;
   out_5041909296412759665[262] = 0;
   out_5041909296412759665[263] = 0;
   out_5041909296412759665[264] = 0;
   out_5041909296412759665[265] = 0;
   out_5041909296412759665[266] = 1;
   out_5041909296412759665[267] = 0;
   out_5041909296412759665[268] = 0;
   out_5041909296412759665[269] = 0;
   out_5041909296412759665[270] = 0;
   out_5041909296412759665[271] = 0;
   out_5041909296412759665[272] = 0;
   out_5041909296412759665[273] = 0;
   out_5041909296412759665[274] = 0;
   out_5041909296412759665[275] = 0;
   out_5041909296412759665[276] = 0;
   out_5041909296412759665[277] = 0;
   out_5041909296412759665[278] = 0;
   out_5041909296412759665[279] = 0;
   out_5041909296412759665[280] = 0;
   out_5041909296412759665[281] = 0;
   out_5041909296412759665[282] = 0;
   out_5041909296412759665[283] = 0;
   out_5041909296412759665[284] = 0;
   out_5041909296412759665[285] = 1;
   out_5041909296412759665[286] = 0;
   out_5041909296412759665[287] = 0;
   out_5041909296412759665[288] = 0;
   out_5041909296412759665[289] = 0;
   out_5041909296412759665[290] = 0;
   out_5041909296412759665[291] = 0;
   out_5041909296412759665[292] = 0;
   out_5041909296412759665[293] = 0;
   out_5041909296412759665[294] = 0;
   out_5041909296412759665[295] = 0;
   out_5041909296412759665[296] = 0;
   out_5041909296412759665[297] = 0;
   out_5041909296412759665[298] = 0;
   out_5041909296412759665[299] = 0;
   out_5041909296412759665[300] = 0;
   out_5041909296412759665[301] = 0;
   out_5041909296412759665[302] = 0;
   out_5041909296412759665[303] = 0;
   out_5041909296412759665[304] = 1;
   out_5041909296412759665[305] = 0;
   out_5041909296412759665[306] = 0;
   out_5041909296412759665[307] = 0;
   out_5041909296412759665[308] = 0;
   out_5041909296412759665[309] = 0;
   out_5041909296412759665[310] = 0;
   out_5041909296412759665[311] = 0;
   out_5041909296412759665[312] = 0;
   out_5041909296412759665[313] = 0;
   out_5041909296412759665[314] = 0;
   out_5041909296412759665[315] = 0;
   out_5041909296412759665[316] = 0;
   out_5041909296412759665[317] = 0;
   out_5041909296412759665[318] = 0;
   out_5041909296412759665[319] = 0;
   out_5041909296412759665[320] = 0;
   out_5041909296412759665[321] = 0;
   out_5041909296412759665[322] = 0;
   out_5041909296412759665[323] = 1;
}
void h_4(double *state, double *unused, double *out_6410794677621402397) {
   out_6410794677621402397[0] = state[6] + state[9];
   out_6410794677621402397[1] = state[7] + state[10];
   out_6410794677621402397[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_7109558773609863934) {
   out_7109558773609863934[0] = 0;
   out_7109558773609863934[1] = 0;
   out_7109558773609863934[2] = 0;
   out_7109558773609863934[3] = 0;
   out_7109558773609863934[4] = 0;
   out_7109558773609863934[5] = 0;
   out_7109558773609863934[6] = 1;
   out_7109558773609863934[7] = 0;
   out_7109558773609863934[8] = 0;
   out_7109558773609863934[9] = 1;
   out_7109558773609863934[10] = 0;
   out_7109558773609863934[11] = 0;
   out_7109558773609863934[12] = 0;
   out_7109558773609863934[13] = 0;
   out_7109558773609863934[14] = 0;
   out_7109558773609863934[15] = 0;
   out_7109558773609863934[16] = 0;
   out_7109558773609863934[17] = 0;
   out_7109558773609863934[18] = 0;
   out_7109558773609863934[19] = 0;
   out_7109558773609863934[20] = 0;
   out_7109558773609863934[21] = 0;
   out_7109558773609863934[22] = 0;
   out_7109558773609863934[23] = 0;
   out_7109558773609863934[24] = 0;
   out_7109558773609863934[25] = 1;
   out_7109558773609863934[26] = 0;
   out_7109558773609863934[27] = 0;
   out_7109558773609863934[28] = 1;
   out_7109558773609863934[29] = 0;
   out_7109558773609863934[30] = 0;
   out_7109558773609863934[31] = 0;
   out_7109558773609863934[32] = 0;
   out_7109558773609863934[33] = 0;
   out_7109558773609863934[34] = 0;
   out_7109558773609863934[35] = 0;
   out_7109558773609863934[36] = 0;
   out_7109558773609863934[37] = 0;
   out_7109558773609863934[38] = 0;
   out_7109558773609863934[39] = 0;
   out_7109558773609863934[40] = 0;
   out_7109558773609863934[41] = 0;
   out_7109558773609863934[42] = 0;
   out_7109558773609863934[43] = 0;
   out_7109558773609863934[44] = 1;
   out_7109558773609863934[45] = 0;
   out_7109558773609863934[46] = 0;
   out_7109558773609863934[47] = 1;
   out_7109558773609863934[48] = 0;
   out_7109558773609863934[49] = 0;
   out_7109558773609863934[50] = 0;
   out_7109558773609863934[51] = 0;
   out_7109558773609863934[52] = 0;
   out_7109558773609863934[53] = 0;
}
void h_10(double *state, double *unused, double *out_7278806369328538184) {
   out_7278806369328538184[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_7278806369328538184[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_7278806369328538184[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6138938714751040661) {
   out_6138938714751040661[0] = 0;
   out_6138938714751040661[1] = 9.8100000000000005*cos(state[1]);
   out_6138938714751040661[2] = 0;
   out_6138938714751040661[3] = 0;
   out_6138938714751040661[4] = -state[8];
   out_6138938714751040661[5] = state[7];
   out_6138938714751040661[6] = 0;
   out_6138938714751040661[7] = state[5];
   out_6138938714751040661[8] = -state[4];
   out_6138938714751040661[9] = 0;
   out_6138938714751040661[10] = 0;
   out_6138938714751040661[11] = 0;
   out_6138938714751040661[12] = 1;
   out_6138938714751040661[13] = 0;
   out_6138938714751040661[14] = 0;
   out_6138938714751040661[15] = 1;
   out_6138938714751040661[16] = 0;
   out_6138938714751040661[17] = 0;
   out_6138938714751040661[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6138938714751040661[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6138938714751040661[20] = 0;
   out_6138938714751040661[21] = state[8];
   out_6138938714751040661[22] = 0;
   out_6138938714751040661[23] = -state[6];
   out_6138938714751040661[24] = -state[5];
   out_6138938714751040661[25] = 0;
   out_6138938714751040661[26] = state[3];
   out_6138938714751040661[27] = 0;
   out_6138938714751040661[28] = 0;
   out_6138938714751040661[29] = 0;
   out_6138938714751040661[30] = 0;
   out_6138938714751040661[31] = 1;
   out_6138938714751040661[32] = 0;
   out_6138938714751040661[33] = 0;
   out_6138938714751040661[34] = 1;
   out_6138938714751040661[35] = 0;
   out_6138938714751040661[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6138938714751040661[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6138938714751040661[38] = 0;
   out_6138938714751040661[39] = -state[7];
   out_6138938714751040661[40] = state[6];
   out_6138938714751040661[41] = 0;
   out_6138938714751040661[42] = state[4];
   out_6138938714751040661[43] = -state[3];
   out_6138938714751040661[44] = 0;
   out_6138938714751040661[45] = 0;
   out_6138938714751040661[46] = 0;
   out_6138938714751040661[47] = 0;
   out_6138938714751040661[48] = 0;
   out_6138938714751040661[49] = 0;
   out_6138938714751040661[50] = 1;
   out_6138938714751040661[51] = 0;
   out_6138938714751040661[52] = 0;
   out_6138938714751040661[53] = 1;
}
void h_13(double *state, double *unused, double *out_8268474279687789459) {
   out_8268474279687789459[0] = state[3];
   out_8268474279687789459[1] = state[4];
   out_8268474279687789459[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3897284948277531133) {
   out_3897284948277531133[0] = 0;
   out_3897284948277531133[1] = 0;
   out_3897284948277531133[2] = 0;
   out_3897284948277531133[3] = 1;
   out_3897284948277531133[4] = 0;
   out_3897284948277531133[5] = 0;
   out_3897284948277531133[6] = 0;
   out_3897284948277531133[7] = 0;
   out_3897284948277531133[8] = 0;
   out_3897284948277531133[9] = 0;
   out_3897284948277531133[10] = 0;
   out_3897284948277531133[11] = 0;
   out_3897284948277531133[12] = 0;
   out_3897284948277531133[13] = 0;
   out_3897284948277531133[14] = 0;
   out_3897284948277531133[15] = 0;
   out_3897284948277531133[16] = 0;
   out_3897284948277531133[17] = 0;
   out_3897284948277531133[18] = 0;
   out_3897284948277531133[19] = 0;
   out_3897284948277531133[20] = 0;
   out_3897284948277531133[21] = 0;
   out_3897284948277531133[22] = 1;
   out_3897284948277531133[23] = 0;
   out_3897284948277531133[24] = 0;
   out_3897284948277531133[25] = 0;
   out_3897284948277531133[26] = 0;
   out_3897284948277531133[27] = 0;
   out_3897284948277531133[28] = 0;
   out_3897284948277531133[29] = 0;
   out_3897284948277531133[30] = 0;
   out_3897284948277531133[31] = 0;
   out_3897284948277531133[32] = 0;
   out_3897284948277531133[33] = 0;
   out_3897284948277531133[34] = 0;
   out_3897284948277531133[35] = 0;
   out_3897284948277531133[36] = 0;
   out_3897284948277531133[37] = 0;
   out_3897284948277531133[38] = 0;
   out_3897284948277531133[39] = 0;
   out_3897284948277531133[40] = 0;
   out_3897284948277531133[41] = 1;
   out_3897284948277531133[42] = 0;
   out_3897284948277531133[43] = 0;
   out_3897284948277531133[44] = 0;
   out_3897284948277531133[45] = 0;
   out_3897284948277531133[46] = 0;
   out_3897284948277531133[47] = 0;
   out_3897284948277531133[48] = 0;
   out_3897284948277531133[49] = 0;
   out_3897284948277531133[50] = 0;
   out_3897284948277531133[51] = 0;
   out_3897284948277531133[52] = 0;
   out_3897284948277531133[53] = 0;
}
void h_14(double *state, double *unused, double *out_6172142331242380649) {
   out_6172142331242380649[0] = state[6];
   out_6172142331242380649[1] = state[7];
   out_6172142331242380649[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3146317917270379405) {
   out_3146317917270379405[0] = 0;
   out_3146317917270379405[1] = 0;
   out_3146317917270379405[2] = 0;
   out_3146317917270379405[3] = 0;
   out_3146317917270379405[4] = 0;
   out_3146317917270379405[5] = 0;
   out_3146317917270379405[6] = 1;
   out_3146317917270379405[7] = 0;
   out_3146317917270379405[8] = 0;
   out_3146317917270379405[9] = 0;
   out_3146317917270379405[10] = 0;
   out_3146317917270379405[11] = 0;
   out_3146317917270379405[12] = 0;
   out_3146317917270379405[13] = 0;
   out_3146317917270379405[14] = 0;
   out_3146317917270379405[15] = 0;
   out_3146317917270379405[16] = 0;
   out_3146317917270379405[17] = 0;
   out_3146317917270379405[18] = 0;
   out_3146317917270379405[19] = 0;
   out_3146317917270379405[20] = 0;
   out_3146317917270379405[21] = 0;
   out_3146317917270379405[22] = 0;
   out_3146317917270379405[23] = 0;
   out_3146317917270379405[24] = 0;
   out_3146317917270379405[25] = 1;
   out_3146317917270379405[26] = 0;
   out_3146317917270379405[27] = 0;
   out_3146317917270379405[28] = 0;
   out_3146317917270379405[29] = 0;
   out_3146317917270379405[30] = 0;
   out_3146317917270379405[31] = 0;
   out_3146317917270379405[32] = 0;
   out_3146317917270379405[33] = 0;
   out_3146317917270379405[34] = 0;
   out_3146317917270379405[35] = 0;
   out_3146317917270379405[36] = 0;
   out_3146317917270379405[37] = 0;
   out_3146317917270379405[38] = 0;
   out_3146317917270379405[39] = 0;
   out_3146317917270379405[40] = 0;
   out_3146317917270379405[41] = 0;
   out_3146317917270379405[42] = 0;
   out_3146317917270379405[43] = 0;
   out_3146317917270379405[44] = 1;
   out_3146317917270379405[45] = 0;
   out_3146317917270379405[46] = 0;
   out_3146317917270379405[47] = 0;
   out_3146317917270379405[48] = 0;
   out_3146317917270379405[49] = 0;
   out_3146317917270379405[50] = 0;
   out_3146317917270379405[51] = 0;
   out_3146317917270379405[52] = 0;
   out_3146317917270379405[53] = 0;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_5518524982420716050) {
  err_fun(nom_x, delta_x, out_5518524982420716050);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4331401110135306651) {
  inv_err_fun(nom_x, true_x, out_4331401110135306651);
}
void pose_H_mod_fun(double *state, double *out_3835336694818914681) {
  H_mod_fun(state, out_3835336694818914681);
}
void pose_f_fun(double *state, double dt, double *out_4487166249411202898) {
  f_fun(state,  dt, out_4487166249411202898);
}
void pose_F_fun(double *state, double dt, double *out_5041909296412759665) {
  F_fun(state,  dt, out_5041909296412759665);
}
void pose_h_4(double *state, double *unused, double *out_6410794677621402397) {
  h_4(state, unused, out_6410794677621402397);
}
void pose_H_4(double *state, double *unused, double *out_7109558773609863934) {
  H_4(state, unused, out_7109558773609863934);
}
void pose_h_10(double *state, double *unused, double *out_7278806369328538184) {
  h_10(state, unused, out_7278806369328538184);
}
void pose_H_10(double *state, double *unused, double *out_6138938714751040661) {
  H_10(state, unused, out_6138938714751040661);
}
void pose_h_13(double *state, double *unused, double *out_8268474279687789459) {
  h_13(state, unused, out_8268474279687789459);
}
void pose_H_13(double *state, double *unused, double *out_3897284948277531133) {
  H_13(state, unused, out_3897284948277531133);
}
void pose_h_14(double *state, double *unused, double *out_6172142331242380649) {
  h_14(state, unused, out_6172142331242380649);
}
void pose_H_14(double *state, double *unused, double *out_3146317917270379405) {
  H_14(state, unused, out_3146317917270379405);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
