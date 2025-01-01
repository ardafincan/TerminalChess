#pragma once 

#include "../include/ConfigReader.hpp"
#include "../include/MoveValidator.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>



struct Piece{
    std::string type;
    std::string color;
    MovementRules movement;
    bool hasMoved = false;
};

class ChessBoard {
    public: 
    std::unordered_map<Position, Piece> board; 

    ChessBoard(std::vector<PieceConfig> pieceConfigs);
    std::vector<Position> pieceFinder(std::string pieceType, std::string color = "all");
    bool movePiece(Position source, Position target);
    bool capturePiece(Position source, Position target);
    bool isCellThreatenedBy(Position cell, std::string color);
    void printBoardStatus();

};