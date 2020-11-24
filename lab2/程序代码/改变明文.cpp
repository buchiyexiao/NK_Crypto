//本程序文件用于测试改变明文中的1位引发的雪崩效应
#include "des.h"

int main() 
{

	cout<<"开始加密处理"<<endl;

	//用于保存原本的64bit二进制密文
	int bit_ciphertext_aft_IPR_form[64] = {1,0,0,0,0,0,1,0,1,1,0,1,1,1,0,0,1,0,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,1,0};


	//实际使用的密钥
	int bit_key_init[64] = { 0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,0,1,1,1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,1,0,0,1,0,0,0,1,1,1,1,0,0,1,1,1,0,1,1,0,1,0,0,1,0,1,0} ;

	//实际使用的明文
	int bit_plaintext_init[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	//-------------------下面测试明文改变一位引发的雪崩效应：依次改变明文中的每一位，统计密文发生改变的位数-------------------

	cout<<"开始测试明文改变一位引发的雪崩效应："<<endl;

	//改变的是明文的第几位
	int plaintext_changedbit = 0;

	//记录改变明文每一位后密文发生变化的位数
	int avalanche_record_plaintext[64] = {0};

	//依次改变明文的第0位--第63位，统计密文改变的位数
	for(;plaintext_changedbit<64;plaintext_changedbit++)
	{
		//反转第plaintext_changedbit位
		bit_plaintext_init[plaintext_changedbit] = 1-bit_plaintext_init[plaintext_changedbit];

		//PC-1置换后的二进制密钥数组(56bit)
		int bit_key_aft_PC1[56];

		//密钥完成初始置换PC-1
		for(int m=0;m<56;m++)
		{
			bit_key_aft_PC1[m]=bit_key_init[PC1_Table[m]-1];
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

		//IP置换后的二进制明文数组(64bit)
		int bit_plaintext_aft_IP[64];

		//明文完成初始IP置换
		for(int m=0;m<64;m++)
		{
			bit_plaintext_aft_IP[m]=bit_plaintext_init[IP_Table[m]-1];
		}

		//把明文分为左右两半
		int bit_plaintext_l1[32],bit_plaintext_r1[32];
		for(int m=0;m<64;m++)
		{
			if(m<32)
				bit_plaintext_l1[m]=bit_plaintext_aft_IP[m];
			else
				bit_plaintext_r1[m-32]=bit_plaintext_aft_IP[m];
		}

		//存储每轮子密钥用于解密
		int round_key_store[16][48];

		//存储每轮移位后的左右密钥
		int bit_key_l2[28],bit_key_r2[28];

		//存储左右明文
		int bit_plaintext_l2[32],bit_plaintext_r2[32];
		int bit_plaintext_l3[32],bit_plaintext_r3[48];

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

			//对右明文备份
			for(int m=0;m<32;m++)
			{
				bit_plaintext_r2[m]=bit_plaintext_r1[m];
			}

			//对右明文进行E扩展运算
			for(int m=0;m<48;m++)
			{
				bit_plaintext_r3[m]=bit_plaintext_r1[E_Table[m]-1];
			}

			//右明文与密钥做异或运算
			for(int m=0;m<48;m++)
			{
				bit_plaintext_r3[m]=bit_plaintext_r3[m]^round_key_store[round][m];
			}

			//右明文S盒代换
			for(int m=0;m<8;m++)
			{
				//根据右明文的值从S_Box中选出值
				int s;
				s=S_Box[(bit_plaintext_r3[m*6]*2+bit_plaintext_r3[5+m*6])+m*4][bit_plaintext_r3[1+m*6]*8+bit_plaintext_r3[2+m*6]*4+bit_plaintext_r3[3+m*6]*2+bit_plaintext_r3[4+m*6]];


				//将S_Box中选中的值表示为二进制 并 赋值到bit_plaintext_r3中
				for(int n=1;n<=4;n++)
				{
					bit_plaintext_r3[(4-n)+4*m]=s%2;
					s=s/2;
				}
			}

			//右明文完成P置换,与左明文异或,并将备份的本轮原始右明文传给左明文，用于下次循环使用
			for(int m=0;m<32;m++)
			{
				bit_plaintext_r1[m]=bit_plaintext_r3[P_Table[m]-1]^bit_plaintext_l1[m];
				bit_plaintext_l1[m]=bit_plaintext_r2[m];
			}
		}

		//逆初始置换IPR置换前的二进制密文数组(64bit)
		int bit_ciphertext_bfr_IPR[64];

		//16轮后明文左右交换形成密文
		for(int m=0;m<64;m++)
		{
			if(m<32)
				bit_ciphertext_bfr_IPR[m]=bit_plaintext_r1[m];
			else
				bit_ciphertext_bfr_IPR[m]=bit_plaintext_l1[m-32];
		}

		//逆初始置换IPR置换后的二进制密文数组(64bit)
		int bit_ciphertext_aft_IPR[64];

		//密文完成逆初始置换
		for(int m=0;m<64;m++)
		{
			bit_ciphertext_aft_IPR[m]=bit_ciphertext_bfr_IPR[IPR_Table[m]-1];
		}

		int changedbit_temp = 0;

		for(int m=0;m<64;m++)
		{
			if(bit_ciphertext_aft_IPR[m] != bit_ciphertext_aft_IPR_form[m])
				changedbit_temp++;
		}

		//变化位数记录到avalanche_record_plaintext数组里
		avalanche_record_plaintext[plaintext_changedbit] = changedbit_temp;

		cout<<"--------------------------------------------------------------------------------------------------"<<endl;
		cout<<"改变明文第"<<plaintext_changedbit<<"位"<<endl;

		cout<<"新密文为：";
		for(int m=0;m<64;m++)
		{
			cout<<bit_ciphertext_aft_IPR[m];
		}
		cout<<endl;

		cout<<"原密文为：";
		for(int m=0;m<64;m++)
		{
			cout<<bit_ciphertext_aft_IPR_form[m];
		}
		cout<<endl;

		cout<<"密文改变位数为："<<avalanche_record_plaintext[plaintext_changedbit]<<endl;

		cout<<"**************************************************************************************************"<<endl;
	}

	cout<<"改变明文第几位"<<'\t'<<"引发的密文改变位数"<<'\t'<<endl;
	for(int m=0;m<64;m++)
	{
		cout<<'\t'<<m<<'\t'<<'\t'<<avalanche_record_plaintext[m]<<'\t'<<endl;
	}

	double average_changed =0;
	for(int m=0;m<64;m++)
	{
		average_changed+=avalanche_record_plaintext[m];
	}
	average_changed /=64;

	cout<<"改变明文中的一位，引发密文改变的平均位数为"<<average_changed<<endl;

    system("pause");
    return 0;
}
