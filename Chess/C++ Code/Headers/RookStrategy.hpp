//
//  RookStrategy.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

class RookStrategy : public PieceStrategy {
    
public:
    RookStrategy(Board *board);
    
    static void getMoves(PieceStrategy *pieceStrategy, LinkedList<Position> *movesList);
    
    bool move(Position from, Position to)
    
    static bool move(Board *board, Position from, Position to);
};