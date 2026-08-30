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
void err_fun(double *nom_x, double *delta_x, double *out_3122087598286484509) {
   out_3122087598286484509[0] = delta_x[0] + nom_x[0];
   out_3122087598286484509[1] = delta_x[1] + nom_x[1];
   out_3122087598286484509[2] = delta_x[2] + nom_x[2];
   out_3122087598286484509[3] = delta_x[3] + nom_x[3];
   out_3122087598286484509[4] = delta_x[4] + nom_x[4];
   out_3122087598286484509[5] = delta_x[5] + nom_x[5];
   out_3122087598286484509[6] = delta_x[6] + nom_x[6];
   out_3122087598286484509[7] = delta_x[7] + nom_x[7];
   out_3122087598286484509[8] = delta_x[8] + nom_x[8];
   out_3122087598286484509[9] = delta_x[9] + nom_x[9];
   out_3122087598286484509[10] = delta_x[10] + nom_x[10];
   out_3122087598286484509[11] = delta_x[11] + nom_x[11];
   out_3122087598286484509[12] = delta_x[12] + nom_x[12];
   out_3122087598286484509[13] = delta_x[13] + nom_x[13];
   out_3122087598286484509[14] = delta_x[14] + nom_x[14];
   out_3122087598286484509[15] = delta_x[15] + nom_x[15];
   out_3122087598286484509[16] = delta_x[16] + nom_x[16];
   out_3122087598286484509[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6671609920081726507) {
   out_6671609920081726507[0] = -nom_x[0] + true_x[0];
   out_6671609920081726507[1] = -nom_x[1] + true_x[1];
   out_6671609920081726507[2] = -nom_x[2] + true_x[2];
   out_6671609920081726507[3] = -nom_x[3] + true_x[3];
   out_6671609920081726507[4] = -nom_x[4] + true_x[4];
   out_6671609920081726507[5] = -nom_x[5] + true_x[5];
   out_6671609920081726507[6] = -nom_x[6] + true_x[6];
   out_6671609920081726507[7] = -nom_x[7] + true_x[7];
   out_6671609920081726507[8] = -nom_x[8] + true_x[8];
   out_6671609920081726507[9] = -nom_x[9] + true_x[9];
   out_6671609920081726507[10] = -nom_x[10] + true_x[10];
   out_6671609920081726507[11] = -nom_x[11] + true_x[11];
   out_6671609920081726507[12] = -nom_x[12] + true_x[12];
   out_6671609920081726507[13] = -nom_x[13] + true_x[13];
   out_6671609920081726507[14] = -nom_x[14] + true_x[14];
   out_6671609920081726507[15] = -nom_x[15] + true_x[15];
   out_6671609920081726507[16] = -nom_x[16] + true_x[16];
   out_6671609920081726507[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_6807142630278803635) {
   out_6807142630278803635[0] = 1.0;
   out_6807142630278803635[1] = 0.0;
   out_6807142630278803635[2] = 0.0;
   out_6807142630278803635[3] = 0.0;
   out_6807142630278803635[4] = 0.0;
   out_6807142630278803635[5] = 0.0;
   out_6807142630278803635[6] = 0.0;
   out_6807142630278803635[7] = 0.0;
   out_6807142630278803635[8] = 0.0;
   out_6807142630278803635[9] = 0.0;
   out_6807142630278803635[10] = 0.0;
   out_6807142630278803635[11] = 0.0;
   out_6807142630278803635[12] = 0.0;
   out_6807142630278803635[13] = 0.0;
   out_6807142630278803635[14] = 0.0;
   out_6807142630278803635[15] = 0.0;
   out_6807142630278803635[16] = 0.0;
   out_6807142630278803635[17] = 0.0;
   out_6807142630278803635[18] = 0.0;
   out_6807142630278803635[19] = 1.0;
   out_6807142630278803635[20] = 0.0;
   out_6807142630278803635[21] = 0.0;
   out_6807142630278803635[22] = 0.0;
   out_6807142630278803635[23] = 0.0;
   out_6807142630278803635[24] = 0.0;
   out_6807142630278803635[25] = 0.0;
   out_6807142630278803635[26] = 0.0;
   out_6807142630278803635[27] = 0.0;
   out_6807142630278803635[28] = 0.0;
   out_6807142630278803635[29] = 0.0;
   out_6807142630278803635[30] = 0.0;
   out_6807142630278803635[31] = 0.0;
   out_6807142630278803635[32] = 0.0;
   out_6807142630278803635[33] = 0.0;
   out_6807142630278803635[34] = 0.0;
   out_6807142630278803635[35] = 0.0;
   out_6807142630278803635[36] = 0.0;
   out_6807142630278803635[37] = 0.0;
   out_6807142630278803635[38] = 1.0;
   out_6807142630278803635[39] = 0.0;
   out_6807142630278803635[40] = 0.0;
   out_6807142630278803635[41] = 0.0;
   out_6807142630278803635[42] = 0.0;
   out_6807142630278803635[43] = 0.0;
   out_6807142630278803635[44] = 0.0;
   out_6807142630278803635[45] = 0.0;
   out_6807142630278803635[46] = 0.0;
   out_6807142630278803635[47] = 0.0;
   out_6807142630278803635[48] = 0.0;
   out_6807142630278803635[49] = 0.0;
   out_6807142630278803635[50] = 0.0;
   out_6807142630278803635[51] = 0.0;
   out_6807142630278803635[52] = 0.0;
   out_6807142630278803635[53] = 0.0;
   out_6807142630278803635[54] = 0.0;
   out_6807142630278803635[55] = 0.0;
   out_6807142630278803635[56] = 0.0;
   out_6807142630278803635[57] = 1.0;
   out_6807142630278803635[58] = 0.0;
   out_6807142630278803635[59] = 0.0;
   out_6807142630278803635[60] = 0.0;
   out_6807142630278803635[61] = 0.0;
   out_6807142630278803635[62] = 0.0;
   out_6807142630278803635[63] = 0.0;
   out_6807142630278803635[64] = 0.0;
   out_6807142630278803635[65] = 0.0;
   out_6807142630278803635[66] = 0.0;
   out_6807142630278803635[67] = 0.0;
   out_6807142630278803635[68] = 0.0;
   out_6807142630278803635[69] = 0.0;
   out_6807142630278803635[70] = 0.0;
   out_6807142630278803635[71] = 0.0;
   out_6807142630278803635[72] = 0.0;
   out_6807142630278803635[73] = 0.0;
   out_6807142630278803635[74] = 0.0;
   out_6807142630278803635[75] = 0.0;
   out_6807142630278803635[76] = 1.0;
   out_6807142630278803635[77] = 0.0;
   out_6807142630278803635[78] = 0.0;
   out_6807142630278803635[79] = 0.0;
   out_6807142630278803635[80] = 0.0;
   out_6807142630278803635[81] = 0.0;
   out_6807142630278803635[82] = 0.0;
   out_6807142630278803635[83] = 0.0;
   out_6807142630278803635[84] = 0.0;
   out_6807142630278803635[85] = 0.0;
   out_6807142630278803635[86] = 0.0;
   out_6807142630278803635[87] = 0.0;
   out_6807142630278803635[88] = 0.0;
   out_6807142630278803635[89] = 0.0;
   out_6807142630278803635[90] = 0.0;
   out_6807142630278803635[91] = 0.0;
   out_6807142630278803635[92] = 0.0;
   out_6807142630278803635[93] = 0.0;
   out_6807142630278803635[94] = 0.0;
   out_6807142630278803635[95] = 1.0;
   out_6807142630278803635[96] = 0.0;
   out_6807142630278803635[97] = 0.0;
   out_6807142630278803635[98] = 0.0;
   out_6807142630278803635[99] = 0.0;
   out_6807142630278803635[100] = 0.0;
   out_6807142630278803635[101] = 0.0;
   out_6807142630278803635[102] = 0.0;
   out_6807142630278803635[103] = 0.0;
   out_6807142630278803635[104] = 0.0;
   out_6807142630278803635[105] = 0.0;
   out_6807142630278803635[106] = 0.0;
   out_6807142630278803635[107] = 0.0;
   out_6807142630278803635[108] = 0.0;
   out_6807142630278803635[109] = 0.0;
   out_6807142630278803635[110] = 0.0;
   out_6807142630278803635[111] = 0.0;
   out_6807142630278803635[112] = 0.0;
   out_6807142630278803635[113] = 0.0;
   out_6807142630278803635[114] = 1.0;
   out_6807142630278803635[115] = 0.0;
   out_6807142630278803635[116] = 0.0;
   out_6807142630278803635[117] = 0.0;
   out_6807142630278803635[118] = 0.0;
   out_6807142630278803635[119] = 0.0;
   out_6807142630278803635[120] = 0.0;
   out_6807142630278803635[121] = 0.0;
   out_6807142630278803635[122] = 0.0;
   out_6807142630278803635[123] = 0.0;
   out_6807142630278803635[124] = 0.0;
   out_6807142630278803635[125] = 0.0;
   out_6807142630278803635[126] = 0.0;
   out_6807142630278803635[127] = 0.0;
   out_6807142630278803635[128] = 0.0;
   out_6807142630278803635[129] = 0.0;
   out_6807142630278803635[130] = 0.0;
   out_6807142630278803635[131] = 0.0;
   out_6807142630278803635[132] = 0.0;
   out_6807142630278803635[133] = 1.0;
   out_6807142630278803635[134] = 0.0;
   out_6807142630278803635[135] = 0.0;
   out_6807142630278803635[136] = 0.0;
   out_6807142630278803635[137] = 0.0;
   out_6807142630278803635[138] = 0.0;
   out_6807142630278803635[139] = 0.0;
   out_6807142630278803635[140] = 0.0;
   out_6807142630278803635[141] = 0.0;
   out_6807142630278803635[142] = 0.0;
   out_6807142630278803635[143] = 0.0;
   out_6807142630278803635[144] = 0.0;
   out_6807142630278803635[145] = 0.0;
   out_6807142630278803635[146] = 0.0;
   out_6807142630278803635[147] = 0.0;
   out_6807142630278803635[148] = 0.0;
   out_6807142630278803635[149] = 0.0;
   out_6807142630278803635[150] = 0.0;
   out_6807142630278803635[151] = 0.0;
   out_6807142630278803635[152] = 1.0;
   out_6807142630278803635[153] = 0.0;
   out_6807142630278803635[154] = 0.0;
   out_6807142630278803635[155] = 0.0;
   out_6807142630278803635[156] = 0.0;
   out_6807142630278803635[157] = 0.0;
   out_6807142630278803635[158] = 0.0;
   out_6807142630278803635[159] = 0.0;
   out_6807142630278803635[160] = 0.0;
   out_6807142630278803635[161] = 0.0;
   out_6807142630278803635[162] = 0.0;
   out_6807142630278803635[163] = 0.0;
   out_6807142630278803635[164] = 0.0;
   out_6807142630278803635[165] = 0.0;
   out_6807142630278803635[166] = 0.0;
   out_6807142630278803635[167] = 0.0;
   out_6807142630278803635[168] = 0.0;
   out_6807142630278803635[169] = 0.0;
   out_6807142630278803635[170] = 0.0;
   out_6807142630278803635[171] = 1.0;
   out_6807142630278803635[172] = 0.0;
   out_6807142630278803635[173] = 0.0;
   out_6807142630278803635[174] = 0.0;
   out_6807142630278803635[175] = 0.0;
   out_6807142630278803635[176] = 0.0;
   out_6807142630278803635[177] = 0.0;
   out_6807142630278803635[178] = 0.0;
   out_6807142630278803635[179] = 0.0;
   out_6807142630278803635[180] = 0.0;
   out_6807142630278803635[181] = 0.0;
   out_6807142630278803635[182] = 0.0;
   out_6807142630278803635[183] = 0.0;
   out_6807142630278803635[184] = 0.0;
   out_6807142630278803635[185] = 0.0;
   out_6807142630278803635[186] = 0.0;
   out_6807142630278803635[187] = 0.0;
   out_6807142630278803635[188] = 0.0;
   out_6807142630278803635[189] = 0.0;
   out_6807142630278803635[190] = 1.0;
   out_6807142630278803635[191] = 0.0;
   out_6807142630278803635[192] = 0.0;
   out_6807142630278803635[193] = 0.0;
   out_6807142630278803635[194] = 0.0;
   out_6807142630278803635[195] = 0.0;
   out_6807142630278803635[196] = 0.0;
   out_6807142630278803635[197] = 0.0;
   out_6807142630278803635[198] = 0.0;
   out_6807142630278803635[199] = 0.0;
   out_6807142630278803635[200] = 0.0;
   out_6807142630278803635[201] = 0.0;
   out_6807142630278803635[202] = 0.0;
   out_6807142630278803635[203] = 0.0;
   out_6807142630278803635[204] = 0.0;
   out_6807142630278803635[205] = 0.0;
   out_6807142630278803635[206] = 0.0;
   out_6807142630278803635[207] = 0.0;
   out_6807142630278803635[208] = 0.0;
   out_6807142630278803635[209] = 1.0;
   out_6807142630278803635[210] = 0.0;
   out_6807142630278803635[211] = 0.0;
   out_6807142630278803635[212] = 0.0;
   out_6807142630278803635[213] = 0.0;
   out_6807142630278803635[214] = 0.0;
   out_6807142630278803635[215] = 0.0;
   out_6807142630278803635[216] = 0.0;
   out_6807142630278803635[217] = 0.0;
   out_6807142630278803635[218] = 0.0;
   out_6807142630278803635[219] = 0.0;
   out_6807142630278803635[220] = 0.0;
   out_6807142630278803635[221] = 0.0;
   out_6807142630278803635[222] = 0.0;
   out_6807142630278803635[223] = 0.0;
   out_6807142630278803635[224] = 0.0;
   out_6807142630278803635[225] = 0.0;
   out_6807142630278803635[226] = 0.0;
   out_6807142630278803635[227] = 0.0;
   out_6807142630278803635[228] = 1.0;
   out_6807142630278803635[229] = 0.0;
   out_6807142630278803635[230] = 0.0;
   out_6807142630278803635[231] = 0.0;
   out_6807142630278803635[232] = 0.0;
   out_6807142630278803635[233] = 0.0;
   out_6807142630278803635[234] = 0.0;
   out_6807142630278803635[235] = 0.0;
   out_6807142630278803635[236] = 0.0;
   out_6807142630278803635[237] = 0.0;
   out_6807142630278803635[238] = 0.0;
   out_6807142630278803635[239] = 0.0;
   out_6807142630278803635[240] = 0.0;
   out_6807142630278803635[241] = 0.0;
   out_6807142630278803635[242] = 0.0;
   out_6807142630278803635[243] = 0.0;
   out_6807142630278803635[244] = 0.0;
   out_6807142630278803635[245] = 0.0;
   out_6807142630278803635[246] = 0.0;
   out_6807142630278803635[247] = 1.0;
   out_6807142630278803635[248] = 0.0;
   out_6807142630278803635[249] = 0.0;
   out_6807142630278803635[250] = 0.0;
   out_6807142630278803635[251] = 0.0;
   out_6807142630278803635[252] = 0.0;
   out_6807142630278803635[253] = 0.0;
   out_6807142630278803635[254] = 0.0;
   out_6807142630278803635[255] = 0.0;
   out_6807142630278803635[256] = 0.0;
   out_6807142630278803635[257] = 0.0;
   out_6807142630278803635[258] = 0.0;
   out_6807142630278803635[259] = 0.0;
   out_6807142630278803635[260] = 0.0;
   out_6807142630278803635[261] = 0.0;
   out_6807142630278803635[262] = 0.0;
   out_6807142630278803635[263] = 0.0;
   out_6807142630278803635[264] = 0.0;
   out_6807142630278803635[265] = 0.0;
   out_6807142630278803635[266] = 1.0;
   out_6807142630278803635[267] = 0.0;
   out_6807142630278803635[268] = 0.0;
   out_6807142630278803635[269] = 0.0;
   out_6807142630278803635[270] = 0.0;
   out_6807142630278803635[271] = 0.0;
   out_6807142630278803635[272] = 0.0;
   out_6807142630278803635[273] = 0.0;
   out_6807142630278803635[274] = 0.0;
   out_6807142630278803635[275] = 0.0;
   out_6807142630278803635[276] = 0.0;
   out_6807142630278803635[277] = 0.0;
   out_6807142630278803635[278] = 0.0;
   out_6807142630278803635[279] = 0.0;
   out_6807142630278803635[280] = 0.0;
   out_6807142630278803635[281] = 0.0;
   out_6807142630278803635[282] = 0.0;
   out_6807142630278803635[283] = 0.0;
   out_6807142630278803635[284] = 0.0;
   out_6807142630278803635[285] = 1.0;
   out_6807142630278803635[286] = 0.0;
   out_6807142630278803635[287] = 0.0;
   out_6807142630278803635[288] = 0.0;
   out_6807142630278803635[289] = 0.0;
   out_6807142630278803635[290] = 0.0;
   out_6807142630278803635[291] = 0.0;
   out_6807142630278803635[292] = 0.0;
   out_6807142630278803635[293] = 0.0;
   out_6807142630278803635[294] = 0.0;
   out_6807142630278803635[295] = 0.0;
   out_6807142630278803635[296] = 0.0;
   out_6807142630278803635[297] = 0.0;
   out_6807142630278803635[298] = 0.0;
   out_6807142630278803635[299] = 0.0;
   out_6807142630278803635[300] = 0.0;
   out_6807142630278803635[301] = 0.0;
   out_6807142630278803635[302] = 0.0;
   out_6807142630278803635[303] = 0.0;
   out_6807142630278803635[304] = 1.0;
   out_6807142630278803635[305] = 0.0;
   out_6807142630278803635[306] = 0.0;
   out_6807142630278803635[307] = 0.0;
   out_6807142630278803635[308] = 0.0;
   out_6807142630278803635[309] = 0.0;
   out_6807142630278803635[310] = 0.0;
   out_6807142630278803635[311] = 0.0;
   out_6807142630278803635[312] = 0.0;
   out_6807142630278803635[313] = 0.0;
   out_6807142630278803635[314] = 0.0;
   out_6807142630278803635[315] = 0.0;
   out_6807142630278803635[316] = 0.0;
   out_6807142630278803635[317] = 0.0;
   out_6807142630278803635[318] = 0.0;
   out_6807142630278803635[319] = 0.0;
   out_6807142630278803635[320] = 0.0;
   out_6807142630278803635[321] = 0.0;
   out_6807142630278803635[322] = 0.0;
   out_6807142630278803635[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_6438279809192142379) {
   out_6438279809192142379[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_6438279809192142379[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_6438279809192142379[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_6438279809192142379[3] = dt*state[12] + state[3];
   out_6438279809192142379[4] = dt*state[13] + state[4];
   out_6438279809192142379[5] = dt*state[14] + state[5];
   out_6438279809192142379[6] = state[6];
   out_6438279809192142379[7] = state[7];
   out_6438279809192142379[8] = state[8];
   out_6438279809192142379[9] = state[9];
   out_6438279809192142379[10] = state[10];
   out_6438279809192142379[11] = state[11];
   out_6438279809192142379[12] = state[12];
   out_6438279809192142379[13] = state[13];
   out_6438279809192142379[14] = state[14];
   out_6438279809192142379[15] = state[15];
   out_6438279809192142379[16] = state[16];
   out_6438279809192142379[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8719681830852947447) {
   out_8719681830852947447[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8719681830852947447[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8719681830852947447[2] = 0;
   out_8719681830852947447[3] = 0;
   out_8719681830852947447[4] = 0;
   out_8719681830852947447[5] = 0;
   out_8719681830852947447[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8719681830852947447[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8719681830852947447[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8719681830852947447[9] = 0;
   out_8719681830852947447[10] = 0;
   out_8719681830852947447[11] = 0;
   out_8719681830852947447[12] = 0;
   out_8719681830852947447[13] = 0;
   out_8719681830852947447[14] = 0;
   out_8719681830852947447[15] = 0;
   out_8719681830852947447[16] = 0;
   out_8719681830852947447[17] = 0;
   out_8719681830852947447[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8719681830852947447[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8719681830852947447[20] = 0;
   out_8719681830852947447[21] = 0;
   out_8719681830852947447[22] = 0;
   out_8719681830852947447[23] = 0;
   out_8719681830852947447[24] = 0;
   out_8719681830852947447[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8719681830852947447[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8719681830852947447[27] = 0;
   out_8719681830852947447[28] = 0;
   out_8719681830852947447[29] = 0;
   out_8719681830852947447[30] = 0;
   out_8719681830852947447[31] = 0;
   out_8719681830852947447[32] = 0;
   out_8719681830852947447[33] = 0;
   out_8719681830852947447[34] = 0;
   out_8719681830852947447[35] = 0;
   out_8719681830852947447[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8719681830852947447[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8719681830852947447[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8719681830852947447[39] = 0;
   out_8719681830852947447[40] = 0;
   out_8719681830852947447[41] = 0;
   out_8719681830852947447[42] = 0;
   out_8719681830852947447[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8719681830852947447[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8719681830852947447[45] = 0;
   out_8719681830852947447[46] = 0;
   out_8719681830852947447[47] = 0;
   out_8719681830852947447[48] = 0;
   out_8719681830852947447[49] = 0;
   out_8719681830852947447[50] = 0;
   out_8719681830852947447[51] = 0;
   out_8719681830852947447[52] = 0;
   out_8719681830852947447[53] = 0;
   out_8719681830852947447[54] = 0;
   out_8719681830852947447[55] = 0;
   out_8719681830852947447[56] = 0;
   out_8719681830852947447[57] = 1;
   out_8719681830852947447[58] = 0;
   out_8719681830852947447[59] = 0;
   out_8719681830852947447[60] = 0;
   out_8719681830852947447[61] = 0;
   out_8719681830852947447[62] = 0;
   out_8719681830852947447[63] = 0;
   out_8719681830852947447[64] = 0;
   out_8719681830852947447[65] = 0;
   out_8719681830852947447[66] = dt;
   out_8719681830852947447[67] = 0;
   out_8719681830852947447[68] = 0;
   out_8719681830852947447[69] = 0;
   out_8719681830852947447[70] = 0;
   out_8719681830852947447[71] = 0;
   out_8719681830852947447[72] = 0;
   out_8719681830852947447[73] = 0;
   out_8719681830852947447[74] = 0;
   out_8719681830852947447[75] = 0;
   out_8719681830852947447[76] = 1;
   out_8719681830852947447[77] = 0;
   out_8719681830852947447[78] = 0;
   out_8719681830852947447[79] = 0;
   out_8719681830852947447[80] = 0;
   out_8719681830852947447[81] = 0;
   out_8719681830852947447[82] = 0;
   out_8719681830852947447[83] = 0;
   out_8719681830852947447[84] = 0;
   out_8719681830852947447[85] = dt;
   out_8719681830852947447[86] = 0;
   out_8719681830852947447[87] = 0;
   out_8719681830852947447[88] = 0;
   out_8719681830852947447[89] = 0;
   out_8719681830852947447[90] = 0;
   out_8719681830852947447[91] = 0;
   out_8719681830852947447[92] = 0;
   out_8719681830852947447[93] = 0;
   out_8719681830852947447[94] = 0;
   out_8719681830852947447[95] = 1;
   out_8719681830852947447[96] = 0;
   out_8719681830852947447[97] = 0;
   out_8719681830852947447[98] = 0;
   out_8719681830852947447[99] = 0;
   out_8719681830852947447[100] = 0;
   out_8719681830852947447[101] = 0;
   out_8719681830852947447[102] = 0;
   out_8719681830852947447[103] = 0;
   out_8719681830852947447[104] = dt;
   out_8719681830852947447[105] = 0;
   out_8719681830852947447[106] = 0;
   out_8719681830852947447[107] = 0;
   out_8719681830852947447[108] = 0;
   out_8719681830852947447[109] = 0;
   out_8719681830852947447[110] = 0;
   out_8719681830852947447[111] = 0;
   out_8719681830852947447[112] = 0;
   out_8719681830852947447[113] = 0;
   out_8719681830852947447[114] = 1;
   out_8719681830852947447[115] = 0;
   out_8719681830852947447[116] = 0;
   out_8719681830852947447[117] = 0;
   out_8719681830852947447[118] = 0;
   out_8719681830852947447[119] = 0;
   out_8719681830852947447[120] = 0;
   out_8719681830852947447[121] = 0;
   out_8719681830852947447[122] = 0;
   out_8719681830852947447[123] = 0;
   out_8719681830852947447[124] = 0;
   out_8719681830852947447[125] = 0;
   out_8719681830852947447[126] = 0;
   out_8719681830852947447[127] = 0;
   out_8719681830852947447[128] = 0;
   out_8719681830852947447[129] = 0;
   out_8719681830852947447[130] = 0;
   out_8719681830852947447[131] = 0;
   out_8719681830852947447[132] = 0;
   out_8719681830852947447[133] = 1;
   out_8719681830852947447[134] = 0;
   out_8719681830852947447[135] = 0;
   out_8719681830852947447[136] = 0;
   out_8719681830852947447[137] = 0;
   out_8719681830852947447[138] = 0;
   out_8719681830852947447[139] = 0;
   out_8719681830852947447[140] = 0;
   out_8719681830852947447[141] = 0;
   out_8719681830852947447[142] = 0;
   out_8719681830852947447[143] = 0;
   out_8719681830852947447[144] = 0;
   out_8719681830852947447[145] = 0;
   out_8719681830852947447[146] = 0;
   out_8719681830852947447[147] = 0;
   out_8719681830852947447[148] = 0;
   out_8719681830852947447[149] = 0;
   out_8719681830852947447[150] = 0;
   out_8719681830852947447[151] = 0;
   out_8719681830852947447[152] = 1;
   out_8719681830852947447[153] = 0;
   out_8719681830852947447[154] = 0;
   out_8719681830852947447[155] = 0;
   out_8719681830852947447[156] = 0;
   out_8719681830852947447[157] = 0;
   out_8719681830852947447[158] = 0;
   out_8719681830852947447[159] = 0;
   out_8719681830852947447[160] = 0;
   out_8719681830852947447[161] = 0;
   out_8719681830852947447[162] = 0;
   out_8719681830852947447[163] = 0;
   out_8719681830852947447[164] = 0;
   out_8719681830852947447[165] = 0;
   out_8719681830852947447[166] = 0;
   out_8719681830852947447[167] = 0;
   out_8719681830852947447[168] = 0;
   out_8719681830852947447[169] = 0;
   out_8719681830852947447[170] = 0;
   out_8719681830852947447[171] = 1;
   out_8719681830852947447[172] = 0;
   out_8719681830852947447[173] = 0;
   out_8719681830852947447[174] = 0;
   out_8719681830852947447[175] = 0;
   out_8719681830852947447[176] = 0;
   out_8719681830852947447[177] = 0;
   out_8719681830852947447[178] = 0;
   out_8719681830852947447[179] = 0;
   out_8719681830852947447[180] = 0;
   out_8719681830852947447[181] = 0;
   out_8719681830852947447[182] = 0;
   out_8719681830852947447[183] = 0;
   out_8719681830852947447[184] = 0;
   out_8719681830852947447[185] = 0;
   out_8719681830852947447[186] = 0;
   out_8719681830852947447[187] = 0;
   out_8719681830852947447[188] = 0;
   out_8719681830852947447[189] = 0;
   out_8719681830852947447[190] = 1;
   out_8719681830852947447[191] = 0;
   out_8719681830852947447[192] = 0;
   out_8719681830852947447[193] = 0;
   out_8719681830852947447[194] = 0;
   out_8719681830852947447[195] = 0;
   out_8719681830852947447[196] = 0;
   out_8719681830852947447[197] = 0;
   out_8719681830852947447[198] = 0;
   out_8719681830852947447[199] = 0;
   out_8719681830852947447[200] = 0;
   out_8719681830852947447[201] = 0;
   out_8719681830852947447[202] = 0;
   out_8719681830852947447[203] = 0;
   out_8719681830852947447[204] = 0;
   out_8719681830852947447[205] = 0;
   out_8719681830852947447[206] = 0;
   out_8719681830852947447[207] = 0;
   out_8719681830852947447[208] = 0;
   out_8719681830852947447[209] = 1;
   out_8719681830852947447[210] = 0;
   out_8719681830852947447[211] = 0;
   out_8719681830852947447[212] = 0;
   out_8719681830852947447[213] = 0;
   out_8719681830852947447[214] = 0;
   out_8719681830852947447[215] = 0;
   out_8719681830852947447[216] = 0;
   out_8719681830852947447[217] = 0;
   out_8719681830852947447[218] = 0;
   out_8719681830852947447[219] = 0;
   out_8719681830852947447[220] = 0;
   out_8719681830852947447[221] = 0;
   out_8719681830852947447[222] = 0;
   out_8719681830852947447[223] = 0;
   out_8719681830852947447[224] = 0;
   out_8719681830852947447[225] = 0;
   out_8719681830852947447[226] = 0;
   out_8719681830852947447[227] = 0;
   out_8719681830852947447[228] = 1;
   out_8719681830852947447[229] = 0;
   out_8719681830852947447[230] = 0;
   out_8719681830852947447[231] = 0;
   out_8719681830852947447[232] = 0;
   out_8719681830852947447[233] = 0;
   out_8719681830852947447[234] = 0;
   out_8719681830852947447[235] = 0;
   out_8719681830852947447[236] = 0;
   out_8719681830852947447[237] = 0;
   out_8719681830852947447[238] = 0;
   out_8719681830852947447[239] = 0;
   out_8719681830852947447[240] = 0;
   out_8719681830852947447[241] = 0;
   out_8719681830852947447[242] = 0;
   out_8719681830852947447[243] = 0;
   out_8719681830852947447[244] = 0;
   out_8719681830852947447[245] = 0;
   out_8719681830852947447[246] = 0;
   out_8719681830852947447[247] = 1;
   out_8719681830852947447[248] = 0;
   out_8719681830852947447[249] = 0;
   out_8719681830852947447[250] = 0;
   out_8719681830852947447[251] = 0;
   out_8719681830852947447[252] = 0;
   out_8719681830852947447[253] = 0;
   out_8719681830852947447[254] = 0;
   out_8719681830852947447[255] = 0;
   out_8719681830852947447[256] = 0;
   out_8719681830852947447[257] = 0;
   out_8719681830852947447[258] = 0;
   out_8719681830852947447[259] = 0;
   out_8719681830852947447[260] = 0;
   out_8719681830852947447[261] = 0;
   out_8719681830852947447[262] = 0;
   out_8719681830852947447[263] = 0;
   out_8719681830852947447[264] = 0;
   out_8719681830852947447[265] = 0;
   out_8719681830852947447[266] = 1;
   out_8719681830852947447[267] = 0;
   out_8719681830852947447[268] = 0;
   out_8719681830852947447[269] = 0;
   out_8719681830852947447[270] = 0;
   out_8719681830852947447[271] = 0;
   out_8719681830852947447[272] = 0;
   out_8719681830852947447[273] = 0;
   out_8719681830852947447[274] = 0;
   out_8719681830852947447[275] = 0;
   out_8719681830852947447[276] = 0;
   out_8719681830852947447[277] = 0;
   out_8719681830852947447[278] = 0;
   out_8719681830852947447[279] = 0;
   out_8719681830852947447[280] = 0;
   out_8719681830852947447[281] = 0;
   out_8719681830852947447[282] = 0;
   out_8719681830852947447[283] = 0;
   out_8719681830852947447[284] = 0;
   out_8719681830852947447[285] = 1;
   out_8719681830852947447[286] = 0;
   out_8719681830852947447[287] = 0;
   out_8719681830852947447[288] = 0;
   out_8719681830852947447[289] = 0;
   out_8719681830852947447[290] = 0;
   out_8719681830852947447[291] = 0;
   out_8719681830852947447[292] = 0;
   out_8719681830852947447[293] = 0;
   out_8719681830852947447[294] = 0;
   out_8719681830852947447[295] = 0;
   out_8719681830852947447[296] = 0;
   out_8719681830852947447[297] = 0;
   out_8719681830852947447[298] = 0;
   out_8719681830852947447[299] = 0;
   out_8719681830852947447[300] = 0;
   out_8719681830852947447[301] = 0;
   out_8719681830852947447[302] = 0;
   out_8719681830852947447[303] = 0;
   out_8719681830852947447[304] = 1;
   out_8719681830852947447[305] = 0;
   out_8719681830852947447[306] = 0;
   out_8719681830852947447[307] = 0;
   out_8719681830852947447[308] = 0;
   out_8719681830852947447[309] = 0;
   out_8719681830852947447[310] = 0;
   out_8719681830852947447[311] = 0;
   out_8719681830852947447[312] = 0;
   out_8719681830852947447[313] = 0;
   out_8719681830852947447[314] = 0;
   out_8719681830852947447[315] = 0;
   out_8719681830852947447[316] = 0;
   out_8719681830852947447[317] = 0;
   out_8719681830852947447[318] = 0;
   out_8719681830852947447[319] = 0;
   out_8719681830852947447[320] = 0;
   out_8719681830852947447[321] = 0;
   out_8719681830852947447[322] = 0;
   out_8719681830852947447[323] = 1;
}
void h_4(double *state, double *unused, double *out_2598619130748282794) {
   out_2598619130748282794[0] = state[6] + state[9];
   out_2598619130748282794[1] = state[7] + state[10];
   out_2598619130748282794[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2137219035779017707) {
   out_2137219035779017707[0] = 0;
   out_2137219035779017707[1] = 0;
   out_2137219035779017707[2] = 0;
   out_2137219035779017707[3] = 0;
   out_2137219035779017707[4] = 0;
   out_2137219035779017707[5] = 0;
   out_2137219035779017707[6] = 1;
   out_2137219035779017707[7] = 0;
   out_2137219035779017707[8] = 0;
   out_2137219035779017707[9] = 1;
   out_2137219035779017707[10] = 0;
   out_2137219035779017707[11] = 0;
   out_2137219035779017707[12] = 0;
   out_2137219035779017707[13] = 0;
   out_2137219035779017707[14] = 0;
   out_2137219035779017707[15] = 0;
   out_2137219035779017707[16] = 0;
   out_2137219035779017707[17] = 0;
   out_2137219035779017707[18] = 0;
   out_2137219035779017707[19] = 0;
   out_2137219035779017707[20] = 0;
   out_2137219035779017707[21] = 0;
   out_2137219035779017707[22] = 0;
   out_2137219035779017707[23] = 0;
   out_2137219035779017707[24] = 0;
   out_2137219035779017707[25] = 1;
   out_2137219035779017707[26] = 0;
   out_2137219035779017707[27] = 0;
   out_2137219035779017707[28] = 1;
   out_2137219035779017707[29] = 0;
   out_2137219035779017707[30] = 0;
   out_2137219035779017707[31] = 0;
   out_2137219035779017707[32] = 0;
   out_2137219035779017707[33] = 0;
   out_2137219035779017707[34] = 0;
   out_2137219035779017707[35] = 0;
   out_2137219035779017707[36] = 0;
   out_2137219035779017707[37] = 0;
   out_2137219035779017707[38] = 0;
   out_2137219035779017707[39] = 0;
   out_2137219035779017707[40] = 0;
   out_2137219035779017707[41] = 0;
   out_2137219035779017707[42] = 0;
   out_2137219035779017707[43] = 0;
   out_2137219035779017707[44] = 1;
   out_2137219035779017707[45] = 0;
   out_2137219035779017707[46] = 0;
   out_2137219035779017707[47] = 1;
   out_2137219035779017707[48] = 0;
   out_2137219035779017707[49] = 0;
   out_2137219035779017707[50] = 0;
   out_2137219035779017707[51] = 0;
   out_2137219035779017707[52] = 0;
   out_2137219035779017707[53] = 0;
}
void h_10(double *state, double *unused, double *out_7728804711762559661) {
   out_7728804711762559661[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_7728804711762559661[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_7728804711762559661[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3682779017075027073) {
   out_3682779017075027073[0] = 0;
   out_3682779017075027073[1] = 9.8100000000000005*cos(state[1]);
   out_3682779017075027073[2] = 0;
   out_3682779017075027073[3] = 0;
   out_3682779017075027073[4] = -state[8];
   out_3682779017075027073[5] = state[7];
   out_3682779017075027073[6] = 0;
   out_3682779017075027073[7] = state[5];
   out_3682779017075027073[8] = -state[4];
   out_3682779017075027073[9] = 0;
   out_3682779017075027073[10] = 0;
   out_3682779017075027073[11] = 0;
   out_3682779017075027073[12] = 1;
   out_3682779017075027073[13] = 0;
   out_3682779017075027073[14] = 0;
   out_3682779017075027073[15] = 1;
   out_3682779017075027073[16] = 0;
   out_3682779017075027073[17] = 0;
   out_3682779017075027073[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3682779017075027073[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3682779017075027073[20] = 0;
   out_3682779017075027073[21] = state[8];
   out_3682779017075027073[22] = 0;
   out_3682779017075027073[23] = -state[6];
   out_3682779017075027073[24] = -state[5];
   out_3682779017075027073[25] = 0;
   out_3682779017075027073[26] = state[3];
   out_3682779017075027073[27] = 0;
   out_3682779017075027073[28] = 0;
   out_3682779017075027073[29] = 0;
   out_3682779017075027073[30] = 0;
   out_3682779017075027073[31] = 1;
   out_3682779017075027073[32] = 0;
   out_3682779017075027073[33] = 0;
   out_3682779017075027073[34] = 1;
   out_3682779017075027073[35] = 0;
   out_3682779017075027073[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3682779017075027073[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3682779017075027073[38] = 0;
   out_3682779017075027073[39] = -state[7];
   out_3682779017075027073[40] = state[6];
   out_3682779017075027073[41] = 0;
   out_3682779017075027073[42] = state[4];
   out_3682779017075027073[43] = -state[3];
   out_3682779017075027073[44] = 0;
   out_3682779017075027073[45] = 0;
   out_3682779017075027073[46] = 0;
   out_3682779017075027073[47] = 0;
   out_3682779017075027073[48] = 0;
   out_3682779017075027073[49] = 0;
   out_3682779017075027073[50] = 1;
   out_3682779017075027073[51] = 0;
   out_3682779017075027073[52] = 0;
   out_3682779017075027073[53] = 1;
}
void h_13(double *state, double *unused, double *out_8746038974809318358) {
   out_8746038974809318358[0] = state[3];
   out_8746038974809318358[1] = state[4];
   out_8746038974809318358[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1075054789553315094) {
   out_1075054789553315094[0] = 0;
   out_1075054789553315094[1] = 0;
   out_1075054789553315094[2] = 0;
   out_1075054789553315094[3] = 1;
   out_1075054789553315094[4] = 0;
   out_1075054789553315094[5] = 0;
   out_1075054789553315094[6] = 0;
   out_1075054789553315094[7] = 0;
   out_1075054789553315094[8] = 0;
   out_1075054789553315094[9] = 0;
   out_1075054789553315094[10] = 0;
   out_1075054789553315094[11] = 0;
   out_1075054789553315094[12] = 0;
   out_1075054789553315094[13] = 0;
   out_1075054789553315094[14] = 0;
   out_1075054789553315094[15] = 0;
   out_1075054789553315094[16] = 0;
   out_1075054789553315094[17] = 0;
   out_1075054789553315094[18] = 0;
   out_1075054789553315094[19] = 0;
   out_1075054789553315094[20] = 0;
   out_1075054789553315094[21] = 0;
   out_1075054789553315094[22] = 1;
   out_1075054789553315094[23] = 0;
   out_1075054789553315094[24] = 0;
   out_1075054789553315094[25] = 0;
   out_1075054789553315094[26] = 0;
   out_1075054789553315094[27] = 0;
   out_1075054789553315094[28] = 0;
   out_1075054789553315094[29] = 0;
   out_1075054789553315094[30] = 0;
   out_1075054789553315094[31] = 0;
   out_1075054789553315094[32] = 0;
   out_1075054789553315094[33] = 0;
   out_1075054789553315094[34] = 0;
   out_1075054789553315094[35] = 0;
   out_1075054789553315094[36] = 0;
   out_1075054789553315094[37] = 0;
   out_1075054789553315094[38] = 0;
   out_1075054789553315094[39] = 0;
   out_1075054789553315094[40] = 0;
   out_1075054789553315094[41] = 1;
   out_1075054789553315094[42] = 0;
   out_1075054789553315094[43] = 0;
   out_1075054789553315094[44] = 0;
   out_1075054789553315094[45] = 0;
   out_1075054789553315094[46] = 0;
   out_1075054789553315094[47] = 0;
   out_1075054789553315094[48] = 0;
   out_1075054789553315094[49] = 0;
   out_1075054789553315094[50] = 0;
   out_1075054789553315094[51] = 0;
   out_1075054789553315094[52] = 0;
   out_1075054789553315094[53] = 0;
}
void h_14(double *state, double *unused, double *out_4279600364142536095) {
   out_4279600364142536095[0] = state[6];
   out_4279600364142536095[1] = state[7];
   out_4279600364142536095[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5220007468074390003) {
   out_5220007468074390003[0] = 0;
   out_5220007468074390003[1] = 0;
   out_5220007468074390003[2] = 0;
   out_5220007468074390003[3] = 0;
   out_5220007468074390003[4] = 0;
   out_5220007468074390003[5] = 0;
   out_5220007468074390003[6] = 1;
   out_5220007468074390003[7] = 0;
   out_5220007468074390003[8] = 0;
   out_5220007468074390003[9] = 0;
   out_5220007468074390003[10] = 0;
   out_5220007468074390003[11] = 0;
   out_5220007468074390003[12] = 0;
   out_5220007468074390003[13] = 0;
   out_5220007468074390003[14] = 0;
   out_5220007468074390003[15] = 0;
   out_5220007468074390003[16] = 0;
   out_5220007468074390003[17] = 0;
   out_5220007468074390003[18] = 0;
   out_5220007468074390003[19] = 0;
   out_5220007468074390003[20] = 0;
   out_5220007468074390003[21] = 0;
   out_5220007468074390003[22] = 0;
   out_5220007468074390003[23] = 0;
   out_5220007468074390003[24] = 0;
   out_5220007468074390003[25] = 1;
   out_5220007468074390003[26] = 0;
   out_5220007468074390003[27] = 0;
   out_5220007468074390003[28] = 0;
   out_5220007468074390003[29] = 0;
   out_5220007468074390003[30] = 0;
   out_5220007468074390003[31] = 0;
   out_5220007468074390003[32] = 0;
   out_5220007468074390003[33] = 0;
   out_5220007468074390003[34] = 0;
   out_5220007468074390003[35] = 0;
   out_5220007468074390003[36] = 0;
   out_5220007468074390003[37] = 0;
   out_5220007468074390003[38] = 0;
   out_5220007468074390003[39] = 0;
   out_5220007468074390003[40] = 0;
   out_5220007468074390003[41] = 0;
   out_5220007468074390003[42] = 0;
   out_5220007468074390003[43] = 0;
   out_5220007468074390003[44] = 1;
   out_5220007468074390003[45] = 0;
   out_5220007468074390003[46] = 0;
   out_5220007468074390003[47] = 0;
   out_5220007468074390003[48] = 0;
   out_5220007468074390003[49] = 0;
   out_5220007468074390003[50] = 0;
   out_5220007468074390003[51] = 0;
   out_5220007468074390003[52] = 0;
   out_5220007468074390003[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3122087598286484509) {
  err_fun(nom_x, delta_x, out_3122087598286484509);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6671609920081726507) {
  inv_err_fun(nom_x, true_x, out_6671609920081726507);
}
void pose_H_mod_fun(double *state, double *out_6807142630278803635) {
  H_mod_fun(state, out_6807142630278803635);
}
void pose_f_fun(double *state, double dt, double *out_6438279809192142379) {
  f_fun(state,  dt, out_6438279809192142379);
}
void pose_F_fun(double *state, double dt, double *out_8719681830852947447) {
  F_fun(state,  dt, out_8719681830852947447);
}
void pose_h_4(double *state, double *unused, double *out_2598619130748282794) {
  h_4(state, unused, out_2598619130748282794);
}
void pose_H_4(double *state, double *unused, double *out_2137219035779017707) {
  H_4(state, unused, out_2137219035779017707);
}
void pose_h_10(double *state, double *unused, double *out_7728804711762559661) {
  h_10(state, unused, out_7728804711762559661);
}
void pose_H_10(double *state, double *unused, double *out_3682779017075027073) {
  H_10(state, unused, out_3682779017075027073);
}
void pose_h_13(double *state, double *unused, double *out_8746038974809318358) {
  h_13(state, unused, out_8746038974809318358);
}
void pose_H_13(double *state, double *unused, double *out_1075054789553315094) {
  H_13(state, unused, out_1075054789553315094);
}
void pose_h_14(double *state, double *unused, double *out_4279600364142536095) {
  h_14(state, unused, out_4279600364142536095);
}
void pose_H_14(double *state, double *unused, double *out_5220007468074390003) {
  H_14(state, unused, out_5220007468074390003);
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
