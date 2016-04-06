//
//  BishopStrategy.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "../../Headers/BishopStrategy.hpp"

BishopStrategy::void setColor(Color color) {
    this->color = color;
}

BishopStrategy::void setPosition(Position position) {
    this->centralBitboard->clearPreviousPosition(*this->decentralBitboard);
    this->centralBitboard->clearPreviousBishopPosition(this->decentralBitboard);
    this->position = position;
    
    this->decentralBitboard->setPosition(this->position);
    this->centralBitboard->setBishopPosition(this->decentralBitboard);
}

BishopStrategy::void updateMoves() {
    this->decentralBitboard->setMoves(this->getMoves(this->position));
    this->centralBitboard->setBishopMoves(this->decentralBitboard);
}

BishopStrategy::LinkedList<Position> *getMoves(Position position) {
    
    this->mobility = 0;
    LinkedList<Position> *movesList = new LinkedList<Position>();
    this->getMoves(this, movesList);
    return movesList;
}

BishopStrategy::BishopStrategy(Board *board) : PieceStrategy(board) {
}

BishopStrategy::static void getMoves(PieceStrategy *pieceStrategy, LinkedList<Position> *movesList) {
    
    Index index = pieceStrategy->board->positionToIndex(pieceStrategy->position);
    
    if (index.y <= index.x) {
        for (int x = index.x - index.y, y = 0; x < 8; x ++, y ++) {
            Position to = pieceStrategy->board->indexToPosition(x, y);
            pieceStrategy->addMoveToList(pieceStrategy->position, to, movesList);
        }
    } else {
        for (int x = 0, y = index.y - index.x; y < 8; x ++, y ++) {
            Position to = pieceStrategy->board->indexToPosition(x, y);
            pieceStrategy->addMoveToList(pieceStrategy->position, to, movesList);
        }
    }
    
    if (index.x + index.y < 8) {
        for (int x = 0, y = index.x + index.y; y >= 0; x ++, y --) {
            Position to = pieceStrategy->board->indexToPosition(x, y);
            pieceStrategy->addMoveToList(pieceStrategy->position, to, movesList);
        }
    } else {
        for (int x = index.x + index.y - 7, y = 7; x < 8; x ++, y --) {
            Position to = pieceStrategy->board->indexToPosition(x, y);
            pieceStrategy->addMoveToList(pieceStrategy->position, to, movesList);
        }
    }
}

BishopStrategy::bool move(Position from, Position to) {
    
    Piece *destinationPiece = this->board->getPieceOnPosition(to);
    
    if (destinationPiece == nullptr || destinationPiece->color != this->color) {
        return this->move(this->board, from, to);
    }
    
    return false;
}

BishopStrategy::static bool move(Board *board, Position from, Position to) {
    
    Position tempPosition;
    
    if (from.file != to.file) {
        if (from.rank != to.rank) {
            if (std::fabs(from.file - to.file) == std::fabs(from.rank - to.rank)) {
                
                if (from.file < to.file && from.rank < to.rank) {
                    for (int i = from.file + 1, j = from.rank + 1; i < to.file && j < to.rank; i ++, j ++) {
                        tempPosition.file = i;
                        tempPosition.rank = j;
                        if (board->getPieceOnPosition(tempPosition) != nullptr) {
                            return false;
                        }
                    }
                } else if (from.file > to.file && from.rank < to.rank) {
                    for (int i = from.file - 1, j = from.rank + 1; i > to.file && j < to.rank; i --, j ++) {
                        tempPosition.file = i;
                        tempPosition.rank = j;
                        if (board->getPieceOnPosition(tempPosition) != nullptr) {
                            return false;
                        }
                    }
                } else if (from.file > to.file && from.rank > to.rank) {
                    for (int i = from.file - 1, j = from.rank - 1; i > to.file && j > to.rank; i --, j --) {
                        tempPosition.file = i;
                        tempPosition.rank = j;
                        if (board->getPieceOnPosition(tempPosition) != nullptr) {
                            return false;
                        }
                    }
                } else if (from.file < to.file && from.rank > to.rank) {
                    for (int i = from.file + 1, j = from.rank - 1; i < to.file && j > to.rank; i ++, j --) {
                        tempPosition.file = i;
                        tempPosition.rank = j;
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