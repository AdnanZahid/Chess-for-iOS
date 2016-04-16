//
//  Piece.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

#include <stack>

#include "../../Others/Constants.cpp"
#include "../CentralBitboard.cpp"
#include "../DecentralBitboard.cpp"
#include "../../Others/PieceDelegate.cpp"
#include "../../Others/PieceStrategyDelegate.cpp"
#include "PieceStrategy.cpp"
//#include "QueenStrategy.cpp" // UNCOMMENT THIS PLEASE

typedef struct {
    Position position;
    Piece *piece;
    bool hasMoved;
    bool isEnPassant;
} State;

typedef struct {
    State fromState;
    State toState;
} StateStack;

class Piece : PieceStrategyDelegate {
    
private:
    Board *board;
    PieceDelegate *pieceDelegate;
    std::stack <StateStack> stateStack;
    
public:
    int value;
    int order;
    Color color;
    Position position;
    PieceStrategy *pieceStrategy;
    CentralBitboard *centralBitboard;
    
    Piece(int value, Color color, Board *board, PieceDelegate *pieceDelegate, CentralBitboard *centralBitboard) {
        this->value = value;
        this->color = color;
        this->board = board;
        this->pieceDelegate = pieceDelegate;
        this->centralBitboard = centralBitboard;
    }
    
    void setPieceStrategy(PieceStrategy *pieceStrategy) {
        
        this->pieceStrategy = pieceStrategy;
        this->pieceStrategy->pieceStrategyDelegate = this;
        this->pieceStrategy->board = this->board;
        this->pieceStrategy->centralBitboard = this->centralBitboard;
        this->pieceStrategy->setColor(this->color);
    }
    
    void setPosition(Position position) {
        this->position = position;
        this->pieceStrategy->setPosition(this->position);
        
        Index index = this->board->positionToIndex(this->position);
        this->order = (index.y * NUMBER_OF_RANKS_ON_BOARD) + index.x + 1;
    }
    
    void promoteIfApplicable() {
        if ((this->position.rank == RANK_ONE || this->position.rank == RANK_EIGHT) && this->value == PAWN) {
            this->value = QUEEN;
//            this->setPieceStrategy(new QueenStrategy(this->board)); // UNCOMMENT THIS PLEASE
        }
    }
    
    bool moveTo(Position position) {
        
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
    
    void undoMove() {
        StateStack stack = this->stateStack.top();
        this->stateStack.pop();
        
        this->setPosition(stack.fromState.position);
        
        this->pieceStrategy->hasMoved = stack.fromState.hasMoved;
        this->pieceStrategy->isEnPassant = stack.fromState.isEnPassant;
        
        this->board->setPieceOnPosition(stack.fromState.piece, stack.fromState.position);
        this->board->setPieceOnPosition(stack.toState.piece, stack.toState.position);
    }
    
    bool canCheck(Position position) {
        return this->pieceStrategy->move(this->position, position);
    }
    
    bool moveKingSideRook() {
        return this->pieceDelegate->moveKingSideRook();
    }
    
    bool moveQueenSideRook() {
        return this->pieceDelegate->moveQueenSideRook();
    }
    
    bool canCheckDuringPassing(Position position) {
        return this->pieceDelegate->canCheckDuringPassing(position);
    }
    
    void updateMoves() {
        this->pieceStrategy->updateMoves();
    }
};