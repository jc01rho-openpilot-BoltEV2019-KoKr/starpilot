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
void err_fun(double *nom_x, double *delta_x, double *out_5522943408677507622) {
   out_5522943408677507622[0] = delta_x[0] + nom_x[0];
   out_5522943408677507622[1] = delta_x[1] + nom_x[1];
   out_5522943408677507622[2] = delta_x[2] + nom_x[2];
   out_5522943408677507622[3] = delta_x[3] + nom_x[3];
   out_5522943408677507622[4] = delta_x[4] + nom_x[4];
   out_5522943408677507622[5] = delta_x[5] + nom_x[5];
   out_5522943408677507622[6] = delta_x[6] + nom_x[6];
   out_5522943408677507622[7] = delta_x[7] + nom_x[7];
   out_5522943408677507622[8] = delta_x[8] + nom_x[8];
   out_5522943408677507622[9] = delta_x[9] + nom_x[9];
   out_5522943408677507622[10] = delta_x[10] + nom_x[10];
   out_5522943408677507622[11] = delta_x[11] + nom_x[11];
   out_5522943408677507622[12] = delta_x[12] + nom_x[12];
   out_5522943408677507622[13] = delta_x[13] + nom_x[13];
   out_5522943408677507622[14] = delta_x[14] + nom_x[14];
   out_5522943408677507622[15] = delta_x[15] + nom_x[15];
   out_5522943408677507622[16] = delta_x[16] + nom_x[16];
   out_5522943408677507622[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4295983432349839383) {
   out_4295983432349839383[0] = -nom_x[0] + true_x[0];
   out_4295983432349839383[1] = -nom_x[1] + true_x[1];
   out_4295983432349839383[2] = -nom_x[2] + true_x[2];
   out_4295983432349839383[3] = -nom_x[3] + true_x[3];
   out_4295983432349839383[4] = -nom_x[4] + true_x[4];
   out_4295983432349839383[5] = -nom_x[5] + true_x[5];
   out_4295983432349839383[6] = -nom_x[6] + true_x[6];
   out_4295983432349839383[7] = -nom_x[7] + true_x[7];
   out_4295983432349839383[8] = -nom_x[8] + true_x[8];
   out_4295983432349839383[9] = -nom_x[9] + true_x[9];
   out_4295983432349839383[10] = -nom_x[10] + true_x[10];
   out_4295983432349839383[11] = -nom_x[11] + true_x[11];
   out_4295983432349839383[12] = -nom_x[12] + true_x[12];
   out_4295983432349839383[13] = -nom_x[13] + true_x[13];
   out_4295983432349839383[14] = -nom_x[14] + true_x[14];
   out_4295983432349839383[15] = -nom_x[15] + true_x[15];
   out_4295983432349839383[16] = -nom_x[16] + true_x[16];
   out_4295983432349839383[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4346696932482416909) {
   out_4346696932482416909[0] = 1.0;
   out_4346696932482416909[1] = 0.0;
   out_4346696932482416909[2] = 0.0;
   out_4346696932482416909[3] = 0.0;
   out_4346696932482416909[4] = 0.0;
   out_4346696932482416909[5] = 0.0;
   out_4346696932482416909[6] = 0.0;
   out_4346696932482416909[7] = 0.0;
   out_4346696932482416909[8] = 0.0;
   out_4346696932482416909[9] = 0.0;
   out_4346696932482416909[10] = 0.0;
   out_4346696932482416909[11] = 0.0;
   out_4346696932482416909[12] = 0.0;
   out_4346696932482416909[13] = 0.0;
   out_4346696932482416909[14] = 0.0;
   out_4346696932482416909[15] = 0.0;
   out_4346696932482416909[16] = 0.0;
   out_4346696932482416909[17] = 0.0;
   out_4346696932482416909[18] = 0.0;
   out_4346696932482416909[19] = 1.0;
   out_4346696932482416909[20] = 0.0;
   out_4346696932482416909[21] = 0.0;
   out_4346696932482416909[22] = 0.0;
   out_4346696932482416909[23] = 0.0;
   out_4346696932482416909[24] = 0.0;
   out_4346696932482416909[25] = 0.0;
   out_4346696932482416909[26] = 0.0;
   out_4346696932482416909[27] = 0.0;
   out_4346696932482416909[28] = 0.0;
   out_4346696932482416909[29] = 0.0;
   out_4346696932482416909[30] = 0.0;
   out_4346696932482416909[31] = 0.0;
   out_4346696932482416909[32] = 0.0;
   out_4346696932482416909[33] = 0.0;
   out_4346696932482416909[34] = 0.0;
   out_4346696932482416909[35] = 0.0;
   out_4346696932482416909[36] = 0.0;
   out_4346696932482416909[37] = 0.0;
   out_4346696932482416909[38] = 1.0;
   out_4346696932482416909[39] = 0.0;
   out_4346696932482416909[40] = 0.0;
   out_4346696932482416909[41] = 0.0;
   out_4346696932482416909[42] = 0.0;
   out_4346696932482416909[43] = 0.0;
   out_4346696932482416909[44] = 0.0;
   out_4346696932482416909[45] = 0.0;
   out_4346696932482416909[46] = 0.0;
   out_4346696932482416909[47] = 0.0;
   out_4346696932482416909[48] = 0.0;
   out_4346696932482416909[49] = 0.0;
   out_4346696932482416909[50] = 0.0;
   out_4346696932482416909[51] = 0.0;
   out_4346696932482416909[52] = 0.0;
   out_4346696932482416909[53] = 0.0;
   out_4346696932482416909[54] = 0.0;
   out_4346696932482416909[55] = 0.0;
   out_4346696932482416909[56] = 0.0;
   out_4346696932482416909[57] = 1.0;
   out_4346696932482416909[58] = 0.0;
   out_4346696932482416909[59] = 0.0;
   out_4346696932482416909[60] = 0.0;
   out_4346696932482416909[61] = 0.0;
   out_4346696932482416909[62] = 0.0;
   out_4346696932482416909[63] = 0.0;
   out_4346696932482416909[64] = 0.0;
   out_4346696932482416909[65] = 0.0;
   out_4346696932482416909[66] = 0.0;
   out_4346696932482416909[67] = 0.0;
   out_4346696932482416909[68] = 0.0;
   out_4346696932482416909[69] = 0.0;
   out_4346696932482416909[70] = 0.0;
   out_4346696932482416909[71] = 0.0;
   out_4346696932482416909[72] = 0.0;
   out_4346696932482416909[73] = 0.0;
   out_4346696932482416909[74] = 0.0;
   out_4346696932482416909[75] = 0.0;
   out_4346696932482416909[76] = 1.0;
   out_4346696932482416909[77] = 0.0;
   out_4346696932482416909[78] = 0.0;
   out_4346696932482416909[79] = 0.0;
   out_4346696932482416909[80] = 0.0;
   out_4346696932482416909[81] = 0.0;
   out_4346696932482416909[82] = 0.0;
   out_4346696932482416909[83] = 0.0;
   out_4346696932482416909[84] = 0.0;
   out_4346696932482416909[85] = 0.0;
   out_4346696932482416909[86] = 0.0;
   out_4346696932482416909[87] = 0.0;
   out_4346696932482416909[88] = 0.0;
   out_4346696932482416909[89] = 0.0;
   out_4346696932482416909[90] = 0.0;
   out_4346696932482416909[91] = 0.0;
   out_4346696932482416909[92] = 0.0;
   out_4346696932482416909[93] = 0.0;
   out_4346696932482416909[94] = 0.0;
   out_4346696932482416909[95] = 1.0;
   out_4346696932482416909[96] = 0.0;
   out_4346696932482416909[97] = 0.0;
   out_4346696932482416909[98] = 0.0;
   out_4346696932482416909[99] = 0.0;
   out_4346696932482416909[100] = 0.0;
   out_4346696932482416909[101] = 0.0;
   out_4346696932482416909[102] = 0.0;
   out_4346696932482416909[103] = 0.0;
   out_4346696932482416909[104] = 0.0;
   out_4346696932482416909[105] = 0.0;
   out_4346696932482416909[106] = 0.0;
   out_4346696932482416909[107] = 0.0;
   out_4346696932482416909[108] = 0.0;
   out_4346696932482416909[109] = 0.0;
   out_4346696932482416909[110] = 0.0;
   out_4346696932482416909[111] = 0.0;
   out_4346696932482416909[112] = 0.0;
   out_4346696932482416909[113] = 0.0;
   out_4346696932482416909[114] = 1.0;
   out_4346696932482416909[115] = 0.0;
   out_4346696932482416909[116] = 0.0;
   out_4346696932482416909[117] = 0.0;
   out_4346696932482416909[118] = 0.0;
   out_4346696932482416909[119] = 0.0;
   out_4346696932482416909[120] = 0.0;
   out_4346696932482416909[121] = 0.0;
   out_4346696932482416909[122] = 0.0;
   out_4346696932482416909[123] = 0.0;
   out_4346696932482416909[124] = 0.0;
   out_4346696932482416909[125] = 0.0;
   out_4346696932482416909[126] = 0.0;
   out_4346696932482416909[127] = 0.0;
   out_4346696932482416909[128] = 0.0;
   out_4346696932482416909[129] = 0.0;
   out_4346696932482416909[130] = 0.0;
   out_4346696932482416909[131] = 0.0;
   out_4346696932482416909[132] = 0.0;
   out_4346696932482416909[133] = 1.0;
   out_4346696932482416909[134] = 0.0;
   out_4346696932482416909[135] = 0.0;
   out_4346696932482416909[136] = 0.0;
   out_4346696932482416909[137] = 0.0;
   out_4346696932482416909[138] = 0.0;
   out_4346696932482416909[139] = 0.0;
   out_4346696932482416909[140] = 0.0;
   out_4346696932482416909[141] = 0.0;
   out_4346696932482416909[142] = 0.0;
   out_4346696932482416909[143] = 0.0;
   out_4346696932482416909[144] = 0.0;
   out_4346696932482416909[145] = 0.0;
   out_4346696932482416909[146] = 0.0;
   out_4346696932482416909[147] = 0.0;
   out_4346696932482416909[148] = 0.0;
   out_4346696932482416909[149] = 0.0;
   out_4346696932482416909[150] = 0.0;
   out_4346696932482416909[151] = 0.0;
   out_4346696932482416909[152] = 1.0;
   out_4346696932482416909[153] = 0.0;
   out_4346696932482416909[154] = 0.0;
   out_4346696932482416909[155] = 0.0;
   out_4346696932482416909[156] = 0.0;
   out_4346696932482416909[157] = 0.0;
   out_4346696932482416909[158] = 0.0;
   out_4346696932482416909[159] = 0.0;
   out_4346696932482416909[160] = 0.0;
   out_4346696932482416909[161] = 0.0;
   out_4346696932482416909[162] = 0.0;
   out_4346696932482416909[163] = 0.0;
   out_4346696932482416909[164] = 0.0;
   out_4346696932482416909[165] = 0.0;
   out_4346696932482416909[166] = 0.0;
   out_4346696932482416909[167] = 0.0;
   out_4346696932482416909[168] = 0.0;
   out_4346696932482416909[169] = 0.0;
   out_4346696932482416909[170] = 0.0;
   out_4346696932482416909[171] = 1.0;
   out_4346696932482416909[172] = 0.0;
   out_4346696932482416909[173] = 0.0;
   out_4346696932482416909[174] = 0.0;
   out_4346696932482416909[175] = 0.0;
   out_4346696932482416909[176] = 0.0;
   out_4346696932482416909[177] = 0.0;
   out_4346696932482416909[178] = 0.0;
   out_4346696932482416909[179] = 0.0;
   out_4346696932482416909[180] = 0.0;
   out_4346696932482416909[181] = 0.0;
   out_4346696932482416909[182] = 0.0;
   out_4346696932482416909[183] = 0.0;
   out_4346696932482416909[184] = 0.0;
   out_4346696932482416909[185] = 0.0;
   out_4346696932482416909[186] = 0.0;
   out_4346696932482416909[187] = 0.0;
   out_4346696932482416909[188] = 0.0;
   out_4346696932482416909[189] = 0.0;
   out_4346696932482416909[190] = 1.0;
   out_4346696932482416909[191] = 0.0;
   out_4346696932482416909[192] = 0.0;
   out_4346696932482416909[193] = 0.0;
   out_4346696932482416909[194] = 0.0;
   out_4346696932482416909[195] = 0.0;
   out_4346696932482416909[196] = 0.0;
   out_4346696932482416909[197] = 0.0;
   out_4346696932482416909[198] = 0.0;
   out_4346696932482416909[199] = 0.0;
   out_4346696932482416909[200] = 0.0;
   out_4346696932482416909[201] = 0.0;
   out_4346696932482416909[202] = 0.0;
   out_4346696932482416909[203] = 0.0;
   out_4346696932482416909[204] = 0.0;
   out_4346696932482416909[205] = 0.0;
   out_4346696932482416909[206] = 0.0;
   out_4346696932482416909[207] = 0.0;
   out_4346696932482416909[208] = 0.0;
   out_4346696932482416909[209] = 1.0;
   out_4346696932482416909[210] = 0.0;
   out_4346696932482416909[211] = 0.0;
   out_4346696932482416909[212] = 0.0;
   out_4346696932482416909[213] = 0.0;
   out_4346696932482416909[214] = 0.0;
   out_4346696932482416909[215] = 0.0;
   out_4346696932482416909[216] = 0.0;
   out_4346696932482416909[217] = 0.0;
   out_4346696932482416909[218] = 0.0;
   out_4346696932482416909[219] = 0.0;
   out_4346696932482416909[220] = 0.0;
   out_4346696932482416909[221] = 0.0;
   out_4346696932482416909[222] = 0.0;
   out_4346696932482416909[223] = 0.0;
   out_4346696932482416909[224] = 0.0;
   out_4346696932482416909[225] = 0.0;
   out_4346696932482416909[226] = 0.0;
   out_4346696932482416909[227] = 0.0;
   out_4346696932482416909[228] = 1.0;
   out_4346696932482416909[229] = 0.0;
   out_4346696932482416909[230] = 0.0;
   out_4346696932482416909[231] = 0.0;
   out_4346696932482416909[232] = 0.0;
   out_4346696932482416909[233] = 0.0;
   out_4346696932482416909[234] = 0.0;
   out_4346696932482416909[235] = 0.0;
   out_4346696932482416909[236] = 0.0;
   out_4346696932482416909[237] = 0.0;
   out_4346696932482416909[238] = 0.0;
   out_4346696932482416909[239] = 0.0;
   out_4346696932482416909[240] = 0.0;
   out_4346696932482416909[241] = 0.0;
   out_4346696932482416909[242] = 0.0;
   out_4346696932482416909[243] = 0.0;
   out_4346696932482416909[244] = 0.0;
   out_4346696932482416909[245] = 0.0;
   out_4346696932482416909[246] = 0.0;
   out_4346696932482416909[247] = 1.0;
   out_4346696932482416909[248] = 0.0;
   out_4346696932482416909[249] = 0.0;
   out_4346696932482416909[250] = 0.0;
   out_4346696932482416909[251] = 0.0;
   out_4346696932482416909[252] = 0.0;
   out_4346696932482416909[253] = 0.0;
   out_4346696932482416909[254] = 0.0;
   out_4346696932482416909[255] = 0.0;
   out_4346696932482416909[256] = 0.0;
   out_4346696932482416909[257] = 0.0;
   out_4346696932482416909[258] = 0.0;
   out_4346696932482416909[259] = 0.0;
   out_4346696932482416909[260] = 0.0;
   out_4346696932482416909[261] = 0.0;
   out_4346696932482416909[262] = 0.0;
   out_4346696932482416909[263] = 0.0;
   out_4346696932482416909[264] = 0.0;
   out_4346696932482416909[265] = 0.0;
   out_4346696932482416909[266] = 1.0;
   out_4346696932482416909[267] = 0.0;
   out_4346696932482416909[268] = 0.0;
   out_4346696932482416909[269] = 0.0;
   out_4346696932482416909[270] = 0.0;
   out_4346696932482416909[271] = 0.0;
   out_4346696932482416909[272] = 0.0;
   out_4346696932482416909[273] = 0.0;
   out_4346696932482416909[274] = 0.0;
   out_4346696932482416909[275] = 0.0;
   out_4346696932482416909[276] = 0.0;
   out_4346696932482416909[277] = 0.0;
   out_4346696932482416909[278] = 0.0;
   out_4346696932482416909[279] = 0.0;
   out_4346696932482416909[280] = 0.0;
   out_4346696932482416909[281] = 0.0;
   out_4346696932482416909[282] = 0.0;
   out_4346696932482416909[283] = 0.0;
   out_4346696932482416909[284] = 0.0;
   out_4346696932482416909[285] = 1.0;
   out_4346696932482416909[286] = 0.0;
   out_4346696932482416909[287] = 0.0;
   out_4346696932482416909[288] = 0.0;
   out_4346696932482416909[289] = 0.0;
   out_4346696932482416909[290] = 0.0;
   out_4346696932482416909[291] = 0.0;
   out_4346696932482416909[292] = 0.0;
   out_4346696932482416909[293] = 0.0;
   out_4346696932482416909[294] = 0.0;
   out_4346696932482416909[295] = 0.0;
   out_4346696932482416909[296] = 0.0;
   out_4346696932482416909[297] = 0.0;
   out_4346696932482416909[298] = 0.0;
   out_4346696932482416909[299] = 0.0;
   out_4346696932482416909[300] = 0.0;
   out_4346696932482416909[301] = 0.0;
   out_4346696932482416909[302] = 0.0;
   out_4346696932482416909[303] = 0.0;
   out_4346696932482416909[304] = 1.0;
   out_4346696932482416909[305] = 0.0;
   out_4346696932482416909[306] = 0.0;
   out_4346696932482416909[307] = 0.0;
   out_4346696932482416909[308] = 0.0;
   out_4346696932482416909[309] = 0.0;
   out_4346696932482416909[310] = 0.0;
   out_4346696932482416909[311] = 0.0;
   out_4346696932482416909[312] = 0.0;
   out_4346696932482416909[313] = 0.0;
   out_4346696932482416909[314] = 0.0;
   out_4346696932482416909[315] = 0.0;
   out_4346696932482416909[316] = 0.0;
   out_4346696932482416909[317] = 0.0;
   out_4346696932482416909[318] = 0.0;
   out_4346696932482416909[319] = 0.0;
   out_4346696932482416909[320] = 0.0;
   out_4346696932482416909[321] = 0.0;
   out_4346696932482416909[322] = 0.0;
   out_4346696932482416909[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_6102158893978946471) {
   out_6102158893978946471[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_6102158893978946471[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_6102158893978946471[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_6102158893978946471[3] = dt*state[12] + state[3];
   out_6102158893978946471[4] = dt*state[13] + state[4];
   out_6102158893978946471[5] = dt*state[14] + state[5];
   out_6102158893978946471[6] = state[6];
   out_6102158893978946471[7] = state[7];
   out_6102158893978946471[8] = state[8];
   out_6102158893978946471[9] = state[9];
   out_6102158893978946471[10] = state[10];
   out_6102158893978946471[11] = state[11];
   out_6102158893978946471[12] = state[12];
   out_6102158893978946471[13] = state[13];
   out_6102158893978946471[14] = state[14];
   out_6102158893978946471[15] = state[15];
   out_6102158893978946471[16] = state[16];
   out_6102158893978946471[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2499898042682651457) {
   out_2499898042682651457[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2499898042682651457[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2499898042682651457[2] = 0;
   out_2499898042682651457[3] = 0;
   out_2499898042682651457[4] = 0;
   out_2499898042682651457[5] = 0;
   out_2499898042682651457[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2499898042682651457[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2499898042682651457[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2499898042682651457[9] = 0;
   out_2499898042682651457[10] = 0;
   out_2499898042682651457[11] = 0;
   out_2499898042682651457[12] = 0;
   out_2499898042682651457[13] = 0;
   out_2499898042682651457[14] = 0;
   out_2499898042682651457[15] = 0;
   out_2499898042682651457[16] = 0;
   out_2499898042682651457[17] = 0;
   out_2499898042682651457[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2499898042682651457[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2499898042682651457[20] = 0;
   out_2499898042682651457[21] = 0;
   out_2499898042682651457[22] = 0;
   out_2499898042682651457[23] = 0;
   out_2499898042682651457[24] = 0;
   out_2499898042682651457[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2499898042682651457[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2499898042682651457[27] = 0;
   out_2499898042682651457[28] = 0;
   out_2499898042682651457[29] = 0;
   out_2499898042682651457[30] = 0;
   out_2499898042682651457[31] = 0;
   out_2499898042682651457[32] = 0;
   out_2499898042682651457[33] = 0;
   out_2499898042682651457[34] = 0;
   out_2499898042682651457[35] = 0;
   out_2499898042682651457[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2499898042682651457[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2499898042682651457[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2499898042682651457[39] = 0;
   out_2499898042682651457[40] = 0;
   out_2499898042682651457[41] = 0;
   out_2499898042682651457[42] = 0;
   out_2499898042682651457[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2499898042682651457[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2499898042682651457[45] = 0;
   out_2499898042682651457[46] = 0;
   out_2499898042682651457[47] = 0;
   out_2499898042682651457[48] = 0;
   out_2499898042682651457[49] = 0;
   out_2499898042682651457[50] = 0;
   out_2499898042682651457[51] = 0;
   out_2499898042682651457[52] = 0;
   out_2499898042682651457[53] = 0;
   out_2499898042682651457[54] = 0;
   out_2499898042682651457[55] = 0;
   out_2499898042682651457[56] = 0;
   out_2499898042682651457[57] = 1;
   out_2499898042682651457[58] = 0;
   out_2499898042682651457[59] = 0;
   out_2499898042682651457[60] = 0;
   out_2499898042682651457[61] = 0;
   out_2499898042682651457[62] = 0;
   out_2499898042682651457[63] = 0;
   out_2499898042682651457[64] = 0;
   out_2499898042682651457[65] = 0;
   out_2499898042682651457[66] = dt;
   out_2499898042682651457[67] = 0;
   out_2499898042682651457[68] = 0;
   out_2499898042682651457[69] = 0;
   out_2499898042682651457[70] = 0;
   out_2499898042682651457[71] = 0;
   out_2499898042682651457[72] = 0;
   out_2499898042682651457[73] = 0;
   out_2499898042682651457[74] = 0;
   out_2499898042682651457[75] = 0;
   out_2499898042682651457[76] = 1;
   out_2499898042682651457[77] = 0;
   out_2499898042682651457[78] = 0;
   out_2499898042682651457[79] = 0;
   out_2499898042682651457[80] = 0;
   out_2499898042682651457[81] = 0;
   out_2499898042682651457[82] = 0;
   out_2499898042682651457[83] = 0;
   out_2499898042682651457[84] = 0;
   out_2499898042682651457[85] = dt;
   out_2499898042682651457[86] = 0;
   out_2499898042682651457[87] = 0;
   out_2499898042682651457[88] = 0;
   out_2499898042682651457[89] = 0;
   out_2499898042682651457[90] = 0;
   out_2499898042682651457[91] = 0;
   out_2499898042682651457[92] = 0;
   out_2499898042682651457[93] = 0;
   out_2499898042682651457[94] = 0;
   out_2499898042682651457[95] = 1;
   out_2499898042682651457[96] = 0;
   out_2499898042682651457[97] = 0;
   out_2499898042682651457[98] = 0;
   out_2499898042682651457[99] = 0;
   out_2499898042682651457[100] = 0;
   out_2499898042682651457[101] = 0;
   out_2499898042682651457[102] = 0;
   out_2499898042682651457[103] = 0;
   out_2499898042682651457[104] = dt;
   out_2499898042682651457[105] = 0;
   out_2499898042682651457[106] = 0;
   out_2499898042682651457[107] = 0;
   out_2499898042682651457[108] = 0;
   out_2499898042682651457[109] = 0;
   out_2499898042682651457[110] = 0;
   out_2499898042682651457[111] = 0;
   out_2499898042682651457[112] = 0;
   out_2499898042682651457[113] = 0;
   out_2499898042682651457[114] = 1;
   out_2499898042682651457[115] = 0;
   out_2499898042682651457[116] = 0;
   out_2499898042682651457[117] = 0;
   out_2499898042682651457[118] = 0;
   out_2499898042682651457[119] = 0;
   out_2499898042682651457[120] = 0;
   out_2499898042682651457[121] = 0;
   out_2499898042682651457[122] = 0;
   out_2499898042682651457[123] = 0;
   out_2499898042682651457[124] = 0;
   out_2499898042682651457[125] = 0;
   out_2499898042682651457[126] = 0;
   out_2499898042682651457[127] = 0;
   out_2499898042682651457[128] = 0;
   out_2499898042682651457[129] = 0;
   out_2499898042682651457[130] = 0;
   out_2499898042682651457[131] = 0;
   out_2499898042682651457[132] = 0;
   out_2499898042682651457[133] = 1;
   out_2499898042682651457[134] = 0;
   out_2499898042682651457[135] = 0;
   out_2499898042682651457[136] = 0;
   out_2499898042682651457[137] = 0;
   out_2499898042682651457[138] = 0;
   out_2499898042682651457[139] = 0;
   out_2499898042682651457[140] = 0;
   out_2499898042682651457[141] = 0;
   out_2499898042682651457[142] = 0;
   out_2499898042682651457[143] = 0;
   out_2499898042682651457[144] = 0;
   out_2499898042682651457[145] = 0;
   out_2499898042682651457[146] = 0;
   out_2499898042682651457[147] = 0;
   out_2499898042682651457[148] = 0;
   out_2499898042682651457[149] = 0;
   out_2499898042682651457[150] = 0;
   out_2499898042682651457[151] = 0;
   out_2499898042682651457[152] = 1;
   out_2499898042682651457[153] = 0;
   out_2499898042682651457[154] = 0;
   out_2499898042682651457[155] = 0;
   out_2499898042682651457[156] = 0;
   out_2499898042682651457[157] = 0;
   out_2499898042682651457[158] = 0;
   out_2499898042682651457[159] = 0;
   out_2499898042682651457[160] = 0;
   out_2499898042682651457[161] = 0;
   out_2499898042682651457[162] = 0;
   out_2499898042682651457[163] = 0;
   out_2499898042682651457[164] = 0;
   out_2499898042682651457[165] = 0;
   out_2499898042682651457[166] = 0;
   out_2499898042682651457[167] = 0;
   out_2499898042682651457[168] = 0;
   out_2499898042682651457[169] = 0;
   out_2499898042682651457[170] = 0;
   out_2499898042682651457[171] = 1;
   out_2499898042682651457[172] = 0;
   out_2499898042682651457[173] = 0;
   out_2499898042682651457[174] = 0;
   out_2499898042682651457[175] = 0;
   out_2499898042682651457[176] = 0;
   out_2499898042682651457[177] = 0;
   out_2499898042682651457[178] = 0;
   out_2499898042682651457[179] = 0;
   out_2499898042682651457[180] = 0;
   out_2499898042682651457[181] = 0;
   out_2499898042682651457[182] = 0;
   out_2499898042682651457[183] = 0;
   out_2499898042682651457[184] = 0;
   out_2499898042682651457[185] = 0;
   out_2499898042682651457[186] = 0;
   out_2499898042682651457[187] = 0;
   out_2499898042682651457[188] = 0;
   out_2499898042682651457[189] = 0;
   out_2499898042682651457[190] = 1;
   out_2499898042682651457[191] = 0;
   out_2499898042682651457[192] = 0;
   out_2499898042682651457[193] = 0;
   out_2499898042682651457[194] = 0;
   out_2499898042682651457[195] = 0;
   out_2499898042682651457[196] = 0;
   out_2499898042682651457[197] = 0;
   out_2499898042682651457[198] = 0;
   out_2499898042682651457[199] = 0;
   out_2499898042682651457[200] = 0;
   out_2499898042682651457[201] = 0;
   out_2499898042682651457[202] = 0;
   out_2499898042682651457[203] = 0;
   out_2499898042682651457[204] = 0;
   out_2499898042682651457[205] = 0;
   out_2499898042682651457[206] = 0;
   out_2499898042682651457[207] = 0;
   out_2499898042682651457[208] = 0;
   out_2499898042682651457[209] = 1;
   out_2499898042682651457[210] = 0;
   out_2499898042682651457[211] = 0;
   out_2499898042682651457[212] = 0;
   out_2499898042682651457[213] = 0;
   out_2499898042682651457[214] = 0;
   out_2499898042682651457[215] = 0;
   out_2499898042682651457[216] = 0;
   out_2499898042682651457[217] = 0;
   out_2499898042682651457[218] = 0;
   out_2499898042682651457[219] = 0;
   out_2499898042682651457[220] = 0;
   out_2499898042682651457[221] = 0;
   out_2499898042682651457[222] = 0;
   out_2499898042682651457[223] = 0;
   out_2499898042682651457[224] = 0;
   out_2499898042682651457[225] = 0;
   out_2499898042682651457[226] = 0;
   out_2499898042682651457[227] = 0;
   out_2499898042682651457[228] = 1;
   out_2499898042682651457[229] = 0;
   out_2499898042682651457[230] = 0;
   out_2499898042682651457[231] = 0;
   out_2499898042682651457[232] = 0;
   out_2499898042682651457[233] = 0;
   out_2499898042682651457[234] = 0;
   out_2499898042682651457[235] = 0;
   out_2499898042682651457[236] = 0;
   out_2499898042682651457[237] = 0;
   out_2499898042682651457[238] = 0;
   out_2499898042682651457[239] = 0;
   out_2499898042682651457[240] = 0;
   out_2499898042682651457[241] = 0;
   out_2499898042682651457[242] = 0;
   out_2499898042682651457[243] = 0;
   out_2499898042682651457[244] = 0;
   out_2499898042682651457[245] = 0;
   out_2499898042682651457[246] = 0;
   out_2499898042682651457[247] = 1;
   out_2499898042682651457[248] = 0;
   out_2499898042682651457[249] = 0;
   out_2499898042682651457[250] = 0;
   out_2499898042682651457[251] = 0;
   out_2499898042682651457[252] = 0;
   out_2499898042682651457[253] = 0;
   out_2499898042682651457[254] = 0;
   out_2499898042682651457[255] = 0;
   out_2499898042682651457[256] = 0;
   out_2499898042682651457[257] = 0;
   out_2499898042682651457[258] = 0;
   out_2499898042682651457[259] = 0;
   out_2499898042682651457[260] = 0;
   out_2499898042682651457[261] = 0;
   out_2499898042682651457[262] = 0;
   out_2499898042682651457[263] = 0;
   out_2499898042682651457[264] = 0;
   out_2499898042682651457[265] = 0;
   out_2499898042682651457[266] = 1;
   out_2499898042682651457[267] = 0;
   out_2499898042682651457[268] = 0;
   out_2499898042682651457[269] = 0;
   out_2499898042682651457[270] = 0;
   out_2499898042682651457[271] = 0;
   out_2499898042682651457[272] = 0;
   out_2499898042682651457[273] = 0;
   out_2499898042682651457[274] = 0;
   out_2499898042682651457[275] = 0;
   out_2499898042682651457[276] = 0;
   out_2499898042682651457[277] = 0;
   out_2499898042682651457[278] = 0;
   out_2499898042682651457[279] = 0;
   out_2499898042682651457[280] = 0;
   out_2499898042682651457[281] = 0;
   out_2499898042682651457[282] = 0;
   out_2499898042682651457[283] = 0;
   out_2499898042682651457[284] = 0;
   out_2499898042682651457[285] = 1;
   out_2499898042682651457[286] = 0;
   out_2499898042682651457[287] = 0;
   out_2499898042682651457[288] = 0;
   out_2499898042682651457[289] = 0;
   out_2499898042682651457[290] = 0;
   out_2499898042682651457[291] = 0;
   out_2499898042682651457[292] = 0;
   out_2499898042682651457[293] = 0;
   out_2499898042682651457[294] = 0;
   out_2499898042682651457[295] = 0;
   out_2499898042682651457[296] = 0;
   out_2499898042682651457[297] = 0;
   out_2499898042682651457[298] = 0;
   out_2499898042682651457[299] = 0;
   out_2499898042682651457[300] = 0;
   out_2499898042682651457[301] = 0;
   out_2499898042682651457[302] = 0;
   out_2499898042682651457[303] = 0;
   out_2499898042682651457[304] = 1;
   out_2499898042682651457[305] = 0;
   out_2499898042682651457[306] = 0;
   out_2499898042682651457[307] = 0;
   out_2499898042682651457[308] = 0;
   out_2499898042682651457[309] = 0;
   out_2499898042682651457[310] = 0;
   out_2499898042682651457[311] = 0;
   out_2499898042682651457[312] = 0;
   out_2499898042682651457[313] = 0;
   out_2499898042682651457[314] = 0;
   out_2499898042682651457[315] = 0;
   out_2499898042682651457[316] = 0;
   out_2499898042682651457[317] = 0;
   out_2499898042682651457[318] = 0;
   out_2499898042682651457[319] = 0;
   out_2499898042682651457[320] = 0;
   out_2499898042682651457[321] = 0;
   out_2499898042682651457[322] = 0;
   out_2499898042682651457[323] = 1;
}
void h_4(double *state, double *unused, double *out_3279047988568344132) {
   out_3279047988568344132[0] = state[6] + state[9];
   out_3279047988568344132[1] = state[7] + state[10];
   out_3279047988568344132[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_5899742257253909940) {
   out_5899742257253909940[0] = 0;
   out_5899742257253909940[1] = 0;
   out_5899742257253909940[2] = 0;
   out_5899742257253909940[3] = 0;
   out_5899742257253909940[4] = 0;
   out_5899742257253909940[5] = 0;
   out_5899742257253909940[6] = 1;
   out_5899742257253909940[7] = 0;
   out_5899742257253909940[8] = 0;
   out_5899742257253909940[9] = 1;
   out_5899742257253909940[10] = 0;
   out_5899742257253909940[11] = 0;
   out_5899742257253909940[12] = 0;
   out_5899742257253909940[13] = 0;
   out_5899742257253909940[14] = 0;
   out_5899742257253909940[15] = 0;
   out_5899742257253909940[16] = 0;
   out_5899742257253909940[17] = 0;
   out_5899742257253909940[18] = 0;
   out_5899742257253909940[19] = 0;
   out_5899742257253909940[20] = 0;
   out_5899742257253909940[21] = 0;
   out_5899742257253909940[22] = 0;
   out_5899742257253909940[23] = 0;
   out_5899742257253909940[24] = 0;
   out_5899742257253909940[25] = 1;
   out_5899742257253909940[26] = 0;
   out_5899742257253909940[27] = 0;
   out_5899742257253909940[28] = 1;
   out_5899742257253909940[29] = 0;
   out_5899742257253909940[30] = 0;
   out_5899742257253909940[31] = 0;
   out_5899742257253909940[32] = 0;
   out_5899742257253909940[33] = 0;
   out_5899742257253909940[34] = 0;
   out_5899742257253909940[35] = 0;
   out_5899742257253909940[36] = 0;
   out_5899742257253909940[37] = 0;
   out_5899742257253909940[38] = 0;
   out_5899742257253909940[39] = 0;
   out_5899742257253909940[40] = 0;
   out_5899742257253909940[41] = 0;
   out_5899742257253909940[42] = 0;
   out_5899742257253909940[43] = 0;
   out_5899742257253909940[44] = 1;
   out_5899742257253909940[45] = 0;
   out_5899742257253909940[46] = 0;
   out_5899742257253909940[47] = 1;
   out_5899742257253909940[48] = 0;
   out_5899742257253909940[49] = 0;
   out_5899742257253909940[50] = 0;
   out_5899742257253909940[51] = 0;
   out_5899742257253909940[52] = 0;
   out_5899742257253909940[53] = 0;
}
void h_10(double *state, double *unused, double *out_9007933995216703840) {
   out_9007933995216703840[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_9007933995216703840[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_9007933995216703840[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2326992144684427807) {
   out_2326992144684427807[0] = 0;
   out_2326992144684427807[1] = 9.8100000000000005*cos(state[1]);
   out_2326992144684427807[2] = 0;
   out_2326992144684427807[3] = 0;
   out_2326992144684427807[4] = -state[8];
   out_2326992144684427807[5] = state[7];
   out_2326992144684427807[6] = 0;
   out_2326992144684427807[7] = state[5];
   out_2326992144684427807[8] = -state[4];
   out_2326992144684427807[9] = 0;
   out_2326992144684427807[10] = 0;
   out_2326992144684427807[11] = 0;
   out_2326992144684427807[12] = 1;
   out_2326992144684427807[13] = 0;
   out_2326992144684427807[14] = 0;
   out_2326992144684427807[15] = 1;
   out_2326992144684427807[16] = 0;
   out_2326992144684427807[17] = 0;
   out_2326992144684427807[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2326992144684427807[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2326992144684427807[20] = 0;
   out_2326992144684427807[21] = state[8];
   out_2326992144684427807[22] = 0;
   out_2326992144684427807[23] = -state[6];
   out_2326992144684427807[24] = -state[5];
   out_2326992144684427807[25] = 0;
   out_2326992144684427807[26] = state[3];
   out_2326992144684427807[27] = 0;
   out_2326992144684427807[28] = 0;
   out_2326992144684427807[29] = 0;
   out_2326992144684427807[30] = 0;
   out_2326992144684427807[31] = 1;
   out_2326992144684427807[32] = 0;
   out_2326992144684427807[33] = 0;
   out_2326992144684427807[34] = 1;
   out_2326992144684427807[35] = 0;
   out_2326992144684427807[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2326992144684427807[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2326992144684427807[38] = 0;
   out_2326992144684427807[39] = -state[7];
   out_2326992144684427807[40] = state[6];
   out_2326992144684427807[41] = 0;
   out_2326992144684427807[42] = state[4];
   out_2326992144684427807[43] = -state[3];
   out_2326992144684427807[44] = 0;
   out_2326992144684427807[45] = 0;
   out_2326992144684427807[46] = 0;
   out_2326992144684427807[47] = 0;
   out_2326992144684427807[48] = 0;
   out_2326992144684427807[49] = 0;
   out_2326992144684427807[50] = 1;
   out_2326992144684427807[51] = 0;
   out_2326992144684427807[52] = 0;
   out_2326992144684427807[53] = 1;
}
void h_13(double *state, double *unused, double *out_8858214994014047499) {
   out_8858214994014047499[0] = state[3];
   out_8858214994014047499[1] = state[4];
   out_8858214994014047499[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1710888951062790989) {
   out_1710888951062790989[0] = 0;
   out_1710888951062790989[1] = 0;
   out_1710888951062790989[2] = 0;
   out_1710888951062790989[3] = 1;
   out_1710888951062790989[4] = 0;
   out_1710888951062790989[5] = 0;
   out_1710888951062790989[6] = 0;
   out_1710888951062790989[7] = 0;
   out_1710888951062790989[8] = 0;
   out_1710888951062790989[9] = 0;
   out_1710888951062790989[10] = 0;
   out_1710888951062790989[11] = 0;
   out_1710888951062790989[12] = 0;
   out_1710888951062790989[13] = 0;
   out_1710888951062790989[14] = 0;
   out_1710888951062790989[15] = 0;
   out_1710888951062790989[16] = 0;
   out_1710888951062790989[17] = 0;
   out_1710888951062790989[18] = 0;
   out_1710888951062790989[19] = 0;
   out_1710888951062790989[20] = 0;
   out_1710888951062790989[21] = 0;
   out_1710888951062790989[22] = 1;
   out_1710888951062790989[23] = 0;
   out_1710888951062790989[24] = 0;
   out_1710888951062790989[25] = 0;
   out_1710888951062790989[26] = 0;
   out_1710888951062790989[27] = 0;
   out_1710888951062790989[28] = 0;
   out_1710888951062790989[29] = 0;
   out_1710888951062790989[30] = 0;
   out_1710888951062790989[31] = 0;
   out_1710888951062790989[32] = 0;
   out_1710888951062790989[33] = 0;
   out_1710888951062790989[34] = 0;
   out_1710888951062790989[35] = 0;
   out_1710888951062790989[36] = 0;
   out_1710888951062790989[37] = 0;
   out_1710888951062790989[38] = 0;
   out_1710888951062790989[39] = 0;
   out_1710888951062790989[40] = 0;
   out_1710888951062790989[41] = 1;
   out_1710888951062790989[42] = 0;
   out_1710888951062790989[43] = 0;
   out_1710888951062790989[44] = 0;
   out_1710888951062790989[45] = 0;
   out_1710888951062790989[46] = 0;
   out_1710888951062790989[47] = 0;
   out_1710888951062790989[48] = 0;
   out_1710888951062790989[49] = 0;
   out_1710888951062790989[50] = 0;
   out_1710888951062790989[51] = 0;
   out_1710888951062790989[52] = 0;
   out_1710888951062790989[53] = 0;
}
void h_14(double *state, double *unused, double *out_7751194400543680936) {
   out_7751194400543680936[0] = state[6];
   out_7751194400543680936[1] = state[7];
   out_7751194400543680936[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1936501400914425411) {
   out_1936501400914425411[0] = 0;
   out_1936501400914425411[1] = 0;
   out_1936501400914425411[2] = 0;
   out_1936501400914425411[3] = 0;
   out_1936501400914425411[4] = 0;
   out_1936501400914425411[5] = 0;
   out_1936501400914425411[6] = 1;
   out_1936501400914425411[7] = 0;
   out_1936501400914425411[8] = 0;
   out_1936501400914425411[9] = 0;
   out_1936501400914425411[10] = 0;
   out_1936501400914425411[11] = 0;
   out_1936501400914425411[12] = 0;
   out_1936501400914425411[13] = 0;
   out_1936501400914425411[14] = 0;
   out_1936501400914425411[15] = 0;
   out_1936501400914425411[16] = 0;
   out_1936501400914425411[17] = 0;
   out_1936501400914425411[18] = 0;
   out_1936501400914425411[19] = 0;
   out_1936501400914425411[20] = 0;
   out_1936501400914425411[21] = 0;
   out_1936501400914425411[22] = 0;
   out_1936501400914425411[23] = 0;
   out_1936501400914425411[24] = 0;
   out_1936501400914425411[25] = 1;
   out_1936501400914425411[26] = 0;
   out_1936501400914425411[27] = 0;
   out_1936501400914425411[28] = 0;
   out_1936501400914425411[29] = 0;
   out_1936501400914425411[30] = 0;
   out_1936501400914425411[31] = 0;
   out_1936501400914425411[32] = 0;
   out_1936501400914425411[33] = 0;
   out_1936501400914425411[34] = 0;
   out_1936501400914425411[35] = 0;
   out_1936501400914425411[36] = 0;
   out_1936501400914425411[37] = 0;
   out_1936501400914425411[38] = 0;
   out_1936501400914425411[39] = 0;
   out_1936501400914425411[40] = 0;
   out_1936501400914425411[41] = 0;
   out_1936501400914425411[42] = 0;
   out_1936501400914425411[43] = 0;
   out_1936501400914425411[44] = 1;
   out_1936501400914425411[45] = 0;
   out_1936501400914425411[46] = 0;
   out_1936501400914425411[47] = 0;
   out_1936501400914425411[48] = 0;
   out_1936501400914425411[49] = 0;
   out_1936501400914425411[50] = 0;
   out_1936501400914425411[51] = 0;
   out_1936501400914425411[52] = 0;
   out_1936501400914425411[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5522943408677507622) {
  err_fun(nom_x, delta_x, out_5522943408677507622);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4295983432349839383) {
  inv_err_fun(nom_x, true_x, out_4295983432349839383);
}
void pose_H_mod_fun(double *state, double *out_4346696932482416909) {
  H_mod_fun(state, out_4346696932482416909);
}
void pose_f_fun(double *state, double dt, double *out_6102158893978946471) {
  f_fun(state,  dt, out_6102158893978946471);
}
void pose_F_fun(double *state, double dt, double *out_2499898042682651457) {
  F_fun(state,  dt, out_2499898042682651457);
}
void pose_h_4(double *state, double *unused, double *out_3279047988568344132) {
  h_4(state, unused, out_3279047988568344132);
}
void pose_H_4(double *state, double *unused, double *out_5899742257253909940) {
  H_4(state, unused, out_5899742257253909940);
}
void pose_h_10(double *state, double *unused, double *out_9007933995216703840) {
  h_10(state, unused, out_9007933995216703840);
}
void pose_H_10(double *state, double *unused, double *out_2326992144684427807) {
  H_10(state, unused, out_2326992144684427807);
}
void pose_h_13(double *state, double *unused, double *out_8858214994014047499) {
  h_13(state, unused, out_8858214994014047499);
}
void pose_H_13(double *state, double *unused, double *out_1710888951062790989) {
  H_13(state, unused, out_1710888951062790989);
}
void pose_h_14(double *state, double *unused, double *out_7751194400543680936) {
  h_14(state, unused, out_7751194400543680936);
}
void pose_H_14(double *state, double *unused, double *out_1936501400914425411) {
  H_14(state, unused, out_1936501400914425411);
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
