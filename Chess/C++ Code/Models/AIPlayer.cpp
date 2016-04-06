//
//  AIPlayer.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/29/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "../Headers/AIPlayer.hpp"

AIPlayer::AIPlayer(ErrorDelegate *errorDelegate, InputDelegate *inputDelegate, Color color, Board *board) : Player(errorDelegate, inputDelegate, color, board) {
    this->isAI = true;
}
    
AIPlayer::void generateMove() {
    
    Move move = this->firstMiniMax(MAX_PLIES, this);
    this->inputDelegate->inputTaken(move.from, move.to);
}
    
AIPlayer::Move firstMiniMax(int depth, Player *player) {
    
    Move bestValue;
    
    if(player->color == white) {
        bestValue = { { '\0', '\0' }, { '\0', '\0' }, std::numeric_limits<int>::min() };
    } else {
        bestValue = { { '\0', '\0' }, { '\0', '\0' }, std::numeric_limits<int>::max() };
    }
        
    for(LinkedList<Piece>::Node *pieceNode = player->piecesList->head; pieceNode != nullptr; pieceNode = pieceNode->next) {
        for(LinkedList<Position>::Node *moveNode = player->centralBitboard->computePositionsFromBitboard(pieceNode->value->pieceStrategy->decentralBitboard->moves)->head; moveNode != nullptr; moveNode = moveNode->next) {
            
            Position fromPosition = pieceNode->value->position;
            Position toPosition = *moveNode->value;
            
            if (pieceNode->value->moveTo(toPosition) == true) {
                player->updateMoves();
                
                Move value = { fromPosition, toPosition, miniMax(depth - 1, player->opponent) };
                
                pieceNode->value->undoMove();
                player->updateMoves();
                
                if(player->color == white) {
                    if (value.evaluationValue > bestValue.evaluationValue) {
                        bestValue = value;
                    }
                } else {
                    if (value.evaluationValue < bestValue.evaluationValue) {
                        bestValue = value;
                    }
                }
            }
        }
    }
    
    return bestValue;
}
    
AIPlayer::int miniMax(int depth, Player *player) {
    
    if(depth == 0) {
        return this->board->evaluationValue;
    }
    
    int bestValue;
    
    if(player->color == white) {
        bestValue = std::numeric_limits<int>::min();
    } else {
        bestValue = std::numeric_limits<int>::max();
    }
    
    for(LinkedList<Piece>::Node *pieceNode = player->piecesList->head; pieceNode != nullptr; pieceNode = pieceNode->next) {
        for(LinkedList<Position>::Node *moveNode = player->centralBitboard->computePositionsFromBitboard(pieceNode->value->pieceStrategy->decentralBitboard->moves)->head; moveNode != nullptr; moveNode = moveNode->next) {
            
            if (pieceNode->value->moveTo(*moveNode->value) == true) {
                player->updateMoves();
                
                int value = this->miniMax(depth - 1, player->opponent);
                
                pieceNode->value->undoMove();
                player->updateMoves();
                
                if(player->color == white) {
                    if (value > bestValue) {
                        bestValue = value;
                    }
                } else {
                    if (value < bestValue) {
                        bestValue = value;
                    }
                }
            }
        }
    }
    
    return bestValue;
}