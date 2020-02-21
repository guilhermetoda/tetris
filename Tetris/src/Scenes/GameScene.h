//
//  GameScene.h
//  SDLTest
//
//  Created by Guilherme Toda on 18/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef GameScene_h
#define GameScene_h

#include "Scene.h"
#include "Game.h"
#include <memory>

class GameScene : public Scene
{
public:
    GameScene(std::unique_ptr<Game> optrGame);
    virtual ~GameScene() {};
    virtual void Init() override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen& screen) override;
    virtual const std::string& GetSceneName() const override;
    
private:
    std::unique_ptr<Game> mGame;
};

#endif /* GameScene_h */
