#include "../include/MoveValidator.hpp"


bool MoveValidator::isMoveValid(Position source, Position target){
        int side_diff = abs(target.x - source.x);
        int vertical_diff = abs(target.y - source.y);

        if(source.x == target.x){
            if(!chessBoard.board.at(source).hasMoved && chessBoard.board.at(source).movement.first_move_forward > vertical_diff){
                return true;
            }
            return (chessBoard.board.at(source).movement.forward >= vertical_diff);
        }
        if(source.y == target.y){
            return (chessBoard.board.at(source).movement.sideways >= side_diff);
        }
        if(side_diff == vertical_diff){
            if(side_diff == 1 && chessBoard.board.contains(target)){
                return (chessBoard.board.at(source).movement.diagonal_capture == 1);
            }
            return (chessBoard.board.at(source).movement.diagonal >= side_diff);
        }
        if((side_diff == 2 && vertical_diff == 1) || (side_diff == 1 && vertical_diff == 2)){
            return (chessBoard.board.at(source).movement.l_shape);
        }

    }

bool MoveValidator::isPathValid(Position source, Position target){
    int side_diff = abs(target.x - source.x);
    int vertical_diff = abs(target.y - source.y);

    if(side_diff == 0){
        if(target.y > source.y){
            for(int i = source.y; i < target.y; i++){
                Position checkPos;
                checkPos.x = source.x;
                checkPos.y = i;
                if(chessBoard.board.contains(checkPos)){
                    return false;
                }
            }
        }else if(source.y > target.y){
            for(int i = target.y; i < source.y; i++){
                Position checkPos;
                checkPos.x = source.x;
                checkPos.y = i;
                if(chessBoard.board.contains(checkPos)){
                    return false;
                }
            }
        }
    }
    if(vertical_diff == 0){
        if(target.x > source.x){
            for(int i = source.x; i < target.x; i++){
                Position checkPos;
                checkPos.x = i;
                checkPos.y = source.y;
                if(chessBoard.board.contains(checkPos)){
                    return false;
                }
            }
        }else if(source.x > target.x){
            for(int i = target.x; i < source.x; i++){
                Position checkPos;
                checkPos.x = i;
                checkPos.y = source.y;
                if(chessBoard.board.contains(checkPos)){
                    return false;
                }
            }
        }
    }
    if( )


}
    