//
//  TetrisGame.cpp
//  Tetris
//
//  Created by Guilherme Toda on 03/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include "TetrisGame.h"
#include "GameController.h"
#include <iostream>

void TetrisGame::Init(GameController& controller) {

    controller.ClearAll();
    
    ButtonAction rotateAction;
    rotateAction.key = GameController::ActionKey();
    rotateAction.action = [this](uint32_t dt, InputState state) {
        if (GameController::IsPressed(state))
        {
            std::cout << "Era pra rodar";
            mPiece.Rotate();
            
        }
    };
    controller.AddInputActionForKey(rotateAction);
}
void TetrisGame::Update(uint32_t dt)
{
    mPiece.Update(dt);
}

void TetrisGame::Draw(Screen& screen) {
    mPiece.Draw(screen);
}

const std::string& TetrisGame::GetName() const {
    static std::string title = "The Tetris";
    return title;
}
