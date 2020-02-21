//
//  InputAction.h
//  SDLTest
//
//  Created by Guilherme Toda on 18/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef InputAction_h
#define InputAction_h

#include <functional>
#include <stdint.h>

using InputKey = uint8_t;
using InputState = uint8_t;
using MouseButton = uint8_t;

using InputAction = std::function<void(uint32_t dt, InputState)>;

struct ButtonAction
{
    InputKey key;
    InputAction action;
};

struct MousePosition
{
    int32_t xPos;
    int32_t yPos;
};

using MouseMovedAction = std::function<void(const MousePosition& mousePosition)>;
using MouseInputAction = std::function<void(InputState state, const MousePosition& mousePosition)>;

struct MouseButtonAction
{
    MouseButton mouseButton;
    MouseInputAction mouseInputAction;
};
#endif /* InputAction_h */
