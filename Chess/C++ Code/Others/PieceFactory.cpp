//
//  PieceFactory.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

#include <cmath>

#include "../Others/Constants.cpp"
#include "../Models/Pieces/Piece.cpp"
#include "../Models/Pieces/PawnStrategy.cpp"
#include "../Models/Pieces/KnightStrategy.cpp"
#include "../Models/Pieces/BishopStrategy.cpp"
#include "../Models/Pieces/RookStrategy.cpp"
#include "../Models/Pieces/QueenStrategy.cpp"
#include "../Models/Pieces/KingStrategy.cpp"

class PieceFactory {
    
public:
    static Piece *createPiece(int value, Color color, Position position, Board *board, PieceDelegate *pieceDelegate, CentralBitboard *centralBitboard) {
        
        Piece *piece = new Piece(value, color, board, pieceDelegate, centralBitboard);
        int absoluteValue = std::fabs(value);
        switch (absoluteValue) {
            case PAWN:
                piece->setPieceStrategy(new PawnStrategy(board));
                break;
            case KNIGHT:
                piece->setPieceStrategy(new KnightStrategy(board));
                break;
            case BISHOP:
                piece->setPieceStrategy(new BishopStrategy(board));
                break;
            case ROOK:
                piece->setPieceStrategy(new RookStrategy(board));
                break;
            case QUEEN:
                piece->setPieceStrategy(new QueenStrategy(board));
                break;
            case KING:
                piece->setPieceStrategy(new KingStrategy(board));
                break;
        }
        
        piece->setPosition(position);
        return piece;
    }
};