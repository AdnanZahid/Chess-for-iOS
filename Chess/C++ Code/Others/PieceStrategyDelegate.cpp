//
//  PieceStrategyDelegate.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/15/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

#include "../Models/Board.cpp"

class PieceStrategyDelegate {
    
public:
    virtual bool moveTo(Position position) = 0;
    virtual bool moveKingSideRook() = 0;
    virtual bool moveQueenSideRook() = 0;
    virtual bool canCheckDuringPassing(Position position) = 0;
};