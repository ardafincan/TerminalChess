#include <PortalSystem.hpp>
#include "ChessBoard.hpp"

PortalSystem::PortalSystem(std::vector<PortalConfig> portalConfigs)
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
    }
};

bool PortalSystem::isTeleportValid(Piece piece, Portal portal)
{
    if ((piece.color == portal.allowed_colors[0] || piece.color == portal.allowed_colors[1]) && portal.isCool)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PortalSystem::teleportPiece(Position source)
{
    Position target = portals.at(source).exit;
    if (isTeleportValid(chessBoard->board.at(source), portals.at(source)))
    {
        chessBoard->board.at(target) = chessBoard->board.at(target);
        chessBoard->board.at(target);
    }
}