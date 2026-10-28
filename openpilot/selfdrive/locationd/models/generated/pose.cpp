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
void err_fun(double *nom_x, double *delta_x, double *out_3590467737713675004) {
   out_3590467737713675004[0] = delta_x[0] + nom_x[0];
   out_3590467737713675004[1] = delta_x[1] + nom_x[1];
   out_3590467737713675004[2] = delta_x[2] + nom_x[2];
   out_3590467737713675004[3] = delta_x[3] + nom_x[3];
   out_3590467737713675004[4] = delta_x[4] + nom_x[4];
   out_3590467737713675004[5] = delta_x[5] + nom_x[5];
   out_3590467737713675004[6] = delta_x[6] + nom_x[6];
   out_3590467737713675004[7] = delta_x[7] + nom_x[7];
   out_3590467737713675004[8] = delta_x[8] + nom_x[8];
   out_3590467737713675004[9] = delta_x[9] + nom_x[9];
   out_3590467737713675004[10] = delta_x[10] + nom_x[10];
   out_3590467737713675004[11] = delta_x[11] + nom_x[11];
   out_3590467737713675004[12] = delta_x[12] + nom_x[12];
   out_3590467737713675004[13] = delta_x[13] + nom_x[13];
   out_3590467737713675004[14] = delta_x[14] + nom_x[14];
   out_3590467737713675004[15] = delta_x[15] + nom_x[15];
   out_3590467737713675004[16] = delta_x[16] + nom_x[16];
   out_3590467737713675004[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_837876479050183132) {
   out_837876479050183132[0] = -nom_x[0] + true_x[0];
   out_837876479050183132[1] = -nom_x[1] + true_x[1];
   out_837876479050183132[2] = -nom_x[2] + true_x[2];
   out_837876479050183132[3] = -nom_x[3] + true_x[3];
   out_837876479050183132[4] = -nom_x[4] + true_x[4];
   out_837876479050183132[5] = -nom_x[5] + true_x[5];
   out_837876479050183132[6] = -nom_x[6] + true_x[6];
   out_837876479050183132[7] = -nom_x[7] + true_x[7];
   out_837876479050183132[8] = -nom_x[8] + true_x[8];
   out_837876479050183132[9] = -nom_x[9] + true_x[9];
   out_837876479050183132[10] = -nom_x[10] + true_x[10];
   out_837876479050183132[11] = -nom_x[11] + true_x[11];
   out_837876479050183132[12] = -nom_x[12] + true_x[12];
   out_837876479050183132[13] = -nom_x[13] + true_x[13];
   out_837876479050183132[14] = -nom_x[14] + true_x[14];
   out_837876479050183132[15] = -nom_x[15] + true_x[15];
   out_837876479050183132[16] = -nom_x[16] + true_x[16];
   out_837876479050183132[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5781655979714254891) {
   out_5781655979714254891[0] = 1.0;
   out_5781655979714254891[1] = 0.0;
   out_5781655979714254891[2] = 0.0;
   out_5781655979714254891[3] = 0.0;
   out_5781655979714254891[4] = 0.0;
   out_5781655979714254891[5] = 0.0;
   out_5781655979714254891[6] = 0.0;
   out_5781655979714254891[7] = 0.0;
   out_5781655979714254891[8] = 0.0;
   out_5781655979714254891[9] = 0.0;
   out_5781655979714254891[10] = 0.0;
   out_5781655979714254891[11] = 0.0;
   out_5781655979714254891[12] = 0.0;
   out_5781655979714254891[13] = 0.0;
   out_5781655979714254891[14] = 0.0;
   out_5781655979714254891[15] = 0.0;
   out_5781655979714254891[16] = 0.0;
   out_5781655979714254891[17] = 0.0;
   out_5781655979714254891[18] = 0.0;
   out_5781655979714254891[19] = 1.0;
   out_5781655979714254891[20] = 0.0;
   out_5781655979714254891[21] = 0.0;
   out_5781655979714254891[22] = 0.0;
   out_5781655979714254891[23] = 0.0;
   out_5781655979714254891[24] = 0.0;
   out_5781655979714254891[25] = 0.0;
   out_5781655979714254891[26] = 0.0;
   out_5781655979714254891[27] = 0.0;
   out_5781655979714254891[28] = 0.0;
   out_5781655979714254891[29] = 0.0;
   out_5781655979714254891[30] = 0.0;
   out_5781655979714254891[31] = 0.0;
   out_5781655979714254891[32] = 0.0;
   out_5781655979714254891[33] = 0.0;
   out_5781655979714254891[34] = 0.0;
   out_5781655979714254891[35] = 0.0;
   out_5781655979714254891[36] = 0.0;
   out_5781655979714254891[37] = 0.0;
   out_5781655979714254891[38] = 1.0;
   out_5781655979714254891[39] = 0.0;
   out_5781655979714254891[40] = 0.0;
   out_5781655979714254891[41] = 0.0;
   out_5781655979714254891[42] = 0.0;
   out_5781655979714254891[43] = 0.0;
   out_5781655979714254891[44] = 0.0;
   out_5781655979714254891[45] = 0.0;
   out_5781655979714254891[46] = 0.0;
   out_5781655979714254891[47] = 0.0;
   out_5781655979714254891[48] = 0.0;
   out_5781655979714254891[49] = 0.0;
   out_5781655979714254891[50] = 0.0;
   out_5781655979714254891[51] = 0.0;
   out_5781655979714254891[52] = 0.0;
   out_5781655979714254891[53] = 0.0;
   out_5781655979714254891[54] = 0.0;
   out_5781655979714254891[55] = 0.0;
   out_5781655979714254891[56] = 0.0;
   out_5781655979714254891[57] = 1.0;
   out_5781655979714254891[58] = 0.0;
   out_5781655979714254891[59] = 0.0;
   out_5781655979714254891[60] = 0.0;
   out_5781655979714254891[61] = 0.0;
   out_5781655979714254891[62] = 0.0;
   out_5781655979714254891[63] = 0.0;
   out_5781655979714254891[64] = 0.0;
   out_5781655979714254891[65] = 0.0;
   out_5781655979714254891[66] = 0.0;
   out_5781655979714254891[67] = 0.0;
   out_5781655979714254891[68] = 0.0;
   out_5781655979714254891[69] = 0.0;
   out_5781655979714254891[70] = 0.0;
   out_5781655979714254891[71] = 0.0;
   out_5781655979714254891[72] = 0.0;
   out_5781655979714254891[73] = 0.0;
   out_5781655979714254891[74] = 0.0;
   out_5781655979714254891[75] = 0.0;
   out_5781655979714254891[76] = 1.0;
   out_5781655979714254891[77] = 0.0;
   out_5781655979714254891[78] = 0.0;
   out_5781655979714254891[79] = 0.0;
   out_5781655979714254891[80] = 0.0;
   out_5781655979714254891[81] = 0.0;
   out_5781655979714254891[82] = 0.0;
   out_5781655979714254891[83] = 0.0;
   out_5781655979714254891[84] = 0.0;
   out_5781655979714254891[85] = 0.0;
   out_5781655979714254891[86] = 0.0;
   out_5781655979714254891[87] = 0.0;
   out_5781655979714254891[88] = 0.0;
   out_5781655979714254891[89] = 0.0;
   out_5781655979714254891[90] = 0.0;
   out_5781655979714254891[91] = 0.0;
   out_5781655979714254891[92] = 0.0;
   out_5781655979714254891[93] = 0.0;
   out_5781655979714254891[94] = 0.0;
   out_5781655979714254891[95] = 1.0;
   out_5781655979714254891[96] = 0.0;
   out_5781655979714254891[97] = 0.0;
   out_5781655979714254891[98] = 0.0;
   out_5781655979714254891[99] = 0.0;
   out_5781655979714254891[100] = 0.0;
   out_5781655979714254891[101] = 0.0;
   out_5781655979714254891[102] = 0.0;
   out_5781655979714254891[103] = 0.0;
   out_5781655979714254891[104] = 0.0;
   out_5781655979714254891[105] = 0.0;
   out_5781655979714254891[106] = 0.0;
   out_5781655979714254891[107] = 0.0;
   out_5781655979714254891[108] = 0.0;
   out_5781655979714254891[109] = 0.0;
   out_5781655979714254891[110] = 0.0;
   out_5781655979714254891[111] = 0.0;
   out_5781655979714254891[112] = 0.0;
   out_5781655979714254891[113] = 0.0;
   out_5781655979714254891[114] = 1.0;
   out_5781655979714254891[115] = 0.0;
   out_5781655979714254891[116] = 0.0;
   out_5781655979714254891[117] = 0.0;
   out_5781655979714254891[118] = 0.0;
   out_5781655979714254891[119] = 0.0;
   out_5781655979714254891[120] = 0.0;
   out_5781655979714254891[121] = 0.0;
   out_5781655979714254891[122] = 0.0;
   out_5781655979714254891[123] = 0.0;
   out_5781655979714254891[124] = 0.0;
   out_5781655979714254891[125] = 0.0;
   out_5781655979714254891[126] = 0.0;
   out_5781655979714254891[127] = 0.0;
   out_5781655979714254891[128] = 0.0;
   out_5781655979714254891[129] = 0.0;
   out_5781655979714254891[130] = 0.0;
   out_5781655979714254891[131] = 0.0;
   out_5781655979714254891[132] = 0.0;
   out_5781655979714254891[133] = 1.0;
   out_5781655979714254891[134] = 0.0;
   out_5781655979714254891[135] = 0.0;
   out_5781655979714254891[136] = 0.0;
   out_5781655979714254891[137] = 0.0;
   out_5781655979714254891[138] = 0.0;
   out_5781655979714254891[139] = 0.0;
   out_5781655979714254891[140] = 0.0;
   out_5781655979714254891[141] = 0.0;
   out_5781655979714254891[142] = 0.0;
   out_5781655979714254891[143] = 0.0;
   out_5781655979714254891[144] = 0.0;
   out_5781655979714254891[145] = 0.0;
   out_5781655979714254891[146] = 0.0;
   out_5781655979714254891[147] = 0.0;
   out_5781655979714254891[148] = 0.0;
   out_5781655979714254891[149] = 0.0;
   out_5781655979714254891[150] = 0.0;
   out_5781655979714254891[151] = 0.0;
   out_5781655979714254891[152] = 1.0;
   out_5781655979714254891[153] = 0.0;
   out_5781655979714254891[154] = 0.0;
   out_5781655979714254891[155] = 0.0;
   out_5781655979714254891[156] = 0.0;
   out_5781655979714254891[157] = 0.0;
   out_5781655979714254891[158] = 0.0;
   out_5781655979714254891[159] = 0.0;
   out_5781655979714254891[160] = 0.0;
   out_5781655979714254891[161] = 0.0;
   out_5781655979714254891[162] = 0.0;
   out_5781655979714254891[163] = 0.0;
   out_5781655979714254891[164] = 0.0;
   out_5781655979714254891[165] = 0.0;
   out_5781655979714254891[166] = 0.0;
   out_5781655979714254891[167] = 0.0;
   out_5781655979714254891[168] = 0.0;
   out_5781655979714254891[169] = 0.0;
   out_5781655979714254891[170] = 0.0;
   out_5781655979714254891[171] = 1.0;
   out_5781655979714254891[172] = 0.0;
   out_5781655979714254891[173] = 0.0;
   out_5781655979714254891[174] = 0.0;
   out_5781655979714254891[175] = 0.0;
   out_5781655979714254891[176] = 0.0;
   out_5781655979714254891[177] = 0.0;
   out_5781655979714254891[178] = 0.0;
   out_5781655979714254891[179] = 0.0;
   out_5781655979714254891[180] = 0.0;
   out_5781655979714254891[181] = 0.0;
   out_5781655979714254891[182] = 0.0;
   out_5781655979714254891[183] = 0.0;
   out_5781655979714254891[184] = 0.0;
   out_5781655979714254891[185] = 0.0;
   out_5781655979714254891[186] = 0.0;
   out_5781655979714254891[187] = 0.0;
   out_5781655979714254891[188] = 0.0;
   out_5781655979714254891[189] = 0.0;
   out_5781655979714254891[190] = 1.0;
   out_5781655979714254891[191] = 0.0;
   out_5781655979714254891[192] = 0.0;
   out_5781655979714254891[193] = 0.0;
   out_5781655979714254891[194] = 0.0;
   out_5781655979714254891[195] = 0.0;
   out_5781655979714254891[196] = 0.0;
   out_5781655979714254891[197] = 0.0;
   out_5781655979714254891[198] = 0.0;
   out_5781655979714254891[199] = 0.0;
   out_5781655979714254891[200] = 0.0;
   out_5781655979714254891[201] = 0.0;
   out_5781655979714254891[202] = 0.0;
   out_5781655979714254891[203] = 0.0;
   out_5781655979714254891[204] = 0.0;
   out_5781655979714254891[205] = 0.0;
   out_5781655979714254891[206] = 0.0;
   out_5781655979714254891[207] = 0.0;
   out_5781655979714254891[208] = 0.0;
   out_5781655979714254891[209] = 1.0;
   out_5781655979714254891[210] = 0.0;
   out_5781655979714254891[211] = 0.0;
   out_5781655979714254891[212] = 0.0;
   out_5781655979714254891[213] = 0.0;
   out_5781655979714254891[214] = 0.0;
   out_5781655979714254891[215] = 0.0;
   out_5781655979714254891[216] = 0.0;
   out_5781655979714254891[217] = 0.0;
   out_5781655979714254891[218] = 0.0;
   out_5781655979714254891[219] = 0.0;
   out_5781655979714254891[220] = 0.0;
   out_5781655979714254891[221] = 0.0;
   out_5781655979714254891[222] = 0.0;
   out_5781655979714254891[223] = 0.0;
   out_5781655979714254891[224] = 0.0;
   out_5781655979714254891[225] = 0.0;
   out_5781655979714254891[226] = 0.0;
   out_5781655979714254891[227] = 0.0;
   out_5781655979714254891[228] = 1.0;
   out_5781655979714254891[229] = 0.0;
   out_5781655979714254891[230] = 0.0;
   out_5781655979714254891[231] = 0.0;
   out_5781655979714254891[232] = 0.0;
   out_5781655979714254891[233] = 0.0;
   out_5781655979714254891[234] = 0.0;
   out_5781655979714254891[235] = 0.0;
   out_5781655979714254891[236] = 0.0;
   out_5781655979714254891[237] = 0.0;
   out_5781655979714254891[238] = 0.0;
   out_5781655979714254891[239] = 0.0;
   out_5781655979714254891[240] = 0.0;
   out_5781655979714254891[241] = 0.0;
   out_5781655979714254891[242] = 0.0;
   out_5781655979714254891[243] = 0.0;
   out_5781655979714254891[244] = 0.0;
   out_5781655979714254891[245] = 0.0;
   out_5781655979714254891[246] = 0.0;
   out_5781655979714254891[247] = 1.0;
   out_5781655979714254891[248] = 0.0;
   out_5781655979714254891[249] = 0.0;
   out_5781655979714254891[250] = 0.0;
   out_5781655979714254891[251] = 0.0;
   out_5781655979714254891[252] = 0.0;
   out_5781655979714254891[253] = 0.0;
   out_5781655979714254891[254] = 0.0;
   out_5781655979714254891[255] = 0.0;
   out_5781655979714254891[256] = 0.0;
   out_5781655979714254891[257] = 0.0;
   out_5781655979714254891[258] = 0.0;
   out_5781655979714254891[259] = 0.0;
   out_5781655979714254891[260] = 0.0;
   out_5781655979714254891[261] = 0.0;
   out_5781655979714254891[262] = 0.0;
   out_5781655979714254891[263] = 0.0;
   out_5781655979714254891[264] = 0.0;
   out_5781655979714254891[265] = 0.0;
   out_5781655979714254891[266] = 1.0;
   out_5781655979714254891[267] = 0.0;
   out_5781655979714254891[268] = 0.0;
   out_5781655979714254891[269] = 0.0;
   out_5781655979714254891[270] = 0.0;
   out_5781655979714254891[271] = 0.0;
   out_5781655979714254891[272] = 0.0;
   out_5781655979714254891[273] = 0.0;
   out_5781655979714254891[274] = 0.0;
   out_5781655979714254891[275] = 0.0;
   out_5781655979714254891[276] = 0.0;
   out_5781655979714254891[277] = 0.0;
   out_5781655979714254891[278] = 0.0;
   out_5781655979714254891[279] = 0.0;
   out_5781655979714254891[280] = 0.0;
   out_5781655979714254891[281] = 0.0;
   out_5781655979714254891[282] = 0.0;
   out_5781655979714254891[283] = 0.0;
   out_5781655979714254891[284] = 0.0;
   out_5781655979714254891[285] = 1.0;
   out_5781655979714254891[286] = 0.0;
   out_5781655979714254891[287] = 0.0;
   out_5781655979714254891[288] = 0.0;
   out_5781655979714254891[289] = 0.0;
   out_5781655979714254891[290] = 0.0;
   out_5781655979714254891[291] = 0.0;
   out_5781655979714254891[292] = 0.0;
   out_5781655979714254891[293] = 0.0;
   out_5781655979714254891[294] = 0.0;
   out_5781655979714254891[295] = 0.0;
   out_5781655979714254891[296] = 0.0;
   out_5781655979714254891[297] = 0.0;
   out_5781655979714254891[298] = 0.0;
   out_5781655979714254891[299] = 0.0;
   out_5781655979714254891[300] = 0.0;
   out_5781655979714254891[301] = 0.0;
   out_5781655979714254891[302] = 0.0;
   out_5781655979714254891[303] = 0.0;
   out_5781655979714254891[304] = 1.0;
   out_5781655979714254891[305] = 0.0;
   out_5781655979714254891[306] = 0.0;
   out_5781655979714254891[307] = 0.0;
   out_5781655979714254891[308] = 0.0;
   out_5781655979714254891[309] = 0.0;
   out_5781655979714254891[310] = 0.0;
   out_5781655979714254891[311] = 0.0;
   out_5781655979714254891[312] = 0.0;
   out_5781655979714254891[313] = 0.0;
   out_5781655979714254891[314] = 0.0;
   out_5781655979714254891[315] = 0.0;
   out_5781655979714254891[316] = 0.0;
   out_5781655979714254891[317] = 0.0;
   out_5781655979714254891[318] = 0.0;
   out_5781655979714254891[319] = 0.0;
   out_5781655979714254891[320] = 0.0;
   out_5781655979714254891[321] = 0.0;
   out_5781655979714254891[322] = 0.0;
   out_5781655979714254891[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_2390805150352098946) {
   out_2390805150352098946[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_2390805150352098946[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_2390805150352098946[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_2390805150352098946[3] = dt*state[12] + state[3];
   out_2390805150352098946[4] = dt*state[13] + state[4];
   out_2390805150352098946[5] = dt*state[14] + state[5];
   out_2390805150352098946[6] = state[6];
   out_2390805150352098946[7] = state[7];
   out_2390805150352098946[8] = state[8];
   out_2390805150352098946[9] = state[9];
   out_2390805150352098946[10] = state[10];
   out_2390805150352098946[11] = state[11];
   out_2390805150352098946[12] = state[12];
   out_2390805150352098946[13] = state[13];
   out_2390805150352098946[14] = state[14];
   out_2390805150352098946[15] = state[15];
   out_2390805150352098946[16] = state[16];
   out_2390805150352098946[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3481270369411220980) {
   out_3481270369411220980[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3481270369411220980[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3481270369411220980[2] = 0;
   out_3481270369411220980[3] = 0;
   out_3481270369411220980[4] = 0;
   out_3481270369411220980[5] = 0;
   out_3481270369411220980[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3481270369411220980[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3481270369411220980[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3481270369411220980[9] = 0;
   out_3481270369411220980[10] = 0;
   out_3481270369411220980[11] = 0;
   out_3481270369411220980[12] = 0;
   out_3481270369411220980[13] = 0;
   out_3481270369411220980[14] = 0;
   out_3481270369411220980[15] = 0;
   out_3481270369411220980[16] = 0;
   out_3481270369411220980[17] = 0;
   out_3481270369411220980[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3481270369411220980[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3481270369411220980[20] = 0;
   out_3481270369411220980[21] = 0;
   out_3481270369411220980[22] = 0;
   out_3481270369411220980[23] = 0;
   out_3481270369411220980[24] = 0;
   out_3481270369411220980[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3481270369411220980[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3481270369411220980[27] = 0;
   out_3481270369411220980[28] = 0;
   out_3481270369411220980[29] = 0;
   out_3481270369411220980[30] = 0;
   out_3481270369411220980[31] = 0;
   out_3481270369411220980[32] = 0;
   out_3481270369411220980[33] = 0;
   out_3481270369411220980[34] = 0;
   out_3481270369411220980[35] = 0;
   out_3481270369411220980[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3481270369411220980[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3481270369411220980[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3481270369411220980[39] = 0;
   out_3481270369411220980[40] = 0;
   out_3481270369411220980[41] = 0;
   out_3481270369411220980[42] = 0;
   out_3481270369411220980[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3481270369411220980[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3481270369411220980[45] = 0;
   out_3481270369411220980[46] = 0;
   out_3481270369411220980[47] = 0;
   out_3481270369411220980[48] = 0;
   out_3481270369411220980[49] = 0;
   out_3481270369411220980[50] = 0;
   out_3481270369411220980[51] = 0;
   out_3481270369411220980[52] = 0;
   out_3481270369411220980[53] = 0;
   out_3481270369411220980[54] = 0;
   out_3481270369411220980[55] = 0;
   out_3481270369411220980[56] = 0;
   out_3481270369411220980[57] = 1;
   out_3481270369411220980[58] = 0;
   out_3481270369411220980[59] = 0;
   out_3481270369411220980[60] = 0;
   out_3481270369411220980[61] = 0;
   out_3481270369411220980[62] = 0;
   out_3481270369411220980[63] = 0;
   out_3481270369411220980[64] = 0;
   out_3481270369411220980[65] = 0;
   out_3481270369411220980[66] = dt;
   out_3481270369411220980[67] = 0;
   out_3481270369411220980[68] = 0;
   out_3481270369411220980[69] = 0;
   out_3481270369411220980[70] = 0;
   out_3481270369411220980[71] = 0;
   out_3481270369411220980[72] = 0;
   out_3481270369411220980[73] = 0;
   out_3481270369411220980[74] = 0;
   out_3481270369411220980[75] = 0;
   out_3481270369411220980[76] = 1;
   out_3481270369411220980[77] = 0;
   out_3481270369411220980[78] = 0;
   out_3481270369411220980[79] = 0;
   out_3481270369411220980[80] = 0;
   out_3481270369411220980[81] = 0;
   out_3481270369411220980[82] = 0;
   out_3481270369411220980[83] = 0;
   out_3481270369411220980[84] = 0;
   out_3481270369411220980[85] = dt;
   out_3481270369411220980[86] = 0;
   out_3481270369411220980[87] = 0;
   out_3481270369411220980[88] = 0;
   out_3481270369411220980[89] = 0;
   out_3481270369411220980[90] = 0;
   out_3481270369411220980[91] = 0;
   out_3481270369411220980[92] = 0;
   out_3481270369411220980[93] = 0;
   out_3481270369411220980[94] = 0;
   out_3481270369411220980[95] = 1;
   out_3481270369411220980[96] = 0;
   out_3481270369411220980[97] = 0;
   out_3481270369411220980[98] = 0;
   out_3481270369411220980[99] = 0;
   out_3481270369411220980[100] = 0;
   out_3481270369411220980[101] = 0;
   out_3481270369411220980[102] = 0;
   out_3481270369411220980[103] = 0;
   out_3481270369411220980[104] = dt;
   out_3481270369411220980[105] = 0;
   out_3481270369411220980[106] = 0;
   out_3481270369411220980[107] = 0;
   out_3481270369411220980[108] = 0;
   out_3481270369411220980[109] = 0;
   out_3481270369411220980[110] = 0;
   out_3481270369411220980[111] = 0;
   out_3481270369411220980[112] = 0;
   out_3481270369411220980[113] = 0;
   out_3481270369411220980[114] = 1;
   out_3481270369411220980[115] = 0;
   out_3481270369411220980[116] = 0;
   out_3481270369411220980[117] = 0;
   out_3481270369411220980[118] = 0;
   out_3481270369411220980[119] = 0;
   out_3481270369411220980[120] = 0;
   out_3481270369411220980[121] = 0;
   out_3481270369411220980[122] = 0;
   out_3481270369411220980[123] = 0;
   out_3481270369411220980[124] = 0;
   out_3481270369411220980[125] = 0;
   out_3481270369411220980[126] = 0;
   out_3481270369411220980[127] = 0;
   out_3481270369411220980[128] = 0;
   out_3481270369411220980[129] = 0;
   out_3481270369411220980[130] = 0;
   out_3481270369411220980[131] = 0;
   out_3481270369411220980[132] = 0;
   out_3481270369411220980[133] = 1;
   out_3481270369411220980[134] = 0;
   out_3481270369411220980[135] = 0;
   out_3481270369411220980[136] = 0;
   out_3481270369411220980[137] = 0;
   out_3481270369411220980[138] = 0;
   out_3481270369411220980[139] = 0;
   out_3481270369411220980[140] = 0;
   out_3481270369411220980[141] = 0;
   out_3481270369411220980[142] = 0;
   out_3481270369411220980[143] = 0;
   out_3481270369411220980[144] = 0;
   out_3481270369411220980[145] = 0;
   out_3481270369411220980[146] = 0;
   out_3481270369411220980[147] = 0;
   out_3481270369411220980[148] = 0;
   out_3481270369411220980[149] = 0;
   out_3481270369411220980[150] = 0;
   out_3481270369411220980[151] = 0;
   out_3481270369411220980[152] = 1;
   out_3481270369411220980[153] = 0;
   out_3481270369411220980[154] = 0;
   out_3481270369411220980[155] = 0;
   out_3481270369411220980[156] = 0;
   out_3481270369411220980[157] = 0;
   out_3481270369411220980[158] = 0;
   out_3481270369411220980[159] = 0;
   out_3481270369411220980[160] = 0;
   out_3481270369411220980[161] = 0;
   out_3481270369411220980[162] = 0;
   out_3481270369411220980[163] = 0;
   out_3481270369411220980[164] = 0;
   out_3481270369411220980[165] = 0;
   out_3481270369411220980[166] = 0;
   out_3481270369411220980[167] = 0;
   out_3481270369411220980[168] = 0;
   out_3481270369411220980[169] = 0;
   out_3481270369411220980[170] = 0;
   out_3481270369411220980[171] = 1;
   out_3481270369411220980[172] = 0;
   out_3481270369411220980[173] = 0;
   out_3481270369411220980[174] = 0;
   out_3481270369411220980[175] = 0;
   out_3481270369411220980[176] = 0;
   out_3481270369411220980[177] = 0;
   out_3481270369411220980[178] = 0;
   out_3481270369411220980[179] = 0;
   out_3481270369411220980[180] = 0;
   out_3481270369411220980[181] = 0;
   out_3481270369411220980[182] = 0;
   out_3481270369411220980[183] = 0;
   out_3481270369411220980[184] = 0;
   out_3481270369411220980[185] = 0;
   out_3481270369411220980[186] = 0;
   out_3481270369411220980[187] = 0;
   out_3481270369411220980[188] = 0;
   out_3481270369411220980[189] = 0;
   out_3481270369411220980[190] = 1;
   out_3481270369411220980[191] = 0;
   out_3481270369411220980[192] = 0;
   out_3481270369411220980[193] = 0;
   out_3481270369411220980[194] = 0;
   out_3481270369411220980[195] = 0;
   out_3481270369411220980[196] = 0;
   out_3481270369411220980[197] = 0;
   out_3481270369411220980[198] = 0;
   out_3481270369411220980[199] = 0;
   out_3481270369411220980[200] = 0;
   out_3481270369411220980[201] = 0;
   out_3481270369411220980[202] = 0;
   out_3481270369411220980[203] = 0;
   out_3481270369411220980[204] = 0;
   out_3481270369411220980[205] = 0;
   out_3481270369411220980[206] = 0;
   out_3481270369411220980[207] = 0;
   out_3481270369411220980[208] = 0;
   out_3481270369411220980[209] = 1;
   out_3481270369411220980[210] = 0;
   out_3481270369411220980[211] = 0;
   out_3481270369411220980[212] = 0;
   out_3481270369411220980[213] = 0;
   out_3481270369411220980[214] = 0;
   out_3481270369411220980[215] = 0;
   out_3481270369411220980[216] = 0;
   out_3481270369411220980[217] = 0;
   out_3481270369411220980[218] = 0;
   out_3481270369411220980[219] = 0;
   out_3481270369411220980[220] = 0;
   out_3481270369411220980[221] = 0;
   out_3481270369411220980[222] = 0;
   out_3481270369411220980[223] = 0;
   out_3481270369411220980[224] = 0;
   out_3481270369411220980[225] = 0;
   out_3481270369411220980[226] = 0;
   out_3481270369411220980[227] = 0;
   out_3481270369411220980[228] = 1;
   out_3481270369411220980[229] = 0;
   out_3481270369411220980[230] = 0;
   out_3481270369411220980[231] = 0;
   out_3481270369411220980[232] = 0;
   out_3481270369411220980[233] = 0;
   out_3481270369411220980[234] = 0;
   out_3481270369411220980[235] = 0;
   out_3481270369411220980[236] = 0;
   out_3481270369411220980[237] = 0;
   out_3481270369411220980[238] = 0;
   out_3481270369411220980[239] = 0;
   out_3481270369411220980[240] = 0;
   out_3481270369411220980[241] = 0;
   out_3481270369411220980[242] = 0;
   out_3481270369411220980[243] = 0;
   out_3481270369411220980[244] = 0;
   out_3481270369411220980[245] = 0;
   out_3481270369411220980[246] = 0;
   out_3481270369411220980[247] = 1;
   out_3481270369411220980[248] = 0;
   out_3481270369411220980[249] = 0;
   out_3481270369411220980[250] = 0;
   out_3481270369411220980[251] = 0;
   out_3481270369411220980[252] = 0;
   out_3481270369411220980[253] = 0;
   out_3481270369411220980[254] = 0;
   out_3481270369411220980[255] = 0;
   out_3481270369411220980[256] = 0;
   out_3481270369411220980[257] = 0;
   out_3481270369411220980[258] = 0;
   out_3481270369411220980[259] = 0;
   out_3481270369411220980[260] = 0;
   out_3481270369411220980[261] = 0;
   out_3481270369411220980[262] = 0;
   out_3481270369411220980[263] = 0;
   out_3481270369411220980[264] = 0;
   out_3481270369411220980[265] = 0;
   out_3481270369411220980[266] = 1;
   out_3481270369411220980[267] = 0;
   out_3481270369411220980[268] = 0;
   out_3481270369411220980[269] = 0;
   out_3481270369411220980[270] = 0;
   out_3481270369411220980[271] = 0;
   out_3481270369411220980[272] = 0;
   out_3481270369411220980[273] = 0;
   out_3481270369411220980[274] = 0;
   out_3481270369411220980[275] = 0;
   out_3481270369411220980[276] = 0;
   out_3481270369411220980[277] = 0;
   out_3481270369411220980[278] = 0;
   out_3481270369411220980[279] = 0;
   out_3481270369411220980[280] = 0;
   out_3481270369411220980[281] = 0;
   out_3481270369411220980[282] = 0;
   out_3481270369411220980[283] = 0;
   out_3481270369411220980[284] = 0;
   out_3481270369411220980[285] = 1;
   out_3481270369411220980[286] = 0;
   out_3481270369411220980[287] = 0;
   out_3481270369411220980[288] = 0;
   out_3481270369411220980[289] = 0;
   out_3481270369411220980[290] = 0;
   out_3481270369411220980[291] = 0;
   out_3481270369411220980[292] = 0;
   out_3481270369411220980[293] = 0;
   out_3481270369411220980[294] = 0;
   out_3481270369411220980[295] = 0;
   out_3481270369411220980[296] = 0;
   out_3481270369411220980[297] = 0;
   out_3481270369411220980[298] = 0;
   out_3481270369411220980[299] = 0;
   out_3481270369411220980[300] = 0;
   out_3481270369411220980[301] = 0;
   out_3481270369411220980[302] = 0;
   out_3481270369411220980[303] = 0;
   out_3481270369411220980[304] = 1;
   out_3481270369411220980[305] = 0;
   out_3481270369411220980[306] = 0;
   out_3481270369411220980[307] = 0;
   out_3481270369411220980[308] = 0;
   out_3481270369411220980[309] = 0;
   out_3481270369411220980[310] = 0;
   out_3481270369411220980[311] = 0;
   out_3481270369411220980[312] = 0;
   out_3481270369411220980[313] = 0;
   out_3481270369411220980[314] = 0;
   out_3481270369411220980[315] = 0;
   out_3481270369411220980[316] = 0;
   out_3481270369411220980[317] = 0;
   out_3481270369411220980[318] = 0;
   out_3481270369411220980[319] = 0;
   out_3481270369411220980[320] = 0;
   out_3481270369411220980[321] = 0;
   out_3481270369411220980[322] = 0;
   out_3481270369411220980[323] = 1;
}
void h_4(double *state, double *unused, double *out_7159453629796036478) {
   out_7159453629796036478[0] = state[6] + state[9];
   out_7159453629796036478[1] = state[7] + state[10];
   out_7159453629796036478[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6817006287243338004) {
   out_6817006287243338004[0] = 0;
   out_6817006287243338004[1] = 0;
   out_6817006287243338004[2] = 0;
   out_6817006287243338004[3] = 0;
   out_6817006287243338004[4] = 0;
   out_6817006287243338004[5] = 0;
   out_6817006287243338004[6] = 1;
   out_6817006287243338004[7] = 0;
   out_6817006287243338004[8] = 0;
   out_6817006287243338004[9] = 1;
   out_6817006287243338004[10] = 0;
   out_6817006287243338004[11] = 0;
   out_6817006287243338004[12] = 0;
   out_6817006287243338004[13] = 0;
   out_6817006287243338004[14] = 0;
   out_6817006287243338004[15] = 0;
   out_6817006287243338004[16] = 0;
   out_6817006287243338004[17] = 0;
   out_6817006287243338004[18] = 0;
   out_6817006287243338004[19] = 0;
   out_6817006287243338004[20] = 0;
   out_6817006287243338004[21] = 0;
   out_6817006287243338004[22] = 0;
   out_6817006287243338004[23] = 0;
   out_6817006287243338004[24] = 0;
   out_6817006287243338004[25] = 1;
   out_6817006287243338004[26] = 0;
   out_6817006287243338004[27] = 0;
   out_6817006287243338004[28] = 1;
   out_6817006287243338004[29] = 0;
   out_6817006287243338004[30] = 0;
   out_6817006287243338004[31] = 0;
   out_6817006287243338004[32] = 0;
   out_6817006287243338004[33] = 0;
   out_6817006287243338004[34] = 0;
   out_6817006287243338004[35] = 0;
   out_6817006287243338004[36] = 0;
   out_6817006287243338004[37] = 0;
   out_6817006287243338004[38] = 0;
   out_6817006287243338004[39] = 0;
   out_6817006287243338004[40] = 0;
   out_6817006287243338004[41] = 0;
   out_6817006287243338004[42] = 0;
   out_6817006287243338004[43] = 0;
   out_6817006287243338004[44] = 1;
   out_6817006287243338004[45] = 0;
   out_6817006287243338004[46] = 0;
   out_6817006287243338004[47] = 1;
   out_6817006287243338004[48] = 0;
   out_6817006287243338004[49] = 0;
   out_6817006287243338004[50] = 0;
   out_6817006287243338004[51] = 0;
   out_6817006287243338004[52] = 0;
   out_6817006287243338004[53] = 0;
}
void h_10(double *state, double *unused, double *out_8919665046689555279) {
   out_8919665046689555279[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_8919665046689555279[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_8919665046689555279[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5719523531190417023) {
   out_5719523531190417023[0] = 0;
   out_5719523531190417023[1] = 9.8100000000000005*cos(state[1]);
   out_5719523531190417023[2] = 0;
   out_5719523531190417023[3] = 0;
   out_5719523531190417023[4] = -state[8];
   out_5719523531190417023[5] = state[7];
   out_5719523531190417023[6] = 0;
   out_5719523531190417023[7] = state[5];
   out_5719523531190417023[8] = -state[4];
   out_5719523531190417023[9] = 0;
   out_5719523531190417023[10] = 0;
   out_5719523531190417023[11] = 0;
   out_5719523531190417023[12] = 1;
   out_5719523531190417023[13] = 0;
   out_5719523531190417023[14] = 0;
   out_5719523531190417023[15] = 1;
   out_5719523531190417023[16] = 0;
   out_5719523531190417023[17] = 0;
   out_5719523531190417023[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5719523531190417023[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5719523531190417023[20] = 0;
   out_5719523531190417023[21] = state[8];
   out_5719523531190417023[22] = 0;
   out_5719523531190417023[23] = -state[6];
   out_5719523531190417023[24] = -state[5];
   out_5719523531190417023[25] = 0;
   out_5719523531190417023[26] = state[3];
   out_5719523531190417023[27] = 0;
   out_5719523531190417023[28] = 0;
   out_5719523531190417023[29] = 0;
   out_5719523531190417023[30] = 0;
   out_5719523531190417023[31] = 1;
   out_5719523531190417023[32] = 0;
   out_5719523531190417023[33] = 0;
   out_5719523531190417023[34] = 1;
   out_5719523531190417023[35] = 0;
   out_5719523531190417023[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5719523531190417023[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5719523531190417023[38] = 0;
   out_5719523531190417023[39] = -state[7];
   out_5719523531190417023[40] = state[6];
   out_5719523531190417023[41] = 0;
   out_5719523531190417023[42] = state[4];
   out_5719523531190417023[43] = -state[3];
   out_5719523531190417023[44] = 0;
   out_5719523531190417023[45] = 0;
   out_5719523531190417023[46] = 0;
   out_5719523531190417023[47] = 0;
   out_5719523531190417023[48] = 0;
   out_5719523531190417023[49] = 0;
   out_5719523531190417023[50] = 1;
   out_5719523531190417023[51] = 0;
   out_5719523531190417023[52] = 0;
   out_5719523531190417023[53] = 1;
}
void h_13(double *state, double *unused, double *out_6831827799770286357) {
   out_6831827799770286357[0] = state[3];
   out_6831827799770286357[1] = state[4];
   out_6831827799770286357[2] = state[5];
}
void H_13(double *state, double *unused, double *out_8417463961133880811) {
   out_8417463961133880811[0] = 0;
   out_8417463961133880811[1] = 0;
   out_8417463961133880811[2] = 0;
   out_8417463961133880811[3] = 1;
   out_8417463961133880811[4] = 0;
   out_8417463961133880811[5] = 0;
   out_8417463961133880811[6] = 0;
   out_8417463961133880811[7] = 0;
   out_8417463961133880811[8] = 0;
   out_8417463961133880811[9] = 0;
   out_8417463961133880811[10] = 0;
   out_8417463961133880811[11] = 0;
   out_8417463961133880811[12] = 0;
   out_8417463961133880811[13] = 0;
   out_8417463961133880811[14] = 0;
   out_8417463961133880811[15] = 0;
   out_8417463961133880811[16] = 0;
   out_8417463961133880811[17] = 0;
   out_8417463961133880811[18] = 0;
   out_8417463961133880811[19] = 0;
   out_8417463961133880811[20] = 0;
   out_8417463961133880811[21] = 0;
   out_8417463961133880811[22] = 1;
   out_8417463961133880811[23] = 0;
   out_8417463961133880811[24] = 0;
   out_8417463961133880811[25] = 0;
   out_8417463961133880811[26] = 0;
   out_8417463961133880811[27] = 0;
   out_8417463961133880811[28] = 0;
   out_8417463961133880811[29] = 0;
   out_8417463961133880811[30] = 0;
   out_8417463961133880811[31] = 0;
   out_8417463961133880811[32] = 0;
   out_8417463961133880811[33] = 0;
   out_8417463961133880811[34] = 0;
   out_8417463961133880811[35] = 0;
   out_8417463961133880811[36] = 0;
   out_8417463961133880811[37] = 0;
   out_8417463961133880811[38] = 0;
   out_8417463961133880811[39] = 0;
   out_8417463961133880811[40] = 0;
   out_8417463961133880811[41] = 1;
   out_8417463961133880811[42] = 0;
   out_8417463961133880811[43] = 0;
   out_8417463961133880811[44] = 0;
   out_8417463961133880811[45] = 0;
   out_8417463961133880811[46] = 0;
   out_8417463961133880811[47] = 0;
   out_8417463961133880811[48] = 0;
   out_8417463961133880811[49] = 0;
   out_8417463961133880811[50] = 0;
   out_8417463961133880811[51] = 0;
   out_8417463961133880811[52] = 0;
   out_8417463961133880811[53] = 0;
}
void h_14(double *state, double *unused, double *out_5444267422335175417) {
   out_5444267422335175417[0] = state[6];
   out_5444267422335175417[1] = state[7];
   out_5444267422335175417[2] = state[8];
}
void H_14(double *state, double *unused, double *out_7666496930126729083) {
   out_7666496930126729083[0] = 0;
   out_7666496930126729083[1] = 0;
   out_7666496930126729083[2] = 0;
   out_7666496930126729083[3] = 0;
   out_7666496930126729083[4] = 0;
   out_7666496930126729083[5] = 0;
   out_7666496930126729083[6] = 1;
   out_7666496930126729083[7] = 0;
   out_7666496930126729083[8] = 0;
   out_7666496930126729083[9] = 0;
   out_7666496930126729083[10] = 0;
   out_7666496930126729083[11] = 0;
   out_7666496930126729083[12] = 0;
   out_7666496930126729083[13] = 0;
   out_7666496930126729083[14] = 0;
   out_7666496930126729083[15] = 0;
   out_7666496930126729083[16] = 0;
   out_7666496930126729083[17] = 0;
   out_7666496930126729083[18] = 0;
   out_7666496930126729083[19] = 0;
   out_7666496930126729083[20] = 0;
   out_7666496930126729083[21] = 0;
   out_7666496930126729083[22] = 0;
   out_7666496930126729083[23] = 0;
   out_7666496930126729083[24] = 0;
   out_7666496930126729083[25] = 1;
   out_7666496930126729083[26] = 0;
   out_7666496930126729083[27] = 0;
   out_7666496930126729083[28] = 0;
   out_7666496930126729083[29] = 0;
   out_7666496930126729083[30] = 0;
   out_7666496930126729083[31] = 0;
   out_7666496930126729083[32] = 0;
   out_7666496930126729083[33] = 0;
   out_7666496930126729083[34] = 0;
   out_7666496930126729083[35] = 0;
   out_7666496930126729083[36] = 0;
   out_7666496930126729083[37] = 0;
   out_7666496930126729083[38] = 0;
   out_7666496930126729083[39] = 0;
   out_7666496930126729083[40] = 0;
   out_7666496930126729083[41] = 0;
   out_7666496930126729083[42] = 0;
   out_7666496930126729083[43] = 0;
   out_7666496930126729083[44] = 1;
   out_7666496930126729083[45] = 0;
   out_7666496930126729083[46] = 0;
   out_7666496930126729083[47] = 0;
   out_7666496930126729083[48] = 0;
   out_7666496930126729083[49] = 0;
   out_7666496930126729083[50] = 0;
   out_7666496930126729083[51] = 0;
   out_7666496930126729083[52] = 0;
   out_7666496930126729083[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3590467737713675004) {
  err_fun(nom_x, delta_x, out_3590467737713675004);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_837876479050183132) {
  inv_err_fun(nom_x, true_x, out_837876479050183132);
}
void pose_H_mod_fun(double *state, double *out_5781655979714254891) {
  H_mod_fun(state, out_5781655979714254891);
}
void pose_f_fun(double *state, double dt, double *out_2390805150352098946) {
  f_fun(state,  dt, out_2390805150352098946);
}
void pose_F_fun(double *state, double dt, double *out_3481270369411220980) {
  F_fun(state,  dt, out_3481270369411220980);
}
void pose_h_4(double *state, double *unused, double *out_7159453629796036478) {
  h_4(state, unused, out_7159453629796036478);
}
void pose_H_4(double *state, double *unused, double *out_6817006287243338004) {
  H_4(state, unused, out_6817006287243338004);
}
void pose_h_10(double *state, double *unused, double *out_8919665046689555279) {
  h_10(state, unused, out_8919665046689555279);
}
void pose_H_10(double *state, double *unused, double *out_5719523531190417023) {
  H_10(state, unused, out_5719523531190417023);
}
void pose_h_13(double *state, double *unused, double *out_6831827799770286357) {
  h_13(state, unused, out_6831827799770286357);
}
void pose_H_13(double *state, double *unused, double *out_8417463961133880811) {
  H_13(state, unused, out_8417463961133880811);
}
void pose_h_14(double *state, double *unused, double *out_5444267422335175417) {
  h_14(state, unused, out_5444267422335175417);
}
void pose_H_14(double *state, double *unused, double *out_7666496930126729083) {
  H_14(state, unused, out_7666496930126729083);
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
