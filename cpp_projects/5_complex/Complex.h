#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <iostream>


/**
@class Complex creates complex number objects with real and imaginary terms (in double type),
	and defines all the operations that could be used by the complex numbers
*/
class Complex
{
	/**
	this operator<< print/display the complex number with ostream reference
	@param _out is the ostream input reference
	@param _compNum is the Complex object to be printed/displayed
	@return the ostream _out to display (in the form of a+bi)
	*/
	friend std::ostream& operator<<(std::ostream& _out, const Complex& _compNum) // non-member function
	{
		_out << _compNum.operator std::string(); // call the conversion operator

		return _out;
	}

	/**
	this operator>> reads two doubles from a Complex obejct (seperated by a space) into istream
	@param _in is the istream input reference
	@param _compNum is the Complex object to be read through (provides real and imaginary)
	@return the istream _in that has information of real and imaginary
	*/
	friend std::istream& operator>>(std::istream& _in, Complex& _compNum) // non-member function
	{
		_in >> _compNum.real >> _compNum.imaginary;

		if (!_in) // if the stream fails to read
		{
			throw std::runtime_error("read error");
		}

		return _in;
	}

	/**
	this binary operator< compares two Complex numbers and check if the first argument is less than the second argument
	@param left is the complex number on the left-hand side
	@param right is the complex number on the right-hand side
	@return the boolean type of whether the left complex is less than the right complex
	*/
	friend bool operator<(const Complex& left, const Complex& right); // non-member function


public:

	constexpr Complex(double _real = 0, double _imaginary = 0) //constructor taking two doubles (with default arguments 0)
		:real(_real), imaginary(_imaginary)
	{
		/*empty*/
	}
	
	Complex(const std::string _phrase); //constructor taking a string

	

	/**
	this binary operator+= adds two complex numbers and change the left-hand side
	@param _compNum is the Complex number to be added
	@return the current Complex object that has been modified (added)
	*/
	constexpr Complex& operator+=(const Complex& _compNum) // member function
	{
		real += _compNum.real; // adding real to the current Complex
		imaginary += _compNum.imaginary; // adding imaginary to the current Complex

		return *this; // return the current Complex
	}

	/**
	this unary operator+ returns a copy of the complex number
	@return a copy of a Complex object having the same real and imaginary variables
	*/
	constexpr Complex operator+() const // member function
	{
		return Complex(real, imaginary); //return a copy of the current Complex
	}

	/**
	this unary operator++ returns the prefix increment of a complex number
	@return the current complex number having the real part increased by 1
	*/
	constexpr Complex& operator++() // member function
	{
		++real; // increment

		return *this; // return the current increased Complex object
	}

	/**
	this binary operator++ returns the postfix increment of a complex number
	@param unused is an int parameter for the compiler to find the postfix function
	@return a copy of the complex number before the real part being increased by 1
	*/
	constexpr Complex operator++(int unused) // member function
	{
		Complex copy(* this); // copy the current Complex object
		++real; // increment

		return copy; // return the non-increased copy
	}


	/**
	this binary operator-= subtracts two complex numbers and change the left-hand side
	@param _compNum is the Complex number to be subtracted
	@return the current Complex object that has been modified (subtracted)
	*/
	constexpr Complex& operator-=(const Complex& _compNum) // member function
	{
		real -= _compNum.real; // subtracting real from the current Complex
		imaginary -= _compNum.imaginary; // subtracting imaginary from the current Complex

		return *this; // return the current Complex
	}

	/**
	this unary operator- returns a copy of the complex number with negated real and imaginary terms
	@return a Complex object having the negated real and imaginary variables
	*/
	constexpr Complex operator-() const // member function
	{
		return Complex(-real, -imaginary); // make a new Complex with negated real and imaginary arguments
	}

	/**
	this unary operator-- returns the prefix decrement of a complex number
	@return the current complex number having the real part decreased by 1
	*/
	constexpr Complex& operator--() // member function
	{
		--real; // decrement

		return *this; // return the current decreased Complex object
	}

	/**
	this binary operator-- returns the postfix decrement of a complex number
	@param unused is an int parameter for the compiler to find the postfix function
	@return a copy of the complex number before the real part being decreased by 1
	*/
	constexpr Complex operator--(int unused) // member function
	{
		Complex copy(*this); // copy the current Complex object
		--real; // decrement

		return copy; // return the non-decreased copy
	}
	

	/**
	this binary operator*= multiplies two complex numbers and change the left-hand side
	@param _compNum is the Complex number to be multiplied
	@return the current Complex object that has been modified (multiplied)
	*/
	constexpr Complex& operator*=(const Complex& _compNum) // member function
	{
		//making copies of real and imaginary
		double realCopy = real;
		double imagCopy = imaginary;

		// multiplication: (a+bi) * (c+di) = (ac-bd) + (bc+ad)i
		real = (realCopy * _compNum.real) - (imagCopy * _compNum.imaginary);
		imaginary = (imagCopy * _compNum.real) + (realCopy * _compNum.imaginary);
		
		return *this; // return the multiplied current Complex (the product)
	}

