//
//  NextPiece.h
//  Tetris
//
//  Created by Guilherme Toda on 09/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef NextPiece_h
#define NextPiece_h

#include "Definitions.h"
#include "AARectangle.h"
#include "Piece.h"

class Screen;

class NextPiece
{
public:
    void Init(const Vec2D& topLeftPos, uint32_t width, uint32_t height);
    void Draw(Screen& screen);
    void UpdateNextPiece(TetrominosType newType);
    void GenerateNextPiece();

    inline const Piece GetNextPiece() const { return mNextPiece; }
    
    bool hasNextPiece = false;
private:
    AARectangle mBox;
    Piece mNextPiece;
    
};

#endif /* NextPiece_h */
