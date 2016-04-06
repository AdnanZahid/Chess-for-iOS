//
//  CentralBitboard.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/18/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "DecentralBitboard.hpp"

class CentralBitboard : public Bitboard {
    
public:
    DecentralBitboard *pawnBitboard;
    DecentralBitboard *knightBitboard;
    DecentralBitboard *bishopBitboard;
    DecentralBitboard *rookBitboard;
    DecentralBitboard *queenBitboard;
    DecentralBitboard *kingBitboard;
    
    CentralBitboard();
    
    void clearPreviousPosition(DecentralBitboard decentralBitboard);
    
    void clearPreviousPawnPosition(DecentralBitboard *decentralBitboard);
    
    void clearPreviousKnightPosition(DecentralBitboard *decentralBitboard);
    
    void clearPreviousBishopPosition(DecentralBitboard *decentralBitboard);
    
    void clearPreviousRookPosition(DecentralBitboard *decentralBitboard);
    
    void clearPreviousQueenPosition(DecentralBitboard *decentralBitboard);
    
    void clearPreviousKingPosition(DecentralBitboard *decentralBitboard);
    
    void setPawnPosition(DecentralBitboard *decentralBitboard);
    
    void setKnightPosition(DecentralBitboard *decentralBitboard);
    
    void setBishopPosition(DecentralBitboard *decentralBitboard);
    
    void setRookPosition(DecentralBitboard *decentralBitboard);
    
    void setQueenPosition(DecentralBitboard *decentralBitboard);
    
    void setKingPosition(DecentralBitboard *decentralBitboard);
    
    void setPawnMoves(DecentralBitboard *decentralBitboard);
    
    void setKnightMoves(DecentralBitboard *decentralBitboard);
    
    void setBishopMoves(DecentralBitboard *decentralBitboard);
    
    void setRookMoves(DecentralBitboard *decentralBitboard);
    
    void setQueenMoves(DecentralBitboard *decentralBitboard);
    
    void setKingMoves(DecentralBitboard *decentralBitboard);
};