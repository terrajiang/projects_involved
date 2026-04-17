#ifndef _MAGICSQUARE_H_
#define _MAGICSQUARE_H_

#include <vector>
#include <unordered_set>



/**
@class MagicSquare creates a magic square object with user input square size, 
	it stores the information of a magic square and than solves for the number of solutions from the information given
*/
class MagicSquare
{
	
	/**
	this operator>> reads a	2D vector input (seperated by spaces and newlines) into istream 
		with '*' char as an invalid input (will not be read and keep the slot 0 as initialized)
	@param in is the istream input reference
	@param magSqr is the magic square object to be specified (into each row and column of the square)
	@return the istream in that has specified slots information
	*/
	friend std::istream& operator>>(std::istream& in, MagicSquare& magSqr) // non-member function
	{
		for (size_t i = 0; i < magSqr.sqrSize; ++i) // each row
		{
			for (size_t j = 0; j < magSqr.sqrSize; ++j) // each column
			{
				in >> magSqr.square[i][j]; // read each input number

				if (in.fail()) // when input is '*' (non-int type)
				{
					in.clear(); // clear the fail state of istream
					in.ignore(); // ignore the invalid input to continue reading
				}
			}
		}

		return in; // return the istream
	}


	/**
	this operator<< print/display the magic square with ostream reference
	@param out is the ostream input reference
	@param square is the 2D vector that will be displayed
	@return the ostream out to display (in n by n format)
	*/
	friend std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<int>>& square) // non-member function
	{
		for (size_t i = 0; i < square.size(); ++i) // each row
		{
			for (size_t j = 0; j < square[i].size(); ++j) // each column
			{
				if (j == square[i].size() - 1) // when it's the last value in a row
				{
					out << square[i][j]; // seperate each row by new lines
				}
				else // when not the last value in a row
				{
					out << square[i][j] << " "; // seperate each value by spaces
				}
			}

			if (i == square.size() - 1) // when it's the last row for the square
			{
				out << '\n'; // generate a new line after the square
			}
		}

		return out; // return the ostream
	}


public:

	MagicSquare(size_t sqrSize); // constructor taking a square size in int type


	/**
	this function tests if the given position in the square is empty (is 0)
	@param row is the row number in size_t type
	@param col is the column number in size_t type
	@return the boolean type of whether the position at the specific row and column is empty (is 0)
	*/
	bool empty(size_t row, size_t col) const;

	/**
	this function tests if the integer given has already been used in the square yet
	@param i is the integer to be tested
	@return the boolean type of whether the integer exists in the unordered_set used
	*/
	bool taken(int i) const;

	/**
	this function checks if the rows completely filled and the columns partially filled are valid, 
		the sum of each row should equal to S = n(n2+1)/2, and the potential columns filled should not exceed S = n(n2+1)/2
	@return the boolean type of whether the rows and columns filled are valid
	*/
	bool checkRow();

	/**
	this function checks if the complete magic square filled is valid, 
		all columns completely filled and the two main diagonals should equal to S = n(n2+1)/2
	@return the boolean type of whether the complete magic square is valid
	*/
	bool checkValid();


	
	/**
	this function is a getter function that allows users to get access to the total number of solutions of the magic square
	@return the member variable count in int type
	*/
	int getCount() const; // accessor

	/**
	this function prints the magic square (square) in the required format (n by n)
	*/
	void printSquare() const;



	/**
	this recursion function tries all possible solutions of the magic square as specified,
		it prints the complete square and increase the member variable count by one if any solution is found
	@param index is the index of the square for the recursive process in size_t type, 
		the index of [0][0] position of the square is expected to be 1 (the first slot), 
		and the index of [n-1][n-1] position of the square is expected to be n^2 (the last slot)
	*/
	constexpr void solveSquare(size_t index)
	{
		if (index == 0) // before checking the first index, initial index is 0
		{
			for (size_t i = 0; i < sqrSize; ++i) // each row
			{
				for (size_t j = 0; j < sqrSize; ++j) // each column
				{
					if (!empty(i, j)) // when the position in the square has a value other than 0
					{
						used.insert(square[i][j]); // insert the values from the square into the set 'used'
					}
				}
			}
			solveSquare(index + 1); // push to index 1: start checking the first slot
		}
		else if (index == slots + 1) // when the square is full, after the last index was filled
		{
			if (checkValid()) // when the complete square is valid
			{
				// print the solution (the square) found
				printSquare();

				// increase the solution count by one
				count++;
			}
		}
		else // index in between the first and the last slot (1~9)
		{
			// try if the current slot is empty
			if (empty((index - 1) / sqrSize, (index - 1) % sqrSize)) // when empty
			{
				for (int i = 1; i <= sqrSize * sqrSize; ++i) // try every possible 'integer' (from 1 to n^2)
				{
					if (!taken(i)) // when the value has not yet used in the square
					{
						used.insert(i); // insert the number into 'used' set
						square[(index - 1) / sqrSize][(index - 1) % sqrSize] = i; // put the value into the square at the slot

						// check if a row is filled
						if (index % sqrSize == 0) // when a row is filled
						{
							if (checkRow()) // when the row filled is valid
							{
								solveSquare(index + 1); // continue checking the next slot
							}
							else // when the row filled is not valid
							{
								used.erase(i); // remove the value from 'used' set after use
								square[(index - 1) / sqrSize][(index - 1) % sqrSize] = 0; // remove from the square after use
							}
						}
						else // when a row has not yet filled
						{
							solveSquare(index + 1); // continue to next slot
						}

						used.erase(i); // remove from 'used' set after use
						square[(index - 1) / sqrSize][(index - 1) % sqrSize] = 0; // remove from the square after use
					}
				}
			}
			else // when not empty
			{
				// check if a row is filled
				if (index % sqrSize == 0) // when a row is filled
				{
					if (checkRow()) // when the row filled is valid
					{
						solveSquare(index + 1); // continue checking the next slot
					}
				}
				else // when a row has not yet filled
				{
					solveSquare(index + 1); // skip the current slot, continue to next slot
				}
			}
		}
	}


private:

	const size_t sqrSize;
	std::vector<std::vector<int>> square;
	std::unordered_set<int> used;
	size_t slots;
	int count;
	
};


#endif