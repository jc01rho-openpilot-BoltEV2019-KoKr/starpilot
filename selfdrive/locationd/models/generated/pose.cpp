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
void err_fun(double *nom_x, double *delta_x, double *out_6497612872484174174) {
   out_6497612872484174174[0] = delta_x[0] + nom_x[0];
   out_6497612872484174174[1] = delta_x[1] + nom_x[1];
   out_6497612872484174174[2] = delta_x[2] + nom_x[2];
   out_6497612872484174174[3] = delta_x[3] + nom_x[3];
   out_6497612872484174174[4] = delta_x[4] + nom_x[4];
   out_6497612872484174174[5] = delta_x[5] + nom_x[5];
   out_6497612872484174174[6] = delta_x[6] + nom_x[6];
   out_6497612872484174174[7] = delta_x[7] + nom_x[7];
   out_6497612872484174174[8] = delta_x[8] + nom_x[8];
   out_6497612872484174174[9] = delta_x[9] + nom_x[9];
   out_6497612872484174174[10] = delta_x[10] + nom_x[10];
   out_6497612872484174174[11] = delta_x[11] + nom_x[11];
   out_6497612872484174174[12] = delta_x[12] + nom_x[12];
   out_6497612872484174174[13] = delta_x[13] + nom_x[13];
   out_6497612872484174174[14] = delta_x[14] + nom_x[14];
   out_6497612872484174174[15] = delta_x[15] + nom_x[15];
   out_6497612872484174174[16] = delta_x[16] + nom_x[16];
   out_6497612872484174174[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1975580934350294204) {
   out_1975580934350294204[0] = -nom_x[0] + true_x[0];
   out_1975580934350294204[1] = -nom_x[1] + true_x[1];
   out_1975580934350294204[2] = -nom_x[2] + true_x[2];
   out_1975580934350294204[3] = -nom_x[3] + true_x[3];
   out_1975580934350294204[4] = -nom_x[4] + true_x[4];
   out_1975580934350294204[5] = -nom_x[5] + true_x[5];
   out_1975580934350294204[6] = -nom_x[6] + true_x[6];
   out_1975580934350294204[7] = -nom_x[7] + true_x[7];
   out_1975580934350294204[8] = -nom_x[8] + true_x[8];
   out_1975580934350294204[9] = -nom_x[9] + true_x[9];
   out_1975580934350294204[10] = -nom_x[10] + true_x[10];
   out_1975580934350294204[11] = -nom_x[11] + true_x[11];
   out_1975580934350294204[12] = -nom_x[12] + true_x[12];
   out_1975580934350294204[13] = -nom_x[13] + true_x[13];
   out_1975580934350294204[14] = -nom_x[14] + true_x[14];
   out_1975580934350294204[15] = -nom_x[15] + true_x[15];
   out_1975580934350294204[16] = -nom_x[16] + true_x[16];
   out_1975580934350294204[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4617418789543565628) {
   out_4617418789543565628[0] = 1.0;
   out_4617418789543565628[1] = 0.0;
   out_4617418789543565628[2] = 0.0;
   out_4617418789543565628[3] = 0.0;
   out_4617418789543565628[4] = 0.0;
   out_4617418789543565628[5] = 0.0;
   out_4617418789543565628[6] = 0.0;
   out_4617418789543565628[7] = 0.0;
   out_4617418789543565628[8] = 0.0;
   out_4617418789543565628[9] = 0.0;
   out_4617418789543565628[10] = 0.0;
   out_4617418789543565628[11] = 0.0;
   out_4617418789543565628[12] = 0.0;
   out_4617418789543565628[13] = 0.0;
   out_4617418789543565628[14] = 0.0;
   out_4617418789543565628[15] = 0.0;
   out_4617418789543565628[16] = 0.0;
   out_4617418789543565628[17] = 0.0;
   out_4617418789543565628[18] = 0.0;
   out_4617418789543565628[19] = 1.0;
   out_4617418789543565628[20] = 0.0;
   out_4617418789543565628[21] = 0.0;
   out_4617418789543565628[22] = 0.0;
   out_4617418789543565628[23] = 0.0;
   out_4617418789543565628[24] = 0.0;
   out_4617418789543565628[25] = 0.0;
   out_4617418789543565628[26] = 0.0;
   out_4617418789543565628[27] = 0.0;
   out_4617418789543565628[28] = 0.0;
   out_4617418789543565628[29] = 0.0;
   out_4617418789543565628[30] = 0.0;
   out_4617418789543565628[31] = 0.0;
   out_4617418789543565628[32] = 0.0;
   out_4617418789543565628[33] = 0.0;
   out_4617418789543565628[34] = 0.0;
   out_4617418789543565628[35] = 0.0;
   out_4617418789543565628[36] = 0.0;
   out_4617418789543565628[37] = 0.0;
   out_4617418789543565628[38] = 1.0;
   out_4617418789543565628[39] = 0.0;
   out_4617418789543565628[40] = 0.0;
   out_4617418789543565628[41] = 0.0;
   out_4617418789543565628[42] = 0.0;
   out_4617418789543565628[43] = 0.0;
   out_4617418789543565628[44] = 0.0;
   out_4617418789543565628[45] = 0.0;
   out_4617418789543565628[46] = 0.0;
   out_4617418789543565628[47] = 0.0;
   out_4617418789543565628[48] = 0.0;
   out_4617418789543565628[49] = 0.0;
   out_4617418789543565628[50] = 0.0;
   out_4617418789543565628[51] = 0.0;
   out_4617418789543565628[52] = 0.0;
   out_4617418789543565628[53] = 0.0;
   out_4617418789543565628[54] = 0.0;
   out_4617418789543565628[55] = 0.0;
   out_4617418789543565628[56] = 0.0;
   out_4617418789543565628[57] = 1.0;
   out_4617418789543565628[58] = 0.0;
   out_4617418789543565628[59] = 0.0;
   out_4617418789543565628[60] = 0.0;
   out_4617418789543565628[61] = 0.0;
   out_4617418789543565628[62] = 0.0;
   out_4617418789543565628[63] = 0.0;
   out_4617418789543565628[64] = 0.0;
   out_4617418789543565628[65] = 0.0;
   out_4617418789543565628[66] = 0.0;
   out_4617418789543565628[67] = 0.0;
   out_4617418789543565628[68] = 0.0;
   out_4617418789543565628[69] = 0.0;
   out_4617418789543565628[70] = 0.0;
   out_4617418789543565628[71] = 0.0;
   out_4617418789543565628[72] = 0.0;
   out_4617418789543565628[73] = 0.0;
   out_4617418789543565628[74] = 0.0;
   out_4617418789543565628[75] = 0.0;
   out_4617418789543565628[76] = 1.0;
   out_4617418789543565628[77] = 0.0;
   out_4617418789543565628[78] = 0.0;
   out_4617418789543565628[79] = 0.0;
   out_4617418789543565628[80] = 0.0;
   out_4617418789543565628[81] = 0.0;
   out_4617418789543565628[82] = 0.0;
   out_4617418789543565628[83] = 0.0;
   out_4617418789543565628[84] = 0.0;
   out_4617418789543565628[85] = 0.0;
   out_4617418789543565628[86] = 0.0;
   out_4617418789543565628[87] = 0.0;
   out_4617418789543565628[88] = 0.0;
   out_4617418789543565628[89] = 0.0;
   out_4617418789543565628[90] = 0.0;
   out_4617418789543565628[91] = 0.0;
   out_4617418789543565628[92] = 0.0;
   out_4617418789543565628[93] = 0.0;
   out_4617418789543565628[94] = 0.0;
   out_4617418789543565628[95] = 1.0;
   out_4617418789543565628[96] = 0.0;
   out_4617418789543565628[97] = 0.0;
   out_4617418789543565628[98] = 0.0;
   out_4617418789543565628[99] = 0.0;
   out_4617418789543565628[100] = 0.0;
   out_4617418789543565628[101] = 0.0;
   out_4617418789543565628[102] = 0.0;
   out_4617418789543565628[103] = 0.0;
   out_4617418789543565628[104] = 0.0;
   out_4617418789543565628[105] = 0.0;
   out_4617418789543565628[106] = 0.0;
   out_4617418789543565628[107] = 0.0;
   out_4617418789543565628[108] = 0.0;
   out_4617418789543565628[109] = 0.0;
   out_4617418789543565628[110] = 0.0;
   out_4617418789543565628[111] = 0.0;
   out_4617418789543565628[112] = 0.0;
   out_4617418789543565628[113] = 0.0;
   out_4617418789543565628[114] = 1.0;
   out_4617418789543565628[115] = 0.0;
   out_4617418789543565628[116] = 0.0;
   out_4617418789543565628[117] = 0.0;
   out_4617418789543565628[118] = 0.0;
   out_4617418789543565628[119] = 0.0;
   out_4617418789543565628[120] = 0.0;
   out_4617418789543565628[121] = 0.0;
   out_4617418789543565628[122] = 0.0;
   out_4617418789543565628[123] = 0.0;
   out_4617418789543565628[124] = 0.0;
   out_4617418789543565628[125] = 0.0;
   out_4617418789543565628[126] = 0.0;
   out_4617418789543565628[127] = 0.0;
   out_4617418789543565628[128] = 0.0;
   out_4617418789543565628[129] = 0.0;
   out_4617418789543565628[130] = 0.0;
   out_4617418789543565628[131] = 0.0;
   out_4617418789543565628[132] = 0.0;
   out_4617418789543565628[133] = 1.0;
   out_4617418789543565628[134] = 0.0;
   out_4617418789543565628[135] = 0.0;
   out_4617418789543565628[136] = 0.0;
   out_4617418789543565628[137] = 0.0;
   out_4617418789543565628[138] = 0.0;
   out_4617418789543565628[139] = 0.0;
   out_4617418789543565628[140] = 0.0;
   out_4617418789543565628[141] = 0.0;
   out_4617418789543565628[142] = 0.0;
   out_4617418789543565628[143] = 0.0;
   out_4617418789543565628[144] = 0.0;
   out_4617418789543565628[145] = 0.0;
   out_4617418789543565628[146] = 0.0;
   out_4617418789543565628[147] = 0.0;
   out_4617418789543565628[148] = 0.0;
   out_4617418789543565628[149] = 0.0;
   out_4617418789543565628[150] = 0.0;
   out_4617418789543565628[151] = 0.0;
   out_4617418789543565628[152] = 1.0;
   out_4617418789543565628[153] = 0.0;
   out_4617418789543565628[154] = 0.0;
   out_4617418789543565628[155] = 0.0;
   out_4617418789543565628[156] = 0.0;
   out_4617418789543565628[157] = 0.0;
   out_4617418789543565628[158] = 0.0;
   out_4617418789543565628[159] = 0.0;
   out_4617418789543565628[160] = 0.0;
   out_4617418789543565628[161] = 0.0;
   out_4617418789543565628[162] = 0.0;
   out_4617418789543565628[163] = 0.0;
   out_4617418789543565628[164] = 0.0;
   out_4617418789543565628[165] = 0.0;
   out_4617418789543565628[166] = 0.0;
   out_4617418789543565628[167] = 0.0;
   out_4617418789543565628[168] = 0.0;
   out_4617418789543565628[169] = 0.0;
   out_4617418789543565628[170] = 0.0;
   out_4617418789543565628[171] = 1.0;
   out_4617418789543565628[172] = 0.0;
   out_4617418789543565628[173] = 0.0;
   out_4617418789543565628[174] = 0.0;
   out_4617418789543565628[175] = 0.0;
   out_4617418789543565628[176] = 0.0;
   out_4617418789543565628[177] = 0.0;
   out_4617418789543565628[178] = 0.0;
   out_4617418789543565628[179] = 0.0;
   out_4617418789543565628[180] = 0.0;
   out_4617418789543565628[181] = 0.0;
   out_4617418789543565628[182] = 0.0;
   out_4617418789543565628[183] = 0.0;
   out_4617418789543565628[184] = 0.0;
   out_4617418789543565628[185] = 0.0;
   out_4617418789543565628[186] = 0.0;
   out_4617418789543565628[187] = 0.0;
   out_4617418789543565628[188] = 0.0;
   out_4617418789543565628[189] = 0.0;
   out_4617418789543565628[190] = 1.0;
   out_4617418789543565628[191] = 0.0;
   out_4617418789543565628[192] = 0.0;
   out_4617418789543565628[193] = 0.0;
   out_4617418789543565628[194] = 0.0;
   out_4617418789543565628[195] = 0.0;
   out_4617418789543565628[196] = 0.0;
   out_4617418789543565628[197] = 0.0;
   out_4617418789543565628[198] = 0.0;
   out_4617418789543565628[199] = 0.0;
   out_4617418789543565628[200] = 0.0;
   out_4617418789543565628[201] = 0.0;
   out_4617418789543565628[202] = 0.0;
   out_4617418789543565628[203] = 0.0;
   out_4617418789543565628[204] = 0.0;
   out_4617418789543565628[205] = 0.0;
   out_4617418789543565628[206] = 0.0;
   out_4617418789543565628[207] = 0.0;
   out_4617418789543565628[208] = 0.0;
   out_4617418789543565628[209] = 1.0;
   out_4617418789543565628[210] = 0.0;
   out_4617418789543565628[211] = 0.0;
   out_4617418789543565628[212] = 0.0;
   out_4617418789543565628[213] = 0.0;
   out_4617418789543565628[214] = 0.0;
   out_4617418789543565628[215] = 0.0;
   out_4617418789543565628[216] = 0.0;
   out_4617418789543565628[217] = 0.0;
   out_4617418789543565628[218] = 0.0;
   out_4617418789543565628[219] = 0.0;
   out_4617418789543565628[220] = 0.0;
   out_4617418789543565628[221] = 0.0;
   out_4617418789543565628[222] = 0.0;
   out_4617418789543565628[223] = 0.0;
   out_4617418789543565628[224] = 0.0;
   out_4617418789543565628[225] = 0.0;
   out_4617418789543565628[226] = 0.0;
   out_4617418789543565628[227] = 0.0;
   out_4617418789543565628[228] = 1.0;
   out_4617418789543565628[229] = 0.0;
   out_4617418789543565628[230] = 0.0;
   out_4617418789543565628[231] = 0.0;
   out_4617418789543565628[232] = 0.0;
   out_4617418789543565628[233] = 0.0;
   out_4617418789543565628[234] = 0.0;
   out_4617418789543565628[235] = 0.0;
   out_4617418789543565628[236] = 0.0;
   out_4617418789543565628[237] = 0.0;
   out_4617418789543565628[238] = 0.0;
   out_4617418789543565628[239] = 0.0;
   out_4617418789543565628[240] = 0.0;
   out_4617418789543565628[241] = 0.0;
   out_4617418789543565628[242] = 0.0;
   out_4617418789543565628[243] = 0.0;
   out_4617418789543565628[244] = 0.0;
   out_4617418789543565628[245] = 0.0;
   out_4617418789543565628[246] = 0.0;
   out_4617418789543565628[247] = 1.0;
   out_4617418789543565628[248] = 0.0;
   out_4617418789543565628[249] = 0.0;
   out_4617418789543565628[250] = 0.0;
   out_4617418789543565628[251] = 0.0;
   out_4617418789543565628[252] = 0.0;
   out_4617418789543565628[253] = 0.0;
   out_4617418789543565628[254] = 0.0;
   out_4617418789543565628[255] = 0.0;
   out_4617418789543565628[256] = 0.0;
   out_4617418789543565628[257] = 0.0;
   out_4617418789543565628[258] = 0.0;
   out_4617418789543565628[259] = 0.0;
   out_4617418789543565628[260] = 0.0;
   out_4617418789543565628[261] = 0.0;
   out_4617418789543565628[262] = 0.0;
   out_4617418789543565628[263] = 0.0;
   out_4617418789543565628[264] = 0.0;
   out_4617418789543565628[265] = 0.0;
   out_4617418789543565628[266] = 1.0;
   out_4617418789543565628[267] = 0.0;
   out_4617418789543565628[268] = 0.0;
   out_4617418789543565628[269] = 0.0;
   out_4617418789543565628[270] = 0.0;
   out_4617418789543565628[271] = 0.0;
   out_4617418789543565628[272] = 0.0;
   out_4617418789543565628[273] = 0.0;
   out_4617418789543565628[274] = 0.0;
   out_4617418789543565628[275] = 0.0;
   out_4617418789543565628[276] = 0.0;
   out_4617418789543565628[277] = 0.0;
   out_4617418789543565628[278] = 0.0;
   out_4617418789543565628[279] = 0.0;
   out_4617418789543565628[280] = 0.0;
   out_4617418789543565628[281] = 0.0;
   out_4617418789543565628[282] = 0.0;
   out_4617418789543565628[283] = 0.0;
   out_4617418789543565628[284] = 0.0;
   out_4617418789543565628[285] = 1.0;
   out_4617418789543565628[286] = 0.0;
   out_4617418789543565628[287] = 0.0;
   out_4617418789543565628[288] = 0.0;
   out_4617418789543565628[289] = 0.0;
   out_4617418789543565628[290] = 0.0;
   out_4617418789543565628[291] = 0.0;
   out_4617418789543565628[292] = 0.0;
   out_4617418789543565628[293] = 0.0;
   out_4617418789543565628[294] = 0.0;
   out_4617418789543565628[295] = 0.0;
   out_4617418789543565628[296] = 0.0;
   out_4617418789543565628[297] = 0.0;
   out_4617418789543565628[298] = 0.0;
   out_4617418789543565628[299] = 0.0;
   out_4617418789543565628[300] = 0.0;
   out_4617418789543565628[301] = 0.0;
   out_4617418789543565628[302] = 0.0;
   out_4617418789543565628[303] = 0.0;
   out_4617418789543565628[304] = 1.0;
   out_4617418789543565628[305] = 0.0;
   out_4617418789543565628[306] = 0.0;
   out_4617418789543565628[307] = 0.0;
   out_4617418789543565628[308] = 0.0;
   out_4617418789543565628[309] = 0.0;
   out_4617418789543565628[310] = 0.0;
   out_4617418789543565628[311] = 0.0;
   out_4617418789543565628[312] = 0.0;
   out_4617418789543565628[313] = 0.0;
   out_4617418789543565628[314] = 0.0;
   out_4617418789543565628[315] = 0.0;
   out_4617418789543565628[316] = 0.0;
   out_4617418789543565628[317] = 0.0;
   out_4617418789543565628[318] = 0.0;
   out_4617418789543565628[319] = 0.0;
   out_4617418789543565628[320] = 0.0;
   out_4617418789543565628[321] = 0.0;
   out_4617418789543565628[322] = 0.0;
   out_4617418789543565628[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_9094503671864348345) {
   out_9094503671864348345[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_9094503671864348345[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_9094503671864348345[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_9094503671864348345[3] = dt*state[12] + state[3];
   out_9094503671864348345[4] = dt*state[13] + state[4];
   out_9094503671864348345[5] = dt*state[14] + state[5];
   out_9094503671864348345[6] = state[6];
   out_9094503671864348345[7] = state[7];
   out_9094503671864348345[8] = state[8];
   out_9094503671864348345[9] = state[9];
   out_9094503671864348345[10] = state[10];
   out_9094503671864348345[11] = state[11];
   out_9094503671864348345[12] = state[12];
   out_9094503671864348345[13] = state[13];
   out_9094503671864348345[14] = state[14];
   out_9094503671864348345[15] = state[15];
   out_9094503671864348345[16] = state[16];
   out_9094503671864348345[17] = state[17];
}
void F_fun(double *state, double dt, double *out_1312959600226932432) {
   out_1312959600226932432[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1312959600226932432[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1312959600226932432[2] = 0;
   out_1312959600226932432[3] = 0;
   out_1312959600226932432[4] = 0;
   out_1312959600226932432[5] = 0;
   out_1312959600226932432[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1312959600226932432[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1312959600226932432[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_1312959600226932432[9] = 0;
   out_1312959600226932432[10] = 0;
   out_1312959600226932432[11] = 0;
   out_1312959600226932432[12] = 0;
   out_1312959600226932432[13] = 0;
   out_1312959600226932432[14] = 0;
   out_1312959600226932432[15] = 0;
   out_1312959600226932432[16] = 0;
   out_1312959600226932432[17] = 0;
   out_1312959600226932432[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1312959600226932432[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1312959600226932432[20] = 0;
   out_1312959600226932432[21] = 0;
   out_1312959600226932432[22] = 0;
   out_1312959600226932432[23] = 0;
   out_1312959600226932432[24] = 0;
   out_1312959600226932432[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1312959600226932432[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_1312959600226932432[27] = 0;
   out_1312959600226932432[28] = 0;
   out_1312959600226932432[29] = 0;
   out_1312959600226932432[30] = 0;
   out_1312959600226932432[31] = 0;
   out_1312959600226932432[32] = 0;
   out_1312959600226932432[33] = 0;
   out_1312959600226932432[34] = 0;
   out_1312959600226932432[35] = 0;
   out_1312959600226932432[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1312959600226932432[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1312959600226932432[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1312959600226932432[39] = 0;
   out_1312959600226932432[40] = 0;
   out_1312959600226932432[41] = 0;
   out_1312959600226932432[42] = 0;
   out_1312959600226932432[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1312959600226932432[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_1312959600226932432[45] = 0;
   out_1312959600226932432[46] = 0;
   out_1312959600226932432[47] = 0;
   out_1312959600226932432[48] = 0;
   out_1312959600226932432[49] = 0;
   out_1312959600226932432[50] = 0;
   out_1312959600226932432[51] = 0;
   out_1312959600226932432[52] = 0;
   out_1312959600226932432[53] = 0;
   out_1312959600226932432[54] = 0;
   out_1312959600226932432[55] = 0;
   out_1312959600226932432[56] = 0;
   out_1312959600226932432[57] = 1;
   out_1312959600226932432[58] = 0;
   out_1312959600226932432[59] = 0;
   out_1312959600226932432[60] = 0;
   out_1312959600226932432[61] = 0;
   out_1312959600226932432[62] = 0;
   out_1312959600226932432[63] = 0;
   out_1312959600226932432[64] = 0;
   out_1312959600226932432[65] = 0;
   out_1312959600226932432[66] = dt;
   out_1312959600226932432[67] = 0;
   out_1312959600226932432[68] = 0;
   out_1312959600226932432[69] = 0;
   out_1312959600226932432[70] = 0;
   out_1312959600226932432[71] = 0;
   out_1312959600226932432[72] = 0;
   out_1312959600226932432[73] = 0;
   out_1312959600226932432[74] = 0;
   out_1312959600226932432[75] = 0;
   out_1312959600226932432[76] = 1;
   out_1312959600226932432[77] = 0;
   out_1312959600226932432[78] = 0;
   out_1312959600226932432[79] = 0;
   out_1312959600226932432[80] = 0;
   out_1312959600226932432[81] = 0;
   out_1312959600226932432[82] = 0;
   out_1312959600226932432[83] = 0;
   out_1312959600226932432[84] = 0;
   out_1312959600226932432[85] = dt;
   out_1312959600226932432[86] = 0;
   out_1312959600226932432[87] = 0;
   out_1312959600226932432[88] = 0;
   out_1312959600226932432[89] = 0;
   out_1312959600226932432[90] = 0;
   out_1312959600226932432[91] = 0;
   out_1312959600226932432[92] = 0;
   out_1312959600226932432[93] = 0;
   out_1312959600226932432[94] = 0;
   out_1312959600226932432[95] = 1;
   out_1312959600226932432[96] = 0;
   out_1312959600226932432[97] = 0;
   out_1312959600226932432[98] = 0;
   out_1312959600226932432[99] = 0;
   out_1312959600226932432[100] = 0;
   out_1312959600226932432[101] = 0;
   out_1312959600226932432[102] = 0;
   out_1312959600226932432[103] = 0;
   out_1312959600226932432[104] = dt;
   out_1312959600226932432[105] = 0;
   out_1312959600226932432[106] = 0;
   out_1312959600226932432[107] = 0;
   out_1312959600226932432[108] = 0;
   out_1312959600226932432[109] = 0;
   out_1312959600226932432[110] = 0;
   out_1312959600226932432[111] = 0;
   out_1312959600226932432[112] = 0;
   out_1312959600226932432[113] = 0;
   out_1312959600226932432[114] = 1;
   out_1312959600226932432[115] = 0;
   out_1312959600226932432[116] = 0;
   out_1312959600226932432[117] = 0;
   out_1312959600226932432[118] = 0;
   out_1312959600226932432[119] = 0;
   out_1312959600226932432[120] = 0;
   out_1312959600226932432[121] = 0;
   out_1312959600226932432[122] = 0;
   out_1312959600226932432[123] = 0;
   out_1312959600226932432[124] = 0;
   out_1312959600226932432[125] = 0;
   out_1312959600226932432[126] = 0;
   out_1312959600226932432[127] = 0;
   out_1312959600226932432[128] = 0;
   out_1312959600226932432[129] = 0;
   out_1312959600226932432[130] = 0;
   out_1312959600226932432[131] = 0;
   out_1312959600226932432[132] = 0;
   out_1312959600226932432[133] = 1;
   out_1312959600226932432[134] = 0;
   out_1312959600226932432[135] = 0;
   out_1312959600226932432[136] = 0;
   out_1312959600226932432[137] = 0;
   out_1312959600226932432[138] = 0;
   out_1312959600226932432[139] = 0;
   out_1312959600226932432[140] = 0;
   out_1312959600226932432[141] = 0;
   out_1312959600226932432[142] = 0;
   out_1312959600226932432[143] = 0;
   out_1312959600226932432[144] = 0;
   out_1312959600226932432[145] = 0;
   out_1312959600226932432[146] = 0;
   out_1312959600226932432[147] = 0;
   out_1312959600226932432[148] = 0;
   out_1312959600226932432[149] = 0;
   out_1312959600226932432[150] = 0;
   out_1312959600226932432[151] = 0;
   out_1312959600226932432[152] = 1;
   out_1312959600226932432[153] = 0;
   out_1312959600226932432[154] = 0;
   out_1312959600226932432[155] = 0;
   out_1312959600226932432[156] = 0;
   out_1312959600226932432[157] = 0;
   out_1312959600226932432[158] = 0;
   out_1312959600226932432[159] = 0;
   out_1312959600226932432[160] = 0;
   out_1312959600226932432[161] = 0;
   out_1312959600226932432[162] = 0;
   out_1312959600226932432[163] = 0;
   out_1312959600226932432[164] = 0;
   out_1312959600226932432[165] = 0;
   out_1312959600226932432[166] = 0;
   out_1312959600226932432[167] = 0;
   out_1312959600226932432[168] = 0;
   out_1312959600226932432[169] = 0;
   out_1312959600226932432[170] = 0;
   out_1312959600226932432[171] = 1;
   out_1312959600226932432[172] = 0;
   out_1312959600226932432[173] = 0;
   out_1312959600226932432[174] = 0;
   out_1312959600226932432[175] = 0;
   out_1312959600226932432[176] = 0;
   out_1312959600226932432[177] = 0;
   out_1312959600226932432[178] = 0;
   out_1312959600226932432[179] = 0;
   out_1312959600226932432[180] = 0;
   out_1312959600226932432[181] = 0;
   out_1312959600226932432[182] = 0;
   out_1312959600226932432[183] = 0;
   out_1312959600226932432[184] = 0;
   out_1312959600226932432[185] = 0;
   out_1312959600226932432[186] = 0;
   out_1312959600226932432[187] = 0;
   out_1312959600226932432[188] = 0;
   out_1312959600226932432[189] = 0;
   out_1312959600226932432[190] = 1;
   out_1312959600226932432[191] = 0;
   out_1312959600226932432[192] = 0;
   out_1312959600226932432[193] = 0;
   out_1312959600226932432[194] = 0;
   out_1312959600226932432[195] = 0;
   out_1312959600226932432[196] = 0;
   out_1312959600226932432[197] = 0;
   out_1312959600226932432[198] = 0;
   out_1312959600226932432[199] = 0;
   out_1312959600226932432[200] = 0;
   out_1312959600226932432[201] = 0;
   out_1312959600226932432[202] = 0;
   out_1312959600226932432[203] = 0;
   out_1312959600226932432[204] = 0;
   out_1312959600226932432[205] = 0;
   out_1312959600226932432[206] = 0;
   out_1312959600226932432[207] = 0;
   out_1312959600226932432[208] = 0;
   out_1312959600226932432[209] = 1;
   out_1312959600226932432[210] = 0;
   out_1312959600226932432[211] = 0;
   out_1312959600226932432[212] = 0;
   out_1312959600226932432[213] = 0;
   out_1312959600226932432[214] = 0;
   out_1312959600226932432[215] = 0;
   out_1312959600226932432[216] = 0;
   out_1312959600226932432[217] = 0;
   out_1312959600226932432[218] = 0;
   out_1312959600226932432[219] = 0;
   out_1312959600226932432[220] = 0;
   out_1312959600226932432[221] = 0;
   out_1312959600226932432[222] = 0;
   out_1312959600226932432[223] = 0;
   out_1312959600226932432[224] = 0;
   out_1312959600226932432[225] = 0;
   out_1312959600226932432[226] = 0;
   out_1312959600226932432[227] = 0;
   out_1312959600226932432[228] = 1;
   out_1312959600226932432[229] = 0;
   out_1312959600226932432[230] = 0;
   out_1312959600226932432[231] = 0;
   out_1312959600226932432[232] = 0;
   out_1312959600226932432[233] = 0;
   out_1312959600226932432[234] = 0;
   out_1312959600226932432[235] = 0;
   out_1312959600226932432[236] = 0;
   out_1312959600226932432[237] = 0;
   out_1312959600226932432[238] = 0;
   out_1312959600226932432[239] = 0;
   out_1312959600226932432[240] = 0;
   out_1312959600226932432[241] = 0;
   out_1312959600226932432[242] = 0;
   out_1312959600226932432[243] = 0;
   out_1312959600226932432[244] = 0;
   out_1312959600226932432[245] = 0;
   out_1312959600226932432[246] = 0;
   out_1312959600226932432[247] = 1;
   out_1312959600226932432[248] = 0;
   out_1312959600226932432[249] = 0;
   out_1312959600226932432[250] = 0;
   out_1312959600226932432[251] = 0;
   out_1312959600226932432[252] = 0;
   out_1312959600226932432[253] = 0;
   out_1312959600226932432[254] = 0;
   out_1312959600226932432[255] = 0;
   out_1312959600226932432[256] = 0;
   out_1312959600226932432[257] = 0;
   out_1312959600226932432[258] = 0;
   out_1312959600226932432[259] = 0;
   out_1312959600226932432[260] = 0;
   out_1312959600226932432[261] = 0;
   out_1312959600226932432[262] = 0;
   out_1312959600226932432[263] = 0;
   out_1312959600226932432[264] = 0;
   out_1312959600226932432[265] = 0;
   out_1312959600226932432[266] = 1;
   out_1312959600226932432[267] = 0;
   out_1312959600226932432[268] = 0;
   out_1312959600226932432[269] = 0;
   out_1312959600226932432[270] = 0;
   out_1312959600226932432[271] = 0;
   out_1312959600226932432[272] = 0;
   out_1312959600226932432[273] = 0;
   out_1312959600226932432[274] = 0;
   out_1312959600226932432[275] = 0;
   out_1312959600226932432[276] = 0;
   out_1312959600226932432[277] = 0;
   out_1312959600226932432[278] = 0;
   out_1312959600226932432[279] = 0;
   out_1312959600226932432[280] = 0;
   out_1312959600226932432[281] = 0;
   out_1312959600226932432[282] = 0;
   out_1312959600226932432[283] = 0;
   out_1312959600226932432[284] = 0;
   out_1312959600226932432[285] = 1;
   out_1312959600226932432[286] = 0;
   out_1312959600226932432[287] = 0;
   out_1312959600226932432[288] = 0;
   out_1312959600226932432[289] = 0;
   out_1312959600226932432[290] = 0;
   out_1312959600226932432[291] = 0;
   out_1312959600226932432[292] = 0;
   out_1312959600226932432[293] = 0;
   out_1312959600226932432[294] = 0;
   out_1312959600226932432[295] = 0;
   out_1312959600226932432[296] = 0;
   out_1312959600226932432[297] = 0;
   out_1312959600226932432[298] = 0;
   out_1312959600226932432[299] = 0;
   out_1312959600226932432[300] = 0;
   out_1312959600226932432[301] = 0;
   out_1312959600226932432[302] = 0;
   out_1312959600226932432[303] = 0;
   out_1312959600226932432[304] = 1;
   out_1312959600226932432[305] = 0;
   out_1312959600226932432[306] = 0;
   out_1312959600226932432[307] = 0;
   out_1312959600226932432[308] = 0;
   out_1312959600226932432[309] = 0;
   out_1312959600226932432[310] = 0;
   out_1312959600226932432[311] = 0;
   out_1312959600226932432[312] = 0;
   out_1312959600226932432[313] = 0;
   out_1312959600226932432[314] = 0;
   out_1312959600226932432[315] = 0;
   out_1312959600226932432[316] = 0;
   out_1312959600226932432[317] = 0;
   out_1312959600226932432[318] = 0;
   out_1312959600226932432[319] = 0;
   out_1312959600226932432[320] = 0;
   out_1312959600226932432[321] = 0;
   out_1312959600226932432[322] = 0;
   out_1312959600226932432[323] = 1;
}
void h_4(double *state, double *unused, double *out_6400948089178504221) {
   out_6400948089178504221[0] = state[6] + state[9];
   out_6400948089178504221[1] = state[7] + state[10];
   out_6400948089178504221[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3419471307660667524) {
   out_3419471307660667524[0] = 0;
   out_3419471307660667524[1] = 0;
   out_3419471307660667524[2] = 0;
   out_3419471307660667524[3] = 0;
   out_3419471307660667524[4] = 0;
   out_3419471307660667524[5] = 0;
   out_3419471307660667524[6] = 1;
   out_3419471307660667524[7] = 0;
   out_3419471307660667524[8] = 0;
   out_3419471307660667524[9] = 1;
   out_3419471307660667524[10] = 0;
   out_3419471307660667524[11] = 0;
   out_3419471307660667524[12] = 0;
   out_3419471307660667524[13] = 0;
   out_3419471307660667524[14] = 0;
   out_3419471307660667524[15] = 0;
   out_3419471307660667524[16] = 0;
   out_3419471307660667524[17] = 0;
   out_3419471307660667524[18] = 0;
   out_3419471307660667524[19] = 0;
   out_3419471307660667524[20] = 0;
   out_3419471307660667524[21] = 0;
   out_3419471307660667524[22] = 0;
   out_3419471307660667524[23] = 0;
   out_3419471307660667524[24] = 0;
   out_3419471307660667524[25] = 1;
   out_3419471307660667524[26] = 0;
   out_3419471307660667524[27] = 0;
   out_3419471307660667524[28] = 1;
   out_3419471307660667524[29] = 0;
   out_3419471307660667524[30] = 0;
   out_3419471307660667524[31] = 0;
   out_3419471307660667524[32] = 0;
   out_3419471307660667524[33] = 0;
   out_3419471307660667524[34] = 0;
   out_3419471307660667524[35] = 0;
   out_3419471307660667524[36] = 0;
   out_3419471307660667524[37] = 0;
   out_3419471307660667524[38] = 0;
   out_3419471307660667524[39] = 0;
   out_3419471307660667524[40] = 0;
   out_3419471307660667524[41] = 0;
   out_3419471307660667524[42] = 0;
   out_3419471307660667524[43] = 0;
   out_3419471307660667524[44] = 1;
   out_3419471307660667524[45] = 0;
   out_3419471307660667524[46] = 0;
   out_3419471307660667524[47] = 1;
   out_3419471307660667524[48] = 0;
   out_3419471307660667524[49] = 0;
   out_3419471307660667524[50] = 0;
   out_3419471307660667524[51] = 0;
   out_3419471307660667524[52] = 0;
   out_3419471307660667524[53] = 0;
}
void h_10(double *state, double *unused, double *out_8540054287512262719) {
   out_8540054287512262719[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8540054287512262719[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8540054287512262719[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5231659216258162963) {
   out_5231659216258162963[0] = 0;
   out_5231659216258162963[1] = 9.8100000000000005*cos(state[1]);
   out_5231659216258162963[2] = 0;
   out_5231659216258162963[3] = 0;
   out_5231659216258162963[4] = -state[8];
   out_5231659216258162963[5] = state[7];
   out_5231659216258162963[6] = 0;
   out_5231659216258162963[7] = state[5];
   out_5231659216258162963[8] = -state[4];
   out_5231659216258162963[9] = 0;
   out_5231659216258162963[10] = 0;
   out_5231659216258162963[11] = 0;
   out_5231659216258162963[12] = 1;
   out_5231659216258162963[13] = 0;
   out_5231659216258162963[14] = 0;
   out_5231659216258162963[15] = 1;
   out_5231659216258162963[16] = 0;
   out_5231659216258162963[17] = 0;
   out_5231659216258162963[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5231659216258162963[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5231659216258162963[20] = 0;
   out_5231659216258162963[21] = state[8];
   out_5231659216258162963[22] = 0;
   out_5231659216258162963[23] = -state[6];
   out_5231659216258162963[24] = -state[5];
   out_5231659216258162963[25] = 0;
   out_5231659216258162963[26] = state[3];
   out_5231659216258162963[27] = 0;
   out_5231659216258162963[28] = 0;
   out_5231659216258162963[29] = 0;
   out_5231659216258162963[30] = 0;
   out_5231659216258162963[31] = 1;
   out_5231659216258162963[32] = 0;
   out_5231659216258162963[33] = 0;
   out_5231659216258162963[34] = 1;
   out_5231659216258162963[35] = 0;
   out_5231659216258162963[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5231659216258162963[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5231659216258162963[38] = 0;
   out_5231659216258162963[39] = -state[7];
   out_5231659216258162963[40] = state[6];
   out_5231659216258162963[41] = 0;
   out_5231659216258162963[42] = state[4];
   out_5231659216258162963[43] = -state[3];
   out_5231659216258162963[44] = 0;
   out_5231659216258162963[45] = 0;
   out_5231659216258162963[46] = 0;
   out_5231659216258162963[47] = 0;
   out_5231659216258162963[48] = 0;
   out_5231659216258162963[49] = 0;
   out_5231659216258162963[50] = 1;
   out_5231659216258162963[51] = 0;
   out_5231659216258162963[52] = 0;
   out_5231659216258162963[53] = 1;
}
void h_13(double *state, double *unused, double *out_7953441679753433349) {
   out_7953441679753433349[0] = state[3];
   out_7953441679753433349[1] = state[4];
   out_7953441679753433349[2] = state[5];
}
void H_13(double *state, double *unused, double *out_207197482328334723) {
   out_207197482328334723[0] = 0;
   out_207197482328334723[1] = 0;
   out_207197482328334723[2] = 0;
   out_207197482328334723[3] = 1;
   out_207197482328334723[4] = 0;
   out_207197482328334723[5] = 0;
   out_207197482328334723[6] = 0;
   out_207197482328334723[7] = 0;
   out_207197482328334723[8] = 0;
   out_207197482328334723[9] = 0;
   out_207197482328334723[10] = 0;
   out_207197482328334723[11] = 0;
   out_207197482328334723[12] = 0;
   out_207197482328334723[13] = 0;
   out_207197482328334723[14] = 0;
   out_207197482328334723[15] = 0;
   out_207197482328334723[16] = 0;
   out_207197482328334723[17] = 0;
   out_207197482328334723[18] = 0;
   out_207197482328334723[19] = 0;
   out_207197482328334723[20] = 0;
   out_207197482328334723[21] = 0;
   out_207197482328334723[22] = 1;
   out_207197482328334723[23] = 0;
   out_207197482328334723[24] = 0;
   out_207197482328334723[25] = 0;
   out_207197482328334723[26] = 0;
   out_207197482328334723[27] = 0;
   out_207197482328334723[28] = 0;
   out_207197482328334723[29] = 0;
   out_207197482328334723[30] = 0;
   out_207197482328334723[31] = 0;
   out_207197482328334723[32] = 0;
   out_207197482328334723[33] = 0;
   out_207197482328334723[34] = 0;
   out_207197482328334723[35] = 0;
   out_207197482328334723[36] = 0;
   out_207197482328334723[37] = 0;
   out_207197482328334723[38] = 0;
   out_207197482328334723[39] = 0;
   out_207197482328334723[40] = 0;
   out_207197482328334723[41] = 1;
   out_207197482328334723[42] = 0;
   out_207197482328334723[43] = 0;
   out_207197482328334723[44] = 0;
   out_207197482328334723[45] = 0;
   out_207197482328334723[46] = 0;
   out_207197482328334723[47] = 0;
   out_207197482328334723[48] = 0;
   out_207197482328334723[49] = 0;
   out_207197482328334723[50] = 0;
   out_207197482328334723[51] = 0;
   out_207197482328334723[52] = 0;
   out_207197482328334723[53] = 0;
}
void h_14(double *state, double *unused, double *out_8785755176393893631) {
   out_8785755176393893631[0] = state[6];
   out_8785755176393893631[1] = state[7];
   out_8785755176393893631[2] = state[8];
}
void H_14(double *state, double *unused, double *out_543769548678817005) {
   out_543769548678817005[0] = 0;
   out_543769548678817005[1] = 0;
   out_543769548678817005[2] = 0;
   out_543769548678817005[3] = 0;
   out_543769548678817005[4] = 0;
   out_543769548678817005[5] = 0;
   out_543769548678817005[6] = 1;
   out_543769548678817005[7] = 0;
   out_543769548678817005[8] = 0;
   out_543769548678817005[9] = 0;
   out_543769548678817005[10] = 0;
   out_543769548678817005[11] = 0;
   out_543769548678817005[12] = 0;
   out_543769548678817005[13] = 0;
   out_543769548678817005[14] = 0;
   out_543769548678817005[15] = 0;
   out_543769548678817005[16] = 0;
   out_543769548678817005[17] = 0;
   out_543769548678817005[18] = 0;
   out_543769548678817005[19] = 0;
   out_543769548678817005[20] = 0;
   out_543769548678817005[21] = 0;
   out_543769548678817005[22] = 0;
   out_543769548678817005[23] = 0;
   out_543769548678817005[24] = 0;
   out_543769548678817005[25] = 1;
   out_543769548678817005[26] = 0;
   out_543769548678817005[27] = 0;
   out_543769548678817005[28] = 0;
   out_543769548678817005[29] = 0;
   out_543769548678817005[30] = 0;
   out_543769548678817005[31] = 0;
   out_543769548678817005[32] = 0;
   out_543769548678817005[33] = 0;
   out_543769548678817005[34] = 0;
   out_543769548678817005[35] = 0;
   out_543769548678817005[36] = 0;
   out_543769548678817005[37] = 0;
   out_543769548678817005[38] = 0;
   out_543769548678817005[39] = 0;
   out_543769548678817005[40] = 0;
   out_543769548678817005[41] = 0;
   out_543769548678817005[42] = 0;
   out_543769548678817005[43] = 0;
   out_543769548678817005[44] = 1;
   out_543769548678817005[45] = 0;
   out_543769548678817005[46] = 0;
   out_543769548678817005[47] = 0;
   out_543769548678817005[48] = 0;
   out_543769548678817005[49] = 0;
   out_543769548678817005[50] = 0;
   out_543769548678817005[51] = 0;
   out_543769548678817005[52] = 0;
   out_543769548678817005[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_6497612872484174174) {
  err_fun(nom_x, delta_x, out_6497612872484174174);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1975580934350294204) {
  inv_err_fun(nom_x, true_x, out_1975580934350294204);
}
void pose_H_mod_fun(double *state, double *out_4617418789543565628) {
  H_mod_fun(state, out_4617418789543565628);
}
void pose_f_fun(double *state, double dt, double *out_9094503671864348345) {
  f_fun(state,  dt, out_9094503671864348345);
}
void pose_F_fun(double *state, double dt, double *out_1312959600226932432) {
  F_fun(state,  dt, out_1312959600226932432);
}
void pose_h_4(double *state, double *unused, double *out_6400948089178504221) {
  h_4(state, unused, out_6400948089178504221);
}
void pose_H_4(double *state, double *unused, double *out_3419471307660667524) {
  H_4(state, unused, out_3419471307660667524);
}
void pose_h_10(double *state, double *unused, double *out_8540054287512262719) {
  h_10(state, unused, out_8540054287512262719);
}
void pose_H_10(double *state, double *unused, double *out_5231659216258162963) {
  H_10(state, unused, out_5231659216258162963);
}
void pose_h_13(double *state, double *unused, double *out_7953441679753433349) {
  h_13(state, unused, out_7953441679753433349);
}
void pose_H_13(double *state, double *unused, double *out_207197482328334723) {
  H_13(state, unused, out_207197482328334723);
}
void pose_h_14(double *state, double *unused, double *out_8785755176393893631) {
  h_14(state, unused, out_8785755176393893631);
}
void pose_H_14(double *state, double *unused, double *out_543769548678817005) {
  H_14(state, unused, out_543769548678817005);
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
