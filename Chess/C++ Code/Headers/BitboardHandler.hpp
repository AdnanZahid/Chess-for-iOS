//
//  BitboardHandler.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/20/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "BasicStructs.h"
#include "Board.hpp"
#include "CentralBitboard.hpp"

class BitboardHandler {
    
public:
    BitboardHandler(Board *board, Color color, CentralBitboard *centralBitboard);
    
    void clearAllMovesBitboards();
    
    void updateArray(bool whiteArray[8][8], bool blackArray[8][8], U64 bitboard);
    
    void updatePresenceAndMovesArrays();
};