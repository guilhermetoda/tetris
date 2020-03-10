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
#include "Definitions.h"

class Screen;
class Board;

enum PieceDirection
{
    LEFT = 1 << 0,
    RIGHT = 1 << 1
};

const float SPEED_SCALAR = 1.0f;
static const float MOVE_KEY_RATE = 0.1f;

class Piece {
public:
    Piece();
    void Init(TetrominosType type, const AARectangle& boundary, const Color& outlineColor, const Color& fillColor);
    void Update(uint32_t dt, Board& board);
    void Draw(Screen& screen, bool debug = false);
    void Rotate(Board& board);
    void MoveTo(const Vec2D& position);
    void MovePieceDirection(const Vec2D& direction, const float velocity = SPEED_SCALAR);
    void ConfirmMovement();
    void UndoMovement();
    
    bool CheckIfMovementIsAllowed(Board& boardmGameOver);
    
    //inline AARectangle* GetBlocks() const { return mBlocks; }
    
    inline bool IsMovingLeft() const { return mDirection == PieceDirection::LEFT; }
    inline bool IsMovingRight() const { return mDirection == PieceDirection::RIGHT; }
    
    inline void SetMovementDirection(PieceDirection dr) { mDirection |= dr; }
    inline void UnsetMovementDirection(PieceDirection dr) { mDirection &= ~dr; }
    inline void StopMovement() { mDirection = 0; }
    
    inline const Color& GetOutlineColor() const { return mOutlineColor; }
    inline const Color& GetFillColor() const { return mFillColor; }
    
    inline const TetrominosType GetType() const { return mType; }
    
    void CreateNewPiece(TetrominosType newType = TetrominosType::NUM_TYPES, bool hasPosition = false, const Vec2D& startPosition = Vec2D::Zero);
    
    AARectangle mBlocks[NUM_BLOCKS_PIECE];
    AARectangle mBlocksMovementAux[NUM_BLOCKS_PIECE];
private:
    uint32_t mDirection;
    Color mOutlineColor;
    Color mFillColor;
    TetrominosType mType;
    
    AARectangle mBoundary;
    float mTimer;
    float mWaitTime;
    float mKeyTimer;
    
};

#endif /* Piece_h */
