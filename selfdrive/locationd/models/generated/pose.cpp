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
void err_fun(double *nom_x, double *delta_x, double *out_1308154946342484284) {
   out_1308154946342484284[0] = delta_x[0] + nom_x[0];
   out_1308154946342484284[1] = delta_x[1] + nom_x[1];
   out_1308154946342484284[2] = delta_x[2] + nom_x[2];
   out_1308154946342484284[3] = delta_x[3] + nom_x[3];
   out_1308154946342484284[4] = delta_x[4] + nom_x[4];
   out_1308154946342484284[5] = delta_x[5] + nom_x[5];
   out_1308154946342484284[6] = delta_x[6] + nom_x[6];
   out_1308154946342484284[7] = delta_x[7] + nom_x[7];
   out_1308154946342484284[8] = delta_x[8] + nom_x[8];
   out_1308154946342484284[9] = delta_x[9] + nom_x[9];
   out_1308154946342484284[10] = delta_x[10] + nom_x[10];
   out_1308154946342484284[11] = delta_x[11] + nom_x[11];
   out_1308154946342484284[12] = delta_x[12] + nom_x[12];
   out_1308154946342484284[13] = delta_x[13] + nom_x[13];
   out_1308154946342484284[14] = delta_x[14] + nom_x[14];
   out_1308154946342484284[15] = delta_x[15] + nom_x[15];
   out_1308154946342484284[16] = delta_x[16] + nom_x[16];
   out_1308154946342484284[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8706500607592261698) {
   out_8706500607592261698[0] = -nom_x[0] + true_x[0];
   out_8706500607592261698[1] = -nom_x[1] + true_x[1];
   out_8706500607592261698[2] = -nom_x[2] + true_x[2];
   out_8706500607592261698[3] = -nom_x[3] + true_x[3];
   out_8706500607592261698[4] = -nom_x[4] + true_x[4];
   out_8706500607592261698[5] = -nom_x[5] + true_x[5];
   out_8706500607592261698[6] = -nom_x[6] + true_x[6];
   out_8706500607592261698[7] = -nom_x[7] + true_x[7];
   out_8706500607592261698[8] = -nom_x[8] + true_x[8];
   out_8706500607592261698[9] = -nom_x[9] + true_x[9];
   out_8706500607592261698[10] = -nom_x[10] + true_x[10];
   out_8706500607592261698[11] = -nom_x[11] + true_x[11];
   out_8706500607592261698[12] = -nom_x[12] + true_x[12];
   out_8706500607592261698[13] = -nom_x[13] + true_x[13];
   out_8706500607592261698[14] = -nom_x[14] + true_x[14];
   out_8706500607592261698[15] = -nom_x[15] + true_x[15];
   out_8706500607592261698[16] = -nom_x[16] + true_x[16];
   out_8706500607592261698[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_1512473366161392308) {
   out_1512473366161392308[0] = 1.0;
   out_1512473366161392308[1] = 0.0;
   out_1512473366161392308[2] = 0.0;
   out_1512473366161392308[3] = 0.0;
   out_1512473366161392308[4] = 0.0;
   out_1512473366161392308[5] = 0.0;
   out_1512473366161392308[6] = 0.0;
   out_1512473366161392308[7] = 0.0;
   out_1512473366161392308[8] = 0.0;
   out_1512473366161392308[9] = 0.0;
   out_1512473366161392308[10] = 0.0;
   out_1512473366161392308[11] = 0.0;
   out_1512473366161392308[12] = 0.0;
   out_1512473366161392308[13] = 0.0;
   out_1512473366161392308[14] = 0.0;
   out_1512473366161392308[15] = 0.0;
   out_1512473366161392308[16] = 0.0;
   out_1512473366161392308[17] = 0.0;
   out_1512473366161392308[18] = 0.0;
   out_1512473366161392308[19] = 1.0;
   out_1512473366161392308[20] = 0.0;
   out_1512473366161392308[21] = 0.0;
   out_1512473366161392308[22] = 0.0;
   out_1512473366161392308[23] = 0.0;
   out_1512473366161392308[24] = 0.0;
   out_1512473366161392308[25] = 0.0;
   out_1512473366161392308[26] = 0.0;
   out_1512473366161392308[27] = 0.0;
   out_1512473366161392308[28] = 0.0;
   out_1512473366161392308[29] = 0.0;
   out_1512473366161392308[30] = 0.0;
   out_1512473366161392308[31] = 0.0;
   out_1512473366161392308[32] = 0.0;
   out_1512473366161392308[33] = 0.0;
   out_1512473366161392308[34] = 0.0;
   out_1512473366161392308[35] = 0.0;
   out_1512473366161392308[36] = 0.0;
   out_1512473366161392308[37] = 0.0;
   out_1512473366161392308[38] = 1.0;
   out_1512473366161392308[39] = 0.0;
   out_1512473366161392308[40] = 0.0;
   out_1512473366161392308[41] = 0.0;
   out_1512473366161392308[42] = 0.0;
   out_1512473366161392308[43] = 0.0;
   out_1512473366161392308[44] = 0.0;
   out_1512473366161392308[45] = 0.0;
   out_1512473366161392308[46] = 0.0;
   out_1512473366161392308[47] = 0.0;
   out_1512473366161392308[48] = 0.0;
   out_1512473366161392308[49] = 0.0;
   out_1512473366161392308[50] = 0.0;
   out_1512473366161392308[51] = 0.0;
   out_1512473366161392308[52] = 0.0;
   out_1512473366161392308[53] = 0.0;
   out_1512473366161392308[54] = 0.0;
   out_1512473366161392308[55] = 0.0;
   out_1512473366161392308[56] = 0.0;
   out_1512473366161392308[57] = 1.0;
   out_1512473366161392308[58] = 0.0;
   out_1512473366161392308[59] = 0.0;
   out_1512473366161392308[60] = 0.0;
   out_1512473366161392308[61] = 0.0;
   out_1512473366161392308[62] = 0.0;
   out_1512473366161392308[63] = 0.0;
   out_1512473366161392308[64] = 0.0;
   out_1512473366161392308[65] = 0.0;
   out_1512473366161392308[66] = 0.0;
   out_1512473366161392308[67] = 0.0;
   out_1512473366161392308[68] = 0.0;
   out_1512473366161392308[69] = 0.0;
   out_1512473366161392308[70] = 0.0;
   out_1512473366161392308[71] = 0.0;
   out_1512473366161392308[72] = 0.0;
   out_1512473366161392308[73] = 0.0;
   out_1512473366161392308[74] = 0.0;
   out_1512473366161392308[75] = 0.0;
   out_1512473366161392308[76] = 1.0;
   out_1512473366161392308[77] = 0.0;
   out_1512473366161392308[78] = 0.0;
   out_1512473366161392308[79] = 0.0;
   out_1512473366161392308[80] = 0.0;
   out_1512473366161392308[81] = 0.0;
   out_1512473366161392308[82] = 0.0;
   out_1512473366161392308[83] = 0.0;
   out_1512473366161392308[84] = 0.0;
   out_1512473366161392308[85] = 0.0;
   out_1512473366161392308[86] = 0.0;
   out_1512473366161392308[87] = 0.0;
   out_1512473366161392308[88] = 0.0;
   out_1512473366161392308[89] = 0.0;
   out_1512473366161392308[90] = 0.0;
   out_1512473366161392308[91] = 0.0;
   out_1512473366161392308[92] = 0.0;
   out_1512473366161392308[93] = 0.0;
   out_1512473366161392308[94] = 0.0;
   out_1512473366161392308[95] = 1.0;
   out_1512473366161392308[96] = 0.0;
   out_1512473366161392308[97] = 0.0;
   out_1512473366161392308[98] = 0.0;
   out_1512473366161392308[99] = 0.0;
   out_1512473366161392308[100] = 0.0;
   out_1512473366161392308[101] = 0.0;
   out_1512473366161392308[102] = 0.0;
   out_1512473366161392308[103] = 0.0;
   out_1512473366161392308[104] = 0.0;
   out_1512473366161392308[105] = 0.0;
   out_1512473366161392308[106] = 0.0;
   out_1512473366161392308[107] = 0.0;
   out_1512473366161392308[108] = 0.0;
   out_1512473366161392308[109] = 0.0;
   out_1512473366161392308[110] = 0.0;
   out_1512473366161392308[111] = 0.0;
   out_1512473366161392308[112] = 0.0;
   out_1512473366161392308[113] = 0.0;
   out_1512473366161392308[114] = 1.0;
   out_1512473366161392308[115] = 0.0;
   out_1512473366161392308[116] = 0.0;
   out_1512473366161392308[117] = 0.0;
   out_1512473366161392308[118] = 0.0;
   out_1512473366161392308[119] = 0.0;
   out_1512473366161392308[120] = 0.0;
   out_1512473366161392308[121] = 0.0;
   out_1512473366161392308[122] = 0.0;
   out_1512473366161392308[123] = 0.0;
   out_1512473366161392308[124] = 0.0;
   out_1512473366161392308[125] = 0.0;
   out_1512473366161392308[126] = 0.0;
   out_1512473366161392308[127] = 0.0;
   out_1512473366161392308[128] = 0.0;
   out_1512473366161392308[129] = 0.0;
   out_1512473366161392308[130] = 0.0;
   out_1512473366161392308[131] = 0.0;
   out_1512473366161392308[132] = 0.0;
   out_1512473366161392308[133] = 1.0;
   out_1512473366161392308[134] = 0.0;
   out_1512473366161392308[135] = 0.0;
   out_1512473366161392308[136] = 0.0;
   out_1512473366161392308[137] = 0.0;
   out_1512473366161392308[138] = 0.0;
   out_1512473366161392308[139] = 0.0;
   out_1512473366161392308[140] = 0.0;
   out_1512473366161392308[141] = 0.0;
   out_1512473366161392308[142] = 0.0;
   out_1512473366161392308[143] = 0.0;
   out_1512473366161392308[144] = 0.0;
   out_1512473366161392308[145] = 0.0;
   out_1512473366161392308[146] = 0.0;
   out_1512473366161392308[147] = 0.0;
   out_1512473366161392308[148] = 0.0;
   out_1512473366161392308[149] = 0.0;
   out_1512473366161392308[150] = 0.0;
   out_1512473366161392308[151] = 0.0;
   out_1512473366161392308[152] = 1.0;
   out_1512473366161392308[153] = 0.0;
   out_1512473366161392308[154] = 0.0;
   out_1512473366161392308[155] = 0.0;
   out_1512473366161392308[156] = 0.0;
   out_1512473366161392308[157] = 0.0;
   out_1512473366161392308[158] = 0.0;
   out_1512473366161392308[159] = 0.0;
   out_1512473366161392308[160] = 0.0;
   out_1512473366161392308[161] = 0.0;
   out_1512473366161392308[162] = 0.0;
   out_1512473366161392308[163] = 0.0;
   out_1512473366161392308[164] = 0.0;
   out_1512473366161392308[165] = 0.0;
   out_1512473366161392308[166] = 0.0;
   out_1512473366161392308[167] = 0.0;
   out_1512473366161392308[168] = 0.0;
   out_1512473366161392308[169] = 0.0;
   out_1512473366161392308[170] = 0.0;
   out_1512473366161392308[171] = 1.0;
   out_1512473366161392308[172] = 0.0;
   out_1512473366161392308[173] = 0.0;
   out_1512473366161392308[174] = 0.0;
   out_1512473366161392308[175] = 0.0;
   out_1512473366161392308[176] = 0.0;
   out_1512473366161392308[177] = 0.0;
   out_1512473366161392308[178] = 0.0;
   out_1512473366161392308[179] = 0.0;
   out_1512473366161392308[180] = 0.0;
   out_1512473366161392308[181] = 0.0;
   out_1512473366161392308[182] = 0.0;
   out_1512473366161392308[183] = 0.0;
   out_1512473366161392308[184] = 0.0;
   out_1512473366161392308[185] = 0.0;
   out_1512473366161392308[186] = 0.0;
   out_1512473366161392308[187] = 0.0;
   out_1512473366161392308[188] = 0.0;
   out_1512473366161392308[189] = 0.0;
   out_1512473366161392308[190] = 1.0;
   out_1512473366161392308[191] = 0.0;
   out_1512473366161392308[192] = 0.0;
   out_1512473366161392308[193] = 0.0;
   out_1512473366161392308[194] = 0.0;
   out_1512473366161392308[195] = 0.0;
   out_1512473366161392308[196] = 0.0;
   out_1512473366161392308[197] = 0.0;
   out_1512473366161392308[198] = 0.0;
   out_1512473366161392308[199] = 0.0;
   out_1512473366161392308[200] = 0.0;
   out_1512473366161392308[201] = 0.0;
   out_1512473366161392308[202] = 0.0;
   out_1512473366161392308[203] = 0.0;
   out_1512473366161392308[204] = 0.0;
   out_1512473366161392308[205] = 0.0;
   out_1512473366161392308[206] = 0.0;
   out_1512473366161392308[207] = 0.0;
   out_1512473366161392308[208] = 0.0;
   out_1512473366161392308[209] = 1.0;
   out_1512473366161392308[210] = 0.0;
   out_1512473366161392308[211] = 0.0;
   out_1512473366161392308[212] = 0.0;
   out_1512473366161392308[213] = 0.0;
   out_1512473366161392308[214] = 0.0;
   out_1512473366161392308[215] = 0.0;
   out_1512473366161392308[216] = 0.0;
   out_1512473366161392308[217] = 0.0;
   out_1512473366161392308[218] = 0.0;
   out_1512473366161392308[219] = 0.0;
   out_1512473366161392308[220] = 0.0;
   out_1512473366161392308[221] = 0.0;
   out_1512473366161392308[222] = 0.0;
   out_1512473366161392308[223] = 0.0;
   out_1512473366161392308[224] = 0.0;
   out_1512473366161392308[225] = 0.0;
   out_1512473366161392308[226] = 0.0;
   out_1512473366161392308[227] = 0.0;
   out_1512473366161392308[228] = 1.0;
   out_1512473366161392308[229] = 0.0;
   out_1512473366161392308[230] = 0.0;
   out_1512473366161392308[231] = 0.0;
   out_1512473366161392308[232] = 0.0;
   out_1512473366161392308[233] = 0.0;
   out_1512473366161392308[234] = 0.0;
   out_1512473366161392308[235] = 0.0;
   out_1512473366161392308[236] = 0.0;
   out_1512473366161392308[237] = 0.0;
   out_1512473366161392308[238] = 0.0;
   out_1512473366161392308[239] = 0.0;
   out_1512473366161392308[240] = 0.0;
   out_1512473366161392308[241] = 0.0;
   out_1512473366161392308[242] = 0.0;
   out_1512473366161392308[243] = 0.0;
   out_1512473366161392308[244] = 0.0;
   out_1512473366161392308[245] = 0.0;
   out_1512473366161392308[246] = 0.0;
   out_1512473366161392308[247] = 1.0;
   out_1512473366161392308[248] = 0.0;
   out_1512473366161392308[249] = 0.0;
   out_1512473366161392308[250] = 0.0;
   out_1512473366161392308[251] = 0.0;
   out_1512473366161392308[252] = 0.0;
   out_1512473366161392308[253] = 0.0;
   out_1512473366161392308[254] = 0.0;
   out_1512473366161392308[255] = 0.0;
   out_1512473366161392308[256] = 0.0;
   out_1512473366161392308[257] = 0.0;
   out_1512473366161392308[258] = 0.0;
   out_1512473366161392308[259] = 0.0;
   out_1512473366161392308[260] = 0.0;
   out_1512473366161392308[261] = 0.0;
   out_1512473366161392308[262] = 0.0;
   out_1512473366161392308[263] = 0.0;
   out_1512473366161392308[264] = 0.0;
   out_1512473366161392308[265] = 0.0;
   out_1512473366161392308[266] = 1.0;
   out_1512473366161392308[267] = 0.0;
   out_1512473366161392308[268] = 0.0;
   out_1512473366161392308[269] = 0.0;
   out_1512473366161392308[270] = 0.0;
   out_1512473366161392308[271] = 0.0;
   out_1512473366161392308[272] = 0.0;
   out_1512473366161392308[273] = 0.0;
   out_1512473366161392308[274] = 0.0;
   out_1512473366161392308[275] = 0.0;
   out_1512473366161392308[276] = 0.0;
   out_1512473366161392308[277] = 0.0;
   out_1512473366161392308[278] = 0.0;
   out_1512473366161392308[279] = 0.0;
   out_1512473366161392308[280] = 0.0;
   out_1512473366161392308[281] = 0.0;
   out_1512473366161392308[282] = 0.0;
   out_1512473366161392308[283] = 0.0;
   out_1512473366161392308[284] = 0.0;
   out_1512473366161392308[285] = 1.0;
   out_1512473366161392308[286] = 0.0;
   out_1512473366161392308[287] = 0.0;
   out_1512473366161392308[288] = 0.0;
   out_1512473366161392308[289] = 0.0;
   out_1512473366161392308[290] = 0.0;
   out_1512473366161392308[291] = 0.0;
   out_1512473366161392308[292] = 0.0;
   out_1512473366161392308[293] = 0.0;
   out_1512473366161392308[294] = 0.0;
   out_1512473366161392308[295] = 0.0;
   out_1512473366161392308[296] = 0.0;
   out_1512473366161392308[297] = 0.0;
   out_1512473366161392308[298] = 0.0;
   out_1512473366161392308[299] = 0.0;
   out_1512473366161392308[300] = 0.0;
   out_1512473366161392308[301] = 0.0;
   out_1512473366161392308[302] = 0.0;
   out_1512473366161392308[303] = 0.0;
   out_1512473366161392308[304] = 1.0;
   out_1512473366161392308[305] = 0.0;
   out_1512473366161392308[306] = 0.0;
   out_1512473366161392308[307] = 0.0;
   out_1512473366161392308[308] = 0.0;
   out_1512473366161392308[309] = 0.0;
   out_1512473366161392308[310] = 0.0;
   out_1512473366161392308[311] = 0.0;
   out_1512473366161392308[312] = 0.0;
   out_1512473366161392308[313] = 0.0;
   out_1512473366161392308[314] = 0.0;
   out_1512473366161392308[315] = 0.0;
   out_1512473366161392308[316] = 0.0;
   out_1512473366161392308[317] = 0.0;
   out_1512473366161392308[318] = 0.0;
   out_1512473366161392308[319] = 0.0;
   out_1512473366161392308[320] = 0.0;
   out_1512473366161392308[321] = 0.0;
   out_1512473366161392308[322] = 0.0;
   out_1512473366161392308[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_7813170452072968754) {
   out_7813170452072968754[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_7813170452072968754[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_7813170452072968754[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_7813170452072968754[3] = dt*state[12] + state[3];
   out_7813170452072968754[4] = dt*state[13] + state[4];
   out_7813170452072968754[5] = dt*state[14] + state[5];
   out_7813170452072968754[6] = state[6];
   out_7813170452072968754[7] = state[7];
   out_7813170452072968754[8] = state[8];
   out_7813170452072968754[9] = state[9];
   out_7813170452072968754[10] = state[10];
   out_7813170452072968754[11] = state[11];
   out_7813170452072968754[12] = state[12];
   out_7813170452072968754[13] = state[13];
   out_7813170452072968754[14] = state[14];
   out_7813170452072968754[15] = state[15];
   out_7813170452072968754[16] = state[16];
   out_7813170452072968754[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5083828130456064396) {
   out_5083828130456064396[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5083828130456064396[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5083828130456064396[2] = 0;
   out_5083828130456064396[3] = 0;
   out_5083828130456064396[4] = 0;
   out_5083828130456064396[5] = 0;
   out_5083828130456064396[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5083828130456064396[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5083828130456064396[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5083828130456064396[9] = 0;
   out_5083828130456064396[10] = 0;
   out_5083828130456064396[11] = 0;
   out_5083828130456064396[12] = 0;
   out_5083828130456064396[13] = 0;
   out_5083828130456064396[14] = 0;
   out_5083828130456064396[15] = 0;
   out_5083828130456064396[16] = 0;
   out_5083828130456064396[17] = 0;
   out_5083828130456064396[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5083828130456064396[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5083828130456064396[20] = 0;
   out_5083828130456064396[21] = 0;
   out_5083828130456064396[22] = 0;
   out_5083828130456064396[23] = 0;
   out_5083828130456064396[24] = 0;
   out_5083828130456064396[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5083828130456064396[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5083828130456064396[27] = 0;
   out_5083828130456064396[28] = 0;
   out_5083828130456064396[29] = 0;
   out_5083828130456064396[30] = 0;
   out_5083828130456064396[31] = 0;
   out_5083828130456064396[32] = 0;
   out_5083828130456064396[33] = 0;
   out_5083828130456064396[34] = 0;
   out_5083828130456064396[35] = 0;
   out_5083828130456064396[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5083828130456064396[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5083828130456064396[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5083828130456064396[39] = 0;
   out_5083828130456064396[40] = 0;
   out_5083828130456064396[41] = 0;
   out_5083828130456064396[42] = 0;
   out_5083828130456064396[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5083828130456064396[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5083828130456064396[45] = 0;
   out_5083828130456064396[46] = 0;
   out_5083828130456064396[47] = 0;
   out_5083828130456064396[48] = 0;
   out_5083828130456064396[49] = 0;
   out_5083828130456064396[50] = 0;
   out_5083828130456064396[51] = 0;
   out_5083828130456064396[52] = 0;
   out_5083828130456064396[53] = 0;
   out_5083828130456064396[54] = 0;
   out_5083828130456064396[55] = 0;
   out_5083828130456064396[56] = 0;
   out_5083828130456064396[57] = 1;
   out_5083828130456064396[58] = 0;
   out_5083828130456064396[59] = 0;
   out_5083828130456064396[60] = 0;
   out_5083828130456064396[61] = 0;
   out_5083828130456064396[62] = 0;
   out_5083828130456064396[63] = 0;
   out_5083828130456064396[64] = 0;
   out_5083828130456064396[65] = 0;
   out_5083828130456064396[66] = dt;
   out_5083828130456064396[67] = 0;
   out_5083828130456064396[68] = 0;
   out_5083828130456064396[69] = 0;
   out_5083828130456064396[70] = 0;
   out_5083828130456064396[71] = 0;
   out_5083828130456064396[72] = 0;
   out_5083828130456064396[73] = 0;
   out_5083828130456064396[74] = 0;
   out_5083828130456064396[75] = 0;
   out_5083828130456064396[76] = 1;
   out_5083828130456064396[77] = 0;
   out_5083828130456064396[78] = 0;
   out_5083828130456064396[79] = 0;
   out_5083828130456064396[80] = 0;
   out_5083828130456064396[81] = 0;
   out_5083828130456064396[82] = 0;
   out_5083828130456064396[83] = 0;
   out_5083828130456064396[84] = 0;
   out_5083828130456064396[85] = dt;
   out_5083828130456064396[86] = 0;
   out_5083828130456064396[87] = 0;
   out_5083828130456064396[88] = 0;
   out_5083828130456064396[89] = 0;
   out_5083828130456064396[90] = 0;
   out_5083828130456064396[91] = 0;
   out_5083828130456064396[92] = 0;
   out_5083828130456064396[93] = 0;
   out_5083828130456064396[94] = 0;
   out_5083828130456064396[95] = 1;
   out_5083828130456064396[96] = 0;
   out_5083828130456064396[97] = 0;
   out_5083828130456064396[98] = 0;
   out_5083828130456064396[99] = 0;
   out_5083828130456064396[100] = 0;
   out_5083828130456064396[101] = 0;
   out_5083828130456064396[102] = 0;
   out_5083828130456064396[103] = 0;
   out_5083828130456064396[104] = dt;
   out_5083828130456064396[105] = 0;
   out_5083828130456064396[106] = 0;
   out_5083828130456064396[107] = 0;
   out_5083828130456064396[108] = 0;
   out_5083828130456064396[109] = 0;
   out_5083828130456064396[110] = 0;
   out_5083828130456064396[111] = 0;
   out_5083828130456064396[112] = 0;
   out_5083828130456064396[113] = 0;
   out_5083828130456064396[114] = 1;
   out_5083828130456064396[115] = 0;
   out_5083828130456064396[116] = 0;
   out_5083828130456064396[117] = 0;
   out_5083828130456064396[118] = 0;
   out_5083828130456064396[119] = 0;
   out_5083828130456064396[120] = 0;
   out_5083828130456064396[121] = 0;
   out_5083828130456064396[122] = 0;
   out_5083828130456064396[123] = 0;
   out_5083828130456064396[124] = 0;
   out_5083828130456064396[125] = 0;
   out_5083828130456064396[126] = 0;
   out_5083828130456064396[127] = 0;
   out_5083828130456064396[128] = 0;
   out_5083828130456064396[129] = 0;
   out_5083828130456064396[130] = 0;
   out_5083828130456064396[131] = 0;
   out_5083828130456064396[132] = 0;
   out_5083828130456064396[133] = 1;
   out_5083828130456064396[134] = 0;
   out_5083828130456064396[135] = 0;
   out_5083828130456064396[136] = 0;
   out_5083828130456064396[137] = 0;
   out_5083828130456064396[138] = 0;
   out_5083828130456064396[139] = 0;
   out_5083828130456064396[140] = 0;
   out_5083828130456064396[141] = 0;
   out_5083828130456064396[142] = 0;
   out_5083828130456064396[143] = 0;
   out_5083828130456064396[144] = 0;
   out_5083828130456064396[145] = 0;
   out_5083828130456064396[146] = 0;
   out_5083828130456064396[147] = 0;
   out_5083828130456064396[148] = 0;
   out_5083828130456064396[149] = 0;
   out_5083828130456064396[150] = 0;
   out_5083828130456064396[151] = 0;
   out_5083828130456064396[152] = 1;
   out_5083828130456064396[153] = 0;
   out_5083828130456064396[154] = 0;
   out_5083828130456064396[155] = 0;
   out_5083828130456064396[156] = 0;
   out_5083828130456064396[157] = 0;
   out_5083828130456064396[158] = 0;
   out_5083828130456064396[159] = 0;
   out_5083828130456064396[160] = 0;
   out_5083828130456064396[161] = 0;
   out_5083828130456064396[162] = 0;
   out_5083828130456064396[163] = 0;
   out_5083828130456064396[164] = 0;
   out_5083828130456064396[165] = 0;
   out_5083828130456064396[166] = 0;
   out_5083828130456064396[167] = 0;
   out_5083828130456064396[168] = 0;
   out_5083828130456064396[169] = 0;
   out_5083828130456064396[170] = 0;
   out_5083828130456064396[171] = 1;
   out_5083828130456064396[172] = 0;
   out_5083828130456064396[173] = 0;
   out_5083828130456064396[174] = 0;
   out_5083828130456064396[175] = 0;
   out_5083828130456064396[176] = 0;
   out_5083828130456064396[177] = 0;
   out_5083828130456064396[178] = 0;
   out_5083828130456064396[179] = 0;
   out_5083828130456064396[180] = 0;
   out_5083828130456064396[181] = 0;
   out_5083828130456064396[182] = 0;
   out_5083828130456064396[183] = 0;
   out_5083828130456064396[184] = 0;
   out_5083828130456064396[185] = 0;
   out_5083828130456064396[186] = 0;
   out_5083828130456064396[187] = 0;
   out_5083828130456064396[188] = 0;
   out_5083828130456064396[189] = 0;
   out_5083828130456064396[190] = 1;
   out_5083828130456064396[191] = 0;
   out_5083828130456064396[192] = 0;
   out_5083828130456064396[193] = 0;
   out_5083828130456064396[194] = 0;
   out_5083828130456064396[195] = 0;
   out_5083828130456064396[196] = 0;
   out_5083828130456064396[197] = 0;
   out_5083828130456064396[198] = 0;
   out_5083828130456064396[199] = 0;
   out_5083828130456064396[200] = 0;
   out_5083828130456064396[201] = 0;
   out_5083828130456064396[202] = 0;
   out_5083828130456064396[203] = 0;
   out_5083828130456064396[204] = 0;
   out_5083828130456064396[205] = 0;
   out_5083828130456064396[206] = 0;
   out_5083828130456064396[207] = 0;
   out_5083828130456064396[208] = 0;
   out_5083828130456064396[209] = 1;
   out_5083828130456064396[210] = 0;
   out_5083828130456064396[211] = 0;
   out_5083828130456064396[212] = 0;
   out_5083828130456064396[213] = 0;
   out_5083828130456064396[214] = 0;
   out_5083828130456064396[215] = 0;
   out_5083828130456064396[216] = 0;
   out_5083828130456064396[217] = 0;
   out_5083828130456064396[218] = 0;
   out_5083828130456064396[219] = 0;
   out_5083828130456064396[220] = 0;
   out_5083828130456064396[221] = 0;
   out_5083828130456064396[222] = 0;
   out_5083828130456064396[223] = 0;
   out_5083828130456064396[224] = 0;
   out_5083828130456064396[225] = 0;
   out_5083828130456064396[226] = 0;
   out_5083828130456064396[227] = 0;
   out_5083828130456064396[228] = 1;
   out_5083828130456064396[229] = 0;
   out_5083828130456064396[230] = 0;
   out_5083828130456064396[231] = 0;
   out_5083828130456064396[232] = 0;
   out_5083828130456064396[233] = 0;
   out_5083828130456064396[234] = 0;
   out_5083828130456064396[235] = 0;
   out_5083828130456064396[236] = 0;
   out_5083828130456064396[237] = 0;
   out_5083828130456064396[238] = 0;
   out_5083828130456064396[239] = 0;
   out_5083828130456064396[240] = 0;
   out_5083828130456064396[241] = 0;
   out_5083828130456064396[242] = 0;
   out_5083828130456064396[243] = 0;
   out_5083828130456064396[244] = 0;
   out_5083828130456064396[245] = 0;
   out_5083828130456064396[246] = 0;
   out_5083828130456064396[247] = 1;
   out_5083828130456064396[248] = 0;
   out_5083828130456064396[249] = 0;
   out_5083828130456064396[250] = 0;
   out_5083828130456064396[251] = 0;
   out_5083828130456064396[252] = 0;
   out_5083828130456064396[253] = 0;
   out_5083828130456064396[254] = 0;
   out_5083828130456064396[255] = 0;
   out_5083828130456064396[256] = 0;
   out_5083828130456064396[257] = 0;
   out_5083828130456064396[258] = 0;
   out_5083828130456064396[259] = 0;
   out_5083828130456064396[260] = 0;
   out_5083828130456064396[261] = 0;
   out_5083828130456064396[262] = 0;
   out_5083828130456064396[263] = 0;
   out_5083828130456064396[264] = 0;
   out_5083828130456064396[265] = 0;
   out_5083828130456064396[266] = 1;
   out_5083828130456064396[267] = 0;
   out_5083828130456064396[268] = 0;
   out_5083828130456064396[269] = 0;
   out_5083828130456064396[270] = 0;
   out_5083828130456064396[271] = 0;
   out_5083828130456064396[272] = 0;
   out_5083828130456064396[273] = 0;
   out_5083828130456064396[274] = 0;
   out_5083828130456064396[275] = 0;
   out_5083828130456064396[276] = 0;
   out_5083828130456064396[277] = 0;
   out_5083828130456064396[278] = 0;
   out_5083828130456064396[279] = 0;
   out_5083828130456064396[280] = 0;
   out_5083828130456064396[281] = 0;
   out_5083828130456064396[282] = 0;
   out_5083828130456064396[283] = 0;
   out_5083828130456064396[284] = 0;
   out_5083828130456064396[285] = 1;
   out_5083828130456064396[286] = 0;
   out_5083828130456064396[287] = 0;
   out_5083828130456064396[288] = 0;
   out_5083828130456064396[289] = 0;
   out_5083828130456064396[290] = 0;
   out_5083828130456064396[291] = 0;
   out_5083828130456064396[292] = 0;
   out_5083828130456064396[293] = 0;
   out_5083828130456064396[294] = 0;
   out_5083828130456064396[295] = 0;
   out_5083828130456064396[296] = 0;
   out_5083828130456064396[297] = 0;
   out_5083828130456064396[298] = 0;
   out_5083828130456064396[299] = 0;
   out_5083828130456064396[300] = 0;
   out_5083828130456064396[301] = 0;
   out_5083828130456064396[302] = 0;
   out_5083828130456064396[303] = 0;
   out_5083828130456064396[304] = 1;
   out_5083828130456064396[305] = 0;
   out_5083828130456064396[306] = 0;
   out_5083828130456064396[307] = 0;
   out_5083828130456064396[308] = 0;
   out_5083828130456064396[309] = 0;
   out_5083828130456064396[310] = 0;
   out_5083828130456064396[311] = 0;
   out_5083828130456064396[312] = 0;
   out_5083828130456064396[313] = 0;
   out_5083828130456064396[314] = 0;
   out_5083828130456064396[315] = 0;
   out_5083828130456064396[316] = 0;
   out_5083828130456064396[317] = 0;
   out_5083828130456064396[318] = 0;
   out_5083828130456064396[319] = 0;
   out_5083828130456064396[320] = 0;
   out_5083828130456064396[321] = 0;
   out_5083828130456064396[322] = 0;
   out_5083828130456064396[323] = 1;
}
void h_4(double *state, double *unused, double *out_8720432154848991493) {
   out_8720432154848991493[0] = state[6] + state[9];
   out_8720432154848991493[1] = state[7] + state[10];
   out_8720432154848991493[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4091132023239463575) {
   out_4091132023239463575[0] = 0;
   out_4091132023239463575[1] = 0;
   out_4091132023239463575[2] = 0;
   out_4091132023239463575[3] = 0;
   out_4091132023239463575[4] = 0;
   out_4091132023239463575[5] = 0;
   out_4091132023239463575[6] = 1;
   out_4091132023239463575[7] = 0;
   out_4091132023239463575[8] = 0;
   out_4091132023239463575[9] = 1;
   out_4091132023239463575[10] = 0;
   out_4091132023239463575[11] = 0;
   out_4091132023239463575[12] = 0;
   out_4091132023239463575[13] = 0;
   out_4091132023239463575[14] = 0;
   out_4091132023239463575[15] = 0;
   out_4091132023239463575[16] = 0;
   out_4091132023239463575[17] = 0;
   out_4091132023239463575[18] = 0;
   out_4091132023239463575[19] = 0;
   out_4091132023239463575[20] = 0;
   out_4091132023239463575[21] = 0;
   out_4091132023239463575[22] = 0;
   out_4091132023239463575[23] = 0;
   out_4091132023239463575[24] = 0;
   out_4091132023239463575[25] = 1;
   out_4091132023239463575[26] = 0;
   out_4091132023239463575[27] = 0;
   out_4091132023239463575[28] = 1;
   out_4091132023239463575[29] = 0;
   out_4091132023239463575[30] = 0;
   out_4091132023239463575[31] = 0;
   out_4091132023239463575[32] = 0;
   out_4091132023239463575[33] = 0;
   out_4091132023239463575[34] = 0;
   out_4091132023239463575[35] = 0;
   out_4091132023239463575[36] = 0;
   out_4091132023239463575[37] = 0;
   out_4091132023239463575[38] = 0;
   out_4091132023239463575[39] = 0;
   out_4091132023239463575[40] = 0;
   out_4091132023239463575[41] = 0;
   out_4091132023239463575[42] = 0;
   out_4091132023239463575[43] = 0;
   out_4091132023239463575[44] = 1;
   out_4091132023239463575[45] = 0;
   out_4091132023239463575[46] = 0;
   out_4091132023239463575[47] = 1;
   out_4091132023239463575[48] = 0;
   out_4091132023239463575[49] = 0;
   out_4091132023239463575[50] = 0;
   out_4091132023239463575[51] = 0;
   out_4091132023239463575[52] = 0;
   out_4091132023239463575[53] = 0;
}
void h_10(double *state, double *unused, double *out_682446449180910309) {
   out_682446449180910309[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_682446449180910309[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_682446449180910309[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_4919001356891757040) {
   out_4919001356891757040[0] = 0;
   out_4919001356891757040[1] = 9.8100000000000005*cos(state[1]);
   out_4919001356891757040[2] = 0;
   out_4919001356891757040[3] = 0;
   out_4919001356891757040[4] = -state[8];
   out_4919001356891757040[5] = state[7];
   out_4919001356891757040[6] = 0;
   out_4919001356891757040[7] = state[5];
   out_4919001356891757040[8] = -state[4];
   out_4919001356891757040[9] = 0;
   out_4919001356891757040[10] = 0;
   out_4919001356891757040[11] = 0;
   out_4919001356891757040[12] = 1;
   out_4919001356891757040[13] = 0;
   out_4919001356891757040[14] = 0;
   out_4919001356891757040[15] = 1;
   out_4919001356891757040[16] = 0;
   out_4919001356891757040[17] = 0;
   out_4919001356891757040[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_4919001356891757040[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_4919001356891757040[20] = 0;
   out_4919001356891757040[21] = state[8];
   out_4919001356891757040[22] = 0;
   out_4919001356891757040[23] = -state[6];
   out_4919001356891757040[24] = -state[5];
   out_4919001356891757040[25] = 0;
   out_4919001356891757040[26] = state[3];
   out_4919001356891757040[27] = 0;
   out_4919001356891757040[28] = 0;
   out_4919001356891757040[29] = 0;
   out_4919001356891757040[30] = 0;
   out_4919001356891757040[31] = 1;
   out_4919001356891757040[32] = 0;
   out_4919001356891757040[33] = 0;
   out_4919001356891757040[34] = 1;
   out_4919001356891757040[35] = 0;
   out_4919001356891757040[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_4919001356891757040[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_4919001356891757040[38] = 0;
   out_4919001356891757040[39] = -state[7];
   out_4919001356891757040[40] = state[6];
   out_4919001356891757040[41] = 0;
   out_4919001356891757040[42] = state[4];
   out_4919001356891757040[43] = -state[3];
   out_4919001356891757040[44] = 0;
   out_4919001356891757040[45] = 0;
   out_4919001356891757040[46] = 0;
   out_4919001356891757040[47] = 0;
   out_4919001356891757040[48] = 0;
   out_4919001356891757040[49] = 0;
   out_4919001356891757040[50] = 1;
   out_4919001356891757040[51] = 0;
   out_4919001356891757040[52] = 0;
   out_4919001356891757040[53] = 1;
}
void h_13(double *state, double *unused, double *out_2860834984953274042) {
   out_2860834984953274042[0] = state[3];
   out_2860834984953274042[1] = state[4];
   out_2860834984953274042[2] = state[5];
}
void H_13(double *state, double *unused, double *out_7303405848571796376) {
   out_7303405848571796376[0] = 0;
   out_7303405848571796376[1] = 0;
   out_7303405848571796376[2] = 0;
   out_7303405848571796376[3] = 1;
   out_7303405848571796376[4] = 0;
   out_7303405848571796376[5] = 0;
   out_7303405848571796376[6] = 0;
   out_7303405848571796376[7] = 0;
   out_7303405848571796376[8] = 0;
   out_7303405848571796376[9] = 0;
   out_7303405848571796376[10] = 0;
   out_7303405848571796376[11] = 0;
   out_7303405848571796376[12] = 0;
   out_7303405848571796376[13] = 0;
   out_7303405848571796376[14] = 0;
   out_7303405848571796376[15] = 0;
   out_7303405848571796376[16] = 0;
   out_7303405848571796376[17] = 0;
   out_7303405848571796376[18] = 0;
   out_7303405848571796376[19] = 0;
   out_7303405848571796376[20] = 0;
   out_7303405848571796376[21] = 0;
   out_7303405848571796376[22] = 1;
   out_7303405848571796376[23] = 0;
   out_7303405848571796376[24] = 0;
   out_7303405848571796376[25] = 0;
   out_7303405848571796376[26] = 0;
   out_7303405848571796376[27] = 0;
   out_7303405848571796376[28] = 0;
   out_7303405848571796376[29] = 0;
   out_7303405848571796376[30] = 0;
   out_7303405848571796376[31] = 0;
   out_7303405848571796376[32] = 0;
   out_7303405848571796376[33] = 0;
   out_7303405848571796376[34] = 0;
   out_7303405848571796376[35] = 0;
   out_7303405848571796376[36] = 0;
   out_7303405848571796376[37] = 0;
   out_7303405848571796376[38] = 0;
   out_7303405848571796376[39] = 0;
   out_7303405848571796376[40] = 0;
   out_7303405848571796376[41] = 1;
   out_7303405848571796376[42] = 0;
   out_7303405848571796376[43] = 0;
   out_7303405848571796376[44] = 0;
   out_7303405848571796376[45] = 0;
   out_7303405848571796376[46] = 0;
   out_7303405848571796376[47] = 0;
   out_7303405848571796376[48] = 0;
   out_7303405848571796376[49] = 0;
   out_7303405848571796376[50] = 0;
   out_7303405848571796376[51] = 0;
   out_7303405848571796376[52] = 0;
   out_7303405848571796376[53] = 0;
}
void h_14(double *state, double *unused, double *out_6283645208607536870) {
   out_6283645208607536870[0] = state[6];
   out_6283645208607536870[1] = state[7];
   out_6283645208607536870[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1008343590944091279) {
   out_1008343590944091279[0] = 0;
   out_1008343590944091279[1] = 0;
   out_1008343590944091279[2] = 0;
   out_1008343590944091279[3] = 0;
   out_1008343590944091279[4] = 0;
   out_1008343590944091279[5] = 0;
   out_1008343590944091279[6] = 1;
   out_1008343590944091279[7] = 0;
   out_1008343590944091279[8] = 0;
   out_1008343590944091279[9] = 0;
   out_1008343590944091279[10] = 0;
   out_1008343590944091279[11] = 0;
   out_1008343590944091279[12] = 0;
   out_1008343590944091279[13] = 0;
   out_1008343590944091279[14] = 0;
   out_1008343590944091279[15] = 0;
   out_1008343590944091279[16] = 0;
   out_1008343590944091279[17] = 0;
   out_1008343590944091279[18] = 0;
   out_1008343590944091279[19] = 0;
   out_1008343590944091279[20] = 0;
   out_1008343590944091279[21] = 0;
   out_1008343590944091279[22] = 0;
   out_1008343590944091279[23] = 0;
   out_1008343590944091279[24] = 0;
   out_1008343590944091279[25] = 1;
   out_1008343590944091279[26] = 0;
   out_1008343590944091279[27] = 0;
   out_1008343590944091279[28] = 0;
   out_1008343590944091279[29] = 0;
   out_1008343590944091279[30] = 0;
   out_1008343590944091279[31] = 0;
   out_1008343590944091279[32] = 0;
   out_1008343590944091279[33] = 0;
   out_1008343590944091279[34] = 0;
   out_1008343590944091279[35] = 0;
   out_1008343590944091279[36] = 0;
   out_1008343590944091279[37] = 0;
   out_1008343590944091279[38] = 0;
   out_1008343590944091279[39] = 0;
   out_1008343590944091279[40] = 0;
   out_1008343590944091279[41] = 0;
   out_1008343590944091279[42] = 0;
   out_1008343590944091279[43] = 0;
   out_1008343590944091279[44] = 1;
   out_1008343590944091279[45] = 0;
   out_1008343590944091279[46] = 0;
   out_1008343590944091279[47] = 0;
   out_1008343590944091279[48] = 0;
   out_1008343590944091279[49] = 0;
   out_1008343590944091279[50] = 0;
   out_1008343590944091279[51] = 0;
   out_1008343590944091279[52] = 0;
   out_1008343590944091279[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_1308154946342484284) {
  err_fun(nom_x, delta_x, out_1308154946342484284);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8706500607592261698) {
  inv_err_fun(nom_x, true_x, out_8706500607592261698);
}
void pose_H_mod_fun(double *state, double *out_1512473366161392308) {
  H_mod_fun(state, out_1512473366161392308);
}
void pose_f_fun(double *state, double dt, double *out_7813170452072968754) {
  f_fun(state,  dt, out_7813170452072968754);
}
void pose_F_fun(double *state, double dt, double *out_5083828130456064396) {
  F_fun(state,  dt, out_5083828130456064396);
}
void pose_h_4(double *state, double *unused, double *out_8720432154848991493) {
  h_4(state, unused, out_8720432154848991493);
}
void pose_H_4(double *state, double *unused, double *out_4091132023239463575) {
  H_4(state, unused, out_4091132023239463575);
}
void pose_h_10(double *state, double *unused, double *out_682446449180910309) {
  h_10(state, unused, out_682446449180910309);
}
void pose_H_10(double *state, double *unused, double *out_4919001356891757040) {
  H_10(state, unused, out_4919001356891757040);
}
void pose_h_13(double *state, double *unused, double *out_2860834984953274042) {
  h_13(state, unused, out_2860834984953274042);
}
void pose_H_13(double *state, double *unused, double *out_7303405848571796376) {
  H_13(state, unused, out_7303405848571796376);
}
void pose_h_14(double *state, double *unused, double *out_6283645208607536870) {
  h_14(state, unused, out_6283645208607536870);
}
void pose_H_14(double *state, double *unused, double *out_1008343590944091279) {
  H_14(state, unused, out_1008343590944091279);
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
