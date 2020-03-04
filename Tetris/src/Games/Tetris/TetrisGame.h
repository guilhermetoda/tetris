//
//  TetrisGame.h
//  Tetris
//
//  Created by Guilherme Toda on 21/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef TetrisGame_h
#define TetrisGame_h

#include "Game.h"
#include "Piece.h"

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

class TetrisGame : public Game {

public:
    virtual void Init(GameController& controller) override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen& screen) override;
    virtual const std::string& GetName() const override;
private:
    Piece mPiece;
};

#endif /* TetrisGame_h */
