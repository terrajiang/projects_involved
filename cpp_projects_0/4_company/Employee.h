#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

#include <string>


/**
@class Employee is a base class that stores general information (name, email, and id) for an employee, 
	and operate some memeber functions with those general informations
*/
class Employee
{
public:

	Employee(std::string _name, std::string _email); // constructor that takes name and email arguments
	Employee(std::ifstream& _file); // constructor that takes an input file stream argument

	virtual ~Employee() = default; // virtual destructor that set to default
	

	/**
	this function prints the name, id, and email for an employee
	*/
	void print();


	/**
	this vritual function writes name, email, and id into a file with the required format (can be overridden)
	@param _name is the input name that should be written into the file
	@param _email is the input email that should be written into the file
	@param _id is the input id that should be written into the file
	*/
	virtual void write_data(std::string _name, std::string _email, int _id);

	/**
	this function is a pure virtual function that forces the 'print_pay' function from
		derived classes (SalariedWorker and HourlyWorker) to implement
	*/
	virtual void print_pay() const = 0;

	/**
	this function is a pure virtual function that forces the 'save' function from
		derived classes (SalariedWorker and HourlyWorker) to implement
	*/
	virtual void save() const = 0;

protected:

	std::string name;
	std::string email;
	int id;
	std::string employeeType;

private:

	static int next_id;

};


/**
this function is a free function that helps for setting the static member variable next_id, 
	it will read through all the existing files until it fails to open
@return the number of existing files plus one in int type
*/
int find_next_id();


#endif