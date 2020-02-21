//
//  ArcadeScene.h
//  SDLTest
//
//  Created by Guilherme Toda on 18/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef ArcadeScene_h
#define ArcadeScene_h

#include "Scene.h"


enum eGame {
    TETRIS = 0,
    BREAK_OUT,
    ASTEROIDS,
    PACMAN,
    NUM_GAMES
};

class Screen;

class ArcadeScene: public Scene {
public:
    ArcadeScene();
    virtual void Init() override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen& screen) override;
    virtual const std::string& GetSceneName() const override;

private:
    std::unique_ptr<Scene> GetScene(eGame game);
};

#endif /* ArcadeScene_h */
