#pragma once 

#include "ChessBoard.hpp"




class GameManager {
    public:
    GameManager(ChessBoard* board, GameSettings* settings);

    ChessBoard *chessBoard;
    GameSettings *gameSettings;
    
    void chessGame();
    int whoWon();

    private:
    bool blackTurn = false;
};