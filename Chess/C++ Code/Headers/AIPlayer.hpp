//
//  AIPlayer.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/29/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include <limits>

#include "BasicStructs.h"
#include "Player.hpp"
#include "ErrorDelegate.hpp"
#include "InputDelegate.hpp"

class AIPlayer : public Player {
    
public:
    AIPlayer(ErrorDelegate *errorDelegate, InputDelegate *inputDelegate, Color color, Board *board);
    
    void generateMove();
    
    Move firstMiniMax(int depth, Player *player);
    
    int miniMax(int depth, Player *player);
};