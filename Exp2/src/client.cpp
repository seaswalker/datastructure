/*
 * client.cpp
 * ����
 *
 *  Created on: 2015��10��13��
 *      Author: skywalker
 */

using namespace std;
#include "Salary.h"
#include <iostream>

int main(void) {
	Salary salary(5500, 500, 1000, 100, 100);
	cout << salary.getRealSalary() << endl;
	return 0;
}


