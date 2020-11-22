#include<iostream>
#include<string>
using namespace std;
int get_length(char* text) {
	int i = 0;
	while (text[i] != '\0') {
		i++;
	}
	return i;
}
class letter {
private:
	int num;
	char letter_old;
	char letter_new;
public:
	letter() {
		num = 0;
		letter_old = '\0';
		letter_new = '\0';
	}
	letter(char a) {
		num = 0;
		letter_old = a;
		letter_new = '\0';
	}
	void set_old(char a) {
		letter_old = a;
	}
	void set_num(int a) {
		num = a;
	}
	void num_plus() {
		num++;
	}
	void set_new(char a) {
		letter_new = a;
	}
	char get_old() {
		return letter_old;
	}
	char get_new() {
		return letter_new;
	}
	int get_num() {
		return num;
	}
};
void letter_sort(letter a[]) {
	for (int i = 1; i < 26; i++) {
		for (int j = 0; j < 26 - i; j++) {
			if (a[j].get_num() < a[j + 1].get_num()) {
				char t1 = a[j].get_old();
				a[j].set_old(a[j + 1].get_old());
				a[j + 1].set_old(t1);
				int t2 = a[j].get_num();
				a[j].set_num(a[j + 1].get_num());
				a[j + 1].set_num(t2);
			}
		}
	}
}
int main() {
	char re[27];
	memset(re, '\0', 27);
	letter text_letter[26];
	for (int i = 0; i < 26; i++) {
		text_letter[i].set_old('a' + i);
	}
	cout << "请输入您的文本段:" << endl;
	char* text = new char[1000];
	cin.getline(text, 1000);
	int len = get_length(text);
	double num = 0;
	for (int i = 0; i < len; i++) {
		if (text[i] >= 65 && text[i] <= 90) {
			text_letter[(int)(text[i] - 'A')].num_plus();
			num++;
		}
		if (text[i] >= 97 && text[i] <= 122) {
			text_letter[(int)(text[i] - 'a')].num_plus();
			num++;
		}
	}
	cout << "您的文本中出现的字母频率为：" << endl;
	for (int i = 0; i < 26; i++) {
		text_letter[i].set_old('a' + i);
		cout << (char)('a' + i) << "     " << (double)(text_letter[i].get_num() / num) << endl;
	}

	char real_freq[26] = { 'e','t','o','i','a','n','s','r','h','l','d','u','c','m','p','y','f','g','w','b','v','k','x','j','q','z' };
	letter_sort(text_letter);
	for (int i = 0; i < 26; i++) {
		text_letter[i].set_new(real_freq[i]);
	}
	for (int i = 0; i < 26; i++) {
		re[text_letter[i].get_new() - 'a'] = text_letter[i].get_old();
	}
	re[26] = '\0';
	cout << "置换序列: " << re;
	cout << endl;
	return 0;
}