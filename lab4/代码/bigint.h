#pragma once
#include <iostream>
#include <stdlib.h> 
using namespace std;

const int MAXSIZE = 64;
static int prime[] = { 3,    5,    7,    11,   13,   17,   19,   23,   29,   31,
37,   41,   43,   47,   53,   59,   61,   67,   71,   73,
79,   83,   89,   97,   101,  103,  107,  109,  113,  127,
131,  137,  139,  149,  151,  157,  163,  167,  173,  179,
181,  191,  193,  197,  199,  211,  223,  227,  229,  233,
239,  241,  251,  257,  263,  269,  271,  277,  281,  283,
293,  307,  311,  313,  317,  331,  337,  347,  349,  353,
359,  367,  373,  379,  383,  389,  397,  401,  409,  419,
421,  431,  433,  439,  443,  449,  457,  461,  463,  467,
479,  487,  491,  499,  503,  509,  521,  523,  541,  547,
557,  563,  569,  571,  577,  587,  593,  599,  601,  607,
613,  617,  619,  631,  641,  643,  647,  653,  659,  661,
673,  677,  683,  691,  701,  709,  719,  727,  733,  739,
743,  751,  757,  761,  769,  773,  787,  797,  809,  811,
821,  823,  827,  829,  839,  853,  857,  859,  863,  877,
881,  883,  887,  907,  911,  919,  929,  937,  941,  947,
953,  967,  971,  977,  983,  991,  997,  1009, 1013, 1019,
1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087,
1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153,
1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229,
1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297,
1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381,
1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453,
1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511, 1523,
1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597,
1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663,
1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741,
1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811, 1823,
1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 1901,
1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993,
1997, 1999, 2003, 2011, 2017, 2027, 2029, 2039, 2053, 2063,
2069, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129, 2131,
2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213, 2221,
2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287, 2293,
2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357, 2371,
2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423, 2437,
2441, 2447, 2459, 2467, 2473, 2477, 2503, 2521, 2531, 2539,
2543, 2549, 2551, 2557, 2579, 2591, 2593, 2609, 2617, 2621,
2633, 2647, 2657, 2659, 2663, 2671, 2677, 2683, 2687, 2689,
2693, 2699, 2707, 2711, 2713, 2719, 2729, 2731, 2741, 2749,
2753, 2767, 2777, 2789, 2791, 2797, 2801, 2803, 2819, 2833,
2837, 2843, 2851, 2857, 2861, 2879, 2887, 2897, 2903, 2909,
2917, 2927, 2939, 2953, 2957, 2963, 2969, 2971, 2999, 3001,
3011, 3019, 3023, 3037, 3041, 3049, 3061, 3067, 3079, 3083,
3089, 3109, 3119, 3121, 3137, 3163, 3167, 3169, 3181, 3187,
3191, 3203, 3209, 3217, 3221, 3229, 3251, 3253, 3257, 3259,
3271, 3299, 3301, 3307, 3313, 3319, 3323, 3329, 3331, 3343,
3347, 3359, 3361, 3371, 3373, 3389, 3391, 3407, 3413, 3433,
3449, 3457, 3461, 3463, 3467, 3469, 3491, 3499, 3511, 3517,
3527, 3529, 3533, 3539, 3541, 3547, 3557, 3559, 3571, 3581,
3583, 3593, 3607, 3613, 3617, 3623, 3631, 3637, 3643, 3659,
3671, 3673, 3677, 3691, 3697, 3701, 3709, 3719, 3727, 3733,
3739, 3761, 3767, 3769, 3779, 3793, 3797, 3803, 3821, 3823,
3833, 3847, 3851, 3853, 3863, 3877, 3881, 3889, 3907, 3911,
3917, 3919, 3923, 3929, 3931, 3943, 3947, 3967, 3989, 4001,
4003, 4007, 4013, 4019, 4021, 4027, 4049, 4051, 4057, 4073,
4079, 4091, 4093, 4099, 4111, 4127, 4129, 4133, 4139, 4153,
4157, 4159, 4177, 4201, 4211, 4217, 4219, 4229, 4231, 4241,
4243, 4253, 4259, 4261, 4271, 4273, 4283, 4289, 4297, 4327,
4337, 4339, 4349, 4357, 4363, 4373, 4391, 4397, 4409, 4421,
4423, 4441, 4447, 4451, 4457, 4463, 4481, 4483, 4493, 4507,
4513, 4517, 4519, 4523, 4547, 4549, 4561, 4567, 4583, 4591,
4597, 4603, 4621, 4637, 4639, 4643, 4649, 4651, 4657, 4663,
4673, 4679, 4691, 4703, 4721, 4723, 4729, 4733, 4751, 4759,
4783, 4787, 4789, 4793, 4799, 4801, 4813, 4817, 4831, 4861,
4871, 4877, 4889, 4903, 4909, 4919, 4931, 4933, 4937, 4943,
4951, 4957, 4967, 4969, 4973, 4987, 4993, 4999 , 5003, 5009,
5011, 5021, 5023, 5039, 5051, 5059, 5077, 5081, 5087, 5099,
5101, 5107, 5113, 5119, 5147, 5153, 5167, 5171, 5179, 5189,
5197, 5209, 5227, 5231, 5233, 5237, 5261, 5273, 5279, 5281,
5297, 5303, 5309, 5323, 5333, 5347, 5351, 5381, 5387, 5393,
5399, 5407, 5413, 5417, 5419, 5431, 5437, 5441, 5443, 5449,
5471, 5477, 5479, 5483, 5501, 5503, 5507, 5519, 5521, 5527,
5531, 5557, 5563, 5569, 5573, 5581, 5591, 5623, 5639, 5641,
5647, 5651, 5653, 5657, 5659, 5669, 5683, 5689, 5693, 5701,
5711, 5717, 5737, 5741, 5743, 5749, 5779, 5783, 5791, 5801,
5807, 5813, 5821, 5827, 5839, 5843, 5849, 5851, 5857, 5861,
5867, 5869, 5879, 5881, 5897, 5903, 5923, 5927, 5939, 5953,
5981, 5987, 6007, 6011, 6029, 6037, 6043, 6047, 6053, 6067,
6073, 6079, 6089, 6091, 6101, 6113, 6121, 6131, 6133, 6143,
6151, 6163, 6173, 6197, 6199, 6203, 6211, 6217, 6221, 6229,
6247, 6257, 6263, 6269, 6271, 6277, 6287, 6299, 6301, 6311,
6317, 6323, 6329, 6337, 6343, 6353, 6359, 6361, 6367, 6373,
6379, 6389, 6397, 6421, 6427, 6449, 6451, 6469, 6473, 6481,
6491, 6521, 6529, 6547, 6551, 6553, 6563, 6569, 6571, 6577,
6581, 6599, 6607, 6619, 6637, 6653, 6659, 6661, 6673, 6679,
6689, 6691, 6701, 6703, 6709, 6719, 6733, 6737, 6761, 6763,
6779, 6781, 6791, 6793, 6803, 6823, 6827, 6829, 6833, 6841,
6857, 6863, 6869, 6871, 6883, 6899, 6907, 6911, 6917, 6947,
6949, 6959, 6961, 6967, 6971, 6977, 6983, 6991, 6997, 7001,
7013, 7019, 7027, 7039, 7043, 7057, 7069, 7079, 7103, 7109,
7121, 7127, 7129, 7151, 7159, 7177, 7187, 7193, 7207, 7211,
7213, 7219, 7229, 7237, 7243, 7247, 7253, 7283, 7297, 7307,
7309, 7321, 7331, 7333, 7349, 7351, 7369, 7393, 7411, 7417,
7433, 7451, 7457, 7459, 7477, 7481, 7487, 7489, 7499, 7507,
7517, 7523, 7529, 7537, 7541, 7547, 7549, 7559, 7561, 7573,
7577, 7583, 7589, 7591, 7603, 7607, 7621, 7639, 7643, 7649,
7669, 7673, 7681, 7687, 7691, 7699, 7703, 7717, 7723, 7727,
7741, 7753, 7757, 7759, 7789, 7793, 7817, 7823, 7829, 7841,
7853, 7867, 7873, 7877, 7879, 7883, 7901, 7907, 7919, 7927,
7933, 7937, 7949, 7951, 7963, 7993, 8009, 8011, 8017, 8039,
8053, 8059, 8069, 8081, 8087, 8089, 8093, 8101, 8111, 8117,
8123, 8147, 8161, 8167, 8171, 8179, 8191, 8209, 8219, 8221,
8231, 8233, 8237, 8243, 8263, 8269, 8273, 8287, 8291, 8293,
8297, 8311, 8317, 8329, 8353, 8363, 8369, 8377, 8387, 8389,
8419, 8423, 8429, 8431, 8443, 8447, 8461, 8467, 8501, 8513,
8521, 8527, 8537, 8539, 8543, 8563, 8573, 8581, 8597, 8599,
8609, 8623, 8627, 8629, 8641, 8647, 8663, 8669, 8677, 8681,
8689, 8693, 8699, 8707, 8713, 8719, 8731, 8737, 8741, 8747,
8753, 8761, 8779, 8783, 8803, 8807, 8819, 8821, 8831, 8837,
8839, 8849, 8861, 8863, 8867, 8887, 8893, 8923, 8929, 8933,
8941, 8951, 8963, 8969, 8971, 8999, 9001, 9007, 9011, 9013,
9029, 9041, 9043, 9049, 9059, 9067, 9091, 9103, 9109, 9127,
9133, 9137, 9151, 9157, 9161, 9173, 9181, 9187, 9199, 9203,
9209, 9221, 9227, 9239, 9241, 9257, 9277, 9281, 9283, 9293,
9311, 9319, 9323, 9337, 9341, 9343, 9349, 9371, 9377, 9391,
9397, 9403, 9413, 9419, 9421, 9431, 9433, 9437, 9439, 9461,
9463, 9467, 9473, 9479, 9491, 9497, 9511, 9521, 9533, 9539,
9547, 9551, 9587, 9601, 9613, 9619, 9623, 9629, 9631, 9643,
9649, 9661, 9677, 9679, 9689, 9697, 9719, 9721, 9733, 9739,
9743, 9749, 9767, 9769, 9781, 9787, 9791, 9803, 9811, 9817,
9829, 9833, 9839, 9851, 9857, 9859, 9871, 9883, 9887, 9901,
9907, 9923, 9929, 9931, 9941, 9949, 9967, 9973, 10007,10009 };

