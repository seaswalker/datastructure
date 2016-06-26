/*
 * Salary.h
 *
 *  Created on: 2015��10��13��
 *      Author: skywalker
 */

#ifndef SALARY_H_
#define SALARY_H_

class Salary {

private:
	//��������
	double wage;
	//����
	double subsidy;
	//����
	double rent;
	//ˮ��
	double waterFee;
	//���
	double elecFee;

public:
	Salary();
	Salary(double wage, double subsidy, double rent, double waterFee, double elecFee);

	//����ʵ������
	double getRealSalary();

	double getElecFee() const {
		return elecFee;
	}

	void setElecFee(double elecFee) {
		this->elecFee = elecFee;
	}

	double getRent() const {
		return rent;
	}

	void setRent(double rent) {
		this->rent = rent;
	}

	double getSubsidy() const {
		return subsidy;
	}

	void setSubsidy(double subsidy) {
		this->subsidy = subsidy;
	}

	double getWage() const {
		return wage;
	}

	void setWage(double wage) {
		this->wage = wage;
	}

	double getWaterFee() const {
		return waterFee;
	}

	void setWaterFee(double waterFee) {
		this->waterFee = waterFee;
	}
};

#endif /* SALARY_H_ */
