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
void err_fun(double *nom_x, double *delta_x, double *out_2423125642091007723) {
   out_2423125642091007723[0] = delta_x[0] + nom_x[0];
   out_2423125642091007723[1] = delta_x[1] + nom_x[1];
   out_2423125642091007723[2] = delta_x[2] + nom_x[2];
   out_2423125642091007723[3] = delta_x[3] + nom_x[3];
   out_2423125642091007723[4] = delta_x[4] + nom_x[4];
   out_2423125642091007723[5] = delta_x[5] + nom_x[5];
   out_2423125642091007723[6] = delta_x[6] + nom_x[6];
   out_2423125642091007723[7] = delta_x[7] + nom_x[7];
   out_2423125642091007723[8] = delta_x[8] + nom_x[8];
   out_2423125642091007723[9] = delta_x[9] + nom_x[9];
   out_2423125642091007723[10] = delta_x[10] + nom_x[10];
   out_2423125642091007723[11] = delta_x[11] + nom_x[11];
   out_2423125642091007723[12] = delta_x[12] + nom_x[12];
   out_2423125642091007723[13] = delta_x[13] + nom_x[13];
   out_2423125642091007723[14] = delta_x[14] + nom_x[14];
   out_2423125642091007723[15] = delta_x[15] + nom_x[15];
   out_2423125642091007723[16] = delta_x[16] + nom_x[16];
   out_2423125642091007723[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1501585610038659930) {
   out_1501585610038659930[0] = -nom_x[0] + true_x[0];
   out_1501585610038659930[1] = -nom_x[1] + true_x[1];
   out_1501585610038659930[2] = -nom_x[2] + true_x[2];
   out_1501585610038659930[3] = -nom_x[3] + true_x[3];
   out_1501585610038659930[4] = -nom_x[4] + true_x[4];
   out_1501585610038659930[5] = -nom_x[5] + true_x[5];
   out_1501585610038659930[6] = -nom_x[6] + true_x[6];
   out_1501585610038659930[7] = -nom_x[7] + true_x[7];
   out_1501585610038659930[8] = -nom_x[8] + true_x[8];
   out_1501585610038659930[9] = -nom_x[9] + true_x[9];
   out_1501585610038659930[10] = -nom_x[10] + true_x[10];
   out_1501585610038659930[11] = -nom_x[11] + true_x[11];
   out_1501585610038659930[12] = -nom_x[12] + true_x[12];
   out_1501585610038659930[13] = -nom_x[13] + true_x[13];
   out_1501585610038659930[14] = -nom_x[14] + true_x[14];
   out_1501585610038659930[15] = -nom_x[15] + true_x[15];
   out_1501585610038659930[16] = -nom_x[16] + true_x[16];
   out_1501585610038659930[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_313504174478215792) {
   out_313504174478215792[0] = 1.0;
   out_313504174478215792[1] = 0.0;
   out_313504174478215792[2] = 0.0;
   out_313504174478215792[3] = 0.0;
   out_313504174478215792[4] = 0.0;
   out_313504174478215792[5] = 0.0;
   out_313504174478215792[6] = 0.0;
   out_313504174478215792[7] = 0.0;
   out_313504174478215792[8] = 0.0;
   out_313504174478215792[9] = 0.0;
   out_313504174478215792[10] = 0.0;
   out_313504174478215792[11] = 0.0;
   out_313504174478215792[12] = 0.0;
   out_313504174478215792[13] = 0.0;
   out_313504174478215792[14] = 0.0;
   out_313504174478215792[15] = 0.0;
   out_313504174478215792[16] = 0.0;
   out_313504174478215792[17] = 0.0;
   out_313504174478215792[18] = 0.0;
   out_313504174478215792[19] = 1.0;
   out_313504174478215792[20] = 0.0;
   out_313504174478215792[21] = 0.0;
   out_313504174478215792[22] = 0.0;
   out_313504174478215792[23] = 0.0;
   out_313504174478215792[24] = 0.0;
   out_313504174478215792[25] = 0.0;
   out_313504174478215792[26] = 0.0;
   out_313504174478215792[27] = 0.0;
   out_313504174478215792[28] = 0.0;
   out_313504174478215792[29] = 0.0;
   out_313504174478215792[30] = 0.0;
   out_313504174478215792[31] = 0.0;
   out_313504174478215792[32] = 0.0;
   out_313504174478215792[33] = 0.0;
   out_313504174478215792[34] = 0.0;
   out_313504174478215792[35] = 0.0;
   out_313504174478215792[36] = 0.0;
   out_313504174478215792[37] = 0.0;
   out_313504174478215792[38] = 1.0;
   out_313504174478215792[39] = 0.0;
   out_313504174478215792[40] = 0.0;
   out_313504174478215792[41] = 0.0;
   out_313504174478215792[42] = 0.0;
   out_313504174478215792[43] = 0.0;
   out_313504174478215792[44] = 0.0;
   out_313504174478215792[45] = 0.0;
   out_313504174478215792[46] = 0.0;
   out_313504174478215792[47] = 0.0;
   out_313504174478215792[48] = 0.0;
   out_313504174478215792[49] = 0.0;
   out_313504174478215792[50] = 0.0;
   out_313504174478215792[51] = 0.0;
   out_313504174478215792[52] = 0.0;
   out_313504174478215792[53] = 0.0;
   out_313504174478215792[54] = 0.0;
   out_313504174478215792[55] = 0.0;
   out_313504174478215792[56] = 0.0;
   out_313504174478215792[57] = 1.0;
   out_313504174478215792[58] = 0.0;
   out_313504174478215792[59] = 0.0;
   out_313504174478215792[60] = 0.0;
   out_313504174478215792[61] = 0.0;
   out_313504174478215792[62] = 0.0;
   out_313504174478215792[63] = 0.0;
   out_313504174478215792[64] = 0.0;
   out_313504174478215792[65] = 0.0;
   out_313504174478215792[66] = 0.0;
   out_313504174478215792[67] = 0.0;
   out_313504174478215792[68] = 0.0;
   out_313504174478215792[69] = 0.0;
   out_313504174478215792[70] = 0.0;
   out_313504174478215792[71] = 0.0;
   out_313504174478215792[72] = 0.0;
   out_313504174478215792[73] = 0.0;
   out_313504174478215792[74] = 0.0;
   out_313504174478215792[75] = 0.0;
   out_313504174478215792[76] = 1.0;
   out_313504174478215792[77] = 0.0;
   out_313504174478215792[78] = 0.0;
   out_313504174478215792[79] = 0.0;
   out_313504174478215792[80] = 0.0;
   out_313504174478215792[81] = 0.0;
   out_313504174478215792[82] = 0.0;
   out_313504174478215792[83] = 0.0;
   out_313504174478215792[84] = 0.0;
   out_313504174478215792[85] = 0.0;
   out_313504174478215792[86] = 0.0;
   out_313504174478215792[87] = 0.0;
   out_313504174478215792[88] = 0.0;
   out_313504174478215792[89] = 0.0;
   out_313504174478215792[90] = 0.0;
   out_313504174478215792[91] = 0.0;
   out_313504174478215792[92] = 0.0;
   out_313504174478215792[93] = 0.0;
   out_313504174478215792[94] = 0.0;
   out_313504174478215792[95] = 1.0;
   out_313504174478215792[96] = 0.0;
   out_313504174478215792[97] = 0.0;
   out_313504174478215792[98] = 0.0;
   out_313504174478215792[99] = 0.0;
   out_313504174478215792[100] = 0.0;
   out_313504174478215792[101] = 0.0;
   out_313504174478215792[102] = 0.0;
   out_313504174478215792[103] = 0.0;
   out_313504174478215792[104] = 0.0;
   out_313504174478215792[105] = 0.0;
   out_313504174478215792[106] = 0.0;
   out_313504174478215792[107] = 0.0;
   out_313504174478215792[108] = 0.0;
   out_313504174478215792[109] = 0.0;
   out_313504174478215792[110] = 0.0;
   out_313504174478215792[111] = 0.0;
   out_313504174478215792[112] = 0.0;
   out_313504174478215792[113] = 0.0;
   out_313504174478215792[114] = 1.0;
   out_313504174478215792[115] = 0.0;
   out_313504174478215792[116] = 0.0;
   out_313504174478215792[117] = 0.0;
   out_313504174478215792[118] = 0.0;
   out_313504174478215792[119] = 0.0;
   out_313504174478215792[120] = 0.0;
   out_313504174478215792[121] = 0.0;
   out_313504174478215792[122] = 0.0;
   out_313504174478215792[123] = 0.0;
   out_313504174478215792[124] = 0.0;
   out_313504174478215792[125] = 0.0;
   out_313504174478215792[126] = 0.0;
   out_313504174478215792[127] = 0.0;
   out_313504174478215792[128] = 0.0;
   out_313504174478215792[129] = 0.0;
   out_313504174478215792[130] = 0.0;
   out_313504174478215792[131] = 0.0;
   out_313504174478215792[132] = 0.0;
   out_313504174478215792[133] = 1.0;
   out_313504174478215792[134] = 0.0;
   out_313504174478215792[135] = 0.0;
   out_313504174478215792[136] = 0.0;
   out_313504174478215792[137] = 0.0;
   out_313504174478215792[138] = 0.0;
   out_313504174478215792[139] = 0.0;
   out_313504174478215792[140] = 0.0;
   out_313504174478215792[141] = 0.0;
   out_313504174478215792[142] = 0.0;
   out_313504174478215792[143] = 0.0;
   out_313504174478215792[144] = 0.0;
   out_313504174478215792[145] = 0.0;
   out_313504174478215792[146] = 0.0;
   out_313504174478215792[147] = 0.0;
   out_313504174478215792[148] = 0.0;
   out_313504174478215792[149] = 0.0;
   out_313504174478215792[150] = 0.0;
   out_313504174478215792[151] = 0.0;
   out_313504174478215792[152] = 1.0;
   out_313504174478215792[153] = 0.0;
   out_313504174478215792[154] = 0.0;
   out_313504174478215792[155] = 0.0;
   out_313504174478215792[156] = 0.0;
   out_313504174478215792[157] = 0.0;
   out_313504174478215792[158] = 0.0;
   out_313504174478215792[159] = 0.0;
   out_313504174478215792[160] = 0.0;
   out_313504174478215792[161] = 0.0;
   out_313504174478215792[162] = 0.0;
   out_313504174478215792[163] = 0.0;
   out_313504174478215792[164] = 0.0;
   out_313504174478215792[165] = 0.0;
   out_313504174478215792[166] = 0.0;
   out_313504174478215792[167] = 0.0;
   out_313504174478215792[168] = 0.0;
   out_313504174478215792[169] = 0.0;
   out_313504174478215792[170] = 0.0;
   out_313504174478215792[171] = 1.0;
   out_313504174478215792[172] = 0.0;
   out_313504174478215792[173] = 0.0;
   out_313504174478215792[174] = 0.0;
   out_313504174478215792[175] = 0.0;
   out_313504174478215792[176] = 0.0;
   out_313504174478215792[177] = 0.0;
   out_313504174478215792[178] = 0.0;
   out_313504174478215792[179] = 0.0;
   out_313504174478215792[180] = 0.0;
   out_313504174478215792[181] = 0.0;
   out_313504174478215792[182] = 0.0;
   out_313504174478215792[183] = 0.0;
   out_313504174478215792[184] = 0.0;
   out_313504174478215792[185] = 0.0;
   out_313504174478215792[186] = 0.0;
   out_313504174478215792[187] = 0.0;
   out_313504174478215792[188] = 0.0;
   out_313504174478215792[189] = 0.0;
   out_313504174478215792[190] = 1.0;
   out_313504174478215792[191] = 0.0;
   out_313504174478215792[192] = 0.0;
   out_313504174478215792[193] = 0.0;
   out_313504174478215792[194] = 0.0;
   out_313504174478215792[195] = 0.0;
   out_313504174478215792[196] = 0.0;
   out_313504174478215792[197] = 0.0;
   out_313504174478215792[198] = 0.0;
   out_313504174478215792[199] = 0.0;
   out_313504174478215792[200] = 0.0;
   out_313504174478215792[201] = 0.0;
   out_313504174478215792[202] = 0.0;
   out_313504174478215792[203] = 0.0;
   out_313504174478215792[204] = 0.0;
   out_313504174478215792[205] = 0.0;
   out_313504174478215792[206] = 0.0;
   out_313504174478215792[207] = 0.0;
   out_313504174478215792[208] = 0.0;
   out_313504174478215792[209] = 1.0;
   out_313504174478215792[210] = 0.0;
   out_313504174478215792[211] = 0.0;
   out_313504174478215792[212] = 0.0;
   out_313504174478215792[213] = 0.0;
   out_313504174478215792[214] = 0.0;
   out_313504174478215792[215] = 0.0;
   out_313504174478215792[216] = 0.0;
   out_313504174478215792[217] = 0.0;
   out_313504174478215792[218] = 0.0;
   out_313504174478215792[219] = 0.0;
   out_313504174478215792[220] = 0.0;
   out_313504174478215792[221] = 0.0;
   out_313504174478215792[222] = 0.0;
   out_313504174478215792[223] = 0.0;
   out_313504174478215792[224] = 0.0;
   out_313504174478215792[225] = 0.0;
   out_313504174478215792[226] = 0.0;
   out_313504174478215792[227] = 0.0;
   out_313504174478215792[228] = 1.0;
   out_313504174478215792[229] = 0.0;
   out_313504174478215792[230] = 0.0;
   out_313504174478215792[231] = 0.0;
   out_313504174478215792[232] = 0.0;
   out_313504174478215792[233] = 0.0;
   out_313504174478215792[234] = 0.0;
   out_313504174478215792[235] = 0.0;
   out_313504174478215792[236] = 0.0;
   out_313504174478215792[237] = 0.0;
   out_313504174478215792[238] = 0.0;
   out_313504174478215792[239] = 0.0;
   out_313504174478215792[240] = 0.0;
   out_313504174478215792[241] = 0.0;
   out_313504174478215792[242] = 0.0;
   out_313504174478215792[243] = 0.0;
   out_313504174478215792[244] = 0.0;
   out_313504174478215792[245] = 0.0;
   out_313504174478215792[246] = 0.0;
   out_313504174478215792[247] = 1.0;
   out_313504174478215792[248] = 0.0;
   out_313504174478215792[249] = 0.0;
   out_313504174478215792[250] = 0.0;
   out_313504174478215792[251] = 0.0;
   out_313504174478215792[252] = 0.0;
   out_313504174478215792[253] = 0.0;
   out_313504174478215792[254] = 0.0;
   out_313504174478215792[255] = 0.0;
   out_313504174478215792[256] = 0.0;
   out_313504174478215792[257] = 0.0;
   out_313504174478215792[258] = 0.0;
   out_313504174478215792[259] = 0.0;
   out_313504174478215792[260] = 0.0;
   out_313504174478215792[261] = 0.0;
   out_313504174478215792[262] = 0.0;
   out_313504174478215792[263] = 0.0;
   out_313504174478215792[264] = 0.0;
   out_313504174478215792[265] = 0.0;
   out_313504174478215792[266] = 1.0;
   out_313504174478215792[267] = 0.0;
   out_313504174478215792[268] = 0.0;
   out_313504174478215792[269] = 0.0;
   out_313504174478215792[270] = 0.0;
   out_313504174478215792[271] = 0.0;
   out_313504174478215792[272] = 0.0;
   out_313504174478215792[273] = 0.0;
   out_313504174478215792[274] = 0.0;
   out_313504174478215792[275] = 0.0;
   out_313504174478215792[276] = 0.0;
   out_313504174478215792[277] = 0.0;
   out_313504174478215792[278] = 0.0;
   out_313504174478215792[279] = 0.0;
   out_313504174478215792[280] = 0.0;
   out_313504174478215792[281] = 0.0;
   out_313504174478215792[282] = 0.0;
   out_313504174478215792[283] = 0.0;
   out_313504174478215792[284] = 0.0;
   out_313504174478215792[285] = 1.0;
   out_313504174478215792[286] = 0.0;
   out_313504174478215792[287] = 0.0;
   out_313504174478215792[288] = 0.0;
   out_313504174478215792[289] = 0.0;
   out_313504174478215792[290] = 0.0;
   out_313504174478215792[291] = 0.0;
   out_313504174478215792[292] = 0.0;
   out_313504174478215792[293] = 0.0;
   out_313504174478215792[294] = 0.0;
   out_313504174478215792[295] = 0.0;
   out_313504174478215792[296] = 0.0;
   out_313504174478215792[297] = 0.0;
   out_313504174478215792[298] = 0.0;
   out_313504174478215792[299] = 0.0;
   out_313504174478215792[300] = 0.0;
   out_313504174478215792[301] = 0.0;
   out_313504174478215792[302] = 0.0;
   out_313504174478215792[303] = 0.0;
   out_313504174478215792[304] = 1.0;
   out_313504174478215792[305] = 0.0;
   out_313504174478215792[306] = 0.0;
   out_313504174478215792[307] = 0.0;
   out_313504174478215792[308] = 0.0;
   out_313504174478215792[309] = 0.0;
   out_313504174478215792[310] = 0.0;
   out_313504174478215792[311] = 0.0;
   out_313504174478215792[312] = 0.0;
   out_313504174478215792[313] = 0.0;
   out_313504174478215792[314] = 0.0;
   out_313504174478215792[315] = 0.0;
   out_313504174478215792[316] = 0.0;
   out_313504174478215792[317] = 0.0;
   out_313504174478215792[318] = 0.0;
   out_313504174478215792[319] = 0.0;
   out_313504174478215792[320] = 0.0;
   out_313504174478215792[321] = 0.0;
   out_313504174478215792[322] = 0.0;
   out_313504174478215792[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8978916703249748052) {
   out_8978916703249748052[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8978916703249748052[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8978916703249748052[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8978916703249748052[3] = dt*state[12] + state[3];
   out_8978916703249748052[4] = dt*state[13] + state[4];
   out_8978916703249748052[5] = dt*state[14] + state[5];
   out_8978916703249748052[6] = state[6];
   out_8978916703249748052[7] = state[7];
   out_8978916703249748052[8] = state[8];
   out_8978916703249748052[9] = state[9];
   out_8978916703249748052[10] = state[10];
   out_8978916703249748052[11] = state[11];
   out_8978916703249748052[12] = state[12];
   out_8978916703249748052[13] = state[13];
   out_8978916703249748052[14] = state[14];
   out_8978916703249748052[15] = state[15];
   out_8978916703249748052[16] = state[16];
   out_8978916703249748052[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3060487946531646253) {
   out_3060487946531646253[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3060487946531646253[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3060487946531646253[2] = 0;
   out_3060487946531646253[3] = 0;
   out_3060487946531646253[4] = 0;
   out_3060487946531646253[5] = 0;
   out_3060487946531646253[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3060487946531646253[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3060487946531646253[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3060487946531646253[9] = 0;
   out_3060487946531646253[10] = 0;
   out_3060487946531646253[11] = 0;
   out_3060487946531646253[12] = 0;
   out_3060487946531646253[13] = 0;
   out_3060487946531646253[14] = 0;
   out_3060487946531646253[15] = 0;
   out_3060487946531646253[16] = 0;
   out_3060487946531646253[17] = 0;
   out_3060487946531646253[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3060487946531646253[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3060487946531646253[20] = 0;
   out_3060487946531646253[21] = 0;
   out_3060487946531646253[22] = 0;
   out_3060487946531646253[23] = 0;
   out_3060487946531646253[24] = 0;
   out_3060487946531646253[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3060487946531646253[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3060487946531646253[27] = 0;
   out_3060487946531646253[28] = 0;
   out_3060487946531646253[29] = 0;
   out_3060487946531646253[30] = 0;
   out_3060487946531646253[31] = 0;
   out_3060487946531646253[32] = 0;
   out_3060487946531646253[33] = 0;
   out_3060487946531646253[34] = 0;
   out_3060487946531646253[35] = 0;
   out_3060487946531646253[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3060487946531646253[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3060487946531646253[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3060487946531646253[39] = 0;
   out_3060487946531646253[40] = 0;
   out_3060487946531646253[41] = 0;
   out_3060487946531646253[42] = 0;
   out_3060487946531646253[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3060487946531646253[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3060487946531646253[45] = 0;
   out_3060487946531646253[46] = 0;
   out_3060487946531646253[47] = 0;
   out_3060487946531646253[48] = 0;
   out_3060487946531646253[49] = 0;
   out_3060487946531646253[50] = 0;
   out_3060487946531646253[51] = 0;
   out_3060487946531646253[52] = 0;
   out_3060487946531646253[53] = 0;
   out_3060487946531646253[54] = 0;
   out_3060487946531646253[55] = 0;
   out_3060487946531646253[56] = 0;
   out_3060487946531646253[57] = 1;
   out_3060487946531646253[58] = 0;
   out_3060487946531646253[59] = 0;
   out_3060487946531646253[60] = 0;
   out_3060487946531646253[61] = 0;
   out_3060487946531646253[62] = 0;
   out_3060487946531646253[63] = 0;
   out_3060487946531646253[64] = 0;
   out_3060487946531646253[65] = 0;
   out_3060487946531646253[66] = dt;
   out_3060487946531646253[67] = 0;
   out_3060487946531646253[68] = 0;
   out_3060487946531646253[69] = 0;
   out_3060487946531646253[70] = 0;
   out_3060487946531646253[71] = 0;
   out_3060487946531646253[72] = 0;
   out_3060487946531646253[73] = 0;
   out_3060487946531646253[74] = 0;
   out_3060487946531646253[75] = 0;
   out_3060487946531646253[76] = 1;
   out_3060487946531646253[77] = 0;
   out_3060487946531646253[78] = 0;
   out_3060487946531646253[79] = 0;
   out_3060487946531646253[80] = 0;
   out_3060487946531646253[81] = 0;
   out_3060487946531646253[82] = 0;
   out_3060487946531646253[83] = 0;
   out_3060487946531646253[84] = 0;
   out_3060487946531646253[85] = dt;
   out_3060487946531646253[86] = 0;
   out_3060487946531646253[87] = 0;
   out_3060487946531646253[88] = 0;
   out_3060487946531646253[89] = 0;
   out_3060487946531646253[90] = 0;
   out_3060487946531646253[91] = 0;
   out_3060487946531646253[92] = 0;
   out_3060487946531646253[93] = 0;
   out_3060487946531646253[94] = 0;
   out_3060487946531646253[95] = 1;
   out_3060487946531646253[96] = 0;
   out_3060487946531646253[97] = 0;
   out_3060487946531646253[98] = 0;
   out_3060487946531646253[99] = 0;
   out_3060487946531646253[100] = 0;
   out_3060487946531646253[101] = 0;
   out_3060487946531646253[102] = 0;
   out_3060487946531646253[103] = 0;
   out_3060487946531646253[104] = dt;
   out_3060487946531646253[105] = 0;
   out_3060487946531646253[106] = 0;
   out_3060487946531646253[107] = 0;
   out_3060487946531646253[108] = 0;
   out_3060487946531646253[109] = 0;
   out_3060487946531646253[110] = 0;
   out_3060487946531646253[111] = 0;
   out_3060487946531646253[112] = 0;
   out_3060487946531646253[113] = 0;
   out_3060487946531646253[114] = 1;
   out_3060487946531646253[115] = 0;
   out_3060487946531646253[116] = 0;
   out_3060487946531646253[117] = 0;
   out_3060487946531646253[118] = 0;
   out_3060487946531646253[119] = 0;
   out_3060487946531646253[120] = 0;
   out_3060487946531646253[121] = 0;
   out_3060487946531646253[122] = 0;
   out_3060487946531646253[123] = 0;
   out_3060487946531646253[124] = 0;
   out_3060487946531646253[125] = 0;
   out_3060487946531646253[126] = 0;
   out_3060487946531646253[127] = 0;
   out_3060487946531646253[128] = 0;
   out_3060487946531646253[129] = 0;
   out_3060487946531646253[130] = 0;
   out_3060487946531646253[131] = 0;
   out_3060487946531646253[132] = 0;
   out_3060487946531646253[133] = 1;
   out_3060487946531646253[134] = 0;
   out_3060487946531646253[135] = 0;
   out_3060487946531646253[136] = 0;
   out_3060487946531646253[137] = 0;
   out_3060487946531646253[138] = 0;
   out_3060487946531646253[139] = 0;
   out_3060487946531646253[140] = 0;
   out_3060487946531646253[141] = 0;
   out_3060487946531646253[142] = 0;
   out_3060487946531646253[143] = 0;
   out_3060487946531646253[144] = 0;
   out_3060487946531646253[145] = 0;
   out_3060487946531646253[146] = 0;
   out_3060487946531646253[147] = 0;
   out_3060487946531646253[148] = 0;
   out_3060487946531646253[149] = 0;
   out_3060487946531646253[150] = 0;
   out_3060487946531646253[151] = 0;
   out_3060487946531646253[152] = 1;
   out_3060487946531646253[153] = 0;
   out_3060487946531646253[154] = 0;
   out_3060487946531646253[155] = 0;
   out_3060487946531646253[156] = 0;
   out_3060487946531646253[157] = 0;
   out_3060487946531646253[158] = 0;
   out_3060487946531646253[159] = 0;
   out_3060487946531646253[160] = 0;
   out_3060487946531646253[161] = 0;
   out_3060487946531646253[162] = 0;
   out_3060487946531646253[163] = 0;
   out_3060487946531646253[164] = 0;
   out_3060487946531646253[165] = 0;
   out_3060487946531646253[166] = 0;
   out_3060487946531646253[167] = 0;
   out_3060487946531646253[168] = 0;
   out_3060487946531646253[169] = 0;
   out_3060487946531646253[170] = 0;
   out_3060487946531646253[171] = 1;
   out_3060487946531646253[172] = 0;
   out_3060487946531646253[173] = 0;
   out_3060487946531646253[174] = 0;
   out_3060487946531646253[175] = 0;
   out_3060487946531646253[176] = 0;
   out_3060487946531646253[177] = 0;
   out_3060487946531646253[178] = 0;
   out_3060487946531646253[179] = 0;
   out_3060487946531646253[180] = 0;
   out_3060487946531646253[181] = 0;
   out_3060487946531646253[182] = 0;
   out_3060487946531646253[183] = 0;
   out_3060487946531646253[184] = 0;
   out_3060487946531646253[185] = 0;
   out_3060487946531646253[186] = 0;
   out_3060487946531646253[187] = 0;
   out_3060487946531646253[188] = 0;
   out_3060487946531646253[189] = 0;
   out_3060487946531646253[190] = 1;
   out_3060487946531646253[191] = 0;
   out_3060487946531646253[192] = 0;
   out_3060487946531646253[193] = 0;
   out_3060487946531646253[194] = 0;
   out_3060487946531646253[195] = 0;
   out_3060487946531646253[196] = 0;
   out_3060487946531646253[197] = 0;
   out_3060487946531646253[198] = 0;
   out_3060487946531646253[199] = 0;
   out_3060487946531646253[200] = 0;
   out_3060487946531646253[201] = 0;
   out_3060487946531646253[202] = 0;
   out_3060487946531646253[203] = 0;
   out_3060487946531646253[204] = 0;
   out_3060487946531646253[205] = 0;
   out_3060487946531646253[206] = 0;
   out_3060487946531646253[207] = 0;
   out_3060487946531646253[208] = 0;
   out_3060487946531646253[209] = 1;
   out_3060487946531646253[210] = 0;
   out_3060487946531646253[211] = 0;
   out_3060487946531646253[212] = 0;
   out_3060487946531646253[213] = 0;
   out_3060487946531646253[214] = 0;
   out_3060487946531646253[215] = 0;
   out_3060487946531646253[216] = 0;
   out_3060487946531646253[217] = 0;
   out_3060487946531646253[218] = 0;
   out_3060487946531646253[219] = 0;
   out_3060487946531646253[220] = 0;
   out_3060487946531646253[221] = 0;
   out_3060487946531646253[222] = 0;
   out_3060487946531646253[223] = 0;
   out_3060487946531646253[224] = 0;
   out_3060487946531646253[225] = 0;
   out_3060487946531646253[226] = 0;
   out_3060487946531646253[227] = 0;
   out_3060487946531646253[228] = 1;
   out_3060487946531646253[229] = 0;
   out_3060487946531646253[230] = 0;
   out_3060487946531646253[231] = 0;
   out_3060487946531646253[232] = 0;
   out_3060487946531646253[233] = 0;
   out_3060487946531646253[234] = 0;
   out_3060487946531646253[235] = 0;
   out_3060487946531646253[236] = 0;
   out_3060487946531646253[237] = 0;
   out_3060487946531646253[238] = 0;
   out_3060487946531646253[239] = 0;
   out_3060487946531646253[240] = 0;
   out_3060487946531646253[241] = 0;
   out_3060487946531646253[242] = 0;
   out_3060487946531646253[243] = 0;
   out_3060487946531646253[244] = 0;
   out_3060487946531646253[245] = 0;
   out_3060487946531646253[246] = 0;
   out_3060487946531646253[247] = 1;
   out_3060487946531646253[248] = 0;
   out_3060487946531646253[249] = 0;
   out_3060487946531646253[250] = 0;
   out_3060487946531646253[251] = 0;
   out_3060487946531646253[252] = 0;
   out_3060487946531646253[253] = 0;
   out_3060487946531646253[254] = 0;
   out_3060487946531646253[255] = 0;
   out_3060487946531646253[256] = 0;
   out_3060487946531646253[257] = 0;
   out_3060487946531646253[258] = 0;
   out_3060487946531646253[259] = 0;
   out_3060487946531646253[260] = 0;
   out_3060487946531646253[261] = 0;
   out_3060487946531646253[262] = 0;
   out_3060487946531646253[263] = 0;
   out_3060487946531646253[264] = 0;
   out_3060487946531646253[265] = 0;
   out_3060487946531646253[266] = 1;
   out_3060487946531646253[267] = 0;
   out_3060487946531646253[268] = 0;
   out_3060487946531646253[269] = 0;
   out_3060487946531646253[270] = 0;
   out_3060487946531646253[271] = 0;
   out_3060487946531646253[272] = 0;
   out_3060487946531646253[273] = 0;
   out_3060487946531646253[274] = 0;
   out_3060487946531646253[275] = 0;
   out_3060487946531646253[276] = 0;
   out_3060487946531646253[277] = 0;
   out_3060487946531646253[278] = 0;
   out_3060487946531646253[279] = 0;
   out_3060487946531646253[280] = 0;
   out_3060487946531646253[281] = 0;
   out_3060487946531646253[282] = 0;
   out_3060487946531646253[283] = 0;
   out_3060487946531646253[284] = 0;
   out_3060487946531646253[285] = 1;
   out_3060487946531646253[286] = 0;
   out_3060487946531646253[287] = 0;
   out_3060487946531646253[288] = 0;
   out_3060487946531646253[289] = 0;
   out_3060487946531646253[290] = 0;
   out_3060487946531646253[291] = 0;
   out_3060487946531646253[292] = 0;
   out_3060487946531646253[293] = 0;
   out_3060487946531646253[294] = 0;
   out_3060487946531646253[295] = 0;
   out_3060487946531646253[296] = 0;
   out_3060487946531646253[297] = 0;
   out_3060487946531646253[298] = 0;
   out_3060487946531646253[299] = 0;
   out_3060487946531646253[300] = 0;
   out_3060487946531646253[301] = 0;
   out_3060487946531646253[302] = 0;
   out_3060487946531646253[303] = 0;
   out_3060487946531646253[304] = 1;
   out_3060487946531646253[305] = 0;
   out_3060487946531646253[306] = 0;
   out_3060487946531646253[307] = 0;
   out_3060487946531646253[308] = 0;
   out_3060487946531646253[309] = 0;
   out_3060487946531646253[310] = 0;
   out_3060487946531646253[311] = 0;
   out_3060487946531646253[312] = 0;
   out_3060487946531646253[313] = 0;
   out_3060487946531646253[314] = 0;
   out_3060487946531646253[315] = 0;
   out_3060487946531646253[316] = 0;
   out_3060487946531646253[317] = 0;
   out_3060487946531646253[318] = 0;
   out_3060487946531646253[319] = 0;
   out_3060487946531646253[320] = 0;
   out_3060487946531646253[321] = 0;
   out_3060487946531646253[322] = 0;
   out_3060487946531646253[323] = 1;
}
void h_4(double *state, double *unused, double *out_2072690755108230087) {
   out_2072690755108230087[0] = state[6] + state[9];
   out_2072690755108230087[1] = state[7] + state[10];
   out_2072690755108230087[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_440656827576496815) {
   out_440656827576496815[0] = 0;
   out_440656827576496815[1] = 0;
   out_440656827576496815[2] = 0;
   out_440656827576496815[3] = 0;
   out_440656827576496815[4] = 0;
   out_440656827576496815[5] = 0;
   out_440656827576496815[6] = 1;
   out_440656827576496815[7] = 0;
   out_440656827576496815[8] = 0;
   out_440656827576496815[9] = 1;
   out_440656827576496815[10] = 0;
   out_440656827576496815[11] = 0;
   out_440656827576496815[12] = 0;
   out_440656827576496815[13] = 0;
   out_440656827576496815[14] = 0;
   out_440656827576496815[15] = 0;
   out_440656827576496815[16] = 0;
   out_440656827576496815[17] = 0;
   out_440656827576496815[18] = 0;
   out_440656827576496815[19] = 0;
   out_440656827576496815[20] = 0;
   out_440656827576496815[21] = 0;
   out_440656827576496815[22] = 0;
   out_440656827576496815[23] = 0;
   out_440656827576496815[24] = 0;
   out_440656827576496815[25] = 1;
   out_440656827576496815[26] = 0;
   out_440656827576496815[27] = 0;
   out_440656827576496815[28] = 1;
   out_440656827576496815[29] = 0;
   out_440656827576496815[30] = 0;
   out_440656827576496815[31] = 0;
   out_440656827576496815[32] = 0;
   out_440656827576496815[33] = 0;
   out_440656827576496815[34] = 0;
   out_440656827576496815[35] = 0;
   out_440656827576496815[36] = 0;
   out_440656827576496815[37] = 0;
   out_440656827576496815[38] = 0;
   out_440656827576496815[39] = 0;
   out_440656827576496815[40] = 0;
   out_440656827576496815[41] = 0;
   out_440656827576496815[42] = 0;
   out_440656827576496815[43] = 0;
   out_440656827576496815[44] = 1;
   out_440656827576496815[45] = 0;
   out_440656827576496815[46] = 0;
   out_440656827576496815[47] = 1;
   out_440656827576496815[48] = 0;
   out_440656827576496815[49] = 0;
   out_440656827576496815[50] = 0;
   out_440656827576496815[51] = 0;
   out_440656827576496815[52] = 0;
   out_440656827576496815[53] = 0;
}
void h_10(double *state, double *unused, double *out_3685903144892211871) {
   out_3685903144892211871[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3685903144892211871[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3685903144892211871[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7274933657249705055) {
   out_7274933657249705055[0] = 0;
   out_7274933657249705055[1] = 9.8100000000000005*cos(state[1]);
   out_7274933657249705055[2] = 0;
   out_7274933657249705055[3] = 0;
   out_7274933657249705055[4] = -state[8];
   out_7274933657249705055[5] = state[7];
   out_7274933657249705055[6] = 0;
   out_7274933657249705055[7] = state[5];
   out_7274933657249705055[8] = -state[4];
   out_7274933657249705055[9] = 0;
   out_7274933657249705055[10] = 0;
   out_7274933657249705055[11] = 0;
   out_7274933657249705055[12] = 1;
   out_7274933657249705055[13] = 0;
   out_7274933657249705055[14] = 0;
   out_7274933657249705055[15] = 1;
   out_7274933657249705055[16] = 0;
   out_7274933657249705055[17] = 0;
   out_7274933657249705055[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7274933657249705055[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7274933657249705055[20] = 0;
   out_7274933657249705055[21] = state[8];
   out_7274933657249705055[22] = 0;
   out_7274933657249705055[23] = -state[6];
   out_7274933657249705055[24] = -state[5];
   out_7274933657249705055[25] = 0;
   out_7274933657249705055[26] = state[3];
   out_7274933657249705055[27] = 0;
   out_7274933657249705055[28] = 0;
   out_7274933657249705055[29] = 0;
   out_7274933657249705055[30] = 0;
   out_7274933657249705055[31] = 1;
   out_7274933657249705055[32] = 0;
   out_7274933657249705055[33] = 0;
   out_7274933657249705055[34] = 1;
   out_7274933657249705055[35] = 0;
   out_7274933657249705055[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7274933657249705055[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7274933657249705055[38] = 0;
   out_7274933657249705055[39] = -state[7];
   out_7274933657249705055[40] = state[6];
   out_7274933657249705055[41] = 0;
   out_7274933657249705055[42] = state[4];
   out_7274933657249705055[43] = -state[3];
   out_7274933657249705055[44] = 0;
   out_7274933657249705055[45] = 0;
   out_7274933657249705055[46] = 0;
   out_7274933657249705055[47] = 0;
   out_7274933657249705055[48] = 0;
   out_7274933657249705055[49] = 0;
   out_7274933657249705055[50] = 1;
   out_7274933657249705055[51] = 0;
   out_7274933657249705055[52] = 0;
   out_7274933657249705055[53] = 1;
}
void h_13(double *state, double *unused, double *out_7605941513603236476) {
   out_7605941513603236476[0] = state[3];
   out_7605941513603236476[1] = state[4];
   out_7605941513603236476[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3652930652908829616) {
   out_3652930652908829616[0] = 0;
   out_3652930652908829616[1] = 0;
   out_3652930652908829616[2] = 0;
   out_3652930652908829616[3] = 1;
   out_3652930652908829616[4] = 0;
   out_3652930652908829616[5] = 0;
   out_3652930652908829616[6] = 0;
   out_3652930652908829616[7] = 0;
   out_3652930652908829616[8] = 0;
   out_3652930652908829616[9] = 0;
   out_3652930652908829616[10] = 0;
   out_3652930652908829616[11] = 0;
   out_3652930652908829616[12] = 0;
   out_3652930652908829616[13] = 0;
   out_3652930652908829616[14] = 0;
   out_3652930652908829616[15] = 0;
   out_3652930652908829616[16] = 0;
   out_3652930652908829616[17] = 0;
   out_3652930652908829616[18] = 0;
   out_3652930652908829616[19] = 0;
   out_3652930652908829616[20] = 0;
   out_3652930652908829616[21] = 0;
   out_3652930652908829616[22] = 1;
   out_3652930652908829616[23] = 0;
   out_3652930652908829616[24] = 0;
   out_3652930652908829616[25] = 0;
   out_3652930652908829616[26] = 0;
   out_3652930652908829616[27] = 0;
   out_3652930652908829616[28] = 0;
   out_3652930652908829616[29] = 0;
   out_3652930652908829616[30] = 0;
   out_3652930652908829616[31] = 0;
   out_3652930652908829616[32] = 0;
   out_3652930652908829616[33] = 0;
   out_3652930652908829616[34] = 0;
   out_3652930652908829616[35] = 0;
   out_3652930652908829616[36] = 0;
   out_3652930652908829616[37] = 0;
   out_3652930652908829616[38] = 0;
   out_3652930652908829616[39] = 0;
   out_3652930652908829616[40] = 0;
   out_3652930652908829616[41] = 1;
   out_3652930652908829616[42] = 0;
   out_3652930652908829616[43] = 0;
   out_3652930652908829616[44] = 0;
   out_3652930652908829616[45] = 0;
   out_3652930652908829616[46] = 0;
   out_3652930652908829616[47] = 0;
   out_3652930652908829616[48] = 0;
   out_3652930652908829616[49] = 0;
   out_3652930652908829616[50] = 0;
   out_3652930652908829616[51] = 0;
   out_3652930652908829616[52] = 0;
   out_3652930652908829616[53] = 0;
}
void h_14(double *state, double *unused, double *out_732635666688386653) {
   out_732635666688386653[0] = state[6];
   out_732635666688386653[1] = state[7];
   out_732635666688386653[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4403897683915981344) {
   out_4403897683915981344[0] = 0;
   out_4403897683915981344[1] = 0;
   out_4403897683915981344[2] = 0;
   out_4403897683915981344[3] = 0;
   out_4403897683915981344[4] = 0;
   out_4403897683915981344[5] = 0;
   out_4403897683915981344[6] = 1;
   out_4403897683915981344[7] = 0;
   out_4403897683915981344[8] = 0;
   out_4403897683915981344[9] = 0;
   out_4403897683915981344[10] = 0;
   out_4403897683915981344[11] = 0;
   out_4403897683915981344[12] = 0;
   out_4403897683915981344[13] = 0;
   out_4403897683915981344[14] = 0;
   out_4403897683915981344[15] = 0;
   out_4403897683915981344[16] = 0;
   out_4403897683915981344[17] = 0;
   out_4403897683915981344[18] = 0;
   out_4403897683915981344[19] = 0;
   out_4403897683915981344[20] = 0;
   out_4403897683915981344[21] = 0;
   out_4403897683915981344[22] = 0;
   out_4403897683915981344[23] = 0;
   out_4403897683915981344[24] = 0;
   out_4403897683915981344[25] = 1;
   out_4403897683915981344[26] = 0;
   out_4403897683915981344[27] = 0;
   out_4403897683915981344[28] = 0;
   out_4403897683915981344[29] = 0;
   out_4403897683915981344[30] = 0;
   out_4403897683915981344[31] = 0;
   out_4403897683915981344[32] = 0;
   out_4403897683915981344[33] = 0;
   out_4403897683915981344[34] = 0;
   out_4403897683915981344[35] = 0;
   out_4403897683915981344[36] = 0;
   out_4403897683915981344[37] = 0;
   out_4403897683915981344[38] = 0;
   out_4403897683915981344[39] = 0;
   out_4403897683915981344[40] = 0;
   out_4403897683915981344[41] = 0;
   out_4403897683915981344[42] = 0;
   out_4403897683915981344[43] = 0;
   out_4403897683915981344[44] = 1;
   out_4403897683915981344[45] = 0;
   out_4403897683915981344[46] = 0;
   out_4403897683915981344[47] = 0;
   out_4403897683915981344[48] = 0;
   out_4403897683915981344[49] = 0;
   out_4403897683915981344[50] = 0;
   out_4403897683915981344[51] = 0;
   out_4403897683915981344[52] = 0;
   out_4403897683915981344[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_2423125642091007723) {
  err_fun(nom_x, delta_x, out_2423125642091007723);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1501585610038659930) {
  inv_err_fun(nom_x, true_x, out_1501585610038659930);
}
void pose_H_mod_fun(double *state, double *out_313504174478215792) {
  H_mod_fun(state, out_313504174478215792);
}
void pose_f_fun(double *state, double dt, double *out_8978916703249748052) {
  f_fun(state,  dt, out_8978916703249748052);
}
void pose_F_fun(double *state, double dt, double *out_3060487946531646253) {
  F_fun(state,  dt, out_3060487946531646253);
}
void pose_h_4(double *state, double *unused, double *out_2072690755108230087) {
  h_4(state, unused, out_2072690755108230087);
}
void pose_H_4(double *state, double *unused, double *out_440656827576496815) {
  H_4(state, unused, out_440656827576496815);
}
void pose_h_10(double *state, double *unused, double *out_3685903144892211871) {
  h_10(state, unused, out_3685903144892211871);
}
void pose_H_10(double *state, double *unused, double *out_7274933657249705055) {
  H_10(state, unused, out_7274933657249705055);
}
void pose_h_13(double *state, double *unused, double *out_7605941513603236476) {
  h_13(state, unused, out_7605941513603236476);
}
void pose_H_13(double *state, double *unused, double *out_3652930652908829616) {
  H_13(state, unused, out_3652930652908829616);
}
void pose_h_14(double *state, double *unused, double *out_732635666688386653) {
  h_14(state, unused, out_732635666688386653);
}
void pose_H_14(double *state, double *unused, double *out_4403897683915981344) {
  H_14(state, unused, out_4403897683915981344);
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