class BigInt {

	friend BigInt operator+ (const BigInt&, const BigInt&);
	friend BigInt operator- (const BigInt&, const BigInt&);
	friend BigInt operator- (const BigInt&, const int&);
	friend BigInt operator* (const BigInt&, const BigInt&);
	friend BigInt operator% (const BigInt&, const BigInt&);
	friend BigInt operator/ (const BigInt&, const BigInt&);
	friend BigInt operator* (const BigInt&, const unsigned int&);
	friend bool operator< (const BigInt&, const BigInt&);
	friend bool operator> (const BigInt&, const BigInt&);
	friend bool operator<= (const BigInt&, const int&);
	friend bool operator== (const BigInt&, const BigInt&);
	friend bool operator== (const BigInt&, const int&);
	friend ostream& operator<< (ostream&, const BigInt&);
	friend BigInt PowerMode(const BigInt&, const BigInt&, const BigInt&);
	friend void SortPrime(BigInt& n);

public:
	BigInt();
	BigInt(const int&);
	BigInt(const BigInt&);

	void operator= (const BigInt&);
	void operator= (const int& a) { Clear(); data[0] = a; }
	void operator>> (const int&);

	inline int GetLength() const;   //返回大数的长度
	bool TestSign() { return sign; }  //判断大数的正负 
	void Clear();  //大数清0
	void Random(); //随机产生一个大数
	void Randomsmall();  //随机产生一个稍小的大数
	void display() const;
	void Output(ostream& out) const;
	bool IsOdd() const { return (data[0] & 1); }  //判断大数奇偶性

public:
	unsigned int data[MAXSIZE];
	bool sign;
};

