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
void err_fun(double *nom_x, double *delta_x, double *out_3926294361318359623) {
   out_3926294361318359623[0] = delta_x[0] + nom_x[0];
   out_3926294361318359623[1] = delta_x[1] + nom_x[1];
   out_3926294361318359623[2] = delta_x[2] + nom_x[2];
   out_3926294361318359623[3] = delta_x[3] + nom_x[3];
   out_3926294361318359623[4] = delta_x[4] + nom_x[4];
   out_3926294361318359623[5] = delta_x[5] + nom_x[5];
   out_3926294361318359623[6] = delta_x[6] + nom_x[6];
   out_3926294361318359623[7] = delta_x[7] + nom_x[7];
   out_3926294361318359623[8] = delta_x[8] + nom_x[8];
   out_3926294361318359623[9] = delta_x[9] + nom_x[9];
   out_3926294361318359623[10] = delta_x[10] + nom_x[10];
   out_3926294361318359623[11] = delta_x[11] + nom_x[11];
   out_3926294361318359623[12] = delta_x[12] + nom_x[12];
   out_3926294361318359623[13] = delta_x[13] + nom_x[13];
   out_3926294361318359623[14] = delta_x[14] + nom_x[14];
   out_3926294361318359623[15] = delta_x[15] + nom_x[15];
   out_3926294361318359623[16] = delta_x[16] + nom_x[16];
   out_3926294361318359623[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5231104082209692226) {
   out_5231104082209692226[0] = -nom_x[0] + true_x[0];
   out_5231104082209692226[1] = -nom_x[1] + true_x[1];
   out_5231104082209692226[2] = -nom_x[2] + true_x[2];
   out_5231104082209692226[3] = -nom_x[3] + true_x[3];
   out_5231104082209692226[4] = -nom_x[4] + true_x[4];
   out_5231104082209692226[5] = -nom_x[5] + true_x[5];
   out_5231104082209692226[6] = -nom_x[6] + true_x[6];
   out_5231104082209692226[7] = -nom_x[7] + true_x[7];
   out_5231104082209692226[8] = -nom_x[8] + true_x[8];
   out_5231104082209692226[9] = -nom_x[9] + true_x[9];
   out_5231104082209692226[10] = -nom_x[10] + true_x[10];
   out_5231104082209692226[11] = -nom_x[11] + true_x[11];
   out_5231104082209692226[12] = -nom_x[12] + true_x[12];
   out_5231104082209692226[13] = -nom_x[13] + true_x[13];
   out_5231104082209692226[14] = -nom_x[14] + true_x[14];
   out_5231104082209692226[15] = -nom_x[15] + true_x[15];
   out_5231104082209692226[16] = -nom_x[16] + true_x[16];
   out_5231104082209692226[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5646756432622182646) {
   out_5646756432622182646[0] = 1.0;
   out_5646756432622182646[1] = 0.0;
   out_5646756432622182646[2] = 0.0;
   out_5646756432622182646[3] = 0.0;
   out_5646756432622182646[4] = 0.0;
   out_5646756432622182646[5] = 0.0;
   out_5646756432622182646[6] = 0.0;
   out_5646756432622182646[7] = 0.0;
   out_5646756432622182646[8] = 0.0;
   out_5646756432622182646[9] = 0.0;
   out_5646756432622182646[10] = 0.0;
   out_5646756432622182646[11] = 0.0;
   out_5646756432622182646[12] = 0.0;
   out_5646756432622182646[13] = 0.0;
   out_5646756432622182646[14] = 0.0;
   out_5646756432622182646[15] = 0.0;
   out_5646756432622182646[16] = 0.0;
   out_5646756432622182646[17] = 0.0;
   out_5646756432622182646[18] = 0.0;
   out_5646756432622182646[19] = 1.0;
   out_5646756432622182646[20] = 0.0;
   out_5646756432622182646[21] = 0.0;
   out_5646756432622182646[22] = 0.0;
   out_5646756432622182646[23] = 0.0;
   out_5646756432622182646[24] = 0.0;
   out_5646756432622182646[25] = 0.0;
   out_5646756432622182646[26] = 0.0;
   out_5646756432622182646[27] = 0.0;
   out_5646756432622182646[28] = 0.0;
   out_5646756432622182646[29] = 0.0;
   out_5646756432622182646[30] = 0.0;
   out_5646756432622182646[31] = 0.0;
   out_5646756432622182646[32] = 0.0;
   out_5646756432622182646[33] = 0.0;
   out_5646756432622182646[34] = 0.0;
   out_5646756432622182646[35] = 0.0;
   out_5646756432622182646[36] = 0.0;
   out_5646756432622182646[37] = 0.0;
   out_5646756432622182646[38] = 1.0;
   out_5646756432622182646[39] = 0.0;
   out_5646756432622182646[40] = 0.0;
   out_5646756432622182646[41] = 0.0;
   out_5646756432622182646[42] = 0.0;
   out_5646756432622182646[43] = 0.0;
   out_5646756432622182646[44] = 0.0;
   out_5646756432622182646[45] = 0.0;
   out_5646756432622182646[46] = 0.0;
   out_5646756432622182646[47] = 0.0;
   out_5646756432622182646[48] = 0.0;
   out_5646756432622182646[49] = 0.0;
   out_5646756432622182646[50] = 0.0;
   out_5646756432622182646[51] = 0.0;
   out_5646756432622182646[52] = 0.0;
   out_5646756432622182646[53] = 0.0;
   out_5646756432622182646[54] = 0.0;
   out_5646756432622182646[55] = 0.0;
   out_5646756432622182646[56] = 0.0;
   out_5646756432622182646[57] = 1.0;
   out_5646756432622182646[58] = 0.0;
   out_5646756432622182646[59] = 0.0;
   out_5646756432622182646[60] = 0.0;
   out_5646756432622182646[61] = 0.0;
   out_5646756432622182646[62] = 0.0;
   out_5646756432622182646[63] = 0.0;
   out_5646756432622182646[64] = 0.0;
   out_5646756432622182646[65] = 0.0;
   out_5646756432622182646[66] = 0.0;
   out_5646756432622182646[67] = 0.0;
   out_5646756432622182646[68] = 0.0;
   out_5646756432622182646[69] = 0.0;
   out_5646756432622182646[70] = 0.0;
   out_5646756432622182646[71] = 0.0;
   out_5646756432622182646[72] = 0.0;
   out_5646756432622182646[73] = 0.0;
   out_5646756432622182646[74] = 0.0;
   out_5646756432622182646[75] = 0.0;
   out_5646756432622182646[76] = 1.0;
   out_5646756432622182646[77] = 0.0;
   out_5646756432622182646[78] = 0.0;
   out_5646756432622182646[79] = 0.0;
   out_5646756432622182646[80] = 0.0;
   out_5646756432622182646[81] = 0.0;
   out_5646756432622182646[82] = 0.0;
   out_5646756432622182646[83] = 0.0;
   out_5646756432622182646[84] = 0.0;
   out_5646756432622182646[85] = 0.0;
   out_5646756432622182646[86] = 0.0;
   out_5646756432622182646[87] = 0.0;
   out_5646756432622182646[88] = 0.0;
   out_5646756432622182646[89] = 0.0;
   out_5646756432622182646[90] = 0.0;
   out_5646756432622182646[91] = 0.0;
   out_5646756432622182646[92] = 0.0;
   out_5646756432622182646[93] = 0.0;
   out_5646756432622182646[94] = 0.0;
   out_5646756432622182646[95] = 1.0;
   out_5646756432622182646[96] = 0.0;
   out_5646756432622182646[97] = 0.0;
   out_5646756432622182646[98] = 0.0;
   out_5646756432622182646[99] = 0.0;
   out_5646756432622182646[100] = 0.0;
   out_5646756432622182646[101] = 0.0;
   out_5646756432622182646[102] = 0.0;
   out_5646756432622182646[103] = 0.0;
   out_5646756432622182646[104] = 0.0;
   out_5646756432622182646[105] = 0.0;
   out_5646756432622182646[106] = 0.0;
   out_5646756432622182646[107] = 0.0;
   out_5646756432622182646[108] = 0.0;
   out_5646756432622182646[109] = 0.0;
   out_5646756432622182646[110] = 0.0;
   out_5646756432622182646[111] = 0.0;
   out_5646756432622182646[112] = 0.0;
   out_5646756432622182646[113] = 0.0;
   out_5646756432622182646[114] = 1.0;
   out_5646756432622182646[115] = 0.0;
   out_5646756432622182646[116] = 0.0;
   out_5646756432622182646[117] = 0.0;
   out_5646756432622182646[118] = 0.0;
   out_5646756432622182646[119] = 0.0;
   out_5646756432622182646[120] = 0.0;
   out_5646756432622182646[121] = 0.0;
   out_5646756432622182646[122] = 0.0;
   out_5646756432622182646[123] = 0.0;
   out_5646756432622182646[124] = 0.0;
   out_5646756432622182646[125] = 0.0;
   out_5646756432622182646[126] = 0.0;
   out_5646756432622182646[127] = 0.0;
   out_5646756432622182646[128] = 0.0;
   out_5646756432622182646[129] = 0.0;
   out_5646756432622182646[130] = 0.0;
   out_5646756432622182646[131] = 0.0;
   out_5646756432622182646[132] = 0.0;
   out_5646756432622182646[133] = 1.0;
   out_5646756432622182646[134] = 0.0;
   out_5646756432622182646[135] = 0.0;
   out_5646756432622182646[136] = 0.0;
   out_5646756432622182646[137] = 0.0;
   out_5646756432622182646[138] = 0.0;
   out_5646756432622182646[139] = 0.0;
   out_5646756432622182646[140] = 0.0;
   out_5646756432622182646[141] = 0.0;
   out_5646756432622182646[142] = 0.0;
   out_5646756432622182646[143] = 0.0;
   out_5646756432622182646[144] = 0.0;
   out_5646756432622182646[145] = 0.0;
   out_5646756432622182646[146] = 0.0;
   out_5646756432622182646[147] = 0.0;
   out_5646756432622182646[148] = 0.0;
   out_5646756432622182646[149] = 0.0;
   out_5646756432622182646[150] = 0.0;
   out_5646756432622182646[151] = 0.0;
   out_5646756432622182646[152] = 1.0;
   out_5646756432622182646[153] = 0.0;
   out_5646756432622182646[154] = 0.0;
   out_5646756432622182646[155] = 0.0;
   out_5646756432622182646[156] = 0.0;
   out_5646756432622182646[157] = 0.0;
   out_5646756432622182646[158] = 0.0;
   out_5646756432622182646[159] = 0.0;
   out_5646756432622182646[160] = 0.0;
   out_5646756432622182646[161] = 0.0;
   out_5646756432622182646[162] = 0.0;
   out_5646756432622182646[163] = 0.0;
   out_5646756432622182646[164] = 0.0;
   out_5646756432622182646[165] = 0.0;
   out_5646756432622182646[166] = 0.0;
   out_5646756432622182646[167] = 0.0;
   out_5646756432622182646[168] = 0.0;
   out_5646756432622182646[169] = 0.0;
   out_5646756432622182646[170] = 0.0;
   out_5646756432622182646[171] = 1.0;
   out_5646756432622182646[172] = 0.0;
   out_5646756432622182646[173] = 0.0;
   out_5646756432622182646[174] = 0.0;
   out_5646756432622182646[175] = 0.0;
   out_5646756432622182646[176] = 0.0;
   out_5646756432622182646[177] = 0.0;
   out_5646756432622182646[178] = 0.0;
   out_5646756432622182646[179] = 0.0;
   out_5646756432622182646[180] = 0.0;
   out_5646756432622182646[181] = 0.0;
   out_5646756432622182646[182] = 0.0;
   out_5646756432622182646[183] = 0.0;
   out_5646756432622182646[184] = 0.0;
   out_5646756432622182646[185] = 0.0;
   out_5646756432622182646[186] = 0.0;
   out_5646756432622182646[187] = 0.0;
   out_5646756432622182646[188] = 0.0;
   out_5646756432622182646[189] = 0.0;
   out_5646756432622182646[190] = 1.0;
   out_5646756432622182646[191] = 0.0;
   out_5646756432622182646[192] = 0.0;
   out_5646756432622182646[193] = 0.0;
   out_5646756432622182646[194] = 0.0;
   out_5646756432622182646[195] = 0.0;
   out_5646756432622182646[196] = 0.0;
   out_5646756432622182646[197] = 0.0;
   out_5646756432622182646[198] = 0.0;
   out_5646756432622182646[199] = 0.0;
   out_5646756432622182646[200] = 0.0;
   out_5646756432622182646[201] = 0.0;
   out_5646756432622182646[202] = 0.0;
   out_5646756432622182646[203] = 0.0;
   out_5646756432622182646[204] = 0.0;
   out_5646756432622182646[205] = 0.0;
   out_5646756432622182646[206] = 0.0;
   out_5646756432622182646[207] = 0.0;
   out_5646756432622182646[208] = 0.0;
   out_5646756432622182646[209] = 1.0;
   out_5646756432622182646[210] = 0.0;
   out_5646756432622182646[211] = 0.0;
   out_5646756432622182646[212] = 0.0;
   out_5646756432622182646[213] = 0.0;
   out_5646756432622182646[214] = 0.0;
   out_5646756432622182646[215] = 0.0;
   out_5646756432622182646[216] = 0.0;
   out_5646756432622182646[217] = 0.0;
   out_5646756432622182646[218] = 0.0;
   out_5646756432622182646[219] = 0.0;
   out_5646756432622182646[220] = 0.0;
   out_5646756432622182646[221] = 0.0;
   out_5646756432622182646[222] = 0.0;
   out_5646756432622182646[223] = 0.0;
   out_5646756432622182646[224] = 0.0;
   out_5646756432622182646[225] = 0.0;
   out_5646756432622182646[226] = 0.0;
   out_5646756432622182646[227] = 0.0;
   out_5646756432622182646[228] = 1.0;
   out_5646756432622182646[229] = 0.0;
   out_5646756432622182646[230] = 0.0;
   out_5646756432622182646[231] = 0.0;
   out_5646756432622182646[232] = 0.0;
   out_5646756432622182646[233] = 0.0;
   out_5646756432622182646[234] = 0.0;
   out_5646756432622182646[235] = 0.0;
   out_5646756432622182646[236] = 0.0;
   out_5646756432622182646[237] = 0.0;
   out_5646756432622182646[238] = 0.0;
   out_5646756432622182646[239] = 0.0;
   out_5646756432622182646[240] = 0.0;
   out_5646756432622182646[241] = 0.0;
   out_5646756432622182646[242] = 0.0;
   out_5646756432622182646[243] = 0.0;
   out_5646756432622182646[244] = 0.0;
   out_5646756432622182646[245] = 0.0;
   out_5646756432622182646[246] = 0.0;
   out_5646756432622182646[247] = 1.0;
   out_5646756432622182646[248] = 0.0;
   out_5646756432622182646[249] = 0.0;
   out_5646756432622182646[250] = 0.0;
   out_5646756432622182646[251] = 0.0;
   out_5646756432622182646[252] = 0.0;
   out_5646756432622182646[253] = 0.0;
   out_5646756432622182646[254] = 0.0;
   out_5646756432622182646[255] = 0.0;
   out_5646756432622182646[256] = 0.0;
   out_5646756432622182646[257] = 0.0;
   out_5646756432622182646[258] = 0.0;
   out_5646756432622182646[259] = 0.0;
   out_5646756432622182646[260] = 0.0;
   out_5646756432622182646[261] = 0.0;
   out_5646756432622182646[262] = 0.0;
   out_5646756432622182646[263] = 0.0;
   out_5646756432622182646[264] = 0.0;
   out_5646756432622182646[265] = 0.0;
   out_5646756432622182646[266] = 1.0;
   out_5646756432622182646[267] = 0.0;
   out_5646756432622182646[268] = 0.0;
   out_5646756432622182646[269] = 0.0;
   out_5646756432622182646[270] = 0.0;
   out_5646756432622182646[271] = 0.0;
   out_5646756432622182646[272] = 0.0;
   out_5646756432622182646[273] = 0.0;
   out_5646756432622182646[274] = 0.0;
   out_5646756432622182646[275] = 0.0;
   out_5646756432622182646[276] = 0.0;
   out_5646756432622182646[277] = 0.0;
   out_5646756432622182646[278] = 0.0;
   out_5646756432622182646[279] = 0.0;
   out_5646756432622182646[280] = 0.0;
   out_5646756432622182646[281] = 0.0;
   out_5646756432622182646[282] = 0.0;
   out_5646756432622182646[283] = 0.0;
   out_5646756432622182646[284] = 0.0;
   out_5646756432622182646[285] = 1.0;
   out_5646756432622182646[286] = 0.0;
   out_5646756432622182646[287] = 0.0;
   out_5646756432622182646[288] = 0.0;
   out_5646756432622182646[289] = 0.0;
   out_5646756432622182646[290] = 0.0;
   out_5646756432622182646[291] = 0.0;
   out_5646756432622182646[292] = 0.0;
   out_5646756432622182646[293] = 0.0;
   out_5646756432622182646[294] = 0.0;
   out_5646756432622182646[295] = 0.0;
   out_5646756432622182646[296] = 0.0;
   out_5646756432622182646[297] = 0.0;
   out_5646756432622182646[298] = 0.0;
   out_5646756432622182646[299] = 0.0;
   out_5646756432622182646[300] = 0.0;
   out_5646756432622182646[301] = 0.0;
   out_5646756432622182646[302] = 0.0;
   out_5646756432622182646[303] = 0.0;
   out_5646756432622182646[304] = 1.0;
   out_5646756432622182646[305] = 0.0;
   out_5646756432622182646[306] = 0.0;
   out_5646756432622182646[307] = 0.0;
   out_5646756432622182646[308] = 0.0;
   out_5646756432622182646[309] = 0.0;
   out_5646756432622182646[310] = 0.0;
   out_5646756432622182646[311] = 0.0;
   out_5646756432622182646[312] = 0.0;
   out_5646756432622182646[313] = 0.0;
   out_5646756432622182646[314] = 0.0;
   out_5646756432622182646[315] = 0.0;
   out_5646756432622182646[316] = 0.0;
   out_5646756432622182646[317] = 0.0;
   out_5646756432622182646[318] = 0.0;
   out_5646756432622182646[319] = 0.0;
   out_5646756432622182646[320] = 0.0;
   out_5646756432622182646[321] = 0.0;
   out_5646756432622182646[322] = 0.0;
   out_5646756432622182646[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1137320570887410122) {
   out_1137320570887410122[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1137320570887410122[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1137320570887410122[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1137320570887410122[3] = dt*state[12] + state[3];
   out_1137320570887410122[4] = dt*state[13] + state[4];
   out_1137320570887410122[5] = dt*state[14] + state[5];
   out_1137320570887410122[6] = state[6];
   out_1137320570887410122[7] = state[7];
   out_1137320570887410122[8] = state[8];
   out_1137320570887410122[9] = state[9];
   out_1137320570887410122[10] = state[10];
   out_1137320570887410122[11] = state[11];
   out_1137320570887410122[12] = state[12];
   out_1137320570887410122[13] = state[13];
   out_1137320570887410122[14] = state[14];
   out_1137320570887410122[15] = state[15];
   out_1137320570887410122[16] = state[16];
   out_1137320570887410122[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2697011094328554799) {
   out_2697011094328554799[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2697011094328554799[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2697011094328554799[2] = 0;
   out_2697011094328554799[3] = 0;
   out_2697011094328554799[4] = 0;
   out_2697011094328554799[5] = 0;
   out_2697011094328554799[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2697011094328554799[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2697011094328554799[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2697011094328554799[9] = 0;
   out_2697011094328554799[10] = 0;
   out_2697011094328554799[11] = 0;
   out_2697011094328554799[12] = 0;
   out_2697011094328554799[13] = 0;
   out_2697011094328554799[14] = 0;
   out_2697011094328554799[15] = 0;
   out_2697011094328554799[16] = 0;
   out_2697011094328554799[17] = 0;
   out_2697011094328554799[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2697011094328554799[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2697011094328554799[20] = 0;
   out_2697011094328554799[21] = 0;
   out_2697011094328554799[22] = 0;
   out_2697011094328554799[23] = 0;
   out_2697011094328554799[24] = 0;
   out_2697011094328554799[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2697011094328554799[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2697011094328554799[27] = 0;
   out_2697011094328554799[28] = 0;
   out_2697011094328554799[29] = 0;
   out_2697011094328554799[30] = 0;
   out_2697011094328554799[31] = 0;
   out_2697011094328554799[32] = 0;
   out_2697011094328554799[33] = 0;
   out_2697011094328554799[34] = 0;
   out_2697011094328554799[35] = 0;
   out_2697011094328554799[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2697011094328554799[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2697011094328554799[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2697011094328554799[39] = 0;
   out_2697011094328554799[40] = 0;
   out_2697011094328554799[41] = 0;
   out_2697011094328554799[42] = 0;
   out_2697011094328554799[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2697011094328554799[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2697011094328554799[45] = 0;
   out_2697011094328554799[46] = 0;
   out_2697011094328554799[47] = 0;
   out_2697011094328554799[48] = 0;
   out_2697011094328554799[49] = 0;
   out_2697011094328554799[50] = 0;
   out_2697011094328554799[51] = 0;
   out_2697011094328554799[52] = 0;
   out_2697011094328554799[53] = 0;
   out_2697011094328554799[54] = 0;
   out_2697011094328554799[55] = 0;
   out_2697011094328554799[56] = 0;
   out_2697011094328554799[57] = 1;
   out_2697011094328554799[58] = 0;
   out_2697011094328554799[59] = 0;
   out_2697011094328554799[60] = 0;
   out_2697011094328554799[61] = 0;
   out_2697011094328554799[62] = 0;
   out_2697011094328554799[63] = 0;
   out_2697011094328554799[64] = 0;
   out_2697011094328554799[65] = 0;
   out_2697011094328554799[66] = dt;
   out_2697011094328554799[67] = 0;
   out_2697011094328554799[68] = 0;
   out_2697011094328554799[69] = 0;
   out_2697011094328554799[70] = 0;
   out_2697011094328554799[71] = 0;
   out_2697011094328554799[72] = 0;
   out_2697011094328554799[73] = 0;
   out_2697011094328554799[74] = 0;
   out_2697011094328554799[75] = 0;
   out_2697011094328554799[76] = 1;
   out_2697011094328554799[77] = 0;
   out_2697011094328554799[78] = 0;
   out_2697011094328554799[79] = 0;
   out_2697011094328554799[80] = 0;
   out_2697011094328554799[81] = 0;
   out_2697011094328554799[82] = 0;
   out_2697011094328554799[83] = 0;
   out_2697011094328554799[84] = 0;
   out_2697011094328554799[85] = dt;
   out_2697011094328554799[86] = 0;
   out_2697011094328554799[87] = 0;
   out_2697011094328554799[88] = 0;
   out_2697011094328554799[89] = 0;
   out_2697011094328554799[90] = 0;
   out_2697011094328554799[91] = 0;
   out_2697011094328554799[92] = 0;
   out_2697011094328554799[93] = 0;
   out_2697011094328554799[94] = 0;
   out_2697011094328554799[95] = 1;
   out_2697011094328554799[96] = 0;
   out_2697011094328554799[97] = 0;
   out_2697011094328554799[98] = 0;
   out_2697011094328554799[99] = 0;
   out_2697011094328554799[100] = 0;
   out_2697011094328554799[101] = 0;
   out_2697011094328554799[102] = 0;
   out_2697011094328554799[103] = 0;
   out_2697011094328554799[104] = dt;
   out_2697011094328554799[105] = 0;
   out_2697011094328554799[106] = 0;
   out_2697011094328554799[107] = 0;
   out_2697011094328554799[108] = 0;
   out_2697011094328554799[109] = 0;
   out_2697011094328554799[110] = 0;
   out_2697011094328554799[111] = 0;
   out_2697011094328554799[112] = 0;
   out_2697011094328554799[113] = 0;
   out_2697011094328554799[114] = 1;
   out_2697011094328554799[115] = 0;
   out_2697011094328554799[116] = 0;
   out_2697011094328554799[117] = 0;
   out_2697011094328554799[118] = 0;
   out_2697011094328554799[119] = 0;
   out_2697011094328554799[120] = 0;
   out_2697011094328554799[121] = 0;
   out_2697011094328554799[122] = 0;
   out_2697011094328554799[123] = 0;
   out_2697011094328554799[124] = 0;
   out_2697011094328554799[125] = 0;
   out_2697011094328554799[126] = 0;
   out_2697011094328554799[127] = 0;
   out_2697011094328554799[128] = 0;
   out_2697011094328554799[129] = 0;
   out_2697011094328554799[130] = 0;
   out_2697011094328554799[131] = 0;
   out_2697011094328554799[132] = 0;
   out_2697011094328554799[133] = 1;
   out_2697011094328554799[134] = 0;
   out_2697011094328554799[135] = 0;
   out_2697011094328554799[136] = 0;
   out_2697011094328554799[137] = 0;
   out_2697011094328554799[138] = 0;
   out_2697011094328554799[139] = 0;
   out_2697011094328554799[140] = 0;
   out_2697011094328554799[141] = 0;
   out_2697011094328554799[142] = 0;
   out_2697011094328554799[143] = 0;
   out_2697011094328554799[144] = 0;
   out_2697011094328554799[145] = 0;
   out_2697011094328554799[146] = 0;
   out_2697011094328554799[147] = 0;
   out_2697011094328554799[148] = 0;
   out_2697011094328554799[149] = 0;
   out_2697011094328554799[150] = 0;
   out_2697011094328554799[151] = 0;
   out_2697011094328554799[152] = 1;
   out_2697011094328554799[153] = 0;
   out_2697011094328554799[154] = 0;
   out_2697011094328554799[155] = 0;
   out_2697011094328554799[156] = 0;
   out_2697011094328554799[157] = 0;
   out_2697011094328554799[158] = 0;
   out_2697011094328554799[159] = 0;
   out_2697011094328554799[160] = 0;
   out_2697011094328554799[161] = 0;
   out_2697011094328554799[162] = 0;
   out_2697011094328554799[163] = 0;
   out_2697011094328554799[164] = 0;
   out_2697011094328554799[165] = 0;
   out_2697011094328554799[166] = 0;
   out_2697011094328554799[167] = 0;
   out_2697011094328554799[168] = 0;
   out_2697011094328554799[169] = 0;
   out_2697011094328554799[170] = 0;
   out_2697011094328554799[171] = 1;
   out_2697011094328554799[172] = 0;
   out_2697011094328554799[173] = 0;
   out_2697011094328554799[174] = 0;
   out_2697011094328554799[175] = 0;
   out_2697011094328554799[176] = 0;
   out_2697011094328554799[177] = 0;
   out_2697011094328554799[178] = 0;
   out_2697011094328554799[179] = 0;
   out_2697011094328554799[180] = 0;
   out_2697011094328554799[181] = 0;
   out_2697011094328554799[182] = 0;
   out_2697011094328554799[183] = 0;
   out_2697011094328554799[184] = 0;
   out_2697011094328554799[185] = 0;
   out_2697011094328554799[186] = 0;
   out_2697011094328554799[187] = 0;
   out_2697011094328554799[188] = 0;
   out_2697011094328554799[189] = 0;
   out_2697011094328554799[190] = 1;
   out_2697011094328554799[191] = 0;
   out_2697011094328554799[192] = 0;
   out_2697011094328554799[193] = 0;
   out_2697011094328554799[194] = 0;
   out_2697011094328554799[195] = 0;
   out_2697011094328554799[196] = 0;
   out_2697011094328554799[197] = 0;
   out_2697011094328554799[198] = 0;
   out_2697011094328554799[199] = 0;
   out_2697011094328554799[200] = 0;
   out_2697011094328554799[201] = 0;
   out_2697011094328554799[202] = 0;
   out_2697011094328554799[203] = 0;
   out_2697011094328554799[204] = 0;
   out_2697011094328554799[205] = 0;
   out_2697011094328554799[206] = 0;
   out_2697011094328554799[207] = 0;
   out_2697011094328554799[208] = 0;
   out_2697011094328554799[209] = 1;
   out_2697011094328554799[210] = 0;
   out_2697011094328554799[211] = 0;
   out_2697011094328554799[212] = 0;
   out_2697011094328554799[213] = 0;
   out_2697011094328554799[214] = 0;
   out_2697011094328554799[215] = 0;
   out_2697011094328554799[216] = 0;
   out_2697011094328554799[217] = 0;
   out_2697011094328554799[218] = 0;
   out_2697011094328554799[219] = 0;
   out_2697011094328554799[220] = 0;
   out_2697011094328554799[221] = 0;
   out_2697011094328554799[222] = 0;
   out_2697011094328554799[223] = 0;
   out_2697011094328554799[224] = 0;
   out_2697011094328554799[225] = 0;
   out_2697011094328554799[226] = 0;
   out_2697011094328554799[227] = 0;
   out_2697011094328554799[228] = 1;
   out_2697011094328554799[229] = 0;
   out_2697011094328554799[230] = 0;
   out_2697011094328554799[231] = 0;
   out_2697011094328554799[232] = 0;
   out_2697011094328554799[233] = 0;
   out_2697011094328554799[234] = 0;
   out_2697011094328554799[235] = 0;
   out_2697011094328554799[236] = 0;
   out_2697011094328554799[237] = 0;
   out_2697011094328554799[238] = 0;
   out_2697011094328554799[239] = 0;
   out_2697011094328554799[240] = 0;
   out_2697011094328554799[241] = 0;
   out_2697011094328554799[242] = 0;
   out_2697011094328554799[243] = 0;
   out_2697011094328554799[244] = 0;
   out_2697011094328554799[245] = 0;
   out_2697011094328554799[246] = 0;
   out_2697011094328554799[247] = 1;
   out_2697011094328554799[248] = 0;
   out_2697011094328554799[249] = 0;
   out_2697011094328554799[250] = 0;
   out_2697011094328554799[251] = 0;
   out_2697011094328554799[252] = 0;
   out_2697011094328554799[253] = 0;
   out_2697011094328554799[254] = 0;
   out_2697011094328554799[255] = 0;
   out_2697011094328554799[256] = 0;
   out_2697011094328554799[257] = 0;
   out_2697011094328554799[258] = 0;
   out_2697011094328554799[259] = 0;
   out_2697011094328554799[260] = 0;
   out_2697011094328554799[261] = 0;
   out_2697011094328554799[262] = 0;
   out_2697011094328554799[263] = 0;
   out_2697011094328554799[264] = 0;
   out_2697011094328554799[265] = 0;
   out_2697011094328554799[266] = 1;
   out_2697011094328554799[267] = 0;
   out_2697011094328554799[268] = 0;
   out_2697011094328554799[269] = 0;
   out_2697011094328554799[270] = 0;
   out_2697011094328554799[271] = 0;
   out_2697011094328554799[272] = 0;
   out_2697011094328554799[273] = 0;
   out_2697011094328554799[274] = 0;
   out_2697011094328554799[275] = 0;
   out_2697011094328554799[276] = 0;
   out_2697011094328554799[277] = 0;
   out_2697011094328554799[278] = 0;
   out_2697011094328554799[279] = 0;
   out_2697011094328554799[280] = 0;
   out_2697011094328554799[281] = 0;
   out_2697011094328554799[282] = 0;
   out_2697011094328554799[283] = 0;
   out_2697011094328554799[284] = 0;
   out_2697011094328554799[285] = 1;
   out_2697011094328554799[286] = 0;
   out_2697011094328554799[287] = 0;
   out_2697011094328554799[288] = 0;
   out_2697011094328554799[289] = 0;
   out_2697011094328554799[290] = 0;
   out_2697011094328554799[291] = 0;
   out_2697011094328554799[292] = 0;
   out_2697011094328554799[293] = 0;
   out_2697011094328554799[294] = 0;
   out_2697011094328554799[295] = 0;
   out_2697011094328554799[296] = 0;
   out_2697011094328554799[297] = 0;
   out_2697011094328554799[298] = 0;
   out_2697011094328554799[299] = 0;
   out_2697011094328554799[300] = 0;
   out_2697011094328554799[301] = 0;
   out_2697011094328554799[302] = 0;
   out_2697011094328554799[303] = 0;
   out_2697011094328554799[304] = 1;
   out_2697011094328554799[305] = 0;
   out_2697011094328554799[306] = 0;
   out_2697011094328554799[307] = 0;
   out_2697011094328554799[308] = 0;
   out_2697011094328554799[309] = 0;
   out_2697011094328554799[310] = 0;
   out_2697011094328554799[311] = 0;
   out_2697011094328554799[312] = 0;
   out_2697011094328554799[313] = 0;
   out_2697011094328554799[314] = 0;
   out_2697011094328554799[315] = 0;
   out_2697011094328554799[316] = 0;
   out_2697011094328554799[317] = 0;
   out_2697011094328554799[318] = 0;
   out_2697011094328554799[319] = 0;
   out_2697011094328554799[320] = 0;
   out_2697011094328554799[321] = 0;
   out_2697011094328554799[322] = 0;
   out_2697011094328554799[323] = 1;
}
void h_4(double *state, double *unused, double *out_1053451418042427012) {
   out_1053451418042427012[0] = state[6] + state[9];
   out_1053451418042427012[1] = state[7] + state[10];
   out_1053451418042427012[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_7540267336217958736) {
   out_7540267336217958736[0] = 0;
   out_7540267336217958736[1] = 0;
   out_7540267336217958736[2] = 0;
   out_7540267336217958736[3] = 0;
   out_7540267336217958736[4] = 0;
   out_7540267336217958736[5] = 0;
   out_7540267336217958736[6] = 1;
   out_7540267336217958736[7] = 0;
   out_7540267336217958736[8] = 0;
   out_7540267336217958736[9] = 1;
   out_7540267336217958736[10] = 0;
   out_7540267336217958736[11] = 0;
   out_7540267336217958736[12] = 0;
   out_7540267336217958736[13] = 0;
   out_7540267336217958736[14] = 0;
   out_7540267336217958736[15] = 0;
   out_7540267336217958736[16] = 0;
   out_7540267336217958736[17] = 0;
   out_7540267336217958736[18] = 0;
   out_7540267336217958736[19] = 0;
   out_7540267336217958736[20] = 0;
   out_7540267336217958736[21] = 0;
   out_7540267336217958736[22] = 0;
   out_7540267336217958736[23] = 0;
   out_7540267336217958736[24] = 0;
   out_7540267336217958736[25] = 1;
   out_7540267336217958736[26] = 0;
   out_7540267336217958736[27] = 0;
   out_7540267336217958736[28] = 1;
   out_7540267336217958736[29] = 0;
   out_7540267336217958736[30] = 0;
   out_7540267336217958736[31] = 0;
   out_7540267336217958736[32] = 0;
   out_7540267336217958736[33] = 0;
   out_7540267336217958736[34] = 0;
   out_7540267336217958736[35] = 0;
   out_7540267336217958736[36] = 0;
   out_7540267336217958736[37] = 0;
   out_7540267336217958736[38] = 0;
   out_7540267336217958736[39] = 0;
   out_7540267336217958736[40] = 0;
   out_7540267336217958736[41] = 0;
   out_7540267336217958736[42] = 0;
   out_7540267336217958736[43] = 0;
   out_7540267336217958736[44] = 1;
   out_7540267336217958736[45] = 0;
   out_7540267336217958736[46] = 0;
   out_7540267336217958736[47] = 1;
   out_7540267336217958736[48] = 0;
   out_7540267336217958736[49] = 0;
   out_7540267336217958736[50] = 0;
   out_7540267336217958736[51] = 0;
   out_7540267336217958736[52] = 0;
   out_7540267336217958736[53] = 0;
}
void h_10(double *state, double *unused, double *out_3684376753725260505) {
   out_3684376753725260505[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3684376753725260505[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3684376753725260505[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5090252371717073425) {
   out_5090252371717073425[0] = 0;
   out_5090252371717073425[1] = 9.8100000000000005*cos(state[1]);
   out_5090252371717073425[2] = 0;
   out_5090252371717073425[3] = 0;
   out_5090252371717073425[4] = -state[8];
   out_5090252371717073425[5] = state[7];
   out_5090252371717073425[6] = 0;
   out_5090252371717073425[7] = state[5];
   out_5090252371717073425[8] = -state[4];
   out_5090252371717073425[9] = 0;
   out_5090252371717073425[10] = 0;
   out_5090252371717073425[11] = 0;
   out_5090252371717073425[12] = 1;
   out_5090252371717073425[13] = 0;
   out_5090252371717073425[14] = 0;
   out_5090252371717073425[15] = 1;
   out_5090252371717073425[16] = 0;
   out_5090252371717073425[17] = 0;
   out_5090252371717073425[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5090252371717073425[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5090252371717073425[20] = 0;
   out_5090252371717073425[21] = state[8];
   out_5090252371717073425[22] = 0;
   out_5090252371717073425[23] = -state[6];
   out_5090252371717073425[24] = -state[5];
   out_5090252371717073425[25] = 0;
   out_5090252371717073425[26] = state[3];
   out_5090252371717073425[27] = 0;
   out_5090252371717073425[28] = 0;
   out_5090252371717073425[29] = 0;
   out_5090252371717073425[30] = 0;
   out_5090252371717073425[31] = 1;
   out_5090252371717073425[32] = 0;
   out_5090252371717073425[33] = 0;
   out_5090252371717073425[34] = 1;
   out_5090252371717073425[35] = 0;
   out_5090252371717073425[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5090252371717073425[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5090252371717073425[38] = 0;
   out_5090252371717073425[39] = -state[7];
   out_5090252371717073425[40] = state[6];
   out_5090252371717073425[41] = 0;
   out_5090252371717073425[42] = state[4];
   out_5090252371717073425[43] = -state[3];
   out_5090252371717073425[44] = 0;
   out_5090252371717073425[45] = 0;
   out_5090252371717073425[46] = 0;
   out_5090252371717073425[47] = 0;
   out_5090252371717073425[48] = 0;
   out_5090252371717073425[49] = 0;
   out_5090252371717073425[50] = 1;
   out_5090252371717073425[51] = 0;
   out_5090252371717073425[52] = 0;
   out_5090252371717073425[53] = 1;
}
void h_13(double *state, double *unused, double *out_5749954067458841209) {
   out_5749954067458841209[0] = state[3];
   out_5749954067458841209[1] = state[4];
   out_5749954067458841209[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4327993510885625935) {
   out_4327993510885625935[0] = 0;
   out_4327993510885625935[1] = 0;
   out_4327993510885625935[2] = 0;
   out_4327993510885625935[3] = 1;
   out_4327993510885625935[4] = 0;
   out_4327993510885625935[5] = 0;
   out_4327993510885625935[6] = 0;
   out_4327993510885625935[7] = 0;
   out_4327993510885625935[8] = 0;
   out_4327993510885625935[9] = 0;
   out_4327993510885625935[10] = 0;
   out_4327993510885625935[11] = 0;
   out_4327993510885625935[12] = 0;
   out_4327993510885625935[13] = 0;
   out_4327993510885625935[14] = 0;
   out_4327993510885625935[15] = 0;
   out_4327993510885625935[16] = 0;
   out_4327993510885625935[17] = 0;
   out_4327993510885625935[18] = 0;
   out_4327993510885625935[19] = 0;
   out_4327993510885625935[20] = 0;
   out_4327993510885625935[21] = 0;
   out_4327993510885625935[22] = 1;
   out_4327993510885625935[23] = 0;
   out_4327993510885625935[24] = 0;
   out_4327993510885625935[25] = 0;
   out_4327993510885625935[26] = 0;
   out_4327993510885625935[27] = 0;
   out_4327993510885625935[28] = 0;
   out_4327993510885625935[29] = 0;
   out_4327993510885625935[30] = 0;
   out_4327993510885625935[31] = 0;
   out_4327993510885625935[32] = 0;
   out_4327993510885625935[33] = 0;
   out_4327993510885625935[34] = 0;
   out_4327993510885625935[35] = 0;
   out_4327993510885625935[36] = 0;
   out_4327993510885625935[37] = 0;
   out_4327993510885625935[38] = 0;
   out_4327993510885625935[39] = 0;
   out_4327993510885625935[40] = 0;
   out_4327993510885625935[41] = 1;
   out_4327993510885625935[42] = 0;
   out_4327993510885625935[43] = 0;
   out_4327993510885625935[44] = 0;
   out_4327993510885625935[45] = 0;
   out_4327993510885625935[46] = 0;
   out_4327993510885625935[47] = 0;
   out_4327993510885625935[48] = 0;
   out_4327993510885625935[49] = 0;
   out_4327993510885625935[50] = 0;
   out_4327993510885625935[51] = 0;
   out_4327993510885625935[52] = 0;
   out_4327993510885625935[53] = 0;
}
void h_14(double *state, double *unused, double *out_9151671114827748167) {
   out_9151671114827748167[0] = state[6];
   out_9151671114827748167[1] = state[7];
   out_9151671114827748167[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3577026479878474207) {
   out_3577026479878474207[0] = 0;
   out_3577026479878474207[1] = 0;
   out_3577026479878474207[2] = 0;
   out_3577026479878474207[3] = 0;
   out_3577026479878474207[4] = 0;
   out_3577026479878474207[5] = 0;
   out_3577026479878474207[6] = 1;
   out_3577026479878474207[7] = 0;
   out_3577026479878474207[8] = 0;
   out_3577026479878474207[9] = 0;
   out_3577026479878474207[10] = 0;
   out_3577026479878474207[11] = 0;
   out_3577026479878474207[12] = 0;
   out_3577026479878474207[13] = 0;
   out_3577026479878474207[14] = 0;
   out_3577026479878474207[15] = 0;
   out_3577026479878474207[16] = 0;
   out_3577026479878474207[17] = 0;
   out_3577026479878474207[18] = 0;
   out_3577026479878474207[19] = 0;
   out_3577026479878474207[20] = 0;
   out_3577026479878474207[21] = 0;
   out_3577026479878474207[22] = 0;
   out_3577026479878474207[23] = 0;
   out_3577026479878474207[24] = 0;
   out_3577026479878474207[25] = 1;
   out_3577026479878474207[26] = 0;
   out_3577026479878474207[27] = 0;
   out_3577026479878474207[28] = 0;
   out_3577026479878474207[29] = 0;
   out_3577026479878474207[30] = 0;
   out_3577026479878474207[31] = 0;
   out_3577026479878474207[32] = 0;
   out_3577026479878474207[33] = 0;
   out_3577026479878474207[34] = 0;
   out_3577026479878474207[35] = 0;
   out_3577026479878474207[36] = 0;
   out_3577026479878474207[37] = 0;
   out_3577026479878474207[38] = 0;
   out_3577026479878474207[39] = 0;
   out_3577026479878474207[40] = 0;
   out_3577026479878474207[41] = 0;
   out_3577026479878474207[42] = 0;
   out_3577026479878474207[43] = 0;
   out_3577026479878474207[44] = 1;
   out_3577026479878474207[45] = 0;
   out_3577026479878474207[46] = 0;
   out_3577026479878474207[47] = 0;
   out_3577026479878474207[48] = 0;
   out_3577026479878474207[49] = 0;
   out_3577026479878474207[50] = 0;
   out_3577026479878474207[51] = 0;
   out_3577026479878474207[52] = 0;
   out_3577026479878474207[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3926294361318359623) {
  err_fun(nom_x, delta_x, out_3926294361318359623);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5231104082209692226) {
  inv_err_fun(nom_x, true_x, out_5231104082209692226);
}
void pose_H_mod_fun(double *state, double *out_5646756432622182646) {
  H_mod_fun(state, out_5646756432622182646);
}
void pose_f_fun(double *state, double dt, double *out_1137320570887410122) {
  f_fun(state,  dt, out_1137320570887410122);
}
void pose_F_fun(double *state, double dt, double *out_2697011094328554799) {
  F_fun(state,  dt, out_2697011094328554799);
}
void pose_h_4(double *state, double *unused, double *out_1053451418042427012) {
  h_4(state, unused, out_1053451418042427012);
}
void pose_H_4(double *state, double *unused, double *out_7540267336217958736) {
  H_4(state, unused, out_7540267336217958736);
}
void pose_h_10(double *state, double *unused, double *out_3684376753725260505) {
  h_10(state, unused, out_3684376753725260505);
}
void pose_H_10(double *state, double *unused, double *out_5090252371717073425) {
  H_10(state, unused, out_5090252371717073425);
}
void pose_h_13(double *state, double *unused, double *out_5749954067458841209) {
  h_13(state, unused, out_5749954067458841209);
}
void pose_H_13(double *state, double *unused, double *out_4327993510885625935) {
  H_13(state, unused, out_4327993510885625935);
}
void pose_h_14(double *state, double *unused, double *out_9151671114827748167) {
  h_14(state, unused, out_9151671114827748167);
}
void pose_H_14(double *state, double *unused, double *out_3577026479878474207) {
  H_14(state, unused, out_3577026479878474207);
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
