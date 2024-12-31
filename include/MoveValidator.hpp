#pragma once

#include "ChessBoard.hpp"
#include "ConfigReader.hpp"

class ChessBoard;

class MoveValidator {
    public: 
    explicit MoveValidator(ChessBoard* board);

    bool isMoveValid(Position source, Position target);
    bool isPathValid(Position source, Position target);
    bool isTeleportValid();

    private: 
        ChessBoard* board;
        ChessBoard& chessBoard;
};