//默认构造函数,成员数据清0
BigInt::BigInt()
{
	for (int i = 0; i < MAXSIZE; i++)
		data[i] = 0;
	sign = true;
}


//用int初始化大数
BigInt::BigInt(const int& input)
{
	for (int i = 0; i < MAXSIZE; i++)
		data[i] = 0;
	data[0] = input;
	if (input >= 0)
		sign = true;
	else
		sign = false;
}

//用大数给大数赋值
BigInt::BigInt(const BigInt& input)
{
	for (int i = 0; i < MAXSIZE; i++)
		data[i] = input.data[i];
	sign = input.sign;
}

//用大数给大数赋值
void BigInt::operator= (const BigInt& input)
{
	for (int i = 0; i < MAXSIZE; i++)
		data[i] = input.data[i];
	sign = input.sign;
}

//比较两个大数的大小,a<b,返回真,否则返回假
bool operator< (const BigInt& a, const BigInt& b)
{
	for (int i = MAXSIZE - 1; i > 0; i--)
	{
		if (a.data[i] < b.data[i])
			return true;
		if (a.data[i] > b.data[i])
			return false;
	}
	return a.data[0] < b.data[0];
}

//比较两个大数的大小,a>b,返回真,否则返回假
bool operator> (const BigInt& a, const BigInt& b)
{
	for (int i = MAXSIZE - 1; i >= 0; i--)
	{
		if (a.data[i] > b.data[i])
			return true;
		if (a.data[i] < b.data[i])
			return false;
	}
	return false;
}

