//
//  NextPiece.cpp
//  Tetris
//
//  Created by Guilherme Toda on 09/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include <stdio.h>
#include "NextPiece.h"
#include "screen.h"


void NextPiece::Init(const Vec2D& topLeftPos, uint32_t width, uint32_t height)
{
    mBox = { topLeftPos, width, height };
}

void NextPiece::Draw(Screen& screen)
{
    screen.Draw(mBox, Color::White(), true, Color::Black());
    mNextPiece.Draw(screen, true);
    
}

void NextPiece::GenerateNextPiece()
{
    Vec2D position = { mBox.GetTopLeftPoint().GetX() + 2*TILE_SIZE, mBox.GetTopLeftPoint().GetY() + TILE_SIZE};
    std::cout << position;
    UpdateNextPiece(mNextPiece.GetType());
    mNextPiece.CreateNewPiece(TetrominosType::NUM_TYPES, true, position);
    hasNextPiece = true;
}

void NextPiece::UpdateNextPiece(TetrominosType newType)
{
    AARectangle boundary = {};
    mNextPiece.Init(newType, boundary, Color::White(), Color::Red());
}
