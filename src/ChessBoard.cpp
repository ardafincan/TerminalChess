#include "../include/ChessBoard.hpp"
#include "../include/ConfigReader.hpp"

    ChessBoard::ChessBoard(PieceConfig pieceConfig, char* argv[]) {
        std::unordered_map<Position, Piece> board; 
        ConfigReader reader(argv[1]);
        
        for(int i = 0; i < reader.getPieceConfigs().size(); i++){
            for(int i = 0; i < pieceConfig.white_positions.size(); i++){
                Piece piece = {pieceConfig.type, "white", pieceConfig.movement};
                board.insert(std::make_pair(pieceConfig.white_positions[i], piece));
            }
            for(int i = 0; i < pieceConfig.black_positions.size(); i++){
                Piece piece = {pieceConfig.type, "white", pieceConfig.movement};
                board.insert(std::make_pair(pieceConfig.white_positions[i], piece));
            }
        }
    };