//判断两个大数是否相等,相等返回真,否则返回假
bool operator== (const BigInt& a, const BigInt& b)
{
	for (int i = 0; i < MAXSIZE; i++)
		if (a.data[i] != b.data[i])
			return false;
	return true;
}

//判断一个大数和一个int值是否相等,相等返回真,否则返回假
bool operator== (const BigInt& a, const int& b)
{
	for (int i = 1; i < a.GetLength(); i++)
		if (a.data[i] != 0)
			return false;
	return a.data[0] == b;
}

//计算两个大数的和,采用竖式相加法
BigInt operator+ (const BigInt& a, const BigInt& b)
{
	BigInt result;
	//64位数据,存放每两位数相加的临时和
	unsigned __int64 sum;
	//carry为进位标志,sub为当两数符号相异时,存放每两位数相减的临时差
	unsigned int carry = 0, sub;
	//取a,b中长度较长的长度
	int length = (a.GetLength() >= b.GetLength() ? a.GetLength() : b.GetLength());

	//当两数符号相同时,进行加法运算
	if (a.sign == b.sign)
	{
		//每一位进行竖式相加
		for (int i = 0; i < length; i++)
		{
			sum = (unsigned __int64)a.data[i] + b.data[i] + carry;
			result.data[i] = (unsigned int)sum;
			//sum的高位为进位
			carry = (sum >> 32);
		}

		result.sign = a.sign;
		return result;
	}

	//两数符号不同时,进行减法运算
	else
	{
		BigInt tempa, tempb;

		//取出a,b中绝对值较大的作为被减数
		if (a < b)
		{
			tempa = b;
			tempb = a;
		}
		else
		{
			tempa = a;
			tempb = b;
		}

		//每一位进行竖式减
		for (int i = 0; i < length; i++)
		{
			sub = tempb.data[i] + carry;
			if (tempa.data[i] >= sub)
			{
				result.data[i] = tempa.data[i] - sub;
				carry = 0;
			}
			else
			{
				//借位减
				result.data[i] = (unsigned __int64)tempa.data[i] + (1 << 32) - sub;
				carry = 1;
			}
		}
		result.sign = tempa.sign;
		return result;
	}
}

