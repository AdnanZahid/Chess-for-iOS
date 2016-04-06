//
//  DecentralBitboard.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/18/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "BasicStructs.h"
#include "Bitboard.hpp"

class DecentralBitboard : public Bitboard {
    
public:
    void setPosition(Position position);
    
    void setMoves(LinkedList<Position> *moves);
};