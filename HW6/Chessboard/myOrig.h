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

class myPlayer : public chessPlayer 
{
public:
    myPlayer(chessBoard::colorType col) : chessPlayer(col) { srand(time(NULL)); };
    virtual void enemyMove(chessBoard::move theMove) {myBoard.makeMove(theMove); };
    virtual chessBoard::move getMove() {chessBoard::move theMove = myBoard.nthMove(rand() % myBoard.numMoves()); myBoard.makeMove(theMove); return theMove;}
    
private:
    chessBoard myBoard; // internal version of the current board
};

#endif	/* MYPLAYER_H */

