#include <iostream>
#include <string>
#include <vector>

#include "Game.h"
#include "Player.h"

using namespace std;


/**
this function prints the board with pipes (|), dashes (-), 1 2 3 indicating rows and columns,
	and x's or o's indicating player 1 and player 2's inputs (if any)
@param board is a vecotr input with information about rows and columns
*/
void printTheBoard(vector<vector<string> >& board);	//prototype of printTheBoard function

/**
this function checks if one of the players has 3 in the row, 3 down, or 3 a diagonal that wins the round
@param board is a vecotr input with information about rows and columns
@return the boolean type of whether or not someone wins the round
*/
bool winTheRound(vector<vector<string> >& board);	//prototype of winTheRound function


int main()
{
	cout << "This is a Tic Tac Toe game! \n";

	cout << "How many rounds would you like to play ? "; //prompts the user to decide the number of rounds to play
	int numOfRounds = 0;
	cin >> numOfRounds;
	cin.ignore();

	cout << "Please enter the name of player 1 : "; //prompts the user to enter the name of player 1
	string name1 = "name1";
	getline(cin, name1);


	cout << "Thanks.Please enter the name of player 2 : "; //prompts the user to enter the name of player 2
	string name2 = "name2";
	getline(cin, name2);

	Player player1(name1, 0);	//construct two players' objects with the name inputs and default score 0
	Player player2(name2, 0);

	cout << "Let the game begin! \n";


	vector<vector<string> > board;
	for (int i = 0; i < 3; i++)		//create and initiliaze the board to be empty
	{
		vector<string> boardRow;
		for (int j = 0; j < 3; j++)
		{
			boardRow.push_back(" ");
		}
		board.push_back(boardRow);
	}



	Game game(numOfRounds, player1.getName(), player2.getName()); //construct the game object

	int roundCounts = 0;
	while (roundCounts >= 0 && roundCounts < numOfRounds) //from 0 to the number of rounds the user wants to play
	{
		printTheBoard(board);	//call printTheBoard function (empty at the beginning) before each round

		int turnCounts = 0;
		while (turnCounts >= 0 && turnCounts <= 9) //from 0 to 9 since there's only 9 positions
		{
			if (winTheRound(board) == false) //when no one has yet won the round
			{
				if (turnCounts == 9) //when 9 positions are all full but no one wins
				{
					cout << "It's a draw!\n";

					cout << "Presently, " << player1.getName() << " has " << player1.getScore()
						<< " points and " << player2.getName() << " has " << player2.getScore() << " points.\n";  //cout the result (no change)

					break; //break to the next round
				}
				else //when none of the players win and the board has not yet full
				{
					string userSpot = game.playTheGame(); //call playTheGame function to get user input for desired position chosen

					int rowInput = userSpot.front() - '0'; //obtain the numerical row and col numbers instead of string type
					int colInput = userSpot.back() - '0';

					if (game.getPlayer() == player1.getName())	//put x's or o's on the board based on who's the current player
					{
						board[rowInput - 1][colInput - 1] = "x";
					}
					else
					{
						board[rowInput - 1][colInput - 1] = "o";
					}
				}
				printTheBoard(board); //prints the board after each player's turn
				turnCounts++;
			}
			else //when one of the players win before exceeding 9 turns
			{
				cout << game.getPlayer() << " won the round!\n";

				if (game.getPlayer() == player1.getName())	//add one point to whoever wins the round
				{
					player1.setScore(1);
				}
				else
				{
					player2.setScore(1);
				}

				cout << "Presently, " << player1.getName() << " has " << player1.getScore()			//cout the current points obtained by each player
					<< " points and " << player2.getName() << " has " << player2.getScore() << " points.\n";

				break; //break to the next round
			}
		}

		for (int i = 0; i < 3; i++)			//clear the board for the next round
		{
			for (int j = 0; j < 3; j++)
			{
				board[i][j] = " ";
			}
		}

		roundCounts++;
	}


	if (player1.getScore() > player2.getScore())		//when all rounds end and cout the result (who wins or it's a draw)
	{
		cout << player1.getName() << " won the game!\n";
	}
	else if (player1.getScore() < player2.getScore())
	{
		cout << player2.getName() << " won the game!\n";
	}
	else
	{
		cout << "It's a draw!\n";
	}

	return 0;
}


void printTheBoard(vector<vector<string> >& board)		//printTheBoard function implementation
{
	cout << " 1 2 3\n"; //columns' title (horizontal 1 2 3)

	for (int i = 0; i < 3; i++)
	{
		cout << i + 1; //rows' title (vertical 1 2 3)

		if (i >= 0 && i < 2) //for the first and the second rows
		{
			for (int j = 0; j < 3; j++)
			{
				if (j >= 0 && j < 2)
				{
					cout << board[i][j] << "|"; //pipes to seperate columns
				}
				else
				{
					cout << board[i][j] << '\n';
				}
			}
			cout << " ----- \n"; //dashes to seperate rows (no need for the last row)
		}
		else //for the third (the last) row
		{
			for (int j = 0; j < 3; j++)
			{
				if (j >= 0 && j < 2)
				{
					cout << board[i][j] << "|"; //pipes to seperate columns
				}
				else
				{
					cout << board[i][j] << '\n';
				}
			}
		}

	}
}

bool winTheRound(vector<vector<string> >& board)			//winTheRound function implementation (test winning status)
{
	if ((board[0][0] != " " && board[0][0] == board[0][1] && board[0][0] == board[0][2])
		|| (board[1][0] != " " && board[1][0] == board[1][1] && board[1][0] == board[1][2])
		|| (board[2][0] != " " && board[2][0] == board[2][1] && board[2][0] == board[2][2]))
	{
		return true; //someone wins when the player has 3 in a row (but not empty)
	}
	else if ((board[0][0] != " " && board[0][0] == board[1][0] && board[0][0] == board[2][0])
		|| (board[0][1] != " " && board[0][1] == board[1][1] && board[0][1] == board[2][1])
		|| (board[0][2] != " " && board[0][2] == board[1][2] && board[0][2] == board[2][2]))
	{
		return true; //someone wins when the player has 3 in a column (but not empty)
	}
	else if ((board[0][0] != " " && board[0][0] == board[1][1] && board[0][0] == board[2][2])
		|| (board[0][2] != " " && board[0][2] == board[1][1] && board[0][2] == board[2][0]))
	{
		return true; //someone wins when the player has 3 in a diagonal (but not empty)
	}
	else
	{
		return false; //when none of the players has 3 in a row, 3 down, or a diagonal (none of the players win)
	}
}