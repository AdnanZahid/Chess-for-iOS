//
//  PieceStrategy.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "../../Headers/PieceStrategy.hpp"
    
PieceStrategy::PieceStrategy(Board *board) : PieceStrategy(board) {
    this->board = board;
    this->decentralBitboard = new DecentralBitboard();
}

PieceStrategy::LinkedList<Position> *addMoveToList(Position from, Position to, LinkedList<Position> *movesList) {
    
    if (this->move(from, to) == true) {
        movesList->add(&to);
        
        this->mobility ++;
    }
    
    return movesList;
}