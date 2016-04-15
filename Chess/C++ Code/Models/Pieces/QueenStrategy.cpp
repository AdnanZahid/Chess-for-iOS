//
//  QueenStrategy.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

#include "../../Others/Constants.cpp"
#include "RookStrategy.cpp"
#include "BishopStrategy.cpp"

class QueenStrategy : public PieceStrategy {
    
private:
    void setColor(Color color) {
        this->color = color;
    }
    
    void setPosition(Position position) {
        this->centralBitboard->clearPreviousPosition(*this->decentralBitboard);
        this->centralBitboard->clearPreviousQueenPosition(this->decentralBitboard);
        this->position = position;
        
        this->decentralBitboard->setPosition(this->position);
        this->centralBitboard->setQueenPosition(this->decentralBitboard);
    }
    
    void updateMoves() {
        this->decentralBitboard->setMoves(this->getMoves(this->position));
        this->centralBitboard->setQueenMoves(this->decentralBitboard);
    }
    
    std::list<Position> getMoves(Position position) {
        
        this->mobility = 0;
        std::list<Position> movesList;
        movesList = BishopStrategy::getMoves(this, movesList);
        movesList = RookStrategy::getMoves(this, movesList);
        return movesList;
    }
    
public:
    QueenStrategy(Board *board) : PieceStrategy(board) {
    }
    
    bool move(Position from, Position to) {
        
        Piece *destinationPiece = this->board->getPieceOnPosition(to);
        
        if (destinationPiece == nullptr || destinationPiece->color != this->color) {
            if (RookStrategy::move(this->board, from, to)) {
                return true;
            } else if (BishopStrategy::move(this->board, from, to)) {
                return true;
            }
        }
        
        return false;
    }
};