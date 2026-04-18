#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

#include "Company.h"
#include "Employee.h"
#include "HourlyWorker.h"
#include "SalariedWorker.h"


using namespace std;


//Company class implementations
Company::Company() noexcept
{
	int numOfFiles = find_next_id() - 1; // call find_next_id function to know the number of existing files
	
	for (size_t i = 0; i < numOfFiles; ++i) // for all existing files
	{
		stringstream convertInt;
		convertInt << i; // read the id of the current file
		string EmpFileId = "employee" + convertInt.str() + ".txt"; // convert to specific file name

		ifstream openFile;
		openFile.open(EmpFileId);

		if (!openFile.is_open()) // when the file failed to opened
		{
			cout << "Failed to open!\n";
		}
		else // when the file is successfully opened
		{
			string employeeType = "";
			openFile >> employeeType; // read the first word from the file
			
			if (employeeType == "salaried") // when the first word is "salaried"
			{
				// generate a SalariedWorker employee with the ifstream input
				employees.push_back(make_shared<SalariedWorker>(openFile));
			}
			else if (employeeType == "hourly") // when the first word is "hourly"
			{
				// generate an HourlyWorker employee with the ifstream input
				employees.push_back(make_shared<HourlyWorker>(openFile));
			}
			else // when the first word from the file is neither "salaried" nor "hourly"
			{
				cout << "invalid employee type!\n";
			}
			
			openFile.close(); // close the file
		}
	}
}

void Company::print_directory() // user input 'D'
{
	size_t employeeCnt = employees.size(); // the number of employees in the company
	cout << "There are " << employeeCnt << " employees:\n";

	for (size_t i = 0; i < employeeCnt; ++i) // for all employees
	{
		employees.at(i)->print(); // calls print function to print their names, ids, and emails
	}
}

void Company::do_hours() // user input 'H'
{
	size_t employeeCnt = employees.size(); // the number of employees in the company

	for (size_t i = 0; i < employeeCnt; ++i) // for all employees
	{
		// a dynamic pointer to check if the current employee is an hourly worker
		auto tempEmployee = dynamic_pointer_cast<HourlyWorker>(employees.at(i));

		if (tempEmployee) // when the employee is an hourly worker
		{
			int workHours;
			cout << "How many hours did " << tempEmployee->get_name() << " work? ";
			cin >> workHours;

			tempEmployee->set_hours(workHours); // set the hours worked into its 'hours' variable
			tempEmployee->save(); // saves the new information
		}
		else // when the employee is not an hourly worker
		{
			continue; // continue checking the next employee
		}
	}
}

void Company::print_payroll() const // user input 'P'
{
	size_t employeeCnt = employees.size(); // the number of employees in the company

	for (size_t i = 0; i < employeeCnt; ++i) // for all employees
	{
		employees.at(i)->print_pay(); // calls print_pay function to print payrolls they recieved
	}
}

void Company::create_salaried() // user input 'S' after 'C'
{
	// prompts user for the name
	cout << "Enter name: ";
	string name = "";
	cin.ignore();
	getline(cin, name); // use getline to retrieve first and last name

	// prompts user for the email
	cout << "Enter email: ";
	string email = "";
	cin >> email;
	
	// prompts user for the salary
	cout << "Enter salary: $";
	double salary = 0;
	cin >> salary;

	// create a salaried worker with the name, email, and salary information
	SalariedWorker theEmployee(name, email, salary);
	theEmployee.save(); // saves the new information
	employees.push_back(make_shared<SalariedWorker>(theEmployee)); // stores into the vectors of all employees

}

void Company::create_hourly() // user input 'H' after 'C'
{
	// prompts user for the name
	cout << "Enter name: ";
	string name = "";
	cin.ignore();
	getline(cin, name); // use getline to retrieve first and last name

	// prompts user for the email
	cout << "Enter email: ";
	string email = "";
	cin >> email;

	// prompts user for the hourly rate
	cout << "Enter hourly rate: $";
	double hourlyRate = 0;
	cin >> hourlyRate;

	// create an hourly worker with the name, email, and hourly rate information
	HourlyWorker theEmployee(name, email, hourlyRate);
	theEmployee.save(); // saves the new information
	employees.push_back(make_shared<HourlyWorker>(theEmployee)); // stores into the vectors of all employees
}

void Company::create_employee() // user input 'C'
{
	// prompts the user for the type of employee to be created
	cout << "What type of employee?\n" << "S - Salaried\n" << "H - Hourly\n"
		<< "Abort (all other inputs)? ";

	char empType = ' ';
	cin >> empType;

	if (empType == 'S') // user input 'S'
	{
		create_salaried(); // create a salaried worker by calling create_salaried function
	}
	else if (empType == 'H') // user input 'H'
	{
		create_hourly(); // create an hourly worker by calling create_hourly function
	}
	else // when the user input is neither 'S' nor 'H'
	{
		cout << "creation aborted\n"; // aborting the creation
	}
}




//Employee class implementations
int Employee::next_id = find_next_id(); // set the static member variable next_id using find_next_id function

Employee::Employee(string _name, string _email)
	:name(_name), email(_email)
{
	id = find_next_id() - 1; // using find_next_id function (decrease by one) to initialize the id
	employeeType = ""; // initialize the employeeType to be empty
}

Employee::Employee(ifstream& _file)
{
	//reads name, email, and id from the file stream
	_file.ignore();
	getline(_file, name, '\t');
	_file >> email >> id;

	employeeType = ""; // initialize the employeeType to be empty
}

void Employee::print()
{
	// prints the name, id, and email of the employee
	cout << name << '\t' << id << '\t' << email << '\n';
}

