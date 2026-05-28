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
void err_fun(double *nom_x, double *delta_x, double *out_6989025868442055132) {
   out_6989025868442055132[0] = delta_x[0] + nom_x[0];
   out_6989025868442055132[1] = delta_x[1] + nom_x[1];
   out_6989025868442055132[2] = delta_x[2] + nom_x[2];
   out_6989025868442055132[3] = delta_x[3] + nom_x[3];
   out_6989025868442055132[4] = delta_x[4] + nom_x[4];
   out_6989025868442055132[5] = delta_x[5] + nom_x[5];
   out_6989025868442055132[6] = delta_x[6] + nom_x[6];
   out_6989025868442055132[7] = delta_x[7] + nom_x[7];
   out_6989025868442055132[8] = delta_x[8] + nom_x[8];
   out_6989025868442055132[9] = delta_x[9] + nom_x[9];
   out_6989025868442055132[10] = delta_x[10] + nom_x[10];
   out_6989025868442055132[11] = delta_x[11] + nom_x[11];
   out_6989025868442055132[12] = delta_x[12] + nom_x[12];
   out_6989025868442055132[13] = delta_x[13] + nom_x[13];
   out_6989025868442055132[14] = delta_x[14] + nom_x[14];
   out_6989025868442055132[15] = delta_x[15] + nom_x[15];
   out_6989025868442055132[16] = delta_x[16] + nom_x[16];
   out_6989025868442055132[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3172938755845140042) {
   out_3172938755845140042[0] = -nom_x[0] + true_x[0];
   out_3172938755845140042[1] = -nom_x[1] + true_x[1];
   out_3172938755845140042[2] = -nom_x[2] + true_x[2];
   out_3172938755845140042[3] = -nom_x[3] + true_x[3];
   out_3172938755845140042[4] = -nom_x[4] + true_x[4];
   out_3172938755845140042[5] = -nom_x[5] + true_x[5];
   out_3172938755845140042[6] = -nom_x[6] + true_x[6];
   out_3172938755845140042[7] = -nom_x[7] + true_x[7];
   out_3172938755845140042[8] = -nom_x[8] + true_x[8];
   out_3172938755845140042[9] = -nom_x[9] + true_x[9];
   out_3172938755845140042[10] = -nom_x[10] + true_x[10];
   out_3172938755845140042[11] = -nom_x[11] + true_x[11];
   out_3172938755845140042[12] = -nom_x[12] + true_x[12];
   out_3172938755845140042[13] = -nom_x[13] + true_x[13];
   out_3172938755845140042[14] = -nom_x[14] + true_x[14];
   out_3172938755845140042[15] = -nom_x[15] + true_x[15];
   out_3172938755845140042[16] = -nom_x[16] + true_x[16];
   out_3172938755845140042[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3225867917449183727) {
   out_3225867917449183727[0] = 1.0;
   out_3225867917449183727[1] = 0.0;
   out_3225867917449183727[2] = 0.0;
   out_3225867917449183727[3] = 0.0;
   out_3225867917449183727[4] = 0.0;
   out_3225867917449183727[5] = 0.0;
   out_3225867917449183727[6] = 0.0;
   out_3225867917449183727[7] = 0.0;
   out_3225867917449183727[8] = 0.0;
   out_3225867917449183727[9] = 0.0;
   out_3225867917449183727[10] = 0.0;
   out_3225867917449183727[11] = 0.0;
   out_3225867917449183727[12] = 0.0;
   out_3225867917449183727[13] = 0.0;
   out_3225867917449183727[14] = 0.0;
   out_3225867917449183727[15] = 0.0;
   out_3225867917449183727[16] = 0.0;
   out_3225867917449183727[17] = 0.0;
   out_3225867917449183727[18] = 0.0;
   out_3225867917449183727[19] = 1.0;
   out_3225867917449183727[20] = 0.0;
   out_3225867917449183727[21] = 0.0;
   out_3225867917449183727[22] = 0.0;
   out_3225867917449183727[23] = 0.0;
   out_3225867917449183727[24] = 0.0;
   out_3225867917449183727[25] = 0.0;
   out_3225867917449183727[26] = 0.0;
   out_3225867917449183727[27] = 0.0;
   out_3225867917449183727[28] = 0.0;
   out_3225867917449183727[29] = 0.0;
   out_3225867917449183727[30] = 0.0;
   out_3225867917449183727[31] = 0.0;
   out_3225867917449183727[32] = 0.0;
   out_3225867917449183727[33] = 0.0;
   out_3225867917449183727[34] = 0.0;
   out_3225867917449183727[35] = 0.0;
   out_3225867917449183727[36] = 0.0;
   out_3225867917449183727[37] = 0.0;
   out_3225867917449183727[38] = 1.0;
   out_3225867917449183727[39] = 0.0;
   out_3225867917449183727[40] = 0.0;
   out_3225867917449183727[41] = 0.0;
   out_3225867917449183727[42] = 0.0;
   out_3225867917449183727[43] = 0.0;
   out_3225867917449183727[44] = 0.0;
   out_3225867917449183727[45] = 0.0;
   out_3225867917449183727[46] = 0.0;
   out_3225867917449183727[47] = 0.0;
   out_3225867917449183727[48] = 0.0;
   out_3225867917449183727[49] = 0.0;
   out_3225867917449183727[50] = 0.0;
   out_3225867917449183727[51] = 0.0;
   out_3225867917449183727[52] = 0.0;
   out_3225867917449183727[53] = 0.0;
   out_3225867917449183727[54] = 0.0;
   out_3225867917449183727[55] = 0.0;
   out_3225867917449183727[56] = 0.0;
   out_3225867917449183727[57] = 1.0;
   out_3225867917449183727[58] = 0.0;
   out_3225867917449183727[59] = 0.0;
   out_3225867917449183727[60] = 0.0;
   out_3225867917449183727[61] = 0.0;
   out_3225867917449183727[62] = 0.0;
   out_3225867917449183727[63] = 0.0;
   out_3225867917449183727[64] = 0.0;
   out_3225867917449183727[65] = 0.0;
   out_3225867917449183727[66] = 0.0;
   out_3225867917449183727[67] = 0.0;
   out_3225867917449183727[68] = 0.0;
   out_3225867917449183727[69] = 0.0;
   out_3225867917449183727[70] = 0.0;
   out_3225867917449183727[71] = 0.0;
   out_3225867917449183727[72] = 0.0;
   out_3225867917449183727[73] = 0.0;
   out_3225867917449183727[74] = 0.0;
   out_3225867917449183727[75] = 0.0;
   out_3225867917449183727[76] = 1.0;
   out_3225867917449183727[77] = 0.0;
   out_3225867917449183727[78] = 0.0;
   out_3225867917449183727[79] = 0.0;
   out_3225867917449183727[80] = 0.0;
   out_3225867917449183727[81] = 0.0;
   out_3225867917449183727[82] = 0.0;
   out_3225867917449183727[83] = 0.0;
   out_3225867917449183727[84] = 0.0;
   out_3225867917449183727[85] = 0.0;
   out_3225867917449183727[86] = 0.0;
   out_3225867917449183727[87] = 0.0;
   out_3225867917449183727[88] = 0.0;
   out_3225867917449183727[89] = 0.0;
   out_3225867917449183727[90] = 0.0;
   out_3225867917449183727[91] = 0.0;
   out_3225867917449183727[92] = 0.0;
   out_3225867917449183727[93] = 0.0;
   out_3225867917449183727[94] = 0.0;
   out_3225867917449183727[95] = 1.0;
   out_3225867917449183727[96] = 0.0;
   out_3225867917449183727[97] = 0.0;
   out_3225867917449183727[98] = 0.0;
   out_3225867917449183727[99] = 0.0;
   out_3225867917449183727[100] = 0.0;
   out_3225867917449183727[101] = 0.0;
   out_3225867917449183727[102] = 0.0;
   out_3225867917449183727[103] = 0.0;
   out_3225867917449183727[104] = 0.0;
   out_3225867917449183727[105] = 0.0;
   out_3225867917449183727[106] = 0.0;
   out_3225867917449183727[107] = 0.0;
   out_3225867917449183727[108] = 0.0;
   out_3225867917449183727[109] = 0.0;
   out_3225867917449183727[110] = 0.0;
   out_3225867917449183727[111] = 0.0;
   out_3225867917449183727[112] = 0.0;
   out_3225867917449183727[113] = 0.0;
   out_3225867917449183727[114] = 1.0;
   out_3225867917449183727[115] = 0.0;
   out_3225867917449183727[116] = 0.0;
   out_3225867917449183727[117] = 0.0;
   out_3225867917449183727[118] = 0.0;
   out_3225867917449183727[119] = 0.0;
   out_3225867917449183727[120] = 0.0;
   out_3225867917449183727[121] = 0.0;
   out_3225867917449183727[122] = 0.0;
   out_3225867917449183727[123] = 0.0;
   out_3225867917449183727[124] = 0.0;
   out_3225867917449183727[125] = 0.0;
   out_3225867917449183727[126] = 0.0;
   out_3225867917449183727[127] = 0.0;
   out_3225867917449183727[128] = 0.0;
   out_3225867917449183727[129] = 0.0;
   out_3225867917449183727[130] = 0.0;
   out_3225867917449183727[131] = 0.0;
   out_3225867917449183727[132] = 0.0;
   out_3225867917449183727[133] = 1.0;
   out_3225867917449183727[134] = 0.0;
   out_3225867917449183727[135] = 0.0;
   out_3225867917449183727[136] = 0.0;
   out_3225867917449183727[137] = 0.0;
   out_3225867917449183727[138] = 0.0;
   out_3225867917449183727[139] = 0.0;
   out_3225867917449183727[140] = 0.0;
   out_3225867917449183727[141] = 0.0;
   out_3225867917449183727[142] = 0.0;
   out_3225867917449183727[143] = 0.0;
   out_3225867917449183727[144] = 0.0;
   out_3225867917449183727[145] = 0.0;
   out_3225867917449183727[146] = 0.0;
   out_3225867917449183727[147] = 0.0;
   out_3225867917449183727[148] = 0.0;
   out_3225867917449183727[149] = 0.0;
   out_3225867917449183727[150] = 0.0;
   out_3225867917449183727[151] = 0.0;
   out_3225867917449183727[152] = 1.0;
   out_3225867917449183727[153] = 0.0;
   out_3225867917449183727[154] = 0.0;
   out_3225867917449183727[155] = 0.0;
   out_3225867917449183727[156] = 0.0;
   out_3225867917449183727[157] = 0.0;
   out_3225867917449183727[158] = 0.0;
   out_3225867917449183727[159] = 0.0;
   out_3225867917449183727[160] = 0.0;
   out_3225867917449183727[161] = 0.0;
   out_3225867917449183727[162] = 0.0;
   out_3225867917449183727[163] = 0.0;
   out_3225867917449183727[164] = 0.0;
   out_3225867917449183727[165] = 0.0;
   out_3225867917449183727[166] = 0.0;
   out_3225867917449183727[167] = 0.0;
   out_3225867917449183727[168] = 0.0;
   out_3225867917449183727[169] = 0.0;
   out_3225867917449183727[170] = 0.0;
   out_3225867917449183727[171] = 1.0;
   out_3225867917449183727[172] = 0.0;
   out_3225867917449183727[173] = 0.0;
   out_3225867917449183727[174] = 0.0;
   out_3225867917449183727[175] = 0.0;
   out_3225867917449183727[176] = 0.0;
   out_3225867917449183727[177] = 0.0;
   out_3225867917449183727[178] = 0.0;
   out_3225867917449183727[179] = 0.0;
   out_3225867917449183727[180] = 0.0;
   out_3225867917449183727[181] = 0.0;
   out_3225867917449183727[182] = 0.0;
   out_3225867917449183727[183] = 0.0;
   out_3225867917449183727[184] = 0.0;
   out_3225867917449183727[185] = 0.0;
   out_3225867917449183727[186] = 0.0;
   out_3225867917449183727[187] = 0.0;
   out_3225867917449183727[188] = 0.0;
   out_3225867917449183727[189] = 0.0;
   out_3225867917449183727[190] = 1.0;
   out_3225867917449183727[191] = 0.0;
   out_3225867917449183727[192] = 0.0;
   out_3225867917449183727[193] = 0.0;
   out_3225867917449183727[194] = 0.0;
   out_3225867917449183727[195] = 0.0;
   out_3225867917449183727[196] = 0.0;
   out_3225867917449183727[197] = 0.0;
   out_3225867917449183727[198] = 0.0;
   out_3225867917449183727[199] = 0.0;
   out_3225867917449183727[200] = 0.0;
   out_3225867917449183727[201] = 0.0;
   out_3225867917449183727[202] = 0.0;
   out_3225867917449183727[203] = 0.0;
   out_3225867917449183727[204] = 0.0;
   out_3225867917449183727[205] = 0.0;
   out_3225867917449183727[206] = 0.0;
   out_3225867917449183727[207] = 0.0;
   out_3225867917449183727[208] = 0.0;
   out_3225867917449183727[209] = 1.0;
   out_3225867917449183727[210] = 0.0;
   out_3225867917449183727[211] = 0.0;
   out_3225867917449183727[212] = 0.0;
   out_3225867917449183727[213] = 0.0;
   out_3225867917449183727[214] = 0.0;
   out_3225867917449183727[215] = 0.0;
   out_3225867917449183727[216] = 0.0;
   out_3225867917449183727[217] = 0.0;
   out_3225867917449183727[218] = 0.0;
   out_3225867917449183727[219] = 0.0;
   out_3225867917449183727[220] = 0.0;
   out_3225867917449183727[221] = 0.0;
   out_3225867917449183727[222] = 0.0;
   out_3225867917449183727[223] = 0.0;
   out_3225867917449183727[224] = 0.0;
   out_3225867917449183727[225] = 0.0;
   out_3225867917449183727[226] = 0.0;
   out_3225867917449183727[227] = 0.0;
   out_3225867917449183727[228] = 1.0;
   out_3225867917449183727[229] = 0.0;
   out_3225867917449183727[230] = 0.0;
   out_3225867917449183727[231] = 0.0;
   out_3225867917449183727[232] = 0.0;
   out_3225867917449183727[233] = 0.0;
   out_3225867917449183727[234] = 0.0;
   out_3225867917449183727[235] = 0.0;
   out_3225867917449183727[236] = 0.0;
   out_3225867917449183727[237] = 0.0;
   out_3225867917449183727[238] = 0.0;
   out_3225867917449183727[239] = 0.0;
   out_3225867917449183727[240] = 0.0;
   out_3225867917449183727[241] = 0.0;
   out_3225867917449183727[242] = 0.0;
   out_3225867917449183727[243] = 0.0;
   out_3225867917449183727[244] = 0.0;
   out_3225867917449183727[245] = 0.0;
   out_3225867917449183727[246] = 0.0;
   out_3225867917449183727[247] = 1.0;
   out_3225867917449183727[248] = 0.0;
   out_3225867917449183727[249] = 0.0;
   out_3225867917449183727[250] = 0.0;
   out_3225867917449183727[251] = 0.0;
   out_3225867917449183727[252] = 0.0;
   out_3225867917449183727[253] = 0.0;
   out_3225867917449183727[254] = 0.0;
   out_3225867917449183727[255] = 0.0;
   out_3225867917449183727[256] = 0.0;
   out_3225867917449183727[257] = 0.0;
   out_3225867917449183727[258] = 0.0;
   out_3225867917449183727[259] = 0.0;
   out_3225867917449183727[260] = 0.0;
   out_3225867917449183727[261] = 0.0;
   out_3225867917449183727[262] = 0.0;
   out_3225867917449183727[263] = 0.0;
   out_3225867917449183727[264] = 0.0;
   out_3225867917449183727[265] = 0.0;
   out_3225867917449183727[266] = 1.0;
   out_3225867917449183727[267] = 0.0;
   out_3225867917449183727[268] = 0.0;
   out_3225867917449183727[269] = 0.0;
   out_3225867917449183727[270] = 0.0;
   out_3225867917449183727[271] = 0.0;
   out_3225867917449183727[272] = 0.0;
   out_3225867917449183727[273] = 0.0;
   out_3225867917449183727[274] = 0.0;
   out_3225867917449183727[275] = 0.0;
   out_3225867917449183727[276] = 0.0;
   out_3225867917449183727[277] = 0.0;
   out_3225867917449183727[278] = 0.0;
   out_3225867917449183727[279] = 0.0;
   out_3225867917449183727[280] = 0.0;
   out_3225867917449183727[281] = 0.0;
   out_3225867917449183727[282] = 0.0;
   out_3225867917449183727[283] = 0.0;
   out_3225867917449183727[284] = 0.0;
   out_3225867917449183727[285] = 1.0;
   out_3225867917449183727[286] = 0.0;
   out_3225867917449183727[287] = 0.0;
   out_3225867917449183727[288] = 0.0;
   out_3225867917449183727[289] = 0.0;
   out_3225867917449183727[290] = 0.0;
   out_3225867917449183727[291] = 0.0;
   out_3225867917449183727[292] = 0.0;
   out_3225867917449183727[293] = 0.0;
   out_3225867917449183727[294] = 0.0;
   out_3225867917449183727[295] = 0.0;
   out_3225867917449183727[296] = 0.0;
   out_3225867917449183727[297] = 0.0;
   out_3225867917449183727[298] = 0.0;
   out_3225867917449183727[299] = 0.0;
   out_3225867917449183727[300] = 0.0;
   out_3225867917449183727[301] = 0.0;
   out_3225867917449183727[302] = 0.0;
   out_3225867917449183727[303] = 0.0;
   out_3225867917449183727[304] = 1.0;
   out_3225867917449183727[305] = 0.0;
   out_3225867917449183727[306] = 0.0;
   out_3225867917449183727[307] = 0.0;
   out_3225867917449183727[308] = 0.0;
   out_3225867917449183727[309] = 0.0;
   out_3225867917449183727[310] = 0.0;
   out_3225867917449183727[311] = 0.0;
   out_3225867917449183727[312] = 0.0;
   out_3225867917449183727[313] = 0.0;
   out_3225867917449183727[314] = 0.0;
   out_3225867917449183727[315] = 0.0;
   out_3225867917449183727[316] = 0.0;
   out_3225867917449183727[317] = 0.0;
   out_3225867917449183727[318] = 0.0;
   out_3225867917449183727[319] = 0.0;
   out_3225867917449183727[320] = 0.0;
   out_3225867917449183727[321] = 0.0;
   out_3225867917449183727[322] = 0.0;
   out_3225867917449183727[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_2533972772359230172) {
   out_2533972772359230172[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_2533972772359230172[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_2533972772359230172[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_2533972772359230172[3] = dt*state[12] + state[3];
   out_2533972772359230172[4] = dt*state[13] + state[4];
   out_2533972772359230172[5] = dt*state[14] + state[5];
   out_2533972772359230172[6] = state[6];
   out_2533972772359230172[7] = state[7];
   out_2533972772359230172[8] = state[8];
   out_2533972772359230172[9] = state[9];
   out_2533972772359230172[10] = state[10];
   out_2533972772359230172[11] = state[11];
   out_2533972772359230172[12] = state[12];
   out_2533972772359230172[13] = state[13];
   out_2533972772359230172[14] = state[14];
   out_2533972772359230172[15] = state[15];
   out_2533972772359230172[16] = state[16];
   out_2533972772359230172[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3663800095301942537) {
   out_3663800095301942537[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3663800095301942537[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3663800095301942537[2] = 0;
   out_3663800095301942537[3] = 0;
   out_3663800095301942537[4] = 0;
   out_3663800095301942537[5] = 0;
   out_3663800095301942537[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3663800095301942537[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3663800095301942537[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3663800095301942537[9] = 0;
   out_3663800095301942537[10] = 0;
   out_3663800095301942537[11] = 0;
   out_3663800095301942537[12] = 0;
   out_3663800095301942537[13] = 0;
   out_3663800095301942537[14] = 0;
   out_3663800095301942537[15] = 0;
   out_3663800095301942537[16] = 0;
   out_3663800095301942537[17] = 0;
   out_3663800095301942537[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3663800095301942537[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3663800095301942537[20] = 0;
   out_3663800095301942537[21] = 0;
   out_3663800095301942537[22] = 0;
   out_3663800095301942537[23] = 0;
   out_3663800095301942537[24] = 0;
   out_3663800095301942537[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3663800095301942537[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3663800095301942537[27] = 0;
   out_3663800095301942537[28] = 0;
   out_3663800095301942537[29] = 0;
   out_3663800095301942537[30] = 0;
   out_3663800095301942537[31] = 0;
   out_3663800095301942537[32] = 0;
   out_3663800095301942537[33] = 0;
   out_3663800095301942537[34] = 0;
   out_3663800095301942537[35] = 0;
   out_3663800095301942537[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3663800095301942537[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3663800095301942537[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3663800095301942537[39] = 0;
   out_3663800095301942537[40] = 0;
   out_3663800095301942537[41] = 0;
   out_3663800095301942537[42] = 0;
   out_3663800095301942537[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3663800095301942537[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3663800095301942537[45] = 0;
   out_3663800095301942537[46] = 0;
   out_3663800095301942537[47] = 0;
   out_3663800095301942537[48] = 0;
   out_3663800095301942537[49] = 0;
   out_3663800095301942537[50] = 0;
   out_3663800095301942537[51] = 0;
   out_3663800095301942537[52] = 0;
   out_3663800095301942537[53] = 0;
   out_3663800095301942537[54] = 0;
   out_3663800095301942537[55] = 0;
   out_3663800095301942537[56] = 0;
   out_3663800095301942537[57] = 1;
   out_3663800095301942537[58] = 0;
   out_3663800095301942537[59] = 0;
   out_3663800095301942537[60] = 0;
   out_3663800095301942537[61] = 0;
   out_3663800095301942537[62] = 0;
   out_3663800095301942537[63] = 0;
   out_3663800095301942537[64] = 0;
   out_3663800095301942537[65] = 0;
   out_3663800095301942537[66] = dt;
   out_3663800095301942537[67] = 0;
   out_3663800095301942537[68] = 0;
   out_3663800095301942537[69] = 0;
   out_3663800095301942537[70] = 0;
   out_3663800095301942537[71] = 0;
   out_3663800095301942537[72] = 0;
   out_3663800095301942537[73] = 0;
   out_3663800095301942537[74] = 0;
   out_3663800095301942537[75] = 0;
   out_3663800095301942537[76] = 1;
   out_3663800095301942537[77] = 0;
   out_3663800095301942537[78] = 0;
   out_3663800095301942537[79] = 0;
   out_3663800095301942537[80] = 0;
   out_3663800095301942537[81] = 0;
   out_3663800095301942537[82] = 0;
   out_3663800095301942537[83] = 0;
   out_3663800095301942537[84] = 0;
   out_3663800095301942537[85] = dt;
   out_3663800095301942537[86] = 0;
   out_3663800095301942537[87] = 0;
   out_3663800095301942537[88] = 0;
   out_3663800095301942537[89] = 0;
   out_3663800095301942537[90] = 0;
   out_3663800095301942537[91] = 0;
   out_3663800095301942537[92] = 0;
   out_3663800095301942537[93] = 0;
   out_3663800095301942537[94] = 0;
   out_3663800095301942537[95] = 1;
   out_3663800095301942537[96] = 0;
   out_3663800095301942537[97] = 0;
   out_3663800095301942537[98] = 0;
   out_3663800095301942537[99] = 0;
   out_3663800095301942537[100] = 0;
   out_3663800095301942537[101] = 0;
   out_3663800095301942537[102] = 0;
   out_3663800095301942537[103] = 0;
   out_3663800095301942537[104] = dt;
   out_3663800095301942537[105] = 0;
   out_3663800095301942537[106] = 0;
   out_3663800095301942537[107] = 0;
   out_3663800095301942537[108] = 0;
   out_3663800095301942537[109] = 0;
   out_3663800095301942537[110] = 0;
   out_3663800095301942537[111] = 0;
   out_3663800095301942537[112] = 0;
   out_3663800095301942537[113] = 0;
   out_3663800095301942537[114] = 1;
   out_3663800095301942537[115] = 0;
   out_3663800095301942537[116] = 0;
   out_3663800095301942537[117] = 0;
   out_3663800095301942537[118] = 0;
   out_3663800095301942537[119] = 0;
   out_3663800095301942537[120] = 0;
   out_3663800095301942537[121] = 0;
   out_3663800095301942537[122] = 0;
   out_3663800095301942537[123] = 0;
   out_3663800095301942537[124] = 0;
   out_3663800095301942537[125] = 0;
   out_3663800095301942537[126] = 0;
   out_3663800095301942537[127] = 0;
   out_3663800095301942537[128] = 0;
   out_3663800095301942537[129] = 0;
   out_3663800095301942537[130] = 0;
   out_3663800095301942537[131] = 0;
   out_3663800095301942537[132] = 0;
   out_3663800095301942537[133] = 1;
   out_3663800095301942537[134] = 0;
   out_3663800095301942537[135] = 0;
   out_3663800095301942537[136] = 0;
   out_3663800095301942537[137] = 0;
   out_3663800095301942537[138] = 0;
   out_3663800095301942537[139] = 0;
   out_3663800095301942537[140] = 0;
   out_3663800095301942537[141] = 0;
   out_3663800095301942537[142] = 0;
   out_3663800095301942537[143] = 0;
   out_3663800095301942537[144] = 0;
   out_3663800095301942537[145] = 0;
   out_3663800095301942537[146] = 0;
   out_3663800095301942537[147] = 0;
   out_3663800095301942537[148] = 0;
   out_3663800095301942537[149] = 0;
   out_3663800095301942537[150] = 0;
   out_3663800095301942537[151] = 0;
   out_3663800095301942537[152] = 1;
   out_3663800095301942537[153] = 0;
   out_3663800095301942537[154] = 0;
   out_3663800095301942537[155] = 0;
   out_3663800095301942537[156] = 0;
   out_3663800095301942537[157] = 0;
   out_3663800095301942537[158] = 0;
   out_3663800095301942537[159] = 0;
   out_3663800095301942537[160] = 0;
   out_3663800095301942537[161] = 0;
   out_3663800095301942537[162] = 0;
   out_3663800095301942537[163] = 0;
   out_3663800095301942537[164] = 0;
   out_3663800095301942537[165] = 0;
   out_3663800095301942537[166] = 0;
   out_3663800095301942537[167] = 0;
   out_3663800095301942537[168] = 0;
   out_3663800095301942537[169] = 0;
   out_3663800095301942537[170] = 0;
   out_3663800095301942537[171] = 1;
   out_3663800095301942537[172] = 0;
   out_3663800095301942537[173] = 0;
   out_3663800095301942537[174] = 0;
   out_3663800095301942537[175] = 0;
   out_3663800095301942537[176] = 0;
   out_3663800095301942537[177] = 0;
   out_3663800095301942537[178] = 0;
   out_3663800095301942537[179] = 0;
   out_3663800095301942537[180] = 0;
   out_3663800095301942537[181] = 0;
   out_3663800095301942537[182] = 0;
   out_3663800095301942537[183] = 0;
   out_3663800095301942537[184] = 0;
   out_3663800095301942537[185] = 0;
   out_3663800095301942537[186] = 0;
   out_3663800095301942537[187] = 0;
   out_3663800095301942537[188] = 0;
   out_3663800095301942537[189] = 0;
   out_3663800095301942537[190] = 1;
   out_3663800095301942537[191] = 0;
   out_3663800095301942537[192] = 0;
   out_3663800095301942537[193] = 0;
   out_3663800095301942537[194] = 0;
   out_3663800095301942537[195] = 0;
   out_3663800095301942537[196] = 0;
   out_3663800095301942537[197] = 0;
   out_3663800095301942537[198] = 0;
   out_3663800095301942537[199] = 0;
   out_3663800095301942537[200] = 0;
   out_3663800095301942537[201] = 0;
   out_3663800095301942537[202] = 0;
   out_3663800095301942537[203] = 0;
   out_3663800095301942537[204] = 0;
   out_3663800095301942537[205] = 0;
   out_3663800095301942537[206] = 0;
   out_3663800095301942537[207] = 0;
   out_3663800095301942537[208] = 0;
   out_3663800095301942537[209] = 1;
   out_3663800095301942537[210] = 0;
   out_3663800095301942537[211] = 0;
   out_3663800095301942537[212] = 0;
   out_3663800095301942537[213] = 0;
   out_3663800095301942537[214] = 0;
   out_3663800095301942537[215] = 0;
   out_3663800095301942537[216] = 0;
   out_3663800095301942537[217] = 0;
   out_3663800095301942537[218] = 0;
   out_3663800095301942537[219] = 0;
   out_3663800095301942537[220] = 0;
   out_3663800095301942537[221] = 0;
   out_3663800095301942537[222] = 0;
   out_3663800095301942537[223] = 0;
   out_3663800095301942537[224] = 0;
   out_3663800095301942537[225] = 0;
   out_3663800095301942537[226] = 0;
   out_3663800095301942537[227] = 0;
   out_3663800095301942537[228] = 1;
   out_3663800095301942537[229] = 0;
   out_3663800095301942537[230] = 0;
   out_3663800095301942537[231] = 0;
   out_3663800095301942537[232] = 0;
   out_3663800095301942537[233] = 0;
   out_3663800095301942537[234] = 0;
   out_3663800095301942537[235] = 0;
   out_3663800095301942537[236] = 0;
   out_3663800095301942537[237] = 0;
   out_3663800095301942537[238] = 0;
   out_3663800095301942537[239] = 0;
   out_3663800095301942537[240] = 0;
   out_3663800095301942537[241] = 0;
   out_3663800095301942537[242] = 0;
   out_3663800095301942537[243] = 0;
   out_3663800095301942537[244] = 0;
   out_3663800095301942537[245] = 0;
   out_3663800095301942537[246] = 0;
   out_3663800095301942537[247] = 1;
   out_3663800095301942537[248] = 0;
   out_3663800095301942537[249] = 0;
   out_3663800095301942537[250] = 0;
   out_3663800095301942537[251] = 0;
   out_3663800095301942537[252] = 0;
   out_3663800095301942537[253] = 0;
   out_3663800095301942537[254] = 0;
   out_3663800095301942537[255] = 0;
   out_3663800095301942537[256] = 0;
   out_3663800095301942537[257] = 0;
   out_3663800095301942537[258] = 0;
   out_3663800095301942537[259] = 0;
   out_3663800095301942537[260] = 0;
   out_3663800095301942537[261] = 0;
   out_3663800095301942537[262] = 0;
   out_3663800095301942537[263] = 0;
   out_3663800095301942537[264] = 0;
   out_3663800095301942537[265] = 0;
   out_3663800095301942537[266] = 1;
   out_3663800095301942537[267] = 0;
   out_3663800095301942537[268] = 0;
   out_3663800095301942537[269] = 0;
   out_3663800095301942537[270] = 0;
   out_3663800095301942537[271] = 0;
   out_3663800095301942537[272] = 0;
   out_3663800095301942537[273] = 0;
   out_3663800095301942537[274] = 0;
   out_3663800095301942537[275] = 0;
   out_3663800095301942537[276] = 0;
   out_3663800095301942537[277] = 0;
   out_3663800095301942537[278] = 0;
   out_3663800095301942537[279] = 0;
   out_3663800095301942537[280] = 0;
   out_3663800095301942537[281] = 0;
   out_3663800095301942537[282] = 0;
   out_3663800095301942537[283] = 0;
   out_3663800095301942537[284] = 0;
   out_3663800095301942537[285] = 1;
   out_3663800095301942537[286] = 0;
   out_3663800095301942537[287] = 0;
   out_3663800095301942537[288] = 0;
   out_3663800095301942537[289] = 0;
   out_3663800095301942537[290] = 0;
   out_3663800095301942537[291] = 0;
   out_3663800095301942537[292] = 0;
   out_3663800095301942537[293] = 0;
   out_3663800095301942537[294] = 0;
   out_3663800095301942537[295] = 0;
   out_3663800095301942537[296] = 0;
   out_3663800095301942537[297] = 0;
   out_3663800095301942537[298] = 0;
   out_3663800095301942537[299] = 0;
   out_3663800095301942537[300] = 0;
   out_3663800095301942537[301] = 0;
   out_3663800095301942537[302] = 0;
   out_3663800095301942537[303] = 0;
   out_3663800095301942537[304] = 1;
   out_3663800095301942537[305] = 0;
   out_3663800095301942537[306] = 0;
   out_3663800095301942537[307] = 0;
   out_3663800095301942537[308] = 0;
   out_3663800095301942537[309] = 0;
   out_3663800095301942537[310] = 0;
   out_3663800095301942537[311] = 0;
   out_3663800095301942537[312] = 0;
   out_3663800095301942537[313] = 0;
   out_3663800095301942537[314] = 0;
   out_3663800095301942537[315] = 0;
   out_3663800095301942537[316] = 0;
   out_3663800095301942537[317] = 0;
   out_3663800095301942537[318] = 0;
   out_3663800095301942537[319] = 0;
   out_3663800095301942537[320] = 0;
   out_3663800095301942537[321] = 0;
   out_3663800095301942537[322] = 0;
   out_3663800095301942537[323] = 1;
}
void h_4(double *state, double *unused, double *out_223446469702120852) {
   out_223446469702120852[0] = state[6] + state[9];
   out_223446469702120852[1] = state[7] + state[10];
   out_223446469702120852[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4324406006264935836) {
   out_4324406006264935836[0] = 0;
   out_4324406006264935836[1] = 0;
   out_4324406006264935836[2] = 0;
   out_4324406006264935836[3] = 0;
   out_4324406006264935836[4] = 0;
   out_4324406006264935836[5] = 0;
   out_4324406006264935836[6] = 1;
   out_4324406006264935836[7] = 0;
   out_4324406006264935836[8] = 0;
   out_4324406006264935836[9] = 1;
   out_4324406006264935836[10] = 0;
   out_4324406006264935836[11] = 0;
   out_4324406006264935836[12] = 0;
   out_4324406006264935836[13] = 0;
   out_4324406006264935836[14] = 0;
   out_4324406006264935836[15] = 0;
   out_4324406006264935836[16] = 0;
   out_4324406006264935836[17] = 0;
   out_4324406006264935836[18] = 0;
   out_4324406006264935836[19] = 0;
   out_4324406006264935836[20] = 0;
   out_4324406006264935836[21] = 0;
   out_4324406006264935836[22] = 0;
   out_4324406006264935836[23] = 0;
   out_4324406006264935836[24] = 0;
   out_4324406006264935836[25] = 1;
   out_4324406006264935836[26] = 0;
   out_4324406006264935836[27] = 0;
   out_4324406006264935836[28] = 1;
   out_4324406006264935836[29] = 0;
   out_4324406006264935836[30] = 0;
   out_4324406006264935836[31] = 0;
   out_4324406006264935836[32] = 0;
   out_4324406006264935836[33] = 0;
   out_4324406006264935836[34] = 0;
   out_4324406006264935836[35] = 0;
   out_4324406006264935836[36] = 0;
   out_4324406006264935836[37] = 0;
   out_4324406006264935836[38] = 0;
   out_4324406006264935836[39] = 0;
   out_4324406006264935836[40] = 0;
   out_4324406006264935836[41] = 0;
   out_4324406006264935836[42] = 0;
   out_4324406006264935836[43] = 0;
   out_4324406006264935836[44] = 1;
   out_4324406006264935836[45] = 0;
   out_4324406006264935836[46] = 0;
   out_4324406006264935836[47] = 1;
   out_4324406006264935836[48] = 0;
   out_4324406006264935836[49] = 0;
   out_4324406006264935836[50] = 0;
   out_4324406006264935836[51] = 0;
   out_4324406006264935836[52] = 0;
   out_4324406006264935836[53] = 0;
}
void h_10(double *state, double *unused, double *out_2753848967308463071) {
   out_2753848967308463071[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2753848967308463071[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2753848967308463071[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1159288756680005657) {
   out_1159288756680005657[0] = 0;
   out_1159288756680005657[1] = 9.8100000000000005*cos(state[1]);
   out_1159288756680005657[2] = 0;
   out_1159288756680005657[3] = 0;
   out_1159288756680005657[4] = -state[8];
   out_1159288756680005657[5] = state[7];
   out_1159288756680005657[6] = 0;
   out_1159288756680005657[7] = state[5];
   out_1159288756680005657[8] = -state[4];
   out_1159288756680005657[9] = 0;
   out_1159288756680005657[10] = 0;
   out_1159288756680005657[11] = 0;
   out_1159288756680005657[12] = 1;
   out_1159288756680005657[13] = 0;
   out_1159288756680005657[14] = 0;
   out_1159288756680005657[15] = 1;
   out_1159288756680005657[16] = 0;
   out_1159288756680005657[17] = 0;
   out_1159288756680005657[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1159288756680005657[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1159288756680005657[20] = 0;
   out_1159288756680005657[21] = state[8];
   out_1159288756680005657[22] = 0;
   out_1159288756680005657[23] = -state[6];
   out_1159288756680005657[24] = -state[5];
   out_1159288756680005657[25] = 0;
   out_1159288756680005657[26] = state[3];
   out_1159288756680005657[27] = 0;
   out_1159288756680005657[28] = 0;
   out_1159288756680005657[29] = 0;
   out_1159288756680005657[30] = 0;
   out_1159288756680005657[31] = 1;
   out_1159288756680005657[32] = 0;
   out_1159288756680005657[33] = 0;
   out_1159288756680005657[34] = 1;
   out_1159288756680005657[35] = 0;
   out_1159288756680005657[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1159288756680005657[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1159288756680005657[38] = 0;
   out_1159288756680005657[39] = -state[7];
   out_1159288756680005657[40] = state[6];
   out_1159288756680005657[41] = 0;
   out_1159288756680005657[42] = state[4];
   out_1159288756680005657[43] = -state[3];
   out_1159288756680005657[44] = 0;
   out_1159288756680005657[45] = 0;
   out_1159288756680005657[46] = 0;
   out_1159288756680005657[47] = 0;
   out_1159288756680005657[48] = 0;
   out_1159288756680005657[49] = 0;
   out_1159288756680005657[50] = 1;
   out_1159288756680005657[51] = 0;
   out_1159288756680005657[52] = 0;
   out_1159288756680005657[53] = 1;
}
void h_13(double *state, double *unused, double *out_4379566868646893753) {
   out_4379566868646893753[0] = state[3];
   out_4379566868646893753[1] = state[4];
   out_4379566868646893753[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8158161469567459860) {
   out_8158161469567459860[0] = 0;
   out_8158161469567459860[1] = 0;
   out_8158161469567459860[2] = 0;
   out_8158161469567459860[3] = 1;
   out_8158161469567459860[4] = 0;
   out_8158161469567459860[5] = 0;
   out_8158161469567459860[6] = 0;
   out_8158161469567459860[7] = 0;
   out_8158161469567459860[8] = 0;
   out_8158161469567459860[9] = 0;
   out_8158161469567459860[10] = 0;
   out_8158161469567459860[11] = 0;
   out_8158161469567459860[12] = 0;
   out_8158161469567459860[13] = 0;
   out_8158161469567459860[14] = 0;
   out_8158161469567459860[15] = 0;
   out_8158161469567459860[16] = 0;
   out_8158161469567459860[17] = 0;
   out_8158161469567459860[18] = 0;
   out_8158161469567459860[19] = 0;
   out_8158161469567459860[20] = 0;
   out_8158161469567459860[21] = 0;
   out_8158161469567459860[22] = 1;
   out_8158161469567459860[23] = 0;
   out_8158161469567459860[24] = 0;
   out_8158161469567459860[25] = 0;
   out_8158161469567459860[26] = 0;
   out_8158161469567459860[27] = 0;
   out_8158161469567459860[28] = 0;
   out_8158161469567459860[29] = 0;
   out_8158161469567459860[30] = 0;
   out_8158161469567459860[31] = 0;
   out_8158161469567459860[32] = 0;
   out_8158161469567459860[33] = 0;
   out_8158161469567459860[34] = 0;
   out_8158161469567459860[35] = 0;
   out_8158161469567459860[36] = 0;
   out_8158161469567459860[37] = 0;
   out_8158161469567459860[38] = 0;
   out_8158161469567459860[39] = 0;
   out_8158161469567459860[40] = 0;
   out_8158161469567459860[41] = 1;
   out_8158161469567459860[42] = 0;
   out_8158161469567459860[43] = 0;
   out_8158161469567459860[44] = 0;
   out_8158161469567459860[45] = 0;
   out_8158161469567459860[46] = 0;
   out_8158161469567459860[47] = 0;
   out_8158161469567459860[48] = 0;
   out_8158161469567459860[49] = 0;
   out_8158161469567459860[50] = 0;
   out_8158161469567459860[51] = 0;
   out_8158161469567459860[52] = 0;
   out_8158161469567459860[53] = 0;
}
void h_14(double *state, double *unused, double *out_8438977474921151403) {
   out_8438977474921151403[0] = state[6];
   out_8438977474921151403[1] = state[7];
   out_8438977474921151403[2] = state[8];
}
void H_14(double *state, double *unused, double *out_7407194438560308132) {
   out_7407194438560308132[0] = 0;
   out_7407194438560308132[1] = 0;
   out_7407194438560308132[2] = 0;
   out_7407194438560308132[3] = 0;
   out_7407194438560308132[4] = 0;
   out_7407194438560308132[5] = 0;
   out_7407194438560308132[6] = 1;
   out_7407194438560308132[7] = 0;
   out_7407194438560308132[8] = 0;
   out_7407194438560308132[9] = 0;
   out_7407194438560308132[10] = 0;
   out_7407194438560308132[11] = 0;
   out_7407194438560308132[12] = 0;
   out_7407194438560308132[13] = 0;
   out_7407194438560308132[14] = 0;
   out_7407194438560308132[15] = 0;
   out_7407194438560308132[16] = 0;
   out_7407194438560308132[17] = 0;
   out_7407194438560308132[18] = 0;
   out_7407194438560308132[19] = 0;
   out_7407194438560308132[20] = 0;
   out_7407194438560308132[21] = 0;
   out_7407194438560308132[22] = 0;
   out_7407194438560308132[23] = 0;
   out_7407194438560308132[24] = 0;
   out_7407194438560308132[25] = 1;
   out_7407194438560308132[26] = 0;
   out_7407194438560308132[27] = 0;
   out_7407194438560308132[28] = 0;
   out_7407194438560308132[29] = 0;
   out_7407194438560308132[30] = 0;
   out_7407194438560308132[31] = 0;
   out_7407194438560308132[32] = 0;
   out_7407194438560308132[33] = 0;
   out_7407194438560308132[34] = 0;
   out_7407194438560308132[35] = 0;
   out_7407194438560308132[36] = 0;
   out_7407194438560308132[37] = 0;
   out_7407194438560308132[38] = 0;
   out_7407194438560308132[39] = 0;
   out_7407194438560308132[40] = 0;
   out_7407194438560308132[41] = 0;
   out_7407194438560308132[42] = 0;
   out_7407194438560308132[43] = 0;
   out_7407194438560308132[44] = 1;
   out_7407194438560308132[45] = 0;
   out_7407194438560308132[46] = 0;
   out_7407194438560308132[47] = 0;
   out_7407194438560308132[48] = 0;
   out_7407194438560308132[49] = 0;
   out_7407194438560308132[50] = 0;
   out_7407194438560308132[51] = 0;
   out_7407194438560308132[52] = 0;
   out_7407194438560308132[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_6989025868442055132) {
  err_fun(nom_x, delta_x, out_6989025868442055132);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3172938755845140042) {
  inv_err_fun(nom_x, true_x, out_3172938755845140042);
}
void pose_H_mod_fun(double *state, double *out_3225867917449183727) {
  H_mod_fun(state, out_3225867917449183727);
}
void pose_f_fun(double *state, double dt, double *out_2533972772359230172) {
  f_fun(state,  dt, out_2533972772359230172);
}
void pose_F_fun(double *state, double dt, double *out_3663800095301942537) {
  F_fun(state,  dt, out_3663800095301942537);
}
void pose_h_4(double *state, double *unused, double *out_223446469702120852) {
  h_4(state, unused, out_223446469702120852);
}
void pose_H_4(double *state, double *unused, double *out_4324406006264935836) {
  H_4(state, unused, out_4324406006264935836);
}
void pose_h_10(double *state, double *unused, double *out_2753848967308463071) {
  h_10(state, unused, out_2753848967308463071);
}
void pose_H_10(double *state, double *unused, double *out_1159288756680005657) {
  H_10(state, unused, out_1159288756680005657);
}
void pose_h_13(double *state, double *unused, double *out_4379566868646893753) {
  h_13(state, unused, out_4379566868646893753);
}
void pose_H_13(double *state, double *unused, double *out_8158161469567459860) {
  H_13(state, unused, out_8158161469567459860);
}
void pose_h_14(double *state, double *unused, double *out_8438977474921151403) {
  h_14(state, unused, out_8438977474921151403);
}
void pose_H_14(double *state, double *unused, double *out_7407194438560308132) {
  H_14(state, unused, out_7407194438560308132);
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
