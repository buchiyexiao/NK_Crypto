#include "des.h"

int main() 
{
    //用户输入密钥
	string key_input;
    cout <<"输入64bit密钥：" ;
    cin >> key_input;
	char * char_key = get_text(key_input);
	if(is_input_valid(char_key))
	{
		cout<<"64bit 密钥为："<< char_key<<endl;
	}
	else
	{
		cout<<"输入16进制数不合法"<<endl;
		return 0;
	}

	//用户输入密文
	string cipher_input;
    cout <<"输入64bit密文：" ;
    cin >> cipher_input;
	char * char_cipher = get_text(cipher_input); 
	if(is_input_valid(char_cipher))
	{
		cout<<"64bit 密文为："<< char_cipher<<endl;
	}
	else
	{
		cout<<"输入16进制数不合法"<<endl;
		return 0;
	}

	cout<<"解密！！！！！"<<endl<<endl<<endl;

	//用于保存用户输入的64bit二进制密钥
	int bit_key[64];

	//将输入的十六进制密钥char数组转换为二进制int数组
	hex_to_bin(char_key, bit_key);
	cout<<"二进制初始密钥为：";
	for(int i=0;i<64;i++)
		cout<<bit_key[i];
	cout<<endl;

	//用于保存用户输入的64bit二进制密文
	int bit_ciphertext_init[64];

	//将输入的十六进制密文char数组转换为二进制int数组
	hex_to_bin(char_cipher, bit_ciphertext_init);
	cout<<"二进制输入密文为：";
	for(int i=0;i<64;i++)
		cout<<bit_ciphertext_init[i];
	cout<<endl;

	//-----------------子密钥获取------------------------------
	//先要获得16轮子密钥

	//PC-1置换后的二进制密钥数组(56bit)
	int bit_key_aft_PC1[56];

	//密钥完成初始置换PC-1
	for(int m=0;m<56;m++)
	{
		bit_key_aft_PC1[m]=bit_key[PC1_Table[m]-1];
	}

	//把密钥分为左右两半
	int bit_key_l1[28],bit_key_r1[28];
	for(int m=0;m<56;m++)
	{
		if(m<28)
			bit_key_l1[m]=bit_key_aft_PC1[m];
		else
			bit_key_r1[m-28]=bit_key_aft_PC1[m];
	}

	//存储每轮子密钥用于解密
	int round_key_store[16][48];

	//存储每轮移位后的左右密钥
	int bit_key_l2[28],bit_key_r2[28];

	//16轮次结构
	for(int round=0;round<16;round++)
	{
		//密钥左移位
		for(int m=0;m<28;m++)
		{
			bit_key_l2[m]=bit_key_l1[(m+LOOP_Table[round])%28];
			bit_key_r2[m]=bit_key_r1[(m+LOOP_Table[round])%28];
		}

		//更新左右密钥，用于下次循环使用
		for(int m=0;m<28;m++)
		{
			bit_key_l1[m]=bit_key_l2[m];
			bit_key_r1[m]=bit_key_r2[m];
		}

		//密钥完成PC-2置换
		for(int m=0;m<48;m++)
		{
			if(PC2_Table[m]<29)
			{
				round_key_store[round][m]=bit_key_l2[PC2_Table[m]-1];
			}
			else
			{
				round_key_store[round][m]=bit_key_r2[PC2_Table[m]-29];
			}
		}
	}
	//-----------------子密钥获取结束--------------------------


	//IP置换后的二进制密文数组(64bit)
	int bit_ciphertext_aft_IP[64];

	//密文完成初始IP置换
	for(int m=0;m<64;m++)
	{
		bit_ciphertext_aft_IP[m]=bit_ciphertext_init[IP_Table[m]-1];
	}

	//把密文分为左右两半
	int bit_ciphertext_l1[32],bit_ciphertext_r1[32];
	for(int m=0;m<64;m++)
	{
		if(m<32)
			bit_ciphertext_l1[m]=bit_ciphertext_aft_IP[m];
		else
			bit_ciphertext_r1[m-32]=bit_ciphertext_aft_IP[m];
	}

	//存储左右明文
	int bit_ciphertext_l2[32],bit_ciphertext_r2[32];
	int bit_ciphertext_l3[32],bit_ciphertext_r3[48];

	//16轮次结构
	for(int round=0;round<16;round++)
	{

		//对右明文备份
		for(int m=0;m<32;m++)
		{
			bit_ciphertext_r2[m]=bit_ciphertext_r1[m];
		}

		//对右明文进行E扩展运算
		for(int m=0;m<48;m++)
		{
			bit_ciphertext_r3[m]=bit_ciphertext_r1[E_Table[m]-1];
		}

		//右明文与对应的轮密钥做异或运算
		for(int m=0;m<48;m++)
		{
			bit_ciphertext_r3[m]=bit_ciphertext_r3[m]^round_key_store[15-round][m];
		}

		//右明文S盒代换
		for(int m=0;m<8;m++)
		{
			//根据右明文的值从S_Box中选出值
			int s;
			s=S_Box[(bit_ciphertext_r3[m*6]*2+bit_ciphertext_r3[5+m*6])+m*4][bit_ciphertext_r3[1+m*6]*8+bit_ciphertext_r3[2+m*6]*4+bit_ciphertext_r3[3+m*6]*2+bit_ciphertext_r3[4+m*6]];


			//将S_Box中选中的值表示为二进制 并 赋值到bit_plaintext_r3中
			for(int n=1;n<=4;n++)
			{
				bit_ciphertext_r3[(4-n)+4*m]=s%2;
				s=s/2;
			}
		}

		//右明文完成P置换,与左明文异或,并将备份的本轮原始右明文传给左明文，用于下次循环使用
		for(int m=0;m<32;m++)
		{
			bit_ciphertext_r1[m]=bit_ciphertext_r3[P_Table[m]-1]^bit_ciphertext_l1[m];
			bit_ciphertext_l1[m]=bit_ciphertext_r2[m];
		}
	}

	//逆初始置换IPR置换前的二进制明文数组(64bit)
	int bit_plaintext_bfr_IPR[64];

	//16轮后密文左右交换得到明文
	for(int m=0;m<64;m++)
	{
		if(m<32)
			bit_plaintext_bfr_IPR[m]=bit_ciphertext_r1[m];
		else
			bit_plaintext_bfr_IPR[m]=bit_ciphertext_l1[m-32];
	}

	//逆初始置换IPR置换后的二进制明文数组(64bit)
	int bit_plaintext_aft_IPR[64];

	//明文完成逆初始置换
	for(int m=0;m<64;m++)
	{
		bit_plaintext_aft_IPR[m]=bit_plaintext_bfr_IPR[IPR_Table[m]-1];
	}

	cout<<"二进制结果明文为：";
	for(int m=0;m<64;m++)
	{
		cout<<bit_plaintext_aft_IPR[m];
	}
	cout<<endl;

	//存储明文十六进制char数组
	char char_plaintext[17];

	//将得到的二进制明文int数组转化为十六进制char数组
	bin_to_hex(bit_plaintext_aft_IPR, char_plaintext);

	//输出16进制密钥、明文、密文，方便对比结果
	cout<<"**************************************************************************************************"<<endl;
	
	//输出密钥
	cout<<"十六进制 密钥为："<<char_key<<endl;
	
	//输出密文
	cout<<"十六进制 密文为："<<char_cipher<<endl;

	//输出明文
	cout<<"十六进制 明文为："<<char_plaintext<<endl;

	cout<<"**************************************************************************************************"<<endl;
    system("pause");
    return 0;
}
