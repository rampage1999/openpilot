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
void err_fun(double *nom_x, double *delta_x, double *out_8069274513708895969) {
   out_8069274513708895969[0] = delta_x[0] + nom_x[0];
   out_8069274513708895969[1] = delta_x[1] + nom_x[1];
   out_8069274513708895969[2] = delta_x[2] + nom_x[2];
   out_8069274513708895969[3] = delta_x[3] + nom_x[3];
   out_8069274513708895969[4] = delta_x[4] + nom_x[4];
   out_8069274513708895969[5] = delta_x[5] + nom_x[5];
   out_8069274513708895969[6] = delta_x[6] + nom_x[6];
   out_8069274513708895969[7] = delta_x[7] + nom_x[7];
   out_8069274513708895969[8] = delta_x[8] + nom_x[8];
   out_8069274513708895969[9] = delta_x[9] + nom_x[9];
   out_8069274513708895969[10] = delta_x[10] + nom_x[10];
   out_8069274513708895969[11] = delta_x[11] + nom_x[11];
   out_8069274513708895969[12] = delta_x[12] + nom_x[12];
   out_8069274513708895969[13] = delta_x[13] + nom_x[13];
   out_8069274513708895969[14] = delta_x[14] + nom_x[14];
   out_8069274513708895969[15] = delta_x[15] + nom_x[15];
   out_8069274513708895969[16] = delta_x[16] + nom_x[16];
   out_8069274513708895969[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6148460760368505675) {
   out_6148460760368505675[0] = -nom_x[0] + true_x[0];
   out_6148460760368505675[1] = -nom_x[1] + true_x[1];
   out_6148460760368505675[2] = -nom_x[2] + true_x[2];
   out_6148460760368505675[3] = -nom_x[3] + true_x[3];
   out_6148460760368505675[4] = -nom_x[4] + true_x[4];
   out_6148460760368505675[5] = -nom_x[5] + true_x[5];
   out_6148460760368505675[6] = -nom_x[6] + true_x[6];
   out_6148460760368505675[7] = -nom_x[7] + true_x[7];
   out_6148460760368505675[8] = -nom_x[8] + true_x[8];
   out_6148460760368505675[9] = -nom_x[9] + true_x[9];
   out_6148460760368505675[10] = -nom_x[10] + true_x[10];
   out_6148460760368505675[11] = -nom_x[11] + true_x[11];
   out_6148460760368505675[12] = -nom_x[12] + true_x[12];
   out_6148460760368505675[13] = -nom_x[13] + true_x[13];
   out_6148460760368505675[14] = -nom_x[14] + true_x[14];
   out_6148460760368505675[15] = -nom_x[15] + true_x[15];
   out_6148460760368505675[16] = -nom_x[16] + true_x[16];
   out_6148460760368505675[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3716754627317504890) {
   out_3716754627317504890[0] = 1.0;
   out_3716754627317504890[1] = 0.0;
   out_3716754627317504890[2] = 0.0;
   out_3716754627317504890[3] = 0.0;
   out_3716754627317504890[4] = 0.0;
   out_3716754627317504890[5] = 0.0;
   out_3716754627317504890[6] = 0.0;
   out_3716754627317504890[7] = 0.0;
   out_3716754627317504890[8] = 0.0;
   out_3716754627317504890[9] = 0.0;
   out_3716754627317504890[10] = 0.0;
   out_3716754627317504890[11] = 0.0;
   out_3716754627317504890[12] = 0.0;
   out_3716754627317504890[13] = 0.0;
   out_3716754627317504890[14] = 0.0;
   out_3716754627317504890[15] = 0.0;
   out_3716754627317504890[16] = 0.0;
   out_3716754627317504890[17] = 0.0;
   out_3716754627317504890[18] = 0.0;
   out_3716754627317504890[19] = 1.0;
   out_3716754627317504890[20] = 0.0;
   out_3716754627317504890[21] = 0.0;
   out_3716754627317504890[22] = 0.0;
   out_3716754627317504890[23] = 0.0;
   out_3716754627317504890[24] = 0.0;
   out_3716754627317504890[25] = 0.0;
   out_3716754627317504890[26] = 0.0;
   out_3716754627317504890[27] = 0.0;
   out_3716754627317504890[28] = 0.0;
   out_3716754627317504890[29] = 0.0;
   out_3716754627317504890[30] = 0.0;
   out_3716754627317504890[31] = 0.0;
   out_3716754627317504890[32] = 0.0;
   out_3716754627317504890[33] = 0.0;
   out_3716754627317504890[34] = 0.0;
   out_3716754627317504890[35] = 0.0;
   out_3716754627317504890[36] = 0.0;
   out_3716754627317504890[37] = 0.0;
   out_3716754627317504890[38] = 1.0;
   out_3716754627317504890[39] = 0.0;
   out_3716754627317504890[40] = 0.0;
   out_3716754627317504890[41] = 0.0;
   out_3716754627317504890[42] = 0.0;
   out_3716754627317504890[43] = 0.0;
   out_3716754627317504890[44] = 0.0;
   out_3716754627317504890[45] = 0.0;
   out_3716754627317504890[46] = 0.0;
   out_3716754627317504890[47] = 0.0;
   out_3716754627317504890[48] = 0.0;
   out_3716754627317504890[49] = 0.0;
   out_3716754627317504890[50] = 0.0;
   out_3716754627317504890[51] = 0.0;
   out_3716754627317504890[52] = 0.0;
   out_3716754627317504890[53] = 0.0;
   out_3716754627317504890[54] = 0.0;
   out_3716754627317504890[55] = 0.0;
   out_3716754627317504890[56] = 0.0;
   out_3716754627317504890[57] = 1.0;
   out_3716754627317504890[58] = 0.0;
   out_3716754627317504890[59] = 0.0;
   out_3716754627317504890[60] = 0.0;
   out_3716754627317504890[61] = 0.0;
   out_3716754627317504890[62] = 0.0;
   out_3716754627317504890[63] = 0.0;
   out_3716754627317504890[64] = 0.0;
   out_3716754627317504890[65] = 0.0;
   out_3716754627317504890[66] = 0.0;
   out_3716754627317504890[67] = 0.0;
   out_3716754627317504890[68] = 0.0;
   out_3716754627317504890[69] = 0.0;
   out_3716754627317504890[70] = 0.0;
   out_3716754627317504890[71] = 0.0;
   out_3716754627317504890[72] = 0.0;
   out_3716754627317504890[73] = 0.0;
   out_3716754627317504890[74] = 0.0;
   out_3716754627317504890[75] = 0.0;
   out_3716754627317504890[76] = 1.0;
   out_3716754627317504890[77] = 0.0;
   out_3716754627317504890[78] = 0.0;
   out_3716754627317504890[79] = 0.0;
   out_3716754627317504890[80] = 0.0;
   out_3716754627317504890[81] = 0.0;
   out_3716754627317504890[82] = 0.0;
   out_3716754627317504890[83] = 0.0;
   out_3716754627317504890[84] = 0.0;
   out_3716754627317504890[85] = 0.0;
   out_3716754627317504890[86] = 0.0;
   out_3716754627317504890[87] = 0.0;
   out_3716754627317504890[88] = 0.0;
   out_3716754627317504890[89] = 0.0;
   out_3716754627317504890[90] = 0.0;
   out_3716754627317504890[91] = 0.0;
   out_3716754627317504890[92] = 0.0;
   out_3716754627317504890[93] = 0.0;
   out_3716754627317504890[94] = 0.0;
   out_3716754627317504890[95] = 1.0;
   out_3716754627317504890[96] = 0.0;
   out_3716754627317504890[97] = 0.0;
   out_3716754627317504890[98] = 0.0;
   out_3716754627317504890[99] = 0.0;
   out_3716754627317504890[100] = 0.0;
   out_3716754627317504890[101] = 0.0;
   out_3716754627317504890[102] = 0.0;
   out_3716754627317504890[103] = 0.0;
   out_3716754627317504890[104] = 0.0;
   out_3716754627317504890[105] = 0.0;
   out_3716754627317504890[106] = 0.0;
   out_3716754627317504890[107] = 0.0;
   out_3716754627317504890[108] = 0.0;
   out_3716754627317504890[109] = 0.0;
   out_3716754627317504890[110] = 0.0;
   out_3716754627317504890[111] = 0.0;
   out_3716754627317504890[112] = 0.0;
   out_3716754627317504890[113] = 0.0;
   out_3716754627317504890[114] = 1.0;
   out_3716754627317504890[115] = 0.0;
   out_3716754627317504890[116] = 0.0;
   out_3716754627317504890[117] = 0.0;
   out_3716754627317504890[118] = 0.0;
   out_3716754627317504890[119] = 0.0;
   out_3716754627317504890[120] = 0.0;
   out_3716754627317504890[121] = 0.0;
   out_3716754627317504890[122] = 0.0;
   out_3716754627317504890[123] = 0.0;
   out_3716754627317504890[124] = 0.0;
   out_3716754627317504890[125] = 0.0;
   out_3716754627317504890[126] = 0.0;
   out_3716754627317504890[127] = 0.0;
   out_3716754627317504890[128] = 0.0;
   out_3716754627317504890[129] = 0.0;
   out_3716754627317504890[130] = 0.0;
   out_3716754627317504890[131] = 0.0;
   out_3716754627317504890[132] = 0.0;
   out_3716754627317504890[133] = 1.0;
   out_3716754627317504890[134] = 0.0;
   out_3716754627317504890[135] = 0.0;
   out_3716754627317504890[136] = 0.0;
   out_3716754627317504890[137] = 0.0;
   out_3716754627317504890[138] = 0.0;
   out_3716754627317504890[139] = 0.0;
   out_3716754627317504890[140] = 0.0;
   out_3716754627317504890[141] = 0.0;
   out_3716754627317504890[142] = 0.0;
   out_3716754627317504890[143] = 0.0;
   out_3716754627317504890[144] = 0.0;
   out_3716754627317504890[145] = 0.0;
   out_3716754627317504890[146] = 0.0;
   out_3716754627317504890[147] = 0.0;
   out_3716754627317504890[148] = 0.0;
   out_3716754627317504890[149] = 0.0;
   out_3716754627317504890[150] = 0.0;
   out_3716754627317504890[151] = 0.0;
   out_3716754627317504890[152] = 1.0;
   out_3716754627317504890[153] = 0.0;
   out_3716754627317504890[154] = 0.0;
   out_3716754627317504890[155] = 0.0;
   out_3716754627317504890[156] = 0.0;
   out_3716754627317504890[157] = 0.0;
   out_3716754627317504890[158] = 0.0;
   out_3716754627317504890[159] = 0.0;
   out_3716754627317504890[160] = 0.0;
   out_3716754627317504890[161] = 0.0;
   out_3716754627317504890[162] = 0.0;
   out_3716754627317504890[163] = 0.0;
   out_3716754627317504890[164] = 0.0;
   out_3716754627317504890[165] = 0.0;
   out_3716754627317504890[166] = 0.0;
   out_3716754627317504890[167] = 0.0;
   out_3716754627317504890[168] = 0.0;
   out_3716754627317504890[169] = 0.0;
   out_3716754627317504890[170] = 0.0;
   out_3716754627317504890[171] = 1.0;
   out_3716754627317504890[172] = 0.0;
   out_3716754627317504890[173] = 0.0;
   out_3716754627317504890[174] = 0.0;
   out_3716754627317504890[175] = 0.0;
   out_3716754627317504890[176] = 0.0;
   out_3716754627317504890[177] = 0.0;
   out_3716754627317504890[178] = 0.0;
   out_3716754627317504890[179] = 0.0;
   out_3716754627317504890[180] = 0.0;
   out_3716754627317504890[181] = 0.0;
   out_3716754627317504890[182] = 0.0;
   out_3716754627317504890[183] = 0.0;
   out_3716754627317504890[184] = 0.0;
   out_3716754627317504890[185] = 0.0;
   out_3716754627317504890[186] = 0.0;
   out_3716754627317504890[187] = 0.0;
   out_3716754627317504890[188] = 0.0;
   out_3716754627317504890[189] = 0.0;
   out_3716754627317504890[190] = 1.0;
   out_3716754627317504890[191] = 0.0;
   out_3716754627317504890[192] = 0.0;
   out_3716754627317504890[193] = 0.0;
   out_3716754627317504890[194] = 0.0;
   out_3716754627317504890[195] = 0.0;
   out_3716754627317504890[196] = 0.0;
   out_3716754627317504890[197] = 0.0;
   out_3716754627317504890[198] = 0.0;
   out_3716754627317504890[199] = 0.0;
   out_3716754627317504890[200] = 0.0;
   out_3716754627317504890[201] = 0.0;
   out_3716754627317504890[202] = 0.0;
   out_3716754627317504890[203] = 0.0;
   out_3716754627317504890[204] = 0.0;
   out_3716754627317504890[205] = 0.0;
   out_3716754627317504890[206] = 0.0;
   out_3716754627317504890[207] = 0.0;
   out_3716754627317504890[208] = 0.0;
   out_3716754627317504890[209] = 1.0;
   out_3716754627317504890[210] = 0.0;
   out_3716754627317504890[211] = 0.0;
   out_3716754627317504890[212] = 0.0;
   out_3716754627317504890[213] = 0.0;
   out_3716754627317504890[214] = 0.0;
   out_3716754627317504890[215] = 0.0;
   out_3716754627317504890[216] = 0.0;
   out_3716754627317504890[217] = 0.0;
   out_3716754627317504890[218] = 0.0;
   out_3716754627317504890[219] = 0.0;
   out_3716754627317504890[220] = 0.0;
   out_3716754627317504890[221] = 0.0;
   out_3716754627317504890[222] = 0.0;
   out_3716754627317504890[223] = 0.0;
   out_3716754627317504890[224] = 0.0;
   out_3716754627317504890[225] = 0.0;
   out_3716754627317504890[226] = 0.0;
   out_3716754627317504890[227] = 0.0;
   out_3716754627317504890[228] = 1.0;
   out_3716754627317504890[229] = 0.0;
   out_3716754627317504890[230] = 0.0;
   out_3716754627317504890[231] = 0.0;
   out_3716754627317504890[232] = 0.0;
   out_3716754627317504890[233] = 0.0;
   out_3716754627317504890[234] = 0.0;
   out_3716754627317504890[235] = 0.0;
   out_3716754627317504890[236] = 0.0;
   out_3716754627317504890[237] = 0.0;
   out_3716754627317504890[238] = 0.0;
   out_3716754627317504890[239] = 0.0;
   out_3716754627317504890[240] = 0.0;
   out_3716754627317504890[241] = 0.0;
   out_3716754627317504890[242] = 0.0;
   out_3716754627317504890[243] = 0.0;
   out_3716754627317504890[244] = 0.0;
   out_3716754627317504890[245] = 0.0;
   out_3716754627317504890[246] = 0.0;
   out_3716754627317504890[247] = 1.0;
   out_3716754627317504890[248] = 0.0;
   out_3716754627317504890[249] = 0.0;
   out_3716754627317504890[250] = 0.0;
   out_3716754627317504890[251] = 0.0;
   out_3716754627317504890[252] = 0.0;
   out_3716754627317504890[253] = 0.0;
   out_3716754627317504890[254] = 0.0;
   out_3716754627317504890[255] = 0.0;
   out_3716754627317504890[256] = 0.0;
   out_3716754627317504890[257] = 0.0;
   out_3716754627317504890[258] = 0.0;
   out_3716754627317504890[259] = 0.0;
   out_3716754627317504890[260] = 0.0;
   out_3716754627317504890[261] = 0.0;
   out_3716754627317504890[262] = 0.0;
   out_3716754627317504890[263] = 0.0;
   out_3716754627317504890[264] = 0.0;
   out_3716754627317504890[265] = 0.0;
   out_3716754627317504890[266] = 1.0;
   out_3716754627317504890[267] = 0.0;
   out_3716754627317504890[268] = 0.0;
   out_3716754627317504890[269] = 0.0;
   out_3716754627317504890[270] = 0.0;
   out_3716754627317504890[271] = 0.0;
   out_3716754627317504890[272] = 0.0;
   out_3716754627317504890[273] = 0.0;
   out_3716754627317504890[274] = 0.0;
   out_3716754627317504890[275] = 0.0;
   out_3716754627317504890[276] = 0.0;
   out_3716754627317504890[277] = 0.0;
   out_3716754627317504890[278] = 0.0;
   out_3716754627317504890[279] = 0.0;
   out_3716754627317504890[280] = 0.0;
   out_3716754627317504890[281] = 0.0;
   out_3716754627317504890[282] = 0.0;
   out_3716754627317504890[283] = 0.0;
   out_3716754627317504890[284] = 0.0;
   out_3716754627317504890[285] = 1.0;
   out_3716754627317504890[286] = 0.0;
   out_3716754627317504890[287] = 0.0;
   out_3716754627317504890[288] = 0.0;
   out_3716754627317504890[289] = 0.0;
   out_3716754627317504890[290] = 0.0;
   out_3716754627317504890[291] = 0.0;
   out_3716754627317504890[292] = 0.0;
   out_3716754627317504890[293] = 0.0;
   out_3716754627317504890[294] = 0.0;
   out_3716754627317504890[295] = 0.0;
   out_3716754627317504890[296] = 0.0;
   out_3716754627317504890[297] = 0.0;
   out_3716754627317504890[298] = 0.0;
   out_3716754627317504890[299] = 0.0;
   out_3716754627317504890[300] = 0.0;
   out_3716754627317504890[301] = 0.0;
   out_3716754627317504890[302] = 0.0;
   out_3716754627317504890[303] = 0.0;
   out_3716754627317504890[304] = 1.0;
   out_3716754627317504890[305] = 0.0;
   out_3716754627317504890[306] = 0.0;
   out_3716754627317504890[307] = 0.0;
   out_3716754627317504890[308] = 0.0;
   out_3716754627317504890[309] = 0.0;
   out_3716754627317504890[310] = 0.0;
   out_3716754627317504890[311] = 0.0;
   out_3716754627317504890[312] = 0.0;
   out_3716754627317504890[313] = 0.0;
   out_3716754627317504890[314] = 0.0;
   out_3716754627317504890[315] = 0.0;
   out_3716754627317504890[316] = 0.0;
   out_3716754627317504890[317] = 0.0;
   out_3716754627317504890[318] = 0.0;
   out_3716754627317504890[319] = 0.0;
   out_3716754627317504890[320] = 0.0;
   out_3716754627317504890[321] = 0.0;
   out_3716754627317504890[322] = 0.0;
   out_3716754627317504890[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_4855167580946130027) {
   out_4855167580946130027[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_4855167580946130027[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_4855167580946130027[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_4855167580946130027[3] = dt*state[12] + state[3];
   out_4855167580946130027[4] = dt*state[13] + state[4];
   out_4855167580946130027[5] = dt*state[14] + state[5];
   out_4855167580946130027[6] = state[6];
   out_4855167580946130027[7] = state[7];
   out_4855167580946130027[8] = state[8];
   out_4855167580946130027[9] = state[9];
   out_4855167580946130027[10] = state[10];
   out_4855167580946130027[11] = state[11];
   out_4855167580946130027[12] = state[12];
   out_4855167580946130027[13] = state[13];
   out_4855167580946130027[14] = state[14];
   out_4855167580946130027[15] = state[15];
   out_4855167580946130027[16] = state[16];
   out_4855167580946130027[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4420770900431173050) {
   out_4420770900431173050[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4420770900431173050[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4420770900431173050[2] = 0;
   out_4420770900431173050[3] = 0;
   out_4420770900431173050[4] = 0;
   out_4420770900431173050[5] = 0;
   out_4420770900431173050[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4420770900431173050[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4420770900431173050[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4420770900431173050[9] = 0;
   out_4420770900431173050[10] = 0;
   out_4420770900431173050[11] = 0;
   out_4420770900431173050[12] = 0;
   out_4420770900431173050[13] = 0;
   out_4420770900431173050[14] = 0;
   out_4420770900431173050[15] = 0;
   out_4420770900431173050[16] = 0;
   out_4420770900431173050[17] = 0;
   out_4420770900431173050[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4420770900431173050[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4420770900431173050[20] = 0;
   out_4420770900431173050[21] = 0;
   out_4420770900431173050[22] = 0;
   out_4420770900431173050[23] = 0;
   out_4420770900431173050[24] = 0;
   out_4420770900431173050[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4420770900431173050[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4420770900431173050[27] = 0;
   out_4420770900431173050[28] = 0;
   out_4420770900431173050[29] = 0;
   out_4420770900431173050[30] = 0;
   out_4420770900431173050[31] = 0;
   out_4420770900431173050[32] = 0;
   out_4420770900431173050[33] = 0;
   out_4420770900431173050[34] = 0;
   out_4420770900431173050[35] = 0;
   out_4420770900431173050[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4420770900431173050[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4420770900431173050[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4420770900431173050[39] = 0;
   out_4420770900431173050[40] = 0;
   out_4420770900431173050[41] = 0;
   out_4420770900431173050[42] = 0;
   out_4420770900431173050[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4420770900431173050[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4420770900431173050[45] = 0;
   out_4420770900431173050[46] = 0;
   out_4420770900431173050[47] = 0;
   out_4420770900431173050[48] = 0;
   out_4420770900431173050[49] = 0;
   out_4420770900431173050[50] = 0;
   out_4420770900431173050[51] = 0;
   out_4420770900431173050[52] = 0;
   out_4420770900431173050[53] = 0;
   out_4420770900431173050[54] = 0;
   out_4420770900431173050[55] = 0;
   out_4420770900431173050[56] = 0;
   out_4420770900431173050[57] = 1;
   out_4420770900431173050[58] = 0;
   out_4420770900431173050[59] = 0;
   out_4420770900431173050[60] = 0;
   out_4420770900431173050[61] = 0;
   out_4420770900431173050[62] = 0;
   out_4420770900431173050[63] = 0;
   out_4420770900431173050[64] = 0;
   out_4420770900431173050[65] = 0;
   out_4420770900431173050[66] = dt;
   out_4420770900431173050[67] = 0;
   out_4420770900431173050[68] = 0;
   out_4420770900431173050[69] = 0;
   out_4420770900431173050[70] = 0;
   out_4420770900431173050[71] = 0;
   out_4420770900431173050[72] = 0;
   out_4420770900431173050[73] = 0;
   out_4420770900431173050[74] = 0;
   out_4420770900431173050[75] = 0;
   out_4420770900431173050[76] = 1;
   out_4420770900431173050[77] = 0;
   out_4420770900431173050[78] = 0;
   out_4420770900431173050[79] = 0;
   out_4420770900431173050[80] = 0;
   out_4420770900431173050[81] = 0;
   out_4420770900431173050[82] = 0;
   out_4420770900431173050[83] = 0;
   out_4420770900431173050[84] = 0;
   out_4420770900431173050[85] = dt;
   out_4420770900431173050[86] = 0;
   out_4420770900431173050[87] = 0;
   out_4420770900431173050[88] = 0;
   out_4420770900431173050[89] = 0;
   out_4420770900431173050[90] = 0;
   out_4420770900431173050[91] = 0;
   out_4420770900431173050[92] = 0;
   out_4420770900431173050[93] = 0;
   out_4420770900431173050[94] = 0;
   out_4420770900431173050[95] = 1;
   out_4420770900431173050[96] = 0;
   out_4420770900431173050[97] = 0;
   out_4420770900431173050[98] = 0;
   out_4420770900431173050[99] = 0;
   out_4420770900431173050[100] = 0;
   out_4420770900431173050[101] = 0;
   out_4420770900431173050[102] = 0;
   out_4420770900431173050[103] = 0;
   out_4420770900431173050[104] = dt;
   out_4420770900431173050[105] = 0;
   out_4420770900431173050[106] = 0;
   out_4420770900431173050[107] = 0;
   out_4420770900431173050[108] = 0;
   out_4420770900431173050[109] = 0;
   out_4420770900431173050[110] = 0;
   out_4420770900431173050[111] = 0;
   out_4420770900431173050[112] = 0;
   out_4420770900431173050[113] = 0;
   out_4420770900431173050[114] = 1;
   out_4420770900431173050[115] = 0;
   out_4420770900431173050[116] = 0;
   out_4420770900431173050[117] = 0;
   out_4420770900431173050[118] = 0;
   out_4420770900431173050[119] = 0;
   out_4420770900431173050[120] = 0;
   out_4420770900431173050[121] = 0;
   out_4420770900431173050[122] = 0;
   out_4420770900431173050[123] = 0;
   out_4420770900431173050[124] = 0;
   out_4420770900431173050[125] = 0;
   out_4420770900431173050[126] = 0;
   out_4420770900431173050[127] = 0;
   out_4420770900431173050[128] = 0;
   out_4420770900431173050[129] = 0;
   out_4420770900431173050[130] = 0;
   out_4420770900431173050[131] = 0;
   out_4420770900431173050[132] = 0;
   out_4420770900431173050[133] = 1;
   out_4420770900431173050[134] = 0;
   out_4420770900431173050[135] = 0;
   out_4420770900431173050[136] = 0;
   out_4420770900431173050[137] = 0;
   out_4420770900431173050[138] = 0;
   out_4420770900431173050[139] = 0;
   out_4420770900431173050[140] = 0;
   out_4420770900431173050[141] = 0;
   out_4420770900431173050[142] = 0;
   out_4420770900431173050[143] = 0;
   out_4420770900431173050[144] = 0;
   out_4420770900431173050[145] = 0;
   out_4420770900431173050[146] = 0;
   out_4420770900431173050[147] = 0;
   out_4420770900431173050[148] = 0;
   out_4420770900431173050[149] = 0;
   out_4420770900431173050[150] = 0;
   out_4420770900431173050[151] = 0;
   out_4420770900431173050[152] = 1;
   out_4420770900431173050[153] = 0;
   out_4420770900431173050[154] = 0;
   out_4420770900431173050[155] = 0;
   out_4420770900431173050[156] = 0;
   out_4420770900431173050[157] = 0;
   out_4420770900431173050[158] = 0;
   out_4420770900431173050[159] = 0;
   out_4420770900431173050[160] = 0;
   out_4420770900431173050[161] = 0;
   out_4420770900431173050[162] = 0;
   out_4420770900431173050[163] = 0;
   out_4420770900431173050[164] = 0;
   out_4420770900431173050[165] = 0;
   out_4420770900431173050[166] = 0;
   out_4420770900431173050[167] = 0;
   out_4420770900431173050[168] = 0;
   out_4420770900431173050[169] = 0;
   out_4420770900431173050[170] = 0;
   out_4420770900431173050[171] = 1;
   out_4420770900431173050[172] = 0;
   out_4420770900431173050[173] = 0;
   out_4420770900431173050[174] = 0;
   out_4420770900431173050[175] = 0;
   out_4420770900431173050[176] = 0;
   out_4420770900431173050[177] = 0;
   out_4420770900431173050[178] = 0;
   out_4420770900431173050[179] = 0;
   out_4420770900431173050[180] = 0;
   out_4420770900431173050[181] = 0;
   out_4420770900431173050[182] = 0;
   out_4420770900431173050[183] = 0;
   out_4420770900431173050[184] = 0;
   out_4420770900431173050[185] = 0;
   out_4420770900431173050[186] = 0;
   out_4420770900431173050[187] = 0;
   out_4420770900431173050[188] = 0;
   out_4420770900431173050[189] = 0;
   out_4420770900431173050[190] = 1;
   out_4420770900431173050[191] = 0;
   out_4420770900431173050[192] = 0;
   out_4420770900431173050[193] = 0;
   out_4420770900431173050[194] = 0;
   out_4420770900431173050[195] = 0;
   out_4420770900431173050[196] = 0;
   out_4420770900431173050[197] = 0;
   out_4420770900431173050[198] = 0;
   out_4420770900431173050[199] = 0;
   out_4420770900431173050[200] = 0;
   out_4420770900431173050[201] = 0;
   out_4420770900431173050[202] = 0;
   out_4420770900431173050[203] = 0;
   out_4420770900431173050[204] = 0;
   out_4420770900431173050[205] = 0;
   out_4420770900431173050[206] = 0;
   out_4420770900431173050[207] = 0;
   out_4420770900431173050[208] = 0;
   out_4420770900431173050[209] = 1;
   out_4420770900431173050[210] = 0;
   out_4420770900431173050[211] = 0;
   out_4420770900431173050[212] = 0;
   out_4420770900431173050[213] = 0;
   out_4420770900431173050[214] = 0;
   out_4420770900431173050[215] = 0;
   out_4420770900431173050[216] = 0;
   out_4420770900431173050[217] = 0;
   out_4420770900431173050[218] = 0;
   out_4420770900431173050[219] = 0;
   out_4420770900431173050[220] = 0;
   out_4420770900431173050[221] = 0;
   out_4420770900431173050[222] = 0;
   out_4420770900431173050[223] = 0;
   out_4420770900431173050[224] = 0;
   out_4420770900431173050[225] = 0;
   out_4420770900431173050[226] = 0;
   out_4420770900431173050[227] = 0;
   out_4420770900431173050[228] = 1;
   out_4420770900431173050[229] = 0;
   out_4420770900431173050[230] = 0;
   out_4420770900431173050[231] = 0;
   out_4420770900431173050[232] = 0;
   out_4420770900431173050[233] = 0;
   out_4420770900431173050[234] = 0;
   out_4420770900431173050[235] = 0;
   out_4420770900431173050[236] = 0;
   out_4420770900431173050[237] = 0;
   out_4420770900431173050[238] = 0;
   out_4420770900431173050[239] = 0;
   out_4420770900431173050[240] = 0;
   out_4420770900431173050[241] = 0;
   out_4420770900431173050[242] = 0;
   out_4420770900431173050[243] = 0;
   out_4420770900431173050[244] = 0;
   out_4420770900431173050[245] = 0;
   out_4420770900431173050[246] = 0;
   out_4420770900431173050[247] = 1;
   out_4420770900431173050[248] = 0;
   out_4420770900431173050[249] = 0;
   out_4420770900431173050[250] = 0;
   out_4420770900431173050[251] = 0;
   out_4420770900431173050[252] = 0;
   out_4420770900431173050[253] = 0;
   out_4420770900431173050[254] = 0;
   out_4420770900431173050[255] = 0;
   out_4420770900431173050[256] = 0;
   out_4420770900431173050[257] = 0;
   out_4420770900431173050[258] = 0;
   out_4420770900431173050[259] = 0;
   out_4420770900431173050[260] = 0;
   out_4420770900431173050[261] = 0;
   out_4420770900431173050[262] = 0;
   out_4420770900431173050[263] = 0;
   out_4420770900431173050[264] = 0;
   out_4420770900431173050[265] = 0;
   out_4420770900431173050[266] = 1;
   out_4420770900431173050[267] = 0;
   out_4420770900431173050[268] = 0;
   out_4420770900431173050[269] = 0;
   out_4420770900431173050[270] = 0;
   out_4420770900431173050[271] = 0;
   out_4420770900431173050[272] = 0;
   out_4420770900431173050[273] = 0;
   out_4420770900431173050[274] = 0;
   out_4420770900431173050[275] = 0;
   out_4420770900431173050[276] = 0;
   out_4420770900431173050[277] = 0;
   out_4420770900431173050[278] = 0;
   out_4420770900431173050[279] = 0;
   out_4420770900431173050[280] = 0;
   out_4420770900431173050[281] = 0;
   out_4420770900431173050[282] = 0;
   out_4420770900431173050[283] = 0;
   out_4420770900431173050[284] = 0;
   out_4420770900431173050[285] = 1;
   out_4420770900431173050[286] = 0;
   out_4420770900431173050[287] = 0;
   out_4420770900431173050[288] = 0;
   out_4420770900431173050[289] = 0;
   out_4420770900431173050[290] = 0;
   out_4420770900431173050[291] = 0;
   out_4420770900431173050[292] = 0;
   out_4420770900431173050[293] = 0;
   out_4420770900431173050[294] = 0;
   out_4420770900431173050[295] = 0;
   out_4420770900431173050[296] = 0;
   out_4420770900431173050[297] = 0;
   out_4420770900431173050[298] = 0;
   out_4420770900431173050[299] = 0;
   out_4420770900431173050[300] = 0;
   out_4420770900431173050[301] = 0;
   out_4420770900431173050[302] = 0;
   out_4420770900431173050[303] = 0;
   out_4420770900431173050[304] = 1;
   out_4420770900431173050[305] = 0;
   out_4420770900431173050[306] = 0;
   out_4420770900431173050[307] = 0;
   out_4420770900431173050[308] = 0;
   out_4420770900431173050[309] = 0;
   out_4420770900431173050[310] = 0;
   out_4420770900431173050[311] = 0;
   out_4420770900431173050[312] = 0;
   out_4420770900431173050[313] = 0;
   out_4420770900431173050[314] = 0;
   out_4420770900431173050[315] = 0;
   out_4420770900431173050[316] = 0;
   out_4420770900431173050[317] = 0;
   out_4420770900431173050[318] = 0;
   out_4420770900431173050[319] = 0;
   out_4420770900431173050[320] = 0;
   out_4420770900431173050[321] = 0;
   out_4420770900431173050[322] = 0;
   out_4420770900431173050[323] = 1;
}
void h_4(double *state, double *unused, double *out_169586844375619970) {
   out_169586844375619970[0] = state[6] + state[9];
   out_169586844375619970[1] = state[7] + state[10];
   out_169586844375619970[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2962593625262792283) {
   out_2962593625262792283[0] = 0;
   out_2962593625262792283[1] = 0;
   out_2962593625262792283[2] = 0;
   out_2962593625262792283[3] = 0;
   out_2962593625262792283[4] = 0;
   out_2962593625262792283[5] = 0;
   out_2962593625262792283[6] = 1;
   out_2962593625262792283[7] = 0;
   out_2962593625262792283[8] = 0;
   out_2962593625262792283[9] = 1;
   out_2962593625262792283[10] = 0;
   out_2962593625262792283[11] = 0;
   out_2962593625262792283[12] = 0;
   out_2962593625262792283[13] = 0;
   out_2962593625262792283[14] = 0;
   out_2962593625262792283[15] = 0;
   out_2962593625262792283[16] = 0;
   out_2962593625262792283[17] = 0;
   out_2962593625262792283[18] = 0;
   out_2962593625262792283[19] = 0;
   out_2962593625262792283[20] = 0;
   out_2962593625262792283[21] = 0;
   out_2962593625262792283[22] = 0;
   out_2962593625262792283[23] = 0;
   out_2962593625262792283[24] = 0;
   out_2962593625262792283[25] = 1;
   out_2962593625262792283[26] = 0;
   out_2962593625262792283[27] = 0;
   out_2962593625262792283[28] = 1;
   out_2962593625262792283[29] = 0;
   out_2962593625262792283[30] = 0;
   out_2962593625262792283[31] = 0;
   out_2962593625262792283[32] = 0;
   out_2962593625262792283[33] = 0;
   out_2962593625262792283[34] = 0;
   out_2962593625262792283[35] = 0;
   out_2962593625262792283[36] = 0;
   out_2962593625262792283[37] = 0;
   out_2962593625262792283[38] = 0;
   out_2962593625262792283[39] = 0;
   out_2962593625262792283[40] = 0;
   out_2962593625262792283[41] = 0;
   out_2962593625262792283[42] = 0;
   out_2962593625262792283[43] = 0;
   out_2962593625262792283[44] = 1;
   out_2962593625262792283[45] = 0;
   out_2962593625262792283[46] = 0;
   out_2962593625262792283[47] = 1;
   out_2962593625262792283[48] = 0;
   out_2962593625262792283[49] = 0;
   out_2962593625262792283[50] = 0;
   out_2962593625262792283[51] = 0;
   out_2962593625262792283[52] = 0;
   out_2962593625262792283[53] = 0;
}
void h_10(double *state, double *unused, double *out_8793925764545223572) {
   out_8793925764545223572[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8793925764545223572[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8793925764545223572[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2626145331746833569) {
   out_2626145331746833569[0] = 0;
   out_2626145331746833569[1] = 9.8100000000000005*cos(state[1]);
   out_2626145331746833569[2] = 0;
   out_2626145331746833569[3] = 0;
   out_2626145331746833569[4] = -state[8];
   out_2626145331746833569[5] = state[7];
   out_2626145331746833569[6] = 0;
   out_2626145331746833569[7] = state[5];
   out_2626145331746833569[8] = -state[4];
   out_2626145331746833569[9] = 0;
   out_2626145331746833569[10] = 0;
   out_2626145331746833569[11] = 0;
   out_2626145331746833569[12] = 1;
   out_2626145331746833569[13] = 0;
   out_2626145331746833569[14] = 0;
   out_2626145331746833569[15] = 1;
   out_2626145331746833569[16] = 0;
   out_2626145331746833569[17] = 0;
   out_2626145331746833569[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2626145331746833569[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2626145331746833569[20] = 0;
   out_2626145331746833569[21] = state[8];
   out_2626145331746833569[22] = 0;
   out_2626145331746833569[23] = -state[6];
   out_2626145331746833569[24] = -state[5];
   out_2626145331746833569[25] = 0;
   out_2626145331746833569[26] = state[3];
   out_2626145331746833569[27] = 0;
   out_2626145331746833569[28] = 0;
   out_2626145331746833569[29] = 0;
   out_2626145331746833569[30] = 0;
   out_2626145331746833569[31] = 1;
   out_2626145331746833569[32] = 0;
   out_2626145331746833569[33] = 0;
   out_2626145331746833569[34] = 1;
   out_2626145331746833569[35] = 0;
   out_2626145331746833569[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2626145331746833569[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2626145331746833569[38] = 0;
   out_2626145331746833569[39] = -state[7];
   out_2626145331746833569[40] = state[6];
   out_2626145331746833569[41] = 0;
   out_2626145331746833569[42] = state[4];
   out_2626145331746833569[43] = -state[3];
   out_2626145331746833569[44] = 0;
   out_2626145331746833569[45] = 0;
   out_2626145331746833569[46] = 0;
   out_2626145331746833569[47] = 0;
   out_2626145331746833569[48] = 0;
   out_2626145331746833569[49] = 0;
   out_2626145331746833569[50] = 1;
   out_2626145331746833569[51] = 0;
   out_2626145331746833569[52] = 0;
   out_2626145331746833569[53] = 1;
}
void h_13(double *state, double *unused, double *out_4090467412018967888) {
   out_4090467412018967888[0] = state[3];
   out_4090467412018967888[1] = state[4];
   out_4090467412018967888[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6796349088565316307) {
   out_6796349088565316307[0] = 0;
   out_6796349088565316307[1] = 0;
   out_6796349088565316307[2] = 0;
   out_6796349088565316307[3] = 1;
   out_6796349088565316307[4] = 0;
   out_6796349088565316307[5] = 0;
   out_6796349088565316307[6] = 0;
   out_6796349088565316307[7] = 0;
   out_6796349088565316307[8] = 0;
   out_6796349088565316307[9] = 0;
   out_6796349088565316307[10] = 0;
   out_6796349088565316307[11] = 0;
   out_6796349088565316307[12] = 0;
   out_6796349088565316307[13] = 0;
   out_6796349088565316307[14] = 0;
   out_6796349088565316307[15] = 0;
   out_6796349088565316307[16] = 0;
   out_6796349088565316307[17] = 0;
   out_6796349088565316307[18] = 0;
   out_6796349088565316307[19] = 0;
   out_6796349088565316307[20] = 0;
   out_6796349088565316307[21] = 0;
   out_6796349088565316307[22] = 1;
   out_6796349088565316307[23] = 0;
   out_6796349088565316307[24] = 0;
   out_6796349088565316307[25] = 0;
   out_6796349088565316307[26] = 0;
   out_6796349088565316307[27] = 0;
   out_6796349088565316307[28] = 0;
   out_6796349088565316307[29] = 0;
   out_6796349088565316307[30] = 0;
   out_6796349088565316307[31] = 0;
   out_6796349088565316307[32] = 0;
   out_6796349088565316307[33] = 0;
   out_6796349088565316307[34] = 0;
   out_6796349088565316307[35] = 0;
   out_6796349088565316307[36] = 0;
   out_6796349088565316307[37] = 0;
   out_6796349088565316307[38] = 0;
   out_6796349088565316307[39] = 0;
   out_6796349088565316307[40] = 0;
   out_6796349088565316307[41] = 1;
   out_6796349088565316307[42] = 0;
   out_6796349088565316307[43] = 0;
   out_6796349088565316307[44] = 0;
   out_6796349088565316307[45] = 0;
   out_6796349088565316307[46] = 0;
   out_6796349088565316307[47] = 0;
   out_6796349088565316307[48] = 0;
   out_6796349088565316307[49] = 0;
   out_6796349088565316307[50] = 0;
   out_6796349088565316307[51] = 0;
   out_6796349088565316307[52] = 0;
   out_6796349088565316307[53] = 0;
}
void h_14(double *state, double *unused, double *out_8363622320862145642) {
   out_8363622320862145642[0] = state[6];
   out_8363622320862145642[1] = state[7];
   out_8363622320862145642[2] = state[8];
}
void H_14(double *state, double *unused, double *out_6045382057558164579) {
   out_6045382057558164579[0] = 0;
   out_6045382057558164579[1] = 0;
   out_6045382057558164579[2] = 0;
   out_6045382057558164579[3] = 0;
   out_6045382057558164579[4] = 0;
   out_6045382057558164579[5] = 0;
   out_6045382057558164579[6] = 1;
   out_6045382057558164579[7] = 0;
   out_6045382057558164579[8] = 0;
   out_6045382057558164579[9] = 0;
   out_6045382057558164579[10] = 0;
   out_6045382057558164579[11] = 0;
   out_6045382057558164579[12] = 0;
   out_6045382057558164579[13] = 0;
   out_6045382057558164579[14] = 0;
   out_6045382057558164579[15] = 0;
   out_6045382057558164579[16] = 0;
   out_6045382057558164579[17] = 0;
   out_6045382057558164579[18] = 0;
   out_6045382057558164579[19] = 0;
   out_6045382057558164579[20] = 0;
   out_6045382057558164579[21] = 0;
   out_6045382057558164579[22] = 0;
   out_6045382057558164579[23] = 0;
   out_6045382057558164579[24] = 0;
   out_6045382057558164579[25] = 1;
   out_6045382057558164579[26] = 0;
   out_6045382057558164579[27] = 0;
   out_6045382057558164579[28] = 0;
   out_6045382057558164579[29] = 0;
   out_6045382057558164579[30] = 0;
   out_6045382057558164579[31] = 0;
   out_6045382057558164579[32] = 0;
   out_6045382057558164579[33] = 0;
   out_6045382057558164579[34] = 0;
   out_6045382057558164579[35] = 0;
   out_6045382057558164579[36] = 0;
   out_6045382057558164579[37] = 0;
   out_6045382057558164579[38] = 0;
   out_6045382057558164579[39] = 0;
   out_6045382057558164579[40] = 0;
   out_6045382057558164579[41] = 0;
   out_6045382057558164579[42] = 0;
   out_6045382057558164579[43] = 0;
   out_6045382057558164579[44] = 1;
   out_6045382057558164579[45] = 0;
   out_6045382057558164579[46] = 0;
   out_6045382057558164579[47] = 0;
   out_6045382057558164579[48] = 0;
   out_6045382057558164579[49] = 0;
   out_6045382057558164579[50] = 0;
   out_6045382057558164579[51] = 0;
   out_6045382057558164579[52] = 0;
   out_6045382057558164579[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_8069274513708895969) {
  err_fun(nom_x, delta_x, out_8069274513708895969);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6148460760368505675) {
  inv_err_fun(nom_x, true_x, out_6148460760368505675);
}
void pose_H_mod_fun(double *state, double *out_3716754627317504890) {
  H_mod_fun(state, out_3716754627317504890);
}
void pose_f_fun(double *state, double dt, double *out_4855167580946130027) {
  f_fun(state,  dt, out_4855167580946130027);
}
void pose_F_fun(double *state, double dt, double *out_4420770900431173050) {
  F_fun(state,  dt, out_4420770900431173050);
}
void pose_h_4(double *state, double *unused, double *out_169586844375619970) {
  h_4(state, unused, out_169586844375619970);
}
void pose_H_4(double *state, double *unused, double *out_2962593625262792283) {
  H_4(state, unused, out_2962593625262792283);
}
void pose_h_10(double *state, double *unused, double *out_8793925764545223572) {
  h_10(state, unused, out_8793925764545223572);
}
void pose_H_10(double *state, double *unused, double *out_2626145331746833569) {
  H_10(state, unused, out_2626145331746833569);
}
void pose_h_13(double *state, double *unused, double *out_4090467412018967888) {
  h_13(state, unused, out_4090467412018967888);
}
void pose_H_13(double *state, double *unused, double *out_6796349088565316307) {
  H_13(state, unused, out_6796349088565316307);
}
void pose_h_14(double *state, double *unused, double *out_8363622320862145642) {
  h_14(state, unused, out_8363622320862145642);
}
void pose_H_14(double *state, double *unused, double *out_6045382057558164579) {
  H_14(state, unused, out_6045382057558164579);
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
