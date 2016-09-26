#ifndef SJTU_SPIM_DECODE_FLOW_CLASS_HPP
#define SJTU_SPIM_DECODE_FLOW_CLASS_HPP

#include <iostream>
#include <map>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#include "Class.hpp"

using namespace std;

bool Solve_step_Decode(flow &X, bool &Canread, int &now){
	int lab, *sw, pw, len;
	char pb;
	short ph, *sh;
	long long sl, pl;
	unsigned long long uv, uw, uans;
	switch(X.op){
		case abs_TS:
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = abs(TS[X.B]);
			break;
		case add_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] + TS[X.C];
			break;
		case add_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] + X.C;
			break;
		case and_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (TS[X.B] & TS[X.C]);
			break;
		case and_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (TS[X.B] & X.C);
			break;
		case div_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] / TS[X.C];
			break;
		case div_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] / X.C;
			break;
		case div_two: 
			if(lock[X.A] || lock[X.B]) return 0;
			++lock[32]; ++lock[33];
			X.to_ts[X.top] = 33; X.to_data[X.top++] = TS[X.A] / TS[X.B];
			X.to_ts[X.top] = 32; X.to_data[X.top++] = TS[X.A] % TS[X.B];
			break;
		case mul_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] * TS[X.C];
			break;
		case mul_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] * X.C;
			break;
		case neg_TS: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = -TS[X.B];
			break;
		case rem_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] % TS[X.C];
			break;
		case rem_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] % X.C;
			break;
		case sub_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] - TS[X.C];
			break;
		case sub_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B] - X.C;
			break;
		case xor_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (TS[X.B] ^ TS[X.C]);
			break;
		case xor_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (TS[X.B] ^ X.C);
			break;
		case li: 
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = X.B;
			break;
		case seq_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			lab = (TS[X.B] == TS[X.C]) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case seq_i: 
			if(lock[X.B]) return 0;
			lab = (TS[X.B] == X.C) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case sge_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			lab = (TS[X.B] >= TS[X.C]) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case sge_i: 
			if(lock[X.B]) return 0;
			lab = (TS[X.B] >= X.C) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case sgt_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			lab = (TS[X.B] > TS[X.C]) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case sgt_i: 
			if(lock[X.B]) return 0;
			lab = (TS[X.B] > X.C) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case sle_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			lab = (TS[X.B] <= TS[X.C]) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case sle_i: 
			if(lock[X.B]) return 0;
			lab = (TS[X.B] <= X.C) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case slt_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			lab = (TS[X.B] < TS[X.C]) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case slt_i: 
			if(lock[X.B]) return 0;
			lab = (TS[X.B] < X.C) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case sne_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			lab = (TS[X.B] != TS[X.C]) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case sne_i: 
			if(lock[X.B]) return 0;
			lab = (TS[X.B] != X.C) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case b: 
			Canread = 0; X.isjump = 1;
			now = X.C;
			break;
		case beq_TS: 
			if(lock[X.A] || lock[X.B]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] == TS[X.B]) now = X.C;
			break; 
		case beq_i: 
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] == X.B) now = X.C;
			break; 
		case bge_TS: 
			if(lock[X.A] || lock[X.B]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] >= TS[X.B]) now = X.C;
			break; 
		case bge_i: 
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] >= X.B) now = X.C;
			break;
		case bgt_TS: 
			if(lock[X.A] || lock[X.B]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] > TS[X.B]) now = X.C;
			break; 
		case bgt_i: 
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] > X.B) now = X.C;
			break;
		case ble_TS: 
			if(lock[X.A] || lock[X.B]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] <= TS[X.B]) now = X.C;
			break; 
		case ble_i: 
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] <= X.B) now = X.C;
			break;
		case blt_TS: 
			if(lock[X.A] || lock[X.B]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] < TS[X.B]) now = X.C;
			break; 
		case blt_i: 
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] < X.B) now = X.C;
			break;
		case bne_TS: 
			if(lock[X.A] || lock[X.B]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] != TS[X.B]) now = X.C;
			break; 
		case bne_i: 
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			if(TS[X.A] != X.B) now = X.C;
			break;
		case j: 
			Canread = 0; X.isjump = 1;
			now = X.C;
			break;
		case jal:
			Canread = 0; X.isjump = 1;
			++lock[31];
			X.to_ts[X.top] = 31; X.to_data[X.top++] = now;
			now = X.C;
			break;
		case jalr: 
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			++lock[31];
			X.to_ts[X.top] = 31; X.to_data[X.top++] = now;
			now = TS[X.A];
			break;
		case jr: 
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			now = TS[X.A];
			break;
		case move_TS: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[X.B];
			break;
		case mfhi: 
			if(lock[32]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[32];
			break;
		case mflo:
			if(lock[33]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = TS[33];
			break;
		case syscall: 
			if(lock[2] || lock[4] || lock[5]) return 0;
			switch(TS[2]){
				case 1: // print word
					printf("%d", TS[4]);
					break;
				case 5: // read word
					scanf("%d", &pw);
					lock[2]++;
					X.to_ts[X.top] = 2; X.to_data[X.top++] = pw;
					break;
				case 9: // heap memory
					lock[2]++;
					X.to_ts[X.top] = 2; X.to_data[X.top++] = nowheap;
					nowheap += TS[4];
					break;
				case 10: // end
					lock[35]++;
					X.to_ts[X.top] = 35; X.to_data[X.top++] = 1;
					break;
				case 17: // end with return num
					retu = TS[4];
					lock[35]++;
					X.to_ts[X.top] = 35; X.to_data[X.top++] = 1;
					break;
			}
			Canread = 0; X.isjump = 1;
			break;
			
		case la:
			++lock[X.A]; 
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = X.B;
			break; 
		case lb_dx:
			if(lock[X.B]) return 0;
			++lock[X.A]; break; 
		case lb_label: 
			++lock[X.A]; break; 
		case lh_dx:
			if(lock[X.B]) return 0;
			++lock[X.A]; break; 
		case lh_label: 
			++lock[X.A]; break; 
		case lw_dx: 
			if(lock[X.B]) return 0;
			++lock[X.A]; break; 
		case lw_label: 
			++lock[X.A]; break; 
		case sb_dx: 
			if(lock[X.A] || lock[X.B]) return 0;
			break;
		case sb_label: 
			if(lock[X.A]) return 0;
			break;
		case sw_dx: 
			if(lock[X.A] || lock[X.B]) return 0;
			break;
		case sw_label: 
			if(lock[X.A]) return 0;
			break;
		case sh_dx: 
			if(lock[X.A] || lock[X.B]) return 0;
			break;
		case sh_label: 
			if(lock[X.A]) return 0;
			break;
		case subu_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			uv = TS[X.B]; uw = TS[X.C];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = uv - uw;
			break;
		case subu_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			uv = TS[X.B]; uw = X.C;
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = uv - uw;
			break;
		case addu_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			uv = TS[X.B]; uw = TS[X.C];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = uv + uw;
			break;
		case addu_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			uv = TS[X.B]; uw = X.C;
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = uv + uw;
			break;
		case divu_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			uv = TS[X.B]; uw = TS[X.C];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = uv / uw;
			break;
		case divu_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			uv = TS[X.B]; uw = X.C;
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = uv / uw;
			break;
		case divu_two: 
			if(lock[X.A] || lock[X.B]) return 0;
			++lock[32]; ++lock[33];
			uv = TS[X.A]; uw = TS[X.B];
			X.to_ts[X.top] = 33; X.to_data[X.top++] = uv / uw;
			X.to_ts[X.top] = 32; X.to_data[X.top++] = uv % uw;
			break;
		case mult: 
			if(lock[X.A] || lock[X.B]) return 0;
			++lock[32]; ++lock[33];
			uans = (long long)(TS[X.A]) * TS[X.B];
			X.to_ts[X.top] = 32; X.to_data[X.top++] = (uans >> 32);
			X.to_ts[X.top] = 33; X.to_data[X.top++] = (uans - ((uans >> 32) << 32));
			break;
		case multu: 
			if(lock[X.A] || lock[X.B]) return 0;
			++lock[32]; ++lock[33];
			uv = TS[X.A]; uw = TS[X.B];
			uans = uv * uw;
			X.to_ts[X.top] = 32; X.to_data[X.top++] = (uans >> 32);
			X.to_ts[X.top] = 33; X.to_data[X.top++] = (uans - ((uans >> 32) << 32));
			break;
		case nor_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (~(TS[X.B] | TS[X.C]));
			break;
		case nor_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (~(TS[X.B] | X.C));
			break;
		case not_TS: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (~TS[X.B]);
			break;
		case or_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (TS[X.B] | TS[X.C]);
			break;
		case or_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (TS[X.B] | X.C);
			break;
		case remu_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			uv = TS[X.B]; uw = TS[X.C];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = uv % uw;
			break;
		case remu_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			uv = TS[X.B]; uw = X.C;
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = uv % uw;
			break;
		case rol_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			uv = TS[X.B];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (uv << TS[X.C]) + (uv >> (32 - TS[X.C]));
			break;
		case rol_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			uv = TS[X.B];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (uv << X.C) + (uv >> (32 - X.C));
			break;
		case ror_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			uv = TS[X.B];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (uv >> TS[X.C]) + (uv << (32 - TS[X.C]));
			break;
		case ror_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			uv = TS[X.B];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (uv >> X.C) + (uv << (32 - X.C));
			break;
		case sll_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			uv = TS[X.B];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (uv << TS[X.C]);
			break;
		case sll_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			uv = TS[X.B];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (uv << X.C);
			break;
		case sra_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (TS[X.B] >> TS[X.C]);
			break;
		case sra_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (TS[X.B] >> X.C);
			break;
		case srl_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			++lock[X.A];
			uv = TS[X.B];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (uv >> TS[X.C]);
			break;
		case srl_i: 
			if(lock[X.B]) return 0;
			++lock[X.A];
			uv = TS[X.B];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = (uv >> X.C);
			break;
		case sgeu_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			uv = TS[X.B]; uw = TS[X.C];
			lab = (uv >= uw) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case sgeu_i: 
			if(lock[X.B]) return 0;
			uv = TS[X.B]; uw = X.C;
			lab = (uv >= uw) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case sgtu_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			uv = TS[X.B]; uw = TS[X.C];
			lab = (uv > uw) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case sgtu_i: 
			if(lock[X.B]) return 0;
			uv = TS[X.B]; uw = X.C;
			lab = (uv > uw) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case sleu_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			uv = TS[X.B]; uw = TS[X.C];
			lab = (uv <= uw) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case sleu_i: 
			if(lock[X.B]) return 0;
			uv = TS[X.B]; uw = X.C;
			lab = (uv <= uw) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case sltu_TS: 
			if(lock[X.B] || lock[X.C]) return 0;
			uv = TS[X.B]; uw = TS[X.C];
			lab = (uv < uw) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case sltu_i: 
			if(lock[X.B]) return 0;
			uv = TS[X.B]; uw = X.C;
			lab = (uv < uw) ? 1 : 0;
			++lock[X.A];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = lab;
			break;
		case bgezal: 
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			X.to_ts[X.top] = 31; X.to_data[X.top++] = now;
			if(TS[X.A] >= 0) now = X.C;
			break; 
		case bgtzal: 
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			X.to_ts[X.top] = 31; X.to_data[X.top++] = now;
			if(TS[X.A] > 0) now = X.C;
			break; 
		case blezal: 
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			X.to_ts[X.top] = 31; X.to_data[X.top++] = now;
			if(TS[X.A] <= 0) now = X.C;
			break; 
		case bltzal: 
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			X.to_ts[X.top] = 31; X.to_data[X.top++] = now;
			if(TS[X.A] < 0) now = X.C;
			break; 
		case bgeu_TS: 
			if(lock[X.A] || lock[X.B]) return 0;
			Canread = 0; X.isjump = 1;
			uv = TS[X.A]; uw = TS[X.B];
			if(uv >= uw) now = X.C;
			break; 
		case bgeu_i: 
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			uv = TS[X.A]; uw = X.B;
			if(uv >= uw) now = X.C;
			break;
		case bgtu_TS: 
			if(lock[X.A] || lock[X.B]) return 0;
			Canread = 0; X.isjump = 1;
			uv = TS[X.A]; uw = TS[X.B];
			if(uv > uw) now = X.C;
			break; 
		case bgtu_i: 
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			uv = TS[X.A]; uw = X.B;
			if(uv > uw) now = X.C;
			break;
		case bleu_TS: 
			if(lock[X.A] || lock[X.B]) return 0;
			Canread = 0; X.isjump = 1;
			uv = TS[X.A]; uw = TS[X.B];
			if(uv <= uw) now = X.C;
			break; 
		case bleu_i: 
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			uv = TS[X.A]; uw = X.B;
			if(uv <= uw) now = X.C;
			break;
		case bltu_TS: 
			if(lock[X.A] || lock[X.B]) return 0;
			Canread = 0; X.isjump = 1;
			uv = TS[X.A]; uw = TS[X.B];
			if(uv < uw) now = X.C;
			break; 
		case bltu_i: 
			if(lock[X.A]) return 0;
			Canread = 0; X.isjump = 1;
			uv = TS[X.A]; uw = X.B;
			if(uv < uw) now = X.C;
			break;
	}
	return 1;
}

