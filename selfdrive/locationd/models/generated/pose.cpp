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
void err_fun(double *nom_x, double *delta_x, double *out_8230036097863094971) {
   out_8230036097863094971[0] = delta_x[0] + nom_x[0];
   out_8230036097863094971[1] = delta_x[1] + nom_x[1];
   out_8230036097863094971[2] = delta_x[2] + nom_x[2];
   out_8230036097863094971[3] = delta_x[3] + nom_x[3];
   out_8230036097863094971[4] = delta_x[4] + nom_x[4];
   out_8230036097863094971[5] = delta_x[5] + nom_x[5];
   out_8230036097863094971[6] = delta_x[6] + nom_x[6];
   out_8230036097863094971[7] = delta_x[7] + nom_x[7];
   out_8230036097863094971[8] = delta_x[8] + nom_x[8];
   out_8230036097863094971[9] = delta_x[9] + nom_x[9];
   out_8230036097863094971[10] = delta_x[10] + nom_x[10];
   out_8230036097863094971[11] = delta_x[11] + nom_x[11];
   out_8230036097863094971[12] = delta_x[12] + nom_x[12];
   out_8230036097863094971[13] = delta_x[13] + nom_x[13];
   out_8230036097863094971[14] = delta_x[14] + nom_x[14];
   out_8230036097863094971[15] = delta_x[15] + nom_x[15];
   out_8230036097863094971[16] = delta_x[16] + nom_x[16];
   out_8230036097863094971[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8741051770711475830) {
   out_8741051770711475830[0] = -nom_x[0] + true_x[0];
   out_8741051770711475830[1] = -nom_x[1] + true_x[1];
   out_8741051770711475830[2] = -nom_x[2] + true_x[2];
   out_8741051770711475830[3] = -nom_x[3] + true_x[3];
   out_8741051770711475830[4] = -nom_x[4] + true_x[4];
   out_8741051770711475830[5] = -nom_x[5] + true_x[5];
   out_8741051770711475830[6] = -nom_x[6] + true_x[6];
   out_8741051770711475830[7] = -nom_x[7] + true_x[7];
   out_8741051770711475830[8] = -nom_x[8] + true_x[8];
   out_8741051770711475830[9] = -nom_x[9] + true_x[9];
   out_8741051770711475830[10] = -nom_x[10] + true_x[10];
   out_8741051770711475830[11] = -nom_x[11] + true_x[11];
   out_8741051770711475830[12] = -nom_x[12] + true_x[12];
   out_8741051770711475830[13] = -nom_x[13] + true_x[13];
   out_8741051770711475830[14] = -nom_x[14] + true_x[14];
   out_8741051770711475830[15] = -nom_x[15] + true_x[15];
   out_8741051770711475830[16] = -nom_x[16] + true_x[16];
   out_8741051770711475830[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_1900632188772248703) {
   out_1900632188772248703[0] = 1.0;
   out_1900632188772248703[1] = 0.0;
   out_1900632188772248703[2] = 0.0;
   out_1900632188772248703[3] = 0.0;
   out_1900632188772248703[4] = 0.0;
   out_1900632188772248703[5] = 0.0;
   out_1900632188772248703[6] = 0.0;
   out_1900632188772248703[7] = 0.0;
   out_1900632188772248703[8] = 0.0;
   out_1900632188772248703[9] = 0.0;
   out_1900632188772248703[10] = 0.0;
   out_1900632188772248703[11] = 0.0;
   out_1900632188772248703[12] = 0.0;
   out_1900632188772248703[13] = 0.0;
   out_1900632188772248703[14] = 0.0;
   out_1900632188772248703[15] = 0.0;
   out_1900632188772248703[16] = 0.0;
   out_1900632188772248703[17] = 0.0;
   out_1900632188772248703[18] = 0.0;
   out_1900632188772248703[19] = 1.0;
   out_1900632188772248703[20] = 0.0;
   out_1900632188772248703[21] = 0.0;
   out_1900632188772248703[22] = 0.0;
   out_1900632188772248703[23] = 0.0;
   out_1900632188772248703[24] = 0.0;
   out_1900632188772248703[25] = 0.0;
   out_1900632188772248703[26] = 0.0;
   out_1900632188772248703[27] = 0.0;
   out_1900632188772248703[28] = 0.0;
   out_1900632188772248703[29] = 0.0;
   out_1900632188772248703[30] = 0.0;
   out_1900632188772248703[31] = 0.0;
   out_1900632188772248703[32] = 0.0;
   out_1900632188772248703[33] = 0.0;
   out_1900632188772248703[34] = 0.0;
   out_1900632188772248703[35] = 0.0;
   out_1900632188772248703[36] = 0.0;
   out_1900632188772248703[37] = 0.0;
   out_1900632188772248703[38] = 1.0;
   out_1900632188772248703[39] = 0.0;
   out_1900632188772248703[40] = 0.0;
   out_1900632188772248703[41] = 0.0;
   out_1900632188772248703[42] = 0.0;
   out_1900632188772248703[43] = 0.0;
   out_1900632188772248703[44] = 0.0;
   out_1900632188772248703[45] = 0.0;
   out_1900632188772248703[46] = 0.0;
   out_1900632188772248703[47] = 0.0;
   out_1900632188772248703[48] = 0.0;
   out_1900632188772248703[49] = 0.0;
   out_1900632188772248703[50] = 0.0;
   out_1900632188772248703[51] = 0.0;
   out_1900632188772248703[52] = 0.0;
   out_1900632188772248703[53] = 0.0;
   out_1900632188772248703[54] = 0.0;
   out_1900632188772248703[55] = 0.0;
   out_1900632188772248703[56] = 0.0;
   out_1900632188772248703[57] = 1.0;
   out_1900632188772248703[58] = 0.0;
   out_1900632188772248703[59] = 0.0;
   out_1900632188772248703[60] = 0.0;
   out_1900632188772248703[61] = 0.0;
   out_1900632188772248703[62] = 0.0;
   out_1900632188772248703[63] = 0.0;
   out_1900632188772248703[64] = 0.0;
   out_1900632188772248703[65] = 0.0;
   out_1900632188772248703[66] = 0.0;
   out_1900632188772248703[67] = 0.0;
   out_1900632188772248703[68] = 0.0;
   out_1900632188772248703[69] = 0.0;
   out_1900632188772248703[70] = 0.0;
   out_1900632188772248703[71] = 0.0;
   out_1900632188772248703[72] = 0.0;
   out_1900632188772248703[73] = 0.0;
   out_1900632188772248703[74] = 0.0;
   out_1900632188772248703[75] = 0.0;
   out_1900632188772248703[76] = 1.0;
   out_1900632188772248703[77] = 0.0;
   out_1900632188772248703[78] = 0.0;
   out_1900632188772248703[79] = 0.0;
   out_1900632188772248703[80] = 0.0;
   out_1900632188772248703[81] = 0.0;
   out_1900632188772248703[82] = 0.0;
   out_1900632188772248703[83] = 0.0;
   out_1900632188772248703[84] = 0.0;
   out_1900632188772248703[85] = 0.0;
   out_1900632188772248703[86] = 0.0;
   out_1900632188772248703[87] = 0.0;
   out_1900632188772248703[88] = 0.0;
   out_1900632188772248703[89] = 0.0;
   out_1900632188772248703[90] = 0.0;
   out_1900632188772248703[91] = 0.0;
   out_1900632188772248703[92] = 0.0;
   out_1900632188772248703[93] = 0.0;
   out_1900632188772248703[94] = 0.0;
   out_1900632188772248703[95] = 1.0;
   out_1900632188772248703[96] = 0.0;
   out_1900632188772248703[97] = 0.0;
   out_1900632188772248703[98] = 0.0;
   out_1900632188772248703[99] = 0.0;
   out_1900632188772248703[100] = 0.0;
   out_1900632188772248703[101] = 0.0;
   out_1900632188772248703[102] = 0.0;
   out_1900632188772248703[103] = 0.0;
   out_1900632188772248703[104] = 0.0;
   out_1900632188772248703[105] = 0.0;
   out_1900632188772248703[106] = 0.0;
   out_1900632188772248703[107] = 0.0;
   out_1900632188772248703[108] = 0.0;
   out_1900632188772248703[109] = 0.0;
   out_1900632188772248703[110] = 0.0;
   out_1900632188772248703[111] = 0.0;
   out_1900632188772248703[112] = 0.0;
   out_1900632188772248703[113] = 0.0;
   out_1900632188772248703[114] = 1.0;
   out_1900632188772248703[115] = 0.0;
   out_1900632188772248703[116] = 0.0;
   out_1900632188772248703[117] = 0.0;
   out_1900632188772248703[118] = 0.0;
   out_1900632188772248703[119] = 0.0;
   out_1900632188772248703[120] = 0.0;
   out_1900632188772248703[121] = 0.0;
   out_1900632188772248703[122] = 0.0;
   out_1900632188772248703[123] = 0.0;
   out_1900632188772248703[124] = 0.0;
   out_1900632188772248703[125] = 0.0;
   out_1900632188772248703[126] = 0.0;
   out_1900632188772248703[127] = 0.0;
   out_1900632188772248703[128] = 0.0;
   out_1900632188772248703[129] = 0.0;
   out_1900632188772248703[130] = 0.0;
   out_1900632188772248703[131] = 0.0;
   out_1900632188772248703[132] = 0.0;
   out_1900632188772248703[133] = 1.0;
   out_1900632188772248703[134] = 0.0;
   out_1900632188772248703[135] = 0.0;
   out_1900632188772248703[136] = 0.0;
   out_1900632188772248703[137] = 0.0;
   out_1900632188772248703[138] = 0.0;
   out_1900632188772248703[139] = 0.0;
   out_1900632188772248703[140] = 0.0;
   out_1900632188772248703[141] = 0.0;
   out_1900632188772248703[142] = 0.0;
   out_1900632188772248703[143] = 0.0;
   out_1900632188772248703[144] = 0.0;
   out_1900632188772248703[145] = 0.0;
   out_1900632188772248703[146] = 0.0;
   out_1900632188772248703[147] = 0.0;
   out_1900632188772248703[148] = 0.0;
   out_1900632188772248703[149] = 0.0;
   out_1900632188772248703[150] = 0.0;
   out_1900632188772248703[151] = 0.0;
   out_1900632188772248703[152] = 1.0;
   out_1900632188772248703[153] = 0.0;
   out_1900632188772248703[154] = 0.0;
   out_1900632188772248703[155] = 0.0;
   out_1900632188772248703[156] = 0.0;
   out_1900632188772248703[157] = 0.0;
   out_1900632188772248703[158] = 0.0;
   out_1900632188772248703[159] = 0.0;
   out_1900632188772248703[160] = 0.0;
   out_1900632188772248703[161] = 0.0;
   out_1900632188772248703[162] = 0.0;
   out_1900632188772248703[163] = 0.0;
   out_1900632188772248703[164] = 0.0;
   out_1900632188772248703[165] = 0.0;
   out_1900632188772248703[166] = 0.0;
   out_1900632188772248703[167] = 0.0;
   out_1900632188772248703[168] = 0.0;
   out_1900632188772248703[169] = 0.0;
   out_1900632188772248703[170] = 0.0;
   out_1900632188772248703[171] = 1.0;
   out_1900632188772248703[172] = 0.0;
   out_1900632188772248703[173] = 0.0;
   out_1900632188772248703[174] = 0.0;
   out_1900632188772248703[175] = 0.0;
   out_1900632188772248703[176] = 0.0;
   out_1900632188772248703[177] = 0.0;
   out_1900632188772248703[178] = 0.0;
   out_1900632188772248703[179] = 0.0;
   out_1900632188772248703[180] = 0.0;
   out_1900632188772248703[181] = 0.0;
   out_1900632188772248703[182] = 0.0;
   out_1900632188772248703[183] = 0.0;
   out_1900632188772248703[184] = 0.0;
   out_1900632188772248703[185] = 0.0;
   out_1900632188772248703[186] = 0.0;
   out_1900632188772248703[187] = 0.0;
   out_1900632188772248703[188] = 0.0;
   out_1900632188772248703[189] = 0.0;
   out_1900632188772248703[190] = 1.0;
   out_1900632188772248703[191] = 0.0;
   out_1900632188772248703[192] = 0.0;
   out_1900632188772248703[193] = 0.0;
   out_1900632188772248703[194] = 0.0;
   out_1900632188772248703[195] = 0.0;
   out_1900632188772248703[196] = 0.0;
   out_1900632188772248703[197] = 0.0;
   out_1900632188772248703[198] = 0.0;
   out_1900632188772248703[199] = 0.0;
   out_1900632188772248703[200] = 0.0;
   out_1900632188772248703[201] = 0.0;
   out_1900632188772248703[202] = 0.0;
   out_1900632188772248703[203] = 0.0;
   out_1900632188772248703[204] = 0.0;
   out_1900632188772248703[205] = 0.0;
   out_1900632188772248703[206] = 0.0;
   out_1900632188772248703[207] = 0.0;
   out_1900632188772248703[208] = 0.0;
   out_1900632188772248703[209] = 1.0;
   out_1900632188772248703[210] = 0.0;
   out_1900632188772248703[211] = 0.0;
   out_1900632188772248703[212] = 0.0;
   out_1900632188772248703[213] = 0.0;
   out_1900632188772248703[214] = 0.0;
   out_1900632188772248703[215] = 0.0;
   out_1900632188772248703[216] = 0.0;
   out_1900632188772248703[217] = 0.0;
   out_1900632188772248703[218] = 0.0;
   out_1900632188772248703[219] = 0.0;
   out_1900632188772248703[220] = 0.0;
   out_1900632188772248703[221] = 0.0;
   out_1900632188772248703[222] = 0.0;
   out_1900632188772248703[223] = 0.0;
   out_1900632188772248703[224] = 0.0;
   out_1900632188772248703[225] = 0.0;
   out_1900632188772248703[226] = 0.0;
   out_1900632188772248703[227] = 0.0;
   out_1900632188772248703[228] = 1.0;
   out_1900632188772248703[229] = 0.0;
   out_1900632188772248703[230] = 0.0;
   out_1900632188772248703[231] = 0.0;
   out_1900632188772248703[232] = 0.0;
   out_1900632188772248703[233] = 0.0;
   out_1900632188772248703[234] = 0.0;
   out_1900632188772248703[235] = 0.0;
   out_1900632188772248703[236] = 0.0;
   out_1900632188772248703[237] = 0.0;
   out_1900632188772248703[238] = 0.0;
   out_1900632188772248703[239] = 0.0;
   out_1900632188772248703[240] = 0.0;
   out_1900632188772248703[241] = 0.0;
   out_1900632188772248703[242] = 0.0;
   out_1900632188772248703[243] = 0.0;
   out_1900632188772248703[244] = 0.0;
   out_1900632188772248703[245] = 0.0;
   out_1900632188772248703[246] = 0.0;
   out_1900632188772248703[247] = 1.0;
   out_1900632188772248703[248] = 0.0;
   out_1900632188772248703[249] = 0.0;
   out_1900632188772248703[250] = 0.0;
   out_1900632188772248703[251] = 0.0;
   out_1900632188772248703[252] = 0.0;
   out_1900632188772248703[253] = 0.0;
   out_1900632188772248703[254] = 0.0;
   out_1900632188772248703[255] = 0.0;
   out_1900632188772248703[256] = 0.0;
   out_1900632188772248703[257] = 0.0;
   out_1900632188772248703[258] = 0.0;
   out_1900632188772248703[259] = 0.0;
   out_1900632188772248703[260] = 0.0;
   out_1900632188772248703[261] = 0.0;
   out_1900632188772248703[262] = 0.0;
   out_1900632188772248703[263] = 0.0;
   out_1900632188772248703[264] = 0.0;
   out_1900632188772248703[265] = 0.0;
   out_1900632188772248703[266] = 1.0;
   out_1900632188772248703[267] = 0.0;
   out_1900632188772248703[268] = 0.0;
   out_1900632188772248703[269] = 0.0;
   out_1900632188772248703[270] = 0.0;
   out_1900632188772248703[271] = 0.0;
   out_1900632188772248703[272] = 0.0;
   out_1900632188772248703[273] = 0.0;
   out_1900632188772248703[274] = 0.0;
   out_1900632188772248703[275] = 0.0;
   out_1900632188772248703[276] = 0.0;
   out_1900632188772248703[277] = 0.0;
   out_1900632188772248703[278] = 0.0;
   out_1900632188772248703[279] = 0.0;
   out_1900632188772248703[280] = 0.0;
   out_1900632188772248703[281] = 0.0;
   out_1900632188772248703[282] = 0.0;
   out_1900632188772248703[283] = 0.0;
   out_1900632188772248703[284] = 0.0;
   out_1900632188772248703[285] = 1.0;
   out_1900632188772248703[286] = 0.0;
   out_1900632188772248703[287] = 0.0;
   out_1900632188772248703[288] = 0.0;
   out_1900632188772248703[289] = 0.0;
   out_1900632188772248703[290] = 0.0;
   out_1900632188772248703[291] = 0.0;
   out_1900632188772248703[292] = 0.0;
   out_1900632188772248703[293] = 0.0;
   out_1900632188772248703[294] = 0.0;
   out_1900632188772248703[295] = 0.0;
   out_1900632188772248703[296] = 0.0;
   out_1900632188772248703[297] = 0.0;
   out_1900632188772248703[298] = 0.0;
   out_1900632188772248703[299] = 0.0;
   out_1900632188772248703[300] = 0.0;
   out_1900632188772248703[301] = 0.0;
   out_1900632188772248703[302] = 0.0;
   out_1900632188772248703[303] = 0.0;
   out_1900632188772248703[304] = 1.0;
   out_1900632188772248703[305] = 0.0;
   out_1900632188772248703[306] = 0.0;
   out_1900632188772248703[307] = 0.0;
   out_1900632188772248703[308] = 0.0;
   out_1900632188772248703[309] = 0.0;
   out_1900632188772248703[310] = 0.0;
   out_1900632188772248703[311] = 0.0;
   out_1900632188772248703[312] = 0.0;
   out_1900632188772248703[313] = 0.0;
   out_1900632188772248703[314] = 0.0;
   out_1900632188772248703[315] = 0.0;
   out_1900632188772248703[316] = 0.0;
   out_1900632188772248703[317] = 0.0;
   out_1900632188772248703[318] = 0.0;
   out_1900632188772248703[319] = 0.0;
   out_1900632188772248703[320] = 0.0;
   out_1900632188772248703[321] = 0.0;
   out_1900632188772248703[322] = 0.0;
   out_1900632188772248703[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_3077738493587277525) {
   out_3077738493587277525[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_3077738493587277525[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_3077738493587277525[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_3077738493587277525[3] = dt*state[12] + state[3];
   out_3077738493587277525[4] = dt*state[13] + state[4];
   out_3077738493587277525[5] = dt*state[14] + state[5];
   out_3077738493587277525[6] = state[6];
   out_3077738493587277525[7] = state[7];
   out_3077738493587277525[8] = state[8];
   out_3077738493587277525[9] = state[9];
   out_3077738493587277525[10] = state[10];
   out_3077738493587277525[11] = state[11];
   out_3077738493587277525[12] = state[12];
   out_3077738493587277525[13] = state[13];
   out_3077738493587277525[14] = state[14];
   out_3077738493587277525[15] = state[15];
   out_3077738493587277525[16] = state[16];
   out_3077738493587277525[17] = state[17];
}
void F_fun(double *state, double dt, double *out_474426866180563475) {
   out_474426866180563475[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_474426866180563475[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_474426866180563475[2] = 0;
   out_474426866180563475[3] = 0;
   out_474426866180563475[4] = 0;
   out_474426866180563475[5] = 0;
   out_474426866180563475[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_474426866180563475[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_474426866180563475[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_474426866180563475[9] = 0;
   out_474426866180563475[10] = 0;
   out_474426866180563475[11] = 0;
   out_474426866180563475[12] = 0;
   out_474426866180563475[13] = 0;
   out_474426866180563475[14] = 0;
   out_474426866180563475[15] = 0;
   out_474426866180563475[16] = 0;
   out_474426866180563475[17] = 0;
   out_474426866180563475[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_474426866180563475[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_474426866180563475[20] = 0;
   out_474426866180563475[21] = 0;
   out_474426866180563475[22] = 0;
   out_474426866180563475[23] = 0;
   out_474426866180563475[24] = 0;
   out_474426866180563475[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_474426866180563475[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_474426866180563475[27] = 0;
   out_474426866180563475[28] = 0;
   out_474426866180563475[29] = 0;
   out_474426866180563475[30] = 0;
   out_474426866180563475[31] = 0;
   out_474426866180563475[32] = 0;
   out_474426866180563475[33] = 0;
   out_474426866180563475[34] = 0;
   out_474426866180563475[35] = 0;
   out_474426866180563475[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_474426866180563475[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_474426866180563475[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_474426866180563475[39] = 0;
   out_474426866180563475[40] = 0;
   out_474426866180563475[41] = 0;
   out_474426866180563475[42] = 0;
   out_474426866180563475[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_474426866180563475[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_474426866180563475[45] = 0;
   out_474426866180563475[46] = 0;
   out_474426866180563475[47] = 0;
   out_474426866180563475[48] = 0;
   out_474426866180563475[49] = 0;
   out_474426866180563475[50] = 0;
   out_474426866180563475[51] = 0;
   out_474426866180563475[52] = 0;
   out_474426866180563475[53] = 0;
   out_474426866180563475[54] = 0;
   out_474426866180563475[55] = 0;
   out_474426866180563475[56] = 0;
   out_474426866180563475[57] = 1;
   out_474426866180563475[58] = 0;
   out_474426866180563475[59] = 0;
   out_474426866180563475[60] = 0;
   out_474426866180563475[61] = 0;
   out_474426866180563475[62] = 0;
   out_474426866180563475[63] = 0;
   out_474426866180563475[64] = 0;
   out_474426866180563475[65] = 0;
   out_474426866180563475[66] = dt;
   out_474426866180563475[67] = 0;
   out_474426866180563475[68] = 0;
   out_474426866180563475[69] = 0;
   out_474426866180563475[70] = 0;
   out_474426866180563475[71] = 0;
   out_474426866180563475[72] = 0;
   out_474426866180563475[73] = 0;
   out_474426866180563475[74] = 0;
   out_474426866180563475[75] = 0;
   out_474426866180563475[76] = 1;
   out_474426866180563475[77] = 0;
   out_474426866180563475[78] = 0;
   out_474426866180563475[79] = 0;
   out_474426866180563475[80] = 0;
   out_474426866180563475[81] = 0;
   out_474426866180563475[82] = 0;
   out_474426866180563475[83] = 0;
   out_474426866180563475[84] = 0;
   out_474426866180563475[85] = dt;
   out_474426866180563475[86] = 0;
   out_474426866180563475[87] = 0;
   out_474426866180563475[88] = 0;
   out_474426866180563475[89] = 0;
   out_474426866180563475[90] = 0;
   out_474426866180563475[91] = 0;
   out_474426866180563475[92] = 0;
   out_474426866180563475[93] = 0;
   out_474426866180563475[94] = 0;
   out_474426866180563475[95] = 1;
   out_474426866180563475[96] = 0;
   out_474426866180563475[97] = 0;
   out_474426866180563475[98] = 0;
   out_474426866180563475[99] = 0;
   out_474426866180563475[100] = 0;
   out_474426866180563475[101] = 0;
   out_474426866180563475[102] = 0;
   out_474426866180563475[103] = 0;
   out_474426866180563475[104] = dt;
   out_474426866180563475[105] = 0;
   out_474426866180563475[106] = 0;
   out_474426866180563475[107] = 0;
   out_474426866180563475[108] = 0;
   out_474426866180563475[109] = 0;
   out_474426866180563475[110] = 0;
   out_474426866180563475[111] = 0;
   out_474426866180563475[112] = 0;
   out_474426866180563475[113] = 0;
   out_474426866180563475[114] = 1;
   out_474426866180563475[115] = 0;
   out_474426866180563475[116] = 0;
   out_474426866180563475[117] = 0;
   out_474426866180563475[118] = 0;
   out_474426866180563475[119] = 0;
   out_474426866180563475[120] = 0;
   out_474426866180563475[121] = 0;
   out_474426866180563475[122] = 0;
   out_474426866180563475[123] = 0;
   out_474426866180563475[124] = 0;
   out_474426866180563475[125] = 0;
   out_474426866180563475[126] = 0;
   out_474426866180563475[127] = 0;
   out_474426866180563475[128] = 0;
   out_474426866180563475[129] = 0;
   out_474426866180563475[130] = 0;
   out_474426866180563475[131] = 0;
   out_474426866180563475[132] = 0;
   out_474426866180563475[133] = 1;
   out_474426866180563475[134] = 0;
   out_474426866180563475[135] = 0;
   out_474426866180563475[136] = 0;
   out_474426866180563475[137] = 0;
   out_474426866180563475[138] = 0;
   out_474426866180563475[139] = 0;
   out_474426866180563475[140] = 0;
   out_474426866180563475[141] = 0;
   out_474426866180563475[142] = 0;
   out_474426866180563475[143] = 0;
   out_474426866180563475[144] = 0;
   out_474426866180563475[145] = 0;
   out_474426866180563475[146] = 0;
   out_474426866180563475[147] = 0;
   out_474426866180563475[148] = 0;
   out_474426866180563475[149] = 0;
   out_474426866180563475[150] = 0;
   out_474426866180563475[151] = 0;
   out_474426866180563475[152] = 1;
   out_474426866180563475[153] = 0;
   out_474426866180563475[154] = 0;
   out_474426866180563475[155] = 0;
   out_474426866180563475[156] = 0;
   out_474426866180563475[157] = 0;
   out_474426866180563475[158] = 0;
   out_474426866180563475[159] = 0;
   out_474426866180563475[160] = 0;
   out_474426866180563475[161] = 0;
   out_474426866180563475[162] = 0;
   out_474426866180563475[163] = 0;
   out_474426866180563475[164] = 0;
   out_474426866180563475[165] = 0;
   out_474426866180563475[166] = 0;
   out_474426866180563475[167] = 0;
   out_474426866180563475[168] = 0;
   out_474426866180563475[169] = 0;
   out_474426866180563475[170] = 0;
   out_474426866180563475[171] = 1;
   out_474426866180563475[172] = 0;
   out_474426866180563475[173] = 0;
   out_474426866180563475[174] = 0;
   out_474426866180563475[175] = 0;
   out_474426866180563475[176] = 0;
   out_474426866180563475[177] = 0;
   out_474426866180563475[178] = 0;
   out_474426866180563475[179] = 0;
   out_474426866180563475[180] = 0;
   out_474426866180563475[181] = 0;
   out_474426866180563475[182] = 0;
   out_474426866180563475[183] = 0;
   out_474426866180563475[184] = 0;
   out_474426866180563475[185] = 0;
   out_474426866180563475[186] = 0;
   out_474426866180563475[187] = 0;
   out_474426866180563475[188] = 0;
   out_474426866180563475[189] = 0;
   out_474426866180563475[190] = 1;
   out_474426866180563475[191] = 0;
   out_474426866180563475[192] = 0;
   out_474426866180563475[193] = 0;
   out_474426866180563475[194] = 0;
   out_474426866180563475[195] = 0;
   out_474426866180563475[196] = 0;
   out_474426866180563475[197] = 0;
   out_474426866180563475[198] = 0;
   out_474426866180563475[199] = 0;
   out_474426866180563475[200] = 0;
   out_474426866180563475[201] = 0;
   out_474426866180563475[202] = 0;
   out_474426866180563475[203] = 0;
   out_474426866180563475[204] = 0;
   out_474426866180563475[205] = 0;
   out_474426866180563475[206] = 0;
   out_474426866180563475[207] = 0;
   out_474426866180563475[208] = 0;
   out_474426866180563475[209] = 1;
   out_474426866180563475[210] = 0;
   out_474426866180563475[211] = 0;
   out_474426866180563475[212] = 0;
   out_474426866180563475[213] = 0;
   out_474426866180563475[214] = 0;
   out_474426866180563475[215] = 0;
   out_474426866180563475[216] = 0;
   out_474426866180563475[217] = 0;
   out_474426866180563475[218] = 0;
   out_474426866180563475[219] = 0;
   out_474426866180563475[220] = 0;
   out_474426866180563475[221] = 0;
   out_474426866180563475[222] = 0;
   out_474426866180563475[223] = 0;
   out_474426866180563475[224] = 0;
   out_474426866180563475[225] = 0;
   out_474426866180563475[226] = 0;
   out_474426866180563475[227] = 0;
   out_474426866180563475[228] = 1;
   out_474426866180563475[229] = 0;
   out_474426866180563475[230] = 0;
   out_474426866180563475[231] = 0;
   out_474426866180563475[232] = 0;
   out_474426866180563475[233] = 0;
   out_474426866180563475[234] = 0;
   out_474426866180563475[235] = 0;
   out_474426866180563475[236] = 0;
   out_474426866180563475[237] = 0;
   out_474426866180563475[238] = 0;
   out_474426866180563475[239] = 0;
   out_474426866180563475[240] = 0;
   out_474426866180563475[241] = 0;
   out_474426866180563475[242] = 0;
   out_474426866180563475[243] = 0;
   out_474426866180563475[244] = 0;
   out_474426866180563475[245] = 0;
   out_474426866180563475[246] = 0;
   out_474426866180563475[247] = 1;
   out_474426866180563475[248] = 0;
   out_474426866180563475[249] = 0;
   out_474426866180563475[250] = 0;
   out_474426866180563475[251] = 0;
   out_474426866180563475[252] = 0;
   out_474426866180563475[253] = 0;
   out_474426866180563475[254] = 0;
   out_474426866180563475[255] = 0;
   out_474426866180563475[256] = 0;
   out_474426866180563475[257] = 0;
   out_474426866180563475[258] = 0;
   out_474426866180563475[259] = 0;
   out_474426866180563475[260] = 0;
   out_474426866180563475[261] = 0;
   out_474426866180563475[262] = 0;
   out_474426866180563475[263] = 0;
   out_474426866180563475[264] = 0;
   out_474426866180563475[265] = 0;
   out_474426866180563475[266] = 1;
   out_474426866180563475[267] = 0;
   out_474426866180563475[268] = 0;
   out_474426866180563475[269] = 0;
   out_474426866180563475[270] = 0;
   out_474426866180563475[271] = 0;
   out_474426866180563475[272] = 0;
   out_474426866180563475[273] = 0;
   out_474426866180563475[274] = 0;
   out_474426866180563475[275] = 0;
   out_474426866180563475[276] = 0;
   out_474426866180563475[277] = 0;
   out_474426866180563475[278] = 0;
   out_474426866180563475[279] = 0;
   out_474426866180563475[280] = 0;
   out_474426866180563475[281] = 0;
   out_474426866180563475[282] = 0;
   out_474426866180563475[283] = 0;
   out_474426866180563475[284] = 0;
   out_474426866180563475[285] = 1;
   out_474426866180563475[286] = 0;
   out_474426866180563475[287] = 0;
   out_474426866180563475[288] = 0;
   out_474426866180563475[289] = 0;
   out_474426866180563475[290] = 0;
   out_474426866180563475[291] = 0;
   out_474426866180563475[292] = 0;
   out_474426866180563475[293] = 0;
   out_474426866180563475[294] = 0;
   out_474426866180563475[295] = 0;
   out_474426866180563475[296] = 0;
   out_474426866180563475[297] = 0;
   out_474426866180563475[298] = 0;
   out_474426866180563475[299] = 0;
   out_474426866180563475[300] = 0;
   out_474426866180563475[301] = 0;
   out_474426866180563475[302] = 0;
   out_474426866180563475[303] = 0;
   out_474426866180563475[304] = 1;
   out_474426866180563475[305] = 0;
   out_474426866180563475[306] = 0;
   out_474426866180563475[307] = 0;
   out_474426866180563475[308] = 0;
   out_474426866180563475[309] = 0;
   out_474426866180563475[310] = 0;
   out_474426866180563475[311] = 0;
   out_474426866180563475[312] = 0;
   out_474426866180563475[313] = 0;
   out_474426866180563475[314] = 0;
   out_474426866180563475[315] = 0;
   out_474426866180563475[316] = 0;
   out_474426866180563475[317] = 0;
   out_474426866180563475[318] = 0;
   out_474426866180563475[319] = 0;
   out_474426866180563475[320] = 0;
   out_474426866180563475[321] = 0;
   out_474426866180563475[322] = 0;
   out_474426866180563475[323] = 1;
}
void h_4(double *state, double *unused, double *out_616527671886839495) {
   out_616527671886839495[0] = state[6] + state[9];
   out_616527671886839495[1] = state[7] + state[10];
   out_616527671886839495[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_702684706889350599) {
   out_702684706889350599[0] = 0;
   out_702684706889350599[1] = 0;
   out_702684706889350599[2] = 0;
   out_702684706889350599[3] = 0;
   out_702684706889350599[4] = 0;
   out_702684706889350599[5] = 0;
   out_702684706889350599[6] = 1;
   out_702684706889350599[7] = 0;
   out_702684706889350599[8] = 0;
   out_702684706889350599[9] = 1;
   out_702684706889350599[10] = 0;
   out_702684706889350599[11] = 0;
   out_702684706889350599[12] = 0;
   out_702684706889350599[13] = 0;
   out_702684706889350599[14] = 0;
   out_702684706889350599[15] = 0;
   out_702684706889350599[16] = 0;
   out_702684706889350599[17] = 0;
   out_702684706889350599[18] = 0;
   out_702684706889350599[19] = 0;
   out_702684706889350599[20] = 0;
   out_702684706889350599[21] = 0;
   out_702684706889350599[22] = 0;
   out_702684706889350599[23] = 0;
   out_702684706889350599[24] = 0;
   out_702684706889350599[25] = 1;
   out_702684706889350599[26] = 0;
   out_702684706889350599[27] = 0;
   out_702684706889350599[28] = 1;
   out_702684706889350599[29] = 0;
   out_702684706889350599[30] = 0;
   out_702684706889350599[31] = 0;
   out_702684706889350599[32] = 0;
   out_702684706889350599[33] = 0;
   out_702684706889350599[34] = 0;
   out_702684706889350599[35] = 0;
   out_702684706889350599[36] = 0;
   out_702684706889350599[37] = 0;
   out_702684706889350599[38] = 0;
   out_702684706889350599[39] = 0;
   out_702684706889350599[40] = 0;
   out_702684706889350599[41] = 0;
   out_702684706889350599[42] = 0;
   out_702684706889350599[43] = 0;
   out_702684706889350599[44] = 1;
   out_702684706889350599[45] = 0;
   out_702684706889350599[46] = 0;
   out_702684706889350599[47] = 1;
   out_702684706889350599[48] = 0;
   out_702684706889350599[49] = 0;
   out_702684706889350599[50] = 0;
   out_702684706889350599[51] = 0;
   out_702684706889350599[52] = 0;
   out_702684706889350599[53] = 0;
}
void h_10(double *state, double *unused, double *out_767369525646024651) {
   out_767369525646024651[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_767369525646024651[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_767369525646024651[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8347276505705953254) {
   out_8347276505705953254[0] = 0;
   out_8347276505705953254[1] = 9.8100000000000005*cos(state[1]);
   out_8347276505705953254[2] = 0;
   out_8347276505705953254[3] = 0;
   out_8347276505705953254[4] = -state[8];
   out_8347276505705953254[5] = state[7];
   out_8347276505705953254[6] = 0;
   out_8347276505705953254[7] = state[5];
   out_8347276505705953254[8] = -state[4];
   out_8347276505705953254[9] = 0;
   out_8347276505705953254[10] = 0;
   out_8347276505705953254[11] = 0;
   out_8347276505705953254[12] = 1;
   out_8347276505705953254[13] = 0;
   out_8347276505705953254[14] = 0;
   out_8347276505705953254[15] = 1;
   out_8347276505705953254[16] = 0;
   out_8347276505705953254[17] = 0;
   out_8347276505705953254[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8347276505705953254[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8347276505705953254[20] = 0;
   out_8347276505705953254[21] = state[8];
   out_8347276505705953254[22] = 0;
   out_8347276505705953254[23] = -state[6];
   out_8347276505705953254[24] = -state[5];
   out_8347276505705953254[25] = 0;
   out_8347276505705953254[26] = state[3];
   out_8347276505705953254[27] = 0;
   out_8347276505705953254[28] = 0;
   out_8347276505705953254[29] = 0;
   out_8347276505705953254[30] = 0;
   out_8347276505705953254[31] = 1;
   out_8347276505705953254[32] = 0;
   out_8347276505705953254[33] = 0;
   out_8347276505705953254[34] = 1;
   out_8347276505705953254[35] = 0;
   out_8347276505705953254[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8347276505705953254[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8347276505705953254[38] = 0;
   out_8347276505705953254[39] = -state[7];
   out_8347276505705953254[40] = state[6];
   out_8347276505705953254[41] = 0;
   out_8347276505705953254[42] = state[4];
   out_8347276505705953254[43] = -state[3];
   out_8347276505705953254[44] = 0;
   out_8347276505705953254[45] = 0;
   out_8347276505705953254[46] = 0;
   out_8347276505705953254[47] = 0;
   out_8347276505705953254[48] = 0;
   out_8347276505705953254[49] = 0;
   out_8347276505705953254[50] = 1;
   out_8347276505705953254[51] = 0;
   out_8347276505705953254[52] = 0;
   out_8347276505705953254[53] = 1;
}
void h_13(double *state, double *unused, double *out_7518652466578138352) {
   out_7518652466578138352[0] = state[3];
   out_7518652466578138352[1] = state[4];
   out_7518652466578138352[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2509589118442982202) {
   out_2509589118442982202[0] = 0;
   out_2509589118442982202[1] = 0;
   out_2509589118442982202[2] = 0;
   out_2509589118442982202[3] = 1;
   out_2509589118442982202[4] = 0;
   out_2509589118442982202[5] = 0;
   out_2509589118442982202[6] = 0;
   out_2509589118442982202[7] = 0;
   out_2509589118442982202[8] = 0;
   out_2509589118442982202[9] = 0;
   out_2509589118442982202[10] = 0;
   out_2509589118442982202[11] = 0;
   out_2509589118442982202[12] = 0;
   out_2509589118442982202[13] = 0;
   out_2509589118442982202[14] = 0;
   out_2509589118442982202[15] = 0;
   out_2509589118442982202[16] = 0;
   out_2509589118442982202[17] = 0;
   out_2509589118442982202[18] = 0;
   out_2509589118442982202[19] = 0;
   out_2509589118442982202[20] = 0;
   out_2509589118442982202[21] = 0;
   out_2509589118442982202[22] = 1;
   out_2509589118442982202[23] = 0;
   out_2509589118442982202[24] = 0;
   out_2509589118442982202[25] = 0;
   out_2509589118442982202[26] = 0;
   out_2509589118442982202[27] = 0;
   out_2509589118442982202[28] = 0;
   out_2509589118442982202[29] = 0;
   out_2509589118442982202[30] = 0;
   out_2509589118442982202[31] = 0;
   out_2509589118442982202[32] = 0;
   out_2509589118442982202[33] = 0;
   out_2509589118442982202[34] = 0;
   out_2509589118442982202[35] = 0;
   out_2509589118442982202[36] = 0;
   out_2509589118442982202[37] = 0;
   out_2509589118442982202[38] = 0;
   out_2509589118442982202[39] = 0;
   out_2509589118442982202[40] = 0;
   out_2509589118442982202[41] = 1;
   out_2509589118442982202[42] = 0;
   out_2509589118442982202[43] = 0;
   out_2509589118442982202[44] = 0;
   out_2509589118442982202[45] = 0;
   out_2509589118442982202[46] = 0;
   out_2509589118442982202[47] = 0;
   out_2509589118442982202[48] = 0;
   out_2509589118442982202[49] = 0;
   out_2509589118442982202[50] = 0;
   out_2509589118442982202[51] = 0;
   out_2509589118442982202[52] = 0;
   out_2509589118442982202[53] = 0;
}
void h_14(double *state, double *unused, double *out_7727744869207997497) {
   out_7727744869207997497[0] = state[6];
   out_7727744869207997497[1] = state[7];
   out_7727744869207997497[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8183830522169091023) {
   out_8183830522169091023[0] = 0;
   out_8183830522169091023[1] = 0;
   out_8183830522169091023[2] = 0;
   out_8183830522169091023[3] = 0;
   out_8183830522169091023[4] = 0;
   out_8183830522169091023[5] = 0;
   out_8183830522169091023[6] = 1;
   out_8183830522169091023[7] = 0;
   out_8183830522169091023[8] = 0;
   out_8183830522169091023[9] = 0;
   out_8183830522169091023[10] = 0;
   out_8183830522169091023[11] = 0;
   out_8183830522169091023[12] = 0;
   out_8183830522169091023[13] = 0;
   out_8183830522169091023[14] = 0;
   out_8183830522169091023[15] = 0;
   out_8183830522169091023[16] = 0;
   out_8183830522169091023[17] = 0;
   out_8183830522169091023[18] = 0;
   out_8183830522169091023[19] = 0;
   out_8183830522169091023[20] = 0;
   out_8183830522169091023[21] = 0;
   out_8183830522169091023[22] = 0;
   out_8183830522169091023[23] = 0;
   out_8183830522169091023[24] = 0;
   out_8183830522169091023[25] = 1;
   out_8183830522169091023[26] = 0;
   out_8183830522169091023[27] = 0;
   out_8183830522169091023[28] = 0;
   out_8183830522169091023[29] = 0;
   out_8183830522169091023[30] = 0;
   out_8183830522169091023[31] = 0;
   out_8183830522169091023[32] = 0;
   out_8183830522169091023[33] = 0;
   out_8183830522169091023[34] = 0;
   out_8183830522169091023[35] = 0;
   out_8183830522169091023[36] = 0;
   out_8183830522169091023[37] = 0;
   out_8183830522169091023[38] = 0;
   out_8183830522169091023[39] = 0;
   out_8183830522169091023[40] = 0;
   out_8183830522169091023[41] = 0;
   out_8183830522169091023[42] = 0;
   out_8183830522169091023[43] = 0;
   out_8183830522169091023[44] = 1;
   out_8183830522169091023[45] = 0;
   out_8183830522169091023[46] = 0;
   out_8183830522169091023[47] = 0;
   out_8183830522169091023[48] = 0;
   out_8183830522169091023[49] = 0;
   out_8183830522169091023[50] = 0;
   out_8183830522169091023[51] = 0;
   out_8183830522169091023[52] = 0;
   out_8183830522169091023[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_8230036097863094971) {
  err_fun(nom_x, delta_x, out_8230036097863094971);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8741051770711475830) {
  inv_err_fun(nom_x, true_x, out_8741051770711475830);
}
void pose_H_mod_fun(double *state, double *out_1900632188772248703) {
  H_mod_fun(state, out_1900632188772248703);
}
void pose_f_fun(double *state, double dt, double *out_3077738493587277525) {
  f_fun(state,  dt, out_3077738493587277525);
}
void pose_F_fun(double *state, double dt, double *out_474426866180563475) {
  F_fun(state,  dt, out_474426866180563475);
}
void pose_h_4(double *state, double *unused, double *out_616527671886839495) {
  h_4(state, unused, out_616527671886839495);
}
void pose_H_4(double *state, double *unused, double *out_702684706889350599) {
  H_4(state, unused, out_702684706889350599);
}
void pose_h_10(double *state, double *unused, double *out_767369525646024651) {
  h_10(state, unused, out_767369525646024651);
}
void pose_H_10(double *state, double *unused, double *out_8347276505705953254) {
  H_10(state, unused, out_8347276505705953254);
}
void pose_h_13(double *state, double *unused, double *out_7518652466578138352) {
  h_13(state, unused, out_7518652466578138352);
}
void pose_H_13(double *state, double *unused, double *out_2509589118442982202) {
  H_13(state, unused, out_2509589118442982202);
}
void pose_h_14(double *state, double *unused, double *out_7727744869207997497) {
  h_14(state, unused, out_7727744869207997497);
}
void pose_H_14(double *state, double *unused, double *out_8183830522169091023) {
  H_14(state, unused, out_8183830522169091023);
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
