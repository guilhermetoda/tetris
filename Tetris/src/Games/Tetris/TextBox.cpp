//
//  TextBox.cpp
//  Tetris
//
//  Created by Guilherme Toda on 24/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include "TextBox.h"
#include "screen.h"
#include "BitmapFont.h"
#include "App.h"
#include "Score.h"

void TextBox::Init(const AARectangle& boundary)
{
    mBox = boundary;
}
//void Update(uint32_t dt);
void TextBox::Draw(Screen& screen)
{
    const BitmapFont& font = App::Singleton().GetFont();
    
    Vec2D textPosition;
    std::string scoreText = "Score";
    textPosition = font.GetDrawPosition(scoreText, mBox, BFXA_CENTER, BFYA_TOP);
    textPosition.SetY(textPosition.GetY() + 20);
    screen.Draw(font, scoreText, textPosition, Color::Red());
    
    std::string scorePointsText = std::to_string(Score::points);
    textPosition = font.GetDrawPosition(scorePointsText, mBox, BFXA_CENTER, BFYA_TOP);
    textPosition.SetY(textPosition.GetY() + 35);
    screen.Draw(font, scorePointsText, textPosition, Color::Red());
    
    std::string linesText = "Lines";
    textPosition = font.GetDrawPosition(linesText, mBox, BFXA_CENTER, BFYA_TOP);
    textPosition.SetY(textPosition.GetY() + 50);
    screen.Draw(font, linesText, textPosition, Color::Red());
    
    std::string linesPointsText = std::to_string(Score::lines);
    textPosition = font.GetDrawPosition(linesPointsText, mBox, BFXA_CENTER, BFYA_TOP);
    textPosition.SetY(textPosition.GetY() + 65);
    screen.Draw(font, linesPointsText, textPosition, Color::Red());
    
    std::string nextPieceText = "Next";
    textPosition = font.GetDrawPosition(nextPieceText, mBox, BFXA_LEFT, BFYA_TOP);
    textPosition.SetY(textPosition.GetY() + 130);
    textPosition.SetX(textPosition.GetX() + 20);
    screen.Draw(font, nextPieceText, textPosition, Color::Red());
}
