#pragma once

#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>
#include "ChessBoard.hpp"
#include "ConfigReader.hpp"  

class ChessBoard;
struct Piece;

struct Portal
{
    Position entry;
    Position exit;
    std::vector<std::string> allowed_colors;
    bool isCool;
};

class PortalSystem
{
public:
    explicit PortalSystem(std::vector<PortalConfig> portalConfigs, ChessBoard *chessBoard);

    ChessBoard *chessBoard;

    std::unordered_map<Position, Portal> portals;

    bool isTeleportValid(Piece piece, Portal portal);
    void teleportPiece(Position source);
};