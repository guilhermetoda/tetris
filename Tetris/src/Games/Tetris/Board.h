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
#include <vector>

class Piece;
class Screen;

static const int BOARD_WIDTH = 10;
static const int BOARD_HEIGHT = 20;

//static const Color GHOST_COLOR = Color::Green();

struct BoardBlock
{
    bool empty = true;
    bool isGhost = false;
    AARectangle rect;
    Color color = {40,40,40,255};
};

struct GhostBlockPosition
{
    int xPosition;
    int yPosition;
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
    
    bool CheckAndRemovesGhostPiece(int y, int x);
    
    bool HasBlockAbove(int row, int pieceRow, int column);
    
    void MoveGhostPiece(const Piece& piece);
    void ClearGhostVector();
    void SetGhostVector();
    
private:
    std::vector<GhostBlockPosition> mGhostVector;
    BoardBlock mBlocksOnBoard[BOARD_HEIGHT][BOARD_WIDTH];
    AARectangle mBoundary;
    int mWidth;
    int mHeight;
    float mEndBoard;
    
    float mOffsetBoardX;
    float mOffsetBoardY;
    
    Color mBackgroundColor;
    Color mGhostPieceColor;
    bool isGameOver;
    
    bool GetBoardPositionFromBlock(const AARectangle& block, int& r, int& c);
    void DeleteRow(int row);
    void CheckRows();
    void SetEmptyBlocksOnBoard();
    int GetFirstEmptyRow(int row,int column, int maxRow = BOARD_HEIGHT);
    
};

#endif /* Board_h */
