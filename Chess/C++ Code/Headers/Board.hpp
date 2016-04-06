//
//  Board.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/11/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "Piece.hpp"

class Board {
    
public:
    Piece *pieceArray[8][8];
    
    bool whitePresenceArray[8][8];
    bool blackPresenceArray[8][8];
    
    bool whitePawnPresenceArray[8][8];
    bool whiteKnightPresenceArray[8][8];
    bool whiteBishopPresenceArray[8][8];
    bool whiteRookPresenceArray[8][8];
    bool whiteQueenPresenceArray[8][8];
    bool whiteKingPresenceArray[8][8];
    
    bool blackPawnPresenceArray[8][8];
    bool blackKnightPresenceArray[8][8];
    bool blackBishopPresenceArray[8][8];
    bool blackRookPresenceArray[8][8];
    bool blackQueenPresenceArray[8][8];
    bool blackKingPresenceArray[8][8];
    
    bool whiteMovesArray[8][8];
    bool blackMovesArray[8][8];
    
    bool whitePawnMovesArray[8][8];
    bool whiteKnightMovesArray[8][8];
    bool whiteBishopMovesArray[8][8];
    bool whiteRookMovesArray[8][8];
    bool whiteQueenMovesArray[8][8];
    bool whiteKingMovesArray[8][8];
    
    bool blackPawnMovesArray[8][8];
    bool blackKnightMovesArray[8][8];
    bool blackBishopMovesArray[8][8];
    bool blackRookMovesArray[8][8];
    bool blackQueenMovesArray[8][8];
    bool blackKingMovesArray[8][8];
    
    int evaluationValue;
    int whiteEvaluationValue;
    int blackEvaluationValue;
    
    Piece *getPieceOnPosition(Position position);
    
    void setPieceOnPosition(Piece *piece, Position position);
    
    static Index positionToIndex(Position position);
    
    static Position indexToPosition(int x, int y);
};