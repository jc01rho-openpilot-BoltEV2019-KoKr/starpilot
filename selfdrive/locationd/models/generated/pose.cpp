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
void err_fun(double *nom_x, double *delta_x, double *out_3650099251769799718) {
   out_3650099251769799718[0] = delta_x[0] + nom_x[0];
   out_3650099251769799718[1] = delta_x[1] + nom_x[1];
   out_3650099251769799718[2] = delta_x[2] + nom_x[2];
   out_3650099251769799718[3] = delta_x[3] + nom_x[3];
   out_3650099251769799718[4] = delta_x[4] + nom_x[4];
   out_3650099251769799718[5] = delta_x[5] + nom_x[5];
   out_3650099251769799718[6] = delta_x[6] + nom_x[6];
   out_3650099251769799718[7] = delta_x[7] + nom_x[7];
   out_3650099251769799718[8] = delta_x[8] + nom_x[8];
   out_3650099251769799718[9] = delta_x[9] + nom_x[9];
   out_3650099251769799718[10] = delta_x[10] + nom_x[10];
   out_3650099251769799718[11] = delta_x[11] + nom_x[11];
   out_3650099251769799718[12] = delta_x[12] + nom_x[12];
   out_3650099251769799718[13] = delta_x[13] + nom_x[13];
   out_3650099251769799718[14] = delta_x[14] + nom_x[14];
   out_3650099251769799718[15] = delta_x[15] + nom_x[15];
   out_3650099251769799718[16] = delta_x[16] + nom_x[16];
   out_3650099251769799718[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4549899801136771746) {
   out_4549899801136771746[0] = -nom_x[0] + true_x[0];
   out_4549899801136771746[1] = -nom_x[1] + true_x[1];
   out_4549899801136771746[2] = -nom_x[2] + true_x[2];
   out_4549899801136771746[3] = -nom_x[3] + true_x[3];
   out_4549899801136771746[4] = -nom_x[4] + true_x[4];
   out_4549899801136771746[5] = -nom_x[5] + true_x[5];
   out_4549899801136771746[6] = -nom_x[6] + true_x[6];
   out_4549899801136771746[7] = -nom_x[7] + true_x[7];
   out_4549899801136771746[8] = -nom_x[8] + true_x[8];
   out_4549899801136771746[9] = -nom_x[9] + true_x[9];
   out_4549899801136771746[10] = -nom_x[10] + true_x[10];
   out_4549899801136771746[11] = -nom_x[11] + true_x[11];
   out_4549899801136771746[12] = -nom_x[12] + true_x[12];
   out_4549899801136771746[13] = -nom_x[13] + true_x[13];
   out_4549899801136771746[14] = -nom_x[14] + true_x[14];
   out_4549899801136771746[15] = -nom_x[15] + true_x[15];
   out_4549899801136771746[16] = -nom_x[16] + true_x[16];
   out_4549899801136771746[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_6815214623410224821) {
   out_6815214623410224821[0] = 1.0;
   out_6815214623410224821[1] = 0.0;
   out_6815214623410224821[2] = 0.0;
   out_6815214623410224821[3] = 0.0;
   out_6815214623410224821[4] = 0.0;
   out_6815214623410224821[5] = 0.0;
   out_6815214623410224821[6] = 0.0;
   out_6815214623410224821[7] = 0.0;
   out_6815214623410224821[8] = 0.0;
   out_6815214623410224821[9] = 0.0;
   out_6815214623410224821[10] = 0.0;
   out_6815214623410224821[11] = 0.0;
   out_6815214623410224821[12] = 0.0;
   out_6815214623410224821[13] = 0.0;
   out_6815214623410224821[14] = 0.0;
   out_6815214623410224821[15] = 0.0;
   out_6815214623410224821[16] = 0.0;
   out_6815214623410224821[17] = 0.0;
   out_6815214623410224821[18] = 0.0;
   out_6815214623410224821[19] = 1.0;
   out_6815214623410224821[20] = 0.0;
   out_6815214623410224821[21] = 0.0;
   out_6815214623410224821[22] = 0.0;
   out_6815214623410224821[23] = 0.0;
   out_6815214623410224821[24] = 0.0;
   out_6815214623410224821[25] = 0.0;
   out_6815214623410224821[26] = 0.0;
   out_6815214623410224821[27] = 0.0;
   out_6815214623410224821[28] = 0.0;
   out_6815214623410224821[29] = 0.0;
   out_6815214623410224821[30] = 0.0;
   out_6815214623410224821[31] = 0.0;
   out_6815214623410224821[32] = 0.0;
   out_6815214623410224821[33] = 0.0;
   out_6815214623410224821[34] = 0.0;
   out_6815214623410224821[35] = 0.0;
   out_6815214623410224821[36] = 0.0;
   out_6815214623410224821[37] = 0.0;
   out_6815214623410224821[38] = 1.0;
   out_6815214623410224821[39] = 0.0;
   out_6815214623410224821[40] = 0.0;
   out_6815214623410224821[41] = 0.0;
   out_6815214623410224821[42] = 0.0;
   out_6815214623410224821[43] = 0.0;
   out_6815214623410224821[44] = 0.0;
   out_6815214623410224821[45] = 0.0;
   out_6815214623410224821[46] = 0.0;
   out_6815214623410224821[47] = 0.0;
   out_6815214623410224821[48] = 0.0;
   out_6815214623410224821[49] = 0.0;
   out_6815214623410224821[50] = 0.0;
   out_6815214623410224821[51] = 0.0;
   out_6815214623410224821[52] = 0.0;
   out_6815214623410224821[53] = 0.0;
   out_6815214623410224821[54] = 0.0;
   out_6815214623410224821[55] = 0.0;
   out_6815214623410224821[56] = 0.0;
   out_6815214623410224821[57] = 1.0;
   out_6815214623410224821[58] = 0.0;
   out_6815214623410224821[59] = 0.0;
   out_6815214623410224821[60] = 0.0;
   out_6815214623410224821[61] = 0.0;
   out_6815214623410224821[62] = 0.0;
   out_6815214623410224821[63] = 0.0;
   out_6815214623410224821[64] = 0.0;
   out_6815214623410224821[65] = 0.0;
   out_6815214623410224821[66] = 0.0;
   out_6815214623410224821[67] = 0.0;
   out_6815214623410224821[68] = 0.0;
   out_6815214623410224821[69] = 0.0;
   out_6815214623410224821[70] = 0.0;
   out_6815214623410224821[71] = 0.0;
   out_6815214623410224821[72] = 0.0;
   out_6815214623410224821[73] = 0.0;
   out_6815214623410224821[74] = 0.0;
   out_6815214623410224821[75] = 0.0;
   out_6815214623410224821[76] = 1.0;
   out_6815214623410224821[77] = 0.0;
   out_6815214623410224821[78] = 0.0;
   out_6815214623410224821[79] = 0.0;
   out_6815214623410224821[80] = 0.0;
   out_6815214623410224821[81] = 0.0;
   out_6815214623410224821[82] = 0.0;
   out_6815214623410224821[83] = 0.0;
   out_6815214623410224821[84] = 0.0;
   out_6815214623410224821[85] = 0.0;
   out_6815214623410224821[86] = 0.0;
   out_6815214623410224821[87] = 0.0;
   out_6815214623410224821[88] = 0.0;
   out_6815214623410224821[89] = 0.0;
   out_6815214623410224821[90] = 0.0;
   out_6815214623410224821[91] = 0.0;
   out_6815214623410224821[92] = 0.0;
   out_6815214623410224821[93] = 0.0;
   out_6815214623410224821[94] = 0.0;
   out_6815214623410224821[95] = 1.0;
   out_6815214623410224821[96] = 0.0;
   out_6815214623410224821[97] = 0.0;
   out_6815214623410224821[98] = 0.0;
   out_6815214623410224821[99] = 0.0;
   out_6815214623410224821[100] = 0.0;
   out_6815214623410224821[101] = 0.0;
   out_6815214623410224821[102] = 0.0;
   out_6815214623410224821[103] = 0.0;
   out_6815214623410224821[104] = 0.0;
   out_6815214623410224821[105] = 0.0;
   out_6815214623410224821[106] = 0.0;
   out_6815214623410224821[107] = 0.0;
   out_6815214623410224821[108] = 0.0;
   out_6815214623410224821[109] = 0.0;
   out_6815214623410224821[110] = 0.0;
   out_6815214623410224821[111] = 0.0;
   out_6815214623410224821[112] = 0.0;
   out_6815214623410224821[113] = 0.0;
   out_6815214623410224821[114] = 1.0;
   out_6815214623410224821[115] = 0.0;
   out_6815214623410224821[116] = 0.0;
   out_6815214623410224821[117] = 0.0;
   out_6815214623410224821[118] = 0.0;
   out_6815214623410224821[119] = 0.0;
   out_6815214623410224821[120] = 0.0;
   out_6815214623410224821[121] = 0.0;
   out_6815214623410224821[122] = 0.0;
   out_6815214623410224821[123] = 0.0;
   out_6815214623410224821[124] = 0.0;
   out_6815214623410224821[125] = 0.0;
   out_6815214623410224821[126] = 0.0;
   out_6815214623410224821[127] = 0.0;
   out_6815214623410224821[128] = 0.0;
   out_6815214623410224821[129] = 0.0;
   out_6815214623410224821[130] = 0.0;
   out_6815214623410224821[131] = 0.0;
   out_6815214623410224821[132] = 0.0;
   out_6815214623410224821[133] = 1.0;
   out_6815214623410224821[134] = 0.0;
   out_6815214623410224821[135] = 0.0;
   out_6815214623410224821[136] = 0.0;
   out_6815214623410224821[137] = 0.0;
   out_6815214623410224821[138] = 0.0;
   out_6815214623410224821[139] = 0.0;
   out_6815214623410224821[140] = 0.0;
   out_6815214623410224821[141] = 0.0;
   out_6815214623410224821[142] = 0.0;
   out_6815214623410224821[143] = 0.0;
   out_6815214623410224821[144] = 0.0;
   out_6815214623410224821[145] = 0.0;
   out_6815214623410224821[146] = 0.0;
   out_6815214623410224821[147] = 0.0;
   out_6815214623410224821[148] = 0.0;
   out_6815214623410224821[149] = 0.0;
   out_6815214623410224821[150] = 0.0;
   out_6815214623410224821[151] = 0.0;
   out_6815214623410224821[152] = 1.0;
   out_6815214623410224821[153] = 0.0;
   out_6815214623410224821[154] = 0.0;
   out_6815214623410224821[155] = 0.0;
   out_6815214623410224821[156] = 0.0;
   out_6815214623410224821[157] = 0.0;
   out_6815214623410224821[158] = 0.0;
   out_6815214623410224821[159] = 0.0;
   out_6815214623410224821[160] = 0.0;
   out_6815214623410224821[161] = 0.0;
   out_6815214623410224821[162] = 0.0;
   out_6815214623410224821[163] = 0.0;
   out_6815214623410224821[164] = 0.0;
   out_6815214623410224821[165] = 0.0;
   out_6815214623410224821[166] = 0.0;
   out_6815214623410224821[167] = 0.0;
   out_6815214623410224821[168] = 0.0;
   out_6815214623410224821[169] = 0.0;
   out_6815214623410224821[170] = 0.0;
   out_6815214623410224821[171] = 1.0;
   out_6815214623410224821[172] = 0.0;
   out_6815214623410224821[173] = 0.0;
   out_6815214623410224821[174] = 0.0;
   out_6815214623410224821[175] = 0.0;
   out_6815214623410224821[176] = 0.0;
   out_6815214623410224821[177] = 0.0;
   out_6815214623410224821[178] = 0.0;
   out_6815214623410224821[179] = 0.0;
   out_6815214623410224821[180] = 0.0;
   out_6815214623410224821[181] = 0.0;
   out_6815214623410224821[182] = 0.0;
   out_6815214623410224821[183] = 0.0;
   out_6815214623410224821[184] = 0.0;
   out_6815214623410224821[185] = 0.0;
   out_6815214623410224821[186] = 0.0;
   out_6815214623410224821[187] = 0.0;
   out_6815214623410224821[188] = 0.0;
   out_6815214623410224821[189] = 0.0;
   out_6815214623410224821[190] = 1.0;
   out_6815214623410224821[191] = 0.0;
   out_6815214623410224821[192] = 0.0;
   out_6815214623410224821[193] = 0.0;
   out_6815214623410224821[194] = 0.0;
   out_6815214623410224821[195] = 0.0;
   out_6815214623410224821[196] = 0.0;
   out_6815214623410224821[197] = 0.0;
   out_6815214623410224821[198] = 0.0;
   out_6815214623410224821[199] = 0.0;
   out_6815214623410224821[200] = 0.0;
   out_6815214623410224821[201] = 0.0;
   out_6815214623410224821[202] = 0.0;
   out_6815214623410224821[203] = 0.0;
   out_6815214623410224821[204] = 0.0;
   out_6815214623410224821[205] = 0.0;
   out_6815214623410224821[206] = 0.0;
   out_6815214623410224821[207] = 0.0;
   out_6815214623410224821[208] = 0.0;
   out_6815214623410224821[209] = 1.0;
   out_6815214623410224821[210] = 0.0;
   out_6815214623410224821[211] = 0.0;
   out_6815214623410224821[212] = 0.0;
   out_6815214623410224821[213] = 0.0;
   out_6815214623410224821[214] = 0.0;
   out_6815214623410224821[215] = 0.0;
   out_6815214623410224821[216] = 0.0;
   out_6815214623410224821[217] = 0.0;
   out_6815214623410224821[218] = 0.0;
   out_6815214623410224821[219] = 0.0;
   out_6815214623410224821[220] = 0.0;
   out_6815214623410224821[221] = 0.0;
   out_6815214623410224821[222] = 0.0;
   out_6815214623410224821[223] = 0.0;
   out_6815214623410224821[224] = 0.0;
   out_6815214623410224821[225] = 0.0;
   out_6815214623410224821[226] = 0.0;
   out_6815214623410224821[227] = 0.0;
   out_6815214623410224821[228] = 1.0;
   out_6815214623410224821[229] = 0.0;
   out_6815214623410224821[230] = 0.0;
   out_6815214623410224821[231] = 0.0;
   out_6815214623410224821[232] = 0.0;
   out_6815214623410224821[233] = 0.0;
   out_6815214623410224821[234] = 0.0;
   out_6815214623410224821[235] = 0.0;
   out_6815214623410224821[236] = 0.0;
   out_6815214623410224821[237] = 0.0;
   out_6815214623410224821[238] = 0.0;
   out_6815214623410224821[239] = 0.0;
   out_6815214623410224821[240] = 0.0;
   out_6815214623410224821[241] = 0.0;
   out_6815214623410224821[242] = 0.0;
   out_6815214623410224821[243] = 0.0;
   out_6815214623410224821[244] = 0.0;
   out_6815214623410224821[245] = 0.0;
   out_6815214623410224821[246] = 0.0;
   out_6815214623410224821[247] = 1.0;
   out_6815214623410224821[248] = 0.0;
   out_6815214623410224821[249] = 0.0;
   out_6815214623410224821[250] = 0.0;
   out_6815214623410224821[251] = 0.0;
   out_6815214623410224821[252] = 0.0;
   out_6815214623410224821[253] = 0.0;
   out_6815214623410224821[254] = 0.0;
   out_6815214623410224821[255] = 0.0;
   out_6815214623410224821[256] = 0.0;
   out_6815214623410224821[257] = 0.0;
   out_6815214623410224821[258] = 0.0;
   out_6815214623410224821[259] = 0.0;
   out_6815214623410224821[260] = 0.0;
   out_6815214623410224821[261] = 0.0;
   out_6815214623410224821[262] = 0.0;
   out_6815214623410224821[263] = 0.0;
   out_6815214623410224821[264] = 0.0;
   out_6815214623410224821[265] = 0.0;
   out_6815214623410224821[266] = 1.0;
   out_6815214623410224821[267] = 0.0;
   out_6815214623410224821[268] = 0.0;
   out_6815214623410224821[269] = 0.0;
   out_6815214623410224821[270] = 0.0;
   out_6815214623410224821[271] = 0.0;
   out_6815214623410224821[272] = 0.0;
   out_6815214623410224821[273] = 0.0;
   out_6815214623410224821[274] = 0.0;
   out_6815214623410224821[275] = 0.0;
   out_6815214623410224821[276] = 0.0;
   out_6815214623410224821[277] = 0.0;
   out_6815214623410224821[278] = 0.0;
   out_6815214623410224821[279] = 0.0;
   out_6815214623410224821[280] = 0.0;
   out_6815214623410224821[281] = 0.0;
   out_6815214623410224821[282] = 0.0;
   out_6815214623410224821[283] = 0.0;
   out_6815214623410224821[284] = 0.0;
   out_6815214623410224821[285] = 1.0;
   out_6815214623410224821[286] = 0.0;
   out_6815214623410224821[287] = 0.0;
   out_6815214623410224821[288] = 0.0;
   out_6815214623410224821[289] = 0.0;
   out_6815214623410224821[290] = 0.0;
   out_6815214623410224821[291] = 0.0;
   out_6815214623410224821[292] = 0.0;
   out_6815214623410224821[293] = 0.0;
   out_6815214623410224821[294] = 0.0;
   out_6815214623410224821[295] = 0.0;
   out_6815214623410224821[296] = 0.0;
   out_6815214623410224821[297] = 0.0;
   out_6815214623410224821[298] = 0.0;
   out_6815214623410224821[299] = 0.0;
   out_6815214623410224821[300] = 0.0;
   out_6815214623410224821[301] = 0.0;
   out_6815214623410224821[302] = 0.0;
   out_6815214623410224821[303] = 0.0;
   out_6815214623410224821[304] = 1.0;
   out_6815214623410224821[305] = 0.0;
   out_6815214623410224821[306] = 0.0;
   out_6815214623410224821[307] = 0.0;
   out_6815214623410224821[308] = 0.0;
   out_6815214623410224821[309] = 0.0;
   out_6815214623410224821[310] = 0.0;
   out_6815214623410224821[311] = 0.0;
   out_6815214623410224821[312] = 0.0;
   out_6815214623410224821[313] = 0.0;
   out_6815214623410224821[314] = 0.0;
   out_6815214623410224821[315] = 0.0;
   out_6815214623410224821[316] = 0.0;
   out_6815214623410224821[317] = 0.0;
   out_6815214623410224821[318] = 0.0;
   out_6815214623410224821[319] = 0.0;
   out_6815214623410224821[320] = 0.0;
   out_6815214623410224821[321] = 0.0;
   out_6815214623410224821[322] = 0.0;
   out_6815214623410224821[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4724171785691844407) {
   out_4724171785691844407[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4724171785691844407[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4724171785691844407[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4724171785691844407[3] = dt*state[12] + state[3];
   out_4724171785691844407[4] = dt*state[13] + state[4];
   out_4724171785691844407[5] = dt*state[14] + state[5];
   out_4724171785691844407[6] = state[6];
   out_4724171785691844407[7] = state[7];
   out_4724171785691844407[8] = state[8];
   out_4724171785691844407[9] = state[9];
   out_4724171785691844407[10] = state[10];
   out_4724171785691844407[11] = state[11];
   out_4724171785691844407[12] = state[12];
   out_4724171785691844407[13] = state[13];
   out_4724171785691844407[14] = state[14];
   out_4724171785691844407[15] = state[15];
   out_4724171785691844407[16] = state[16];
   out_4724171785691844407[17] = state[17];
}
void F_fun(double *state, double dt, double *out_638456415896569458) {
   out_638456415896569458[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_638456415896569458[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_638456415896569458[2] = 0;
   out_638456415896569458[3] = 0;
   out_638456415896569458[4] = 0;
   out_638456415896569458[5] = 0;
   out_638456415896569458[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_638456415896569458[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_638456415896569458[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_638456415896569458[9] = 0;
   out_638456415896569458[10] = 0;
   out_638456415896569458[11] = 0;
   out_638456415896569458[12] = 0;
   out_638456415896569458[13] = 0;
   out_638456415896569458[14] = 0;
   out_638456415896569458[15] = 0;
   out_638456415896569458[16] = 0;
   out_638456415896569458[17] = 0;
   out_638456415896569458[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_638456415896569458[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_638456415896569458[20] = 0;
   out_638456415896569458[21] = 0;
   out_638456415896569458[22] = 0;
   out_638456415896569458[23] = 0;
   out_638456415896569458[24] = 0;
   out_638456415896569458[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_638456415896569458[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_638456415896569458[27] = 0;
   out_638456415896569458[28] = 0;
   out_638456415896569458[29] = 0;
   out_638456415896569458[30] = 0;
   out_638456415896569458[31] = 0;
   out_638456415896569458[32] = 0;
   out_638456415896569458[33] = 0;
   out_638456415896569458[34] = 0;
   out_638456415896569458[35] = 0;
   out_638456415896569458[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_638456415896569458[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_638456415896569458[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_638456415896569458[39] = 0;
   out_638456415896569458[40] = 0;
   out_638456415896569458[41] = 0;
   out_638456415896569458[42] = 0;
   out_638456415896569458[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_638456415896569458[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_638456415896569458[45] = 0;
   out_638456415896569458[46] = 0;
   out_638456415896569458[47] = 0;
   out_638456415896569458[48] = 0;
   out_638456415896569458[49] = 0;
   out_638456415896569458[50] = 0;
   out_638456415896569458[51] = 0;
   out_638456415896569458[52] = 0;
   out_638456415896569458[53] = 0;
   out_638456415896569458[54] = 0;
   out_638456415896569458[55] = 0;
   out_638456415896569458[56] = 0;
   out_638456415896569458[57] = 1;
   out_638456415896569458[58] = 0;
   out_638456415896569458[59] = 0;
   out_638456415896569458[60] = 0;
   out_638456415896569458[61] = 0;
   out_638456415896569458[62] = 0;
   out_638456415896569458[63] = 0;
   out_638456415896569458[64] = 0;
   out_638456415896569458[65] = 0;
   out_638456415896569458[66] = dt;
   out_638456415896569458[67] = 0;
   out_638456415896569458[68] = 0;
   out_638456415896569458[69] = 0;
   out_638456415896569458[70] = 0;
   out_638456415896569458[71] = 0;
   out_638456415896569458[72] = 0;
   out_638456415896569458[73] = 0;
   out_638456415896569458[74] = 0;
   out_638456415896569458[75] = 0;
   out_638456415896569458[76] = 1;
   out_638456415896569458[77] = 0;
   out_638456415896569458[78] = 0;
   out_638456415896569458[79] = 0;
   out_638456415896569458[80] = 0;
   out_638456415896569458[81] = 0;
   out_638456415896569458[82] = 0;
   out_638456415896569458[83] = 0;
   out_638456415896569458[84] = 0;
   out_638456415896569458[85] = dt;
   out_638456415896569458[86] = 0;
   out_638456415896569458[87] = 0;
   out_638456415896569458[88] = 0;
   out_638456415896569458[89] = 0;
   out_638456415896569458[90] = 0;
   out_638456415896569458[91] = 0;
   out_638456415896569458[92] = 0;
   out_638456415896569458[93] = 0;
   out_638456415896569458[94] = 0;
   out_638456415896569458[95] = 1;
   out_638456415896569458[96] = 0;
   out_638456415896569458[97] = 0;
   out_638456415896569458[98] = 0;
   out_638456415896569458[99] = 0;
   out_638456415896569458[100] = 0;
   out_638456415896569458[101] = 0;
   out_638456415896569458[102] = 0;
   out_638456415896569458[103] = 0;
   out_638456415896569458[104] = dt;
   out_638456415896569458[105] = 0;
   out_638456415896569458[106] = 0;
   out_638456415896569458[107] = 0;
   out_638456415896569458[108] = 0;
   out_638456415896569458[109] = 0;
   out_638456415896569458[110] = 0;
   out_638456415896569458[111] = 0;
   out_638456415896569458[112] = 0;
   out_638456415896569458[113] = 0;
   out_638456415896569458[114] = 1;
   out_638456415896569458[115] = 0;
   out_638456415896569458[116] = 0;
   out_638456415896569458[117] = 0;
   out_638456415896569458[118] = 0;
   out_638456415896569458[119] = 0;
   out_638456415896569458[120] = 0;
   out_638456415896569458[121] = 0;
   out_638456415896569458[122] = 0;
   out_638456415896569458[123] = 0;
   out_638456415896569458[124] = 0;
   out_638456415896569458[125] = 0;
   out_638456415896569458[126] = 0;
   out_638456415896569458[127] = 0;
   out_638456415896569458[128] = 0;
   out_638456415896569458[129] = 0;
   out_638456415896569458[130] = 0;
   out_638456415896569458[131] = 0;
   out_638456415896569458[132] = 0;
   out_638456415896569458[133] = 1;
   out_638456415896569458[134] = 0;
   out_638456415896569458[135] = 0;
   out_638456415896569458[136] = 0;
   out_638456415896569458[137] = 0;
   out_638456415896569458[138] = 0;
   out_638456415896569458[139] = 0;
   out_638456415896569458[140] = 0;
   out_638456415896569458[141] = 0;
   out_638456415896569458[142] = 0;
   out_638456415896569458[143] = 0;
   out_638456415896569458[144] = 0;
   out_638456415896569458[145] = 0;
   out_638456415896569458[146] = 0;
   out_638456415896569458[147] = 0;
   out_638456415896569458[148] = 0;
   out_638456415896569458[149] = 0;
   out_638456415896569458[150] = 0;
   out_638456415896569458[151] = 0;
   out_638456415896569458[152] = 1;
   out_638456415896569458[153] = 0;
   out_638456415896569458[154] = 0;
   out_638456415896569458[155] = 0;
   out_638456415896569458[156] = 0;
   out_638456415896569458[157] = 0;
   out_638456415896569458[158] = 0;
   out_638456415896569458[159] = 0;
   out_638456415896569458[160] = 0;
   out_638456415896569458[161] = 0;
   out_638456415896569458[162] = 0;
   out_638456415896569458[163] = 0;
   out_638456415896569458[164] = 0;
   out_638456415896569458[165] = 0;
   out_638456415896569458[166] = 0;
   out_638456415896569458[167] = 0;
   out_638456415896569458[168] = 0;
   out_638456415896569458[169] = 0;
   out_638456415896569458[170] = 0;
   out_638456415896569458[171] = 1;
   out_638456415896569458[172] = 0;
   out_638456415896569458[173] = 0;
   out_638456415896569458[174] = 0;
   out_638456415896569458[175] = 0;
   out_638456415896569458[176] = 0;
   out_638456415896569458[177] = 0;
   out_638456415896569458[178] = 0;
   out_638456415896569458[179] = 0;
   out_638456415896569458[180] = 0;
   out_638456415896569458[181] = 0;
   out_638456415896569458[182] = 0;
   out_638456415896569458[183] = 0;
   out_638456415896569458[184] = 0;
   out_638456415896569458[185] = 0;
   out_638456415896569458[186] = 0;
   out_638456415896569458[187] = 0;
   out_638456415896569458[188] = 0;
   out_638456415896569458[189] = 0;
   out_638456415896569458[190] = 1;
   out_638456415896569458[191] = 0;
   out_638456415896569458[192] = 0;
   out_638456415896569458[193] = 0;
   out_638456415896569458[194] = 0;
   out_638456415896569458[195] = 0;
   out_638456415896569458[196] = 0;
   out_638456415896569458[197] = 0;
   out_638456415896569458[198] = 0;
   out_638456415896569458[199] = 0;
   out_638456415896569458[200] = 0;
   out_638456415896569458[201] = 0;
   out_638456415896569458[202] = 0;
   out_638456415896569458[203] = 0;
   out_638456415896569458[204] = 0;
   out_638456415896569458[205] = 0;
   out_638456415896569458[206] = 0;
   out_638456415896569458[207] = 0;
   out_638456415896569458[208] = 0;
   out_638456415896569458[209] = 1;
   out_638456415896569458[210] = 0;
   out_638456415896569458[211] = 0;
   out_638456415896569458[212] = 0;
   out_638456415896569458[213] = 0;
   out_638456415896569458[214] = 0;
   out_638456415896569458[215] = 0;
   out_638456415896569458[216] = 0;
   out_638456415896569458[217] = 0;
   out_638456415896569458[218] = 0;
   out_638456415896569458[219] = 0;
   out_638456415896569458[220] = 0;
   out_638456415896569458[221] = 0;
   out_638456415896569458[222] = 0;
   out_638456415896569458[223] = 0;
   out_638456415896569458[224] = 0;
   out_638456415896569458[225] = 0;
   out_638456415896569458[226] = 0;
   out_638456415896569458[227] = 0;
   out_638456415896569458[228] = 1;
   out_638456415896569458[229] = 0;
   out_638456415896569458[230] = 0;
   out_638456415896569458[231] = 0;
   out_638456415896569458[232] = 0;
   out_638456415896569458[233] = 0;
   out_638456415896569458[234] = 0;
   out_638456415896569458[235] = 0;
   out_638456415896569458[236] = 0;
   out_638456415896569458[237] = 0;
   out_638456415896569458[238] = 0;
   out_638456415896569458[239] = 0;
   out_638456415896569458[240] = 0;
   out_638456415896569458[241] = 0;
   out_638456415896569458[242] = 0;
   out_638456415896569458[243] = 0;
   out_638456415896569458[244] = 0;
   out_638456415896569458[245] = 0;
   out_638456415896569458[246] = 0;
   out_638456415896569458[247] = 1;
   out_638456415896569458[248] = 0;
   out_638456415896569458[249] = 0;
   out_638456415896569458[250] = 0;
   out_638456415896569458[251] = 0;
   out_638456415896569458[252] = 0;
   out_638456415896569458[253] = 0;
   out_638456415896569458[254] = 0;
   out_638456415896569458[255] = 0;
   out_638456415896569458[256] = 0;
   out_638456415896569458[257] = 0;
   out_638456415896569458[258] = 0;
   out_638456415896569458[259] = 0;
   out_638456415896569458[260] = 0;
   out_638456415896569458[261] = 0;
   out_638456415896569458[262] = 0;
   out_638456415896569458[263] = 0;
   out_638456415896569458[264] = 0;
   out_638456415896569458[265] = 0;
   out_638456415896569458[266] = 1;
   out_638456415896569458[267] = 0;
   out_638456415896569458[268] = 0;
   out_638456415896569458[269] = 0;
   out_638456415896569458[270] = 0;
   out_638456415896569458[271] = 0;
   out_638456415896569458[272] = 0;
   out_638456415896569458[273] = 0;
   out_638456415896569458[274] = 0;
   out_638456415896569458[275] = 0;
   out_638456415896569458[276] = 0;
   out_638456415896569458[277] = 0;
   out_638456415896569458[278] = 0;
   out_638456415896569458[279] = 0;
   out_638456415896569458[280] = 0;
   out_638456415896569458[281] = 0;
   out_638456415896569458[282] = 0;
   out_638456415896569458[283] = 0;
   out_638456415896569458[284] = 0;
   out_638456415896569458[285] = 1;
   out_638456415896569458[286] = 0;
   out_638456415896569458[287] = 0;
   out_638456415896569458[288] = 0;
   out_638456415896569458[289] = 0;
   out_638456415896569458[290] = 0;
   out_638456415896569458[291] = 0;
   out_638456415896569458[292] = 0;
   out_638456415896569458[293] = 0;
   out_638456415896569458[294] = 0;
   out_638456415896569458[295] = 0;
   out_638456415896569458[296] = 0;
   out_638456415896569458[297] = 0;
   out_638456415896569458[298] = 0;
   out_638456415896569458[299] = 0;
   out_638456415896569458[300] = 0;
   out_638456415896569458[301] = 0;
   out_638456415896569458[302] = 0;
   out_638456415896569458[303] = 0;
   out_638456415896569458[304] = 1;
   out_638456415896569458[305] = 0;
   out_638456415896569458[306] = 0;
   out_638456415896569458[307] = 0;
   out_638456415896569458[308] = 0;
   out_638456415896569458[309] = 0;
   out_638456415896569458[310] = 0;
   out_638456415896569458[311] = 0;
   out_638456415896569458[312] = 0;
   out_638456415896569458[313] = 0;
   out_638456415896569458[314] = 0;
   out_638456415896569458[315] = 0;
   out_638456415896569458[316] = 0;
   out_638456415896569458[317] = 0;
   out_638456415896569458[318] = 0;
   out_638456415896569458[319] = 0;
   out_638456415896569458[320] = 0;
   out_638456415896569458[321] = 0;
   out_638456415896569458[322] = 0;
   out_638456415896569458[323] = 1;
}
void h_4(double *state, double *unused, double *out_3715383509872023288) {
   out_3715383509872023288[0] = state[6] + state[9];
   out_3715383509872023288[1] = state[7] + state[10];
   out_3715383509872023288[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_7859722240455419223) {
   out_7859722240455419223[0] = 0;
   out_7859722240455419223[1] = 0;
   out_7859722240455419223[2] = 0;
   out_7859722240455419223[3] = 0;
   out_7859722240455419223[4] = 0;
   out_7859722240455419223[5] = 0;
   out_7859722240455419223[6] = 1;
   out_7859722240455419223[7] = 0;
   out_7859722240455419223[8] = 0;
   out_7859722240455419223[9] = 1;
   out_7859722240455419223[10] = 0;
   out_7859722240455419223[11] = 0;
   out_7859722240455419223[12] = 0;
   out_7859722240455419223[13] = 0;
   out_7859722240455419223[14] = 0;
   out_7859722240455419223[15] = 0;
   out_7859722240455419223[16] = 0;
   out_7859722240455419223[17] = 0;
   out_7859722240455419223[18] = 0;
   out_7859722240455419223[19] = 0;
   out_7859722240455419223[20] = 0;
   out_7859722240455419223[21] = 0;
   out_7859722240455419223[22] = 0;
   out_7859722240455419223[23] = 0;
   out_7859722240455419223[24] = 0;
   out_7859722240455419223[25] = 1;
   out_7859722240455419223[26] = 0;
   out_7859722240455419223[27] = 0;
   out_7859722240455419223[28] = 1;
   out_7859722240455419223[29] = 0;
   out_7859722240455419223[30] = 0;
   out_7859722240455419223[31] = 0;
   out_7859722240455419223[32] = 0;
   out_7859722240455419223[33] = 0;
   out_7859722240455419223[34] = 0;
   out_7859722240455419223[35] = 0;
   out_7859722240455419223[36] = 0;
   out_7859722240455419223[37] = 0;
   out_7859722240455419223[38] = 0;
   out_7859722240455419223[39] = 0;
   out_7859722240455419223[40] = 0;
   out_7859722240455419223[41] = 0;
   out_7859722240455419223[42] = 0;
   out_7859722240455419223[43] = 0;
   out_7859722240455419223[44] = 1;
   out_7859722240455419223[45] = 0;
   out_7859722240455419223[46] = 0;
   out_7859722240455419223[47] = 1;
   out_7859722240455419223[48] = 0;
   out_7859722240455419223[49] = 0;
   out_7859722240455419223[50] = 0;
   out_7859722240455419223[51] = 0;
   out_7859722240455419223[52] = 0;
   out_7859722240455419223[53] = 0;
}
void h_10(double *state, double *unused, double *out_1493881979826544307) {
   out_1493881979826544307[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_1493881979826544307[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_1493881979826544307[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8226181140571901267) {
   out_8226181140571901267[0] = 0;
   out_8226181140571901267[1] = 9.8100000000000005*cos(state[1]);
   out_8226181140571901267[2] = 0;
   out_8226181140571901267[3] = 0;
   out_8226181140571901267[4] = -state[8];
   out_8226181140571901267[5] = state[7];
   out_8226181140571901267[6] = 0;
   out_8226181140571901267[7] = state[5];
   out_8226181140571901267[8] = -state[4];
   out_8226181140571901267[9] = 0;
   out_8226181140571901267[10] = 0;
   out_8226181140571901267[11] = 0;
   out_8226181140571901267[12] = 1;
   out_8226181140571901267[13] = 0;
   out_8226181140571901267[14] = 0;
   out_8226181140571901267[15] = 1;
   out_8226181140571901267[16] = 0;
   out_8226181140571901267[17] = 0;
   out_8226181140571901267[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8226181140571901267[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8226181140571901267[20] = 0;
   out_8226181140571901267[21] = state[8];
   out_8226181140571901267[22] = 0;
   out_8226181140571901267[23] = -state[6];
   out_8226181140571901267[24] = -state[5];
   out_8226181140571901267[25] = 0;
   out_8226181140571901267[26] = state[3];
   out_8226181140571901267[27] = 0;
   out_8226181140571901267[28] = 0;
   out_8226181140571901267[29] = 0;
   out_8226181140571901267[30] = 0;
   out_8226181140571901267[31] = 1;
   out_8226181140571901267[32] = 0;
   out_8226181140571901267[33] = 0;
   out_8226181140571901267[34] = 1;
   out_8226181140571901267[35] = 0;
   out_8226181140571901267[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8226181140571901267[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8226181140571901267[38] = 0;
   out_8226181140571901267[39] = -state[7];
   out_8226181140571901267[40] = state[6];
   out_8226181140571901267[41] = 0;
   out_8226181140571901267[42] = state[4];
   out_8226181140571901267[43] = -state[3];
   out_8226181140571901267[44] = 0;
   out_8226181140571901267[45] = 0;
   out_8226181140571901267[46] = 0;
   out_8226181140571901267[47] = 0;
   out_8226181140571901267[48] = 0;
   out_8226181140571901267[49] = 0;
   out_8226181140571901267[50] = 1;
   out_8226181140571901267[51] = 0;
   out_8226181140571901267[52] = 0;
   out_8226181140571901267[53] = 1;
}
void h_13(double *state, double *unused, double *out_820596947016455055) {
   out_820596947016455055[0] = state[3];
   out_820596947016455055[1] = state[4];
   out_820596947016455055[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4647448415123086422) {
   out_4647448415123086422[0] = 0;
   out_4647448415123086422[1] = 0;
   out_4647448415123086422[2] = 0;
   out_4647448415123086422[3] = 1;
   out_4647448415123086422[4] = 0;
   out_4647448415123086422[5] = 0;
   out_4647448415123086422[6] = 0;
   out_4647448415123086422[7] = 0;
   out_4647448415123086422[8] = 0;
   out_4647448415123086422[9] = 0;
   out_4647448415123086422[10] = 0;
   out_4647448415123086422[11] = 0;
   out_4647448415123086422[12] = 0;
   out_4647448415123086422[13] = 0;
   out_4647448415123086422[14] = 0;
   out_4647448415123086422[15] = 0;
   out_4647448415123086422[16] = 0;
   out_4647448415123086422[17] = 0;
   out_4647448415123086422[18] = 0;
   out_4647448415123086422[19] = 0;
   out_4647448415123086422[20] = 0;
   out_4647448415123086422[21] = 0;
   out_4647448415123086422[22] = 1;
   out_4647448415123086422[23] = 0;
   out_4647448415123086422[24] = 0;
   out_4647448415123086422[25] = 0;
   out_4647448415123086422[26] = 0;
   out_4647448415123086422[27] = 0;
   out_4647448415123086422[28] = 0;
   out_4647448415123086422[29] = 0;
   out_4647448415123086422[30] = 0;
   out_4647448415123086422[31] = 0;
   out_4647448415123086422[32] = 0;
   out_4647448415123086422[33] = 0;
   out_4647448415123086422[34] = 0;
   out_4647448415123086422[35] = 0;
   out_4647448415123086422[36] = 0;
   out_4647448415123086422[37] = 0;
   out_4647448415123086422[38] = 0;
   out_4647448415123086422[39] = 0;
   out_4647448415123086422[40] = 0;
   out_4647448415123086422[41] = 1;
   out_4647448415123086422[42] = 0;
   out_4647448415123086422[43] = 0;
   out_4647448415123086422[44] = 0;
   out_4647448415123086422[45] = 0;
   out_4647448415123086422[46] = 0;
   out_4647448415123086422[47] = 0;
   out_4647448415123086422[48] = 0;
   out_4647448415123086422[49] = 0;
   out_4647448415123086422[50] = 0;
   out_4647448415123086422[51] = 0;
   out_4647448415123086422[52] = 0;
   out_4647448415123086422[53] = 0;
}
void h_14(double *state, double *unused, double *out_7488710011373447915) {
   out_7488710011373447915[0] = state[6];
   out_7488710011373447915[1] = state[7];
   out_7488710011373447915[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3896481384115934694) {
   out_3896481384115934694[0] = 0;
   out_3896481384115934694[1] = 0;
   out_3896481384115934694[2] = 0;
   out_3896481384115934694[3] = 0;
   out_3896481384115934694[4] = 0;
   out_3896481384115934694[5] = 0;
   out_3896481384115934694[6] = 1;
   out_3896481384115934694[7] = 0;
   out_3896481384115934694[8] = 0;
   out_3896481384115934694[9] = 0;
   out_3896481384115934694[10] = 0;
   out_3896481384115934694[11] = 0;
   out_3896481384115934694[12] = 0;
   out_3896481384115934694[13] = 0;
   out_3896481384115934694[14] = 0;
   out_3896481384115934694[15] = 0;
   out_3896481384115934694[16] = 0;
   out_3896481384115934694[17] = 0;
   out_3896481384115934694[18] = 0;
   out_3896481384115934694[19] = 0;
   out_3896481384115934694[20] = 0;
   out_3896481384115934694[21] = 0;
   out_3896481384115934694[22] = 0;
   out_3896481384115934694[23] = 0;
   out_3896481384115934694[24] = 0;
   out_3896481384115934694[25] = 1;
   out_3896481384115934694[26] = 0;
   out_3896481384115934694[27] = 0;
   out_3896481384115934694[28] = 0;
   out_3896481384115934694[29] = 0;
   out_3896481384115934694[30] = 0;
   out_3896481384115934694[31] = 0;
   out_3896481384115934694[32] = 0;
   out_3896481384115934694[33] = 0;
   out_3896481384115934694[34] = 0;
   out_3896481384115934694[35] = 0;
   out_3896481384115934694[36] = 0;
   out_3896481384115934694[37] = 0;
   out_3896481384115934694[38] = 0;
   out_3896481384115934694[39] = 0;
   out_3896481384115934694[40] = 0;
   out_3896481384115934694[41] = 0;
   out_3896481384115934694[42] = 0;
   out_3896481384115934694[43] = 0;
   out_3896481384115934694[44] = 1;
   out_3896481384115934694[45] = 0;
   out_3896481384115934694[46] = 0;
   out_3896481384115934694[47] = 0;
   out_3896481384115934694[48] = 0;
   out_3896481384115934694[49] = 0;
   out_3896481384115934694[50] = 0;
   out_3896481384115934694[51] = 0;
   out_3896481384115934694[52] = 0;
   out_3896481384115934694[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3650099251769799718) {
  err_fun(nom_x, delta_x, out_3650099251769799718);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4549899801136771746) {
  inv_err_fun(nom_x, true_x, out_4549899801136771746);
}
void pose_H_mod_fun(double *state, double *out_6815214623410224821) {
  H_mod_fun(state, out_6815214623410224821);
}
void pose_f_fun(double *state, double dt, double *out_4724171785691844407) {
  f_fun(state,  dt, out_4724171785691844407);
}
void pose_F_fun(double *state, double dt, double *out_638456415896569458) {
  F_fun(state,  dt, out_638456415896569458);
}
void pose_h_4(double *state, double *unused, double *out_3715383509872023288) {
  h_4(state, unused, out_3715383509872023288);
}
void pose_H_4(double *state, double *unused, double *out_7859722240455419223) {
  H_4(state, unused, out_7859722240455419223);
}
void pose_h_10(double *state, double *unused, double *out_1493881979826544307) {
  h_10(state, unused, out_1493881979826544307);
}
void pose_H_10(double *state, double *unused, double *out_8226181140571901267) {
  H_10(state, unused, out_8226181140571901267);
}
void pose_h_13(double *state, double *unused, double *out_820596947016455055) {
  h_13(state, unused, out_820596947016455055);
}
void pose_H_13(double *state, double *unused, double *out_4647448415123086422) {
  H_13(state, unused, out_4647448415123086422);
}
void pose_h_14(double *state, double *unused, double *out_7488710011373447915) {
  h_14(state, unused, out_7488710011373447915);
}
void pose_H_14(double *state, double *unused, double *out_3896481384115934694) {
  H_14(state, unused, out_3896481384115934694);
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
