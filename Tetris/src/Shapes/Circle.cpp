//
//  Circle.cpp
//  SDLTest
//
//  Created by Guilherme Toda on 12/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include <stdio.h>
#include "Circle.h"

Circle::Circle(): Circle(Vec2D::Zero, 0)
{
    
}
Circle::Circle(const Vec2D& center, float radius):mRadius(radius)
{
    mPoints.push_back(center);
}
 
bool Circle::Intersects(const Circle& otherCircle) const
{
    return GetCenterPoint().Distance(otherCircle.GetCenterPoint()) < (mRadius + otherCircle.mRadius);
}
bool Circle::ContainsPoint(const Vec2D& point) const
{
    return IsLessThanOrEqual(GetCenterPoint().Distance(point), mRadius);
}
