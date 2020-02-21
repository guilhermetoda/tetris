//
//  InputController.h
//  SDLTest
//
//  Created by Guilherme Toda on 18/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef InputController_h
#define InputController_h

#include "InputAction.h"

class GameController;

class InputController
{
public:
    InputController();
    void Init(InputAction quitAction);
    void Update(uint32_t dt);
    void SetGameController(GameController* controller);
    
private:
    InputAction mQuit;
    GameController *mnoptrCurrentController;
    
};

#endif /* InputController_h */
