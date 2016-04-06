//
//  Player.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/9/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "ErrorDelegate.hpp"
#include "InputDelegate.hpp"
#include "PieceDelegate.hpp"
#include "Piece.hpp"

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
    LinkedList<Piece> *piecesList;
    Player *opponent;
    int evaluationValue = 0;
    bool isAI;
    
    Player(ErrorDelegate *errorDelegate, InputDelegate *inputDelegate, Color color, Board *board);
    
    void addPiece(Piece *piece);
    
    void removePiece(Piece *piece);
    
    bool isUnderCheck();
    
    bool isUnderCheckmate();
    
    void setupPieces();
    
    void createPiece(int value, Position position);
    
    bool takeTurn(Position from, Position to);
    
    void updateMoves();
    
    bool movePiece(Position from, Position to);
    
    bool moveKingSideRook();
    
    bool moveQueenSideRook();
    
    bool canCheckDuringPassing(Position position);
};