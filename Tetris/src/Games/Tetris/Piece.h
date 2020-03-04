//
//  Tetrononimo.h
//  Tetris
//
//  Created by Guilherme Toda on 21/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef Piece_h
#define Piece_h

#include <stdint.h>
#include <vector>
#include "Vec2D.h"
#include "color.h"
#include "AARectangle.h"

class Screen;

const int TILE_SIZE = 10;
const int NUM_BLOCKS_PIECE = 4;

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

const Vec2D INITIAL_POSITION_TETROMINOS[7][4] = {
    {Vec2D(0.0f, -TILE_SIZE), Vec2D(0.0f, 0.0f), Vec2D(TILE_SIZE, -TILE_SIZE), Vec2D(TILE_SIZE, 0.0f)},
    {Vec2D(-TILE_SIZE, 0.0f), Vec2D(0.0f, 0.0f), Vec2D(TILE_SIZE, 0.0f), Vec2D(2*TILE_SIZE, 0.0f)},
    {Vec2D(0.0f, TILE_SIZE), Vec2D(0.0f, 0.0f), Vec2D(-TILE_SIZE, 0), Vec2D(TILE_SIZE, 0)},
    {Vec2D(0.0f, -TILE_SIZE), Vec2D(0.0f, 0.0f), Vec2D(TILE_SIZE, 0), Vec2D(2*TILE_SIZE, 0)},
    {Vec2D(0.0f, TILE_SIZE), Vec2D(0.0f, 0.0f), Vec2D(TILE_SIZE, 0), Vec2D(2*TILE_SIZE, 0)},
    {Vec2D(-TILE_SIZE, 0.0f), Vec2D(0.0f, 0.0f), Vec2D(0.0f, -TILE_SIZE), Vec2D(TILE_SIZE, -TILE_SIZE)},
    {Vec2D(-TILE_SIZE, 0.0f), Vec2D(0.0f, 0.0f), Vec2D(0.0f, TILE_SIZE), Vec2D(TILE_SIZE, TILE_SIZE)}
};

class Piece {
public:
    Piece();
    void Init(TetrominosType type, const Color& outlineColor, const Color& fillColor);
    void Update(uint32_t dt);
    void Draw(Screen& screen);
    void Rotate();
    void MoveTo(const Vec2D& position);
    
    inline const Color& GetOutlineColor() const { return mOutlineColor; }
    inline const Color& GetFillColor() const { return mFillColor; }
private:
    Color mOutlineColor;
    Color mFillColor;
    TetrominosType mType;
    std::vector<AARectangle> mBlocks;
};

#endif /* Piece_h */
