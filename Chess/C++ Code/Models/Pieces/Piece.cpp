//
//  Piece.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "../../Headers/Piece.hpp"
    
Piece::Piece(int value, Color color, Board *board, PieceDelegate *pieceDelegate, CentralBitboard *centralBitboard) {
    this->value = value;
    this->color = color;
    this->board = board;
    this->pieceDelegate = pieceDelegate;
    this->centralBitboard = centralBitboard;
}

Piece::void setPieceStrategy(PieceStrategy *pieceStrategy) {
    
    this->pieceStrategy = pieceStrategy;
    this->pieceStrategy->pieceStrategyDelegate = this;
    this->pieceStrategy->board = this->board;
    this->pieceStrategy->centralBitboard = this->centralBitboard;
    this->pieceStrategy->setColor(this->color);
}

Piece::void setPosition(Position position) {
    this->position = position;
    this->pieceStrategy->setPosition(this->position);
}

Piece::void promoteIfApplicable() {
    if ((this->position.rank == 1 || this->position.rank == 8) && this->value == PAWN) {
        this->value = QUEEN;
//            this->setPieceStrategy(new QueenStrategy(this->board)); // UNCOMMENT THIS PLEASE
    }
}

Piece::bool moveTo(Position position) {
    
    Position fromPosition = this->position;
    Position toPosition = position;
    
    Piece *destinationPiece = this->board->getPieceOnPosition(toPosition);
    
    if (this->pieceStrategy->move(fromPosition, toPosition) == true) {
        
        State fromState = { fromPosition, this, this->pieceStrategy->hasMoved, this-pieceStrategy->isEnPassant };
        State toState = { toPosition, destinationPiece, true, false };
        
        this->stateStack.push({ fromState, toState });
        
        this->pieceStrategy->hasMoved = true;
        
        this->promoteIfApplicable();
        
        this->setPosition(toPosition);
        
        this->board->setPieceOnPosition(fromState.piece, toPosition);
        this->board->setPieceOnPosition(nullptr, fromPosition);
        
        return true;
    }
    
    return false;
}

Piece::void undoMove() {
    
    StateStack stack = this->stateStack.top();
    this->stateStack.pop();
    
    this->setPosition(stack.fromState.position);
    
    this->pieceStrategy->hasMoved = stack.fromState.hasMoved;
    this->pieceStrategy->isEnPassant = stack.fromState.isEnPassant;
    
    this->board->setPieceOnPosition(stack.fromState.piece, stack.fromState.position);
    this->board->setPieceOnPosition(stack.toState.piece, stack.toState.position);
}

Piece::bool canCheck(Position position) {
    return this->pieceStrategy->move(this->position, position);
}

Piece::bool moveKingSideRook() {
    return this->pieceDelegate->moveKingSideRook();
}

Piece::bool moveQueenSideRook() {
    return this->pieceDelegate->moveQueenSideRook();
}

Piece::bool canCheckDuringPassing(Position position) {
    return this->pieceDelegate->canCheckDuringPassing(position);
}

Piece::void updateMoves() {
    this->pieceStrategy->updateMoves();
}