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
void err_fun(double *nom_x, double *delta_x, double *out_521051683878790646) {
   out_521051683878790646[0] = delta_x[0] + nom_x[0];
   out_521051683878790646[1] = delta_x[1] + nom_x[1];
   out_521051683878790646[2] = delta_x[2] + nom_x[2];
   out_521051683878790646[3] = delta_x[3] + nom_x[3];
   out_521051683878790646[4] = delta_x[4] + nom_x[4];
   out_521051683878790646[5] = delta_x[5] + nom_x[5];
   out_521051683878790646[6] = delta_x[6] + nom_x[6];
   out_521051683878790646[7] = delta_x[7] + nom_x[7];
   out_521051683878790646[8] = delta_x[8] + nom_x[8];
   out_521051683878790646[9] = delta_x[9] + nom_x[9];
   out_521051683878790646[10] = delta_x[10] + nom_x[10];
   out_521051683878790646[11] = delta_x[11] + nom_x[11];
   out_521051683878790646[12] = delta_x[12] + nom_x[12];
   out_521051683878790646[13] = delta_x[13] + nom_x[13];
   out_521051683878790646[14] = delta_x[14] + nom_x[14];
   out_521051683878790646[15] = delta_x[15] + nom_x[15];
   out_521051683878790646[16] = delta_x[16] + nom_x[16];
   out_521051683878790646[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_210058828153721645) {
   out_210058828153721645[0] = -nom_x[0] + true_x[0];
   out_210058828153721645[1] = -nom_x[1] + true_x[1];
   out_210058828153721645[2] = -nom_x[2] + true_x[2];
   out_210058828153721645[3] = -nom_x[3] + true_x[3];
   out_210058828153721645[4] = -nom_x[4] + true_x[4];
   out_210058828153721645[5] = -nom_x[5] + true_x[5];
   out_210058828153721645[6] = -nom_x[6] + true_x[6];
   out_210058828153721645[7] = -nom_x[7] + true_x[7];
   out_210058828153721645[8] = -nom_x[8] + true_x[8];
   out_210058828153721645[9] = -nom_x[9] + true_x[9];
   out_210058828153721645[10] = -nom_x[10] + true_x[10];
   out_210058828153721645[11] = -nom_x[11] + true_x[11];
   out_210058828153721645[12] = -nom_x[12] + true_x[12];
   out_210058828153721645[13] = -nom_x[13] + true_x[13];
   out_210058828153721645[14] = -nom_x[14] + true_x[14];
   out_210058828153721645[15] = -nom_x[15] + true_x[15];
   out_210058828153721645[16] = -nom_x[16] + true_x[16];
   out_210058828153721645[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4312613236564964080) {
   out_4312613236564964080[0] = 1.0;
   out_4312613236564964080[1] = 0.0;
   out_4312613236564964080[2] = 0.0;
   out_4312613236564964080[3] = 0.0;
   out_4312613236564964080[4] = 0.0;
   out_4312613236564964080[5] = 0.0;
   out_4312613236564964080[6] = 0.0;
   out_4312613236564964080[7] = 0.0;
   out_4312613236564964080[8] = 0.0;
   out_4312613236564964080[9] = 0.0;
   out_4312613236564964080[10] = 0.0;
   out_4312613236564964080[11] = 0.0;
   out_4312613236564964080[12] = 0.0;
   out_4312613236564964080[13] = 0.0;
   out_4312613236564964080[14] = 0.0;
   out_4312613236564964080[15] = 0.0;
   out_4312613236564964080[16] = 0.0;
   out_4312613236564964080[17] = 0.0;
   out_4312613236564964080[18] = 0.0;
   out_4312613236564964080[19] = 1.0;
   out_4312613236564964080[20] = 0.0;
   out_4312613236564964080[21] = 0.0;
   out_4312613236564964080[22] = 0.0;
   out_4312613236564964080[23] = 0.0;
   out_4312613236564964080[24] = 0.0;
   out_4312613236564964080[25] = 0.0;
   out_4312613236564964080[26] = 0.0;
   out_4312613236564964080[27] = 0.0;
   out_4312613236564964080[28] = 0.0;
   out_4312613236564964080[29] = 0.0;
   out_4312613236564964080[30] = 0.0;
   out_4312613236564964080[31] = 0.0;
   out_4312613236564964080[32] = 0.0;
   out_4312613236564964080[33] = 0.0;
   out_4312613236564964080[34] = 0.0;
   out_4312613236564964080[35] = 0.0;
   out_4312613236564964080[36] = 0.0;
   out_4312613236564964080[37] = 0.0;
   out_4312613236564964080[38] = 1.0;
   out_4312613236564964080[39] = 0.0;
   out_4312613236564964080[40] = 0.0;
   out_4312613236564964080[41] = 0.0;
   out_4312613236564964080[42] = 0.0;
   out_4312613236564964080[43] = 0.0;
   out_4312613236564964080[44] = 0.0;
   out_4312613236564964080[45] = 0.0;
   out_4312613236564964080[46] = 0.0;
   out_4312613236564964080[47] = 0.0;
   out_4312613236564964080[48] = 0.0;
   out_4312613236564964080[49] = 0.0;
   out_4312613236564964080[50] = 0.0;
   out_4312613236564964080[51] = 0.0;
   out_4312613236564964080[52] = 0.0;
   out_4312613236564964080[53] = 0.0;
   out_4312613236564964080[54] = 0.0;
   out_4312613236564964080[55] = 0.0;
   out_4312613236564964080[56] = 0.0;
   out_4312613236564964080[57] = 1.0;
   out_4312613236564964080[58] = 0.0;
   out_4312613236564964080[59] = 0.0;
   out_4312613236564964080[60] = 0.0;
   out_4312613236564964080[61] = 0.0;
   out_4312613236564964080[62] = 0.0;
   out_4312613236564964080[63] = 0.0;
   out_4312613236564964080[64] = 0.0;
   out_4312613236564964080[65] = 0.0;
   out_4312613236564964080[66] = 0.0;
   out_4312613236564964080[67] = 0.0;
   out_4312613236564964080[68] = 0.0;
   out_4312613236564964080[69] = 0.0;
   out_4312613236564964080[70] = 0.0;
   out_4312613236564964080[71] = 0.0;
   out_4312613236564964080[72] = 0.0;
   out_4312613236564964080[73] = 0.0;
   out_4312613236564964080[74] = 0.0;
   out_4312613236564964080[75] = 0.0;
   out_4312613236564964080[76] = 1.0;
   out_4312613236564964080[77] = 0.0;
   out_4312613236564964080[78] = 0.0;
   out_4312613236564964080[79] = 0.0;
   out_4312613236564964080[80] = 0.0;
   out_4312613236564964080[81] = 0.0;
   out_4312613236564964080[82] = 0.0;
   out_4312613236564964080[83] = 0.0;
   out_4312613236564964080[84] = 0.0;
   out_4312613236564964080[85] = 0.0;
   out_4312613236564964080[86] = 0.0;
   out_4312613236564964080[87] = 0.0;
   out_4312613236564964080[88] = 0.0;
   out_4312613236564964080[89] = 0.0;
   out_4312613236564964080[90] = 0.0;
   out_4312613236564964080[91] = 0.0;
   out_4312613236564964080[92] = 0.0;
   out_4312613236564964080[93] = 0.0;
   out_4312613236564964080[94] = 0.0;
   out_4312613236564964080[95] = 1.0;
   out_4312613236564964080[96] = 0.0;
   out_4312613236564964080[97] = 0.0;
   out_4312613236564964080[98] = 0.0;
   out_4312613236564964080[99] = 0.0;
   out_4312613236564964080[100] = 0.0;
   out_4312613236564964080[101] = 0.0;
   out_4312613236564964080[102] = 0.0;
   out_4312613236564964080[103] = 0.0;
   out_4312613236564964080[104] = 0.0;
   out_4312613236564964080[105] = 0.0;
   out_4312613236564964080[106] = 0.0;
   out_4312613236564964080[107] = 0.0;
   out_4312613236564964080[108] = 0.0;
   out_4312613236564964080[109] = 0.0;
   out_4312613236564964080[110] = 0.0;
   out_4312613236564964080[111] = 0.0;
   out_4312613236564964080[112] = 0.0;
   out_4312613236564964080[113] = 0.0;
   out_4312613236564964080[114] = 1.0;
   out_4312613236564964080[115] = 0.0;
   out_4312613236564964080[116] = 0.0;
   out_4312613236564964080[117] = 0.0;
   out_4312613236564964080[118] = 0.0;
   out_4312613236564964080[119] = 0.0;
   out_4312613236564964080[120] = 0.0;
   out_4312613236564964080[121] = 0.0;
   out_4312613236564964080[122] = 0.0;
   out_4312613236564964080[123] = 0.0;
   out_4312613236564964080[124] = 0.0;
   out_4312613236564964080[125] = 0.0;
   out_4312613236564964080[126] = 0.0;
   out_4312613236564964080[127] = 0.0;
   out_4312613236564964080[128] = 0.0;
   out_4312613236564964080[129] = 0.0;
   out_4312613236564964080[130] = 0.0;
   out_4312613236564964080[131] = 0.0;
   out_4312613236564964080[132] = 0.0;
   out_4312613236564964080[133] = 1.0;
   out_4312613236564964080[134] = 0.0;
   out_4312613236564964080[135] = 0.0;
   out_4312613236564964080[136] = 0.0;
   out_4312613236564964080[137] = 0.0;
   out_4312613236564964080[138] = 0.0;
   out_4312613236564964080[139] = 0.0;
   out_4312613236564964080[140] = 0.0;
   out_4312613236564964080[141] = 0.0;
   out_4312613236564964080[142] = 0.0;
   out_4312613236564964080[143] = 0.0;
   out_4312613236564964080[144] = 0.0;
   out_4312613236564964080[145] = 0.0;
   out_4312613236564964080[146] = 0.0;
   out_4312613236564964080[147] = 0.0;
   out_4312613236564964080[148] = 0.0;
   out_4312613236564964080[149] = 0.0;
   out_4312613236564964080[150] = 0.0;
   out_4312613236564964080[151] = 0.0;
   out_4312613236564964080[152] = 1.0;
   out_4312613236564964080[153] = 0.0;
   out_4312613236564964080[154] = 0.0;
   out_4312613236564964080[155] = 0.0;
   out_4312613236564964080[156] = 0.0;
   out_4312613236564964080[157] = 0.0;
   out_4312613236564964080[158] = 0.0;
   out_4312613236564964080[159] = 0.0;
   out_4312613236564964080[160] = 0.0;
   out_4312613236564964080[161] = 0.0;
   out_4312613236564964080[162] = 0.0;
   out_4312613236564964080[163] = 0.0;
   out_4312613236564964080[164] = 0.0;
   out_4312613236564964080[165] = 0.0;
   out_4312613236564964080[166] = 0.0;
   out_4312613236564964080[167] = 0.0;
   out_4312613236564964080[168] = 0.0;
   out_4312613236564964080[169] = 0.0;
   out_4312613236564964080[170] = 0.0;
   out_4312613236564964080[171] = 1.0;
   out_4312613236564964080[172] = 0.0;
   out_4312613236564964080[173] = 0.0;
   out_4312613236564964080[174] = 0.0;
   out_4312613236564964080[175] = 0.0;
   out_4312613236564964080[176] = 0.0;
   out_4312613236564964080[177] = 0.0;
   out_4312613236564964080[178] = 0.0;
   out_4312613236564964080[179] = 0.0;
   out_4312613236564964080[180] = 0.0;
   out_4312613236564964080[181] = 0.0;
   out_4312613236564964080[182] = 0.0;
   out_4312613236564964080[183] = 0.0;
   out_4312613236564964080[184] = 0.0;
   out_4312613236564964080[185] = 0.0;
   out_4312613236564964080[186] = 0.0;
   out_4312613236564964080[187] = 0.0;
   out_4312613236564964080[188] = 0.0;
   out_4312613236564964080[189] = 0.0;
   out_4312613236564964080[190] = 1.0;
   out_4312613236564964080[191] = 0.0;
   out_4312613236564964080[192] = 0.0;
   out_4312613236564964080[193] = 0.0;
   out_4312613236564964080[194] = 0.0;
   out_4312613236564964080[195] = 0.0;
   out_4312613236564964080[196] = 0.0;
   out_4312613236564964080[197] = 0.0;
   out_4312613236564964080[198] = 0.0;
   out_4312613236564964080[199] = 0.0;
   out_4312613236564964080[200] = 0.0;
   out_4312613236564964080[201] = 0.0;
   out_4312613236564964080[202] = 0.0;
   out_4312613236564964080[203] = 0.0;
   out_4312613236564964080[204] = 0.0;
   out_4312613236564964080[205] = 0.0;
   out_4312613236564964080[206] = 0.0;
   out_4312613236564964080[207] = 0.0;
   out_4312613236564964080[208] = 0.0;
   out_4312613236564964080[209] = 1.0;
   out_4312613236564964080[210] = 0.0;
   out_4312613236564964080[211] = 0.0;
   out_4312613236564964080[212] = 0.0;
   out_4312613236564964080[213] = 0.0;
   out_4312613236564964080[214] = 0.0;
   out_4312613236564964080[215] = 0.0;
   out_4312613236564964080[216] = 0.0;
   out_4312613236564964080[217] = 0.0;
   out_4312613236564964080[218] = 0.0;
   out_4312613236564964080[219] = 0.0;
   out_4312613236564964080[220] = 0.0;
   out_4312613236564964080[221] = 0.0;
   out_4312613236564964080[222] = 0.0;
   out_4312613236564964080[223] = 0.0;
   out_4312613236564964080[224] = 0.0;
   out_4312613236564964080[225] = 0.0;
   out_4312613236564964080[226] = 0.0;
   out_4312613236564964080[227] = 0.0;
   out_4312613236564964080[228] = 1.0;
   out_4312613236564964080[229] = 0.0;
   out_4312613236564964080[230] = 0.0;
   out_4312613236564964080[231] = 0.0;
   out_4312613236564964080[232] = 0.0;
   out_4312613236564964080[233] = 0.0;
   out_4312613236564964080[234] = 0.0;
   out_4312613236564964080[235] = 0.0;
   out_4312613236564964080[236] = 0.0;
   out_4312613236564964080[237] = 0.0;
   out_4312613236564964080[238] = 0.0;
   out_4312613236564964080[239] = 0.0;
   out_4312613236564964080[240] = 0.0;
   out_4312613236564964080[241] = 0.0;
   out_4312613236564964080[242] = 0.0;
   out_4312613236564964080[243] = 0.0;
   out_4312613236564964080[244] = 0.0;
   out_4312613236564964080[245] = 0.0;
   out_4312613236564964080[246] = 0.0;
   out_4312613236564964080[247] = 1.0;
   out_4312613236564964080[248] = 0.0;
   out_4312613236564964080[249] = 0.0;
   out_4312613236564964080[250] = 0.0;
   out_4312613236564964080[251] = 0.0;
   out_4312613236564964080[252] = 0.0;
   out_4312613236564964080[253] = 0.0;
   out_4312613236564964080[254] = 0.0;
   out_4312613236564964080[255] = 0.0;
   out_4312613236564964080[256] = 0.0;
   out_4312613236564964080[257] = 0.0;
   out_4312613236564964080[258] = 0.0;
   out_4312613236564964080[259] = 0.0;
   out_4312613236564964080[260] = 0.0;
   out_4312613236564964080[261] = 0.0;
   out_4312613236564964080[262] = 0.0;
   out_4312613236564964080[263] = 0.0;
   out_4312613236564964080[264] = 0.0;
   out_4312613236564964080[265] = 0.0;
   out_4312613236564964080[266] = 1.0;
   out_4312613236564964080[267] = 0.0;
   out_4312613236564964080[268] = 0.0;
   out_4312613236564964080[269] = 0.0;
   out_4312613236564964080[270] = 0.0;
   out_4312613236564964080[271] = 0.0;
   out_4312613236564964080[272] = 0.0;
   out_4312613236564964080[273] = 0.0;
   out_4312613236564964080[274] = 0.0;
   out_4312613236564964080[275] = 0.0;
   out_4312613236564964080[276] = 0.0;
   out_4312613236564964080[277] = 0.0;
   out_4312613236564964080[278] = 0.0;
   out_4312613236564964080[279] = 0.0;
   out_4312613236564964080[280] = 0.0;
   out_4312613236564964080[281] = 0.0;
   out_4312613236564964080[282] = 0.0;
   out_4312613236564964080[283] = 0.0;
   out_4312613236564964080[284] = 0.0;
   out_4312613236564964080[285] = 1.0;
   out_4312613236564964080[286] = 0.0;
   out_4312613236564964080[287] = 0.0;
   out_4312613236564964080[288] = 0.0;
   out_4312613236564964080[289] = 0.0;
   out_4312613236564964080[290] = 0.0;
   out_4312613236564964080[291] = 0.0;
   out_4312613236564964080[292] = 0.0;
   out_4312613236564964080[293] = 0.0;
   out_4312613236564964080[294] = 0.0;
   out_4312613236564964080[295] = 0.0;
   out_4312613236564964080[296] = 0.0;
   out_4312613236564964080[297] = 0.0;
   out_4312613236564964080[298] = 0.0;
   out_4312613236564964080[299] = 0.0;
   out_4312613236564964080[300] = 0.0;
   out_4312613236564964080[301] = 0.0;
   out_4312613236564964080[302] = 0.0;
   out_4312613236564964080[303] = 0.0;
   out_4312613236564964080[304] = 1.0;
   out_4312613236564964080[305] = 0.0;
   out_4312613236564964080[306] = 0.0;
   out_4312613236564964080[307] = 0.0;
   out_4312613236564964080[308] = 0.0;
   out_4312613236564964080[309] = 0.0;
   out_4312613236564964080[310] = 0.0;
   out_4312613236564964080[311] = 0.0;
   out_4312613236564964080[312] = 0.0;
   out_4312613236564964080[313] = 0.0;
   out_4312613236564964080[314] = 0.0;
   out_4312613236564964080[315] = 0.0;
   out_4312613236564964080[316] = 0.0;
   out_4312613236564964080[317] = 0.0;
   out_4312613236564964080[318] = 0.0;
   out_4312613236564964080[319] = 0.0;
   out_4312613236564964080[320] = 0.0;
   out_4312613236564964080[321] = 0.0;
   out_4312613236564964080[322] = 0.0;
   out_4312613236564964080[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_7807614062433422920) {
   out_7807614062433422920[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_7807614062433422920[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_7807614062433422920[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_7807614062433422920[3] = dt*state[12] + state[3];
   out_7807614062433422920[4] = dt*state[13] + state[4];
   out_7807614062433422920[5] = dt*state[14] + state[5];
   out_7807614062433422920[6] = state[6];
   out_7807614062433422920[7] = state[7];
   out_7807614062433422920[8] = state[8];
   out_7807614062433422920[9] = state[9];
   out_7807614062433422920[10] = state[10];
   out_7807614062433422920[11] = state[11];
   out_7807614062433422920[12] = state[12];
   out_7807614062433422920[13] = state[13];
   out_7807614062433422920[14] = state[14];
   out_7807614062433422920[15] = state[15];
   out_7807614062433422920[16] = state[16];
   out_7807614062433422920[17] = state[17];
}
void F_fun(double *state, double dt, double *out_54869773676509633) {
   out_54869773676509633[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_54869773676509633[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_54869773676509633[2] = 0;
   out_54869773676509633[3] = 0;
   out_54869773676509633[4] = 0;
   out_54869773676509633[5] = 0;
   out_54869773676509633[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_54869773676509633[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_54869773676509633[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_54869773676509633[9] = 0;
   out_54869773676509633[10] = 0;
   out_54869773676509633[11] = 0;
   out_54869773676509633[12] = 0;
   out_54869773676509633[13] = 0;
   out_54869773676509633[14] = 0;
   out_54869773676509633[15] = 0;
   out_54869773676509633[16] = 0;
   out_54869773676509633[17] = 0;
   out_54869773676509633[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_54869773676509633[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_54869773676509633[20] = 0;
   out_54869773676509633[21] = 0;
   out_54869773676509633[22] = 0;
   out_54869773676509633[23] = 0;
   out_54869773676509633[24] = 0;
   out_54869773676509633[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_54869773676509633[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_54869773676509633[27] = 0;
   out_54869773676509633[28] = 0;
   out_54869773676509633[29] = 0;
   out_54869773676509633[30] = 0;
   out_54869773676509633[31] = 0;
   out_54869773676509633[32] = 0;
   out_54869773676509633[33] = 0;
   out_54869773676509633[34] = 0;
   out_54869773676509633[35] = 0;
   out_54869773676509633[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_54869773676509633[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_54869773676509633[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_54869773676509633[39] = 0;
   out_54869773676509633[40] = 0;
   out_54869773676509633[41] = 0;
   out_54869773676509633[42] = 0;
   out_54869773676509633[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_54869773676509633[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_54869773676509633[45] = 0;
   out_54869773676509633[46] = 0;
   out_54869773676509633[47] = 0;
   out_54869773676509633[48] = 0;
   out_54869773676509633[49] = 0;
   out_54869773676509633[50] = 0;
   out_54869773676509633[51] = 0;
   out_54869773676509633[52] = 0;
   out_54869773676509633[53] = 0;
   out_54869773676509633[54] = 0;
   out_54869773676509633[55] = 0;
   out_54869773676509633[56] = 0;
   out_54869773676509633[57] = 1;
   out_54869773676509633[58] = 0;
   out_54869773676509633[59] = 0;
   out_54869773676509633[60] = 0;
   out_54869773676509633[61] = 0;
   out_54869773676509633[62] = 0;
   out_54869773676509633[63] = 0;
   out_54869773676509633[64] = 0;
   out_54869773676509633[65] = 0;
   out_54869773676509633[66] = dt;
   out_54869773676509633[67] = 0;
   out_54869773676509633[68] = 0;
   out_54869773676509633[69] = 0;
   out_54869773676509633[70] = 0;
   out_54869773676509633[71] = 0;
   out_54869773676509633[72] = 0;
   out_54869773676509633[73] = 0;
   out_54869773676509633[74] = 0;
   out_54869773676509633[75] = 0;
   out_54869773676509633[76] = 1;
   out_54869773676509633[77] = 0;
   out_54869773676509633[78] = 0;
   out_54869773676509633[79] = 0;
   out_54869773676509633[80] = 0;
   out_54869773676509633[81] = 0;
   out_54869773676509633[82] = 0;
   out_54869773676509633[83] = 0;
   out_54869773676509633[84] = 0;
   out_54869773676509633[85] = dt;
   out_54869773676509633[86] = 0;
   out_54869773676509633[87] = 0;
   out_54869773676509633[88] = 0;
   out_54869773676509633[89] = 0;
   out_54869773676509633[90] = 0;
   out_54869773676509633[91] = 0;
   out_54869773676509633[92] = 0;
   out_54869773676509633[93] = 0;
   out_54869773676509633[94] = 0;
   out_54869773676509633[95] = 1;
   out_54869773676509633[96] = 0;
   out_54869773676509633[97] = 0;
   out_54869773676509633[98] = 0;
   out_54869773676509633[99] = 0;
   out_54869773676509633[100] = 0;
   out_54869773676509633[101] = 0;
   out_54869773676509633[102] = 0;
   out_54869773676509633[103] = 0;
   out_54869773676509633[104] = dt;
   out_54869773676509633[105] = 0;
   out_54869773676509633[106] = 0;
   out_54869773676509633[107] = 0;
   out_54869773676509633[108] = 0;
   out_54869773676509633[109] = 0;
   out_54869773676509633[110] = 0;
   out_54869773676509633[111] = 0;
   out_54869773676509633[112] = 0;
   out_54869773676509633[113] = 0;
   out_54869773676509633[114] = 1;
   out_54869773676509633[115] = 0;
   out_54869773676509633[116] = 0;
   out_54869773676509633[117] = 0;
   out_54869773676509633[118] = 0;
   out_54869773676509633[119] = 0;
   out_54869773676509633[120] = 0;
   out_54869773676509633[121] = 0;
   out_54869773676509633[122] = 0;
   out_54869773676509633[123] = 0;
   out_54869773676509633[124] = 0;
   out_54869773676509633[125] = 0;
   out_54869773676509633[126] = 0;
   out_54869773676509633[127] = 0;
   out_54869773676509633[128] = 0;
   out_54869773676509633[129] = 0;
   out_54869773676509633[130] = 0;
   out_54869773676509633[131] = 0;
   out_54869773676509633[132] = 0;
   out_54869773676509633[133] = 1;
   out_54869773676509633[134] = 0;
   out_54869773676509633[135] = 0;
   out_54869773676509633[136] = 0;
   out_54869773676509633[137] = 0;
   out_54869773676509633[138] = 0;
   out_54869773676509633[139] = 0;
   out_54869773676509633[140] = 0;
   out_54869773676509633[141] = 0;
   out_54869773676509633[142] = 0;
   out_54869773676509633[143] = 0;
   out_54869773676509633[144] = 0;
   out_54869773676509633[145] = 0;
   out_54869773676509633[146] = 0;
   out_54869773676509633[147] = 0;
   out_54869773676509633[148] = 0;
   out_54869773676509633[149] = 0;
   out_54869773676509633[150] = 0;
   out_54869773676509633[151] = 0;
   out_54869773676509633[152] = 1;
   out_54869773676509633[153] = 0;
   out_54869773676509633[154] = 0;
   out_54869773676509633[155] = 0;
   out_54869773676509633[156] = 0;
   out_54869773676509633[157] = 0;
   out_54869773676509633[158] = 0;
   out_54869773676509633[159] = 0;
   out_54869773676509633[160] = 0;
   out_54869773676509633[161] = 0;
   out_54869773676509633[162] = 0;
   out_54869773676509633[163] = 0;
   out_54869773676509633[164] = 0;
   out_54869773676509633[165] = 0;
   out_54869773676509633[166] = 0;
   out_54869773676509633[167] = 0;
   out_54869773676509633[168] = 0;
   out_54869773676509633[169] = 0;
   out_54869773676509633[170] = 0;
   out_54869773676509633[171] = 1;
   out_54869773676509633[172] = 0;
   out_54869773676509633[173] = 0;
   out_54869773676509633[174] = 0;
   out_54869773676509633[175] = 0;
   out_54869773676509633[176] = 0;
   out_54869773676509633[177] = 0;
   out_54869773676509633[178] = 0;
   out_54869773676509633[179] = 0;
   out_54869773676509633[180] = 0;
   out_54869773676509633[181] = 0;
   out_54869773676509633[182] = 0;
   out_54869773676509633[183] = 0;
   out_54869773676509633[184] = 0;
   out_54869773676509633[185] = 0;
   out_54869773676509633[186] = 0;
   out_54869773676509633[187] = 0;
   out_54869773676509633[188] = 0;
   out_54869773676509633[189] = 0;
   out_54869773676509633[190] = 1;
   out_54869773676509633[191] = 0;
   out_54869773676509633[192] = 0;
   out_54869773676509633[193] = 0;
   out_54869773676509633[194] = 0;
   out_54869773676509633[195] = 0;
   out_54869773676509633[196] = 0;
   out_54869773676509633[197] = 0;
   out_54869773676509633[198] = 0;
   out_54869773676509633[199] = 0;
   out_54869773676509633[200] = 0;
   out_54869773676509633[201] = 0;
   out_54869773676509633[202] = 0;
   out_54869773676509633[203] = 0;
   out_54869773676509633[204] = 0;
   out_54869773676509633[205] = 0;
   out_54869773676509633[206] = 0;
   out_54869773676509633[207] = 0;
   out_54869773676509633[208] = 0;
   out_54869773676509633[209] = 1;
   out_54869773676509633[210] = 0;
   out_54869773676509633[211] = 0;
   out_54869773676509633[212] = 0;
   out_54869773676509633[213] = 0;
   out_54869773676509633[214] = 0;
   out_54869773676509633[215] = 0;
   out_54869773676509633[216] = 0;
   out_54869773676509633[217] = 0;
   out_54869773676509633[218] = 0;
   out_54869773676509633[219] = 0;
   out_54869773676509633[220] = 0;
   out_54869773676509633[221] = 0;
   out_54869773676509633[222] = 0;
   out_54869773676509633[223] = 0;
   out_54869773676509633[224] = 0;
   out_54869773676509633[225] = 0;
   out_54869773676509633[226] = 0;
   out_54869773676509633[227] = 0;
   out_54869773676509633[228] = 1;
   out_54869773676509633[229] = 0;
   out_54869773676509633[230] = 0;
   out_54869773676509633[231] = 0;
   out_54869773676509633[232] = 0;
   out_54869773676509633[233] = 0;
   out_54869773676509633[234] = 0;
   out_54869773676509633[235] = 0;
   out_54869773676509633[236] = 0;
   out_54869773676509633[237] = 0;
   out_54869773676509633[238] = 0;
   out_54869773676509633[239] = 0;
   out_54869773676509633[240] = 0;
   out_54869773676509633[241] = 0;
   out_54869773676509633[242] = 0;
   out_54869773676509633[243] = 0;
   out_54869773676509633[244] = 0;
   out_54869773676509633[245] = 0;
   out_54869773676509633[246] = 0;
   out_54869773676509633[247] = 1;
   out_54869773676509633[248] = 0;
   out_54869773676509633[249] = 0;
   out_54869773676509633[250] = 0;
   out_54869773676509633[251] = 0;
   out_54869773676509633[252] = 0;
   out_54869773676509633[253] = 0;
   out_54869773676509633[254] = 0;
   out_54869773676509633[255] = 0;
   out_54869773676509633[256] = 0;
   out_54869773676509633[257] = 0;
   out_54869773676509633[258] = 0;
   out_54869773676509633[259] = 0;
   out_54869773676509633[260] = 0;
   out_54869773676509633[261] = 0;
   out_54869773676509633[262] = 0;
   out_54869773676509633[263] = 0;
   out_54869773676509633[264] = 0;
   out_54869773676509633[265] = 0;
   out_54869773676509633[266] = 1;
   out_54869773676509633[267] = 0;
   out_54869773676509633[268] = 0;
   out_54869773676509633[269] = 0;
   out_54869773676509633[270] = 0;
   out_54869773676509633[271] = 0;
   out_54869773676509633[272] = 0;
   out_54869773676509633[273] = 0;
   out_54869773676509633[274] = 0;
   out_54869773676509633[275] = 0;
   out_54869773676509633[276] = 0;
   out_54869773676509633[277] = 0;
   out_54869773676509633[278] = 0;
   out_54869773676509633[279] = 0;
   out_54869773676509633[280] = 0;
   out_54869773676509633[281] = 0;
   out_54869773676509633[282] = 0;
   out_54869773676509633[283] = 0;
   out_54869773676509633[284] = 0;
   out_54869773676509633[285] = 1;
   out_54869773676509633[286] = 0;
   out_54869773676509633[287] = 0;
   out_54869773676509633[288] = 0;
   out_54869773676509633[289] = 0;
   out_54869773676509633[290] = 0;
   out_54869773676509633[291] = 0;
   out_54869773676509633[292] = 0;
   out_54869773676509633[293] = 0;
   out_54869773676509633[294] = 0;
   out_54869773676509633[295] = 0;
   out_54869773676509633[296] = 0;
   out_54869773676509633[297] = 0;
   out_54869773676509633[298] = 0;
   out_54869773676509633[299] = 0;
   out_54869773676509633[300] = 0;
   out_54869773676509633[301] = 0;
   out_54869773676509633[302] = 0;
   out_54869773676509633[303] = 0;
   out_54869773676509633[304] = 1;
   out_54869773676509633[305] = 0;
   out_54869773676509633[306] = 0;
   out_54869773676509633[307] = 0;
   out_54869773676509633[308] = 0;
   out_54869773676509633[309] = 0;
   out_54869773676509633[310] = 0;
   out_54869773676509633[311] = 0;
   out_54869773676509633[312] = 0;
   out_54869773676509633[313] = 0;
   out_54869773676509633[314] = 0;
   out_54869773676509633[315] = 0;
   out_54869773676509633[316] = 0;
   out_54869773676509633[317] = 0;
   out_54869773676509633[318] = 0;
   out_54869773676509633[319] = 0;
   out_54869773676509633[320] = 0;
   out_54869773676509633[321] = 0;
   out_54869773676509633[322] = 0;
   out_54869773676509633[323] = 1;
}
void h_4(double *state, double *unused, double *out_3501775823039351379) {
   out_3501775823039351379[0] = state[6] + state[9];
   out_3501775823039351379[1] = state[7] + state[10];
   out_3501775823039351379[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_8084420446408871652) {
   out_8084420446408871652[0] = 0;
   out_8084420446408871652[1] = 0;
   out_8084420446408871652[2] = 0;
   out_8084420446408871652[3] = 0;
   out_8084420446408871652[4] = 0;
   out_8084420446408871652[5] = 0;
   out_8084420446408871652[6] = 1;
   out_8084420446408871652[7] = 0;
   out_8084420446408871652[8] = 0;
   out_8084420446408871652[9] = 1;
   out_8084420446408871652[10] = 0;
   out_8084420446408871652[11] = 0;
   out_8084420446408871652[12] = 0;
   out_8084420446408871652[13] = 0;
   out_8084420446408871652[14] = 0;
   out_8084420446408871652[15] = 0;
   out_8084420446408871652[16] = 0;
   out_8084420446408871652[17] = 0;
   out_8084420446408871652[18] = 0;
   out_8084420446408871652[19] = 0;
   out_8084420446408871652[20] = 0;
   out_8084420446408871652[21] = 0;
   out_8084420446408871652[22] = 0;
   out_8084420446408871652[23] = 0;
   out_8084420446408871652[24] = 0;
   out_8084420446408871652[25] = 1;
   out_8084420446408871652[26] = 0;
   out_8084420446408871652[27] = 0;
   out_8084420446408871652[28] = 1;
   out_8084420446408871652[29] = 0;
   out_8084420446408871652[30] = 0;
   out_8084420446408871652[31] = 0;
   out_8084420446408871652[32] = 0;
   out_8084420446408871652[33] = 0;
   out_8084420446408871652[34] = 0;
   out_8084420446408871652[35] = 0;
   out_8084420446408871652[36] = 0;
   out_8084420446408871652[37] = 0;
   out_8084420446408871652[38] = 0;
   out_8084420446408871652[39] = 0;
   out_8084420446408871652[40] = 0;
   out_8084420446408871652[41] = 0;
   out_8084420446408871652[42] = 0;
   out_8084420446408871652[43] = 0;
   out_8084420446408871652[44] = 1;
   out_8084420446408871652[45] = 0;
   out_8084420446408871652[46] = 0;
   out_8084420446408871652[47] = 1;
   out_8084420446408871652[48] = 0;
   out_8084420446408871652[49] = 0;
   out_8084420446408871652[50] = 0;
   out_8084420446408871652[51] = 0;
   out_8084420446408871652[52] = 0;
   out_8084420446408871652[53] = 0;
}
void h_10(double *state, double *unused, double *out_8571708459300677945) {
   out_8571708459300677945[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8571708459300677945[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8571708459300677945[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2059745207116816931) {
   out_2059745207116816931[0] = 0;
   out_2059745207116816931[1] = 9.8100000000000005*cos(state[1]);
   out_2059745207116816931[2] = 0;
   out_2059745207116816931[3] = 0;
   out_2059745207116816931[4] = -state[8];
   out_2059745207116816931[5] = state[7];
   out_2059745207116816931[6] = 0;
   out_2059745207116816931[7] = state[5];
   out_2059745207116816931[8] = -state[4];
   out_2059745207116816931[9] = 0;
   out_2059745207116816931[10] = 0;
   out_2059745207116816931[11] = 0;
   out_2059745207116816931[12] = 1;
   out_2059745207116816931[13] = 0;
   out_2059745207116816931[14] = 0;
   out_2059745207116816931[15] = 1;
   out_2059745207116816931[16] = 0;
   out_2059745207116816931[17] = 0;
   out_2059745207116816931[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2059745207116816931[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2059745207116816931[20] = 0;
   out_2059745207116816931[21] = state[8];
   out_2059745207116816931[22] = 0;
   out_2059745207116816931[23] = -state[6];
   out_2059745207116816931[24] = -state[5];
   out_2059745207116816931[25] = 0;
   out_2059745207116816931[26] = state[3];
   out_2059745207116816931[27] = 0;
   out_2059745207116816931[28] = 0;
   out_2059745207116816931[29] = 0;
   out_2059745207116816931[30] = 0;
   out_2059745207116816931[31] = 1;
   out_2059745207116816931[32] = 0;
   out_2059745207116816931[33] = 0;
   out_2059745207116816931[34] = 1;
   out_2059745207116816931[35] = 0;
   out_2059745207116816931[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2059745207116816931[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2059745207116816931[38] = 0;
   out_2059745207116816931[39] = -state[7];
   out_2059745207116816931[40] = state[6];
   out_2059745207116816931[41] = 0;
   out_2059745207116816931[42] = state[4];
   out_2059745207116816931[43] = -state[3];
   out_2059745207116816931[44] = 0;
   out_2059745207116816931[45] = 0;
   out_2059745207116816931[46] = 0;
   out_2059745207116816931[47] = 0;
   out_2059745207116816931[48] = 0;
   out_2059745207116816931[49] = 0;
   out_2059745207116816931[50] = 1;
   out_2059745207116816931[51] = 0;
   out_2059745207116816931[52] = 0;
   out_2059745207116816931[53] = 1;
}
void h_13(double *state, double *unused, double *out_6791205246269589213) {
   out_6791205246269589213[0] = state[3];
   out_6791205246269589213[1] = state[4];
   out_6791205246269589213[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8649022366090715756) {
   out_8649022366090715756[0] = 0;
   out_8649022366090715756[1] = 0;
   out_8649022366090715756[2] = 0;
   out_8649022366090715756[3] = 1;
   out_8649022366090715756[4] = 0;
   out_8649022366090715756[5] = 0;
   out_8649022366090715756[6] = 0;
   out_8649022366090715756[7] = 0;
   out_8649022366090715756[8] = 0;
   out_8649022366090715756[9] = 0;
   out_8649022366090715756[10] = 0;
   out_8649022366090715756[11] = 0;
   out_8649022366090715756[12] = 0;
   out_8649022366090715756[13] = 0;
   out_8649022366090715756[14] = 0;
   out_8649022366090715756[15] = 0;
   out_8649022366090715756[16] = 0;
   out_8649022366090715756[17] = 0;
   out_8649022366090715756[18] = 0;
   out_8649022366090715756[19] = 0;
   out_8649022366090715756[20] = 0;
   out_8649022366090715756[21] = 0;
   out_8649022366090715756[22] = 1;
   out_8649022366090715756[23] = 0;
   out_8649022366090715756[24] = 0;
   out_8649022366090715756[25] = 0;
   out_8649022366090715756[26] = 0;
   out_8649022366090715756[27] = 0;
   out_8649022366090715756[28] = 0;
   out_8649022366090715756[29] = 0;
   out_8649022366090715756[30] = 0;
   out_8649022366090715756[31] = 0;
   out_8649022366090715756[32] = 0;
   out_8649022366090715756[33] = 0;
   out_8649022366090715756[34] = 0;
   out_8649022366090715756[35] = 0;
   out_8649022366090715756[36] = 0;
   out_8649022366090715756[37] = 0;
   out_8649022366090715756[38] = 0;
   out_8649022366090715756[39] = 0;
   out_8649022366090715756[40] = 0;
   out_8649022366090715756[41] = 1;
   out_8649022366090715756[42] = 0;
   out_8649022366090715756[43] = 0;
   out_8649022366090715756[44] = 0;
   out_8649022366090715756[45] = 0;
   out_8649022366090715756[46] = 0;
   out_8649022366090715756[47] = 0;
   out_8649022366090715756[48] = 0;
   out_8649022366090715756[49] = 0;
   out_8649022366090715756[50] = 0;
   out_8649022366090715756[51] = 0;
   out_8649022366090715756[52] = 0;
   out_8649022366090715756[53] = 0;
}
void h_14(double *state, double *unused, double *out_8615295986968492388) {
   out_8615295986968492388[0] = state[6];
   out_8615295986968492388[1] = state[7];
   out_8615295986968492388[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5001632014113499356) {
   out_5001632014113499356[0] = 0;
   out_5001632014113499356[1] = 0;
   out_5001632014113499356[2] = 0;
   out_5001632014113499356[3] = 0;
   out_5001632014113499356[4] = 0;
   out_5001632014113499356[5] = 0;
   out_5001632014113499356[6] = 1;
   out_5001632014113499356[7] = 0;
   out_5001632014113499356[8] = 0;
   out_5001632014113499356[9] = 0;
   out_5001632014113499356[10] = 0;
   out_5001632014113499356[11] = 0;
   out_5001632014113499356[12] = 0;
   out_5001632014113499356[13] = 0;
   out_5001632014113499356[14] = 0;
   out_5001632014113499356[15] = 0;
   out_5001632014113499356[16] = 0;
   out_5001632014113499356[17] = 0;
   out_5001632014113499356[18] = 0;
   out_5001632014113499356[19] = 0;
   out_5001632014113499356[20] = 0;
   out_5001632014113499356[21] = 0;
   out_5001632014113499356[22] = 0;
   out_5001632014113499356[23] = 0;
   out_5001632014113499356[24] = 0;
   out_5001632014113499356[25] = 1;
   out_5001632014113499356[26] = 0;
   out_5001632014113499356[27] = 0;
   out_5001632014113499356[28] = 0;
   out_5001632014113499356[29] = 0;
   out_5001632014113499356[30] = 0;
   out_5001632014113499356[31] = 0;
   out_5001632014113499356[32] = 0;
   out_5001632014113499356[33] = 0;
   out_5001632014113499356[34] = 0;
   out_5001632014113499356[35] = 0;
   out_5001632014113499356[36] = 0;
   out_5001632014113499356[37] = 0;
   out_5001632014113499356[38] = 0;
   out_5001632014113499356[39] = 0;
   out_5001632014113499356[40] = 0;
   out_5001632014113499356[41] = 0;
   out_5001632014113499356[42] = 0;
   out_5001632014113499356[43] = 0;
   out_5001632014113499356[44] = 1;
   out_5001632014113499356[45] = 0;
   out_5001632014113499356[46] = 0;
   out_5001632014113499356[47] = 0;
   out_5001632014113499356[48] = 0;
   out_5001632014113499356[49] = 0;
   out_5001632014113499356[50] = 0;
   out_5001632014113499356[51] = 0;
   out_5001632014113499356[52] = 0;
   out_5001632014113499356[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_521051683878790646) {
  err_fun(nom_x, delta_x, out_521051683878790646);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_210058828153721645) {
  inv_err_fun(nom_x, true_x, out_210058828153721645);
}
void pose_H_mod_fun(double *state, double *out_4312613236564964080) {
  H_mod_fun(state, out_4312613236564964080);
}
void pose_f_fun(double *state, double dt, double *out_7807614062433422920) {
  f_fun(state,  dt, out_7807614062433422920);
}
void pose_F_fun(double *state, double dt, double *out_54869773676509633) {
  F_fun(state,  dt, out_54869773676509633);
}
void pose_h_4(double *state, double *unused, double *out_3501775823039351379) {
  h_4(state, unused, out_3501775823039351379);
}
void pose_H_4(double *state, double *unused, double *out_8084420446408871652) {
  H_4(state, unused, out_8084420446408871652);
}
void pose_h_10(double *state, double *unused, double *out_8571708459300677945) {
  h_10(state, unused, out_8571708459300677945);
}
void pose_H_10(double *state, double *unused, double *out_2059745207116816931) {
  H_10(state, unused, out_2059745207116816931);
}
void pose_h_13(double *state, double *unused, double *out_6791205246269589213) {
  h_13(state, unused, out_6791205246269589213);
}
void pose_H_13(double *state, double *unused, double *out_8649022366090715756) {
  H_13(state, unused, out_8649022366090715756);
}
void pose_h_14(double *state, double *unused, double *out_8615295986968492388) {
  h_14(state, unused, out_8615295986968492388);
}
void pose_H_14(double *state, double *unused, double *out_5001632014113499356) {
  H_14(state, unused, out_5001632014113499356);
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
