//
//  KnightStrategy.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "../../Headers/KnightStrategy.hpp"

KnightStrategy::void setColor(Color color) {
    this->color = color;
}

KnightStrategy::void setPosition(Position position) {
    this->centralBitboard->clearPreviousPosition(*this->decentralBitboard);
    this->centralBitboard->clearPreviousKnightPosition(this->decentralBitboard);
    this->position = position;
    
    this->decentralBitboard->setPosition(this->position);
    this->centralBitboard->setKnightPosition(this->decentralBitboard);
}

KnightStrategy::void updateMoves() {
    this->decentralBitboard->setMoves(this->getMoves(this->position));
    this->centralBitboard->setKnightMoves(this->decentralBitboard);
}

KnightStrategy::LinkedList<Position> *getMoves(Position position) {
    
    this->mobility = 0;
    LinkedList<Position> *movesList = new LinkedList<Position>();
    
    if (position.file > 'a') {
        if (position.rank > '2') {
            Position toOneLeftTwoBackwardStep = { (char)(position.rank - 2), (char)(position.file - 1) };
            this->addMoveToList(position, toOneLeftTwoBackwardStep, movesList);
        }
        
        if (position.rank < '7') {
            Position toOneLeftTwoForwardStep = { (char)(position.rank + 2), (char)(position.file - 1) };
            this->addMoveToList(position, toOneLeftTwoForwardStep, movesList);
        }
        
        if (position.file > 'b') {
            if (position.rank > '1') {
                Position toTwoLeftOneBackwardStep = { (char)(position.rank - 1), (char)(position.file - 2) };
                this->addMoveToList(position, toTwoLeftOneBackwardStep, movesList);
            }
            
            if (position.rank < '8') {
                Position toTwoLeftOneForwardStep = { (char)(position.rank + 1), (char)(position.file - 2) };
                this->addMoveToList(position, toTwoLeftOneForwardStep, movesList);
            }
        }
    }
    
    if (position.file < 'h') {
        if (position.rank > '2') {
            Position toOneRightTwoBackwardStep = { (char)(position.rank - 2), (char)(position.file + 1) };
            this->addMoveToList(position, toOneRightTwoBackwardStep, movesList);
        }
        
        if (position.rank < '7') {
            Position toOneRightTwoForwardStep = { (char)(position.rank + 2), (char)(position.file + 1) };
            this->addMoveToList(position, toOneRightTwoForwardStep, movesList);
        }
        
        if (position.file < 'g') {
            if (position.rank > '1') {
                Position toTwoRightOneBackwardStep = { (char)(position.rank - 1), (char)(position.file + 2) };
                this->addMoveToList(position, toTwoRightOneBackwardStep, movesList);
            }
            
            if (position.rank < '8') {
                Position toTwoRightOneForwardStep = { (char)(position.rank + 1), (char)(position.file + 2) };
                this->addMoveToList(position, toTwoRightOneForwardStep, movesList);
            }
        }
    }
    
    return movesList;
}

KnightStrategy::KnightStrategy(Board *board) : PieceStrategy(board) {
}

KnightStrategy::bool move(Position from, Position to) {
    
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