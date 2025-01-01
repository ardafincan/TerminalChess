#include "../include/MoveValidator.hpp"

MoveValidator::MoveValidator(ChessBoard *board)
    : chessBoard(*board), board(board) {};

bool MoveValidator::isMoveValid(Position source, Position target)
{
    int side_diff = abs(target.x - source.x);
    int vertical_diff = abs(target.y - source.y);

    std::cout << "ilk adımmlar mı???" << chessBoard.board.at(source).hasMoved << std::endl;
    if (source.x == target.x)
    {
        if (!chessBoard.board.at(source).hasMoved && chessBoard.board.at(source).movement.first_move_forward >= vertical_diff)
        {
            return true;
        }
        return (chessBoard.board.at(source).movement.forward >= vertical_diff);
    }
    if (source.y == target.y)
    {
        return (chessBoard.board.at(source).movement.sideways >= side_diff);
    }
    if (side_diff == vertical_diff)
    {
        if (side_diff == 1 && chessBoard.board.contains(target))
        {
            return (chessBoard.board.at(source).movement.diagonal_capture == 1);
        }
        return (chessBoard.board.at(source).movement.diagonal >= side_diff);
    }
    if ((side_diff == 2 && vertical_diff == 1) || (side_diff == 1 && vertical_diff == 2))
    {
        return (chessBoard.board.at(source).movement.l_shape);
    }

    // şah mı bak
    return true;
}

bool MoveValidator::isPathValid(Position source, Position target)
{
    int side_diff = abs(target.x - source.x);
    int vertical_diff = abs(target.y - source.y);

    int start_point = 0;
    int end_point = 0;

    if (side_diff == 0)
    {
        if (target.y > source.y)
        {
            end_point = target.y;
            start_point = source.y;
        }
        else if (source.y > target.y)
        {
            end_point = source.y;
            start_point = target.y;
        }
        for (int i = start_point + 1; i < end_point; i++)
        {
            Position checkPos;
            checkPos.x = source.x;
            checkPos.y = i;
            if (chessBoard.board.contains(checkPos))
            {
                return false;
            }
        }
    }

    if (vertical_diff == 0)
    {
        if (target.x > source.x)
        {
            end_point = target.x;
            start_point = source.x;
        }
        else if (source.x > target.x)
        {
            end_point = source.x;
            start_point = target.x;
        }
        for (int i = start_point + 1; i < end_point; i++)
        {
            Position checkPos;
            checkPos.x = i;
            checkPos.y = source.y;
            if (chessBoard.board.contains(checkPos))
            {
                return false;
            }
        }
    }
    if (side_diff == vertical_diff)
    {
        if (target.x > source.x)
        {
            for (int i = 1; source.x + i < target.x; i++)
            {
                Position checkPos;
                checkPos.x = source.x + i;
                checkPos.y = source.y + i;
                if (chessBoard.board.contains(checkPos))
                {
                    return false;
                }
            }
        }
        else if (source.x > target.x)
        {
            for (int i = 1; target.x + i < source.x; i++)
            {
                Position checkPos;
                checkPos.x = target.x + i;
                checkPos.y = target.y + i;
                if (chessBoard.board.contains(checkPos))
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool MoveValidator::isPossibleMove(Position source, Position target){
    bool isKingChecked = false;
    chessBoard.board.insert(std::make_pair(target, chessBoard.board.at(source)));
    chessBoard.board.erase(source);

    if (chessBoard.isCellThreatenedBy(chessBoard.pieceFinder("King", chessBoard.board.at(source).color)[0], chessBoard.board.at(source).color == "White" ? "Black": "White"))
    {
        isKingChecked = true;
    }

    chessBoard.board.insert(std::make_pair(source, chessBoard.board.at(target)));
    chessBoard.board.erase(target);

    std::cout << isKingChecked << std::endl;
    return !isKingChecked;
}
    