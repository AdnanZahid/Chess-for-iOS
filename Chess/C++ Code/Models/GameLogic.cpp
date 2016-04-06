//
//  GameLogic.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/7/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "../Headers/GameLogic.hpp"

GameLogic::GameLogic(ErrorDelegate *errorDelegate, InputDelegate *inputDelegate) {
    this->board = new Board();
    this->errorDelegate = errorDelegate;
    this->inputDelegate = inputDelegate;
    this->whitePlayer = new Player(this, this, white, this->board);
    this->blackPlayer = new AIPlayer(this, this, black, this->board);
    this->whitePlayer->opponent = this->blackPlayer;
    this->blackPlayer->opponent = this->whitePlayer;
    this->currentPlayer = this->whitePlayer;
    
    this->whitePlayer->updateMoves();
    this->blackPlayer->updateMoves();
}

GameLogic::Board *getBoard() {
    return this->board;
}

GameLogic::bool movePiece(Position from, Position to) {
    
    if (this->currentPlayer->takeTurn(from, to) == true) {
        this->currentPlayer = this->currentPlayer->opponent;
        
        this->whitePlayer->updateMoves();
        this->blackPlayer->updateMoves();
        
        return true;
    }
    
    return false;
}

GameLogic::bool shouldTakeInputFromHuman() {
    return not this->currentPlayer->isAI;
}

GameLogic::void inputTaken(Position from, Position to) {
    this->inputDelegate->inputTaken(from, to);
}

GameLogic::void askAIToGenerateMove() {
    ((AIPlayer *)this->currentPlayer)->generateMove();
}

GameLogic::void error(std::string message) {
    this->errorDelegate->error(message);
}