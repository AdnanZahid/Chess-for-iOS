//
//  RookStrategy.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "../../Headers/RookStrategy.hpp"

RookStrategy::void setColor(Color color) {
    this->color = color;
}

RookStrategy::void setPosition(Position position) {
    this->centralBitboard->clearPreviousPosition(*this->decentralBitboard);
    this->centralBitboard->clearPreviousRookPosition(this->decentralBitboard);
    this->position = position;
    
    this->decentralBitboard->setPosition(this->position);
    this->centralBitboard->setRookPosition(this->decentralBitboard);
}

RookStrategy::void updateMoves() {
    this->decentralBitboard->setMoves(this->getMoves(this->position));
    this->centralBitboard->setRookMoves(this->decentralBitboard);
}

RookStrategy::LinkedList<Position> *getMoves(Position position) {
    
    this->mobility = 0;
    LinkedList<Position> *movesList = new LinkedList<Position>();
    this->getMoves(this, movesList);
    return movesList;
}

RookStrategy::RookStrategy(Board *board) : PieceStrategy(board) {
}

RookStrategy::static void getMoves(PieceStrategy *pieceStrategy, LinkedList<Position> *movesList) {
    
    Index fromIndex = pieceStrategy->board->positionToIndex(pieceStrategy->position);
    Index index = fromIndex;
    
    for (int rank = 0; rank < 8; rank ++) {
        index.y = rank;
        Position to = pieceStrategy->board->indexToPosition(index.x, index.y);
        pieceStrategy->addMoveToList(pieceStrategy->position, to, movesList);
    }
    
    index.y = fromIndex.y;
    
    for (int file = 0; file < 8; file ++) {
        index.x = file;
        Position to = pieceStrategy->board->indexToPosition(index.x, index.y);
        pieceStrategy->addMoveToList(pieceStrategy->position, to, movesList);
    }
}

RookStrategy::bool move(Position from, Position to) {
    
    Piece *destinationPiece = this->board->getPieceOnPosition(to);
    
    if (destinationPiece == nullptr || destinationPiece->color != this->color) {
        return this->move(this->board, from, to);
    }
    
    return false;
}

RookStrategy::static bool move(Board *board, Position from, Position to) {
    
    Position tempPosition = from;

    if (from.file == to.file) {
        if (from.rank != to.rank) {
            
            if (from.rank < to.rank) {
                for (int i = from.rank + 1; i < to.rank; i ++) {
                    tempPosition.rank = i;
                    if (board->getPieceOnPosition(tempPosition) != nullptr) {
                        return false;
                    }
                }
            } else {
                for (int i = to.rank + 1; i < from.rank; i ++) {
                    tempPosition.rank = i;
                    if (board->getPieceOnPosition(tempPosition) != nullptr) {
                        return false;
                    }
                }
            }
            
            return true;
        }
    } else if (from.rank == to.rank) {
        if (from.file != to.file) {
            
            if (from.file < to.file) {
                for (int i = from.file + 1; i < to.file; i ++) {
                    tempPosition.file = i;
                    if (board->getPieceOnPosition(tempPosition) != nullptr) {
                        return false;
                    }
                }
            } else {
                for (int i = to.file + 1; i < from.file; i ++) {
                    tempPosition.file = i;
                    if (board->getPieceOnPosition(tempPosition) != nullptr) {
                        return false;
                    }
                }
            }
            
            return true;
        }
    }
    
    return false;
}