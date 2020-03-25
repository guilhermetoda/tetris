//
//  ButtonScene.h
//  Tetris
//
//  Created by Guilherme Toda on 25/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef ButtonScene_h
#define ButtonScene_h

#include "Scene.h"
#include "Button.h"
#include <string>
#include <vector>

class Screen;

class ButtonScene: public Scene
{
public:
    ButtonScene(const std::vector<std::string>& optionNames, const Color& textColor);
    virtual void Init() override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen& screen) override;
    
    void SetButtonActions(const std::vector<Button::ButtonAction>& buttonActions);
    
private:
    void SetNextButtonHighlighted();
    void SetPreviousButtonHighlighted();
    void ExecuteCurrentButtonAction();
    void HighlightCurrentButton();
    
    std::vector<Button> mButtons;
    int mHighlightedOption;
};

#endif /* ButtonScene_h */
