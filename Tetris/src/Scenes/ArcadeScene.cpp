//
//  ArcadeScene.cpp
//  SDLTest
//
//  Created by Guilherme Toda on 18/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include "ArcadeScene.h"
#include "Scene.h"
#include "screen.h"
#include "AARectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "color.h"
#include "GameController.h"
#include <iostream>
#include "App.h"

ArcadeScene::ArcadeScene()
{

}

void ArcadeScene::Init()
{
    ButtonAction action;
    action.key = GameController::ActionKey();
    action.action = [](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            std::cout << "Action Button pressed" << std::endl;
        }
    };
    
    mGameController.AddInputActionForKey(action);
    
    MouseButtonAction mouseAction;
    mouseAction.mouseButton = GameController::LeftClickButton();
    mouseAction.mouseInputAction = [](InputState state, const MousePosition& mousePosition)
    {
        if (GameController::IsPressed(state)) {
            //std::cout << "Mouse is pressed" << std::endl;
        }
    };
    mGameController.AddMouseButtonAction(mouseAction);
    mGameController.SetMouseMovedAction([](const MousePosition& mousePosition)
    {
        //std::cout << "Mouse Position X: " << mousePosition.xPos << ", Mouse Position Y: " << mousePosition.yPos << std::endl;
    });
    
}
void ArcadeScene::Update(uint32_t dt)
{

}

void ArcadeScene::Draw(Screen& screen)
{
    const BitmapFont& font = App::Singleton().GetFont();
    AARectangle rect = { Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height() };
    
    Vec2D textPosition;
    textPosition = font.GetDrawPosition(GetSceneName(), rect, BFXA_CENTER, BFYA_CENTER);
    screen.Draw(font, GetSceneName(), textPosition, Color::Red());
}
const std::string& ArcadeScene::GetSceneName() const
{
    static std::string sceneName = "Arcade Scene";
    return sceneName;
}

std::unique_ptr<Scene> ArcadeScene::GetScene(eGame game)
{
    switch (game) {
        case TETRIS:
        {
            
        }
        break;
        case BREAK_OUT:
        {
                
        }
        break;
        case ASTEROIDS:
        {
                    
        }
        break;
        case PACMAN:
        {
                        
        }
        break;
        default:
        break;
    }
    return nullptr;
}
