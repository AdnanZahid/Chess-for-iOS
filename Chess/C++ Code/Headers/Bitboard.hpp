//
//  Bitboard.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/18/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include <stdint.h>
typedef uint64_t U64;

#include "BasicStructs.h"
#include "Board.hpp"
#include "LinkedList.hpp"

class Bitboard {
    
public:
    U64 position;
    U64 moves;
    
    LinkedList<Position> *computePositionsFromBitboard(U64 bitboardPosition);
    
    U64 computeBitboardFromPosition(Position position);
    
    void performBitwiseORForPosition(Bitboard *first, Bitboard *second);
    
    void performBitwiseANDForPosition(Bitboard *first, Bitboard *second);
    
    void performBitwiseNOTForPosition(Bitboard *bitboard);
    
    void performBitwiseORForMoves(Bitboard *first, Bitboard *second);
    
    void performBitwiseANDForMoves(Bitboard *first, Bitboard *second);
    
    void performBitwiseNOTForMoves(Bitboard *bitboard);
};