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
void err_fun(double *nom_x, double *delta_x, double *out_6169503642516981710) {
   out_6169503642516981710[0] = delta_x[0] + nom_x[0];
   out_6169503642516981710[1] = delta_x[1] + nom_x[1];
   out_6169503642516981710[2] = delta_x[2] + nom_x[2];
   out_6169503642516981710[3] = delta_x[3] + nom_x[3];
   out_6169503642516981710[4] = delta_x[4] + nom_x[4];
   out_6169503642516981710[5] = delta_x[5] + nom_x[5];
   out_6169503642516981710[6] = delta_x[6] + nom_x[6];
   out_6169503642516981710[7] = delta_x[7] + nom_x[7];
   out_6169503642516981710[8] = delta_x[8] + nom_x[8];
   out_6169503642516981710[9] = delta_x[9] + nom_x[9];
   out_6169503642516981710[10] = delta_x[10] + nom_x[10];
   out_6169503642516981710[11] = delta_x[11] + nom_x[11];
   out_6169503642516981710[12] = delta_x[12] + nom_x[12];
   out_6169503642516981710[13] = delta_x[13] + nom_x[13];
   out_6169503642516981710[14] = delta_x[14] + nom_x[14];
   out_6169503642516981710[15] = delta_x[15] + nom_x[15];
   out_6169503642516981710[16] = delta_x[16] + nom_x[16];
   out_6169503642516981710[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2781558835044378693) {
   out_2781558835044378693[0] = -nom_x[0] + true_x[0];
   out_2781558835044378693[1] = -nom_x[1] + true_x[1];
   out_2781558835044378693[2] = -nom_x[2] + true_x[2];
   out_2781558835044378693[3] = -nom_x[3] + true_x[3];
   out_2781558835044378693[4] = -nom_x[4] + true_x[4];
   out_2781558835044378693[5] = -nom_x[5] + true_x[5];
   out_2781558835044378693[6] = -nom_x[6] + true_x[6];
   out_2781558835044378693[7] = -nom_x[7] + true_x[7];
   out_2781558835044378693[8] = -nom_x[8] + true_x[8];
   out_2781558835044378693[9] = -nom_x[9] + true_x[9];
   out_2781558835044378693[10] = -nom_x[10] + true_x[10];
   out_2781558835044378693[11] = -nom_x[11] + true_x[11];
   out_2781558835044378693[12] = -nom_x[12] + true_x[12];
   out_2781558835044378693[13] = -nom_x[13] + true_x[13];
   out_2781558835044378693[14] = -nom_x[14] + true_x[14];
   out_2781558835044378693[15] = -nom_x[15] + true_x[15];
   out_2781558835044378693[16] = -nom_x[16] + true_x[16];
   out_2781558835044378693[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4498457996676133449) {
   out_4498457996676133449[0] = 1.0;
   out_4498457996676133449[1] = 0.0;
   out_4498457996676133449[2] = 0.0;
   out_4498457996676133449[3] = 0.0;
   out_4498457996676133449[4] = 0.0;
   out_4498457996676133449[5] = 0.0;
   out_4498457996676133449[6] = 0.0;
   out_4498457996676133449[7] = 0.0;
   out_4498457996676133449[8] = 0.0;
   out_4498457996676133449[9] = 0.0;
   out_4498457996676133449[10] = 0.0;
   out_4498457996676133449[11] = 0.0;
   out_4498457996676133449[12] = 0.0;
   out_4498457996676133449[13] = 0.0;
   out_4498457996676133449[14] = 0.0;
   out_4498457996676133449[15] = 0.0;
   out_4498457996676133449[16] = 0.0;
   out_4498457996676133449[17] = 0.0;
   out_4498457996676133449[18] = 0.0;
   out_4498457996676133449[19] = 1.0;
   out_4498457996676133449[20] = 0.0;
   out_4498457996676133449[21] = 0.0;
   out_4498457996676133449[22] = 0.0;
   out_4498457996676133449[23] = 0.0;
   out_4498457996676133449[24] = 0.0;
   out_4498457996676133449[25] = 0.0;
   out_4498457996676133449[26] = 0.0;
   out_4498457996676133449[27] = 0.0;
   out_4498457996676133449[28] = 0.0;
   out_4498457996676133449[29] = 0.0;
   out_4498457996676133449[30] = 0.0;
   out_4498457996676133449[31] = 0.0;
   out_4498457996676133449[32] = 0.0;
   out_4498457996676133449[33] = 0.0;
   out_4498457996676133449[34] = 0.0;
   out_4498457996676133449[35] = 0.0;
   out_4498457996676133449[36] = 0.0;
   out_4498457996676133449[37] = 0.0;
   out_4498457996676133449[38] = 1.0;
   out_4498457996676133449[39] = 0.0;
   out_4498457996676133449[40] = 0.0;
   out_4498457996676133449[41] = 0.0;
   out_4498457996676133449[42] = 0.0;
   out_4498457996676133449[43] = 0.0;
   out_4498457996676133449[44] = 0.0;
   out_4498457996676133449[45] = 0.0;
   out_4498457996676133449[46] = 0.0;
   out_4498457996676133449[47] = 0.0;
   out_4498457996676133449[48] = 0.0;
   out_4498457996676133449[49] = 0.0;
   out_4498457996676133449[50] = 0.0;
   out_4498457996676133449[51] = 0.0;
   out_4498457996676133449[52] = 0.0;
   out_4498457996676133449[53] = 0.0;
   out_4498457996676133449[54] = 0.0;
   out_4498457996676133449[55] = 0.0;
   out_4498457996676133449[56] = 0.0;
   out_4498457996676133449[57] = 1.0;
   out_4498457996676133449[58] = 0.0;
   out_4498457996676133449[59] = 0.0;
   out_4498457996676133449[60] = 0.0;
   out_4498457996676133449[61] = 0.0;
   out_4498457996676133449[62] = 0.0;
   out_4498457996676133449[63] = 0.0;
   out_4498457996676133449[64] = 0.0;
   out_4498457996676133449[65] = 0.0;
   out_4498457996676133449[66] = 0.0;
   out_4498457996676133449[67] = 0.0;
   out_4498457996676133449[68] = 0.0;
   out_4498457996676133449[69] = 0.0;
   out_4498457996676133449[70] = 0.0;
   out_4498457996676133449[71] = 0.0;
   out_4498457996676133449[72] = 0.0;
   out_4498457996676133449[73] = 0.0;
   out_4498457996676133449[74] = 0.0;
   out_4498457996676133449[75] = 0.0;
   out_4498457996676133449[76] = 1.0;
   out_4498457996676133449[77] = 0.0;
   out_4498457996676133449[78] = 0.0;
   out_4498457996676133449[79] = 0.0;
   out_4498457996676133449[80] = 0.0;
   out_4498457996676133449[81] = 0.0;
   out_4498457996676133449[82] = 0.0;
   out_4498457996676133449[83] = 0.0;
   out_4498457996676133449[84] = 0.0;
   out_4498457996676133449[85] = 0.0;
   out_4498457996676133449[86] = 0.0;
   out_4498457996676133449[87] = 0.0;
   out_4498457996676133449[88] = 0.0;
   out_4498457996676133449[89] = 0.0;
   out_4498457996676133449[90] = 0.0;
   out_4498457996676133449[91] = 0.0;
   out_4498457996676133449[92] = 0.0;
   out_4498457996676133449[93] = 0.0;
   out_4498457996676133449[94] = 0.0;
   out_4498457996676133449[95] = 1.0;
   out_4498457996676133449[96] = 0.0;
   out_4498457996676133449[97] = 0.0;
   out_4498457996676133449[98] = 0.0;
   out_4498457996676133449[99] = 0.0;
   out_4498457996676133449[100] = 0.0;
   out_4498457996676133449[101] = 0.0;
   out_4498457996676133449[102] = 0.0;
   out_4498457996676133449[103] = 0.0;
   out_4498457996676133449[104] = 0.0;
   out_4498457996676133449[105] = 0.0;
   out_4498457996676133449[106] = 0.0;
   out_4498457996676133449[107] = 0.0;
   out_4498457996676133449[108] = 0.0;
   out_4498457996676133449[109] = 0.0;
   out_4498457996676133449[110] = 0.0;
   out_4498457996676133449[111] = 0.0;
   out_4498457996676133449[112] = 0.0;
   out_4498457996676133449[113] = 0.0;
   out_4498457996676133449[114] = 1.0;
   out_4498457996676133449[115] = 0.0;
   out_4498457996676133449[116] = 0.0;
   out_4498457996676133449[117] = 0.0;
   out_4498457996676133449[118] = 0.0;
   out_4498457996676133449[119] = 0.0;
   out_4498457996676133449[120] = 0.0;
   out_4498457996676133449[121] = 0.0;
   out_4498457996676133449[122] = 0.0;
   out_4498457996676133449[123] = 0.0;
   out_4498457996676133449[124] = 0.0;
   out_4498457996676133449[125] = 0.0;
   out_4498457996676133449[126] = 0.0;
   out_4498457996676133449[127] = 0.0;
   out_4498457996676133449[128] = 0.0;
   out_4498457996676133449[129] = 0.0;
   out_4498457996676133449[130] = 0.0;
   out_4498457996676133449[131] = 0.0;
   out_4498457996676133449[132] = 0.0;
   out_4498457996676133449[133] = 1.0;
   out_4498457996676133449[134] = 0.0;
   out_4498457996676133449[135] = 0.0;
   out_4498457996676133449[136] = 0.0;
   out_4498457996676133449[137] = 0.0;
   out_4498457996676133449[138] = 0.0;
   out_4498457996676133449[139] = 0.0;
   out_4498457996676133449[140] = 0.0;
   out_4498457996676133449[141] = 0.0;
   out_4498457996676133449[142] = 0.0;
   out_4498457996676133449[143] = 0.0;
   out_4498457996676133449[144] = 0.0;
   out_4498457996676133449[145] = 0.0;
   out_4498457996676133449[146] = 0.0;
   out_4498457996676133449[147] = 0.0;
   out_4498457996676133449[148] = 0.0;
   out_4498457996676133449[149] = 0.0;
   out_4498457996676133449[150] = 0.0;
   out_4498457996676133449[151] = 0.0;
   out_4498457996676133449[152] = 1.0;
   out_4498457996676133449[153] = 0.0;
   out_4498457996676133449[154] = 0.0;
   out_4498457996676133449[155] = 0.0;
   out_4498457996676133449[156] = 0.0;
   out_4498457996676133449[157] = 0.0;
   out_4498457996676133449[158] = 0.0;
   out_4498457996676133449[159] = 0.0;
   out_4498457996676133449[160] = 0.0;
   out_4498457996676133449[161] = 0.0;
   out_4498457996676133449[162] = 0.0;
   out_4498457996676133449[163] = 0.0;
   out_4498457996676133449[164] = 0.0;
   out_4498457996676133449[165] = 0.0;
   out_4498457996676133449[166] = 0.0;
   out_4498457996676133449[167] = 0.0;
   out_4498457996676133449[168] = 0.0;
   out_4498457996676133449[169] = 0.0;
   out_4498457996676133449[170] = 0.0;
   out_4498457996676133449[171] = 1.0;
   out_4498457996676133449[172] = 0.0;
   out_4498457996676133449[173] = 0.0;
   out_4498457996676133449[174] = 0.0;
   out_4498457996676133449[175] = 0.0;
   out_4498457996676133449[176] = 0.0;
   out_4498457996676133449[177] = 0.0;
   out_4498457996676133449[178] = 0.0;
   out_4498457996676133449[179] = 0.0;
   out_4498457996676133449[180] = 0.0;
   out_4498457996676133449[181] = 0.0;
   out_4498457996676133449[182] = 0.0;
   out_4498457996676133449[183] = 0.0;
   out_4498457996676133449[184] = 0.0;
   out_4498457996676133449[185] = 0.0;
   out_4498457996676133449[186] = 0.0;
   out_4498457996676133449[187] = 0.0;
   out_4498457996676133449[188] = 0.0;
   out_4498457996676133449[189] = 0.0;
   out_4498457996676133449[190] = 1.0;
   out_4498457996676133449[191] = 0.0;
   out_4498457996676133449[192] = 0.0;
   out_4498457996676133449[193] = 0.0;
   out_4498457996676133449[194] = 0.0;
   out_4498457996676133449[195] = 0.0;
   out_4498457996676133449[196] = 0.0;
   out_4498457996676133449[197] = 0.0;
   out_4498457996676133449[198] = 0.0;
   out_4498457996676133449[199] = 0.0;
   out_4498457996676133449[200] = 0.0;
   out_4498457996676133449[201] = 0.0;
   out_4498457996676133449[202] = 0.0;
   out_4498457996676133449[203] = 0.0;
   out_4498457996676133449[204] = 0.0;
   out_4498457996676133449[205] = 0.0;
   out_4498457996676133449[206] = 0.0;
   out_4498457996676133449[207] = 0.0;
   out_4498457996676133449[208] = 0.0;
   out_4498457996676133449[209] = 1.0;
   out_4498457996676133449[210] = 0.0;
   out_4498457996676133449[211] = 0.0;
   out_4498457996676133449[212] = 0.0;
   out_4498457996676133449[213] = 0.0;
   out_4498457996676133449[214] = 0.0;
   out_4498457996676133449[215] = 0.0;
   out_4498457996676133449[216] = 0.0;
   out_4498457996676133449[217] = 0.0;
   out_4498457996676133449[218] = 0.0;
   out_4498457996676133449[219] = 0.0;
   out_4498457996676133449[220] = 0.0;
   out_4498457996676133449[221] = 0.0;
   out_4498457996676133449[222] = 0.0;
   out_4498457996676133449[223] = 0.0;
   out_4498457996676133449[224] = 0.0;
   out_4498457996676133449[225] = 0.0;
   out_4498457996676133449[226] = 0.0;
   out_4498457996676133449[227] = 0.0;
   out_4498457996676133449[228] = 1.0;
   out_4498457996676133449[229] = 0.0;
   out_4498457996676133449[230] = 0.0;
   out_4498457996676133449[231] = 0.0;
   out_4498457996676133449[232] = 0.0;
   out_4498457996676133449[233] = 0.0;
   out_4498457996676133449[234] = 0.0;
   out_4498457996676133449[235] = 0.0;
   out_4498457996676133449[236] = 0.0;
   out_4498457996676133449[237] = 0.0;
   out_4498457996676133449[238] = 0.0;
   out_4498457996676133449[239] = 0.0;
   out_4498457996676133449[240] = 0.0;
   out_4498457996676133449[241] = 0.0;
   out_4498457996676133449[242] = 0.0;
   out_4498457996676133449[243] = 0.0;
   out_4498457996676133449[244] = 0.0;
   out_4498457996676133449[245] = 0.0;
   out_4498457996676133449[246] = 0.0;
   out_4498457996676133449[247] = 1.0;
   out_4498457996676133449[248] = 0.0;
   out_4498457996676133449[249] = 0.0;
   out_4498457996676133449[250] = 0.0;
   out_4498457996676133449[251] = 0.0;
   out_4498457996676133449[252] = 0.0;
   out_4498457996676133449[253] = 0.0;
   out_4498457996676133449[254] = 0.0;
   out_4498457996676133449[255] = 0.0;
   out_4498457996676133449[256] = 0.0;
   out_4498457996676133449[257] = 0.0;
   out_4498457996676133449[258] = 0.0;
   out_4498457996676133449[259] = 0.0;
   out_4498457996676133449[260] = 0.0;
   out_4498457996676133449[261] = 0.0;
   out_4498457996676133449[262] = 0.0;
   out_4498457996676133449[263] = 0.0;
   out_4498457996676133449[264] = 0.0;
   out_4498457996676133449[265] = 0.0;
   out_4498457996676133449[266] = 1.0;
   out_4498457996676133449[267] = 0.0;
   out_4498457996676133449[268] = 0.0;
   out_4498457996676133449[269] = 0.0;
   out_4498457996676133449[270] = 0.0;
   out_4498457996676133449[271] = 0.0;
   out_4498457996676133449[272] = 0.0;
   out_4498457996676133449[273] = 0.0;
   out_4498457996676133449[274] = 0.0;
   out_4498457996676133449[275] = 0.0;
   out_4498457996676133449[276] = 0.0;
   out_4498457996676133449[277] = 0.0;
   out_4498457996676133449[278] = 0.0;
   out_4498457996676133449[279] = 0.0;
   out_4498457996676133449[280] = 0.0;
   out_4498457996676133449[281] = 0.0;
   out_4498457996676133449[282] = 0.0;
   out_4498457996676133449[283] = 0.0;
   out_4498457996676133449[284] = 0.0;
   out_4498457996676133449[285] = 1.0;
   out_4498457996676133449[286] = 0.0;
   out_4498457996676133449[287] = 0.0;
   out_4498457996676133449[288] = 0.0;
   out_4498457996676133449[289] = 0.0;
   out_4498457996676133449[290] = 0.0;
   out_4498457996676133449[291] = 0.0;
   out_4498457996676133449[292] = 0.0;
   out_4498457996676133449[293] = 0.0;
   out_4498457996676133449[294] = 0.0;
   out_4498457996676133449[295] = 0.0;
   out_4498457996676133449[296] = 0.0;
   out_4498457996676133449[297] = 0.0;
   out_4498457996676133449[298] = 0.0;
   out_4498457996676133449[299] = 0.0;
   out_4498457996676133449[300] = 0.0;
   out_4498457996676133449[301] = 0.0;
   out_4498457996676133449[302] = 0.0;
   out_4498457996676133449[303] = 0.0;
   out_4498457996676133449[304] = 1.0;
   out_4498457996676133449[305] = 0.0;
   out_4498457996676133449[306] = 0.0;
   out_4498457996676133449[307] = 0.0;
   out_4498457996676133449[308] = 0.0;
   out_4498457996676133449[309] = 0.0;
   out_4498457996676133449[310] = 0.0;
   out_4498457996676133449[311] = 0.0;
   out_4498457996676133449[312] = 0.0;
   out_4498457996676133449[313] = 0.0;
   out_4498457996676133449[314] = 0.0;
   out_4498457996676133449[315] = 0.0;
   out_4498457996676133449[316] = 0.0;
   out_4498457996676133449[317] = 0.0;
   out_4498457996676133449[318] = 0.0;
   out_4498457996676133449[319] = 0.0;
   out_4498457996676133449[320] = 0.0;
   out_4498457996676133449[321] = 0.0;
   out_4498457996676133449[322] = 0.0;
   out_4498457996676133449[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_3471362747861957887) {
   out_3471362747861957887[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_3471362747861957887[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_3471362747861957887[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_3471362747861957887[3] = dt*state[12] + state[3];
   out_3471362747861957887[4] = dt*state[13] + state[4];
   out_3471362747861957887[5] = dt*state[14] + state[5];
   out_3471362747861957887[6] = state[6];
   out_3471362747861957887[7] = state[7];
   out_3471362747861957887[8] = state[8];
   out_3471362747861957887[9] = state[9];
   out_3471362747861957887[10] = state[10];
   out_3471362747861957887[11] = state[11];
   out_3471362747861957887[12] = state[12];
   out_3471362747861957887[13] = state[13];
   out_3471362747861957887[14] = state[14];
   out_3471362747861957887[15] = state[15];
   out_3471362747861957887[16] = state[16];
   out_3471362747861957887[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2324287403941072643) {
   out_2324287403941072643[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2324287403941072643[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2324287403941072643[2] = 0;
   out_2324287403941072643[3] = 0;
   out_2324287403941072643[4] = 0;
   out_2324287403941072643[5] = 0;
   out_2324287403941072643[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2324287403941072643[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2324287403941072643[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2324287403941072643[9] = 0;
   out_2324287403941072643[10] = 0;
   out_2324287403941072643[11] = 0;
   out_2324287403941072643[12] = 0;
   out_2324287403941072643[13] = 0;
   out_2324287403941072643[14] = 0;
   out_2324287403941072643[15] = 0;
   out_2324287403941072643[16] = 0;
   out_2324287403941072643[17] = 0;
   out_2324287403941072643[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2324287403941072643[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2324287403941072643[20] = 0;
   out_2324287403941072643[21] = 0;
   out_2324287403941072643[22] = 0;
   out_2324287403941072643[23] = 0;
   out_2324287403941072643[24] = 0;
   out_2324287403941072643[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2324287403941072643[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2324287403941072643[27] = 0;
   out_2324287403941072643[28] = 0;
   out_2324287403941072643[29] = 0;
   out_2324287403941072643[30] = 0;
   out_2324287403941072643[31] = 0;
   out_2324287403941072643[32] = 0;
   out_2324287403941072643[33] = 0;
   out_2324287403941072643[34] = 0;
   out_2324287403941072643[35] = 0;
   out_2324287403941072643[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2324287403941072643[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2324287403941072643[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2324287403941072643[39] = 0;
   out_2324287403941072643[40] = 0;
   out_2324287403941072643[41] = 0;
   out_2324287403941072643[42] = 0;
   out_2324287403941072643[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2324287403941072643[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2324287403941072643[45] = 0;
   out_2324287403941072643[46] = 0;
   out_2324287403941072643[47] = 0;
   out_2324287403941072643[48] = 0;
   out_2324287403941072643[49] = 0;
   out_2324287403941072643[50] = 0;
   out_2324287403941072643[51] = 0;
   out_2324287403941072643[52] = 0;
   out_2324287403941072643[53] = 0;
   out_2324287403941072643[54] = 0;
   out_2324287403941072643[55] = 0;
   out_2324287403941072643[56] = 0;
   out_2324287403941072643[57] = 1;
   out_2324287403941072643[58] = 0;
   out_2324287403941072643[59] = 0;
   out_2324287403941072643[60] = 0;
   out_2324287403941072643[61] = 0;
   out_2324287403941072643[62] = 0;
   out_2324287403941072643[63] = 0;
   out_2324287403941072643[64] = 0;
   out_2324287403941072643[65] = 0;
   out_2324287403941072643[66] = dt;
   out_2324287403941072643[67] = 0;
   out_2324287403941072643[68] = 0;
   out_2324287403941072643[69] = 0;
   out_2324287403941072643[70] = 0;
   out_2324287403941072643[71] = 0;
   out_2324287403941072643[72] = 0;
   out_2324287403941072643[73] = 0;
   out_2324287403941072643[74] = 0;
   out_2324287403941072643[75] = 0;
   out_2324287403941072643[76] = 1;
   out_2324287403941072643[77] = 0;
   out_2324287403941072643[78] = 0;
   out_2324287403941072643[79] = 0;
   out_2324287403941072643[80] = 0;
   out_2324287403941072643[81] = 0;
   out_2324287403941072643[82] = 0;
   out_2324287403941072643[83] = 0;
   out_2324287403941072643[84] = 0;
   out_2324287403941072643[85] = dt;
   out_2324287403941072643[86] = 0;
   out_2324287403941072643[87] = 0;
   out_2324287403941072643[88] = 0;
   out_2324287403941072643[89] = 0;
   out_2324287403941072643[90] = 0;
   out_2324287403941072643[91] = 0;
   out_2324287403941072643[92] = 0;
   out_2324287403941072643[93] = 0;
   out_2324287403941072643[94] = 0;
   out_2324287403941072643[95] = 1;
   out_2324287403941072643[96] = 0;
   out_2324287403941072643[97] = 0;
   out_2324287403941072643[98] = 0;
   out_2324287403941072643[99] = 0;
   out_2324287403941072643[100] = 0;
   out_2324287403941072643[101] = 0;
   out_2324287403941072643[102] = 0;
   out_2324287403941072643[103] = 0;
   out_2324287403941072643[104] = dt;
   out_2324287403941072643[105] = 0;
   out_2324287403941072643[106] = 0;
   out_2324287403941072643[107] = 0;
   out_2324287403941072643[108] = 0;
   out_2324287403941072643[109] = 0;
   out_2324287403941072643[110] = 0;
   out_2324287403941072643[111] = 0;
   out_2324287403941072643[112] = 0;
   out_2324287403941072643[113] = 0;
   out_2324287403941072643[114] = 1;
   out_2324287403941072643[115] = 0;
   out_2324287403941072643[116] = 0;
   out_2324287403941072643[117] = 0;
   out_2324287403941072643[118] = 0;
   out_2324287403941072643[119] = 0;
   out_2324287403941072643[120] = 0;
   out_2324287403941072643[121] = 0;
   out_2324287403941072643[122] = 0;
   out_2324287403941072643[123] = 0;
   out_2324287403941072643[124] = 0;
   out_2324287403941072643[125] = 0;
   out_2324287403941072643[126] = 0;
   out_2324287403941072643[127] = 0;
   out_2324287403941072643[128] = 0;
   out_2324287403941072643[129] = 0;
   out_2324287403941072643[130] = 0;
   out_2324287403941072643[131] = 0;
   out_2324287403941072643[132] = 0;
   out_2324287403941072643[133] = 1;
   out_2324287403941072643[134] = 0;
   out_2324287403941072643[135] = 0;
   out_2324287403941072643[136] = 0;
   out_2324287403941072643[137] = 0;
   out_2324287403941072643[138] = 0;
   out_2324287403941072643[139] = 0;
   out_2324287403941072643[140] = 0;
   out_2324287403941072643[141] = 0;
   out_2324287403941072643[142] = 0;
   out_2324287403941072643[143] = 0;
   out_2324287403941072643[144] = 0;
   out_2324287403941072643[145] = 0;
   out_2324287403941072643[146] = 0;
   out_2324287403941072643[147] = 0;
   out_2324287403941072643[148] = 0;
   out_2324287403941072643[149] = 0;
   out_2324287403941072643[150] = 0;
   out_2324287403941072643[151] = 0;
   out_2324287403941072643[152] = 1;
   out_2324287403941072643[153] = 0;
   out_2324287403941072643[154] = 0;
   out_2324287403941072643[155] = 0;
   out_2324287403941072643[156] = 0;
   out_2324287403941072643[157] = 0;
   out_2324287403941072643[158] = 0;
   out_2324287403941072643[159] = 0;
   out_2324287403941072643[160] = 0;
   out_2324287403941072643[161] = 0;
   out_2324287403941072643[162] = 0;
   out_2324287403941072643[163] = 0;
   out_2324287403941072643[164] = 0;
   out_2324287403941072643[165] = 0;
   out_2324287403941072643[166] = 0;
   out_2324287403941072643[167] = 0;
   out_2324287403941072643[168] = 0;
   out_2324287403941072643[169] = 0;
   out_2324287403941072643[170] = 0;
   out_2324287403941072643[171] = 1;
   out_2324287403941072643[172] = 0;
   out_2324287403941072643[173] = 0;
   out_2324287403941072643[174] = 0;
   out_2324287403941072643[175] = 0;
   out_2324287403941072643[176] = 0;
   out_2324287403941072643[177] = 0;
   out_2324287403941072643[178] = 0;
   out_2324287403941072643[179] = 0;
   out_2324287403941072643[180] = 0;
   out_2324287403941072643[181] = 0;
   out_2324287403941072643[182] = 0;
   out_2324287403941072643[183] = 0;
   out_2324287403941072643[184] = 0;
   out_2324287403941072643[185] = 0;
   out_2324287403941072643[186] = 0;
   out_2324287403941072643[187] = 0;
   out_2324287403941072643[188] = 0;
   out_2324287403941072643[189] = 0;
   out_2324287403941072643[190] = 1;
   out_2324287403941072643[191] = 0;
   out_2324287403941072643[192] = 0;
   out_2324287403941072643[193] = 0;
   out_2324287403941072643[194] = 0;
   out_2324287403941072643[195] = 0;
   out_2324287403941072643[196] = 0;
   out_2324287403941072643[197] = 0;
   out_2324287403941072643[198] = 0;
   out_2324287403941072643[199] = 0;
   out_2324287403941072643[200] = 0;
   out_2324287403941072643[201] = 0;
   out_2324287403941072643[202] = 0;
   out_2324287403941072643[203] = 0;
   out_2324287403941072643[204] = 0;
   out_2324287403941072643[205] = 0;
   out_2324287403941072643[206] = 0;
   out_2324287403941072643[207] = 0;
   out_2324287403941072643[208] = 0;
   out_2324287403941072643[209] = 1;
   out_2324287403941072643[210] = 0;
   out_2324287403941072643[211] = 0;
   out_2324287403941072643[212] = 0;
   out_2324287403941072643[213] = 0;
   out_2324287403941072643[214] = 0;
   out_2324287403941072643[215] = 0;
   out_2324287403941072643[216] = 0;
   out_2324287403941072643[217] = 0;
   out_2324287403941072643[218] = 0;
   out_2324287403941072643[219] = 0;
   out_2324287403941072643[220] = 0;
   out_2324287403941072643[221] = 0;
   out_2324287403941072643[222] = 0;
   out_2324287403941072643[223] = 0;
   out_2324287403941072643[224] = 0;
   out_2324287403941072643[225] = 0;
   out_2324287403941072643[226] = 0;
   out_2324287403941072643[227] = 0;
   out_2324287403941072643[228] = 1;
   out_2324287403941072643[229] = 0;
   out_2324287403941072643[230] = 0;
   out_2324287403941072643[231] = 0;
   out_2324287403941072643[232] = 0;
   out_2324287403941072643[233] = 0;
   out_2324287403941072643[234] = 0;
   out_2324287403941072643[235] = 0;
   out_2324287403941072643[236] = 0;
   out_2324287403941072643[237] = 0;
   out_2324287403941072643[238] = 0;
   out_2324287403941072643[239] = 0;
   out_2324287403941072643[240] = 0;
   out_2324287403941072643[241] = 0;
   out_2324287403941072643[242] = 0;
   out_2324287403941072643[243] = 0;
   out_2324287403941072643[244] = 0;
   out_2324287403941072643[245] = 0;
   out_2324287403941072643[246] = 0;
   out_2324287403941072643[247] = 1;
   out_2324287403941072643[248] = 0;
   out_2324287403941072643[249] = 0;
   out_2324287403941072643[250] = 0;
   out_2324287403941072643[251] = 0;
   out_2324287403941072643[252] = 0;
   out_2324287403941072643[253] = 0;
   out_2324287403941072643[254] = 0;
   out_2324287403941072643[255] = 0;
   out_2324287403941072643[256] = 0;
   out_2324287403941072643[257] = 0;
   out_2324287403941072643[258] = 0;
   out_2324287403941072643[259] = 0;
   out_2324287403941072643[260] = 0;
   out_2324287403941072643[261] = 0;
   out_2324287403941072643[262] = 0;
   out_2324287403941072643[263] = 0;
   out_2324287403941072643[264] = 0;
   out_2324287403941072643[265] = 0;
   out_2324287403941072643[266] = 1;
   out_2324287403941072643[267] = 0;
   out_2324287403941072643[268] = 0;
   out_2324287403941072643[269] = 0;
   out_2324287403941072643[270] = 0;
   out_2324287403941072643[271] = 0;
   out_2324287403941072643[272] = 0;
   out_2324287403941072643[273] = 0;
   out_2324287403941072643[274] = 0;
   out_2324287403941072643[275] = 0;
   out_2324287403941072643[276] = 0;
   out_2324287403941072643[277] = 0;
   out_2324287403941072643[278] = 0;
   out_2324287403941072643[279] = 0;
   out_2324287403941072643[280] = 0;
   out_2324287403941072643[281] = 0;
   out_2324287403941072643[282] = 0;
   out_2324287403941072643[283] = 0;
   out_2324287403941072643[284] = 0;
   out_2324287403941072643[285] = 1;
   out_2324287403941072643[286] = 0;
   out_2324287403941072643[287] = 0;
   out_2324287403941072643[288] = 0;
   out_2324287403941072643[289] = 0;
   out_2324287403941072643[290] = 0;
   out_2324287403941072643[291] = 0;
   out_2324287403941072643[292] = 0;
   out_2324287403941072643[293] = 0;
   out_2324287403941072643[294] = 0;
   out_2324287403941072643[295] = 0;
   out_2324287403941072643[296] = 0;
   out_2324287403941072643[297] = 0;
   out_2324287403941072643[298] = 0;
   out_2324287403941072643[299] = 0;
   out_2324287403941072643[300] = 0;
   out_2324287403941072643[301] = 0;
   out_2324287403941072643[302] = 0;
   out_2324287403941072643[303] = 0;
   out_2324287403941072643[304] = 1;
   out_2324287403941072643[305] = 0;
   out_2324287403941072643[306] = 0;
   out_2324287403941072643[307] = 0;
   out_2324287403941072643[308] = 0;
   out_2324287403941072643[309] = 0;
   out_2324287403941072643[310] = 0;
   out_2324287403941072643[311] = 0;
   out_2324287403941072643[312] = 0;
   out_2324287403941072643[313] = 0;
   out_2324287403941072643[314] = 0;
   out_2324287403941072643[315] = 0;
   out_2324287403941072643[316] = 0;
   out_2324287403941072643[317] = 0;
   out_2324287403941072643[318] = 0;
   out_2324287403941072643[319] = 0;
   out_2324287403941072643[320] = 0;
   out_2324287403941072643[321] = 0;
   out_2324287403941072643[322] = 0;
   out_2324287403941072643[323] = 1;
}
void h_4(double *state, double *unused, double *out_3295127809911230665) {
   out_3295127809911230665[0] = state[6] + state[9];
   out_3295127809911230665[1] = state[7] + state[10];
   out_3295127809911230665[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_8270265206520041021) {
   out_8270265206520041021[0] = 0;
   out_8270265206520041021[1] = 0;
   out_8270265206520041021[2] = 0;
   out_8270265206520041021[3] = 0;
   out_8270265206520041021[4] = 0;
   out_8270265206520041021[5] = 0;
   out_8270265206520041021[6] = 1;
   out_8270265206520041021[7] = 0;
   out_8270265206520041021[8] = 0;
   out_8270265206520041021[9] = 1;
   out_8270265206520041021[10] = 0;
   out_8270265206520041021[11] = 0;
   out_8270265206520041021[12] = 0;
   out_8270265206520041021[13] = 0;
   out_8270265206520041021[14] = 0;
   out_8270265206520041021[15] = 0;
   out_8270265206520041021[16] = 0;
   out_8270265206520041021[17] = 0;
   out_8270265206520041021[18] = 0;
   out_8270265206520041021[19] = 0;
   out_8270265206520041021[20] = 0;
   out_8270265206520041021[21] = 0;
   out_8270265206520041021[22] = 0;
   out_8270265206520041021[23] = 0;
   out_8270265206520041021[24] = 0;
   out_8270265206520041021[25] = 1;
   out_8270265206520041021[26] = 0;
   out_8270265206520041021[27] = 0;
   out_8270265206520041021[28] = 1;
   out_8270265206520041021[29] = 0;
   out_8270265206520041021[30] = 0;
   out_8270265206520041021[31] = 0;
   out_8270265206520041021[32] = 0;
   out_8270265206520041021[33] = 0;
   out_8270265206520041021[34] = 0;
   out_8270265206520041021[35] = 0;
   out_8270265206520041021[36] = 0;
   out_8270265206520041021[37] = 0;
   out_8270265206520041021[38] = 0;
   out_8270265206520041021[39] = 0;
   out_8270265206520041021[40] = 0;
   out_8270265206520041021[41] = 0;
   out_8270265206520041021[42] = 0;
   out_8270265206520041021[43] = 0;
   out_8270265206520041021[44] = 1;
   out_8270265206520041021[45] = 0;
   out_8270265206520041021[46] = 0;
   out_8270265206520041021[47] = 1;
   out_8270265206520041021[48] = 0;
   out_8270265206520041021[49] = 0;
   out_8270265206520041021[50] = 0;
   out_8270265206520041021[51] = 0;
   out_8270265206520041021[52] = 0;
   out_8270265206520041021[53] = 0;
}
void h_10(double *state, double *unused, double *out_3863591942336910664) {
   out_3863591942336910664[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3863591942336910664[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3863591942336910664[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6343727255885996060) {
   out_6343727255885996060[0] = 0;
   out_6343727255885996060[1] = 9.8100000000000005*cos(state[1]);
   out_6343727255885996060[2] = 0;
   out_6343727255885996060[3] = 0;
   out_6343727255885996060[4] = -state[8];
   out_6343727255885996060[5] = state[7];
   out_6343727255885996060[6] = 0;
   out_6343727255885996060[7] = state[5];
   out_6343727255885996060[8] = -state[4];
   out_6343727255885996060[9] = 0;
   out_6343727255885996060[10] = 0;
   out_6343727255885996060[11] = 0;
   out_6343727255885996060[12] = 1;
   out_6343727255885996060[13] = 0;
   out_6343727255885996060[14] = 0;
   out_6343727255885996060[15] = 1;
   out_6343727255885996060[16] = 0;
   out_6343727255885996060[17] = 0;
   out_6343727255885996060[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6343727255885996060[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6343727255885996060[20] = 0;
   out_6343727255885996060[21] = state[8];
   out_6343727255885996060[22] = 0;
   out_6343727255885996060[23] = -state[6];
   out_6343727255885996060[24] = -state[5];
   out_6343727255885996060[25] = 0;
   out_6343727255885996060[26] = state[3];
   out_6343727255885996060[27] = 0;
   out_6343727255885996060[28] = 0;
   out_6343727255885996060[29] = 0;
   out_6343727255885996060[30] = 0;
   out_6343727255885996060[31] = 1;
   out_6343727255885996060[32] = 0;
   out_6343727255885996060[33] = 0;
   out_6343727255885996060[34] = 1;
   out_6343727255885996060[35] = 0;
   out_6343727255885996060[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6343727255885996060[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6343727255885996060[38] = 0;
   out_6343727255885996060[39] = -state[7];
   out_6343727255885996060[40] = state[6];
   out_6343727255885996060[41] = 0;
   out_6343727255885996060[42] = state[4];
   out_6343727255885996060[43] = -state[3];
   out_6343727255885996060[44] = 0;
   out_6343727255885996060[45] = 0;
   out_6343727255885996060[46] = 0;
   out_6343727255885996060[47] = 0;
   out_6343727255885996060[48] = 0;
   out_6343727255885996060[49] = 0;
   out_6343727255885996060[50] = 1;
   out_6343727255885996060[51] = 0;
   out_6343727255885996060[52] = 0;
   out_6343727255885996060[53] = 1;
}
void h_13(double *state, double *unused, double *out_3880954183827223653) {
   out_3880954183827223653[0] = state[3];
   out_3880954183827223653[1] = state[4];
   out_3880954183827223653[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6964205041857177794) {
   out_6964205041857177794[0] = 0;
   out_6964205041857177794[1] = 0;
   out_6964205041857177794[2] = 0;
   out_6964205041857177794[3] = 1;
   out_6964205041857177794[4] = 0;
   out_6964205041857177794[5] = 0;
   out_6964205041857177794[6] = 0;
   out_6964205041857177794[7] = 0;
   out_6964205041857177794[8] = 0;
   out_6964205041857177794[9] = 0;
   out_6964205041857177794[10] = 0;
   out_6964205041857177794[11] = 0;
   out_6964205041857177794[12] = 0;
   out_6964205041857177794[13] = 0;
   out_6964205041857177794[14] = 0;
   out_6964205041857177794[15] = 0;
   out_6964205041857177794[16] = 0;
   out_6964205041857177794[17] = 0;
   out_6964205041857177794[18] = 0;
   out_6964205041857177794[19] = 0;
   out_6964205041857177794[20] = 0;
   out_6964205041857177794[21] = 0;
   out_6964205041857177794[22] = 1;
   out_6964205041857177794[23] = 0;
   out_6964205041857177794[24] = 0;
   out_6964205041857177794[25] = 0;
   out_6964205041857177794[26] = 0;
   out_6964205041857177794[27] = 0;
   out_6964205041857177794[28] = 0;
   out_6964205041857177794[29] = 0;
   out_6964205041857177794[30] = 0;
   out_6964205041857177794[31] = 0;
   out_6964205041857177794[32] = 0;
   out_6964205041857177794[33] = 0;
   out_6964205041857177794[34] = 0;
   out_6964205041857177794[35] = 0;
   out_6964205041857177794[36] = 0;
   out_6964205041857177794[37] = 0;
   out_6964205041857177794[38] = 0;
   out_6964205041857177794[39] = 0;
   out_6964205041857177794[40] = 0;
   out_6964205041857177794[41] = 1;
   out_6964205041857177794[42] = 0;
   out_6964205041857177794[43] = 0;
   out_6964205041857177794[44] = 0;
   out_6964205041857177794[45] = 0;
   out_6964205041857177794[46] = 0;
   out_6964205041857177794[47] = 0;
   out_6964205041857177794[48] = 0;
   out_6964205041857177794[49] = 0;
   out_6964205041857177794[50] = 0;
   out_6964205041857177794[51] = 0;
   out_6964205041857177794[52] = 0;
   out_6964205041857177794[53] = 0;
}
void h_14(double *state, double *unused, double *out_8209348319732836111) {
   out_8209348319732836111[0] = state[6];
   out_8209348319732836111[1] = state[7];
   out_8209348319732836111[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5187476774224668725) {
   out_5187476774224668725[0] = 0;
   out_5187476774224668725[1] = 0;
   out_5187476774224668725[2] = 0;
   out_5187476774224668725[3] = 0;
   out_5187476774224668725[4] = 0;
   out_5187476774224668725[5] = 0;
   out_5187476774224668725[6] = 1;
   out_5187476774224668725[7] = 0;
   out_5187476774224668725[8] = 0;
   out_5187476774224668725[9] = 0;
   out_5187476774224668725[10] = 0;
   out_5187476774224668725[11] = 0;
   out_5187476774224668725[12] = 0;
   out_5187476774224668725[13] = 0;
   out_5187476774224668725[14] = 0;
   out_5187476774224668725[15] = 0;
   out_5187476774224668725[16] = 0;
   out_5187476774224668725[17] = 0;
   out_5187476774224668725[18] = 0;
   out_5187476774224668725[19] = 0;
   out_5187476774224668725[20] = 0;
   out_5187476774224668725[21] = 0;
   out_5187476774224668725[22] = 0;
   out_5187476774224668725[23] = 0;
   out_5187476774224668725[24] = 0;
   out_5187476774224668725[25] = 1;
   out_5187476774224668725[26] = 0;
   out_5187476774224668725[27] = 0;
   out_5187476774224668725[28] = 0;
   out_5187476774224668725[29] = 0;
   out_5187476774224668725[30] = 0;
   out_5187476774224668725[31] = 0;
   out_5187476774224668725[32] = 0;
   out_5187476774224668725[33] = 0;
   out_5187476774224668725[34] = 0;
   out_5187476774224668725[35] = 0;
   out_5187476774224668725[36] = 0;
   out_5187476774224668725[37] = 0;
   out_5187476774224668725[38] = 0;
   out_5187476774224668725[39] = 0;
   out_5187476774224668725[40] = 0;
   out_5187476774224668725[41] = 0;
   out_5187476774224668725[42] = 0;
   out_5187476774224668725[43] = 0;
   out_5187476774224668725[44] = 1;
   out_5187476774224668725[45] = 0;
   out_5187476774224668725[46] = 0;
   out_5187476774224668725[47] = 0;
   out_5187476774224668725[48] = 0;
   out_5187476774224668725[49] = 0;
   out_5187476774224668725[50] = 0;
   out_5187476774224668725[51] = 0;
   out_5187476774224668725[52] = 0;
   out_5187476774224668725[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_6169503642516981710) {
  err_fun(nom_x, delta_x, out_6169503642516981710);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2781558835044378693) {
  inv_err_fun(nom_x, true_x, out_2781558835044378693);
}
void pose_H_mod_fun(double *state, double *out_4498457996676133449) {
  H_mod_fun(state, out_4498457996676133449);
}
void pose_f_fun(double *state, double dt, double *out_3471362747861957887) {
  f_fun(state,  dt, out_3471362747861957887);
}
void pose_F_fun(double *state, double dt, double *out_2324287403941072643) {
  F_fun(state,  dt, out_2324287403941072643);
}
void pose_h_4(double *state, double *unused, double *out_3295127809911230665) {
  h_4(state, unused, out_3295127809911230665);
}
void pose_H_4(double *state, double *unused, double *out_8270265206520041021) {
  H_4(state, unused, out_8270265206520041021);
}
void pose_h_10(double *state, double *unused, double *out_3863591942336910664) {
  h_10(state, unused, out_3863591942336910664);
}
void pose_H_10(double *state, double *unused, double *out_6343727255885996060) {
  H_10(state, unused, out_6343727255885996060);
}
void pose_h_13(double *state, double *unused, double *out_3880954183827223653) {
  h_13(state, unused, out_3880954183827223653);
}
void pose_H_13(double *state, double *unused, double *out_6964205041857177794) {
  H_13(state, unused, out_6964205041857177794);
}
void pose_h_14(double *state, double *unused, double *out_8209348319732836111) {
  h_14(state, unused, out_8209348319732836111);
}
void pose_H_14(double *state, double *unused, double *out_5187476774224668725) {
  H_14(state, unused, out_5187476774224668725);
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
