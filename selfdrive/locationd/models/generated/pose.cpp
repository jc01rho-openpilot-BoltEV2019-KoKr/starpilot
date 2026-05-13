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
void err_fun(double *nom_x, double *delta_x, double *out_1909500707924070274) {
   out_1909500707924070274[0] = delta_x[0] + nom_x[0];
   out_1909500707924070274[1] = delta_x[1] + nom_x[1];
   out_1909500707924070274[2] = delta_x[2] + nom_x[2];
   out_1909500707924070274[3] = delta_x[3] + nom_x[3];
   out_1909500707924070274[4] = delta_x[4] + nom_x[4];
   out_1909500707924070274[5] = delta_x[5] + nom_x[5];
   out_1909500707924070274[6] = delta_x[6] + nom_x[6];
   out_1909500707924070274[7] = delta_x[7] + nom_x[7];
   out_1909500707924070274[8] = delta_x[8] + nom_x[8];
   out_1909500707924070274[9] = delta_x[9] + nom_x[9];
   out_1909500707924070274[10] = delta_x[10] + nom_x[10];
   out_1909500707924070274[11] = delta_x[11] + nom_x[11];
   out_1909500707924070274[12] = delta_x[12] + nom_x[12];
   out_1909500707924070274[13] = delta_x[13] + nom_x[13];
   out_1909500707924070274[14] = delta_x[14] + nom_x[14];
   out_1909500707924070274[15] = delta_x[15] + nom_x[15];
   out_1909500707924070274[16] = delta_x[16] + nom_x[16];
   out_1909500707924070274[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4767002163824434397) {
   out_4767002163824434397[0] = -nom_x[0] + true_x[0];
   out_4767002163824434397[1] = -nom_x[1] + true_x[1];
   out_4767002163824434397[2] = -nom_x[2] + true_x[2];
   out_4767002163824434397[3] = -nom_x[3] + true_x[3];
   out_4767002163824434397[4] = -nom_x[4] + true_x[4];
   out_4767002163824434397[5] = -nom_x[5] + true_x[5];
   out_4767002163824434397[6] = -nom_x[6] + true_x[6];
   out_4767002163824434397[7] = -nom_x[7] + true_x[7];
   out_4767002163824434397[8] = -nom_x[8] + true_x[8];
   out_4767002163824434397[9] = -nom_x[9] + true_x[9];
   out_4767002163824434397[10] = -nom_x[10] + true_x[10];
   out_4767002163824434397[11] = -nom_x[11] + true_x[11];
   out_4767002163824434397[12] = -nom_x[12] + true_x[12];
   out_4767002163824434397[13] = -nom_x[13] + true_x[13];
   out_4767002163824434397[14] = -nom_x[14] + true_x[14];
   out_4767002163824434397[15] = -nom_x[15] + true_x[15];
   out_4767002163824434397[16] = -nom_x[16] + true_x[16];
   out_4767002163824434397[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_2632577706224621837) {
   out_2632577706224621837[0] = 1.0;
   out_2632577706224621837[1] = 0.0;
   out_2632577706224621837[2] = 0.0;
   out_2632577706224621837[3] = 0.0;
   out_2632577706224621837[4] = 0.0;
   out_2632577706224621837[5] = 0.0;
   out_2632577706224621837[6] = 0.0;
   out_2632577706224621837[7] = 0.0;
   out_2632577706224621837[8] = 0.0;
   out_2632577706224621837[9] = 0.0;
   out_2632577706224621837[10] = 0.0;
   out_2632577706224621837[11] = 0.0;
   out_2632577706224621837[12] = 0.0;
   out_2632577706224621837[13] = 0.0;
   out_2632577706224621837[14] = 0.0;
   out_2632577706224621837[15] = 0.0;
   out_2632577706224621837[16] = 0.0;
   out_2632577706224621837[17] = 0.0;
   out_2632577706224621837[18] = 0.0;
   out_2632577706224621837[19] = 1.0;
   out_2632577706224621837[20] = 0.0;
   out_2632577706224621837[21] = 0.0;
   out_2632577706224621837[22] = 0.0;
   out_2632577706224621837[23] = 0.0;
   out_2632577706224621837[24] = 0.0;
   out_2632577706224621837[25] = 0.0;
   out_2632577706224621837[26] = 0.0;
   out_2632577706224621837[27] = 0.0;
   out_2632577706224621837[28] = 0.0;
   out_2632577706224621837[29] = 0.0;
   out_2632577706224621837[30] = 0.0;
   out_2632577706224621837[31] = 0.0;
   out_2632577706224621837[32] = 0.0;
   out_2632577706224621837[33] = 0.0;
   out_2632577706224621837[34] = 0.0;
   out_2632577706224621837[35] = 0.0;
   out_2632577706224621837[36] = 0.0;
   out_2632577706224621837[37] = 0.0;
   out_2632577706224621837[38] = 1.0;
   out_2632577706224621837[39] = 0.0;
   out_2632577706224621837[40] = 0.0;
   out_2632577706224621837[41] = 0.0;
   out_2632577706224621837[42] = 0.0;
   out_2632577706224621837[43] = 0.0;
   out_2632577706224621837[44] = 0.0;
   out_2632577706224621837[45] = 0.0;
   out_2632577706224621837[46] = 0.0;
   out_2632577706224621837[47] = 0.0;
   out_2632577706224621837[48] = 0.0;
   out_2632577706224621837[49] = 0.0;
   out_2632577706224621837[50] = 0.0;
   out_2632577706224621837[51] = 0.0;
   out_2632577706224621837[52] = 0.0;
   out_2632577706224621837[53] = 0.0;
   out_2632577706224621837[54] = 0.0;
   out_2632577706224621837[55] = 0.0;
   out_2632577706224621837[56] = 0.0;
   out_2632577706224621837[57] = 1.0;
   out_2632577706224621837[58] = 0.0;
   out_2632577706224621837[59] = 0.0;
   out_2632577706224621837[60] = 0.0;
   out_2632577706224621837[61] = 0.0;
   out_2632577706224621837[62] = 0.0;
   out_2632577706224621837[63] = 0.0;
   out_2632577706224621837[64] = 0.0;
   out_2632577706224621837[65] = 0.0;
   out_2632577706224621837[66] = 0.0;
   out_2632577706224621837[67] = 0.0;
   out_2632577706224621837[68] = 0.0;
   out_2632577706224621837[69] = 0.0;
   out_2632577706224621837[70] = 0.0;
   out_2632577706224621837[71] = 0.0;
   out_2632577706224621837[72] = 0.0;
   out_2632577706224621837[73] = 0.0;
   out_2632577706224621837[74] = 0.0;
   out_2632577706224621837[75] = 0.0;
   out_2632577706224621837[76] = 1.0;
   out_2632577706224621837[77] = 0.0;
   out_2632577706224621837[78] = 0.0;
   out_2632577706224621837[79] = 0.0;
   out_2632577706224621837[80] = 0.0;
   out_2632577706224621837[81] = 0.0;
   out_2632577706224621837[82] = 0.0;
   out_2632577706224621837[83] = 0.0;
   out_2632577706224621837[84] = 0.0;
   out_2632577706224621837[85] = 0.0;
   out_2632577706224621837[86] = 0.0;
   out_2632577706224621837[87] = 0.0;
   out_2632577706224621837[88] = 0.0;
   out_2632577706224621837[89] = 0.0;
   out_2632577706224621837[90] = 0.0;
   out_2632577706224621837[91] = 0.0;
   out_2632577706224621837[92] = 0.0;
   out_2632577706224621837[93] = 0.0;
   out_2632577706224621837[94] = 0.0;
   out_2632577706224621837[95] = 1.0;
   out_2632577706224621837[96] = 0.0;
   out_2632577706224621837[97] = 0.0;
   out_2632577706224621837[98] = 0.0;
   out_2632577706224621837[99] = 0.0;
   out_2632577706224621837[100] = 0.0;
   out_2632577706224621837[101] = 0.0;
   out_2632577706224621837[102] = 0.0;
   out_2632577706224621837[103] = 0.0;
   out_2632577706224621837[104] = 0.0;
   out_2632577706224621837[105] = 0.0;
   out_2632577706224621837[106] = 0.0;
   out_2632577706224621837[107] = 0.0;
   out_2632577706224621837[108] = 0.0;
   out_2632577706224621837[109] = 0.0;
   out_2632577706224621837[110] = 0.0;
   out_2632577706224621837[111] = 0.0;
   out_2632577706224621837[112] = 0.0;
   out_2632577706224621837[113] = 0.0;
   out_2632577706224621837[114] = 1.0;
   out_2632577706224621837[115] = 0.0;
   out_2632577706224621837[116] = 0.0;
   out_2632577706224621837[117] = 0.0;
   out_2632577706224621837[118] = 0.0;
   out_2632577706224621837[119] = 0.0;
   out_2632577706224621837[120] = 0.0;
   out_2632577706224621837[121] = 0.0;
   out_2632577706224621837[122] = 0.0;
   out_2632577706224621837[123] = 0.0;
   out_2632577706224621837[124] = 0.0;
   out_2632577706224621837[125] = 0.0;
   out_2632577706224621837[126] = 0.0;
   out_2632577706224621837[127] = 0.0;
   out_2632577706224621837[128] = 0.0;
   out_2632577706224621837[129] = 0.0;
   out_2632577706224621837[130] = 0.0;
   out_2632577706224621837[131] = 0.0;
   out_2632577706224621837[132] = 0.0;
   out_2632577706224621837[133] = 1.0;
   out_2632577706224621837[134] = 0.0;
   out_2632577706224621837[135] = 0.0;
   out_2632577706224621837[136] = 0.0;
   out_2632577706224621837[137] = 0.0;
   out_2632577706224621837[138] = 0.0;
   out_2632577706224621837[139] = 0.0;
   out_2632577706224621837[140] = 0.0;
   out_2632577706224621837[141] = 0.0;
   out_2632577706224621837[142] = 0.0;
   out_2632577706224621837[143] = 0.0;
   out_2632577706224621837[144] = 0.0;
   out_2632577706224621837[145] = 0.0;
   out_2632577706224621837[146] = 0.0;
   out_2632577706224621837[147] = 0.0;
   out_2632577706224621837[148] = 0.0;
   out_2632577706224621837[149] = 0.0;
   out_2632577706224621837[150] = 0.0;
   out_2632577706224621837[151] = 0.0;
   out_2632577706224621837[152] = 1.0;
   out_2632577706224621837[153] = 0.0;
   out_2632577706224621837[154] = 0.0;
   out_2632577706224621837[155] = 0.0;
   out_2632577706224621837[156] = 0.0;
   out_2632577706224621837[157] = 0.0;
   out_2632577706224621837[158] = 0.0;
   out_2632577706224621837[159] = 0.0;
   out_2632577706224621837[160] = 0.0;
   out_2632577706224621837[161] = 0.0;
   out_2632577706224621837[162] = 0.0;
   out_2632577706224621837[163] = 0.0;
   out_2632577706224621837[164] = 0.0;
   out_2632577706224621837[165] = 0.0;
   out_2632577706224621837[166] = 0.0;
   out_2632577706224621837[167] = 0.0;
   out_2632577706224621837[168] = 0.0;
   out_2632577706224621837[169] = 0.0;
   out_2632577706224621837[170] = 0.0;
   out_2632577706224621837[171] = 1.0;
   out_2632577706224621837[172] = 0.0;
   out_2632577706224621837[173] = 0.0;
   out_2632577706224621837[174] = 0.0;
   out_2632577706224621837[175] = 0.0;
   out_2632577706224621837[176] = 0.0;
   out_2632577706224621837[177] = 0.0;
   out_2632577706224621837[178] = 0.0;
   out_2632577706224621837[179] = 0.0;
   out_2632577706224621837[180] = 0.0;
   out_2632577706224621837[181] = 0.0;
   out_2632577706224621837[182] = 0.0;
   out_2632577706224621837[183] = 0.0;
   out_2632577706224621837[184] = 0.0;
   out_2632577706224621837[185] = 0.0;
   out_2632577706224621837[186] = 0.0;
   out_2632577706224621837[187] = 0.0;
   out_2632577706224621837[188] = 0.0;
   out_2632577706224621837[189] = 0.0;
   out_2632577706224621837[190] = 1.0;
   out_2632577706224621837[191] = 0.0;
   out_2632577706224621837[192] = 0.0;
   out_2632577706224621837[193] = 0.0;
   out_2632577706224621837[194] = 0.0;
   out_2632577706224621837[195] = 0.0;
   out_2632577706224621837[196] = 0.0;
   out_2632577706224621837[197] = 0.0;
   out_2632577706224621837[198] = 0.0;
   out_2632577706224621837[199] = 0.0;
   out_2632577706224621837[200] = 0.0;
   out_2632577706224621837[201] = 0.0;
   out_2632577706224621837[202] = 0.0;
   out_2632577706224621837[203] = 0.0;
   out_2632577706224621837[204] = 0.0;
   out_2632577706224621837[205] = 0.0;
   out_2632577706224621837[206] = 0.0;
   out_2632577706224621837[207] = 0.0;
   out_2632577706224621837[208] = 0.0;
   out_2632577706224621837[209] = 1.0;
   out_2632577706224621837[210] = 0.0;
   out_2632577706224621837[211] = 0.0;
   out_2632577706224621837[212] = 0.0;
   out_2632577706224621837[213] = 0.0;
   out_2632577706224621837[214] = 0.0;
   out_2632577706224621837[215] = 0.0;
   out_2632577706224621837[216] = 0.0;
   out_2632577706224621837[217] = 0.0;
   out_2632577706224621837[218] = 0.0;
   out_2632577706224621837[219] = 0.0;
   out_2632577706224621837[220] = 0.0;
   out_2632577706224621837[221] = 0.0;
   out_2632577706224621837[222] = 0.0;
   out_2632577706224621837[223] = 0.0;
   out_2632577706224621837[224] = 0.0;
   out_2632577706224621837[225] = 0.0;
   out_2632577706224621837[226] = 0.0;
   out_2632577706224621837[227] = 0.0;
   out_2632577706224621837[228] = 1.0;
   out_2632577706224621837[229] = 0.0;
   out_2632577706224621837[230] = 0.0;
   out_2632577706224621837[231] = 0.0;
   out_2632577706224621837[232] = 0.0;
   out_2632577706224621837[233] = 0.0;
   out_2632577706224621837[234] = 0.0;
   out_2632577706224621837[235] = 0.0;
   out_2632577706224621837[236] = 0.0;
   out_2632577706224621837[237] = 0.0;
   out_2632577706224621837[238] = 0.0;
   out_2632577706224621837[239] = 0.0;
   out_2632577706224621837[240] = 0.0;
   out_2632577706224621837[241] = 0.0;
   out_2632577706224621837[242] = 0.0;
   out_2632577706224621837[243] = 0.0;
   out_2632577706224621837[244] = 0.0;
   out_2632577706224621837[245] = 0.0;
   out_2632577706224621837[246] = 0.0;
   out_2632577706224621837[247] = 1.0;
   out_2632577706224621837[248] = 0.0;
   out_2632577706224621837[249] = 0.0;
   out_2632577706224621837[250] = 0.0;
   out_2632577706224621837[251] = 0.0;
   out_2632577706224621837[252] = 0.0;
   out_2632577706224621837[253] = 0.0;
   out_2632577706224621837[254] = 0.0;
   out_2632577706224621837[255] = 0.0;
   out_2632577706224621837[256] = 0.0;
   out_2632577706224621837[257] = 0.0;
   out_2632577706224621837[258] = 0.0;
   out_2632577706224621837[259] = 0.0;
   out_2632577706224621837[260] = 0.0;
   out_2632577706224621837[261] = 0.0;
   out_2632577706224621837[262] = 0.0;
   out_2632577706224621837[263] = 0.0;
   out_2632577706224621837[264] = 0.0;
   out_2632577706224621837[265] = 0.0;
   out_2632577706224621837[266] = 1.0;
   out_2632577706224621837[267] = 0.0;
   out_2632577706224621837[268] = 0.0;
   out_2632577706224621837[269] = 0.0;
   out_2632577706224621837[270] = 0.0;
   out_2632577706224621837[271] = 0.0;
   out_2632577706224621837[272] = 0.0;
   out_2632577706224621837[273] = 0.0;
   out_2632577706224621837[274] = 0.0;
   out_2632577706224621837[275] = 0.0;
   out_2632577706224621837[276] = 0.0;
   out_2632577706224621837[277] = 0.0;
   out_2632577706224621837[278] = 0.0;
   out_2632577706224621837[279] = 0.0;
   out_2632577706224621837[280] = 0.0;
   out_2632577706224621837[281] = 0.0;
   out_2632577706224621837[282] = 0.0;
   out_2632577706224621837[283] = 0.0;
   out_2632577706224621837[284] = 0.0;
   out_2632577706224621837[285] = 1.0;
   out_2632577706224621837[286] = 0.0;
   out_2632577706224621837[287] = 0.0;
   out_2632577706224621837[288] = 0.0;
   out_2632577706224621837[289] = 0.0;
   out_2632577706224621837[290] = 0.0;
   out_2632577706224621837[291] = 0.0;
   out_2632577706224621837[292] = 0.0;
   out_2632577706224621837[293] = 0.0;
   out_2632577706224621837[294] = 0.0;
   out_2632577706224621837[295] = 0.0;
   out_2632577706224621837[296] = 0.0;
   out_2632577706224621837[297] = 0.0;
   out_2632577706224621837[298] = 0.0;
   out_2632577706224621837[299] = 0.0;
   out_2632577706224621837[300] = 0.0;
   out_2632577706224621837[301] = 0.0;
   out_2632577706224621837[302] = 0.0;
   out_2632577706224621837[303] = 0.0;
   out_2632577706224621837[304] = 1.0;
   out_2632577706224621837[305] = 0.0;
   out_2632577706224621837[306] = 0.0;
   out_2632577706224621837[307] = 0.0;
   out_2632577706224621837[308] = 0.0;
   out_2632577706224621837[309] = 0.0;
   out_2632577706224621837[310] = 0.0;
   out_2632577706224621837[311] = 0.0;
   out_2632577706224621837[312] = 0.0;
   out_2632577706224621837[313] = 0.0;
   out_2632577706224621837[314] = 0.0;
   out_2632577706224621837[315] = 0.0;
   out_2632577706224621837[316] = 0.0;
   out_2632577706224621837[317] = 0.0;
   out_2632577706224621837[318] = 0.0;
   out_2632577706224621837[319] = 0.0;
   out_2632577706224621837[320] = 0.0;
   out_2632577706224621837[321] = 0.0;
   out_2632577706224621837[322] = 0.0;
   out_2632577706224621837[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_2193527682870666897) {
   out_2193527682870666897[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_2193527682870666897[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_2193527682870666897[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_2193527682870666897[3] = dt*state[12] + state[3];
   out_2193527682870666897[4] = dt*state[13] + state[4];
   out_2193527682870666897[5] = dt*state[14] + state[5];
   out_2193527682870666897[6] = state[6];
   out_2193527682870666897[7] = state[7];
   out_2193527682870666897[8] = state[8];
   out_2193527682870666897[9] = state[9];
   out_2193527682870666897[10] = state[10];
   out_2193527682870666897[11] = state[11];
   out_2193527682870666897[12] = state[12];
   out_2193527682870666897[13] = state[13];
   out_2193527682870666897[14] = state[14];
   out_2193527682870666897[15] = state[15];
   out_2193527682870666897[16] = state[16];
   out_2193527682870666897[17] = state[17];
}
void F_fun(double *state, double dt, double *out_7071521444289373248) {
   out_7071521444289373248[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7071521444289373248[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7071521444289373248[2] = 0;
   out_7071521444289373248[3] = 0;
   out_7071521444289373248[4] = 0;
   out_7071521444289373248[5] = 0;
   out_7071521444289373248[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7071521444289373248[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7071521444289373248[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7071521444289373248[9] = 0;
   out_7071521444289373248[10] = 0;
   out_7071521444289373248[11] = 0;
   out_7071521444289373248[12] = 0;
   out_7071521444289373248[13] = 0;
   out_7071521444289373248[14] = 0;
   out_7071521444289373248[15] = 0;
   out_7071521444289373248[16] = 0;
   out_7071521444289373248[17] = 0;
   out_7071521444289373248[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7071521444289373248[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7071521444289373248[20] = 0;
   out_7071521444289373248[21] = 0;
   out_7071521444289373248[22] = 0;
   out_7071521444289373248[23] = 0;
   out_7071521444289373248[24] = 0;
   out_7071521444289373248[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7071521444289373248[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7071521444289373248[27] = 0;
   out_7071521444289373248[28] = 0;
   out_7071521444289373248[29] = 0;
   out_7071521444289373248[30] = 0;
   out_7071521444289373248[31] = 0;
   out_7071521444289373248[32] = 0;
   out_7071521444289373248[33] = 0;
   out_7071521444289373248[34] = 0;
   out_7071521444289373248[35] = 0;
   out_7071521444289373248[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7071521444289373248[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7071521444289373248[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7071521444289373248[39] = 0;
   out_7071521444289373248[40] = 0;
   out_7071521444289373248[41] = 0;
   out_7071521444289373248[42] = 0;
   out_7071521444289373248[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7071521444289373248[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7071521444289373248[45] = 0;
   out_7071521444289373248[46] = 0;
   out_7071521444289373248[47] = 0;
   out_7071521444289373248[48] = 0;
   out_7071521444289373248[49] = 0;
   out_7071521444289373248[50] = 0;
   out_7071521444289373248[51] = 0;
   out_7071521444289373248[52] = 0;
   out_7071521444289373248[53] = 0;
   out_7071521444289373248[54] = 0;
   out_7071521444289373248[55] = 0;
   out_7071521444289373248[56] = 0;
   out_7071521444289373248[57] = 1;
   out_7071521444289373248[58] = 0;
   out_7071521444289373248[59] = 0;
   out_7071521444289373248[60] = 0;
   out_7071521444289373248[61] = 0;
   out_7071521444289373248[62] = 0;
   out_7071521444289373248[63] = 0;
   out_7071521444289373248[64] = 0;
   out_7071521444289373248[65] = 0;
   out_7071521444289373248[66] = dt;
   out_7071521444289373248[67] = 0;
   out_7071521444289373248[68] = 0;
   out_7071521444289373248[69] = 0;
   out_7071521444289373248[70] = 0;
   out_7071521444289373248[71] = 0;
   out_7071521444289373248[72] = 0;
   out_7071521444289373248[73] = 0;
   out_7071521444289373248[74] = 0;
   out_7071521444289373248[75] = 0;
   out_7071521444289373248[76] = 1;
   out_7071521444289373248[77] = 0;
   out_7071521444289373248[78] = 0;
   out_7071521444289373248[79] = 0;
   out_7071521444289373248[80] = 0;
   out_7071521444289373248[81] = 0;
   out_7071521444289373248[82] = 0;
   out_7071521444289373248[83] = 0;
   out_7071521444289373248[84] = 0;
   out_7071521444289373248[85] = dt;
   out_7071521444289373248[86] = 0;
   out_7071521444289373248[87] = 0;
   out_7071521444289373248[88] = 0;
   out_7071521444289373248[89] = 0;
   out_7071521444289373248[90] = 0;
   out_7071521444289373248[91] = 0;
   out_7071521444289373248[92] = 0;
   out_7071521444289373248[93] = 0;
   out_7071521444289373248[94] = 0;
   out_7071521444289373248[95] = 1;
   out_7071521444289373248[96] = 0;
   out_7071521444289373248[97] = 0;
   out_7071521444289373248[98] = 0;
   out_7071521444289373248[99] = 0;
   out_7071521444289373248[100] = 0;
   out_7071521444289373248[101] = 0;
   out_7071521444289373248[102] = 0;
   out_7071521444289373248[103] = 0;
   out_7071521444289373248[104] = dt;
   out_7071521444289373248[105] = 0;
   out_7071521444289373248[106] = 0;
   out_7071521444289373248[107] = 0;
   out_7071521444289373248[108] = 0;
   out_7071521444289373248[109] = 0;
   out_7071521444289373248[110] = 0;
   out_7071521444289373248[111] = 0;
   out_7071521444289373248[112] = 0;
   out_7071521444289373248[113] = 0;
   out_7071521444289373248[114] = 1;
   out_7071521444289373248[115] = 0;
   out_7071521444289373248[116] = 0;
   out_7071521444289373248[117] = 0;
   out_7071521444289373248[118] = 0;
   out_7071521444289373248[119] = 0;
   out_7071521444289373248[120] = 0;
   out_7071521444289373248[121] = 0;
   out_7071521444289373248[122] = 0;
   out_7071521444289373248[123] = 0;
   out_7071521444289373248[124] = 0;
   out_7071521444289373248[125] = 0;
   out_7071521444289373248[126] = 0;
   out_7071521444289373248[127] = 0;
   out_7071521444289373248[128] = 0;
   out_7071521444289373248[129] = 0;
   out_7071521444289373248[130] = 0;
   out_7071521444289373248[131] = 0;
   out_7071521444289373248[132] = 0;
   out_7071521444289373248[133] = 1;
   out_7071521444289373248[134] = 0;
   out_7071521444289373248[135] = 0;
   out_7071521444289373248[136] = 0;
   out_7071521444289373248[137] = 0;
   out_7071521444289373248[138] = 0;
   out_7071521444289373248[139] = 0;
   out_7071521444289373248[140] = 0;
   out_7071521444289373248[141] = 0;
   out_7071521444289373248[142] = 0;
   out_7071521444289373248[143] = 0;
   out_7071521444289373248[144] = 0;
   out_7071521444289373248[145] = 0;
   out_7071521444289373248[146] = 0;
   out_7071521444289373248[147] = 0;
   out_7071521444289373248[148] = 0;
   out_7071521444289373248[149] = 0;
   out_7071521444289373248[150] = 0;
   out_7071521444289373248[151] = 0;
   out_7071521444289373248[152] = 1;
   out_7071521444289373248[153] = 0;
   out_7071521444289373248[154] = 0;
   out_7071521444289373248[155] = 0;
   out_7071521444289373248[156] = 0;
   out_7071521444289373248[157] = 0;
   out_7071521444289373248[158] = 0;
   out_7071521444289373248[159] = 0;
   out_7071521444289373248[160] = 0;
   out_7071521444289373248[161] = 0;
   out_7071521444289373248[162] = 0;
   out_7071521444289373248[163] = 0;
   out_7071521444289373248[164] = 0;
   out_7071521444289373248[165] = 0;
   out_7071521444289373248[166] = 0;
   out_7071521444289373248[167] = 0;
   out_7071521444289373248[168] = 0;
   out_7071521444289373248[169] = 0;
   out_7071521444289373248[170] = 0;
   out_7071521444289373248[171] = 1;
   out_7071521444289373248[172] = 0;
   out_7071521444289373248[173] = 0;
   out_7071521444289373248[174] = 0;
   out_7071521444289373248[175] = 0;
   out_7071521444289373248[176] = 0;
   out_7071521444289373248[177] = 0;
   out_7071521444289373248[178] = 0;
   out_7071521444289373248[179] = 0;
   out_7071521444289373248[180] = 0;
   out_7071521444289373248[181] = 0;
   out_7071521444289373248[182] = 0;
   out_7071521444289373248[183] = 0;
   out_7071521444289373248[184] = 0;
   out_7071521444289373248[185] = 0;
   out_7071521444289373248[186] = 0;
   out_7071521444289373248[187] = 0;
   out_7071521444289373248[188] = 0;
   out_7071521444289373248[189] = 0;
   out_7071521444289373248[190] = 1;
   out_7071521444289373248[191] = 0;
   out_7071521444289373248[192] = 0;
   out_7071521444289373248[193] = 0;
   out_7071521444289373248[194] = 0;
   out_7071521444289373248[195] = 0;
   out_7071521444289373248[196] = 0;
   out_7071521444289373248[197] = 0;
   out_7071521444289373248[198] = 0;
   out_7071521444289373248[199] = 0;
   out_7071521444289373248[200] = 0;
   out_7071521444289373248[201] = 0;
   out_7071521444289373248[202] = 0;
   out_7071521444289373248[203] = 0;
   out_7071521444289373248[204] = 0;
   out_7071521444289373248[205] = 0;
   out_7071521444289373248[206] = 0;
   out_7071521444289373248[207] = 0;
   out_7071521444289373248[208] = 0;
   out_7071521444289373248[209] = 1;
   out_7071521444289373248[210] = 0;
   out_7071521444289373248[211] = 0;
   out_7071521444289373248[212] = 0;
   out_7071521444289373248[213] = 0;
   out_7071521444289373248[214] = 0;
   out_7071521444289373248[215] = 0;
   out_7071521444289373248[216] = 0;
   out_7071521444289373248[217] = 0;
   out_7071521444289373248[218] = 0;
   out_7071521444289373248[219] = 0;
   out_7071521444289373248[220] = 0;
   out_7071521444289373248[221] = 0;
   out_7071521444289373248[222] = 0;
   out_7071521444289373248[223] = 0;
   out_7071521444289373248[224] = 0;
   out_7071521444289373248[225] = 0;
   out_7071521444289373248[226] = 0;
   out_7071521444289373248[227] = 0;
   out_7071521444289373248[228] = 1;
   out_7071521444289373248[229] = 0;
   out_7071521444289373248[230] = 0;
   out_7071521444289373248[231] = 0;
   out_7071521444289373248[232] = 0;
   out_7071521444289373248[233] = 0;
   out_7071521444289373248[234] = 0;
   out_7071521444289373248[235] = 0;
   out_7071521444289373248[236] = 0;
   out_7071521444289373248[237] = 0;
   out_7071521444289373248[238] = 0;
   out_7071521444289373248[239] = 0;
   out_7071521444289373248[240] = 0;
   out_7071521444289373248[241] = 0;
   out_7071521444289373248[242] = 0;
   out_7071521444289373248[243] = 0;
   out_7071521444289373248[244] = 0;
   out_7071521444289373248[245] = 0;
   out_7071521444289373248[246] = 0;
   out_7071521444289373248[247] = 1;
   out_7071521444289373248[248] = 0;
   out_7071521444289373248[249] = 0;
   out_7071521444289373248[250] = 0;
   out_7071521444289373248[251] = 0;
   out_7071521444289373248[252] = 0;
   out_7071521444289373248[253] = 0;
   out_7071521444289373248[254] = 0;
   out_7071521444289373248[255] = 0;
   out_7071521444289373248[256] = 0;
   out_7071521444289373248[257] = 0;
   out_7071521444289373248[258] = 0;
   out_7071521444289373248[259] = 0;
   out_7071521444289373248[260] = 0;
   out_7071521444289373248[261] = 0;
   out_7071521444289373248[262] = 0;
   out_7071521444289373248[263] = 0;
   out_7071521444289373248[264] = 0;
   out_7071521444289373248[265] = 0;
   out_7071521444289373248[266] = 1;
   out_7071521444289373248[267] = 0;
   out_7071521444289373248[268] = 0;
   out_7071521444289373248[269] = 0;
   out_7071521444289373248[270] = 0;
   out_7071521444289373248[271] = 0;
   out_7071521444289373248[272] = 0;
   out_7071521444289373248[273] = 0;
   out_7071521444289373248[274] = 0;
   out_7071521444289373248[275] = 0;
   out_7071521444289373248[276] = 0;
   out_7071521444289373248[277] = 0;
   out_7071521444289373248[278] = 0;
   out_7071521444289373248[279] = 0;
   out_7071521444289373248[280] = 0;
   out_7071521444289373248[281] = 0;
   out_7071521444289373248[282] = 0;
   out_7071521444289373248[283] = 0;
   out_7071521444289373248[284] = 0;
   out_7071521444289373248[285] = 1;
   out_7071521444289373248[286] = 0;
   out_7071521444289373248[287] = 0;
   out_7071521444289373248[288] = 0;
   out_7071521444289373248[289] = 0;
   out_7071521444289373248[290] = 0;
   out_7071521444289373248[291] = 0;
   out_7071521444289373248[292] = 0;
   out_7071521444289373248[293] = 0;
   out_7071521444289373248[294] = 0;
   out_7071521444289373248[295] = 0;
   out_7071521444289373248[296] = 0;
   out_7071521444289373248[297] = 0;
   out_7071521444289373248[298] = 0;
   out_7071521444289373248[299] = 0;
   out_7071521444289373248[300] = 0;
   out_7071521444289373248[301] = 0;
   out_7071521444289373248[302] = 0;
   out_7071521444289373248[303] = 0;
   out_7071521444289373248[304] = 1;
   out_7071521444289373248[305] = 0;
   out_7071521444289373248[306] = 0;
   out_7071521444289373248[307] = 0;
   out_7071521444289373248[308] = 0;
   out_7071521444289373248[309] = 0;
   out_7071521444289373248[310] = 0;
   out_7071521444289373248[311] = 0;
   out_7071521444289373248[312] = 0;
   out_7071521444289373248[313] = 0;
   out_7071521444289373248[314] = 0;
   out_7071521444289373248[315] = 0;
   out_7071521444289373248[316] = 0;
   out_7071521444289373248[317] = 0;
   out_7071521444289373248[318] = 0;
   out_7071521444289373248[319] = 0;
   out_7071521444289373248[320] = 0;
   out_7071521444289373248[321] = 0;
   out_7071521444289373248[322] = 0;
   out_7071521444289373248[323] = 1;
}
void h_4(double *state, double *unused, double *out_67509566290800345) {
   out_67509566290800345[0] = state[6] + state[9];
   out_67509566290800345[1] = state[7] + state[10];
   out_67509566290800345[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3215504100527336884) {
   out_3215504100527336884[0] = 0;
   out_3215504100527336884[1] = 0;
   out_3215504100527336884[2] = 0;
   out_3215504100527336884[3] = 0;
   out_3215504100527336884[4] = 0;
   out_3215504100527336884[5] = 0;
   out_3215504100527336884[6] = 1;
   out_3215504100527336884[7] = 0;
   out_3215504100527336884[8] = 0;
   out_3215504100527336884[9] = 1;
   out_3215504100527336884[10] = 0;
   out_3215504100527336884[11] = 0;
   out_3215504100527336884[12] = 0;
   out_3215504100527336884[13] = 0;
   out_3215504100527336884[14] = 0;
   out_3215504100527336884[15] = 0;
   out_3215504100527336884[16] = 0;
   out_3215504100527336884[17] = 0;
   out_3215504100527336884[18] = 0;
   out_3215504100527336884[19] = 0;
   out_3215504100527336884[20] = 0;
   out_3215504100527336884[21] = 0;
   out_3215504100527336884[22] = 0;
   out_3215504100527336884[23] = 0;
   out_3215504100527336884[24] = 0;
   out_3215504100527336884[25] = 1;
   out_3215504100527336884[26] = 0;
   out_3215504100527336884[27] = 0;
   out_3215504100527336884[28] = 1;
   out_3215504100527336884[29] = 0;
   out_3215504100527336884[30] = 0;
   out_3215504100527336884[31] = 0;
   out_3215504100527336884[32] = 0;
   out_3215504100527336884[33] = 0;
   out_3215504100527336884[34] = 0;
   out_3215504100527336884[35] = 0;
   out_3215504100527336884[36] = 0;
   out_3215504100527336884[37] = 0;
   out_3215504100527336884[38] = 0;
   out_3215504100527336884[39] = 0;
   out_3215504100527336884[40] = 0;
   out_3215504100527336884[41] = 0;
   out_3215504100527336884[42] = 0;
   out_3215504100527336884[43] = 0;
   out_3215504100527336884[44] = 1;
   out_3215504100527336884[45] = 0;
   out_3215504100527336884[46] = 0;
   out_3215504100527336884[47] = 1;
   out_3215504100527336884[48] = 0;
   out_3215504100527336884[49] = 0;
   out_3215504100527336884[50] = 0;
   out_3215504100527336884[51] = 0;
   out_3215504100527336884[52] = 0;
   out_3215504100527336884[53] = 0;
}
void h_10(double *state, double *unused, double *out_2077999983659095687) {
   out_2077999983659095687[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2077999983659095687[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2077999983659095687[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1146830641480722290) {
   out_1146830641480722290[0] = 0;
   out_1146830641480722290[1] = 9.8100000000000005*cos(state[1]);
   out_1146830641480722290[2] = 0;
   out_1146830641480722290[3] = 0;
   out_1146830641480722290[4] = -state[8];
   out_1146830641480722290[5] = state[7];
   out_1146830641480722290[6] = 0;
   out_1146830641480722290[7] = state[5];
   out_1146830641480722290[8] = -state[4];
   out_1146830641480722290[9] = 0;
   out_1146830641480722290[10] = 0;
   out_1146830641480722290[11] = 0;
   out_1146830641480722290[12] = 1;
   out_1146830641480722290[13] = 0;
   out_1146830641480722290[14] = 0;
   out_1146830641480722290[15] = 1;
   out_1146830641480722290[16] = 0;
   out_1146830641480722290[17] = 0;
   out_1146830641480722290[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1146830641480722290[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1146830641480722290[20] = 0;
   out_1146830641480722290[21] = state[8];
   out_1146830641480722290[22] = 0;
   out_1146830641480722290[23] = -state[6];
   out_1146830641480722290[24] = -state[5];
   out_1146830641480722290[25] = 0;
   out_1146830641480722290[26] = state[3];
   out_1146830641480722290[27] = 0;
   out_1146830641480722290[28] = 0;
   out_1146830641480722290[29] = 0;
   out_1146830641480722290[30] = 0;
   out_1146830641480722290[31] = 1;
   out_1146830641480722290[32] = 0;
   out_1146830641480722290[33] = 0;
   out_1146830641480722290[34] = 1;
   out_1146830641480722290[35] = 0;
   out_1146830641480722290[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1146830641480722290[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1146830641480722290[38] = 0;
   out_1146830641480722290[39] = -state[7];
   out_1146830641480722290[40] = state[6];
   out_1146830641480722290[41] = 0;
   out_1146830641480722290[42] = state[4];
   out_1146830641480722290[43] = -state[3];
   out_1146830641480722290[44] = 0;
   out_1146830641480722290[45] = 0;
   out_1146830641480722290[46] = 0;
   out_1146830641480722290[47] = 0;
   out_1146830641480722290[48] = 0;
   out_1146830641480722290[49] = 0;
   out_1146830641480722290[50] = 1;
   out_1146830641480722290[51] = 0;
   out_1146830641480722290[52] = 0;
   out_1146830641480722290[53] = 1;
}
void h_13(double *state, double *unused, double *out_7759616382768276568) {
   out_7759616382768276568[0] = state[3];
   out_7759616382768276568[1] = state[4];
   out_7759616382768276568[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3230275195004083) {
   out_3230275195004083[0] = 0;
   out_3230275195004083[1] = 0;
   out_3230275195004083[2] = 0;
   out_3230275195004083[3] = 1;
   out_3230275195004083[4] = 0;
   out_3230275195004083[5] = 0;
   out_3230275195004083[6] = 0;
   out_3230275195004083[7] = 0;
   out_3230275195004083[8] = 0;
   out_3230275195004083[9] = 0;
   out_3230275195004083[10] = 0;
   out_3230275195004083[11] = 0;
   out_3230275195004083[12] = 0;
   out_3230275195004083[13] = 0;
   out_3230275195004083[14] = 0;
   out_3230275195004083[15] = 0;
   out_3230275195004083[16] = 0;
   out_3230275195004083[17] = 0;
   out_3230275195004083[18] = 0;
   out_3230275195004083[19] = 0;
   out_3230275195004083[20] = 0;
   out_3230275195004083[21] = 0;
   out_3230275195004083[22] = 1;
   out_3230275195004083[23] = 0;
   out_3230275195004083[24] = 0;
   out_3230275195004083[25] = 0;
   out_3230275195004083[26] = 0;
   out_3230275195004083[27] = 0;
   out_3230275195004083[28] = 0;
   out_3230275195004083[29] = 0;
   out_3230275195004083[30] = 0;
   out_3230275195004083[31] = 0;
   out_3230275195004083[32] = 0;
   out_3230275195004083[33] = 0;
   out_3230275195004083[34] = 0;
   out_3230275195004083[35] = 0;
   out_3230275195004083[36] = 0;
   out_3230275195004083[37] = 0;
   out_3230275195004083[38] = 0;
   out_3230275195004083[39] = 0;
   out_3230275195004083[40] = 0;
   out_3230275195004083[41] = 1;
   out_3230275195004083[42] = 0;
   out_3230275195004083[43] = 0;
   out_3230275195004083[44] = 0;
   out_3230275195004083[45] = 0;
   out_3230275195004083[46] = 0;
   out_3230275195004083[47] = 0;
   out_3230275195004083[48] = 0;
   out_3230275195004083[49] = 0;
   out_3230275195004083[50] = 0;
   out_3230275195004083[51] = 0;
   out_3230275195004083[52] = 0;
   out_3230275195004083[53] = 0;
}
void h_14(double *state, double *unused, double *out_3709581126101699448) {
   out_3709581126101699448[0] = state[6];
   out_3709581126101699448[1] = state[7];
   out_3709581126101699448[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3650620627172220483) {
   out_3650620627172220483[0] = 0;
   out_3650620627172220483[1] = 0;
   out_3650620627172220483[2] = 0;
   out_3650620627172220483[3] = 0;
   out_3650620627172220483[4] = 0;
   out_3650620627172220483[5] = 0;
   out_3650620627172220483[6] = 1;
   out_3650620627172220483[7] = 0;
   out_3650620627172220483[8] = 0;
   out_3650620627172220483[9] = 0;
   out_3650620627172220483[10] = 0;
   out_3650620627172220483[11] = 0;
   out_3650620627172220483[12] = 0;
   out_3650620627172220483[13] = 0;
   out_3650620627172220483[14] = 0;
   out_3650620627172220483[15] = 0;
   out_3650620627172220483[16] = 0;
   out_3650620627172220483[17] = 0;
   out_3650620627172220483[18] = 0;
   out_3650620627172220483[19] = 0;
   out_3650620627172220483[20] = 0;
   out_3650620627172220483[21] = 0;
   out_3650620627172220483[22] = 0;
   out_3650620627172220483[23] = 0;
   out_3650620627172220483[24] = 0;
   out_3650620627172220483[25] = 1;
   out_3650620627172220483[26] = 0;
   out_3650620627172220483[27] = 0;
   out_3650620627172220483[28] = 0;
   out_3650620627172220483[29] = 0;
   out_3650620627172220483[30] = 0;
   out_3650620627172220483[31] = 0;
   out_3650620627172220483[32] = 0;
   out_3650620627172220483[33] = 0;
   out_3650620627172220483[34] = 0;
   out_3650620627172220483[35] = 0;
   out_3650620627172220483[36] = 0;
   out_3650620627172220483[37] = 0;
   out_3650620627172220483[38] = 0;
   out_3650620627172220483[39] = 0;
   out_3650620627172220483[40] = 0;
   out_3650620627172220483[41] = 0;
   out_3650620627172220483[42] = 0;
   out_3650620627172220483[43] = 0;
   out_3650620627172220483[44] = 1;
   out_3650620627172220483[45] = 0;
   out_3650620627172220483[46] = 0;
   out_3650620627172220483[47] = 0;
   out_3650620627172220483[48] = 0;
   out_3650620627172220483[49] = 0;
   out_3650620627172220483[50] = 0;
   out_3650620627172220483[51] = 0;
   out_3650620627172220483[52] = 0;
   out_3650620627172220483[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_1909500707924070274) {
  err_fun(nom_x, delta_x, out_1909500707924070274);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4767002163824434397) {
  inv_err_fun(nom_x, true_x, out_4767002163824434397);
}
void pose_H_mod_fun(double *state, double *out_2632577706224621837) {
  H_mod_fun(state, out_2632577706224621837);
}
void pose_f_fun(double *state, double dt, double *out_2193527682870666897) {
  f_fun(state,  dt, out_2193527682870666897);
}
void pose_F_fun(double *state, double dt, double *out_7071521444289373248) {
  F_fun(state,  dt, out_7071521444289373248);
}
void pose_h_4(double *state, double *unused, double *out_67509566290800345) {
  h_4(state, unused, out_67509566290800345);
}
void pose_H_4(double *state, double *unused, double *out_3215504100527336884) {
  H_4(state, unused, out_3215504100527336884);
}
void pose_h_10(double *state, double *unused, double *out_2077999983659095687) {
  h_10(state, unused, out_2077999983659095687);
}
void pose_H_10(double *state, double *unused, double *out_1146830641480722290) {
  H_10(state, unused, out_1146830641480722290);
}
void pose_h_13(double *state, double *unused, double *out_7759616382768276568) {
  h_13(state, unused, out_7759616382768276568);
}
void pose_H_13(double *state, double *unused, double *out_3230275195004083) {
  H_13(state, unused, out_3230275195004083);
}
void pose_h_14(double *state, double *unused, double *out_3709581126101699448) {
  h_14(state, unused, out_3709581126101699448);
}
void pose_H_14(double *state, double *unused, double *out_3650620627172220483) {
  H_14(state, unused, out_3650620627172220483);
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
