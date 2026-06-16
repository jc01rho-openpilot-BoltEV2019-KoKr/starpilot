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
void err_fun(double *nom_x, double *delta_x, double *out_6392571160168570842) {
   out_6392571160168570842[0] = delta_x[0] + nom_x[0];
   out_6392571160168570842[1] = delta_x[1] + nom_x[1];
   out_6392571160168570842[2] = delta_x[2] + nom_x[2];
   out_6392571160168570842[3] = delta_x[3] + nom_x[3];
   out_6392571160168570842[4] = delta_x[4] + nom_x[4];
   out_6392571160168570842[5] = delta_x[5] + nom_x[5];
   out_6392571160168570842[6] = delta_x[6] + nom_x[6];
   out_6392571160168570842[7] = delta_x[7] + nom_x[7];
   out_6392571160168570842[8] = delta_x[8] + nom_x[8];
   out_6392571160168570842[9] = delta_x[9] + nom_x[9];
   out_6392571160168570842[10] = delta_x[10] + nom_x[10];
   out_6392571160168570842[11] = delta_x[11] + nom_x[11];
   out_6392571160168570842[12] = delta_x[12] + nom_x[12];
   out_6392571160168570842[13] = delta_x[13] + nom_x[13];
   out_6392571160168570842[14] = delta_x[14] + nom_x[14];
   out_6392571160168570842[15] = delta_x[15] + nom_x[15];
   out_6392571160168570842[16] = delta_x[16] + nom_x[16];
   out_6392571160168570842[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_70108598084165787) {
   out_70108598084165787[0] = -nom_x[0] + true_x[0];
   out_70108598084165787[1] = -nom_x[1] + true_x[1];
   out_70108598084165787[2] = -nom_x[2] + true_x[2];
   out_70108598084165787[3] = -nom_x[3] + true_x[3];
   out_70108598084165787[4] = -nom_x[4] + true_x[4];
   out_70108598084165787[5] = -nom_x[5] + true_x[5];
   out_70108598084165787[6] = -nom_x[6] + true_x[6];
   out_70108598084165787[7] = -nom_x[7] + true_x[7];
   out_70108598084165787[8] = -nom_x[8] + true_x[8];
   out_70108598084165787[9] = -nom_x[9] + true_x[9];
   out_70108598084165787[10] = -nom_x[10] + true_x[10];
   out_70108598084165787[11] = -nom_x[11] + true_x[11];
   out_70108598084165787[12] = -nom_x[12] + true_x[12];
   out_70108598084165787[13] = -nom_x[13] + true_x[13];
   out_70108598084165787[14] = -nom_x[14] + true_x[14];
   out_70108598084165787[15] = -nom_x[15] + true_x[15];
   out_70108598084165787[16] = -nom_x[16] + true_x[16];
   out_70108598084165787[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7031029695439970094) {
   out_7031029695439970094[0] = 1.0;
   out_7031029695439970094[1] = 0.0;
   out_7031029695439970094[2] = 0.0;
   out_7031029695439970094[3] = 0.0;
   out_7031029695439970094[4] = 0.0;
   out_7031029695439970094[5] = 0.0;
   out_7031029695439970094[6] = 0.0;
   out_7031029695439970094[7] = 0.0;
   out_7031029695439970094[8] = 0.0;
   out_7031029695439970094[9] = 0.0;
   out_7031029695439970094[10] = 0.0;
   out_7031029695439970094[11] = 0.0;
   out_7031029695439970094[12] = 0.0;
   out_7031029695439970094[13] = 0.0;
   out_7031029695439970094[14] = 0.0;
   out_7031029695439970094[15] = 0.0;
   out_7031029695439970094[16] = 0.0;
   out_7031029695439970094[17] = 0.0;
   out_7031029695439970094[18] = 0.0;
   out_7031029695439970094[19] = 1.0;
   out_7031029695439970094[20] = 0.0;
   out_7031029695439970094[21] = 0.0;
   out_7031029695439970094[22] = 0.0;
   out_7031029695439970094[23] = 0.0;
   out_7031029695439970094[24] = 0.0;
   out_7031029695439970094[25] = 0.0;
   out_7031029695439970094[26] = 0.0;
   out_7031029695439970094[27] = 0.0;
   out_7031029695439970094[28] = 0.0;
   out_7031029695439970094[29] = 0.0;
   out_7031029695439970094[30] = 0.0;
   out_7031029695439970094[31] = 0.0;
   out_7031029695439970094[32] = 0.0;
   out_7031029695439970094[33] = 0.0;
   out_7031029695439970094[34] = 0.0;
   out_7031029695439970094[35] = 0.0;
   out_7031029695439970094[36] = 0.0;
   out_7031029695439970094[37] = 0.0;
   out_7031029695439970094[38] = 1.0;
   out_7031029695439970094[39] = 0.0;
   out_7031029695439970094[40] = 0.0;
   out_7031029695439970094[41] = 0.0;
   out_7031029695439970094[42] = 0.0;
   out_7031029695439970094[43] = 0.0;
   out_7031029695439970094[44] = 0.0;
   out_7031029695439970094[45] = 0.0;
   out_7031029695439970094[46] = 0.0;
   out_7031029695439970094[47] = 0.0;
   out_7031029695439970094[48] = 0.0;
   out_7031029695439970094[49] = 0.0;
   out_7031029695439970094[50] = 0.0;
   out_7031029695439970094[51] = 0.0;
   out_7031029695439970094[52] = 0.0;
   out_7031029695439970094[53] = 0.0;
   out_7031029695439970094[54] = 0.0;
   out_7031029695439970094[55] = 0.0;
   out_7031029695439970094[56] = 0.0;
   out_7031029695439970094[57] = 1.0;
   out_7031029695439970094[58] = 0.0;
   out_7031029695439970094[59] = 0.0;
   out_7031029695439970094[60] = 0.0;
   out_7031029695439970094[61] = 0.0;
   out_7031029695439970094[62] = 0.0;
   out_7031029695439970094[63] = 0.0;
   out_7031029695439970094[64] = 0.0;
   out_7031029695439970094[65] = 0.0;
   out_7031029695439970094[66] = 0.0;
   out_7031029695439970094[67] = 0.0;
   out_7031029695439970094[68] = 0.0;
   out_7031029695439970094[69] = 0.0;
   out_7031029695439970094[70] = 0.0;
   out_7031029695439970094[71] = 0.0;
   out_7031029695439970094[72] = 0.0;
   out_7031029695439970094[73] = 0.0;
   out_7031029695439970094[74] = 0.0;
   out_7031029695439970094[75] = 0.0;
   out_7031029695439970094[76] = 1.0;
   out_7031029695439970094[77] = 0.0;
   out_7031029695439970094[78] = 0.0;
   out_7031029695439970094[79] = 0.0;
   out_7031029695439970094[80] = 0.0;
   out_7031029695439970094[81] = 0.0;
   out_7031029695439970094[82] = 0.0;
   out_7031029695439970094[83] = 0.0;
   out_7031029695439970094[84] = 0.0;
   out_7031029695439970094[85] = 0.0;
   out_7031029695439970094[86] = 0.0;
   out_7031029695439970094[87] = 0.0;
   out_7031029695439970094[88] = 0.0;
   out_7031029695439970094[89] = 0.0;
   out_7031029695439970094[90] = 0.0;
   out_7031029695439970094[91] = 0.0;
   out_7031029695439970094[92] = 0.0;
   out_7031029695439970094[93] = 0.0;
   out_7031029695439970094[94] = 0.0;
   out_7031029695439970094[95] = 1.0;
   out_7031029695439970094[96] = 0.0;
   out_7031029695439970094[97] = 0.0;
   out_7031029695439970094[98] = 0.0;
   out_7031029695439970094[99] = 0.0;
   out_7031029695439970094[100] = 0.0;
   out_7031029695439970094[101] = 0.0;
   out_7031029695439970094[102] = 0.0;
   out_7031029695439970094[103] = 0.0;
   out_7031029695439970094[104] = 0.0;
   out_7031029695439970094[105] = 0.0;
   out_7031029695439970094[106] = 0.0;
   out_7031029695439970094[107] = 0.0;
   out_7031029695439970094[108] = 0.0;
   out_7031029695439970094[109] = 0.0;
   out_7031029695439970094[110] = 0.0;
   out_7031029695439970094[111] = 0.0;
   out_7031029695439970094[112] = 0.0;
   out_7031029695439970094[113] = 0.0;
   out_7031029695439970094[114] = 1.0;
   out_7031029695439970094[115] = 0.0;
   out_7031029695439970094[116] = 0.0;
   out_7031029695439970094[117] = 0.0;
   out_7031029695439970094[118] = 0.0;
   out_7031029695439970094[119] = 0.0;
   out_7031029695439970094[120] = 0.0;
   out_7031029695439970094[121] = 0.0;
   out_7031029695439970094[122] = 0.0;
   out_7031029695439970094[123] = 0.0;
   out_7031029695439970094[124] = 0.0;
   out_7031029695439970094[125] = 0.0;
   out_7031029695439970094[126] = 0.0;
   out_7031029695439970094[127] = 0.0;
   out_7031029695439970094[128] = 0.0;
   out_7031029695439970094[129] = 0.0;
   out_7031029695439970094[130] = 0.0;
   out_7031029695439970094[131] = 0.0;
   out_7031029695439970094[132] = 0.0;
   out_7031029695439970094[133] = 1.0;
   out_7031029695439970094[134] = 0.0;
   out_7031029695439970094[135] = 0.0;
   out_7031029695439970094[136] = 0.0;
   out_7031029695439970094[137] = 0.0;
   out_7031029695439970094[138] = 0.0;
   out_7031029695439970094[139] = 0.0;
   out_7031029695439970094[140] = 0.0;
   out_7031029695439970094[141] = 0.0;
   out_7031029695439970094[142] = 0.0;
   out_7031029695439970094[143] = 0.0;
   out_7031029695439970094[144] = 0.0;
   out_7031029695439970094[145] = 0.0;
   out_7031029695439970094[146] = 0.0;
   out_7031029695439970094[147] = 0.0;
   out_7031029695439970094[148] = 0.0;
   out_7031029695439970094[149] = 0.0;
   out_7031029695439970094[150] = 0.0;
   out_7031029695439970094[151] = 0.0;
   out_7031029695439970094[152] = 1.0;
   out_7031029695439970094[153] = 0.0;
   out_7031029695439970094[154] = 0.0;
   out_7031029695439970094[155] = 0.0;
   out_7031029695439970094[156] = 0.0;
   out_7031029695439970094[157] = 0.0;
   out_7031029695439970094[158] = 0.0;
   out_7031029695439970094[159] = 0.0;
   out_7031029695439970094[160] = 0.0;
   out_7031029695439970094[161] = 0.0;
   out_7031029695439970094[162] = 0.0;
   out_7031029695439970094[163] = 0.0;
   out_7031029695439970094[164] = 0.0;
   out_7031029695439970094[165] = 0.0;
   out_7031029695439970094[166] = 0.0;
   out_7031029695439970094[167] = 0.0;
   out_7031029695439970094[168] = 0.0;
   out_7031029695439970094[169] = 0.0;
   out_7031029695439970094[170] = 0.0;
   out_7031029695439970094[171] = 1.0;
   out_7031029695439970094[172] = 0.0;
   out_7031029695439970094[173] = 0.0;
   out_7031029695439970094[174] = 0.0;
   out_7031029695439970094[175] = 0.0;
   out_7031029695439970094[176] = 0.0;
   out_7031029695439970094[177] = 0.0;
   out_7031029695439970094[178] = 0.0;
   out_7031029695439970094[179] = 0.0;
   out_7031029695439970094[180] = 0.0;
   out_7031029695439970094[181] = 0.0;
   out_7031029695439970094[182] = 0.0;
   out_7031029695439970094[183] = 0.0;
   out_7031029695439970094[184] = 0.0;
   out_7031029695439970094[185] = 0.0;
   out_7031029695439970094[186] = 0.0;
   out_7031029695439970094[187] = 0.0;
   out_7031029695439970094[188] = 0.0;
   out_7031029695439970094[189] = 0.0;
   out_7031029695439970094[190] = 1.0;
   out_7031029695439970094[191] = 0.0;
   out_7031029695439970094[192] = 0.0;
   out_7031029695439970094[193] = 0.0;
   out_7031029695439970094[194] = 0.0;
   out_7031029695439970094[195] = 0.0;
   out_7031029695439970094[196] = 0.0;
   out_7031029695439970094[197] = 0.0;
   out_7031029695439970094[198] = 0.0;
   out_7031029695439970094[199] = 0.0;
   out_7031029695439970094[200] = 0.0;
   out_7031029695439970094[201] = 0.0;
   out_7031029695439970094[202] = 0.0;
   out_7031029695439970094[203] = 0.0;
   out_7031029695439970094[204] = 0.0;
   out_7031029695439970094[205] = 0.0;
   out_7031029695439970094[206] = 0.0;
   out_7031029695439970094[207] = 0.0;
   out_7031029695439970094[208] = 0.0;
   out_7031029695439970094[209] = 1.0;
   out_7031029695439970094[210] = 0.0;
   out_7031029695439970094[211] = 0.0;
   out_7031029695439970094[212] = 0.0;
   out_7031029695439970094[213] = 0.0;
   out_7031029695439970094[214] = 0.0;
   out_7031029695439970094[215] = 0.0;
   out_7031029695439970094[216] = 0.0;
   out_7031029695439970094[217] = 0.0;
   out_7031029695439970094[218] = 0.0;
   out_7031029695439970094[219] = 0.0;
   out_7031029695439970094[220] = 0.0;
   out_7031029695439970094[221] = 0.0;
   out_7031029695439970094[222] = 0.0;
   out_7031029695439970094[223] = 0.0;
   out_7031029695439970094[224] = 0.0;
   out_7031029695439970094[225] = 0.0;
   out_7031029695439970094[226] = 0.0;
   out_7031029695439970094[227] = 0.0;
   out_7031029695439970094[228] = 1.0;
   out_7031029695439970094[229] = 0.0;
   out_7031029695439970094[230] = 0.0;
   out_7031029695439970094[231] = 0.0;
   out_7031029695439970094[232] = 0.0;
   out_7031029695439970094[233] = 0.0;
   out_7031029695439970094[234] = 0.0;
   out_7031029695439970094[235] = 0.0;
   out_7031029695439970094[236] = 0.0;
   out_7031029695439970094[237] = 0.0;
   out_7031029695439970094[238] = 0.0;
   out_7031029695439970094[239] = 0.0;
   out_7031029695439970094[240] = 0.0;
   out_7031029695439970094[241] = 0.0;
   out_7031029695439970094[242] = 0.0;
   out_7031029695439970094[243] = 0.0;
   out_7031029695439970094[244] = 0.0;
   out_7031029695439970094[245] = 0.0;
   out_7031029695439970094[246] = 0.0;
   out_7031029695439970094[247] = 1.0;
   out_7031029695439970094[248] = 0.0;
   out_7031029695439970094[249] = 0.0;
   out_7031029695439970094[250] = 0.0;
   out_7031029695439970094[251] = 0.0;
   out_7031029695439970094[252] = 0.0;
   out_7031029695439970094[253] = 0.0;
   out_7031029695439970094[254] = 0.0;
   out_7031029695439970094[255] = 0.0;
   out_7031029695439970094[256] = 0.0;
   out_7031029695439970094[257] = 0.0;
   out_7031029695439970094[258] = 0.0;
   out_7031029695439970094[259] = 0.0;
   out_7031029695439970094[260] = 0.0;
   out_7031029695439970094[261] = 0.0;
   out_7031029695439970094[262] = 0.0;
   out_7031029695439970094[263] = 0.0;
   out_7031029695439970094[264] = 0.0;
   out_7031029695439970094[265] = 0.0;
   out_7031029695439970094[266] = 1.0;
   out_7031029695439970094[267] = 0.0;
   out_7031029695439970094[268] = 0.0;
   out_7031029695439970094[269] = 0.0;
   out_7031029695439970094[270] = 0.0;
   out_7031029695439970094[271] = 0.0;
   out_7031029695439970094[272] = 0.0;
   out_7031029695439970094[273] = 0.0;
   out_7031029695439970094[274] = 0.0;
   out_7031029695439970094[275] = 0.0;
   out_7031029695439970094[276] = 0.0;
   out_7031029695439970094[277] = 0.0;
   out_7031029695439970094[278] = 0.0;
   out_7031029695439970094[279] = 0.0;
   out_7031029695439970094[280] = 0.0;
   out_7031029695439970094[281] = 0.0;
   out_7031029695439970094[282] = 0.0;
   out_7031029695439970094[283] = 0.0;
   out_7031029695439970094[284] = 0.0;
   out_7031029695439970094[285] = 1.0;
   out_7031029695439970094[286] = 0.0;
   out_7031029695439970094[287] = 0.0;
   out_7031029695439970094[288] = 0.0;
   out_7031029695439970094[289] = 0.0;
   out_7031029695439970094[290] = 0.0;
   out_7031029695439970094[291] = 0.0;
   out_7031029695439970094[292] = 0.0;
   out_7031029695439970094[293] = 0.0;
   out_7031029695439970094[294] = 0.0;
   out_7031029695439970094[295] = 0.0;
   out_7031029695439970094[296] = 0.0;
   out_7031029695439970094[297] = 0.0;
   out_7031029695439970094[298] = 0.0;
   out_7031029695439970094[299] = 0.0;
   out_7031029695439970094[300] = 0.0;
   out_7031029695439970094[301] = 0.0;
   out_7031029695439970094[302] = 0.0;
   out_7031029695439970094[303] = 0.0;
   out_7031029695439970094[304] = 1.0;
   out_7031029695439970094[305] = 0.0;
   out_7031029695439970094[306] = 0.0;
   out_7031029695439970094[307] = 0.0;
   out_7031029695439970094[308] = 0.0;
   out_7031029695439970094[309] = 0.0;
   out_7031029695439970094[310] = 0.0;
   out_7031029695439970094[311] = 0.0;
   out_7031029695439970094[312] = 0.0;
   out_7031029695439970094[313] = 0.0;
   out_7031029695439970094[314] = 0.0;
   out_7031029695439970094[315] = 0.0;
   out_7031029695439970094[316] = 0.0;
   out_7031029695439970094[317] = 0.0;
   out_7031029695439970094[318] = 0.0;
   out_7031029695439970094[319] = 0.0;
   out_7031029695439970094[320] = 0.0;
   out_7031029695439970094[321] = 0.0;
   out_7031029695439970094[322] = 0.0;
   out_7031029695439970094[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4622611615613940133) {
   out_4622611615613940133[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4622611615613940133[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4622611615613940133[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4622611615613940133[3] = dt*state[12] + state[3];
   out_4622611615613940133[4] = dt*state[13] + state[4];
   out_4622611615613940133[5] = dt*state[14] + state[5];
   out_4622611615613940133[6] = state[6];
   out_4622611615613940133[7] = state[7];
   out_4622611615613940133[8] = state[8];
   out_4622611615613940133[9] = state[9];
   out_4622611615613940133[10] = state[10];
   out_4622611615613940133[11] = state[11];
   out_4622611615613940133[12] = state[12];
   out_4622611615613940133[13] = state[13];
   out_4622611615613940133[14] = state[14];
   out_4622611615613940133[15] = state[15];
   out_4622611615613940133[16] = state[16];
   out_4622611615613940133[17] = state[17];
}
void F_fun(double *state, double dt, double *out_542246045313485722) {
   out_542246045313485722[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_542246045313485722[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_542246045313485722[2] = 0;
   out_542246045313485722[3] = 0;
   out_542246045313485722[4] = 0;
   out_542246045313485722[5] = 0;
   out_542246045313485722[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_542246045313485722[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_542246045313485722[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_542246045313485722[9] = 0;
   out_542246045313485722[10] = 0;
   out_542246045313485722[11] = 0;
   out_542246045313485722[12] = 0;
   out_542246045313485722[13] = 0;
   out_542246045313485722[14] = 0;
   out_542246045313485722[15] = 0;
   out_542246045313485722[16] = 0;
   out_542246045313485722[17] = 0;
   out_542246045313485722[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_542246045313485722[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_542246045313485722[20] = 0;
   out_542246045313485722[21] = 0;
   out_542246045313485722[22] = 0;
   out_542246045313485722[23] = 0;
   out_542246045313485722[24] = 0;
   out_542246045313485722[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_542246045313485722[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_542246045313485722[27] = 0;
   out_542246045313485722[28] = 0;
   out_542246045313485722[29] = 0;
   out_542246045313485722[30] = 0;
   out_542246045313485722[31] = 0;
   out_542246045313485722[32] = 0;
   out_542246045313485722[33] = 0;
   out_542246045313485722[34] = 0;
   out_542246045313485722[35] = 0;
   out_542246045313485722[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_542246045313485722[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_542246045313485722[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_542246045313485722[39] = 0;
   out_542246045313485722[40] = 0;
   out_542246045313485722[41] = 0;
   out_542246045313485722[42] = 0;
   out_542246045313485722[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_542246045313485722[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_542246045313485722[45] = 0;
   out_542246045313485722[46] = 0;
   out_542246045313485722[47] = 0;
   out_542246045313485722[48] = 0;
   out_542246045313485722[49] = 0;
   out_542246045313485722[50] = 0;
   out_542246045313485722[51] = 0;
   out_542246045313485722[52] = 0;
   out_542246045313485722[53] = 0;
   out_542246045313485722[54] = 0;
   out_542246045313485722[55] = 0;
   out_542246045313485722[56] = 0;
   out_542246045313485722[57] = 1;
   out_542246045313485722[58] = 0;
   out_542246045313485722[59] = 0;
   out_542246045313485722[60] = 0;
   out_542246045313485722[61] = 0;
   out_542246045313485722[62] = 0;
   out_542246045313485722[63] = 0;
   out_542246045313485722[64] = 0;
   out_542246045313485722[65] = 0;
   out_542246045313485722[66] = dt;
   out_542246045313485722[67] = 0;
   out_542246045313485722[68] = 0;
   out_542246045313485722[69] = 0;
   out_542246045313485722[70] = 0;
   out_542246045313485722[71] = 0;
   out_542246045313485722[72] = 0;
   out_542246045313485722[73] = 0;
   out_542246045313485722[74] = 0;
   out_542246045313485722[75] = 0;
   out_542246045313485722[76] = 1;
   out_542246045313485722[77] = 0;
   out_542246045313485722[78] = 0;
   out_542246045313485722[79] = 0;
   out_542246045313485722[80] = 0;
   out_542246045313485722[81] = 0;
   out_542246045313485722[82] = 0;
   out_542246045313485722[83] = 0;
   out_542246045313485722[84] = 0;
   out_542246045313485722[85] = dt;
   out_542246045313485722[86] = 0;
   out_542246045313485722[87] = 0;
   out_542246045313485722[88] = 0;
   out_542246045313485722[89] = 0;
   out_542246045313485722[90] = 0;
   out_542246045313485722[91] = 0;
   out_542246045313485722[92] = 0;
   out_542246045313485722[93] = 0;
   out_542246045313485722[94] = 0;
   out_542246045313485722[95] = 1;
   out_542246045313485722[96] = 0;
   out_542246045313485722[97] = 0;
   out_542246045313485722[98] = 0;
   out_542246045313485722[99] = 0;
   out_542246045313485722[100] = 0;
   out_542246045313485722[101] = 0;
   out_542246045313485722[102] = 0;
   out_542246045313485722[103] = 0;
   out_542246045313485722[104] = dt;
   out_542246045313485722[105] = 0;
   out_542246045313485722[106] = 0;
   out_542246045313485722[107] = 0;
   out_542246045313485722[108] = 0;
   out_542246045313485722[109] = 0;
   out_542246045313485722[110] = 0;
   out_542246045313485722[111] = 0;
   out_542246045313485722[112] = 0;
   out_542246045313485722[113] = 0;
   out_542246045313485722[114] = 1;
   out_542246045313485722[115] = 0;
   out_542246045313485722[116] = 0;
   out_542246045313485722[117] = 0;
   out_542246045313485722[118] = 0;
   out_542246045313485722[119] = 0;
   out_542246045313485722[120] = 0;
   out_542246045313485722[121] = 0;
   out_542246045313485722[122] = 0;
   out_542246045313485722[123] = 0;
   out_542246045313485722[124] = 0;
   out_542246045313485722[125] = 0;
   out_542246045313485722[126] = 0;
   out_542246045313485722[127] = 0;
   out_542246045313485722[128] = 0;
   out_542246045313485722[129] = 0;
   out_542246045313485722[130] = 0;
   out_542246045313485722[131] = 0;
   out_542246045313485722[132] = 0;
   out_542246045313485722[133] = 1;
   out_542246045313485722[134] = 0;
   out_542246045313485722[135] = 0;
   out_542246045313485722[136] = 0;
   out_542246045313485722[137] = 0;
   out_542246045313485722[138] = 0;
   out_542246045313485722[139] = 0;
   out_542246045313485722[140] = 0;
   out_542246045313485722[141] = 0;
   out_542246045313485722[142] = 0;
   out_542246045313485722[143] = 0;
   out_542246045313485722[144] = 0;
   out_542246045313485722[145] = 0;
   out_542246045313485722[146] = 0;
   out_542246045313485722[147] = 0;
   out_542246045313485722[148] = 0;
   out_542246045313485722[149] = 0;
   out_542246045313485722[150] = 0;
   out_542246045313485722[151] = 0;
   out_542246045313485722[152] = 1;
   out_542246045313485722[153] = 0;
   out_542246045313485722[154] = 0;
   out_542246045313485722[155] = 0;
   out_542246045313485722[156] = 0;
   out_542246045313485722[157] = 0;
   out_542246045313485722[158] = 0;
   out_542246045313485722[159] = 0;
   out_542246045313485722[160] = 0;
   out_542246045313485722[161] = 0;
   out_542246045313485722[162] = 0;
   out_542246045313485722[163] = 0;
   out_542246045313485722[164] = 0;
   out_542246045313485722[165] = 0;
   out_542246045313485722[166] = 0;
   out_542246045313485722[167] = 0;
   out_542246045313485722[168] = 0;
   out_542246045313485722[169] = 0;
   out_542246045313485722[170] = 0;
   out_542246045313485722[171] = 1;
   out_542246045313485722[172] = 0;
   out_542246045313485722[173] = 0;
   out_542246045313485722[174] = 0;
   out_542246045313485722[175] = 0;
   out_542246045313485722[176] = 0;
   out_542246045313485722[177] = 0;
   out_542246045313485722[178] = 0;
   out_542246045313485722[179] = 0;
   out_542246045313485722[180] = 0;
   out_542246045313485722[181] = 0;
   out_542246045313485722[182] = 0;
   out_542246045313485722[183] = 0;
   out_542246045313485722[184] = 0;
   out_542246045313485722[185] = 0;
   out_542246045313485722[186] = 0;
   out_542246045313485722[187] = 0;
   out_542246045313485722[188] = 0;
   out_542246045313485722[189] = 0;
   out_542246045313485722[190] = 1;
   out_542246045313485722[191] = 0;
   out_542246045313485722[192] = 0;
   out_542246045313485722[193] = 0;
   out_542246045313485722[194] = 0;
   out_542246045313485722[195] = 0;
   out_542246045313485722[196] = 0;
   out_542246045313485722[197] = 0;
   out_542246045313485722[198] = 0;
   out_542246045313485722[199] = 0;
   out_542246045313485722[200] = 0;
   out_542246045313485722[201] = 0;
   out_542246045313485722[202] = 0;
   out_542246045313485722[203] = 0;
   out_542246045313485722[204] = 0;
   out_542246045313485722[205] = 0;
   out_542246045313485722[206] = 0;
   out_542246045313485722[207] = 0;
   out_542246045313485722[208] = 0;
   out_542246045313485722[209] = 1;
   out_542246045313485722[210] = 0;
   out_542246045313485722[211] = 0;
   out_542246045313485722[212] = 0;
   out_542246045313485722[213] = 0;
   out_542246045313485722[214] = 0;
   out_542246045313485722[215] = 0;
   out_542246045313485722[216] = 0;
   out_542246045313485722[217] = 0;
   out_542246045313485722[218] = 0;
   out_542246045313485722[219] = 0;
   out_542246045313485722[220] = 0;
   out_542246045313485722[221] = 0;
   out_542246045313485722[222] = 0;
   out_542246045313485722[223] = 0;
   out_542246045313485722[224] = 0;
   out_542246045313485722[225] = 0;
   out_542246045313485722[226] = 0;
   out_542246045313485722[227] = 0;
   out_542246045313485722[228] = 1;
   out_542246045313485722[229] = 0;
   out_542246045313485722[230] = 0;
   out_542246045313485722[231] = 0;
   out_542246045313485722[232] = 0;
   out_542246045313485722[233] = 0;
   out_542246045313485722[234] = 0;
   out_542246045313485722[235] = 0;
   out_542246045313485722[236] = 0;
   out_542246045313485722[237] = 0;
   out_542246045313485722[238] = 0;
   out_542246045313485722[239] = 0;
   out_542246045313485722[240] = 0;
   out_542246045313485722[241] = 0;
   out_542246045313485722[242] = 0;
   out_542246045313485722[243] = 0;
   out_542246045313485722[244] = 0;
   out_542246045313485722[245] = 0;
   out_542246045313485722[246] = 0;
   out_542246045313485722[247] = 1;
   out_542246045313485722[248] = 0;
   out_542246045313485722[249] = 0;
   out_542246045313485722[250] = 0;
   out_542246045313485722[251] = 0;
   out_542246045313485722[252] = 0;
   out_542246045313485722[253] = 0;
   out_542246045313485722[254] = 0;
   out_542246045313485722[255] = 0;
   out_542246045313485722[256] = 0;
   out_542246045313485722[257] = 0;
   out_542246045313485722[258] = 0;
   out_542246045313485722[259] = 0;
   out_542246045313485722[260] = 0;
   out_542246045313485722[261] = 0;
   out_542246045313485722[262] = 0;
   out_542246045313485722[263] = 0;
   out_542246045313485722[264] = 0;
   out_542246045313485722[265] = 0;
   out_542246045313485722[266] = 1;
   out_542246045313485722[267] = 0;
   out_542246045313485722[268] = 0;
   out_542246045313485722[269] = 0;
   out_542246045313485722[270] = 0;
   out_542246045313485722[271] = 0;
   out_542246045313485722[272] = 0;
   out_542246045313485722[273] = 0;
   out_542246045313485722[274] = 0;
   out_542246045313485722[275] = 0;
   out_542246045313485722[276] = 0;
   out_542246045313485722[277] = 0;
   out_542246045313485722[278] = 0;
   out_542246045313485722[279] = 0;
   out_542246045313485722[280] = 0;
   out_542246045313485722[281] = 0;
   out_542246045313485722[282] = 0;
   out_542246045313485722[283] = 0;
   out_542246045313485722[284] = 0;
   out_542246045313485722[285] = 1;
   out_542246045313485722[286] = 0;
   out_542246045313485722[287] = 0;
   out_542246045313485722[288] = 0;
   out_542246045313485722[289] = 0;
   out_542246045313485722[290] = 0;
   out_542246045313485722[291] = 0;
   out_542246045313485722[292] = 0;
   out_542246045313485722[293] = 0;
   out_542246045313485722[294] = 0;
   out_542246045313485722[295] = 0;
   out_542246045313485722[296] = 0;
   out_542246045313485722[297] = 0;
   out_542246045313485722[298] = 0;
   out_542246045313485722[299] = 0;
   out_542246045313485722[300] = 0;
   out_542246045313485722[301] = 0;
   out_542246045313485722[302] = 0;
   out_542246045313485722[303] = 0;
   out_542246045313485722[304] = 1;
   out_542246045313485722[305] = 0;
   out_542246045313485722[306] = 0;
   out_542246045313485722[307] = 0;
   out_542246045313485722[308] = 0;
   out_542246045313485722[309] = 0;
   out_542246045313485722[310] = 0;
   out_542246045313485722[311] = 0;
   out_542246045313485722[312] = 0;
   out_542246045313485722[313] = 0;
   out_542246045313485722[314] = 0;
   out_542246045313485722[315] = 0;
   out_542246045313485722[316] = 0;
   out_542246045313485722[317] = 0;
   out_542246045313485722[318] = 0;
   out_542246045313485722[319] = 0;
   out_542246045313485722[320] = 0;
   out_542246045313485722[321] = 0;
   out_542246045313485722[322] = 0;
   out_542246045313485722[323] = 1;
}
void h_4(double *state, double *unused, double *out_6293306196609579881) {
   out_6293306196609579881[0] = state[6] + state[9];
   out_6293306196609579881[1] = state[7] + state[10];
   out_6293306196609579881[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1878511310400889359) {
   out_1878511310400889359[0] = 0;
   out_1878511310400889359[1] = 0;
   out_1878511310400889359[2] = 0;
   out_1878511310400889359[3] = 0;
   out_1878511310400889359[4] = 0;
   out_1878511310400889359[5] = 0;
   out_1878511310400889359[6] = 1;
   out_1878511310400889359[7] = 0;
   out_1878511310400889359[8] = 0;
   out_1878511310400889359[9] = 1;
   out_1878511310400889359[10] = 0;
   out_1878511310400889359[11] = 0;
   out_1878511310400889359[12] = 0;
   out_1878511310400889359[13] = 0;
   out_1878511310400889359[14] = 0;
   out_1878511310400889359[15] = 0;
   out_1878511310400889359[16] = 0;
   out_1878511310400889359[17] = 0;
   out_1878511310400889359[18] = 0;
   out_1878511310400889359[19] = 0;
   out_1878511310400889359[20] = 0;
   out_1878511310400889359[21] = 0;
   out_1878511310400889359[22] = 0;
   out_1878511310400889359[23] = 0;
   out_1878511310400889359[24] = 0;
   out_1878511310400889359[25] = 1;
   out_1878511310400889359[26] = 0;
   out_1878511310400889359[27] = 0;
   out_1878511310400889359[28] = 1;
   out_1878511310400889359[29] = 0;
   out_1878511310400889359[30] = 0;
   out_1878511310400889359[31] = 0;
   out_1878511310400889359[32] = 0;
   out_1878511310400889359[33] = 0;
   out_1878511310400889359[34] = 0;
   out_1878511310400889359[35] = 0;
   out_1878511310400889359[36] = 0;
   out_1878511310400889359[37] = 0;
   out_1878511310400889359[38] = 0;
   out_1878511310400889359[39] = 0;
   out_1878511310400889359[40] = 0;
   out_1878511310400889359[41] = 0;
   out_1878511310400889359[42] = 0;
   out_1878511310400889359[43] = 0;
   out_1878511310400889359[44] = 1;
   out_1878511310400889359[45] = 0;
   out_1878511310400889359[46] = 0;
   out_1878511310400889359[47] = 1;
   out_1878511310400889359[48] = 0;
   out_1878511310400889359[49] = 0;
   out_1878511310400889359[50] = 0;
   out_1878511310400889359[51] = 0;
   out_1878511310400889359[52] = 0;
   out_1878511310400889359[53] = 0;
}
void h_10(double *state, double *unused, double *out_8801939057301033560) {
   out_8801939057301033560[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8801939057301033560[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8801939057301033560[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2335330326985309171) {
   out_2335330326985309171[0] = 0;
   out_2335330326985309171[1] = 9.8100000000000005*cos(state[1]);
   out_2335330326985309171[2] = 0;
   out_2335330326985309171[3] = 0;
   out_2335330326985309171[4] = -state[8];
   out_2335330326985309171[5] = state[7];
   out_2335330326985309171[6] = 0;
   out_2335330326985309171[7] = state[5];
   out_2335330326985309171[8] = -state[4];
   out_2335330326985309171[9] = 0;
   out_2335330326985309171[10] = 0;
   out_2335330326985309171[11] = 0;
   out_2335330326985309171[12] = 1;
   out_2335330326985309171[13] = 0;
   out_2335330326985309171[14] = 0;
   out_2335330326985309171[15] = 1;
   out_2335330326985309171[16] = 0;
   out_2335330326985309171[17] = 0;
   out_2335330326985309171[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2335330326985309171[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2335330326985309171[20] = 0;
   out_2335330326985309171[21] = state[8];
   out_2335330326985309171[22] = 0;
   out_2335330326985309171[23] = -state[6];
   out_2335330326985309171[24] = -state[5];
   out_2335330326985309171[25] = 0;
   out_2335330326985309171[26] = state[3];
   out_2335330326985309171[27] = 0;
   out_2335330326985309171[28] = 0;
   out_2335330326985309171[29] = 0;
   out_2335330326985309171[30] = 0;
   out_2335330326985309171[31] = 1;
   out_2335330326985309171[32] = 0;
   out_2335330326985309171[33] = 0;
   out_2335330326985309171[34] = 1;
   out_2335330326985309171[35] = 0;
   out_2335330326985309171[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2335330326985309171[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2335330326985309171[38] = 0;
   out_2335330326985309171[39] = -state[7];
   out_2335330326985309171[40] = state[6];
   out_2335330326985309171[41] = 0;
   out_2335330326985309171[42] = state[4];
   out_2335330326985309171[43] = -state[3];
   out_2335330326985309171[44] = 0;
   out_2335330326985309171[45] = 0;
   out_2335330326985309171[46] = 0;
   out_2335330326985309171[47] = 0;
   out_2335330326985309171[48] = 0;
   out_2335330326985309171[49] = 0;
   out_2335330326985309171[50] = 1;
   out_2335330326985309171[51] = 0;
   out_2335330326985309171[52] = 0;
   out_2335330326985309171[53] = 1;
}
void h_13(double *state, double *unused, double *out_442641261201264592) {
   out_442641261201264592[0] = state[3];
   out_442641261201264592[1] = state[4];
   out_442641261201264592[2] = state[5];
}
void H_13(double *state, double *unused, double *out_5712266773703413383) {
   out_5712266773703413383[0] = 0;
   out_5712266773703413383[1] = 0;
   out_5712266773703413383[2] = 0;
   out_5712266773703413383[3] = 1;
   out_5712266773703413383[4] = 0;
   out_5712266773703413383[5] = 0;
   out_5712266773703413383[6] = 0;
   out_5712266773703413383[7] = 0;
   out_5712266773703413383[8] = 0;
   out_5712266773703413383[9] = 0;
   out_5712266773703413383[10] = 0;
   out_5712266773703413383[11] = 0;
   out_5712266773703413383[12] = 0;
   out_5712266773703413383[13] = 0;
   out_5712266773703413383[14] = 0;
   out_5712266773703413383[15] = 0;
   out_5712266773703413383[16] = 0;
   out_5712266773703413383[17] = 0;
   out_5712266773703413383[18] = 0;
   out_5712266773703413383[19] = 0;
   out_5712266773703413383[20] = 0;
   out_5712266773703413383[21] = 0;
   out_5712266773703413383[22] = 1;
   out_5712266773703413383[23] = 0;
   out_5712266773703413383[24] = 0;
   out_5712266773703413383[25] = 0;
   out_5712266773703413383[26] = 0;
   out_5712266773703413383[27] = 0;
   out_5712266773703413383[28] = 0;
   out_5712266773703413383[29] = 0;
   out_5712266773703413383[30] = 0;
   out_5712266773703413383[31] = 0;
   out_5712266773703413383[32] = 0;
   out_5712266773703413383[33] = 0;
   out_5712266773703413383[34] = 0;
   out_5712266773703413383[35] = 0;
   out_5712266773703413383[36] = 0;
   out_5712266773703413383[37] = 0;
   out_5712266773703413383[38] = 0;
   out_5712266773703413383[39] = 0;
   out_5712266773703413383[40] = 0;
   out_5712266773703413383[41] = 1;
   out_5712266773703413383[42] = 0;
   out_5712266773703413383[43] = 0;
   out_5712266773703413383[44] = 0;
   out_5712266773703413383[45] = 0;
   out_5712266773703413383[46] = 0;
   out_5712266773703413383[47] = 0;
   out_5712266773703413383[48] = 0;
   out_5712266773703413383[49] = 0;
   out_5712266773703413383[50] = 0;
   out_5712266773703413383[51] = 0;
   out_5712266773703413383[52] = 0;
   out_5712266773703413383[53] = 0;
}
void h_14(double *state, double *unused, double *out_6788275849684674744) {
   out_6788275849684674744[0] = state[6];
   out_6788275849684674744[1] = state[7];
   out_6788275849684674744[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4961299742696261655) {
   out_4961299742696261655[0] = 0;
   out_4961299742696261655[1] = 0;
   out_4961299742696261655[2] = 0;
   out_4961299742696261655[3] = 0;
   out_4961299742696261655[4] = 0;
   out_4961299742696261655[5] = 0;
   out_4961299742696261655[6] = 1;
   out_4961299742696261655[7] = 0;
   out_4961299742696261655[8] = 0;
   out_4961299742696261655[9] = 0;
   out_4961299742696261655[10] = 0;
   out_4961299742696261655[11] = 0;
   out_4961299742696261655[12] = 0;
   out_4961299742696261655[13] = 0;
   out_4961299742696261655[14] = 0;
   out_4961299742696261655[15] = 0;
   out_4961299742696261655[16] = 0;
   out_4961299742696261655[17] = 0;
   out_4961299742696261655[18] = 0;
   out_4961299742696261655[19] = 0;
   out_4961299742696261655[20] = 0;
   out_4961299742696261655[21] = 0;
   out_4961299742696261655[22] = 0;
   out_4961299742696261655[23] = 0;
   out_4961299742696261655[24] = 0;
   out_4961299742696261655[25] = 1;
   out_4961299742696261655[26] = 0;
   out_4961299742696261655[27] = 0;
   out_4961299742696261655[28] = 0;
   out_4961299742696261655[29] = 0;
   out_4961299742696261655[30] = 0;
   out_4961299742696261655[31] = 0;
   out_4961299742696261655[32] = 0;
   out_4961299742696261655[33] = 0;
   out_4961299742696261655[34] = 0;
   out_4961299742696261655[35] = 0;
   out_4961299742696261655[36] = 0;
   out_4961299742696261655[37] = 0;
   out_4961299742696261655[38] = 0;
   out_4961299742696261655[39] = 0;
   out_4961299742696261655[40] = 0;
   out_4961299742696261655[41] = 0;
   out_4961299742696261655[42] = 0;
   out_4961299742696261655[43] = 0;
   out_4961299742696261655[44] = 1;
   out_4961299742696261655[45] = 0;
   out_4961299742696261655[46] = 0;
   out_4961299742696261655[47] = 0;
   out_4961299742696261655[48] = 0;
   out_4961299742696261655[49] = 0;
   out_4961299742696261655[50] = 0;
   out_4961299742696261655[51] = 0;
   out_4961299742696261655[52] = 0;
   out_4961299742696261655[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_6392571160168570842) {
  err_fun(nom_x, delta_x, out_6392571160168570842);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_70108598084165787) {
  inv_err_fun(nom_x, true_x, out_70108598084165787);
}
void pose_H_mod_fun(double *state, double *out_7031029695439970094) {
  H_mod_fun(state, out_7031029695439970094);
}
void pose_f_fun(double *state, double dt, double *out_4622611615613940133) {
  f_fun(state,  dt, out_4622611615613940133);
}
void pose_F_fun(double *state, double dt, double *out_542246045313485722) {
  F_fun(state,  dt, out_542246045313485722);
}
void pose_h_4(double *state, double *unused, double *out_6293306196609579881) {
  h_4(state, unused, out_6293306196609579881);
}
void pose_H_4(double *state, double *unused, double *out_1878511310400889359) {
  H_4(state, unused, out_1878511310400889359);
}
void pose_h_10(double *state, double *unused, double *out_8801939057301033560) {
  h_10(state, unused, out_8801939057301033560);
}
void pose_H_10(double *state, double *unused, double *out_2335330326985309171) {
  H_10(state, unused, out_2335330326985309171);
}
void pose_h_13(double *state, double *unused, double *out_442641261201264592) {
  h_13(state, unused, out_442641261201264592);
}
void pose_H_13(double *state, double *unused, double *out_5712266773703413383) {
  H_13(state, unused, out_5712266773703413383);
}
void pose_h_14(double *state, double *unused, double *out_6788275849684674744) {
  h_14(state, unused, out_6788275849684674744);
}
void pose_H_14(double *state, double *unused, double *out_4961299742696261655) {
  H_14(state, unused, out_4961299742696261655);
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
