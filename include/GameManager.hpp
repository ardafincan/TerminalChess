#pragma once 

#include "ChessBoard.hpp"




class GameManager {
    public:
    GameManager(ChessBoard* board);

    ChessBoard *chessBoard;
    
    void chessGame();
    bool TurnProcessor();
    int whoWon();

    private:
    bool blackTurn = false;
};