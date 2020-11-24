#include "des.h"

int main() 
{
    //�û�������Կ
	string key_input;
    cout <<"����64bit��Կ��" ;
    cin >> key_input;
	char * char_key = get_text(key_input);
	if(is_input_valid(char_key))
	{
		cout<<"64bit ��ԿΪ��"<< char_key<<endl;
	}
	else
	{
		cout<<"����16���������Ϸ�"<<endl;
		return 0;
	}

	//�û���������
	string cipher_input;
    cout <<"����64bit���ģ�" ;
    cin >> cipher_input;
	char * char_cipher = get_text(cipher_input); 
	if(is_input_valid(char_cipher))
	{
		cout<<"64bit ����Ϊ��"<< char_cipher<<endl;
	}
	else
	{
		cout<<"����16���������Ϸ�"<<endl;
		return 0;
	}

	cout<<"���ܣ���������"<<endl<<endl<<endl;

	//���ڱ����û������64bit��������Կ
	int bit_key[64];

	//�������ʮ��������Կchar����ת��Ϊ������int����
	hex_to_bin(char_key, bit_key);
	cout<<"�����Ƴ�ʼ��ԿΪ��";
	for(int i=0;i<64;i++)
		cout<<bit_key[i];
	cout<<endl;

	//���ڱ����û������64bit����������
	int bit_ciphertext_init[64];

	//�������ʮ����������char����ת��Ϊ������int����
	hex_to_bin(char_cipher, bit_ciphertext_init);
	cout<<"��������������Ϊ��";
	for(int i=0;i<64;i++)
		cout<<bit_ciphertext_init[i];
	cout<<endl;

	//-----------------����Կ��ȡ------------------------------
	//��Ҫ���16������Կ

	//PC-1�û���Ķ�������Կ����(56bit)
	int bit_key_aft_PC1[56];

	//��Կ��ɳ�ʼ�û�PC-1
	for(int m=0;m<56;m++)
	{
		bit_key_aft_PC1[m]=bit_key[PC1_Table[m]-1];
	}

	//����Կ��Ϊ��������
	int bit_key_l1[28],bit_key_r1[28];
	for(int m=0;m<56;m++)
	{
		if(m<28)
			bit_key_l1[m]=bit_key_aft_PC1[m];
		else
			bit_key_r1[m-28]=bit_key_aft_PC1[m];
	}

	//�洢ÿ������Կ���ڽ���
	int round_key_store[16][48];

	//�洢ÿ����λ���������Կ
	int bit_key_l2[28],bit_key_r2[28];

	//16�ִνṹ
	for(int round=0;round<16;round++)
	{
		//��Կ����λ
		for(int m=0;m<28;m++)
		{
			bit_key_l2[m]=bit_key_l1[(m+LOOP_Table[round])%28];
			bit_key_r2[m]=bit_key_r1[(m+LOOP_Table[round])%28];
		}

		//����������Կ�������´�ѭ��ʹ��
		for(int m=0;m<28;m++)
		{
			bit_key_l1[m]=bit_key_l2[m];
			bit_key_r1[m]=bit_key_r2[m];
		}

		//��Կ���PC-2�û�
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
	//-----------------����Կ��ȡ����--------------------------


	//IP�û���Ķ�������������(64bit)
	int bit_ciphertext_aft_IP[64];

	//������ɳ�ʼIP�û�
	for(int m=0;m<64;m++)
	{
		bit_ciphertext_aft_IP[m]=bit_ciphertext_init[IP_Table[m]-1];
	}

	//�����ķ�Ϊ��������
	int bit_ciphertext_l1[32],bit_ciphertext_r1[32];
	for(int m=0;m<64;m++)
	{
		if(m<32)
			bit_ciphertext_l1[m]=bit_ciphertext_aft_IP[m];
		else
			bit_ciphertext_r1[m-32]=bit_ciphertext_aft_IP[m];
	}

	//�洢��������
	int bit_ciphertext_l2[32],bit_ciphertext_r2[32];
	int bit_ciphertext_l3[32],bit_ciphertext_r3[48];

	//16�ִνṹ
	for(int round=0;round<16;round++)
	{

		//�������ı���
		for(int m=0;m<32;m++)
		{
			bit_ciphertext_r2[m]=bit_ciphertext_r1[m];
		}

		//�������Ľ���E��չ����
		for(int m=0;m<48;m++)
		{
			bit_ciphertext_r3[m]=bit_ciphertext_r1[E_Table[m]-1];
		}

		//���������Ӧ������Կ���������
		for(int m=0;m<48;m++)
		{
			bit_ciphertext_r3[m]=bit_ciphertext_r3[m]^round_key_store[15-round][m];
		}

		//������S�д���
		for(int m=0;m<8;m++)
		{
			//���������ĵ�ֵ��S_Box��ѡ��ֵ
			int s;
			s=S_Box[(bit_ciphertext_r3[m*6]*2+bit_ciphertext_r3[5+m*6])+m*4][bit_ciphertext_r3[1+m*6]*8+bit_ciphertext_r3[2+m*6]*4+bit_ciphertext_r3[3+m*6]*2+bit_ciphertext_r3[4+m*6]];


			//��S_Box��ѡ�е�ֵ��ʾΪ������ �� ��ֵ��bit_plaintext_r3��
			for(int n=1;n<=4;n++)
			{
				bit_ciphertext_r3[(4-n)+4*m]=s%2;
				s=s/2;
			}
		}

		//���������P�û�,�����������,�������ݵı���ԭʼ�����Ĵ��������ģ������´�ѭ��ʹ��
		for(int m=0;m<32;m++)
		{
			bit_ciphertext_r1[m]=bit_ciphertext_r3[P_Table[m]-1]^bit_ciphertext_l1[m];
			bit_ciphertext_l1[m]=bit_ciphertext_r2[m];
		}
	}

	//���ʼ�û�IPR�û�ǰ�Ķ�������������(64bit)
	int bit_plaintext_bfr_IPR[64];

	//16�ֺ��������ҽ����õ�����
	for(int m=0;m<64;m++)
	{
		if(m<32)
			bit_plaintext_bfr_IPR[m]=bit_ciphertext_r1[m];
		else
			bit_plaintext_bfr_IPR[m]=bit_ciphertext_l1[m-32];
	}

	//���ʼ�û�IPR�û���Ķ�������������(64bit)
	int bit_plaintext_aft_IPR[64];

	//����������ʼ�û�
	for(int m=0;m<64;m++)
	{
		bit_plaintext_aft_IPR[m]=bit_plaintext_bfr_IPR[IPR_Table[m]-1];
	}

	cout<<"�����ƽ������Ϊ��";
	for(int m=0;m<64;m++)
	{
		cout<<bit_plaintext_aft_IPR[m];
	}
	cout<<endl;

	//�洢����ʮ������char����
	char char_plaintext[17];

	//���õ��Ķ���������int����ת��Ϊʮ������char����
	bin_to_hex(bit_plaintext_aft_IPR, char_plaintext);

	//���16������Կ�����ġ����ģ�����ԱȽ��
	cout<<"**************************************************************************************************"<<endl;
	
	//�����Կ
	cout<<"ʮ������ ��ԿΪ��"<<char_key<<endl;
	
	//�������
	cout<<"ʮ������ ����Ϊ��"<<char_cipher<<endl;

	//�������
	cout<<"ʮ������ ����Ϊ��"<<char_plaintext<<endl;

	cout<<"**************************************************************************************************"<<endl;
    system("pause");
    return 0;
}
