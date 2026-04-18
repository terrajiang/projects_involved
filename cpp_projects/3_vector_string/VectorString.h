#ifndef _VECTORSTRING_
#define _VECTORSTRING_

#include <memory>
#include <string>

namespace pic10b
{
	/**
	@class VectorString stores the information of each vector string and defines their operations (adding or subtracting elements)
	*/
	class VectorString
	{
	public:
		
		VectorString();													//default constructor
		VectorString(size_t _theSize);									//constructor with input size
		VectorString(size_t _theSize, std::string _theString);			//constructor with input size and input string

		VectorString(const VectorString& _theString);					//copy constructor
		VectorString(VectorString&& _theString) noexcept;				//move constructor

		VectorString& operator=(const VectorString& _theString);		//copy assignment
		VectorString& operator=(VectorString&& _theString) noexcept;	//move assignment


		/**
		this function allows the access to the size of the vector string object
		@return the size of the vector string in size_t type
		*/
		size_t size() const;

		/**
		this function allows the access to the capacity of the vector string object
		@return the capacity of the vector string in size_t type
		*/
		size_t capacity() const;


		/**
		this function allows the user to add a string element to the end of the vector string
		@param _theString is the input word in string type to be added
		*/
		void push_back(const std::string& _theString);

		/**
		this function allows the user to remove the string element from the end of the vector string
		*/
		void pop_back();

		/**
		this function allows the user to delete a string element from the vector string at the position that the user wants
			the elements will shift backward after deleting
		@param _theIndex is the input index in size_t type to be deleted
		*/
		void deleteAt(size_t _theIndex);

		/**
		this function allows the user to insert a string element to the vector string at the position that the user wants
			the elements will shift forward after inserting
		@param _theIndex is the input index in size_t type to be inserted
		@param _theString is the string input in string type that the user wnats to insert
		*/
		void insertAt(size_t _theIndex, std::string _theString);


		/**
		this function allows the access to a specific element from the vector string at the position that the user indicates
		@param _theIndex is the input index (position) in size_t type that the user wants to obtain element from
		@return the string element of string type by reference to const from the specific index (position)
		*/
		std::string at(size_t _theIndex) const;					//overloaded (const string)

		/**
		this function allows the access to a specific element from the vector string at the position that the user indicates
		@param _theIndex is the input index (position) in size_t type that the user wants to obtain element from
		@return the string element of string type by reference from the specific index (position)
		*/
		std::string& at(size_t _theIndex);						//overloaded (non-const string)

	private:
		size_t vec_size;
		size_t vec_capacity;
		size_t index;
		std::unique_ptr<std::string[]> theString;
		std::string inputString;
	};

}

#endif