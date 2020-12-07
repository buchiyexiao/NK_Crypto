//�������ļ����ڲ��Ըı������е�1λ������ѩ��ЧӦ
#include "des.h"

int main() 
{

	cout<<"��ʼ���ܴ���"<<endl;

	//���ڱ���ԭ����64bit����������
	int bit_ciphertext_aft_IPR_form[64] = {1,0,0,0,0,0,1,0,1,1,0,1,1,1,0,0,1,0,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,1,0};


	//ʵ��ʹ�õ���Կ
	int bit_key_init[64] = { 0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,1,0,1,1,0,1,1,1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,1,0,0,1,0,0,0,1,1,1,1,0,0,1,1,1,0,1,1,0,1,0,0,1,0,1,0} ;

	//ʵ��ʹ�õ�����
	int bit_plaintext_init[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	//-------------------����������ĸı�һλ������ѩ��ЧӦ�����θı������е�ÿһλ��ͳ�����ķ����ı��λ��-------------------

	cout<<"��ʼ�������ĸı�һλ������ѩ��ЧӦ��"<<endl;

	//�ı�������ĵĵڼ�λ
	int plaintext_changedbit = 0;

	//��¼�ı�����ÿһλ�����ķ����仯��λ��
	int avalanche_record_plaintext[64] = {0};

	//���θı����ĵĵ�0λ--��63λ��ͳ�����ĸı��λ��
	for(;plaintext_changedbit<64;plaintext_changedbit++)
	{
		//��ת��plaintext_changedbitλ
		bit_plaintext_init[plaintext_changedbit] = 1-bit_plaintext_init[plaintext_changedbit];

		//PC-1�û���Ķ�������Կ����(56bit)
		int bit_key_aft_PC1[56];

		//��Կ��ɳ�ʼ�û�PC-1
		for(int m=0;m<56;m++)
		{
			bit_key_aft_PC1[m]=bit_key_init[PC1_Table[m]-1];
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

		//IP�û���Ķ�������������(64bit)
		int bit_plaintext_aft_IP[64];

		//������ɳ�ʼIP�û�
		for(int m=0;m<64;m++)
		{
			bit_plaintext_aft_IP[m]=bit_plaintext_init[IP_Table[m]-1];
		}

		//�����ķ�Ϊ��������
		int bit_plaintext_l1[32],bit_plaintext_r1[32];
		for(int m=0;m<64;m++)
		{
			if(m<32)
				bit_plaintext_l1[m]=bit_plaintext_aft_IP[m];
			else
				bit_plaintext_r1[m-32]=bit_plaintext_aft_IP[m];
		}

		//�洢ÿ������Կ���ڽ���
		int round_key_store[16][48];

		//�洢ÿ����λ���������Կ
		int bit_key_l2[28],bit_key_r2[28];

		//�洢��������
		int bit_plaintext_l2[32],bit_plaintext_r2[32];
		int bit_plaintext_l3[32],bit_plaintext_r3[48];

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

			//�������ı���
			for(int m=0;m<32;m++)
			{
				bit_plaintext_r2[m]=bit_plaintext_r1[m];
			}

			//�������Ľ���E��չ����
			for(int m=0;m<48;m++)
			{
				bit_plaintext_r3[m]=bit_plaintext_r1[E_Table[m]-1];
			}

			//����������Կ���������
			for(int m=0;m<48;m++)
			{
				bit_plaintext_r3[m]=bit_plaintext_r3[m]^round_key_store[round][m];
			}

			//������S�д���
			for(int m=0;m<8;m++)
			{
				//���������ĵ�ֵ��S_Box��ѡ��ֵ
				int s;
				s=S_Box[(bit_plaintext_r3[m*6]*2+bit_plaintext_r3[5+m*6])+m*4][bit_plaintext_r3[1+m*6]*8+bit_plaintext_r3[2+m*6]*4+bit_plaintext_r3[3+m*6]*2+bit_plaintext_r3[4+m*6]];


				//��S_Box��ѡ�е�ֵ��ʾΪ������ �� ��ֵ��bit_plaintext_r3��
				for(int n=1;n<=4;n++)
				{
					bit_plaintext_r3[(4-n)+4*m]=s%2;
					s=s/2;
				}
			}

			//���������P�û�,�����������,�������ݵı���ԭʼ�����Ĵ��������ģ������´�ѭ��ʹ��
			for(int m=0;m<32;m++)
			{
				bit_plaintext_r1[m]=bit_plaintext_r3[P_Table[m]-1]^bit_plaintext_l1[m];
				bit_plaintext_l1[m]=bit_plaintext_r2[m];
			}
		}

		//���ʼ�û�IPR�û�ǰ�Ķ�������������(64bit)
		int bit_ciphertext_bfr_IPR[64];

		//16�ֺ��������ҽ����γ�����
		for(int m=0;m<64;m++)
		{
			if(m<32)
				bit_ciphertext_bfr_IPR[m]=bit_plaintext_r1[m];
			else
				bit_ciphertext_bfr_IPR[m]=bit_plaintext_l1[m-32];
		}

		//���ʼ�û�IPR�û���Ķ�������������(64bit)
		int bit_ciphertext_aft_IPR[64];

		//����������ʼ�û�
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

		//�仯λ����¼��avalanche_record_plaintext������
		avalanche_record_plaintext[plaintext_changedbit] = changedbit_temp;

		cout<<"--------------------------------------------------------------------------------------------------"<<endl;
		cout<<"�ı����ĵ�"<<plaintext_changedbit<<"λ"<<endl;

		cout<<"������Ϊ��";
		for(int m=0;m<64;m++)
		{
			cout<<bit_ciphertext_aft_IPR[m];
		}
		cout<<endl;

		cout<<"ԭ����Ϊ��";
		for(int m=0;m<64;m++)
		{
			cout<<bit_ciphertext_aft_IPR_form[m];
		}
		cout<<endl;

		cout<<"���ĸı�λ��Ϊ��"<<avalanche_record_plaintext[plaintext_changedbit]<<endl;

		cout<<"**************************************************************************************************"<<endl;
	}

	cout<<"�ı����ĵڼ�λ"<<'\t'<<"���������ĸı�λ��"<<'\t'<<endl;
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

	cout<<"�ı������е�һλ���������ĸı��ƽ��λ��Ϊ"<<average_changed<<endl;

    system("pause");
    return 0;
}
