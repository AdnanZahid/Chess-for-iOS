//
//  BishopStrategy.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

#include "Piece.cpp"
#include "../../Others/Constants.cpp"

class BishopStrategy : public PieceStrategy {
    
private:
    void setColor(Color color) {
        this->color = color;
    }
    
    void setPosition(Position position) {
        this->centralBitboard->clearPreviousPosition(*this->decentralBitboard);
        this->centralBitboard->clearPreviousBishopPosition(this->decentralBitboard);
        this->position = position;
        
        this->decentralBitboard->setPosition(this->position);
        this->centralBitboard->setBishopPosition(this->decentralBitboard);
    }
    
    void updateMoves() {
        this->decentralBitboard->setMoves(this->getMoves(this->position));
        this->centralBitboard->setBishopMoves(this->decentralBitboard);
    }
    
    std::list<Position> getMoves(Position position) {
        
        this->mobility = 0;
        std::list<Position> movesList;
        movesList = this->getMoves(this, movesList);
        return movesList;
    }
    
public:
    BishopStrategy(Board *board) : PieceStrategy(board) {
    }
    
    static std::list<Position> getMoves(PieceStrategy *pieceStrategy, std::list<Position> movesList) {
        
        Index index = pieceStrategy->board->positionToIndex(pieceStrategy->position);
        
        if (index.y <= index.x) {
            for (int file = index.x - index.y, rank = 0; file < NUMBER_OF_FILES_ON_BOARD; file ++, rank ++) {
                Position to = pieceStrategy->board->indexToPosition(file, rank);
                movesList = pieceStrategy->addMoveToList(pieceStrategy->position, to, movesList);
            }
        } else {
            for (int file = 0, rank = index.y - index.x; rank < NUMBER_OF_RANKS_ON_BOARD; file ++, rank ++) {
                Position to = pieceStrategy->board->indexToPosition(file, rank);
                movesList = pieceStrategy->addMoveToList(pieceStrategy->position, to, movesList);
            }
        }
        
        if (index.x + index.y < NUMBER_OF_RANKS_ON_BOARD) {
            for (int file = 0, rank = index.x + index.y; rank >= 0; file ++, rank --) {
                Position to = pieceStrategy->board->indexToPosition(file, rank);
                movesList = pieceStrategy->addMoveToList(pieceStrategy->position, to, movesList);
            }
        } else {
            for (int file = index.x + index.y - 7, rank = NUMBER_OF_RANKS_ON_BOARD - 1; file < NUMBER_OF_RANKS_ON_BOARD; file ++, rank --) {
                Position to = pieceStrategy->board->indexToPosition(file, rank);
                movesList = pieceStrategy->addMoveToList(pieceStrategy->position, to, movesList);
            }
        }
        
        return movesList;
    }
    
    bool move(Position from, Position to) {
        
        Piece *destinationPiece = this->board->getPieceOnPosition(to);
        
        if (destinationPiece == nullptr || destinationPiece->color != this->color) {
            return this->move(this->board, from, to);
        }
        
        return false;
    }
    
    static bool move(Board *board, Position from, Position to) {
        
        Position tempPosition;
        
        if (from.file != to.file) {
            if (from.rank != to.rank) {
                if (std::fabs(from.file - to.file) == std::fabs(from.rank - to.rank)) {
                    
                    if (from.file < to.file && from.rank < to.rank) {
                        for (int file = from.file + 1, rank = from.rank + 1; file < to.file && rank < to.rank; file ++, rank ++) {
                            tempPosition.file = file;
                            tempPosition.rank = rank;
                            if (board->getPieceOnPosition(tempPosition) != nullptr) {
                                return false;
                            }
                        }
                    } else if (from.file > to.file && from.rank < to.rank) {
                        for (int file = from.file - 1, rank = from.rank + 1; file > to.file && rank < to.rank; file --, rank ++) {
                            tempPosition.file = file;
                            tempPosition.rank = rank;
                            if (board->getPieceOnPosition(tempPosition) != nullptr) {
                                return false;
                            }
                        }
                    } else if (from.file > to.file && from.rank > to.rank) {
                        for (int file = from.file - 1, rank = from.rank - 1; file > to.file && rank > to.rank; file --, rank --) {
                            tempPosition.file = file;
                            tempPosition.rank = rank;
                            if (board->getPieceOnPosition(tempPosition) != nullptr) {
                                return false;
                            }
                        }
                    } else if (from.file < to.file && from.rank > to.rank) {
                        for (int file = from.file + 1, rank = from.rank - 1; file < to.file && rank > to.rank; file ++, rank --) {
                            tempPosition.file = file;
                            tempPosition.rank = rank;
                            if (board->getPieceOnPosition(tempPosition) != nullptr) {
                                return false;
                            }
                        }
                    }
                    
                    return true;
                }
            }
        }
        
        return false;
    }
};