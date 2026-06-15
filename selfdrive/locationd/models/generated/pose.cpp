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
void err_fun(double *nom_x, double *delta_x, double *out_7337273534871130421) {
   out_7337273534871130421[0] = delta_x[0] + nom_x[0];
   out_7337273534871130421[1] = delta_x[1] + nom_x[1];
   out_7337273534871130421[2] = delta_x[2] + nom_x[2];
   out_7337273534871130421[3] = delta_x[3] + nom_x[3];
   out_7337273534871130421[4] = delta_x[4] + nom_x[4];
   out_7337273534871130421[5] = delta_x[5] + nom_x[5];
   out_7337273534871130421[6] = delta_x[6] + nom_x[6];
   out_7337273534871130421[7] = delta_x[7] + nom_x[7];
   out_7337273534871130421[8] = delta_x[8] + nom_x[8];
   out_7337273534871130421[9] = delta_x[9] + nom_x[9];
   out_7337273534871130421[10] = delta_x[10] + nom_x[10];
   out_7337273534871130421[11] = delta_x[11] + nom_x[11];
   out_7337273534871130421[12] = delta_x[12] + nom_x[12];
   out_7337273534871130421[13] = delta_x[13] + nom_x[13];
   out_7337273534871130421[14] = delta_x[14] + nom_x[14];
   out_7337273534871130421[15] = delta_x[15] + nom_x[15];
   out_7337273534871130421[16] = delta_x[16] + nom_x[16];
   out_7337273534871130421[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7370167163616029780) {
   out_7370167163616029780[0] = -nom_x[0] + true_x[0];
   out_7370167163616029780[1] = -nom_x[1] + true_x[1];
   out_7370167163616029780[2] = -nom_x[2] + true_x[2];
   out_7370167163616029780[3] = -nom_x[3] + true_x[3];
   out_7370167163616029780[4] = -nom_x[4] + true_x[4];
   out_7370167163616029780[5] = -nom_x[5] + true_x[5];
   out_7370167163616029780[6] = -nom_x[6] + true_x[6];
   out_7370167163616029780[7] = -nom_x[7] + true_x[7];
   out_7370167163616029780[8] = -nom_x[8] + true_x[8];
   out_7370167163616029780[9] = -nom_x[9] + true_x[9];
   out_7370167163616029780[10] = -nom_x[10] + true_x[10];
   out_7370167163616029780[11] = -nom_x[11] + true_x[11];
   out_7370167163616029780[12] = -nom_x[12] + true_x[12];
   out_7370167163616029780[13] = -nom_x[13] + true_x[13];
   out_7370167163616029780[14] = -nom_x[14] + true_x[14];
   out_7370167163616029780[15] = -nom_x[15] + true_x[15];
   out_7370167163616029780[16] = -nom_x[16] + true_x[16];
   out_7370167163616029780[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_1839001963735438802) {
   out_1839001963735438802[0] = 1.0;
   out_1839001963735438802[1] = 0.0;
   out_1839001963735438802[2] = 0.0;
   out_1839001963735438802[3] = 0.0;
   out_1839001963735438802[4] = 0.0;
   out_1839001963735438802[5] = 0.0;
   out_1839001963735438802[6] = 0.0;
   out_1839001963735438802[7] = 0.0;
   out_1839001963735438802[8] = 0.0;
   out_1839001963735438802[9] = 0.0;
   out_1839001963735438802[10] = 0.0;
   out_1839001963735438802[11] = 0.0;
   out_1839001963735438802[12] = 0.0;
   out_1839001963735438802[13] = 0.0;
   out_1839001963735438802[14] = 0.0;
   out_1839001963735438802[15] = 0.0;
   out_1839001963735438802[16] = 0.0;
   out_1839001963735438802[17] = 0.0;
   out_1839001963735438802[18] = 0.0;
   out_1839001963735438802[19] = 1.0;
   out_1839001963735438802[20] = 0.0;
   out_1839001963735438802[21] = 0.0;
   out_1839001963735438802[22] = 0.0;
   out_1839001963735438802[23] = 0.0;
   out_1839001963735438802[24] = 0.0;
   out_1839001963735438802[25] = 0.0;
   out_1839001963735438802[26] = 0.0;
   out_1839001963735438802[27] = 0.0;
   out_1839001963735438802[28] = 0.0;
   out_1839001963735438802[29] = 0.0;
   out_1839001963735438802[30] = 0.0;
   out_1839001963735438802[31] = 0.0;
   out_1839001963735438802[32] = 0.0;
   out_1839001963735438802[33] = 0.0;
   out_1839001963735438802[34] = 0.0;
   out_1839001963735438802[35] = 0.0;
   out_1839001963735438802[36] = 0.0;
   out_1839001963735438802[37] = 0.0;
   out_1839001963735438802[38] = 1.0;
   out_1839001963735438802[39] = 0.0;
   out_1839001963735438802[40] = 0.0;
   out_1839001963735438802[41] = 0.0;
   out_1839001963735438802[42] = 0.0;
   out_1839001963735438802[43] = 0.0;
   out_1839001963735438802[44] = 0.0;
   out_1839001963735438802[45] = 0.0;
   out_1839001963735438802[46] = 0.0;
   out_1839001963735438802[47] = 0.0;
   out_1839001963735438802[48] = 0.0;
   out_1839001963735438802[49] = 0.0;
   out_1839001963735438802[50] = 0.0;
   out_1839001963735438802[51] = 0.0;
   out_1839001963735438802[52] = 0.0;
   out_1839001963735438802[53] = 0.0;
   out_1839001963735438802[54] = 0.0;
   out_1839001963735438802[55] = 0.0;
   out_1839001963735438802[56] = 0.0;
   out_1839001963735438802[57] = 1.0;
   out_1839001963735438802[58] = 0.0;
   out_1839001963735438802[59] = 0.0;
   out_1839001963735438802[60] = 0.0;
   out_1839001963735438802[61] = 0.0;
   out_1839001963735438802[62] = 0.0;
   out_1839001963735438802[63] = 0.0;
   out_1839001963735438802[64] = 0.0;
   out_1839001963735438802[65] = 0.0;
   out_1839001963735438802[66] = 0.0;
   out_1839001963735438802[67] = 0.0;
   out_1839001963735438802[68] = 0.0;
   out_1839001963735438802[69] = 0.0;
   out_1839001963735438802[70] = 0.0;
   out_1839001963735438802[71] = 0.0;
   out_1839001963735438802[72] = 0.0;
   out_1839001963735438802[73] = 0.0;
   out_1839001963735438802[74] = 0.0;
   out_1839001963735438802[75] = 0.0;
   out_1839001963735438802[76] = 1.0;
   out_1839001963735438802[77] = 0.0;
   out_1839001963735438802[78] = 0.0;
   out_1839001963735438802[79] = 0.0;
   out_1839001963735438802[80] = 0.0;
   out_1839001963735438802[81] = 0.0;
   out_1839001963735438802[82] = 0.0;
   out_1839001963735438802[83] = 0.0;
   out_1839001963735438802[84] = 0.0;
   out_1839001963735438802[85] = 0.0;
   out_1839001963735438802[86] = 0.0;
   out_1839001963735438802[87] = 0.0;
   out_1839001963735438802[88] = 0.0;
   out_1839001963735438802[89] = 0.0;
   out_1839001963735438802[90] = 0.0;
   out_1839001963735438802[91] = 0.0;
   out_1839001963735438802[92] = 0.0;
   out_1839001963735438802[93] = 0.0;
   out_1839001963735438802[94] = 0.0;
   out_1839001963735438802[95] = 1.0;
   out_1839001963735438802[96] = 0.0;
   out_1839001963735438802[97] = 0.0;
   out_1839001963735438802[98] = 0.0;
   out_1839001963735438802[99] = 0.0;
   out_1839001963735438802[100] = 0.0;
   out_1839001963735438802[101] = 0.0;
   out_1839001963735438802[102] = 0.0;
   out_1839001963735438802[103] = 0.0;
   out_1839001963735438802[104] = 0.0;
   out_1839001963735438802[105] = 0.0;
   out_1839001963735438802[106] = 0.0;
   out_1839001963735438802[107] = 0.0;
   out_1839001963735438802[108] = 0.0;
   out_1839001963735438802[109] = 0.0;
   out_1839001963735438802[110] = 0.0;
   out_1839001963735438802[111] = 0.0;
   out_1839001963735438802[112] = 0.0;
   out_1839001963735438802[113] = 0.0;
   out_1839001963735438802[114] = 1.0;
   out_1839001963735438802[115] = 0.0;
   out_1839001963735438802[116] = 0.0;
   out_1839001963735438802[117] = 0.0;
   out_1839001963735438802[118] = 0.0;
   out_1839001963735438802[119] = 0.0;
   out_1839001963735438802[120] = 0.0;
   out_1839001963735438802[121] = 0.0;
   out_1839001963735438802[122] = 0.0;
   out_1839001963735438802[123] = 0.0;
   out_1839001963735438802[124] = 0.0;
   out_1839001963735438802[125] = 0.0;
   out_1839001963735438802[126] = 0.0;
   out_1839001963735438802[127] = 0.0;
   out_1839001963735438802[128] = 0.0;
   out_1839001963735438802[129] = 0.0;
   out_1839001963735438802[130] = 0.0;
   out_1839001963735438802[131] = 0.0;
   out_1839001963735438802[132] = 0.0;
   out_1839001963735438802[133] = 1.0;
   out_1839001963735438802[134] = 0.0;
   out_1839001963735438802[135] = 0.0;
   out_1839001963735438802[136] = 0.0;
   out_1839001963735438802[137] = 0.0;
   out_1839001963735438802[138] = 0.0;
   out_1839001963735438802[139] = 0.0;
   out_1839001963735438802[140] = 0.0;
   out_1839001963735438802[141] = 0.0;
   out_1839001963735438802[142] = 0.0;
   out_1839001963735438802[143] = 0.0;
   out_1839001963735438802[144] = 0.0;
   out_1839001963735438802[145] = 0.0;
   out_1839001963735438802[146] = 0.0;
   out_1839001963735438802[147] = 0.0;
   out_1839001963735438802[148] = 0.0;
   out_1839001963735438802[149] = 0.0;
   out_1839001963735438802[150] = 0.0;
   out_1839001963735438802[151] = 0.0;
   out_1839001963735438802[152] = 1.0;
   out_1839001963735438802[153] = 0.0;
   out_1839001963735438802[154] = 0.0;
   out_1839001963735438802[155] = 0.0;
   out_1839001963735438802[156] = 0.0;
   out_1839001963735438802[157] = 0.0;
   out_1839001963735438802[158] = 0.0;
   out_1839001963735438802[159] = 0.0;
   out_1839001963735438802[160] = 0.0;
   out_1839001963735438802[161] = 0.0;
   out_1839001963735438802[162] = 0.0;
   out_1839001963735438802[163] = 0.0;
   out_1839001963735438802[164] = 0.0;
   out_1839001963735438802[165] = 0.0;
   out_1839001963735438802[166] = 0.0;
   out_1839001963735438802[167] = 0.0;
   out_1839001963735438802[168] = 0.0;
   out_1839001963735438802[169] = 0.0;
   out_1839001963735438802[170] = 0.0;
   out_1839001963735438802[171] = 1.0;
   out_1839001963735438802[172] = 0.0;
   out_1839001963735438802[173] = 0.0;
   out_1839001963735438802[174] = 0.0;
   out_1839001963735438802[175] = 0.0;
   out_1839001963735438802[176] = 0.0;
   out_1839001963735438802[177] = 0.0;
   out_1839001963735438802[178] = 0.0;
   out_1839001963735438802[179] = 0.0;
   out_1839001963735438802[180] = 0.0;
   out_1839001963735438802[181] = 0.0;
   out_1839001963735438802[182] = 0.0;
   out_1839001963735438802[183] = 0.0;
   out_1839001963735438802[184] = 0.0;
   out_1839001963735438802[185] = 0.0;
   out_1839001963735438802[186] = 0.0;
   out_1839001963735438802[187] = 0.0;
   out_1839001963735438802[188] = 0.0;
   out_1839001963735438802[189] = 0.0;
   out_1839001963735438802[190] = 1.0;
   out_1839001963735438802[191] = 0.0;
   out_1839001963735438802[192] = 0.0;
   out_1839001963735438802[193] = 0.0;
   out_1839001963735438802[194] = 0.0;
   out_1839001963735438802[195] = 0.0;
   out_1839001963735438802[196] = 0.0;
   out_1839001963735438802[197] = 0.0;
   out_1839001963735438802[198] = 0.0;
   out_1839001963735438802[199] = 0.0;
   out_1839001963735438802[200] = 0.0;
   out_1839001963735438802[201] = 0.0;
   out_1839001963735438802[202] = 0.0;
   out_1839001963735438802[203] = 0.0;
   out_1839001963735438802[204] = 0.0;
   out_1839001963735438802[205] = 0.0;
   out_1839001963735438802[206] = 0.0;
   out_1839001963735438802[207] = 0.0;
   out_1839001963735438802[208] = 0.0;
   out_1839001963735438802[209] = 1.0;
   out_1839001963735438802[210] = 0.0;
   out_1839001963735438802[211] = 0.0;
   out_1839001963735438802[212] = 0.0;
   out_1839001963735438802[213] = 0.0;
   out_1839001963735438802[214] = 0.0;
   out_1839001963735438802[215] = 0.0;
   out_1839001963735438802[216] = 0.0;
   out_1839001963735438802[217] = 0.0;
   out_1839001963735438802[218] = 0.0;
   out_1839001963735438802[219] = 0.0;
   out_1839001963735438802[220] = 0.0;
   out_1839001963735438802[221] = 0.0;
   out_1839001963735438802[222] = 0.0;
   out_1839001963735438802[223] = 0.0;
   out_1839001963735438802[224] = 0.0;
   out_1839001963735438802[225] = 0.0;
   out_1839001963735438802[226] = 0.0;
   out_1839001963735438802[227] = 0.0;
   out_1839001963735438802[228] = 1.0;
   out_1839001963735438802[229] = 0.0;
   out_1839001963735438802[230] = 0.0;
   out_1839001963735438802[231] = 0.0;
   out_1839001963735438802[232] = 0.0;
   out_1839001963735438802[233] = 0.0;
   out_1839001963735438802[234] = 0.0;
   out_1839001963735438802[235] = 0.0;
   out_1839001963735438802[236] = 0.0;
   out_1839001963735438802[237] = 0.0;
   out_1839001963735438802[238] = 0.0;
   out_1839001963735438802[239] = 0.0;
   out_1839001963735438802[240] = 0.0;
   out_1839001963735438802[241] = 0.0;
   out_1839001963735438802[242] = 0.0;
   out_1839001963735438802[243] = 0.0;
   out_1839001963735438802[244] = 0.0;
   out_1839001963735438802[245] = 0.0;
   out_1839001963735438802[246] = 0.0;
   out_1839001963735438802[247] = 1.0;
   out_1839001963735438802[248] = 0.0;
   out_1839001963735438802[249] = 0.0;
   out_1839001963735438802[250] = 0.0;
   out_1839001963735438802[251] = 0.0;
   out_1839001963735438802[252] = 0.0;
   out_1839001963735438802[253] = 0.0;
   out_1839001963735438802[254] = 0.0;
   out_1839001963735438802[255] = 0.0;
   out_1839001963735438802[256] = 0.0;
   out_1839001963735438802[257] = 0.0;
   out_1839001963735438802[258] = 0.0;
   out_1839001963735438802[259] = 0.0;
   out_1839001963735438802[260] = 0.0;
   out_1839001963735438802[261] = 0.0;
   out_1839001963735438802[262] = 0.0;
   out_1839001963735438802[263] = 0.0;
   out_1839001963735438802[264] = 0.0;
   out_1839001963735438802[265] = 0.0;
   out_1839001963735438802[266] = 1.0;
   out_1839001963735438802[267] = 0.0;
   out_1839001963735438802[268] = 0.0;
   out_1839001963735438802[269] = 0.0;
   out_1839001963735438802[270] = 0.0;
   out_1839001963735438802[271] = 0.0;
   out_1839001963735438802[272] = 0.0;
   out_1839001963735438802[273] = 0.0;
   out_1839001963735438802[274] = 0.0;
   out_1839001963735438802[275] = 0.0;
   out_1839001963735438802[276] = 0.0;
   out_1839001963735438802[277] = 0.0;
   out_1839001963735438802[278] = 0.0;
   out_1839001963735438802[279] = 0.0;
   out_1839001963735438802[280] = 0.0;
   out_1839001963735438802[281] = 0.0;
   out_1839001963735438802[282] = 0.0;
   out_1839001963735438802[283] = 0.0;
   out_1839001963735438802[284] = 0.0;
   out_1839001963735438802[285] = 1.0;
   out_1839001963735438802[286] = 0.0;
   out_1839001963735438802[287] = 0.0;
   out_1839001963735438802[288] = 0.0;
   out_1839001963735438802[289] = 0.0;
   out_1839001963735438802[290] = 0.0;
   out_1839001963735438802[291] = 0.0;
   out_1839001963735438802[292] = 0.0;
   out_1839001963735438802[293] = 0.0;
   out_1839001963735438802[294] = 0.0;
   out_1839001963735438802[295] = 0.0;
   out_1839001963735438802[296] = 0.0;
   out_1839001963735438802[297] = 0.0;
   out_1839001963735438802[298] = 0.0;
   out_1839001963735438802[299] = 0.0;
   out_1839001963735438802[300] = 0.0;
   out_1839001963735438802[301] = 0.0;
   out_1839001963735438802[302] = 0.0;
   out_1839001963735438802[303] = 0.0;
   out_1839001963735438802[304] = 1.0;
   out_1839001963735438802[305] = 0.0;
   out_1839001963735438802[306] = 0.0;
   out_1839001963735438802[307] = 0.0;
   out_1839001963735438802[308] = 0.0;
   out_1839001963735438802[309] = 0.0;
   out_1839001963735438802[310] = 0.0;
   out_1839001963735438802[311] = 0.0;
   out_1839001963735438802[312] = 0.0;
   out_1839001963735438802[313] = 0.0;
   out_1839001963735438802[314] = 0.0;
   out_1839001963735438802[315] = 0.0;
   out_1839001963735438802[316] = 0.0;
   out_1839001963735438802[317] = 0.0;
   out_1839001963735438802[318] = 0.0;
   out_1839001963735438802[319] = 0.0;
   out_1839001963735438802[320] = 0.0;
   out_1839001963735438802[321] = 0.0;
   out_1839001963735438802[322] = 0.0;
   out_1839001963735438802[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_3683398569821655413) {
   out_3683398569821655413[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_3683398569821655413[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_3683398569821655413[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_3683398569821655413[3] = dt*state[12] + state[3];
   out_3683398569821655413[4] = dt*state[13] + state[4];
   out_3683398569821655413[5] = dt*state[14] + state[5];
   out_3683398569821655413[6] = state[6];
   out_3683398569821655413[7] = state[7];
   out_3683398569821655413[8] = state[8];
   out_3683398569821655413[9] = state[9];
   out_3683398569821655413[10] = state[10];
   out_3683398569821655413[11] = state[11];
   out_3683398569821655413[12] = state[12];
   out_3683398569821655413[13] = state[13];
   out_3683398569821655413[14] = state[14];
   out_3683398569821655413[15] = state[15];
   out_3683398569821655413[16] = state[16];
   out_3683398569821655413[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3094277237620606525) {
   out_3094277237620606525[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3094277237620606525[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3094277237620606525[2] = 0;
   out_3094277237620606525[3] = 0;
   out_3094277237620606525[4] = 0;
   out_3094277237620606525[5] = 0;
   out_3094277237620606525[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3094277237620606525[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3094277237620606525[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3094277237620606525[9] = 0;
   out_3094277237620606525[10] = 0;
   out_3094277237620606525[11] = 0;
   out_3094277237620606525[12] = 0;
   out_3094277237620606525[13] = 0;
   out_3094277237620606525[14] = 0;
   out_3094277237620606525[15] = 0;
   out_3094277237620606525[16] = 0;
   out_3094277237620606525[17] = 0;
   out_3094277237620606525[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3094277237620606525[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3094277237620606525[20] = 0;
   out_3094277237620606525[21] = 0;
   out_3094277237620606525[22] = 0;
   out_3094277237620606525[23] = 0;
   out_3094277237620606525[24] = 0;
   out_3094277237620606525[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3094277237620606525[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3094277237620606525[27] = 0;
   out_3094277237620606525[28] = 0;
   out_3094277237620606525[29] = 0;
   out_3094277237620606525[30] = 0;
   out_3094277237620606525[31] = 0;
   out_3094277237620606525[32] = 0;
   out_3094277237620606525[33] = 0;
   out_3094277237620606525[34] = 0;
   out_3094277237620606525[35] = 0;
   out_3094277237620606525[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3094277237620606525[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3094277237620606525[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3094277237620606525[39] = 0;
   out_3094277237620606525[40] = 0;
   out_3094277237620606525[41] = 0;
   out_3094277237620606525[42] = 0;
   out_3094277237620606525[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3094277237620606525[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3094277237620606525[45] = 0;
   out_3094277237620606525[46] = 0;
   out_3094277237620606525[47] = 0;
   out_3094277237620606525[48] = 0;
   out_3094277237620606525[49] = 0;
   out_3094277237620606525[50] = 0;
   out_3094277237620606525[51] = 0;
   out_3094277237620606525[52] = 0;
   out_3094277237620606525[53] = 0;
   out_3094277237620606525[54] = 0;
   out_3094277237620606525[55] = 0;
   out_3094277237620606525[56] = 0;
   out_3094277237620606525[57] = 1;
   out_3094277237620606525[58] = 0;
   out_3094277237620606525[59] = 0;
   out_3094277237620606525[60] = 0;
   out_3094277237620606525[61] = 0;
   out_3094277237620606525[62] = 0;
   out_3094277237620606525[63] = 0;
   out_3094277237620606525[64] = 0;
   out_3094277237620606525[65] = 0;
   out_3094277237620606525[66] = dt;
   out_3094277237620606525[67] = 0;
   out_3094277237620606525[68] = 0;
   out_3094277237620606525[69] = 0;
   out_3094277237620606525[70] = 0;
   out_3094277237620606525[71] = 0;
   out_3094277237620606525[72] = 0;
   out_3094277237620606525[73] = 0;
   out_3094277237620606525[74] = 0;
   out_3094277237620606525[75] = 0;
   out_3094277237620606525[76] = 1;
   out_3094277237620606525[77] = 0;
   out_3094277237620606525[78] = 0;
   out_3094277237620606525[79] = 0;
   out_3094277237620606525[80] = 0;
   out_3094277237620606525[81] = 0;
   out_3094277237620606525[82] = 0;
   out_3094277237620606525[83] = 0;
   out_3094277237620606525[84] = 0;
   out_3094277237620606525[85] = dt;
   out_3094277237620606525[86] = 0;
   out_3094277237620606525[87] = 0;
   out_3094277237620606525[88] = 0;
   out_3094277237620606525[89] = 0;
   out_3094277237620606525[90] = 0;
   out_3094277237620606525[91] = 0;
   out_3094277237620606525[92] = 0;
   out_3094277237620606525[93] = 0;
   out_3094277237620606525[94] = 0;
   out_3094277237620606525[95] = 1;
   out_3094277237620606525[96] = 0;
   out_3094277237620606525[97] = 0;
   out_3094277237620606525[98] = 0;
   out_3094277237620606525[99] = 0;
   out_3094277237620606525[100] = 0;
   out_3094277237620606525[101] = 0;
   out_3094277237620606525[102] = 0;
   out_3094277237620606525[103] = 0;
   out_3094277237620606525[104] = dt;
   out_3094277237620606525[105] = 0;
   out_3094277237620606525[106] = 0;
   out_3094277237620606525[107] = 0;
   out_3094277237620606525[108] = 0;
   out_3094277237620606525[109] = 0;
   out_3094277237620606525[110] = 0;
   out_3094277237620606525[111] = 0;
   out_3094277237620606525[112] = 0;
   out_3094277237620606525[113] = 0;
   out_3094277237620606525[114] = 1;
   out_3094277237620606525[115] = 0;
   out_3094277237620606525[116] = 0;
   out_3094277237620606525[117] = 0;
   out_3094277237620606525[118] = 0;
   out_3094277237620606525[119] = 0;
   out_3094277237620606525[120] = 0;
   out_3094277237620606525[121] = 0;
   out_3094277237620606525[122] = 0;
   out_3094277237620606525[123] = 0;
   out_3094277237620606525[124] = 0;
   out_3094277237620606525[125] = 0;
   out_3094277237620606525[126] = 0;
   out_3094277237620606525[127] = 0;
   out_3094277237620606525[128] = 0;
   out_3094277237620606525[129] = 0;
   out_3094277237620606525[130] = 0;
   out_3094277237620606525[131] = 0;
   out_3094277237620606525[132] = 0;
   out_3094277237620606525[133] = 1;
   out_3094277237620606525[134] = 0;
   out_3094277237620606525[135] = 0;
   out_3094277237620606525[136] = 0;
   out_3094277237620606525[137] = 0;
   out_3094277237620606525[138] = 0;
   out_3094277237620606525[139] = 0;
   out_3094277237620606525[140] = 0;
   out_3094277237620606525[141] = 0;
   out_3094277237620606525[142] = 0;
   out_3094277237620606525[143] = 0;
   out_3094277237620606525[144] = 0;
   out_3094277237620606525[145] = 0;
   out_3094277237620606525[146] = 0;
   out_3094277237620606525[147] = 0;
   out_3094277237620606525[148] = 0;
   out_3094277237620606525[149] = 0;
   out_3094277237620606525[150] = 0;
   out_3094277237620606525[151] = 0;
   out_3094277237620606525[152] = 1;
   out_3094277237620606525[153] = 0;
   out_3094277237620606525[154] = 0;
   out_3094277237620606525[155] = 0;
   out_3094277237620606525[156] = 0;
   out_3094277237620606525[157] = 0;
   out_3094277237620606525[158] = 0;
   out_3094277237620606525[159] = 0;
   out_3094277237620606525[160] = 0;
   out_3094277237620606525[161] = 0;
   out_3094277237620606525[162] = 0;
   out_3094277237620606525[163] = 0;
   out_3094277237620606525[164] = 0;
   out_3094277237620606525[165] = 0;
   out_3094277237620606525[166] = 0;
   out_3094277237620606525[167] = 0;
   out_3094277237620606525[168] = 0;
   out_3094277237620606525[169] = 0;
   out_3094277237620606525[170] = 0;
   out_3094277237620606525[171] = 1;
   out_3094277237620606525[172] = 0;
   out_3094277237620606525[173] = 0;
   out_3094277237620606525[174] = 0;
   out_3094277237620606525[175] = 0;
   out_3094277237620606525[176] = 0;
   out_3094277237620606525[177] = 0;
   out_3094277237620606525[178] = 0;
   out_3094277237620606525[179] = 0;
   out_3094277237620606525[180] = 0;
   out_3094277237620606525[181] = 0;
   out_3094277237620606525[182] = 0;
   out_3094277237620606525[183] = 0;
   out_3094277237620606525[184] = 0;
   out_3094277237620606525[185] = 0;
   out_3094277237620606525[186] = 0;
   out_3094277237620606525[187] = 0;
   out_3094277237620606525[188] = 0;
   out_3094277237620606525[189] = 0;
   out_3094277237620606525[190] = 1;
   out_3094277237620606525[191] = 0;
   out_3094277237620606525[192] = 0;
   out_3094277237620606525[193] = 0;
   out_3094277237620606525[194] = 0;
   out_3094277237620606525[195] = 0;
   out_3094277237620606525[196] = 0;
   out_3094277237620606525[197] = 0;
   out_3094277237620606525[198] = 0;
   out_3094277237620606525[199] = 0;
   out_3094277237620606525[200] = 0;
   out_3094277237620606525[201] = 0;
   out_3094277237620606525[202] = 0;
   out_3094277237620606525[203] = 0;
   out_3094277237620606525[204] = 0;
   out_3094277237620606525[205] = 0;
   out_3094277237620606525[206] = 0;
   out_3094277237620606525[207] = 0;
   out_3094277237620606525[208] = 0;
   out_3094277237620606525[209] = 1;
   out_3094277237620606525[210] = 0;
   out_3094277237620606525[211] = 0;
   out_3094277237620606525[212] = 0;
   out_3094277237620606525[213] = 0;
   out_3094277237620606525[214] = 0;
   out_3094277237620606525[215] = 0;
   out_3094277237620606525[216] = 0;
   out_3094277237620606525[217] = 0;
   out_3094277237620606525[218] = 0;
   out_3094277237620606525[219] = 0;
   out_3094277237620606525[220] = 0;
   out_3094277237620606525[221] = 0;
   out_3094277237620606525[222] = 0;
   out_3094277237620606525[223] = 0;
   out_3094277237620606525[224] = 0;
   out_3094277237620606525[225] = 0;
   out_3094277237620606525[226] = 0;
   out_3094277237620606525[227] = 0;
   out_3094277237620606525[228] = 1;
   out_3094277237620606525[229] = 0;
   out_3094277237620606525[230] = 0;
   out_3094277237620606525[231] = 0;
   out_3094277237620606525[232] = 0;
   out_3094277237620606525[233] = 0;
   out_3094277237620606525[234] = 0;
   out_3094277237620606525[235] = 0;
   out_3094277237620606525[236] = 0;
   out_3094277237620606525[237] = 0;
   out_3094277237620606525[238] = 0;
   out_3094277237620606525[239] = 0;
   out_3094277237620606525[240] = 0;
   out_3094277237620606525[241] = 0;
   out_3094277237620606525[242] = 0;
   out_3094277237620606525[243] = 0;
   out_3094277237620606525[244] = 0;
   out_3094277237620606525[245] = 0;
   out_3094277237620606525[246] = 0;
   out_3094277237620606525[247] = 1;
   out_3094277237620606525[248] = 0;
   out_3094277237620606525[249] = 0;
   out_3094277237620606525[250] = 0;
   out_3094277237620606525[251] = 0;
   out_3094277237620606525[252] = 0;
   out_3094277237620606525[253] = 0;
   out_3094277237620606525[254] = 0;
   out_3094277237620606525[255] = 0;
   out_3094277237620606525[256] = 0;
   out_3094277237620606525[257] = 0;
   out_3094277237620606525[258] = 0;
   out_3094277237620606525[259] = 0;
   out_3094277237620606525[260] = 0;
   out_3094277237620606525[261] = 0;
   out_3094277237620606525[262] = 0;
   out_3094277237620606525[263] = 0;
   out_3094277237620606525[264] = 0;
   out_3094277237620606525[265] = 0;
   out_3094277237620606525[266] = 1;
   out_3094277237620606525[267] = 0;
   out_3094277237620606525[268] = 0;
   out_3094277237620606525[269] = 0;
   out_3094277237620606525[270] = 0;
   out_3094277237620606525[271] = 0;
   out_3094277237620606525[272] = 0;
   out_3094277237620606525[273] = 0;
   out_3094277237620606525[274] = 0;
   out_3094277237620606525[275] = 0;
   out_3094277237620606525[276] = 0;
   out_3094277237620606525[277] = 0;
   out_3094277237620606525[278] = 0;
   out_3094277237620606525[279] = 0;
   out_3094277237620606525[280] = 0;
   out_3094277237620606525[281] = 0;
   out_3094277237620606525[282] = 0;
   out_3094277237620606525[283] = 0;
   out_3094277237620606525[284] = 0;
   out_3094277237620606525[285] = 1;
   out_3094277237620606525[286] = 0;
   out_3094277237620606525[287] = 0;
   out_3094277237620606525[288] = 0;
   out_3094277237620606525[289] = 0;
   out_3094277237620606525[290] = 0;
   out_3094277237620606525[291] = 0;
   out_3094277237620606525[292] = 0;
   out_3094277237620606525[293] = 0;
   out_3094277237620606525[294] = 0;
   out_3094277237620606525[295] = 0;
   out_3094277237620606525[296] = 0;
   out_3094277237620606525[297] = 0;
   out_3094277237620606525[298] = 0;
   out_3094277237620606525[299] = 0;
   out_3094277237620606525[300] = 0;
   out_3094277237620606525[301] = 0;
   out_3094277237620606525[302] = 0;
   out_3094277237620606525[303] = 0;
   out_3094277237620606525[304] = 1;
   out_3094277237620606525[305] = 0;
   out_3094277237620606525[306] = 0;
   out_3094277237620606525[307] = 0;
   out_3094277237620606525[308] = 0;
   out_3094277237620606525[309] = 0;
   out_3094277237620606525[310] = 0;
   out_3094277237620606525[311] = 0;
   out_3094277237620606525[312] = 0;
   out_3094277237620606525[313] = 0;
   out_3094277237620606525[314] = 0;
   out_3094277237620606525[315] = 0;
   out_3094277237620606525[316] = 0;
   out_3094277237620606525[317] = 0;
   out_3094277237620606525[318] = 0;
   out_3094277237620606525[319] = 0;
   out_3094277237620606525[320] = 0;
   out_3094277237620606525[321] = 0;
   out_3094277237620606525[322] = 0;
   out_3094277237620606525[323] = 1;
}
void h_4(double *state, double *unused, double *out_8966126842197524709) {
   out_8966126842197524709[0] = state[6] + state[9];
   out_8966126842197524709[1] = state[7] + state[10];
   out_8966126842197524709[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_641054481852540698) {
   out_641054481852540698[0] = 0;
   out_641054481852540698[1] = 0;
   out_641054481852540698[2] = 0;
   out_641054481852540698[3] = 0;
   out_641054481852540698[4] = 0;
   out_641054481852540698[5] = 0;
   out_641054481852540698[6] = 1;
   out_641054481852540698[7] = 0;
   out_641054481852540698[8] = 0;
   out_641054481852540698[9] = 1;
   out_641054481852540698[10] = 0;
   out_641054481852540698[11] = 0;
   out_641054481852540698[12] = 0;
   out_641054481852540698[13] = 0;
   out_641054481852540698[14] = 0;
   out_641054481852540698[15] = 0;
   out_641054481852540698[16] = 0;
   out_641054481852540698[17] = 0;
   out_641054481852540698[18] = 0;
   out_641054481852540698[19] = 0;
   out_641054481852540698[20] = 0;
   out_641054481852540698[21] = 0;
   out_641054481852540698[22] = 0;
   out_641054481852540698[23] = 0;
   out_641054481852540698[24] = 0;
   out_641054481852540698[25] = 1;
   out_641054481852540698[26] = 0;
   out_641054481852540698[27] = 0;
   out_641054481852540698[28] = 1;
   out_641054481852540698[29] = 0;
   out_641054481852540698[30] = 0;
   out_641054481852540698[31] = 0;
   out_641054481852540698[32] = 0;
   out_641054481852540698[33] = 0;
   out_641054481852540698[34] = 0;
   out_641054481852540698[35] = 0;
   out_641054481852540698[36] = 0;
   out_641054481852540698[37] = 0;
   out_641054481852540698[38] = 0;
   out_641054481852540698[39] = 0;
   out_641054481852540698[40] = 0;
   out_641054481852540698[41] = 0;
   out_641054481852540698[42] = 0;
   out_641054481852540698[43] = 0;
   out_641054481852540698[44] = 1;
   out_641054481852540698[45] = 0;
   out_641054481852540698[46] = 0;
   out_641054481852540698[47] = 1;
   out_641054481852540698[48] = 0;
   out_641054481852540698[49] = 0;
   out_641054481852540698[50] = 0;
   out_641054481852540698[51] = 0;
   out_641054481852540698[52] = 0;
   out_641054481852540698[53] = 0;
}
void h_10(double *state, double *unused, double *out_7218356862001512524) {
   out_7218356862001512524[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_7218356862001512524[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_7218356862001512524[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6416512439383232257) {
   out_6416512439383232257[0] = 0;
   out_6416512439383232257[1] = 9.8100000000000005*cos(state[1]);
   out_6416512439383232257[2] = 0;
   out_6416512439383232257[3] = 0;
   out_6416512439383232257[4] = -state[8];
   out_6416512439383232257[5] = state[7];
   out_6416512439383232257[6] = 0;
   out_6416512439383232257[7] = state[5];
   out_6416512439383232257[8] = -state[4];
   out_6416512439383232257[9] = 0;
   out_6416512439383232257[10] = 0;
   out_6416512439383232257[11] = 0;
   out_6416512439383232257[12] = 1;
   out_6416512439383232257[13] = 0;
   out_6416512439383232257[14] = 0;
   out_6416512439383232257[15] = 1;
   out_6416512439383232257[16] = 0;
   out_6416512439383232257[17] = 0;
   out_6416512439383232257[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6416512439383232257[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6416512439383232257[20] = 0;
   out_6416512439383232257[21] = state[8];
   out_6416512439383232257[22] = 0;
   out_6416512439383232257[23] = -state[6];
   out_6416512439383232257[24] = -state[5];
   out_6416512439383232257[25] = 0;
   out_6416512439383232257[26] = state[3];
   out_6416512439383232257[27] = 0;
   out_6416512439383232257[28] = 0;
   out_6416512439383232257[29] = 0;
   out_6416512439383232257[30] = 0;
   out_6416512439383232257[31] = 1;
   out_6416512439383232257[32] = 0;
   out_6416512439383232257[33] = 0;
   out_6416512439383232257[34] = 1;
   out_6416512439383232257[35] = 0;
   out_6416512439383232257[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6416512439383232257[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6416512439383232257[38] = 0;
   out_6416512439383232257[39] = -state[7];
   out_6416512439383232257[40] = state[6];
   out_6416512439383232257[41] = 0;
   out_6416512439383232257[42] = state[4];
   out_6416512439383232257[43] = -state[3];
   out_6416512439383232257[44] = 0;
   out_6416512439383232257[45] = 0;
   out_6416512439383232257[46] = 0;
   out_6416512439383232257[47] = 0;
   out_6416512439383232257[48] = 0;
   out_6416512439383232257[49] = 0;
   out_6416512439383232257[50] = 1;
   out_6416512439383232257[51] = 0;
   out_6416512439383232257[52] = 0;
   out_6416512439383232257[53] = 1;
}
void h_13(double *state, double *unused, double *out_4665077883382816557) {
   out_4665077883382816557[0] = state[3];
   out_4665077883382816557[1] = state[4];
   out_4665077883382816557[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2571219343479792103) {
   out_2571219343479792103[0] = 0;
   out_2571219343479792103[1] = 0;
   out_2571219343479792103[2] = 0;
   out_2571219343479792103[3] = 1;
   out_2571219343479792103[4] = 0;
   out_2571219343479792103[5] = 0;
   out_2571219343479792103[6] = 0;
   out_2571219343479792103[7] = 0;
   out_2571219343479792103[8] = 0;
   out_2571219343479792103[9] = 0;
   out_2571219343479792103[10] = 0;
   out_2571219343479792103[11] = 0;
   out_2571219343479792103[12] = 0;
   out_2571219343479792103[13] = 0;
   out_2571219343479792103[14] = 0;
   out_2571219343479792103[15] = 0;
   out_2571219343479792103[16] = 0;
   out_2571219343479792103[17] = 0;
   out_2571219343479792103[18] = 0;
   out_2571219343479792103[19] = 0;
   out_2571219343479792103[20] = 0;
   out_2571219343479792103[21] = 0;
   out_2571219343479792103[22] = 1;
   out_2571219343479792103[23] = 0;
   out_2571219343479792103[24] = 0;
   out_2571219343479792103[25] = 0;
   out_2571219343479792103[26] = 0;
   out_2571219343479792103[27] = 0;
   out_2571219343479792103[28] = 0;
   out_2571219343479792103[29] = 0;
   out_2571219343479792103[30] = 0;
   out_2571219343479792103[31] = 0;
   out_2571219343479792103[32] = 0;
   out_2571219343479792103[33] = 0;
   out_2571219343479792103[34] = 0;
   out_2571219343479792103[35] = 0;
   out_2571219343479792103[36] = 0;
   out_2571219343479792103[37] = 0;
   out_2571219343479792103[38] = 0;
   out_2571219343479792103[39] = 0;
   out_2571219343479792103[40] = 0;
   out_2571219343479792103[41] = 1;
   out_2571219343479792103[42] = 0;
   out_2571219343479792103[43] = 0;
   out_2571219343479792103[44] = 0;
   out_2571219343479792103[45] = 0;
   out_2571219343479792103[46] = 0;
   out_2571219343479792103[47] = 0;
   out_2571219343479792103[48] = 0;
   out_2571219343479792103[49] = 0;
   out_2571219343479792103[50] = 0;
   out_2571219343479792103[51] = 0;
   out_2571219343479792103[52] = 0;
   out_2571219343479792103[53] = 0;
}
void h_14(double *state, double *unused, double *out_6885640217960215473) {
   out_6885640217960215473[0] = state[6];
   out_6885640217960215473[1] = state[7];
   out_6885640217960215473[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3723842914147912994) {
   out_3723842914147912994[0] = 0;
   out_3723842914147912994[1] = 0;
   out_3723842914147912994[2] = 0;
   out_3723842914147912994[3] = 0;
   out_3723842914147912994[4] = 0;
   out_3723842914147912994[5] = 0;
   out_3723842914147912994[6] = 1;
   out_3723842914147912994[7] = 0;
   out_3723842914147912994[8] = 0;
   out_3723842914147912994[9] = 0;
   out_3723842914147912994[10] = 0;
   out_3723842914147912994[11] = 0;
   out_3723842914147912994[12] = 0;
   out_3723842914147912994[13] = 0;
   out_3723842914147912994[14] = 0;
   out_3723842914147912994[15] = 0;
   out_3723842914147912994[16] = 0;
   out_3723842914147912994[17] = 0;
   out_3723842914147912994[18] = 0;
   out_3723842914147912994[19] = 0;
   out_3723842914147912994[20] = 0;
   out_3723842914147912994[21] = 0;
   out_3723842914147912994[22] = 0;
   out_3723842914147912994[23] = 0;
   out_3723842914147912994[24] = 0;
   out_3723842914147912994[25] = 1;
   out_3723842914147912994[26] = 0;
   out_3723842914147912994[27] = 0;
   out_3723842914147912994[28] = 0;
   out_3723842914147912994[29] = 0;
   out_3723842914147912994[30] = 0;
   out_3723842914147912994[31] = 0;
   out_3723842914147912994[32] = 0;
   out_3723842914147912994[33] = 0;
   out_3723842914147912994[34] = 0;
   out_3723842914147912994[35] = 0;
   out_3723842914147912994[36] = 0;
   out_3723842914147912994[37] = 0;
   out_3723842914147912994[38] = 0;
   out_3723842914147912994[39] = 0;
   out_3723842914147912994[40] = 0;
   out_3723842914147912994[41] = 0;
   out_3723842914147912994[42] = 0;
   out_3723842914147912994[43] = 0;
   out_3723842914147912994[44] = 1;
   out_3723842914147912994[45] = 0;
   out_3723842914147912994[46] = 0;
   out_3723842914147912994[47] = 0;
   out_3723842914147912994[48] = 0;
   out_3723842914147912994[49] = 0;
   out_3723842914147912994[50] = 0;
   out_3723842914147912994[51] = 0;
   out_3723842914147912994[52] = 0;
   out_3723842914147912994[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7337273534871130421) {
  err_fun(nom_x, delta_x, out_7337273534871130421);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7370167163616029780) {
  inv_err_fun(nom_x, true_x, out_7370167163616029780);
}
void pose_H_mod_fun(double *state, double *out_1839001963735438802) {
  H_mod_fun(state, out_1839001963735438802);
}
void pose_f_fun(double *state, double dt, double *out_3683398569821655413) {
  f_fun(state,  dt, out_3683398569821655413);
}
void pose_F_fun(double *state, double dt, double *out_3094277237620606525) {
  F_fun(state,  dt, out_3094277237620606525);
}
void pose_h_4(double *state, double *unused, double *out_8966126842197524709) {
  h_4(state, unused, out_8966126842197524709);
}
void pose_H_4(double *state, double *unused, double *out_641054481852540698) {
  H_4(state, unused, out_641054481852540698);
}
void pose_h_10(double *state, double *unused, double *out_7218356862001512524) {
  h_10(state, unused, out_7218356862001512524);
}
void pose_H_10(double *state, double *unused, double *out_6416512439383232257) {
  H_10(state, unused, out_6416512439383232257);
}
void pose_h_13(double *state, double *unused, double *out_4665077883382816557) {
  h_13(state, unused, out_4665077883382816557);
}
void pose_H_13(double *state, double *unused, double *out_2571219343479792103) {
  H_13(state, unused, out_2571219343479792103);
}
void pose_h_14(double *state, double *unused, double *out_6885640217960215473) {
  h_14(state, unused, out_6885640217960215473);
}
void pose_H_14(double *state, double *unused, double *out_3723842914147912994) {
  H_14(state, unused, out_3723842914147912994);
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
