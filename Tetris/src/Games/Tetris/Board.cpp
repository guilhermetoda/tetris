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
#include "Score.h"

void Board::Init(const int width, const int height, const AARectangle& boundary)
{
    mWidth = width;
    mHeight = height;
    //mEndBoard = height * tileSize;
    mBoundary = boundary;
    isGameOver = false;
    mOffsetBoardX = mBoundary.GetTopLeftPoint().GetX();
    mOffsetBoardY = mBoundary.GetTopLeftPoint().GetY();
    mBackgroundColor = {0,0,0,0};
    mGhostPieceColor = Color(190, 190, 190, 200);
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
            
            if (mBlocksOnBoard[i][j].isGhost) {
                screen.Draw(mBlocksOnBoard[i][j].rect, Color::White(), true, mGhostPieceColor);
            }
            else {
                screen.Draw(mBlocksOnBoard[i][j].rect, Color::White(), true, mBlocksOnBoard[i][j].color);
            }
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
    CheckAndRemovesGhostPiece(GetRowFromBlock(block), GetColumnFromBlock(block));
    return true;
}

bool Board::CheckAndRemovesGhostPiece(int y, int x)
{
    if (mBlocksOnBoard[y][x].isGhost) {
        ClearGhostVector();
        return true;
    }
    return false;
}

bool Board::IsBlockFree(int y, int x) const
{
    return mBlocksOnBoard[y][x].empty;
}

void Board::SetEmptyBlocksOnBoard()
{
    for (int i = 0; i < BOARD_HEIGHT; ++i)
    {
        for (int j = 0; j < BOARD_WIDTH; ++j)
        {
            Vec2D rectPosition = { mOffsetBoardX + j*TILE_SIZE, i * TILE_SIZE + mOffsetBoardY  };
            AARectangle rect = { rectPosition , TILE_SIZE, TILE_SIZE };
            BoardBlock emptyBoardBlock = { true, false, rect , Color::LightGrey()};
            mBlocksOnBoard[i][j] = emptyBoardBlock;
        }
    }
}

void Board::StorePiece(Piece& piece, uint32_t dt)
{
    piece.MovePieceDirection(DOWN_DIR, SPEED_SCALAR * MsToSec(dt));
    for (int i = 0; i < NUM_BLOCKS_PIECE; ++i)
    {
        int row, column;
        if (GetBoardPositionFromBlock(piece.mBlocks[i], row, column))  {
            mBlocksOnBoard[row][column].empty = false;
            mBlocksOnBoard[row][column].isGhost = false;
            mBlocksOnBoard[row][column].color = piece.GetFillColor();
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
    int rowsDeleted = 0;
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
            ++rowsDeleted;
        }
    }
    Score::CheckAndIncreaseScore(rowsDeleted);
}

void Board::MoveGhostPiece(const Piece& piece)
{
    int findRow = 1;
    int maxRow = BOARD_HEIGHT;
    int lowestBlock = piece.GetLowestBlock();
    ClearGhostVector();
    mGhostVector.clear();
    
    while (findRow < NUM_BLOCKS_PIECE)
    {
        int row, column;
        GetBoardPositionFromBlock(piece.mBlocks[lowestBlock], row, column);
        if (row >= maxRow) {
            break;
        }
        int emptyRow = GetFirstEmptyRow(row, column, maxRow);
        GhostBlockPosition firstGhostBlock = { emptyRow , column };
        mGhostVector.push_back(firstGhostBlock);
        
        for (int i = 0; i < NUM_BLOCKS_PIECE; ++i)
        {
            if (i != lowestBlock) {
                //Vec2D positionOnBoard = piece.mBlocks[i].GetTopLeftPoint() / TILE_SIZE;
                
                //INITIAL_POSITION_TETROMINOS[piece.GetType()][i] / TILE_SIZE;
                int blockRow, blockColumn;
                GetBoardPositionFromBlock(piece.mBlocks[i], blockRow, blockColumn);
                blockRow = emptyRow + (blockRow - row);
                blockColumn =  column + (blockColumn - column);
                if (!mBlocksOnBoard[blockRow][blockColumn].empty || HasBlockAbove(blockRow, row, blockColumn)) {
                    findRow = 1;
                    mGhostVector.clear();
                    break;
                }
                else {
                    GhostBlockPosition ghostBlock = { blockRow , blockColumn };
                    mGhostVector.push_back(ghostBlock);
                    ++findRow;
                }
            }
        }
        maxRow = emptyRow;
    }
    
    if (mGhostVector.size() >= NUM_BLOCKS_PIECE)
    {
        SetGhostVector();
    }
    
}

void Board::ClearGhostVector()
{
    for (int i = 0; i < mGhostVector.size(); ++i)
    {
        mBlocksOnBoard[mGhostVector[i].xPosition][mGhostVector[i].yPosition].isGhost = false;
    }
}


void Board::SetGhostVector()
{
    for (int i = 0; i < mGhostVector.size(); ++i)
    {
        mBlocksOnBoard[mGhostVector[i].xPosition][mGhostVector[i].yPosition].isGhost = true;
    }
}

bool Board::HasBlockAbove(int row, int pieceRow, int column)
{
    for (int j = row - 1; j > pieceRow; --j)
    {
        if (!mBlocksOnBoard[j][column].empty)
        {
            return true;
        }
    }
    return false;
}

int Board::GetFirstEmptyRow(int row, int column, int maxRow)
{
    for (int i = maxRow - 1; i > row; --i)
    {
        if (mBlocksOnBoard[i][column].empty)
        {
            // checks rows above
            if (!HasBlockAbove(i, row, column))
            {
                return i;
            }
        }
    }
    return row;
}
