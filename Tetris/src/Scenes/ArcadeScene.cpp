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
    Triangle tri = { Vec2D(0,0), Vec2D(100,200), Vec2D(0,200) };
    AARectangle rect = { Vec2D(screen.GetWidth()/2 - 25,screen.GetHeight()/2 - 25), 50, 50};
    Circle circle = { Vec2D(screen.GetWidth()/2+50, screen.GetHeight()/2 + 50), 50};
    
    tri.MoveTo(Vec2D(screen.GetWidth() / 2.0f, screen.GetHeight() / 2.0f));
    screen.Draw(tri, Color::Green(), true, Color::Green());
    screen.Draw(rect, Color::Blue(), true, Color::Blue());
    screen.Draw(circle, Color(0,255, 0, 150), true, Color(0,255, 0, 150));
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
