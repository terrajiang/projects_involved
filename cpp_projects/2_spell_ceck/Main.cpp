#include <iostream>
#include <string>
#include "SpellCheck.h"

using namespace std;


int main()
{
	cout << "Enter file to spell check: ";	//prompt user to enter the name of the file to be spell checked
	string fileName = "";
	getline(cin, fileName);

	string dicName = "dictionary.txt";		//assume the dictionary is always called "dictionary.txt"

	SpellCheck mySpellCheck;				//create mySpellCheck object

	mySpellCheck.read_dictionary(dicName);	//read "dictionary.txt" to be the source to check the spelling
	mySpellCheck.process_file(fileName);	//open the "example.txt"(or other files) to be spell checked


	return 0;
}