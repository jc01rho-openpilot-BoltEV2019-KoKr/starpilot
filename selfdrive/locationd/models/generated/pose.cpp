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
void err_fun(double *nom_x, double *delta_x, double *out_7365448194845582757) {
   out_7365448194845582757[0] = delta_x[0] + nom_x[0];
   out_7365448194845582757[1] = delta_x[1] + nom_x[1];
   out_7365448194845582757[2] = delta_x[2] + nom_x[2];
   out_7365448194845582757[3] = delta_x[3] + nom_x[3];
   out_7365448194845582757[4] = delta_x[4] + nom_x[4];
   out_7365448194845582757[5] = delta_x[5] + nom_x[5];
   out_7365448194845582757[6] = delta_x[6] + nom_x[6];
   out_7365448194845582757[7] = delta_x[7] + nom_x[7];
   out_7365448194845582757[8] = delta_x[8] + nom_x[8];
   out_7365448194845582757[9] = delta_x[9] + nom_x[9];
   out_7365448194845582757[10] = delta_x[10] + nom_x[10];
   out_7365448194845582757[11] = delta_x[11] + nom_x[11];
   out_7365448194845582757[12] = delta_x[12] + nom_x[12];
   out_7365448194845582757[13] = delta_x[13] + nom_x[13];
   out_7365448194845582757[14] = delta_x[14] + nom_x[14];
   out_7365448194845582757[15] = delta_x[15] + nom_x[15];
   out_7365448194845582757[16] = delta_x[16] + nom_x[16];
   out_7365448194845582757[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1967800537697910635) {
   out_1967800537697910635[0] = -nom_x[0] + true_x[0];
   out_1967800537697910635[1] = -nom_x[1] + true_x[1];
   out_1967800537697910635[2] = -nom_x[2] + true_x[2];
   out_1967800537697910635[3] = -nom_x[3] + true_x[3];
   out_1967800537697910635[4] = -nom_x[4] + true_x[4];
   out_1967800537697910635[5] = -nom_x[5] + true_x[5];
   out_1967800537697910635[6] = -nom_x[6] + true_x[6];
   out_1967800537697910635[7] = -nom_x[7] + true_x[7];
   out_1967800537697910635[8] = -nom_x[8] + true_x[8];
   out_1967800537697910635[9] = -nom_x[9] + true_x[9];
   out_1967800537697910635[10] = -nom_x[10] + true_x[10];
   out_1967800537697910635[11] = -nom_x[11] + true_x[11];
   out_1967800537697910635[12] = -nom_x[12] + true_x[12];
   out_1967800537697910635[13] = -nom_x[13] + true_x[13];
   out_1967800537697910635[14] = -nom_x[14] + true_x[14];
   out_1967800537697910635[15] = -nom_x[15] + true_x[15];
   out_1967800537697910635[16] = -nom_x[16] + true_x[16];
   out_1967800537697910635[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_8390959249454907977) {
   out_8390959249454907977[0] = 1.0;
   out_8390959249454907977[1] = 0.0;
   out_8390959249454907977[2] = 0.0;
   out_8390959249454907977[3] = 0.0;
   out_8390959249454907977[4] = 0.0;
   out_8390959249454907977[5] = 0.0;
   out_8390959249454907977[6] = 0.0;
   out_8390959249454907977[7] = 0.0;
   out_8390959249454907977[8] = 0.0;
   out_8390959249454907977[9] = 0.0;
   out_8390959249454907977[10] = 0.0;
   out_8390959249454907977[11] = 0.0;
   out_8390959249454907977[12] = 0.0;
   out_8390959249454907977[13] = 0.0;
   out_8390959249454907977[14] = 0.0;
   out_8390959249454907977[15] = 0.0;
   out_8390959249454907977[16] = 0.0;
   out_8390959249454907977[17] = 0.0;
   out_8390959249454907977[18] = 0.0;
   out_8390959249454907977[19] = 1.0;
   out_8390959249454907977[20] = 0.0;
   out_8390959249454907977[21] = 0.0;
   out_8390959249454907977[22] = 0.0;
   out_8390959249454907977[23] = 0.0;
   out_8390959249454907977[24] = 0.0;
   out_8390959249454907977[25] = 0.0;
   out_8390959249454907977[26] = 0.0;
   out_8390959249454907977[27] = 0.0;
   out_8390959249454907977[28] = 0.0;
   out_8390959249454907977[29] = 0.0;
   out_8390959249454907977[30] = 0.0;
   out_8390959249454907977[31] = 0.0;
   out_8390959249454907977[32] = 0.0;
   out_8390959249454907977[33] = 0.0;
   out_8390959249454907977[34] = 0.0;
   out_8390959249454907977[35] = 0.0;
   out_8390959249454907977[36] = 0.0;
   out_8390959249454907977[37] = 0.0;
   out_8390959249454907977[38] = 1.0;
   out_8390959249454907977[39] = 0.0;
   out_8390959249454907977[40] = 0.0;
   out_8390959249454907977[41] = 0.0;
   out_8390959249454907977[42] = 0.0;
   out_8390959249454907977[43] = 0.0;
   out_8390959249454907977[44] = 0.0;
   out_8390959249454907977[45] = 0.0;
   out_8390959249454907977[46] = 0.0;
   out_8390959249454907977[47] = 0.0;
   out_8390959249454907977[48] = 0.0;
   out_8390959249454907977[49] = 0.0;
   out_8390959249454907977[50] = 0.0;
   out_8390959249454907977[51] = 0.0;
   out_8390959249454907977[52] = 0.0;
   out_8390959249454907977[53] = 0.0;
   out_8390959249454907977[54] = 0.0;
   out_8390959249454907977[55] = 0.0;
   out_8390959249454907977[56] = 0.0;
   out_8390959249454907977[57] = 1.0;
   out_8390959249454907977[58] = 0.0;
   out_8390959249454907977[59] = 0.0;
   out_8390959249454907977[60] = 0.0;
   out_8390959249454907977[61] = 0.0;
   out_8390959249454907977[62] = 0.0;
   out_8390959249454907977[63] = 0.0;
   out_8390959249454907977[64] = 0.0;
   out_8390959249454907977[65] = 0.0;
   out_8390959249454907977[66] = 0.0;
   out_8390959249454907977[67] = 0.0;
   out_8390959249454907977[68] = 0.0;
   out_8390959249454907977[69] = 0.0;
   out_8390959249454907977[70] = 0.0;
   out_8390959249454907977[71] = 0.0;
   out_8390959249454907977[72] = 0.0;
   out_8390959249454907977[73] = 0.0;
   out_8390959249454907977[74] = 0.0;
   out_8390959249454907977[75] = 0.0;
   out_8390959249454907977[76] = 1.0;
   out_8390959249454907977[77] = 0.0;
   out_8390959249454907977[78] = 0.0;
   out_8390959249454907977[79] = 0.0;
   out_8390959249454907977[80] = 0.0;
   out_8390959249454907977[81] = 0.0;
   out_8390959249454907977[82] = 0.0;
   out_8390959249454907977[83] = 0.0;
   out_8390959249454907977[84] = 0.0;
   out_8390959249454907977[85] = 0.0;
   out_8390959249454907977[86] = 0.0;
   out_8390959249454907977[87] = 0.0;
   out_8390959249454907977[88] = 0.0;
   out_8390959249454907977[89] = 0.0;
   out_8390959249454907977[90] = 0.0;
   out_8390959249454907977[91] = 0.0;
   out_8390959249454907977[92] = 0.0;
   out_8390959249454907977[93] = 0.0;
   out_8390959249454907977[94] = 0.0;
   out_8390959249454907977[95] = 1.0;
   out_8390959249454907977[96] = 0.0;
   out_8390959249454907977[97] = 0.0;
   out_8390959249454907977[98] = 0.0;
   out_8390959249454907977[99] = 0.0;
   out_8390959249454907977[100] = 0.0;
   out_8390959249454907977[101] = 0.0;
   out_8390959249454907977[102] = 0.0;
   out_8390959249454907977[103] = 0.0;
   out_8390959249454907977[104] = 0.0;
   out_8390959249454907977[105] = 0.0;
   out_8390959249454907977[106] = 0.0;
   out_8390959249454907977[107] = 0.0;
   out_8390959249454907977[108] = 0.0;
   out_8390959249454907977[109] = 0.0;
   out_8390959249454907977[110] = 0.0;
   out_8390959249454907977[111] = 0.0;
   out_8390959249454907977[112] = 0.0;
   out_8390959249454907977[113] = 0.0;
   out_8390959249454907977[114] = 1.0;
   out_8390959249454907977[115] = 0.0;
   out_8390959249454907977[116] = 0.0;
   out_8390959249454907977[117] = 0.0;
   out_8390959249454907977[118] = 0.0;
   out_8390959249454907977[119] = 0.0;
   out_8390959249454907977[120] = 0.0;
   out_8390959249454907977[121] = 0.0;
   out_8390959249454907977[122] = 0.0;
   out_8390959249454907977[123] = 0.0;
   out_8390959249454907977[124] = 0.0;
   out_8390959249454907977[125] = 0.0;
   out_8390959249454907977[126] = 0.0;
   out_8390959249454907977[127] = 0.0;
   out_8390959249454907977[128] = 0.0;
   out_8390959249454907977[129] = 0.0;
   out_8390959249454907977[130] = 0.0;
   out_8390959249454907977[131] = 0.0;
   out_8390959249454907977[132] = 0.0;
   out_8390959249454907977[133] = 1.0;
   out_8390959249454907977[134] = 0.0;
   out_8390959249454907977[135] = 0.0;
   out_8390959249454907977[136] = 0.0;
   out_8390959249454907977[137] = 0.0;
   out_8390959249454907977[138] = 0.0;
   out_8390959249454907977[139] = 0.0;
   out_8390959249454907977[140] = 0.0;
   out_8390959249454907977[141] = 0.0;
   out_8390959249454907977[142] = 0.0;
   out_8390959249454907977[143] = 0.0;
   out_8390959249454907977[144] = 0.0;
   out_8390959249454907977[145] = 0.0;
   out_8390959249454907977[146] = 0.0;
   out_8390959249454907977[147] = 0.0;
   out_8390959249454907977[148] = 0.0;
   out_8390959249454907977[149] = 0.0;
   out_8390959249454907977[150] = 0.0;
   out_8390959249454907977[151] = 0.0;
   out_8390959249454907977[152] = 1.0;
   out_8390959249454907977[153] = 0.0;
   out_8390959249454907977[154] = 0.0;
   out_8390959249454907977[155] = 0.0;
   out_8390959249454907977[156] = 0.0;
   out_8390959249454907977[157] = 0.0;
   out_8390959249454907977[158] = 0.0;
   out_8390959249454907977[159] = 0.0;
   out_8390959249454907977[160] = 0.0;
   out_8390959249454907977[161] = 0.0;
   out_8390959249454907977[162] = 0.0;
   out_8390959249454907977[163] = 0.0;
   out_8390959249454907977[164] = 0.0;
   out_8390959249454907977[165] = 0.0;
   out_8390959249454907977[166] = 0.0;
   out_8390959249454907977[167] = 0.0;
   out_8390959249454907977[168] = 0.0;
   out_8390959249454907977[169] = 0.0;
   out_8390959249454907977[170] = 0.0;
   out_8390959249454907977[171] = 1.0;
   out_8390959249454907977[172] = 0.0;
   out_8390959249454907977[173] = 0.0;
   out_8390959249454907977[174] = 0.0;
   out_8390959249454907977[175] = 0.0;
   out_8390959249454907977[176] = 0.0;
   out_8390959249454907977[177] = 0.0;
   out_8390959249454907977[178] = 0.0;
   out_8390959249454907977[179] = 0.0;
   out_8390959249454907977[180] = 0.0;
   out_8390959249454907977[181] = 0.0;
   out_8390959249454907977[182] = 0.0;
   out_8390959249454907977[183] = 0.0;
   out_8390959249454907977[184] = 0.0;
   out_8390959249454907977[185] = 0.0;
   out_8390959249454907977[186] = 0.0;
   out_8390959249454907977[187] = 0.0;
   out_8390959249454907977[188] = 0.0;
   out_8390959249454907977[189] = 0.0;
   out_8390959249454907977[190] = 1.0;
   out_8390959249454907977[191] = 0.0;
   out_8390959249454907977[192] = 0.0;
   out_8390959249454907977[193] = 0.0;
   out_8390959249454907977[194] = 0.0;
   out_8390959249454907977[195] = 0.0;
   out_8390959249454907977[196] = 0.0;
   out_8390959249454907977[197] = 0.0;
   out_8390959249454907977[198] = 0.0;
   out_8390959249454907977[199] = 0.0;
   out_8390959249454907977[200] = 0.0;
   out_8390959249454907977[201] = 0.0;
   out_8390959249454907977[202] = 0.0;
   out_8390959249454907977[203] = 0.0;
   out_8390959249454907977[204] = 0.0;
   out_8390959249454907977[205] = 0.0;
   out_8390959249454907977[206] = 0.0;
   out_8390959249454907977[207] = 0.0;
   out_8390959249454907977[208] = 0.0;
   out_8390959249454907977[209] = 1.0;
   out_8390959249454907977[210] = 0.0;
   out_8390959249454907977[211] = 0.0;
   out_8390959249454907977[212] = 0.0;
   out_8390959249454907977[213] = 0.0;
   out_8390959249454907977[214] = 0.0;
   out_8390959249454907977[215] = 0.0;
   out_8390959249454907977[216] = 0.0;
   out_8390959249454907977[217] = 0.0;
   out_8390959249454907977[218] = 0.0;
   out_8390959249454907977[219] = 0.0;
   out_8390959249454907977[220] = 0.0;
   out_8390959249454907977[221] = 0.0;
   out_8390959249454907977[222] = 0.0;
   out_8390959249454907977[223] = 0.0;
   out_8390959249454907977[224] = 0.0;
   out_8390959249454907977[225] = 0.0;
   out_8390959249454907977[226] = 0.0;
   out_8390959249454907977[227] = 0.0;
   out_8390959249454907977[228] = 1.0;
   out_8390959249454907977[229] = 0.0;
   out_8390959249454907977[230] = 0.0;
   out_8390959249454907977[231] = 0.0;
   out_8390959249454907977[232] = 0.0;
   out_8390959249454907977[233] = 0.0;
   out_8390959249454907977[234] = 0.0;
   out_8390959249454907977[235] = 0.0;
   out_8390959249454907977[236] = 0.0;
   out_8390959249454907977[237] = 0.0;
   out_8390959249454907977[238] = 0.0;
   out_8390959249454907977[239] = 0.0;
   out_8390959249454907977[240] = 0.0;
   out_8390959249454907977[241] = 0.0;
   out_8390959249454907977[242] = 0.0;
   out_8390959249454907977[243] = 0.0;
   out_8390959249454907977[244] = 0.0;
   out_8390959249454907977[245] = 0.0;
   out_8390959249454907977[246] = 0.0;
   out_8390959249454907977[247] = 1.0;
   out_8390959249454907977[248] = 0.0;
   out_8390959249454907977[249] = 0.0;
   out_8390959249454907977[250] = 0.0;
   out_8390959249454907977[251] = 0.0;
   out_8390959249454907977[252] = 0.0;
   out_8390959249454907977[253] = 0.0;
   out_8390959249454907977[254] = 0.0;
   out_8390959249454907977[255] = 0.0;
   out_8390959249454907977[256] = 0.0;
   out_8390959249454907977[257] = 0.0;
   out_8390959249454907977[258] = 0.0;
   out_8390959249454907977[259] = 0.0;
   out_8390959249454907977[260] = 0.0;
   out_8390959249454907977[261] = 0.0;
   out_8390959249454907977[262] = 0.0;
   out_8390959249454907977[263] = 0.0;
   out_8390959249454907977[264] = 0.0;
   out_8390959249454907977[265] = 0.0;
   out_8390959249454907977[266] = 1.0;
   out_8390959249454907977[267] = 0.0;
   out_8390959249454907977[268] = 0.0;
   out_8390959249454907977[269] = 0.0;
   out_8390959249454907977[270] = 0.0;
   out_8390959249454907977[271] = 0.0;
   out_8390959249454907977[272] = 0.0;
   out_8390959249454907977[273] = 0.0;
   out_8390959249454907977[274] = 0.0;
   out_8390959249454907977[275] = 0.0;
   out_8390959249454907977[276] = 0.0;
   out_8390959249454907977[277] = 0.0;
   out_8390959249454907977[278] = 0.0;
   out_8390959249454907977[279] = 0.0;
   out_8390959249454907977[280] = 0.0;
   out_8390959249454907977[281] = 0.0;
   out_8390959249454907977[282] = 0.0;
   out_8390959249454907977[283] = 0.0;
   out_8390959249454907977[284] = 0.0;
   out_8390959249454907977[285] = 1.0;
   out_8390959249454907977[286] = 0.0;
   out_8390959249454907977[287] = 0.0;
   out_8390959249454907977[288] = 0.0;
   out_8390959249454907977[289] = 0.0;
   out_8390959249454907977[290] = 0.0;
   out_8390959249454907977[291] = 0.0;
   out_8390959249454907977[292] = 0.0;
   out_8390959249454907977[293] = 0.0;
   out_8390959249454907977[294] = 0.0;
   out_8390959249454907977[295] = 0.0;
   out_8390959249454907977[296] = 0.0;
   out_8390959249454907977[297] = 0.0;
   out_8390959249454907977[298] = 0.0;
   out_8390959249454907977[299] = 0.0;
   out_8390959249454907977[300] = 0.0;
   out_8390959249454907977[301] = 0.0;
   out_8390959249454907977[302] = 0.0;
   out_8390959249454907977[303] = 0.0;
   out_8390959249454907977[304] = 1.0;
   out_8390959249454907977[305] = 0.0;
   out_8390959249454907977[306] = 0.0;
   out_8390959249454907977[307] = 0.0;
   out_8390959249454907977[308] = 0.0;
   out_8390959249454907977[309] = 0.0;
   out_8390959249454907977[310] = 0.0;
   out_8390959249454907977[311] = 0.0;
   out_8390959249454907977[312] = 0.0;
   out_8390959249454907977[313] = 0.0;
   out_8390959249454907977[314] = 0.0;
   out_8390959249454907977[315] = 0.0;
   out_8390959249454907977[316] = 0.0;
   out_8390959249454907977[317] = 0.0;
   out_8390959249454907977[318] = 0.0;
   out_8390959249454907977[319] = 0.0;
   out_8390959249454907977[320] = 0.0;
   out_8390959249454907977[321] = 0.0;
   out_8390959249454907977[322] = 0.0;
   out_8390959249454907977[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_9042230065077868228) {
   out_9042230065077868228[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_9042230065077868228[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_9042230065077868228[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_9042230065077868228[3] = dt*state[12] + state[3];
   out_9042230065077868228[4] = dt*state[13] + state[4];
   out_9042230065077868228[5] = dt*state[14] + state[5];
   out_9042230065077868228[6] = state[6];
   out_9042230065077868228[7] = state[7];
   out_9042230065077868228[8] = state[8];
   out_9042230065077868228[9] = state[9];
   out_9042230065077868228[10] = state[10];
   out_9042230065077868228[11] = state[11];
   out_9042230065077868228[12] = state[12];
   out_9042230065077868228[13] = state[13];
   out_9042230065077868228[14] = state[14];
   out_9042230065077868228[15] = state[15];
   out_9042230065077868228[16] = state[16];
   out_9042230065077868228[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3211704972733304042) {
   out_3211704972733304042[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3211704972733304042[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3211704972733304042[2] = 0;
   out_3211704972733304042[3] = 0;
   out_3211704972733304042[4] = 0;
   out_3211704972733304042[5] = 0;
   out_3211704972733304042[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3211704972733304042[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3211704972733304042[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3211704972733304042[9] = 0;
   out_3211704972733304042[10] = 0;
   out_3211704972733304042[11] = 0;
   out_3211704972733304042[12] = 0;
   out_3211704972733304042[13] = 0;
   out_3211704972733304042[14] = 0;
   out_3211704972733304042[15] = 0;
   out_3211704972733304042[16] = 0;
   out_3211704972733304042[17] = 0;
   out_3211704972733304042[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3211704972733304042[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3211704972733304042[20] = 0;
   out_3211704972733304042[21] = 0;
   out_3211704972733304042[22] = 0;
   out_3211704972733304042[23] = 0;
   out_3211704972733304042[24] = 0;
   out_3211704972733304042[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3211704972733304042[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3211704972733304042[27] = 0;
   out_3211704972733304042[28] = 0;
   out_3211704972733304042[29] = 0;
   out_3211704972733304042[30] = 0;
   out_3211704972733304042[31] = 0;
   out_3211704972733304042[32] = 0;
   out_3211704972733304042[33] = 0;
   out_3211704972733304042[34] = 0;
   out_3211704972733304042[35] = 0;
   out_3211704972733304042[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3211704972733304042[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3211704972733304042[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3211704972733304042[39] = 0;
   out_3211704972733304042[40] = 0;
   out_3211704972733304042[41] = 0;
   out_3211704972733304042[42] = 0;
   out_3211704972733304042[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3211704972733304042[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3211704972733304042[45] = 0;
   out_3211704972733304042[46] = 0;
   out_3211704972733304042[47] = 0;
   out_3211704972733304042[48] = 0;
   out_3211704972733304042[49] = 0;
   out_3211704972733304042[50] = 0;
   out_3211704972733304042[51] = 0;
   out_3211704972733304042[52] = 0;
   out_3211704972733304042[53] = 0;
   out_3211704972733304042[54] = 0;
   out_3211704972733304042[55] = 0;
   out_3211704972733304042[56] = 0;
   out_3211704972733304042[57] = 1;
   out_3211704972733304042[58] = 0;
   out_3211704972733304042[59] = 0;
   out_3211704972733304042[60] = 0;
   out_3211704972733304042[61] = 0;
   out_3211704972733304042[62] = 0;
   out_3211704972733304042[63] = 0;
   out_3211704972733304042[64] = 0;
   out_3211704972733304042[65] = 0;
   out_3211704972733304042[66] = dt;
   out_3211704972733304042[67] = 0;
   out_3211704972733304042[68] = 0;
   out_3211704972733304042[69] = 0;
   out_3211704972733304042[70] = 0;
   out_3211704972733304042[71] = 0;
   out_3211704972733304042[72] = 0;
   out_3211704972733304042[73] = 0;
   out_3211704972733304042[74] = 0;
   out_3211704972733304042[75] = 0;
   out_3211704972733304042[76] = 1;
   out_3211704972733304042[77] = 0;
   out_3211704972733304042[78] = 0;
   out_3211704972733304042[79] = 0;
   out_3211704972733304042[80] = 0;
   out_3211704972733304042[81] = 0;
   out_3211704972733304042[82] = 0;
   out_3211704972733304042[83] = 0;
   out_3211704972733304042[84] = 0;
   out_3211704972733304042[85] = dt;
   out_3211704972733304042[86] = 0;
   out_3211704972733304042[87] = 0;
   out_3211704972733304042[88] = 0;
   out_3211704972733304042[89] = 0;
   out_3211704972733304042[90] = 0;
   out_3211704972733304042[91] = 0;
   out_3211704972733304042[92] = 0;
   out_3211704972733304042[93] = 0;
   out_3211704972733304042[94] = 0;
   out_3211704972733304042[95] = 1;
   out_3211704972733304042[96] = 0;
   out_3211704972733304042[97] = 0;
   out_3211704972733304042[98] = 0;
   out_3211704972733304042[99] = 0;
   out_3211704972733304042[100] = 0;
   out_3211704972733304042[101] = 0;
   out_3211704972733304042[102] = 0;
   out_3211704972733304042[103] = 0;
   out_3211704972733304042[104] = dt;
   out_3211704972733304042[105] = 0;
   out_3211704972733304042[106] = 0;
   out_3211704972733304042[107] = 0;
   out_3211704972733304042[108] = 0;
   out_3211704972733304042[109] = 0;
   out_3211704972733304042[110] = 0;
   out_3211704972733304042[111] = 0;
   out_3211704972733304042[112] = 0;
   out_3211704972733304042[113] = 0;
   out_3211704972733304042[114] = 1;
   out_3211704972733304042[115] = 0;
   out_3211704972733304042[116] = 0;
   out_3211704972733304042[117] = 0;
   out_3211704972733304042[118] = 0;
   out_3211704972733304042[119] = 0;
   out_3211704972733304042[120] = 0;
   out_3211704972733304042[121] = 0;
   out_3211704972733304042[122] = 0;
   out_3211704972733304042[123] = 0;
   out_3211704972733304042[124] = 0;
   out_3211704972733304042[125] = 0;
   out_3211704972733304042[126] = 0;
   out_3211704972733304042[127] = 0;
   out_3211704972733304042[128] = 0;
   out_3211704972733304042[129] = 0;
   out_3211704972733304042[130] = 0;
   out_3211704972733304042[131] = 0;
   out_3211704972733304042[132] = 0;
   out_3211704972733304042[133] = 1;
   out_3211704972733304042[134] = 0;
   out_3211704972733304042[135] = 0;
   out_3211704972733304042[136] = 0;
   out_3211704972733304042[137] = 0;
   out_3211704972733304042[138] = 0;
   out_3211704972733304042[139] = 0;
   out_3211704972733304042[140] = 0;
   out_3211704972733304042[141] = 0;
   out_3211704972733304042[142] = 0;
   out_3211704972733304042[143] = 0;
   out_3211704972733304042[144] = 0;
   out_3211704972733304042[145] = 0;
   out_3211704972733304042[146] = 0;
   out_3211704972733304042[147] = 0;
   out_3211704972733304042[148] = 0;
   out_3211704972733304042[149] = 0;
   out_3211704972733304042[150] = 0;
   out_3211704972733304042[151] = 0;
   out_3211704972733304042[152] = 1;
   out_3211704972733304042[153] = 0;
   out_3211704972733304042[154] = 0;
   out_3211704972733304042[155] = 0;
   out_3211704972733304042[156] = 0;
   out_3211704972733304042[157] = 0;
   out_3211704972733304042[158] = 0;
   out_3211704972733304042[159] = 0;
   out_3211704972733304042[160] = 0;
   out_3211704972733304042[161] = 0;
   out_3211704972733304042[162] = 0;
   out_3211704972733304042[163] = 0;
   out_3211704972733304042[164] = 0;
   out_3211704972733304042[165] = 0;
   out_3211704972733304042[166] = 0;
   out_3211704972733304042[167] = 0;
   out_3211704972733304042[168] = 0;
   out_3211704972733304042[169] = 0;
   out_3211704972733304042[170] = 0;
   out_3211704972733304042[171] = 1;
   out_3211704972733304042[172] = 0;
   out_3211704972733304042[173] = 0;
   out_3211704972733304042[174] = 0;
   out_3211704972733304042[175] = 0;
   out_3211704972733304042[176] = 0;
   out_3211704972733304042[177] = 0;
   out_3211704972733304042[178] = 0;
   out_3211704972733304042[179] = 0;
   out_3211704972733304042[180] = 0;
   out_3211704972733304042[181] = 0;
   out_3211704972733304042[182] = 0;
   out_3211704972733304042[183] = 0;
   out_3211704972733304042[184] = 0;
   out_3211704972733304042[185] = 0;
   out_3211704972733304042[186] = 0;
   out_3211704972733304042[187] = 0;
   out_3211704972733304042[188] = 0;
   out_3211704972733304042[189] = 0;
   out_3211704972733304042[190] = 1;
   out_3211704972733304042[191] = 0;
   out_3211704972733304042[192] = 0;
   out_3211704972733304042[193] = 0;
   out_3211704972733304042[194] = 0;
   out_3211704972733304042[195] = 0;
   out_3211704972733304042[196] = 0;
   out_3211704972733304042[197] = 0;
   out_3211704972733304042[198] = 0;
   out_3211704972733304042[199] = 0;
   out_3211704972733304042[200] = 0;
   out_3211704972733304042[201] = 0;
   out_3211704972733304042[202] = 0;
   out_3211704972733304042[203] = 0;
   out_3211704972733304042[204] = 0;
   out_3211704972733304042[205] = 0;
   out_3211704972733304042[206] = 0;
   out_3211704972733304042[207] = 0;
   out_3211704972733304042[208] = 0;
   out_3211704972733304042[209] = 1;
   out_3211704972733304042[210] = 0;
   out_3211704972733304042[211] = 0;
   out_3211704972733304042[212] = 0;
   out_3211704972733304042[213] = 0;
   out_3211704972733304042[214] = 0;
   out_3211704972733304042[215] = 0;
   out_3211704972733304042[216] = 0;
   out_3211704972733304042[217] = 0;
   out_3211704972733304042[218] = 0;
   out_3211704972733304042[219] = 0;
   out_3211704972733304042[220] = 0;
   out_3211704972733304042[221] = 0;
   out_3211704972733304042[222] = 0;
   out_3211704972733304042[223] = 0;
   out_3211704972733304042[224] = 0;
   out_3211704972733304042[225] = 0;
   out_3211704972733304042[226] = 0;
   out_3211704972733304042[227] = 0;
   out_3211704972733304042[228] = 1;
   out_3211704972733304042[229] = 0;
   out_3211704972733304042[230] = 0;
   out_3211704972733304042[231] = 0;
   out_3211704972733304042[232] = 0;
   out_3211704972733304042[233] = 0;
   out_3211704972733304042[234] = 0;
   out_3211704972733304042[235] = 0;
   out_3211704972733304042[236] = 0;
   out_3211704972733304042[237] = 0;
   out_3211704972733304042[238] = 0;
   out_3211704972733304042[239] = 0;
   out_3211704972733304042[240] = 0;
   out_3211704972733304042[241] = 0;
   out_3211704972733304042[242] = 0;
   out_3211704972733304042[243] = 0;
   out_3211704972733304042[244] = 0;
   out_3211704972733304042[245] = 0;
   out_3211704972733304042[246] = 0;
   out_3211704972733304042[247] = 1;
   out_3211704972733304042[248] = 0;
   out_3211704972733304042[249] = 0;
   out_3211704972733304042[250] = 0;
   out_3211704972733304042[251] = 0;
   out_3211704972733304042[252] = 0;
   out_3211704972733304042[253] = 0;
   out_3211704972733304042[254] = 0;
   out_3211704972733304042[255] = 0;
   out_3211704972733304042[256] = 0;
   out_3211704972733304042[257] = 0;
   out_3211704972733304042[258] = 0;
   out_3211704972733304042[259] = 0;
   out_3211704972733304042[260] = 0;
   out_3211704972733304042[261] = 0;
   out_3211704972733304042[262] = 0;
   out_3211704972733304042[263] = 0;
   out_3211704972733304042[264] = 0;
   out_3211704972733304042[265] = 0;
   out_3211704972733304042[266] = 1;
   out_3211704972733304042[267] = 0;
   out_3211704972733304042[268] = 0;
   out_3211704972733304042[269] = 0;
   out_3211704972733304042[270] = 0;
   out_3211704972733304042[271] = 0;
   out_3211704972733304042[272] = 0;
   out_3211704972733304042[273] = 0;
   out_3211704972733304042[274] = 0;
   out_3211704972733304042[275] = 0;
   out_3211704972733304042[276] = 0;
   out_3211704972733304042[277] = 0;
   out_3211704972733304042[278] = 0;
   out_3211704972733304042[279] = 0;
   out_3211704972733304042[280] = 0;
   out_3211704972733304042[281] = 0;
   out_3211704972733304042[282] = 0;
   out_3211704972733304042[283] = 0;
   out_3211704972733304042[284] = 0;
   out_3211704972733304042[285] = 1;
   out_3211704972733304042[286] = 0;
   out_3211704972733304042[287] = 0;
   out_3211704972733304042[288] = 0;
   out_3211704972733304042[289] = 0;
   out_3211704972733304042[290] = 0;
   out_3211704972733304042[291] = 0;
   out_3211704972733304042[292] = 0;
   out_3211704972733304042[293] = 0;
   out_3211704972733304042[294] = 0;
   out_3211704972733304042[295] = 0;
   out_3211704972733304042[296] = 0;
   out_3211704972733304042[297] = 0;
   out_3211704972733304042[298] = 0;
   out_3211704972733304042[299] = 0;
   out_3211704972733304042[300] = 0;
   out_3211704972733304042[301] = 0;
   out_3211704972733304042[302] = 0;
   out_3211704972733304042[303] = 0;
   out_3211704972733304042[304] = 1;
   out_3211704972733304042[305] = 0;
   out_3211704972733304042[306] = 0;
   out_3211704972733304042[307] = 0;
   out_3211704972733304042[308] = 0;
   out_3211704972733304042[309] = 0;
   out_3211704972733304042[310] = 0;
   out_3211704972733304042[311] = 0;
   out_3211704972733304042[312] = 0;
   out_3211704972733304042[313] = 0;
   out_3211704972733304042[314] = 0;
   out_3211704972733304042[315] = 0;
   out_3211704972733304042[316] = 0;
   out_3211704972733304042[317] = 0;
   out_3211704972733304042[318] = 0;
   out_3211704972733304042[319] = 0;
   out_3211704972733304042[320] = 0;
   out_3211704972733304042[321] = 0;
   out_3211704972733304042[322] = 0;
   out_3211704972733304042[323] = 1;
}
void h_4(double *state, double *unused, double *out_4618547932677025290) {
   out_4618547932677025290[0] = state[6] + state[9];
   out_4618547932677025290[1] = state[7] + state[10];
   out_4618547932677025290[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_8857837342371745535) {
   out_8857837342371745535[0] = 0;
   out_8857837342371745535[1] = 0;
   out_8857837342371745535[2] = 0;
   out_8857837342371745535[3] = 0;
   out_8857837342371745535[4] = 0;
   out_8857837342371745535[5] = 0;
   out_8857837342371745535[6] = 1;
   out_8857837342371745535[7] = 0;
   out_8857837342371745535[8] = 0;
   out_8857837342371745535[9] = 1;
   out_8857837342371745535[10] = 0;
   out_8857837342371745535[11] = 0;
   out_8857837342371745535[12] = 0;
   out_8857837342371745535[13] = 0;
   out_8857837342371745535[14] = 0;
   out_8857837342371745535[15] = 0;
   out_8857837342371745535[16] = 0;
   out_8857837342371745535[17] = 0;
   out_8857837342371745535[18] = 0;
   out_8857837342371745535[19] = 0;
   out_8857837342371745535[20] = 0;
   out_8857837342371745535[21] = 0;
   out_8857837342371745535[22] = 0;
   out_8857837342371745535[23] = 0;
   out_8857837342371745535[24] = 0;
   out_8857837342371745535[25] = 1;
   out_8857837342371745535[26] = 0;
   out_8857837342371745535[27] = 0;
   out_8857837342371745535[28] = 1;
   out_8857837342371745535[29] = 0;
   out_8857837342371745535[30] = 0;
   out_8857837342371745535[31] = 0;
   out_8857837342371745535[32] = 0;
   out_8857837342371745535[33] = 0;
   out_8857837342371745535[34] = 0;
   out_8857837342371745535[35] = 0;
   out_8857837342371745535[36] = 0;
   out_8857837342371745535[37] = 0;
   out_8857837342371745535[38] = 0;
   out_8857837342371745535[39] = 0;
   out_8857837342371745535[40] = 0;
   out_8857837342371745535[41] = 0;
   out_8857837342371745535[42] = 0;
   out_8857837342371745535[43] = 0;
   out_8857837342371745535[44] = 1;
   out_8857837342371745535[45] = 0;
   out_8857837342371745535[46] = 0;
   out_8857837342371745535[47] = 1;
   out_8857837342371745535[48] = 0;
   out_8857837342371745535[49] = 0;
   out_8857837342371745535[50] = 0;
   out_8857837342371745535[51] = 0;
   out_8857837342371745535[52] = 0;
   out_8857837342371745535[53] = 0;
}
void h_10(double *state, double *unused, double *out_286079926766125973) {
   out_286079926766125973[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_286079926766125973[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_286079926766125973[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2479119896376040884) {
   out_2479119896376040884[0] = 0;
   out_2479119896376040884[1] = 9.8100000000000005*cos(state[1]);
   out_2479119896376040884[2] = 0;
   out_2479119896376040884[3] = 0;
   out_2479119896376040884[4] = -state[8];
   out_2479119896376040884[5] = state[7];
   out_2479119896376040884[6] = 0;
   out_2479119896376040884[7] = state[5];
   out_2479119896376040884[8] = -state[4];
   out_2479119896376040884[9] = 0;
   out_2479119896376040884[10] = 0;
   out_2479119896376040884[11] = 0;
   out_2479119896376040884[12] = 1;
   out_2479119896376040884[13] = 0;
   out_2479119896376040884[14] = 0;
   out_2479119896376040884[15] = 1;
   out_2479119896376040884[16] = 0;
   out_2479119896376040884[17] = 0;
   out_2479119896376040884[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2479119896376040884[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2479119896376040884[20] = 0;
   out_2479119896376040884[21] = state[8];
   out_2479119896376040884[22] = 0;
   out_2479119896376040884[23] = -state[6];
   out_2479119896376040884[24] = -state[5];
   out_2479119896376040884[25] = 0;
   out_2479119896376040884[26] = state[3];
   out_2479119896376040884[27] = 0;
   out_2479119896376040884[28] = 0;
   out_2479119896376040884[29] = 0;
   out_2479119896376040884[30] = 0;
   out_2479119896376040884[31] = 1;
   out_2479119896376040884[32] = 0;
   out_2479119896376040884[33] = 0;
   out_2479119896376040884[34] = 1;
   out_2479119896376040884[35] = 0;
   out_2479119896376040884[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2479119896376040884[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2479119896376040884[38] = 0;
   out_2479119896376040884[39] = -state[7];
   out_2479119896376040884[40] = state[6];
   out_2479119896376040884[41] = 0;
   out_2479119896376040884[42] = state[4];
   out_2479119896376040884[43] = -state[3];
   out_2479119896376040884[44] = 0;
   out_2479119896376040884[45] = 0;
   out_2479119896376040884[46] = 0;
   out_2479119896376040884[47] = 0;
   out_2479119896376040884[48] = 0;
   out_2479119896376040884[49] = 0;
   out_2479119896376040884[50] = 1;
   out_2479119896376040884[51] = 0;
   out_2479119896376040884[52] = 0;
   out_2479119896376040884[53] = 1;
}
void h_13(double *state, double *unused, double *out_829945007780659418) {
   out_829945007780659418[0] = state[3];
   out_829945007780659418[1] = state[4];
   out_829945007780659418[2] = state[5];
}
void H_13(double *state, double *unused, double *out_5755151268035282057) {
   out_5755151268035282057[0] = 0;
   out_5755151268035282057[1] = 0;
   out_5755151268035282057[2] = 0;
   out_5755151268035282057[3] = 1;
   out_5755151268035282057[4] = 0;
   out_5755151268035282057[5] = 0;
   out_5755151268035282057[6] = 0;
   out_5755151268035282057[7] = 0;
   out_5755151268035282057[8] = 0;
   out_5755151268035282057[9] = 0;
   out_5755151268035282057[10] = 0;
   out_5755151268035282057[11] = 0;
   out_5755151268035282057[12] = 0;
   out_5755151268035282057[13] = 0;
   out_5755151268035282057[14] = 0;
   out_5755151268035282057[15] = 0;
   out_5755151268035282057[16] = 0;
   out_5755151268035282057[17] = 0;
   out_5755151268035282057[18] = 0;
   out_5755151268035282057[19] = 0;
   out_5755151268035282057[20] = 0;
   out_5755151268035282057[21] = 0;
   out_5755151268035282057[22] = 1;
   out_5755151268035282057[23] = 0;
   out_5755151268035282057[24] = 0;
   out_5755151268035282057[25] = 0;
   out_5755151268035282057[26] = 0;
   out_5755151268035282057[27] = 0;
   out_5755151268035282057[28] = 0;
   out_5755151268035282057[29] = 0;
   out_5755151268035282057[30] = 0;
   out_5755151268035282057[31] = 0;
   out_5755151268035282057[32] = 0;
   out_5755151268035282057[33] = 0;
   out_5755151268035282057[34] = 0;
   out_5755151268035282057[35] = 0;
   out_5755151268035282057[36] = 0;
   out_5755151268035282057[37] = 0;
   out_5755151268035282057[38] = 0;
   out_5755151268035282057[39] = 0;
   out_5755151268035282057[40] = 0;
   out_5755151268035282057[41] = 1;
   out_5755151268035282057[42] = 0;
   out_5755151268035282057[43] = 0;
   out_5755151268035282057[44] = 0;
   out_5755151268035282057[45] = 0;
   out_5755151268035282057[46] = 0;
   out_5755151268035282057[47] = 0;
   out_5755151268035282057[48] = 0;
   out_5755151268035282057[49] = 0;
   out_5755151268035282057[50] = 0;
   out_5755151268035282057[51] = 0;
   out_5755151268035282057[52] = 0;
   out_5755151268035282057[53] = 0;
}
void h_14(double *state, double *unused, double *out_1492834352067073969) {
   out_1492834352067073969[0] = state[6];
   out_1492834352067073969[1] = state[7];
   out_1492834352067073969[2] = state[8];
}
void H_14(double *state, double *unused, double *out_6506118299042433785) {
   out_6506118299042433785[0] = 0;
   out_6506118299042433785[1] = 0;
   out_6506118299042433785[2] = 0;
   out_6506118299042433785[3] = 0;
   out_6506118299042433785[4] = 0;
   out_6506118299042433785[5] = 0;
   out_6506118299042433785[6] = 1;
   out_6506118299042433785[7] = 0;
   out_6506118299042433785[8] = 0;
   out_6506118299042433785[9] = 0;
   out_6506118299042433785[10] = 0;
   out_6506118299042433785[11] = 0;
   out_6506118299042433785[12] = 0;
   out_6506118299042433785[13] = 0;
   out_6506118299042433785[14] = 0;
   out_6506118299042433785[15] = 0;
   out_6506118299042433785[16] = 0;
   out_6506118299042433785[17] = 0;
   out_6506118299042433785[18] = 0;
   out_6506118299042433785[19] = 0;
   out_6506118299042433785[20] = 0;
   out_6506118299042433785[21] = 0;
   out_6506118299042433785[22] = 0;
   out_6506118299042433785[23] = 0;
   out_6506118299042433785[24] = 0;
   out_6506118299042433785[25] = 1;
   out_6506118299042433785[26] = 0;
   out_6506118299042433785[27] = 0;
   out_6506118299042433785[28] = 0;
   out_6506118299042433785[29] = 0;
   out_6506118299042433785[30] = 0;
   out_6506118299042433785[31] = 0;
   out_6506118299042433785[32] = 0;
   out_6506118299042433785[33] = 0;
   out_6506118299042433785[34] = 0;
   out_6506118299042433785[35] = 0;
   out_6506118299042433785[36] = 0;
   out_6506118299042433785[37] = 0;
   out_6506118299042433785[38] = 0;
   out_6506118299042433785[39] = 0;
   out_6506118299042433785[40] = 0;
   out_6506118299042433785[41] = 0;
   out_6506118299042433785[42] = 0;
   out_6506118299042433785[43] = 0;
   out_6506118299042433785[44] = 1;
   out_6506118299042433785[45] = 0;
   out_6506118299042433785[46] = 0;
   out_6506118299042433785[47] = 0;
   out_6506118299042433785[48] = 0;
   out_6506118299042433785[49] = 0;
   out_6506118299042433785[50] = 0;
   out_6506118299042433785[51] = 0;
   out_6506118299042433785[52] = 0;
   out_6506118299042433785[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7365448194845582757) {
  err_fun(nom_x, delta_x, out_7365448194845582757);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1967800537697910635) {
  inv_err_fun(nom_x, true_x, out_1967800537697910635);
}
void pose_H_mod_fun(double *state, double *out_8390959249454907977) {
  H_mod_fun(state, out_8390959249454907977);
}
void pose_f_fun(double *state, double dt, double *out_9042230065077868228) {
  f_fun(state,  dt, out_9042230065077868228);
}
void pose_F_fun(double *state, double dt, double *out_3211704972733304042) {
  F_fun(state,  dt, out_3211704972733304042);
}
void pose_h_4(double *state, double *unused, double *out_4618547932677025290) {
  h_4(state, unused, out_4618547932677025290);
}
void pose_H_4(double *state, double *unused, double *out_8857837342371745535) {
  H_4(state, unused, out_8857837342371745535);
}
void pose_h_10(double *state, double *unused, double *out_286079926766125973) {
  h_10(state, unused, out_286079926766125973);
}
void pose_H_10(double *state, double *unused, double *out_2479119896376040884) {
  H_10(state, unused, out_2479119896376040884);
}
void pose_h_13(double *state, double *unused, double *out_829945007780659418) {
  h_13(state, unused, out_829945007780659418);
}
void pose_H_13(double *state, double *unused, double *out_5755151268035282057) {
  H_13(state, unused, out_5755151268035282057);
}
void pose_h_14(double *state, double *unused, double *out_1492834352067073969) {
  h_14(state, unused, out_1492834352067073969);
}
void pose_H_14(double *state, double *unused, double *out_6506118299042433785) {
  H_14(state, unused, out_6506118299042433785);
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
