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
void err_fun(double *nom_x, double *delta_x, double *out_9170572944906816852) {
   out_9170572944906816852[0] = delta_x[0] + nom_x[0];
   out_9170572944906816852[1] = delta_x[1] + nom_x[1];
   out_9170572944906816852[2] = delta_x[2] + nom_x[2];
   out_9170572944906816852[3] = delta_x[3] + nom_x[3];
   out_9170572944906816852[4] = delta_x[4] + nom_x[4];
   out_9170572944906816852[5] = delta_x[5] + nom_x[5];
   out_9170572944906816852[6] = delta_x[6] + nom_x[6];
   out_9170572944906816852[7] = delta_x[7] + nom_x[7];
   out_9170572944906816852[8] = delta_x[8] + nom_x[8];
   out_9170572944906816852[9] = delta_x[9] + nom_x[9];
   out_9170572944906816852[10] = delta_x[10] + nom_x[10];
   out_9170572944906816852[11] = delta_x[11] + nom_x[11];
   out_9170572944906816852[12] = delta_x[12] + nom_x[12];
   out_9170572944906816852[13] = delta_x[13] + nom_x[13];
   out_9170572944906816852[14] = delta_x[14] + nom_x[14];
   out_9170572944906816852[15] = delta_x[15] + nom_x[15];
   out_9170572944906816852[16] = delta_x[16] + nom_x[16];
   out_9170572944906816852[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4867215415263963768) {
   out_4867215415263963768[0] = -nom_x[0] + true_x[0];
   out_4867215415263963768[1] = -nom_x[1] + true_x[1];
   out_4867215415263963768[2] = -nom_x[2] + true_x[2];
   out_4867215415263963768[3] = -nom_x[3] + true_x[3];
   out_4867215415263963768[4] = -nom_x[4] + true_x[4];
   out_4867215415263963768[5] = -nom_x[5] + true_x[5];
   out_4867215415263963768[6] = -nom_x[6] + true_x[6];
   out_4867215415263963768[7] = -nom_x[7] + true_x[7];
   out_4867215415263963768[8] = -nom_x[8] + true_x[8];
   out_4867215415263963768[9] = -nom_x[9] + true_x[9];
   out_4867215415263963768[10] = -nom_x[10] + true_x[10];
   out_4867215415263963768[11] = -nom_x[11] + true_x[11];
   out_4867215415263963768[12] = -nom_x[12] + true_x[12];
   out_4867215415263963768[13] = -nom_x[13] + true_x[13];
   out_4867215415263963768[14] = -nom_x[14] + true_x[14];
   out_4867215415263963768[15] = -nom_x[15] + true_x[15];
   out_4867215415263963768[16] = -nom_x[16] + true_x[16];
   out_4867215415263963768[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_1396735664605592698) {
   out_1396735664605592698[0] = 1.0;
   out_1396735664605592698[1] = 0.0;
   out_1396735664605592698[2] = 0.0;
   out_1396735664605592698[3] = 0.0;
   out_1396735664605592698[4] = 0.0;
   out_1396735664605592698[5] = 0.0;
   out_1396735664605592698[6] = 0.0;
   out_1396735664605592698[7] = 0.0;
   out_1396735664605592698[8] = 0.0;
   out_1396735664605592698[9] = 0.0;
   out_1396735664605592698[10] = 0.0;
   out_1396735664605592698[11] = 0.0;
   out_1396735664605592698[12] = 0.0;
   out_1396735664605592698[13] = 0.0;
   out_1396735664605592698[14] = 0.0;
   out_1396735664605592698[15] = 0.0;
   out_1396735664605592698[16] = 0.0;
   out_1396735664605592698[17] = 0.0;
   out_1396735664605592698[18] = 0.0;
   out_1396735664605592698[19] = 1.0;
   out_1396735664605592698[20] = 0.0;
   out_1396735664605592698[21] = 0.0;
   out_1396735664605592698[22] = 0.0;
   out_1396735664605592698[23] = 0.0;
   out_1396735664605592698[24] = 0.0;
   out_1396735664605592698[25] = 0.0;
   out_1396735664605592698[26] = 0.0;
   out_1396735664605592698[27] = 0.0;
   out_1396735664605592698[28] = 0.0;
   out_1396735664605592698[29] = 0.0;
   out_1396735664605592698[30] = 0.0;
   out_1396735664605592698[31] = 0.0;
   out_1396735664605592698[32] = 0.0;
   out_1396735664605592698[33] = 0.0;
   out_1396735664605592698[34] = 0.0;
   out_1396735664605592698[35] = 0.0;
   out_1396735664605592698[36] = 0.0;
   out_1396735664605592698[37] = 0.0;
   out_1396735664605592698[38] = 1.0;
   out_1396735664605592698[39] = 0.0;
   out_1396735664605592698[40] = 0.0;
   out_1396735664605592698[41] = 0.0;
   out_1396735664605592698[42] = 0.0;
   out_1396735664605592698[43] = 0.0;
   out_1396735664605592698[44] = 0.0;
   out_1396735664605592698[45] = 0.0;
   out_1396735664605592698[46] = 0.0;
   out_1396735664605592698[47] = 0.0;
   out_1396735664605592698[48] = 0.0;
   out_1396735664605592698[49] = 0.0;
   out_1396735664605592698[50] = 0.0;
   out_1396735664605592698[51] = 0.0;
   out_1396735664605592698[52] = 0.0;
   out_1396735664605592698[53] = 0.0;
   out_1396735664605592698[54] = 0.0;
   out_1396735664605592698[55] = 0.0;
   out_1396735664605592698[56] = 0.0;
   out_1396735664605592698[57] = 1.0;
   out_1396735664605592698[58] = 0.0;
   out_1396735664605592698[59] = 0.0;
   out_1396735664605592698[60] = 0.0;
   out_1396735664605592698[61] = 0.0;
   out_1396735664605592698[62] = 0.0;
   out_1396735664605592698[63] = 0.0;
   out_1396735664605592698[64] = 0.0;
   out_1396735664605592698[65] = 0.0;
   out_1396735664605592698[66] = 0.0;
   out_1396735664605592698[67] = 0.0;
   out_1396735664605592698[68] = 0.0;
   out_1396735664605592698[69] = 0.0;
   out_1396735664605592698[70] = 0.0;
   out_1396735664605592698[71] = 0.0;
   out_1396735664605592698[72] = 0.0;
   out_1396735664605592698[73] = 0.0;
   out_1396735664605592698[74] = 0.0;
   out_1396735664605592698[75] = 0.0;
   out_1396735664605592698[76] = 1.0;
   out_1396735664605592698[77] = 0.0;
   out_1396735664605592698[78] = 0.0;
   out_1396735664605592698[79] = 0.0;
   out_1396735664605592698[80] = 0.0;
   out_1396735664605592698[81] = 0.0;
   out_1396735664605592698[82] = 0.0;
   out_1396735664605592698[83] = 0.0;
   out_1396735664605592698[84] = 0.0;
   out_1396735664605592698[85] = 0.0;
   out_1396735664605592698[86] = 0.0;
   out_1396735664605592698[87] = 0.0;
   out_1396735664605592698[88] = 0.0;
   out_1396735664605592698[89] = 0.0;
   out_1396735664605592698[90] = 0.0;
   out_1396735664605592698[91] = 0.0;
   out_1396735664605592698[92] = 0.0;
   out_1396735664605592698[93] = 0.0;
   out_1396735664605592698[94] = 0.0;
   out_1396735664605592698[95] = 1.0;
   out_1396735664605592698[96] = 0.0;
   out_1396735664605592698[97] = 0.0;
   out_1396735664605592698[98] = 0.0;
   out_1396735664605592698[99] = 0.0;
   out_1396735664605592698[100] = 0.0;
   out_1396735664605592698[101] = 0.0;
   out_1396735664605592698[102] = 0.0;
   out_1396735664605592698[103] = 0.0;
   out_1396735664605592698[104] = 0.0;
   out_1396735664605592698[105] = 0.0;
   out_1396735664605592698[106] = 0.0;
   out_1396735664605592698[107] = 0.0;
   out_1396735664605592698[108] = 0.0;
   out_1396735664605592698[109] = 0.0;
   out_1396735664605592698[110] = 0.0;
   out_1396735664605592698[111] = 0.0;
   out_1396735664605592698[112] = 0.0;
   out_1396735664605592698[113] = 0.0;
   out_1396735664605592698[114] = 1.0;
   out_1396735664605592698[115] = 0.0;
   out_1396735664605592698[116] = 0.0;
   out_1396735664605592698[117] = 0.0;
   out_1396735664605592698[118] = 0.0;
   out_1396735664605592698[119] = 0.0;
   out_1396735664605592698[120] = 0.0;
   out_1396735664605592698[121] = 0.0;
   out_1396735664605592698[122] = 0.0;
   out_1396735664605592698[123] = 0.0;
   out_1396735664605592698[124] = 0.0;
   out_1396735664605592698[125] = 0.0;
   out_1396735664605592698[126] = 0.0;
   out_1396735664605592698[127] = 0.0;
   out_1396735664605592698[128] = 0.0;
   out_1396735664605592698[129] = 0.0;
   out_1396735664605592698[130] = 0.0;
   out_1396735664605592698[131] = 0.0;
   out_1396735664605592698[132] = 0.0;
   out_1396735664605592698[133] = 1.0;
   out_1396735664605592698[134] = 0.0;
   out_1396735664605592698[135] = 0.0;
   out_1396735664605592698[136] = 0.0;
   out_1396735664605592698[137] = 0.0;
   out_1396735664605592698[138] = 0.0;
   out_1396735664605592698[139] = 0.0;
   out_1396735664605592698[140] = 0.0;
   out_1396735664605592698[141] = 0.0;
   out_1396735664605592698[142] = 0.0;
   out_1396735664605592698[143] = 0.0;
   out_1396735664605592698[144] = 0.0;
   out_1396735664605592698[145] = 0.0;
   out_1396735664605592698[146] = 0.0;
   out_1396735664605592698[147] = 0.0;
   out_1396735664605592698[148] = 0.0;
   out_1396735664605592698[149] = 0.0;
   out_1396735664605592698[150] = 0.0;
   out_1396735664605592698[151] = 0.0;
   out_1396735664605592698[152] = 1.0;
   out_1396735664605592698[153] = 0.0;
   out_1396735664605592698[154] = 0.0;
   out_1396735664605592698[155] = 0.0;
   out_1396735664605592698[156] = 0.0;
   out_1396735664605592698[157] = 0.0;
   out_1396735664605592698[158] = 0.0;
   out_1396735664605592698[159] = 0.0;
   out_1396735664605592698[160] = 0.0;
   out_1396735664605592698[161] = 0.0;
   out_1396735664605592698[162] = 0.0;
   out_1396735664605592698[163] = 0.0;
   out_1396735664605592698[164] = 0.0;
   out_1396735664605592698[165] = 0.0;
   out_1396735664605592698[166] = 0.0;
   out_1396735664605592698[167] = 0.0;
   out_1396735664605592698[168] = 0.0;
   out_1396735664605592698[169] = 0.0;
   out_1396735664605592698[170] = 0.0;
   out_1396735664605592698[171] = 1.0;
   out_1396735664605592698[172] = 0.0;
   out_1396735664605592698[173] = 0.0;
   out_1396735664605592698[174] = 0.0;
   out_1396735664605592698[175] = 0.0;
   out_1396735664605592698[176] = 0.0;
   out_1396735664605592698[177] = 0.0;
   out_1396735664605592698[178] = 0.0;
   out_1396735664605592698[179] = 0.0;
   out_1396735664605592698[180] = 0.0;
   out_1396735664605592698[181] = 0.0;
   out_1396735664605592698[182] = 0.0;
   out_1396735664605592698[183] = 0.0;
   out_1396735664605592698[184] = 0.0;
   out_1396735664605592698[185] = 0.0;
   out_1396735664605592698[186] = 0.0;
   out_1396735664605592698[187] = 0.0;
   out_1396735664605592698[188] = 0.0;
   out_1396735664605592698[189] = 0.0;
   out_1396735664605592698[190] = 1.0;
   out_1396735664605592698[191] = 0.0;
   out_1396735664605592698[192] = 0.0;
   out_1396735664605592698[193] = 0.0;
   out_1396735664605592698[194] = 0.0;
   out_1396735664605592698[195] = 0.0;
   out_1396735664605592698[196] = 0.0;
   out_1396735664605592698[197] = 0.0;
   out_1396735664605592698[198] = 0.0;
   out_1396735664605592698[199] = 0.0;
   out_1396735664605592698[200] = 0.0;
   out_1396735664605592698[201] = 0.0;
   out_1396735664605592698[202] = 0.0;
   out_1396735664605592698[203] = 0.0;
   out_1396735664605592698[204] = 0.0;
   out_1396735664605592698[205] = 0.0;
   out_1396735664605592698[206] = 0.0;
   out_1396735664605592698[207] = 0.0;
   out_1396735664605592698[208] = 0.0;
   out_1396735664605592698[209] = 1.0;
   out_1396735664605592698[210] = 0.0;
   out_1396735664605592698[211] = 0.0;
   out_1396735664605592698[212] = 0.0;
   out_1396735664605592698[213] = 0.0;
   out_1396735664605592698[214] = 0.0;
   out_1396735664605592698[215] = 0.0;
   out_1396735664605592698[216] = 0.0;
   out_1396735664605592698[217] = 0.0;
   out_1396735664605592698[218] = 0.0;
   out_1396735664605592698[219] = 0.0;
   out_1396735664605592698[220] = 0.0;
   out_1396735664605592698[221] = 0.0;
   out_1396735664605592698[222] = 0.0;
   out_1396735664605592698[223] = 0.0;
   out_1396735664605592698[224] = 0.0;
   out_1396735664605592698[225] = 0.0;
   out_1396735664605592698[226] = 0.0;
   out_1396735664605592698[227] = 0.0;
   out_1396735664605592698[228] = 1.0;
   out_1396735664605592698[229] = 0.0;
   out_1396735664605592698[230] = 0.0;
   out_1396735664605592698[231] = 0.0;
   out_1396735664605592698[232] = 0.0;
   out_1396735664605592698[233] = 0.0;
   out_1396735664605592698[234] = 0.0;
   out_1396735664605592698[235] = 0.0;
   out_1396735664605592698[236] = 0.0;
   out_1396735664605592698[237] = 0.0;
   out_1396735664605592698[238] = 0.0;
   out_1396735664605592698[239] = 0.0;
   out_1396735664605592698[240] = 0.0;
   out_1396735664605592698[241] = 0.0;
   out_1396735664605592698[242] = 0.0;
   out_1396735664605592698[243] = 0.0;
   out_1396735664605592698[244] = 0.0;
   out_1396735664605592698[245] = 0.0;
   out_1396735664605592698[246] = 0.0;
   out_1396735664605592698[247] = 1.0;
   out_1396735664605592698[248] = 0.0;
   out_1396735664605592698[249] = 0.0;
   out_1396735664605592698[250] = 0.0;
   out_1396735664605592698[251] = 0.0;
   out_1396735664605592698[252] = 0.0;
   out_1396735664605592698[253] = 0.0;
   out_1396735664605592698[254] = 0.0;
   out_1396735664605592698[255] = 0.0;
   out_1396735664605592698[256] = 0.0;
   out_1396735664605592698[257] = 0.0;
   out_1396735664605592698[258] = 0.0;
   out_1396735664605592698[259] = 0.0;
   out_1396735664605592698[260] = 0.0;
   out_1396735664605592698[261] = 0.0;
   out_1396735664605592698[262] = 0.0;
   out_1396735664605592698[263] = 0.0;
   out_1396735664605592698[264] = 0.0;
   out_1396735664605592698[265] = 0.0;
   out_1396735664605592698[266] = 1.0;
   out_1396735664605592698[267] = 0.0;
   out_1396735664605592698[268] = 0.0;
   out_1396735664605592698[269] = 0.0;
   out_1396735664605592698[270] = 0.0;
   out_1396735664605592698[271] = 0.0;
   out_1396735664605592698[272] = 0.0;
   out_1396735664605592698[273] = 0.0;
   out_1396735664605592698[274] = 0.0;
   out_1396735664605592698[275] = 0.0;
   out_1396735664605592698[276] = 0.0;
   out_1396735664605592698[277] = 0.0;
   out_1396735664605592698[278] = 0.0;
   out_1396735664605592698[279] = 0.0;
   out_1396735664605592698[280] = 0.0;
   out_1396735664605592698[281] = 0.0;
   out_1396735664605592698[282] = 0.0;
   out_1396735664605592698[283] = 0.0;
   out_1396735664605592698[284] = 0.0;
   out_1396735664605592698[285] = 1.0;
   out_1396735664605592698[286] = 0.0;
   out_1396735664605592698[287] = 0.0;
   out_1396735664605592698[288] = 0.0;
   out_1396735664605592698[289] = 0.0;
   out_1396735664605592698[290] = 0.0;
   out_1396735664605592698[291] = 0.0;
   out_1396735664605592698[292] = 0.0;
   out_1396735664605592698[293] = 0.0;
   out_1396735664605592698[294] = 0.0;
   out_1396735664605592698[295] = 0.0;
   out_1396735664605592698[296] = 0.0;
   out_1396735664605592698[297] = 0.0;
   out_1396735664605592698[298] = 0.0;
   out_1396735664605592698[299] = 0.0;
   out_1396735664605592698[300] = 0.0;
   out_1396735664605592698[301] = 0.0;
   out_1396735664605592698[302] = 0.0;
   out_1396735664605592698[303] = 0.0;
   out_1396735664605592698[304] = 1.0;
   out_1396735664605592698[305] = 0.0;
   out_1396735664605592698[306] = 0.0;
   out_1396735664605592698[307] = 0.0;
   out_1396735664605592698[308] = 0.0;
   out_1396735664605592698[309] = 0.0;
   out_1396735664605592698[310] = 0.0;
   out_1396735664605592698[311] = 0.0;
   out_1396735664605592698[312] = 0.0;
   out_1396735664605592698[313] = 0.0;
   out_1396735664605592698[314] = 0.0;
   out_1396735664605592698[315] = 0.0;
   out_1396735664605592698[316] = 0.0;
   out_1396735664605592698[317] = 0.0;
   out_1396735664605592698[318] = 0.0;
   out_1396735664605592698[319] = 0.0;
   out_1396735664605592698[320] = 0.0;
   out_1396735664605592698[321] = 0.0;
   out_1396735664605592698[322] = 0.0;
   out_1396735664605592698[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_916482441408583797) {
   out_916482441408583797[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_916482441408583797[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_916482441408583797[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_916482441408583797[3] = dt*state[12] + state[3];
   out_916482441408583797[4] = dt*state[13] + state[4];
   out_916482441408583797[5] = dt*state[14] + state[5];
   out_916482441408583797[6] = state[6];
   out_916482441408583797[7] = state[7];
   out_916482441408583797[8] = state[8];
   out_916482441408583797[9] = state[9];
   out_916482441408583797[10] = state[10];
   out_916482441408583797[11] = state[11];
   out_916482441408583797[12] = state[12];
   out_916482441408583797[13] = state[13];
   out_916482441408583797[14] = state[14];
   out_916482441408583797[15] = state[15];
   out_916482441408583797[16] = state[16];
   out_916482441408583797[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5639772936950525263) {
   out_5639772936950525263[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5639772936950525263[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5639772936950525263[2] = 0;
   out_5639772936950525263[3] = 0;
   out_5639772936950525263[4] = 0;
   out_5639772936950525263[5] = 0;
   out_5639772936950525263[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5639772936950525263[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5639772936950525263[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5639772936950525263[9] = 0;
   out_5639772936950525263[10] = 0;
   out_5639772936950525263[11] = 0;
   out_5639772936950525263[12] = 0;
   out_5639772936950525263[13] = 0;
   out_5639772936950525263[14] = 0;
   out_5639772936950525263[15] = 0;
   out_5639772936950525263[16] = 0;
   out_5639772936950525263[17] = 0;
   out_5639772936950525263[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5639772936950525263[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5639772936950525263[20] = 0;
   out_5639772936950525263[21] = 0;
   out_5639772936950525263[22] = 0;
   out_5639772936950525263[23] = 0;
   out_5639772936950525263[24] = 0;
   out_5639772936950525263[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5639772936950525263[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5639772936950525263[27] = 0;
   out_5639772936950525263[28] = 0;
   out_5639772936950525263[29] = 0;
   out_5639772936950525263[30] = 0;
   out_5639772936950525263[31] = 0;
   out_5639772936950525263[32] = 0;
   out_5639772936950525263[33] = 0;
   out_5639772936950525263[34] = 0;
   out_5639772936950525263[35] = 0;
   out_5639772936950525263[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5639772936950525263[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5639772936950525263[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5639772936950525263[39] = 0;
   out_5639772936950525263[40] = 0;
   out_5639772936950525263[41] = 0;
   out_5639772936950525263[42] = 0;
   out_5639772936950525263[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5639772936950525263[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5639772936950525263[45] = 0;
   out_5639772936950525263[46] = 0;
   out_5639772936950525263[47] = 0;
   out_5639772936950525263[48] = 0;
   out_5639772936950525263[49] = 0;
   out_5639772936950525263[50] = 0;
   out_5639772936950525263[51] = 0;
   out_5639772936950525263[52] = 0;
   out_5639772936950525263[53] = 0;
   out_5639772936950525263[54] = 0;
   out_5639772936950525263[55] = 0;
   out_5639772936950525263[56] = 0;
   out_5639772936950525263[57] = 1;
   out_5639772936950525263[58] = 0;
   out_5639772936950525263[59] = 0;
   out_5639772936950525263[60] = 0;
   out_5639772936950525263[61] = 0;
   out_5639772936950525263[62] = 0;
   out_5639772936950525263[63] = 0;
   out_5639772936950525263[64] = 0;
   out_5639772936950525263[65] = 0;
   out_5639772936950525263[66] = dt;
   out_5639772936950525263[67] = 0;
   out_5639772936950525263[68] = 0;
   out_5639772936950525263[69] = 0;
   out_5639772936950525263[70] = 0;
   out_5639772936950525263[71] = 0;
   out_5639772936950525263[72] = 0;
   out_5639772936950525263[73] = 0;
   out_5639772936950525263[74] = 0;
   out_5639772936950525263[75] = 0;
   out_5639772936950525263[76] = 1;
   out_5639772936950525263[77] = 0;
   out_5639772936950525263[78] = 0;
   out_5639772936950525263[79] = 0;
   out_5639772936950525263[80] = 0;
   out_5639772936950525263[81] = 0;
   out_5639772936950525263[82] = 0;
   out_5639772936950525263[83] = 0;
   out_5639772936950525263[84] = 0;
   out_5639772936950525263[85] = dt;
   out_5639772936950525263[86] = 0;
   out_5639772936950525263[87] = 0;
   out_5639772936950525263[88] = 0;
   out_5639772936950525263[89] = 0;
   out_5639772936950525263[90] = 0;
   out_5639772936950525263[91] = 0;
   out_5639772936950525263[92] = 0;
   out_5639772936950525263[93] = 0;
   out_5639772936950525263[94] = 0;
   out_5639772936950525263[95] = 1;
   out_5639772936950525263[96] = 0;
   out_5639772936950525263[97] = 0;
   out_5639772936950525263[98] = 0;
   out_5639772936950525263[99] = 0;
   out_5639772936950525263[100] = 0;
   out_5639772936950525263[101] = 0;
   out_5639772936950525263[102] = 0;
   out_5639772936950525263[103] = 0;
   out_5639772936950525263[104] = dt;
   out_5639772936950525263[105] = 0;
   out_5639772936950525263[106] = 0;
   out_5639772936950525263[107] = 0;
   out_5639772936950525263[108] = 0;
   out_5639772936950525263[109] = 0;
   out_5639772936950525263[110] = 0;
   out_5639772936950525263[111] = 0;
   out_5639772936950525263[112] = 0;
   out_5639772936950525263[113] = 0;
   out_5639772936950525263[114] = 1;
   out_5639772936950525263[115] = 0;
   out_5639772936950525263[116] = 0;
   out_5639772936950525263[117] = 0;
   out_5639772936950525263[118] = 0;
   out_5639772936950525263[119] = 0;
   out_5639772936950525263[120] = 0;
   out_5639772936950525263[121] = 0;
   out_5639772936950525263[122] = 0;
   out_5639772936950525263[123] = 0;
   out_5639772936950525263[124] = 0;
   out_5639772936950525263[125] = 0;
   out_5639772936950525263[126] = 0;
   out_5639772936950525263[127] = 0;
   out_5639772936950525263[128] = 0;
   out_5639772936950525263[129] = 0;
   out_5639772936950525263[130] = 0;
   out_5639772936950525263[131] = 0;
   out_5639772936950525263[132] = 0;
   out_5639772936950525263[133] = 1;
   out_5639772936950525263[134] = 0;
   out_5639772936950525263[135] = 0;
   out_5639772936950525263[136] = 0;
   out_5639772936950525263[137] = 0;
   out_5639772936950525263[138] = 0;
   out_5639772936950525263[139] = 0;
   out_5639772936950525263[140] = 0;
   out_5639772936950525263[141] = 0;
   out_5639772936950525263[142] = 0;
   out_5639772936950525263[143] = 0;
   out_5639772936950525263[144] = 0;
   out_5639772936950525263[145] = 0;
   out_5639772936950525263[146] = 0;
   out_5639772936950525263[147] = 0;
   out_5639772936950525263[148] = 0;
   out_5639772936950525263[149] = 0;
   out_5639772936950525263[150] = 0;
   out_5639772936950525263[151] = 0;
   out_5639772936950525263[152] = 1;
   out_5639772936950525263[153] = 0;
   out_5639772936950525263[154] = 0;
   out_5639772936950525263[155] = 0;
   out_5639772936950525263[156] = 0;
   out_5639772936950525263[157] = 0;
   out_5639772936950525263[158] = 0;
   out_5639772936950525263[159] = 0;
   out_5639772936950525263[160] = 0;
   out_5639772936950525263[161] = 0;
   out_5639772936950525263[162] = 0;
   out_5639772936950525263[163] = 0;
   out_5639772936950525263[164] = 0;
   out_5639772936950525263[165] = 0;
   out_5639772936950525263[166] = 0;
   out_5639772936950525263[167] = 0;
   out_5639772936950525263[168] = 0;
   out_5639772936950525263[169] = 0;
   out_5639772936950525263[170] = 0;
   out_5639772936950525263[171] = 1;
   out_5639772936950525263[172] = 0;
   out_5639772936950525263[173] = 0;
   out_5639772936950525263[174] = 0;
   out_5639772936950525263[175] = 0;
   out_5639772936950525263[176] = 0;
   out_5639772936950525263[177] = 0;
   out_5639772936950525263[178] = 0;
   out_5639772936950525263[179] = 0;
   out_5639772936950525263[180] = 0;
   out_5639772936950525263[181] = 0;
   out_5639772936950525263[182] = 0;
   out_5639772936950525263[183] = 0;
   out_5639772936950525263[184] = 0;
   out_5639772936950525263[185] = 0;
   out_5639772936950525263[186] = 0;
   out_5639772936950525263[187] = 0;
   out_5639772936950525263[188] = 0;
   out_5639772936950525263[189] = 0;
   out_5639772936950525263[190] = 1;
   out_5639772936950525263[191] = 0;
   out_5639772936950525263[192] = 0;
   out_5639772936950525263[193] = 0;
   out_5639772936950525263[194] = 0;
   out_5639772936950525263[195] = 0;
   out_5639772936950525263[196] = 0;
   out_5639772936950525263[197] = 0;
   out_5639772936950525263[198] = 0;
   out_5639772936950525263[199] = 0;
   out_5639772936950525263[200] = 0;
   out_5639772936950525263[201] = 0;
   out_5639772936950525263[202] = 0;
   out_5639772936950525263[203] = 0;
   out_5639772936950525263[204] = 0;
   out_5639772936950525263[205] = 0;
   out_5639772936950525263[206] = 0;
   out_5639772936950525263[207] = 0;
   out_5639772936950525263[208] = 0;
   out_5639772936950525263[209] = 1;
   out_5639772936950525263[210] = 0;
   out_5639772936950525263[211] = 0;
   out_5639772936950525263[212] = 0;
   out_5639772936950525263[213] = 0;
   out_5639772936950525263[214] = 0;
   out_5639772936950525263[215] = 0;
   out_5639772936950525263[216] = 0;
   out_5639772936950525263[217] = 0;
   out_5639772936950525263[218] = 0;
   out_5639772936950525263[219] = 0;
   out_5639772936950525263[220] = 0;
   out_5639772936950525263[221] = 0;
   out_5639772936950525263[222] = 0;
   out_5639772936950525263[223] = 0;
   out_5639772936950525263[224] = 0;
   out_5639772936950525263[225] = 0;
   out_5639772936950525263[226] = 0;
   out_5639772936950525263[227] = 0;
   out_5639772936950525263[228] = 1;
   out_5639772936950525263[229] = 0;
   out_5639772936950525263[230] = 0;
   out_5639772936950525263[231] = 0;
   out_5639772936950525263[232] = 0;
   out_5639772936950525263[233] = 0;
   out_5639772936950525263[234] = 0;
   out_5639772936950525263[235] = 0;
   out_5639772936950525263[236] = 0;
   out_5639772936950525263[237] = 0;
   out_5639772936950525263[238] = 0;
   out_5639772936950525263[239] = 0;
   out_5639772936950525263[240] = 0;
   out_5639772936950525263[241] = 0;
   out_5639772936950525263[242] = 0;
   out_5639772936950525263[243] = 0;
   out_5639772936950525263[244] = 0;
   out_5639772936950525263[245] = 0;
   out_5639772936950525263[246] = 0;
   out_5639772936950525263[247] = 1;
   out_5639772936950525263[248] = 0;
   out_5639772936950525263[249] = 0;
   out_5639772936950525263[250] = 0;
   out_5639772936950525263[251] = 0;
   out_5639772936950525263[252] = 0;
   out_5639772936950525263[253] = 0;
   out_5639772936950525263[254] = 0;
   out_5639772936950525263[255] = 0;
   out_5639772936950525263[256] = 0;
   out_5639772936950525263[257] = 0;
   out_5639772936950525263[258] = 0;
   out_5639772936950525263[259] = 0;
   out_5639772936950525263[260] = 0;
   out_5639772936950525263[261] = 0;
   out_5639772936950525263[262] = 0;
   out_5639772936950525263[263] = 0;
   out_5639772936950525263[264] = 0;
   out_5639772936950525263[265] = 0;
   out_5639772936950525263[266] = 1;
   out_5639772936950525263[267] = 0;
   out_5639772936950525263[268] = 0;
   out_5639772936950525263[269] = 0;
   out_5639772936950525263[270] = 0;
   out_5639772936950525263[271] = 0;
   out_5639772936950525263[272] = 0;
   out_5639772936950525263[273] = 0;
   out_5639772936950525263[274] = 0;
   out_5639772936950525263[275] = 0;
   out_5639772936950525263[276] = 0;
   out_5639772936950525263[277] = 0;
   out_5639772936950525263[278] = 0;
   out_5639772936950525263[279] = 0;
   out_5639772936950525263[280] = 0;
   out_5639772936950525263[281] = 0;
   out_5639772936950525263[282] = 0;
   out_5639772936950525263[283] = 0;
   out_5639772936950525263[284] = 0;
   out_5639772936950525263[285] = 1;
   out_5639772936950525263[286] = 0;
   out_5639772936950525263[287] = 0;
   out_5639772936950525263[288] = 0;
   out_5639772936950525263[289] = 0;
   out_5639772936950525263[290] = 0;
   out_5639772936950525263[291] = 0;
   out_5639772936950525263[292] = 0;
   out_5639772936950525263[293] = 0;
   out_5639772936950525263[294] = 0;
   out_5639772936950525263[295] = 0;
   out_5639772936950525263[296] = 0;
   out_5639772936950525263[297] = 0;
   out_5639772936950525263[298] = 0;
   out_5639772936950525263[299] = 0;
   out_5639772936950525263[300] = 0;
   out_5639772936950525263[301] = 0;
   out_5639772936950525263[302] = 0;
   out_5639772936950525263[303] = 0;
   out_5639772936950525263[304] = 1;
   out_5639772936950525263[305] = 0;
   out_5639772936950525263[306] = 0;
   out_5639772936950525263[307] = 0;
   out_5639772936950525263[308] = 0;
   out_5639772936950525263[309] = 0;
   out_5639772936950525263[310] = 0;
   out_5639772936950525263[311] = 0;
   out_5639772936950525263[312] = 0;
   out_5639772936950525263[313] = 0;
   out_5639772936950525263[314] = 0;
   out_5639772936950525263[315] = 0;
   out_5639772936950525263[316] = 0;
   out_5639772936950525263[317] = 0;
   out_5639772936950525263[318] = 0;
   out_5639772936950525263[319] = 0;
   out_5639772936950525263[320] = 0;
   out_5639772936950525263[321] = 0;
   out_5639772936950525263[322] = 0;
   out_5639772936950525263[323] = 1;
}
void h_4(double *state, double *unused, double *out_5848855439961291946) {
   out_5848855439961291946[0] = state[6] + state[9];
   out_5848855439961291946[1] = state[7] + state[10];
   out_5848855439961291946[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3290246568201368788) {
   out_3290246568201368788[0] = 0;
   out_3290246568201368788[1] = 0;
   out_3290246568201368788[2] = 0;
   out_3290246568201368788[3] = 0;
   out_3290246568201368788[4] = 0;
   out_3290246568201368788[5] = 0;
   out_3290246568201368788[6] = 1;
   out_3290246568201368788[7] = 0;
   out_3290246568201368788[8] = 0;
   out_3290246568201368788[9] = 1;
   out_3290246568201368788[10] = 0;
   out_3290246568201368788[11] = 0;
   out_3290246568201368788[12] = 0;
   out_3290246568201368788[13] = 0;
   out_3290246568201368788[14] = 0;
   out_3290246568201368788[15] = 0;
   out_3290246568201368788[16] = 0;
   out_3290246568201368788[17] = 0;
   out_3290246568201368788[18] = 0;
   out_3290246568201368788[19] = 0;
   out_3290246568201368788[20] = 0;
   out_3290246568201368788[21] = 0;
   out_3290246568201368788[22] = 0;
   out_3290246568201368788[23] = 0;
   out_3290246568201368788[24] = 0;
   out_3290246568201368788[25] = 1;
   out_3290246568201368788[26] = 0;
   out_3290246568201368788[27] = 0;
   out_3290246568201368788[28] = 1;
   out_3290246568201368788[29] = 0;
   out_3290246568201368788[30] = 0;
   out_3290246568201368788[31] = 0;
   out_3290246568201368788[32] = 0;
   out_3290246568201368788[33] = 0;
   out_3290246568201368788[34] = 0;
   out_3290246568201368788[35] = 0;
   out_3290246568201368788[36] = 0;
   out_3290246568201368788[37] = 0;
   out_3290246568201368788[38] = 0;
   out_3290246568201368788[39] = 0;
   out_3290246568201368788[40] = 0;
   out_3290246568201368788[41] = 0;
   out_3290246568201368788[42] = 0;
   out_3290246568201368788[43] = 0;
   out_3290246568201368788[44] = 1;
   out_3290246568201368788[45] = 0;
   out_3290246568201368788[46] = 0;
   out_3290246568201368788[47] = 1;
   out_3290246568201368788[48] = 0;
   out_3290246568201368788[49] = 0;
   out_3290246568201368788[50] = 0;
   out_3290246568201368788[51] = 0;
   out_3290246568201368788[52] = 0;
   out_3290246568201368788[53] = 0;
}
void h_10(double *state, double *unused, double *out_3954090448202517665) {
   out_3954090448202517665[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3954090448202517665[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3954090448202517665[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1376781969837987839) {
   out_1376781969837987839[0] = 0;
   out_1376781969837987839[1] = 9.8100000000000005*cos(state[1]);
   out_1376781969837987839[2] = 0;
   out_1376781969837987839[3] = 0;
   out_1376781969837987839[4] = -state[8];
   out_1376781969837987839[5] = state[7];
   out_1376781969837987839[6] = 0;
   out_1376781969837987839[7] = state[5];
   out_1376781969837987839[8] = -state[4];
   out_1376781969837987839[9] = 0;
   out_1376781969837987839[10] = 0;
   out_1376781969837987839[11] = 0;
   out_1376781969837987839[12] = 1;
   out_1376781969837987839[13] = 0;
   out_1376781969837987839[14] = 0;
   out_1376781969837987839[15] = 1;
   out_1376781969837987839[16] = 0;
   out_1376781969837987839[17] = 0;
   out_1376781969837987839[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1376781969837987839[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1376781969837987839[20] = 0;
   out_1376781969837987839[21] = state[8];
   out_1376781969837987839[22] = 0;
   out_1376781969837987839[23] = -state[6];
   out_1376781969837987839[24] = -state[5];
   out_1376781969837987839[25] = 0;
   out_1376781969837987839[26] = state[3];
   out_1376781969837987839[27] = 0;
   out_1376781969837987839[28] = 0;
   out_1376781969837987839[29] = 0;
   out_1376781969837987839[30] = 0;
   out_1376781969837987839[31] = 1;
   out_1376781969837987839[32] = 0;
   out_1376781969837987839[33] = 0;
   out_1376781969837987839[34] = 1;
   out_1376781969837987839[35] = 0;
   out_1376781969837987839[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1376781969837987839[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1376781969837987839[38] = 0;
   out_1376781969837987839[39] = -state[7];
   out_1376781969837987839[40] = state[6];
   out_1376781969837987839[41] = 0;
   out_1376781969837987839[42] = state[4];
   out_1376781969837987839[43] = -state[3];
   out_1376781969837987839[44] = 0;
   out_1376781969837987839[45] = 0;
   out_1376781969837987839[46] = 0;
   out_1376781969837987839[47] = 0;
   out_1376781969837987839[48] = 0;
   out_1376781969837987839[49] = 0;
   out_1376781969837987839[50] = 1;
   out_1376781969837987839[51] = 0;
   out_1376781969837987839[52] = 0;
   out_1376781969837987839[53] = 1;
}
void h_13(double *state, double *unused, double *out_8116870387044428464) {
   out_8116870387044428464[0] = state[3];
   out_8116870387044428464[1] = state[4];
   out_8116870387044428464[2] = state[5];
}
void H_13(double *state, double *unused, double *out_77972742869035987) {
   out_77972742869035987[0] = 0;
   out_77972742869035987[1] = 0;
   out_77972742869035987[2] = 0;
   out_77972742869035987[3] = 1;
   out_77972742869035987[4] = 0;
   out_77972742869035987[5] = 0;
   out_77972742869035987[6] = 0;
   out_77972742869035987[7] = 0;
   out_77972742869035987[8] = 0;
   out_77972742869035987[9] = 0;
   out_77972742869035987[10] = 0;
   out_77972742869035987[11] = 0;
   out_77972742869035987[12] = 0;
   out_77972742869035987[13] = 0;
   out_77972742869035987[14] = 0;
   out_77972742869035987[15] = 0;
   out_77972742869035987[16] = 0;
   out_77972742869035987[17] = 0;
   out_77972742869035987[18] = 0;
   out_77972742869035987[19] = 0;
   out_77972742869035987[20] = 0;
   out_77972742869035987[21] = 0;
   out_77972742869035987[22] = 1;
   out_77972742869035987[23] = 0;
   out_77972742869035987[24] = 0;
   out_77972742869035987[25] = 0;
   out_77972742869035987[26] = 0;
   out_77972742869035987[27] = 0;
   out_77972742869035987[28] = 0;
   out_77972742869035987[29] = 0;
   out_77972742869035987[30] = 0;
   out_77972742869035987[31] = 0;
   out_77972742869035987[32] = 0;
   out_77972742869035987[33] = 0;
   out_77972742869035987[34] = 0;
   out_77972742869035987[35] = 0;
   out_77972742869035987[36] = 0;
   out_77972742869035987[37] = 0;
   out_77972742869035987[38] = 0;
   out_77972742869035987[39] = 0;
   out_77972742869035987[40] = 0;
   out_77972742869035987[41] = 1;
   out_77972742869035987[42] = 0;
   out_77972742869035987[43] = 0;
   out_77972742869035987[44] = 0;
   out_77972742869035987[45] = 0;
   out_77972742869035987[46] = 0;
   out_77972742869035987[47] = 0;
   out_77972742869035987[48] = 0;
   out_77972742869035987[49] = 0;
   out_77972742869035987[50] = 0;
   out_77972742869035987[51] = 0;
   out_77972742869035987[52] = 0;
   out_77972742869035987[53] = 0;
}
void h_14(double *state, double *unused, double *out_2879136579664093334) {
   out_2879136579664093334[0] = state[6];
   out_2879136579664093334[1] = state[7];
   out_2879136579664093334[2] = state[8];
}
void H_14(double *state, double *unused, double *out_672994288138115741) {
   out_672994288138115741[0] = 0;
   out_672994288138115741[1] = 0;
   out_672994288138115741[2] = 0;
   out_672994288138115741[3] = 0;
   out_672994288138115741[4] = 0;
   out_672994288138115741[5] = 0;
   out_672994288138115741[6] = 1;
   out_672994288138115741[7] = 0;
   out_672994288138115741[8] = 0;
   out_672994288138115741[9] = 0;
   out_672994288138115741[10] = 0;
   out_672994288138115741[11] = 0;
   out_672994288138115741[12] = 0;
   out_672994288138115741[13] = 0;
   out_672994288138115741[14] = 0;
   out_672994288138115741[15] = 0;
   out_672994288138115741[16] = 0;
   out_672994288138115741[17] = 0;
   out_672994288138115741[18] = 0;
   out_672994288138115741[19] = 0;
   out_672994288138115741[20] = 0;
   out_672994288138115741[21] = 0;
   out_672994288138115741[22] = 0;
   out_672994288138115741[23] = 0;
   out_672994288138115741[24] = 0;
   out_672994288138115741[25] = 1;
   out_672994288138115741[26] = 0;
   out_672994288138115741[27] = 0;
   out_672994288138115741[28] = 0;
   out_672994288138115741[29] = 0;
   out_672994288138115741[30] = 0;
   out_672994288138115741[31] = 0;
   out_672994288138115741[32] = 0;
   out_672994288138115741[33] = 0;
   out_672994288138115741[34] = 0;
   out_672994288138115741[35] = 0;
   out_672994288138115741[36] = 0;
   out_672994288138115741[37] = 0;
   out_672994288138115741[38] = 0;
   out_672994288138115741[39] = 0;
   out_672994288138115741[40] = 0;
   out_672994288138115741[41] = 0;
   out_672994288138115741[42] = 0;
   out_672994288138115741[43] = 0;
   out_672994288138115741[44] = 1;
   out_672994288138115741[45] = 0;
   out_672994288138115741[46] = 0;
   out_672994288138115741[47] = 0;
   out_672994288138115741[48] = 0;
   out_672994288138115741[49] = 0;
   out_672994288138115741[50] = 0;
   out_672994288138115741[51] = 0;
   out_672994288138115741[52] = 0;
   out_672994288138115741[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_9170572944906816852) {
  err_fun(nom_x, delta_x, out_9170572944906816852);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4867215415263963768) {
  inv_err_fun(nom_x, true_x, out_4867215415263963768);
}
void pose_H_mod_fun(double *state, double *out_1396735664605592698) {
  H_mod_fun(state, out_1396735664605592698);
}
void pose_f_fun(double *state, double dt, double *out_916482441408583797) {
  f_fun(state,  dt, out_916482441408583797);
}
void pose_F_fun(double *state, double dt, double *out_5639772936950525263) {
  F_fun(state,  dt, out_5639772936950525263);
}
void pose_h_4(double *state, double *unused, double *out_5848855439961291946) {
  h_4(state, unused, out_5848855439961291946);
}
void pose_H_4(double *state, double *unused, double *out_3290246568201368788) {
  H_4(state, unused, out_3290246568201368788);
}
void pose_h_10(double *state, double *unused, double *out_3954090448202517665) {
  h_10(state, unused, out_3954090448202517665);
}
void pose_H_10(double *state, double *unused, double *out_1376781969837987839) {
  H_10(state, unused, out_1376781969837987839);
}
void pose_h_13(double *state, double *unused, double *out_8116870387044428464) {
  h_13(state, unused, out_8116870387044428464);
}
void pose_H_13(double *state, double *unused, double *out_77972742869035987) {
  H_13(state, unused, out_77972742869035987);
}
void pose_h_14(double *state, double *unused, double *out_2879136579664093334) {
  h_14(state, unused, out_2879136579664093334);
}
void pose_H_14(double *state, double *unused, double *out_672994288138115741) {
  H_14(state, unused, out_672994288138115741);
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
