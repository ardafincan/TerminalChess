#pragma once 

#include "ChessBoard.hpp"

struct move
{
    Position source;
    Position target;
};




class GameManager {
    public:
    GameManager(ChessBoard* board);

    ChessBoard *chessBoard;
    
    void chessGame();
    bool TurnProcessor();
    int whoWon();

    private:
    std::vector<move> moveHistory;
};