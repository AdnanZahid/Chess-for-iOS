//
//  Bitboard.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/18/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

#include "../Others/Constants.cpp"
#include "Board.cpp"
#include <list>

class Bitboard {
    
public:
    U64 position;
    U64 moves;
    
    std::list<Position> computePositionsFromBitboard(U64 bitboardPosition) {
        
        std::list<Position> list;
        
        for(int order = 0; bitboardPosition != 0;) {
            for(; (bitboardPosition & 1) != 1; bitboardPosition >>= 1) {
                order ++;
            }
            
            bitboardPosition &= 0b1111111111111111111111111111111111111111111111111111111111111110;
            
            int x = order % 8;
            int y = order / 8;
            
            Position position = Board::indexToPosition(x, y);
            list.push_back(position);
        }
        
        return list;
    }
    
    U64 computeBitboardFromPosition(Position position) {
        
        Index index = Board::positionToIndex(position);
        int x = index.x;
        int y = index.y;
        
        int order = (y * 8) + x;
        U64 bitboard = 1ull << order;
        return bitboard;
    }
    
    void performBitwiseORForPosition(Bitboard *first, Bitboard *second) {
        first->position |= second->position;
    }
    
    void performBitwiseANDForPosition(Bitboard *first, Bitboard *second) {
        first->position &= second->position;
    }
    
    void performBitwiseNOTForPosition(Bitboard *bitboard) {
        bitboard->position = ~bitboard->position;
    }
    
    void performBitwiseORForMoves(Bitboard *first, Bitboard *second) {
        first->moves |= second->moves;
    }
    
    void performBitwiseANDForMoves(Bitboard *first, Bitboard *second) {
        first->moves &= second->moves;
    }
    
    void performBitwiseNOTForMoves(Bitboard *bitboard) {
        bitboard->moves = ~bitboard->moves;
    }
};