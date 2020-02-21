//
//  Circle.h
//  SDLTest
//
//  Created by Guilherme Toda on 12/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef Circle_h
#define Circle_h

#include "Shape.h"

class Circle : public Shape
{
public:
    Circle();
    Circle(const Vec2D& center, float radius);
    
    virtual Vec2D GetCenterPoint() const override { return mPoints[0]; };
    inline float GetRadius() const { return mRadius; }
    inline void SetRadius(float radius) { mRadius = radius; }
    virtual void MoveTo(const Vec2D& position) override { mPoints[0] = position; }
    
    bool Intersects(const Circle& otherCircle) const;
    bool ContainsPoint(const Vec2D& point) const;

private:
    float mRadius;
};

#endif /* Circle_h */
