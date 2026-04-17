#include <iostream>

#include "MagicSquare.h"


using namespace std;


int main()
{
	cout << "Enter a square size: ";
	int squareSize = 0;
	cin >> squareSize;

	MagicSquare magicSquare(squareSize); // create an MagicSquare object with the input square size n

	cout << "Enter square format: \n";
	cin >> magicSquare; // set the squares as required format to be analyzed


	magicSquare.solveSquare(0); // find all solutions, initial index is 0

	// call getCount function to get and print the number of solutions found
	cout << "Solving complete!\n"
		<< "There were " << magicSquare.getCount() << " solutions!\n";
	

	return 0;
}