#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
using namespace std;

 //基本逻辑函数 宏定义
#define F(b,c,d) (( b & c ) | (( ~b ) & ( d )))
#define G(b,c,d) (( b & d ) | ( c & ( ~d )))
#define H(b,c,d) ( b ^ c ^ d )
#define I(b,c,d) ( c ^ ( b | ( ~d )))
//x循环左移n位 宏定义
#define shift(x,n) (( x << n ) | ( x >> ( 32 - n )))
//压缩函数每轮的每步中A分块循环左移的位数
const unsigned s[64] = 
{
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};
const unsigned T[64] = 
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};
string int2hexstr(int origin)
{
	const char str16[] = "0123456789abcdef";
	unsigned hexNum;

	string temp;
	string hexString = "";

	for (int i = 0; i < 4; i++) 
	{
		temp = "";
		hexNum = (origin >> (i * 8)) & 0xff;
		
		for (int j = 0; j < 2; j++) 
		{
			temp.insert(0, 1, str16[hexNum % 16]);
			hexNum /= 16;
		}

		hexString += temp;
	}
	return hexString;
}
string md5(string message)
{
	unsigned int A = 0x67452301;
	unsigned int B = 0xefcdab89;
	unsigned int C = 0x98badcfe;
	unsigned int D = 0x10325476;
	
	int lengthInByte = message.length();
	int groupNum = ((lengthInByte + 8) / 64) + 1;
	unsigned int *messageByte = new unsigned int[groupNum * 16];
	memset(messageByte, 0, sizeof(unsigned int)*groupNum * 16);
	for (int i = 0; i < lengthInByte; i++) 
	{
		messageByte[i / 4] |= message[i] << ((i % 4) * 8);
	}
	messageByte[lengthInByte >> 2] |= 0x80 << ((lengthInByte % 4) * 8);
	
	messageByte[groupNum * 16 - 2] = lengthInByte * 8;

	unsigned int a, b, c, d;
	for (int i = 0; i < groupNum; i++) 
	{
		a = A; 
		b = B; 
		c = C; 
		d = D;
		unsigned int g;
		int k;

		for (int j = 0; j < 64; j++) 
		{
			if ( j < 16 )  
			{
				g = F(b, c, d);
				k = j;
			}
			else if ( j>=16 && j < 32 ) 
			{
				g = G(b, c, d);
				k = (1 + 5 * j) % 16;
			}
			else if ( j>=32 && j < 48 ) 
			{
				g = H(b, c, d);
				k = (5 + 3 * j) % 16;
			}
			else if ( j>=48 && j < 64 )
			{
				g = I(b, c, d);
				k = (7 * j) % 16;
			}

			unsigned tempd = d;
			d = c;
			c = b;
			b = b + shift(a + g + messageByte[i * 16 + k] + T[j], s[j]);
			a = tempd;
		}
		A = a + A;
		B = b + B;
		C = c + C;
		D = d + D;
	}
	return int2hexstr(A) + int2hexstr(B) + int2hexstr(C) + int2hexstr(D);
}
int cmp_bit(string NewSumry,string OrigiSumry)
{
	int BitDiff = 0;
	for(int part=0;part<8;part++)
	{
		string NewSumry_temp =NewSumry.substr(0+4*part, 4);
		char * end_1;
		long NewSumry_Int = static_cast<long>(strtol(NewSumry_temp.c_str(),&end_1,16));
		string OrigiSumry_temp =OrigiSumry.substr(0+4*part, 4);
		char * end_2;
		long OrigiSumry_Int = static_cast<long>(strtol(OrigiSumry_temp.c_str(),&end_2,16));
		for(int round = 0;round <16;round++ )
		{
			if( NewSumry_Int%2 != OrigiSumry_Int%2)
			{
				BitDiff++;
			}
			NewSumry_Int /= 2;
			OrigiSumry_Int /= 2;
		}
	}

	 return BitDiff;
}
