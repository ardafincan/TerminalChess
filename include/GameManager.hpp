#pragma once 

#include "ChessBoard.hpp"




class GameManager {
    public:
    GameManager(ChessBoard* board);

    ChessBoard *chessBoard;
    
    void chessGame();
    int whoWon();

    private:
    bool blackTurn = false;
};