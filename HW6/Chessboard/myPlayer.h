/* 
 * File:   myPlayer.h
 * Author: Ari Trachtenberg
 * 
 * A very simple chess player that randomly chooses one of the moves available to it.
 * Created on March 25, 2015, 4:33 PM
 */

#ifndef MYPLAYER_H
#define	MYPLAYER_H
#include <cstdlib>
#include "chessBoard.h"
#include "chessPlayer.h"

class myPlayer : public chessPlayer 
{
public:
/*
	ALL DESCRIPTIONS ARE INSIDE THE .CPP!!!!!!!!!!!!!
	Step by step comments :)
*/
	vector<int> evals;
	vector<int> evals2;
	vector<int> evals3;
	vector<int> evals4;
	vector<int> looksGood;
	int count;

	myPlayer(chessBoard::colorType col);

	virtual void enemyMove(chessBoard::move theMove);
	virtual chessBoard::move getMove();

	int evalBoard(chessBoard);
	chessBoard::move calcMove();
	int eval(vector<chessBoard::piece>,chessBoard);
    
private:
    chessBoard myBoard; // internal version of the current board
};

#endif	/* MYPLAYER_H */


