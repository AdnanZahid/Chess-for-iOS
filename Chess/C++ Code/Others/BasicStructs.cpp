//
//  BasicStructs.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/30/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#pragma once

typedef struct {
    char rank;
    char file;
} Position;

typedef struct {
    Position from;
    Position to;
    int evaluationValue;
} Move;

typedef struct {
    int x;
    int y;
} Index;

typedef enum {
    white,
    black
} Color;