//
//  EvaluationValueHandler.cpp
//  Chess
//
//  Created by Adnan Zahid on 4/2/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "LinkedList.hpp"
#include "Piece.hpp"

class EvaluationValueHandler {

public:
    int getEvaluationValue(LinkedList<Piece> *piecesList);
};