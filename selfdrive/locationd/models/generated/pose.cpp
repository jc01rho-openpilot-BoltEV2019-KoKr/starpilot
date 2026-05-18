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
void err_fun(double *nom_x, double *delta_x, double *out_7704133318394013706) {
   out_7704133318394013706[0] = delta_x[0] + nom_x[0];
   out_7704133318394013706[1] = delta_x[1] + nom_x[1];
   out_7704133318394013706[2] = delta_x[2] + nom_x[2];
   out_7704133318394013706[3] = delta_x[3] + nom_x[3];
   out_7704133318394013706[4] = delta_x[4] + nom_x[4];
   out_7704133318394013706[5] = delta_x[5] + nom_x[5];
   out_7704133318394013706[6] = delta_x[6] + nom_x[6];
   out_7704133318394013706[7] = delta_x[7] + nom_x[7];
   out_7704133318394013706[8] = delta_x[8] + nom_x[8];
   out_7704133318394013706[9] = delta_x[9] + nom_x[9];
   out_7704133318394013706[10] = delta_x[10] + nom_x[10];
   out_7704133318394013706[11] = delta_x[11] + nom_x[11];
   out_7704133318394013706[12] = delta_x[12] + nom_x[12];
   out_7704133318394013706[13] = delta_x[13] + nom_x[13];
   out_7704133318394013706[14] = delta_x[14] + nom_x[14];
   out_7704133318394013706[15] = delta_x[15] + nom_x[15];
   out_7704133318394013706[16] = delta_x[16] + nom_x[16];
   out_7704133318394013706[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5732870200970735889) {
   out_5732870200970735889[0] = -nom_x[0] + true_x[0];
   out_5732870200970735889[1] = -nom_x[1] + true_x[1];
   out_5732870200970735889[2] = -nom_x[2] + true_x[2];
   out_5732870200970735889[3] = -nom_x[3] + true_x[3];
   out_5732870200970735889[4] = -nom_x[4] + true_x[4];
   out_5732870200970735889[5] = -nom_x[5] + true_x[5];
   out_5732870200970735889[6] = -nom_x[6] + true_x[6];
   out_5732870200970735889[7] = -nom_x[7] + true_x[7];
   out_5732870200970735889[8] = -nom_x[8] + true_x[8];
   out_5732870200970735889[9] = -nom_x[9] + true_x[9];
   out_5732870200970735889[10] = -nom_x[10] + true_x[10];
   out_5732870200970735889[11] = -nom_x[11] + true_x[11];
   out_5732870200970735889[12] = -nom_x[12] + true_x[12];
   out_5732870200970735889[13] = -nom_x[13] + true_x[13];
   out_5732870200970735889[14] = -nom_x[14] + true_x[14];
   out_5732870200970735889[15] = -nom_x[15] + true_x[15];
   out_5732870200970735889[16] = -nom_x[16] + true_x[16];
   out_5732870200970735889[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5613029472060395452) {
   out_5613029472060395452[0] = 1.0;
   out_5613029472060395452[1] = 0.0;
   out_5613029472060395452[2] = 0.0;
   out_5613029472060395452[3] = 0.0;
   out_5613029472060395452[4] = 0.0;
   out_5613029472060395452[5] = 0.0;
   out_5613029472060395452[6] = 0.0;
   out_5613029472060395452[7] = 0.0;
   out_5613029472060395452[8] = 0.0;
   out_5613029472060395452[9] = 0.0;
   out_5613029472060395452[10] = 0.0;
   out_5613029472060395452[11] = 0.0;
   out_5613029472060395452[12] = 0.0;
   out_5613029472060395452[13] = 0.0;
   out_5613029472060395452[14] = 0.0;
   out_5613029472060395452[15] = 0.0;
   out_5613029472060395452[16] = 0.0;
   out_5613029472060395452[17] = 0.0;
   out_5613029472060395452[18] = 0.0;
   out_5613029472060395452[19] = 1.0;
   out_5613029472060395452[20] = 0.0;
   out_5613029472060395452[21] = 0.0;
   out_5613029472060395452[22] = 0.0;
   out_5613029472060395452[23] = 0.0;
   out_5613029472060395452[24] = 0.0;
   out_5613029472060395452[25] = 0.0;
   out_5613029472060395452[26] = 0.0;
   out_5613029472060395452[27] = 0.0;
   out_5613029472060395452[28] = 0.0;
   out_5613029472060395452[29] = 0.0;
   out_5613029472060395452[30] = 0.0;
   out_5613029472060395452[31] = 0.0;
   out_5613029472060395452[32] = 0.0;
   out_5613029472060395452[33] = 0.0;
   out_5613029472060395452[34] = 0.0;
   out_5613029472060395452[35] = 0.0;
   out_5613029472060395452[36] = 0.0;
   out_5613029472060395452[37] = 0.0;
   out_5613029472060395452[38] = 1.0;
   out_5613029472060395452[39] = 0.0;
   out_5613029472060395452[40] = 0.0;
   out_5613029472060395452[41] = 0.0;
   out_5613029472060395452[42] = 0.0;
   out_5613029472060395452[43] = 0.0;
   out_5613029472060395452[44] = 0.0;
   out_5613029472060395452[45] = 0.0;
   out_5613029472060395452[46] = 0.0;
   out_5613029472060395452[47] = 0.0;
   out_5613029472060395452[48] = 0.0;
   out_5613029472060395452[49] = 0.0;
   out_5613029472060395452[50] = 0.0;
   out_5613029472060395452[51] = 0.0;
   out_5613029472060395452[52] = 0.0;
   out_5613029472060395452[53] = 0.0;
   out_5613029472060395452[54] = 0.0;
   out_5613029472060395452[55] = 0.0;
   out_5613029472060395452[56] = 0.0;
   out_5613029472060395452[57] = 1.0;
   out_5613029472060395452[58] = 0.0;
   out_5613029472060395452[59] = 0.0;
   out_5613029472060395452[60] = 0.0;
   out_5613029472060395452[61] = 0.0;
   out_5613029472060395452[62] = 0.0;
   out_5613029472060395452[63] = 0.0;
   out_5613029472060395452[64] = 0.0;
   out_5613029472060395452[65] = 0.0;
   out_5613029472060395452[66] = 0.0;
   out_5613029472060395452[67] = 0.0;
   out_5613029472060395452[68] = 0.0;
   out_5613029472060395452[69] = 0.0;
   out_5613029472060395452[70] = 0.0;
   out_5613029472060395452[71] = 0.0;
   out_5613029472060395452[72] = 0.0;
   out_5613029472060395452[73] = 0.0;
   out_5613029472060395452[74] = 0.0;
   out_5613029472060395452[75] = 0.0;
   out_5613029472060395452[76] = 1.0;
   out_5613029472060395452[77] = 0.0;
   out_5613029472060395452[78] = 0.0;
   out_5613029472060395452[79] = 0.0;
   out_5613029472060395452[80] = 0.0;
   out_5613029472060395452[81] = 0.0;
   out_5613029472060395452[82] = 0.0;
   out_5613029472060395452[83] = 0.0;
   out_5613029472060395452[84] = 0.0;
   out_5613029472060395452[85] = 0.0;
   out_5613029472060395452[86] = 0.0;
   out_5613029472060395452[87] = 0.0;
   out_5613029472060395452[88] = 0.0;
   out_5613029472060395452[89] = 0.0;
   out_5613029472060395452[90] = 0.0;
   out_5613029472060395452[91] = 0.0;
   out_5613029472060395452[92] = 0.0;
   out_5613029472060395452[93] = 0.0;
   out_5613029472060395452[94] = 0.0;
   out_5613029472060395452[95] = 1.0;
   out_5613029472060395452[96] = 0.0;
   out_5613029472060395452[97] = 0.0;
   out_5613029472060395452[98] = 0.0;
   out_5613029472060395452[99] = 0.0;
   out_5613029472060395452[100] = 0.0;
   out_5613029472060395452[101] = 0.0;
   out_5613029472060395452[102] = 0.0;
   out_5613029472060395452[103] = 0.0;
   out_5613029472060395452[104] = 0.0;
   out_5613029472060395452[105] = 0.0;
   out_5613029472060395452[106] = 0.0;
   out_5613029472060395452[107] = 0.0;
   out_5613029472060395452[108] = 0.0;
   out_5613029472060395452[109] = 0.0;
   out_5613029472060395452[110] = 0.0;
   out_5613029472060395452[111] = 0.0;
   out_5613029472060395452[112] = 0.0;
   out_5613029472060395452[113] = 0.0;
   out_5613029472060395452[114] = 1.0;
   out_5613029472060395452[115] = 0.0;
   out_5613029472060395452[116] = 0.0;
   out_5613029472060395452[117] = 0.0;
   out_5613029472060395452[118] = 0.0;
   out_5613029472060395452[119] = 0.0;
   out_5613029472060395452[120] = 0.0;
   out_5613029472060395452[121] = 0.0;
   out_5613029472060395452[122] = 0.0;
   out_5613029472060395452[123] = 0.0;
   out_5613029472060395452[124] = 0.0;
   out_5613029472060395452[125] = 0.0;
   out_5613029472060395452[126] = 0.0;
   out_5613029472060395452[127] = 0.0;
   out_5613029472060395452[128] = 0.0;
   out_5613029472060395452[129] = 0.0;
   out_5613029472060395452[130] = 0.0;
   out_5613029472060395452[131] = 0.0;
   out_5613029472060395452[132] = 0.0;
   out_5613029472060395452[133] = 1.0;
   out_5613029472060395452[134] = 0.0;
   out_5613029472060395452[135] = 0.0;
   out_5613029472060395452[136] = 0.0;
   out_5613029472060395452[137] = 0.0;
   out_5613029472060395452[138] = 0.0;
   out_5613029472060395452[139] = 0.0;
   out_5613029472060395452[140] = 0.0;
   out_5613029472060395452[141] = 0.0;
   out_5613029472060395452[142] = 0.0;
   out_5613029472060395452[143] = 0.0;
   out_5613029472060395452[144] = 0.0;
   out_5613029472060395452[145] = 0.0;
   out_5613029472060395452[146] = 0.0;
   out_5613029472060395452[147] = 0.0;
   out_5613029472060395452[148] = 0.0;
   out_5613029472060395452[149] = 0.0;
   out_5613029472060395452[150] = 0.0;
   out_5613029472060395452[151] = 0.0;
   out_5613029472060395452[152] = 1.0;
   out_5613029472060395452[153] = 0.0;
   out_5613029472060395452[154] = 0.0;
   out_5613029472060395452[155] = 0.0;
   out_5613029472060395452[156] = 0.0;
   out_5613029472060395452[157] = 0.0;
   out_5613029472060395452[158] = 0.0;
   out_5613029472060395452[159] = 0.0;
   out_5613029472060395452[160] = 0.0;
   out_5613029472060395452[161] = 0.0;
   out_5613029472060395452[162] = 0.0;
   out_5613029472060395452[163] = 0.0;
   out_5613029472060395452[164] = 0.0;
   out_5613029472060395452[165] = 0.0;
   out_5613029472060395452[166] = 0.0;
   out_5613029472060395452[167] = 0.0;
   out_5613029472060395452[168] = 0.0;
   out_5613029472060395452[169] = 0.0;
   out_5613029472060395452[170] = 0.0;
   out_5613029472060395452[171] = 1.0;
   out_5613029472060395452[172] = 0.0;
   out_5613029472060395452[173] = 0.0;
   out_5613029472060395452[174] = 0.0;
   out_5613029472060395452[175] = 0.0;
   out_5613029472060395452[176] = 0.0;
   out_5613029472060395452[177] = 0.0;
   out_5613029472060395452[178] = 0.0;
   out_5613029472060395452[179] = 0.0;
   out_5613029472060395452[180] = 0.0;
   out_5613029472060395452[181] = 0.0;
   out_5613029472060395452[182] = 0.0;
   out_5613029472060395452[183] = 0.0;
   out_5613029472060395452[184] = 0.0;
   out_5613029472060395452[185] = 0.0;
   out_5613029472060395452[186] = 0.0;
   out_5613029472060395452[187] = 0.0;
   out_5613029472060395452[188] = 0.0;
   out_5613029472060395452[189] = 0.0;
   out_5613029472060395452[190] = 1.0;
   out_5613029472060395452[191] = 0.0;
   out_5613029472060395452[192] = 0.0;
   out_5613029472060395452[193] = 0.0;
   out_5613029472060395452[194] = 0.0;
   out_5613029472060395452[195] = 0.0;
   out_5613029472060395452[196] = 0.0;
   out_5613029472060395452[197] = 0.0;
   out_5613029472060395452[198] = 0.0;
   out_5613029472060395452[199] = 0.0;
   out_5613029472060395452[200] = 0.0;
   out_5613029472060395452[201] = 0.0;
   out_5613029472060395452[202] = 0.0;
   out_5613029472060395452[203] = 0.0;
   out_5613029472060395452[204] = 0.0;
   out_5613029472060395452[205] = 0.0;
   out_5613029472060395452[206] = 0.0;
   out_5613029472060395452[207] = 0.0;
   out_5613029472060395452[208] = 0.0;
   out_5613029472060395452[209] = 1.0;
   out_5613029472060395452[210] = 0.0;
   out_5613029472060395452[211] = 0.0;
   out_5613029472060395452[212] = 0.0;
   out_5613029472060395452[213] = 0.0;
   out_5613029472060395452[214] = 0.0;
   out_5613029472060395452[215] = 0.0;
   out_5613029472060395452[216] = 0.0;
   out_5613029472060395452[217] = 0.0;
   out_5613029472060395452[218] = 0.0;
   out_5613029472060395452[219] = 0.0;
   out_5613029472060395452[220] = 0.0;
   out_5613029472060395452[221] = 0.0;
   out_5613029472060395452[222] = 0.0;
   out_5613029472060395452[223] = 0.0;
   out_5613029472060395452[224] = 0.0;
   out_5613029472060395452[225] = 0.0;
   out_5613029472060395452[226] = 0.0;
   out_5613029472060395452[227] = 0.0;
   out_5613029472060395452[228] = 1.0;
   out_5613029472060395452[229] = 0.0;
   out_5613029472060395452[230] = 0.0;
   out_5613029472060395452[231] = 0.0;
   out_5613029472060395452[232] = 0.0;
   out_5613029472060395452[233] = 0.0;
   out_5613029472060395452[234] = 0.0;
   out_5613029472060395452[235] = 0.0;
   out_5613029472060395452[236] = 0.0;
   out_5613029472060395452[237] = 0.0;
   out_5613029472060395452[238] = 0.0;
   out_5613029472060395452[239] = 0.0;
   out_5613029472060395452[240] = 0.0;
   out_5613029472060395452[241] = 0.0;
   out_5613029472060395452[242] = 0.0;
   out_5613029472060395452[243] = 0.0;
   out_5613029472060395452[244] = 0.0;
   out_5613029472060395452[245] = 0.0;
   out_5613029472060395452[246] = 0.0;
   out_5613029472060395452[247] = 1.0;
   out_5613029472060395452[248] = 0.0;
   out_5613029472060395452[249] = 0.0;
   out_5613029472060395452[250] = 0.0;
   out_5613029472060395452[251] = 0.0;
   out_5613029472060395452[252] = 0.0;
   out_5613029472060395452[253] = 0.0;
   out_5613029472060395452[254] = 0.0;
   out_5613029472060395452[255] = 0.0;
   out_5613029472060395452[256] = 0.0;
   out_5613029472060395452[257] = 0.0;
   out_5613029472060395452[258] = 0.0;
   out_5613029472060395452[259] = 0.0;
   out_5613029472060395452[260] = 0.0;
   out_5613029472060395452[261] = 0.0;
   out_5613029472060395452[262] = 0.0;
   out_5613029472060395452[263] = 0.0;
   out_5613029472060395452[264] = 0.0;
   out_5613029472060395452[265] = 0.0;
   out_5613029472060395452[266] = 1.0;
   out_5613029472060395452[267] = 0.0;
   out_5613029472060395452[268] = 0.0;
   out_5613029472060395452[269] = 0.0;
   out_5613029472060395452[270] = 0.0;
   out_5613029472060395452[271] = 0.0;
   out_5613029472060395452[272] = 0.0;
   out_5613029472060395452[273] = 0.0;
   out_5613029472060395452[274] = 0.0;
   out_5613029472060395452[275] = 0.0;
   out_5613029472060395452[276] = 0.0;
   out_5613029472060395452[277] = 0.0;
   out_5613029472060395452[278] = 0.0;
   out_5613029472060395452[279] = 0.0;
   out_5613029472060395452[280] = 0.0;
   out_5613029472060395452[281] = 0.0;
   out_5613029472060395452[282] = 0.0;
   out_5613029472060395452[283] = 0.0;
   out_5613029472060395452[284] = 0.0;
   out_5613029472060395452[285] = 1.0;
   out_5613029472060395452[286] = 0.0;
   out_5613029472060395452[287] = 0.0;
   out_5613029472060395452[288] = 0.0;
   out_5613029472060395452[289] = 0.0;
   out_5613029472060395452[290] = 0.0;
   out_5613029472060395452[291] = 0.0;
   out_5613029472060395452[292] = 0.0;
   out_5613029472060395452[293] = 0.0;
   out_5613029472060395452[294] = 0.0;
   out_5613029472060395452[295] = 0.0;
   out_5613029472060395452[296] = 0.0;
   out_5613029472060395452[297] = 0.0;
   out_5613029472060395452[298] = 0.0;
   out_5613029472060395452[299] = 0.0;
   out_5613029472060395452[300] = 0.0;
   out_5613029472060395452[301] = 0.0;
   out_5613029472060395452[302] = 0.0;
   out_5613029472060395452[303] = 0.0;
   out_5613029472060395452[304] = 1.0;
   out_5613029472060395452[305] = 0.0;
   out_5613029472060395452[306] = 0.0;
   out_5613029472060395452[307] = 0.0;
   out_5613029472060395452[308] = 0.0;
   out_5613029472060395452[309] = 0.0;
   out_5613029472060395452[310] = 0.0;
   out_5613029472060395452[311] = 0.0;
   out_5613029472060395452[312] = 0.0;
   out_5613029472060395452[313] = 0.0;
   out_5613029472060395452[314] = 0.0;
   out_5613029472060395452[315] = 0.0;
   out_5613029472060395452[316] = 0.0;
   out_5613029472060395452[317] = 0.0;
   out_5613029472060395452[318] = 0.0;
   out_5613029472060395452[319] = 0.0;
   out_5613029472060395452[320] = 0.0;
   out_5613029472060395452[321] = 0.0;
   out_5613029472060395452[322] = 0.0;
   out_5613029472060395452[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_3560257805552383557) {
   out_3560257805552383557[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_3560257805552383557[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_3560257805552383557[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_3560257805552383557[3] = dt*state[12] + state[3];
   out_3560257805552383557[4] = dt*state[13] + state[4];
   out_3560257805552383557[5] = dt*state[14] + state[5];
   out_3560257805552383557[6] = state[6];
   out_3560257805552383557[7] = state[7];
   out_3560257805552383557[8] = state[8];
   out_3560257805552383557[9] = state[9];
   out_3560257805552383557[10] = state[10];
   out_3560257805552383557[11] = state[11];
   out_3560257805552383557[12] = state[12];
   out_3560257805552383557[13] = state[13];
   out_3560257805552383557[14] = state[14];
   out_3560257805552383557[15] = state[15];
   out_3560257805552383557[16] = state[16];
   out_3560257805552383557[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8405700866591566947) {
   out_8405700866591566947[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8405700866591566947[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8405700866591566947[2] = 0;
   out_8405700866591566947[3] = 0;
   out_8405700866591566947[4] = 0;
   out_8405700866591566947[5] = 0;
   out_8405700866591566947[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8405700866591566947[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8405700866591566947[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8405700866591566947[9] = 0;
   out_8405700866591566947[10] = 0;
   out_8405700866591566947[11] = 0;
   out_8405700866591566947[12] = 0;
   out_8405700866591566947[13] = 0;
   out_8405700866591566947[14] = 0;
   out_8405700866591566947[15] = 0;
   out_8405700866591566947[16] = 0;
   out_8405700866591566947[17] = 0;
   out_8405700866591566947[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8405700866591566947[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8405700866591566947[20] = 0;
   out_8405700866591566947[21] = 0;
   out_8405700866591566947[22] = 0;
   out_8405700866591566947[23] = 0;
   out_8405700866591566947[24] = 0;
   out_8405700866591566947[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8405700866591566947[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8405700866591566947[27] = 0;
   out_8405700866591566947[28] = 0;
   out_8405700866591566947[29] = 0;
   out_8405700866591566947[30] = 0;
   out_8405700866591566947[31] = 0;
   out_8405700866591566947[32] = 0;
   out_8405700866591566947[33] = 0;
   out_8405700866591566947[34] = 0;
   out_8405700866591566947[35] = 0;
   out_8405700866591566947[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8405700866591566947[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8405700866591566947[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8405700866591566947[39] = 0;
   out_8405700866591566947[40] = 0;
   out_8405700866591566947[41] = 0;
   out_8405700866591566947[42] = 0;
   out_8405700866591566947[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8405700866591566947[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8405700866591566947[45] = 0;
   out_8405700866591566947[46] = 0;
   out_8405700866591566947[47] = 0;
   out_8405700866591566947[48] = 0;
   out_8405700866591566947[49] = 0;
   out_8405700866591566947[50] = 0;
   out_8405700866591566947[51] = 0;
   out_8405700866591566947[52] = 0;
   out_8405700866591566947[53] = 0;
   out_8405700866591566947[54] = 0;
   out_8405700866591566947[55] = 0;
   out_8405700866591566947[56] = 0;
   out_8405700866591566947[57] = 1;
   out_8405700866591566947[58] = 0;
   out_8405700866591566947[59] = 0;
   out_8405700866591566947[60] = 0;
   out_8405700866591566947[61] = 0;
   out_8405700866591566947[62] = 0;
   out_8405700866591566947[63] = 0;
   out_8405700866591566947[64] = 0;
   out_8405700866591566947[65] = 0;
   out_8405700866591566947[66] = dt;
   out_8405700866591566947[67] = 0;
   out_8405700866591566947[68] = 0;
   out_8405700866591566947[69] = 0;
   out_8405700866591566947[70] = 0;
   out_8405700866591566947[71] = 0;
   out_8405700866591566947[72] = 0;
   out_8405700866591566947[73] = 0;
   out_8405700866591566947[74] = 0;
   out_8405700866591566947[75] = 0;
   out_8405700866591566947[76] = 1;
   out_8405700866591566947[77] = 0;
   out_8405700866591566947[78] = 0;
   out_8405700866591566947[79] = 0;
   out_8405700866591566947[80] = 0;
   out_8405700866591566947[81] = 0;
   out_8405700866591566947[82] = 0;
   out_8405700866591566947[83] = 0;
   out_8405700866591566947[84] = 0;
   out_8405700866591566947[85] = dt;
   out_8405700866591566947[86] = 0;
   out_8405700866591566947[87] = 0;
   out_8405700866591566947[88] = 0;
   out_8405700866591566947[89] = 0;
   out_8405700866591566947[90] = 0;
   out_8405700866591566947[91] = 0;
   out_8405700866591566947[92] = 0;
   out_8405700866591566947[93] = 0;
   out_8405700866591566947[94] = 0;
   out_8405700866591566947[95] = 1;
   out_8405700866591566947[96] = 0;
   out_8405700866591566947[97] = 0;
   out_8405700866591566947[98] = 0;
   out_8405700866591566947[99] = 0;
   out_8405700866591566947[100] = 0;
   out_8405700866591566947[101] = 0;
   out_8405700866591566947[102] = 0;
   out_8405700866591566947[103] = 0;
   out_8405700866591566947[104] = dt;
   out_8405700866591566947[105] = 0;
   out_8405700866591566947[106] = 0;
   out_8405700866591566947[107] = 0;
   out_8405700866591566947[108] = 0;
   out_8405700866591566947[109] = 0;
   out_8405700866591566947[110] = 0;
   out_8405700866591566947[111] = 0;
   out_8405700866591566947[112] = 0;
   out_8405700866591566947[113] = 0;
   out_8405700866591566947[114] = 1;
   out_8405700866591566947[115] = 0;
   out_8405700866591566947[116] = 0;
   out_8405700866591566947[117] = 0;
   out_8405700866591566947[118] = 0;
   out_8405700866591566947[119] = 0;
   out_8405700866591566947[120] = 0;
   out_8405700866591566947[121] = 0;
   out_8405700866591566947[122] = 0;
   out_8405700866591566947[123] = 0;
   out_8405700866591566947[124] = 0;
   out_8405700866591566947[125] = 0;
   out_8405700866591566947[126] = 0;
   out_8405700866591566947[127] = 0;
   out_8405700866591566947[128] = 0;
   out_8405700866591566947[129] = 0;
   out_8405700866591566947[130] = 0;
   out_8405700866591566947[131] = 0;
   out_8405700866591566947[132] = 0;
   out_8405700866591566947[133] = 1;
   out_8405700866591566947[134] = 0;
   out_8405700866591566947[135] = 0;
   out_8405700866591566947[136] = 0;
   out_8405700866591566947[137] = 0;
   out_8405700866591566947[138] = 0;
   out_8405700866591566947[139] = 0;
   out_8405700866591566947[140] = 0;
   out_8405700866591566947[141] = 0;
   out_8405700866591566947[142] = 0;
   out_8405700866591566947[143] = 0;
   out_8405700866591566947[144] = 0;
   out_8405700866591566947[145] = 0;
   out_8405700866591566947[146] = 0;
   out_8405700866591566947[147] = 0;
   out_8405700866591566947[148] = 0;
   out_8405700866591566947[149] = 0;
   out_8405700866591566947[150] = 0;
   out_8405700866591566947[151] = 0;
   out_8405700866591566947[152] = 1;
   out_8405700866591566947[153] = 0;
   out_8405700866591566947[154] = 0;
   out_8405700866591566947[155] = 0;
   out_8405700866591566947[156] = 0;
   out_8405700866591566947[157] = 0;
   out_8405700866591566947[158] = 0;
   out_8405700866591566947[159] = 0;
   out_8405700866591566947[160] = 0;
   out_8405700866591566947[161] = 0;
   out_8405700866591566947[162] = 0;
   out_8405700866591566947[163] = 0;
   out_8405700866591566947[164] = 0;
   out_8405700866591566947[165] = 0;
   out_8405700866591566947[166] = 0;
   out_8405700866591566947[167] = 0;
   out_8405700866591566947[168] = 0;
   out_8405700866591566947[169] = 0;
   out_8405700866591566947[170] = 0;
   out_8405700866591566947[171] = 1;
   out_8405700866591566947[172] = 0;
   out_8405700866591566947[173] = 0;
   out_8405700866591566947[174] = 0;
   out_8405700866591566947[175] = 0;
   out_8405700866591566947[176] = 0;
   out_8405700866591566947[177] = 0;
   out_8405700866591566947[178] = 0;
   out_8405700866591566947[179] = 0;
   out_8405700866591566947[180] = 0;
   out_8405700866591566947[181] = 0;
   out_8405700866591566947[182] = 0;
   out_8405700866591566947[183] = 0;
   out_8405700866591566947[184] = 0;
   out_8405700866591566947[185] = 0;
   out_8405700866591566947[186] = 0;
   out_8405700866591566947[187] = 0;
   out_8405700866591566947[188] = 0;
   out_8405700866591566947[189] = 0;
   out_8405700866591566947[190] = 1;
   out_8405700866591566947[191] = 0;
   out_8405700866591566947[192] = 0;
   out_8405700866591566947[193] = 0;
   out_8405700866591566947[194] = 0;
   out_8405700866591566947[195] = 0;
   out_8405700866591566947[196] = 0;
   out_8405700866591566947[197] = 0;
   out_8405700866591566947[198] = 0;
   out_8405700866591566947[199] = 0;
   out_8405700866591566947[200] = 0;
   out_8405700866591566947[201] = 0;
   out_8405700866591566947[202] = 0;
   out_8405700866591566947[203] = 0;
   out_8405700866591566947[204] = 0;
   out_8405700866591566947[205] = 0;
   out_8405700866591566947[206] = 0;
   out_8405700866591566947[207] = 0;
   out_8405700866591566947[208] = 0;
   out_8405700866591566947[209] = 1;
   out_8405700866591566947[210] = 0;
   out_8405700866591566947[211] = 0;
   out_8405700866591566947[212] = 0;
   out_8405700866591566947[213] = 0;
   out_8405700866591566947[214] = 0;
   out_8405700866591566947[215] = 0;
   out_8405700866591566947[216] = 0;
   out_8405700866591566947[217] = 0;
   out_8405700866591566947[218] = 0;
   out_8405700866591566947[219] = 0;
   out_8405700866591566947[220] = 0;
   out_8405700866591566947[221] = 0;
   out_8405700866591566947[222] = 0;
   out_8405700866591566947[223] = 0;
   out_8405700866591566947[224] = 0;
   out_8405700866591566947[225] = 0;
   out_8405700866591566947[226] = 0;
   out_8405700866591566947[227] = 0;
   out_8405700866591566947[228] = 1;
   out_8405700866591566947[229] = 0;
   out_8405700866591566947[230] = 0;
   out_8405700866591566947[231] = 0;
   out_8405700866591566947[232] = 0;
   out_8405700866591566947[233] = 0;
   out_8405700866591566947[234] = 0;
   out_8405700866591566947[235] = 0;
   out_8405700866591566947[236] = 0;
   out_8405700866591566947[237] = 0;
   out_8405700866591566947[238] = 0;
   out_8405700866591566947[239] = 0;
   out_8405700866591566947[240] = 0;
   out_8405700866591566947[241] = 0;
   out_8405700866591566947[242] = 0;
   out_8405700866591566947[243] = 0;
   out_8405700866591566947[244] = 0;
   out_8405700866591566947[245] = 0;
   out_8405700866591566947[246] = 0;
   out_8405700866591566947[247] = 1;
   out_8405700866591566947[248] = 0;
   out_8405700866591566947[249] = 0;
   out_8405700866591566947[250] = 0;
   out_8405700866591566947[251] = 0;
   out_8405700866591566947[252] = 0;
   out_8405700866591566947[253] = 0;
   out_8405700866591566947[254] = 0;
   out_8405700866591566947[255] = 0;
   out_8405700866591566947[256] = 0;
   out_8405700866591566947[257] = 0;
   out_8405700866591566947[258] = 0;
   out_8405700866591566947[259] = 0;
   out_8405700866591566947[260] = 0;
   out_8405700866591566947[261] = 0;
   out_8405700866591566947[262] = 0;
   out_8405700866591566947[263] = 0;
   out_8405700866591566947[264] = 0;
   out_8405700866591566947[265] = 0;
   out_8405700866591566947[266] = 1;
   out_8405700866591566947[267] = 0;
   out_8405700866591566947[268] = 0;
   out_8405700866591566947[269] = 0;
   out_8405700866591566947[270] = 0;
   out_8405700866591566947[271] = 0;
   out_8405700866591566947[272] = 0;
   out_8405700866591566947[273] = 0;
   out_8405700866591566947[274] = 0;
   out_8405700866591566947[275] = 0;
   out_8405700866591566947[276] = 0;
   out_8405700866591566947[277] = 0;
   out_8405700866591566947[278] = 0;
   out_8405700866591566947[279] = 0;
   out_8405700866591566947[280] = 0;
   out_8405700866591566947[281] = 0;
   out_8405700866591566947[282] = 0;
   out_8405700866591566947[283] = 0;
   out_8405700866591566947[284] = 0;
   out_8405700866591566947[285] = 1;
   out_8405700866591566947[286] = 0;
   out_8405700866591566947[287] = 0;
   out_8405700866591566947[288] = 0;
   out_8405700866591566947[289] = 0;
   out_8405700866591566947[290] = 0;
   out_8405700866591566947[291] = 0;
   out_8405700866591566947[292] = 0;
   out_8405700866591566947[293] = 0;
   out_8405700866591566947[294] = 0;
   out_8405700866591566947[295] = 0;
   out_8405700866591566947[296] = 0;
   out_8405700866591566947[297] = 0;
   out_8405700866591566947[298] = 0;
   out_8405700866591566947[299] = 0;
   out_8405700866591566947[300] = 0;
   out_8405700866591566947[301] = 0;
   out_8405700866591566947[302] = 0;
   out_8405700866591566947[303] = 0;
   out_8405700866591566947[304] = 1;
   out_8405700866591566947[305] = 0;
   out_8405700866591566947[306] = 0;
   out_8405700866591566947[307] = 0;
   out_8405700866591566947[308] = 0;
   out_8405700866591566947[309] = 0;
   out_8405700866591566947[310] = 0;
   out_8405700866591566947[311] = 0;
   out_8405700866591566947[312] = 0;
   out_8405700866591566947[313] = 0;
   out_8405700866591566947[314] = 0;
   out_8405700866591566947[315] = 0;
   out_8405700866591566947[316] = 0;
   out_8405700866591566947[317] = 0;
   out_8405700866591566947[318] = 0;
   out_8405700866591566947[319] = 0;
   out_8405700866591566947[320] = 0;
   out_8405700866591566947[321] = 0;
   out_8405700866591566947[322] = 0;
   out_8405700866591566947[323] = 1;
}
void h_4(double *state, double *unused, double *out_6714333113820678959) {
   out_6714333113820678959[0] = state[6] + state[9];
   out_6714333113820678959[1] = state[7] + state[10];
   out_6714333113820678959[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6985632794897197443) {
   out_6985632794897197443[0] = 0;
   out_6985632794897197443[1] = 0;
   out_6985632794897197443[2] = 0;
   out_6985632794897197443[3] = 0;
   out_6985632794897197443[4] = 0;
   out_6985632794897197443[5] = 0;
   out_6985632794897197443[6] = 1;
   out_6985632794897197443[7] = 0;
   out_6985632794897197443[8] = 0;
   out_6985632794897197443[9] = 1;
   out_6985632794897197443[10] = 0;
   out_6985632794897197443[11] = 0;
   out_6985632794897197443[12] = 0;
   out_6985632794897197443[13] = 0;
   out_6985632794897197443[14] = 0;
   out_6985632794897197443[15] = 0;
   out_6985632794897197443[16] = 0;
   out_6985632794897197443[17] = 0;
   out_6985632794897197443[18] = 0;
   out_6985632794897197443[19] = 0;
   out_6985632794897197443[20] = 0;
   out_6985632794897197443[21] = 0;
   out_6985632794897197443[22] = 0;
   out_6985632794897197443[23] = 0;
   out_6985632794897197443[24] = 0;
   out_6985632794897197443[25] = 1;
   out_6985632794897197443[26] = 0;
   out_6985632794897197443[27] = 0;
   out_6985632794897197443[28] = 1;
   out_6985632794897197443[29] = 0;
   out_6985632794897197443[30] = 0;
   out_6985632794897197443[31] = 0;
   out_6985632794897197443[32] = 0;
   out_6985632794897197443[33] = 0;
   out_6985632794897197443[34] = 0;
   out_6985632794897197443[35] = 0;
   out_6985632794897197443[36] = 0;
   out_6985632794897197443[37] = 0;
   out_6985632794897197443[38] = 0;
   out_6985632794897197443[39] = 0;
   out_6985632794897197443[40] = 0;
   out_6985632794897197443[41] = 0;
   out_6985632794897197443[42] = 0;
   out_6985632794897197443[43] = 0;
   out_6985632794897197443[44] = 1;
   out_6985632794897197443[45] = 0;
   out_6985632794897197443[46] = 0;
   out_6985632794897197443[47] = 1;
   out_6985632794897197443[48] = 0;
   out_6985632794897197443[49] = 0;
   out_6985632794897197443[50] = 0;
   out_6985632794897197443[51] = 0;
   out_6985632794897197443[52] = 0;
   out_6985632794897197443[53] = 0;
}
void h_10(double *state, double *unused, double *out_1436740119579277140) {
   out_1436740119579277140[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1436740119579277140[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1436740119579277140[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1336760473497929829) {
   out_1336760473497929829[0] = 0;
   out_1336760473497929829[1] = 9.8100000000000005*cos(state[1]);
   out_1336760473497929829[2] = 0;
   out_1336760473497929829[3] = 0;
   out_1336760473497929829[4] = -state[8];
   out_1336760473497929829[5] = state[7];
   out_1336760473497929829[6] = 0;
   out_1336760473497929829[7] = state[5];
   out_1336760473497929829[8] = -state[4];
   out_1336760473497929829[9] = 0;
   out_1336760473497929829[10] = 0;
   out_1336760473497929829[11] = 0;
   out_1336760473497929829[12] = 1;
   out_1336760473497929829[13] = 0;
   out_1336760473497929829[14] = 0;
   out_1336760473497929829[15] = 1;
   out_1336760473497929829[16] = 0;
   out_1336760473497929829[17] = 0;
   out_1336760473497929829[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1336760473497929829[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1336760473497929829[20] = 0;
   out_1336760473497929829[21] = state[8];
   out_1336760473497929829[22] = 0;
   out_1336760473497929829[23] = -state[6];
   out_1336760473497929829[24] = -state[5];
   out_1336760473497929829[25] = 0;
   out_1336760473497929829[26] = state[3];
   out_1336760473497929829[27] = 0;
   out_1336760473497929829[28] = 0;
   out_1336760473497929829[29] = 0;
   out_1336760473497929829[30] = 0;
   out_1336760473497929829[31] = 1;
   out_1336760473497929829[32] = 0;
   out_1336760473497929829[33] = 0;
   out_1336760473497929829[34] = 1;
   out_1336760473497929829[35] = 0;
   out_1336760473497929829[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1336760473497929829[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1336760473497929829[38] = 0;
   out_1336760473497929829[39] = -state[7];
   out_1336760473497929829[40] = state[6];
   out_1336760473497929829[41] = 0;
   out_1336760473497929829[42] = state[4];
   out_1336760473497929829[43] = -state[3];
   out_1336760473497929829[44] = 0;
   out_1336760473497929829[45] = 0;
   out_1336760473497929829[46] = 0;
   out_1336760473497929829[47] = 0;
   out_1336760473497929829[48] = 0;
   out_1336760473497929829[49] = 0;
   out_1336760473497929829[50] = 1;
   out_1336760473497929829[51] = 0;
   out_1336760473497929829[52] = 0;
   out_1336760473497929829[53] = 1;
}
void h_13(double *state, double *unused, double *out_8610784800470542827) {
   out_8610784800470542827[0] = state[3];
   out_8610784800470542827[1] = state[4];
   out_8610784800470542827[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8248837453480021372) {
   out_8248837453480021372[0] = 0;
   out_8248837453480021372[1] = 0;
   out_8248837453480021372[2] = 0;
   out_8248837453480021372[3] = 1;
   out_8248837453480021372[4] = 0;
   out_8248837453480021372[5] = 0;
   out_8248837453480021372[6] = 0;
   out_8248837453480021372[7] = 0;
   out_8248837453480021372[8] = 0;
   out_8248837453480021372[9] = 0;
   out_8248837453480021372[10] = 0;
   out_8248837453480021372[11] = 0;
   out_8248837453480021372[12] = 0;
   out_8248837453480021372[13] = 0;
   out_8248837453480021372[14] = 0;
   out_8248837453480021372[15] = 0;
   out_8248837453480021372[16] = 0;
   out_8248837453480021372[17] = 0;
   out_8248837453480021372[18] = 0;
   out_8248837453480021372[19] = 0;
   out_8248837453480021372[20] = 0;
   out_8248837453480021372[21] = 0;
   out_8248837453480021372[22] = 1;
   out_8248837453480021372[23] = 0;
   out_8248837453480021372[24] = 0;
   out_8248837453480021372[25] = 0;
   out_8248837453480021372[26] = 0;
   out_8248837453480021372[27] = 0;
   out_8248837453480021372[28] = 0;
   out_8248837453480021372[29] = 0;
   out_8248837453480021372[30] = 0;
   out_8248837453480021372[31] = 0;
   out_8248837453480021372[32] = 0;
   out_8248837453480021372[33] = 0;
   out_8248837453480021372[34] = 0;
   out_8248837453480021372[35] = 0;
   out_8248837453480021372[36] = 0;
   out_8248837453480021372[37] = 0;
   out_8248837453480021372[38] = 0;
   out_8248837453480021372[39] = 0;
   out_8248837453480021372[40] = 0;
   out_8248837453480021372[41] = 1;
   out_8248837453480021372[42] = 0;
   out_8248837453480021372[43] = 0;
   out_8248837453480021372[44] = 0;
   out_8248837453480021372[45] = 0;
   out_8248837453480021372[46] = 0;
   out_8248837453480021372[47] = 0;
   out_8248837453480021372[48] = 0;
   out_8248837453480021372[49] = 0;
   out_8248837453480021372[50] = 0;
   out_8248837453480021372[51] = 0;
   out_8248837453480021372[52] = 0;
   out_8248837453480021372[53] = 0;
}
void h_14(double *state, double *unused, double *out_7905030664698657319) {
   out_7905030664698657319[0] = state[6];
   out_7905030664698657319[1] = state[7];
   out_7905030664698657319[2] = state[8];
}
void H_14(double *state, double *unused, double *out_6550516268252313844) {
   out_6550516268252313844[0] = 0;
   out_6550516268252313844[1] = 0;
   out_6550516268252313844[2] = 0;
   out_6550516268252313844[3] = 0;
   out_6550516268252313844[4] = 0;
   out_6550516268252313844[5] = 0;
   out_6550516268252313844[6] = 1;
   out_6550516268252313844[7] = 0;
   out_6550516268252313844[8] = 0;
   out_6550516268252313844[9] = 0;
   out_6550516268252313844[10] = 0;
   out_6550516268252313844[11] = 0;
   out_6550516268252313844[12] = 0;
   out_6550516268252313844[13] = 0;
   out_6550516268252313844[14] = 0;
   out_6550516268252313844[15] = 0;
   out_6550516268252313844[16] = 0;
   out_6550516268252313844[17] = 0;
   out_6550516268252313844[18] = 0;
   out_6550516268252313844[19] = 0;
   out_6550516268252313844[20] = 0;
   out_6550516268252313844[21] = 0;
   out_6550516268252313844[22] = 0;
   out_6550516268252313844[23] = 0;
   out_6550516268252313844[24] = 0;
   out_6550516268252313844[25] = 1;
   out_6550516268252313844[26] = 0;
   out_6550516268252313844[27] = 0;
   out_6550516268252313844[28] = 0;
   out_6550516268252313844[29] = 0;
   out_6550516268252313844[30] = 0;
   out_6550516268252313844[31] = 0;
   out_6550516268252313844[32] = 0;
   out_6550516268252313844[33] = 0;
   out_6550516268252313844[34] = 0;
   out_6550516268252313844[35] = 0;
   out_6550516268252313844[36] = 0;
   out_6550516268252313844[37] = 0;
   out_6550516268252313844[38] = 0;
   out_6550516268252313844[39] = 0;
   out_6550516268252313844[40] = 0;
   out_6550516268252313844[41] = 0;
   out_6550516268252313844[42] = 0;
   out_6550516268252313844[43] = 0;
   out_6550516268252313844[44] = 1;
   out_6550516268252313844[45] = 0;
   out_6550516268252313844[46] = 0;
   out_6550516268252313844[47] = 0;
   out_6550516268252313844[48] = 0;
   out_6550516268252313844[49] = 0;
   out_6550516268252313844[50] = 0;
   out_6550516268252313844[51] = 0;
   out_6550516268252313844[52] = 0;
   out_6550516268252313844[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7704133318394013706) {
  err_fun(nom_x, delta_x, out_7704133318394013706);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5732870200970735889) {
  inv_err_fun(nom_x, true_x, out_5732870200970735889);
}
void pose_H_mod_fun(double *state, double *out_5613029472060395452) {
  H_mod_fun(state, out_5613029472060395452);
}
void pose_f_fun(double *state, double dt, double *out_3560257805552383557) {
  f_fun(state,  dt, out_3560257805552383557);
}
void pose_F_fun(double *state, double dt, double *out_8405700866591566947) {
  F_fun(state,  dt, out_8405700866591566947);
}
void pose_h_4(double *state, double *unused, double *out_6714333113820678959) {
  h_4(state, unused, out_6714333113820678959);
}
void pose_H_4(double *state, double *unused, double *out_6985632794897197443) {
  H_4(state, unused, out_6985632794897197443);
}
void pose_h_10(double *state, double *unused, double *out_1436740119579277140) {
  h_10(state, unused, out_1436740119579277140);
}
void pose_H_10(double *state, double *unused, double *out_1336760473497929829) {
  H_10(state, unused, out_1336760473497929829);
}
void pose_h_13(double *state, double *unused, double *out_8610784800470542827) {
  h_13(state, unused, out_8610784800470542827);
}
void pose_H_13(double *state, double *unused, double *out_8248837453480021372) {
  H_13(state, unused, out_8248837453480021372);
}
void pose_h_14(double *state, double *unused, double *out_7905030664698657319) {
  h_14(state, unused, out_7905030664698657319);
}
void pose_H_14(double *state, double *unused, double *out_6550516268252313844) {
  H_14(state, unused, out_6550516268252313844);
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
