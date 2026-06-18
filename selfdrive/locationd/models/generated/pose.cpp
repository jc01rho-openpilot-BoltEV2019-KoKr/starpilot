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
void err_fun(double *nom_x, double *delta_x, double *out_3316982698909296372) {
   out_3316982698909296372[0] = delta_x[0] + nom_x[0];
   out_3316982698909296372[1] = delta_x[1] + nom_x[1];
   out_3316982698909296372[2] = delta_x[2] + nom_x[2];
   out_3316982698909296372[3] = delta_x[3] + nom_x[3];
   out_3316982698909296372[4] = delta_x[4] + nom_x[4];
   out_3316982698909296372[5] = delta_x[5] + nom_x[5];
   out_3316982698909296372[6] = delta_x[6] + nom_x[6];
   out_3316982698909296372[7] = delta_x[7] + nom_x[7];
   out_3316982698909296372[8] = delta_x[8] + nom_x[8];
   out_3316982698909296372[9] = delta_x[9] + nom_x[9];
   out_3316982698909296372[10] = delta_x[10] + nom_x[10];
   out_3316982698909296372[11] = delta_x[11] + nom_x[11];
   out_3316982698909296372[12] = delta_x[12] + nom_x[12];
   out_3316982698909296372[13] = delta_x[13] + nom_x[13];
   out_3316982698909296372[14] = delta_x[14] + nom_x[14];
   out_3316982698909296372[15] = delta_x[15] + nom_x[15];
   out_3316982698909296372[16] = delta_x[16] + nom_x[16];
   out_3316982698909296372[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_875278244398304479) {
   out_875278244398304479[0] = -nom_x[0] + true_x[0];
   out_875278244398304479[1] = -nom_x[1] + true_x[1];
   out_875278244398304479[2] = -nom_x[2] + true_x[2];
   out_875278244398304479[3] = -nom_x[3] + true_x[3];
   out_875278244398304479[4] = -nom_x[4] + true_x[4];
   out_875278244398304479[5] = -nom_x[5] + true_x[5];
   out_875278244398304479[6] = -nom_x[6] + true_x[6];
   out_875278244398304479[7] = -nom_x[7] + true_x[7];
   out_875278244398304479[8] = -nom_x[8] + true_x[8];
   out_875278244398304479[9] = -nom_x[9] + true_x[9];
   out_875278244398304479[10] = -nom_x[10] + true_x[10];
   out_875278244398304479[11] = -nom_x[11] + true_x[11];
   out_875278244398304479[12] = -nom_x[12] + true_x[12];
   out_875278244398304479[13] = -nom_x[13] + true_x[13];
   out_875278244398304479[14] = -nom_x[14] + true_x[14];
   out_875278244398304479[15] = -nom_x[15] + true_x[15];
   out_875278244398304479[16] = -nom_x[16] + true_x[16];
   out_875278244398304479[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4269788700262626124) {
   out_4269788700262626124[0] = 1.0;
   out_4269788700262626124[1] = 0.0;
   out_4269788700262626124[2] = 0.0;
   out_4269788700262626124[3] = 0.0;
   out_4269788700262626124[4] = 0.0;
   out_4269788700262626124[5] = 0.0;
   out_4269788700262626124[6] = 0.0;
   out_4269788700262626124[7] = 0.0;
   out_4269788700262626124[8] = 0.0;
   out_4269788700262626124[9] = 0.0;
   out_4269788700262626124[10] = 0.0;
   out_4269788700262626124[11] = 0.0;
   out_4269788700262626124[12] = 0.0;
   out_4269788700262626124[13] = 0.0;
   out_4269788700262626124[14] = 0.0;
   out_4269788700262626124[15] = 0.0;
   out_4269788700262626124[16] = 0.0;
   out_4269788700262626124[17] = 0.0;
   out_4269788700262626124[18] = 0.0;
   out_4269788700262626124[19] = 1.0;
   out_4269788700262626124[20] = 0.0;
   out_4269788700262626124[21] = 0.0;
   out_4269788700262626124[22] = 0.0;
   out_4269788700262626124[23] = 0.0;
   out_4269788700262626124[24] = 0.0;
   out_4269788700262626124[25] = 0.0;
   out_4269788700262626124[26] = 0.0;
   out_4269788700262626124[27] = 0.0;
   out_4269788700262626124[28] = 0.0;
   out_4269788700262626124[29] = 0.0;
   out_4269788700262626124[30] = 0.0;
   out_4269788700262626124[31] = 0.0;
   out_4269788700262626124[32] = 0.0;
   out_4269788700262626124[33] = 0.0;
   out_4269788700262626124[34] = 0.0;
   out_4269788700262626124[35] = 0.0;
   out_4269788700262626124[36] = 0.0;
   out_4269788700262626124[37] = 0.0;
   out_4269788700262626124[38] = 1.0;
   out_4269788700262626124[39] = 0.0;
   out_4269788700262626124[40] = 0.0;
   out_4269788700262626124[41] = 0.0;
   out_4269788700262626124[42] = 0.0;
   out_4269788700262626124[43] = 0.0;
   out_4269788700262626124[44] = 0.0;
   out_4269788700262626124[45] = 0.0;
   out_4269788700262626124[46] = 0.0;
   out_4269788700262626124[47] = 0.0;
   out_4269788700262626124[48] = 0.0;
   out_4269788700262626124[49] = 0.0;
   out_4269788700262626124[50] = 0.0;
   out_4269788700262626124[51] = 0.0;
   out_4269788700262626124[52] = 0.0;
   out_4269788700262626124[53] = 0.0;
   out_4269788700262626124[54] = 0.0;
   out_4269788700262626124[55] = 0.0;
   out_4269788700262626124[56] = 0.0;
   out_4269788700262626124[57] = 1.0;
   out_4269788700262626124[58] = 0.0;
   out_4269788700262626124[59] = 0.0;
   out_4269788700262626124[60] = 0.0;
   out_4269788700262626124[61] = 0.0;
   out_4269788700262626124[62] = 0.0;
   out_4269788700262626124[63] = 0.0;
   out_4269788700262626124[64] = 0.0;
   out_4269788700262626124[65] = 0.0;
   out_4269788700262626124[66] = 0.0;
   out_4269788700262626124[67] = 0.0;
   out_4269788700262626124[68] = 0.0;
   out_4269788700262626124[69] = 0.0;
   out_4269788700262626124[70] = 0.0;
   out_4269788700262626124[71] = 0.0;
   out_4269788700262626124[72] = 0.0;
   out_4269788700262626124[73] = 0.0;
   out_4269788700262626124[74] = 0.0;
   out_4269788700262626124[75] = 0.0;
   out_4269788700262626124[76] = 1.0;
   out_4269788700262626124[77] = 0.0;
   out_4269788700262626124[78] = 0.0;
   out_4269788700262626124[79] = 0.0;
   out_4269788700262626124[80] = 0.0;
   out_4269788700262626124[81] = 0.0;
   out_4269788700262626124[82] = 0.0;
   out_4269788700262626124[83] = 0.0;
   out_4269788700262626124[84] = 0.0;
   out_4269788700262626124[85] = 0.0;
   out_4269788700262626124[86] = 0.0;
   out_4269788700262626124[87] = 0.0;
   out_4269788700262626124[88] = 0.0;
   out_4269788700262626124[89] = 0.0;
   out_4269788700262626124[90] = 0.0;
   out_4269788700262626124[91] = 0.0;
   out_4269788700262626124[92] = 0.0;
   out_4269788700262626124[93] = 0.0;
   out_4269788700262626124[94] = 0.0;
   out_4269788700262626124[95] = 1.0;
   out_4269788700262626124[96] = 0.0;
   out_4269788700262626124[97] = 0.0;
   out_4269788700262626124[98] = 0.0;
   out_4269788700262626124[99] = 0.0;
   out_4269788700262626124[100] = 0.0;
   out_4269788700262626124[101] = 0.0;
   out_4269788700262626124[102] = 0.0;
   out_4269788700262626124[103] = 0.0;
   out_4269788700262626124[104] = 0.0;
   out_4269788700262626124[105] = 0.0;
   out_4269788700262626124[106] = 0.0;
   out_4269788700262626124[107] = 0.0;
   out_4269788700262626124[108] = 0.0;
   out_4269788700262626124[109] = 0.0;
   out_4269788700262626124[110] = 0.0;
   out_4269788700262626124[111] = 0.0;
   out_4269788700262626124[112] = 0.0;
   out_4269788700262626124[113] = 0.0;
   out_4269788700262626124[114] = 1.0;
   out_4269788700262626124[115] = 0.0;
   out_4269788700262626124[116] = 0.0;
   out_4269788700262626124[117] = 0.0;
   out_4269788700262626124[118] = 0.0;
   out_4269788700262626124[119] = 0.0;
   out_4269788700262626124[120] = 0.0;
   out_4269788700262626124[121] = 0.0;
   out_4269788700262626124[122] = 0.0;
   out_4269788700262626124[123] = 0.0;
   out_4269788700262626124[124] = 0.0;
   out_4269788700262626124[125] = 0.0;
   out_4269788700262626124[126] = 0.0;
   out_4269788700262626124[127] = 0.0;
   out_4269788700262626124[128] = 0.0;
   out_4269788700262626124[129] = 0.0;
   out_4269788700262626124[130] = 0.0;
   out_4269788700262626124[131] = 0.0;
   out_4269788700262626124[132] = 0.0;
   out_4269788700262626124[133] = 1.0;
   out_4269788700262626124[134] = 0.0;
   out_4269788700262626124[135] = 0.0;
   out_4269788700262626124[136] = 0.0;
   out_4269788700262626124[137] = 0.0;
   out_4269788700262626124[138] = 0.0;
   out_4269788700262626124[139] = 0.0;
   out_4269788700262626124[140] = 0.0;
   out_4269788700262626124[141] = 0.0;
   out_4269788700262626124[142] = 0.0;
   out_4269788700262626124[143] = 0.0;
   out_4269788700262626124[144] = 0.0;
   out_4269788700262626124[145] = 0.0;
   out_4269788700262626124[146] = 0.0;
   out_4269788700262626124[147] = 0.0;
   out_4269788700262626124[148] = 0.0;
   out_4269788700262626124[149] = 0.0;
   out_4269788700262626124[150] = 0.0;
   out_4269788700262626124[151] = 0.0;
   out_4269788700262626124[152] = 1.0;
   out_4269788700262626124[153] = 0.0;
   out_4269788700262626124[154] = 0.0;
   out_4269788700262626124[155] = 0.0;
   out_4269788700262626124[156] = 0.0;
   out_4269788700262626124[157] = 0.0;
   out_4269788700262626124[158] = 0.0;
   out_4269788700262626124[159] = 0.0;
   out_4269788700262626124[160] = 0.0;
   out_4269788700262626124[161] = 0.0;
   out_4269788700262626124[162] = 0.0;
   out_4269788700262626124[163] = 0.0;
   out_4269788700262626124[164] = 0.0;
   out_4269788700262626124[165] = 0.0;
   out_4269788700262626124[166] = 0.0;
   out_4269788700262626124[167] = 0.0;
   out_4269788700262626124[168] = 0.0;
   out_4269788700262626124[169] = 0.0;
   out_4269788700262626124[170] = 0.0;
   out_4269788700262626124[171] = 1.0;
   out_4269788700262626124[172] = 0.0;
   out_4269788700262626124[173] = 0.0;
   out_4269788700262626124[174] = 0.0;
   out_4269788700262626124[175] = 0.0;
   out_4269788700262626124[176] = 0.0;
   out_4269788700262626124[177] = 0.0;
   out_4269788700262626124[178] = 0.0;
   out_4269788700262626124[179] = 0.0;
   out_4269788700262626124[180] = 0.0;
   out_4269788700262626124[181] = 0.0;
   out_4269788700262626124[182] = 0.0;
   out_4269788700262626124[183] = 0.0;
   out_4269788700262626124[184] = 0.0;
   out_4269788700262626124[185] = 0.0;
   out_4269788700262626124[186] = 0.0;
   out_4269788700262626124[187] = 0.0;
   out_4269788700262626124[188] = 0.0;
   out_4269788700262626124[189] = 0.0;
   out_4269788700262626124[190] = 1.0;
   out_4269788700262626124[191] = 0.0;
   out_4269788700262626124[192] = 0.0;
   out_4269788700262626124[193] = 0.0;
   out_4269788700262626124[194] = 0.0;
   out_4269788700262626124[195] = 0.0;
   out_4269788700262626124[196] = 0.0;
   out_4269788700262626124[197] = 0.0;
   out_4269788700262626124[198] = 0.0;
   out_4269788700262626124[199] = 0.0;
   out_4269788700262626124[200] = 0.0;
   out_4269788700262626124[201] = 0.0;
   out_4269788700262626124[202] = 0.0;
   out_4269788700262626124[203] = 0.0;
   out_4269788700262626124[204] = 0.0;
   out_4269788700262626124[205] = 0.0;
   out_4269788700262626124[206] = 0.0;
   out_4269788700262626124[207] = 0.0;
   out_4269788700262626124[208] = 0.0;
   out_4269788700262626124[209] = 1.0;
   out_4269788700262626124[210] = 0.0;
   out_4269788700262626124[211] = 0.0;
   out_4269788700262626124[212] = 0.0;
   out_4269788700262626124[213] = 0.0;
   out_4269788700262626124[214] = 0.0;
   out_4269788700262626124[215] = 0.0;
   out_4269788700262626124[216] = 0.0;
   out_4269788700262626124[217] = 0.0;
   out_4269788700262626124[218] = 0.0;
   out_4269788700262626124[219] = 0.0;
   out_4269788700262626124[220] = 0.0;
   out_4269788700262626124[221] = 0.0;
   out_4269788700262626124[222] = 0.0;
   out_4269788700262626124[223] = 0.0;
   out_4269788700262626124[224] = 0.0;
   out_4269788700262626124[225] = 0.0;
   out_4269788700262626124[226] = 0.0;
   out_4269788700262626124[227] = 0.0;
   out_4269788700262626124[228] = 1.0;
   out_4269788700262626124[229] = 0.0;
   out_4269788700262626124[230] = 0.0;
   out_4269788700262626124[231] = 0.0;
   out_4269788700262626124[232] = 0.0;
   out_4269788700262626124[233] = 0.0;
   out_4269788700262626124[234] = 0.0;
   out_4269788700262626124[235] = 0.0;
   out_4269788700262626124[236] = 0.0;
   out_4269788700262626124[237] = 0.0;
   out_4269788700262626124[238] = 0.0;
   out_4269788700262626124[239] = 0.0;
   out_4269788700262626124[240] = 0.0;
   out_4269788700262626124[241] = 0.0;
   out_4269788700262626124[242] = 0.0;
   out_4269788700262626124[243] = 0.0;
   out_4269788700262626124[244] = 0.0;
   out_4269788700262626124[245] = 0.0;
   out_4269788700262626124[246] = 0.0;
   out_4269788700262626124[247] = 1.0;
   out_4269788700262626124[248] = 0.0;
   out_4269788700262626124[249] = 0.0;
   out_4269788700262626124[250] = 0.0;
   out_4269788700262626124[251] = 0.0;
   out_4269788700262626124[252] = 0.0;
   out_4269788700262626124[253] = 0.0;
   out_4269788700262626124[254] = 0.0;
   out_4269788700262626124[255] = 0.0;
   out_4269788700262626124[256] = 0.0;
   out_4269788700262626124[257] = 0.0;
   out_4269788700262626124[258] = 0.0;
   out_4269788700262626124[259] = 0.0;
   out_4269788700262626124[260] = 0.0;
   out_4269788700262626124[261] = 0.0;
   out_4269788700262626124[262] = 0.0;
   out_4269788700262626124[263] = 0.0;
   out_4269788700262626124[264] = 0.0;
   out_4269788700262626124[265] = 0.0;
   out_4269788700262626124[266] = 1.0;
   out_4269788700262626124[267] = 0.0;
   out_4269788700262626124[268] = 0.0;
   out_4269788700262626124[269] = 0.0;
   out_4269788700262626124[270] = 0.0;
   out_4269788700262626124[271] = 0.0;
   out_4269788700262626124[272] = 0.0;
   out_4269788700262626124[273] = 0.0;
   out_4269788700262626124[274] = 0.0;
   out_4269788700262626124[275] = 0.0;
   out_4269788700262626124[276] = 0.0;
   out_4269788700262626124[277] = 0.0;
   out_4269788700262626124[278] = 0.0;
   out_4269788700262626124[279] = 0.0;
   out_4269788700262626124[280] = 0.0;
   out_4269788700262626124[281] = 0.0;
   out_4269788700262626124[282] = 0.0;
   out_4269788700262626124[283] = 0.0;
   out_4269788700262626124[284] = 0.0;
   out_4269788700262626124[285] = 1.0;
   out_4269788700262626124[286] = 0.0;
   out_4269788700262626124[287] = 0.0;
   out_4269788700262626124[288] = 0.0;
   out_4269788700262626124[289] = 0.0;
   out_4269788700262626124[290] = 0.0;
   out_4269788700262626124[291] = 0.0;
   out_4269788700262626124[292] = 0.0;
   out_4269788700262626124[293] = 0.0;
   out_4269788700262626124[294] = 0.0;
   out_4269788700262626124[295] = 0.0;
   out_4269788700262626124[296] = 0.0;
   out_4269788700262626124[297] = 0.0;
   out_4269788700262626124[298] = 0.0;
   out_4269788700262626124[299] = 0.0;
   out_4269788700262626124[300] = 0.0;
   out_4269788700262626124[301] = 0.0;
   out_4269788700262626124[302] = 0.0;
   out_4269788700262626124[303] = 0.0;
   out_4269788700262626124[304] = 1.0;
   out_4269788700262626124[305] = 0.0;
   out_4269788700262626124[306] = 0.0;
   out_4269788700262626124[307] = 0.0;
   out_4269788700262626124[308] = 0.0;
   out_4269788700262626124[309] = 0.0;
   out_4269788700262626124[310] = 0.0;
   out_4269788700262626124[311] = 0.0;
   out_4269788700262626124[312] = 0.0;
   out_4269788700262626124[313] = 0.0;
   out_4269788700262626124[314] = 0.0;
   out_4269788700262626124[315] = 0.0;
   out_4269788700262626124[316] = 0.0;
   out_4269788700262626124[317] = 0.0;
   out_4269788700262626124[318] = 0.0;
   out_4269788700262626124[319] = 0.0;
   out_4269788700262626124[320] = 0.0;
   out_4269788700262626124[321] = 0.0;
   out_4269788700262626124[322] = 0.0;
   out_4269788700262626124[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_3692668602312034618) {
   out_3692668602312034618[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_3692668602312034618[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_3692668602312034618[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_3692668602312034618[3] = dt*state[12] + state[3];
   out_3692668602312034618[4] = dt*state[13] + state[4];
   out_3692668602312034618[5] = dt*state[14] + state[5];
   out_3692668602312034618[6] = state[6];
   out_3692668602312034618[7] = state[7];
   out_3692668602312034618[8] = state[8];
   out_3692668602312034618[9] = state[9];
   out_3692668602312034618[10] = state[10];
   out_3692668602312034618[11] = state[11];
   out_3692668602312034618[12] = state[12];
   out_3692668602312034618[13] = state[13];
   out_3692668602312034618[14] = state[14];
   out_3692668602312034618[15] = state[15];
   out_3692668602312034618[16] = state[16];
   out_3692668602312034618[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2955282305521857746) {
   out_2955282305521857746[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2955282305521857746[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2955282305521857746[2] = 0;
   out_2955282305521857746[3] = 0;
   out_2955282305521857746[4] = 0;
   out_2955282305521857746[5] = 0;
   out_2955282305521857746[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2955282305521857746[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2955282305521857746[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2955282305521857746[9] = 0;
   out_2955282305521857746[10] = 0;
   out_2955282305521857746[11] = 0;
   out_2955282305521857746[12] = 0;
   out_2955282305521857746[13] = 0;
   out_2955282305521857746[14] = 0;
   out_2955282305521857746[15] = 0;
   out_2955282305521857746[16] = 0;
   out_2955282305521857746[17] = 0;
   out_2955282305521857746[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2955282305521857746[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2955282305521857746[20] = 0;
   out_2955282305521857746[21] = 0;
   out_2955282305521857746[22] = 0;
   out_2955282305521857746[23] = 0;
   out_2955282305521857746[24] = 0;
   out_2955282305521857746[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2955282305521857746[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2955282305521857746[27] = 0;
   out_2955282305521857746[28] = 0;
   out_2955282305521857746[29] = 0;
   out_2955282305521857746[30] = 0;
   out_2955282305521857746[31] = 0;
   out_2955282305521857746[32] = 0;
   out_2955282305521857746[33] = 0;
   out_2955282305521857746[34] = 0;
   out_2955282305521857746[35] = 0;
   out_2955282305521857746[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2955282305521857746[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2955282305521857746[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2955282305521857746[39] = 0;
   out_2955282305521857746[40] = 0;
   out_2955282305521857746[41] = 0;
   out_2955282305521857746[42] = 0;
   out_2955282305521857746[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2955282305521857746[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2955282305521857746[45] = 0;
   out_2955282305521857746[46] = 0;
   out_2955282305521857746[47] = 0;
   out_2955282305521857746[48] = 0;
   out_2955282305521857746[49] = 0;
   out_2955282305521857746[50] = 0;
   out_2955282305521857746[51] = 0;
   out_2955282305521857746[52] = 0;
   out_2955282305521857746[53] = 0;
   out_2955282305521857746[54] = 0;
   out_2955282305521857746[55] = 0;
   out_2955282305521857746[56] = 0;
   out_2955282305521857746[57] = 1;
   out_2955282305521857746[58] = 0;
   out_2955282305521857746[59] = 0;
   out_2955282305521857746[60] = 0;
   out_2955282305521857746[61] = 0;
   out_2955282305521857746[62] = 0;
   out_2955282305521857746[63] = 0;
   out_2955282305521857746[64] = 0;
   out_2955282305521857746[65] = 0;
   out_2955282305521857746[66] = dt;
   out_2955282305521857746[67] = 0;
   out_2955282305521857746[68] = 0;
   out_2955282305521857746[69] = 0;
   out_2955282305521857746[70] = 0;
   out_2955282305521857746[71] = 0;
   out_2955282305521857746[72] = 0;
   out_2955282305521857746[73] = 0;
   out_2955282305521857746[74] = 0;
   out_2955282305521857746[75] = 0;
   out_2955282305521857746[76] = 1;
   out_2955282305521857746[77] = 0;
   out_2955282305521857746[78] = 0;
   out_2955282305521857746[79] = 0;
   out_2955282305521857746[80] = 0;
   out_2955282305521857746[81] = 0;
   out_2955282305521857746[82] = 0;
   out_2955282305521857746[83] = 0;
   out_2955282305521857746[84] = 0;
   out_2955282305521857746[85] = dt;
   out_2955282305521857746[86] = 0;
   out_2955282305521857746[87] = 0;
   out_2955282305521857746[88] = 0;
   out_2955282305521857746[89] = 0;
   out_2955282305521857746[90] = 0;
   out_2955282305521857746[91] = 0;
   out_2955282305521857746[92] = 0;
   out_2955282305521857746[93] = 0;
   out_2955282305521857746[94] = 0;
   out_2955282305521857746[95] = 1;
   out_2955282305521857746[96] = 0;
   out_2955282305521857746[97] = 0;
   out_2955282305521857746[98] = 0;
   out_2955282305521857746[99] = 0;
   out_2955282305521857746[100] = 0;
   out_2955282305521857746[101] = 0;
   out_2955282305521857746[102] = 0;
   out_2955282305521857746[103] = 0;
   out_2955282305521857746[104] = dt;
   out_2955282305521857746[105] = 0;
   out_2955282305521857746[106] = 0;
   out_2955282305521857746[107] = 0;
   out_2955282305521857746[108] = 0;
   out_2955282305521857746[109] = 0;
   out_2955282305521857746[110] = 0;
   out_2955282305521857746[111] = 0;
   out_2955282305521857746[112] = 0;
   out_2955282305521857746[113] = 0;
   out_2955282305521857746[114] = 1;
   out_2955282305521857746[115] = 0;
   out_2955282305521857746[116] = 0;
   out_2955282305521857746[117] = 0;
   out_2955282305521857746[118] = 0;
   out_2955282305521857746[119] = 0;
   out_2955282305521857746[120] = 0;
   out_2955282305521857746[121] = 0;
   out_2955282305521857746[122] = 0;
   out_2955282305521857746[123] = 0;
   out_2955282305521857746[124] = 0;
   out_2955282305521857746[125] = 0;
   out_2955282305521857746[126] = 0;
   out_2955282305521857746[127] = 0;
   out_2955282305521857746[128] = 0;
   out_2955282305521857746[129] = 0;
   out_2955282305521857746[130] = 0;
   out_2955282305521857746[131] = 0;
   out_2955282305521857746[132] = 0;
   out_2955282305521857746[133] = 1;
   out_2955282305521857746[134] = 0;
   out_2955282305521857746[135] = 0;
   out_2955282305521857746[136] = 0;
   out_2955282305521857746[137] = 0;
   out_2955282305521857746[138] = 0;
   out_2955282305521857746[139] = 0;
   out_2955282305521857746[140] = 0;
   out_2955282305521857746[141] = 0;
   out_2955282305521857746[142] = 0;
   out_2955282305521857746[143] = 0;
   out_2955282305521857746[144] = 0;
   out_2955282305521857746[145] = 0;
   out_2955282305521857746[146] = 0;
   out_2955282305521857746[147] = 0;
   out_2955282305521857746[148] = 0;
   out_2955282305521857746[149] = 0;
   out_2955282305521857746[150] = 0;
   out_2955282305521857746[151] = 0;
   out_2955282305521857746[152] = 1;
   out_2955282305521857746[153] = 0;
   out_2955282305521857746[154] = 0;
   out_2955282305521857746[155] = 0;
   out_2955282305521857746[156] = 0;
   out_2955282305521857746[157] = 0;
   out_2955282305521857746[158] = 0;
   out_2955282305521857746[159] = 0;
   out_2955282305521857746[160] = 0;
   out_2955282305521857746[161] = 0;
   out_2955282305521857746[162] = 0;
   out_2955282305521857746[163] = 0;
   out_2955282305521857746[164] = 0;
   out_2955282305521857746[165] = 0;
   out_2955282305521857746[166] = 0;
   out_2955282305521857746[167] = 0;
   out_2955282305521857746[168] = 0;
   out_2955282305521857746[169] = 0;
   out_2955282305521857746[170] = 0;
   out_2955282305521857746[171] = 1;
   out_2955282305521857746[172] = 0;
   out_2955282305521857746[173] = 0;
   out_2955282305521857746[174] = 0;
   out_2955282305521857746[175] = 0;
   out_2955282305521857746[176] = 0;
   out_2955282305521857746[177] = 0;
   out_2955282305521857746[178] = 0;
   out_2955282305521857746[179] = 0;
   out_2955282305521857746[180] = 0;
   out_2955282305521857746[181] = 0;
   out_2955282305521857746[182] = 0;
   out_2955282305521857746[183] = 0;
   out_2955282305521857746[184] = 0;
   out_2955282305521857746[185] = 0;
   out_2955282305521857746[186] = 0;
   out_2955282305521857746[187] = 0;
   out_2955282305521857746[188] = 0;
   out_2955282305521857746[189] = 0;
   out_2955282305521857746[190] = 1;
   out_2955282305521857746[191] = 0;
   out_2955282305521857746[192] = 0;
   out_2955282305521857746[193] = 0;
   out_2955282305521857746[194] = 0;
   out_2955282305521857746[195] = 0;
   out_2955282305521857746[196] = 0;
   out_2955282305521857746[197] = 0;
   out_2955282305521857746[198] = 0;
   out_2955282305521857746[199] = 0;
   out_2955282305521857746[200] = 0;
   out_2955282305521857746[201] = 0;
   out_2955282305521857746[202] = 0;
   out_2955282305521857746[203] = 0;
   out_2955282305521857746[204] = 0;
   out_2955282305521857746[205] = 0;
   out_2955282305521857746[206] = 0;
   out_2955282305521857746[207] = 0;
   out_2955282305521857746[208] = 0;
   out_2955282305521857746[209] = 1;
   out_2955282305521857746[210] = 0;
   out_2955282305521857746[211] = 0;
   out_2955282305521857746[212] = 0;
   out_2955282305521857746[213] = 0;
   out_2955282305521857746[214] = 0;
   out_2955282305521857746[215] = 0;
   out_2955282305521857746[216] = 0;
   out_2955282305521857746[217] = 0;
   out_2955282305521857746[218] = 0;
   out_2955282305521857746[219] = 0;
   out_2955282305521857746[220] = 0;
   out_2955282305521857746[221] = 0;
   out_2955282305521857746[222] = 0;
   out_2955282305521857746[223] = 0;
   out_2955282305521857746[224] = 0;
   out_2955282305521857746[225] = 0;
   out_2955282305521857746[226] = 0;
   out_2955282305521857746[227] = 0;
   out_2955282305521857746[228] = 1;
   out_2955282305521857746[229] = 0;
   out_2955282305521857746[230] = 0;
   out_2955282305521857746[231] = 0;
   out_2955282305521857746[232] = 0;
   out_2955282305521857746[233] = 0;
   out_2955282305521857746[234] = 0;
   out_2955282305521857746[235] = 0;
   out_2955282305521857746[236] = 0;
   out_2955282305521857746[237] = 0;
   out_2955282305521857746[238] = 0;
   out_2955282305521857746[239] = 0;
   out_2955282305521857746[240] = 0;
   out_2955282305521857746[241] = 0;
   out_2955282305521857746[242] = 0;
   out_2955282305521857746[243] = 0;
   out_2955282305521857746[244] = 0;
   out_2955282305521857746[245] = 0;
   out_2955282305521857746[246] = 0;
   out_2955282305521857746[247] = 1;
   out_2955282305521857746[248] = 0;
   out_2955282305521857746[249] = 0;
   out_2955282305521857746[250] = 0;
   out_2955282305521857746[251] = 0;
   out_2955282305521857746[252] = 0;
   out_2955282305521857746[253] = 0;
   out_2955282305521857746[254] = 0;
   out_2955282305521857746[255] = 0;
   out_2955282305521857746[256] = 0;
   out_2955282305521857746[257] = 0;
   out_2955282305521857746[258] = 0;
   out_2955282305521857746[259] = 0;
   out_2955282305521857746[260] = 0;
   out_2955282305521857746[261] = 0;
   out_2955282305521857746[262] = 0;
   out_2955282305521857746[263] = 0;
   out_2955282305521857746[264] = 0;
   out_2955282305521857746[265] = 0;
   out_2955282305521857746[266] = 1;
   out_2955282305521857746[267] = 0;
   out_2955282305521857746[268] = 0;
   out_2955282305521857746[269] = 0;
   out_2955282305521857746[270] = 0;
   out_2955282305521857746[271] = 0;
   out_2955282305521857746[272] = 0;
   out_2955282305521857746[273] = 0;
   out_2955282305521857746[274] = 0;
   out_2955282305521857746[275] = 0;
   out_2955282305521857746[276] = 0;
   out_2955282305521857746[277] = 0;
   out_2955282305521857746[278] = 0;
   out_2955282305521857746[279] = 0;
   out_2955282305521857746[280] = 0;
   out_2955282305521857746[281] = 0;
   out_2955282305521857746[282] = 0;
   out_2955282305521857746[283] = 0;
   out_2955282305521857746[284] = 0;
   out_2955282305521857746[285] = 1;
   out_2955282305521857746[286] = 0;
   out_2955282305521857746[287] = 0;
   out_2955282305521857746[288] = 0;
   out_2955282305521857746[289] = 0;
   out_2955282305521857746[290] = 0;
   out_2955282305521857746[291] = 0;
   out_2955282305521857746[292] = 0;
   out_2955282305521857746[293] = 0;
   out_2955282305521857746[294] = 0;
   out_2955282305521857746[295] = 0;
   out_2955282305521857746[296] = 0;
   out_2955282305521857746[297] = 0;
   out_2955282305521857746[298] = 0;
   out_2955282305521857746[299] = 0;
   out_2955282305521857746[300] = 0;
   out_2955282305521857746[301] = 0;
   out_2955282305521857746[302] = 0;
   out_2955282305521857746[303] = 0;
   out_2955282305521857746[304] = 1;
   out_2955282305521857746[305] = 0;
   out_2955282305521857746[306] = 0;
   out_2955282305521857746[307] = 0;
   out_2955282305521857746[308] = 0;
   out_2955282305521857746[309] = 0;
   out_2955282305521857746[310] = 0;
   out_2955282305521857746[311] = 0;
   out_2955282305521857746[312] = 0;
   out_2955282305521857746[313] = 0;
   out_2955282305521857746[314] = 0;
   out_2955282305521857746[315] = 0;
   out_2955282305521857746[316] = 0;
   out_2955282305521857746[317] = 0;
   out_2955282305521857746[318] = 0;
   out_2955282305521857746[319] = 0;
   out_2955282305521857746[320] = 0;
   out_2955282305521857746[321] = 0;
   out_2955282305521857746[322] = 0;
   out_2955282305521857746[323] = 1;
}
void h_4(double *state, double *unused, double *out_6086550385890598344) {
   out_6086550385890598344[0] = state[6] + state[9];
   out_6086550385890598344[1] = state[7] + state[10];
   out_6086550385890598344[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_882729684776454611) {
   out_882729684776454611[0] = 0;
   out_882729684776454611[1] = 0;
   out_882729684776454611[2] = 0;
   out_882729684776454611[3] = 0;
   out_882729684776454611[4] = 0;
   out_882729684776454611[5] = 0;
   out_882729684776454611[6] = 1;
   out_882729684776454611[7] = 0;
   out_882729684776454611[8] = 0;
   out_882729684776454611[9] = 1;
   out_882729684776454611[10] = 0;
   out_882729684776454611[11] = 0;
   out_882729684776454611[12] = 0;
   out_882729684776454611[13] = 0;
   out_882729684776454611[14] = 0;
   out_882729684776454611[15] = 0;
   out_882729684776454611[16] = 0;
   out_882729684776454611[17] = 0;
   out_882729684776454611[18] = 0;
   out_882729684776454611[19] = 0;
   out_882729684776454611[20] = 0;
   out_882729684776454611[21] = 0;
   out_882729684776454611[22] = 0;
   out_882729684776454611[23] = 0;
   out_882729684776454611[24] = 0;
   out_882729684776454611[25] = 1;
   out_882729684776454611[26] = 0;
   out_882729684776454611[27] = 0;
   out_882729684776454611[28] = 1;
   out_882729684776454611[29] = 0;
   out_882729684776454611[30] = 0;
   out_882729684776454611[31] = 0;
   out_882729684776454611[32] = 0;
   out_882729684776454611[33] = 0;
   out_882729684776454611[34] = 0;
   out_882729684776454611[35] = 0;
   out_882729684776454611[36] = 0;
   out_882729684776454611[37] = 0;
   out_882729684776454611[38] = 0;
   out_882729684776454611[39] = 0;
   out_882729684776454611[40] = 0;
   out_882729684776454611[41] = 0;
   out_882729684776454611[42] = 0;
   out_882729684776454611[43] = 0;
   out_882729684776454611[44] = 1;
   out_882729684776454611[45] = 0;
   out_882729684776454611[46] = 0;
   out_882729684776454611[47] = 1;
   out_882729684776454611[48] = 0;
   out_882729684776454611[49] = 0;
   out_882729684776454611[50] = 0;
   out_882729684776454611[51] = 0;
   out_882729684776454611[52] = 0;
   out_882729684776454611[53] = 0;
}
void h_10(double *state, double *unused, double *out_822146309921429030) {
   out_822146309921429030[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_822146309921429030[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_822146309921429030[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8527164112518639864) {
   out_8527164112518639864[0] = 0;
   out_8527164112518639864[1] = 9.8100000000000005*cos(state[1]);
   out_8527164112518639864[2] = 0;
   out_8527164112518639864[3] = 0;
   out_8527164112518639864[4] = -state[8];
   out_8527164112518639864[5] = state[7];
   out_8527164112518639864[6] = 0;
   out_8527164112518639864[7] = state[5];
   out_8527164112518639864[8] = -state[4];
   out_8527164112518639864[9] = 0;
   out_8527164112518639864[10] = 0;
   out_8527164112518639864[11] = 0;
   out_8527164112518639864[12] = 1;
   out_8527164112518639864[13] = 0;
   out_8527164112518639864[14] = 0;
   out_8527164112518639864[15] = 1;
   out_8527164112518639864[16] = 0;
   out_8527164112518639864[17] = 0;
   out_8527164112518639864[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8527164112518639864[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8527164112518639864[20] = 0;
   out_8527164112518639864[21] = state[8];
   out_8527164112518639864[22] = 0;
   out_8527164112518639864[23] = -state[6];
   out_8527164112518639864[24] = -state[5];
   out_8527164112518639864[25] = 0;
   out_8527164112518639864[26] = state[3];
   out_8527164112518639864[27] = 0;
   out_8527164112518639864[28] = 0;
   out_8527164112518639864[29] = 0;
   out_8527164112518639864[30] = 0;
   out_8527164112518639864[31] = 1;
   out_8527164112518639864[32] = 0;
   out_8527164112518639864[33] = 0;
   out_8527164112518639864[34] = 1;
   out_8527164112518639864[35] = 0;
   out_8527164112518639864[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8527164112518639864[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8527164112518639864[38] = 0;
   out_8527164112518639864[39] = -state[7];
   out_8527164112518639864[40] = state[6];
   out_8527164112518639864[41] = 0;
   out_8527164112518639864[42] = state[4];
   out_8527164112518639864[43] = -state[3];
   out_8527164112518639864[44] = 0;
   out_8527164112518639864[45] = 0;
   out_8527164112518639864[46] = 0;
   out_8527164112518639864[47] = 0;
   out_8527164112518639864[48] = 0;
   out_8527164112518639864[49] = 0;
   out_8527164112518639864[50] = 1;
   out_8527164112518639864[51] = 0;
   out_8527164112518639864[52] = 0;
   out_8527164112518639864[53] = 1;
}
void h_13(double *state, double *unused, double *out_9110778303873781210) {
   out_9110778303873781210[0] = state[3];
   out_9110778303873781210[1] = state[4];
   out_9110778303873781210[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4095003510108787412) {
   out_4095003510108787412[0] = 0;
   out_4095003510108787412[1] = 0;
   out_4095003510108787412[2] = 0;
   out_4095003510108787412[3] = 1;
   out_4095003510108787412[4] = 0;
   out_4095003510108787412[5] = 0;
   out_4095003510108787412[6] = 0;
   out_4095003510108787412[7] = 0;
   out_4095003510108787412[8] = 0;
   out_4095003510108787412[9] = 0;
   out_4095003510108787412[10] = 0;
   out_4095003510108787412[11] = 0;
   out_4095003510108787412[12] = 0;
   out_4095003510108787412[13] = 0;
   out_4095003510108787412[14] = 0;
   out_4095003510108787412[15] = 0;
   out_4095003510108787412[16] = 0;
   out_4095003510108787412[17] = 0;
   out_4095003510108787412[18] = 0;
   out_4095003510108787412[19] = 0;
   out_4095003510108787412[20] = 0;
   out_4095003510108787412[21] = 0;
   out_4095003510108787412[22] = 1;
   out_4095003510108787412[23] = 0;
   out_4095003510108787412[24] = 0;
   out_4095003510108787412[25] = 0;
   out_4095003510108787412[26] = 0;
   out_4095003510108787412[27] = 0;
   out_4095003510108787412[28] = 0;
   out_4095003510108787412[29] = 0;
   out_4095003510108787412[30] = 0;
   out_4095003510108787412[31] = 0;
   out_4095003510108787412[32] = 0;
   out_4095003510108787412[33] = 0;
   out_4095003510108787412[34] = 0;
   out_4095003510108787412[35] = 0;
   out_4095003510108787412[36] = 0;
   out_4095003510108787412[37] = 0;
   out_4095003510108787412[38] = 0;
   out_4095003510108787412[39] = 0;
   out_4095003510108787412[40] = 0;
   out_4095003510108787412[41] = 1;
   out_4095003510108787412[42] = 0;
   out_4095003510108787412[43] = 0;
   out_4095003510108787412[44] = 0;
   out_4095003510108787412[45] = 0;
   out_4095003510108787412[46] = 0;
   out_4095003510108787412[47] = 0;
   out_4095003510108787412[48] = 0;
   out_4095003510108787412[49] = 0;
   out_4095003510108787412[50] = 0;
   out_4095003510108787412[51] = 0;
   out_4095003510108787412[52] = 0;
   out_4095003510108787412[53] = 0;
}
void h_14(double *state, double *unused, double *out_6914362473414566847) {
   out_6914362473414566847[0] = state[6];
   out_6914362473414566847[1] = state[7];
   out_6914362473414566847[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4845970541115939140) {
   out_4845970541115939140[0] = 0;
   out_4845970541115939140[1] = 0;
   out_4845970541115939140[2] = 0;
   out_4845970541115939140[3] = 0;
   out_4845970541115939140[4] = 0;
   out_4845970541115939140[5] = 0;
   out_4845970541115939140[6] = 1;
   out_4845970541115939140[7] = 0;
   out_4845970541115939140[8] = 0;
   out_4845970541115939140[9] = 0;
   out_4845970541115939140[10] = 0;
   out_4845970541115939140[11] = 0;
   out_4845970541115939140[12] = 0;
   out_4845970541115939140[13] = 0;
   out_4845970541115939140[14] = 0;
   out_4845970541115939140[15] = 0;
   out_4845970541115939140[16] = 0;
   out_4845970541115939140[17] = 0;
   out_4845970541115939140[18] = 0;
   out_4845970541115939140[19] = 0;
   out_4845970541115939140[20] = 0;
   out_4845970541115939140[21] = 0;
   out_4845970541115939140[22] = 0;
   out_4845970541115939140[23] = 0;
   out_4845970541115939140[24] = 0;
   out_4845970541115939140[25] = 1;
   out_4845970541115939140[26] = 0;
   out_4845970541115939140[27] = 0;
   out_4845970541115939140[28] = 0;
   out_4845970541115939140[29] = 0;
   out_4845970541115939140[30] = 0;
   out_4845970541115939140[31] = 0;
   out_4845970541115939140[32] = 0;
   out_4845970541115939140[33] = 0;
   out_4845970541115939140[34] = 0;
   out_4845970541115939140[35] = 0;
   out_4845970541115939140[36] = 0;
   out_4845970541115939140[37] = 0;
   out_4845970541115939140[38] = 0;
   out_4845970541115939140[39] = 0;
   out_4845970541115939140[40] = 0;
   out_4845970541115939140[41] = 0;
   out_4845970541115939140[42] = 0;
   out_4845970541115939140[43] = 0;
   out_4845970541115939140[44] = 1;
   out_4845970541115939140[45] = 0;
   out_4845970541115939140[46] = 0;
   out_4845970541115939140[47] = 0;
   out_4845970541115939140[48] = 0;
   out_4845970541115939140[49] = 0;
   out_4845970541115939140[50] = 0;
   out_4845970541115939140[51] = 0;
   out_4845970541115939140[52] = 0;
   out_4845970541115939140[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3316982698909296372) {
  err_fun(nom_x, delta_x, out_3316982698909296372);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_875278244398304479) {
  inv_err_fun(nom_x, true_x, out_875278244398304479);
}
void pose_H_mod_fun(double *state, double *out_4269788700262626124) {
  H_mod_fun(state, out_4269788700262626124);
}
void pose_f_fun(double *state, double dt, double *out_3692668602312034618) {
  f_fun(state,  dt, out_3692668602312034618);
}
void pose_F_fun(double *state, double dt, double *out_2955282305521857746) {
  F_fun(state,  dt, out_2955282305521857746);
}
void pose_h_4(double *state, double *unused, double *out_6086550385890598344) {
  h_4(state, unused, out_6086550385890598344);
}
void pose_H_4(double *state, double *unused, double *out_882729684776454611) {
  H_4(state, unused, out_882729684776454611);
}
void pose_h_10(double *state, double *unused, double *out_822146309921429030) {
  h_10(state, unused, out_822146309921429030);
}
void pose_H_10(double *state, double *unused, double *out_8527164112518639864) {
  H_10(state, unused, out_8527164112518639864);
}
void pose_h_13(double *state, double *unused, double *out_9110778303873781210) {
  h_13(state, unused, out_9110778303873781210);
}
void pose_H_13(double *state, double *unused, double *out_4095003510108787412) {
  H_13(state, unused, out_4095003510108787412);
}
void pose_h_14(double *state, double *unused, double *out_6914362473414566847) {
  h_14(state, unused, out_6914362473414566847);
}
void pose_H_14(double *state, double *unused, double *out_4845970541115939140) {
  H_14(state, unused, out_4845970541115939140);
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
