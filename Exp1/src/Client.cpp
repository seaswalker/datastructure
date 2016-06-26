/**
 * 客户端
 */
using namespace std;
#include <string>
#include <vector>
#include <iostream>
#include "Employee.h"

//文件路径
#define PATH "Salary.dat"

/**
 * 把员工vector转为字符串
 */
string mergeData(vector<Employee> employees) {
	string data = "";
	for (int i = 0, l = employees.size();i < l;i ++) {
		data += employees[i].toString() + "\n";
	}
	return data;
}

/**
 * 执行数据输入
 */
vector<Employee> input() {
	vector<Employee> employees;
	cout << "请输入职工数据(输入done结束),格式如下:" << endl;
	cout << "职工编号 姓名 基本工资 加班工资 奖金 扣除" << endl;
	while (true) {
		string str;
		getline(cin, str);
		if (str == "done") {
			break;
		}
		employees.push_back(Employee::parseEmployee(str, true));
	}
	return employees;
}

/**
 * 测试数据
K01 tom 1200 500 1000 134
K02 john 2000 120 500 300
K03 white 1400 200 400 120
 * 正确结果:2566 2320 1880
 */
int main(void) {
	string data = mergeData(input());
	write2File(PATH, data);
	cout << "写入文件Salary.dat成功" << endl;
	//从文件读取
	cout << "读取数据..." << endl;
	vector<string> content = readFile(PATH);
	//转为对象
	vector<Employee> employees;
	for (int i = 0, l = content.size();i < l;i ++) {
		employees.push_back(Employee::parseEmployee(content[i], false));
	}
	//输出
	cout << mergeData(employees) << endl;
	system("pause");
	return 0;
}
