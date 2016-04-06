//
//  DecentralBitboard.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/18/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "../Headers/DecentralBitboard.hpp"

DecentralBitboard::void setPosition(Position position) {
    this->position = this->computeBitboardFromPosition(position);
}

DecentralBitboard::void setMoves(LinkedList<Position> *moves) {
    this->moves = 0;
    for(LinkedList<Position>::Node *node = moves->head; node != nullptr; node = node->next) {
        this->moves |= this->computeBitboardFromPosition(*node->value);
    }
}