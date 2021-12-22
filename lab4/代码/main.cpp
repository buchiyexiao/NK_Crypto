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
	cout << "开始生成大素数p" << endl;

	//产生大素数
	BigInt p = GeneratePrime();

	//16进制形式显示
	p.display();
	outfile << "大素数p:" << endl;
	outfile << p;
	cout << endl;

	cout << "开始生成素数q" << endl;

	//产生大素数
	BigInt q = GeneratePrime();

	//16进制形式显示
	q.display();
	outfile << "大素数q:" << endl;
	outfile << q;
	cout << endl;
	cout << "公钥n = p * q" << endl;
	BigInt n = p * q;

	cout << "公钥n为： " << endl;
	//16进制形式显示
	n.display();
	outfile << "公钥n为：" << endl;
	outfile << n;
	cout << endl;
	cout << "公钥e和秘钥d " << endl;
	BigInt t = (p - 1) * (q - 1);

	//e为公开钥
	BigInt e;

	//d为秘密钥，即e模t的乘法逆元
	BigInt d;

	//y用于参与扩展欧几里得运算，存储t模e的乘法逆元
	BigInt y;

	BigInt temp;

	while (1)
	{
		//产生与t互质的e
		e.Random();
		while (!(Gcd(e, t) == 1))
		{
			e.Random();
		}

		//用扩展欧几里德算法试图求出e模t的乘法逆元
		temp = ExtendedGcd(e, t, d, y);

		//e*d模t结果为1，说明d确实是e模t的乘法逆元
		temp = (e * d) % t;
		if (temp == 1)
			break;

		//否则重新生成e
	}


	cout << "公钥e为： " << endl;
	//16进制形式显示
	e.display();
	outfile << "公钥e:" << endl;
	outfile << e;
	cout << endl;

	cout << "秘钥d为： " << endl;
	//16进制形式显示
	d.display();
	outfile << "秘钥d:" << endl;
	outfile << d;
	cout << endl;
	cout << "随机生成明文分组m " << endl;
	BigInt m;
	m.Random();
	cout << "明文分组m为：" << endl;
	//16进制形式显示
	m.display();
	outfile << "明文分组m为：" << endl;
	outfile << m;
	cout << endl;
	cout << "用秘密钥e对m加密,得到密文分组c " << endl;
	BigInt c = PowerMode(m, e, n);
	cout << "密文分组c为：" << endl;
	//16进制形式显示
	c.display();
	outfile << "密文分组c为：" << endl;
	outfile << c;
	cout << endl;
	cout << "用公开钥d对c解密，得到明文分组m2 " << endl;
	BigInt m2 = PowerMode(c, d, n);
	cout << "明文分组m2为：" << endl;
	//16进制形式显示
	m2.display();
	outfile << "明文分组m2为：" << endl;
	outfile << m2;
	cout << endl;

	system("pause");
	return 0;
}
