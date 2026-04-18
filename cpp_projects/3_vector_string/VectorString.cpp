#include <string>
#include <memory>

#include "VectorString.h"

namespace pic10b
{
	//default constructor
	VectorString::VectorString()
		:vec_size(0), vec_capacity(1), index(0), inputString("")
	{
		theString = std::make_unique<std::string[]>(vec_capacity); //initialize theString as a unique pointer to the heap memory
	}

	//constructor with input size
	VectorString::VectorString(size_t _theSize)
		:vec_size(_theSize), vec_capacity(_theSize * 2), index(0), inputString("")
	{
		theString = std::make_unique<std::string[]>(vec_capacity); //initialize theString as a unique pointer to the heap memory

		for (size_t i = 0; i < vec_size; ++i)
		{
			theString[i] = "";
		}
	}

	//constructor with input size and input string
	VectorString::VectorString(size_t _theSize, std::string _inputString)
		:vec_size(_theSize), vec_capacity(_theSize * 2), index(0), inputString(_inputString)
	{
		theString = std::make_unique<std::string[]>(vec_capacity); //initialize theString as a unique pointer to the heap memory

		for (size_t i = 0; i < vec_size; ++i)
		{
			theString[i] = inputString;
		}
	}

	//copy constructor
	VectorString::VectorString(const VectorString& _theVecStr)
		:vec_size(_theVecStr.vec_size), vec_capacity(_theVecStr.vec_capacity),
		index(_theVecStr.index), theString(new std::string[_theVecStr.vec_capacity])
	{
		for (size_t i = 0; i < _theVecStr.vec_capacity; ++i)
		{
			theString[i] = _theVecStr.theString[i]; //copy each string element from the input object
		}
	}

	//move constructor
	VectorString::VectorString(VectorString&& _theVecStr) noexcept
		:VectorString() //invoking the default constructor
	{
		std::swap(theString, _theVecStr.theString);
		std::swap(vec_size, _theVecStr.vec_size);
		std::swap(vec_capacity, _theVecStr.vec_capacity);
		std::swap(index, _theVecStr.index);
		std::swap(inputString, _theVecStr.inputString); //swap all the information between the input object and the default object
	}

	//copy assignment
	VectorString& VectorString::operator=(const VectorString& _theVecStr)
	{
		vec_size = _theVecStr.vec_size;
		vec_capacity = _theVecStr.vec_capacity;

		//does nothing, only self-assigned
		if (this == &_theVecStr)
		{
			return *this;
		}

		//making copy
		std::unique_ptr<std::string[]> tempString(new std::string[_theVecStr.vec_capacity]); //making another tempString pointer to copy elements


		for (size_t i = 0; i < _theVecStr.vec_size; ++i)
		{
			tempString[i] = _theVecStr.theString[i]; //copy elements down
		}

		theString = std::move(tempString); //make theString points to the new allocated copy on the heap

		return *this; //return the object reference
	}

	//move assignment
	VectorString& VectorString::operator=(VectorString&& _theVecStr) noexcept
	{
		std::swap(theString, _theVecStr.theString);
		std::swap(vec_size, _theVecStr.vec_size);
		std::swap(vec_capacity, _theVecStr.vec_capacity);
		std::swap(index, _theVecStr.index);
		std::swap(inputString, _theVecStr.inputString); //swap all the information between the input object and the default object

		return *this; //return the object reference
	}


	//member functions
	size_t VectorString::size() const
	{
		return vec_size;
	}

	size_t VectorString::capacity() const
	{
		return vec_capacity;
	}

	void VectorString::push_back(const std::string& _inputString)
	{
		inputString = _inputString;
		vec_size++;

		if (vec_size > vec_capacity) //if capacity is exceeded
		{
			vec_capacity *= 2;
			std::unique_ptr<std::string[]> tempString(new std::string[vec_capacity]); //making another tempString pointer to store new elements

			for (size_t i = 0; i < vec_size - 1; ++i)
			{
				tempString[i] = theString[i];
			}

			tempString[vec_size - 1] = inputString; //remove the last element

			theString = std::move(tempString); //make theString points to the new allocated copy on the heap

		}
		else	//if capacity has not been exceeded
		{
			theString[vec_size - 1] = inputString; //remove the last element
		}
	}

	void VectorString::pop_back()
	{
		theString[vec_size--] = "";

		std::unique_ptr<std::string[]> tempString(new std::string[vec_capacity]); //making another tempString pointer to store new elements

		for (size_t i = 0; i < vec_size - 1; ++i)
		{
			tempString[i] = theString[i];
		}

		theString = std::move(tempString);//make theString points to the new allocated copy on the heap
	}

	void VectorString::deleteAt(size_t _theIndex)
	{
		index = _theIndex;
		vec_size--;

		std::unique_ptr<std::string[]> tempString(new std::string[vec_capacity]); //making another tempString pointer to store new elements

		for (size_t i = 0; i < index; ++i)
		{
			tempString[i] = theString[i];
		}

		//skip the deleted index

		for (size_t i = index; i < vec_size; ++i)
		{
			tempString[i] = theString[i + 1];
		}

		theString = std::move(tempString);//make theString points to the new allocated copy on the heap
	}

	void VectorString::insertAt(size_t _theIndex, std::string _inputString)
	{
		index = _theIndex;
		inputString = _inputString;
		vec_size++;

		if (vec_size > vec_capacity)
		{
			vec_capacity *= 2; //if exceeds capacity
		}

		std::unique_ptr<std::string[]> tempString(new std::string[vec_capacity]); //making another tempString pointer to store new elements

		for (size_t i = 0; i < index; ++i)
		{
			tempString[i] = theString[i];
		}

		tempString[index] = inputString; //assign the insert string

		for (size_t i = index + 1; i < vec_size; ++i)
		{
			tempString[i] = theString[i - 1];
		}

		theString = std::move(tempString); //make theString points to the new allocated copy on the heap
	}

	std::string VectorString::at(size_t _theIndex) const
	{
		return theString[_theIndex]; //return the element
	}

	std::string& VectorString::at(size_t _theIndex)
	{
		return theString[_theIndex]; //return the element
	}
}