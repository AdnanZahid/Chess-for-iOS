//
//  KingStrategy.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

#include "PieceStrategy.cpp"
#include "Piece.cpp"

class KingStrategy : public PieceStrategy {
    
private:
    void setColor(Color color) {
        this->color = color;
    }
    
    void setPosition(Position position) {
        this->centralBitboard->clearPreviousPosition(*this->decentralBitboard);
        this->centralBitboard->clearPreviousKingPosition(this->decentralBitboard);
        this->position = position;
        
        this->decentralBitboard->setPosition(this->position);
        this->centralBitboard->setKingPosition(this->decentralBitboard);
    }
    
    void updateMoves() {
        this->decentralBitboard->setMoves(this->getMoves(this->position));
        this->centralBitboard->setKingMoves(this->decentralBitboard);
    }
    
    std::list<Position> getMoves(Position position) {
        
        this->mobility = 0;
        std::list<Position> movesList;
        
        if (position.rank > RANK_ONE) {
            Position toOneForwardStep = { (char)(position.rank - 1), position.file };
            movesList = this->addMoveToList(position, toOneForwardStep, movesList);
        }
        
        if (position.rank < RANK_EIGHT) {
            Position toOneBackwardStep = { (char)(position.rank + 1), position.file };
            movesList = this->addMoveToList(position, toOneBackwardStep, movesList);
        }
        
        if (position.file > FILE_A) {
            Position toOneLeftStep = { position.rank, (char)(position.file - 1) };
            movesList = this->addMoveToList(position, toOneLeftStep, movesList);
            
            if (position.rank > RANK_ONE) {
                Position toOneLeftBackwardStep = { (char)(position.rank - 1), (char)(position.file - 1) };
                movesList = this->addMoveToList(position, toOneLeftBackwardStep, movesList);
            }
            
            if (position.rank < RANK_EIGHT) {
                Position toOneLeftForwardStep = { (char)(position.rank + 1), (char)(position.file - 1) };
                movesList = this->addMoveToList(position, toOneLeftForwardStep, movesList);
            }
        }
        
        if (position.file < FILE_H) {
            Position toOneRightStep = { position.rank, (char)(position.file + 1) };
            movesList = this->addMoveToList(position, toOneRightStep, movesList);
            
            if (position.rank > RANK_ONE) {
                Position toOneRightBackwardStep = { (char)(position.rank - 1), (char)(position.file + 1) };
                movesList = this->addMoveToList(position, toOneRightBackwardStep, movesList);
            }
            
            if (position.rank < RANK_EIGHT) {
                Position toOneRightForwardStep = { (char)(position.rank + 1), (char)(position.file + 1) };
                movesList = this->addMoveToList(position, toOneRightForwardStep, movesList);
            }
        }
        
        return movesList;
    }
    
public:
    KingStrategy(Board *board) : PieceStrategy(board) {
    }
    
    bool move(Position from, Position to) {
        
        Piece *destinationPiece = this->board->getPieceOnPosition(to);
        
        if (destinationPiece == nullptr || destinationPiece->color != this->color) {
            Index fromIndex = this->board->positionToIndex(from);
            
            if (std::fabs(from.file - to.file) <= 1 && std::fabs(from.rank - to.rank) <= 1) {
                
                return true;
            
            } else if (this->hasMoved == false) {
                if (to.file == FILE_C && from.rank == to.rank) {
                    
                    if (from.file > from.file) {
                        for (int file = to.file + 1; file < from.file; file ++) {
                            if(this->pieceStrategyDelegate->canCheckDuringPassing(board->indexToPosition(file, fromIndex.y))) {
                                return false;
                            }
                        }
                    }
                    
                    if (this->pieceStrategyDelegate->moveQueenSideRook() == true) {
                        
                        return true;
                    }
                    return false;
                
                } else if (to.file == FILE_G && from.rank == to.rank) {
                    
                    if (from.file < to.file) {
                        for (int file = fromIndex.x + 1; file < to.file; file ++) {
                            if(this->pieceStrategyDelegate->canCheckDuringPassing(board->indexToPosition(fromIndex.y, file))) {
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
};