//
//  Button.h
//  Tetris
//
//  Created by Guilherme Toda on 24/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef Button_h
#define Button_h

#include <string>
#include "AARectangle.h"
#include <functional>
#include "color.h"
#include "InputAction.h"
#include "BitmapFont.h"

class Screen;

class Button
{
public:
    using ButtonAction = std::function<void(void)>;
    Button(const BitmapFont& bitmapFont, const Color& textColor, const Color& highlightColor = Color::White());
    void Init(Vec2D topLeft, unsigned int width, unsigned int height);
    void Draw(Screen &screen);
    void ExecuteAction();
    
    inline void SetButtonText(const std::string& text) { mTitle = text; }
    inline const std::string& GetButtonText() const { return mTitle; }
    inline void SetHighlighted(bool highlighted) { mHighlighted = highlighted; }
    inline bool IsHighlighted() { return mHighlighted; }
    inline void SetButtonAction(Button::ButtonAction action) { mAction = action; }
private:
    const BitmapFont& mBitmapFont;
    std::string mTitle;
    AARectangle mBBox;
    
    bool mHighlighted;
    ButtonAction mAction;
    Color mHighlightColor;
    Color mTextColor;
};

#endif /* Button_h */
