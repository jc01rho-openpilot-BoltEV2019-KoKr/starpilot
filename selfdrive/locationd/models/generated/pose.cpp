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
void err_fun(double *nom_x, double *delta_x, double *out_2551549382290402050) {
   out_2551549382290402050[0] = delta_x[0] + nom_x[0];
   out_2551549382290402050[1] = delta_x[1] + nom_x[1];
   out_2551549382290402050[2] = delta_x[2] + nom_x[2];
   out_2551549382290402050[3] = delta_x[3] + nom_x[3];
   out_2551549382290402050[4] = delta_x[4] + nom_x[4];
   out_2551549382290402050[5] = delta_x[5] + nom_x[5];
   out_2551549382290402050[6] = delta_x[6] + nom_x[6];
   out_2551549382290402050[7] = delta_x[7] + nom_x[7];
   out_2551549382290402050[8] = delta_x[8] + nom_x[8];
   out_2551549382290402050[9] = delta_x[9] + nom_x[9];
   out_2551549382290402050[10] = delta_x[10] + nom_x[10];
   out_2551549382290402050[11] = delta_x[11] + nom_x[11];
   out_2551549382290402050[12] = delta_x[12] + nom_x[12];
   out_2551549382290402050[13] = delta_x[13] + nom_x[13];
   out_2551549382290402050[14] = delta_x[14] + nom_x[14];
   out_2551549382290402050[15] = delta_x[15] + nom_x[15];
   out_2551549382290402050[16] = delta_x[16] + nom_x[16];
   out_2551549382290402050[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3575109948453160374) {
   out_3575109948453160374[0] = -nom_x[0] + true_x[0];
   out_3575109948453160374[1] = -nom_x[1] + true_x[1];
   out_3575109948453160374[2] = -nom_x[2] + true_x[2];
   out_3575109948453160374[3] = -nom_x[3] + true_x[3];
   out_3575109948453160374[4] = -nom_x[4] + true_x[4];
   out_3575109948453160374[5] = -nom_x[5] + true_x[5];
   out_3575109948453160374[6] = -nom_x[6] + true_x[6];
   out_3575109948453160374[7] = -nom_x[7] + true_x[7];
   out_3575109948453160374[8] = -nom_x[8] + true_x[8];
   out_3575109948453160374[9] = -nom_x[9] + true_x[9];
   out_3575109948453160374[10] = -nom_x[10] + true_x[10];
   out_3575109948453160374[11] = -nom_x[11] + true_x[11];
   out_3575109948453160374[12] = -nom_x[12] + true_x[12];
   out_3575109948453160374[13] = -nom_x[13] + true_x[13];
   out_3575109948453160374[14] = -nom_x[14] + true_x[14];
   out_3575109948453160374[15] = -nom_x[15] + true_x[15];
   out_3575109948453160374[16] = -nom_x[16] + true_x[16];
   out_3575109948453160374[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_2954011976512996711) {
   out_2954011976512996711[0] = 1.0;
   out_2954011976512996711[1] = 0.0;
   out_2954011976512996711[2] = 0.0;
   out_2954011976512996711[3] = 0.0;
   out_2954011976512996711[4] = 0.0;
   out_2954011976512996711[5] = 0.0;
   out_2954011976512996711[6] = 0.0;
   out_2954011976512996711[7] = 0.0;
   out_2954011976512996711[8] = 0.0;
   out_2954011976512996711[9] = 0.0;
   out_2954011976512996711[10] = 0.0;
   out_2954011976512996711[11] = 0.0;
   out_2954011976512996711[12] = 0.0;
   out_2954011976512996711[13] = 0.0;
   out_2954011976512996711[14] = 0.0;
   out_2954011976512996711[15] = 0.0;
   out_2954011976512996711[16] = 0.0;
   out_2954011976512996711[17] = 0.0;
   out_2954011976512996711[18] = 0.0;
   out_2954011976512996711[19] = 1.0;
   out_2954011976512996711[20] = 0.0;
   out_2954011976512996711[21] = 0.0;
   out_2954011976512996711[22] = 0.0;
   out_2954011976512996711[23] = 0.0;
   out_2954011976512996711[24] = 0.0;
   out_2954011976512996711[25] = 0.0;
   out_2954011976512996711[26] = 0.0;
   out_2954011976512996711[27] = 0.0;
   out_2954011976512996711[28] = 0.0;
   out_2954011976512996711[29] = 0.0;
   out_2954011976512996711[30] = 0.0;
   out_2954011976512996711[31] = 0.0;
   out_2954011976512996711[32] = 0.0;
   out_2954011976512996711[33] = 0.0;
   out_2954011976512996711[34] = 0.0;
   out_2954011976512996711[35] = 0.0;
   out_2954011976512996711[36] = 0.0;
   out_2954011976512996711[37] = 0.0;
   out_2954011976512996711[38] = 1.0;
   out_2954011976512996711[39] = 0.0;
   out_2954011976512996711[40] = 0.0;
   out_2954011976512996711[41] = 0.0;
   out_2954011976512996711[42] = 0.0;
   out_2954011976512996711[43] = 0.0;
   out_2954011976512996711[44] = 0.0;
   out_2954011976512996711[45] = 0.0;
   out_2954011976512996711[46] = 0.0;
   out_2954011976512996711[47] = 0.0;
   out_2954011976512996711[48] = 0.0;
   out_2954011976512996711[49] = 0.0;
   out_2954011976512996711[50] = 0.0;
   out_2954011976512996711[51] = 0.0;
   out_2954011976512996711[52] = 0.0;
   out_2954011976512996711[53] = 0.0;
   out_2954011976512996711[54] = 0.0;
   out_2954011976512996711[55] = 0.0;
   out_2954011976512996711[56] = 0.0;
   out_2954011976512996711[57] = 1.0;
   out_2954011976512996711[58] = 0.0;
   out_2954011976512996711[59] = 0.0;
   out_2954011976512996711[60] = 0.0;
   out_2954011976512996711[61] = 0.0;
   out_2954011976512996711[62] = 0.0;
   out_2954011976512996711[63] = 0.0;
   out_2954011976512996711[64] = 0.0;
   out_2954011976512996711[65] = 0.0;
   out_2954011976512996711[66] = 0.0;
   out_2954011976512996711[67] = 0.0;
   out_2954011976512996711[68] = 0.0;
   out_2954011976512996711[69] = 0.0;
   out_2954011976512996711[70] = 0.0;
   out_2954011976512996711[71] = 0.0;
   out_2954011976512996711[72] = 0.0;
   out_2954011976512996711[73] = 0.0;
   out_2954011976512996711[74] = 0.0;
   out_2954011976512996711[75] = 0.0;
   out_2954011976512996711[76] = 1.0;
   out_2954011976512996711[77] = 0.0;
   out_2954011976512996711[78] = 0.0;
   out_2954011976512996711[79] = 0.0;
   out_2954011976512996711[80] = 0.0;
   out_2954011976512996711[81] = 0.0;
   out_2954011976512996711[82] = 0.0;
   out_2954011976512996711[83] = 0.0;
   out_2954011976512996711[84] = 0.0;
   out_2954011976512996711[85] = 0.0;
   out_2954011976512996711[86] = 0.0;
   out_2954011976512996711[87] = 0.0;
   out_2954011976512996711[88] = 0.0;
   out_2954011976512996711[89] = 0.0;
   out_2954011976512996711[90] = 0.0;
   out_2954011976512996711[91] = 0.0;
   out_2954011976512996711[92] = 0.0;
   out_2954011976512996711[93] = 0.0;
   out_2954011976512996711[94] = 0.0;
   out_2954011976512996711[95] = 1.0;
   out_2954011976512996711[96] = 0.0;
   out_2954011976512996711[97] = 0.0;
   out_2954011976512996711[98] = 0.0;
   out_2954011976512996711[99] = 0.0;
   out_2954011976512996711[100] = 0.0;
   out_2954011976512996711[101] = 0.0;
   out_2954011976512996711[102] = 0.0;
   out_2954011976512996711[103] = 0.0;
   out_2954011976512996711[104] = 0.0;
   out_2954011976512996711[105] = 0.0;
   out_2954011976512996711[106] = 0.0;
   out_2954011976512996711[107] = 0.0;
   out_2954011976512996711[108] = 0.0;
   out_2954011976512996711[109] = 0.0;
   out_2954011976512996711[110] = 0.0;
   out_2954011976512996711[111] = 0.0;
   out_2954011976512996711[112] = 0.0;
   out_2954011976512996711[113] = 0.0;
   out_2954011976512996711[114] = 1.0;
   out_2954011976512996711[115] = 0.0;
   out_2954011976512996711[116] = 0.0;
   out_2954011976512996711[117] = 0.0;
   out_2954011976512996711[118] = 0.0;
   out_2954011976512996711[119] = 0.0;
   out_2954011976512996711[120] = 0.0;
   out_2954011976512996711[121] = 0.0;
   out_2954011976512996711[122] = 0.0;
   out_2954011976512996711[123] = 0.0;
   out_2954011976512996711[124] = 0.0;
   out_2954011976512996711[125] = 0.0;
   out_2954011976512996711[126] = 0.0;
   out_2954011976512996711[127] = 0.0;
   out_2954011976512996711[128] = 0.0;
   out_2954011976512996711[129] = 0.0;
   out_2954011976512996711[130] = 0.0;
   out_2954011976512996711[131] = 0.0;
   out_2954011976512996711[132] = 0.0;
   out_2954011976512996711[133] = 1.0;
   out_2954011976512996711[134] = 0.0;
   out_2954011976512996711[135] = 0.0;
   out_2954011976512996711[136] = 0.0;
   out_2954011976512996711[137] = 0.0;
   out_2954011976512996711[138] = 0.0;
   out_2954011976512996711[139] = 0.0;
   out_2954011976512996711[140] = 0.0;
   out_2954011976512996711[141] = 0.0;
   out_2954011976512996711[142] = 0.0;
   out_2954011976512996711[143] = 0.0;
   out_2954011976512996711[144] = 0.0;
   out_2954011976512996711[145] = 0.0;
   out_2954011976512996711[146] = 0.0;
   out_2954011976512996711[147] = 0.0;
   out_2954011976512996711[148] = 0.0;
   out_2954011976512996711[149] = 0.0;
   out_2954011976512996711[150] = 0.0;
   out_2954011976512996711[151] = 0.0;
   out_2954011976512996711[152] = 1.0;
   out_2954011976512996711[153] = 0.0;
   out_2954011976512996711[154] = 0.0;
   out_2954011976512996711[155] = 0.0;
   out_2954011976512996711[156] = 0.0;
   out_2954011976512996711[157] = 0.0;
   out_2954011976512996711[158] = 0.0;
   out_2954011976512996711[159] = 0.0;
   out_2954011976512996711[160] = 0.0;
   out_2954011976512996711[161] = 0.0;
   out_2954011976512996711[162] = 0.0;
   out_2954011976512996711[163] = 0.0;
   out_2954011976512996711[164] = 0.0;
   out_2954011976512996711[165] = 0.0;
   out_2954011976512996711[166] = 0.0;
   out_2954011976512996711[167] = 0.0;
   out_2954011976512996711[168] = 0.0;
   out_2954011976512996711[169] = 0.0;
   out_2954011976512996711[170] = 0.0;
   out_2954011976512996711[171] = 1.0;
   out_2954011976512996711[172] = 0.0;
   out_2954011976512996711[173] = 0.0;
   out_2954011976512996711[174] = 0.0;
   out_2954011976512996711[175] = 0.0;
   out_2954011976512996711[176] = 0.0;
   out_2954011976512996711[177] = 0.0;
   out_2954011976512996711[178] = 0.0;
   out_2954011976512996711[179] = 0.0;
   out_2954011976512996711[180] = 0.0;
   out_2954011976512996711[181] = 0.0;
   out_2954011976512996711[182] = 0.0;
   out_2954011976512996711[183] = 0.0;
   out_2954011976512996711[184] = 0.0;
   out_2954011976512996711[185] = 0.0;
   out_2954011976512996711[186] = 0.0;
   out_2954011976512996711[187] = 0.0;
   out_2954011976512996711[188] = 0.0;
   out_2954011976512996711[189] = 0.0;
   out_2954011976512996711[190] = 1.0;
   out_2954011976512996711[191] = 0.0;
   out_2954011976512996711[192] = 0.0;
   out_2954011976512996711[193] = 0.0;
   out_2954011976512996711[194] = 0.0;
   out_2954011976512996711[195] = 0.0;
   out_2954011976512996711[196] = 0.0;
   out_2954011976512996711[197] = 0.0;
   out_2954011976512996711[198] = 0.0;
   out_2954011976512996711[199] = 0.0;
   out_2954011976512996711[200] = 0.0;
   out_2954011976512996711[201] = 0.0;
   out_2954011976512996711[202] = 0.0;
   out_2954011976512996711[203] = 0.0;
   out_2954011976512996711[204] = 0.0;
   out_2954011976512996711[205] = 0.0;
   out_2954011976512996711[206] = 0.0;
   out_2954011976512996711[207] = 0.0;
   out_2954011976512996711[208] = 0.0;
   out_2954011976512996711[209] = 1.0;
   out_2954011976512996711[210] = 0.0;
   out_2954011976512996711[211] = 0.0;
   out_2954011976512996711[212] = 0.0;
   out_2954011976512996711[213] = 0.0;
   out_2954011976512996711[214] = 0.0;
   out_2954011976512996711[215] = 0.0;
   out_2954011976512996711[216] = 0.0;
   out_2954011976512996711[217] = 0.0;
   out_2954011976512996711[218] = 0.0;
   out_2954011976512996711[219] = 0.0;
   out_2954011976512996711[220] = 0.0;
   out_2954011976512996711[221] = 0.0;
   out_2954011976512996711[222] = 0.0;
   out_2954011976512996711[223] = 0.0;
   out_2954011976512996711[224] = 0.0;
   out_2954011976512996711[225] = 0.0;
   out_2954011976512996711[226] = 0.0;
   out_2954011976512996711[227] = 0.0;
   out_2954011976512996711[228] = 1.0;
   out_2954011976512996711[229] = 0.0;
   out_2954011976512996711[230] = 0.0;
   out_2954011976512996711[231] = 0.0;
   out_2954011976512996711[232] = 0.0;
   out_2954011976512996711[233] = 0.0;
   out_2954011976512996711[234] = 0.0;
   out_2954011976512996711[235] = 0.0;
   out_2954011976512996711[236] = 0.0;
   out_2954011976512996711[237] = 0.0;
   out_2954011976512996711[238] = 0.0;
   out_2954011976512996711[239] = 0.0;
   out_2954011976512996711[240] = 0.0;
   out_2954011976512996711[241] = 0.0;
   out_2954011976512996711[242] = 0.0;
   out_2954011976512996711[243] = 0.0;
   out_2954011976512996711[244] = 0.0;
   out_2954011976512996711[245] = 0.0;
   out_2954011976512996711[246] = 0.0;
   out_2954011976512996711[247] = 1.0;
   out_2954011976512996711[248] = 0.0;
   out_2954011976512996711[249] = 0.0;
   out_2954011976512996711[250] = 0.0;
   out_2954011976512996711[251] = 0.0;
   out_2954011976512996711[252] = 0.0;
   out_2954011976512996711[253] = 0.0;
   out_2954011976512996711[254] = 0.0;
   out_2954011976512996711[255] = 0.0;
   out_2954011976512996711[256] = 0.0;
   out_2954011976512996711[257] = 0.0;
   out_2954011976512996711[258] = 0.0;
   out_2954011976512996711[259] = 0.0;
   out_2954011976512996711[260] = 0.0;
   out_2954011976512996711[261] = 0.0;
   out_2954011976512996711[262] = 0.0;
   out_2954011976512996711[263] = 0.0;
   out_2954011976512996711[264] = 0.0;
   out_2954011976512996711[265] = 0.0;
   out_2954011976512996711[266] = 1.0;
   out_2954011976512996711[267] = 0.0;
   out_2954011976512996711[268] = 0.0;
   out_2954011976512996711[269] = 0.0;
   out_2954011976512996711[270] = 0.0;
   out_2954011976512996711[271] = 0.0;
   out_2954011976512996711[272] = 0.0;
   out_2954011976512996711[273] = 0.0;
   out_2954011976512996711[274] = 0.0;
   out_2954011976512996711[275] = 0.0;
   out_2954011976512996711[276] = 0.0;
   out_2954011976512996711[277] = 0.0;
   out_2954011976512996711[278] = 0.0;
   out_2954011976512996711[279] = 0.0;
   out_2954011976512996711[280] = 0.0;
   out_2954011976512996711[281] = 0.0;
   out_2954011976512996711[282] = 0.0;
   out_2954011976512996711[283] = 0.0;
   out_2954011976512996711[284] = 0.0;
   out_2954011976512996711[285] = 1.0;
   out_2954011976512996711[286] = 0.0;
   out_2954011976512996711[287] = 0.0;
   out_2954011976512996711[288] = 0.0;
   out_2954011976512996711[289] = 0.0;
   out_2954011976512996711[290] = 0.0;
   out_2954011976512996711[291] = 0.0;
   out_2954011976512996711[292] = 0.0;
   out_2954011976512996711[293] = 0.0;
   out_2954011976512996711[294] = 0.0;
   out_2954011976512996711[295] = 0.0;
   out_2954011976512996711[296] = 0.0;
   out_2954011976512996711[297] = 0.0;
   out_2954011976512996711[298] = 0.0;
   out_2954011976512996711[299] = 0.0;
   out_2954011976512996711[300] = 0.0;
   out_2954011976512996711[301] = 0.0;
   out_2954011976512996711[302] = 0.0;
   out_2954011976512996711[303] = 0.0;
   out_2954011976512996711[304] = 1.0;
   out_2954011976512996711[305] = 0.0;
   out_2954011976512996711[306] = 0.0;
   out_2954011976512996711[307] = 0.0;
   out_2954011976512996711[308] = 0.0;
   out_2954011976512996711[309] = 0.0;
   out_2954011976512996711[310] = 0.0;
   out_2954011976512996711[311] = 0.0;
   out_2954011976512996711[312] = 0.0;
   out_2954011976512996711[313] = 0.0;
   out_2954011976512996711[314] = 0.0;
   out_2954011976512996711[315] = 0.0;
   out_2954011976512996711[316] = 0.0;
   out_2954011976512996711[317] = 0.0;
   out_2954011976512996711[318] = 0.0;
   out_2954011976512996711[319] = 0.0;
   out_2954011976512996711[320] = 0.0;
   out_2954011976512996711[321] = 0.0;
   out_2954011976512996711[322] = 0.0;
   out_2954011976512996711[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4081841541460951824) {
   out_4081841541460951824[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4081841541460951824[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4081841541460951824[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4081841541460951824[3] = dt*state[12] + state[3];
   out_4081841541460951824[4] = dt*state[13] + state[4];
   out_4081841541460951824[5] = dt*state[14] + state[5];
   out_4081841541460951824[6] = state[6];
   out_4081841541460951824[7] = state[7];
   out_4081841541460951824[8] = state[8];
   out_4081841541460951824[9] = state[9];
   out_4081841541460951824[10] = state[10];
   out_4081841541460951824[11] = state[11];
   out_4081841541460951824[12] = state[12];
   out_4081841541460951824[13] = state[13];
   out_4081841541460951824[14] = state[14];
   out_4081841541460951824[15] = state[15];
   out_4081841541460951824[16] = state[16];
   out_4081841541460951824[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2326707394449301144) {
   out_2326707394449301144[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2326707394449301144[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2326707394449301144[2] = 0;
   out_2326707394449301144[3] = 0;
   out_2326707394449301144[4] = 0;
   out_2326707394449301144[5] = 0;
   out_2326707394449301144[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2326707394449301144[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2326707394449301144[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2326707394449301144[9] = 0;
   out_2326707394449301144[10] = 0;
   out_2326707394449301144[11] = 0;
   out_2326707394449301144[12] = 0;
   out_2326707394449301144[13] = 0;
   out_2326707394449301144[14] = 0;
   out_2326707394449301144[15] = 0;
   out_2326707394449301144[16] = 0;
   out_2326707394449301144[17] = 0;
   out_2326707394449301144[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2326707394449301144[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2326707394449301144[20] = 0;
   out_2326707394449301144[21] = 0;
   out_2326707394449301144[22] = 0;
   out_2326707394449301144[23] = 0;
   out_2326707394449301144[24] = 0;
   out_2326707394449301144[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2326707394449301144[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2326707394449301144[27] = 0;
   out_2326707394449301144[28] = 0;
   out_2326707394449301144[29] = 0;
   out_2326707394449301144[30] = 0;
   out_2326707394449301144[31] = 0;
   out_2326707394449301144[32] = 0;
   out_2326707394449301144[33] = 0;
   out_2326707394449301144[34] = 0;
   out_2326707394449301144[35] = 0;
   out_2326707394449301144[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2326707394449301144[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2326707394449301144[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2326707394449301144[39] = 0;
   out_2326707394449301144[40] = 0;
   out_2326707394449301144[41] = 0;
   out_2326707394449301144[42] = 0;
   out_2326707394449301144[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2326707394449301144[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2326707394449301144[45] = 0;
   out_2326707394449301144[46] = 0;
   out_2326707394449301144[47] = 0;
   out_2326707394449301144[48] = 0;
   out_2326707394449301144[49] = 0;
   out_2326707394449301144[50] = 0;
   out_2326707394449301144[51] = 0;
   out_2326707394449301144[52] = 0;
   out_2326707394449301144[53] = 0;
   out_2326707394449301144[54] = 0;
   out_2326707394449301144[55] = 0;
   out_2326707394449301144[56] = 0;
   out_2326707394449301144[57] = 1;
   out_2326707394449301144[58] = 0;
   out_2326707394449301144[59] = 0;
   out_2326707394449301144[60] = 0;
   out_2326707394449301144[61] = 0;
   out_2326707394449301144[62] = 0;
   out_2326707394449301144[63] = 0;
   out_2326707394449301144[64] = 0;
   out_2326707394449301144[65] = 0;
   out_2326707394449301144[66] = dt;
   out_2326707394449301144[67] = 0;
   out_2326707394449301144[68] = 0;
   out_2326707394449301144[69] = 0;
   out_2326707394449301144[70] = 0;
   out_2326707394449301144[71] = 0;
   out_2326707394449301144[72] = 0;
   out_2326707394449301144[73] = 0;
   out_2326707394449301144[74] = 0;
   out_2326707394449301144[75] = 0;
   out_2326707394449301144[76] = 1;
   out_2326707394449301144[77] = 0;
   out_2326707394449301144[78] = 0;
   out_2326707394449301144[79] = 0;
   out_2326707394449301144[80] = 0;
   out_2326707394449301144[81] = 0;
   out_2326707394449301144[82] = 0;
   out_2326707394449301144[83] = 0;
   out_2326707394449301144[84] = 0;
   out_2326707394449301144[85] = dt;
   out_2326707394449301144[86] = 0;
   out_2326707394449301144[87] = 0;
   out_2326707394449301144[88] = 0;
   out_2326707394449301144[89] = 0;
   out_2326707394449301144[90] = 0;
   out_2326707394449301144[91] = 0;
   out_2326707394449301144[92] = 0;
   out_2326707394449301144[93] = 0;
   out_2326707394449301144[94] = 0;
   out_2326707394449301144[95] = 1;
   out_2326707394449301144[96] = 0;
   out_2326707394449301144[97] = 0;
   out_2326707394449301144[98] = 0;
   out_2326707394449301144[99] = 0;
   out_2326707394449301144[100] = 0;
   out_2326707394449301144[101] = 0;
   out_2326707394449301144[102] = 0;
   out_2326707394449301144[103] = 0;
   out_2326707394449301144[104] = dt;
   out_2326707394449301144[105] = 0;
   out_2326707394449301144[106] = 0;
   out_2326707394449301144[107] = 0;
   out_2326707394449301144[108] = 0;
   out_2326707394449301144[109] = 0;
   out_2326707394449301144[110] = 0;
   out_2326707394449301144[111] = 0;
   out_2326707394449301144[112] = 0;
   out_2326707394449301144[113] = 0;
   out_2326707394449301144[114] = 1;
   out_2326707394449301144[115] = 0;
   out_2326707394449301144[116] = 0;
   out_2326707394449301144[117] = 0;
   out_2326707394449301144[118] = 0;
   out_2326707394449301144[119] = 0;
   out_2326707394449301144[120] = 0;
   out_2326707394449301144[121] = 0;
   out_2326707394449301144[122] = 0;
   out_2326707394449301144[123] = 0;
   out_2326707394449301144[124] = 0;
   out_2326707394449301144[125] = 0;
   out_2326707394449301144[126] = 0;
   out_2326707394449301144[127] = 0;
   out_2326707394449301144[128] = 0;
   out_2326707394449301144[129] = 0;
   out_2326707394449301144[130] = 0;
   out_2326707394449301144[131] = 0;
   out_2326707394449301144[132] = 0;
   out_2326707394449301144[133] = 1;
   out_2326707394449301144[134] = 0;
   out_2326707394449301144[135] = 0;
   out_2326707394449301144[136] = 0;
   out_2326707394449301144[137] = 0;
   out_2326707394449301144[138] = 0;
   out_2326707394449301144[139] = 0;
   out_2326707394449301144[140] = 0;
   out_2326707394449301144[141] = 0;
   out_2326707394449301144[142] = 0;
   out_2326707394449301144[143] = 0;
   out_2326707394449301144[144] = 0;
   out_2326707394449301144[145] = 0;
   out_2326707394449301144[146] = 0;
   out_2326707394449301144[147] = 0;
   out_2326707394449301144[148] = 0;
   out_2326707394449301144[149] = 0;
   out_2326707394449301144[150] = 0;
   out_2326707394449301144[151] = 0;
   out_2326707394449301144[152] = 1;
   out_2326707394449301144[153] = 0;
   out_2326707394449301144[154] = 0;
   out_2326707394449301144[155] = 0;
   out_2326707394449301144[156] = 0;
   out_2326707394449301144[157] = 0;
   out_2326707394449301144[158] = 0;
   out_2326707394449301144[159] = 0;
   out_2326707394449301144[160] = 0;
   out_2326707394449301144[161] = 0;
   out_2326707394449301144[162] = 0;
   out_2326707394449301144[163] = 0;
   out_2326707394449301144[164] = 0;
   out_2326707394449301144[165] = 0;
   out_2326707394449301144[166] = 0;
   out_2326707394449301144[167] = 0;
   out_2326707394449301144[168] = 0;
   out_2326707394449301144[169] = 0;
   out_2326707394449301144[170] = 0;
   out_2326707394449301144[171] = 1;
   out_2326707394449301144[172] = 0;
   out_2326707394449301144[173] = 0;
   out_2326707394449301144[174] = 0;
   out_2326707394449301144[175] = 0;
   out_2326707394449301144[176] = 0;
   out_2326707394449301144[177] = 0;
   out_2326707394449301144[178] = 0;
   out_2326707394449301144[179] = 0;
   out_2326707394449301144[180] = 0;
   out_2326707394449301144[181] = 0;
   out_2326707394449301144[182] = 0;
   out_2326707394449301144[183] = 0;
   out_2326707394449301144[184] = 0;
   out_2326707394449301144[185] = 0;
   out_2326707394449301144[186] = 0;
   out_2326707394449301144[187] = 0;
   out_2326707394449301144[188] = 0;
   out_2326707394449301144[189] = 0;
   out_2326707394449301144[190] = 1;
   out_2326707394449301144[191] = 0;
   out_2326707394449301144[192] = 0;
   out_2326707394449301144[193] = 0;
   out_2326707394449301144[194] = 0;
   out_2326707394449301144[195] = 0;
   out_2326707394449301144[196] = 0;
   out_2326707394449301144[197] = 0;
   out_2326707394449301144[198] = 0;
   out_2326707394449301144[199] = 0;
   out_2326707394449301144[200] = 0;
   out_2326707394449301144[201] = 0;
   out_2326707394449301144[202] = 0;
   out_2326707394449301144[203] = 0;
   out_2326707394449301144[204] = 0;
   out_2326707394449301144[205] = 0;
   out_2326707394449301144[206] = 0;
   out_2326707394449301144[207] = 0;
   out_2326707394449301144[208] = 0;
   out_2326707394449301144[209] = 1;
   out_2326707394449301144[210] = 0;
   out_2326707394449301144[211] = 0;
   out_2326707394449301144[212] = 0;
   out_2326707394449301144[213] = 0;
   out_2326707394449301144[214] = 0;
   out_2326707394449301144[215] = 0;
   out_2326707394449301144[216] = 0;
   out_2326707394449301144[217] = 0;
   out_2326707394449301144[218] = 0;
   out_2326707394449301144[219] = 0;
   out_2326707394449301144[220] = 0;
   out_2326707394449301144[221] = 0;
   out_2326707394449301144[222] = 0;
   out_2326707394449301144[223] = 0;
   out_2326707394449301144[224] = 0;
   out_2326707394449301144[225] = 0;
   out_2326707394449301144[226] = 0;
   out_2326707394449301144[227] = 0;
   out_2326707394449301144[228] = 1;
   out_2326707394449301144[229] = 0;
   out_2326707394449301144[230] = 0;
   out_2326707394449301144[231] = 0;
   out_2326707394449301144[232] = 0;
   out_2326707394449301144[233] = 0;
   out_2326707394449301144[234] = 0;
   out_2326707394449301144[235] = 0;
   out_2326707394449301144[236] = 0;
   out_2326707394449301144[237] = 0;
   out_2326707394449301144[238] = 0;
   out_2326707394449301144[239] = 0;
   out_2326707394449301144[240] = 0;
   out_2326707394449301144[241] = 0;
   out_2326707394449301144[242] = 0;
   out_2326707394449301144[243] = 0;
   out_2326707394449301144[244] = 0;
   out_2326707394449301144[245] = 0;
   out_2326707394449301144[246] = 0;
   out_2326707394449301144[247] = 1;
   out_2326707394449301144[248] = 0;
   out_2326707394449301144[249] = 0;
   out_2326707394449301144[250] = 0;
   out_2326707394449301144[251] = 0;
   out_2326707394449301144[252] = 0;
   out_2326707394449301144[253] = 0;
   out_2326707394449301144[254] = 0;
   out_2326707394449301144[255] = 0;
   out_2326707394449301144[256] = 0;
   out_2326707394449301144[257] = 0;
   out_2326707394449301144[258] = 0;
   out_2326707394449301144[259] = 0;
   out_2326707394449301144[260] = 0;
   out_2326707394449301144[261] = 0;
   out_2326707394449301144[262] = 0;
   out_2326707394449301144[263] = 0;
   out_2326707394449301144[264] = 0;
   out_2326707394449301144[265] = 0;
   out_2326707394449301144[266] = 1;
   out_2326707394449301144[267] = 0;
   out_2326707394449301144[268] = 0;
   out_2326707394449301144[269] = 0;
   out_2326707394449301144[270] = 0;
   out_2326707394449301144[271] = 0;
   out_2326707394449301144[272] = 0;
   out_2326707394449301144[273] = 0;
   out_2326707394449301144[274] = 0;
   out_2326707394449301144[275] = 0;
   out_2326707394449301144[276] = 0;
   out_2326707394449301144[277] = 0;
   out_2326707394449301144[278] = 0;
   out_2326707394449301144[279] = 0;
   out_2326707394449301144[280] = 0;
   out_2326707394449301144[281] = 0;
   out_2326707394449301144[282] = 0;
   out_2326707394449301144[283] = 0;
   out_2326707394449301144[284] = 0;
   out_2326707394449301144[285] = 1;
   out_2326707394449301144[286] = 0;
   out_2326707394449301144[287] = 0;
   out_2326707394449301144[288] = 0;
   out_2326707394449301144[289] = 0;
   out_2326707394449301144[290] = 0;
   out_2326707394449301144[291] = 0;
   out_2326707394449301144[292] = 0;
   out_2326707394449301144[293] = 0;
   out_2326707394449301144[294] = 0;
   out_2326707394449301144[295] = 0;
   out_2326707394449301144[296] = 0;
   out_2326707394449301144[297] = 0;
   out_2326707394449301144[298] = 0;
   out_2326707394449301144[299] = 0;
   out_2326707394449301144[300] = 0;
   out_2326707394449301144[301] = 0;
   out_2326707394449301144[302] = 0;
   out_2326707394449301144[303] = 0;
   out_2326707394449301144[304] = 1;
   out_2326707394449301144[305] = 0;
   out_2326707394449301144[306] = 0;
   out_2326707394449301144[307] = 0;
   out_2326707394449301144[308] = 0;
   out_2326707394449301144[309] = 0;
   out_2326707394449301144[310] = 0;
   out_2326707394449301144[311] = 0;
   out_2326707394449301144[312] = 0;
   out_2326707394449301144[313] = 0;
   out_2326707394449301144[314] = 0;
   out_2326707394449301144[315] = 0;
   out_2326707394449301144[316] = 0;
   out_2326707394449301144[317] = 0;
   out_2326707394449301144[318] = 0;
   out_2326707394449301144[319] = 0;
   out_2326707394449301144[320] = 0;
   out_2326707394449301144[321] = 0;
   out_2326707394449301144[322] = 0;
   out_2326707394449301144[323] = 1;
}
void h_4(double *state, double *unused, double *out_5242858642703077087) {
   out_5242858642703077087[0] = state[6] + state[9];
   out_5242858642703077087[1] = state[7] + state[10];
   out_5242858642703077087[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1660615060416319653) {
   out_1660615060416319653[0] = 0;
   out_1660615060416319653[1] = 0;
   out_1660615060416319653[2] = 0;
   out_1660615060416319653[3] = 0;
   out_1660615060416319653[4] = 0;
   out_1660615060416319653[5] = 0;
   out_1660615060416319653[6] = 1;
   out_1660615060416319653[7] = 0;
   out_1660615060416319653[8] = 0;
   out_1660615060416319653[9] = 1;
   out_1660615060416319653[10] = 0;
   out_1660615060416319653[11] = 0;
   out_1660615060416319653[12] = 0;
   out_1660615060416319653[13] = 0;
   out_1660615060416319653[14] = 0;
   out_1660615060416319653[15] = 0;
   out_1660615060416319653[16] = 0;
   out_1660615060416319653[17] = 0;
   out_1660615060416319653[18] = 0;
   out_1660615060416319653[19] = 0;
   out_1660615060416319653[20] = 0;
   out_1660615060416319653[21] = 0;
   out_1660615060416319653[22] = 0;
   out_1660615060416319653[23] = 0;
   out_1660615060416319653[24] = 0;
   out_1660615060416319653[25] = 1;
   out_1660615060416319653[26] = 0;
   out_1660615060416319653[27] = 0;
   out_1660615060416319653[28] = 1;
   out_1660615060416319653[29] = 0;
   out_1660615060416319653[30] = 0;
   out_1660615060416319653[31] = 0;
   out_1660615060416319653[32] = 0;
   out_1660615060416319653[33] = 0;
   out_1660615060416319653[34] = 0;
   out_1660615060416319653[35] = 0;
   out_1660615060416319653[36] = 0;
   out_1660615060416319653[37] = 0;
   out_1660615060416319653[38] = 0;
   out_1660615060416319653[39] = 0;
   out_1660615060416319653[40] = 0;
   out_1660615060416319653[41] = 0;
   out_1660615060416319653[42] = 0;
   out_1660615060416319653[43] = 0;
   out_1660615060416319653[44] = 1;
   out_1660615060416319653[45] = 0;
   out_1660615060416319653[46] = 0;
   out_1660615060416319653[47] = 1;
   out_1660615060416319653[48] = 0;
   out_1660615060416319653[49] = 0;
   out_1660615060416319653[50] = 0;
   out_1660615060416319653[51] = 0;
   out_1660615060416319653[52] = 0;
   out_1660615060416319653[53] = 0;
}
void h_10(double *state, double *unused, double *out_8287724405821980303) {
   out_8287724405821980303[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8287724405821980303[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8287724405821980303[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8634670991932313772) {
   out_8634670991932313772[0] = 0;
   out_8634670991932313772[1] = 9.8100000000000005*cos(state[1]);
   out_8634670991932313772[2] = 0;
   out_8634670991932313772[3] = 0;
   out_8634670991932313772[4] = -state[8];
   out_8634670991932313772[5] = state[7];
   out_8634670991932313772[6] = 0;
   out_8634670991932313772[7] = state[5];
   out_8634670991932313772[8] = -state[4];
   out_8634670991932313772[9] = 0;
   out_8634670991932313772[10] = 0;
   out_8634670991932313772[11] = 0;
   out_8634670991932313772[12] = 1;
   out_8634670991932313772[13] = 0;
   out_8634670991932313772[14] = 0;
   out_8634670991932313772[15] = 1;
   out_8634670991932313772[16] = 0;
   out_8634670991932313772[17] = 0;
   out_8634670991932313772[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8634670991932313772[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8634670991932313772[20] = 0;
   out_8634670991932313772[21] = state[8];
   out_8634670991932313772[22] = 0;
   out_8634670991932313772[23] = -state[6];
   out_8634670991932313772[24] = -state[5];
   out_8634670991932313772[25] = 0;
   out_8634670991932313772[26] = state[3];
   out_8634670991932313772[27] = 0;
   out_8634670991932313772[28] = 0;
   out_8634670991932313772[29] = 0;
   out_8634670991932313772[30] = 0;
   out_8634670991932313772[31] = 1;
   out_8634670991932313772[32] = 0;
   out_8634670991932313772[33] = 0;
   out_8634670991932313772[34] = 1;
   out_8634670991932313772[35] = 0;
   out_8634670991932313772[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8634670991932313772[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8634670991932313772[38] = 0;
   out_8634670991932313772[39] = -state[7];
   out_8634670991932313772[40] = state[6];
   out_8634670991932313772[41] = 0;
   out_8634670991932313772[42] = state[4];
   out_8634670991932313772[43] = -state[3];
   out_8634670991932313772[44] = 0;
   out_8634670991932313772[45] = 0;
   out_8634670991932313772[46] = 0;
   out_8634670991932313772[47] = 0;
   out_8634670991932313772[48] = 0;
   out_8634670991932313772[49] = 0;
   out_8634670991932313772[50] = 1;
   out_8634670991932313772[51] = 0;
   out_8634670991932313772[52] = 0;
   out_8634670991932313772[53] = 1;
}
void h_13(double *state, double *unused, double *out_936388540160520926) {
   out_936388540160520926[0] = state[3];
   out_936388540160520926[1] = state[4];
   out_936388540160520926[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4872888885748652454) {
   out_4872888885748652454[0] = 0;
   out_4872888885748652454[1] = 0;
   out_4872888885748652454[2] = 0;
   out_4872888885748652454[3] = 1;
   out_4872888885748652454[4] = 0;
   out_4872888885748652454[5] = 0;
   out_4872888885748652454[6] = 0;
   out_4872888885748652454[7] = 0;
   out_4872888885748652454[8] = 0;
   out_4872888885748652454[9] = 0;
   out_4872888885748652454[10] = 0;
   out_4872888885748652454[11] = 0;
   out_4872888885748652454[12] = 0;
   out_4872888885748652454[13] = 0;
   out_4872888885748652454[14] = 0;
   out_4872888885748652454[15] = 0;
   out_4872888885748652454[16] = 0;
   out_4872888885748652454[17] = 0;
   out_4872888885748652454[18] = 0;
   out_4872888885748652454[19] = 0;
   out_4872888885748652454[20] = 0;
   out_4872888885748652454[21] = 0;
   out_4872888885748652454[22] = 1;
   out_4872888885748652454[23] = 0;
   out_4872888885748652454[24] = 0;
   out_4872888885748652454[25] = 0;
   out_4872888885748652454[26] = 0;
   out_4872888885748652454[27] = 0;
   out_4872888885748652454[28] = 0;
   out_4872888885748652454[29] = 0;
   out_4872888885748652454[30] = 0;
   out_4872888885748652454[31] = 0;
   out_4872888885748652454[32] = 0;
   out_4872888885748652454[33] = 0;
   out_4872888885748652454[34] = 0;
   out_4872888885748652454[35] = 0;
   out_4872888885748652454[36] = 0;
   out_4872888885748652454[37] = 0;
   out_4872888885748652454[38] = 0;
   out_4872888885748652454[39] = 0;
   out_4872888885748652454[40] = 0;
   out_4872888885748652454[41] = 1;
   out_4872888885748652454[42] = 0;
   out_4872888885748652454[43] = 0;
   out_4872888885748652454[44] = 0;
   out_4872888885748652454[45] = 0;
   out_4872888885748652454[46] = 0;
   out_4872888885748652454[47] = 0;
   out_4872888885748652454[48] = 0;
   out_4872888885748652454[49] = 0;
   out_4872888885748652454[50] = 0;
   out_4872888885748652454[51] = 0;
   out_4872888885748652454[52] = 0;
   out_4872888885748652454[53] = 0;
}
void h_14(double *state, double *unused, double *out_3784911557802666238) {
   out_3784911557802666238[0] = state[6];
   out_3784911557802666238[1] = state[7];
   out_3784911557802666238[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5623855916755804182) {
   out_5623855916755804182[0] = 0;
   out_5623855916755804182[1] = 0;
   out_5623855916755804182[2] = 0;
   out_5623855916755804182[3] = 0;
   out_5623855916755804182[4] = 0;
   out_5623855916755804182[5] = 0;
   out_5623855916755804182[6] = 1;
   out_5623855916755804182[7] = 0;
   out_5623855916755804182[8] = 0;
   out_5623855916755804182[9] = 0;
   out_5623855916755804182[10] = 0;
   out_5623855916755804182[11] = 0;
   out_5623855916755804182[12] = 0;
   out_5623855916755804182[13] = 0;
   out_5623855916755804182[14] = 0;
   out_5623855916755804182[15] = 0;
   out_5623855916755804182[16] = 0;
   out_5623855916755804182[17] = 0;
   out_5623855916755804182[18] = 0;
   out_5623855916755804182[19] = 0;
   out_5623855916755804182[20] = 0;
   out_5623855916755804182[21] = 0;
   out_5623855916755804182[22] = 0;
   out_5623855916755804182[23] = 0;
   out_5623855916755804182[24] = 0;
   out_5623855916755804182[25] = 1;
   out_5623855916755804182[26] = 0;
   out_5623855916755804182[27] = 0;
   out_5623855916755804182[28] = 0;
   out_5623855916755804182[29] = 0;
   out_5623855916755804182[30] = 0;
   out_5623855916755804182[31] = 0;
   out_5623855916755804182[32] = 0;
   out_5623855916755804182[33] = 0;
   out_5623855916755804182[34] = 0;
   out_5623855916755804182[35] = 0;
   out_5623855916755804182[36] = 0;
   out_5623855916755804182[37] = 0;
   out_5623855916755804182[38] = 0;
   out_5623855916755804182[39] = 0;
   out_5623855916755804182[40] = 0;
   out_5623855916755804182[41] = 0;
   out_5623855916755804182[42] = 0;
   out_5623855916755804182[43] = 0;
   out_5623855916755804182[44] = 1;
   out_5623855916755804182[45] = 0;
   out_5623855916755804182[46] = 0;
   out_5623855916755804182[47] = 0;
   out_5623855916755804182[48] = 0;
   out_5623855916755804182[49] = 0;
   out_5623855916755804182[50] = 0;
   out_5623855916755804182[51] = 0;
   out_5623855916755804182[52] = 0;
   out_5623855916755804182[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_2551549382290402050) {
  err_fun(nom_x, delta_x, out_2551549382290402050);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3575109948453160374) {
  inv_err_fun(nom_x, true_x, out_3575109948453160374);
}
void pose_H_mod_fun(double *state, double *out_2954011976512996711) {
  H_mod_fun(state, out_2954011976512996711);
}
void pose_f_fun(double *state, double dt, double *out_4081841541460951824) {
  f_fun(state,  dt, out_4081841541460951824);
}
void pose_F_fun(double *state, double dt, double *out_2326707394449301144) {
  F_fun(state,  dt, out_2326707394449301144);
}
void pose_h_4(double *state, double *unused, double *out_5242858642703077087) {
  h_4(state, unused, out_5242858642703077087);
}
void pose_H_4(double *state, double *unused, double *out_1660615060416319653) {
  H_4(state, unused, out_1660615060416319653);
}
void pose_h_10(double *state, double *unused, double *out_8287724405821980303) {
  h_10(state, unused, out_8287724405821980303);
}
void pose_H_10(double *state, double *unused, double *out_8634670991932313772) {
  H_10(state, unused, out_8634670991932313772);
}
void pose_h_13(double *state, double *unused, double *out_936388540160520926) {
  h_13(state, unused, out_936388540160520926);
}
void pose_H_13(double *state, double *unused, double *out_4872888885748652454) {
  H_13(state, unused, out_4872888885748652454);
}
void pose_h_14(double *state, double *unused, double *out_3784911557802666238) {
  h_14(state, unused, out_3784911557802666238);
}
void pose_H_14(double *state, double *unused, double *out_5623855916755804182) {
  H_14(state, unused, out_5623855916755804182);
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
