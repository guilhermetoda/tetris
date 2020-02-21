//
//  Scene.h
//  SDLTest
//
//  Created by Guilherme Toda on 18/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef Scene_h
#define Scene_h

#include <string>
#include <stdint.h>
#include "GameController.h"

class Screen;
//Scene Interface
class Scene
{
public:
    virtual ~Scene() {};
    virtual void Init() = 0;
    virtual void Update(uint32_t dt) = 0;
    virtual void Draw(Screen& screen) = 0;
    virtual const std::string& GetSceneName() const = 0;
    
    GameController* GetGameController() { return &mGameController; };
    
protected:
    GameController mGameController;
    
};

#endif /* Scene_h */
