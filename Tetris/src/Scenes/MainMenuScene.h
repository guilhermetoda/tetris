//
//  MainMenuScene.h
//  Tetris
//
//  Created by Guilherme Toda on 25/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef MainMenuScene_h
#define MainMenuScene_h

#include "ButtonScene.h"

class Screen;

enum eScenes {
    PLAY = 0,
    HIGHSCORE,
    QUIT
};

class MainMenuScene: public ButtonScene {
public:
    MainMenuScene();
    virtual void Init() override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen& screen) override;
    virtual const std::string& GetSceneName() const override;

private:
    std::unique_ptr<Scene> GetScene(eScenes scene);

};

#endif /* MainMenuScene_h */
