//
//  Player.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/9/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "../Headers/Player.hpp"

Player::Player(ErrorDelegate *errorDelegate, InputDelegate *inputDelegate, Color color, Board *board) {
    
    this->piecesList = new LinkedList<Piece>();
    
    this->errorDelegate = errorDelegate;
    this->inputDelegate = inputDelegate;
    this->color = color;
    this->board = board;
    
    this->centralBitboard = new CentralBitboard();
    this->bitboardHandler = new BitboardHandler(this->board, this->color, this->centralBitboard);
    
    this->setupPieces();
    
    this->isAI = false;
}

Player::void addPiece(Piece *piece) {
    if (piece != nullptr) {
        this->piecesList->add(piece);
    }
}

Player::void removePiece(Piece *piece) {
    if (piece != nullptr) {
        this->piecesList->remove(piece);
    }
}

Player::bool isUnderCheck() {
    
    this->updateMoves();
    this->opponent->updateMoves();
    
    if ((this->opponent->centralBitboard->moves & this->king->pieceStrategy->decentralBitboard->position) != 0) {
        return true;
    }
    return false;
}

Player::bool isUnderCheckmate() {
    
    for(LinkedList<Piece>::Node *pieceNode = this->piecesList->head; pieceNode != nullptr; pieceNode = pieceNode->next) {
        for(LinkedList<Position>::Node *moveNode = this->centralBitboard->computePositionsFromBitboard(pieceNode->value->pieceStrategy->decentralBitboard->moves)->head; moveNode != nullptr; moveNode = moveNode->next) {
            
            Piece *capturedPiece = this->board->getPieceOnPosition(*moveNode->value);
            
            if (pieceNode->value->moveTo(*moveNode->value) == true) {
                
                this->opponent->removePiece(capturedPiece);
                
                if (this->isUnderCheck() == false) {
                    pieceNode->value->undoMove();
                    this->opponent->addPiece(capturedPiece);
                    
                    return false;
                }
                pieceNode->value->undoMove();
                this->opponent->addPiece(capturedPiece);
            }
        }
    }
    return true;
}

Player::void setupPieces() {
    
    for (int a = 7; a > -1; a--) {
        for (int b = 0; b < 8; b++) {
            int value = startup[a][b];
            
            if (value != 0) {
                
                Position position = this->board->indexToPosition(b, a);
                
                if (this->color == white) {
                    if (value > 0) {
                        this->createPiece(std::fabs(value), position);
                    }
                } else {
                    if (value < 0) {
                        this->createPiece(std::fabs(value), position);
                    }
                }
            }
        }
    }
}

Player::void createPiece(int value, Position position) {
    
    Piece *piece = PieceFactory::createPiece(value, this->color, position, this->board, this, this->centralBitboard);
    this->addPiece(piece);
    
    if (value == KING) {
        this->king = piece;
    } else if (value == ROOK && position.file == 'a') {
        this->queenSideRook = piece;
    } else if (value == ROOK && position.file == 'h') {
        this->kingSideRook = piece;
    }
    
    this->board->setPieceOnPosition(piece, position);
}

Player::bool takeTurn(Position from, Position to) {
    
    if (this->movePiece(from, to)) {
        return true;
    }
    
    return false;
}

Player::void updateMoves() {
    this->bitboardHandler->clearAllMovesBitboards();
    for(LinkedList<Piece>::Node *node = this->piecesList->head; node != nullptr; node = node->next) {
        node->value->updateMoves();
    }
    this->bitboardHandler->updatePresenceAndMovesArrays();
    this->evaluationValue = this->evaluationValueHandler->getEvaluationValue(this->piecesList);
    
    if (this->color == white) {
        this->board->whiteEvaluationValue = this->evaluationValue;
    } else {
        this->board->blackEvaluationValue = this->evaluationValue;
    }
    
    this->board->evaluationValue = this->board->whiteEvaluationValue - this->board->blackEvaluationValue;
}

Player::bool movePiece(Position from, Position to) {
    
    Piece *piece = this->board->getPieceOnPosition(from);
    Piece *destinationPiece = this->board->getPieceOnPosition(to);
    
    if (from.rank != to.rank || from.file != to.file) {
        if (piece != nullptr) {
            if (piece->color == this->color) {
                if (piece->moveTo(to) == true) {
                    this->opponent->removePiece(destinationPiece);
                    if (this->isUnderCheck() == false) {
                        if (this->opponent->isUnderCheck() == true) {
                            if (this->opponent->isUnderCheckmate() == true) {
                                this->errorDelegate->error(CHECKMATE_STRING);
                            } else {
                                this->errorDelegate->error(CHECK_STRING);
                            }
                        }
                        return true;
                    } else {
                        piece->undoMove();
                        this->addPiece(destinationPiece);
                        this->errorDelegate->error(KING_IS_UNDER_CHECK_STRING);
                    }
                } else {
                    this->errorDelegate->error(INVALID_MOVE_STRING);
                }
            } else {
                this->errorDelegate->error(WRONG_TURN_STRING);
            }
        } else {
            this->errorDelegate->error(PIECE_DOES_NOT_EXIST_STRING);
        }
    } else {
        this->errorDelegate->error(PIECE_NOT_MOVED_STRING);
    }
    return false;
}

Player::bool moveKingSideRook() {
    Position position;
    position.rank = this->kingSideRook->position.rank;
    position.file = 'f';
    return this->movePiece(this->kingSideRook->position, position);
}

Player::bool moveQueenSideRook() {
    Position position;
    position.rank = this->queenSideRook->position.rank;
    position.file = 'd';
    return this->movePiece(this->queenSideRook->position, position);
}

Player::bool canCheckDuringPassing(Position position) {
    for(LinkedList<Piece>::Node *node = this->opponent->piecesList->head; node != nullptr; node = node->next) {
        if (node->value->canCheck(position) == true) {
            return true;
        }
    }
    return false;
}