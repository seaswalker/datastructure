/*
 * Employee.h
 *
 *  Created on: 2015��10��9��
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
	//�Ӱ๤��
	float extraSalary;
	//����
	float reward;
	//�۳�
	float deduct;
	//ʵ������
	float realSalary;

public:
	Employee();

	//toString
	string toString();

	/**
	 * �����ַ���������ΪEmployee����
	 * @param isCalRealSalary ���Ϊtrue��ʾ��Ҫ�����������ʼ����ʵ�ʹ��ʣ����Ϊfalse����ô�Ǵ��ļ���ȡ
	 * ��ʱ����Ѿ���������ˣ�ֻ��Ҫ���þ�����
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
		//������нˮ�������
		this->realSalary = baseSaraly + extraSalary + reward - deduct;
	}

	void setRealSalary(float r) {
		//������нˮ�������
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
