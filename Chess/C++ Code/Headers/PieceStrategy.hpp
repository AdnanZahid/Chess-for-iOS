//
//  PieceStrategy.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include <cmath>

#include "Board.hpp"
#include "CentralBitboard.hpp"
#include "DecentralBitboard.hpp"
#include "LinkedList.hpp"

class PieceStrategy {

protected:
    Color color;
    
public:
    int mobility;
    bool hasMoved;
    Position position;
    Board *board;
    PieceStrategyDelegate *pieceStrategyDelegate;
    CentralBitboard *centralBitboard;
    DecentralBitboard *decentralBitboard;
    
    bool isEnPassant = false;
    
    virtual void setColor(Color color) = 0;
    virtual void setPosition(Position position) = 0;
    virtual bool move(Position from, Position to) = 0;
    virtual LinkedList<Position> *getMoves(Position position) = 0;
    virtual void updateMoves() = 0;
    
    PieceStrategy(Board *board);
    
    LinkedList<Position> *addMoveToList(Position from, Position to, LinkedList<Position> *movesList);
};