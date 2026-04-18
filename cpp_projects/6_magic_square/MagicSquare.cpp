#include <iostream>
#include <vector>
#include <unordered_set>

#include "MagicSquare.h"



using namespace std;


MagicSquare::MagicSquare(size_t _sqrSize)
	: sqrSize(_sqrSize) // set square size as the user input n
{
	for (size_t i = 0; i < sqrSize; ++i)
	{
		vector<int> rows; // make an 1D vector to set each row
		for (size_t j = 0; j < sqrSize; ++j)
		{
			rows.push_back(0); // stores 0 in a row initially, indicating no values yet
		}
		square.push_back(rows); // add each row set into out 2D vector square
	}

	used = {}; // used no number yet initially

	slots = sqrSize * sqrSize; // number of slots to go through (n^2)

	count = 0; // initialize the number of solution to be 0
}



bool MagicSquare::empty(size_t row, size_t col) const
{
	return (square[row][col] == 0); // if the position is empty (is 0), return true
}


bool MagicSquare::taken(int i) const
{
	return (used.count(i) != 0); // if the integer is in the unordered set, return true
}


bool MagicSquare::checkRow()
{
	// 1. the sum of each filled row = S = n(n^2+1)/2 
	for (size_t i = 0; i < sqrSize; ++i)
	{
		int sum = 0;
		bool noZero = true; // to test if a row has no zero (i.e. is completely filled with numbers)

		for (size_t j = 0; j < sqrSize; ++j)
		{
			if (square[i][j] == 0) // when the row has 0, is not completely filled yet
			{
				noZero = false; // has 0
			}
			
			sum += square[i][j]; // summing each row filled
		}
		
		if (noZero && sum != (sqrSize * (sqrSize * sqrSize + 1) / 2))
		{
			return false; // false when a comletely filled row does not equal to S
		}
	}


	// 2. each partially filled col <= S = n(n^2+1)/2 (does not exceed)
	for (size_t j = 0; j < sqrSize; ++j)
	{
		int sum = 0;
		for (size_t i = 0; i < sqrSize; ++i)
		{
			sum += square[i][j]; // summing each column partially filled
		}

		if (sum > (sqrSize * (sqrSize * sqrSize + 1) / 2))
		{
			return false; // false when the partially filled column is greater than S
		}
	}


	return true; // true if after 1 & 2 both chekced and not failed
}


bool MagicSquare::checkValid()
{
	// 1. the sum of each column = S = n(n^2+1)/2 
	for (size_t j = 0; j < sqrSize; ++j)
	{
		int sum = 0;
		for (size_t i = 0; i < sqrSize; ++i)
		{
			sum += square[i][j]; // summing each column completely filled
		}

		if (sum != (sqrSize * (sqrSize * sqrSize + 1) / 2))
		{
			return false; // false when the completely filled column does not equal to S
		}
	}


	// 2-1. check top-left to bottom-right main diagonal = S = n(n^2+1)/2 
	int sum1 = 0;
	for (size_t i = 0; i < sqrSize; ++i)
	{
		sum1 += square[i][i]; // summing the top-left to bottom-right main diagonal
	}

	if (sum1 != (sqrSize * (sqrSize * sqrSize + 1) / 2))
	{
		return false; // false when the sum of this main diagonal does not equal to S
	}

	// 2-2. check top-right to bottom-left main diagonal = S = n(n^2+1)/2 
	int sum2 = 0;
	for (size_t i = 0; i < sqrSize; ++i)
	{
		sum2 += square[i][sqrSize - i - 1]; // summing the top-right to bottom-left main diagonal
	}

	if (sum2 != (sqrSize * (sqrSize * sqrSize + 1) / 2))
	{
		return false; // false when the sum of this main diagonal does not equal to S
	}


	return true; // true if after 1 & 2 both chekced and not failed
}




// helper functions
int MagicSquare::getCount() const
{
	return count; // return the number of solutions found
}


void MagicSquare::printSquare() const
{
	for (size_t i = 0; i < sqrSize; ++i) // each row
	{
		for (size_t j = 0; j < sqrSize; ++j) // each column
		{
			if (j == sqrSize - 1) // when it's the last value in a row
			{
				cout << square[i][j] << '\n'; // seperate each row by new lines
			}
			else // when not the last value in a row
			{
				cout << square[i][j] << " "; // seperate each value by spaces
			}
		}
		
		if (i == square.size() - 1) // when it's the last row for the square
		{
			cout << '\n'; // seperate each square printed by a new line
		}
	}
}