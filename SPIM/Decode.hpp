#ifndef SJTU_SPIM_DECODE_CLASS_HPP
#define SJTU_SPIM_DECODE_CLASS_HPP

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

void Decode(instruction &X, int &now){
	int lab, *sw, pw, len;
	char S;
	short ph, *sh;
	unsigned long long uv, uw, uans;
	switch(X.op){
		case add_TS: 
			TS[X.A] = TS[X.B] + TS[X.C];
			break;
		case add_i: 
			TS[X.A] = TS[X.B] + X.C;
			break;
		case and_TS:
			TS[X.A] = (TS[X.B] & TS[X.C]);
			break;
		case and_i: 
			TS[X.A] = (TS[X.B] & X.C);
			break;
		case div_TS: 
			TS[X.A] = TS[X.B] / TS[X.C];
			break;
		case div_i: 
			TS[X.A] = TS[X.B] / X.C;
			break;
		case div_two: 
			TS[33] = TS[X.A] / TS[X.B];
			TS[32] = TS[X.A] % TS[X.B];
			break;
		case mul_TS: 
			TS[X.A] = TS[X.B] * TS[X.C];
			break;
		case mul_i: 
			TS[X.A] = TS[X.B] * X.C;
			break;
		case neg_TS: 
			TS[X.A] = -TS[X.B];
			break;
		case rem_TS: 
			TS[X.A] = TS[X.B] % TS[X.C];
			break;
		case rem_i: 
			TS[X.A] = TS[X.B] % X.C;
			break;
		case sub_TS: 
			TS[X.A] = TS[X.B] - TS[X.C];
			break;
		case sub_i: 
			TS[X.A] = TS[X.B] - X.C;
			break;
		case xor_TS: 
			TS[X.A] = (TS[X.B] ^ TS[X.C]);
			break;
		case xor_i: 
			TS[X.A] = (TS[X.B] ^ X.C);
			break;
		case li: 
			TS[X.A] = X.B;
			break;		
		case seq_TS: 
			TS[X.A] = (TS[X.B] == TS[X.C]) ? 1 : 0;
			break;
		case seq_i: 
			TS[X.A] = (TS[X.B] == X.C) ? 1 : 0;
			break;
		case sge_TS: 
			TS[X.A] = (TS[X.B] >= TS[X.C]) ? 1 : 0;
			break;
		case sge_i: 
			TS[X.A] = (TS[X.B] >= X.C) ? 1 : 0;
			break;
		case sgt_TS: 
			TS[X.A] = (TS[X.B] > TS[X.C]) ? 1 : 0;
			break;
		case sgt_i: 
			TS[X.A] = (TS[X.B] > X.C) ? 1 : 0;
			break;
		case sle_TS: 
			TS[X.A] = (TS[X.B] <= TS[X.C]) ? 1 : 0;
			break;
		case sle_i: 
			TS[X.A] = (TS[X.B] <= X.C) ? 1 : 0;
			break;
		case slt_TS: 
			TS[X.A] = (TS[X.B] < TS[X.C]) ? 1 : 0;
			break;
		case slt_i: 
			TS[X.A] = (TS[X.B] < X.C) ? 1 : 0;
			break;
		case sne_TS: 
			TS[X.A] = (TS[X.B] != TS[X.C]) ? 1 : 0;
			break;
		case sne_i: 
			TS[X.A] = (TS[X.B] != X.C) ? 1 : 0;
			break;	
		case b: 
			now = X.C;
			break;
		case beq_TS: 
			if(TS[X.A] == TS[X.B]) now = X.C;
			break; 
		case beq_i: 
			if(TS[X.A] == X.B) now = X.C;
			break; 
		case bge_TS: 
			if(TS[X.A] >= TS[X.B]) now = X.C;
			break; 
		case bge_i: 
			if(TS[X.A] >= X.B) now = X.C;
			break;
		case bgt_TS: 
			if(TS[X.A] > TS[X.B]) now = X.C;
			break; 
		case bgt_i: 
			if(TS[X.A] > X.B) now = X.C;
			break;
		case ble_TS: 
			if(TS[X.A] <= TS[X.B]) now = X.C;
			break; 
		case ble_i: 
			if(TS[X.A] <= X.B) now = X.C;
			break;
		case blt_TS: 
			if(TS[X.A] < TS[X.B]) now = X.C;
			break; 
		case blt_i: 
			if(TS[X.A] < X.B) now = X.C;
			break;
		case bne_TS: 
			if(TS[X.A] != TS[X.B]) now = X.C;
			break; 
		case bne_i: 
			if(TS[X.A] != X.B) now = X.C;
			break;
		case j: 
			now = X.C;
			break;
		case jal: 
			TS[31] = now;
			now = X.C;
			break;
		case jalr: 
			TS[31] = now;
			now = TS[X.A];
			break;
		case jr: 
			now = TS[X.A];
			break;
		case move_TS: 
			TS[X.A] = TS[X.B];
			break;
		case mfhi: 
			TS[X.A] = TS[32];
			break;
		case mflo: 
			TS[X.A] = TS[33];
			break;
		case syscall: 
			switch(TS[2]){
				case 1: // print word
					printf("%d", TS[4]);
					break;
				case 5: // read word
					scanf("%d", &pw);
					TS[2] = pw;
					break;
				case 9: // heap memory
					TS[2] = nowheap;
					nowheap += TS[4];
					break;
				case 10: // end
					TS[35] = 1;
					break;
				case 17: // end with return num
					retu = TS[4];
					TS[35] = 1;
					break;
				case 4: // print string
					for(int j = TS[4]; ; j++){
						if(data[j] == '\0') break;
						putchar(data[j]);
					}
					break;
				case 8: // read string
					scanf("%s", Read_string);
					len = strlen(Read_string);
					pw = TS[4];
					for(int j = 0; j < len; j++) 
						data[pw++] = Read_string[j];
					data[pw] = '\0';
					break;
			}
			break;
			
		case la: 
			TS[X.A] = X.B;
			break; 
		case lb_dx: 
			lab = TS[X.B] + X.C;
			S = data[lab];
			TS[X.A] = S;
			break; 
		case lb_label: 
			S = data[X.B];
			TS[X.A] = S;
			break; 
		case lh_dx: 
			lab = TS[X.B] + X.C;
			sh = reinterpret_cast<short*>(data + lab);
			ph = *sh;
			TS[X.A] = ph; 
			break; 
		case lh_label: 
			sh = reinterpret_cast<short*>(data + X.B);
			ph = *sh;
			TS[X.A] = ph;
			break; 
		case lw_dx: 
			lab = TS[X.B] + X.C;
			sw = reinterpret_cast<int*>(data + lab);
			pw = *sw;
			TS[X.A] = pw;
			break; 
		case lw_label: 
			sw = reinterpret_cast<int*>(data + X.B);
			pw = *sw;
			TS[X.A] = pw;
			break; 
		case sb_dx: 
			lab = TS[X.B] + X.C;
			S = TS[X.A];
			data[lab] = S;
			break;
		case sb_label: 
			S = TS[X.A];
			data[X.B] = S;
			break;
		case sw_dx: 
			lab = TS[X.B] + X.C;
			sw = reinterpret_cast<int*>(data + lab);
			*sw = TS[X.A];
			break;
		case sw_label: 
			sw = reinterpret_cast<int*>(data + X.B);
			*sw = TS[X.A];
			break;
		case subu_TS: 
			uv = TS[X.B]; uw = TS[X.C];
			TS[X.A] = uv - uw;
			break;
		case subu_i: 
			uv = TS[X.B]; uw = X.C;
			TS[X.A] = uv - uw;
			break;
		case addu_TS: 
			uv = TS[X.B]; uw = TS[X.C];
			TS[X.A] = uv + uw;
			break;
		case addu_i: 
			uv = TS[X.B]; uw = X.C;
			TS[X.A] = uv + uw;
			break;
		case divu_TS: 
			uv = TS[X.B]; uw = TS[X.C];
			TS[X.A] = uv / uw;
			break;
		case divu_i: 
			uv = TS[X.B]; uw = X.C;
			TS[X.A] = uv / uw;
			break;
		case abs_TS:
			TS[X.A] = abs(TS[X.B]);
			break;
		case divu_two: 
			uv = TS[X.A]; uw = TS[X.B];
			TS[33] = uv / uw;
			TS[32] = uv % uw;
			break;
		case mult: 
			uans = (long long)(TS[X.A]) * TS[X.B];
			TS[32] = (uans >> 32);
			TS[33] = (uans - ((uans >> 32) << 32));
			break;
		case multu:
			uv = TS[X.A]; uw = TS[X.B];
			uans = uv * uw;
			TS[32] = (uans >> 32);
			TS[33] = (uans - ((uans >> 32) << 32));
			break;
		case nor_TS:
			TS[X.A] = (~(TS[X.B] | TS[X.C]));
			break;
		case nor_i:
			TS[X.A] = (~(TS[X.B] | X.C));
			break;
		case not_TS:
			TS[X.A] = (~TS[X.B]);
			break;
		case or_TS: 
			TS[X.A] = (TS[X.B] | TS[X.C]);
			break;
		case or_i: 
			TS[X.A] = (TS[X.B] | X.C);
			break;
		case remu_TS: 
			uv = TS[X.B]; uw = TS[X.C];
			TS[X.A] = uv % uw;
			break;
		case remu_i: 
			uv = TS[X.B]; uw = X.C;
			TS[X.A] = uv % uw;
			break;
		case rol_TS:
			uv = TS[X.B];
			TS[X.A] = (uv << TS[X.C]) + (uv >> (32 - TS[X.C]));
			break;
		case rol_i:
			uv = TS[X.B];
			TS[X.A] = (uv << X.C) + (uv >> (32 - X.C));
			break;
		case ror_TS:
			uv = TS[X.B];
			TS[X.A] = (uv >> TS[X.C]) + (uv << (32 - TS[X.C]));
			break;
		case ror_i:
			uv = TS[X.B];
			TS[X.A] = (uv >> X.C) + (uv << (32 - X.C));
			break;
		case sll_TS:
			uv = TS[X.B];
			TS[X.A] = (uv << TS[X.C]);
			break;
		case sll_i:
			uv = TS[X.B];
			TS[X.A] = (uv << X.C);
			break;	
		case sra_TS:
			TS[X.A] = (TS[X.B] >> TS[X.C]);
			break;
		case sra_i:
			TS[X.A] = (TS[X.B] >> X.C);
			break;
		case srl_TS:
			uv = TS[X.B];
			TS[X.A] = (uv >> TS[X.C]);
			break;
		case srl_i:
			uv = TS[X.B];
			TS[X.A] = (uv >> X.C);
			break;
		case sgeu_TS: 
			uv = TS[X.B]; uw = TS[X.C];
			TS[X.A] = (uv >= uw) ? 1 : 0;
			break;
		case sgeu_i: 
			uv = TS[X.B]; uw = X.C;
			TS[X.A] = (uv >= uw) ? 1 : 0;
			break;
		case sgtu_TS: 
			uv = TS[X.B]; uw = TS[X.C];
			TS[X.A] = (uv > uw) ? 1 : 0;
			break;
		case sgtu_i: 
			uv = TS[X.B]; uw = X.C;
			TS[X.A] = (uv > uw) ? 1 : 0;
			break;
		case sleu_TS: 
			uv = TS[X.B]; uw = TS[X.C];
			TS[X.A] = (uv <= uw) ? 1 : 0;
			break;
		case sleu_i: 
			uv = TS[X.B]; uw = X.C;
			TS[X.A] = (uv <= uw) ? 1 : 0;
			break;
		case sltu_TS: 
			uv = TS[X.B]; uw = TS[X.C];
			TS[X.A] = (uv < uw) ? 1 : 0;
			break;
		case sltu_i: 
			uv = TS[X.B]; uw = X.C;
			TS[X.A] = (uv < uw) ? 1 : 0;
			break;
		case bgezal: 
			TS[31] = now;
			if(TS[X.A] >= 0) now = X.C;
			break; 
		case bgtzal: 
			TS[31] = now;
			if(TS[X.A] > 0) now = X.C;
			break; 
		case blezal: 
			TS[31] = now;
			if(TS[X.A] <= 0) now = X.C;
			break; 
		case bltzal: 
			TS[31] = now;
			if(TS[X.A] < 0) now = X.C;
			break; 
		case bgeu_TS: 
			uv = TS[X.A]; uw = TS[X.B];
			if(uv >= uw) now = X.C;
			break; 
		case bgeu_i: 
			uv = TS[X.A]; uw = X.B;
			if(uv >= uw) now = X.C;
			break;
		case bgtu_TS: 
			uv = TS[X.A]; uw = TS[X.B];
			if(uv > uw) now = X.C;
			break; 
		case bgtu_i: 
			uv = TS[X.A]; uw = X.B;
			if(uv > uw) now = X.C;
			break;
		case bleu_TS: 
			uv = TS[X.A]; uw = TS[X.B];
			if(uv <= uw) now = X.C;
			break; 
		case bleu_i: 
			uv = TS[X.A]; uw = X.B;
			if(uv <= uw) now = X.C;
			break;
		case bltu_TS: 
			uv = TS[X.A]; uw = TS[X.B];
			if(uv < uw) now = X.C;
			break; 
		case bltu_i: 
			uv = TS[X.A]; uw = X.B;
			if(uv < uw) now = X.C;
			break;
		case sh_dx: 
			lab = TS[X.B] + X.C;
			sh = reinterpret_cast<short*>(data + lab);
			*sh = (short)(TS[X.A]);
			break;
		case sh_label: 
			sh = reinterpret_cast<short*>(data + X.B);
			*sh = (short)(TS[X.A]);
			break;
	}
}

#endif
