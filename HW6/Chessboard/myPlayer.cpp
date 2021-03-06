#include "myPlayer.h"
#include "chessBoard.h"
#include <limits>
#include <cstring>
// King, Queen, Rook, Bishop, Knight, Pawn
// 0,1,2,3,4,5
// White = 0, Black = 1
myPlayer::myPlayer(chessBoard::colorType col) : chessPlayer(col) 
{ 
	srand(time(NULL));
	//Counts how many moves I've made
	count = 0;
};

int myPlayer::evalBoard(chessBoard Board)
{
	int whitePts = 0;
	int blackPts = 0;
	//Go through the entire board and evaluate it
	//Store evaluations based on color
	//Gives enemy pieces a higher score to promote agression
	for(int x = Board.minRow; x <= Board.maxRow; x++)
	{
		for(int y = Board.minCol; y <= Board.maxCol; y++)
		{	
			try
			{
				chessBoard::piece temp = Board.atSquare(y,x);
				if(myColor)
				{
					if(temp.type == 0 && temp.color == 0)
					{
						whitePts+=10000000;
					}		
					else if(temp.type == 1 && temp.color == 0)
					{		
						whitePts+= 900+9;
					}		
					else if(temp.type == 2 && temp.color == 0)
					{		
						whitePts+=500+5;
					}		
					else if(temp.type == 3 && temp.color == 0)
					{		
						whitePts+=300+3;
					}		
					else if(temp.type == 4 && temp.color == 0)
					{	
						whitePts+=300+3;
					}		
					else if(temp.type == 5 && temp.color == 0)
					{		
						whitePts+=100+1;		
					}	
					else if(temp.type == 0 && temp.color == 1)
					{
						blackPts+=10000000;
					}		
					else if(temp.type == 1 && temp.color == 1)
					{		
						blackPts+= 900;
					}		
					else if(temp.type == 2 && temp.color == 1)
					{		
						blackPts+=500;
					}		
					else if(temp.type == 3 && temp.color == 1)
					{		
						blackPts+=300;
					}		
					else if(temp.type == 4 && temp.color == 1)
					{		
						blackPts+=300;
					}		
					else if(temp.type == 5 && temp.color == 1)
					{		
						blackPts+=100;		
					}	
				}
				else
				{
					if(temp.type == 0 && temp.color == 0)
					{
						whitePts+=10000000;
					}		
					else if(temp.type == 1 && temp.color == 0)
					{		
						whitePts+= 900;
					}		
					else if(temp.type == 2 && temp.color == 0)
					{		
						whitePts+=500;
					}		
					else if(temp.type == 3 && temp.color == 0)
					{		
						whitePts+=300;
					}		
					else if(temp.type == 4 && temp.color == 0)
					{	
						whitePts+=300;
					}		
					else if(temp.type == 5 && temp.color == 0)
					{		
						whitePts+=100;		
					}	
					else if(temp.type == 0 && temp.color == 1)
					{
						blackPts+=10000000;
					}		
					else if(temp.type == 1 && temp.color == 1)
					{		
						blackPts+= 900+9;
					}		
					else if(temp.type == 2 && temp.color == 1)
					{		
						blackPts+=500+5;
					}		
					else if(temp.type == 3 && temp.color == 1)
					{		
						blackPts+=300+3;
					}		
					else if(temp.type == 4 && temp.color == 1)
					{		
						blackPts+=300+3;
					}		
					else if(temp.type == 5 && temp.color == 1)
					{		
						blackPts+=100+1;		
					}	
				}
			}	
			catch (chessBoard::NoPieceException e)
			{	
				//#HANDLED
				continue;
			}		
		}
	}	
	
	//Does a subtraction/pseudoprune based on color
	if(myColor)
	{
		return blackPts-whitePts;	
	}
	else
	{
		return whitePts-blackPts;
	}
}

chessBoard::move myPlayer::calcMove()
{
	evals.clear();
	evals2.clear();
	looksGood.clear();
	chessBoard::move myMove;
	vector<int> plsno;
	int max = numeric_limits<int>::min();
	int min = numeric_limits<int>::max();
	//First move (ours)
	for(int x = 0; x < myBoard.numMoves(); x++)
	{
		chessBoard local = myBoard;
		local.makeMove(local.nthMove(x));
		//Second move (theirs)
		for(int y = 0; y < local.numMoves(); y++)
		{
			chessBoard localer = local;
			localer.makeMove(localer.nthMove(y));	
			//If the board is in a better or equal state after their move, then add the move that got us here and add the board state value (should have used std::pair)
			if(evalBoard(localer) >= evalBoard(local))
			{
				evals.push_back(evalBoard(localer));
				evals2.push_back(x);	
			}
			//If we can lose, add the potential loss move into a vector
			else if(evalBoard(localer) < -1000000)
			{
				plsno.push_back(x);
			}
		}	
	}	

	//Getting max score of moves
	for(int x = 0; x < evals.size(); x++)
	{
		if(evals[x] > max)
		{
			max = evals[x];
		}	
	}
	//Geting the best moves
	for(int x = 0; x < evals.size(); x++)
	{
		//If it is one of the best moves to make, it is stored in looksGood
		if(evals[x] == max)
		{
			looksGood.push_back(evals2[x]);
		}
	}
	//If something in the best move list can potentially cause us to lose, remove it
	for(int x = 0; x < plsno.size(); x++)
	{
		for(int y = 0; y < looksGood.size(); y++)
		{
			if(plsno[x] == looksGood[y])
			{
				looksGood.erase(looksGood.begin()+(y-1));
			}
		}
	}
	
	//Randomly picks a best move to use
	myMove = myBoard.nthMove(looksGood[rand() % looksGood.size()]);
	//If there are no good moves in the vector, do something random
	if(max == 0 || looksGood.size() == 0)
		myMove = myBoard.nthMove(rand() % myBoard.numMoves());
	
	//Increment the turn counter
	count++;
	
	return myMove;
}

void myPlayer::enemyMove(chessBoard::move theMove) 
{
	myBoard.makeMove(theMove); 
};

chessBoard::move myPlayer::getMove() 
{	
	//Calculates and executes the move
	chessBoard::move theMove = calcMove();
	myBoard.makeMove(theMove); 
	return theMove;
}
