#include "../include/ChessBoard.hpp"

ChessBoard::ChessBoard(std::vector<PieceConfig> pieceConfigs)
{

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
    if(!board.contains(source)){
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
    if (!board.at(source).hasMoved)
    {
        board.at(source).hasMoved = true;
    }
    if (!board.contains(target))
    {
        board.insert(std::make_pair(target, board.at(source)));
        board.erase(source);
    }
    // else if (board.at(target).color == board.at(source).color)
    // {
    //     return false;
    // }
    else
    {
        ChessBoard::capturePiece(source, target);
    }
    Position ourKing =  pieceFinder("King", color)[0];
    std::cout << ourKing.x << " " << ourKing.y << std::endl;

    if (isCellThreatenedBy(ourKing, color == "White" ? "Black" : "White"))
    {
        std::cout << "Threat? " << std::endl;
        board.insert(std::make_pair(source, board.at(target)));
        board.erase(target);
        std::cout << "Invalid move, your king being checked." << std::endl;
        return false;
    }
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
    std::cout << "+---+---+---+---+---+---+---+---+" << std::endl;
    for (int row = 7; row >= 0; row--)
    {
        // Print pieces row
        std::cout << "|";
        for (int col = 0; col < 8; col++)
        {

            std::cout << " ";
            // Here you can add logic to print pieces
            Position checkPos;
            checkPos.x = col;
            checkPos.y = row;
            if (board.contains(checkPos))
            {
                if (board.at(checkPos).type == "Pawn")
                {
                    if (board.at(checkPos).color == "White")
                    {
                        std::cout << "P";
                    }
                    else if (board.at(checkPos).color == "Black")
                    {
                        std::cout << "p";
                    }
                }
                else if (board.at(checkPos).type == "Rook")
                {
                    if (board.at(checkPos).color == "White")
                    {
                        std::cout << "R";
                    }
                    else
                    {
                        std::cout << "r";
                    }
                }
                else if (board.at(checkPos).type == "Knight")
                {
                    if (board.at(checkPos).color == "White")
                    {
                        std::cout << "N";
                    }
                    else
                    {
                        std::cout << "n";
                    }
                }
                else if (board.at(checkPos).type == "Bishop")
                {
                    if (board.at(checkPos).color == "White")
                    {
                        std::cout << "B";
                    }
                    else
                    {
                        std::cout << "b";
                    }
                }
                else if (board.at(checkPos).type == "Queen")
                {
                    if (board.at(checkPos).color == "White")
                    {
                        std::cout << "Q";
                    }
                    else
                    {
                        std::cout << "q";
                    }
                }
                else if (board.at(checkPos).type == "King")
                {
                    if (board.at(checkPos).color == "White")
                    {
                        std::cout << "K";
                    }
                    else
                    {
                        std::cout << "k";
                    }
                }
            }
            else
                std::cout << " ";
            std::cout << " ";
            std::cout << "|";
        }
        std::cout << " " << row << std::endl;

        // Print horizontal border
        std::cout << "+---+---+---+---+---+---+---+---+";
        if (row > 0)
            std::cout << std::endl;
    }

    // Print column labels
    std::cout << std::endl;
    std::cout << "  0   1   2   3   4   5   6   7" << std::endl;
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
