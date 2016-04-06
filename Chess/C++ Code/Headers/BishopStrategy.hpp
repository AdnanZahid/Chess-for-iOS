//
//  BishopStrategy.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "Board.hpp"
#include "PieceStrategy.hpp"

class BishopStrategy : public PieceStrategy {
    
public:
    BishopStrategy(Board *board) : PieceStrategy(board);
    
    static void getMoves(PieceStrategy *pieceStrategy, LinkedList<Position> *movesList);
    
    bool move(Position from, Position to);
    
    static bool move(Board *board, Position from, Position to);
};