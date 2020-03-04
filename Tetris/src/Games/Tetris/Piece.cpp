//
//  Piece.cpp
//  Tetris
//
//  Created by Guilherme Toda on 03/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include "Piece.h"
#include "App.h"
#include <iostream>

Piece::Piece() {
    mType = TetrominosType::T_TYPE;
    Init(mType, Color::White(), Color::Red());
}
void Piece::Init(TetrominosType type, const Color& outlineColor, const Color& fillColor) {
    mOutlineColor = outlineColor;
    mFillColor = fillColor;
    Vec2D gameStartPosition = Vec2D(App::Singleton().Width()/2, 30.0f);
    std::vector<AARectangle> blocks;
    for (size_t i = 0; i < NUM_BLOCKS_PIECE; ++i)
    {
        Vec2D blockStartPosition = INITIAL_POSITION_TETROMINOS[mType][i] + gameStartPosition;
        std::cout << INITIAL_POSITION_TETROMINOS[mType][i];
        AARectangle rect = {blockStartPosition, TILE_SIZE, TILE_SIZE};
        blocks.push_back(rect);
    }
    mBlocks = blocks;
}

void Piece::Update(uint32_t dt)
{
    Vec2D velocity = { 0.0f, 60.0f };
    for (size_t i = 0; i < NUM_BLOCKS_PIECE; ++i)
    {
        mBlocks[i].MoveBy(velocity * MsToSec(dt));
    }
}

void Piece::Draw(Screen& screen)
{
    for (int i = 0; i < NUM_BLOCKS_PIECE; ++i)
    {
        screen.Draw(mBlocks[i], mOutlineColor, true, mFillColor);
    }
}

void Piece::Rotate()
{
    Vec2D centerPoint = mBlocks[1].GetTopLeftPoint();
    
    for (size_t i=0; i < mBlocks.size(); ++i) {
        std::cout << mBlocks[i].GetTopLeftPoint();
    }
    
    for (size_t i = 0; i < mBlocks.size(); ++i)
    {
        float currentBlockX = mBlocks[i].GetTopLeftPoint().GetX();
        float currentBlockY = mBlocks[i].GetTopLeftPoint().GetY();
        float x = currentBlockY - centerPoint.GetY();
        float y = currentBlockX - centerPoint.GetX();
        //std::cout << mBlocks[i].GetTopLeftPoint() << std::endl;
        mBlocks[i].MoveTo({centerPoint.GetX() - x, centerPoint.GetY() + y});
        std::cout << mBlocks[i].GetTopLeftPoint();
    }
    

}

void Piece::MoveTo(const Vec2D& position) {
    
}
