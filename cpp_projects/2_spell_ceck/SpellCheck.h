#ifndef _SPELLCHECK_H_
#define _SPELLCHECK_H_

#include <unordered_set>


/**
@class SpellCheck reads the dictionary file as a source to spell check 
	and checks if each individual word from the input file is valid (if not, asterisks will surrounds the word)
*/
class SpellCheck
{
public:
	SpellCheck();		//default constructor
	
	/**
	this function opens the dictionary file and stores each word from the dictionary into an unordered set
	@param _dicName is the name of the dictionary file to be opened (expected to be called "dictionary.txt")
	*/
	void read_dictionary(const std::string _dicName);

	/**
	this function allows the user (or program) to check if the word input is in the dictionary
	@param _theWord is the input word in string type to be checked if it exists in the dictionary (unordered set)
	@return the boolean type of whether or not the word spells correctly (exists in the dictionary)
	*/
	bool is_valid(std::string _theWord);
	
	/**
	this function opens the file to be spell checked and checks the correctness of each word in the file 
		(if not, asterisks will surround the word), and then prints the checked result to the console window
	@param _fileName is the input file name in string type to be opened and spell checked
	*/
	void process_file(const std::string _fileName);

private:
	std::unordered_set<std::string> theDictionary;
	std::vector<std::string> theFile;
	std::string theDicName;
	std::string theWord;
	std::string theFileName;
};




/**
this function checks if the input character is a white space (a space, a tab, or a new line)
@param theChar is the input character to be checked
@return the boolean type of whether or not the character input is a space, tab, or a new line
*/
bool is_white_space(char theChar);					//definition of is_white_space function 

/**
this function checks if the input word has a punctuation mark at the end
@param theWord is the input string of the word to be checked
@return the boolean type of whether or not the final character of the word is a punctuation mark
*/
bool final_punctuation(std::string theWord);		//definition of final_punctuation function

/**
this function removes the final punctuation (if any) of the word 
	and converts the first character of the word from upper case to lower case
@param theWord is the input string reference of the word to be depunctuated
*/
void depunctuate(std::string& theWord);				//definition of depunctuate function


#endif