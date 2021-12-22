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
			cout << "原始信息为: " << input << endl << "128比特摘要为: " << md5(input) << endl;
		}
		else if(flag == '2'){
			cout << "检测文件的md5是否正确" << endl;
			string md5_message = "";
			cout << "请输入您的md5: " << endl;
			cin >> md5_message;
			cout << "输入文件名: " << endl;
			string filepath = "";
			cin >> filepath;
			ifstream ifile(filepath.data());
			ostringstream buf;
			char ch;
			while(buf&&ifile.get(ch))
				buf.put(ch);
			string input = buf.str();
			cout << "文件md5为: " << md5(input) << endl;
			if(md5(input) == md5_message){
				cout << "匹配正确！！" << endl; 
			} 
			else{
				cout << "匹配错误 ~ " << endl;
			}
		}
		else if(flag == '0'){
			string message = "";
			cin >> message;
			cout << "128比特摘要为: " << md5(message) << endl;
		}
		else if(flag == 'q'){
			break;
		}
		else{
			continue;
		}
	}
	cout << "网络安全就是国家安全 " << endl;
	system("pause");
	return 0;
}
