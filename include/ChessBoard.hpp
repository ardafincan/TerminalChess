#pragma once 

#include "../include/ConfigReader.hpp"
#include <vector>
#include <string>
#include <unordered_map>



struct Piece{
    std::string type;
    std::string color;
    MovementRules movement;
    bool hasMoved = false;
};

class ChessBoard {
    public: 
    std::unordered_map<Position, Piece> board; 

    ChessBoard(PieceConfig pieceConfig, char* argv[]);
    bool movePiece(Position source, Position target);
    bool capturePiece(Position source, Position target);
    void printBoardStatus();

};