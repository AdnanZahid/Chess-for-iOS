//
//  EvaluationValueHandler.cpp
//  Chess
//
//  Created by Adnan Zahid on 4/2/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "../Headers/EvaluationValueHandler.hpp"

EvaluationValueHandler::int getEvaluationValue(LinkedList<Piece> *piecesList) {
    
    int mobility = 0;
    int value = 0;
    
    for(LinkedList<Piece>::Node *pieceNode = piecesList->head; pieceNode != nullptr; pieceNode = pieceNode->next) {
        
        mobility += pieceNode->value->pieceStrategy->mobility;
        value += pieceNode->value->value;
    }
    
    return mobility + value;
}