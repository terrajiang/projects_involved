#ifndef _SALARIEDWORKER_H_
#define _SALARIEDWORKER_H_

#include <string>
#include "Employee.h"


/**
@class SalariedWorker is a derived class from Employee class that stores the salary
	of an salaried employee, and operate the functions that require the variable
*/
class SalariedWorker final : public Employee
{
public:

	SalariedWorker(std::string _name, std::string _email, double _salary); // constructor that takes name, email, and salary arguments
	SalariedWorker(std::ifstream& _file); // constructor that takes an input file stream argument


	/**
	this function writes name, email, and id into a file
		with the required format (overrides the virtual function)
	@param _name is the input name that should be written into the file
	@param _email is the input email that should be written into the file
	@param _id is the input id that should be written into the file
	*/
	void write_data(std::string _name, std::string _email, int _id) override;

	/**
	this function overrides the pure virtual 'print_pay' function from the base class Employee,
		and it prints the amount of payroll the salaried worker should recieve
	*/
	void print_pay() const override;

	/**
	this function overrides the pure virtual 'save' function from the base class Employee,
		and saves new information of an SalariedWorker object into a file by invoking 'write_data' function
	*/
	void save() const override;

private:

	double salary;

};


#endif