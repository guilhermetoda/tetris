//
//  MainMenuScene.cpp
//  Tetris
//
//  Created by Guilherme Toda on 25/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//
#include "App.h"
#include "MainMenuScene.h"
#include "GameController.h"
#include "screen.h"
#include "AARectangle.h"
#include "GameScene.h"
#include <vector>
#include "TetrisGame.h"
#include "HighScoreScene.h"

MainMenuScene::MainMenuScene():ButtonScene({"Play Game", "High Score", "Quit Game"}, Color::Blue())
{
    
}

void MainMenuScene::Init()
{
    std::vector<Button::ButtonAction> actions;
    
    actions.push_back([this]{
        App::Singleton().PushScene(GetScene(PLAY));
    });
    
    actions.push_back([this]{
        App::Singleton().PushScene(GetScene(HIGHSCORE));
    });
    
    actions.push_back([this]{
        SDL_Quit();
    });
    SetButtonActions(actions);
    
    ButtonScene::Init();
}

void MainMenuScene::Update(uint32_t dt)
{

}

void MainMenuScene::Draw(Screen &screen)
{
    const BitmapFont& font = App::Singleton().GetFont();
    
    
    AARectangle rect = { Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height()};
    Vec2D textPosition;
    std::string scoreText = "TETRIS";
    
    textPosition = font.GetDrawPosition(scoreText, rect, BFXA_CENTER, BFYA_TOP);
    textPosition.SetY(textPosition.GetY() + 20);
    screen.Draw(font, scoreText, textPosition, Color::Red());
    
    std::string byText = "By Guilherme Toda";
    
    textPosition = font.GetDrawPosition(byText, rect, BFXA_CENTER, BFYA_BOTTOM);
    textPosition.SetY(textPosition.GetY() - 10);
    screen.Draw(font, byText, textPosition, Color::Green());
    
    
    ButtonScene::Draw(screen);
}

const std::string& MainMenuScene::GetSceneName() const
{
    static std::string sceneName = "Tetris ";
    return sceneName;
}

std::unique_ptr<Scene> MainMenuScene::GetScene(eScenes scene)
{
    switch (scene) {
        case PLAY:
        {
            std::unique_ptr<TetrisGame> tetrisGame = std::make_unique<TetrisGame>();
            std::unique_ptr<GameScene> tetrisScene = std::make_unique<GameScene>(std::move(tetrisGame));
            return tetrisScene;
        }
        break;
        case HIGHSCORE:
        {
            std::unique_ptr<Scene> highScoreScene = std::make_unique<HighScoreScene>();
            return highScoreScene;
        }
        break;
        case QUIT:
        {
                    
        }
        break;
        default:
        break;
    }
    return nullptr;
}
