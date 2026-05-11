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
void err_fun(double *nom_x, double *delta_x, double *out_4154280524256563890) {
   out_4154280524256563890[0] = delta_x[0] + nom_x[0];
   out_4154280524256563890[1] = delta_x[1] + nom_x[1];
   out_4154280524256563890[2] = delta_x[2] + nom_x[2];
   out_4154280524256563890[3] = delta_x[3] + nom_x[3];
   out_4154280524256563890[4] = delta_x[4] + nom_x[4];
   out_4154280524256563890[5] = delta_x[5] + nom_x[5];
   out_4154280524256563890[6] = delta_x[6] + nom_x[6];
   out_4154280524256563890[7] = delta_x[7] + nom_x[7];
   out_4154280524256563890[8] = delta_x[8] + nom_x[8];
   out_4154280524256563890[9] = delta_x[9] + nom_x[9];
   out_4154280524256563890[10] = delta_x[10] + nom_x[10];
   out_4154280524256563890[11] = delta_x[11] + nom_x[11];
   out_4154280524256563890[12] = delta_x[12] + nom_x[12];
   out_4154280524256563890[13] = delta_x[13] + nom_x[13];
   out_4154280524256563890[14] = delta_x[14] + nom_x[14];
   out_4154280524256563890[15] = delta_x[15] + nom_x[15];
   out_4154280524256563890[16] = delta_x[16] + nom_x[16];
   out_4154280524256563890[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5487211563177375728) {
   out_5487211563177375728[0] = -nom_x[0] + true_x[0];
   out_5487211563177375728[1] = -nom_x[1] + true_x[1];
   out_5487211563177375728[2] = -nom_x[2] + true_x[2];
   out_5487211563177375728[3] = -nom_x[3] + true_x[3];
   out_5487211563177375728[4] = -nom_x[4] + true_x[4];
   out_5487211563177375728[5] = -nom_x[5] + true_x[5];
   out_5487211563177375728[6] = -nom_x[6] + true_x[6];
   out_5487211563177375728[7] = -nom_x[7] + true_x[7];
   out_5487211563177375728[8] = -nom_x[8] + true_x[8];
   out_5487211563177375728[9] = -nom_x[9] + true_x[9];
   out_5487211563177375728[10] = -nom_x[10] + true_x[10];
   out_5487211563177375728[11] = -nom_x[11] + true_x[11];
   out_5487211563177375728[12] = -nom_x[12] + true_x[12];
   out_5487211563177375728[13] = -nom_x[13] + true_x[13];
   out_5487211563177375728[14] = -nom_x[14] + true_x[14];
   out_5487211563177375728[15] = -nom_x[15] + true_x[15];
   out_5487211563177375728[16] = -nom_x[16] + true_x[16];
   out_5487211563177375728[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_6762039440372011872) {
   out_6762039440372011872[0] = 1.0;
   out_6762039440372011872[1] = 0.0;
   out_6762039440372011872[2] = 0.0;
   out_6762039440372011872[3] = 0.0;
   out_6762039440372011872[4] = 0.0;
   out_6762039440372011872[5] = 0.0;
   out_6762039440372011872[6] = 0.0;
   out_6762039440372011872[7] = 0.0;
   out_6762039440372011872[8] = 0.0;
   out_6762039440372011872[9] = 0.0;
   out_6762039440372011872[10] = 0.0;
   out_6762039440372011872[11] = 0.0;
   out_6762039440372011872[12] = 0.0;
   out_6762039440372011872[13] = 0.0;
   out_6762039440372011872[14] = 0.0;
   out_6762039440372011872[15] = 0.0;
   out_6762039440372011872[16] = 0.0;
   out_6762039440372011872[17] = 0.0;
   out_6762039440372011872[18] = 0.0;
   out_6762039440372011872[19] = 1.0;
   out_6762039440372011872[20] = 0.0;
   out_6762039440372011872[21] = 0.0;
   out_6762039440372011872[22] = 0.0;
   out_6762039440372011872[23] = 0.0;
   out_6762039440372011872[24] = 0.0;
   out_6762039440372011872[25] = 0.0;
   out_6762039440372011872[26] = 0.0;
   out_6762039440372011872[27] = 0.0;
   out_6762039440372011872[28] = 0.0;
   out_6762039440372011872[29] = 0.0;
   out_6762039440372011872[30] = 0.0;
   out_6762039440372011872[31] = 0.0;
   out_6762039440372011872[32] = 0.0;
   out_6762039440372011872[33] = 0.0;
   out_6762039440372011872[34] = 0.0;
   out_6762039440372011872[35] = 0.0;
   out_6762039440372011872[36] = 0.0;
   out_6762039440372011872[37] = 0.0;
   out_6762039440372011872[38] = 1.0;
   out_6762039440372011872[39] = 0.0;
   out_6762039440372011872[40] = 0.0;
   out_6762039440372011872[41] = 0.0;
   out_6762039440372011872[42] = 0.0;
   out_6762039440372011872[43] = 0.0;
   out_6762039440372011872[44] = 0.0;
   out_6762039440372011872[45] = 0.0;
   out_6762039440372011872[46] = 0.0;
   out_6762039440372011872[47] = 0.0;
   out_6762039440372011872[48] = 0.0;
   out_6762039440372011872[49] = 0.0;
   out_6762039440372011872[50] = 0.0;
   out_6762039440372011872[51] = 0.0;
   out_6762039440372011872[52] = 0.0;
   out_6762039440372011872[53] = 0.0;
   out_6762039440372011872[54] = 0.0;
   out_6762039440372011872[55] = 0.0;
   out_6762039440372011872[56] = 0.0;
   out_6762039440372011872[57] = 1.0;
   out_6762039440372011872[58] = 0.0;
   out_6762039440372011872[59] = 0.0;
   out_6762039440372011872[60] = 0.0;
   out_6762039440372011872[61] = 0.0;
   out_6762039440372011872[62] = 0.0;
   out_6762039440372011872[63] = 0.0;
   out_6762039440372011872[64] = 0.0;
   out_6762039440372011872[65] = 0.0;
   out_6762039440372011872[66] = 0.0;
   out_6762039440372011872[67] = 0.0;
   out_6762039440372011872[68] = 0.0;
   out_6762039440372011872[69] = 0.0;
   out_6762039440372011872[70] = 0.0;
   out_6762039440372011872[71] = 0.0;
   out_6762039440372011872[72] = 0.0;
   out_6762039440372011872[73] = 0.0;
   out_6762039440372011872[74] = 0.0;
   out_6762039440372011872[75] = 0.0;
   out_6762039440372011872[76] = 1.0;
   out_6762039440372011872[77] = 0.0;
   out_6762039440372011872[78] = 0.0;
   out_6762039440372011872[79] = 0.0;
   out_6762039440372011872[80] = 0.0;
   out_6762039440372011872[81] = 0.0;
   out_6762039440372011872[82] = 0.0;
   out_6762039440372011872[83] = 0.0;
   out_6762039440372011872[84] = 0.0;
   out_6762039440372011872[85] = 0.0;
   out_6762039440372011872[86] = 0.0;
   out_6762039440372011872[87] = 0.0;
   out_6762039440372011872[88] = 0.0;
   out_6762039440372011872[89] = 0.0;
   out_6762039440372011872[90] = 0.0;
   out_6762039440372011872[91] = 0.0;
   out_6762039440372011872[92] = 0.0;
   out_6762039440372011872[93] = 0.0;
   out_6762039440372011872[94] = 0.0;
   out_6762039440372011872[95] = 1.0;
   out_6762039440372011872[96] = 0.0;
   out_6762039440372011872[97] = 0.0;
   out_6762039440372011872[98] = 0.0;
   out_6762039440372011872[99] = 0.0;
   out_6762039440372011872[100] = 0.0;
   out_6762039440372011872[101] = 0.0;
   out_6762039440372011872[102] = 0.0;
   out_6762039440372011872[103] = 0.0;
   out_6762039440372011872[104] = 0.0;
   out_6762039440372011872[105] = 0.0;
   out_6762039440372011872[106] = 0.0;
   out_6762039440372011872[107] = 0.0;
   out_6762039440372011872[108] = 0.0;
   out_6762039440372011872[109] = 0.0;
   out_6762039440372011872[110] = 0.0;
   out_6762039440372011872[111] = 0.0;
   out_6762039440372011872[112] = 0.0;
   out_6762039440372011872[113] = 0.0;
   out_6762039440372011872[114] = 1.0;
   out_6762039440372011872[115] = 0.0;
   out_6762039440372011872[116] = 0.0;
   out_6762039440372011872[117] = 0.0;
   out_6762039440372011872[118] = 0.0;
   out_6762039440372011872[119] = 0.0;
   out_6762039440372011872[120] = 0.0;
   out_6762039440372011872[121] = 0.0;
   out_6762039440372011872[122] = 0.0;
   out_6762039440372011872[123] = 0.0;
   out_6762039440372011872[124] = 0.0;
   out_6762039440372011872[125] = 0.0;
   out_6762039440372011872[126] = 0.0;
   out_6762039440372011872[127] = 0.0;
   out_6762039440372011872[128] = 0.0;
   out_6762039440372011872[129] = 0.0;
   out_6762039440372011872[130] = 0.0;
   out_6762039440372011872[131] = 0.0;
   out_6762039440372011872[132] = 0.0;
   out_6762039440372011872[133] = 1.0;
   out_6762039440372011872[134] = 0.0;
   out_6762039440372011872[135] = 0.0;
   out_6762039440372011872[136] = 0.0;
   out_6762039440372011872[137] = 0.0;
   out_6762039440372011872[138] = 0.0;
   out_6762039440372011872[139] = 0.0;
   out_6762039440372011872[140] = 0.0;
   out_6762039440372011872[141] = 0.0;
   out_6762039440372011872[142] = 0.0;
   out_6762039440372011872[143] = 0.0;
   out_6762039440372011872[144] = 0.0;
   out_6762039440372011872[145] = 0.0;
   out_6762039440372011872[146] = 0.0;
   out_6762039440372011872[147] = 0.0;
   out_6762039440372011872[148] = 0.0;
   out_6762039440372011872[149] = 0.0;
   out_6762039440372011872[150] = 0.0;
   out_6762039440372011872[151] = 0.0;
   out_6762039440372011872[152] = 1.0;
   out_6762039440372011872[153] = 0.0;
   out_6762039440372011872[154] = 0.0;
   out_6762039440372011872[155] = 0.0;
   out_6762039440372011872[156] = 0.0;
   out_6762039440372011872[157] = 0.0;
   out_6762039440372011872[158] = 0.0;
   out_6762039440372011872[159] = 0.0;
   out_6762039440372011872[160] = 0.0;
   out_6762039440372011872[161] = 0.0;
   out_6762039440372011872[162] = 0.0;
   out_6762039440372011872[163] = 0.0;
   out_6762039440372011872[164] = 0.0;
   out_6762039440372011872[165] = 0.0;
   out_6762039440372011872[166] = 0.0;
   out_6762039440372011872[167] = 0.0;
   out_6762039440372011872[168] = 0.0;
   out_6762039440372011872[169] = 0.0;
   out_6762039440372011872[170] = 0.0;
   out_6762039440372011872[171] = 1.0;
   out_6762039440372011872[172] = 0.0;
   out_6762039440372011872[173] = 0.0;
   out_6762039440372011872[174] = 0.0;
   out_6762039440372011872[175] = 0.0;
   out_6762039440372011872[176] = 0.0;
   out_6762039440372011872[177] = 0.0;
   out_6762039440372011872[178] = 0.0;
   out_6762039440372011872[179] = 0.0;
   out_6762039440372011872[180] = 0.0;
   out_6762039440372011872[181] = 0.0;
   out_6762039440372011872[182] = 0.0;
   out_6762039440372011872[183] = 0.0;
   out_6762039440372011872[184] = 0.0;
   out_6762039440372011872[185] = 0.0;
   out_6762039440372011872[186] = 0.0;
   out_6762039440372011872[187] = 0.0;
   out_6762039440372011872[188] = 0.0;
   out_6762039440372011872[189] = 0.0;
   out_6762039440372011872[190] = 1.0;
   out_6762039440372011872[191] = 0.0;
   out_6762039440372011872[192] = 0.0;
   out_6762039440372011872[193] = 0.0;
   out_6762039440372011872[194] = 0.0;
   out_6762039440372011872[195] = 0.0;
   out_6762039440372011872[196] = 0.0;
   out_6762039440372011872[197] = 0.0;
   out_6762039440372011872[198] = 0.0;
   out_6762039440372011872[199] = 0.0;
   out_6762039440372011872[200] = 0.0;
   out_6762039440372011872[201] = 0.0;
   out_6762039440372011872[202] = 0.0;
   out_6762039440372011872[203] = 0.0;
   out_6762039440372011872[204] = 0.0;
   out_6762039440372011872[205] = 0.0;
   out_6762039440372011872[206] = 0.0;
   out_6762039440372011872[207] = 0.0;
   out_6762039440372011872[208] = 0.0;
   out_6762039440372011872[209] = 1.0;
   out_6762039440372011872[210] = 0.0;
   out_6762039440372011872[211] = 0.0;
   out_6762039440372011872[212] = 0.0;
   out_6762039440372011872[213] = 0.0;
   out_6762039440372011872[214] = 0.0;
   out_6762039440372011872[215] = 0.0;
   out_6762039440372011872[216] = 0.0;
   out_6762039440372011872[217] = 0.0;
   out_6762039440372011872[218] = 0.0;
   out_6762039440372011872[219] = 0.0;
   out_6762039440372011872[220] = 0.0;
   out_6762039440372011872[221] = 0.0;
   out_6762039440372011872[222] = 0.0;
   out_6762039440372011872[223] = 0.0;
   out_6762039440372011872[224] = 0.0;
   out_6762039440372011872[225] = 0.0;
   out_6762039440372011872[226] = 0.0;
   out_6762039440372011872[227] = 0.0;
   out_6762039440372011872[228] = 1.0;
   out_6762039440372011872[229] = 0.0;
   out_6762039440372011872[230] = 0.0;
   out_6762039440372011872[231] = 0.0;
   out_6762039440372011872[232] = 0.0;
   out_6762039440372011872[233] = 0.0;
   out_6762039440372011872[234] = 0.0;
   out_6762039440372011872[235] = 0.0;
   out_6762039440372011872[236] = 0.0;
   out_6762039440372011872[237] = 0.0;
   out_6762039440372011872[238] = 0.0;
   out_6762039440372011872[239] = 0.0;
   out_6762039440372011872[240] = 0.0;
   out_6762039440372011872[241] = 0.0;
   out_6762039440372011872[242] = 0.0;
   out_6762039440372011872[243] = 0.0;
   out_6762039440372011872[244] = 0.0;
   out_6762039440372011872[245] = 0.0;
   out_6762039440372011872[246] = 0.0;
   out_6762039440372011872[247] = 1.0;
   out_6762039440372011872[248] = 0.0;
   out_6762039440372011872[249] = 0.0;
   out_6762039440372011872[250] = 0.0;
   out_6762039440372011872[251] = 0.0;
   out_6762039440372011872[252] = 0.0;
   out_6762039440372011872[253] = 0.0;
   out_6762039440372011872[254] = 0.0;
   out_6762039440372011872[255] = 0.0;
   out_6762039440372011872[256] = 0.0;
   out_6762039440372011872[257] = 0.0;
   out_6762039440372011872[258] = 0.0;
   out_6762039440372011872[259] = 0.0;
   out_6762039440372011872[260] = 0.0;
   out_6762039440372011872[261] = 0.0;
   out_6762039440372011872[262] = 0.0;
   out_6762039440372011872[263] = 0.0;
   out_6762039440372011872[264] = 0.0;
   out_6762039440372011872[265] = 0.0;
   out_6762039440372011872[266] = 1.0;
   out_6762039440372011872[267] = 0.0;
   out_6762039440372011872[268] = 0.0;
   out_6762039440372011872[269] = 0.0;
   out_6762039440372011872[270] = 0.0;
   out_6762039440372011872[271] = 0.0;
   out_6762039440372011872[272] = 0.0;
   out_6762039440372011872[273] = 0.0;
   out_6762039440372011872[274] = 0.0;
   out_6762039440372011872[275] = 0.0;
   out_6762039440372011872[276] = 0.0;
   out_6762039440372011872[277] = 0.0;
   out_6762039440372011872[278] = 0.0;
   out_6762039440372011872[279] = 0.0;
   out_6762039440372011872[280] = 0.0;
   out_6762039440372011872[281] = 0.0;
   out_6762039440372011872[282] = 0.0;
   out_6762039440372011872[283] = 0.0;
   out_6762039440372011872[284] = 0.0;
   out_6762039440372011872[285] = 1.0;
   out_6762039440372011872[286] = 0.0;
   out_6762039440372011872[287] = 0.0;
   out_6762039440372011872[288] = 0.0;
   out_6762039440372011872[289] = 0.0;
   out_6762039440372011872[290] = 0.0;
   out_6762039440372011872[291] = 0.0;
   out_6762039440372011872[292] = 0.0;
   out_6762039440372011872[293] = 0.0;
   out_6762039440372011872[294] = 0.0;
   out_6762039440372011872[295] = 0.0;
   out_6762039440372011872[296] = 0.0;
   out_6762039440372011872[297] = 0.0;
   out_6762039440372011872[298] = 0.0;
   out_6762039440372011872[299] = 0.0;
   out_6762039440372011872[300] = 0.0;
   out_6762039440372011872[301] = 0.0;
   out_6762039440372011872[302] = 0.0;
   out_6762039440372011872[303] = 0.0;
   out_6762039440372011872[304] = 1.0;
   out_6762039440372011872[305] = 0.0;
   out_6762039440372011872[306] = 0.0;
   out_6762039440372011872[307] = 0.0;
   out_6762039440372011872[308] = 0.0;
   out_6762039440372011872[309] = 0.0;
   out_6762039440372011872[310] = 0.0;
   out_6762039440372011872[311] = 0.0;
   out_6762039440372011872[312] = 0.0;
   out_6762039440372011872[313] = 0.0;
   out_6762039440372011872[314] = 0.0;
   out_6762039440372011872[315] = 0.0;
   out_6762039440372011872[316] = 0.0;
   out_6762039440372011872[317] = 0.0;
   out_6762039440372011872[318] = 0.0;
   out_6762039440372011872[319] = 0.0;
   out_6762039440372011872[320] = 0.0;
   out_6762039440372011872[321] = 0.0;
   out_6762039440372011872[322] = 0.0;
   out_6762039440372011872[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_2487690271541209027) {
   out_2487690271541209027[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_2487690271541209027[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_2487690271541209027[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_2487690271541209027[3] = dt*state[12] + state[3];
   out_2487690271541209027[4] = dt*state[13] + state[4];
   out_2487690271541209027[5] = dt*state[14] + state[5];
   out_2487690271541209027[6] = state[6];
   out_2487690271541209027[7] = state[7];
   out_2487690271541209027[8] = state[8];
   out_2487690271541209027[9] = state[9];
   out_2487690271541209027[10] = state[10];
   out_2487690271541209027[11] = state[11];
   out_2487690271541209027[12] = state[12];
   out_2487690271541209027[13] = state[13];
   out_2487690271541209027[14] = state[14];
   out_2487690271541209027[15] = state[15];
   out_2487690271541209027[16] = state[16];
   out_2487690271541209027[17] = state[17];
}
void F_fun(double *state, double dt, double *out_950182517979020623) {
   out_950182517979020623[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_950182517979020623[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_950182517979020623[2] = 0;
   out_950182517979020623[3] = 0;
   out_950182517979020623[4] = 0;
   out_950182517979020623[5] = 0;
   out_950182517979020623[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_950182517979020623[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_950182517979020623[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_950182517979020623[9] = 0;
   out_950182517979020623[10] = 0;
   out_950182517979020623[11] = 0;
   out_950182517979020623[12] = 0;
   out_950182517979020623[13] = 0;
   out_950182517979020623[14] = 0;
   out_950182517979020623[15] = 0;
   out_950182517979020623[16] = 0;
   out_950182517979020623[17] = 0;
   out_950182517979020623[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_950182517979020623[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_950182517979020623[20] = 0;
   out_950182517979020623[21] = 0;
   out_950182517979020623[22] = 0;
   out_950182517979020623[23] = 0;
   out_950182517979020623[24] = 0;
   out_950182517979020623[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_950182517979020623[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_950182517979020623[27] = 0;
   out_950182517979020623[28] = 0;
   out_950182517979020623[29] = 0;
   out_950182517979020623[30] = 0;
   out_950182517979020623[31] = 0;
   out_950182517979020623[32] = 0;
   out_950182517979020623[33] = 0;
   out_950182517979020623[34] = 0;
   out_950182517979020623[35] = 0;
   out_950182517979020623[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_950182517979020623[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_950182517979020623[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_950182517979020623[39] = 0;
   out_950182517979020623[40] = 0;
   out_950182517979020623[41] = 0;
   out_950182517979020623[42] = 0;
   out_950182517979020623[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_950182517979020623[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_950182517979020623[45] = 0;
   out_950182517979020623[46] = 0;
   out_950182517979020623[47] = 0;
   out_950182517979020623[48] = 0;
   out_950182517979020623[49] = 0;
   out_950182517979020623[50] = 0;
   out_950182517979020623[51] = 0;
   out_950182517979020623[52] = 0;
   out_950182517979020623[53] = 0;
   out_950182517979020623[54] = 0;
   out_950182517979020623[55] = 0;
   out_950182517979020623[56] = 0;
   out_950182517979020623[57] = 1;
   out_950182517979020623[58] = 0;
   out_950182517979020623[59] = 0;
   out_950182517979020623[60] = 0;
   out_950182517979020623[61] = 0;
   out_950182517979020623[62] = 0;
   out_950182517979020623[63] = 0;
   out_950182517979020623[64] = 0;
   out_950182517979020623[65] = 0;
   out_950182517979020623[66] = dt;
   out_950182517979020623[67] = 0;
   out_950182517979020623[68] = 0;
   out_950182517979020623[69] = 0;
   out_950182517979020623[70] = 0;
   out_950182517979020623[71] = 0;
   out_950182517979020623[72] = 0;
   out_950182517979020623[73] = 0;
   out_950182517979020623[74] = 0;
   out_950182517979020623[75] = 0;
   out_950182517979020623[76] = 1;
   out_950182517979020623[77] = 0;
   out_950182517979020623[78] = 0;
   out_950182517979020623[79] = 0;
   out_950182517979020623[80] = 0;
   out_950182517979020623[81] = 0;
   out_950182517979020623[82] = 0;
   out_950182517979020623[83] = 0;
   out_950182517979020623[84] = 0;
   out_950182517979020623[85] = dt;
   out_950182517979020623[86] = 0;
   out_950182517979020623[87] = 0;
   out_950182517979020623[88] = 0;
   out_950182517979020623[89] = 0;
   out_950182517979020623[90] = 0;
   out_950182517979020623[91] = 0;
   out_950182517979020623[92] = 0;
   out_950182517979020623[93] = 0;
   out_950182517979020623[94] = 0;
   out_950182517979020623[95] = 1;
   out_950182517979020623[96] = 0;
   out_950182517979020623[97] = 0;
   out_950182517979020623[98] = 0;
   out_950182517979020623[99] = 0;
   out_950182517979020623[100] = 0;
   out_950182517979020623[101] = 0;
   out_950182517979020623[102] = 0;
   out_950182517979020623[103] = 0;
   out_950182517979020623[104] = dt;
   out_950182517979020623[105] = 0;
   out_950182517979020623[106] = 0;
   out_950182517979020623[107] = 0;
   out_950182517979020623[108] = 0;
   out_950182517979020623[109] = 0;
   out_950182517979020623[110] = 0;
   out_950182517979020623[111] = 0;
   out_950182517979020623[112] = 0;
   out_950182517979020623[113] = 0;
   out_950182517979020623[114] = 1;
   out_950182517979020623[115] = 0;
   out_950182517979020623[116] = 0;
   out_950182517979020623[117] = 0;
   out_950182517979020623[118] = 0;
   out_950182517979020623[119] = 0;
   out_950182517979020623[120] = 0;
   out_950182517979020623[121] = 0;
   out_950182517979020623[122] = 0;
   out_950182517979020623[123] = 0;
   out_950182517979020623[124] = 0;
   out_950182517979020623[125] = 0;
   out_950182517979020623[126] = 0;
   out_950182517979020623[127] = 0;
   out_950182517979020623[128] = 0;
   out_950182517979020623[129] = 0;
   out_950182517979020623[130] = 0;
   out_950182517979020623[131] = 0;
   out_950182517979020623[132] = 0;
   out_950182517979020623[133] = 1;
   out_950182517979020623[134] = 0;
   out_950182517979020623[135] = 0;
   out_950182517979020623[136] = 0;
   out_950182517979020623[137] = 0;
   out_950182517979020623[138] = 0;
   out_950182517979020623[139] = 0;
   out_950182517979020623[140] = 0;
   out_950182517979020623[141] = 0;
   out_950182517979020623[142] = 0;
   out_950182517979020623[143] = 0;
   out_950182517979020623[144] = 0;
   out_950182517979020623[145] = 0;
   out_950182517979020623[146] = 0;
   out_950182517979020623[147] = 0;
   out_950182517979020623[148] = 0;
   out_950182517979020623[149] = 0;
   out_950182517979020623[150] = 0;
   out_950182517979020623[151] = 0;
   out_950182517979020623[152] = 1;
   out_950182517979020623[153] = 0;
   out_950182517979020623[154] = 0;
   out_950182517979020623[155] = 0;
   out_950182517979020623[156] = 0;
   out_950182517979020623[157] = 0;
   out_950182517979020623[158] = 0;
   out_950182517979020623[159] = 0;
   out_950182517979020623[160] = 0;
   out_950182517979020623[161] = 0;
   out_950182517979020623[162] = 0;
   out_950182517979020623[163] = 0;
   out_950182517979020623[164] = 0;
   out_950182517979020623[165] = 0;
   out_950182517979020623[166] = 0;
   out_950182517979020623[167] = 0;
   out_950182517979020623[168] = 0;
   out_950182517979020623[169] = 0;
   out_950182517979020623[170] = 0;
   out_950182517979020623[171] = 1;
   out_950182517979020623[172] = 0;
   out_950182517979020623[173] = 0;
   out_950182517979020623[174] = 0;
   out_950182517979020623[175] = 0;
   out_950182517979020623[176] = 0;
   out_950182517979020623[177] = 0;
   out_950182517979020623[178] = 0;
   out_950182517979020623[179] = 0;
   out_950182517979020623[180] = 0;
   out_950182517979020623[181] = 0;
   out_950182517979020623[182] = 0;
   out_950182517979020623[183] = 0;
   out_950182517979020623[184] = 0;
   out_950182517979020623[185] = 0;
   out_950182517979020623[186] = 0;
   out_950182517979020623[187] = 0;
   out_950182517979020623[188] = 0;
   out_950182517979020623[189] = 0;
   out_950182517979020623[190] = 1;
   out_950182517979020623[191] = 0;
   out_950182517979020623[192] = 0;
   out_950182517979020623[193] = 0;
   out_950182517979020623[194] = 0;
   out_950182517979020623[195] = 0;
   out_950182517979020623[196] = 0;
   out_950182517979020623[197] = 0;
   out_950182517979020623[198] = 0;
   out_950182517979020623[199] = 0;
   out_950182517979020623[200] = 0;
   out_950182517979020623[201] = 0;
   out_950182517979020623[202] = 0;
   out_950182517979020623[203] = 0;
   out_950182517979020623[204] = 0;
   out_950182517979020623[205] = 0;
   out_950182517979020623[206] = 0;
   out_950182517979020623[207] = 0;
   out_950182517979020623[208] = 0;
   out_950182517979020623[209] = 1;
   out_950182517979020623[210] = 0;
   out_950182517979020623[211] = 0;
   out_950182517979020623[212] = 0;
   out_950182517979020623[213] = 0;
   out_950182517979020623[214] = 0;
   out_950182517979020623[215] = 0;
   out_950182517979020623[216] = 0;
   out_950182517979020623[217] = 0;
   out_950182517979020623[218] = 0;
   out_950182517979020623[219] = 0;
   out_950182517979020623[220] = 0;
   out_950182517979020623[221] = 0;
   out_950182517979020623[222] = 0;
   out_950182517979020623[223] = 0;
   out_950182517979020623[224] = 0;
   out_950182517979020623[225] = 0;
   out_950182517979020623[226] = 0;
   out_950182517979020623[227] = 0;
   out_950182517979020623[228] = 1;
   out_950182517979020623[229] = 0;
   out_950182517979020623[230] = 0;
   out_950182517979020623[231] = 0;
   out_950182517979020623[232] = 0;
   out_950182517979020623[233] = 0;
   out_950182517979020623[234] = 0;
   out_950182517979020623[235] = 0;
   out_950182517979020623[236] = 0;
   out_950182517979020623[237] = 0;
   out_950182517979020623[238] = 0;
   out_950182517979020623[239] = 0;
   out_950182517979020623[240] = 0;
   out_950182517979020623[241] = 0;
   out_950182517979020623[242] = 0;
   out_950182517979020623[243] = 0;
   out_950182517979020623[244] = 0;
   out_950182517979020623[245] = 0;
   out_950182517979020623[246] = 0;
   out_950182517979020623[247] = 1;
   out_950182517979020623[248] = 0;
   out_950182517979020623[249] = 0;
   out_950182517979020623[250] = 0;
   out_950182517979020623[251] = 0;
   out_950182517979020623[252] = 0;
   out_950182517979020623[253] = 0;
   out_950182517979020623[254] = 0;
   out_950182517979020623[255] = 0;
   out_950182517979020623[256] = 0;
   out_950182517979020623[257] = 0;
   out_950182517979020623[258] = 0;
   out_950182517979020623[259] = 0;
   out_950182517979020623[260] = 0;
   out_950182517979020623[261] = 0;
   out_950182517979020623[262] = 0;
   out_950182517979020623[263] = 0;
   out_950182517979020623[264] = 0;
   out_950182517979020623[265] = 0;
   out_950182517979020623[266] = 1;
   out_950182517979020623[267] = 0;
   out_950182517979020623[268] = 0;
   out_950182517979020623[269] = 0;
   out_950182517979020623[270] = 0;
   out_950182517979020623[271] = 0;
   out_950182517979020623[272] = 0;
   out_950182517979020623[273] = 0;
   out_950182517979020623[274] = 0;
   out_950182517979020623[275] = 0;
   out_950182517979020623[276] = 0;
   out_950182517979020623[277] = 0;
   out_950182517979020623[278] = 0;
   out_950182517979020623[279] = 0;
   out_950182517979020623[280] = 0;
   out_950182517979020623[281] = 0;
   out_950182517979020623[282] = 0;
   out_950182517979020623[283] = 0;
   out_950182517979020623[284] = 0;
   out_950182517979020623[285] = 1;
   out_950182517979020623[286] = 0;
   out_950182517979020623[287] = 0;
   out_950182517979020623[288] = 0;
   out_950182517979020623[289] = 0;
   out_950182517979020623[290] = 0;
   out_950182517979020623[291] = 0;
   out_950182517979020623[292] = 0;
   out_950182517979020623[293] = 0;
   out_950182517979020623[294] = 0;
   out_950182517979020623[295] = 0;
   out_950182517979020623[296] = 0;
   out_950182517979020623[297] = 0;
   out_950182517979020623[298] = 0;
   out_950182517979020623[299] = 0;
   out_950182517979020623[300] = 0;
   out_950182517979020623[301] = 0;
   out_950182517979020623[302] = 0;
   out_950182517979020623[303] = 0;
   out_950182517979020623[304] = 1;
   out_950182517979020623[305] = 0;
   out_950182517979020623[306] = 0;
   out_950182517979020623[307] = 0;
   out_950182517979020623[308] = 0;
   out_950182517979020623[309] = 0;
   out_950182517979020623[310] = 0;
   out_950182517979020623[311] = 0;
   out_950182517979020623[312] = 0;
   out_950182517979020623[313] = 0;
   out_950182517979020623[314] = 0;
   out_950182517979020623[315] = 0;
   out_950182517979020623[316] = 0;
   out_950182517979020623[317] = 0;
   out_950182517979020623[318] = 0;
   out_950182517979020623[319] = 0;
   out_950182517979020623[320] = 0;
   out_950182517979020623[321] = 0;
   out_950182517979020623[322] = 0;
   out_950182517979020623[323] = 1;
}
void h_4(double *state, double *unused, double *out_1064982969821053038) {
   out_1064982969821053038[0] = state[6] + state[9];
   out_1064982969821053038[1] = state[7] + state[10];
   out_1064982969821053038[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1976156791710977266) {
   out_1976156791710977266[0] = 0;
   out_1976156791710977266[1] = 0;
   out_1976156791710977266[2] = 0;
   out_1976156791710977266[3] = 0;
   out_1976156791710977266[4] = 0;
   out_1976156791710977266[5] = 0;
   out_1976156791710977266[6] = 1;
   out_1976156791710977266[7] = 0;
   out_1976156791710977266[8] = 0;
   out_1976156791710977266[9] = 1;
   out_1976156791710977266[10] = 0;
   out_1976156791710977266[11] = 0;
   out_1976156791710977266[12] = 0;
   out_1976156791710977266[13] = 0;
   out_1976156791710977266[14] = 0;
   out_1976156791710977266[15] = 0;
   out_1976156791710977266[16] = 0;
   out_1976156791710977266[17] = 0;
   out_1976156791710977266[18] = 0;
   out_1976156791710977266[19] = 0;
   out_1976156791710977266[20] = 0;
   out_1976156791710977266[21] = 0;
   out_1976156791710977266[22] = 0;
   out_1976156791710977266[23] = 0;
   out_1976156791710977266[24] = 0;
   out_1976156791710977266[25] = 1;
   out_1976156791710977266[26] = 0;
   out_1976156791710977266[27] = 0;
   out_1976156791710977266[28] = 1;
   out_1976156791710977266[29] = 0;
   out_1976156791710977266[30] = 0;
   out_1976156791710977266[31] = 0;
   out_1976156791710977266[32] = 0;
   out_1976156791710977266[33] = 0;
   out_1976156791710977266[34] = 0;
   out_1976156791710977266[35] = 0;
   out_1976156791710977266[36] = 0;
   out_1976156791710977266[37] = 0;
   out_1976156791710977266[38] = 0;
   out_1976156791710977266[39] = 0;
   out_1976156791710977266[40] = 0;
   out_1976156791710977266[41] = 0;
   out_1976156791710977266[42] = 0;
   out_1976156791710977266[43] = 0;
   out_1976156791710977266[44] = 1;
   out_1976156791710977266[45] = 0;
   out_1976156791710977266[46] = 0;
   out_1976156791710977266[47] = 1;
   out_1976156791710977266[48] = 0;
   out_1976156791710977266[49] = 0;
   out_1976156791710977266[50] = 0;
   out_1976156791710977266[51] = 0;
   out_1976156791710977266[52] = 0;
   out_1976156791710977266[53] = 0;
}
void h_10(double *state, double *unused, double *out_9039008373436645978) {
   out_9039008373436645978[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_9039008373436645978[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_9039008373436645978[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6832717040485250243) {
   out_6832717040485250243[0] = 0;
   out_6832717040485250243[1] = 9.8100000000000005*cos(state[1]);
   out_6832717040485250243[2] = 0;
   out_6832717040485250243[3] = 0;
   out_6832717040485250243[4] = -state[8];
   out_6832717040485250243[5] = state[7];
   out_6832717040485250243[6] = 0;
   out_6832717040485250243[7] = state[5];
   out_6832717040485250243[8] = -state[4];
   out_6832717040485250243[9] = 0;
   out_6832717040485250243[10] = 0;
   out_6832717040485250243[11] = 0;
   out_6832717040485250243[12] = 1;
   out_6832717040485250243[13] = 0;
   out_6832717040485250243[14] = 0;
   out_6832717040485250243[15] = 1;
   out_6832717040485250243[16] = 0;
   out_6832717040485250243[17] = 0;
   out_6832717040485250243[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6832717040485250243[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6832717040485250243[20] = 0;
   out_6832717040485250243[21] = state[8];
   out_6832717040485250243[22] = 0;
   out_6832717040485250243[23] = -state[6];
   out_6832717040485250243[24] = -state[5];
   out_6832717040485250243[25] = 0;
   out_6832717040485250243[26] = state[3];
   out_6832717040485250243[27] = 0;
   out_6832717040485250243[28] = 0;
   out_6832717040485250243[29] = 0;
   out_6832717040485250243[30] = 0;
   out_6832717040485250243[31] = 1;
   out_6832717040485250243[32] = 0;
   out_6832717040485250243[33] = 0;
   out_6832717040485250243[34] = 1;
   out_6832717040485250243[35] = 0;
   out_6832717040485250243[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6832717040485250243[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6832717040485250243[38] = 0;
   out_6832717040485250243[39] = -state[7];
   out_6832717040485250243[40] = state[6];
   out_6832717040485250243[41] = 0;
   out_6832717040485250243[42] = state[4];
   out_6832717040485250243[43] = -state[3];
   out_6832717040485250243[44] = 0;
   out_6832717040485250243[45] = 0;
   out_6832717040485250243[46] = 0;
   out_6832717040485250243[47] = 0;
   out_6832717040485250243[48] = 0;
   out_6832717040485250243[49] = 0;
   out_6832717040485250243[50] = 1;
   out_6832717040485250243[51] = 0;
   out_6832717040485250243[52] = 0;
   out_6832717040485250243[53] = 1;
}
void h_13(double *state, double *unused, double *out_6939466162668529956) {
   out_6939466162668529956[0] = state[3];
   out_6939466162668529956[1] = state[4];
   out_6939466162668529956[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2540758711392821370) {
   out_2540758711392821370[0] = 0;
   out_2540758711392821370[1] = 0;
   out_2540758711392821370[2] = 0;
   out_2540758711392821370[3] = 1;
   out_2540758711392821370[4] = 0;
   out_2540758711392821370[5] = 0;
   out_2540758711392821370[6] = 0;
   out_2540758711392821370[7] = 0;
   out_2540758711392821370[8] = 0;
   out_2540758711392821370[9] = 0;
   out_2540758711392821370[10] = 0;
   out_2540758711392821370[11] = 0;
   out_2540758711392821370[12] = 0;
   out_2540758711392821370[13] = 0;
   out_2540758711392821370[14] = 0;
   out_2540758711392821370[15] = 0;
   out_2540758711392821370[16] = 0;
   out_2540758711392821370[17] = 0;
   out_2540758711392821370[18] = 0;
   out_2540758711392821370[19] = 0;
   out_2540758711392821370[20] = 0;
   out_2540758711392821370[21] = 0;
   out_2540758711392821370[22] = 1;
   out_2540758711392821370[23] = 0;
   out_2540758711392821370[24] = 0;
   out_2540758711392821370[25] = 0;
   out_2540758711392821370[26] = 0;
   out_2540758711392821370[27] = 0;
   out_2540758711392821370[28] = 0;
   out_2540758711392821370[29] = 0;
   out_2540758711392821370[30] = 0;
   out_2540758711392821370[31] = 0;
   out_2540758711392821370[32] = 0;
   out_2540758711392821370[33] = 0;
   out_2540758711392821370[34] = 0;
   out_2540758711392821370[35] = 0;
   out_2540758711392821370[36] = 0;
   out_2540758711392821370[37] = 0;
   out_2540758711392821370[38] = 0;
   out_2540758711392821370[39] = 0;
   out_2540758711392821370[40] = 0;
   out_2540758711392821370[41] = 1;
   out_2540758711392821370[42] = 0;
   out_2540758711392821370[43] = 0;
   out_2540758711392821370[44] = 0;
   out_2540758711392821370[45] = 0;
   out_2540758711392821370[46] = 0;
   out_2540758711392821370[47] = 0;
   out_2540758711392821370[48] = 0;
   out_2540758711392821370[49] = 0;
   out_2540758711392821370[50] = 0;
   out_2540758711392821370[51] = 0;
   out_2540758711392821370[52] = 0;
   out_2540758711392821370[53] = 0;
}
void h_14(double *state, double *unused, double *out_542665533068743617) {
   out_542665533068743617[0] = state[6];
   out_542665533068743617[1] = state[7];
   out_542665533068743617[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1106631640584395030) {
   out_1106631640584395030[0] = 0;
   out_1106631640584395030[1] = 0;
   out_1106631640584395030[2] = 0;
   out_1106631640584395030[3] = 0;
   out_1106631640584395030[4] = 0;
   out_1106631640584395030[5] = 0;
   out_1106631640584395030[6] = 1;
   out_1106631640584395030[7] = 0;
   out_1106631640584395030[8] = 0;
   out_1106631640584395030[9] = 0;
   out_1106631640584395030[10] = 0;
   out_1106631640584395030[11] = 0;
   out_1106631640584395030[12] = 0;
   out_1106631640584395030[13] = 0;
   out_1106631640584395030[14] = 0;
   out_1106631640584395030[15] = 0;
   out_1106631640584395030[16] = 0;
   out_1106631640584395030[17] = 0;
   out_1106631640584395030[18] = 0;
   out_1106631640584395030[19] = 0;
   out_1106631640584395030[20] = 0;
   out_1106631640584395030[21] = 0;
   out_1106631640584395030[22] = 0;
   out_1106631640584395030[23] = 0;
   out_1106631640584395030[24] = 0;
   out_1106631640584395030[25] = 1;
   out_1106631640584395030[26] = 0;
   out_1106631640584395030[27] = 0;
   out_1106631640584395030[28] = 0;
   out_1106631640584395030[29] = 0;
   out_1106631640584395030[30] = 0;
   out_1106631640584395030[31] = 0;
   out_1106631640584395030[32] = 0;
   out_1106631640584395030[33] = 0;
   out_1106631640584395030[34] = 0;
   out_1106631640584395030[35] = 0;
   out_1106631640584395030[36] = 0;
   out_1106631640584395030[37] = 0;
   out_1106631640584395030[38] = 0;
   out_1106631640584395030[39] = 0;
   out_1106631640584395030[40] = 0;
   out_1106631640584395030[41] = 0;
   out_1106631640584395030[42] = 0;
   out_1106631640584395030[43] = 0;
   out_1106631640584395030[44] = 1;
   out_1106631640584395030[45] = 0;
   out_1106631640584395030[46] = 0;
   out_1106631640584395030[47] = 0;
   out_1106631640584395030[48] = 0;
   out_1106631640584395030[49] = 0;
   out_1106631640584395030[50] = 0;
   out_1106631640584395030[51] = 0;
   out_1106631640584395030[52] = 0;
   out_1106631640584395030[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_4154280524256563890) {
  err_fun(nom_x, delta_x, out_4154280524256563890);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5487211563177375728) {
  inv_err_fun(nom_x, true_x, out_5487211563177375728);
}
void pose_H_mod_fun(double *state, double *out_6762039440372011872) {
  H_mod_fun(state, out_6762039440372011872);
}
void pose_f_fun(double *state, double dt, double *out_2487690271541209027) {
  f_fun(state,  dt, out_2487690271541209027);
}
void pose_F_fun(double *state, double dt, double *out_950182517979020623) {
  F_fun(state,  dt, out_950182517979020623);
}
void pose_h_4(double *state, double *unused, double *out_1064982969821053038) {
  h_4(state, unused, out_1064982969821053038);
}
void pose_H_4(double *state, double *unused, double *out_1976156791710977266) {
  H_4(state, unused, out_1976156791710977266);
}
void pose_h_10(double *state, double *unused, double *out_9039008373436645978) {
  h_10(state, unused, out_9039008373436645978);
}
void pose_H_10(double *state, double *unused, double *out_6832717040485250243) {
  H_10(state, unused, out_6832717040485250243);
}
void pose_h_13(double *state, double *unused, double *out_6939466162668529956) {
  h_13(state, unused, out_6939466162668529956);
}
void pose_H_13(double *state, double *unused, double *out_2540758711392821370) {
  H_13(state, unused, out_2540758711392821370);
}
void pose_h_14(double *state, double *unused, double *out_542665533068743617) {
  h_14(state, unused, out_542665533068743617);
}
void pose_H_14(double *state, double *unused, double *out_1106631640584395030) {
  H_14(state, unused, out_1106631640584395030);
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
