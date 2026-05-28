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
void err_fun(double *nom_x, double *delta_x, double *out_6079659893886918220) {
   out_6079659893886918220[0] = delta_x[0] + nom_x[0];
   out_6079659893886918220[1] = delta_x[1] + nom_x[1];
   out_6079659893886918220[2] = delta_x[2] + nom_x[2];
   out_6079659893886918220[3] = delta_x[3] + nom_x[3];
   out_6079659893886918220[4] = delta_x[4] + nom_x[4];
   out_6079659893886918220[5] = delta_x[5] + nom_x[5];
   out_6079659893886918220[6] = delta_x[6] + nom_x[6];
   out_6079659893886918220[7] = delta_x[7] + nom_x[7];
   out_6079659893886918220[8] = delta_x[8] + nom_x[8];
   out_6079659893886918220[9] = delta_x[9] + nom_x[9];
   out_6079659893886918220[10] = delta_x[10] + nom_x[10];
   out_6079659893886918220[11] = delta_x[11] + nom_x[11];
   out_6079659893886918220[12] = delta_x[12] + nom_x[12];
   out_6079659893886918220[13] = delta_x[13] + nom_x[13];
   out_6079659893886918220[14] = delta_x[14] + nom_x[14];
   out_6079659893886918220[15] = delta_x[15] + nom_x[15];
   out_6079659893886918220[16] = delta_x[16] + nom_x[16];
   out_6079659893886918220[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5200837164005369107) {
   out_5200837164005369107[0] = -nom_x[0] + true_x[0];
   out_5200837164005369107[1] = -nom_x[1] + true_x[1];
   out_5200837164005369107[2] = -nom_x[2] + true_x[2];
   out_5200837164005369107[3] = -nom_x[3] + true_x[3];
   out_5200837164005369107[4] = -nom_x[4] + true_x[4];
   out_5200837164005369107[5] = -nom_x[5] + true_x[5];
   out_5200837164005369107[6] = -nom_x[6] + true_x[6];
   out_5200837164005369107[7] = -nom_x[7] + true_x[7];
   out_5200837164005369107[8] = -nom_x[8] + true_x[8];
   out_5200837164005369107[9] = -nom_x[9] + true_x[9];
   out_5200837164005369107[10] = -nom_x[10] + true_x[10];
   out_5200837164005369107[11] = -nom_x[11] + true_x[11];
   out_5200837164005369107[12] = -nom_x[12] + true_x[12];
   out_5200837164005369107[13] = -nom_x[13] + true_x[13];
   out_5200837164005369107[14] = -nom_x[14] + true_x[14];
   out_5200837164005369107[15] = -nom_x[15] + true_x[15];
   out_5200837164005369107[16] = -nom_x[16] + true_x[16];
   out_5200837164005369107[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_1320875044412644660) {
   out_1320875044412644660[0] = 1.0;
   out_1320875044412644660[1] = 0.0;
   out_1320875044412644660[2] = 0.0;
   out_1320875044412644660[3] = 0.0;
   out_1320875044412644660[4] = 0.0;
   out_1320875044412644660[5] = 0.0;
   out_1320875044412644660[6] = 0.0;
   out_1320875044412644660[7] = 0.0;
   out_1320875044412644660[8] = 0.0;
   out_1320875044412644660[9] = 0.0;
   out_1320875044412644660[10] = 0.0;
   out_1320875044412644660[11] = 0.0;
   out_1320875044412644660[12] = 0.0;
   out_1320875044412644660[13] = 0.0;
   out_1320875044412644660[14] = 0.0;
   out_1320875044412644660[15] = 0.0;
   out_1320875044412644660[16] = 0.0;
   out_1320875044412644660[17] = 0.0;
   out_1320875044412644660[18] = 0.0;
   out_1320875044412644660[19] = 1.0;
   out_1320875044412644660[20] = 0.0;
   out_1320875044412644660[21] = 0.0;
   out_1320875044412644660[22] = 0.0;
   out_1320875044412644660[23] = 0.0;
   out_1320875044412644660[24] = 0.0;
   out_1320875044412644660[25] = 0.0;
   out_1320875044412644660[26] = 0.0;
   out_1320875044412644660[27] = 0.0;
   out_1320875044412644660[28] = 0.0;
   out_1320875044412644660[29] = 0.0;
   out_1320875044412644660[30] = 0.0;
   out_1320875044412644660[31] = 0.0;
   out_1320875044412644660[32] = 0.0;
   out_1320875044412644660[33] = 0.0;
   out_1320875044412644660[34] = 0.0;
   out_1320875044412644660[35] = 0.0;
   out_1320875044412644660[36] = 0.0;
   out_1320875044412644660[37] = 0.0;
   out_1320875044412644660[38] = 1.0;
   out_1320875044412644660[39] = 0.0;
   out_1320875044412644660[40] = 0.0;
   out_1320875044412644660[41] = 0.0;
   out_1320875044412644660[42] = 0.0;
   out_1320875044412644660[43] = 0.0;
   out_1320875044412644660[44] = 0.0;
   out_1320875044412644660[45] = 0.0;
   out_1320875044412644660[46] = 0.0;
   out_1320875044412644660[47] = 0.0;
   out_1320875044412644660[48] = 0.0;
   out_1320875044412644660[49] = 0.0;
   out_1320875044412644660[50] = 0.0;
   out_1320875044412644660[51] = 0.0;
   out_1320875044412644660[52] = 0.0;
   out_1320875044412644660[53] = 0.0;
   out_1320875044412644660[54] = 0.0;
   out_1320875044412644660[55] = 0.0;
   out_1320875044412644660[56] = 0.0;
   out_1320875044412644660[57] = 1.0;
   out_1320875044412644660[58] = 0.0;
   out_1320875044412644660[59] = 0.0;
   out_1320875044412644660[60] = 0.0;
   out_1320875044412644660[61] = 0.0;
   out_1320875044412644660[62] = 0.0;
   out_1320875044412644660[63] = 0.0;
   out_1320875044412644660[64] = 0.0;
   out_1320875044412644660[65] = 0.0;
   out_1320875044412644660[66] = 0.0;
   out_1320875044412644660[67] = 0.0;
   out_1320875044412644660[68] = 0.0;
   out_1320875044412644660[69] = 0.0;
   out_1320875044412644660[70] = 0.0;
   out_1320875044412644660[71] = 0.0;
   out_1320875044412644660[72] = 0.0;
   out_1320875044412644660[73] = 0.0;
   out_1320875044412644660[74] = 0.0;
   out_1320875044412644660[75] = 0.0;
   out_1320875044412644660[76] = 1.0;
   out_1320875044412644660[77] = 0.0;
   out_1320875044412644660[78] = 0.0;
   out_1320875044412644660[79] = 0.0;
   out_1320875044412644660[80] = 0.0;
   out_1320875044412644660[81] = 0.0;
   out_1320875044412644660[82] = 0.0;
   out_1320875044412644660[83] = 0.0;
   out_1320875044412644660[84] = 0.0;
   out_1320875044412644660[85] = 0.0;
   out_1320875044412644660[86] = 0.0;
   out_1320875044412644660[87] = 0.0;
   out_1320875044412644660[88] = 0.0;
   out_1320875044412644660[89] = 0.0;
   out_1320875044412644660[90] = 0.0;
   out_1320875044412644660[91] = 0.0;
   out_1320875044412644660[92] = 0.0;
   out_1320875044412644660[93] = 0.0;
   out_1320875044412644660[94] = 0.0;
   out_1320875044412644660[95] = 1.0;
   out_1320875044412644660[96] = 0.0;
   out_1320875044412644660[97] = 0.0;
   out_1320875044412644660[98] = 0.0;
   out_1320875044412644660[99] = 0.0;
   out_1320875044412644660[100] = 0.0;
   out_1320875044412644660[101] = 0.0;
   out_1320875044412644660[102] = 0.0;
   out_1320875044412644660[103] = 0.0;
   out_1320875044412644660[104] = 0.0;
   out_1320875044412644660[105] = 0.0;
   out_1320875044412644660[106] = 0.0;
   out_1320875044412644660[107] = 0.0;
   out_1320875044412644660[108] = 0.0;
   out_1320875044412644660[109] = 0.0;
   out_1320875044412644660[110] = 0.0;
   out_1320875044412644660[111] = 0.0;
   out_1320875044412644660[112] = 0.0;
   out_1320875044412644660[113] = 0.0;
   out_1320875044412644660[114] = 1.0;
   out_1320875044412644660[115] = 0.0;
   out_1320875044412644660[116] = 0.0;
   out_1320875044412644660[117] = 0.0;
   out_1320875044412644660[118] = 0.0;
   out_1320875044412644660[119] = 0.0;
   out_1320875044412644660[120] = 0.0;
   out_1320875044412644660[121] = 0.0;
   out_1320875044412644660[122] = 0.0;
   out_1320875044412644660[123] = 0.0;
   out_1320875044412644660[124] = 0.0;
   out_1320875044412644660[125] = 0.0;
   out_1320875044412644660[126] = 0.0;
   out_1320875044412644660[127] = 0.0;
   out_1320875044412644660[128] = 0.0;
   out_1320875044412644660[129] = 0.0;
   out_1320875044412644660[130] = 0.0;
   out_1320875044412644660[131] = 0.0;
   out_1320875044412644660[132] = 0.0;
   out_1320875044412644660[133] = 1.0;
   out_1320875044412644660[134] = 0.0;
   out_1320875044412644660[135] = 0.0;
   out_1320875044412644660[136] = 0.0;
   out_1320875044412644660[137] = 0.0;
   out_1320875044412644660[138] = 0.0;
   out_1320875044412644660[139] = 0.0;
   out_1320875044412644660[140] = 0.0;
   out_1320875044412644660[141] = 0.0;
   out_1320875044412644660[142] = 0.0;
   out_1320875044412644660[143] = 0.0;
   out_1320875044412644660[144] = 0.0;
   out_1320875044412644660[145] = 0.0;
   out_1320875044412644660[146] = 0.0;
   out_1320875044412644660[147] = 0.0;
   out_1320875044412644660[148] = 0.0;
   out_1320875044412644660[149] = 0.0;
   out_1320875044412644660[150] = 0.0;
   out_1320875044412644660[151] = 0.0;
   out_1320875044412644660[152] = 1.0;
   out_1320875044412644660[153] = 0.0;
   out_1320875044412644660[154] = 0.0;
   out_1320875044412644660[155] = 0.0;
   out_1320875044412644660[156] = 0.0;
   out_1320875044412644660[157] = 0.0;
   out_1320875044412644660[158] = 0.0;
   out_1320875044412644660[159] = 0.0;
   out_1320875044412644660[160] = 0.0;
   out_1320875044412644660[161] = 0.0;
   out_1320875044412644660[162] = 0.0;
   out_1320875044412644660[163] = 0.0;
   out_1320875044412644660[164] = 0.0;
   out_1320875044412644660[165] = 0.0;
   out_1320875044412644660[166] = 0.0;
   out_1320875044412644660[167] = 0.0;
   out_1320875044412644660[168] = 0.0;
   out_1320875044412644660[169] = 0.0;
   out_1320875044412644660[170] = 0.0;
   out_1320875044412644660[171] = 1.0;
   out_1320875044412644660[172] = 0.0;
   out_1320875044412644660[173] = 0.0;
   out_1320875044412644660[174] = 0.0;
   out_1320875044412644660[175] = 0.0;
   out_1320875044412644660[176] = 0.0;
   out_1320875044412644660[177] = 0.0;
   out_1320875044412644660[178] = 0.0;
   out_1320875044412644660[179] = 0.0;
   out_1320875044412644660[180] = 0.0;
   out_1320875044412644660[181] = 0.0;
   out_1320875044412644660[182] = 0.0;
   out_1320875044412644660[183] = 0.0;
   out_1320875044412644660[184] = 0.0;
   out_1320875044412644660[185] = 0.0;
   out_1320875044412644660[186] = 0.0;
   out_1320875044412644660[187] = 0.0;
   out_1320875044412644660[188] = 0.0;
   out_1320875044412644660[189] = 0.0;
   out_1320875044412644660[190] = 1.0;
   out_1320875044412644660[191] = 0.0;
   out_1320875044412644660[192] = 0.0;
   out_1320875044412644660[193] = 0.0;
   out_1320875044412644660[194] = 0.0;
   out_1320875044412644660[195] = 0.0;
   out_1320875044412644660[196] = 0.0;
   out_1320875044412644660[197] = 0.0;
   out_1320875044412644660[198] = 0.0;
   out_1320875044412644660[199] = 0.0;
   out_1320875044412644660[200] = 0.0;
   out_1320875044412644660[201] = 0.0;
   out_1320875044412644660[202] = 0.0;
   out_1320875044412644660[203] = 0.0;
   out_1320875044412644660[204] = 0.0;
   out_1320875044412644660[205] = 0.0;
   out_1320875044412644660[206] = 0.0;
   out_1320875044412644660[207] = 0.0;
   out_1320875044412644660[208] = 0.0;
   out_1320875044412644660[209] = 1.0;
   out_1320875044412644660[210] = 0.0;
   out_1320875044412644660[211] = 0.0;
   out_1320875044412644660[212] = 0.0;
   out_1320875044412644660[213] = 0.0;
   out_1320875044412644660[214] = 0.0;
   out_1320875044412644660[215] = 0.0;
   out_1320875044412644660[216] = 0.0;
   out_1320875044412644660[217] = 0.0;
   out_1320875044412644660[218] = 0.0;
   out_1320875044412644660[219] = 0.0;
   out_1320875044412644660[220] = 0.0;
   out_1320875044412644660[221] = 0.0;
   out_1320875044412644660[222] = 0.0;
   out_1320875044412644660[223] = 0.0;
   out_1320875044412644660[224] = 0.0;
   out_1320875044412644660[225] = 0.0;
   out_1320875044412644660[226] = 0.0;
   out_1320875044412644660[227] = 0.0;
   out_1320875044412644660[228] = 1.0;
   out_1320875044412644660[229] = 0.0;
   out_1320875044412644660[230] = 0.0;
   out_1320875044412644660[231] = 0.0;
   out_1320875044412644660[232] = 0.0;
   out_1320875044412644660[233] = 0.0;
   out_1320875044412644660[234] = 0.0;
   out_1320875044412644660[235] = 0.0;
   out_1320875044412644660[236] = 0.0;
   out_1320875044412644660[237] = 0.0;
   out_1320875044412644660[238] = 0.0;
   out_1320875044412644660[239] = 0.0;
   out_1320875044412644660[240] = 0.0;
   out_1320875044412644660[241] = 0.0;
   out_1320875044412644660[242] = 0.0;
   out_1320875044412644660[243] = 0.0;
   out_1320875044412644660[244] = 0.0;
   out_1320875044412644660[245] = 0.0;
   out_1320875044412644660[246] = 0.0;
   out_1320875044412644660[247] = 1.0;
   out_1320875044412644660[248] = 0.0;
   out_1320875044412644660[249] = 0.0;
   out_1320875044412644660[250] = 0.0;
   out_1320875044412644660[251] = 0.0;
   out_1320875044412644660[252] = 0.0;
   out_1320875044412644660[253] = 0.0;
   out_1320875044412644660[254] = 0.0;
   out_1320875044412644660[255] = 0.0;
   out_1320875044412644660[256] = 0.0;
   out_1320875044412644660[257] = 0.0;
   out_1320875044412644660[258] = 0.0;
   out_1320875044412644660[259] = 0.0;
   out_1320875044412644660[260] = 0.0;
   out_1320875044412644660[261] = 0.0;
   out_1320875044412644660[262] = 0.0;
   out_1320875044412644660[263] = 0.0;
   out_1320875044412644660[264] = 0.0;
   out_1320875044412644660[265] = 0.0;
   out_1320875044412644660[266] = 1.0;
   out_1320875044412644660[267] = 0.0;
   out_1320875044412644660[268] = 0.0;
   out_1320875044412644660[269] = 0.0;
   out_1320875044412644660[270] = 0.0;
   out_1320875044412644660[271] = 0.0;
   out_1320875044412644660[272] = 0.0;
   out_1320875044412644660[273] = 0.0;
   out_1320875044412644660[274] = 0.0;
   out_1320875044412644660[275] = 0.0;
   out_1320875044412644660[276] = 0.0;
   out_1320875044412644660[277] = 0.0;
   out_1320875044412644660[278] = 0.0;
   out_1320875044412644660[279] = 0.0;
   out_1320875044412644660[280] = 0.0;
   out_1320875044412644660[281] = 0.0;
   out_1320875044412644660[282] = 0.0;
   out_1320875044412644660[283] = 0.0;
   out_1320875044412644660[284] = 0.0;
   out_1320875044412644660[285] = 1.0;
   out_1320875044412644660[286] = 0.0;
   out_1320875044412644660[287] = 0.0;
   out_1320875044412644660[288] = 0.0;
   out_1320875044412644660[289] = 0.0;
   out_1320875044412644660[290] = 0.0;
   out_1320875044412644660[291] = 0.0;
   out_1320875044412644660[292] = 0.0;
   out_1320875044412644660[293] = 0.0;
   out_1320875044412644660[294] = 0.0;
   out_1320875044412644660[295] = 0.0;
   out_1320875044412644660[296] = 0.0;
   out_1320875044412644660[297] = 0.0;
   out_1320875044412644660[298] = 0.0;
   out_1320875044412644660[299] = 0.0;
   out_1320875044412644660[300] = 0.0;
   out_1320875044412644660[301] = 0.0;
   out_1320875044412644660[302] = 0.0;
   out_1320875044412644660[303] = 0.0;
   out_1320875044412644660[304] = 1.0;
   out_1320875044412644660[305] = 0.0;
   out_1320875044412644660[306] = 0.0;
   out_1320875044412644660[307] = 0.0;
   out_1320875044412644660[308] = 0.0;
   out_1320875044412644660[309] = 0.0;
   out_1320875044412644660[310] = 0.0;
   out_1320875044412644660[311] = 0.0;
   out_1320875044412644660[312] = 0.0;
   out_1320875044412644660[313] = 0.0;
   out_1320875044412644660[314] = 0.0;
   out_1320875044412644660[315] = 0.0;
   out_1320875044412644660[316] = 0.0;
   out_1320875044412644660[317] = 0.0;
   out_1320875044412644660[318] = 0.0;
   out_1320875044412644660[319] = 0.0;
   out_1320875044412644660[320] = 0.0;
   out_1320875044412644660[321] = 0.0;
   out_1320875044412644660[322] = 0.0;
   out_1320875044412644660[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4957392939814811366) {
   out_4957392939814811366[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4957392939814811366[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4957392939814811366[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4957392939814811366[3] = dt*state[12] + state[3];
   out_4957392939814811366[4] = dt*state[13] + state[4];
   out_4957392939814811366[5] = dt*state[14] + state[5];
   out_4957392939814811366[6] = state[6];
   out_4957392939814811366[7] = state[7];
   out_4957392939814811366[8] = state[8];
   out_4957392939814811366[9] = state[9];
   out_4957392939814811366[10] = state[10];
   out_4957392939814811366[11] = state[11];
   out_4957392939814811366[12] = state[12];
   out_4957392939814811366[13] = state[13];
   out_4957392939814811366[14] = state[14];
   out_4957392939814811366[15] = state[15];
   out_4957392939814811366[16] = state[16];
   out_4957392939814811366[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3660031818732653459) {
   out_3660031818732653459[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3660031818732653459[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3660031818732653459[2] = 0;
   out_3660031818732653459[3] = 0;
   out_3660031818732653459[4] = 0;
   out_3660031818732653459[5] = 0;
   out_3660031818732653459[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3660031818732653459[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3660031818732653459[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3660031818732653459[9] = 0;
   out_3660031818732653459[10] = 0;
   out_3660031818732653459[11] = 0;
   out_3660031818732653459[12] = 0;
   out_3660031818732653459[13] = 0;
   out_3660031818732653459[14] = 0;
   out_3660031818732653459[15] = 0;
   out_3660031818732653459[16] = 0;
   out_3660031818732653459[17] = 0;
   out_3660031818732653459[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3660031818732653459[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3660031818732653459[20] = 0;
   out_3660031818732653459[21] = 0;
   out_3660031818732653459[22] = 0;
   out_3660031818732653459[23] = 0;
   out_3660031818732653459[24] = 0;
   out_3660031818732653459[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3660031818732653459[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3660031818732653459[27] = 0;
   out_3660031818732653459[28] = 0;
   out_3660031818732653459[29] = 0;
   out_3660031818732653459[30] = 0;
   out_3660031818732653459[31] = 0;
   out_3660031818732653459[32] = 0;
   out_3660031818732653459[33] = 0;
   out_3660031818732653459[34] = 0;
   out_3660031818732653459[35] = 0;
   out_3660031818732653459[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3660031818732653459[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3660031818732653459[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3660031818732653459[39] = 0;
   out_3660031818732653459[40] = 0;
   out_3660031818732653459[41] = 0;
   out_3660031818732653459[42] = 0;
   out_3660031818732653459[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3660031818732653459[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3660031818732653459[45] = 0;
   out_3660031818732653459[46] = 0;
   out_3660031818732653459[47] = 0;
   out_3660031818732653459[48] = 0;
   out_3660031818732653459[49] = 0;
   out_3660031818732653459[50] = 0;
   out_3660031818732653459[51] = 0;
   out_3660031818732653459[52] = 0;
   out_3660031818732653459[53] = 0;
   out_3660031818732653459[54] = 0;
   out_3660031818732653459[55] = 0;
   out_3660031818732653459[56] = 0;
   out_3660031818732653459[57] = 1;
   out_3660031818732653459[58] = 0;
   out_3660031818732653459[59] = 0;
   out_3660031818732653459[60] = 0;
   out_3660031818732653459[61] = 0;
   out_3660031818732653459[62] = 0;
   out_3660031818732653459[63] = 0;
   out_3660031818732653459[64] = 0;
   out_3660031818732653459[65] = 0;
   out_3660031818732653459[66] = dt;
   out_3660031818732653459[67] = 0;
   out_3660031818732653459[68] = 0;
   out_3660031818732653459[69] = 0;
   out_3660031818732653459[70] = 0;
   out_3660031818732653459[71] = 0;
   out_3660031818732653459[72] = 0;
   out_3660031818732653459[73] = 0;
   out_3660031818732653459[74] = 0;
   out_3660031818732653459[75] = 0;
   out_3660031818732653459[76] = 1;
   out_3660031818732653459[77] = 0;
   out_3660031818732653459[78] = 0;
   out_3660031818732653459[79] = 0;
   out_3660031818732653459[80] = 0;
   out_3660031818732653459[81] = 0;
   out_3660031818732653459[82] = 0;
   out_3660031818732653459[83] = 0;
   out_3660031818732653459[84] = 0;
   out_3660031818732653459[85] = dt;
   out_3660031818732653459[86] = 0;
   out_3660031818732653459[87] = 0;
   out_3660031818732653459[88] = 0;
   out_3660031818732653459[89] = 0;
   out_3660031818732653459[90] = 0;
   out_3660031818732653459[91] = 0;
   out_3660031818732653459[92] = 0;
   out_3660031818732653459[93] = 0;
   out_3660031818732653459[94] = 0;
   out_3660031818732653459[95] = 1;
   out_3660031818732653459[96] = 0;
   out_3660031818732653459[97] = 0;
   out_3660031818732653459[98] = 0;
   out_3660031818732653459[99] = 0;
   out_3660031818732653459[100] = 0;
   out_3660031818732653459[101] = 0;
   out_3660031818732653459[102] = 0;
   out_3660031818732653459[103] = 0;
   out_3660031818732653459[104] = dt;
   out_3660031818732653459[105] = 0;
   out_3660031818732653459[106] = 0;
   out_3660031818732653459[107] = 0;
   out_3660031818732653459[108] = 0;
   out_3660031818732653459[109] = 0;
   out_3660031818732653459[110] = 0;
   out_3660031818732653459[111] = 0;
   out_3660031818732653459[112] = 0;
   out_3660031818732653459[113] = 0;
   out_3660031818732653459[114] = 1;
   out_3660031818732653459[115] = 0;
   out_3660031818732653459[116] = 0;
   out_3660031818732653459[117] = 0;
   out_3660031818732653459[118] = 0;
   out_3660031818732653459[119] = 0;
   out_3660031818732653459[120] = 0;
   out_3660031818732653459[121] = 0;
   out_3660031818732653459[122] = 0;
   out_3660031818732653459[123] = 0;
   out_3660031818732653459[124] = 0;
   out_3660031818732653459[125] = 0;
   out_3660031818732653459[126] = 0;
   out_3660031818732653459[127] = 0;
   out_3660031818732653459[128] = 0;
   out_3660031818732653459[129] = 0;
   out_3660031818732653459[130] = 0;
   out_3660031818732653459[131] = 0;
   out_3660031818732653459[132] = 0;
   out_3660031818732653459[133] = 1;
   out_3660031818732653459[134] = 0;
   out_3660031818732653459[135] = 0;
   out_3660031818732653459[136] = 0;
   out_3660031818732653459[137] = 0;
   out_3660031818732653459[138] = 0;
   out_3660031818732653459[139] = 0;
   out_3660031818732653459[140] = 0;
   out_3660031818732653459[141] = 0;
   out_3660031818732653459[142] = 0;
   out_3660031818732653459[143] = 0;
   out_3660031818732653459[144] = 0;
   out_3660031818732653459[145] = 0;
   out_3660031818732653459[146] = 0;
   out_3660031818732653459[147] = 0;
   out_3660031818732653459[148] = 0;
   out_3660031818732653459[149] = 0;
   out_3660031818732653459[150] = 0;
   out_3660031818732653459[151] = 0;
   out_3660031818732653459[152] = 1;
   out_3660031818732653459[153] = 0;
   out_3660031818732653459[154] = 0;
   out_3660031818732653459[155] = 0;
   out_3660031818732653459[156] = 0;
   out_3660031818732653459[157] = 0;
   out_3660031818732653459[158] = 0;
   out_3660031818732653459[159] = 0;
   out_3660031818732653459[160] = 0;
   out_3660031818732653459[161] = 0;
   out_3660031818732653459[162] = 0;
   out_3660031818732653459[163] = 0;
   out_3660031818732653459[164] = 0;
   out_3660031818732653459[165] = 0;
   out_3660031818732653459[166] = 0;
   out_3660031818732653459[167] = 0;
   out_3660031818732653459[168] = 0;
   out_3660031818732653459[169] = 0;
   out_3660031818732653459[170] = 0;
   out_3660031818732653459[171] = 1;
   out_3660031818732653459[172] = 0;
   out_3660031818732653459[173] = 0;
   out_3660031818732653459[174] = 0;
   out_3660031818732653459[175] = 0;
   out_3660031818732653459[176] = 0;
   out_3660031818732653459[177] = 0;
   out_3660031818732653459[178] = 0;
   out_3660031818732653459[179] = 0;
   out_3660031818732653459[180] = 0;
   out_3660031818732653459[181] = 0;
   out_3660031818732653459[182] = 0;
   out_3660031818732653459[183] = 0;
   out_3660031818732653459[184] = 0;
   out_3660031818732653459[185] = 0;
   out_3660031818732653459[186] = 0;
   out_3660031818732653459[187] = 0;
   out_3660031818732653459[188] = 0;
   out_3660031818732653459[189] = 0;
   out_3660031818732653459[190] = 1;
   out_3660031818732653459[191] = 0;
   out_3660031818732653459[192] = 0;
   out_3660031818732653459[193] = 0;
   out_3660031818732653459[194] = 0;
   out_3660031818732653459[195] = 0;
   out_3660031818732653459[196] = 0;
   out_3660031818732653459[197] = 0;
   out_3660031818732653459[198] = 0;
   out_3660031818732653459[199] = 0;
   out_3660031818732653459[200] = 0;
   out_3660031818732653459[201] = 0;
   out_3660031818732653459[202] = 0;
   out_3660031818732653459[203] = 0;
   out_3660031818732653459[204] = 0;
   out_3660031818732653459[205] = 0;
   out_3660031818732653459[206] = 0;
   out_3660031818732653459[207] = 0;
   out_3660031818732653459[208] = 0;
   out_3660031818732653459[209] = 1;
   out_3660031818732653459[210] = 0;
   out_3660031818732653459[211] = 0;
   out_3660031818732653459[212] = 0;
   out_3660031818732653459[213] = 0;
   out_3660031818732653459[214] = 0;
   out_3660031818732653459[215] = 0;
   out_3660031818732653459[216] = 0;
   out_3660031818732653459[217] = 0;
   out_3660031818732653459[218] = 0;
   out_3660031818732653459[219] = 0;
   out_3660031818732653459[220] = 0;
   out_3660031818732653459[221] = 0;
   out_3660031818732653459[222] = 0;
   out_3660031818732653459[223] = 0;
   out_3660031818732653459[224] = 0;
   out_3660031818732653459[225] = 0;
   out_3660031818732653459[226] = 0;
   out_3660031818732653459[227] = 0;
   out_3660031818732653459[228] = 1;
   out_3660031818732653459[229] = 0;
   out_3660031818732653459[230] = 0;
   out_3660031818732653459[231] = 0;
   out_3660031818732653459[232] = 0;
   out_3660031818732653459[233] = 0;
   out_3660031818732653459[234] = 0;
   out_3660031818732653459[235] = 0;
   out_3660031818732653459[236] = 0;
   out_3660031818732653459[237] = 0;
   out_3660031818732653459[238] = 0;
   out_3660031818732653459[239] = 0;
   out_3660031818732653459[240] = 0;
   out_3660031818732653459[241] = 0;
   out_3660031818732653459[242] = 0;
   out_3660031818732653459[243] = 0;
   out_3660031818732653459[244] = 0;
   out_3660031818732653459[245] = 0;
   out_3660031818732653459[246] = 0;
   out_3660031818732653459[247] = 1;
   out_3660031818732653459[248] = 0;
   out_3660031818732653459[249] = 0;
   out_3660031818732653459[250] = 0;
   out_3660031818732653459[251] = 0;
   out_3660031818732653459[252] = 0;
   out_3660031818732653459[253] = 0;
   out_3660031818732653459[254] = 0;
   out_3660031818732653459[255] = 0;
   out_3660031818732653459[256] = 0;
   out_3660031818732653459[257] = 0;
   out_3660031818732653459[258] = 0;
   out_3660031818732653459[259] = 0;
   out_3660031818732653459[260] = 0;
   out_3660031818732653459[261] = 0;
   out_3660031818732653459[262] = 0;
   out_3660031818732653459[263] = 0;
   out_3660031818732653459[264] = 0;
   out_3660031818732653459[265] = 0;
   out_3660031818732653459[266] = 1;
   out_3660031818732653459[267] = 0;
   out_3660031818732653459[268] = 0;
   out_3660031818732653459[269] = 0;
   out_3660031818732653459[270] = 0;
   out_3660031818732653459[271] = 0;
   out_3660031818732653459[272] = 0;
   out_3660031818732653459[273] = 0;
   out_3660031818732653459[274] = 0;
   out_3660031818732653459[275] = 0;
   out_3660031818732653459[276] = 0;
   out_3660031818732653459[277] = 0;
   out_3660031818732653459[278] = 0;
   out_3660031818732653459[279] = 0;
   out_3660031818732653459[280] = 0;
   out_3660031818732653459[281] = 0;
   out_3660031818732653459[282] = 0;
   out_3660031818732653459[283] = 0;
   out_3660031818732653459[284] = 0;
   out_3660031818732653459[285] = 1;
   out_3660031818732653459[286] = 0;
   out_3660031818732653459[287] = 0;
   out_3660031818732653459[288] = 0;
   out_3660031818732653459[289] = 0;
   out_3660031818732653459[290] = 0;
   out_3660031818732653459[291] = 0;
   out_3660031818732653459[292] = 0;
   out_3660031818732653459[293] = 0;
   out_3660031818732653459[294] = 0;
   out_3660031818732653459[295] = 0;
   out_3660031818732653459[296] = 0;
   out_3660031818732653459[297] = 0;
   out_3660031818732653459[298] = 0;
   out_3660031818732653459[299] = 0;
   out_3660031818732653459[300] = 0;
   out_3660031818732653459[301] = 0;
   out_3660031818732653459[302] = 0;
   out_3660031818732653459[303] = 0;
   out_3660031818732653459[304] = 1;
   out_3660031818732653459[305] = 0;
   out_3660031818732653459[306] = 0;
   out_3660031818732653459[307] = 0;
   out_3660031818732653459[308] = 0;
   out_3660031818732653459[309] = 0;
   out_3660031818732653459[310] = 0;
   out_3660031818732653459[311] = 0;
   out_3660031818732653459[312] = 0;
   out_3660031818732653459[313] = 0;
   out_3660031818732653459[314] = 0;
   out_3660031818732653459[315] = 0;
   out_3660031818732653459[316] = 0;
   out_3660031818732653459[317] = 0;
   out_3660031818732653459[318] = 0;
   out_3660031818732653459[319] = 0;
   out_3660031818732653459[320] = 0;
   out_3660031818732653459[321] = 0;
   out_3660031818732653459[322] = 0;
   out_3660031818732653459[323] = 1;
}
void h_4(double *state, double *unused, double *out_4354770932396622955) {
   out_4354770932396622955[0] = state[6] + state[9];
   out_4354770932396622955[1] = state[7] + state[10];
   out_4354770932396622955[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3140573770318941521) {
   out_3140573770318941521[0] = 0;
   out_3140573770318941521[1] = 0;
   out_3140573770318941521[2] = 0;
   out_3140573770318941521[3] = 0;
   out_3140573770318941521[4] = 0;
   out_3140573770318941521[5] = 0;
   out_3140573770318941521[6] = 1;
   out_3140573770318941521[7] = 0;
   out_3140573770318941521[8] = 0;
   out_3140573770318941521[9] = 1;
   out_3140573770318941521[10] = 0;
   out_3140573770318941521[11] = 0;
   out_3140573770318941521[12] = 0;
   out_3140573770318941521[13] = 0;
   out_3140573770318941521[14] = 0;
   out_3140573770318941521[15] = 0;
   out_3140573770318941521[16] = 0;
   out_3140573770318941521[17] = 0;
   out_3140573770318941521[18] = 0;
   out_3140573770318941521[19] = 0;
   out_3140573770318941521[20] = 0;
   out_3140573770318941521[21] = 0;
   out_3140573770318941521[22] = 0;
   out_3140573770318941521[23] = 0;
   out_3140573770318941521[24] = 0;
   out_3140573770318941521[25] = 1;
   out_3140573770318941521[26] = 0;
   out_3140573770318941521[27] = 0;
   out_3140573770318941521[28] = 1;
   out_3140573770318941521[29] = 0;
   out_3140573770318941521[30] = 0;
   out_3140573770318941521[31] = 0;
   out_3140573770318941521[32] = 0;
   out_3140573770318941521[33] = 0;
   out_3140573770318941521[34] = 0;
   out_3140573770318941521[35] = 0;
   out_3140573770318941521[36] = 0;
   out_3140573770318941521[37] = 0;
   out_3140573770318941521[38] = 0;
   out_3140573770318941521[39] = 0;
   out_3140573770318941521[40] = 0;
   out_3140573770318941521[41] = 0;
   out_3140573770318941521[42] = 0;
   out_3140573770318941521[43] = 0;
   out_3140573770318941521[44] = 1;
   out_3140573770318941521[45] = 0;
   out_3140573770318941521[46] = 0;
   out_3140573770318941521[47] = 1;
   out_3140573770318941521[48] = 0;
   out_3140573770318941521[49] = 0;
   out_3140573770318941521[50] = 0;
   out_3140573770318941521[51] = 0;
   out_3140573770318941521[52] = 0;
   out_3140573770318941521[53] = 0;
}
void h_10(double *state, double *unused, double *out_8942219874713773227) {
   out_8942219874713773227[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8942219874713773227[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8942219874713773227[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5705253479912587073) {
   out_5705253479912587073[0] = 0;
   out_5705253479912587073[1] = 9.8100000000000005*cos(state[1]);
   out_5705253479912587073[2] = 0;
   out_5705253479912587073[3] = 0;
   out_5705253479912587073[4] = -state[8];
   out_5705253479912587073[5] = state[7];
   out_5705253479912587073[6] = 0;
   out_5705253479912587073[7] = state[5];
   out_5705253479912587073[8] = -state[4];
   out_5705253479912587073[9] = 0;
   out_5705253479912587073[10] = 0;
   out_5705253479912587073[11] = 0;
   out_5705253479912587073[12] = 1;
   out_5705253479912587073[13] = 0;
   out_5705253479912587073[14] = 0;
   out_5705253479912587073[15] = 1;
   out_5705253479912587073[16] = 0;
   out_5705253479912587073[17] = 0;
   out_5705253479912587073[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5705253479912587073[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5705253479912587073[20] = 0;
   out_5705253479912587073[21] = state[8];
   out_5705253479912587073[22] = 0;
   out_5705253479912587073[23] = -state[6];
   out_5705253479912587073[24] = -state[5];
   out_5705253479912587073[25] = 0;
   out_5705253479912587073[26] = state[3];
   out_5705253479912587073[27] = 0;
   out_5705253479912587073[28] = 0;
   out_5705253479912587073[29] = 0;
   out_5705253479912587073[30] = 0;
   out_5705253479912587073[31] = 1;
   out_5705253479912587073[32] = 0;
   out_5705253479912587073[33] = 0;
   out_5705253479912587073[34] = 1;
   out_5705253479912587073[35] = 0;
   out_5705253479912587073[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5705253479912587073[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5705253479912587073[38] = 0;
   out_5705253479912587073[39] = -state[7];
   out_5705253479912587073[40] = state[6];
   out_5705253479912587073[41] = 0;
   out_5705253479912587073[42] = state[4];
   out_5705253479912587073[43] = -state[3];
   out_5705253479912587073[44] = 0;
   out_5705253479912587073[45] = 0;
   out_5705253479912587073[46] = 0;
   out_5705253479912587073[47] = 0;
   out_5705253479912587073[48] = 0;
   out_5705253479912587073[49] = 0;
   out_5705253479912587073[50] = 1;
   out_5705253479912587073[51] = 0;
   out_5705253479912587073[52] = 0;
   out_5705253479912587073[53] = 1;
}
void h_13(double *state, double *unused, double *out_5867183224538439243) {
   out_5867183224538439243[0] = state[3];
   out_5867183224538439243[1] = state[4];
   out_5867183224538439243[2] = state[5];
}
void H_13(double *state, double *unused, double *out_71700055013391280) {
   out_71700055013391280[0] = 0;
   out_71700055013391280[1] = 0;
   out_71700055013391280[2] = 0;
   out_71700055013391280[3] = 1;
   out_71700055013391280[4] = 0;
   out_71700055013391280[5] = 0;
   out_71700055013391280[6] = 0;
   out_71700055013391280[7] = 0;
   out_71700055013391280[8] = 0;
   out_71700055013391280[9] = 0;
   out_71700055013391280[10] = 0;
   out_71700055013391280[11] = 0;
   out_71700055013391280[12] = 0;
   out_71700055013391280[13] = 0;
   out_71700055013391280[14] = 0;
   out_71700055013391280[15] = 0;
   out_71700055013391280[16] = 0;
   out_71700055013391280[17] = 0;
   out_71700055013391280[18] = 0;
   out_71700055013391280[19] = 0;
   out_71700055013391280[20] = 0;
   out_71700055013391280[21] = 0;
   out_71700055013391280[22] = 1;
   out_71700055013391280[23] = 0;
   out_71700055013391280[24] = 0;
   out_71700055013391280[25] = 0;
   out_71700055013391280[26] = 0;
   out_71700055013391280[27] = 0;
   out_71700055013391280[28] = 0;
   out_71700055013391280[29] = 0;
   out_71700055013391280[30] = 0;
   out_71700055013391280[31] = 0;
   out_71700055013391280[32] = 0;
   out_71700055013391280[33] = 0;
   out_71700055013391280[34] = 0;
   out_71700055013391280[35] = 0;
   out_71700055013391280[36] = 0;
   out_71700055013391280[37] = 0;
   out_71700055013391280[38] = 0;
   out_71700055013391280[39] = 0;
   out_71700055013391280[40] = 0;
   out_71700055013391280[41] = 1;
   out_71700055013391280[42] = 0;
   out_71700055013391280[43] = 0;
   out_71700055013391280[44] = 0;
   out_71700055013391280[45] = 0;
   out_71700055013391280[46] = 0;
   out_71700055013391280[47] = 0;
   out_71700055013391280[48] = 0;
   out_71700055013391280[49] = 0;
   out_71700055013391280[50] = 0;
   out_71700055013391280[51] = 0;
   out_71700055013391280[52] = 0;
   out_71700055013391280[53] = 0;
}
void h_14(double *state, double *unused, double *out_4155160495787210910) {
   out_4155160495787210910[0] = state[6];
   out_4155160495787210910[1] = state[7];
   out_4155160495787210910[2] = state[8];
}
void H_14(double *state, double *unused, double *out_822667086020543008) {
   out_822667086020543008[0] = 0;
   out_822667086020543008[1] = 0;
   out_822667086020543008[2] = 0;
   out_822667086020543008[3] = 0;
   out_822667086020543008[4] = 0;
   out_822667086020543008[5] = 0;
   out_822667086020543008[6] = 1;
   out_822667086020543008[7] = 0;
   out_822667086020543008[8] = 0;
   out_822667086020543008[9] = 0;
   out_822667086020543008[10] = 0;
   out_822667086020543008[11] = 0;
   out_822667086020543008[12] = 0;
   out_822667086020543008[13] = 0;
   out_822667086020543008[14] = 0;
   out_822667086020543008[15] = 0;
   out_822667086020543008[16] = 0;
   out_822667086020543008[17] = 0;
   out_822667086020543008[18] = 0;
   out_822667086020543008[19] = 0;
   out_822667086020543008[20] = 0;
   out_822667086020543008[21] = 0;
   out_822667086020543008[22] = 0;
   out_822667086020543008[23] = 0;
   out_822667086020543008[24] = 0;
   out_822667086020543008[25] = 1;
   out_822667086020543008[26] = 0;
   out_822667086020543008[27] = 0;
   out_822667086020543008[28] = 0;
   out_822667086020543008[29] = 0;
   out_822667086020543008[30] = 0;
   out_822667086020543008[31] = 0;
   out_822667086020543008[32] = 0;
   out_822667086020543008[33] = 0;
   out_822667086020543008[34] = 0;
   out_822667086020543008[35] = 0;
   out_822667086020543008[36] = 0;
   out_822667086020543008[37] = 0;
   out_822667086020543008[38] = 0;
   out_822667086020543008[39] = 0;
   out_822667086020543008[40] = 0;
   out_822667086020543008[41] = 0;
   out_822667086020543008[42] = 0;
   out_822667086020543008[43] = 0;
   out_822667086020543008[44] = 1;
   out_822667086020543008[45] = 0;
   out_822667086020543008[46] = 0;
   out_822667086020543008[47] = 0;
   out_822667086020543008[48] = 0;
   out_822667086020543008[49] = 0;
   out_822667086020543008[50] = 0;
   out_822667086020543008[51] = 0;
   out_822667086020543008[52] = 0;
   out_822667086020543008[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_6079659893886918220) {
  err_fun(nom_x, delta_x, out_6079659893886918220);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5200837164005369107) {
  inv_err_fun(nom_x, true_x, out_5200837164005369107);
}
void pose_H_mod_fun(double *state, double *out_1320875044412644660) {
  H_mod_fun(state, out_1320875044412644660);
}
void pose_f_fun(double *state, double dt, double *out_4957392939814811366) {
  f_fun(state,  dt, out_4957392939814811366);
}
void pose_F_fun(double *state, double dt, double *out_3660031818732653459) {
  F_fun(state,  dt, out_3660031818732653459);
}
void pose_h_4(double *state, double *unused, double *out_4354770932396622955) {
  h_4(state, unused, out_4354770932396622955);
}
void pose_H_4(double *state, double *unused, double *out_3140573770318941521) {
  H_4(state, unused, out_3140573770318941521);
}
void pose_h_10(double *state, double *unused, double *out_8942219874713773227) {
  h_10(state, unused, out_8942219874713773227);
}
void pose_H_10(double *state, double *unused, double *out_5705253479912587073) {
  H_10(state, unused, out_5705253479912587073);
}
void pose_h_13(double *state, double *unused, double *out_5867183224538439243) {
  h_13(state, unused, out_5867183224538439243);
}
void pose_H_13(double *state, double *unused, double *out_71700055013391280) {
  H_13(state, unused, out_71700055013391280);
}
void pose_h_14(double *state, double *unused, double *out_4155160495787210910) {
  h_14(state, unused, out_4155160495787210910);
}
void pose_H_14(double *state, double *unused, double *out_822667086020543008) {
  H_14(state, unused, out_822667086020543008);
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
