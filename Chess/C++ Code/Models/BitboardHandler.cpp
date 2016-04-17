//
//  BitboardHandler.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/20/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

#include "Board.cpp"
#include "CentralBitboard.cpp"
#include <string>

class BitboardHandler {

private:
    Board *board;
    Color color;
    CentralBitboard *centralBitboard;
    
public:
    BitboardHandler(Board *board, Color color, CentralBitboard *centralBitboard) {
        this->board = board;
        this->color = color;
        this->centralBitboard = centralBitboard;
    }
    
    void clearAllMovesBitboards() {
        this->centralBitboard->moves = 0;
        this->centralBitboard->pawnBitboard->moves = 0;
        this->centralBitboard->knightBitboard->moves = 0;
        this->centralBitboard->bishopBitboard->moves = 0;
        this->centralBitboard->rookBitboard->moves = 0;
        this->centralBitboard->queenBitboard->moves = 0;
        this->centralBitboard->kingBitboard->moves = 0;
    }
    
    void updateArray(bool whiteArray[8][8], bool blackArray[8][8], U64 bitboard) {
        std::list<Position> moves = this->centralBitboard->computePositionsFromBitboard(bitboard);
        
        for(std::list<Position>::iterator iterator = moves.begin(); iterator != moves.end(); iterator++) {
            Index index = this->board->positionToIndex(*iterator);
            
            if (this->color == white) {
                whiteArray[index.y][index.x] = true;
            } else {
                blackArray[index.y][index.x] = true;
            }
        }
    }
    
    void updatePresenceAndMovesArrays() {
//        if (this->color == white) {
//            memset(this->board->whitePresenceArray, 0, sizeof(this->board->whitePresenceArray));
//            memset(this->board->whitePawnPresenceArray, 0, sizeof(this->board->whitePawnPresenceArray));
//            memset(this->board->whiteKnightPresenceArray, 0, sizeof(this->board->whiteKnightPresenceArray));
//            memset(this->board->whiteBishopPresenceArray, 0, sizeof(this->board->whiteBishopPresenceArray));
//            memset(this->board->whiteRookPresenceArray, 0, sizeof(this->board->whiteRookPresenceArray));
//            memset(this->board->whiteQueenPresenceArray, 0, sizeof(this->board->whiteQueenPresenceArray));
//            memset(this->board->whiteKingPresenceArray, 0, sizeof(this->board->whiteKingPresenceArray));
//            
//            memset(this->board->whiteMovesArray, 0, sizeof(this->board->whiteMovesArray));
//            memset(this->board->whitePawnMovesArray, 0, sizeof(this->board->whitePawnMovesArray));
//            memset(this->board->whiteKnightMovesArray, 0, sizeof(this->board->whiteKnightMovesArray));
//            memset(this->board->whiteBishopMovesArray, 0, sizeof(this->board->whiteBishopMovesArray));
//            memset(this->board->whiteRookMovesArray, 0, sizeof(this->board->whiteRookMovesArray));
//            memset(this->board->whiteQueenMovesArray, 0, sizeof(this->board->whiteQueenMovesArray));
//            memset(this->board->whiteKingMovesArray, 0, sizeof(this->board->whiteKingMovesArray));
//        } else {
//            memset(this->board->blackPresenceArray, 0, sizeof(this->board->blackPresenceArray));
//            memset(this->board->blackPawnPresenceArray, 0, sizeof(this->board->blackPawnPresenceArray));
//            memset(this->board->blackKnightPresenceArray, 0, sizeof(this->board->blackKnightPresenceArray));
//            memset(this->board->blackBishopPresenceArray, 0, sizeof(this->board->blackBishopPresenceArray));
//            memset(this->board->blackRookPresenceArray, 0, sizeof(this->board->blackRookPresenceArray));
//            memset(this->board->blackQueenPresenceArray, 0, sizeof(this->board->blackQueenPresenceArray));
//            memset(this->board->blackKingPresenceArray, 0, sizeof(this->board->blackKingPresenceArray));
//            
//            memset(this->board->blackMovesArray, 0, sizeof(this->board->blackMovesArray));
//            memset(this->board->blackPawnMovesArray, 0, sizeof(this->board->blackPawnMovesArray));
//            memset(this->board->blackKnightMovesArray, 0, sizeof(this->board->blackKnightMovesArray));
//            memset(this->board->blackBishopMovesArray, 0, sizeof(this->board->blackBishopMovesArray));
//            memset(this->board->blackRookMovesArray, 0, sizeof(this->board->blackRookMovesArray));
//            memset(this->board->blackQueenMovesArray, 0, sizeof(this->board->blackQueenMovesArray));
//            memset(this->board->blackKingMovesArray, 0, sizeof(this->board->blackKingMovesArray));
//        }
//        
//        this->updateArray(this->board->whitePresenceArray, this->board->blackPresenceArray, this->centralBitboard->position);
//        this->updateArray(this->board->whitePawnPresenceArray, this->board->blackPawnPresenceArray, this->centralBitboard->pawnBitboard->position);
//        this->updateArray(this->board->whiteKnightPresenceArray, this->board->blackKnightPresenceArray, this->centralBitboard->knightBitboard->position);
//        this->updateArray(this->board->whiteBishopPresenceArray, this->board->blackBishopPresenceArray, this->centralBitboard->bishopBitboard->position);
//        this->updateArray(this->board->whiteRookPresenceArray, this->board->blackRookPresenceArray, this->centralBitboard->rookBitboard->position);
//        this->updateArray(this->board->whiteQueenPresenceArray, this->board->blackQueenPresenceArray, this->centralBitboard->queenBitboard->position);
//        this->updateArray(this->board->whiteKingPresenceArray, this->board->blackKingPresenceArray, this->centralBitboard->kingBitboard->position);
//        
//        this->updateArray(this->board->whiteMovesArray, this->board->blackMovesArray, this->centralBitboard->moves);
//        this->updateArray(this->board->whitePawnMovesArray, this->board->blackPawnMovesArray, this->centralBitboard->pawnBitboard->moves);
//        this->updateArray(this->board->whiteKnightMovesArray, this->board->blackKnightMovesArray, this->centralBitboard->knightBitboard->moves);
//        this->updateArray(this->board->whiteBishopMovesArray, this->board->blackBishopMovesArray, this->centralBitboard->bishopBitboard->moves);
//        this->updateArray(this->board->whiteRookMovesArray, this->board->blackRookMovesArray, this->centralBitboard->rookBitboard->moves);
//        this->updateArray(this->board->whiteQueenMovesArray, this->board->blackQueenMovesArray, this->centralBitboard->queenBitboard->moves);
//        this->updateArray(this->board->whiteKingMovesArray, this->board->blackKingMovesArray, this->centralBitboard->kingBitboard->moves);
    }
};