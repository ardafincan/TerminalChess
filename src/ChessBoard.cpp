#include "../include/ChessBoard.hpp"

ChessBoard::ChessBoard(std::vector<PieceConfig> pieceConfigs, GameSettings *settings, PortalSystem *portalSystem)
{
    gameSettings = settings;

    for (int j = 0; j < pieceConfigs.size(); j++)
    {
        PieceConfig pieceConfig = pieceConfigs[j];
        std::string white = "White";
        std::string black = "Black";

        for (int i = 0; i < pieceConfig.white_positions.size(); i++)
        {
            Piece piece = {pieceConfig.type, white, pieceConfig.movement};
            board.insert(std::make_pair(pieceConfig.white_positions[i], piece));
        }
        for (int i = 0; i < pieceConfig.black_positions.size(); i++)
        {
            Piece piece = {pieceConfig.type, black, pieceConfig.movement};
            board.insert(std::make_pair(pieceConfig.black_positions[i], piece));
        }
    }
};

bool ChessBoard::movePiece(Position source, Position target)
{
    if (!board.contains(source))
    {
        std::cout << "Invalid move, please move a valid piece." << std::endl;
        return false;
    }
    std::string color = board.at(source).color;
    MoveValidator validator(this);

    if (!validator.isPathValid(source, target))
    {
        return false;
    }
    if (!validator.isMoveValid(source, target))
    {
        return false;
    }
    if (portalSystem->portals.contains(target))
    {
        if (!portalSystem->isTeleportValid(board.at(source), portalSystem->portals.at(target)) && !board.contains(target))
        {
            std::cout << "You landed on a portal but you can not use this one." << std::endl;
        }
        else
        {
            if (!board.contains(target))
            {
                board.insert(std::make_pair(target, board.at(source)));
                board.erase(source);
                portalSystem->teleportPiece(target);
                return true;
            }
            else if (board.at(target).color == board.at(source).color)
            {
                std::cout << "Invalid move, you can not teleport there." << std::endl;
                return false;
            }
            else
            {
                ChessBoard::capturePiece(source, target);
            }
        }
    }
    // target portal mı diye bak
    if (!board.at(source).hasMoved)
    {
        board.at(source).hasMoved = true;
    }
    if (!board.contains(target))
    {
        board.insert(std::make_pair(target, board.at(source)));
        board.erase(source);
    }
    else if (board.at(target).color == board.at(source).color)
    {
        return false;
    }
    else
    {
        ChessBoard::capturePiece(source, target);
    }
    /*
    Position ourKing =  pieceFinder("King", color)[0];
    std::cout << ourKing.x << " " << ourKing.y << std::endl;

    if (isCellThreatenedBy(ourKing, color == "White" ? "Black" : "White"))
    {
        std::cout << "Threat? " << std::endl;
        board.insert(std::make_pair(source, board.at(target)));
        board.erase(target);
        std::cout << "Invalid move, your king being checked." << std::endl;
        return false;
    }*/
    return true;
};

bool ChessBoard::capturePiece(Position source, Position target)
{
    board.at(target) = board.at(source);
    board.erase(source);
    return true;
};

