/*
 * util.cpp
 *
 *  Created on: 2015年10月10日
 *      Author: skywalker
 */
#include "util.h"
using namespace std;

vector<string> split(string str, string pattern) {
	string::size_type pos;
	vector<string> result;
	str += pattern; //扩展字符串以方便操作
	unsigned int size = str.size();
	for (unsigned int i = 0; i < size; i++) {
		pos = str.find(pattern, i);
		if (pos < size) {
			string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

float string2Float(string str) {
	const char* arr = str.c_str();
	return atof(arr);
}

string float2String(float num) {
	ostringstream os;
	os << num;
	return os.str();
}

void write2File(string path, string data) {
	ofstream os;
	os.open(path.c_str());
	os << data;
	os.close();
}

vector<string> readFile(string path) {
	ifstream ifs;
	vector<string> data;
	ifs.open(path.c_str());
	if (!ifs.rdbuf()->is_open()) {
		cout <<"文件打开错误!" << endl;
	}
	string str;
	while (getline(ifs, str)) {
		data.push_back(str);
	}
	ifs.close();
	return data;
}

