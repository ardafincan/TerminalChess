#include <PortalSystem.hpp>
#include "ChessBoard.hpp"

PortalSystem::PortalSystem(std::vector<PortalConfig> portalConfigs, ChessBoard *chessBoard)
    : chessBoard(chessBoard)
{
    for (int i = 0; i < portalConfigs.size(); i++)
    {
        PortalConfig portalConfig = portalConfigs[i];
        Portal portal;
        portal.entry = portalConfig.positions.entry;
        portal.exit = portalConfig.positions.exit;
        portal.allowed_colors = portalConfig.properties.allowed_colors;
        portal.isCool = true;
        portals.insert(std::make_pair(portalConfig.positions.entry, portal));
        portalExits.insert(std::make_pair(portalConfig.positions.exit, portal));
    }
};

bool PortalSystem::isTeleportValid(Piece piece, Portal portal)
{
    std::cout << "Checking if teleport is valid" << std::endl;
    for (int i = 0; i < portal.allowed_colors.size(); i++)
    {
        if (piece.color == portal.allowed_colors[i] && portal.isCool)
        {
            return true;
        }
    }
    return false;
}

void PortalSystem::teleportPiece(Position source)
{
    Position target;
    if (portals.contains(source))
    {
        target = portals.at(source).exit;
    }
    if (chessBoard)
    {
        if (chessBoard->board.contains(source))
        {
            if (isTeleportValid(chessBoard->board.at(source), portals.at(source)))
            {
                chessBoard->board.insert(std::make_pair(target, chessBoard->board.at(source)));
                chessBoard->board.erase(source);
            }
        }
    }
}