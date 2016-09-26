#ifndef SJTU_SPIM_OPSAVE_HPP
#define SJTU_SPIM_OPSAVE_HPP

#include <iostream>
#include <map>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <unordered_map>

#include "Class.hpp"
#include "String_option.hpp"

using namespace std;

int readtype; // 0: .data, 1: .text

void op_data_save(string op){ // .xxxx
	int pos = 0, len = op.size();
	while(pos < len && (op[pos] == ' ' || op[pos] == '\t')) pos++;
	pos++;
	if(op[pos] == 'd') readtype = 0; else //.data
	if(op[pos] == 't') readtype = 1; else //.text
	if(op[pos] == 'b'){ //.byte
		pos += 4; 
		op += ',';
		string Next = Split_next(op, pos, ',');
		while(pos != -1){
			if(Next[0] == '\'') data[nowdata] = Next[1];
			else data[nowdata] = Atoi(Next);
			++nowdata;
			Next = Split_next(op, pos, ',');
		}
	} else 
	if(op[pos] == 'h'){ //.half
		pos += 4;
		op += ',';
		short Num = Atoi(Split_next(op, pos, ','));
		while(pos != -1){
			short *P = reinterpret_cast<short*>(data + nowdata);
			*P = Num;
			nowdata += 2;
			Num = Atoi(Split_next(op, pos, ','));
		}
	} else
	if(op[pos] == 's'){ //.space
		pos += 5;
		op += ' ';
		int n = Atoi(Split_next(op, pos, ' '));
		nowdata += n;
	} else
	if(op[pos] == 'w'){ //.word
		pos += 4;
		op += ',';
		int Num = Atoi(Split_next(op, pos, ','));
		while(pos != -1){
			int *P = reinterpret_cast<int*>(data + nowdata);
			*P = Num;
			nowdata += 4;
			Num = Atoi(Split_next(op, pos, ','));
		}
	} else
	if(op[pos] == 'a'){ 
		if(op[pos + 1] == 'l'){ //.align
			op += ' ';
			pos += 5;
			int n = Atoi(Split_next(op, pos, ' '));
			n = (1 << n);
			if(nowdata % n) 
				nowdata = (nowdata / n + 1) * n;
		} else
		if(op[pos + 5] == 'z'){ //.asciiz
			op += ' ';
			pos += 6;
			string Q = Split_string(op, pos);
			int len = Q.size();
			for(int j = 0; j < len; j++){
				if(Q[j] == '\\'){
					if(Q[j + 1] == '\\') data[nowdata++] = Q[j + 1]; 
					else if(Q[j + 1] == '\"') data[nowdata++] = Q[j + 1]; 
					else if(Q[j + 1] == 'n') data[nowdata++] = '\n';
					else if(Q[j + 1] == 't') data[nowdata++] = '\t';
					else if(Q[j + 1] == '0') data[nowdata++] = '\0';
					j++;
				}
				else data[nowdata++] = Q[j];
			}
			data[nowdata++] = '\0';
		} 
		else{ //.ascii
			op += ' ';
			pos += 5;
			string Q = Split_string(op, pos);
			int len = Q.size();
			for(int j = 0; j < len; j++){
				if(Q[j] == '\\'){
					if(Q[j + 1] == '\\') data[nowdata++] = Q[j + 1];
					else if(Q[j + 1] == '\"') data[nowdata++] = Q[j + 1];
					else if(Q[j + 1] == 'n') data[nowdata++] = '\n';
					else if(Q[j + 1] == 't') data[nowdata++] = '\t';
					else if(Q[j + 1] == '0') data[nowdata++] = '\0';
					j++;
				}
				else data[nowdata++] = Q[j];
			}
		}
	}	
}

