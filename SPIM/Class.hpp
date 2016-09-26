#ifndef SJTU_SPIM_CLASS_HPP
#define SJTU_SPIM_CLASS_HPP

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

using namespace std;

int stacktop = 1000000000;

int nowdata = 0, nowheap = 300000000;

char *data; // datatop up, stacktop down

void Prework(){
	data = (char *)malloc(1000000006 * sizeof(char));
}

enum options {
	add_TS, add_i, and_TS, and_i, andi, div_TS, div_i, div_two, mul_TS, mul_i, mult, multu, neg_TS, nor_TS,
	nor_i, not_TS, or_TS, or_i, rem_TS, rem_i, sub_TS, sub_i, xor_TS, xor_i, li, seq_TS, seq_i, sge_TS, sge_i,
	sgt_TS, sgt_i, sle_TS, sle_i, slt_TS, slt_i, sne_TS, sne_i, b, beq_TS, beq_i, bge_TS, bge_i,bgezal, bgt_TS,
	bgt_i, ble_TS, ble_i, blezal, bltzal, blt_TS, blt_i, bne_TS, bne_i, j, jal, jalr, jr, la, lb_label, lb_dx,
	lh_label, lh_dx, lw_label, lw_dx, sb_label, sb_dx, sw_label, sw_dx, move_TS, mfhi, mflo, nop, syscall,
	sll_TS, sll_i, sra_TS, sra_i, srl_TS, srl_i, subu_TS, subu_i, addu_TS, addu_i, abs_TS, divu_TS, divu_i,
	divu_two, remu_TS, remu_i, rol_TS, rol_i, ror_TS, ror_i, sgeu_TS, sgeu_i, sgtu_TS, sgtu_i, sleu_TS, sleu_i,
	sltu_TS, sltu_i, bgtzal, bgeu_TS, bgeu_i, bgtu_TS, bgtu_i, bleu_TS, bleu_i, bltu_TS, bltu_i, sh_dx, sh_label
};

struct code{
	int op, A, B, C;
	string lab;
public:
	code(int _op = 0, int _A = 0, int _B = 0, int _C = 0, string _lab = "") : op(_op), A(_A), B(_B), C(_C), lab(_lab) {}

};

struct label{
	int ty, x; //ty: 0 -> .data, 1 -> .text
	label(int _ty = 0, int _x = 0) : ty(_ty), x(_x) {}
};

std::unordered_map<string, int> label_to_num;
std::vector<code> Code;
std::vector<label> Code_label;

int TS[36]; // register, high:32, low:33, 35: 1 the program ends

int lock[36], retu; // retu: the num which program will return

char Read_string[3000010];

struct flow{
	int op, A, B, C, top;
	int to_ts[3], to_data[3];
	bool exist, isjump;
	flow(int _op = 0, int _A = 0, int _B = 0, int _C = 0) : op(_op), A(_A), B(_B), C(_C){
		top = 0; exist = 0; isjump = 0;
		memset(to_ts, 0, sizeof(to_ts));
		memset(to_data, 0, sizeof(to_data));
	}
}F[5];
//0: IF, 1:Decode && Getdata, 2:Calc, 3:Memory Access, 4:Write Back

struct instruction{
	int op, A, B, C;
	instruction(int _op = 0, int _A = 0, int _B = 0, int _C = 0) : op(_op), A(_A), B(_B), C(_C){}
};

#endif

