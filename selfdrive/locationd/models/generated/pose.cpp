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
void err_fun(double *nom_x, double *delta_x, double *out_9183838211698085113) {
   out_9183838211698085113[0] = delta_x[0] + nom_x[0];
   out_9183838211698085113[1] = delta_x[1] + nom_x[1];
   out_9183838211698085113[2] = delta_x[2] + nom_x[2];
   out_9183838211698085113[3] = delta_x[3] + nom_x[3];
   out_9183838211698085113[4] = delta_x[4] + nom_x[4];
   out_9183838211698085113[5] = delta_x[5] + nom_x[5];
   out_9183838211698085113[6] = delta_x[6] + nom_x[6];
   out_9183838211698085113[7] = delta_x[7] + nom_x[7];
   out_9183838211698085113[8] = delta_x[8] + nom_x[8];
   out_9183838211698085113[9] = delta_x[9] + nom_x[9];
   out_9183838211698085113[10] = delta_x[10] + nom_x[10];
   out_9183838211698085113[11] = delta_x[11] + nom_x[11];
   out_9183838211698085113[12] = delta_x[12] + nom_x[12];
   out_9183838211698085113[13] = delta_x[13] + nom_x[13];
   out_9183838211698085113[14] = delta_x[14] + nom_x[14];
   out_9183838211698085113[15] = delta_x[15] + nom_x[15];
   out_9183838211698085113[16] = delta_x[16] + nom_x[16];
   out_9183838211698085113[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7880707634176237912) {
   out_7880707634176237912[0] = -nom_x[0] + true_x[0];
   out_7880707634176237912[1] = -nom_x[1] + true_x[1];
   out_7880707634176237912[2] = -nom_x[2] + true_x[2];
   out_7880707634176237912[3] = -nom_x[3] + true_x[3];
   out_7880707634176237912[4] = -nom_x[4] + true_x[4];
   out_7880707634176237912[5] = -nom_x[5] + true_x[5];
   out_7880707634176237912[6] = -nom_x[6] + true_x[6];
   out_7880707634176237912[7] = -nom_x[7] + true_x[7];
   out_7880707634176237912[8] = -nom_x[8] + true_x[8];
   out_7880707634176237912[9] = -nom_x[9] + true_x[9];
   out_7880707634176237912[10] = -nom_x[10] + true_x[10];
   out_7880707634176237912[11] = -nom_x[11] + true_x[11];
   out_7880707634176237912[12] = -nom_x[12] + true_x[12];
   out_7880707634176237912[13] = -nom_x[13] + true_x[13];
   out_7880707634176237912[14] = -nom_x[14] + true_x[14];
   out_7880707634176237912[15] = -nom_x[15] + true_x[15];
   out_7880707634176237912[16] = -nom_x[16] + true_x[16];
   out_7880707634176237912[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4757006295873358620) {
   out_4757006295873358620[0] = 1.0;
   out_4757006295873358620[1] = 0.0;
   out_4757006295873358620[2] = 0.0;
   out_4757006295873358620[3] = 0.0;
   out_4757006295873358620[4] = 0.0;
   out_4757006295873358620[5] = 0.0;
   out_4757006295873358620[6] = 0.0;
   out_4757006295873358620[7] = 0.0;
   out_4757006295873358620[8] = 0.0;
   out_4757006295873358620[9] = 0.0;
   out_4757006295873358620[10] = 0.0;
   out_4757006295873358620[11] = 0.0;
   out_4757006295873358620[12] = 0.0;
   out_4757006295873358620[13] = 0.0;
   out_4757006295873358620[14] = 0.0;
   out_4757006295873358620[15] = 0.0;
   out_4757006295873358620[16] = 0.0;
   out_4757006295873358620[17] = 0.0;
   out_4757006295873358620[18] = 0.0;
   out_4757006295873358620[19] = 1.0;
   out_4757006295873358620[20] = 0.0;
   out_4757006295873358620[21] = 0.0;
   out_4757006295873358620[22] = 0.0;
   out_4757006295873358620[23] = 0.0;
   out_4757006295873358620[24] = 0.0;
   out_4757006295873358620[25] = 0.0;
   out_4757006295873358620[26] = 0.0;
   out_4757006295873358620[27] = 0.0;
   out_4757006295873358620[28] = 0.0;
   out_4757006295873358620[29] = 0.0;
   out_4757006295873358620[30] = 0.0;
   out_4757006295873358620[31] = 0.0;
   out_4757006295873358620[32] = 0.0;
   out_4757006295873358620[33] = 0.0;
   out_4757006295873358620[34] = 0.0;
   out_4757006295873358620[35] = 0.0;
   out_4757006295873358620[36] = 0.0;
   out_4757006295873358620[37] = 0.0;
   out_4757006295873358620[38] = 1.0;
   out_4757006295873358620[39] = 0.0;
   out_4757006295873358620[40] = 0.0;
   out_4757006295873358620[41] = 0.0;
   out_4757006295873358620[42] = 0.0;
   out_4757006295873358620[43] = 0.0;
   out_4757006295873358620[44] = 0.0;
   out_4757006295873358620[45] = 0.0;
   out_4757006295873358620[46] = 0.0;
   out_4757006295873358620[47] = 0.0;
   out_4757006295873358620[48] = 0.0;
   out_4757006295873358620[49] = 0.0;
   out_4757006295873358620[50] = 0.0;
   out_4757006295873358620[51] = 0.0;
   out_4757006295873358620[52] = 0.0;
   out_4757006295873358620[53] = 0.0;
   out_4757006295873358620[54] = 0.0;
   out_4757006295873358620[55] = 0.0;
   out_4757006295873358620[56] = 0.0;
   out_4757006295873358620[57] = 1.0;
   out_4757006295873358620[58] = 0.0;
   out_4757006295873358620[59] = 0.0;
   out_4757006295873358620[60] = 0.0;
   out_4757006295873358620[61] = 0.0;
   out_4757006295873358620[62] = 0.0;
   out_4757006295873358620[63] = 0.0;
   out_4757006295873358620[64] = 0.0;
   out_4757006295873358620[65] = 0.0;
   out_4757006295873358620[66] = 0.0;
   out_4757006295873358620[67] = 0.0;
   out_4757006295873358620[68] = 0.0;
   out_4757006295873358620[69] = 0.0;
   out_4757006295873358620[70] = 0.0;
   out_4757006295873358620[71] = 0.0;
   out_4757006295873358620[72] = 0.0;
   out_4757006295873358620[73] = 0.0;
   out_4757006295873358620[74] = 0.0;
   out_4757006295873358620[75] = 0.0;
   out_4757006295873358620[76] = 1.0;
   out_4757006295873358620[77] = 0.0;
   out_4757006295873358620[78] = 0.0;
   out_4757006295873358620[79] = 0.0;
   out_4757006295873358620[80] = 0.0;
   out_4757006295873358620[81] = 0.0;
   out_4757006295873358620[82] = 0.0;
   out_4757006295873358620[83] = 0.0;
   out_4757006295873358620[84] = 0.0;
   out_4757006295873358620[85] = 0.0;
   out_4757006295873358620[86] = 0.0;
   out_4757006295873358620[87] = 0.0;
   out_4757006295873358620[88] = 0.0;
   out_4757006295873358620[89] = 0.0;
   out_4757006295873358620[90] = 0.0;
   out_4757006295873358620[91] = 0.0;
   out_4757006295873358620[92] = 0.0;
   out_4757006295873358620[93] = 0.0;
   out_4757006295873358620[94] = 0.0;
   out_4757006295873358620[95] = 1.0;
   out_4757006295873358620[96] = 0.0;
   out_4757006295873358620[97] = 0.0;
   out_4757006295873358620[98] = 0.0;
   out_4757006295873358620[99] = 0.0;
   out_4757006295873358620[100] = 0.0;
   out_4757006295873358620[101] = 0.0;
   out_4757006295873358620[102] = 0.0;
   out_4757006295873358620[103] = 0.0;
   out_4757006295873358620[104] = 0.0;
   out_4757006295873358620[105] = 0.0;
   out_4757006295873358620[106] = 0.0;
   out_4757006295873358620[107] = 0.0;
   out_4757006295873358620[108] = 0.0;
   out_4757006295873358620[109] = 0.0;
   out_4757006295873358620[110] = 0.0;
   out_4757006295873358620[111] = 0.0;
   out_4757006295873358620[112] = 0.0;
   out_4757006295873358620[113] = 0.0;
   out_4757006295873358620[114] = 1.0;
   out_4757006295873358620[115] = 0.0;
   out_4757006295873358620[116] = 0.0;
   out_4757006295873358620[117] = 0.0;
   out_4757006295873358620[118] = 0.0;
   out_4757006295873358620[119] = 0.0;
   out_4757006295873358620[120] = 0.0;
   out_4757006295873358620[121] = 0.0;
   out_4757006295873358620[122] = 0.0;
   out_4757006295873358620[123] = 0.0;
   out_4757006295873358620[124] = 0.0;
   out_4757006295873358620[125] = 0.0;
   out_4757006295873358620[126] = 0.0;
   out_4757006295873358620[127] = 0.0;
   out_4757006295873358620[128] = 0.0;
   out_4757006295873358620[129] = 0.0;
   out_4757006295873358620[130] = 0.0;
   out_4757006295873358620[131] = 0.0;
   out_4757006295873358620[132] = 0.0;
   out_4757006295873358620[133] = 1.0;
   out_4757006295873358620[134] = 0.0;
   out_4757006295873358620[135] = 0.0;
   out_4757006295873358620[136] = 0.0;
   out_4757006295873358620[137] = 0.0;
   out_4757006295873358620[138] = 0.0;
   out_4757006295873358620[139] = 0.0;
   out_4757006295873358620[140] = 0.0;
   out_4757006295873358620[141] = 0.0;
   out_4757006295873358620[142] = 0.0;
   out_4757006295873358620[143] = 0.0;
   out_4757006295873358620[144] = 0.0;
   out_4757006295873358620[145] = 0.0;
   out_4757006295873358620[146] = 0.0;
   out_4757006295873358620[147] = 0.0;
   out_4757006295873358620[148] = 0.0;
   out_4757006295873358620[149] = 0.0;
   out_4757006295873358620[150] = 0.0;
   out_4757006295873358620[151] = 0.0;
   out_4757006295873358620[152] = 1.0;
   out_4757006295873358620[153] = 0.0;
   out_4757006295873358620[154] = 0.0;
   out_4757006295873358620[155] = 0.0;
   out_4757006295873358620[156] = 0.0;
   out_4757006295873358620[157] = 0.0;
   out_4757006295873358620[158] = 0.0;
   out_4757006295873358620[159] = 0.0;
   out_4757006295873358620[160] = 0.0;
   out_4757006295873358620[161] = 0.0;
   out_4757006295873358620[162] = 0.0;
   out_4757006295873358620[163] = 0.0;
   out_4757006295873358620[164] = 0.0;
   out_4757006295873358620[165] = 0.0;
   out_4757006295873358620[166] = 0.0;
   out_4757006295873358620[167] = 0.0;
   out_4757006295873358620[168] = 0.0;
   out_4757006295873358620[169] = 0.0;
   out_4757006295873358620[170] = 0.0;
   out_4757006295873358620[171] = 1.0;
   out_4757006295873358620[172] = 0.0;
   out_4757006295873358620[173] = 0.0;
   out_4757006295873358620[174] = 0.0;
   out_4757006295873358620[175] = 0.0;
   out_4757006295873358620[176] = 0.0;
   out_4757006295873358620[177] = 0.0;
   out_4757006295873358620[178] = 0.0;
   out_4757006295873358620[179] = 0.0;
   out_4757006295873358620[180] = 0.0;
   out_4757006295873358620[181] = 0.0;
   out_4757006295873358620[182] = 0.0;
   out_4757006295873358620[183] = 0.0;
   out_4757006295873358620[184] = 0.0;
   out_4757006295873358620[185] = 0.0;
   out_4757006295873358620[186] = 0.0;
   out_4757006295873358620[187] = 0.0;
   out_4757006295873358620[188] = 0.0;
   out_4757006295873358620[189] = 0.0;
   out_4757006295873358620[190] = 1.0;
   out_4757006295873358620[191] = 0.0;
   out_4757006295873358620[192] = 0.0;
   out_4757006295873358620[193] = 0.0;
   out_4757006295873358620[194] = 0.0;
   out_4757006295873358620[195] = 0.0;
   out_4757006295873358620[196] = 0.0;
   out_4757006295873358620[197] = 0.0;
   out_4757006295873358620[198] = 0.0;
   out_4757006295873358620[199] = 0.0;
   out_4757006295873358620[200] = 0.0;
   out_4757006295873358620[201] = 0.0;
   out_4757006295873358620[202] = 0.0;
   out_4757006295873358620[203] = 0.0;
   out_4757006295873358620[204] = 0.0;
   out_4757006295873358620[205] = 0.0;
   out_4757006295873358620[206] = 0.0;
   out_4757006295873358620[207] = 0.0;
   out_4757006295873358620[208] = 0.0;
   out_4757006295873358620[209] = 1.0;
   out_4757006295873358620[210] = 0.0;
   out_4757006295873358620[211] = 0.0;
   out_4757006295873358620[212] = 0.0;
   out_4757006295873358620[213] = 0.0;
   out_4757006295873358620[214] = 0.0;
   out_4757006295873358620[215] = 0.0;
   out_4757006295873358620[216] = 0.0;
   out_4757006295873358620[217] = 0.0;
   out_4757006295873358620[218] = 0.0;
   out_4757006295873358620[219] = 0.0;
   out_4757006295873358620[220] = 0.0;
   out_4757006295873358620[221] = 0.0;
   out_4757006295873358620[222] = 0.0;
   out_4757006295873358620[223] = 0.0;
   out_4757006295873358620[224] = 0.0;
   out_4757006295873358620[225] = 0.0;
   out_4757006295873358620[226] = 0.0;
   out_4757006295873358620[227] = 0.0;
   out_4757006295873358620[228] = 1.0;
   out_4757006295873358620[229] = 0.0;
   out_4757006295873358620[230] = 0.0;
   out_4757006295873358620[231] = 0.0;
   out_4757006295873358620[232] = 0.0;
   out_4757006295873358620[233] = 0.0;
   out_4757006295873358620[234] = 0.0;
   out_4757006295873358620[235] = 0.0;
   out_4757006295873358620[236] = 0.0;
   out_4757006295873358620[237] = 0.0;
   out_4757006295873358620[238] = 0.0;
   out_4757006295873358620[239] = 0.0;
   out_4757006295873358620[240] = 0.0;
   out_4757006295873358620[241] = 0.0;
   out_4757006295873358620[242] = 0.0;
   out_4757006295873358620[243] = 0.0;
   out_4757006295873358620[244] = 0.0;
   out_4757006295873358620[245] = 0.0;
   out_4757006295873358620[246] = 0.0;
   out_4757006295873358620[247] = 1.0;
   out_4757006295873358620[248] = 0.0;
   out_4757006295873358620[249] = 0.0;
   out_4757006295873358620[250] = 0.0;
   out_4757006295873358620[251] = 0.0;
   out_4757006295873358620[252] = 0.0;
   out_4757006295873358620[253] = 0.0;
   out_4757006295873358620[254] = 0.0;
   out_4757006295873358620[255] = 0.0;
   out_4757006295873358620[256] = 0.0;
   out_4757006295873358620[257] = 0.0;
   out_4757006295873358620[258] = 0.0;
   out_4757006295873358620[259] = 0.0;
   out_4757006295873358620[260] = 0.0;
   out_4757006295873358620[261] = 0.0;
   out_4757006295873358620[262] = 0.0;
   out_4757006295873358620[263] = 0.0;
   out_4757006295873358620[264] = 0.0;
   out_4757006295873358620[265] = 0.0;
   out_4757006295873358620[266] = 1.0;
   out_4757006295873358620[267] = 0.0;
   out_4757006295873358620[268] = 0.0;
   out_4757006295873358620[269] = 0.0;
   out_4757006295873358620[270] = 0.0;
   out_4757006295873358620[271] = 0.0;
   out_4757006295873358620[272] = 0.0;
   out_4757006295873358620[273] = 0.0;
   out_4757006295873358620[274] = 0.0;
   out_4757006295873358620[275] = 0.0;
   out_4757006295873358620[276] = 0.0;
   out_4757006295873358620[277] = 0.0;
   out_4757006295873358620[278] = 0.0;
   out_4757006295873358620[279] = 0.0;
   out_4757006295873358620[280] = 0.0;
   out_4757006295873358620[281] = 0.0;
   out_4757006295873358620[282] = 0.0;
   out_4757006295873358620[283] = 0.0;
   out_4757006295873358620[284] = 0.0;
   out_4757006295873358620[285] = 1.0;
   out_4757006295873358620[286] = 0.0;
   out_4757006295873358620[287] = 0.0;
   out_4757006295873358620[288] = 0.0;
   out_4757006295873358620[289] = 0.0;
   out_4757006295873358620[290] = 0.0;
   out_4757006295873358620[291] = 0.0;
   out_4757006295873358620[292] = 0.0;
   out_4757006295873358620[293] = 0.0;
   out_4757006295873358620[294] = 0.0;
   out_4757006295873358620[295] = 0.0;
   out_4757006295873358620[296] = 0.0;
   out_4757006295873358620[297] = 0.0;
   out_4757006295873358620[298] = 0.0;
   out_4757006295873358620[299] = 0.0;
   out_4757006295873358620[300] = 0.0;
   out_4757006295873358620[301] = 0.0;
   out_4757006295873358620[302] = 0.0;
   out_4757006295873358620[303] = 0.0;
   out_4757006295873358620[304] = 1.0;
   out_4757006295873358620[305] = 0.0;
   out_4757006295873358620[306] = 0.0;
   out_4757006295873358620[307] = 0.0;
   out_4757006295873358620[308] = 0.0;
   out_4757006295873358620[309] = 0.0;
   out_4757006295873358620[310] = 0.0;
   out_4757006295873358620[311] = 0.0;
   out_4757006295873358620[312] = 0.0;
   out_4757006295873358620[313] = 0.0;
   out_4757006295873358620[314] = 0.0;
   out_4757006295873358620[315] = 0.0;
   out_4757006295873358620[316] = 0.0;
   out_4757006295873358620[317] = 0.0;
   out_4757006295873358620[318] = 0.0;
   out_4757006295873358620[319] = 0.0;
   out_4757006295873358620[320] = 0.0;
   out_4757006295873358620[321] = 0.0;
   out_4757006295873358620[322] = 0.0;
   out_4757006295873358620[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_9118920386528411329) {
   out_9118920386528411329[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_9118920386528411329[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_9118920386528411329[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_9118920386528411329[3] = dt*state[12] + state[3];
   out_9118920386528411329[4] = dt*state[13] + state[4];
   out_9118920386528411329[5] = dt*state[14] + state[5];
   out_9118920386528411329[6] = state[6];
   out_9118920386528411329[7] = state[7];
   out_9118920386528411329[8] = state[8];
   out_9118920386528411329[9] = state[9];
   out_9118920386528411329[10] = state[10];
   out_9118920386528411329[11] = state[11];
   out_9118920386528411329[12] = state[12];
   out_9118920386528411329[13] = state[13];
   out_9118920386528411329[14] = state[14];
   out_9118920386528411329[15] = state[15];
   out_9118920386528411329[16] = state[16];
   out_9118920386528411329[17] = state[17];
}
void F_fun(double *state, double dt, double *out_388070008261359487) {
   out_388070008261359487[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_388070008261359487[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_388070008261359487[2] = 0;
   out_388070008261359487[3] = 0;
   out_388070008261359487[4] = 0;
   out_388070008261359487[5] = 0;
   out_388070008261359487[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_388070008261359487[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_388070008261359487[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_388070008261359487[9] = 0;
   out_388070008261359487[10] = 0;
   out_388070008261359487[11] = 0;
   out_388070008261359487[12] = 0;
   out_388070008261359487[13] = 0;
   out_388070008261359487[14] = 0;
   out_388070008261359487[15] = 0;
   out_388070008261359487[16] = 0;
   out_388070008261359487[17] = 0;
   out_388070008261359487[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_388070008261359487[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_388070008261359487[20] = 0;
   out_388070008261359487[21] = 0;
   out_388070008261359487[22] = 0;
   out_388070008261359487[23] = 0;
   out_388070008261359487[24] = 0;
   out_388070008261359487[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_388070008261359487[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_388070008261359487[27] = 0;
   out_388070008261359487[28] = 0;
   out_388070008261359487[29] = 0;
   out_388070008261359487[30] = 0;
   out_388070008261359487[31] = 0;
   out_388070008261359487[32] = 0;
   out_388070008261359487[33] = 0;
   out_388070008261359487[34] = 0;
   out_388070008261359487[35] = 0;
   out_388070008261359487[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_388070008261359487[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_388070008261359487[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_388070008261359487[39] = 0;
   out_388070008261359487[40] = 0;
   out_388070008261359487[41] = 0;
   out_388070008261359487[42] = 0;
   out_388070008261359487[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_388070008261359487[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_388070008261359487[45] = 0;
   out_388070008261359487[46] = 0;
   out_388070008261359487[47] = 0;
   out_388070008261359487[48] = 0;
   out_388070008261359487[49] = 0;
   out_388070008261359487[50] = 0;
   out_388070008261359487[51] = 0;
   out_388070008261359487[52] = 0;
   out_388070008261359487[53] = 0;
   out_388070008261359487[54] = 0;
   out_388070008261359487[55] = 0;
   out_388070008261359487[56] = 0;
   out_388070008261359487[57] = 1;
   out_388070008261359487[58] = 0;
   out_388070008261359487[59] = 0;
   out_388070008261359487[60] = 0;
   out_388070008261359487[61] = 0;
   out_388070008261359487[62] = 0;
   out_388070008261359487[63] = 0;
   out_388070008261359487[64] = 0;
   out_388070008261359487[65] = 0;
   out_388070008261359487[66] = dt;
   out_388070008261359487[67] = 0;
   out_388070008261359487[68] = 0;
   out_388070008261359487[69] = 0;
   out_388070008261359487[70] = 0;
   out_388070008261359487[71] = 0;
   out_388070008261359487[72] = 0;
   out_388070008261359487[73] = 0;
   out_388070008261359487[74] = 0;
   out_388070008261359487[75] = 0;
   out_388070008261359487[76] = 1;
   out_388070008261359487[77] = 0;
   out_388070008261359487[78] = 0;
   out_388070008261359487[79] = 0;
   out_388070008261359487[80] = 0;
   out_388070008261359487[81] = 0;
   out_388070008261359487[82] = 0;
   out_388070008261359487[83] = 0;
   out_388070008261359487[84] = 0;
   out_388070008261359487[85] = dt;
   out_388070008261359487[86] = 0;
   out_388070008261359487[87] = 0;
   out_388070008261359487[88] = 0;
   out_388070008261359487[89] = 0;
   out_388070008261359487[90] = 0;
   out_388070008261359487[91] = 0;
   out_388070008261359487[92] = 0;
   out_388070008261359487[93] = 0;
   out_388070008261359487[94] = 0;
   out_388070008261359487[95] = 1;
   out_388070008261359487[96] = 0;
   out_388070008261359487[97] = 0;
   out_388070008261359487[98] = 0;
   out_388070008261359487[99] = 0;
   out_388070008261359487[100] = 0;
   out_388070008261359487[101] = 0;
   out_388070008261359487[102] = 0;
   out_388070008261359487[103] = 0;
   out_388070008261359487[104] = dt;
   out_388070008261359487[105] = 0;
   out_388070008261359487[106] = 0;
   out_388070008261359487[107] = 0;
   out_388070008261359487[108] = 0;
   out_388070008261359487[109] = 0;
   out_388070008261359487[110] = 0;
   out_388070008261359487[111] = 0;
   out_388070008261359487[112] = 0;
   out_388070008261359487[113] = 0;
   out_388070008261359487[114] = 1;
   out_388070008261359487[115] = 0;
   out_388070008261359487[116] = 0;
   out_388070008261359487[117] = 0;
   out_388070008261359487[118] = 0;
   out_388070008261359487[119] = 0;
   out_388070008261359487[120] = 0;
   out_388070008261359487[121] = 0;
   out_388070008261359487[122] = 0;
   out_388070008261359487[123] = 0;
   out_388070008261359487[124] = 0;
   out_388070008261359487[125] = 0;
   out_388070008261359487[126] = 0;
   out_388070008261359487[127] = 0;
   out_388070008261359487[128] = 0;
   out_388070008261359487[129] = 0;
   out_388070008261359487[130] = 0;
   out_388070008261359487[131] = 0;
   out_388070008261359487[132] = 0;
   out_388070008261359487[133] = 1;
   out_388070008261359487[134] = 0;
   out_388070008261359487[135] = 0;
   out_388070008261359487[136] = 0;
   out_388070008261359487[137] = 0;
   out_388070008261359487[138] = 0;
   out_388070008261359487[139] = 0;
   out_388070008261359487[140] = 0;
   out_388070008261359487[141] = 0;
   out_388070008261359487[142] = 0;
   out_388070008261359487[143] = 0;
   out_388070008261359487[144] = 0;
   out_388070008261359487[145] = 0;
   out_388070008261359487[146] = 0;
   out_388070008261359487[147] = 0;
   out_388070008261359487[148] = 0;
   out_388070008261359487[149] = 0;
   out_388070008261359487[150] = 0;
   out_388070008261359487[151] = 0;
   out_388070008261359487[152] = 1;
   out_388070008261359487[153] = 0;
   out_388070008261359487[154] = 0;
   out_388070008261359487[155] = 0;
   out_388070008261359487[156] = 0;
   out_388070008261359487[157] = 0;
   out_388070008261359487[158] = 0;
   out_388070008261359487[159] = 0;
   out_388070008261359487[160] = 0;
   out_388070008261359487[161] = 0;
   out_388070008261359487[162] = 0;
   out_388070008261359487[163] = 0;
   out_388070008261359487[164] = 0;
   out_388070008261359487[165] = 0;
   out_388070008261359487[166] = 0;
   out_388070008261359487[167] = 0;
   out_388070008261359487[168] = 0;
   out_388070008261359487[169] = 0;
   out_388070008261359487[170] = 0;
   out_388070008261359487[171] = 1;
   out_388070008261359487[172] = 0;
   out_388070008261359487[173] = 0;
   out_388070008261359487[174] = 0;
   out_388070008261359487[175] = 0;
   out_388070008261359487[176] = 0;
   out_388070008261359487[177] = 0;
   out_388070008261359487[178] = 0;
   out_388070008261359487[179] = 0;
   out_388070008261359487[180] = 0;
   out_388070008261359487[181] = 0;
   out_388070008261359487[182] = 0;
   out_388070008261359487[183] = 0;
   out_388070008261359487[184] = 0;
   out_388070008261359487[185] = 0;
   out_388070008261359487[186] = 0;
   out_388070008261359487[187] = 0;
   out_388070008261359487[188] = 0;
   out_388070008261359487[189] = 0;
   out_388070008261359487[190] = 1;
   out_388070008261359487[191] = 0;
   out_388070008261359487[192] = 0;
   out_388070008261359487[193] = 0;
   out_388070008261359487[194] = 0;
   out_388070008261359487[195] = 0;
   out_388070008261359487[196] = 0;
   out_388070008261359487[197] = 0;
   out_388070008261359487[198] = 0;
   out_388070008261359487[199] = 0;
   out_388070008261359487[200] = 0;
   out_388070008261359487[201] = 0;
   out_388070008261359487[202] = 0;
   out_388070008261359487[203] = 0;
   out_388070008261359487[204] = 0;
   out_388070008261359487[205] = 0;
   out_388070008261359487[206] = 0;
   out_388070008261359487[207] = 0;
   out_388070008261359487[208] = 0;
   out_388070008261359487[209] = 1;
   out_388070008261359487[210] = 0;
   out_388070008261359487[211] = 0;
   out_388070008261359487[212] = 0;
   out_388070008261359487[213] = 0;
   out_388070008261359487[214] = 0;
   out_388070008261359487[215] = 0;
   out_388070008261359487[216] = 0;
   out_388070008261359487[217] = 0;
   out_388070008261359487[218] = 0;
   out_388070008261359487[219] = 0;
   out_388070008261359487[220] = 0;
   out_388070008261359487[221] = 0;
   out_388070008261359487[222] = 0;
   out_388070008261359487[223] = 0;
   out_388070008261359487[224] = 0;
   out_388070008261359487[225] = 0;
   out_388070008261359487[226] = 0;
   out_388070008261359487[227] = 0;
   out_388070008261359487[228] = 1;
   out_388070008261359487[229] = 0;
   out_388070008261359487[230] = 0;
   out_388070008261359487[231] = 0;
   out_388070008261359487[232] = 0;
   out_388070008261359487[233] = 0;
   out_388070008261359487[234] = 0;
   out_388070008261359487[235] = 0;
   out_388070008261359487[236] = 0;
   out_388070008261359487[237] = 0;
   out_388070008261359487[238] = 0;
   out_388070008261359487[239] = 0;
   out_388070008261359487[240] = 0;
   out_388070008261359487[241] = 0;
   out_388070008261359487[242] = 0;
   out_388070008261359487[243] = 0;
   out_388070008261359487[244] = 0;
   out_388070008261359487[245] = 0;
   out_388070008261359487[246] = 0;
   out_388070008261359487[247] = 1;
   out_388070008261359487[248] = 0;
   out_388070008261359487[249] = 0;
   out_388070008261359487[250] = 0;
   out_388070008261359487[251] = 0;
   out_388070008261359487[252] = 0;
   out_388070008261359487[253] = 0;
   out_388070008261359487[254] = 0;
   out_388070008261359487[255] = 0;
   out_388070008261359487[256] = 0;
   out_388070008261359487[257] = 0;
   out_388070008261359487[258] = 0;
   out_388070008261359487[259] = 0;
   out_388070008261359487[260] = 0;
   out_388070008261359487[261] = 0;
   out_388070008261359487[262] = 0;
   out_388070008261359487[263] = 0;
   out_388070008261359487[264] = 0;
   out_388070008261359487[265] = 0;
   out_388070008261359487[266] = 1;
   out_388070008261359487[267] = 0;
   out_388070008261359487[268] = 0;
   out_388070008261359487[269] = 0;
   out_388070008261359487[270] = 0;
   out_388070008261359487[271] = 0;
   out_388070008261359487[272] = 0;
   out_388070008261359487[273] = 0;
   out_388070008261359487[274] = 0;
   out_388070008261359487[275] = 0;
   out_388070008261359487[276] = 0;
   out_388070008261359487[277] = 0;
   out_388070008261359487[278] = 0;
   out_388070008261359487[279] = 0;
   out_388070008261359487[280] = 0;
   out_388070008261359487[281] = 0;
   out_388070008261359487[282] = 0;
   out_388070008261359487[283] = 0;
   out_388070008261359487[284] = 0;
   out_388070008261359487[285] = 1;
   out_388070008261359487[286] = 0;
   out_388070008261359487[287] = 0;
   out_388070008261359487[288] = 0;
   out_388070008261359487[289] = 0;
   out_388070008261359487[290] = 0;
   out_388070008261359487[291] = 0;
   out_388070008261359487[292] = 0;
   out_388070008261359487[293] = 0;
   out_388070008261359487[294] = 0;
   out_388070008261359487[295] = 0;
   out_388070008261359487[296] = 0;
   out_388070008261359487[297] = 0;
   out_388070008261359487[298] = 0;
   out_388070008261359487[299] = 0;
   out_388070008261359487[300] = 0;
   out_388070008261359487[301] = 0;
   out_388070008261359487[302] = 0;
   out_388070008261359487[303] = 0;
   out_388070008261359487[304] = 1;
   out_388070008261359487[305] = 0;
   out_388070008261359487[306] = 0;
   out_388070008261359487[307] = 0;
   out_388070008261359487[308] = 0;
   out_388070008261359487[309] = 0;
   out_388070008261359487[310] = 0;
   out_388070008261359487[311] = 0;
   out_388070008261359487[312] = 0;
   out_388070008261359487[313] = 0;
   out_388070008261359487[314] = 0;
   out_388070008261359487[315] = 0;
   out_388070008261359487[316] = 0;
   out_388070008261359487[317] = 0;
   out_388070008261359487[318] = 0;
   out_388070008261359487[319] = 0;
   out_388070008261359487[320] = 0;
   out_388070008261359487[321] = 0;
   out_388070008261359487[322] = 0;
   out_388070008261359487[323] = 1;
}
void h_4(double *state, double *unused, double *out_424143301988092518) {
   out_424143301988092518[0] = state[6] + state[9];
   out_424143301988092518[1] = state[7] + state[10];
   out_424143301988092518[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6650517199469134710) {
   out_6650517199469134710[0] = 0;
   out_6650517199469134710[1] = 0;
   out_6650517199469134710[2] = 0;
   out_6650517199469134710[3] = 0;
   out_6650517199469134710[4] = 0;
   out_6650517199469134710[5] = 0;
   out_6650517199469134710[6] = 1;
   out_6650517199469134710[7] = 0;
   out_6650517199469134710[8] = 0;
   out_6650517199469134710[9] = 1;
   out_6650517199469134710[10] = 0;
   out_6650517199469134710[11] = 0;
   out_6650517199469134710[12] = 0;
   out_6650517199469134710[13] = 0;
   out_6650517199469134710[14] = 0;
   out_6650517199469134710[15] = 0;
   out_6650517199469134710[16] = 0;
   out_6650517199469134710[17] = 0;
   out_6650517199469134710[18] = 0;
   out_6650517199469134710[19] = 0;
   out_6650517199469134710[20] = 0;
   out_6650517199469134710[21] = 0;
   out_6650517199469134710[22] = 0;
   out_6650517199469134710[23] = 0;
   out_6650517199469134710[24] = 0;
   out_6650517199469134710[25] = 1;
   out_6650517199469134710[26] = 0;
   out_6650517199469134710[27] = 0;
   out_6650517199469134710[28] = 1;
   out_6650517199469134710[29] = 0;
   out_6650517199469134710[30] = 0;
   out_6650517199469134710[31] = 0;
   out_6650517199469134710[32] = 0;
   out_6650517199469134710[33] = 0;
   out_6650517199469134710[34] = 0;
   out_6650517199469134710[35] = 0;
   out_6650517199469134710[36] = 0;
   out_6650517199469134710[37] = 0;
   out_6650517199469134710[38] = 0;
   out_6650517199469134710[39] = 0;
   out_6650517199469134710[40] = 0;
   out_6650517199469134710[41] = 0;
   out_6650517199469134710[42] = 0;
   out_6650517199469134710[43] = 0;
   out_6650517199469134710[44] = 1;
   out_6650517199469134710[45] = 0;
   out_6650517199469134710[46] = 0;
   out_6650517199469134710[47] = 1;
   out_6650517199469134710[48] = 0;
   out_6650517199469134710[49] = 0;
   out_6650517199469134710[50] = 0;
   out_6650517199469134710[51] = 0;
   out_6650517199469134710[52] = 0;
   out_6650517199469134710[53] = 0;
}
void h_10(double *state, double *unused, double *out_5429944465818265103) {
   out_5429944465818265103[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5429944465818265103[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5429944465818265103[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6328749297458135702) {
   out_6328749297458135702[0] = 0;
   out_6328749297458135702[1] = 9.8100000000000005*cos(state[1]);
   out_6328749297458135702[2] = 0;
   out_6328749297458135702[3] = 0;
   out_6328749297458135702[4] = -state[8];
   out_6328749297458135702[5] = state[7];
   out_6328749297458135702[6] = 0;
   out_6328749297458135702[7] = state[5];
   out_6328749297458135702[8] = -state[4];
   out_6328749297458135702[9] = 0;
   out_6328749297458135702[10] = 0;
   out_6328749297458135702[11] = 0;
   out_6328749297458135702[12] = 1;
   out_6328749297458135702[13] = 0;
   out_6328749297458135702[14] = 0;
   out_6328749297458135702[15] = 1;
   out_6328749297458135702[16] = 0;
   out_6328749297458135702[17] = 0;
   out_6328749297458135702[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6328749297458135702[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6328749297458135702[20] = 0;
   out_6328749297458135702[21] = state[8];
   out_6328749297458135702[22] = 0;
   out_6328749297458135702[23] = -state[6];
   out_6328749297458135702[24] = -state[5];
   out_6328749297458135702[25] = 0;
   out_6328749297458135702[26] = state[3];
   out_6328749297458135702[27] = 0;
   out_6328749297458135702[28] = 0;
   out_6328749297458135702[29] = 0;
   out_6328749297458135702[30] = 0;
   out_6328749297458135702[31] = 1;
   out_6328749297458135702[32] = 0;
   out_6328749297458135702[33] = 0;
   out_6328749297458135702[34] = 1;
   out_6328749297458135702[35] = 0;
   out_6328749297458135702[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6328749297458135702[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6328749297458135702[38] = 0;
   out_6328749297458135702[39] = -state[7];
   out_6328749297458135702[40] = state[6];
   out_6328749297458135702[41] = 0;
   out_6328749297458135702[42] = state[4];
   out_6328749297458135702[43] = -state[3];
   out_6328749297458135702[44] = 0;
   out_6328749297458135702[45] = 0;
   out_6328749297458135702[46] = 0;
   out_6328749297458135702[47] = 0;
   out_6328749297458135702[48] = 0;
   out_6328749297458135702[49] = 0;
   out_6328749297458135702[50] = 1;
   out_6328749297458135702[51] = 0;
   out_6328749297458135702[52] = 0;
   out_6328749297458135702[53] = 1;
}
void h_13(double *state, double *unused, double *out_7408027604108256403) {
   out_7408027604108256403[0] = state[3];
   out_7408027604108256403[1] = state[4];
   out_7408027604108256403[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3438243374136801909) {
   out_3438243374136801909[0] = 0;
   out_3438243374136801909[1] = 0;
   out_3438243374136801909[2] = 0;
   out_3438243374136801909[3] = 1;
   out_3438243374136801909[4] = 0;
   out_3438243374136801909[5] = 0;
   out_3438243374136801909[6] = 0;
   out_3438243374136801909[7] = 0;
   out_3438243374136801909[8] = 0;
   out_3438243374136801909[9] = 0;
   out_3438243374136801909[10] = 0;
   out_3438243374136801909[11] = 0;
   out_3438243374136801909[12] = 0;
   out_3438243374136801909[13] = 0;
   out_3438243374136801909[14] = 0;
   out_3438243374136801909[15] = 0;
   out_3438243374136801909[16] = 0;
   out_3438243374136801909[17] = 0;
   out_3438243374136801909[18] = 0;
   out_3438243374136801909[19] = 0;
   out_3438243374136801909[20] = 0;
   out_3438243374136801909[21] = 0;
   out_3438243374136801909[22] = 1;
   out_3438243374136801909[23] = 0;
   out_3438243374136801909[24] = 0;
   out_3438243374136801909[25] = 0;
   out_3438243374136801909[26] = 0;
   out_3438243374136801909[27] = 0;
   out_3438243374136801909[28] = 0;
   out_3438243374136801909[29] = 0;
   out_3438243374136801909[30] = 0;
   out_3438243374136801909[31] = 0;
   out_3438243374136801909[32] = 0;
   out_3438243374136801909[33] = 0;
   out_3438243374136801909[34] = 0;
   out_3438243374136801909[35] = 0;
   out_3438243374136801909[36] = 0;
   out_3438243374136801909[37] = 0;
   out_3438243374136801909[38] = 0;
   out_3438243374136801909[39] = 0;
   out_3438243374136801909[40] = 0;
   out_3438243374136801909[41] = 1;
   out_3438243374136801909[42] = 0;
   out_3438243374136801909[43] = 0;
   out_3438243374136801909[44] = 0;
   out_3438243374136801909[45] = 0;
   out_3438243374136801909[46] = 0;
   out_3438243374136801909[47] = 0;
   out_3438243374136801909[48] = 0;
   out_3438243374136801909[49] = 0;
   out_3438243374136801909[50] = 0;
   out_3438243374136801909[51] = 0;
   out_3438243374136801909[52] = 0;
   out_3438243374136801909[53] = 0;
}
void h_14(double *state, double *unused, double *out_1915359263866192008) {
   out_1915359263866192008[0] = state[6];
   out_1915359263866192008[1] = state[7];
   out_1915359263866192008[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2687276343129650181) {
   out_2687276343129650181[0] = 0;
   out_2687276343129650181[1] = 0;
   out_2687276343129650181[2] = 0;
   out_2687276343129650181[3] = 0;
   out_2687276343129650181[4] = 0;
   out_2687276343129650181[5] = 0;
   out_2687276343129650181[6] = 1;
   out_2687276343129650181[7] = 0;
   out_2687276343129650181[8] = 0;
   out_2687276343129650181[9] = 0;
   out_2687276343129650181[10] = 0;
   out_2687276343129650181[11] = 0;
   out_2687276343129650181[12] = 0;
   out_2687276343129650181[13] = 0;
   out_2687276343129650181[14] = 0;
   out_2687276343129650181[15] = 0;
   out_2687276343129650181[16] = 0;
   out_2687276343129650181[17] = 0;
   out_2687276343129650181[18] = 0;
   out_2687276343129650181[19] = 0;
   out_2687276343129650181[20] = 0;
   out_2687276343129650181[21] = 0;
   out_2687276343129650181[22] = 0;
   out_2687276343129650181[23] = 0;
   out_2687276343129650181[24] = 0;
   out_2687276343129650181[25] = 1;
   out_2687276343129650181[26] = 0;
   out_2687276343129650181[27] = 0;
   out_2687276343129650181[28] = 0;
   out_2687276343129650181[29] = 0;
   out_2687276343129650181[30] = 0;
   out_2687276343129650181[31] = 0;
   out_2687276343129650181[32] = 0;
   out_2687276343129650181[33] = 0;
   out_2687276343129650181[34] = 0;
   out_2687276343129650181[35] = 0;
   out_2687276343129650181[36] = 0;
   out_2687276343129650181[37] = 0;
   out_2687276343129650181[38] = 0;
   out_2687276343129650181[39] = 0;
   out_2687276343129650181[40] = 0;
   out_2687276343129650181[41] = 0;
   out_2687276343129650181[42] = 0;
   out_2687276343129650181[43] = 0;
   out_2687276343129650181[44] = 1;
   out_2687276343129650181[45] = 0;
   out_2687276343129650181[46] = 0;
   out_2687276343129650181[47] = 0;
   out_2687276343129650181[48] = 0;
   out_2687276343129650181[49] = 0;
   out_2687276343129650181[50] = 0;
   out_2687276343129650181[51] = 0;
   out_2687276343129650181[52] = 0;
   out_2687276343129650181[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_9183838211698085113) {
  err_fun(nom_x, delta_x, out_9183838211698085113);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7880707634176237912) {
  inv_err_fun(nom_x, true_x, out_7880707634176237912);
}
void pose_H_mod_fun(double *state, double *out_4757006295873358620) {
  H_mod_fun(state, out_4757006295873358620);
}
void pose_f_fun(double *state, double dt, double *out_9118920386528411329) {
  f_fun(state,  dt, out_9118920386528411329);
}
void pose_F_fun(double *state, double dt, double *out_388070008261359487) {
  F_fun(state,  dt, out_388070008261359487);
}
void pose_h_4(double *state, double *unused, double *out_424143301988092518) {
  h_4(state, unused, out_424143301988092518);
}
void pose_H_4(double *state, double *unused, double *out_6650517199469134710) {
  H_4(state, unused, out_6650517199469134710);
}
void pose_h_10(double *state, double *unused, double *out_5429944465818265103) {
  h_10(state, unused, out_5429944465818265103);
}
void pose_H_10(double *state, double *unused, double *out_6328749297458135702) {
  H_10(state, unused, out_6328749297458135702);
}
void pose_h_13(double *state, double *unused, double *out_7408027604108256403) {
  h_13(state, unused, out_7408027604108256403);
}
void pose_H_13(double *state, double *unused, double *out_3438243374136801909) {
  H_13(state, unused, out_3438243374136801909);
}
void pose_h_14(double *state, double *unused, double *out_1915359263866192008) {
  h_14(state, unused, out_1915359263866192008);
}
void pose_H_14(double *state, double *unused, double *out_2687276343129650181) {
  H_14(state, unused, out_2687276343129650181);
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
