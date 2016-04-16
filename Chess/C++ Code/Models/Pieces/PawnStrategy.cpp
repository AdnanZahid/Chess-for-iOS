//
//  Pawn.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

#include "../../Others/Constants.cpp"
#include "Piece.cpp"

class PawnStrategy : public PieceStrategy {

private:
    int oneStep = 1;
    int twoStep = 2;
    
    void setColor(Color color) {
        
        this->color = color;
        
        if (color == black) {
            
            oneStep *= -1;
            twoStep *= -1;
        }
    }
    
    void setPosition(Position position) {
        this->centralBitboard->clearPreviousPosition(*this->decentralBitboard);
        this->centralBitboard->clearPreviousPawnPosition(this->decentralBitboard);
        this->position = position;
        
        this->decentralBitboard->setPosition(this->position);
        this->centralBitboard->setPawnPosition(this->decentralBitboard);
    }
    
    void updateMoves() {
        this->decentralBitboard->setMoves(this->getMoves(this->position));
        this->centralBitboard->setPawnMoves(this->decentralBitboard);
    }
    
    std::list<Position> getMoves(Position position) {
        
        this->mobility = 0;
        std::list<Position> movesList;
        
        if ((this->color == white && position.rank < RANK_SEVEN) || (this->color == black && position.rank > RANK_TWO)) {
            if ((this->color == white && position.rank < RANK_EIGHT) || (this->color == black && position.rank > RANK_ONE)) {
                Position toOneStep = { (char)(position.rank + oneStep), position.file };
                movesList = this->addMoveToList(position, toOneStep, movesList);
                
                if (position.file > FILE_A) {
                    Position toOneLeftStep = { (char)(position.rank + oneStep), (char)(position.file - 1) };
                    movesList = this->addMoveToList(position, toOneLeftStep, movesList);
                }
                
                if (position.file < FILE_H) {
                    Position toOneRightStep = { (char)(position.rank + oneStep), (char)(position.file + 1) };
                    movesList = this->addMoveToList(position, toOneRightStep, movesList);
                }
            }
            Position toTwoStep = { (char)(position.rank + twoStep), position.file };
            movesList = this->addMoveToList(position, toTwoStep, movesList);
        }
        
        return movesList;
    }
    
public:
    PawnStrategy(Board *board) : PieceStrategy(board) {
    }
    
    bool move(Position from, Position to) {
        
        Piece *destinationPiece = this->board->getPieceOnPosition(to);
        
        if (destinationPiece == nullptr || destinationPiece->color != this->color) {
            
            if (from.file == to.file && (this->board->getPieceOnPosition(to) == nullptr || this->board->getPieceOnPosition(to)->value == KING)) {
                
                Position tempPosition = from;
                tempPosition.rank += oneStep;
                
                if (from.rank + oneStep == to.rank) {
                    
                    return true;
                    
                } else if (from.rank + twoStep == to.rank && this->hasMoved == false && this->board->getPieceOnPosition(tempPosition) == nullptr) {
                    
                    this->isEnPassant = true;
                    return true;
                }
            } else if (std::fabs(from.file - to.file) == 1 && from.rank + oneStep == to.rank) {
                
                Position tempPosition = to;
                tempPosition.rank -= oneStep;
                
                Piece *piece = this->board->getPieceOnPosition(tempPosition);
                if (this->board->getPieceOnPosition(to) != nullptr) {
                    
                    return true;
                } else if (from.rank == 5 && this->board->getPieceOnPosition(to) == nullptr && piece != nullptr && std::fabs(piece->value) == PAWN && piece->pieceStrategy->isEnPassant == true) {
                    piece->value = 0;
                    piece = nullptr;
                    
                    return true;
                }
            }
        }
        
        return false;
    }
};