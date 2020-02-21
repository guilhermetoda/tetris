//
//  Shape.h
//  SDLTest
//
//  Created by Guilherme Toda on 12/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef Shape_h
#define Shape_h

#include "Vec2D.h"
#include "Utils.h"
#include <vector>

class Shape
{
public:
    virtual Vec2D GetCenterPoint() const = 0;
    virtual ~Shape() {}
    inline virtual std::vector<Vec2D> GetPoints() const { return mPoints; }
    virtual void MoveTo(const Vec2D& position) = 0;
    void MoveBy(const Vec2D& deltaOffset);
    
protected:
    std::vector<Vec2D> mPoints;
};

#endif /* Shape_h */
