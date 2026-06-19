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
void err_fun(double *nom_x, double *delta_x, double *out_4423077432163082570) {
   out_4423077432163082570[0] = delta_x[0] + nom_x[0];
   out_4423077432163082570[1] = delta_x[1] + nom_x[1];
   out_4423077432163082570[2] = delta_x[2] + nom_x[2];
   out_4423077432163082570[3] = delta_x[3] + nom_x[3];
   out_4423077432163082570[4] = delta_x[4] + nom_x[4];
   out_4423077432163082570[5] = delta_x[5] + nom_x[5];
   out_4423077432163082570[6] = delta_x[6] + nom_x[6];
   out_4423077432163082570[7] = delta_x[7] + nom_x[7];
   out_4423077432163082570[8] = delta_x[8] + nom_x[8];
   out_4423077432163082570[9] = delta_x[9] + nom_x[9];
   out_4423077432163082570[10] = delta_x[10] + nom_x[10];
   out_4423077432163082570[11] = delta_x[11] + nom_x[11];
   out_4423077432163082570[12] = delta_x[12] + nom_x[12];
   out_4423077432163082570[13] = delta_x[13] + nom_x[13];
   out_4423077432163082570[14] = delta_x[14] + nom_x[14];
   out_4423077432163082570[15] = delta_x[15] + nom_x[15];
   out_4423077432163082570[16] = delta_x[16] + nom_x[16];
   out_4423077432163082570[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3066625947211960781) {
   out_3066625947211960781[0] = -nom_x[0] + true_x[0];
   out_3066625947211960781[1] = -nom_x[1] + true_x[1];
   out_3066625947211960781[2] = -nom_x[2] + true_x[2];
   out_3066625947211960781[3] = -nom_x[3] + true_x[3];
   out_3066625947211960781[4] = -nom_x[4] + true_x[4];
   out_3066625947211960781[5] = -nom_x[5] + true_x[5];
   out_3066625947211960781[6] = -nom_x[6] + true_x[6];
   out_3066625947211960781[7] = -nom_x[7] + true_x[7];
   out_3066625947211960781[8] = -nom_x[8] + true_x[8];
   out_3066625947211960781[9] = -nom_x[9] + true_x[9];
   out_3066625947211960781[10] = -nom_x[10] + true_x[10];
   out_3066625947211960781[11] = -nom_x[11] + true_x[11];
   out_3066625947211960781[12] = -nom_x[12] + true_x[12];
   out_3066625947211960781[13] = -nom_x[13] + true_x[13];
   out_3066625947211960781[14] = -nom_x[14] + true_x[14];
   out_3066625947211960781[15] = -nom_x[15] + true_x[15];
   out_3066625947211960781[16] = -nom_x[16] + true_x[16];
   out_3066625947211960781[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7899193355677302719) {
   out_7899193355677302719[0] = 1.0;
   out_7899193355677302719[1] = 0.0;
   out_7899193355677302719[2] = 0.0;
   out_7899193355677302719[3] = 0.0;
   out_7899193355677302719[4] = 0.0;
   out_7899193355677302719[5] = 0.0;
   out_7899193355677302719[6] = 0.0;
   out_7899193355677302719[7] = 0.0;
   out_7899193355677302719[8] = 0.0;
   out_7899193355677302719[9] = 0.0;
   out_7899193355677302719[10] = 0.0;
   out_7899193355677302719[11] = 0.0;
   out_7899193355677302719[12] = 0.0;
   out_7899193355677302719[13] = 0.0;
   out_7899193355677302719[14] = 0.0;
   out_7899193355677302719[15] = 0.0;
   out_7899193355677302719[16] = 0.0;
   out_7899193355677302719[17] = 0.0;
   out_7899193355677302719[18] = 0.0;
   out_7899193355677302719[19] = 1.0;
   out_7899193355677302719[20] = 0.0;
   out_7899193355677302719[21] = 0.0;
   out_7899193355677302719[22] = 0.0;
   out_7899193355677302719[23] = 0.0;
   out_7899193355677302719[24] = 0.0;
   out_7899193355677302719[25] = 0.0;
   out_7899193355677302719[26] = 0.0;
   out_7899193355677302719[27] = 0.0;
   out_7899193355677302719[28] = 0.0;
   out_7899193355677302719[29] = 0.0;
   out_7899193355677302719[30] = 0.0;
   out_7899193355677302719[31] = 0.0;
   out_7899193355677302719[32] = 0.0;
   out_7899193355677302719[33] = 0.0;
   out_7899193355677302719[34] = 0.0;
   out_7899193355677302719[35] = 0.0;
   out_7899193355677302719[36] = 0.0;
   out_7899193355677302719[37] = 0.0;
   out_7899193355677302719[38] = 1.0;
   out_7899193355677302719[39] = 0.0;
   out_7899193355677302719[40] = 0.0;
   out_7899193355677302719[41] = 0.0;
   out_7899193355677302719[42] = 0.0;
   out_7899193355677302719[43] = 0.0;
   out_7899193355677302719[44] = 0.0;
   out_7899193355677302719[45] = 0.0;
   out_7899193355677302719[46] = 0.0;
   out_7899193355677302719[47] = 0.0;
   out_7899193355677302719[48] = 0.0;
   out_7899193355677302719[49] = 0.0;
   out_7899193355677302719[50] = 0.0;
   out_7899193355677302719[51] = 0.0;
   out_7899193355677302719[52] = 0.0;
   out_7899193355677302719[53] = 0.0;
   out_7899193355677302719[54] = 0.0;
   out_7899193355677302719[55] = 0.0;
   out_7899193355677302719[56] = 0.0;
   out_7899193355677302719[57] = 1.0;
   out_7899193355677302719[58] = 0.0;
   out_7899193355677302719[59] = 0.0;
   out_7899193355677302719[60] = 0.0;
   out_7899193355677302719[61] = 0.0;
   out_7899193355677302719[62] = 0.0;
   out_7899193355677302719[63] = 0.0;
   out_7899193355677302719[64] = 0.0;
   out_7899193355677302719[65] = 0.0;
   out_7899193355677302719[66] = 0.0;
   out_7899193355677302719[67] = 0.0;
   out_7899193355677302719[68] = 0.0;
   out_7899193355677302719[69] = 0.0;
   out_7899193355677302719[70] = 0.0;
   out_7899193355677302719[71] = 0.0;
   out_7899193355677302719[72] = 0.0;
   out_7899193355677302719[73] = 0.0;
   out_7899193355677302719[74] = 0.0;
   out_7899193355677302719[75] = 0.0;
   out_7899193355677302719[76] = 1.0;
   out_7899193355677302719[77] = 0.0;
   out_7899193355677302719[78] = 0.0;
   out_7899193355677302719[79] = 0.0;
   out_7899193355677302719[80] = 0.0;
   out_7899193355677302719[81] = 0.0;
   out_7899193355677302719[82] = 0.0;
   out_7899193355677302719[83] = 0.0;
   out_7899193355677302719[84] = 0.0;
   out_7899193355677302719[85] = 0.0;
   out_7899193355677302719[86] = 0.0;
   out_7899193355677302719[87] = 0.0;
   out_7899193355677302719[88] = 0.0;
   out_7899193355677302719[89] = 0.0;
   out_7899193355677302719[90] = 0.0;
   out_7899193355677302719[91] = 0.0;
   out_7899193355677302719[92] = 0.0;
   out_7899193355677302719[93] = 0.0;
   out_7899193355677302719[94] = 0.0;
   out_7899193355677302719[95] = 1.0;
   out_7899193355677302719[96] = 0.0;
   out_7899193355677302719[97] = 0.0;
   out_7899193355677302719[98] = 0.0;
   out_7899193355677302719[99] = 0.0;
   out_7899193355677302719[100] = 0.0;
   out_7899193355677302719[101] = 0.0;
   out_7899193355677302719[102] = 0.0;
   out_7899193355677302719[103] = 0.0;
   out_7899193355677302719[104] = 0.0;
   out_7899193355677302719[105] = 0.0;
   out_7899193355677302719[106] = 0.0;
   out_7899193355677302719[107] = 0.0;
   out_7899193355677302719[108] = 0.0;
   out_7899193355677302719[109] = 0.0;
   out_7899193355677302719[110] = 0.0;
   out_7899193355677302719[111] = 0.0;
   out_7899193355677302719[112] = 0.0;
   out_7899193355677302719[113] = 0.0;
   out_7899193355677302719[114] = 1.0;
   out_7899193355677302719[115] = 0.0;
   out_7899193355677302719[116] = 0.0;
   out_7899193355677302719[117] = 0.0;
   out_7899193355677302719[118] = 0.0;
   out_7899193355677302719[119] = 0.0;
   out_7899193355677302719[120] = 0.0;
   out_7899193355677302719[121] = 0.0;
   out_7899193355677302719[122] = 0.0;
   out_7899193355677302719[123] = 0.0;
   out_7899193355677302719[124] = 0.0;
   out_7899193355677302719[125] = 0.0;
   out_7899193355677302719[126] = 0.0;
   out_7899193355677302719[127] = 0.0;
   out_7899193355677302719[128] = 0.0;
   out_7899193355677302719[129] = 0.0;
   out_7899193355677302719[130] = 0.0;
   out_7899193355677302719[131] = 0.0;
   out_7899193355677302719[132] = 0.0;
   out_7899193355677302719[133] = 1.0;
   out_7899193355677302719[134] = 0.0;
   out_7899193355677302719[135] = 0.0;
   out_7899193355677302719[136] = 0.0;
   out_7899193355677302719[137] = 0.0;
   out_7899193355677302719[138] = 0.0;
   out_7899193355677302719[139] = 0.0;
   out_7899193355677302719[140] = 0.0;
   out_7899193355677302719[141] = 0.0;
   out_7899193355677302719[142] = 0.0;
   out_7899193355677302719[143] = 0.0;
   out_7899193355677302719[144] = 0.0;
   out_7899193355677302719[145] = 0.0;
   out_7899193355677302719[146] = 0.0;
   out_7899193355677302719[147] = 0.0;
   out_7899193355677302719[148] = 0.0;
   out_7899193355677302719[149] = 0.0;
   out_7899193355677302719[150] = 0.0;
   out_7899193355677302719[151] = 0.0;
   out_7899193355677302719[152] = 1.0;
   out_7899193355677302719[153] = 0.0;
   out_7899193355677302719[154] = 0.0;
   out_7899193355677302719[155] = 0.0;
   out_7899193355677302719[156] = 0.0;
   out_7899193355677302719[157] = 0.0;
   out_7899193355677302719[158] = 0.0;
   out_7899193355677302719[159] = 0.0;
   out_7899193355677302719[160] = 0.0;
   out_7899193355677302719[161] = 0.0;
   out_7899193355677302719[162] = 0.0;
   out_7899193355677302719[163] = 0.0;
   out_7899193355677302719[164] = 0.0;
   out_7899193355677302719[165] = 0.0;
   out_7899193355677302719[166] = 0.0;
   out_7899193355677302719[167] = 0.0;
   out_7899193355677302719[168] = 0.0;
   out_7899193355677302719[169] = 0.0;
   out_7899193355677302719[170] = 0.0;
   out_7899193355677302719[171] = 1.0;
   out_7899193355677302719[172] = 0.0;
   out_7899193355677302719[173] = 0.0;
   out_7899193355677302719[174] = 0.0;
   out_7899193355677302719[175] = 0.0;
   out_7899193355677302719[176] = 0.0;
   out_7899193355677302719[177] = 0.0;
   out_7899193355677302719[178] = 0.0;
   out_7899193355677302719[179] = 0.0;
   out_7899193355677302719[180] = 0.0;
   out_7899193355677302719[181] = 0.0;
   out_7899193355677302719[182] = 0.0;
   out_7899193355677302719[183] = 0.0;
   out_7899193355677302719[184] = 0.0;
   out_7899193355677302719[185] = 0.0;
   out_7899193355677302719[186] = 0.0;
   out_7899193355677302719[187] = 0.0;
   out_7899193355677302719[188] = 0.0;
   out_7899193355677302719[189] = 0.0;
   out_7899193355677302719[190] = 1.0;
   out_7899193355677302719[191] = 0.0;
   out_7899193355677302719[192] = 0.0;
   out_7899193355677302719[193] = 0.0;
   out_7899193355677302719[194] = 0.0;
   out_7899193355677302719[195] = 0.0;
   out_7899193355677302719[196] = 0.0;
   out_7899193355677302719[197] = 0.0;
   out_7899193355677302719[198] = 0.0;
   out_7899193355677302719[199] = 0.0;
   out_7899193355677302719[200] = 0.0;
   out_7899193355677302719[201] = 0.0;
   out_7899193355677302719[202] = 0.0;
   out_7899193355677302719[203] = 0.0;
   out_7899193355677302719[204] = 0.0;
   out_7899193355677302719[205] = 0.0;
   out_7899193355677302719[206] = 0.0;
   out_7899193355677302719[207] = 0.0;
   out_7899193355677302719[208] = 0.0;
   out_7899193355677302719[209] = 1.0;
   out_7899193355677302719[210] = 0.0;
   out_7899193355677302719[211] = 0.0;
   out_7899193355677302719[212] = 0.0;
   out_7899193355677302719[213] = 0.0;
   out_7899193355677302719[214] = 0.0;
   out_7899193355677302719[215] = 0.0;
   out_7899193355677302719[216] = 0.0;
   out_7899193355677302719[217] = 0.0;
   out_7899193355677302719[218] = 0.0;
   out_7899193355677302719[219] = 0.0;
   out_7899193355677302719[220] = 0.0;
   out_7899193355677302719[221] = 0.0;
   out_7899193355677302719[222] = 0.0;
   out_7899193355677302719[223] = 0.0;
   out_7899193355677302719[224] = 0.0;
   out_7899193355677302719[225] = 0.0;
   out_7899193355677302719[226] = 0.0;
   out_7899193355677302719[227] = 0.0;
   out_7899193355677302719[228] = 1.0;
   out_7899193355677302719[229] = 0.0;
   out_7899193355677302719[230] = 0.0;
   out_7899193355677302719[231] = 0.0;
   out_7899193355677302719[232] = 0.0;
   out_7899193355677302719[233] = 0.0;
   out_7899193355677302719[234] = 0.0;
   out_7899193355677302719[235] = 0.0;
   out_7899193355677302719[236] = 0.0;
   out_7899193355677302719[237] = 0.0;
   out_7899193355677302719[238] = 0.0;
   out_7899193355677302719[239] = 0.0;
   out_7899193355677302719[240] = 0.0;
   out_7899193355677302719[241] = 0.0;
   out_7899193355677302719[242] = 0.0;
   out_7899193355677302719[243] = 0.0;
   out_7899193355677302719[244] = 0.0;
   out_7899193355677302719[245] = 0.0;
   out_7899193355677302719[246] = 0.0;
   out_7899193355677302719[247] = 1.0;
   out_7899193355677302719[248] = 0.0;
   out_7899193355677302719[249] = 0.0;
   out_7899193355677302719[250] = 0.0;
   out_7899193355677302719[251] = 0.0;
   out_7899193355677302719[252] = 0.0;
   out_7899193355677302719[253] = 0.0;
   out_7899193355677302719[254] = 0.0;
   out_7899193355677302719[255] = 0.0;
   out_7899193355677302719[256] = 0.0;
   out_7899193355677302719[257] = 0.0;
   out_7899193355677302719[258] = 0.0;
   out_7899193355677302719[259] = 0.0;
   out_7899193355677302719[260] = 0.0;
   out_7899193355677302719[261] = 0.0;
   out_7899193355677302719[262] = 0.0;
   out_7899193355677302719[263] = 0.0;
   out_7899193355677302719[264] = 0.0;
   out_7899193355677302719[265] = 0.0;
   out_7899193355677302719[266] = 1.0;
   out_7899193355677302719[267] = 0.0;
   out_7899193355677302719[268] = 0.0;
   out_7899193355677302719[269] = 0.0;
   out_7899193355677302719[270] = 0.0;
   out_7899193355677302719[271] = 0.0;
   out_7899193355677302719[272] = 0.0;
   out_7899193355677302719[273] = 0.0;
   out_7899193355677302719[274] = 0.0;
   out_7899193355677302719[275] = 0.0;
   out_7899193355677302719[276] = 0.0;
   out_7899193355677302719[277] = 0.0;
   out_7899193355677302719[278] = 0.0;
   out_7899193355677302719[279] = 0.0;
   out_7899193355677302719[280] = 0.0;
   out_7899193355677302719[281] = 0.0;
   out_7899193355677302719[282] = 0.0;
   out_7899193355677302719[283] = 0.0;
   out_7899193355677302719[284] = 0.0;
   out_7899193355677302719[285] = 1.0;
   out_7899193355677302719[286] = 0.0;
   out_7899193355677302719[287] = 0.0;
   out_7899193355677302719[288] = 0.0;
   out_7899193355677302719[289] = 0.0;
   out_7899193355677302719[290] = 0.0;
   out_7899193355677302719[291] = 0.0;
   out_7899193355677302719[292] = 0.0;
   out_7899193355677302719[293] = 0.0;
   out_7899193355677302719[294] = 0.0;
   out_7899193355677302719[295] = 0.0;
   out_7899193355677302719[296] = 0.0;
   out_7899193355677302719[297] = 0.0;
   out_7899193355677302719[298] = 0.0;
   out_7899193355677302719[299] = 0.0;
   out_7899193355677302719[300] = 0.0;
   out_7899193355677302719[301] = 0.0;
   out_7899193355677302719[302] = 0.0;
   out_7899193355677302719[303] = 0.0;
   out_7899193355677302719[304] = 1.0;
   out_7899193355677302719[305] = 0.0;
   out_7899193355677302719[306] = 0.0;
   out_7899193355677302719[307] = 0.0;
   out_7899193355677302719[308] = 0.0;
   out_7899193355677302719[309] = 0.0;
   out_7899193355677302719[310] = 0.0;
   out_7899193355677302719[311] = 0.0;
   out_7899193355677302719[312] = 0.0;
   out_7899193355677302719[313] = 0.0;
   out_7899193355677302719[314] = 0.0;
   out_7899193355677302719[315] = 0.0;
   out_7899193355677302719[316] = 0.0;
   out_7899193355677302719[317] = 0.0;
   out_7899193355677302719[318] = 0.0;
   out_7899193355677302719[319] = 0.0;
   out_7899193355677302719[320] = 0.0;
   out_7899193355677302719[321] = 0.0;
   out_7899193355677302719[322] = 0.0;
   out_7899193355677302719[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1767716959874096227) {
   out_1767716959874096227[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1767716959874096227[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1767716959874096227[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1767716959874096227[3] = dt*state[12] + state[3];
   out_1767716959874096227[4] = dt*state[13] + state[4];
   out_1767716959874096227[5] = dt*state[14] + state[5];
   out_1767716959874096227[6] = state[6];
   out_1767716959874096227[7] = state[7];
   out_1767716959874096227[8] = state[8];
   out_1767716959874096227[9] = state[9];
   out_1767716959874096227[10] = state[10];
   out_1767716959874096227[11] = state[11];
   out_1767716959874096227[12] = state[12];
   out_1767716959874096227[13] = state[13];
   out_1767716959874096227[14] = state[14];
   out_1767716959874096227[15] = state[15];
   out_1767716959874096227[16] = state[16];
   out_1767716959874096227[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5946100134082923473) {
   out_5946100134082923473[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5946100134082923473[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5946100134082923473[2] = 0;
   out_5946100134082923473[3] = 0;
   out_5946100134082923473[4] = 0;
   out_5946100134082923473[5] = 0;
   out_5946100134082923473[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5946100134082923473[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5946100134082923473[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5946100134082923473[9] = 0;
   out_5946100134082923473[10] = 0;
   out_5946100134082923473[11] = 0;
   out_5946100134082923473[12] = 0;
   out_5946100134082923473[13] = 0;
   out_5946100134082923473[14] = 0;
   out_5946100134082923473[15] = 0;
   out_5946100134082923473[16] = 0;
   out_5946100134082923473[17] = 0;
   out_5946100134082923473[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5946100134082923473[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5946100134082923473[20] = 0;
   out_5946100134082923473[21] = 0;
   out_5946100134082923473[22] = 0;
   out_5946100134082923473[23] = 0;
   out_5946100134082923473[24] = 0;
   out_5946100134082923473[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5946100134082923473[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5946100134082923473[27] = 0;
   out_5946100134082923473[28] = 0;
   out_5946100134082923473[29] = 0;
   out_5946100134082923473[30] = 0;
   out_5946100134082923473[31] = 0;
   out_5946100134082923473[32] = 0;
   out_5946100134082923473[33] = 0;
   out_5946100134082923473[34] = 0;
   out_5946100134082923473[35] = 0;
   out_5946100134082923473[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5946100134082923473[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5946100134082923473[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5946100134082923473[39] = 0;
   out_5946100134082923473[40] = 0;
   out_5946100134082923473[41] = 0;
   out_5946100134082923473[42] = 0;
   out_5946100134082923473[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5946100134082923473[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5946100134082923473[45] = 0;
   out_5946100134082923473[46] = 0;
   out_5946100134082923473[47] = 0;
   out_5946100134082923473[48] = 0;
   out_5946100134082923473[49] = 0;
   out_5946100134082923473[50] = 0;
   out_5946100134082923473[51] = 0;
   out_5946100134082923473[52] = 0;
   out_5946100134082923473[53] = 0;
   out_5946100134082923473[54] = 0;
   out_5946100134082923473[55] = 0;
   out_5946100134082923473[56] = 0;
   out_5946100134082923473[57] = 1;
   out_5946100134082923473[58] = 0;
   out_5946100134082923473[59] = 0;
   out_5946100134082923473[60] = 0;
   out_5946100134082923473[61] = 0;
   out_5946100134082923473[62] = 0;
   out_5946100134082923473[63] = 0;
   out_5946100134082923473[64] = 0;
   out_5946100134082923473[65] = 0;
   out_5946100134082923473[66] = dt;
   out_5946100134082923473[67] = 0;
   out_5946100134082923473[68] = 0;
   out_5946100134082923473[69] = 0;
   out_5946100134082923473[70] = 0;
   out_5946100134082923473[71] = 0;
   out_5946100134082923473[72] = 0;
   out_5946100134082923473[73] = 0;
   out_5946100134082923473[74] = 0;
   out_5946100134082923473[75] = 0;
   out_5946100134082923473[76] = 1;
   out_5946100134082923473[77] = 0;
   out_5946100134082923473[78] = 0;
   out_5946100134082923473[79] = 0;
   out_5946100134082923473[80] = 0;
   out_5946100134082923473[81] = 0;
   out_5946100134082923473[82] = 0;
   out_5946100134082923473[83] = 0;
   out_5946100134082923473[84] = 0;
   out_5946100134082923473[85] = dt;
   out_5946100134082923473[86] = 0;
   out_5946100134082923473[87] = 0;
   out_5946100134082923473[88] = 0;
   out_5946100134082923473[89] = 0;
   out_5946100134082923473[90] = 0;
   out_5946100134082923473[91] = 0;
   out_5946100134082923473[92] = 0;
   out_5946100134082923473[93] = 0;
   out_5946100134082923473[94] = 0;
   out_5946100134082923473[95] = 1;
   out_5946100134082923473[96] = 0;
   out_5946100134082923473[97] = 0;
   out_5946100134082923473[98] = 0;
   out_5946100134082923473[99] = 0;
   out_5946100134082923473[100] = 0;
   out_5946100134082923473[101] = 0;
   out_5946100134082923473[102] = 0;
   out_5946100134082923473[103] = 0;
   out_5946100134082923473[104] = dt;
   out_5946100134082923473[105] = 0;
   out_5946100134082923473[106] = 0;
   out_5946100134082923473[107] = 0;
   out_5946100134082923473[108] = 0;
   out_5946100134082923473[109] = 0;
   out_5946100134082923473[110] = 0;
   out_5946100134082923473[111] = 0;
   out_5946100134082923473[112] = 0;
   out_5946100134082923473[113] = 0;
   out_5946100134082923473[114] = 1;
   out_5946100134082923473[115] = 0;
   out_5946100134082923473[116] = 0;
   out_5946100134082923473[117] = 0;
   out_5946100134082923473[118] = 0;
   out_5946100134082923473[119] = 0;
   out_5946100134082923473[120] = 0;
   out_5946100134082923473[121] = 0;
   out_5946100134082923473[122] = 0;
   out_5946100134082923473[123] = 0;
   out_5946100134082923473[124] = 0;
   out_5946100134082923473[125] = 0;
   out_5946100134082923473[126] = 0;
   out_5946100134082923473[127] = 0;
   out_5946100134082923473[128] = 0;
   out_5946100134082923473[129] = 0;
   out_5946100134082923473[130] = 0;
   out_5946100134082923473[131] = 0;
   out_5946100134082923473[132] = 0;
   out_5946100134082923473[133] = 1;
   out_5946100134082923473[134] = 0;
   out_5946100134082923473[135] = 0;
   out_5946100134082923473[136] = 0;
   out_5946100134082923473[137] = 0;
   out_5946100134082923473[138] = 0;
   out_5946100134082923473[139] = 0;
   out_5946100134082923473[140] = 0;
   out_5946100134082923473[141] = 0;
   out_5946100134082923473[142] = 0;
   out_5946100134082923473[143] = 0;
   out_5946100134082923473[144] = 0;
   out_5946100134082923473[145] = 0;
   out_5946100134082923473[146] = 0;
   out_5946100134082923473[147] = 0;
   out_5946100134082923473[148] = 0;
   out_5946100134082923473[149] = 0;
   out_5946100134082923473[150] = 0;
   out_5946100134082923473[151] = 0;
   out_5946100134082923473[152] = 1;
   out_5946100134082923473[153] = 0;
   out_5946100134082923473[154] = 0;
   out_5946100134082923473[155] = 0;
   out_5946100134082923473[156] = 0;
   out_5946100134082923473[157] = 0;
   out_5946100134082923473[158] = 0;
   out_5946100134082923473[159] = 0;
   out_5946100134082923473[160] = 0;
   out_5946100134082923473[161] = 0;
   out_5946100134082923473[162] = 0;
   out_5946100134082923473[163] = 0;
   out_5946100134082923473[164] = 0;
   out_5946100134082923473[165] = 0;
   out_5946100134082923473[166] = 0;
   out_5946100134082923473[167] = 0;
   out_5946100134082923473[168] = 0;
   out_5946100134082923473[169] = 0;
   out_5946100134082923473[170] = 0;
   out_5946100134082923473[171] = 1;
   out_5946100134082923473[172] = 0;
   out_5946100134082923473[173] = 0;
   out_5946100134082923473[174] = 0;
   out_5946100134082923473[175] = 0;
   out_5946100134082923473[176] = 0;
   out_5946100134082923473[177] = 0;
   out_5946100134082923473[178] = 0;
   out_5946100134082923473[179] = 0;
   out_5946100134082923473[180] = 0;
   out_5946100134082923473[181] = 0;
   out_5946100134082923473[182] = 0;
   out_5946100134082923473[183] = 0;
   out_5946100134082923473[184] = 0;
   out_5946100134082923473[185] = 0;
   out_5946100134082923473[186] = 0;
   out_5946100134082923473[187] = 0;
   out_5946100134082923473[188] = 0;
   out_5946100134082923473[189] = 0;
   out_5946100134082923473[190] = 1;
   out_5946100134082923473[191] = 0;
   out_5946100134082923473[192] = 0;
   out_5946100134082923473[193] = 0;
   out_5946100134082923473[194] = 0;
   out_5946100134082923473[195] = 0;
   out_5946100134082923473[196] = 0;
   out_5946100134082923473[197] = 0;
   out_5946100134082923473[198] = 0;
   out_5946100134082923473[199] = 0;
   out_5946100134082923473[200] = 0;
   out_5946100134082923473[201] = 0;
   out_5946100134082923473[202] = 0;
   out_5946100134082923473[203] = 0;
   out_5946100134082923473[204] = 0;
   out_5946100134082923473[205] = 0;
   out_5946100134082923473[206] = 0;
   out_5946100134082923473[207] = 0;
   out_5946100134082923473[208] = 0;
   out_5946100134082923473[209] = 1;
   out_5946100134082923473[210] = 0;
   out_5946100134082923473[211] = 0;
   out_5946100134082923473[212] = 0;
   out_5946100134082923473[213] = 0;
   out_5946100134082923473[214] = 0;
   out_5946100134082923473[215] = 0;
   out_5946100134082923473[216] = 0;
   out_5946100134082923473[217] = 0;
   out_5946100134082923473[218] = 0;
   out_5946100134082923473[219] = 0;
   out_5946100134082923473[220] = 0;
   out_5946100134082923473[221] = 0;
   out_5946100134082923473[222] = 0;
   out_5946100134082923473[223] = 0;
   out_5946100134082923473[224] = 0;
   out_5946100134082923473[225] = 0;
   out_5946100134082923473[226] = 0;
   out_5946100134082923473[227] = 0;
   out_5946100134082923473[228] = 1;
   out_5946100134082923473[229] = 0;
   out_5946100134082923473[230] = 0;
   out_5946100134082923473[231] = 0;
   out_5946100134082923473[232] = 0;
   out_5946100134082923473[233] = 0;
   out_5946100134082923473[234] = 0;
   out_5946100134082923473[235] = 0;
   out_5946100134082923473[236] = 0;
   out_5946100134082923473[237] = 0;
   out_5946100134082923473[238] = 0;
   out_5946100134082923473[239] = 0;
   out_5946100134082923473[240] = 0;
   out_5946100134082923473[241] = 0;
   out_5946100134082923473[242] = 0;
   out_5946100134082923473[243] = 0;
   out_5946100134082923473[244] = 0;
   out_5946100134082923473[245] = 0;
   out_5946100134082923473[246] = 0;
   out_5946100134082923473[247] = 1;
   out_5946100134082923473[248] = 0;
   out_5946100134082923473[249] = 0;
   out_5946100134082923473[250] = 0;
   out_5946100134082923473[251] = 0;
   out_5946100134082923473[252] = 0;
   out_5946100134082923473[253] = 0;
   out_5946100134082923473[254] = 0;
   out_5946100134082923473[255] = 0;
   out_5946100134082923473[256] = 0;
   out_5946100134082923473[257] = 0;
   out_5946100134082923473[258] = 0;
   out_5946100134082923473[259] = 0;
   out_5946100134082923473[260] = 0;
   out_5946100134082923473[261] = 0;
   out_5946100134082923473[262] = 0;
   out_5946100134082923473[263] = 0;
   out_5946100134082923473[264] = 0;
   out_5946100134082923473[265] = 0;
   out_5946100134082923473[266] = 1;
   out_5946100134082923473[267] = 0;
   out_5946100134082923473[268] = 0;
   out_5946100134082923473[269] = 0;
   out_5946100134082923473[270] = 0;
   out_5946100134082923473[271] = 0;
   out_5946100134082923473[272] = 0;
   out_5946100134082923473[273] = 0;
   out_5946100134082923473[274] = 0;
   out_5946100134082923473[275] = 0;
   out_5946100134082923473[276] = 0;
   out_5946100134082923473[277] = 0;
   out_5946100134082923473[278] = 0;
   out_5946100134082923473[279] = 0;
   out_5946100134082923473[280] = 0;
   out_5946100134082923473[281] = 0;
   out_5946100134082923473[282] = 0;
   out_5946100134082923473[283] = 0;
   out_5946100134082923473[284] = 0;
   out_5946100134082923473[285] = 1;
   out_5946100134082923473[286] = 0;
   out_5946100134082923473[287] = 0;
   out_5946100134082923473[288] = 0;
   out_5946100134082923473[289] = 0;
   out_5946100134082923473[290] = 0;
   out_5946100134082923473[291] = 0;
   out_5946100134082923473[292] = 0;
   out_5946100134082923473[293] = 0;
   out_5946100134082923473[294] = 0;
   out_5946100134082923473[295] = 0;
   out_5946100134082923473[296] = 0;
   out_5946100134082923473[297] = 0;
   out_5946100134082923473[298] = 0;
   out_5946100134082923473[299] = 0;
   out_5946100134082923473[300] = 0;
   out_5946100134082923473[301] = 0;
   out_5946100134082923473[302] = 0;
   out_5946100134082923473[303] = 0;
   out_5946100134082923473[304] = 1;
   out_5946100134082923473[305] = 0;
   out_5946100134082923473[306] = 0;
   out_5946100134082923473[307] = 0;
   out_5946100134082923473[308] = 0;
   out_5946100134082923473[309] = 0;
   out_5946100134082923473[310] = 0;
   out_5946100134082923473[311] = 0;
   out_5946100134082923473[312] = 0;
   out_5946100134082923473[313] = 0;
   out_5946100134082923473[314] = 0;
   out_5946100134082923473[315] = 0;
   out_5946100134082923473[316] = 0;
   out_5946100134082923473[317] = 0;
   out_5946100134082923473[318] = 0;
   out_5946100134082923473[319] = 0;
   out_5946100134082923473[320] = 0;
   out_5946100134082923473[321] = 0;
   out_5946100134082923473[322] = 0;
   out_5946100134082923473[323] = 1;
}
void h_4(double *state, double *unused, double *out_7895468860031348123) {
   out_7895468860031348123[0] = state[6] + state[9];
   out_7895468860031348123[1] = state[7] + state[10];
   out_7895468860031348123[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4699468911280290176) {
   out_4699468911280290176[0] = 0;
   out_4699468911280290176[1] = 0;
   out_4699468911280290176[2] = 0;
   out_4699468911280290176[3] = 0;
   out_4699468911280290176[4] = 0;
   out_4699468911280290176[5] = 0;
   out_4699468911280290176[6] = 1;
   out_4699468911280290176[7] = 0;
   out_4699468911280290176[8] = 0;
   out_4699468911280290176[9] = 1;
   out_4699468911280290176[10] = 0;
   out_4699468911280290176[11] = 0;
   out_4699468911280290176[12] = 0;
   out_4699468911280290176[13] = 0;
   out_4699468911280290176[14] = 0;
   out_4699468911280290176[15] = 0;
   out_4699468911280290176[16] = 0;
   out_4699468911280290176[17] = 0;
   out_4699468911280290176[18] = 0;
   out_4699468911280290176[19] = 0;
   out_4699468911280290176[20] = 0;
   out_4699468911280290176[21] = 0;
   out_4699468911280290176[22] = 0;
   out_4699468911280290176[23] = 0;
   out_4699468911280290176[24] = 0;
   out_4699468911280290176[25] = 1;
   out_4699468911280290176[26] = 0;
   out_4699468911280290176[27] = 0;
   out_4699468911280290176[28] = 1;
   out_4699468911280290176[29] = 0;
   out_4699468911280290176[30] = 0;
   out_4699468911280290176[31] = 0;
   out_4699468911280290176[32] = 0;
   out_4699468911280290176[33] = 0;
   out_4699468911280290176[34] = 0;
   out_4699468911280290176[35] = 0;
   out_4699468911280290176[36] = 0;
   out_4699468911280290176[37] = 0;
   out_4699468911280290176[38] = 0;
   out_4699468911280290176[39] = 0;
   out_4699468911280290176[40] = 0;
   out_4699468911280290176[41] = 0;
   out_4699468911280290176[42] = 0;
   out_4699468911280290176[43] = 0;
   out_4699468911280290176[44] = 1;
   out_4699468911280290176[45] = 0;
   out_4699468911280290176[46] = 0;
   out_4699468911280290176[47] = 1;
   out_4699468911280290176[48] = 0;
   out_4699468911280290176[49] = 0;
   out_4699468911280290176[50] = 0;
   out_4699468911280290176[51] = 0;
   out_4699468911280290176[52] = 0;
   out_4699468911280290176[53] = 0;
}
void h_10(double *state, double *unused, double *out_7051420194440758803) {
   out_7051420194440758803[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_7051420194440758803[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_7051420194440758803[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_181799554460224071) {
   out_181799554460224071[0] = 0;
   out_181799554460224071[1] = 9.8100000000000005*cos(state[1]);
   out_181799554460224071[2] = 0;
   out_181799554460224071[3] = 0;
   out_181799554460224071[4] = -state[8];
   out_181799554460224071[5] = state[7];
   out_181799554460224071[6] = 0;
   out_181799554460224071[7] = state[5];
   out_181799554460224071[8] = -state[4];
   out_181799554460224071[9] = 0;
   out_181799554460224071[10] = 0;
   out_181799554460224071[11] = 0;
   out_181799554460224071[12] = 1;
   out_181799554460224071[13] = 0;
   out_181799554460224071[14] = 0;
   out_181799554460224071[15] = 1;
   out_181799554460224071[16] = 0;
   out_181799554460224071[17] = 0;
   out_181799554460224071[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_181799554460224071[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_181799554460224071[20] = 0;
   out_181799554460224071[21] = state[8];
   out_181799554460224071[22] = 0;
   out_181799554460224071[23] = -state[6];
   out_181799554460224071[24] = -state[5];
   out_181799554460224071[25] = 0;
   out_181799554460224071[26] = state[3];
   out_181799554460224071[27] = 0;
   out_181799554460224071[28] = 0;
   out_181799554460224071[29] = 0;
   out_181799554460224071[30] = 0;
   out_181799554460224071[31] = 1;
   out_181799554460224071[32] = 0;
   out_181799554460224071[33] = 0;
   out_181799554460224071[34] = 1;
   out_181799554460224071[35] = 0;
   out_181799554460224071[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_181799554460224071[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_181799554460224071[38] = 0;
   out_181799554460224071[39] = -state[7];
   out_181799554460224071[40] = state[6];
   out_181799554460224071[41] = 0;
   out_181799554460224071[42] = state[4];
   out_181799554460224071[43] = -state[3];
   out_181799554460224071[44] = 0;
   out_181799554460224071[45] = 0;
   out_181799554460224071[46] = 0;
   out_181799554460224071[47] = 0;
   out_181799554460224071[48] = 0;
   out_181799554460224071[49] = 0;
   out_181799554460224071[50] = 1;
   out_181799554460224071[51] = 0;
   out_181799554460224071[52] = 0;
   out_181799554460224071[53] = 1;
}
void h_13(double *state, double *unused, double *out_1850536561694260921) {
   out_1850536561694260921[0] = state[3];
   out_1850536561694260921[1] = state[4];
   out_1850536561694260921[2] = state[5];
}
void H_13(double *state, double *unused, double *out_7911742736612622977) {
   out_7911742736612622977[0] = 0;
   out_7911742736612622977[1] = 0;
   out_7911742736612622977[2] = 0;
   out_7911742736612622977[3] = 1;
   out_7911742736612622977[4] = 0;
   out_7911742736612622977[5] = 0;
   out_7911742736612622977[6] = 0;
   out_7911742736612622977[7] = 0;
   out_7911742736612622977[8] = 0;
   out_7911742736612622977[9] = 0;
   out_7911742736612622977[10] = 0;
   out_7911742736612622977[11] = 0;
   out_7911742736612622977[12] = 0;
   out_7911742736612622977[13] = 0;
   out_7911742736612622977[14] = 0;
   out_7911742736612622977[15] = 0;
   out_7911742736612622977[16] = 0;
   out_7911742736612622977[17] = 0;
   out_7911742736612622977[18] = 0;
   out_7911742736612622977[19] = 0;
   out_7911742736612622977[20] = 0;
   out_7911742736612622977[21] = 0;
   out_7911742736612622977[22] = 1;
   out_7911742736612622977[23] = 0;
   out_7911742736612622977[24] = 0;
   out_7911742736612622977[25] = 0;
   out_7911742736612622977[26] = 0;
   out_7911742736612622977[27] = 0;
   out_7911742736612622977[28] = 0;
   out_7911742736612622977[29] = 0;
   out_7911742736612622977[30] = 0;
   out_7911742736612622977[31] = 0;
   out_7911742736612622977[32] = 0;
   out_7911742736612622977[33] = 0;
   out_7911742736612622977[34] = 0;
   out_7911742736612622977[35] = 0;
   out_7911742736612622977[36] = 0;
   out_7911742736612622977[37] = 0;
   out_7911742736612622977[38] = 0;
   out_7911742736612622977[39] = 0;
   out_7911742736612622977[40] = 0;
   out_7911742736612622977[41] = 1;
   out_7911742736612622977[42] = 0;
   out_7911742736612622977[43] = 0;
   out_7911742736612622977[44] = 0;
   out_7911742736612622977[45] = 0;
   out_7911742736612622977[46] = 0;
   out_7911742736612622977[47] = 0;
   out_7911742736612622977[48] = 0;
   out_7911742736612622977[49] = 0;
   out_7911742736612622977[50] = 0;
   out_7911742736612622977[51] = 0;
   out_7911742736612622977[52] = 0;
   out_7911742736612622977[53] = 0;
}
void h_14(double *state, double *unused, double *out_8940417508633322111) {
   out_8940417508633322111[0] = state[6];
   out_8940417508633322111[1] = state[7];
   out_8940417508633322111[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8662709767619774705) {
   out_8662709767619774705[0] = 0;
   out_8662709767619774705[1] = 0;
   out_8662709767619774705[2] = 0;
   out_8662709767619774705[3] = 0;
   out_8662709767619774705[4] = 0;
   out_8662709767619774705[5] = 0;
   out_8662709767619774705[6] = 1;
   out_8662709767619774705[7] = 0;
   out_8662709767619774705[8] = 0;
   out_8662709767619774705[9] = 0;
   out_8662709767619774705[10] = 0;
   out_8662709767619774705[11] = 0;
   out_8662709767619774705[12] = 0;
   out_8662709767619774705[13] = 0;
   out_8662709767619774705[14] = 0;
   out_8662709767619774705[15] = 0;
   out_8662709767619774705[16] = 0;
   out_8662709767619774705[17] = 0;
   out_8662709767619774705[18] = 0;
   out_8662709767619774705[19] = 0;
   out_8662709767619774705[20] = 0;
   out_8662709767619774705[21] = 0;
   out_8662709767619774705[22] = 0;
   out_8662709767619774705[23] = 0;
   out_8662709767619774705[24] = 0;
   out_8662709767619774705[25] = 1;
   out_8662709767619774705[26] = 0;
   out_8662709767619774705[27] = 0;
   out_8662709767619774705[28] = 0;
   out_8662709767619774705[29] = 0;
   out_8662709767619774705[30] = 0;
   out_8662709767619774705[31] = 0;
   out_8662709767619774705[32] = 0;
   out_8662709767619774705[33] = 0;
   out_8662709767619774705[34] = 0;
   out_8662709767619774705[35] = 0;
   out_8662709767619774705[36] = 0;
   out_8662709767619774705[37] = 0;
   out_8662709767619774705[38] = 0;
   out_8662709767619774705[39] = 0;
   out_8662709767619774705[40] = 0;
   out_8662709767619774705[41] = 0;
   out_8662709767619774705[42] = 0;
   out_8662709767619774705[43] = 0;
   out_8662709767619774705[44] = 1;
   out_8662709767619774705[45] = 0;
   out_8662709767619774705[46] = 0;
   out_8662709767619774705[47] = 0;
   out_8662709767619774705[48] = 0;
   out_8662709767619774705[49] = 0;
   out_8662709767619774705[50] = 0;
   out_8662709767619774705[51] = 0;
   out_8662709767619774705[52] = 0;
   out_8662709767619774705[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_4423077432163082570) {
  err_fun(nom_x, delta_x, out_4423077432163082570);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3066625947211960781) {
  inv_err_fun(nom_x, true_x, out_3066625947211960781);
}
void pose_H_mod_fun(double *state, double *out_7899193355677302719) {
  H_mod_fun(state, out_7899193355677302719);
}
void pose_f_fun(double *state, double dt, double *out_1767716959874096227) {
  f_fun(state,  dt, out_1767716959874096227);
}
void pose_F_fun(double *state, double dt, double *out_5946100134082923473) {
  F_fun(state,  dt, out_5946100134082923473);
}
void pose_h_4(double *state, double *unused, double *out_7895468860031348123) {
  h_4(state, unused, out_7895468860031348123);
}
void pose_H_4(double *state, double *unused, double *out_4699468911280290176) {
  H_4(state, unused, out_4699468911280290176);
}
void pose_h_10(double *state, double *unused, double *out_7051420194440758803) {
  h_10(state, unused, out_7051420194440758803);
}
void pose_H_10(double *state, double *unused, double *out_181799554460224071) {
  H_10(state, unused, out_181799554460224071);
}
void pose_h_13(double *state, double *unused, double *out_1850536561694260921) {
  h_13(state, unused, out_1850536561694260921);
}
void pose_H_13(double *state, double *unused, double *out_7911742736612622977) {
  H_13(state, unused, out_7911742736612622977);
}
void pose_h_14(double *state, double *unused, double *out_8940417508633322111) {
  h_14(state, unused, out_8940417508633322111);
}
void pose_H_14(double *state, double *unused, double *out_8662709767619774705) {
  H_14(state, unused, out_8662709767619774705);
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
