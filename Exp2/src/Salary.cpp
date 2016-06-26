/*
 * Salary.cpp
 *
 *  Created on: 2015Äê10ÔÂ13ÈÕ
 *      Author: skywalker
 */

#include "Salary.h"

Salary::Salary() {
	this->elecFee = 0;
	this->rent = 0;
	this->subsidy = 0;
	this->wage = 0;
	this->waterFee = 0;
}

Salary::Salary(double wage, double subsidy, double rent, double waterFee, double elecFee) {
	this->elecFee = elecFee;
	this->rent = rent;
	this->subsidy = subsidy;
	this->wage = wage;
	this->waterFee = waterFee;
}

double Salary::getRealSalary() {
	return this->wage + this->subsidy - this->rent - this->elecFee - this->waterFee;
}
