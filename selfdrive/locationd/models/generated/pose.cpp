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
void err_fun(double *nom_x, double *delta_x, double *out_1277882425838003162) {
   out_1277882425838003162[0] = delta_x[0] + nom_x[0];
   out_1277882425838003162[1] = delta_x[1] + nom_x[1];
   out_1277882425838003162[2] = delta_x[2] + nom_x[2];
   out_1277882425838003162[3] = delta_x[3] + nom_x[3];
   out_1277882425838003162[4] = delta_x[4] + nom_x[4];
   out_1277882425838003162[5] = delta_x[5] + nom_x[5];
   out_1277882425838003162[6] = delta_x[6] + nom_x[6];
   out_1277882425838003162[7] = delta_x[7] + nom_x[7];
   out_1277882425838003162[8] = delta_x[8] + nom_x[8];
   out_1277882425838003162[9] = delta_x[9] + nom_x[9];
   out_1277882425838003162[10] = delta_x[10] + nom_x[10];
   out_1277882425838003162[11] = delta_x[11] + nom_x[11];
   out_1277882425838003162[12] = delta_x[12] + nom_x[12];
   out_1277882425838003162[13] = delta_x[13] + nom_x[13];
   out_1277882425838003162[14] = delta_x[14] + nom_x[14];
   out_1277882425838003162[15] = delta_x[15] + nom_x[15];
   out_1277882425838003162[16] = delta_x[16] + nom_x[16];
   out_1277882425838003162[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5395183656796766) {
   out_5395183656796766[0] = -nom_x[0] + true_x[0];
   out_5395183656796766[1] = -nom_x[1] + true_x[1];
   out_5395183656796766[2] = -nom_x[2] + true_x[2];
   out_5395183656796766[3] = -nom_x[3] + true_x[3];
   out_5395183656796766[4] = -nom_x[4] + true_x[4];
   out_5395183656796766[5] = -nom_x[5] + true_x[5];
   out_5395183656796766[6] = -nom_x[6] + true_x[6];
   out_5395183656796766[7] = -nom_x[7] + true_x[7];
   out_5395183656796766[8] = -nom_x[8] + true_x[8];
   out_5395183656796766[9] = -nom_x[9] + true_x[9];
   out_5395183656796766[10] = -nom_x[10] + true_x[10];
   out_5395183656796766[11] = -nom_x[11] + true_x[11];
   out_5395183656796766[12] = -nom_x[12] + true_x[12];
   out_5395183656796766[13] = -nom_x[13] + true_x[13];
   out_5395183656796766[14] = -nom_x[14] + true_x[14];
   out_5395183656796766[15] = -nom_x[15] + true_x[15];
   out_5395183656796766[16] = -nom_x[16] + true_x[16];
   out_5395183656796766[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4641299731180659481) {
   out_4641299731180659481[0] = 1.0;
   out_4641299731180659481[1] = 0.0;
   out_4641299731180659481[2] = 0.0;
   out_4641299731180659481[3] = 0.0;
   out_4641299731180659481[4] = 0.0;
   out_4641299731180659481[5] = 0.0;
   out_4641299731180659481[6] = 0.0;
   out_4641299731180659481[7] = 0.0;
   out_4641299731180659481[8] = 0.0;
   out_4641299731180659481[9] = 0.0;
   out_4641299731180659481[10] = 0.0;
   out_4641299731180659481[11] = 0.0;
   out_4641299731180659481[12] = 0.0;
   out_4641299731180659481[13] = 0.0;
   out_4641299731180659481[14] = 0.0;
   out_4641299731180659481[15] = 0.0;
   out_4641299731180659481[16] = 0.0;
   out_4641299731180659481[17] = 0.0;
   out_4641299731180659481[18] = 0.0;
   out_4641299731180659481[19] = 1.0;
   out_4641299731180659481[20] = 0.0;
   out_4641299731180659481[21] = 0.0;
   out_4641299731180659481[22] = 0.0;
   out_4641299731180659481[23] = 0.0;
   out_4641299731180659481[24] = 0.0;
   out_4641299731180659481[25] = 0.0;
   out_4641299731180659481[26] = 0.0;
   out_4641299731180659481[27] = 0.0;
   out_4641299731180659481[28] = 0.0;
   out_4641299731180659481[29] = 0.0;
   out_4641299731180659481[30] = 0.0;
   out_4641299731180659481[31] = 0.0;
   out_4641299731180659481[32] = 0.0;
   out_4641299731180659481[33] = 0.0;
   out_4641299731180659481[34] = 0.0;
   out_4641299731180659481[35] = 0.0;
   out_4641299731180659481[36] = 0.0;
   out_4641299731180659481[37] = 0.0;
   out_4641299731180659481[38] = 1.0;
   out_4641299731180659481[39] = 0.0;
   out_4641299731180659481[40] = 0.0;
   out_4641299731180659481[41] = 0.0;
   out_4641299731180659481[42] = 0.0;
   out_4641299731180659481[43] = 0.0;
   out_4641299731180659481[44] = 0.0;
   out_4641299731180659481[45] = 0.0;
   out_4641299731180659481[46] = 0.0;
   out_4641299731180659481[47] = 0.0;
   out_4641299731180659481[48] = 0.0;
   out_4641299731180659481[49] = 0.0;
   out_4641299731180659481[50] = 0.0;
   out_4641299731180659481[51] = 0.0;
   out_4641299731180659481[52] = 0.0;
   out_4641299731180659481[53] = 0.0;
   out_4641299731180659481[54] = 0.0;
   out_4641299731180659481[55] = 0.0;
   out_4641299731180659481[56] = 0.0;
   out_4641299731180659481[57] = 1.0;
   out_4641299731180659481[58] = 0.0;
   out_4641299731180659481[59] = 0.0;
   out_4641299731180659481[60] = 0.0;
   out_4641299731180659481[61] = 0.0;
   out_4641299731180659481[62] = 0.0;
   out_4641299731180659481[63] = 0.0;
   out_4641299731180659481[64] = 0.0;
   out_4641299731180659481[65] = 0.0;
   out_4641299731180659481[66] = 0.0;
   out_4641299731180659481[67] = 0.0;
   out_4641299731180659481[68] = 0.0;
   out_4641299731180659481[69] = 0.0;
   out_4641299731180659481[70] = 0.0;
   out_4641299731180659481[71] = 0.0;
   out_4641299731180659481[72] = 0.0;
   out_4641299731180659481[73] = 0.0;
   out_4641299731180659481[74] = 0.0;
   out_4641299731180659481[75] = 0.0;
   out_4641299731180659481[76] = 1.0;
   out_4641299731180659481[77] = 0.0;
   out_4641299731180659481[78] = 0.0;
   out_4641299731180659481[79] = 0.0;
   out_4641299731180659481[80] = 0.0;
   out_4641299731180659481[81] = 0.0;
   out_4641299731180659481[82] = 0.0;
   out_4641299731180659481[83] = 0.0;
   out_4641299731180659481[84] = 0.0;
   out_4641299731180659481[85] = 0.0;
   out_4641299731180659481[86] = 0.0;
   out_4641299731180659481[87] = 0.0;
   out_4641299731180659481[88] = 0.0;
   out_4641299731180659481[89] = 0.0;
   out_4641299731180659481[90] = 0.0;
   out_4641299731180659481[91] = 0.0;
   out_4641299731180659481[92] = 0.0;
   out_4641299731180659481[93] = 0.0;
   out_4641299731180659481[94] = 0.0;
   out_4641299731180659481[95] = 1.0;
   out_4641299731180659481[96] = 0.0;
   out_4641299731180659481[97] = 0.0;
   out_4641299731180659481[98] = 0.0;
   out_4641299731180659481[99] = 0.0;
   out_4641299731180659481[100] = 0.0;
   out_4641299731180659481[101] = 0.0;
   out_4641299731180659481[102] = 0.0;
   out_4641299731180659481[103] = 0.0;
   out_4641299731180659481[104] = 0.0;
   out_4641299731180659481[105] = 0.0;
   out_4641299731180659481[106] = 0.0;
   out_4641299731180659481[107] = 0.0;
   out_4641299731180659481[108] = 0.0;
   out_4641299731180659481[109] = 0.0;
   out_4641299731180659481[110] = 0.0;
   out_4641299731180659481[111] = 0.0;
   out_4641299731180659481[112] = 0.0;
   out_4641299731180659481[113] = 0.0;
   out_4641299731180659481[114] = 1.0;
   out_4641299731180659481[115] = 0.0;
   out_4641299731180659481[116] = 0.0;
   out_4641299731180659481[117] = 0.0;
   out_4641299731180659481[118] = 0.0;
   out_4641299731180659481[119] = 0.0;
   out_4641299731180659481[120] = 0.0;
   out_4641299731180659481[121] = 0.0;
   out_4641299731180659481[122] = 0.0;
   out_4641299731180659481[123] = 0.0;
   out_4641299731180659481[124] = 0.0;
   out_4641299731180659481[125] = 0.0;
   out_4641299731180659481[126] = 0.0;
   out_4641299731180659481[127] = 0.0;
   out_4641299731180659481[128] = 0.0;
   out_4641299731180659481[129] = 0.0;
   out_4641299731180659481[130] = 0.0;
   out_4641299731180659481[131] = 0.0;
   out_4641299731180659481[132] = 0.0;
   out_4641299731180659481[133] = 1.0;
   out_4641299731180659481[134] = 0.0;
   out_4641299731180659481[135] = 0.0;
   out_4641299731180659481[136] = 0.0;
   out_4641299731180659481[137] = 0.0;
   out_4641299731180659481[138] = 0.0;
   out_4641299731180659481[139] = 0.0;
   out_4641299731180659481[140] = 0.0;
   out_4641299731180659481[141] = 0.0;
   out_4641299731180659481[142] = 0.0;
   out_4641299731180659481[143] = 0.0;
   out_4641299731180659481[144] = 0.0;
   out_4641299731180659481[145] = 0.0;
   out_4641299731180659481[146] = 0.0;
   out_4641299731180659481[147] = 0.0;
   out_4641299731180659481[148] = 0.0;
   out_4641299731180659481[149] = 0.0;
   out_4641299731180659481[150] = 0.0;
   out_4641299731180659481[151] = 0.0;
   out_4641299731180659481[152] = 1.0;
   out_4641299731180659481[153] = 0.0;
   out_4641299731180659481[154] = 0.0;
   out_4641299731180659481[155] = 0.0;
   out_4641299731180659481[156] = 0.0;
   out_4641299731180659481[157] = 0.0;
   out_4641299731180659481[158] = 0.0;
   out_4641299731180659481[159] = 0.0;
   out_4641299731180659481[160] = 0.0;
   out_4641299731180659481[161] = 0.0;
   out_4641299731180659481[162] = 0.0;
   out_4641299731180659481[163] = 0.0;
   out_4641299731180659481[164] = 0.0;
   out_4641299731180659481[165] = 0.0;
   out_4641299731180659481[166] = 0.0;
   out_4641299731180659481[167] = 0.0;
   out_4641299731180659481[168] = 0.0;
   out_4641299731180659481[169] = 0.0;
   out_4641299731180659481[170] = 0.0;
   out_4641299731180659481[171] = 1.0;
   out_4641299731180659481[172] = 0.0;
   out_4641299731180659481[173] = 0.0;
   out_4641299731180659481[174] = 0.0;
   out_4641299731180659481[175] = 0.0;
   out_4641299731180659481[176] = 0.0;
   out_4641299731180659481[177] = 0.0;
   out_4641299731180659481[178] = 0.0;
   out_4641299731180659481[179] = 0.0;
   out_4641299731180659481[180] = 0.0;
   out_4641299731180659481[181] = 0.0;
   out_4641299731180659481[182] = 0.0;
   out_4641299731180659481[183] = 0.0;
   out_4641299731180659481[184] = 0.0;
   out_4641299731180659481[185] = 0.0;
   out_4641299731180659481[186] = 0.0;
   out_4641299731180659481[187] = 0.0;
   out_4641299731180659481[188] = 0.0;
   out_4641299731180659481[189] = 0.0;
   out_4641299731180659481[190] = 1.0;
   out_4641299731180659481[191] = 0.0;
   out_4641299731180659481[192] = 0.0;
   out_4641299731180659481[193] = 0.0;
   out_4641299731180659481[194] = 0.0;
   out_4641299731180659481[195] = 0.0;
   out_4641299731180659481[196] = 0.0;
   out_4641299731180659481[197] = 0.0;
   out_4641299731180659481[198] = 0.0;
   out_4641299731180659481[199] = 0.0;
   out_4641299731180659481[200] = 0.0;
   out_4641299731180659481[201] = 0.0;
   out_4641299731180659481[202] = 0.0;
   out_4641299731180659481[203] = 0.0;
   out_4641299731180659481[204] = 0.0;
   out_4641299731180659481[205] = 0.0;
   out_4641299731180659481[206] = 0.0;
   out_4641299731180659481[207] = 0.0;
   out_4641299731180659481[208] = 0.0;
   out_4641299731180659481[209] = 1.0;
   out_4641299731180659481[210] = 0.0;
   out_4641299731180659481[211] = 0.0;
   out_4641299731180659481[212] = 0.0;
   out_4641299731180659481[213] = 0.0;
   out_4641299731180659481[214] = 0.0;
   out_4641299731180659481[215] = 0.0;
   out_4641299731180659481[216] = 0.0;
   out_4641299731180659481[217] = 0.0;
   out_4641299731180659481[218] = 0.0;
   out_4641299731180659481[219] = 0.0;
   out_4641299731180659481[220] = 0.0;
   out_4641299731180659481[221] = 0.0;
   out_4641299731180659481[222] = 0.0;
   out_4641299731180659481[223] = 0.0;
   out_4641299731180659481[224] = 0.0;
   out_4641299731180659481[225] = 0.0;
   out_4641299731180659481[226] = 0.0;
   out_4641299731180659481[227] = 0.0;
   out_4641299731180659481[228] = 1.0;
   out_4641299731180659481[229] = 0.0;
   out_4641299731180659481[230] = 0.0;
   out_4641299731180659481[231] = 0.0;
   out_4641299731180659481[232] = 0.0;
   out_4641299731180659481[233] = 0.0;
   out_4641299731180659481[234] = 0.0;
   out_4641299731180659481[235] = 0.0;
   out_4641299731180659481[236] = 0.0;
   out_4641299731180659481[237] = 0.0;
   out_4641299731180659481[238] = 0.0;
   out_4641299731180659481[239] = 0.0;
   out_4641299731180659481[240] = 0.0;
   out_4641299731180659481[241] = 0.0;
   out_4641299731180659481[242] = 0.0;
   out_4641299731180659481[243] = 0.0;
   out_4641299731180659481[244] = 0.0;
   out_4641299731180659481[245] = 0.0;
   out_4641299731180659481[246] = 0.0;
   out_4641299731180659481[247] = 1.0;
   out_4641299731180659481[248] = 0.0;
   out_4641299731180659481[249] = 0.0;
   out_4641299731180659481[250] = 0.0;
   out_4641299731180659481[251] = 0.0;
   out_4641299731180659481[252] = 0.0;
   out_4641299731180659481[253] = 0.0;
   out_4641299731180659481[254] = 0.0;
   out_4641299731180659481[255] = 0.0;
   out_4641299731180659481[256] = 0.0;
   out_4641299731180659481[257] = 0.0;
   out_4641299731180659481[258] = 0.0;
   out_4641299731180659481[259] = 0.0;
   out_4641299731180659481[260] = 0.0;
   out_4641299731180659481[261] = 0.0;
   out_4641299731180659481[262] = 0.0;
   out_4641299731180659481[263] = 0.0;
   out_4641299731180659481[264] = 0.0;
   out_4641299731180659481[265] = 0.0;
   out_4641299731180659481[266] = 1.0;
   out_4641299731180659481[267] = 0.0;
   out_4641299731180659481[268] = 0.0;
   out_4641299731180659481[269] = 0.0;
   out_4641299731180659481[270] = 0.0;
   out_4641299731180659481[271] = 0.0;
   out_4641299731180659481[272] = 0.0;
   out_4641299731180659481[273] = 0.0;
   out_4641299731180659481[274] = 0.0;
   out_4641299731180659481[275] = 0.0;
   out_4641299731180659481[276] = 0.0;
   out_4641299731180659481[277] = 0.0;
   out_4641299731180659481[278] = 0.0;
   out_4641299731180659481[279] = 0.0;
   out_4641299731180659481[280] = 0.0;
   out_4641299731180659481[281] = 0.0;
   out_4641299731180659481[282] = 0.0;
   out_4641299731180659481[283] = 0.0;
   out_4641299731180659481[284] = 0.0;
   out_4641299731180659481[285] = 1.0;
   out_4641299731180659481[286] = 0.0;
   out_4641299731180659481[287] = 0.0;
   out_4641299731180659481[288] = 0.0;
   out_4641299731180659481[289] = 0.0;
   out_4641299731180659481[290] = 0.0;
   out_4641299731180659481[291] = 0.0;
   out_4641299731180659481[292] = 0.0;
   out_4641299731180659481[293] = 0.0;
   out_4641299731180659481[294] = 0.0;
   out_4641299731180659481[295] = 0.0;
   out_4641299731180659481[296] = 0.0;
   out_4641299731180659481[297] = 0.0;
   out_4641299731180659481[298] = 0.0;
   out_4641299731180659481[299] = 0.0;
   out_4641299731180659481[300] = 0.0;
   out_4641299731180659481[301] = 0.0;
   out_4641299731180659481[302] = 0.0;
   out_4641299731180659481[303] = 0.0;
   out_4641299731180659481[304] = 1.0;
   out_4641299731180659481[305] = 0.0;
   out_4641299731180659481[306] = 0.0;
   out_4641299731180659481[307] = 0.0;
   out_4641299731180659481[308] = 0.0;
   out_4641299731180659481[309] = 0.0;
   out_4641299731180659481[310] = 0.0;
   out_4641299731180659481[311] = 0.0;
   out_4641299731180659481[312] = 0.0;
   out_4641299731180659481[313] = 0.0;
   out_4641299731180659481[314] = 0.0;
   out_4641299731180659481[315] = 0.0;
   out_4641299731180659481[316] = 0.0;
   out_4641299731180659481[317] = 0.0;
   out_4641299731180659481[318] = 0.0;
   out_4641299731180659481[319] = 0.0;
   out_4641299731180659481[320] = 0.0;
   out_4641299731180659481[321] = 0.0;
   out_4641299731180659481[322] = 0.0;
   out_4641299731180659481[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4475655607956648045) {
   out_4475655607956648045[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4475655607956648045[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4475655607956648045[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4475655607956648045[3] = dt*state[12] + state[3];
   out_4475655607956648045[4] = dt*state[13] + state[4];
   out_4475655607956648045[5] = dt*state[14] + state[5];
   out_4475655607956648045[6] = state[6];
   out_4475655607956648045[7] = state[7];
   out_4475655607956648045[8] = state[8];
   out_4475655607956648045[9] = state[9];
   out_4475655607956648045[10] = state[10];
   out_4475655607956648045[11] = state[11];
   out_4475655607956648045[12] = state[12];
   out_4475655607956648045[13] = state[13];
   out_4475655607956648045[14] = state[14];
   out_4475655607956648045[15] = state[15];
   out_4475655607956648045[16] = state[16];
   out_4475655607956648045[17] = state[17];
}
void F_fun(double *state, double dt, double *out_1490364464464661376) {
   out_1490364464464661376[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1490364464464661376[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1490364464464661376[2] = 0;
   out_1490364464464661376[3] = 0;
   out_1490364464464661376[4] = 0;
   out_1490364464464661376[5] = 0;
   out_1490364464464661376[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1490364464464661376[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1490364464464661376[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1490364464464661376[9] = 0;
   out_1490364464464661376[10] = 0;
   out_1490364464464661376[11] = 0;
   out_1490364464464661376[12] = 0;
   out_1490364464464661376[13] = 0;
   out_1490364464464661376[14] = 0;
   out_1490364464464661376[15] = 0;
   out_1490364464464661376[16] = 0;
   out_1490364464464661376[17] = 0;
   out_1490364464464661376[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1490364464464661376[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1490364464464661376[20] = 0;
   out_1490364464464661376[21] = 0;
   out_1490364464464661376[22] = 0;
   out_1490364464464661376[23] = 0;
   out_1490364464464661376[24] = 0;
   out_1490364464464661376[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1490364464464661376[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1490364464464661376[27] = 0;
   out_1490364464464661376[28] = 0;
   out_1490364464464661376[29] = 0;
   out_1490364464464661376[30] = 0;
   out_1490364464464661376[31] = 0;
   out_1490364464464661376[32] = 0;
   out_1490364464464661376[33] = 0;
   out_1490364464464661376[34] = 0;
   out_1490364464464661376[35] = 0;
   out_1490364464464661376[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1490364464464661376[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1490364464464661376[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1490364464464661376[39] = 0;
   out_1490364464464661376[40] = 0;
   out_1490364464464661376[41] = 0;
   out_1490364464464661376[42] = 0;
   out_1490364464464661376[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1490364464464661376[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1490364464464661376[45] = 0;
   out_1490364464464661376[46] = 0;
   out_1490364464464661376[47] = 0;
   out_1490364464464661376[48] = 0;
   out_1490364464464661376[49] = 0;
   out_1490364464464661376[50] = 0;
   out_1490364464464661376[51] = 0;
   out_1490364464464661376[52] = 0;
   out_1490364464464661376[53] = 0;
   out_1490364464464661376[54] = 0;
   out_1490364464464661376[55] = 0;
   out_1490364464464661376[56] = 0;
   out_1490364464464661376[57] = 1;
   out_1490364464464661376[58] = 0;
   out_1490364464464661376[59] = 0;
   out_1490364464464661376[60] = 0;
   out_1490364464464661376[61] = 0;
   out_1490364464464661376[62] = 0;
   out_1490364464464661376[63] = 0;
   out_1490364464464661376[64] = 0;
   out_1490364464464661376[65] = 0;
   out_1490364464464661376[66] = dt;
   out_1490364464464661376[67] = 0;
   out_1490364464464661376[68] = 0;
   out_1490364464464661376[69] = 0;
   out_1490364464464661376[70] = 0;
   out_1490364464464661376[71] = 0;
   out_1490364464464661376[72] = 0;
   out_1490364464464661376[73] = 0;
   out_1490364464464661376[74] = 0;
   out_1490364464464661376[75] = 0;
   out_1490364464464661376[76] = 1;
   out_1490364464464661376[77] = 0;
   out_1490364464464661376[78] = 0;
   out_1490364464464661376[79] = 0;
   out_1490364464464661376[80] = 0;
   out_1490364464464661376[81] = 0;
   out_1490364464464661376[82] = 0;
   out_1490364464464661376[83] = 0;
   out_1490364464464661376[84] = 0;
   out_1490364464464661376[85] = dt;
   out_1490364464464661376[86] = 0;
   out_1490364464464661376[87] = 0;
   out_1490364464464661376[88] = 0;
   out_1490364464464661376[89] = 0;
   out_1490364464464661376[90] = 0;
   out_1490364464464661376[91] = 0;
   out_1490364464464661376[92] = 0;
   out_1490364464464661376[93] = 0;
   out_1490364464464661376[94] = 0;
   out_1490364464464661376[95] = 1;
   out_1490364464464661376[96] = 0;
   out_1490364464464661376[97] = 0;
   out_1490364464464661376[98] = 0;
   out_1490364464464661376[99] = 0;
   out_1490364464464661376[100] = 0;
   out_1490364464464661376[101] = 0;
   out_1490364464464661376[102] = 0;
   out_1490364464464661376[103] = 0;
   out_1490364464464661376[104] = dt;
   out_1490364464464661376[105] = 0;
   out_1490364464464661376[106] = 0;
   out_1490364464464661376[107] = 0;
   out_1490364464464661376[108] = 0;
   out_1490364464464661376[109] = 0;
   out_1490364464464661376[110] = 0;
   out_1490364464464661376[111] = 0;
   out_1490364464464661376[112] = 0;
   out_1490364464464661376[113] = 0;
   out_1490364464464661376[114] = 1;
   out_1490364464464661376[115] = 0;
   out_1490364464464661376[116] = 0;
   out_1490364464464661376[117] = 0;
   out_1490364464464661376[118] = 0;
   out_1490364464464661376[119] = 0;
   out_1490364464464661376[120] = 0;
   out_1490364464464661376[121] = 0;
   out_1490364464464661376[122] = 0;
   out_1490364464464661376[123] = 0;
   out_1490364464464661376[124] = 0;
   out_1490364464464661376[125] = 0;
   out_1490364464464661376[126] = 0;
   out_1490364464464661376[127] = 0;
   out_1490364464464661376[128] = 0;
   out_1490364464464661376[129] = 0;
   out_1490364464464661376[130] = 0;
   out_1490364464464661376[131] = 0;
   out_1490364464464661376[132] = 0;
   out_1490364464464661376[133] = 1;
   out_1490364464464661376[134] = 0;
   out_1490364464464661376[135] = 0;
   out_1490364464464661376[136] = 0;
   out_1490364464464661376[137] = 0;
   out_1490364464464661376[138] = 0;
   out_1490364464464661376[139] = 0;
   out_1490364464464661376[140] = 0;
   out_1490364464464661376[141] = 0;
   out_1490364464464661376[142] = 0;
   out_1490364464464661376[143] = 0;
   out_1490364464464661376[144] = 0;
   out_1490364464464661376[145] = 0;
   out_1490364464464661376[146] = 0;
   out_1490364464464661376[147] = 0;
   out_1490364464464661376[148] = 0;
   out_1490364464464661376[149] = 0;
   out_1490364464464661376[150] = 0;
   out_1490364464464661376[151] = 0;
   out_1490364464464661376[152] = 1;
   out_1490364464464661376[153] = 0;
   out_1490364464464661376[154] = 0;
   out_1490364464464661376[155] = 0;
   out_1490364464464661376[156] = 0;
   out_1490364464464661376[157] = 0;
   out_1490364464464661376[158] = 0;
   out_1490364464464661376[159] = 0;
   out_1490364464464661376[160] = 0;
   out_1490364464464661376[161] = 0;
   out_1490364464464661376[162] = 0;
   out_1490364464464661376[163] = 0;
   out_1490364464464661376[164] = 0;
   out_1490364464464661376[165] = 0;
   out_1490364464464661376[166] = 0;
   out_1490364464464661376[167] = 0;
   out_1490364464464661376[168] = 0;
   out_1490364464464661376[169] = 0;
   out_1490364464464661376[170] = 0;
   out_1490364464464661376[171] = 1;
   out_1490364464464661376[172] = 0;
   out_1490364464464661376[173] = 0;
   out_1490364464464661376[174] = 0;
   out_1490364464464661376[175] = 0;
   out_1490364464464661376[176] = 0;
   out_1490364464464661376[177] = 0;
   out_1490364464464661376[178] = 0;
   out_1490364464464661376[179] = 0;
   out_1490364464464661376[180] = 0;
   out_1490364464464661376[181] = 0;
   out_1490364464464661376[182] = 0;
   out_1490364464464661376[183] = 0;
   out_1490364464464661376[184] = 0;
   out_1490364464464661376[185] = 0;
   out_1490364464464661376[186] = 0;
   out_1490364464464661376[187] = 0;
   out_1490364464464661376[188] = 0;
   out_1490364464464661376[189] = 0;
   out_1490364464464661376[190] = 1;
   out_1490364464464661376[191] = 0;
   out_1490364464464661376[192] = 0;
   out_1490364464464661376[193] = 0;
   out_1490364464464661376[194] = 0;
   out_1490364464464661376[195] = 0;
   out_1490364464464661376[196] = 0;
   out_1490364464464661376[197] = 0;
   out_1490364464464661376[198] = 0;
   out_1490364464464661376[199] = 0;
   out_1490364464464661376[200] = 0;
   out_1490364464464661376[201] = 0;
   out_1490364464464661376[202] = 0;
   out_1490364464464661376[203] = 0;
   out_1490364464464661376[204] = 0;
   out_1490364464464661376[205] = 0;
   out_1490364464464661376[206] = 0;
   out_1490364464464661376[207] = 0;
   out_1490364464464661376[208] = 0;
   out_1490364464464661376[209] = 1;
   out_1490364464464661376[210] = 0;
   out_1490364464464661376[211] = 0;
   out_1490364464464661376[212] = 0;
   out_1490364464464661376[213] = 0;
   out_1490364464464661376[214] = 0;
   out_1490364464464661376[215] = 0;
   out_1490364464464661376[216] = 0;
   out_1490364464464661376[217] = 0;
   out_1490364464464661376[218] = 0;
   out_1490364464464661376[219] = 0;
   out_1490364464464661376[220] = 0;
   out_1490364464464661376[221] = 0;
   out_1490364464464661376[222] = 0;
   out_1490364464464661376[223] = 0;
   out_1490364464464661376[224] = 0;
   out_1490364464464661376[225] = 0;
   out_1490364464464661376[226] = 0;
   out_1490364464464661376[227] = 0;
   out_1490364464464661376[228] = 1;
   out_1490364464464661376[229] = 0;
   out_1490364464464661376[230] = 0;
   out_1490364464464661376[231] = 0;
   out_1490364464464661376[232] = 0;
   out_1490364464464661376[233] = 0;
   out_1490364464464661376[234] = 0;
   out_1490364464464661376[235] = 0;
   out_1490364464464661376[236] = 0;
   out_1490364464464661376[237] = 0;
   out_1490364464464661376[238] = 0;
   out_1490364464464661376[239] = 0;
   out_1490364464464661376[240] = 0;
   out_1490364464464661376[241] = 0;
   out_1490364464464661376[242] = 0;
   out_1490364464464661376[243] = 0;
   out_1490364464464661376[244] = 0;
   out_1490364464464661376[245] = 0;
   out_1490364464464661376[246] = 0;
   out_1490364464464661376[247] = 1;
   out_1490364464464661376[248] = 0;
   out_1490364464464661376[249] = 0;
   out_1490364464464661376[250] = 0;
   out_1490364464464661376[251] = 0;
   out_1490364464464661376[252] = 0;
   out_1490364464464661376[253] = 0;
   out_1490364464464661376[254] = 0;
   out_1490364464464661376[255] = 0;
   out_1490364464464661376[256] = 0;
   out_1490364464464661376[257] = 0;
   out_1490364464464661376[258] = 0;
   out_1490364464464661376[259] = 0;
   out_1490364464464661376[260] = 0;
   out_1490364464464661376[261] = 0;
   out_1490364464464661376[262] = 0;
   out_1490364464464661376[263] = 0;
   out_1490364464464661376[264] = 0;
   out_1490364464464661376[265] = 0;
   out_1490364464464661376[266] = 1;
   out_1490364464464661376[267] = 0;
   out_1490364464464661376[268] = 0;
   out_1490364464464661376[269] = 0;
   out_1490364464464661376[270] = 0;
   out_1490364464464661376[271] = 0;
   out_1490364464464661376[272] = 0;
   out_1490364464464661376[273] = 0;
   out_1490364464464661376[274] = 0;
   out_1490364464464661376[275] = 0;
   out_1490364464464661376[276] = 0;
   out_1490364464464661376[277] = 0;
   out_1490364464464661376[278] = 0;
   out_1490364464464661376[279] = 0;
   out_1490364464464661376[280] = 0;
   out_1490364464464661376[281] = 0;
   out_1490364464464661376[282] = 0;
   out_1490364464464661376[283] = 0;
   out_1490364464464661376[284] = 0;
   out_1490364464464661376[285] = 1;
   out_1490364464464661376[286] = 0;
   out_1490364464464661376[287] = 0;
   out_1490364464464661376[288] = 0;
   out_1490364464464661376[289] = 0;
   out_1490364464464661376[290] = 0;
   out_1490364464464661376[291] = 0;
   out_1490364464464661376[292] = 0;
   out_1490364464464661376[293] = 0;
   out_1490364464464661376[294] = 0;
   out_1490364464464661376[295] = 0;
   out_1490364464464661376[296] = 0;
   out_1490364464464661376[297] = 0;
   out_1490364464464661376[298] = 0;
   out_1490364464464661376[299] = 0;
   out_1490364464464661376[300] = 0;
   out_1490364464464661376[301] = 0;
   out_1490364464464661376[302] = 0;
   out_1490364464464661376[303] = 0;
   out_1490364464464661376[304] = 1;
   out_1490364464464661376[305] = 0;
   out_1490364464464661376[306] = 0;
   out_1490364464464661376[307] = 0;
   out_1490364464464661376[308] = 0;
   out_1490364464464661376[309] = 0;
   out_1490364464464661376[310] = 0;
   out_1490364464464661376[311] = 0;
   out_1490364464464661376[312] = 0;
   out_1490364464464661376[313] = 0;
   out_1490364464464661376[314] = 0;
   out_1490364464464661376[315] = 0;
   out_1490364464464661376[316] = 0;
   out_1490364464464661376[317] = 0;
   out_1490364464464661376[318] = 0;
   out_1490364464464661376[319] = 0;
   out_1490364464464661376[320] = 0;
   out_1490364464464661376[321] = 0;
   out_1490364464464661376[322] = 0;
   out_1490364464464661376[323] = 1;
}
void h_4(double *state, double *unused, double *out_4985239385195179173) {
   out_4985239385195179173[0] = state[6] + state[9];
   out_4985239385195179173[1] = state[7] + state[10];
   out_4985239385195179173[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2821601005274362620) {
   out_2821601005274362620[0] = 0;
   out_2821601005274362620[1] = 0;
   out_2821601005274362620[2] = 0;
   out_2821601005274362620[3] = 0;
   out_2821601005274362620[4] = 0;
   out_2821601005274362620[5] = 0;
   out_2821601005274362620[6] = 1;
   out_2821601005274362620[7] = 0;
   out_2821601005274362620[8] = 0;
   out_2821601005274362620[9] = 1;
   out_2821601005274362620[10] = 0;
   out_2821601005274362620[11] = 0;
   out_2821601005274362620[12] = 0;
   out_2821601005274362620[13] = 0;
   out_2821601005274362620[14] = 0;
   out_2821601005274362620[15] = 0;
   out_2821601005274362620[16] = 0;
   out_2821601005274362620[17] = 0;
   out_2821601005274362620[18] = 0;
   out_2821601005274362620[19] = 0;
   out_2821601005274362620[20] = 0;
   out_2821601005274362620[21] = 0;
   out_2821601005274362620[22] = 0;
   out_2821601005274362620[23] = 0;
   out_2821601005274362620[24] = 0;
   out_2821601005274362620[25] = 1;
   out_2821601005274362620[26] = 0;
   out_2821601005274362620[27] = 0;
   out_2821601005274362620[28] = 1;
   out_2821601005274362620[29] = 0;
   out_2821601005274362620[30] = 0;
   out_2821601005274362620[31] = 0;
   out_2821601005274362620[32] = 0;
   out_2821601005274362620[33] = 0;
   out_2821601005274362620[34] = 0;
   out_2821601005274362620[35] = 0;
   out_2821601005274362620[36] = 0;
   out_2821601005274362620[37] = 0;
   out_2821601005274362620[38] = 0;
   out_2821601005274362620[39] = 0;
   out_2821601005274362620[40] = 0;
   out_2821601005274362620[41] = 0;
   out_2821601005274362620[42] = 0;
   out_2821601005274362620[43] = 0;
   out_2821601005274362620[44] = 1;
   out_2821601005274362620[45] = 0;
   out_2821601005274362620[46] = 0;
   out_2821601005274362620[47] = 1;
   out_2821601005274362620[48] = 0;
   out_2821601005274362620[49] = 0;
   out_2821601005274362620[50] = 0;
   out_2821601005274362620[51] = 0;
   out_2821601005274362620[52] = 0;
   out_2821601005274362620[53] = 0;
}
void h_10(double *state, double *unused, double *out_5766917160067306951) {
   out_5766917160067306951[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5766917160067306951[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5766917160067306951[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_393429258268914973) {
   out_393429258268914973[0] = 0;
   out_393429258268914973[1] = 9.8100000000000005*cos(state[1]);
   out_393429258268914973[2] = 0;
   out_393429258268914973[3] = 0;
   out_393429258268914973[4] = -state[8];
   out_393429258268914973[5] = state[7];
   out_393429258268914973[6] = 0;
   out_393429258268914973[7] = state[5];
   out_393429258268914973[8] = -state[4];
   out_393429258268914973[9] = 0;
   out_393429258268914973[10] = 0;
   out_393429258268914973[11] = 0;
   out_393429258268914973[12] = 1;
   out_393429258268914973[13] = 0;
   out_393429258268914973[14] = 0;
   out_393429258268914973[15] = 1;
   out_393429258268914973[16] = 0;
   out_393429258268914973[17] = 0;
   out_393429258268914973[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_393429258268914973[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_393429258268914973[20] = 0;
   out_393429258268914973[21] = state[8];
   out_393429258268914973[22] = 0;
   out_393429258268914973[23] = -state[6];
   out_393429258268914973[24] = -state[5];
   out_393429258268914973[25] = 0;
   out_393429258268914973[26] = state[3];
   out_393429258268914973[27] = 0;
   out_393429258268914973[28] = 0;
   out_393429258268914973[29] = 0;
   out_393429258268914973[30] = 0;
   out_393429258268914973[31] = 1;
   out_393429258268914973[32] = 0;
   out_393429258268914973[33] = 0;
   out_393429258268914973[34] = 1;
   out_393429258268914973[35] = 0;
   out_393429258268914973[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_393429258268914973[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_393429258268914973[38] = 0;
   out_393429258268914973[39] = -state[7];
   out_393429258268914973[40] = state[6];
   out_393429258268914973[41] = 0;
   out_393429258268914973[42] = state[4];
   out_393429258268914973[43] = -state[3];
   out_393429258268914973[44] = 0;
   out_393429258268914973[45] = 0;
   out_393429258268914973[46] = 0;
   out_393429258268914973[47] = 0;
   out_393429258268914973[48] = 0;
   out_393429258268914973[49] = 0;
   out_393429258268914973[50] = 1;
   out_393429258268914973[51] = 0;
   out_393429258268914973[52] = 0;
   out_393429258268914973[53] = 1;
}
void h_13(double *state, double *unused, double *out_7359463090555700335) {
   out_7359463090555700335[0] = state[3];
   out_7359463090555700335[1] = state[4];
   out_7359463090555700335[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6033874830606695421) {
   out_6033874830606695421[0] = 0;
   out_6033874830606695421[1] = 0;
   out_6033874830606695421[2] = 0;
   out_6033874830606695421[3] = 1;
   out_6033874830606695421[4] = 0;
   out_6033874830606695421[5] = 0;
   out_6033874830606695421[6] = 0;
   out_6033874830606695421[7] = 0;
   out_6033874830606695421[8] = 0;
   out_6033874830606695421[9] = 0;
   out_6033874830606695421[10] = 0;
   out_6033874830606695421[11] = 0;
   out_6033874830606695421[12] = 0;
   out_6033874830606695421[13] = 0;
   out_6033874830606695421[14] = 0;
   out_6033874830606695421[15] = 0;
   out_6033874830606695421[16] = 0;
   out_6033874830606695421[17] = 0;
   out_6033874830606695421[18] = 0;
   out_6033874830606695421[19] = 0;
   out_6033874830606695421[20] = 0;
   out_6033874830606695421[21] = 0;
   out_6033874830606695421[22] = 1;
   out_6033874830606695421[23] = 0;
   out_6033874830606695421[24] = 0;
   out_6033874830606695421[25] = 0;
   out_6033874830606695421[26] = 0;
   out_6033874830606695421[27] = 0;
   out_6033874830606695421[28] = 0;
   out_6033874830606695421[29] = 0;
   out_6033874830606695421[30] = 0;
   out_6033874830606695421[31] = 0;
   out_6033874830606695421[32] = 0;
   out_6033874830606695421[33] = 0;
   out_6033874830606695421[34] = 0;
   out_6033874830606695421[35] = 0;
   out_6033874830606695421[36] = 0;
   out_6033874830606695421[37] = 0;
   out_6033874830606695421[38] = 0;
   out_6033874830606695421[39] = 0;
   out_6033874830606695421[40] = 0;
   out_6033874830606695421[41] = 1;
   out_6033874830606695421[42] = 0;
   out_6033874830606695421[43] = 0;
   out_6033874830606695421[44] = 0;
   out_6033874830606695421[45] = 0;
   out_6033874830606695421[46] = 0;
   out_6033874830606695421[47] = 0;
   out_6033874830606695421[48] = 0;
   out_6033874830606695421[49] = 0;
   out_6033874830606695421[50] = 0;
   out_6033874830606695421[51] = 0;
   out_6033874830606695421[52] = 0;
   out_6033874830606695421[53] = 0;
}
void h_14(double *state, double *unused, double *out_1914760434129654014) {
   out_1914760434129654014[0] = state[6];
   out_1914760434129654014[1] = state[7];
   out_1914760434129654014[2] = state[8];
}
void H_14(double *state, double *unused, double *out_261187427021009676) {
   out_261187427021009676[0] = 0;
   out_261187427021009676[1] = 0;
   out_261187427021009676[2] = 0;
   out_261187427021009676[3] = 0;
   out_261187427021009676[4] = 0;
   out_261187427021009676[5] = 0;
   out_261187427021009676[6] = 1;
   out_261187427021009676[7] = 0;
   out_261187427021009676[8] = 0;
   out_261187427021009676[9] = 0;
   out_261187427021009676[10] = 0;
   out_261187427021009676[11] = 0;
   out_261187427021009676[12] = 0;
   out_261187427021009676[13] = 0;
   out_261187427021009676[14] = 0;
   out_261187427021009676[15] = 0;
   out_261187427021009676[16] = 0;
   out_261187427021009676[17] = 0;
   out_261187427021009676[18] = 0;
   out_261187427021009676[19] = 0;
   out_261187427021009676[20] = 0;
   out_261187427021009676[21] = 0;
   out_261187427021009676[22] = 0;
   out_261187427021009676[23] = 0;
   out_261187427021009676[24] = 0;
   out_261187427021009676[25] = 1;
   out_261187427021009676[26] = 0;
   out_261187427021009676[27] = 0;
   out_261187427021009676[28] = 0;
   out_261187427021009676[29] = 0;
   out_261187427021009676[30] = 0;
   out_261187427021009676[31] = 0;
   out_261187427021009676[32] = 0;
   out_261187427021009676[33] = 0;
   out_261187427021009676[34] = 0;
   out_261187427021009676[35] = 0;
   out_261187427021009676[36] = 0;
   out_261187427021009676[37] = 0;
   out_261187427021009676[38] = 0;
   out_261187427021009676[39] = 0;
   out_261187427021009676[40] = 0;
   out_261187427021009676[41] = 0;
   out_261187427021009676[42] = 0;
   out_261187427021009676[43] = 0;
   out_261187427021009676[44] = 1;
   out_261187427021009676[45] = 0;
   out_261187427021009676[46] = 0;
   out_261187427021009676[47] = 0;
   out_261187427021009676[48] = 0;
   out_261187427021009676[49] = 0;
   out_261187427021009676[50] = 0;
   out_261187427021009676[51] = 0;
   out_261187427021009676[52] = 0;
   out_261187427021009676[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_1277882425838003162) {
  err_fun(nom_x, delta_x, out_1277882425838003162);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5395183656796766) {
  inv_err_fun(nom_x, true_x, out_5395183656796766);
}
void pose_H_mod_fun(double *state, double *out_4641299731180659481) {
  H_mod_fun(state, out_4641299731180659481);
}
void pose_f_fun(double *state, double dt, double *out_4475655607956648045) {
  f_fun(state,  dt, out_4475655607956648045);
}
void pose_F_fun(double *state, double dt, double *out_1490364464464661376) {
  F_fun(state,  dt, out_1490364464464661376);
}
void pose_h_4(double *state, double *unused, double *out_4985239385195179173) {
  h_4(state, unused, out_4985239385195179173);
}
void pose_H_4(double *state, double *unused, double *out_2821601005274362620) {
  H_4(state, unused, out_2821601005274362620);
}
void pose_h_10(double *state, double *unused, double *out_5766917160067306951) {
  h_10(state, unused, out_5766917160067306951);
}
void pose_H_10(double *state, double *unused, double *out_393429258268914973) {
  H_10(state, unused, out_393429258268914973);
}
void pose_h_13(double *state, double *unused, double *out_7359463090555700335) {
  h_13(state, unused, out_7359463090555700335);
}
void pose_H_13(double *state, double *unused, double *out_6033874830606695421) {
  H_13(state, unused, out_6033874830606695421);
}
void pose_h_14(double *state, double *unused, double *out_1914760434129654014) {
  h_14(state, unused, out_1914760434129654014);
}
void pose_H_14(double *state, double *unused, double *out_261187427021009676) {
  H_14(state, unused, out_261187427021009676);
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
