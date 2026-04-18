#include "SpellCheck.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


SpellCheck::SpellCheck()		//default constructor (no argument)
{
	unordered_set<string> theDictionary = {};		//the dictionary stores no words initially
	vector<string> theFile = {};					//the file has no word (empty string) initially
	string theDicName = "theDicName";				//initializing the dictionary name as "theDicName"
	string theWord = "theWord";						//initializing the word as "theWord"
	string theFileName = "theFileName";				//initializing the file name as "theFileName"
}


void SpellCheck::read_dictionary(const string _dicName)
{
	theDicName = _dicName;

	ifstream myDictionary;
	myDictionary.open(theDicName);		//opens myDictionary text file using the input name of the dictionary

	if (!myDictionary.is_open())
	{
		cout << "failed to open!\n";	//checks if the file is opened
	}
	else
	{
		string eachDicWord = "";
		while (myDictionary >> eachDicWord)		//reads each word from the dictionary file
		{
			theDictionary.insert(eachDicWord);	//inserts each word from the dictionary file into the unordered set
		}
	}
	myDictionary.close();		//closes myDictionary text file
}


bool SpellCheck::is_valid(string _theWord)
{
	theWord = _theWord;

	//returns true if the input word is found from the dictionary unordered set (should be exactly the same word)
	return (theDictionary.count(theWord) != 0) ? true : false;
}


void SpellCheck::process_file(const std::string _fileName)
{
	theFileName = _fileName;

	ifstream myFile;
	myFile.open(theFileName);		//opens myFile text file to be spell checked using the input name of the file

	if (!myFile.is_open())
	{
		cout << "failed to open!\n";		//checks if the file is opened
	}
	else
	{
		string eachLine = "";
		while (!myFile.eof())
		{
			getline(myFile, eachLine);			//gets each line from myFile into "eachLine" string
			theFile.push_back(eachLine);		//stores "eachLine" string into the string vector theFile
		}
		myFile.close();		//closes myFile text file
	}


	//spells checking
	for (size_t i = 0; i < theFile.size(); ++i)	//each line
	{
		string theLine = theFile[i];		//stores each string element (each line) from the vector into "theLine"

		while (theLine.size() == 0)
		{
			cout << '\n';					//if the line is an empty string, goes to the next line by printing '\n'
			theLine = theFile[++i];			//and checks the next line in the file
		}


		//to read each of the entire word from the line
		int index = 0;							//the index of the line is set to be zero initially (the beginning character of the line)
		char currentChar = theLine.front();		//the initial character to be checked is the beginning character of theLine

		string tempLine = theLine;		//makes a copy of theLine into tempLine
		tempLine.append(1, ' ');		//to avoid "out_or_range" error when checking the last word of the line, add a space at the end of tempLine

		while (index < theLine.size())
		{
			if (is_white_space(currentChar) == false)	//while currentChar is NOT a white space
			{
				int wordSizeCount = 1;
				while (is_white_space(currentChar) == false)		//detects the word
				{
					if (index + 1 <= theLine.size() - 1 && is_white_space(tempLine.at(index + 1)) == false)
					{
						wordSizeCount++;
						currentChar = tempLine.at(++index); //not yet recieve a word, continue checking next characters
					}
					else	//detected a whitespace, get the word
					{
						string currentWord = tempLine.substr((index - wordSizeCount + 1), wordSizeCount);	//forms the word detected

						//checks the spelling of the current word detected and prints it to the console
						if (!final_punctuation(currentWord))	//does not have final punctuation mark
						{
							string tempWord = currentWord;
							depunctuate(currentWord);
							if (is_valid(currentWord))
							{
								cout << tempWord;
							}
							else
							{
								cout << '*' << tempWord << '*';		//after dupunctuated, still mispelling
							}
						}
						else	//has final punctuation mark
						{
							string tempWord = currentWord;
							depunctuate(currentWord);
							if (is_valid(currentWord))
							{
								cout << tempWord;
							}
							else
							{
								//after dupunctuated, still mispelling (preserves the final punctuation mark in the end)
								cout << '*' << tempWord.substr(0, (tempWord.size() - 1)) << '*' << tempWord.at(tempWord.size() - 1);
							}
						}
						currentChar = tempLine.at(++index);		//moves currentChar and index forward to continue detecting the next word
						break;		//completes the current word's detecting and spell-checking
					}
				}
			}
			else	//while currentChar IS a white space 
			{
				cout << currentChar;
				currentChar = tempLine.at(++index);		//moves currentChar and index forward to continue detecting the next character
			}
		}
		cout << '\n';		//end of each line, prints '\n' to go to the next line
	}
}




//implementations of non-member functions

bool is_white_space(char theChar)
{
	return (theChar == ' ' || theChar == '\t' || theChar == '\n') ? true : false;
}


bool final_punctuation(string theWord)
{
	return (theWord.back() == '.' || theWord.back() == ',' || theWord.back() == '!'
		|| theWord.back() == '?' || theWord.back() == ';' || theWord.back() == ':') ? true : false;		//assume there're only ,.!?;: possibilities
}


void depunctuate(string& theWord)		//mutates the string reference input
{
	//removes the last punctuation (if any)
	char theLastLetter = theWord.back();

	if (theLastLetter == '.' || theLastLetter == ',' || theLastLetter == '!'
		|| theLastLetter == '?' || theLastLetter == ';' || theLastLetter == ':')
	{
		theWord.pop_back();
	}

	//converts the first character from upper case to lower case
	char& theFirstLetter = theWord.front();

	if (theFirstLetter >= 'A' && theFirstLetter <= 'Z' && theWord != "I")		//except "I"
	{
		theFirstLetter += ('a' - 'A');
	}
}