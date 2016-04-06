//
//  Pawn.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

class PawnStrategy : public PieceStrategy {
    
public:
    PawnStrategy(Board *board);
    
    bool move(Position from, Position to);
};