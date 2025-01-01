#include "../include/GameManager.hpp"

GameManager::GameManager(ChessBoard *board)
{
    chessBoard = board;
}

int GameManager::whoWon()
{
    if (chessBoard->pieceFinder("King", "White").empty())
    {
        return 1;
    }
    else if (chessBoard->pieceFinder("King", "Black").empty())
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

void GameManager::chessGame()
{
    int anyWinner = whoWon();

    while (anyWinner == 0)
    {
        chessBoard->printBoardStatus();
        Position source;
        Position target;
        if (blackTurn == false)
        {
            std::cout << "\nWhite's turn" << std::endl;
            std::cout << "\nEnter source position: ";
            std::cin >> source.x >> source.y;
            std::cout << "\nEnter target position: ";
            std::cin >> target.x >> target.y;
            if (chessBoard->board.at(source).color == "White" && chessBoard->movePiece(source, target))
            {
                blackTurn = true;
            }

            else
            {
                std::cout << "Invalid move, try again" << std::endl;
            }
        }
        else
        {
            std::cout << "\nBlack's turn" << std::endl;
            std::cout << "\nEnter source position: ";
            std::cin >> source.x >> source.y;
            std::cout << "\nEnter target position: ";
            std::cin >> target.x >> target.y;
            if (chessBoard->board.at(source).color == "Black" && chessBoard->movePiece(source, target))
            {
                blackTurn = false;
            }
            else
            {
                std::cout << "Invalid move, try again" << std::endl;
            }
        }
    }
    if (anyWinner == 1)
    {
        std::cout << "Black wins!" << std::endl;
    }
    else
    {
        std::cout << "White wins!" << std::endl;
    };
}