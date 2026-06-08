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
void err_fun(double *nom_x, double *delta_x, double *out_6891956137394554809) {
   out_6891956137394554809[0] = delta_x[0] + nom_x[0];
   out_6891956137394554809[1] = delta_x[1] + nom_x[1];
   out_6891956137394554809[2] = delta_x[2] + nom_x[2];
   out_6891956137394554809[3] = delta_x[3] + nom_x[3];
   out_6891956137394554809[4] = delta_x[4] + nom_x[4];
   out_6891956137394554809[5] = delta_x[5] + nom_x[5];
   out_6891956137394554809[6] = delta_x[6] + nom_x[6];
   out_6891956137394554809[7] = delta_x[7] + nom_x[7];
   out_6891956137394554809[8] = delta_x[8] + nom_x[8];
   out_6891956137394554809[9] = delta_x[9] + nom_x[9];
   out_6891956137394554809[10] = delta_x[10] + nom_x[10];
   out_6891956137394554809[11] = delta_x[11] + nom_x[11];
   out_6891956137394554809[12] = delta_x[12] + nom_x[12];
   out_6891956137394554809[13] = delta_x[13] + nom_x[13];
   out_6891956137394554809[14] = delta_x[14] + nom_x[14];
   out_6891956137394554809[15] = delta_x[15] + nom_x[15];
   out_6891956137394554809[16] = delta_x[16] + nom_x[16];
   out_6891956137394554809[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_352074767866048570) {
   out_352074767866048570[0] = -nom_x[0] + true_x[0];
   out_352074767866048570[1] = -nom_x[1] + true_x[1];
   out_352074767866048570[2] = -nom_x[2] + true_x[2];
   out_352074767866048570[3] = -nom_x[3] + true_x[3];
   out_352074767866048570[4] = -nom_x[4] + true_x[4];
   out_352074767866048570[5] = -nom_x[5] + true_x[5];
   out_352074767866048570[6] = -nom_x[6] + true_x[6];
   out_352074767866048570[7] = -nom_x[7] + true_x[7];
   out_352074767866048570[8] = -nom_x[8] + true_x[8];
   out_352074767866048570[9] = -nom_x[9] + true_x[9];
   out_352074767866048570[10] = -nom_x[10] + true_x[10];
   out_352074767866048570[11] = -nom_x[11] + true_x[11];
   out_352074767866048570[12] = -nom_x[12] + true_x[12];
   out_352074767866048570[13] = -nom_x[13] + true_x[13];
   out_352074767866048570[14] = -nom_x[14] + true_x[14];
   out_352074767866048570[15] = -nom_x[15] + true_x[15];
   out_352074767866048570[16] = -nom_x[16] + true_x[16];
   out_352074767866048570[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_57344037476075931) {
   out_57344037476075931[0] = 1.0;
   out_57344037476075931[1] = 0.0;
   out_57344037476075931[2] = 0.0;
   out_57344037476075931[3] = 0.0;
   out_57344037476075931[4] = 0.0;
   out_57344037476075931[5] = 0.0;
   out_57344037476075931[6] = 0.0;
   out_57344037476075931[7] = 0.0;
   out_57344037476075931[8] = 0.0;
   out_57344037476075931[9] = 0.0;
   out_57344037476075931[10] = 0.0;
   out_57344037476075931[11] = 0.0;
   out_57344037476075931[12] = 0.0;
   out_57344037476075931[13] = 0.0;
   out_57344037476075931[14] = 0.0;
   out_57344037476075931[15] = 0.0;
   out_57344037476075931[16] = 0.0;
   out_57344037476075931[17] = 0.0;
   out_57344037476075931[18] = 0.0;
   out_57344037476075931[19] = 1.0;
   out_57344037476075931[20] = 0.0;
   out_57344037476075931[21] = 0.0;
   out_57344037476075931[22] = 0.0;
   out_57344037476075931[23] = 0.0;
   out_57344037476075931[24] = 0.0;
   out_57344037476075931[25] = 0.0;
   out_57344037476075931[26] = 0.0;
   out_57344037476075931[27] = 0.0;
   out_57344037476075931[28] = 0.0;
   out_57344037476075931[29] = 0.0;
   out_57344037476075931[30] = 0.0;
   out_57344037476075931[31] = 0.0;
   out_57344037476075931[32] = 0.0;
   out_57344037476075931[33] = 0.0;
   out_57344037476075931[34] = 0.0;
   out_57344037476075931[35] = 0.0;
   out_57344037476075931[36] = 0.0;
   out_57344037476075931[37] = 0.0;
   out_57344037476075931[38] = 1.0;
   out_57344037476075931[39] = 0.0;
   out_57344037476075931[40] = 0.0;
   out_57344037476075931[41] = 0.0;
   out_57344037476075931[42] = 0.0;
   out_57344037476075931[43] = 0.0;
   out_57344037476075931[44] = 0.0;
   out_57344037476075931[45] = 0.0;
   out_57344037476075931[46] = 0.0;
   out_57344037476075931[47] = 0.0;
   out_57344037476075931[48] = 0.0;
   out_57344037476075931[49] = 0.0;
   out_57344037476075931[50] = 0.0;
   out_57344037476075931[51] = 0.0;
   out_57344037476075931[52] = 0.0;
   out_57344037476075931[53] = 0.0;
   out_57344037476075931[54] = 0.0;
   out_57344037476075931[55] = 0.0;
   out_57344037476075931[56] = 0.0;
   out_57344037476075931[57] = 1.0;
   out_57344037476075931[58] = 0.0;
   out_57344037476075931[59] = 0.0;
   out_57344037476075931[60] = 0.0;
   out_57344037476075931[61] = 0.0;
   out_57344037476075931[62] = 0.0;
   out_57344037476075931[63] = 0.0;
   out_57344037476075931[64] = 0.0;
   out_57344037476075931[65] = 0.0;
   out_57344037476075931[66] = 0.0;
   out_57344037476075931[67] = 0.0;
   out_57344037476075931[68] = 0.0;
   out_57344037476075931[69] = 0.0;
   out_57344037476075931[70] = 0.0;
   out_57344037476075931[71] = 0.0;
   out_57344037476075931[72] = 0.0;
   out_57344037476075931[73] = 0.0;
   out_57344037476075931[74] = 0.0;
   out_57344037476075931[75] = 0.0;
   out_57344037476075931[76] = 1.0;
   out_57344037476075931[77] = 0.0;
   out_57344037476075931[78] = 0.0;
   out_57344037476075931[79] = 0.0;
   out_57344037476075931[80] = 0.0;
   out_57344037476075931[81] = 0.0;
   out_57344037476075931[82] = 0.0;
   out_57344037476075931[83] = 0.0;
   out_57344037476075931[84] = 0.0;
   out_57344037476075931[85] = 0.0;
   out_57344037476075931[86] = 0.0;
   out_57344037476075931[87] = 0.0;
   out_57344037476075931[88] = 0.0;
   out_57344037476075931[89] = 0.0;
   out_57344037476075931[90] = 0.0;
   out_57344037476075931[91] = 0.0;
   out_57344037476075931[92] = 0.0;
   out_57344037476075931[93] = 0.0;
   out_57344037476075931[94] = 0.0;
   out_57344037476075931[95] = 1.0;
   out_57344037476075931[96] = 0.0;
   out_57344037476075931[97] = 0.0;
   out_57344037476075931[98] = 0.0;
   out_57344037476075931[99] = 0.0;
   out_57344037476075931[100] = 0.0;
   out_57344037476075931[101] = 0.0;
   out_57344037476075931[102] = 0.0;
   out_57344037476075931[103] = 0.0;
   out_57344037476075931[104] = 0.0;
   out_57344037476075931[105] = 0.0;
   out_57344037476075931[106] = 0.0;
   out_57344037476075931[107] = 0.0;
   out_57344037476075931[108] = 0.0;
   out_57344037476075931[109] = 0.0;
   out_57344037476075931[110] = 0.0;
   out_57344037476075931[111] = 0.0;
   out_57344037476075931[112] = 0.0;
   out_57344037476075931[113] = 0.0;
   out_57344037476075931[114] = 1.0;
   out_57344037476075931[115] = 0.0;
   out_57344037476075931[116] = 0.0;
   out_57344037476075931[117] = 0.0;
   out_57344037476075931[118] = 0.0;
   out_57344037476075931[119] = 0.0;
   out_57344037476075931[120] = 0.0;
   out_57344037476075931[121] = 0.0;
   out_57344037476075931[122] = 0.0;
   out_57344037476075931[123] = 0.0;
   out_57344037476075931[124] = 0.0;
   out_57344037476075931[125] = 0.0;
   out_57344037476075931[126] = 0.0;
   out_57344037476075931[127] = 0.0;
   out_57344037476075931[128] = 0.0;
   out_57344037476075931[129] = 0.0;
   out_57344037476075931[130] = 0.0;
   out_57344037476075931[131] = 0.0;
   out_57344037476075931[132] = 0.0;
   out_57344037476075931[133] = 1.0;
   out_57344037476075931[134] = 0.0;
   out_57344037476075931[135] = 0.0;
   out_57344037476075931[136] = 0.0;
   out_57344037476075931[137] = 0.0;
   out_57344037476075931[138] = 0.0;
   out_57344037476075931[139] = 0.0;
   out_57344037476075931[140] = 0.0;
   out_57344037476075931[141] = 0.0;
   out_57344037476075931[142] = 0.0;
   out_57344037476075931[143] = 0.0;
   out_57344037476075931[144] = 0.0;
   out_57344037476075931[145] = 0.0;
   out_57344037476075931[146] = 0.0;
   out_57344037476075931[147] = 0.0;
   out_57344037476075931[148] = 0.0;
   out_57344037476075931[149] = 0.0;
   out_57344037476075931[150] = 0.0;
   out_57344037476075931[151] = 0.0;
   out_57344037476075931[152] = 1.0;
   out_57344037476075931[153] = 0.0;
   out_57344037476075931[154] = 0.0;
   out_57344037476075931[155] = 0.0;
   out_57344037476075931[156] = 0.0;
   out_57344037476075931[157] = 0.0;
   out_57344037476075931[158] = 0.0;
   out_57344037476075931[159] = 0.0;
   out_57344037476075931[160] = 0.0;
   out_57344037476075931[161] = 0.0;
   out_57344037476075931[162] = 0.0;
   out_57344037476075931[163] = 0.0;
   out_57344037476075931[164] = 0.0;
   out_57344037476075931[165] = 0.0;
   out_57344037476075931[166] = 0.0;
   out_57344037476075931[167] = 0.0;
   out_57344037476075931[168] = 0.0;
   out_57344037476075931[169] = 0.0;
   out_57344037476075931[170] = 0.0;
   out_57344037476075931[171] = 1.0;
   out_57344037476075931[172] = 0.0;
   out_57344037476075931[173] = 0.0;
   out_57344037476075931[174] = 0.0;
   out_57344037476075931[175] = 0.0;
   out_57344037476075931[176] = 0.0;
   out_57344037476075931[177] = 0.0;
   out_57344037476075931[178] = 0.0;
   out_57344037476075931[179] = 0.0;
   out_57344037476075931[180] = 0.0;
   out_57344037476075931[181] = 0.0;
   out_57344037476075931[182] = 0.0;
   out_57344037476075931[183] = 0.0;
   out_57344037476075931[184] = 0.0;
   out_57344037476075931[185] = 0.0;
   out_57344037476075931[186] = 0.0;
   out_57344037476075931[187] = 0.0;
   out_57344037476075931[188] = 0.0;
   out_57344037476075931[189] = 0.0;
   out_57344037476075931[190] = 1.0;
   out_57344037476075931[191] = 0.0;
   out_57344037476075931[192] = 0.0;
   out_57344037476075931[193] = 0.0;
   out_57344037476075931[194] = 0.0;
   out_57344037476075931[195] = 0.0;
   out_57344037476075931[196] = 0.0;
   out_57344037476075931[197] = 0.0;
   out_57344037476075931[198] = 0.0;
   out_57344037476075931[199] = 0.0;
   out_57344037476075931[200] = 0.0;
   out_57344037476075931[201] = 0.0;
   out_57344037476075931[202] = 0.0;
   out_57344037476075931[203] = 0.0;
   out_57344037476075931[204] = 0.0;
   out_57344037476075931[205] = 0.0;
   out_57344037476075931[206] = 0.0;
   out_57344037476075931[207] = 0.0;
   out_57344037476075931[208] = 0.0;
   out_57344037476075931[209] = 1.0;
   out_57344037476075931[210] = 0.0;
   out_57344037476075931[211] = 0.0;
   out_57344037476075931[212] = 0.0;
   out_57344037476075931[213] = 0.0;
   out_57344037476075931[214] = 0.0;
   out_57344037476075931[215] = 0.0;
   out_57344037476075931[216] = 0.0;
   out_57344037476075931[217] = 0.0;
   out_57344037476075931[218] = 0.0;
   out_57344037476075931[219] = 0.0;
   out_57344037476075931[220] = 0.0;
   out_57344037476075931[221] = 0.0;
   out_57344037476075931[222] = 0.0;
   out_57344037476075931[223] = 0.0;
   out_57344037476075931[224] = 0.0;
   out_57344037476075931[225] = 0.0;
   out_57344037476075931[226] = 0.0;
   out_57344037476075931[227] = 0.0;
   out_57344037476075931[228] = 1.0;
   out_57344037476075931[229] = 0.0;
   out_57344037476075931[230] = 0.0;
   out_57344037476075931[231] = 0.0;
   out_57344037476075931[232] = 0.0;
   out_57344037476075931[233] = 0.0;
   out_57344037476075931[234] = 0.0;
   out_57344037476075931[235] = 0.0;
   out_57344037476075931[236] = 0.0;
   out_57344037476075931[237] = 0.0;
   out_57344037476075931[238] = 0.0;
   out_57344037476075931[239] = 0.0;
   out_57344037476075931[240] = 0.0;
   out_57344037476075931[241] = 0.0;
   out_57344037476075931[242] = 0.0;
   out_57344037476075931[243] = 0.0;
   out_57344037476075931[244] = 0.0;
   out_57344037476075931[245] = 0.0;
   out_57344037476075931[246] = 0.0;
   out_57344037476075931[247] = 1.0;
   out_57344037476075931[248] = 0.0;
   out_57344037476075931[249] = 0.0;
   out_57344037476075931[250] = 0.0;
   out_57344037476075931[251] = 0.0;
   out_57344037476075931[252] = 0.0;
   out_57344037476075931[253] = 0.0;
   out_57344037476075931[254] = 0.0;
   out_57344037476075931[255] = 0.0;
   out_57344037476075931[256] = 0.0;
   out_57344037476075931[257] = 0.0;
   out_57344037476075931[258] = 0.0;
   out_57344037476075931[259] = 0.0;
   out_57344037476075931[260] = 0.0;
   out_57344037476075931[261] = 0.0;
   out_57344037476075931[262] = 0.0;
   out_57344037476075931[263] = 0.0;
   out_57344037476075931[264] = 0.0;
   out_57344037476075931[265] = 0.0;
   out_57344037476075931[266] = 1.0;
   out_57344037476075931[267] = 0.0;
   out_57344037476075931[268] = 0.0;
   out_57344037476075931[269] = 0.0;
   out_57344037476075931[270] = 0.0;
   out_57344037476075931[271] = 0.0;
   out_57344037476075931[272] = 0.0;
   out_57344037476075931[273] = 0.0;
   out_57344037476075931[274] = 0.0;
   out_57344037476075931[275] = 0.0;
   out_57344037476075931[276] = 0.0;
   out_57344037476075931[277] = 0.0;
   out_57344037476075931[278] = 0.0;
   out_57344037476075931[279] = 0.0;
   out_57344037476075931[280] = 0.0;
   out_57344037476075931[281] = 0.0;
   out_57344037476075931[282] = 0.0;
   out_57344037476075931[283] = 0.0;
   out_57344037476075931[284] = 0.0;
   out_57344037476075931[285] = 1.0;
   out_57344037476075931[286] = 0.0;
   out_57344037476075931[287] = 0.0;
   out_57344037476075931[288] = 0.0;
   out_57344037476075931[289] = 0.0;
   out_57344037476075931[290] = 0.0;
   out_57344037476075931[291] = 0.0;
   out_57344037476075931[292] = 0.0;
   out_57344037476075931[293] = 0.0;
   out_57344037476075931[294] = 0.0;
   out_57344037476075931[295] = 0.0;
   out_57344037476075931[296] = 0.0;
   out_57344037476075931[297] = 0.0;
   out_57344037476075931[298] = 0.0;
   out_57344037476075931[299] = 0.0;
   out_57344037476075931[300] = 0.0;
   out_57344037476075931[301] = 0.0;
   out_57344037476075931[302] = 0.0;
   out_57344037476075931[303] = 0.0;
   out_57344037476075931[304] = 1.0;
   out_57344037476075931[305] = 0.0;
   out_57344037476075931[306] = 0.0;
   out_57344037476075931[307] = 0.0;
   out_57344037476075931[308] = 0.0;
   out_57344037476075931[309] = 0.0;
   out_57344037476075931[310] = 0.0;
   out_57344037476075931[311] = 0.0;
   out_57344037476075931[312] = 0.0;
   out_57344037476075931[313] = 0.0;
   out_57344037476075931[314] = 0.0;
   out_57344037476075931[315] = 0.0;
   out_57344037476075931[316] = 0.0;
   out_57344037476075931[317] = 0.0;
   out_57344037476075931[318] = 0.0;
   out_57344037476075931[319] = 0.0;
   out_57344037476075931[320] = 0.0;
   out_57344037476075931[321] = 0.0;
   out_57344037476075931[322] = 0.0;
   out_57344037476075931[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8328845329683204295) {
   out_8328845329683204295[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8328845329683204295[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8328845329683204295[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8328845329683204295[3] = dt*state[12] + state[3];
   out_8328845329683204295[4] = dt*state[13] + state[4];
   out_8328845329683204295[5] = dt*state[14] + state[5];
   out_8328845329683204295[6] = state[6];
   out_8328845329683204295[7] = state[7];
   out_8328845329683204295[8] = state[8];
   out_8328845329683204295[9] = state[9];
   out_8328845329683204295[10] = state[10];
   out_8328845329683204295[11] = state[11];
   out_8328845329683204295[12] = state[12];
   out_8328845329683204295[13] = state[13];
   out_8328845329683204295[14] = state[14];
   out_8328845329683204295[15] = state[15];
   out_8328845329683204295[16] = state[16];
   out_8328845329683204295[17] = state[17];
}
void F_fun(double *state, double dt, double *out_6465495001911852221) {
   out_6465495001911852221[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6465495001911852221[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6465495001911852221[2] = 0;
   out_6465495001911852221[3] = 0;
   out_6465495001911852221[4] = 0;
   out_6465495001911852221[5] = 0;
   out_6465495001911852221[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6465495001911852221[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6465495001911852221[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6465495001911852221[9] = 0;
   out_6465495001911852221[10] = 0;
   out_6465495001911852221[11] = 0;
   out_6465495001911852221[12] = 0;
   out_6465495001911852221[13] = 0;
   out_6465495001911852221[14] = 0;
   out_6465495001911852221[15] = 0;
   out_6465495001911852221[16] = 0;
   out_6465495001911852221[17] = 0;
   out_6465495001911852221[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6465495001911852221[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6465495001911852221[20] = 0;
   out_6465495001911852221[21] = 0;
   out_6465495001911852221[22] = 0;
   out_6465495001911852221[23] = 0;
   out_6465495001911852221[24] = 0;
   out_6465495001911852221[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6465495001911852221[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6465495001911852221[27] = 0;
   out_6465495001911852221[28] = 0;
   out_6465495001911852221[29] = 0;
   out_6465495001911852221[30] = 0;
   out_6465495001911852221[31] = 0;
   out_6465495001911852221[32] = 0;
   out_6465495001911852221[33] = 0;
   out_6465495001911852221[34] = 0;
   out_6465495001911852221[35] = 0;
   out_6465495001911852221[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6465495001911852221[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6465495001911852221[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6465495001911852221[39] = 0;
   out_6465495001911852221[40] = 0;
   out_6465495001911852221[41] = 0;
   out_6465495001911852221[42] = 0;
   out_6465495001911852221[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6465495001911852221[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6465495001911852221[45] = 0;
   out_6465495001911852221[46] = 0;
   out_6465495001911852221[47] = 0;
   out_6465495001911852221[48] = 0;
   out_6465495001911852221[49] = 0;
   out_6465495001911852221[50] = 0;
   out_6465495001911852221[51] = 0;
   out_6465495001911852221[52] = 0;
   out_6465495001911852221[53] = 0;
   out_6465495001911852221[54] = 0;
   out_6465495001911852221[55] = 0;
   out_6465495001911852221[56] = 0;
   out_6465495001911852221[57] = 1;
   out_6465495001911852221[58] = 0;
   out_6465495001911852221[59] = 0;
   out_6465495001911852221[60] = 0;
   out_6465495001911852221[61] = 0;
   out_6465495001911852221[62] = 0;
   out_6465495001911852221[63] = 0;
   out_6465495001911852221[64] = 0;
   out_6465495001911852221[65] = 0;
   out_6465495001911852221[66] = dt;
   out_6465495001911852221[67] = 0;
   out_6465495001911852221[68] = 0;
   out_6465495001911852221[69] = 0;
   out_6465495001911852221[70] = 0;
   out_6465495001911852221[71] = 0;
   out_6465495001911852221[72] = 0;
   out_6465495001911852221[73] = 0;
   out_6465495001911852221[74] = 0;
   out_6465495001911852221[75] = 0;
   out_6465495001911852221[76] = 1;
   out_6465495001911852221[77] = 0;
   out_6465495001911852221[78] = 0;
   out_6465495001911852221[79] = 0;
   out_6465495001911852221[80] = 0;
   out_6465495001911852221[81] = 0;
   out_6465495001911852221[82] = 0;
   out_6465495001911852221[83] = 0;
   out_6465495001911852221[84] = 0;
   out_6465495001911852221[85] = dt;
   out_6465495001911852221[86] = 0;
   out_6465495001911852221[87] = 0;
   out_6465495001911852221[88] = 0;
   out_6465495001911852221[89] = 0;
   out_6465495001911852221[90] = 0;
   out_6465495001911852221[91] = 0;
   out_6465495001911852221[92] = 0;
   out_6465495001911852221[93] = 0;
   out_6465495001911852221[94] = 0;
   out_6465495001911852221[95] = 1;
   out_6465495001911852221[96] = 0;
   out_6465495001911852221[97] = 0;
   out_6465495001911852221[98] = 0;
   out_6465495001911852221[99] = 0;
   out_6465495001911852221[100] = 0;
   out_6465495001911852221[101] = 0;
   out_6465495001911852221[102] = 0;
   out_6465495001911852221[103] = 0;
   out_6465495001911852221[104] = dt;
   out_6465495001911852221[105] = 0;
   out_6465495001911852221[106] = 0;
   out_6465495001911852221[107] = 0;
   out_6465495001911852221[108] = 0;
   out_6465495001911852221[109] = 0;
   out_6465495001911852221[110] = 0;
   out_6465495001911852221[111] = 0;
   out_6465495001911852221[112] = 0;
   out_6465495001911852221[113] = 0;
   out_6465495001911852221[114] = 1;
   out_6465495001911852221[115] = 0;
   out_6465495001911852221[116] = 0;
   out_6465495001911852221[117] = 0;
   out_6465495001911852221[118] = 0;
   out_6465495001911852221[119] = 0;
   out_6465495001911852221[120] = 0;
   out_6465495001911852221[121] = 0;
   out_6465495001911852221[122] = 0;
   out_6465495001911852221[123] = 0;
   out_6465495001911852221[124] = 0;
   out_6465495001911852221[125] = 0;
   out_6465495001911852221[126] = 0;
   out_6465495001911852221[127] = 0;
   out_6465495001911852221[128] = 0;
   out_6465495001911852221[129] = 0;
   out_6465495001911852221[130] = 0;
   out_6465495001911852221[131] = 0;
   out_6465495001911852221[132] = 0;
   out_6465495001911852221[133] = 1;
   out_6465495001911852221[134] = 0;
   out_6465495001911852221[135] = 0;
   out_6465495001911852221[136] = 0;
   out_6465495001911852221[137] = 0;
   out_6465495001911852221[138] = 0;
   out_6465495001911852221[139] = 0;
   out_6465495001911852221[140] = 0;
   out_6465495001911852221[141] = 0;
   out_6465495001911852221[142] = 0;
   out_6465495001911852221[143] = 0;
   out_6465495001911852221[144] = 0;
   out_6465495001911852221[145] = 0;
   out_6465495001911852221[146] = 0;
   out_6465495001911852221[147] = 0;
   out_6465495001911852221[148] = 0;
   out_6465495001911852221[149] = 0;
   out_6465495001911852221[150] = 0;
   out_6465495001911852221[151] = 0;
   out_6465495001911852221[152] = 1;
   out_6465495001911852221[153] = 0;
   out_6465495001911852221[154] = 0;
   out_6465495001911852221[155] = 0;
   out_6465495001911852221[156] = 0;
   out_6465495001911852221[157] = 0;
   out_6465495001911852221[158] = 0;
   out_6465495001911852221[159] = 0;
   out_6465495001911852221[160] = 0;
   out_6465495001911852221[161] = 0;
   out_6465495001911852221[162] = 0;
   out_6465495001911852221[163] = 0;
   out_6465495001911852221[164] = 0;
   out_6465495001911852221[165] = 0;
   out_6465495001911852221[166] = 0;
   out_6465495001911852221[167] = 0;
   out_6465495001911852221[168] = 0;
   out_6465495001911852221[169] = 0;
   out_6465495001911852221[170] = 0;
   out_6465495001911852221[171] = 1;
   out_6465495001911852221[172] = 0;
   out_6465495001911852221[173] = 0;
   out_6465495001911852221[174] = 0;
   out_6465495001911852221[175] = 0;
   out_6465495001911852221[176] = 0;
   out_6465495001911852221[177] = 0;
   out_6465495001911852221[178] = 0;
   out_6465495001911852221[179] = 0;
   out_6465495001911852221[180] = 0;
   out_6465495001911852221[181] = 0;
   out_6465495001911852221[182] = 0;
   out_6465495001911852221[183] = 0;
   out_6465495001911852221[184] = 0;
   out_6465495001911852221[185] = 0;
   out_6465495001911852221[186] = 0;
   out_6465495001911852221[187] = 0;
   out_6465495001911852221[188] = 0;
   out_6465495001911852221[189] = 0;
   out_6465495001911852221[190] = 1;
   out_6465495001911852221[191] = 0;
   out_6465495001911852221[192] = 0;
   out_6465495001911852221[193] = 0;
   out_6465495001911852221[194] = 0;
   out_6465495001911852221[195] = 0;
   out_6465495001911852221[196] = 0;
   out_6465495001911852221[197] = 0;
   out_6465495001911852221[198] = 0;
   out_6465495001911852221[199] = 0;
   out_6465495001911852221[200] = 0;
   out_6465495001911852221[201] = 0;
   out_6465495001911852221[202] = 0;
   out_6465495001911852221[203] = 0;
   out_6465495001911852221[204] = 0;
   out_6465495001911852221[205] = 0;
   out_6465495001911852221[206] = 0;
   out_6465495001911852221[207] = 0;
   out_6465495001911852221[208] = 0;
   out_6465495001911852221[209] = 1;
   out_6465495001911852221[210] = 0;
   out_6465495001911852221[211] = 0;
   out_6465495001911852221[212] = 0;
   out_6465495001911852221[213] = 0;
   out_6465495001911852221[214] = 0;
   out_6465495001911852221[215] = 0;
   out_6465495001911852221[216] = 0;
   out_6465495001911852221[217] = 0;
   out_6465495001911852221[218] = 0;
   out_6465495001911852221[219] = 0;
   out_6465495001911852221[220] = 0;
   out_6465495001911852221[221] = 0;
   out_6465495001911852221[222] = 0;
   out_6465495001911852221[223] = 0;
   out_6465495001911852221[224] = 0;
   out_6465495001911852221[225] = 0;
   out_6465495001911852221[226] = 0;
   out_6465495001911852221[227] = 0;
   out_6465495001911852221[228] = 1;
   out_6465495001911852221[229] = 0;
   out_6465495001911852221[230] = 0;
   out_6465495001911852221[231] = 0;
   out_6465495001911852221[232] = 0;
   out_6465495001911852221[233] = 0;
   out_6465495001911852221[234] = 0;
   out_6465495001911852221[235] = 0;
   out_6465495001911852221[236] = 0;
   out_6465495001911852221[237] = 0;
   out_6465495001911852221[238] = 0;
   out_6465495001911852221[239] = 0;
   out_6465495001911852221[240] = 0;
   out_6465495001911852221[241] = 0;
   out_6465495001911852221[242] = 0;
   out_6465495001911852221[243] = 0;
   out_6465495001911852221[244] = 0;
   out_6465495001911852221[245] = 0;
   out_6465495001911852221[246] = 0;
   out_6465495001911852221[247] = 1;
   out_6465495001911852221[248] = 0;
   out_6465495001911852221[249] = 0;
   out_6465495001911852221[250] = 0;
   out_6465495001911852221[251] = 0;
   out_6465495001911852221[252] = 0;
   out_6465495001911852221[253] = 0;
   out_6465495001911852221[254] = 0;
   out_6465495001911852221[255] = 0;
   out_6465495001911852221[256] = 0;
   out_6465495001911852221[257] = 0;
   out_6465495001911852221[258] = 0;
   out_6465495001911852221[259] = 0;
   out_6465495001911852221[260] = 0;
   out_6465495001911852221[261] = 0;
   out_6465495001911852221[262] = 0;
   out_6465495001911852221[263] = 0;
   out_6465495001911852221[264] = 0;
   out_6465495001911852221[265] = 0;
   out_6465495001911852221[266] = 1;
   out_6465495001911852221[267] = 0;
   out_6465495001911852221[268] = 0;
   out_6465495001911852221[269] = 0;
   out_6465495001911852221[270] = 0;
   out_6465495001911852221[271] = 0;
   out_6465495001911852221[272] = 0;
   out_6465495001911852221[273] = 0;
   out_6465495001911852221[274] = 0;
   out_6465495001911852221[275] = 0;
   out_6465495001911852221[276] = 0;
   out_6465495001911852221[277] = 0;
   out_6465495001911852221[278] = 0;
   out_6465495001911852221[279] = 0;
   out_6465495001911852221[280] = 0;
   out_6465495001911852221[281] = 0;
   out_6465495001911852221[282] = 0;
   out_6465495001911852221[283] = 0;
   out_6465495001911852221[284] = 0;
   out_6465495001911852221[285] = 1;
   out_6465495001911852221[286] = 0;
   out_6465495001911852221[287] = 0;
   out_6465495001911852221[288] = 0;
   out_6465495001911852221[289] = 0;
   out_6465495001911852221[290] = 0;
   out_6465495001911852221[291] = 0;
   out_6465495001911852221[292] = 0;
   out_6465495001911852221[293] = 0;
   out_6465495001911852221[294] = 0;
   out_6465495001911852221[295] = 0;
   out_6465495001911852221[296] = 0;
   out_6465495001911852221[297] = 0;
   out_6465495001911852221[298] = 0;
   out_6465495001911852221[299] = 0;
   out_6465495001911852221[300] = 0;
   out_6465495001911852221[301] = 0;
   out_6465495001911852221[302] = 0;
   out_6465495001911852221[303] = 0;
   out_6465495001911852221[304] = 1;
   out_6465495001911852221[305] = 0;
   out_6465495001911852221[306] = 0;
   out_6465495001911852221[307] = 0;
   out_6465495001911852221[308] = 0;
   out_6465495001911852221[309] = 0;
   out_6465495001911852221[310] = 0;
   out_6465495001911852221[311] = 0;
   out_6465495001911852221[312] = 0;
   out_6465495001911852221[313] = 0;
   out_6465495001911852221[314] = 0;
   out_6465495001911852221[315] = 0;
   out_6465495001911852221[316] = 0;
   out_6465495001911852221[317] = 0;
   out_6465495001911852221[318] = 0;
   out_6465495001911852221[319] = 0;
   out_6465495001911852221[320] = 0;
   out_6465495001911852221[321] = 0;
   out_6465495001911852221[322] = 0;
   out_6465495001911852221[323] = 1;
}
void h_4(double *state, double *unused, double *out_7442631847161232120) {
   out_7442631847161232120[0] = state[6] + state[9];
   out_7442631847161232120[1] = state[7] + state[10];
   out_7442631847161232120[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_8142960846497148836) {
   out_8142960846497148836[0] = 0;
   out_8142960846497148836[1] = 0;
   out_8142960846497148836[2] = 0;
   out_8142960846497148836[3] = 0;
   out_8142960846497148836[4] = 0;
   out_8142960846497148836[5] = 0;
   out_8142960846497148836[6] = 1;
   out_8142960846497148836[7] = 0;
   out_8142960846497148836[8] = 0;
   out_8142960846497148836[9] = 1;
   out_8142960846497148836[10] = 0;
   out_8142960846497148836[11] = 0;
   out_8142960846497148836[12] = 0;
   out_8142960846497148836[13] = 0;
   out_8142960846497148836[14] = 0;
   out_8142960846497148836[15] = 0;
   out_8142960846497148836[16] = 0;
   out_8142960846497148836[17] = 0;
   out_8142960846497148836[18] = 0;
   out_8142960846497148836[19] = 0;
   out_8142960846497148836[20] = 0;
   out_8142960846497148836[21] = 0;
   out_8142960846497148836[22] = 0;
   out_8142960846497148836[23] = 0;
   out_8142960846497148836[24] = 0;
   out_8142960846497148836[25] = 1;
   out_8142960846497148836[26] = 0;
   out_8142960846497148836[27] = 0;
   out_8142960846497148836[28] = 1;
   out_8142960846497148836[29] = 0;
   out_8142960846497148836[30] = 0;
   out_8142960846497148836[31] = 0;
   out_8142960846497148836[32] = 0;
   out_8142960846497148836[33] = 0;
   out_8142960846497148836[34] = 0;
   out_8142960846497148836[35] = 0;
   out_8142960846497148836[36] = 0;
   out_8142960846497148836[37] = 0;
   out_8142960846497148836[38] = 0;
   out_8142960846497148836[39] = 0;
   out_8142960846497148836[40] = 0;
   out_8142960846497148836[41] = 0;
   out_8142960846497148836[42] = 0;
   out_8142960846497148836[43] = 0;
   out_8142960846497148836[44] = 1;
   out_8142960846497148836[45] = 0;
   out_8142960846497148836[46] = 0;
   out_8142960846497148836[47] = 1;
   out_8142960846497148836[48] = 0;
   out_8142960846497148836[49] = 0;
   out_8142960846497148836[50] = 0;
   out_8142960846497148836[51] = 0;
   out_8142960846497148836[52] = 0;
   out_8142960846497148836[53] = 0;
}
void h_10(double *state, double *unused, double *out_6865183365695080269) {
   out_6865183365695080269[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_6865183365695080269[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_6865183365695080269[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_456103805919410821) {
   out_456103805919410821[0] = 0;
   out_456103805919410821[1] = 9.8100000000000005*cos(state[1]);
   out_456103805919410821[2] = 0;
   out_456103805919410821[3] = 0;
   out_456103805919410821[4] = -state[8];
   out_456103805919410821[5] = state[7];
   out_456103805919410821[6] = 0;
   out_456103805919410821[7] = state[5];
   out_456103805919410821[8] = -state[4];
   out_456103805919410821[9] = 0;
   out_456103805919410821[10] = 0;
   out_456103805919410821[11] = 0;
   out_456103805919410821[12] = 1;
   out_456103805919410821[13] = 0;
   out_456103805919410821[14] = 0;
   out_456103805919410821[15] = 1;
   out_456103805919410821[16] = 0;
   out_456103805919410821[17] = 0;
   out_456103805919410821[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_456103805919410821[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_456103805919410821[20] = 0;
   out_456103805919410821[21] = state[8];
   out_456103805919410821[22] = 0;
   out_456103805919410821[23] = -state[6];
   out_456103805919410821[24] = -state[5];
   out_456103805919410821[25] = 0;
   out_456103805919410821[26] = state[3];
   out_456103805919410821[27] = 0;
   out_456103805919410821[28] = 0;
   out_456103805919410821[29] = 0;
   out_456103805919410821[30] = 0;
   out_456103805919410821[31] = 1;
   out_456103805919410821[32] = 0;
   out_456103805919410821[33] = 0;
   out_456103805919410821[34] = 1;
   out_456103805919410821[35] = 0;
   out_456103805919410821[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_456103805919410821[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_456103805919410821[38] = 0;
   out_456103805919410821[39] = -state[7];
   out_456103805919410821[40] = state[6];
   out_456103805919410821[41] = 0;
   out_456103805919410821[42] = state[4];
   out_456103805919410821[43] = -state[3];
   out_456103805919410821[44] = 0;
   out_456103805919410821[45] = 0;
   out_456103805919410821[46] = 0;
   out_456103805919410821[47] = 0;
   out_456103805919410821[48] = 0;
   out_456103805919410821[49] = 0;
   out_456103805919410821[50] = 1;
   out_456103805919410821[51] = 0;
   out_456103805919410821[52] = 0;
   out_456103805919410821[53] = 1;
}
void h_13(double *state, double *unused, double *out_2130091715364414233) {
   out_2130091715364414233[0] = state[3];
   out_2130091715364414233[1] = state[4];
   out_2130091715364414233[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2693152018895701851) {
   out_2693152018895701851[0] = 0;
   out_2693152018895701851[1] = 0;
   out_2693152018895701851[2] = 0;
   out_2693152018895701851[3] = 1;
   out_2693152018895701851[4] = 0;
   out_2693152018895701851[5] = 0;
   out_2693152018895701851[6] = 0;
   out_2693152018895701851[7] = 0;
   out_2693152018895701851[8] = 0;
   out_2693152018895701851[9] = 0;
   out_2693152018895701851[10] = 0;
   out_2693152018895701851[11] = 0;
   out_2693152018895701851[12] = 0;
   out_2693152018895701851[13] = 0;
   out_2693152018895701851[14] = 0;
   out_2693152018895701851[15] = 0;
   out_2693152018895701851[16] = 0;
   out_2693152018895701851[17] = 0;
   out_2693152018895701851[18] = 0;
   out_2693152018895701851[19] = 0;
   out_2693152018895701851[20] = 0;
   out_2693152018895701851[21] = 0;
   out_2693152018895701851[22] = 1;
   out_2693152018895701851[23] = 0;
   out_2693152018895701851[24] = 0;
   out_2693152018895701851[25] = 0;
   out_2693152018895701851[26] = 0;
   out_2693152018895701851[27] = 0;
   out_2693152018895701851[28] = 0;
   out_2693152018895701851[29] = 0;
   out_2693152018895701851[30] = 0;
   out_2693152018895701851[31] = 0;
   out_2693152018895701851[32] = 0;
   out_2693152018895701851[33] = 0;
   out_2693152018895701851[34] = 0;
   out_2693152018895701851[35] = 0;
   out_2693152018895701851[36] = 0;
   out_2693152018895701851[37] = 0;
   out_2693152018895701851[38] = 0;
   out_2693152018895701851[39] = 0;
   out_2693152018895701851[40] = 0;
   out_2693152018895701851[41] = 1;
   out_2693152018895701851[42] = 0;
   out_2693152018895701851[43] = 0;
   out_2693152018895701851[44] = 0;
   out_2693152018895701851[45] = 0;
   out_2693152018895701851[46] = 0;
   out_2693152018895701851[47] = 0;
   out_2693152018895701851[48] = 0;
   out_2693152018895701851[49] = 0;
   out_2693152018895701851[50] = 0;
   out_2693152018895701851[51] = 0;
   out_2693152018895701851[52] = 0;
   out_2693152018895701851[53] = 0;
}
void h_14(double *state, double *unused, double *out_2314638522999502046) {
   out_2314638522999502046[0] = state[6];
   out_2314638522999502046[1] = state[7];
   out_2314638522999502046[2] = state[8];
}
void H_14(double *state, double *unused, double *out_6340542370872918251) {
   out_6340542370872918251[0] = 0;
   out_6340542370872918251[1] = 0;
   out_6340542370872918251[2] = 0;
   out_6340542370872918251[3] = 0;
   out_6340542370872918251[4] = 0;
   out_6340542370872918251[5] = 0;
   out_6340542370872918251[6] = 1;
   out_6340542370872918251[7] = 0;
   out_6340542370872918251[8] = 0;
   out_6340542370872918251[9] = 0;
   out_6340542370872918251[10] = 0;
   out_6340542370872918251[11] = 0;
   out_6340542370872918251[12] = 0;
   out_6340542370872918251[13] = 0;
   out_6340542370872918251[14] = 0;
   out_6340542370872918251[15] = 0;
   out_6340542370872918251[16] = 0;
   out_6340542370872918251[17] = 0;
   out_6340542370872918251[18] = 0;
   out_6340542370872918251[19] = 0;
   out_6340542370872918251[20] = 0;
   out_6340542370872918251[21] = 0;
   out_6340542370872918251[22] = 0;
   out_6340542370872918251[23] = 0;
   out_6340542370872918251[24] = 0;
   out_6340542370872918251[25] = 1;
   out_6340542370872918251[26] = 0;
   out_6340542370872918251[27] = 0;
   out_6340542370872918251[28] = 0;
   out_6340542370872918251[29] = 0;
   out_6340542370872918251[30] = 0;
   out_6340542370872918251[31] = 0;
   out_6340542370872918251[32] = 0;
   out_6340542370872918251[33] = 0;
   out_6340542370872918251[34] = 0;
   out_6340542370872918251[35] = 0;
   out_6340542370872918251[36] = 0;
   out_6340542370872918251[37] = 0;
   out_6340542370872918251[38] = 0;
   out_6340542370872918251[39] = 0;
   out_6340542370872918251[40] = 0;
   out_6340542370872918251[41] = 0;
   out_6340542370872918251[42] = 0;
   out_6340542370872918251[43] = 0;
   out_6340542370872918251[44] = 1;
   out_6340542370872918251[45] = 0;
   out_6340542370872918251[46] = 0;
   out_6340542370872918251[47] = 0;
   out_6340542370872918251[48] = 0;
   out_6340542370872918251[49] = 0;
   out_6340542370872918251[50] = 0;
   out_6340542370872918251[51] = 0;
   out_6340542370872918251[52] = 0;
   out_6340542370872918251[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_6891956137394554809) {
  err_fun(nom_x, delta_x, out_6891956137394554809);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_352074767866048570) {
  inv_err_fun(nom_x, true_x, out_352074767866048570);
}
void pose_H_mod_fun(double *state, double *out_57344037476075931) {
  H_mod_fun(state, out_57344037476075931);
}
void pose_f_fun(double *state, double dt, double *out_8328845329683204295) {
  f_fun(state,  dt, out_8328845329683204295);
}
void pose_F_fun(double *state, double dt, double *out_6465495001911852221) {
  F_fun(state,  dt, out_6465495001911852221);
}
void pose_h_4(double *state, double *unused, double *out_7442631847161232120) {
  h_4(state, unused, out_7442631847161232120);
}
void pose_H_4(double *state, double *unused, double *out_8142960846497148836) {
  H_4(state, unused, out_8142960846497148836);
}
void pose_h_10(double *state, double *unused, double *out_6865183365695080269) {
  h_10(state, unused, out_6865183365695080269);
}
void pose_H_10(double *state, double *unused, double *out_456103805919410821) {
  H_10(state, unused, out_456103805919410821);
}
void pose_h_13(double *state, double *unused, double *out_2130091715364414233) {
  h_13(state, unused, out_2130091715364414233);
}
void pose_H_13(double *state, double *unused, double *out_2693152018895701851) {
  H_13(state, unused, out_2693152018895701851);
}
void pose_h_14(double *state, double *unused, double *out_2314638522999502046) {
  h_14(state, unused, out_2314638522999502046);
}
void pose_H_14(double *state, double *unused, double *out_6340542370872918251) {
  H_14(state, unused, out_6340542370872918251);
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
