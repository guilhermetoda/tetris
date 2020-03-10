//
//  Definitions.h
//  Tetris
//
//  Created by Guilherme Toda on 05/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef Definitions_h
#define Definitions_h

#include "Vec2D.h"

static const int TILE_SIZE = 12;
const int NUM_BLOCKS_PIECE = 4;
// Direction definitions
static const Vec2D UP_DIR {0, -1};
static const Vec2D DOWN_DIR {0, 1};
static const Vec2D LEFT_DIR {-1, 0};
static const Vec2D RIGHT_DIR {1, 0};

enum TetrominosType {
    O_TYPE = 0,
    I_TYPE,
    T_TYPE,
    J_TYPE,
    L_TYPE,
    S_TYPE,
    Z_TYPE,
    NUM_TYPES
};

static const Vec2D INITIAL_POSITION_TETROMINOS[7][4] = {
    {Vec2D(0.0f, -TILE_SIZE), Vec2D(0.0f, 0.0f), Vec2D(TILE_SIZE, -TILE_SIZE), Vec2D(TILE_SIZE, 0.0f)},
    {Vec2D(-TILE_SIZE, 0.0f), Vec2D(0.0f, 0.0f), Vec2D(TILE_SIZE, 0.0f), Vec2D(2*TILE_SIZE, 0.0f)},
    {Vec2D(0.0f, TILE_SIZE), Vec2D(0.0f, 0.0f), Vec2D(-TILE_SIZE, 0), Vec2D(TILE_SIZE, 0)},
    {Vec2D(0.0f, -TILE_SIZE), Vec2D(0.0f, 0.0f), Vec2D(TILE_SIZE, 0), Vec2D(2*TILE_SIZE, 0)},
    {Vec2D(0.0f, TILE_SIZE), Vec2D(0.0f, 0.0f), Vec2D(TILE_SIZE, 0), Vec2D(2*TILE_SIZE, 0)},
    {Vec2D(-TILE_SIZE, 0.0f), Vec2D(0.0f, 0.0f), Vec2D(0.0f, -TILE_SIZE), Vec2D(TILE_SIZE, -TILE_SIZE)},
    {Vec2D(-TILE_SIZE, 0.0f), Vec2D(0.0f, 0.0f), Vec2D(0.0f, TILE_SIZE), Vec2D(TILE_SIZE, TILE_SIZE)}
};

struct BoardPosition {
    int row;
    int column;
};

#endif /* Definitions_h */
