#include "Game.h"
#include <iostream>
#include <string>

using namespace std;


Game::Game(const int _numOfRounds, const string _name1, const string _name2)
	:numOfRnds(_numOfRounds), plr1(_name1), plr2(_name2)		//constructor initializer lists
{
	whosTurn = plr1;	//initiliazing whosTurn (the name of the current player) to be plr1
	turnCnts = 0;		//initializing turnCnts (the current turn counts) to be 0 (at the beginning of every round)
}


string Game::playTheGame()
{
	if (turnCnts % 2 == 0)	 //the players take turns (starting with player 1 in the first move of round 1)
	{
		whosTurn = plr1;
	}
	else
	{
		whosTurn = plr2;
	}

	cout << "This is " << whosTurn << "'s turn.\n"		//cout who's turn it is
		<< "Where would you like to play ? Enter your row position and column position : row col : ";
	string choosingSpot = "0 0";
	getline(cin, choosingSpot);		//prompt user to input the desired row and col position (1 to 3) on the board ("row col" format)

	turnCnts++;

	return choosingSpot;	//return the user's input of desired position on the board
}

string Game::getPlayer()
{
	return whosTurn;	//return the name of the current player that takes action
}