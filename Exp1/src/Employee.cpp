/*
 * Employee.cpp
 *
 *  Created on: 2015年10月9日
 *      Author: skywalker
 */

using namespace std;
#include "Employee.h"
#include <iostream>

Employee::Employee() {
	this->baseSaraly = 0;
	this->extraSalary = 0;
	this->deduct = 0;
	this->id = "";
	this->name = "";
	this->realSalary = 0;
	this->reward = 0;
}

string Employee::toString() {
	return this->id + " " + this->name + " " + float2String(this->baseSaraly) +
			" " + float2String(this->extraSalary) + " " + float2String(this->deduct) + " " +
			float2String(this->reward) + " " + float2String(this->realSalary);
}

Employee Employee::parseEmployee(string data, bool isCalRealSalary) {
	vector<string> elements = split(data, " ");
	Employee employee;
	employee.setId(elements[0]);
	employee.setName(elements[1]);
	employee.setBaseSaraly(string2Float(elements[2]));
	employee.setExtraSalary(string2Float(elements[3]));
	employee.setReward(string2Float(elements[4]));
	employee.setDeduct(string2Float(elements[5]));
	if (isCalRealSalary) {
		//计算实际工资
		employee.setRealSalary();
	} else {
		employee.setRealSalary(string2Float(elements[6]));
	}
	return employee;
}
