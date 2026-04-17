#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

#include "Complex.h"

using namespace std;


Complex::Complex(const string _phrase) // member function
{
	if (_phrase == "" || !validString(_phrase)) // invalid if it's an empty string or non-acceptable string
	{
		throw logic_error("bad input string: " + _phrase); // throw a logic error message using the invalid string
	}

	stringstream phrase(_phrase); // using stringstream to store the string and check the characters

	double realPart = 0; // initialize the cumulative coefficient of real term as 0
	double imagPart = 0; // initialize the cumulative coefficient of imaginary term as 0
	double tempNum = 0; // initialize the temporary number to be read to be 0
	bool positive = true; // initialize the positiveness to be true becasue an unsigned first number should be positive
	char tempChar = 'o'; // initialize the temporary character to be read to be 'o'
	bool coeff = false; // design as a switch-like variable, when no coefficient was read before 'i', we'll set the coefficient to be +1/-1
	

	while (!phrase.eof())
	{
		if (phrase.peek() == '+') // when the next char is '+'
		{
			phrase >> tempChar;	// read the '+'
			positive = true;
			coeff = false; // a sign was read, but not yet read a number
		}
		else if (phrase.peek() == '-') // when the next char is '-'
		{
			phrase >> tempChar; // read the '-'
			positive = false;
			coeff = false; // a sign was read, but not yet read a number
		}
		else if (phrase.peek() == 'i') // when the next char is 'i'
		{
			phrase >> tempChar; // read the 'i'

			if (positive) // if it's a positive number (since read a '+' before)
			{
				if (coeff) // when there is a number (the coefficient) read after the '+' sign
				{
					imagPart += tempNum; // add the number to the imaginary term
					realPart -= tempNum; // subtract the number from the real term that has been temporarily added to real before reading 'i'
				}
				else // when there is no number detected after reading the '+' sign: the coefficient is 1
				{
					++imagPart; // add one to the imaginary term because there's no number read after reading the '+' sign: +i
				}
			}
			else // if it's a negative number (since read a '-' before)
			{
				if (coeff) // when there is a number (the coefficient) read after the '-' sign
				{
					imagPart -= tempNum; // subtract the number from the imaginary term
					realPart += tempNum; // add the number back to the real term that has been temporarily subtracted from real before reading 'i'
				}
				else // when there is no number detected after reading the '-' sign: the coefficient is -1
				{
					--imagPart; // subtract one from the imaginary term because there's no number read after reading the '-' sign: -i
				}
			}
		}
		else // when the next char is either '1', '2', .... , or '9'
		{
			if (phrase >> tempNum) // read the number to the double tempNum
			{
				coeff = true; // when there is a number detected

				if (positive) // if it's a positive number 
				{
					realPart += tempNum; // add the number to the real term
				}
				else // if it's a negative number
				{
					realPart -= tempNum; // subtract the number from the real term
				}
			}
		}
	}

	real = realPart; // set the real variable using the cumulative realPart obtained from the string
	imaginary = imagPart; // set the imaginary variable using the cumulative imagPart obtained from the string
}


double& Complex::operator[](string _type) // member function
{
	if (_type == "real") // when the input is "real"
	{
		return real; // return the real variable
	}
	else if (_type == "imag") // when the input is "imag"
	{
		return imaginary; // return the imaginary variable
	}
	else // when the input is neither "real" nor "imag"
	{
		throw out_of_range("invalid index: " + _type); // throw an out of range error with the invalid input string
	}
}


double Complex::operator[](const string _type) const // member function
{
	if (_type == "real") // when the input is "real"
	{
		return real; // return the real variable
	}
	else if (_type == "imag") // when the input is "imag"
	{
		return imaginary; // return the imaginary variable
	}
	else // when the input is neither "real" nor "imag"
	{
		throw out_of_range("invalid index: " + _type); // throw an out of range error with the invalid input string
	}
}


