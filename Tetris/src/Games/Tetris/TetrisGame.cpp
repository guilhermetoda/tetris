//
//  TetrisGame.cpp
//  Tetris
//
//  Created by Guilherme Toda on 03/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include "TetrisGame.h"
#include "GameController.h"
#include "App.h"
#include "Definitions.h"
#include <iostream>
#include "Score.h"

void TetrisGame::Init(GameController& controller) {
    //srand(time(NULL));

    controller.ClearAll();
    
    ButtonAction rotateAction;
    rotateAction.key = GameController::UpKey();
    rotateAction.action = [this](uint32_t dt, InputState state) {
        if (GameController::IsPressed(state))
        {
            if (mGameState == GAME_OVER)
            {
                mGameState = PLAYING;
                ResetGame();
            }
            else if (mGameState == PLAYING)
            {
                mPiece.Rotate(mBoard);
            }
            
        }
    };
    controller.AddInputActionForKey(rotateAction);
    
    //Adding the action for the left arrow
    ButtonAction leftKeyAction;
    leftKeyAction.key = GameController::LeftKey();
    leftKeyAction.action = [this](uint32_t dt, InputState state){
        if (GameController::IsPressed(state)) {
            mPiece.SetMovementDirection(PieceDirection::LEFT);
        }
        else
        {
            mPiece.UnsetMovementDirection(PieceDirection::LEFT);
        }
    };
    controller.AddInputActionForKey(leftKeyAction);
    //Adding the action for the right arrow
    ButtonAction rightKeyAction;
    rightKeyAction.key = GameController::RightKey();
    rightKeyAction.action = [this](uint32_t dt, InputState state){
        if (GameController::IsPressed(state)) {
            mPiece.SetMovementDirection(PieceDirection::RIGHT);
        }
        else
        {
            mPiece.UnsetMovementDirection(PieceDirection::RIGHT);
        }
    };
    controller.AddInputActionForKey(rightKeyAction);
    
    //Adding the action for the right arrow
    ButtonAction downKeyAction;
    rightKeyAction.key = GameController::DownKey();
    rightKeyAction.action = [this](uint32_t dt, InputState state){
        if (GameController::IsPressed(state)) {
            MoveDownFaster();
        }
        else
        {
            mWaitTime = INITIAL_WAIT_TIME;
        }
    };
    controller.AddInputActionForKey(rightKeyAction);
    
    ButtonAction backAction;
    backAction.key = GameController::CancelKey();
    backAction.action = [this](uint32_t dt, InputState state){
        if (GameController::IsPressed(state)) {
            App::Singleton().PopScene();
        }
    };
    controller.AddInputActionForKey(backAction);
    
    //mBoard.Init(BOARD_WIDTH, BOARD_HEIGHT, 10);
    mHighScores.Init(App::Singleton().GetBasePath() + "Assets/HighScores.dat");
    ResetGame();
}

void TetrisGame::Update(uint32_t dt)
{
    if (mGameState == PLAYING)
    {
        mPiece.Update(dt, mBoard);
        if (mTimer > mWaitTime) {
            mPiece.MovePieceDirection(DOWN_DIR, SPEED_SCALAR * MsToSec(dt));
            if (!mPiece.CheckIfMovementIsAllowed(mBoard)) {
                // If movement is not allowed, store piece in the board
                // Generates a new piece
                if (!mBoard.IsGameOver()) {
                    mBoard.StorePiece(mPiece, dt);
                    if (mNextPiece.hasNextPiece) {
                        mPiece.CreateNewPiece(mNextPiece.GetNextPiece().GetType());
                        mNextPiece.GenerateNextPiece();
                    }
                    else {
                        mNextPiece.GenerateNextPiece();
                        mPiece.CreateNewPiece();
                    }
                }
                else {
                    // Game Over
                    mGameState = GAME_OVER;
                    CheckIfHighScore();
                    //ResetGame();
                }
                
            }
            mTimer = 0;
        }
        else {
            mTimer += MsToSec(dt);
        }
    }
}

void TetrisGame::MoveDownFaster()
{
    mWaitTime = 0.1f;
}

void TetrisGame::Draw(Screen& screen) {
    if (mGameState == GAME_OVER)
    {
        const BitmapFont& font = App::Singleton().GetFont();
        AARectangle rect = { Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height()};
        Vec2D textPosition;
        std::string gameOverText = "Game Over";
              
        textPosition = font.GetDrawPosition(gameOverText, rect, BFXA_LEFT, BFYA_TOP);
        textPosition.SetY(textPosition.GetY() + 5);
        textPosition.SetX(textPosition.GetX() + 10);
        screen.Draw(font, gameOverText, textPosition, Color::Red());
    }
    mBoard.Draw(screen);
    mPiece.Draw(screen);
    mNextPiece.Draw(screen);
    mTextBox.Draw(screen);
    
}

const std::string& TetrisGame::GetName() const {
    static std::string title = "The Tetris";
    return title;
}

void TetrisGame::ResetGame()
{
    Score::ResetScore();
    float endBoard = BOARD_HEIGHT * TILE_SIZE;
    float widthBoundary = BOARD_WIDTH * TILE_SIZE;
    
    mTimer = 0;
    mWaitTime = INITIAL_WAIT_TIME;
    
    Vec2D initialPosition = { 0.0f , App::Singleton().Height() - endBoard};
    AARectangle gameBoundary = { initialPosition, (uint32_t)widthBoundary, (uint32_t)endBoard };
   
    int nextPieceOffsetYPos = 100;
    Vec2D nextPieceBoardPosition = { gameBoundary.GetBottomRightPoint().GetX() + TILE_SIZE, gameBoundary.GetTopLeftPoint().GetY() + nextPieceOffsetYPos };
    mNextPiece.Init(nextPieceBoardPosition, TILE_SIZE * 6, TILE_SIZE * 4);
    mNextPiece.GenerateNextPiece();
    
    mBoard.Init(BOARD_WIDTH, BOARD_HEIGHT, gameBoundary);
    mPiece.Init(gameBoundary, Color::White());
    Vec2D textBoxInitialPosition = { widthBoundary, 0.0f };
    AARectangle textBoxBoundaries = { textBoxInitialPosition, App::Singleton().Width() - (uint32_t)widthBoundary, App::Singleton().Height() };
    mTextBox.Init(textBoxBoundaries);
}

void TetrisGame::CheckIfHighScore()
{
    PlayerScore newScore = { Score::points, "ABC" };
    mHighScores.AddPlayerScore(newScore);
    mHighScores.PrintScores();
}
