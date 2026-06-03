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
void err_fun(double *nom_x, double *delta_x, double *out_616508134330162473) {
   out_616508134330162473[0] = delta_x[0] + nom_x[0];
   out_616508134330162473[1] = delta_x[1] + nom_x[1];
   out_616508134330162473[2] = delta_x[2] + nom_x[2];
   out_616508134330162473[3] = delta_x[3] + nom_x[3];
   out_616508134330162473[4] = delta_x[4] + nom_x[4];
   out_616508134330162473[5] = delta_x[5] + nom_x[5];
   out_616508134330162473[6] = delta_x[6] + nom_x[6];
   out_616508134330162473[7] = delta_x[7] + nom_x[7];
   out_616508134330162473[8] = delta_x[8] + nom_x[8];
   out_616508134330162473[9] = delta_x[9] + nom_x[9];
   out_616508134330162473[10] = delta_x[10] + nom_x[10];
   out_616508134330162473[11] = delta_x[11] + nom_x[11];
   out_616508134330162473[12] = delta_x[12] + nom_x[12];
   out_616508134330162473[13] = delta_x[13] + nom_x[13];
   out_616508134330162473[14] = delta_x[14] + nom_x[14];
   out_616508134330162473[15] = delta_x[15] + nom_x[15];
   out_616508134330162473[16] = delta_x[16] + nom_x[16];
   out_616508134330162473[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3534488348241865019) {
   out_3534488348241865019[0] = -nom_x[0] + true_x[0];
   out_3534488348241865019[1] = -nom_x[1] + true_x[1];
   out_3534488348241865019[2] = -nom_x[2] + true_x[2];
   out_3534488348241865019[3] = -nom_x[3] + true_x[3];
   out_3534488348241865019[4] = -nom_x[4] + true_x[4];
   out_3534488348241865019[5] = -nom_x[5] + true_x[5];
   out_3534488348241865019[6] = -nom_x[6] + true_x[6];
   out_3534488348241865019[7] = -nom_x[7] + true_x[7];
   out_3534488348241865019[8] = -nom_x[8] + true_x[8];
   out_3534488348241865019[9] = -nom_x[9] + true_x[9];
   out_3534488348241865019[10] = -nom_x[10] + true_x[10];
   out_3534488348241865019[11] = -nom_x[11] + true_x[11];
   out_3534488348241865019[12] = -nom_x[12] + true_x[12];
   out_3534488348241865019[13] = -nom_x[13] + true_x[13];
   out_3534488348241865019[14] = -nom_x[14] + true_x[14];
   out_3534488348241865019[15] = -nom_x[15] + true_x[15];
   out_3534488348241865019[16] = -nom_x[16] + true_x[16];
   out_3534488348241865019[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5384152065241129084) {
   out_5384152065241129084[0] = 1.0;
   out_5384152065241129084[1] = 0.0;
   out_5384152065241129084[2] = 0.0;
   out_5384152065241129084[3] = 0.0;
   out_5384152065241129084[4] = 0.0;
   out_5384152065241129084[5] = 0.0;
   out_5384152065241129084[6] = 0.0;
   out_5384152065241129084[7] = 0.0;
   out_5384152065241129084[8] = 0.0;
   out_5384152065241129084[9] = 0.0;
   out_5384152065241129084[10] = 0.0;
   out_5384152065241129084[11] = 0.0;
   out_5384152065241129084[12] = 0.0;
   out_5384152065241129084[13] = 0.0;
   out_5384152065241129084[14] = 0.0;
   out_5384152065241129084[15] = 0.0;
   out_5384152065241129084[16] = 0.0;
   out_5384152065241129084[17] = 0.0;
   out_5384152065241129084[18] = 0.0;
   out_5384152065241129084[19] = 1.0;
   out_5384152065241129084[20] = 0.0;
   out_5384152065241129084[21] = 0.0;
   out_5384152065241129084[22] = 0.0;
   out_5384152065241129084[23] = 0.0;
   out_5384152065241129084[24] = 0.0;
   out_5384152065241129084[25] = 0.0;
   out_5384152065241129084[26] = 0.0;
   out_5384152065241129084[27] = 0.0;
   out_5384152065241129084[28] = 0.0;
   out_5384152065241129084[29] = 0.0;
   out_5384152065241129084[30] = 0.0;
   out_5384152065241129084[31] = 0.0;
   out_5384152065241129084[32] = 0.0;
   out_5384152065241129084[33] = 0.0;
   out_5384152065241129084[34] = 0.0;
   out_5384152065241129084[35] = 0.0;
   out_5384152065241129084[36] = 0.0;
   out_5384152065241129084[37] = 0.0;
   out_5384152065241129084[38] = 1.0;
   out_5384152065241129084[39] = 0.0;
   out_5384152065241129084[40] = 0.0;
   out_5384152065241129084[41] = 0.0;
   out_5384152065241129084[42] = 0.0;
   out_5384152065241129084[43] = 0.0;
   out_5384152065241129084[44] = 0.0;
   out_5384152065241129084[45] = 0.0;
   out_5384152065241129084[46] = 0.0;
   out_5384152065241129084[47] = 0.0;
   out_5384152065241129084[48] = 0.0;
   out_5384152065241129084[49] = 0.0;
   out_5384152065241129084[50] = 0.0;
   out_5384152065241129084[51] = 0.0;
   out_5384152065241129084[52] = 0.0;
   out_5384152065241129084[53] = 0.0;
   out_5384152065241129084[54] = 0.0;
   out_5384152065241129084[55] = 0.0;
   out_5384152065241129084[56] = 0.0;
   out_5384152065241129084[57] = 1.0;
   out_5384152065241129084[58] = 0.0;
   out_5384152065241129084[59] = 0.0;
   out_5384152065241129084[60] = 0.0;
   out_5384152065241129084[61] = 0.0;
   out_5384152065241129084[62] = 0.0;
   out_5384152065241129084[63] = 0.0;
   out_5384152065241129084[64] = 0.0;
   out_5384152065241129084[65] = 0.0;
   out_5384152065241129084[66] = 0.0;
   out_5384152065241129084[67] = 0.0;
   out_5384152065241129084[68] = 0.0;
   out_5384152065241129084[69] = 0.0;
   out_5384152065241129084[70] = 0.0;
   out_5384152065241129084[71] = 0.0;
   out_5384152065241129084[72] = 0.0;
   out_5384152065241129084[73] = 0.0;
   out_5384152065241129084[74] = 0.0;
   out_5384152065241129084[75] = 0.0;
   out_5384152065241129084[76] = 1.0;
   out_5384152065241129084[77] = 0.0;
   out_5384152065241129084[78] = 0.0;
   out_5384152065241129084[79] = 0.0;
   out_5384152065241129084[80] = 0.0;
   out_5384152065241129084[81] = 0.0;
   out_5384152065241129084[82] = 0.0;
   out_5384152065241129084[83] = 0.0;
   out_5384152065241129084[84] = 0.0;
   out_5384152065241129084[85] = 0.0;
   out_5384152065241129084[86] = 0.0;
   out_5384152065241129084[87] = 0.0;
   out_5384152065241129084[88] = 0.0;
   out_5384152065241129084[89] = 0.0;
   out_5384152065241129084[90] = 0.0;
   out_5384152065241129084[91] = 0.0;
   out_5384152065241129084[92] = 0.0;
   out_5384152065241129084[93] = 0.0;
   out_5384152065241129084[94] = 0.0;
   out_5384152065241129084[95] = 1.0;
   out_5384152065241129084[96] = 0.0;
   out_5384152065241129084[97] = 0.0;
   out_5384152065241129084[98] = 0.0;
   out_5384152065241129084[99] = 0.0;
   out_5384152065241129084[100] = 0.0;
   out_5384152065241129084[101] = 0.0;
   out_5384152065241129084[102] = 0.0;
   out_5384152065241129084[103] = 0.0;
   out_5384152065241129084[104] = 0.0;
   out_5384152065241129084[105] = 0.0;
   out_5384152065241129084[106] = 0.0;
   out_5384152065241129084[107] = 0.0;
   out_5384152065241129084[108] = 0.0;
   out_5384152065241129084[109] = 0.0;
   out_5384152065241129084[110] = 0.0;
   out_5384152065241129084[111] = 0.0;
   out_5384152065241129084[112] = 0.0;
   out_5384152065241129084[113] = 0.0;
   out_5384152065241129084[114] = 1.0;
   out_5384152065241129084[115] = 0.0;
   out_5384152065241129084[116] = 0.0;
   out_5384152065241129084[117] = 0.0;
   out_5384152065241129084[118] = 0.0;
   out_5384152065241129084[119] = 0.0;
   out_5384152065241129084[120] = 0.0;
   out_5384152065241129084[121] = 0.0;
   out_5384152065241129084[122] = 0.0;
   out_5384152065241129084[123] = 0.0;
   out_5384152065241129084[124] = 0.0;
   out_5384152065241129084[125] = 0.0;
   out_5384152065241129084[126] = 0.0;
   out_5384152065241129084[127] = 0.0;
   out_5384152065241129084[128] = 0.0;
   out_5384152065241129084[129] = 0.0;
   out_5384152065241129084[130] = 0.0;
   out_5384152065241129084[131] = 0.0;
   out_5384152065241129084[132] = 0.0;
   out_5384152065241129084[133] = 1.0;
   out_5384152065241129084[134] = 0.0;
   out_5384152065241129084[135] = 0.0;
   out_5384152065241129084[136] = 0.0;
   out_5384152065241129084[137] = 0.0;
   out_5384152065241129084[138] = 0.0;
   out_5384152065241129084[139] = 0.0;
   out_5384152065241129084[140] = 0.0;
   out_5384152065241129084[141] = 0.0;
   out_5384152065241129084[142] = 0.0;
   out_5384152065241129084[143] = 0.0;
   out_5384152065241129084[144] = 0.0;
   out_5384152065241129084[145] = 0.0;
   out_5384152065241129084[146] = 0.0;
   out_5384152065241129084[147] = 0.0;
   out_5384152065241129084[148] = 0.0;
   out_5384152065241129084[149] = 0.0;
   out_5384152065241129084[150] = 0.0;
   out_5384152065241129084[151] = 0.0;
   out_5384152065241129084[152] = 1.0;
   out_5384152065241129084[153] = 0.0;
   out_5384152065241129084[154] = 0.0;
   out_5384152065241129084[155] = 0.0;
   out_5384152065241129084[156] = 0.0;
   out_5384152065241129084[157] = 0.0;
   out_5384152065241129084[158] = 0.0;
   out_5384152065241129084[159] = 0.0;
   out_5384152065241129084[160] = 0.0;
   out_5384152065241129084[161] = 0.0;
   out_5384152065241129084[162] = 0.0;
   out_5384152065241129084[163] = 0.0;
   out_5384152065241129084[164] = 0.0;
   out_5384152065241129084[165] = 0.0;
   out_5384152065241129084[166] = 0.0;
   out_5384152065241129084[167] = 0.0;
   out_5384152065241129084[168] = 0.0;
   out_5384152065241129084[169] = 0.0;
   out_5384152065241129084[170] = 0.0;
   out_5384152065241129084[171] = 1.0;
   out_5384152065241129084[172] = 0.0;
   out_5384152065241129084[173] = 0.0;
   out_5384152065241129084[174] = 0.0;
   out_5384152065241129084[175] = 0.0;
   out_5384152065241129084[176] = 0.0;
   out_5384152065241129084[177] = 0.0;
   out_5384152065241129084[178] = 0.0;
   out_5384152065241129084[179] = 0.0;
   out_5384152065241129084[180] = 0.0;
   out_5384152065241129084[181] = 0.0;
   out_5384152065241129084[182] = 0.0;
   out_5384152065241129084[183] = 0.0;
   out_5384152065241129084[184] = 0.0;
   out_5384152065241129084[185] = 0.0;
   out_5384152065241129084[186] = 0.0;
   out_5384152065241129084[187] = 0.0;
   out_5384152065241129084[188] = 0.0;
   out_5384152065241129084[189] = 0.0;
   out_5384152065241129084[190] = 1.0;
   out_5384152065241129084[191] = 0.0;
   out_5384152065241129084[192] = 0.0;
   out_5384152065241129084[193] = 0.0;
   out_5384152065241129084[194] = 0.0;
   out_5384152065241129084[195] = 0.0;
   out_5384152065241129084[196] = 0.0;
   out_5384152065241129084[197] = 0.0;
   out_5384152065241129084[198] = 0.0;
   out_5384152065241129084[199] = 0.0;
   out_5384152065241129084[200] = 0.0;
   out_5384152065241129084[201] = 0.0;
   out_5384152065241129084[202] = 0.0;
   out_5384152065241129084[203] = 0.0;
   out_5384152065241129084[204] = 0.0;
   out_5384152065241129084[205] = 0.0;
   out_5384152065241129084[206] = 0.0;
   out_5384152065241129084[207] = 0.0;
   out_5384152065241129084[208] = 0.0;
   out_5384152065241129084[209] = 1.0;
   out_5384152065241129084[210] = 0.0;
   out_5384152065241129084[211] = 0.0;
   out_5384152065241129084[212] = 0.0;
   out_5384152065241129084[213] = 0.0;
   out_5384152065241129084[214] = 0.0;
   out_5384152065241129084[215] = 0.0;
   out_5384152065241129084[216] = 0.0;
   out_5384152065241129084[217] = 0.0;
   out_5384152065241129084[218] = 0.0;
   out_5384152065241129084[219] = 0.0;
   out_5384152065241129084[220] = 0.0;
   out_5384152065241129084[221] = 0.0;
   out_5384152065241129084[222] = 0.0;
   out_5384152065241129084[223] = 0.0;
   out_5384152065241129084[224] = 0.0;
   out_5384152065241129084[225] = 0.0;
   out_5384152065241129084[226] = 0.0;
   out_5384152065241129084[227] = 0.0;
   out_5384152065241129084[228] = 1.0;
   out_5384152065241129084[229] = 0.0;
   out_5384152065241129084[230] = 0.0;
   out_5384152065241129084[231] = 0.0;
   out_5384152065241129084[232] = 0.0;
   out_5384152065241129084[233] = 0.0;
   out_5384152065241129084[234] = 0.0;
   out_5384152065241129084[235] = 0.0;
   out_5384152065241129084[236] = 0.0;
   out_5384152065241129084[237] = 0.0;
   out_5384152065241129084[238] = 0.0;
   out_5384152065241129084[239] = 0.0;
   out_5384152065241129084[240] = 0.0;
   out_5384152065241129084[241] = 0.0;
   out_5384152065241129084[242] = 0.0;
   out_5384152065241129084[243] = 0.0;
   out_5384152065241129084[244] = 0.0;
   out_5384152065241129084[245] = 0.0;
   out_5384152065241129084[246] = 0.0;
   out_5384152065241129084[247] = 1.0;
   out_5384152065241129084[248] = 0.0;
   out_5384152065241129084[249] = 0.0;
   out_5384152065241129084[250] = 0.0;
   out_5384152065241129084[251] = 0.0;
   out_5384152065241129084[252] = 0.0;
   out_5384152065241129084[253] = 0.0;
   out_5384152065241129084[254] = 0.0;
   out_5384152065241129084[255] = 0.0;
   out_5384152065241129084[256] = 0.0;
   out_5384152065241129084[257] = 0.0;
   out_5384152065241129084[258] = 0.0;
   out_5384152065241129084[259] = 0.0;
   out_5384152065241129084[260] = 0.0;
   out_5384152065241129084[261] = 0.0;
   out_5384152065241129084[262] = 0.0;
   out_5384152065241129084[263] = 0.0;
   out_5384152065241129084[264] = 0.0;
   out_5384152065241129084[265] = 0.0;
   out_5384152065241129084[266] = 1.0;
   out_5384152065241129084[267] = 0.0;
   out_5384152065241129084[268] = 0.0;
   out_5384152065241129084[269] = 0.0;
   out_5384152065241129084[270] = 0.0;
   out_5384152065241129084[271] = 0.0;
   out_5384152065241129084[272] = 0.0;
   out_5384152065241129084[273] = 0.0;
   out_5384152065241129084[274] = 0.0;
   out_5384152065241129084[275] = 0.0;
   out_5384152065241129084[276] = 0.0;
   out_5384152065241129084[277] = 0.0;
   out_5384152065241129084[278] = 0.0;
   out_5384152065241129084[279] = 0.0;
   out_5384152065241129084[280] = 0.0;
   out_5384152065241129084[281] = 0.0;
   out_5384152065241129084[282] = 0.0;
   out_5384152065241129084[283] = 0.0;
   out_5384152065241129084[284] = 0.0;
   out_5384152065241129084[285] = 1.0;
   out_5384152065241129084[286] = 0.0;
   out_5384152065241129084[287] = 0.0;
   out_5384152065241129084[288] = 0.0;
   out_5384152065241129084[289] = 0.0;
   out_5384152065241129084[290] = 0.0;
   out_5384152065241129084[291] = 0.0;
   out_5384152065241129084[292] = 0.0;
   out_5384152065241129084[293] = 0.0;
   out_5384152065241129084[294] = 0.0;
   out_5384152065241129084[295] = 0.0;
   out_5384152065241129084[296] = 0.0;
   out_5384152065241129084[297] = 0.0;
   out_5384152065241129084[298] = 0.0;
   out_5384152065241129084[299] = 0.0;
   out_5384152065241129084[300] = 0.0;
   out_5384152065241129084[301] = 0.0;
   out_5384152065241129084[302] = 0.0;
   out_5384152065241129084[303] = 0.0;
   out_5384152065241129084[304] = 1.0;
   out_5384152065241129084[305] = 0.0;
   out_5384152065241129084[306] = 0.0;
   out_5384152065241129084[307] = 0.0;
   out_5384152065241129084[308] = 0.0;
   out_5384152065241129084[309] = 0.0;
   out_5384152065241129084[310] = 0.0;
   out_5384152065241129084[311] = 0.0;
   out_5384152065241129084[312] = 0.0;
   out_5384152065241129084[313] = 0.0;
   out_5384152065241129084[314] = 0.0;
   out_5384152065241129084[315] = 0.0;
   out_5384152065241129084[316] = 0.0;
   out_5384152065241129084[317] = 0.0;
   out_5384152065241129084[318] = 0.0;
   out_5384152065241129084[319] = 0.0;
   out_5384152065241129084[320] = 0.0;
   out_5384152065241129084[321] = 0.0;
   out_5384152065241129084[322] = 0.0;
   out_5384152065241129084[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1966290028419981018) {
   out_1966290028419981018[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1966290028419981018[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1966290028419981018[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1966290028419981018[3] = dt*state[12] + state[3];
   out_1966290028419981018[4] = dt*state[13] + state[4];
   out_1966290028419981018[5] = dt*state[14] + state[5];
   out_1966290028419981018[6] = state[6];
   out_1966290028419981018[7] = state[7];
   out_1966290028419981018[8] = state[8];
   out_1966290028419981018[9] = state[9];
   out_1966290028419981018[10] = state[10];
   out_1966290028419981018[11] = state[11];
   out_1966290028419981018[12] = state[12];
   out_1966290028419981018[13] = state[13];
   out_1966290028419981018[14] = state[14];
   out_1966290028419981018[15] = state[15];
   out_1966290028419981018[16] = state[16];
   out_1966290028419981018[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8500986371107107872) {
   out_8500986371107107872[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8500986371107107872[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8500986371107107872[2] = 0;
   out_8500986371107107872[3] = 0;
   out_8500986371107107872[4] = 0;
   out_8500986371107107872[5] = 0;
   out_8500986371107107872[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8500986371107107872[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8500986371107107872[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8500986371107107872[9] = 0;
   out_8500986371107107872[10] = 0;
   out_8500986371107107872[11] = 0;
   out_8500986371107107872[12] = 0;
   out_8500986371107107872[13] = 0;
   out_8500986371107107872[14] = 0;
   out_8500986371107107872[15] = 0;
   out_8500986371107107872[16] = 0;
   out_8500986371107107872[17] = 0;
   out_8500986371107107872[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8500986371107107872[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8500986371107107872[20] = 0;
   out_8500986371107107872[21] = 0;
   out_8500986371107107872[22] = 0;
   out_8500986371107107872[23] = 0;
   out_8500986371107107872[24] = 0;
   out_8500986371107107872[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8500986371107107872[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8500986371107107872[27] = 0;
   out_8500986371107107872[28] = 0;
   out_8500986371107107872[29] = 0;
   out_8500986371107107872[30] = 0;
   out_8500986371107107872[31] = 0;
   out_8500986371107107872[32] = 0;
   out_8500986371107107872[33] = 0;
   out_8500986371107107872[34] = 0;
   out_8500986371107107872[35] = 0;
   out_8500986371107107872[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8500986371107107872[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8500986371107107872[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8500986371107107872[39] = 0;
   out_8500986371107107872[40] = 0;
   out_8500986371107107872[41] = 0;
   out_8500986371107107872[42] = 0;
   out_8500986371107107872[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8500986371107107872[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8500986371107107872[45] = 0;
   out_8500986371107107872[46] = 0;
   out_8500986371107107872[47] = 0;
   out_8500986371107107872[48] = 0;
   out_8500986371107107872[49] = 0;
   out_8500986371107107872[50] = 0;
   out_8500986371107107872[51] = 0;
   out_8500986371107107872[52] = 0;
   out_8500986371107107872[53] = 0;
   out_8500986371107107872[54] = 0;
   out_8500986371107107872[55] = 0;
   out_8500986371107107872[56] = 0;
   out_8500986371107107872[57] = 1;
   out_8500986371107107872[58] = 0;
   out_8500986371107107872[59] = 0;
   out_8500986371107107872[60] = 0;
   out_8500986371107107872[61] = 0;
   out_8500986371107107872[62] = 0;
   out_8500986371107107872[63] = 0;
   out_8500986371107107872[64] = 0;
   out_8500986371107107872[65] = 0;
   out_8500986371107107872[66] = dt;
   out_8500986371107107872[67] = 0;
   out_8500986371107107872[68] = 0;
   out_8500986371107107872[69] = 0;
   out_8500986371107107872[70] = 0;
   out_8500986371107107872[71] = 0;
   out_8500986371107107872[72] = 0;
   out_8500986371107107872[73] = 0;
   out_8500986371107107872[74] = 0;
   out_8500986371107107872[75] = 0;
   out_8500986371107107872[76] = 1;
   out_8500986371107107872[77] = 0;
   out_8500986371107107872[78] = 0;
   out_8500986371107107872[79] = 0;
   out_8500986371107107872[80] = 0;
   out_8500986371107107872[81] = 0;
   out_8500986371107107872[82] = 0;
   out_8500986371107107872[83] = 0;
   out_8500986371107107872[84] = 0;
   out_8500986371107107872[85] = dt;
   out_8500986371107107872[86] = 0;
   out_8500986371107107872[87] = 0;
   out_8500986371107107872[88] = 0;
   out_8500986371107107872[89] = 0;
   out_8500986371107107872[90] = 0;
   out_8500986371107107872[91] = 0;
   out_8500986371107107872[92] = 0;
   out_8500986371107107872[93] = 0;
   out_8500986371107107872[94] = 0;
   out_8500986371107107872[95] = 1;
   out_8500986371107107872[96] = 0;
   out_8500986371107107872[97] = 0;
   out_8500986371107107872[98] = 0;
   out_8500986371107107872[99] = 0;
   out_8500986371107107872[100] = 0;
   out_8500986371107107872[101] = 0;
   out_8500986371107107872[102] = 0;
   out_8500986371107107872[103] = 0;
   out_8500986371107107872[104] = dt;
   out_8500986371107107872[105] = 0;
   out_8500986371107107872[106] = 0;
   out_8500986371107107872[107] = 0;
   out_8500986371107107872[108] = 0;
   out_8500986371107107872[109] = 0;
   out_8500986371107107872[110] = 0;
   out_8500986371107107872[111] = 0;
   out_8500986371107107872[112] = 0;
   out_8500986371107107872[113] = 0;
   out_8500986371107107872[114] = 1;
   out_8500986371107107872[115] = 0;
   out_8500986371107107872[116] = 0;
   out_8500986371107107872[117] = 0;
   out_8500986371107107872[118] = 0;
   out_8500986371107107872[119] = 0;
   out_8500986371107107872[120] = 0;
   out_8500986371107107872[121] = 0;
   out_8500986371107107872[122] = 0;
   out_8500986371107107872[123] = 0;
   out_8500986371107107872[124] = 0;
   out_8500986371107107872[125] = 0;
   out_8500986371107107872[126] = 0;
   out_8500986371107107872[127] = 0;
   out_8500986371107107872[128] = 0;
   out_8500986371107107872[129] = 0;
   out_8500986371107107872[130] = 0;
   out_8500986371107107872[131] = 0;
   out_8500986371107107872[132] = 0;
   out_8500986371107107872[133] = 1;
   out_8500986371107107872[134] = 0;
   out_8500986371107107872[135] = 0;
   out_8500986371107107872[136] = 0;
   out_8500986371107107872[137] = 0;
   out_8500986371107107872[138] = 0;
   out_8500986371107107872[139] = 0;
   out_8500986371107107872[140] = 0;
   out_8500986371107107872[141] = 0;
   out_8500986371107107872[142] = 0;
   out_8500986371107107872[143] = 0;
   out_8500986371107107872[144] = 0;
   out_8500986371107107872[145] = 0;
   out_8500986371107107872[146] = 0;
   out_8500986371107107872[147] = 0;
   out_8500986371107107872[148] = 0;
   out_8500986371107107872[149] = 0;
   out_8500986371107107872[150] = 0;
   out_8500986371107107872[151] = 0;
   out_8500986371107107872[152] = 1;
   out_8500986371107107872[153] = 0;
   out_8500986371107107872[154] = 0;
   out_8500986371107107872[155] = 0;
   out_8500986371107107872[156] = 0;
   out_8500986371107107872[157] = 0;
   out_8500986371107107872[158] = 0;
   out_8500986371107107872[159] = 0;
   out_8500986371107107872[160] = 0;
   out_8500986371107107872[161] = 0;
   out_8500986371107107872[162] = 0;
   out_8500986371107107872[163] = 0;
   out_8500986371107107872[164] = 0;
   out_8500986371107107872[165] = 0;
   out_8500986371107107872[166] = 0;
   out_8500986371107107872[167] = 0;
   out_8500986371107107872[168] = 0;
   out_8500986371107107872[169] = 0;
   out_8500986371107107872[170] = 0;
   out_8500986371107107872[171] = 1;
   out_8500986371107107872[172] = 0;
   out_8500986371107107872[173] = 0;
   out_8500986371107107872[174] = 0;
   out_8500986371107107872[175] = 0;
   out_8500986371107107872[176] = 0;
   out_8500986371107107872[177] = 0;
   out_8500986371107107872[178] = 0;
   out_8500986371107107872[179] = 0;
   out_8500986371107107872[180] = 0;
   out_8500986371107107872[181] = 0;
   out_8500986371107107872[182] = 0;
   out_8500986371107107872[183] = 0;
   out_8500986371107107872[184] = 0;
   out_8500986371107107872[185] = 0;
   out_8500986371107107872[186] = 0;
   out_8500986371107107872[187] = 0;
   out_8500986371107107872[188] = 0;
   out_8500986371107107872[189] = 0;
   out_8500986371107107872[190] = 1;
   out_8500986371107107872[191] = 0;
   out_8500986371107107872[192] = 0;
   out_8500986371107107872[193] = 0;
   out_8500986371107107872[194] = 0;
   out_8500986371107107872[195] = 0;
   out_8500986371107107872[196] = 0;
   out_8500986371107107872[197] = 0;
   out_8500986371107107872[198] = 0;
   out_8500986371107107872[199] = 0;
   out_8500986371107107872[200] = 0;
   out_8500986371107107872[201] = 0;
   out_8500986371107107872[202] = 0;
   out_8500986371107107872[203] = 0;
   out_8500986371107107872[204] = 0;
   out_8500986371107107872[205] = 0;
   out_8500986371107107872[206] = 0;
   out_8500986371107107872[207] = 0;
   out_8500986371107107872[208] = 0;
   out_8500986371107107872[209] = 1;
   out_8500986371107107872[210] = 0;
   out_8500986371107107872[211] = 0;
   out_8500986371107107872[212] = 0;
   out_8500986371107107872[213] = 0;
   out_8500986371107107872[214] = 0;
   out_8500986371107107872[215] = 0;
   out_8500986371107107872[216] = 0;
   out_8500986371107107872[217] = 0;
   out_8500986371107107872[218] = 0;
   out_8500986371107107872[219] = 0;
   out_8500986371107107872[220] = 0;
   out_8500986371107107872[221] = 0;
   out_8500986371107107872[222] = 0;
   out_8500986371107107872[223] = 0;
   out_8500986371107107872[224] = 0;
   out_8500986371107107872[225] = 0;
   out_8500986371107107872[226] = 0;
   out_8500986371107107872[227] = 0;
   out_8500986371107107872[228] = 1;
   out_8500986371107107872[229] = 0;
   out_8500986371107107872[230] = 0;
   out_8500986371107107872[231] = 0;
   out_8500986371107107872[232] = 0;
   out_8500986371107107872[233] = 0;
   out_8500986371107107872[234] = 0;
   out_8500986371107107872[235] = 0;
   out_8500986371107107872[236] = 0;
   out_8500986371107107872[237] = 0;
   out_8500986371107107872[238] = 0;
   out_8500986371107107872[239] = 0;
   out_8500986371107107872[240] = 0;
   out_8500986371107107872[241] = 0;
   out_8500986371107107872[242] = 0;
   out_8500986371107107872[243] = 0;
   out_8500986371107107872[244] = 0;
   out_8500986371107107872[245] = 0;
   out_8500986371107107872[246] = 0;
   out_8500986371107107872[247] = 1;
   out_8500986371107107872[248] = 0;
   out_8500986371107107872[249] = 0;
   out_8500986371107107872[250] = 0;
   out_8500986371107107872[251] = 0;
   out_8500986371107107872[252] = 0;
   out_8500986371107107872[253] = 0;
   out_8500986371107107872[254] = 0;
   out_8500986371107107872[255] = 0;
   out_8500986371107107872[256] = 0;
   out_8500986371107107872[257] = 0;
   out_8500986371107107872[258] = 0;
   out_8500986371107107872[259] = 0;
   out_8500986371107107872[260] = 0;
   out_8500986371107107872[261] = 0;
   out_8500986371107107872[262] = 0;
   out_8500986371107107872[263] = 0;
   out_8500986371107107872[264] = 0;
   out_8500986371107107872[265] = 0;
   out_8500986371107107872[266] = 1;
   out_8500986371107107872[267] = 0;
   out_8500986371107107872[268] = 0;
   out_8500986371107107872[269] = 0;
   out_8500986371107107872[270] = 0;
   out_8500986371107107872[271] = 0;
   out_8500986371107107872[272] = 0;
   out_8500986371107107872[273] = 0;
   out_8500986371107107872[274] = 0;
   out_8500986371107107872[275] = 0;
   out_8500986371107107872[276] = 0;
   out_8500986371107107872[277] = 0;
   out_8500986371107107872[278] = 0;
   out_8500986371107107872[279] = 0;
   out_8500986371107107872[280] = 0;
   out_8500986371107107872[281] = 0;
   out_8500986371107107872[282] = 0;
   out_8500986371107107872[283] = 0;
   out_8500986371107107872[284] = 0;
   out_8500986371107107872[285] = 1;
   out_8500986371107107872[286] = 0;
   out_8500986371107107872[287] = 0;
   out_8500986371107107872[288] = 0;
   out_8500986371107107872[289] = 0;
   out_8500986371107107872[290] = 0;
   out_8500986371107107872[291] = 0;
   out_8500986371107107872[292] = 0;
   out_8500986371107107872[293] = 0;
   out_8500986371107107872[294] = 0;
   out_8500986371107107872[295] = 0;
   out_8500986371107107872[296] = 0;
   out_8500986371107107872[297] = 0;
   out_8500986371107107872[298] = 0;
   out_8500986371107107872[299] = 0;
   out_8500986371107107872[300] = 0;
   out_8500986371107107872[301] = 0;
   out_8500986371107107872[302] = 0;
   out_8500986371107107872[303] = 0;
   out_8500986371107107872[304] = 1;
   out_8500986371107107872[305] = 0;
   out_8500986371107107872[306] = 0;
   out_8500986371107107872[307] = 0;
   out_8500986371107107872[308] = 0;
   out_8500986371107107872[309] = 0;
   out_8500986371107107872[310] = 0;
   out_8500986371107107872[311] = 0;
   out_8500986371107107872[312] = 0;
   out_8500986371107107872[313] = 0;
   out_8500986371107107872[314] = 0;
   out_8500986371107107872[315] = 0;
   out_8500986371107107872[316] = 0;
   out_8500986371107107872[317] = 0;
   out_8500986371107107872[318] = 0;
   out_8500986371107107872[319] = 0;
   out_8500986371107107872[320] = 0;
   out_8500986371107107872[321] = 0;
   out_8500986371107107872[322] = 0;
   out_8500986371107107872[323] = 1;
}
void h_4(double *state, double *unused, double *out_5400718070291809963) {
   out_5400718070291809963[0] = state[6] + state[9];
   out_5400718070291809963[1] = state[7] + state[10];
   out_5400718070291809963[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_9155959275085036656) {
   out_9155959275085036656[0] = 0;
   out_9155959275085036656[1] = 0;
   out_9155959275085036656[2] = 0;
   out_9155959275085036656[3] = 0;
   out_9155959275085036656[4] = 0;
   out_9155959275085036656[5] = 0;
   out_9155959275085036656[6] = 1;
   out_9155959275085036656[7] = 0;
   out_9155959275085036656[8] = 0;
   out_9155959275085036656[9] = 1;
   out_9155959275085036656[10] = 0;
   out_9155959275085036656[11] = 0;
   out_9155959275085036656[12] = 0;
   out_9155959275085036656[13] = 0;
   out_9155959275085036656[14] = 0;
   out_9155959275085036656[15] = 0;
   out_9155959275085036656[16] = 0;
   out_9155959275085036656[17] = 0;
   out_9155959275085036656[18] = 0;
   out_9155959275085036656[19] = 0;
   out_9155959275085036656[20] = 0;
   out_9155959275085036656[21] = 0;
   out_9155959275085036656[22] = 0;
   out_9155959275085036656[23] = 0;
   out_9155959275085036656[24] = 0;
   out_9155959275085036656[25] = 1;
   out_9155959275085036656[26] = 0;
   out_9155959275085036656[27] = 0;
   out_9155959275085036656[28] = 1;
   out_9155959275085036656[29] = 0;
   out_9155959275085036656[30] = 0;
   out_9155959275085036656[31] = 0;
   out_9155959275085036656[32] = 0;
   out_9155959275085036656[33] = 0;
   out_9155959275085036656[34] = 0;
   out_9155959275085036656[35] = 0;
   out_9155959275085036656[36] = 0;
   out_9155959275085036656[37] = 0;
   out_9155959275085036656[38] = 0;
   out_9155959275085036656[39] = 0;
   out_9155959275085036656[40] = 0;
   out_9155959275085036656[41] = 0;
   out_9155959275085036656[42] = 0;
   out_9155959275085036656[43] = 0;
   out_9155959275085036656[44] = 1;
   out_9155959275085036656[45] = 0;
   out_9155959275085036656[46] = 0;
   out_9155959275085036656[47] = 1;
   out_9155959275085036656[48] = 0;
   out_9155959275085036656[49] = 0;
   out_9155959275085036656[50] = 0;
   out_9155959275085036656[51] = 0;
   out_9155959275085036656[52] = 0;
   out_9155959275085036656[53] = 0;
}
void h_10(double *state, double *unused, double *out_2963274022918519597) {
   out_2963274022918519597[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2963274022918519597[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2963274022918519597[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5627581855619872909) {
   out_5627581855619872909[0] = 0;
   out_5627581855619872909[1] = 9.8100000000000005*cos(state[1]);
   out_5627581855619872909[2] = 0;
   out_5627581855619872909[3] = 0;
   out_5627581855619872909[4] = -state[8];
   out_5627581855619872909[5] = state[7];
   out_5627581855619872909[6] = 0;
   out_5627581855619872909[7] = state[5];
   out_5627581855619872909[8] = -state[4];
   out_5627581855619872909[9] = 0;
   out_5627581855619872909[10] = 0;
   out_5627581855619872909[11] = 0;
   out_5627581855619872909[12] = 1;
   out_5627581855619872909[13] = 0;
   out_5627581855619872909[14] = 0;
   out_5627581855619872909[15] = 1;
   out_5627581855619872909[16] = 0;
   out_5627581855619872909[17] = 0;
   out_5627581855619872909[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5627581855619872909[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5627581855619872909[20] = 0;
   out_5627581855619872909[21] = state[8];
   out_5627581855619872909[22] = 0;
   out_5627581855619872909[23] = -state[6];
   out_5627581855619872909[24] = -state[5];
   out_5627581855619872909[25] = 0;
   out_5627581855619872909[26] = state[3];
   out_5627581855619872909[27] = 0;
   out_5627581855619872909[28] = 0;
   out_5627581855619872909[29] = 0;
   out_5627581855619872909[30] = 0;
   out_5627581855619872909[31] = 1;
   out_5627581855619872909[32] = 0;
   out_5627581855619872909[33] = 0;
   out_5627581855619872909[34] = 1;
   out_5627581855619872909[35] = 0;
   out_5627581855619872909[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5627581855619872909[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5627581855619872909[38] = 0;
   out_5627581855619872909[39] = -state[7];
   out_5627581855619872909[40] = state[6];
   out_5627581855619872909[41] = 0;
   out_5627581855619872909[42] = state[4];
   out_5627581855619872909[43] = -state[3];
   out_5627581855619872909[44] = 0;
   out_5627581855619872909[45] = 0;
   out_5627581855619872909[46] = 0;
   out_5627581855619872909[47] = 0;
   out_5627581855619872909[48] = 0;
   out_5627581855619872909[49] = 0;
   out_5627581855619872909[50] = 1;
   out_5627581855619872909[51] = 0;
   out_5627581855619872909[52] = 0;
   out_5627581855619872909[53] = 1;
}
void h_13(double *state, double *unused, double *out_6005618121794927988) {
   out_6005618121794927988[0] = state[3];
   out_6005618121794927988[1] = state[4];
   out_6005618121794927988[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1680153590307814031) {
   out_1680153590307814031[0] = 0;
   out_1680153590307814031[1] = 0;
   out_1680153590307814031[2] = 0;
   out_1680153590307814031[3] = 1;
   out_1680153590307814031[4] = 0;
   out_1680153590307814031[5] = 0;
   out_1680153590307814031[6] = 0;
   out_1680153590307814031[7] = 0;
   out_1680153590307814031[8] = 0;
   out_1680153590307814031[9] = 0;
   out_1680153590307814031[10] = 0;
   out_1680153590307814031[11] = 0;
   out_1680153590307814031[12] = 0;
   out_1680153590307814031[13] = 0;
   out_1680153590307814031[14] = 0;
   out_1680153590307814031[15] = 0;
   out_1680153590307814031[16] = 0;
   out_1680153590307814031[17] = 0;
   out_1680153590307814031[18] = 0;
   out_1680153590307814031[19] = 0;
   out_1680153590307814031[20] = 0;
   out_1680153590307814031[21] = 0;
   out_1680153590307814031[22] = 1;
   out_1680153590307814031[23] = 0;
   out_1680153590307814031[24] = 0;
   out_1680153590307814031[25] = 0;
   out_1680153590307814031[26] = 0;
   out_1680153590307814031[27] = 0;
   out_1680153590307814031[28] = 0;
   out_1680153590307814031[29] = 0;
   out_1680153590307814031[30] = 0;
   out_1680153590307814031[31] = 0;
   out_1680153590307814031[32] = 0;
   out_1680153590307814031[33] = 0;
   out_1680153590307814031[34] = 0;
   out_1680153590307814031[35] = 0;
   out_1680153590307814031[36] = 0;
   out_1680153590307814031[37] = 0;
   out_1680153590307814031[38] = 0;
   out_1680153590307814031[39] = 0;
   out_1680153590307814031[40] = 0;
   out_1680153590307814031[41] = 1;
   out_1680153590307814031[42] = 0;
   out_1680153590307814031[43] = 0;
   out_1680153590307814031[44] = 0;
   out_1680153590307814031[45] = 0;
   out_1680153590307814031[46] = 0;
   out_1680153590307814031[47] = 0;
   out_1680153590307814031[48] = 0;
   out_1680153590307814031[49] = 0;
   out_1680153590307814031[50] = 0;
   out_1680153590307814031[51] = 0;
   out_1680153590307814031[52] = 0;
   out_1680153590307814031[53] = 0;
}
void h_14(double *state, double *unused, double *out_5652518326669022365) {
   out_5652518326669022365[0] = state[6];
   out_5652518326669022365[1] = state[7];
   out_5652518326669022365[2] = state[8];
}
void H_14(double *state, double *unused, double *out_6073170842789664360) {
   out_6073170842789664360[0] = 0;
   out_6073170842789664360[1] = 0;
   out_6073170842789664360[2] = 0;
   out_6073170842789664360[3] = 0;
   out_6073170842789664360[4] = 0;
   out_6073170842789664360[5] = 0;
   out_6073170842789664360[6] = 1;
   out_6073170842789664360[7] = 0;
   out_6073170842789664360[8] = 0;
   out_6073170842789664360[9] = 0;
   out_6073170842789664360[10] = 0;
   out_6073170842789664360[11] = 0;
   out_6073170842789664360[12] = 0;
   out_6073170842789664360[13] = 0;
   out_6073170842789664360[14] = 0;
   out_6073170842789664360[15] = 0;
   out_6073170842789664360[16] = 0;
   out_6073170842789664360[17] = 0;
   out_6073170842789664360[18] = 0;
   out_6073170842789664360[19] = 0;
   out_6073170842789664360[20] = 0;
   out_6073170842789664360[21] = 0;
   out_6073170842789664360[22] = 0;
   out_6073170842789664360[23] = 0;
   out_6073170842789664360[24] = 0;
   out_6073170842789664360[25] = 1;
   out_6073170842789664360[26] = 0;
   out_6073170842789664360[27] = 0;
   out_6073170842789664360[28] = 0;
   out_6073170842789664360[29] = 0;
   out_6073170842789664360[30] = 0;
   out_6073170842789664360[31] = 0;
   out_6073170842789664360[32] = 0;
   out_6073170842789664360[33] = 0;
   out_6073170842789664360[34] = 0;
   out_6073170842789664360[35] = 0;
   out_6073170842789664360[36] = 0;
   out_6073170842789664360[37] = 0;
   out_6073170842789664360[38] = 0;
   out_6073170842789664360[39] = 0;
   out_6073170842789664360[40] = 0;
   out_6073170842789664360[41] = 0;
   out_6073170842789664360[42] = 0;
   out_6073170842789664360[43] = 0;
   out_6073170842789664360[44] = 1;
   out_6073170842789664360[45] = 0;
   out_6073170842789664360[46] = 0;
   out_6073170842789664360[47] = 0;
   out_6073170842789664360[48] = 0;
   out_6073170842789664360[49] = 0;
   out_6073170842789664360[50] = 0;
   out_6073170842789664360[51] = 0;
   out_6073170842789664360[52] = 0;
   out_6073170842789664360[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_616508134330162473) {
  err_fun(nom_x, delta_x, out_616508134330162473);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3534488348241865019) {
  inv_err_fun(nom_x, true_x, out_3534488348241865019);
}
void pose_H_mod_fun(double *state, double *out_5384152065241129084) {
  H_mod_fun(state, out_5384152065241129084);
}
void pose_f_fun(double *state, double dt, double *out_1966290028419981018) {
  f_fun(state,  dt, out_1966290028419981018);
}
void pose_F_fun(double *state, double dt, double *out_8500986371107107872) {
  F_fun(state,  dt, out_8500986371107107872);
}
void pose_h_4(double *state, double *unused, double *out_5400718070291809963) {
  h_4(state, unused, out_5400718070291809963);
}
void pose_H_4(double *state, double *unused, double *out_9155959275085036656) {
  H_4(state, unused, out_9155959275085036656);
}
void pose_h_10(double *state, double *unused, double *out_2963274022918519597) {
  h_10(state, unused, out_2963274022918519597);
}
void pose_H_10(double *state, double *unused, double *out_5627581855619872909) {
  H_10(state, unused, out_5627581855619872909);
}
void pose_h_13(double *state, double *unused, double *out_6005618121794927988) {
  h_13(state, unused, out_6005618121794927988);
}
void pose_H_13(double *state, double *unused, double *out_1680153590307814031) {
  H_13(state, unused, out_1680153590307814031);
}
void pose_h_14(double *state, double *unused, double *out_5652518326669022365) {
  h_14(state, unused, out_5652518326669022365);
}
void pose_H_14(double *state, double *unused, double *out_6073170842789664360) {
  H_14(state, unused, out_6073170842789664360);
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
