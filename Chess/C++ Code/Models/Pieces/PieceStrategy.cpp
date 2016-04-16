//
//  PieceStrategy.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

#include <cmath>
#include "../../Others/PieceStrategyDelegate.cpp"
#include "../CentralBitboard.cpp"
#include "../DecentralBitboard.cpp"

class PieceStrategy {

protected:
    Color color;
    
public:
    int mobility;
    bool hasMoved = false;
    Position position;
    Board *board;
    PieceStrategyDelegate *pieceStrategyDelegate;
    CentralBitboard *centralBitboard;
    DecentralBitboard *decentralBitboard;
    
    bool isEnPassant = false;
    
    virtual void setColor(Color color) = 0;
    virtual void setPosition(Position position) = 0;
    virtual bool move(Position from, Position to) = 0;
    virtual std::list<Position> getMoves(Position position) = 0;
    virtual void updateMoves() = 0;
    
    PieceStrategy(Board *board) {
        this->board = board;
        this->decentralBitboard = new DecentralBitboard();
    }
    
    std::list<Position> addMoveToList(Position from, Position to, std::list<Position> movesList) {
        
        if (this->move(from, to) == true) {
            movesList.push_back(to);
            this->mobility ++;
        }
        
        return movesList;
    }
};