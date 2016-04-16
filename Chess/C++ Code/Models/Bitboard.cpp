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
            
            int file = order % NUMBER_OF_FILES_ON_BOARD;
            int rank = order / NUMBER_OF_RANKS_ON_BOARD;
            
            Position position = Board::indexToPosition(file, rank);
            list.push_back(position);
        }
        
        return list;
    }
    
    U64 computeBitboardFromPosition(Position position) {
        
        Index index = Board::positionToIndex(position);
        int file = index.x;
        int rank = index.y;
        
        int order = (rank * NUMBER_OF_RANKS_ON_BOARD) + file;
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