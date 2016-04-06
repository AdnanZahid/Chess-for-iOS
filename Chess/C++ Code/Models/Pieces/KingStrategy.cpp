//
//  KingStrategy.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "../../Headers/KingStrategy.hpp"

KingStrategy::void setColor(Color color) {
    this->color = color;
}

KingStrategy::void setPosition(Position position) {
    this->centralBitboard->clearPreviousPosition(*this->decentralBitboard);
    this->centralBitboard->clearPreviousKingPosition(this->decentralBitboard);
    this->position = position;
    
    this->decentralBitboard->setPosition(this->position);
    this->centralBitboard->setKingPosition(this->decentralBitboard);
}

KingStrategy::void updateMoves() {
    this->decentralBitboard->setMoves(this->getMoves(this->position));
    this->centralBitboard->setKingMoves(this->decentralBitboard);
}

KingStrategy::LinkedList<Position> *getMoves(Position position) {
    
    this->mobility = 0;
    LinkedList<Position> *movesList = new LinkedList<Position>();
    
    if (position.rank > '1') {
        Position toOneForwardStep = { (char)(position.rank - 1), position.file };
        this->addMoveToList(position, toOneForwardStep, movesList);
    }
    
    if (position.rank < '8') {
        Position toOneBackwardStep = { (char)(position.rank + 1), position.file };
        this->addMoveToList(position, toOneBackwardStep, movesList);
    }
    
    if (position.file > 'a') {
        Position toOneLeftStep = { position.rank, (char)(position.file - 1) };
        this->addMoveToList(position, toOneLeftStep, movesList);
        
        if (position.rank > '1') {
            Position toOneLeftBackwardStep = { (char)(position.rank - 1), (char)(position.file - 1) };
            this->addMoveToList(position, toOneLeftBackwardStep, movesList);
        }
        
        if (position.rank < '8') {
            Position toOneLeftForwardStep = { (char)(position.rank + 1), (char)(position.file - 1) };
            this->addMoveToList(position, toOneLeftForwardStep, movesList);
        }
    }
    
    if (position.file < 'h') {
        Position toOneRightStep = { position.rank, (char)(position.file + 1) };
        this->addMoveToList(position, toOneRightStep, movesList);
        
        if (position.rank > '1') {
            Position toOneRightBackwardStep = { (char)(position.rank - 1), (char)(position.file + 1) };
            this->addMoveToList(position, toOneRightBackwardStep, movesList);
        }
        
        if (position.rank < '8') {
            Position toOneRightForwardStep = { (char)(position.rank + 1), (char)(position.file + 1) };
            this->addMoveToList(position, toOneRightForwardStep, movesList);
        }
    }
    
    return movesList;
}

KingStrategy::KingStrategy(Board *board) : PieceStrategy(board) {
}

KingStrategy::bool move(Position from, Position to) {
    
    Piece *destinationPiece = this->board->getPieceOnPosition(to);
    
    if (destinationPiece == nullptr || destinationPiece->color != this->color) {
        Index fromIndex = this->board->positionToIndex(from);
        
        if (std::fabs(from.file - to.file) <= 1 && std::fabs(from.rank - to.rank) <= 1) {
            
            return true;
        
        } else if (this->hasMoved == false) {
            if (to.file == 'c' && from.rank == to.rank) {
                
                if (from.file > from.file) {
                    for (int i = to.file + 1; i < from.file; i ++) {
                        if(this->pieceStrategyDelegate->canCheckDuringPassing(board->indexToPosition(i, fromIndex.y))) {
                            return false;
                        }
                    }
                }
                
                if (this->pieceStrategyDelegate->moveQueenSideRook() == true) {
                    
                    return true;
                }
                return false;
            
            } else if (to.file == 'g' && from.rank == to.rank) {
                
                if (from.file < to.file) {
                    for (int i = fromIndex.x + 1; i < to.file; i ++) {
                        if(this->pieceStrategyDelegate->canCheckDuringPassing(board->indexToPosition(fromIndex.y, i))) {
                            return false;
                        }
                    }
                }
                
                if (this->pieceStrategyDelegate->moveKingSideRook() == true) {
                    
                    return true;
                }
                return false;
            }
        }
    }
    
    return false;
}