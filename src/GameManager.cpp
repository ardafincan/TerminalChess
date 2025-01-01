#include "../include/GameManager.hpp"

GameManager::GameManager(ChessBoard* board){
    chessBoard = board;
}

void GameManager::chessGame(){

    
}

bool GameManager::TurnProcessor(){
    std::string color = chessBoard->board.at(moveHistory.back().source).color;
    if(moveHistory.empty()){
        return true;
    }else if(color == "White"){
        return false;
    }else{
        return true;
    };
}