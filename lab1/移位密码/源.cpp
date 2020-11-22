#include<iostream>
using namespace std;
int get_length(char* text) {
	int i = 0;
	while (text[i] != '\0') {
		i++;
	}
	return i;
}
class shift_crypt {
private:
	int offset;
public:
	shift_crypt() {
		offset = 0;
	}
	shift_crypt(int offset) {
		this->offset = offset;
	}
	char* shift_encrypt(char* plain, int offset) {
		int real_offset = offset % 26;
		int length = get_length(plain);
		char* cipher = new char[length];
		for (int i = 0; i < length; i++) {
			if (plain[i] >= 65 && plain[i] <= 90) {
				int temp = plain[i] + real_offset;
				if (temp > 90)
					temp -= 26;
				cipher[i] = (char)temp;
				continue;
			}
			if (plain[i] >= 97 && plain[i] <= 122) {
				int temp = plain[i] + real_offset;
				if (temp > 122)
					temp -= 26;
				cipher[i] = (char)temp;
				continue;
			}
			cipher[i] = plain[i]; //����ĸ��λĬ�ϲ�����
		}
		cipher[length] = '\0';
		return cipher;
	}
	char* shift_decrypt(char* cipher, int offset) {
		int real_offset = offset % 26;
		int length = get_length(cipher);
		char* plain = new char[length];
		for (int i = 0; i < length; i++) {
			if (cipher[i] >= 65 && cipher[i] <= 90) {
				int temp = cipher[i] - real_offset;
				if (temp < 65)
					temp += 26;
				plain[i] = (char)temp;
				continue;
			}
			if (cipher[i] >= 97 && cipher[i] <= 122) {
				int temp = cipher[i] - real_offset;
				if (temp < 97)
					temp += 26;
				plain[i] = (char)temp;
				continue;
			}
			plain[i] = cipher[i]; //����ĸ��λĬ�ϲ�����
		}
		plain[length] = '\0';
		return plain;
	}
	void brute_force(char* cipher) {
		cout << "����Ϊ��" << cipher << endl;
		for (int i = 0; i < 26; i++) {
			cout << "��λΪ��" << i << "   ����Ϊ��" << shift_decrypt(cipher, i) << endl;
		}
		cout << endl;
	}
};
int main() {
	int flag;
	cout << "��ѡ����ܹ��̻��߽��ܹ��̣�0Ϊ���ܣ�1Ϊ���ܣ�2Ϊ���ƣ���������Ϊ�˳�:   ";
	while (true) {
		cin >> flag;
		if (flag == 0) {
			char* plaintext = new char[100];
			int offset;
			cout << "���������ĺ�ƫ������  ";
			cin >> plaintext >> offset;
			shift_crypt encrypt(offset);
			cout << "���ܵõ�������Ϊ��  " << encrypt.shift_encrypt(plaintext, offset) << endl;
		}
		else if (flag == 1) {
			char* ciphertext = new char[100];
			int offset;
			cout << "���������ĺ�ƫ������  ";
			cin >> ciphertext >> offset;
			shift_crypt decrypt(offset);
			cout << "���ܵõ�������Ϊ��  " << decrypt.shift_decrypt(ciphertext, offset) << endl;
		}
		else if (flag == 2) {
			char* ciphertext = new char[100];
			cout << "���������ģ�  ";
			cin >> ciphertext;
			shift_crypt decrypt;
			decrypt.brute_force(ciphertext);
		}
		else {
			break;
		}
	}
	return 0;
}