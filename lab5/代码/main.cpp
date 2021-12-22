#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "md5.h"
using namespace std;


int main() 
{
	cout << "MD5 hash by Buchiyexiao 1811463" << endl;
	while(true){
		cout << "input 0 for message , 1 for file ,2 for check and q for quit" << endl;
		char flag;
		cin >> flag;
		if(flag == '1'){
			FILE *fp;
			char buff[1024];
			string filepath = "";
			cin >> filepath;
			ifstream ifile(filepath.data());
			ostringstream buf;
			char ch;
			while(buf&&ifile.get(ch))
				buf.put(ch);
			string input = buf.str();
			cout << "ԭʼ��ϢΪ: " << input << endl << "128����ժҪΪ: " << md5(input) << endl;
		}
		else if(flag == '2'){
			cout << "����ļ���md5�Ƿ���ȷ" << endl;
			string md5_message = "";
			cout << "����������md5: " << endl;
			cin >> md5_message;
			cout << "�����ļ���: " << endl;
			string filepath = "";
			cin >> filepath;
			ifstream ifile(filepath.data());
			ostringstream buf;
			char ch;
			while(buf&&ifile.get(ch))
				buf.put(ch);
			string input = buf.str();
			cout << "�ļ�md5Ϊ: " << md5(input) << endl;
			if(md5(input) == md5_message){
				cout << "ƥ����ȷ����" << endl; 
			} 
			else{
				cout << "ƥ����� ~ " << endl;
			}
		}
		else if(flag == '0'){
			string message = "";
			cin >> message;
			cout << "128����ժҪΪ: " << md5(message) << endl;
		}
		else if(flag == 'q'){
			break;
		}
		else{
			continue;
		}
	}
	cout << "���簲ȫ���ǹ��Ұ�ȫ " << endl;
	system("pause");
	return 0;
}
