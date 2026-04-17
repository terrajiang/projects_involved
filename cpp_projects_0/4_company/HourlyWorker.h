#ifndef _HOURLYWORKER_H_
#define _HOURLYWORKER_H_

#include <string>
#include "Employee.h"


/**
@class HourlyWorker is a derived class from Employee class that stores the hours worked and hourly rate
	of an hourly employee, and operate the functions that require those variables
*/
class HourlyWorker final : public Employee
{
public:

	HourlyWorker(std::string _name, std::string _email, double _hourlyRate); // constructor that takes name, email, and hourly rate arguments
	HourlyWorker(std::ifstream& _file); // constructor that takes an input file stream argument


	/**
	this function sets the 'hours' variable by using the hours input argument
	@param _hours is the input hours the hourly worker worked
	*/
	void set_hours(int _hours);


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
		and it prints the amount of payroll the hourly worker should recieve
	*/
	void print_pay() const override;

	/**
	this function overrides the pure virtual 'save' function from the base class Employee, 
		and saves new information of an HourlyWorker object into a file by invoking 'write_data' function
	*/
	void save() const override; // invokes write_data


	/**
	this function allows the users to get access to the name of the current hourly worker
	@return name of the hourly worker in string type
	*/
	std::string get_name() const; // accessor

private:

	int hours;
	double rate;

};


#endif