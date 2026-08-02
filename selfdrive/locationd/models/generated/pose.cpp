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
void err_fun(double *nom_x, double *delta_x, double *out_327274557709511665) {
   out_327274557709511665[0] = delta_x[0] + nom_x[0];
   out_327274557709511665[1] = delta_x[1] + nom_x[1];
   out_327274557709511665[2] = delta_x[2] + nom_x[2];
   out_327274557709511665[3] = delta_x[3] + nom_x[3];
   out_327274557709511665[4] = delta_x[4] + nom_x[4];
   out_327274557709511665[5] = delta_x[5] + nom_x[5];
   out_327274557709511665[6] = delta_x[6] + nom_x[6];
   out_327274557709511665[7] = delta_x[7] + nom_x[7];
   out_327274557709511665[8] = delta_x[8] + nom_x[8];
   out_327274557709511665[9] = delta_x[9] + nom_x[9];
   out_327274557709511665[10] = delta_x[10] + nom_x[10];
   out_327274557709511665[11] = delta_x[11] + nom_x[11];
   out_327274557709511665[12] = delta_x[12] + nom_x[12];
   out_327274557709511665[13] = delta_x[13] + nom_x[13];
   out_327274557709511665[14] = delta_x[14] + nom_x[14];
   out_327274557709511665[15] = delta_x[15] + nom_x[15];
   out_327274557709511665[16] = delta_x[16] + nom_x[16];
   out_327274557709511665[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4344179942375735738) {
   out_4344179942375735738[0] = -nom_x[0] + true_x[0];
   out_4344179942375735738[1] = -nom_x[1] + true_x[1];
   out_4344179942375735738[2] = -nom_x[2] + true_x[2];
   out_4344179942375735738[3] = -nom_x[3] + true_x[3];
   out_4344179942375735738[4] = -nom_x[4] + true_x[4];
   out_4344179942375735738[5] = -nom_x[5] + true_x[5];
   out_4344179942375735738[6] = -nom_x[6] + true_x[6];
   out_4344179942375735738[7] = -nom_x[7] + true_x[7];
   out_4344179942375735738[8] = -nom_x[8] + true_x[8];
   out_4344179942375735738[9] = -nom_x[9] + true_x[9];
   out_4344179942375735738[10] = -nom_x[10] + true_x[10];
   out_4344179942375735738[11] = -nom_x[11] + true_x[11];
   out_4344179942375735738[12] = -nom_x[12] + true_x[12];
   out_4344179942375735738[13] = -nom_x[13] + true_x[13];
   out_4344179942375735738[14] = -nom_x[14] + true_x[14];
   out_4344179942375735738[15] = -nom_x[15] + true_x[15];
   out_4344179942375735738[16] = -nom_x[16] + true_x[16];
   out_4344179942375735738[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_8315920796386777796) {
   out_8315920796386777796[0] = 1.0;
   out_8315920796386777796[1] = 0.0;
   out_8315920796386777796[2] = 0.0;
   out_8315920796386777796[3] = 0.0;
   out_8315920796386777796[4] = 0.0;
   out_8315920796386777796[5] = 0.0;
   out_8315920796386777796[6] = 0.0;
   out_8315920796386777796[7] = 0.0;
   out_8315920796386777796[8] = 0.0;
   out_8315920796386777796[9] = 0.0;
   out_8315920796386777796[10] = 0.0;
   out_8315920796386777796[11] = 0.0;
   out_8315920796386777796[12] = 0.0;
   out_8315920796386777796[13] = 0.0;
   out_8315920796386777796[14] = 0.0;
   out_8315920796386777796[15] = 0.0;
   out_8315920796386777796[16] = 0.0;
   out_8315920796386777796[17] = 0.0;
   out_8315920796386777796[18] = 0.0;
   out_8315920796386777796[19] = 1.0;
   out_8315920796386777796[20] = 0.0;
   out_8315920796386777796[21] = 0.0;
   out_8315920796386777796[22] = 0.0;
   out_8315920796386777796[23] = 0.0;
   out_8315920796386777796[24] = 0.0;
   out_8315920796386777796[25] = 0.0;
   out_8315920796386777796[26] = 0.0;
   out_8315920796386777796[27] = 0.0;
   out_8315920796386777796[28] = 0.0;
   out_8315920796386777796[29] = 0.0;
   out_8315920796386777796[30] = 0.0;
   out_8315920796386777796[31] = 0.0;
   out_8315920796386777796[32] = 0.0;
   out_8315920796386777796[33] = 0.0;
   out_8315920796386777796[34] = 0.0;
   out_8315920796386777796[35] = 0.0;
   out_8315920796386777796[36] = 0.0;
   out_8315920796386777796[37] = 0.0;
   out_8315920796386777796[38] = 1.0;
   out_8315920796386777796[39] = 0.0;
   out_8315920796386777796[40] = 0.0;
   out_8315920796386777796[41] = 0.0;
   out_8315920796386777796[42] = 0.0;
   out_8315920796386777796[43] = 0.0;
   out_8315920796386777796[44] = 0.0;
   out_8315920796386777796[45] = 0.0;
   out_8315920796386777796[46] = 0.0;
   out_8315920796386777796[47] = 0.0;
   out_8315920796386777796[48] = 0.0;
   out_8315920796386777796[49] = 0.0;
   out_8315920796386777796[50] = 0.0;
   out_8315920796386777796[51] = 0.0;
   out_8315920796386777796[52] = 0.0;
   out_8315920796386777796[53] = 0.0;
   out_8315920796386777796[54] = 0.0;
   out_8315920796386777796[55] = 0.0;
   out_8315920796386777796[56] = 0.0;
   out_8315920796386777796[57] = 1.0;
   out_8315920796386777796[58] = 0.0;
   out_8315920796386777796[59] = 0.0;
   out_8315920796386777796[60] = 0.0;
   out_8315920796386777796[61] = 0.0;
   out_8315920796386777796[62] = 0.0;
   out_8315920796386777796[63] = 0.0;
   out_8315920796386777796[64] = 0.0;
   out_8315920796386777796[65] = 0.0;
   out_8315920796386777796[66] = 0.0;
   out_8315920796386777796[67] = 0.0;
   out_8315920796386777796[68] = 0.0;
   out_8315920796386777796[69] = 0.0;
   out_8315920796386777796[70] = 0.0;
   out_8315920796386777796[71] = 0.0;
   out_8315920796386777796[72] = 0.0;
   out_8315920796386777796[73] = 0.0;
   out_8315920796386777796[74] = 0.0;
   out_8315920796386777796[75] = 0.0;
   out_8315920796386777796[76] = 1.0;
   out_8315920796386777796[77] = 0.0;
   out_8315920796386777796[78] = 0.0;
   out_8315920796386777796[79] = 0.0;
   out_8315920796386777796[80] = 0.0;
   out_8315920796386777796[81] = 0.0;
   out_8315920796386777796[82] = 0.0;
   out_8315920796386777796[83] = 0.0;
   out_8315920796386777796[84] = 0.0;
   out_8315920796386777796[85] = 0.0;
   out_8315920796386777796[86] = 0.0;
   out_8315920796386777796[87] = 0.0;
   out_8315920796386777796[88] = 0.0;
   out_8315920796386777796[89] = 0.0;
   out_8315920796386777796[90] = 0.0;
   out_8315920796386777796[91] = 0.0;
   out_8315920796386777796[92] = 0.0;
   out_8315920796386777796[93] = 0.0;
   out_8315920796386777796[94] = 0.0;
   out_8315920796386777796[95] = 1.0;
   out_8315920796386777796[96] = 0.0;
   out_8315920796386777796[97] = 0.0;
   out_8315920796386777796[98] = 0.0;
   out_8315920796386777796[99] = 0.0;
   out_8315920796386777796[100] = 0.0;
   out_8315920796386777796[101] = 0.0;
   out_8315920796386777796[102] = 0.0;
   out_8315920796386777796[103] = 0.0;
   out_8315920796386777796[104] = 0.0;
   out_8315920796386777796[105] = 0.0;
   out_8315920796386777796[106] = 0.0;
   out_8315920796386777796[107] = 0.0;
   out_8315920796386777796[108] = 0.0;
   out_8315920796386777796[109] = 0.0;
   out_8315920796386777796[110] = 0.0;
   out_8315920796386777796[111] = 0.0;
   out_8315920796386777796[112] = 0.0;
   out_8315920796386777796[113] = 0.0;
   out_8315920796386777796[114] = 1.0;
   out_8315920796386777796[115] = 0.0;
   out_8315920796386777796[116] = 0.0;
   out_8315920796386777796[117] = 0.0;
   out_8315920796386777796[118] = 0.0;
   out_8315920796386777796[119] = 0.0;
   out_8315920796386777796[120] = 0.0;
   out_8315920796386777796[121] = 0.0;
   out_8315920796386777796[122] = 0.0;
   out_8315920796386777796[123] = 0.0;
   out_8315920796386777796[124] = 0.0;
   out_8315920796386777796[125] = 0.0;
   out_8315920796386777796[126] = 0.0;
   out_8315920796386777796[127] = 0.0;
   out_8315920796386777796[128] = 0.0;
   out_8315920796386777796[129] = 0.0;
   out_8315920796386777796[130] = 0.0;
   out_8315920796386777796[131] = 0.0;
   out_8315920796386777796[132] = 0.0;
   out_8315920796386777796[133] = 1.0;
   out_8315920796386777796[134] = 0.0;
   out_8315920796386777796[135] = 0.0;
   out_8315920796386777796[136] = 0.0;
   out_8315920796386777796[137] = 0.0;
   out_8315920796386777796[138] = 0.0;
   out_8315920796386777796[139] = 0.0;
   out_8315920796386777796[140] = 0.0;
   out_8315920796386777796[141] = 0.0;
   out_8315920796386777796[142] = 0.0;
   out_8315920796386777796[143] = 0.0;
   out_8315920796386777796[144] = 0.0;
   out_8315920796386777796[145] = 0.0;
   out_8315920796386777796[146] = 0.0;
   out_8315920796386777796[147] = 0.0;
   out_8315920796386777796[148] = 0.0;
   out_8315920796386777796[149] = 0.0;
   out_8315920796386777796[150] = 0.0;
   out_8315920796386777796[151] = 0.0;
   out_8315920796386777796[152] = 1.0;
   out_8315920796386777796[153] = 0.0;
   out_8315920796386777796[154] = 0.0;
   out_8315920796386777796[155] = 0.0;
   out_8315920796386777796[156] = 0.0;
   out_8315920796386777796[157] = 0.0;
   out_8315920796386777796[158] = 0.0;
   out_8315920796386777796[159] = 0.0;
   out_8315920796386777796[160] = 0.0;
   out_8315920796386777796[161] = 0.0;
   out_8315920796386777796[162] = 0.0;
   out_8315920796386777796[163] = 0.0;
   out_8315920796386777796[164] = 0.0;
   out_8315920796386777796[165] = 0.0;
   out_8315920796386777796[166] = 0.0;
   out_8315920796386777796[167] = 0.0;
   out_8315920796386777796[168] = 0.0;
   out_8315920796386777796[169] = 0.0;
   out_8315920796386777796[170] = 0.0;
   out_8315920796386777796[171] = 1.0;
   out_8315920796386777796[172] = 0.0;
   out_8315920796386777796[173] = 0.0;
   out_8315920796386777796[174] = 0.0;
   out_8315920796386777796[175] = 0.0;
   out_8315920796386777796[176] = 0.0;
   out_8315920796386777796[177] = 0.0;
   out_8315920796386777796[178] = 0.0;
   out_8315920796386777796[179] = 0.0;
   out_8315920796386777796[180] = 0.0;
   out_8315920796386777796[181] = 0.0;
   out_8315920796386777796[182] = 0.0;
   out_8315920796386777796[183] = 0.0;
   out_8315920796386777796[184] = 0.0;
   out_8315920796386777796[185] = 0.0;
   out_8315920796386777796[186] = 0.0;
   out_8315920796386777796[187] = 0.0;
   out_8315920796386777796[188] = 0.0;
   out_8315920796386777796[189] = 0.0;
   out_8315920796386777796[190] = 1.0;
   out_8315920796386777796[191] = 0.0;
   out_8315920796386777796[192] = 0.0;
   out_8315920796386777796[193] = 0.0;
   out_8315920796386777796[194] = 0.0;
   out_8315920796386777796[195] = 0.0;
   out_8315920796386777796[196] = 0.0;
   out_8315920796386777796[197] = 0.0;
   out_8315920796386777796[198] = 0.0;
   out_8315920796386777796[199] = 0.0;
   out_8315920796386777796[200] = 0.0;
   out_8315920796386777796[201] = 0.0;
   out_8315920796386777796[202] = 0.0;
   out_8315920796386777796[203] = 0.0;
   out_8315920796386777796[204] = 0.0;
   out_8315920796386777796[205] = 0.0;
   out_8315920796386777796[206] = 0.0;
   out_8315920796386777796[207] = 0.0;
   out_8315920796386777796[208] = 0.0;
   out_8315920796386777796[209] = 1.0;
   out_8315920796386777796[210] = 0.0;
   out_8315920796386777796[211] = 0.0;
   out_8315920796386777796[212] = 0.0;
   out_8315920796386777796[213] = 0.0;
   out_8315920796386777796[214] = 0.0;
   out_8315920796386777796[215] = 0.0;
   out_8315920796386777796[216] = 0.0;
   out_8315920796386777796[217] = 0.0;
   out_8315920796386777796[218] = 0.0;
   out_8315920796386777796[219] = 0.0;
   out_8315920796386777796[220] = 0.0;
   out_8315920796386777796[221] = 0.0;
   out_8315920796386777796[222] = 0.0;
   out_8315920796386777796[223] = 0.0;
   out_8315920796386777796[224] = 0.0;
   out_8315920796386777796[225] = 0.0;
   out_8315920796386777796[226] = 0.0;
   out_8315920796386777796[227] = 0.0;
   out_8315920796386777796[228] = 1.0;
   out_8315920796386777796[229] = 0.0;
   out_8315920796386777796[230] = 0.0;
   out_8315920796386777796[231] = 0.0;
   out_8315920796386777796[232] = 0.0;
   out_8315920796386777796[233] = 0.0;
   out_8315920796386777796[234] = 0.0;
   out_8315920796386777796[235] = 0.0;
   out_8315920796386777796[236] = 0.0;
   out_8315920796386777796[237] = 0.0;
   out_8315920796386777796[238] = 0.0;
   out_8315920796386777796[239] = 0.0;
   out_8315920796386777796[240] = 0.0;
   out_8315920796386777796[241] = 0.0;
   out_8315920796386777796[242] = 0.0;
   out_8315920796386777796[243] = 0.0;
   out_8315920796386777796[244] = 0.0;
   out_8315920796386777796[245] = 0.0;
   out_8315920796386777796[246] = 0.0;
   out_8315920796386777796[247] = 1.0;
   out_8315920796386777796[248] = 0.0;
   out_8315920796386777796[249] = 0.0;
   out_8315920796386777796[250] = 0.0;
   out_8315920796386777796[251] = 0.0;
   out_8315920796386777796[252] = 0.0;
   out_8315920796386777796[253] = 0.0;
   out_8315920796386777796[254] = 0.0;
   out_8315920796386777796[255] = 0.0;
   out_8315920796386777796[256] = 0.0;
   out_8315920796386777796[257] = 0.0;
   out_8315920796386777796[258] = 0.0;
   out_8315920796386777796[259] = 0.0;
   out_8315920796386777796[260] = 0.0;
   out_8315920796386777796[261] = 0.0;
   out_8315920796386777796[262] = 0.0;
   out_8315920796386777796[263] = 0.0;
   out_8315920796386777796[264] = 0.0;
   out_8315920796386777796[265] = 0.0;
   out_8315920796386777796[266] = 1.0;
   out_8315920796386777796[267] = 0.0;
   out_8315920796386777796[268] = 0.0;
   out_8315920796386777796[269] = 0.0;
   out_8315920796386777796[270] = 0.0;
   out_8315920796386777796[271] = 0.0;
   out_8315920796386777796[272] = 0.0;
   out_8315920796386777796[273] = 0.0;
   out_8315920796386777796[274] = 0.0;
   out_8315920796386777796[275] = 0.0;
   out_8315920796386777796[276] = 0.0;
   out_8315920796386777796[277] = 0.0;
   out_8315920796386777796[278] = 0.0;
   out_8315920796386777796[279] = 0.0;
   out_8315920796386777796[280] = 0.0;
   out_8315920796386777796[281] = 0.0;
   out_8315920796386777796[282] = 0.0;
   out_8315920796386777796[283] = 0.0;
   out_8315920796386777796[284] = 0.0;
   out_8315920796386777796[285] = 1.0;
   out_8315920796386777796[286] = 0.0;
   out_8315920796386777796[287] = 0.0;
   out_8315920796386777796[288] = 0.0;
   out_8315920796386777796[289] = 0.0;
   out_8315920796386777796[290] = 0.0;
   out_8315920796386777796[291] = 0.0;
   out_8315920796386777796[292] = 0.0;
   out_8315920796386777796[293] = 0.0;
   out_8315920796386777796[294] = 0.0;
   out_8315920796386777796[295] = 0.0;
   out_8315920796386777796[296] = 0.0;
   out_8315920796386777796[297] = 0.0;
   out_8315920796386777796[298] = 0.0;
   out_8315920796386777796[299] = 0.0;
   out_8315920796386777796[300] = 0.0;
   out_8315920796386777796[301] = 0.0;
   out_8315920796386777796[302] = 0.0;
   out_8315920796386777796[303] = 0.0;
   out_8315920796386777796[304] = 1.0;
   out_8315920796386777796[305] = 0.0;
   out_8315920796386777796[306] = 0.0;
   out_8315920796386777796[307] = 0.0;
   out_8315920796386777796[308] = 0.0;
   out_8315920796386777796[309] = 0.0;
   out_8315920796386777796[310] = 0.0;
   out_8315920796386777796[311] = 0.0;
   out_8315920796386777796[312] = 0.0;
   out_8315920796386777796[313] = 0.0;
   out_8315920796386777796[314] = 0.0;
   out_8315920796386777796[315] = 0.0;
   out_8315920796386777796[316] = 0.0;
   out_8315920796386777796[317] = 0.0;
   out_8315920796386777796[318] = 0.0;
   out_8315920796386777796[319] = 0.0;
   out_8315920796386777796[320] = 0.0;
   out_8315920796386777796[321] = 0.0;
   out_8315920796386777796[322] = 0.0;
   out_8315920796386777796[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1706853749310621885) {
   out_1706853749310621885[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1706853749310621885[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1706853749310621885[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1706853749310621885[3] = dt*state[12] + state[3];
   out_1706853749310621885[4] = dt*state[13] + state[4];
   out_1706853749310621885[5] = dt*state[14] + state[5];
   out_1706853749310621885[6] = state[6];
   out_1706853749310621885[7] = state[7];
   out_1706853749310621885[8] = state[8];
   out_1706853749310621885[9] = state[9];
   out_1706853749310621885[10] = state[10];
   out_1706853749310621885[11] = state[11];
   out_1706853749310621885[12] = state[12];
   out_1706853749310621885[13] = state[13];
   out_1706853749310621885[14] = state[14];
   out_1706853749310621885[15] = state[15];
   out_1706853749310621885[16] = state[16];
   out_1706853749310621885[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3565612569828347872) {
   out_3565612569828347872[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3565612569828347872[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3565612569828347872[2] = 0;
   out_3565612569828347872[3] = 0;
   out_3565612569828347872[4] = 0;
   out_3565612569828347872[5] = 0;
   out_3565612569828347872[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3565612569828347872[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3565612569828347872[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3565612569828347872[9] = 0;
   out_3565612569828347872[10] = 0;
   out_3565612569828347872[11] = 0;
   out_3565612569828347872[12] = 0;
   out_3565612569828347872[13] = 0;
   out_3565612569828347872[14] = 0;
   out_3565612569828347872[15] = 0;
   out_3565612569828347872[16] = 0;
   out_3565612569828347872[17] = 0;
   out_3565612569828347872[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3565612569828347872[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3565612569828347872[20] = 0;
   out_3565612569828347872[21] = 0;
   out_3565612569828347872[22] = 0;
   out_3565612569828347872[23] = 0;
   out_3565612569828347872[24] = 0;
   out_3565612569828347872[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3565612569828347872[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3565612569828347872[27] = 0;
   out_3565612569828347872[28] = 0;
   out_3565612569828347872[29] = 0;
   out_3565612569828347872[30] = 0;
   out_3565612569828347872[31] = 0;
   out_3565612569828347872[32] = 0;
   out_3565612569828347872[33] = 0;
   out_3565612569828347872[34] = 0;
   out_3565612569828347872[35] = 0;
   out_3565612569828347872[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3565612569828347872[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3565612569828347872[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3565612569828347872[39] = 0;
   out_3565612569828347872[40] = 0;
   out_3565612569828347872[41] = 0;
   out_3565612569828347872[42] = 0;
   out_3565612569828347872[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3565612569828347872[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3565612569828347872[45] = 0;
   out_3565612569828347872[46] = 0;
   out_3565612569828347872[47] = 0;
   out_3565612569828347872[48] = 0;
   out_3565612569828347872[49] = 0;
   out_3565612569828347872[50] = 0;
   out_3565612569828347872[51] = 0;
   out_3565612569828347872[52] = 0;
   out_3565612569828347872[53] = 0;
   out_3565612569828347872[54] = 0;
   out_3565612569828347872[55] = 0;
   out_3565612569828347872[56] = 0;
   out_3565612569828347872[57] = 1;
   out_3565612569828347872[58] = 0;
   out_3565612569828347872[59] = 0;
   out_3565612569828347872[60] = 0;
   out_3565612569828347872[61] = 0;
   out_3565612569828347872[62] = 0;
   out_3565612569828347872[63] = 0;
   out_3565612569828347872[64] = 0;
   out_3565612569828347872[65] = 0;
   out_3565612569828347872[66] = dt;
   out_3565612569828347872[67] = 0;
   out_3565612569828347872[68] = 0;
   out_3565612569828347872[69] = 0;
   out_3565612569828347872[70] = 0;
   out_3565612569828347872[71] = 0;
   out_3565612569828347872[72] = 0;
   out_3565612569828347872[73] = 0;
   out_3565612569828347872[74] = 0;
   out_3565612569828347872[75] = 0;
   out_3565612569828347872[76] = 1;
   out_3565612569828347872[77] = 0;
   out_3565612569828347872[78] = 0;
   out_3565612569828347872[79] = 0;
   out_3565612569828347872[80] = 0;
   out_3565612569828347872[81] = 0;
   out_3565612569828347872[82] = 0;
   out_3565612569828347872[83] = 0;
   out_3565612569828347872[84] = 0;
   out_3565612569828347872[85] = dt;
   out_3565612569828347872[86] = 0;
   out_3565612569828347872[87] = 0;
   out_3565612569828347872[88] = 0;
   out_3565612569828347872[89] = 0;
   out_3565612569828347872[90] = 0;
   out_3565612569828347872[91] = 0;
   out_3565612569828347872[92] = 0;
   out_3565612569828347872[93] = 0;
   out_3565612569828347872[94] = 0;
   out_3565612569828347872[95] = 1;
   out_3565612569828347872[96] = 0;
   out_3565612569828347872[97] = 0;
   out_3565612569828347872[98] = 0;
   out_3565612569828347872[99] = 0;
   out_3565612569828347872[100] = 0;
   out_3565612569828347872[101] = 0;
   out_3565612569828347872[102] = 0;
   out_3565612569828347872[103] = 0;
   out_3565612569828347872[104] = dt;
   out_3565612569828347872[105] = 0;
   out_3565612569828347872[106] = 0;
   out_3565612569828347872[107] = 0;
   out_3565612569828347872[108] = 0;
   out_3565612569828347872[109] = 0;
   out_3565612569828347872[110] = 0;
   out_3565612569828347872[111] = 0;
   out_3565612569828347872[112] = 0;
   out_3565612569828347872[113] = 0;
   out_3565612569828347872[114] = 1;
   out_3565612569828347872[115] = 0;
   out_3565612569828347872[116] = 0;
   out_3565612569828347872[117] = 0;
   out_3565612569828347872[118] = 0;
   out_3565612569828347872[119] = 0;
   out_3565612569828347872[120] = 0;
   out_3565612569828347872[121] = 0;
   out_3565612569828347872[122] = 0;
   out_3565612569828347872[123] = 0;
   out_3565612569828347872[124] = 0;
   out_3565612569828347872[125] = 0;
   out_3565612569828347872[126] = 0;
   out_3565612569828347872[127] = 0;
   out_3565612569828347872[128] = 0;
   out_3565612569828347872[129] = 0;
   out_3565612569828347872[130] = 0;
   out_3565612569828347872[131] = 0;
   out_3565612569828347872[132] = 0;
   out_3565612569828347872[133] = 1;
   out_3565612569828347872[134] = 0;
   out_3565612569828347872[135] = 0;
   out_3565612569828347872[136] = 0;
   out_3565612569828347872[137] = 0;
   out_3565612569828347872[138] = 0;
   out_3565612569828347872[139] = 0;
   out_3565612569828347872[140] = 0;
   out_3565612569828347872[141] = 0;
   out_3565612569828347872[142] = 0;
   out_3565612569828347872[143] = 0;
   out_3565612569828347872[144] = 0;
   out_3565612569828347872[145] = 0;
   out_3565612569828347872[146] = 0;
   out_3565612569828347872[147] = 0;
   out_3565612569828347872[148] = 0;
   out_3565612569828347872[149] = 0;
   out_3565612569828347872[150] = 0;
   out_3565612569828347872[151] = 0;
   out_3565612569828347872[152] = 1;
   out_3565612569828347872[153] = 0;
   out_3565612569828347872[154] = 0;
   out_3565612569828347872[155] = 0;
   out_3565612569828347872[156] = 0;
   out_3565612569828347872[157] = 0;
   out_3565612569828347872[158] = 0;
   out_3565612569828347872[159] = 0;
   out_3565612569828347872[160] = 0;
   out_3565612569828347872[161] = 0;
   out_3565612569828347872[162] = 0;
   out_3565612569828347872[163] = 0;
   out_3565612569828347872[164] = 0;
   out_3565612569828347872[165] = 0;
   out_3565612569828347872[166] = 0;
   out_3565612569828347872[167] = 0;
   out_3565612569828347872[168] = 0;
   out_3565612569828347872[169] = 0;
   out_3565612569828347872[170] = 0;
   out_3565612569828347872[171] = 1;
   out_3565612569828347872[172] = 0;
   out_3565612569828347872[173] = 0;
   out_3565612569828347872[174] = 0;
   out_3565612569828347872[175] = 0;
   out_3565612569828347872[176] = 0;
   out_3565612569828347872[177] = 0;
   out_3565612569828347872[178] = 0;
   out_3565612569828347872[179] = 0;
   out_3565612569828347872[180] = 0;
   out_3565612569828347872[181] = 0;
   out_3565612569828347872[182] = 0;
   out_3565612569828347872[183] = 0;
   out_3565612569828347872[184] = 0;
   out_3565612569828347872[185] = 0;
   out_3565612569828347872[186] = 0;
   out_3565612569828347872[187] = 0;
   out_3565612569828347872[188] = 0;
   out_3565612569828347872[189] = 0;
   out_3565612569828347872[190] = 1;
   out_3565612569828347872[191] = 0;
   out_3565612569828347872[192] = 0;
   out_3565612569828347872[193] = 0;
   out_3565612569828347872[194] = 0;
   out_3565612569828347872[195] = 0;
   out_3565612569828347872[196] = 0;
   out_3565612569828347872[197] = 0;
   out_3565612569828347872[198] = 0;
   out_3565612569828347872[199] = 0;
   out_3565612569828347872[200] = 0;
   out_3565612569828347872[201] = 0;
   out_3565612569828347872[202] = 0;
   out_3565612569828347872[203] = 0;
   out_3565612569828347872[204] = 0;
   out_3565612569828347872[205] = 0;
   out_3565612569828347872[206] = 0;
   out_3565612569828347872[207] = 0;
   out_3565612569828347872[208] = 0;
   out_3565612569828347872[209] = 1;
   out_3565612569828347872[210] = 0;
   out_3565612569828347872[211] = 0;
   out_3565612569828347872[212] = 0;
   out_3565612569828347872[213] = 0;
   out_3565612569828347872[214] = 0;
   out_3565612569828347872[215] = 0;
   out_3565612569828347872[216] = 0;
   out_3565612569828347872[217] = 0;
   out_3565612569828347872[218] = 0;
   out_3565612569828347872[219] = 0;
   out_3565612569828347872[220] = 0;
   out_3565612569828347872[221] = 0;
   out_3565612569828347872[222] = 0;
   out_3565612569828347872[223] = 0;
   out_3565612569828347872[224] = 0;
   out_3565612569828347872[225] = 0;
   out_3565612569828347872[226] = 0;
   out_3565612569828347872[227] = 0;
   out_3565612569828347872[228] = 1;
   out_3565612569828347872[229] = 0;
   out_3565612569828347872[230] = 0;
   out_3565612569828347872[231] = 0;
   out_3565612569828347872[232] = 0;
   out_3565612569828347872[233] = 0;
   out_3565612569828347872[234] = 0;
   out_3565612569828347872[235] = 0;
   out_3565612569828347872[236] = 0;
   out_3565612569828347872[237] = 0;
   out_3565612569828347872[238] = 0;
   out_3565612569828347872[239] = 0;
   out_3565612569828347872[240] = 0;
   out_3565612569828347872[241] = 0;
   out_3565612569828347872[242] = 0;
   out_3565612569828347872[243] = 0;
   out_3565612569828347872[244] = 0;
   out_3565612569828347872[245] = 0;
   out_3565612569828347872[246] = 0;
   out_3565612569828347872[247] = 1;
   out_3565612569828347872[248] = 0;
   out_3565612569828347872[249] = 0;
   out_3565612569828347872[250] = 0;
   out_3565612569828347872[251] = 0;
   out_3565612569828347872[252] = 0;
   out_3565612569828347872[253] = 0;
   out_3565612569828347872[254] = 0;
   out_3565612569828347872[255] = 0;
   out_3565612569828347872[256] = 0;
   out_3565612569828347872[257] = 0;
   out_3565612569828347872[258] = 0;
   out_3565612569828347872[259] = 0;
   out_3565612569828347872[260] = 0;
   out_3565612569828347872[261] = 0;
   out_3565612569828347872[262] = 0;
   out_3565612569828347872[263] = 0;
   out_3565612569828347872[264] = 0;
   out_3565612569828347872[265] = 0;
   out_3565612569828347872[266] = 1;
   out_3565612569828347872[267] = 0;
   out_3565612569828347872[268] = 0;
   out_3565612569828347872[269] = 0;
   out_3565612569828347872[270] = 0;
   out_3565612569828347872[271] = 0;
   out_3565612569828347872[272] = 0;
   out_3565612569828347872[273] = 0;
   out_3565612569828347872[274] = 0;
   out_3565612569828347872[275] = 0;
   out_3565612569828347872[276] = 0;
   out_3565612569828347872[277] = 0;
   out_3565612569828347872[278] = 0;
   out_3565612569828347872[279] = 0;
   out_3565612569828347872[280] = 0;
   out_3565612569828347872[281] = 0;
   out_3565612569828347872[282] = 0;
   out_3565612569828347872[283] = 0;
   out_3565612569828347872[284] = 0;
   out_3565612569828347872[285] = 1;
   out_3565612569828347872[286] = 0;
   out_3565612569828347872[287] = 0;
   out_3565612569828347872[288] = 0;
   out_3565612569828347872[289] = 0;
   out_3565612569828347872[290] = 0;
   out_3565612569828347872[291] = 0;
   out_3565612569828347872[292] = 0;
   out_3565612569828347872[293] = 0;
   out_3565612569828347872[294] = 0;
   out_3565612569828347872[295] = 0;
   out_3565612569828347872[296] = 0;
   out_3565612569828347872[297] = 0;
   out_3565612569828347872[298] = 0;
   out_3565612569828347872[299] = 0;
   out_3565612569828347872[300] = 0;
   out_3565612569828347872[301] = 0;
   out_3565612569828347872[302] = 0;
   out_3565612569828347872[303] = 0;
   out_3565612569828347872[304] = 1;
   out_3565612569828347872[305] = 0;
   out_3565612569828347872[306] = 0;
   out_3565612569828347872[307] = 0;
   out_3565612569828347872[308] = 0;
   out_3565612569828347872[309] = 0;
   out_3565612569828347872[310] = 0;
   out_3565612569828347872[311] = 0;
   out_3565612569828347872[312] = 0;
   out_3565612569828347872[313] = 0;
   out_3565612569828347872[314] = 0;
   out_3565612569828347872[315] = 0;
   out_3565612569828347872[316] = 0;
   out_3565612569828347872[317] = 0;
   out_3565612569828347872[318] = 0;
   out_3565612569828347872[319] = 0;
   out_3565612569828347872[320] = 0;
   out_3565612569828347872[321] = 0;
   out_3565612569828347872[322] = 0;
   out_3565612569828347872[323] = 1;
}
void h_4(double *state, double *unused, double *out_6256833977858620129) {
   out_6256833977858620129[0] = state[6] + state[9];
   out_6256833977858620129[1] = state[7] + state[10];
   out_6256833977858620129[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_7117973314503879692) {
   out_7117973314503879692[0] = 0;
   out_7117973314503879692[1] = 0;
   out_7117973314503879692[2] = 0;
   out_7117973314503879692[3] = 0;
   out_7117973314503879692[4] = 0;
   out_7117973314503879692[5] = 0;
   out_7117973314503879692[6] = 1;
   out_7117973314503879692[7] = 0;
   out_7117973314503879692[8] = 0;
   out_7117973314503879692[9] = 1;
   out_7117973314503879692[10] = 0;
   out_7117973314503879692[11] = 0;
   out_7117973314503879692[12] = 0;
   out_7117973314503879692[13] = 0;
   out_7117973314503879692[14] = 0;
   out_7117973314503879692[15] = 0;
   out_7117973314503879692[16] = 0;
   out_7117973314503879692[17] = 0;
   out_7117973314503879692[18] = 0;
   out_7117973314503879692[19] = 0;
   out_7117973314503879692[20] = 0;
   out_7117973314503879692[21] = 0;
   out_7117973314503879692[22] = 0;
   out_7117973314503879692[23] = 0;
   out_7117973314503879692[24] = 0;
   out_7117973314503879692[25] = 1;
   out_7117973314503879692[26] = 0;
   out_7117973314503879692[27] = 0;
   out_7117973314503879692[28] = 1;
   out_7117973314503879692[29] = 0;
   out_7117973314503879692[30] = 0;
   out_7117973314503879692[31] = 0;
   out_7117973314503879692[32] = 0;
   out_7117973314503879692[33] = 0;
   out_7117973314503879692[34] = 0;
   out_7117973314503879692[35] = 0;
   out_7117973314503879692[36] = 0;
   out_7117973314503879692[37] = 0;
   out_7117973314503879692[38] = 0;
   out_7117973314503879692[39] = 0;
   out_7117973314503879692[40] = 0;
   out_7117973314503879692[41] = 0;
   out_7117973314503879692[42] = 0;
   out_7117973314503879692[43] = 0;
   out_7117973314503879692[44] = 1;
   out_7117973314503879692[45] = 0;
   out_7117973314503879692[46] = 0;
   out_7117973314503879692[47] = 1;
   out_7117973314503879692[48] = 0;
   out_7117973314503879692[49] = 0;
   out_7117973314503879692[50] = 0;
   out_7117973314503879692[51] = 0;
   out_7117973314503879692[52] = 0;
   out_7117973314503879692[53] = 0;
}
void h_10(double *state, double *unused, double *out_8339904701560037775) {
   out_8339904701560037775[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8339904701560037775[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8339904701560037775[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_4285286583568518818) {
   out_4285286583568518818[0] = 0;
   out_4285286583568518818[1] = 9.8100000000000005*cos(state[1]);
   out_4285286583568518818[2] = 0;
   out_4285286583568518818[3] = 0;
   out_4285286583568518818[4] = -state[8];
   out_4285286583568518818[5] = state[7];
   out_4285286583568518818[6] = 0;
   out_4285286583568518818[7] = state[5];
   out_4285286583568518818[8] = -state[4];
   out_4285286583568518818[9] = 0;
   out_4285286583568518818[10] = 0;
   out_4285286583568518818[11] = 0;
   out_4285286583568518818[12] = 1;
   out_4285286583568518818[13] = 0;
   out_4285286583568518818[14] = 0;
   out_4285286583568518818[15] = 1;
   out_4285286583568518818[16] = 0;
   out_4285286583568518818[17] = 0;
   out_4285286583568518818[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_4285286583568518818[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_4285286583568518818[20] = 0;
   out_4285286583568518818[21] = state[8];
   out_4285286583568518818[22] = 0;
   out_4285286583568518818[23] = -state[6];
   out_4285286583568518818[24] = -state[5];
   out_4285286583568518818[25] = 0;
   out_4285286583568518818[26] = state[3];
   out_4285286583568518818[27] = 0;
   out_4285286583568518818[28] = 0;
   out_4285286583568518818[29] = 0;
   out_4285286583568518818[30] = 0;
   out_4285286583568518818[31] = 1;
   out_4285286583568518818[32] = 0;
   out_4285286583568518818[33] = 0;
   out_4285286583568518818[34] = 1;
   out_4285286583568518818[35] = 0;
   out_4285286583568518818[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_4285286583568518818[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_4285286583568518818[38] = 0;
   out_4285286583568518818[39] = -state[7];
   out_4285286583568518818[40] = state[6];
   out_4285286583568518818[41] = 0;
   out_4285286583568518818[42] = state[4];
   out_4285286583568518818[43] = -state[3];
   out_4285286583568518818[44] = 0;
   out_4285286583568518818[45] = 0;
   out_4285286583568518818[46] = 0;
   out_4285286583568518818[47] = 0;
   out_4285286583568518818[48] = 0;
   out_4285286583568518818[49] = 0;
   out_4285286583568518818[50] = 1;
   out_4285286583568518818[51] = 0;
   out_4285286583568518818[52] = 0;
   out_4285286583568518818[53] = 1;
}
void h_13(double *state, double *unused, double *out_4092510433385355744) {
   out_4092510433385355744[0] = state[3];
   out_4092510433385355744[1] = state[4];
   out_4092510433385355744[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3905699489171546891) {
   out_3905699489171546891[0] = 0;
   out_3905699489171546891[1] = 0;
   out_3905699489171546891[2] = 0;
   out_3905699489171546891[3] = 1;
   out_3905699489171546891[4] = 0;
   out_3905699489171546891[5] = 0;
   out_3905699489171546891[6] = 0;
   out_3905699489171546891[7] = 0;
   out_3905699489171546891[8] = 0;
   out_3905699489171546891[9] = 0;
   out_3905699489171546891[10] = 0;
   out_3905699489171546891[11] = 0;
   out_3905699489171546891[12] = 0;
   out_3905699489171546891[13] = 0;
   out_3905699489171546891[14] = 0;
   out_3905699489171546891[15] = 0;
   out_3905699489171546891[16] = 0;
   out_3905699489171546891[17] = 0;
   out_3905699489171546891[18] = 0;
   out_3905699489171546891[19] = 0;
   out_3905699489171546891[20] = 0;
   out_3905699489171546891[21] = 0;
   out_3905699489171546891[22] = 1;
   out_3905699489171546891[23] = 0;
   out_3905699489171546891[24] = 0;
   out_3905699489171546891[25] = 0;
   out_3905699489171546891[26] = 0;
   out_3905699489171546891[27] = 0;
   out_3905699489171546891[28] = 0;
   out_3905699489171546891[29] = 0;
   out_3905699489171546891[30] = 0;
   out_3905699489171546891[31] = 0;
   out_3905699489171546891[32] = 0;
   out_3905699489171546891[33] = 0;
   out_3905699489171546891[34] = 0;
   out_3905699489171546891[35] = 0;
   out_3905699489171546891[36] = 0;
   out_3905699489171546891[37] = 0;
   out_3905699489171546891[38] = 0;
   out_3905699489171546891[39] = 0;
   out_3905699489171546891[40] = 0;
   out_3905699489171546891[41] = 1;
   out_3905699489171546891[42] = 0;
   out_3905699489171546891[43] = 0;
   out_3905699489171546891[44] = 0;
   out_3905699489171546891[45] = 0;
   out_3905699489171546891[46] = 0;
   out_3905699489171546891[47] = 0;
   out_3905699489171546891[48] = 0;
   out_3905699489171546891[49] = 0;
   out_3905699489171546891[50] = 0;
   out_3905699489171546891[51] = 0;
   out_3905699489171546891[52] = 0;
   out_3905699489171546891[53] = 0;
}
void h_14(double *state, double *unused, double *out_1965285751179212564) {
   out_1965285751179212564[0] = state[6];
   out_1965285751179212564[1] = state[7];
   out_1965285751179212564[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8245982326910299628) {
   out_8245982326910299628[0] = 0;
   out_8245982326910299628[1] = 0;
   out_8245982326910299628[2] = 0;
   out_8245982326910299628[3] = 0;
   out_8245982326910299628[4] = 0;
   out_8245982326910299628[5] = 0;
   out_8245982326910299628[6] = 1;
   out_8245982326910299628[7] = 0;
   out_8245982326910299628[8] = 0;
   out_8245982326910299628[9] = 0;
   out_8245982326910299628[10] = 0;
   out_8245982326910299628[11] = 0;
   out_8245982326910299628[12] = 0;
   out_8245982326910299628[13] = 0;
   out_8245982326910299628[14] = 0;
   out_8245982326910299628[15] = 0;
   out_8245982326910299628[16] = 0;
   out_8245982326910299628[17] = 0;
   out_8245982326910299628[18] = 0;
   out_8245982326910299628[19] = 0;
   out_8245982326910299628[20] = 0;
   out_8245982326910299628[21] = 0;
   out_8245982326910299628[22] = 0;
   out_8245982326910299628[23] = 0;
   out_8245982326910299628[24] = 0;
   out_8245982326910299628[25] = 1;
   out_8245982326910299628[26] = 0;
   out_8245982326910299628[27] = 0;
   out_8245982326910299628[28] = 0;
   out_8245982326910299628[29] = 0;
   out_8245982326910299628[30] = 0;
   out_8245982326910299628[31] = 0;
   out_8245982326910299628[32] = 0;
   out_8245982326910299628[33] = 0;
   out_8245982326910299628[34] = 0;
   out_8245982326910299628[35] = 0;
   out_8245982326910299628[36] = 0;
   out_8245982326910299628[37] = 0;
   out_8245982326910299628[38] = 0;
   out_8245982326910299628[39] = 0;
   out_8245982326910299628[40] = 0;
   out_8245982326910299628[41] = 0;
   out_8245982326910299628[42] = 0;
   out_8245982326910299628[43] = 0;
   out_8245982326910299628[44] = 1;
   out_8245982326910299628[45] = 0;
   out_8245982326910299628[46] = 0;
   out_8245982326910299628[47] = 0;
   out_8245982326910299628[48] = 0;
   out_8245982326910299628[49] = 0;
   out_8245982326910299628[50] = 0;
   out_8245982326910299628[51] = 0;
   out_8245982326910299628[52] = 0;
   out_8245982326910299628[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_327274557709511665) {
  err_fun(nom_x, delta_x, out_327274557709511665);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4344179942375735738) {
  inv_err_fun(nom_x, true_x, out_4344179942375735738);
}
void pose_H_mod_fun(double *state, double *out_8315920796386777796) {
  H_mod_fun(state, out_8315920796386777796);
}
void pose_f_fun(double *state, double dt, double *out_1706853749310621885) {
  f_fun(state,  dt, out_1706853749310621885);
}
void pose_F_fun(double *state, double dt, double *out_3565612569828347872) {
  F_fun(state,  dt, out_3565612569828347872);
}
void pose_h_4(double *state, double *unused, double *out_6256833977858620129) {
  h_4(state, unused, out_6256833977858620129);
}
void pose_H_4(double *state, double *unused, double *out_7117973314503879692) {
  H_4(state, unused, out_7117973314503879692);
}
void pose_h_10(double *state, double *unused, double *out_8339904701560037775) {
  h_10(state, unused, out_8339904701560037775);
}
void pose_H_10(double *state, double *unused, double *out_4285286583568518818) {
  H_10(state, unused, out_4285286583568518818);
}
void pose_h_13(double *state, double *unused, double *out_4092510433385355744) {
  h_13(state, unused, out_4092510433385355744);
}
void pose_H_13(double *state, double *unused, double *out_3905699489171546891) {
  H_13(state, unused, out_3905699489171546891);
}
void pose_h_14(double *state, double *unused, double *out_1965285751179212564) {
  h_14(state, unused, out_1965285751179212564);
}
void pose_H_14(double *state, double *unused, double *out_8245982326910299628) {
  H_14(state, unused, out_8245982326910299628);
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