//计算两个大数的差,采用竖式相减法
BigInt operator- (const BigInt& a, const BigInt& b)
{
	BigInt result;
	//64位数据,存放每两位数相加的临时和
	unsigned __int64 sum;
	//carry为进位标志,sub为当两数符号相异时,存放每两位数相减的临时差
	unsigned int carry = 0, sub;

	//符号相同时,进行减法运算
	if (a.sign == b.sign)
	{
		BigInt tempa, tempb;

		//取出a,b中绝对值较大的作为被减数
		if (a < b)
		{
			tempa = b;
			tempb = a;
			tempa.sign = !tempa.sign;
		}
		else
		{
			tempa = a;
			tempb = b;
		}

		//每一位进行竖式减
		for (int i = 0; i < MAXSIZE; i++)
		{
			sub = tempb.data[i] + carry;
			if (tempa.data[i] >= sub)
			{
				result.data[i] = tempa.data[i] - sub;
				carry = 0;
			}
			else
			{
				//借位减
				result.data[i] = (unsigned __int64)tempa.data[i] + (1 << 32) - sub;
				carry = 1;
			}
		}
		result.sign = tempa.sign;
		return result;
	}

	//两数符号不同时,进行加法运算
	else
	{
		//每一位进行竖式相加
		for (int i = 0; i < MAXSIZE; i++)
		{
			sum = (unsigned __int64)a.data[i] + b.data[i] + carry;
			result.data[i] = (unsigned int)sum;
			//sum的高位为进位
			carry = (sum >> 32);
		}
		result.sign = a.sign;
		return result;
	}
}

//大数减一个int数
BigInt operator- (const BigInt& a, const int& b)
{
	BigInt temp(b);
	BigInt result = a - temp;
	return result;
}


//大数乘以一个INT数
BigInt operator* (const BigInt& a, const unsigned int& b)
{
	BigInt result;
	//存放B乘以A的每一位的临时积
	unsigned __int64 sum;
	//存放进位
	unsigned int carry = 0;

	for (int i = 0; i < MAXSIZE; i++)
	{
		sum = ((unsigned __int64)a.data[i]) * b + carry;
		result.data[i] = (unsigned int)sum;
		//进位在SUM的高位中
		carry = (sum >> 32);
	}
	result.sign = a.sign;
	return result;
}

//大数相乘,采用竖式乘
BigInt operator* (const BigInt& a, const BigInt& b)
{
	//last存放竖式上一行的积,temp存放当前行的积
	BigInt result, last, temp;
	//sum存放当前行带进位的积
	unsigned __int64 sum;
	//存放进位
	unsigned int carry;

	//进行竖式乘
	for (int i = 0; i < b.GetLength(); i++)
	{
		carry = 0;
		//B的每一位与A相乘
		for (int j = 0; j < a.GetLength() + 1; j++)
		{
			sum = ((unsigned __int64)a.data[j]) * (b.data[i]) + carry;
			if ((i + j) < MAXSIZE)
				temp.data[i + j] = (unsigned int)sum;
			carry = (sum >> 32);
		}
		result = (temp + last);
		last = result;
		temp.Clear();
	}

	//判断积的符号
	if (a.sign == b.sign)
		result.sign = true;
	else
		result.sign = false;

	return result;
}

