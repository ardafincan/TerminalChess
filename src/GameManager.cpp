#include "../include/GameManager.hpp"

GameManager::GameManager(ChessBoard* board){
    chessBoard = board;
}


bool GameManager::TurnProcessor(){
    std::string color;
    if(!moveHistory.empty()){
        color = chessBoard->board.at(moveHistory.back().source).color;
    }
    if(moveHistory.empty()){
        return true;
    }else if(color == "White"){
        return false;
    }else{
        return true;
    };
}


int GameManager::whoWon(){
    if(chessBoard->pieceFinder("King", "White").empty()){
        return 1;
    }else if(chessBoard->pieceFinder("King", "Black").empty()){
        return 2;
    }else{
        return 0;
    }
}

void GameManager::chessGame(){
    while(whoWon() == 0){
        chessBoard->printBoardStatus();
        Position source;
        Position target;
        if(TurnProcessor()){
            std::cout << "\nWhite's turn" << std::endl;
            std::cout << "\nEnter source position: ";
            std::cin >> source.x >> source.y;
            std::cout << "\nEnter target position: ";
            std::cin >> target.x >> target.y;
            if(chessBoard->board.at(source).color == "White"){
                if(chessBoard->movePiece(source, target)){
                    moveHistory.push_back({source, target});
                }else{
                    std::cout << "Invalid move, try again" << std::endl;
                }
        } else {
            std::cout << "\nBlack's turn" << std::endl;
            std::cout << "\nEnter source position: ";
            std::cin >> source.x >> source.y;
            std::cout << "\nEnter target position: ";
            std::cin >> target.x >> target.y;
            if(chessBoard->board.at(source).color == "Black"){
                if(chessBoard->movePiece(source, target)){
                    moveHistory.push_back({source, target});
                }else{
                    std::cout << "Invalid move, try again" << std::endl;
                }
            }
        };
    }
    if(whoWon() == 1){
        std::cout << "Black wins!" << std::endl;
    }else{
        std::cout << "White wins!" << std::endl;
    };
}
}