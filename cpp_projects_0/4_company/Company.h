#ifndef _COMPANY_H_
#define _COMPANY_H_

#include <vector>
#include <memory>
#include "Employee.h"


/**
@class Company stores all employees (both salaried and hourly) into a vector, and does 
	all the actions that the users want to do (with keywords 'D', 'H', 'P', 'C', ... etc.)
*/
class Company
{
public:

	Company() noexcept; // default constructor
	

	/**
	this function displays how many employees there are in the company, 
		and calls 'print' function for all employees to print their names, ids, and emails
	*/
	void print_directory(); // 'D'
	
	/**
	this function asks users for the hours worked by every hourly worker
		by alling 'set_hours' function from HourlyWorker class
	*/
	void do_hours(); // 'H'

	/**
	this function prints the payroll that every employee should recieve 
		by calling 'print_pay' function for all employees
	*/
	void print_payroll() const; // 'P'


	/**
	this function creates a salaried worker after prompting users for the name, email, and salary, 
		and this salaried worker will be stored into the vector of employees in this company
	*/
	void create_salaried(); // 'S' (after 'C')

	/**
	this function creates an hourly worker after prompting users for the name, email, and hourly rate,
		and this hourly worker will be stored into the vector of employees in this company
	*/
	void create_hourly(); // 'H' (after 'C')

	/**
	this function prompts the users for the type of employee they want to create, 
		and calls 'create_salaried' or 'create_hourly' member functions respectively 
		according to the users' input (with 'S', 'H', and all other inputs aborted)
	*/
	void create_employee(); // 'C'

private:

	std::vector<std::shared_ptr<Employee>> employees;

};


#endif