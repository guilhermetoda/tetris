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

void TetrisGame::Init(GameController& controller) {
    //srand(time(NULL));
    
    controller.ClearAll();
    
    ButtonAction rotateAction;
    rotateAction.key = GameController::ActionKey();
    rotateAction.action = [this](uint32_t dt, InputState state) {
        if (GameController::IsPressed(state))
        {
            mPiece.Rotate(mBoard);
            
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
    
    //mBoard.Init(BOARD_WIDTH, BOARD_HEIGHT, 10);
    ResetGame();
}

void TetrisGame::Update(uint32_t dt)
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
                ResetGame();
            }
            
        }
        mTimer = 0;
    }
    else {
        mTimer += MsToSec(dt);
    }
}

void TetrisGame::MoveDownFaster()
{
    mWaitTime = 0.1f;
}

void TetrisGame::Draw(Screen& screen) {
    mBoard.Draw(screen);
    mPiece.Draw(screen);
    mNextPiece.Draw(screen);
    
}

const std::string& TetrisGame::GetName() const {
    static std::string title = "The Tetris";
    return title;
}

void TetrisGame::ResetGame()
{
    float endBoard = BOARD_HEIGHT * TILE_SIZE;
    float widthBoundary = BOARD_WIDTH * TILE_SIZE;
    
    mTimer = 0;
    mWaitTime = INITIAL_WAIT_TIME;
    
    Vec2D initialPosition = { 0.0f , App::Singleton().Height() - endBoard};
    AARectangle gameBoundary = { initialPosition, (uint32_t)widthBoundary, (uint32_t)endBoard };
    TetrominosType type = TetrominosType::T_TYPE;
   
    Vec2D nextPieceBoardPosition = { gameBoundary.GetBottomRightPoint().GetX() + TILE_SIZE, gameBoundary.GetTopLeftPoint().GetY() + TILE_SIZE };
    mNextPiece.Init(nextPieceBoardPosition, TILE_SIZE * 6, TILE_SIZE * 4);
    mNextPiece.GenerateNextPiece();
    
    mBoard.Init(BOARD_WIDTH, BOARD_HEIGHT, gameBoundary);
    mPiece.Init(type, gameBoundary, Color::White(), Color::Red());
}
