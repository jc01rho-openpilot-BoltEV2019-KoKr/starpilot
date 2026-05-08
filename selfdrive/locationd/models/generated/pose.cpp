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
void err_fun(double *nom_x, double *delta_x, double *out_2526150130430510074) {
   out_2526150130430510074[0] = delta_x[0] + nom_x[0];
   out_2526150130430510074[1] = delta_x[1] + nom_x[1];
   out_2526150130430510074[2] = delta_x[2] + nom_x[2];
   out_2526150130430510074[3] = delta_x[3] + nom_x[3];
   out_2526150130430510074[4] = delta_x[4] + nom_x[4];
   out_2526150130430510074[5] = delta_x[5] + nom_x[5];
   out_2526150130430510074[6] = delta_x[6] + nom_x[6];
   out_2526150130430510074[7] = delta_x[7] + nom_x[7];
   out_2526150130430510074[8] = delta_x[8] + nom_x[8];
   out_2526150130430510074[9] = delta_x[9] + nom_x[9];
   out_2526150130430510074[10] = delta_x[10] + nom_x[10];
   out_2526150130430510074[11] = delta_x[11] + nom_x[11];
   out_2526150130430510074[12] = delta_x[12] + nom_x[12];
   out_2526150130430510074[13] = delta_x[13] + nom_x[13];
   out_2526150130430510074[14] = delta_x[14] + nom_x[14];
   out_2526150130430510074[15] = delta_x[15] + nom_x[15];
   out_2526150130430510074[16] = delta_x[16] + nom_x[16];
   out_2526150130430510074[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3515561648914426109) {
   out_3515561648914426109[0] = -nom_x[0] + true_x[0];
   out_3515561648914426109[1] = -nom_x[1] + true_x[1];
   out_3515561648914426109[2] = -nom_x[2] + true_x[2];
   out_3515561648914426109[3] = -nom_x[3] + true_x[3];
   out_3515561648914426109[4] = -nom_x[4] + true_x[4];
   out_3515561648914426109[5] = -nom_x[5] + true_x[5];
   out_3515561648914426109[6] = -nom_x[6] + true_x[6];
   out_3515561648914426109[7] = -nom_x[7] + true_x[7];
   out_3515561648914426109[8] = -nom_x[8] + true_x[8];
   out_3515561648914426109[9] = -nom_x[9] + true_x[9];
   out_3515561648914426109[10] = -nom_x[10] + true_x[10];
   out_3515561648914426109[11] = -nom_x[11] + true_x[11];
   out_3515561648914426109[12] = -nom_x[12] + true_x[12];
   out_3515561648914426109[13] = -nom_x[13] + true_x[13];
   out_3515561648914426109[14] = -nom_x[14] + true_x[14];
   out_3515561648914426109[15] = -nom_x[15] + true_x[15];
   out_3515561648914426109[16] = -nom_x[16] + true_x[16];
   out_3515561648914426109[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_6056162720073724257) {
   out_6056162720073724257[0] = 1.0;
   out_6056162720073724257[1] = 0.0;
   out_6056162720073724257[2] = 0.0;
   out_6056162720073724257[3] = 0.0;
   out_6056162720073724257[4] = 0.0;
   out_6056162720073724257[5] = 0.0;
   out_6056162720073724257[6] = 0.0;
   out_6056162720073724257[7] = 0.0;
   out_6056162720073724257[8] = 0.0;
   out_6056162720073724257[9] = 0.0;
   out_6056162720073724257[10] = 0.0;
   out_6056162720073724257[11] = 0.0;
   out_6056162720073724257[12] = 0.0;
   out_6056162720073724257[13] = 0.0;
   out_6056162720073724257[14] = 0.0;
   out_6056162720073724257[15] = 0.0;
   out_6056162720073724257[16] = 0.0;
   out_6056162720073724257[17] = 0.0;
   out_6056162720073724257[18] = 0.0;
   out_6056162720073724257[19] = 1.0;
   out_6056162720073724257[20] = 0.0;
   out_6056162720073724257[21] = 0.0;
   out_6056162720073724257[22] = 0.0;
   out_6056162720073724257[23] = 0.0;
   out_6056162720073724257[24] = 0.0;
   out_6056162720073724257[25] = 0.0;
   out_6056162720073724257[26] = 0.0;
   out_6056162720073724257[27] = 0.0;
   out_6056162720073724257[28] = 0.0;
   out_6056162720073724257[29] = 0.0;
   out_6056162720073724257[30] = 0.0;
   out_6056162720073724257[31] = 0.0;
   out_6056162720073724257[32] = 0.0;
   out_6056162720073724257[33] = 0.0;
   out_6056162720073724257[34] = 0.0;
   out_6056162720073724257[35] = 0.0;
   out_6056162720073724257[36] = 0.0;
   out_6056162720073724257[37] = 0.0;
   out_6056162720073724257[38] = 1.0;
   out_6056162720073724257[39] = 0.0;
   out_6056162720073724257[40] = 0.0;
   out_6056162720073724257[41] = 0.0;
   out_6056162720073724257[42] = 0.0;
   out_6056162720073724257[43] = 0.0;
   out_6056162720073724257[44] = 0.0;
   out_6056162720073724257[45] = 0.0;
   out_6056162720073724257[46] = 0.0;
   out_6056162720073724257[47] = 0.0;
   out_6056162720073724257[48] = 0.0;
   out_6056162720073724257[49] = 0.0;
   out_6056162720073724257[50] = 0.0;
   out_6056162720073724257[51] = 0.0;
   out_6056162720073724257[52] = 0.0;
   out_6056162720073724257[53] = 0.0;
   out_6056162720073724257[54] = 0.0;
   out_6056162720073724257[55] = 0.0;
   out_6056162720073724257[56] = 0.0;
   out_6056162720073724257[57] = 1.0;
   out_6056162720073724257[58] = 0.0;
   out_6056162720073724257[59] = 0.0;
   out_6056162720073724257[60] = 0.0;
   out_6056162720073724257[61] = 0.0;
   out_6056162720073724257[62] = 0.0;
   out_6056162720073724257[63] = 0.0;
   out_6056162720073724257[64] = 0.0;
   out_6056162720073724257[65] = 0.0;
   out_6056162720073724257[66] = 0.0;
   out_6056162720073724257[67] = 0.0;
   out_6056162720073724257[68] = 0.0;
   out_6056162720073724257[69] = 0.0;
   out_6056162720073724257[70] = 0.0;
   out_6056162720073724257[71] = 0.0;
   out_6056162720073724257[72] = 0.0;
   out_6056162720073724257[73] = 0.0;
   out_6056162720073724257[74] = 0.0;
   out_6056162720073724257[75] = 0.0;
   out_6056162720073724257[76] = 1.0;
   out_6056162720073724257[77] = 0.0;
   out_6056162720073724257[78] = 0.0;
   out_6056162720073724257[79] = 0.0;
   out_6056162720073724257[80] = 0.0;
   out_6056162720073724257[81] = 0.0;
   out_6056162720073724257[82] = 0.0;
   out_6056162720073724257[83] = 0.0;
   out_6056162720073724257[84] = 0.0;
   out_6056162720073724257[85] = 0.0;
   out_6056162720073724257[86] = 0.0;
   out_6056162720073724257[87] = 0.0;
   out_6056162720073724257[88] = 0.0;
   out_6056162720073724257[89] = 0.0;
   out_6056162720073724257[90] = 0.0;
   out_6056162720073724257[91] = 0.0;
   out_6056162720073724257[92] = 0.0;
   out_6056162720073724257[93] = 0.0;
   out_6056162720073724257[94] = 0.0;
   out_6056162720073724257[95] = 1.0;
   out_6056162720073724257[96] = 0.0;
   out_6056162720073724257[97] = 0.0;
   out_6056162720073724257[98] = 0.0;
   out_6056162720073724257[99] = 0.0;
   out_6056162720073724257[100] = 0.0;
   out_6056162720073724257[101] = 0.0;
   out_6056162720073724257[102] = 0.0;
   out_6056162720073724257[103] = 0.0;
   out_6056162720073724257[104] = 0.0;
   out_6056162720073724257[105] = 0.0;
   out_6056162720073724257[106] = 0.0;
   out_6056162720073724257[107] = 0.0;
   out_6056162720073724257[108] = 0.0;
   out_6056162720073724257[109] = 0.0;
   out_6056162720073724257[110] = 0.0;
   out_6056162720073724257[111] = 0.0;
   out_6056162720073724257[112] = 0.0;
   out_6056162720073724257[113] = 0.0;
   out_6056162720073724257[114] = 1.0;
   out_6056162720073724257[115] = 0.0;
   out_6056162720073724257[116] = 0.0;
   out_6056162720073724257[117] = 0.0;
   out_6056162720073724257[118] = 0.0;
   out_6056162720073724257[119] = 0.0;
   out_6056162720073724257[120] = 0.0;
   out_6056162720073724257[121] = 0.0;
   out_6056162720073724257[122] = 0.0;
   out_6056162720073724257[123] = 0.0;
   out_6056162720073724257[124] = 0.0;
   out_6056162720073724257[125] = 0.0;
   out_6056162720073724257[126] = 0.0;
   out_6056162720073724257[127] = 0.0;
   out_6056162720073724257[128] = 0.0;
   out_6056162720073724257[129] = 0.0;
   out_6056162720073724257[130] = 0.0;
   out_6056162720073724257[131] = 0.0;
   out_6056162720073724257[132] = 0.0;
   out_6056162720073724257[133] = 1.0;
   out_6056162720073724257[134] = 0.0;
   out_6056162720073724257[135] = 0.0;
   out_6056162720073724257[136] = 0.0;
   out_6056162720073724257[137] = 0.0;
   out_6056162720073724257[138] = 0.0;
   out_6056162720073724257[139] = 0.0;
   out_6056162720073724257[140] = 0.0;
   out_6056162720073724257[141] = 0.0;
   out_6056162720073724257[142] = 0.0;
   out_6056162720073724257[143] = 0.0;
   out_6056162720073724257[144] = 0.0;
   out_6056162720073724257[145] = 0.0;
   out_6056162720073724257[146] = 0.0;
   out_6056162720073724257[147] = 0.0;
   out_6056162720073724257[148] = 0.0;
   out_6056162720073724257[149] = 0.0;
   out_6056162720073724257[150] = 0.0;
   out_6056162720073724257[151] = 0.0;
   out_6056162720073724257[152] = 1.0;
   out_6056162720073724257[153] = 0.0;
   out_6056162720073724257[154] = 0.0;
   out_6056162720073724257[155] = 0.0;
   out_6056162720073724257[156] = 0.0;
   out_6056162720073724257[157] = 0.0;
   out_6056162720073724257[158] = 0.0;
   out_6056162720073724257[159] = 0.0;
   out_6056162720073724257[160] = 0.0;
   out_6056162720073724257[161] = 0.0;
   out_6056162720073724257[162] = 0.0;
   out_6056162720073724257[163] = 0.0;
   out_6056162720073724257[164] = 0.0;
   out_6056162720073724257[165] = 0.0;
   out_6056162720073724257[166] = 0.0;
   out_6056162720073724257[167] = 0.0;
   out_6056162720073724257[168] = 0.0;
   out_6056162720073724257[169] = 0.0;
   out_6056162720073724257[170] = 0.0;
   out_6056162720073724257[171] = 1.0;
   out_6056162720073724257[172] = 0.0;
   out_6056162720073724257[173] = 0.0;
   out_6056162720073724257[174] = 0.0;
   out_6056162720073724257[175] = 0.0;
   out_6056162720073724257[176] = 0.0;
   out_6056162720073724257[177] = 0.0;
   out_6056162720073724257[178] = 0.0;
   out_6056162720073724257[179] = 0.0;
   out_6056162720073724257[180] = 0.0;
   out_6056162720073724257[181] = 0.0;
   out_6056162720073724257[182] = 0.0;
   out_6056162720073724257[183] = 0.0;
   out_6056162720073724257[184] = 0.0;
   out_6056162720073724257[185] = 0.0;
   out_6056162720073724257[186] = 0.0;
   out_6056162720073724257[187] = 0.0;
   out_6056162720073724257[188] = 0.0;
   out_6056162720073724257[189] = 0.0;
   out_6056162720073724257[190] = 1.0;
   out_6056162720073724257[191] = 0.0;
   out_6056162720073724257[192] = 0.0;
   out_6056162720073724257[193] = 0.0;
   out_6056162720073724257[194] = 0.0;
   out_6056162720073724257[195] = 0.0;
   out_6056162720073724257[196] = 0.0;
   out_6056162720073724257[197] = 0.0;
   out_6056162720073724257[198] = 0.0;
   out_6056162720073724257[199] = 0.0;
   out_6056162720073724257[200] = 0.0;
   out_6056162720073724257[201] = 0.0;
   out_6056162720073724257[202] = 0.0;
   out_6056162720073724257[203] = 0.0;
   out_6056162720073724257[204] = 0.0;
   out_6056162720073724257[205] = 0.0;
   out_6056162720073724257[206] = 0.0;
   out_6056162720073724257[207] = 0.0;
   out_6056162720073724257[208] = 0.0;
   out_6056162720073724257[209] = 1.0;
   out_6056162720073724257[210] = 0.0;
   out_6056162720073724257[211] = 0.0;
   out_6056162720073724257[212] = 0.0;
   out_6056162720073724257[213] = 0.0;
   out_6056162720073724257[214] = 0.0;
   out_6056162720073724257[215] = 0.0;
   out_6056162720073724257[216] = 0.0;
   out_6056162720073724257[217] = 0.0;
   out_6056162720073724257[218] = 0.0;
   out_6056162720073724257[219] = 0.0;
   out_6056162720073724257[220] = 0.0;
   out_6056162720073724257[221] = 0.0;
   out_6056162720073724257[222] = 0.0;
   out_6056162720073724257[223] = 0.0;
   out_6056162720073724257[224] = 0.0;
   out_6056162720073724257[225] = 0.0;
   out_6056162720073724257[226] = 0.0;
   out_6056162720073724257[227] = 0.0;
   out_6056162720073724257[228] = 1.0;
   out_6056162720073724257[229] = 0.0;
   out_6056162720073724257[230] = 0.0;
   out_6056162720073724257[231] = 0.0;
   out_6056162720073724257[232] = 0.0;
   out_6056162720073724257[233] = 0.0;
   out_6056162720073724257[234] = 0.0;
   out_6056162720073724257[235] = 0.0;
   out_6056162720073724257[236] = 0.0;
   out_6056162720073724257[237] = 0.0;
   out_6056162720073724257[238] = 0.0;
   out_6056162720073724257[239] = 0.0;
   out_6056162720073724257[240] = 0.0;
   out_6056162720073724257[241] = 0.0;
   out_6056162720073724257[242] = 0.0;
   out_6056162720073724257[243] = 0.0;
   out_6056162720073724257[244] = 0.0;
   out_6056162720073724257[245] = 0.0;
   out_6056162720073724257[246] = 0.0;
   out_6056162720073724257[247] = 1.0;
   out_6056162720073724257[248] = 0.0;
   out_6056162720073724257[249] = 0.0;
   out_6056162720073724257[250] = 0.0;
   out_6056162720073724257[251] = 0.0;
   out_6056162720073724257[252] = 0.0;
   out_6056162720073724257[253] = 0.0;
   out_6056162720073724257[254] = 0.0;
   out_6056162720073724257[255] = 0.0;
   out_6056162720073724257[256] = 0.0;
   out_6056162720073724257[257] = 0.0;
   out_6056162720073724257[258] = 0.0;
   out_6056162720073724257[259] = 0.0;
   out_6056162720073724257[260] = 0.0;
   out_6056162720073724257[261] = 0.0;
   out_6056162720073724257[262] = 0.0;
   out_6056162720073724257[263] = 0.0;
   out_6056162720073724257[264] = 0.0;
   out_6056162720073724257[265] = 0.0;
   out_6056162720073724257[266] = 1.0;
   out_6056162720073724257[267] = 0.0;
   out_6056162720073724257[268] = 0.0;
   out_6056162720073724257[269] = 0.0;
   out_6056162720073724257[270] = 0.0;
   out_6056162720073724257[271] = 0.0;
   out_6056162720073724257[272] = 0.0;
   out_6056162720073724257[273] = 0.0;
   out_6056162720073724257[274] = 0.0;
   out_6056162720073724257[275] = 0.0;
   out_6056162720073724257[276] = 0.0;
   out_6056162720073724257[277] = 0.0;
   out_6056162720073724257[278] = 0.0;
   out_6056162720073724257[279] = 0.0;
   out_6056162720073724257[280] = 0.0;
   out_6056162720073724257[281] = 0.0;
   out_6056162720073724257[282] = 0.0;
   out_6056162720073724257[283] = 0.0;
   out_6056162720073724257[284] = 0.0;
   out_6056162720073724257[285] = 1.0;
   out_6056162720073724257[286] = 0.0;
   out_6056162720073724257[287] = 0.0;
   out_6056162720073724257[288] = 0.0;
   out_6056162720073724257[289] = 0.0;
   out_6056162720073724257[290] = 0.0;
   out_6056162720073724257[291] = 0.0;
   out_6056162720073724257[292] = 0.0;
   out_6056162720073724257[293] = 0.0;
   out_6056162720073724257[294] = 0.0;
   out_6056162720073724257[295] = 0.0;
   out_6056162720073724257[296] = 0.0;
   out_6056162720073724257[297] = 0.0;
   out_6056162720073724257[298] = 0.0;
   out_6056162720073724257[299] = 0.0;
   out_6056162720073724257[300] = 0.0;
   out_6056162720073724257[301] = 0.0;
   out_6056162720073724257[302] = 0.0;
   out_6056162720073724257[303] = 0.0;
   out_6056162720073724257[304] = 1.0;
   out_6056162720073724257[305] = 0.0;
   out_6056162720073724257[306] = 0.0;
   out_6056162720073724257[307] = 0.0;
   out_6056162720073724257[308] = 0.0;
   out_6056162720073724257[309] = 0.0;
   out_6056162720073724257[310] = 0.0;
   out_6056162720073724257[311] = 0.0;
   out_6056162720073724257[312] = 0.0;
   out_6056162720073724257[313] = 0.0;
   out_6056162720073724257[314] = 0.0;
   out_6056162720073724257[315] = 0.0;
   out_6056162720073724257[316] = 0.0;
   out_6056162720073724257[317] = 0.0;
   out_6056162720073724257[318] = 0.0;
   out_6056162720073724257[319] = 0.0;
   out_6056162720073724257[320] = 0.0;
   out_6056162720073724257[321] = 0.0;
   out_6056162720073724257[322] = 0.0;
   out_6056162720073724257[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8780284750928315681) {
   out_8780284750928315681[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8780284750928315681[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8780284750928315681[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8780284750928315681[3] = dt*state[12] + state[3];
   out_8780284750928315681[4] = dt*state[13] + state[4];
   out_8780284750928315681[5] = dt*state[14] + state[5];
   out_8780284750928315681[6] = state[6];
   out_8780284750928315681[7] = state[7];
   out_8780284750928315681[8] = state[8];
   out_8780284750928315681[9] = state[9];
   out_8780284750928315681[10] = state[10];
   out_8780284750928315681[11] = state[11];
   out_8780284750928315681[12] = state[12];
   out_8780284750928315681[13] = state[13];
   out_8780284750928315681[14] = state[14];
   out_8780284750928315681[15] = state[15];
   out_8780284750928315681[16] = state[16];
   out_8780284750928315681[17] = state[17];
}
void F_fun(double *state, double dt, double *out_1516035527731464330) {
   out_1516035527731464330[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1516035527731464330[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1516035527731464330[2] = 0;
   out_1516035527731464330[3] = 0;
   out_1516035527731464330[4] = 0;
   out_1516035527731464330[5] = 0;
   out_1516035527731464330[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1516035527731464330[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1516035527731464330[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1516035527731464330[9] = 0;
   out_1516035527731464330[10] = 0;
   out_1516035527731464330[11] = 0;
   out_1516035527731464330[12] = 0;
   out_1516035527731464330[13] = 0;
   out_1516035527731464330[14] = 0;
   out_1516035527731464330[15] = 0;
   out_1516035527731464330[16] = 0;
   out_1516035527731464330[17] = 0;
   out_1516035527731464330[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1516035527731464330[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1516035527731464330[20] = 0;
   out_1516035527731464330[21] = 0;
   out_1516035527731464330[22] = 0;
   out_1516035527731464330[23] = 0;
   out_1516035527731464330[24] = 0;
   out_1516035527731464330[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1516035527731464330[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1516035527731464330[27] = 0;
   out_1516035527731464330[28] = 0;
   out_1516035527731464330[29] = 0;
   out_1516035527731464330[30] = 0;
   out_1516035527731464330[31] = 0;
   out_1516035527731464330[32] = 0;
   out_1516035527731464330[33] = 0;
   out_1516035527731464330[34] = 0;
   out_1516035527731464330[35] = 0;
   out_1516035527731464330[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1516035527731464330[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1516035527731464330[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1516035527731464330[39] = 0;
   out_1516035527731464330[40] = 0;
   out_1516035527731464330[41] = 0;
   out_1516035527731464330[42] = 0;
   out_1516035527731464330[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1516035527731464330[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1516035527731464330[45] = 0;
   out_1516035527731464330[46] = 0;
   out_1516035527731464330[47] = 0;
   out_1516035527731464330[48] = 0;
   out_1516035527731464330[49] = 0;
   out_1516035527731464330[50] = 0;
   out_1516035527731464330[51] = 0;
   out_1516035527731464330[52] = 0;
   out_1516035527731464330[53] = 0;
   out_1516035527731464330[54] = 0;
   out_1516035527731464330[55] = 0;
   out_1516035527731464330[56] = 0;
   out_1516035527731464330[57] = 1;
   out_1516035527731464330[58] = 0;
   out_1516035527731464330[59] = 0;
   out_1516035527731464330[60] = 0;
   out_1516035527731464330[61] = 0;
   out_1516035527731464330[62] = 0;
   out_1516035527731464330[63] = 0;
   out_1516035527731464330[64] = 0;
   out_1516035527731464330[65] = 0;
   out_1516035527731464330[66] = dt;
   out_1516035527731464330[67] = 0;
   out_1516035527731464330[68] = 0;
   out_1516035527731464330[69] = 0;
   out_1516035527731464330[70] = 0;
   out_1516035527731464330[71] = 0;
   out_1516035527731464330[72] = 0;
   out_1516035527731464330[73] = 0;
   out_1516035527731464330[74] = 0;
   out_1516035527731464330[75] = 0;
   out_1516035527731464330[76] = 1;
   out_1516035527731464330[77] = 0;
   out_1516035527731464330[78] = 0;
   out_1516035527731464330[79] = 0;
   out_1516035527731464330[80] = 0;
   out_1516035527731464330[81] = 0;
   out_1516035527731464330[82] = 0;
   out_1516035527731464330[83] = 0;
   out_1516035527731464330[84] = 0;
   out_1516035527731464330[85] = dt;
   out_1516035527731464330[86] = 0;
   out_1516035527731464330[87] = 0;
   out_1516035527731464330[88] = 0;
   out_1516035527731464330[89] = 0;
   out_1516035527731464330[90] = 0;
   out_1516035527731464330[91] = 0;
   out_1516035527731464330[92] = 0;
   out_1516035527731464330[93] = 0;
   out_1516035527731464330[94] = 0;
   out_1516035527731464330[95] = 1;
   out_1516035527731464330[96] = 0;
   out_1516035527731464330[97] = 0;
   out_1516035527731464330[98] = 0;
   out_1516035527731464330[99] = 0;
   out_1516035527731464330[100] = 0;
   out_1516035527731464330[101] = 0;
   out_1516035527731464330[102] = 0;
   out_1516035527731464330[103] = 0;
   out_1516035527731464330[104] = dt;
   out_1516035527731464330[105] = 0;
   out_1516035527731464330[106] = 0;
   out_1516035527731464330[107] = 0;
   out_1516035527731464330[108] = 0;
   out_1516035527731464330[109] = 0;
   out_1516035527731464330[110] = 0;
   out_1516035527731464330[111] = 0;
   out_1516035527731464330[112] = 0;
   out_1516035527731464330[113] = 0;
   out_1516035527731464330[114] = 1;
   out_1516035527731464330[115] = 0;
   out_1516035527731464330[116] = 0;
   out_1516035527731464330[117] = 0;
   out_1516035527731464330[118] = 0;
   out_1516035527731464330[119] = 0;
   out_1516035527731464330[120] = 0;
   out_1516035527731464330[121] = 0;
   out_1516035527731464330[122] = 0;
   out_1516035527731464330[123] = 0;
   out_1516035527731464330[124] = 0;
   out_1516035527731464330[125] = 0;
   out_1516035527731464330[126] = 0;
   out_1516035527731464330[127] = 0;
   out_1516035527731464330[128] = 0;
   out_1516035527731464330[129] = 0;
   out_1516035527731464330[130] = 0;
   out_1516035527731464330[131] = 0;
   out_1516035527731464330[132] = 0;
   out_1516035527731464330[133] = 1;
   out_1516035527731464330[134] = 0;
   out_1516035527731464330[135] = 0;
   out_1516035527731464330[136] = 0;
   out_1516035527731464330[137] = 0;
   out_1516035527731464330[138] = 0;
   out_1516035527731464330[139] = 0;
   out_1516035527731464330[140] = 0;
   out_1516035527731464330[141] = 0;
   out_1516035527731464330[142] = 0;
   out_1516035527731464330[143] = 0;
   out_1516035527731464330[144] = 0;
   out_1516035527731464330[145] = 0;
   out_1516035527731464330[146] = 0;
   out_1516035527731464330[147] = 0;
   out_1516035527731464330[148] = 0;
   out_1516035527731464330[149] = 0;
   out_1516035527731464330[150] = 0;
   out_1516035527731464330[151] = 0;
   out_1516035527731464330[152] = 1;
   out_1516035527731464330[153] = 0;
   out_1516035527731464330[154] = 0;
   out_1516035527731464330[155] = 0;
   out_1516035527731464330[156] = 0;
   out_1516035527731464330[157] = 0;
   out_1516035527731464330[158] = 0;
   out_1516035527731464330[159] = 0;
   out_1516035527731464330[160] = 0;
   out_1516035527731464330[161] = 0;
   out_1516035527731464330[162] = 0;
   out_1516035527731464330[163] = 0;
   out_1516035527731464330[164] = 0;
   out_1516035527731464330[165] = 0;
   out_1516035527731464330[166] = 0;
   out_1516035527731464330[167] = 0;
   out_1516035527731464330[168] = 0;
   out_1516035527731464330[169] = 0;
   out_1516035527731464330[170] = 0;
   out_1516035527731464330[171] = 1;
   out_1516035527731464330[172] = 0;
   out_1516035527731464330[173] = 0;
   out_1516035527731464330[174] = 0;
   out_1516035527731464330[175] = 0;
   out_1516035527731464330[176] = 0;
   out_1516035527731464330[177] = 0;
   out_1516035527731464330[178] = 0;
   out_1516035527731464330[179] = 0;
   out_1516035527731464330[180] = 0;
   out_1516035527731464330[181] = 0;
   out_1516035527731464330[182] = 0;
   out_1516035527731464330[183] = 0;
   out_1516035527731464330[184] = 0;
   out_1516035527731464330[185] = 0;
   out_1516035527731464330[186] = 0;
   out_1516035527731464330[187] = 0;
   out_1516035527731464330[188] = 0;
   out_1516035527731464330[189] = 0;
   out_1516035527731464330[190] = 1;
   out_1516035527731464330[191] = 0;
   out_1516035527731464330[192] = 0;
   out_1516035527731464330[193] = 0;
   out_1516035527731464330[194] = 0;
   out_1516035527731464330[195] = 0;
   out_1516035527731464330[196] = 0;
   out_1516035527731464330[197] = 0;
   out_1516035527731464330[198] = 0;
   out_1516035527731464330[199] = 0;
   out_1516035527731464330[200] = 0;
   out_1516035527731464330[201] = 0;
   out_1516035527731464330[202] = 0;
   out_1516035527731464330[203] = 0;
   out_1516035527731464330[204] = 0;
   out_1516035527731464330[205] = 0;
   out_1516035527731464330[206] = 0;
   out_1516035527731464330[207] = 0;
   out_1516035527731464330[208] = 0;
   out_1516035527731464330[209] = 1;
   out_1516035527731464330[210] = 0;
   out_1516035527731464330[211] = 0;
   out_1516035527731464330[212] = 0;
   out_1516035527731464330[213] = 0;
   out_1516035527731464330[214] = 0;
   out_1516035527731464330[215] = 0;
   out_1516035527731464330[216] = 0;
   out_1516035527731464330[217] = 0;
   out_1516035527731464330[218] = 0;
   out_1516035527731464330[219] = 0;
   out_1516035527731464330[220] = 0;
   out_1516035527731464330[221] = 0;
   out_1516035527731464330[222] = 0;
   out_1516035527731464330[223] = 0;
   out_1516035527731464330[224] = 0;
   out_1516035527731464330[225] = 0;
   out_1516035527731464330[226] = 0;
   out_1516035527731464330[227] = 0;
   out_1516035527731464330[228] = 1;
   out_1516035527731464330[229] = 0;
   out_1516035527731464330[230] = 0;
   out_1516035527731464330[231] = 0;
   out_1516035527731464330[232] = 0;
   out_1516035527731464330[233] = 0;
   out_1516035527731464330[234] = 0;
   out_1516035527731464330[235] = 0;
   out_1516035527731464330[236] = 0;
   out_1516035527731464330[237] = 0;
   out_1516035527731464330[238] = 0;
   out_1516035527731464330[239] = 0;
   out_1516035527731464330[240] = 0;
   out_1516035527731464330[241] = 0;
   out_1516035527731464330[242] = 0;
   out_1516035527731464330[243] = 0;
   out_1516035527731464330[244] = 0;
   out_1516035527731464330[245] = 0;
   out_1516035527731464330[246] = 0;
   out_1516035527731464330[247] = 1;
   out_1516035527731464330[248] = 0;
   out_1516035527731464330[249] = 0;
   out_1516035527731464330[250] = 0;
   out_1516035527731464330[251] = 0;
   out_1516035527731464330[252] = 0;
   out_1516035527731464330[253] = 0;
   out_1516035527731464330[254] = 0;
   out_1516035527731464330[255] = 0;
   out_1516035527731464330[256] = 0;
   out_1516035527731464330[257] = 0;
   out_1516035527731464330[258] = 0;
   out_1516035527731464330[259] = 0;
   out_1516035527731464330[260] = 0;
   out_1516035527731464330[261] = 0;
   out_1516035527731464330[262] = 0;
   out_1516035527731464330[263] = 0;
   out_1516035527731464330[264] = 0;
   out_1516035527731464330[265] = 0;
   out_1516035527731464330[266] = 1;
   out_1516035527731464330[267] = 0;
   out_1516035527731464330[268] = 0;
   out_1516035527731464330[269] = 0;
   out_1516035527731464330[270] = 0;
   out_1516035527731464330[271] = 0;
   out_1516035527731464330[272] = 0;
   out_1516035527731464330[273] = 0;
   out_1516035527731464330[274] = 0;
   out_1516035527731464330[275] = 0;
   out_1516035527731464330[276] = 0;
   out_1516035527731464330[277] = 0;
   out_1516035527731464330[278] = 0;
   out_1516035527731464330[279] = 0;
   out_1516035527731464330[280] = 0;
   out_1516035527731464330[281] = 0;
   out_1516035527731464330[282] = 0;
   out_1516035527731464330[283] = 0;
   out_1516035527731464330[284] = 0;
   out_1516035527731464330[285] = 1;
   out_1516035527731464330[286] = 0;
   out_1516035527731464330[287] = 0;
   out_1516035527731464330[288] = 0;
   out_1516035527731464330[289] = 0;
   out_1516035527731464330[290] = 0;
   out_1516035527731464330[291] = 0;
   out_1516035527731464330[292] = 0;
   out_1516035527731464330[293] = 0;
   out_1516035527731464330[294] = 0;
   out_1516035527731464330[295] = 0;
   out_1516035527731464330[296] = 0;
   out_1516035527731464330[297] = 0;
   out_1516035527731464330[298] = 0;
   out_1516035527731464330[299] = 0;
   out_1516035527731464330[300] = 0;
   out_1516035527731464330[301] = 0;
   out_1516035527731464330[302] = 0;
   out_1516035527731464330[303] = 0;
   out_1516035527731464330[304] = 1;
   out_1516035527731464330[305] = 0;
   out_1516035527731464330[306] = 0;
   out_1516035527731464330[307] = 0;
   out_1516035527731464330[308] = 0;
   out_1516035527731464330[309] = 0;
   out_1516035527731464330[310] = 0;
   out_1516035527731464330[311] = 0;
   out_1516035527731464330[312] = 0;
   out_1516035527731464330[313] = 0;
   out_1516035527731464330[314] = 0;
   out_1516035527731464330[315] = 0;
   out_1516035527731464330[316] = 0;
   out_1516035527731464330[317] = 0;
   out_1516035527731464330[318] = 0;
   out_1516035527731464330[319] = 0;
   out_1516035527731464330[320] = 0;
   out_1516035527731464330[321] = 0;
   out_1516035527731464330[322] = 0;
   out_1516035527731464330[323] = 1;
}
void h_4(double *state, double *unused, double *out_4492721189395603550) {
   out_4492721189395603550[0] = state[6] + state[9];
   out_4492721189395603550[1] = state[7] + state[10];
   out_4492721189395603550[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4858215238190826153) {
   out_4858215238190826153[0] = 0;
   out_4858215238190826153[1] = 0;
   out_4858215238190826153[2] = 0;
   out_4858215238190826153[3] = 0;
   out_4858215238190826153[4] = 0;
   out_4858215238190826153[5] = 0;
   out_4858215238190826153[6] = 1;
   out_4858215238190826153[7] = 0;
   out_4858215238190826153[8] = 0;
   out_4858215238190826153[9] = 1;
   out_4858215238190826153[10] = 0;
   out_4858215238190826153[11] = 0;
   out_4858215238190826153[12] = 0;
   out_4858215238190826153[13] = 0;
   out_4858215238190826153[14] = 0;
   out_4858215238190826153[15] = 0;
   out_4858215238190826153[16] = 0;
   out_4858215238190826153[17] = 0;
   out_4858215238190826153[18] = 0;
   out_4858215238190826153[19] = 0;
   out_4858215238190826153[20] = 0;
   out_4858215238190826153[21] = 0;
   out_4858215238190826153[22] = 0;
   out_4858215238190826153[23] = 0;
   out_4858215238190826153[24] = 0;
   out_4858215238190826153[25] = 1;
   out_4858215238190826153[26] = 0;
   out_4858215238190826153[27] = 0;
   out_4858215238190826153[28] = 1;
   out_4858215238190826153[29] = 0;
   out_4858215238190826153[30] = 0;
   out_4858215238190826153[31] = 0;
   out_4858215238190826153[32] = 0;
   out_4858215238190826153[33] = 0;
   out_4858215238190826153[34] = 0;
   out_4858215238190826153[35] = 0;
   out_4858215238190826153[36] = 0;
   out_4858215238190826153[37] = 0;
   out_4858215238190826153[38] = 0;
   out_4858215238190826153[39] = 0;
   out_4858215238190826153[40] = 0;
   out_4858215238190826153[41] = 0;
   out_4858215238190826153[42] = 0;
   out_4858215238190826153[43] = 0;
   out_4858215238190826153[44] = 1;
   out_4858215238190826153[45] = 0;
   out_4858215238190826153[46] = 0;
   out_4858215238190826153[47] = 1;
   out_4858215238190826153[48] = 0;
   out_4858215238190826153[49] = 0;
   out_4858215238190826153[50] = 0;
   out_4858215238190826153[51] = 0;
   out_4858215238190826153[52] = 0;
   out_4858215238190826153[53] = 0;
}
void h_10(double *state, double *unused, double *out_558240635521768637) {
   out_558240635521768637[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_558240635521768637[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_558240635521768637[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7377176961528777036) {
   out_7377176961528777036[0] = 0;
   out_7377176961528777036[1] = 9.8100000000000005*cos(state[1]);
   out_7377176961528777036[2] = 0;
   out_7377176961528777036[3] = 0;
   out_7377176961528777036[4] = -state[8];
   out_7377176961528777036[5] = state[7];
   out_7377176961528777036[6] = 0;
   out_7377176961528777036[7] = state[5];
   out_7377176961528777036[8] = -state[4];
   out_7377176961528777036[9] = 0;
   out_7377176961528777036[10] = 0;
   out_7377176961528777036[11] = 0;
   out_7377176961528777036[12] = 1;
   out_7377176961528777036[13] = 0;
   out_7377176961528777036[14] = 0;
   out_7377176961528777036[15] = 1;
   out_7377176961528777036[16] = 0;
   out_7377176961528777036[17] = 0;
   out_7377176961528777036[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7377176961528777036[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7377176961528777036[20] = 0;
   out_7377176961528777036[21] = state[8];
   out_7377176961528777036[22] = 0;
   out_7377176961528777036[23] = -state[6];
   out_7377176961528777036[24] = -state[5];
   out_7377176961528777036[25] = 0;
   out_7377176961528777036[26] = state[3];
   out_7377176961528777036[27] = 0;
   out_7377176961528777036[28] = 0;
   out_7377176961528777036[29] = 0;
   out_7377176961528777036[30] = 0;
   out_7377176961528777036[31] = 1;
   out_7377176961528777036[32] = 0;
   out_7377176961528777036[33] = 0;
   out_7377176961528777036[34] = 1;
   out_7377176961528777036[35] = 0;
   out_7377176961528777036[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7377176961528777036[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7377176961528777036[38] = 0;
   out_7377176961528777036[39] = -state[7];
   out_7377176961528777036[40] = state[6];
   out_7377176961528777036[41] = 0;
   out_7377176961528777036[42] = state[4];
   out_7377176961528777036[43] = -state[3];
   out_7377176961528777036[44] = 0;
   out_7377176961528777036[45] = 0;
   out_7377176961528777036[46] = 0;
   out_7377176961528777036[47] = 0;
   out_7377176961528777036[48] = 0;
   out_7377176961528777036[49] = 0;
   out_7377176961528777036[50] = 1;
   out_7377176961528777036[51] = 0;
   out_7377176961528777036[52] = 0;
   out_7377176961528777036[53] = 1;
}
void h_13(double *state, double *unused, double *out_3864223786954470726) {
   out_3864223786954470726[0] = state[3];
   out_3864223786954470726[1] = state[4];
   out_3864223786954470726[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1645941412858493352) {
   out_1645941412858493352[0] = 0;
   out_1645941412858493352[1] = 0;
   out_1645941412858493352[2] = 0;
   out_1645941412858493352[3] = 1;
   out_1645941412858493352[4] = 0;
   out_1645941412858493352[5] = 0;
   out_1645941412858493352[6] = 0;
   out_1645941412858493352[7] = 0;
   out_1645941412858493352[8] = 0;
   out_1645941412858493352[9] = 0;
   out_1645941412858493352[10] = 0;
   out_1645941412858493352[11] = 0;
   out_1645941412858493352[12] = 0;
   out_1645941412858493352[13] = 0;
   out_1645941412858493352[14] = 0;
   out_1645941412858493352[15] = 0;
   out_1645941412858493352[16] = 0;
   out_1645941412858493352[17] = 0;
   out_1645941412858493352[18] = 0;
   out_1645941412858493352[19] = 0;
   out_1645941412858493352[20] = 0;
   out_1645941412858493352[21] = 0;
   out_1645941412858493352[22] = 1;
   out_1645941412858493352[23] = 0;
   out_1645941412858493352[24] = 0;
   out_1645941412858493352[25] = 0;
   out_1645941412858493352[26] = 0;
   out_1645941412858493352[27] = 0;
   out_1645941412858493352[28] = 0;
   out_1645941412858493352[29] = 0;
   out_1645941412858493352[30] = 0;
   out_1645941412858493352[31] = 0;
   out_1645941412858493352[32] = 0;
   out_1645941412858493352[33] = 0;
   out_1645941412858493352[34] = 0;
   out_1645941412858493352[35] = 0;
   out_1645941412858493352[36] = 0;
   out_1645941412858493352[37] = 0;
   out_1645941412858493352[38] = 0;
   out_1645941412858493352[39] = 0;
   out_1645941412858493352[40] = 0;
   out_1645941412858493352[41] = 1;
   out_1645941412858493352[42] = 0;
   out_1645941412858493352[43] = 0;
   out_1645941412858493352[44] = 0;
   out_1645941412858493352[45] = 0;
   out_1645941412858493352[46] = 0;
   out_1645941412858493352[47] = 0;
   out_1645941412858493352[48] = 0;
   out_1645941412858493352[49] = 0;
   out_1645941412858493352[50] = 0;
   out_1645941412858493352[51] = 0;
   out_1645941412858493352[52] = 0;
   out_1645941412858493352[53] = 0;
}
void h_14(double *state, double *unused, double *out_2242454366414003666) {
   out_2242454366414003666[0] = state[6];
   out_2242454366414003666[1] = state[7];
   out_2242454366414003666[2] = state[8];
}
void H_14(double *state, double *unused, double *out_7941003670486198449) {
   out_7941003670486198449[0] = 0;
   out_7941003670486198449[1] = 0;
   out_7941003670486198449[2] = 0;
   out_7941003670486198449[3] = 0;
   out_7941003670486198449[4] = 0;
   out_7941003670486198449[5] = 0;
   out_7941003670486198449[6] = 1;
   out_7941003670486198449[7] = 0;
   out_7941003670486198449[8] = 0;
   out_7941003670486198449[9] = 0;
   out_7941003670486198449[10] = 0;
   out_7941003670486198449[11] = 0;
   out_7941003670486198449[12] = 0;
   out_7941003670486198449[13] = 0;
   out_7941003670486198449[14] = 0;
   out_7941003670486198449[15] = 0;
   out_7941003670486198449[16] = 0;
   out_7941003670486198449[17] = 0;
   out_7941003670486198449[18] = 0;
   out_7941003670486198449[19] = 0;
   out_7941003670486198449[20] = 0;
   out_7941003670486198449[21] = 0;
   out_7941003670486198449[22] = 0;
   out_7941003670486198449[23] = 0;
   out_7941003670486198449[24] = 0;
   out_7941003670486198449[25] = 1;
   out_7941003670486198449[26] = 0;
   out_7941003670486198449[27] = 0;
   out_7941003670486198449[28] = 0;
   out_7941003670486198449[29] = 0;
   out_7941003670486198449[30] = 0;
   out_7941003670486198449[31] = 0;
   out_7941003670486198449[32] = 0;
   out_7941003670486198449[33] = 0;
   out_7941003670486198449[34] = 0;
   out_7941003670486198449[35] = 0;
   out_7941003670486198449[36] = 0;
   out_7941003670486198449[37] = 0;
   out_7941003670486198449[38] = 0;
   out_7941003670486198449[39] = 0;
   out_7941003670486198449[40] = 0;
   out_7941003670486198449[41] = 0;
   out_7941003670486198449[42] = 0;
   out_7941003670486198449[43] = 0;
   out_7941003670486198449[44] = 1;
   out_7941003670486198449[45] = 0;
   out_7941003670486198449[46] = 0;
   out_7941003670486198449[47] = 0;
   out_7941003670486198449[48] = 0;
   out_7941003670486198449[49] = 0;
   out_7941003670486198449[50] = 0;
   out_7941003670486198449[51] = 0;
   out_7941003670486198449[52] = 0;
   out_7941003670486198449[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_2526150130430510074) {
  err_fun(nom_x, delta_x, out_2526150130430510074);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3515561648914426109) {
  inv_err_fun(nom_x, true_x, out_3515561648914426109);
}
void pose_H_mod_fun(double *state, double *out_6056162720073724257) {
  H_mod_fun(state, out_6056162720073724257);
}
void pose_f_fun(double *state, double dt, double *out_8780284750928315681) {
  f_fun(state,  dt, out_8780284750928315681);
}
void pose_F_fun(double *state, double dt, double *out_1516035527731464330) {
  F_fun(state,  dt, out_1516035527731464330);
}
void pose_h_4(double *state, double *unused, double *out_4492721189395603550) {
  h_4(state, unused, out_4492721189395603550);
}
void pose_H_4(double *state, double *unused, double *out_4858215238190826153) {
  H_4(state, unused, out_4858215238190826153);
}
void pose_h_10(double *state, double *unused, double *out_558240635521768637) {
  h_10(state, unused, out_558240635521768637);
}
void pose_H_10(double *state, double *unused, double *out_7377176961528777036) {
  H_10(state, unused, out_7377176961528777036);
}
void pose_h_13(double *state, double *unused, double *out_3864223786954470726) {
  h_13(state, unused, out_3864223786954470726);
}
void pose_H_13(double *state, double *unused, double *out_1645941412858493352) {
  H_13(state, unused, out_1645941412858493352);
}
void pose_h_14(double *state, double *unused, double *out_2242454366414003666) {
  h_14(state, unused, out_2242454366414003666);
}
void pose_H_14(double *state, double *unused, double *out_7941003670486198449) {
  H_14(state, unused, out_7941003670486198449);
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
