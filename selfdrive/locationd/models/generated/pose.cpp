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
void err_fun(double *nom_x, double *delta_x, double *out_4294292118997978771) {
   out_4294292118997978771[0] = delta_x[0] + nom_x[0];
   out_4294292118997978771[1] = delta_x[1] + nom_x[1];
   out_4294292118997978771[2] = delta_x[2] + nom_x[2];
   out_4294292118997978771[3] = delta_x[3] + nom_x[3];
   out_4294292118997978771[4] = delta_x[4] + nom_x[4];
   out_4294292118997978771[5] = delta_x[5] + nom_x[5];
   out_4294292118997978771[6] = delta_x[6] + nom_x[6];
   out_4294292118997978771[7] = delta_x[7] + nom_x[7];
   out_4294292118997978771[8] = delta_x[8] + nom_x[8];
   out_4294292118997978771[9] = delta_x[9] + nom_x[9];
   out_4294292118997978771[10] = delta_x[10] + nom_x[10];
   out_4294292118997978771[11] = delta_x[11] + nom_x[11];
   out_4294292118997978771[12] = delta_x[12] + nom_x[12];
   out_4294292118997978771[13] = delta_x[13] + nom_x[13];
   out_4294292118997978771[14] = delta_x[14] + nom_x[14];
   out_4294292118997978771[15] = delta_x[15] + nom_x[15];
   out_4294292118997978771[16] = delta_x[16] + nom_x[16];
   out_4294292118997978771[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4013254910072164359) {
   out_4013254910072164359[0] = -nom_x[0] + true_x[0];
   out_4013254910072164359[1] = -nom_x[1] + true_x[1];
   out_4013254910072164359[2] = -nom_x[2] + true_x[2];
   out_4013254910072164359[3] = -nom_x[3] + true_x[3];
   out_4013254910072164359[4] = -nom_x[4] + true_x[4];
   out_4013254910072164359[5] = -nom_x[5] + true_x[5];
   out_4013254910072164359[6] = -nom_x[6] + true_x[6];
   out_4013254910072164359[7] = -nom_x[7] + true_x[7];
   out_4013254910072164359[8] = -nom_x[8] + true_x[8];
   out_4013254910072164359[9] = -nom_x[9] + true_x[9];
   out_4013254910072164359[10] = -nom_x[10] + true_x[10];
   out_4013254910072164359[11] = -nom_x[11] + true_x[11];
   out_4013254910072164359[12] = -nom_x[12] + true_x[12];
   out_4013254910072164359[13] = -nom_x[13] + true_x[13];
   out_4013254910072164359[14] = -nom_x[14] + true_x[14];
   out_4013254910072164359[15] = -nom_x[15] + true_x[15];
   out_4013254910072164359[16] = -nom_x[16] + true_x[16];
   out_4013254910072164359[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_896657555631845271) {
   out_896657555631845271[0] = 1.0;
   out_896657555631845271[1] = 0.0;
   out_896657555631845271[2] = 0.0;
   out_896657555631845271[3] = 0.0;
   out_896657555631845271[4] = 0.0;
   out_896657555631845271[5] = 0.0;
   out_896657555631845271[6] = 0.0;
   out_896657555631845271[7] = 0.0;
   out_896657555631845271[8] = 0.0;
   out_896657555631845271[9] = 0.0;
   out_896657555631845271[10] = 0.0;
   out_896657555631845271[11] = 0.0;
   out_896657555631845271[12] = 0.0;
   out_896657555631845271[13] = 0.0;
   out_896657555631845271[14] = 0.0;
   out_896657555631845271[15] = 0.0;
   out_896657555631845271[16] = 0.0;
   out_896657555631845271[17] = 0.0;
   out_896657555631845271[18] = 0.0;
   out_896657555631845271[19] = 1.0;
   out_896657555631845271[20] = 0.0;
   out_896657555631845271[21] = 0.0;
   out_896657555631845271[22] = 0.0;
   out_896657555631845271[23] = 0.0;
   out_896657555631845271[24] = 0.0;
   out_896657555631845271[25] = 0.0;
   out_896657555631845271[26] = 0.0;
   out_896657555631845271[27] = 0.0;
   out_896657555631845271[28] = 0.0;
   out_896657555631845271[29] = 0.0;
   out_896657555631845271[30] = 0.0;
   out_896657555631845271[31] = 0.0;
   out_896657555631845271[32] = 0.0;
   out_896657555631845271[33] = 0.0;
   out_896657555631845271[34] = 0.0;
   out_896657555631845271[35] = 0.0;
   out_896657555631845271[36] = 0.0;
   out_896657555631845271[37] = 0.0;
   out_896657555631845271[38] = 1.0;
   out_896657555631845271[39] = 0.0;
   out_896657555631845271[40] = 0.0;
   out_896657555631845271[41] = 0.0;
   out_896657555631845271[42] = 0.0;
   out_896657555631845271[43] = 0.0;
   out_896657555631845271[44] = 0.0;
   out_896657555631845271[45] = 0.0;
   out_896657555631845271[46] = 0.0;
   out_896657555631845271[47] = 0.0;
   out_896657555631845271[48] = 0.0;
   out_896657555631845271[49] = 0.0;
   out_896657555631845271[50] = 0.0;
   out_896657555631845271[51] = 0.0;
   out_896657555631845271[52] = 0.0;
   out_896657555631845271[53] = 0.0;
   out_896657555631845271[54] = 0.0;
   out_896657555631845271[55] = 0.0;
   out_896657555631845271[56] = 0.0;
   out_896657555631845271[57] = 1.0;
   out_896657555631845271[58] = 0.0;
   out_896657555631845271[59] = 0.0;
   out_896657555631845271[60] = 0.0;
   out_896657555631845271[61] = 0.0;
   out_896657555631845271[62] = 0.0;
   out_896657555631845271[63] = 0.0;
   out_896657555631845271[64] = 0.0;
   out_896657555631845271[65] = 0.0;
   out_896657555631845271[66] = 0.0;
   out_896657555631845271[67] = 0.0;
   out_896657555631845271[68] = 0.0;
   out_896657555631845271[69] = 0.0;
   out_896657555631845271[70] = 0.0;
   out_896657555631845271[71] = 0.0;
   out_896657555631845271[72] = 0.0;
   out_896657555631845271[73] = 0.0;
   out_896657555631845271[74] = 0.0;
   out_896657555631845271[75] = 0.0;
   out_896657555631845271[76] = 1.0;
   out_896657555631845271[77] = 0.0;
   out_896657555631845271[78] = 0.0;
   out_896657555631845271[79] = 0.0;
   out_896657555631845271[80] = 0.0;
   out_896657555631845271[81] = 0.0;
   out_896657555631845271[82] = 0.0;
   out_896657555631845271[83] = 0.0;
   out_896657555631845271[84] = 0.0;
   out_896657555631845271[85] = 0.0;
   out_896657555631845271[86] = 0.0;
   out_896657555631845271[87] = 0.0;
   out_896657555631845271[88] = 0.0;
   out_896657555631845271[89] = 0.0;
   out_896657555631845271[90] = 0.0;
   out_896657555631845271[91] = 0.0;
   out_896657555631845271[92] = 0.0;
   out_896657555631845271[93] = 0.0;
   out_896657555631845271[94] = 0.0;
   out_896657555631845271[95] = 1.0;
   out_896657555631845271[96] = 0.0;
   out_896657555631845271[97] = 0.0;
   out_896657555631845271[98] = 0.0;
   out_896657555631845271[99] = 0.0;
   out_896657555631845271[100] = 0.0;
   out_896657555631845271[101] = 0.0;
   out_896657555631845271[102] = 0.0;
   out_896657555631845271[103] = 0.0;
   out_896657555631845271[104] = 0.0;
   out_896657555631845271[105] = 0.0;
   out_896657555631845271[106] = 0.0;
   out_896657555631845271[107] = 0.0;
   out_896657555631845271[108] = 0.0;
   out_896657555631845271[109] = 0.0;
   out_896657555631845271[110] = 0.0;
   out_896657555631845271[111] = 0.0;
   out_896657555631845271[112] = 0.0;
   out_896657555631845271[113] = 0.0;
   out_896657555631845271[114] = 1.0;
   out_896657555631845271[115] = 0.0;
   out_896657555631845271[116] = 0.0;
   out_896657555631845271[117] = 0.0;
   out_896657555631845271[118] = 0.0;
   out_896657555631845271[119] = 0.0;
   out_896657555631845271[120] = 0.0;
   out_896657555631845271[121] = 0.0;
   out_896657555631845271[122] = 0.0;
   out_896657555631845271[123] = 0.0;
   out_896657555631845271[124] = 0.0;
   out_896657555631845271[125] = 0.0;
   out_896657555631845271[126] = 0.0;
   out_896657555631845271[127] = 0.0;
   out_896657555631845271[128] = 0.0;
   out_896657555631845271[129] = 0.0;
   out_896657555631845271[130] = 0.0;
   out_896657555631845271[131] = 0.0;
   out_896657555631845271[132] = 0.0;
   out_896657555631845271[133] = 1.0;
   out_896657555631845271[134] = 0.0;
   out_896657555631845271[135] = 0.0;
   out_896657555631845271[136] = 0.0;
   out_896657555631845271[137] = 0.0;
   out_896657555631845271[138] = 0.0;
   out_896657555631845271[139] = 0.0;
   out_896657555631845271[140] = 0.0;
   out_896657555631845271[141] = 0.0;
   out_896657555631845271[142] = 0.0;
   out_896657555631845271[143] = 0.0;
   out_896657555631845271[144] = 0.0;
   out_896657555631845271[145] = 0.0;
   out_896657555631845271[146] = 0.0;
   out_896657555631845271[147] = 0.0;
   out_896657555631845271[148] = 0.0;
   out_896657555631845271[149] = 0.0;
   out_896657555631845271[150] = 0.0;
   out_896657555631845271[151] = 0.0;
   out_896657555631845271[152] = 1.0;
   out_896657555631845271[153] = 0.0;
   out_896657555631845271[154] = 0.0;
   out_896657555631845271[155] = 0.0;
   out_896657555631845271[156] = 0.0;
   out_896657555631845271[157] = 0.0;
   out_896657555631845271[158] = 0.0;
   out_896657555631845271[159] = 0.0;
   out_896657555631845271[160] = 0.0;
   out_896657555631845271[161] = 0.0;
   out_896657555631845271[162] = 0.0;
   out_896657555631845271[163] = 0.0;
   out_896657555631845271[164] = 0.0;
   out_896657555631845271[165] = 0.0;
   out_896657555631845271[166] = 0.0;
   out_896657555631845271[167] = 0.0;
   out_896657555631845271[168] = 0.0;
   out_896657555631845271[169] = 0.0;
   out_896657555631845271[170] = 0.0;
   out_896657555631845271[171] = 1.0;
   out_896657555631845271[172] = 0.0;
   out_896657555631845271[173] = 0.0;
   out_896657555631845271[174] = 0.0;
   out_896657555631845271[175] = 0.0;
   out_896657555631845271[176] = 0.0;
   out_896657555631845271[177] = 0.0;
   out_896657555631845271[178] = 0.0;
   out_896657555631845271[179] = 0.0;
   out_896657555631845271[180] = 0.0;
   out_896657555631845271[181] = 0.0;
   out_896657555631845271[182] = 0.0;
   out_896657555631845271[183] = 0.0;
   out_896657555631845271[184] = 0.0;
   out_896657555631845271[185] = 0.0;
   out_896657555631845271[186] = 0.0;
   out_896657555631845271[187] = 0.0;
   out_896657555631845271[188] = 0.0;
   out_896657555631845271[189] = 0.0;
   out_896657555631845271[190] = 1.0;
   out_896657555631845271[191] = 0.0;
   out_896657555631845271[192] = 0.0;
   out_896657555631845271[193] = 0.0;
   out_896657555631845271[194] = 0.0;
   out_896657555631845271[195] = 0.0;
   out_896657555631845271[196] = 0.0;
   out_896657555631845271[197] = 0.0;
   out_896657555631845271[198] = 0.0;
   out_896657555631845271[199] = 0.0;
   out_896657555631845271[200] = 0.0;
   out_896657555631845271[201] = 0.0;
   out_896657555631845271[202] = 0.0;
   out_896657555631845271[203] = 0.0;
   out_896657555631845271[204] = 0.0;
   out_896657555631845271[205] = 0.0;
   out_896657555631845271[206] = 0.0;
   out_896657555631845271[207] = 0.0;
   out_896657555631845271[208] = 0.0;
   out_896657555631845271[209] = 1.0;
   out_896657555631845271[210] = 0.0;
   out_896657555631845271[211] = 0.0;
   out_896657555631845271[212] = 0.0;
   out_896657555631845271[213] = 0.0;
   out_896657555631845271[214] = 0.0;
   out_896657555631845271[215] = 0.0;
   out_896657555631845271[216] = 0.0;
   out_896657555631845271[217] = 0.0;
   out_896657555631845271[218] = 0.0;
   out_896657555631845271[219] = 0.0;
   out_896657555631845271[220] = 0.0;
   out_896657555631845271[221] = 0.0;
   out_896657555631845271[222] = 0.0;
   out_896657555631845271[223] = 0.0;
   out_896657555631845271[224] = 0.0;
   out_896657555631845271[225] = 0.0;
   out_896657555631845271[226] = 0.0;
   out_896657555631845271[227] = 0.0;
   out_896657555631845271[228] = 1.0;
   out_896657555631845271[229] = 0.0;
   out_896657555631845271[230] = 0.0;
   out_896657555631845271[231] = 0.0;
   out_896657555631845271[232] = 0.0;
   out_896657555631845271[233] = 0.0;
   out_896657555631845271[234] = 0.0;
   out_896657555631845271[235] = 0.0;
   out_896657555631845271[236] = 0.0;
   out_896657555631845271[237] = 0.0;
   out_896657555631845271[238] = 0.0;
   out_896657555631845271[239] = 0.0;
   out_896657555631845271[240] = 0.0;
   out_896657555631845271[241] = 0.0;
   out_896657555631845271[242] = 0.0;
   out_896657555631845271[243] = 0.0;
   out_896657555631845271[244] = 0.0;
   out_896657555631845271[245] = 0.0;
   out_896657555631845271[246] = 0.0;
   out_896657555631845271[247] = 1.0;
   out_896657555631845271[248] = 0.0;
   out_896657555631845271[249] = 0.0;
   out_896657555631845271[250] = 0.0;
   out_896657555631845271[251] = 0.0;
   out_896657555631845271[252] = 0.0;
   out_896657555631845271[253] = 0.0;
   out_896657555631845271[254] = 0.0;
   out_896657555631845271[255] = 0.0;
   out_896657555631845271[256] = 0.0;
   out_896657555631845271[257] = 0.0;
   out_896657555631845271[258] = 0.0;
   out_896657555631845271[259] = 0.0;
   out_896657555631845271[260] = 0.0;
   out_896657555631845271[261] = 0.0;
   out_896657555631845271[262] = 0.0;
   out_896657555631845271[263] = 0.0;
   out_896657555631845271[264] = 0.0;
   out_896657555631845271[265] = 0.0;
   out_896657555631845271[266] = 1.0;
   out_896657555631845271[267] = 0.0;
   out_896657555631845271[268] = 0.0;
   out_896657555631845271[269] = 0.0;
   out_896657555631845271[270] = 0.0;
   out_896657555631845271[271] = 0.0;
   out_896657555631845271[272] = 0.0;
   out_896657555631845271[273] = 0.0;
   out_896657555631845271[274] = 0.0;
   out_896657555631845271[275] = 0.0;
   out_896657555631845271[276] = 0.0;
   out_896657555631845271[277] = 0.0;
   out_896657555631845271[278] = 0.0;
   out_896657555631845271[279] = 0.0;
   out_896657555631845271[280] = 0.0;
   out_896657555631845271[281] = 0.0;
   out_896657555631845271[282] = 0.0;
   out_896657555631845271[283] = 0.0;
   out_896657555631845271[284] = 0.0;
   out_896657555631845271[285] = 1.0;
   out_896657555631845271[286] = 0.0;
   out_896657555631845271[287] = 0.0;
   out_896657555631845271[288] = 0.0;
   out_896657555631845271[289] = 0.0;
   out_896657555631845271[290] = 0.0;
   out_896657555631845271[291] = 0.0;
   out_896657555631845271[292] = 0.0;
   out_896657555631845271[293] = 0.0;
   out_896657555631845271[294] = 0.0;
   out_896657555631845271[295] = 0.0;
   out_896657555631845271[296] = 0.0;
   out_896657555631845271[297] = 0.0;
   out_896657555631845271[298] = 0.0;
   out_896657555631845271[299] = 0.0;
   out_896657555631845271[300] = 0.0;
   out_896657555631845271[301] = 0.0;
   out_896657555631845271[302] = 0.0;
   out_896657555631845271[303] = 0.0;
   out_896657555631845271[304] = 1.0;
   out_896657555631845271[305] = 0.0;
   out_896657555631845271[306] = 0.0;
   out_896657555631845271[307] = 0.0;
   out_896657555631845271[308] = 0.0;
   out_896657555631845271[309] = 0.0;
   out_896657555631845271[310] = 0.0;
   out_896657555631845271[311] = 0.0;
   out_896657555631845271[312] = 0.0;
   out_896657555631845271[313] = 0.0;
   out_896657555631845271[314] = 0.0;
   out_896657555631845271[315] = 0.0;
   out_896657555631845271[316] = 0.0;
   out_896657555631845271[317] = 0.0;
   out_896657555631845271[318] = 0.0;
   out_896657555631845271[319] = 0.0;
   out_896657555631845271[320] = 0.0;
   out_896657555631845271[321] = 0.0;
   out_896657555631845271[322] = 0.0;
   out_896657555631845271[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8443743878960458350) {
   out_8443743878960458350[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8443743878960458350[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8443743878960458350[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8443743878960458350[3] = dt*state[12] + state[3];
   out_8443743878960458350[4] = dt*state[13] + state[4];
   out_8443743878960458350[5] = dt*state[14] + state[5];
   out_8443743878960458350[6] = state[6];
   out_8443743878960458350[7] = state[7];
   out_8443743878960458350[8] = state[8];
   out_8443743878960458350[9] = state[9];
   out_8443743878960458350[10] = state[10];
   out_8443743878960458350[11] = state[11];
   out_8443743878960458350[12] = state[12];
   out_8443743878960458350[13] = state[13];
   out_8443743878960458350[14] = state[14];
   out_8443743878960458350[15] = state[15];
   out_8443743878960458350[16] = state[16];
   out_8443743878960458350[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8213357667145446301) {
   out_8213357667145446301[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8213357667145446301[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8213357667145446301[2] = 0;
   out_8213357667145446301[3] = 0;
   out_8213357667145446301[4] = 0;
   out_8213357667145446301[5] = 0;
   out_8213357667145446301[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8213357667145446301[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8213357667145446301[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8213357667145446301[9] = 0;
   out_8213357667145446301[10] = 0;
   out_8213357667145446301[11] = 0;
   out_8213357667145446301[12] = 0;
   out_8213357667145446301[13] = 0;
   out_8213357667145446301[14] = 0;
   out_8213357667145446301[15] = 0;
   out_8213357667145446301[16] = 0;
   out_8213357667145446301[17] = 0;
   out_8213357667145446301[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8213357667145446301[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8213357667145446301[20] = 0;
   out_8213357667145446301[21] = 0;
   out_8213357667145446301[22] = 0;
   out_8213357667145446301[23] = 0;
   out_8213357667145446301[24] = 0;
   out_8213357667145446301[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8213357667145446301[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8213357667145446301[27] = 0;
   out_8213357667145446301[28] = 0;
   out_8213357667145446301[29] = 0;
   out_8213357667145446301[30] = 0;
   out_8213357667145446301[31] = 0;
   out_8213357667145446301[32] = 0;
   out_8213357667145446301[33] = 0;
   out_8213357667145446301[34] = 0;
   out_8213357667145446301[35] = 0;
   out_8213357667145446301[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8213357667145446301[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8213357667145446301[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8213357667145446301[39] = 0;
   out_8213357667145446301[40] = 0;
   out_8213357667145446301[41] = 0;
   out_8213357667145446301[42] = 0;
   out_8213357667145446301[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8213357667145446301[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8213357667145446301[45] = 0;
   out_8213357667145446301[46] = 0;
   out_8213357667145446301[47] = 0;
   out_8213357667145446301[48] = 0;
   out_8213357667145446301[49] = 0;
   out_8213357667145446301[50] = 0;
   out_8213357667145446301[51] = 0;
   out_8213357667145446301[52] = 0;
   out_8213357667145446301[53] = 0;
   out_8213357667145446301[54] = 0;
   out_8213357667145446301[55] = 0;
   out_8213357667145446301[56] = 0;
   out_8213357667145446301[57] = 1;
   out_8213357667145446301[58] = 0;
   out_8213357667145446301[59] = 0;
   out_8213357667145446301[60] = 0;
   out_8213357667145446301[61] = 0;
   out_8213357667145446301[62] = 0;
   out_8213357667145446301[63] = 0;
   out_8213357667145446301[64] = 0;
   out_8213357667145446301[65] = 0;
   out_8213357667145446301[66] = dt;
   out_8213357667145446301[67] = 0;
   out_8213357667145446301[68] = 0;
   out_8213357667145446301[69] = 0;
   out_8213357667145446301[70] = 0;
   out_8213357667145446301[71] = 0;
   out_8213357667145446301[72] = 0;
   out_8213357667145446301[73] = 0;
   out_8213357667145446301[74] = 0;
   out_8213357667145446301[75] = 0;
   out_8213357667145446301[76] = 1;
   out_8213357667145446301[77] = 0;
   out_8213357667145446301[78] = 0;
   out_8213357667145446301[79] = 0;
   out_8213357667145446301[80] = 0;
   out_8213357667145446301[81] = 0;
   out_8213357667145446301[82] = 0;
   out_8213357667145446301[83] = 0;
   out_8213357667145446301[84] = 0;
   out_8213357667145446301[85] = dt;
   out_8213357667145446301[86] = 0;
   out_8213357667145446301[87] = 0;
   out_8213357667145446301[88] = 0;
   out_8213357667145446301[89] = 0;
   out_8213357667145446301[90] = 0;
   out_8213357667145446301[91] = 0;
   out_8213357667145446301[92] = 0;
   out_8213357667145446301[93] = 0;
   out_8213357667145446301[94] = 0;
   out_8213357667145446301[95] = 1;
   out_8213357667145446301[96] = 0;
   out_8213357667145446301[97] = 0;
   out_8213357667145446301[98] = 0;
   out_8213357667145446301[99] = 0;
   out_8213357667145446301[100] = 0;
   out_8213357667145446301[101] = 0;
   out_8213357667145446301[102] = 0;
   out_8213357667145446301[103] = 0;
   out_8213357667145446301[104] = dt;
   out_8213357667145446301[105] = 0;
   out_8213357667145446301[106] = 0;
   out_8213357667145446301[107] = 0;
   out_8213357667145446301[108] = 0;
   out_8213357667145446301[109] = 0;
   out_8213357667145446301[110] = 0;
   out_8213357667145446301[111] = 0;
   out_8213357667145446301[112] = 0;
   out_8213357667145446301[113] = 0;
   out_8213357667145446301[114] = 1;
   out_8213357667145446301[115] = 0;
   out_8213357667145446301[116] = 0;
   out_8213357667145446301[117] = 0;
   out_8213357667145446301[118] = 0;
   out_8213357667145446301[119] = 0;
   out_8213357667145446301[120] = 0;
   out_8213357667145446301[121] = 0;
   out_8213357667145446301[122] = 0;
   out_8213357667145446301[123] = 0;
   out_8213357667145446301[124] = 0;
   out_8213357667145446301[125] = 0;
   out_8213357667145446301[126] = 0;
   out_8213357667145446301[127] = 0;
   out_8213357667145446301[128] = 0;
   out_8213357667145446301[129] = 0;
   out_8213357667145446301[130] = 0;
   out_8213357667145446301[131] = 0;
   out_8213357667145446301[132] = 0;
   out_8213357667145446301[133] = 1;
   out_8213357667145446301[134] = 0;
   out_8213357667145446301[135] = 0;
   out_8213357667145446301[136] = 0;
   out_8213357667145446301[137] = 0;
   out_8213357667145446301[138] = 0;
   out_8213357667145446301[139] = 0;
   out_8213357667145446301[140] = 0;
   out_8213357667145446301[141] = 0;
   out_8213357667145446301[142] = 0;
   out_8213357667145446301[143] = 0;
   out_8213357667145446301[144] = 0;
   out_8213357667145446301[145] = 0;
   out_8213357667145446301[146] = 0;
   out_8213357667145446301[147] = 0;
   out_8213357667145446301[148] = 0;
   out_8213357667145446301[149] = 0;
   out_8213357667145446301[150] = 0;
   out_8213357667145446301[151] = 0;
   out_8213357667145446301[152] = 1;
   out_8213357667145446301[153] = 0;
   out_8213357667145446301[154] = 0;
   out_8213357667145446301[155] = 0;
   out_8213357667145446301[156] = 0;
   out_8213357667145446301[157] = 0;
   out_8213357667145446301[158] = 0;
   out_8213357667145446301[159] = 0;
   out_8213357667145446301[160] = 0;
   out_8213357667145446301[161] = 0;
   out_8213357667145446301[162] = 0;
   out_8213357667145446301[163] = 0;
   out_8213357667145446301[164] = 0;
   out_8213357667145446301[165] = 0;
   out_8213357667145446301[166] = 0;
   out_8213357667145446301[167] = 0;
   out_8213357667145446301[168] = 0;
   out_8213357667145446301[169] = 0;
   out_8213357667145446301[170] = 0;
   out_8213357667145446301[171] = 1;
   out_8213357667145446301[172] = 0;
   out_8213357667145446301[173] = 0;
   out_8213357667145446301[174] = 0;
   out_8213357667145446301[175] = 0;
   out_8213357667145446301[176] = 0;
   out_8213357667145446301[177] = 0;
   out_8213357667145446301[178] = 0;
   out_8213357667145446301[179] = 0;
   out_8213357667145446301[180] = 0;
   out_8213357667145446301[181] = 0;
   out_8213357667145446301[182] = 0;
   out_8213357667145446301[183] = 0;
   out_8213357667145446301[184] = 0;
   out_8213357667145446301[185] = 0;
   out_8213357667145446301[186] = 0;
   out_8213357667145446301[187] = 0;
   out_8213357667145446301[188] = 0;
   out_8213357667145446301[189] = 0;
   out_8213357667145446301[190] = 1;
   out_8213357667145446301[191] = 0;
   out_8213357667145446301[192] = 0;
   out_8213357667145446301[193] = 0;
   out_8213357667145446301[194] = 0;
   out_8213357667145446301[195] = 0;
   out_8213357667145446301[196] = 0;
   out_8213357667145446301[197] = 0;
   out_8213357667145446301[198] = 0;
   out_8213357667145446301[199] = 0;
   out_8213357667145446301[200] = 0;
   out_8213357667145446301[201] = 0;
   out_8213357667145446301[202] = 0;
   out_8213357667145446301[203] = 0;
   out_8213357667145446301[204] = 0;
   out_8213357667145446301[205] = 0;
   out_8213357667145446301[206] = 0;
   out_8213357667145446301[207] = 0;
   out_8213357667145446301[208] = 0;
   out_8213357667145446301[209] = 1;
   out_8213357667145446301[210] = 0;
   out_8213357667145446301[211] = 0;
   out_8213357667145446301[212] = 0;
   out_8213357667145446301[213] = 0;
   out_8213357667145446301[214] = 0;
   out_8213357667145446301[215] = 0;
   out_8213357667145446301[216] = 0;
   out_8213357667145446301[217] = 0;
   out_8213357667145446301[218] = 0;
   out_8213357667145446301[219] = 0;
   out_8213357667145446301[220] = 0;
   out_8213357667145446301[221] = 0;
   out_8213357667145446301[222] = 0;
   out_8213357667145446301[223] = 0;
   out_8213357667145446301[224] = 0;
   out_8213357667145446301[225] = 0;
   out_8213357667145446301[226] = 0;
   out_8213357667145446301[227] = 0;
   out_8213357667145446301[228] = 1;
   out_8213357667145446301[229] = 0;
   out_8213357667145446301[230] = 0;
   out_8213357667145446301[231] = 0;
   out_8213357667145446301[232] = 0;
   out_8213357667145446301[233] = 0;
   out_8213357667145446301[234] = 0;
   out_8213357667145446301[235] = 0;
   out_8213357667145446301[236] = 0;
   out_8213357667145446301[237] = 0;
   out_8213357667145446301[238] = 0;
   out_8213357667145446301[239] = 0;
   out_8213357667145446301[240] = 0;
   out_8213357667145446301[241] = 0;
   out_8213357667145446301[242] = 0;
   out_8213357667145446301[243] = 0;
   out_8213357667145446301[244] = 0;
   out_8213357667145446301[245] = 0;
   out_8213357667145446301[246] = 0;
   out_8213357667145446301[247] = 1;
   out_8213357667145446301[248] = 0;
   out_8213357667145446301[249] = 0;
   out_8213357667145446301[250] = 0;
   out_8213357667145446301[251] = 0;
   out_8213357667145446301[252] = 0;
   out_8213357667145446301[253] = 0;
   out_8213357667145446301[254] = 0;
   out_8213357667145446301[255] = 0;
   out_8213357667145446301[256] = 0;
   out_8213357667145446301[257] = 0;
   out_8213357667145446301[258] = 0;
   out_8213357667145446301[259] = 0;
   out_8213357667145446301[260] = 0;
   out_8213357667145446301[261] = 0;
   out_8213357667145446301[262] = 0;
   out_8213357667145446301[263] = 0;
   out_8213357667145446301[264] = 0;
   out_8213357667145446301[265] = 0;
   out_8213357667145446301[266] = 1;
   out_8213357667145446301[267] = 0;
   out_8213357667145446301[268] = 0;
   out_8213357667145446301[269] = 0;
   out_8213357667145446301[270] = 0;
   out_8213357667145446301[271] = 0;
   out_8213357667145446301[272] = 0;
   out_8213357667145446301[273] = 0;
   out_8213357667145446301[274] = 0;
   out_8213357667145446301[275] = 0;
   out_8213357667145446301[276] = 0;
   out_8213357667145446301[277] = 0;
   out_8213357667145446301[278] = 0;
   out_8213357667145446301[279] = 0;
   out_8213357667145446301[280] = 0;
   out_8213357667145446301[281] = 0;
   out_8213357667145446301[282] = 0;
   out_8213357667145446301[283] = 0;
   out_8213357667145446301[284] = 0;
   out_8213357667145446301[285] = 1;
   out_8213357667145446301[286] = 0;
   out_8213357667145446301[287] = 0;
   out_8213357667145446301[288] = 0;
   out_8213357667145446301[289] = 0;
   out_8213357667145446301[290] = 0;
   out_8213357667145446301[291] = 0;
   out_8213357667145446301[292] = 0;
   out_8213357667145446301[293] = 0;
   out_8213357667145446301[294] = 0;
   out_8213357667145446301[295] = 0;
   out_8213357667145446301[296] = 0;
   out_8213357667145446301[297] = 0;
   out_8213357667145446301[298] = 0;
   out_8213357667145446301[299] = 0;
   out_8213357667145446301[300] = 0;
   out_8213357667145446301[301] = 0;
   out_8213357667145446301[302] = 0;
   out_8213357667145446301[303] = 0;
   out_8213357667145446301[304] = 1;
   out_8213357667145446301[305] = 0;
   out_8213357667145446301[306] = 0;
   out_8213357667145446301[307] = 0;
   out_8213357667145446301[308] = 0;
   out_8213357667145446301[309] = 0;
   out_8213357667145446301[310] = 0;
   out_8213357667145446301[311] = 0;
   out_8213357667145446301[312] = 0;
   out_8213357667145446301[313] = 0;
   out_8213357667145446301[314] = 0;
   out_8213357667145446301[315] = 0;
   out_8213357667145446301[316] = 0;
   out_8213357667145446301[317] = 0;
   out_8213357667145446301[318] = 0;
   out_8213357667145446301[319] = 0;
   out_8213357667145446301[320] = 0;
   out_8213357667145446301[321] = 0;
   out_8213357667145446301[322] = 0;
   out_8213357667145446301[323] = 1;
}
void h_4(double *state, double *unused, double *out_70651799205578182) {
   out_70651799205578182[0] = state[6] + state[9];
   out_70651799205578182[1] = state[7] + state[10];
   out_70651799205578182[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6049175940670926006) {
   out_6049175940670926006[0] = 0;
   out_6049175940670926006[1] = 0;
   out_6049175940670926006[2] = 0;
   out_6049175940670926006[3] = 0;
   out_6049175940670926006[4] = 0;
   out_6049175940670926006[5] = 0;
   out_6049175940670926006[6] = 1;
   out_6049175940670926006[7] = 0;
   out_6049175940670926006[8] = 0;
   out_6049175940670926006[9] = 1;
   out_6049175940670926006[10] = 0;
   out_6049175940670926006[11] = 0;
   out_6049175940670926006[12] = 0;
   out_6049175940670926006[13] = 0;
   out_6049175940670926006[14] = 0;
   out_6049175940670926006[15] = 0;
   out_6049175940670926006[16] = 0;
   out_6049175940670926006[17] = 0;
   out_6049175940670926006[18] = 0;
   out_6049175940670926006[19] = 0;
   out_6049175940670926006[20] = 0;
   out_6049175940670926006[21] = 0;
   out_6049175940670926006[22] = 0;
   out_6049175940670926006[23] = 0;
   out_6049175940670926006[24] = 0;
   out_6049175940670926006[25] = 1;
   out_6049175940670926006[26] = 0;
   out_6049175940670926006[27] = 0;
   out_6049175940670926006[28] = 1;
   out_6049175940670926006[29] = 0;
   out_6049175940670926006[30] = 0;
   out_6049175940670926006[31] = 0;
   out_6049175940670926006[32] = 0;
   out_6049175940670926006[33] = 0;
   out_6049175940670926006[34] = 0;
   out_6049175940670926006[35] = 0;
   out_6049175940670926006[36] = 0;
   out_6049175940670926006[37] = 0;
   out_6049175940670926006[38] = 0;
   out_6049175940670926006[39] = 0;
   out_6049175940670926006[40] = 0;
   out_6049175940670926006[41] = 0;
   out_6049175940670926006[42] = 0;
   out_6049175940670926006[43] = 0;
   out_6049175940670926006[44] = 1;
   out_6049175940670926006[45] = 0;
   out_6049175940670926006[46] = 0;
   out_6049175940670926006[47] = 1;
   out_6049175940670926006[48] = 0;
   out_6049175940670926006[49] = 0;
   out_6049175940670926006[50] = 0;
   out_6049175940670926006[51] = 0;
   out_6049175940670926006[52] = 0;
   out_6049175940670926006[53] = 0;
}
void h_10(double *state, double *unused, double *out_3996731865855353315) {
   out_3996731865855353315[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3996731865855353315[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3996731865855353315[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1029675721885226562) {
   out_1029675721885226562[0] = 0;
   out_1029675721885226562[1] = 9.8100000000000005*cos(state[1]);
   out_1029675721885226562[2] = 0;
   out_1029675721885226562[3] = 0;
   out_1029675721885226562[4] = -state[8];
   out_1029675721885226562[5] = state[7];
   out_1029675721885226562[6] = 0;
   out_1029675721885226562[7] = state[5];
   out_1029675721885226562[8] = -state[4];
   out_1029675721885226562[9] = 0;
   out_1029675721885226562[10] = 0;
   out_1029675721885226562[11] = 0;
   out_1029675721885226562[12] = 1;
   out_1029675721885226562[13] = 0;
   out_1029675721885226562[14] = 0;
   out_1029675721885226562[15] = 1;
   out_1029675721885226562[16] = 0;
   out_1029675721885226562[17] = 0;
   out_1029675721885226562[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1029675721885226562[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1029675721885226562[20] = 0;
   out_1029675721885226562[21] = state[8];
   out_1029675721885226562[22] = 0;
   out_1029675721885226562[23] = -state[6];
   out_1029675721885226562[24] = -state[5];
   out_1029675721885226562[25] = 0;
   out_1029675721885226562[26] = state[3];
   out_1029675721885226562[27] = 0;
   out_1029675721885226562[28] = 0;
   out_1029675721885226562[29] = 0;
   out_1029675721885226562[30] = 0;
   out_1029675721885226562[31] = 1;
   out_1029675721885226562[32] = 0;
   out_1029675721885226562[33] = 0;
   out_1029675721885226562[34] = 1;
   out_1029675721885226562[35] = 0;
   out_1029675721885226562[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1029675721885226562[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1029675721885226562[38] = 0;
   out_1029675721885226562[39] = -state[7];
   out_1029675721885226562[40] = state[6];
   out_1029675721885226562[41] = 0;
   out_1029675721885226562[42] = state[4];
   out_1029675721885226562[43] = -state[3];
   out_1029675721885226562[44] = 0;
   out_1029675721885226562[45] = 0;
   out_1029675721885226562[46] = 0;
   out_1029675721885226562[47] = 0;
   out_1029675721885226562[48] = 0;
   out_1029675721885226562[49] = 0;
   out_1029675721885226562[50] = 1;
   out_1029675721885226562[51] = 0;
   out_1029675721885226562[52] = 0;
   out_1029675721885226562[53] = 1;
}
void h_13(double *state, double *unused, double *out_5486873982549130902) {
   out_5486873982549130902[0] = state[3];
   out_5486873982549130902[1] = state[4];
   out_5486873982549130902[2] = state[5];
}
void H_13(double *state, double *unused, double *out_9185294307706292809) {
   out_9185294307706292809[0] = 0;
   out_9185294307706292809[1] = 0;
   out_9185294307706292809[2] = 0;
   out_9185294307706292809[3] = 1;
   out_9185294307706292809[4] = 0;
   out_9185294307706292809[5] = 0;
   out_9185294307706292809[6] = 0;
   out_9185294307706292809[7] = 0;
   out_9185294307706292809[8] = 0;
   out_9185294307706292809[9] = 0;
   out_9185294307706292809[10] = 0;
   out_9185294307706292809[11] = 0;
   out_9185294307706292809[12] = 0;
   out_9185294307706292809[13] = 0;
   out_9185294307706292809[14] = 0;
   out_9185294307706292809[15] = 0;
   out_9185294307706292809[16] = 0;
   out_9185294307706292809[17] = 0;
   out_9185294307706292809[18] = 0;
   out_9185294307706292809[19] = 0;
   out_9185294307706292809[20] = 0;
   out_9185294307706292809[21] = 0;
   out_9185294307706292809[22] = 1;
   out_9185294307706292809[23] = 0;
   out_9185294307706292809[24] = 0;
   out_9185294307706292809[25] = 0;
   out_9185294307706292809[26] = 0;
   out_9185294307706292809[27] = 0;
   out_9185294307706292809[28] = 0;
   out_9185294307706292809[29] = 0;
   out_9185294307706292809[30] = 0;
   out_9185294307706292809[31] = 0;
   out_9185294307706292809[32] = 0;
   out_9185294307706292809[33] = 0;
   out_9185294307706292809[34] = 0;
   out_9185294307706292809[35] = 0;
   out_9185294307706292809[36] = 0;
   out_9185294307706292809[37] = 0;
   out_9185294307706292809[38] = 0;
   out_9185294307706292809[39] = 0;
   out_9185294307706292809[40] = 0;
   out_9185294307706292809[41] = 1;
   out_9185294307706292809[42] = 0;
   out_9185294307706292809[43] = 0;
   out_9185294307706292809[44] = 0;
   out_9185294307706292809[45] = 0;
   out_9185294307706292809[46] = 0;
   out_9185294307706292809[47] = 0;
   out_9185294307706292809[48] = 0;
   out_9185294307706292809[49] = 0;
   out_9185294307706292809[50] = 0;
   out_9185294307706292809[51] = 0;
   out_9185294307706292809[52] = 0;
   out_9185294307706292809[53] = 0;
}
void h_14(double *state, double *unused, double *out_5889763171134805790) {
   out_5889763171134805790[0] = state[6];
   out_5889763171134805790[1] = state[7];
   out_5889763171134805790[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8434327276699141081) {
   out_8434327276699141081[0] = 0;
   out_8434327276699141081[1] = 0;
   out_8434327276699141081[2] = 0;
   out_8434327276699141081[3] = 0;
   out_8434327276699141081[4] = 0;
   out_8434327276699141081[5] = 0;
   out_8434327276699141081[6] = 1;
   out_8434327276699141081[7] = 0;
   out_8434327276699141081[8] = 0;
   out_8434327276699141081[9] = 0;
   out_8434327276699141081[10] = 0;
   out_8434327276699141081[11] = 0;
   out_8434327276699141081[12] = 0;
   out_8434327276699141081[13] = 0;
   out_8434327276699141081[14] = 0;
   out_8434327276699141081[15] = 0;
   out_8434327276699141081[16] = 0;
   out_8434327276699141081[17] = 0;
   out_8434327276699141081[18] = 0;
   out_8434327276699141081[19] = 0;
   out_8434327276699141081[20] = 0;
   out_8434327276699141081[21] = 0;
   out_8434327276699141081[22] = 0;
   out_8434327276699141081[23] = 0;
   out_8434327276699141081[24] = 0;
   out_8434327276699141081[25] = 1;
   out_8434327276699141081[26] = 0;
   out_8434327276699141081[27] = 0;
   out_8434327276699141081[28] = 0;
   out_8434327276699141081[29] = 0;
   out_8434327276699141081[30] = 0;
   out_8434327276699141081[31] = 0;
   out_8434327276699141081[32] = 0;
   out_8434327276699141081[33] = 0;
   out_8434327276699141081[34] = 0;
   out_8434327276699141081[35] = 0;
   out_8434327276699141081[36] = 0;
   out_8434327276699141081[37] = 0;
   out_8434327276699141081[38] = 0;
   out_8434327276699141081[39] = 0;
   out_8434327276699141081[40] = 0;
   out_8434327276699141081[41] = 0;
   out_8434327276699141081[42] = 0;
   out_8434327276699141081[43] = 0;
   out_8434327276699141081[44] = 1;
   out_8434327276699141081[45] = 0;
   out_8434327276699141081[46] = 0;
   out_8434327276699141081[47] = 0;
   out_8434327276699141081[48] = 0;
   out_8434327276699141081[49] = 0;
   out_8434327276699141081[50] = 0;
   out_8434327276699141081[51] = 0;
   out_8434327276699141081[52] = 0;
   out_8434327276699141081[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_4294292118997978771) {
  err_fun(nom_x, delta_x, out_4294292118997978771);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4013254910072164359) {
  inv_err_fun(nom_x, true_x, out_4013254910072164359);
}
void pose_H_mod_fun(double *state, double *out_896657555631845271) {
  H_mod_fun(state, out_896657555631845271);
}
void pose_f_fun(double *state, double dt, double *out_8443743878960458350) {
  f_fun(state,  dt, out_8443743878960458350);
}
void pose_F_fun(double *state, double dt, double *out_8213357667145446301) {
  F_fun(state,  dt, out_8213357667145446301);
}
void pose_h_4(double *state, double *unused, double *out_70651799205578182) {
  h_4(state, unused, out_70651799205578182);
}
void pose_H_4(double *state, double *unused, double *out_6049175940670926006) {
  H_4(state, unused, out_6049175940670926006);
}
void pose_h_10(double *state, double *unused, double *out_3996731865855353315) {
  h_10(state, unused, out_3996731865855353315);
}
void pose_H_10(double *state, double *unused, double *out_1029675721885226562) {
  H_10(state, unused, out_1029675721885226562);
}
void pose_h_13(double *state, double *unused, double *out_5486873982549130902) {
  h_13(state, unused, out_5486873982549130902);
}
void pose_H_13(double *state, double *unused, double *out_9185294307706292809) {
  H_13(state, unused, out_9185294307706292809);
}
void pose_h_14(double *state, double *unused, double *out_5889763171134805790) {
  h_14(state, unused, out_5889763171134805790);
}
void pose_H_14(double *state, double *unused, double *out_8434327276699141081) {
  H_14(state, unused, out_8434327276699141081);
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
