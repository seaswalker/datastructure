/**
 * �ͻ���
 */
using namespace std;
#include <string>
#include <vector>
#include <iostream>
#include "Employee.h"

//�ļ�·��
#define PATH "Salary.dat"

/**
 * ��Ա��vectorתΪ�ַ���
 */
string mergeData(vector<Employee> employees) {
	string data = "";
	for (int i = 0, l = employees.size();i < l;i ++) {
		data += employees[i].toString() + "\n";
	}
	return data;
}

/**
 * ִ����������
 */
vector<Employee> input() {
	vector<Employee> employees;
	cout << "������ְ������(����done����),��ʽ����:" << endl;
	cout << "ְ����� ���� �������� �Ӱ๤�� ���� �۳�" << endl;
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
 * ��������
K01 tom 1200 500 1000 134
K02 john 2000 120 500 300
K03 white 1400 200 400 120
 * ��ȷ���:2566 2320 1880
 */
int main(void) {
	string data = mergeData(input());
	write2File(PATH, data);
	cout << "д���ļ�Salary.dat�ɹ�" << endl;
	//���ļ���ȡ
	cout << "��ȡ����..." << endl;
	vector<string> content = readFile(PATH);
	//תΪ����
	vector<Employee> employees;
	for (int i = 0, l = content.size();i < l;i ++) {
		employees.push_back(Employee::parseEmployee(content[i], false));
	}
	//���
	cout << mergeData(employees) << endl;
	system("pause");
	return 0;
}
