#include "myaes.h"
using namespace std;
string int2binstr(int text[4][4]){
	string result;
	for(int i = 0;i<4;i++){
		for(int j = 0;j<4;j++){
			string str = "00000000";
			int temp = text[j][i];
			for(int k = 7;k>=0;k--) {
				str[k] = '0' + temp % 2;
				temp /= 2;
			}
			result += str;
		}
	}
	return result;
} 
void binstr2int(int text[4][4],string str){
	unsigned char* output = new unsigned char[16];
	for(int i = 0;i <= 15;i++){
		int start = i*8;
		int temp = 0;
		for(int j = start;j<=start + 7;j++){
			int each = 1;
			for(int s = 1;s <= 7 - j + start;s++){
				each *= 2;
			}
			if(str[i] == '1'){
				temp += each;	
			}
		}
		output[i] = temp;
	}
	for(int i = 0;i<4;i++){
		for(int j = 0;j<4;j++){
			text[j][i] = output[j*4+i];
		}
	}
}
//基本运算
int mult(int a, int b)
{
	int third = b & 0x8;
	int second = b & 0x4;
	int first = b & 0x2;
	int firstMod = b % 2;
	int res = 0;

	if (third)
	{
		int temp = a;
		for (int i = 1; i <= 3; ++i)
		{
			temp = temp << 1;
			if (temp >= 256)
			{
				temp = temp ^ 0x11b;
			}
		}
		temp = temp % 256;
		res = res ^ temp;
	}
	if (second)
	{
		int temp = a;
		for (int i = 1; i <= 2; ++i)
		{
			temp = temp << 1;
			if (temp >= 256)
			{
				temp = temp ^ 0x11b;
			}
		}
		temp = temp % 256;
		res = res ^ temp;
	}
	if (first)
	{
		int temp = a;
		temp = temp << 1;
		if (temp >= 256)
		{
			temp = temp ^ 0x11b;
		}
		temp = temp % 256;
		res = res ^ temp;
	}
	if (firstMod)
	{
		res = res ^ a;
	}
	return res;
}
void KeyExpansion(int key[4][4], int w[11][4][4])
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; j++)
		{
			w[0][i][j] = key[j][i];

		}
	}
	for (int i = 1; i < 11; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			int temp[4];
			if (j == 0)
			{
				temp[0] = w[i - 1][3][1];
				temp[1] = w[i - 1][3][2];
				temp[2] = w[i - 1][3][3];
				temp[3] = w[i - 1][3][0];
				for (int k = 0; k < 4; ++k)
				{
					int m = temp[k];
					int row = m / 16;
					int col = m % 16;
					temp[k] = S[row][col];
					if (k == 0)
					{
						temp[k] = temp[k] ^ rC[i - 1];
					}
				}
			}
			else
			{
				temp[0] = w[i][j - 1][0];
				temp[1] = w[i][j - 1][1];
				temp[2] = w[i][j - 1][2];
				temp[3] = w[i][j - 1][3];
			}
			for (int x = 0; x < 4; x++)
			{
				w[i][j][x] = w[i - 1][j][x] ^ temp[x];
			}
		}
	}
}
void ByteSub(int in[4][4], int type)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int temp = in[i][j];
			int row = temp / 16;
			int col = temp % 16;
			if (type == 1)
			{
				in[i][j] = S[row][col];
			}
			if (type == 0)
			{
				in[i][j] = rS[row][col];
			}
		}
	}
}
void ShiftRow(int in[4][4], int type) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (type == 1)
			{
				int temp = in[i][0];
				in[i][0] = in[i][1];
				in[i][1] = in[i][2];
				in[i][2] = in[i][3];
				in[i][3] = temp;
			}
			else
			{
				int temp = in[i][3];
				in[i][3] = in[i][2];
				in[i][2] = in[i][1];
				in[i][1] = in[i][0];
				in[i][0] = temp;
			}
		}
	}
}
void MixColumn(int in[4][4], int type)
{
	for (int i = 0; i < 4; i++)
	{
		int t0 = in[0][i];
		int t1 = in[1][i];
		int t2 = in[2][i];

		int t3 = in[3][i];
		if (type == 1)
		{
			in[0][i] = mult(t0, 2) ^ mult(t1, 3) ^ t2 ^ t3;
			in[1][i] = t0 ^ mult(t1, 2) ^ mult(t2, 3) ^ t3;
			in[2][i] = t0 ^ t1 ^ mult(t2, 2) ^ mult(t3, 3);
			in[3][i] = mult(t0, 3) ^ t1 ^ t2 ^ mult(t3, 2);
		}
		else
		{
			in[0][i] = mult(t0, 14) ^ mult(t1, 11) ^ mult(t2, 13) ^ mult(t3, 9);
			in[1][i] = mult(t0, 9) ^ mult(t1, 14) ^ mult(t2, 11) ^ mult(t3, 13);
			in[2][i] = mult(t0, 13) ^ mult(t1, 9) ^ mult(t2, 14) ^ mult(t3, 11);
			in[3][i] = mult(t0, 11) ^ mult(t1, 13) ^ mult(t2, 9) ^ mult(t3, 14);
		}
	}
}
void AddRoundKey(int in[4][4], int key[4][4])
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; j++)
		{
			in[i][j] = in[i][j] ^ key[j][i];
		}
	}
}

