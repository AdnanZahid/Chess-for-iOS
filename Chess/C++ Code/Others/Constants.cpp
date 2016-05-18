//
//  Constants.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

#define WHITE_PLAYER Player
#define BLACK_PLAYER AIPlayer

#define MAIN_QUEUE dispatch_async(dispatch_get_main_queue(), ^(void) {
#define OTHER_QUEUE dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^(void) {

#define WHITE_CAMERA_X_POSITION 3.5f
#define WHITE_CAMERA_Y_POSITION 12.0f
#define WHITE_CAMERA_Z_POSITION 14.0f

#define BLACK_CAMERA_X_POSITION 3.5f
#define BLACK_CAMERA_Y_POSITION 12.0f
#define BLACK_CAMERA_Z_POSITION -7.0f

#define WHITE_CAMERA_X_ROTATION 0.0f
#define WHITE_CAMERA_Y_ROTATION 0.0f
#define WHITE_CAMERA_Z_ROTATION 0.0f

#define BLACK_CAMERA_X_ROTATION 0.0f
#define BLACK_CAMERA_Y_ROTATION 0.0f
#define BLACK_CAMERA_Z_ROTATION M_PI

#define LIGHT_X_POSITION 0.0f
#define LIGHT_Y_POSITION 10.0f
#define LIGHT_Z_POSITION 10.0f

#define LIFT_PIECE_Y_DISTANCE 0.5f
#define CAPTURED_PIECE_Z_DISTANCE 10.0f

#define EmptyType  @"Empty"
#define PawnType   @"Pawn"
#define KnightType @"Knight"
#define BishopType @"Bishop"
#define RookType   @"Rook"
#define QueenType  @"Queen"
#define KingType   @"King"

#define NUMBER_OF_RANKS_ON_BOARD 8
#define NUMBER_OF_FILES_ON_BOARD 8

#define MAX_PLIES 3

#define CHECK_STRING "Check!"
#define CHECKMATE_STRING "Checkmate!"
#define KING_IS_UNDER_CHECK_STRING "King is under check!"
#define INVALID_MOVE_STRING "Invalid move!"
#define WRONG_TURN_STRING "Wrong turn!"
#define PIECE_DOES_NOT_EXIST_STRING "Piece does not exist!"
#define PIECE_NOT_MOVED_STRING "Piece not moved!"
#define DESTINATION_OUT_OF_BOARD_STRING "Destination out of board"

#define FILE_A 'a'
#define FILE_B 'b'
#define FILE_C 'c'
#define FILE_D 'd'
#define FILE_F 'f'
#define FILE_G 'g'
#define FILE_H 'h'

#define RANK_ONE '1'
#define RANK_TWO '2'
#define RANK_SEVEN '7'
#define RANK_EIGHT '8'

#include <stdint.h>
typedef uint64_t U64;

typedef enum {
    EMPTY = 0,
    PAWN = 100,
    BISHOP = 305,
    KNIGHT = 300,
    ROOK = 500,
    QUEEN = 900,
    KING = 2000
} PieceType;

const int startup[8][8] = {
                            ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK,
                            PAWN,  PAWN,   PAWN,   PAWN, PAWN,  PAWN,   PAWN,  PAWN,
                            EMPTY, EMPTY,  EMPTY,  EMPTY,EMPTY, EMPTY,  EMPTY, EMPTY,
                            EMPTY, EMPTY,  EMPTY,  EMPTY,EMPTY, EMPTY,  EMPTY, EMPTY,
                            EMPTY, EMPTY,  EMPTY,  EMPTY,EMPTY, EMPTY,  EMPTY, EMPTY,
                            EMPTY, EMPTY,  EMPTY,  EMPTY,EMPTY, EMPTY,  EMPTY, EMPTY,
                            -PAWN, -PAWN,  -PAWN, -PAWN,-PAWN,  -PAWN,  -PAWN, -PAWN,
                            -ROOK,-KNIGHT,-BISHOP,-QUEEN,-KING,-BISHOP,-KNIGHT,-ROOK
                          };