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
void err_fun(double *nom_x, double *delta_x, double *out_8123935570106658818) {
   out_8123935570106658818[0] = delta_x[0] + nom_x[0];
   out_8123935570106658818[1] = delta_x[1] + nom_x[1];
   out_8123935570106658818[2] = delta_x[2] + nom_x[2];
   out_8123935570106658818[3] = delta_x[3] + nom_x[3];
   out_8123935570106658818[4] = delta_x[4] + nom_x[4];
   out_8123935570106658818[5] = delta_x[5] + nom_x[5];
   out_8123935570106658818[6] = delta_x[6] + nom_x[6];
   out_8123935570106658818[7] = delta_x[7] + nom_x[7];
   out_8123935570106658818[8] = delta_x[8] + nom_x[8];
   out_8123935570106658818[9] = delta_x[9] + nom_x[9];
   out_8123935570106658818[10] = delta_x[10] + nom_x[10];
   out_8123935570106658818[11] = delta_x[11] + nom_x[11];
   out_8123935570106658818[12] = delta_x[12] + nom_x[12];
   out_8123935570106658818[13] = delta_x[13] + nom_x[13];
   out_8123935570106658818[14] = delta_x[14] + nom_x[14];
   out_8123935570106658818[15] = delta_x[15] + nom_x[15];
   out_8123935570106658818[16] = delta_x[16] + nom_x[16];
   out_8123935570106658818[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7916605304970807670) {
   out_7916605304970807670[0] = -nom_x[0] + true_x[0];
   out_7916605304970807670[1] = -nom_x[1] + true_x[1];
   out_7916605304970807670[2] = -nom_x[2] + true_x[2];
   out_7916605304970807670[3] = -nom_x[3] + true_x[3];
   out_7916605304970807670[4] = -nom_x[4] + true_x[4];
   out_7916605304970807670[5] = -nom_x[5] + true_x[5];
   out_7916605304970807670[6] = -nom_x[6] + true_x[6];
   out_7916605304970807670[7] = -nom_x[7] + true_x[7];
   out_7916605304970807670[8] = -nom_x[8] + true_x[8];
   out_7916605304970807670[9] = -nom_x[9] + true_x[9];
   out_7916605304970807670[10] = -nom_x[10] + true_x[10];
   out_7916605304970807670[11] = -nom_x[11] + true_x[11];
   out_7916605304970807670[12] = -nom_x[12] + true_x[12];
   out_7916605304970807670[13] = -nom_x[13] + true_x[13];
   out_7916605304970807670[14] = -nom_x[14] + true_x[14];
   out_7916605304970807670[15] = -nom_x[15] + true_x[15];
   out_7916605304970807670[16] = -nom_x[16] + true_x[16];
   out_7916605304970807670[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_1602815725505969341) {
   out_1602815725505969341[0] = 1.0;
   out_1602815725505969341[1] = 0.0;
   out_1602815725505969341[2] = 0.0;
   out_1602815725505969341[3] = 0.0;
   out_1602815725505969341[4] = 0.0;
   out_1602815725505969341[5] = 0.0;
   out_1602815725505969341[6] = 0.0;
   out_1602815725505969341[7] = 0.0;
   out_1602815725505969341[8] = 0.0;
   out_1602815725505969341[9] = 0.0;
   out_1602815725505969341[10] = 0.0;
   out_1602815725505969341[11] = 0.0;
   out_1602815725505969341[12] = 0.0;
   out_1602815725505969341[13] = 0.0;
   out_1602815725505969341[14] = 0.0;
   out_1602815725505969341[15] = 0.0;
   out_1602815725505969341[16] = 0.0;
   out_1602815725505969341[17] = 0.0;
   out_1602815725505969341[18] = 0.0;
   out_1602815725505969341[19] = 1.0;
   out_1602815725505969341[20] = 0.0;
   out_1602815725505969341[21] = 0.0;
   out_1602815725505969341[22] = 0.0;
   out_1602815725505969341[23] = 0.0;
   out_1602815725505969341[24] = 0.0;
   out_1602815725505969341[25] = 0.0;
   out_1602815725505969341[26] = 0.0;
   out_1602815725505969341[27] = 0.0;
   out_1602815725505969341[28] = 0.0;
   out_1602815725505969341[29] = 0.0;
   out_1602815725505969341[30] = 0.0;
   out_1602815725505969341[31] = 0.0;
   out_1602815725505969341[32] = 0.0;
   out_1602815725505969341[33] = 0.0;
   out_1602815725505969341[34] = 0.0;
   out_1602815725505969341[35] = 0.0;
   out_1602815725505969341[36] = 0.0;
   out_1602815725505969341[37] = 0.0;
   out_1602815725505969341[38] = 1.0;
   out_1602815725505969341[39] = 0.0;
   out_1602815725505969341[40] = 0.0;
   out_1602815725505969341[41] = 0.0;
   out_1602815725505969341[42] = 0.0;
   out_1602815725505969341[43] = 0.0;
   out_1602815725505969341[44] = 0.0;
   out_1602815725505969341[45] = 0.0;
   out_1602815725505969341[46] = 0.0;
   out_1602815725505969341[47] = 0.0;
   out_1602815725505969341[48] = 0.0;
   out_1602815725505969341[49] = 0.0;
   out_1602815725505969341[50] = 0.0;
   out_1602815725505969341[51] = 0.0;
   out_1602815725505969341[52] = 0.0;
   out_1602815725505969341[53] = 0.0;
   out_1602815725505969341[54] = 0.0;
   out_1602815725505969341[55] = 0.0;
   out_1602815725505969341[56] = 0.0;
   out_1602815725505969341[57] = 1.0;
   out_1602815725505969341[58] = 0.0;
   out_1602815725505969341[59] = 0.0;
   out_1602815725505969341[60] = 0.0;
   out_1602815725505969341[61] = 0.0;
   out_1602815725505969341[62] = 0.0;
   out_1602815725505969341[63] = 0.0;
   out_1602815725505969341[64] = 0.0;
   out_1602815725505969341[65] = 0.0;
   out_1602815725505969341[66] = 0.0;
   out_1602815725505969341[67] = 0.0;
   out_1602815725505969341[68] = 0.0;
   out_1602815725505969341[69] = 0.0;
   out_1602815725505969341[70] = 0.0;
   out_1602815725505969341[71] = 0.0;
   out_1602815725505969341[72] = 0.0;
   out_1602815725505969341[73] = 0.0;
   out_1602815725505969341[74] = 0.0;
   out_1602815725505969341[75] = 0.0;
   out_1602815725505969341[76] = 1.0;
   out_1602815725505969341[77] = 0.0;
   out_1602815725505969341[78] = 0.0;
   out_1602815725505969341[79] = 0.0;
   out_1602815725505969341[80] = 0.0;
   out_1602815725505969341[81] = 0.0;
   out_1602815725505969341[82] = 0.0;
   out_1602815725505969341[83] = 0.0;
   out_1602815725505969341[84] = 0.0;
   out_1602815725505969341[85] = 0.0;
   out_1602815725505969341[86] = 0.0;
   out_1602815725505969341[87] = 0.0;
   out_1602815725505969341[88] = 0.0;
   out_1602815725505969341[89] = 0.0;
   out_1602815725505969341[90] = 0.0;
   out_1602815725505969341[91] = 0.0;
   out_1602815725505969341[92] = 0.0;
   out_1602815725505969341[93] = 0.0;
   out_1602815725505969341[94] = 0.0;
   out_1602815725505969341[95] = 1.0;
   out_1602815725505969341[96] = 0.0;
   out_1602815725505969341[97] = 0.0;
   out_1602815725505969341[98] = 0.0;
   out_1602815725505969341[99] = 0.0;
   out_1602815725505969341[100] = 0.0;
   out_1602815725505969341[101] = 0.0;
   out_1602815725505969341[102] = 0.0;
   out_1602815725505969341[103] = 0.0;
   out_1602815725505969341[104] = 0.0;
   out_1602815725505969341[105] = 0.0;
   out_1602815725505969341[106] = 0.0;
   out_1602815725505969341[107] = 0.0;
   out_1602815725505969341[108] = 0.0;
   out_1602815725505969341[109] = 0.0;
   out_1602815725505969341[110] = 0.0;
   out_1602815725505969341[111] = 0.0;
   out_1602815725505969341[112] = 0.0;
   out_1602815725505969341[113] = 0.0;
   out_1602815725505969341[114] = 1.0;
   out_1602815725505969341[115] = 0.0;
   out_1602815725505969341[116] = 0.0;
   out_1602815725505969341[117] = 0.0;
   out_1602815725505969341[118] = 0.0;
   out_1602815725505969341[119] = 0.0;
   out_1602815725505969341[120] = 0.0;
   out_1602815725505969341[121] = 0.0;
   out_1602815725505969341[122] = 0.0;
   out_1602815725505969341[123] = 0.0;
   out_1602815725505969341[124] = 0.0;
   out_1602815725505969341[125] = 0.0;
   out_1602815725505969341[126] = 0.0;
   out_1602815725505969341[127] = 0.0;
   out_1602815725505969341[128] = 0.0;
   out_1602815725505969341[129] = 0.0;
   out_1602815725505969341[130] = 0.0;
   out_1602815725505969341[131] = 0.0;
   out_1602815725505969341[132] = 0.0;
   out_1602815725505969341[133] = 1.0;
   out_1602815725505969341[134] = 0.0;
   out_1602815725505969341[135] = 0.0;
   out_1602815725505969341[136] = 0.0;
   out_1602815725505969341[137] = 0.0;
   out_1602815725505969341[138] = 0.0;
   out_1602815725505969341[139] = 0.0;
   out_1602815725505969341[140] = 0.0;
   out_1602815725505969341[141] = 0.0;
   out_1602815725505969341[142] = 0.0;
   out_1602815725505969341[143] = 0.0;
   out_1602815725505969341[144] = 0.0;
   out_1602815725505969341[145] = 0.0;
   out_1602815725505969341[146] = 0.0;
   out_1602815725505969341[147] = 0.0;
   out_1602815725505969341[148] = 0.0;
   out_1602815725505969341[149] = 0.0;
   out_1602815725505969341[150] = 0.0;
   out_1602815725505969341[151] = 0.0;
   out_1602815725505969341[152] = 1.0;
   out_1602815725505969341[153] = 0.0;
   out_1602815725505969341[154] = 0.0;
   out_1602815725505969341[155] = 0.0;
   out_1602815725505969341[156] = 0.0;
   out_1602815725505969341[157] = 0.0;
   out_1602815725505969341[158] = 0.0;
   out_1602815725505969341[159] = 0.0;
   out_1602815725505969341[160] = 0.0;
   out_1602815725505969341[161] = 0.0;
   out_1602815725505969341[162] = 0.0;
   out_1602815725505969341[163] = 0.0;
   out_1602815725505969341[164] = 0.0;
   out_1602815725505969341[165] = 0.0;
   out_1602815725505969341[166] = 0.0;
   out_1602815725505969341[167] = 0.0;
   out_1602815725505969341[168] = 0.0;
   out_1602815725505969341[169] = 0.0;
   out_1602815725505969341[170] = 0.0;
   out_1602815725505969341[171] = 1.0;
   out_1602815725505969341[172] = 0.0;
   out_1602815725505969341[173] = 0.0;
   out_1602815725505969341[174] = 0.0;
   out_1602815725505969341[175] = 0.0;
   out_1602815725505969341[176] = 0.0;
   out_1602815725505969341[177] = 0.0;
   out_1602815725505969341[178] = 0.0;
   out_1602815725505969341[179] = 0.0;
   out_1602815725505969341[180] = 0.0;
   out_1602815725505969341[181] = 0.0;
   out_1602815725505969341[182] = 0.0;
   out_1602815725505969341[183] = 0.0;
   out_1602815725505969341[184] = 0.0;
   out_1602815725505969341[185] = 0.0;
   out_1602815725505969341[186] = 0.0;
   out_1602815725505969341[187] = 0.0;
   out_1602815725505969341[188] = 0.0;
   out_1602815725505969341[189] = 0.0;
   out_1602815725505969341[190] = 1.0;
   out_1602815725505969341[191] = 0.0;
   out_1602815725505969341[192] = 0.0;
   out_1602815725505969341[193] = 0.0;
   out_1602815725505969341[194] = 0.0;
   out_1602815725505969341[195] = 0.0;
   out_1602815725505969341[196] = 0.0;
   out_1602815725505969341[197] = 0.0;
   out_1602815725505969341[198] = 0.0;
   out_1602815725505969341[199] = 0.0;
   out_1602815725505969341[200] = 0.0;
   out_1602815725505969341[201] = 0.0;
   out_1602815725505969341[202] = 0.0;
   out_1602815725505969341[203] = 0.0;
   out_1602815725505969341[204] = 0.0;
   out_1602815725505969341[205] = 0.0;
   out_1602815725505969341[206] = 0.0;
   out_1602815725505969341[207] = 0.0;
   out_1602815725505969341[208] = 0.0;
   out_1602815725505969341[209] = 1.0;
   out_1602815725505969341[210] = 0.0;
   out_1602815725505969341[211] = 0.0;
   out_1602815725505969341[212] = 0.0;
   out_1602815725505969341[213] = 0.0;
   out_1602815725505969341[214] = 0.0;
   out_1602815725505969341[215] = 0.0;
   out_1602815725505969341[216] = 0.0;
   out_1602815725505969341[217] = 0.0;
   out_1602815725505969341[218] = 0.0;
   out_1602815725505969341[219] = 0.0;
   out_1602815725505969341[220] = 0.0;
   out_1602815725505969341[221] = 0.0;
   out_1602815725505969341[222] = 0.0;
   out_1602815725505969341[223] = 0.0;
   out_1602815725505969341[224] = 0.0;
   out_1602815725505969341[225] = 0.0;
   out_1602815725505969341[226] = 0.0;
   out_1602815725505969341[227] = 0.0;
   out_1602815725505969341[228] = 1.0;
   out_1602815725505969341[229] = 0.0;
   out_1602815725505969341[230] = 0.0;
   out_1602815725505969341[231] = 0.0;
   out_1602815725505969341[232] = 0.0;
   out_1602815725505969341[233] = 0.0;
   out_1602815725505969341[234] = 0.0;
   out_1602815725505969341[235] = 0.0;
   out_1602815725505969341[236] = 0.0;
   out_1602815725505969341[237] = 0.0;
   out_1602815725505969341[238] = 0.0;
   out_1602815725505969341[239] = 0.0;
   out_1602815725505969341[240] = 0.0;
   out_1602815725505969341[241] = 0.0;
   out_1602815725505969341[242] = 0.0;
   out_1602815725505969341[243] = 0.0;
   out_1602815725505969341[244] = 0.0;
   out_1602815725505969341[245] = 0.0;
   out_1602815725505969341[246] = 0.0;
   out_1602815725505969341[247] = 1.0;
   out_1602815725505969341[248] = 0.0;
   out_1602815725505969341[249] = 0.0;
   out_1602815725505969341[250] = 0.0;
   out_1602815725505969341[251] = 0.0;
   out_1602815725505969341[252] = 0.0;
   out_1602815725505969341[253] = 0.0;
   out_1602815725505969341[254] = 0.0;
   out_1602815725505969341[255] = 0.0;
   out_1602815725505969341[256] = 0.0;
   out_1602815725505969341[257] = 0.0;
   out_1602815725505969341[258] = 0.0;
   out_1602815725505969341[259] = 0.0;
   out_1602815725505969341[260] = 0.0;
   out_1602815725505969341[261] = 0.0;
   out_1602815725505969341[262] = 0.0;
   out_1602815725505969341[263] = 0.0;
   out_1602815725505969341[264] = 0.0;
   out_1602815725505969341[265] = 0.0;
   out_1602815725505969341[266] = 1.0;
   out_1602815725505969341[267] = 0.0;
   out_1602815725505969341[268] = 0.0;
   out_1602815725505969341[269] = 0.0;
   out_1602815725505969341[270] = 0.0;
   out_1602815725505969341[271] = 0.0;
   out_1602815725505969341[272] = 0.0;
   out_1602815725505969341[273] = 0.0;
   out_1602815725505969341[274] = 0.0;
   out_1602815725505969341[275] = 0.0;
   out_1602815725505969341[276] = 0.0;
   out_1602815725505969341[277] = 0.0;
   out_1602815725505969341[278] = 0.0;
   out_1602815725505969341[279] = 0.0;
   out_1602815725505969341[280] = 0.0;
   out_1602815725505969341[281] = 0.0;
   out_1602815725505969341[282] = 0.0;
   out_1602815725505969341[283] = 0.0;
   out_1602815725505969341[284] = 0.0;
   out_1602815725505969341[285] = 1.0;
   out_1602815725505969341[286] = 0.0;
   out_1602815725505969341[287] = 0.0;
   out_1602815725505969341[288] = 0.0;
   out_1602815725505969341[289] = 0.0;
   out_1602815725505969341[290] = 0.0;
   out_1602815725505969341[291] = 0.0;
   out_1602815725505969341[292] = 0.0;
   out_1602815725505969341[293] = 0.0;
   out_1602815725505969341[294] = 0.0;
   out_1602815725505969341[295] = 0.0;
   out_1602815725505969341[296] = 0.0;
   out_1602815725505969341[297] = 0.0;
   out_1602815725505969341[298] = 0.0;
   out_1602815725505969341[299] = 0.0;
   out_1602815725505969341[300] = 0.0;
   out_1602815725505969341[301] = 0.0;
   out_1602815725505969341[302] = 0.0;
   out_1602815725505969341[303] = 0.0;
   out_1602815725505969341[304] = 1.0;
   out_1602815725505969341[305] = 0.0;
   out_1602815725505969341[306] = 0.0;
   out_1602815725505969341[307] = 0.0;
   out_1602815725505969341[308] = 0.0;
   out_1602815725505969341[309] = 0.0;
   out_1602815725505969341[310] = 0.0;
   out_1602815725505969341[311] = 0.0;
   out_1602815725505969341[312] = 0.0;
   out_1602815725505969341[313] = 0.0;
   out_1602815725505969341[314] = 0.0;
   out_1602815725505969341[315] = 0.0;
   out_1602815725505969341[316] = 0.0;
   out_1602815725505969341[317] = 0.0;
   out_1602815725505969341[318] = 0.0;
   out_1602815725505969341[319] = 0.0;
   out_1602815725505969341[320] = 0.0;
   out_1602815725505969341[321] = 0.0;
   out_1602815725505969341[322] = 0.0;
   out_1602815725505969341[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_6941148323357631663) {
   out_6941148323357631663[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_6941148323357631663[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_6941148323357631663[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_6941148323357631663[3] = dt*state[12] + state[3];
   out_6941148323357631663[4] = dt*state[13] + state[4];
   out_6941148323357631663[5] = dt*state[14] + state[5];
   out_6941148323357631663[6] = state[6];
   out_6941148323357631663[7] = state[7];
   out_6941148323357631663[8] = state[8];
   out_6941148323357631663[9] = state[9];
   out_6941148323357631663[10] = state[10];
   out_6941148323357631663[11] = state[11];
   out_6941148323357631663[12] = state[12];
   out_6941148323357631663[13] = state[13];
   out_6941148323357631663[14] = state[14];
   out_6941148323357631663[15] = state[15];
   out_6941148323357631663[16] = state[16];
   out_6941148323357631663[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8174317485626071951) {
   out_8174317485626071951[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8174317485626071951[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8174317485626071951[2] = 0;
   out_8174317485626071951[3] = 0;
   out_8174317485626071951[4] = 0;
   out_8174317485626071951[5] = 0;
   out_8174317485626071951[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8174317485626071951[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8174317485626071951[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8174317485626071951[9] = 0;
   out_8174317485626071951[10] = 0;
   out_8174317485626071951[11] = 0;
   out_8174317485626071951[12] = 0;
   out_8174317485626071951[13] = 0;
   out_8174317485626071951[14] = 0;
   out_8174317485626071951[15] = 0;
   out_8174317485626071951[16] = 0;
   out_8174317485626071951[17] = 0;
   out_8174317485626071951[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8174317485626071951[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8174317485626071951[20] = 0;
   out_8174317485626071951[21] = 0;
   out_8174317485626071951[22] = 0;
   out_8174317485626071951[23] = 0;
   out_8174317485626071951[24] = 0;
   out_8174317485626071951[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8174317485626071951[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8174317485626071951[27] = 0;
   out_8174317485626071951[28] = 0;
   out_8174317485626071951[29] = 0;
   out_8174317485626071951[30] = 0;
   out_8174317485626071951[31] = 0;
   out_8174317485626071951[32] = 0;
   out_8174317485626071951[33] = 0;
   out_8174317485626071951[34] = 0;
   out_8174317485626071951[35] = 0;
   out_8174317485626071951[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8174317485626071951[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8174317485626071951[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8174317485626071951[39] = 0;
   out_8174317485626071951[40] = 0;
   out_8174317485626071951[41] = 0;
   out_8174317485626071951[42] = 0;
   out_8174317485626071951[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8174317485626071951[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8174317485626071951[45] = 0;
   out_8174317485626071951[46] = 0;
   out_8174317485626071951[47] = 0;
   out_8174317485626071951[48] = 0;
   out_8174317485626071951[49] = 0;
   out_8174317485626071951[50] = 0;
   out_8174317485626071951[51] = 0;
   out_8174317485626071951[52] = 0;
   out_8174317485626071951[53] = 0;
   out_8174317485626071951[54] = 0;
   out_8174317485626071951[55] = 0;
   out_8174317485626071951[56] = 0;
   out_8174317485626071951[57] = 1;
   out_8174317485626071951[58] = 0;
   out_8174317485626071951[59] = 0;
   out_8174317485626071951[60] = 0;
   out_8174317485626071951[61] = 0;
   out_8174317485626071951[62] = 0;
   out_8174317485626071951[63] = 0;
   out_8174317485626071951[64] = 0;
   out_8174317485626071951[65] = 0;
   out_8174317485626071951[66] = dt;
   out_8174317485626071951[67] = 0;
   out_8174317485626071951[68] = 0;
   out_8174317485626071951[69] = 0;
   out_8174317485626071951[70] = 0;
   out_8174317485626071951[71] = 0;
   out_8174317485626071951[72] = 0;
   out_8174317485626071951[73] = 0;
   out_8174317485626071951[74] = 0;
   out_8174317485626071951[75] = 0;
   out_8174317485626071951[76] = 1;
   out_8174317485626071951[77] = 0;
   out_8174317485626071951[78] = 0;
   out_8174317485626071951[79] = 0;
   out_8174317485626071951[80] = 0;
   out_8174317485626071951[81] = 0;
   out_8174317485626071951[82] = 0;
   out_8174317485626071951[83] = 0;
   out_8174317485626071951[84] = 0;
   out_8174317485626071951[85] = dt;
   out_8174317485626071951[86] = 0;
   out_8174317485626071951[87] = 0;
   out_8174317485626071951[88] = 0;
   out_8174317485626071951[89] = 0;
   out_8174317485626071951[90] = 0;
   out_8174317485626071951[91] = 0;
   out_8174317485626071951[92] = 0;
   out_8174317485626071951[93] = 0;
   out_8174317485626071951[94] = 0;
   out_8174317485626071951[95] = 1;
   out_8174317485626071951[96] = 0;
   out_8174317485626071951[97] = 0;
   out_8174317485626071951[98] = 0;
   out_8174317485626071951[99] = 0;
   out_8174317485626071951[100] = 0;
   out_8174317485626071951[101] = 0;
   out_8174317485626071951[102] = 0;
   out_8174317485626071951[103] = 0;
   out_8174317485626071951[104] = dt;
   out_8174317485626071951[105] = 0;
   out_8174317485626071951[106] = 0;
   out_8174317485626071951[107] = 0;
   out_8174317485626071951[108] = 0;
   out_8174317485626071951[109] = 0;
   out_8174317485626071951[110] = 0;
   out_8174317485626071951[111] = 0;
   out_8174317485626071951[112] = 0;
   out_8174317485626071951[113] = 0;
   out_8174317485626071951[114] = 1;
   out_8174317485626071951[115] = 0;
   out_8174317485626071951[116] = 0;
   out_8174317485626071951[117] = 0;
   out_8174317485626071951[118] = 0;
   out_8174317485626071951[119] = 0;
   out_8174317485626071951[120] = 0;
   out_8174317485626071951[121] = 0;
   out_8174317485626071951[122] = 0;
   out_8174317485626071951[123] = 0;
   out_8174317485626071951[124] = 0;
   out_8174317485626071951[125] = 0;
   out_8174317485626071951[126] = 0;
   out_8174317485626071951[127] = 0;
   out_8174317485626071951[128] = 0;
   out_8174317485626071951[129] = 0;
   out_8174317485626071951[130] = 0;
   out_8174317485626071951[131] = 0;
   out_8174317485626071951[132] = 0;
   out_8174317485626071951[133] = 1;
   out_8174317485626071951[134] = 0;
   out_8174317485626071951[135] = 0;
   out_8174317485626071951[136] = 0;
   out_8174317485626071951[137] = 0;
   out_8174317485626071951[138] = 0;
   out_8174317485626071951[139] = 0;
   out_8174317485626071951[140] = 0;
   out_8174317485626071951[141] = 0;
   out_8174317485626071951[142] = 0;
   out_8174317485626071951[143] = 0;
   out_8174317485626071951[144] = 0;
   out_8174317485626071951[145] = 0;
   out_8174317485626071951[146] = 0;
   out_8174317485626071951[147] = 0;
   out_8174317485626071951[148] = 0;
   out_8174317485626071951[149] = 0;
   out_8174317485626071951[150] = 0;
   out_8174317485626071951[151] = 0;
   out_8174317485626071951[152] = 1;
   out_8174317485626071951[153] = 0;
   out_8174317485626071951[154] = 0;
   out_8174317485626071951[155] = 0;
   out_8174317485626071951[156] = 0;
   out_8174317485626071951[157] = 0;
   out_8174317485626071951[158] = 0;
   out_8174317485626071951[159] = 0;
   out_8174317485626071951[160] = 0;
   out_8174317485626071951[161] = 0;
   out_8174317485626071951[162] = 0;
   out_8174317485626071951[163] = 0;
   out_8174317485626071951[164] = 0;
   out_8174317485626071951[165] = 0;
   out_8174317485626071951[166] = 0;
   out_8174317485626071951[167] = 0;
   out_8174317485626071951[168] = 0;
   out_8174317485626071951[169] = 0;
   out_8174317485626071951[170] = 0;
   out_8174317485626071951[171] = 1;
   out_8174317485626071951[172] = 0;
   out_8174317485626071951[173] = 0;
   out_8174317485626071951[174] = 0;
   out_8174317485626071951[175] = 0;
   out_8174317485626071951[176] = 0;
   out_8174317485626071951[177] = 0;
   out_8174317485626071951[178] = 0;
   out_8174317485626071951[179] = 0;
   out_8174317485626071951[180] = 0;
   out_8174317485626071951[181] = 0;
   out_8174317485626071951[182] = 0;
   out_8174317485626071951[183] = 0;
   out_8174317485626071951[184] = 0;
   out_8174317485626071951[185] = 0;
   out_8174317485626071951[186] = 0;
   out_8174317485626071951[187] = 0;
   out_8174317485626071951[188] = 0;
   out_8174317485626071951[189] = 0;
   out_8174317485626071951[190] = 1;
   out_8174317485626071951[191] = 0;
   out_8174317485626071951[192] = 0;
   out_8174317485626071951[193] = 0;
   out_8174317485626071951[194] = 0;
   out_8174317485626071951[195] = 0;
   out_8174317485626071951[196] = 0;
   out_8174317485626071951[197] = 0;
   out_8174317485626071951[198] = 0;
   out_8174317485626071951[199] = 0;
   out_8174317485626071951[200] = 0;
   out_8174317485626071951[201] = 0;
   out_8174317485626071951[202] = 0;
   out_8174317485626071951[203] = 0;
   out_8174317485626071951[204] = 0;
   out_8174317485626071951[205] = 0;
   out_8174317485626071951[206] = 0;
   out_8174317485626071951[207] = 0;
   out_8174317485626071951[208] = 0;
   out_8174317485626071951[209] = 1;
   out_8174317485626071951[210] = 0;
   out_8174317485626071951[211] = 0;
   out_8174317485626071951[212] = 0;
   out_8174317485626071951[213] = 0;
   out_8174317485626071951[214] = 0;
   out_8174317485626071951[215] = 0;
   out_8174317485626071951[216] = 0;
   out_8174317485626071951[217] = 0;
   out_8174317485626071951[218] = 0;
   out_8174317485626071951[219] = 0;
   out_8174317485626071951[220] = 0;
   out_8174317485626071951[221] = 0;
   out_8174317485626071951[222] = 0;
   out_8174317485626071951[223] = 0;
   out_8174317485626071951[224] = 0;
   out_8174317485626071951[225] = 0;
   out_8174317485626071951[226] = 0;
   out_8174317485626071951[227] = 0;
   out_8174317485626071951[228] = 1;
   out_8174317485626071951[229] = 0;
   out_8174317485626071951[230] = 0;
   out_8174317485626071951[231] = 0;
   out_8174317485626071951[232] = 0;
   out_8174317485626071951[233] = 0;
   out_8174317485626071951[234] = 0;
   out_8174317485626071951[235] = 0;
   out_8174317485626071951[236] = 0;
   out_8174317485626071951[237] = 0;
   out_8174317485626071951[238] = 0;
   out_8174317485626071951[239] = 0;
   out_8174317485626071951[240] = 0;
   out_8174317485626071951[241] = 0;
   out_8174317485626071951[242] = 0;
   out_8174317485626071951[243] = 0;
   out_8174317485626071951[244] = 0;
   out_8174317485626071951[245] = 0;
   out_8174317485626071951[246] = 0;
   out_8174317485626071951[247] = 1;
   out_8174317485626071951[248] = 0;
   out_8174317485626071951[249] = 0;
   out_8174317485626071951[250] = 0;
   out_8174317485626071951[251] = 0;
   out_8174317485626071951[252] = 0;
   out_8174317485626071951[253] = 0;
   out_8174317485626071951[254] = 0;
   out_8174317485626071951[255] = 0;
   out_8174317485626071951[256] = 0;
   out_8174317485626071951[257] = 0;
   out_8174317485626071951[258] = 0;
   out_8174317485626071951[259] = 0;
   out_8174317485626071951[260] = 0;
   out_8174317485626071951[261] = 0;
   out_8174317485626071951[262] = 0;
   out_8174317485626071951[263] = 0;
   out_8174317485626071951[264] = 0;
   out_8174317485626071951[265] = 0;
   out_8174317485626071951[266] = 1;
   out_8174317485626071951[267] = 0;
   out_8174317485626071951[268] = 0;
   out_8174317485626071951[269] = 0;
   out_8174317485626071951[270] = 0;
   out_8174317485626071951[271] = 0;
   out_8174317485626071951[272] = 0;
   out_8174317485626071951[273] = 0;
   out_8174317485626071951[274] = 0;
   out_8174317485626071951[275] = 0;
   out_8174317485626071951[276] = 0;
   out_8174317485626071951[277] = 0;
   out_8174317485626071951[278] = 0;
   out_8174317485626071951[279] = 0;
   out_8174317485626071951[280] = 0;
   out_8174317485626071951[281] = 0;
   out_8174317485626071951[282] = 0;
   out_8174317485626071951[283] = 0;
   out_8174317485626071951[284] = 0;
   out_8174317485626071951[285] = 1;
   out_8174317485626071951[286] = 0;
   out_8174317485626071951[287] = 0;
   out_8174317485626071951[288] = 0;
   out_8174317485626071951[289] = 0;
   out_8174317485626071951[290] = 0;
   out_8174317485626071951[291] = 0;
   out_8174317485626071951[292] = 0;
   out_8174317485626071951[293] = 0;
   out_8174317485626071951[294] = 0;
   out_8174317485626071951[295] = 0;
   out_8174317485626071951[296] = 0;
   out_8174317485626071951[297] = 0;
   out_8174317485626071951[298] = 0;
   out_8174317485626071951[299] = 0;
   out_8174317485626071951[300] = 0;
   out_8174317485626071951[301] = 0;
   out_8174317485626071951[302] = 0;
   out_8174317485626071951[303] = 0;
   out_8174317485626071951[304] = 1;
   out_8174317485626071951[305] = 0;
   out_8174317485626071951[306] = 0;
   out_8174317485626071951[307] = 0;
   out_8174317485626071951[308] = 0;
   out_8174317485626071951[309] = 0;
   out_8174317485626071951[310] = 0;
   out_8174317485626071951[311] = 0;
   out_8174317485626071951[312] = 0;
   out_8174317485626071951[313] = 0;
   out_8174317485626071951[314] = 0;
   out_8174317485626071951[315] = 0;
   out_8174317485626071951[316] = 0;
   out_8174317485626071951[317] = 0;
   out_8174317485626071951[318] = 0;
   out_8174317485626071951[319] = 0;
   out_8174317485626071951[320] = 0;
   out_8174317485626071951[321] = 0;
   out_8174317485626071951[322] = 0;
   out_8174317485626071951[323] = 1;
}
void h_4(double *state, double *unused, double *out_5523365294760256360) {
   out_5523365294760256360[0] = state[6] + state[9];
   out_5523365294760256360[1] = state[7] + state[10];
   out_5523365294760256360[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_848654723451256734) {
   out_848654723451256734[0] = 0;
   out_848654723451256734[1] = 0;
   out_848654723451256734[2] = 0;
   out_848654723451256734[3] = 0;
   out_848654723451256734[4] = 0;
   out_848654723451256734[5] = 0;
   out_848654723451256734[6] = 1;
   out_848654723451256734[7] = 0;
   out_848654723451256734[8] = 0;
   out_848654723451256734[9] = 1;
   out_848654723451256734[10] = 0;
   out_848654723451256734[11] = 0;
   out_848654723451256734[12] = 0;
   out_848654723451256734[13] = 0;
   out_848654723451256734[14] = 0;
   out_848654723451256734[15] = 0;
   out_848654723451256734[16] = 0;
   out_848654723451256734[17] = 0;
   out_848654723451256734[18] = 0;
   out_848654723451256734[19] = 0;
   out_848654723451256734[20] = 0;
   out_848654723451256734[21] = 0;
   out_848654723451256734[22] = 0;
   out_848654723451256734[23] = 0;
   out_848654723451256734[24] = 0;
   out_848654723451256734[25] = 1;
   out_848654723451256734[26] = 0;
   out_848654723451256734[27] = 0;
   out_848654723451256734[28] = 1;
   out_848654723451256734[29] = 0;
   out_848654723451256734[30] = 0;
   out_848654723451256734[31] = 0;
   out_848654723451256734[32] = 0;
   out_848654723451256734[33] = 0;
   out_848654723451256734[34] = 0;
   out_848654723451256734[35] = 0;
   out_848654723451256734[36] = 0;
   out_848654723451256734[37] = 0;
   out_848654723451256734[38] = 0;
   out_848654723451256734[39] = 0;
   out_848654723451256734[40] = 0;
   out_848654723451256734[41] = 0;
   out_848654723451256734[42] = 0;
   out_848654723451256734[43] = 0;
   out_848654723451256734[44] = 1;
   out_848654723451256734[45] = 0;
   out_848654723451256734[46] = 0;
   out_848654723451256734[47] = 1;
   out_848654723451256734[48] = 0;
   out_848654723451256734[49] = 0;
   out_848654723451256734[50] = 0;
   out_848654723451256734[51] = 0;
   out_848654723451256734[52] = 0;
   out_848654723451256734[53] = 0;
}
void h_10(double *state, double *unused, double *out_1239079208898706284) {
   out_1239079208898706284[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1239079208898706284[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1239079208898706284[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1001724707531765931) {
   out_1001724707531765931[0] = 0;
   out_1001724707531765931[1] = 9.8100000000000005*cos(state[1]);
   out_1001724707531765931[2] = 0;
   out_1001724707531765931[3] = 0;
   out_1001724707531765931[4] = -state[8];
   out_1001724707531765931[5] = state[7];
   out_1001724707531765931[6] = 0;
   out_1001724707531765931[7] = state[5];
   out_1001724707531765931[8] = -state[4];
   out_1001724707531765931[9] = 0;
   out_1001724707531765931[10] = 0;
   out_1001724707531765931[11] = 0;
   out_1001724707531765931[12] = 1;
   out_1001724707531765931[13] = 0;
   out_1001724707531765931[14] = 0;
   out_1001724707531765931[15] = 1;
   out_1001724707531765931[16] = 0;
   out_1001724707531765931[17] = 0;
   out_1001724707531765931[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1001724707531765931[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1001724707531765931[20] = 0;
   out_1001724707531765931[21] = state[8];
   out_1001724707531765931[22] = 0;
   out_1001724707531765931[23] = -state[6];
   out_1001724707531765931[24] = -state[5];
   out_1001724707531765931[25] = 0;
   out_1001724707531765931[26] = state[3];
   out_1001724707531765931[27] = 0;
   out_1001724707531765931[28] = 0;
   out_1001724707531765931[29] = 0;
   out_1001724707531765931[30] = 0;
   out_1001724707531765931[31] = 1;
   out_1001724707531765931[32] = 0;
   out_1001724707531765931[33] = 0;
   out_1001724707531765931[34] = 1;
   out_1001724707531765931[35] = 0;
   out_1001724707531765931[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1001724707531765931[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1001724707531765931[38] = 0;
   out_1001724707531765931[39] = -state[7];
   out_1001724707531765931[40] = state[6];
   out_1001724707531765931[41] = 0;
   out_1001724707531765931[42] = state[4];
   out_1001724707531765931[43] = -state[3];
   out_1001724707531765931[44] = 0;
   out_1001724707531765931[45] = 0;
   out_1001724707531765931[46] = 0;
   out_1001724707531765931[47] = 0;
   out_1001724707531765931[48] = 0;
   out_1001724707531765931[49] = 0;
   out_1001724707531765931[50] = 1;
   out_1001724707531765931[51] = 0;
   out_1001724707531765931[52] = 0;
   out_1001724707531765931[53] = 1;
}
void h_13(double *state, double *unused, double *out_7307670055393162069) {
   out_7307670055393162069[0] = state[3];
   out_7307670055393162069[1] = state[4];
   out_7307670055393162069[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6761976484865444195) {
   out_6761976484865444195[0] = 0;
   out_6761976484865444195[1] = 0;
   out_6761976484865444195[2] = 0;
   out_6761976484865444195[3] = 1;
   out_6761976484865444195[4] = 0;
   out_6761976484865444195[5] = 0;
   out_6761976484865444195[6] = 0;
   out_6761976484865444195[7] = 0;
   out_6761976484865444195[8] = 0;
   out_6761976484865444195[9] = 0;
   out_6761976484865444195[10] = 0;
   out_6761976484865444195[11] = 0;
   out_6761976484865444195[12] = 0;
   out_6761976484865444195[13] = 0;
   out_6761976484865444195[14] = 0;
   out_6761976484865444195[15] = 0;
   out_6761976484865444195[16] = 0;
   out_6761976484865444195[17] = 0;
   out_6761976484865444195[18] = 0;
   out_6761976484865444195[19] = 0;
   out_6761976484865444195[20] = 0;
   out_6761976484865444195[21] = 0;
   out_6761976484865444195[22] = 1;
   out_6761976484865444195[23] = 0;
   out_6761976484865444195[24] = 0;
   out_6761976484865444195[25] = 0;
   out_6761976484865444195[26] = 0;
   out_6761976484865444195[27] = 0;
   out_6761976484865444195[28] = 0;
   out_6761976484865444195[29] = 0;
   out_6761976484865444195[30] = 0;
   out_6761976484865444195[31] = 0;
   out_6761976484865444195[32] = 0;
   out_6761976484865444195[33] = 0;
   out_6761976484865444195[34] = 0;
   out_6761976484865444195[35] = 0;
   out_6761976484865444195[36] = 0;
   out_6761976484865444195[37] = 0;
   out_6761976484865444195[38] = 0;
   out_6761976484865444195[39] = 0;
   out_6761976484865444195[40] = 0;
   out_6761976484865444195[41] = 1;
   out_6761976484865444195[42] = 0;
   out_6761976484865444195[43] = 0;
   out_6761976484865444195[44] = 0;
   out_6761976484865444195[45] = 0;
   out_6761976484865444195[46] = 0;
   out_6761976484865444195[47] = 0;
   out_6761976484865444195[48] = 0;
   out_6761976484865444195[49] = 0;
   out_6761976484865444195[50] = 0;
   out_6761976484865444195[51] = 0;
   out_6761976484865444195[52] = 0;
   out_6761976484865444195[53] = 0;
}
void h_14(double *state, double *unused, double *out_7233663736752442507) {
   out_7233663736752442507[0] = state[6];
   out_7233663736752442507[1] = state[7];
   out_7233663736752442507[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3114586132888227795) {
   out_3114586132888227795[0] = 0;
   out_3114586132888227795[1] = 0;
   out_3114586132888227795[2] = 0;
   out_3114586132888227795[3] = 0;
   out_3114586132888227795[4] = 0;
   out_3114586132888227795[5] = 0;
   out_3114586132888227795[6] = 1;
   out_3114586132888227795[7] = 0;
   out_3114586132888227795[8] = 0;
   out_3114586132888227795[9] = 0;
   out_3114586132888227795[10] = 0;
   out_3114586132888227795[11] = 0;
   out_3114586132888227795[12] = 0;
   out_3114586132888227795[13] = 0;
   out_3114586132888227795[14] = 0;
   out_3114586132888227795[15] = 0;
   out_3114586132888227795[16] = 0;
   out_3114586132888227795[17] = 0;
   out_3114586132888227795[18] = 0;
   out_3114586132888227795[19] = 0;
   out_3114586132888227795[20] = 0;
   out_3114586132888227795[21] = 0;
   out_3114586132888227795[22] = 0;
   out_3114586132888227795[23] = 0;
   out_3114586132888227795[24] = 0;
   out_3114586132888227795[25] = 1;
   out_3114586132888227795[26] = 0;
   out_3114586132888227795[27] = 0;
   out_3114586132888227795[28] = 0;
   out_3114586132888227795[29] = 0;
   out_3114586132888227795[30] = 0;
   out_3114586132888227795[31] = 0;
   out_3114586132888227795[32] = 0;
   out_3114586132888227795[33] = 0;
   out_3114586132888227795[34] = 0;
   out_3114586132888227795[35] = 0;
   out_3114586132888227795[36] = 0;
   out_3114586132888227795[37] = 0;
   out_3114586132888227795[38] = 0;
   out_3114586132888227795[39] = 0;
   out_3114586132888227795[40] = 0;
   out_3114586132888227795[41] = 0;
   out_3114586132888227795[42] = 0;
   out_3114586132888227795[43] = 0;
   out_3114586132888227795[44] = 1;
   out_3114586132888227795[45] = 0;
   out_3114586132888227795[46] = 0;
   out_3114586132888227795[47] = 0;
   out_3114586132888227795[48] = 0;
   out_3114586132888227795[49] = 0;
   out_3114586132888227795[50] = 0;
   out_3114586132888227795[51] = 0;
   out_3114586132888227795[52] = 0;
   out_3114586132888227795[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_8123935570106658818) {
  err_fun(nom_x, delta_x, out_8123935570106658818);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7916605304970807670) {
  inv_err_fun(nom_x, true_x, out_7916605304970807670);
}
void pose_H_mod_fun(double *state, double *out_1602815725505969341) {
  H_mod_fun(state, out_1602815725505969341);
}
void pose_f_fun(double *state, double dt, double *out_6941148323357631663) {
  f_fun(state,  dt, out_6941148323357631663);
}
void pose_F_fun(double *state, double dt, double *out_8174317485626071951) {
  F_fun(state,  dt, out_8174317485626071951);
}
void pose_h_4(double *state, double *unused, double *out_5523365294760256360) {
  h_4(state, unused, out_5523365294760256360);
}
void pose_H_4(double *state, double *unused, double *out_848654723451256734) {
  H_4(state, unused, out_848654723451256734);
}
void pose_h_10(double *state, double *unused, double *out_1239079208898706284) {
  h_10(state, unused, out_1239079208898706284);
}
void pose_H_10(double *state, double *unused, double *out_1001724707531765931) {
  H_10(state, unused, out_1001724707531765931);
}
void pose_h_13(double *state, double *unused, double *out_7307670055393162069) {
  h_13(state, unused, out_7307670055393162069);
}
void pose_H_13(double *state, double *unused, double *out_6761976484865444195) {
  H_13(state, unused, out_6761976484865444195);
}
void pose_h_14(double *state, double *unused, double *out_7233663736752442507) {
  h_14(state, unused, out_7233663736752442507);
}
void pose_H_14(double *state, double *unused, double *out_3114586132888227795) {
  H_14(state, unused, out_3114586132888227795);
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
