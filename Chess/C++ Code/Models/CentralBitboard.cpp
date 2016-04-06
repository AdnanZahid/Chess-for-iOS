//
//  CentralBitboard.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/18/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "../Headers/CentralBitboard.hpp"
    
CentralBitboard::CentralBitboard() {
    this->pawnBitboard = new DecentralBitboard();
    this->knightBitboard = new DecentralBitboard();
    this->bishopBitboard = new DecentralBitboard();
    this->rookBitboard = new DecentralBitboard();
    this->queenBitboard = new DecentralBitboard();
    this->kingBitboard = new DecentralBitboard();
}

CentralBitboard::void clearPreviousPosition(DecentralBitboard decentralBitboard) {
    this->performBitwiseNOTForPosition(&decentralBitboard);
    this->performBitwiseANDForPosition(this, &decentralBitboard);
}

CentralBitboard::void clearPreviousPawnPosition(DecentralBitboard *decentralBitboard) {
    this->performBitwiseNOTForPosition(decentralBitboard);
    this->performBitwiseANDForPosition(this->pawnBitboard, decentralBitboard);
}

CentralBitboard::void clearPreviousKnightPosition(DecentralBitboard *decentralBitboard) {
    this->performBitwiseNOTForPosition(decentralBitboard);
    this->performBitwiseANDForPosition(this->knightBitboard, decentralBitboard);
}

CentralBitboard::void clearPreviousBishopPosition(DecentralBitboard *decentralBitboard) {
    this->performBitwiseNOTForPosition(decentralBitboard);
    this->performBitwiseANDForPosition(this->bishopBitboard, decentralBitboard);
}

CentralBitboard::void clearPreviousRookPosition(DecentralBitboard *decentralBitboard) {
    this->performBitwiseNOTForPosition(decentralBitboard);
    this->performBitwiseANDForPosition(this->rookBitboard, decentralBitboard);
}

CentralBitboard::void clearPreviousQueenPosition(DecentralBitboard *decentralBitboard) {
    this->performBitwiseNOTForPosition(decentralBitboard);
    this->performBitwiseANDForPosition(this->queenBitboard, decentralBitboard);
}

CentralBitboard::void clearPreviousKingPosition(DecentralBitboard *decentralBitboard) {
    this->performBitwiseNOTForPosition(decentralBitboard);
    this->performBitwiseANDForPosition(this->kingBitboard, decentralBitboard);
}

CentralBitboard::void setPawnPosition(DecentralBitboard *decentralBitboard) {
    this->performBitwiseORForPosition(this->pawnBitboard, decentralBitboard);
    this->performBitwiseORForPosition(this, decentralBitboard);
}

CentralBitboard::void setKnightPosition(DecentralBitboard *decentralBitboard) {
    this->performBitwiseORForPosition(this->knightBitboard, decentralBitboard);
    this->performBitwiseORForPosition(this, decentralBitboard);
}

CentralBitboard::void setBishopPosition(DecentralBitboard *decentralBitboard) {
    this->performBitwiseORForPosition(this->bishopBitboard, decentralBitboard);
    this->performBitwiseORForPosition(this, decentralBitboard);
}

CentralBitboard::void setRookPosition(DecentralBitboard *decentralBitboard) {
    this->performBitwiseORForPosition(this->rookBitboard, decentralBitboard);
    this->performBitwiseORForPosition(this, decentralBitboard);
}

CentralBitboard::void setQueenPosition(DecentralBitboard *decentralBitboard) {
    this->performBitwiseORForPosition(this->queenBitboard, decentralBitboard);
    this->performBitwiseORForPosition(this, decentralBitboard);
}

CentralBitboard::void setKingPosition(DecentralBitboard *decentralBitboard) {
    this->performBitwiseORForPosition(this->kingBitboard, decentralBitboard);
    this->performBitwiseORForPosition(this, decentralBitboard);
}

CentralBitboard::void setPawnMoves(DecentralBitboard *decentralBitboard) {
    this->performBitwiseORForMoves(this->pawnBitboard, decentralBitboard);
    this->performBitwiseORForMoves(this, decentralBitboard);
}

CentralBitboard::void setKnightMoves(DecentralBitboard *decentralBitboard) {
    this->performBitwiseORForMoves(this->knightBitboard, decentralBitboard);
    this->performBitwiseORForMoves(this, decentralBitboard);
}

CentralBitboard::void setBishopMoves(DecentralBitboard *decentralBitboard) {
    this->performBitwiseORForMoves(this->bishopBitboard, decentralBitboard);
    this->performBitwiseORForMoves(this, decentralBitboard);
}

CentralBitboard::void setRookMoves(DecentralBitboard *decentralBitboard) {
    this->performBitwiseORForMoves(this->rookBitboard, decentralBitboard);
    this->performBitwiseORForMoves(this, decentralBitboard);
}

CentralBitboard::void setQueenMoves(DecentralBitboard *decentralBitboard) {
    this->performBitwiseORForMoves(this->queenBitboard, decentralBitboard);
    this->performBitwiseORForMoves(this, decentralBitboard);
}

CentralBitboard::void setKingMoves(DecentralBitboard *decentralBitboard) {
    this->performBitwiseORForMoves(this->kingBitboard, decentralBitboard);
    this->performBitwiseORForMoves(this, decentralBitboard);
}