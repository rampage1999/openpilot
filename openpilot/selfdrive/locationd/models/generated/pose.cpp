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
void err_fun(double *nom_x, double *delta_x, double *out_7473524147338108814) {
   out_7473524147338108814[0] = delta_x[0] + nom_x[0];
   out_7473524147338108814[1] = delta_x[1] + nom_x[1];
   out_7473524147338108814[2] = delta_x[2] + nom_x[2];
   out_7473524147338108814[3] = delta_x[3] + nom_x[3];
   out_7473524147338108814[4] = delta_x[4] + nom_x[4];
   out_7473524147338108814[5] = delta_x[5] + nom_x[5];
   out_7473524147338108814[6] = delta_x[6] + nom_x[6];
   out_7473524147338108814[7] = delta_x[7] + nom_x[7];
   out_7473524147338108814[8] = delta_x[8] + nom_x[8];
   out_7473524147338108814[9] = delta_x[9] + nom_x[9];
   out_7473524147338108814[10] = delta_x[10] + nom_x[10];
   out_7473524147338108814[11] = delta_x[11] + nom_x[11];
   out_7473524147338108814[12] = delta_x[12] + nom_x[12];
   out_7473524147338108814[13] = delta_x[13] + nom_x[13];
   out_7473524147338108814[14] = delta_x[14] + nom_x[14];
   out_7473524147338108814[15] = delta_x[15] + nom_x[15];
   out_7473524147338108814[16] = delta_x[16] + nom_x[16];
   out_7473524147338108814[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1225327672199224143) {
   out_1225327672199224143[0] = -nom_x[0] + true_x[0];
   out_1225327672199224143[1] = -nom_x[1] + true_x[1];
   out_1225327672199224143[2] = -nom_x[2] + true_x[2];
   out_1225327672199224143[3] = -nom_x[3] + true_x[3];
   out_1225327672199224143[4] = -nom_x[4] + true_x[4];
   out_1225327672199224143[5] = -nom_x[5] + true_x[5];
   out_1225327672199224143[6] = -nom_x[6] + true_x[6];
   out_1225327672199224143[7] = -nom_x[7] + true_x[7];
   out_1225327672199224143[8] = -nom_x[8] + true_x[8];
   out_1225327672199224143[9] = -nom_x[9] + true_x[9];
   out_1225327672199224143[10] = -nom_x[10] + true_x[10];
   out_1225327672199224143[11] = -nom_x[11] + true_x[11];
   out_1225327672199224143[12] = -nom_x[12] + true_x[12];
   out_1225327672199224143[13] = -nom_x[13] + true_x[13];
   out_1225327672199224143[14] = -nom_x[14] + true_x[14];
   out_1225327672199224143[15] = -nom_x[15] + true_x[15];
   out_1225327672199224143[16] = -nom_x[16] + true_x[16];
   out_1225327672199224143[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_962358481072545828) {
   out_962358481072545828[0] = 1.0;
   out_962358481072545828[1] = 0.0;
   out_962358481072545828[2] = 0.0;
   out_962358481072545828[3] = 0.0;
   out_962358481072545828[4] = 0.0;
   out_962358481072545828[5] = 0.0;
   out_962358481072545828[6] = 0.0;
   out_962358481072545828[7] = 0.0;
   out_962358481072545828[8] = 0.0;
   out_962358481072545828[9] = 0.0;
   out_962358481072545828[10] = 0.0;
   out_962358481072545828[11] = 0.0;
   out_962358481072545828[12] = 0.0;
   out_962358481072545828[13] = 0.0;
   out_962358481072545828[14] = 0.0;
   out_962358481072545828[15] = 0.0;
   out_962358481072545828[16] = 0.0;
   out_962358481072545828[17] = 0.0;
   out_962358481072545828[18] = 0.0;
   out_962358481072545828[19] = 1.0;
   out_962358481072545828[20] = 0.0;
   out_962358481072545828[21] = 0.0;
   out_962358481072545828[22] = 0.0;
   out_962358481072545828[23] = 0.0;
   out_962358481072545828[24] = 0.0;
   out_962358481072545828[25] = 0.0;
   out_962358481072545828[26] = 0.0;
   out_962358481072545828[27] = 0.0;
   out_962358481072545828[28] = 0.0;
   out_962358481072545828[29] = 0.0;
   out_962358481072545828[30] = 0.0;
   out_962358481072545828[31] = 0.0;
   out_962358481072545828[32] = 0.0;
   out_962358481072545828[33] = 0.0;
   out_962358481072545828[34] = 0.0;
   out_962358481072545828[35] = 0.0;
   out_962358481072545828[36] = 0.0;
   out_962358481072545828[37] = 0.0;
   out_962358481072545828[38] = 1.0;
   out_962358481072545828[39] = 0.0;
   out_962358481072545828[40] = 0.0;
   out_962358481072545828[41] = 0.0;
   out_962358481072545828[42] = 0.0;
   out_962358481072545828[43] = 0.0;
   out_962358481072545828[44] = 0.0;
   out_962358481072545828[45] = 0.0;
   out_962358481072545828[46] = 0.0;
   out_962358481072545828[47] = 0.0;
   out_962358481072545828[48] = 0.0;
   out_962358481072545828[49] = 0.0;
   out_962358481072545828[50] = 0.0;
   out_962358481072545828[51] = 0.0;
   out_962358481072545828[52] = 0.0;
   out_962358481072545828[53] = 0.0;
   out_962358481072545828[54] = 0.0;
   out_962358481072545828[55] = 0.0;
   out_962358481072545828[56] = 0.0;
   out_962358481072545828[57] = 1.0;
   out_962358481072545828[58] = 0.0;
   out_962358481072545828[59] = 0.0;
   out_962358481072545828[60] = 0.0;
   out_962358481072545828[61] = 0.0;
   out_962358481072545828[62] = 0.0;
   out_962358481072545828[63] = 0.0;
   out_962358481072545828[64] = 0.0;
   out_962358481072545828[65] = 0.0;
   out_962358481072545828[66] = 0.0;
   out_962358481072545828[67] = 0.0;
   out_962358481072545828[68] = 0.0;
   out_962358481072545828[69] = 0.0;
   out_962358481072545828[70] = 0.0;
   out_962358481072545828[71] = 0.0;
   out_962358481072545828[72] = 0.0;
   out_962358481072545828[73] = 0.0;
   out_962358481072545828[74] = 0.0;
   out_962358481072545828[75] = 0.0;
   out_962358481072545828[76] = 1.0;
   out_962358481072545828[77] = 0.0;
   out_962358481072545828[78] = 0.0;
   out_962358481072545828[79] = 0.0;
   out_962358481072545828[80] = 0.0;
   out_962358481072545828[81] = 0.0;
   out_962358481072545828[82] = 0.0;
   out_962358481072545828[83] = 0.0;
   out_962358481072545828[84] = 0.0;
   out_962358481072545828[85] = 0.0;
   out_962358481072545828[86] = 0.0;
   out_962358481072545828[87] = 0.0;
   out_962358481072545828[88] = 0.0;
   out_962358481072545828[89] = 0.0;
   out_962358481072545828[90] = 0.0;
   out_962358481072545828[91] = 0.0;
   out_962358481072545828[92] = 0.0;
   out_962358481072545828[93] = 0.0;
   out_962358481072545828[94] = 0.0;
   out_962358481072545828[95] = 1.0;
   out_962358481072545828[96] = 0.0;
   out_962358481072545828[97] = 0.0;
   out_962358481072545828[98] = 0.0;
   out_962358481072545828[99] = 0.0;
   out_962358481072545828[100] = 0.0;
   out_962358481072545828[101] = 0.0;
   out_962358481072545828[102] = 0.0;
   out_962358481072545828[103] = 0.0;
   out_962358481072545828[104] = 0.0;
   out_962358481072545828[105] = 0.0;
   out_962358481072545828[106] = 0.0;
   out_962358481072545828[107] = 0.0;
   out_962358481072545828[108] = 0.0;
   out_962358481072545828[109] = 0.0;
   out_962358481072545828[110] = 0.0;
   out_962358481072545828[111] = 0.0;
   out_962358481072545828[112] = 0.0;
   out_962358481072545828[113] = 0.0;
   out_962358481072545828[114] = 1.0;
   out_962358481072545828[115] = 0.0;
   out_962358481072545828[116] = 0.0;
   out_962358481072545828[117] = 0.0;
   out_962358481072545828[118] = 0.0;
   out_962358481072545828[119] = 0.0;
   out_962358481072545828[120] = 0.0;
   out_962358481072545828[121] = 0.0;
   out_962358481072545828[122] = 0.0;
   out_962358481072545828[123] = 0.0;
   out_962358481072545828[124] = 0.0;
   out_962358481072545828[125] = 0.0;
   out_962358481072545828[126] = 0.0;
   out_962358481072545828[127] = 0.0;
   out_962358481072545828[128] = 0.0;
   out_962358481072545828[129] = 0.0;
   out_962358481072545828[130] = 0.0;
   out_962358481072545828[131] = 0.0;
   out_962358481072545828[132] = 0.0;
   out_962358481072545828[133] = 1.0;
   out_962358481072545828[134] = 0.0;
   out_962358481072545828[135] = 0.0;
   out_962358481072545828[136] = 0.0;
   out_962358481072545828[137] = 0.0;
   out_962358481072545828[138] = 0.0;
   out_962358481072545828[139] = 0.0;
   out_962358481072545828[140] = 0.0;
   out_962358481072545828[141] = 0.0;
   out_962358481072545828[142] = 0.0;
   out_962358481072545828[143] = 0.0;
   out_962358481072545828[144] = 0.0;
   out_962358481072545828[145] = 0.0;
   out_962358481072545828[146] = 0.0;
   out_962358481072545828[147] = 0.0;
   out_962358481072545828[148] = 0.0;
   out_962358481072545828[149] = 0.0;
   out_962358481072545828[150] = 0.0;
   out_962358481072545828[151] = 0.0;
   out_962358481072545828[152] = 1.0;
   out_962358481072545828[153] = 0.0;
   out_962358481072545828[154] = 0.0;
   out_962358481072545828[155] = 0.0;
   out_962358481072545828[156] = 0.0;
   out_962358481072545828[157] = 0.0;
   out_962358481072545828[158] = 0.0;
   out_962358481072545828[159] = 0.0;
   out_962358481072545828[160] = 0.0;
   out_962358481072545828[161] = 0.0;
   out_962358481072545828[162] = 0.0;
   out_962358481072545828[163] = 0.0;
   out_962358481072545828[164] = 0.0;
   out_962358481072545828[165] = 0.0;
   out_962358481072545828[166] = 0.0;
   out_962358481072545828[167] = 0.0;
   out_962358481072545828[168] = 0.0;
   out_962358481072545828[169] = 0.0;
   out_962358481072545828[170] = 0.0;
   out_962358481072545828[171] = 1.0;
   out_962358481072545828[172] = 0.0;
   out_962358481072545828[173] = 0.0;
   out_962358481072545828[174] = 0.0;
   out_962358481072545828[175] = 0.0;
   out_962358481072545828[176] = 0.0;
   out_962358481072545828[177] = 0.0;
   out_962358481072545828[178] = 0.0;
   out_962358481072545828[179] = 0.0;
   out_962358481072545828[180] = 0.0;
   out_962358481072545828[181] = 0.0;
   out_962358481072545828[182] = 0.0;
   out_962358481072545828[183] = 0.0;
   out_962358481072545828[184] = 0.0;
   out_962358481072545828[185] = 0.0;
   out_962358481072545828[186] = 0.0;
   out_962358481072545828[187] = 0.0;
   out_962358481072545828[188] = 0.0;
   out_962358481072545828[189] = 0.0;
   out_962358481072545828[190] = 1.0;
   out_962358481072545828[191] = 0.0;
   out_962358481072545828[192] = 0.0;
   out_962358481072545828[193] = 0.0;
   out_962358481072545828[194] = 0.0;
   out_962358481072545828[195] = 0.0;
   out_962358481072545828[196] = 0.0;
   out_962358481072545828[197] = 0.0;
   out_962358481072545828[198] = 0.0;
   out_962358481072545828[199] = 0.0;
   out_962358481072545828[200] = 0.0;
   out_962358481072545828[201] = 0.0;
   out_962358481072545828[202] = 0.0;
   out_962358481072545828[203] = 0.0;
   out_962358481072545828[204] = 0.0;
   out_962358481072545828[205] = 0.0;
   out_962358481072545828[206] = 0.0;
   out_962358481072545828[207] = 0.0;
   out_962358481072545828[208] = 0.0;
   out_962358481072545828[209] = 1.0;
   out_962358481072545828[210] = 0.0;
   out_962358481072545828[211] = 0.0;
   out_962358481072545828[212] = 0.0;
   out_962358481072545828[213] = 0.0;
   out_962358481072545828[214] = 0.0;
   out_962358481072545828[215] = 0.0;
   out_962358481072545828[216] = 0.0;
   out_962358481072545828[217] = 0.0;
   out_962358481072545828[218] = 0.0;
   out_962358481072545828[219] = 0.0;
   out_962358481072545828[220] = 0.0;
   out_962358481072545828[221] = 0.0;
   out_962358481072545828[222] = 0.0;
   out_962358481072545828[223] = 0.0;
   out_962358481072545828[224] = 0.0;
   out_962358481072545828[225] = 0.0;
   out_962358481072545828[226] = 0.0;
   out_962358481072545828[227] = 0.0;
   out_962358481072545828[228] = 1.0;
   out_962358481072545828[229] = 0.0;
   out_962358481072545828[230] = 0.0;
   out_962358481072545828[231] = 0.0;
   out_962358481072545828[232] = 0.0;
   out_962358481072545828[233] = 0.0;
   out_962358481072545828[234] = 0.0;
   out_962358481072545828[235] = 0.0;
   out_962358481072545828[236] = 0.0;
   out_962358481072545828[237] = 0.0;
   out_962358481072545828[238] = 0.0;
   out_962358481072545828[239] = 0.0;
   out_962358481072545828[240] = 0.0;
   out_962358481072545828[241] = 0.0;
   out_962358481072545828[242] = 0.0;
   out_962358481072545828[243] = 0.0;
   out_962358481072545828[244] = 0.0;
   out_962358481072545828[245] = 0.0;
   out_962358481072545828[246] = 0.0;
   out_962358481072545828[247] = 1.0;
   out_962358481072545828[248] = 0.0;
   out_962358481072545828[249] = 0.0;
   out_962358481072545828[250] = 0.0;
   out_962358481072545828[251] = 0.0;
   out_962358481072545828[252] = 0.0;
   out_962358481072545828[253] = 0.0;
   out_962358481072545828[254] = 0.0;
   out_962358481072545828[255] = 0.0;
   out_962358481072545828[256] = 0.0;
   out_962358481072545828[257] = 0.0;
   out_962358481072545828[258] = 0.0;
   out_962358481072545828[259] = 0.0;
   out_962358481072545828[260] = 0.0;
   out_962358481072545828[261] = 0.0;
   out_962358481072545828[262] = 0.0;
   out_962358481072545828[263] = 0.0;
   out_962358481072545828[264] = 0.0;
   out_962358481072545828[265] = 0.0;
   out_962358481072545828[266] = 1.0;
   out_962358481072545828[267] = 0.0;
   out_962358481072545828[268] = 0.0;
   out_962358481072545828[269] = 0.0;
   out_962358481072545828[270] = 0.0;
   out_962358481072545828[271] = 0.0;
   out_962358481072545828[272] = 0.0;
   out_962358481072545828[273] = 0.0;
   out_962358481072545828[274] = 0.0;
   out_962358481072545828[275] = 0.0;
   out_962358481072545828[276] = 0.0;
   out_962358481072545828[277] = 0.0;
   out_962358481072545828[278] = 0.0;
   out_962358481072545828[279] = 0.0;
   out_962358481072545828[280] = 0.0;
   out_962358481072545828[281] = 0.0;
   out_962358481072545828[282] = 0.0;
   out_962358481072545828[283] = 0.0;
   out_962358481072545828[284] = 0.0;
   out_962358481072545828[285] = 1.0;
   out_962358481072545828[286] = 0.0;
   out_962358481072545828[287] = 0.0;
   out_962358481072545828[288] = 0.0;
   out_962358481072545828[289] = 0.0;
   out_962358481072545828[290] = 0.0;
   out_962358481072545828[291] = 0.0;
   out_962358481072545828[292] = 0.0;
   out_962358481072545828[293] = 0.0;
   out_962358481072545828[294] = 0.0;
   out_962358481072545828[295] = 0.0;
   out_962358481072545828[296] = 0.0;
   out_962358481072545828[297] = 0.0;
   out_962358481072545828[298] = 0.0;
   out_962358481072545828[299] = 0.0;
   out_962358481072545828[300] = 0.0;
   out_962358481072545828[301] = 0.0;
   out_962358481072545828[302] = 0.0;
   out_962358481072545828[303] = 0.0;
   out_962358481072545828[304] = 1.0;
   out_962358481072545828[305] = 0.0;
   out_962358481072545828[306] = 0.0;
   out_962358481072545828[307] = 0.0;
   out_962358481072545828[308] = 0.0;
   out_962358481072545828[309] = 0.0;
   out_962358481072545828[310] = 0.0;
   out_962358481072545828[311] = 0.0;
   out_962358481072545828[312] = 0.0;
   out_962358481072545828[313] = 0.0;
   out_962358481072545828[314] = 0.0;
   out_962358481072545828[315] = 0.0;
   out_962358481072545828[316] = 0.0;
   out_962358481072545828[317] = 0.0;
   out_962358481072545828[318] = 0.0;
   out_962358481072545828[319] = 0.0;
   out_962358481072545828[320] = 0.0;
   out_962358481072545828[321] = 0.0;
   out_962358481072545828[322] = 0.0;
   out_962358481072545828[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8886629790052716118) {
   out_8886629790052716118[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8886629790052716118[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8886629790052716118[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8886629790052716118[3] = dt*state[12] + state[3];
   out_8886629790052716118[4] = dt*state[13] + state[4];
   out_8886629790052716118[5] = dt*state[14] + state[5];
   out_8886629790052716118[6] = state[6];
   out_8886629790052716118[7] = state[7];
   out_8886629790052716118[8] = state[8];
   out_8886629790052716118[9] = state[9];
   out_8886629790052716118[10] = state[10];
   out_8886629790052716118[11] = state[11];
   out_8886629790052716118[12] = state[12];
   out_8886629790052716118[13] = state[13];
   out_8886629790052716118[14] = state[14];
   out_8886629790052716118[15] = state[15];
   out_8886629790052716118[16] = state[16];
   out_8886629790052716118[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8669821383571928839) {
   out_8669821383571928839[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8669821383571928839[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8669821383571928839[2] = 0;
   out_8669821383571928839[3] = 0;
   out_8669821383571928839[4] = 0;
   out_8669821383571928839[5] = 0;
   out_8669821383571928839[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8669821383571928839[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8669821383571928839[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8669821383571928839[9] = 0;
   out_8669821383571928839[10] = 0;
   out_8669821383571928839[11] = 0;
   out_8669821383571928839[12] = 0;
   out_8669821383571928839[13] = 0;
   out_8669821383571928839[14] = 0;
   out_8669821383571928839[15] = 0;
   out_8669821383571928839[16] = 0;
   out_8669821383571928839[17] = 0;
   out_8669821383571928839[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8669821383571928839[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8669821383571928839[20] = 0;
   out_8669821383571928839[21] = 0;
   out_8669821383571928839[22] = 0;
   out_8669821383571928839[23] = 0;
   out_8669821383571928839[24] = 0;
   out_8669821383571928839[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8669821383571928839[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8669821383571928839[27] = 0;
   out_8669821383571928839[28] = 0;
   out_8669821383571928839[29] = 0;
   out_8669821383571928839[30] = 0;
   out_8669821383571928839[31] = 0;
   out_8669821383571928839[32] = 0;
   out_8669821383571928839[33] = 0;
   out_8669821383571928839[34] = 0;
   out_8669821383571928839[35] = 0;
   out_8669821383571928839[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8669821383571928839[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8669821383571928839[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8669821383571928839[39] = 0;
   out_8669821383571928839[40] = 0;
   out_8669821383571928839[41] = 0;
   out_8669821383571928839[42] = 0;
   out_8669821383571928839[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8669821383571928839[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8669821383571928839[45] = 0;
   out_8669821383571928839[46] = 0;
   out_8669821383571928839[47] = 0;
   out_8669821383571928839[48] = 0;
   out_8669821383571928839[49] = 0;
   out_8669821383571928839[50] = 0;
   out_8669821383571928839[51] = 0;
   out_8669821383571928839[52] = 0;
   out_8669821383571928839[53] = 0;
   out_8669821383571928839[54] = 0;
   out_8669821383571928839[55] = 0;
   out_8669821383571928839[56] = 0;
   out_8669821383571928839[57] = 1;
   out_8669821383571928839[58] = 0;
   out_8669821383571928839[59] = 0;
   out_8669821383571928839[60] = 0;
   out_8669821383571928839[61] = 0;
   out_8669821383571928839[62] = 0;
   out_8669821383571928839[63] = 0;
   out_8669821383571928839[64] = 0;
   out_8669821383571928839[65] = 0;
   out_8669821383571928839[66] = dt;
   out_8669821383571928839[67] = 0;
   out_8669821383571928839[68] = 0;
   out_8669821383571928839[69] = 0;
   out_8669821383571928839[70] = 0;
   out_8669821383571928839[71] = 0;
   out_8669821383571928839[72] = 0;
   out_8669821383571928839[73] = 0;
   out_8669821383571928839[74] = 0;
   out_8669821383571928839[75] = 0;
   out_8669821383571928839[76] = 1;
   out_8669821383571928839[77] = 0;
   out_8669821383571928839[78] = 0;
   out_8669821383571928839[79] = 0;
   out_8669821383571928839[80] = 0;
   out_8669821383571928839[81] = 0;
   out_8669821383571928839[82] = 0;
   out_8669821383571928839[83] = 0;
   out_8669821383571928839[84] = 0;
   out_8669821383571928839[85] = dt;
   out_8669821383571928839[86] = 0;
   out_8669821383571928839[87] = 0;
   out_8669821383571928839[88] = 0;
   out_8669821383571928839[89] = 0;
   out_8669821383571928839[90] = 0;
   out_8669821383571928839[91] = 0;
   out_8669821383571928839[92] = 0;
   out_8669821383571928839[93] = 0;
   out_8669821383571928839[94] = 0;
   out_8669821383571928839[95] = 1;
   out_8669821383571928839[96] = 0;
   out_8669821383571928839[97] = 0;
   out_8669821383571928839[98] = 0;
   out_8669821383571928839[99] = 0;
   out_8669821383571928839[100] = 0;
   out_8669821383571928839[101] = 0;
   out_8669821383571928839[102] = 0;
   out_8669821383571928839[103] = 0;
   out_8669821383571928839[104] = dt;
   out_8669821383571928839[105] = 0;
   out_8669821383571928839[106] = 0;
   out_8669821383571928839[107] = 0;
   out_8669821383571928839[108] = 0;
   out_8669821383571928839[109] = 0;
   out_8669821383571928839[110] = 0;
   out_8669821383571928839[111] = 0;
   out_8669821383571928839[112] = 0;
   out_8669821383571928839[113] = 0;
   out_8669821383571928839[114] = 1;
   out_8669821383571928839[115] = 0;
   out_8669821383571928839[116] = 0;
   out_8669821383571928839[117] = 0;
   out_8669821383571928839[118] = 0;
   out_8669821383571928839[119] = 0;
   out_8669821383571928839[120] = 0;
   out_8669821383571928839[121] = 0;
   out_8669821383571928839[122] = 0;
   out_8669821383571928839[123] = 0;
   out_8669821383571928839[124] = 0;
   out_8669821383571928839[125] = 0;
   out_8669821383571928839[126] = 0;
   out_8669821383571928839[127] = 0;
   out_8669821383571928839[128] = 0;
   out_8669821383571928839[129] = 0;
   out_8669821383571928839[130] = 0;
   out_8669821383571928839[131] = 0;
   out_8669821383571928839[132] = 0;
   out_8669821383571928839[133] = 1;
   out_8669821383571928839[134] = 0;
   out_8669821383571928839[135] = 0;
   out_8669821383571928839[136] = 0;
   out_8669821383571928839[137] = 0;
   out_8669821383571928839[138] = 0;
   out_8669821383571928839[139] = 0;
   out_8669821383571928839[140] = 0;
   out_8669821383571928839[141] = 0;
   out_8669821383571928839[142] = 0;
   out_8669821383571928839[143] = 0;
   out_8669821383571928839[144] = 0;
   out_8669821383571928839[145] = 0;
   out_8669821383571928839[146] = 0;
   out_8669821383571928839[147] = 0;
   out_8669821383571928839[148] = 0;
   out_8669821383571928839[149] = 0;
   out_8669821383571928839[150] = 0;
   out_8669821383571928839[151] = 0;
   out_8669821383571928839[152] = 1;
   out_8669821383571928839[153] = 0;
   out_8669821383571928839[154] = 0;
   out_8669821383571928839[155] = 0;
   out_8669821383571928839[156] = 0;
   out_8669821383571928839[157] = 0;
   out_8669821383571928839[158] = 0;
   out_8669821383571928839[159] = 0;
   out_8669821383571928839[160] = 0;
   out_8669821383571928839[161] = 0;
   out_8669821383571928839[162] = 0;
   out_8669821383571928839[163] = 0;
   out_8669821383571928839[164] = 0;
   out_8669821383571928839[165] = 0;
   out_8669821383571928839[166] = 0;
   out_8669821383571928839[167] = 0;
   out_8669821383571928839[168] = 0;
   out_8669821383571928839[169] = 0;
   out_8669821383571928839[170] = 0;
   out_8669821383571928839[171] = 1;
   out_8669821383571928839[172] = 0;
   out_8669821383571928839[173] = 0;
   out_8669821383571928839[174] = 0;
   out_8669821383571928839[175] = 0;
   out_8669821383571928839[176] = 0;
   out_8669821383571928839[177] = 0;
   out_8669821383571928839[178] = 0;
   out_8669821383571928839[179] = 0;
   out_8669821383571928839[180] = 0;
   out_8669821383571928839[181] = 0;
   out_8669821383571928839[182] = 0;
   out_8669821383571928839[183] = 0;
   out_8669821383571928839[184] = 0;
   out_8669821383571928839[185] = 0;
   out_8669821383571928839[186] = 0;
   out_8669821383571928839[187] = 0;
   out_8669821383571928839[188] = 0;
   out_8669821383571928839[189] = 0;
   out_8669821383571928839[190] = 1;
   out_8669821383571928839[191] = 0;
   out_8669821383571928839[192] = 0;
   out_8669821383571928839[193] = 0;
   out_8669821383571928839[194] = 0;
   out_8669821383571928839[195] = 0;
   out_8669821383571928839[196] = 0;
   out_8669821383571928839[197] = 0;
   out_8669821383571928839[198] = 0;
   out_8669821383571928839[199] = 0;
   out_8669821383571928839[200] = 0;
   out_8669821383571928839[201] = 0;
   out_8669821383571928839[202] = 0;
   out_8669821383571928839[203] = 0;
   out_8669821383571928839[204] = 0;
   out_8669821383571928839[205] = 0;
   out_8669821383571928839[206] = 0;
   out_8669821383571928839[207] = 0;
   out_8669821383571928839[208] = 0;
   out_8669821383571928839[209] = 1;
   out_8669821383571928839[210] = 0;
   out_8669821383571928839[211] = 0;
   out_8669821383571928839[212] = 0;
   out_8669821383571928839[213] = 0;
   out_8669821383571928839[214] = 0;
   out_8669821383571928839[215] = 0;
   out_8669821383571928839[216] = 0;
   out_8669821383571928839[217] = 0;
   out_8669821383571928839[218] = 0;
   out_8669821383571928839[219] = 0;
   out_8669821383571928839[220] = 0;
   out_8669821383571928839[221] = 0;
   out_8669821383571928839[222] = 0;
   out_8669821383571928839[223] = 0;
   out_8669821383571928839[224] = 0;
   out_8669821383571928839[225] = 0;
   out_8669821383571928839[226] = 0;
   out_8669821383571928839[227] = 0;
   out_8669821383571928839[228] = 1;
   out_8669821383571928839[229] = 0;
   out_8669821383571928839[230] = 0;
   out_8669821383571928839[231] = 0;
   out_8669821383571928839[232] = 0;
   out_8669821383571928839[233] = 0;
   out_8669821383571928839[234] = 0;
   out_8669821383571928839[235] = 0;
   out_8669821383571928839[236] = 0;
   out_8669821383571928839[237] = 0;
   out_8669821383571928839[238] = 0;
   out_8669821383571928839[239] = 0;
   out_8669821383571928839[240] = 0;
   out_8669821383571928839[241] = 0;
   out_8669821383571928839[242] = 0;
   out_8669821383571928839[243] = 0;
   out_8669821383571928839[244] = 0;
   out_8669821383571928839[245] = 0;
   out_8669821383571928839[246] = 0;
   out_8669821383571928839[247] = 1;
   out_8669821383571928839[248] = 0;
   out_8669821383571928839[249] = 0;
   out_8669821383571928839[250] = 0;
   out_8669821383571928839[251] = 0;
   out_8669821383571928839[252] = 0;
   out_8669821383571928839[253] = 0;
   out_8669821383571928839[254] = 0;
   out_8669821383571928839[255] = 0;
   out_8669821383571928839[256] = 0;
   out_8669821383571928839[257] = 0;
   out_8669821383571928839[258] = 0;
   out_8669821383571928839[259] = 0;
   out_8669821383571928839[260] = 0;
   out_8669821383571928839[261] = 0;
   out_8669821383571928839[262] = 0;
   out_8669821383571928839[263] = 0;
   out_8669821383571928839[264] = 0;
   out_8669821383571928839[265] = 0;
   out_8669821383571928839[266] = 1;
   out_8669821383571928839[267] = 0;
   out_8669821383571928839[268] = 0;
   out_8669821383571928839[269] = 0;
   out_8669821383571928839[270] = 0;
   out_8669821383571928839[271] = 0;
   out_8669821383571928839[272] = 0;
   out_8669821383571928839[273] = 0;
   out_8669821383571928839[274] = 0;
   out_8669821383571928839[275] = 0;
   out_8669821383571928839[276] = 0;
   out_8669821383571928839[277] = 0;
   out_8669821383571928839[278] = 0;
   out_8669821383571928839[279] = 0;
   out_8669821383571928839[280] = 0;
   out_8669821383571928839[281] = 0;
   out_8669821383571928839[282] = 0;
   out_8669821383571928839[283] = 0;
   out_8669821383571928839[284] = 0;
   out_8669821383571928839[285] = 1;
   out_8669821383571928839[286] = 0;
   out_8669821383571928839[287] = 0;
   out_8669821383571928839[288] = 0;
   out_8669821383571928839[289] = 0;
   out_8669821383571928839[290] = 0;
   out_8669821383571928839[291] = 0;
   out_8669821383571928839[292] = 0;
   out_8669821383571928839[293] = 0;
   out_8669821383571928839[294] = 0;
   out_8669821383571928839[295] = 0;
   out_8669821383571928839[296] = 0;
   out_8669821383571928839[297] = 0;
   out_8669821383571928839[298] = 0;
   out_8669821383571928839[299] = 0;
   out_8669821383571928839[300] = 0;
   out_8669821383571928839[301] = 0;
   out_8669821383571928839[302] = 0;
   out_8669821383571928839[303] = 0;
   out_8669821383571928839[304] = 1;
   out_8669821383571928839[305] = 0;
   out_8669821383571928839[306] = 0;
   out_8669821383571928839[307] = 0;
   out_8669821383571928839[308] = 0;
   out_8669821383571928839[309] = 0;
   out_8669821383571928839[310] = 0;
   out_8669821383571928839[311] = 0;
   out_8669821383571928839[312] = 0;
   out_8669821383571928839[313] = 0;
   out_8669821383571928839[314] = 0;
   out_8669821383571928839[315] = 0;
   out_8669821383571928839[316] = 0;
   out_8669821383571928839[317] = 0;
   out_8669821383571928839[318] = 0;
   out_8669821383571928839[319] = 0;
   out_8669821383571928839[320] = 0;
   out_8669821383571928839[321] = 0;
   out_8669821383571928839[322] = 0;
   out_8669821383571928839[323] = 1;
}
void h_4(double *state, double *unused, double *out_5054205481177388779) {
   out_5054205481177388779[0] = state[6] + state[9];
   out_5054205481177388779[1] = state[7] + state[10];
   out_5054205481177388779[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_8540023926579184446) {
   out_8540023926579184446[0] = 0;
   out_8540023926579184446[1] = 0;
   out_8540023926579184446[2] = 0;
   out_8540023926579184446[3] = 0;
   out_8540023926579184446[4] = 0;
   out_8540023926579184446[5] = 0;
   out_8540023926579184446[6] = 1;
   out_8540023926579184446[7] = 0;
   out_8540023926579184446[8] = 0;
   out_8540023926579184446[9] = 1;
   out_8540023926579184446[10] = 0;
   out_8540023926579184446[11] = 0;
   out_8540023926579184446[12] = 0;
   out_8540023926579184446[13] = 0;
   out_8540023926579184446[14] = 0;
   out_8540023926579184446[15] = 0;
   out_8540023926579184446[16] = 0;
   out_8540023926579184446[17] = 0;
   out_8540023926579184446[18] = 0;
   out_8540023926579184446[19] = 0;
   out_8540023926579184446[20] = 0;
   out_8540023926579184446[21] = 0;
   out_8540023926579184446[22] = 0;
   out_8540023926579184446[23] = 0;
   out_8540023926579184446[24] = 0;
   out_8540023926579184446[25] = 1;
   out_8540023926579184446[26] = 0;
   out_8540023926579184446[27] = 0;
   out_8540023926579184446[28] = 1;
   out_8540023926579184446[29] = 0;
   out_8540023926579184446[30] = 0;
   out_8540023926579184446[31] = 0;
   out_8540023926579184446[32] = 0;
   out_8540023926579184446[33] = 0;
   out_8540023926579184446[34] = 0;
   out_8540023926579184446[35] = 0;
   out_8540023926579184446[36] = 0;
   out_8540023926579184446[37] = 0;
   out_8540023926579184446[38] = 0;
   out_8540023926579184446[39] = 0;
   out_8540023926579184446[40] = 0;
   out_8540023926579184446[41] = 0;
   out_8540023926579184446[42] = 0;
   out_8540023926579184446[43] = 0;
   out_8540023926579184446[44] = 1;
   out_8540023926579184446[45] = 0;
   out_8540023926579184446[46] = 0;
   out_8540023926579184446[47] = 1;
   out_8540023926579184446[48] = 0;
   out_8540023926579184446[49] = 0;
   out_8540023926579184446[50] = 0;
   out_8540023926579184446[51] = 0;
   out_8540023926579184446[52] = 0;
   out_8540023926579184446[53] = 0;
}
void h_10(double *state, double *unused, double *out_5695429124193662539) {
   out_5695429124193662539[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5695429124193662539[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5695429124193662539[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2647901277076076620) {
   out_2647901277076076620[0] = 0;
   out_2647901277076076620[1] = 9.8100000000000005*cos(state[1]);
   out_2647901277076076620[2] = 0;
   out_2647901277076076620[3] = 0;
   out_2647901277076076620[4] = -state[8];
   out_2647901277076076620[5] = state[7];
   out_2647901277076076620[6] = 0;
   out_2647901277076076620[7] = state[5];
   out_2647901277076076620[8] = -state[4];
   out_2647901277076076620[9] = 0;
   out_2647901277076076620[10] = 0;
   out_2647901277076076620[11] = 0;
   out_2647901277076076620[12] = 1;
   out_2647901277076076620[13] = 0;
   out_2647901277076076620[14] = 0;
   out_2647901277076076620[15] = 1;
   out_2647901277076076620[16] = 0;
   out_2647901277076076620[17] = 0;
   out_2647901277076076620[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2647901277076076620[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2647901277076076620[20] = 0;
   out_2647901277076076620[21] = state[8];
   out_2647901277076076620[22] = 0;
   out_2647901277076076620[23] = -state[6];
   out_2647901277076076620[24] = -state[5];
   out_2647901277076076620[25] = 0;
   out_2647901277076076620[26] = state[3];
   out_2647901277076076620[27] = 0;
   out_2647901277076076620[28] = 0;
   out_2647901277076076620[29] = 0;
   out_2647901277076076620[30] = 0;
   out_2647901277076076620[31] = 1;
   out_2647901277076076620[32] = 0;
   out_2647901277076076620[33] = 0;
   out_2647901277076076620[34] = 1;
   out_2647901277076076620[35] = 0;
   out_2647901277076076620[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2647901277076076620[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2647901277076076620[38] = 0;
   out_2647901277076076620[39] = -state[7];
   out_2647901277076076620[40] = state[6];
   out_2647901277076076620[41] = 0;
   out_2647901277076076620[42] = state[4];
   out_2647901277076076620[43] = -state[3];
   out_2647901277076076620[44] = 0;
   out_2647901277076076620[45] = 0;
   out_2647901277076076620[46] = 0;
   out_2647901277076076620[47] = 0;
   out_2647901277076076620[48] = 0;
   out_2647901277076076620[49] = 0;
   out_2647901277076076620[50] = 1;
   out_2647901277076076620[51] = 0;
   out_2647901277076076620[52] = 0;
   out_2647901277076076620[53] = 1;
}
void h_13(double *state, double *unused, double *out_4567101886999322894) {
   out_4567101886999322894[0] = state[3];
   out_4567101886999322894[1] = state[4];
   out_4567101886999322894[2] = state[5];
}
void H_13(double *state, double *unused, double *out_6694446321798034369) {
   out_6694446321798034369[0] = 0;
   out_6694446321798034369[1] = 0;
   out_6694446321798034369[2] = 0;
   out_6694446321798034369[3] = 1;
   out_6694446321798034369[4] = 0;
   out_6694446321798034369[5] = 0;
   out_6694446321798034369[6] = 0;
   out_6694446321798034369[7] = 0;
   out_6694446321798034369[8] = 0;
   out_6694446321798034369[9] = 0;
   out_6694446321798034369[10] = 0;
   out_6694446321798034369[11] = 0;
   out_6694446321798034369[12] = 0;
   out_6694446321798034369[13] = 0;
   out_6694446321798034369[14] = 0;
   out_6694446321798034369[15] = 0;
   out_6694446321798034369[16] = 0;
   out_6694446321798034369[17] = 0;
   out_6694446321798034369[18] = 0;
   out_6694446321798034369[19] = 0;
   out_6694446321798034369[20] = 0;
   out_6694446321798034369[21] = 0;
   out_6694446321798034369[22] = 1;
   out_6694446321798034369[23] = 0;
   out_6694446321798034369[24] = 0;
   out_6694446321798034369[25] = 0;
   out_6694446321798034369[26] = 0;
   out_6694446321798034369[27] = 0;
   out_6694446321798034369[28] = 0;
   out_6694446321798034369[29] = 0;
   out_6694446321798034369[30] = 0;
   out_6694446321798034369[31] = 0;
   out_6694446321798034369[32] = 0;
   out_6694446321798034369[33] = 0;
   out_6694446321798034369[34] = 0;
   out_6694446321798034369[35] = 0;
   out_6694446321798034369[36] = 0;
   out_6694446321798034369[37] = 0;
   out_6694446321798034369[38] = 0;
   out_6694446321798034369[39] = 0;
   out_6694446321798034369[40] = 0;
   out_6694446321798034369[41] = 1;
   out_6694446321798034369[42] = 0;
   out_6694446321798034369[43] = 0;
   out_6694446321798034369[44] = 0;
   out_6694446321798034369[45] = 0;
   out_6694446321798034369[46] = 0;
   out_6694446321798034369[47] = 0;
   out_6694446321798034369[48] = 0;
   out_6694446321798034369[49] = 0;
   out_6694446321798034369[50] = 0;
   out_6694446321798034369[51] = 0;
   out_6694446321798034369[52] = 0;
   out_6694446321798034369[53] = 0;
}
void h_14(double *state, double *unused, double *out_8069458685978663356) {
   out_8069458685978663356[0] = state[6];
   out_8069458685978663356[1] = state[7];
   out_8069458685978663356[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5943479290790882641) {
   out_5943479290790882641[0] = 0;
   out_5943479290790882641[1] = 0;
   out_5943479290790882641[2] = 0;
   out_5943479290790882641[3] = 0;
   out_5943479290790882641[4] = 0;
   out_5943479290790882641[5] = 0;
   out_5943479290790882641[6] = 1;
   out_5943479290790882641[7] = 0;
   out_5943479290790882641[8] = 0;
   out_5943479290790882641[9] = 0;
   out_5943479290790882641[10] = 0;
   out_5943479290790882641[11] = 0;
   out_5943479290790882641[12] = 0;
   out_5943479290790882641[13] = 0;
   out_5943479290790882641[14] = 0;
   out_5943479290790882641[15] = 0;
   out_5943479290790882641[16] = 0;
   out_5943479290790882641[17] = 0;
   out_5943479290790882641[18] = 0;
   out_5943479290790882641[19] = 0;
   out_5943479290790882641[20] = 0;
   out_5943479290790882641[21] = 0;
   out_5943479290790882641[22] = 0;
   out_5943479290790882641[23] = 0;
   out_5943479290790882641[24] = 0;
   out_5943479290790882641[25] = 1;
   out_5943479290790882641[26] = 0;
   out_5943479290790882641[27] = 0;
   out_5943479290790882641[28] = 0;
   out_5943479290790882641[29] = 0;
   out_5943479290790882641[30] = 0;
   out_5943479290790882641[31] = 0;
   out_5943479290790882641[32] = 0;
   out_5943479290790882641[33] = 0;
   out_5943479290790882641[34] = 0;
   out_5943479290790882641[35] = 0;
   out_5943479290790882641[36] = 0;
   out_5943479290790882641[37] = 0;
   out_5943479290790882641[38] = 0;
   out_5943479290790882641[39] = 0;
   out_5943479290790882641[40] = 0;
   out_5943479290790882641[41] = 0;
   out_5943479290790882641[42] = 0;
   out_5943479290790882641[43] = 0;
   out_5943479290790882641[44] = 1;
   out_5943479290790882641[45] = 0;
   out_5943479290790882641[46] = 0;
   out_5943479290790882641[47] = 0;
   out_5943479290790882641[48] = 0;
   out_5943479290790882641[49] = 0;
   out_5943479290790882641[50] = 0;
   out_5943479290790882641[51] = 0;
   out_5943479290790882641[52] = 0;
   out_5943479290790882641[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7473524147338108814) {
  err_fun(nom_x, delta_x, out_7473524147338108814);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1225327672199224143) {
  inv_err_fun(nom_x, true_x, out_1225327672199224143);
}
void pose_H_mod_fun(double *state, double *out_962358481072545828) {
  H_mod_fun(state, out_962358481072545828);
}
void pose_f_fun(double *state, double dt, double *out_8886629790052716118) {
  f_fun(state,  dt, out_8886629790052716118);
}
void pose_F_fun(double *state, double dt, double *out_8669821383571928839) {
  F_fun(state,  dt, out_8669821383571928839);
}
void pose_h_4(double *state, double *unused, double *out_5054205481177388779) {
  h_4(state, unused, out_5054205481177388779);
}
void pose_H_4(double *state, double *unused, double *out_8540023926579184446) {
  H_4(state, unused, out_8540023926579184446);
}
void pose_h_10(double *state, double *unused, double *out_5695429124193662539) {
  h_10(state, unused, out_5695429124193662539);
}
void pose_H_10(double *state, double *unused, double *out_2647901277076076620) {
  H_10(state, unused, out_2647901277076076620);
}
void pose_h_13(double *state, double *unused, double *out_4567101886999322894) {
  h_13(state, unused, out_4567101886999322894);
}
void pose_H_13(double *state, double *unused, double *out_6694446321798034369) {
  H_13(state, unused, out_6694446321798034369);
}
void pose_h_14(double *state, double *unused, double *out_8069458685978663356) {
  h_14(state, unused, out_8069458685978663356);
}
void pose_H_14(double *state, double *unused, double *out_5943479290790882641) {
  H_14(state, unused, out_5943479290790882641);
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
