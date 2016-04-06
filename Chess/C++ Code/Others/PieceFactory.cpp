//
//  PieceFactory.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "../Headers/PieceFactory.hpp"

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