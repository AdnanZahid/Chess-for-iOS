//
//  QueenStrategy.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

class QueenStrategy : public PieceStrategy {
    
public:
    QueenStrategy(Board *board);
    
    bool move(Position from, Position to);
};