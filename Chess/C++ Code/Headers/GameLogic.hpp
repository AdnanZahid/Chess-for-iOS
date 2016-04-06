//
//  GameLogic.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/7/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "ErrorDelegate.hpp"
#include "InputDelegate.hpp"
#include "Player.hpp"

class GameLogic : ErrorDelegate, InputDelegate {

public:
    Player *currentPlayer;
    
    GameLogic(ErrorDelegate *errorDelegate, InputDelegate *inputDelegate);
    
    Board *getBoard();
    
    bool movePiece(Position from, Position to);
    
    bool shouldTakeInputFromHuman();
    
    void inputTaken(Position from, Position to);
    
    void askAIToGenerateMove();
    
    void error(std::string message);
};