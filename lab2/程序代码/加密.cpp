#include "des.h"
int main(){
	string key_input;
	cout<<"输入64bit密钥：";
	cin>>key_input;
	char* char_key = get_text(key_input);
	if(is_input_valid(char_key)){
		cout<<"您输入的密钥为："<<char_key<<endl;
	}
	else{
		cout<<"输入16进制密钥不合法"<<endl;
		return 0;
	}
	string plain_input;
	cout<<"输入64bit明文：";
	cin>>plain_input;
	char* char_plain = get_text(plain_input);
	if(is_input_valid(char_plain)){
		cout<<"您输入的明文为："<<char_plain<<endl;
	}
	else{
		cout<<"输入16进制明文不合法"<<endl;
		return 0;
	}
	cout<<"加密！！！！！"<<endl<<endl<<endl;
	int bit_key[64];
	hex_to_bin(char_key,bit_key);
	int bit_plain[64];
	hex_to_bin(char_plain,bit_plain);
	//PC-1置换后的二进制密钥数组
	int bit_key_aft_pc1[56];
	for(int i = 0;i<56;i++){
		bit_key_aft_pc1[i] = bit_key[PC1_Table[i] - 1];
	} 
	//密钥分成两半
	int bit_key_l1[28],bit_key_r1[28];
	for(int i = 0;i<56;i++){
		if(i<28){
			bit_key_l1[i] = bit_key_aft_pc1[i];
		}
		else{
			bit_key_r1[i-28] = bit_key_aft_pc1[i];
		}
	} 
	//明文完成初始IP置换
	int bit_plain_aft_ip[64];
	for(int i = 0;i<64;i++){
		bit_plain_aft_ip[i] = bit_plain[IP_Table[i] - 1];
	}
	//明文分成两半
	int bit_plain_l1[32],bit_plain_r1[32];
	for(int i = 0;i<64;i++){
		if(i < 32){
			bit_plain_l1[i] = bit_plain_aft_ip[i];
		}
		else{
			bit_plain_r1[i-32] = bit_plain_aft_ip[i];
		}
	} 
	//每轮子密钥
	int round_key_store[16][48]; 
	//移位后的左右密钥
	int bit_key_l2[28],bit_key_r2[28];
	//左右明文 
	int bit_plain_l2[32],bit_plain_r2[32];
	int bit_plain_l3[32],bit_plain_r3[32];
	
	for(int round = 0;round <16;round ++){
		//密钥左移位
		for(int m = 0;m<28;m++){
			bit_key_l2[m] = bit_key_l1[(m + LOOP_Table[round]) %28];
			bit_key_r2[m] = bit_key_r1[(m + LOOP_Table[round]) %28]; 
		}
		//更新左右密钥
		for(int m = 0;m<28;m++){
			bit_key_l1[m] = bit_key_l2[m];
			bit_key_r1[m] = bit_key_r2[m];
		}
		//密钥完成PC-2置换
		for(int m = 0;m<48;m++){
			if(PC2_Table[m] < 28){
				round_key_store[round][m] = bit_key_l2[PC2_Table[m]-1];
			}
			else{
				round_key_store[round][m] = bit_key_r2[PC2_Table[m] - 29];
			}
		}
		//备份右明文
		for(int m = 0;m<32;m++){
			bit_plain_r2[m] = bit_plain_r1[m];
		}
		//对右明文进行E拓展运算
		for(int m = 0;m<48;m++){
			bit_plain_r3[m] = bit_plain_r1[E_Table[m] - 1];
		}
		//右明文于密钥做异或运算
		for(int m = 0;m<48;m++){
			bit_plain_r3[m] = bit_plain_r3[m] ^ round_key_store[round][m];
		}
		//右明文S盒代换
		for(int m = 0;m < 8;m++){
			int s ;
			//根据右明文的值从S_Box中选值
			s = S_Box[(bit_plain_r3[m * 6] * 2 + bit_plain_r3[5 + m * 6]) + m * 4][bit_plain_r3[1 + m * 6] * 8 + bit_plain_r3[2 + m * 6] * 4 + bit_plain_r3[3 + m * 6] * 2 + bit_plain_r3[4 + m * 6]];
			//将S_Box中选中的值表示为二进制 并 赋值到bit_plain_r3中
			for(int n = 1;n<=4;n++){
				bit_plain_r3[(4-n) + 4*m] = s % 2;
				s = s/2;
			}
		}
		//右明文完成P置换，与左明文异或，将备份的本轮原始右明文传给左明文
		for(int m = 0 ;m<32;m++){
			bit_plain_r1[m] = bit_plain_r3[P_Table[m] - 1] ^ bit_plain_l1[m];
			bit_plain_l1[m] = bit_plain_r2[m];
		}
	}
	//逆初始置换IPR置换前后的二进制明文数组
	int bit_cipher_bfr_ipr[64];
	int bit_cipher_aft_ipr[64];
	//16轮明文左右交换得到密文
	for(int m = 0;m<64;m++){
		if(m < 32){
			bit_cipher_bfr_ipr[m] = bit_plain_r1[m];
		}
		else{
			bit_cipher_bfr_ipr[m] = bit_plain_l1[m - 32];
		}
	}
	//密文完成逆初始置换
	for(int m = 0;m<64;m++){
		bit_cipher_aft_ipr[m] = bit_cipher_bfr_ipr[IPR_Table[m] - 1];
	}
	cout<<"二进制结果密文为：";
	for(int m = 0;m<64;m++){
		cout<<bit_cipher_aft_ipr[m];
	}
	cout<<endl;
	char char_cipher[17];
	bin_to_hex(bit_cipher_aft_ipr,char_cipher);
	cout<<"十六进制结果————————————————————"<<endl;
	cout<<"密钥"<<char_key<<endl;
	cout<<"明文"<<char_plain<<endl;
	cout<<"密文"<<char_cipher<<endl;
	return 0;
}












