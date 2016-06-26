/*
 * Salary.h
 *
 *  Created on: 2015年10月13日
 *      Author: skywalker
 */

#ifndef SALARY_H_
#define SALARY_H_

class Salary {

private:
	//基本工资
	double wage;
	//津贴
	double subsidy;
	//房租
	double rent;
	//水费
	double waterFee;
	//电费
	double elecFee;

public:
	Salary();
	Salary(double wage, double subsidy, double rent, double waterFee, double elecFee);

	//计算实发工资
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
