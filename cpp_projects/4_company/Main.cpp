#include <iostream>
#include <string>

#include "Company.h"


using namespace std;



/**
this function repeatedly asks the user for the actions that the user would like to do
	(with 'C', 'D', 'H', 'P' keywords valid) until the user enter invalid input
*/
void run_event(); // function prototype


int main()
{
	run_event(); // calls run_event free function

	return 0;
}


// run_event function implementation
void run_event()
{
	Company company; // create an company object

	char likeToDo = ' ';


	do // a do-while loop that does the action once before condition checking
	{
		cout << "What would you like to do?\n" << "C - Create Employee\n"
			<< "D - Display Current Directory\n" << "H - Set Hours\n"
			<< "P - Print Payroll\n" << "Quit (all other inputs)? ";

		cin >> likeToDo;

		if (likeToDo == 'C') // when user enter 'C'
		{
			company.create_employee(); // create a new employee
		}
		else if (likeToDo == 'D') // when user enter 'D'
		{
			company.print_directory(); // display the company's exisiting employees
		}
		else if (likeToDo == 'H') // when user enter 'H'
		{
			company.do_hours(); // set hours worked for hourly workers
		}
		else if (likeToDo == 'P') // when user enter 'P'
		{
			company.print_payroll(); // print payrolls each employee should recieve
		}
		else // when user enter all other invalid input
		{
			break; // quit and exit the loop
		}

		cout << '\n'; // generate a new line between each action done

	} while (likeToDo == 'C' || likeToDo == 'D' || likeToDo == 'H' || likeToDo == 'P');

}