//
//  InputDelegate.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/29/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

#include "../Models/Board.cpp"

class InputDelegate {
    
public:
    virtual void inputTaken(Position from, Position to) = 0;
};