	/**
	this binary operator/= divides two complex numbers and change the left-hand side
	@param _compNum is the Complex number to be divided
	@return the current Complex object that has been modified (divided)
	*/
	constexpr Complex& operator/=(const Complex& _compNum) // member function
	{
		//making copies of real and imaginary
		double realCopy = real;
		double imagCopy = imaginary;
		
		// division: (a+bi) / (c+di) = ((ac+bd)/(c^2+d^2)) + ((bc-ad)i/(c^2+d^2))
		real = ((realCopy * _compNum.real) + (imagCopy * _compNum.imaginary)) /
			((_compNum.real * _compNum.real) + (_compNum.imaginary * _compNum.imaginary));
		imaginary = ((imagCopy * _compNum.real) - (realCopy * _compNum.imaginary)) /
			((_compNum.real * _compNum.real) + (_compNum.imaginary * _compNum.imaginary));

		return *this; // return the divided current Complex (the quotient)
	}


	/**
	this unary operator~ returns the conjugate of a complex number
	@return a Complex object having the same real vareiable but negated imaginary variable
	*/
	constexpr Complex operator~() const // member function
	{
		return Complex(real, -imaginary); // make a new Complex with negated imaginary argument
	}

	/**
	this call operator() resets a complex number to be zero (in both real and imaginary)
	@return the Complex object having the reset (zero) real and imaginary variables
	*/
	constexpr Complex& operator()() // member function
	{
		real = 0; // reset the real to be zero
		imaginary = 0; // reset the imaginary to be zero

		return *this; // return the current Complex
	}


	/**
	this subscript operator[] allows the access to the real or the imaginary variable
	@param _type takes either "real" or "imag" string to get access to the variable
	@return either the real or the imaginary variable in double type
	*/
	double& operator[](std::string _type); // member function

	/**
	this subscript operator[] overloaded on const allows the access to the real or the imaginary variable
	@param _type takes either "real" or "imag" string to get access to the variable
	@return either the real or the imaginary variable in double type
	*/
	double operator[](const std::string _type) const; // member function

	/**
	this conversion operator converts a Complex object (by using real/imaginary variables) to a string
	@return the string that's being generated from the complex number
	*/
	operator std::string() const; // member function



private:

	double real;
	double imaginary;

};



/**
this binary operator== compares two Complex numbers and checks if they are completely equal
@param left is the complex number on the left-hand side
@param right is the complex number on the right-hand side
@return the boolean type of whether the left complex is equal to the right complex
*/
bool operator==(const Complex& left, const Complex& right); // non-member function

/**
this binary operator> compares two Complex numbers and check if the first argument is greater than the second argument
@param left is the complex number on the left-hand side
@param right is the complex number on the right-hand side
@return the boolean type of whether the left complex is greater than the right complex
*/
bool operator>(const Complex& left, const Complex& right); // non-member function

/**
this binary operator<= compares two Complex numbers and check if the first argument is
	less than or equal to the second argument
@param left is the complex number on the left-hand side
@param right is the complex number on the right-hand side
@return the boolean type of whether the left complex is less than or equal to the right complex
*/
bool operator<=(const Complex& left, const Complex& right); // non-member function

/**
this binary operator>= compares two Complex numbers and check if the first argument is
	greater than or equal to the second argument
@param left is the complex number on the left-hand side
@param right is the complex number on the right-hand side
@return the boolean type of whether the left complex is greater than or equal to the right complex
*/
bool operator>=(const Complex& left, const Complex& right); // non-member function

/**
this binary operator!= compares two Complex numbers and check if they are NOT equal
@param left is the complex number on the left-hand side
@param right is the complex number on the right-hand side
@return the boolean type of whether the left complex is NOT equal to the right complex
*/
bool operator!=(const Complex& left, const Complex& right); // non-member function


/**
this binary operator+ adds two complex numbers together using the binary operator+= defined above
@param left is the complex number on the left-hand side
@param right is the complex number on the right-hand side
@return the sum of the addition
*/
constexpr Complex operator+(Complex left, const Complex& right) // non-member function
{
	return left += right; // return the sum
}

/**
this binary operator- subtracts two complex numbers together using the binary operator-= defined above
@param left is the complex number on the left-hand side
@param right is the complex number on the right-hand side
@return the difference of the subtraction
*/
constexpr Complex operator-(Complex left, const Complex& right) // non-member function
{
	return left -= right; // return the difference
}

/**
this binary operator* multiplies two complex numbers together using the binary operator*= defined above
@param left is the complex number on the left-hand side
@param right is the complex number on the right-hand side
@return the product of the multiplication
*/
constexpr Complex operator*(Complex left, const Complex& right) // non-member function
{
	return left *= right; // return the product
}

/**
this binary operator/ divides two complex numbers together using the binary operator/= defined above
@param left is the complex number on the left-hand side
@param right is the complex number on the right-hand side
@return the quotient from the division
*/
constexpr Complex operator/(Complex left, const Complex& right) // non-member function
{
	return left /= right; // return the quotient
}


/**
this user-defined literal _i converts a long double to a Complex number (with imaginary part only)
@param _imaginary is the long double input that will be converted
@return the Complex number that having the real term 0 and the imaginary term from the input
*/
constexpr Complex operator""_i(long double _imaginary) // non-member function
{
	return Complex(0, _imaginary); // make a Complex object using the long double input as the imaginary term
}


/**
this non-member function helps validString function to determine if a character is either 1-9, '+', '-', or 'i'
@param _ch is the char input to be checked the validity
@return the boolean type of whether the char input is valid
*/
bool validChar(char _ch); // non-member function

/**
this non-member function helps the Complex constructor that takes a string input
	to determine if every single character in a string is either 1-9, '+', '-', or 'i'
@param _str is the string input to be checked the validity
@return the boolean type of whether the string has all characters valid to be parsed
*/
bool validString(const std::string _str); // non-member function


#endif