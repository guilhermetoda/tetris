//
//  Button.cpp
//  Tetris
//
//  Created by Guilherme Toda on 24/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include "Button.h"
#include "screen.h"

Button::Button(const BitmapFont& bitmapFont, const Color& textColor, const Color& highlightColor):
    mBitmapFont(bitmapFont),mTextColor(textColor), mHighlightColor(highlightColor), mTitle(""), mHighlighted(false), mAction(nullptr)
{
    
}
void Button::Init(Vec2D topLeft, unsigned int width, unsigned int height)
{
    mBBox = AARectangle(topLeft, width, height);
}
void Button::Draw(Screen &screen)
{
    screen.Draw(mBitmapFont, mTitle, mBitmapFont.GetDrawPosition(mTitle, mBBox, BFXA_CENTER, BFYA_CENTER), mTextColor);
    if (mHighlighted)
    {
        screen.Draw(mBBox, mHighlightColor);
    }
}
void Button::ExecuteAction()
{
    mAction();
}
