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
void err_fun(double *nom_x, double *delta_x, double *out_1493079546624007114) {
   out_1493079546624007114[0] = delta_x[0] + nom_x[0];
   out_1493079546624007114[1] = delta_x[1] + nom_x[1];
   out_1493079546624007114[2] = delta_x[2] + nom_x[2];
   out_1493079546624007114[3] = delta_x[3] + nom_x[3];
   out_1493079546624007114[4] = delta_x[4] + nom_x[4];
   out_1493079546624007114[5] = delta_x[5] + nom_x[5];
   out_1493079546624007114[6] = delta_x[6] + nom_x[6];
   out_1493079546624007114[7] = delta_x[7] + nom_x[7];
   out_1493079546624007114[8] = delta_x[8] + nom_x[8];
   out_1493079546624007114[9] = delta_x[9] + nom_x[9];
   out_1493079546624007114[10] = delta_x[10] + nom_x[10];
   out_1493079546624007114[11] = delta_x[11] + nom_x[11];
   out_1493079546624007114[12] = delta_x[12] + nom_x[12];
   out_1493079546624007114[13] = delta_x[13] + nom_x[13];
   out_1493079546624007114[14] = delta_x[14] + nom_x[14];
   out_1493079546624007114[15] = delta_x[15] + nom_x[15];
   out_1493079546624007114[16] = delta_x[16] + nom_x[16];
   out_1493079546624007114[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4580499654968994478) {
   out_4580499654968994478[0] = -nom_x[0] + true_x[0];
   out_4580499654968994478[1] = -nom_x[1] + true_x[1];
   out_4580499654968994478[2] = -nom_x[2] + true_x[2];
   out_4580499654968994478[3] = -nom_x[3] + true_x[3];
   out_4580499654968994478[4] = -nom_x[4] + true_x[4];
   out_4580499654968994478[5] = -nom_x[5] + true_x[5];
   out_4580499654968994478[6] = -nom_x[6] + true_x[6];
   out_4580499654968994478[7] = -nom_x[7] + true_x[7];
   out_4580499654968994478[8] = -nom_x[8] + true_x[8];
   out_4580499654968994478[9] = -nom_x[9] + true_x[9];
   out_4580499654968994478[10] = -nom_x[10] + true_x[10];
   out_4580499654968994478[11] = -nom_x[11] + true_x[11];
   out_4580499654968994478[12] = -nom_x[12] + true_x[12];
   out_4580499654968994478[13] = -nom_x[13] + true_x[13];
   out_4580499654968994478[14] = -nom_x[14] + true_x[14];
   out_4580499654968994478[15] = -nom_x[15] + true_x[15];
   out_4580499654968994478[16] = -nom_x[16] + true_x[16];
   out_4580499654968994478[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_8273119377234766952) {
   out_8273119377234766952[0] = 1.0;
   out_8273119377234766952[1] = 0.0;
   out_8273119377234766952[2] = 0.0;
   out_8273119377234766952[3] = 0.0;
   out_8273119377234766952[4] = 0.0;
   out_8273119377234766952[5] = 0.0;
   out_8273119377234766952[6] = 0.0;
   out_8273119377234766952[7] = 0.0;
   out_8273119377234766952[8] = 0.0;
   out_8273119377234766952[9] = 0.0;
   out_8273119377234766952[10] = 0.0;
   out_8273119377234766952[11] = 0.0;
   out_8273119377234766952[12] = 0.0;
   out_8273119377234766952[13] = 0.0;
   out_8273119377234766952[14] = 0.0;
   out_8273119377234766952[15] = 0.0;
   out_8273119377234766952[16] = 0.0;
   out_8273119377234766952[17] = 0.0;
   out_8273119377234766952[18] = 0.0;
   out_8273119377234766952[19] = 1.0;
   out_8273119377234766952[20] = 0.0;
   out_8273119377234766952[21] = 0.0;
   out_8273119377234766952[22] = 0.0;
   out_8273119377234766952[23] = 0.0;
   out_8273119377234766952[24] = 0.0;
   out_8273119377234766952[25] = 0.0;
   out_8273119377234766952[26] = 0.0;
   out_8273119377234766952[27] = 0.0;
   out_8273119377234766952[28] = 0.0;
   out_8273119377234766952[29] = 0.0;
   out_8273119377234766952[30] = 0.0;
   out_8273119377234766952[31] = 0.0;
   out_8273119377234766952[32] = 0.0;
   out_8273119377234766952[33] = 0.0;
   out_8273119377234766952[34] = 0.0;
   out_8273119377234766952[35] = 0.0;
   out_8273119377234766952[36] = 0.0;
   out_8273119377234766952[37] = 0.0;
   out_8273119377234766952[38] = 1.0;
   out_8273119377234766952[39] = 0.0;
   out_8273119377234766952[40] = 0.0;
   out_8273119377234766952[41] = 0.0;
   out_8273119377234766952[42] = 0.0;
   out_8273119377234766952[43] = 0.0;
   out_8273119377234766952[44] = 0.0;
   out_8273119377234766952[45] = 0.0;
   out_8273119377234766952[46] = 0.0;
   out_8273119377234766952[47] = 0.0;
   out_8273119377234766952[48] = 0.0;
   out_8273119377234766952[49] = 0.0;
   out_8273119377234766952[50] = 0.0;
   out_8273119377234766952[51] = 0.0;
   out_8273119377234766952[52] = 0.0;
   out_8273119377234766952[53] = 0.0;
   out_8273119377234766952[54] = 0.0;
   out_8273119377234766952[55] = 0.0;
   out_8273119377234766952[56] = 0.0;
   out_8273119377234766952[57] = 1.0;
   out_8273119377234766952[58] = 0.0;
   out_8273119377234766952[59] = 0.0;
   out_8273119377234766952[60] = 0.0;
   out_8273119377234766952[61] = 0.0;
   out_8273119377234766952[62] = 0.0;
   out_8273119377234766952[63] = 0.0;
   out_8273119377234766952[64] = 0.0;
   out_8273119377234766952[65] = 0.0;
   out_8273119377234766952[66] = 0.0;
   out_8273119377234766952[67] = 0.0;
   out_8273119377234766952[68] = 0.0;
   out_8273119377234766952[69] = 0.0;
   out_8273119377234766952[70] = 0.0;
   out_8273119377234766952[71] = 0.0;
   out_8273119377234766952[72] = 0.0;
   out_8273119377234766952[73] = 0.0;
   out_8273119377234766952[74] = 0.0;
   out_8273119377234766952[75] = 0.0;
   out_8273119377234766952[76] = 1.0;
   out_8273119377234766952[77] = 0.0;
   out_8273119377234766952[78] = 0.0;
   out_8273119377234766952[79] = 0.0;
   out_8273119377234766952[80] = 0.0;
   out_8273119377234766952[81] = 0.0;
   out_8273119377234766952[82] = 0.0;
   out_8273119377234766952[83] = 0.0;
   out_8273119377234766952[84] = 0.0;
   out_8273119377234766952[85] = 0.0;
   out_8273119377234766952[86] = 0.0;
   out_8273119377234766952[87] = 0.0;
   out_8273119377234766952[88] = 0.0;
   out_8273119377234766952[89] = 0.0;
   out_8273119377234766952[90] = 0.0;
   out_8273119377234766952[91] = 0.0;
   out_8273119377234766952[92] = 0.0;
   out_8273119377234766952[93] = 0.0;
   out_8273119377234766952[94] = 0.0;
   out_8273119377234766952[95] = 1.0;
   out_8273119377234766952[96] = 0.0;
   out_8273119377234766952[97] = 0.0;
   out_8273119377234766952[98] = 0.0;
   out_8273119377234766952[99] = 0.0;
   out_8273119377234766952[100] = 0.0;
   out_8273119377234766952[101] = 0.0;
   out_8273119377234766952[102] = 0.0;
   out_8273119377234766952[103] = 0.0;
   out_8273119377234766952[104] = 0.0;
   out_8273119377234766952[105] = 0.0;
   out_8273119377234766952[106] = 0.0;
   out_8273119377234766952[107] = 0.0;
   out_8273119377234766952[108] = 0.0;
   out_8273119377234766952[109] = 0.0;
   out_8273119377234766952[110] = 0.0;
   out_8273119377234766952[111] = 0.0;
   out_8273119377234766952[112] = 0.0;
   out_8273119377234766952[113] = 0.0;
   out_8273119377234766952[114] = 1.0;
   out_8273119377234766952[115] = 0.0;
   out_8273119377234766952[116] = 0.0;
   out_8273119377234766952[117] = 0.0;
   out_8273119377234766952[118] = 0.0;
   out_8273119377234766952[119] = 0.0;
   out_8273119377234766952[120] = 0.0;
   out_8273119377234766952[121] = 0.0;
   out_8273119377234766952[122] = 0.0;
   out_8273119377234766952[123] = 0.0;
   out_8273119377234766952[124] = 0.0;
   out_8273119377234766952[125] = 0.0;
   out_8273119377234766952[126] = 0.0;
   out_8273119377234766952[127] = 0.0;
   out_8273119377234766952[128] = 0.0;
   out_8273119377234766952[129] = 0.0;
   out_8273119377234766952[130] = 0.0;
   out_8273119377234766952[131] = 0.0;
   out_8273119377234766952[132] = 0.0;
   out_8273119377234766952[133] = 1.0;
   out_8273119377234766952[134] = 0.0;
   out_8273119377234766952[135] = 0.0;
   out_8273119377234766952[136] = 0.0;
   out_8273119377234766952[137] = 0.0;
   out_8273119377234766952[138] = 0.0;
   out_8273119377234766952[139] = 0.0;
   out_8273119377234766952[140] = 0.0;
   out_8273119377234766952[141] = 0.0;
   out_8273119377234766952[142] = 0.0;
   out_8273119377234766952[143] = 0.0;
   out_8273119377234766952[144] = 0.0;
   out_8273119377234766952[145] = 0.0;
   out_8273119377234766952[146] = 0.0;
   out_8273119377234766952[147] = 0.0;
   out_8273119377234766952[148] = 0.0;
   out_8273119377234766952[149] = 0.0;
   out_8273119377234766952[150] = 0.0;
   out_8273119377234766952[151] = 0.0;
   out_8273119377234766952[152] = 1.0;
   out_8273119377234766952[153] = 0.0;
   out_8273119377234766952[154] = 0.0;
   out_8273119377234766952[155] = 0.0;
   out_8273119377234766952[156] = 0.0;
   out_8273119377234766952[157] = 0.0;
   out_8273119377234766952[158] = 0.0;
   out_8273119377234766952[159] = 0.0;
   out_8273119377234766952[160] = 0.0;
   out_8273119377234766952[161] = 0.0;
   out_8273119377234766952[162] = 0.0;
   out_8273119377234766952[163] = 0.0;
   out_8273119377234766952[164] = 0.0;
   out_8273119377234766952[165] = 0.0;
   out_8273119377234766952[166] = 0.0;
   out_8273119377234766952[167] = 0.0;
   out_8273119377234766952[168] = 0.0;
   out_8273119377234766952[169] = 0.0;
   out_8273119377234766952[170] = 0.0;
   out_8273119377234766952[171] = 1.0;
   out_8273119377234766952[172] = 0.0;
   out_8273119377234766952[173] = 0.0;
   out_8273119377234766952[174] = 0.0;
   out_8273119377234766952[175] = 0.0;
   out_8273119377234766952[176] = 0.0;
   out_8273119377234766952[177] = 0.0;
   out_8273119377234766952[178] = 0.0;
   out_8273119377234766952[179] = 0.0;
   out_8273119377234766952[180] = 0.0;
   out_8273119377234766952[181] = 0.0;
   out_8273119377234766952[182] = 0.0;
   out_8273119377234766952[183] = 0.0;
   out_8273119377234766952[184] = 0.0;
   out_8273119377234766952[185] = 0.0;
   out_8273119377234766952[186] = 0.0;
   out_8273119377234766952[187] = 0.0;
   out_8273119377234766952[188] = 0.0;
   out_8273119377234766952[189] = 0.0;
   out_8273119377234766952[190] = 1.0;
   out_8273119377234766952[191] = 0.0;
   out_8273119377234766952[192] = 0.0;
   out_8273119377234766952[193] = 0.0;
   out_8273119377234766952[194] = 0.0;
   out_8273119377234766952[195] = 0.0;
   out_8273119377234766952[196] = 0.0;
   out_8273119377234766952[197] = 0.0;
   out_8273119377234766952[198] = 0.0;
   out_8273119377234766952[199] = 0.0;
   out_8273119377234766952[200] = 0.0;
   out_8273119377234766952[201] = 0.0;
   out_8273119377234766952[202] = 0.0;
   out_8273119377234766952[203] = 0.0;
   out_8273119377234766952[204] = 0.0;
   out_8273119377234766952[205] = 0.0;
   out_8273119377234766952[206] = 0.0;
   out_8273119377234766952[207] = 0.0;
   out_8273119377234766952[208] = 0.0;
   out_8273119377234766952[209] = 1.0;
   out_8273119377234766952[210] = 0.0;
   out_8273119377234766952[211] = 0.0;
   out_8273119377234766952[212] = 0.0;
   out_8273119377234766952[213] = 0.0;
   out_8273119377234766952[214] = 0.0;
   out_8273119377234766952[215] = 0.0;
   out_8273119377234766952[216] = 0.0;
   out_8273119377234766952[217] = 0.0;
   out_8273119377234766952[218] = 0.0;
   out_8273119377234766952[219] = 0.0;
   out_8273119377234766952[220] = 0.0;
   out_8273119377234766952[221] = 0.0;
   out_8273119377234766952[222] = 0.0;
   out_8273119377234766952[223] = 0.0;
   out_8273119377234766952[224] = 0.0;
   out_8273119377234766952[225] = 0.0;
   out_8273119377234766952[226] = 0.0;
   out_8273119377234766952[227] = 0.0;
   out_8273119377234766952[228] = 1.0;
   out_8273119377234766952[229] = 0.0;
   out_8273119377234766952[230] = 0.0;
   out_8273119377234766952[231] = 0.0;
   out_8273119377234766952[232] = 0.0;
   out_8273119377234766952[233] = 0.0;
   out_8273119377234766952[234] = 0.0;
   out_8273119377234766952[235] = 0.0;
   out_8273119377234766952[236] = 0.0;
   out_8273119377234766952[237] = 0.0;
   out_8273119377234766952[238] = 0.0;
   out_8273119377234766952[239] = 0.0;
   out_8273119377234766952[240] = 0.0;
   out_8273119377234766952[241] = 0.0;
   out_8273119377234766952[242] = 0.0;
   out_8273119377234766952[243] = 0.0;
   out_8273119377234766952[244] = 0.0;
   out_8273119377234766952[245] = 0.0;
   out_8273119377234766952[246] = 0.0;
   out_8273119377234766952[247] = 1.0;
   out_8273119377234766952[248] = 0.0;
   out_8273119377234766952[249] = 0.0;
   out_8273119377234766952[250] = 0.0;
   out_8273119377234766952[251] = 0.0;
   out_8273119377234766952[252] = 0.0;
   out_8273119377234766952[253] = 0.0;
   out_8273119377234766952[254] = 0.0;
   out_8273119377234766952[255] = 0.0;
   out_8273119377234766952[256] = 0.0;
   out_8273119377234766952[257] = 0.0;
   out_8273119377234766952[258] = 0.0;
   out_8273119377234766952[259] = 0.0;
   out_8273119377234766952[260] = 0.0;
   out_8273119377234766952[261] = 0.0;
   out_8273119377234766952[262] = 0.0;
   out_8273119377234766952[263] = 0.0;
   out_8273119377234766952[264] = 0.0;
   out_8273119377234766952[265] = 0.0;
   out_8273119377234766952[266] = 1.0;
   out_8273119377234766952[267] = 0.0;
   out_8273119377234766952[268] = 0.0;
   out_8273119377234766952[269] = 0.0;
   out_8273119377234766952[270] = 0.0;
   out_8273119377234766952[271] = 0.0;
   out_8273119377234766952[272] = 0.0;
   out_8273119377234766952[273] = 0.0;
   out_8273119377234766952[274] = 0.0;
   out_8273119377234766952[275] = 0.0;
   out_8273119377234766952[276] = 0.0;
   out_8273119377234766952[277] = 0.0;
   out_8273119377234766952[278] = 0.0;
   out_8273119377234766952[279] = 0.0;
   out_8273119377234766952[280] = 0.0;
   out_8273119377234766952[281] = 0.0;
   out_8273119377234766952[282] = 0.0;
   out_8273119377234766952[283] = 0.0;
   out_8273119377234766952[284] = 0.0;
   out_8273119377234766952[285] = 1.0;
   out_8273119377234766952[286] = 0.0;
   out_8273119377234766952[287] = 0.0;
   out_8273119377234766952[288] = 0.0;
   out_8273119377234766952[289] = 0.0;
   out_8273119377234766952[290] = 0.0;
   out_8273119377234766952[291] = 0.0;
   out_8273119377234766952[292] = 0.0;
   out_8273119377234766952[293] = 0.0;
   out_8273119377234766952[294] = 0.0;
   out_8273119377234766952[295] = 0.0;
   out_8273119377234766952[296] = 0.0;
   out_8273119377234766952[297] = 0.0;
   out_8273119377234766952[298] = 0.0;
   out_8273119377234766952[299] = 0.0;
   out_8273119377234766952[300] = 0.0;
   out_8273119377234766952[301] = 0.0;
   out_8273119377234766952[302] = 0.0;
   out_8273119377234766952[303] = 0.0;
   out_8273119377234766952[304] = 1.0;
   out_8273119377234766952[305] = 0.0;
   out_8273119377234766952[306] = 0.0;
   out_8273119377234766952[307] = 0.0;
   out_8273119377234766952[308] = 0.0;
   out_8273119377234766952[309] = 0.0;
   out_8273119377234766952[310] = 0.0;
   out_8273119377234766952[311] = 0.0;
   out_8273119377234766952[312] = 0.0;
   out_8273119377234766952[313] = 0.0;
   out_8273119377234766952[314] = 0.0;
   out_8273119377234766952[315] = 0.0;
   out_8273119377234766952[316] = 0.0;
   out_8273119377234766952[317] = 0.0;
   out_8273119377234766952[318] = 0.0;
   out_8273119377234766952[319] = 0.0;
   out_8273119377234766952[320] = 0.0;
   out_8273119377234766952[321] = 0.0;
   out_8273119377234766952[322] = 0.0;
   out_8273119377234766952[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_2742900412262200056) {
   out_2742900412262200056[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_2742900412262200056[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_2742900412262200056[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_2742900412262200056[3] = dt*state[12] + state[3];
   out_2742900412262200056[4] = dt*state[13] + state[4];
   out_2742900412262200056[5] = dt*state[14] + state[5];
   out_2742900412262200056[6] = state[6];
   out_2742900412262200056[7] = state[7];
   out_2742900412262200056[8] = state[8];
   out_2742900412262200056[9] = state[9];
   out_2742900412262200056[10] = state[10];
   out_2742900412262200056[11] = state[11];
   out_2742900412262200056[12] = state[12];
   out_2742900412262200056[13] = state[13];
   out_2742900412262200056[14] = state[14];
   out_2742900412262200056[15] = state[15];
   out_2742900412262200056[16] = state[16];
   out_2742900412262200056[17] = state[17];
}
void F_fun(double *state, double dt, double *out_1250059419478269226) {
   out_1250059419478269226[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1250059419478269226[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1250059419478269226[2] = 0;
   out_1250059419478269226[3] = 0;
   out_1250059419478269226[4] = 0;
   out_1250059419478269226[5] = 0;
   out_1250059419478269226[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1250059419478269226[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1250059419478269226[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1250059419478269226[9] = 0;
   out_1250059419478269226[10] = 0;
   out_1250059419478269226[11] = 0;
   out_1250059419478269226[12] = 0;
   out_1250059419478269226[13] = 0;
   out_1250059419478269226[14] = 0;
   out_1250059419478269226[15] = 0;
   out_1250059419478269226[16] = 0;
   out_1250059419478269226[17] = 0;
   out_1250059419478269226[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1250059419478269226[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1250059419478269226[20] = 0;
   out_1250059419478269226[21] = 0;
   out_1250059419478269226[22] = 0;
   out_1250059419478269226[23] = 0;
   out_1250059419478269226[24] = 0;
   out_1250059419478269226[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1250059419478269226[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1250059419478269226[27] = 0;
   out_1250059419478269226[28] = 0;
   out_1250059419478269226[29] = 0;
   out_1250059419478269226[30] = 0;
   out_1250059419478269226[31] = 0;
   out_1250059419478269226[32] = 0;
   out_1250059419478269226[33] = 0;
   out_1250059419478269226[34] = 0;
   out_1250059419478269226[35] = 0;
   out_1250059419478269226[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1250059419478269226[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1250059419478269226[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1250059419478269226[39] = 0;
   out_1250059419478269226[40] = 0;
   out_1250059419478269226[41] = 0;
   out_1250059419478269226[42] = 0;
   out_1250059419478269226[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1250059419478269226[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1250059419478269226[45] = 0;
   out_1250059419478269226[46] = 0;
   out_1250059419478269226[47] = 0;
   out_1250059419478269226[48] = 0;
   out_1250059419478269226[49] = 0;
   out_1250059419478269226[50] = 0;
   out_1250059419478269226[51] = 0;
   out_1250059419478269226[52] = 0;
   out_1250059419478269226[53] = 0;
   out_1250059419478269226[54] = 0;
   out_1250059419478269226[55] = 0;
   out_1250059419478269226[56] = 0;
   out_1250059419478269226[57] = 1;
   out_1250059419478269226[58] = 0;
   out_1250059419478269226[59] = 0;
   out_1250059419478269226[60] = 0;
   out_1250059419478269226[61] = 0;
   out_1250059419478269226[62] = 0;
   out_1250059419478269226[63] = 0;
   out_1250059419478269226[64] = 0;
   out_1250059419478269226[65] = 0;
   out_1250059419478269226[66] = dt;
   out_1250059419478269226[67] = 0;
   out_1250059419478269226[68] = 0;
   out_1250059419478269226[69] = 0;
   out_1250059419478269226[70] = 0;
   out_1250059419478269226[71] = 0;
   out_1250059419478269226[72] = 0;
   out_1250059419478269226[73] = 0;
   out_1250059419478269226[74] = 0;
   out_1250059419478269226[75] = 0;
   out_1250059419478269226[76] = 1;
   out_1250059419478269226[77] = 0;
   out_1250059419478269226[78] = 0;
   out_1250059419478269226[79] = 0;
   out_1250059419478269226[80] = 0;
   out_1250059419478269226[81] = 0;
   out_1250059419478269226[82] = 0;
   out_1250059419478269226[83] = 0;
   out_1250059419478269226[84] = 0;
   out_1250059419478269226[85] = dt;
   out_1250059419478269226[86] = 0;
   out_1250059419478269226[87] = 0;
   out_1250059419478269226[88] = 0;
   out_1250059419478269226[89] = 0;
   out_1250059419478269226[90] = 0;
   out_1250059419478269226[91] = 0;
   out_1250059419478269226[92] = 0;
   out_1250059419478269226[93] = 0;
   out_1250059419478269226[94] = 0;
   out_1250059419478269226[95] = 1;
   out_1250059419478269226[96] = 0;
   out_1250059419478269226[97] = 0;
   out_1250059419478269226[98] = 0;
   out_1250059419478269226[99] = 0;
   out_1250059419478269226[100] = 0;
   out_1250059419478269226[101] = 0;
   out_1250059419478269226[102] = 0;
   out_1250059419478269226[103] = 0;
   out_1250059419478269226[104] = dt;
   out_1250059419478269226[105] = 0;
   out_1250059419478269226[106] = 0;
   out_1250059419478269226[107] = 0;
   out_1250059419478269226[108] = 0;
   out_1250059419478269226[109] = 0;
   out_1250059419478269226[110] = 0;
   out_1250059419478269226[111] = 0;
   out_1250059419478269226[112] = 0;
   out_1250059419478269226[113] = 0;
   out_1250059419478269226[114] = 1;
   out_1250059419478269226[115] = 0;
   out_1250059419478269226[116] = 0;
   out_1250059419478269226[117] = 0;
   out_1250059419478269226[118] = 0;
   out_1250059419478269226[119] = 0;
   out_1250059419478269226[120] = 0;
   out_1250059419478269226[121] = 0;
   out_1250059419478269226[122] = 0;
   out_1250059419478269226[123] = 0;
   out_1250059419478269226[124] = 0;
   out_1250059419478269226[125] = 0;
   out_1250059419478269226[126] = 0;
   out_1250059419478269226[127] = 0;
   out_1250059419478269226[128] = 0;
   out_1250059419478269226[129] = 0;
   out_1250059419478269226[130] = 0;
   out_1250059419478269226[131] = 0;
   out_1250059419478269226[132] = 0;
   out_1250059419478269226[133] = 1;
   out_1250059419478269226[134] = 0;
   out_1250059419478269226[135] = 0;
   out_1250059419478269226[136] = 0;
   out_1250059419478269226[137] = 0;
   out_1250059419478269226[138] = 0;
   out_1250059419478269226[139] = 0;
   out_1250059419478269226[140] = 0;
   out_1250059419478269226[141] = 0;
   out_1250059419478269226[142] = 0;
   out_1250059419478269226[143] = 0;
   out_1250059419478269226[144] = 0;
   out_1250059419478269226[145] = 0;
   out_1250059419478269226[146] = 0;
   out_1250059419478269226[147] = 0;
   out_1250059419478269226[148] = 0;
   out_1250059419478269226[149] = 0;
   out_1250059419478269226[150] = 0;
   out_1250059419478269226[151] = 0;
   out_1250059419478269226[152] = 1;
   out_1250059419478269226[153] = 0;
   out_1250059419478269226[154] = 0;
   out_1250059419478269226[155] = 0;
   out_1250059419478269226[156] = 0;
   out_1250059419478269226[157] = 0;
   out_1250059419478269226[158] = 0;
   out_1250059419478269226[159] = 0;
   out_1250059419478269226[160] = 0;
   out_1250059419478269226[161] = 0;
   out_1250059419478269226[162] = 0;
   out_1250059419478269226[163] = 0;
   out_1250059419478269226[164] = 0;
   out_1250059419478269226[165] = 0;
   out_1250059419478269226[166] = 0;
   out_1250059419478269226[167] = 0;
   out_1250059419478269226[168] = 0;
   out_1250059419478269226[169] = 0;
   out_1250059419478269226[170] = 0;
   out_1250059419478269226[171] = 1;
   out_1250059419478269226[172] = 0;
   out_1250059419478269226[173] = 0;
   out_1250059419478269226[174] = 0;
   out_1250059419478269226[175] = 0;
   out_1250059419478269226[176] = 0;
   out_1250059419478269226[177] = 0;
   out_1250059419478269226[178] = 0;
   out_1250059419478269226[179] = 0;
   out_1250059419478269226[180] = 0;
   out_1250059419478269226[181] = 0;
   out_1250059419478269226[182] = 0;
   out_1250059419478269226[183] = 0;
   out_1250059419478269226[184] = 0;
   out_1250059419478269226[185] = 0;
   out_1250059419478269226[186] = 0;
   out_1250059419478269226[187] = 0;
   out_1250059419478269226[188] = 0;
   out_1250059419478269226[189] = 0;
   out_1250059419478269226[190] = 1;
   out_1250059419478269226[191] = 0;
   out_1250059419478269226[192] = 0;
   out_1250059419478269226[193] = 0;
   out_1250059419478269226[194] = 0;
   out_1250059419478269226[195] = 0;
   out_1250059419478269226[196] = 0;
   out_1250059419478269226[197] = 0;
   out_1250059419478269226[198] = 0;
   out_1250059419478269226[199] = 0;
   out_1250059419478269226[200] = 0;
   out_1250059419478269226[201] = 0;
   out_1250059419478269226[202] = 0;
   out_1250059419478269226[203] = 0;
   out_1250059419478269226[204] = 0;
   out_1250059419478269226[205] = 0;
   out_1250059419478269226[206] = 0;
   out_1250059419478269226[207] = 0;
   out_1250059419478269226[208] = 0;
   out_1250059419478269226[209] = 1;
   out_1250059419478269226[210] = 0;
   out_1250059419478269226[211] = 0;
   out_1250059419478269226[212] = 0;
   out_1250059419478269226[213] = 0;
   out_1250059419478269226[214] = 0;
   out_1250059419478269226[215] = 0;
   out_1250059419478269226[216] = 0;
   out_1250059419478269226[217] = 0;
   out_1250059419478269226[218] = 0;
   out_1250059419478269226[219] = 0;
   out_1250059419478269226[220] = 0;
   out_1250059419478269226[221] = 0;
   out_1250059419478269226[222] = 0;
   out_1250059419478269226[223] = 0;
   out_1250059419478269226[224] = 0;
   out_1250059419478269226[225] = 0;
   out_1250059419478269226[226] = 0;
   out_1250059419478269226[227] = 0;
   out_1250059419478269226[228] = 1;
   out_1250059419478269226[229] = 0;
   out_1250059419478269226[230] = 0;
   out_1250059419478269226[231] = 0;
   out_1250059419478269226[232] = 0;
   out_1250059419478269226[233] = 0;
   out_1250059419478269226[234] = 0;
   out_1250059419478269226[235] = 0;
   out_1250059419478269226[236] = 0;
   out_1250059419478269226[237] = 0;
   out_1250059419478269226[238] = 0;
   out_1250059419478269226[239] = 0;
   out_1250059419478269226[240] = 0;
   out_1250059419478269226[241] = 0;
   out_1250059419478269226[242] = 0;
   out_1250059419478269226[243] = 0;
   out_1250059419478269226[244] = 0;
   out_1250059419478269226[245] = 0;
   out_1250059419478269226[246] = 0;
   out_1250059419478269226[247] = 1;
   out_1250059419478269226[248] = 0;
   out_1250059419478269226[249] = 0;
   out_1250059419478269226[250] = 0;
   out_1250059419478269226[251] = 0;
   out_1250059419478269226[252] = 0;
   out_1250059419478269226[253] = 0;
   out_1250059419478269226[254] = 0;
   out_1250059419478269226[255] = 0;
   out_1250059419478269226[256] = 0;
   out_1250059419478269226[257] = 0;
   out_1250059419478269226[258] = 0;
   out_1250059419478269226[259] = 0;
   out_1250059419478269226[260] = 0;
   out_1250059419478269226[261] = 0;
   out_1250059419478269226[262] = 0;
   out_1250059419478269226[263] = 0;
   out_1250059419478269226[264] = 0;
   out_1250059419478269226[265] = 0;
   out_1250059419478269226[266] = 1;
   out_1250059419478269226[267] = 0;
   out_1250059419478269226[268] = 0;
   out_1250059419478269226[269] = 0;
   out_1250059419478269226[270] = 0;
   out_1250059419478269226[271] = 0;
   out_1250059419478269226[272] = 0;
   out_1250059419478269226[273] = 0;
   out_1250059419478269226[274] = 0;
   out_1250059419478269226[275] = 0;
   out_1250059419478269226[276] = 0;
   out_1250059419478269226[277] = 0;
   out_1250059419478269226[278] = 0;
   out_1250059419478269226[279] = 0;
   out_1250059419478269226[280] = 0;
   out_1250059419478269226[281] = 0;
   out_1250059419478269226[282] = 0;
   out_1250059419478269226[283] = 0;
   out_1250059419478269226[284] = 0;
   out_1250059419478269226[285] = 1;
   out_1250059419478269226[286] = 0;
   out_1250059419478269226[287] = 0;
   out_1250059419478269226[288] = 0;
   out_1250059419478269226[289] = 0;
   out_1250059419478269226[290] = 0;
   out_1250059419478269226[291] = 0;
   out_1250059419478269226[292] = 0;
   out_1250059419478269226[293] = 0;
   out_1250059419478269226[294] = 0;
   out_1250059419478269226[295] = 0;
   out_1250059419478269226[296] = 0;
   out_1250059419478269226[297] = 0;
   out_1250059419478269226[298] = 0;
   out_1250059419478269226[299] = 0;
   out_1250059419478269226[300] = 0;
   out_1250059419478269226[301] = 0;
   out_1250059419478269226[302] = 0;
   out_1250059419478269226[303] = 0;
   out_1250059419478269226[304] = 1;
   out_1250059419478269226[305] = 0;
   out_1250059419478269226[306] = 0;
   out_1250059419478269226[307] = 0;
   out_1250059419478269226[308] = 0;
   out_1250059419478269226[309] = 0;
   out_1250059419478269226[310] = 0;
   out_1250059419478269226[311] = 0;
   out_1250059419478269226[312] = 0;
   out_1250059419478269226[313] = 0;
   out_1250059419478269226[314] = 0;
   out_1250059419478269226[315] = 0;
   out_1250059419478269226[316] = 0;
   out_1250059419478269226[317] = 0;
   out_1250059419478269226[318] = 0;
   out_1250059419478269226[319] = 0;
   out_1250059419478269226[320] = 0;
   out_1250059419478269226[321] = 0;
   out_1250059419478269226[322] = 0;
   out_1250059419478269226[323] = 1;
}
void h_4(double *state, double *unused, double *out_6706399028598537324) {
   out_6706399028598537324[0] = state[6] + state[9];
   out_6706399028598537324[1] = state[7] + state[10];
   out_6706399028598537324[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1435428464391795526) {
   out_1435428464391795526[0] = 0;
   out_1435428464391795526[1] = 0;
   out_1435428464391795526[2] = 0;
   out_1435428464391795526[3] = 0;
   out_1435428464391795526[4] = 0;
   out_1435428464391795526[5] = 0;
   out_1435428464391795526[6] = 1;
   out_1435428464391795526[7] = 0;
   out_1435428464391795526[8] = 0;
   out_1435428464391795526[9] = 1;
   out_1435428464391795526[10] = 0;
   out_1435428464391795526[11] = 0;
   out_1435428464391795526[12] = 0;
   out_1435428464391795526[13] = 0;
   out_1435428464391795526[14] = 0;
   out_1435428464391795526[15] = 0;
   out_1435428464391795526[16] = 0;
   out_1435428464391795526[17] = 0;
   out_1435428464391795526[18] = 0;
   out_1435428464391795526[19] = 0;
   out_1435428464391795526[20] = 0;
   out_1435428464391795526[21] = 0;
   out_1435428464391795526[22] = 0;
   out_1435428464391795526[23] = 0;
   out_1435428464391795526[24] = 0;
   out_1435428464391795526[25] = 1;
   out_1435428464391795526[26] = 0;
   out_1435428464391795526[27] = 0;
   out_1435428464391795526[28] = 1;
   out_1435428464391795526[29] = 0;
   out_1435428464391795526[30] = 0;
   out_1435428464391795526[31] = 0;
   out_1435428464391795526[32] = 0;
   out_1435428464391795526[33] = 0;
   out_1435428464391795526[34] = 0;
   out_1435428464391795526[35] = 0;
   out_1435428464391795526[36] = 0;
   out_1435428464391795526[37] = 0;
   out_1435428464391795526[38] = 0;
   out_1435428464391795526[39] = 0;
   out_1435428464391795526[40] = 0;
   out_1435428464391795526[41] = 0;
   out_1435428464391795526[42] = 0;
   out_1435428464391795526[43] = 0;
   out_1435428464391795526[44] = 1;
   out_1435428464391795526[45] = 0;
   out_1435428464391795526[46] = 0;
   out_1435428464391795526[47] = 1;
   out_1435428464391795526[48] = 0;
   out_1435428464391795526[49] = 0;
   out_1435428464391795526[50] = 0;
   out_1435428464391795526[51] = 0;
   out_1435428464391795526[52] = 0;
   out_1435428464391795526[53] = 0;
}
void h_10(double *state, double *unused, double *out_3193952299746834757) {
   out_3193952299746834757[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3193952299746834757[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3193952299746834757[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1464924797507750077) {
   out_1464924797507750077[0] = 0;
   out_1464924797507750077[1] = 9.8100000000000005*cos(state[1]);
   out_1464924797507750077[2] = 0;
   out_1464924797507750077[3] = 0;
   out_1464924797507750077[4] = -state[8];
   out_1464924797507750077[5] = state[7];
   out_1464924797507750077[6] = 0;
   out_1464924797507750077[7] = state[5];
   out_1464924797507750077[8] = -state[4];
   out_1464924797507750077[9] = 0;
   out_1464924797507750077[10] = 0;
   out_1464924797507750077[11] = 0;
   out_1464924797507750077[12] = 1;
   out_1464924797507750077[13] = 0;
   out_1464924797507750077[14] = 0;
   out_1464924797507750077[15] = 1;
   out_1464924797507750077[16] = 0;
   out_1464924797507750077[17] = 0;
   out_1464924797507750077[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1464924797507750077[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1464924797507750077[20] = 0;
   out_1464924797507750077[21] = state[8];
   out_1464924797507750077[22] = 0;
   out_1464924797507750077[23] = -state[6];
   out_1464924797507750077[24] = -state[5];
   out_1464924797507750077[25] = 0;
   out_1464924797507750077[26] = state[3];
   out_1464924797507750077[27] = 0;
   out_1464924797507750077[28] = 0;
   out_1464924797507750077[29] = 0;
   out_1464924797507750077[30] = 0;
   out_1464924797507750077[31] = 1;
   out_1464924797507750077[32] = 0;
   out_1464924797507750077[33] = 0;
   out_1464924797507750077[34] = 1;
   out_1464924797507750077[35] = 0;
   out_1464924797507750077[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1464924797507750077[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1464924797507750077[38] = 0;
   out_1464924797507750077[39] = -state[7];
   out_1464924797507750077[40] = state[6];
   out_1464924797507750077[41] = 0;
   out_1464924797507750077[42] = state[4];
   out_1464924797507750077[43] = -state[3];
   out_1464924797507750077[44] = 0;
   out_1464924797507750077[45] = 0;
   out_1464924797507750077[46] = 0;
   out_1464924797507750077[47] = 0;
   out_1464924797507750077[48] = 0;
   out_1464924797507750077[49] = 0;
   out_1464924797507750077[50] = 1;
   out_1464924797507750077[51] = 0;
   out_1464924797507750077[52] = 0;
   out_1464924797507750077[53] = 1;
}
void h_13(double *state, double *unused, double *out_7802893222450228438) {
   out_7802893222450228438[0] = state[3];
   out_7802893222450228438[1] = state[4];
   out_7802893222450228438[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1776845360940537275) {
   out_1776845360940537275[0] = 0;
   out_1776845360940537275[1] = 0;
   out_1776845360940537275[2] = 0;
   out_1776845360940537275[3] = 1;
   out_1776845360940537275[4] = 0;
   out_1776845360940537275[5] = 0;
   out_1776845360940537275[6] = 0;
   out_1776845360940537275[7] = 0;
   out_1776845360940537275[8] = 0;
   out_1776845360940537275[9] = 0;
   out_1776845360940537275[10] = 0;
   out_1776845360940537275[11] = 0;
   out_1776845360940537275[12] = 0;
   out_1776845360940537275[13] = 0;
   out_1776845360940537275[14] = 0;
   out_1776845360940537275[15] = 0;
   out_1776845360940537275[16] = 0;
   out_1776845360940537275[17] = 0;
   out_1776845360940537275[18] = 0;
   out_1776845360940537275[19] = 0;
   out_1776845360940537275[20] = 0;
   out_1776845360940537275[21] = 0;
   out_1776845360940537275[22] = 1;
   out_1776845360940537275[23] = 0;
   out_1776845360940537275[24] = 0;
   out_1776845360940537275[25] = 0;
   out_1776845360940537275[26] = 0;
   out_1776845360940537275[27] = 0;
   out_1776845360940537275[28] = 0;
   out_1776845360940537275[29] = 0;
   out_1776845360940537275[30] = 0;
   out_1776845360940537275[31] = 0;
   out_1776845360940537275[32] = 0;
   out_1776845360940537275[33] = 0;
   out_1776845360940537275[34] = 0;
   out_1776845360940537275[35] = 0;
   out_1776845360940537275[36] = 0;
   out_1776845360940537275[37] = 0;
   out_1776845360940537275[38] = 0;
   out_1776845360940537275[39] = 0;
   out_1776845360940537275[40] = 0;
   out_1776845360940537275[41] = 1;
   out_1776845360940537275[42] = 0;
   out_1776845360940537275[43] = 0;
   out_1776845360940537275[44] = 0;
   out_1776845360940537275[45] = 0;
   out_1776845360940537275[46] = 0;
   out_1776845360940537275[47] = 0;
   out_1776845360940537275[48] = 0;
   out_1776845360940537275[49] = 0;
   out_1776845360940537275[50] = 0;
   out_1776845360940537275[51] = 0;
   out_1776845360940537275[52] = 0;
   out_1776845360940537275[53] = 0;
}
void h_14(double *state, double *unused, double *out_7652212324095214333) {
   out_7652212324095214333[0] = state[6];
   out_7652212324095214333[1] = state[7];
   out_7652212324095214333[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2527812391947689003) {
   out_2527812391947689003[0] = 0;
   out_2527812391947689003[1] = 0;
   out_2527812391947689003[2] = 0;
   out_2527812391947689003[3] = 0;
   out_2527812391947689003[4] = 0;
   out_2527812391947689003[5] = 0;
   out_2527812391947689003[6] = 1;
   out_2527812391947689003[7] = 0;
   out_2527812391947689003[8] = 0;
   out_2527812391947689003[9] = 0;
   out_2527812391947689003[10] = 0;
   out_2527812391947689003[11] = 0;
   out_2527812391947689003[12] = 0;
   out_2527812391947689003[13] = 0;
   out_2527812391947689003[14] = 0;
   out_2527812391947689003[15] = 0;
   out_2527812391947689003[16] = 0;
   out_2527812391947689003[17] = 0;
   out_2527812391947689003[18] = 0;
   out_2527812391947689003[19] = 0;
   out_2527812391947689003[20] = 0;
   out_2527812391947689003[21] = 0;
   out_2527812391947689003[22] = 0;
   out_2527812391947689003[23] = 0;
   out_2527812391947689003[24] = 0;
   out_2527812391947689003[25] = 1;
   out_2527812391947689003[26] = 0;
   out_2527812391947689003[27] = 0;
   out_2527812391947689003[28] = 0;
   out_2527812391947689003[29] = 0;
   out_2527812391947689003[30] = 0;
   out_2527812391947689003[31] = 0;
   out_2527812391947689003[32] = 0;
   out_2527812391947689003[33] = 0;
   out_2527812391947689003[34] = 0;
   out_2527812391947689003[35] = 0;
   out_2527812391947689003[36] = 0;
   out_2527812391947689003[37] = 0;
   out_2527812391947689003[38] = 0;
   out_2527812391947689003[39] = 0;
   out_2527812391947689003[40] = 0;
   out_2527812391947689003[41] = 0;
   out_2527812391947689003[42] = 0;
   out_2527812391947689003[43] = 0;
   out_2527812391947689003[44] = 1;
   out_2527812391947689003[45] = 0;
   out_2527812391947689003[46] = 0;
   out_2527812391947689003[47] = 0;
   out_2527812391947689003[48] = 0;
   out_2527812391947689003[49] = 0;
   out_2527812391947689003[50] = 0;
   out_2527812391947689003[51] = 0;
   out_2527812391947689003[52] = 0;
   out_2527812391947689003[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_1493079546624007114) {
  err_fun(nom_x, delta_x, out_1493079546624007114);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4580499654968994478) {
  inv_err_fun(nom_x, true_x, out_4580499654968994478);
}
void pose_H_mod_fun(double *state, double *out_8273119377234766952) {
  H_mod_fun(state, out_8273119377234766952);
}
void pose_f_fun(double *state, double dt, double *out_2742900412262200056) {
  f_fun(state,  dt, out_2742900412262200056);
}
void pose_F_fun(double *state, double dt, double *out_1250059419478269226) {
  F_fun(state,  dt, out_1250059419478269226);
}
void pose_h_4(double *state, double *unused, double *out_6706399028598537324) {
  h_4(state, unused, out_6706399028598537324);
}
void pose_H_4(double *state, double *unused, double *out_1435428464391795526) {
  H_4(state, unused, out_1435428464391795526);
}
void pose_h_10(double *state, double *unused, double *out_3193952299746834757) {
  h_10(state, unused, out_3193952299746834757);
}
void pose_H_10(double *state, double *unused, double *out_1464924797507750077) {
  H_10(state, unused, out_1464924797507750077);
}
void pose_h_13(double *state, double *unused, double *out_7802893222450228438) {
  h_13(state, unused, out_7802893222450228438);
}
void pose_H_13(double *state, double *unused, double *out_1776845360940537275) {
  H_13(state, unused, out_1776845360940537275);
}
void pose_h_14(double *state, double *unused, double *out_7652212324095214333) {
  h_14(state, unused, out_7652212324095214333);
}
void pose_H_14(double *state, double *unused, double *out_2527812391947689003) {
  H_14(state, unused, out_2527812391947689003);
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
