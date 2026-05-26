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
void err_fun(double *nom_x, double *delta_x, double *out_7536058918625145808) {
   out_7536058918625145808[0] = delta_x[0] + nom_x[0];
   out_7536058918625145808[1] = delta_x[1] + nom_x[1];
   out_7536058918625145808[2] = delta_x[2] + nom_x[2];
   out_7536058918625145808[3] = delta_x[3] + nom_x[3];
   out_7536058918625145808[4] = delta_x[4] + nom_x[4];
   out_7536058918625145808[5] = delta_x[5] + nom_x[5];
   out_7536058918625145808[6] = delta_x[6] + nom_x[6];
   out_7536058918625145808[7] = delta_x[7] + nom_x[7];
   out_7536058918625145808[8] = delta_x[8] + nom_x[8];
   out_7536058918625145808[9] = delta_x[9] + nom_x[9];
   out_7536058918625145808[10] = delta_x[10] + nom_x[10];
   out_7536058918625145808[11] = delta_x[11] + nom_x[11];
   out_7536058918625145808[12] = delta_x[12] + nom_x[12];
   out_7536058918625145808[13] = delta_x[13] + nom_x[13];
   out_7536058918625145808[14] = delta_x[14] + nom_x[14];
   out_7536058918625145808[15] = delta_x[15] + nom_x[15];
   out_7536058918625145808[16] = delta_x[16] + nom_x[16];
   out_7536058918625145808[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6294980525542920357) {
   out_6294980525542920357[0] = -nom_x[0] + true_x[0];
   out_6294980525542920357[1] = -nom_x[1] + true_x[1];
   out_6294980525542920357[2] = -nom_x[2] + true_x[2];
   out_6294980525542920357[3] = -nom_x[3] + true_x[3];
   out_6294980525542920357[4] = -nom_x[4] + true_x[4];
   out_6294980525542920357[5] = -nom_x[5] + true_x[5];
   out_6294980525542920357[6] = -nom_x[6] + true_x[6];
   out_6294980525542920357[7] = -nom_x[7] + true_x[7];
   out_6294980525542920357[8] = -nom_x[8] + true_x[8];
   out_6294980525542920357[9] = -nom_x[9] + true_x[9];
   out_6294980525542920357[10] = -nom_x[10] + true_x[10];
   out_6294980525542920357[11] = -nom_x[11] + true_x[11];
   out_6294980525542920357[12] = -nom_x[12] + true_x[12];
   out_6294980525542920357[13] = -nom_x[13] + true_x[13];
   out_6294980525542920357[14] = -nom_x[14] + true_x[14];
   out_6294980525542920357[15] = -nom_x[15] + true_x[15];
   out_6294980525542920357[16] = -nom_x[16] + true_x[16];
   out_6294980525542920357[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_1208523344993905378) {
   out_1208523344993905378[0] = 1.0;
   out_1208523344993905378[1] = 0.0;
   out_1208523344993905378[2] = 0.0;
   out_1208523344993905378[3] = 0.0;
   out_1208523344993905378[4] = 0.0;
   out_1208523344993905378[5] = 0.0;
   out_1208523344993905378[6] = 0.0;
   out_1208523344993905378[7] = 0.0;
   out_1208523344993905378[8] = 0.0;
   out_1208523344993905378[9] = 0.0;
   out_1208523344993905378[10] = 0.0;
   out_1208523344993905378[11] = 0.0;
   out_1208523344993905378[12] = 0.0;
   out_1208523344993905378[13] = 0.0;
   out_1208523344993905378[14] = 0.0;
   out_1208523344993905378[15] = 0.0;
   out_1208523344993905378[16] = 0.0;
   out_1208523344993905378[17] = 0.0;
   out_1208523344993905378[18] = 0.0;
   out_1208523344993905378[19] = 1.0;
   out_1208523344993905378[20] = 0.0;
   out_1208523344993905378[21] = 0.0;
   out_1208523344993905378[22] = 0.0;
   out_1208523344993905378[23] = 0.0;
   out_1208523344993905378[24] = 0.0;
   out_1208523344993905378[25] = 0.0;
   out_1208523344993905378[26] = 0.0;
   out_1208523344993905378[27] = 0.0;
   out_1208523344993905378[28] = 0.0;
   out_1208523344993905378[29] = 0.0;
   out_1208523344993905378[30] = 0.0;
   out_1208523344993905378[31] = 0.0;
   out_1208523344993905378[32] = 0.0;
   out_1208523344993905378[33] = 0.0;
   out_1208523344993905378[34] = 0.0;
   out_1208523344993905378[35] = 0.0;
   out_1208523344993905378[36] = 0.0;
   out_1208523344993905378[37] = 0.0;
   out_1208523344993905378[38] = 1.0;
   out_1208523344993905378[39] = 0.0;
   out_1208523344993905378[40] = 0.0;
   out_1208523344993905378[41] = 0.0;
   out_1208523344993905378[42] = 0.0;
   out_1208523344993905378[43] = 0.0;
   out_1208523344993905378[44] = 0.0;
   out_1208523344993905378[45] = 0.0;
   out_1208523344993905378[46] = 0.0;
   out_1208523344993905378[47] = 0.0;
   out_1208523344993905378[48] = 0.0;
   out_1208523344993905378[49] = 0.0;
   out_1208523344993905378[50] = 0.0;
   out_1208523344993905378[51] = 0.0;
   out_1208523344993905378[52] = 0.0;
   out_1208523344993905378[53] = 0.0;
   out_1208523344993905378[54] = 0.0;
   out_1208523344993905378[55] = 0.0;
   out_1208523344993905378[56] = 0.0;
   out_1208523344993905378[57] = 1.0;
   out_1208523344993905378[58] = 0.0;
   out_1208523344993905378[59] = 0.0;
   out_1208523344993905378[60] = 0.0;
   out_1208523344993905378[61] = 0.0;
   out_1208523344993905378[62] = 0.0;
   out_1208523344993905378[63] = 0.0;
   out_1208523344993905378[64] = 0.0;
   out_1208523344993905378[65] = 0.0;
   out_1208523344993905378[66] = 0.0;
   out_1208523344993905378[67] = 0.0;
   out_1208523344993905378[68] = 0.0;
   out_1208523344993905378[69] = 0.0;
   out_1208523344993905378[70] = 0.0;
   out_1208523344993905378[71] = 0.0;
   out_1208523344993905378[72] = 0.0;
   out_1208523344993905378[73] = 0.0;
   out_1208523344993905378[74] = 0.0;
   out_1208523344993905378[75] = 0.0;
   out_1208523344993905378[76] = 1.0;
   out_1208523344993905378[77] = 0.0;
   out_1208523344993905378[78] = 0.0;
   out_1208523344993905378[79] = 0.0;
   out_1208523344993905378[80] = 0.0;
   out_1208523344993905378[81] = 0.0;
   out_1208523344993905378[82] = 0.0;
   out_1208523344993905378[83] = 0.0;
   out_1208523344993905378[84] = 0.0;
   out_1208523344993905378[85] = 0.0;
   out_1208523344993905378[86] = 0.0;
   out_1208523344993905378[87] = 0.0;
   out_1208523344993905378[88] = 0.0;
   out_1208523344993905378[89] = 0.0;
   out_1208523344993905378[90] = 0.0;
   out_1208523344993905378[91] = 0.0;
   out_1208523344993905378[92] = 0.0;
   out_1208523344993905378[93] = 0.0;
   out_1208523344993905378[94] = 0.0;
   out_1208523344993905378[95] = 1.0;
   out_1208523344993905378[96] = 0.0;
   out_1208523344993905378[97] = 0.0;
   out_1208523344993905378[98] = 0.0;
   out_1208523344993905378[99] = 0.0;
   out_1208523344993905378[100] = 0.0;
   out_1208523344993905378[101] = 0.0;
   out_1208523344993905378[102] = 0.0;
   out_1208523344993905378[103] = 0.0;
   out_1208523344993905378[104] = 0.0;
   out_1208523344993905378[105] = 0.0;
   out_1208523344993905378[106] = 0.0;
   out_1208523344993905378[107] = 0.0;
   out_1208523344993905378[108] = 0.0;
   out_1208523344993905378[109] = 0.0;
   out_1208523344993905378[110] = 0.0;
   out_1208523344993905378[111] = 0.0;
   out_1208523344993905378[112] = 0.0;
   out_1208523344993905378[113] = 0.0;
   out_1208523344993905378[114] = 1.0;
   out_1208523344993905378[115] = 0.0;
   out_1208523344993905378[116] = 0.0;
   out_1208523344993905378[117] = 0.0;
   out_1208523344993905378[118] = 0.0;
   out_1208523344993905378[119] = 0.0;
   out_1208523344993905378[120] = 0.0;
   out_1208523344993905378[121] = 0.0;
   out_1208523344993905378[122] = 0.0;
   out_1208523344993905378[123] = 0.0;
   out_1208523344993905378[124] = 0.0;
   out_1208523344993905378[125] = 0.0;
   out_1208523344993905378[126] = 0.0;
   out_1208523344993905378[127] = 0.0;
   out_1208523344993905378[128] = 0.0;
   out_1208523344993905378[129] = 0.0;
   out_1208523344993905378[130] = 0.0;
   out_1208523344993905378[131] = 0.0;
   out_1208523344993905378[132] = 0.0;
   out_1208523344993905378[133] = 1.0;
   out_1208523344993905378[134] = 0.0;
   out_1208523344993905378[135] = 0.0;
   out_1208523344993905378[136] = 0.0;
   out_1208523344993905378[137] = 0.0;
   out_1208523344993905378[138] = 0.0;
   out_1208523344993905378[139] = 0.0;
   out_1208523344993905378[140] = 0.0;
   out_1208523344993905378[141] = 0.0;
   out_1208523344993905378[142] = 0.0;
   out_1208523344993905378[143] = 0.0;
   out_1208523344993905378[144] = 0.0;
   out_1208523344993905378[145] = 0.0;
   out_1208523344993905378[146] = 0.0;
   out_1208523344993905378[147] = 0.0;
   out_1208523344993905378[148] = 0.0;
   out_1208523344993905378[149] = 0.0;
   out_1208523344993905378[150] = 0.0;
   out_1208523344993905378[151] = 0.0;
   out_1208523344993905378[152] = 1.0;
   out_1208523344993905378[153] = 0.0;
   out_1208523344993905378[154] = 0.0;
   out_1208523344993905378[155] = 0.0;
   out_1208523344993905378[156] = 0.0;
   out_1208523344993905378[157] = 0.0;
   out_1208523344993905378[158] = 0.0;
   out_1208523344993905378[159] = 0.0;
   out_1208523344993905378[160] = 0.0;
   out_1208523344993905378[161] = 0.0;
   out_1208523344993905378[162] = 0.0;
   out_1208523344993905378[163] = 0.0;
   out_1208523344993905378[164] = 0.0;
   out_1208523344993905378[165] = 0.0;
   out_1208523344993905378[166] = 0.0;
   out_1208523344993905378[167] = 0.0;
   out_1208523344993905378[168] = 0.0;
   out_1208523344993905378[169] = 0.0;
   out_1208523344993905378[170] = 0.0;
   out_1208523344993905378[171] = 1.0;
   out_1208523344993905378[172] = 0.0;
   out_1208523344993905378[173] = 0.0;
   out_1208523344993905378[174] = 0.0;
   out_1208523344993905378[175] = 0.0;
   out_1208523344993905378[176] = 0.0;
   out_1208523344993905378[177] = 0.0;
   out_1208523344993905378[178] = 0.0;
   out_1208523344993905378[179] = 0.0;
   out_1208523344993905378[180] = 0.0;
   out_1208523344993905378[181] = 0.0;
   out_1208523344993905378[182] = 0.0;
   out_1208523344993905378[183] = 0.0;
   out_1208523344993905378[184] = 0.0;
   out_1208523344993905378[185] = 0.0;
   out_1208523344993905378[186] = 0.0;
   out_1208523344993905378[187] = 0.0;
   out_1208523344993905378[188] = 0.0;
   out_1208523344993905378[189] = 0.0;
   out_1208523344993905378[190] = 1.0;
   out_1208523344993905378[191] = 0.0;
   out_1208523344993905378[192] = 0.0;
   out_1208523344993905378[193] = 0.0;
   out_1208523344993905378[194] = 0.0;
   out_1208523344993905378[195] = 0.0;
   out_1208523344993905378[196] = 0.0;
   out_1208523344993905378[197] = 0.0;
   out_1208523344993905378[198] = 0.0;
   out_1208523344993905378[199] = 0.0;
   out_1208523344993905378[200] = 0.0;
   out_1208523344993905378[201] = 0.0;
   out_1208523344993905378[202] = 0.0;
   out_1208523344993905378[203] = 0.0;
   out_1208523344993905378[204] = 0.0;
   out_1208523344993905378[205] = 0.0;
   out_1208523344993905378[206] = 0.0;
   out_1208523344993905378[207] = 0.0;
   out_1208523344993905378[208] = 0.0;
   out_1208523344993905378[209] = 1.0;
   out_1208523344993905378[210] = 0.0;
   out_1208523344993905378[211] = 0.0;
   out_1208523344993905378[212] = 0.0;
   out_1208523344993905378[213] = 0.0;
   out_1208523344993905378[214] = 0.0;
   out_1208523344993905378[215] = 0.0;
   out_1208523344993905378[216] = 0.0;
   out_1208523344993905378[217] = 0.0;
   out_1208523344993905378[218] = 0.0;
   out_1208523344993905378[219] = 0.0;
   out_1208523344993905378[220] = 0.0;
   out_1208523344993905378[221] = 0.0;
   out_1208523344993905378[222] = 0.0;
   out_1208523344993905378[223] = 0.0;
   out_1208523344993905378[224] = 0.0;
   out_1208523344993905378[225] = 0.0;
   out_1208523344993905378[226] = 0.0;
   out_1208523344993905378[227] = 0.0;
   out_1208523344993905378[228] = 1.0;
   out_1208523344993905378[229] = 0.0;
   out_1208523344993905378[230] = 0.0;
   out_1208523344993905378[231] = 0.0;
   out_1208523344993905378[232] = 0.0;
   out_1208523344993905378[233] = 0.0;
   out_1208523344993905378[234] = 0.0;
   out_1208523344993905378[235] = 0.0;
   out_1208523344993905378[236] = 0.0;
   out_1208523344993905378[237] = 0.0;
   out_1208523344993905378[238] = 0.0;
   out_1208523344993905378[239] = 0.0;
   out_1208523344993905378[240] = 0.0;
   out_1208523344993905378[241] = 0.0;
   out_1208523344993905378[242] = 0.0;
   out_1208523344993905378[243] = 0.0;
   out_1208523344993905378[244] = 0.0;
   out_1208523344993905378[245] = 0.0;
   out_1208523344993905378[246] = 0.0;
   out_1208523344993905378[247] = 1.0;
   out_1208523344993905378[248] = 0.0;
   out_1208523344993905378[249] = 0.0;
   out_1208523344993905378[250] = 0.0;
   out_1208523344993905378[251] = 0.0;
   out_1208523344993905378[252] = 0.0;
   out_1208523344993905378[253] = 0.0;
   out_1208523344993905378[254] = 0.0;
   out_1208523344993905378[255] = 0.0;
   out_1208523344993905378[256] = 0.0;
   out_1208523344993905378[257] = 0.0;
   out_1208523344993905378[258] = 0.0;
   out_1208523344993905378[259] = 0.0;
   out_1208523344993905378[260] = 0.0;
   out_1208523344993905378[261] = 0.0;
   out_1208523344993905378[262] = 0.0;
   out_1208523344993905378[263] = 0.0;
   out_1208523344993905378[264] = 0.0;
   out_1208523344993905378[265] = 0.0;
   out_1208523344993905378[266] = 1.0;
   out_1208523344993905378[267] = 0.0;
   out_1208523344993905378[268] = 0.0;
   out_1208523344993905378[269] = 0.0;
   out_1208523344993905378[270] = 0.0;
   out_1208523344993905378[271] = 0.0;
   out_1208523344993905378[272] = 0.0;
   out_1208523344993905378[273] = 0.0;
   out_1208523344993905378[274] = 0.0;
   out_1208523344993905378[275] = 0.0;
   out_1208523344993905378[276] = 0.0;
   out_1208523344993905378[277] = 0.0;
   out_1208523344993905378[278] = 0.0;
   out_1208523344993905378[279] = 0.0;
   out_1208523344993905378[280] = 0.0;
   out_1208523344993905378[281] = 0.0;
   out_1208523344993905378[282] = 0.0;
   out_1208523344993905378[283] = 0.0;
   out_1208523344993905378[284] = 0.0;
   out_1208523344993905378[285] = 1.0;
   out_1208523344993905378[286] = 0.0;
   out_1208523344993905378[287] = 0.0;
   out_1208523344993905378[288] = 0.0;
   out_1208523344993905378[289] = 0.0;
   out_1208523344993905378[290] = 0.0;
   out_1208523344993905378[291] = 0.0;
   out_1208523344993905378[292] = 0.0;
   out_1208523344993905378[293] = 0.0;
   out_1208523344993905378[294] = 0.0;
   out_1208523344993905378[295] = 0.0;
   out_1208523344993905378[296] = 0.0;
   out_1208523344993905378[297] = 0.0;
   out_1208523344993905378[298] = 0.0;
   out_1208523344993905378[299] = 0.0;
   out_1208523344993905378[300] = 0.0;
   out_1208523344993905378[301] = 0.0;
   out_1208523344993905378[302] = 0.0;
   out_1208523344993905378[303] = 0.0;
   out_1208523344993905378[304] = 1.0;
   out_1208523344993905378[305] = 0.0;
   out_1208523344993905378[306] = 0.0;
   out_1208523344993905378[307] = 0.0;
   out_1208523344993905378[308] = 0.0;
   out_1208523344993905378[309] = 0.0;
   out_1208523344993905378[310] = 0.0;
   out_1208523344993905378[311] = 0.0;
   out_1208523344993905378[312] = 0.0;
   out_1208523344993905378[313] = 0.0;
   out_1208523344993905378[314] = 0.0;
   out_1208523344993905378[315] = 0.0;
   out_1208523344993905378[316] = 0.0;
   out_1208523344993905378[317] = 0.0;
   out_1208523344993905378[318] = 0.0;
   out_1208523344993905378[319] = 0.0;
   out_1208523344993905378[320] = 0.0;
   out_1208523344993905378[321] = 0.0;
   out_1208523344993905378[322] = 0.0;
   out_1208523344993905378[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_828336908542161324) {
   out_828336908542161324[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_828336908542161324[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_828336908542161324[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_828336908542161324[3] = dt*state[12] + state[3];
   out_828336908542161324[4] = dt*state[13] + state[4];
   out_828336908542161324[5] = dt*state[14] + state[5];
   out_828336908542161324[6] = state[6];
   out_828336908542161324[7] = state[7];
   out_828336908542161324[8] = state[8];
   out_828336908542161324[9] = state[9];
   out_828336908542161324[10] = state[10];
   out_828336908542161324[11] = state[11];
   out_828336908542161324[12] = state[12];
   out_828336908542161324[13] = state[13];
   out_828336908542161324[14] = state[14];
   out_828336908542161324[15] = state[15];
   out_828336908542161324[16] = state[16];
   out_828336908542161324[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5703387388084628727) {
   out_5703387388084628727[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5703387388084628727[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5703387388084628727[2] = 0;
   out_5703387388084628727[3] = 0;
   out_5703387388084628727[4] = 0;
   out_5703387388084628727[5] = 0;
   out_5703387388084628727[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5703387388084628727[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5703387388084628727[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5703387388084628727[9] = 0;
   out_5703387388084628727[10] = 0;
   out_5703387388084628727[11] = 0;
   out_5703387388084628727[12] = 0;
   out_5703387388084628727[13] = 0;
   out_5703387388084628727[14] = 0;
   out_5703387388084628727[15] = 0;
   out_5703387388084628727[16] = 0;
   out_5703387388084628727[17] = 0;
   out_5703387388084628727[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5703387388084628727[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5703387388084628727[20] = 0;
   out_5703387388084628727[21] = 0;
   out_5703387388084628727[22] = 0;
   out_5703387388084628727[23] = 0;
   out_5703387388084628727[24] = 0;
   out_5703387388084628727[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5703387388084628727[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5703387388084628727[27] = 0;
   out_5703387388084628727[28] = 0;
   out_5703387388084628727[29] = 0;
   out_5703387388084628727[30] = 0;
   out_5703387388084628727[31] = 0;
   out_5703387388084628727[32] = 0;
   out_5703387388084628727[33] = 0;
   out_5703387388084628727[34] = 0;
   out_5703387388084628727[35] = 0;
   out_5703387388084628727[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5703387388084628727[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5703387388084628727[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5703387388084628727[39] = 0;
   out_5703387388084628727[40] = 0;
   out_5703387388084628727[41] = 0;
   out_5703387388084628727[42] = 0;
   out_5703387388084628727[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5703387388084628727[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5703387388084628727[45] = 0;
   out_5703387388084628727[46] = 0;
   out_5703387388084628727[47] = 0;
   out_5703387388084628727[48] = 0;
   out_5703387388084628727[49] = 0;
   out_5703387388084628727[50] = 0;
   out_5703387388084628727[51] = 0;
   out_5703387388084628727[52] = 0;
   out_5703387388084628727[53] = 0;
   out_5703387388084628727[54] = 0;
   out_5703387388084628727[55] = 0;
   out_5703387388084628727[56] = 0;
   out_5703387388084628727[57] = 1;
   out_5703387388084628727[58] = 0;
   out_5703387388084628727[59] = 0;
   out_5703387388084628727[60] = 0;
   out_5703387388084628727[61] = 0;
   out_5703387388084628727[62] = 0;
   out_5703387388084628727[63] = 0;
   out_5703387388084628727[64] = 0;
   out_5703387388084628727[65] = 0;
   out_5703387388084628727[66] = dt;
   out_5703387388084628727[67] = 0;
   out_5703387388084628727[68] = 0;
   out_5703387388084628727[69] = 0;
   out_5703387388084628727[70] = 0;
   out_5703387388084628727[71] = 0;
   out_5703387388084628727[72] = 0;
   out_5703387388084628727[73] = 0;
   out_5703387388084628727[74] = 0;
   out_5703387388084628727[75] = 0;
   out_5703387388084628727[76] = 1;
   out_5703387388084628727[77] = 0;
   out_5703387388084628727[78] = 0;
   out_5703387388084628727[79] = 0;
   out_5703387388084628727[80] = 0;
   out_5703387388084628727[81] = 0;
   out_5703387388084628727[82] = 0;
   out_5703387388084628727[83] = 0;
   out_5703387388084628727[84] = 0;
   out_5703387388084628727[85] = dt;
   out_5703387388084628727[86] = 0;
   out_5703387388084628727[87] = 0;
   out_5703387388084628727[88] = 0;
   out_5703387388084628727[89] = 0;
   out_5703387388084628727[90] = 0;
   out_5703387388084628727[91] = 0;
   out_5703387388084628727[92] = 0;
   out_5703387388084628727[93] = 0;
   out_5703387388084628727[94] = 0;
   out_5703387388084628727[95] = 1;
   out_5703387388084628727[96] = 0;
   out_5703387388084628727[97] = 0;
   out_5703387388084628727[98] = 0;
   out_5703387388084628727[99] = 0;
   out_5703387388084628727[100] = 0;
   out_5703387388084628727[101] = 0;
   out_5703387388084628727[102] = 0;
   out_5703387388084628727[103] = 0;
   out_5703387388084628727[104] = dt;
   out_5703387388084628727[105] = 0;
   out_5703387388084628727[106] = 0;
   out_5703387388084628727[107] = 0;
   out_5703387388084628727[108] = 0;
   out_5703387388084628727[109] = 0;
   out_5703387388084628727[110] = 0;
   out_5703387388084628727[111] = 0;
   out_5703387388084628727[112] = 0;
   out_5703387388084628727[113] = 0;
   out_5703387388084628727[114] = 1;
   out_5703387388084628727[115] = 0;
   out_5703387388084628727[116] = 0;
   out_5703387388084628727[117] = 0;
   out_5703387388084628727[118] = 0;
   out_5703387388084628727[119] = 0;
   out_5703387388084628727[120] = 0;
   out_5703387388084628727[121] = 0;
   out_5703387388084628727[122] = 0;
   out_5703387388084628727[123] = 0;
   out_5703387388084628727[124] = 0;
   out_5703387388084628727[125] = 0;
   out_5703387388084628727[126] = 0;
   out_5703387388084628727[127] = 0;
   out_5703387388084628727[128] = 0;
   out_5703387388084628727[129] = 0;
   out_5703387388084628727[130] = 0;
   out_5703387388084628727[131] = 0;
   out_5703387388084628727[132] = 0;
   out_5703387388084628727[133] = 1;
   out_5703387388084628727[134] = 0;
   out_5703387388084628727[135] = 0;
   out_5703387388084628727[136] = 0;
   out_5703387388084628727[137] = 0;
   out_5703387388084628727[138] = 0;
   out_5703387388084628727[139] = 0;
   out_5703387388084628727[140] = 0;
   out_5703387388084628727[141] = 0;
   out_5703387388084628727[142] = 0;
   out_5703387388084628727[143] = 0;
   out_5703387388084628727[144] = 0;
   out_5703387388084628727[145] = 0;
   out_5703387388084628727[146] = 0;
   out_5703387388084628727[147] = 0;
   out_5703387388084628727[148] = 0;
   out_5703387388084628727[149] = 0;
   out_5703387388084628727[150] = 0;
   out_5703387388084628727[151] = 0;
   out_5703387388084628727[152] = 1;
   out_5703387388084628727[153] = 0;
   out_5703387388084628727[154] = 0;
   out_5703387388084628727[155] = 0;
   out_5703387388084628727[156] = 0;
   out_5703387388084628727[157] = 0;
   out_5703387388084628727[158] = 0;
   out_5703387388084628727[159] = 0;
   out_5703387388084628727[160] = 0;
   out_5703387388084628727[161] = 0;
   out_5703387388084628727[162] = 0;
   out_5703387388084628727[163] = 0;
   out_5703387388084628727[164] = 0;
   out_5703387388084628727[165] = 0;
   out_5703387388084628727[166] = 0;
   out_5703387388084628727[167] = 0;
   out_5703387388084628727[168] = 0;
   out_5703387388084628727[169] = 0;
   out_5703387388084628727[170] = 0;
   out_5703387388084628727[171] = 1;
   out_5703387388084628727[172] = 0;
   out_5703387388084628727[173] = 0;
   out_5703387388084628727[174] = 0;
   out_5703387388084628727[175] = 0;
   out_5703387388084628727[176] = 0;
   out_5703387388084628727[177] = 0;
   out_5703387388084628727[178] = 0;
   out_5703387388084628727[179] = 0;
   out_5703387388084628727[180] = 0;
   out_5703387388084628727[181] = 0;
   out_5703387388084628727[182] = 0;
   out_5703387388084628727[183] = 0;
   out_5703387388084628727[184] = 0;
   out_5703387388084628727[185] = 0;
   out_5703387388084628727[186] = 0;
   out_5703387388084628727[187] = 0;
   out_5703387388084628727[188] = 0;
   out_5703387388084628727[189] = 0;
   out_5703387388084628727[190] = 1;
   out_5703387388084628727[191] = 0;
   out_5703387388084628727[192] = 0;
   out_5703387388084628727[193] = 0;
   out_5703387388084628727[194] = 0;
   out_5703387388084628727[195] = 0;
   out_5703387388084628727[196] = 0;
   out_5703387388084628727[197] = 0;
   out_5703387388084628727[198] = 0;
   out_5703387388084628727[199] = 0;
   out_5703387388084628727[200] = 0;
   out_5703387388084628727[201] = 0;
   out_5703387388084628727[202] = 0;
   out_5703387388084628727[203] = 0;
   out_5703387388084628727[204] = 0;
   out_5703387388084628727[205] = 0;
   out_5703387388084628727[206] = 0;
   out_5703387388084628727[207] = 0;
   out_5703387388084628727[208] = 0;
   out_5703387388084628727[209] = 1;
   out_5703387388084628727[210] = 0;
   out_5703387388084628727[211] = 0;
   out_5703387388084628727[212] = 0;
   out_5703387388084628727[213] = 0;
   out_5703387388084628727[214] = 0;
   out_5703387388084628727[215] = 0;
   out_5703387388084628727[216] = 0;
   out_5703387388084628727[217] = 0;
   out_5703387388084628727[218] = 0;
   out_5703387388084628727[219] = 0;
   out_5703387388084628727[220] = 0;
   out_5703387388084628727[221] = 0;
   out_5703387388084628727[222] = 0;
   out_5703387388084628727[223] = 0;
   out_5703387388084628727[224] = 0;
   out_5703387388084628727[225] = 0;
   out_5703387388084628727[226] = 0;
   out_5703387388084628727[227] = 0;
   out_5703387388084628727[228] = 1;
   out_5703387388084628727[229] = 0;
   out_5703387388084628727[230] = 0;
   out_5703387388084628727[231] = 0;
   out_5703387388084628727[232] = 0;
   out_5703387388084628727[233] = 0;
   out_5703387388084628727[234] = 0;
   out_5703387388084628727[235] = 0;
   out_5703387388084628727[236] = 0;
   out_5703387388084628727[237] = 0;
   out_5703387388084628727[238] = 0;
   out_5703387388084628727[239] = 0;
   out_5703387388084628727[240] = 0;
   out_5703387388084628727[241] = 0;
   out_5703387388084628727[242] = 0;
   out_5703387388084628727[243] = 0;
   out_5703387388084628727[244] = 0;
   out_5703387388084628727[245] = 0;
   out_5703387388084628727[246] = 0;
   out_5703387388084628727[247] = 1;
   out_5703387388084628727[248] = 0;
   out_5703387388084628727[249] = 0;
   out_5703387388084628727[250] = 0;
   out_5703387388084628727[251] = 0;
   out_5703387388084628727[252] = 0;
   out_5703387388084628727[253] = 0;
   out_5703387388084628727[254] = 0;
   out_5703387388084628727[255] = 0;
   out_5703387388084628727[256] = 0;
   out_5703387388084628727[257] = 0;
   out_5703387388084628727[258] = 0;
   out_5703387388084628727[259] = 0;
   out_5703387388084628727[260] = 0;
   out_5703387388084628727[261] = 0;
   out_5703387388084628727[262] = 0;
   out_5703387388084628727[263] = 0;
   out_5703387388084628727[264] = 0;
   out_5703387388084628727[265] = 0;
   out_5703387388084628727[266] = 1;
   out_5703387388084628727[267] = 0;
   out_5703387388084628727[268] = 0;
   out_5703387388084628727[269] = 0;
   out_5703387388084628727[270] = 0;
   out_5703387388084628727[271] = 0;
   out_5703387388084628727[272] = 0;
   out_5703387388084628727[273] = 0;
   out_5703387388084628727[274] = 0;
   out_5703387388084628727[275] = 0;
   out_5703387388084628727[276] = 0;
   out_5703387388084628727[277] = 0;
   out_5703387388084628727[278] = 0;
   out_5703387388084628727[279] = 0;
   out_5703387388084628727[280] = 0;
   out_5703387388084628727[281] = 0;
   out_5703387388084628727[282] = 0;
   out_5703387388084628727[283] = 0;
   out_5703387388084628727[284] = 0;
   out_5703387388084628727[285] = 1;
   out_5703387388084628727[286] = 0;
   out_5703387388084628727[287] = 0;
   out_5703387388084628727[288] = 0;
   out_5703387388084628727[289] = 0;
   out_5703387388084628727[290] = 0;
   out_5703387388084628727[291] = 0;
   out_5703387388084628727[292] = 0;
   out_5703387388084628727[293] = 0;
   out_5703387388084628727[294] = 0;
   out_5703387388084628727[295] = 0;
   out_5703387388084628727[296] = 0;
   out_5703387388084628727[297] = 0;
   out_5703387388084628727[298] = 0;
   out_5703387388084628727[299] = 0;
   out_5703387388084628727[300] = 0;
   out_5703387388084628727[301] = 0;
   out_5703387388084628727[302] = 0;
   out_5703387388084628727[303] = 0;
   out_5703387388084628727[304] = 1;
   out_5703387388084628727[305] = 0;
   out_5703387388084628727[306] = 0;
   out_5703387388084628727[307] = 0;
   out_5703387388084628727[308] = 0;
   out_5703387388084628727[309] = 0;
   out_5703387388084628727[310] = 0;
   out_5703387388084628727[311] = 0;
   out_5703387388084628727[312] = 0;
   out_5703387388084628727[313] = 0;
   out_5703387388084628727[314] = 0;
   out_5703387388084628727[315] = 0;
   out_5703387388084628727[316] = 0;
   out_5703387388084628727[317] = 0;
   out_5703387388084628727[318] = 0;
   out_5703387388084628727[319] = 0;
   out_5703387388084628727[320] = 0;
   out_5703387388084628727[321] = 0;
   out_5703387388084628727[322] = 0;
   out_5703387388084628727[323] = 1;
}
void h_4(double *state, double *unused, double *out_2600666041609585625) {
   out_2600666041609585625[0] = state[6] + state[9];
   out_2600666041609585625[1] = state[7] + state[10];
   out_2600666041609585625[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2406470826876803482) {
   out_2406470826876803482[0] = 0;
   out_2406470826876803482[1] = 0;
   out_2406470826876803482[2] = 0;
   out_2406470826876803482[3] = 0;
   out_2406470826876803482[4] = 0;
   out_2406470826876803482[5] = 0;
   out_2406470826876803482[6] = 1;
   out_2406470826876803482[7] = 0;
   out_2406470826876803482[8] = 0;
   out_2406470826876803482[9] = 1;
   out_2406470826876803482[10] = 0;
   out_2406470826876803482[11] = 0;
   out_2406470826876803482[12] = 0;
   out_2406470826876803482[13] = 0;
   out_2406470826876803482[14] = 0;
   out_2406470826876803482[15] = 0;
   out_2406470826876803482[16] = 0;
   out_2406470826876803482[17] = 0;
   out_2406470826876803482[18] = 0;
   out_2406470826876803482[19] = 0;
   out_2406470826876803482[20] = 0;
   out_2406470826876803482[21] = 0;
   out_2406470826876803482[22] = 0;
   out_2406470826876803482[23] = 0;
   out_2406470826876803482[24] = 0;
   out_2406470826876803482[25] = 1;
   out_2406470826876803482[26] = 0;
   out_2406470826876803482[27] = 0;
   out_2406470826876803482[28] = 1;
   out_2406470826876803482[29] = 0;
   out_2406470826876803482[30] = 0;
   out_2406470826876803482[31] = 0;
   out_2406470826876803482[32] = 0;
   out_2406470826876803482[33] = 0;
   out_2406470826876803482[34] = 0;
   out_2406470826876803482[35] = 0;
   out_2406470826876803482[36] = 0;
   out_2406470826876803482[37] = 0;
   out_2406470826876803482[38] = 0;
   out_2406470826876803482[39] = 0;
   out_2406470826876803482[40] = 0;
   out_2406470826876803482[41] = 0;
   out_2406470826876803482[42] = 0;
   out_2406470826876803482[43] = 0;
   out_2406470826876803482[44] = 1;
   out_2406470826876803482[45] = 0;
   out_2406470826876803482[46] = 0;
   out_2406470826876803482[47] = 1;
   out_2406470826876803482[48] = 0;
   out_2406470826876803482[49] = 0;
   out_2406470826876803482[50] = 0;
   out_2406470826876803482[51] = 0;
   out_2406470826876803482[52] = 0;
   out_2406470826876803482[53] = 0;
}
void h_10(double *state, double *unused, double *out_2042730394265084466) {
   out_2042730394265084466[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2042730394265084466[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2042730394265084466[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6010400890176312817) {
   out_6010400890176312817[0] = 0;
   out_6010400890176312817[1] = 9.8100000000000005*cos(state[1]);
   out_6010400890176312817[2] = 0;
   out_6010400890176312817[3] = 0;
   out_6010400890176312817[4] = -state[8];
   out_6010400890176312817[5] = state[7];
   out_6010400890176312817[6] = 0;
   out_6010400890176312817[7] = state[5];
   out_6010400890176312817[8] = -state[4];
   out_6010400890176312817[9] = 0;
   out_6010400890176312817[10] = 0;
   out_6010400890176312817[11] = 0;
   out_6010400890176312817[12] = 1;
   out_6010400890176312817[13] = 0;
   out_6010400890176312817[14] = 0;
   out_6010400890176312817[15] = 1;
   out_6010400890176312817[16] = 0;
   out_6010400890176312817[17] = 0;
   out_6010400890176312817[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6010400890176312817[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6010400890176312817[20] = 0;
   out_6010400890176312817[21] = state[8];
   out_6010400890176312817[22] = 0;
   out_6010400890176312817[23] = -state[6];
   out_6010400890176312817[24] = -state[5];
   out_6010400890176312817[25] = 0;
   out_6010400890176312817[26] = state[3];
   out_6010400890176312817[27] = 0;
   out_6010400890176312817[28] = 0;
   out_6010400890176312817[29] = 0;
   out_6010400890176312817[30] = 0;
   out_6010400890176312817[31] = 1;
   out_6010400890176312817[32] = 0;
   out_6010400890176312817[33] = 0;
   out_6010400890176312817[34] = 1;
   out_6010400890176312817[35] = 0;
   out_6010400890176312817[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6010400890176312817[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6010400890176312817[38] = 0;
   out_6010400890176312817[39] = -state[7];
   out_6010400890176312817[40] = state[6];
   out_6010400890176312817[41] = 0;
   out_6010400890176312817[42] = state[4];
   out_6010400890176312817[43] = -state[3];
   out_6010400890176312817[44] = 0;
   out_6010400890176312817[45] = 0;
   out_6010400890176312817[46] = 0;
   out_6010400890176312817[47] = 0;
   out_6010400890176312817[48] = 0;
   out_6010400890176312817[49] = 0;
   out_6010400890176312817[50] = 1;
   out_6010400890176312817[51] = 0;
   out_6010400890176312817[52] = 0;
   out_6010400890176312817[53] = 1;
}
void h_13(double *state, double *unused, double *out_3259369495818676553) {
   out_3259369495818676553[0] = state[3];
   out_3259369495818676553[1] = state[4];
   out_3259369495818676553[2] = state[5];
}
void H_13(double *state, double *unused, double *out_5618744652209136283) {
   out_5618744652209136283[0] = 0;
   out_5618744652209136283[1] = 0;
   out_5618744652209136283[2] = 0;
   out_5618744652209136283[3] = 1;
   out_5618744652209136283[4] = 0;
   out_5618744652209136283[5] = 0;
   out_5618744652209136283[6] = 0;
   out_5618744652209136283[7] = 0;
   out_5618744652209136283[8] = 0;
   out_5618744652209136283[9] = 0;
   out_5618744652209136283[10] = 0;
   out_5618744652209136283[11] = 0;
   out_5618744652209136283[12] = 0;
   out_5618744652209136283[13] = 0;
   out_5618744652209136283[14] = 0;
   out_5618744652209136283[15] = 0;
   out_5618744652209136283[16] = 0;
   out_5618744652209136283[17] = 0;
   out_5618744652209136283[18] = 0;
   out_5618744652209136283[19] = 0;
   out_5618744652209136283[20] = 0;
   out_5618744652209136283[21] = 0;
   out_5618744652209136283[22] = 1;
   out_5618744652209136283[23] = 0;
   out_5618744652209136283[24] = 0;
   out_5618744652209136283[25] = 0;
   out_5618744652209136283[26] = 0;
   out_5618744652209136283[27] = 0;
   out_5618744652209136283[28] = 0;
   out_5618744652209136283[29] = 0;
   out_5618744652209136283[30] = 0;
   out_5618744652209136283[31] = 0;
   out_5618744652209136283[32] = 0;
   out_5618744652209136283[33] = 0;
   out_5618744652209136283[34] = 0;
   out_5618744652209136283[35] = 0;
   out_5618744652209136283[36] = 0;
   out_5618744652209136283[37] = 0;
   out_5618744652209136283[38] = 0;
   out_5618744652209136283[39] = 0;
   out_5618744652209136283[40] = 0;
   out_5618744652209136283[41] = 1;
   out_5618744652209136283[42] = 0;
   out_5618744652209136283[43] = 0;
   out_5618744652209136283[44] = 0;
   out_5618744652209136283[45] = 0;
   out_5618744652209136283[46] = 0;
   out_5618744652209136283[47] = 0;
   out_5618744652209136283[48] = 0;
   out_5618744652209136283[49] = 0;
   out_5618744652209136283[50] = 0;
   out_5618744652209136283[51] = 0;
   out_5618744652209136283[52] = 0;
   out_5618744652209136283[53] = 0;
}
void h_14(double *state, double *unused, double *out_1539412177960834763) {
   out_1539412177960834763[0] = state[6];
   out_1539412177960834763[1] = state[7];
   out_1539412177960834763[2] = state[8];
}
void H_14(double *state, double *unused, double *out_676317605418568814) {
   out_676317605418568814[0] = 0;
   out_676317605418568814[1] = 0;
   out_676317605418568814[2] = 0;
   out_676317605418568814[3] = 0;
   out_676317605418568814[4] = 0;
   out_676317605418568814[5] = 0;
   out_676317605418568814[6] = 1;
   out_676317605418568814[7] = 0;
   out_676317605418568814[8] = 0;
   out_676317605418568814[9] = 0;
   out_676317605418568814[10] = 0;
   out_676317605418568814[11] = 0;
   out_676317605418568814[12] = 0;
   out_676317605418568814[13] = 0;
   out_676317605418568814[14] = 0;
   out_676317605418568814[15] = 0;
   out_676317605418568814[16] = 0;
   out_676317605418568814[17] = 0;
   out_676317605418568814[18] = 0;
   out_676317605418568814[19] = 0;
   out_676317605418568814[20] = 0;
   out_676317605418568814[21] = 0;
   out_676317605418568814[22] = 0;
   out_676317605418568814[23] = 0;
   out_676317605418568814[24] = 0;
   out_676317605418568814[25] = 1;
   out_676317605418568814[26] = 0;
   out_676317605418568814[27] = 0;
   out_676317605418568814[28] = 0;
   out_676317605418568814[29] = 0;
   out_676317605418568814[30] = 0;
   out_676317605418568814[31] = 0;
   out_676317605418568814[32] = 0;
   out_676317605418568814[33] = 0;
   out_676317605418568814[34] = 0;
   out_676317605418568814[35] = 0;
   out_676317605418568814[36] = 0;
   out_676317605418568814[37] = 0;
   out_676317605418568814[38] = 0;
   out_676317605418568814[39] = 0;
   out_676317605418568814[40] = 0;
   out_676317605418568814[41] = 0;
   out_676317605418568814[42] = 0;
   out_676317605418568814[43] = 0;
   out_676317605418568814[44] = 1;
   out_676317605418568814[45] = 0;
   out_676317605418568814[46] = 0;
   out_676317605418568814[47] = 0;
   out_676317605418568814[48] = 0;
   out_676317605418568814[49] = 0;
   out_676317605418568814[50] = 0;
   out_676317605418568814[51] = 0;
   out_676317605418568814[52] = 0;
   out_676317605418568814[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7536058918625145808) {
  err_fun(nom_x, delta_x, out_7536058918625145808);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6294980525542920357) {
  inv_err_fun(nom_x, true_x, out_6294980525542920357);
}
void pose_H_mod_fun(double *state, double *out_1208523344993905378) {
  H_mod_fun(state, out_1208523344993905378);
}
void pose_f_fun(double *state, double dt, double *out_828336908542161324) {
  f_fun(state,  dt, out_828336908542161324);
}
void pose_F_fun(double *state, double dt, double *out_5703387388084628727) {
  F_fun(state,  dt, out_5703387388084628727);
}
void pose_h_4(double *state, double *unused, double *out_2600666041609585625) {
  h_4(state, unused, out_2600666041609585625);
}
void pose_H_4(double *state, double *unused, double *out_2406470826876803482) {
  H_4(state, unused, out_2406470826876803482);
}
void pose_h_10(double *state, double *unused, double *out_2042730394265084466) {
  h_10(state, unused, out_2042730394265084466);
}
void pose_H_10(double *state, double *unused, double *out_6010400890176312817) {
  H_10(state, unused, out_6010400890176312817);
}
void pose_h_13(double *state, double *unused, double *out_3259369495818676553) {
  h_13(state, unused, out_3259369495818676553);
}
void pose_H_13(double *state, double *unused, double *out_5618744652209136283) {
  H_13(state, unused, out_5618744652209136283);
}
void pose_h_14(double *state, double *unused, double *out_1539412177960834763) {
  h_14(state, unused, out_1539412177960834763);
}
void pose_H_14(double *state, double *unused, double *out_676317605418568814) {
  H_14(state, unused, out_676317605418568814);
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
