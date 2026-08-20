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
void err_fun(double *nom_x, double *delta_x, double *out_5813097801788606117) {
   out_5813097801788606117[0] = delta_x[0] + nom_x[0];
   out_5813097801788606117[1] = delta_x[1] + nom_x[1];
   out_5813097801788606117[2] = delta_x[2] + nom_x[2];
   out_5813097801788606117[3] = delta_x[3] + nom_x[3];
   out_5813097801788606117[4] = delta_x[4] + nom_x[4];
   out_5813097801788606117[5] = delta_x[5] + nom_x[5];
   out_5813097801788606117[6] = delta_x[6] + nom_x[6];
   out_5813097801788606117[7] = delta_x[7] + nom_x[7];
   out_5813097801788606117[8] = delta_x[8] + nom_x[8];
   out_5813097801788606117[9] = delta_x[9] + nom_x[9];
   out_5813097801788606117[10] = delta_x[10] + nom_x[10];
   out_5813097801788606117[11] = delta_x[11] + nom_x[11];
   out_5813097801788606117[12] = delta_x[12] + nom_x[12];
   out_5813097801788606117[13] = delta_x[13] + nom_x[13];
   out_5813097801788606117[14] = delta_x[14] + nom_x[14];
   out_5813097801788606117[15] = delta_x[15] + nom_x[15];
   out_5813097801788606117[16] = delta_x[16] + nom_x[16];
   out_5813097801788606117[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_265932847343752274) {
   out_265932847343752274[0] = -nom_x[0] + true_x[0];
   out_265932847343752274[1] = -nom_x[1] + true_x[1];
   out_265932847343752274[2] = -nom_x[2] + true_x[2];
   out_265932847343752274[3] = -nom_x[3] + true_x[3];
   out_265932847343752274[4] = -nom_x[4] + true_x[4];
   out_265932847343752274[5] = -nom_x[5] + true_x[5];
   out_265932847343752274[6] = -nom_x[6] + true_x[6];
   out_265932847343752274[7] = -nom_x[7] + true_x[7];
   out_265932847343752274[8] = -nom_x[8] + true_x[8];
   out_265932847343752274[9] = -nom_x[9] + true_x[9];
   out_265932847343752274[10] = -nom_x[10] + true_x[10];
   out_265932847343752274[11] = -nom_x[11] + true_x[11];
   out_265932847343752274[12] = -nom_x[12] + true_x[12];
   out_265932847343752274[13] = -nom_x[13] + true_x[13];
   out_265932847343752274[14] = -nom_x[14] + true_x[14];
   out_265932847343752274[15] = -nom_x[15] + true_x[15];
   out_265932847343752274[16] = -nom_x[16] + true_x[16];
   out_265932847343752274[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3782749078324294962) {
   out_3782749078324294962[0] = 1.0;
   out_3782749078324294962[1] = 0.0;
   out_3782749078324294962[2] = 0.0;
   out_3782749078324294962[3] = 0.0;
   out_3782749078324294962[4] = 0.0;
   out_3782749078324294962[5] = 0.0;
   out_3782749078324294962[6] = 0.0;
   out_3782749078324294962[7] = 0.0;
   out_3782749078324294962[8] = 0.0;
   out_3782749078324294962[9] = 0.0;
   out_3782749078324294962[10] = 0.0;
   out_3782749078324294962[11] = 0.0;
   out_3782749078324294962[12] = 0.0;
   out_3782749078324294962[13] = 0.0;
   out_3782749078324294962[14] = 0.0;
   out_3782749078324294962[15] = 0.0;
   out_3782749078324294962[16] = 0.0;
   out_3782749078324294962[17] = 0.0;
   out_3782749078324294962[18] = 0.0;
   out_3782749078324294962[19] = 1.0;
   out_3782749078324294962[20] = 0.0;
   out_3782749078324294962[21] = 0.0;
   out_3782749078324294962[22] = 0.0;
   out_3782749078324294962[23] = 0.0;
   out_3782749078324294962[24] = 0.0;
   out_3782749078324294962[25] = 0.0;
   out_3782749078324294962[26] = 0.0;
   out_3782749078324294962[27] = 0.0;
   out_3782749078324294962[28] = 0.0;
   out_3782749078324294962[29] = 0.0;
   out_3782749078324294962[30] = 0.0;
   out_3782749078324294962[31] = 0.0;
   out_3782749078324294962[32] = 0.0;
   out_3782749078324294962[33] = 0.0;
   out_3782749078324294962[34] = 0.0;
   out_3782749078324294962[35] = 0.0;
   out_3782749078324294962[36] = 0.0;
   out_3782749078324294962[37] = 0.0;
   out_3782749078324294962[38] = 1.0;
   out_3782749078324294962[39] = 0.0;
   out_3782749078324294962[40] = 0.0;
   out_3782749078324294962[41] = 0.0;
   out_3782749078324294962[42] = 0.0;
   out_3782749078324294962[43] = 0.0;
   out_3782749078324294962[44] = 0.0;
   out_3782749078324294962[45] = 0.0;
   out_3782749078324294962[46] = 0.0;
   out_3782749078324294962[47] = 0.0;
   out_3782749078324294962[48] = 0.0;
   out_3782749078324294962[49] = 0.0;
   out_3782749078324294962[50] = 0.0;
   out_3782749078324294962[51] = 0.0;
   out_3782749078324294962[52] = 0.0;
   out_3782749078324294962[53] = 0.0;
   out_3782749078324294962[54] = 0.0;
   out_3782749078324294962[55] = 0.0;
   out_3782749078324294962[56] = 0.0;
   out_3782749078324294962[57] = 1.0;
   out_3782749078324294962[58] = 0.0;
   out_3782749078324294962[59] = 0.0;
   out_3782749078324294962[60] = 0.0;
   out_3782749078324294962[61] = 0.0;
   out_3782749078324294962[62] = 0.0;
   out_3782749078324294962[63] = 0.0;
   out_3782749078324294962[64] = 0.0;
   out_3782749078324294962[65] = 0.0;
   out_3782749078324294962[66] = 0.0;
   out_3782749078324294962[67] = 0.0;
   out_3782749078324294962[68] = 0.0;
   out_3782749078324294962[69] = 0.0;
   out_3782749078324294962[70] = 0.0;
   out_3782749078324294962[71] = 0.0;
   out_3782749078324294962[72] = 0.0;
   out_3782749078324294962[73] = 0.0;
   out_3782749078324294962[74] = 0.0;
   out_3782749078324294962[75] = 0.0;
   out_3782749078324294962[76] = 1.0;
   out_3782749078324294962[77] = 0.0;
   out_3782749078324294962[78] = 0.0;
   out_3782749078324294962[79] = 0.0;
   out_3782749078324294962[80] = 0.0;
   out_3782749078324294962[81] = 0.0;
   out_3782749078324294962[82] = 0.0;
   out_3782749078324294962[83] = 0.0;
   out_3782749078324294962[84] = 0.0;
   out_3782749078324294962[85] = 0.0;
   out_3782749078324294962[86] = 0.0;
   out_3782749078324294962[87] = 0.0;
   out_3782749078324294962[88] = 0.0;
   out_3782749078324294962[89] = 0.0;
   out_3782749078324294962[90] = 0.0;
   out_3782749078324294962[91] = 0.0;
   out_3782749078324294962[92] = 0.0;
   out_3782749078324294962[93] = 0.0;
   out_3782749078324294962[94] = 0.0;
   out_3782749078324294962[95] = 1.0;
   out_3782749078324294962[96] = 0.0;
   out_3782749078324294962[97] = 0.0;
   out_3782749078324294962[98] = 0.0;
   out_3782749078324294962[99] = 0.0;
   out_3782749078324294962[100] = 0.0;
   out_3782749078324294962[101] = 0.0;
   out_3782749078324294962[102] = 0.0;
   out_3782749078324294962[103] = 0.0;
   out_3782749078324294962[104] = 0.0;
   out_3782749078324294962[105] = 0.0;
   out_3782749078324294962[106] = 0.0;
   out_3782749078324294962[107] = 0.0;
   out_3782749078324294962[108] = 0.0;
   out_3782749078324294962[109] = 0.0;
   out_3782749078324294962[110] = 0.0;
   out_3782749078324294962[111] = 0.0;
   out_3782749078324294962[112] = 0.0;
   out_3782749078324294962[113] = 0.0;
   out_3782749078324294962[114] = 1.0;
   out_3782749078324294962[115] = 0.0;
   out_3782749078324294962[116] = 0.0;
   out_3782749078324294962[117] = 0.0;
   out_3782749078324294962[118] = 0.0;
   out_3782749078324294962[119] = 0.0;
   out_3782749078324294962[120] = 0.0;
   out_3782749078324294962[121] = 0.0;
   out_3782749078324294962[122] = 0.0;
   out_3782749078324294962[123] = 0.0;
   out_3782749078324294962[124] = 0.0;
   out_3782749078324294962[125] = 0.0;
   out_3782749078324294962[126] = 0.0;
   out_3782749078324294962[127] = 0.0;
   out_3782749078324294962[128] = 0.0;
   out_3782749078324294962[129] = 0.0;
   out_3782749078324294962[130] = 0.0;
   out_3782749078324294962[131] = 0.0;
   out_3782749078324294962[132] = 0.0;
   out_3782749078324294962[133] = 1.0;
   out_3782749078324294962[134] = 0.0;
   out_3782749078324294962[135] = 0.0;
   out_3782749078324294962[136] = 0.0;
   out_3782749078324294962[137] = 0.0;
   out_3782749078324294962[138] = 0.0;
   out_3782749078324294962[139] = 0.0;
   out_3782749078324294962[140] = 0.0;
   out_3782749078324294962[141] = 0.0;
   out_3782749078324294962[142] = 0.0;
   out_3782749078324294962[143] = 0.0;
   out_3782749078324294962[144] = 0.0;
   out_3782749078324294962[145] = 0.0;
   out_3782749078324294962[146] = 0.0;
   out_3782749078324294962[147] = 0.0;
   out_3782749078324294962[148] = 0.0;
   out_3782749078324294962[149] = 0.0;
   out_3782749078324294962[150] = 0.0;
   out_3782749078324294962[151] = 0.0;
   out_3782749078324294962[152] = 1.0;
   out_3782749078324294962[153] = 0.0;
   out_3782749078324294962[154] = 0.0;
   out_3782749078324294962[155] = 0.0;
   out_3782749078324294962[156] = 0.0;
   out_3782749078324294962[157] = 0.0;
   out_3782749078324294962[158] = 0.0;
   out_3782749078324294962[159] = 0.0;
   out_3782749078324294962[160] = 0.0;
   out_3782749078324294962[161] = 0.0;
   out_3782749078324294962[162] = 0.0;
   out_3782749078324294962[163] = 0.0;
   out_3782749078324294962[164] = 0.0;
   out_3782749078324294962[165] = 0.0;
   out_3782749078324294962[166] = 0.0;
   out_3782749078324294962[167] = 0.0;
   out_3782749078324294962[168] = 0.0;
   out_3782749078324294962[169] = 0.0;
   out_3782749078324294962[170] = 0.0;
   out_3782749078324294962[171] = 1.0;
   out_3782749078324294962[172] = 0.0;
   out_3782749078324294962[173] = 0.0;
   out_3782749078324294962[174] = 0.0;
   out_3782749078324294962[175] = 0.0;
   out_3782749078324294962[176] = 0.0;
   out_3782749078324294962[177] = 0.0;
   out_3782749078324294962[178] = 0.0;
   out_3782749078324294962[179] = 0.0;
   out_3782749078324294962[180] = 0.0;
   out_3782749078324294962[181] = 0.0;
   out_3782749078324294962[182] = 0.0;
   out_3782749078324294962[183] = 0.0;
   out_3782749078324294962[184] = 0.0;
   out_3782749078324294962[185] = 0.0;
   out_3782749078324294962[186] = 0.0;
   out_3782749078324294962[187] = 0.0;
   out_3782749078324294962[188] = 0.0;
   out_3782749078324294962[189] = 0.0;
   out_3782749078324294962[190] = 1.0;
   out_3782749078324294962[191] = 0.0;
   out_3782749078324294962[192] = 0.0;
   out_3782749078324294962[193] = 0.0;
   out_3782749078324294962[194] = 0.0;
   out_3782749078324294962[195] = 0.0;
   out_3782749078324294962[196] = 0.0;
   out_3782749078324294962[197] = 0.0;
   out_3782749078324294962[198] = 0.0;
   out_3782749078324294962[199] = 0.0;
   out_3782749078324294962[200] = 0.0;
   out_3782749078324294962[201] = 0.0;
   out_3782749078324294962[202] = 0.0;
   out_3782749078324294962[203] = 0.0;
   out_3782749078324294962[204] = 0.0;
   out_3782749078324294962[205] = 0.0;
   out_3782749078324294962[206] = 0.0;
   out_3782749078324294962[207] = 0.0;
   out_3782749078324294962[208] = 0.0;
   out_3782749078324294962[209] = 1.0;
   out_3782749078324294962[210] = 0.0;
   out_3782749078324294962[211] = 0.0;
   out_3782749078324294962[212] = 0.0;
   out_3782749078324294962[213] = 0.0;
   out_3782749078324294962[214] = 0.0;
   out_3782749078324294962[215] = 0.0;
   out_3782749078324294962[216] = 0.0;
   out_3782749078324294962[217] = 0.0;
   out_3782749078324294962[218] = 0.0;
   out_3782749078324294962[219] = 0.0;
   out_3782749078324294962[220] = 0.0;
   out_3782749078324294962[221] = 0.0;
   out_3782749078324294962[222] = 0.0;
   out_3782749078324294962[223] = 0.0;
   out_3782749078324294962[224] = 0.0;
   out_3782749078324294962[225] = 0.0;
   out_3782749078324294962[226] = 0.0;
   out_3782749078324294962[227] = 0.0;
   out_3782749078324294962[228] = 1.0;
   out_3782749078324294962[229] = 0.0;
   out_3782749078324294962[230] = 0.0;
   out_3782749078324294962[231] = 0.0;
   out_3782749078324294962[232] = 0.0;
   out_3782749078324294962[233] = 0.0;
   out_3782749078324294962[234] = 0.0;
   out_3782749078324294962[235] = 0.0;
   out_3782749078324294962[236] = 0.0;
   out_3782749078324294962[237] = 0.0;
   out_3782749078324294962[238] = 0.0;
   out_3782749078324294962[239] = 0.0;
   out_3782749078324294962[240] = 0.0;
   out_3782749078324294962[241] = 0.0;
   out_3782749078324294962[242] = 0.0;
   out_3782749078324294962[243] = 0.0;
   out_3782749078324294962[244] = 0.0;
   out_3782749078324294962[245] = 0.0;
   out_3782749078324294962[246] = 0.0;
   out_3782749078324294962[247] = 1.0;
   out_3782749078324294962[248] = 0.0;
   out_3782749078324294962[249] = 0.0;
   out_3782749078324294962[250] = 0.0;
   out_3782749078324294962[251] = 0.0;
   out_3782749078324294962[252] = 0.0;
   out_3782749078324294962[253] = 0.0;
   out_3782749078324294962[254] = 0.0;
   out_3782749078324294962[255] = 0.0;
   out_3782749078324294962[256] = 0.0;
   out_3782749078324294962[257] = 0.0;
   out_3782749078324294962[258] = 0.0;
   out_3782749078324294962[259] = 0.0;
   out_3782749078324294962[260] = 0.0;
   out_3782749078324294962[261] = 0.0;
   out_3782749078324294962[262] = 0.0;
   out_3782749078324294962[263] = 0.0;
   out_3782749078324294962[264] = 0.0;
   out_3782749078324294962[265] = 0.0;
   out_3782749078324294962[266] = 1.0;
   out_3782749078324294962[267] = 0.0;
   out_3782749078324294962[268] = 0.0;
   out_3782749078324294962[269] = 0.0;
   out_3782749078324294962[270] = 0.0;
   out_3782749078324294962[271] = 0.0;
   out_3782749078324294962[272] = 0.0;
   out_3782749078324294962[273] = 0.0;
   out_3782749078324294962[274] = 0.0;
   out_3782749078324294962[275] = 0.0;
   out_3782749078324294962[276] = 0.0;
   out_3782749078324294962[277] = 0.0;
   out_3782749078324294962[278] = 0.0;
   out_3782749078324294962[279] = 0.0;
   out_3782749078324294962[280] = 0.0;
   out_3782749078324294962[281] = 0.0;
   out_3782749078324294962[282] = 0.0;
   out_3782749078324294962[283] = 0.0;
   out_3782749078324294962[284] = 0.0;
   out_3782749078324294962[285] = 1.0;
   out_3782749078324294962[286] = 0.0;
   out_3782749078324294962[287] = 0.0;
   out_3782749078324294962[288] = 0.0;
   out_3782749078324294962[289] = 0.0;
   out_3782749078324294962[290] = 0.0;
   out_3782749078324294962[291] = 0.0;
   out_3782749078324294962[292] = 0.0;
   out_3782749078324294962[293] = 0.0;
   out_3782749078324294962[294] = 0.0;
   out_3782749078324294962[295] = 0.0;
   out_3782749078324294962[296] = 0.0;
   out_3782749078324294962[297] = 0.0;
   out_3782749078324294962[298] = 0.0;
   out_3782749078324294962[299] = 0.0;
   out_3782749078324294962[300] = 0.0;
   out_3782749078324294962[301] = 0.0;
   out_3782749078324294962[302] = 0.0;
   out_3782749078324294962[303] = 0.0;
   out_3782749078324294962[304] = 1.0;
   out_3782749078324294962[305] = 0.0;
   out_3782749078324294962[306] = 0.0;
   out_3782749078324294962[307] = 0.0;
   out_3782749078324294962[308] = 0.0;
   out_3782749078324294962[309] = 0.0;
   out_3782749078324294962[310] = 0.0;
   out_3782749078324294962[311] = 0.0;
   out_3782749078324294962[312] = 0.0;
   out_3782749078324294962[313] = 0.0;
   out_3782749078324294962[314] = 0.0;
   out_3782749078324294962[315] = 0.0;
   out_3782749078324294962[316] = 0.0;
   out_3782749078324294962[317] = 0.0;
   out_3782749078324294962[318] = 0.0;
   out_3782749078324294962[319] = 0.0;
   out_3782749078324294962[320] = 0.0;
   out_3782749078324294962[321] = 0.0;
   out_3782749078324294962[322] = 0.0;
   out_3782749078324294962[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_2316687695349101514) {
   out_2316687695349101514[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_2316687695349101514[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_2316687695349101514[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_2316687695349101514[3] = dt*state[12] + state[3];
   out_2316687695349101514[4] = dt*state[13] + state[4];
   out_2316687695349101514[5] = dt*state[14] + state[5];
   out_2316687695349101514[6] = state[6];
   out_2316687695349101514[7] = state[7];
   out_2316687695349101514[8] = state[8];
   out_2316687695349101514[9] = state[9];
   out_2316687695349101514[10] = state[10];
   out_2316687695349101514[11] = state[11];
   out_2316687695349101514[12] = state[12];
   out_2316687695349101514[13] = state[13];
   out_2316687695349101514[14] = state[14];
   out_2316687695349101514[15] = state[15];
   out_2316687695349101514[16] = state[16];
   out_2316687695349101514[17] = state[17];
}
void F_fun(double *state, double dt, double *out_830203783768276833) {
   out_830203783768276833[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_830203783768276833[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_830203783768276833[2] = 0;
   out_830203783768276833[3] = 0;
   out_830203783768276833[4] = 0;
   out_830203783768276833[5] = 0;
   out_830203783768276833[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_830203783768276833[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_830203783768276833[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_830203783768276833[9] = 0;
   out_830203783768276833[10] = 0;
   out_830203783768276833[11] = 0;
   out_830203783768276833[12] = 0;
   out_830203783768276833[13] = 0;
   out_830203783768276833[14] = 0;
   out_830203783768276833[15] = 0;
   out_830203783768276833[16] = 0;
   out_830203783768276833[17] = 0;
   out_830203783768276833[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_830203783768276833[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_830203783768276833[20] = 0;
   out_830203783768276833[21] = 0;
   out_830203783768276833[22] = 0;
   out_830203783768276833[23] = 0;
   out_830203783768276833[24] = 0;
   out_830203783768276833[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_830203783768276833[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_830203783768276833[27] = 0;
   out_830203783768276833[28] = 0;
   out_830203783768276833[29] = 0;
   out_830203783768276833[30] = 0;
   out_830203783768276833[31] = 0;
   out_830203783768276833[32] = 0;
   out_830203783768276833[33] = 0;
   out_830203783768276833[34] = 0;
   out_830203783768276833[35] = 0;
   out_830203783768276833[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_830203783768276833[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_830203783768276833[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_830203783768276833[39] = 0;
   out_830203783768276833[40] = 0;
   out_830203783768276833[41] = 0;
   out_830203783768276833[42] = 0;
   out_830203783768276833[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_830203783768276833[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_830203783768276833[45] = 0;
   out_830203783768276833[46] = 0;
   out_830203783768276833[47] = 0;
   out_830203783768276833[48] = 0;
   out_830203783768276833[49] = 0;
   out_830203783768276833[50] = 0;
   out_830203783768276833[51] = 0;
   out_830203783768276833[52] = 0;
   out_830203783768276833[53] = 0;
   out_830203783768276833[54] = 0;
   out_830203783768276833[55] = 0;
   out_830203783768276833[56] = 0;
   out_830203783768276833[57] = 1;
   out_830203783768276833[58] = 0;
   out_830203783768276833[59] = 0;
   out_830203783768276833[60] = 0;
   out_830203783768276833[61] = 0;
   out_830203783768276833[62] = 0;
   out_830203783768276833[63] = 0;
   out_830203783768276833[64] = 0;
   out_830203783768276833[65] = 0;
   out_830203783768276833[66] = dt;
   out_830203783768276833[67] = 0;
   out_830203783768276833[68] = 0;
   out_830203783768276833[69] = 0;
   out_830203783768276833[70] = 0;
   out_830203783768276833[71] = 0;
   out_830203783768276833[72] = 0;
   out_830203783768276833[73] = 0;
   out_830203783768276833[74] = 0;
   out_830203783768276833[75] = 0;
   out_830203783768276833[76] = 1;
   out_830203783768276833[77] = 0;
   out_830203783768276833[78] = 0;
   out_830203783768276833[79] = 0;
   out_830203783768276833[80] = 0;
   out_830203783768276833[81] = 0;
   out_830203783768276833[82] = 0;
   out_830203783768276833[83] = 0;
   out_830203783768276833[84] = 0;
   out_830203783768276833[85] = dt;
   out_830203783768276833[86] = 0;
   out_830203783768276833[87] = 0;
   out_830203783768276833[88] = 0;
   out_830203783768276833[89] = 0;
   out_830203783768276833[90] = 0;
   out_830203783768276833[91] = 0;
   out_830203783768276833[92] = 0;
   out_830203783768276833[93] = 0;
   out_830203783768276833[94] = 0;
   out_830203783768276833[95] = 1;
   out_830203783768276833[96] = 0;
   out_830203783768276833[97] = 0;
   out_830203783768276833[98] = 0;
   out_830203783768276833[99] = 0;
   out_830203783768276833[100] = 0;
   out_830203783768276833[101] = 0;
   out_830203783768276833[102] = 0;
   out_830203783768276833[103] = 0;
   out_830203783768276833[104] = dt;
   out_830203783768276833[105] = 0;
   out_830203783768276833[106] = 0;
   out_830203783768276833[107] = 0;
   out_830203783768276833[108] = 0;
   out_830203783768276833[109] = 0;
   out_830203783768276833[110] = 0;
   out_830203783768276833[111] = 0;
   out_830203783768276833[112] = 0;
   out_830203783768276833[113] = 0;
   out_830203783768276833[114] = 1;
   out_830203783768276833[115] = 0;
   out_830203783768276833[116] = 0;
   out_830203783768276833[117] = 0;
   out_830203783768276833[118] = 0;
   out_830203783768276833[119] = 0;
   out_830203783768276833[120] = 0;
   out_830203783768276833[121] = 0;
   out_830203783768276833[122] = 0;
   out_830203783768276833[123] = 0;
   out_830203783768276833[124] = 0;
   out_830203783768276833[125] = 0;
   out_830203783768276833[126] = 0;
   out_830203783768276833[127] = 0;
   out_830203783768276833[128] = 0;
   out_830203783768276833[129] = 0;
   out_830203783768276833[130] = 0;
   out_830203783768276833[131] = 0;
   out_830203783768276833[132] = 0;
   out_830203783768276833[133] = 1;
   out_830203783768276833[134] = 0;
   out_830203783768276833[135] = 0;
   out_830203783768276833[136] = 0;
   out_830203783768276833[137] = 0;
   out_830203783768276833[138] = 0;
   out_830203783768276833[139] = 0;
   out_830203783768276833[140] = 0;
   out_830203783768276833[141] = 0;
   out_830203783768276833[142] = 0;
   out_830203783768276833[143] = 0;
   out_830203783768276833[144] = 0;
   out_830203783768276833[145] = 0;
   out_830203783768276833[146] = 0;
   out_830203783768276833[147] = 0;
   out_830203783768276833[148] = 0;
   out_830203783768276833[149] = 0;
   out_830203783768276833[150] = 0;
   out_830203783768276833[151] = 0;
   out_830203783768276833[152] = 1;
   out_830203783768276833[153] = 0;
   out_830203783768276833[154] = 0;
   out_830203783768276833[155] = 0;
   out_830203783768276833[156] = 0;
   out_830203783768276833[157] = 0;
   out_830203783768276833[158] = 0;
   out_830203783768276833[159] = 0;
   out_830203783768276833[160] = 0;
   out_830203783768276833[161] = 0;
   out_830203783768276833[162] = 0;
   out_830203783768276833[163] = 0;
   out_830203783768276833[164] = 0;
   out_830203783768276833[165] = 0;
   out_830203783768276833[166] = 0;
   out_830203783768276833[167] = 0;
   out_830203783768276833[168] = 0;
   out_830203783768276833[169] = 0;
   out_830203783768276833[170] = 0;
   out_830203783768276833[171] = 1;
   out_830203783768276833[172] = 0;
   out_830203783768276833[173] = 0;
   out_830203783768276833[174] = 0;
   out_830203783768276833[175] = 0;
   out_830203783768276833[176] = 0;
   out_830203783768276833[177] = 0;
   out_830203783768276833[178] = 0;
   out_830203783768276833[179] = 0;
   out_830203783768276833[180] = 0;
   out_830203783768276833[181] = 0;
   out_830203783768276833[182] = 0;
   out_830203783768276833[183] = 0;
   out_830203783768276833[184] = 0;
   out_830203783768276833[185] = 0;
   out_830203783768276833[186] = 0;
   out_830203783768276833[187] = 0;
   out_830203783768276833[188] = 0;
   out_830203783768276833[189] = 0;
   out_830203783768276833[190] = 1;
   out_830203783768276833[191] = 0;
   out_830203783768276833[192] = 0;
   out_830203783768276833[193] = 0;
   out_830203783768276833[194] = 0;
   out_830203783768276833[195] = 0;
   out_830203783768276833[196] = 0;
   out_830203783768276833[197] = 0;
   out_830203783768276833[198] = 0;
   out_830203783768276833[199] = 0;
   out_830203783768276833[200] = 0;
   out_830203783768276833[201] = 0;
   out_830203783768276833[202] = 0;
   out_830203783768276833[203] = 0;
   out_830203783768276833[204] = 0;
   out_830203783768276833[205] = 0;
   out_830203783768276833[206] = 0;
   out_830203783768276833[207] = 0;
   out_830203783768276833[208] = 0;
   out_830203783768276833[209] = 1;
   out_830203783768276833[210] = 0;
   out_830203783768276833[211] = 0;
   out_830203783768276833[212] = 0;
   out_830203783768276833[213] = 0;
   out_830203783768276833[214] = 0;
   out_830203783768276833[215] = 0;
   out_830203783768276833[216] = 0;
   out_830203783768276833[217] = 0;
   out_830203783768276833[218] = 0;
   out_830203783768276833[219] = 0;
   out_830203783768276833[220] = 0;
   out_830203783768276833[221] = 0;
   out_830203783768276833[222] = 0;
   out_830203783768276833[223] = 0;
   out_830203783768276833[224] = 0;
   out_830203783768276833[225] = 0;
   out_830203783768276833[226] = 0;
   out_830203783768276833[227] = 0;
   out_830203783768276833[228] = 1;
   out_830203783768276833[229] = 0;
   out_830203783768276833[230] = 0;
   out_830203783768276833[231] = 0;
   out_830203783768276833[232] = 0;
   out_830203783768276833[233] = 0;
   out_830203783768276833[234] = 0;
   out_830203783768276833[235] = 0;
   out_830203783768276833[236] = 0;
   out_830203783768276833[237] = 0;
   out_830203783768276833[238] = 0;
   out_830203783768276833[239] = 0;
   out_830203783768276833[240] = 0;
   out_830203783768276833[241] = 0;
   out_830203783768276833[242] = 0;
   out_830203783768276833[243] = 0;
   out_830203783768276833[244] = 0;
   out_830203783768276833[245] = 0;
   out_830203783768276833[246] = 0;
   out_830203783768276833[247] = 1;
   out_830203783768276833[248] = 0;
   out_830203783768276833[249] = 0;
   out_830203783768276833[250] = 0;
   out_830203783768276833[251] = 0;
   out_830203783768276833[252] = 0;
   out_830203783768276833[253] = 0;
   out_830203783768276833[254] = 0;
   out_830203783768276833[255] = 0;
   out_830203783768276833[256] = 0;
   out_830203783768276833[257] = 0;
   out_830203783768276833[258] = 0;
   out_830203783768276833[259] = 0;
   out_830203783768276833[260] = 0;
   out_830203783768276833[261] = 0;
   out_830203783768276833[262] = 0;
   out_830203783768276833[263] = 0;
   out_830203783768276833[264] = 0;
   out_830203783768276833[265] = 0;
   out_830203783768276833[266] = 1;
   out_830203783768276833[267] = 0;
   out_830203783768276833[268] = 0;
   out_830203783768276833[269] = 0;
   out_830203783768276833[270] = 0;
   out_830203783768276833[271] = 0;
   out_830203783768276833[272] = 0;
   out_830203783768276833[273] = 0;
   out_830203783768276833[274] = 0;
   out_830203783768276833[275] = 0;
   out_830203783768276833[276] = 0;
   out_830203783768276833[277] = 0;
   out_830203783768276833[278] = 0;
   out_830203783768276833[279] = 0;
   out_830203783768276833[280] = 0;
   out_830203783768276833[281] = 0;
   out_830203783768276833[282] = 0;
   out_830203783768276833[283] = 0;
   out_830203783768276833[284] = 0;
   out_830203783768276833[285] = 1;
   out_830203783768276833[286] = 0;
   out_830203783768276833[287] = 0;
   out_830203783768276833[288] = 0;
   out_830203783768276833[289] = 0;
   out_830203783768276833[290] = 0;
   out_830203783768276833[291] = 0;
   out_830203783768276833[292] = 0;
   out_830203783768276833[293] = 0;
   out_830203783768276833[294] = 0;
   out_830203783768276833[295] = 0;
   out_830203783768276833[296] = 0;
   out_830203783768276833[297] = 0;
   out_830203783768276833[298] = 0;
   out_830203783768276833[299] = 0;
   out_830203783768276833[300] = 0;
   out_830203783768276833[301] = 0;
   out_830203783768276833[302] = 0;
   out_830203783768276833[303] = 0;
   out_830203783768276833[304] = 1;
   out_830203783768276833[305] = 0;
   out_830203783768276833[306] = 0;
   out_830203783768276833[307] = 0;
   out_830203783768276833[308] = 0;
   out_830203783768276833[309] = 0;
   out_830203783768276833[310] = 0;
   out_830203783768276833[311] = 0;
   out_830203783768276833[312] = 0;
   out_830203783768276833[313] = 0;
   out_830203783768276833[314] = 0;
   out_830203783768276833[315] = 0;
   out_830203783768276833[316] = 0;
   out_830203783768276833[317] = 0;
   out_830203783768276833[318] = 0;
   out_830203783768276833[319] = 0;
   out_830203783768276833[320] = 0;
   out_830203783768276833[321] = 0;
   out_830203783768276833[322] = 0;
   out_830203783768276833[323] = 1;
}
void h_4(double *state, double *unused, double *out_1652667498977980545) {
   out_1652667498977980545[0] = state[6] + state[9];
   out_1652667498977980545[1] = state[7] + state[10];
   out_1652667498977980545[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2065332728427663759) {
   out_2065332728427663759[0] = 0;
   out_2065332728427663759[1] = 0;
   out_2065332728427663759[2] = 0;
   out_2065332728427663759[3] = 0;
   out_2065332728427663759[4] = 0;
   out_2065332728427663759[5] = 0;
   out_2065332728427663759[6] = 1;
   out_2065332728427663759[7] = 0;
   out_2065332728427663759[8] = 0;
   out_2065332728427663759[9] = 1;
   out_2065332728427663759[10] = 0;
   out_2065332728427663759[11] = 0;
   out_2065332728427663759[12] = 0;
   out_2065332728427663759[13] = 0;
   out_2065332728427663759[14] = 0;
   out_2065332728427663759[15] = 0;
   out_2065332728427663759[16] = 0;
   out_2065332728427663759[17] = 0;
   out_2065332728427663759[18] = 0;
   out_2065332728427663759[19] = 0;
   out_2065332728427663759[20] = 0;
   out_2065332728427663759[21] = 0;
   out_2065332728427663759[22] = 0;
   out_2065332728427663759[23] = 0;
   out_2065332728427663759[24] = 0;
   out_2065332728427663759[25] = 1;
   out_2065332728427663759[26] = 0;
   out_2065332728427663759[27] = 0;
   out_2065332728427663759[28] = 1;
   out_2065332728427663759[29] = 0;
   out_2065332728427663759[30] = 0;
   out_2065332728427663759[31] = 0;
   out_2065332728427663759[32] = 0;
   out_2065332728427663759[33] = 0;
   out_2065332728427663759[34] = 0;
   out_2065332728427663759[35] = 0;
   out_2065332728427663759[36] = 0;
   out_2065332728427663759[37] = 0;
   out_2065332728427663759[38] = 0;
   out_2065332728427663759[39] = 0;
   out_2065332728427663759[40] = 0;
   out_2065332728427663759[41] = 0;
   out_2065332728427663759[42] = 0;
   out_2065332728427663759[43] = 0;
   out_2065332728427663759[44] = 1;
   out_2065332728427663759[45] = 0;
   out_2065332728427663759[46] = 0;
   out_2065332728427663759[47] = 1;
   out_2065332728427663759[48] = 0;
   out_2065332728427663759[49] = 0;
   out_2065332728427663759[50] = 0;
   out_2065332728427663759[51] = 0;
   out_2065332728427663759[52] = 0;
   out_2065332728427663759[53] = 0;
}
void h_10(double *state, double *unused, double *out_8803253396773735652) {
   out_8803253396773735652[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8803253396773735652[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8803253396773735652[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1768777245936477788) {
   out_1768777245936477788[0] = 0;
   out_1768777245936477788[1] = 9.8100000000000005*cos(state[1]);
   out_1768777245936477788[2] = 0;
   out_1768777245936477788[3] = 0;
   out_1768777245936477788[4] = -state[8];
   out_1768777245936477788[5] = state[7];
   out_1768777245936477788[6] = 0;
   out_1768777245936477788[7] = state[5];
   out_1768777245936477788[8] = -state[4];
   out_1768777245936477788[9] = 0;
   out_1768777245936477788[10] = 0;
   out_1768777245936477788[11] = 0;
   out_1768777245936477788[12] = 1;
   out_1768777245936477788[13] = 0;
   out_1768777245936477788[14] = 0;
   out_1768777245936477788[15] = 1;
   out_1768777245936477788[16] = 0;
   out_1768777245936477788[17] = 0;
   out_1768777245936477788[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1768777245936477788[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1768777245936477788[20] = 0;
   out_1768777245936477788[21] = state[8];
   out_1768777245936477788[22] = 0;
   out_1768777245936477788[23] = -state[6];
   out_1768777245936477788[24] = -state[5];
   out_1768777245936477788[25] = 0;
   out_1768777245936477788[26] = state[3];
   out_1768777245936477788[27] = 0;
   out_1768777245936477788[28] = 0;
   out_1768777245936477788[29] = 0;
   out_1768777245936477788[30] = 0;
   out_1768777245936477788[31] = 1;
   out_1768777245936477788[32] = 0;
   out_1768777245936477788[33] = 0;
   out_1768777245936477788[34] = 1;
   out_1768777245936477788[35] = 0;
   out_1768777245936477788[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1768777245936477788[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1768777245936477788[38] = 0;
   out_1768777245936477788[39] = -state[7];
   out_1768777245936477788[40] = state[6];
   out_1768777245936477788[41] = 0;
   out_1768777245936477788[42] = state[4];
   out_1768777245936477788[43] = -state[3];
   out_1768777245936477788[44] = 0;
   out_1768777245936477788[45] = 0;
   out_1768777245936477788[46] = 0;
   out_1768777245936477788[47] = 0;
   out_1768777245936477788[48] = 0;
   out_1768777245936477788[49] = 0;
   out_1768777245936477788[50] = 1;
   out_1768777245936477788[51] = 0;
   out_1768777245936477788[52] = 0;
   out_1768777245936477788[53] = 1;
}
void h_13(double *state, double *unused, double *out_5388839778110327076) {
   out_5388839778110327076[0] = state[3];
   out_5388839778110327076[1] = state[4];
   out_5388839778110327076[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1146941096904669042) {
   out_1146941096904669042[0] = 0;
   out_1146941096904669042[1] = 0;
   out_1146941096904669042[2] = 0;
   out_1146941096904669042[3] = 1;
   out_1146941096904669042[4] = 0;
   out_1146941096904669042[5] = 0;
   out_1146941096904669042[6] = 0;
   out_1146941096904669042[7] = 0;
   out_1146941096904669042[8] = 0;
   out_1146941096904669042[9] = 0;
   out_1146941096904669042[10] = 0;
   out_1146941096904669042[11] = 0;
   out_1146941096904669042[12] = 0;
   out_1146941096904669042[13] = 0;
   out_1146941096904669042[14] = 0;
   out_1146941096904669042[15] = 0;
   out_1146941096904669042[16] = 0;
   out_1146941096904669042[17] = 0;
   out_1146941096904669042[18] = 0;
   out_1146941096904669042[19] = 0;
   out_1146941096904669042[20] = 0;
   out_1146941096904669042[21] = 0;
   out_1146941096904669042[22] = 1;
   out_1146941096904669042[23] = 0;
   out_1146941096904669042[24] = 0;
   out_1146941096904669042[25] = 0;
   out_1146941096904669042[26] = 0;
   out_1146941096904669042[27] = 0;
   out_1146941096904669042[28] = 0;
   out_1146941096904669042[29] = 0;
   out_1146941096904669042[30] = 0;
   out_1146941096904669042[31] = 0;
   out_1146941096904669042[32] = 0;
   out_1146941096904669042[33] = 0;
   out_1146941096904669042[34] = 0;
   out_1146941096904669042[35] = 0;
   out_1146941096904669042[36] = 0;
   out_1146941096904669042[37] = 0;
   out_1146941096904669042[38] = 0;
   out_1146941096904669042[39] = 0;
   out_1146941096904669042[40] = 0;
   out_1146941096904669042[41] = 1;
   out_1146941096904669042[42] = 0;
   out_1146941096904669042[43] = 0;
   out_1146941096904669042[44] = 0;
   out_1146941096904669042[45] = 0;
   out_1146941096904669042[46] = 0;
   out_1146941096904669042[47] = 0;
   out_1146941096904669042[48] = 0;
   out_1146941096904669042[49] = 0;
   out_1146941096904669042[50] = 0;
   out_1146941096904669042[51] = 0;
   out_1146941096904669042[52] = 0;
   out_1146941096904669042[53] = 0;
}
void h_14(double *state, double *unused, double *out_653899258242143155) {
   out_653899258242143155[0] = state[6];
   out_653899258242143155[1] = state[7];
   out_653899258242143155[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1897908127911820770) {
   out_1897908127911820770[0] = 0;
   out_1897908127911820770[1] = 0;
   out_1897908127911820770[2] = 0;
   out_1897908127911820770[3] = 0;
   out_1897908127911820770[4] = 0;
   out_1897908127911820770[5] = 0;
   out_1897908127911820770[6] = 1;
   out_1897908127911820770[7] = 0;
   out_1897908127911820770[8] = 0;
   out_1897908127911820770[9] = 0;
   out_1897908127911820770[10] = 0;
   out_1897908127911820770[11] = 0;
   out_1897908127911820770[12] = 0;
   out_1897908127911820770[13] = 0;
   out_1897908127911820770[14] = 0;
   out_1897908127911820770[15] = 0;
   out_1897908127911820770[16] = 0;
   out_1897908127911820770[17] = 0;
   out_1897908127911820770[18] = 0;
   out_1897908127911820770[19] = 0;
   out_1897908127911820770[20] = 0;
   out_1897908127911820770[21] = 0;
   out_1897908127911820770[22] = 0;
   out_1897908127911820770[23] = 0;
   out_1897908127911820770[24] = 0;
   out_1897908127911820770[25] = 1;
   out_1897908127911820770[26] = 0;
   out_1897908127911820770[27] = 0;
   out_1897908127911820770[28] = 0;
   out_1897908127911820770[29] = 0;
   out_1897908127911820770[30] = 0;
   out_1897908127911820770[31] = 0;
   out_1897908127911820770[32] = 0;
   out_1897908127911820770[33] = 0;
   out_1897908127911820770[34] = 0;
   out_1897908127911820770[35] = 0;
   out_1897908127911820770[36] = 0;
   out_1897908127911820770[37] = 0;
   out_1897908127911820770[38] = 0;
   out_1897908127911820770[39] = 0;
   out_1897908127911820770[40] = 0;
   out_1897908127911820770[41] = 0;
   out_1897908127911820770[42] = 0;
   out_1897908127911820770[43] = 0;
   out_1897908127911820770[44] = 1;
   out_1897908127911820770[45] = 0;
   out_1897908127911820770[46] = 0;
   out_1897908127911820770[47] = 0;
   out_1897908127911820770[48] = 0;
   out_1897908127911820770[49] = 0;
   out_1897908127911820770[50] = 0;
   out_1897908127911820770[51] = 0;
   out_1897908127911820770[52] = 0;
   out_1897908127911820770[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5813097801788606117) {
  err_fun(nom_x, delta_x, out_5813097801788606117);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_265932847343752274) {
  inv_err_fun(nom_x, true_x, out_265932847343752274);
}
void pose_H_mod_fun(double *state, double *out_3782749078324294962) {
  H_mod_fun(state, out_3782749078324294962);
}
void pose_f_fun(double *state, double dt, double *out_2316687695349101514) {
  f_fun(state,  dt, out_2316687695349101514);
}
void pose_F_fun(double *state, double dt, double *out_830203783768276833) {
  F_fun(state,  dt, out_830203783768276833);
}
void pose_h_4(double *state, double *unused, double *out_1652667498977980545) {
  h_4(state, unused, out_1652667498977980545);
}
void pose_H_4(double *state, double *unused, double *out_2065332728427663759) {
  H_4(state, unused, out_2065332728427663759);
}
void pose_h_10(double *state, double *unused, double *out_8803253396773735652) {
  h_10(state, unused, out_8803253396773735652);
}
void pose_H_10(double *state, double *unused, double *out_1768777245936477788) {
  H_10(state, unused, out_1768777245936477788);
}
void pose_h_13(double *state, double *unused, double *out_5388839778110327076) {
  h_13(state, unused, out_5388839778110327076);
}
void pose_H_13(double *state, double *unused, double *out_1146941096904669042) {
  H_13(state, unused, out_1146941096904669042);
}
void pose_h_14(double *state, double *unused, double *out_653899258242143155) {
  h_14(state, unused, out_653899258242143155);
}
void pose_H_14(double *state, double *unused, double *out_1897908127911820770) {
  H_14(state, unused, out_1897908127911820770);
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
