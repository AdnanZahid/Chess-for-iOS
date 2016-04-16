//
//  Player.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/9/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

#include "Pieces/Piece.cpp"
#include "../Others/Constants.cpp"
#include "../Others/PieceFactory.cpp"
#include "../Others/ErrorDelegate.cpp"
#include "../Others/InputDelegate.cpp"
#include "../Others/PieceDelegate.cpp"
#include "CentralBitboard.cpp"
#include "BitboardHandler.cpp"
#include "EvaluationValueHandler.cpp"

class Player : PieceDelegate {

protected:
    Piece *king;
    Piece *kingSideRook;
    Piece *queenSideRook;
    Board *board;
    
    ErrorDelegate *errorDelegate;
    InputDelegate *inputDelegate;
    BitboardHandler *bitboardHandler;
    EvaluationValueHandler *evaluationValueHandler;
    
public:
    Color color;
    CentralBitboard *centralBitboard;
    std::list<Piece> piecesList;
    Player *opponent;
    int evaluationValue = 0;
    bool isAI;
    
    Player(ErrorDelegate *errorDelegate, InputDelegate *inputDelegate, Color color, Board *board) {
        
        this->errorDelegate = errorDelegate;
        this->inputDelegate = inputDelegate;
        this->color = color;
        this->board = board;
        
        this->centralBitboard = new CentralBitboard();
        this->bitboardHandler = new BitboardHandler(this->board, this->color, this->centralBitboard);
        
        this->setupPieces();
        
        this->isAI = false;
    }
    
    void addPiece(Piece *piece) {
        if (piece != nullptr) {
            this->piecesList.push_back(*piece);
        }
    }
    
    void removePiece(Piece *piece) {
        if (piece != nullptr) {
            for(std::list<Piece>::iterator iterator = this->piecesList.begin(); iterator != this->piecesList.end(); iterator++) {
                if (iterator->order == piece->order) {
                    this->piecesList.erase(iterator);
                    break;
                }
            }
        }
    }
    
    bool isUnderCheck() {
        
        this->updateMoves();
        this->opponent->updateMoves();
        
        if ((this->opponent->centralBitboard->moves & this->king->pieceStrategy->decentralBitboard->position) != 0) {
            return true;
        }
        return false;
    }
    
    bool isUnderCheckmate() {
        
        for(std::list<Piece>::iterator pieceNode = this->piecesList.begin(); pieceNode != this->piecesList.end(); pieceNode++) {
            
            std::list<Position> moves = this->centralBitboard->computePositionsFromBitboard(pieceNode->pieceStrategy->decentralBitboard->moves);
            
            for(std::list<Position>::iterator iterator = moves.begin(); iterator != moves.end(); iterator++) {
                
                Piece *capturedPiece = this->board->getPieceOnPosition(*iterator);
                
                if ((*pieceNode).moveTo(*iterator) == true) {
                    
                    this->opponent->removePiece(capturedPiece);
                    
                    if (this->isUnderCheck() == false) {
                        pieceNode->undoMove();
                        this->opponent->addPiece(capturedPiece);
                        
                        return false;
                    }
                    pieceNode->undoMove();
                    this->opponent->addPiece(capturedPiece);
                }
            }
        }
        return true;
    }
    
    void setupPieces() {
        
        for (int rank = 0; rank < NUMBER_OF_RANKS_ON_BOARD; rank ++) {
            for (int file = 0; file < NUMBER_OF_FILES_ON_BOARD; file ++) {
                int value = startup[rank][file];
                
                if (value != 0) {
                    
                    Position position = this->board->indexToPosition(file, rank);
                    
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
    
    void createPiece(int value, Position position) {
        
        Piece *piece = PieceFactory::createPiece(value, this->color, position, this->board, this, this->centralBitboard);
        this->addPiece(piece);
        
        if (value == KING) {
            this->king = piece;
        } else if (value == ROOK && position.file == FILE_A) {
            this->queenSideRook = piece;
        } else if (value == ROOK && position.file == FILE_H) {
            this->kingSideRook = piece;
        }
        
        this->board->setPieceOnPosition(piece, position);
    }
    
    bool takeTurn(Position from, Position to) {
        
        if (this->movePiece(from, to)) {
            return true;
        }
        
        return false;
    }
    
    void updateMoves() {
        this->bitboardHandler->clearAllMovesBitboards();
        for(std::list<Piece>::iterator iterator = this->piecesList.begin(); iterator != this->piecesList.end(); iterator++) {
            iterator->updateMoves();
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
    
    bool movePiece(Position from, Position to) {
        
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
    
    bool moveKingSideRook() {
        Position position;
        position.rank = this->kingSideRook->position.rank;
        position.file = FILE_F;
        return this->movePiece(this->kingSideRook->position, position);
    }
    
    bool moveQueenSideRook() {
        Position position;
        position.rank = this->queenSideRook->position.rank;
        position.file = FILE_D;
        return this->movePiece(this->queenSideRook->position, position);
    }
    
    bool canCheckDuringPassing(Position position) {
        for(std::list<Piece>::iterator iterator = this->piecesList.begin(); iterator != this->piecesList.end(); iterator++) {
            if (iterator->canCheck(position) == true) {
                return true;
            }
        }
        return false;
    }
};