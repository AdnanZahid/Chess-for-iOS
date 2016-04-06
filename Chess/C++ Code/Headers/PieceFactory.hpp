//
//  PieceFactory.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include <cmath>

#include "Piece.hpp"

class PieceFactory {
    
public:
    static Piece *createPiece(int value, Color color, Position position, Board *board, PieceDelegate *pieceDelegate, CentralBitboard *centralBitboard);
};