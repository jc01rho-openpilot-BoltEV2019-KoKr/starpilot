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
void err_fun(double *nom_x, double *delta_x, double *out_8940459122146932400) {
   out_8940459122146932400[0] = delta_x[0] + nom_x[0];
   out_8940459122146932400[1] = delta_x[1] + nom_x[1];
   out_8940459122146932400[2] = delta_x[2] + nom_x[2];
   out_8940459122146932400[3] = delta_x[3] + nom_x[3];
   out_8940459122146932400[4] = delta_x[4] + nom_x[4];
   out_8940459122146932400[5] = delta_x[5] + nom_x[5];
   out_8940459122146932400[6] = delta_x[6] + nom_x[6];
   out_8940459122146932400[7] = delta_x[7] + nom_x[7];
   out_8940459122146932400[8] = delta_x[8] + nom_x[8];
   out_8940459122146932400[9] = delta_x[9] + nom_x[9];
   out_8940459122146932400[10] = delta_x[10] + nom_x[10];
   out_8940459122146932400[11] = delta_x[11] + nom_x[11];
   out_8940459122146932400[12] = delta_x[12] + nom_x[12];
   out_8940459122146932400[13] = delta_x[13] + nom_x[13];
   out_8940459122146932400[14] = delta_x[14] + nom_x[14];
   out_8940459122146932400[15] = delta_x[15] + nom_x[15];
   out_8940459122146932400[16] = delta_x[16] + nom_x[16];
   out_8940459122146932400[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3384987028755125218) {
   out_3384987028755125218[0] = -nom_x[0] + true_x[0];
   out_3384987028755125218[1] = -nom_x[1] + true_x[1];
   out_3384987028755125218[2] = -nom_x[2] + true_x[2];
   out_3384987028755125218[3] = -nom_x[3] + true_x[3];
   out_3384987028755125218[4] = -nom_x[4] + true_x[4];
   out_3384987028755125218[5] = -nom_x[5] + true_x[5];
   out_3384987028755125218[6] = -nom_x[6] + true_x[6];
   out_3384987028755125218[7] = -nom_x[7] + true_x[7];
   out_3384987028755125218[8] = -nom_x[8] + true_x[8];
   out_3384987028755125218[9] = -nom_x[9] + true_x[9];
   out_3384987028755125218[10] = -nom_x[10] + true_x[10];
   out_3384987028755125218[11] = -nom_x[11] + true_x[11];
   out_3384987028755125218[12] = -nom_x[12] + true_x[12];
   out_3384987028755125218[13] = -nom_x[13] + true_x[13];
   out_3384987028755125218[14] = -nom_x[14] + true_x[14];
   out_3384987028755125218[15] = -nom_x[15] + true_x[15];
   out_3384987028755125218[16] = -nom_x[16] + true_x[16];
   out_3384987028755125218[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5245124330854285834) {
   out_5245124330854285834[0] = 1.0;
   out_5245124330854285834[1] = 0.0;
   out_5245124330854285834[2] = 0.0;
   out_5245124330854285834[3] = 0.0;
   out_5245124330854285834[4] = 0.0;
   out_5245124330854285834[5] = 0.0;
   out_5245124330854285834[6] = 0.0;
   out_5245124330854285834[7] = 0.0;
   out_5245124330854285834[8] = 0.0;
   out_5245124330854285834[9] = 0.0;
   out_5245124330854285834[10] = 0.0;
   out_5245124330854285834[11] = 0.0;
   out_5245124330854285834[12] = 0.0;
   out_5245124330854285834[13] = 0.0;
   out_5245124330854285834[14] = 0.0;
   out_5245124330854285834[15] = 0.0;
   out_5245124330854285834[16] = 0.0;
   out_5245124330854285834[17] = 0.0;
   out_5245124330854285834[18] = 0.0;
   out_5245124330854285834[19] = 1.0;
   out_5245124330854285834[20] = 0.0;
   out_5245124330854285834[21] = 0.0;
   out_5245124330854285834[22] = 0.0;
   out_5245124330854285834[23] = 0.0;
   out_5245124330854285834[24] = 0.0;
   out_5245124330854285834[25] = 0.0;
   out_5245124330854285834[26] = 0.0;
   out_5245124330854285834[27] = 0.0;
   out_5245124330854285834[28] = 0.0;
   out_5245124330854285834[29] = 0.0;
   out_5245124330854285834[30] = 0.0;
   out_5245124330854285834[31] = 0.0;
   out_5245124330854285834[32] = 0.0;
   out_5245124330854285834[33] = 0.0;
   out_5245124330854285834[34] = 0.0;
   out_5245124330854285834[35] = 0.0;
   out_5245124330854285834[36] = 0.0;
   out_5245124330854285834[37] = 0.0;
   out_5245124330854285834[38] = 1.0;
   out_5245124330854285834[39] = 0.0;
   out_5245124330854285834[40] = 0.0;
   out_5245124330854285834[41] = 0.0;
   out_5245124330854285834[42] = 0.0;
   out_5245124330854285834[43] = 0.0;
   out_5245124330854285834[44] = 0.0;
   out_5245124330854285834[45] = 0.0;
   out_5245124330854285834[46] = 0.0;
   out_5245124330854285834[47] = 0.0;
   out_5245124330854285834[48] = 0.0;
   out_5245124330854285834[49] = 0.0;
   out_5245124330854285834[50] = 0.0;
   out_5245124330854285834[51] = 0.0;
   out_5245124330854285834[52] = 0.0;
   out_5245124330854285834[53] = 0.0;
   out_5245124330854285834[54] = 0.0;
   out_5245124330854285834[55] = 0.0;
   out_5245124330854285834[56] = 0.0;
   out_5245124330854285834[57] = 1.0;
   out_5245124330854285834[58] = 0.0;
   out_5245124330854285834[59] = 0.0;
   out_5245124330854285834[60] = 0.0;
   out_5245124330854285834[61] = 0.0;
   out_5245124330854285834[62] = 0.0;
   out_5245124330854285834[63] = 0.0;
   out_5245124330854285834[64] = 0.0;
   out_5245124330854285834[65] = 0.0;
   out_5245124330854285834[66] = 0.0;
   out_5245124330854285834[67] = 0.0;
   out_5245124330854285834[68] = 0.0;
   out_5245124330854285834[69] = 0.0;
   out_5245124330854285834[70] = 0.0;
   out_5245124330854285834[71] = 0.0;
   out_5245124330854285834[72] = 0.0;
   out_5245124330854285834[73] = 0.0;
   out_5245124330854285834[74] = 0.0;
   out_5245124330854285834[75] = 0.0;
   out_5245124330854285834[76] = 1.0;
   out_5245124330854285834[77] = 0.0;
   out_5245124330854285834[78] = 0.0;
   out_5245124330854285834[79] = 0.0;
   out_5245124330854285834[80] = 0.0;
   out_5245124330854285834[81] = 0.0;
   out_5245124330854285834[82] = 0.0;
   out_5245124330854285834[83] = 0.0;
   out_5245124330854285834[84] = 0.0;
   out_5245124330854285834[85] = 0.0;
   out_5245124330854285834[86] = 0.0;
   out_5245124330854285834[87] = 0.0;
   out_5245124330854285834[88] = 0.0;
   out_5245124330854285834[89] = 0.0;
   out_5245124330854285834[90] = 0.0;
   out_5245124330854285834[91] = 0.0;
   out_5245124330854285834[92] = 0.0;
   out_5245124330854285834[93] = 0.0;
   out_5245124330854285834[94] = 0.0;
   out_5245124330854285834[95] = 1.0;
   out_5245124330854285834[96] = 0.0;
   out_5245124330854285834[97] = 0.0;
   out_5245124330854285834[98] = 0.0;
   out_5245124330854285834[99] = 0.0;
   out_5245124330854285834[100] = 0.0;
   out_5245124330854285834[101] = 0.0;
   out_5245124330854285834[102] = 0.0;
   out_5245124330854285834[103] = 0.0;
   out_5245124330854285834[104] = 0.0;
   out_5245124330854285834[105] = 0.0;
   out_5245124330854285834[106] = 0.0;
   out_5245124330854285834[107] = 0.0;
   out_5245124330854285834[108] = 0.0;
   out_5245124330854285834[109] = 0.0;
   out_5245124330854285834[110] = 0.0;
   out_5245124330854285834[111] = 0.0;
   out_5245124330854285834[112] = 0.0;
   out_5245124330854285834[113] = 0.0;
   out_5245124330854285834[114] = 1.0;
   out_5245124330854285834[115] = 0.0;
   out_5245124330854285834[116] = 0.0;
   out_5245124330854285834[117] = 0.0;
   out_5245124330854285834[118] = 0.0;
   out_5245124330854285834[119] = 0.0;
   out_5245124330854285834[120] = 0.0;
   out_5245124330854285834[121] = 0.0;
   out_5245124330854285834[122] = 0.0;
   out_5245124330854285834[123] = 0.0;
   out_5245124330854285834[124] = 0.0;
   out_5245124330854285834[125] = 0.0;
   out_5245124330854285834[126] = 0.0;
   out_5245124330854285834[127] = 0.0;
   out_5245124330854285834[128] = 0.0;
   out_5245124330854285834[129] = 0.0;
   out_5245124330854285834[130] = 0.0;
   out_5245124330854285834[131] = 0.0;
   out_5245124330854285834[132] = 0.0;
   out_5245124330854285834[133] = 1.0;
   out_5245124330854285834[134] = 0.0;
   out_5245124330854285834[135] = 0.0;
   out_5245124330854285834[136] = 0.0;
   out_5245124330854285834[137] = 0.0;
   out_5245124330854285834[138] = 0.0;
   out_5245124330854285834[139] = 0.0;
   out_5245124330854285834[140] = 0.0;
   out_5245124330854285834[141] = 0.0;
   out_5245124330854285834[142] = 0.0;
   out_5245124330854285834[143] = 0.0;
   out_5245124330854285834[144] = 0.0;
   out_5245124330854285834[145] = 0.0;
   out_5245124330854285834[146] = 0.0;
   out_5245124330854285834[147] = 0.0;
   out_5245124330854285834[148] = 0.0;
   out_5245124330854285834[149] = 0.0;
   out_5245124330854285834[150] = 0.0;
   out_5245124330854285834[151] = 0.0;
   out_5245124330854285834[152] = 1.0;
   out_5245124330854285834[153] = 0.0;
   out_5245124330854285834[154] = 0.0;
   out_5245124330854285834[155] = 0.0;
   out_5245124330854285834[156] = 0.0;
   out_5245124330854285834[157] = 0.0;
   out_5245124330854285834[158] = 0.0;
   out_5245124330854285834[159] = 0.0;
   out_5245124330854285834[160] = 0.0;
   out_5245124330854285834[161] = 0.0;
   out_5245124330854285834[162] = 0.0;
   out_5245124330854285834[163] = 0.0;
   out_5245124330854285834[164] = 0.0;
   out_5245124330854285834[165] = 0.0;
   out_5245124330854285834[166] = 0.0;
   out_5245124330854285834[167] = 0.0;
   out_5245124330854285834[168] = 0.0;
   out_5245124330854285834[169] = 0.0;
   out_5245124330854285834[170] = 0.0;
   out_5245124330854285834[171] = 1.0;
   out_5245124330854285834[172] = 0.0;
   out_5245124330854285834[173] = 0.0;
   out_5245124330854285834[174] = 0.0;
   out_5245124330854285834[175] = 0.0;
   out_5245124330854285834[176] = 0.0;
   out_5245124330854285834[177] = 0.0;
   out_5245124330854285834[178] = 0.0;
   out_5245124330854285834[179] = 0.0;
   out_5245124330854285834[180] = 0.0;
   out_5245124330854285834[181] = 0.0;
   out_5245124330854285834[182] = 0.0;
   out_5245124330854285834[183] = 0.0;
   out_5245124330854285834[184] = 0.0;
   out_5245124330854285834[185] = 0.0;
   out_5245124330854285834[186] = 0.0;
   out_5245124330854285834[187] = 0.0;
   out_5245124330854285834[188] = 0.0;
   out_5245124330854285834[189] = 0.0;
   out_5245124330854285834[190] = 1.0;
   out_5245124330854285834[191] = 0.0;
   out_5245124330854285834[192] = 0.0;
   out_5245124330854285834[193] = 0.0;
   out_5245124330854285834[194] = 0.0;
   out_5245124330854285834[195] = 0.0;
   out_5245124330854285834[196] = 0.0;
   out_5245124330854285834[197] = 0.0;
   out_5245124330854285834[198] = 0.0;
   out_5245124330854285834[199] = 0.0;
   out_5245124330854285834[200] = 0.0;
   out_5245124330854285834[201] = 0.0;
   out_5245124330854285834[202] = 0.0;
   out_5245124330854285834[203] = 0.0;
   out_5245124330854285834[204] = 0.0;
   out_5245124330854285834[205] = 0.0;
   out_5245124330854285834[206] = 0.0;
   out_5245124330854285834[207] = 0.0;
   out_5245124330854285834[208] = 0.0;
   out_5245124330854285834[209] = 1.0;
   out_5245124330854285834[210] = 0.0;
   out_5245124330854285834[211] = 0.0;
   out_5245124330854285834[212] = 0.0;
   out_5245124330854285834[213] = 0.0;
   out_5245124330854285834[214] = 0.0;
   out_5245124330854285834[215] = 0.0;
   out_5245124330854285834[216] = 0.0;
   out_5245124330854285834[217] = 0.0;
   out_5245124330854285834[218] = 0.0;
   out_5245124330854285834[219] = 0.0;
   out_5245124330854285834[220] = 0.0;
   out_5245124330854285834[221] = 0.0;
   out_5245124330854285834[222] = 0.0;
   out_5245124330854285834[223] = 0.0;
   out_5245124330854285834[224] = 0.0;
   out_5245124330854285834[225] = 0.0;
   out_5245124330854285834[226] = 0.0;
   out_5245124330854285834[227] = 0.0;
   out_5245124330854285834[228] = 1.0;
   out_5245124330854285834[229] = 0.0;
   out_5245124330854285834[230] = 0.0;
   out_5245124330854285834[231] = 0.0;
   out_5245124330854285834[232] = 0.0;
   out_5245124330854285834[233] = 0.0;
   out_5245124330854285834[234] = 0.0;
   out_5245124330854285834[235] = 0.0;
   out_5245124330854285834[236] = 0.0;
   out_5245124330854285834[237] = 0.0;
   out_5245124330854285834[238] = 0.0;
   out_5245124330854285834[239] = 0.0;
   out_5245124330854285834[240] = 0.0;
   out_5245124330854285834[241] = 0.0;
   out_5245124330854285834[242] = 0.0;
   out_5245124330854285834[243] = 0.0;
   out_5245124330854285834[244] = 0.0;
   out_5245124330854285834[245] = 0.0;
   out_5245124330854285834[246] = 0.0;
   out_5245124330854285834[247] = 1.0;
   out_5245124330854285834[248] = 0.0;
   out_5245124330854285834[249] = 0.0;
   out_5245124330854285834[250] = 0.0;
   out_5245124330854285834[251] = 0.0;
   out_5245124330854285834[252] = 0.0;
   out_5245124330854285834[253] = 0.0;
   out_5245124330854285834[254] = 0.0;
   out_5245124330854285834[255] = 0.0;
   out_5245124330854285834[256] = 0.0;
   out_5245124330854285834[257] = 0.0;
   out_5245124330854285834[258] = 0.0;
   out_5245124330854285834[259] = 0.0;
   out_5245124330854285834[260] = 0.0;
   out_5245124330854285834[261] = 0.0;
   out_5245124330854285834[262] = 0.0;
   out_5245124330854285834[263] = 0.0;
   out_5245124330854285834[264] = 0.0;
   out_5245124330854285834[265] = 0.0;
   out_5245124330854285834[266] = 1.0;
   out_5245124330854285834[267] = 0.0;
   out_5245124330854285834[268] = 0.0;
   out_5245124330854285834[269] = 0.0;
   out_5245124330854285834[270] = 0.0;
   out_5245124330854285834[271] = 0.0;
   out_5245124330854285834[272] = 0.0;
   out_5245124330854285834[273] = 0.0;
   out_5245124330854285834[274] = 0.0;
   out_5245124330854285834[275] = 0.0;
   out_5245124330854285834[276] = 0.0;
   out_5245124330854285834[277] = 0.0;
   out_5245124330854285834[278] = 0.0;
   out_5245124330854285834[279] = 0.0;
   out_5245124330854285834[280] = 0.0;
   out_5245124330854285834[281] = 0.0;
   out_5245124330854285834[282] = 0.0;
   out_5245124330854285834[283] = 0.0;
   out_5245124330854285834[284] = 0.0;
   out_5245124330854285834[285] = 1.0;
   out_5245124330854285834[286] = 0.0;
   out_5245124330854285834[287] = 0.0;
   out_5245124330854285834[288] = 0.0;
   out_5245124330854285834[289] = 0.0;
   out_5245124330854285834[290] = 0.0;
   out_5245124330854285834[291] = 0.0;
   out_5245124330854285834[292] = 0.0;
   out_5245124330854285834[293] = 0.0;
   out_5245124330854285834[294] = 0.0;
   out_5245124330854285834[295] = 0.0;
   out_5245124330854285834[296] = 0.0;
   out_5245124330854285834[297] = 0.0;
   out_5245124330854285834[298] = 0.0;
   out_5245124330854285834[299] = 0.0;
   out_5245124330854285834[300] = 0.0;
   out_5245124330854285834[301] = 0.0;
   out_5245124330854285834[302] = 0.0;
   out_5245124330854285834[303] = 0.0;
   out_5245124330854285834[304] = 1.0;
   out_5245124330854285834[305] = 0.0;
   out_5245124330854285834[306] = 0.0;
   out_5245124330854285834[307] = 0.0;
   out_5245124330854285834[308] = 0.0;
   out_5245124330854285834[309] = 0.0;
   out_5245124330854285834[310] = 0.0;
   out_5245124330854285834[311] = 0.0;
   out_5245124330854285834[312] = 0.0;
   out_5245124330854285834[313] = 0.0;
   out_5245124330854285834[314] = 0.0;
   out_5245124330854285834[315] = 0.0;
   out_5245124330854285834[316] = 0.0;
   out_5245124330854285834[317] = 0.0;
   out_5245124330854285834[318] = 0.0;
   out_5245124330854285834[319] = 0.0;
   out_5245124330854285834[320] = 0.0;
   out_5245124330854285834[321] = 0.0;
   out_5245124330854285834[322] = 0.0;
   out_5245124330854285834[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_6830900184565569763) {
   out_6830900184565569763[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_6830900184565569763[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_6830900184565569763[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_6830900184565569763[3] = dt*state[12] + state[3];
   out_6830900184565569763[4] = dt*state[13] + state[4];
   out_6830900184565569763[5] = dt*state[14] + state[5];
   out_6830900184565569763[6] = state[6];
   out_6830900184565569763[7] = state[7];
   out_6830900184565569763[8] = state[8];
   out_6830900184565569763[9] = state[9];
   out_6830900184565569763[10] = state[10];
   out_6830900184565569763[11] = state[11];
   out_6830900184565569763[12] = state[12];
   out_6830900184565569763[13] = state[13];
   out_6830900184565569763[14] = state[14];
   out_6830900184565569763[15] = state[15];
   out_6830900184565569763[16] = state[16];
   out_6830900184565569763[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5118094281500581129) {
   out_5118094281500581129[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5118094281500581129[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5118094281500581129[2] = 0;
   out_5118094281500581129[3] = 0;
   out_5118094281500581129[4] = 0;
   out_5118094281500581129[5] = 0;
   out_5118094281500581129[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5118094281500581129[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5118094281500581129[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5118094281500581129[9] = 0;
   out_5118094281500581129[10] = 0;
   out_5118094281500581129[11] = 0;
   out_5118094281500581129[12] = 0;
   out_5118094281500581129[13] = 0;
   out_5118094281500581129[14] = 0;
   out_5118094281500581129[15] = 0;
   out_5118094281500581129[16] = 0;
   out_5118094281500581129[17] = 0;
   out_5118094281500581129[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5118094281500581129[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5118094281500581129[20] = 0;
   out_5118094281500581129[21] = 0;
   out_5118094281500581129[22] = 0;
   out_5118094281500581129[23] = 0;
   out_5118094281500581129[24] = 0;
   out_5118094281500581129[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5118094281500581129[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5118094281500581129[27] = 0;
   out_5118094281500581129[28] = 0;
   out_5118094281500581129[29] = 0;
   out_5118094281500581129[30] = 0;
   out_5118094281500581129[31] = 0;
   out_5118094281500581129[32] = 0;
   out_5118094281500581129[33] = 0;
   out_5118094281500581129[34] = 0;
   out_5118094281500581129[35] = 0;
   out_5118094281500581129[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5118094281500581129[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5118094281500581129[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5118094281500581129[39] = 0;
   out_5118094281500581129[40] = 0;
   out_5118094281500581129[41] = 0;
   out_5118094281500581129[42] = 0;
   out_5118094281500581129[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5118094281500581129[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5118094281500581129[45] = 0;
   out_5118094281500581129[46] = 0;
   out_5118094281500581129[47] = 0;
   out_5118094281500581129[48] = 0;
   out_5118094281500581129[49] = 0;
   out_5118094281500581129[50] = 0;
   out_5118094281500581129[51] = 0;
   out_5118094281500581129[52] = 0;
   out_5118094281500581129[53] = 0;
   out_5118094281500581129[54] = 0;
   out_5118094281500581129[55] = 0;
   out_5118094281500581129[56] = 0;
   out_5118094281500581129[57] = 1;
   out_5118094281500581129[58] = 0;
   out_5118094281500581129[59] = 0;
   out_5118094281500581129[60] = 0;
   out_5118094281500581129[61] = 0;
   out_5118094281500581129[62] = 0;
   out_5118094281500581129[63] = 0;
   out_5118094281500581129[64] = 0;
   out_5118094281500581129[65] = 0;
   out_5118094281500581129[66] = dt;
   out_5118094281500581129[67] = 0;
   out_5118094281500581129[68] = 0;
   out_5118094281500581129[69] = 0;
   out_5118094281500581129[70] = 0;
   out_5118094281500581129[71] = 0;
   out_5118094281500581129[72] = 0;
   out_5118094281500581129[73] = 0;
   out_5118094281500581129[74] = 0;
   out_5118094281500581129[75] = 0;
   out_5118094281500581129[76] = 1;
   out_5118094281500581129[77] = 0;
   out_5118094281500581129[78] = 0;
   out_5118094281500581129[79] = 0;
   out_5118094281500581129[80] = 0;
   out_5118094281500581129[81] = 0;
   out_5118094281500581129[82] = 0;
   out_5118094281500581129[83] = 0;
   out_5118094281500581129[84] = 0;
   out_5118094281500581129[85] = dt;
   out_5118094281500581129[86] = 0;
   out_5118094281500581129[87] = 0;
   out_5118094281500581129[88] = 0;
   out_5118094281500581129[89] = 0;
   out_5118094281500581129[90] = 0;
   out_5118094281500581129[91] = 0;
   out_5118094281500581129[92] = 0;
   out_5118094281500581129[93] = 0;
   out_5118094281500581129[94] = 0;
   out_5118094281500581129[95] = 1;
   out_5118094281500581129[96] = 0;
   out_5118094281500581129[97] = 0;
   out_5118094281500581129[98] = 0;
   out_5118094281500581129[99] = 0;
   out_5118094281500581129[100] = 0;
   out_5118094281500581129[101] = 0;
   out_5118094281500581129[102] = 0;
   out_5118094281500581129[103] = 0;
   out_5118094281500581129[104] = dt;
   out_5118094281500581129[105] = 0;
   out_5118094281500581129[106] = 0;
   out_5118094281500581129[107] = 0;
   out_5118094281500581129[108] = 0;
   out_5118094281500581129[109] = 0;
   out_5118094281500581129[110] = 0;
   out_5118094281500581129[111] = 0;
   out_5118094281500581129[112] = 0;
   out_5118094281500581129[113] = 0;
   out_5118094281500581129[114] = 1;
   out_5118094281500581129[115] = 0;
   out_5118094281500581129[116] = 0;
   out_5118094281500581129[117] = 0;
   out_5118094281500581129[118] = 0;
   out_5118094281500581129[119] = 0;
   out_5118094281500581129[120] = 0;
   out_5118094281500581129[121] = 0;
   out_5118094281500581129[122] = 0;
   out_5118094281500581129[123] = 0;
   out_5118094281500581129[124] = 0;
   out_5118094281500581129[125] = 0;
   out_5118094281500581129[126] = 0;
   out_5118094281500581129[127] = 0;
   out_5118094281500581129[128] = 0;
   out_5118094281500581129[129] = 0;
   out_5118094281500581129[130] = 0;
   out_5118094281500581129[131] = 0;
   out_5118094281500581129[132] = 0;
   out_5118094281500581129[133] = 1;
   out_5118094281500581129[134] = 0;
   out_5118094281500581129[135] = 0;
   out_5118094281500581129[136] = 0;
   out_5118094281500581129[137] = 0;
   out_5118094281500581129[138] = 0;
   out_5118094281500581129[139] = 0;
   out_5118094281500581129[140] = 0;
   out_5118094281500581129[141] = 0;
   out_5118094281500581129[142] = 0;
   out_5118094281500581129[143] = 0;
   out_5118094281500581129[144] = 0;
   out_5118094281500581129[145] = 0;
   out_5118094281500581129[146] = 0;
   out_5118094281500581129[147] = 0;
   out_5118094281500581129[148] = 0;
   out_5118094281500581129[149] = 0;
   out_5118094281500581129[150] = 0;
   out_5118094281500581129[151] = 0;
   out_5118094281500581129[152] = 1;
   out_5118094281500581129[153] = 0;
   out_5118094281500581129[154] = 0;
   out_5118094281500581129[155] = 0;
   out_5118094281500581129[156] = 0;
   out_5118094281500581129[157] = 0;
   out_5118094281500581129[158] = 0;
   out_5118094281500581129[159] = 0;
   out_5118094281500581129[160] = 0;
   out_5118094281500581129[161] = 0;
   out_5118094281500581129[162] = 0;
   out_5118094281500581129[163] = 0;
   out_5118094281500581129[164] = 0;
   out_5118094281500581129[165] = 0;
   out_5118094281500581129[166] = 0;
   out_5118094281500581129[167] = 0;
   out_5118094281500581129[168] = 0;
   out_5118094281500581129[169] = 0;
   out_5118094281500581129[170] = 0;
   out_5118094281500581129[171] = 1;
   out_5118094281500581129[172] = 0;
   out_5118094281500581129[173] = 0;
   out_5118094281500581129[174] = 0;
   out_5118094281500581129[175] = 0;
   out_5118094281500581129[176] = 0;
   out_5118094281500581129[177] = 0;
   out_5118094281500581129[178] = 0;
   out_5118094281500581129[179] = 0;
   out_5118094281500581129[180] = 0;
   out_5118094281500581129[181] = 0;
   out_5118094281500581129[182] = 0;
   out_5118094281500581129[183] = 0;
   out_5118094281500581129[184] = 0;
   out_5118094281500581129[185] = 0;
   out_5118094281500581129[186] = 0;
   out_5118094281500581129[187] = 0;
   out_5118094281500581129[188] = 0;
   out_5118094281500581129[189] = 0;
   out_5118094281500581129[190] = 1;
   out_5118094281500581129[191] = 0;
   out_5118094281500581129[192] = 0;
   out_5118094281500581129[193] = 0;
   out_5118094281500581129[194] = 0;
   out_5118094281500581129[195] = 0;
   out_5118094281500581129[196] = 0;
   out_5118094281500581129[197] = 0;
   out_5118094281500581129[198] = 0;
   out_5118094281500581129[199] = 0;
   out_5118094281500581129[200] = 0;
   out_5118094281500581129[201] = 0;
   out_5118094281500581129[202] = 0;
   out_5118094281500581129[203] = 0;
   out_5118094281500581129[204] = 0;
   out_5118094281500581129[205] = 0;
   out_5118094281500581129[206] = 0;
   out_5118094281500581129[207] = 0;
   out_5118094281500581129[208] = 0;
   out_5118094281500581129[209] = 1;
   out_5118094281500581129[210] = 0;
   out_5118094281500581129[211] = 0;
   out_5118094281500581129[212] = 0;
   out_5118094281500581129[213] = 0;
   out_5118094281500581129[214] = 0;
   out_5118094281500581129[215] = 0;
   out_5118094281500581129[216] = 0;
   out_5118094281500581129[217] = 0;
   out_5118094281500581129[218] = 0;
   out_5118094281500581129[219] = 0;
   out_5118094281500581129[220] = 0;
   out_5118094281500581129[221] = 0;
   out_5118094281500581129[222] = 0;
   out_5118094281500581129[223] = 0;
   out_5118094281500581129[224] = 0;
   out_5118094281500581129[225] = 0;
   out_5118094281500581129[226] = 0;
   out_5118094281500581129[227] = 0;
   out_5118094281500581129[228] = 1;
   out_5118094281500581129[229] = 0;
   out_5118094281500581129[230] = 0;
   out_5118094281500581129[231] = 0;
   out_5118094281500581129[232] = 0;
   out_5118094281500581129[233] = 0;
   out_5118094281500581129[234] = 0;
   out_5118094281500581129[235] = 0;
   out_5118094281500581129[236] = 0;
   out_5118094281500581129[237] = 0;
   out_5118094281500581129[238] = 0;
   out_5118094281500581129[239] = 0;
   out_5118094281500581129[240] = 0;
   out_5118094281500581129[241] = 0;
   out_5118094281500581129[242] = 0;
   out_5118094281500581129[243] = 0;
   out_5118094281500581129[244] = 0;
   out_5118094281500581129[245] = 0;
   out_5118094281500581129[246] = 0;
   out_5118094281500581129[247] = 1;
   out_5118094281500581129[248] = 0;
   out_5118094281500581129[249] = 0;
   out_5118094281500581129[250] = 0;
   out_5118094281500581129[251] = 0;
   out_5118094281500581129[252] = 0;
   out_5118094281500581129[253] = 0;
   out_5118094281500581129[254] = 0;
   out_5118094281500581129[255] = 0;
   out_5118094281500581129[256] = 0;
   out_5118094281500581129[257] = 0;
   out_5118094281500581129[258] = 0;
   out_5118094281500581129[259] = 0;
   out_5118094281500581129[260] = 0;
   out_5118094281500581129[261] = 0;
   out_5118094281500581129[262] = 0;
   out_5118094281500581129[263] = 0;
   out_5118094281500581129[264] = 0;
   out_5118094281500581129[265] = 0;
   out_5118094281500581129[266] = 1;
   out_5118094281500581129[267] = 0;
   out_5118094281500581129[268] = 0;
   out_5118094281500581129[269] = 0;
   out_5118094281500581129[270] = 0;
   out_5118094281500581129[271] = 0;
   out_5118094281500581129[272] = 0;
   out_5118094281500581129[273] = 0;
   out_5118094281500581129[274] = 0;
   out_5118094281500581129[275] = 0;
   out_5118094281500581129[276] = 0;
   out_5118094281500581129[277] = 0;
   out_5118094281500581129[278] = 0;
   out_5118094281500581129[279] = 0;
   out_5118094281500581129[280] = 0;
   out_5118094281500581129[281] = 0;
   out_5118094281500581129[282] = 0;
   out_5118094281500581129[283] = 0;
   out_5118094281500581129[284] = 0;
   out_5118094281500581129[285] = 1;
   out_5118094281500581129[286] = 0;
   out_5118094281500581129[287] = 0;
   out_5118094281500581129[288] = 0;
   out_5118094281500581129[289] = 0;
   out_5118094281500581129[290] = 0;
   out_5118094281500581129[291] = 0;
   out_5118094281500581129[292] = 0;
   out_5118094281500581129[293] = 0;
   out_5118094281500581129[294] = 0;
   out_5118094281500581129[295] = 0;
   out_5118094281500581129[296] = 0;
   out_5118094281500581129[297] = 0;
   out_5118094281500581129[298] = 0;
   out_5118094281500581129[299] = 0;
   out_5118094281500581129[300] = 0;
   out_5118094281500581129[301] = 0;
   out_5118094281500581129[302] = 0;
   out_5118094281500581129[303] = 0;
   out_5118094281500581129[304] = 1;
   out_5118094281500581129[305] = 0;
   out_5118094281500581129[306] = 0;
   out_5118094281500581129[307] = 0;
   out_5118094281500581129[308] = 0;
   out_5118094281500581129[309] = 0;
   out_5118094281500581129[310] = 0;
   out_5118094281500581129[311] = 0;
   out_5118094281500581129[312] = 0;
   out_5118094281500581129[313] = 0;
   out_5118094281500581129[314] = 0;
   out_5118094281500581129[315] = 0;
   out_5118094281500581129[316] = 0;
   out_5118094281500581129[317] = 0;
   out_5118094281500581129[318] = 0;
   out_5118094281500581129[319] = 0;
   out_5118094281500581129[320] = 0;
   out_5118094281500581129[321] = 0;
   out_5118094281500581129[322] = 0;
   out_5118094281500581129[323] = 1;
}
void h_4(double *state, double *unused, double *out_4935070827926002458) {
   out_4935070827926002458[0] = state[6] + state[9];
   out_4935070827926002458[1] = state[7] + state[10];
   out_4935070827926002458[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6443071812737183938) {
   out_6443071812737183938[0] = 0;
   out_6443071812737183938[1] = 0;
   out_6443071812737183938[2] = 0;
   out_6443071812737183938[3] = 0;
   out_6443071812737183938[4] = 0;
   out_6443071812737183938[5] = 0;
   out_6443071812737183938[6] = 1;
   out_6443071812737183938[7] = 0;
   out_6443071812737183938[8] = 0;
   out_6443071812737183938[9] = 1;
   out_6443071812737183938[10] = 0;
   out_6443071812737183938[11] = 0;
   out_6443071812737183938[12] = 0;
   out_6443071812737183938[13] = 0;
   out_6443071812737183938[14] = 0;
   out_6443071812737183938[15] = 0;
   out_6443071812737183938[16] = 0;
   out_6443071812737183938[17] = 0;
   out_6443071812737183938[18] = 0;
   out_6443071812737183938[19] = 0;
   out_6443071812737183938[20] = 0;
   out_6443071812737183938[21] = 0;
   out_6443071812737183938[22] = 0;
   out_6443071812737183938[23] = 0;
   out_6443071812737183938[24] = 0;
   out_6443071812737183938[25] = 1;
   out_6443071812737183938[26] = 0;
   out_6443071812737183938[27] = 0;
   out_6443071812737183938[28] = 1;
   out_6443071812737183938[29] = 0;
   out_6443071812737183938[30] = 0;
   out_6443071812737183938[31] = 0;
   out_6443071812737183938[32] = 0;
   out_6443071812737183938[33] = 0;
   out_6443071812737183938[34] = 0;
   out_6443071812737183938[35] = 0;
   out_6443071812737183938[36] = 0;
   out_6443071812737183938[37] = 0;
   out_6443071812737183938[38] = 0;
   out_6443071812737183938[39] = 0;
   out_6443071812737183938[40] = 0;
   out_6443071812737183938[41] = 0;
   out_6443071812737183938[42] = 0;
   out_6443071812737183938[43] = 0;
   out_6443071812737183938[44] = 1;
   out_6443071812737183938[45] = 0;
   out_6443071812737183938[46] = 0;
   out_6443071812737183938[47] = 1;
   out_6443071812737183938[48] = 0;
   out_6443071812737183938[49] = 0;
   out_6443071812737183938[50] = 0;
   out_6443071812737183938[51] = 0;
   out_6443071812737183938[52] = 0;
   out_6443071812737183938[53] = 0;
}
void h_10(double *state, double *unused, double *out_2021668210924663063) {
   out_2021668210924663063[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2021668210924663063[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2021668210924663063[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7830124823924821015) {
   out_7830124823924821015[0] = 0;
   out_7830124823924821015[1] = 9.8100000000000005*cos(state[1]);
   out_7830124823924821015[2] = 0;
   out_7830124823924821015[3] = 0;
   out_7830124823924821015[4] = -state[8];
   out_7830124823924821015[5] = state[7];
   out_7830124823924821015[6] = 0;
   out_7830124823924821015[7] = state[5];
   out_7830124823924821015[8] = -state[4];
   out_7830124823924821015[9] = 0;
   out_7830124823924821015[10] = 0;
   out_7830124823924821015[11] = 0;
   out_7830124823924821015[12] = 1;
   out_7830124823924821015[13] = 0;
   out_7830124823924821015[14] = 0;
   out_7830124823924821015[15] = 1;
   out_7830124823924821015[16] = 0;
   out_7830124823924821015[17] = 0;
   out_7830124823924821015[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7830124823924821015[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7830124823924821015[20] = 0;
   out_7830124823924821015[21] = state[8];
   out_7830124823924821015[22] = 0;
   out_7830124823924821015[23] = -state[6];
   out_7830124823924821015[24] = -state[5];
   out_7830124823924821015[25] = 0;
   out_7830124823924821015[26] = state[3];
   out_7830124823924821015[27] = 0;
   out_7830124823924821015[28] = 0;
   out_7830124823924821015[29] = 0;
   out_7830124823924821015[30] = 0;
   out_7830124823924821015[31] = 1;
   out_7830124823924821015[32] = 0;
   out_7830124823924821015[33] = 0;
   out_7830124823924821015[34] = 1;
   out_7830124823924821015[35] = 0;
   out_7830124823924821015[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7830124823924821015[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7830124823924821015[38] = 0;
   out_7830124823924821015[39] = -state[7];
   out_7830124823924821015[40] = state[6];
   out_7830124823924821015[41] = 0;
   out_7830124823924821015[42] = state[4];
   out_7830124823924821015[43] = -state[3];
   out_7830124823924821015[44] = 0;
   out_7830124823924821015[45] = 0;
   out_7830124823924821015[46] = 0;
   out_7830124823924821015[47] = 0;
   out_7830124823924821015[48] = 0;
   out_7830124823924821015[49] = 0;
   out_7830124823924821015[50] = 1;
   out_7830124823924821015[51] = 0;
   out_7830124823924821015[52] = 0;
   out_7830124823924821015[53] = 1;
}
void h_13(double *state, double *unused, double *out_7135402855206141384) {
   out_7135402855206141384[0] = state[3];
   out_7135402855206141384[1] = state[4];
   out_7135402855206141384[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8791398435640034877) {
   out_8791398435640034877[0] = 0;
   out_8791398435640034877[1] = 0;
   out_8791398435640034877[2] = 0;
   out_8791398435640034877[3] = 1;
   out_8791398435640034877[4] = 0;
   out_8791398435640034877[5] = 0;
   out_8791398435640034877[6] = 0;
   out_8791398435640034877[7] = 0;
   out_8791398435640034877[8] = 0;
   out_8791398435640034877[9] = 0;
   out_8791398435640034877[10] = 0;
   out_8791398435640034877[11] = 0;
   out_8791398435640034877[12] = 0;
   out_8791398435640034877[13] = 0;
   out_8791398435640034877[14] = 0;
   out_8791398435640034877[15] = 0;
   out_8791398435640034877[16] = 0;
   out_8791398435640034877[17] = 0;
   out_8791398435640034877[18] = 0;
   out_8791398435640034877[19] = 0;
   out_8791398435640034877[20] = 0;
   out_8791398435640034877[21] = 0;
   out_8791398435640034877[22] = 1;
   out_8791398435640034877[23] = 0;
   out_8791398435640034877[24] = 0;
   out_8791398435640034877[25] = 0;
   out_8791398435640034877[26] = 0;
   out_8791398435640034877[27] = 0;
   out_8791398435640034877[28] = 0;
   out_8791398435640034877[29] = 0;
   out_8791398435640034877[30] = 0;
   out_8791398435640034877[31] = 0;
   out_8791398435640034877[32] = 0;
   out_8791398435640034877[33] = 0;
   out_8791398435640034877[34] = 0;
   out_8791398435640034877[35] = 0;
   out_8791398435640034877[36] = 0;
   out_8791398435640034877[37] = 0;
   out_8791398435640034877[38] = 0;
   out_8791398435640034877[39] = 0;
   out_8791398435640034877[40] = 0;
   out_8791398435640034877[41] = 1;
   out_8791398435640034877[42] = 0;
   out_8791398435640034877[43] = 0;
   out_8791398435640034877[44] = 0;
   out_8791398435640034877[45] = 0;
   out_8791398435640034877[46] = 0;
   out_8791398435640034877[47] = 0;
   out_8791398435640034877[48] = 0;
   out_8791398435640034877[49] = 0;
   out_8791398435640034877[50] = 0;
   out_8791398435640034877[51] = 0;
   out_8791398435640034877[52] = 0;
   out_8791398435640034877[53] = 0;
}
void h_14(double *state, double *unused, double *out_7043440464612625298) {
   out_7043440464612625298[0] = state[6];
   out_7043440464612625298[1] = state[7];
   out_7043440464612625298[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3360283380441811642) {
   out_3360283380441811642[0] = 0;
   out_3360283380441811642[1] = 0;
   out_3360283380441811642[2] = 0;
   out_3360283380441811642[3] = 0;
   out_3360283380441811642[4] = 0;
   out_3360283380441811642[5] = 0;
   out_3360283380441811642[6] = 1;
   out_3360283380441811642[7] = 0;
   out_3360283380441811642[8] = 0;
   out_3360283380441811642[9] = 0;
   out_3360283380441811642[10] = 0;
   out_3360283380441811642[11] = 0;
   out_3360283380441811642[12] = 0;
   out_3360283380441811642[13] = 0;
   out_3360283380441811642[14] = 0;
   out_3360283380441811642[15] = 0;
   out_3360283380441811642[16] = 0;
   out_3360283380441811642[17] = 0;
   out_3360283380441811642[18] = 0;
   out_3360283380441811642[19] = 0;
   out_3360283380441811642[20] = 0;
   out_3360283380441811642[21] = 0;
   out_3360283380441811642[22] = 0;
   out_3360283380441811642[23] = 0;
   out_3360283380441811642[24] = 0;
   out_3360283380441811642[25] = 1;
   out_3360283380441811642[26] = 0;
   out_3360283380441811642[27] = 0;
   out_3360283380441811642[28] = 0;
   out_3360283380441811642[29] = 0;
   out_3360283380441811642[30] = 0;
   out_3360283380441811642[31] = 0;
   out_3360283380441811642[32] = 0;
   out_3360283380441811642[33] = 0;
   out_3360283380441811642[34] = 0;
   out_3360283380441811642[35] = 0;
   out_3360283380441811642[36] = 0;
   out_3360283380441811642[37] = 0;
   out_3360283380441811642[38] = 0;
   out_3360283380441811642[39] = 0;
   out_3360283380441811642[40] = 0;
   out_3360283380441811642[41] = 0;
   out_3360283380441811642[42] = 0;
   out_3360283380441811642[43] = 0;
   out_3360283380441811642[44] = 1;
   out_3360283380441811642[45] = 0;
   out_3360283380441811642[46] = 0;
   out_3360283380441811642[47] = 0;
   out_3360283380441811642[48] = 0;
   out_3360283380441811642[49] = 0;
   out_3360283380441811642[50] = 0;
   out_3360283380441811642[51] = 0;
   out_3360283380441811642[52] = 0;
   out_3360283380441811642[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_8940459122146932400) {
  err_fun(nom_x, delta_x, out_8940459122146932400);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3384987028755125218) {
  inv_err_fun(nom_x, true_x, out_3384987028755125218);
}
void pose_H_mod_fun(double *state, double *out_5245124330854285834) {
  H_mod_fun(state, out_5245124330854285834);
}
void pose_f_fun(double *state, double dt, double *out_6830900184565569763) {
  f_fun(state,  dt, out_6830900184565569763);
}
void pose_F_fun(double *state, double dt, double *out_5118094281500581129) {
  F_fun(state,  dt, out_5118094281500581129);
}
void pose_h_4(double *state, double *unused, double *out_4935070827926002458) {
  h_4(state, unused, out_4935070827926002458);
}
void pose_H_4(double *state, double *unused, double *out_6443071812737183938) {
  H_4(state, unused, out_6443071812737183938);
}
void pose_h_10(double *state, double *unused, double *out_2021668210924663063) {
  h_10(state, unused, out_2021668210924663063);
}
void pose_H_10(double *state, double *unused, double *out_7830124823924821015) {
  H_10(state, unused, out_7830124823924821015);
}
void pose_h_13(double *state, double *unused, double *out_7135402855206141384) {
  h_13(state, unused, out_7135402855206141384);
}
void pose_H_13(double *state, double *unused, double *out_8791398435640034877) {
  H_13(state, unused, out_8791398435640034877);
}
void pose_h_14(double *state, double *unused, double *out_7043440464612625298) {
  h_14(state, unused, out_7043440464612625298);
}
void pose_H_14(double *state, double *unused, double *out_3360283380441811642) {
  H_14(state, unused, out_3360283380441811642);
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
