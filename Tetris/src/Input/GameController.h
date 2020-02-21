//
//  GameController.h
//  SDLTest
//
//  Created by Guilherme Toda on 18/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef GameController_h
#define GameController_h

#include "InputAction.h"
#include <vector>

class GameController
{
public:
    GameController();
    InputAction GetActionForKey(InputKey key);
    void AddInputActionForKey(const ButtonAction& buttonAction);
    void ClearAll();
    static bool IsPressed(InputState state);
    static bool IsReleased(InputState state);
    static InputKey ActionKey();
    static InputKey CancelKey();
    static InputKey LeftKey();
    static InputKey RightKey();
    static InputKey UpKey();
    static InputKey DownKey();
    
    inline const MouseMovedAction& GetMouseMovedAction() { return mMouseMovedAction; }
    inline void SetMouseMovedAction(const MouseMovedAction& mouseMovedAction) { mMouseMovedAction = mouseMovedAction; }
    
    MouseInputAction GetMouseButtonActionForMouseButton(MouseButton button);
    void AddMouseButtonAction(const MouseButtonAction& mouseButtonAction);
    static MouseButton LeftClickButton();
    static MouseButton RightClickButton();
    
private:
    std::vector<ButtonAction> mButtonActions;
    std::vector<MouseButtonAction> mMouseButtonActions;
    MouseMovedAction mMouseMovedAction;
    
};


#endif /* GameController_h */
