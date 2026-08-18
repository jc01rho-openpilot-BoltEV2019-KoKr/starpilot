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
void err_fun(double *nom_x, double *delta_x, double *out_2182435369834896236) {
   out_2182435369834896236[0] = delta_x[0] + nom_x[0];
   out_2182435369834896236[1] = delta_x[1] + nom_x[1];
   out_2182435369834896236[2] = delta_x[2] + nom_x[2];
   out_2182435369834896236[3] = delta_x[3] + nom_x[3];
   out_2182435369834896236[4] = delta_x[4] + nom_x[4];
   out_2182435369834896236[5] = delta_x[5] + nom_x[5];
   out_2182435369834896236[6] = delta_x[6] + nom_x[6];
   out_2182435369834896236[7] = delta_x[7] + nom_x[7];
   out_2182435369834896236[8] = delta_x[8] + nom_x[8];
   out_2182435369834896236[9] = delta_x[9] + nom_x[9];
   out_2182435369834896236[10] = delta_x[10] + nom_x[10];
   out_2182435369834896236[11] = delta_x[11] + nom_x[11];
   out_2182435369834896236[12] = delta_x[12] + nom_x[12];
   out_2182435369834896236[13] = delta_x[13] + nom_x[13];
   out_2182435369834896236[14] = delta_x[14] + nom_x[14];
   out_2182435369834896236[15] = delta_x[15] + nom_x[15];
   out_2182435369834896236[16] = delta_x[16] + nom_x[16];
   out_2182435369834896236[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2883166859334089197) {
   out_2883166859334089197[0] = -nom_x[0] + true_x[0];
   out_2883166859334089197[1] = -nom_x[1] + true_x[1];
   out_2883166859334089197[2] = -nom_x[2] + true_x[2];
   out_2883166859334089197[3] = -nom_x[3] + true_x[3];
   out_2883166859334089197[4] = -nom_x[4] + true_x[4];
   out_2883166859334089197[5] = -nom_x[5] + true_x[5];
   out_2883166859334089197[6] = -nom_x[6] + true_x[6];
   out_2883166859334089197[7] = -nom_x[7] + true_x[7];
   out_2883166859334089197[8] = -nom_x[8] + true_x[8];
   out_2883166859334089197[9] = -nom_x[9] + true_x[9];
   out_2883166859334089197[10] = -nom_x[10] + true_x[10];
   out_2883166859334089197[11] = -nom_x[11] + true_x[11];
   out_2883166859334089197[12] = -nom_x[12] + true_x[12];
   out_2883166859334089197[13] = -nom_x[13] + true_x[13];
   out_2883166859334089197[14] = -nom_x[14] + true_x[14];
   out_2883166859334089197[15] = -nom_x[15] + true_x[15];
   out_2883166859334089197[16] = -nom_x[16] + true_x[16];
   out_2883166859334089197[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_671491409411989589) {
   out_671491409411989589[0] = 1.0;
   out_671491409411989589[1] = 0.0;
   out_671491409411989589[2] = 0.0;
   out_671491409411989589[3] = 0.0;
   out_671491409411989589[4] = 0.0;
   out_671491409411989589[5] = 0.0;
   out_671491409411989589[6] = 0.0;
   out_671491409411989589[7] = 0.0;
   out_671491409411989589[8] = 0.0;
   out_671491409411989589[9] = 0.0;
   out_671491409411989589[10] = 0.0;
   out_671491409411989589[11] = 0.0;
   out_671491409411989589[12] = 0.0;
   out_671491409411989589[13] = 0.0;
   out_671491409411989589[14] = 0.0;
   out_671491409411989589[15] = 0.0;
   out_671491409411989589[16] = 0.0;
   out_671491409411989589[17] = 0.0;
   out_671491409411989589[18] = 0.0;
   out_671491409411989589[19] = 1.0;
   out_671491409411989589[20] = 0.0;
   out_671491409411989589[21] = 0.0;
   out_671491409411989589[22] = 0.0;
   out_671491409411989589[23] = 0.0;
   out_671491409411989589[24] = 0.0;
   out_671491409411989589[25] = 0.0;
   out_671491409411989589[26] = 0.0;
   out_671491409411989589[27] = 0.0;
   out_671491409411989589[28] = 0.0;
   out_671491409411989589[29] = 0.0;
   out_671491409411989589[30] = 0.0;
   out_671491409411989589[31] = 0.0;
   out_671491409411989589[32] = 0.0;
   out_671491409411989589[33] = 0.0;
   out_671491409411989589[34] = 0.0;
   out_671491409411989589[35] = 0.0;
   out_671491409411989589[36] = 0.0;
   out_671491409411989589[37] = 0.0;
   out_671491409411989589[38] = 1.0;
   out_671491409411989589[39] = 0.0;
   out_671491409411989589[40] = 0.0;
   out_671491409411989589[41] = 0.0;
   out_671491409411989589[42] = 0.0;
   out_671491409411989589[43] = 0.0;
   out_671491409411989589[44] = 0.0;
   out_671491409411989589[45] = 0.0;
   out_671491409411989589[46] = 0.0;
   out_671491409411989589[47] = 0.0;
   out_671491409411989589[48] = 0.0;
   out_671491409411989589[49] = 0.0;
   out_671491409411989589[50] = 0.0;
   out_671491409411989589[51] = 0.0;
   out_671491409411989589[52] = 0.0;
   out_671491409411989589[53] = 0.0;
   out_671491409411989589[54] = 0.0;
   out_671491409411989589[55] = 0.0;
   out_671491409411989589[56] = 0.0;
   out_671491409411989589[57] = 1.0;
   out_671491409411989589[58] = 0.0;
   out_671491409411989589[59] = 0.0;
   out_671491409411989589[60] = 0.0;
   out_671491409411989589[61] = 0.0;
   out_671491409411989589[62] = 0.0;
   out_671491409411989589[63] = 0.0;
   out_671491409411989589[64] = 0.0;
   out_671491409411989589[65] = 0.0;
   out_671491409411989589[66] = 0.0;
   out_671491409411989589[67] = 0.0;
   out_671491409411989589[68] = 0.0;
   out_671491409411989589[69] = 0.0;
   out_671491409411989589[70] = 0.0;
   out_671491409411989589[71] = 0.0;
   out_671491409411989589[72] = 0.0;
   out_671491409411989589[73] = 0.0;
   out_671491409411989589[74] = 0.0;
   out_671491409411989589[75] = 0.0;
   out_671491409411989589[76] = 1.0;
   out_671491409411989589[77] = 0.0;
   out_671491409411989589[78] = 0.0;
   out_671491409411989589[79] = 0.0;
   out_671491409411989589[80] = 0.0;
   out_671491409411989589[81] = 0.0;
   out_671491409411989589[82] = 0.0;
   out_671491409411989589[83] = 0.0;
   out_671491409411989589[84] = 0.0;
   out_671491409411989589[85] = 0.0;
   out_671491409411989589[86] = 0.0;
   out_671491409411989589[87] = 0.0;
   out_671491409411989589[88] = 0.0;
   out_671491409411989589[89] = 0.0;
   out_671491409411989589[90] = 0.0;
   out_671491409411989589[91] = 0.0;
   out_671491409411989589[92] = 0.0;
   out_671491409411989589[93] = 0.0;
   out_671491409411989589[94] = 0.0;
   out_671491409411989589[95] = 1.0;
   out_671491409411989589[96] = 0.0;
   out_671491409411989589[97] = 0.0;
   out_671491409411989589[98] = 0.0;
   out_671491409411989589[99] = 0.0;
   out_671491409411989589[100] = 0.0;
   out_671491409411989589[101] = 0.0;
   out_671491409411989589[102] = 0.0;
   out_671491409411989589[103] = 0.0;
   out_671491409411989589[104] = 0.0;
   out_671491409411989589[105] = 0.0;
   out_671491409411989589[106] = 0.0;
   out_671491409411989589[107] = 0.0;
   out_671491409411989589[108] = 0.0;
   out_671491409411989589[109] = 0.0;
   out_671491409411989589[110] = 0.0;
   out_671491409411989589[111] = 0.0;
   out_671491409411989589[112] = 0.0;
   out_671491409411989589[113] = 0.0;
   out_671491409411989589[114] = 1.0;
   out_671491409411989589[115] = 0.0;
   out_671491409411989589[116] = 0.0;
   out_671491409411989589[117] = 0.0;
   out_671491409411989589[118] = 0.0;
   out_671491409411989589[119] = 0.0;
   out_671491409411989589[120] = 0.0;
   out_671491409411989589[121] = 0.0;
   out_671491409411989589[122] = 0.0;
   out_671491409411989589[123] = 0.0;
   out_671491409411989589[124] = 0.0;
   out_671491409411989589[125] = 0.0;
   out_671491409411989589[126] = 0.0;
   out_671491409411989589[127] = 0.0;
   out_671491409411989589[128] = 0.0;
   out_671491409411989589[129] = 0.0;
   out_671491409411989589[130] = 0.0;
   out_671491409411989589[131] = 0.0;
   out_671491409411989589[132] = 0.0;
   out_671491409411989589[133] = 1.0;
   out_671491409411989589[134] = 0.0;
   out_671491409411989589[135] = 0.0;
   out_671491409411989589[136] = 0.0;
   out_671491409411989589[137] = 0.0;
   out_671491409411989589[138] = 0.0;
   out_671491409411989589[139] = 0.0;
   out_671491409411989589[140] = 0.0;
   out_671491409411989589[141] = 0.0;
   out_671491409411989589[142] = 0.0;
   out_671491409411989589[143] = 0.0;
   out_671491409411989589[144] = 0.0;
   out_671491409411989589[145] = 0.0;
   out_671491409411989589[146] = 0.0;
   out_671491409411989589[147] = 0.0;
   out_671491409411989589[148] = 0.0;
   out_671491409411989589[149] = 0.0;
   out_671491409411989589[150] = 0.0;
   out_671491409411989589[151] = 0.0;
   out_671491409411989589[152] = 1.0;
   out_671491409411989589[153] = 0.0;
   out_671491409411989589[154] = 0.0;
   out_671491409411989589[155] = 0.0;
   out_671491409411989589[156] = 0.0;
   out_671491409411989589[157] = 0.0;
   out_671491409411989589[158] = 0.0;
   out_671491409411989589[159] = 0.0;
   out_671491409411989589[160] = 0.0;
   out_671491409411989589[161] = 0.0;
   out_671491409411989589[162] = 0.0;
   out_671491409411989589[163] = 0.0;
   out_671491409411989589[164] = 0.0;
   out_671491409411989589[165] = 0.0;
   out_671491409411989589[166] = 0.0;
   out_671491409411989589[167] = 0.0;
   out_671491409411989589[168] = 0.0;
   out_671491409411989589[169] = 0.0;
   out_671491409411989589[170] = 0.0;
   out_671491409411989589[171] = 1.0;
   out_671491409411989589[172] = 0.0;
   out_671491409411989589[173] = 0.0;
   out_671491409411989589[174] = 0.0;
   out_671491409411989589[175] = 0.0;
   out_671491409411989589[176] = 0.0;
   out_671491409411989589[177] = 0.0;
   out_671491409411989589[178] = 0.0;
   out_671491409411989589[179] = 0.0;
   out_671491409411989589[180] = 0.0;
   out_671491409411989589[181] = 0.0;
   out_671491409411989589[182] = 0.0;
   out_671491409411989589[183] = 0.0;
   out_671491409411989589[184] = 0.0;
   out_671491409411989589[185] = 0.0;
   out_671491409411989589[186] = 0.0;
   out_671491409411989589[187] = 0.0;
   out_671491409411989589[188] = 0.0;
   out_671491409411989589[189] = 0.0;
   out_671491409411989589[190] = 1.0;
   out_671491409411989589[191] = 0.0;
   out_671491409411989589[192] = 0.0;
   out_671491409411989589[193] = 0.0;
   out_671491409411989589[194] = 0.0;
   out_671491409411989589[195] = 0.0;
   out_671491409411989589[196] = 0.0;
   out_671491409411989589[197] = 0.0;
   out_671491409411989589[198] = 0.0;
   out_671491409411989589[199] = 0.0;
   out_671491409411989589[200] = 0.0;
   out_671491409411989589[201] = 0.0;
   out_671491409411989589[202] = 0.0;
   out_671491409411989589[203] = 0.0;
   out_671491409411989589[204] = 0.0;
   out_671491409411989589[205] = 0.0;
   out_671491409411989589[206] = 0.0;
   out_671491409411989589[207] = 0.0;
   out_671491409411989589[208] = 0.0;
   out_671491409411989589[209] = 1.0;
   out_671491409411989589[210] = 0.0;
   out_671491409411989589[211] = 0.0;
   out_671491409411989589[212] = 0.0;
   out_671491409411989589[213] = 0.0;
   out_671491409411989589[214] = 0.0;
   out_671491409411989589[215] = 0.0;
   out_671491409411989589[216] = 0.0;
   out_671491409411989589[217] = 0.0;
   out_671491409411989589[218] = 0.0;
   out_671491409411989589[219] = 0.0;
   out_671491409411989589[220] = 0.0;
   out_671491409411989589[221] = 0.0;
   out_671491409411989589[222] = 0.0;
   out_671491409411989589[223] = 0.0;
   out_671491409411989589[224] = 0.0;
   out_671491409411989589[225] = 0.0;
   out_671491409411989589[226] = 0.0;
   out_671491409411989589[227] = 0.0;
   out_671491409411989589[228] = 1.0;
   out_671491409411989589[229] = 0.0;
   out_671491409411989589[230] = 0.0;
   out_671491409411989589[231] = 0.0;
   out_671491409411989589[232] = 0.0;
   out_671491409411989589[233] = 0.0;
   out_671491409411989589[234] = 0.0;
   out_671491409411989589[235] = 0.0;
   out_671491409411989589[236] = 0.0;
   out_671491409411989589[237] = 0.0;
   out_671491409411989589[238] = 0.0;
   out_671491409411989589[239] = 0.0;
   out_671491409411989589[240] = 0.0;
   out_671491409411989589[241] = 0.0;
   out_671491409411989589[242] = 0.0;
   out_671491409411989589[243] = 0.0;
   out_671491409411989589[244] = 0.0;
   out_671491409411989589[245] = 0.0;
   out_671491409411989589[246] = 0.0;
   out_671491409411989589[247] = 1.0;
   out_671491409411989589[248] = 0.0;
   out_671491409411989589[249] = 0.0;
   out_671491409411989589[250] = 0.0;
   out_671491409411989589[251] = 0.0;
   out_671491409411989589[252] = 0.0;
   out_671491409411989589[253] = 0.0;
   out_671491409411989589[254] = 0.0;
   out_671491409411989589[255] = 0.0;
   out_671491409411989589[256] = 0.0;
   out_671491409411989589[257] = 0.0;
   out_671491409411989589[258] = 0.0;
   out_671491409411989589[259] = 0.0;
   out_671491409411989589[260] = 0.0;
   out_671491409411989589[261] = 0.0;
   out_671491409411989589[262] = 0.0;
   out_671491409411989589[263] = 0.0;
   out_671491409411989589[264] = 0.0;
   out_671491409411989589[265] = 0.0;
   out_671491409411989589[266] = 1.0;
   out_671491409411989589[267] = 0.0;
   out_671491409411989589[268] = 0.0;
   out_671491409411989589[269] = 0.0;
   out_671491409411989589[270] = 0.0;
   out_671491409411989589[271] = 0.0;
   out_671491409411989589[272] = 0.0;
   out_671491409411989589[273] = 0.0;
   out_671491409411989589[274] = 0.0;
   out_671491409411989589[275] = 0.0;
   out_671491409411989589[276] = 0.0;
   out_671491409411989589[277] = 0.0;
   out_671491409411989589[278] = 0.0;
   out_671491409411989589[279] = 0.0;
   out_671491409411989589[280] = 0.0;
   out_671491409411989589[281] = 0.0;
   out_671491409411989589[282] = 0.0;
   out_671491409411989589[283] = 0.0;
   out_671491409411989589[284] = 0.0;
   out_671491409411989589[285] = 1.0;
   out_671491409411989589[286] = 0.0;
   out_671491409411989589[287] = 0.0;
   out_671491409411989589[288] = 0.0;
   out_671491409411989589[289] = 0.0;
   out_671491409411989589[290] = 0.0;
   out_671491409411989589[291] = 0.0;
   out_671491409411989589[292] = 0.0;
   out_671491409411989589[293] = 0.0;
   out_671491409411989589[294] = 0.0;
   out_671491409411989589[295] = 0.0;
   out_671491409411989589[296] = 0.0;
   out_671491409411989589[297] = 0.0;
   out_671491409411989589[298] = 0.0;
   out_671491409411989589[299] = 0.0;
   out_671491409411989589[300] = 0.0;
   out_671491409411989589[301] = 0.0;
   out_671491409411989589[302] = 0.0;
   out_671491409411989589[303] = 0.0;
   out_671491409411989589[304] = 1.0;
   out_671491409411989589[305] = 0.0;
   out_671491409411989589[306] = 0.0;
   out_671491409411989589[307] = 0.0;
   out_671491409411989589[308] = 0.0;
   out_671491409411989589[309] = 0.0;
   out_671491409411989589[310] = 0.0;
   out_671491409411989589[311] = 0.0;
   out_671491409411989589[312] = 0.0;
   out_671491409411989589[313] = 0.0;
   out_671491409411989589[314] = 0.0;
   out_671491409411989589[315] = 0.0;
   out_671491409411989589[316] = 0.0;
   out_671491409411989589[317] = 0.0;
   out_671491409411989589[318] = 0.0;
   out_671491409411989589[319] = 0.0;
   out_671491409411989589[320] = 0.0;
   out_671491409411989589[321] = 0.0;
   out_671491409411989589[322] = 0.0;
   out_671491409411989589[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_7919031781502386377) {
   out_7919031781502386377[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_7919031781502386377[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_7919031781502386377[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_7919031781502386377[3] = dt*state[12] + state[3];
   out_7919031781502386377[4] = dt*state[13] + state[4];
   out_7919031781502386377[5] = dt*state[14] + state[5];
   out_7919031781502386377[6] = state[6];
   out_7919031781502386377[7] = state[7];
   out_7919031781502386377[8] = state[8];
   out_7919031781502386377[9] = state[9];
   out_7919031781502386377[10] = state[10];
   out_7919031781502386377[11] = state[11];
   out_7919031781502386377[12] = state[12];
   out_7919031781502386377[13] = state[13];
   out_7919031781502386377[14] = state[14];
   out_7919031781502386377[15] = state[15];
   out_7919031781502386377[16] = state[16];
   out_7919031781502386377[17] = state[17];
}
void F_fun(double *state, double dt, double *out_7380360880106775220) {
   out_7380360880106775220[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7380360880106775220[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7380360880106775220[2] = 0;
   out_7380360880106775220[3] = 0;
   out_7380360880106775220[4] = 0;
   out_7380360880106775220[5] = 0;
   out_7380360880106775220[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7380360880106775220[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7380360880106775220[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_7380360880106775220[9] = 0;
   out_7380360880106775220[10] = 0;
   out_7380360880106775220[11] = 0;
   out_7380360880106775220[12] = 0;
   out_7380360880106775220[13] = 0;
   out_7380360880106775220[14] = 0;
   out_7380360880106775220[15] = 0;
   out_7380360880106775220[16] = 0;
   out_7380360880106775220[17] = 0;
   out_7380360880106775220[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7380360880106775220[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7380360880106775220[20] = 0;
   out_7380360880106775220[21] = 0;
   out_7380360880106775220[22] = 0;
   out_7380360880106775220[23] = 0;
   out_7380360880106775220[24] = 0;
   out_7380360880106775220[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7380360880106775220[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_7380360880106775220[27] = 0;
   out_7380360880106775220[28] = 0;
   out_7380360880106775220[29] = 0;
   out_7380360880106775220[30] = 0;
   out_7380360880106775220[31] = 0;
   out_7380360880106775220[32] = 0;
   out_7380360880106775220[33] = 0;
   out_7380360880106775220[34] = 0;
   out_7380360880106775220[35] = 0;
   out_7380360880106775220[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7380360880106775220[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7380360880106775220[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7380360880106775220[39] = 0;
   out_7380360880106775220[40] = 0;
   out_7380360880106775220[41] = 0;
   out_7380360880106775220[42] = 0;
   out_7380360880106775220[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7380360880106775220[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_7380360880106775220[45] = 0;
   out_7380360880106775220[46] = 0;
   out_7380360880106775220[47] = 0;
   out_7380360880106775220[48] = 0;
   out_7380360880106775220[49] = 0;
   out_7380360880106775220[50] = 0;
   out_7380360880106775220[51] = 0;
   out_7380360880106775220[52] = 0;
   out_7380360880106775220[53] = 0;
   out_7380360880106775220[54] = 0;
   out_7380360880106775220[55] = 0;
   out_7380360880106775220[56] = 0;
   out_7380360880106775220[57] = 1;
   out_7380360880106775220[58] = 0;
   out_7380360880106775220[59] = 0;
   out_7380360880106775220[60] = 0;
   out_7380360880106775220[61] = 0;
   out_7380360880106775220[62] = 0;
   out_7380360880106775220[63] = 0;
   out_7380360880106775220[64] = 0;
   out_7380360880106775220[65] = 0;
   out_7380360880106775220[66] = dt;
   out_7380360880106775220[67] = 0;
   out_7380360880106775220[68] = 0;
   out_7380360880106775220[69] = 0;
   out_7380360880106775220[70] = 0;
   out_7380360880106775220[71] = 0;
   out_7380360880106775220[72] = 0;
   out_7380360880106775220[73] = 0;
   out_7380360880106775220[74] = 0;
   out_7380360880106775220[75] = 0;
   out_7380360880106775220[76] = 1;
   out_7380360880106775220[77] = 0;
   out_7380360880106775220[78] = 0;
   out_7380360880106775220[79] = 0;
   out_7380360880106775220[80] = 0;
   out_7380360880106775220[81] = 0;
   out_7380360880106775220[82] = 0;
   out_7380360880106775220[83] = 0;
   out_7380360880106775220[84] = 0;
   out_7380360880106775220[85] = dt;
   out_7380360880106775220[86] = 0;
   out_7380360880106775220[87] = 0;
   out_7380360880106775220[88] = 0;
   out_7380360880106775220[89] = 0;
   out_7380360880106775220[90] = 0;
   out_7380360880106775220[91] = 0;
   out_7380360880106775220[92] = 0;
   out_7380360880106775220[93] = 0;
   out_7380360880106775220[94] = 0;
   out_7380360880106775220[95] = 1;
   out_7380360880106775220[96] = 0;
   out_7380360880106775220[97] = 0;
   out_7380360880106775220[98] = 0;
   out_7380360880106775220[99] = 0;
   out_7380360880106775220[100] = 0;
   out_7380360880106775220[101] = 0;
   out_7380360880106775220[102] = 0;
   out_7380360880106775220[103] = 0;
   out_7380360880106775220[104] = dt;
   out_7380360880106775220[105] = 0;
   out_7380360880106775220[106] = 0;
   out_7380360880106775220[107] = 0;
   out_7380360880106775220[108] = 0;
   out_7380360880106775220[109] = 0;
   out_7380360880106775220[110] = 0;
   out_7380360880106775220[111] = 0;
   out_7380360880106775220[112] = 0;
   out_7380360880106775220[113] = 0;
   out_7380360880106775220[114] = 1;
   out_7380360880106775220[115] = 0;
   out_7380360880106775220[116] = 0;
   out_7380360880106775220[117] = 0;
   out_7380360880106775220[118] = 0;
   out_7380360880106775220[119] = 0;
   out_7380360880106775220[120] = 0;
   out_7380360880106775220[121] = 0;
   out_7380360880106775220[122] = 0;
   out_7380360880106775220[123] = 0;
   out_7380360880106775220[124] = 0;
   out_7380360880106775220[125] = 0;
   out_7380360880106775220[126] = 0;
   out_7380360880106775220[127] = 0;
   out_7380360880106775220[128] = 0;
   out_7380360880106775220[129] = 0;
   out_7380360880106775220[130] = 0;
   out_7380360880106775220[131] = 0;
   out_7380360880106775220[132] = 0;
   out_7380360880106775220[133] = 1;
   out_7380360880106775220[134] = 0;
   out_7380360880106775220[135] = 0;
   out_7380360880106775220[136] = 0;
   out_7380360880106775220[137] = 0;
   out_7380360880106775220[138] = 0;
   out_7380360880106775220[139] = 0;
   out_7380360880106775220[140] = 0;
   out_7380360880106775220[141] = 0;
   out_7380360880106775220[142] = 0;
   out_7380360880106775220[143] = 0;
   out_7380360880106775220[144] = 0;
   out_7380360880106775220[145] = 0;
   out_7380360880106775220[146] = 0;
   out_7380360880106775220[147] = 0;
   out_7380360880106775220[148] = 0;
   out_7380360880106775220[149] = 0;
   out_7380360880106775220[150] = 0;
   out_7380360880106775220[151] = 0;
   out_7380360880106775220[152] = 1;
   out_7380360880106775220[153] = 0;
   out_7380360880106775220[154] = 0;
   out_7380360880106775220[155] = 0;
   out_7380360880106775220[156] = 0;
   out_7380360880106775220[157] = 0;
   out_7380360880106775220[158] = 0;
   out_7380360880106775220[159] = 0;
   out_7380360880106775220[160] = 0;
   out_7380360880106775220[161] = 0;
   out_7380360880106775220[162] = 0;
   out_7380360880106775220[163] = 0;
   out_7380360880106775220[164] = 0;
   out_7380360880106775220[165] = 0;
   out_7380360880106775220[166] = 0;
   out_7380360880106775220[167] = 0;
   out_7380360880106775220[168] = 0;
   out_7380360880106775220[169] = 0;
   out_7380360880106775220[170] = 0;
   out_7380360880106775220[171] = 1;
   out_7380360880106775220[172] = 0;
   out_7380360880106775220[173] = 0;
   out_7380360880106775220[174] = 0;
   out_7380360880106775220[175] = 0;
   out_7380360880106775220[176] = 0;
   out_7380360880106775220[177] = 0;
   out_7380360880106775220[178] = 0;
   out_7380360880106775220[179] = 0;
   out_7380360880106775220[180] = 0;
   out_7380360880106775220[181] = 0;
   out_7380360880106775220[182] = 0;
   out_7380360880106775220[183] = 0;
   out_7380360880106775220[184] = 0;
   out_7380360880106775220[185] = 0;
   out_7380360880106775220[186] = 0;
   out_7380360880106775220[187] = 0;
   out_7380360880106775220[188] = 0;
   out_7380360880106775220[189] = 0;
   out_7380360880106775220[190] = 1;
   out_7380360880106775220[191] = 0;
   out_7380360880106775220[192] = 0;
   out_7380360880106775220[193] = 0;
   out_7380360880106775220[194] = 0;
   out_7380360880106775220[195] = 0;
   out_7380360880106775220[196] = 0;
   out_7380360880106775220[197] = 0;
   out_7380360880106775220[198] = 0;
   out_7380360880106775220[199] = 0;
   out_7380360880106775220[200] = 0;
   out_7380360880106775220[201] = 0;
   out_7380360880106775220[202] = 0;
   out_7380360880106775220[203] = 0;
   out_7380360880106775220[204] = 0;
   out_7380360880106775220[205] = 0;
   out_7380360880106775220[206] = 0;
   out_7380360880106775220[207] = 0;
   out_7380360880106775220[208] = 0;
   out_7380360880106775220[209] = 1;
   out_7380360880106775220[210] = 0;
   out_7380360880106775220[211] = 0;
   out_7380360880106775220[212] = 0;
   out_7380360880106775220[213] = 0;
   out_7380360880106775220[214] = 0;
   out_7380360880106775220[215] = 0;
   out_7380360880106775220[216] = 0;
   out_7380360880106775220[217] = 0;
   out_7380360880106775220[218] = 0;
   out_7380360880106775220[219] = 0;
   out_7380360880106775220[220] = 0;
   out_7380360880106775220[221] = 0;
   out_7380360880106775220[222] = 0;
   out_7380360880106775220[223] = 0;
   out_7380360880106775220[224] = 0;
   out_7380360880106775220[225] = 0;
   out_7380360880106775220[226] = 0;
   out_7380360880106775220[227] = 0;
   out_7380360880106775220[228] = 1;
   out_7380360880106775220[229] = 0;
   out_7380360880106775220[230] = 0;
   out_7380360880106775220[231] = 0;
   out_7380360880106775220[232] = 0;
   out_7380360880106775220[233] = 0;
   out_7380360880106775220[234] = 0;
   out_7380360880106775220[235] = 0;
   out_7380360880106775220[236] = 0;
   out_7380360880106775220[237] = 0;
   out_7380360880106775220[238] = 0;
   out_7380360880106775220[239] = 0;
   out_7380360880106775220[240] = 0;
   out_7380360880106775220[241] = 0;
   out_7380360880106775220[242] = 0;
   out_7380360880106775220[243] = 0;
   out_7380360880106775220[244] = 0;
   out_7380360880106775220[245] = 0;
   out_7380360880106775220[246] = 0;
   out_7380360880106775220[247] = 1;
   out_7380360880106775220[248] = 0;
   out_7380360880106775220[249] = 0;
   out_7380360880106775220[250] = 0;
   out_7380360880106775220[251] = 0;
   out_7380360880106775220[252] = 0;
   out_7380360880106775220[253] = 0;
   out_7380360880106775220[254] = 0;
   out_7380360880106775220[255] = 0;
   out_7380360880106775220[256] = 0;
   out_7380360880106775220[257] = 0;
   out_7380360880106775220[258] = 0;
   out_7380360880106775220[259] = 0;
   out_7380360880106775220[260] = 0;
   out_7380360880106775220[261] = 0;
   out_7380360880106775220[262] = 0;
   out_7380360880106775220[263] = 0;
   out_7380360880106775220[264] = 0;
   out_7380360880106775220[265] = 0;
   out_7380360880106775220[266] = 1;
   out_7380360880106775220[267] = 0;
   out_7380360880106775220[268] = 0;
   out_7380360880106775220[269] = 0;
   out_7380360880106775220[270] = 0;
   out_7380360880106775220[271] = 0;
   out_7380360880106775220[272] = 0;
   out_7380360880106775220[273] = 0;
   out_7380360880106775220[274] = 0;
   out_7380360880106775220[275] = 0;
   out_7380360880106775220[276] = 0;
   out_7380360880106775220[277] = 0;
   out_7380360880106775220[278] = 0;
   out_7380360880106775220[279] = 0;
   out_7380360880106775220[280] = 0;
   out_7380360880106775220[281] = 0;
   out_7380360880106775220[282] = 0;
   out_7380360880106775220[283] = 0;
   out_7380360880106775220[284] = 0;
   out_7380360880106775220[285] = 1;
   out_7380360880106775220[286] = 0;
   out_7380360880106775220[287] = 0;
   out_7380360880106775220[288] = 0;
   out_7380360880106775220[289] = 0;
   out_7380360880106775220[290] = 0;
   out_7380360880106775220[291] = 0;
   out_7380360880106775220[292] = 0;
   out_7380360880106775220[293] = 0;
   out_7380360880106775220[294] = 0;
   out_7380360880106775220[295] = 0;
   out_7380360880106775220[296] = 0;
   out_7380360880106775220[297] = 0;
   out_7380360880106775220[298] = 0;
   out_7380360880106775220[299] = 0;
   out_7380360880106775220[300] = 0;
   out_7380360880106775220[301] = 0;
   out_7380360880106775220[302] = 0;
   out_7380360880106775220[303] = 0;
   out_7380360880106775220[304] = 1;
   out_7380360880106775220[305] = 0;
   out_7380360880106775220[306] = 0;
   out_7380360880106775220[307] = 0;
   out_7380360880106775220[308] = 0;
   out_7380360880106775220[309] = 0;
   out_7380360880106775220[310] = 0;
   out_7380360880106775220[311] = 0;
   out_7380360880106775220[312] = 0;
   out_7380360880106775220[313] = 0;
   out_7380360880106775220[314] = 0;
   out_7380360880106775220[315] = 0;
   out_7380360880106775220[316] = 0;
   out_7380360880106775220[317] = 0;
   out_7380360880106775220[318] = 0;
   out_7380360880106775220[319] = 0;
   out_7380360880106775220[320] = 0;
   out_7380360880106775220[321] = 0;
   out_7380360880106775220[322] = 0;
   out_7380360880106775220[323] = 1;
}
void h_4(double *state, double *unused, double *out_4702057929225754412) {
   out_4702057929225754412[0] = state[6] + state[9];
   out_4702057929225754412[1] = state[7] + state[10];
   out_4702057929225754412[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3100315800431917983) {
   out_3100315800431917983[0] = 0;
   out_3100315800431917983[1] = 0;
   out_3100315800431917983[2] = 0;
   out_3100315800431917983[3] = 0;
   out_3100315800431917983[4] = 0;
   out_3100315800431917983[5] = 0;
   out_3100315800431917983[6] = 1;
   out_3100315800431917983[7] = 0;
   out_3100315800431917983[8] = 0;
   out_3100315800431917983[9] = 1;
   out_3100315800431917983[10] = 0;
   out_3100315800431917983[11] = 0;
   out_3100315800431917983[12] = 0;
   out_3100315800431917983[13] = 0;
   out_3100315800431917983[14] = 0;
   out_3100315800431917983[15] = 0;
   out_3100315800431917983[16] = 0;
   out_3100315800431917983[17] = 0;
   out_3100315800431917983[18] = 0;
   out_3100315800431917983[19] = 0;
   out_3100315800431917983[20] = 0;
   out_3100315800431917983[21] = 0;
   out_3100315800431917983[22] = 0;
   out_3100315800431917983[23] = 0;
   out_3100315800431917983[24] = 0;
   out_3100315800431917983[25] = 1;
   out_3100315800431917983[26] = 0;
   out_3100315800431917983[27] = 0;
   out_3100315800431917983[28] = 1;
   out_3100315800431917983[29] = 0;
   out_3100315800431917983[30] = 0;
   out_3100315800431917983[31] = 0;
   out_3100315800431917983[32] = 0;
   out_3100315800431917983[33] = 0;
   out_3100315800431917983[34] = 0;
   out_3100315800431917983[35] = 0;
   out_3100315800431917983[36] = 0;
   out_3100315800431917983[37] = 0;
   out_3100315800431917983[38] = 0;
   out_3100315800431917983[39] = 0;
   out_3100315800431917983[40] = 0;
   out_3100315800431917983[41] = 0;
   out_3100315800431917983[42] = 0;
   out_3100315800431917983[43] = 0;
   out_3100315800431917983[44] = 1;
   out_3100315800431917983[45] = 0;
   out_3100315800431917983[46] = 0;
   out_3100315800431917983[47] = 1;
   out_3100315800431917983[48] = 0;
   out_3100315800431917983[49] = 0;
   out_3100315800431917983[50] = 0;
   out_3100315800431917983[51] = 0;
   out_3100315800431917983[52] = 0;
   out_3100315800431917983[53] = 0;
}
void h_10(double *state, double *unused, double *out_1901997026290432130) {
   out_1901997026290432130[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1901997026290432130[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1901997026290432130[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5200655737232907775) {
   out_5200655737232907775[0] = 0;
   out_5200655737232907775[1] = 9.8100000000000005*cos(state[1]);
   out_5200655737232907775[2] = 0;
   out_5200655737232907775[3] = 0;
   out_5200655737232907775[4] = -state[8];
   out_5200655737232907775[5] = state[7];
   out_5200655737232907775[6] = 0;
   out_5200655737232907775[7] = state[5];
   out_5200655737232907775[8] = -state[4];
   out_5200655737232907775[9] = 0;
   out_5200655737232907775[10] = 0;
   out_5200655737232907775[11] = 0;
   out_5200655737232907775[12] = 1;
   out_5200655737232907775[13] = 0;
   out_5200655737232907775[14] = 0;
   out_5200655737232907775[15] = 1;
   out_5200655737232907775[16] = 0;
   out_5200655737232907775[17] = 0;
   out_5200655737232907775[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5200655737232907775[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5200655737232907775[20] = 0;
   out_5200655737232907775[21] = state[8];
   out_5200655737232907775[22] = 0;
   out_5200655737232907775[23] = -state[6];
   out_5200655737232907775[24] = -state[5];
   out_5200655737232907775[25] = 0;
   out_5200655737232907775[26] = state[3];
   out_5200655737232907775[27] = 0;
   out_5200655737232907775[28] = 0;
   out_5200655737232907775[29] = 0;
   out_5200655737232907775[30] = 0;
   out_5200655737232907775[31] = 1;
   out_5200655737232907775[32] = 0;
   out_5200655737232907775[33] = 0;
   out_5200655737232907775[34] = 1;
   out_5200655737232907775[35] = 0;
   out_5200655737232907775[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5200655737232907775[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5200655737232907775[38] = 0;
   out_5200655737232907775[39] = -state[7];
   out_5200655737232907775[40] = state[6];
   out_5200655737232907775[41] = 0;
   out_5200655737232907775[42] = state[4];
   out_5200655737232907775[43] = -state[3];
   out_5200655737232907775[44] = 0;
   out_5200655737232907775[45] = 0;
   out_5200655737232907775[46] = 0;
   out_5200655737232907775[47] = 0;
   out_5200655737232907775[48] = 0;
   out_5200655737232907775[49] = 0;
   out_5200655737232907775[50] = 1;
   out_5200655737232907775[51] = 0;
   out_5200655737232907775[52] = 0;
   out_5200655737232907775[53] = 1;
}
void h_13(double *state, double *unused, double *out_6749072148499604094) {
   out_6749072148499604094[0] = state[3];
   out_6749072148499604094[1] = state[4];
   out_6749072148499604094[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6312589625764250784) {
   out_6312589625764250784[0] = 0;
   out_6312589625764250784[1] = 0;
   out_6312589625764250784[2] = 0;
   out_6312589625764250784[3] = 1;
   out_6312589625764250784[4] = 0;
   out_6312589625764250784[5] = 0;
   out_6312589625764250784[6] = 0;
   out_6312589625764250784[7] = 0;
   out_6312589625764250784[8] = 0;
   out_6312589625764250784[9] = 0;
   out_6312589625764250784[10] = 0;
   out_6312589625764250784[11] = 0;
   out_6312589625764250784[12] = 0;
   out_6312589625764250784[13] = 0;
   out_6312589625764250784[14] = 0;
   out_6312589625764250784[15] = 0;
   out_6312589625764250784[16] = 0;
   out_6312589625764250784[17] = 0;
   out_6312589625764250784[18] = 0;
   out_6312589625764250784[19] = 0;
   out_6312589625764250784[20] = 0;
   out_6312589625764250784[21] = 0;
   out_6312589625764250784[22] = 1;
   out_6312589625764250784[23] = 0;
   out_6312589625764250784[24] = 0;
   out_6312589625764250784[25] = 0;
   out_6312589625764250784[26] = 0;
   out_6312589625764250784[27] = 0;
   out_6312589625764250784[28] = 0;
   out_6312589625764250784[29] = 0;
   out_6312589625764250784[30] = 0;
   out_6312589625764250784[31] = 0;
   out_6312589625764250784[32] = 0;
   out_6312589625764250784[33] = 0;
   out_6312589625764250784[34] = 0;
   out_6312589625764250784[35] = 0;
   out_6312589625764250784[36] = 0;
   out_6312589625764250784[37] = 0;
   out_6312589625764250784[38] = 0;
   out_6312589625764250784[39] = 0;
   out_6312589625764250784[40] = 0;
   out_6312589625764250784[41] = 1;
   out_6312589625764250784[42] = 0;
   out_6312589625764250784[43] = 0;
   out_6312589625764250784[44] = 0;
   out_6312589625764250784[45] = 0;
   out_6312589625764250784[46] = 0;
   out_6312589625764250784[47] = 0;
   out_6312589625764250784[48] = 0;
   out_6312589625764250784[49] = 0;
   out_6312589625764250784[50] = 0;
   out_6312589625764250784[51] = 0;
   out_6312589625764250784[52] = 0;
   out_6312589625764250784[53] = 0;
}
void h_14(double *state, double *unused, double *out_7677380843386584152) {
   out_7677380843386584152[0] = state[6];
   out_7677380843386584152[1] = state[7];
   out_7677380843386584152[2] = state[8];
}
void H_14(double *state, double *unused, double *out_17527368136545687) {
   out_17527368136545687[0] = 0;
   out_17527368136545687[1] = 0;
   out_17527368136545687[2] = 0;
   out_17527368136545687[3] = 0;
   out_17527368136545687[4] = 0;
   out_17527368136545687[5] = 0;
   out_17527368136545687[6] = 1;
   out_17527368136545687[7] = 0;
   out_17527368136545687[8] = 0;
   out_17527368136545687[9] = 0;
   out_17527368136545687[10] = 0;
   out_17527368136545687[11] = 0;
   out_17527368136545687[12] = 0;
   out_17527368136545687[13] = 0;
   out_17527368136545687[14] = 0;
   out_17527368136545687[15] = 0;
   out_17527368136545687[16] = 0;
   out_17527368136545687[17] = 0;
   out_17527368136545687[18] = 0;
   out_17527368136545687[19] = 0;
   out_17527368136545687[20] = 0;
   out_17527368136545687[21] = 0;
   out_17527368136545687[22] = 0;
   out_17527368136545687[23] = 0;
   out_17527368136545687[24] = 0;
   out_17527368136545687[25] = 1;
   out_17527368136545687[26] = 0;
   out_17527368136545687[27] = 0;
   out_17527368136545687[28] = 0;
   out_17527368136545687[29] = 0;
   out_17527368136545687[30] = 0;
   out_17527368136545687[31] = 0;
   out_17527368136545687[32] = 0;
   out_17527368136545687[33] = 0;
   out_17527368136545687[34] = 0;
   out_17527368136545687[35] = 0;
   out_17527368136545687[36] = 0;
   out_17527368136545687[37] = 0;
   out_17527368136545687[38] = 0;
   out_17527368136545687[39] = 0;
   out_17527368136545687[40] = 0;
   out_17527368136545687[41] = 0;
   out_17527368136545687[42] = 0;
   out_17527368136545687[43] = 0;
   out_17527368136545687[44] = 1;
   out_17527368136545687[45] = 0;
   out_17527368136545687[46] = 0;
   out_17527368136545687[47] = 0;
   out_17527368136545687[48] = 0;
   out_17527368136545687[49] = 0;
   out_17527368136545687[50] = 0;
   out_17527368136545687[51] = 0;
   out_17527368136545687[52] = 0;
   out_17527368136545687[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_2182435369834896236) {
  err_fun(nom_x, delta_x, out_2182435369834896236);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2883166859334089197) {
  inv_err_fun(nom_x, true_x, out_2883166859334089197);
}
void pose_H_mod_fun(double *state, double *out_671491409411989589) {
  H_mod_fun(state, out_671491409411989589);
}
void pose_f_fun(double *state, double dt, double *out_7919031781502386377) {
  f_fun(state,  dt, out_7919031781502386377);
}
void pose_F_fun(double *state, double dt, double *out_7380360880106775220) {
  F_fun(state,  dt, out_7380360880106775220);
}
void pose_h_4(double *state, double *unused, double *out_4702057929225754412) {
  h_4(state, unused, out_4702057929225754412);
}
void pose_H_4(double *state, double *unused, double *out_3100315800431917983) {
  H_4(state, unused, out_3100315800431917983);
}
void pose_h_10(double *state, double *unused, double *out_1901997026290432130) {
  h_10(state, unused, out_1901997026290432130);
}
void pose_H_10(double *state, double *unused, double *out_5200655737232907775) {
  H_10(state, unused, out_5200655737232907775);
}
void pose_h_13(double *state, double *unused, double *out_6749072148499604094) {
  h_13(state, unused, out_6749072148499604094);
}
void pose_H_13(double *state, double *unused, double *out_6312589625764250784) {
  H_13(state, unused, out_6312589625764250784);
}
void pose_h_14(double *state, double *unused, double *out_7677380843386584152) {
  h_14(state, unused, out_7677380843386584152);
}
void pose_H_14(double *state, double *unused, double *out_17527368136545687) {
  H_14(state, unused, out_17527368136545687);
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
