//
//  GameLogic.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/7/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

#include "../Others/ErrorDelegate.cpp"
#include "../Others/InputDelegate.cpp"
#include "Board.cpp"
#include "Player.cpp"
#include "AIPlayer.cpp"

class GameLogic : ErrorDelegate, InputDelegate {
    
private:
    Board *board;
    WHITE_PLAYER *whitePlayer;
    BLACK_PLAYER *blackPlayer;
    ErrorDelegate *errorDelegate;
    InputDelegate *inputDelegate;

public:
    Player *currentPlayer;
    
    GameLogic(ErrorDelegate *errorDelegate, InputDelegate *inputDelegate) {
        this->board = new Board();
        this->errorDelegate = errorDelegate;
        this->inputDelegate = inputDelegate;
        this->whitePlayer = new WHITE_PLAYER(this, this, white, this->board);
        this->blackPlayer = new BLACK_PLAYER(this, this, black, this->board);
        this->whitePlayer->opponent = this->blackPlayer;
        this->blackPlayer->opponent = this->whitePlayer;
        this->currentPlayer = this->whitePlayer;
        
        this->whitePlayer->updateMoves();
        this->blackPlayer->updateMoves();
    }
    
    Board *getBoard() {
        return this->board;
    }
    
    bool movePiece(Position from, Position to) {
        
        if (this->currentPlayer->takeTurn(from, to) == true) {
            this->currentPlayer = this->currentPlayer->opponent;
            
            this->whitePlayer->updateMoves();
            this->blackPlayer->updateMoves();
            
            return true;
        }
        
        return false;
    }
    
    bool shouldTakeInputFromHuman() {
        return not this->currentPlayer->isAI;
    }
    
    void inputTaken(Position from, Position to) {
        this->inputDelegate->inputTaken(from, to);
    }
    
    void askAIToGenerateMove() {
        ((AIPlayer *)this->currentPlayer)->generateMove();
    }
    
    void error(std::string message) {
        this->errorDelegate->error(message);
    }
};