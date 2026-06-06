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
void err_fun(double *nom_x, double *delta_x, double *out_3524911542636248309) {
   out_3524911542636248309[0] = delta_x[0] + nom_x[0];
   out_3524911542636248309[1] = delta_x[1] + nom_x[1];
   out_3524911542636248309[2] = delta_x[2] + nom_x[2];
   out_3524911542636248309[3] = delta_x[3] + nom_x[3];
   out_3524911542636248309[4] = delta_x[4] + nom_x[4];
   out_3524911542636248309[5] = delta_x[5] + nom_x[5];
   out_3524911542636248309[6] = delta_x[6] + nom_x[6];
   out_3524911542636248309[7] = delta_x[7] + nom_x[7];
   out_3524911542636248309[8] = delta_x[8] + nom_x[8];
   out_3524911542636248309[9] = delta_x[9] + nom_x[9];
   out_3524911542636248309[10] = delta_x[10] + nom_x[10];
   out_3524911542636248309[11] = delta_x[11] + nom_x[11];
   out_3524911542636248309[12] = delta_x[12] + nom_x[12];
   out_3524911542636248309[13] = delta_x[13] + nom_x[13];
   out_3524911542636248309[14] = delta_x[14] + nom_x[14];
   out_3524911542636248309[15] = delta_x[15] + nom_x[15];
   out_3524911542636248309[16] = delta_x[16] + nom_x[16];
   out_3524911542636248309[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_9101758542759318568) {
   out_9101758542759318568[0] = -nom_x[0] + true_x[0];
   out_9101758542759318568[1] = -nom_x[1] + true_x[1];
   out_9101758542759318568[2] = -nom_x[2] + true_x[2];
   out_9101758542759318568[3] = -nom_x[3] + true_x[3];
   out_9101758542759318568[4] = -nom_x[4] + true_x[4];
   out_9101758542759318568[5] = -nom_x[5] + true_x[5];
   out_9101758542759318568[6] = -nom_x[6] + true_x[6];
   out_9101758542759318568[7] = -nom_x[7] + true_x[7];
   out_9101758542759318568[8] = -nom_x[8] + true_x[8];
   out_9101758542759318568[9] = -nom_x[9] + true_x[9];
   out_9101758542759318568[10] = -nom_x[10] + true_x[10];
   out_9101758542759318568[11] = -nom_x[11] + true_x[11];
   out_9101758542759318568[12] = -nom_x[12] + true_x[12];
   out_9101758542759318568[13] = -nom_x[13] + true_x[13];
   out_9101758542759318568[14] = -nom_x[14] + true_x[14];
   out_9101758542759318568[15] = -nom_x[15] + true_x[15];
   out_9101758542759318568[16] = -nom_x[16] + true_x[16];
   out_9101758542759318568[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_202451455870783186) {
   out_202451455870783186[0] = 1.0;
   out_202451455870783186[1] = 0.0;
   out_202451455870783186[2] = 0.0;
   out_202451455870783186[3] = 0.0;
   out_202451455870783186[4] = 0.0;
   out_202451455870783186[5] = 0.0;
   out_202451455870783186[6] = 0.0;
   out_202451455870783186[7] = 0.0;
   out_202451455870783186[8] = 0.0;
   out_202451455870783186[9] = 0.0;
   out_202451455870783186[10] = 0.0;
   out_202451455870783186[11] = 0.0;
   out_202451455870783186[12] = 0.0;
   out_202451455870783186[13] = 0.0;
   out_202451455870783186[14] = 0.0;
   out_202451455870783186[15] = 0.0;
   out_202451455870783186[16] = 0.0;
   out_202451455870783186[17] = 0.0;
   out_202451455870783186[18] = 0.0;
   out_202451455870783186[19] = 1.0;
   out_202451455870783186[20] = 0.0;
   out_202451455870783186[21] = 0.0;
   out_202451455870783186[22] = 0.0;
   out_202451455870783186[23] = 0.0;
   out_202451455870783186[24] = 0.0;
   out_202451455870783186[25] = 0.0;
   out_202451455870783186[26] = 0.0;
   out_202451455870783186[27] = 0.0;
   out_202451455870783186[28] = 0.0;
   out_202451455870783186[29] = 0.0;
   out_202451455870783186[30] = 0.0;
   out_202451455870783186[31] = 0.0;
   out_202451455870783186[32] = 0.0;
   out_202451455870783186[33] = 0.0;
   out_202451455870783186[34] = 0.0;
   out_202451455870783186[35] = 0.0;
   out_202451455870783186[36] = 0.0;
   out_202451455870783186[37] = 0.0;
   out_202451455870783186[38] = 1.0;
   out_202451455870783186[39] = 0.0;
   out_202451455870783186[40] = 0.0;
   out_202451455870783186[41] = 0.0;
   out_202451455870783186[42] = 0.0;
   out_202451455870783186[43] = 0.0;
   out_202451455870783186[44] = 0.0;
   out_202451455870783186[45] = 0.0;
   out_202451455870783186[46] = 0.0;
   out_202451455870783186[47] = 0.0;
   out_202451455870783186[48] = 0.0;
   out_202451455870783186[49] = 0.0;
   out_202451455870783186[50] = 0.0;
   out_202451455870783186[51] = 0.0;
   out_202451455870783186[52] = 0.0;
   out_202451455870783186[53] = 0.0;
   out_202451455870783186[54] = 0.0;
   out_202451455870783186[55] = 0.0;
   out_202451455870783186[56] = 0.0;
   out_202451455870783186[57] = 1.0;
   out_202451455870783186[58] = 0.0;
   out_202451455870783186[59] = 0.0;
   out_202451455870783186[60] = 0.0;
   out_202451455870783186[61] = 0.0;
   out_202451455870783186[62] = 0.0;
   out_202451455870783186[63] = 0.0;
   out_202451455870783186[64] = 0.0;
   out_202451455870783186[65] = 0.0;
   out_202451455870783186[66] = 0.0;
   out_202451455870783186[67] = 0.0;
   out_202451455870783186[68] = 0.0;
   out_202451455870783186[69] = 0.0;
   out_202451455870783186[70] = 0.0;
   out_202451455870783186[71] = 0.0;
   out_202451455870783186[72] = 0.0;
   out_202451455870783186[73] = 0.0;
   out_202451455870783186[74] = 0.0;
   out_202451455870783186[75] = 0.0;
   out_202451455870783186[76] = 1.0;
   out_202451455870783186[77] = 0.0;
   out_202451455870783186[78] = 0.0;
   out_202451455870783186[79] = 0.0;
   out_202451455870783186[80] = 0.0;
   out_202451455870783186[81] = 0.0;
   out_202451455870783186[82] = 0.0;
   out_202451455870783186[83] = 0.0;
   out_202451455870783186[84] = 0.0;
   out_202451455870783186[85] = 0.0;
   out_202451455870783186[86] = 0.0;
   out_202451455870783186[87] = 0.0;
   out_202451455870783186[88] = 0.0;
   out_202451455870783186[89] = 0.0;
   out_202451455870783186[90] = 0.0;
   out_202451455870783186[91] = 0.0;
   out_202451455870783186[92] = 0.0;
   out_202451455870783186[93] = 0.0;
   out_202451455870783186[94] = 0.0;
   out_202451455870783186[95] = 1.0;
   out_202451455870783186[96] = 0.0;
   out_202451455870783186[97] = 0.0;
   out_202451455870783186[98] = 0.0;
   out_202451455870783186[99] = 0.0;
   out_202451455870783186[100] = 0.0;
   out_202451455870783186[101] = 0.0;
   out_202451455870783186[102] = 0.0;
   out_202451455870783186[103] = 0.0;
   out_202451455870783186[104] = 0.0;
   out_202451455870783186[105] = 0.0;
   out_202451455870783186[106] = 0.0;
   out_202451455870783186[107] = 0.0;
   out_202451455870783186[108] = 0.0;
   out_202451455870783186[109] = 0.0;
   out_202451455870783186[110] = 0.0;
   out_202451455870783186[111] = 0.0;
   out_202451455870783186[112] = 0.0;
   out_202451455870783186[113] = 0.0;
   out_202451455870783186[114] = 1.0;
   out_202451455870783186[115] = 0.0;
   out_202451455870783186[116] = 0.0;
   out_202451455870783186[117] = 0.0;
   out_202451455870783186[118] = 0.0;
   out_202451455870783186[119] = 0.0;
   out_202451455870783186[120] = 0.0;
   out_202451455870783186[121] = 0.0;
   out_202451455870783186[122] = 0.0;
   out_202451455870783186[123] = 0.0;
   out_202451455870783186[124] = 0.0;
   out_202451455870783186[125] = 0.0;
   out_202451455870783186[126] = 0.0;
   out_202451455870783186[127] = 0.0;
   out_202451455870783186[128] = 0.0;
   out_202451455870783186[129] = 0.0;
   out_202451455870783186[130] = 0.0;
   out_202451455870783186[131] = 0.0;
   out_202451455870783186[132] = 0.0;
   out_202451455870783186[133] = 1.0;
   out_202451455870783186[134] = 0.0;
   out_202451455870783186[135] = 0.0;
   out_202451455870783186[136] = 0.0;
   out_202451455870783186[137] = 0.0;
   out_202451455870783186[138] = 0.0;
   out_202451455870783186[139] = 0.0;
   out_202451455870783186[140] = 0.0;
   out_202451455870783186[141] = 0.0;
   out_202451455870783186[142] = 0.0;
   out_202451455870783186[143] = 0.0;
   out_202451455870783186[144] = 0.0;
   out_202451455870783186[145] = 0.0;
   out_202451455870783186[146] = 0.0;
   out_202451455870783186[147] = 0.0;
   out_202451455870783186[148] = 0.0;
   out_202451455870783186[149] = 0.0;
   out_202451455870783186[150] = 0.0;
   out_202451455870783186[151] = 0.0;
   out_202451455870783186[152] = 1.0;
   out_202451455870783186[153] = 0.0;
   out_202451455870783186[154] = 0.0;
   out_202451455870783186[155] = 0.0;
   out_202451455870783186[156] = 0.0;
   out_202451455870783186[157] = 0.0;
   out_202451455870783186[158] = 0.0;
   out_202451455870783186[159] = 0.0;
   out_202451455870783186[160] = 0.0;
   out_202451455870783186[161] = 0.0;
   out_202451455870783186[162] = 0.0;
   out_202451455870783186[163] = 0.0;
   out_202451455870783186[164] = 0.0;
   out_202451455870783186[165] = 0.0;
   out_202451455870783186[166] = 0.0;
   out_202451455870783186[167] = 0.0;
   out_202451455870783186[168] = 0.0;
   out_202451455870783186[169] = 0.0;
   out_202451455870783186[170] = 0.0;
   out_202451455870783186[171] = 1.0;
   out_202451455870783186[172] = 0.0;
   out_202451455870783186[173] = 0.0;
   out_202451455870783186[174] = 0.0;
   out_202451455870783186[175] = 0.0;
   out_202451455870783186[176] = 0.0;
   out_202451455870783186[177] = 0.0;
   out_202451455870783186[178] = 0.0;
   out_202451455870783186[179] = 0.0;
   out_202451455870783186[180] = 0.0;
   out_202451455870783186[181] = 0.0;
   out_202451455870783186[182] = 0.0;
   out_202451455870783186[183] = 0.0;
   out_202451455870783186[184] = 0.0;
   out_202451455870783186[185] = 0.0;
   out_202451455870783186[186] = 0.0;
   out_202451455870783186[187] = 0.0;
   out_202451455870783186[188] = 0.0;
   out_202451455870783186[189] = 0.0;
   out_202451455870783186[190] = 1.0;
   out_202451455870783186[191] = 0.0;
   out_202451455870783186[192] = 0.0;
   out_202451455870783186[193] = 0.0;
   out_202451455870783186[194] = 0.0;
   out_202451455870783186[195] = 0.0;
   out_202451455870783186[196] = 0.0;
   out_202451455870783186[197] = 0.0;
   out_202451455870783186[198] = 0.0;
   out_202451455870783186[199] = 0.0;
   out_202451455870783186[200] = 0.0;
   out_202451455870783186[201] = 0.0;
   out_202451455870783186[202] = 0.0;
   out_202451455870783186[203] = 0.0;
   out_202451455870783186[204] = 0.0;
   out_202451455870783186[205] = 0.0;
   out_202451455870783186[206] = 0.0;
   out_202451455870783186[207] = 0.0;
   out_202451455870783186[208] = 0.0;
   out_202451455870783186[209] = 1.0;
   out_202451455870783186[210] = 0.0;
   out_202451455870783186[211] = 0.0;
   out_202451455870783186[212] = 0.0;
   out_202451455870783186[213] = 0.0;
   out_202451455870783186[214] = 0.0;
   out_202451455870783186[215] = 0.0;
   out_202451455870783186[216] = 0.0;
   out_202451455870783186[217] = 0.0;
   out_202451455870783186[218] = 0.0;
   out_202451455870783186[219] = 0.0;
   out_202451455870783186[220] = 0.0;
   out_202451455870783186[221] = 0.0;
   out_202451455870783186[222] = 0.0;
   out_202451455870783186[223] = 0.0;
   out_202451455870783186[224] = 0.0;
   out_202451455870783186[225] = 0.0;
   out_202451455870783186[226] = 0.0;
   out_202451455870783186[227] = 0.0;
   out_202451455870783186[228] = 1.0;
   out_202451455870783186[229] = 0.0;
   out_202451455870783186[230] = 0.0;
   out_202451455870783186[231] = 0.0;
   out_202451455870783186[232] = 0.0;
   out_202451455870783186[233] = 0.0;
   out_202451455870783186[234] = 0.0;
   out_202451455870783186[235] = 0.0;
   out_202451455870783186[236] = 0.0;
   out_202451455870783186[237] = 0.0;
   out_202451455870783186[238] = 0.0;
   out_202451455870783186[239] = 0.0;
   out_202451455870783186[240] = 0.0;
   out_202451455870783186[241] = 0.0;
   out_202451455870783186[242] = 0.0;
   out_202451455870783186[243] = 0.0;
   out_202451455870783186[244] = 0.0;
   out_202451455870783186[245] = 0.0;
   out_202451455870783186[246] = 0.0;
   out_202451455870783186[247] = 1.0;
   out_202451455870783186[248] = 0.0;
   out_202451455870783186[249] = 0.0;
   out_202451455870783186[250] = 0.0;
   out_202451455870783186[251] = 0.0;
   out_202451455870783186[252] = 0.0;
   out_202451455870783186[253] = 0.0;
   out_202451455870783186[254] = 0.0;
   out_202451455870783186[255] = 0.0;
   out_202451455870783186[256] = 0.0;
   out_202451455870783186[257] = 0.0;
   out_202451455870783186[258] = 0.0;
   out_202451455870783186[259] = 0.0;
   out_202451455870783186[260] = 0.0;
   out_202451455870783186[261] = 0.0;
   out_202451455870783186[262] = 0.0;
   out_202451455870783186[263] = 0.0;
   out_202451455870783186[264] = 0.0;
   out_202451455870783186[265] = 0.0;
   out_202451455870783186[266] = 1.0;
   out_202451455870783186[267] = 0.0;
   out_202451455870783186[268] = 0.0;
   out_202451455870783186[269] = 0.0;
   out_202451455870783186[270] = 0.0;
   out_202451455870783186[271] = 0.0;
   out_202451455870783186[272] = 0.0;
   out_202451455870783186[273] = 0.0;
   out_202451455870783186[274] = 0.0;
   out_202451455870783186[275] = 0.0;
   out_202451455870783186[276] = 0.0;
   out_202451455870783186[277] = 0.0;
   out_202451455870783186[278] = 0.0;
   out_202451455870783186[279] = 0.0;
   out_202451455870783186[280] = 0.0;
   out_202451455870783186[281] = 0.0;
   out_202451455870783186[282] = 0.0;
   out_202451455870783186[283] = 0.0;
   out_202451455870783186[284] = 0.0;
   out_202451455870783186[285] = 1.0;
   out_202451455870783186[286] = 0.0;
   out_202451455870783186[287] = 0.0;
   out_202451455870783186[288] = 0.0;
   out_202451455870783186[289] = 0.0;
   out_202451455870783186[290] = 0.0;
   out_202451455870783186[291] = 0.0;
   out_202451455870783186[292] = 0.0;
   out_202451455870783186[293] = 0.0;
   out_202451455870783186[294] = 0.0;
   out_202451455870783186[295] = 0.0;
   out_202451455870783186[296] = 0.0;
   out_202451455870783186[297] = 0.0;
   out_202451455870783186[298] = 0.0;
   out_202451455870783186[299] = 0.0;
   out_202451455870783186[300] = 0.0;
   out_202451455870783186[301] = 0.0;
   out_202451455870783186[302] = 0.0;
   out_202451455870783186[303] = 0.0;
   out_202451455870783186[304] = 1.0;
   out_202451455870783186[305] = 0.0;
   out_202451455870783186[306] = 0.0;
   out_202451455870783186[307] = 0.0;
   out_202451455870783186[308] = 0.0;
   out_202451455870783186[309] = 0.0;
   out_202451455870783186[310] = 0.0;
   out_202451455870783186[311] = 0.0;
   out_202451455870783186[312] = 0.0;
   out_202451455870783186[313] = 0.0;
   out_202451455870783186[314] = 0.0;
   out_202451455870783186[315] = 0.0;
   out_202451455870783186[316] = 0.0;
   out_202451455870783186[317] = 0.0;
   out_202451455870783186[318] = 0.0;
   out_202451455870783186[319] = 0.0;
   out_202451455870783186[320] = 0.0;
   out_202451455870783186[321] = 0.0;
   out_202451455870783186[322] = 0.0;
   out_202451455870783186[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_3404078345216964699) {
   out_3404078345216964699[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_3404078345216964699[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_3404078345216964699[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_3404078345216964699[3] = dt*state[12] + state[3];
   out_3404078345216964699[4] = dt*state[13] + state[4];
   out_3404078345216964699[5] = dt*state[14] + state[5];
   out_3404078345216964699[6] = state[6];
   out_3404078345216964699[7] = state[7];
   out_3404078345216964699[8] = state[8];
   out_3404078345216964699[9] = state[9];
   out_3404078345216964699[10] = state[10];
   out_3404078345216964699[11] = state[11];
   out_3404078345216964699[12] = state[12];
   out_3404078345216964699[13] = state[13];
   out_3404078345216964699[14] = state[14];
   out_3404078345216964699[15] = state[15];
   out_3404078345216964699[16] = state[16];
   out_3404078345216964699[17] = state[17];
}
void F_fun(double *state, double dt, double *out_9161898751948597001) {
   out_9161898751948597001[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9161898751948597001[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9161898751948597001[2] = 0;
   out_9161898751948597001[3] = 0;
   out_9161898751948597001[4] = 0;
   out_9161898751948597001[5] = 0;
   out_9161898751948597001[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9161898751948597001[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9161898751948597001[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9161898751948597001[9] = 0;
   out_9161898751948597001[10] = 0;
   out_9161898751948597001[11] = 0;
   out_9161898751948597001[12] = 0;
   out_9161898751948597001[13] = 0;
   out_9161898751948597001[14] = 0;
   out_9161898751948597001[15] = 0;
   out_9161898751948597001[16] = 0;
   out_9161898751948597001[17] = 0;
   out_9161898751948597001[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9161898751948597001[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9161898751948597001[20] = 0;
   out_9161898751948597001[21] = 0;
   out_9161898751948597001[22] = 0;
   out_9161898751948597001[23] = 0;
   out_9161898751948597001[24] = 0;
   out_9161898751948597001[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9161898751948597001[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9161898751948597001[27] = 0;
   out_9161898751948597001[28] = 0;
   out_9161898751948597001[29] = 0;
   out_9161898751948597001[30] = 0;
   out_9161898751948597001[31] = 0;
   out_9161898751948597001[32] = 0;
   out_9161898751948597001[33] = 0;
   out_9161898751948597001[34] = 0;
   out_9161898751948597001[35] = 0;
   out_9161898751948597001[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9161898751948597001[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9161898751948597001[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9161898751948597001[39] = 0;
   out_9161898751948597001[40] = 0;
   out_9161898751948597001[41] = 0;
   out_9161898751948597001[42] = 0;
   out_9161898751948597001[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9161898751948597001[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9161898751948597001[45] = 0;
   out_9161898751948597001[46] = 0;
   out_9161898751948597001[47] = 0;
   out_9161898751948597001[48] = 0;
   out_9161898751948597001[49] = 0;
   out_9161898751948597001[50] = 0;
   out_9161898751948597001[51] = 0;
   out_9161898751948597001[52] = 0;
   out_9161898751948597001[53] = 0;
   out_9161898751948597001[54] = 0;
   out_9161898751948597001[55] = 0;
   out_9161898751948597001[56] = 0;
   out_9161898751948597001[57] = 1;
   out_9161898751948597001[58] = 0;
   out_9161898751948597001[59] = 0;
   out_9161898751948597001[60] = 0;
   out_9161898751948597001[61] = 0;
   out_9161898751948597001[62] = 0;
   out_9161898751948597001[63] = 0;
   out_9161898751948597001[64] = 0;
   out_9161898751948597001[65] = 0;
   out_9161898751948597001[66] = dt;
   out_9161898751948597001[67] = 0;
   out_9161898751948597001[68] = 0;
   out_9161898751948597001[69] = 0;
   out_9161898751948597001[70] = 0;
   out_9161898751948597001[71] = 0;
   out_9161898751948597001[72] = 0;
   out_9161898751948597001[73] = 0;
   out_9161898751948597001[74] = 0;
   out_9161898751948597001[75] = 0;
   out_9161898751948597001[76] = 1;
   out_9161898751948597001[77] = 0;
   out_9161898751948597001[78] = 0;
   out_9161898751948597001[79] = 0;
   out_9161898751948597001[80] = 0;
   out_9161898751948597001[81] = 0;
   out_9161898751948597001[82] = 0;
   out_9161898751948597001[83] = 0;
   out_9161898751948597001[84] = 0;
   out_9161898751948597001[85] = dt;
   out_9161898751948597001[86] = 0;
   out_9161898751948597001[87] = 0;
   out_9161898751948597001[88] = 0;
   out_9161898751948597001[89] = 0;
   out_9161898751948597001[90] = 0;
   out_9161898751948597001[91] = 0;
   out_9161898751948597001[92] = 0;
   out_9161898751948597001[93] = 0;
   out_9161898751948597001[94] = 0;
   out_9161898751948597001[95] = 1;
   out_9161898751948597001[96] = 0;
   out_9161898751948597001[97] = 0;
   out_9161898751948597001[98] = 0;
   out_9161898751948597001[99] = 0;
   out_9161898751948597001[100] = 0;
   out_9161898751948597001[101] = 0;
   out_9161898751948597001[102] = 0;
   out_9161898751948597001[103] = 0;
   out_9161898751948597001[104] = dt;
   out_9161898751948597001[105] = 0;
   out_9161898751948597001[106] = 0;
   out_9161898751948597001[107] = 0;
   out_9161898751948597001[108] = 0;
   out_9161898751948597001[109] = 0;
   out_9161898751948597001[110] = 0;
   out_9161898751948597001[111] = 0;
   out_9161898751948597001[112] = 0;
   out_9161898751948597001[113] = 0;
   out_9161898751948597001[114] = 1;
   out_9161898751948597001[115] = 0;
   out_9161898751948597001[116] = 0;
   out_9161898751948597001[117] = 0;
   out_9161898751948597001[118] = 0;
   out_9161898751948597001[119] = 0;
   out_9161898751948597001[120] = 0;
   out_9161898751948597001[121] = 0;
   out_9161898751948597001[122] = 0;
   out_9161898751948597001[123] = 0;
   out_9161898751948597001[124] = 0;
   out_9161898751948597001[125] = 0;
   out_9161898751948597001[126] = 0;
   out_9161898751948597001[127] = 0;
   out_9161898751948597001[128] = 0;
   out_9161898751948597001[129] = 0;
   out_9161898751948597001[130] = 0;
   out_9161898751948597001[131] = 0;
   out_9161898751948597001[132] = 0;
   out_9161898751948597001[133] = 1;
   out_9161898751948597001[134] = 0;
   out_9161898751948597001[135] = 0;
   out_9161898751948597001[136] = 0;
   out_9161898751948597001[137] = 0;
   out_9161898751948597001[138] = 0;
   out_9161898751948597001[139] = 0;
   out_9161898751948597001[140] = 0;
   out_9161898751948597001[141] = 0;
   out_9161898751948597001[142] = 0;
   out_9161898751948597001[143] = 0;
   out_9161898751948597001[144] = 0;
   out_9161898751948597001[145] = 0;
   out_9161898751948597001[146] = 0;
   out_9161898751948597001[147] = 0;
   out_9161898751948597001[148] = 0;
   out_9161898751948597001[149] = 0;
   out_9161898751948597001[150] = 0;
   out_9161898751948597001[151] = 0;
   out_9161898751948597001[152] = 1;
   out_9161898751948597001[153] = 0;
   out_9161898751948597001[154] = 0;
   out_9161898751948597001[155] = 0;
   out_9161898751948597001[156] = 0;
   out_9161898751948597001[157] = 0;
   out_9161898751948597001[158] = 0;
   out_9161898751948597001[159] = 0;
   out_9161898751948597001[160] = 0;
   out_9161898751948597001[161] = 0;
   out_9161898751948597001[162] = 0;
   out_9161898751948597001[163] = 0;
   out_9161898751948597001[164] = 0;
   out_9161898751948597001[165] = 0;
   out_9161898751948597001[166] = 0;
   out_9161898751948597001[167] = 0;
   out_9161898751948597001[168] = 0;
   out_9161898751948597001[169] = 0;
   out_9161898751948597001[170] = 0;
   out_9161898751948597001[171] = 1;
   out_9161898751948597001[172] = 0;
   out_9161898751948597001[173] = 0;
   out_9161898751948597001[174] = 0;
   out_9161898751948597001[175] = 0;
   out_9161898751948597001[176] = 0;
   out_9161898751948597001[177] = 0;
   out_9161898751948597001[178] = 0;
   out_9161898751948597001[179] = 0;
   out_9161898751948597001[180] = 0;
   out_9161898751948597001[181] = 0;
   out_9161898751948597001[182] = 0;
   out_9161898751948597001[183] = 0;
   out_9161898751948597001[184] = 0;
   out_9161898751948597001[185] = 0;
   out_9161898751948597001[186] = 0;
   out_9161898751948597001[187] = 0;
   out_9161898751948597001[188] = 0;
   out_9161898751948597001[189] = 0;
   out_9161898751948597001[190] = 1;
   out_9161898751948597001[191] = 0;
   out_9161898751948597001[192] = 0;
   out_9161898751948597001[193] = 0;
   out_9161898751948597001[194] = 0;
   out_9161898751948597001[195] = 0;
   out_9161898751948597001[196] = 0;
   out_9161898751948597001[197] = 0;
   out_9161898751948597001[198] = 0;
   out_9161898751948597001[199] = 0;
   out_9161898751948597001[200] = 0;
   out_9161898751948597001[201] = 0;
   out_9161898751948597001[202] = 0;
   out_9161898751948597001[203] = 0;
   out_9161898751948597001[204] = 0;
   out_9161898751948597001[205] = 0;
   out_9161898751948597001[206] = 0;
   out_9161898751948597001[207] = 0;
   out_9161898751948597001[208] = 0;
   out_9161898751948597001[209] = 1;
   out_9161898751948597001[210] = 0;
   out_9161898751948597001[211] = 0;
   out_9161898751948597001[212] = 0;
   out_9161898751948597001[213] = 0;
   out_9161898751948597001[214] = 0;
   out_9161898751948597001[215] = 0;
   out_9161898751948597001[216] = 0;
   out_9161898751948597001[217] = 0;
   out_9161898751948597001[218] = 0;
   out_9161898751948597001[219] = 0;
   out_9161898751948597001[220] = 0;
   out_9161898751948597001[221] = 0;
   out_9161898751948597001[222] = 0;
   out_9161898751948597001[223] = 0;
   out_9161898751948597001[224] = 0;
   out_9161898751948597001[225] = 0;
   out_9161898751948597001[226] = 0;
   out_9161898751948597001[227] = 0;
   out_9161898751948597001[228] = 1;
   out_9161898751948597001[229] = 0;
   out_9161898751948597001[230] = 0;
   out_9161898751948597001[231] = 0;
   out_9161898751948597001[232] = 0;
   out_9161898751948597001[233] = 0;
   out_9161898751948597001[234] = 0;
   out_9161898751948597001[235] = 0;
   out_9161898751948597001[236] = 0;
   out_9161898751948597001[237] = 0;
   out_9161898751948597001[238] = 0;
   out_9161898751948597001[239] = 0;
   out_9161898751948597001[240] = 0;
   out_9161898751948597001[241] = 0;
   out_9161898751948597001[242] = 0;
   out_9161898751948597001[243] = 0;
   out_9161898751948597001[244] = 0;
   out_9161898751948597001[245] = 0;
   out_9161898751948597001[246] = 0;
   out_9161898751948597001[247] = 1;
   out_9161898751948597001[248] = 0;
   out_9161898751948597001[249] = 0;
   out_9161898751948597001[250] = 0;
   out_9161898751948597001[251] = 0;
   out_9161898751948597001[252] = 0;
   out_9161898751948597001[253] = 0;
   out_9161898751948597001[254] = 0;
   out_9161898751948597001[255] = 0;
   out_9161898751948597001[256] = 0;
   out_9161898751948597001[257] = 0;
   out_9161898751948597001[258] = 0;
   out_9161898751948597001[259] = 0;
   out_9161898751948597001[260] = 0;
   out_9161898751948597001[261] = 0;
   out_9161898751948597001[262] = 0;
   out_9161898751948597001[263] = 0;
   out_9161898751948597001[264] = 0;
   out_9161898751948597001[265] = 0;
   out_9161898751948597001[266] = 1;
   out_9161898751948597001[267] = 0;
   out_9161898751948597001[268] = 0;
   out_9161898751948597001[269] = 0;
   out_9161898751948597001[270] = 0;
   out_9161898751948597001[271] = 0;
   out_9161898751948597001[272] = 0;
   out_9161898751948597001[273] = 0;
   out_9161898751948597001[274] = 0;
   out_9161898751948597001[275] = 0;
   out_9161898751948597001[276] = 0;
   out_9161898751948597001[277] = 0;
   out_9161898751948597001[278] = 0;
   out_9161898751948597001[279] = 0;
   out_9161898751948597001[280] = 0;
   out_9161898751948597001[281] = 0;
   out_9161898751948597001[282] = 0;
   out_9161898751948597001[283] = 0;
   out_9161898751948597001[284] = 0;
   out_9161898751948597001[285] = 1;
   out_9161898751948597001[286] = 0;
   out_9161898751948597001[287] = 0;
   out_9161898751948597001[288] = 0;
   out_9161898751948597001[289] = 0;
   out_9161898751948597001[290] = 0;
   out_9161898751948597001[291] = 0;
   out_9161898751948597001[292] = 0;
   out_9161898751948597001[293] = 0;
   out_9161898751948597001[294] = 0;
   out_9161898751948597001[295] = 0;
   out_9161898751948597001[296] = 0;
   out_9161898751948597001[297] = 0;
   out_9161898751948597001[298] = 0;
   out_9161898751948597001[299] = 0;
   out_9161898751948597001[300] = 0;
   out_9161898751948597001[301] = 0;
   out_9161898751948597001[302] = 0;
   out_9161898751948597001[303] = 0;
   out_9161898751948597001[304] = 1;
   out_9161898751948597001[305] = 0;
   out_9161898751948597001[306] = 0;
   out_9161898751948597001[307] = 0;
   out_9161898751948597001[308] = 0;
   out_9161898751948597001[309] = 0;
   out_9161898751948597001[310] = 0;
   out_9161898751948597001[311] = 0;
   out_9161898751948597001[312] = 0;
   out_9161898751948597001[313] = 0;
   out_9161898751948597001[314] = 0;
   out_9161898751948597001[315] = 0;
   out_9161898751948597001[316] = 0;
   out_9161898751948597001[317] = 0;
   out_9161898751948597001[318] = 0;
   out_9161898751948597001[319] = 0;
   out_9161898751948597001[320] = 0;
   out_9161898751948597001[321] = 0;
   out_9161898751948597001[322] = 0;
   out_9161898751948597001[323] = 1;
}
void h_4(double *state, double *unused, double *out_3298849734810867951) {
   out_3298849734810867951[0] = state[6] + state[9];
   out_3298849734810867951[1] = state[7] + state[10];
   out_3298849734810867951[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3476673534661732439) {
   out_3476673534661732439[0] = 0;
   out_3476673534661732439[1] = 0;
   out_3476673534661732439[2] = 0;
   out_3476673534661732439[3] = 0;
   out_3476673534661732439[4] = 0;
   out_3476673534661732439[5] = 0;
   out_3476673534661732439[6] = 1;
   out_3476673534661732439[7] = 0;
   out_3476673534661732439[8] = 0;
   out_3476673534661732439[9] = 1;
   out_3476673534661732439[10] = 0;
   out_3476673534661732439[11] = 0;
   out_3476673534661732439[12] = 0;
   out_3476673534661732439[13] = 0;
   out_3476673534661732439[14] = 0;
   out_3476673534661732439[15] = 0;
   out_3476673534661732439[16] = 0;
   out_3476673534661732439[17] = 0;
   out_3476673534661732439[18] = 0;
   out_3476673534661732439[19] = 0;
   out_3476673534661732439[20] = 0;
   out_3476673534661732439[21] = 0;
   out_3476673534661732439[22] = 0;
   out_3476673534661732439[23] = 0;
   out_3476673534661732439[24] = 0;
   out_3476673534661732439[25] = 1;
   out_3476673534661732439[26] = 0;
   out_3476673534661732439[27] = 0;
   out_3476673534661732439[28] = 1;
   out_3476673534661732439[29] = 0;
   out_3476673534661732439[30] = 0;
   out_3476673534661732439[31] = 0;
   out_3476673534661732439[32] = 0;
   out_3476673534661732439[33] = 0;
   out_3476673534661732439[34] = 0;
   out_3476673534661732439[35] = 0;
   out_3476673534661732439[36] = 0;
   out_3476673534661732439[37] = 0;
   out_3476673534661732439[38] = 0;
   out_3476673534661732439[39] = 0;
   out_3476673534661732439[40] = 0;
   out_3476673534661732439[41] = 0;
   out_3476673534661732439[42] = 0;
   out_3476673534661732439[43] = 0;
   out_3476673534661732439[44] = 1;
   out_3476673534661732439[45] = 0;
   out_3476673534661732439[46] = 0;
   out_3476673534661732439[47] = 1;
   out_3476673534661732439[48] = 0;
   out_3476673534661732439[49] = 0;
   out_3476673534661732439[50] = 0;
   out_3476673534661732439[51] = 0;
   out_3476673534661732439[52] = 0;
   out_3476673534661732439[53] = 0;
}
void h_10(double *state, double *unused, double *out_1490778051551919602) {
   out_1490778051551919602[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1490778051551919602[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1490778051551919602[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3065010150012391749) {
   out_3065010150012391749[0] = 0;
   out_3065010150012391749[1] = 9.8100000000000005*cos(state[1]);
   out_3065010150012391749[2] = 0;
   out_3065010150012391749[3] = 0;
   out_3065010150012391749[4] = -state[8];
   out_3065010150012391749[5] = state[7];
   out_3065010150012391749[6] = 0;
   out_3065010150012391749[7] = state[5];
   out_3065010150012391749[8] = -state[4];
   out_3065010150012391749[9] = 0;
   out_3065010150012391749[10] = 0;
   out_3065010150012391749[11] = 0;
   out_3065010150012391749[12] = 1;
   out_3065010150012391749[13] = 0;
   out_3065010150012391749[14] = 0;
   out_3065010150012391749[15] = 1;
   out_3065010150012391749[16] = 0;
   out_3065010150012391749[17] = 0;
   out_3065010150012391749[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3065010150012391749[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3065010150012391749[20] = 0;
   out_3065010150012391749[21] = state[8];
   out_3065010150012391749[22] = 0;
   out_3065010150012391749[23] = -state[6];
   out_3065010150012391749[24] = -state[5];
   out_3065010150012391749[25] = 0;
   out_3065010150012391749[26] = state[3];
   out_3065010150012391749[27] = 0;
   out_3065010150012391749[28] = 0;
   out_3065010150012391749[29] = 0;
   out_3065010150012391749[30] = 0;
   out_3065010150012391749[31] = 1;
   out_3065010150012391749[32] = 0;
   out_3065010150012391749[33] = 0;
   out_3065010150012391749[34] = 1;
   out_3065010150012391749[35] = 0;
   out_3065010150012391749[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3065010150012391749[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3065010150012391749[38] = 0;
   out_3065010150012391749[39] = -state[7];
   out_3065010150012391749[40] = state[6];
   out_3065010150012391749[41] = 0;
   out_3065010150012391749[42] = state[4];
   out_3065010150012391749[43] = -state[3];
   out_3065010150012391749[44] = 0;
   out_3065010150012391749[45] = 0;
   out_3065010150012391749[46] = 0;
   out_3065010150012391749[47] = 0;
   out_3065010150012391749[48] = 0;
   out_3065010150012391749[49] = 0;
   out_3065010150012391749[50] = 1;
   out_3065010150012391749[51] = 0;
   out_3065010150012391749[52] = 0;
   out_3065010150012391749[53] = 1;
}
void h_13(double *state, double *unused, double *out_2293000846655251698) {
   out_2293000846655251698[0] = state[3];
   out_2293000846655251698[1] = state[4];
   out_2293000846655251698[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4133957673654968490) {
   out_4133957673654968490[0] = 0;
   out_4133957673654968490[1] = 0;
   out_4133957673654968490[2] = 0;
   out_4133957673654968490[3] = 1;
   out_4133957673654968490[4] = 0;
   out_4133957673654968490[5] = 0;
   out_4133957673654968490[6] = 0;
   out_4133957673654968490[7] = 0;
   out_4133957673654968490[8] = 0;
   out_4133957673654968490[9] = 0;
   out_4133957673654968490[10] = 0;
   out_4133957673654968490[11] = 0;
   out_4133957673654968490[12] = 0;
   out_4133957673654968490[13] = 0;
   out_4133957673654968490[14] = 0;
   out_4133957673654968490[15] = 0;
   out_4133957673654968490[16] = 0;
   out_4133957673654968490[17] = 0;
   out_4133957673654968490[18] = 0;
   out_4133957673654968490[19] = 0;
   out_4133957673654968490[20] = 0;
   out_4133957673654968490[21] = 0;
   out_4133957673654968490[22] = 1;
   out_4133957673654968490[23] = 0;
   out_4133957673654968490[24] = 0;
   out_4133957673654968490[25] = 0;
   out_4133957673654968490[26] = 0;
   out_4133957673654968490[27] = 0;
   out_4133957673654968490[28] = 0;
   out_4133957673654968490[29] = 0;
   out_4133957673654968490[30] = 0;
   out_4133957673654968490[31] = 0;
   out_4133957673654968490[32] = 0;
   out_4133957673654968490[33] = 0;
   out_4133957673654968490[34] = 0;
   out_4133957673654968490[35] = 0;
   out_4133957673654968490[36] = 0;
   out_4133957673654968490[37] = 0;
   out_4133957673654968490[38] = 0;
   out_4133957673654968490[39] = 0;
   out_4133957673654968490[40] = 0;
   out_4133957673654968490[41] = 1;
   out_4133957673654968490[42] = 0;
   out_4133957673654968490[43] = 0;
   out_4133957673654968490[44] = 0;
   out_4133957673654968490[45] = 0;
   out_4133957673654968490[46] = 0;
   out_4133957673654968490[47] = 0;
   out_4133957673654968490[48] = 0;
   out_4133957673654968490[49] = 0;
   out_4133957673654968490[50] = 0;
   out_4133957673654968490[51] = 0;
   out_4133957673654968490[52] = 0;
   out_4133957673654968490[53] = 0;
}
void h_14(double *state, double *unused, double *out_6732417031145183728) {
   out_6732417031145183728[0] = state[6];
   out_6732417031145183728[1] = state[7];
   out_6732417031145183728[2] = state[8];
}
void H_14(double *state, double *unused, double *out_486567321677752090) {
   out_486567321677752090[0] = 0;
   out_486567321677752090[1] = 0;
   out_486567321677752090[2] = 0;
   out_486567321677752090[3] = 0;
   out_486567321677752090[4] = 0;
   out_486567321677752090[5] = 0;
   out_486567321677752090[6] = 1;
   out_486567321677752090[7] = 0;
   out_486567321677752090[8] = 0;
   out_486567321677752090[9] = 0;
   out_486567321677752090[10] = 0;
   out_486567321677752090[11] = 0;
   out_486567321677752090[12] = 0;
   out_486567321677752090[13] = 0;
   out_486567321677752090[14] = 0;
   out_486567321677752090[15] = 0;
   out_486567321677752090[16] = 0;
   out_486567321677752090[17] = 0;
   out_486567321677752090[18] = 0;
   out_486567321677752090[19] = 0;
   out_486567321677752090[20] = 0;
   out_486567321677752090[21] = 0;
   out_486567321677752090[22] = 0;
   out_486567321677752090[23] = 0;
   out_486567321677752090[24] = 0;
   out_486567321677752090[25] = 1;
   out_486567321677752090[26] = 0;
   out_486567321677752090[27] = 0;
   out_486567321677752090[28] = 0;
   out_486567321677752090[29] = 0;
   out_486567321677752090[30] = 0;
   out_486567321677752090[31] = 0;
   out_486567321677752090[32] = 0;
   out_486567321677752090[33] = 0;
   out_486567321677752090[34] = 0;
   out_486567321677752090[35] = 0;
   out_486567321677752090[36] = 0;
   out_486567321677752090[37] = 0;
   out_486567321677752090[38] = 0;
   out_486567321677752090[39] = 0;
   out_486567321677752090[40] = 0;
   out_486567321677752090[41] = 0;
   out_486567321677752090[42] = 0;
   out_486567321677752090[43] = 0;
   out_486567321677752090[44] = 1;
   out_486567321677752090[45] = 0;
   out_486567321677752090[46] = 0;
   out_486567321677752090[47] = 0;
   out_486567321677752090[48] = 0;
   out_486567321677752090[49] = 0;
   out_486567321677752090[50] = 0;
   out_486567321677752090[51] = 0;
   out_486567321677752090[52] = 0;
   out_486567321677752090[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3524911542636248309) {
  err_fun(nom_x, delta_x, out_3524911542636248309);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_9101758542759318568) {
  inv_err_fun(nom_x, true_x, out_9101758542759318568);
}
void pose_H_mod_fun(double *state, double *out_202451455870783186) {
  H_mod_fun(state, out_202451455870783186);
}
void pose_f_fun(double *state, double dt, double *out_3404078345216964699) {
  f_fun(state,  dt, out_3404078345216964699);
}
void pose_F_fun(double *state, double dt, double *out_9161898751948597001) {
  F_fun(state,  dt, out_9161898751948597001);
}
void pose_h_4(double *state, double *unused, double *out_3298849734810867951) {
  h_4(state, unused, out_3298849734810867951);
}
void pose_H_4(double *state, double *unused, double *out_3476673534661732439) {
  H_4(state, unused, out_3476673534661732439);
}
void pose_h_10(double *state, double *unused, double *out_1490778051551919602) {
  h_10(state, unused, out_1490778051551919602);
}
void pose_H_10(double *state, double *unused, double *out_3065010150012391749) {
  H_10(state, unused, out_3065010150012391749);
}
void pose_h_13(double *state, double *unused, double *out_2293000846655251698) {
  h_13(state, unused, out_2293000846655251698);
}
void pose_H_13(double *state, double *unused, double *out_4133957673654968490) {
  H_13(state, unused, out_4133957673654968490);
}
void pose_h_14(double *state, double *unused, double *out_6732417031145183728) {
  h_14(state, unused, out_6732417031145183728);
}
void pose_H_14(double *state, double *unused, double *out_486567321677752090) {
  H_14(state, unused, out_486567321677752090);
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
