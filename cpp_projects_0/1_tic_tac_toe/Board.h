#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>

class Board
{
public:
    
    // Constructor
    Board();

    // Accessors
    std::string getSpotLocated(int _rowNum, int _colNum);

    // Mutators
    std::string setSpotLocated(int _rowNum, int _colNum);


private:
    int rowNum;
    int colNum;
};

#endif