#include <iostream>
#include <map>
#include <ctime>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <io.h>

using namespace std;

string table[36];

void Pre_work(){
	table[1] = "array_test1-mahaojun";
	table[2] = "array_test2-mahaojun";
	table[3] = "basicopt1-5100309127-hetianxing";
	table[4] = "builtin-5140519064-youyurong";
	table[5] = "bulgarian-5110379024-wuhang";
	table[6] = "class_test-mahaojun";
	table[7] = "expr-5110309085-jintianxing";
	table[8] = "function_test-huyuncong";
	table[9] = "gcd-5090379042-jiaxiao";
	table[10] = "hanoi-5100379110-daibo";
	table[11] = "hashmap-5100309127-hetianxing";
	table[12] = "heapsort-5100379110-daibo";
	table[13] = "horse2-5100309153-yanghuan";
	table[14] = "horse3-5100309153-yanghuan";
	table[15] = "horse-5100309153-yanghuan";
	table[16] = "lvalue2-5110379024-wuhang";
	table[17] = "magic-5100309153-yanghuan";
	table[18] = "manyarguments-5100379110-daibo";
	table[19] = "maxflow-5100379110-daibo";
	table[20] = "multiarray-5100309153-yanghuan";
	table[21] = "pi-5090379042-jiaxiao";
	table[22] = "prime-5100309153-yanghuan";
	table[23] = "qsort-5100379110-daibo";
	table[24] = "queens-5100379110-daibo";
	table[25] = "spill2-5100379110-daibo";
	table[26] = "statement_test-huyuncong";
	table[27] = "string_test-huyuncong";
	table[28] = "superloop-5090379042-jiaxiao";
	table[29] = "tak-5090379042-jiaxiao";
	table[30] = "twinprime-5090379042-jiaxiao";
	
}

int main(){
	int T = 0, t0 = clock(), sum = 30;
	bool flag = 0;
	Pre_work();	
	for(int i = 1; i <= 30; i++){
		cout << "Case "  << i << ": " << table[i] << endl;
		string p = "", q = "";
		p = "SPIM " + table[i] + ".s ";
		q = table[i] + ".in";
		if(access(q.c_str(), 0) != -1) p += "<" + table[i] + ".in ";
		p += "> user.ans";
		t0 = clock();
		system(p.c_str());
		T += clock() - t0;
		q = "fc /W user.ans " + table[i] + ".ans";
		if(system(q.c_str())) {
			flag = 1; sum--; //break;
		}
		//cout << "Passed !" << endl;
	}
	cout << "You have passed : " << sum << "/30" << endl;
	if(!flag){
		cout << "You have passed all tests and use time: " << (double)(T) / 1000.0 << "s" << endl;
		system("del user.ans");
	} 
	return 0;
}

