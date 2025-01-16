#pragma once

#include "../include/ConfigReader.hpp"
#include "../include/MoveValidator.hpp"
#include "../include/PortalSystem.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

class PortalSystem;

struct Piece
{
    std::string type;
    std::string color;
    MovementRules movement;
    bool hasMoved = false;
};

class ChessBoard
{
public:
    ChessBoard(std::vector<PieceConfig> pieceConfigs, GameSettings *settings);

    std::unordered_map<Position, Piece> board;
    GameSettings *gameSettings;
    PortalSystem *portalSystem;

    std::vector<Position> pieceFinder(std::string pieceType, std::string color = "all");
    bool movePiece(Position source, Position target);
    bool capturePiece(Position source, Position target);
    bool isCellThreatenedBy(Position cell, std::string color);
    void printBoardStatus();
};