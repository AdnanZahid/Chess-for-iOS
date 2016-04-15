//
//  CentralBitboard.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/18/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

#include "Bitboard.cpp"
#include "DecentralBitboard.cpp"

class CentralBitboard : public Bitboard {
    
public:
    DecentralBitboard *pawnBitboard;
    DecentralBitboard *knightBitboard;
    DecentralBitboard *bishopBitboard;
    DecentralBitboard *rookBitboard;
    DecentralBitboard *queenBitboard;
    DecentralBitboard *kingBitboard;
    
    CentralBitboard() {
        this->pawnBitboard = new DecentralBitboard();
        this->knightBitboard = new DecentralBitboard();
        this->bishopBitboard = new DecentralBitboard();
        this->rookBitboard = new DecentralBitboard();
        this->queenBitboard = new DecentralBitboard();
        this->kingBitboard = new DecentralBitboard();
    }
    
    void clearPreviousPosition(DecentralBitboard decentralBitboard) {
        this->performBitwiseNOTForPosition(&decentralBitboard);
        this->performBitwiseANDForPosition(this, &decentralBitboard);
    }
    
    void clearPreviousPawnPosition(DecentralBitboard *decentralBitboard) {
        this->performBitwiseNOTForPosition(decentralBitboard);
        this->performBitwiseANDForPosition(this->pawnBitboard, decentralBitboard);
    }
    
    void clearPreviousKnightPosition(DecentralBitboard *decentralBitboard) {
        this->performBitwiseNOTForPosition(decentralBitboard);
        this->performBitwiseANDForPosition(this->knightBitboard, decentralBitboard);
    }
    
    void clearPreviousBishopPosition(DecentralBitboard *decentralBitboard) {
        this->performBitwiseNOTForPosition(decentralBitboard);
        this->performBitwiseANDForPosition(this->bishopBitboard, decentralBitboard);
    }
    
    void clearPreviousRookPosition(DecentralBitboard *decentralBitboard) {
        this->performBitwiseNOTForPosition(decentralBitboard);
        this->performBitwiseANDForPosition(this->rookBitboard, decentralBitboard);
    }
    
    void clearPreviousQueenPosition(DecentralBitboard *decentralBitboard) {
        this->performBitwiseNOTForPosition(decentralBitboard);
        this->performBitwiseANDForPosition(this->queenBitboard, decentralBitboard);
    }
    
    void clearPreviousKingPosition(DecentralBitboard *decentralBitboard) {
        this->performBitwiseNOTForPosition(decentralBitboard);
        this->performBitwiseANDForPosition(this->kingBitboard, decentralBitboard);
    }
    
    void setPawnPosition(DecentralBitboard *decentralBitboard) {
        this->performBitwiseORForPosition(this->pawnBitboard, decentralBitboard);
        this->performBitwiseORForPosition(this, decentralBitboard);
    }
    
    void setKnightPosition(DecentralBitboard *decentralBitboard) {
        this->performBitwiseORForPosition(this->knightBitboard, decentralBitboard);
        this->performBitwiseORForPosition(this, decentralBitboard);
    }
    
    void setBishopPosition(DecentralBitboard *decentralBitboard) {
        this->performBitwiseORForPosition(this->bishopBitboard, decentralBitboard);
        this->performBitwiseORForPosition(this, decentralBitboard);
    }
    
    void setRookPosition(DecentralBitboard *decentralBitboard) {
        this->performBitwiseORForPosition(this->rookBitboard, decentralBitboard);
        this->performBitwiseORForPosition(this, decentralBitboard);
    }
    
    void setQueenPosition(DecentralBitboard *decentralBitboard) {
        this->performBitwiseORForPosition(this->queenBitboard, decentralBitboard);
        this->performBitwiseORForPosition(this, decentralBitboard);
    }
    
    void setKingPosition(DecentralBitboard *decentralBitboard) {
        this->performBitwiseORForPosition(this->kingBitboard, decentralBitboard);
        this->performBitwiseORForPosition(this, decentralBitboard);
    }
    
    void setPawnMoves(DecentralBitboard *decentralBitboard) {
        this->performBitwiseORForMoves(this->pawnBitboard, decentralBitboard);
        this->performBitwiseORForMoves(this, decentralBitboard);
    }
    
    void setKnightMoves(DecentralBitboard *decentralBitboard) {
        this->performBitwiseORForMoves(this->knightBitboard, decentralBitboard);
        this->performBitwiseORForMoves(this, decentralBitboard);
    }
    
    void setBishopMoves(DecentralBitboard *decentralBitboard) {
        this->performBitwiseORForMoves(this->bishopBitboard, decentralBitboard);
        this->performBitwiseORForMoves(this, decentralBitboard);
    }
    
    void setRookMoves(DecentralBitboard *decentralBitboard) {
        this->performBitwiseORForMoves(this->rookBitboard, decentralBitboard);
        this->performBitwiseORForMoves(this, decentralBitboard);
    }
    
    void setQueenMoves(DecentralBitboard *decentralBitboard) {
        this->performBitwiseORForMoves(this->queenBitboard, decentralBitboard);
        this->performBitwiseORForMoves(this, decentralBitboard);
    }
    
    void setKingMoves(DecentralBitboard *decentralBitboard) {
        this->performBitwiseORForMoves(this->kingBitboard, decentralBitboard);
        this->performBitwiseORForMoves(this, decentralBitboard);
    }
};