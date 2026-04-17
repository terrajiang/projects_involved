#ifndef _GAME_H_
#define _GAME_H_

#include <string>


/**
@class Game represents how a TicTacToe game works by taking turns
*/
class Game
{
public:
    Game(const int _numOfRounds, const std::string _name1, const std::string _name2);       // Constructor


    /**
    this function tells the user who's turn it is (it alternates with player 1 and player 2),
        and gets the user's input of the desired position chosen (row col)
    @return the desired position that the user inputs in a string type
    */
    std::string playTheGame();      // Accessor


    /**
    this function allows the user to get access to the name of the player that takes action in the turn
    @return the name of the current player in a string type
    */
    std::string getPlayer();      // Accessor

private:
    const int numOfRnds;
    const std::string plr1;
    const std::string plr2;
    std::string choosingSpot;
    std::string whosTurn;
    int turnCnts;
};

#endif