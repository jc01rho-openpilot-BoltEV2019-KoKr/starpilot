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
void err_fun(double *nom_x, double *delta_x, double *out_5206974560936582462) {
   out_5206974560936582462[0] = delta_x[0] + nom_x[0];
   out_5206974560936582462[1] = delta_x[1] + nom_x[1];
   out_5206974560936582462[2] = delta_x[2] + nom_x[2];
   out_5206974560936582462[3] = delta_x[3] + nom_x[3];
   out_5206974560936582462[4] = delta_x[4] + nom_x[4];
   out_5206974560936582462[5] = delta_x[5] + nom_x[5];
   out_5206974560936582462[6] = delta_x[6] + nom_x[6];
   out_5206974560936582462[7] = delta_x[7] + nom_x[7];
   out_5206974560936582462[8] = delta_x[8] + nom_x[8];
   out_5206974560936582462[9] = delta_x[9] + nom_x[9];
   out_5206974560936582462[10] = delta_x[10] + nom_x[10];
   out_5206974560936582462[11] = delta_x[11] + nom_x[11];
   out_5206974560936582462[12] = delta_x[12] + nom_x[12];
   out_5206974560936582462[13] = delta_x[13] + nom_x[13];
   out_5206974560936582462[14] = delta_x[14] + nom_x[14];
   out_5206974560936582462[15] = delta_x[15] + nom_x[15];
   out_5206974560936582462[16] = delta_x[16] + nom_x[16];
   out_5206974560936582462[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8580851081509816390) {
   out_8580851081509816390[0] = -nom_x[0] + true_x[0];
   out_8580851081509816390[1] = -nom_x[1] + true_x[1];
   out_8580851081509816390[2] = -nom_x[2] + true_x[2];
   out_8580851081509816390[3] = -nom_x[3] + true_x[3];
   out_8580851081509816390[4] = -nom_x[4] + true_x[4];
   out_8580851081509816390[5] = -nom_x[5] + true_x[5];
   out_8580851081509816390[6] = -nom_x[6] + true_x[6];
   out_8580851081509816390[7] = -nom_x[7] + true_x[7];
   out_8580851081509816390[8] = -nom_x[8] + true_x[8];
   out_8580851081509816390[9] = -nom_x[9] + true_x[9];
   out_8580851081509816390[10] = -nom_x[10] + true_x[10];
   out_8580851081509816390[11] = -nom_x[11] + true_x[11];
   out_8580851081509816390[12] = -nom_x[12] + true_x[12];
   out_8580851081509816390[13] = -nom_x[13] + true_x[13];
   out_8580851081509816390[14] = -nom_x[14] + true_x[14];
   out_8580851081509816390[15] = -nom_x[15] + true_x[15];
   out_8580851081509816390[16] = -nom_x[16] + true_x[16];
   out_8580851081509816390[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_310958725680718826) {
   out_310958725680718826[0] = 1.0;
   out_310958725680718826[1] = 0.0;
   out_310958725680718826[2] = 0.0;
   out_310958725680718826[3] = 0.0;
   out_310958725680718826[4] = 0.0;
   out_310958725680718826[5] = 0.0;
   out_310958725680718826[6] = 0.0;
   out_310958725680718826[7] = 0.0;
   out_310958725680718826[8] = 0.0;
   out_310958725680718826[9] = 0.0;
   out_310958725680718826[10] = 0.0;
   out_310958725680718826[11] = 0.0;
   out_310958725680718826[12] = 0.0;
   out_310958725680718826[13] = 0.0;
   out_310958725680718826[14] = 0.0;
   out_310958725680718826[15] = 0.0;
   out_310958725680718826[16] = 0.0;
   out_310958725680718826[17] = 0.0;
   out_310958725680718826[18] = 0.0;
   out_310958725680718826[19] = 1.0;
   out_310958725680718826[20] = 0.0;
   out_310958725680718826[21] = 0.0;
   out_310958725680718826[22] = 0.0;
   out_310958725680718826[23] = 0.0;
   out_310958725680718826[24] = 0.0;
   out_310958725680718826[25] = 0.0;
   out_310958725680718826[26] = 0.0;
   out_310958725680718826[27] = 0.0;
   out_310958725680718826[28] = 0.0;
   out_310958725680718826[29] = 0.0;
   out_310958725680718826[30] = 0.0;
   out_310958725680718826[31] = 0.0;
   out_310958725680718826[32] = 0.0;
   out_310958725680718826[33] = 0.0;
   out_310958725680718826[34] = 0.0;
   out_310958725680718826[35] = 0.0;
   out_310958725680718826[36] = 0.0;
   out_310958725680718826[37] = 0.0;
   out_310958725680718826[38] = 1.0;
   out_310958725680718826[39] = 0.0;
   out_310958725680718826[40] = 0.0;
   out_310958725680718826[41] = 0.0;
   out_310958725680718826[42] = 0.0;
   out_310958725680718826[43] = 0.0;
   out_310958725680718826[44] = 0.0;
   out_310958725680718826[45] = 0.0;
   out_310958725680718826[46] = 0.0;
   out_310958725680718826[47] = 0.0;
   out_310958725680718826[48] = 0.0;
   out_310958725680718826[49] = 0.0;
   out_310958725680718826[50] = 0.0;
   out_310958725680718826[51] = 0.0;
   out_310958725680718826[52] = 0.0;
   out_310958725680718826[53] = 0.0;
   out_310958725680718826[54] = 0.0;
   out_310958725680718826[55] = 0.0;
   out_310958725680718826[56] = 0.0;
   out_310958725680718826[57] = 1.0;
   out_310958725680718826[58] = 0.0;
   out_310958725680718826[59] = 0.0;
   out_310958725680718826[60] = 0.0;
   out_310958725680718826[61] = 0.0;
   out_310958725680718826[62] = 0.0;
   out_310958725680718826[63] = 0.0;
   out_310958725680718826[64] = 0.0;
   out_310958725680718826[65] = 0.0;
   out_310958725680718826[66] = 0.0;
   out_310958725680718826[67] = 0.0;
   out_310958725680718826[68] = 0.0;
   out_310958725680718826[69] = 0.0;
   out_310958725680718826[70] = 0.0;
   out_310958725680718826[71] = 0.0;
   out_310958725680718826[72] = 0.0;
   out_310958725680718826[73] = 0.0;
   out_310958725680718826[74] = 0.0;
   out_310958725680718826[75] = 0.0;
   out_310958725680718826[76] = 1.0;
   out_310958725680718826[77] = 0.0;
   out_310958725680718826[78] = 0.0;
   out_310958725680718826[79] = 0.0;
   out_310958725680718826[80] = 0.0;
   out_310958725680718826[81] = 0.0;
   out_310958725680718826[82] = 0.0;
   out_310958725680718826[83] = 0.0;
   out_310958725680718826[84] = 0.0;
   out_310958725680718826[85] = 0.0;
   out_310958725680718826[86] = 0.0;
   out_310958725680718826[87] = 0.0;
   out_310958725680718826[88] = 0.0;
   out_310958725680718826[89] = 0.0;
   out_310958725680718826[90] = 0.0;
   out_310958725680718826[91] = 0.0;
   out_310958725680718826[92] = 0.0;
   out_310958725680718826[93] = 0.0;
   out_310958725680718826[94] = 0.0;
   out_310958725680718826[95] = 1.0;
   out_310958725680718826[96] = 0.0;
   out_310958725680718826[97] = 0.0;
   out_310958725680718826[98] = 0.0;
   out_310958725680718826[99] = 0.0;
   out_310958725680718826[100] = 0.0;
   out_310958725680718826[101] = 0.0;
   out_310958725680718826[102] = 0.0;
   out_310958725680718826[103] = 0.0;
   out_310958725680718826[104] = 0.0;
   out_310958725680718826[105] = 0.0;
   out_310958725680718826[106] = 0.0;
   out_310958725680718826[107] = 0.0;
   out_310958725680718826[108] = 0.0;
   out_310958725680718826[109] = 0.0;
   out_310958725680718826[110] = 0.0;
   out_310958725680718826[111] = 0.0;
   out_310958725680718826[112] = 0.0;
   out_310958725680718826[113] = 0.0;
   out_310958725680718826[114] = 1.0;
   out_310958725680718826[115] = 0.0;
   out_310958725680718826[116] = 0.0;
   out_310958725680718826[117] = 0.0;
   out_310958725680718826[118] = 0.0;
   out_310958725680718826[119] = 0.0;
   out_310958725680718826[120] = 0.0;
   out_310958725680718826[121] = 0.0;
   out_310958725680718826[122] = 0.0;
   out_310958725680718826[123] = 0.0;
   out_310958725680718826[124] = 0.0;
   out_310958725680718826[125] = 0.0;
   out_310958725680718826[126] = 0.0;
   out_310958725680718826[127] = 0.0;
   out_310958725680718826[128] = 0.0;
   out_310958725680718826[129] = 0.0;
   out_310958725680718826[130] = 0.0;
   out_310958725680718826[131] = 0.0;
   out_310958725680718826[132] = 0.0;
   out_310958725680718826[133] = 1.0;
   out_310958725680718826[134] = 0.0;
   out_310958725680718826[135] = 0.0;
   out_310958725680718826[136] = 0.0;
   out_310958725680718826[137] = 0.0;
   out_310958725680718826[138] = 0.0;
   out_310958725680718826[139] = 0.0;
   out_310958725680718826[140] = 0.0;
   out_310958725680718826[141] = 0.0;
   out_310958725680718826[142] = 0.0;
   out_310958725680718826[143] = 0.0;
   out_310958725680718826[144] = 0.0;
   out_310958725680718826[145] = 0.0;
   out_310958725680718826[146] = 0.0;
   out_310958725680718826[147] = 0.0;
   out_310958725680718826[148] = 0.0;
   out_310958725680718826[149] = 0.0;
   out_310958725680718826[150] = 0.0;
   out_310958725680718826[151] = 0.0;
   out_310958725680718826[152] = 1.0;
   out_310958725680718826[153] = 0.0;
   out_310958725680718826[154] = 0.0;
   out_310958725680718826[155] = 0.0;
   out_310958725680718826[156] = 0.0;
   out_310958725680718826[157] = 0.0;
   out_310958725680718826[158] = 0.0;
   out_310958725680718826[159] = 0.0;
   out_310958725680718826[160] = 0.0;
   out_310958725680718826[161] = 0.0;
   out_310958725680718826[162] = 0.0;
   out_310958725680718826[163] = 0.0;
   out_310958725680718826[164] = 0.0;
   out_310958725680718826[165] = 0.0;
   out_310958725680718826[166] = 0.0;
   out_310958725680718826[167] = 0.0;
   out_310958725680718826[168] = 0.0;
   out_310958725680718826[169] = 0.0;
   out_310958725680718826[170] = 0.0;
   out_310958725680718826[171] = 1.0;
   out_310958725680718826[172] = 0.0;
   out_310958725680718826[173] = 0.0;
   out_310958725680718826[174] = 0.0;
   out_310958725680718826[175] = 0.0;
   out_310958725680718826[176] = 0.0;
   out_310958725680718826[177] = 0.0;
   out_310958725680718826[178] = 0.0;
   out_310958725680718826[179] = 0.0;
   out_310958725680718826[180] = 0.0;
   out_310958725680718826[181] = 0.0;
   out_310958725680718826[182] = 0.0;
   out_310958725680718826[183] = 0.0;
   out_310958725680718826[184] = 0.0;
   out_310958725680718826[185] = 0.0;
   out_310958725680718826[186] = 0.0;
   out_310958725680718826[187] = 0.0;
   out_310958725680718826[188] = 0.0;
   out_310958725680718826[189] = 0.0;
   out_310958725680718826[190] = 1.0;
   out_310958725680718826[191] = 0.0;
   out_310958725680718826[192] = 0.0;
   out_310958725680718826[193] = 0.0;
   out_310958725680718826[194] = 0.0;
   out_310958725680718826[195] = 0.0;
   out_310958725680718826[196] = 0.0;
   out_310958725680718826[197] = 0.0;
   out_310958725680718826[198] = 0.0;
   out_310958725680718826[199] = 0.0;
   out_310958725680718826[200] = 0.0;
   out_310958725680718826[201] = 0.0;
   out_310958725680718826[202] = 0.0;
   out_310958725680718826[203] = 0.0;
   out_310958725680718826[204] = 0.0;
   out_310958725680718826[205] = 0.0;
   out_310958725680718826[206] = 0.0;
   out_310958725680718826[207] = 0.0;
   out_310958725680718826[208] = 0.0;
   out_310958725680718826[209] = 1.0;
   out_310958725680718826[210] = 0.0;
   out_310958725680718826[211] = 0.0;
   out_310958725680718826[212] = 0.0;
   out_310958725680718826[213] = 0.0;
   out_310958725680718826[214] = 0.0;
   out_310958725680718826[215] = 0.0;
   out_310958725680718826[216] = 0.0;
   out_310958725680718826[217] = 0.0;
   out_310958725680718826[218] = 0.0;
   out_310958725680718826[219] = 0.0;
   out_310958725680718826[220] = 0.0;
   out_310958725680718826[221] = 0.0;
   out_310958725680718826[222] = 0.0;
   out_310958725680718826[223] = 0.0;
   out_310958725680718826[224] = 0.0;
   out_310958725680718826[225] = 0.0;
   out_310958725680718826[226] = 0.0;
   out_310958725680718826[227] = 0.0;
   out_310958725680718826[228] = 1.0;
   out_310958725680718826[229] = 0.0;
   out_310958725680718826[230] = 0.0;
   out_310958725680718826[231] = 0.0;
   out_310958725680718826[232] = 0.0;
   out_310958725680718826[233] = 0.0;
   out_310958725680718826[234] = 0.0;
   out_310958725680718826[235] = 0.0;
   out_310958725680718826[236] = 0.0;
   out_310958725680718826[237] = 0.0;
   out_310958725680718826[238] = 0.0;
   out_310958725680718826[239] = 0.0;
   out_310958725680718826[240] = 0.0;
   out_310958725680718826[241] = 0.0;
   out_310958725680718826[242] = 0.0;
   out_310958725680718826[243] = 0.0;
   out_310958725680718826[244] = 0.0;
   out_310958725680718826[245] = 0.0;
   out_310958725680718826[246] = 0.0;
   out_310958725680718826[247] = 1.0;
   out_310958725680718826[248] = 0.0;
   out_310958725680718826[249] = 0.0;
   out_310958725680718826[250] = 0.0;
   out_310958725680718826[251] = 0.0;
   out_310958725680718826[252] = 0.0;
   out_310958725680718826[253] = 0.0;
   out_310958725680718826[254] = 0.0;
   out_310958725680718826[255] = 0.0;
   out_310958725680718826[256] = 0.0;
   out_310958725680718826[257] = 0.0;
   out_310958725680718826[258] = 0.0;
   out_310958725680718826[259] = 0.0;
   out_310958725680718826[260] = 0.0;
   out_310958725680718826[261] = 0.0;
   out_310958725680718826[262] = 0.0;
   out_310958725680718826[263] = 0.0;
   out_310958725680718826[264] = 0.0;
   out_310958725680718826[265] = 0.0;
   out_310958725680718826[266] = 1.0;
   out_310958725680718826[267] = 0.0;
   out_310958725680718826[268] = 0.0;
   out_310958725680718826[269] = 0.0;
   out_310958725680718826[270] = 0.0;
   out_310958725680718826[271] = 0.0;
   out_310958725680718826[272] = 0.0;
   out_310958725680718826[273] = 0.0;
   out_310958725680718826[274] = 0.0;
   out_310958725680718826[275] = 0.0;
   out_310958725680718826[276] = 0.0;
   out_310958725680718826[277] = 0.0;
   out_310958725680718826[278] = 0.0;
   out_310958725680718826[279] = 0.0;
   out_310958725680718826[280] = 0.0;
   out_310958725680718826[281] = 0.0;
   out_310958725680718826[282] = 0.0;
   out_310958725680718826[283] = 0.0;
   out_310958725680718826[284] = 0.0;
   out_310958725680718826[285] = 1.0;
   out_310958725680718826[286] = 0.0;
   out_310958725680718826[287] = 0.0;
   out_310958725680718826[288] = 0.0;
   out_310958725680718826[289] = 0.0;
   out_310958725680718826[290] = 0.0;
   out_310958725680718826[291] = 0.0;
   out_310958725680718826[292] = 0.0;
   out_310958725680718826[293] = 0.0;
   out_310958725680718826[294] = 0.0;
   out_310958725680718826[295] = 0.0;
   out_310958725680718826[296] = 0.0;
   out_310958725680718826[297] = 0.0;
   out_310958725680718826[298] = 0.0;
   out_310958725680718826[299] = 0.0;
   out_310958725680718826[300] = 0.0;
   out_310958725680718826[301] = 0.0;
   out_310958725680718826[302] = 0.0;
   out_310958725680718826[303] = 0.0;
   out_310958725680718826[304] = 1.0;
   out_310958725680718826[305] = 0.0;
   out_310958725680718826[306] = 0.0;
   out_310958725680718826[307] = 0.0;
   out_310958725680718826[308] = 0.0;
   out_310958725680718826[309] = 0.0;
   out_310958725680718826[310] = 0.0;
   out_310958725680718826[311] = 0.0;
   out_310958725680718826[312] = 0.0;
   out_310958725680718826[313] = 0.0;
   out_310958725680718826[314] = 0.0;
   out_310958725680718826[315] = 0.0;
   out_310958725680718826[316] = 0.0;
   out_310958725680718826[317] = 0.0;
   out_310958725680718826[318] = 0.0;
   out_310958725680718826[319] = 0.0;
   out_310958725680718826[320] = 0.0;
   out_310958725680718826[321] = 0.0;
   out_310958725680718826[322] = 0.0;
   out_310958725680718826[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8333876756213369009) {
   out_8333876756213369009[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8333876756213369009[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8333876756213369009[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8333876756213369009[3] = dt*state[12] + state[3];
   out_8333876756213369009[4] = dt*state[13] + state[4];
   out_8333876756213369009[5] = dt*state[14] + state[5];
   out_8333876756213369009[6] = state[6];
   out_8333876756213369009[7] = state[7];
   out_8333876756213369009[8] = state[8];
   out_8333876756213369009[9] = state[9];
   out_8333876756213369009[10] = state[10];
   out_8333876756213369009[11] = state[11];
   out_8333876756213369009[12] = state[12];
   out_8333876756213369009[13] = state[13];
   out_8333876756213369009[14] = state[14];
   out_8333876756213369009[15] = state[15];
   out_8333876756213369009[16] = state[16];
   out_8333876756213369009[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8736875160637463263) {
   out_8736875160637463263[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8736875160637463263[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8736875160637463263[2] = 0;
   out_8736875160637463263[3] = 0;
   out_8736875160637463263[4] = 0;
   out_8736875160637463263[5] = 0;
   out_8736875160637463263[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8736875160637463263[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8736875160637463263[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8736875160637463263[9] = 0;
   out_8736875160637463263[10] = 0;
   out_8736875160637463263[11] = 0;
   out_8736875160637463263[12] = 0;
   out_8736875160637463263[13] = 0;
   out_8736875160637463263[14] = 0;
   out_8736875160637463263[15] = 0;
   out_8736875160637463263[16] = 0;
   out_8736875160637463263[17] = 0;
   out_8736875160637463263[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8736875160637463263[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8736875160637463263[20] = 0;
   out_8736875160637463263[21] = 0;
   out_8736875160637463263[22] = 0;
   out_8736875160637463263[23] = 0;
   out_8736875160637463263[24] = 0;
   out_8736875160637463263[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8736875160637463263[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8736875160637463263[27] = 0;
   out_8736875160637463263[28] = 0;
   out_8736875160637463263[29] = 0;
   out_8736875160637463263[30] = 0;
   out_8736875160637463263[31] = 0;
   out_8736875160637463263[32] = 0;
   out_8736875160637463263[33] = 0;
   out_8736875160637463263[34] = 0;
   out_8736875160637463263[35] = 0;
   out_8736875160637463263[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8736875160637463263[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8736875160637463263[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8736875160637463263[39] = 0;
   out_8736875160637463263[40] = 0;
   out_8736875160637463263[41] = 0;
   out_8736875160637463263[42] = 0;
   out_8736875160637463263[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8736875160637463263[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8736875160637463263[45] = 0;
   out_8736875160637463263[46] = 0;
   out_8736875160637463263[47] = 0;
   out_8736875160637463263[48] = 0;
   out_8736875160637463263[49] = 0;
   out_8736875160637463263[50] = 0;
   out_8736875160637463263[51] = 0;
   out_8736875160637463263[52] = 0;
   out_8736875160637463263[53] = 0;
   out_8736875160637463263[54] = 0;
   out_8736875160637463263[55] = 0;
   out_8736875160637463263[56] = 0;
   out_8736875160637463263[57] = 1;
   out_8736875160637463263[58] = 0;
   out_8736875160637463263[59] = 0;
   out_8736875160637463263[60] = 0;
   out_8736875160637463263[61] = 0;
   out_8736875160637463263[62] = 0;
   out_8736875160637463263[63] = 0;
   out_8736875160637463263[64] = 0;
   out_8736875160637463263[65] = 0;
   out_8736875160637463263[66] = dt;
   out_8736875160637463263[67] = 0;
   out_8736875160637463263[68] = 0;
   out_8736875160637463263[69] = 0;
   out_8736875160637463263[70] = 0;
   out_8736875160637463263[71] = 0;
   out_8736875160637463263[72] = 0;
   out_8736875160637463263[73] = 0;
   out_8736875160637463263[74] = 0;
   out_8736875160637463263[75] = 0;
   out_8736875160637463263[76] = 1;
   out_8736875160637463263[77] = 0;
   out_8736875160637463263[78] = 0;
   out_8736875160637463263[79] = 0;
   out_8736875160637463263[80] = 0;
   out_8736875160637463263[81] = 0;
   out_8736875160637463263[82] = 0;
   out_8736875160637463263[83] = 0;
   out_8736875160637463263[84] = 0;
   out_8736875160637463263[85] = dt;
   out_8736875160637463263[86] = 0;
   out_8736875160637463263[87] = 0;
   out_8736875160637463263[88] = 0;
   out_8736875160637463263[89] = 0;
   out_8736875160637463263[90] = 0;
   out_8736875160637463263[91] = 0;
   out_8736875160637463263[92] = 0;
   out_8736875160637463263[93] = 0;
   out_8736875160637463263[94] = 0;
   out_8736875160637463263[95] = 1;
   out_8736875160637463263[96] = 0;
   out_8736875160637463263[97] = 0;
   out_8736875160637463263[98] = 0;
   out_8736875160637463263[99] = 0;
   out_8736875160637463263[100] = 0;
   out_8736875160637463263[101] = 0;
   out_8736875160637463263[102] = 0;
   out_8736875160637463263[103] = 0;
   out_8736875160637463263[104] = dt;
   out_8736875160637463263[105] = 0;
   out_8736875160637463263[106] = 0;
   out_8736875160637463263[107] = 0;
   out_8736875160637463263[108] = 0;
   out_8736875160637463263[109] = 0;
   out_8736875160637463263[110] = 0;
   out_8736875160637463263[111] = 0;
   out_8736875160637463263[112] = 0;
   out_8736875160637463263[113] = 0;
   out_8736875160637463263[114] = 1;
   out_8736875160637463263[115] = 0;
   out_8736875160637463263[116] = 0;
   out_8736875160637463263[117] = 0;
   out_8736875160637463263[118] = 0;
   out_8736875160637463263[119] = 0;
   out_8736875160637463263[120] = 0;
   out_8736875160637463263[121] = 0;
   out_8736875160637463263[122] = 0;
   out_8736875160637463263[123] = 0;
   out_8736875160637463263[124] = 0;
   out_8736875160637463263[125] = 0;
   out_8736875160637463263[126] = 0;
   out_8736875160637463263[127] = 0;
   out_8736875160637463263[128] = 0;
   out_8736875160637463263[129] = 0;
   out_8736875160637463263[130] = 0;
   out_8736875160637463263[131] = 0;
   out_8736875160637463263[132] = 0;
   out_8736875160637463263[133] = 1;
   out_8736875160637463263[134] = 0;
   out_8736875160637463263[135] = 0;
   out_8736875160637463263[136] = 0;
   out_8736875160637463263[137] = 0;
   out_8736875160637463263[138] = 0;
   out_8736875160637463263[139] = 0;
   out_8736875160637463263[140] = 0;
   out_8736875160637463263[141] = 0;
   out_8736875160637463263[142] = 0;
   out_8736875160637463263[143] = 0;
   out_8736875160637463263[144] = 0;
   out_8736875160637463263[145] = 0;
   out_8736875160637463263[146] = 0;
   out_8736875160637463263[147] = 0;
   out_8736875160637463263[148] = 0;
   out_8736875160637463263[149] = 0;
   out_8736875160637463263[150] = 0;
   out_8736875160637463263[151] = 0;
   out_8736875160637463263[152] = 1;
   out_8736875160637463263[153] = 0;
   out_8736875160637463263[154] = 0;
   out_8736875160637463263[155] = 0;
   out_8736875160637463263[156] = 0;
   out_8736875160637463263[157] = 0;
   out_8736875160637463263[158] = 0;
   out_8736875160637463263[159] = 0;
   out_8736875160637463263[160] = 0;
   out_8736875160637463263[161] = 0;
   out_8736875160637463263[162] = 0;
   out_8736875160637463263[163] = 0;
   out_8736875160637463263[164] = 0;
   out_8736875160637463263[165] = 0;
   out_8736875160637463263[166] = 0;
   out_8736875160637463263[167] = 0;
   out_8736875160637463263[168] = 0;
   out_8736875160637463263[169] = 0;
   out_8736875160637463263[170] = 0;
   out_8736875160637463263[171] = 1;
   out_8736875160637463263[172] = 0;
   out_8736875160637463263[173] = 0;
   out_8736875160637463263[174] = 0;
   out_8736875160637463263[175] = 0;
   out_8736875160637463263[176] = 0;
   out_8736875160637463263[177] = 0;
   out_8736875160637463263[178] = 0;
   out_8736875160637463263[179] = 0;
   out_8736875160637463263[180] = 0;
   out_8736875160637463263[181] = 0;
   out_8736875160637463263[182] = 0;
   out_8736875160637463263[183] = 0;
   out_8736875160637463263[184] = 0;
   out_8736875160637463263[185] = 0;
   out_8736875160637463263[186] = 0;
   out_8736875160637463263[187] = 0;
   out_8736875160637463263[188] = 0;
   out_8736875160637463263[189] = 0;
   out_8736875160637463263[190] = 1;
   out_8736875160637463263[191] = 0;
   out_8736875160637463263[192] = 0;
   out_8736875160637463263[193] = 0;
   out_8736875160637463263[194] = 0;
   out_8736875160637463263[195] = 0;
   out_8736875160637463263[196] = 0;
   out_8736875160637463263[197] = 0;
   out_8736875160637463263[198] = 0;
   out_8736875160637463263[199] = 0;
   out_8736875160637463263[200] = 0;
   out_8736875160637463263[201] = 0;
   out_8736875160637463263[202] = 0;
   out_8736875160637463263[203] = 0;
   out_8736875160637463263[204] = 0;
   out_8736875160637463263[205] = 0;
   out_8736875160637463263[206] = 0;
   out_8736875160637463263[207] = 0;
   out_8736875160637463263[208] = 0;
   out_8736875160637463263[209] = 1;
   out_8736875160637463263[210] = 0;
   out_8736875160637463263[211] = 0;
   out_8736875160637463263[212] = 0;
   out_8736875160637463263[213] = 0;
   out_8736875160637463263[214] = 0;
   out_8736875160637463263[215] = 0;
   out_8736875160637463263[216] = 0;
   out_8736875160637463263[217] = 0;
   out_8736875160637463263[218] = 0;
   out_8736875160637463263[219] = 0;
   out_8736875160637463263[220] = 0;
   out_8736875160637463263[221] = 0;
   out_8736875160637463263[222] = 0;
   out_8736875160637463263[223] = 0;
   out_8736875160637463263[224] = 0;
   out_8736875160637463263[225] = 0;
   out_8736875160637463263[226] = 0;
   out_8736875160637463263[227] = 0;
   out_8736875160637463263[228] = 1;
   out_8736875160637463263[229] = 0;
   out_8736875160637463263[230] = 0;
   out_8736875160637463263[231] = 0;
   out_8736875160637463263[232] = 0;
   out_8736875160637463263[233] = 0;
   out_8736875160637463263[234] = 0;
   out_8736875160637463263[235] = 0;
   out_8736875160637463263[236] = 0;
   out_8736875160637463263[237] = 0;
   out_8736875160637463263[238] = 0;
   out_8736875160637463263[239] = 0;
   out_8736875160637463263[240] = 0;
   out_8736875160637463263[241] = 0;
   out_8736875160637463263[242] = 0;
   out_8736875160637463263[243] = 0;
   out_8736875160637463263[244] = 0;
   out_8736875160637463263[245] = 0;
   out_8736875160637463263[246] = 0;
   out_8736875160637463263[247] = 1;
   out_8736875160637463263[248] = 0;
   out_8736875160637463263[249] = 0;
   out_8736875160637463263[250] = 0;
   out_8736875160637463263[251] = 0;
   out_8736875160637463263[252] = 0;
   out_8736875160637463263[253] = 0;
   out_8736875160637463263[254] = 0;
   out_8736875160637463263[255] = 0;
   out_8736875160637463263[256] = 0;
   out_8736875160637463263[257] = 0;
   out_8736875160637463263[258] = 0;
   out_8736875160637463263[259] = 0;
   out_8736875160637463263[260] = 0;
   out_8736875160637463263[261] = 0;
   out_8736875160637463263[262] = 0;
   out_8736875160637463263[263] = 0;
   out_8736875160637463263[264] = 0;
   out_8736875160637463263[265] = 0;
   out_8736875160637463263[266] = 1;
   out_8736875160637463263[267] = 0;
   out_8736875160637463263[268] = 0;
   out_8736875160637463263[269] = 0;
   out_8736875160637463263[270] = 0;
   out_8736875160637463263[271] = 0;
   out_8736875160637463263[272] = 0;
   out_8736875160637463263[273] = 0;
   out_8736875160637463263[274] = 0;
   out_8736875160637463263[275] = 0;
   out_8736875160637463263[276] = 0;
   out_8736875160637463263[277] = 0;
   out_8736875160637463263[278] = 0;
   out_8736875160637463263[279] = 0;
   out_8736875160637463263[280] = 0;
   out_8736875160637463263[281] = 0;
   out_8736875160637463263[282] = 0;
   out_8736875160637463263[283] = 0;
   out_8736875160637463263[284] = 0;
   out_8736875160637463263[285] = 1;
   out_8736875160637463263[286] = 0;
   out_8736875160637463263[287] = 0;
   out_8736875160637463263[288] = 0;
   out_8736875160637463263[289] = 0;
   out_8736875160637463263[290] = 0;
   out_8736875160637463263[291] = 0;
   out_8736875160637463263[292] = 0;
   out_8736875160637463263[293] = 0;
   out_8736875160637463263[294] = 0;
   out_8736875160637463263[295] = 0;
   out_8736875160637463263[296] = 0;
   out_8736875160637463263[297] = 0;
   out_8736875160637463263[298] = 0;
   out_8736875160637463263[299] = 0;
   out_8736875160637463263[300] = 0;
   out_8736875160637463263[301] = 0;
   out_8736875160637463263[302] = 0;
   out_8736875160637463263[303] = 0;
   out_8736875160637463263[304] = 1;
   out_8736875160637463263[305] = 0;
   out_8736875160637463263[306] = 0;
   out_8736875160637463263[307] = 0;
   out_8736875160637463263[308] = 0;
   out_8736875160637463263[309] = 0;
   out_8736875160637463263[310] = 0;
   out_8736875160637463263[311] = 0;
   out_8736875160637463263[312] = 0;
   out_8736875160637463263[313] = 0;
   out_8736875160637463263[314] = 0;
   out_8736875160637463263[315] = 0;
   out_8736875160637463263[316] = 0;
   out_8736875160637463263[317] = 0;
   out_8736875160637463263[318] = 0;
   out_8736875160637463263[319] = 0;
   out_8736875160637463263[320] = 0;
   out_8736875160637463263[321] = 0;
   out_8736875160637463263[322] = 0;
   out_8736875160637463263[323] = 1;
}
void h_4(double *state, double *unused, double *out_5158761943134929654) {
   out_5158761943134929654[0] = state[6] + state[9];
   out_5158761943134929654[1] = state[7] + state[10];
   out_5158761943134929654[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4082765935524626398) {
   out_4082765935524626398[0] = 0;
   out_4082765935524626398[1] = 0;
   out_4082765935524626398[2] = 0;
   out_4082765935524626398[3] = 0;
   out_4082765935524626398[4] = 0;
   out_4082765935524626398[5] = 0;
   out_4082765935524626398[6] = 1;
   out_4082765935524626398[7] = 0;
   out_4082765935524626398[8] = 0;
   out_4082765935524626398[9] = 1;
   out_4082765935524626398[10] = 0;
   out_4082765935524626398[11] = 0;
   out_4082765935524626398[12] = 0;
   out_4082765935524626398[13] = 0;
   out_4082765935524626398[14] = 0;
   out_4082765935524626398[15] = 0;
   out_4082765935524626398[16] = 0;
   out_4082765935524626398[17] = 0;
   out_4082765935524626398[18] = 0;
   out_4082765935524626398[19] = 0;
   out_4082765935524626398[20] = 0;
   out_4082765935524626398[21] = 0;
   out_4082765935524626398[22] = 0;
   out_4082765935524626398[23] = 0;
   out_4082765935524626398[24] = 0;
   out_4082765935524626398[25] = 1;
   out_4082765935524626398[26] = 0;
   out_4082765935524626398[27] = 0;
   out_4082765935524626398[28] = 1;
   out_4082765935524626398[29] = 0;
   out_4082765935524626398[30] = 0;
   out_4082765935524626398[31] = 0;
   out_4082765935524626398[32] = 0;
   out_4082765935524626398[33] = 0;
   out_4082765935524626398[34] = 0;
   out_4082765935524626398[35] = 0;
   out_4082765935524626398[36] = 0;
   out_4082765935524626398[37] = 0;
   out_4082765935524626398[38] = 0;
   out_4082765935524626398[39] = 0;
   out_4082765935524626398[40] = 0;
   out_4082765935524626398[41] = 0;
   out_4082765935524626398[42] = 0;
   out_4082765935524626398[43] = 0;
   out_4082765935524626398[44] = 1;
   out_4082765935524626398[45] = 0;
   out_4082765935524626398[46] = 0;
   out_4082765935524626398[47] = 1;
   out_4082765935524626398[48] = 0;
   out_4082765935524626398[49] = 0;
   out_4082765935524626398[50] = 0;
   out_4082765935524626398[51] = 0;
   out_4082765935524626398[52] = 0;
   out_4082765935524626398[53] = 0;
}
void h_10(double *state, double *unused, double *out_563005185308758885) {
   out_563005185308758885[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_563005185308758885[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_563005185308758885[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7993288058010589722) {
   out_7993288058010589722[0] = 0;
   out_7993288058010589722[1] = 9.8100000000000005*cos(state[1]);
   out_7993288058010589722[2] = 0;
   out_7993288058010589722[3] = 0;
   out_7993288058010589722[4] = -state[8];
   out_7993288058010589722[5] = state[7];
   out_7993288058010589722[6] = 0;
   out_7993288058010589722[7] = state[5];
   out_7993288058010589722[8] = -state[4];
   out_7993288058010589722[9] = 0;
   out_7993288058010589722[10] = 0;
   out_7993288058010589722[11] = 0;
   out_7993288058010589722[12] = 1;
   out_7993288058010589722[13] = 0;
   out_7993288058010589722[14] = 0;
   out_7993288058010589722[15] = 1;
   out_7993288058010589722[16] = 0;
   out_7993288058010589722[17] = 0;
   out_7993288058010589722[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7993288058010589722[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7993288058010589722[20] = 0;
   out_7993288058010589722[21] = state[8];
   out_7993288058010589722[22] = 0;
   out_7993288058010589722[23] = -state[6];
   out_7993288058010589722[24] = -state[5];
   out_7993288058010589722[25] = 0;
   out_7993288058010589722[26] = state[3];
   out_7993288058010589722[27] = 0;
   out_7993288058010589722[28] = 0;
   out_7993288058010589722[29] = 0;
   out_7993288058010589722[30] = 0;
   out_7993288058010589722[31] = 1;
   out_7993288058010589722[32] = 0;
   out_7993288058010589722[33] = 0;
   out_7993288058010589722[34] = 1;
   out_7993288058010589722[35] = 0;
   out_7993288058010589722[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7993288058010589722[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7993288058010589722[38] = 0;
   out_7993288058010589722[39] = -state[7];
   out_7993288058010589722[40] = state[6];
   out_7993288058010589722[41] = 0;
   out_7993288058010589722[42] = state[4];
   out_7993288058010589722[43] = -state[3];
   out_7993288058010589722[44] = 0;
   out_7993288058010589722[45] = 0;
   out_7993288058010589722[46] = 0;
   out_7993288058010589722[47] = 0;
   out_7993288058010589722[48] = 0;
   out_7993288058010589722[49] = 0;
   out_7993288058010589722[50] = 1;
   out_7993288058010589722[51] = 0;
   out_7993288058010589722[52] = 0;
   out_7993288058010589722[53] = 1;
}
void h_13(double *state, double *unused, double *out_1191809301965979441) {
   out_1191809301965979441[0] = state[3];
   out_1191809301965979441[1] = state[4];
   out_1191809301965979441[2] = state[5];
}
void H_13(double *state, double *unused, double *out_7295039760856959199) {
   out_7295039760856959199[0] = 0;
   out_7295039760856959199[1] = 0;
   out_7295039760856959199[2] = 0;
   out_7295039760856959199[3] = 1;
   out_7295039760856959199[4] = 0;
   out_7295039760856959199[5] = 0;
   out_7295039760856959199[6] = 0;
   out_7295039760856959199[7] = 0;
   out_7295039760856959199[8] = 0;
   out_7295039760856959199[9] = 0;
   out_7295039760856959199[10] = 0;
   out_7295039760856959199[11] = 0;
   out_7295039760856959199[12] = 0;
   out_7295039760856959199[13] = 0;
   out_7295039760856959199[14] = 0;
   out_7295039760856959199[15] = 0;
   out_7295039760856959199[16] = 0;
   out_7295039760856959199[17] = 0;
   out_7295039760856959199[18] = 0;
   out_7295039760856959199[19] = 0;
   out_7295039760856959199[20] = 0;
   out_7295039760856959199[21] = 0;
   out_7295039760856959199[22] = 1;
   out_7295039760856959199[23] = 0;
   out_7295039760856959199[24] = 0;
   out_7295039760856959199[25] = 0;
   out_7295039760856959199[26] = 0;
   out_7295039760856959199[27] = 0;
   out_7295039760856959199[28] = 0;
   out_7295039760856959199[29] = 0;
   out_7295039760856959199[30] = 0;
   out_7295039760856959199[31] = 0;
   out_7295039760856959199[32] = 0;
   out_7295039760856959199[33] = 0;
   out_7295039760856959199[34] = 0;
   out_7295039760856959199[35] = 0;
   out_7295039760856959199[36] = 0;
   out_7295039760856959199[37] = 0;
   out_7295039760856959199[38] = 0;
   out_7295039760856959199[39] = 0;
   out_7295039760856959199[40] = 0;
   out_7295039760856959199[41] = 1;
   out_7295039760856959199[42] = 0;
   out_7295039760856959199[43] = 0;
   out_7295039760856959199[44] = 0;
   out_7295039760856959199[45] = 0;
   out_7295039760856959199[46] = 0;
   out_7295039760856959199[47] = 0;
   out_7295039760856959199[48] = 0;
   out_7295039760856959199[49] = 0;
   out_7295039760856959199[50] = 0;
   out_7295039760856959199[51] = 0;
   out_7295039760856959199[52] = 0;
   out_7295039760856959199[53] = 0;
}
void h_14(double *state, double *unused, double *out_8501358265546490714) {
   out_8501358265546490714[0] = state[6];
   out_8501358265546490714[1] = state[7];
   out_8501358265546490714[2] = state[8];
}
void H_14(double *state, double *unused, double *out_999977503229254102) {
   out_999977503229254102[0] = 0;
   out_999977503229254102[1] = 0;
   out_999977503229254102[2] = 0;
   out_999977503229254102[3] = 0;
   out_999977503229254102[4] = 0;
   out_999977503229254102[5] = 0;
   out_999977503229254102[6] = 1;
   out_999977503229254102[7] = 0;
   out_999977503229254102[8] = 0;
   out_999977503229254102[9] = 0;
   out_999977503229254102[10] = 0;
   out_999977503229254102[11] = 0;
   out_999977503229254102[12] = 0;
   out_999977503229254102[13] = 0;
   out_999977503229254102[14] = 0;
   out_999977503229254102[15] = 0;
   out_999977503229254102[16] = 0;
   out_999977503229254102[17] = 0;
   out_999977503229254102[18] = 0;
   out_999977503229254102[19] = 0;
   out_999977503229254102[20] = 0;
   out_999977503229254102[21] = 0;
   out_999977503229254102[22] = 0;
   out_999977503229254102[23] = 0;
   out_999977503229254102[24] = 0;
   out_999977503229254102[25] = 1;
   out_999977503229254102[26] = 0;
   out_999977503229254102[27] = 0;
   out_999977503229254102[28] = 0;
   out_999977503229254102[29] = 0;
   out_999977503229254102[30] = 0;
   out_999977503229254102[31] = 0;
   out_999977503229254102[32] = 0;
   out_999977503229254102[33] = 0;
   out_999977503229254102[34] = 0;
   out_999977503229254102[35] = 0;
   out_999977503229254102[36] = 0;
   out_999977503229254102[37] = 0;
   out_999977503229254102[38] = 0;
   out_999977503229254102[39] = 0;
   out_999977503229254102[40] = 0;
   out_999977503229254102[41] = 0;
   out_999977503229254102[42] = 0;
   out_999977503229254102[43] = 0;
   out_999977503229254102[44] = 1;
   out_999977503229254102[45] = 0;
   out_999977503229254102[46] = 0;
   out_999977503229254102[47] = 0;
   out_999977503229254102[48] = 0;
   out_999977503229254102[49] = 0;
   out_999977503229254102[50] = 0;
   out_999977503229254102[51] = 0;
   out_999977503229254102[52] = 0;
   out_999977503229254102[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5206974560936582462) {
  err_fun(nom_x, delta_x, out_5206974560936582462);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8580851081509816390) {
  inv_err_fun(nom_x, true_x, out_8580851081509816390);
}
void pose_H_mod_fun(double *state, double *out_310958725680718826) {
  H_mod_fun(state, out_310958725680718826);
}
void pose_f_fun(double *state, double dt, double *out_8333876756213369009) {
  f_fun(state,  dt, out_8333876756213369009);
}
void pose_F_fun(double *state, double dt, double *out_8736875160637463263) {
  F_fun(state,  dt, out_8736875160637463263);
}
void pose_h_4(double *state, double *unused, double *out_5158761943134929654) {
  h_4(state, unused, out_5158761943134929654);
}
void pose_H_4(double *state, double *unused, double *out_4082765935524626398) {
  H_4(state, unused, out_4082765935524626398);
}
void pose_h_10(double *state, double *unused, double *out_563005185308758885) {
  h_10(state, unused, out_563005185308758885);
}
void pose_H_10(double *state, double *unused, double *out_7993288058010589722) {
  H_10(state, unused, out_7993288058010589722);
}
void pose_h_13(double *state, double *unused, double *out_1191809301965979441) {
  h_13(state, unused, out_1191809301965979441);
}
void pose_H_13(double *state, double *unused, double *out_7295039760856959199) {
  H_13(state, unused, out_7295039760856959199);
}
void pose_h_14(double *state, double *unused, double *out_8501358265546490714) {
  h_14(state, unused, out_8501358265546490714);
}
void pose_H_14(double *state, double *unused, double *out_999977503229254102) {
  H_14(state, unused, out_999977503229254102);
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
