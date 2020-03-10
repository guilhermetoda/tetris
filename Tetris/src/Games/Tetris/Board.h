//
//  Board.h
//  Tetris
//
//  Created by Guilherme Toda on 04/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef Board_h
#define Board_h

#include "color.h"
#include "AARectangle.h"
#include "Definitions.h"

class Piece;
class Screen;

static const int BOARD_WIDTH = 10;
static const int BOARD_HEIGHT = 20;

struct BoardBlock
{
    bool empty = true;
    AARectangle rect;
    Color color = Color::LightGrey();
};

class Board
{
public:
    void Init(const int width, const int height, const AARectangle& boundary);
    void Update(uint32_t dt);
    void Draw(Screen& screen);
    bool IsFull();
    bool IsBlockFree(int y, int x) const;
    
    bool CheckIfMovementIsAllowed(const AARectangle block);
    void StorePiece(Piece& piece, uint32_t dt);
    
    inline const int GetRowFromBlock(const AARectangle& block) const { return (block.GetTopLeftPoint().GetY() - mOffsetBoardY)/TILE_SIZE; }
    inline const int GetColumnFromBlock(const AARectangle& block) const { return (block.GetTopLeftPoint().GetX() - mOffsetBoardX)/TILE_SIZE; }
    inline void SetGameOver() { isGameOver = true; }
    inline const bool IsGameOver() const { return isGameOver; }
    
    bool CheckGameOver(const Piece& piece) const;
    
private:
    
    BoardBlock mBlocksOnBoard[BOARD_HEIGHT][BOARD_WIDTH];
    AARectangle mBoundary;
    int mWidth;
    int mHeight;
    float mEndBoard;
    
    float mOffsetBoardX;
    float mOffsetBoardY;
    
    Color mBackgroundColor;
    bool isGameOver;
    
    bool GetBoardPositionFromBlock(const AARectangle& block, int& r, int& c);
    void DeleteRow(int row);
    void CheckRows();
    void SetEmptyBlocksOnBoard();
    
};

#endif /* Board_h */
