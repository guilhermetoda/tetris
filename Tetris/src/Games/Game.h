//
//  Game.h
//  SDLTest
//
//  Created by Guilherme Toda on 18/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <string>
#include <stdint.h>

class GameController;
class Screen;

class Game
{
public:
    virtual ~Game(){}
    virtual void Init(GameController& controller) = 0;
    virtual void Update(uint32_t dt) = 0;
    virtual void Draw(Screen& screen) = 0;
    virtual const std::string& GetName() const = 0;
    
    
};


#endif /* Game_h */
