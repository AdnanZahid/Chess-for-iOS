//
//  Piece.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "BasicStructs.h"
#include "PieceStrategyDelegate.hpp"
#include "PieceStrategy.hpp"
#include "CentralBitboard.hpp"

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
    
public:
    int value;
    Color color;
    Position position;
    PieceStrategy *pieceStrategy;
    CentralBitboard *centralBitboard;
    
    Piece(int value, Color color, Board *board, PieceDelegate *pieceDelegate, CentralBitboard *centralBitboard);
    
    void setPieceStrategy(PieceStrategy *pieceStrategy);
    
    void setPosition(Position position);
    
    void promoteIfApplicable();
    
    bool moveTo(Position position);
    
    void undoMove();
    
    bool canCheck(Position position);
    
    bool moveKingSideRook();
    
    bool moveQueenSideRook();
    
    bool canCheckDuringPassing(Position position);
    
    void updateMoves();
};