//大数除,采用试商除法,采用二分查找法优化
BigInt operator/ (const BigInt& a, const BigInt& b)
{
	//mul为当前试商,low,high为二分查找试商时所用的标志
	unsigned int mul, low, high;
	//sub为除数与当前试商的积,subsequent为除数与下一试商的积
	//dividend存放临时被除数
	BigInt dividend, quotient, sub, subsequent;
	int lengtha = a.GetLength(), lengthb = b.GetLength();

	//如果被除数小于除数,直接返回0
	if (a < b)
	{
		if (a.sign == b.sign)
			quotient.sign = true;
		else
			quotient.sign = false;
		return quotient;
	}

	//把被除数按除数的长度从高位截位
	int i;
	for (i = 0; i < lengthb; i++)
		dividend.data[i] = a.data[lengtha - lengthb + i];

	for (i = lengtha - lengthb; i >= 0; i--)
	{
		//如果被除数小于除数,再往后补位
		if (dividend < b)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
			continue;
		}

		low = 0;
		high = 0xffffffff;

		//二分查找法查找试商
		while (low < high)
		{
			mul = (((unsigned __int64)high) + low) / 2;
			sub = (b * mul);
			subsequent = (b * (mul + 1));

			if (((sub < dividend) && (subsequent > dividend)) || (sub == dividend))
				break;
			if (subsequent == dividend)
			{
				mul++;
				sub = subsequent;
				break;
			}
			if ((sub < dividend) && (subsequent < dividend))
			{
				low = mul;
				continue;
			}
			if ((sub > dividend) && (subsequent > dividend))
			{
				high = mul;
				continue;
			}

		}

		//试商结果保存到商中去
		quotient.data[i] = mul;
		//临时被除数变为被除数与试商积的差
		dividend = dividend - sub;

		//临时被除数往后补位
		if ((i - 1) >= 0)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
		}
	}

	//判断商的符号
	if (a.sign == b.sign)
		quotient.sign = true;
	else
		quotient.sign = false;
	return quotient;
}

//大数求模运算,与除法运算类似
BigInt operator% (const BigInt& a, const BigInt& b)
{
	unsigned int mul, low, high;
	BigInt dividend, quotient, sub, subsequent;
	int lengtha = a.GetLength(), lengthb = b.GetLength();

	//如果被除数小于除数,返回被除数为模
	if (a < b)
	{
		dividend = a;
		//余数的商永远与被除数相同
		dividend.sign = a.sign;
		return dividend;
	}

	//进行除法运算
	int i;
	for (i = 0; i < lengthb; i++)
		dividend.data[i] = a.data[lengtha - lengthb + i];

	for (i = lengtha - lengthb; i >= 0; i--)
	{
		if (dividend < b)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
			continue;
		}

		low = 0;
		high = 0xffffffff;

		while (low <= high)
		{
			mul = (((unsigned __int64)high) + low) / 2;
			sub = (b * mul);
			subsequent = (b * (mul + 1));

			if (((sub < dividend) && (subsequent > dividend)) || (sub == dividend))
				break;
			if (subsequent == dividend)
			{
				mul++;
				sub = subsequent;
				break;
			}
			if ((sub < dividend) && (subsequent < dividend))
			{
				low = mul;
				continue;
			}
			if ((sub > dividend) && (subsequent > dividend))
			{
				high = mul;
				continue;
			}
		}

		quotient.data[i] = mul;
		dividend = dividend - sub;
		if ((i - 1) >= 0)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
		}
	}

	//临时被除数即为所求模
	dividend.sign = a.sign;
	return dividend;
}

//产生一个随机大数,大数的LENGTH为SIZE的1/4,是为了防止运算时的溢出
void BigInt::Random()
{
	for (int i = 0; i < (MAXSIZE / 4); i++)
		//由于RAND()最大只能产生0X7FFF的数,为了能产生32位的随机数,需要
		//3次RAND()操作
		data[i] = (rand() << 17) + (rand() << 2) + rand() % 4;
}


//产生一个较小的随机大数,大数的LENGTH为SIZE的1/8
void BigInt::Randomsmall()
{
	for (int i = 0; i < (MAXSIZE / 16); i++)
		//由于RAND()最大只能产生0X7FFF的数,为了能产生32位的随机数,需要
		//3次RAND()操作
		data[i] = (rand() << 17) + (rand() << 2) + rand() % 4;
}

