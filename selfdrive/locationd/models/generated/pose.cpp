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
void err_fun(double *nom_x, double *delta_x, double *out_5340642756295943636) {
   out_5340642756295943636[0] = delta_x[0] + nom_x[0];
   out_5340642756295943636[1] = delta_x[1] + nom_x[1];
   out_5340642756295943636[2] = delta_x[2] + nom_x[2];
   out_5340642756295943636[3] = delta_x[3] + nom_x[3];
   out_5340642756295943636[4] = delta_x[4] + nom_x[4];
   out_5340642756295943636[5] = delta_x[5] + nom_x[5];
   out_5340642756295943636[6] = delta_x[6] + nom_x[6];
   out_5340642756295943636[7] = delta_x[7] + nom_x[7];
   out_5340642756295943636[8] = delta_x[8] + nom_x[8];
   out_5340642756295943636[9] = delta_x[9] + nom_x[9];
   out_5340642756295943636[10] = delta_x[10] + nom_x[10];
   out_5340642756295943636[11] = delta_x[11] + nom_x[11];
   out_5340642756295943636[12] = delta_x[12] + nom_x[12];
   out_5340642756295943636[13] = delta_x[13] + nom_x[13];
   out_5340642756295943636[14] = delta_x[14] + nom_x[14];
   out_5340642756295943636[15] = delta_x[15] + nom_x[15];
   out_5340642756295943636[16] = delta_x[16] + nom_x[16];
   out_5340642756295943636[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6968876690248087810) {
   out_6968876690248087810[0] = -nom_x[0] + true_x[0];
   out_6968876690248087810[1] = -nom_x[1] + true_x[1];
   out_6968876690248087810[2] = -nom_x[2] + true_x[2];
   out_6968876690248087810[3] = -nom_x[3] + true_x[3];
   out_6968876690248087810[4] = -nom_x[4] + true_x[4];
   out_6968876690248087810[5] = -nom_x[5] + true_x[5];
   out_6968876690248087810[6] = -nom_x[6] + true_x[6];
   out_6968876690248087810[7] = -nom_x[7] + true_x[7];
   out_6968876690248087810[8] = -nom_x[8] + true_x[8];
   out_6968876690248087810[9] = -nom_x[9] + true_x[9];
   out_6968876690248087810[10] = -nom_x[10] + true_x[10];
   out_6968876690248087810[11] = -nom_x[11] + true_x[11];
   out_6968876690248087810[12] = -nom_x[12] + true_x[12];
   out_6968876690248087810[13] = -nom_x[13] + true_x[13];
   out_6968876690248087810[14] = -nom_x[14] + true_x[14];
   out_6968876690248087810[15] = -nom_x[15] + true_x[15];
   out_6968876690248087810[16] = -nom_x[16] + true_x[16];
   out_6968876690248087810[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3389862186663429553) {
   out_3389862186663429553[0] = 1.0;
   out_3389862186663429553[1] = 0.0;
   out_3389862186663429553[2] = 0.0;
   out_3389862186663429553[3] = 0.0;
   out_3389862186663429553[4] = 0.0;
   out_3389862186663429553[5] = 0.0;
   out_3389862186663429553[6] = 0.0;
   out_3389862186663429553[7] = 0.0;
   out_3389862186663429553[8] = 0.0;
   out_3389862186663429553[9] = 0.0;
   out_3389862186663429553[10] = 0.0;
   out_3389862186663429553[11] = 0.0;
   out_3389862186663429553[12] = 0.0;
   out_3389862186663429553[13] = 0.0;
   out_3389862186663429553[14] = 0.0;
   out_3389862186663429553[15] = 0.0;
   out_3389862186663429553[16] = 0.0;
   out_3389862186663429553[17] = 0.0;
   out_3389862186663429553[18] = 0.0;
   out_3389862186663429553[19] = 1.0;
   out_3389862186663429553[20] = 0.0;
   out_3389862186663429553[21] = 0.0;
   out_3389862186663429553[22] = 0.0;
   out_3389862186663429553[23] = 0.0;
   out_3389862186663429553[24] = 0.0;
   out_3389862186663429553[25] = 0.0;
   out_3389862186663429553[26] = 0.0;
   out_3389862186663429553[27] = 0.0;
   out_3389862186663429553[28] = 0.0;
   out_3389862186663429553[29] = 0.0;
   out_3389862186663429553[30] = 0.0;
   out_3389862186663429553[31] = 0.0;
   out_3389862186663429553[32] = 0.0;
   out_3389862186663429553[33] = 0.0;
   out_3389862186663429553[34] = 0.0;
   out_3389862186663429553[35] = 0.0;
   out_3389862186663429553[36] = 0.0;
   out_3389862186663429553[37] = 0.0;
   out_3389862186663429553[38] = 1.0;
   out_3389862186663429553[39] = 0.0;
   out_3389862186663429553[40] = 0.0;
   out_3389862186663429553[41] = 0.0;
   out_3389862186663429553[42] = 0.0;
   out_3389862186663429553[43] = 0.0;
   out_3389862186663429553[44] = 0.0;
   out_3389862186663429553[45] = 0.0;
   out_3389862186663429553[46] = 0.0;
   out_3389862186663429553[47] = 0.0;
   out_3389862186663429553[48] = 0.0;
   out_3389862186663429553[49] = 0.0;
   out_3389862186663429553[50] = 0.0;
   out_3389862186663429553[51] = 0.0;
   out_3389862186663429553[52] = 0.0;
   out_3389862186663429553[53] = 0.0;
   out_3389862186663429553[54] = 0.0;
   out_3389862186663429553[55] = 0.0;
   out_3389862186663429553[56] = 0.0;
   out_3389862186663429553[57] = 1.0;
   out_3389862186663429553[58] = 0.0;
   out_3389862186663429553[59] = 0.0;
   out_3389862186663429553[60] = 0.0;
   out_3389862186663429553[61] = 0.0;
   out_3389862186663429553[62] = 0.0;
   out_3389862186663429553[63] = 0.0;
   out_3389862186663429553[64] = 0.0;
   out_3389862186663429553[65] = 0.0;
   out_3389862186663429553[66] = 0.0;
   out_3389862186663429553[67] = 0.0;
   out_3389862186663429553[68] = 0.0;
   out_3389862186663429553[69] = 0.0;
   out_3389862186663429553[70] = 0.0;
   out_3389862186663429553[71] = 0.0;
   out_3389862186663429553[72] = 0.0;
   out_3389862186663429553[73] = 0.0;
   out_3389862186663429553[74] = 0.0;
   out_3389862186663429553[75] = 0.0;
   out_3389862186663429553[76] = 1.0;
   out_3389862186663429553[77] = 0.0;
   out_3389862186663429553[78] = 0.0;
   out_3389862186663429553[79] = 0.0;
   out_3389862186663429553[80] = 0.0;
   out_3389862186663429553[81] = 0.0;
   out_3389862186663429553[82] = 0.0;
   out_3389862186663429553[83] = 0.0;
   out_3389862186663429553[84] = 0.0;
   out_3389862186663429553[85] = 0.0;
   out_3389862186663429553[86] = 0.0;
   out_3389862186663429553[87] = 0.0;
   out_3389862186663429553[88] = 0.0;
   out_3389862186663429553[89] = 0.0;
   out_3389862186663429553[90] = 0.0;
   out_3389862186663429553[91] = 0.0;
   out_3389862186663429553[92] = 0.0;
   out_3389862186663429553[93] = 0.0;
   out_3389862186663429553[94] = 0.0;
   out_3389862186663429553[95] = 1.0;
   out_3389862186663429553[96] = 0.0;
   out_3389862186663429553[97] = 0.0;
   out_3389862186663429553[98] = 0.0;
   out_3389862186663429553[99] = 0.0;
   out_3389862186663429553[100] = 0.0;
   out_3389862186663429553[101] = 0.0;
   out_3389862186663429553[102] = 0.0;
   out_3389862186663429553[103] = 0.0;
   out_3389862186663429553[104] = 0.0;
   out_3389862186663429553[105] = 0.0;
   out_3389862186663429553[106] = 0.0;
   out_3389862186663429553[107] = 0.0;
   out_3389862186663429553[108] = 0.0;
   out_3389862186663429553[109] = 0.0;
   out_3389862186663429553[110] = 0.0;
   out_3389862186663429553[111] = 0.0;
   out_3389862186663429553[112] = 0.0;
   out_3389862186663429553[113] = 0.0;
   out_3389862186663429553[114] = 1.0;
   out_3389862186663429553[115] = 0.0;
   out_3389862186663429553[116] = 0.0;
   out_3389862186663429553[117] = 0.0;
   out_3389862186663429553[118] = 0.0;
   out_3389862186663429553[119] = 0.0;
   out_3389862186663429553[120] = 0.0;
   out_3389862186663429553[121] = 0.0;
   out_3389862186663429553[122] = 0.0;
   out_3389862186663429553[123] = 0.0;
   out_3389862186663429553[124] = 0.0;
   out_3389862186663429553[125] = 0.0;
   out_3389862186663429553[126] = 0.0;
   out_3389862186663429553[127] = 0.0;
   out_3389862186663429553[128] = 0.0;
   out_3389862186663429553[129] = 0.0;
   out_3389862186663429553[130] = 0.0;
   out_3389862186663429553[131] = 0.0;
   out_3389862186663429553[132] = 0.0;
   out_3389862186663429553[133] = 1.0;
   out_3389862186663429553[134] = 0.0;
   out_3389862186663429553[135] = 0.0;
   out_3389862186663429553[136] = 0.0;
   out_3389862186663429553[137] = 0.0;
   out_3389862186663429553[138] = 0.0;
   out_3389862186663429553[139] = 0.0;
   out_3389862186663429553[140] = 0.0;
   out_3389862186663429553[141] = 0.0;
   out_3389862186663429553[142] = 0.0;
   out_3389862186663429553[143] = 0.0;
   out_3389862186663429553[144] = 0.0;
   out_3389862186663429553[145] = 0.0;
   out_3389862186663429553[146] = 0.0;
   out_3389862186663429553[147] = 0.0;
   out_3389862186663429553[148] = 0.0;
   out_3389862186663429553[149] = 0.0;
   out_3389862186663429553[150] = 0.0;
   out_3389862186663429553[151] = 0.0;
   out_3389862186663429553[152] = 1.0;
   out_3389862186663429553[153] = 0.0;
   out_3389862186663429553[154] = 0.0;
   out_3389862186663429553[155] = 0.0;
   out_3389862186663429553[156] = 0.0;
   out_3389862186663429553[157] = 0.0;
   out_3389862186663429553[158] = 0.0;
   out_3389862186663429553[159] = 0.0;
   out_3389862186663429553[160] = 0.0;
   out_3389862186663429553[161] = 0.0;
   out_3389862186663429553[162] = 0.0;
   out_3389862186663429553[163] = 0.0;
   out_3389862186663429553[164] = 0.0;
   out_3389862186663429553[165] = 0.0;
   out_3389862186663429553[166] = 0.0;
   out_3389862186663429553[167] = 0.0;
   out_3389862186663429553[168] = 0.0;
   out_3389862186663429553[169] = 0.0;
   out_3389862186663429553[170] = 0.0;
   out_3389862186663429553[171] = 1.0;
   out_3389862186663429553[172] = 0.0;
   out_3389862186663429553[173] = 0.0;
   out_3389862186663429553[174] = 0.0;
   out_3389862186663429553[175] = 0.0;
   out_3389862186663429553[176] = 0.0;
   out_3389862186663429553[177] = 0.0;
   out_3389862186663429553[178] = 0.0;
   out_3389862186663429553[179] = 0.0;
   out_3389862186663429553[180] = 0.0;
   out_3389862186663429553[181] = 0.0;
   out_3389862186663429553[182] = 0.0;
   out_3389862186663429553[183] = 0.0;
   out_3389862186663429553[184] = 0.0;
   out_3389862186663429553[185] = 0.0;
   out_3389862186663429553[186] = 0.0;
   out_3389862186663429553[187] = 0.0;
   out_3389862186663429553[188] = 0.0;
   out_3389862186663429553[189] = 0.0;
   out_3389862186663429553[190] = 1.0;
   out_3389862186663429553[191] = 0.0;
   out_3389862186663429553[192] = 0.0;
   out_3389862186663429553[193] = 0.0;
   out_3389862186663429553[194] = 0.0;
   out_3389862186663429553[195] = 0.0;
   out_3389862186663429553[196] = 0.0;
   out_3389862186663429553[197] = 0.0;
   out_3389862186663429553[198] = 0.0;
   out_3389862186663429553[199] = 0.0;
   out_3389862186663429553[200] = 0.0;
   out_3389862186663429553[201] = 0.0;
   out_3389862186663429553[202] = 0.0;
   out_3389862186663429553[203] = 0.0;
   out_3389862186663429553[204] = 0.0;
   out_3389862186663429553[205] = 0.0;
   out_3389862186663429553[206] = 0.0;
   out_3389862186663429553[207] = 0.0;
   out_3389862186663429553[208] = 0.0;
   out_3389862186663429553[209] = 1.0;
   out_3389862186663429553[210] = 0.0;
   out_3389862186663429553[211] = 0.0;
   out_3389862186663429553[212] = 0.0;
   out_3389862186663429553[213] = 0.0;
   out_3389862186663429553[214] = 0.0;
   out_3389862186663429553[215] = 0.0;
   out_3389862186663429553[216] = 0.0;
   out_3389862186663429553[217] = 0.0;
   out_3389862186663429553[218] = 0.0;
   out_3389862186663429553[219] = 0.0;
   out_3389862186663429553[220] = 0.0;
   out_3389862186663429553[221] = 0.0;
   out_3389862186663429553[222] = 0.0;
   out_3389862186663429553[223] = 0.0;
   out_3389862186663429553[224] = 0.0;
   out_3389862186663429553[225] = 0.0;
   out_3389862186663429553[226] = 0.0;
   out_3389862186663429553[227] = 0.0;
   out_3389862186663429553[228] = 1.0;
   out_3389862186663429553[229] = 0.0;
   out_3389862186663429553[230] = 0.0;
   out_3389862186663429553[231] = 0.0;
   out_3389862186663429553[232] = 0.0;
   out_3389862186663429553[233] = 0.0;
   out_3389862186663429553[234] = 0.0;
   out_3389862186663429553[235] = 0.0;
   out_3389862186663429553[236] = 0.0;
   out_3389862186663429553[237] = 0.0;
   out_3389862186663429553[238] = 0.0;
   out_3389862186663429553[239] = 0.0;
   out_3389862186663429553[240] = 0.0;
   out_3389862186663429553[241] = 0.0;
   out_3389862186663429553[242] = 0.0;
   out_3389862186663429553[243] = 0.0;
   out_3389862186663429553[244] = 0.0;
   out_3389862186663429553[245] = 0.0;
   out_3389862186663429553[246] = 0.0;
   out_3389862186663429553[247] = 1.0;
   out_3389862186663429553[248] = 0.0;
   out_3389862186663429553[249] = 0.0;
   out_3389862186663429553[250] = 0.0;
   out_3389862186663429553[251] = 0.0;
   out_3389862186663429553[252] = 0.0;
   out_3389862186663429553[253] = 0.0;
   out_3389862186663429553[254] = 0.0;
   out_3389862186663429553[255] = 0.0;
   out_3389862186663429553[256] = 0.0;
   out_3389862186663429553[257] = 0.0;
   out_3389862186663429553[258] = 0.0;
   out_3389862186663429553[259] = 0.0;
   out_3389862186663429553[260] = 0.0;
   out_3389862186663429553[261] = 0.0;
   out_3389862186663429553[262] = 0.0;
   out_3389862186663429553[263] = 0.0;
   out_3389862186663429553[264] = 0.0;
   out_3389862186663429553[265] = 0.0;
   out_3389862186663429553[266] = 1.0;
   out_3389862186663429553[267] = 0.0;
   out_3389862186663429553[268] = 0.0;
   out_3389862186663429553[269] = 0.0;
   out_3389862186663429553[270] = 0.0;
   out_3389862186663429553[271] = 0.0;
   out_3389862186663429553[272] = 0.0;
   out_3389862186663429553[273] = 0.0;
   out_3389862186663429553[274] = 0.0;
   out_3389862186663429553[275] = 0.0;
   out_3389862186663429553[276] = 0.0;
   out_3389862186663429553[277] = 0.0;
   out_3389862186663429553[278] = 0.0;
   out_3389862186663429553[279] = 0.0;
   out_3389862186663429553[280] = 0.0;
   out_3389862186663429553[281] = 0.0;
   out_3389862186663429553[282] = 0.0;
   out_3389862186663429553[283] = 0.0;
   out_3389862186663429553[284] = 0.0;
   out_3389862186663429553[285] = 1.0;
   out_3389862186663429553[286] = 0.0;
   out_3389862186663429553[287] = 0.0;
   out_3389862186663429553[288] = 0.0;
   out_3389862186663429553[289] = 0.0;
   out_3389862186663429553[290] = 0.0;
   out_3389862186663429553[291] = 0.0;
   out_3389862186663429553[292] = 0.0;
   out_3389862186663429553[293] = 0.0;
   out_3389862186663429553[294] = 0.0;
   out_3389862186663429553[295] = 0.0;
   out_3389862186663429553[296] = 0.0;
   out_3389862186663429553[297] = 0.0;
   out_3389862186663429553[298] = 0.0;
   out_3389862186663429553[299] = 0.0;
   out_3389862186663429553[300] = 0.0;
   out_3389862186663429553[301] = 0.0;
   out_3389862186663429553[302] = 0.0;
   out_3389862186663429553[303] = 0.0;
   out_3389862186663429553[304] = 1.0;
   out_3389862186663429553[305] = 0.0;
   out_3389862186663429553[306] = 0.0;
   out_3389862186663429553[307] = 0.0;
   out_3389862186663429553[308] = 0.0;
   out_3389862186663429553[309] = 0.0;
   out_3389862186663429553[310] = 0.0;
   out_3389862186663429553[311] = 0.0;
   out_3389862186663429553[312] = 0.0;
   out_3389862186663429553[313] = 0.0;
   out_3389862186663429553[314] = 0.0;
   out_3389862186663429553[315] = 0.0;
   out_3389862186663429553[316] = 0.0;
   out_3389862186663429553[317] = 0.0;
   out_3389862186663429553[318] = 0.0;
   out_3389862186663429553[319] = 0.0;
   out_3389862186663429553[320] = 0.0;
   out_3389862186663429553[321] = 0.0;
   out_3389862186663429553[322] = 0.0;
   out_3389862186663429553[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4802700997878092668) {
   out_4802700997878092668[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4802700997878092668[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4802700997878092668[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4802700997878092668[3] = dt*state[12] + state[3];
   out_4802700997878092668[4] = dt*state[13] + state[4];
   out_4802700997878092668[5] = dt*state[14] + state[5];
   out_4802700997878092668[6] = state[6];
   out_4802700997878092668[7] = state[7];
   out_4802700997878092668[8] = state[8];
   out_4802700997878092668[9] = state[9];
   out_4802700997878092668[10] = state[10];
   out_4802700997878092668[11] = state[11];
   out_4802700997878092668[12] = state[12];
   out_4802700997878092668[13] = state[13];
   out_4802700997878092668[14] = state[14];
   out_4802700997878092668[15] = state[15];
   out_4802700997878092668[16] = state[16];
   out_4802700997878092668[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8725044315227912670) {
   out_8725044315227912670[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8725044315227912670[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8725044315227912670[2] = 0;
   out_8725044315227912670[3] = 0;
   out_8725044315227912670[4] = 0;
   out_8725044315227912670[5] = 0;
   out_8725044315227912670[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8725044315227912670[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8725044315227912670[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8725044315227912670[9] = 0;
   out_8725044315227912670[10] = 0;
   out_8725044315227912670[11] = 0;
   out_8725044315227912670[12] = 0;
   out_8725044315227912670[13] = 0;
   out_8725044315227912670[14] = 0;
   out_8725044315227912670[15] = 0;
   out_8725044315227912670[16] = 0;
   out_8725044315227912670[17] = 0;
   out_8725044315227912670[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8725044315227912670[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8725044315227912670[20] = 0;
   out_8725044315227912670[21] = 0;
   out_8725044315227912670[22] = 0;
   out_8725044315227912670[23] = 0;
   out_8725044315227912670[24] = 0;
   out_8725044315227912670[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8725044315227912670[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8725044315227912670[27] = 0;
   out_8725044315227912670[28] = 0;
   out_8725044315227912670[29] = 0;
   out_8725044315227912670[30] = 0;
   out_8725044315227912670[31] = 0;
   out_8725044315227912670[32] = 0;
   out_8725044315227912670[33] = 0;
   out_8725044315227912670[34] = 0;
   out_8725044315227912670[35] = 0;
   out_8725044315227912670[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8725044315227912670[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8725044315227912670[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8725044315227912670[39] = 0;
   out_8725044315227912670[40] = 0;
   out_8725044315227912670[41] = 0;
   out_8725044315227912670[42] = 0;
   out_8725044315227912670[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8725044315227912670[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8725044315227912670[45] = 0;
   out_8725044315227912670[46] = 0;
   out_8725044315227912670[47] = 0;
   out_8725044315227912670[48] = 0;
   out_8725044315227912670[49] = 0;
   out_8725044315227912670[50] = 0;
   out_8725044315227912670[51] = 0;
   out_8725044315227912670[52] = 0;
   out_8725044315227912670[53] = 0;
   out_8725044315227912670[54] = 0;
   out_8725044315227912670[55] = 0;
   out_8725044315227912670[56] = 0;
   out_8725044315227912670[57] = 1;
   out_8725044315227912670[58] = 0;
   out_8725044315227912670[59] = 0;
   out_8725044315227912670[60] = 0;
   out_8725044315227912670[61] = 0;
   out_8725044315227912670[62] = 0;
   out_8725044315227912670[63] = 0;
   out_8725044315227912670[64] = 0;
   out_8725044315227912670[65] = 0;
   out_8725044315227912670[66] = dt;
   out_8725044315227912670[67] = 0;
   out_8725044315227912670[68] = 0;
   out_8725044315227912670[69] = 0;
   out_8725044315227912670[70] = 0;
   out_8725044315227912670[71] = 0;
   out_8725044315227912670[72] = 0;
   out_8725044315227912670[73] = 0;
   out_8725044315227912670[74] = 0;
   out_8725044315227912670[75] = 0;
   out_8725044315227912670[76] = 1;
   out_8725044315227912670[77] = 0;
   out_8725044315227912670[78] = 0;
   out_8725044315227912670[79] = 0;
   out_8725044315227912670[80] = 0;
   out_8725044315227912670[81] = 0;
   out_8725044315227912670[82] = 0;
   out_8725044315227912670[83] = 0;
   out_8725044315227912670[84] = 0;
   out_8725044315227912670[85] = dt;
   out_8725044315227912670[86] = 0;
   out_8725044315227912670[87] = 0;
   out_8725044315227912670[88] = 0;
   out_8725044315227912670[89] = 0;
   out_8725044315227912670[90] = 0;
   out_8725044315227912670[91] = 0;
   out_8725044315227912670[92] = 0;
   out_8725044315227912670[93] = 0;
   out_8725044315227912670[94] = 0;
   out_8725044315227912670[95] = 1;
   out_8725044315227912670[96] = 0;
   out_8725044315227912670[97] = 0;
   out_8725044315227912670[98] = 0;
   out_8725044315227912670[99] = 0;
   out_8725044315227912670[100] = 0;
   out_8725044315227912670[101] = 0;
   out_8725044315227912670[102] = 0;
   out_8725044315227912670[103] = 0;
   out_8725044315227912670[104] = dt;
   out_8725044315227912670[105] = 0;
   out_8725044315227912670[106] = 0;
   out_8725044315227912670[107] = 0;
   out_8725044315227912670[108] = 0;
   out_8725044315227912670[109] = 0;
   out_8725044315227912670[110] = 0;
   out_8725044315227912670[111] = 0;
   out_8725044315227912670[112] = 0;
   out_8725044315227912670[113] = 0;
   out_8725044315227912670[114] = 1;
   out_8725044315227912670[115] = 0;
   out_8725044315227912670[116] = 0;
   out_8725044315227912670[117] = 0;
   out_8725044315227912670[118] = 0;
   out_8725044315227912670[119] = 0;
   out_8725044315227912670[120] = 0;
   out_8725044315227912670[121] = 0;
   out_8725044315227912670[122] = 0;
   out_8725044315227912670[123] = 0;
   out_8725044315227912670[124] = 0;
   out_8725044315227912670[125] = 0;
   out_8725044315227912670[126] = 0;
   out_8725044315227912670[127] = 0;
   out_8725044315227912670[128] = 0;
   out_8725044315227912670[129] = 0;
   out_8725044315227912670[130] = 0;
   out_8725044315227912670[131] = 0;
   out_8725044315227912670[132] = 0;
   out_8725044315227912670[133] = 1;
   out_8725044315227912670[134] = 0;
   out_8725044315227912670[135] = 0;
   out_8725044315227912670[136] = 0;
   out_8725044315227912670[137] = 0;
   out_8725044315227912670[138] = 0;
   out_8725044315227912670[139] = 0;
   out_8725044315227912670[140] = 0;
   out_8725044315227912670[141] = 0;
   out_8725044315227912670[142] = 0;
   out_8725044315227912670[143] = 0;
   out_8725044315227912670[144] = 0;
   out_8725044315227912670[145] = 0;
   out_8725044315227912670[146] = 0;
   out_8725044315227912670[147] = 0;
   out_8725044315227912670[148] = 0;
   out_8725044315227912670[149] = 0;
   out_8725044315227912670[150] = 0;
   out_8725044315227912670[151] = 0;
   out_8725044315227912670[152] = 1;
   out_8725044315227912670[153] = 0;
   out_8725044315227912670[154] = 0;
   out_8725044315227912670[155] = 0;
   out_8725044315227912670[156] = 0;
   out_8725044315227912670[157] = 0;
   out_8725044315227912670[158] = 0;
   out_8725044315227912670[159] = 0;
   out_8725044315227912670[160] = 0;
   out_8725044315227912670[161] = 0;
   out_8725044315227912670[162] = 0;
   out_8725044315227912670[163] = 0;
   out_8725044315227912670[164] = 0;
   out_8725044315227912670[165] = 0;
   out_8725044315227912670[166] = 0;
   out_8725044315227912670[167] = 0;
   out_8725044315227912670[168] = 0;
   out_8725044315227912670[169] = 0;
   out_8725044315227912670[170] = 0;
   out_8725044315227912670[171] = 1;
   out_8725044315227912670[172] = 0;
   out_8725044315227912670[173] = 0;
   out_8725044315227912670[174] = 0;
   out_8725044315227912670[175] = 0;
   out_8725044315227912670[176] = 0;
   out_8725044315227912670[177] = 0;
   out_8725044315227912670[178] = 0;
   out_8725044315227912670[179] = 0;
   out_8725044315227912670[180] = 0;
   out_8725044315227912670[181] = 0;
   out_8725044315227912670[182] = 0;
   out_8725044315227912670[183] = 0;
   out_8725044315227912670[184] = 0;
   out_8725044315227912670[185] = 0;
   out_8725044315227912670[186] = 0;
   out_8725044315227912670[187] = 0;
   out_8725044315227912670[188] = 0;
   out_8725044315227912670[189] = 0;
   out_8725044315227912670[190] = 1;
   out_8725044315227912670[191] = 0;
   out_8725044315227912670[192] = 0;
   out_8725044315227912670[193] = 0;
   out_8725044315227912670[194] = 0;
   out_8725044315227912670[195] = 0;
   out_8725044315227912670[196] = 0;
   out_8725044315227912670[197] = 0;
   out_8725044315227912670[198] = 0;
   out_8725044315227912670[199] = 0;
   out_8725044315227912670[200] = 0;
   out_8725044315227912670[201] = 0;
   out_8725044315227912670[202] = 0;
   out_8725044315227912670[203] = 0;
   out_8725044315227912670[204] = 0;
   out_8725044315227912670[205] = 0;
   out_8725044315227912670[206] = 0;
   out_8725044315227912670[207] = 0;
   out_8725044315227912670[208] = 0;
   out_8725044315227912670[209] = 1;
   out_8725044315227912670[210] = 0;
   out_8725044315227912670[211] = 0;
   out_8725044315227912670[212] = 0;
   out_8725044315227912670[213] = 0;
   out_8725044315227912670[214] = 0;
   out_8725044315227912670[215] = 0;
   out_8725044315227912670[216] = 0;
   out_8725044315227912670[217] = 0;
   out_8725044315227912670[218] = 0;
   out_8725044315227912670[219] = 0;
   out_8725044315227912670[220] = 0;
   out_8725044315227912670[221] = 0;
   out_8725044315227912670[222] = 0;
   out_8725044315227912670[223] = 0;
   out_8725044315227912670[224] = 0;
   out_8725044315227912670[225] = 0;
   out_8725044315227912670[226] = 0;
   out_8725044315227912670[227] = 0;
   out_8725044315227912670[228] = 1;
   out_8725044315227912670[229] = 0;
   out_8725044315227912670[230] = 0;
   out_8725044315227912670[231] = 0;
   out_8725044315227912670[232] = 0;
   out_8725044315227912670[233] = 0;
   out_8725044315227912670[234] = 0;
   out_8725044315227912670[235] = 0;
   out_8725044315227912670[236] = 0;
   out_8725044315227912670[237] = 0;
   out_8725044315227912670[238] = 0;
   out_8725044315227912670[239] = 0;
   out_8725044315227912670[240] = 0;
   out_8725044315227912670[241] = 0;
   out_8725044315227912670[242] = 0;
   out_8725044315227912670[243] = 0;
   out_8725044315227912670[244] = 0;
   out_8725044315227912670[245] = 0;
   out_8725044315227912670[246] = 0;
   out_8725044315227912670[247] = 1;
   out_8725044315227912670[248] = 0;
   out_8725044315227912670[249] = 0;
   out_8725044315227912670[250] = 0;
   out_8725044315227912670[251] = 0;
   out_8725044315227912670[252] = 0;
   out_8725044315227912670[253] = 0;
   out_8725044315227912670[254] = 0;
   out_8725044315227912670[255] = 0;
   out_8725044315227912670[256] = 0;
   out_8725044315227912670[257] = 0;
   out_8725044315227912670[258] = 0;
   out_8725044315227912670[259] = 0;
   out_8725044315227912670[260] = 0;
   out_8725044315227912670[261] = 0;
   out_8725044315227912670[262] = 0;
   out_8725044315227912670[263] = 0;
   out_8725044315227912670[264] = 0;
   out_8725044315227912670[265] = 0;
   out_8725044315227912670[266] = 1;
   out_8725044315227912670[267] = 0;
   out_8725044315227912670[268] = 0;
   out_8725044315227912670[269] = 0;
   out_8725044315227912670[270] = 0;
   out_8725044315227912670[271] = 0;
   out_8725044315227912670[272] = 0;
   out_8725044315227912670[273] = 0;
   out_8725044315227912670[274] = 0;
   out_8725044315227912670[275] = 0;
   out_8725044315227912670[276] = 0;
   out_8725044315227912670[277] = 0;
   out_8725044315227912670[278] = 0;
   out_8725044315227912670[279] = 0;
   out_8725044315227912670[280] = 0;
   out_8725044315227912670[281] = 0;
   out_8725044315227912670[282] = 0;
   out_8725044315227912670[283] = 0;
   out_8725044315227912670[284] = 0;
   out_8725044315227912670[285] = 1;
   out_8725044315227912670[286] = 0;
   out_8725044315227912670[287] = 0;
   out_8725044315227912670[288] = 0;
   out_8725044315227912670[289] = 0;
   out_8725044315227912670[290] = 0;
   out_8725044315227912670[291] = 0;
   out_8725044315227912670[292] = 0;
   out_8725044315227912670[293] = 0;
   out_8725044315227912670[294] = 0;
   out_8725044315227912670[295] = 0;
   out_8725044315227912670[296] = 0;
   out_8725044315227912670[297] = 0;
   out_8725044315227912670[298] = 0;
   out_8725044315227912670[299] = 0;
   out_8725044315227912670[300] = 0;
   out_8725044315227912670[301] = 0;
   out_8725044315227912670[302] = 0;
   out_8725044315227912670[303] = 0;
   out_8725044315227912670[304] = 1;
   out_8725044315227912670[305] = 0;
   out_8725044315227912670[306] = 0;
   out_8725044315227912670[307] = 0;
   out_8725044315227912670[308] = 0;
   out_8725044315227912670[309] = 0;
   out_8725044315227912670[310] = 0;
   out_8725044315227912670[311] = 0;
   out_8725044315227912670[312] = 0;
   out_8725044315227912670[313] = 0;
   out_8725044315227912670[314] = 0;
   out_8725044315227912670[315] = 0;
   out_8725044315227912670[316] = 0;
   out_8725044315227912670[317] = 0;
   out_8725044315227912670[318] = 0;
   out_8725044315227912670[319] = 0;
   out_8725044315227912670[320] = 0;
   out_8725044315227912670[321] = 0;
   out_8725044315227912670[322] = 0;
   out_8725044315227912670[323] = 1;
}
void h_4(double *state, double *unused, double *out_1359340648735360631) {
   out_1359340648735360631[0] = state[6] + state[9];
   out_1359340648735360631[1] = state[7] + state[10];
   out_1359340648735360631[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4587809668546327657) {
   out_4587809668546327657[0] = 0;
   out_4587809668546327657[1] = 0;
   out_4587809668546327657[2] = 0;
   out_4587809668546327657[3] = 0;
   out_4587809668546327657[4] = 0;
   out_4587809668546327657[5] = 0;
   out_4587809668546327657[6] = 1;
   out_4587809668546327657[7] = 0;
   out_4587809668546327657[8] = 0;
   out_4587809668546327657[9] = 1;
   out_4587809668546327657[10] = 0;
   out_4587809668546327657[11] = 0;
   out_4587809668546327657[12] = 0;
   out_4587809668546327657[13] = 0;
   out_4587809668546327657[14] = 0;
   out_4587809668546327657[15] = 0;
   out_4587809668546327657[16] = 0;
   out_4587809668546327657[17] = 0;
   out_4587809668546327657[18] = 0;
   out_4587809668546327657[19] = 0;
   out_4587809668546327657[20] = 0;
   out_4587809668546327657[21] = 0;
   out_4587809668546327657[22] = 0;
   out_4587809668546327657[23] = 0;
   out_4587809668546327657[24] = 0;
   out_4587809668546327657[25] = 1;
   out_4587809668546327657[26] = 0;
   out_4587809668546327657[27] = 0;
   out_4587809668546327657[28] = 1;
   out_4587809668546327657[29] = 0;
   out_4587809668546327657[30] = 0;
   out_4587809668546327657[31] = 0;
   out_4587809668546327657[32] = 0;
   out_4587809668546327657[33] = 0;
   out_4587809668546327657[34] = 0;
   out_4587809668546327657[35] = 0;
   out_4587809668546327657[36] = 0;
   out_4587809668546327657[37] = 0;
   out_4587809668546327657[38] = 0;
   out_4587809668546327657[39] = 0;
   out_4587809668546327657[40] = 0;
   out_4587809668546327657[41] = 0;
   out_4587809668546327657[42] = 0;
   out_4587809668546327657[43] = 0;
   out_4587809668546327657[44] = 1;
   out_4587809668546327657[45] = 0;
   out_4587809668546327657[46] = 0;
   out_4587809668546327657[47] = 1;
   out_4587809668546327657[48] = 0;
   out_4587809668546327657[49] = 0;
   out_4587809668546327657[50] = 0;
   out_4587809668546327657[51] = 0;
   out_4587809668546327657[52] = 0;
   out_4587809668546327657[53] = 0;
}
void h_10(double *state, double *unused, double *out_6036145492114111302) {
   out_6036145492114111302[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_6036145492114111302[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_6036145492114111302[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7466880812702133914) {
   out_7466880812702133914[0] = 0;
   out_7466880812702133914[1] = 9.8100000000000005*cos(state[1]);
   out_7466880812702133914[2] = 0;
   out_7466880812702133914[3] = 0;
   out_7466880812702133914[4] = -state[8];
   out_7466880812702133914[5] = state[7];
   out_7466880812702133914[6] = 0;
   out_7466880812702133914[7] = state[5];
   out_7466880812702133914[8] = -state[4];
   out_7466880812702133914[9] = 0;
   out_7466880812702133914[10] = 0;
   out_7466880812702133914[11] = 0;
   out_7466880812702133914[12] = 1;
   out_7466880812702133914[13] = 0;
   out_7466880812702133914[14] = 0;
   out_7466880812702133914[15] = 1;
   out_7466880812702133914[16] = 0;
   out_7466880812702133914[17] = 0;
   out_7466880812702133914[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7466880812702133914[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7466880812702133914[20] = 0;
   out_7466880812702133914[21] = state[8];
   out_7466880812702133914[22] = 0;
   out_7466880812702133914[23] = -state[6];
   out_7466880812702133914[24] = -state[5];
   out_7466880812702133914[25] = 0;
   out_7466880812702133914[26] = state[3];
   out_7466880812702133914[27] = 0;
   out_7466880812702133914[28] = 0;
   out_7466880812702133914[29] = 0;
   out_7466880812702133914[30] = 0;
   out_7466880812702133914[31] = 1;
   out_7466880812702133914[32] = 0;
   out_7466880812702133914[33] = 0;
   out_7466880812702133914[34] = 1;
   out_7466880812702133914[35] = 0;
   out_7466880812702133914[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7466880812702133914[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7466880812702133914[38] = 0;
   out_7466880812702133914[39] = -state[7];
   out_7466880812702133914[40] = state[6];
   out_7466880812702133914[41] = 0;
   out_7466880812702133914[42] = state[4];
   out_7466880812702133914[43] = -state[3];
   out_7466880812702133914[44] = 0;
   out_7466880812702133914[45] = 0;
   out_7466880812702133914[46] = 0;
   out_7466880812702133914[47] = 0;
   out_7466880812702133914[48] = 0;
   out_7466880812702133914[49] = 0;
   out_7466880812702133914[50] = 1;
   out_7466880812702133914[51] = 0;
   out_7466880812702133914[52] = 0;
   out_7466880812702133914[53] = 1;
}
void h_13(double *state, double *unused, double *out_863073697323037062) {
   out_863073697323037062[0] = state[3];
   out_863073697323037062[1] = state[4];
   out_863073697323037062[2] = state[5];
}
void H_13(double *state, double *unused, double *out_7800083493878660458) {
   out_7800083493878660458[0] = 0;
   out_7800083493878660458[1] = 0;
   out_7800083493878660458[2] = 0;
   out_7800083493878660458[3] = 1;
   out_7800083493878660458[4] = 0;
   out_7800083493878660458[5] = 0;
   out_7800083493878660458[6] = 0;
   out_7800083493878660458[7] = 0;
   out_7800083493878660458[8] = 0;
   out_7800083493878660458[9] = 0;
   out_7800083493878660458[10] = 0;
   out_7800083493878660458[11] = 0;
   out_7800083493878660458[12] = 0;
   out_7800083493878660458[13] = 0;
   out_7800083493878660458[14] = 0;
   out_7800083493878660458[15] = 0;
   out_7800083493878660458[16] = 0;
   out_7800083493878660458[17] = 0;
   out_7800083493878660458[18] = 0;
   out_7800083493878660458[19] = 0;
   out_7800083493878660458[20] = 0;
   out_7800083493878660458[21] = 0;
   out_7800083493878660458[22] = 1;
   out_7800083493878660458[23] = 0;
   out_7800083493878660458[24] = 0;
   out_7800083493878660458[25] = 0;
   out_7800083493878660458[26] = 0;
   out_7800083493878660458[27] = 0;
   out_7800083493878660458[28] = 0;
   out_7800083493878660458[29] = 0;
   out_7800083493878660458[30] = 0;
   out_7800083493878660458[31] = 0;
   out_7800083493878660458[32] = 0;
   out_7800083493878660458[33] = 0;
   out_7800083493878660458[34] = 0;
   out_7800083493878660458[35] = 0;
   out_7800083493878660458[36] = 0;
   out_7800083493878660458[37] = 0;
   out_7800083493878660458[38] = 0;
   out_7800083493878660458[39] = 0;
   out_7800083493878660458[40] = 0;
   out_7800083493878660458[41] = 1;
   out_7800083493878660458[42] = 0;
   out_7800083493878660458[43] = 0;
   out_7800083493878660458[44] = 0;
   out_7800083493878660458[45] = 0;
   out_7800083493878660458[46] = 0;
   out_7800083493878660458[47] = 0;
   out_7800083493878660458[48] = 0;
   out_7800083493878660458[49] = 0;
   out_7800083493878660458[50] = 0;
   out_7800083493878660458[51] = 0;
   out_7800083493878660458[52] = 0;
   out_7800083493878660458[53] = 0;
}
void h_14(double *state, double *unused, double *out_1770197321873156194) {
   out_1770197321873156194[0] = state[6];
   out_1770197321873156194[1] = state[7];
   out_1770197321873156194[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1505021236250955361) {
   out_1505021236250955361[0] = 0;
   out_1505021236250955361[1] = 0;
   out_1505021236250955361[2] = 0;
   out_1505021236250955361[3] = 0;
   out_1505021236250955361[4] = 0;
   out_1505021236250955361[5] = 0;
   out_1505021236250955361[6] = 1;
   out_1505021236250955361[7] = 0;
   out_1505021236250955361[8] = 0;
   out_1505021236250955361[9] = 0;
   out_1505021236250955361[10] = 0;
   out_1505021236250955361[11] = 0;
   out_1505021236250955361[12] = 0;
   out_1505021236250955361[13] = 0;
   out_1505021236250955361[14] = 0;
   out_1505021236250955361[15] = 0;
   out_1505021236250955361[16] = 0;
   out_1505021236250955361[17] = 0;
   out_1505021236250955361[18] = 0;
   out_1505021236250955361[19] = 0;
   out_1505021236250955361[20] = 0;
   out_1505021236250955361[21] = 0;
   out_1505021236250955361[22] = 0;
   out_1505021236250955361[23] = 0;
   out_1505021236250955361[24] = 0;
   out_1505021236250955361[25] = 1;
   out_1505021236250955361[26] = 0;
   out_1505021236250955361[27] = 0;
   out_1505021236250955361[28] = 0;
   out_1505021236250955361[29] = 0;
   out_1505021236250955361[30] = 0;
   out_1505021236250955361[31] = 0;
   out_1505021236250955361[32] = 0;
   out_1505021236250955361[33] = 0;
   out_1505021236250955361[34] = 0;
   out_1505021236250955361[35] = 0;
   out_1505021236250955361[36] = 0;
   out_1505021236250955361[37] = 0;
   out_1505021236250955361[38] = 0;
   out_1505021236250955361[39] = 0;
   out_1505021236250955361[40] = 0;
   out_1505021236250955361[41] = 0;
   out_1505021236250955361[42] = 0;
   out_1505021236250955361[43] = 0;
   out_1505021236250955361[44] = 1;
   out_1505021236250955361[45] = 0;
   out_1505021236250955361[46] = 0;
   out_1505021236250955361[47] = 0;
   out_1505021236250955361[48] = 0;
   out_1505021236250955361[49] = 0;
   out_1505021236250955361[50] = 0;
   out_1505021236250955361[51] = 0;
   out_1505021236250955361[52] = 0;
   out_1505021236250955361[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5340642756295943636) {
  err_fun(nom_x, delta_x, out_5340642756295943636);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6968876690248087810) {
  inv_err_fun(nom_x, true_x, out_6968876690248087810);
}
void pose_H_mod_fun(double *state, double *out_3389862186663429553) {
  H_mod_fun(state, out_3389862186663429553);
}
void pose_f_fun(double *state, double dt, double *out_4802700997878092668) {
  f_fun(state,  dt, out_4802700997878092668);
}
void pose_F_fun(double *state, double dt, double *out_8725044315227912670) {
  F_fun(state,  dt, out_8725044315227912670);
}
void pose_h_4(double *state, double *unused, double *out_1359340648735360631) {
  h_4(state, unused, out_1359340648735360631);
}
void pose_H_4(double *state, double *unused, double *out_4587809668546327657) {
  H_4(state, unused, out_4587809668546327657);
}
void pose_h_10(double *state, double *unused, double *out_6036145492114111302) {
  h_10(state, unused, out_6036145492114111302);
}
void pose_H_10(double *state, double *unused, double *out_7466880812702133914) {
  H_10(state, unused, out_7466880812702133914);
}
void pose_h_13(double *state, double *unused, double *out_863073697323037062) {
  h_13(state, unused, out_863073697323037062);
}
void pose_H_13(double *state, double *unused, double *out_7800083493878660458) {
  H_13(state, unused, out_7800083493878660458);
}
void pose_h_14(double *state, double *unused, double *out_1770197321873156194) {
  h_14(state, unused, out_1770197321873156194);
}
void pose_H_14(double *state, double *unused, double *out_1505021236250955361) {
  H_14(state, unused, out_1505021236250955361);
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