int Solve_step_Memory(flow &X){
	int lab, *sw, pw, len;
	char S;
	short ph, *sh;
	switch(X.op){
		case lb_dx: 
			lab = TS[X.B] + X.C;
			S = data[lab];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = S;
			return 1; 
		case lb_label: 
			S = data[X.B];
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = S;
			return 1;
		case lh_dx: 
			lab = TS[X.B] + X.C;
			sh = reinterpret_cast<short*>(data + lab);
			ph = *sh;
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = ph;
			return 1;
		case lh_label: 
			sh = reinterpret_cast<short*>(data + X.B);
			ph = *sh;
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = ph;
			return 1;
		case lw_dx: 
			lab = TS[X.B] + X.C;
			sw = reinterpret_cast<int*>(data + lab);
			pw = *sw;
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = pw;
			return 1;
		case lw_label: 
			sw = reinterpret_cast<int*>(data + X.B);
			pw = *sw;
			X.to_ts[X.top] = X.A; X.to_data[X.top++] = pw;
			return 1;
		case sb_dx: 
			lab = TS[X.B] + X.C;
			S = TS[X.A];
			data[lab] = S;
			return 1;
		case sb_label: 
			S = TS[X.A];
			data[X.B] = S;
			return 1;
		case sw_dx: 
			lab = TS[X.B] + X.C;
			sw = reinterpret_cast<int*>(data + lab);
			*sw = TS[X.A];
			return 1;
		case sw_label: 
			sw = reinterpret_cast<int*>(data + X.B);
			*sw = TS[X.A];
			return 1;
		case sh_dx: 
			lab = TS[X.B] + X.C;
			sh = reinterpret_cast<short*>(data + lab);
			*sh = (short)(TS[X.A]);
			return 1;
		case sh_label: 
			sh = reinterpret_cast<short*>(data + X.B);
			*sh = (short)(TS[X.A]);
			return 1;
		case syscall: 
			switch(TS[2]){
				case 4: // print string
					for(int j = TS[4]; ; j++){
						if(data[j] == '\0') break;
						putchar(data[j]);
					}
					return 1;
				case 8: // read string
					scanf("%s", Read_string);
					len = strlen(Read_string);
					pw = TS[4];
					for(int j = 0; j < len; j++) 
						data[pw++] = Read_string[j];
					data[pw] = '\0';
					return 1;
				case 9: // heap memory
					return 1;
			}
	}
	return 0;
}

#endif
