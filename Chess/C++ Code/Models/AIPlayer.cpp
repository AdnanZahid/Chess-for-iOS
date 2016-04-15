//
//  AIPlayer.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/29/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

#include <limits>
#include "Player.cpp"

class AIPlayer : public Player {

private:
    
public:
    AIPlayer(ErrorDelegate *errorDelegate, InputDelegate *inputDelegate, Color color, Board *board) : Player(errorDelegate, inputDelegate, color, board) {
        this->isAI = true;
    }
    
    void generateMove() {
        
        Move move = this->firstAlphaBeta(MAX_PLIES, this, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        this->inputDelegate->inputTaken(move.from, move.to);
    }
    
    Move firstAlphaBeta(int depth, Player *player, int alpha, int beta) {
        
        Move bestValue = { { '\0', '\0' }, { '\0', '\0' }, std::numeric_limits<int>::min() };
        
        for(std::list<Piece>::iterator pieceNode = player->piecesList.begin(); pieceNode != player->piecesList.end(); pieceNode++) {
            
            std::list<Position> moves = player->centralBitboard->computePositionsFromBitboard(pieceNode->pieceStrategy->decentralBitboard->moves);
            
            for(std::list<Position>::iterator iterator = moves.begin(); iterator != moves.end(); iterator++) {
                
                Position fromPosition = pieceNode->position;
                Position toPosition = *iterator;
                
                if (pieceNode->moveTo(toPosition) == true) {
                    player->updateMoves();
                    
                    Move value = { fromPosition, toPosition, -(alphaBeta(depth - 1, player->opponent, -beta, -alpha)) };
                    
                    pieceNode->undoMove();
                    player->updateMoves();
                    
                    if (value.evaluationValue > bestValue.evaluationValue) {
                        bestValue = value;
                    }
                    
                    if(bestValue.evaluationValue >= beta) {
                        break;
                    } else if(bestValue.evaluationValue > alpha) {
                        alpha = bestValue.evaluationValue;
                    }
                }
            }
        }
        
        return bestValue;
    }
    
    int alphaBeta(int depth, Player *player, int alpha, int beta) {
        
        if(depth == 0) {
            if (player->color == white) {
                return this->board->evaluationValue;
            } else {
                return -(this->board->evaluationValue);
            }
        }
        
        int bestValue = std::numeric_limits<int>::min();
                
        for(std::list<Piece>::iterator pieceNode = player->piecesList.begin(); pieceNode != player->piecesList.end(); pieceNode++) {
            
            std::list<Position> moves = player->centralBitboard->computePositionsFromBitboard(pieceNode->pieceStrategy->decentralBitboard->moves);
            
            for(std::list<Position>::iterator iterator = moves.begin(); iterator != moves.end(); iterator++) {
                
                Position fromPosition = pieceNode->position;
                Position toPosition = *iterator;
                
                if (pieceNode->moveTo(toPosition) == true) {
                    player->updateMoves();
                    
                    int value = -(this->alphaBeta(depth - 1, player->opponent,-beta,-alpha));
                    
                    pieceNode->undoMove();
                    player->updateMoves();
                    
                    if (value > bestValue) {
                        bestValue = value;
                    }
                    
                    if(bestValue >= beta) {
                        break;
                    } else if(bestValue > alpha) {
                        alpha = bestValue;
                    }
                }
            }
        }
        
        return bestValue;
    }
};