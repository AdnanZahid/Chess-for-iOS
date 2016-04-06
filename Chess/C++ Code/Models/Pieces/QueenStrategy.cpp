//
//  QueenStrategy.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "../../Headers/QueenStrategy.hpp"

QueenStrategy::void setColor(Color color) {
    this->color = color;
}

QueenStrategy::void setPosition(Position position) {
    this->centralBitboard->clearPreviousPosition(*this->decentralBitboard);
    this->centralBitboard->clearPreviousQueenPosition(this->decentralBitboard);
    this->position = position;
    
    this->decentralBitboard->setPosition(this->position);
    this->centralBitboard->setQueenPosition(this->decentralBitboard);
}

QueenStrategy::void updateMoves() {
    this->decentralBitboard->setMoves(this->getMoves(this->position));
    this->centralBitboard->setQueenMoves(this->decentralBitboard);
}

QueenStrategy::LinkedList<Position> *getMoves(Position position) {
    
    this->mobility = 0;
    LinkedList<Position> *movesList = new LinkedList<Position>();
    BishopStrategy::getMoves(this, movesList);
    RookStrategy::getMoves(this, movesList);
    return movesList;
}

QueenStrategy::QueenStrategy(Board *board) : PieceStrategy(board) {
}

QueenStrategy::bool move(Position from, Position to) {
    
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