//将大数以16进制显示到屏幕上
void BigInt::display() const
{
	unsigned int temp, result;
	unsigned int an = 0xf0000000;

	for (int i = GetLength() - 1; i >= 0; i--)
	{
		temp = data[i];
		//大数的每一位数字转换成16进制输出
		for (int j = 0; j < 8; j++)
		{
			result = temp & an;
			result = (result >> 28);
			temp = (temp << 4);
			if (result >= 0 && result <= 9)
				cout << result;
			else
			{
				switch (result)
				{
				case 10:
					cout << "A";
					break;
				case 11:
					cout << "B";
					break;
				case 12:
					cout << "C";
					break;
				case 13:
					cout << "D";
					break;
				case 14:
					cout << "E";
					break;
				case 15:
					cout << "F";
					break;
				}
			}
		}
		cout << " ";
		if (i == GetLength() / 2)
			cout << endl;
	}
	cout << endl;
}

//将大数输出到输入输出流
void BigInt::Output(ostream& out) const
{
	unsigned int temp, result;
	unsigned int an = 0xf0000000;

	for (int i = GetLength() - 1; i >= 0; i--)
	{
		temp = data[i];
		//大数的每一位数字转换成16进制输出
		for (int j = 0; j < 8; j++)
		{
			result = temp & an;
			result = (result >> 28);
			temp = (temp << 4);
			if (result >= 0 && result <= 9)
				out << result;
			else
			{
				switch (result)
				{
				case 10:
					out << "A";
					break;
				case 11:
					out << "B";
					break;
				case 12:
					out << "C";
					break;
				case 13:
					out << "D";
					break;
				case 14:
					out << "E";
					break;
				case 15:
					out << "F";
					break;
				}
			}
		}
	}
	out << endl;
}

//重载输出操作符
ostream& operator<< (ostream& out, const BigInt& x)
{
	x.Output(out);
	return out;
}

//大数置0
void BigInt::Clear()
{
	for (int i = 0; i < MAXSIZE; i++)
		data[i] = 0;
}

//返回大数长度
inline int BigInt::GetLength() const
{
	int length = MAXSIZE;
	for (int i = MAXSIZE - 1; i >= 0; i--)
	{
		//第一位不为0即为LENGTH
		if (data[i] == 0)
			length--;
		else
			break;
	}
	return length;
}

//重载移位操作符,向右移N位
void BigInt::operator>> (const int& a)
{
	unsigned int bit;
	data[0] = (data[0] >> a);
	for (int i = 1; i < GetLength(); i++)
	{
		//先将每一位的低位移到BIT中
		bit = data[i] & 1;
		//再把BIT移到上一位的高位中
		bit = bit << (32 - a);;
		data[i - 1] = data[i - 1] | bit;
		data[i] = (data[i] >> a);
	}
}

//判断大数和一个INT的大小
bool operator<= (const BigInt& a, const int& b)
{
	for (int i = 1; i < a.GetLength(); i++)
	{
		if (a.data[i] != 0)
			return false;
	}
	if (a.data[0] <= b)
		return true;
	else
		return false;
}


//模幂运算——计算n的p次幂模m
//利用Montgomery算法，
BigInt PowerMode(const BigInt& n, const BigInt& p, const BigInt& m)
{
	BigInt temp = p;
	BigInt base = n % m;
	BigInt result(1);

	//检测指数p的二进制形式的每一位
	while (!(temp <= 1))
	{
		//如果该位为1，则表示该位需要参与模运算
		if (temp.IsOdd())
		{
			result = (result * base) % m;
		}
		base = (base * base) % m;
		temp >> 1;
	}
	return (base * result) % m;
}


//产生一个待测素数,保证此数为奇数,且不能被小于5000的素数整除
void SortPrime(BigInt& n)
{
	int i = 0;
	BigInt divisor;
	const int length = sizeof(prime) / sizeof(int);

	while (i != length)
	{
		n.Random();
		while (!n.IsOdd())
			n.Random();

		i = 0;
		for (; i < length; i++)
		{
			divisor = prime[i];
			if ((n % divisor) == 0)
				break;
		}
	}
}

