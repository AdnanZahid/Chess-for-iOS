//
//  KnightStrategy.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

#include "Piece.cpp"

class KnightStrategy : public PieceStrategy {
    
private:
    void setColor(Color color) {
        this->color = color;
    }
    
    void setPosition(Position position) {
        this->centralBitboard->clearPreviousPosition(*this->decentralBitboard);
        this->centralBitboard->clearPreviousKnightPosition(this->decentralBitboard);
        this->position = position;
        
        this->decentralBitboard->setPosition(this->position);
        this->centralBitboard->setKnightPosition(this->decentralBitboard);
    }
    
    void updateMoves() {
        this->decentralBitboard->setMoves(this->getMoves(this->position));
        this->centralBitboard->setKnightMoves(this->decentralBitboard);
    }
    
    std::list<Position> getMoves(Position position) {
        
        this->mobility = 0;
        std::list<Position> movesList;
        
        if (position.file > 'a') {
            if (position.rank > '2') {
                Position toOneLeftTwoBackwardStep = { (char)(position.rank - 2), (char)(position.file - 1) };
                movesList = this->addMoveToList(position, toOneLeftTwoBackwardStep, movesList);
            }
            
            if (position.rank < '7') {
                Position toOneLeftTwoForwardStep = { (char)(position.rank + 2), (char)(position.file - 1) };
                movesList = this->addMoveToList(position, toOneLeftTwoForwardStep, movesList);
            }
            
            if (position.file > 'b') {
                if (position.rank > '1') {
                    Position toTwoLeftOneBackwardStep = { (char)(position.rank - 1), (char)(position.file - 2) };
                    movesList = this->addMoveToList(position, toTwoLeftOneBackwardStep, movesList);
                }
                
                if (position.rank < '8') {
                    Position toTwoLeftOneForwardStep = { (char)(position.rank + 1), (char)(position.file - 2) };
                    movesList = this->addMoveToList(position, toTwoLeftOneForwardStep, movesList);
                }
            }
        }
        
        if (position.file < 'h') {
            if (position.rank > '2') {
                Position toOneRightTwoBackwardStep = { (char)(position.rank - 2), (char)(position.file + 1) };
                movesList = this->addMoveToList(position, toOneRightTwoBackwardStep, movesList);
            }
            
            if (position.rank < '7') {
                Position toOneRightTwoForwardStep = { (char)(position.rank + 2), (char)(position.file + 1) };
                movesList = this->addMoveToList(position, toOneRightTwoForwardStep, movesList);
            }
            
            if (position.file < 'g') {
                if (position.rank > '1') {
                    Position toTwoRightOneBackwardStep = { (char)(position.rank - 1), (char)(position.file + 2) };
                    movesList = this->addMoveToList(position, toTwoRightOneBackwardStep, movesList);
                }
                
                if (position.rank < '8') {
                    Position toTwoRightOneForwardStep = { (char)(position.rank + 1), (char)(position.file + 2) };
                    movesList = this->addMoveToList(position, toTwoRightOneForwardStep, movesList);
                }
            }
        }
        
        return movesList;
    }
    
public:
    KnightStrategy(Board *board) : PieceStrategy(board) {
    }
    
    bool move(Position from, Position to) {
        
        Piece *destinationPiece = this->board->getPieceOnPosition(to);
        
        if (destinationPiece == nullptr || destinationPiece->color != this->color) {
            if (std::fabs(from.file - to.file) == 2 && std::fabs(from.rank - to.rank) == 1) {
                
                return true;
                
            } else if (std::fabs(from.rank - to.rank) == 2 && std::fabs(from.file - to.file) == 1) {
                
                return true;
            }
        }
        
        return false;
    }
};