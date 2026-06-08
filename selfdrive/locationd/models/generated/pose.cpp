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
void err_fun(double *nom_x, double *delta_x, double *out_8979246808243312501) {
   out_8979246808243312501[0] = delta_x[0] + nom_x[0];
   out_8979246808243312501[1] = delta_x[1] + nom_x[1];
   out_8979246808243312501[2] = delta_x[2] + nom_x[2];
   out_8979246808243312501[3] = delta_x[3] + nom_x[3];
   out_8979246808243312501[4] = delta_x[4] + nom_x[4];
   out_8979246808243312501[5] = delta_x[5] + nom_x[5];
   out_8979246808243312501[6] = delta_x[6] + nom_x[6];
   out_8979246808243312501[7] = delta_x[7] + nom_x[7];
   out_8979246808243312501[8] = delta_x[8] + nom_x[8];
   out_8979246808243312501[9] = delta_x[9] + nom_x[9];
   out_8979246808243312501[10] = delta_x[10] + nom_x[10];
   out_8979246808243312501[11] = delta_x[11] + nom_x[11];
   out_8979246808243312501[12] = delta_x[12] + nom_x[12];
   out_8979246808243312501[13] = delta_x[13] + nom_x[13];
   out_8979246808243312501[14] = delta_x[14] + nom_x[14];
   out_8979246808243312501[15] = delta_x[15] + nom_x[15];
   out_8979246808243312501[16] = delta_x[16] + nom_x[16];
   out_8979246808243312501[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6182129478777519212) {
   out_6182129478777519212[0] = -nom_x[0] + true_x[0];
   out_6182129478777519212[1] = -nom_x[1] + true_x[1];
   out_6182129478777519212[2] = -nom_x[2] + true_x[2];
   out_6182129478777519212[3] = -nom_x[3] + true_x[3];
   out_6182129478777519212[4] = -nom_x[4] + true_x[4];
   out_6182129478777519212[5] = -nom_x[5] + true_x[5];
   out_6182129478777519212[6] = -nom_x[6] + true_x[6];
   out_6182129478777519212[7] = -nom_x[7] + true_x[7];
   out_6182129478777519212[8] = -nom_x[8] + true_x[8];
   out_6182129478777519212[9] = -nom_x[9] + true_x[9];
   out_6182129478777519212[10] = -nom_x[10] + true_x[10];
   out_6182129478777519212[11] = -nom_x[11] + true_x[11];
   out_6182129478777519212[12] = -nom_x[12] + true_x[12];
   out_6182129478777519212[13] = -nom_x[13] + true_x[13];
   out_6182129478777519212[14] = -nom_x[14] + true_x[14];
   out_6182129478777519212[15] = -nom_x[15] + true_x[15];
   out_6182129478777519212[16] = -nom_x[16] + true_x[16];
   out_6182129478777519212[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5496809482113736276) {
   out_5496809482113736276[0] = 1.0;
   out_5496809482113736276[1] = 0.0;
   out_5496809482113736276[2] = 0.0;
   out_5496809482113736276[3] = 0.0;
   out_5496809482113736276[4] = 0.0;
   out_5496809482113736276[5] = 0.0;
   out_5496809482113736276[6] = 0.0;
   out_5496809482113736276[7] = 0.0;
   out_5496809482113736276[8] = 0.0;
   out_5496809482113736276[9] = 0.0;
   out_5496809482113736276[10] = 0.0;
   out_5496809482113736276[11] = 0.0;
   out_5496809482113736276[12] = 0.0;
   out_5496809482113736276[13] = 0.0;
   out_5496809482113736276[14] = 0.0;
   out_5496809482113736276[15] = 0.0;
   out_5496809482113736276[16] = 0.0;
   out_5496809482113736276[17] = 0.0;
   out_5496809482113736276[18] = 0.0;
   out_5496809482113736276[19] = 1.0;
   out_5496809482113736276[20] = 0.0;
   out_5496809482113736276[21] = 0.0;
   out_5496809482113736276[22] = 0.0;
   out_5496809482113736276[23] = 0.0;
   out_5496809482113736276[24] = 0.0;
   out_5496809482113736276[25] = 0.0;
   out_5496809482113736276[26] = 0.0;
   out_5496809482113736276[27] = 0.0;
   out_5496809482113736276[28] = 0.0;
   out_5496809482113736276[29] = 0.0;
   out_5496809482113736276[30] = 0.0;
   out_5496809482113736276[31] = 0.0;
   out_5496809482113736276[32] = 0.0;
   out_5496809482113736276[33] = 0.0;
   out_5496809482113736276[34] = 0.0;
   out_5496809482113736276[35] = 0.0;
   out_5496809482113736276[36] = 0.0;
   out_5496809482113736276[37] = 0.0;
   out_5496809482113736276[38] = 1.0;
   out_5496809482113736276[39] = 0.0;
   out_5496809482113736276[40] = 0.0;
   out_5496809482113736276[41] = 0.0;
   out_5496809482113736276[42] = 0.0;
   out_5496809482113736276[43] = 0.0;
   out_5496809482113736276[44] = 0.0;
   out_5496809482113736276[45] = 0.0;
   out_5496809482113736276[46] = 0.0;
   out_5496809482113736276[47] = 0.0;
   out_5496809482113736276[48] = 0.0;
   out_5496809482113736276[49] = 0.0;
   out_5496809482113736276[50] = 0.0;
   out_5496809482113736276[51] = 0.0;
   out_5496809482113736276[52] = 0.0;
   out_5496809482113736276[53] = 0.0;
   out_5496809482113736276[54] = 0.0;
   out_5496809482113736276[55] = 0.0;
   out_5496809482113736276[56] = 0.0;
   out_5496809482113736276[57] = 1.0;
   out_5496809482113736276[58] = 0.0;
   out_5496809482113736276[59] = 0.0;
   out_5496809482113736276[60] = 0.0;
   out_5496809482113736276[61] = 0.0;
   out_5496809482113736276[62] = 0.0;
   out_5496809482113736276[63] = 0.0;
   out_5496809482113736276[64] = 0.0;
   out_5496809482113736276[65] = 0.0;
   out_5496809482113736276[66] = 0.0;
   out_5496809482113736276[67] = 0.0;
   out_5496809482113736276[68] = 0.0;
   out_5496809482113736276[69] = 0.0;
   out_5496809482113736276[70] = 0.0;
   out_5496809482113736276[71] = 0.0;
   out_5496809482113736276[72] = 0.0;
   out_5496809482113736276[73] = 0.0;
   out_5496809482113736276[74] = 0.0;
   out_5496809482113736276[75] = 0.0;
   out_5496809482113736276[76] = 1.0;
   out_5496809482113736276[77] = 0.0;
   out_5496809482113736276[78] = 0.0;
   out_5496809482113736276[79] = 0.0;
   out_5496809482113736276[80] = 0.0;
   out_5496809482113736276[81] = 0.0;
   out_5496809482113736276[82] = 0.0;
   out_5496809482113736276[83] = 0.0;
   out_5496809482113736276[84] = 0.0;
   out_5496809482113736276[85] = 0.0;
   out_5496809482113736276[86] = 0.0;
   out_5496809482113736276[87] = 0.0;
   out_5496809482113736276[88] = 0.0;
   out_5496809482113736276[89] = 0.0;
   out_5496809482113736276[90] = 0.0;
   out_5496809482113736276[91] = 0.0;
   out_5496809482113736276[92] = 0.0;
   out_5496809482113736276[93] = 0.0;
   out_5496809482113736276[94] = 0.0;
   out_5496809482113736276[95] = 1.0;
   out_5496809482113736276[96] = 0.0;
   out_5496809482113736276[97] = 0.0;
   out_5496809482113736276[98] = 0.0;
   out_5496809482113736276[99] = 0.0;
   out_5496809482113736276[100] = 0.0;
   out_5496809482113736276[101] = 0.0;
   out_5496809482113736276[102] = 0.0;
   out_5496809482113736276[103] = 0.0;
   out_5496809482113736276[104] = 0.0;
   out_5496809482113736276[105] = 0.0;
   out_5496809482113736276[106] = 0.0;
   out_5496809482113736276[107] = 0.0;
   out_5496809482113736276[108] = 0.0;
   out_5496809482113736276[109] = 0.0;
   out_5496809482113736276[110] = 0.0;
   out_5496809482113736276[111] = 0.0;
   out_5496809482113736276[112] = 0.0;
   out_5496809482113736276[113] = 0.0;
   out_5496809482113736276[114] = 1.0;
   out_5496809482113736276[115] = 0.0;
   out_5496809482113736276[116] = 0.0;
   out_5496809482113736276[117] = 0.0;
   out_5496809482113736276[118] = 0.0;
   out_5496809482113736276[119] = 0.0;
   out_5496809482113736276[120] = 0.0;
   out_5496809482113736276[121] = 0.0;
   out_5496809482113736276[122] = 0.0;
   out_5496809482113736276[123] = 0.0;
   out_5496809482113736276[124] = 0.0;
   out_5496809482113736276[125] = 0.0;
   out_5496809482113736276[126] = 0.0;
   out_5496809482113736276[127] = 0.0;
   out_5496809482113736276[128] = 0.0;
   out_5496809482113736276[129] = 0.0;
   out_5496809482113736276[130] = 0.0;
   out_5496809482113736276[131] = 0.0;
   out_5496809482113736276[132] = 0.0;
   out_5496809482113736276[133] = 1.0;
   out_5496809482113736276[134] = 0.0;
   out_5496809482113736276[135] = 0.0;
   out_5496809482113736276[136] = 0.0;
   out_5496809482113736276[137] = 0.0;
   out_5496809482113736276[138] = 0.0;
   out_5496809482113736276[139] = 0.0;
   out_5496809482113736276[140] = 0.0;
   out_5496809482113736276[141] = 0.0;
   out_5496809482113736276[142] = 0.0;
   out_5496809482113736276[143] = 0.0;
   out_5496809482113736276[144] = 0.0;
   out_5496809482113736276[145] = 0.0;
   out_5496809482113736276[146] = 0.0;
   out_5496809482113736276[147] = 0.0;
   out_5496809482113736276[148] = 0.0;
   out_5496809482113736276[149] = 0.0;
   out_5496809482113736276[150] = 0.0;
   out_5496809482113736276[151] = 0.0;
   out_5496809482113736276[152] = 1.0;
   out_5496809482113736276[153] = 0.0;
   out_5496809482113736276[154] = 0.0;
   out_5496809482113736276[155] = 0.0;
   out_5496809482113736276[156] = 0.0;
   out_5496809482113736276[157] = 0.0;
   out_5496809482113736276[158] = 0.0;
   out_5496809482113736276[159] = 0.0;
   out_5496809482113736276[160] = 0.0;
   out_5496809482113736276[161] = 0.0;
   out_5496809482113736276[162] = 0.0;
   out_5496809482113736276[163] = 0.0;
   out_5496809482113736276[164] = 0.0;
   out_5496809482113736276[165] = 0.0;
   out_5496809482113736276[166] = 0.0;
   out_5496809482113736276[167] = 0.0;
   out_5496809482113736276[168] = 0.0;
   out_5496809482113736276[169] = 0.0;
   out_5496809482113736276[170] = 0.0;
   out_5496809482113736276[171] = 1.0;
   out_5496809482113736276[172] = 0.0;
   out_5496809482113736276[173] = 0.0;
   out_5496809482113736276[174] = 0.0;
   out_5496809482113736276[175] = 0.0;
   out_5496809482113736276[176] = 0.0;
   out_5496809482113736276[177] = 0.0;
   out_5496809482113736276[178] = 0.0;
   out_5496809482113736276[179] = 0.0;
   out_5496809482113736276[180] = 0.0;
   out_5496809482113736276[181] = 0.0;
   out_5496809482113736276[182] = 0.0;
   out_5496809482113736276[183] = 0.0;
   out_5496809482113736276[184] = 0.0;
   out_5496809482113736276[185] = 0.0;
   out_5496809482113736276[186] = 0.0;
   out_5496809482113736276[187] = 0.0;
   out_5496809482113736276[188] = 0.0;
   out_5496809482113736276[189] = 0.0;
   out_5496809482113736276[190] = 1.0;
   out_5496809482113736276[191] = 0.0;
   out_5496809482113736276[192] = 0.0;
   out_5496809482113736276[193] = 0.0;
   out_5496809482113736276[194] = 0.0;
   out_5496809482113736276[195] = 0.0;
   out_5496809482113736276[196] = 0.0;
   out_5496809482113736276[197] = 0.0;
   out_5496809482113736276[198] = 0.0;
   out_5496809482113736276[199] = 0.0;
   out_5496809482113736276[200] = 0.0;
   out_5496809482113736276[201] = 0.0;
   out_5496809482113736276[202] = 0.0;
   out_5496809482113736276[203] = 0.0;
   out_5496809482113736276[204] = 0.0;
   out_5496809482113736276[205] = 0.0;
   out_5496809482113736276[206] = 0.0;
   out_5496809482113736276[207] = 0.0;
   out_5496809482113736276[208] = 0.0;
   out_5496809482113736276[209] = 1.0;
   out_5496809482113736276[210] = 0.0;
   out_5496809482113736276[211] = 0.0;
   out_5496809482113736276[212] = 0.0;
   out_5496809482113736276[213] = 0.0;
   out_5496809482113736276[214] = 0.0;
   out_5496809482113736276[215] = 0.0;
   out_5496809482113736276[216] = 0.0;
   out_5496809482113736276[217] = 0.0;
   out_5496809482113736276[218] = 0.0;
   out_5496809482113736276[219] = 0.0;
   out_5496809482113736276[220] = 0.0;
   out_5496809482113736276[221] = 0.0;
   out_5496809482113736276[222] = 0.0;
   out_5496809482113736276[223] = 0.0;
   out_5496809482113736276[224] = 0.0;
   out_5496809482113736276[225] = 0.0;
   out_5496809482113736276[226] = 0.0;
   out_5496809482113736276[227] = 0.0;
   out_5496809482113736276[228] = 1.0;
   out_5496809482113736276[229] = 0.0;
   out_5496809482113736276[230] = 0.0;
   out_5496809482113736276[231] = 0.0;
   out_5496809482113736276[232] = 0.0;
   out_5496809482113736276[233] = 0.0;
   out_5496809482113736276[234] = 0.0;
   out_5496809482113736276[235] = 0.0;
   out_5496809482113736276[236] = 0.0;
   out_5496809482113736276[237] = 0.0;
   out_5496809482113736276[238] = 0.0;
   out_5496809482113736276[239] = 0.0;
   out_5496809482113736276[240] = 0.0;
   out_5496809482113736276[241] = 0.0;
   out_5496809482113736276[242] = 0.0;
   out_5496809482113736276[243] = 0.0;
   out_5496809482113736276[244] = 0.0;
   out_5496809482113736276[245] = 0.0;
   out_5496809482113736276[246] = 0.0;
   out_5496809482113736276[247] = 1.0;
   out_5496809482113736276[248] = 0.0;
   out_5496809482113736276[249] = 0.0;
   out_5496809482113736276[250] = 0.0;
   out_5496809482113736276[251] = 0.0;
   out_5496809482113736276[252] = 0.0;
   out_5496809482113736276[253] = 0.0;
   out_5496809482113736276[254] = 0.0;
   out_5496809482113736276[255] = 0.0;
   out_5496809482113736276[256] = 0.0;
   out_5496809482113736276[257] = 0.0;
   out_5496809482113736276[258] = 0.0;
   out_5496809482113736276[259] = 0.0;
   out_5496809482113736276[260] = 0.0;
   out_5496809482113736276[261] = 0.0;
   out_5496809482113736276[262] = 0.0;
   out_5496809482113736276[263] = 0.0;
   out_5496809482113736276[264] = 0.0;
   out_5496809482113736276[265] = 0.0;
   out_5496809482113736276[266] = 1.0;
   out_5496809482113736276[267] = 0.0;
   out_5496809482113736276[268] = 0.0;
   out_5496809482113736276[269] = 0.0;
   out_5496809482113736276[270] = 0.0;
   out_5496809482113736276[271] = 0.0;
   out_5496809482113736276[272] = 0.0;
   out_5496809482113736276[273] = 0.0;
   out_5496809482113736276[274] = 0.0;
   out_5496809482113736276[275] = 0.0;
   out_5496809482113736276[276] = 0.0;
   out_5496809482113736276[277] = 0.0;
   out_5496809482113736276[278] = 0.0;
   out_5496809482113736276[279] = 0.0;
   out_5496809482113736276[280] = 0.0;
   out_5496809482113736276[281] = 0.0;
   out_5496809482113736276[282] = 0.0;
   out_5496809482113736276[283] = 0.0;
   out_5496809482113736276[284] = 0.0;
   out_5496809482113736276[285] = 1.0;
   out_5496809482113736276[286] = 0.0;
   out_5496809482113736276[287] = 0.0;
   out_5496809482113736276[288] = 0.0;
   out_5496809482113736276[289] = 0.0;
   out_5496809482113736276[290] = 0.0;
   out_5496809482113736276[291] = 0.0;
   out_5496809482113736276[292] = 0.0;
   out_5496809482113736276[293] = 0.0;
   out_5496809482113736276[294] = 0.0;
   out_5496809482113736276[295] = 0.0;
   out_5496809482113736276[296] = 0.0;
   out_5496809482113736276[297] = 0.0;
   out_5496809482113736276[298] = 0.0;
   out_5496809482113736276[299] = 0.0;
   out_5496809482113736276[300] = 0.0;
   out_5496809482113736276[301] = 0.0;
   out_5496809482113736276[302] = 0.0;
   out_5496809482113736276[303] = 0.0;
   out_5496809482113736276[304] = 1.0;
   out_5496809482113736276[305] = 0.0;
   out_5496809482113736276[306] = 0.0;
   out_5496809482113736276[307] = 0.0;
   out_5496809482113736276[308] = 0.0;
   out_5496809482113736276[309] = 0.0;
   out_5496809482113736276[310] = 0.0;
   out_5496809482113736276[311] = 0.0;
   out_5496809482113736276[312] = 0.0;
   out_5496809482113736276[313] = 0.0;
   out_5496809482113736276[314] = 0.0;
   out_5496809482113736276[315] = 0.0;
   out_5496809482113736276[316] = 0.0;
   out_5496809482113736276[317] = 0.0;
   out_5496809482113736276[318] = 0.0;
   out_5496809482113736276[319] = 0.0;
   out_5496809482113736276[320] = 0.0;
   out_5496809482113736276[321] = 0.0;
   out_5496809482113736276[322] = 0.0;
   out_5496809482113736276[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_76749327147481970) {
   out_76749327147481970[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_76749327147481970[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_76749327147481970[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_76749327147481970[3] = dt*state[12] + state[3];
   out_76749327147481970[4] = dt*state[13] + state[4];
   out_76749327147481970[5] = dt*state[14] + state[5];
   out_76749327147481970[6] = state[6];
   out_76749327147481970[7] = state[7];
   out_76749327147481970[8] = state[8];
   out_76749327147481970[9] = state[9];
   out_76749327147481970[10] = state[10];
   out_76749327147481970[11] = state[11];
   out_76749327147481970[12] = state[12];
   out_76749327147481970[13] = state[13];
   out_76749327147481970[14] = state[14];
   out_76749327147481970[15] = state[15];
   out_76749327147481970[16] = state[16];
   out_76749327147481970[17] = state[17];
}
void F_fun(double *state, double dt, double *out_7773273273846026145) {
   out_7773273273846026145[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7773273273846026145[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7773273273846026145[2] = 0;
   out_7773273273846026145[3] = 0;
   out_7773273273846026145[4] = 0;
   out_7773273273846026145[5] = 0;
   out_7773273273846026145[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7773273273846026145[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7773273273846026145[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7773273273846026145[9] = 0;
   out_7773273273846026145[10] = 0;
   out_7773273273846026145[11] = 0;
   out_7773273273846026145[12] = 0;
   out_7773273273846026145[13] = 0;
   out_7773273273846026145[14] = 0;
   out_7773273273846026145[15] = 0;
   out_7773273273846026145[16] = 0;
   out_7773273273846026145[17] = 0;
   out_7773273273846026145[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7773273273846026145[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7773273273846026145[20] = 0;
   out_7773273273846026145[21] = 0;
   out_7773273273846026145[22] = 0;
   out_7773273273846026145[23] = 0;
   out_7773273273846026145[24] = 0;
   out_7773273273846026145[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7773273273846026145[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7773273273846026145[27] = 0;
   out_7773273273846026145[28] = 0;
   out_7773273273846026145[29] = 0;
   out_7773273273846026145[30] = 0;
   out_7773273273846026145[31] = 0;
   out_7773273273846026145[32] = 0;
   out_7773273273846026145[33] = 0;
   out_7773273273846026145[34] = 0;
   out_7773273273846026145[35] = 0;
   out_7773273273846026145[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7773273273846026145[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7773273273846026145[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7773273273846026145[39] = 0;
   out_7773273273846026145[40] = 0;
   out_7773273273846026145[41] = 0;
   out_7773273273846026145[42] = 0;
   out_7773273273846026145[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7773273273846026145[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7773273273846026145[45] = 0;
   out_7773273273846026145[46] = 0;
   out_7773273273846026145[47] = 0;
   out_7773273273846026145[48] = 0;
   out_7773273273846026145[49] = 0;
   out_7773273273846026145[50] = 0;
   out_7773273273846026145[51] = 0;
   out_7773273273846026145[52] = 0;
   out_7773273273846026145[53] = 0;
   out_7773273273846026145[54] = 0;
   out_7773273273846026145[55] = 0;
   out_7773273273846026145[56] = 0;
   out_7773273273846026145[57] = 1;
   out_7773273273846026145[58] = 0;
   out_7773273273846026145[59] = 0;
   out_7773273273846026145[60] = 0;
   out_7773273273846026145[61] = 0;
   out_7773273273846026145[62] = 0;
   out_7773273273846026145[63] = 0;
   out_7773273273846026145[64] = 0;
   out_7773273273846026145[65] = 0;
   out_7773273273846026145[66] = dt;
   out_7773273273846026145[67] = 0;
   out_7773273273846026145[68] = 0;
   out_7773273273846026145[69] = 0;
   out_7773273273846026145[70] = 0;
   out_7773273273846026145[71] = 0;
   out_7773273273846026145[72] = 0;
   out_7773273273846026145[73] = 0;
   out_7773273273846026145[74] = 0;
   out_7773273273846026145[75] = 0;
   out_7773273273846026145[76] = 1;
   out_7773273273846026145[77] = 0;
   out_7773273273846026145[78] = 0;
   out_7773273273846026145[79] = 0;
   out_7773273273846026145[80] = 0;
   out_7773273273846026145[81] = 0;
   out_7773273273846026145[82] = 0;
   out_7773273273846026145[83] = 0;
   out_7773273273846026145[84] = 0;
   out_7773273273846026145[85] = dt;
   out_7773273273846026145[86] = 0;
   out_7773273273846026145[87] = 0;
   out_7773273273846026145[88] = 0;
   out_7773273273846026145[89] = 0;
   out_7773273273846026145[90] = 0;
   out_7773273273846026145[91] = 0;
   out_7773273273846026145[92] = 0;
   out_7773273273846026145[93] = 0;
   out_7773273273846026145[94] = 0;
   out_7773273273846026145[95] = 1;
   out_7773273273846026145[96] = 0;
   out_7773273273846026145[97] = 0;
   out_7773273273846026145[98] = 0;
   out_7773273273846026145[99] = 0;
   out_7773273273846026145[100] = 0;
   out_7773273273846026145[101] = 0;
   out_7773273273846026145[102] = 0;
   out_7773273273846026145[103] = 0;
   out_7773273273846026145[104] = dt;
   out_7773273273846026145[105] = 0;
   out_7773273273846026145[106] = 0;
   out_7773273273846026145[107] = 0;
   out_7773273273846026145[108] = 0;
   out_7773273273846026145[109] = 0;
   out_7773273273846026145[110] = 0;
   out_7773273273846026145[111] = 0;
   out_7773273273846026145[112] = 0;
   out_7773273273846026145[113] = 0;
   out_7773273273846026145[114] = 1;
   out_7773273273846026145[115] = 0;
   out_7773273273846026145[116] = 0;
   out_7773273273846026145[117] = 0;
   out_7773273273846026145[118] = 0;
   out_7773273273846026145[119] = 0;
   out_7773273273846026145[120] = 0;
   out_7773273273846026145[121] = 0;
   out_7773273273846026145[122] = 0;
   out_7773273273846026145[123] = 0;
   out_7773273273846026145[124] = 0;
   out_7773273273846026145[125] = 0;
   out_7773273273846026145[126] = 0;
   out_7773273273846026145[127] = 0;
   out_7773273273846026145[128] = 0;
   out_7773273273846026145[129] = 0;
   out_7773273273846026145[130] = 0;
   out_7773273273846026145[131] = 0;
   out_7773273273846026145[132] = 0;
   out_7773273273846026145[133] = 1;
   out_7773273273846026145[134] = 0;
   out_7773273273846026145[135] = 0;
   out_7773273273846026145[136] = 0;
   out_7773273273846026145[137] = 0;
   out_7773273273846026145[138] = 0;
   out_7773273273846026145[139] = 0;
   out_7773273273846026145[140] = 0;
   out_7773273273846026145[141] = 0;
   out_7773273273846026145[142] = 0;
   out_7773273273846026145[143] = 0;
   out_7773273273846026145[144] = 0;
   out_7773273273846026145[145] = 0;
   out_7773273273846026145[146] = 0;
   out_7773273273846026145[147] = 0;
   out_7773273273846026145[148] = 0;
   out_7773273273846026145[149] = 0;
   out_7773273273846026145[150] = 0;
   out_7773273273846026145[151] = 0;
   out_7773273273846026145[152] = 1;
   out_7773273273846026145[153] = 0;
   out_7773273273846026145[154] = 0;
   out_7773273273846026145[155] = 0;
   out_7773273273846026145[156] = 0;
   out_7773273273846026145[157] = 0;
   out_7773273273846026145[158] = 0;
   out_7773273273846026145[159] = 0;
   out_7773273273846026145[160] = 0;
   out_7773273273846026145[161] = 0;
   out_7773273273846026145[162] = 0;
   out_7773273273846026145[163] = 0;
   out_7773273273846026145[164] = 0;
   out_7773273273846026145[165] = 0;
   out_7773273273846026145[166] = 0;
   out_7773273273846026145[167] = 0;
   out_7773273273846026145[168] = 0;
   out_7773273273846026145[169] = 0;
   out_7773273273846026145[170] = 0;
   out_7773273273846026145[171] = 1;
   out_7773273273846026145[172] = 0;
   out_7773273273846026145[173] = 0;
   out_7773273273846026145[174] = 0;
   out_7773273273846026145[175] = 0;
   out_7773273273846026145[176] = 0;
   out_7773273273846026145[177] = 0;
   out_7773273273846026145[178] = 0;
   out_7773273273846026145[179] = 0;
   out_7773273273846026145[180] = 0;
   out_7773273273846026145[181] = 0;
   out_7773273273846026145[182] = 0;
   out_7773273273846026145[183] = 0;
   out_7773273273846026145[184] = 0;
   out_7773273273846026145[185] = 0;
   out_7773273273846026145[186] = 0;
   out_7773273273846026145[187] = 0;
   out_7773273273846026145[188] = 0;
   out_7773273273846026145[189] = 0;
   out_7773273273846026145[190] = 1;
   out_7773273273846026145[191] = 0;
   out_7773273273846026145[192] = 0;
   out_7773273273846026145[193] = 0;
   out_7773273273846026145[194] = 0;
   out_7773273273846026145[195] = 0;
   out_7773273273846026145[196] = 0;
   out_7773273273846026145[197] = 0;
   out_7773273273846026145[198] = 0;
   out_7773273273846026145[199] = 0;
   out_7773273273846026145[200] = 0;
   out_7773273273846026145[201] = 0;
   out_7773273273846026145[202] = 0;
   out_7773273273846026145[203] = 0;
   out_7773273273846026145[204] = 0;
   out_7773273273846026145[205] = 0;
   out_7773273273846026145[206] = 0;
   out_7773273273846026145[207] = 0;
   out_7773273273846026145[208] = 0;
   out_7773273273846026145[209] = 1;
   out_7773273273846026145[210] = 0;
   out_7773273273846026145[211] = 0;
   out_7773273273846026145[212] = 0;
   out_7773273273846026145[213] = 0;
   out_7773273273846026145[214] = 0;
   out_7773273273846026145[215] = 0;
   out_7773273273846026145[216] = 0;
   out_7773273273846026145[217] = 0;
   out_7773273273846026145[218] = 0;
   out_7773273273846026145[219] = 0;
   out_7773273273846026145[220] = 0;
   out_7773273273846026145[221] = 0;
   out_7773273273846026145[222] = 0;
   out_7773273273846026145[223] = 0;
   out_7773273273846026145[224] = 0;
   out_7773273273846026145[225] = 0;
   out_7773273273846026145[226] = 0;
   out_7773273273846026145[227] = 0;
   out_7773273273846026145[228] = 1;
   out_7773273273846026145[229] = 0;
   out_7773273273846026145[230] = 0;
   out_7773273273846026145[231] = 0;
   out_7773273273846026145[232] = 0;
   out_7773273273846026145[233] = 0;
   out_7773273273846026145[234] = 0;
   out_7773273273846026145[235] = 0;
   out_7773273273846026145[236] = 0;
   out_7773273273846026145[237] = 0;
   out_7773273273846026145[238] = 0;
   out_7773273273846026145[239] = 0;
   out_7773273273846026145[240] = 0;
   out_7773273273846026145[241] = 0;
   out_7773273273846026145[242] = 0;
   out_7773273273846026145[243] = 0;
   out_7773273273846026145[244] = 0;
   out_7773273273846026145[245] = 0;
   out_7773273273846026145[246] = 0;
   out_7773273273846026145[247] = 1;
   out_7773273273846026145[248] = 0;
   out_7773273273846026145[249] = 0;
   out_7773273273846026145[250] = 0;
   out_7773273273846026145[251] = 0;
   out_7773273273846026145[252] = 0;
   out_7773273273846026145[253] = 0;
   out_7773273273846026145[254] = 0;
   out_7773273273846026145[255] = 0;
   out_7773273273846026145[256] = 0;
   out_7773273273846026145[257] = 0;
   out_7773273273846026145[258] = 0;
   out_7773273273846026145[259] = 0;
   out_7773273273846026145[260] = 0;
   out_7773273273846026145[261] = 0;
   out_7773273273846026145[262] = 0;
   out_7773273273846026145[263] = 0;
   out_7773273273846026145[264] = 0;
   out_7773273273846026145[265] = 0;
   out_7773273273846026145[266] = 1;
   out_7773273273846026145[267] = 0;
   out_7773273273846026145[268] = 0;
   out_7773273273846026145[269] = 0;
   out_7773273273846026145[270] = 0;
   out_7773273273846026145[271] = 0;
   out_7773273273846026145[272] = 0;
   out_7773273273846026145[273] = 0;
   out_7773273273846026145[274] = 0;
   out_7773273273846026145[275] = 0;
   out_7773273273846026145[276] = 0;
   out_7773273273846026145[277] = 0;
   out_7773273273846026145[278] = 0;
   out_7773273273846026145[279] = 0;
   out_7773273273846026145[280] = 0;
   out_7773273273846026145[281] = 0;
   out_7773273273846026145[282] = 0;
   out_7773273273846026145[283] = 0;
   out_7773273273846026145[284] = 0;
   out_7773273273846026145[285] = 1;
   out_7773273273846026145[286] = 0;
   out_7773273273846026145[287] = 0;
   out_7773273273846026145[288] = 0;
   out_7773273273846026145[289] = 0;
   out_7773273273846026145[290] = 0;
   out_7773273273846026145[291] = 0;
   out_7773273273846026145[292] = 0;
   out_7773273273846026145[293] = 0;
   out_7773273273846026145[294] = 0;
   out_7773273273846026145[295] = 0;
   out_7773273273846026145[296] = 0;
   out_7773273273846026145[297] = 0;
   out_7773273273846026145[298] = 0;
   out_7773273273846026145[299] = 0;
   out_7773273273846026145[300] = 0;
   out_7773273273846026145[301] = 0;
   out_7773273273846026145[302] = 0;
   out_7773273273846026145[303] = 0;
   out_7773273273846026145[304] = 1;
   out_7773273273846026145[305] = 0;
   out_7773273273846026145[306] = 0;
   out_7773273273846026145[307] = 0;
   out_7773273273846026145[308] = 0;
   out_7773273273846026145[309] = 0;
   out_7773273273846026145[310] = 0;
   out_7773273273846026145[311] = 0;
   out_7773273273846026145[312] = 0;
   out_7773273273846026145[313] = 0;
   out_7773273273846026145[314] = 0;
   out_7773273273846026145[315] = 0;
   out_7773273273846026145[316] = 0;
   out_7773273273846026145[317] = 0;
   out_7773273273846026145[318] = 0;
   out_7773273273846026145[319] = 0;
   out_7773273273846026145[320] = 0;
   out_7773273273846026145[321] = 0;
   out_7773273273846026145[322] = 0;
   out_7773273273846026145[323] = 1;
}
void h_4(double *state, double *unused, double *out_8836590006675901483) {
   out_8836590006675901483[0] = state[6] + state[9];
   out_8836590006675901483[1] = state[7] + state[10];
   out_8836590006675901483[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_8771031560904685529) {
   out_8771031560904685529[0] = 0;
   out_8771031560904685529[1] = 0;
   out_8771031560904685529[2] = 0;
   out_8771031560904685529[3] = 0;
   out_8771031560904685529[4] = 0;
   out_8771031560904685529[5] = 0;
   out_8771031560904685529[6] = 1;
   out_8771031560904685529[7] = 0;
   out_8771031560904685529[8] = 0;
   out_8771031560904685529[9] = 1;
   out_8771031560904685529[10] = 0;
   out_8771031560904685529[11] = 0;
   out_8771031560904685529[12] = 0;
   out_8771031560904685529[13] = 0;
   out_8771031560904685529[14] = 0;
   out_8771031560904685529[15] = 0;
   out_8771031560904685529[16] = 0;
   out_8771031560904685529[17] = 0;
   out_8771031560904685529[18] = 0;
   out_8771031560904685529[19] = 0;
   out_8771031560904685529[20] = 0;
   out_8771031560904685529[21] = 0;
   out_8771031560904685529[22] = 0;
   out_8771031560904685529[23] = 0;
   out_8771031560904685529[24] = 0;
   out_8771031560904685529[25] = 1;
   out_8771031560904685529[26] = 0;
   out_8771031560904685529[27] = 0;
   out_8771031560904685529[28] = 1;
   out_8771031560904685529[29] = 0;
   out_8771031560904685529[30] = 0;
   out_8771031560904685529[31] = 0;
   out_8771031560904685529[32] = 0;
   out_8771031560904685529[33] = 0;
   out_8771031560904685529[34] = 0;
   out_8771031560904685529[35] = 0;
   out_8771031560904685529[36] = 0;
   out_8771031560904685529[37] = 0;
   out_8771031560904685529[38] = 0;
   out_8771031560904685529[39] = 0;
   out_8771031560904685529[40] = 0;
   out_8771031560904685529[41] = 0;
   out_8771031560904685529[42] = 0;
   out_8771031560904685529[43] = 0;
   out_8771031560904685529[44] = 1;
   out_8771031560904685529[45] = 0;
   out_8771031560904685529[46] = 0;
   out_8771031560904685529[47] = 1;
   out_8771031560904685529[48] = 0;
   out_8771031560904685529[49] = 0;
   out_8771031560904685529[50] = 0;
   out_8771031560904685529[51] = 0;
   out_8771031560904685529[52] = 0;
   out_8771031560904685529[53] = 0;
}
void h_10(double *state, double *unused, double *out_7833049906299002536) {
   out_7833049906299002536[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_7833049906299002536[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_7833049906299002536[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1676230657278343882) {
   out_1676230657278343882[0] = 0;
   out_1676230657278343882[1] = 9.8100000000000005*cos(state[1]);
   out_1676230657278343882[2] = 0;
   out_1676230657278343882[3] = 0;
   out_1676230657278343882[4] = -state[8];
   out_1676230657278343882[5] = state[7];
   out_1676230657278343882[6] = 0;
   out_1676230657278343882[7] = state[5];
   out_1676230657278343882[8] = -state[4];
   out_1676230657278343882[9] = 0;
   out_1676230657278343882[10] = 0;
   out_1676230657278343882[11] = 0;
   out_1676230657278343882[12] = 1;
   out_1676230657278343882[13] = 0;
   out_1676230657278343882[14] = 0;
   out_1676230657278343882[15] = 1;
   out_1676230657278343882[16] = 0;
   out_1676230657278343882[17] = 0;
   out_1676230657278343882[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1676230657278343882[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1676230657278343882[20] = 0;
   out_1676230657278343882[21] = state[8];
   out_1676230657278343882[22] = 0;
   out_1676230657278343882[23] = -state[6];
   out_1676230657278343882[24] = -state[5];
   out_1676230657278343882[25] = 0;
   out_1676230657278343882[26] = state[3];
   out_1676230657278343882[27] = 0;
   out_1676230657278343882[28] = 0;
   out_1676230657278343882[29] = 0;
   out_1676230657278343882[30] = 0;
   out_1676230657278343882[31] = 1;
   out_1676230657278343882[32] = 0;
   out_1676230657278343882[33] = 0;
   out_1676230657278343882[34] = 1;
   out_1676230657278343882[35] = 0;
   out_1676230657278343882[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1676230657278343882[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1676230657278343882[38] = 0;
   out_1676230657278343882[39] = -state[7];
   out_1676230657278343882[40] = state[6];
   out_1676230657278343882[41] = 0;
   out_1676230657278343882[42] = state[4];
   out_1676230657278343882[43] = -state[3];
   out_1676230657278343882[44] = 0;
   out_1676230657278343882[45] = 0;
   out_1676230657278343882[46] = 0;
   out_1676230657278343882[47] = 0;
   out_1676230657278343882[48] = 0;
   out_1676230657278343882[49] = 0;
   out_1676230657278343882[50] = 1;
   out_1676230657278343882[51] = 0;
   out_1676230657278343882[52] = 0;
   out_1676230657278343882[53] = 1;
}
void h_13(double *state, double *unused, double *out_8788718686171382623) {
   out_8788718686171382623[0] = state[3];
   out_8788718686171382623[1] = state[4];
   out_8788718686171382623[2] = state[5];
}
void H_13(double *state, double *unused, double *out_5558757735572352728) {
   out_5558757735572352728[0] = 0;
   out_5558757735572352728[1] = 0;
   out_5558757735572352728[2] = 0;
   out_5558757735572352728[3] = 1;
   out_5558757735572352728[4] = 0;
   out_5558757735572352728[5] = 0;
   out_5558757735572352728[6] = 0;
   out_5558757735572352728[7] = 0;
   out_5558757735572352728[8] = 0;
   out_5558757735572352728[9] = 0;
   out_5558757735572352728[10] = 0;
   out_5558757735572352728[11] = 0;
   out_5558757735572352728[12] = 0;
   out_5558757735572352728[13] = 0;
   out_5558757735572352728[14] = 0;
   out_5558757735572352728[15] = 0;
   out_5558757735572352728[16] = 0;
   out_5558757735572352728[17] = 0;
   out_5558757735572352728[18] = 0;
   out_5558757735572352728[19] = 0;
   out_5558757735572352728[20] = 0;
   out_5558757735572352728[21] = 0;
   out_5558757735572352728[22] = 1;
   out_5558757735572352728[23] = 0;
   out_5558757735572352728[24] = 0;
   out_5558757735572352728[25] = 0;
   out_5558757735572352728[26] = 0;
   out_5558757735572352728[27] = 0;
   out_5558757735572352728[28] = 0;
   out_5558757735572352728[29] = 0;
   out_5558757735572352728[30] = 0;
   out_5558757735572352728[31] = 0;
   out_5558757735572352728[32] = 0;
   out_5558757735572352728[33] = 0;
   out_5558757735572352728[34] = 0;
   out_5558757735572352728[35] = 0;
   out_5558757735572352728[36] = 0;
   out_5558757735572352728[37] = 0;
   out_5558757735572352728[38] = 0;
   out_5558757735572352728[39] = 0;
   out_5558757735572352728[40] = 0;
   out_5558757735572352728[41] = 1;
   out_5558757735572352728[42] = 0;
   out_5558757735572352728[43] = 0;
   out_5558757735572352728[44] = 0;
   out_5558757735572352728[45] = 0;
   out_5558757735572352728[46] = 0;
   out_5558757735572352728[47] = 0;
   out_5558757735572352728[48] = 0;
   out_5558757735572352728[49] = 0;
   out_5558757735572352728[50] = 0;
   out_5558757735572352728[51] = 0;
   out_5558757735572352728[52] = 0;
   out_5558757735572352728[53] = 0;
}
void h_14(double *state, double *unused, double *out_4044191392879282830) {
   out_4044191392879282830[0] = state[6];
   out_4044191392879282830[1] = state[7];
   out_4044191392879282830[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4807790704565201000) {
   out_4807790704565201000[0] = 0;
   out_4807790704565201000[1] = 0;
   out_4807790704565201000[2] = 0;
   out_4807790704565201000[3] = 0;
   out_4807790704565201000[4] = 0;
   out_4807790704565201000[5] = 0;
   out_4807790704565201000[6] = 1;
   out_4807790704565201000[7] = 0;
   out_4807790704565201000[8] = 0;
   out_4807790704565201000[9] = 0;
   out_4807790704565201000[10] = 0;
   out_4807790704565201000[11] = 0;
   out_4807790704565201000[12] = 0;
   out_4807790704565201000[13] = 0;
   out_4807790704565201000[14] = 0;
   out_4807790704565201000[15] = 0;
   out_4807790704565201000[16] = 0;
   out_4807790704565201000[17] = 0;
   out_4807790704565201000[18] = 0;
   out_4807790704565201000[19] = 0;
   out_4807790704565201000[20] = 0;
   out_4807790704565201000[21] = 0;
   out_4807790704565201000[22] = 0;
   out_4807790704565201000[23] = 0;
   out_4807790704565201000[24] = 0;
   out_4807790704565201000[25] = 1;
   out_4807790704565201000[26] = 0;
   out_4807790704565201000[27] = 0;
   out_4807790704565201000[28] = 0;
   out_4807790704565201000[29] = 0;
   out_4807790704565201000[30] = 0;
   out_4807790704565201000[31] = 0;
   out_4807790704565201000[32] = 0;
   out_4807790704565201000[33] = 0;
   out_4807790704565201000[34] = 0;
   out_4807790704565201000[35] = 0;
   out_4807790704565201000[36] = 0;
   out_4807790704565201000[37] = 0;
   out_4807790704565201000[38] = 0;
   out_4807790704565201000[39] = 0;
   out_4807790704565201000[40] = 0;
   out_4807790704565201000[41] = 0;
   out_4807790704565201000[42] = 0;
   out_4807790704565201000[43] = 0;
   out_4807790704565201000[44] = 1;
   out_4807790704565201000[45] = 0;
   out_4807790704565201000[46] = 0;
   out_4807790704565201000[47] = 0;
   out_4807790704565201000[48] = 0;
   out_4807790704565201000[49] = 0;
   out_4807790704565201000[50] = 0;
   out_4807790704565201000[51] = 0;
   out_4807790704565201000[52] = 0;
   out_4807790704565201000[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_8979246808243312501) {
  err_fun(nom_x, delta_x, out_8979246808243312501);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6182129478777519212) {
  inv_err_fun(nom_x, true_x, out_6182129478777519212);
}
void pose_H_mod_fun(double *state, double *out_5496809482113736276) {
  H_mod_fun(state, out_5496809482113736276);
}
void pose_f_fun(double *state, double dt, double *out_76749327147481970) {
  f_fun(state,  dt, out_76749327147481970);
}
void pose_F_fun(double *state, double dt, double *out_7773273273846026145) {
  F_fun(state,  dt, out_7773273273846026145);
}
void pose_h_4(double *state, double *unused, double *out_8836590006675901483) {
  h_4(state, unused, out_8836590006675901483);
}
void pose_H_4(double *state, double *unused, double *out_8771031560904685529) {
  H_4(state, unused, out_8771031560904685529);
}
void pose_h_10(double *state, double *unused, double *out_7833049906299002536) {
  h_10(state, unused, out_7833049906299002536);
}
void pose_H_10(double *state, double *unused, double *out_1676230657278343882) {
  H_10(state, unused, out_1676230657278343882);
}
void pose_h_13(double *state, double *unused, double *out_8788718686171382623) {
  h_13(state, unused, out_8788718686171382623);
}
void pose_H_13(double *state, double *unused, double *out_5558757735572352728) {
  H_13(state, unused, out_5558757735572352728);
}
void pose_h_14(double *state, double *unused, double *out_4044191392879282830) {
  h_14(state, unused, out_4044191392879282830);
}
void pose_H_14(double *state, double *unused, double *out_4807790704565201000) {
  H_14(state, unused, out_4807790704565201000);
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
