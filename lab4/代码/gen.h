#pragma once
#include <iostream>
#include "bigint.h"

using namespace std;

//�Դ�����n����RabinMiller���
bool RabinMiller(const BigInt& n)
{
	BigInt r, a, y;
	unsigned int s, j;
	r = n - 1;
	s = 0;

	while (!r.IsOdd())
	{
		s++;
		r >> 1;
	}

	//�������һ��С��N-1�ļ����a
	a.Randomsmall();

	//y = a��r����ģn
	y = PowerMode(a, r, n);

	//���J=2��J<S��
	if ((!(y == 1)) && (!(y == (n - 1))))
	{
		j = 1;
		while ((j <= s - 1) && (!(y == (n - 1))))
		{
			y = (y * y) % n;
			if (y == 1)
				return false;
			j++;
		}
		if (!(y == (n - 1)))
			return false;
	}
	return true;
}

//����һ������
BigInt GeneratePrime()
{
	BigInt n;
	int i = 0;

	//���޴�ѭ�������ϲ���������ֱ��i==5ʱ��ͨ������RabinMiller���ԣ��Ż�����whileѭ��
	while (i < 5)
	{
		cout << "���������������" << endl;
		SortPrime(n);
		n.display();

		i = 0;
		//��������RABINMILLER����,����ȫ��ͨ���������ϸ�
		for (; i < 5; i++)
		{
			if (!RabinMiller(n))
			{
				cout << "RABINMILLER����ʧ��" << endl;
				break;
			}
			cout << "RABINMILLER����ͨ��" << endl;
		}
	}
	return n;
}

//���������������Լ��,����շת�����
BigInt Gcd(const BigInt& m, const BigInt& n)
{
	if (n == 0)
		return m;
	else
		return Gcd(n, m % n);
}

//����չŷ������㷨��˷�ģ��
BigInt ExtendedGcd(const BigInt& a, const BigInt& b, BigInt& x, BigInt& y)
{
	BigInt t, d;
	//���һ��������Ϊ�����޷����г�������
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	d = ExtendedGcd(b, a % b, x, y);
	t = x;
	x = y;
	y = t - ((a / b) * y);
	return d;
}