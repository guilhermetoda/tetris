//
//  TextBox.h
//  Tetris
//
//  Created by Guilherme Toda on 24/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef TextBox_h
#define TextBox_h
#include <stdint.h>
#include "AARectangle.h"

class Screen;


class TextBox
{
public:
    void Init(const AARectangle& boundary);
    void Update(uint32_t dt);
    void Draw(Screen& screen);

private:
    AARectangle mBox;
};

#endif /* TextBox_h */
