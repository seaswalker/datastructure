/*
 * client.cpp
 * ²âÊÔ
 *
 *  Created on: 2015Äê10ÔÂ13ÈÕ
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


