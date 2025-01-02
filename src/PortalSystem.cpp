#include <PortalSystem.hpp>

PortalSystem::PortalSystem(std::vector<PortalConfig> portalConfigs, ChessBoard *board)
    : chessBoard(*board), board(board)
{
    for (int i = 0; i < portalConfigs.size(); i++)
    {
        PortalConfig portalConfig = portalConfigs[i];
        portals.insert(std::make_pair(portalConfig.positions.entry, portalConfig));
    }
};


// void PortalSystem::teleportPiece(Position source, Position target)
// {
//     if (portals.contains(source) && portals.contains(target) && validator.isTeleportValid())
//     {
//         if (portals.at(source).properties.allowed_colors.contains(chessBoard.board.at(source).color))
//         {
//             chessBoard.board.insert(std::make_pair(target, chessBoard.board.at(source)));
//             chessBoard.board.erase(source);
//         }else{
//             std::cout << "Invalid move, piece cannot be teleported." << std::endl;
//         }
//     }

// }