/*
 * Employee.h
 *
 *  Created on: 2015年10月9日
 *      Author: skywalker
 */

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

using namespace std;
#include <string>
#include "util.h"

class Employee {

private:
	string id;
	string name;
	float baseSaraly;
	//加班工资
	float extraSalary;
	//奖金
	float reward;
	//扣除
	float deduct;
	//实发工资
	float realSalary;

public:
	Employee();

	//toString
	string toString();

	/**
	 * 根据字符串解析成为Employee对象
	 * @param isCalRealSalary 如果为true表示需要根据其它工资计算出实际工资，如果为false，那么是从文件读取
	 * 此时结果已经计算出来了，只需要设置就行了
	 */
	static Employee parseEmployee(string data, bool isCalRealSalary);

	float getBaseSaraly() const {
		return baseSaraly;
	}

	void setBaseSaraly(float baseSaraly) {
		this->baseSaraly = baseSaraly;
	}

	float getDeduct() const {
		return deduct;
	}

	void setDeduct(float deduct) {
		this->deduct = deduct;
	}

	float getExtraSalary() const {
		return extraSalary;
	}

	void setExtraSalary(float extraSalary) {
		this->extraSalary = extraSalary;
	}

	const string& getId() const {
		return id;
	}

	void setId(const string& id) {
		this->id = id;
	}

	const string& getName() const {
		return name;
	}

	void setName(const string& name) {
		this->name = name;
	}

	float getRealSalary() const {
		return realSalary;
	}

	void setRealSalary() {
		//由其它薪水计算而来
		this->realSalary = baseSaraly + extraSalary + reward - deduct;
	}

	void setRealSalary(float r) {
		//由其它薪水计算而来
		this->realSalary = r;
	}

	float getReward() const {
		return reward;
	}

	void setReward(float reward) {
		this->reward = reward;
	}

};

#endif /* EMPLOYEE_H_ */
