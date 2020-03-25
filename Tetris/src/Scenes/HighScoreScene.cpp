//
//  HighScoreScene.cpp
//  Tetris
//
//  Created by Guilherme Toda on 25/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include "HighScoreScene.h"
#include "App.h"
#include "screen.h"
#include "AARectangle.h"
#include "Vec2D.h"

HighScoreScene::HighScoreScene()
{
    
}
void HighScoreScene::Init()
{
    ButtonAction backAction;
    backAction.key = GameController::CancelKey();
    backAction.action = [this](uint32_t dt, InputState state){
        if (GameController::IsPressed(state)) {
            App::Singleton().PopScene();
        }
    };
    mGameController.AddInputActionForKey(backAction);
       
    mHighScores.Init(App::Singleton().GetBasePath() + "Assets/HighScores.dat");
}
void HighScoreScene::Update(uint32_t dt)
{
}
void HighScoreScene::Draw(Screen& screen)
{
    const BitmapFont& font = App::Singleton().GetFont();
    AARectangle rect = { Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height()};
    Vec2D textPosition;
    std::string scoreText = "High Scores";
       
    textPosition = font.GetDrawPosition(scoreText, rect, BFXA_CENTER, BFYA_TOP);
    textPosition.SetY(textPosition.GetY() + 20);
    screen.Draw(font, scoreText, textPosition, Color::Red());
    for (size_t i = 0; i < mHighScores.GetHighScoreSize(); ++i)
    {
        std::string playerName = mHighScores.GetHighScores()[i].playerName;
        std::string points = std::to_string(mHighScores.GetHighScores()[i].score);
        std::string text = playerName+" - "+points;
           
        textPosition = font.GetDrawPosition(text, rect, BFXA_CENTER, BFYA_TOP);
        textPosition.SetY(textPosition.GetY() + 40+10*i);
        screen.Draw(font, text, textPosition, Color::Green());
    }
    
       
}
const std::string& HighScoreScene::GetSceneName() const
{
    static std::string name = "High Score";
    return name;
}

