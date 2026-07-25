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
void err_fun(double *nom_x, double *delta_x, double *out_2803054085873220166) {
   out_2803054085873220166[0] = delta_x[0] + nom_x[0];
   out_2803054085873220166[1] = delta_x[1] + nom_x[1];
   out_2803054085873220166[2] = delta_x[2] + nom_x[2];
   out_2803054085873220166[3] = delta_x[3] + nom_x[3];
   out_2803054085873220166[4] = delta_x[4] + nom_x[4];
   out_2803054085873220166[5] = delta_x[5] + nom_x[5];
   out_2803054085873220166[6] = delta_x[6] + nom_x[6];
   out_2803054085873220166[7] = delta_x[7] + nom_x[7];
   out_2803054085873220166[8] = delta_x[8] + nom_x[8];
   out_2803054085873220166[9] = delta_x[9] + nom_x[9];
   out_2803054085873220166[10] = delta_x[10] + nom_x[10];
   out_2803054085873220166[11] = delta_x[11] + nom_x[11];
   out_2803054085873220166[12] = delta_x[12] + nom_x[12];
   out_2803054085873220166[13] = delta_x[13] + nom_x[13];
   out_2803054085873220166[14] = delta_x[14] + nom_x[14];
   out_2803054085873220166[15] = delta_x[15] + nom_x[15];
   out_2803054085873220166[16] = delta_x[16] + nom_x[16];
   out_2803054085873220166[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_870718263858356541) {
   out_870718263858356541[0] = -nom_x[0] + true_x[0];
   out_870718263858356541[1] = -nom_x[1] + true_x[1];
   out_870718263858356541[2] = -nom_x[2] + true_x[2];
   out_870718263858356541[3] = -nom_x[3] + true_x[3];
   out_870718263858356541[4] = -nom_x[4] + true_x[4];
   out_870718263858356541[5] = -nom_x[5] + true_x[5];
   out_870718263858356541[6] = -nom_x[6] + true_x[6];
   out_870718263858356541[7] = -nom_x[7] + true_x[7];
   out_870718263858356541[8] = -nom_x[8] + true_x[8];
   out_870718263858356541[9] = -nom_x[9] + true_x[9];
   out_870718263858356541[10] = -nom_x[10] + true_x[10];
   out_870718263858356541[11] = -nom_x[11] + true_x[11];
   out_870718263858356541[12] = -nom_x[12] + true_x[12];
   out_870718263858356541[13] = -nom_x[13] + true_x[13];
   out_870718263858356541[14] = -nom_x[14] + true_x[14];
   out_870718263858356541[15] = -nom_x[15] + true_x[15];
   out_870718263858356541[16] = -nom_x[16] + true_x[16];
   out_870718263858356541[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_245560868528396178) {
   out_245560868528396178[0] = 1.0;
   out_245560868528396178[1] = 0.0;
   out_245560868528396178[2] = 0.0;
   out_245560868528396178[3] = 0.0;
   out_245560868528396178[4] = 0.0;
   out_245560868528396178[5] = 0.0;
   out_245560868528396178[6] = 0.0;
   out_245560868528396178[7] = 0.0;
   out_245560868528396178[8] = 0.0;
   out_245560868528396178[9] = 0.0;
   out_245560868528396178[10] = 0.0;
   out_245560868528396178[11] = 0.0;
   out_245560868528396178[12] = 0.0;
   out_245560868528396178[13] = 0.0;
   out_245560868528396178[14] = 0.0;
   out_245560868528396178[15] = 0.0;
   out_245560868528396178[16] = 0.0;
   out_245560868528396178[17] = 0.0;
   out_245560868528396178[18] = 0.0;
   out_245560868528396178[19] = 1.0;
   out_245560868528396178[20] = 0.0;
   out_245560868528396178[21] = 0.0;
   out_245560868528396178[22] = 0.0;
   out_245560868528396178[23] = 0.0;
   out_245560868528396178[24] = 0.0;
   out_245560868528396178[25] = 0.0;
   out_245560868528396178[26] = 0.0;
   out_245560868528396178[27] = 0.0;
   out_245560868528396178[28] = 0.0;
   out_245560868528396178[29] = 0.0;
   out_245560868528396178[30] = 0.0;
   out_245560868528396178[31] = 0.0;
   out_245560868528396178[32] = 0.0;
   out_245560868528396178[33] = 0.0;
   out_245560868528396178[34] = 0.0;
   out_245560868528396178[35] = 0.0;
   out_245560868528396178[36] = 0.0;
   out_245560868528396178[37] = 0.0;
   out_245560868528396178[38] = 1.0;
   out_245560868528396178[39] = 0.0;
   out_245560868528396178[40] = 0.0;
   out_245560868528396178[41] = 0.0;
   out_245560868528396178[42] = 0.0;
   out_245560868528396178[43] = 0.0;
   out_245560868528396178[44] = 0.0;
   out_245560868528396178[45] = 0.0;
   out_245560868528396178[46] = 0.0;
   out_245560868528396178[47] = 0.0;
   out_245560868528396178[48] = 0.0;
   out_245560868528396178[49] = 0.0;
   out_245560868528396178[50] = 0.0;
   out_245560868528396178[51] = 0.0;
   out_245560868528396178[52] = 0.0;
   out_245560868528396178[53] = 0.0;
   out_245560868528396178[54] = 0.0;
   out_245560868528396178[55] = 0.0;
   out_245560868528396178[56] = 0.0;
   out_245560868528396178[57] = 1.0;
   out_245560868528396178[58] = 0.0;
   out_245560868528396178[59] = 0.0;
   out_245560868528396178[60] = 0.0;
   out_245560868528396178[61] = 0.0;
   out_245560868528396178[62] = 0.0;
   out_245560868528396178[63] = 0.0;
   out_245560868528396178[64] = 0.0;
   out_245560868528396178[65] = 0.0;
   out_245560868528396178[66] = 0.0;
   out_245560868528396178[67] = 0.0;
   out_245560868528396178[68] = 0.0;
   out_245560868528396178[69] = 0.0;
   out_245560868528396178[70] = 0.0;
   out_245560868528396178[71] = 0.0;
   out_245560868528396178[72] = 0.0;
   out_245560868528396178[73] = 0.0;
   out_245560868528396178[74] = 0.0;
   out_245560868528396178[75] = 0.0;
   out_245560868528396178[76] = 1.0;
   out_245560868528396178[77] = 0.0;
   out_245560868528396178[78] = 0.0;
   out_245560868528396178[79] = 0.0;
   out_245560868528396178[80] = 0.0;
   out_245560868528396178[81] = 0.0;
   out_245560868528396178[82] = 0.0;
   out_245560868528396178[83] = 0.0;
   out_245560868528396178[84] = 0.0;
   out_245560868528396178[85] = 0.0;
   out_245560868528396178[86] = 0.0;
   out_245560868528396178[87] = 0.0;
   out_245560868528396178[88] = 0.0;
   out_245560868528396178[89] = 0.0;
   out_245560868528396178[90] = 0.0;
   out_245560868528396178[91] = 0.0;
   out_245560868528396178[92] = 0.0;
   out_245560868528396178[93] = 0.0;
   out_245560868528396178[94] = 0.0;
   out_245560868528396178[95] = 1.0;
   out_245560868528396178[96] = 0.0;
   out_245560868528396178[97] = 0.0;
   out_245560868528396178[98] = 0.0;
   out_245560868528396178[99] = 0.0;
   out_245560868528396178[100] = 0.0;
   out_245560868528396178[101] = 0.0;
   out_245560868528396178[102] = 0.0;
   out_245560868528396178[103] = 0.0;
   out_245560868528396178[104] = 0.0;
   out_245560868528396178[105] = 0.0;
   out_245560868528396178[106] = 0.0;
   out_245560868528396178[107] = 0.0;
   out_245560868528396178[108] = 0.0;
   out_245560868528396178[109] = 0.0;
   out_245560868528396178[110] = 0.0;
   out_245560868528396178[111] = 0.0;
   out_245560868528396178[112] = 0.0;
   out_245560868528396178[113] = 0.0;
   out_245560868528396178[114] = 1.0;
   out_245560868528396178[115] = 0.0;
   out_245560868528396178[116] = 0.0;
   out_245560868528396178[117] = 0.0;
   out_245560868528396178[118] = 0.0;
   out_245560868528396178[119] = 0.0;
   out_245560868528396178[120] = 0.0;
   out_245560868528396178[121] = 0.0;
   out_245560868528396178[122] = 0.0;
   out_245560868528396178[123] = 0.0;
   out_245560868528396178[124] = 0.0;
   out_245560868528396178[125] = 0.0;
   out_245560868528396178[126] = 0.0;
   out_245560868528396178[127] = 0.0;
   out_245560868528396178[128] = 0.0;
   out_245560868528396178[129] = 0.0;
   out_245560868528396178[130] = 0.0;
   out_245560868528396178[131] = 0.0;
   out_245560868528396178[132] = 0.0;
   out_245560868528396178[133] = 1.0;
   out_245560868528396178[134] = 0.0;
   out_245560868528396178[135] = 0.0;
   out_245560868528396178[136] = 0.0;
   out_245560868528396178[137] = 0.0;
   out_245560868528396178[138] = 0.0;
   out_245560868528396178[139] = 0.0;
   out_245560868528396178[140] = 0.0;
   out_245560868528396178[141] = 0.0;
   out_245560868528396178[142] = 0.0;
   out_245560868528396178[143] = 0.0;
   out_245560868528396178[144] = 0.0;
   out_245560868528396178[145] = 0.0;
   out_245560868528396178[146] = 0.0;
   out_245560868528396178[147] = 0.0;
   out_245560868528396178[148] = 0.0;
   out_245560868528396178[149] = 0.0;
   out_245560868528396178[150] = 0.0;
   out_245560868528396178[151] = 0.0;
   out_245560868528396178[152] = 1.0;
   out_245560868528396178[153] = 0.0;
   out_245560868528396178[154] = 0.0;
   out_245560868528396178[155] = 0.0;
   out_245560868528396178[156] = 0.0;
   out_245560868528396178[157] = 0.0;
   out_245560868528396178[158] = 0.0;
   out_245560868528396178[159] = 0.0;
   out_245560868528396178[160] = 0.0;
   out_245560868528396178[161] = 0.0;
   out_245560868528396178[162] = 0.0;
   out_245560868528396178[163] = 0.0;
   out_245560868528396178[164] = 0.0;
   out_245560868528396178[165] = 0.0;
   out_245560868528396178[166] = 0.0;
   out_245560868528396178[167] = 0.0;
   out_245560868528396178[168] = 0.0;
   out_245560868528396178[169] = 0.0;
   out_245560868528396178[170] = 0.0;
   out_245560868528396178[171] = 1.0;
   out_245560868528396178[172] = 0.0;
   out_245560868528396178[173] = 0.0;
   out_245560868528396178[174] = 0.0;
   out_245560868528396178[175] = 0.0;
   out_245560868528396178[176] = 0.0;
   out_245560868528396178[177] = 0.0;
   out_245560868528396178[178] = 0.0;
   out_245560868528396178[179] = 0.0;
   out_245560868528396178[180] = 0.0;
   out_245560868528396178[181] = 0.0;
   out_245560868528396178[182] = 0.0;
   out_245560868528396178[183] = 0.0;
   out_245560868528396178[184] = 0.0;
   out_245560868528396178[185] = 0.0;
   out_245560868528396178[186] = 0.0;
   out_245560868528396178[187] = 0.0;
   out_245560868528396178[188] = 0.0;
   out_245560868528396178[189] = 0.0;
   out_245560868528396178[190] = 1.0;
   out_245560868528396178[191] = 0.0;
   out_245560868528396178[192] = 0.0;
   out_245560868528396178[193] = 0.0;
   out_245560868528396178[194] = 0.0;
   out_245560868528396178[195] = 0.0;
   out_245560868528396178[196] = 0.0;
   out_245560868528396178[197] = 0.0;
   out_245560868528396178[198] = 0.0;
   out_245560868528396178[199] = 0.0;
   out_245560868528396178[200] = 0.0;
   out_245560868528396178[201] = 0.0;
   out_245560868528396178[202] = 0.0;
   out_245560868528396178[203] = 0.0;
   out_245560868528396178[204] = 0.0;
   out_245560868528396178[205] = 0.0;
   out_245560868528396178[206] = 0.0;
   out_245560868528396178[207] = 0.0;
   out_245560868528396178[208] = 0.0;
   out_245560868528396178[209] = 1.0;
   out_245560868528396178[210] = 0.0;
   out_245560868528396178[211] = 0.0;
   out_245560868528396178[212] = 0.0;
   out_245560868528396178[213] = 0.0;
   out_245560868528396178[214] = 0.0;
   out_245560868528396178[215] = 0.0;
   out_245560868528396178[216] = 0.0;
   out_245560868528396178[217] = 0.0;
   out_245560868528396178[218] = 0.0;
   out_245560868528396178[219] = 0.0;
   out_245560868528396178[220] = 0.0;
   out_245560868528396178[221] = 0.0;
   out_245560868528396178[222] = 0.0;
   out_245560868528396178[223] = 0.0;
   out_245560868528396178[224] = 0.0;
   out_245560868528396178[225] = 0.0;
   out_245560868528396178[226] = 0.0;
   out_245560868528396178[227] = 0.0;
   out_245560868528396178[228] = 1.0;
   out_245560868528396178[229] = 0.0;
   out_245560868528396178[230] = 0.0;
   out_245560868528396178[231] = 0.0;
   out_245560868528396178[232] = 0.0;
   out_245560868528396178[233] = 0.0;
   out_245560868528396178[234] = 0.0;
   out_245560868528396178[235] = 0.0;
   out_245560868528396178[236] = 0.0;
   out_245560868528396178[237] = 0.0;
   out_245560868528396178[238] = 0.0;
   out_245560868528396178[239] = 0.0;
   out_245560868528396178[240] = 0.0;
   out_245560868528396178[241] = 0.0;
   out_245560868528396178[242] = 0.0;
   out_245560868528396178[243] = 0.0;
   out_245560868528396178[244] = 0.0;
   out_245560868528396178[245] = 0.0;
   out_245560868528396178[246] = 0.0;
   out_245560868528396178[247] = 1.0;
   out_245560868528396178[248] = 0.0;
   out_245560868528396178[249] = 0.0;
   out_245560868528396178[250] = 0.0;
   out_245560868528396178[251] = 0.0;
   out_245560868528396178[252] = 0.0;
   out_245560868528396178[253] = 0.0;
   out_245560868528396178[254] = 0.0;
   out_245560868528396178[255] = 0.0;
   out_245560868528396178[256] = 0.0;
   out_245560868528396178[257] = 0.0;
   out_245560868528396178[258] = 0.0;
   out_245560868528396178[259] = 0.0;
   out_245560868528396178[260] = 0.0;
   out_245560868528396178[261] = 0.0;
   out_245560868528396178[262] = 0.0;
   out_245560868528396178[263] = 0.0;
   out_245560868528396178[264] = 0.0;
   out_245560868528396178[265] = 0.0;
   out_245560868528396178[266] = 1.0;
   out_245560868528396178[267] = 0.0;
   out_245560868528396178[268] = 0.0;
   out_245560868528396178[269] = 0.0;
   out_245560868528396178[270] = 0.0;
   out_245560868528396178[271] = 0.0;
   out_245560868528396178[272] = 0.0;
   out_245560868528396178[273] = 0.0;
   out_245560868528396178[274] = 0.0;
   out_245560868528396178[275] = 0.0;
   out_245560868528396178[276] = 0.0;
   out_245560868528396178[277] = 0.0;
   out_245560868528396178[278] = 0.0;
   out_245560868528396178[279] = 0.0;
   out_245560868528396178[280] = 0.0;
   out_245560868528396178[281] = 0.0;
   out_245560868528396178[282] = 0.0;
   out_245560868528396178[283] = 0.0;
   out_245560868528396178[284] = 0.0;
   out_245560868528396178[285] = 1.0;
   out_245560868528396178[286] = 0.0;
   out_245560868528396178[287] = 0.0;
   out_245560868528396178[288] = 0.0;
   out_245560868528396178[289] = 0.0;
   out_245560868528396178[290] = 0.0;
   out_245560868528396178[291] = 0.0;
   out_245560868528396178[292] = 0.0;
   out_245560868528396178[293] = 0.0;
   out_245560868528396178[294] = 0.0;
   out_245560868528396178[295] = 0.0;
   out_245560868528396178[296] = 0.0;
   out_245560868528396178[297] = 0.0;
   out_245560868528396178[298] = 0.0;
   out_245560868528396178[299] = 0.0;
   out_245560868528396178[300] = 0.0;
   out_245560868528396178[301] = 0.0;
   out_245560868528396178[302] = 0.0;
   out_245560868528396178[303] = 0.0;
   out_245560868528396178[304] = 1.0;
   out_245560868528396178[305] = 0.0;
   out_245560868528396178[306] = 0.0;
   out_245560868528396178[307] = 0.0;
   out_245560868528396178[308] = 0.0;
   out_245560868528396178[309] = 0.0;
   out_245560868528396178[310] = 0.0;
   out_245560868528396178[311] = 0.0;
   out_245560868528396178[312] = 0.0;
   out_245560868528396178[313] = 0.0;
   out_245560868528396178[314] = 0.0;
   out_245560868528396178[315] = 0.0;
   out_245560868528396178[316] = 0.0;
   out_245560868528396178[317] = 0.0;
   out_245560868528396178[318] = 0.0;
   out_245560868528396178[319] = 0.0;
   out_245560868528396178[320] = 0.0;
   out_245560868528396178[321] = 0.0;
   out_245560868528396178[322] = 0.0;
   out_245560868528396178[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8465405656783528291) {
   out_8465405656783528291[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8465405656783528291[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8465405656783528291[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8465405656783528291[3] = dt*state[12] + state[3];
   out_8465405656783528291[4] = dt*state[13] + state[4];
   out_8465405656783528291[5] = dt*state[14] + state[5];
   out_8465405656783528291[6] = state[6];
   out_8465405656783528291[7] = state[7];
   out_8465405656783528291[8] = state[8];
   out_8465405656783528291[9] = state[9];
   out_8465405656783528291[10] = state[10];
   out_8465405656783528291[11] = state[11];
   out_8465405656783528291[12] = state[12];
   out_8465405656783528291[13] = state[13];
   out_8465405656783528291[14] = state[14];
   out_8465405656783528291[15] = state[15];
   out_8465405656783528291[16] = state[16];
   out_8465405656783528291[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5153518595662752782) {
   out_5153518595662752782[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5153518595662752782[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5153518595662752782[2] = 0;
   out_5153518595662752782[3] = 0;
   out_5153518595662752782[4] = 0;
   out_5153518595662752782[5] = 0;
   out_5153518595662752782[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5153518595662752782[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5153518595662752782[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5153518595662752782[9] = 0;
   out_5153518595662752782[10] = 0;
   out_5153518595662752782[11] = 0;
   out_5153518595662752782[12] = 0;
   out_5153518595662752782[13] = 0;
   out_5153518595662752782[14] = 0;
   out_5153518595662752782[15] = 0;
   out_5153518595662752782[16] = 0;
   out_5153518595662752782[17] = 0;
   out_5153518595662752782[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5153518595662752782[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5153518595662752782[20] = 0;
   out_5153518595662752782[21] = 0;
   out_5153518595662752782[22] = 0;
   out_5153518595662752782[23] = 0;
   out_5153518595662752782[24] = 0;
   out_5153518595662752782[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5153518595662752782[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5153518595662752782[27] = 0;
   out_5153518595662752782[28] = 0;
   out_5153518595662752782[29] = 0;
   out_5153518595662752782[30] = 0;
   out_5153518595662752782[31] = 0;
   out_5153518595662752782[32] = 0;
   out_5153518595662752782[33] = 0;
   out_5153518595662752782[34] = 0;
   out_5153518595662752782[35] = 0;
   out_5153518595662752782[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5153518595662752782[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5153518595662752782[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5153518595662752782[39] = 0;
   out_5153518595662752782[40] = 0;
   out_5153518595662752782[41] = 0;
   out_5153518595662752782[42] = 0;
   out_5153518595662752782[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5153518595662752782[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5153518595662752782[45] = 0;
   out_5153518595662752782[46] = 0;
   out_5153518595662752782[47] = 0;
   out_5153518595662752782[48] = 0;
   out_5153518595662752782[49] = 0;
   out_5153518595662752782[50] = 0;
   out_5153518595662752782[51] = 0;
   out_5153518595662752782[52] = 0;
   out_5153518595662752782[53] = 0;
   out_5153518595662752782[54] = 0;
   out_5153518595662752782[55] = 0;
   out_5153518595662752782[56] = 0;
   out_5153518595662752782[57] = 1;
   out_5153518595662752782[58] = 0;
   out_5153518595662752782[59] = 0;
   out_5153518595662752782[60] = 0;
   out_5153518595662752782[61] = 0;
   out_5153518595662752782[62] = 0;
   out_5153518595662752782[63] = 0;
   out_5153518595662752782[64] = 0;
   out_5153518595662752782[65] = 0;
   out_5153518595662752782[66] = dt;
   out_5153518595662752782[67] = 0;
   out_5153518595662752782[68] = 0;
   out_5153518595662752782[69] = 0;
   out_5153518595662752782[70] = 0;
   out_5153518595662752782[71] = 0;
   out_5153518595662752782[72] = 0;
   out_5153518595662752782[73] = 0;
   out_5153518595662752782[74] = 0;
   out_5153518595662752782[75] = 0;
   out_5153518595662752782[76] = 1;
   out_5153518595662752782[77] = 0;
   out_5153518595662752782[78] = 0;
   out_5153518595662752782[79] = 0;
   out_5153518595662752782[80] = 0;
   out_5153518595662752782[81] = 0;
   out_5153518595662752782[82] = 0;
   out_5153518595662752782[83] = 0;
   out_5153518595662752782[84] = 0;
   out_5153518595662752782[85] = dt;
   out_5153518595662752782[86] = 0;
   out_5153518595662752782[87] = 0;
   out_5153518595662752782[88] = 0;
   out_5153518595662752782[89] = 0;
   out_5153518595662752782[90] = 0;
   out_5153518595662752782[91] = 0;
   out_5153518595662752782[92] = 0;
   out_5153518595662752782[93] = 0;
   out_5153518595662752782[94] = 0;
   out_5153518595662752782[95] = 1;
   out_5153518595662752782[96] = 0;
   out_5153518595662752782[97] = 0;
   out_5153518595662752782[98] = 0;
   out_5153518595662752782[99] = 0;
   out_5153518595662752782[100] = 0;
   out_5153518595662752782[101] = 0;
   out_5153518595662752782[102] = 0;
   out_5153518595662752782[103] = 0;
   out_5153518595662752782[104] = dt;
   out_5153518595662752782[105] = 0;
   out_5153518595662752782[106] = 0;
   out_5153518595662752782[107] = 0;
   out_5153518595662752782[108] = 0;
   out_5153518595662752782[109] = 0;
   out_5153518595662752782[110] = 0;
   out_5153518595662752782[111] = 0;
   out_5153518595662752782[112] = 0;
   out_5153518595662752782[113] = 0;
   out_5153518595662752782[114] = 1;
   out_5153518595662752782[115] = 0;
   out_5153518595662752782[116] = 0;
   out_5153518595662752782[117] = 0;
   out_5153518595662752782[118] = 0;
   out_5153518595662752782[119] = 0;
   out_5153518595662752782[120] = 0;
   out_5153518595662752782[121] = 0;
   out_5153518595662752782[122] = 0;
   out_5153518595662752782[123] = 0;
   out_5153518595662752782[124] = 0;
   out_5153518595662752782[125] = 0;
   out_5153518595662752782[126] = 0;
   out_5153518595662752782[127] = 0;
   out_5153518595662752782[128] = 0;
   out_5153518595662752782[129] = 0;
   out_5153518595662752782[130] = 0;
   out_5153518595662752782[131] = 0;
   out_5153518595662752782[132] = 0;
   out_5153518595662752782[133] = 1;
   out_5153518595662752782[134] = 0;
   out_5153518595662752782[135] = 0;
   out_5153518595662752782[136] = 0;
   out_5153518595662752782[137] = 0;
   out_5153518595662752782[138] = 0;
   out_5153518595662752782[139] = 0;
   out_5153518595662752782[140] = 0;
   out_5153518595662752782[141] = 0;
   out_5153518595662752782[142] = 0;
   out_5153518595662752782[143] = 0;
   out_5153518595662752782[144] = 0;
   out_5153518595662752782[145] = 0;
   out_5153518595662752782[146] = 0;
   out_5153518595662752782[147] = 0;
   out_5153518595662752782[148] = 0;
   out_5153518595662752782[149] = 0;
   out_5153518595662752782[150] = 0;
   out_5153518595662752782[151] = 0;
   out_5153518595662752782[152] = 1;
   out_5153518595662752782[153] = 0;
   out_5153518595662752782[154] = 0;
   out_5153518595662752782[155] = 0;
   out_5153518595662752782[156] = 0;
   out_5153518595662752782[157] = 0;
   out_5153518595662752782[158] = 0;
   out_5153518595662752782[159] = 0;
   out_5153518595662752782[160] = 0;
   out_5153518595662752782[161] = 0;
   out_5153518595662752782[162] = 0;
   out_5153518595662752782[163] = 0;
   out_5153518595662752782[164] = 0;
   out_5153518595662752782[165] = 0;
   out_5153518595662752782[166] = 0;
   out_5153518595662752782[167] = 0;
   out_5153518595662752782[168] = 0;
   out_5153518595662752782[169] = 0;
   out_5153518595662752782[170] = 0;
   out_5153518595662752782[171] = 1;
   out_5153518595662752782[172] = 0;
   out_5153518595662752782[173] = 0;
   out_5153518595662752782[174] = 0;
   out_5153518595662752782[175] = 0;
   out_5153518595662752782[176] = 0;
   out_5153518595662752782[177] = 0;
   out_5153518595662752782[178] = 0;
   out_5153518595662752782[179] = 0;
   out_5153518595662752782[180] = 0;
   out_5153518595662752782[181] = 0;
   out_5153518595662752782[182] = 0;
   out_5153518595662752782[183] = 0;
   out_5153518595662752782[184] = 0;
   out_5153518595662752782[185] = 0;
   out_5153518595662752782[186] = 0;
   out_5153518595662752782[187] = 0;
   out_5153518595662752782[188] = 0;
   out_5153518595662752782[189] = 0;
   out_5153518595662752782[190] = 1;
   out_5153518595662752782[191] = 0;
   out_5153518595662752782[192] = 0;
   out_5153518595662752782[193] = 0;
   out_5153518595662752782[194] = 0;
   out_5153518595662752782[195] = 0;
   out_5153518595662752782[196] = 0;
   out_5153518595662752782[197] = 0;
   out_5153518595662752782[198] = 0;
   out_5153518595662752782[199] = 0;
   out_5153518595662752782[200] = 0;
   out_5153518595662752782[201] = 0;
   out_5153518595662752782[202] = 0;
   out_5153518595662752782[203] = 0;
   out_5153518595662752782[204] = 0;
   out_5153518595662752782[205] = 0;
   out_5153518595662752782[206] = 0;
   out_5153518595662752782[207] = 0;
   out_5153518595662752782[208] = 0;
   out_5153518595662752782[209] = 1;
   out_5153518595662752782[210] = 0;
   out_5153518595662752782[211] = 0;
   out_5153518595662752782[212] = 0;
   out_5153518595662752782[213] = 0;
   out_5153518595662752782[214] = 0;
   out_5153518595662752782[215] = 0;
   out_5153518595662752782[216] = 0;
   out_5153518595662752782[217] = 0;
   out_5153518595662752782[218] = 0;
   out_5153518595662752782[219] = 0;
   out_5153518595662752782[220] = 0;
   out_5153518595662752782[221] = 0;
   out_5153518595662752782[222] = 0;
   out_5153518595662752782[223] = 0;
   out_5153518595662752782[224] = 0;
   out_5153518595662752782[225] = 0;
   out_5153518595662752782[226] = 0;
   out_5153518595662752782[227] = 0;
   out_5153518595662752782[228] = 1;
   out_5153518595662752782[229] = 0;
   out_5153518595662752782[230] = 0;
   out_5153518595662752782[231] = 0;
   out_5153518595662752782[232] = 0;
   out_5153518595662752782[233] = 0;
   out_5153518595662752782[234] = 0;
   out_5153518595662752782[235] = 0;
   out_5153518595662752782[236] = 0;
   out_5153518595662752782[237] = 0;
   out_5153518595662752782[238] = 0;
   out_5153518595662752782[239] = 0;
   out_5153518595662752782[240] = 0;
   out_5153518595662752782[241] = 0;
   out_5153518595662752782[242] = 0;
   out_5153518595662752782[243] = 0;
   out_5153518595662752782[244] = 0;
   out_5153518595662752782[245] = 0;
   out_5153518595662752782[246] = 0;
   out_5153518595662752782[247] = 1;
   out_5153518595662752782[248] = 0;
   out_5153518595662752782[249] = 0;
   out_5153518595662752782[250] = 0;
   out_5153518595662752782[251] = 0;
   out_5153518595662752782[252] = 0;
   out_5153518595662752782[253] = 0;
   out_5153518595662752782[254] = 0;
   out_5153518595662752782[255] = 0;
   out_5153518595662752782[256] = 0;
   out_5153518595662752782[257] = 0;
   out_5153518595662752782[258] = 0;
   out_5153518595662752782[259] = 0;
   out_5153518595662752782[260] = 0;
   out_5153518595662752782[261] = 0;
   out_5153518595662752782[262] = 0;
   out_5153518595662752782[263] = 0;
   out_5153518595662752782[264] = 0;
   out_5153518595662752782[265] = 0;
   out_5153518595662752782[266] = 1;
   out_5153518595662752782[267] = 0;
   out_5153518595662752782[268] = 0;
   out_5153518595662752782[269] = 0;
   out_5153518595662752782[270] = 0;
   out_5153518595662752782[271] = 0;
   out_5153518595662752782[272] = 0;
   out_5153518595662752782[273] = 0;
   out_5153518595662752782[274] = 0;
   out_5153518595662752782[275] = 0;
   out_5153518595662752782[276] = 0;
   out_5153518595662752782[277] = 0;
   out_5153518595662752782[278] = 0;
   out_5153518595662752782[279] = 0;
   out_5153518595662752782[280] = 0;
   out_5153518595662752782[281] = 0;
   out_5153518595662752782[282] = 0;
   out_5153518595662752782[283] = 0;
   out_5153518595662752782[284] = 0;
   out_5153518595662752782[285] = 1;
   out_5153518595662752782[286] = 0;
   out_5153518595662752782[287] = 0;
   out_5153518595662752782[288] = 0;
   out_5153518595662752782[289] = 0;
   out_5153518595662752782[290] = 0;
   out_5153518595662752782[291] = 0;
   out_5153518595662752782[292] = 0;
   out_5153518595662752782[293] = 0;
   out_5153518595662752782[294] = 0;
   out_5153518595662752782[295] = 0;
   out_5153518595662752782[296] = 0;
   out_5153518595662752782[297] = 0;
   out_5153518595662752782[298] = 0;
   out_5153518595662752782[299] = 0;
   out_5153518595662752782[300] = 0;
   out_5153518595662752782[301] = 0;
   out_5153518595662752782[302] = 0;
   out_5153518595662752782[303] = 0;
   out_5153518595662752782[304] = 1;
   out_5153518595662752782[305] = 0;
   out_5153518595662752782[306] = 0;
   out_5153518595662752782[307] = 0;
   out_5153518595662752782[308] = 0;
   out_5153518595662752782[309] = 0;
   out_5153518595662752782[310] = 0;
   out_5153518595662752782[311] = 0;
   out_5153518595662752782[312] = 0;
   out_5153518595662752782[313] = 0;
   out_5153518595662752782[314] = 0;
   out_5153518595662752782[315] = 0;
   out_5153518595662752782[316] = 0;
   out_5153518595662752782[317] = 0;
   out_5153518595662752782[318] = 0;
   out_5153518595662752782[319] = 0;
   out_5153518595662752782[320] = 0;
   out_5153518595662752782[321] = 0;
   out_5153518595662752782[322] = 0;
   out_5153518595662752782[323] = 1;
}
void h_4(double *state, double *unused, double *out_3441983837194168135) {
   out_3441983837194168135[0] = state[6] + state[9];
   out_3441983837194168135[1] = state[7] + state[10];
   out_3441983837194168135[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3792847385831294211) {
   out_3792847385831294211[0] = 0;
   out_3792847385831294211[1] = 0;
   out_3792847385831294211[2] = 0;
   out_3792847385831294211[3] = 0;
   out_3792847385831294211[4] = 0;
   out_3792847385831294211[5] = 0;
   out_3792847385831294211[6] = 1;
   out_3792847385831294211[7] = 0;
   out_3792847385831294211[8] = 0;
   out_3792847385831294211[9] = 1;
   out_3792847385831294211[10] = 0;
   out_3792847385831294211[11] = 0;
   out_3792847385831294211[12] = 0;
   out_3792847385831294211[13] = 0;
   out_3792847385831294211[14] = 0;
   out_3792847385831294211[15] = 0;
   out_3792847385831294211[16] = 0;
   out_3792847385831294211[17] = 0;
   out_3792847385831294211[18] = 0;
   out_3792847385831294211[19] = 0;
   out_3792847385831294211[20] = 0;
   out_3792847385831294211[21] = 0;
   out_3792847385831294211[22] = 0;
   out_3792847385831294211[23] = 0;
   out_3792847385831294211[24] = 0;
   out_3792847385831294211[25] = 1;
   out_3792847385831294211[26] = 0;
   out_3792847385831294211[27] = 0;
   out_3792847385831294211[28] = 1;
   out_3792847385831294211[29] = 0;
   out_3792847385831294211[30] = 0;
   out_3792847385831294211[31] = 0;
   out_3792847385831294211[32] = 0;
   out_3792847385831294211[33] = 0;
   out_3792847385831294211[34] = 0;
   out_3792847385831294211[35] = 0;
   out_3792847385831294211[36] = 0;
   out_3792847385831294211[37] = 0;
   out_3792847385831294211[38] = 0;
   out_3792847385831294211[39] = 0;
   out_3792847385831294211[40] = 0;
   out_3792847385831294211[41] = 0;
   out_3792847385831294211[42] = 0;
   out_3792847385831294211[43] = 0;
   out_3792847385831294211[44] = 1;
   out_3792847385831294211[45] = 0;
   out_3792847385831294211[46] = 0;
   out_3792847385831294211[47] = 1;
   out_3792847385831294211[48] = 0;
   out_3792847385831294211[49] = 0;
   out_3792847385831294211[50] = 0;
   out_3792847385831294211[51] = 0;
   out_3792847385831294211[52] = 0;
   out_3792847385831294211[53] = 0;
}
void h_10(double *state, double *unused, double *out_6864246601547225854) {
   out_6864246601547225854[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_6864246601547225854[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_6864246601547225854[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5871577252215708993) {
   out_5871577252215708993[0] = 0;
   out_5871577252215708993[1] = 9.8100000000000005*cos(state[1]);
   out_5871577252215708993[2] = 0;
   out_5871577252215708993[3] = 0;
   out_5871577252215708993[4] = -state[8];
   out_5871577252215708993[5] = state[7];
   out_5871577252215708993[6] = 0;
   out_5871577252215708993[7] = state[5];
   out_5871577252215708993[8] = -state[4];
   out_5871577252215708993[9] = 0;
   out_5871577252215708993[10] = 0;
   out_5871577252215708993[11] = 0;
   out_5871577252215708993[12] = 1;
   out_5871577252215708993[13] = 0;
   out_5871577252215708993[14] = 0;
   out_5871577252215708993[15] = 1;
   out_5871577252215708993[16] = 0;
   out_5871577252215708993[17] = 0;
   out_5871577252215708993[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5871577252215708993[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5871577252215708993[20] = 0;
   out_5871577252215708993[21] = state[8];
   out_5871577252215708993[22] = 0;
   out_5871577252215708993[23] = -state[6];
   out_5871577252215708993[24] = -state[5];
   out_5871577252215708993[25] = 0;
   out_5871577252215708993[26] = state[3];
   out_5871577252215708993[27] = 0;
   out_5871577252215708993[28] = 0;
   out_5871577252215708993[29] = 0;
   out_5871577252215708993[30] = 0;
   out_5871577252215708993[31] = 1;
   out_5871577252215708993[32] = 0;
   out_5871577252215708993[33] = 0;
   out_5871577252215708993[34] = 1;
   out_5871577252215708993[35] = 0;
   out_5871577252215708993[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5871577252215708993[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5871577252215708993[38] = 0;
   out_5871577252215708993[39] = -state[7];
   out_5871577252215708993[40] = state[6];
   out_5871577252215708993[41] = 0;
   out_5871577252215708993[42] = state[4];
   out_5871577252215708993[43] = -state[3];
   out_5871577252215708993[44] = 0;
   out_5871577252215708993[45] = 0;
   out_5871577252215708993[46] = 0;
   out_5871577252215708993[47] = 0;
   out_5871577252215708993[48] = 0;
   out_5871577252215708993[49] = 0;
   out_5871577252215708993[50] = 1;
   out_5871577252215708993[51] = 0;
   out_5871577252215708993[52] = 0;
   out_5871577252215708993[53] = 1;
}
void h_13(double *state, double *unused, double *out_3325053226247216097) {
   out_3325053226247216097[0] = state[3];
   out_3325053226247216097[1] = state[4];
   out_3325053226247216097[2] = state[5];
}
void H_13(double *state, double *unused, double *out_580573560498961410) {
   out_580573560498961410[0] = 0;
   out_580573560498961410[1] = 0;
   out_580573560498961410[2] = 0;
   out_580573560498961410[3] = 1;
   out_580573560498961410[4] = 0;
   out_580573560498961410[5] = 0;
   out_580573560498961410[6] = 0;
   out_580573560498961410[7] = 0;
   out_580573560498961410[8] = 0;
   out_580573560498961410[9] = 0;
   out_580573560498961410[10] = 0;
   out_580573560498961410[11] = 0;
   out_580573560498961410[12] = 0;
   out_580573560498961410[13] = 0;
   out_580573560498961410[14] = 0;
   out_580573560498961410[15] = 0;
   out_580573560498961410[16] = 0;
   out_580573560498961410[17] = 0;
   out_580573560498961410[18] = 0;
   out_580573560498961410[19] = 0;
   out_580573560498961410[20] = 0;
   out_580573560498961410[21] = 0;
   out_580573560498961410[22] = 1;
   out_580573560498961410[23] = 0;
   out_580573560498961410[24] = 0;
   out_580573560498961410[25] = 0;
   out_580573560498961410[26] = 0;
   out_580573560498961410[27] = 0;
   out_580573560498961410[28] = 0;
   out_580573560498961410[29] = 0;
   out_580573560498961410[30] = 0;
   out_580573560498961410[31] = 0;
   out_580573560498961410[32] = 0;
   out_580573560498961410[33] = 0;
   out_580573560498961410[34] = 0;
   out_580573560498961410[35] = 0;
   out_580573560498961410[36] = 0;
   out_580573560498961410[37] = 0;
   out_580573560498961410[38] = 0;
   out_580573560498961410[39] = 0;
   out_580573560498961410[40] = 0;
   out_580573560498961410[41] = 1;
   out_580573560498961410[42] = 0;
   out_580573560498961410[43] = 0;
   out_580573560498961410[44] = 0;
   out_580573560498961410[45] = 0;
   out_580573560498961410[46] = 0;
   out_580573560498961410[47] = 0;
   out_580573560498961410[48] = 0;
   out_580573560498961410[49] = 0;
   out_580573560498961410[50] = 0;
   out_580573560498961410[51] = 0;
   out_580573560498961410[52] = 0;
   out_580573560498961410[53] = 0;
}
void h_14(double *state, double *unused, double *out_7213076452181803827) {
   out_7213076452181803827[0] = state[6];
   out_7213076452181803827[1] = state[7];
   out_7213076452181803827[2] = state[8];
}
void H_14(double *state, double *unused, double *out_170393470508190318) {
   out_170393470508190318[0] = 0;
   out_170393470508190318[1] = 0;
   out_170393470508190318[2] = 0;
   out_170393470508190318[3] = 0;
   out_170393470508190318[4] = 0;
   out_170393470508190318[5] = 0;
   out_170393470508190318[6] = 1;
   out_170393470508190318[7] = 0;
   out_170393470508190318[8] = 0;
   out_170393470508190318[9] = 0;
   out_170393470508190318[10] = 0;
   out_170393470508190318[11] = 0;
   out_170393470508190318[12] = 0;
   out_170393470508190318[13] = 0;
   out_170393470508190318[14] = 0;
   out_170393470508190318[15] = 0;
   out_170393470508190318[16] = 0;
   out_170393470508190318[17] = 0;
   out_170393470508190318[18] = 0;
   out_170393470508190318[19] = 0;
   out_170393470508190318[20] = 0;
   out_170393470508190318[21] = 0;
   out_170393470508190318[22] = 0;
   out_170393470508190318[23] = 0;
   out_170393470508190318[24] = 0;
   out_170393470508190318[25] = 1;
   out_170393470508190318[26] = 0;
   out_170393470508190318[27] = 0;
   out_170393470508190318[28] = 0;
   out_170393470508190318[29] = 0;
   out_170393470508190318[30] = 0;
   out_170393470508190318[31] = 0;
   out_170393470508190318[32] = 0;
   out_170393470508190318[33] = 0;
   out_170393470508190318[34] = 0;
   out_170393470508190318[35] = 0;
   out_170393470508190318[36] = 0;
   out_170393470508190318[37] = 0;
   out_170393470508190318[38] = 0;
   out_170393470508190318[39] = 0;
   out_170393470508190318[40] = 0;
   out_170393470508190318[41] = 0;
   out_170393470508190318[42] = 0;
   out_170393470508190318[43] = 0;
   out_170393470508190318[44] = 1;
   out_170393470508190318[45] = 0;
   out_170393470508190318[46] = 0;
   out_170393470508190318[47] = 0;
   out_170393470508190318[48] = 0;
   out_170393470508190318[49] = 0;
   out_170393470508190318[50] = 0;
   out_170393470508190318[51] = 0;
   out_170393470508190318[52] = 0;
   out_170393470508190318[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_2803054085873220166) {
  err_fun(nom_x, delta_x, out_2803054085873220166);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_870718263858356541) {
  inv_err_fun(nom_x, true_x, out_870718263858356541);
}
void pose_H_mod_fun(double *state, double *out_245560868528396178) {
  H_mod_fun(state, out_245560868528396178);
}
void pose_f_fun(double *state, double dt, double *out_8465405656783528291) {
  f_fun(state,  dt, out_8465405656783528291);
}
void pose_F_fun(double *state, double dt, double *out_5153518595662752782) {
  F_fun(state,  dt, out_5153518595662752782);
}
void pose_h_4(double *state, double *unused, double *out_3441983837194168135) {
  h_4(state, unused, out_3441983837194168135);
}
void pose_H_4(double *state, double *unused, double *out_3792847385831294211) {
  H_4(state, unused, out_3792847385831294211);
}
void pose_h_10(double *state, double *unused, double *out_6864246601547225854) {
  h_10(state, unused, out_6864246601547225854);
}
void pose_H_10(double *state, double *unused, double *out_5871577252215708993) {
  H_10(state, unused, out_5871577252215708993);
}
void pose_h_13(double *state, double *unused, double *out_3325053226247216097) {
  h_13(state, unused, out_3325053226247216097);
}
void pose_H_13(double *state, double *unused, double *out_580573560498961410) {
  H_13(state, unused, out_580573560498961410);
}
void pose_h_14(double *state, double *unused, double *out_7213076452181803827) {
  h_14(state, unused, out_7213076452181803827);
}
void pose_H_14(double *state, double *unused, double *out_170393470508190318) {
  H_14(state, unused, out_170393470508190318);
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
