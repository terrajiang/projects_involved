#include "Player.h"
#include <iostream>
#include <string>

using namespace std;


Player::Player(const string _name, int _score)
	:name(_name), score(_score)		//constructor initializer lists
{
	/*empty*/
}


int Player::getScore()
{
	return score;	//returns score of a player
}

const string Player::getName()
{
	return name;	//returns the unchanging (const) name of a player 
}


void Player::setScore(int _addPoints)
{
	score += _addPoints;	//add points to whoever wins the round
}