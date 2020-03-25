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
#include "Board.h"
#include "NextPiece.h"
#include "TextBox.h"
#include "HighScores.h"
#include "ArcadePlayerName.h"

enum GameState {
    PLAYING = 0,
    GAME_OVER,
    TYPING
};

class TetrisGame : public Game {

public:
    virtual void Init(GameController& controller) override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen& screen) override;
    virtual const std::string& GetName() const override;
    void ResetGame();
private:
    
    void MoveDownFaster();
    void CheckIfHighScore();
    void ConfirmNewHighScore();
    
    Piece mPiece;
    Board mBoard;
    NextPiece mNextPiece;
    TextBox mTextBox;
    HighScores mHighScores;
    
    GameState mGameState;
    ArcadePlayerName mArcadePlayerName;
    
    int mArcadePlayerNameCurrentIndex;
    
    
    bool mGameOver;
    float mTimer;
    float mWaitTime;
    
    const float INITIAL_WAIT_TIME = 0.5f;
};

#endif /* TetrisGame_h */
