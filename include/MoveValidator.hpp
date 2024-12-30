#pragma once

#include "ChessBoard.hpp"

class MoveValidator {
    public: 
    MoveValidator(ChessBoard board);

    ChessBoard chessBoard;

    bool isMoveValid(Position source, Position target);
    bool isPathValid(Position source, Position target);
    bool isTeleportValid();
};