void op_text_save(string op){ // Code
	int pos = 0, len = op.size(), top = 0;
	for(int i = 0; i < len; i++) if(op[i] == ',' || op[i] == '\t') op[i] = ' ';
	op += ' ';
	while(pos < len && (op[pos] == ' ' || op[pos] == '\t')) pos++;
	string option[6]; 
	while(pos != -1){
		option[top++] = Split_next(op, pos, ' ');
	}
	top--;
	code Q;
	string address, dx;
	if(option[0] == "add"){
		if(option[3][0] == '$') Q = code(add_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else Q = code(add_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	}
	else if(option[0] == "addi") Q = code(add_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	else if(option[0] == "and"){
		if(option[3][0] == '$') Q = code(and_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else  Q = code(and_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	}
	else if(option[0] == "andi") Q = code(and_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	else if(option[0] == "div"){
		if(top == 4){
			if(option[3][0] == '$')	Q = code(div_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
			else Q = code(div_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
		}	
		else Q = code(div_two, ts_to_num(option[1]), ts_to_num(option[2]));
	}
	else if(option[0] == "divu"){
		if(top == 4){
			if(option[3][0] == '$')	Q = code(divu_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
			else Q = code(divu_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
		}	
		else Q = code(divu_two, ts_to_num(option[1]), ts_to_num(option[2]));
	}
	else if(option[0] == "mul"){
		if(option[3][0] == '$') Q = code(mul_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else Q = code(mul_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	}
	
	else if(option[0] == "mult") Q = code(mult, ts_to_num(option[1]), ts_to_num(option[2])); 
	else if(option[0] == "multu") Q = code(multu, ts_to_num(option[1]), ts_to_num(option[2])); 
	else if(option[0] == "neg") Q = code(neg_TS, ts_to_num(option[1]), ts_to_num(option[2])); 
	else if(option[0] == "negu") Q = code(neg_TS, ts_to_num(option[1]), ts_to_num(option[2])); 
	else if(option[0] == "nor"){
		if(option[3][0] == '$') Q = code(nor_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else Q = code(nor_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	}
	else if(option[0] == "not") Q = code(not_TS, ts_to_num(option[1]), ts_to_num(option[2])); 
	else if(option[0] == "or"){
		if(option[3][0] == '$') Q = code(or_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else Q = code(or_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	}
	else if(option[0] == "ori") Q = code(or_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	else if(option[0] == "rem"){
		if(option[3][0] == '$') Q = code(rem_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(rem_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "remu"){
		if(option[3][0] == '$') Q = code(remu_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(remu_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "sub"){
		if(option[3][0] == '$') Q = code(sub_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else Q = code(sub_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	} 
	else if(option[0] == "xor"){
		if(option[3][0] == '$') Q = code(xor_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else  Q = code(xor_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	}
	else if(option[0] == "xori") Q = code(xor_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	else if(option[0] == "li") Q = code(li, ts_to_num(option[1]), Atoi(option[2])); 
	else if(option[0] == "seq"){
		if(option[3][0] == '$') Q = code(seq_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else  Q = code(seq_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	}
	else if(option[0] == "sge"){
		if(option[3][0] == '$') Q = code(sge_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(sge_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "sgeu"){
		if(option[3][0] == '$') Q = code(sgeu_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(sgeu_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "sgt"){
		if(option[3][0] == '$') Q = code(sgt_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(sgt_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "sgtu"){
		if(option[3][0] == '$') Q = code(sgtu_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(sgtu_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "sle"){
		if(option[3][0] == '$') Q = code(sle_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else Q = code(sle_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	} 
	else if(option[0] == "sleu"){
		if(option[3][0] == '$') Q = code(sleu_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3]));
		else Q = code(sleu_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	} 
	else if(option[0] == "slt"){
		if(option[3][0] == '$') Q = code(slt_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(slt_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "slti") Q = code(slt_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	else if(option[0] == "sltu"){
		if(option[3][0] == '$') Q = code(sltu_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(sltu_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "sltiu") Q = code(sltu_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	else if(option[0] == "sne"){
		if(option[3][0] == '$') Q = code(sne_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(sne_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "b") Q = code(b, 0, 0, 0, option[1]); 
	else if(option[0] == "beq"){
		if(option[2][0] == '$') Q = code(beq_TS, ts_to_num(option[1]), ts_to_num(option[2]), 0, option[3]); 
		else Q = code(beq_i, ts_to_num(option[1]), Atoi(option[2]), 0, option[3]); 
	}
	else if(option[0] == "beqz") Q = code(beq_i, ts_to_num(option[1]), 0, 0, option[2]); 
	else if(option[0] == "bge"){
		if(option[2][0] == '$') Q = code(bge_TS, ts_to_num(option[1]), ts_to_num(option[2]), 0, option[3]); 
		else Q = code(bge_i, ts_to_num(option[1]), Atoi(option[2]), 0, option[3]); 
	}
	else if(option[0] == "bgeu"){
		if(option[2][0] == '$') Q = code(bgeu_TS, ts_to_num(option[1]), ts_to_num(option[2]), 0, option[3]); 
		else Q = code(bgeu_i, ts_to_num(option[1]), Atoi(option[2]), 0, option[3]); 
	}
	else if(option[0] == "bgez") Q = code(bge_i, ts_to_num(option[1]), 0, 0, option[2]); 
	else if(option[0] == "bgezal") Q = code(bgezal, ts_to_num(option[1]), 0, 0, option[2]);
	else if(option[0] == "bgt"){
		if(option[2][0] == '$') Q = code(bgt_TS, ts_to_num(option[1]), ts_to_num(option[2]), 0, option[3]);
		else Q = code(bgt_i, ts_to_num(option[1]), Atoi(option[2]), 0, option[3]);
	}
	else if(option[0] == "bgtu"){
		if(option[2][0] == '$') Q = code(bgtu_TS, ts_to_num(option[1]), ts_to_num(option[2]), 0, option[3]);
		else Q = code(bgtu_i, ts_to_num(option[1]), Atoi(option[2]), 0, option[3]);
	}
	else if(option[0] == "bgtz") Q = code(bgt_i, ts_to_num(option[1]), 0, 0, option[2]);
	else if(option[0] == "bgtzal") Q = code(bgtzal, ts_to_num(option[1]), 0, 0, option[2]);
	else if(option[0] == "ble"){
		if(option[2][0] == '$') Q = code(ble_TS, ts_to_num(option[1]), ts_to_num(option[2]), 0, option[3]); 
		else Q = code(ble_i, ts_to_num(option[1]), Atoi(option[2]), 0, option[3]); 
	}
	else if(option[0] == "bleu"){
		if(option[2][0] == '$') Q = code(bleu_TS, ts_to_num(option[1]), ts_to_num(option[2]), 0, option[3]); 
		else Q = code(bleu_i, ts_to_num(option[1]), Atoi(option[2]), 0, option[3]); 
	}
	else if(option[0] == "blez") Q = code(ble_i, ts_to_num(option[1]), 0, 0, option[2]); 
	else if(option[0] == "blezal") Q = code(blezal, ts_to_num(option[1]), 0, 0, option[2]); 
	else if(option[0] == "bltzal") Q = code(bltzal, ts_to_num(option[1]), 0, 0, option[2]); 
	else if(option[0] == "blt"){
		if(option[2][0] == '$') Q = code(blt_TS, ts_to_num(option[1]), ts_to_num(option[2]), 0, option[3]); 
		else  Q = code(blt_i, ts_to_num(option[1]), Atoi(option[2]), 0, option[3]); 
	}
	else if(option[0] == "bltu"){
		if(option[2][0] == '$') Q = code(bltu_TS, ts_to_num(option[1]), ts_to_num(option[2]), 0, option[3]); 
		else  Q = code(bltu_i, ts_to_num(option[1]), Atoi(option[2]), 0, option[3]); 
	}
	else if(option[0] == "bltz") Q = code(blt_i, ts_to_num(option[1]), 0, 0, option[2]); 
	else if(option[0] == "bne"){
		if(option[2][0] == '$') Q = code(bne_TS, ts_to_num(option[1]), ts_to_num(option[2]), 0, option[3]); 
		else  Q = code(bne_i, ts_to_num(option[1]), Atoi(option[2]), 0, option[3]); 
	}
	else if(option[0] == "bnez") Q = code(bne_i, ts_to_num(option[1]), 0, 0, option[2]); 
	else if(option[0] == "j") Q = code(j, 0, 0, 0, option[1]); 
	else if(option[0] == "jal") Q = code(jal, 0, 0, 0, option[1]); 
	else if(option[0] == "jalr") Q = code(jalr, ts_to_num(option[1])); 
	else if(option[0] == "jr") Q = code(jr, ts_to_num(option[1]));
	else if(option[0] == "la") Q = code(la, ts_to_num(option[1]), 0, 0, option[2]); 
	else if(option[0] == "lb"){
		pos = 0; dx = Split_next(option[2], pos, '(');
		if(pos != -1){
			address = Split_next(option[2], pos, ')');
			Q = code(lb_dx, ts_to_num(option[1]), ts_to_num(address), Atoi(dx)); 
		}
		else Q = code(lb_label, ts_to_num(option[1]), 0, 0, option[2]);
	}
	else if(option[0] == "lh"){
		pos = 0; dx = Split_next(option[2], pos, '(');
		if(pos != -1){
			address = Split_next(option[2], pos, ')');
			Q = code(lh_dx, ts_to_num(option[1]), ts_to_num(address), Atoi(dx)); 
		}
		else Q = code(lh_label, ts_to_num(option[1]), 0, 0, option[2]);
	}
	else if(option[0] == "lw"){
		pos = 0; dx = Split_next(option[2], pos, '(');
		if(pos != -1){
			address = Split_next(option[2], pos, ')');
			Q = code(lw_dx, ts_to_num(option[1]), ts_to_num(address), Atoi(dx)); 
		}
		else Q = code(lw_label, ts_to_num(option[1]), 0, 0, option[2]);
	}
	else if(option[0] == "sb"){
		pos = 0; dx = Split_next(option[2], pos, '(');
		if(pos != -1){
			address = Split_next(option[2], pos, ')');
			Q = code(sb_dx, ts_to_num(option[1]), ts_to_num(address), Atoi(dx)); 
		}
		else Q = code(sb_label, ts_to_num(option[1]), 0, 0, option[2]);
	}
	else if(option[0] == "sh"){
		pos = 0; dx = Split_next(option[2], pos, '(');
		if(pos != -1){
			address = Split_next(option[2], pos, ')');
			Q = code(sh_dx, ts_to_num(option[1]), ts_to_num(address), Atoi(dx)); 
		}
		else Q = code(sh_label, ts_to_num(option[1]), 0, 0, option[2]);
	}
	else if(option[0] == "sw"){
		pos = 0; dx = Split_next(option[2], pos, '(');
		if(pos != -1){
			address = Split_next(option[2], pos, ')');
			Q = code(sw_dx, ts_to_num(option[1]), ts_to_num(address), Atoi(dx)); 
		}
		else Q = code(sw_label, ts_to_num(option[1]), 0, 0, option[2]);
	}
	else if(option[0] == "move") Q = code(move_TS, ts_to_num(option[1]), ts_to_num(option[2])); 
	else if(option[0] == "mfhi") Q = code(mfhi, ts_to_num(option[1])); 
	else if(option[0] == "mflo") Q = code(mflo, ts_to_num(option[1])); 
	else if(option[0] == "nop") Q = code(nop); 
	else if(option[0] == "syscall") Q = code(syscall); 
	else if(option[0] == "sll"){
		if(option[3][0] == '$') Q = code(sll_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(sll_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "sllv") Q = code(sll_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
	else if(option[0] == "sra"){
		if(option[3][0] == '$') Q = code(sra_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(sra_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "srav") Q = code(sra_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
	else if(option[0] == "srl"){
		if(option[3][0] == '$') Q = code(srl_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(srl_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "srlv") Q = code(srl_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
	else if(option[0] == "subu"){
		if(option[3][0] == '$') Q = code(subu_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(subu_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "addu"){
		if(option[3][0] == '$') Q = code(addu_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(addu_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "addiu") Q = code(addu_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3]));
	else if(option[0] == "abs"){
		Q = code(abs_TS, ts_to_num(option[1]), ts_to_num(option[2]));
	}
	else if(option[0] == "rol"){
		if(option[3][0] == '$') Q = code(rol_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(rol_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	else if(option[0] == "ror"){
		if(option[3][0] == '$') Q = code(ror_TS, ts_to_num(option[1]), ts_to_num(option[2]), ts_to_num(option[3])); 
		else Q = code(ror_i, ts_to_num(option[1]), ts_to_num(option[2]), Atoi(option[3])); 
	}
	Code.push_back(Q);
}

void op_save(string op){
	int pos = 0, len = op.size();
	while(pos < len && (op[pos] == ' ' || op[pos] == '\t')) pos++;
	if(pos >= len || op[pos] == '#') return;
	if(op[pos] != '.' && Find(op, ':')){
		string lab = "";
		for(int i = pos; i < len; i++){
			if(op[i] == ':'){
				pos = i; break;
			}
			lab += op[i];
		}
		label_to_num[lab] = Code_label.size();
		if(readtype == 0) Code_label.push_back(label(0, nowdata));
		else Code_label.push_back(label(1, Code.size()));
		lab = "";
		for(int i = pos + 1; i < len; i++) lab += op[i];
		op_save(lab); 
		return;
	}
	if(op[pos] == '.') op_data_save(op);
	else op_text_save(op);
}

void Find_label(){
	int len = Code.size();
	for(int i =0; i < len; i++){
		switch(Code[i].op){
			case la:
				Code[i].B = Code_label[label_to_num[Code[i].lab]].x; break;
			case lb_label:
				Code[i].B = Code_label[label_to_num[Code[i].lab]].x; break;
			case lh_label:
				Code[i].B = Code_label[label_to_num[Code[i].lab]].x; break;
			case lw_label:
				Code[i].B = Code_label[label_to_num[Code[i].lab]].x; break;
			case sb_label:
				Code[i].B = Code_label[label_to_num[Code[i].lab]].x; break;
			case sh_label:
				Code[i].B = Code_label[label_to_num[Code[i].lab]].x; break;
			case sw_label:
				Code[i].B = Code_label[label_to_num[Code[i].lab]].x; break;
			case b:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case beq_TS:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case beq_i:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case bge_TS:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case bge_i:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case bgt_TS:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case bgt_i:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case ble_TS:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case ble_i:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case blt_TS:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case blt_i:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case bne_TS:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case bne_i:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case j:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case jal:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case bgezal:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case bgtzal:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case blezal:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case bltzal:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case bgeu_TS:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case bgeu_i:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case bgtu_TS:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case bgtu_i:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case bleu_TS:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case bleu_i:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case bltu_TS:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
			case bltu_i:
				Code[i].C = Code_label[label_to_num[Code[i].lab]].x; break;
		}
	}
}


#endif

