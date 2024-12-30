#include "../include/ConfigReader.hpp"
#include <vector>
#include <string>
#include <unordered_map>


struct Piece{
    std::string type;
    std::string color;
    MovementRules movement;
};

class ChessBoard {
    public: 
    ChessBoard(PieceConfig pieceConfig, char* argv[]) {
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
    }

    void movePiece(Position source, Position target);
    void printBoardStatus();

};