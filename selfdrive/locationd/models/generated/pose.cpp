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
void err_fun(double *nom_x, double *delta_x, double *out_607652414837750033) {
   out_607652414837750033[0] = delta_x[0] + nom_x[0];
   out_607652414837750033[1] = delta_x[1] + nom_x[1];
   out_607652414837750033[2] = delta_x[2] + nom_x[2];
   out_607652414837750033[3] = delta_x[3] + nom_x[3];
   out_607652414837750033[4] = delta_x[4] + nom_x[4];
   out_607652414837750033[5] = delta_x[5] + nom_x[5];
   out_607652414837750033[6] = delta_x[6] + nom_x[6];
   out_607652414837750033[7] = delta_x[7] + nom_x[7];
   out_607652414837750033[8] = delta_x[8] + nom_x[8];
   out_607652414837750033[9] = delta_x[9] + nom_x[9];
   out_607652414837750033[10] = delta_x[10] + nom_x[10];
   out_607652414837750033[11] = delta_x[11] + nom_x[11];
   out_607652414837750033[12] = delta_x[12] + nom_x[12];
   out_607652414837750033[13] = delta_x[13] + nom_x[13];
   out_607652414837750033[14] = delta_x[14] + nom_x[14];
   out_607652414837750033[15] = delta_x[15] + nom_x[15];
   out_607652414837750033[16] = delta_x[16] + nom_x[16];
   out_607652414837750033[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4916314802659989276) {
   out_4916314802659989276[0] = -nom_x[0] + true_x[0];
   out_4916314802659989276[1] = -nom_x[1] + true_x[1];
   out_4916314802659989276[2] = -nom_x[2] + true_x[2];
   out_4916314802659989276[3] = -nom_x[3] + true_x[3];
   out_4916314802659989276[4] = -nom_x[4] + true_x[4];
   out_4916314802659989276[5] = -nom_x[5] + true_x[5];
   out_4916314802659989276[6] = -nom_x[6] + true_x[6];
   out_4916314802659989276[7] = -nom_x[7] + true_x[7];
   out_4916314802659989276[8] = -nom_x[8] + true_x[8];
   out_4916314802659989276[9] = -nom_x[9] + true_x[9];
   out_4916314802659989276[10] = -nom_x[10] + true_x[10];
   out_4916314802659989276[11] = -nom_x[11] + true_x[11];
   out_4916314802659989276[12] = -nom_x[12] + true_x[12];
   out_4916314802659989276[13] = -nom_x[13] + true_x[13];
   out_4916314802659989276[14] = -nom_x[14] + true_x[14];
   out_4916314802659989276[15] = -nom_x[15] + true_x[15];
   out_4916314802659989276[16] = -nom_x[16] + true_x[16];
   out_4916314802659989276[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_1887258982449267152) {
   out_1887258982449267152[0] = 1.0;
   out_1887258982449267152[1] = 0.0;
   out_1887258982449267152[2] = 0.0;
   out_1887258982449267152[3] = 0.0;
   out_1887258982449267152[4] = 0.0;
   out_1887258982449267152[5] = 0.0;
   out_1887258982449267152[6] = 0.0;
   out_1887258982449267152[7] = 0.0;
   out_1887258982449267152[8] = 0.0;
   out_1887258982449267152[9] = 0.0;
   out_1887258982449267152[10] = 0.0;
   out_1887258982449267152[11] = 0.0;
   out_1887258982449267152[12] = 0.0;
   out_1887258982449267152[13] = 0.0;
   out_1887258982449267152[14] = 0.0;
   out_1887258982449267152[15] = 0.0;
   out_1887258982449267152[16] = 0.0;
   out_1887258982449267152[17] = 0.0;
   out_1887258982449267152[18] = 0.0;
   out_1887258982449267152[19] = 1.0;
   out_1887258982449267152[20] = 0.0;
   out_1887258982449267152[21] = 0.0;
   out_1887258982449267152[22] = 0.0;
   out_1887258982449267152[23] = 0.0;
   out_1887258982449267152[24] = 0.0;
   out_1887258982449267152[25] = 0.0;
   out_1887258982449267152[26] = 0.0;
   out_1887258982449267152[27] = 0.0;
   out_1887258982449267152[28] = 0.0;
   out_1887258982449267152[29] = 0.0;
   out_1887258982449267152[30] = 0.0;
   out_1887258982449267152[31] = 0.0;
   out_1887258982449267152[32] = 0.0;
   out_1887258982449267152[33] = 0.0;
   out_1887258982449267152[34] = 0.0;
   out_1887258982449267152[35] = 0.0;
   out_1887258982449267152[36] = 0.0;
   out_1887258982449267152[37] = 0.0;
   out_1887258982449267152[38] = 1.0;
   out_1887258982449267152[39] = 0.0;
   out_1887258982449267152[40] = 0.0;
   out_1887258982449267152[41] = 0.0;
   out_1887258982449267152[42] = 0.0;
   out_1887258982449267152[43] = 0.0;
   out_1887258982449267152[44] = 0.0;
   out_1887258982449267152[45] = 0.0;
   out_1887258982449267152[46] = 0.0;
   out_1887258982449267152[47] = 0.0;
   out_1887258982449267152[48] = 0.0;
   out_1887258982449267152[49] = 0.0;
   out_1887258982449267152[50] = 0.0;
   out_1887258982449267152[51] = 0.0;
   out_1887258982449267152[52] = 0.0;
   out_1887258982449267152[53] = 0.0;
   out_1887258982449267152[54] = 0.0;
   out_1887258982449267152[55] = 0.0;
   out_1887258982449267152[56] = 0.0;
   out_1887258982449267152[57] = 1.0;
   out_1887258982449267152[58] = 0.0;
   out_1887258982449267152[59] = 0.0;
   out_1887258982449267152[60] = 0.0;
   out_1887258982449267152[61] = 0.0;
   out_1887258982449267152[62] = 0.0;
   out_1887258982449267152[63] = 0.0;
   out_1887258982449267152[64] = 0.0;
   out_1887258982449267152[65] = 0.0;
   out_1887258982449267152[66] = 0.0;
   out_1887258982449267152[67] = 0.0;
   out_1887258982449267152[68] = 0.0;
   out_1887258982449267152[69] = 0.0;
   out_1887258982449267152[70] = 0.0;
   out_1887258982449267152[71] = 0.0;
   out_1887258982449267152[72] = 0.0;
   out_1887258982449267152[73] = 0.0;
   out_1887258982449267152[74] = 0.0;
   out_1887258982449267152[75] = 0.0;
   out_1887258982449267152[76] = 1.0;
   out_1887258982449267152[77] = 0.0;
   out_1887258982449267152[78] = 0.0;
   out_1887258982449267152[79] = 0.0;
   out_1887258982449267152[80] = 0.0;
   out_1887258982449267152[81] = 0.0;
   out_1887258982449267152[82] = 0.0;
   out_1887258982449267152[83] = 0.0;
   out_1887258982449267152[84] = 0.0;
   out_1887258982449267152[85] = 0.0;
   out_1887258982449267152[86] = 0.0;
   out_1887258982449267152[87] = 0.0;
   out_1887258982449267152[88] = 0.0;
   out_1887258982449267152[89] = 0.0;
   out_1887258982449267152[90] = 0.0;
   out_1887258982449267152[91] = 0.0;
   out_1887258982449267152[92] = 0.0;
   out_1887258982449267152[93] = 0.0;
   out_1887258982449267152[94] = 0.0;
   out_1887258982449267152[95] = 1.0;
   out_1887258982449267152[96] = 0.0;
   out_1887258982449267152[97] = 0.0;
   out_1887258982449267152[98] = 0.0;
   out_1887258982449267152[99] = 0.0;
   out_1887258982449267152[100] = 0.0;
   out_1887258982449267152[101] = 0.0;
   out_1887258982449267152[102] = 0.0;
   out_1887258982449267152[103] = 0.0;
   out_1887258982449267152[104] = 0.0;
   out_1887258982449267152[105] = 0.0;
   out_1887258982449267152[106] = 0.0;
   out_1887258982449267152[107] = 0.0;
   out_1887258982449267152[108] = 0.0;
   out_1887258982449267152[109] = 0.0;
   out_1887258982449267152[110] = 0.0;
   out_1887258982449267152[111] = 0.0;
   out_1887258982449267152[112] = 0.0;
   out_1887258982449267152[113] = 0.0;
   out_1887258982449267152[114] = 1.0;
   out_1887258982449267152[115] = 0.0;
   out_1887258982449267152[116] = 0.0;
   out_1887258982449267152[117] = 0.0;
   out_1887258982449267152[118] = 0.0;
   out_1887258982449267152[119] = 0.0;
   out_1887258982449267152[120] = 0.0;
   out_1887258982449267152[121] = 0.0;
   out_1887258982449267152[122] = 0.0;
   out_1887258982449267152[123] = 0.0;
   out_1887258982449267152[124] = 0.0;
   out_1887258982449267152[125] = 0.0;
   out_1887258982449267152[126] = 0.0;
   out_1887258982449267152[127] = 0.0;
   out_1887258982449267152[128] = 0.0;
   out_1887258982449267152[129] = 0.0;
   out_1887258982449267152[130] = 0.0;
   out_1887258982449267152[131] = 0.0;
   out_1887258982449267152[132] = 0.0;
   out_1887258982449267152[133] = 1.0;
   out_1887258982449267152[134] = 0.0;
   out_1887258982449267152[135] = 0.0;
   out_1887258982449267152[136] = 0.0;
   out_1887258982449267152[137] = 0.0;
   out_1887258982449267152[138] = 0.0;
   out_1887258982449267152[139] = 0.0;
   out_1887258982449267152[140] = 0.0;
   out_1887258982449267152[141] = 0.0;
   out_1887258982449267152[142] = 0.0;
   out_1887258982449267152[143] = 0.0;
   out_1887258982449267152[144] = 0.0;
   out_1887258982449267152[145] = 0.0;
   out_1887258982449267152[146] = 0.0;
   out_1887258982449267152[147] = 0.0;
   out_1887258982449267152[148] = 0.0;
   out_1887258982449267152[149] = 0.0;
   out_1887258982449267152[150] = 0.0;
   out_1887258982449267152[151] = 0.0;
   out_1887258982449267152[152] = 1.0;
   out_1887258982449267152[153] = 0.0;
   out_1887258982449267152[154] = 0.0;
   out_1887258982449267152[155] = 0.0;
   out_1887258982449267152[156] = 0.0;
   out_1887258982449267152[157] = 0.0;
   out_1887258982449267152[158] = 0.0;
   out_1887258982449267152[159] = 0.0;
   out_1887258982449267152[160] = 0.0;
   out_1887258982449267152[161] = 0.0;
   out_1887258982449267152[162] = 0.0;
   out_1887258982449267152[163] = 0.0;
   out_1887258982449267152[164] = 0.0;
   out_1887258982449267152[165] = 0.0;
   out_1887258982449267152[166] = 0.0;
   out_1887258982449267152[167] = 0.0;
   out_1887258982449267152[168] = 0.0;
   out_1887258982449267152[169] = 0.0;
   out_1887258982449267152[170] = 0.0;
   out_1887258982449267152[171] = 1.0;
   out_1887258982449267152[172] = 0.0;
   out_1887258982449267152[173] = 0.0;
   out_1887258982449267152[174] = 0.0;
   out_1887258982449267152[175] = 0.0;
   out_1887258982449267152[176] = 0.0;
   out_1887258982449267152[177] = 0.0;
   out_1887258982449267152[178] = 0.0;
   out_1887258982449267152[179] = 0.0;
   out_1887258982449267152[180] = 0.0;
   out_1887258982449267152[181] = 0.0;
   out_1887258982449267152[182] = 0.0;
   out_1887258982449267152[183] = 0.0;
   out_1887258982449267152[184] = 0.0;
   out_1887258982449267152[185] = 0.0;
   out_1887258982449267152[186] = 0.0;
   out_1887258982449267152[187] = 0.0;
   out_1887258982449267152[188] = 0.0;
   out_1887258982449267152[189] = 0.0;
   out_1887258982449267152[190] = 1.0;
   out_1887258982449267152[191] = 0.0;
   out_1887258982449267152[192] = 0.0;
   out_1887258982449267152[193] = 0.0;
   out_1887258982449267152[194] = 0.0;
   out_1887258982449267152[195] = 0.0;
   out_1887258982449267152[196] = 0.0;
   out_1887258982449267152[197] = 0.0;
   out_1887258982449267152[198] = 0.0;
   out_1887258982449267152[199] = 0.0;
   out_1887258982449267152[200] = 0.0;
   out_1887258982449267152[201] = 0.0;
   out_1887258982449267152[202] = 0.0;
   out_1887258982449267152[203] = 0.0;
   out_1887258982449267152[204] = 0.0;
   out_1887258982449267152[205] = 0.0;
   out_1887258982449267152[206] = 0.0;
   out_1887258982449267152[207] = 0.0;
   out_1887258982449267152[208] = 0.0;
   out_1887258982449267152[209] = 1.0;
   out_1887258982449267152[210] = 0.0;
   out_1887258982449267152[211] = 0.0;
   out_1887258982449267152[212] = 0.0;
   out_1887258982449267152[213] = 0.0;
   out_1887258982449267152[214] = 0.0;
   out_1887258982449267152[215] = 0.0;
   out_1887258982449267152[216] = 0.0;
   out_1887258982449267152[217] = 0.0;
   out_1887258982449267152[218] = 0.0;
   out_1887258982449267152[219] = 0.0;
   out_1887258982449267152[220] = 0.0;
   out_1887258982449267152[221] = 0.0;
   out_1887258982449267152[222] = 0.0;
   out_1887258982449267152[223] = 0.0;
   out_1887258982449267152[224] = 0.0;
   out_1887258982449267152[225] = 0.0;
   out_1887258982449267152[226] = 0.0;
   out_1887258982449267152[227] = 0.0;
   out_1887258982449267152[228] = 1.0;
   out_1887258982449267152[229] = 0.0;
   out_1887258982449267152[230] = 0.0;
   out_1887258982449267152[231] = 0.0;
   out_1887258982449267152[232] = 0.0;
   out_1887258982449267152[233] = 0.0;
   out_1887258982449267152[234] = 0.0;
   out_1887258982449267152[235] = 0.0;
   out_1887258982449267152[236] = 0.0;
   out_1887258982449267152[237] = 0.0;
   out_1887258982449267152[238] = 0.0;
   out_1887258982449267152[239] = 0.0;
   out_1887258982449267152[240] = 0.0;
   out_1887258982449267152[241] = 0.0;
   out_1887258982449267152[242] = 0.0;
   out_1887258982449267152[243] = 0.0;
   out_1887258982449267152[244] = 0.0;
   out_1887258982449267152[245] = 0.0;
   out_1887258982449267152[246] = 0.0;
   out_1887258982449267152[247] = 1.0;
   out_1887258982449267152[248] = 0.0;
   out_1887258982449267152[249] = 0.0;
   out_1887258982449267152[250] = 0.0;
   out_1887258982449267152[251] = 0.0;
   out_1887258982449267152[252] = 0.0;
   out_1887258982449267152[253] = 0.0;
   out_1887258982449267152[254] = 0.0;
   out_1887258982449267152[255] = 0.0;
   out_1887258982449267152[256] = 0.0;
   out_1887258982449267152[257] = 0.0;
   out_1887258982449267152[258] = 0.0;
   out_1887258982449267152[259] = 0.0;
   out_1887258982449267152[260] = 0.0;
   out_1887258982449267152[261] = 0.0;
   out_1887258982449267152[262] = 0.0;
   out_1887258982449267152[263] = 0.0;
   out_1887258982449267152[264] = 0.0;
   out_1887258982449267152[265] = 0.0;
   out_1887258982449267152[266] = 1.0;
   out_1887258982449267152[267] = 0.0;
   out_1887258982449267152[268] = 0.0;
   out_1887258982449267152[269] = 0.0;
   out_1887258982449267152[270] = 0.0;
   out_1887258982449267152[271] = 0.0;
   out_1887258982449267152[272] = 0.0;
   out_1887258982449267152[273] = 0.0;
   out_1887258982449267152[274] = 0.0;
   out_1887258982449267152[275] = 0.0;
   out_1887258982449267152[276] = 0.0;
   out_1887258982449267152[277] = 0.0;
   out_1887258982449267152[278] = 0.0;
   out_1887258982449267152[279] = 0.0;
   out_1887258982449267152[280] = 0.0;
   out_1887258982449267152[281] = 0.0;
   out_1887258982449267152[282] = 0.0;
   out_1887258982449267152[283] = 0.0;
   out_1887258982449267152[284] = 0.0;
   out_1887258982449267152[285] = 1.0;
   out_1887258982449267152[286] = 0.0;
   out_1887258982449267152[287] = 0.0;
   out_1887258982449267152[288] = 0.0;
   out_1887258982449267152[289] = 0.0;
   out_1887258982449267152[290] = 0.0;
   out_1887258982449267152[291] = 0.0;
   out_1887258982449267152[292] = 0.0;
   out_1887258982449267152[293] = 0.0;
   out_1887258982449267152[294] = 0.0;
   out_1887258982449267152[295] = 0.0;
   out_1887258982449267152[296] = 0.0;
   out_1887258982449267152[297] = 0.0;
   out_1887258982449267152[298] = 0.0;
   out_1887258982449267152[299] = 0.0;
   out_1887258982449267152[300] = 0.0;
   out_1887258982449267152[301] = 0.0;
   out_1887258982449267152[302] = 0.0;
   out_1887258982449267152[303] = 0.0;
   out_1887258982449267152[304] = 1.0;
   out_1887258982449267152[305] = 0.0;
   out_1887258982449267152[306] = 0.0;
   out_1887258982449267152[307] = 0.0;
   out_1887258982449267152[308] = 0.0;
   out_1887258982449267152[309] = 0.0;
   out_1887258982449267152[310] = 0.0;
   out_1887258982449267152[311] = 0.0;
   out_1887258982449267152[312] = 0.0;
   out_1887258982449267152[313] = 0.0;
   out_1887258982449267152[314] = 0.0;
   out_1887258982449267152[315] = 0.0;
   out_1887258982449267152[316] = 0.0;
   out_1887258982449267152[317] = 0.0;
   out_1887258982449267152[318] = 0.0;
   out_1887258982449267152[319] = 0.0;
   out_1887258982449267152[320] = 0.0;
   out_1887258982449267152[321] = 0.0;
   out_1887258982449267152[322] = 0.0;
   out_1887258982449267152[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_2681276694689160944) {
   out_2681276694689160944[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_2681276694689160944[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_2681276694689160944[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_2681276694689160944[3] = dt*state[12] + state[3];
   out_2681276694689160944[4] = dt*state[13] + state[4];
   out_2681276694689160944[5] = dt*state[14] + state[5];
   out_2681276694689160944[6] = state[6];
   out_2681276694689160944[7] = state[7];
   out_2681276694689160944[8] = state[8];
   out_2681276694689160944[9] = state[9];
   out_2681276694689160944[10] = state[10];
   out_2681276694689160944[11] = state[11];
   out_2681276694689160944[12] = state[12];
   out_2681276694689160944[13] = state[13];
   out_2681276694689160944[14] = state[14];
   out_2681276694689160944[15] = state[15];
   out_2681276694689160944[16] = state[16];
   out_2681276694689160944[17] = state[17];
}
void F_fun(double *state, double dt, double *out_6011099377550215473) {
   out_6011099377550215473[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6011099377550215473[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6011099377550215473[2] = 0;
   out_6011099377550215473[3] = 0;
   out_6011099377550215473[4] = 0;
   out_6011099377550215473[5] = 0;
   out_6011099377550215473[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6011099377550215473[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6011099377550215473[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6011099377550215473[9] = 0;
   out_6011099377550215473[10] = 0;
   out_6011099377550215473[11] = 0;
   out_6011099377550215473[12] = 0;
   out_6011099377550215473[13] = 0;
   out_6011099377550215473[14] = 0;
   out_6011099377550215473[15] = 0;
   out_6011099377550215473[16] = 0;
   out_6011099377550215473[17] = 0;
   out_6011099377550215473[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6011099377550215473[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6011099377550215473[20] = 0;
   out_6011099377550215473[21] = 0;
   out_6011099377550215473[22] = 0;
   out_6011099377550215473[23] = 0;
   out_6011099377550215473[24] = 0;
   out_6011099377550215473[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6011099377550215473[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6011099377550215473[27] = 0;
   out_6011099377550215473[28] = 0;
   out_6011099377550215473[29] = 0;
   out_6011099377550215473[30] = 0;
   out_6011099377550215473[31] = 0;
   out_6011099377550215473[32] = 0;
   out_6011099377550215473[33] = 0;
   out_6011099377550215473[34] = 0;
   out_6011099377550215473[35] = 0;
   out_6011099377550215473[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6011099377550215473[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6011099377550215473[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6011099377550215473[39] = 0;
   out_6011099377550215473[40] = 0;
   out_6011099377550215473[41] = 0;
   out_6011099377550215473[42] = 0;
   out_6011099377550215473[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6011099377550215473[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6011099377550215473[45] = 0;
   out_6011099377550215473[46] = 0;
   out_6011099377550215473[47] = 0;
   out_6011099377550215473[48] = 0;
   out_6011099377550215473[49] = 0;
   out_6011099377550215473[50] = 0;
   out_6011099377550215473[51] = 0;
   out_6011099377550215473[52] = 0;
   out_6011099377550215473[53] = 0;
   out_6011099377550215473[54] = 0;
   out_6011099377550215473[55] = 0;
   out_6011099377550215473[56] = 0;
   out_6011099377550215473[57] = 1;
   out_6011099377550215473[58] = 0;
   out_6011099377550215473[59] = 0;
   out_6011099377550215473[60] = 0;
   out_6011099377550215473[61] = 0;
   out_6011099377550215473[62] = 0;
   out_6011099377550215473[63] = 0;
   out_6011099377550215473[64] = 0;
   out_6011099377550215473[65] = 0;
   out_6011099377550215473[66] = dt;
   out_6011099377550215473[67] = 0;
   out_6011099377550215473[68] = 0;
   out_6011099377550215473[69] = 0;
   out_6011099377550215473[70] = 0;
   out_6011099377550215473[71] = 0;
   out_6011099377550215473[72] = 0;
   out_6011099377550215473[73] = 0;
   out_6011099377550215473[74] = 0;
   out_6011099377550215473[75] = 0;
   out_6011099377550215473[76] = 1;
   out_6011099377550215473[77] = 0;
   out_6011099377550215473[78] = 0;
   out_6011099377550215473[79] = 0;
   out_6011099377550215473[80] = 0;
   out_6011099377550215473[81] = 0;
   out_6011099377550215473[82] = 0;
   out_6011099377550215473[83] = 0;
   out_6011099377550215473[84] = 0;
   out_6011099377550215473[85] = dt;
   out_6011099377550215473[86] = 0;
   out_6011099377550215473[87] = 0;
   out_6011099377550215473[88] = 0;
   out_6011099377550215473[89] = 0;
   out_6011099377550215473[90] = 0;
   out_6011099377550215473[91] = 0;
   out_6011099377550215473[92] = 0;
   out_6011099377550215473[93] = 0;
   out_6011099377550215473[94] = 0;
   out_6011099377550215473[95] = 1;
   out_6011099377550215473[96] = 0;
   out_6011099377550215473[97] = 0;
   out_6011099377550215473[98] = 0;
   out_6011099377550215473[99] = 0;
   out_6011099377550215473[100] = 0;
   out_6011099377550215473[101] = 0;
   out_6011099377550215473[102] = 0;
   out_6011099377550215473[103] = 0;
   out_6011099377550215473[104] = dt;
   out_6011099377550215473[105] = 0;
   out_6011099377550215473[106] = 0;
   out_6011099377550215473[107] = 0;
   out_6011099377550215473[108] = 0;
   out_6011099377550215473[109] = 0;
   out_6011099377550215473[110] = 0;
   out_6011099377550215473[111] = 0;
   out_6011099377550215473[112] = 0;
   out_6011099377550215473[113] = 0;
   out_6011099377550215473[114] = 1;
   out_6011099377550215473[115] = 0;
   out_6011099377550215473[116] = 0;
   out_6011099377550215473[117] = 0;
   out_6011099377550215473[118] = 0;
   out_6011099377550215473[119] = 0;
   out_6011099377550215473[120] = 0;
   out_6011099377550215473[121] = 0;
   out_6011099377550215473[122] = 0;
   out_6011099377550215473[123] = 0;
   out_6011099377550215473[124] = 0;
   out_6011099377550215473[125] = 0;
   out_6011099377550215473[126] = 0;
   out_6011099377550215473[127] = 0;
   out_6011099377550215473[128] = 0;
   out_6011099377550215473[129] = 0;
   out_6011099377550215473[130] = 0;
   out_6011099377550215473[131] = 0;
   out_6011099377550215473[132] = 0;
   out_6011099377550215473[133] = 1;
   out_6011099377550215473[134] = 0;
   out_6011099377550215473[135] = 0;
   out_6011099377550215473[136] = 0;
   out_6011099377550215473[137] = 0;
   out_6011099377550215473[138] = 0;
   out_6011099377550215473[139] = 0;
   out_6011099377550215473[140] = 0;
   out_6011099377550215473[141] = 0;
   out_6011099377550215473[142] = 0;
   out_6011099377550215473[143] = 0;
   out_6011099377550215473[144] = 0;
   out_6011099377550215473[145] = 0;
   out_6011099377550215473[146] = 0;
   out_6011099377550215473[147] = 0;
   out_6011099377550215473[148] = 0;
   out_6011099377550215473[149] = 0;
   out_6011099377550215473[150] = 0;
   out_6011099377550215473[151] = 0;
   out_6011099377550215473[152] = 1;
   out_6011099377550215473[153] = 0;
   out_6011099377550215473[154] = 0;
   out_6011099377550215473[155] = 0;
   out_6011099377550215473[156] = 0;
   out_6011099377550215473[157] = 0;
   out_6011099377550215473[158] = 0;
   out_6011099377550215473[159] = 0;
   out_6011099377550215473[160] = 0;
   out_6011099377550215473[161] = 0;
   out_6011099377550215473[162] = 0;
   out_6011099377550215473[163] = 0;
   out_6011099377550215473[164] = 0;
   out_6011099377550215473[165] = 0;
   out_6011099377550215473[166] = 0;
   out_6011099377550215473[167] = 0;
   out_6011099377550215473[168] = 0;
   out_6011099377550215473[169] = 0;
   out_6011099377550215473[170] = 0;
   out_6011099377550215473[171] = 1;
   out_6011099377550215473[172] = 0;
   out_6011099377550215473[173] = 0;
   out_6011099377550215473[174] = 0;
   out_6011099377550215473[175] = 0;
   out_6011099377550215473[176] = 0;
   out_6011099377550215473[177] = 0;
   out_6011099377550215473[178] = 0;
   out_6011099377550215473[179] = 0;
   out_6011099377550215473[180] = 0;
   out_6011099377550215473[181] = 0;
   out_6011099377550215473[182] = 0;
   out_6011099377550215473[183] = 0;
   out_6011099377550215473[184] = 0;
   out_6011099377550215473[185] = 0;
   out_6011099377550215473[186] = 0;
   out_6011099377550215473[187] = 0;
   out_6011099377550215473[188] = 0;
   out_6011099377550215473[189] = 0;
   out_6011099377550215473[190] = 1;
   out_6011099377550215473[191] = 0;
   out_6011099377550215473[192] = 0;
   out_6011099377550215473[193] = 0;
   out_6011099377550215473[194] = 0;
   out_6011099377550215473[195] = 0;
   out_6011099377550215473[196] = 0;
   out_6011099377550215473[197] = 0;
   out_6011099377550215473[198] = 0;
   out_6011099377550215473[199] = 0;
   out_6011099377550215473[200] = 0;
   out_6011099377550215473[201] = 0;
   out_6011099377550215473[202] = 0;
   out_6011099377550215473[203] = 0;
   out_6011099377550215473[204] = 0;
   out_6011099377550215473[205] = 0;
   out_6011099377550215473[206] = 0;
   out_6011099377550215473[207] = 0;
   out_6011099377550215473[208] = 0;
   out_6011099377550215473[209] = 1;
   out_6011099377550215473[210] = 0;
   out_6011099377550215473[211] = 0;
   out_6011099377550215473[212] = 0;
   out_6011099377550215473[213] = 0;
   out_6011099377550215473[214] = 0;
   out_6011099377550215473[215] = 0;
   out_6011099377550215473[216] = 0;
   out_6011099377550215473[217] = 0;
   out_6011099377550215473[218] = 0;
   out_6011099377550215473[219] = 0;
   out_6011099377550215473[220] = 0;
   out_6011099377550215473[221] = 0;
   out_6011099377550215473[222] = 0;
   out_6011099377550215473[223] = 0;
   out_6011099377550215473[224] = 0;
   out_6011099377550215473[225] = 0;
   out_6011099377550215473[226] = 0;
   out_6011099377550215473[227] = 0;
   out_6011099377550215473[228] = 1;
   out_6011099377550215473[229] = 0;
   out_6011099377550215473[230] = 0;
   out_6011099377550215473[231] = 0;
   out_6011099377550215473[232] = 0;
   out_6011099377550215473[233] = 0;
   out_6011099377550215473[234] = 0;
   out_6011099377550215473[235] = 0;
   out_6011099377550215473[236] = 0;
   out_6011099377550215473[237] = 0;
   out_6011099377550215473[238] = 0;
   out_6011099377550215473[239] = 0;
   out_6011099377550215473[240] = 0;
   out_6011099377550215473[241] = 0;
   out_6011099377550215473[242] = 0;
   out_6011099377550215473[243] = 0;
   out_6011099377550215473[244] = 0;
   out_6011099377550215473[245] = 0;
   out_6011099377550215473[246] = 0;
   out_6011099377550215473[247] = 1;
   out_6011099377550215473[248] = 0;
   out_6011099377550215473[249] = 0;
   out_6011099377550215473[250] = 0;
   out_6011099377550215473[251] = 0;
   out_6011099377550215473[252] = 0;
   out_6011099377550215473[253] = 0;
   out_6011099377550215473[254] = 0;
   out_6011099377550215473[255] = 0;
   out_6011099377550215473[256] = 0;
   out_6011099377550215473[257] = 0;
   out_6011099377550215473[258] = 0;
   out_6011099377550215473[259] = 0;
   out_6011099377550215473[260] = 0;
   out_6011099377550215473[261] = 0;
   out_6011099377550215473[262] = 0;
   out_6011099377550215473[263] = 0;
   out_6011099377550215473[264] = 0;
   out_6011099377550215473[265] = 0;
   out_6011099377550215473[266] = 1;
   out_6011099377550215473[267] = 0;
   out_6011099377550215473[268] = 0;
   out_6011099377550215473[269] = 0;
   out_6011099377550215473[270] = 0;
   out_6011099377550215473[271] = 0;
   out_6011099377550215473[272] = 0;
   out_6011099377550215473[273] = 0;
   out_6011099377550215473[274] = 0;
   out_6011099377550215473[275] = 0;
   out_6011099377550215473[276] = 0;
   out_6011099377550215473[277] = 0;
   out_6011099377550215473[278] = 0;
   out_6011099377550215473[279] = 0;
   out_6011099377550215473[280] = 0;
   out_6011099377550215473[281] = 0;
   out_6011099377550215473[282] = 0;
   out_6011099377550215473[283] = 0;
   out_6011099377550215473[284] = 0;
   out_6011099377550215473[285] = 1;
   out_6011099377550215473[286] = 0;
   out_6011099377550215473[287] = 0;
   out_6011099377550215473[288] = 0;
   out_6011099377550215473[289] = 0;
   out_6011099377550215473[290] = 0;
   out_6011099377550215473[291] = 0;
   out_6011099377550215473[292] = 0;
   out_6011099377550215473[293] = 0;
   out_6011099377550215473[294] = 0;
   out_6011099377550215473[295] = 0;
   out_6011099377550215473[296] = 0;
   out_6011099377550215473[297] = 0;
   out_6011099377550215473[298] = 0;
   out_6011099377550215473[299] = 0;
   out_6011099377550215473[300] = 0;
   out_6011099377550215473[301] = 0;
   out_6011099377550215473[302] = 0;
   out_6011099377550215473[303] = 0;
   out_6011099377550215473[304] = 1;
   out_6011099377550215473[305] = 0;
   out_6011099377550215473[306] = 0;
   out_6011099377550215473[307] = 0;
   out_6011099377550215473[308] = 0;
   out_6011099377550215473[309] = 0;
   out_6011099377550215473[310] = 0;
   out_6011099377550215473[311] = 0;
   out_6011099377550215473[312] = 0;
   out_6011099377550215473[313] = 0;
   out_6011099377550215473[314] = 0;
   out_6011099377550215473[315] = 0;
   out_6011099377550215473[316] = 0;
   out_6011099377550215473[317] = 0;
   out_6011099377550215473[318] = 0;
   out_6011099377550215473[319] = 0;
   out_6011099377550215473[320] = 0;
   out_6011099377550215473[321] = 0;
   out_6011099377550215473[322] = 0;
   out_6011099377550215473[323] = 1;
}
void h_4(double *state, double *unused, double *out_5478412217433972001) {
   out_5478412217433972001[0] = state[6] + state[9];
   out_5478412217433972001[1] = state[7] + state[10];
   out_5478412217433972001[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3085206464332165256) {
   out_3085206464332165256[0] = 0;
   out_3085206464332165256[1] = 0;
   out_3085206464332165256[2] = 0;
   out_3085206464332165256[3] = 0;
   out_3085206464332165256[4] = 0;
   out_3085206464332165256[5] = 0;
   out_3085206464332165256[6] = 1;
   out_3085206464332165256[7] = 0;
   out_3085206464332165256[8] = 0;
   out_3085206464332165256[9] = 1;
   out_3085206464332165256[10] = 0;
   out_3085206464332165256[11] = 0;
   out_3085206464332165256[12] = 0;
   out_3085206464332165256[13] = 0;
   out_3085206464332165256[14] = 0;
   out_3085206464332165256[15] = 0;
   out_3085206464332165256[16] = 0;
   out_3085206464332165256[17] = 0;
   out_3085206464332165256[18] = 0;
   out_3085206464332165256[19] = 0;
   out_3085206464332165256[20] = 0;
   out_3085206464332165256[21] = 0;
   out_3085206464332165256[22] = 0;
   out_3085206464332165256[23] = 0;
   out_3085206464332165256[24] = 0;
   out_3085206464332165256[25] = 1;
   out_3085206464332165256[26] = 0;
   out_3085206464332165256[27] = 0;
   out_3085206464332165256[28] = 1;
   out_3085206464332165256[29] = 0;
   out_3085206464332165256[30] = 0;
   out_3085206464332165256[31] = 0;
   out_3085206464332165256[32] = 0;
   out_3085206464332165256[33] = 0;
   out_3085206464332165256[34] = 0;
   out_3085206464332165256[35] = 0;
   out_3085206464332165256[36] = 0;
   out_3085206464332165256[37] = 0;
   out_3085206464332165256[38] = 0;
   out_3085206464332165256[39] = 0;
   out_3085206464332165256[40] = 0;
   out_3085206464332165256[41] = 0;
   out_3085206464332165256[42] = 0;
   out_3085206464332165256[43] = 0;
   out_3085206464332165256[44] = 1;
   out_3085206464332165256[45] = 0;
   out_3085206464332165256[46] = 0;
   out_3085206464332165256[47] = 1;
   out_3085206464332165256[48] = 0;
   out_3085206464332165256[49] = 0;
   out_3085206464332165256[50] = 0;
   out_3085206464332165256[51] = 0;
   out_3085206464332165256[52] = 0;
   out_3085206464332165256[53] = 0;
}
void h_10(double *state, double *unused, double *out_5861828944145935890) {
   out_5861828944145935890[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5861828944145935890[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5861828944145935890[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1460352446362739633) {
   out_1460352446362739633[0] = 0;
   out_1460352446362739633[1] = 9.8100000000000005*cos(state[1]);
   out_1460352446362739633[2] = 0;
   out_1460352446362739633[3] = 0;
   out_1460352446362739633[4] = -state[8];
   out_1460352446362739633[5] = state[7];
   out_1460352446362739633[6] = 0;
   out_1460352446362739633[7] = state[5];
   out_1460352446362739633[8] = -state[4];
   out_1460352446362739633[9] = 0;
   out_1460352446362739633[10] = 0;
   out_1460352446362739633[11] = 0;
   out_1460352446362739633[12] = 1;
   out_1460352446362739633[13] = 0;
   out_1460352446362739633[14] = 0;
   out_1460352446362739633[15] = 1;
   out_1460352446362739633[16] = 0;
   out_1460352446362739633[17] = 0;
   out_1460352446362739633[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1460352446362739633[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1460352446362739633[20] = 0;
   out_1460352446362739633[21] = state[8];
   out_1460352446362739633[22] = 0;
   out_1460352446362739633[23] = -state[6];
   out_1460352446362739633[24] = -state[5];
   out_1460352446362739633[25] = 0;
   out_1460352446362739633[26] = state[3];
   out_1460352446362739633[27] = 0;
   out_1460352446362739633[28] = 0;
   out_1460352446362739633[29] = 0;
   out_1460352446362739633[30] = 0;
   out_1460352446362739633[31] = 1;
   out_1460352446362739633[32] = 0;
   out_1460352446362739633[33] = 0;
   out_1460352446362739633[34] = 1;
   out_1460352446362739633[35] = 0;
   out_1460352446362739633[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1460352446362739633[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1460352446362739633[38] = 0;
   out_1460352446362739633[39] = -state[7];
   out_1460352446362739633[40] = state[6];
   out_1460352446362739633[41] = 0;
   out_1460352446362739633[42] = state[4];
   out_1460352446362739633[43] = -state[3];
   out_1460352446362739633[44] = 0;
   out_1460352446362739633[45] = 0;
   out_1460352446362739633[46] = 0;
   out_1460352446362739633[47] = 0;
   out_1460352446362739633[48] = 0;
   out_1460352446362739633[49] = 0;
   out_1460352446362739633[50] = 1;
   out_1460352446362739633[51] = 0;
   out_1460352446362739633[52] = 0;
   out_1460352446362739633[53] = 1;
}
void h_13(double *state, double *unused, double *out_6845339361600931042) {
   out_6845339361600931042[0] = state[3];
   out_6845339361600931042[1] = state[4];
   out_6845339361600931042[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6297480289664498057) {
   out_6297480289664498057[0] = 0;
   out_6297480289664498057[1] = 0;
   out_6297480289664498057[2] = 0;
   out_6297480289664498057[3] = 1;
   out_6297480289664498057[4] = 0;
   out_6297480289664498057[5] = 0;
   out_6297480289664498057[6] = 0;
   out_6297480289664498057[7] = 0;
   out_6297480289664498057[8] = 0;
   out_6297480289664498057[9] = 0;
   out_6297480289664498057[10] = 0;
   out_6297480289664498057[11] = 0;
   out_6297480289664498057[12] = 0;
   out_6297480289664498057[13] = 0;
   out_6297480289664498057[14] = 0;
   out_6297480289664498057[15] = 0;
   out_6297480289664498057[16] = 0;
   out_6297480289664498057[17] = 0;
   out_6297480289664498057[18] = 0;
   out_6297480289664498057[19] = 0;
   out_6297480289664498057[20] = 0;
   out_6297480289664498057[21] = 0;
   out_6297480289664498057[22] = 1;
   out_6297480289664498057[23] = 0;
   out_6297480289664498057[24] = 0;
   out_6297480289664498057[25] = 0;
   out_6297480289664498057[26] = 0;
   out_6297480289664498057[27] = 0;
   out_6297480289664498057[28] = 0;
   out_6297480289664498057[29] = 0;
   out_6297480289664498057[30] = 0;
   out_6297480289664498057[31] = 0;
   out_6297480289664498057[32] = 0;
   out_6297480289664498057[33] = 0;
   out_6297480289664498057[34] = 0;
   out_6297480289664498057[35] = 0;
   out_6297480289664498057[36] = 0;
   out_6297480289664498057[37] = 0;
   out_6297480289664498057[38] = 0;
   out_6297480289664498057[39] = 0;
   out_6297480289664498057[40] = 0;
   out_6297480289664498057[41] = 1;
   out_6297480289664498057[42] = 0;
   out_6297480289664498057[43] = 0;
   out_6297480289664498057[44] = 0;
   out_6297480289664498057[45] = 0;
   out_6297480289664498057[46] = 0;
   out_6297480289664498057[47] = 0;
   out_6297480289664498057[48] = 0;
   out_6297480289664498057[49] = 0;
   out_6297480289664498057[50] = 0;
   out_6297480289664498057[51] = 0;
   out_6297480289664498057[52] = 0;
   out_6297480289664498057[53] = 0;
}
void h_14(double *state, double *unused, double *out_6355309693456612665) {
   out_6355309693456612665[0] = state[6];
   out_6355309693456612665[1] = state[7];
   out_6355309693456612665[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2418032036792960) {
   out_2418032036792960[0] = 0;
   out_2418032036792960[1] = 0;
   out_2418032036792960[2] = 0;
   out_2418032036792960[3] = 0;
   out_2418032036792960[4] = 0;
   out_2418032036792960[5] = 0;
   out_2418032036792960[6] = 1;
   out_2418032036792960[7] = 0;
   out_2418032036792960[8] = 0;
   out_2418032036792960[9] = 0;
   out_2418032036792960[10] = 0;
   out_2418032036792960[11] = 0;
   out_2418032036792960[12] = 0;
   out_2418032036792960[13] = 0;
   out_2418032036792960[14] = 0;
   out_2418032036792960[15] = 0;
   out_2418032036792960[16] = 0;
   out_2418032036792960[17] = 0;
   out_2418032036792960[18] = 0;
   out_2418032036792960[19] = 0;
   out_2418032036792960[20] = 0;
   out_2418032036792960[21] = 0;
   out_2418032036792960[22] = 0;
   out_2418032036792960[23] = 0;
   out_2418032036792960[24] = 0;
   out_2418032036792960[25] = 1;
   out_2418032036792960[26] = 0;
   out_2418032036792960[27] = 0;
   out_2418032036792960[28] = 0;
   out_2418032036792960[29] = 0;
   out_2418032036792960[30] = 0;
   out_2418032036792960[31] = 0;
   out_2418032036792960[32] = 0;
   out_2418032036792960[33] = 0;
   out_2418032036792960[34] = 0;
   out_2418032036792960[35] = 0;
   out_2418032036792960[36] = 0;
   out_2418032036792960[37] = 0;
   out_2418032036792960[38] = 0;
   out_2418032036792960[39] = 0;
   out_2418032036792960[40] = 0;
   out_2418032036792960[41] = 0;
   out_2418032036792960[42] = 0;
   out_2418032036792960[43] = 0;
   out_2418032036792960[44] = 1;
   out_2418032036792960[45] = 0;
   out_2418032036792960[46] = 0;
   out_2418032036792960[47] = 0;
   out_2418032036792960[48] = 0;
   out_2418032036792960[49] = 0;
   out_2418032036792960[50] = 0;
   out_2418032036792960[51] = 0;
   out_2418032036792960[52] = 0;
   out_2418032036792960[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_607652414837750033) {
  err_fun(nom_x, delta_x, out_607652414837750033);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4916314802659989276) {
  inv_err_fun(nom_x, true_x, out_4916314802659989276);
}
void pose_H_mod_fun(double *state, double *out_1887258982449267152) {
  H_mod_fun(state, out_1887258982449267152);
}
void pose_f_fun(double *state, double dt, double *out_2681276694689160944) {
  f_fun(state,  dt, out_2681276694689160944);
}
void pose_F_fun(double *state, double dt, double *out_6011099377550215473) {
  F_fun(state,  dt, out_6011099377550215473);
}
void pose_h_4(double *state, double *unused, double *out_5478412217433972001) {
  h_4(state, unused, out_5478412217433972001);
}
void pose_H_4(double *state, double *unused, double *out_3085206464332165256) {
  H_4(state, unused, out_3085206464332165256);
}
void pose_h_10(double *state, double *unused, double *out_5861828944145935890) {
  h_10(state, unused, out_5861828944145935890);
}
void pose_H_10(double *state, double *unused, double *out_1460352446362739633) {
  H_10(state, unused, out_1460352446362739633);
}
void pose_h_13(double *state, double *unused, double *out_6845339361600931042) {
  h_13(state, unused, out_6845339361600931042);
}
void pose_H_13(double *state, double *unused, double *out_6297480289664498057) {
  H_13(state, unused, out_6297480289664498057);
}
void pose_h_14(double *state, double *unused, double *out_6355309693456612665) {
  h_14(state, unused, out_6355309693456612665);
}
void pose_H_14(double *state, double *unused, double *out_2418032036792960) {
  H_14(state, unused, out_2418032036792960);
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
