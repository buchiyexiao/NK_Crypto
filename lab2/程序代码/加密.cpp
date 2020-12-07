#include "des.h"
int main(){
	string key_input;
	cout<<"����64bit��Կ��";
	cin>>key_input;
	char* char_key = get_text(key_input);
	if(is_input_valid(char_key)){
		cout<<"���������ԿΪ��"<<char_key<<endl;
	}
	else{
		cout<<"����16������Կ���Ϸ�"<<endl;
		return 0;
	}
	string plain_input;
	cout<<"����64bit���ģ�";
	cin>>plain_input;
	char* char_plain = get_text(plain_input);
	if(is_input_valid(char_plain)){
		cout<<"�����������Ϊ��"<<char_plain<<endl;
	}
	else{
		cout<<"����16�������Ĳ��Ϸ�"<<endl;
		return 0;
	}
	cout<<"���ܣ���������"<<endl<<endl<<endl;
	int bit_key[64];
	hex_to_bin(char_key,bit_key);
	int bit_plain[64];
	hex_to_bin(char_plain,bit_plain);
	//PC-1�û���Ķ�������Կ����
	int bit_key_aft_pc1[56];
	for(int i = 0;i<56;i++){
		bit_key_aft_pc1[i] = bit_key[PC1_Table[i] - 1];
	} 
	//��Կ�ֳ�����
	int bit_key_l1[28],bit_key_r1[28];
	for(int i = 0;i<56;i++){
		if(i<28){
			bit_key_l1[i] = bit_key_aft_pc1[i];
		}
		else{
			bit_key_r1[i-28] = bit_key_aft_pc1[i];
		}
	} 
	//������ɳ�ʼIP�û�
	int bit_plain_aft_ip[64];
	for(int i = 0;i<64;i++){
		bit_plain_aft_ip[i] = bit_plain[IP_Table[i] - 1];
	}
	//���ķֳ�����
	int bit_plain_l1[32],bit_plain_r1[32];
	for(int i = 0;i<64;i++){
		if(i < 32){
			bit_plain_l1[i] = bit_plain_aft_ip[i];
		}
		else{
			bit_plain_r1[i-32] = bit_plain_aft_ip[i];
		}
	} 
	//ÿ������Կ
	int round_key_store[16][48]; 
	//��λ���������Կ
	int bit_key_l2[28],bit_key_r2[28];
	//�������� 
	int bit_plain_l2[32],bit_plain_r2[32];
	int bit_plain_l3[32],bit_plain_r3[32];
	
	for(int round = 0;round <16;round ++){
		//��Կ����λ
		for(int m = 0;m<28;m++){
			bit_key_l2[m] = bit_key_l1[(m + LOOP_Table[round]) %28];
			bit_key_r2[m] = bit_key_r1[(m + LOOP_Table[round]) %28]; 
		}
		//����������Կ
		for(int m = 0;m<28;m++){
			bit_key_l1[m] = bit_key_l2[m];
			bit_key_r1[m] = bit_key_r2[m];
		}
		//��Կ���PC-2�û�
		for(int m = 0;m<48;m++){
			if(PC2_Table[m] < 28){
				round_key_store[round][m] = bit_key_l2[PC2_Table[m]-1];
			}
			else{
				round_key_store[round][m] = bit_key_r2[PC2_Table[m] - 29];
			}
		}
		//����������
		for(int m = 0;m<32;m++){
			bit_plain_r2[m] = bit_plain_r1[m];
		}
		//�������Ľ���E��չ����
		for(int m = 0;m<48;m++){
			bit_plain_r3[m] = bit_plain_r1[E_Table[m] - 1];
		}
		//����������Կ���������
		for(int m = 0;m<48;m++){
			bit_plain_r3[m] = bit_plain_r3[m] ^ round_key_store[round][m];
		}
		//������S�д���
		for(int m = 0;m < 8;m++){
			int s ;
			//���������ĵ�ֵ��S_Box��ѡֵ
			s = S_Box[(bit_plain_r3[m * 6] * 2 + bit_plain_r3[5 + m * 6]) + m * 4][bit_plain_r3[1 + m * 6] * 8 + bit_plain_r3[2 + m * 6] * 4 + bit_plain_r3[3 + m * 6] * 2 + bit_plain_r3[4 + m * 6]];
			//��S_Box��ѡ�е�ֵ��ʾΪ������ �� ��ֵ��bit_plain_r3��
			for(int n = 1;n<=4;n++){
				bit_plain_r3[(4-n) + 4*m] = s % 2;
				s = s/2;
			}
		}
		//���������P�û�������������򣬽����ݵı���ԭʼ�����Ĵ���������
		for(int m = 0 ;m<32;m++){
			bit_plain_r1[m] = bit_plain_r3[P_Table[m] - 1] ^ bit_plain_l1[m];
			bit_plain_l1[m] = bit_plain_r2[m];
		}
	}
	//���ʼ�û�IPR�û�ǰ��Ķ�������������
	int bit_cipher_bfr_ipr[64];
	int bit_cipher_aft_ipr[64];
	//16���������ҽ����õ�����
	for(int m = 0;m<64;m++){
		if(m < 32){
			bit_cipher_bfr_ipr[m] = bit_plain_r1[m];
		}
		else{
			bit_cipher_bfr_ipr[m] = bit_plain_l1[m - 32];
		}
	}
	//����������ʼ�û�
	for(int m = 0;m<64;m++){
		bit_cipher_aft_ipr[m] = bit_cipher_bfr_ipr[IPR_Table[m] - 1];
	}
	cout<<"�����ƽ������Ϊ��";
	for(int m = 0;m<64;m++){
		cout<<bit_cipher_aft_ipr[m];
	}
	cout<<endl;
	char char_cipher[17];
	bin_to_hex(bit_cipher_aft_ipr,char_cipher);
	cout<<"ʮ�����ƽ������������������������������������������"<<endl;
	cout<<"��Կ"<<char_key<<endl;
	cout<<"����"<<char_plain<<endl;
	cout<<"����"<<char_cipher<<endl;
	return 0;
}