Complex::operator std::string() const // member function
{
	stringstream theReal;
	theReal << real; // put real into the string stream
	stringstream theImag;
	theImag << imaginary; // put imaginary into the string stream

	string convertStr = ""; // to store the string to be returned

	bool realZero = (real == 0) ? true : false; // true if real is zero
	bool imagZero = (imaginary == 0) ? true : false; // true if imaginary is zero
	bool imagPos = (imaginary > 0) ? true : false; // true if imaginary is positive
	bool isOne = (imaginary == 1 || imaginary == -1) ? true : false; // to check if the coefficient of i term is 1/-1

	if (realZero) // when the real term is zero
	{
		if (imagZero) // when the imaginary term is also zero
		{
			convertStr = "0"; // a zero complex number: 0
		}
		else if (imagPos) // when the imaginary term is positive
		{
			// the coefficient of imaginary term will not display when it's 1, otherwise display the coefficient
			convertStr = (isOne) ? "i" : (theImag.str() + "i");
		}
		else // when the imaginary term is negative
		{
			// the coefficient of imaginary term will display as '-' when it's -1, otherwise display the coefficient
			convertStr = (isOne) ? "-i" : (theImag.str() + "i");
		}
	}
	else // when the real term is not zero
	{
		if (imagZero) // when the imaginary term is zero
		{
			convertStr = theReal.str(); // the string is the real part itself
		}
		else if (imagPos) // when the imaginary term is positive
		{
			// '+' will display when the imaginary term is positive, 1 will not display as a coefficient
			convertStr = (isOne) ? (theReal.str() + "+i") : (theReal.str() + "+" + theImag.str() + "i"); // 3+i / 3+6i
		}
		else // when the imaginary term is negative
		{
			// make it display '-i' when the coefficient of the imaginary term is -1
			convertStr = (isOne) ? (theReal.str() + "-i") : (theReal.str() + theImag.str() + "i"); // 3-i / 3-6i
		}
	}

	return convertStr; // return the string converted from the Complex data (real and imaginary)
}


bool operator<(const Complex& left, const Complex& right) // non-member function
{
	if (left["real"] < right["real"])
	{
		// when the real from the left is less than the real from the right
		return true;
	}
	else if (left["real"] == right["real"] && left["imag"] < right["imag"])
	{
		// when the reals are the same, and the imaginary from the left is less than the imaginary from the right
		return true;
	}
	else // when the right complex is greater than or equal to the left complex
	{
		return false;
	}
}


bool operator==(const Complex& left, const Complex& right) // non-member function
{
	return !(left < right || right < left); // true if neither the left nor the right is less than the other
}


bool operator>(const Complex& left, const Complex& right) // non-member function
{
	return (right < left); // true if the right complex is less than the left
}


bool operator<=(const Complex& left, const Complex& right) // non-member function
{
	return (left < right || left == right); // true if the left complex is less than or equal to the right complex
}


bool operator>=(const Complex& left, const Complex& right) // non-member function
{
	return (left > right || left == right); // true of the left complex is greater than or equal to the right complex
}


bool operator!=(const Complex& left, const Complex& right) // non-member function
{
	return !(left == right); // true if the left complex is NOT equal to the right complex
}


bool validChar(char _ch) // non-member function
{
	// a valid character should be either from '1' to '9', '+', '-', or 'i'
	if (_ch == '0' || _ch == '1' || _ch == '2' || _ch == '3' || _ch == '4' || _ch == '5' || _ch == '.'
		|| _ch == '6' || _ch == '7' || _ch == '8' || _ch == '9' || _ch == '+' || _ch == '-' || _ch == 'i')
	{
		return true; 
	}
	else
	{
		return false; // false if the char is not valid
	}
}


bool validString(const string _str) // non-member function
{
	bool validStr = true; // initialize the string as valid
	
	for (size_t i = 0; i < _str.size(); ++i)
	{
		if (!validChar(_str[i])) // check if a char in the string is valid using validChar function
		{
			validStr = false; // invalid string if a single char is invalid
		}
		else
		{
			continue; // continue checking the next character
		}
	}
	
	return validStr; // true if ALL characters in a string are valid, otherwise false
}