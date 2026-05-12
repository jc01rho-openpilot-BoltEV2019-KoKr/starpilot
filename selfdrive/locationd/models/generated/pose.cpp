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
void err_fun(double *nom_x, double *delta_x, double *out_2235485331980533535) {
   out_2235485331980533535[0] = delta_x[0] + nom_x[0];
   out_2235485331980533535[1] = delta_x[1] + nom_x[1];
   out_2235485331980533535[2] = delta_x[2] + nom_x[2];
   out_2235485331980533535[3] = delta_x[3] + nom_x[3];
   out_2235485331980533535[4] = delta_x[4] + nom_x[4];
   out_2235485331980533535[5] = delta_x[5] + nom_x[5];
   out_2235485331980533535[6] = delta_x[6] + nom_x[6];
   out_2235485331980533535[7] = delta_x[7] + nom_x[7];
   out_2235485331980533535[8] = delta_x[8] + nom_x[8];
   out_2235485331980533535[9] = delta_x[9] + nom_x[9];
   out_2235485331980533535[10] = delta_x[10] + nom_x[10];
   out_2235485331980533535[11] = delta_x[11] + nom_x[11];
   out_2235485331980533535[12] = delta_x[12] + nom_x[12];
   out_2235485331980533535[13] = delta_x[13] + nom_x[13];
   out_2235485331980533535[14] = delta_x[14] + nom_x[14];
   out_2235485331980533535[15] = delta_x[15] + nom_x[15];
   out_2235485331980533535[16] = delta_x[16] + nom_x[16];
   out_2235485331980533535[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6263710841243713274) {
   out_6263710841243713274[0] = -nom_x[0] + true_x[0];
   out_6263710841243713274[1] = -nom_x[1] + true_x[1];
   out_6263710841243713274[2] = -nom_x[2] + true_x[2];
   out_6263710841243713274[3] = -nom_x[3] + true_x[3];
   out_6263710841243713274[4] = -nom_x[4] + true_x[4];
   out_6263710841243713274[5] = -nom_x[5] + true_x[5];
   out_6263710841243713274[6] = -nom_x[6] + true_x[6];
   out_6263710841243713274[7] = -nom_x[7] + true_x[7];
   out_6263710841243713274[8] = -nom_x[8] + true_x[8];
   out_6263710841243713274[9] = -nom_x[9] + true_x[9];
   out_6263710841243713274[10] = -nom_x[10] + true_x[10];
   out_6263710841243713274[11] = -nom_x[11] + true_x[11];
   out_6263710841243713274[12] = -nom_x[12] + true_x[12];
   out_6263710841243713274[13] = -nom_x[13] + true_x[13];
   out_6263710841243713274[14] = -nom_x[14] + true_x[14];
   out_6263710841243713274[15] = -nom_x[15] + true_x[15];
   out_6263710841243713274[16] = -nom_x[16] + true_x[16];
   out_6263710841243713274[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_874056645799517577) {
   out_874056645799517577[0] = 1.0;
   out_874056645799517577[1] = 0.0;
   out_874056645799517577[2] = 0.0;
   out_874056645799517577[3] = 0.0;
   out_874056645799517577[4] = 0.0;
   out_874056645799517577[5] = 0.0;
   out_874056645799517577[6] = 0.0;
   out_874056645799517577[7] = 0.0;
   out_874056645799517577[8] = 0.0;
   out_874056645799517577[9] = 0.0;
   out_874056645799517577[10] = 0.0;
   out_874056645799517577[11] = 0.0;
   out_874056645799517577[12] = 0.0;
   out_874056645799517577[13] = 0.0;
   out_874056645799517577[14] = 0.0;
   out_874056645799517577[15] = 0.0;
   out_874056645799517577[16] = 0.0;
   out_874056645799517577[17] = 0.0;
   out_874056645799517577[18] = 0.0;
   out_874056645799517577[19] = 1.0;
   out_874056645799517577[20] = 0.0;
   out_874056645799517577[21] = 0.0;
   out_874056645799517577[22] = 0.0;
   out_874056645799517577[23] = 0.0;
   out_874056645799517577[24] = 0.0;
   out_874056645799517577[25] = 0.0;
   out_874056645799517577[26] = 0.0;
   out_874056645799517577[27] = 0.0;
   out_874056645799517577[28] = 0.0;
   out_874056645799517577[29] = 0.0;
   out_874056645799517577[30] = 0.0;
   out_874056645799517577[31] = 0.0;
   out_874056645799517577[32] = 0.0;
   out_874056645799517577[33] = 0.0;
   out_874056645799517577[34] = 0.0;
   out_874056645799517577[35] = 0.0;
   out_874056645799517577[36] = 0.0;
   out_874056645799517577[37] = 0.0;
   out_874056645799517577[38] = 1.0;
   out_874056645799517577[39] = 0.0;
   out_874056645799517577[40] = 0.0;
   out_874056645799517577[41] = 0.0;
   out_874056645799517577[42] = 0.0;
   out_874056645799517577[43] = 0.0;
   out_874056645799517577[44] = 0.0;
   out_874056645799517577[45] = 0.0;
   out_874056645799517577[46] = 0.0;
   out_874056645799517577[47] = 0.0;
   out_874056645799517577[48] = 0.0;
   out_874056645799517577[49] = 0.0;
   out_874056645799517577[50] = 0.0;
   out_874056645799517577[51] = 0.0;
   out_874056645799517577[52] = 0.0;
   out_874056645799517577[53] = 0.0;
   out_874056645799517577[54] = 0.0;
   out_874056645799517577[55] = 0.0;
   out_874056645799517577[56] = 0.0;
   out_874056645799517577[57] = 1.0;
   out_874056645799517577[58] = 0.0;
   out_874056645799517577[59] = 0.0;
   out_874056645799517577[60] = 0.0;
   out_874056645799517577[61] = 0.0;
   out_874056645799517577[62] = 0.0;
   out_874056645799517577[63] = 0.0;
   out_874056645799517577[64] = 0.0;
   out_874056645799517577[65] = 0.0;
   out_874056645799517577[66] = 0.0;
   out_874056645799517577[67] = 0.0;
   out_874056645799517577[68] = 0.0;
   out_874056645799517577[69] = 0.0;
   out_874056645799517577[70] = 0.0;
   out_874056645799517577[71] = 0.0;
   out_874056645799517577[72] = 0.0;
   out_874056645799517577[73] = 0.0;
   out_874056645799517577[74] = 0.0;
   out_874056645799517577[75] = 0.0;
   out_874056645799517577[76] = 1.0;
   out_874056645799517577[77] = 0.0;
   out_874056645799517577[78] = 0.0;
   out_874056645799517577[79] = 0.0;
   out_874056645799517577[80] = 0.0;
   out_874056645799517577[81] = 0.0;
   out_874056645799517577[82] = 0.0;
   out_874056645799517577[83] = 0.0;
   out_874056645799517577[84] = 0.0;
   out_874056645799517577[85] = 0.0;
   out_874056645799517577[86] = 0.0;
   out_874056645799517577[87] = 0.0;
   out_874056645799517577[88] = 0.0;
   out_874056645799517577[89] = 0.0;
   out_874056645799517577[90] = 0.0;
   out_874056645799517577[91] = 0.0;
   out_874056645799517577[92] = 0.0;
   out_874056645799517577[93] = 0.0;
   out_874056645799517577[94] = 0.0;
   out_874056645799517577[95] = 1.0;
   out_874056645799517577[96] = 0.0;
   out_874056645799517577[97] = 0.0;
   out_874056645799517577[98] = 0.0;
   out_874056645799517577[99] = 0.0;
   out_874056645799517577[100] = 0.0;
   out_874056645799517577[101] = 0.0;
   out_874056645799517577[102] = 0.0;
   out_874056645799517577[103] = 0.0;
   out_874056645799517577[104] = 0.0;
   out_874056645799517577[105] = 0.0;
   out_874056645799517577[106] = 0.0;
   out_874056645799517577[107] = 0.0;
   out_874056645799517577[108] = 0.0;
   out_874056645799517577[109] = 0.0;
   out_874056645799517577[110] = 0.0;
   out_874056645799517577[111] = 0.0;
   out_874056645799517577[112] = 0.0;
   out_874056645799517577[113] = 0.0;
   out_874056645799517577[114] = 1.0;
   out_874056645799517577[115] = 0.0;
   out_874056645799517577[116] = 0.0;
   out_874056645799517577[117] = 0.0;
   out_874056645799517577[118] = 0.0;
   out_874056645799517577[119] = 0.0;
   out_874056645799517577[120] = 0.0;
   out_874056645799517577[121] = 0.0;
   out_874056645799517577[122] = 0.0;
   out_874056645799517577[123] = 0.0;
   out_874056645799517577[124] = 0.0;
   out_874056645799517577[125] = 0.0;
   out_874056645799517577[126] = 0.0;
   out_874056645799517577[127] = 0.0;
   out_874056645799517577[128] = 0.0;
   out_874056645799517577[129] = 0.0;
   out_874056645799517577[130] = 0.0;
   out_874056645799517577[131] = 0.0;
   out_874056645799517577[132] = 0.0;
   out_874056645799517577[133] = 1.0;
   out_874056645799517577[134] = 0.0;
   out_874056645799517577[135] = 0.0;
   out_874056645799517577[136] = 0.0;
   out_874056645799517577[137] = 0.0;
   out_874056645799517577[138] = 0.0;
   out_874056645799517577[139] = 0.0;
   out_874056645799517577[140] = 0.0;
   out_874056645799517577[141] = 0.0;
   out_874056645799517577[142] = 0.0;
   out_874056645799517577[143] = 0.0;
   out_874056645799517577[144] = 0.0;
   out_874056645799517577[145] = 0.0;
   out_874056645799517577[146] = 0.0;
   out_874056645799517577[147] = 0.0;
   out_874056645799517577[148] = 0.0;
   out_874056645799517577[149] = 0.0;
   out_874056645799517577[150] = 0.0;
   out_874056645799517577[151] = 0.0;
   out_874056645799517577[152] = 1.0;
   out_874056645799517577[153] = 0.0;
   out_874056645799517577[154] = 0.0;
   out_874056645799517577[155] = 0.0;
   out_874056645799517577[156] = 0.0;
   out_874056645799517577[157] = 0.0;
   out_874056645799517577[158] = 0.0;
   out_874056645799517577[159] = 0.0;
   out_874056645799517577[160] = 0.0;
   out_874056645799517577[161] = 0.0;
   out_874056645799517577[162] = 0.0;
   out_874056645799517577[163] = 0.0;
   out_874056645799517577[164] = 0.0;
   out_874056645799517577[165] = 0.0;
   out_874056645799517577[166] = 0.0;
   out_874056645799517577[167] = 0.0;
   out_874056645799517577[168] = 0.0;
   out_874056645799517577[169] = 0.0;
   out_874056645799517577[170] = 0.0;
   out_874056645799517577[171] = 1.0;
   out_874056645799517577[172] = 0.0;
   out_874056645799517577[173] = 0.0;
   out_874056645799517577[174] = 0.0;
   out_874056645799517577[175] = 0.0;
   out_874056645799517577[176] = 0.0;
   out_874056645799517577[177] = 0.0;
   out_874056645799517577[178] = 0.0;
   out_874056645799517577[179] = 0.0;
   out_874056645799517577[180] = 0.0;
   out_874056645799517577[181] = 0.0;
   out_874056645799517577[182] = 0.0;
   out_874056645799517577[183] = 0.0;
   out_874056645799517577[184] = 0.0;
   out_874056645799517577[185] = 0.0;
   out_874056645799517577[186] = 0.0;
   out_874056645799517577[187] = 0.0;
   out_874056645799517577[188] = 0.0;
   out_874056645799517577[189] = 0.0;
   out_874056645799517577[190] = 1.0;
   out_874056645799517577[191] = 0.0;
   out_874056645799517577[192] = 0.0;
   out_874056645799517577[193] = 0.0;
   out_874056645799517577[194] = 0.0;
   out_874056645799517577[195] = 0.0;
   out_874056645799517577[196] = 0.0;
   out_874056645799517577[197] = 0.0;
   out_874056645799517577[198] = 0.0;
   out_874056645799517577[199] = 0.0;
   out_874056645799517577[200] = 0.0;
   out_874056645799517577[201] = 0.0;
   out_874056645799517577[202] = 0.0;
   out_874056645799517577[203] = 0.0;
   out_874056645799517577[204] = 0.0;
   out_874056645799517577[205] = 0.0;
   out_874056645799517577[206] = 0.0;
   out_874056645799517577[207] = 0.0;
   out_874056645799517577[208] = 0.0;
   out_874056645799517577[209] = 1.0;
   out_874056645799517577[210] = 0.0;
   out_874056645799517577[211] = 0.0;
   out_874056645799517577[212] = 0.0;
   out_874056645799517577[213] = 0.0;
   out_874056645799517577[214] = 0.0;
   out_874056645799517577[215] = 0.0;
   out_874056645799517577[216] = 0.0;
   out_874056645799517577[217] = 0.0;
   out_874056645799517577[218] = 0.0;
   out_874056645799517577[219] = 0.0;
   out_874056645799517577[220] = 0.0;
   out_874056645799517577[221] = 0.0;
   out_874056645799517577[222] = 0.0;
   out_874056645799517577[223] = 0.0;
   out_874056645799517577[224] = 0.0;
   out_874056645799517577[225] = 0.0;
   out_874056645799517577[226] = 0.0;
   out_874056645799517577[227] = 0.0;
   out_874056645799517577[228] = 1.0;
   out_874056645799517577[229] = 0.0;
   out_874056645799517577[230] = 0.0;
   out_874056645799517577[231] = 0.0;
   out_874056645799517577[232] = 0.0;
   out_874056645799517577[233] = 0.0;
   out_874056645799517577[234] = 0.0;
   out_874056645799517577[235] = 0.0;
   out_874056645799517577[236] = 0.0;
   out_874056645799517577[237] = 0.0;
   out_874056645799517577[238] = 0.0;
   out_874056645799517577[239] = 0.0;
   out_874056645799517577[240] = 0.0;
   out_874056645799517577[241] = 0.0;
   out_874056645799517577[242] = 0.0;
   out_874056645799517577[243] = 0.0;
   out_874056645799517577[244] = 0.0;
   out_874056645799517577[245] = 0.0;
   out_874056645799517577[246] = 0.0;
   out_874056645799517577[247] = 1.0;
   out_874056645799517577[248] = 0.0;
   out_874056645799517577[249] = 0.0;
   out_874056645799517577[250] = 0.0;
   out_874056645799517577[251] = 0.0;
   out_874056645799517577[252] = 0.0;
   out_874056645799517577[253] = 0.0;
   out_874056645799517577[254] = 0.0;
   out_874056645799517577[255] = 0.0;
   out_874056645799517577[256] = 0.0;
   out_874056645799517577[257] = 0.0;
   out_874056645799517577[258] = 0.0;
   out_874056645799517577[259] = 0.0;
   out_874056645799517577[260] = 0.0;
   out_874056645799517577[261] = 0.0;
   out_874056645799517577[262] = 0.0;
   out_874056645799517577[263] = 0.0;
   out_874056645799517577[264] = 0.0;
   out_874056645799517577[265] = 0.0;
   out_874056645799517577[266] = 1.0;
   out_874056645799517577[267] = 0.0;
   out_874056645799517577[268] = 0.0;
   out_874056645799517577[269] = 0.0;
   out_874056645799517577[270] = 0.0;
   out_874056645799517577[271] = 0.0;
   out_874056645799517577[272] = 0.0;
   out_874056645799517577[273] = 0.0;
   out_874056645799517577[274] = 0.0;
   out_874056645799517577[275] = 0.0;
   out_874056645799517577[276] = 0.0;
   out_874056645799517577[277] = 0.0;
   out_874056645799517577[278] = 0.0;
   out_874056645799517577[279] = 0.0;
   out_874056645799517577[280] = 0.0;
   out_874056645799517577[281] = 0.0;
   out_874056645799517577[282] = 0.0;
   out_874056645799517577[283] = 0.0;
   out_874056645799517577[284] = 0.0;
   out_874056645799517577[285] = 1.0;
   out_874056645799517577[286] = 0.0;
   out_874056645799517577[287] = 0.0;
   out_874056645799517577[288] = 0.0;
   out_874056645799517577[289] = 0.0;
   out_874056645799517577[290] = 0.0;
   out_874056645799517577[291] = 0.0;
   out_874056645799517577[292] = 0.0;
   out_874056645799517577[293] = 0.0;
   out_874056645799517577[294] = 0.0;
   out_874056645799517577[295] = 0.0;
   out_874056645799517577[296] = 0.0;
   out_874056645799517577[297] = 0.0;
   out_874056645799517577[298] = 0.0;
   out_874056645799517577[299] = 0.0;
   out_874056645799517577[300] = 0.0;
   out_874056645799517577[301] = 0.0;
   out_874056645799517577[302] = 0.0;
   out_874056645799517577[303] = 0.0;
   out_874056645799517577[304] = 1.0;
   out_874056645799517577[305] = 0.0;
   out_874056645799517577[306] = 0.0;
   out_874056645799517577[307] = 0.0;
   out_874056645799517577[308] = 0.0;
   out_874056645799517577[309] = 0.0;
   out_874056645799517577[310] = 0.0;
   out_874056645799517577[311] = 0.0;
   out_874056645799517577[312] = 0.0;
   out_874056645799517577[313] = 0.0;
   out_874056645799517577[314] = 0.0;
   out_874056645799517577[315] = 0.0;
   out_874056645799517577[316] = 0.0;
   out_874056645799517577[317] = 0.0;
   out_874056645799517577[318] = 0.0;
   out_874056645799517577[319] = 0.0;
   out_874056645799517577[320] = 0.0;
   out_874056645799517577[321] = 0.0;
   out_874056645799517577[322] = 0.0;
   out_874056645799517577[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_7518635824214998963) {
   out_7518635824214998963[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_7518635824214998963[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_7518635824214998963[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_7518635824214998963[3] = dt*state[12] + state[3];
   out_7518635824214998963[4] = dt*state[13] + state[4];
   out_7518635824214998963[5] = dt*state[14] + state[5];
   out_7518635824214998963[6] = state[6];
   out_7518635824214998963[7] = state[7];
   out_7518635824214998963[8] = state[8];
   out_7518635824214998963[9] = state[9];
   out_7518635824214998963[10] = state[10];
   out_7518635824214998963[11] = state[11];
   out_7518635824214998963[12] = state[12];
   out_7518635824214998963[13] = state[13];
   out_7518635824214998963[14] = state[14];
   out_7518635824214998963[15] = state[15];
   out_7518635824214998963[16] = state[16];
   out_7518635824214998963[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2943843104528284461) {
   out_2943843104528284461[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2943843104528284461[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2943843104528284461[2] = 0;
   out_2943843104528284461[3] = 0;
   out_2943843104528284461[4] = 0;
   out_2943843104528284461[5] = 0;
   out_2943843104528284461[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2943843104528284461[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2943843104528284461[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2943843104528284461[9] = 0;
   out_2943843104528284461[10] = 0;
   out_2943843104528284461[11] = 0;
   out_2943843104528284461[12] = 0;
   out_2943843104528284461[13] = 0;
   out_2943843104528284461[14] = 0;
   out_2943843104528284461[15] = 0;
   out_2943843104528284461[16] = 0;
   out_2943843104528284461[17] = 0;
   out_2943843104528284461[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2943843104528284461[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2943843104528284461[20] = 0;
   out_2943843104528284461[21] = 0;
   out_2943843104528284461[22] = 0;
   out_2943843104528284461[23] = 0;
   out_2943843104528284461[24] = 0;
   out_2943843104528284461[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2943843104528284461[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2943843104528284461[27] = 0;
   out_2943843104528284461[28] = 0;
   out_2943843104528284461[29] = 0;
   out_2943843104528284461[30] = 0;
   out_2943843104528284461[31] = 0;
   out_2943843104528284461[32] = 0;
   out_2943843104528284461[33] = 0;
   out_2943843104528284461[34] = 0;
   out_2943843104528284461[35] = 0;
   out_2943843104528284461[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2943843104528284461[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2943843104528284461[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2943843104528284461[39] = 0;
   out_2943843104528284461[40] = 0;
   out_2943843104528284461[41] = 0;
   out_2943843104528284461[42] = 0;
   out_2943843104528284461[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2943843104528284461[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2943843104528284461[45] = 0;
   out_2943843104528284461[46] = 0;
   out_2943843104528284461[47] = 0;
   out_2943843104528284461[48] = 0;
   out_2943843104528284461[49] = 0;
   out_2943843104528284461[50] = 0;
   out_2943843104528284461[51] = 0;
   out_2943843104528284461[52] = 0;
   out_2943843104528284461[53] = 0;
   out_2943843104528284461[54] = 0;
   out_2943843104528284461[55] = 0;
   out_2943843104528284461[56] = 0;
   out_2943843104528284461[57] = 1;
   out_2943843104528284461[58] = 0;
   out_2943843104528284461[59] = 0;
   out_2943843104528284461[60] = 0;
   out_2943843104528284461[61] = 0;
   out_2943843104528284461[62] = 0;
   out_2943843104528284461[63] = 0;
   out_2943843104528284461[64] = 0;
   out_2943843104528284461[65] = 0;
   out_2943843104528284461[66] = dt;
   out_2943843104528284461[67] = 0;
   out_2943843104528284461[68] = 0;
   out_2943843104528284461[69] = 0;
   out_2943843104528284461[70] = 0;
   out_2943843104528284461[71] = 0;
   out_2943843104528284461[72] = 0;
   out_2943843104528284461[73] = 0;
   out_2943843104528284461[74] = 0;
   out_2943843104528284461[75] = 0;
   out_2943843104528284461[76] = 1;
   out_2943843104528284461[77] = 0;
   out_2943843104528284461[78] = 0;
   out_2943843104528284461[79] = 0;
   out_2943843104528284461[80] = 0;
   out_2943843104528284461[81] = 0;
   out_2943843104528284461[82] = 0;
   out_2943843104528284461[83] = 0;
   out_2943843104528284461[84] = 0;
   out_2943843104528284461[85] = dt;
   out_2943843104528284461[86] = 0;
   out_2943843104528284461[87] = 0;
   out_2943843104528284461[88] = 0;
   out_2943843104528284461[89] = 0;
   out_2943843104528284461[90] = 0;
   out_2943843104528284461[91] = 0;
   out_2943843104528284461[92] = 0;
   out_2943843104528284461[93] = 0;
   out_2943843104528284461[94] = 0;
   out_2943843104528284461[95] = 1;
   out_2943843104528284461[96] = 0;
   out_2943843104528284461[97] = 0;
   out_2943843104528284461[98] = 0;
   out_2943843104528284461[99] = 0;
   out_2943843104528284461[100] = 0;
   out_2943843104528284461[101] = 0;
   out_2943843104528284461[102] = 0;
   out_2943843104528284461[103] = 0;
   out_2943843104528284461[104] = dt;
   out_2943843104528284461[105] = 0;
   out_2943843104528284461[106] = 0;
   out_2943843104528284461[107] = 0;
   out_2943843104528284461[108] = 0;
   out_2943843104528284461[109] = 0;
   out_2943843104528284461[110] = 0;
   out_2943843104528284461[111] = 0;
   out_2943843104528284461[112] = 0;
   out_2943843104528284461[113] = 0;
   out_2943843104528284461[114] = 1;
   out_2943843104528284461[115] = 0;
   out_2943843104528284461[116] = 0;
   out_2943843104528284461[117] = 0;
   out_2943843104528284461[118] = 0;
   out_2943843104528284461[119] = 0;
   out_2943843104528284461[120] = 0;
   out_2943843104528284461[121] = 0;
   out_2943843104528284461[122] = 0;
   out_2943843104528284461[123] = 0;
   out_2943843104528284461[124] = 0;
   out_2943843104528284461[125] = 0;
   out_2943843104528284461[126] = 0;
   out_2943843104528284461[127] = 0;
   out_2943843104528284461[128] = 0;
   out_2943843104528284461[129] = 0;
   out_2943843104528284461[130] = 0;
   out_2943843104528284461[131] = 0;
   out_2943843104528284461[132] = 0;
   out_2943843104528284461[133] = 1;
   out_2943843104528284461[134] = 0;
   out_2943843104528284461[135] = 0;
   out_2943843104528284461[136] = 0;
   out_2943843104528284461[137] = 0;
   out_2943843104528284461[138] = 0;
   out_2943843104528284461[139] = 0;
   out_2943843104528284461[140] = 0;
   out_2943843104528284461[141] = 0;
   out_2943843104528284461[142] = 0;
   out_2943843104528284461[143] = 0;
   out_2943843104528284461[144] = 0;
   out_2943843104528284461[145] = 0;
   out_2943843104528284461[146] = 0;
   out_2943843104528284461[147] = 0;
   out_2943843104528284461[148] = 0;
   out_2943843104528284461[149] = 0;
   out_2943843104528284461[150] = 0;
   out_2943843104528284461[151] = 0;
   out_2943843104528284461[152] = 1;
   out_2943843104528284461[153] = 0;
   out_2943843104528284461[154] = 0;
   out_2943843104528284461[155] = 0;
   out_2943843104528284461[156] = 0;
   out_2943843104528284461[157] = 0;
   out_2943843104528284461[158] = 0;
   out_2943843104528284461[159] = 0;
   out_2943843104528284461[160] = 0;
   out_2943843104528284461[161] = 0;
   out_2943843104528284461[162] = 0;
   out_2943843104528284461[163] = 0;
   out_2943843104528284461[164] = 0;
   out_2943843104528284461[165] = 0;
   out_2943843104528284461[166] = 0;
   out_2943843104528284461[167] = 0;
   out_2943843104528284461[168] = 0;
   out_2943843104528284461[169] = 0;
   out_2943843104528284461[170] = 0;
   out_2943843104528284461[171] = 1;
   out_2943843104528284461[172] = 0;
   out_2943843104528284461[173] = 0;
   out_2943843104528284461[174] = 0;
   out_2943843104528284461[175] = 0;
   out_2943843104528284461[176] = 0;
   out_2943843104528284461[177] = 0;
   out_2943843104528284461[178] = 0;
   out_2943843104528284461[179] = 0;
   out_2943843104528284461[180] = 0;
   out_2943843104528284461[181] = 0;
   out_2943843104528284461[182] = 0;
   out_2943843104528284461[183] = 0;
   out_2943843104528284461[184] = 0;
   out_2943843104528284461[185] = 0;
   out_2943843104528284461[186] = 0;
   out_2943843104528284461[187] = 0;
   out_2943843104528284461[188] = 0;
   out_2943843104528284461[189] = 0;
   out_2943843104528284461[190] = 1;
   out_2943843104528284461[191] = 0;
   out_2943843104528284461[192] = 0;
   out_2943843104528284461[193] = 0;
   out_2943843104528284461[194] = 0;
   out_2943843104528284461[195] = 0;
   out_2943843104528284461[196] = 0;
   out_2943843104528284461[197] = 0;
   out_2943843104528284461[198] = 0;
   out_2943843104528284461[199] = 0;
   out_2943843104528284461[200] = 0;
   out_2943843104528284461[201] = 0;
   out_2943843104528284461[202] = 0;
   out_2943843104528284461[203] = 0;
   out_2943843104528284461[204] = 0;
   out_2943843104528284461[205] = 0;
   out_2943843104528284461[206] = 0;
   out_2943843104528284461[207] = 0;
   out_2943843104528284461[208] = 0;
   out_2943843104528284461[209] = 1;
   out_2943843104528284461[210] = 0;
   out_2943843104528284461[211] = 0;
   out_2943843104528284461[212] = 0;
   out_2943843104528284461[213] = 0;
   out_2943843104528284461[214] = 0;
   out_2943843104528284461[215] = 0;
   out_2943843104528284461[216] = 0;
   out_2943843104528284461[217] = 0;
   out_2943843104528284461[218] = 0;
   out_2943843104528284461[219] = 0;
   out_2943843104528284461[220] = 0;
   out_2943843104528284461[221] = 0;
   out_2943843104528284461[222] = 0;
   out_2943843104528284461[223] = 0;
   out_2943843104528284461[224] = 0;
   out_2943843104528284461[225] = 0;
   out_2943843104528284461[226] = 0;
   out_2943843104528284461[227] = 0;
   out_2943843104528284461[228] = 1;
   out_2943843104528284461[229] = 0;
   out_2943843104528284461[230] = 0;
   out_2943843104528284461[231] = 0;
   out_2943843104528284461[232] = 0;
   out_2943843104528284461[233] = 0;
   out_2943843104528284461[234] = 0;
   out_2943843104528284461[235] = 0;
   out_2943843104528284461[236] = 0;
   out_2943843104528284461[237] = 0;
   out_2943843104528284461[238] = 0;
   out_2943843104528284461[239] = 0;
   out_2943843104528284461[240] = 0;
   out_2943843104528284461[241] = 0;
   out_2943843104528284461[242] = 0;
   out_2943843104528284461[243] = 0;
   out_2943843104528284461[244] = 0;
   out_2943843104528284461[245] = 0;
   out_2943843104528284461[246] = 0;
   out_2943843104528284461[247] = 1;
   out_2943843104528284461[248] = 0;
   out_2943843104528284461[249] = 0;
   out_2943843104528284461[250] = 0;
   out_2943843104528284461[251] = 0;
   out_2943843104528284461[252] = 0;
   out_2943843104528284461[253] = 0;
   out_2943843104528284461[254] = 0;
   out_2943843104528284461[255] = 0;
   out_2943843104528284461[256] = 0;
   out_2943843104528284461[257] = 0;
   out_2943843104528284461[258] = 0;
   out_2943843104528284461[259] = 0;
   out_2943843104528284461[260] = 0;
   out_2943843104528284461[261] = 0;
   out_2943843104528284461[262] = 0;
   out_2943843104528284461[263] = 0;
   out_2943843104528284461[264] = 0;
   out_2943843104528284461[265] = 0;
   out_2943843104528284461[266] = 1;
   out_2943843104528284461[267] = 0;
   out_2943843104528284461[268] = 0;
   out_2943843104528284461[269] = 0;
   out_2943843104528284461[270] = 0;
   out_2943843104528284461[271] = 0;
   out_2943843104528284461[272] = 0;
   out_2943843104528284461[273] = 0;
   out_2943843104528284461[274] = 0;
   out_2943843104528284461[275] = 0;
   out_2943843104528284461[276] = 0;
   out_2943843104528284461[277] = 0;
   out_2943843104528284461[278] = 0;
   out_2943843104528284461[279] = 0;
   out_2943843104528284461[280] = 0;
   out_2943843104528284461[281] = 0;
   out_2943843104528284461[282] = 0;
   out_2943843104528284461[283] = 0;
   out_2943843104528284461[284] = 0;
   out_2943843104528284461[285] = 1;
   out_2943843104528284461[286] = 0;
   out_2943843104528284461[287] = 0;
   out_2943843104528284461[288] = 0;
   out_2943843104528284461[289] = 0;
   out_2943843104528284461[290] = 0;
   out_2943843104528284461[291] = 0;
   out_2943843104528284461[292] = 0;
   out_2943843104528284461[293] = 0;
   out_2943843104528284461[294] = 0;
   out_2943843104528284461[295] = 0;
   out_2943843104528284461[296] = 0;
   out_2943843104528284461[297] = 0;
   out_2943843104528284461[298] = 0;
   out_2943843104528284461[299] = 0;
   out_2943843104528284461[300] = 0;
   out_2943843104528284461[301] = 0;
   out_2943843104528284461[302] = 0;
   out_2943843104528284461[303] = 0;
   out_2943843104528284461[304] = 1;
   out_2943843104528284461[305] = 0;
   out_2943843104528284461[306] = 0;
   out_2943843104528284461[307] = 0;
   out_2943843104528284461[308] = 0;
   out_2943843104528284461[309] = 0;
   out_2943843104528284461[310] = 0;
   out_2943843104528284461[311] = 0;
   out_2943843104528284461[312] = 0;
   out_2943843104528284461[313] = 0;
   out_2943843104528284461[314] = 0;
   out_2943843104528284461[315] = 0;
   out_2943843104528284461[316] = 0;
   out_2943843104528284461[317] = 0;
   out_2943843104528284461[318] = 0;
   out_2943843104528284461[319] = 0;
   out_2943843104528284461[320] = 0;
   out_2943843104528284461[321] = 0;
   out_2943843104528284461[322] = 0;
   out_2943843104528284461[323] = 1;
}
void h_4(double *state, double *unused, double *out_7392043206358300323) {
   out_7392043206358300323[0] = state[6] + state[9];
   out_7392043206358300323[1] = state[7] + state[10];
   out_7392043206358300323[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_5488683682728833941) {
   out_5488683682728833941[0] = 0;
   out_5488683682728833941[1] = 0;
   out_5488683682728833941[2] = 0;
   out_5488683682728833941[3] = 0;
   out_5488683682728833941[4] = 0;
   out_5488683682728833941[5] = 0;
   out_5488683682728833941[6] = 1;
   out_5488683682728833941[7] = 0;
   out_5488683682728833941[8] = 0;
   out_5488683682728833941[9] = 1;
   out_5488683682728833941[10] = 0;
   out_5488683682728833941[11] = 0;
   out_5488683682728833941[12] = 0;
   out_5488683682728833941[13] = 0;
   out_5488683682728833941[14] = 0;
   out_5488683682728833941[15] = 0;
   out_5488683682728833941[16] = 0;
   out_5488683682728833941[17] = 0;
   out_5488683682728833941[18] = 0;
   out_5488683682728833941[19] = 0;
   out_5488683682728833941[20] = 0;
   out_5488683682728833941[21] = 0;
   out_5488683682728833941[22] = 0;
   out_5488683682728833941[23] = 0;
   out_5488683682728833941[24] = 0;
   out_5488683682728833941[25] = 1;
   out_5488683682728833941[26] = 0;
   out_5488683682728833941[27] = 0;
   out_5488683682728833941[28] = 1;
   out_5488683682728833941[29] = 0;
   out_5488683682728833941[30] = 0;
   out_5488683682728833941[31] = 0;
   out_5488683682728833941[32] = 0;
   out_5488683682728833941[33] = 0;
   out_5488683682728833941[34] = 0;
   out_5488683682728833941[35] = 0;
   out_5488683682728833941[36] = 0;
   out_5488683682728833941[37] = 0;
   out_5488683682728833941[38] = 0;
   out_5488683682728833941[39] = 0;
   out_5488683682728833941[40] = 0;
   out_5488683682728833941[41] = 0;
   out_5488683682728833941[42] = 0;
   out_5488683682728833941[43] = 0;
   out_5488683682728833941[44] = 1;
   out_5488683682728833941[45] = 0;
   out_5488683682728833941[46] = 0;
   out_5488683682728833941[47] = 1;
   out_5488683682728833941[48] = 0;
   out_5488683682728833941[49] = 0;
   out_5488683682728833941[50] = 0;
   out_5488683682728833941[51] = 0;
   out_5488683682728833941[52] = 0;
   out_5488683682728833941[53] = 0;
}
void h_10(double *state, double *unused, double *out_1893443682310766933) {
   out_1893443682310766933[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1893443682310766933[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1893443682310766933[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_4002633890361339640) {
   out_4002633890361339640[0] = 0;
   out_4002633890361339640[1] = 9.8100000000000005*cos(state[1]);
   out_4002633890361339640[2] = 0;
   out_4002633890361339640[3] = 0;
   out_4002633890361339640[4] = -state[8];
   out_4002633890361339640[5] = state[7];
   out_4002633890361339640[6] = 0;
   out_4002633890361339640[7] = state[5];
   out_4002633890361339640[8] = -state[4];
   out_4002633890361339640[9] = 0;
   out_4002633890361339640[10] = 0;
   out_4002633890361339640[11] = 0;
   out_4002633890361339640[12] = 1;
   out_4002633890361339640[13] = 0;
   out_4002633890361339640[14] = 0;
   out_4002633890361339640[15] = 1;
   out_4002633890361339640[16] = 0;
   out_4002633890361339640[17] = 0;
   out_4002633890361339640[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_4002633890361339640[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_4002633890361339640[20] = 0;
   out_4002633890361339640[21] = state[8];
   out_4002633890361339640[22] = 0;
   out_4002633890361339640[23] = -state[6];
   out_4002633890361339640[24] = -state[5];
   out_4002633890361339640[25] = 0;
   out_4002633890361339640[26] = state[3];
   out_4002633890361339640[27] = 0;
   out_4002633890361339640[28] = 0;
   out_4002633890361339640[29] = 0;
   out_4002633890361339640[30] = 0;
   out_4002633890361339640[31] = 1;
   out_4002633890361339640[32] = 0;
   out_4002633890361339640[33] = 0;
   out_4002633890361339640[34] = 1;
   out_4002633890361339640[35] = 0;
   out_4002633890361339640[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_4002633890361339640[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_4002633890361339640[38] = 0;
   out_4002633890361339640[39] = -state[7];
   out_4002633890361339640[40] = state[6];
   out_4002633890361339640[41] = 0;
   out_4002633890361339640[42] = state[4];
   out_4002633890361339640[43] = -state[3];
   out_4002633890361339640[44] = 0;
   out_4002633890361339640[45] = 0;
   out_4002633890361339640[46] = 0;
   out_4002633890361339640[47] = 0;
   out_4002633890361339640[48] = 0;
   out_4002633890361339640[49] = 0;
   out_4002633890361339640[50] = 1;
   out_4002633890361339640[51] = 0;
   out_4002633890361339640[52] = 0;
   out_4002633890361339640[53] = 1;
}
void h_13(double *state, double *unused, double *out_950850480842812453) {
   out_950850480842812453[0] = state[3];
   out_950850480842812453[1] = state[4];
   out_950850480842812453[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8700957508061166742) {
   out_8700957508061166742[0] = 0;
   out_8700957508061166742[1] = 0;
   out_8700957508061166742[2] = 0;
   out_8700957508061166742[3] = 1;
   out_8700957508061166742[4] = 0;
   out_8700957508061166742[5] = 0;
   out_8700957508061166742[6] = 0;
   out_8700957508061166742[7] = 0;
   out_8700957508061166742[8] = 0;
   out_8700957508061166742[9] = 0;
   out_8700957508061166742[10] = 0;
   out_8700957508061166742[11] = 0;
   out_8700957508061166742[12] = 0;
   out_8700957508061166742[13] = 0;
   out_8700957508061166742[14] = 0;
   out_8700957508061166742[15] = 0;
   out_8700957508061166742[16] = 0;
   out_8700957508061166742[17] = 0;
   out_8700957508061166742[18] = 0;
   out_8700957508061166742[19] = 0;
   out_8700957508061166742[20] = 0;
   out_8700957508061166742[21] = 0;
   out_8700957508061166742[22] = 1;
   out_8700957508061166742[23] = 0;
   out_8700957508061166742[24] = 0;
   out_8700957508061166742[25] = 0;
   out_8700957508061166742[26] = 0;
   out_8700957508061166742[27] = 0;
   out_8700957508061166742[28] = 0;
   out_8700957508061166742[29] = 0;
   out_8700957508061166742[30] = 0;
   out_8700957508061166742[31] = 0;
   out_8700957508061166742[32] = 0;
   out_8700957508061166742[33] = 0;
   out_8700957508061166742[34] = 0;
   out_8700957508061166742[35] = 0;
   out_8700957508061166742[36] = 0;
   out_8700957508061166742[37] = 0;
   out_8700957508061166742[38] = 0;
   out_8700957508061166742[39] = 0;
   out_8700957508061166742[40] = 0;
   out_8700957508061166742[41] = 1;
   out_8700957508061166742[42] = 0;
   out_8700957508061166742[43] = 0;
   out_8700957508061166742[44] = 0;
   out_8700957508061166742[45] = 0;
   out_8700957508061166742[46] = 0;
   out_8700957508061166742[47] = 0;
   out_8700957508061166742[48] = 0;
   out_8700957508061166742[49] = 0;
   out_8700957508061166742[50] = 0;
   out_8700957508061166742[51] = 0;
   out_8700957508061166742[52] = 0;
   out_8700957508061166742[53] = 0;
}
void h_14(double *state, double *unused, double *out_2845286380404369143) {
   out_2845286380404369143[0] = state[6];
   out_2845286380404369143[1] = state[7];
   out_2845286380404369143[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2405895250433461645) {
   out_2405895250433461645[0] = 0;
   out_2405895250433461645[1] = 0;
   out_2405895250433461645[2] = 0;
   out_2405895250433461645[3] = 0;
   out_2405895250433461645[4] = 0;
   out_2405895250433461645[5] = 0;
   out_2405895250433461645[6] = 1;
   out_2405895250433461645[7] = 0;
   out_2405895250433461645[8] = 0;
   out_2405895250433461645[9] = 0;
   out_2405895250433461645[10] = 0;
   out_2405895250433461645[11] = 0;
   out_2405895250433461645[12] = 0;
   out_2405895250433461645[13] = 0;
   out_2405895250433461645[14] = 0;
   out_2405895250433461645[15] = 0;
   out_2405895250433461645[16] = 0;
   out_2405895250433461645[17] = 0;
   out_2405895250433461645[18] = 0;
   out_2405895250433461645[19] = 0;
   out_2405895250433461645[20] = 0;
   out_2405895250433461645[21] = 0;
   out_2405895250433461645[22] = 0;
   out_2405895250433461645[23] = 0;
   out_2405895250433461645[24] = 0;
   out_2405895250433461645[25] = 1;
   out_2405895250433461645[26] = 0;
   out_2405895250433461645[27] = 0;
   out_2405895250433461645[28] = 0;
   out_2405895250433461645[29] = 0;
   out_2405895250433461645[30] = 0;
   out_2405895250433461645[31] = 0;
   out_2405895250433461645[32] = 0;
   out_2405895250433461645[33] = 0;
   out_2405895250433461645[34] = 0;
   out_2405895250433461645[35] = 0;
   out_2405895250433461645[36] = 0;
   out_2405895250433461645[37] = 0;
   out_2405895250433461645[38] = 0;
   out_2405895250433461645[39] = 0;
   out_2405895250433461645[40] = 0;
   out_2405895250433461645[41] = 0;
   out_2405895250433461645[42] = 0;
   out_2405895250433461645[43] = 0;
   out_2405895250433461645[44] = 1;
   out_2405895250433461645[45] = 0;
   out_2405895250433461645[46] = 0;
   out_2405895250433461645[47] = 0;
   out_2405895250433461645[48] = 0;
   out_2405895250433461645[49] = 0;
   out_2405895250433461645[50] = 0;
   out_2405895250433461645[51] = 0;
   out_2405895250433461645[52] = 0;
   out_2405895250433461645[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_2235485331980533535) {
  err_fun(nom_x, delta_x, out_2235485331980533535);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6263710841243713274) {
  inv_err_fun(nom_x, true_x, out_6263710841243713274);
}
void pose_H_mod_fun(double *state, double *out_874056645799517577) {
  H_mod_fun(state, out_874056645799517577);
}
void pose_f_fun(double *state, double dt, double *out_7518635824214998963) {
  f_fun(state,  dt, out_7518635824214998963);
}
void pose_F_fun(double *state, double dt, double *out_2943843104528284461) {
  F_fun(state,  dt, out_2943843104528284461);
}
void pose_h_4(double *state, double *unused, double *out_7392043206358300323) {
  h_4(state, unused, out_7392043206358300323);
}
void pose_H_4(double *state, double *unused, double *out_5488683682728833941) {
  H_4(state, unused, out_5488683682728833941);
}
void pose_h_10(double *state, double *unused, double *out_1893443682310766933) {
  h_10(state, unused, out_1893443682310766933);
}
void pose_H_10(double *state, double *unused, double *out_4002633890361339640) {
  H_10(state, unused, out_4002633890361339640);
}
void pose_h_13(double *state, double *unused, double *out_950850480842812453) {
  h_13(state, unused, out_950850480842812453);
}
void pose_H_13(double *state, double *unused, double *out_8700957508061166742) {
  H_13(state, unused, out_8700957508061166742);
}
void pose_h_14(double *state, double *unused, double *out_2845286380404369143) {
  h_14(state, unused, out_2845286380404369143);
}
void pose_H_14(double *state, double *unused, double *out_2405895250433461645) {
  H_14(state, unused, out_2405895250433461645);
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
