#ifndef SJTU_SPIM_STRING_HPP
#define SJTU_SPIM_STRING_HPP

#include<iostream>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

inline int ts_to_num(string S){
	if(S == "$zero" || S == "$0") return 0;
	else if(S == "$at" || S == "$1") return  1;
	else if(S == "$v0" || S == "$2") return  2;
	else if(S == "$v1" || S == "$3") return  3;
	else if(S == "$a0" || S == "$4") return  4;
	else if(S == "$a1" || S == "$5") return  5;
	else if(S == "$a2" || S == "$6") return  6;
	else if(S == "$a3" || S == "$7") return  7;
	else if(S == "$t0" || S == "$8") return  8;
	else if(S == "$t1" || S == "$9") return  9;
	else if(S == "$t2" || S == "$10") return 10;
	else if(S == "$t3" || S == "$11") return 11;
	else if(S == "$t4" || S == "$12") return 12;
	else if(S == "$t5" || S == "$13") return 13;
	else if(S == "$t6" || S == "$14") return 14;
	else if(S == "$t7" || S == "$15") return 15;
	else if(S == "$s0" || S == "$16") return 16;
	else if(S == "$s1" || S == "$17") return 17;
	else if(S == "$s2" || S == "$18") return 18;
	else if(S == "$s3" || S == "$19") return 19;
	else if(S == "$s4" || S == "$20") return 20;
	else if(S == "$s5" || S == "$21") return 21;
	else if(S == "$s6" || S == "$22") return 22;
	else if(S == "$s7" || S == "$23") return 23;
	else if(S == "$t8" || S == "$24") return 24;
	else if(S == "$t9" || S == "$25") return 25;
	else if(S == "$gp" || S == "$28") return 28;
	else if(S == "$sp" || S == "$29") return 29;
	else if(S == "$fp" || S == "$30") return 30;
	else if(S == "$ra" || S == "$31") return 31;
}

inline bool Find(string S, char A){
	int len = S.size();
	for(int i = 0; i < len; i++){
		if(S[i] == A) return true;
	}
	return false;
}

inline int Atoi(string S){
	int res = 0, len = S.size(), x = 0;
	if(S[0] == '-') x++;
	for(int i = x; i < len; i++) 
		res = res * 10 + (S[i] - '0');
	if(S[0] == '-') res *= -1;
	return res;
}

string Split_next(string S, int &pos, char A){
	int len = S.size();
	while(pos < len && (S[pos] == ' ' || S[pos] == ',' || S[pos] == '\t')) pos++;
	if(pos >= len){
		pos = -1; return "";
	}
	for(int i = pos; i < len; i++){
		if(S[i] != A) continue;
		string res = ""; int j;
		for(j = pos; j < i; j++) res += S[j];
		pos = j + 1;
		return res;
	}
	pos = -1;
	return "";
}

string Split_string(string op, int pos){
	int l, r, len = op.size();
	for(int i = pos; i < len; i++){
		if(op[i] == '\"'){
			l = i; break;
		}
	}
	for(int i = len - 1; i >= pos; i--){
		if(op[i] == '\"'){
			r = i; break;
		}
	}
	string res = "";
	for(int i = l + 1; i < r; i++) res += op[i];
	return res;
}

#endif

