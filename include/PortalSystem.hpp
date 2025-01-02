#pragma once 

#include "ChessBoard.hpp"

class PortalSystem {
    public:
    explicit PortalSystem(std::vector<PortalConfig> portalConfigs, ChessBoard* board);

    std::unordered_map<Position, PortalConfig> portals;


    void teleportPiece(Position source, Position target);

    private: 
        ChessBoard* board;
        ChessBoard& chessBoard;
};