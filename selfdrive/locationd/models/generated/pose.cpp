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
void err_fun(double *nom_x, double *delta_x, double *out_2276930388742637984) {
   out_2276930388742637984[0] = delta_x[0] + nom_x[0];
   out_2276930388742637984[1] = delta_x[1] + nom_x[1];
   out_2276930388742637984[2] = delta_x[2] + nom_x[2];
   out_2276930388742637984[3] = delta_x[3] + nom_x[3];
   out_2276930388742637984[4] = delta_x[4] + nom_x[4];
   out_2276930388742637984[5] = delta_x[5] + nom_x[5];
   out_2276930388742637984[6] = delta_x[6] + nom_x[6];
   out_2276930388742637984[7] = delta_x[7] + nom_x[7];
   out_2276930388742637984[8] = delta_x[8] + nom_x[8];
   out_2276930388742637984[9] = delta_x[9] + nom_x[9];
   out_2276930388742637984[10] = delta_x[10] + nom_x[10];
   out_2276930388742637984[11] = delta_x[11] + nom_x[11];
   out_2276930388742637984[12] = delta_x[12] + nom_x[12];
   out_2276930388742637984[13] = delta_x[13] + nom_x[13];
   out_2276930388742637984[14] = delta_x[14] + nom_x[14];
   out_2276930388742637984[15] = delta_x[15] + nom_x[15];
   out_2276930388742637984[16] = delta_x[16] + nom_x[16];
   out_2276930388742637984[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5553036191683273841) {
   out_5553036191683273841[0] = -nom_x[0] + true_x[0];
   out_5553036191683273841[1] = -nom_x[1] + true_x[1];
   out_5553036191683273841[2] = -nom_x[2] + true_x[2];
   out_5553036191683273841[3] = -nom_x[3] + true_x[3];
   out_5553036191683273841[4] = -nom_x[4] + true_x[4];
   out_5553036191683273841[5] = -nom_x[5] + true_x[5];
   out_5553036191683273841[6] = -nom_x[6] + true_x[6];
   out_5553036191683273841[7] = -nom_x[7] + true_x[7];
   out_5553036191683273841[8] = -nom_x[8] + true_x[8];
   out_5553036191683273841[9] = -nom_x[9] + true_x[9];
   out_5553036191683273841[10] = -nom_x[10] + true_x[10];
   out_5553036191683273841[11] = -nom_x[11] + true_x[11];
   out_5553036191683273841[12] = -nom_x[12] + true_x[12];
   out_5553036191683273841[13] = -nom_x[13] + true_x[13];
   out_5553036191683273841[14] = -nom_x[14] + true_x[14];
   out_5553036191683273841[15] = -nom_x[15] + true_x[15];
   out_5553036191683273841[16] = -nom_x[16] + true_x[16];
   out_5553036191683273841[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_9138325999640393464) {
   out_9138325999640393464[0] = 1.0;
   out_9138325999640393464[1] = 0.0;
   out_9138325999640393464[2] = 0.0;
   out_9138325999640393464[3] = 0.0;
   out_9138325999640393464[4] = 0.0;
   out_9138325999640393464[5] = 0.0;
   out_9138325999640393464[6] = 0.0;
   out_9138325999640393464[7] = 0.0;
   out_9138325999640393464[8] = 0.0;
   out_9138325999640393464[9] = 0.0;
   out_9138325999640393464[10] = 0.0;
   out_9138325999640393464[11] = 0.0;
   out_9138325999640393464[12] = 0.0;
   out_9138325999640393464[13] = 0.0;
   out_9138325999640393464[14] = 0.0;
   out_9138325999640393464[15] = 0.0;
   out_9138325999640393464[16] = 0.0;
   out_9138325999640393464[17] = 0.0;
   out_9138325999640393464[18] = 0.0;
   out_9138325999640393464[19] = 1.0;
   out_9138325999640393464[20] = 0.0;
   out_9138325999640393464[21] = 0.0;
   out_9138325999640393464[22] = 0.0;
   out_9138325999640393464[23] = 0.0;
   out_9138325999640393464[24] = 0.0;
   out_9138325999640393464[25] = 0.0;
   out_9138325999640393464[26] = 0.0;
   out_9138325999640393464[27] = 0.0;
   out_9138325999640393464[28] = 0.0;
   out_9138325999640393464[29] = 0.0;
   out_9138325999640393464[30] = 0.0;
   out_9138325999640393464[31] = 0.0;
   out_9138325999640393464[32] = 0.0;
   out_9138325999640393464[33] = 0.0;
   out_9138325999640393464[34] = 0.0;
   out_9138325999640393464[35] = 0.0;
   out_9138325999640393464[36] = 0.0;
   out_9138325999640393464[37] = 0.0;
   out_9138325999640393464[38] = 1.0;
   out_9138325999640393464[39] = 0.0;
   out_9138325999640393464[40] = 0.0;
   out_9138325999640393464[41] = 0.0;
   out_9138325999640393464[42] = 0.0;
   out_9138325999640393464[43] = 0.0;
   out_9138325999640393464[44] = 0.0;
   out_9138325999640393464[45] = 0.0;
   out_9138325999640393464[46] = 0.0;
   out_9138325999640393464[47] = 0.0;
   out_9138325999640393464[48] = 0.0;
   out_9138325999640393464[49] = 0.0;
   out_9138325999640393464[50] = 0.0;
   out_9138325999640393464[51] = 0.0;
   out_9138325999640393464[52] = 0.0;
   out_9138325999640393464[53] = 0.0;
   out_9138325999640393464[54] = 0.0;
   out_9138325999640393464[55] = 0.0;
   out_9138325999640393464[56] = 0.0;
   out_9138325999640393464[57] = 1.0;
   out_9138325999640393464[58] = 0.0;
   out_9138325999640393464[59] = 0.0;
   out_9138325999640393464[60] = 0.0;
   out_9138325999640393464[61] = 0.0;
   out_9138325999640393464[62] = 0.0;
   out_9138325999640393464[63] = 0.0;
   out_9138325999640393464[64] = 0.0;
   out_9138325999640393464[65] = 0.0;
   out_9138325999640393464[66] = 0.0;
   out_9138325999640393464[67] = 0.0;
   out_9138325999640393464[68] = 0.0;
   out_9138325999640393464[69] = 0.0;
   out_9138325999640393464[70] = 0.0;
   out_9138325999640393464[71] = 0.0;
   out_9138325999640393464[72] = 0.0;
   out_9138325999640393464[73] = 0.0;
   out_9138325999640393464[74] = 0.0;
   out_9138325999640393464[75] = 0.0;
   out_9138325999640393464[76] = 1.0;
   out_9138325999640393464[77] = 0.0;
   out_9138325999640393464[78] = 0.0;
   out_9138325999640393464[79] = 0.0;
   out_9138325999640393464[80] = 0.0;
   out_9138325999640393464[81] = 0.0;
   out_9138325999640393464[82] = 0.0;
   out_9138325999640393464[83] = 0.0;
   out_9138325999640393464[84] = 0.0;
   out_9138325999640393464[85] = 0.0;
   out_9138325999640393464[86] = 0.0;
   out_9138325999640393464[87] = 0.0;
   out_9138325999640393464[88] = 0.0;
   out_9138325999640393464[89] = 0.0;
   out_9138325999640393464[90] = 0.0;
   out_9138325999640393464[91] = 0.0;
   out_9138325999640393464[92] = 0.0;
   out_9138325999640393464[93] = 0.0;
   out_9138325999640393464[94] = 0.0;
   out_9138325999640393464[95] = 1.0;
   out_9138325999640393464[96] = 0.0;
   out_9138325999640393464[97] = 0.0;
   out_9138325999640393464[98] = 0.0;
   out_9138325999640393464[99] = 0.0;
   out_9138325999640393464[100] = 0.0;
   out_9138325999640393464[101] = 0.0;
   out_9138325999640393464[102] = 0.0;
   out_9138325999640393464[103] = 0.0;
   out_9138325999640393464[104] = 0.0;
   out_9138325999640393464[105] = 0.0;
   out_9138325999640393464[106] = 0.0;
   out_9138325999640393464[107] = 0.0;
   out_9138325999640393464[108] = 0.0;
   out_9138325999640393464[109] = 0.0;
   out_9138325999640393464[110] = 0.0;
   out_9138325999640393464[111] = 0.0;
   out_9138325999640393464[112] = 0.0;
   out_9138325999640393464[113] = 0.0;
   out_9138325999640393464[114] = 1.0;
   out_9138325999640393464[115] = 0.0;
   out_9138325999640393464[116] = 0.0;
   out_9138325999640393464[117] = 0.0;
   out_9138325999640393464[118] = 0.0;
   out_9138325999640393464[119] = 0.0;
   out_9138325999640393464[120] = 0.0;
   out_9138325999640393464[121] = 0.0;
   out_9138325999640393464[122] = 0.0;
   out_9138325999640393464[123] = 0.0;
   out_9138325999640393464[124] = 0.0;
   out_9138325999640393464[125] = 0.0;
   out_9138325999640393464[126] = 0.0;
   out_9138325999640393464[127] = 0.0;
   out_9138325999640393464[128] = 0.0;
   out_9138325999640393464[129] = 0.0;
   out_9138325999640393464[130] = 0.0;
   out_9138325999640393464[131] = 0.0;
   out_9138325999640393464[132] = 0.0;
   out_9138325999640393464[133] = 1.0;
   out_9138325999640393464[134] = 0.0;
   out_9138325999640393464[135] = 0.0;
   out_9138325999640393464[136] = 0.0;
   out_9138325999640393464[137] = 0.0;
   out_9138325999640393464[138] = 0.0;
   out_9138325999640393464[139] = 0.0;
   out_9138325999640393464[140] = 0.0;
   out_9138325999640393464[141] = 0.0;
   out_9138325999640393464[142] = 0.0;
   out_9138325999640393464[143] = 0.0;
   out_9138325999640393464[144] = 0.0;
   out_9138325999640393464[145] = 0.0;
   out_9138325999640393464[146] = 0.0;
   out_9138325999640393464[147] = 0.0;
   out_9138325999640393464[148] = 0.0;
   out_9138325999640393464[149] = 0.0;
   out_9138325999640393464[150] = 0.0;
   out_9138325999640393464[151] = 0.0;
   out_9138325999640393464[152] = 1.0;
   out_9138325999640393464[153] = 0.0;
   out_9138325999640393464[154] = 0.0;
   out_9138325999640393464[155] = 0.0;
   out_9138325999640393464[156] = 0.0;
   out_9138325999640393464[157] = 0.0;
   out_9138325999640393464[158] = 0.0;
   out_9138325999640393464[159] = 0.0;
   out_9138325999640393464[160] = 0.0;
   out_9138325999640393464[161] = 0.0;
   out_9138325999640393464[162] = 0.0;
   out_9138325999640393464[163] = 0.0;
   out_9138325999640393464[164] = 0.0;
   out_9138325999640393464[165] = 0.0;
   out_9138325999640393464[166] = 0.0;
   out_9138325999640393464[167] = 0.0;
   out_9138325999640393464[168] = 0.0;
   out_9138325999640393464[169] = 0.0;
   out_9138325999640393464[170] = 0.0;
   out_9138325999640393464[171] = 1.0;
   out_9138325999640393464[172] = 0.0;
   out_9138325999640393464[173] = 0.0;
   out_9138325999640393464[174] = 0.0;
   out_9138325999640393464[175] = 0.0;
   out_9138325999640393464[176] = 0.0;
   out_9138325999640393464[177] = 0.0;
   out_9138325999640393464[178] = 0.0;
   out_9138325999640393464[179] = 0.0;
   out_9138325999640393464[180] = 0.0;
   out_9138325999640393464[181] = 0.0;
   out_9138325999640393464[182] = 0.0;
   out_9138325999640393464[183] = 0.0;
   out_9138325999640393464[184] = 0.0;
   out_9138325999640393464[185] = 0.0;
   out_9138325999640393464[186] = 0.0;
   out_9138325999640393464[187] = 0.0;
   out_9138325999640393464[188] = 0.0;
   out_9138325999640393464[189] = 0.0;
   out_9138325999640393464[190] = 1.0;
   out_9138325999640393464[191] = 0.0;
   out_9138325999640393464[192] = 0.0;
   out_9138325999640393464[193] = 0.0;
   out_9138325999640393464[194] = 0.0;
   out_9138325999640393464[195] = 0.0;
   out_9138325999640393464[196] = 0.0;
   out_9138325999640393464[197] = 0.0;
   out_9138325999640393464[198] = 0.0;
   out_9138325999640393464[199] = 0.0;
   out_9138325999640393464[200] = 0.0;
   out_9138325999640393464[201] = 0.0;
   out_9138325999640393464[202] = 0.0;
   out_9138325999640393464[203] = 0.0;
   out_9138325999640393464[204] = 0.0;
   out_9138325999640393464[205] = 0.0;
   out_9138325999640393464[206] = 0.0;
   out_9138325999640393464[207] = 0.0;
   out_9138325999640393464[208] = 0.0;
   out_9138325999640393464[209] = 1.0;
   out_9138325999640393464[210] = 0.0;
   out_9138325999640393464[211] = 0.0;
   out_9138325999640393464[212] = 0.0;
   out_9138325999640393464[213] = 0.0;
   out_9138325999640393464[214] = 0.0;
   out_9138325999640393464[215] = 0.0;
   out_9138325999640393464[216] = 0.0;
   out_9138325999640393464[217] = 0.0;
   out_9138325999640393464[218] = 0.0;
   out_9138325999640393464[219] = 0.0;
   out_9138325999640393464[220] = 0.0;
   out_9138325999640393464[221] = 0.0;
   out_9138325999640393464[222] = 0.0;
   out_9138325999640393464[223] = 0.0;
   out_9138325999640393464[224] = 0.0;
   out_9138325999640393464[225] = 0.0;
   out_9138325999640393464[226] = 0.0;
   out_9138325999640393464[227] = 0.0;
   out_9138325999640393464[228] = 1.0;
   out_9138325999640393464[229] = 0.0;
   out_9138325999640393464[230] = 0.0;
   out_9138325999640393464[231] = 0.0;
   out_9138325999640393464[232] = 0.0;
   out_9138325999640393464[233] = 0.0;
   out_9138325999640393464[234] = 0.0;
   out_9138325999640393464[235] = 0.0;
   out_9138325999640393464[236] = 0.0;
   out_9138325999640393464[237] = 0.0;
   out_9138325999640393464[238] = 0.0;
   out_9138325999640393464[239] = 0.0;
   out_9138325999640393464[240] = 0.0;
   out_9138325999640393464[241] = 0.0;
   out_9138325999640393464[242] = 0.0;
   out_9138325999640393464[243] = 0.0;
   out_9138325999640393464[244] = 0.0;
   out_9138325999640393464[245] = 0.0;
   out_9138325999640393464[246] = 0.0;
   out_9138325999640393464[247] = 1.0;
   out_9138325999640393464[248] = 0.0;
   out_9138325999640393464[249] = 0.0;
   out_9138325999640393464[250] = 0.0;
   out_9138325999640393464[251] = 0.0;
   out_9138325999640393464[252] = 0.0;
   out_9138325999640393464[253] = 0.0;
   out_9138325999640393464[254] = 0.0;
   out_9138325999640393464[255] = 0.0;
   out_9138325999640393464[256] = 0.0;
   out_9138325999640393464[257] = 0.0;
   out_9138325999640393464[258] = 0.0;
   out_9138325999640393464[259] = 0.0;
   out_9138325999640393464[260] = 0.0;
   out_9138325999640393464[261] = 0.0;
   out_9138325999640393464[262] = 0.0;
   out_9138325999640393464[263] = 0.0;
   out_9138325999640393464[264] = 0.0;
   out_9138325999640393464[265] = 0.0;
   out_9138325999640393464[266] = 1.0;
   out_9138325999640393464[267] = 0.0;
   out_9138325999640393464[268] = 0.0;
   out_9138325999640393464[269] = 0.0;
   out_9138325999640393464[270] = 0.0;
   out_9138325999640393464[271] = 0.0;
   out_9138325999640393464[272] = 0.0;
   out_9138325999640393464[273] = 0.0;
   out_9138325999640393464[274] = 0.0;
   out_9138325999640393464[275] = 0.0;
   out_9138325999640393464[276] = 0.0;
   out_9138325999640393464[277] = 0.0;
   out_9138325999640393464[278] = 0.0;
   out_9138325999640393464[279] = 0.0;
   out_9138325999640393464[280] = 0.0;
   out_9138325999640393464[281] = 0.0;
   out_9138325999640393464[282] = 0.0;
   out_9138325999640393464[283] = 0.0;
   out_9138325999640393464[284] = 0.0;
   out_9138325999640393464[285] = 1.0;
   out_9138325999640393464[286] = 0.0;
   out_9138325999640393464[287] = 0.0;
   out_9138325999640393464[288] = 0.0;
   out_9138325999640393464[289] = 0.0;
   out_9138325999640393464[290] = 0.0;
   out_9138325999640393464[291] = 0.0;
   out_9138325999640393464[292] = 0.0;
   out_9138325999640393464[293] = 0.0;
   out_9138325999640393464[294] = 0.0;
   out_9138325999640393464[295] = 0.0;
   out_9138325999640393464[296] = 0.0;
   out_9138325999640393464[297] = 0.0;
   out_9138325999640393464[298] = 0.0;
   out_9138325999640393464[299] = 0.0;
   out_9138325999640393464[300] = 0.0;
   out_9138325999640393464[301] = 0.0;
   out_9138325999640393464[302] = 0.0;
   out_9138325999640393464[303] = 0.0;
   out_9138325999640393464[304] = 1.0;
   out_9138325999640393464[305] = 0.0;
   out_9138325999640393464[306] = 0.0;
   out_9138325999640393464[307] = 0.0;
   out_9138325999640393464[308] = 0.0;
   out_9138325999640393464[309] = 0.0;
   out_9138325999640393464[310] = 0.0;
   out_9138325999640393464[311] = 0.0;
   out_9138325999640393464[312] = 0.0;
   out_9138325999640393464[313] = 0.0;
   out_9138325999640393464[314] = 0.0;
   out_9138325999640393464[315] = 0.0;
   out_9138325999640393464[316] = 0.0;
   out_9138325999640393464[317] = 0.0;
   out_9138325999640393464[318] = 0.0;
   out_9138325999640393464[319] = 0.0;
   out_9138325999640393464[320] = 0.0;
   out_9138325999640393464[321] = 0.0;
   out_9138325999640393464[322] = 0.0;
   out_9138325999640393464[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1147502803036589913) {
   out_1147502803036589913[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1147502803036589913[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1147502803036589913[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1147502803036589913[3] = dt*state[12] + state[3];
   out_1147502803036589913[4] = dt*state[13] + state[4];
   out_1147502803036589913[5] = dt*state[14] + state[5];
   out_1147502803036589913[6] = state[6];
   out_1147502803036589913[7] = state[7];
   out_1147502803036589913[8] = state[8];
   out_1147502803036589913[9] = state[9];
   out_1147502803036589913[10] = state[10];
   out_1147502803036589913[11] = state[11];
   out_1147502803036589913[12] = state[12];
   out_1147502803036589913[13] = state[13];
   out_1147502803036589913[14] = state[14];
   out_1147502803036589913[15] = state[15];
   out_1147502803036589913[16] = state[16];
   out_1147502803036589913[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5222045031026609980) {
   out_5222045031026609980[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5222045031026609980[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5222045031026609980[2] = 0;
   out_5222045031026609980[3] = 0;
   out_5222045031026609980[4] = 0;
   out_5222045031026609980[5] = 0;
   out_5222045031026609980[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5222045031026609980[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5222045031026609980[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5222045031026609980[9] = 0;
   out_5222045031026609980[10] = 0;
   out_5222045031026609980[11] = 0;
   out_5222045031026609980[12] = 0;
   out_5222045031026609980[13] = 0;
   out_5222045031026609980[14] = 0;
   out_5222045031026609980[15] = 0;
   out_5222045031026609980[16] = 0;
   out_5222045031026609980[17] = 0;
   out_5222045031026609980[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5222045031026609980[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5222045031026609980[20] = 0;
   out_5222045031026609980[21] = 0;
   out_5222045031026609980[22] = 0;
   out_5222045031026609980[23] = 0;
   out_5222045031026609980[24] = 0;
   out_5222045031026609980[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5222045031026609980[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5222045031026609980[27] = 0;
   out_5222045031026609980[28] = 0;
   out_5222045031026609980[29] = 0;
   out_5222045031026609980[30] = 0;
   out_5222045031026609980[31] = 0;
   out_5222045031026609980[32] = 0;
   out_5222045031026609980[33] = 0;
   out_5222045031026609980[34] = 0;
   out_5222045031026609980[35] = 0;
   out_5222045031026609980[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5222045031026609980[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5222045031026609980[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5222045031026609980[39] = 0;
   out_5222045031026609980[40] = 0;
   out_5222045031026609980[41] = 0;
   out_5222045031026609980[42] = 0;
   out_5222045031026609980[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5222045031026609980[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5222045031026609980[45] = 0;
   out_5222045031026609980[46] = 0;
   out_5222045031026609980[47] = 0;
   out_5222045031026609980[48] = 0;
   out_5222045031026609980[49] = 0;
   out_5222045031026609980[50] = 0;
   out_5222045031026609980[51] = 0;
   out_5222045031026609980[52] = 0;
   out_5222045031026609980[53] = 0;
   out_5222045031026609980[54] = 0;
   out_5222045031026609980[55] = 0;
   out_5222045031026609980[56] = 0;
   out_5222045031026609980[57] = 1;
   out_5222045031026609980[58] = 0;
   out_5222045031026609980[59] = 0;
   out_5222045031026609980[60] = 0;
   out_5222045031026609980[61] = 0;
   out_5222045031026609980[62] = 0;
   out_5222045031026609980[63] = 0;
   out_5222045031026609980[64] = 0;
   out_5222045031026609980[65] = 0;
   out_5222045031026609980[66] = dt;
   out_5222045031026609980[67] = 0;
   out_5222045031026609980[68] = 0;
   out_5222045031026609980[69] = 0;
   out_5222045031026609980[70] = 0;
   out_5222045031026609980[71] = 0;
   out_5222045031026609980[72] = 0;
   out_5222045031026609980[73] = 0;
   out_5222045031026609980[74] = 0;
   out_5222045031026609980[75] = 0;
   out_5222045031026609980[76] = 1;
   out_5222045031026609980[77] = 0;
   out_5222045031026609980[78] = 0;
   out_5222045031026609980[79] = 0;
   out_5222045031026609980[80] = 0;
   out_5222045031026609980[81] = 0;
   out_5222045031026609980[82] = 0;
   out_5222045031026609980[83] = 0;
   out_5222045031026609980[84] = 0;
   out_5222045031026609980[85] = dt;
   out_5222045031026609980[86] = 0;
   out_5222045031026609980[87] = 0;
   out_5222045031026609980[88] = 0;
   out_5222045031026609980[89] = 0;
   out_5222045031026609980[90] = 0;
   out_5222045031026609980[91] = 0;
   out_5222045031026609980[92] = 0;
   out_5222045031026609980[93] = 0;
   out_5222045031026609980[94] = 0;
   out_5222045031026609980[95] = 1;
   out_5222045031026609980[96] = 0;
   out_5222045031026609980[97] = 0;
   out_5222045031026609980[98] = 0;
   out_5222045031026609980[99] = 0;
   out_5222045031026609980[100] = 0;
   out_5222045031026609980[101] = 0;
   out_5222045031026609980[102] = 0;
   out_5222045031026609980[103] = 0;
   out_5222045031026609980[104] = dt;
   out_5222045031026609980[105] = 0;
   out_5222045031026609980[106] = 0;
   out_5222045031026609980[107] = 0;
   out_5222045031026609980[108] = 0;
   out_5222045031026609980[109] = 0;
   out_5222045031026609980[110] = 0;
   out_5222045031026609980[111] = 0;
   out_5222045031026609980[112] = 0;
   out_5222045031026609980[113] = 0;
   out_5222045031026609980[114] = 1;
   out_5222045031026609980[115] = 0;
   out_5222045031026609980[116] = 0;
   out_5222045031026609980[117] = 0;
   out_5222045031026609980[118] = 0;
   out_5222045031026609980[119] = 0;
   out_5222045031026609980[120] = 0;
   out_5222045031026609980[121] = 0;
   out_5222045031026609980[122] = 0;
   out_5222045031026609980[123] = 0;
   out_5222045031026609980[124] = 0;
   out_5222045031026609980[125] = 0;
   out_5222045031026609980[126] = 0;
   out_5222045031026609980[127] = 0;
   out_5222045031026609980[128] = 0;
   out_5222045031026609980[129] = 0;
   out_5222045031026609980[130] = 0;
   out_5222045031026609980[131] = 0;
   out_5222045031026609980[132] = 0;
   out_5222045031026609980[133] = 1;
   out_5222045031026609980[134] = 0;
   out_5222045031026609980[135] = 0;
   out_5222045031026609980[136] = 0;
   out_5222045031026609980[137] = 0;
   out_5222045031026609980[138] = 0;
   out_5222045031026609980[139] = 0;
   out_5222045031026609980[140] = 0;
   out_5222045031026609980[141] = 0;
   out_5222045031026609980[142] = 0;
   out_5222045031026609980[143] = 0;
   out_5222045031026609980[144] = 0;
   out_5222045031026609980[145] = 0;
   out_5222045031026609980[146] = 0;
   out_5222045031026609980[147] = 0;
   out_5222045031026609980[148] = 0;
   out_5222045031026609980[149] = 0;
   out_5222045031026609980[150] = 0;
   out_5222045031026609980[151] = 0;
   out_5222045031026609980[152] = 1;
   out_5222045031026609980[153] = 0;
   out_5222045031026609980[154] = 0;
   out_5222045031026609980[155] = 0;
   out_5222045031026609980[156] = 0;
   out_5222045031026609980[157] = 0;
   out_5222045031026609980[158] = 0;
   out_5222045031026609980[159] = 0;
   out_5222045031026609980[160] = 0;
   out_5222045031026609980[161] = 0;
   out_5222045031026609980[162] = 0;
   out_5222045031026609980[163] = 0;
   out_5222045031026609980[164] = 0;
   out_5222045031026609980[165] = 0;
   out_5222045031026609980[166] = 0;
   out_5222045031026609980[167] = 0;
   out_5222045031026609980[168] = 0;
   out_5222045031026609980[169] = 0;
   out_5222045031026609980[170] = 0;
   out_5222045031026609980[171] = 1;
   out_5222045031026609980[172] = 0;
   out_5222045031026609980[173] = 0;
   out_5222045031026609980[174] = 0;
   out_5222045031026609980[175] = 0;
   out_5222045031026609980[176] = 0;
   out_5222045031026609980[177] = 0;
   out_5222045031026609980[178] = 0;
   out_5222045031026609980[179] = 0;
   out_5222045031026609980[180] = 0;
   out_5222045031026609980[181] = 0;
   out_5222045031026609980[182] = 0;
   out_5222045031026609980[183] = 0;
   out_5222045031026609980[184] = 0;
   out_5222045031026609980[185] = 0;
   out_5222045031026609980[186] = 0;
   out_5222045031026609980[187] = 0;
   out_5222045031026609980[188] = 0;
   out_5222045031026609980[189] = 0;
   out_5222045031026609980[190] = 1;
   out_5222045031026609980[191] = 0;
   out_5222045031026609980[192] = 0;
   out_5222045031026609980[193] = 0;
   out_5222045031026609980[194] = 0;
   out_5222045031026609980[195] = 0;
   out_5222045031026609980[196] = 0;
   out_5222045031026609980[197] = 0;
   out_5222045031026609980[198] = 0;
   out_5222045031026609980[199] = 0;
   out_5222045031026609980[200] = 0;
   out_5222045031026609980[201] = 0;
   out_5222045031026609980[202] = 0;
   out_5222045031026609980[203] = 0;
   out_5222045031026609980[204] = 0;
   out_5222045031026609980[205] = 0;
   out_5222045031026609980[206] = 0;
   out_5222045031026609980[207] = 0;
   out_5222045031026609980[208] = 0;
   out_5222045031026609980[209] = 1;
   out_5222045031026609980[210] = 0;
   out_5222045031026609980[211] = 0;
   out_5222045031026609980[212] = 0;
   out_5222045031026609980[213] = 0;
   out_5222045031026609980[214] = 0;
   out_5222045031026609980[215] = 0;
   out_5222045031026609980[216] = 0;
   out_5222045031026609980[217] = 0;
   out_5222045031026609980[218] = 0;
   out_5222045031026609980[219] = 0;
   out_5222045031026609980[220] = 0;
   out_5222045031026609980[221] = 0;
   out_5222045031026609980[222] = 0;
   out_5222045031026609980[223] = 0;
   out_5222045031026609980[224] = 0;
   out_5222045031026609980[225] = 0;
   out_5222045031026609980[226] = 0;
   out_5222045031026609980[227] = 0;
   out_5222045031026609980[228] = 1;
   out_5222045031026609980[229] = 0;
   out_5222045031026609980[230] = 0;
   out_5222045031026609980[231] = 0;
   out_5222045031026609980[232] = 0;
   out_5222045031026609980[233] = 0;
   out_5222045031026609980[234] = 0;
   out_5222045031026609980[235] = 0;
   out_5222045031026609980[236] = 0;
   out_5222045031026609980[237] = 0;
   out_5222045031026609980[238] = 0;
   out_5222045031026609980[239] = 0;
   out_5222045031026609980[240] = 0;
   out_5222045031026609980[241] = 0;
   out_5222045031026609980[242] = 0;
   out_5222045031026609980[243] = 0;
   out_5222045031026609980[244] = 0;
   out_5222045031026609980[245] = 0;
   out_5222045031026609980[246] = 0;
   out_5222045031026609980[247] = 1;
   out_5222045031026609980[248] = 0;
   out_5222045031026609980[249] = 0;
   out_5222045031026609980[250] = 0;
   out_5222045031026609980[251] = 0;
   out_5222045031026609980[252] = 0;
   out_5222045031026609980[253] = 0;
   out_5222045031026609980[254] = 0;
   out_5222045031026609980[255] = 0;
   out_5222045031026609980[256] = 0;
   out_5222045031026609980[257] = 0;
   out_5222045031026609980[258] = 0;
   out_5222045031026609980[259] = 0;
   out_5222045031026609980[260] = 0;
   out_5222045031026609980[261] = 0;
   out_5222045031026609980[262] = 0;
   out_5222045031026609980[263] = 0;
   out_5222045031026609980[264] = 0;
   out_5222045031026609980[265] = 0;
   out_5222045031026609980[266] = 1;
   out_5222045031026609980[267] = 0;
   out_5222045031026609980[268] = 0;
   out_5222045031026609980[269] = 0;
   out_5222045031026609980[270] = 0;
   out_5222045031026609980[271] = 0;
   out_5222045031026609980[272] = 0;
   out_5222045031026609980[273] = 0;
   out_5222045031026609980[274] = 0;
   out_5222045031026609980[275] = 0;
   out_5222045031026609980[276] = 0;
   out_5222045031026609980[277] = 0;
   out_5222045031026609980[278] = 0;
   out_5222045031026609980[279] = 0;
   out_5222045031026609980[280] = 0;
   out_5222045031026609980[281] = 0;
   out_5222045031026609980[282] = 0;
   out_5222045031026609980[283] = 0;
   out_5222045031026609980[284] = 0;
   out_5222045031026609980[285] = 1;
   out_5222045031026609980[286] = 0;
   out_5222045031026609980[287] = 0;
   out_5222045031026609980[288] = 0;
   out_5222045031026609980[289] = 0;
   out_5222045031026609980[290] = 0;
   out_5222045031026609980[291] = 0;
   out_5222045031026609980[292] = 0;
   out_5222045031026609980[293] = 0;
   out_5222045031026609980[294] = 0;
   out_5222045031026609980[295] = 0;
   out_5222045031026609980[296] = 0;
   out_5222045031026609980[297] = 0;
   out_5222045031026609980[298] = 0;
   out_5222045031026609980[299] = 0;
   out_5222045031026609980[300] = 0;
   out_5222045031026609980[301] = 0;
   out_5222045031026609980[302] = 0;
   out_5222045031026609980[303] = 0;
   out_5222045031026609980[304] = 1;
   out_5222045031026609980[305] = 0;
   out_5222045031026609980[306] = 0;
   out_5222045031026609980[307] = 0;
   out_5222045031026609980[308] = 0;
   out_5222045031026609980[309] = 0;
   out_5222045031026609980[310] = 0;
   out_5222045031026609980[311] = 0;
   out_5222045031026609980[312] = 0;
   out_5222045031026609980[313] = 0;
   out_5222045031026609980[314] = 0;
   out_5222045031026609980[315] = 0;
   out_5222045031026609980[316] = 0;
   out_5222045031026609980[317] = 0;
   out_5222045031026609980[318] = 0;
   out_5222045031026609980[319] = 0;
   out_5222045031026609980[320] = 0;
   out_5222045031026609980[321] = 0;
   out_5222045031026609980[322] = 0;
   out_5222045031026609980[323] = 1;
}
void h_4(double *state, double *unused, double *out_9011768275853426182) {
   out_9011768275853426182[0] = state[6] + state[9];
   out_9011768275853426182[1] = state[7] + state[10];
   out_9011768275853426182[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3460336267317199431) {
   out_3460336267317199431[0] = 0;
   out_3460336267317199431[1] = 0;
   out_3460336267317199431[2] = 0;
   out_3460336267317199431[3] = 0;
   out_3460336267317199431[4] = 0;
   out_3460336267317199431[5] = 0;
   out_3460336267317199431[6] = 1;
   out_3460336267317199431[7] = 0;
   out_3460336267317199431[8] = 0;
   out_3460336267317199431[9] = 1;
   out_3460336267317199431[10] = 0;
   out_3460336267317199431[11] = 0;
   out_3460336267317199431[12] = 0;
   out_3460336267317199431[13] = 0;
   out_3460336267317199431[14] = 0;
   out_3460336267317199431[15] = 0;
   out_3460336267317199431[16] = 0;
   out_3460336267317199431[17] = 0;
   out_3460336267317199431[18] = 0;
   out_3460336267317199431[19] = 0;
   out_3460336267317199431[20] = 0;
   out_3460336267317199431[21] = 0;
   out_3460336267317199431[22] = 0;
   out_3460336267317199431[23] = 0;
   out_3460336267317199431[24] = 0;
   out_3460336267317199431[25] = 1;
   out_3460336267317199431[26] = 0;
   out_3460336267317199431[27] = 0;
   out_3460336267317199431[28] = 1;
   out_3460336267317199431[29] = 0;
   out_3460336267317199431[30] = 0;
   out_3460336267317199431[31] = 0;
   out_3460336267317199431[32] = 0;
   out_3460336267317199431[33] = 0;
   out_3460336267317199431[34] = 0;
   out_3460336267317199431[35] = 0;
   out_3460336267317199431[36] = 0;
   out_3460336267317199431[37] = 0;
   out_3460336267317199431[38] = 0;
   out_3460336267317199431[39] = 0;
   out_3460336267317199431[40] = 0;
   out_3460336267317199431[41] = 0;
   out_3460336267317199431[42] = 0;
   out_3460336267317199431[43] = 0;
   out_3460336267317199431[44] = 1;
   out_3460336267317199431[45] = 0;
   out_3460336267317199431[46] = 0;
   out_3460336267317199431[47] = 1;
   out_3460336267317199431[48] = 0;
   out_3460336267317199431[49] = 0;
   out_3460336267317199431[50] = 0;
   out_3460336267317199431[51] = 0;
   out_3460336267317199431[52] = 0;
   out_3460336267317199431[53] = 0;
}
void h_10(double *state, double *unused, double *out_678012550926290311) {
   out_678012550926290311[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_678012550926290311[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_678012550926290311[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_4795577018961183743) {
   out_4795577018961183743[0] = 0;
   out_4795577018961183743[1] = 9.8100000000000005*cos(state[1]);
   out_4795577018961183743[2] = 0;
   out_4795577018961183743[3] = 0;
   out_4795577018961183743[4] = -state[8];
   out_4795577018961183743[5] = state[7];
   out_4795577018961183743[6] = 0;
   out_4795577018961183743[7] = state[5];
   out_4795577018961183743[8] = -state[4];
   out_4795577018961183743[9] = 0;
   out_4795577018961183743[10] = 0;
   out_4795577018961183743[11] = 0;
   out_4795577018961183743[12] = 1;
   out_4795577018961183743[13] = 0;
   out_4795577018961183743[14] = 0;
   out_4795577018961183743[15] = 1;
   out_4795577018961183743[16] = 0;
   out_4795577018961183743[17] = 0;
   out_4795577018961183743[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_4795577018961183743[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_4795577018961183743[20] = 0;
   out_4795577018961183743[21] = state[8];
   out_4795577018961183743[22] = 0;
   out_4795577018961183743[23] = -state[6];
   out_4795577018961183743[24] = -state[5];
   out_4795577018961183743[25] = 0;
   out_4795577018961183743[26] = state[3];
   out_4795577018961183743[27] = 0;
   out_4795577018961183743[28] = 0;
   out_4795577018961183743[29] = 0;
   out_4795577018961183743[30] = 0;
   out_4795577018961183743[31] = 1;
   out_4795577018961183743[32] = 0;
   out_4795577018961183743[33] = 0;
   out_4795577018961183743[34] = 1;
   out_4795577018961183743[35] = 0;
   out_4795577018961183743[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_4795577018961183743[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_4795577018961183743[38] = 0;
   out_4795577018961183743[39] = -state[7];
   out_4795577018961183743[40] = state[6];
   out_4795577018961183743[41] = 0;
   out_4795577018961183743[42] = state[4];
   out_4795577018961183743[43] = -state[3];
   out_4795577018961183743[44] = 0;
   out_4795577018961183743[45] = 0;
   out_4795577018961183743[46] = 0;
   out_4795577018961183743[47] = 0;
   out_4795577018961183743[48] = 0;
   out_4795577018961183743[49] = 0;
   out_4795577018961183743[50] = 1;
   out_4795577018961183743[51] = 0;
   out_4795577018961183743[52] = 0;
   out_4795577018961183743[53] = 1;
}
void h_13(double *state, double *unused, double *out_7050071971782529116) {
   out_7050071971782529116[0] = state[3];
   out_7050071971782529116[1] = state[4];
   out_7050071971782529116[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6672610092649532232) {
   out_6672610092649532232[0] = 0;
   out_6672610092649532232[1] = 0;
   out_6672610092649532232[2] = 0;
   out_6672610092649532232[3] = 1;
   out_6672610092649532232[4] = 0;
   out_6672610092649532232[5] = 0;
   out_6672610092649532232[6] = 0;
   out_6672610092649532232[7] = 0;
   out_6672610092649532232[8] = 0;
   out_6672610092649532232[9] = 0;
   out_6672610092649532232[10] = 0;
   out_6672610092649532232[11] = 0;
   out_6672610092649532232[12] = 0;
   out_6672610092649532232[13] = 0;
   out_6672610092649532232[14] = 0;
   out_6672610092649532232[15] = 0;
   out_6672610092649532232[16] = 0;
   out_6672610092649532232[17] = 0;
   out_6672610092649532232[18] = 0;
   out_6672610092649532232[19] = 0;
   out_6672610092649532232[20] = 0;
   out_6672610092649532232[21] = 0;
   out_6672610092649532232[22] = 1;
   out_6672610092649532232[23] = 0;
   out_6672610092649532232[24] = 0;
   out_6672610092649532232[25] = 0;
   out_6672610092649532232[26] = 0;
   out_6672610092649532232[27] = 0;
   out_6672610092649532232[28] = 0;
   out_6672610092649532232[29] = 0;
   out_6672610092649532232[30] = 0;
   out_6672610092649532232[31] = 0;
   out_6672610092649532232[32] = 0;
   out_6672610092649532232[33] = 0;
   out_6672610092649532232[34] = 0;
   out_6672610092649532232[35] = 0;
   out_6672610092649532232[36] = 0;
   out_6672610092649532232[37] = 0;
   out_6672610092649532232[38] = 0;
   out_6672610092649532232[39] = 0;
   out_6672610092649532232[40] = 0;
   out_6672610092649532232[41] = 1;
   out_6672610092649532232[42] = 0;
   out_6672610092649532232[43] = 0;
   out_6672610092649532232[44] = 0;
   out_6672610092649532232[45] = 0;
   out_6672610092649532232[46] = 0;
   out_6672610092649532232[47] = 0;
   out_6672610092649532232[48] = 0;
   out_6672610092649532232[49] = 0;
   out_6672610092649532232[50] = 0;
   out_6672610092649532232[51] = 0;
   out_6672610092649532232[52] = 0;
   out_6672610092649532232[53] = 0;
}
void h_14(double *state, double *unused, double *out_2771996280971910329) {
   out_2771996280971910329[0] = state[6];
   out_2771996280971910329[1] = state[7];
   out_2771996280971910329[2] = state[8];
}
void H_14(double *state, double *unused, double *out_7423577123656683960) {
   out_7423577123656683960[0] = 0;
   out_7423577123656683960[1] = 0;
   out_7423577123656683960[2] = 0;
   out_7423577123656683960[3] = 0;
   out_7423577123656683960[4] = 0;
   out_7423577123656683960[5] = 0;
   out_7423577123656683960[6] = 1;
   out_7423577123656683960[7] = 0;
   out_7423577123656683960[8] = 0;
   out_7423577123656683960[9] = 0;
   out_7423577123656683960[10] = 0;
   out_7423577123656683960[11] = 0;
   out_7423577123656683960[12] = 0;
   out_7423577123656683960[13] = 0;
   out_7423577123656683960[14] = 0;
   out_7423577123656683960[15] = 0;
   out_7423577123656683960[16] = 0;
   out_7423577123656683960[17] = 0;
   out_7423577123656683960[18] = 0;
   out_7423577123656683960[19] = 0;
   out_7423577123656683960[20] = 0;
   out_7423577123656683960[21] = 0;
   out_7423577123656683960[22] = 0;
   out_7423577123656683960[23] = 0;
   out_7423577123656683960[24] = 0;
   out_7423577123656683960[25] = 1;
   out_7423577123656683960[26] = 0;
   out_7423577123656683960[27] = 0;
   out_7423577123656683960[28] = 0;
   out_7423577123656683960[29] = 0;
   out_7423577123656683960[30] = 0;
   out_7423577123656683960[31] = 0;
   out_7423577123656683960[32] = 0;
   out_7423577123656683960[33] = 0;
   out_7423577123656683960[34] = 0;
   out_7423577123656683960[35] = 0;
   out_7423577123656683960[36] = 0;
   out_7423577123656683960[37] = 0;
   out_7423577123656683960[38] = 0;
   out_7423577123656683960[39] = 0;
   out_7423577123656683960[40] = 0;
   out_7423577123656683960[41] = 0;
   out_7423577123656683960[42] = 0;
   out_7423577123656683960[43] = 0;
   out_7423577123656683960[44] = 1;
   out_7423577123656683960[45] = 0;
   out_7423577123656683960[46] = 0;
   out_7423577123656683960[47] = 0;
   out_7423577123656683960[48] = 0;
   out_7423577123656683960[49] = 0;
   out_7423577123656683960[50] = 0;
   out_7423577123656683960[51] = 0;
   out_7423577123656683960[52] = 0;
   out_7423577123656683960[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_2276930388742637984) {
  err_fun(nom_x, delta_x, out_2276930388742637984);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5553036191683273841) {
  inv_err_fun(nom_x, true_x, out_5553036191683273841);
}
void pose_H_mod_fun(double *state, double *out_9138325999640393464) {
  H_mod_fun(state, out_9138325999640393464);
}
void pose_f_fun(double *state, double dt, double *out_1147502803036589913) {
  f_fun(state,  dt, out_1147502803036589913);
}
void pose_F_fun(double *state, double dt, double *out_5222045031026609980) {
  F_fun(state,  dt, out_5222045031026609980);
}
void pose_h_4(double *state, double *unused, double *out_9011768275853426182) {
  h_4(state, unused, out_9011768275853426182);
}
void pose_H_4(double *state, double *unused, double *out_3460336267317199431) {
  H_4(state, unused, out_3460336267317199431);
}
void pose_h_10(double *state, double *unused, double *out_678012550926290311) {
  h_10(state, unused, out_678012550926290311);
}
void pose_H_10(double *state, double *unused, double *out_4795577018961183743) {
  H_10(state, unused, out_4795577018961183743);
}
void pose_h_13(double *state, double *unused, double *out_7050071971782529116) {
  h_13(state, unused, out_7050071971782529116);
}
void pose_H_13(double *state, double *unused, double *out_6672610092649532232) {
  H_13(state, unused, out_6672610092649532232);
}
void pose_h_14(double *state, double *unused, double *out_2771996280971910329) {
  h_14(state, unused, out_2771996280971910329);
}
void pose_H_14(double *state, double *unused, double *out_7423577123656683960) {
  H_14(state, unused, out_7423577123656683960);
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
