//
//  Piece.cpp
//  Tetris
//
//  Created by Guilherme Toda on 03/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include "Piece.h"
#include "App.h"
#include "Board.h"
#include <iostream>

Piece::Piece() {
    
}


void Piece::Init(TetrominosType type, const AARectangle& boundary, const Color& outlineColor, const Color& fillColor) {
    //mType = type;
    mOutlineColor = outlineColor;
    mFillColor = fillColor;
    mDirection = 0;
    mTimer = 0;
    mWaitTime = 1;
    mKeyTimer = 0;
    mBoundary = boundary;
    CreateNewPiece();
}

void Piece::Update(uint32_t dt, Board& board)
{
    Vec2D dir;
    if (mDirection != 0) {
        if ((mDirection & PieceDirection::LEFT) == PieceDirection::LEFT && (mDirection & PieceDirection::RIGHT) == PieceDirection::RIGHT) {
            dir = Vec2D::Zero;
        }
        else if (mDirection == PieceDirection::LEFT)
        {
            dir = LEFT_DIR;
        }
        else
        {
            dir = RIGHT_DIR;
        }
        
        if (mKeyTimer > MOVE_KEY_RATE) {
            MovePieceDirection(dir, SPEED_SCALAR * MsToSec(dt));
            CheckIfMovementIsAllowed(board);
            mKeyTimer = 0;
        }
        else {
            mKeyTimer += MsToSec(dt);
        }
    }
    
    
}

void Piece::ConfirmMovement()
{
    for (int i = 0; i < NUM_BLOCKS_PIECE; ++i) {
        mBlocks[i] = mBlocksMovementAux[i];
    }
}

void Piece::UndoMovement()
{
    for (int i = 0; i < NUM_BLOCKS_PIECE; ++i) {
        mBlocksMovementAux[i] = mBlocks[i];
    }
}

bool Piece::CheckIfMovementIsAllowed(Board& board)
{
    bool isAllowed = true;
    for (int i = 0; i < NUM_BLOCKS_PIECE; ++i)
    {
        if (!board.CheckIfMovementIsAllowed(mBlocksMovementAux[i]))
        {
            isAllowed = false;
            break;
        }
    }
    if (!isAllowed) {
        UndoMovement();
        return isAllowed;
    }
    
    ConfirmMovement();
    board.MoveGhostPiece(*this);
    return isAllowed;
    
}

void Piece::MovePieceDirection(const Vec2D& direction, const float velocity)
{
    //Vec2D movementSpeed = velocity * direction;
    Vec2D nextPoint = (direction * TILE_SIZE);
    //Vec2D nextPoint =
    for (size_t i = 0; i < NUM_BLOCKS_PIECE; ++i)
    {
        Vec2D currentPosition = mBlocks[i].GetTopLeftPoint();
        //mBlocksMovementAux[i].MoveBy(movementSpeed);
        mBlocksMovementAux[i].MoveTo(currentPosition+nextPoint);
    }
}

void Piece::Draw(Screen& screen, bool debug)
{
    for (int i = 0; i < NUM_BLOCKS_PIECE; ++i)
    {
        screen.Draw(mBlocks[i], mOutlineColor, true, mFillColor);
    }
}

void Piece::Rotate(Board& board)
{
    if (mType != O_TYPE)
    {
        Vec2D centerPoint = mBlocksMovementAux[1].GetTopLeftPoint();
    
        for (size_t i = 0; i < NUM_BLOCKS_PIECE; ++i)
        {
            float currentBlockX = mBlocksMovementAux[i].GetTopLeftPoint().GetX();
            float currentBlockY = mBlocksMovementAux[i].GetTopLeftPoint().GetY();
            float x = currentBlockY - centerPoint.GetY();
            float y = currentBlockX - centerPoint.GetX();
            mBlocksMovementAux[i].MoveTo({centerPoint.GetX() - x, centerPoint.GetY() + y});
        }
        CheckIfMovementIsAllowed(board);
    }
}

void Piece::CreateNewPiece(TetrominosType newType, bool hasPosition, const Vec2D& startPosition)
{
    if (newType == TetrominosType::NUM_TYPES)
    {
        TetrominosType type = static_cast<TetrominosType>(rand() % TetrominosType::NUM_TYPES);
        mType = type;
    }
    else {
        mType = newType;
    }
    
    Vec2D gameStartPosition;
    if (!hasPosition)
    {
        gameStartPosition = Vec2D(mBoundary.GetWidth()/2, mBoundary.GetTopLeftPoint().GetY());
    }
    else {
        gameStartPosition = Vec2D(startPosition.GetX(), startPosition.GetY());
    }
    
    for (size_t i = 0; i < NUM_BLOCKS_PIECE; ++i)
    {
        Vec2D blockStartPosition = INITIAL_POSITION_TETROMINOS[mType][i] + gameStartPosition;
        AARectangle rect = {blockStartPosition, TILE_SIZE, TILE_SIZE};
        mBlocks[i] = rect;
        mBlocksMovementAux[i] = rect;
    }
    
}

void Piece::MoveTo(const Vec2D& position) {
    
}

const int Piece::GetLowestBlock() const
{
    float lowestPositionY = 0.0f;
    int lowestBlock = 0;
    for (int i = 0; i < NUM_BLOCKS_PIECE; ++i)
    {
        if (mBlocks[i].GetTopLeftPoint().GetY() > lowestPositionY) {
            lowestPositionY = mBlocks[i].GetTopLeftPoint().GetY();
            lowestBlock = i;
        }
    }
    
    return lowestBlock;
}
