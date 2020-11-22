#include<iostream>
#include<map>
#include<string>
#include<stdio.h>
using namespace std;
int get_length(char* text) {
	int i = 0;
	while (text[i] != '\0') {
		i++;
	}
	return i;
}
map<char, char> list;
int* a = new int[26];
int main() {
	char* text = new char[100];
	for (int i = 0; i < 26; i++) {
		a[i] = 0;
	}
	cout << "������Կ�������Կ���ȴ���26λ����ֻȡǰ26λ" << endl;
	cin >> text;
	if (get_length(text) > 26) {
		text[26] = '\0';
	}
	//ȫ����ΪСд ȥ��
	int t = 0;
	for (int i = 0; i < get_length(text); i++) {
		//ȥ���ո�
		if (text[i] == ' ') {
			continue;
		}
		text[i] = tolower(text[i]);
		if (text[i] < 97 || text[i] > 122) {
			continue;
		}
		if (a[(int)(text[i] - 'a')]) {
			continue;
		}
		else {
			a[(int)(text[i] - 'a')] = 1;
			list[(char)('a' + t)] = text[i];
			t++;
		}
	}
	for (int j = t; j < 26; j++) {
		char temp = '\0';
		for (int k = 0; k < 26; k++) {
			if (a[k] == 0) {
				a[k] = 1;
				temp = (char)('a' + k);
				break;
			}
		}
		list[(char)('a' + j)] = temp;
	}
	cout << endl << "�滻��Ϊ��  " << endl;
	for (int j = 0; j < 26; j++) {
		cout << (char)('a' + j) << " ";
	}
	cout << endl;
	for (int j = 0; j < 26; j++) {
		cout << list[(char)('a' + j)] << " ";
	}
	cout << endl;
	char* plaintext = new char[100];
	cout << "�������ģ�  ";
	cin.get();
	cin.getline(plaintext,100);
	int len = get_length(plaintext);
	char* ciphertext = new char[len];
	for (int j = 0; j < len; j++) {
		plaintext[j] = tolower(plaintext[j]);
		if (plaintext[j] < 97 || plaintext[j] > 122) {
			ciphertext[j] = plaintext[j];
		}
		else {
			ciphertext[j] = list.at((char)(plaintext[j]));

		}
	}
	ciphertext[len] = '\0';
	cout << "��������Ϊ��  " << ciphertext << endl;
	cout << endl << endl;
	cout << "��������Ϊ��  " << endl;
	cin.getline(ciphertext, 100);
	cout << ciphertext << endl;
	len = get_length(ciphertext);
	for (int j = 0; j < len; j++) {
		ciphertext[j] = tolower(ciphertext[j]);
		if (ciphertext[j] < 97 || ciphertext[j] > 122) {
			plaintext[j] = ciphertext[j];
		}
		else {
			for (std::map<char, char>::iterator it = list.begin(); it != list.end(); it++) {
				if (it->second == ciphertext[j]) {
					plaintext[j] = it->first;
				}
			}
		}
	}
	plaintext[len] = '\0';
	cout << "��������Ϊ��  " << plaintext << endl;
	return 0;
}