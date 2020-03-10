//
//  Board.cpp
//  Tetris
//
//  Created by Guilherme Toda on 04/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include "Board.h"

#include <stdio.h>
#include "screen.h"
#include "Piece.h"
#include <iostream>

void Board::Init(const int width, const int height, const AARectangle& boundary)
{
    mWidth = width;
    mHeight = height;
    //mEndBoard = height * tileSize;
    mBoundary = boundary;
    mOffsetBoardX = mBoundary.GetTopLeftPoint().GetX();
    mOffsetBoardY = mBoundary.GetTopLeftPoint().GetY();
    mBackgroundColor = {0,0,0,0};
    SetEmptyBlocksOnBoard();
}
void Board::Update(uint32_t dt)
{
    
}
void Board::Draw(Screen& screen)
{
    screen.Draw(mBoundary, Color::White(), true, mBackgroundColor);
    for (int i = 0; i < BOARD_HEIGHT; ++i)
    {
        for (int j = 0; j < BOARD_WIDTH; ++j)
        {
            //std::cout << mBlocksOnBoard[i][j].rect.GetCenterPoint() << std::endl;
            
            screen.Draw(mBlocksOnBoard[i][j].rect, Color::White(), true, mBlocksOnBoard[i][j].color);
        }
    }
}

bool Board::IsFull()
{
    return false;
}

bool Board::CheckIfMovementIsAllowed(const AARectangle block)
{
    if(IsGreaterThanOrEqual(mBoundary.GetTopLeftPoint().GetX()-1, block.GetTopLeftPoint().GetX()))
    {
        return false;
    }
    else if (IsGreaterThanOrEqual(block.GetBottomRightPoint().GetX(), mBoundary.GetBottomRightPoint().GetX()+1))
    {
        return false;
    }
    else if (IsGreaterThanOrEqual(block.GetBottomRightPoint().GetY(), mBoundary.GetBottomRightPoint().GetY()+1))
    {
        return false;
    }
    else if (!IsBlockFree(GetRowFromBlock(block), GetColumnFromBlock(block))) {
        if (GetRowFromBlock(block) == 0) {
            SetGameOver();
        }
        return false;
    }
    return true;
}

bool Board::IsBlockFree(int y, int x) const
{
    std::cout << "Free Block: " << y << ":" << x << std::endl;
    return mBlocksOnBoard[y][x].empty;
}

void Board::SetEmptyBlocksOnBoard()
{
    std::cout << mOffsetBoardX << ":" << mOffsetBoardY << std::endl;
    for (int i = 0; i < BOARD_HEIGHT; ++i)
    {
        for (int j = 0; j < BOARD_WIDTH; ++j)
        {
            Vec2D rectPosition = { mOffsetBoardX + j*TILE_SIZE, i * TILE_SIZE + mOffsetBoardY  };
            AARectangle rect = { rectPosition , TILE_SIZE, TILE_SIZE };
            BoardBlock emptyBoardBlock = { true, rect ,Color::LightGrey() };
            mBlocksOnBoard[i][j] = emptyBoardBlock;
        }
    }
}

void Board::StorePiece(Piece& piece, uint32_t dt)
{
    piece.MovePieceDirection(DOWN_DIR,SPEED_SCALAR * MsToSec(dt));
    for (int i = 0; i < NUM_BLOCKS_PIECE; ++i)
    {
        int row, column;
        if (GetBoardPositionFromBlock(piece.mBlocks[i], row, column))  {
            mBlocksOnBoard[row][column].empty = false;
            mBlocksOnBoard[row][column].color = Color::Red();
            std::cout << row << "," << column << std::endl;
        }
        else {
            SetGameOver();
            return;
        }
        
    }
    CheckRows();
}

bool Board::GetBoardPositionFromBlock(const AARectangle& block, int& r, int& c)
{
    Vec2D blockPosition = block.GetTopLeftPoint();
    r = (blockPosition.GetY() - mOffsetBoardY)/TILE_SIZE;
    c = (blockPosition.GetX() - mOffsetBoardX)/TILE_SIZE;
    if ((r < 0 || r > BOARD_HEIGHT - 1) || (c < 0 || c > BOARD_WIDTH - 1))
    {
        return false;
    }
    return true;
}

void Board::DeleteRow(int row)
{
    for (int i = row; i > 0; --i)
    {
        for (int j = 0; j < BOARD_WIDTH; ++j)
        {
            mBlocksOnBoard[i][j].empty = mBlocksOnBoard[i-1][j].empty;
            mBlocksOnBoard[i][j].color = mBlocksOnBoard[i-1][j].color;
        }
    }
}

void Board::CheckRows()
{
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        int j = 0;
        while (j < BOARD_WIDTH) {
            if (mBlocksOnBoard[i][j].empty)
            {
                break;
            }
            j++;
        }
        if (j == BOARD_WIDTH)
        {
            DeleteRow(i);
        }
    }
}
