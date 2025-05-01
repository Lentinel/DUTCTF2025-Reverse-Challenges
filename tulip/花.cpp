#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<map>
#include<vector>
#include<queue>
#include<stack>
#include<set>
#include<string>
#include<cstring>
#include<list>
#include<stdlib.h>
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define DELTA 0x114514

using namespace std;
void Tea(uint32_t* flag, const uint32_t* Key) {
	
	uint32_t sum = 0;
	int i;
	uint32_t v1 = flag[0];
	uint32_t v2 = flag[1];
	_asm {
		jz label1 // zf不为0 跳转
		jnz label1 // zf标志位 为0跳转
		_EMIT 0x89
		label1 :
	}
	_asm
	{
		call f1
		f1 :
		add     byte ptr[esp + 0], 6
		ret
		_EMIT 0x89
	}
	for (i = 0; i < 32; i++) {
		sum += DELTA;
		
		v1 += ((v2 << 4) + Key[0]) ^ (v2 + sum) ^ ((v2 >> 5) + Key[1]);
		v2 += ((v1 << 4) + Key[2]) ^ (v1 + sum) ^ ((v1 >> 5) + Key[3]);
	}
	flag[0] = v1;
	flag[1] = v2;
}

int Check(uint32_t* enc, uint32_t* Input) {
	
	int i = 0;
	for (i; i < 12; i++) {
		
		if (enc[i] != Input[i]) {
			return 0;
		}
	}
	return 1;
}

int main() {
	
	uint32_t Key[4] = { 0x11223344, 0x55667788, 0x99AABBCC, 0xDDEEFF11 };
	uint32_t enc[12] = { 0x329e0eaf,0x6a398361,0x320b21fa,0x2200b7f1,0x2e086774,0x74eaef36,0xe8ef0a23,0xafd4ac64,0x92f93a03,0xb37a9bff,0x3ced126c,0xf5e00531 };
	uint32_t* FlagInput = NULL;
	char Input[100] = { 0 };
	cout<<"Please input your flag:";
	cin>> Input;
	_asm {
		jz label1 
		jnz label1 
		_EMIT 0x89
		label1 :
	}
	_asm
	{
		call f1
		f1 :
		add     byte ptr[esp + 0], 6
		ret
		_EMIT 0x89
	}
	FlagInput = (uint32_t*)Input;
	for (int i = 0; i < 6; i++) {
		Tea(&FlagInput[i * 2], Key);
	}
	if (Check(enc, FlagInput)) {
		cout << "太强了！！！";
	}
	else
	{
		cout << "这不是flag啊喂！";
	}
	return 0;
}

