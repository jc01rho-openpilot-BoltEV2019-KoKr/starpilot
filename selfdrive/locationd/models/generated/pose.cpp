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
void err_fun(double *nom_x, double *delta_x, double *out_4926409855120774640) {
   out_4926409855120774640[0] = delta_x[0] + nom_x[0];
   out_4926409855120774640[1] = delta_x[1] + nom_x[1];
   out_4926409855120774640[2] = delta_x[2] + nom_x[2];
   out_4926409855120774640[3] = delta_x[3] + nom_x[3];
   out_4926409855120774640[4] = delta_x[4] + nom_x[4];
   out_4926409855120774640[5] = delta_x[5] + nom_x[5];
   out_4926409855120774640[6] = delta_x[6] + nom_x[6];
   out_4926409855120774640[7] = delta_x[7] + nom_x[7];
   out_4926409855120774640[8] = delta_x[8] + nom_x[8];
   out_4926409855120774640[9] = delta_x[9] + nom_x[9];
   out_4926409855120774640[10] = delta_x[10] + nom_x[10];
   out_4926409855120774640[11] = delta_x[11] + nom_x[11];
   out_4926409855120774640[12] = delta_x[12] + nom_x[12];
   out_4926409855120774640[13] = delta_x[13] + nom_x[13];
   out_4926409855120774640[14] = delta_x[14] + nom_x[14];
   out_4926409855120774640[15] = delta_x[15] + nom_x[15];
   out_4926409855120774640[16] = delta_x[16] + nom_x[16];
   out_4926409855120774640[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6187782627613179741) {
   out_6187782627613179741[0] = -nom_x[0] + true_x[0];
   out_6187782627613179741[1] = -nom_x[1] + true_x[1];
   out_6187782627613179741[2] = -nom_x[2] + true_x[2];
   out_6187782627613179741[3] = -nom_x[3] + true_x[3];
   out_6187782627613179741[4] = -nom_x[4] + true_x[4];
   out_6187782627613179741[5] = -nom_x[5] + true_x[5];
   out_6187782627613179741[6] = -nom_x[6] + true_x[6];
   out_6187782627613179741[7] = -nom_x[7] + true_x[7];
   out_6187782627613179741[8] = -nom_x[8] + true_x[8];
   out_6187782627613179741[9] = -nom_x[9] + true_x[9];
   out_6187782627613179741[10] = -nom_x[10] + true_x[10];
   out_6187782627613179741[11] = -nom_x[11] + true_x[11];
   out_6187782627613179741[12] = -nom_x[12] + true_x[12];
   out_6187782627613179741[13] = -nom_x[13] + true_x[13];
   out_6187782627613179741[14] = -nom_x[14] + true_x[14];
   out_6187782627613179741[15] = -nom_x[15] + true_x[15];
   out_6187782627613179741[16] = -nom_x[16] + true_x[16];
   out_6187782627613179741[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5486902536301149939) {
   out_5486902536301149939[0] = 1.0;
   out_5486902536301149939[1] = 0.0;
   out_5486902536301149939[2] = 0.0;
   out_5486902536301149939[3] = 0.0;
   out_5486902536301149939[4] = 0.0;
   out_5486902536301149939[5] = 0.0;
   out_5486902536301149939[6] = 0.0;
   out_5486902536301149939[7] = 0.0;
   out_5486902536301149939[8] = 0.0;
   out_5486902536301149939[9] = 0.0;
   out_5486902536301149939[10] = 0.0;
   out_5486902536301149939[11] = 0.0;
   out_5486902536301149939[12] = 0.0;
   out_5486902536301149939[13] = 0.0;
   out_5486902536301149939[14] = 0.0;
   out_5486902536301149939[15] = 0.0;
   out_5486902536301149939[16] = 0.0;
   out_5486902536301149939[17] = 0.0;
   out_5486902536301149939[18] = 0.0;
   out_5486902536301149939[19] = 1.0;
   out_5486902536301149939[20] = 0.0;
   out_5486902536301149939[21] = 0.0;
   out_5486902536301149939[22] = 0.0;
   out_5486902536301149939[23] = 0.0;
   out_5486902536301149939[24] = 0.0;
   out_5486902536301149939[25] = 0.0;
   out_5486902536301149939[26] = 0.0;
   out_5486902536301149939[27] = 0.0;
   out_5486902536301149939[28] = 0.0;
   out_5486902536301149939[29] = 0.0;
   out_5486902536301149939[30] = 0.0;
   out_5486902536301149939[31] = 0.0;
   out_5486902536301149939[32] = 0.0;
   out_5486902536301149939[33] = 0.0;
   out_5486902536301149939[34] = 0.0;
   out_5486902536301149939[35] = 0.0;
   out_5486902536301149939[36] = 0.0;
   out_5486902536301149939[37] = 0.0;
   out_5486902536301149939[38] = 1.0;
   out_5486902536301149939[39] = 0.0;
   out_5486902536301149939[40] = 0.0;
   out_5486902536301149939[41] = 0.0;
   out_5486902536301149939[42] = 0.0;
   out_5486902536301149939[43] = 0.0;
   out_5486902536301149939[44] = 0.0;
   out_5486902536301149939[45] = 0.0;
   out_5486902536301149939[46] = 0.0;
   out_5486902536301149939[47] = 0.0;
   out_5486902536301149939[48] = 0.0;
   out_5486902536301149939[49] = 0.0;
   out_5486902536301149939[50] = 0.0;
   out_5486902536301149939[51] = 0.0;
   out_5486902536301149939[52] = 0.0;
   out_5486902536301149939[53] = 0.0;
   out_5486902536301149939[54] = 0.0;
   out_5486902536301149939[55] = 0.0;
   out_5486902536301149939[56] = 0.0;
   out_5486902536301149939[57] = 1.0;
   out_5486902536301149939[58] = 0.0;
   out_5486902536301149939[59] = 0.0;
   out_5486902536301149939[60] = 0.0;
   out_5486902536301149939[61] = 0.0;
   out_5486902536301149939[62] = 0.0;
   out_5486902536301149939[63] = 0.0;
   out_5486902536301149939[64] = 0.0;
   out_5486902536301149939[65] = 0.0;
   out_5486902536301149939[66] = 0.0;
   out_5486902536301149939[67] = 0.0;
   out_5486902536301149939[68] = 0.0;
   out_5486902536301149939[69] = 0.0;
   out_5486902536301149939[70] = 0.0;
   out_5486902536301149939[71] = 0.0;
   out_5486902536301149939[72] = 0.0;
   out_5486902536301149939[73] = 0.0;
   out_5486902536301149939[74] = 0.0;
   out_5486902536301149939[75] = 0.0;
   out_5486902536301149939[76] = 1.0;
   out_5486902536301149939[77] = 0.0;
   out_5486902536301149939[78] = 0.0;
   out_5486902536301149939[79] = 0.0;
   out_5486902536301149939[80] = 0.0;
   out_5486902536301149939[81] = 0.0;
   out_5486902536301149939[82] = 0.0;
   out_5486902536301149939[83] = 0.0;
   out_5486902536301149939[84] = 0.0;
   out_5486902536301149939[85] = 0.0;
   out_5486902536301149939[86] = 0.0;
   out_5486902536301149939[87] = 0.0;
   out_5486902536301149939[88] = 0.0;
   out_5486902536301149939[89] = 0.0;
   out_5486902536301149939[90] = 0.0;
   out_5486902536301149939[91] = 0.0;
   out_5486902536301149939[92] = 0.0;
   out_5486902536301149939[93] = 0.0;
   out_5486902536301149939[94] = 0.0;
   out_5486902536301149939[95] = 1.0;
   out_5486902536301149939[96] = 0.0;
   out_5486902536301149939[97] = 0.0;
   out_5486902536301149939[98] = 0.0;
   out_5486902536301149939[99] = 0.0;
   out_5486902536301149939[100] = 0.0;
   out_5486902536301149939[101] = 0.0;
   out_5486902536301149939[102] = 0.0;
   out_5486902536301149939[103] = 0.0;
   out_5486902536301149939[104] = 0.0;
   out_5486902536301149939[105] = 0.0;
   out_5486902536301149939[106] = 0.0;
   out_5486902536301149939[107] = 0.0;
   out_5486902536301149939[108] = 0.0;
   out_5486902536301149939[109] = 0.0;
   out_5486902536301149939[110] = 0.0;
   out_5486902536301149939[111] = 0.0;
   out_5486902536301149939[112] = 0.0;
   out_5486902536301149939[113] = 0.0;
   out_5486902536301149939[114] = 1.0;
   out_5486902536301149939[115] = 0.0;
   out_5486902536301149939[116] = 0.0;
   out_5486902536301149939[117] = 0.0;
   out_5486902536301149939[118] = 0.0;
   out_5486902536301149939[119] = 0.0;
   out_5486902536301149939[120] = 0.0;
   out_5486902536301149939[121] = 0.0;
   out_5486902536301149939[122] = 0.0;
   out_5486902536301149939[123] = 0.0;
   out_5486902536301149939[124] = 0.0;
   out_5486902536301149939[125] = 0.0;
   out_5486902536301149939[126] = 0.0;
   out_5486902536301149939[127] = 0.0;
   out_5486902536301149939[128] = 0.0;
   out_5486902536301149939[129] = 0.0;
   out_5486902536301149939[130] = 0.0;
   out_5486902536301149939[131] = 0.0;
   out_5486902536301149939[132] = 0.0;
   out_5486902536301149939[133] = 1.0;
   out_5486902536301149939[134] = 0.0;
   out_5486902536301149939[135] = 0.0;
   out_5486902536301149939[136] = 0.0;
   out_5486902536301149939[137] = 0.0;
   out_5486902536301149939[138] = 0.0;
   out_5486902536301149939[139] = 0.0;
   out_5486902536301149939[140] = 0.0;
   out_5486902536301149939[141] = 0.0;
   out_5486902536301149939[142] = 0.0;
   out_5486902536301149939[143] = 0.0;
   out_5486902536301149939[144] = 0.0;
   out_5486902536301149939[145] = 0.0;
   out_5486902536301149939[146] = 0.0;
   out_5486902536301149939[147] = 0.0;
   out_5486902536301149939[148] = 0.0;
   out_5486902536301149939[149] = 0.0;
   out_5486902536301149939[150] = 0.0;
   out_5486902536301149939[151] = 0.0;
   out_5486902536301149939[152] = 1.0;
   out_5486902536301149939[153] = 0.0;
   out_5486902536301149939[154] = 0.0;
   out_5486902536301149939[155] = 0.0;
   out_5486902536301149939[156] = 0.0;
   out_5486902536301149939[157] = 0.0;
   out_5486902536301149939[158] = 0.0;
   out_5486902536301149939[159] = 0.0;
   out_5486902536301149939[160] = 0.0;
   out_5486902536301149939[161] = 0.0;
   out_5486902536301149939[162] = 0.0;
   out_5486902536301149939[163] = 0.0;
   out_5486902536301149939[164] = 0.0;
   out_5486902536301149939[165] = 0.0;
   out_5486902536301149939[166] = 0.0;
   out_5486902536301149939[167] = 0.0;
   out_5486902536301149939[168] = 0.0;
   out_5486902536301149939[169] = 0.0;
   out_5486902536301149939[170] = 0.0;
   out_5486902536301149939[171] = 1.0;
   out_5486902536301149939[172] = 0.0;
   out_5486902536301149939[173] = 0.0;
   out_5486902536301149939[174] = 0.0;
   out_5486902536301149939[175] = 0.0;
   out_5486902536301149939[176] = 0.0;
   out_5486902536301149939[177] = 0.0;
   out_5486902536301149939[178] = 0.0;
   out_5486902536301149939[179] = 0.0;
   out_5486902536301149939[180] = 0.0;
   out_5486902536301149939[181] = 0.0;
   out_5486902536301149939[182] = 0.0;
   out_5486902536301149939[183] = 0.0;
   out_5486902536301149939[184] = 0.0;
   out_5486902536301149939[185] = 0.0;
   out_5486902536301149939[186] = 0.0;
   out_5486902536301149939[187] = 0.0;
   out_5486902536301149939[188] = 0.0;
   out_5486902536301149939[189] = 0.0;
   out_5486902536301149939[190] = 1.0;
   out_5486902536301149939[191] = 0.0;
   out_5486902536301149939[192] = 0.0;
   out_5486902536301149939[193] = 0.0;
   out_5486902536301149939[194] = 0.0;
   out_5486902536301149939[195] = 0.0;
   out_5486902536301149939[196] = 0.0;
   out_5486902536301149939[197] = 0.0;
   out_5486902536301149939[198] = 0.0;
   out_5486902536301149939[199] = 0.0;
   out_5486902536301149939[200] = 0.0;
   out_5486902536301149939[201] = 0.0;
   out_5486902536301149939[202] = 0.0;
   out_5486902536301149939[203] = 0.0;
   out_5486902536301149939[204] = 0.0;
   out_5486902536301149939[205] = 0.0;
   out_5486902536301149939[206] = 0.0;
   out_5486902536301149939[207] = 0.0;
   out_5486902536301149939[208] = 0.0;
   out_5486902536301149939[209] = 1.0;
   out_5486902536301149939[210] = 0.0;
   out_5486902536301149939[211] = 0.0;
   out_5486902536301149939[212] = 0.0;
   out_5486902536301149939[213] = 0.0;
   out_5486902536301149939[214] = 0.0;
   out_5486902536301149939[215] = 0.0;
   out_5486902536301149939[216] = 0.0;
   out_5486902536301149939[217] = 0.0;
   out_5486902536301149939[218] = 0.0;
   out_5486902536301149939[219] = 0.0;
   out_5486902536301149939[220] = 0.0;
   out_5486902536301149939[221] = 0.0;
   out_5486902536301149939[222] = 0.0;
   out_5486902536301149939[223] = 0.0;
   out_5486902536301149939[224] = 0.0;
   out_5486902536301149939[225] = 0.0;
   out_5486902536301149939[226] = 0.0;
   out_5486902536301149939[227] = 0.0;
   out_5486902536301149939[228] = 1.0;
   out_5486902536301149939[229] = 0.0;
   out_5486902536301149939[230] = 0.0;
   out_5486902536301149939[231] = 0.0;
   out_5486902536301149939[232] = 0.0;
   out_5486902536301149939[233] = 0.0;
   out_5486902536301149939[234] = 0.0;
   out_5486902536301149939[235] = 0.0;
   out_5486902536301149939[236] = 0.0;
   out_5486902536301149939[237] = 0.0;
   out_5486902536301149939[238] = 0.0;
   out_5486902536301149939[239] = 0.0;
   out_5486902536301149939[240] = 0.0;
   out_5486902536301149939[241] = 0.0;
   out_5486902536301149939[242] = 0.0;
   out_5486902536301149939[243] = 0.0;
   out_5486902536301149939[244] = 0.0;
   out_5486902536301149939[245] = 0.0;
   out_5486902536301149939[246] = 0.0;
   out_5486902536301149939[247] = 1.0;
   out_5486902536301149939[248] = 0.0;
   out_5486902536301149939[249] = 0.0;
   out_5486902536301149939[250] = 0.0;
   out_5486902536301149939[251] = 0.0;
   out_5486902536301149939[252] = 0.0;
   out_5486902536301149939[253] = 0.0;
   out_5486902536301149939[254] = 0.0;
   out_5486902536301149939[255] = 0.0;
   out_5486902536301149939[256] = 0.0;
   out_5486902536301149939[257] = 0.0;
   out_5486902536301149939[258] = 0.0;
   out_5486902536301149939[259] = 0.0;
   out_5486902536301149939[260] = 0.0;
   out_5486902536301149939[261] = 0.0;
   out_5486902536301149939[262] = 0.0;
   out_5486902536301149939[263] = 0.0;
   out_5486902536301149939[264] = 0.0;
   out_5486902536301149939[265] = 0.0;
   out_5486902536301149939[266] = 1.0;
   out_5486902536301149939[267] = 0.0;
   out_5486902536301149939[268] = 0.0;
   out_5486902536301149939[269] = 0.0;
   out_5486902536301149939[270] = 0.0;
   out_5486902536301149939[271] = 0.0;
   out_5486902536301149939[272] = 0.0;
   out_5486902536301149939[273] = 0.0;
   out_5486902536301149939[274] = 0.0;
   out_5486902536301149939[275] = 0.0;
   out_5486902536301149939[276] = 0.0;
   out_5486902536301149939[277] = 0.0;
   out_5486902536301149939[278] = 0.0;
   out_5486902536301149939[279] = 0.0;
   out_5486902536301149939[280] = 0.0;
   out_5486902536301149939[281] = 0.0;
   out_5486902536301149939[282] = 0.0;
   out_5486902536301149939[283] = 0.0;
   out_5486902536301149939[284] = 0.0;
   out_5486902536301149939[285] = 1.0;
   out_5486902536301149939[286] = 0.0;
   out_5486902536301149939[287] = 0.0;
   out_5486902536301149939[288] = 0.0;
   out_5486902536301149939[289] = 0.0;
   out_5486902536301149939[290] = 0.0;
   out_5486902536301149939[291] = 0.0;
   out_5486902536301149939[292] = 0.0;
   out_5486902536301149939[293] = 0.0;
   out_5486902536301149939[294] = 0.0;
   out_5486902536301149939[295] = 0.0;
   out_5486902536301149939[296] = 0.0;
   out_5486902536301149939[297] = 0.0;
   out_5486902536301149939[298] = 0.0;
   out_5486902536301149939[299] = 0.0;
   out_5486902536301149939[300] = 0.0;
   out_5486902536301149939[301] = 0.0;
   out_5486902536301149939[302] = 0.0;
   out_5486902536301149939[303] = 0.0;
   out_5486902536301149939[304] = 1.0;
   out_5486902536301149939[305] = 0.0;
   out_5486902536301149939[306] = 0.0;
   out_5486902536301149939[307] = 0.0;
   out_5486902536301149939[308] = 0.0;
   out_5486902536301149939[309] = 0.0;
   out_5486902536301149939[310] = 0.0;
   out_5486902536301149939[311] = 0.0;
   out_5486902536301149939[312] = 0.0;
   out_5486902536301149939[313] = 0.0;
   out_5486902536301149939[314] = 0.0;
   out_5486902536301149939[315] = 0.0;
   out_5486902536301149939[316] = 0.0;
   out_5486902536301149939[317] = 0.0;
   out_5486902536301149939[318] = 0.0;
   out_5486902536301149939[319] = 0.0;
   out_5486902536301149939[320] = 0.0;
   out_5486902536301149939[321] = 0.0;
   out_5486902536301149939[322] = 0.0;
   out_5486902536301149939[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8359863438222097271) {
   out_8359863438222097271[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8359863438222097271[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8359863438222097271[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8359863438222097271[3] = dt*state[12] + state[3];
   out_8359863438222097271[4] = dt*state[13] + state[4];
   out_8359863438222097271[5] = dt*state[14] + state[5];
   out_8359863438222097271[6] = state[6];
   out_8359863438222097271[7] = state[7];
   out_8359863438222097271[8] = state[8];
   out_8359863438222097271[9] = state[9];
   out_8359863438222097271[10] = state[10];
   out_8359863438222097271[11] = state[11];
   out_8359863438222097271[12] = state[12];
   out_8359863438222097271[13] = state[13];
   out_8359863438222097271[14] = state[14];
   out_8359863438222097271[15] = state[15];
   out_8359863438222097271[16] = state[16];
   out_8359863438222097271[17] = state[17];
}
void F_fun(double *state, double dt, double *out_174815157734899050) {
   out_174815157734899050[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_174815157734899050[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_174815157734899050[2] = 0;
   out_174815157734899050[3] = 0;
   out_174815157734899050[4] = 0;
   out_174815157734899050[5] = 0;
   out_174815157734899050[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_174815157734899050[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_174815157734899050[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_174815157734899050[9] = 0;
   out_174815157734899050[10] = 0;
   out_174815157734899050[11] = 0;
   out_174815157734899050[12] = 0;
   out_174815157734899050[13] = 0;
   out_174815157734899050[14] = 0;
   out_174815157734899050[15] = 0;
   out_174815157734899050[16] = 0;
   out_174815157734899050[17] = 0;
   out_174815157734899050[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_174815157734899050[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_174815157734899050[20] = 0;
   out_174815157734899050[21] = 0;
   out_174815157734899050[22] = 0;
   out_174815157734899050[23] = 0;
   out_174815157734899050[24] = 0;
   out_174815157734899050[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_174815157734899050[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_174815157734899050[27] = 0;
   out_174815157734899050[28] = 0;
   out_174815157734899050[29] = 0;
   out_174815157734899050[30] = 0;
   out_174815157734899050[31] = 0;
   out_174815157734899050[32] = 0;
   out_174815157734899050[33] = 0;
   out_174815157734899050[34] = 0;
   out_174815157734899050[35] = 0;
   out_174815157734899050[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_174815157734899050[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_174815157734899050[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_174815157734899050[39] = 0;
   out_174815157734899050[40] = 0;
   out_174815157734899050[41] = 0;
   out_174815157734899050[42] = 0;
   out_174815157734899050[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_174815157734899050[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_174815157734899050[45] = 0;
   out_174815157734899050[46] = 0;
   out_174815157734899050[47] = 0;
   out_174815157734899050[48] = 0;
   out_174815157734899050[49] = 0;
   out_174815157734899050[50] = 0;
   out_174815157734899050[51] = 0;
   out_174815157734899050[52] = 0;
   out_174815157734899050[53] = 0;
   out_174815157734899050[54] = 0;
   out_174815157734899050[55] = 0;
   out_174815157734899050[56] = 0;
   out_174815157734899050[57] = 1;
   out_174815157734899050[58] = 0;
   out_174815157734899050[59] = 0;
   out_174815157734899050[60] = 0;
   out_174815157734899050[61] = 0;
   out_174815157734899050[62] = 0;
   out_174815157734899050[63] = 0;
   out_174815157734899050[64] = 0;
   out_174815157734899050[65] = 0;
   out_174815157734899050[66] = dt;
   out_174815157734899050[67] = 0;
   out_174815157734899050[68] = 0;
   out_174815157734899050[69] = 0;
   out_174815157734899050[70] = 0;
   out_174815157734899050[71] = 0;
   out_174815157734899050[72] = 0;
   out_174815157734899050[73] = 0;
   out_174815157734899050[74] = 0;
   out_174815157734899050[75] = 0;
   out_174815157734899050[76] = 1;
   out_174815157734899050[77] = 0;
   out_174815157734899050[78] = 0;
   out_174815157734899050[79] = 0;
   out_174815157734899050[80] = 0;
   out_174815157734899050[81] = 0;
   out_174815157734899050[82] = 0;
   out_174815157734899050[83] = 0;
   out_174815157734899050[84] = 0;
   out_174815157734899050[85] = dt;
   out_174815157734899050[86] = 0;
   out_174815157734899050[87] = 0;
   out_174815157734899050[88] = 0;
   out_174815157734899050[89] = 0;
   out_174815157734899050[90] = 0;
   out_174815157734899050[91] = 0;
   out_174815157734899050[92] = 0;
   out_174815157734899050[93] = 0;
   out_174815157734899050[94] = 0;
   out_174815157734899050[95] = 1;
   out_174815157734899050[96] = 0;
   out_174815157734899050[97] = 0;
   out_174815157734899050[98] = 0;
   out_174815157734899050[99] = 0;
   out_174815157734899050[100] = 0;
   out_174815157734899050[101] = 0;
   out_174815157734899050[102] = 0;
   out_174815157734899050[103] = 0;
   out_174815157734899050[104] = dt;
   out_174815157734899050[105] = 0;
   out_174815157734899050[106] = 0;
   out_174815157734899050[107] = 0;
   out_174815157734899050[108] = 0;
   out_174815157734899050[109] = 0;
   out_174815157734899050[110] = 0;
   out_174815157734899050[111] = 0;
   out_174815157734899050[112] = 0;
   out_174815157734899050[113] = 0;
   out_174815157734899050[114] = 1;
   out_174815157734899050[115] = 0;
   out_174815157734899050[116] = 0;
   out_174815157734899050[117] = 0;
   out_174815157734899050[118] = 0;
   out_174815157734899050[119] = 0;
   out_174815157734899050[120] = 0;
   out_174815157734899050[121] = 0;
   out_174815157734899050[122] = 0;
   out_174815157734899050[123] = 0;
   out_174815157734899050[124] = 0;
   out_174815157734899050[125] = 0;
   out_174815157734899050[126] = 0;
   out_174815157734899050[127] = 0;
   out_174815157734899050[128] = 0;
   out_174815157734899050[129] = 0;
   out_174815157734899050[130] = 0;
   out_174815157734899050[131] = 0;
   out_174815157734899050[132] = 0;
   out_174815157734899050[133] = 1;
   out_174815157734899050[134] = 0;
   out_174815157734899050[135] = 0;
   out_174815157734899050[136] = 0;
   out_174815157734899050[137] = 0;
   out_174815157734899050[138] = 0;
   out_174815157734899050[139] = 0;
   out_174815157734899050[140] = 0;
   out_174815157734899050[141] = 0;
   out_174815157734899050[142] = 0;
   out_174815157734899050[143] = 0;
   out_174815157734899050[144] = 0;
   out_174815157734899050[145] = 0;
   out_174815157734899050[146] = 0;
   out_174815157734899050[147] = 0;
   out_174815157734899050[148] = 0;
   out_174815157734899050[149] = 0;
   out_174815157734899050[150] = 0;
   out_174815157734899050[151] = 0;
   out_174815157734899050[152] = 1;
   out_174815157734899050[153] = 0;
   out_174815157734899050[154] = 0;
   out_174815157734899050[155] = 0;
   out_174815157734899050[156] = 0;
   out_174815157734899050[157] = 0;
   out_174815157734899050[158] = 0;
   out_174815157734899050[159] = 0;
   out_174815157734899050[160] = 0;
   out_174815157734899050[161] = 0;
   out_174815157734899050[162] = 0;
   out_174815157734899050[163] = 0;
   out_174815157734899050[164] = 0;
   out_174815157734899050[165] = 0;
   out_174815157734899050[166] = 0;
   out_174815157734899050[167] = 0;
   out_174815157734899050[168] = 0;
   out_174815157734899050[169] = 0;
   out_174815157734899050[170] = 0;
   out_174815157734899050[171] = 1;
   out_174815157734899050[172] = 0;
   out_174815157734899050[173] = 0;
   out_174815157734899050[174] = 0;
   out_174815157734899050[175] = 0;
   out_174815157734899050[176] = 0;
   out_174815157734899050[177] = 0;
   out_174815157734899050[178] = 0;
   out_174815157734899050[179] = 0;
   out_174815157734899050[180] = 0;
   out_174815157734899050[181] = 0;
   out_174815157734899050[182] = 0;
   out_174815157734899050[183] = 0;
   out_174815157734899050[184] = 0;
   out_174815157734899050[185] = 0;
   out_174815157734899050[186] = 0;
   out_174815157734899050[187] = 0;
   out_174815157734899050[188] = 0;
   out_174815157734899050[189] = 0;
   out_174815157734899050[190] = 1;
   out_174815157734899050[191] = 0;
   out_174815157734899050[192] = 0;
   out_174815157734899050[193] = 0;
   out_174815157734899050[194] = 0;
   out_174815157734899050[195] = 0;
   out_174815157734899050[196] = 0;
   out_174815157734899050[197] = 0;
   out_174815157734899050[198] = 0;
   out_174815157734899050[199] = 0;
   out_174815157734899050[200] = 0;
   out_174815157734899050[201] = 0;
   out_174815157734899050[202] = 0;
   out_174815157734899050[203] = 0;
   out_174815157734899050[204] = 0;
   out_174815157734899050[205] = 0;
   out_174815157734899050[206] = 0;
   out_174815157734899050[207] = 0;
   out_174815157734899050[208] = 0;
   out_174815157734899050[209] = 1;
   out_174815157734899050[210] = 0;
   out_174815157734899050[211] = 0;
   out_174815157734899050[212] = 0;
   out_174815157734899050[213] = 0;
   out_174815157734899050[214] = 0;
   out_174815157734899050[215] = 0;
   out_174815157734899050[216] = 0;
   out_174815157734899050[217] = 0;
   out_174815157734899050[218] = 0;
   out_174815157734899050[219] = 0;
   out_174815157734899050[220] = 0;
   out_174815157734899050[221] = 0;
   out_174815157734899050[222] = 0;
   out_174815157734899050[223] = 0;
   out_174815157734899050[224] = 0;
   out_174815157734899050[225] = 0;
   out_174815157734899050[226] = 0;
   out_174815157734899050[227] = 0;
   out_174815157734899050[228] = 1;
   out_174815157734899050[229] = 0;
   out_174815157734899050[230] = 0;
   out_174815157734899050[231] = 0;
   out_174815157734899050[232] = 0;
   out_174815157734899050[233] = 0;
   out_174815157734899050[234] = 0;
   out_174815157734899050[235] = 0;
   out_174815157734899050[236] = 0;
   out_174815157734899050[237] = 0;
   out_174815157734899050[238] = 0;
   out_174815157734899050[239] = 0;
   out_174815157734899050[240] = 0;
   out_174815157734899050[241] = 0;
   out_174815157734899050[242] = 0;
   out_174815157734899050[243] = 0;
   out_174815157734899050[244] = 0;
   out_174815157734899050[245] = 0;
   out_174815157734899050[246] = 0;
   out_174815157734899050[247] = 1;
   out_174815157734899050[248] = 0;
   out_174815157734899050[249] = 0;
   out_174815157734899050[250] = 0;
   out_174815157734899050[251] = 0;
   out_174815157734899050[252] = 0;
   out_174815157734899050[253] = 0;
   out_174815157734899050[254] = 0;
   out_174815157734899050[255] = 0;
   out_174815157734899050[256] = 0;
   out_174815157734899050[257] = 0;
   out_174815157734899050[258] = 0;
   out_174815157734899050[259] = 0;
   out_174815157734899050[260] = 0;
   out_174815157734899050[261] = 0;
   out_174815157734899050[262] = 0;
   out_174815157734899050[263] = 0;
   out_174815157734899050[264] = 0;
   out_174815157734899050[265] = 0;
   out_174815157734899050[266] = 1;
   out_174815157734899050[267] = 0;
   out_174815157734899050[268] = 0;
   out_174815157734899050[269] = 0;
   out_174815157734899050[270] = 0;
   out_174815157734899050[271] = 0;
   out_174815157734899050[272] = 0;
   out_174815157734899050[273] = 0;
   out_174815157734899050[274] = 0;
   out_174815157734899050[275] = 0;
   out_174815157734899050[276] = 0;
   out_174815157734899050[277] = 0;
   out_174815157734899050[278] = 0;
   out_174815157734899050[279] = 0;
   out_174815157734899050[280] = 0;
   out_174815157734899050[281] = 0;
   out_174815157734899050[282] = 0;
   out_174815157734899050[283] = 0;
   out_174815157734899050[284] = 0;
   out_174815157734899050[285] = 1;
   out_174815157734899050[286] = 0;
   out_174815157734899050[287] = 0;
   out_174815157734899050[288] = 0;
   out_174815157734899050[289] = 0;
   out_174815157734899050[290] = 0;
   out_174815157734899050[291] = 0;
   out_174815157734899050[292] = 0;
   out_174815157734899050[293] = 0;
   out_174815157734899050[294] = 0;
   out_174815157734899050[295] = 0;
   out_174815157734899050[296] = 0;
   out_174815157734899050[297] = 0;
   out_174815157734899050[298] = 0;
   out_174815157734899050[299] = 0;
   out_174815157734899050[300] = 0;
   out_174815157734899050[301] = 0;
   out_174815157734899050[302] = 0;
   out_174815157734899050[303] = 0;
   out_174815157734899050[304] = 1;
   out_174815157734899050[305] = 0;
   out_174815157734899050[306] = 0;
   out_174815157734899050[307] = 0;
   out_174815157734899050[308] = 0;
   out_174815157734899050[309] = 0;
   out_174815157734899050[310] = 0;
   out_174815157734899050[311] = 0;
   out_174815157734899050[312] = 0;
   out_174815157734899050[313] = 0;
   out_174815157734899050[314] = 0;
   out_174815157734899050[315] = 0;
   out_174815157734899050[316] = 0;
   out_174815157734899050[317] = 0;
   out_174815157734899050[318] = 0;
   out_174815157734899050[319] = 0;
   out_174815157734899050[320] = 0;
   out_174815157734899050[321] = 0;
   out_174815157734899050[322] = 0;
   out_174815157734899050[323] = 1;
}
void h_4(double *state, double *unused, double *out_388088547893374228) {
   out_388088547893374228[0] = state[6] + state[9];
   out_388088547893374228[1] = state[7] + state[10];
   out_388088547893374228[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3526081883612534553) {
   out_3526081883612534553[0] = 0;
   out_3526081883612534553[1] = 0;
   out_3526081883612534553[2] = 0;
   out_3526081883612534553[3] = 0;
   out_3526081883612534553[4] = 0;
   out_3526081883612534553[5] = 0;
   out_3526081883612534553[6] = 1;
   out_3526081883612534553[7] = 0;
   out_3526081883612534553[8] = 0;
   out_3526081883612534553[9] = 1;
   out_3526081883612534553[10] = 0;
   out_3526081883612534553[11] = 0;
   out_3526081883612534553[12] = 0;
   out_3526081883612534553[13] = 0;
   out_3526081883612534553[14] = 0;
   out_3526081883612534553[15] = 0;
   out_3526081883612534553[16] = 0;
   out_3526081883612534553[17] = 0;
   out_3526081883612534553[18] = 0;
   out_3526081883612534553[19] = 0;
   out_3526081883612534553[20] = 0;
   out_3526081883612534553[21] = 0;
   out_3526081883612534553[22] = 0;
   out_3526081883612534553[23] = 0;
   out_3526081883612534553[24] = 0;
   out_3526081883612534553[25] = 1;
   out_3526081883612534553[26] = 0;
   out_3526081883612534553[27] = 0;
   out_3526081883612534553[28] = 1;
   out_3526081883612534553[29] = 0;
   out_3526081883612534553[30] = 0;
   out_3526081883612534553[31] = 0;
   out_3526081883612534553[32] = 0;
   out_3526081883612534553[33] = 0;
   out_3526081883612534553[34] = 0;
   out_3526081883612534553[35] = 0;
   out_3526081883612534553[36] = 0;
   out_3526081883612534553[37] = 0;
   out_3526081883612534553[38] = 0;
   out_3526081883612534553[39] = 0;
   out_3526081883612534553[40] = 0;
   out_3526081883612534553[41] = 0;
   out_3526081883612534553[42] = 0;
   out_3526081883612534553[43] = 0;
   out_3526081883612534553[44] = 1;
   out_3526081883612534553[45] = 0;
   out_3526081883612534553[46] = 0;
   out_3526081883612534553[47] = 1;
   out_3526081883612534553[48] = 0;
   out_3526081883612534553[49] = 0;
   out_3526081883612534553[50] = 0;
   out_3526081883612534553[51] = 0;
   out_3526081883612534553[52] = 0;
   out_3526081883612534553[53] = 0;
}
void h_10(double *state, double *unused, double *out_3651567794159293424) {
   out_3651567794159293424[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3651567794159293424[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3651567794159293424[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7553527708872310168) {
   out_7553527708872310168[0] = 0;
   out_7553527708872310168[1] = 9.8100000000000005*cos(state[1]);
   out_7553527708872310168[2] = 0;
   out_7553527708872310168[3] = 0;
   out_7553527708872310168[4] = -state[8];
   out_7553527708872310168[5] = state[7];
   out_7553527708872310168[6] = 0;
   out_7553527708872310168[7] = state[5];
   out_7553527708872310168[8] = -state[4];
   out_7553527708872310168[9] = 0;
   out_7553527708872310168[10] = 0;
   out_7553527708872310168[11] = 0;
   out_7553527708872310168[12] = 1;
   out_7553527708872310168[13] = 0;
   out_7553527708872310168[14] = 0;
   out_7553527708872310168[15] = 1;
   out_7553527708872310168[16] = 0;
   out_7553527708872310168[17] = 0;
   out_7553527708872310168[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7553527708872310168[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7553527708872310168[20] = 0;
   out_7553527708872310168[21] = state[8];
   out_7553527708872310168[22] = 0;
   out_7553527708872310168[23] = -state[6];
   out_7553527708872310168[24] = -state[5];
   out_7553527708872310168[25] = 0;
   out_7553527708872310168[26] = state[3];
   out_7553527708872310168[27] = 0;
   out_7553527708872310168[28] = 0;
   out_7553527708872310168[29] = 0;
   out_7553527708872310168[30] = 0;
   out_7553527708872310168[31] = 1;
   out_7553527708872310168[32] = 0;
   out_7553527708872310168[33] = 0;
   out_7553527708872310168[34] = 1;
   out_7553527708872310168[35] = 0;
   out_7553527708872310168[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7553527708872310168[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7553527708872310168[38] = 0;
   out_7553527708872310168[39] = -state[7];
   out_7553527708872310168[40] = state[6];
   out_7553527708872310168[41] = 0;
   out_7553527708872310168[42] = state[4];
   out_7553527708872310168[43] = -state[3];
   out_7553527708872310168[44] = 0;
   out_7553527708872310168[45] = 0;
   out_7553527708872310168[46] = 0;
   out_7553527708872310168[47] = 0;
   out_7553527708872310168[48] = 0;
   out_7553527708872310168[49] = 0;
   out_7553527708872310168[50] = 1;
   out_7553527708872310168[51] = 0;
   out_7553527708872310168[52] = 0;
   out_7553527708872310168[53] = 1;
}
void h_13(double *state, double *unused, double *out_5975295746890546976) {
   out_5975295746890546976[0] = state[3];
   out_5975295746890546976[1] = state[4];
   out_5975295746890546976[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6738355708944867354) {
   out_6738355708944867354[0] = 0;
   out_6738355708944867354[1] = 0;
   out_6738355708944867354[2] = 0;
   out_6738355708944867354[3] = 1;
   out_6738355708944867354[4] = 0;
   out_6738355708944867354[5] = 0;
   out_6738355708944867354[6] = 0;
   out_6738355708944867354[7] = 0;
   out_6738355708944867354[8] = 0;
   out_6738355708944867354[9] = 0;
   out_6738355708944867354[10] = 0;
   out_6738355708944867354[11] = 0;
   out_6738355708944867354[12] = 0;
   out_6738355708944867354[13] = 0;
   out_6738355708944867354[14] = 0;
   out_6738355708944867354[15] = 0;
   out_6738355708944867354[16] = 0;
   out_6738355708944867354[17] = 0;
   out_6738355708944867354[18] = 0;
   out_6738355708944867354[19] = 0;
   out_6738355708944867354[20] = 0;
   out_6738355708944867354[21] = 0;
   out_6738355708944867354[22] = 1;
   out_6738355708944867354[23] = 0;
   out_6738355708944867354[24] = 0;
   out_6738355708944867354[25] = 0;
   out_6738355708944867354[26] = 0;
   out_6738355708944867354[27] = 0;
   out_6738355708944867354[28] = 0;
   out_6738355708944867354[29] = 0;
   out_6738355708944867354[30] = 0;
   out_6738355708944867354[31] = 0;
   out_6738355708944867354[32] = 0;
   out_6738355708944867354[33] = 0;
   out_6738355708944867354[34] = 0;
   out_6738355708944867354[35] = 0;
   out_6738355708944867354[36] = 0;
   out_6738355708944867354[37] = 0;
   out_6738355708944867354[38] = 0;
   out_6738355708944867354[39] = 0;
   out_6738355708944867354[40] = 0;
   out_6738355708944867354[41] = 1;
   out_6738355708944867354[42] = 0;
   out_6738355708944867354[43] = 0;
   out_6738355708944867354[44] = 0;
   out_6738355708944867354[45] = 0;
   out_6738355708944867354[46] = 0;
   out_6738355708944867354[47] = 0;
   out_6738355708944867354[48] = 0;
   out_6738355708944867354[49] = 0;
   out_6738355708944867354[50] = 0;
   out_6738355708944867354[51] = 0;
   out_6738355708944867354[52] = 0;
   out_6738355708944867354[53] = 0;
}
void h_14(double *state, double *unused, double *out_7017148445173920389) {
   out_7017148445173920389[0] = state[6];
   out_7017148445173920389[1] = state[7];
   out_7017148445173920389[2] = state[8];
}
void H_14(double *state, double *unused, double *out_7489322739952019082) {
   out_7489322739952019082[0] = 0;
   out_7489322739952019082[1] = 0;
   out_7489322739952019082[2] = 0;
   out_7489322739952019082[3] = 0;
   out_7489322739952019082[4] = 0;
   out_7489322739952019082[5] = 0;
   out_7489322739952019082[6] = 1;
   out_7489322739952019082[7] = 0;
   out_7489322739952019082[8] = 0;
   out_7489322739952019082[9] = 0;
   out_7489322739952019082[10] = 0;
   out_7489322739952019082[11] = 0;
   out_7489322739952019082[12] = 0;
   out_7489322739952019082[13] = 0;
   out_7489322739952019082[14] = 0;
   out_7489322739952019082[15] = 0;
   out_7489322739952019082[16] = 0;
   out_7489322739952019082[17] = 0;
   out_7489322739952019082[18] = 0;
   out_7489322739952019082[19] = 0;
   out_7489322739952019082[20] = 0;
   out_7489322739952019082[21] = 0;
   out_7489322739952019082[22] = 0;
   out_7489322739952019082[23] = 0;
   out_7489322739952019082[24] = 0;
   out_7489322739952019082[25] = 1;
   out_7489322739952019082[26] = 0;
   out_7489322739952019082[27] = 0;
   out_7489322739952019082[28] = 0;
   out_7489322739952019082[29] = 0;
   out_7489322739952019082[30] = 0;
   out_7489322739952019082[31] = 0;
   out_7489322739952019082[32] = 0;
   out_7489322739952019082[33] = 0;
   out_7489322739952019082[34] = 0;
   out_7489322739952019082[35] = 0;
   out_7489322739952019082[36] = 0;
   out_7489322739952019082[37] = 0;
   out_7489322739952019082[38] = 0;
   out_7489322739952019082[39] = 0;
   out_7489322739952019082[40] = 0;
   out_7489322739952019082[41] = 0;
   out_7489322739952019082[42] = 0;
   out_7489322739952019082[43] = 0;
   out_7489322739952019082[44] = 1;
   out_7489322739952019082[45] = 0;
   out_7489322739952019082[46] = 0;
   out_7489322739952019082[47] = 0;
   out_7489322739952019082[48] = 0;
   out_7489322739952019082[49] = 0;
   out_7489322739952019082[50] = 0;
   out_7489322739952019082[51] = 0;
   out_7489322739952019082[52] = 0;
   out_7489322739952019082[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_4926409855120774640) {
  err_fun(nom_x, delta_x, out_4926409855120774640);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6187782627613179741) {
  inv_err_fun(nom_x, true_x, out_6187782627613179741);
}
void pose_H_mod_fun(double *state, double *out_5486902536301149939) {
  H_mod_fun(state, out_5486902536301149939);
}
void pose_f_fun(double *state, double dt, double *out_8359863438222097271) {
  f_fun(state,  dt, out_8359863438222097271);
}
void pose_F_fun(double *state, double dt, double *out_174815157734899050) {
  F_fun(state,  dt, out_174815157734899050);
}
void pose_h_4(double *state, double *unused, double *out_388088547893374228) {
  h_4(state, unused, out_388088547893374228);
}
void pose_H_4(double *state, double *unused, double *out_3526081883612534553) {
  H_4(state, unused, out_3526081883612534553);
}
void pose_h_10(double *state, double *unused, double *out_3651567794159293424) {
  h_10(state, unused, out_3651567794159293424);
}
void pose_H_10(double *state, double *unused, double *out_7553527708872310168) {
  H_10(state, unused, out_7553527708872310168);
}
void pose_h_13(double *state, double *unused, double *out_5975295746890546976) {
  h_13(state, unused, out_5975295746890546976);
}
void pose_H_13(double *state, double *unused, double *out_6738355708944867354) {
  H_13(state, unused, out_6738355708944867354);
}
void pose_h_14(double *state, double *unused, double *out_7017148445173920389) {
  h_14(state, unused, out_7017148445173920389);
}
void pose_H_14(double *state, double *unused, double *out_7489322739952019082) {
  H_14(state, unused, out_7489322739952019082);
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
