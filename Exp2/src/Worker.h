/*
 * Worker.h
 *
 *	工人类
 *  Created on: 2015年10月13日
 *      Author: skywalker
 */

#ifndef WORKER_H_
#define WORKER_H_

#include "Salary.h"
using namespace std;

class Worker {

private:
	string name;
	int age;
	string dept;
	Salary salary;
public:
	Worker();

	//人数统计
	static int nums = 0;

	int getAge() const {
		return age;
	}

	void setAge(int age) {
		this->age = age;
	}

	const string& getDept() const {
		return dept;
	}

	void setDept(const string& dept) {
		this->dept = dept;
	}

	const string& getName() const {
		return name;
	}

	void setName(const string& name) {
		this->name = name;
	}

	const Salary& getSalary() const {
		return salary;
	}

	void setSalary(const Salary& salary) {
		this->salary = salary;
	}
};

#endif /* WORKER_H_ */
