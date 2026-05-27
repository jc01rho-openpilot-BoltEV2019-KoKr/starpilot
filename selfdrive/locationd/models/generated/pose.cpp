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
void err_fun(double *nom_x, double *delta_x, double *out_5735299356181127199) {
   out_5735299356181127199[0] = delta_x[0] + nom_x[0];
   out_5735299356181127199[1] = delta_x[1] + nom_x[1];
   out_5735299356181127199[2] = delta_x[2] + nom_x[2];
   out_5735299356181127199[3] = delta_x[3] + nom_x[3];
   out_5735299356181127199[4] = delta_x[4] + nom_x[4];
   out_5735299356181127199[5] = delta_x[5] + nom_x[5];
   out_5735299356181127199[6] = delta_x[6] + nom_x[6];
   out_5735299356181127199[7] = delta_x[7] + nom_x[7];
   out_5735299356181127199[8] = delta_x[8] + nom_x[8];
   out_5735299356181127199[9] = delta_x[9] + nom_x[9];
   out_5735299356181127199[10] = delta_x[10] + nom_x[10];
   out_5735299356181127199[11] = delta_x[11] + nom_x[11];
   out_5735299356181127199[12] = delta_x[12] + nom_x[12];
   out_5735299356181127199[13] = delta_x[13] + nom_x[13];
   out_5735299356181127199[14] = delta_x[14] + nom_x[14];
   out_5735299356181127199[15] = delta_x[15] + nom_x[15];
   out_5735299356181127199[16] = delta_x[16] + nom_x[16];
   out_5735299356181127199[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1848486118618361424) {
   out_1848486118618361424[0] = -nom_x[0] + true_x[0];
   out_1848486118618361424[1] = -nom_x[1] + true_x[1];
   out_1848486118618361424[2] = -nom_x[2] + true_x[2];
   out_1848486118618361424[3] = -nom_x[3] + true_x[3];
   out_1848486118618361424[4] = -nom_x[4] + true_x[4];
   out_1848486118618361424[5] = -nom_x[5] + true_x[5];
   out_1848486118618361424[6] = -nom_x[6] + true_x[6];
   out_1848486118618361424[7] = -nom_x[7] + true_x[7];
   out_1848486118618361424[8] = -nom_x[8] + true_x[8];
   out_1848486118618361424[9] = -nom_x[9] + true_x[9];
   out_1848486118618361424[10] = -nom_x[10] + true_x[10];
   out_1848486118618361424[11] = -nom_x[11] + true_x[11];
   out_1848486118618361424[12] = -nom_x[12] + true_x[12];
   out_1848486118618361424[13] = -nom_x[13] + true_x[13];
   out_1848486118618361424[14] = -nom_x[14] + true_x[14];
   out_1848486118618361424[15] = -nom_x[15] + true_x[15];
   out_1848486118618361424[16] = -nom_x[16] + true_x[16];
   out_1848486118618361424[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3441620345746718845) {
   out_3441620345746718845[0] = 1.0;
   out_3441620345746718845[1] = 0.0;
   out_3441620345746718845[2] = 0.0;
   out_3441620345746718845[3] = 0.0;
   out_3441620345746718845[4] = 0.0;
   out_3441620345746718845[5] = 0.0;
   out_3441620345746718845[6] = 0.0;
   out_3441620345746718845[7] = 0.0;
   out_3441620345746718845[8] = 0.0;
   out_3441620345746718845[9] = 0.0;
   out_3441620345746718845[10] = 0.0;
   out_3441620345746718845[11] = 0.0;
   out_3441620345746718845[12] = 0.0;
   out_3441620345746718845[13] = 0.0;
   out_3441620345746718845[14] = 0.0;
   out_3441620345746718845[15] = 0.0;
   out_3441620345746718845[16] = 0.0;
   out_3441620345746718845[17] = 0.0;
   out_3441620345746718845[18] = 0.0;
   out_3441620345746718845[19] = 1.0;
   out_3441620345746718845[20] = 0.0;
   out_3441620345746718845[21] = 0.0;
   out_3441620345746718845[22] = 0.0;
   out_3441620345746718845[23] = 0.0;
   out_3441620345746718845[24] = 0.0;
   out_3441620345746718845[25] = 0.0;
   out_3441620345746718845[26] = 0.0;
   out_3441620345746718845[27] = 0.0;
   out_3441620345746718845[28] = 0.0;
   out_3441620345746718845[29] = 0.0;
   out_3441620345746718845[30] = 0.0;
   out_3441620345746718845[31] = 0.0;
   out_3441620345746718845[32] = 0.0;
   out_3441620345746718845[33] = 0.0;
   out_3441620345746718845[34] = 0.0;
   out_3441620345746718845[35] = 0.0;
   out_3441620345746718845[36] = 0.0;
   out_3441620345746718845[37] = 0.0;
   out_3441620345746718845[38] = 1.0;
   out_3441620345746718845[39] = 0.0;
   out_3441620345746718845[40] = 0.0;
   out_3441620345746718845[41] = 0.0;
   out_3441620345746718845[42] = 0.0;
   out_3441620345746718845[43] = 0.0;
   out_3441620345746718845[44] = 0.0;
   out_3441620345746718845[45] = 0.0;
   out_3441620345746718845[46] = 0.0;
   out_3441620345746718845[47] = 0.0;
   out_3441620345746718845[48] = 0.0;
   out_3441620345746718845[49] = 0.0;
   out_3441620345746718845[50] = 0.0;
   out_3441620345746718845[51] = 0.0;
   out_3441620345746718845[52] = 0.0;
   out_3441620345746718845[53] = 0.0;
   out_3441620345746718845[54] = 0.0;
   out_3441620345746718845[55] = 0.0;
   out_3441620345746718845[56] = 0.0;
   out_3441620345746718845[57] = 1.0;
   out_3441620345746718845[58] = 0.0;
   out_3441620345746718845[59] = 0.0;
   out_3441620345746718845[60] = 0.0;
   out_3441620345746718845[61] = 0.0;
   out_3441620345746718845[62] = 0.0;
   out_3441620345746718845[63] = 0.0;
   out_3441620345746718845[64] = 0.0;
   out_3441620345746718845[65] = 0.0;
   out_3441620345746718845[66] = 0.0;
   out_3441620345746718845[67] = 0.0;
   out_3441620345746718845[68] = 0.0;
   out_3441620345746718845[69] = 0.0;
   out_3441620345746718845[70] = 0.0;
   out_3441620345746718845[71] = 0.0;
   out_3441620345746718845[72] = 0.0;
   out_3441620345746718845[73] = 0.0;
   out_3441620345746718845[74] = 0.0;
   out_3441620345746718845[75] = 0.0;
   out_3441620345746718845[76] = 1.0;
   out_3441620345746718845[77] = 0.0;
   out_3441620345746718845[78] = 0.0;
   out_3441620345746718845[79] = 0.0;
   out_3441620345746718845[80] = 0.0;
   out_3441620345746718845[81] = 0.0;
   out_3441620345746718845[82] = 0.0;
   out_3441620345746718845[83] = 0.0;
   out_3441620345746718845[84] = 0.0;
   out_3441620345746718845[85] = 0.0;
   out_3441620345746718845[86] = 0.0;
   out_3441620345746718845[87] = 0.0;
   out_3441620345746718845[88] = 0.0;
   out_3441620345746718845[89] = 0.0;
   out_3441620345746718845[90] = 0.0;
   out_3441620345746718845[91] = 0.0;
   out_3441620345746718845[92] = 0.0;
   out_3441620345746718845[93] = 0.0;
   out_3441620345746718845[94] = 0.0;
   out_3441620345746718845[95] = 1.0;
   out_3441620345746718845[96] = 0.0;
   out_3441620345746718845[97] = 0.0;
   out_3441620345746718845[98] = 0.0;
   out_3441620345746718845[99] = 0.0;
   out_3441620345746718845[100] = 0.0;
   out_3441620345746718845[101] = 0.0;
   out_3441620345746718845[102] = 0.0;
   out_3441620345746718845[103] = 0.0;
   out_3441620345746718845[104] = 0.0;
   out_3441620345746718845[105] = 0.0;
   out_3441620345746718845[106] = 0.0;
   out_3441620345746718845[107] = 0.0;
   out_3441620345746718845[108] = 0.0;
   out_3441620345746718845[109] = 0.0;
   out_3441620345746718845[110] = 0.0;
   out_3441620345746718845[111] = 0.0;
   out_3441620345746718845[112] = 0.0;
   out_3441620345746718845[113] = 0.0;
   out_3441620345746718845[114] = 1.0;
   out_3441620345746718845[115] = 0.0;
   out_3441620345746718845[116] = 0.0;
   out_3441620345746718845[117] = 0.0;
   out_3441620345746718845[118] = 0.0;
   out_3441620345746718845[119] = 0.0;
   out_3441620345746718845[120] = 0.0;
   out_3441620345746718845[121] = 0.0;
   out_3441620345746718845[122] = 0.0;
   out_3441620345746718845[123] = 0.0;
   out_3441620345746718845[124] = 0.0;
   out_3441620345746718845[125] = 0.0;
   out_3441620345746718845[126] = 0.0;
   out_3441620345746718845[127] = 0.0;
   out_3441620345746718845[128] = 0.0;
   out_3441620345746718845[129] = 0.0;
   out_3441620345746718845[130] = 0.0;
   out_3441620345746718845[131] = 0.0;
   out_3441620345746718845[132] = 0.0;
   out_3441620345746718845[133] = 1.0;
   out_3441620345746718845[134] = 0.0;
   out_3441620345746718845[135] = 0.0;
   out_3441620345746718845[136] = 0.0;
   out_3441620345746718845[137] = 0.0;
   out_3441620345746718845[138] = 0.0;
   out_3441620345746718845[139] = 0.0;
   out_3441620345746718845[140] = 0.0;
   out_3441620345746718845[141] = 0.0;
   out_3441620345746718845[142] = 0.0;
   out_3441620345746718845[143] = 0.0;
   out_3441620345746718845[144] = 0.0;
   out_3441620345746718845[145] = 0.0;
   out_3441620345746718845[146] = 0.0;
   out_3441620345746718845[147] = 0.0;
   out_3441620345746718845[148] = 0.0;
   out_3441620345746718845[149] = 0.0;
   out_3441620345746718845[150] = 0.0;
   out_3441620345746718845[151] = 0.0;
   out_3441620345746718845[152] = 1.0;
   out_3441620345746718845[153] = 0.0;
   out_3441620345746718845[154] = 0.0;
   out_3441620345746718845[155] = 0.0;
   out_3441620345746718845[156] = 0.0;
   out_3441620345746718845[157] = 0.0;
   out_3441620345746718845[158] = 0.0;
   out_3441620345746718845[159] = 0.0;
   out_3441620345746718845[160] = 0.0;
   out_3441620345746718845[161] = 0.0;
   out_3441620345746718845[162] = 0.0;
   out_3441620345746718845[163] = 0.0;
   out_3441620345746718845[164] = 0.0;
   out_3441620345746718845[165] = 0.0;
   out_3441620345746718845[166] = 0.0;
   out_3441620345746718845[167] = 0.0;
   out_3441620345746718845[168] = 0.0;
   out_3441620345746718845[169] = 0.0;
   out_3441620345746718845[170] = 0.0;
   out_3441620345746718845[171] = 1.0;
   out_3441620345746718845[172] = 0.0;
   out_3441620345746718845[173] = 0.0;
   out_3441620345746718845[174] = 0.0;
   out_3441620345746718845[175] = 0.0;
   out_3441620345746718845[176] = 0.0;
   out_3441620345746718845[177] = 0.0;
   out_3441620345746718845[178] = 0.0;
   out_3441620345746718845[179] = 0.0;
   out_3441620345746718845[180] = 0.0;
   out_3441620345746718845[181] = 0.0;
   out_3441620345746718845[182] = 0.0;
   out_3441620345746718845[183] = 0.0;
   out_3441620345746718845[184] = 0.0;
   out_3441620345746718845[185] = 0.0;
   out_3441620345746718845[186] = 0.0;
   out_3441620345746718845[187] = 0.0;
   out_3441620345746718845[188] = 0.0;
   out_3441620345746718845[189] = 0.0;
   out_3441620345746718845[190] = 1.0;
   out_3441620345746718845[191] = 0.0;
   out_3441620345746718845[192] = 0.0;
   out_3441620345746718845[193] = 0.0;
   out_3441620345746718845[194] = 0.0;
   out_3441620345746718845[195] = 0.0;
   out_3441620345746718845[196] = 0.0;
   out_3441620345746718845[197] = 0.0;
   out_3441620345746718845[198] = 0.0;
   out_3441620345746718845[199] = 0.0;
   out_3441620345746718845[200] = 0.0;
   out_3441620345746718845[201] = 0.0;
   out_3441620345746718845[202] = 0.0;
   out_3441620345746718845[203] = 0.0;
   out_3441620345746718845[204] = 0.0;
   out_3441620345746718845[205] = 0.0;
   out_3441620345746718845[206] = 0.0;
   out_3441620345746718845[207] = 0.0;
   out_3441620345746718845[208] = 0.0;
   out_3441620345746718845[209] = 1.0;
   out_3441620345746718845[210] = 0.0;
   out_3441620345746718845[211] = 0.0;
   out_3441620345746718845[212] = 0.0;
   out_3441620345746718845[213] = 0.0;
   out_3441620345746718845[214] = 0.0;
   out_3441620345746718845[215] = 0.0;
   out_3441620345746718845[216] = 0.0;
   out_3441620345746718845[217] = 0.0;
   out_3441620345746718845[218] = 0.0;
   out_3441620345746718845[219] = 0.0;
   out_3441620345746718845[220] = 0.0;
   out_3441620345746718845[221] = 0.0;
   out_3441620345746718845[222] = 0.0;
   out_3441620345746718845[223] = 0.0;
   out_3441620345746718845[224] = 0.0;
   out_3441620345746718845[225] = 0.0;
   out_3441620345746718845[226] = 0.0;
   out_3441620345746718845[227] = 0.0;
   out_3441620345746718845[228] = 1.0;
   out_3441620345746718845[229] = 0.0;
   out_3441620345746718845[230] = 0.0;
   out_3441620345746718845[231] = 0.0;
   out_3441620345746718845[232] = 0.0;
   out_3441620345746718845[233] = 0.0;
   out_3441620345746718845[234] = 0.0;
   out_3441620345746718845[235] = 0.0;
   out_3441620345746718845[236] = 0.0;
   out_3441620345746718845[237] = 0.0;
   out_3441620345746718845[238] = 0.0;
   out_3441620345746718845[239] = 0.0;
   out_3441620345746718845[240] = 0.0;
   out_3441620345746718845[241] = 0.0;
   out_3441620345746718845[242] = 0.0;
   out_3441620345746718845[243] = 0.0;
   out_3441620345746718845[244] = 0.0;
   out_3441620345746718845[245] = 0.0;
   out_3441620345746718845[246] = 0.0;
   out_3441620345746718845[247] = 1.0;
   out_3441620345746718845[248] = 0.0;
   out_3441620345746718845[249] = 0.0;
   out_3441620345746718845[250] = 0.0;
   out_3441620345746718845[251] = 0.0;
   out_3441620345746718845[252] = 0.0;
   out_3441620345746718845[253] = 0.0;
   out_3441620345746718845[254] = 0.0;
   out_3441620345746718845[255] = 0.0;
   out_3441620345746718845[256] = 0.0;
   out_3441620345746718845[257] = 0.0;
   out_3441620345746718845[258] = 0.0;
   out_3441620345746718845[259] = 0.0;
   out_3441620345746718845[260] = 0.0;
   out_3441620345746718845[261] = 0.0;
   out_3441620345746718845[262] = 0.0;
   out_3441620345746718845[263] = 0.0;
   out_3441620345746718845[264] = 0.0;
   out_3441620345746718845[265] = 0.0;
   out_3441620345746718845[266] = 1.0;
   out_3441620345746718845[267] = 0.0;
   out_3441620345746718845[268] = 0.0;
   out_3441620345746718845[269] = 0.0;
   out_3441620345746718845[270] = 0.0;
   out_3441620345746718845[271] = 0.0;
   out_3441620345746718845[272] = 0.0;
   out_3441620345746718845[273] = 0.0;
   out_3441620345746718845[274] = 0.0;
   out_3441620345746718845[275] = 0.0;
   out_3441620345746718845[276] = 0.0;
   out_3441620345746718845[277] = 0.0;
   out_3441620345746718845[278] = 0.0;
   out_3441620345746718845[279] = 0.0;
   out_3441620345746718845[280] = 0.0;
   out_3441620345746718845[281] = 0.0;
   out_3441620345746718845[282] = 0.0;
   out_3441620345746718845[283] = 0.0;
   out_3441620345746718845[284] = 0.0;
   out_3441620345746718845[285] = 1.0;
   out_3441620345746718845[286] = 0.0;
   out_3441620345746718845[287] = 0.0;
   out_3441620345746718845[288] = 0.0;
   out_3441620345746718845[289] = 0.0;
   out_3441620345746718845[290] = 0.0;
   out_3441620345746718845[291] = 0.0;
   out_3441620345746718845[292] = 0.0;
   out_3441620345746718845[293] = 0.0;
   out_3441620345746718845[294] = 0.0;
   out_3441620345746718845[295] = 0.0;
   out_3441620345746718845[296] = 0.0;
   out_3441620345746718845[297] = 0.0;
   out_3441620345746718845[298] = 0.0;
   out_3441620345746718845[299] = 0.0;
   out_3441620345746718845[300] = 0.0;
   out_3441620345746718845[301] = 0.0;
   out_3441620345746718845[302] = 0.0;
   out_3441620345746718845[303] = 0.0;
   out_3441620345746718845[304] = 1.0;
   out_3441620345746718845[305] = 0.0;
   out_3441620345746718845[306] = 0.0;
   out_3441620345746718845[307] = 0.0;
   out_3441620345746718845[308] = 0.0;
   out_3441620345746718845[309] = 0.0;
   out_3441620345746718845[310] = 0.0;
   out_3441620345746718845[311] = 0.0;
   out_3441620345746718845[312] = 0.0;
   out_3441620345746718845[313] = 0.0;
   out_3441620345746718845[314] = 0.0;
   out_3441620345746718845[315] = 0.0;
   out_3441620345746718845[316] = 0.0;
   out_3441620345746718845[317] = 0.0;
   out_3441620345746718845[318] = 0.0;
   out_3441620345746718845[319] = 0.0;
   out_3441620345746718845[320] = 0.0;
   out_3441620345746718845[321] = 0.0;
   out_3441620345746718845[322] = 0.0;
   out_3441620345746718845[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5548337699276970526) {
   out_5548337699276970526[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5548337699276970526[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5548337699276970526[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5548337699276970526[3] = dt*state[12] + state[3];
   out_5548337699276970526[4] = dt*state[13] + state[4];
   out_5548337699276970526[5] = dt*state[14] + state[5];
   out_5548337699276970526[6] = state[6];
   out_5548337699276970526[7] = state[7];
   out_5548337699276970526[8] = state[8];
   out_5548337699276970526[9] = state[9];
   out_5548337699276970526[10] = state[10];
   out_5548337699276970526[11] = state[11];
   out_5548337699276970526[12] = state[12];
   out_5548337699276970526[13] = state[13];
   out_5548337699276970526[14] = state[14];
   out_5548337699276970526[15] = state[15];
   out_5548337699276970526[16] = state[16];
   out_5548337699276970526[17] = state[17];
}
void F_fun(double *state, double dt, double *out_6716874081947285130) {
   out_6716874081947285130[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6716874081947285130[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6716874081947285130[2] = 0;
   out_6716874081947285130[3] = 0;
   out_6716874081947285130[4] = 0;
   out_6716874081947285130[5] = 0;
   out_6716874081947285130[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6716874081947285130[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6716874081947285130[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6716874081947285130[9] = 0;
   out_6716874081947285130[10] = 0;
   out_6716874081947285130[11] = 0;
   out_6716874081947285130[12] = 0;
   out_6716874081947285130[13] = 0;
   out_6716874081947285130[14] = 0;
   out_6716874081947285130[15] = 0;
   out_6716874081947285130[16] = 0;
   out_6716874081947285130[17] = 0;
   out_6716874081947285130[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6716874081947285130[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6716874081947285130[20] = 0;
   out_6716874081947285130[21] = 0;
   out_6716874081947285130[22] = 0;
   out_6716874081947285130[23] = 0;
   out_6716874081947285130[24] = 0;
   out_6716874081947285130[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6716874081947285130[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6716874081947285130[27] = 0;
   out_6716874081947285130[28] = 0;
   out_6716874081947285130[29] = 0;
   out_6716874081947285130[30] = 0;
   out_6716874081947285130[31] = 0;
   out_6716874081947285130[32] = 0;
   out_6716874081947285130[33] = 0;
   out_6716874081947285130[34] = 0;
   out_6716874081947285130[35] = 0;
   out_6716874081947285130[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6716874081947285130[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6716874081947285130[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6716874081947285130[39] = 0;
   out_6716874081947285130[40] = 0;
   out_6716874081947285130[41] = 0;
   out_6716874081947285130[42] = 0;
   out_6716874081947285130[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6716874081947285130[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6716874081947285130[45] = 0;
   out_6716874081947285130[46] = 0;
   out_6716874081947285130[47] = 0;
   out_6716874081947285130[48] = 0;
   out_6716874081947285130[49] = 0;
   out_6716874081947285130[50] = 0;
   out_6716874081947285130[51] = 0;
   out_6716874081947285130[52] = 0;
   out_6716874081947285130[53] = 0;
   out_6716874081947285130[54] = 0;
   out_6716874081947285130[55] = 0;
   out_6716874081947285130[56] = 0;
   out_6716874081947285130[57] = 1;
   out_6716874081947285130[58] = 0;
   out_6716874081947285130[59] = 0;
   out_6716874081947285130[60] = 0;
   out_6716874081947285130[61] = 0;
   out_6716874081947285130[62] = 0;
   out_6716874081947285130[63] = 0;
   out_6716874081947285130[64] = 0;
   out_6716874081947285130[65] = 0;
   out_6716874081947285130[66] = dt;
   out_6716874081947285130[67] = 0;
   out_6716874081947285130[68] = 0;
   out_6716874081947285130[69] = 0;
   out_6716874081947285130[70] = 0;
   out_6716874081947285130[71] = 0;
   out_6716874081947285130[72] = 0;
   out_6716874081947285130[73] = 0;
   out_6716874081947285130[74] = 0;
   out_6716874081947285130[75] = 0;
   out_6716874081947285130[76] = 1;
   out_6716874081947285130[77] = 0;
   out_6716874081947285130[78] = 0;
   out_6716874081947285130[79] = 0;
   out_6716874081947285130[80] = 0;
   out_6716874081947285130[81] = 0;
   out_6716874081947285130[82] = 0;
   out_6716874081947285130[83] = 0;
   out_6716874081947285130[84] = 0;
   out_6716874081947285130[85] = dt;
   out_6716874081947285130[86] = 0;
   out_6716874081947285130[87] = 0;
   out_6716874081947285130[88] = 0;
   out_6716874081947285130[89] = 0;
   out_6716874081947285130[90] = 0;
   out_6716874081947285130[91] = 0;
   out_6716874081947285130[92] = 0;
   out_6716874081947285130[93] = 0;
   out_6716874081947285130[94] = 0;
   out_6716874081947285130[95] = 1;
   out_6716874081947285130[96] = 0;
   out_6716874081947285130[97] = 0;
   out_6716874081947285130[98] = 0;
   out_6716874081947285130[99] = 0;
   out_6716874081947285130[100] = 0;
   out_6716874081947285130[101] = 0;
   out_6716874081947285130[102] = 0;
   out_6716874081947285130[103] = 0;
   out_6716874081947285130[104] = dt;
   out_6716874081947285130[105] = 0;
   out_6716874081947285130[106] = 0;
   out_6716874081947285130[107] = 0;
   out_6716874081947285130[108] = 0;
   out_6716874081947285130[109] = 0;
   out_6716874081947285130[110] = 0;
   out_6716874081947285130[111] = 0;
   out_6716874081947285130[112] = 0;
   out_6716874081947285130[113] = 0;
   out_6716874081947285130[114] = 1;
   out_6716874081947285130[115] = 0;
   out_6716874081947285130[116] = 0;
   out_6716874081947285130[117] = 0;
   out_6716874081947285130[118] = 0;
   out_6716874081947285130[119] = 0;
   out_6716874081947285130[120] = 0;
   out_6716874081947285130[121] = 0;
   out_6716874081947285130[122] = 0;
   out_6716874081947285130[123] = 0;
   out_6716874081947285130[124] = 0;
   out_6716874081947285130[125] = 0;
   out_6716874081947285130[126] = 0;
   out_6716874081947285130[127] = 0;
   out_6716874081947285130[128] = 0;
   out_6716874081947285130[129] = 0;
   out_6716874081947285130[130] = 0;
   out_6716874081947285130[131] = 0;
   out_6716874081947285130[132] = 0;
   out_6716874081947285130[133] = 1;
   out_6716874081947285130[134] = 0;
   out_6716874081947285130[135] = 0;
   out_6716874081947285130[136] = 0;
   out_6716874081947285130[137] = 0;
   out_6716874081947285130[138] = 0;
   out_6716874081947285130[139] = 0;
   out_6716874081947285130[140] = 0;
   out_6716874081947285130[141] = 0;
   out_6716874081947285130[142] = 0;
   out_6716874081947285130[143] = 0;
   out_6716874081947285130[144] = 0;
   out_6716874081947285130[145] = 0;
   out_6716874081947285130[146] = 0;
   out_6716874081947285130[147] = 0;
   out_6716874081947285130[148] = 0;
   out_6716874081947285130[149] = 0;
   out_6716874081947285130[150] = 0;
   out_6716874081947285130[151] = 0;
   out_6716874081947285130[152] = 1;
   out_6716874081947285130[153] = 0;
   out_6716874081947285130[154] = 0;
   out_6716874081947285130[155] = 0;
   out_6716874081947285130[156] = 0;
   out_6716874081947285130[157] = 0;
   out_6716874081947285130[158] = 0;
   out_6716874081947285130[159] = 0;
   out_6716874081947285130[160] = 0;
   out_6716874081947285130[161] = 0;
   out_6716874081947285130[162] = 0;
   out_6716874081947285130[163] = 0;
   out_6716874081947285130[164] = 0;
   out_6716874081947285130[165] = 0;
   out_6716874081947285130[166] = 0;
   out_6716874081947285130[167] = 0;
   out_6716874081947285130[168] = 0;
   out_6716874081947285130[169] = 0;
   out_6716874081947285130[170] = 0;
   out_6716874081947285130[171] = 1;
   out_6716874081947285130[172] = 0;
   out_6716874081947285130[173] = 0;
   out_6716874081947285130[174] = 0;
   out_6716874081947285130[175] = 0;
   out_6716874081947285130[176] = 0;
   out_6716874081947285130[177] = 0;
   out_6716874081947285130[178] = 0;
   out_6716874081947285130[179] = 0;
   out_6716874081947285130[180] = 0;
   out_6716874081947285130[181] = 0;
   out_6716874081947285130[182] = 0;
   out_6716874081947285130[183] = 0;
   out_6716874081947285130[184] = 0;
   out_6716874081947285130[185] = 0;
   out_6716874081947285130[186] = 0;
   out_6716874081947285130[187] = 0;
   out_6716874081947285130[188] = 0;
   out_6716874081947285130[189] = 0;
   out_6716874081947285130[190] = 1;
   out_6716874081947285130[191] = 0;
   out_6716874081947285130[192] = 0;
   out_6716874081947285130[193] = 0;
   out_6716874081947285130[194] = 0;
   out_6716874081947285130[195] = 0;
   out_6716874081947285130[196] = 0;
   out_6716874081947285130[197] = 0;
   out_6716874081947285130[198] = 0;
   out_6716874081947285130[199] = 0;
   out_6716874081947285130[200] = 0;
   out_6716874081947285130[201] = 0;
   out_6716874081947285130[202] = 0;
   out_6716874081947285130[203] = 0;
   out_6716874081947285130[204] = 0;
   out_6716874081947285130[205] = 0;
   out_6716874081947285130[206] = 0;
   out_6716874081947285130[207] = 0;
   out_6716874081947285130[208] = 0;
   out_6716874081947285130[209] = 1;
   out_6716874081947285130[210] = 0;
   out_6716874081947285130[211] = 0;
   out_6716874081947285130[212] = 0;
   out_6716874081947285130[213] = 0;
   out_6716874081947285130[214] = 0;
   out_6716874081947285130[215] = 0;
   out_6716874081947285130[216] = 0;
   out_6716874081947285130[217] = 0;
   out_6716874081947285130[218] = 0;
   out_6716874081947285130[219] = 0;
   out_6716874081947285130[220] = 0;
   out_6716874081947285130[221] = 0;
   out_6716874081947285130[222] = 0;
   out_6716874081947285130[223] = 0;
   out_6716874081947285130[224] = 0;
   out_6716874081947285130[225] = 0;
   out_6716874081947285130[226] = 0;
   out_6716874081947285130[227] = 0;
   out_6716874081947285130[228] = 1;
   out_6716874081947285130[229] = 0;
   out_6716874081947285130[230] = 0;
   out_6716874081947285130[231] = 0;
   out_6716874081947285130[232] = 0;
   out_6716874081947285130[233] = 0;
   out_6716874081947285130[234] = 0;
   out_6716874081947285130[235] = 0;
   out_6716874081947285130[236] = 0;
   out_6716874081947285130[237] = 0;
   out_6716874081947285130[238] = 0;
   out_6716874081947285130[239] = 0;
   out_6716874081947285130[240] = 0;
   out_6716874081947285130[241] = 0;
   out_6716874081947285130[242] = 0;
   out_6716874081947285130[243] = 0;
   out_6716874081947285130[244] = 0;
   out_6716874081947285130[245] = 0;
   out_6716874081947285130[246] = 0;
   out_6716874081947285130[247] = 1;
   out_6716874081947285130[248] = 0;
   out_6716874081947285130[249] = 0;
   out_6716874081947285130[250] = 0;
   out_6716874081947285130[251] = 0;
   out_6716874081947285130[252] = 0;
   out_6716874081947285130[253] = 0;
   out_6716874081947285130[254] = 0;
   out_6716874081947285130[255] = 0;
   out_6716874081947285130[256] = 0;
   out_6716874081947285130[257] = 0;
   out_6716874081947285130[258] = 0;
   out_6716874081947285130[259] = 0;
   out_6716874081947285130[260] = 0;
   out_6716874081947285130[261] = 0;
   out_6716874081947285130[262] = 0;
   out_6716874081947285130[263] = 0;
   out_6716874081947285130[264] = 0;
   out_6716874081947285130[265] = 0;
   out_6716874081947285130[266] = 1;
   out_6716874081947285130[267] = 0;
   out_6716874081947285130[268] = 0;
   out_6716874081947285130[269] = 0;
   out_6716874081947285130[270] = 0;
   out_6716874081947285130[271] = 0;
   out_6716874081947285130[272] = 0;
   out_6716874081947285130[273] = 0;
   out_6716874081947285130[274] = 0;
   out_6716874081947285130[275] = 0;
   out_6716874081947285130[276] = 0;
   out_6716874081947285130[277] = 0;
   out_6716874081947285130[278] = 0;
   out_6716874081947285130[279] = 0;
   out_6716874081947285130[280] = 0;
   out_6716874081947285130[281] = 0;
   out_6716874081947285130[282] = 0;
   out_6716874081947285130[283] = 0;
   out_6716874081947285130[284] = 0;
   out_6716874081947285130[285] = 1;
   out_6716874081947285130[286] = 0;
   out_6716874081947285130[287] = 0;
   out_6716874081947285130[288] = 0;
   out_6716874081947285130[289] = 0;
   out_6716874081947285130[290] = 0;
   out_6716874081947285130[291] = 0;
   out_6716874081947285130[292] = 0;
   out_6716874081947285130[293] = 0;
   out_6716874081947285130[294] = 0;
   out_6716874081947285130[295] = 0;
   out_6716874081947285130[296] = 0;
   out_6716874081947285130[297] = 0;
   out_6716874081947285130[298] = 0;
   out_6716874081947285130[299] = 0;
   out_6716874081947285130[300] = 0;
   out_6716874081947285130[301] = 0;
   out_6716874081947285130[302] = 0;
   out_6716874081947285130[303] = 0;
   out_6716874081947285130[304] = 1;
   out_6716874081947285130[305] = 0;
   out_6716874081947285130[306] = 0;
   out_6716874081947285130[307] = 0;
   out_6716874081947285130[308] = 0;
   out_6716874081947285130[309] = 0;
   out_6716874081947285130[310] = 0;
   out_6716874081947285130[311] = 0;
   out_6716874081947285130[312] = 0;
   out_6716874081947285130[313] = 0;
   out_6716874081947285130[314] = 0;
   out_6716874081947285130[315] = 0;
   out_6716874081947285130[316] = 0;
   out_6716874081947285130[317] = 0;
   out_6716874081947285130[318] = 0;
   out_6716874081947285130[319] = 0;
   out_6716874081947285130[320] = 0;
   out_6716874081947285130[321] = 0;
   out_6716874081947285130[322] = 0;
   out_6716874081947285130[323] = 1;
}
void h_4(double *state, double *unused, double *out_6172444408937598103) {
   out_6172444408937598103[0] = state[6] + state[9];
   out_6172444408937598103[1] = state[7] + state[10];
   out_6172444408937598103[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_5296575886336270293) {
   out_5296575886336270293[0] = 0;
   out_5296575886336270293[1] = 0;
   out_5296575886336270293[2] = 0;
   out_5296575886336270293[3] = 0;
   out_5296575886336270293[4] = 0;
   out_5296575886336270293[5] = 0;
   out_5296575886336270293[6] = 1;
   out_5296575886336270293[7] = 0;
   out_5296575886336270293[8] = 0;
   out_5296575886336270293[9] = 1;
   out_5296575886336270293[10] = 0;
   out_5296575886336270293[11] = 0;
   out_5296575886336270293[12] = 0;
   out_5296575886336270293[13] = 0;
   out_5296575886336270293[14] = 0;
   out_5296575886336270293[15] = 0;
   out_5296575886336270293[16] = 0;
   out_5296575886336270293[17] = 0;
   out_5296575886336270293[18] = 0;
   out_5296575886336270293[19] = 0;
   out_5296575886336270293[20] = 0;
   out_5296575886336270293[21] = 0;
   out_5296575886336270293[22] = 0;
   out_5296575886336270293[23] = 0;
   out_5296575886336270293[24] = 0;
   out_5296575886336270293[25] = 1;
   out_5296575886336270293[26] = 0;
   out_5296575886336270293[27] = 0;
   out_5296575886336270293[28] = 1;
   out_5296575886336270293[29] = 0;
   out_5296575886336270293[30] = 0;
   out_5296575886336270293[31] = 0;
   out_5296575886336270293[32] = 0;
   out_5296575886336270293[33] = 0;
   out_5296575886336270293[34] = 0;
   out_5296575886336270293[35] = 0;
   out_5296575886336270293[36] = 0;
   out_5296575886336270293[37] = 0;
   out_5296575886336270293[38] = 0;
   out_5296575886336270293[39] = 0;
   out_5296575886336270293[40] = 0;
   out_5296575886336270293[41] = 0;
   out_5296575886336270293[42] = 0;
   out_5296575886336270293[43] = 0;
   out_5296575886336270293[44] = 1;
   out_5296575886336270293[45] = 0;
   out_5296575886336270293[46] = 0;
   out_5296575886336270293[47] = 1;
   out_5296575886336270293[48] = 0;
   out_5296575886336270293[49] = 0;
   out_5296575886336270293[50] = 0;
   out_5296575886336270293[51] = 0;
   out_5296575886336270293[52] = 0;
   out_5296575886336270293[53] = 0;
}
void h_10(double *state, double *unused, double *out_2819440341260442129) {
   out_2819440341260442129[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2819440341260442129[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2819440341260442129[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5042249891606824417) {
   out_5042249891606824417[0] = 0;
   out_5042249891606824417[1] = 9.8100000000000005*cos(state[1]);
   out_5042249891606824417[2] = 0;
   out_5042249891606824417[3] = 0;
   out_5042249891606824417[4] = -state[8];
   out_5042249891606824417[5] = state[7];
   out_5042249891606824417[6] = 0;
   out_5042249891606824417[7] = state[5];
   out_5042249891606824417[8] = -state[4];
   out_5042249891606824417[9] = 0;
   out_5042249891606824417[10] = 0;
   out_5042249891606824417[11] = 0;
   out_5042249891606824417[12] = 1;
   out_5042249891606824417[13] = 0;
   out_5042249891606824417[14] = 0;
   out_5042249891606824417[15] = 1;
   out_5042249891606824417[16] = 0;
   out_5042249891606824417[17] = 0;
   out_5042249891606824417[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5042249891606824417[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5042249891606824417[20] = 0;
   out_5042249891606824417[21] = state[8];
   out_5042249891606824417[22] = 0;
   out_5042249891606824417[23] = -state[6];
   out_5042249891606824417[24] = -state[5];
   out_5042249891606824417[25] = 0;
   out_5042249891606824417[26] = state[3];
   out_5042249891606824417[27] = 0;
   out_5042249891606824417[28] = 0;
   out_5042249891606824417[29] = 0;
   out_5042249891606824417[30] = 0;
   out_5042249891606824417[31] = 1;
   out_5042249891606824417[32] = 0;
   out_5042249891606824417[33] = 0;
   out_5042249891606824417[34] = 1;
   out_5042249891606824417[35] = 0;
   out_5042249891606824417[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5042249891606824417[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5042249891606824417[38] = 0;
   out_5042249891606824417[39] = -state[7];
   out_5042249891606824417[40] = state[6];
   out_5042249891606824417[41] = 0;
   out_5042249891606824417[42] = state[4];
   out_5042249891606824417[43] = -state[3];
   out_5042249891606824417[44] = 0;
   out_5042249891606824417[45] = 0;
   out_5042249891606824417[46] = 0;
   out_5042249891606824417[47] = 0;
   out_5042249891606824417[48] = 0;
   out_5042249891606824417[49] = 0;
   out_5042249891606824417[50] = 1;
   out_5042249891606824417[51] = 0;
   out_5042249891606824417[52] = 0;
   out_5042249891606824417[53] = 1;
}
void h_13(double *state, double *unused, double *out_3164753833559588683) {
   out_3164753833559588683[0] = state[3];
   out_3164753833559588683[1] = state[4];
   out_3164753833559588683[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8508849711668603094) {
   out_8508849711668603094[0] = 0;
   out_8508849711668603094[1] = 0;
   out_8508849711668603094[2] = 0;
   out_8508849711668603094[3] = 1;
   out_8508849711668603094[4] = 0;
   out_8508849711668603094[5] = 0;
   out_8508849711668603094[6] = 0;
   out_8508849711668603094[7] = 0;
   out_8508849711668603094[8] = 0;
   out_8508849711668603094[9] = 0;
   out_8508849711668603094[10] = 0;
   out_8508849711668603094[11] = 0;
   out_8508849711668603094[12] = 0;
   out_8508849711668603094[13] = 0;
   out_8508849711668603094[14] = 0;
   out_8508849711668603094[15] = 0;
   out_8508849711668603094[16] = 0;
   out_8508849711668603094[17] = 0;
   out_8508849711668603094[18] = 0;
   out_8508849711668603094[19] = 0;
   out_8508849711668603094[20] = 0;
   out_8508849711668603094[21] = 0;
   out_8508849711668603094[22] = 1;
   out_8508849711668603094[23] = 0;
   out_8508849711668603094[24] = 0;
   out_8508849711668603094[25] = 0;
   out_8508849711668603094[26] = 0;
   out_8508849711668603094[27] = 0;
   out_8508849711668603094[28] = 0;
   out_8508849711668603094[29] = 0;
   out_8508849711668603094[30] = 0;
   out_8508849711668603094[31] = 0;
   out_8508849711668603094[32] = 0;
   out_8508849711668603094[33] = 0;
   out_8508849711668603094[34] = 0;
   out_8508849711668603094[35] = 0;
   out_8508849711668603094[36] = 0;
   out_8508849711668603094[37] = 0;
   out_8508849711668603094[38] = 0;
   out_8508849711668603094[39] = 0;
   out_8508849711668603094[40] = 0;
   out_8508849711668603094[41] = 1;
   out_8508849711668603094[42] = 0;
   out_8508849711668603094[43] = 0;
   out_8508849711668603094[44] = 0;
   out_8508849711668603094[45] = 0;
   out_8508849711668603094[46] = 0;
   out_8508849711668603094[47] = 0;
   out_8508849711668603094[48] = 0;
   out_8508849711668603094[49] = 0;
   out_8508849711668603094[50] = 0;
   out_8508849711668603094[51] = 0;
   out_8508849711668603094[52] = 0;
   out_8508849711668603094[53] = 0;
}
void h_14(double *state, double *unused, double *out_3107433859522874355) {
   out_3107433859522874355[0] = state[6];
   out_3107433859522874355[1] = state[7];
   out_3107433859522874355[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2213787454040897997) {
   out_2213787454040897997[0] = 0;
   out_2213787454040897997[1] = 0;
   out_2213787454040897997[2] = 0;
   out_2213787454040897997[3] = 0;
   out_2213787454040897997[4] = 0;
   out_2213787454040897997[5] = 0;
   out_2213787454040897997[6] = 1;
   out_2213787454040897997[7] = 0;
   out_2213787454040897997[8] = 0;
   out_2213787454040897997[9] = 0;
   out_2213787454040897997[10] = 0;
   out_2213787454040897997[11] = 0;
   out_2213787454040897997[12] = 0;
   out_2213787454040897997[13] = 0;
   out_2213787454040897997[14] = 0;
   out_2213787454040897997[15] = 0;
   out_2213787454040897997[16] = 0;
   out_2213787454040897997[17] = 0;
   out_2213787454040897997[18] = 0;
   out_2213787454040897997[19] = 0;
   out_2213787454040897997[20] = 0;
   out_2213787454040897997[21] = 0;
   out_2213787454040897997[22] = 0;
   out_2213787454040897997[23] = 0;
   out_2213787454040897997[24] = 0;
   out_2213787454040897997[25] = 1;
   out_2213787454040897997[26] = 0;
   out_2213787454040897997[27] = 0;
   out_2213787454040897997[28] = 0;
   out_2213787454040897997[29] = 0;
   out_2213787454040897997[30] = 0;
   out_2213787454040897997[31] = 0;
   out_2213787454040897997[32] = 0;
   out_2213787454040897997[33] = 0;
   out_2213787454040897997[34] = 0;
   out_2213787454040897997[35] = 0;
   out_2213787454040897997[36] = 0;
   out_2213787454040897997[37] = 0;
   out_2213787454040897997[38] = 0;
   out_2213787454040897997[39] = 0;
   out_2213787454040897997[40] = 0;
   out_2213787454040897997[41] = 0;
   out_2213787454040897997[42] = 0;
   out_2213787454040897997[43] = 0;
   out_2213787454040897997[44] = 1;
   out_2213787454040897997[45] = 0;
   out_2213787454040897997[46] = 0;
   out_2213787454040897997[47] = 0;
   out_2213787454040897997[48] = 0;
   out_2213787454040897997[49] = 0;
   out_2213787454040897997[50] = 0;
   out_2213787454040897997[51] = 0;
   out_2213787454040897997[52] = 0;
   out_2213787454040897997[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5735299356181127199) {
  err_fun(nom_x, delta_x, out_5735299356181127199);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1848486118618361424) {
  inv_err_fun(nom_x, true_x, out_1848486118618361424);
}
void pose_H_mod_fun(double *state, double *out_3441620345746718845) {
  H_mod_fun(state, out_3441620345746718845);
}
void pose_f_fun(double *state, double dt, double *out_5548337699276970526) {
  f_fun(state,  dt, out_5548337699276970526);
}
void pose_F_fun(double *state, double dt, double *out_6716874081947285130) {
  F_fun(state,  dt, out_6716874081947285130);
}
void pose_h_4(double *state, double *unused, double *out_6172444408937598103) {
  h_4(state, unused, out_6172444408937598103);
}
void pose_H_4(double *state, double *unused, double *out_5296575886336270293) {
  H_4(state, unused, out_5296575886336270293);
}
void pose_h_10(double *state, double *unused, double *out_2819440341260442129) {
  h_10(state, unused, out_2819440341260442129);
}
void pose_H_10(double *state, double *unused, double *out_5042249891606824417) {
  H_10(state, unused, out_5042249891606824417);
}
void pose_h_13(double *state, double *unused, double *out_3164753833559588683) {
  h_13(state, unused, out_3164753833559588683);
}
void pose_H_13(double *state, double *unused, double *out_8508849711668603094) {
  H_13(state, unused, out_8508849711668603094);
}
void pose_h_14(double *state, double *unused, double *out_3107433859522874355) {
  h_14(state, unused, out_3107433859522874355);
}
void pose_H_14(double *state, double *unused, double *out_2213787454040897997) {
  H_14(state, unused, out_2213787454040897997);
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
