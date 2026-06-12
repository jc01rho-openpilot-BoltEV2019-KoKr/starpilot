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
void err_fun(double *nom_x, double *delta_x, double *out_2815596288453817821) {
   out_2815596288453817821[0] = delta_x[0] + nom_x[0];
   out_2815596288453817821[1] = delta_x[1] + nom_x[1];
   out_2815596288453817821[2] = delta_x[2] + nom_x[2];
   out_2815596288453817821[3] = delta_x[3] + nom_x[3];
   out_2815596288453817821[4] = delta_x[4] + nom_x[4];
   out_2815596288453817821[5] = delta_x[5] + nom_x[5];
   out_2815596288453817821[6] = delta_x[6] + nom_x[6];
   out_2815596288453817821[7] = delta_x[7] + nom_x[7];
   out_2815596288453817821[8] = delta_x[8] + nom_x[8];
   out_2815596288453817821[9] = delta_x[9] + nom_x[9];
   out_2815596288453817821[10] = delta_x[10] + nom_x[10];
   out_2815596288453817821[11] = delta_x[11] + nom_x[11];
   out_2815596288453817821[12] = delta_x[12] + nom_x[12];
   out_2815596288453817821[13] = delta_x[13] + nom_x[13];
   out_2815596288453817821[14] = delta_x[14] + nom_x[14];
   out_2815596288453817821[15] = delta_x[15] + nom_x[15];
   out_2815596288453817821[16] = delta_x[16] + nom_x[16];
   out_2815596288453817821[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8761485569796980977) {
   out_8761485569796980977[0] = -nom_x[0] + true_x[0];
   out_8761485569796980977[1] = -nom_x[1] + true_x[1];
   out_8761485569796980977[2] = -nom_x[2] + true_x[2];
   out_8761485569796980977[3] = -nom_x[3] + true_x[3];
   out_8761485569796980977[4] = -nom_x[4] + true_x[4];
   out_8761485569796980977[5] = -nom_x[5] + true_x[5];
   out_8761485569796980977[6] = -nom_x[6] + true_x[6];
   out_8761485569796980977[7] = -nom_x[7] + true_x[7];
   out_8761485569796980977[8] = -nom_x[8] + true_x[8];
   out_8761485569796980977[9] = -nom_x[9] + true_x[9];
   out_8761485569796980977[10] = -nom_x[10] + true_x[10];
   out_8761485569796980977[11] = -nom_x[11] + true_x[11];
   out_8761485569796980977[12] = -nom_x[12] + true_x[12];
   out_8761485569796980977[13] = -nom_x[13] + true_x[13];
   out_8761485569796980977[14] = -nom_x[14] + true_x[14];
   out_8761485569796980977[15] = -nom_x[15] + true_x[15];
   out_8761485569796980977[16] = -nom_x[16] + true_x[16];
   out_8761485569796980977[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_9016812017969752156) {
   out_9016812017969752156[0] = 1.0;
   out_9016812017969752156[1] = 0.0;
   out_9016812017969752156[2] = 0.0;
   out_9016812017969752156[3] = 0.0;
   out_9016812017969752156[4] = 0.0;
   out_9016812017969752156[5] = 0.0;
   out_9016812017969752156[6] = 0.0;
   out_9016812017969752156[7] = 0.0;
   out_9016812017969752156[8] = 0.0;
   out_9016812017969752156[9] = 0.0;
   out_9016812017969752156[10] = 0.0;
   out_9016812017969752156[11] = 0.0;
   out_9016812017969752156[12] = 0.0;
   out_9016812017969752156[13] = 0.0;
   out_9016812017969752156[14] = 0.0;
   out_9016812017969752156[15] = 0.0;
   out_9016812017969752156[16] = 0.0;
   out_9016812017969752156[17] = 0.0;
   out_9016812017969752156[18] = 0.0;
   out_9016812017969752156[19] = 1.0;
   out_9016812017969752156[20] = 0.0;
   out_9016812017969752156[21] = 0.0;
   out_9016812017969752156[22] = 0.0;
   out_9016812017969752156[23] = 0.0;
   out_9016812017969752156[24] = 0.0;
   out_9016812017969752156[25] = 0.0;
   out_9016812017969752156[26] = 0.0;
   out_9016812017969752156[27] = 0.0;
   out_9016812017969752156[28] = 0.0;
   out_9016812017969752156[29] = 0.0;
   out_9016812017969752156[30] = 0.0;
   out_9016812017969752156[31] = 0.0;
   out_9016812017969752156[32] = 0.0;
   out_9016812017969752156[33] = 0.0;
   out_9016812017969752156[34] = 0.0;
   out_9016812017969752156[35] = 0.0;
   out_9016812017969752156[36] = 0.0;
   out_9016812017969752156[37] = 0.0;
   out_9016812017969752156[38] = 1.0;
   out_9016812017969752156[39] = 0.0;
   out_9016812017969752156[40] = 0.0;
   out_9016812017969752156[41] = 0.0;
   out_9016812017969752156[42] = 0.0;
   out_9016812017969752156[43] = 0.0;
   out_9016812017969752156[44] = 0.0;
   out_9016812017969752156[45] = 0.0;
   out_9016812017969752156[46] = 0.0;
   out_9016812017969752156[47] = 0.0;
   out_9016812017969752156[48] = 0.0;
   out_9016812017969752156[49] = 0.0;
   out_9016812017969752156[50] = 0.0;
   out_9016812017969752156[51] = 0.0;
   out_9016812017969752156[52] = 0.0;
   out_9016812017969752156[53] = 0.0;
   out_9016812017969752156[54] = 0.0;
   out_9016812017969752156[55] = 0.0;
   out_9016812017969752156[56] = 0.0;
   out_9016812017969752156[57] = 1.0;
   out_9016812017969752156[58] = 0.0;
   out_9016812017969752156[59] = 0.0;
   out_9016812017969752156[60] = 0.0;
   out_9016812017969752156[61] = 0.0;
   out_9016812017969752156[62] = 0.0;
   out_9016812017969752156[63] = 0.0;
   out_9016812017969752156[64] = 0.0;
   out_9016812017969752156[65] = 0.0;
   out_9016812017969752156[66] = 0.0;
   out_9016812017969752156[67] = 0.0;
   out_9016812017969752156[68] = 0.0;
   out_9016812017969752156[69] = 0.0;
   out_9016812017969752156[70] = 0.0;
   out_9016812017969752156[71] = 0.0;
   out_9016812017969752156[72] = 0.0;
   out_9016812017969752156[73] = 0.0;
   out_9016812017969752156[74] = 0.0;
   out_9016812017969752156[75] = 0.0;
   out_9016812017969752156[76] = 1.0;
   out_9016812017969752156[77] = 0.0;
   out_9016812017969752156[78] = 0.0;
   out_9016812017969752156[79] = 0.0;
   out_9016812017969752156[80] = 0.0;
   out_9016812017969752156[81] = 0.0;
   out_9016812017969752156[82] = 0.0;
   out_9016812017969752156[83] = 0.0;
   out_9016812017969752156[84] = 0.0;
   out_9016812017969752156[85] = 0.0;
   out_9016812017969752156[86] = 0.0;
   out_9016812017969752156[87] = 0.0;
   out_9016812017969752156[88] = 0.0;
   out_9016812017969752156[89] = 0.0;
   out_9016812017969752156[90] = 0.0;
   out_9016812017969752156[91] = 0.0;
   out_9016812017969752156[92] = 0.0;
   out_9016812017969752156[93] = 0.0;
   out_9016812017969752156[94] = 0.0;
   out_9016812017969752156[95] = 1.0;
   out_9016812017969752156[96] = 0.0;
   out_9016812017969752156[97] = 0.0;
   out_9016812017969752156[98] = 0.0;
   out_9016812017969752156[99] = 0.0;
   out_9016812017969752156[100] = 0.0;
   out_9016812017969752156[101] = 0.0;
   out_9016812017969752156[102] = 0.0;
   out_9016812017969752156[103] = 0.0;
   out_9016812017969752156[104] = 0.0;
   out_9016812017969752156[105] = 0.0;
   out_9016812017969752156[106] = 0.0;
   out_9016812017969752156[107] = 0.0;
   out_9016812017969752156[108] = 0.0;
   out_9016812017969752156[109] = 0.0;
   out_9016812017969752156[110] = 0.0;
   out_9016812017969752156[111] = 0.0;
   out_9016812017969752156[112] = 0.0;
   out_9016812017969752156[113] = 0.0;
   out_9016812017969752156[114] = 1.0;
   out_9016812017969752156[115] = 0.0;
   out_9016812017969752156[116] = 0.0;
   out_9016812017969752156[117] = 0.0;
   out_9016812017969752156[118] = 0.0;
   out_9016812017969752156[119] = 0.0;
   out_9016812017969752156[120] = 0.0;
   out_9016812017969752156[121] = 0.0;
   out_9016812017969752156[122] = 0.0;
   out_9016812017969752156[123] = 0.0;
   out_9016812017969752156[124] = 0.0;
   out_9016812017969752156[125] = 0.0;
   out_9016812017969752156[126] = 0.0;
   out_9016812017969752156[127] = 0.0;
   out_9016812017969752156[128] = 0.0;
   out_9016812017969752156[129] = 0.0;
   out_9016812017969752156[130] = 0.0;
   out_9016812017969752156[131] = 0.0;
   out_9016812017969752156[132] = 0.0;
   out_9016812017969752156[133] = 1.0;
   out_9016812017969752156[134] = 0.0;
   out_9016812017969752156[135] = 0.0;
   out_9016812017969752156[136] = 0.0;
   out_9016812017969752156[137] = 0.0;
   out_9016812017969752156[138] = 0.0;
   out_9016812017969752156[139] = 0.0;
   out_9016812017969752156[140] = 0.0;
   out_9016812017969752156[141] = 0.0;
   out_9016812017969752156[142] = 0.0;
   out_9016812017969752156[143] = 0.0;
   out_9016812017969752156[144] = 0.0;
   out_9016812017969752156[145] = 0.0;
   out_9016812017969752156[146] = 0.0;
   out_9016812017969752156[147] = 0.0;
   out_9016812017969752156[148] = 0.0;
   out_9016812017969752156[149] = 0.0;
   out_9016812017969752156[150] = 0.0;
   out_9016812017969752156[151] = 0.0;
   out_9016812017969752156[152] = 1.0;
   out_9016812017969752156[153] = 0.0;
   out_9016812017969752156[154] = 0.0;
   out_9016812017969752156[155] = 0.0;
   out_9016812017969752156[156] = 0.0;
   out_9016812017969752156[157] = 0.0;
   out_9016812017969752156[158] = 0.0;
   out_9016812017969752156[159] = 0.0;
   out_9016812017969752156[160] = 0.0;
   out_9016812017969752156[161] = 0.0;
   out_9016812017969752156[162] = 0.0;
   out_9016812017969752156[163] = 0.0;
   out_9016812017969752156[164] = 0.0;
   out_9016812017969752156[165] = 0.0;
   out_9016812017969752156[166] = 0.0;
   out_9016812017969752156[167] = 0.0;
   out_9016812017969752156[168] = 0.0;
   out_9016812017969752156[169] = 0.0;
   out_9016812017969752156[170] = 0.0;
   out_9016812017969752156[171] = 1.0;
   out_9016812017969752156[172] = 0.0;
   out_9016812017969752156[173] = 0.0;
   out_9016812017969752156[174] = 0.0;
   out_9016812017969752156[175] = 0.0;
   out_9016812017969752156[176] = 0.0;
   out_9016812017969752156[177] = 0.0;
   out_9016812017969752156[178] = 0.0;
   out_9016812017969752156[179] = 0.0;
   out_9016812017969752156[180] = 0.0;
   out_9016812017969752156[181] = 0.0;
   out_9016812017969752156[182] = 0.0;
   out_9016812017969752156[183] = 0.0;
   out_9016812017969752156[184] = 0.0;
   out_9016812017969752156[185] = 0.0;
   out_9016812017969752156[186] = 0.0;
   out_9016812017969752156[187] = 0.0;
   out_9016812017969752156[188] = 0.0;
   out_9016812017969752156[189] = 0.0;
   out_9016812017969752156[190] = 1.0;
   out_9016812017969752156[191] = 0.0;
   out_9016812017969752156[192] = 0.0;
   out_9016812017969752156[193] = 0.0;
   out_9016812017969752156[194] = 0.0;
   out_9016812017969752156[195] = 0.0;
   out_9016812017969752156[196] = 0.0;
   out_9016812017969752156[197] = 0.0;
   out_9016812017969752156[198] = 0.0;
   out_9016812017969752156[199] = 0.0;
   out_9016812017969752156[200] = 0.0;
   out_9016812017969752156[201] = 0.0;
   out_9016812017969752156[202] = 0.0;
   out_9016812017969752156[203] = 0.0;
   out_9016812017969752156[204] = 0.0;
   out_9016812017969752156[205] = 0.0;
   out_9016812017969752156[206] = 0.0;
   out_9016812017969752156[207] = 0.0;
   out_9016812017969752156[208] = 0.0;
   out_9016812017969752156[209] = 1.0;
   out_9016812017969752156[210] = 0.0;
   out_9016812017969752156[211] = 0.0;
   out_9016812017969752156[212] = 0.0;
   out_9016812017969752156[213] = 0.0;
   out_9016812017969752156[214] = 0.0;
   out_9016812017969752156[215] = 0.0;
   out_9016812017969752156[216] = 0.0;
   out_9016812017969752156[217] = 0.0;
   out_9016812017969752156[218] = 0.0;
   out_9016812017969752156[219] = 0.0;
   out_9016812017969752156[220] = 0.0;
   out_9016812017969752156[221] = 0.0;
   out_9016812017969752156[222] = 0.0;
   out_9016812017969752156[223] = 0.0;
   out_9016812017969752156[224] = 0.0;
   out_9016812017969752156[225] = 0.0;
   out_9016812017969752156[226] = 0.0;
   out_9016812017969752156[227] = 0.0;
   out_9016812017969752156[228] = 1.0;
   out_9016812017969752156[229] = 0.0;
   out_9016812017969752156[230] = 0.0;
   out_9016812017969752156[231] = 0.0;
   out_9016812017969752156[232] = 0.0;
   out_9016812017969752156[233] = 0.0;
   out_9016812017969752156[234] = 0.0;
   out_9016812017969752156[235] = 0.0;
   out_9016812017969752156[236] = 0.0;
   out_9016812017969752156[237] = 0.0;
   out_9016812017969752156[238] = 0.0;
   out_9016812017969752156[239] = 0.0;
   out_9016812017969752156[240] = 0.0;
   out_9016812017969752156[241] = 0.0;
   out_9016812017969752156[242] = 0.0;
   out_9016812017969752156[243] = 0.0;
   out_9016812017969752156[244] = 0.0;
   out_9016812017969752156[245] = 0.0;
   out_9016812017969752156[246] = 0.0;
   out_9016812017969752156[247] = 1.0;
   out_9016812017969752156[248] = 0.0;
   out_9016812017969752156[249] = 0.0;
   out_9016812017969752156[250] = 0.0;
   out_9016812017969752156[251] = 0.0;
   out_9016812017969752156[252] = 0.0;
   out_9016812017969752156[253] = 0.0;
   out_9016812017969752156[254] = 0.0;
   out_9016812017969752156[255] = 0.0;
   out_9016812017969752156[256] = 0.0;
   out_9016812017969752156[257] = 0.0;
   out_9016812017969752156[258] = 0.0;
   out_9016812017969752156[259] = 0.0;
   out_9016812017969752156[260] = 0.0;
   out_9016812017969752156[261] = 0.0;
   out_9016812017969752156[262] = 0.0;
   out_9016812017969752156[263] = 0.0;
   out_9016812017969752156[264] = 0.0;
   out_9016812017969752156[265] = 0.0;
   out_9016812017969752156[266] = 1.0;
   out_9016812017969752156[267] = 0.0;
   out_9016812017969752156[268] = 0.0;
   out_9016812017969752156[269] = 0.0;
   out_9016812017969752156[270] = 0.0;
   out_9016812017969752156[271] = 0.0;
   out_9016812017969752156[272] = 0.0;
   out_9016812017969752156[273] = 0.0;
   out_9016812017969752156[274] = 0.0;
   out_9016812017969752156[275] = 0.0;
   out_9016812017969752156[276] = 0.0;
   out_9016812017969752156[277] = 0.0;
   out_9016812017969752156[278] = 0.0;
   out_9016812017969752156[279] = 0.0;
   out_9016812017969752156[280] = 0.0;
   out_9016812017969752156[281] = 0.0;
   out_9016812017969752156[282] = 0.0;
   out_9016812017969752156[283] = 0.0;
   out_9016812017969752156[284] = 0.0;
   out_9016812017969752156[285] = 1.0;
   out_9016812017969752156[286] = 0.0;
   out_9016812017969752156[287] = 0.0;
   out_9016812017969752156[288] = 0.0;
   out_9016812017969752156[289] = 0.0;
   out_9016812017969752156[290] = 0.0;
   out_9016812017969752156[291] = 0.0;
   out_9016812017969752156[292] = 0.0;
   out_9016812017969752156[293] = 0.0;
   out_9016812017969752156[294] = 0.0;
   out_9016812017969752156[295] = 0.0;
   out_9016812017969752156[296] = 0.0;
   out_9016812017969752156[297] = 0.0;
   out_9016812017969752156[298] = 0.0;
   out_9016812017969752156[299] = 0.0;
   out_9016812017969752156[300] = 0.0;
   out_9016812017969752156[301] = 0.0;
   out_9016812017969752156[302] = 0.0;
   out_9016812017969752156[303] = 0.0;
   out_9016812017969752156[304] = 1.0;
   out_9016812017969752156[305] = 0.0;
   out_9016812017969752156[306] = 0.0;
   out_9016812017969752156[307] = 0.0;
   out_9016812017969752156[308] = 0.0;
   out_9016812017969752156[309] = 0.0;
   out_9016812017969752156[310] = 0.0;
   out_9016812017969752156[311] = 0.0;
   out_9016812017969752156[312] = 0.0;
   out_9016812017969752156[313] = 0.0;
   out_9016812017969752156[314] = 0.0;
   out_9016812017969752156[315] = 0.0;
   out_9016812017969752156[316] = 0.0;
   out_9016812017969752156[317] = 0.0;
   out_9016812017969752156[318] = 0.0;
   out_9016812017969752156[319] = 0.0;
   out_9016812017969752156[320] = 0.0;
   out_9016812017969752156[321] = 0.0;
   out_9016812017969752156[322] = 0.0;
   out_9016812017969752156[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5314151849166190903) {
   out_5314151849166190903[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5314151849166190903[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5314151849166190903[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5314151849166190903[3] = dt*state[12] + state[3];
   out_5314151849166190903[4] = dt*state[13] + state[4];
   out_5314151849166190903[5] = dt*state[14] + state[5];
   out_5314151849166190903[6] = state[6];
   out_5314151849166190903[7] = state[7];
   out_5314151849166190903[8] = state[8];
   out_5314151849166190903[9] = state[9];
   out_5314151849166190903[10] = state[10];
   out_5314151849166190903[11] = state[11];
   out_5314151849166190903[12] = state[12];
   out_5314151849166190903[13] = state[13];
   out_5314151849166190903[14] = state[14];
   out_5314151849166190903[15] = state[15];
   out_5314151849166190903[16] = state[16];
   out_5314151849166190903[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3978107798910374878) {
   out_3978107798910374878[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3978107798910374878[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3978107798910374878[2] = 0;
   out_3978107798910374878[3] = 0;
   out_3978107798910374878[4] = 0;
   out_3978107798910374878[5] = 0;
   out_3978107798910374878[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3978107798910374878[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3978107798910374878[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3978107798910374878[9] = 0;
   out_3978107798910374878[10] = 0;
   out_3978107798910374878[11] = 0;
   out_3978107798910374878[12] = 0;
   out_3978107798910374878[13] = 0;
   out_3978107798910374878[14] = 0;
   out_3978107798910374878[15] = 0;
   out_3978107798910374878[16] = 0;
   out_3978107798910374878[17] = 0;
   out_3978107798910374878[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3978107798910374878[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3978107798910374878[20] = 0;
   out_3978107798910374878[21] = 0;
   out_3978107798910374878[22] = 0;
   out_3978107798910374878[23] = 0;
   out_3978107798910374878[24] = 0;
   out_3978107798910374878[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3978107798910374878[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3978107798910374878[27] = 0;
   out_3978107798910374878[28] = 0;
   out_3978107798910374878[29] = 0;
   out_3978107798910374878[30] = 0;
   out_3978107798910374878[31] = 0;
   out_3978107798910374878[32] = 0;
   out_3978107798910374878[33] = 0;
   out_3978107798910374878[34] = 0;
   out_3978107798910374878[35] = 0;
   out_3978107798910374878[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3978107798910374878[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3978107798910374878[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3978107798910374878[39] = 0;
   out_3978107798910374878[40] = 0;
   out_3978107798910374878[41] = 0;
   out_3978107798910374878[42] = 0;
   out_3978107798910374878[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3978107798910374878[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3978107798910374878[45] = 0;
   out_3978107798910374878[46] = 0;
   out_3978107798910374878[47] = 0;
   out_3978107798910374878[48] = 0;
   out_3978107798910374878[49] = 0;
   out_3978107798910374878[50] = 0;
   out_3978107798910374878[51] = 0;
   out_3978107798910374878[52] = 0;
   out_3978107798910374878[53] = 0;
   out_3978107798910374878[54] = 0;
   out_3978107798910374878[55] = 0;
   out_3978107798910374878[56] = 0;
   out_3978107798910374878[57] = 1;
   out_3978107798910374878[58] = 0;
   out_3978107798910374878[59] = 0;
   out_3978107798910374878[60] = 0;
   out_3978107798910374878[61] = 0;
   out_3978107798910374878[62] = 0;
   out_3978107798910374878[63] = 0;
   out_3978107798910374878[64] = 0;
   out_3978107798910374878[65] = 0;
   out_3978107798910374878[66] = dt;
   out_3978107798910374878[67] = 0;
   out_3978107798910374878[68] = 0;
   out_3978107798910374878[69] = 0;
   out_3978107798910374878[70] = 0;
   out_3978107798910374878[71] = 0;
   out_3978107798910374878[72] = 0;
   out_3978107798910374878[73] = 0;
   out_3978107798910374878[74] = 0;
   out_3978107798910374878[75] = 0;
   out_3978107798910374878[76] = 1;
   out_3978107798910374878[77] = 0;
   out_3978107798910374878[78] = 0;
   out_3978107798910374878[79] = 0;
   out_3978107798910374878[80] = 0;
   out_3978107798910374878[81] = 0;
   out_3978107798910374878[82] = 0;
   out_3978107798910374878[83] = 0;
   out_3978107798910374878[84] = 0;
   out_3978107798910374878[85] = dt;
   out_3978107798910374878[86] = 0;
   out_3978107798910374878[87] = 0;
   out_3978107798910374878[88] = 0;
   out_3978107798910374878[89] = 0;
   out_3978107798910374878[90] = 0;
   out_3978107798910374878[91] = 0;
   out_3978107798910374878[92] = 0;
   out_3978107798910374878[93] = 0;
   out_3978107798910374878[94] = 0;
   out_3978107798910374878[95] = 1;
   out_3978107798910374878[96] = 0;
   out_3978107798910374878[97] = 0;
   out_3978107798910374878[98] = 0;
   out_3978107798910374878[99] = 0;
   out_3978107798910374878[100] = 0;
   out_3978107798910374878[101] = 0;
   out_3978107798910374878[102] = 0;
   out_3978107798910374878[103] = 0;
   out_3978107798910374878[104] = dt;
   out_3978107798910374878[105] = 0;
   out_3978107798910374878[106] = 0;
   out_3978107798910374878[107] = 0;
   out_3978107798910374878[108] = 0;
   out_3978107798910374878[109] = 0;
   out_3978107798910374878[110] = 0;
   out_3978107798910374878[111] = 0;
   out_3978107798910374878[112] = 0;
   out_3978107798910374878[113] = 0;
   out_3978107798910374878[114] = 1;
   out_3978107798910374878[115] = 0;
   out_3978107798910374878[116] = 0;
   out_3978107798910374878[117] = 0;
   out_3978107798910374878[118] = 0;
   out_3978107798910374878[119] = 0;
   out_3978107798910374878[120] = 0;
   out_3978107798910374878[121] = 0;
   out_3978107798910374878[122] = 0;
   out_3978107798910374878[123] = 0;
   out_3978107798910374878[124] = 0;
   out_3978107798910374878[125] = 0;
   out_3978107798910374878[126] = 0;
   out_3978107798910374878[127] = 0;
   out_3978107798910374878[128] = 0;
   out_3978107798910374878[129] = 0;
   out_3978107798910374878[130] = 0;
   out_3978107798910374878[131] = 0;
   out_3978107798910374878[132] = 0;
   out_3978107798910374878[133] = 1;
   out_3978107798910374878[134] = 0;
   out_3978107798910374878[135] = 0;
   out_3978107798910374878[136] = 0;
   out_3978107798910374878[137] = 0;
   out_3978107798910374878[138] = 0;
   out_3978107798910374878[139] = 0;
   out_3978107798910374878[140] = 0;
   out_3978107798910374878[141] = 0;
   out_3978107798910374878[142] = 0;
   out_3978107798910374878[143] = 0;
   out_3978107798910374878[144] = 0;
   out_3978107798910374878[145] = 0;
   out_3978107798910374878[146] = 0;
   out_3978107798910374878[147] = 0;
   out_3978107798910374878[148] = 0;
   out_3978107798910374878[149] = 0;
   out_3978107798910374878[150] = 0;
   out_3978107798910374878[151] = 0;
   out_3978107798910374878[152] = 1;
   out_3978107798910374878[153] = 0;
   out_3978107798910374878[154] = 0;
   out_3978107798910374878[155] = 0;
   out_3978107798910374878[156] = 0;
   out_3978107798910374878[157] = 0;
   out_3978107798910374878[158] = 0;
   out_3978107798910374878[159] = 0;
   out_3978107798910374878[160] = 0;
   out_3978107798910374878[161] = 0;
   out_3978107798910374878[162] = 0;
   out_3978107798910374878[163] = 0;
   out_3978107798910374878[164] = 0;
   out_3978107798910374878[165] = 0;
   out_3978107798910374878[166] = 0;
   out_3978107798910374878[167] = 0;
   out_3978107798910374878[168] = 0;
   out_3978107798910374878[169] = 0;
   out_3978107798910374878[170] = 0;
   out_3978107798910374878[171] = 1;
   out_3978107798910374878[172] = 0;
   out_3978107798910374878[173] = 0;
   out_3978107798910374878[174] = 0;
   out_3978107798910374878[175] = 0;
   out_3978107798910374878[176] = 0;
   out_3978107798910374878[177] = 0;
   out_3978107798910374878[178] = 0;
   out_3978107798910374878[179] = 0;
   out_3978107798910374878[180] = 0;
   out_3978107798910374878[181] = 0;
   out_3978107798910374878[182] = 0;
   out_3978107798910374878[183] = 0;
   out_3978107798910374878[184] = 0;
   out_3978107798910374878[185] = 0;
   out_3978107798910374878[186] = 0;
   out_3978107798910374878[187] = 0;
   out_3978107798910374878[188] = 0;
   out_3978107798910374878[189] = 0;
   out_3978107798910374878[190] = 1;
   out_3978107798910374878[191] = 0;
   out_3978107798910374878[192] = 0;
   out_3978107798910374878[193] = 0;
   out_3978107798910374878[194] = 0;
   out_3978107798910374878[195] = 0;
   out_3978107798910374878[196] = 0;
   out_3978107798910374878[197] = 0;
   out_3978107798910374878[198] = 0;
   out_3978107798910374878[199] = 0;
   out_3978107798910374878[200] = 0;
   out_3978107798910374878[201] = 0;
   out_3978107798910374878[202] = 0;
   out_3978107798910374878[203] = 0;
   out_3978107798910374878[204] = 0;
   out_3978107798910374878[205] = 0;
   out_3978107798910374878[206] = 0;
   out_3978107798910374878[207] = 0;
   out_3978107798910374878[208] = 0;
   out_3978107798910374878[209] = 1;
   out_3978107798910374878[210] = 0;
   out_3978107798910374878[211] = 0;
   out_3978107798910374878[212] = 0;
   out_3978107798910374878[213] = 0;
   out_3978107798910374878[214] = 0;
   out_3978107798910374878[215] = 0;
   out_3978107798910374878[216] = 0;
   out_3978107798910374878[217] = 0;
   out_3978107798910374878[218] = 0;
   out_3978107798910374878[219] = 0;
   out_3978107798910374878[220] = 0;
   out_3978107798910374878[221] = 0;
   out_3978107798910374878[222] = 0;
   out_3978107798910374878[223] = 0;
   out_3978107798910374878[224] = 0;
   out_3978107798910374878[225] = 0;
   out_3978107798910374878[226] = 0;
   out_3978107798910374878[227] = 0;
   out_3978107798910374878[228] = 1;
   out_3978107798910374878[229] = 0;
   out_3978107798910374878[230] = 0;
   out_3978107798910374878[231] = 0;
   out_3978107798910374878[232] = 0;
   out_3978107798910374878[233] = 0;
   out_3978107798910374878[234] = 0;
   out_3978107798910374878[235] = 0;
   out_3978107798910374878[236] = 0;
   out_3978107798910374878[237] = 0;
   out_3978107798910374878[238] = 0;
   out_3978107798910374878[239] = 0;
   out_3978107798910374878[240] = 0;
   out_3978107798910374878[241] = 0;
   out_3978107798910374878[242] = 0;
   out_3978107798910374878[243] = 0;
   out_3978107798910374878[244] = 0;
   out_3978107798910374878[245] = 0;
   out_3978107798910374878[246] = 0;
   out_3978107798910374878[247] = 1;
   out_3978107798910374878[248] = 0;
   out_3978107798910374878[249] = 0;
   out_3978107798910374878[250] = 0;
   out_3978107798910374878[251] = 0;
   out_3978107798910374878[252] = 0;
   out_3978107798910374878[253] = 0;
   out_3978107798910374878[254] = 0;
   out_3978107798910374878[255] = 0;
   out_3978107798910374878[256] = 0;
   out_3978107798910374878[257] = 0;
   out_3978107798910374878[258] = 0;
   out_3978107798910374878[259] = 0;
   out_3978107798910374878[260] = 0;
   out_3978107798910374878[261] = 0;
   out_3978107798910374878[262] = 0;
   out_3978107798910374878[263] = 0;
   out_3978107798910374878[264] = 0;
   out_3978107798910374878[265] = 0;
   out_3978107798910374878[266] = 1;
   out_3978107798910374878[267] = 0;
   out_3978107798910374878[268] = 0;
   out_3978107798910374878[269] = 0;
   out_3978107798910374878[270] = 0;
   out_3978107798910374878[271] = 0;
   out_3978107798910374878[272] = 0;
   out_3978107798910374878[273] = 0;
   out_3978107798910374878[274] = 0;
   out_3978107798910374878[275] = 0;
   out_3978107798910374878[276] = 0;
   out_3978107798910374878[277] = 0;
   out_3978107798910374878[278] = 0;
   out_3978107798910374878[279] = 0;
   out_3978107798910374878[280] = 0;
   out_3978107798910374878[281] = 0;
   out_3978107798910374878[282] = 0;
   out_3978107798910374878[283] = 0;
   out_3978107798910374878[284] = 0;
   out_3978107798910374878[285] = 1;
   out_3978107798910374878[286] = 0;
   out_3978107798910374878[287] = 0;
   out_3978107798910374878[288] = 0;
   out_3978107798910374878[289] = 0;
   out_3978107798910374878[290] = 0;
   out_3978107798910374878[291] = 0;
   out_3978107798910374878[292] = 0;
   out_3978107798910374878[293] = 0;
   out_3978107798910374878[294] = 0;
   out_3978107798910374878[295] = 0;
   out_3978107798910374878[296] = 0;
   out_3978107798910374878[297] = 0;
   out_3978107798910374878[298] = 0;
   out_3978107798910374878[299] = 0;
   out_3978107798910374878[300] = 0;
   out_3978107798910374878[301] = 0;
   out_3978107798910374878[302] = 0;
   out_3978107798910374878[303] = 0;
   out_3978107798910374878[304] = 1;
   out_3978107798910374878[305] = 0;
   out_3978107798910374878[306] = 0;
   out_3978107798910374878[307] = 0;
   out_3978107798910374878[308] = 0;
   out_3978107798910374878[309] = 0;
   out_3978107798910374878[310] = 0;
   out_3978107798910374878[311] = 0;
   out_3978107798910374878[312] = 0;
   out_3978107798910374878[313] = 0;
   out_3978107798910374878[314] = 0;
   out_3978107798910374878[315] = 0;
   out_3978107798910374878[316] = 0;
   out_3978107798910374878[317] = 0;
   out_3978107798910374878[318] = 0;
   out_3978107798910374878[319] = 0;
   out_3978107798910374878[320] = 0;
   out_3978107798910374878[321] = 0;
   out_3978107798910374878[322] = 0;
   out_3978107798910374878[323] = 1;
}
void h_4(double *state, double *unused, double *out_6702643113920812120) {
   out_6702643113920812120[0] = state[6] + state[9];
   out_6702643113920812120[1] = state[7] + state[10];
   out_6702643113920812120[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1181133811394856104) {
   out_1181133811394856104[0] = 0;
   out_1181133811394856104[1] = 0;
   out_1181133811394856104[2] = 0;
   out_1181133811394856104[3] = 0;
   out_1181133811394856104[4] = 0;
   out_1181133811394856104[5] = 0;
   out_1181133811394856104[6] = 1;
   out_1181133811394856104[7] = 0;
   out_1181133811394856104[8] = 0;
   out_1181133811394856104[9] = 1;
   out_1181133811394856104[10] = 0;
   out_1181133811394856104[11] = 0;
   out_1181133811394856104[12] = 0;
   out_1181133811394856104[13] = 0;
   out_1181133811394856104[14] = 0;
   out_1181133811394856104[15] = 0;
   out_1181133811394856104[16] = 0;
   out_1181133811394856104[17] = 0;
   out_1181133811394856104[18] = 0;
   out_1181133811394856104[19] = 0;
   out_1181133811394856104[20] = 0;
   out_1181133811394856104[21] = 0;
   out_1181133811394856104[22] = 0;
   out_1181133811394856104[23] = 0;
   out_1181133811394856104[24] = 0;
   out_1181133811394856104[25] = 1;
   out_1181133811394856104[26] = 0;
   out_1181133811394856104[27] = 0;
   out_1181133811394856104[28] = 1;
   out_1181133811394856104[29] = 0;
   out_1181133811394856104[30] = 0;
   out_1181133811394856104[31] = 0;
   out_1181133811394856104[32] = 0;
   out_1181133811394856104[33] = 0;
   out_1181133811394856104[34] = 0;
   out_1181133811394856104[35] = 0;
   out_1181133811394856104[36] = 0;
   out_1181133811394856104[37] = 0;
   out_1181133811394856104[38] = 0;
   out_1181133811394856104[39] = 0;
   out_1181133811394856104[40] = 0;
   out_1181133811394856104[41] = 0;
   out_1181133811394856104[42] = 0;
   out_1181133811394856104[43] = 0;
   out_1181133811394856104[44] = 1;
   out_1181133811394856104[45] = 0;
   out_1181133811394856104[46] = 0;
   out_1181133811394856104[47] = 1;
   out_1181133811394856104[48] = 0;
   out_1181133811394856104[49] = 0;
   out_1181133811394856104[50] = 0;
   out_1181133811394856104[51] = 0;
   out_1181133811394856104[52] = 0;
   out_1181133811394856104[53] = 0;
}
void h_10(double *state, double *unused, double *out_329728007611436907) {
   out_329728007611436907[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_329728007611436907[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_329728007611436907[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8047171094370826367) {
   out_8047171094370826367[0] = 0;
   out_8047171094370826367[1] = 9.8100000000000005*cos(state[1]);
   out_8047171094370826367[2] = 0;
   out_8047171094370826367[3] = 0;
   out_8047171094370826367[4] = -state[8];
   out_8047171094370826367[5] = state[7];
   out_8047171094370826367[6] = 0;
   out_8047171094370826367[7] = state[5];
   out_8047171094370826367[8] = -state[4];
   out_8047171094370826367[9] = 0;
   out_8047171094370826367[10] = 0;
   out_8047171094370826367[11] = 0;
   out_8047171094370826367[12] = 1;
   out_8047171094370826367[13] = 0;
   out_8047171094370826367[14] = 0;
   out_8047171094370826367[15] = 1;
   out_8047171094370826367[16] = 0;
   out_8047171094370826367[17] = 0;
   out_8047171094370826367[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8047171094370826367[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8047171094370826367[20] = 0;
   out_8047171094370826367[21] = state[8];
   out_8047171094370826367[22] = 0;
   out_8047171094370826367[23] = -state[6];
   out_8047171094370826367[24] = -state[5];
   out_8047171094370826367[25] = 0;
   out_8047171094370826367[26] = state[3];
   out_8047171094370826367[27] = 0;
   out_8047171094370826367[28] = 0;
   out_8047171094370826367[29] = 0;
   out_8047171094370826367[30] = 0;
   out_8047171094370826367[31] = 1;
   out_8047171094370826367[32] = 0;
   out_8047171094370826367[33] = 0;
   out_8047171094370826367[34] = 1;
   out_8047171094370826367[35] = 0;
   out_8047171094370826367[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8047171094370826367[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8047171094370826367[38] = 0;
   out_8047171094370826367[39] = -state[7];
   out_8047171094370826367[40] = state[6];
   out_8047171094370826367[41] = 0;
   out_8047171094370826367[42] = state[4];
   out_8047171094370826367[43] = -state[3];
   out_8047171094370826367[44] = 0;
   out_8047171094370826367[45] = 0;
   out_8047171094370826367[46] = 0;
   out_8047171094370826367[47] = 0;
   out_8047171094370826367[48] = 0;
   out_8047171094370826367[49] = 0;
   out_8047171094370826367[50] = 1;
   out_8047171094370826367[51] = 0;
   out_8047171094370826367[52] = 0;
   out_8047171094370826367[53] = 1;
}
void h_13(double *state, double *unused, double *out_8195155792174923791) {
   out_8195155792174923791[0] = state[3];
   out_8195155792174923791[1] = state[4];
   out_8195155792174923791[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2031140013937476697) {
   out_2031140013937476697[0] = 0;
   out_2031140013937476697[1] = 0;
   out_2031140013937476697[2] = 0;
   out_2031140013937476697[3] = 1;
   out_2031140013937476697[4] = 0;
   out_2031140013937476697[5] = 0;
   out_2031140013937476697[6] = 0;
   out_2031140013937476697[7] = 0;
   out_2031140013937476697[8] = 0;
   out_2031140013937476697[9] = 0;
   out_2031140013937476697[10] = 0;
   out_2031140013937476697[11] = 0;
   out_2031140013937476697[12] = 0;
   out_2031140013937476697[13] = 0;
   out_2031140013937476697[14] = 0;
   out_2031140013937476697[15] = 0;
   out_2031140013937476697[16] = 0;
   out_2031140013937476697[17] = 0;
   out_2031140013937476697[18] = 0;
   out_2031140013937476697[19] = 0;
   out_2031140013937476697[20] = 0;
   out_2031140013937476697[21] = 0;
   out_2031140013937476697[22] = 1;
   out_2031140013937476697[23] = 0;
   out_2031140013937476697[24] = 0;
   out_2031140013937476697[25] = 0;
   out_2031140013937476697[26] = 0;
   out_2031140013937476697[27] = 0;
   out_2031140013937476697[28] = 0;
   out_2031140013937476697[29] = 0;
   out_2031140013937476697[30] = 0;
   out_2031140013937476697[31] = 0;
   out_2031140013937476697[32] = 0;
   out_2031140013937476697[33] = 0;
   out_2031140013937476697[34] = 0;
   out_2031140013937476697[35] = 0;
   out_2031140013937476697[36] = 0;
   out_2031140013937476697[37] = 0;
   out_2031140013937476697[38] = 0;
   out_2031140013937476697[39] = 0;
   out_2031140013937476697[40] = 0;
   out_2031140013937476697[41] = 1;
   out_2031140013937476697[42] = 0;
   out_2031140013937476697[43] = 0;
   out_2031140013937476697[44] = 0;
   out_2031140013937476697[45] = 0;
   out_2031140013937476697[46] = 0;
   out_2031140013937476697[47] = 0;
   out_2031140013937476697[48] = 0;
   out_2031140013937476697[49] = 0;
   out_2031140013937476697[50] = 0;
   out_2031140013937476697[51] = 0;
   out_2031140013937476697[52] = 0;
   out_2031140013937476697[53] = 0;
}
void h_14(double *state, double *unused, double *out_3839043433562085237) {
   out_3839043433562085237[0] = state[6];
   out_3839043433562085237[1] = state[7];
   out_3839043433562085237[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2782107044944628425) {
   out_2782107044944628425[0] = 0;
   out_2782107044944628425[1] = 0;
   out_2782107044944628425[2] = 0;
   out_2782107044944628425[3] = 0;
   out_2782107044944628425[4] = 0;
   out_2782107044944628425[5] = 0;
   out_2782107044944628425[6] = 1;
   out_2782107044944628425[7] = 0;
   out_2782107044944628425[8] = 0;
   out_2782107044944628425[9] = 0;
   out_2782107044944628425[10] = 0;
   out_2782107044944628425[11] = 0;
   out_2782107044944628425[12] = 0;
   out_2782107044944628425[13] = 0;
   out_2782107044944628425[14] = 0;
   out_2782107044944628425[15] = 0;
   out_2782107044944628425[16] = 0;
   out_2782107044944628425[17] = 0;
   out_2782107044944628425[18] = 0;
   out_2782107044944628425[19] = 0;
   out_2782107044944628425[20] = 0;
   out_2782107044944628425[21] = 0;
   out_2782107044944628425[22] = 0;
   out_2782107044944628425[23] = 0;
   out_2782107044944628425[24] = 0;
   out_2782107044944628425[25] = 1;
   out_2782107044944628425[26] = 0;
   out_2782107044944628425[27] = 0;
   out_2782107044944628425[28] = 0;
   out_2782107044944628425[29] = 0;
   out_2782107044944628425[30] = 0;
   out_2782107044944628425[31] = 0;
   out_2782107044944628425[32] = 0;
   out_2782107044944628425[33] = 0;
   out_2782107044944628425[34] = 0;
   out_2782107044944628425[35] = 0;
   out_2782107044944628425[36] = 0;
   out_2782107044944628425[37] = 0;
   out_2782107044944628425[38] = 0;
   out_2782107044944628425[39] = 0;
   out_2782107044944628425[40] = 0;
   out_2782107044944628425[41] = 0;
   out_2782107044944628425[42] = 0;
   out_2782107044944628425[43] = 0;
   out_2782107044944628425[44] = 1;
   out_2782107044944628425[45] = 0;
   out_2782107044944628425[46] = 0;
   out_2782107044944628425[47] = 0;
   out_2782107044944628425[48] = 0;
   out_2782107044944628425[49] = 0;
   out_2782107044944628425[50] = 0;
   out_2782107044944628425[51] = 0;
   out_2782107044944628425[52] = 0;
   out_2782107044944628425[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_2815596288453817821) {
  err_fun(nom_x, delta_x, out_2815596288453817821);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8761485569796980977) {
  inv_err_fun(nom_x, true_x, out_8761485569796980977);
}
void pose_H_mod_fun(double *state, double *out_9016812017969752156) {
  H_mod_fun(state, out_9016812017969752156);
}
void pose_f_fun(double *state, double dt, double *out_5314151849166190903) {
  f_fun(state,  dt, out_5314151849166190903);
}
void pose_F_fun(double *state, double dt, double *out_3978107798910374878) {
  F_fun(state,  dt, out_3978107798910374878);
}
void pose_h_4(double *state, double *unused, double *out_6702643113920812120) {
  h_4(state, unused, out_6702643113920812120);
}
void pose_H_4(double *state, double *unused, double *out_1181133811394856104) {
  H_4(state, unused, out_1181133811394856104);
}
void pose_h_10(double *state, double *unused, double *out_329728007611436907) {
  h_10(state, unused, out_329728007611436907);
}
void pose_H_10(double *state, double *unused, double *out_8047171094370826367) {
  H_10(state, unused, out_8047171094370826367);
}
void pose_h_13(double *state, double *unused, double *out_8195155792174923791) {
  h_13(state, unused, out_8195155792174923791);
}
void pose_H_13(double *state, double *unused, double *out_2031140013937476697) {
  H_13(state, unused, out_2031140013937476697);
}
void pose_h_14(double *state, double *unused, double *out_3839043433562085237) {
  h_14(state, unused, out_3839043433562085237);
}
void pose_H_14(double *state, double *unused, double *out_2782107044944628425) {
  H_14(state, unused, out_2782107044944628425);
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
