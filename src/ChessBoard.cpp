#include "../include/ChessBoard.hpp"
#include "../include/ConfigReader.hpp"
#include "../include/MoveValidator.hpp"

    ChessBoard::ChessBoard(PieceConfig pieceConfig, char* argv[]) {
        ConfigReader reader(argv[1]);
        
        for(int i = 0; i < reader.getPieceConfigs().size(); i++){

            for(int i = 0; i < pieceConfig.white_positions.size(); i++){
                Piece piece = {pieceConfig.type, "white", pieceConfig.movement};
                board.insert(std::make_pair(pieceConfig.white_positions[i], piece));
            }
            for(int i = 0; i < pieceConfig.black_positions.size(); i++){
                Piece piece = {pieceConfig.type, "black", pieceConfig.movement};
                board.insert(std::make_pair(pieceConfig.white_positions[i], piece));
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
            board.insert(std::make_pair(source, board.at(source)));
            board.erase(source);
        }else if(board.at(target).color == board.at(source).color){
            return false;
        }else{
            ChessBoard::capturePiece(source, target);
        }
    };

    bool ChessBoard::capturePiece(Position source, Position target){
        
    };
