#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>


/**
@class Player stores the name and score of a player, allows access to the object's name and current score,
    and allows modifying scores (increase the score) when needed
*/
class Player
{
public:
    Player(const std::string _name, int _score = 0);   // Constructor


    /**
    this function allows the user to get access to the current score of a player
    @return the current score of the player object in a int type
    */
    int getScore();     // Accessor


    /**
    this function allows the user to get access to the player's unchanging (const) name
    @return the name of the player in a string type
    */
    const std::string getName();    // Accessor


    /**
    this function allows the user to modify the player's score when needed
    @param _addPoints prompts how many points (integer) to be added to the player
    */
    void setScore(int _addPoints);    // Mutator

private:
    const std::string name;
    int score;
};

#endif