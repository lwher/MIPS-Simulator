#include <iostream>
#include <map>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <fstream>

#include "Class.hpp"
#include "Decode.hpp"
#include "Decode_flow.hpp"
#include "String_option.hpp"
#include "Instruction_Save.hpp"

using namespace std;

void Flow_and_work(){
	bool Canread = 1, havedone, flag;
	int T, ty, Instruction_num = 0, now = label_to_num["main"]; // where first instuct is
	now = Code_label[now].x;
	TS[29] = stacktop;
	F[0].exist = 1;		
	for(T = 1; ; T++){
		havedone = 0; flag = 0; 
		for(int x = 4; x >= 0; x--){
			if(F[x].exist){
				switch(x){
					case 4:
						for(int i = 0; i < F[4].top; i++){
							TS[F[4].to_ts[i]] = F[4].to_data[i];
							--lock[F[4].to_ts[i]];
						}
						F[4].exist = 0; ++Instruction_num;
						if(F[4].isjump) Canread = 1;
						if(TS[35]){
							//cout << Instruction_num << endl;
							//cout << T << endl;
							return;
						}
						break;
					case 3:
						ty = Solve_step_Memory(F[3]);
						if(ty != 0) havedone = 1;
						F[3].exist = 0;			
						F[x + 1] = F[x]; F[x + 1].exist = 1;
						break;
					case 2:
						F[2].exist = 0; F[x + 1] = F[x]; F[x + 1].exist = 1;
						break;
					case 1:
						if(Solve_step_Decode(F[1], Canread, now)){
							F[1].exist = 0; F[x + 1] = F[x]; F[x + 1].exist = 1;
						}
						else flag = 1;
						break;
					case 0:
						if(Canread && !havedone){
							code np = Code[now];
							now++;
							F[1] = flow(np.op, np.A, np.B, np.C);
							F[1].exist = 1;
						}
						break;	
				}
			}
			if(flag) break;
		}
	}
}

void work(){
	instruction ops;
	int now = label_to_num["main"]; // where first instuct is
	now = Code_label[now].x;
	TS[29] = stacktop;
	for(;;){
		code np = Code[now];
		now++;
		ops = instruction(np.op, np.A, np.B, np.C);
		Decode(ops, now);
		if(TS[35]) return;
	}
}

int main(int argc, char* argv[]){
	Prework(); 
	string option;	
	ifstream fin(argv[1]);		
	while(getline(fin, option))
		op_save(option);
	fin.close();
	Find_label();
	work();
	//Flow_and_work();	
	free(data);
	return retu;
}