void ChessBoard::printBoardStatus()
{
    std::cout << "+";
    for (int k = 0; k < gameSettings->board_size; k++)
    {
        std::cout << "---+";
    }
    std::cout << std::endl;

    std::vector<Position> portalExits;

    for (int row = gameSettings->board_size - 1; row >= 0; row--)
    {

        std::cout << "|";
        for (int col = 0; col < gameSettings->board_size; col++)
        {

            std::cout << " ";

            Position checkPos;
            checkPos.x = col;
            checkPos.y = row;

            if (board.contains(checkPos))
            {
                if (board.at(checkPos).type == "Pawn")
                {
                    if (board.at(checkPos).color == "White")
                    {
                        if (portalSystem->portals.contains(checkPos))
                        {
                            std::cout << "\033[32m" << "P" << "\033[0m";
                        }
                        else if (portalSystem->portalExits.contains(checkPos))
                        {
                            std::cout << "\033[31m" << "P" << "\033[0m";
                        }
                        else
                            std::cout << "\033[1m\033[37m" << "P" << "\033[0m";
                    }
                    else if (board.at(checkPos).color == "Black")
                    {
                        if (portalSystem->portals.contains(checkPos))
                        {
                            std::cout << "\033[32m" << "p" << "\033[0m";
                        }
                        else if (portalSystem->portalExits.contains(checkPos))
                        {
                            std::cout << "\033[31m" << "p" << "\033[0m";
                        }
                        else
                            std::cout << "\033[1m\033[35m" << "p" << "\033[0m";
                    }
                }
                else if (board.at(checkPos).type == "Rook")
                {
                    if (board.at(checkPos).color == "White")
                    {
                        if (portalSystem->portals.contains(checkPos))
                        {
                            std::cout << "\033[32m" << "R" << "\033[0m";
                        }
                        else if (portalSystem->portalExits.contains(checkPos))
                        {
                            std::cout << "\033[31m" << "R" << "\033[0m";
                        }
                        else
                            std::cout << "\033[1m\033[37m" << "R" << "\033[0m";
                    }
                    else
                    {
                        if (portalSystem->portals.contains(checkPos))
                        {
                            std::cout << "\033[32m" << "r" << "\033[0m";
                        }
                        else if (portalSystem->portalExits.contains(checkPos))
                        {
                            std::cout << "\033[31m" << "r" << "\033[0m";
                        }
                        else
                            std::cout << "\033[1m\033[35m" << "r" << "\033[0m";
                    }
                }
                else if (board.at(checkPos).type == "Knight")
                {
                    if (board.at(checkPos).color == "White")
                    {
                        if (portalSystem->portals.contains(checkPos))
                        {
                            std::cout << "\033[32m" << "N" << "\033[0m";
                        }
                        else if (portalSystem->portalExits.contains(checkPos))
                        {
                            std::cout << "\033[31m" << "N" << "\033[0m";
                        }
                        else
                            std::cout << "\033[1m\033[37m" << "N" << "\033[0m";
                    }
                    else
                    {
                        if (portalSystem->portals.contains(checkPos))
                        {
                            std::cout << "\033[32m" << "n" << "\033[0m";
                        }
                        else if (portalSystem->portalExits.contains(checkPos))
                        {
                            std::cout << "\033[31m" << "n" << "\033[0m";
                        }
                        else
                            std::cout << "\033[1m\033[35m" << "n" << "\033[0m";
                    }
                }
                else if (board.at(checkPos).type == "Bishop")
                {
                    if (board.at(checkPos).color == "White")
                    {
                        if (portalSystem->portals.contains(checkPos))
                        {
                            std::cout << "\033[32m" << "B" << "\033[0m";
                        }
                        else if (portalSystem->portalExits.contains(checkPos))
                        {
                            std::cout << "\033[31m" << "B" << "\033[0m";
                        }
                        else
                            std::cout << "\033[1m\033[37m" << "B" << "\033[0m";
                    }
                    else
                    {
                        if (portalSystem->portals.contains(checkPos))
                        {
                            std::cout << "\033[32m" << "b" << "\033[0m";
                        }
                        else if (portalSystem->portalExits.contains(checkPos))
                        {
                            std::cout << "\033[31m" << "b" << "\033[0m";
                        }
                        else
                            std::cout << "\033[1m\033[35m" << "b" << "\033[0m";
                    }
                }
                else if (board.at(checkPos).type == "Queen")
                {
                    if (board.at(checkPos).color == "White")
                    {
                        if (portalSystem->portals.contains(checkPos))
                        {
                            std::cout << "\033[32m" << "Q" << "\033[0m";
                        }
                        else if (portalSystem->portalExits.contains(checkPos))
                        {
                            std::cout << "\033[31m" << "Q" << "\033[0m";
                        }
                        else
                            std::cout << "\033[1m\033[37m" << "Q" << "\033[0m";
                    }
                    else
                    {
                        if (portalSystem->portals.contains(checkPos))
                        {
                            std::cout << "\033[32m" << "q" << "\033[0m";
                        }
                        else if (portalSystem->portalExits.contains(checkPos))
                        {
                            std::cout << "\033[31m" << "q" << "\033[0m";
                        }
                        else
                            std::cout << "\033[1m\033[35m" << "q" << "\033[0m";
                    }
                }
                else if (board.at(checkPos).type == "King")
                {
                    if (board.at(checkPos).color == "White")
                    {
                        if (portalSystem->portals.contains(checkPos))
                        {
                            std::cout << "\033[32m" << "K" << "\033[0m";
                        }
                        else if (portalSystem->portalExits.contains(checkPos))
                        {
                            std::cout << "\033[31m" << "K" << "\033[0m";
                        }
                        else
                            std::cout << "\033[1m\033[37m" << "K" << "\033[0m";
                    }
                    else
                    {
                        if (portalSystem->portals.contains(checkPos))
                        {
                            std::cout << "\033[32m" << "k" << "\033[0m";
                        }
                        else if (portalSystem->portalExits.contains(checkPos))
                        {
                            std::cout << "\033[31m" << "k" << "\033[0m";
                        }
                        else
                            std::cout << "\033[1m\033[35m" << "k" << "\033[0m";
                    }
                }
            }
            else if (portalSystem->portals.contains(checkPos))
            {
                portalExits.push_back(portalSystem->portals.at(checkPos).exit);
                std::cout << "\033[32m" << portalSystem->portals.at(checkPos).id << "\033[0m";
            }
            else if (portalSystem->portalExits.contains(checkPos))
            {
                std::cout << "\033[31m" << portalSystem->portalExits.at(checkPos).id << "\033[0m";
            }
            else
                std::cout << " ";
            std::cout << " ";
            std::cout << "|";
        }
        std::cout << " " << row << std::endl;

        std::cout << "+";
        for (int k = 0; k < gameSettings->board_size; k++)
        {
            std::cout << "---+";
        }
        if (row > 0)
            std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "  " << "0";
    for (int k = 1; k < gameSettings->board_size; k++)
    {
        std::cout << "   " << k;
    }
};

std::vector<Position> ChessBoard::pieceFinder(std::string pieceType, std::string color)
{
    std::vector<Position> positions;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Position position;
            position.x = j;
            position.y = i;

            if (board.count(position) > 0)
            {
                if (color == "all")
                {
                    if (board.at(position).type == pieceType)
                    {
                        positions.push_back(position);
                    }
                }
                else
                {
                    if (board.at(position).type == pieceType &&
                        board.at(position).color == color)
                    {
                        positions.push_back(position);
                    }
                }
            }
        }
    }
    return positions;
}

bool ChessBoard::isCellThreatenedBy(Position cell, std::string color)
{
    for (auto const &chessPiece : board)
    {
        if (chessPiece.second.color == color)
        {
            std::cout << "Düşman rengi uyuştu" << std::endl;
            MoveValidator validator(this);
            if (chessPiece.second.movement.diagonal_capture == 1)
            {
                std::cout << "Diyagonal capture" << std::endl;
                int side_diff = abs(cell.x - chessPiece.first.x);
                int vertical_diff = abs(cell.y - chessPiece.first.y);
                if (side_diff == 1 && vertical_diff == 1)
                {
                    return true;
                }
            }
            std::cout << "Diyagonal capture değil" << std::endl;
            if (validator.isMoveValid(chessPiece.first, cell) && validator.isPathValid(chessPiece.first, cell))
            {
                std::cout << "Move valid ve path valid" << std::endl;
                std::cout << chessPiece.first.x << " " << chessPiece.first.y << std::endl;
                std::cout << cell.x << " " << cell.y << std::endl;
                std::cout << chessPiece.second.type << std::endl;
                return true;
            }
        }
    }
    return false;
}
