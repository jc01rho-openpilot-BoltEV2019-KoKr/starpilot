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
void err_fun(double *nom_x, double *delta_x, double *out_842964569186968919) {
   out_842964569186968919[0] = delta_x[0] + nom_x[0];
   out_842964569186968919[1] = delta_x[1] + nom_x[1];
   out_842964569186968919[2] = delta_x[2] + nom_x[2];
   out_842964569186968919[3] = delta_x[3] + nom_x[3];
   out_842964569186968919[4] = delta_x[4] + nom_x[4];
   out_842964569186968919[5] = delta_x[5] + nom_x[5];
   out_842964569186968919[6] = delta_x[6] + nom_x[6];
   out_842964569186968919[7] = delta_x[7] + nom_x[7];
   out_842964569186968919[8] = delta_x[8] + nom_x[8];
   out_842964569186968919[9] = delta_x[9] + nom_x[9];
   out_842964569186968919[10] = delta_x[10] + nom_x[10];
   out_842964569186968919[11] = delta_x[11] + nom_x[11];
   out_842964569186968919[12] = delta_x[12] + nom_x[12];
   out_842964569186968919[13] = delta_x[13] + nom_x[13];
   out_842964569186968919[14] = delta_x[14] + nom_x[14];
   out_842964569186968919[15] = delta_x[15] + nom_x[15];
   out_842964569186968919[16] = delta_x[16] + nom_x[16];
   out_842964569186968919[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7637995249051351300) {
   out_7637995249051351300[0] = -nom_x[0] + true_x[0];
   out_7637995249051351300[1] = -nom_x[1] + true_x[1];
   out_7637995249051351300[2] = -nom_x[2] + true_x[2];
   out_7637995249051351300[3] = -nom_x[3] + true_x[3];
   out_7637995249051351300[4] = -nom_x[4] + true_x[4];
   out_7637995249051351300[5] = -nom_x[5] + true_x[5];
   out_7637995249051351300[6] = -nom_x[6] + true_x[6];
   out_7637995249051351300[7] = -nom_x[7] + true_x[7];
   out_7637995249051351300[8] = -nom_x[8] + true_x[8];
   out_7637995249051351300[9] = -nom_x[9] + true_x[9];
   out_7637995249051351300[10] = -nom_x[10] + true_x[10];
   out_7637995249051351300[11] = -nom_x[11] + true_x[11];
   out_7637995249051351300[12] = -nom_x[12] + true_x[12];
   out_7637995249051351300[13] = -nom_x[13] + true_x[13];
   out_7637995249051351300[14] = -nom_x[14] + true_x[14];
   out_7637995249051351300[15] = -nom_x[15] + true_x[15];
   out_7637995249051351300[16] = -nom_x[16] + true_x[16];
   out_7637995249051351300[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_8306889626903079841) {
   out_8306889626903079841[0] = 1.0;
   out_8306889626903079841[1] = 0.0;
   out_8306889626903079841[2] = 0.0;
   out_8306889626903079841[3] = 0.0;
   out_8306889626903079841[4] = 0.0;
   out_8306889626903079841[5] = 0.0;
   out_8306889626903079841[6] = 0.0;
   out_8306889626903079841[7] = 0.0;
   out_8306889626903079841[8] = 0.0;
   out_8306889626903079841[9] = 0.0;
   out_8306889626903079841[10] = 0.0;
   out_8306889626903079841[11] = 0.0;
   out_8306889626903079841[12] = 0.0;
   out_8306889626903079841[13] = 0.0;
   out_8306889626903079841[14] = 0.0;
   out_8306889626903079841[15] = 0.0;
   out_8306889626903079841[16] = 0.0;
   out_8306889626903079841[17] = 0.0;
   out_8306889626903079841[18] = 0.0;
   out_8306889626903079841[19] = 1.0;
   out_8306889626903079841[20] = 0.0;
   out_8306889626903079841[21] = 0.0;
   out_8306889626903079841[22] = 0.0;
   out_8306889626903079841[23] = 0.0;
   out_8306889626903079841[24] = 0.0;
   out_8306889626903079841[25] = 0.0;
   out_8306889626903079841[26] = 0.0;
   out_8306889626903079841[27] = 0.0;
   out_8306889626903079841[28] = 0.0;
   out_8306889626903079841[29] = 0.0;
   out_8306889626903079841[30] = 0.0;
   out_8306889626903079841[31] = 0.0;
   out_8306889626903079841[32] = 0.0;
   out_8306889626903079841[33] = 0.0;
   out_8306889626903079841[34] = 0.0;
   out_8306889626903079841[35] = 0.0;
   out_8306889626903079841[36] = 0.0;
   out_8306889626903079841[37] = 0.0;
   out_8306889626903079841[38] = 1.0;
   out_8306889626903079841[39] = 0.0;
   out_8306889626903079841[40] = 0.0;
   out_8306889626903079841[41] = 0.0;
   out_8306889626903079841[42] = 0.0;
   out_8306889626903079841[43] = 0.0;
   out_8306889626903079841[44] = 0.0;
   out_8306889626903079841[45] = 0.0;
   out_8306889626903079841[46] = 0.0;
   out_8306889626903079841[47] = 0.0;
   out_8306889626903079841[48] = 0.0;
   out_8306889626903079841[49] = 0.0;
   out_8306889626903079841[50] = 0.0;
   out_8306889626903079841[51] = 0.0;
   out_8306889626903079841[52] = 0.0;
   out_8306889626903079841[53] = 0.0;
   out_8306889626903079841[54] = 0.0;
   out_8306889626903079841[55] = 0.0;
   out_8306889626903079841[56] = 0.0;
   out_8306889626903079841[57] = 1.0;
   out_8306889626903079841[58] = 0.0;
   out_8306889626903079841[59] = 0.0;
   out_8306889626903079841[60] = 0.0;
   out_8306889626903079841[61] = 0.0;
   out_8306889626903079841[62] = 0.0;
   out_8306889626903079841[63] = 0.0;
   out_8306889626903079841[64] = 0.0;
   out_8306889626903079841[65] = 0.0;
   out_8306889626903079841[66] = 0.0;
   out_8306889626903079841[67] = 0.0;
   out_8306889626903079841[68] = 0.0;
   out_8306889626903079841[69] = 0.0;
   out_8306889626903079841[70] = 0.0;
   out_8306889626903079841[71] = 0.0;
   out_8306889626903079841[72] = 0.0;
   out_8306889626903079841[73] = 0.0;
   out_8306889626903079841[74] = 0.0;
   out_8306889626903079841[75] = 0.0;
   out_8306889626903079841[76] = 1.0;
   out_8306889626903079841[77] = 0.0;
   out_8306889626903079841[78] = 0.0;
   out_8306889626903079841[79] = 0.0;
   out_8306889626903079841[80] = 0.0;
   out_8306889626903079841[81] = 0.0;
   out_8306889626903079841[82] = 0.0;
   out_8306889626903079841[83] = 0.0;
   out_8306889626903079841[84] = 0.0;
   out_8306889626903079841[85] = 0.0;
   out_8306889626903079841[86] = 0.0;
   out_8306889626903079841[87] = 0.0;
   out_8306889626903079841[88] = 0.0;
   out_8306889626903079841[89] = 0.0;
   out_8306889626903079841[90] = 0.0;
   out_8306889626903079841[91] = 0.0;
   out_8306889626903079841[92] = 0.0;
   out_8306889626903079841[93] = 0.0;
   out_8306889626903079841[94] = 0.0;
   out_8306889626903079841[95] = 1.0;
   out_8306889626903079841[96] = 0.0;
   out_8306889626903079841[97] = 0.0;
   out_8306889626903079841[98] = 0.0;
   out_8306889626903079841[99] = 0.0;
   out_8306889626903079841[100] = 0.0;
   out_8306889626903079841[101] = 0.0;
   out_8306889626903079841[102] = 0.0;
   out_8306889626903079841[103] = 0.0;
   out_8306889626903079841[104] = 0.0;
   out_8306889626903079841[105] = 0.0;
   out_8306889626903079841[106] = 0.0;
   out_8306889626903079841[107] = 0.0;
   out_8306889626903079841[108] = 0.0;
   out_8306889626903079841[109] = 0.0;
   out_8306889626903079841[110] = 0.0;
   out_8306889626903079841[111] = 0.0;
   out_8306889626903079841[112] = 0.0;
   out_8306889626903079841[113] = 0.0;
   out_8306889626903079841[114] = 1.0;
   out_8306889626903079841[115] = 0.0;
   out_8306889626903079841[116] = 0.0;
   out_8306889626903079841[117] = 0.0;
   out_8306889626903079841[118] = 0.0;
   out_8306889626903079841[119] = 0.0;
   out_8306889626903079841[120] = 0.0;
   out_8306889626903079841[121] = 0.0;
   out_8306889626903079841[122] = 0.0;
   out_8306889626903079841[123] = 0.0;
   out_8306889626903079841[124] = 0.0;
   out_8306889626903079841[125] = 0.0;
   out_8306889626903079841[126] = 0.0;
   out_8306889626903079841[127] = 0.0;
   out_8306889626903079841[128] = 0.0;
   out_8306889626903079841[129] = 0.0;
   out_8306889626903079841[130] = 0.0;
   out_8306889626903079841[131] = 0.0;
   out_8306889626903079841[132] = 0.0;
   out_8306889626903079841[133] = 1.0;
   out_8306889626903079841[134] = 0.0;
   out_8306889626903079841[135] = 0.0;
   out_8306889626903079841[136] = 0.0;
   out_8306889626903079841[137] = 0.0;
   out_8306889626903079841[138] = 0.0;
   out_8306889626903079841[139] = 0.0;
   out_8306889626903079841[140] = 0.0;
   out_8306889626903079841[141] = 0.0;
   out_8306889626903079841[142] = 0.0;
   out_8306889626903079841[143] = 0.0;
   out_8306889626903079841[144] = 0.0;
   out_8306889626903079841[145] = 0.0;
   out_8306889626903079841[146] = 0.0;
   out_8306889626903079841[147] = 0.0;
   out_8306889626903079841[148] = 0.0;
   out_8306889626903079841[149] = 0.0;
   out_8306889626903079841[150] = 0.0;
   out_8306889626903079841[151] = 0.0;
   out_8306889626903079841[152] = 1.0;
   out_8306889626903079841[153] = 0.0;
   out_8306889626903079841[154] = 0.0;
   out_8306889626903079841[155] = 0.0;
   out_8306889626903079841[156] = 0.0;
   out_8306889626903079841[157] = 0.0;
   out_8306889626903079841[158] = 0.0;
   out_8306889626903079841[159] = 0.0;
   out_8306889626903079841[160] = 0.0;
   out_8306889626903079841[161] = 0.0;
   out_8306889626903079841[162] = 0.0;
   out_8306889626903079841[163] = 0.0;
   out_8306889626903079841[164] = 0.0;
   out_8306889626903079841[165] = 0.0;
   out_8306889626903079841[166] = 0.0;
   out_8306889626903079841[167] = 0.0;
   out_8306889626903079841[168] = 0.0;
   out_8306889626903079841[169] = 0.0;
   out_8306889626903079841[170] = 0.0;
   out_8306889626903079841[171] = 1.0;
   out_8306889626903079841[172] = 0.0;
   out_8306889626903079841[173] = 0.0;
   out_8306889626903079841[174] = 0.0;
   out_8306889626903079841[175] = 0.0;
   out_8306889626903079841[176] = 0.0;
   out_8306889626903079841[177] = 0.0;
   out_8306889626903079841[178] = 0.0;
   out_8306889626903079841[179] = 0.0;
   out_8306889626903079841[180] = 0.0;
   out_8306889626903079841[181] = 0.0;
   out_8306889626903079841[182] = 0.0;
   out_8306889626903079841[183] = 0.0;
   out_8306889626903079841[184] = 0.0;
   out_8306889626903079841[185] = 0.0;
   out_8306889626903079841[186] = 0.0;
   out_8306889626903079841[187] = 0.0;
   out_8306889626903079841[188] = 0.0;
   out_8306889626903079841[189] = 0.0;
   out_8306889626903079841[190] = 1.0;
   out_8306889626903079841[191] = 0.0;
   out_8306889626903079841[192] = 0.0;
   out_8306889626903079841[193] = 0.0;
   out_8306889626903079841[194] = 0.0;
   out_8306889626903079841[195] = 0.0;
   out_8306889626903079841[196] = 0.0;
   out_8306889626903079841[197] = 0.0;
   out_8306889626903079841[198] = 0.0;
   out_8306889626903079841[199] = 0.0;
   out_8306889626903079841[200] = 0.0;
   out_8306889626903079841[201] = 0.0;
   out_8306889626903079841[202] = 0.0;
   out_8306889626903079841[203] = 0.0;
   out_8306889626903079841[204] = 0.0;
   out_8306889626903079841[205] = 0.0;
   out_8306889626903079841[206] = 0.0;
   out_8306889626903079841[207] = 0.0;
   out_8306889626903079841[208] = 0.0;
   out_8306889626903079841[209] = 1.0;
   out_8306889626903079841[210] = 0.0;
   out_8306889626903079841[211] = 0.0;
   out_8306889626903079841[212] = 0.0;
   out_8306889626903079841[213] = 0.0;
   out_8306889626903079841[214] = 0.0;
   out_8306889626903079841[215] = 0.0;
   out_8306889626903079841[216] = 0.0;
   out_8306889626903079841[217] = 0.0;
   out_8306889626903079841[218] = 0.0;
   out_8306889626903079841[219] = 0.0;
   out_8306889626903079841[220] = 0.0;
   out_8306889626903079841[221] = 0.0;
   out_8306889626903079841[222] = 0.0;
   out_8306889626903079841[223] = 0.0;
   out_8306889626903079841[224] = 0.0;
   out_8306889626903079841[225] = 0.0;
   out_8306889626903079841[226] = 0.0;
   out_8306889626903079841[227] = 0.0;
   out_8306889626903079841[228] = 1.0;
   out_8306889626903079841[229] = 0.0;
   out_8306889626903079841[230] = 0.0;
   out_8306889626903079841[231] = 0.0;
   out_8306889626903079841[232] = 0.0;
   out_8306889626903079841[233] = 0.0;
   out_8306889626903079841[234] = 0.0;
   out_8306889626903079841[235] = 0.0;
   out_8306889626903079841[236] = 0.0;
   out_8306889626903079841[237] = 0.0;
   out_8306889626903079841[238] = 0.0;
   out_8306889626903079841[239] = 0.0;
   out_8306889626903079841[240] = 0.0;
   out_8306889626903079841[241] = 0.0;
   out_8306889626903079841[242] = 0.0;
   out_8306889626903079841[243] = 0.0;
   out_8306889626903079841[244] = 0.0;
   out_8306889626903079841[245] = 0.0;
   out_8306889626903079841[246] = 0.0;
   out_8306889626903079841[247] = 1.0;
   out_8306889626903079841[248] = 0.0;
   out_8306889626903079841[249] = 0.0;
   out_8306889626903079841[250] = 0.0;
   out_8306889626903079841[251] = 0.0;
   out_8306889626903079841[252] = 0.0;
   out_8306889626903079841[253] = 0.0;
   out_8306889626903079841[254] = 0.0;
   out_8306889626903079841[255] = 0.0;
   out_8306889626903079841[256] = 0.0;
   out_8306889626903079841[257] = 0.0;
   out_8306889626903079841[258] = 0.0;
   out_8306889626903079841[259] = 0.0;
   out_8306889626903079841[260] = 0.0;
   out_8306889626903079841[261] = 0.0;
   out_8306889626903079841[262] = 0.0;
   out_8306889626903079841[263] = 0.0;
   out_8306889626903079841[264] = 0.0;
   out_8306889626903079841[265] = 0.0;
   out_8306889626903079841[266] = 1.0;
   out_8306889626903079841[267] = 0.0;
   out_8306889626903079841[268] = 0.0;
   out_8306889626903079841[269] = 0.0;
   out_8306889626903079841[270] = 0.0;
   out_8306889626903079841[271] = 0.0;
   out_8306889626903079841[272] = 0.0;
   out_8306889626903079841[273] = 0.0;
   out_8306889626903079841[274] = 0.0;
   out_8306889626903079841[275] = 0.0;
   out_8306889626903079841[276] = 0.0;
   out_8306889626903079841[277] = 0.0;
   out_8306889626903079841[278] = 0.0;
   out_8306889626903079841[279] = 0.0;
   out_8306889626903079841[280] = 0.0;
   out_8306889626903079841[281] = 0.0;
   out_8306889626903079841[282] = 0.0;
   out_8306889626903079841[283] = 0.0;
   out_8306889626903079841[284] = 0.0;
   out_8306889626903079841[285] = 1.0;
   out_8306889626903079841[286] = 0.0;
   out_8306889626903079841[287] = 0.0;
   out_8306889626903079841[288] = 0.0;
   out_8306889626903079841[289] = 0.0;
   out_8306889626903079841[290] = 0.0;
   out_8306889626903079841[291] = 0.0;
   out_8306889626903079841[292] = 0.0;
   out_8306889626903079841[293] = 0.0;
   out_8306889626903079841[294] = 0.0;
   out_8306889626903079841[295] = 0.0;
   out_8306889626903079841[296] = 0.0;
   out_8306889626903079841[297] = 0.0;
   out_8306889626903079841[298] = 0.0;
   out_8306889626903079841[299] = 0.0;
   out_8306889626903079841[300] = 0.0;
   out_8306889626903079841[301] = 0.0;
   out_8306889626903079841[302] = 0.0;
   out_8306889626903079841[303] = 0.0;
   out_8306889626903079841[304] = 1.0;
   out_8306889626903079841[305] = 0.0;
   out_8306889626903079841[306] = 0.0;
   out_8306889626903079841[307] = 0.0;
   out_8306889626903079841[308] = 0.0;
   out_8306889626903079841[309] = 0.0;
   out_8306889626903079841[310] = 0.0;
   out_8306889626903079841[311] = 0.0;
   out_8306889626903079841[312] = 0.0;
   out_8306889626903079841[313] = 0.0;
   out_8306889626903079841[314] = 0.0;
   out_8306889626903079841[315] = 0.0;
   out_8306889626903079841[316] = 0.0;
   out_8306889626903079841[317] = 0.0;
   out_8306889626903079841[318] = 0.0;
   out_8306889626903079841[319] = 0.0;
   out_8306889626903079841[320] = 0.0;
   out_8306889626903079841[321] = 0.0;
   out_8306889626903079841[322] = 0.0;
   out_8306889626903079841[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5013225008344736149) {
   out_5013225008344736149[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5013225008344736149[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5013225008344736149[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5013225008344736149[3] = dt*state[12] + state[3];
   out_5013225008344736149[4] = dt*state[13] + state[4];
   out_5013225008344736149[5] = dt*state[14] + state[5];
   out_5013225008344736149[6] = state[6];
   out_5013225008344736149[7] = state[7];
   out_5013225008344736149[8] = state[8];
   out_5013225008344736149[9] = state[9];
   out_5013225008344736149[10] = state[10];
   out_5013225008344736149[11] = state[11];
   out_5013225008344736149[12] = state[12];
   out_5013225008344736149[13] = state[13];
   out_5013225008344736149[14] = state[14];
   out_5013225008344736149[15] = state[15];
   out_5013225008344736149[16] = state[16];
   out_5013225008344736149[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8990818239492707931) {
   out_8990818239492707931[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8990818239492707931[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8990818239492707931[2] = 0;
   out_8990818239492707931[3] = 0;
   out_8990818239492707931[4] = 0;
   out_8990818239492707931[5] = 0;
   out_8990818239492707931[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8990818239492707931[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8990818239492707931[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8990818239492707931[9] = 0;
   out_8990818239492707931[10] = 0;
   out_8990818239492707931[11] = 0;
   out_8990818239492707931[12] = 0;
   out_8990818239492707931[13] = 0;
   out_8990818239492707931[14] = 0;
   out_8990818239492707931[15] = 0;
   out_8990818239492707931[16] = 0;
   out_8990818239492707931[17] = 0;
   out_8990818239492707931[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8990818239492707931[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8990818239492707931[20] = 0;
   out_8990818239492707931[21] = 0;
   out_8990818239492707931[22] = 0;
   out_8990818239492707931[23] = 0;
   out_8990818239492707931[24] = 0;
   out_8990818239492707931[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8990818239492707931[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8990818239492707931[27] = 0;
   out_8990818239492707931[28] = 0;
   out_8990818239492707931[29] = 0;
   out_8990818239492707931[30] = 0;
   out_8990818239492707931[31] = 0;
   out_8990818239492707931[32] = 0;
   out_8990818239492707931[33] = 0;
   out_8990818239492707931[34] = 0;
   out_8990818239492707931[35] = 0;
   out_8990818239492707931[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8990818239492707931[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8990818239492707931[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8990818239492707931[39] = 0;
   out_8990818239492707931[40] = 0;
   out_8990818239492707931[41] = 0;
   out_8990818239492707931[42] = 0;
   out_8990818239492707931[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8990818239492707931[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8990818239492707931[45] = 0;
   out_8990818239492707931[46] = 0;
   out_8990818239492707931[47] = 0;
   out_8990818239492707931[48] = 0;
   out_8990818239492707931[49] = 0;
   out_8990818239492707931[50] = 0;
   out_8990818239492707931[51] = 0;
   out_8990818239492707931[52] = 0;
   out_8990818239492707931[53] = 0;
   out_8990818239492707931[54] = 0;
   out_8990818239492707931[55] = 0;
   out_8990818239492707931[56] = 0;
   out_8990818239492707931[57] = 1;
   out_8990818239492707931[58] = 0;
   out_8990818239492707931[59] = 0;
   out_8990818239492707931[60] = 0;
   out_8990818239492707931[61] = 0;
   out_8990818239492707931[62] = 0;
   out_8990818239492707931[63] = 0;
   out_8990818239492707931[64] = 0;
   out_8990818239492707931[65] = 0;
   out_8990818239492707931[66] = dt;
   out_8990818239492707931[67] = 0;
   out_8990818239492707931[68] = 0;
   out_8990818239492707931[69] = 0;
   out_8990818239492707931[70] = 0;
   out_8990818239492707931[71] = 0;
   out_8990818239492707931[72] = 0;
   out_8990818239492707931[73] = 0;
   out_8990818239492707931[74] = 0;
   out_8990818239492707931[75] = 0;
   out_8990818239492707931[76] = 1;
   out_8990818239492707931[77] = 0;
   out_8990818239492707931[78] = 0;
   out_8990818239492707931[79] = 0;
   out_8990818239492707931[80] = 0;
   out_8990818239492707931[81] = 0;
   out_8990818239492707931[82] = 0;
   out_8990818239492707931[83] = 0;
   out_8990818239492707931[84] = 0;
   out_8990818239492707931[85] = dt;
   out_8990818239492707931[86] = 0;
   out_8990818239492707931[87] = 0;
   out_8990818239492707931[88] = 0;
   out_8990818239492707931[89] = 0;
   out_8990818239492707931[90] = 0;
   out_8990818239492707931[91] = 0;
   out_8990818239492707931[92] = 0;
   out_8990818239492707931[93] = 0;
   out_8990818239492707931[94] = 0;
   out_8990818239492707931[95] = 1;
   out_8990818239492707931[96] = 0;
   out_8990818239492707931[97] = 0;
   out_8990818239492707931[98] = 0;
   out_8990818239492707931[99] = 0;
   out_8990818239492707931[100] = 0;
   out_8990818239492707931[101] = 0;
   out_8990818239492707931[102] = 0;
   out_8990818239492707931[103] = 0;
   out_8990818239492707931[104] = dt;
   out_8990818239492707931[105] = 0;
   out_8990818239492707931[106] = 0;
   out_8990818239492707931[107] = 0;
   out_8990818239492707931[108] = 0;
   out_8990818239492707931[109] = 0;
   out_8990818239492707931[110] = 0;
   out_8990818239492707931[111] = 0;
   out_8990818239492707931[112] = 0;
   out_8990818239492707931[113] = 0;
   out_8990818239492707931[114] = 1;
   out_8990818239492707931[115] = 0;
   out_8990818239492707931[116] = 0;
   out_8990818239492707931[117] = 0;
   out_8990818239492707931[118] = 0;
   out_8990818239492707931[119] = 0;
   out_8990818239492707931[120] = 0;
   out_8990818239492707931[121] = 0;
   out_8990818239492707931[122] = 0;
   out_8990818239492707931[123] = 0;
   out_8990818239492707931[124] = 0;
   out_8990818239492707931[125] = 0;
   out_8990818239492707931[126] = 0;
   out_8990818239492707931[127] = 0;
   out_8990818239492707931[128] = 0;
   out_8990818239492707931[129] = 0;
   out_8990818239492707931[130] = 0;
   out_8990818239492707931[131] = 0;
   out_8990818239492707931[132] = 0;
   out_8990818239492707931[133] = 1;
   out_8990818239492707931[134] = 0;
   out_8990818239492707931[135] = 0;
   out_8990818239492707931[136] = 0;
   out_8990818239492707931[137] = 0;
   out_8990818239492707931[138] = 0;
   out_8990818239492707931[139] = 0;
   out_8990818239492707931[140] = 0;
   out_8990818239492707931[141] = 0;
   out_8990818239492707931[142] = 0;
   out_8990818239492707931[143] = 0;
   out_8990818239492707931[144] = 0;
   out_8990818239492707931[145] = 0;
   out_8990818239492707931[146] = 0;
   out_8990818239492707931[147] = 0;
   out_8990818239492707931[148] = 0;
   out_8990818239492707931[149] = 0;
   out_8990818239492707931[150] = 0;
   out_8990818239492707931[151] = 0;
   out_8990818239492707931[152] = 1;
   out_8990818239492707931[153] = 0;
   out_8990818239492707931[154] = 0;
   out_8990818239492707931[155] = 0;
   out_8990818239492707931[156] = 0;
   out_8990818239492707931[157] = 0;
   out_8990818239492707931[158] = 0;
   out_8990818239492707931[159] = 0;
   out_8990818239492707931[160] = 0;
   out_8990818239492707931[161] = 0;
   out_8990818239492707931[162] = 0;
   out_8990818239492707931[163] = 0;
   out_8990818239492707931[164] = 0;
   out_8990818239492707931[165] = 0;
   out_8990818239492707931[166] = 0;
   out_8990818239492707931[167] = 0;
   out_8990818239492707931[168] = 0;
   out_8990818239492707931[169] = 0;
   out_8990818239492707931[170] = 0;
   out_8990818239492707931[171] = 1;
   out_8990818239492707931[172] = 0;
   out_8990818239492707931[173] = 0;
   out_8990818239492707931[174] = 0;
   out_8990818239492707931[175] = 0;
   out_8990818239492707931[176] = 0;
   out_8990818239492707931[177] = 0;
   out_8990818239492707931[178] = 0;
   out_8990818239492707931[179] = 0;
   out_8990818239492707931[180] = 0;
   out_8990818239492707931[181] = 0;
   out_8990818239492707931[182] = 0;
   out_8990818239492707931[183] = 0;
   out_8990818239492707931[184] = 0;
   out_8990818239492707931[185] = 0;
   out_8990818239492707931[186] = 0;
   out_8990818239492707931[187] = 0;
   out_8990818239492707931[188] = 0;
   out_8990818239492707931[189] = 0;
   out_8990818239492707931[190] = 1;
   out_8990818239492707931[191] = 0;
   out_8990818239492707931[192] = 0;
   out_8990818239492707931[193] = 0;
   out_8990818239492707931[194] = 0;
   out_8990818239492707931[195] = 0;
   out_8990818239492707931[196] = 0;
   out_8990818239492707931[197] = 0;
   out_8990818239492707931[198] = 0;
   out_8990818239492707931[199] = 0;
   out_8990818239492707931[200] = 0;
   out_8990818239492707931[201] = 0;
   out_8990818239492707931[202] = 0;
   out_8990818239492707931[203] = 0;
   out_8990818239492707931[204] = 0;
   out_8990818239492707931[205] = 0;
   out_8990818239492707931[206] = 0;
   out_8990818239492707931[207] = 0;
   out_8990818239492707931[208] = 0;
   out_8990818239492707931[209] = 1;
   out_8990818239492707931[210] = 0;
   out_8990818239492707931[211] = 0;
   out_8990818239492707931[212] = 0;
   out_8990818239492707931[213] = 0;
   out_8990818239492707931[214] = 0;
   out_8990818239492707931[215] = 0;
   out_8990818239492707931[216] = 0;
   out_8990818239492707931[217] = 0;
   out_8990818239492707931[218] = 0;
   out_8990818239492707931[219] = 0;
   out_8990818239492707931[220] = 0;
   out_8990818239492707931[221] = 0;
   out_8990818239492707931[222] = 0;
   out_8990818239492707931[223] = 0;
   out_8990818239492707931[224] = 0;
   out_8990818239492707931[225] = 0;
   out_8990818239492707931[226] = 0;
   out_8990818239492707931[227] = 0;
   out_8990818239492707931[228] = 1;
   out_8990818239492707931[229] = 0;
   out_8990818239492707931[230] = 0;
   out_8990818239492707931[231] = 0;
   out_8990818239492707931[232] = 0;
   out_8990818239492707931[233] = 0;
   out_8990818239492707931[234] = 0;
   out_8990818239492707931[235] = 0;
   out_8990818239492707931[236] = 0;
   out_8990818239492707931[237] = 0;
   out_8990818239492707931[238] = 0;
   out_8990818239492707931[239] = 0;
   out_8990818239492707931[240] = 0;
   out_8990818239492707931[241] = 0;
   out_8990818239492707931[242] = 0;
   out_8990818239492707931[243] = 0;
   out_8990818239492707931[244] = 0;
   out_8990818239492707931[245] = 0;
   out_8990818239492707931[246] = 0;
   out_8990818239492707931[247] = 1;
   out_8990818239492707931[248] = 0;
   out_8990818239492707931[249] = 0;
   out_8990818239492707931[250] = 0;
   out_8990818239492707931[251] = 0;
   out_8990818239492707931[252] = 0;
   out_8990818239492707931[253] = 0;
   out_8990818239492707931[254] = 0;
   out_8990818239492707931[255] = 0;
   out_8990818239492707931[256] = 0;
   out_8990818239492707931[257] = 0;
   out_8990818239492707931[258] = 0;
   out_8990818239492707931[259] = 0;
   out_8990818239492707931[260] = 0;
   out_8990818239492707931[261] = 0;
   out_8990818239492707931[262] = 0;
   out_8990818239492707931[263] = 0;
   out_8990818239492707931[264] = 0;
   out_8990818239492707931[265] = 0;
   out_8990818239492707931[266] = 1;
   out_8990818239492707931[267] = 0;
   out_8990818239492707931[268] = 0;
   out_8990818239492707931[269] = 0;
   out_8990818239492707931[270] = 0;
   out_8990818239492707931[271] = 0;
   out_8990818239492707931[272] = 0;
   out_8990818239492707931[273] = 0;
   out_8990818239492707931[274] = 0;
   out_8990818239492707931[275] = 0;
   out_8990818239492707931[276] = 0;
   out_8990818239492707931[277] = 0;
   out_8990818239492707931[278] = 0;
   out_8990818239492707931[279] = 0;
   out_8990818239492707931[280] = 0;
   out_8990818239492707931[281] = 0;
   out_8990818239492707931[282] = 0;
   out_8990818239492707931[283] = 0;
   out_8990818239492707931[284] = 0;
   out_8990818239492707931[285] = 1;
   out_8990818239492707931[286] = 0;
   out_8990818239492707931[287] = 0;
   out_8990818239492707931[288] = 0;
   out_8990818239492707931[289] = 0;
   out_8990818239492707931[290] = 0;
   out_8990818239492707931[291] = 0;
   out_8990818239492707931[292] = 0;
   out_8990818239492707931[293] = 0;
   out_8990818239492707931[294] = 0;
   out_8990818239492707931[295] = 0;
   out_8990818239492707931[296] = 0;
   out_8990818239492707931[297] = 0;
   out_8990818239492707931[298] = 0;
   out_8990818239492707931[299] = 0;
   out_8990818239492707931[300] = 0;
   out_8990818239492707931[301] = 0;
   out_8990818239492707931[302] = 0;
   out_8990818239492707931[303] = 0;
   out_8990818239492707931[304] = 1;
   out_8990818239492707931[305] = 0;
   out_8990818239492707931[306] = 0;
   out_8990818239492707931[307] = 0;
   out_8990818239492707931[308] = 0;
   out_8990818239492707931[309] = 0;
   out_8990818239492707931[310] = 0;
   out_8990818239492707931[311] = 0;
   out_8990818239492707931[312] = 0;
   out_8990818239492707931[313] = 0;
   out_8990818239492707931[314] = 0;
   out_8990818239492707931[315] = 0;
   out_8990818239492707931[316] = 0;
   out_8990818239492707931[317] = 0;
   out_8990818239492707931[318] = 0;
   out_8990818239492707931[319] = 0;
   out_8990818239492707931[320] = 0;
   out_8990818239492707931[321] = 0;
   out_8990818239492707931[322] = 0;
   out_8990818239492707931[323] = 1;
}
void h_4(double *state, double *unused, double *out_4553534383789500912) {
   out_4553534383789500912[0] = state[6] + state[9];
   out_4553534383789500912[1] = state[7] + state[10];
   out_4553534383789500912[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_637472039154741501) {
   out_637472039154741501[0] = 0;
   out_637472039154741501[1] = 0;
   out_637472039154741501[2] = 0;
   out_637472039154741501[3] = 0;
   out_637472039154741501[4] = 0;
   out_637472039154741501[5] = 0;
   out_637472039154741501[6] = 1;
   out_637472039154741501[7] = 0;
   out_637472039154741501[8] = 0;
   out_637472039154741501[9] = 1;
   out_637472039154741501[10] = 0;
   out_637472039154741501[11] = 0;
   out_637472039154741501[12] = 0;
   out_637472039154741501[13] = 0;
   out_637472039154741501[14] = 0;
   out_637472039154741501[15] = 0;
   out_637472039154741501[16] = 0;
   out_637472039154741501[17] = 0;
   out_637472039154741501[18] = 0;
   out_637472039154741501[19] = 0;
   out_637472039154741501[20] = 0;
   out_637472039154741501[21] = 0;
   out_637472039154741501[22] = 0;
   out_637472039154741501[23] = 0;
   out_637472039154741501[24] = 0;
   out_637472039154741501[25] = 1;
   out_637472039154741501[26] = 0;
   out_637472039154741501[27] = 0;
   out_637472039154741501[28] = 1;
   out_637472039154741501[29] = 0;
   out_637472039154741501[30] = 0;
   out_637472039154741501[31] = 0;
   out_637472039154741501[32] = 0;
   out_637472039154741501[33] = 0;
   out_637472039154741501[34] = 0;
   out_637472039154741501[35] = 0;
   out_637472039154741501[36] = 0;
   out_637472039154741501[37] = 0;
   out_637472039154741501[38] = 0;
   out_637472039154741501[39] = 0;
   out_637472039154741501[40] = 0;
   out_637472039154741501[41] = 0;
   out_637472039154741501[42] = 0;
   out_637472039154741501[43] = 0;
   out_637472039154741501[44] = 1;
   out_637472039154741501[45] = 0;
   out_637472039154741501[46] = 0;
   out_637472039154741501[47] = 1;
   out_637472039154741501[48] = 0;
   out_637472039154741501[49] = 0;
   out_637472039154741501[50] = 0;
   out_637472039154741501[51] = 0;
   out_637472039154741501[52] = 0;
   out_637472039154741501[53] = 0;
}
void h_10(double *state, double *unused, double *out_5896232866039695568) {
   out_5896232866039695568[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5896232866039695568[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5896232866039695568[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6470002192212990620) {
   out_6470002192212990620[0] = 0;
   out_6470002192212990620[1] = 9.8100000000000005*cos(state[1]);
   out_6470002192212990620[2] = 0;
   out_6470002192212990620[3] = 0;
   out_6470002192212990620[4] = -state[8];
   out_6470002192212990620[5] = state[7];
   out_6470002192212990620[6] = 0;
   out_6470002192212990620[7] = state[5];
   out_6470002192212990620[8] = -state[4];
   out_6470002192212990620[9] = 0;
   out_6470002192212990620[10] = 0;
   out_6470002192212990620[11] = 0;
   out_6470002192212990620[12] = 1;
   out_6470002192212990620[13] = 0;
   out_6470002192212990620[14] = 0;
   out_6470002192212990620[15] = 1;
   out_6470002192212990620[16] = 0;
   out_6470002192212990620[17] = 0;
   out_6470002192212990620[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6470002192212990620[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6470002192212990620[20] = 0;
   out_6470002192212990620[21] = state[8];
   out_6470002192212990620[22] = 0;
   out_6470002192212990620[23] = -state[6];
   out_6470002192212990620[24] = -state[5];
   out_6470002192212990620[25] = 0;
   out_6470002192212990620[26] = state[3];
   out_6470002192212990620[27] = 0;
   out_6470002192212990620[28] = 0;
   out_6470002192212990620[29] = 0;
   out_6470002192212990620[30] = 0;
   out_6470002192212990620[31] = 1;
   out_6470002192212990620[32] = 0;
   out_6470002192212990620[33] = 0;
   out_6470002192212990620[34] = 1;
   out_6470002192212990620[35] = 0;
   out_6470002192212990620[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6470002192212990620[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6470002192212990620[38] = 0;
   out_6470002192212990620[39] = -state[7];
   out_6470002192212990620[40] = state[6];
   out_6470002192212990620[41] = 0;
   out_6470002192212990620[42] = state[4];
   out_6470002192212990620[43] = -state[3];
   out_6470002192212990620[44] = 0;
   out_6470002192212990620[45] = 0;
   out_6470002192212990620[46] = 0;
   out_6470002192212990620[47] = 0;
   out_6470002192212990620[48] = 0;
   out_6470002192212990620[49] = 0;
   out_6470002192212990620[50] = 1;
   out_6470002192212990620[51] = 0;
   out_6470002192212990620[52] = 0;
   out_6470002192212990620[53] = 1;
}
void h_13(double *state, double *unused, double *out_5564060116117934481) {
   out_5564060116117934481[0] = state[3];
   out_5564060116117934481[1] = state[4];
   out_5564060116117934481[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2574801786177591300) {
   out_2574801786177591300[0] = 0;
   out_2574801786177591300[1] = 0;
   out_2574801786177591300[2] = 0;
   out_2574801786177591300[3] = 1;
   out_2574801786177591300[4] = 0;
   out_2574801786177591300[5] = 0;
   out_2574801786177591300[6] = 0;
   out_2574801786177591300[7] = 0;
   out_2574801786177591300[8] = 0;
   out_2574801786177591300[9] = 0;
   out_2574801786177591300[10] = 0;
   out_2574801786177591300[11] = 0;
   out_2574801786177591300[12] = 0;
   out_2574801786177591300[13] = 0;
   out_2574801786177591300[14] = 0;
   out_2574801786177591300[15] = 0;
   out_2574801786177591300[16] = 0;
   out_2574801786177591300[17] = 0;
   out_2574801786177591300[18] = 0;
   out_2574801786177591300[19] = 0;
   out_2574801786177591300[20] = 0;
   out_2574801786177591300[21] = 0;
   out_2574801786177591300[22] = 1;
   out_2574801786177591300[23] = 0;
   out_2574801786177591300[24] = 0;
   out_2574801786177591300[25] = 0;
   out_2574801786177591300[26] = 0;
   out_2574801786177591300[27] = 0;
   out_2574801786177591300[28] = 0;
   out_2574801786177591300[29] = 0;
   out_2574801786177591300[30] = 0;
   out_2574801786177591300[31] = 0;
   out_2574801786177591300[32] = 0;
   out_2574801786177591300[33] = 0;
   out_2574801786177591300[34] = 0;
   out_2574801786177591300[35] = 0;
   out_2574801786177591300[36] = 0;
   out_2574801786177591300[37] = 0;
   out_2574801786177591300[38] = 0;
   out_2574801786177591300[39] = 0;
   out_2574801786177591300[40] = 0;
   out_2574801786177591300[41] = 1;
   out_2574801786177591300[42] = 0;
   out_2574801786177591300[43] = 0;
   out_2574801786177591300[44] = 0;
   out_2574801786177591300[45] = 0;
   out_2574801786177591300[46] = 0;
   out_2574801786177591300[47] = 0;
   out_2574801786177591300[48] = 0;
   out_2574801786177591300[49] = 0;
   out_2574801786177591300[50] = 0;
   out_2574801786177591300[51] = 0;
   out_2574801786177591300[52] = 0;
   out_2574801786177591300[53] = 0;
}
void h_14(double *state, double *unused, double *out_9129729305013669813) {
   out_9129729305013669813[0] = state[6];
   out_9129729305013669813[1] = state[7];
   out_9129729305013669813[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3325768817184743028) {
   out_3325768817184743028[0] = 0;
   out_3325768817184743028[1] = 0;
   out_3325768817184743028[2] = 0;
   out_3325768817184743028[3] = 0;
   out_3325768817184743028[4] = 0;
   out_3325768817184743028[5] = 0;
   out_3325768817184743028[6] = 1;
   out_3325768817184743028[7] = 0;
   out_3325768817184743028[8] = 0;
   out_3325768817184743028[9] = 0;
   out_3325768817184743028[10] = 0;
   out_3325768817184743028[11] = 0;
   out_3325768817184743028[12] = 0;
   out_3325768817184743028[13] = 0;
   out_3325768817184743028[14] = 0;
   out_3325768817184743028[15] = 0;
   out_3325768817184743028[16] = 0;
   out_3325768817184743028[17] = 0;
   out_3325768817184743028[18] = 0;
   out_3325768817184743028[19] = 0;
   out_3325768817184743028[20] = 0;
   out_3325768817184743028[21] = 0;
   out_3325768817184743028[22] = 0;
   out_3325768817184743028[23] = 0;
   out_3325768817184743028[24] = 0;
   out_3325768817184743028[25] = 1;
   out_3325768817184743028[26] = 0;
   out_3325768817184743028[27] = 0;
   out_3325768817184743028[28] = 0;
   out_3325768817184743028[29] = 0;
   out_3325768817184743028[30] = 0;
   out_3325768817184743028[31] = 0;
   out_3325768817184743028[32] = 0;
   out_3325768817184743028[33] = 0;
   out_3325768817184743028[34] = 0;
   out_3325768817184743028[35] = 0;
   out_3325768817184743028[36] = 0;
   out_3325768817184743028[37] = 0;
   out_3325768817184743028[38] = 0;
   out_3325768817184743028[39] = 0;
   out_3325768817184743028[40] = 0;
   out_3325768817184743028[41] = 0;
   out_3325768817184743028[42] = 0;
   out_3325768817184743028[43] = 0;
   out_3325768817184743028[44] = 1;
   out_3325768817184743028[45] = 0;
   out_3325768817184743028[46] = 0;
   out_3325768817184743028[47] = 0;
   out_3325768817184743028[48] = 0;
   out_3325768817184743028[49] = 0;
   out_3325768817184743028[50] = 0;
   out_3325768817184743028[51] = 0;
   out_3325768817184743028[52] = 0;
   out_3325768817184743028[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_842964569186968919) {
  err_fun(nom_x, delta_x, out_842964569186968919);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7637995249051351300) {
  inv_err_fun(nom_x, true_x, out_7637995249051351300);
}
void pose_H_mod_fun(double *state, double *out_8306889626903079841) {
  H_mod_fun(state, out_8306889626903079841);
}
void pose_f_fun(double *state, double dt, double *out_5013225008344736149) {
  f_fun(state,  dt, out_5013225008344736149);
}
void pose_F_fun(double *state, double dt, double *out_8990818239492707931) {
  F_fun(state,  dt, out_8990818239492707931);
}
void pose_h_4(double *state, double *unused, double *out_4553534383789500912) {
  h_4(state, unused, out_4553534383789500912);
}
void pose_H_4(double *state, double *unused, double *out_637472039154741501) {
  H_4(state, unused, out_637472039154741501);
}
void pose_h_10(double *state, double *unused, double *out_5896232866039695568) {
  h_10(state, unused, out_5896232866039695568);
}
void pose_H_10(double *state, double *unused, double *out_6470002192212990620) {
  H_10(state, unused, out_6470002192212990620);
}
void pose_h_13(double *state, double *unused, double *out_5564060116117934481) {
  h_13(state, unused, out_5564060116117934481);
}
void pose_H_13(double *state, double *unused, double *out_2574801786177591300) {
  H_13(state, unused, out_2574801786177591300);
}
void pose_h_14(double *state, double *unused, double *out_9129729305013669813) {
  h_14(state, unused, out_9129729305013669813);
}
void pose_H_14(double *state, double *unused, double *out_3325768817184743028) {
  H_14(state, unused, out_3325768817184743028);
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
