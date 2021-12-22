#pragma once
#include <iostream>
#include "bigint.h"

using namespace std;

//对大奇数n进行RabinMiller检测
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

	//随机产生一个小于N-1的检测数a
	a.Randomsmall();

	//y = a的r次幂模n
	y = PowerMode(a, r, n);

	//检测J=2至J<S轮
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

//产生一个素数
BigInt GeneratePrime()
{
	BigInt n;
	int i = 0;

	//无限次循环，不断产生素数，直到i==5时（通过五轮RabinMiller测试）才会跳出while循环
	while (i < 5)
	{
		cout << "产生待测大奇数：" << endl;
		SortPrime(n);
		n.display();

		i = 0;
		//进行五轮RABINMILLER测试,五轮全部通过则素数合格
		for (; i < 5; i++)
		{
			if (!RabinMiller(n))
			{
				cout << "RABINMILLER测试失败" << endl;
				break;
			}
			cout << "RABINMILLER测试通过" << endl;
		}
	}
	return n;
}

//求两个大数的最大公约数,采用辗转相除法
BigInt Gcd(const BigInt& m, const BigInt& n)
{
	if (n == 0)
		return m;
	else
		return Gcd(n, m % n);
}

//用扩展欧几里德算法求乘法模逆
BigInt ExtendedGcd(const BigInt& a, const BigInt& b, BigInt& x, BigInt& y)
{
	BigInt t, d;
	//如果一个操作数为零则无法进行除法运算
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