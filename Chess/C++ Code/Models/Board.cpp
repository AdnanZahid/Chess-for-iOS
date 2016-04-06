//
//  Board.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/11/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "../Headers/Board.hpp"
    
Board::Piece *getPieceOnPosition(Position position) {
    Index index = Board::positionToIndex(position);
    Piece *piece = this->pieceArray[index.y][index.x];
    
    return piece;
}

Board::void setPieceOnPosition(Piece *piece, Position position) {
    
    Index index = Board::positionToIndex(position);
    this->pieceArray[index.y][index.x] = piece;
}

Board::static Index positionToIndex(Position position) {
    
    Index index;
    
    index.x = position.file - 'a';
    index.y = position.rank - '1';
    
    return index;
}

Board::static Position indexToPosition(int x, int y) {
    
    Position position;
    
    position.file = x + 'a';
    position.rank = y + '1';
    
    return position;
}