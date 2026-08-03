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
void err_fun(double *nom_x, double *delta_x, double *out_5763415234273933913) {
   out_5763415234273933913[0] = delta_x[0] + nom_x[0];
   out_5763415234273933913[1] = delta_x[1] + nom_x[1];
   out_5763415234273933913[2] = delta_x[2] + nom_x[2];
   out_5763415234273933913[3] = delta_x[3] + nom_x[3];
   out_5763415234273933913[4] = delta_x[4] + nom_x[4];
   out_5763415234273933913[5] = delta_x[5] + nom_x[5];
   out_5763415234273933913[6] = delta_x[6] + nom_x[6];
   out_5763415234273933913[7] = delta_x[7] + nom_x[7];
   out_5763415234273933913[8] = delta_x[8] + nom_x[8];
   out_5763415234273933913[9] = delta_x[9] + nom_x[9];
   out_5763415234273933913[10] = delta_x[10] + nom_x[10];
   out_5763415234273933913[11] = delta_x[11] + nom_x[11];
   out_5763415234273933913[12] = delta_x[12] + nom_x[12];
   out_5763415234273933913[13] = delta_x[13] + nom_x[13];
   out_5763415234273933913[14] = delta_x[14] + nom_x[14];
   out_5763415234273933913[15] = delta_x[15] + nom_x[15];
   out_5763415234273933913[16] = delta_x[16] + nom_x[16];
   out_5763415234273933913[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1417325942549329712) {
   out_1417325942549329712[0] = -nom_x[0] + true_x[0];
   out_1417325942549329712[1] = -nom_x[1] + true_x[1];
   out_1417325942549329712[2] = -nom_x[2] + true_x[2];
   out_1417325942549329712[3] = -nom_x[3] + true_x[3];
   out_1417325942549329712[4] = -nom_x[4] + true_x[4];
   out_1417325942549329712[5] = -nom_x[5] + true_x[5];
   out_1417325942549329712[6] = -nom_x[6] + true_x[6];
   out_1417325942549329712[7] = -nom_x[7] + true_x[7];
   out_1417325942549329712[8] = -nom_x[8] + true_x[8];
   out_1417325942549329712[9] = -nom_x[9] + true_x[9];
   out_1417325942549329712[10] = -nom_x[10] + true_x[10];
   out_1417325942549329712[11] = -nom_x[11] + true_x[11];
   out_1417325942549329712[12] = -nom_x[12] + true_x[12];
   out_1417325942549329712[13] = -nom_x[13] + true_x[13];
   out_1417325942549329712[14] = -nom_x[14] + true_x[14];
   out_1417325942549329712[15] = -nom_x[15] + true_x[15];
   out_1417325942549329712[16] = -nom_x[16] + true_x[16];
   out_1417325942549329712[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7849761791714406524) {
   out_7849761791714406524[0] = 1.0;
   out_7849761791714406524[1] = 0.0;
   out_7849761791714406524[2] = 0.0;
   out_7849761791714406524[3] = 0.0;
   out_7849761791714406524[4] = 0.0;
   out_7849761791714406524[5] = 0.0;
   out_7849761791714406524[6] = 0.0;
   out_7849761791714406524[7] = 0.0;
   out_7849761791714406524[8] = 0.0;
   out_7849761791714406524[9] = 0.0;
   out_7849761791714406524[10] = 0.0;
   out_7849761791714406524[11] = 0.0;
   out_7849761791714406524[12] = 0.0;
   out_7849761791714406524[13] = 0.0;
   out_7849761791714406524[14] = 0.0;
   out_7849761791714406524[15] = 0.0;
   out_7849761791714406524[16] = 0.0;
   out_7849761791714406524[17] = 0.0;
   out_7849761791714406524[18] = 0.0;
   out_7849761791714406524[19] = 1.0;
   out_7849761791714406524[20] = 0.0;
   out_7849761791714406524[21] = 0.0;
   out_7849761791714406524[22] = 0.0;
   out_7849761791714406524[23] = 0.0;
   out_7849761791714406524[24] = 0.0;
   out_7849761791714406524[25] = 0.0;
   out_7849761791714406524[26] = 0.0;
   out_7849761791714406524[27] = 0.0;
   out_7849761791714406524[28] = 0.0;
   out_7849761791714406524[29] = 0.0;
   out_7849761791714406524[30] = 0.0;
   out_7849761791714406524[31] = 0.0;
   out_7849761791714406524[32] = 0.0;
   out_7849761791714406524[33] = 0.0;
   out_7849761791714406524[34] = 0.0;
   out_7849761791714406524[35] = 0.0;
   out_7849761791714406524[36] = 0.0;
   out_7849761791714406524[37] = 0.0;
   out_7849761791714406524[38] = 1.0;
   out_7849761791714406524[39] = 0.0;
   out_7849761791714406524[40] = 0.0;
   out_7849761791714406524[41] = 0.0;
   out_7849761791714406524[42] = 0.0;
   out_7849761791714406524[43] = 0.0;
   out_7849761791714406524[44] = 0.0;
   out_7849761791714406524[45] = 0.0;
   out_7849761791714406524[46] = 0.0;
   out_7849761791714406524[47] = 0.0;
   out_7849761791714406524[48] = 0.0;
   out_7849761791714406524[49] = 0.0;
   out_7849761791714406524[50] = 0.0;
   out_7849761791714406524[51] = 0.0;
   out_7849761791714406524[52] = 0.0;
   out_7849761791714406524[53] = 0.0;
   out_7849761791714406524[54] = 0.0;
   out_7849761791714406524[55] = 0.0;
   out_7849761791714406524[56] = 0.0;
   out_7849761791714406524[57] = 1.0;
   out_7849761791714406524[58] = 0.0;
   out_7849761791714406524[59] = 0.0;
   out_7849761791714406524[60] = 0.0;
   out_7849761791714406524[61] = 0.0;
   out_7849761791714406524[62] = 0.0;
   out_7849761791714406524[63] = 0.0;
   out_7849761791714406524[64] = 0.0;
   out_7849761791714406524[65] = 0.0;
   out_7849761791714406524[66] = 0.0;
   out_7849761791714406524[67] = 0.0;
   out_7849761791714406524[68] = 0.0;
   out_7849761791714406524[69] = 0.0;
   out_7849761791714406524[70] = 0.0;
   out_7849761791714406524[71] = 0.0;
   out_7849761791714406524[72] = 0.0;
   out_7849761791714406524[73] = 0.0;
   out_7849761791714406524[74] = 0.0;
   out_7849761791714406524[75] = 0.0;
   out_7849761791714406524[76] = 1.0;
   out_7849761791714406524[77] = 0.0;
   out_7849761791714406524[78] = 0.0;
   out_7849761791714406524[79] = 0.0;
   out_7849761791714406524[80] = 0.0;
   out_7849761791714406524[81] = 0.0;
   out_7849761791714406524[82] = 0.0;
   out_7849761791714406524[83] = 0.0;
   out_7849761791714406524[84] = 0.0;
   out_7849761791714406524[85] = 0.0;
   out_7849761791714406524[86] = 0.0;
   out_7849761791714406524[87] = 0.0;
   out_7849761791714406524[88] = 0.0;
   out_7849761791714406524[89] = 0.0;
   out_7849761791714406524[90] = 0.0;
   out_7849761791714406524[91] = 0.0;
   out_7849761791714406524[92] = 0.0;
   out_7849761791714406524[93] = 0.0;
   out_7849761791714406524[94] = 0.0;
   out_7849761791714406524[95] = 1.0;
   out_7849761791714406524[96] = 0.0;
   out_7849761791714406524[97] = 0.0;
   out_7849761791714406524[98] = 0.0;
   out_7849761791714406524[99] = 0.0;
   out_7849761791714406524[100] = 0.0;
   out_7849761791714406524[101] = 0.0;
   out_7849761791714406524[102] = 0.0;
   out_7849761791714406524[103] = 0.0;
   out_7849761791714406524[104] = 0.0;
   out_7849761791714406524[105] = 0.0;
   out_7849761791714406524[106] = 0.0;
   out_7849761791714406524[107] = 0.0;
   out_7849761791714406524[108] = 0.0;
   out_7849761791714406524[109] = 0.0;
   out_7849761791714406524[110] = 0.0;
   out_7849761791714406524[111] = 0.0;
   out_7849761791714406524[112] = 0.0;
   out_7849761791714406524[113] = 0.0;
   out_7849761791714406524[114] = 1.0;
   out_7849761791714406524[115] = 0.0;
   out_7849761791714406524[116] = 0.0;
   out_7849761791714406524[117] = 0.0;
   out_7849761791714406524[118] = 0.0;
   out_7849761791714406524[119] = 0.0;
   out_7849761791714406524[120] = 0.0;
   out_7849761791714406524[121] = 0.0;
   out_7849761791714406524[122] = 0.0;
   out_7849761791714406524[123] = 0.0;
   out_7849761791714406524[124] = 0.0;
   out_7849761791714406524[125] = 0.0;
   out_7849761791714406524[126] = 0.0;
   out_7849761791714406524[127] = 0.0;
   out_7849761791714406524[128] = 0.0;
   out_7849761791714406524[129] = 0.0;
   out_7849761791714406524[130] = 0.0;
   out_7849761791714406524[131] = 0.0;
   out_7849761791714406524[132] = 0.0;
   out_7849761791714406524[133] = 1.0;
   out_7849761791714406524[134] = 0.0;
   out_7849761791714406524[135] = 0.0;
   out_7849761791714406524[136] = 0.0;
   out_7849761791714406524[137] = 0.0;
   out_7849761791714406524[138] = 0.0;
   out_7849761791714406524[139] = 0.0;
   out_7849761791714406524[140] = 0.0;
   out_7849761791714406524[141] = 0.0;
   out_7849761791714406524[142] = 0.0;
   out_7849761791714406524[143] = 0.0;
   out_7849761791714406524[144] = 0.0;
   out_7849761791714406524[145] = 0.0;
   out_7849761791714406524[146] = 0.0;
   out_7849761791714406524[147] = 0.0;
   out_7849761791714406524[148] = 0.0;
   out_7849761791714406524[149] = 0.0;
   out_7849761791714406524[150] = 0.0;
   out_7849761791714406524[151] = 0.0;
   out_7849761791714406524[152] = 1.0;
   out_7849761791714406524[153] = 0.0;
   out_7849761791714406524[154] = 0.0;
   out_7849761791714406524[155] = 0.0;
   out_7849761791714406524[156] = 0.0;
   out_7849761791714406524[157] = 0.0;
   out_7849761791714406524[158] = 0.0;
   out_7849761791714406524[159] = 0.0;
   out_7849761791714406524[160] = 0.0;
   out_7849761791714406524[161] = 0.0;
   out_7849761791714406524[162] = 0.0;
   out_7849761791714406524[163] = 0.0;
   out_7849761791714406524[164] = 0.0;
   out_7849761791714406524[165] = 0.0;
   out_7849761791714406524[166] = 0.0;
   out_7849761791714406524[167] = 0.0;
   out_7849761791714406524[168] = 0.0;
   out_7849761791714406524[169] = 0.0;
   out_7849761791714406524[170] = 0.0;
   out_7849761791714406524[171] = 1.0;
   out_7849761791714406524[172] = 0.0;
   out_7849761791714406524[173] = 0.0;
   out_7849761791714406524[174] = 0.0;
   out_7849761791714406524[175] = 0.0;
   out_7849761791714406524[176] = 0.0;
   out_7849761791714406524[177] = 0.0;
   out_7849761791714406524[178] = 0.0;
   out_7849761791714406524[179] = 0.0;
   out_7849761791714406524[180] = 0.0;
   out_7849761791714406524[181] = 0.0;
   out_7849761791714406524[182] = 0.0;
   out_7849761791714406524[183] = 0.0;
   out_7849761791714406524[184] = 0.0;
   out_7849761791714406524[185] = 0.0;
   out_7849761791714406524[186] = 0.0;
   out_7849761791714406524[187] = 0.0;
   out_7849761791714406524[188] = 0.0;
   out_7849761791714406524[189] = 0.0;
   out_7849761791714406524[190] = 1.0;
   out_7849761791714406524[191] = 0.0;
   out_7849761791714406524[192] = 0.0;
   out_7849761791714406524[193] = 0.0;
   out_7849761791714406524[194] = 0.0;
   out_7849761791714406524[195] = 0.0;
   out_7849761791714406524[196] = 0.0;
   out_7849761791714406524[197] = 0.0;
   out_7849761791714406524[198] = 0.0;
   out_7849761791714406524[199] = 0.0;
   out_7849761791714406524[200] = 0.0;
   out_7849761791714406524[201] = 0.0;
   out_7849761791714406524[202] = 0.0;
   out_7849761791714406524[203] = 0.0;
   out_7849761791714406524[204] = 0.0;
   out_7849761791714406524[205] = 0.0;
   out_7849761791714406524[206] = 0.0;
   out_7849761791714406524[207] = 0.0;
   out_7849761791714406524[208] = 0.0;
   out_7849761791714406524[209] = 1.0;
   out_7849761791714406524[210] = 0.0;
   out_7849761791714406524[211] = 0.0;
   out_7849761791714406524[212] = 0.0;
   out_7849761791714406524[213] = 0.0;
   out_7849761791714406524[214] = 0.0;
   out_7849761791714406524[215] = 0.0;
   out_7849761791714406524[216] = 0.0;
   out_7849761791714406524[217] = 0.0;
   out_7849761791714406524[218] = 0.0;
   out_7849761791714406524[219] = 0.0;
   out_7849761791714406524[220] = 0.0;
   out_7849761791714406524[221] = 0.0;
   out_7849761791714406524[222] = 0.0;
   out_7849761791714406524[223] = 0.0;
   out_7849761791714406524[224] = 0.0;
   out_7849761791714406524[225] = 0.0;
   out_7849761791714406524[226] = 0.0;
   out_7849761791714406524[227] = 0.0;
   out_7849761791714406524[228] = 1.0;
   out_7849761791714406524[229] = 0.0;
   out_7849761791714406524[230] = 0.0;
   out_7849761791714406524[231] = 0.0;
   out_7849761791714406524[232] = 0.0;
   out_7849761791714406524[233] = 0.0;
   out_7849761791714406524[234] = 0.0;
   out_7849761791714406524[235] = 0.0;
   out_7849761791714406524[236] = 0.0;
   out_7849761791714406524[237] = 0.0;
   out_7849761791714406524[238] = 0.0;
   out_7849761791714406524[239] = 0.0;
   out_7849761791714406524[240] = 0.0;
   out_7849761791714406524[241] = 0.0;
   out_7849761791714406524[242] = 0.0;
   out_7849761791714406524[243] = 0.0;
   out_7849761791714406524[244] = 0.0;
   out_7849761791714406524[245] = 0.0;
   out_7849761791714406524[246] = 0.0;
   out_7849761791714406524[247] = 1.0;
   out_7849761791714406524[248] = 0.0;
   out_7849761791714406524[249] = 0.0;
   out_7849761791714406524[250] = 0.0;
   out_7849761791714406524[251] = 0.0;
   out_7849761791714406524[252] = 0.0;
   out_7849761791714406524[253] = 0.0;
   out_7849761791714406524[254] = 0.0;
   out_7849761791714406524[255] = 0.0;
   out_7849761791714406524[256] = 0.0;
   out_7849761791714406524[257] = 0.0;
   out_7849761791714406524[258] = 0.0;
   out_7849761791714406524[259] = 0.0;
   out_7849761791714406524[260] = 0.0;
   out_7849761791714406524[261] = 0.0;
   out_7849761791714406524[262] = 0.0;
   out_7849761791714406524[263] = 0.0;
   out_7849761791714406524[264] = 0.0;
   out_7849761791714406524[265] = 0.0;
   out_7849761791714406524[266] = 1.0;
   out_7849761791714406524[267] = 0.0;
   out_7849761791714406524[268] = 0.0;
   out_7849761791714406524[269] = 0.0;
   out_7849761791714406524[270] = 0.0;
   out_7849761791714406524[271] = 0.0;
   out_7849761791714406524[272] = 0.0;
   out_7849761791714406524[273] = 0.0;
   out_7849761791714406524[274] = 0.0;
   out_7849761791714406524[275] = 0.0;
   out_7849761791714406524[276] = 0.0;
   out_7849761791714406524[277] = 0.0;
   out_7849761791714406524[278] = 0.0;
   out_7849761791714406524[279] = 0.0;
   out_7849761791714406524[280] = 0.0;
   out_7849761791714406524[281] = 0.0;
   out_7849761791714406524[282] = 0.0;
   out_7849761791714406524[283] = 0.0;
   out_7849761791714406524[284] = 0.0;
   out_7849761791714406524[285] = 1.0;
   out_7849761791714406524[286] = 0.0;
   out_7849761791714406524[287] = 0.0;
   out_7849761791714406524[288] = 0.0;
   out_7849761791714406524[289] = 0.0;
   out_7849761791714406524[290] = 0.0;
   out_7849761791714406524[291] = 0.0;
   out_7849761791714406524[292] = 0.0;
   out_7849761791714406524[293] = 0.0;
   out_7849761791714406524[294] = 0.0;
   out_7849761791714406524[295] = 0.0;
   out_7849761791714406524[296] = 0.0;
   out_7849761791714406524[297] = 0.0;
   out_7849761791714406524[298] = 0.0;
   out_7849761791714406524[299] = 0.0;
   out_7849761791714406524[300] = 0.0;
   out_7849761791714406524[301] = 0.0;
   out_7849761791714406524[302] = 0.0;
   out_7849761791714406524[303] = 0.0;
   out_7849761791714406524[304] = 1.0;
   out_7849761791714406524[305] = 0.0;
   out_7849761791714406524[306] = 0.0;
   out_7849761791714406524[307] = 0.0;
   out_7849761791714406524[308] = 0.0;
   out_7849761791714406524[309] = 0.0;
   out_7849761791714406524[310] = 0.0;
   out_7849761791714406524[311] = 0.0;
   out_7849761791714406524[312] = 0.0;
   out_7849761791714406524[313] = 0.0;
   out_7849761791714406524[314] = 0.0;
   out_7849761791714406524[315] = 0.0;
   out_7849761791714406524[316] = 0.0;
   out_7849761791714406524[317] = 0.0;
   out_7849761791714406524[318] = 0.0;
   out_7849761791714406524[319] = 0.0;
   out_7849761791714406524[320] = 0.0;
   out_7849761791714406524[321] = 0.0;
   out_7849761791714406524[322] = 0.0;
   out_7849761791714406524[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4127372900134371769) {
   out_4127372900134371769[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4127372900134371769[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4127372900134371769[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4127372900134371769[3] = dt*state[12] + state[3];
   out_4127372900134371769[4] = dt*state[13] + state[4];
   out_4127372900134371769[5] = dt*state[14] + state[5];
   out_4127372900134371769[6] = state[6];
   out_4127372900134371769[7] = state[7];
   out_4127372900134371769[8] = state[8];
   out_4127372900134371769[9] = state[9];
   out_4127372900134371769[10] = state[10];
   out_4127372900134371769[11] = state[11];
   out_4127372900134371769[12] = state[12];
   out_4127372900134371769[13] = state[13];
   out_4127372900134371769[14] = state[14];
   out_4127372900134371769[15] = state[15];
   out_4127372900134371769[16] = state[16];
   out_4127372900134371769[17] = state[17];
}
void F_fun(double *state, double dt, double *out_6790734299023463428) {
   out_6790734299023463428[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6790734299023463428[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6790734299023463428[2] = 0;
   out_6790734299023463428[3] = 0;
   out_6790734299023463428[4] = 0;
   out_6790734299023463428[5] = 0;
   out_6790734299023463428[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6790734299023463428[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6790734299023463428[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6790734299023463428[9] = 0;
   out_6790734299023463428[10] = 0;
   out_6790734299023463428[11] = 0;
   out_6790734299023463428[12] = 0;
   out_6790734299023463428[13] = 0;
   out_6790734299023463428[14] = 0;
   out_6790734299023463428[15] = 0;
   out_6790734299023463428[16] = 0;
   out_6790734299023463428[17] = 0;
   out_6790734299023463428[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6790734299023463428[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6790734299023463428[20] = 0;
   out_6790734299023463428[21] = 0;
   out_6790734299023463428[22] = 0;
   out_6790734299023463428[23] = 0;
   out_6790734299023463428[24] = 0;
   out_6790734299023463428[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6790734299023463428[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6790734299023463428[27] = 0;
   out_6790734299023463428[28] = 0;
   out_6790734299023463428[29] = 0;
   out_6790734299023463428[30] = 0;
   out_6790734299023463428[31] = 0;
   out_6790734299023463428[32] = 0;
   out_6790734299023463428[33] = 0;
   out_6790734299023463428[34] = 0;
   out_6790734299023463428[35] = 0;
   out_6790734299023463428[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6790734299023463428[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6790734299023463428[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6790734299023463428[39] = 0;
   out_6790734299023463428[40] = 0;
   out_6790734299023463428[41] = 0;
   out_6790734299023463428[42] = 0;
   out_6790734299023463428[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6790734299023463428[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6790734299023463428[45] = 0;
   out_6790734299023463428[46] = 0;
   out_6790734299023463428[47] = 0;
   out_6790734299023463428[48] = 0;
   out_6790734299023463428[49] = 0;
   out_6790734299023463428[50] = 0;
   out_6790734299023463428[51] = 0;
   out_6790734299023463428[52] = 0;
   out_6790734299023463428[53] = 0;
   out_6790734299023463428[54] = 0;
   out_6790734299023463428[55] = 0;
   out_6790734299023463428[56] = 0;
   out_6790734299023463428[57] = 1;
   out_6790734299023463428[58] = 0;
   out_6790734299023463428[59] = 0;
   out_6790734299023463428[60] = 0;
   out_6790734299023463428[61] = 0;
   out_6790734299023463428[62] = 0;
   out_6790734299023463428[63] = 0;
   out_6790734299023463428[64] = 0;
   out_6790734299023463428[65] = 0;
   out_6790734299023463428[66] = dt;
   out_6790734299023463428[67] = 0;
   out_6790734299023463428[68] = 0;
   out_6790734299023463428[69] = 0;
   out_6790734299023463428[70] = 0;
   out_6790734299023463428[71] = 0;
   out_6790734299023463428[72] = 0;
   out_6790734299023463428[73] = 0;
   out_6790734299023463428[74] = 0;
   out_6790734299023463428[75] = 0;
   out_6790734299023463428[76] = 1;
   out_6790734299023463428[77] = 0;
   out_6790734299023463428[78] = 0;
   out_6790734299023463428[79] = 0;
   out_6790734299023463428[80] = 0;
   out_6790734299023463428[81] = 0;
   out_6790734299023463428[82] = 0;
   out_6790734299023463428[83] = 0;
   out_6790734299023463428[84] = 0;
   out_6790734299023463428[85] = dt;
   out_6790734299023463428[86] = 0;
   out_6790734299023463428[87] = 0;
   out_6790734299023463428[88] = 0;
   out_6790734299023463428[89] = 0;
   out_6790734299023463428[90] = 0;
   out_6790734299023463428[91] = 0;
   out_6790734299023463428[92] = 0;
   out_6790734299023463428[93] = 0;
   out_6790734299023463428[94] = 0;
   out_6790734299023463428[95] = 1;
   out_6790734299023463428[96] = 0;
   out_6790734299023463428[97] = 0;
   out_6790734299023463428[98] = 0;
   out_6790734299023463428[99] = 0;
   out_6790734299023463428[100] = 0;
   out_6790734299023463428[101] = 0;
   out_6790734299023463428[102] = 0;
   out_6790734299023463428[103] = 0;
   out_6790734299023463428[104] = dt;
   out_6790734299023463428[105] = 0;
   out_6790734299023463428[106] = 0;
   out_6790734299023463428[107] = 0;
   out_6790734299023463428[108] = 0;
   out_6790734299023463428[109] = 0;
   out_6790734299023463428[110] = 0;
   out_6790734299023463428[111] = 0;
   out_6790734299023463428[112] = 0;
   out_6790734299023463428[113] = 0;
   out_6790734299023463428[114] = 1;
   out_6790734299023463428[115] = 0;
   out_6790734299023463428[116] = 0;
   out_6790734299023463428[117] = 0;
   out_6790734299023463428[118] = 0;
   out_6790734299023463428[119] = 0;
   out_6790734299023463428[120] = 0;
   out_6790734299023463428[121] = 0;
   out_6790734299023463428[122] = 0;
   out_6790734299023463428[123] = 0;
   out_6790734299023463428[124] = 0;
   out_6790734299023463428[125] = 0;
   out_6790734299023463428[126] = 0;
   out_6790734299023463428[127] = 0;
   out_6790734299023463428[128] = 0;
   out_6790734299023463428[129] = 0;
   out_6790734299023463428[130] = 0;
   out_6790734299023463428[131] = 0;
   out_6790734299023463428[132] = 0;
   out_6790734299023463428[133] = 1;
   out_6790734299023463428[134] = 0;
   out_6790734299023463428[135] = 0;
   out_6790734299023463428[136] = 0;
   out_6790734299023463428[137] = 0;
   out_6790734299023463428[138] = 0;
   out_6790734299023463428[139] = 0;
   out_6790734299023463428[140] = 0;
   out_6790734299023463428[141] = 0;
   out_6790734299023463428[142] = 0;
   out_6790734299023463428[143] = 0;
   out_6790734299023463428[144] = 0;
   out_6790734299023463428[145] = 0;
   out_6790734299023463428[146] = 0;
   out_6790734299023463428[147] = 0;
   out_6790734299023463428[148] = 0;
   out_6790734299023463428[149] = 0;
   out_6790734299023463428[150] = 0;
   out_6790734299023463428[151] = 0;
   out_6790734299023463428[152] = 1;
   out_6790734299023463428[153] = 0;
   out_6790734299023463428[154] = 0;
   out_6790734299023463428[155] = 0;
   out_6790734299023463428[156] = 0;
   out_6790734299023463428[157] = 0;
   out_6790734299023463428[158] = 0;
   out_6790734299023463428[159] = 0;
   out_6790734299023463428[160] = 0;
   out_6790734299023463428[161] = 0;
   out_6790734299023463428[162] = 0;
   out_6790734299023463428[163] = 0;
   out_6790734299023463428[164] = 0;
   out_6790734299023463428[165] = 0;
   out_6790734299023463428[166] = 0;
   out_6790734299023463428[167] = 0;
   out_6790734299023463428[168] = 0;
   out_6790734299023463428[169] = 0;
   out_6790734299023463428[170] = 0;
   out_6790734299023463428[171] = 1;
   out_6790734299023463428[172] = 0;
   out_6790734299023463428[173] = 0;
   out_6790734299023463428[174] = 0;
   out_6790734299023463428[175] = 0;
   out_6790734299023463428[176] = 0;
   out_6790734299023463428[177] = 0;
   out_6790734299023463428[178] = 0;
   out_6790734299023463428[179] = 0;
   out_6790734299023463428[180] = 0;
   out_6790734299023463428[181] = 0;
   out_6790734299023463428[182] = 0;
   out_6790734299023463428[183] = 0;
   out_6790734299023463428[184] = 0;
   out_6790734299023463428[185] = 0;
   out_6790734299023463428[186] = 0;
   out_6790734299023463428[187] = 0;
   out_6790734299023463428[188] = 0;
   out_6790734299023463428[189] = 0;
   out_6790734299023463428[190] = 1;
   out_6790734299023463428[191] = 0;
   out_6790734299023463428[192] = 0;
   out_6790734299023463428[193] = 0;
   out_6790734299023463428[194] = 0;
   out_6790734299023463428[195] = 0;
   out_6790734299023463428[196] = 0;
   out_6790734299023463428[197] = 0;
   out_6790734299023463428[198] = 0;
   out_6790734299023463428[199] = 0;
   out_6790734299023463428[200] = 0;
   out_6790734299023463428[201] = 0;
   out_6790734299023463428[202] = 0;
   out_6790734299023463428[203] = 0;
   out_6790734299023463428[204] = 0;
   out_6790734299023463428[205] = 0;
   out_6790734299023463428[206] = 0;
   out_6790734299023463428[207] = 0;
   out_6790734299023463428[208] = 0;
   out_6790734299023463428[209] = 1;
   out_6790734299023463428[210] = 0;
   out_6790734299023463428[211] = 0;
   out_6790734299023463428[212] = 0;
   out_6790734299023463428[213] = 0;
   out_6790734299023463428[214] = 0;
   out_6790734299023463428[215] = 0;
   out_6790734299023463428[216] = 0;
   out_6790734299023463428[217] = 0;
   out_6790734299023463428[218] = 0;
   out_6790734299023463428[219] = 0;
   out_6790734299023463428[220] = 0;
   out_6790734299023463428[221] = 0;
   out_6790734299023463428[222] = 0;
   out_6790734299023463428[223] = 0;
   out_6790734299023463428[224] = 0;
   out_6790734299023463428[225] = 0;
   out_6790734299023463428[226] = 0;
   out_6790734299023463428[227] = 0;
   out_6790734299023463428[228] = 1;
   out_6790734299023463428[229] = 0;
   out_6790734299023463428[230] = 0;
   out_6790734299023463428[231] = 0;
   out_6790734299023463428[232] = 0;
   out_6790734299023463428[233] = 0;
   out_6790734299023463428[234] = 0;
   out_6790734299023463428[235] = 0;
   out_6790734299023463428[236] = 0;
   out_6790734299023463428[237] = 0;
   out_6790734299023463428[238] = 0;
   out_6790734299023463428[239] = 0;
   out_6790734299023463428[240] = 0;
   out_6790734299023463428[241] = 0;
   out_6790734299023463428[242] = 0;
   out_6790734299023463428[243] = 0;
   out_6790734299023463428[244] = 0;
   out_6790734299023463428[245] = 0;
   out_6790734299023463428[246] = 0;
   out_6790734299023463428[247] = 1;
   out_6790734299023463428[248] = 0;
   out_6790734299023463428[249] = 0;
   out_6790734299023463428[250] = 0;
   out_6790734299023463428[251] = 0;
   out_6790734299023463428[252] = 0;
   out_6790734299023463428[253] = 0;
   out_6790734299023463428[254] = 0;
   out_6790734299023463428[255] = 0;
   out_6790734299023463428[256] = 0;
   out_6790734299023463428[257] = 0;
   out_6790734299023463428[258] = 0;
   out_6790734299023463428[259] = 0;
   out_6790734299023463428[260] = 0;
   out_6790734299023463428[261] = 0;
   out_6790734299023463428[262] = 0;
   out_6790734299023463428[263] = 0;
   out_6790734299023463428[264] = 0;
   out_6790734299023463428[265] = 0;
   out_6790734299023463428[266] = 1;
   out_6790734299023463428[267] = 0;
   out_6790734299023463428[268] = 0;
   out_6790734299023463428[269] = 0;
   out_6790734299023463428[270] = 0;
   out_6790734299023463428[271] = 0;
   out_6790734299023463428[272] = 0;
   out_6790734299023463428[273] = 0;
   out_6790734299023463428[274] = 0;
   out_6790734299023463428[275] = 0;
   out_6790734299023463428[276] = 0;
   out_6790734299023463428[277] = 0;
   out_6790734299023463428[278] = 0;
   out_6790734299023463428[279] = 0;
   out_6790734299023463428[280] = 0;
   out_6790734299023463428[281] = 0;
   out_6790734299023463428[282] = 0;
   out_6790734299023463428[283] = 0;
   out_6790734299023463428[284] = 0;
   out_6790734299023463428[285] = 1;
   out_6790734299023463428[286] = 0;
   out_6790734299023463428[287] = 0;
   out_6790734299023463428[288] = 0;
   out_6790734299023463428[289] = 0;
   out_6790734299023463428[290] = 0;
   out_6790734299023463428[291] = 0;
   out_6790734299023463428[292] = 0;
   out_6790734299023463428[293] = 0;
   out_6790734299023463428[294] = 0;
   out_6790734299023463428[295] = 0;
   out_6790734299023463428[296] = 0;
   out_6790734299023463428[297] = 0;
   out_6790734299023463428[298] = 0;
   out_6790734299023463428[299] = 0;
   out_6790734299023463428[300] = 0;
   out_6790734299023463428[301] = 0;
   out_6790734299023463428[302] = 0;
   out_6790734299023463428[303] = 0;
   out_6790734299023463428[304] = 1;
   out_6790734299023463428[305] = 0;
   out_6790734299023463428[306] = 0;
   out_6790734299023463428[307] = 0;
   out_6790734299023463428[308] = 0;
   out_6790734299023463428[309] = 0;
   out_6790734299023463428[310] = 0;
   out_6790734299023463428[311] = 0;
   out_6790734299023463428[312] = 0;
   out_6790734299023463428[313] = 0;
   out_6790734299023463428[314] = 0;
   out_6790734299023463428[315] = 0;
   out_6790734299023463428[316] = 0;
   out_6790734299023463428[317] = 0;
   out_6790734299023463428[318] = 0;
   out_6790734299023463428[319] = 0;
   out_6790734299023463428[320] = 0;
   out_6790734299023463428[321] = 0;
   out_6790734299023463428[322] = 0;
   out_6790734299023463428[323] = 1;
}
void h_4(double *state, double *unused, double *out_7856717095735989173) {
   out_7856717095735989173[0] = state[6] + state[9];
   out_7856717095735989173[1] = state[7] + state[10];
   out_7856717095735989173[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6651814309831508420) {
   out_6651814309831508420[0] = 0;
   out_6651814309831508420[1] = 0;
   out_6651814309831508420[2] = 0;
   out_6651814309831508420[3] = 0;
   out_6651814309831508420[4] = 0;
   out_6651814309831508420[5] = 0;
   out_6651814309831508420[6] = 1;
   out_6651814309831508420[7] = 0;
   out_6651814309831508420[8] = 0;
   out_6651814309831508420[9] = 1;
   out_6651814309831508420[10] = 0;
   out_6651814309831508420[11] = 0;
   out_6651814309831508420[12] = 0;
   out_6651814309831508420[13] = 0;
   out_6651814309831508420[14] = 0;
   out_6651814309831508420[15] = 0;
   out_6651814309831508420[16] = 0;
   out_6651814309831508420[17] = 0;
   out_6651814309831508420[18] = 0;
   out_6651814309831508420[19] = 0;
   out_6651814309831508420[20] = 0;
   out_6651814309831508420[21] = 0;
   out_6651814309831508420[22] = 0;
   out_6651814309831508420[23] = 0;
   out_6651814309831508420[24] = 0;
   out_6651814309831508420[25] = 1;
   out_6651814309831508420[26] = 0;
   out_6651814309831508420[27] = 0;
   out_6651814309831508420[28] = 1;
   out_6651814309831508420[29] = 0;
   out_6651814309831508420[30] = 0;
   out_6651814309831508420[31] = 0;
   out_6651814309831508420[32] = 0;
   out_6651814309831508420[33] = 0;
   out_6651814309831508420[34] = 0;
   out_6651814309831508420[35] = 0;
   out_6651814309831508420[36] = 0;
   out_6651814309831508420[37] = 0;
   out_6651814309831508420[38] = 0;
   out_6651814309831508420[39] = 0;
   out_6651814309831508420[40] = 0;
   out_6651814309831508420[41] = 0;
   out_6651814309831508420[42] = 0;
   out_6651814309831508420[43] = 0;
   out_6651814309831508420[44] = 1;
   out_6651814309831508420[45] = 0;
   out_6651814309831508420[46] = 0;
   out_6651814309831508420[47] = 1;
   out_6651814309831508420[48] = 0;
   out_6651814309831508420[49] = 0;
   out_6651814309831508420[50] = 0;
   out_6651814309831508420[51] = 0;
   out_6651814309831508420[52] = 0;
   out_6651814309831508420[53] = 0;
}
void h_10(double *state, double *unused, double *out_7802819887885526758) {
   out_7802819887885526758[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_7802819887885526758[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_7802819887885526758[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2391217134998665876) {
   out_2391217134998665876[0] = 0;
   out_2391217134998665876[1] = 9.8100000000000005*cos(state[1]);
   out_2391217134998665876[2] = 0;
   out_2391217134998665876[3] = 0;
   out_2391217134998665876[4] = -state[8];
   out_2391217134998665876[5] = state[7];
   out_2391217134998665876[6] = 0;
   out_2391217134998665876[7] = state[5];
   out_2391217134998665876[8] = -state[4];
   out_2391217134998665876[9] = 0;
   out_2391217134998665876[10] = 0;
   out_2391217134998665876[11] = 0;
   out_2391217134998665876[12] = 1;
   out_2391217134998665876[13] = 0;
   out_2391217134998665876[14] = 0;
   out_2391217134998665876[15] = 1;
   out_2391217134998665876[16] = 0;
   out_2391217134998665876[17] = 0;
   out_2391217134998665876[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2391217134998665876[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2391217134998665876[20] = 0;
   out_2391217134998665876[21] = state[8];
   out_2391217134998665876[22] = 0;
   out_2391217134998665876[23] = -state[6];
   out_2391217134998665876[24] = -state[5];
   out_2391217134998665876[25] = 0;
   out_2391217134998665876[26] = state[3];
   out_2391217134998665876[27] = 0;
   out_2391217134998665876[28] = 0;
   out_2391217134998665876[29] = 0;
   out_2391217134998665876[30] = 0;
   out_2391217134998665876[31] = 1;
   out_2391217134998665876[32] = 0;
   out_2391217134998665876[33] = 0;
   out_2391217134998665876[34] = 1;
   out_2391217134998665876[35] = 0;
   out_2391217134998665876[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2391217134998665876[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2391217134998665876[38] = 0;
   out_2391217134998665876[39] = -state[7];
   out_2391217134998665876[40] = state[6];
   out_2391217134998665876[41] = 0;
   out_2391217134998665876[42] = state[4];
   out_2391217134998665876[43] = -state[3];
   out_2391217134998665876[44] = 0;
   out_2391217134998665876[45] = 0;
   out_2391217134998665876[46] = 0;
   out_2391217134998665876[47] = 0;
   out_2391217134998665876[48] = 0;
   out_2391217134998665876[49] = 0;
   out_2391217134998665876[50] = 1;
   out_2391217134998665876[51] = 0;
   out_2391217134998665876[52] = 0;
   out_2391217134998665876[53] = 1;
}
void h_13(double *state, double *unused, double *out_7948582274063627909) {
   out_7948582274063627909[0] = state[3];
   out_7948582274063627909[1] = state[4];
   out_7948582274063627909[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3439540484499175619) {
   out_3439540484499175619[0] = 0;
   out_3439540484499175619[1] = 0;
   out_3439540484499175619[2] = 0;
   out_3439540484499175619[3] = 1;
   out_3439540484499175619[4] = 0;
   out_3439540484499175619[5] = 0;
   out_3439540484499175619[6] = 0;
   out_3439540484499175619[7] = 0;
   out_3439540484499175619[8] = 0;
   out_3439540484499175619[9] = 0;
   out_3439540484499175619[10] = 0;
   out_3439540484499175619[11] = 0;
   out_3439540484499175619[12] = 0;
   out_3439540484499175619[13] = 0;
   out_3439540484499175619[14] = 0;
   out_3439540484499175619[15] = 0;
   out_3439540484499175619[16] = 0;
   out_3439540484499175619[17] = 0;
   out_3439540484499175619[18] = 0;
   out_3439540484499175619[19] = 0;
   out_3439540484499175619[20] = 0;
   out_3439540484499175619[21] = 0;
   out_3439540484499175619[22] = 1;
   out_3439540484499175619[23] = 0;
   out_3439540484499175619[24] = 0;
   out_3439540484499175619[25] = 0;
   out_3439540484499175619[26] = 0;
   out_3439540484499175619[27] = 0;
   out_3439540484499175619[28] = 0;
   out_3439540484499175619[29] = 0;
   out_3439540484499175619[30] = 0;
   out_3439540484499175619[31] = 0;
   out_3439540484499175619[32] = 0;
   out_3439540484499175619[33] = 0;
   out_3439540484499175619[34] = 0;
   out_3439540484499175619[35] = 0;
   out_3439540484499175619[36] = 0;
   out_3439540484499175619[37] = 0;
   out_3439540484499175619[38] = 0;
   out_3439540484499175619[39] = 0;
   out_3439540484499175619[40] = 0;
   out_3439540484499175619[41] = 1;
   out_3439540484499175619[42] = 0;
   out_3439540484499175619[43] = 0;
   out_3439540484499175619[44] = 0;
   out_3439540484499175619[45] = 0;
   out_3439540484499175619[46] = 0;
   out_3439540484499175619[47] = 0;
   out_3439540484499175619[48] = 0;
   out_3439540484499175619[49] = 0;
   out_3439540484499175619[50] = 0;
   out_3439540484499175619[51] = 0;
   out_3439540484499175619[52] = 0;
   out_3439540484499175619[53] = 0;
}
void h_14(double *state, double *unused, double *out_223099352326779878) {
   out_223099352326779878[0] = state[6];
   out_223099352326779878[1] = state[7];
   out_223099352326779878[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8712141331582670900) {
   out_8712141331582670900[0] = 0;
   out_8712141331582670900[1] = 0;
   out_8712141331582670900[2] = 0;
   out_8712141331582670900[3] = 0;
   out_8712141331582670900[4] = 0;
   out_8712141331582670900[5] = 0;
   out_8712141331582670900[6] = 1;
   out_8712141331582670900[7] = 0;
   out_8712141331582670900[8] = 0;
   out_8712141331582670900[9] = 0;
   out_8712141331582670900[10] = 0;
   out_8712141331582670900[11] = 0;
   out_8712141331582670900[12] = 0;
   out_8712141331582670900[13] = 0;
   out_8712141331582670900[14] = 0;
   out_8712141331582670900[15] = 0;
   out_8712141331582670900[16] = 0;
   out_8712141331582670900[17] = 0;
   out_8712141331582670900[18] = 0;
   out_8712141331582670900[19] = 0;
   out_8712141331582670900[20] = 0;
   out_8712141331582670900[21] = 0;
   out_8712141331582670900[22] = 0;
   out_8712141331582670900[23] = 0;
   out_8712141331582670900[24] = 0;
   out_8712141331582670900[25] = 1;
   out_8712141331582670900[26] = 0;
   out_8712141331582670900[27] = 0;
   out_8712141331582670900[28] = 0;
   out_8712141331582670900[29] = 0;
   out_8712141331582670900[30] = 0;
   out_8712141331582670900[31] = 0;
   out_8712141331582670900[32] = 0;
   out_8712141331582670900[33] = 0;
   out_8712141331582670900[34] = 0;
   out_8712141331582670900[35] = 0;
   out_8712141331582670900[36] = 0;
   out_8712141331582670900[37] = 0;
   out_8712141331582670900[38] = 0;
   out_8712141331582670900[39] = 0;
   out_8712141331582670900[40] = 0;
   out_8712141331582670900[41] = 0;
   out_8712141331582670900[42] = 0;
   out_8712141331582670900[43] = 0;
   out_8712141331582670900[44] = 1;
   out_8712141331582670900[45] = 0;
   out_8712141331582670900[46] = 0;
   out_8712141331582670900[47] = 0;
   out_8712141331582670900[48] = 0;
   out_8712141331582670900[49] = 0;
   out_8712141331582670900[50] = 0;
   out_8712141331582670900[51] = 0;
   out_8712141331582670900[52] = 0;
   out_8712141331582670900[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5763415234273933913) {
  err_fun(nom_x, delta_x, out_5763415234273933913);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1417325942549329712) {
  inv_err_fun(nom_x, true_x, out_1417325942549329712);
}
void pose_H_mod_fun(double *state, double *out_7849761791714406524) {
  H_mod_fun(state, out_7849761791714406524);
}
void pose_f_fun(double *state, double dt, double *out_4127372900134371769) {
  f_fun(state,  dt, out_4127372900134371769);
}
void pose_F_fun(double *state, double dt, double *out_6790734299023463428) {
  F_fun(state,  dt, out_6790734299023463428);
}
void pose_h_4(double *state, double *unused, double *out_7856717095735989173) {
  h_4(state, unused, out_7856717095735989173);
}
void pose_H_4(double *state, double *unused, double *out_6651814309831508420) {
  H_4(state, unused, out_6651814309831508420);
}
void pose_h_10(double *state, double *unused, double *out_7802819887885526758) {
  h_10(state, unused, out_7802819887885526758);
}
void pose_H_10(double *state, double *unused, double *out_2391217134998665876) {
  H_10(state, unused, out_2391217134998665876);
}
void pose_h_13(double *state, double *unused, double *out_7948582274063627909) {
  h_13(state, unused, out_7948582274063627909);
}
void pose_H_13(double *state, double *unused, double *out_3439540484499175619) {
  H_13(state, unused, out_3439540484499175619);
}
void pose_h_14(double *state, double *unused, double *out_223099352326779878) {
  h_14(state, unused, out_223099352326779878);
}
void pose_H_14(double *state, double *unused, double *out_8712141331582670900) {
  H_14(state, unused, out_8712141331582670900);
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
