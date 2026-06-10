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
void err_fun(double *nom_x, double *delta_x, double *out_5797775412313342444) {
   out_5797775412313342444[0] = delta_x[0] + nom_x[0];
   out_5797775412313342444[1] = delta_x[1] + nom_x[1];
   out_5797775412313342444[2] = delta_x[2] + nom_x[2];
   out_5797775412313342444[3] = delta_x[3] + nom_x[3];
   out_5797775412313342444[4] = delta_x[4] + nom_x[4];
   out_5797775412313342444[5] = delta_x[5] + nom_x[5];
   out_5797775412313342444[6] = delta_x[6] + nom_x[6];
   out_5797775412313342444[7] = delta_x[7] + nom_x[7];
   out_5797775412313342444[8] = delta_x[8] + nom_x[8];
   out_5797775412313342444[9] = delta_x[9] + nom_x[9];
   out_5797775412313342444[10] = delta_x[10] + nom_x[10];
   out_5797775412313342444[11] = delta_x[11] + nom_x[11];
   out_5797775412313342444[12] = delta_x[12] + nom_x[12];
   out_5797775412313342444[13] = delta_x[13] + nom_x[13];
   out_5797775412313342444[14] = delta_x[14] + nom_x[14];
   out_5797775412313342444[15] = delta_x[15] + nom_x[15];
   out_5797775412313342444[16] = delta_x[16] + nom_x[16];
   out_5797775412313342444[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6978859077859564623) {
   out_6978859077859564623[0] = -nom_x[0] + true_x[0];
   out_6978859077859564623[1] = -nom_x[1] + true_x[1];
   out_6978859077859564623[2] = -nom_x[2] + true_x[2];
   out_6978859077859564623[3] = -nom_x[3] + true_x[3];
   out_6978859077859564623[4] = -nom_x[4] + true_x[4];
   out_6978859077859564623[5] = -nom_x[5] + true_x[5];
   out_6978859077859564623[6] = -nom_x[6] + true_x[6];
   out_6978859077859564623[7] = -nom_x[7] + true_x[7];
   out_6978859077859564623[8] = -nom_x[8] + true_x[8];
   out_6978859077859564623[9] = -nom_x[9] + true_x[9];
   out_6978859077859564623[10] = -nom_x[10] + true_x[10];
   out_6978859077859564623[11] = -nom_x[11] + true_x[11];
   out_6978859077859564623[12] = -nom_x[12] + true_x[12];
   out_6978859077859564623[13] = -nom_x[13] + true_x[13];
   out_6978859077859564623[14] = -nom_x[14] + true_x[14];
   out_6978859077859564623[15] = -nom_x[15] + true_x[15];
   out_6978859077859564623[16] = -nom_x[16] + true_x[16];
   out_6978859077859564623[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7486978165612535736) {
   out_7486978165612535736[0] = 1.0;
   out_7486978165612535736[1] = 0.0;
   out_7486978165612535736[2] = 0.0;
   out_7486978165612535736[3] = 0.0;
   out_7486978165612535736[4] = 0.0;
   out_7486978165612535736[5] = 0.0;
   out_7486978165612535736[6] = 0.0;
   out_7486978165612535736[7] = 0.0;
   out_7486978165612535736[8] = 0.0;
   out_7486978165612535736[9] = 0.0;
   out_7486978165612535736[10] = 0.0;
   out_7486978165612535736[11] = 0.0;
   out_7486978165612535736[12] = 0.0;
   out_7486978165612535736[13] = 0.0;
   out_7486978165612535736[14] = 0.0;
   out_7486978165612535736[15] = 0.0;
   out_7486978165612535736[16] = 0.0;
   out_7486978165612535736[17] = 0.0;
   out_7486978165612535736[18] = 0.0;
   out_7486978165612535736[19] = 1.0;
   out_7486978165612535736[20] = 0.0;
   out_7486978165612535736[21] = 0.0;
   out_7486978165612535736[22] = 0.0;
   out_7486978165612535736[23] = 0.0;
   out_7486978165612535736[24] = 0.0;
   out_7486978165612535736[25] = 0.0;
   out_7486978165612535736[26] = 0.0;
   out_7486978165612535736[27] = 0.0;
   out_7486978165612535736[28] = 0.0;
   out_7486978165612535736[29] = 0.0;
   out_7486978165612535736[30] = 0.0;
   out_7486978165612535736[31] = 0.0;
   out_7486978165612535736[32] = 0.0;
   out_7486978165612535736[33] = 0.0;
   out_7486978165612535736[34] = 0.0;
   out_7486978165612535736[35] = 0.0;
   out_7486978165612535736[36] = 0.0;
   out_7486978165612535736[37] = 0.0;
   out_7486978165612535736[38] = 1.0;
   out_7486978165612535736[39] = 0.0;
   out_7486978165612535736[40] = 0.0;
   out_7486978165612535736[41] = 0.0;
   out_7486978165612535736[42] = 0.0;
   out_7486978165612535736[43] = 0.0;
   out_7486978165612535736[44] = 0.0;
   out_7486978165612535736[45] = 0.0;
   out_7486978165612535736[46] = 0.0;
   out_7486978165612535736[47] = 0.0;
   out_7486978165612535736[48] = 0.0;
   out_7486978165612535736[49] = 0.0;
   out_7486978165612535736[50] = 0.0;
   out_7486978165612535736[51] = 0.0;
   out_7486978165612535736[52] = 0.0;
   out_7486978165612535736[53] = 0.0;
   out_7486978165612535736[54] = 0.0;
   out_7486978165612535736[55] = 0.0;
   out_7486978165612535736[56] = 0.0;
   out_7486978165612535736[57] = 1.0;
   out_7486978165612535736[58] = 0.0;
   out_7486978165612535736[59] = 0.0;
   out_7486978165612535736[60] = 0.0;
   out_7486978165612535736[61] = 0.0;
   out_7486978165612535736[62] = 0.0;
   out_7486978165612535736[63] = 0.0;
   out_7486978165612535736[64] = 0.0;
   out_7486978165612535736[65] = 0.0;
   out_7486978165612535736[66] = 0.0;
   out_7486978165612535736[67] = 0.0;
   out_7486978165612535736[68] = 0.0;
   out_7486978165612535736[69] = 0.0;
   out_7486978165612535736[70] = 0.0;
   out_7486978165612535736[71] = 0.0;
   out_7486978165612535736[72] = 0.0;
   out_7486978165612535736[73] = 0.0;
   out_7486978165612535736[74] = 0.0;
   out_7486978165612535736[75] = 0.0;
   out_7486978165612535736[76] = 1.0;
   out_7486978165612535736[77] = 0.0;
   out_7486978165612535736[78] = 0.0;
   out_7486978165612535736[79] = 0.0;
   out_7486978165612535736[80] = 0.0;
   out_7486978165612535736[81] = 0.0;
   out_7486978165612535736[82] = 0.0;
   out_7486978165612535736[83] = 0.0;
   out_7486978165612535736[84] = 0.0;
   out_7486978165612535736[85] = 0.0;
   out_7486978165612535736[86] = 0.0;
   out_7486978165612535736[87] = 0.0;
   out_7486978165612535736[88] = 0.0;
   out_7486978165612535736[89] = 0.0;
   out_7486978165612535736[90] = 0.0;
   out_7486978165612535736[91] = 0.0;
   out_7486978165612535736[92] = 0.0;
   out_7486978165612535736[93] = 0.0;
   out_7486978165612535736[94] = 0.0;
   out_7486978165612535736[95] = 1.0;
   out_7486978165612535736[96] = 0.0;
   out_7486978165612535736[97] = 0.0;
   out_7486978165612535736[98] = 0.0;
   out_7486978165612535736[99] = 0.0;
   out_7486978165612535736[100] = 0.0;
   out_7486978165612535736[101] = 0.0;
   out_7486978165612535736[102] = 0.0;
   out_7486978165612535736[103] = 0.0;
   out_7486978165612535736[104] = 0.0;
   out_7486978165612535736[105] = 0.0;
   out_7486978165612535736[106] = 0.0;
   out_7486978165612535736[107] = 0.0;
   out_7486978165612535736[108] = 0.0;
   out_7486978165612535736[109] = 0.0;
   out_7486978165612535736[110] = 0.0;
   out_7486978165612535736[111] = 0.0;
   out_7486978165612535736[112] = 0.0;
   out_7486978165612535736[113] = 0.0;
   out_7486978165612535736[114] = 1.0;
   out_7486978165612535736[115] = 0.0;
   out_7486978165612535736[116] = 0.0;
   out_7486978165612535736[117] = 0.0;
   out_7486978165612535736[118] = 0.0;
   out_7486978165612535736[119] = 0.0;
   out_7486978165612535736[120] = 0.0;
   out_7486978165612535736[121] = 0.0;
   out_7486978165612535736[122] = 0.0;
   out_7486978165612535736[123] = 0.0;
   out_7486978165612535736[124] = 0.0;
   out_7486978165612535736[125] = 0.0;
   out_7486978165612535736[126] = 0.0;
   out_7486978165612535736[127] = 0.0;
   out_7486978165612535736[128] = 0.0;
   out_7486978165612535736[129] = 0.0;
   out_7486978165612535736[130] = 0.0;
   out_7486978165612535736[131] = 0.0;
   out_7486978165612535736[132] = 0.0;
   out_7486978165612535736[133] = 1.0;
   out_7486978165612535736[134] = 0.0;
   out_7486978165612535736[135] = 0.0;
   out_7486978165612535736[136] = 0.0;
   out_7486978165612535736[137] = 0.0;
   out_7486978165612535736[138] = 0.0;
   out_7486978165612535736[139] = 0.0;
   out_7486978165612535736[140] = 0.0;
   out_7486978165612535736[141] = 0.0;
   out_7486978165612535736[142] = 0.0;
   out_7486978165612535736[143] = 0.0;
   out_7486978165612535736[144] = 0.0;
   out_7486978165612535736[145] = 0.0;
   out_7486978165612535736[146] = 0.0;
   out_7486978165612535736[147] = 0.0;
   out_7486978165612535736[148] = 0.0;
   out_7486978165612535736[149] = 0.0;
   out_7486978165612535736[150] = 0.0;
   out_7486978165612535736[151] = 0.0;
   out_7486978165612535736[152] = 1.0;
   out_7486978165612535736[153] = 0.0;
   out_7486978165612535736[154] = 0.0;
   out_7486978165612535736[155] = 0.0;
   out_7486978165612535736[156] = 0.0;
   out_7486978165612535736[157] = 0.0;
   out_7486978165612535736[158] = 0.0;
   out_7486978165612535736[159] = 0.0;
   out_7486978165612535736[160] = 0.0;
   out_7486978165612535736[161] = 0.0;
   out_7486978165612535736[162] = 0.0;
   out_7486978165612535736[163] = 0.0;
   out_7486978165612535736[164] = 0.0;
   out_7486978165612535736[165] = 0.0;
   out_7486978165612535736[166] = 0.0;
   out_7486978165612535736[167] = 0.0;
   out_7486978165612535736[168] = 0.0;
   out_7486978165612535736[169] = 0.0;
   out_7486978165612535736[170] = 0.0;
   out_7486978165612535736[171] = 1.0;
   out_7486978165612535736[172] = 0.0;
   out_7486978165612535736[173] = 0.0;
   out_7486978165612535736[174] = 0.0;
   out_7486978165612535736[175] = 0.0;
   out_7486978165612535736[176] = 0.0;
   out_7486978165612535736[177] = 0.0;
   out_7486978165612535736[178] = 0.0;
   out_7486978165612535736[179] = 0.0;
   out_7486978165612535736[180] = 0.0;
   out_7486978165612535736[181] = 0.0;
   out_7486978165612535736[182] = 0.0;
   out_7486978165612535736[183] = 0.0;
   out_7486978165612535736[184] = 0.0;
   out_7486978165612535736[185] = 0.0;
   out_7486978165612535736[186] = 0.0;
   out_7486978165612535736[187] = 0.0;
   out_7486978165612535736[188] = 0.0;
   out_7486978165612535736[189] = 0.0;
   out_7486978165612535736[190] = 1.0;
   out_7486978165612535736[191] = 0.0;
   out_7486978165612535736[192] = 0.0;
   out_7486978165612535736[193] = 0.0;
   out_7486978165612535736[194] = 0.0;
   out_7486978165612535736[195] = 0.0;
   out_7486978165612535736[196] = 0.0;
   out_7486978165612535736[197] = 0.0;
   out_7486978165612535736[198] = 0.0;
   out_7486978165612535736[199] = 0.0;
   out_7486978165612535736[200] = 0.0;
   out_7486978165612535736[201] = 0.0;
   out_7486978165612535736[202] = 0.0;
   out_7486978165612535736[203] = 0.0;
   out_7486978165612535736[204] = 0.0;
   out_7486978165612535736[205] = 0.0;
   out_7486978165612535736[206] = 0.0;
   out_7486978165612535736[207] = 0.0;
   out_7486978165612535736[208] = 0.0;
   out_7486978165612535736[209] = 1.0;
   out_7486978165612535736[210] = 0.0;
   out_7486978165612535736[211] = 0.0;
   out_7486978165612535736[212] = 0.0;
   out_7486978165612535736[213] = 0.0;
   out_7486978165612535736[214] = 0.0;
   out_7486978165612535736[215] = 0.0;
   out_7486978165612535736[216] = 0.0;
   out_7486978165612535736[217] = 0.0;
   out_7486978165612535736[218] = 0.0;
   out_7486978165612535736[219] = 0.0;
   out_7486978165612535736[220] = 0.0;
   out_7486978165612535736[221] = 0.0;
   out_7486978165612535736[222] = 0.0;
   out_7486978165612535736[223] = 0.0;
   out_7486978165612535736[224] = 0.0;
   out_7486978165612535736[225] = 0.0;
   out_7486978165612535736[226] = 0.0;
   out_7486978165612535736[227] = 0.0;
   out_7486978165612535736[228] = 1.0;
   out_7486978165612535736[229] = 0.0;
   out_7486978165612535736[230] = 0.0;
   out_7486978165612535736[231] = 0.0;
   out_7486978165612535736[232] = 0.0;
   out_7486978165612535736[233] = 0.0;
   out_7486978165612535736[234] = 0.0;
   out_7486978165612535736[235] = 0.0;
   out_7486978165612535736[236] = 0.0;
   out_7486978165612535736[237] = 0.0;
   out_7486978165612535736[238] = 0.0;
   out_7486978165612535736[239] = 0.0;
   out_7486978165612535736[240] = 0.0;
   out_7486978165612535736[241] = 0.0;
   out_7486978165612535736[242] = 0.0;
   out_7486978165612535736[243] = 0.0;
   out_7486978165612535736[244] = 0.0;
   out_7486978165612535736[245] = 0.0;
   out_7486978165612535736[246] = 0.0;
   out_7486978165612535736[247] = 1.0;
   out_7486978165612535736[248] = 0.0;
   out_7486978165612535736[249] = 0.0;
   out_7486978165612535736[250] = 0.0;
   out_7486978165612535736[251] = 0.0;
   out_7486978165612535736[252] = 0.0;
   out_7486978165612535736[253] = 0.0;
   out_7486978165612535736[254] = 0.0;
   out_7486978165612535736[255] = 0.0;
   out_7486978165612535736[256] = 0.0;
   out_7486978165612535736[257] = 0.0;
   out_7486978165612535736[258] = 0.0;
   out_7486978165612535736[259] = 0.0;
   out_7486978165612535736[260] = 0.0;
   out_7486978165612535736[261] = 0.0;
   out_7486978165612535736[262] = 0.0;
   out_7486978165612535736[263] = 0.0;
   out_7486978165612535736[264] = 0.0;
   out_7486978165612535736[265] = 0.0;
   out_7486978165612535736[266] = 1.0;
   out_7486978165612535736[267] = 0.0;
   out_7486978165612535736[268] = 0.0;
   out_7486978165612535736[269] = 0.0;
   out_7486978165612535736[270] = 0.0;
   out_7486978165612535736[271] = 0.0;
   out_7486978165612535736[272] = 0.0;
   out_7486978165612535736[273] = 0.0;
   out_7486978165612535736[274] = 0.0;
   out_7486978165612535736[275] = 0.0;
   out_7486978165612535736[276] = 0.0;
   out_7486978165612535736[277] = 0.0;
   out_7486978165612535736[278] = 0.0;
   out_7486978165612535736[279] = 0.0;
   out_7486978165612535736[280] = 0.0;
   out_7486978165612535736[281] = 0.0;
   out_7486978165612535736[282] = 0.0;
   out_7486978165612535736[283] = 0.0;
   out_7486978165612535736[284] = 0.0;
   out_7486978165612535736[285] = 1.0;
   out_7486978165612535736[286] = 0.0;
   out_7486978165612535736[287] = 0.0;
   out_7486978165612535736[288] = 0.0;
   out_7486978165612535736[289] = 0.0;
   out_7486978165612535736[290] = 0.0;
   out_7486978165612535736[291] = 0.0;
   out_7486978165612535736[292] = 0.0;
   out_7486978165612535736[293] = 0.0;
   out_7486978165612535736[294] = 0.0;
   out_7486978165612535736[295] = 0.0;
   out_7486978165612535736[296] = 0.0;
   out_7486978165612535736[297] = 0.0;
   out_7486978165612535736[298] = 0.0;
   out_7486978165612535736[299] = 0.0;
   out_7486978165612535736[300] = 0.0;
   out_7486978165612535736[301] = 0.0;
   out_7486978165612535736[302] = 0.0;
   out_7486978165612535736[303] = 0.0;
   out_7486978165612535736[304] = 1.0;
   out_7486978165612535736[305] = 0.0;
   out_7486978165612535736[306] = 0.0;
   out_7486978165612535736[307] = 0.0;
   out_7486978165612535736[308] = 0.0;
   out_7486978165612535736[309] = 0.0;
   out_7486978165612535736[310] = 0.0;
   out_7486978165612535736[311] = 0.0;
   out_7486978165612535736[312] = 0.0;
   out_7486978165612535736[313] = 0.0;
   out_7486978165612535736[314] = 0.0;
   out_7486978165612535736[315] = 0.0;
   out_7486978165612535736[316] = 0.0;
   out_7486978165612535736[317] = 0.0;
   out_7486978165612535736[318] = 0.0;
   out_7486978165612535736[319] = 0.0;
   out_7486978165612535736[320] = 0.0;
   out_7486978165612535736[321] = 0.0;
   out_7486978165612535736[322] = 0.0;
   out_7486978165612535736[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_7331794505583909673) {
   out_7331794505583909673[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_7331794505583909673[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_7331794505583909673[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_7331794505583909673[3] = dt*state[12] + state[3];
   out_7331794505583909673[4] = dt*state[13] + state[4];
   out_7331794505583909673[5] = dt*state[14] + state[5];
   out_7331794505583909673[6] = state[6];
   out_7331794505583909673[7] = state[7];
   out_7331794505583909673[8] = state[8];
   out_7331794505583909673[9] = state[9];
   out_7331794505583909673[10] = state[10];
   out_7331794505583909673[11] = state[11];
   out_7331794505583909673[12] = state[12];
   out_7331794505583909673[13] = state[13];
   out_7331794505583909673[14] = state[14];
   out_7331794505583909673[15] = state[15];
   out_7331794505583909673[16] = state[16];
   out_7331794505583909673[17] = state[17];
}
void F_fun(double *state, double dt, double *out_6844171548938607295) {
   out_6844171548938607295[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6844171548938607295[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6844171548938607295[2] = 0;
   out_6844171548938607295[3] = 0;
   out_6844171548938607295[4] = 0;
   out_6844171548938607295[5] = 0;
   out_6844171548938607295[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6844171548938607295[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6844171548938607295[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6844171548938607295[9] = 0;
   out_6844171548938607295[10] = 0;
   out_6844171548938607295[11] = 0;
   out_6844171548938607295[12] = 0;
   out_6844171548938607295[13] = 0;
   out_6844171548938607295[14] = 0;
   out_6844171548938607295[15] = 0;
   out_6844171548938607295[16] = 0;
   out_6844171548938607295[17] = 0;
   out_6844171548938607295[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6844171548938607295[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6844171548938607295[20] = 0;
   out_6844171548938607295[21] = 0;
   out_6844171548938607295[22] = 0;
   out_6844171548938607295[23] = 0;
   out_6844171548938607295[24] = 0;
   out_6844171548938607295[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6844171548938607295[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6844171548938607295[27] = 0;
   out_6844171548938607295[28] = 0;
   out_6844171548938607295[29] = 0;
   out_6844171548938607295[30] = 0;
   out_6844171548938607295[31] = 0;
   out_6844171548938607295[32] = 0;
   out_6844171548938607295[33] = 0;
   out_6844171548938607295[34] = 0;
   out_6844171548938607295[35] = 0;
   out_6844171548938607295[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6844171548938607295[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6844171548938607295[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6844171548938607295[39] = 0;
   out_6844171548938607295[40] = 0;
   out_6844171548938607295[41] = 0;
   out_6844171548938607295[42] = 0;
   out_6844171548938607295[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6844171548938607295[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6844171548938607295[45] = 0;
   out_6844171548938607295[46] = 0;
   out_6844171548938607295[47] = 0;
   out_6844171548938607295[48] = 0;
   out_6844171548938607295[49] = 0;
   out_6844171548938607295[50] = 0;
   out_6844171548938607295[51] = 0;
   out_6844171548938607295[52] = 0;
   out_6844171548938607295[53] = 0;
   out_6844171548938607295[54] = 0;
   out_6844171548938607295[55] = 0;
   out_6844171548938607295[56] = 0;
   out_6844171548938607295[57] = 1;
   out_6844171548938607295[58] = 0;
   out_6844171548938607295[59] = 0;
   out_6844171548938607295[60] = 0;
   out_6844171548938607295[61] = 0;
   out_6844171548938607295[62] = 0;
   out_6844171548938607295[63] = 0;
   out_6844171548938607295[64] = 0;
   out_6844171548938607295[65] = 0;
   out_6844171548938607295[66] = dt;
   out_6844171548938607295[67] = 0;
   out_6844171548938607295[68] = 0;
   out_6844171548938607295[69] = 0;
   out_6844171548938607295[70] = 0;
   out_6844171548938607295[71] = 0;
   out_6844171548938607295[72] = 0;
   out_6844171548938607295[73] = 0;
   out_6844171548938607295[74] = 0;
   out_6844171548938607295[75] = 0;
   out_6844171548938607295[76] = 1;
   out_6844171548938607295[77] = 0;
   out_6844171548938607295[78] = 0;
   out_6844171548938607295[79] = 0;
   out_6844171548938607295[80] = 0;
   out_6844171548938607295[81] = 0;
   out_6844171548938607295[82] = 0;
   out_6844171548938607295[83] = 0;
   out_6844171548938607295[84] = 0;
   out_6844171548938607295[85] = dt;
   out_6844171548938607295[86] = 0;
   out_6844171548938607295[87] = 0;
   out_6844171548938607295[88] = 0;
   out_6844171548938607295[89] = 0;
   out_6844171548938607295[90] = 0;
   out_6844171548938607295[91] = 0;
   out_6844171548938607295[92] = 0;
   out_6844171548938607295[93] = 0;
   out_6844171548938607295[94] = 0;
   out_6844171548938607295[95] = 1;
   out_6844171548938607295[96] = 0;
   out_6844171548938607295[97] = 0;
   out_6844171548938607295[98] = 0;
   out_6844171548938607295[99] = 0;
   out_6844171548938607295[100] = 0;
   out_6844171548938607295[101] = 0;
   out_6844171548938607295[102] = 0;
   out_6844171548938607295[103] = 0;
   out_6844171548938607295[104] = dt;
   out_6844171548938607295[105] = 0;
   out_6844171548938607295[106] = 0;
   out_6844171548938607295[107] = 0;
   out_6844171548938607295[108] = 0;
   out_6844171548938607295[109] = 0;
   out_6844171548938607295[110] = 0;
   out_6844171548938607295[111] = 0;
   out_6844171548938607295[112] = 0;
   out_6844171548938607295[113] = 0;
   out_6844171548938607295[114] = 1;
   out_6844171548938607295[115] = 0;
   out_6844171548938607295[116] = 0;
   out_6844171548938607295[117] = 0;
   out_6844171548938607295[118] = 0;
   out_6844171548938607295[119] = 0;
   out_6844171548938607295[120] = 0;
   out_6844171548938607295[121] = 0;
   out_6844171548938607295[122] = 0;
   out_6844171548938607295[123] = 0;
   out_6844171548938607295[124] = 0;
   out_6844171548938607295[125] = 0;
   out_6844171548938607295[126] = 0;
   out_6844171548938607295[127] = 0;
   out_6844171548938607295[128] = 0;
   out_6844171548938607295[129] = 0;
   out_6844171548938607295[130] = 0;
   out_6844171548938607295[131] = 0;
   out_6844171548938607295[132] = 0;
   out_6844171548938607295[133] = 1;
   out_6844171548938607295[134] = 0;
   out_6844171548938607295[135] = 0;
   out_6844171548938607295[136] = 0;
   out_6844171548938607295[137] = 0;
   out_6844171548938607295[138] = 0;
   out_6844171548938607295[139] = 0;
   out_6844171548938607295[140] = 0;
   out_6844171548938607295[141] = 0;
   out_6844171548938607295[142] = 0;
   out_6844171548938607295[143] = 0;
   out_6844171548938607295[144] = 0;
   out_6844171548938607295[145] = 0;
   out_6844171548938607295[146] = 0;
   out_6844171548938607295[147] = 0;
   out_6844171548938607295[148] = 0;
   out_6844171548938607295[149] = 0;
   out_6844171548938607295[150] = 0;
   out_6844171548938607295[151] = 0;
   out_6844171548938607295[152] = 1;
   out_6844171548938607295[153] = 0;
   out_6844171548938607295[154] = 0;
   out_6844171548938607295[155] = 0;
   out_6844171548938607295[156] = 0;
   out_6844171548938607295[157] = 0;
   out_6844171548938607295[158] = 0;
   out_6844171548938607295[159] = 0;
   out_6844171548938607295[160] = 0;
   out_6844171548938607295[161] = 0;
   out_6844171548938607295[162] = 0;
   out_6844171548938607295[163] = 0;
   out_6844171548938607295[164] = 0;
   out_6844171548938607295[165] = 0;
   out_6844171548938607295[166] = 0;
   out_6844171548938607295[167] = 0;
   out_6844171548938607295[168] = 0;
   out_6844171548938607295[169] = 0;
   out_6844171548938607295[170] = 0;
   out_6844171548938607295[171] = 1;
   out_6844171548938607295[172] = 0;
   out_6844171548938607295[173] = 0;
   out_6844171548938607295[174] = 0;
   out_6844171548938607295[175] = 0;
   out_6844171548938607295[176] = 0;
   out_6844171548938607295[177] = 0;
   out_6844171548938607295[178] = 0;
   out_6844171548938607295[179] = 0;
   out_6844171548938607295[180] = 0;
   out_6844171548938607295[181] = 0;
   out_6844171548938607295[182] = 0;
   out_6844171548938607295[183] = 0;
   out_6844171548938607295[184] = 0;
   out_6844171548938607295[185] = 0;
   out_6844171548938607295[186] = 0;
   out_6844171548938607295[187] = 0;
   out_6844171548938607295[188] = 0;
   out_6844171548938607295[189] = 0;
   out_6844171548938607295[190] = 1;
   out_6844171548938607295[191] = 0;
   out_6844171548938607295[192] = 0;
   out_6844171548938607295[193] = 0;
   out_6844171548938607295[194] = 0;
   out_6844171548938607295[195] = 0;
   out_6844171548938607295[196] = 0;
   out_6844171548938607295[197] = 0;
   out_6844171548938607295[198] = 0;
   out_6844171548938607295[199] = 0;
   out_6844171548938607295[200] = 0;
   out_6844171548938607295[201] = 0;
   out_6844171548938607295[202] = 0;
   out_6844171548938607295[203] = 0;
   out_6844171548938607295[204] = 0;
   out_6844171548938607295[205] = 0;
   out_6844171548938607295[206] = 0;
   out_6844171548938607295[207] = 0;
   out_6844171548938607295[208] = 0;
   out_6844171548938607295[209] = 1;
   out_6844171548938607295[210] = 0;
   out_6844171548938607295[211] = 0;
   out_6844171548938607295[212] = 0;
   out_6844171548938607295[213] = 0;
   out_6844171548938607295[214] = 0;
   out_6844171548938607295[215] = 0;
   out_6844171548938607295[216] = 0;
   out_6844171548938607295[217] = 0;
   out_6844171548938607295[218] = 0;
   out_6844171548938607295[219] = 0;
   out_6844171548938607295[220] = 0;
   out_6844171548938607295[221] = 0;
   out_6844171548938607295[222] = 0;
   out_6844171548938607295[223] = 0;
   out_6844171548938607295[224] = 0;
   out_6844171548938607295[225] = 0;
   out_6844171548938607295[226] = 0;
   out_6844171548938607295[227] = 0;
   out_6844171548938607295[228] = 1;
   out_6844171548938607295[229] = 0;
   out_6844171548938607295[230] = 0;
   out_6844171548938607295[231] = 0;
   out_6844171548938607295[232] = 0;
   out_6844171548938607295[233] = 0;
   out_6844171548938607295[234] = 0;
   out_6844171548938607295[235] = 0;
   out_6844171548938607295[236] = 0;
   out_6844171548938607295[237] = 0;
   out_6844171548938607295[238] = 0;
   out_6844171548938607295[239] = 0;
   out_6844171548938607295[240] = 0;
   out_6844171548938607295[241] = 0;
   out_6844171548938607295[242] = 0;
   out_6844171548938607295[243] = 0;
   out_6844171548938607295[244] = 0;
   out_6844171548938607295[245] = 0;
   out_6844171548938607295[246] = 0;
   out_6844171548938607295[247] = 1;
   out_6844171548938607295[248] = 0;
   out_6844171548938607295[249] = 0;
   out_6844171548938607295[250] = 0;
   out_6844171548938607295[251] = 0;
   out_6844171548938607295[252] = 0;
   out_6844171548938607295[253] = 0;
   out_6844171548938607295[254] = 0;
   out_6844171548938607295[255] = 0;
   out_6844171548938607295[256] = 0;
   out_6844171548938607295[257] = 0;
   out_6844171548938607295[258] = 0;
   out_6844171548938607295[259] = 0;
   out_6844171548938607295[260] = 0;
   out_6844171548938607295[261] = 0;
   out_6844171548938607295[262] = 0;
   out_6844171548938607295[263] = 0;
   out_6844171548938607295[264] = 0;
   out_6844171548938607295[265] = 0;
   out_6844171548938607295[266] = 1;
   out_6844171548938607295[267] = 0;
   out_6844171548938607295[268] = 0;
   out_6844171548938607295[269] = 0;
   out_6844171548938607295[270] = 0;
   out_6844171548938607295[271] = 0;
   out_6844171548938607295[272] = 0;
   out_6844171548938607295[273] = 0;
   out_6844171548938607295[274] = 0;
   out_6844171548938607295[275] = 0;
   out_6844171548938607295[276] = 0;
   out_6844171548938607295[277] = 0;
   out_6844171548938607295[278] = 0;
   out_6844171548938607295[279] = 0;
   out_6844171548938607295[280] = 0;
   out_6844171548938607295[281] = 0;
   out_6844171548938607295[282] = 0;
   out_6844171548938607295[283] = 0;
   out_6844171548938607295[284] = 0;
   out_6844171548938607295[285] = 1;
   out_6844171548938607295[286] = 0;
   out_6844171548938607295[287] = 0;
   out_6844171548938607295[288] = 0;
   out_6844171548938607295[289] = 0;
   out_6844171548938607295[290] = 0;
   out_6844171548938607295[291] = 0;
   out_6844171548938607295[292] = 0;
   out_6844171548938607295[293] = 0;
   out_6844171548938607295[294] = 0;
   out_6844171548938607295[295] = 0;
   out_6844171548938607295[296] = 0;
   out_6844171548938607295[297] = 0;
   out_6844171548938607295[298] = 0;
   out_6844171548938607295[299] = 0;
   out_6844171548938607295[300] = 0;
   out_6844171548938607295[301] = 0;
   out_6844171548938607295[302] = 0;
   out_6844171548938607295[303] = 0;
   out_6844171548938607295[304] = 1;
   out_6844171548938607295[305] = 0;
   out_6844171548938607295[306] = 0;
   out_6844171548938607295[307] = 0;
   out_6844171548938607295[308] = 0;
   out_6844171548938607295[309] = 0;
   out_6844171548938607295[310] = 0;
   out_6844171548938607295[311] = 0;
   out_6844171548938607295[312] = 0;
   out_6844171548938607295[313] = 0;
   out_6844171548938607295[314] = 0;
   out_6844171548938607295[315] = 0;
   out_6844171548938607295[316] = 0;
   out_6844171548938607295[317] = 0;
   out_6844171548938607295[318] = 0;
   out_6844171548938607295[319] = 0;
   out_6844171548938607295[320] = 0;
   out_6844171548938607295[321] = 0;
   out_6844171548938607295[322] = 0;
   out_6844171548938607295[323] = 1;
}
void h_4(double *state, double *unused, double *out_7129002449097779903) {
   out_7129002449097779903[0] = state[6] + state[9];
   out_7129002449097779903[1] = state[7] + state[10];
   out_7129002449097779903[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1457383500445285606) {
   out_1457383500445285606[0] = 0;
   out_1457383500445285606[1] = 0;
   out_1457383500445285606[2] = 0;
   out_1457383500445285606[3] = 0;
   out_1457383500445285606[4] = 0;
   out_1457383500445285606[5] = 0;
   out_1457383500445285606[6] = 1;
   out_1457383500445285606[7] = 0;
   out_1457383500445285606[8] = 0;
   out_1457383500445285606[9] = 1;
   out_1457383500445285606[10] = 0;
   out_1457383500445285606[11] = 0;
   out_1457383500445285606[12] = 0;
   out_1457383500445285606[13] = 0;
   out_1457383500445285606[14] = 0;
   out_1457383500445285606[15] = 0;
   out_1457383500445285606[16] = 0;
   out_1457383500445285606[17] = 0;
   out_1457383500445285606[18] = 0;
   out_1457383500445285606[19] = 0;
   out_1457383500445285606[20] = 0;
   out_1457383500445285606[21] = 0;
   out_1457383500445285606[22] = 0;
   out_1457383500445285606[23] = 0;
   out_1457383500445285606[24] = 0;
   out_1457383500445285606[25] = 1;
   out_1457383500445285606[26] = 0;
   out_1457383500445285606[27] = 0;
   out_1457383500445285606[28] = 1;
   out_1457383500445285606[29] = 0;
   out_1457383500445285606[30] = 0;
   out_1457383500445285606[31] = 0;
   out_1457383500445285606[32] = 0;
   out_1457383500445285606[33] = 0;
   out_1457383500445285606[34] = 0;
   out_1457383500445285606[35] = 0;
   out_1457383500445285606[36] = 0;
   out_1457383500445285606[37] = 0;
   out_1457383500445285606[38] = 0;
   out_1457383500445285606[39] = 0;
   out_1457383500445285606[40] = 0;
   out_1457383500445285606[41] = 0;
   out_1457383500445285606[42] = 0;
   out_1457383500445285606[43] = 0;
   out_1457383500445285606[44] = 1;
   out_1457383500445285606[45] = 0;
   out_1457383500445285606[46] = 0;
   out_1457383500445285606[47] = 1;
   out_1457383500445285606[48] = 0;
   out_1457383500445285606[49] = 0;
   out_1457383500445285606[50] = 0;
   out_1457383500445285606[51] = 0;
   out_1457383500445285606[52] = 0;
   out_1457383500445285606[53] = 0;
}
void h_10(double *state, double *unused, double *out_3148302492513217557) {
   out_3148302492513217557[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3148302492513217557[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3148302492513217557[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_4488407256990316453) {
   out_4488407256990316453[0] = 0;
   out_4488407256990316453[1] = 9.8100000000000005*cos(state[1]);
   out_4488407256990316453[2] = 0;
   out_4488407256990316453[3] = 0;
   out_4488407256990316453[4] = -state[8];
   out_4488407256990316453[5] = state[7];
   out_4488407256990316453[6] = 0;
   out_4488407256990316453[7] = state[5];
   out_4488407256990316453[8] = -state[4];
   out_4488407256990316453[9] = 0;
   out_4488407256990316453[10] = 0;
   out_4488407256990316453[11] = 0;
   out_4488407256990316453[12] = 1;
   out_4488407256990316453[13] = 0;
   out_4488407256990316453[14] = 0;
   out_4488407256990316453[15] = 1;
   out_4488407256990316453[16] = 0;
   out_4488407256990316453[17] = 0;
   out_4488407256990316453[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_4488407256990316453[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_4488407256990316453[20] = 0;
   out_4488407256990316453[21] = state[8];
   out_4488407256990316453[22] = 0;
   out_4488407256990316453[23] = -state[6];
   out_4488407256990316453[24] = -state[5];
   out_4488407256990316453[25] = 0;
   out_4488407256990316453[26] = state[3];
   out_4488407256990316453[27] = 0;
   out_4488407256990316453[28] = 0;
   out_4488407256990316453[29] = 0;
   out_4488407256990316453[30] = 0;
   out_4488407256990316453[31] = 1;
   out_4488407256990316453[32] = 0;
   out_4488407256990316453[33] = 0;
   out_4488407256990316453[34] = 1;
   out_4488407256990316453[35] = 0;
   out_4488407256990316453[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_4488407256990316453[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_4488407256990316453[38] = 0;
   out_4488407256990316453[39] = -state[7];
   out_4488407256990316453[40] = state[6];
   out_4488407256990316453[41] = 0;
   out_4488407256990316453[42] = state[4];
   out_4488407256990316453[43] = -state[3];
   out_4488407256990316453[44] = 0;
   out_4488407256990316453[45] = 0;
   out_4488407256990316453[46] = 0;
   out_4488407256990316453[47] = 0;
   out_4488407256990316453[48] = 0;
   out_4488407256990316453[49] = 0;
   out_4488407256990316453[50] = 1;
   out_4488407256990316453[51] = 0;
   out_4488407256990316453[52] = 0;
   out_4488407256990316453[53] = 1;
}
void h_13(double *state, double *unused, double *out_3993880518003112603) {
   out_3993880518003112603[0] = state[3];
   out_3993880518003112603[1] = state[4];
   out_3993880518003112603[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1754890324887047195) {
   out_1754890324887047195[0] = 0;
   out_1754890324887047195[1] = 0;
   out_1754890324887047195[2] = 0;
   out_1754890324887047195[3] = 1;
   out_1754890324887047195[4] = 0;
   out_1754890324887047195[5] = 0;
   out_1754890324887047195[6] = 0;
   out_1754890324887047195[7] = 0;
   out_1754890324887047195[8] = 0;
   out_1754890324887047195[9] = 0;
   out_1754890324887047195[10] = 0;
   out_1754890324887047195[11] = 0;
   out_1754890324887047195[12] = 0;
   out_1754890324887047195[13] = 0;
   out_1754890324887047195[14] = 0;
   out_1754890324887047195[15] = 0;
   out_1754890324887047195[16] = 0;
   out_1754890324887047195[17] = 0;
   out_1754890324887047195[18] = 0;
   out_1754890324887047195[19] = 0;
   out_1754890324887047195[20] = 0;
   out_1754890324887047195[21] = 0;
   out_1754890324887047195[22] = 1;
   out_1754890324887047195[23] = 0;
   out_1754890324887047195[24] = 0;
   out_1754890324887047195[25] = 0;
   out_1754890324887047195[26] = 0;
   out_1754890324887047195[27] = 0;
   out_1754890324887047195[28] = 0;
   out_1754890324887047195[29] = 0;
   out_1754890324887047195[30] = 0;
   out_1754890324887047195[31] = 0;
   out_1754890324887047195[32] = 0;
   out_1754890324887047195[33] = 0;
   out_1754890324887047195[34] = 0;
   out_1754890324887047195[35] = 0;
   out_1754890324887047195[36] = 0;
   out_1754890324887047195[37] = 0;
   out_1754890324887047195[38] = 0;
   out_1754890324887047195[39] = 0;
   out_1754890324887047195[40] = 0;
   out_1754890324887047195[41] = 1;
   out_1754890324887047195[42] = 0;
   out_1754890324887047195[43] = 0;
   out_1754890324887047195[44] = 0;
   out_1754890324887047195[45] = 0;
   out_1754890324887047195[46] = 0;
   out_1754890324887047195[47] = 0;
   out_1754890324887047195[48] = 0;
   out_1754890324887047195[49] = 0;
   out_1754890324887047195[50] = 0;
   out_1754890324887047195[51] = 0;
   out_1754890324887047195[52] = 0;
   out_1754890324887047195[53] = 0;
}
void h_14(double *state, double *unused, double *out_318727471713913742) {
   out_318727471713913742[0] = state[6];
   out_318727471713913742[1] = state[7];
   out_318727471713913742[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4540171932740657902) {
   out_4540171932740657902[0] = 0;
   out_4540171932740657902[1] = 0;
   out_4540171932740657902[2] = 0;
   out_4540171932740657902[3] = 0;
   out_4540171932740657902[4] = 0;
   out_4540171932740657902[5] = 0;
   out_4540171932740657902[6] = 1;
   out_4540171932740657902[7] = 0;
   out_4540171932740657902[8] = 0;
   out_4540171932740657902[9] = 0;
   out_4540171932740657902[10] = 0;
   out_4540171932740657902[11] = 0;
   out_4540171932740657902[12] = 0;
   out_4540171932740657902[13] = 0;
   out_4540171932740657902[14] = 0;
   out_4540171932740657902[15] = 0;
   out_4540171932740657902[16] = 0;
   out_4540171932740657902[17] = 0;
   out_4540171932740657902[18] = 0;
   out_4540171932740657902[19] = 0;
   out_4540171932740657902[20] = 0;
   out_4540171932740657902[21] = 0;
   out_4540171932740657902[22] = 0;
   out_4540171932740657902[23] = 0;
   out_4540171932740657902[24] = 0;
   out_4540171932740657902[25] = 1;
   out_4540171932740657902[26] = 0;
   out_4540171932740657902[27] = 0;
   out_4540171932740657902[28] = 0;
   out_4540171932740657902[29] = 0;
   out_4540171932740657902[30] = 0;
   out_4540171932740657902[31] = 0;
   out_4540171932740657902[32] = 0;
   out_4540171932740657902[33] = 0;
   out_4540171932740657902[34] = 0;
   out_4540171932740657902[35] = 0;
   out_4540171932740657902[36] = 0;
   out_4540171932740657902[37] = 0;
   out_4540171932740657902[38] = 0;
   out_4540171932740657902[39] = 0;
   out_4540171932740657902[40] = 0;
   out_4540171932740657902[41] = 0;
   out_4540171932740657902[42] = 0;
   out_4540171932740657902[43] = 0;
   out_4540171932740657902[44] = 1;
   out_4540171932740657902[45] = 0;
   out_4540171932740657902[46] = 0;
   out_4540171932740657902[47] = 0;
   out_4540171932740657902[48] = 0;
   out_4540171932740657902[49] = 0;
   out_4540171932740657902[50] = 0;
   out_4540171932740657902[51] = 0;
   out_4540171932740657902[52] = 0;
   out_4540171932740657902[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5797775412313342444) {
  err_fun(nom_x, delta_x, out_5797775412313342444);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6978859077859564623) {
  inv_err_fun(nom_x, true_x, out_6978859077859564623);
}
void pose_H_mod_fun(double *state, double *out_7486978165612535736) {
  H_mod_fun(state, out_7486978165612535736);
}
void pose_f_fun(double *state, double dt, double *out_7331794505583909673) {
  f_fun(state,  dt, out_7331794505583909673);
}
void pose_F_fun(double *state, double dt, double *out_6844171548938607295) {
  F_fun(state,  dt, out_6844171548938607295);
}
void pose_h_4(double *state, double *unused, double *out_7129002449097779903) {
  h_4(state, unused, out_7129002449097779903);
}
void pose_H_4(double *state, double *unused, double *out_1457383500445285606) {
  H_4(state, unused, out_1457383500445285606);
}
void pose_h_10(double *state, double *unused, double *out_3148302492513217557) {
  h_10(state, unused, out_3148302492513217557);
}
void pose_H_10(double *state, double *unused, double *out_4488407256990316453) {
  H_10(state, unused, out_4488407256990316453);
}
void pose_h_13(double *state, double *unused, double *out_3993880518003112603) {
  h_13(state, unused, out_3993880518003112603);
}
void pose_H_13(double *state, double *unused, double *out_1754890324887047195) {
  H_13(state, unused, out_1754890324887047195);
}
void pose_h_14(double *state, double *unused, double *out_318727471713913742) {
  h_14(state, unused, out_318727471713913742);
}
void pose_H_14(double *state, double *unused, double *out_4540171932740657902) {
  H_14(state, unused, out_4540171932740657902);
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