void Employee::write_data(std::string _name, std::string _email, int _id) // can be overridden
{
	name = _name;
	email = _email;
	id = _id;

	//create the employee file name using its id
	stringstream convertInt;
	convertInt << id;
	string EmpFileId = "employee" + convertInt.str() + ".txt"; // convert into the file name

	ofstream createFile;
	createFile.open(EmpFileId);

	if (!createFile.is_open()) // when the file failed to opened
	{
		cout << "Failed to open!\n";
	}
	else // when the file is successfully opened
	{
		// write employeeType, name, email, and id into the file
		createFile << employeeType << '\t' << name << '\t' << email << '\t' << id;
		createFile.close();
	}
}

//free function
int find_next_id()
{
	int numOfFiles = 0; // initialize the number of files to be 0
	bool exist = true; // initialize the existing of files to be true

	do // using do-while loop to first open the file employee0.txt before condition checking
	{
		stringstream convertInt;
		convertInt << numOfFiles; // read the current number of files
		string EmpFileId = "employee" + convertInt.str() + ".txt"; // convert into the name of the file

		ifstream testFile;
		testFile.open(EmpFileId);

		if (testFile.is_open()) // when the file is successfully opened
		{
			numOfFiles++; // increase the number of files by one
			testFile.close(); // close the current file
		}
		else // when the file failed to opened
		{
			exist = false; // the file with the id does not exist 
		}

	} while (exist); // continue checking the next file if the current file exists

	return numOfFiles + 1; // the next id is the current number of files increased by one
}




//HourlyWorker class implementations
HourlyWorker::HourlyWorker(string _name, string _email, double _hourlyRate)
	: Employee(_name, _email), rate(_hourlyRate)
{
	hours = 0; // initialize the hours worked to be 0
}

HourlyWorker::HourlyWorker(ifstream& _file)
	: Employee(_file) // invoke the base class first
{
	_file >> hours >> rate; // continue reading the hours worked and the hourly rate from the file
}

void HourlyWorker::set_hours(int _hours)
{
	hours = _hours; // set the hours variables to be the _hours input
}

void HourlyWorker::write_data(std::string _name, std::string _email, int _id)
{
	name = _name;
	email = _email;
	id = _id;

	// create the employee file name using id
	stringstream convertInt;
	convertInt << id;
	string EmpFileId = "employee" + convertInt.str() + ".txt"; // convert into a file name using the id

	ofstream createFile;
	createFile.open(EmpFileId);

	if (!createFile.is_open()) // when the file failed to open
	{
		cout << "Failed to open!\n";
	}
	else // when the file is successfully opened
	{
		// writes all the information into the file
		createFile << "hourly\t" << name << '\t' << email << '\t' << id
			<< '\t' << hours << '\t' << rate;
		createFile.close(); // close the file
	}
}

void HourlyWorker::print_pay() const
{
	// prints the payroll the hourly worker should recieve by multiplying hours and rate
	cout << name << " recieves $" << hours * rate << '\n';
}

void HourlyWorker::save() const
{
	// update the employee file name using id
	stringstream convertInt;
	convertInt << id;
	string EmpFileId = "employee" + convertInt.str() + ".txt"; // convert into a file name using the id

	ofstream updateFile;
	updateFile.open(EmpFileId, ofstream::trunc); // open the file and delete all the content

	if (!updateFile.is_open()) // when the file failed to open
	{
		cout << "Failed to open!\n";
	}
	else // when the file is successfully opened
	{
		// updates all the information into the file
		updateFile << "hourly\t" << name << '\t' << email << '\t' << id
			<< '\t' << hours << '\t' << rate;
		updateFile.close(); // close the file
	}
}

string HourlyWorker::get_name() const // accessor
{
	return name; // return name member variable
}




//SalariedWorker class implementations
SalariedWorker::SalariedWorker(string _name, string _email, double _salary)
	: Employee(_name, _email), salary(_salary)
{
	/*empty*/
}

SalariedWorker::SalariedWorker(ifstream& _file) /*accept input file stream*/
	: Employee(_file)
{
	_file >> salary; // continue reading the salary from the file
}

void SalariedWorker::write_data(std::string _name, std::string _email, int _id)
{
	name = _name;
	email = _email;
	id = _id;

	// create the employee file name using id
	stringstream convertInt;
	convertInt << id;
	string EmpFileId = "employee" + convertInt.str() + ".txt"; // convert into a file name using the id

	ofstream createFile;
	createFile.open(EmpFileId);

	if (!createFile.is_open()) // when the file failed to open
	{
		cout << "Failed to open!\n";
	}
	else // when the file is successfully opened
	{
		// writes all the information into the file
		createFile << "salaried\t" << name << '\t' << email << '\t' << id
			<< '\t' << salary;
		createFile.close(); // close the file
	}
}

void SalariedWorker::print_pay() const
{
	// prints the payroll the hourly worker should recieve by using the member variable salary
	cout << name << " recieves $" << salary << '\n';
}
void SalariedWorker::save() const
{
	// update the employee file name using id
	stringstream convertInt;
	convertInt << id;
	string EmpFileId = "employee" + convertInt.str() + ".txt"; // convert into a file name using the id

	ofstream updateFile;
	updateFile.open(EmpFileId, ofstream::trunc); // open the file and delete all the content

	if (!updateFile.is_open()) // when the file failed to open
	{
		cout << "Failed to open!\n";
	}
	else // when the file is successfully opened
	{
		// updates all the information into the file
		updateFile << "salaried\t" << name << '\t' << email << '\t' << id
			<< '\t' << salary;
		updateFile.close(); // close the file
	}
}