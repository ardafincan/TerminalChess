#include "../include/ChessBoard.hpp"

    ChessBoard::ChessBoard(std::vector<PieceConfig> pieceConfigs) {

        for(int j = 0; j < pieceConfigs.size(); j++){
            PieceConfig pieceConfig = pieceConfigs[j];
            std::string white = "White";
            std::string black = "Black";

            for(int i = 0; i < pieceConfig.white_positions.size(); i++){
                Piece piece = {pieceConfig.type, white, pieceConfig.movement};
                board.insert(std::make_pair(pieceConfig.white_positions[i], piece));
            }
            for(int i = 0; i < pieceConfig.black_positions.size(); i++){
                Piece piece = {pieceConfig.type, black, pieceConfig.movement};
                board.insert(std::make_pair(pieceConfig.black_positions[i], piece));
            }
        }
    };

    bool ChessBoard::movePiece(Position source, Position target){
        MoveValidator validator(this);
        
        if(!validator.isMoveValid(source, target) || !validator.isPathValid(source, target)){
            return false;
        }
        if(!board.at(source).hasMoved){
            board.at(source).hasMoved = true;
        }
        //implement here if condition checking if source exists and target position is within chess board
        if(!board.contains(target)){
            board.insert(std::make_pair(target, board.at(source)));
            board.erase(source);
        }else if(board.at(target).color == board.at(source).color){
            return false;
        }else{
            ChessBoard::capturePiece(source, target);
        }
    };

    bool ChessBoard::capturePiece(Position source, Position target){
        board.at(target) = board.at(source);
        board.erase(source);
    };

    void ChessBoard::printBoardStatus(){
        std::cout << "+---+---+---+---+---+---+---+---+" << std::endl;
        for (int row = 7; row >= 0; row--) {
            // Print pieces row
            std::cout << "|";
            for (int col = 0; col < 8; col++) {

                std::cout << " ";
                // Here you can add logic to print pieces
                Position checkPos;
                checkPos.x = col;
                checkPos.y = row;
                if(board.contains(checkPos)){
                    if (board.at(checkPos).type == "Pawn") {
                        if (board.at(checkPos).color == "White") {
                            std::cout << "P";
                        } else {
                            std::cout << "p";
                        }
                    } else if (board.at(checkPos).type == "Rook") {
                        if (board.at(checkPos).color == "White") {
                            std::cout << "R";
                        } else {
                            std::cout << "r";
                        }
                    } else if (board.at(checkPos).type == "Knight") {
                        if (board.at(checkPos).color == "White") {
                            std::cout << "N";
                        } else {
                            std::cout << "n";
                        }
                    } else if (board.at(checkPos).type == "Bishop") {
                        if (board.at(checkPos).color == "White") {
                            std::cout << "B";
                        } else {
                            std::cout << "b";
                        }
                    }else if (board.at(checkPos).type == "Queen") {
                        if (board.at(checkPos).color == "White") {
                            std::cout << "Q";
                        } else {
                            std::cout << "q";
                        }
                    }else if (board.at(checkPos).type == "King") {
                        if (board.at(checkPos).color == "White") {
                            std::cout << "K";
                        } else {
                            std::cout << "k";
                        }
                    }
                }else std::cout << " ";
                std::cout << " ";
                std::cout << "|";
            }
            std::cout << " " << row << std::endl;
            
            // Print horizontal border
            std::cout << "+---+---+---+---+---+---+---+---+";
            if (row > 0) std::cout << std::endl;
        }
    
        // Print column labels
        std::cout << std::endl;
        std::cout << "  0   1   2   3   4   5   6   7" << std::endl;
    };

    std::vector<Position> ChessBoard::pieceFinder(std::string pieceType, std::string color = "all"){
        std::vector<Position> positions;
        for(int i = 0; i < 7; i++){
            for(int j = 0; j < 7; j++){
                Position position;
                position.x = j;
                position.y = i;
                if(color == "all"){
                    if(board.at(position).type == pieceType){
                        positions.push_back(position);
                    }
                }else{
                    if(board.at(position).type == pieceType && board.at(position).color == color){
                        positions.push_back(position);
                    }
                }
            }
        }
    }
