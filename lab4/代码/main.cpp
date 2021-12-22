#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "bigint.h"
#include "gen.h"
#include <ctime>

using namespace std;

int main()
{
	ofstream outfile("test.txt");
	cout << "��ʼ���ɴ�����p" << endl;

	//����������
	BigInt p = GeneratePrime();

	//16������ʽ��ʾ
	p.display();
	outfile << "������p:" << endl;
	outfile << p;
	cout << endl;

	cout << "��ʼ��������q" << endl;

	//����������
	BigInt q = GeneratePrime();

	//16������ʽ��ʾ
	q.display();
	outfile << "������q:" << endl;
	outfile << q;
	cout << endl;
	cout << "��Կn = p * q" << endl;
	BigInt n = p * q;

	cout << "��ԿnΪ�� " << endl;
	//16������ʽ��ʾ
	n.display();
	outfile << "��ԿnΪ��" << endl;
	outfile << n;
	cout << endl;
	cout << "��Կe����Կd " << endl;
	BigInt t = (p - 1) * (q - 1);

	//eΪ����Կ
	BigInt e;

	//dΪ����Կ����eģt�ĳ˷���Ԫ
	BigInt d;

	//y���ڲ�����չŷ��������㣬�洢tģe�ĳ˷���Ԫ
	BigInt y;

	BigInt temp;

	while (1)
	{
		//������t���ʵ�e
		e.Random();
		while (!(Gcd(e, t) == 1))
		{
			e.Random();
		}

		//����չŷ������㷨��ͼ���eģt�ĳ˷���Ԫ
		temp = ExtendedGcd(e, t, d, y);

		//e*dģt���Ϊ1��˵��dȷʵ��eģt�ĳ˷���Ԫ
		temp = (e * d) % t;
		if (temp == 1)
			break;

		//������������e
	}


	cout << "��ԿeΪ�� " << endl;
	//16������ʽ��ʾ
	e.display();
	outfile << "��Կe:" << endl;
	outfile << e;
	cout << endl;

	cout << "��ԿdΪ�� " << endl;
	//16������ʽ��ʾ
	d.display();
	outfile << "��Կd:" << endl;
	outfile << d;
	cout << endl;
	cout << "����������ķ���m " << endl;
	BigInt m;
	m.Random();
	cout << "���ķ���mΪ��" << endl;
	//16������ʽ��ʾ
	m.display();
	outfile << "���ķ���mΪ��" << endl;
	outfile << m;
	cout << endl;
	cout << "������Կe��m����,�õ����ķ���c " << endl;
	BigInt c = PowerMode(m, e, n);
	cout << "���ķ���cΪ��" << endl;
	//16������ʽ��ʾ
	c.display();
	outfile << "���ķ���cΪ��" << endl;
	outfile << c;
	cout << endl;
	cout << "�ù���Կd��c���ܣ��õ����ķ���m2 " << endl;
	BigInt m2 = PowerMode(c, d, n);
	cout << "���ķ���m2Ϊ��" << endl;
	//16������ʽ��ʾ
	m2.display();
	outfile << "���ķ���m2Ϊ��" << endl;
	outfile << m2;
	cout << endl;

	system("pause");
	return 0;
}
