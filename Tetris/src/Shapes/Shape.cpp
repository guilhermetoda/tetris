//
//  Shape.cpp
//  SDLTest
//
//  Created by Guilherme Toda on 12/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include "Shape.h"

void Shape::MoveBy(const Vec2D& deltaOffset)
{
    for (Vec2D& point : mPoints) {
        point = point + deltaOffset;
    }
}
