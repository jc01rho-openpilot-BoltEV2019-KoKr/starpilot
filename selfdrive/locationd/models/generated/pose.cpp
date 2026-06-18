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
void err_fun(double *nom_x, double *delta_x, double *out_5135933030950096940) {
   out_5135933030950096940[0] = delta_x[0] + nom_x[0];
   out_5135933030950096940[1] = delta_x[1] + nom_x[1];
   out_5135933030950096940[2] = delta_x[2] + nom_x[2];
   out_5135933030950096940[3] = delta_x[3] + nom_x[3];
   out_5135933030950096940[4] = delta_x[4] + nom_x[4];
   out_5135933030950096940[5] = delta_x[5] + nom_x[5];
   out_5135933030950096940[6] = delta_x[6] + nom_x[6];
   out_5135933030950096940[7] = delta_x[7] + nom_x[7];
   out_5135933030950096940[8] = delta_x[8] + nom_x[8];
   out_5135933030950096940[9] = delta_x[9] + nom_x[9];
   out_5135933030950096940[10] = delta_x[10] + nom_x[10];
   out_5135933030950096940[11] = delta_x[11] + nom_x[11];
   out_5135933030950096940[12] = delta_x[12] + nom_x[12];
   out_5135933030950096940[13] = delta_x[13] + nom_x[13];
   out_5135933030950096940[14] = delta_x[14] + nom_x[14];
   out_5135933030950096940[15] = delta_x[15] + nom_x[15];
   out_5135933030950096940[16] = delta_x[16] + nom_x[16];
   out_5135933030950096940[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4473434694497561565) {
   out_4473434694497561565[0] = -nom_x[0] + true_x[0];
   out_4473434694497561565[1] = -nom_x[1] + true_x[1];
   out_4473434694497561565[2] = -nom_x[2] + true_x[2];
   out_4473434694497561565[3] = -nom_x[3] + true_x[3];
   out_4473434694497561565[4] = -nom_x[4] + true_x[4];
   out_4473434694497561565[5] = -nom_x[5] + true_x[5];
   out_4473434694497561565[6] = -nom_x[6] + true_x[6];
   out_4473434694497561565[7] = -nom_x[7] + true_x[7];
   out_4473434694497561565[8] = -nom_x[8] + true_x[8];
   out_4473434694497561565[9] = -nom_x[9] + true_x[9];
   out_4473434694497561565[10] = -nom_x[10] + true_x[10];
   out_4473434694497561565[11] = -nom_x[11] + true_x[11];
   out_4473434694497561565[12] = -nom_x[12] + true_x[12];
   out_4473434694497561565[13] = -nom_x[13] + true_x[13];
   out_4473434694497561565[14] = -nom_x[14] + true_x[14];
   out_4473434694497561565[15] = -nom_x[15] + true_x[15];
   out_4473434694497561565[16] = -nom_x[16] + true_x[16];
   out_4473434694497561565[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4955206330411314418) {
   out_4955206330411314418[0] = 1.0;
   out_4955206330411314418[1] = 0.0;
   out_4955206330411314418[2] = 0.0;
   out_4955206330411314418[3] = 0.0;
   out_4955206330411314418[4] = 0.0;
   out_4955206330411314418[5] = 0.0;
   out_4955206330411314418[6] = 0.0;
   out_4955206330411314418[7] = 0.0;
   out_4955206330411314418[8] = 0.0;
   out_4955206330411314418[9] = 0.0;
   out_4955206330411314418[10] = 0.0;
   out_4955206330411314418[11] = 0.0;
   out_4955206330411314418[12] = 0.0;
   out_4955206330411314418[13] = 0.0;
   out_4955206330411314418[14] = 0.0;
   out_4955206330411314418[15] = 0.0;
   out_4955206330411314418[16] = 0.0;
   out_4955206330411314418[17] = 0.0;
   out_4955206330411314418[18] = 0.0;
   out_4955206330411314418[19] = 1.0;
   out_4955206330411314418[20] = 0.0;
   out_4955206330411314418[21] = 0.0;
   out_4955206330411314418[22] = 0.0;
   out_4955206330411314418[23] = 0.0;
   out_4955206330411314418[24] = 0.0;
   out_4955206330411314418[25] = 0.0;
   out_4955206330411314418[26] = 0.0;
   out_4955206330411314418[27] = 0.0;
   out_4955206330411314418[28] = 0.0;
   out_4955206330411314418[29] = 0.0;
   out_4955206330411314418[30] = 0.0;
   out_4955206330411314418[31] = 0.0;
   out_4955206330411314418[32] = 0.0;
   out_4955206330411314418[33] = 0.0;
   out_4955206330411314418[34] = 0.0;
   out_4955206330411314418[35] = 0.0;
   out_4955206330411314418[36] = 0.0;
   out_4955206330411314418[37] = 0.0;
   out_4955206330411314418[38] = 1.0;
   out_4955206330411314418[39] = 0.0;
   out_4955206330411314418[40] = 0.0;
   out_4955206330411314418[41] = 0.0;
   out_4955206330411314418[42] = 0.0;
   out_4955206330411314418[43] = 0.0;
   out_4955206330411314418[44] = 0.0;
   out_4955206330411314418[45] = 0.0;
   out_4955206330411314418[46] = 0.0;
   out_4955206330411314418[47] = 0.0;
   out_4955206330411314418[48] = 0.0;
   out_4955206330411314418[49] = 0.0;
   out_4955206330411314418[50] = 0.0;
   out_4955206330411314418[51] = 0.0;
   out_4955206330411314418[52] = 0.0;
   out_4955206330411314418[53] = 0.0;
   out_4955206330411314418[54] = 0.0;
   out_4955206330411314418[55] = 0.0;
   out_4955206330411314418[56] = 0.0;
   out_4955206330411314418[57] = 1.0;
   out_4955206330411314418[58] = 0.0;
   out_4955206330411314418[59] = 0.0;
   out_4955206330411314418[60] = 0.0;
   out_4955206330411314418[61] = 0.0;
   out_4955206330411314418[62] = 0.0;
   out_4955206330411314418[63] = 0.0;
   out_4955206330411314418[64] = 0.0;
   out_4955206330411314418[65] = 0.0;
   out_4955206330411314418[66] = 0.0;
   out_4955206330411314418[67] = 0.0;
   out_4955206330411314418[68] = 0.0;
   out_4955206330411314418[69] = 0.0;
   out_4955206330411314418[70] = 0.0;
   out_4955206330411314418[71] = 0.0;
   out_4955206330411314418[72] = 0.0;
   out_4955206330411314418[73] = 0.0;
   out_4955206330411314418[74] = 0.0;
   out_4955206330411314418[75] = 0.0;
   out_4955206330411314418[76] = 1.0;
   out_4955206330411314418[77] = 0.0;
   out_4955206330411314418[78] = 0.0;
   out_4955206330411314418[79] = 0.0;
   out_4955206330411314418[80] = 0.0;
   out_4955206330411314418[81] = 0.0;
   out_4955206330411314418[82] = 0.0;
   out_4955206330411314418[83] = 0.0;
   out_4955206330411314418[84] = 0.0;
   out_4955206330411314418[85] = 0.0;
   out_4955206330411314418[86] = 0.0;
   out_4955206330411314418[87] = 0.0;
   out_4955206330411314418[88] = 0.0;
   out_4955206330411314418[89] = 0.0;
   out_4955206330411314418[90] = 0.0;
   out_4955206330411314418[91] = 0.0;
   out_4955206330411314418[92] = 0.0;
   out_4955206330411314418[93] = 0.0;
   out_4955206330411314418[94] = 0.0;
   out_4955206330411314418[95] = 1.0;
   out_4955206330411314418[96] = 0.0;
   out_4955206330411314418[97] = 0.0;
   out_4955206330411314418[98] = 0.0;
   out_4955206330411314418[99] = 0.0;
   out_4955206330411314418[100] = 0.0;
   out_4955206330411314418[101] = 0.0;
   out_4955206330411314418[102] = 0.0;
   out_4955206330411314418[103] = 0.0;
   out_4955206330411314418[104] = 0.0;
   out_4955206330411314418[105] = 0.0;
   out_4955206330411314418[106] = 0.0;
   out_4955206330411314418[107] = 0.0;
   out_4955206330411314418[108] = 0.0;
   out_4955206330411314418[109] = 0.0;
   out_4955206330411314418[110] = 0.0;
   out_4955206330411314418[111] = 0.0;
   out_4955206330411314418[112] = 0.0;
   out_4955206330411314418[113] = 0.0;
   out_4955206330411314418[114] = 1.0;
   out_4955206330411314418[115] = 0.0;
   out_4955206330411314418[116] = 0.0;
   out_4955206330411314418[117] = 0.0;
   out_4955206330411314418[118] = 0.0;
   out_4955206330411314418[119] = 0.0;
   out_4955206330411314418[120] = 0.0;
   out_4955206330411314418[121] = 0.0;
   out_4955206330411314418[122] = 0.0;
   out_4955206330411314418[123] = 0.0;
   out_4955206330411314418[124] = 0.0;
   out_4955206330411314418[125] = 0.0;
   out_4955206330411314418[126] = 0.0;
   out_4955206330411314418[127] = 0.0;
   out_4955206330411314418[128] = 0.0;
   out_4955206330411314418[129] = 0.0;
   out_4955206330411314418[130] = 0.0;
   out_4955206330411314418[131] = 0.0;
   out_4955206330411314418[132] = 0.0;
   out_4955206330411314418[133] = 1.0;
   out_4955206330411314418[134] = 0.0;
   out_4955206330411314418[135] = 0.0;
   out_4955206330411314418[136] = 0.0;
   out_4955206330411314418[137] = 0.0;
   out_4955206330411314418[138] = 0.0;
   out_4955206330411314418[139] = 0.0;
   out_4955206330411314418[140] = 0.0;
   out_4955206330411314418[141] = 0.0;
   out_4955206330411314418[142] = 0.0;
   out_4955206330411314418[143] = 0.0;
   out_4955206330411314418[144] = 0.0;
   out_4955206330411314418[145] = 0.0;
   out_4955206330411314418[146] = 0.0;
   out_4955206330411314418[147] = 0.0;
   out_4955206330411314418[148] = 0.0;
   out_4955206330411314418[149] = 0.0;
   out_4955206330411314418[150] = 0.0;
   out_4955206330411314418[151] = 0.0;
   out_4955206330411314418[152] = 1.0;
   out_4955206330411314418[153] = 0.0;
   out_4955206330411314418[154] = 0.0;
   out_4955206330411314418[155] = 0.0;
   out_4955206330411314418[156] = 0.0;
   out_4955206330411314418[157] = 0.0;
   out_4955206330411314418[158] = 0.0;
   out_4955206330411314418[159] = 0.0;
   out_4955206330411314418[160] = 0.0;
   out_4955206330411314418[161] = 0.0;
   out_4955206330411314418[162] = 0.0;
   out_4955206330411314418[163] = 0.0;
   out_4955206330411314418[164] = 0.0;
   out_4955206330411314418[165] = 0.0;
   out_4955206330411314418[166] = 0.0;
   out_4955206330411314418[167] = 0.0;
   out_4955206330411314418[168] = 0.0;
   out_4955206330411314418[169] = 0.0;
   out_4955206330411314418[170] = 0.0;
   out_4955206330411314418[171] = 1.0;
   out_4955206330411314418[172] = 0.0;
   out_4955206330411314418[173] = 0.0;
   out_4955206330411314418[174] = 0.0;
   out_4955206330411314418[175] = 0.0;
   out_4955206330411314418[176] = 0.0;
   out_4955206330411314418[177] = 0.0;
   out_4955206330411314418[178] = 0.0;
   out_4955206330411314418[179] = 0.0;
   out_4955206330411314418[180] = 0.0;
   out_4955206330411314418[181] = 0.0;
   out_4955206330411314418[182] = 0.0;
   out_4955206330411314418[183] = 0.0;
   out_4955206330411314418[184] = 0.0;
   out_4955206330411314418[185] = 0.0;
   out_4955206330411314418[186] = 0.0;
   out_4955206330411314418[187] = 0.0;
   out_4955206330411314418[188] = 0.0;
   out_4955206330411314418[189] = 0.0;
   out_4955206330411314418[190] = 1.0;
   out_4955206330411314418[191] = 0.0;
   out_4955206330411314418[192] = 0.0;
   out_4955206330411314418[193] = 0.0;
   out_4955206330411314418[194] = 0.0;
   out_4955206330411314418[195] = 0.0;
   out_4955206330411314418[196] = 0.0;
   out_4955206330411314418[197] = 0.0;
   out_4955206330411314418[198] = 0.0;
   out_4955206330411314418[199] = 0.0;
   out_4955206330411314418[200] = 0.0;
   out_4955206330411314418[201] = 0.0;
   out_4955206330411314418[202] = 0.0;
   out_4955206330411314418[203] = 0.0;
   out_4955206330411314418[204] = 0.0;
   out_4955206330411314418[205] = 0.0;
   out_4955206330411314418[206] = 0.0;
   out_4955206330411314418[207] = 0.0;
   out_4955206330411314418[208] = 0.0;
   out_4955206330411314418[209] = 1.0;
   out_4955206330411314418[210] = 0.0;
   out_4955206330411314418[211] = 0.0;
   out_4955206330411314418[212] = 0.0;
   out_4955206330411314418[213] = 0.0;
   out_4955206330411314418[214] = 0.0;
   out_4955206330411314418[215] = 0.0;
   out_4955206330411314418[216] = 0.0;
   out_4955206330411314418[217] = 0.0;
   out_4955206330411314418[218] = 0.0;
   out_4955206330411314418[219] = 0.0;
   out_4955206330411314418[220] = 0.0;
   out_4955206330411314418[221] = 0.0;
   out_4955206330411314418[222] = 0.0;
   out_4955206330411314418[223] = 0.0;
   out_4955206330411314418[224] = 0.0;
   out_4955206330411314418[225] = 0.0;
   out_4955206330411314418[226] = 0.0;
   out_4955206330411314418[227] = 0.0;
   out_4955206330411314418[228] = 1.0;
   out_4955206330411314418[229] = 0.0;
   out_4955206330411314418[230] = 0.0;
   out_4955206330411314418[231] = 0.0;
   out_4955206330411314418[232] = 0.0;
   out_4955206330411314418[233] = 0.0;
   out_4955206330411314418[234] = 0.0;
   out_4955206330411314418[235] = 0.0;
   out_4955206330411314418[236] = 0.0;
   out_4955206330411314418[237] = 0.0;
   out_4955206330411314418[238] = 0.0;
   out_4955206330411314418[239] = 0.0;
   out_4955206330411314418[240] = 0.0;
   out_4955206330411314418[241] = 0.0;
   out_4955206330411314418[242] = 0.0;
   out_4955206330411314418[243] = 0.0;
   out_4955206330411314418[244] = 0.0;
   out_4955206330411314418[245] = 0.0;
   out_4955206330411314418[246] = 0.0;
   out_4955206330411314418[247] = 1.0;
   out_4955206330411314418[248] = 0.0;
   out_4955206330411314418[249] = 0.0;
   out_4955206330411314418[250] = 0.0;
   out_4955206330411314418[251] = 0.0;
   out_4955206330411314418[252] = 0.0;
   out_4955206330411314418[253] = 0.0;
   out_4955206330411314418[254] = 0.0;
   out_4955206330411314418[255] = 0.0;
   out_4955206330411314418[256] = 0.0;
   out_4955206330411314418[257] = 0.0;
   out_4955206330411314418[258] = 0.0;
   out_4955206330411314418[259] = 0.0;
   out_4955206330411314418[260] = 0.0;
   out_4955206330411314418[261] = 0.0;
   out_4955206330411314418[262] = 0.0;
   out_4955206330411314418[263] = 0.0;
   out_4955206330411314418[264] = 0.0;
   out_4955206330411314418[265] = 0.0;
   out_4955206330411314418[266] = 1.0;
   out_4955206330411314418[267] = 0.0;
   out_4955206330411314418[268] = 0.0;
   out_4955206330411314418[269] = 0.0;
   out_4955206330411314418[270] = 0.0;
   out_4955206330411314418[271] = 0.0;
   out_4955206330411314418[272] = 0.0;
   out_4955206330411314418[273] = 0.0;
   out_4955206330411314418[274] = 0.0;
   out_4955206330411314418[275] = 0.0;
   out_4955206330411314418[276] = 0.0;
   out_4955206330411314418[277] = 0.0;
   out_4955206330411314418[278] = 0.0;
   out_4955206330411314418[279] = 0.0;
   out_4955206330411314418[280] = 0.0;
   out_4955206330411314418[281] = 0.0;
   out_4955206330411314418[282] = 0.0;
   out_4955206330411314418[283] = 0.0;
   out_4955206330411314418[284] = 0.0;
   out_4955206330411314418[285] = 1.0;
   out_4955206330411314418[286] = 0.0;
   out_4955206330411314418[287] = 0.0;
   out_4955206330411314418[288] = 0.0;
   out_4955206330411314418[289] = 0.0;
   out_4955206330411314418[290] = 0.0;
   out_4955206330411314418[291] = 0.0;
   out_4955206330411314418[292] = 0.0;
   out_4955206330411314418[293] = 0.0;
   out_4955206330411314418[294] = 0.0;
   out_4955206330411314418[295] = 0.0;
   out_4955206330411314418[296] = 0.0;
   out_4955206330411314418[297] = 0.0;
   out_4955206330411314418[298] = 0.0;
   out_4955206330411314418[299] = 0.0;
   out_4955206330411314418[300] = 0.0;
   out_4955206330411314418[301] = 0.0;
   out_4955206330411314418[302] = 0.0;
   out_4955206330411314418[303] = 0.0;
   out_4955206330411314418[304] = 1.0;
   out_4955206330411314418[305] = 0.0;
   out_4955206330411314418[306] = 0.0;
   out_4955206330411314418[307] = 0.0;
   out_4955206330411314418[308] = 0.0;
   out_4955206330411314418[309] = 0.0;
   out_4955206330411314418[310] = 0.0;
   out_4955206330411314418[311] = 0.0;
   out_4955206330411314418[312] = 0.0;
   out_4955206330411314418[313] = 0.0;
   out_4955206330411314418[314] = 0.0;
   out_4955206330411314418[315] = 0.0;
   out_4955206330411314418[316] = 0.0;
   out_4955206330411314418[317] = 0.0;
   out_4955206330411314418[318] = 0.0;
   out_4955206330411314418[319] = 0.0;
   out_4955206330411314418[320] = 0.0;
   out_4955206330411314418[321] = 0.0;
   out_4955206330411314418[322] = 0.0;
   out_4955206330411314418[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1052805527796842003) {
   out_1052805527796842003[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1052805527796842003[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1052805527796842003[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1052805527796842003[3] = dt*state[12] + state[3];
   out_1052805527796842003[4] = dt*state[13] + state[4];
   out_1052805527796842003[5] = dt*state[14] + state[5];
   out_1052805527796842003[6] = state[6];
   out_1052805527796842003[7] = state[7];
   out_1052805527796842003[8] = state[8];
   out_1052805527796842003[9] = state[9];
   out_1052805527796842003[10] = state[10];
   out_1052805527796842003[11] = state[11];
   out_1052805527796842003[12] = state[12];
   out_1052805527796842003[13] = state[13];
   out_1052805527796842003[14] = state[14];
   out_1052805527796842003[15] = state[15];
   out_1052805527796842003[16] = state[16];
   out_1052805527796842003[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5871869036335399812) {
   out_5871869036335399812[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5871869036335399812[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5871869036335399812[2] = 0;
   out_5871869036335399812[3] = 0;
   out_5871869036335399812[4] = 0;
   out_5871869036335399812[5] = 0;
   out_5871869036335399812[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5871869036335399812[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5871869036335399812[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5871869036335399812[9] = 0;
   out_5871869036335399812[10] = 0;
   out_5871869036335399812[11] = 0;
   out_5871869036335399812[12] = 0;
   out_5871869036335399812[13] = 0;
   out_5871869036335399812[14] = 0;
   out_5871869036335399812[15] = 0;
   out_5871869036335399812[16] = 0;
   out_5871869036335399812[17] = 0;
   out_5871869036335399812[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5871869036335399812[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5871869036335399812[20] = 0;
   out_5871869036335399812[21] = 0;
   out_5871869036335399812[22] = 0;
   out_5871869036335399812[23] = 0;
   out_5871869036335399812[24] = 0;
   out_5871869036335399812[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5871869036335399812[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5871869036335399812[27] = 0;
   out_5871869036335399812[28] = 0;
   out_5871869036335399812[29] = 0;
   out_5871869036335399812[30] = 0;
   out_5871869036335399812[31] = 0;
   out_5871869036335399812[32] = 0;
   out_5871869036335399812[33] = 0;
   out_5871869036335399812[34] = 0;
   out_5871869036335399812[35] = 0;
   out_5871869036335399812[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5871869036335399812[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5871869036335399812[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5871869036335399812[39] = 0;
   out_5871869036335399812[40] = 0;
   out_5871869036335399812[41] = 0;
   out_5871869036335399812[42] = 0;
   out_5871869036335399812[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5871869036335399812[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5871869036335399812[45] = 0;
   out_5871869036335399812[46] = 0;
   out_5871869036335399812[47] = 0;
   out_5871869036335399812[48] = 0;
   out_5871869036335399812[49] = 0;
   out_5871869036335399812[50] = 0;
   out_5871869036335399812[51] = 0;
   out_5871869036335399812[52] = 0;
   out_5871869036335399812[53] = 0;
   out_5871869036335399812[54] = 0;
   out_5871869036335399812[55] = 0;
   out_5871869036335399812[56] = 0;
   out_5871869036335399812[57] = 1;
   out_5871869036335399812[58] = 0;
   out_5871869036335399812[59] = 0;
   out_5871869036335399812[60] = 0;
   out_5871869036335399812[61] = 0;
   out_5871869036335399812[62] = 0;
   out_5871869036335399812[63] = 0;
   out_5871869036335399812[64] = 0;
   out_5871869036335399812[65] = 0;
   out_5871869036335399812[66] = dt;
   out_5871869036335399812[67] = 0;
   out_5871869036335399812[68] = 0;
   out_5871869036335399812[69] = 0;
   out_5871869036335399812[70] = 0;
   out_5871869036335399812[71] = 0;
   out_5871869036335399812[72] = 0;
   out_5871869036335399812[73] = 0;
   out_5871869036335399812[74] = 0;
   out_5871869036335399812[75] = 0;
   out_5871869036335399812[76] = 1;
   out_5871869036335399812[77] = 0;
   out_5871869036335399812[78] = 0;
   out_5871869036335399812[79] = 0;
   out_5871869036335399812[80] = 0;
   out_5871869036335399812[81] = 0;
   out_5871869036335399812[82] = 0;
   out_5871869036335399812[83] = 0;
   out_5871869036335399812[84] = 0;
   out_5871869036335399812[85] = dt;
   out_5871869036335399812[86] = 0;
   out_5871869036335399812[87] = 0;
   out_5871869036335399812[88] = 0;
   out_5871869036335399812[89] = 0;
   out_5871869036335399812[90] = 0;
   out_5871869036335399812[91] = 0;
   out_5871869036335399812[92] = 0;
   out_5871869036335399812[93] = 0;
   out_5871869036335399812[94] = 0;
   out_5871869036335399812[95] = 1;
   out_5871869036335399812[96] = 0;
   out_5871869036335399812[97] = 0;
   out_5871869036335399812[98] = 0;
   out_5871869036335399812[99] = 0;
   out_5871869036335399812[100] = 0;
   out_5871869036335399812[101] = 0;
   out_5871869036335399812[102] = 0;
   out_5871869036335399812[103] = 0;
   out_5871869036335399812[104] = dt;
   out_5871869036335399812[105] = 0;
   out_5871869036335399812[106] = 0;
   out_5871869036335399812[107] = 0;
   out_5871869036335399812[108] = 0;
   out_5871869036335399812[109] = 0;
   out_5871869036335399812[110] = 0;
   out_5871869036335399812[111] = 0;
   out_5871869036335399812[112] = 0;
   out_5871869036335399812[113] = 0;
   out_5871869036335399812[114] = 1;
   out_5871869036335399812[115] = 0;
   out_5871869036335399812[116] = 0;
   out_5871869036335399812[117] = 0;
   out_5871869036335399812[118] = 0;
   out_5871869036335399812[119] = 0;
   out_5871869036335399812[120] = 0;
   out_5871869036335399812[121] = 0;
   out_5871869036335399812[122] = 0;
   out_5871869036335399812[123] = 0;
   out_5871869036335399812[124] = 0;
   out_5871869036335399812[125] = 0;
   out_5871869036335399812[126] = 0;
   out_5871869036335399812[127] = 0;
   out_5871869036335399812[128] = 0;
   out_5871869036335399812[129] = 0;
   out_5871869036335399812[130] = 0;
   out_5871869036335399812[131] = 0;
   out_5871869036335399812[132] = 0;
   out_5871869036335399812[133] = 1;
   out_5871869036335399812[134] = 0;
   out_5871869036335399812[135] = 0;
   out_5871869036335399812[136] = 0;
   out_5871869036335399812[137] = 0;
   out_5871869036335399812[138] = 0;
   out_5871869036335399812[139] = 0;
   out_5871869036335399812[140] = 0;
   out_5871869036335399812[141] = 0;
   out_5871869036335399812[142] = 0;
   out_5871869036335399812[143] = 0;
   out_5871869036335399812[144] = 0;
   out_5871869036335399812[145] = 0;
   out_5871869036335399812[146] = 0;
   out_5871869036335399812[147] = 0;
   out_5871869036335399812[148] = 0;
   out_5871869036335399812[149] = 0;
   out_5871869036335399812[150] = 0;
   out_5871869036335399812[151] = 0;
   out_5871869036335399812[152] = 1;
   out_5871869036335399812[153] = 0;
   out_5871869036335399812[154] = 0;
   out_5871869036335399812[155] = 0;
   out_5871869036335399812[156] = 0;
   out_5871869036335399812[157] = 0;
   out_5871869036335399812[158] = 0;
   out_5871869036335399812[159] = 0;
   out_5871869036335399812[160] = 0;
   out_5871869036335399812[161] = 0;
   out_5871869036335399812[162] = 0;
   out_5871869036335399812[163] = 0;
   out_5871869036335399812[164] = 0;
   out_5871869036335399812[165] = 0;
   out_5871869036335399812[166] = 0;
   out_5871869036335399812[167] = 0;
   out_5871869036335399812[168] = 0;
   out_5871869036335399812[169] = 0;
   out_5871869036335399812[170] = 0;
   out_5871869036335399812[171] = 1;
   out_5871869036335399812[172] = 0;
   out_5871869036335399812[173] = 0;
   out_5871869036335399812[174] = 0;
   out_5871869036335399812[175] = 0;
   out_5871869036335399812[176] = 0;
   out_5871869036335399812[177] = 0;
   out_5871869036335399812[178] = 0;
   out_5871869036335399812[179] = 0;
   out_5871869036335399812[180] = 0;
   out_5871869036335399812[181] = 0;
   out_5871869036335399812[182] = 0;
   out_5871869036335399812[183] = 0;
   out_5871869036335399812[184] = 0;
   out_5871869036335399812[185] = 0;
   out_5871869036335399812[186] = 0;
   out_5871869036335399812[187] = 0;
   out_5871869036335399812[188] = 0;
   out_5871869036335399812[189] = 0;
   out_5871869036335399812[190] = 1;
   out_5871869036335399812[191] = 0;
   out_5871869036335399812[192] = 0;
   out_5871869036335399812[193] = 0;
   out_5871869036335399812[194] = 0;
   out_5871869036335399812[195] = 0;
   out_5871869036335399812[196] = 0;
   out_5871869036335399812[197] = 0;
   out_5871869036335399812[198] = 0;
   out_5871869036335399812[199] = 0;
   out_5871869036335399812[200] = 0;
   out_5871869036335399812[201] = 0;
   out_5871869036335399812[202] = 0;
   out_5871869036335399812[203] = 0;
   out_5871869036335399812[204] = 0;
   out_5871869036335399812[205] = 0;
   out_5871869036335399812[206] = 0;
   out_5871869036335399812[207] = 0;
   out_5871869036335399812[208] = 0;
   out_5871869036335399812[209] = 1;
   out_5871869036335399812[210] = 0;
   out_5871869036335399812[211] = 0;
   out_5871869036335399812[212] = 0;
   out_5871869036335399812[213] = 0;
   out_5871869036335399812[214] = 0;
   out_5871869036335399812[215] = 0;
   out_5871869036335399812[216] = 0;
   out_5871869036335399812[217] = 0;
   out_5871869036335399812[218] = 0;
   out_5871869036335399812[219] = 0;
   out_5871869036335399812[220] = 0;
   out_5871869036335399812[221] = 0;
   out_5871869036335399812[222] = 0;
   out_5871869036335399812[223] = 0;
   out_5871869036335399812[224] = 0;
   out_5871869036335399812[225] = 0;
   out_5871869036335399812[226] = 0;
   out_5871869036335399812[227] = 0;
   out_5871869036335399812[228] = 1;
   out_5871869036335399812[229] = 0;
   out_5871869036335399812[230] = 0;
   out_5871869036335399812[231] = 0;
   out_5871869036335399812[232] = 0;
   out_5871869036335399812[233] = 0;
   out_5871869036335399812[234] = 0;
   out_5871869036335399812[235] = 0;
   out_5871869036335399812[236] = 0;
   out_5871869036335399812[237] = 0;
   out_5871869036335399812[238] = 0;
   out_5871869036335399812[239] = 0;
   out_5871869036335399812[240] = 0;
   out_5871869036335399812[241] = 0;
   out_5871869036335399812[242] = 0;
   out_5871869036335399812[243] = 0;
   out_5871869036335399812[244] = 0;
   out_5871869036335399812[245] = 0;
   out_5871869036335399812[246] = 0;
   out_5871869036335399812[247] = 1;
   out_5871869036335399812[248] = 0;
   out_5871869036335399812[249] = 0;
   out_5871869036335399812[250] = 0;
   out_5871869036335399812[251] = 0;
   out_5871869036335399812[252] = 0;
   out_5871869036335399812[253] = 0;
   out_5871869036335399812[254] = 0;
   out_5871869036335399812[255] = 0;
   out_5871869036335399812[256] = 0;
   out_5871869036335399812[257] = 0;
   out_5871869036335399812[258] = 0;
   out_5871869036335399812[259] = 0;
   out_5871869036335399812[260] = 0;
   out_5871869036335399812[261] = 0;
   out_5871869036335399812[262] = 0;
   out_5871869036335399812[263] = 0;
   out_5871869036335399812[264] = 0;
   out_5871869036335399812[265] = 0;
   out_5871869036335399812[266] = 1;
   out_5871869036335399812[267] = 0;
   out_5871869036335399812[268] = 0;
   out_5871869036335399812[269] = 0;
   out_5871869036335399812[270] = 0;
   out_5871869036335399812[271] = 0;
   out_5871869036335399812[272] = 0;
   out_5871869036335399812[273] = 0;
   out_5871869036335399812[274] = 0;
   out_5871869036335399812[275] = 0;
   out_5871869036335399812[276] = 0;
   out_5871869036335399812[277] = 0;
   out_5871869036335399812[278] = 0;
   out_5871869036335399812[279] = 0;
   out_5871869036335399812[280] = 0;
   out_5871869036335399812[281] = 0;
   out_5871869036335399812[282] = 0;
   out_5871869036335399812[283] = 0;
   out_5871869036335399812[284] = 0;
   out_5871869036335399812[285] = 1;
   out_5871869036335399812[286] = 0;
   out_5871869036335399812[287] = 0;
   out_5871869036335399812[288] = 0;
   out_5871869036335399812[289] = 0;
   out_5871869036335399812[290] = 0;
   out_5871869036335399812[291] = 0;
   out_5871869036335399812[292] = 0;
   out_5871869036335399812[293] = 0;
   out_5871869036335399812[294] = 0;
   out_5871869036335399812[295] = 0;
   out_5871869036335399812[296] = 0;
   out_5871869036335399812[297] = 0;
   out_5871869036335399812[298] = 0;
   out_5871869036335399812[299] = 0;
   out_5871869036335399812[300] = 0;
   out_5871869036335399812[301] = 0;
   out_5871869036335399812[302] = 0;
   out_5871869036335399812[303] = 0;
   out_5871869036335399812[304] = 1;
   out_5871869036335399812[305] = 0;
   out_5871869036335399812[306] = 0;
   out_5871869036335399812[307] = 0;
   out_5871869036335399812[308] = 0;
   out_5871869036335399812[309] = 0;
   out_5871869036335399812[310] = 0;
   out_5871869036335399812[311] = 0;
   out_5871869036335399812[312] = 0;
   out_5871869036335399812[313] = 0;
   out_5871869036335399812[314] = 0;
   out_5871869036335399812[315] = 0;
   out_5871869036335399812[316] = 0;
   out_5871869036335399812[317] = 0;
   out_5871869036335399812[318] = 0;
   out_5871869036335399812[319] = 0;
   out_5871869036335399812[320] = 0;
   out_5871869036335399812[321] = 0;
   out_5871869036335399812[322] = 0;
   out_5871869036335399812[323] = 1;
}
void h_4(double *state, double *unused, double *out_921118668651624411) {
   out_921118668651624411[0] = state[6] + state[9];
   out_921118668651624411[1] = state[7] + state[10];
   out_921118668651624411[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3989155335646506924) {
   out_3989155335646506924[0] = 0;
   out_3989155335646506924[1] = 0;
   out_3989155335646506924[2] = 0;
   out_3989155335646506924[3] = 0;
   out_3989155335646506924[4] = 0;
   out_3989155335646506924[5] = 0;
   out_3989155335646506924[6] = 1;
   out_3989155335646506924[7] = 0;
   out_3989155335646506924[8] = 0;
   out_3989155335646506924[9] = 1;
   out_3989155335646506924[10] = 0;
   out_3989155335646506924[11] = 0;
   out_3989155335646506924[12] = 0;
   out_3989155335646506924[13] = 0;
   out_3989155335646506924[14] = 0;
   out_3989155335646506924[15] = 0;
   out_3989155335646506924[16] = 0;
   out_3989155335646506924[17] = 0;
   out_3989155335646506924[18] = 0;
   out_3989155335646506924[19] = 0;
   out_3989155335646506924[20] = 0;
   out_3989155335646506924[21] = 0;
   out_3989155335646506924[22] = 0;
   out_3989155335646506924[23] = 0;
   out_3989155335646506924[24] = 0;
   out_3989155335646506924[25] = 1;
   out_3989155335646506924[26] = 0;
   out_3989155335646506924[27] = 0;
   out_3989155335646506924[28] = 1;
   out_3989155335646506924[29] = 0;
   out_3989155335646506924[30] = 0;
   out_3989155335646506924[31] = 0;
   out_3989155335646506924[32] = 0;
   out_3989155335646506924[33] = 0;
   out_3989155335646506924[34] = 0;
   out_3989155335646506924[35] = 0;
   out_3989155335646506924[36] = 0;
   out_3989155335646506924[37] = 0;
   out_3989155335646506924[38] = 0;
   out_3989155335646506924[39] = 0;
   out_3989155335646506924[40] = 0;
   out_3989155335646506924[41] = 0;
   out_3989155335646506924[42] = 0;
   out_3989155335646506924[43] = 0;
   out_3989155335646506924[44] = 1;
   out_3989155335646506924[45] = 0;
   out_3989155335646506924[46] = 0;
   out_3989155335646506924[47] = 1;
   out_3989155335646506924[48] = 0;
   out_3989155335646506924[49] = 0;
   out_3989155335646506924[50] = 0;
   out_3989155335646506924[51] = 0;
   out_3989155335646506924[52] = 0;
   out_3989155335646506924[53] = 0;
}
void h_10(double *state, double *unused, double *out_8738369372345178390) {
   out_8738369372345178390[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8738369372345178390[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8738369372345178390[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2875729590105375124) {
   out_2875729590105375124[0] = 0;
   out_2875729590105375124[1] = 9.8100000000000005*cos(state[1]);
   out_2875729590105375124[2] = 0;
   out_2875729590105375124[3] = 0;
   out_2875729590105375124[4] = -state[8];
   out_2875729590105375124[5] = state[7];
   out_2875729590105375124[6] = 0;
   out_2875729590105375124[7] = state[5];
   out_2875729590105375124[8] = -state[4];
   out_2875729590105375124[9] = 0;
   out_2875729590105375124[10] = 0;
   out_2875729590105375124[11] = 0;
   out_2875729590105375124[12] = 1;
   out_2875729590105375124[13] = 0;
   out_2875729590105375124[14] = 0;
   out_2875729590105375124[15] = 1;
   out_2875729590105375124[16] = 0;
   out_2875729590105375124[17] = 0;
   out_2875729590105375124[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2875729590105375124[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2875729590105375124[20] = 0;
   out_2875729590105375124[21] = state[8];
   out_2875729590105375124[22] = 0;
   out_2875729590105375124[23] = -state[6];
   out_2875729590105375124[24] = -state[5];
   out_2875729590105375124[25] = 0;
   out_2875729590105375124[26] = state[3];
   out_2875729590105375124[27] = 0;
   out_2875729590105375124[28] = 0;
   out_2875729590105375124[29] = 0;
   out_2875729590105375124[30] = 0;
   out_2875729590105375124[31] = 1;
   out_2875729590105375124[32] = 0;
   out_2875729590105375124[33] = 0;
   out_2875729590105375124[34] = 1;
   out_2875729590105375124[35] = 0;
   out_2875729590105375124[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2875729590105375124[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2875729590105375124[38] = 0;
   out_2875729590105375124[39] = -state[7];
   out_2875729590105375124[40] = state[6];
   out_2875729590105375124[41] = 0;
   out_2875729590105375124[42] = state[4];
   out_2875729590105375124[43] = -state[3];
   out_2875729590105375124[44] = 0;
   out_2875729590105375124[45] = 0;
   out_2875729590105375124[46] = 0;
   out_2875729590105375124[47] = 0;
   out_2875729590105375124[48] = 0;
   out_2875729590105375124[49] = 0;
   out_2875729590105375124[50] = 1;
   out_2875729590105375124[51] = 0;
   out_2875729590105375124[52] = 0;
   out_2875729590105375124[53] = 1;
}
void h_13(double *state, double *unused, double *out_1766623406694503914) {
   out_1766623406694503914[0] = state[3];
   out_1766623406694503914[1] = state[4];
   out_1766623406694503914[2] = state[5];
}
void H_13(double *state, double *unused, double *out_776881510314174123) {
   out_776881510314174123[0] = 0;
   out_776881510314174123[1] = 0;
   out_776881510314174123[2] = 0;
   out_776881510314174123[3] = 1;
   out_776881510314174123[4] = 0;
   out_776881510314174123[5] = 0;
   out_776881510314174123[6] = 0;
   out_776881510314174123[7] = 0;
   out_776881510314174123[8] = 0;
   out_776881510314174123[9] = 0;
   out_776881510314174123[10] = 0;
   out_776881510314174123[11] = 0;
   out_776881510314174123[12] = 0;
   out_776881510314174123[13] = 0;
   out_776881510314174123[14] = 0;
   out_776881510314174123[15] = 0;
   out_776881510314174123[16] = 0;
   out_776881510314174123[17] = 0;
   out_776881510314174123[18] = 0;
   out_776881510314174123[19] = 0;
   out_776881510314174123[20] = 0;
   out_776881510314174123[21] = 0;
   out_776881510314174123[22] = 1;
   out_776881510314174123[23] = 0;
   out_776881510314174123[24] = 0;
   out_776881510314174123[25] = 0;
   out_776881510314174123[26] = 0;
   out_776881510314174123[27] = 0;
   out_776881510314174123[28] = 0;
   out_776881510314174123[29] = 0;
   out_776881510314174123[30] = 0;
   out_776881510314174123[31] = 0;
   out_776881510314174123[32] = 0;
   out_776881510314174123[33] = 0;
   out_776881510314174123[34] = 0;
   out_776881510314174123[35] = 0;
   out_776881510314174123[36] = 0;
   out_776881510314174123[37] = 0;
   out_776881510314174123[38] = 0;
   out_776881510314174123[39] = 0;
   out_776881510314174123[40] = 0;
   out_776881510314174123[41] = 1;
   out_776881510314174123[42] = 0;
   out_776881510314174123[43] = 0;
   out_776881510314174123[44] = 0;
   out_776881510314174123[45] = 0;
   out_776881510314174123[46] = 0;
   out_776881510314174123[47] = 0;
   out_776881510314174123[48] = 0;
   out_776881510314174123[49] = 0;
   out_776881510314174123[50] = 0;
   out_776881510314174123[51] = 0;
   out_776881510314174123[52] = 0;
   out_776881510314174123[53] = 0;
}
void h_14(double *state, double *unused, double *out_4485852814658279598) {
   out_4485852814658279598[0] = state[6];
   out_4485852814658279598[1] = state[7];
   out_4485852814658279598[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4424271862291390523) {
   out_4424271862291390523[0] = 0;
   out_4424271862291390523[1] = 0;
   out_4424271862291390523[2] = 0;
   out_4424271862291390523[3] = 0;
   out_4424271862291390523[4] = 0;
   out_4424271862291390523[5] = 0;
   out_4424271862291390523[6] = 1;
   out_4424271862291390523[7] = 0;
   out_4424271862291390523[8] = 0;
   out_4424271862291390523[9] = 0;
   out_4424271862291390523[10] = 0;
   out_4424271862291390523[11] = 0;
   out_4424271862291390523[12] = 0;
   out_4424271862291390523[13] = 0;
   out_4424271862291390523[14] = 0;
   out_4424271862291390523[15] = 0;
   out_4424271862291390523[16] = 0;
   out_4424271862291390523[17] = 0;
   out_4424271862291390523[18] = 0;
   out_4424271862291390523[19] = 0;
   out_4424271862291390523[20] = 0;
   out_4424271862291390523[21] = 0;
   out_4424271862291390523[22] = 0;
   out_4424271862291390523[23] = 0;
   out_4424271862291390523[24] = 0;
   out_4424271862291390523[25] = 1;
   out_4424271862291390523[26] = 0;
   out_4424271862291390523[27] = 0;
   out_4424271862291390523[28] = 0;
   out_4424271862291390523[29] = 0;
   out_4424271862291390523[30] = 0;
   out_4424271862291390523[31] = 0;
   out_4424271862291390523[32] = 0;
   out_4424271862291390523[33] = 0;
   out_4424271862291390523[34] = 0;
   out_4424271862291390523[35] = 0;
   out_4424271862291390523[36] = 0;
   out_4424271862291390523[37] = 0;
   out_4424271862291390523[38] = 0;
   out_4424271862291390523[39] = 0;
   out_4424271862291390523[40] = 0;
   out_4424271862291390523[41] = 0;
   out_4424271862291390523[42] = 0;
   out_4424271862291390523[43] = 0;
   out_4424271862291390523[44] = 1;
   out_4424271862291390523[45] = 0;
   out_4424271862291390523[46] = 0;
   out_4424271862291390523[47] = 0;
   out_4424271862291390523[48] = 0;
   out_4424271862291390523[49] = 0;
   out_4424271862291390523[50] = 0;
   out_4424271862291390523[51] = 0;
   out_4424271862291390523[52] = 0;
   out_4424271862291390523[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5135933030950096940) {
  err_fun(nom_x, delta_x, out_5135933030950096940);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4473434694497561565) {
  inv_err_fun(nom_x, true_x, out_4473434694497561565);
}
void pose_H_mod_fun(double *state, double *out_4955206330411314418) {
  H_mod_fun(state, out_4955206330411314418);
}
void pose_f_fun(double *state, double dt, double *out_1052805527796842003) {
  f_fun(state,  dt, out_1052805527796842003);
}
void pose_F_fun(double *state, double dt, double *out_5871869036335399812) {
  F_fun(state,  dt, out_5871869036335399812);
}
void pose_h_4(double *state, double *unused, double *out_921118668651624411) {
  h_4(state, unused, out_921118668651624411);
}
void pose_H_4(double *state, double *unused, double *out_3989155335646506924) {
  H_4(state, unused, out_3989155335646506924);
}
void pose_h_10(double *state, double *unused, double *out_8738369372345178390) {
  h_10(state, unused, out_8738369372345178390);
}
void pose_H_10(double *state, double *unused, double *out_2875729590105375124) {
  H_10(state, unused, out_2875729590105375124);
}
void pose_h_13(double *state, double *unused, double *out_1766623406694503914) {
  h_13(state, unused, out_1766623406694503914);
}
void pose_H_13(double *state, double *unused, double *out_776881510314174123) {
  H_13(state, unused, out_776881510314174123);
}
void pose_h_14(double *state, double *unused, double *out_4485852814658279598) {
  h_14(state, unused, out_4485852814658279598);
}
void pose_H_14(double *state, double *unused, double *out_4424271862291390523) {
  H_14(state, unused, out_4424271862291390523);
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
