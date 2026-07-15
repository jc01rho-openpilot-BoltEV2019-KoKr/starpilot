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
void err_fun(double *nom_x, double *delta_x, double *out_7322678164781620542) {
   out_7322678164781620542[0] = delta_x[0] + nom_x[0];
   out_7322678164781620542[1] = delta_x[1] + nom_x[1];
   out_7322678164781620542[2] = delta_x[2] + nom_x[2];
   out_7322678164781620542[3] = delta_x[3] + nom_x[3];
   out_7322678164781620542[4] = delta_x[4] + nom_x[4];
   out_7322678164781620542[5] = delta_x[5] + nom_x[5];
   out_7322678164781620542[6] = delta_x[6] + nom_x[6];
   out_7322678164781620542[7] = delta_x[7] + nom_x[7];
   out_7322678164781620542[8] = delta_x[8] + nom_x[8];
   out_7322678164781620542[9] = delta_x[9] + nom_x[9];
   out_7322678164781620542[10] = delta_x[10] + nom_x[10];
   out_7322678164781620542[11] = delta_x[11] + nom_x[11];
   out_7322678164781620542[12] = delta_x[12] + nom_x[12];
   out_7322678164781620542[13] = delta_x[13] + nom_x[13];
   out_7322678164781620542[14] = delta_x[14] + nom_x[14];
   out_7322678164781620542[15] = delta_x[15] + nom_x[15];
   out_7322678164781620542[16] = delta_x[16] + nom_x[16];
   out_7322678164781620542[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6351713798129038522) {
   out_6351713798129038522[0] = -nom_x[0] + true_x[0];
   out_6351713798129038522[1] = -nom_x[1] + true_x[1];
   out_6351713798129038522[2] = -nom_x[2] + true_x[2];
   out_6351713798129038522[3] = -nom_x[3] + true_x[3];
   out_6351713798129038522[4] = -nom_x[4] + true_x[4];
   out_6351713798129038522[5] = -nom_x[5] + true_x[5];
   out_6351713798129038522[6] = -nom_x[6] + true_x[6];
   out_6351713798129038522[7] = -nom_x[7] + true_x[7];
   out_6351713798129038522[8] = -nom_x[8] + true_x[8];
   out_6351713798129038522[9] = -nom_x[9] + true_x[9];
   out_6351713798129038522[10] = -nom_x[10] + true_x[10];
   out_6351713798129038522[11] = -nom_x[11] + true_x[11];
   out_6351713798129038522[12] = -nom_x[12] + true_x[12];
   out_6351713798129038522[13] = -nom_x[13] + true_x[13];
   out_6351713798129038522[14] = -nom_x[14] + true_x[14];
   out_6351713798129038522[15] = -nom_x[15] + true_x[15];
   out_6351713798129038522[16] = -nom_x[16] + true_x[16];
   out_6351713798129038522[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7181373993335857162) {
   out_7181373993335857162[0] = 1.0;
   out_7181373993335857162[1] = 0.0;
   out_7181373993335857162[2] = 0.0;
   out_7181373993335857162[3] = 0.0;
   out_7181373993335857162[4] = 0.0;
   out_7181373993335857162[5] = 0.0;
   out_7181373993335857162[6] = 0.0;
   out_7181373993335857162[7] = 0.0;
   out_7181373993335857162[8] = 0.0;
   out_7181373993335857162[9] = 0.0;
   out_7181373993335857162[10] = 0.0;
   out_7181373993335857162[11] = 0.0;
   out_7181373993335857162[12] = 0.0;
   out_7181373993335857162[13] = 0.0;
   out_7181373993335857162[14] = 0.0;
   out_7181373993335857162[15] = 0.0;
   out_7181373993335857162[16] = 0.0;
   out_7181373993335857162[17] = 0.0;
   out_7181373993335857162[18] = 0.0;
   out_7181373993335857162[19] = 1.0;
   out_7181373993335857162[20] = 0.0;
   out_7181373993335857162[21] = 0.0;
   out_7181373993335857162[22] = 0.0;
   out_7181373993335857162[23] = 0.0;
   out_7181373993335857162[24] = 0.0;
   out_7181373993335857162[25] = 0.0;
   out_7181373993335857162[26] = 0.0;
   out_7181373993335857162[27] = 0.0;
   out_7181373993335857162[28] = 0.0;
   out_7181373993335857162[29] = 0.0;
   out_7181373993335857162[30] = 0.0;
   out_7181373993335857162[31] = 0.0;
   out_7181373993335857162[32] = 0.0;
   out_7181373993335857162[33] = 0.0;
   out_7181373993335857162[34] = 0.0;
   out_7181373993335857162[35] = 0.0;
   out_7181373993335857162[36] = 0.0;
   out_7181373993335857162[37] = 0.0;
   out_7181373993335857162[38] = 1.0;
   out_7181373993335857162[39] = 0.0;
   out_7181373993335857162[40] = 0.0;
   out_7181373993335857162[41] = 0.0;
   out_7181373993335857162[42] = 0.0;
   out_7181373993335857162[43] = 0.0;
   out_7181373993335857162[44] = 0.0;
   out_7181373993335857162[45] = 0.0;
   out_7181373993335857162[46] = 0.0;
   out_7181373993335857162[47] = 0.0;
   out_7181373993335857162[48] = 0.0;
   out_7181373993335857162[49] = 0.0;
   out_7181373993335857162[50] = 0.0;
   out_7181373993335857162[51] = 0.0;
   out_7181373993335857162[52] = 0.0;
   out_7181373993335857162[53] = 0.0;
   out_7181373993335857162[54] = 0.0;
   out_7181373993335857162[55] = 0.0;
   out_7181373993335857162[56] = 0.0;
   out_7181373993335857162[57] = 1.0;
   out_7181373993335857162[58] = 0.0;
   out_7181373993335857162[59] = 0.0;
   out_7181373993335857162[60] = 0.0;
   out_7181373993335857162[61] = 0.0;
   out_7181373993335857162[62] = 0.0;
   out_7181373993335857162[63] = 0.0;
   out_7181373993335857162[64] = 0.0;
   out_7181373993335857162[65] = 0.0;
   out_7181373993335857162[66] = 0.0;
   out_7181373993335857162[67] = 0.0;
   out_7181373993335857162[68] = 0.0;
   out_7181373993335857162[69] = 0.0;
   out_7181373993335857162[70] = 0.0;
   out_7181373993335857162[71] = 0.0;
   out_7181373993335857162[72] = 0.0;
   out_7181373993335857162[73] = 0.0;
   out_7181373993335857162[74] = 0.0;
   out_7181373993335857162[75] = 0.0;
   out_7181373993335857162[76] = 1.0;
   out_7181373993335857162[77] = 0.0;
   out_7181373993335857162[78] = 0.0;
   out_7181373993335857162[79] = 0.0;
   out_7181373993335857162[80] = 0.0;
   out_7181373993335857162[81] = 0.0;
   out_7181373993335857162[82] = 0.0;
   out_7181373993335857162[83] = 0.0;
   out_7181373993335857162[84] = 0.0;
   out_7181373993335857162[85] = 0.0;
   out_7181373993335857162[86] = 0.0;
   out_7181373993335857162[87] = 0.0;
   out_7181373993335857162[88] = 0.0;
   out_7181373993335857162[89] = 0.0;
   out_7181373993335857162[90] = 0.0;
   out_7181373993335857162[91] = 0.0;
   out_7181373993335857162[92] = 0.0;
   out_7181373993335857162[93] = 0.0;
   out_7181373993335857162[94] = 0.0;
   out_7181373993335857162[95] = 1.0;
   out_7181373993335857162[96] = 0.0;
   out_7181373993335857162[97] = 0.0;
   out_7181373993335857162[98] = 0.0;
   out_7181373993335857162[99] = 0.0;
   out_7181373993335857162[100] = 0.0;
   out_7181373993335857162[101] = 0.0;
   out_7181373993335857162[102] = 0.0;
   out_7181373993335857162[103] = 0.0;
   out_7181373993335857162[104] = 0.0;
   out_7181373993335857162[105] = 0.0;
   out_7181373993335857162[106] = 0.0;
   out_7181373993335857162[107] = 0.0;
   out_7181373993335857162[108] = 0.0;
   out_7181373993335857162[109] = 0.0;
   out_7181373993335857162[110] = 0.0;
   out_7181373993335857162[111] = 0.0;
   out_7181373993335857162[112] = 0.0;
   out_7181373993335857162[113] = 0.0;
   out_7181373993335857162[114] = 1.0;
   out_7181373993335857162[115] = 0.0;
   out_7181373993335857162[116] = 0.0;
   out_7181373993335857162[117] = 0.0;
   out_7181373993335857162[118] = 0.0;
   out_7181373993335857162[119] = 0.0;
   out_7181373993335857162[120] = 0.0;
   out_7181373993335857162[121] = 0.0;
   out_7181373993335857162[122] = 0.0;
   out_7181373993335857162[123] = 0.0;
   out_7181373993335857162[124] = 0.0;
   out_7181373993335857162[125] = 0.0;
   out_7181373993335857162[126] = 0.0;
   out_7181373993335857162[127] = 0.0;
   out_7181373993335857162[128] = 0.0;
   out_7181373993335857162[129] = 0.0;
   out_7181373993335857162[130] = 0.0;
   out_7181373993335857162[131] = 0.0;
   out_7181373993335857162[132] = 0.0;
   out_7181373993335857162[133] = 1.0;
   out_7181373993335857162[134] = 0.0;
   out_7181373993335857162[135] = 0.0;
   out_7181373993335857162[136] = 0.0;
   out_7181373993335857162[137] = 0.0;
   out_7181373993335857162[138] = 0.0;
   out_7181373993335857162[139] = 0.0;
   out_7181373993335857162[140] = 0.0;
   out_7181373993335857162[141] = 0.0;
   out_7181373993335857162[142] = 0.0;
   out_7181373993335857162[143] = 0.0;
   out_7181373993335857162[144] = 0.0;
   out_7181373993335857162[145] = 0.0;
   out_7181373993335857162[146] = 0.0;
   out_7181373993335857162[147] = 0.0;
   out_7181373993335857162[148] = 0.0;
   out_7181373993335857162[149] = 0.0;
   out_7181373993335857162[150] = 0.0;
   out_7181373993335857162[151] = 0.0;
   out_7181373993335857162[152] = 1.0;
   out_7181373993335857162[153] = 0.0;
   out_7181373993335857162[154] = 0.0;
   out_7181373993335857162[155] = 0.0;
   out_7181373993335857162[156] = 0.0;
   out_7181373993335857162[157] = 0.0;
   out_7181373993335857162[158] = 0.0;
   out_7181373993335857162[159] = 0.0;
   out_7181373993335857162[160] = 0.0;
   out_7181373993335857162[161] = 0.0;
   out_7181373993335857162[162] = 0.0;
   out_7181373993335857162[163] = 0.0;
   out_7181373993335857162[164] = 0.0;
   out_7181373993335857162[165] = 0.0;
   out_7181373993335857162[166] = 0.0;
   out_7181373993335857162[167] = 0.0;
   out_7181373993335857162[168] = 0.0;
   out_7181373993335857162[169] = 0.0;
   out_7181373993335857162[170] = 0.0;
   out_7181373993335857162[171] = 1.0;
   out_7181373993335857162[172] = 0.0;
   out_7181373993335857162[173] = 0.0;
   out_7181373993335857162[174] = 0.0;
   out_7181373993335857162[175] = 0.0;
   out_7181373993335857162[176] = 0.0;
   out_7181373993335857162[177] = 0.0;
   out_7181373993335857162[178] = 0.0;
   out_7181373993335857162[179] = 0.0;
   out_7181373993335857162[180] = 0.0;
   out_7181373993335857162[181] = 0.0;
   out_7181373993335857162[182] = 0.0;
   out_7181373993335857162[183] = 0.0;
   out_7181373993335857162[184] = 0.0;
   out_7181373993335857162[185] = 0.0;
   out_7181373993335857162[186] = 0.0;
   out_7181373993335857162[187] = 0.0;
   out_7181373993335857162[188] = 0.0;
   out_7181373993335857162[189] = 0.0;
   out_7181373993335857162[190] = 1.0;
   out_7181373993335857162[191] = 0.0;
   out_7181373993335857162[192] = 0.0;
   out_7181373993335857162[193] = 0.0;
   out_7181373993335857162[194] = 0.0;
   out_7181373993335857162[195] = 0.0;
   out_7181373993335857162[196] = 0.0;
   out_7181373993335857162[197] = 0.0;
   out_7181373993335857162[198] = 0.0;
   out_7181373993335857162[199] = 0.0;
   out_7181373993335857162[200] = 0.0;
   out_7181373993335857162[201] = 0.0;
   out_7181373993335857162[202] = 0.0;
   out_7181373993335857162[203] = 0.0;
   out_7181373993335857162[204] = 0.0;
   out_7181373993335857162[205] = 0.0;
   out_7181373993335857162[206] = 0.0;
   out_7181373993335857162[207] = 0.0;
   out_7181373993335857162[208] = 0.0;
   out_7181373993335857162[209] = 1.0;
   out_7181373993335857162[210] = 0.0;
   out_7181373993335857162[211] = 0.0;
   out_7181373993335857162[212] = 0.0;
   out_7181373993335857162[213] = 0.0;
   out_7181373993335857162[214] = 0.0;
   out_7181373993335857162[215] = 0.0;
   out_7181373993335857162[216] = 0.0;
   out_7181373993335857162[217] = 0.0;
   out_7181373993335857162[218] = 0.0;
   out_7181373993335857162[219] = 0.0;
   out_7181373993335857162[220] = 0.0;
   out_7181373993335857162[221] = 0.0;
   out_7181373993335857162[222] = 0.0;
   out_7181373993335857162[223] = 0.0;
   out_7181373993335857162[224] = 0.0;
   out_7181373993335857162[225] = 0.0;
   out_7181373993335857162[226] = 0.0;
   out_7181373993335857162[227] = 0.0;
   out_7181373993335857162[228] = 1.0;
   out_7181373993335857162[229] = 0.0;
   out_7181373993335857162[230] = 0.0;
   out_7181373993335857162[231] = 0.0;
   out_7181373993335857162[232] = 0.0;
   out_7181373993335857162[233] = 0.0;
   out_7181373993335857162[234] = 0.0;
   out_7181373993335857162[235] = 0.0;
   out_7181373993335857162[236] = 0.0;
   out_7181373993335857162[237] = 0.0;
   out_7181373993335857162[238] = 0.0;
   out_7181373993335857162[239] = 0.0;
   out_7181373993335857162[240] = 0.0;
   out_7181373993335857162[241] = 0.0;
   out_7181373993335857162[242] = 0.0;
   out_7181373993335857162[243] = 0.0;
   out_7181373993335857162[244] = 0.0;
   out_7181373993335857162[245] = 0.0;
   out_7181373993335857162[246] = 0.0;
   out_7181373993335857162[247] = 1.0;
   out_7181373993335857162[248] = 0.0;
   out_7181373993335857162[249] = 0.0;
   out_7181373993335857162[250] = 0.0;
   out_7181373993335857162[251] = 0.0;
   out_7181373993335857162[252] = 0.0;
   out_7181373993335857162[253] = 0.0;
   out_7181373993335857162[254] = 0.0;
   out_7181373993335857162[255] = 0.0;
   out_7181373993335857162[256] = 0.0;
   out_7181373993335857162[257] = 0.0;
   out_7181373993335857162[258] = 0.0;
   out_7181373993335857162[259] = 0.0;
   out_7181373993335857162[260] = 0.0;
   out_7181373993335857162[261] = 0.0;
   out_7181373993335857162[262] = 0.0;
   out_7181373993335857162[263] = 0.0;
   out_7181373993335857162[264] = 0.0;
   out_7181373993335857162[265] = 0.0;
   out_7181373993335857162[266] = 1.0;
   out_7181373993335857162[267] = 0.0;
   out_7181373993335857162[268] = 0.0;
   out_7181373993335857162[269] = 0.0;
   out_7181373993335857162[270] = 0.0;
   out_7181373993335857162[271] = 0.0;
   out_7181373993335857162[272] = 0.0;
   out_7181373993335857162[273] = 0.0;
   out_7181373993335857162[274] = 0.0;
   out_7181373993335857162[275] = 0.0;
   out_7181373993335857162[276] = 0.0;
   out_7181373993335857162[277] = 0.0;
   out_7181373993335857162[278] = 0.0;
   out_7181373993335857162[279] = 0.0;
   out_7181373993335857162[280] = 0.0;
   out_7181373993335857162[281] = 0.0;
   out_7181373993335857162[282] = 0.0;
   out_7181373993335857162[283] = 0.0;
   out_7181373993335857162[284] = 0.0;
   out_7181373993335857162[285] = 1.0;
   out_7181373993335857162[286] = 0.0;
   out_7181373993335857162[287] = 0.0;
   out_7181373993335857162[288] = 0.0;
   out_7181373993335857162[289] = 0.0;
   out_7181373993335857162[290] = 0.0;
   out_7181373993335857162[291] = 0.0;
   out_7181373993335857162[292] = 0.0;
   out_7181373993335857162[293] = 0.0;
   out_7181373993335857162[294] = 0.0;
   out_7181373993335857162[295] = 0.0;
   out_7181373993335857162[296] = 0.0;
   out_7181373993335857162[297] = 0.0;
   out_7181373993335857162[298] = 0.0;
   out_7181373993335857162[299] = 0.0;
   out_7181373993335857162[300] = 0.0;
   out_7181373993335857162[301] = 0.0;
   out_7181373993335857162[302] = 0.0;
   out_7181373993335857162[303] = 0.0;
   out_7181373993335857162[304] = 1.0;
   out_7181373993335857162[305] = 0.0;
   out_7181373993335857162[306] = 0.0;
   out_7181373993335857162[307] = 0.0;
   out_7181373993335857162[308] = 0.0;
   out_7181373993335857162[309] = 0.0;
   out_7181373993335857162[310] = 0.0;
   out_7181373993335857162[311] = 0.0;
   out_7181373993335857162[312] = 0.0;
   out_7181373993335857162[313] = 0.0;
   out_7181373993335857162[314] = 0.0;
   out_7181373993335857162[315] = 0.0;
   out_7181373993335857162[316] = 0.0;
   out_7181373993335857162[317] = 0.0;
   out_7181373993335857162[318] = 0.0;
   out_7181373993335857162[319] = 0.0;
   out_7181373993335857162[320] = 0.0;
   out_7181373993335857162[321] = 0.0;
   out_7181373993335857162[322] = 0.0;
   out_7181373993335857162[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1544031639553813882) {
   out_1544031639553813882[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1544031639553813882[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1544031639553813882[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1544031639553813882[3] = dt*state[12] + state[3];
   out_1544031639553813882[4] = dt*state[13] + state[4];
   out_1544031639553813882[5] = dt*state[14] + state[5];
   out_1544031639553813882[6] = state[6];
   out_1544031639553813882[7] = state[7];
   out_1544031639553813882[8] = state[8];
   out_1544031639553813882[9] = state[9];
   out_1544031639553813882[10] = state[10];
   out_1544031639553813882[11] = state[11];
   out_1544031639553813882[12] = state[12];
   out_1544031639553813882[13] = state[13];
   out_1544031639553813882[14] = state[14];
   out_1544031639553813882[15] = state[15];
   out_1544031639553813882[16] = state[16];
   out_1544031639553813882[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4307246870374060335) {
   out_4307246870374060335[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4307246870374060335[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4307246870374060335[2] = 0;
   out_4307246870374060335[3] = 0;
   out_4307246870374060335[4] = 0;
   out_4307246870374060335[5] = 0;
   out_4307246870374060335[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4307246870374060335[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4307246870374060335[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4307246870374060335[9] = 0;
   out_4307246870374060335[10] = 0;
   out_4307246870374060335[11] = 0;
   out_4307246870374060335[12] = 0;
   out_4307246870374060335[13] = 0;
   out_4307246870374060335[14] = 0;
   out_4307246870374060335[15] = 0;
   out_4307246870374060335[16] = 0;
   out_4307246870374060335[17] = 0;
   out_4307246870374060335[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4307246870374060335[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4307246870374060335[20] = 0;
   out_4307246870374060335[21] = 0;
   out_4307246870374060335[22] = 0;
   out_4307246870374060335[23] = 0;
   out_4307246870374060335[24] = 0;
   out_4307246870374060335[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4307246870374060335[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4307246870374060335[27] = 0;
   out_4307246870374060335[28] = 0;
   out_4307246870374060335[29] = 0;
   out_4307246870374060335[30] = 0;
   out_4307246870374060335[31] = 0;
   out_4307246870374060335[32] = 0;
   out_4307246870374060335[33] = 0;
   out_4307246870374060335[34] = 0;
   out_4307246870374060335[35] = 0;
   out_4307246870374060335[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4307246870374060335[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4307246870374060335[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4307246870374060335[39] = 0;
   out_4307246870374060335[40] = 0;
   out_4307246870374060335[41] = 0;
   out_4307246870374060335[42] = 0;
   out_4307246870374060335[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4307246870374060335[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4307246870374060335[45] = 0;
   out_4307246870374060335[46] = 0;
   out_4307246870374060335[47] = 0;
   out_4307246870374060335[48] = 0;
   out_4307246870374060335[49] = 0;
   out_4307246870374060335[50] = 0;
   out_4307246870374060335[51] = 0;
   out_4307246870374060335[52] = 0;
   out_4307246870374060335[53] = 0;
   out_4307246870374060335[54] = 0;
   out_4307246870374060335[55] = 0;
   out_4307246870374060335[56] = 0;
   out_4307246870374060335[57] = 1;
   out_4307246870374060335[58] = 0;
   out_4307246870374060335[59] = 0;
   out_4307246870374060335[60] = 0;
   out_4307246870374060335[61] = 0;
   out_4307246870374060335[62] = 0;
   out_4307246870374060335[63] = 0;
   out_4307246870374060335[64] = 0;
   out_4307246870374060335[65] = 0;
   out_4307246870374060335[66] = dt;
   out_4307246870374060335[67] = 0;
   out_4307246870374060335[68] = 0;
   out_4307246870374060335[69] = 0;
   out_4307246870374060335[70] = 0;
   out_4307246870374060335[71] = 0;
   out_4307246870374060335[72] = 0;
   out_4307246870374060335[73] = 0;
   out_4307246870374060335[74] = 0;
   out_4307246870374060335[75] = 0;
   out_4307246870374060335[76] = 1;
   out_4307246870374060335[77] = 0;
   out_4307246870374060335[78] = 0;
   out_4307246870374060335[79] = 0;
   out_4307246870374060335[80] = 0;
   out_4307246870374060335[81] = 0;
   out_4307246870374060335[82] = 0;
   out_4307246870374060335[83] = 0;
   out_4307246870374060335[84] = 0;
   out_4307246870374060335[85] = dt;
   out_4307246870374060335[86] = 0;
   out_4307246870374060335[87] = 0;
   out_4307246870374060335[88] = 0;
   out_4307246870374060335[89] = 0;
   out_4307246870374060335[90] = 0;
   out_4307246870374060335[91] = 0;
   out_4307246870374060335[92] = 0;
   out_4307246870374060335[93] = 0;
   out_4307246870374060335[94] = 0;
   out_4307246870374060335[95] = 1;
   out_4307246870374060335[96] = 0;
   out_4307246870374060335[97] = 0;
   out_4307246870374060335[98] = 0;
   out_4307246870374060335[99] = 0;
   out_4307246870374060335[100] = 0;
   out_4307246870374060335[101] = 0;
   out_4307246870374060335[102] = 0;
   out_4307246870374060335[103] = 0;
   out_4307246870374060335[104] = dt;
   out_4307246870374060335[105] = 0;
   out_4307246870374060335[106] = 0;
   out_4307246870374060335[107] = 0;
   out_4307246870374060335[108] = 0;
   out_4307246870374060335[109] = 0;
   out_4307246870374060335[110] = 0;
   out_4307246870374060335[111] = 0;
   out_4307246870374060335[112] = 0;
   out_4307246870374060335[113] = 0;
   out_4307246870374060335[114] = 1;
   out_4307246870374060335[115] = 0;
   out_4307246870374060335[116] = 0;
   out_4307246870374060335[117] = 0;
   out_4307246870374060335[118] = 0;
   out_4307246870374060335[119] = 0;
   out_4307246870374060335[120] = 0;
   out_4307246870374060335[121] = 0;
   out_4307246870374060335[122] = 0;
   out_4307246870374060335[123] = 0;
   out_4307246870374060335[124] = 0;
   out_4307246870374060335[125] = 0;
   out_4307246870374060335[126] = 0;
   out_4307246870374060335[127] = 0;
   out_4307246870374060335[128] = 0;
   out_4307246870374060335[129] = 0;
   out_4307246870374060335[130] = 0;
   out_4307246870374060335[131] = 0;
   out_4307246870374060335[132] = 0;
   out_4307246870374060335[133] = 1;
   out_4307246870374060335[134] = 0;
   out_4307246870374060335[135] = 0;
   out_4307246870374060335[136] = 0;
   out_4307246870374060335[137] = 0;
   out_4307246870374060335[138] = 0;
   out_4307246870374060335[139] = 0;
   out_4307246870374060335[140] = 0;
   out_4307246870374060335[141] = 0;
   out_4307246870374060335[142] = 0;
   out_4307246870374060335[143] = 0;
   out_4307246870374060335[144] = 0;
   out_4307246870374060335[145] = 0;
   out_4307246870374060335[146] = 0;
   out_4307246870374060335[147] = 0;
   out_4307246870374060335[148] = 0;
   out_4307246870374060335[149] = 0;
   out_4307246870374060335[150] = 0;
   out_4307246870374060335[151] = 0;
   out_4307246870374060335[152] = 1;
   out_4307246870374060335[153] = 0;
   out_4307246870374060335[154] = 0;
   out_4307246870374060335[155] = 0;
   out_4307246870374060335[156] = 0;
   out_4307246870374060335[157] = 0;
   out_4307246870374060335[158] = 0;
   out_4307246870374060335[159] = 0;
   out_4307246870374060335[160] = 0;
   out_4307246870374060335[161] = 0;
   out_4307246870374060335[162] = 0;
   out_4307246870374060335[163] = 0;
   out_4307246870374060335[164] = 0;
   out_4307246870374060335[165] = 0;
   out_4307246870374060335[166] = 0;
   out_4307246870374060335[167] = 0;
   out_4307246870374060335[168] = 0;
   out_4307246870374060335[169] = 0;
   out_4307246870374060335[170] = 0;
   out_4307246870374060335[171] = 1;
   out_4307246870374060335[172] = 0;
   out_4307246870374060335[173] = 0;
   out_4307246870374060335[174] = 0;
   out_4307246870374060335[175] = 0;
   out_4307246870374060335[176] = 0;
   out_4307246870374060335[177] = 0;
   out_4307246870374060335[178] = 0;
   out_4307246870374060335[179] = 0;
   out_4307246870374060335[180] = 0;
   out_4307246870374060335[181] = 0;
   out_4307246870374060335[182] = 0;
   out_4307246870374060335[183] = 0;
   out_4307246870374060335[184] = 0;
   out_4307246870374060335[185] = 0;
   out_4307246870374060335[186] = 0;
   out_4307246870374060335[187] = 0;
   out_4307246870374060335[188] = 0;
   out_4307246870374060335[189] = 0;
   out_4307246870374060335[190] = 1;
   out_4307246870374060335[191] = 0;
   out_4307246870374060335[192] = 0;
   out_4307246870374060335[193] = 0;
   out_4307246870374060335[194] = 0;
   out_4307246870374060335[195] = 0;
   out_4307246870374060335[196] = 0;
   out_4307246870374060335[197] = 0;
   out_4307246870374060335[198] = 0;
   out_4307246870374060335[199] = 0;
   out_4307246870374060335[200] = 0;
   out_4307246870374060335[201] = 0;
   out_4307246870374060335[202] = 0;
   out_4307246870374060335[203] = 0;
   out_4307246870374060335[204] = 0;
   out_4307246870374060335[205] = 0;
   out_4307246870374060335[206] = 0;
   out_4307246870374060335[207] = 0;
   out_4307246870374060335[208] = 0;
   out_4307246870374060335[209] = 1;
   out_4307246870374060335[210] = 0;
   out_4307246870374060335[211] = 0;
   out_4307246870374060335[212] = 0;
   out_4307246870374060335[213] = 0;
   out_4307246870374060335[214] = 0;
   out_4307246870374060335[215] = 0;
   out_4307246870374060335[216] = 0;
   out_4307246870374060335[217] = 0;
   out_4307246870374060335[218] = 0;
   out_4307246870374060335[219] = 0;
   out_4307246870374060335[220] = 0;
   out_4307246870374060335[221] = 0;
   out_4307246870374060335[222] = 0;
   out_4307246870374060335[223] = 0;
   out_4307246870374060335[224] = 0;
   out_4307246870374060335[225] = 0;
   out_4307246870374060335[226] = 0;
   out_4307246870374060335[227] = 0;
   out_4307246870374060335[228] = 1;
   out_4307246870374060335[229] = 0;
   out_4307246870374060335[230] = 0;
   out_4307246870374060335[231] = 0;
   out_4307246870374060335[232] = 0;
   out_4307246870374060335[233] = 0;
   out_4307246870374060335[234] = 0;
   out_4307246870374060335[235] = 0;
   out_4307246870374060335[236] = 0;
   out_4307246870374060335[237] = 0;
   out_4307246870374060335[238] = 0;
   out_4307246870374060335[239] = 0;
   out_4307246870374060335[240] = 0;
   out_4307246870374060335[241] = 0;
   out_4307246870374060335[242] = 0;
   out_4307246870374060335[243] = 0;
   out_4307246870374060335[244] = 0;
   out_4307246870374060335[245] = 0;
   out_4307246870374060335[246] = 0;
   out_4307246870374060335[247] = 1;
   out_4307246870374060335[248] = 0;
   out_4307246870374060335[249] = 0;
   out_4307246870374060335[250] = 0;
   out_4307246870374060335[251] = 0;
   out_4307246870374060335[252] = 0;
   out_4307246870374060335[253] = 0;
   out_4307246870374060335[254] = 0;
   out_4307246870374060335[255] = 0;
   out_4307246870374060335[256] = 0;
   out_4307246870374060335[257] = 0;
   out_4307246870374060335[258] = 0;
   out_4307246870374060335[259] = 0;
   out_4307246870374060335[260] = 0;
   out_4307246870374060335[261] = 0;
   out_4307246870374060335[262] = 0;
   out_4307246870374060335[263] = 0;
   out_4307246870374060335[264] = 0;
   out_4307246870374060335[265] = 0;
   out_4307246870374060335[266] = 1;
   out_4307246870374060335[267] = 0;
   out_4307246870374060335[268] = 0;
   out_4307246870374060335[269] = 0;
   out_4307246870374060335[270] = 0;
   out_4307246870374060335[271] = 0;
   out_4307246870374060335[272] = 0;
   out_4307246870374060335[273] = 0;
   out_4307246870374060335[274] = 0;
   out_4307246870374060335[275] = 0;
   out_4307246870374060335[276] = 0;
   out_4307246870374060335[277] = 0;
   out_4307246870374060335[278] = 0;
   out_4307246870374060335[279] = 0;
   out_4307246870374060335[280] = 0;
   out_4307246870374060335[281] = 0;
   out_4307246870374060335[282] = 0;
   out_4307246870374060335[283] = 0;
   out_4307246870374060335[284] = 0;
   out_4307246870374060335[285] = 1;
   out_4307246870374060335[286] = 0;
   out_4307246870374060335[287] = 0;
   out_4307246870374060335[288] = 0;
   out_4307246870374060335[289] = 0;
   out_4307246870374060335[290] = 0;
   out_4307246870374060335[291] = 0;
   out_4307246870374060335[292] = 0;
   out_4307246870374060335[293] = 0;
   out_4307246870374060335[294] = 0;
   out_4307246870374060335[295] = 0;
   out_4307246870374060335[296] = 0;
   out_4307246870374060335[297] = 0;
   out_4307246870374060335[298] = 0;
   out_4307246870374060335[299] = 0;
   out_4307246870374060335[300] = 0;
   out_4307246870374060335[301] = 0;
   out_4307246870374060335[302] = 0;
   out_4307246870374060335[303] = 0;
   out_4307246870374060335[304] = 1;
   out_4307246870374060335[305] = 0;
   out_4307246870374060335[306] = 0;
   out_4307246870374060335[307] = 0;
   out_4307246870374060335[308] = 0;
   out_4307246870374060335[309] = 0;
   out_4307246870374060335[310] = 0;
   out_4307246870374060335[311] = 0;
   out_4307246870374060335[312] = 0;
   out_4307246870374060335[313] = 0;
   out_4307246870374060335[314] = 0;
   out_4307246870374060335[315] = 0;
   out_4307246870374060335[316] = 0;
   out_4307246870374060335[317] = 0;
   out_4307246870374060335[318] = 0;
   out_4307246870374060335[319] = 0;
   out_4307246870374060335[320] = 0;
   out_4307246870374060335[321] = 0;
   out_4307246870374060335[322] = 0;
   out_4307246870374060335[323] = 1;
}
void h_4(double *state, double *unused, double *out_2329964328807098264) {
   out_2329964328807098264[0] = state[6] + state[9];
   out_2329964328807098264[1] = state[7] + state[10];
   out_2329964328807098264[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3409566783491949590) {
   out_3409566783491949590[0] = 0;
   out_3409566783491949590[1] = 0;
   out_3409566783491949590[2] = 0;
   out_3409566783491949590[3] = 0;
   out_3409566783491949590[4] = 0;
   out_3409566783491949590[5] = 0;
   out_3409566783491949590[6] = 1;
   out_3409566783491949590[7] = 0;
   out_3409566783491949590[8] = 0;
   out_3409566783491949590[9] = 1;
   out_3409566783491949590[10] = 0;
   out_3409566783491949590[11] = 0;
   out_3409566783491949590[12] = 0;
   out_3409566783491949590[13] = 0;
   out_3409566783491949590[14] = 0;
   out_3409566783491949590[15] = 0;
   out_3409566783491949590[16] = 0;
   out_3409566783491949590[17] = 0;
   out_3409566783491949590[18] = 0;
   out_3409566783491949590[19] = 0;
   out_3409566783491949590[20] = 0;
   out_3409566783491949590[21] = 0;
   out_3409566783491949590[22] = 0;
   out_3409566783491949590[23] = 0;
   out_3409566783491949590[24] = 0;
   out_3409566783491949590[25] = 1;
   out_3409566783491949590[26] = 0;
   out_3409566783491949590[27] = 0;
   out_3409566783491949590[28] = 1;
   out_3409566783491949590[29] = 0;
   out_3409566783491949590[30] = 0;
   out_3409566783491949590[31] = 0;
   out_3409566783491949590[32] = 0;
   out_3409566783491949590[33] = 0;
   out_3409566783491949590[34] = 0;
   out_3409566783491949590[35] = 0;
   out_3409566783491949590[36] = 0;
   out_3409566783491949590[37] = 0;
   out_3409566783491949590[38] = 0;
   out_3409566783491949590[39] = 0;
   out_3409566783491949590[40] = 0;
   out_3409566783491949590[41] = 0;
   out_3409566783491949590[42] = 0;
   out_3409566783491949590[43] = 0;
   out_3409566783491949590[44] = 1;
   out_3409566783491949590[45] = 0;
   out_3409566783491949590[46] = 0;
   out_3409566783491949590[47] = 1;
   out_3409566783491949590[48] = 0;
   out_3409566783491949590[49] = 0;
   out_3409566783491949590[50] = 0;
   out_3409566783491949590[51] = 0;
   out_3409566783491949590[52] = 0;
   out_3409566783491949590[53] = 0;
}
void h_10(double *state, double *unused, double *out_1764029327220956455) {
   out_1764029327220956455[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1764029327220956455[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1764029327220956455[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5084421046690710562) {
   out_5084421046690710562[0] = 0;
   out_5084421046690710562[1] = 9.8100000000000005*cos(state[1]);
   out_5084421046690710562[2] = 0;
   out_5084421046690710562[3] = 0;
   out_5084421046690710562[4] = -state[8];
   out_5084421046690710562[5] = state[7];
   out_5084421046690710562[6] = 0;
   out_5084421046690710562[7] = state[5];
   out_5084421046690710562[8] = -state[4];
   out_5084421046690710562[9] = 0;
   out_5084421046690710562[10] = 0;
   out_5084421046690710562[11] = 0;
   out_5084421046690710562[12] = 1;
   out_5084421046690710562[13] = 0;
   out_5084421046690710562[14] = 0;
   out_5084421046690710562[15] = 1;
   out_5084421046690710562[16] = 0;
   out_5084421046690710562[17] = 0;
   out_5084421046690710562[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5084421046690710562[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5084421046690710562[20] = 0;
   out_5084421046690710562[21] = state[8];
   out_5084421046690710562[22] = 0;
   out_5084421046690710562[23] = -state[6];
   out_5084421046690710562[24] = -state[5];
   out_5084421046690710562[25] = 0;
   out_5084421046690710562[26] = state[3];
   out_5084421046690710562[27] = 0;
   out_5084421046690710562[28] = 0;
   out_5084421046690710562[29] = 0;
   out_5084421046690710562[30] = 0;
   out_5084421046690710562[31] = 1;
   out_5084421046690710562[32] = 0;
   out_5084421046690710562[33] = 0;
   out_5084421046690710562[34] = 1;
   out_5084421046690710562[35] = 0;
   out_5084421046690710562[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5084421046690710562[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5084421046690710562[38] = 0;
   out_5084421046690710562[39] = -state[7];
   out_5084421046690710562[40] = state[6];
   out_5084421046690710562[41] = 0;
   out_5084421046690710562[42] = state[4];
   out_5084421046690710562[43] = -state[3];
   out_5084421046690710562[44] = 0;
   out_5084421046690710562[45] = 0;
   out_5084421046690710562[46] = 0;
   out_5084421046690710562[47] = 0;
   out_5084421046690710562[48] = 0;
   out_5084421046690710562[49] = 0;
   out_5084421046690710562[50] = 1;
   out_5084421046690710562[51] = 0;
   out_5084421046690710562[52] = 0;
   out_5084421046690710562[53] = 1;
}
void h_13(double *state, double *unused, double *out_7799867727264054991) {
   out_7799867727264054991[0] = state[3];
   out_7799867727264054991[1] = state[4];
   out_7799867727264054991[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2844964863810105486) {
   out_2844964863810105486[0] = 0;
   out_2844964863810105486[1] = 0;
   out_2844964863810105486[2] = 0;
   out_2844964863810105486[3] = 1;
   out_2844964863810105486[4] = 0;
   out_2844964863810105486[5] = 0;
   out_2844964863810105486[6] = 0;
   out_2844964863810105486[7] = 0;
   out_2844964863810105486[8] = 0;
   out_2844964863810105486[9] = 0;
   out_2844964863810105486[10] = 0;
   out_2844964863810105486[11] = 0;
   out_2844964863810105486[12] = 0;
   out_2844964863810105486[13] = 0;
   out_2844964863810105486[14] = 0;
   out_2844964863810105486[15] = 0;
   out_2844964863810105486[16] = 0;
   out_2844964863810105486[17] = 0;
   out_2844964863810105486[18] = 0;
   out_2844964863810105486[19] = 0;
   out_2844964863810105486[20] = 0;
   out_2844964863810105486[21] = 0;
   out_2844964863810105486[22] = 1;
   out_2844964863810105486[23] = 0;
   out_2844964863810105486[24] = 0;
   out_2844964863810105486[25] = 0;
   out_2844964863810105486[26] = 0;
   out_2844964863810105486[27] = 0;
   out_2844964863810105486[28] = 0;
   out_2844964863810105486[29] = 0;
   out_2844964863810105486[30] = 0;
   out_2844964863810105486[31] = 0;
   out_2844964863810105486[32] = 0;
   out_2844964863810105486[33] = 0;
   out_2844964863810105486[34] = 0;
   out_2844964863810105486[35] = 0;
   out_2844964863810105486[36] = 0;
   out_2844964863810105486[37] = 0;
   out_2844964863810105486[38] = 0;
   out_2844964863810105486[39] = 0;
   out_2844964863810105486[40] = 0;
   out_2844964863810105486[41] = 1;
   out_2844964863810105486[42] = 0;
   out_2844964863810105486[43] = 0;
   out_2844964863810105486[44] = 0;
   out_2844964863810105486[45] = 0;
   out_2844964863810105486[46] = 0;
   out_2844964863810105486[47] = 0;
   out_2844964863810105486[48] = 0;
   out_2844964863810105486[49] = 0;
   out_2844964863810105486[50] = 0;
   out_2844964863810105486[51] = 0;
   out_2844964863810105486[52] = 0;
   out_2844964863810105486[53] = 0;
}
void h_14(double *state, double *unused, double *out_3740143774591228770) {
   out_3740143774591228770[0] = state[6];
   out_3740143774591228770[1] = state[7];
   out_3740143774591228770[2] = state[8];
}
void H_14(double *state, double *unused, double *out_6492355215787321886) {
   out_6492355215787321886[0] = 0;
   out_6492355215787321886[1] = 0;
   out_6492355215787321886[2] = 0;
   out_6492355215787321886[3] = 0;
   out_6492355215787321886[4] = 0;
   out_6492355215787321886[5] = 0;
   out_6492355215787321886[6] = 1;
   out_6492355215787321886[7] = 0;
   out_6492355215787321886[8] = 0;
   out_6492355215787321886[9] = 0;
   out_6492355215787321886[10] = 0;
   out_6492355215787321886[11] = 0;
   out_6492355215787321886[12] = 0;
   out_6492355215787321886[13] = 0;
   out_6492355215787321886[14] = 0;
   out_6492355215787321886[15] = 0;
   out_6492355215787321886[16] = 0;
   out_6492355215787321886[17] = 0;
   out_6492355215787321886[18] = 0;
   out_6492355215787321886[19] = 0;
   out_6492355215787321886[20] = 0;
   out_6492355215787321886[21] = 0;
   out_6492355215787321886[22] = 0;
   out_6492355215787321886[23] = 0;
   out_6492355215787321886[24] = 0;
   out_6492355215787321886[25] = 1;
   out_6492355215787321886[26] = 0;
   out_6492355215787321886[27] = 0;
   out_6492355215787321886[28] = 0;
   out_6492355215787321886[29] = 0;
   out_6492355215787321886[30] = 0;
   out_6492355215787321886[31] = 0;
   out_6492355215787321886[32] = 0;
   out_6492355215787321886[33] = 0;
   out_6492355215787321886[34] = 0;
   out_6492355215787321886[35] = 0;
   out_6492355215787321886[36] = 0;
   out_6492355215787321886[37] = 0;
   out_6492355215787321886[38] = 0;
   out_6492355215787321886[39] = 0;
   out_6492355215787321886[40] = 0;
   out_6492355215787321886[41] = 0;
   out_6492355215787321886[42] = 0;
   out_6492355215787321886[43] = 0;
   out_6492355215787321886[44] = 1;
   out_6492355215787321886[45] = 0;
   out_6492355215787321886[46] = 0;
   out_6492355215787321886[47] = 0;
   out_6492355215787321886[48] = 0;
   out_6492355215787321886[49] = 0;
   out_6492355215787321886[50] = 0;
   out_6492355215787321886[51] = 0;
   out_6492355215787321886[52] = 0;
   out_6492355215787321886[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7322678164781620542) {
  err_fun(nom_x, delta_x, out_7322678164781620542);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6351713798129038522) {
  inv_err_fun(nom_x, true_x, out_6351713798129038522);
}
void pose_H_mod_fun(double *state, double *out_7181373993335857162) {
  H_mod_fun(state, out_7181373993335857162);
}
void pose_f_fun(double *state, double dt, double *out_1544031639553813882) {
  f_fun(state,  dt, out_1544031639553813882);
}
void pose_F_fun(double *state, double dt, double *out_4307246870374060335) {
  F_fun(state,  dt, out_4307246870374060335);
}
void pose_h_4(double *state, double *unused, double *out_2329964328807098264) {
  h_4(state, unused, out_2329964328807098264);
}
void pose_H_4(double *state, double *unused, double *out_3409566783491949590) {
  H_4(state, unused, out_3409566783491949590);
}
void pose_h_10(double *state, double *unused, double *out_1764029327220956455) {
  h_10(state, unused, out_1764029327220956455);
}
void pose_H_10(double *state, double *unused, double *out_5084421046690710562) {
  H_10(state, unused, out_5084421046690710562);
}
void pose_h_13(double *state, double *unused, double *out_7799867727264054991) {
  h_13(state, unused, out_7799867727264054991);
}
void pose_H_13(double *state, double *unused, double *out_2844964863810105486) {
  H_13(state, unused, out_2844964863810105486);
}
void pose_h_14(double *state, double *unused, double *out_3740143774591228770) {
  h_14(state, unused, out_3740143774591228770);
}
void pose_H_14(double *state, double *unused, double *out_6492355215787321886) {
  H_14(state, unused, out_6492355215787321886);
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
