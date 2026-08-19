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
void err_fun(double *nom_x, double *delta_x, double *out_7828077856483360191) {
   out_7828077856483360191[0] = delta_x[0] + nom_x[0];
   out_7828077856483360191[1] = delta_x[1] + nom_x[1];
   out_7828077856483360191[2] = delta_x[2] + nom_x[2];
   out_7828077856483360191[3] = delta_x[3] + nom_x[3];
   out_7828077856483360191[4] = delta_x[4] + nom_x[4];
   out_7828077856483360191[5] = delta_x[5] + nom_x[5];
   out_7828077856483360191[6] = delta_x[6] + nom_x[6];
   out_7828077856483360191[7] = delta_x[7] + nom_x[7];
   out_7828077856483360191[8] = delta_x[8] + nom_x[8];
   out_7828077856483360191[9] = delta_x[9] + nom_x[9];
   out_7828077856483360191[10] = delta_x[10] + nom_x[10];
   out_7828077856483360191[11] = delta_x[11] + nom_x[11];
   out_7828077856483360191[12] = delta_x[12] + nom_x[12];
   out_7828077856483360191[13] = delta_x[13] + nom_x[13];
   out_7828077856483360191[14] = delta_x[14] + nom_x[14];
   out_7828077856483360191[15] = delta_x[15] + nom_x[15];
   out_7828077856483360191[16] = delta_x[16] + nom_x[16];
   out_7828077856483360191[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_978622641958652250) {
   out_978622641958652250[0] = -nom_x[0] + true_x[0];
   out_978622641958652250[1] = -nom_x[1] + true_x[1];
   out_978622641958652250[2] = -nom_x[2] + true_x[2];
   out_978622641958652250[3] = -nom_x[3] + true_x[3];
   out_978622641958652250[4] = -nom_x[4] + true_x[4];
   out_978622641958652250[5] = -nom_x[5] + true_x[5];
   out_978622641958652250[6] = -nom_x[6] + true_x[6];
   out_978622641958652250[7] = -nom_x[7] + true_x[7];
   out_978622641958652250[8] = -nom_x[8] + true_x[8];
   out_978622641958652250[9] = -nom_x[9] + true_x[9];
   out_978622641958652250[10] = -nom_x[10] + true_x[10];
   out_978622641958652250[11] = -nom_x[11] + true_x[11];
   out_978622641958652250[12] = -nom_x[12] + true_x[12];
   out_978622641958652250[13] = -nom_x[13] + true_x[13];
   out_978622641958652250[14] = -nom_x[14] + true_x[14];
   out_978622641958652250[15] = -nom_x[15] + true_x[15];
   out_978622641958652250[16] = -nom_x[16] + true_x[16];
   out_978622641958652250[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7441553898687288237) {
   out_7441553898687288237[0] = 1.0;
   out_7441553898687288237[1] = 0.0;
   out_7441553898687288237[2] = 0.0;
   out_7441553898687288237[3] = 0.0;
   out_7441553898687288237[4] = 0.0;
   out_7441553898687288237[5] = 0.0;
   out_7441553898687288237[6] = 0.0;
   out_7441553898687288237[7] = 0.0;
   out_7441553898687288237[8] = 0.0;
   out_7441553898687288237[9] = 0.0;
   out_7441553898687288237[10] = 0.0;
   out_7441553898687288237[11] = 0.0;
   out_7441553898687288237[12] = 0.0;
   out_7441553898687288237[13] = 0.0;
   out_7441553898687288237[14] = 0.0;
   out_7441553898687288237[15] = 0.0;
   out_7441553898687288237[16] = 0.0;
   out_7441553898687288237[17] = 0.0;
   out_7441553898687288237[18] = 0.0;
   out_7441553898687288237[19] = 1.0;
   out_7441553898687288237[20] = 0.0;
   out_7441553898687288237[21] = 0.0;
   out_7441553898687288237[22] = 0.0;
   out_7441553898687288237[23] = 0.0;
   out_7441553898687288237[24] = 0.0;
   out_7441553898687288237[25] = 0.0;
   out_7441553898687288237[26] = 0.0;
   out_7441553898687288237[27] = 0.0;
   out_7441553898687288237[28] = 0.0;
   out_7441553898687288237[29] = 0.0;
   out_7441553898687288237[30] = 0.0;
   out_7441553898687288237[31] = 0.0;
   out_7441553898687288237[32] = 0.0;
   out_7441553898687288237[33] = 0.0;
   out_7441553898687288237[34] = 0.0;
   out_7441553898687288237[35] = 0.0;
   out_7441553898687288237[36] = 0.0;
   out_7441553898687288237[37] = 0.0;
   out_7441553898687288237[38] = 1.0;
   out_7441553898687288237[39] = 0.0;
   out_7441553898687288237[40] = 0.0;
   out_7441553898687288237[41] = 0.0;
   out_7441553898687288237[42] = 0.0;
   out_7441553898687288237[43] = 0.0;
   out_7441553898687288237[44] = 0.0;
   out_7441553898687288237[45] = 0.0;
   out_7441553898687288237[46] = 0.0;
   out_7441553898687288237[47] = 0.0;
   out_7441553898687288237[48] = 0.0;
   out_7441553898687288237[49] = 0.0;
   out_7441553898687288237[50] = 0.0;
   out_7441553898687288237[51] = 0.0;
   out_7441553898687288237[52] = 0.0;
   out_7441553898687288237[53] = 0.0;
   out_7441553898687288237[54] = 0.0;
   out_7441553898687288237[55] = 0.0;
   out_7441553898687288237[56] = 0.0;
   out_7441553898687288237[57] = 1.0;
   out_7441553898687288237[58] = 0.0;
   out_7441553898687288237[59] = 0.0;
   out_7441553898687288237[60] = 0.0;
   out_7441553898687288237[61] = 0.0;
   out_7441553898687288237[62] = 0.0;
   out_7441553898687288237[63] = 0.0;
   out_7441553898687288237[64] = 0.0;
   out_7441553898687288237[65] = 0.0;
   out_7441553898687288237[66] = 0.0;
   out_7441553898687288237[67] = 0.0;
   out_7441553898687288237[68] = 0.0;
   out_7441553898687288237[69] = 0.0;
   out_7441553898687288237[70] = 0.0;
   out_7441553898687288237[71] = 0.0;
   out_7441553898687288237[72] = 0.0;
   out_7441553898687288237[73] = 0.0;
   out_7441553898687288237[74] = 0.0;
   out_7441553898687288237[75] = 0.0;
   out_7441553898687288237[76] = 1.0;
   out_7441553898687288237[77] = 0.0;
   out_7441553898687288237[78] = 0.0;
   out_7441553898687288237[79] = 0.0;
   out_7441553898687288237[80] = 0.0;
   out_7441553898687288237[81] = 0.0;
   out_7441553898687288237[82] = 0.0;
   out_7441553898687288237[83] = 0.0;
   out_7441553898687288237[84] = 0.0;
   out_7441553898687288237[85] = 0.0;
   out_7441553898687288237[86] = 0.0;
   out_7441553898687288237[87] = 0.0;
   out_7441553898687288237[88] = 0.0;
   out_7441553898687288237[89] = 0.0;
   out_7441553898687288237[90] = 0.0;
   out_7441553898687288237[91] = 0.0;
   out_7441553898687288237[92] = 0.0;
   out_7441553898687288237[93] = 0.0;
   out_7441553898687288237[94] = 0.0;
   out_7441553898687288237[95] = 1.0;
   out_7441553898687288237[96] = 0.0;
   out_7441553898687288237[97] = 0.0;
   out_7441553898687288237[98] = 0.0;
   out_7441553898687288237[99] = 0.0;
   out_7441553898687288237[100] = 0.0;
   out_7441553898687288237[101] = 0.0;
   out_7441553898687288237[102] = 0.0;
   out_7441553898687288237[103] = 0.0;
   out_7441553898687288237[104] = 0.0;
   out_7441553898687288237[105] = 0.0;
   out_7441553898687288237[106] = 0.0;
   out_7441553898687288237[107] = 0.0;
   out_7441553898687288237[108] = 0.0;
   out_7441553898687288237[109] = 0.0;
   out_7441553898687288237[110] = 0.0;
   out_7441553898687288237[111] = 0.0;
   out_7441553898687288237[112] = 0.0;
   out_7441553898687288237[113] = 0.0;
   out_7441553898687288237[114] = 1.0;
   out_7441553898687288237[115] = 0.0;
   out_7441553898687288237[116] = 0.0;
   out_7441553898687288237[117] = 0.0;
   out_7441553898687288237[118] = 0.0;
   out_7441553898687288237[119] = 0.0;
   out_7441553898687288237[120] = 0.0;
   out_7441553898687288237[121] = 0.0;
   out_7441553898687288237[122] = 0.0;
   out_7441553898687288237[123] = 0.0;
   out_7441553898687288237[124] = 0.0;
   out_7441553898687288237[125] = 0.0;
   out_7441553898687288237[126] = 0.0;
   out_7441553898687288237[127] = 0.0;
   out_7441553898687288237[128] = 0.0;
   out_7441553898687288237[129] = 0.0;
   out_7441553898687288237[130] = 0.0;
   out_7441553898687288237[131] = 0.0;
   out_7441553898687288237[132] = 0.0;
   out_7441553898687288237[133] = 1.0;
   out_7441553898687288237[134] = 0.0;
   out_7441553898687288237[135] = 0.0;
   out_7441553898687288237[136] = 0.0;
   out_7441553898687288237[137] = 0.0;
   out_7441553898687288237[138] = 0.0;
   out_7441553898687288237[139] = 0.0;
   out_7441553898687288237[140] = 0.0;
   out_7441553898687288237[141] = 0.0;
   out_7441553898687288237[142] = 0.0;
   out_7441553898687288237[143] = 0.0;
   out_7441553898687288237[144] = 0.0;
   out_7441553898687288237[145] = 0.0;
   out_7441553898687288237[146] = 0.0;
   out_7441553898687288237[147] = 0.0;
   out_7441553898687288237[148] = 0.0;
   out_7441553898687288237[149] = 0.0;
   out_7441553898687288237[150] = 0.0;
   out_7441553898687288237[151] = 0.0;
   out_7441553898687288237[152] = 1.0;
   out_7441553898687288237[153] = 0.0;
   out_7441553898687288237[154] = 0.0;
   out_7441553898687288237[155] = 0.0;
   out_7441553898687288237[156] = 0.0;
   out_7441553898687288237[157] = 0.0;
   out_7441553898687288237[158] = 0.0;
   out_7441553898687288237[159] = 0.0;
   out_7441553898687288237[160] = 0.0;
   out_7441553898687288237[161] = 0.0;
   out_7441553898687288237[162] = 0.0;
   out_7441553898687288237[163] = 0.0;
   out_7441553898687288237[164] = 0.0;
   out_7441553898687288237[165] = 0.0;
   out_7441553898687288237[166] = 0.0;
   out_7441553898687288237[167] = 0.0;
   out_7441553898687288237[168] = 0.0;
   out_7441553898687288237[169] = 0.0;
   out_7441553898687288237[170] = 0.0;
   out_7441553898687288237[171] = 1.0;
   out_7441553898687288237[172] = 0.0;
   out_7441553898687288237[173] = 0.0;
   out_7441553898687288237[174] = 0.0;
   out_7441553898687288237[175] = 0.0;
   out_7441553898687288237[176] = 0.0;
   out_7441553898687288237[177] = 0.0;
   out_7441553898687288237[178] = 0.0;
   out_7441553898687288237[179] = 0.0;
   out_7441553898687288237[180] = 0.0;
   out_7441553898687288237[181] = 0.0;
   out_7441553898687288237[182] = 0.0;
   out_7441553898687288237[183] = 0.0;
   out_7441553898687288237[184] = 0.0;
   out_7441553898687288237[185] = 0.0;
   out_7441553898687288237[186] = 0.0;
   out_7441553898687288237[187] = 0.0;
   out_7441553898687288237[188] = 0.0;
   out_7441553898687288237[189] = 0.0;
   out_7441553898687288237[190] = 1.0;
   out_7441553898687288237[191] = 0.0;
   out_7441553898687288237[192] = 0.0;
   out_7441553898687288237[193] = 0.0;
   out_7441553898687288237[194] = 0.0;
   out_7441553898687288237[195] = 0.0;
   out_7441553898687288237[196] = 0.0;
   out_7441553898687288237[197] = 0.0;
   out_7441553898687288237[198] = 0.0;
   out_7441553898687288237[199] = 0.0;
   out_7441553898687288237[200] = 0.0;
   out_7441553898687288237[201] = 0.0;
   out_7441553898687288237[202] = 0.0;
   out_7441553898687288237[203] = 0.0;
   out_7441553898687288237[204] = 0.0;
   out_7441553898687288237[205] = 0.0;
   out_7441553898687288237[206] = 0.0;
   out_7441553898687288237[207] = 0.0;
   out_7441553898687288237[208] = 0.0;
   out_7441553898687288237[209] = 1.0;
   out_7441553898687288237[210] = 0.0;
   out_7441553898687288237[211] = 0.0;
   out_7441553898687288237[212] = 0.0;
   out_7441553898687288237[213] = 0.0;
   out_7441553898687288237[214] = 0.0;
   out_7441553898687288237[215] = 0.0;
   out_7441553898687288237[216] = 0.0;
   out_7441553898687288237[217] = 0.0;
   out_7441553898687288237[218] = 0.0;
   out_7441553898687288237[219] = 0.0;
   out_7441553898687288237[220] = 0.0;
   out_7441553898687288237[221] = 0.0;
   out_7441553898687288237[222] = 0.0;
   out_7441553898687288237[223] = 0.0;
   out_7441553898687288237[224] = 0.0;
   out_7441553898687288237[225] = 0.0;
   out_7441553898687288237[226] = 0.0;
   out_7441553898687288237[227] = 0.0;
   out_7441553898687288237[228] = 1.0;
   out_7441553898687288237[229] = 0.0;
   out_7441553898687288237[230] = 0.0;
   out_7441553898687288237[231] = 0.0;
   out_7441553898687288237[232] = 0.0;
   out_7441553898687288237[233] = 0.0;
   out_7441553898687288237[234] = 0.0;
   out_7441553898687288237[235] = 0.0;
   out_7441553898687288237[236] = 0.0;
   out_7441553898687288237[237] = 0.0;
   out_7441553898687288237[238] = 0.0;
   out_7441553898687288237[239] = 0.0;
   out_7441553898687288237[240] = 0.0;
   out_7441553898687288237[241] = 0.0;
   out_7441553898687288237[242] = 0.0;
   out_7441553898687288237[243] = 0.0;
   out_7441553898687288237[244] = 0.0;
   out_7441553898687288237[245] = 0.0;
   out_7441553898687288237[246] = 0.0;
   out_7441553898687288237[247] = 1.0;
   out_7441553898687288237[248] = 0.0;
   out_7441553898687288237[249] = 0.0;
   out_7441553898687288237[250] = 0.0;
   out_7441553898687288237[251] = 0.0;
   out_7441553898687288237[252] = 0.0;
   out_7441553898687288237[253] = 0.0;
   out_7441553898687288237[254] = 0.0;
   out_7441553898687288237[255] = 0.0;
   out_7441553898687288237[256] = 0.0;
   out_7441553898687288237[257] = 0.0;
   out_7441553898687288237[258] = 0.0;
   out_7441553898687288237[259] = 0.0;
   out_7441553898687288237[260] = 0.0;
   out_7441553898687288237[261] = 0.0;
   out_7441553898687288237[262] = 0.0;
   out_7441553898687288237[263] = 0.0;
   out_7441553898687288237[264] = 0.0;
   out_7441553898687288237[265] = 0.0;
   out_7441553898687288237[266] = 1.0;
   out_7441553898687288237[267] = 0.0;
   out_7441553898687288237[268] = 0.0;
   out_7441553898687288237[269] = 0.0;
   out_7441553898687288237[270] = 0.0;
   out_7441553898687288237[271] = 0.0;
   out_7441553898687288237[272] = 0.0;
   out_7441553898687288237[273] = 0.0;
   out_7441553898687288237[274] = 0.0;
   out_7441553898687288237[275] = 0.0;
   out_7441553898687288237[276] = 0.0;
   out_7441553898687288237[277] = 0.0;
   out_7441553898687288237[278] = 0.0;
   out_7441553898687288237[279] = 0.0;
   out_7441553898687288237[280] = 0.0;
   out_7441553898687288237[281] = 0.0;
   out_7441553898687288237[282] = 0.0;
   out_7441553898687288237[283] = 0.0;
   out_7441553898687288237[284] = 0.0;
   out_7441553898687288237[285] = 1.0;
   out_7441553898687288237[286] = 0.0;
   out_7441553898687288237[287] = 0.0;
   out_7441553898687288237[288] = 0.0;
   out_7441553898687288237[289] = 0.0;
   out_7441553898687288237[290] = 0.0;
   out_7441553898687288237[291] = 0.0;
   out_7441553898687288237[292] = 0.0;
   out_7441553898687288237[293] = 0.0;
   out_7441553898687288237[294] = 0.0;
   out_7441553898687288237[295] = 0.0;
   out_7441553898687288237[296] = 0.0;
   out_7441553898687288237[297] = 0.0;
   out_7441553898687288237[298] = 0.0;
   out_7441553898687288237[299] = 0.0;
   out_7441553898687288237[300] = 0.0;
   out_7441553898687288237[301] = 0.0;
   out_7441553898687288237[302] = 0.0;
   out_7441553898687288237[303] = 0.0;
   out_7441553898687288237[304] = 1.0;
   out_7441553898687288237[305] = 0.0;
   out_7441553898687288237[306] = 0.0;
   out_7441553898687288237[307] = 0.0;
   out_7441553898687288237[308] = 0.0;
   out_7441553898687288237[309] = 0.0;
   out_7441553898687288237[310] = 0.0;
   out_7441553898687288237[311] = 0.0;
   out_7441553898687288237[312] = 0.0;
   out_7441553898687288237[313] = 0.0;
   out_7441553898687288237[314] = 0.0;
   out_7441553898687288237[315] = 0.0;
   out_7441553898687288237[316] = 0.0;
   out_7441553898687288237[317] = 0.0;
   out_7441553898687288237[318] = 0.0;
   out_7441553898687288237[319] = 0.0;
   out_7441553898687288237[320] = 0.0;
   out_7441553898687288237[321] = 0.0;
   out_7441553898687288237[322] = 0.0;
   out_7441553898687288237[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8648120814934185415) {
   out_8648120814934185415[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8648120814934185415[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8648120814934185415[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8648120814934185415[3] = dt*state[12] + state[3];
   out_8648120814934185415[4] = dt*state[13] + state[4];
   out_8648120814934185415[5] = dt*state[14] + state[5];
   out_8648120814934185415[6] = state[6];
   out_8648120814934185415[7] = state[7];
   out_8648120814934185415[8] = state[8];
   out_8648120814934185415[9] = state[9];
   out_8648120814934185415[10] = state[10];
   out_8648120814934185415[11] = state[11];
   out_8648120814934185415[12] = state[12];
   out_8648120814934185415[13] = state[13];
   out_8648120814934185415[14] = state[14];
   out_8648120814934185415[15] = state[15];
   out_8648120814934185415[16] = state[16];
   out_8648120814934185415[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5073381682457521558) {
   out_5073381682457521558[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5073381682457521558[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5073381682457521558[2] = 0;
   out_5073381682457521558[3] = 0;
   out_5073381682457521558[4] = 0;
   out_5073381682457521558[5] = 0;
   out_5073381682457521558[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5073381682457521558[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5073381682457521558[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5073381682457521558[9] = 0;
   out_5073381682457521558[10] = 0;
   out_5073381682457521558[11] = 0;
   out_5073381682457521558[12] = 0;
   out_5073381682457521558[13] = 0;
   out_5073381682457521558[14] = 0;
   out_5073381682457521558[15] = 0;
   out_5073381682457521558[16] = 0;
   out_5073381682457521558[17] = 0;
   out_5073381682457521558[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5073381682457521558[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5073381682457521558[20] = 0;
   out_5073381682457521558[21] = 0;
   out_5073381682457521558[22] = 0;
   out_5073381682457521558[23] = 0;
   out_5073381682457521558[24] = 0;
   out_5073381682457521558[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5073381682457521558[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5073381682457521558[27] = 0;
   out_5073381682457521558[28] = 0;
   out_5073381682457521558[29] = 0;
   out_5073381682457521558[30] = 0;
   out_5073381682457521558[31] = 0;
   out_5073381682457521558[32] = 0;
   out_5073381682457521558[33] = 0;
   out_5073381682457521558[34] = 0;
   out_5073381682457521558[35] = 0;
   out_5073381682457521558[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5073381682457521558[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5073381682457521558[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5073381682457521558[39] = 0;
   out_5073381682457521558[40] = 0;
   out_5073381682457521558[41] = 0;
   out_5073381682457521558[42] = 0;
   out_5073381682457521558[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5073381682457521558[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5073381682457521558[45] = 0;
   out_5073381682457521558[46] = 0;
   out_5073381682457521558[47] = 0;
   out_5073381682457521558[48] = 0;
   out_5073381682457521558[49] = 0;
   out_5073381682457521558[50] = 0;
   out_5073381682457521558[51] = 0;
   out_5073381682457521558[52] = 0;
   out_5073381682457521558[53] = 0;
   out_5073381682457521558[54] = 0;
   out_5073381682457521558[55] = 0;
   out_5073381682457521558[56] = 0;
   out_5073381682457521558[57] = 1;
   out_5073381682457521558[58] = 0;
   out_5073381682457521558[59] = 0;
   out_5073381682457521558[60] = 0;
   out_5073381682457521558[61] = 0;
   out_5073381682457521558[62] = 0;
   out_5073381682457521558[63] = 0;
   out_5073381682457521558[64] = 0;
   out_5073381682457521558[65] = 0;
   out_5073381682457521558[66] = dt;
   out_5073381682457521558[67] = 0;
   out_5073381682457521558[68] = 0;
   out_5073381682457521558[69] = 0;
   out_5073381682457521558[70] = 0;
   out_5073381682457521558[71] = 0;
   out_5073381682457521558[72] = 0;
   out_5073381682457521558[73] = 0;
   out_5073381682457521558[74] = 0;
   out_5073381682457521558[75] = 0;
   out_5073381682457521558[76] = 1;
   out_5073381682457521558[77] = 0;
   out_5073381682457521558[78] = 0;
   out_5073381682457521558[79] = 0;
   out_5073381682457521558[80] = 0;
   out_5073381682457521558[81] = 0;
   out_5073381682457521558[82] = 0;
   out_5073381682457521558[83] = 0;
   out_5073381682457521558[84] = 0;
   out_5073381682457521558[85] = dt;
   out_5073381682457521558[86] = 0;
   out_5073381682457521558[87] = 0;
   out_5073381682457521558[88] = 0;
   out_5073381682457521558[89] = 0;
   out_5073381682457521558[90] = 0;
   out_5073381682457521558[91] = 0;
   out_5073381682457521558[92] = 0;
   out_5073381682457521558[93] = 0;
   out_5073381682457521558[94] = 0;
   out_5073381682457521558[95] = 1;
   out_5073381682457521558[96] = 0;
   out_5073381682457521558[97] = 0;
   out_5073381682457521558[98] = 0;
   out_5073381682457521558[99] = 0;
   out_5073381682457521558[100] = 0;
   out_5073381682457521558[101] = 0;
   out_5073381682457521558[102] = 0;
   out_5073381682457521558[103] = 0;
   out_5073381682457521558[104] = dt;
   out_5073381682457521558[105] = 0;
   out_5073381682457521558[106] = 0;
   out_5073381682457521558[107] = 0;
   out_5073381682457521558[108] = 0;
   out_5073381682457521558[109] = 0;
   out_5073381682457521558[110] = 0;
   out_5073381682457521558[111] = 0;
   out_5073381682457521558[112] = 0;
   out_5073381682457521558[113] = 0;
   out_5073381682457521558[114] = 1;
   out_5073381682457521558[115] = 0;
   out_5073381682457521558[116] = 0;
   out_5073381682457521558[117] = 0;
   out_5073381682457521558[118] = 0;
   out_5073381682457521558[119] = 0;
   out_5073381682457521558[120] = 0;
   out_5073381682457521558[121] = 0;
   out_5073381682457521558[122] = 0;
   out_5073381682457521558[123] = 0;
   out_5073381682457521558[124] = 0;
   out_5073381682457521558[125] = 0;
   out_5073381682457521558[126] = 0;
   out_5073381682457521558[127] = 0;
   out_5073381682457521558[128] = 0;
   out_5073381682457521558[129] = 0;
   out_5073381682457521558[130] = 0;
   out_5073381682457521558[131] = 0;
   out_5073381682457521558[132] = 0;
   out_5073381682457521558[133] = 1;
   out_5073381682457521558[134] = 0;
   out_5073381682457521558[135] = 0;
   out_5073381682457521558[136] = 0;
   out_5073381682457521558[137] = 0;
   out_5073381682457521558[138] = 0;
   out_5073381682457521558[139] = 0;
   out_5073381682457521558[140] = 0;
   out_5073381682457521558[141] = 0;
   out_5073381682457521558[142] = 0;
   out_5073381682457521558[143] = 0;
   out_5073381682457521558[144] = 0;
   out_5073381682457521558[145] = 0;
   out_5073381682457521558[146] = 0;
   out_5073381682457521558[147] = 0;
   out_5073381682457521558[148] = 0;
   out_5073381682457521558[149] = 0;
   out_5073381682457521558[150] = 0;
   out_5073381682457521558[151] = 0;
   out_5073381682457521558[152] = 1;
   out_5073381682457521558[153] = 0;
   out_5073381682457521558[154] = 0;
   out_5073381682457521558[155] = 0;
   out_5073381682457521558[156] = 0;
   out_5073381682457521558[157] = 0;
   out_5073381682457521558[158] = 0;
   out_5073381682457521558[159] = 0;
   out_5073381682457521558[160] = 0;
   out_5073381682457521558[161] = 0;
   out_5073381682457521558[162] = 0;
   out_5073381682457521558[163] = 0;
   out_5073381682457521558[164] = 0;
   out_5073381682457521558[165] = 0;
   out_5073381682457521558[166] = 0;
   out_5073381682457521558[167] = 0;
   out_5073381682457521558[168] = 0;
   out_5073381682457521558[169] = 0;
   out_5073381682457521558[170] = 0;
   out_5073381682457521558[171] = 1;
   out_5073381682457521558[172] = 0;
   out_5073381682457521558[173] = 0;
   out_5073381682457521558[174] = 0;
   out_5073381682457521558[175] = 0;
   out_5073381682457521558[176] = 0;
   out_5073381682457521558[177] = 0;
   out_5073381682457521558[178] = 0;
   out_5073381682457521558[179] = 0;
   out_5073381682457521558[180] = 0;
   out_5073381682457521558[181] = 0;
   out_5073381682457521558[182] = 0;
   out_5073381682457521558[183] = 0;
   out_5073381682457521558[184] = 0;
   out_5073381682457521558[185] = 0;
   out_5073381682457521558[186] = 0;
   out_5073381682457521558[187] = 0;
   out_5073381682457521558[188] = 0;
   out_5073381682457521558[189] = 0;
   out_5073381682457521558[190] = 1;
   out_5073381682457521558[191] = 0;
   out_5073381682457521558[192] = 0;
   out_5073381682457521558[193] = 0;
   out_5073381682457521558[194] = 0;
   out_5073381682457521558[195] = 0;
   out_5073381682457521558[196] = 0;
   out_5073381682457521558[197] = 0;
   out_5073381682457521558[198] = 0;
   out_5073381682457521558[199] = 0;
   out_5073381682457521558[200] = 0;
   out_5073381682457521558[201] = 0;
   out_5073381682457521558[202] = 0;
   out_5073381682457521558[203] = 0;
   out_5073381682457521558[204] = 0;
   out_5073381682457521558[205] = 0;
   out_5073381682457521558[206] = 0;
   out_5073381682457521558[207] = 0;
   out_5073381682457521558[208] = 0;
   out_5073381682457521558[209] = 1;
   out_5073381682457521558[210] = 0;
   out_5073381682457521558[211] = 0;
   out_5073381682457521558[212] = 0;
   out_5073381682457521558[213] = 0;
   out_5073381682457521558[214] = 0;
   out_5073381682457521558[215] = 0;
   out_5073381682457521558[216] = 0;
   out_5073381682457521558[217] = 0;
   out_5073381682457521558[218] = 0;
   out_5073381682457521558[219] = 0;
   out_5073381682457521558[220] = 0;
   out_5073381682457521558[221] = 0;
   out_5073381682457521558[222] = 0;
   out_5073381682457521558[223] = 0;
   out_5073381682457521558[224] = 0;
   out_5073381682457521558[225] = 0;
   out_5073381682457521558[226] = 0;
   out_5073381682457521558[227] = 0;
   out_5073381682457521558[228] = 1;
   out_5073381682457521558[229] = 0;
   out_5073381682457521558[230] = 0;
   out_5073381682457521558[231] = 0;
   out_5073381682457521558[232] = 0;
   out_5073381682457521558[233] = 0;
   out_5073381682457521558[234] = 0;
   out_5073381682457521558[235] = 0;
   out_5073381682457521558[236] = 0;
   out_5073381682457521558[237] = 0;
   out_5073381682457521558[238] = 0;
   out_5073381682457521558[239] = 0;
   out_5073381682457521558[240] = 0;
   out_5073381682457521558[241] = 0;
   out_5073381682457521558[242] = 0;
   out_5073381682457521558[243] = 0;
   out_5073381682457521558[244] = 0;
   out_5073381682457521558[245] = 0;
   out_5073381682457521558[246] = 0;
   out_5073381682457521558[247] = 1;
   out_5073381682457521558[248] = 0;
   out_5073381682457521558[249] = 0;
   out_5073381682457521558[250] = 0;
   out_5073381682457521558[251] = 0;
   out_5073381682457521558[252] = 0;
   out_5073381682457521558[253] = 0;
   out_5073381682457521558[254] = 0;
   out_5073381682457521558[255] = 0;
   out_5073381682457521558[256] = 0;
   out_5073381682457521558[257] = 0;
   out_5073381682457521558[258] = 0;
   out_5073381682457521558[259] = 0;
   out_5073381682457521558[260] = 0;
   out_5073381682457521558[261] = 0;
   out_5073381682457521558[262] = 0;
   out_5073381682457521558[263] = 0;
   out_5073381682457521558[264] = 0;
   out_5073381682457521558[265] = 0;
   out_5073381682457521558[266] = 1;
   out_5073381682457521558[267] = 0;
   out_5073381682457521558[268] = 0;
   out_5073381682457521558[269] = 0;
   out_5073381682457521558[270] = 0;
   out_5073381682457521558[271] = 0;
   out_5073381682457521558[272] = 0;
   out_5073381682457521558[273] = 0;
   out_5073381682457521558[274] = 0;
   out_5073381682457521558[275] = 0;
   out_5073381682457521558[276] = 0;
   out_5073381682457521558[277] = 0;
   out_5073381682457521558[278] = 0;
   out_5073381682457521558[279] = 0;
   out_5073381682457521558[280] = 0;
   out_5073381682457521558[281] = 0;
   out_5073381682457521558[282] = 0;
   out_5073381682457521558[283] = 0;
   out_5073381682457521558[284] = 0;
   out_5073381682457521558[285] = 1;
   out_5073381682457521558[286] = 0;
   out_5073381682457521558[287] = 0;
   out_5073381682457521558[288] = 0;
   out_5073381682457521558[289] = 0;
   out_5073381682457521558[290] = 0;
   out_5073381682457521558[291] = 0;
   out_5073381682457521558[292] = 0;
   out_5073381682457521558[293] = 0;
   out_5073381682457521558[294] = 0;
   out_5073381682457521558[295] = 0;
   out_5073381682457521558[296] = 0;
   out_5073381682457521558[297] = 0;
   out_5073381682457521558[298] = 0;
   out_5073381682457521558[299] = 0;
   out_5073381682457521558[300] = 0;
   out_5073381682457521558[301] = 0;
   out_5073381682457521558[302] = 0;
   out_5073381682457521558[303] = 0;
   out_5073381682457521558[304] = 1;
   out_5073381682457521558[305] = 0;
   out_5073381682457521558[306] = 0;
   out_5073381682457521558[307] = 0;
   out_5073381682457521558[308] = 0;
   out_5073381682457521558[309] = 0;
   out_5073381682457521558[310] = 0;
   out_5073381682457521558[311] = 0;
   out_5073381682457521558[312] = 0;
   out_5073381682457521558[313] = 0;
   out_5073381682457521558[314] = 0;
   out_5073381682457521558[315] = 0;
   out_5073381682457521558[316] = 0;
   out_5073381682457521558[317] = 0;
   out_5073381682457521558[318] = 0;
   out_5073381682457521558[319] = 0;
   out_5073381682457521558[320] = 0;
   out_5073381682457521558[321] = 0;
   out_5073381682457521558[322] = 0;
   out_5073381682457521558[323] = 1;
}
void h_4(double *state, double *unused, double *out_2401275546657747080) {
   out_2401275546657747080[0] = state[6] + state[9];
   out_2401275546657747080[1] = state[7] + state[10];
   out_2401275546657747080[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1593472091935329516) {
   out_1593472091935329516[0] = 0;
   out_1593472091935329516[1] = 0;
   out_1593472091935329516[2] = 0;
   out_1593472091935329516[3] = 0;
   out_1593472091935329516[4] = 0;
   out_1593472091935329516[5] = 0;
   out_1593472091935329516[6] = 1;
   out_1593472091935329516[7] = 0;
   out_1593472091935329516[8] = 0;
   out_1593472091935329516[9] = 1;
   out_1593472091935329516[10] = 0;
   out_1593472091935329516[11] = 0;
   out_1593472091935329516[12] = 0;
   out_1593472091935329516[13] = 0;
   out_1593472091935329516[14] = 0;
   out_1593472091935329516[15] = 0;
   out_1593472091935329516[16] = 0;
   out_1593472091935329516[17] = 0;
   out_1593472091935329516[18] = 0;
   out_1593472091935329516[19] = 0;
   out_1593472091935329516[20] = 0;
   out_1593472091935329516[21] = 0;
   out_1593472091935329516[22] = 0;
   out_1593472091935329516[23] = 0;
   out_1593472091935329516[24] = 0;
   out_1593472091935329516[25] = 1;
   out_1593472091935329516[26] = 0;
   out_1593472091935329516[27] = 0;
   out_1593472091935329516[28] = 1;
   out_1593472091935329516[29] = 0;
   out_1593472091935329516[30] = 0;
   out_1593472091935329516[31] = 0;
   out_1593472091935329516[32] = 0;
   out_1593472091935329516[33] = 0;
   out_1593472091935329516[34] = 0;
   out_1593472091935329516[35] = 0;
   out_1593472091935329516[36] = 0;
   out_1593472091935329516[37] = 0;
   out_1593472091935329516[38] = 0;
   out_1593472091935329516[39] = 0;
   out_1593472091935329516[40] = 0;
   out_1593472091935329516[41] = 0;
   out_1593472091935329516[42] = 0;
   out_1593472091935329516[43] = 0;
   out_1593472091935329516[44] = 1;
   out_1593472091935329516[45] = 0;
   out_1593472091935329516[46] = 0;
   out_1593472091935329516[47] = 1;
   out_1593472091935329516[48] = 0;
   out_1593472091935329516[49] = 0;
   out_1593472091935329516[50] = 0;
   out_1593472091935329516[51] = 0;
   out_1593472091935329516[52] = 0;
   out_1593472091935329516[53] = 0;
}
void h_10(double *state, double *unused, double *out_7020895229304053766) {
   out_7020895229304053766[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_7020895229304053766[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_7020895229304053766[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_299233475658510513) {
   out_299233475658510513[0] = 0;
   out_299233475658510513[1] = 9.8100000000000005*cos(state[1]);
   out_299233475658510513[2] = 0;
   out_299233475658510513[3] = 0;
   out_299233475658510513[4] = -state[8];
   out_299233475658510513[5] = state[7];
   out_299233475658510513[6] = 0;
   out_299233475658510513[7] = state[5];
   out_299233475658510513[8] = -state[4];
   out_299233475658510513[9] = 0;
   out_299233475658510513[10] = 0;
   out_299233475658510513[11] = 0;
   out_299233475658510513[12] = 1;
   out_299233475658510513[13] = 0;
   out_299233475658510513[14] = 0;
   out_299233475658510513[15] = 1;
   out_299233475658510513[16] = 0;
   out_299233475658510513[17] = 0;
   out_299233475658510513[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_299233475658510513[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_299233475658510513[20] = 0;
   out_299233475658510513[21] = state[8];
   out_299233475658510513[22] = 0;
   out_299233475658510513[23] = -state[6];
   out_299233475658510513[24] = -state[5];
   out_299233475658510513[25] = 0;
   out_299233475658510513[26] = state[3];
   out_299233475658510513[27] = 0;
   out_299233475658510513[28] = 0;
   out_299233475658510513[29] = 0;
   out_299233475658510513[30] = 0;
   out_299233475658510513[31] = 1;
   out_299233475658510513[32] = 0;
   out_299233475658510513[33] = 0;
   out_299233475658510513[34] = 1;
   out_299233475658510513[35] = 0;
   out_299233475658510513[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_299233475658510513[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_299233475658510513[38] = 0;
   out_299233475658510513[39] = -state[7];
   out_299233475658510513[40] = state[6];
   out_299233475658510513[41] = 0;
   out_299233475658510513[42] = state[4];
   out_299233475658510513[43] = -state[3];
   out_299233475658510513[44] = 0;
   out_299233475658510513[45] = 0;
   out_299233475658510513[46] = 0;
   out_299233475658510513[47] = 0;
   out_299233475658510513[48] = 0;
   out_299233475658510513[49] = 0;
   out_299233475658510513[50] = 1;
   out_299233475658510513[51] = 0;
   out_299233475658510513[52] = 0;
   out_299233475658510513[53] = 1;
}
void h_13(double *state, double *unused, double *out_2810480351238834931) {
   out_2810480351238834931[0] = state[3];
   out_2810480351238834931[1] = state[4];
   out_2810480351238834931[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4805745917267662317) {
   out_4805745917267662317[0] = 0;
   out_4805745917267662317[1] = 0;
   out_4805745917267662317[2] = 0;
   out_4805745917267662317[3] = 1;
   out_4805745917267662317[4] = 0;
   out_4805745917267662317[5] = 0;
   out_4805745917267662317[6] = 0;
   out_4805745917267662317[7] = 0;
   out_4805745917267662317[8] = 0;
   out_4805745917267662317[9] = 0;
   out_4805745917267662317[10] = 0;
   out_4805745917267662317[11] = 0;
   out_4805745917267662317[12] = 0;
   out_4805745917267662317[13] = 0;
   out_4805745917267662317[14] = 0;
   out_4805745917267662317[15] = 0;
   out_4805745917267662317[16] = 0;
   out_4805745917267662317[17] = 0;
   out_4805745917267662317[18] = 0;
   out_4805745917267662317[19] = 0;
   out_4805745917267662317[20] = 0;
   out_4805745917267662317[21] = 0;
   out_4805745917267662317[22] = 1;
   out_4805745917267662317[23] = 0;
   out_4805745917267662317[24] = 0;
   out_4805745917267662317[25] = 0;
   out_4805745917267662317[26] = 0;
   out_4805745917267662317[27] = 0;
   out_4805745917267662317[28] = 0;
   out_4805745917267662317[29] = 0;
   out_4805745917267662317[30] = 0;
   out_4805745917267662317[31] = 0;
   out_4805745917267662317[32] = 0;
   out_4805745917267662317[33] = 0;
   out_4805745917267662317[34] = 0;
   out_4805745917267662317[35] = 0;
   out_4805745917267662317[36] = 0;
   out_4805745917267662317[37] = 0;
   out_4805745917267662317[38] = 0;
   out_4805745917267662317[39] = 0;
   out_4805745917267662317[40] = 0;
   out_4805745917267662317[41] = 1;
   out_4805745917267662317[42] = 0;
   out_4805745917267662317[43] = 0;
   out_4805745917267662317[44] = 0;
   out_4805745917267662317[45] = 0;
   out_4805745917267662317[46] = 0;
   out_4805745917267662317[47] = 0;
   out_4805745917267662317[48] = 0;
   out_4805745917267662317[49] = 0;
   out_4805745917267662317[50] = 0;
   out_4805745917267662317[51] = 0;
   out_4805745917267662317[52] = 0;
   out_4805745917267662317[53] = 0;
}
void h_14(double *state, double *unused, double *out_6318162405249945056) {
   out_6318162405249945056[0] = state[6];
   out_6318162405249945056[1] = state[7];
   out_6318162405249945056[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5556712948274814045) {
   out_5556712948274814045[0] = 0;
   out_5556712948274814045[1] = 0;
   out_5556712948274814045[2] = 0;
   out_5556712948274814045[3] = 0;
   out_5556712948274814045[4] = 0;
   out_5556712948274814045[5] = 0;
   out_5556712948274814045[6] = 1;
   out_5556712948274814045[7] = 0;
   out_5556712948274814045[8] = 0;
   out_5556712948274814045[9] = 0;
   out_5556712948274814045[10] = 0;
   out_5556712948274814045[11] = 0;
   out_5556712948274814045[12] = 0;
   out_5556712948274814045[13] = 0;
   out_5556712948274814045[14] = 0;
   out_5556712948274814045[15] = 0;
   out_5556712948274814045[16] = 0;
   out_5556712948274814045[17] = 0;
   out_5556712948274814045[18] = 0;
   out_5556712948274814045[19] = 0;
   out_5556712948274814045[20] = 0;
   out_5556712948274814045[21] = 0;
   out_5556712948274814045[22] = 0;
   out_5556712948274814045[23] = 0;
   out_5556712948274814045[24] = 0;
   out_5556712948274814045[25] = 1;
   out_5556712948274814045[26] = 0;
   out_5556712948274814045[27] = 0;
   out_5556712948274814045[28] = 0;
   out_5556712948274814045[29] = 0;
   out_5556712948274814045[30] = 0;
   out_5556712948274814045[31] = 0;
   out_5556712948274814045[32] = 0;
   out_5556712948274814045[33] = 0;
   out_5556712948274814045[34] = 0;
   out_5556712948274814045[35] = 0;
   out_5556712948274814045[36] = 0;
   out_5556712948274814045[37] = 0;
   out_5556712948274814045[38] = 0;
   out_5556712948274814045[39] = 0;
   out_5556712948274814045[40] = 0;
   out_5556712948274814045[41] = 0;
   out_5556712948274814045[42] = 0;
   out_5556712948274814045[43] = 0;
   out_5556712948274814045[44] = 1;
   out_5556712948274814045[45] = 0;
   out_5556712948274814045[46] = 0;
   out_5556712948274814045[47] = 0;
   out_5556712948274814045[48] = 0;
   out_5556712948274814045[49] = 0;
   out_5556712948274814045[50] = 0;
   out_5556712948274814045[51] = 0;
   out_5556712948274814045[52] = 0;
   out_5556712948274814045[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7828077856483360191) {
  err_fun(nom_x, delta_x, out_7828077856483360191);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_978622641958652250) {
  inv_err_fun(nom_x, true_x, out_978622641958652250);
}
void pose_H_mod_fun(double *state, double *out_7441553898687288237) {
  H_mod_fun(state, out_7441553898687288237);
}
void pose_f_fun(double *state, double dt, double *out_8648120814934185415) {
  f_fun(state,  dt, out_8648120814934185415);
}
void pose_F_fun(double *state, double dt, double *out_5073381682457521558) {
  F_fun(state,  dt, out_5073381682457521558);
}
void pose_h_4(double *state, double *unused, double *out_2401275546657747080) {
  h_4(state, unused, out_2401275546657747080);
}
void pose_H_4(double *state, double *unused, double *out_1593472091935329516) {
  H_4(state, unused, out_1593472091935329516);
}
void pose_h_10(double *state, double *unused, double *out_7020895229304053766) {
  h_10(state, unused, out_7020895229304053766);
}
void pose_H_10(double *state, double *unused, double *out_299233475658510513) {
  H_10(state, unused, out_299233475658510513);
}
void pose_h_13(double *state, double *unused, double *out_2810480351238834931) {
  h_13(state, unused, out_2810480351238834931);
}
void pose_H_13(double *state, double *unused, double *out_4805745917267662317) {
  H_13(state, unused, out_4805745917267662317);
}
void pose_h_14(double *state, double *unused, double *out_6318162405249945056) {
  h_14(state, unused, out_6318162405249945056);
}
void pose_H_14(double *state, double *unused, double *out_5556712948274814045) {
  H_14(state, unused, out_5556712948274814045);
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
