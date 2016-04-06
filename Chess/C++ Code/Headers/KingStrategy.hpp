//
//  KingStrategy.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

class KingStrategy : public PieceStrategy {
    
public:
    KingStrategy(Board *board) : PieceStrategy(board);
    
    bool move(Position from, Position to);
};