//实现
void Encode(int in[4][4], int key[4][4])
{
	int type = 1;
	int subKey[11][4][4];
	KeyExpansion(key, subKey);
	AddRoundKey(in, subKey[0]);
	for (int i = 1; i <= 10; ++i)
	{
		ByteSub(in, type);
		ShiftRow(in, type);
		if (i != 10)
		{
			MixColumn(in, type);
		}
		AddRoundKey(in, subKey[i]);
	}
}
void Decode(int in[4][4], int key[4][4])
{
	int type = 0;
	int subKey[11][4][4];
	KeyExpansion(key, subKey);
	AddRoundKey(in, subKey[10]);
	for (int i = 9; i >= 0; --i)
	{
		ShiftRow(in, type);
		ByteSub(in, type);
		AddRoundKey(in, subKey[i]);
		if (i != 0)
		{
			MixColumn(in, type);
		}

	}
}

int main(){	
	cout<<"明文（16进制）：0001, 0001, 01a1, 98af, da78, 1734, 8615, 3566"<<endl<<"密钥（16进制）：0001, 2001, 7101, 98ae, da79, 1714, 6015, 3594"<<endl<<"密文（16进制）：6cdd, 596b, 8f56, 42cb, d23b, 4798, 1a65, 422a"<<endl;
	cout<<"明文（16进制）：3243, f6a8, 885a, 308d, 3131, 98a2, e037, 0734"<<endl<<"密钥（16进制）：2b7e, 1516, 28ae, d2a6, abf7, 1588, 09cf, 4f3c"<<endl<<"密文（16进制）：3925, 841d, 02dc, 09fb, dc11, 8597, 196a, 0b32"<<endl;
	int flag;
	cout<<"0-->exit;1-->decode;2-->encode"<<endl;
	while(1){
		cin>>flag;
		if(flag == 0){
			break;
		}
		switch (flag){
		case 1:
		{
			int text[4][4];
			int key[4][4];
			cout<<"输入密文(hex 128bit):";
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					cin >> (hex) >> text[j][i];
				}
			}
			cout<<"输入密钥(hex 128bit):";
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					cin >> (hex) >> key[j][i];
				}
			}
			Decode(text, key);
			cout << "明文:";
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					cout << "0x";
					if (text[j][i] < 16)
						cout << "0";
					cout << (hex) << text[j][i] << " ";
				}
			}
			cout<<endl;
			break;
		}
		case 2:
		{
			int text[4][4];
			int text_new[4][4];
			int text_old[4][4];
			int key[4][4];
			int key_new[4][4];
			cout << "输入明文(hex 128bit):";
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					cin >> (hex) >> text[j][i];
					text_new[j][i] = text[j][i];
					text_old[j][i] = text[j][i];
				}
			}
			cout << "输入密钥(hex 128bit):";
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					cin >> (hex) >> key[j][i];
					key_new[j][i] = key[j][i];
				}
			}
			Encode(text, key);
			cout << "密文(hex 128bit):";
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					cout << "0x";
					if (text[j][i] < 16)
						cout << "0";
					cout << (hex) << text[j][i] << " ";
				}

			}
			cout<<endl;
			//修改前8位 
			cout<<"雪崩测试：修改明文~"<<endl;
			string result = int2binstr(text_new);
			for(int i = 0;i <= 7;i++){
				cout<<"明文改变"<<(i+1)<<"位时：";
				if(result[i] == '0')
					result[i] = '1';
				else
					result[i] = '0';
				binstr2int(text_new,result);
				Encode(text_new,key);
				int result_text = 0;
				string s_new = int2binstr(text_new);
				string s = int2binstr(text);
				for(int i = 0;i<128;i++){
					if(s_new[i] == s[i]){
						result_text++;
					}
				}
				cout<<"改变了";
				cout<<(dec)<<result_text<<"位"<<endl;
			}
			cout<<"雪崩测试：修改密钥~"<<endl;
			result = int2binstr(key_new);
			for(int i = 0;i <= 7;i++){
				cout<<"密钥改变"<<(i+1)<<"位时：";
				if(result[i] == '0')
					result[i] = '1';
				else
					result[i] = '0';
				binstr2int(key_new,result);
				Encode(text_old,key_new);
				int result_text = 0;
				string s_new = int2binstr(text_old);
				string s = int2binstr(text);
				for(int i = 0;i<128;i++){
					if(s_new[i] == s[i]){
						result_text++;
					}
				}
				cout<<"改变了";
				cout<<(dec)<<result_text<<"位"<<endl;
			}
			break;
		}
		default:
		{
			cout<<"0-->exit;1-->decode;2-->encode"<<endl;
			break;
		}
		}
	}
	system("pause");
	return 0;
}
