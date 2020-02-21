//
//  line2D.h
//  SDLTest
//
//  Created by Guilherme Toda on 06/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef line2D_h
#define line2D_h
#include "../Utils/Vec2D.h"
#include "../Utils/Utils.h"
#include <cmath>

class Line2D
{
public:
    //Constructors
    Line2D();
    Line2D(float x0, float y0, float x1, float y1);
    Line2D(const Vec2D& vec1, const Vec2D& vec2);
    
    // "Getters and Setters"
    inline const Vec2D& GetP0() const { return mP0; }
    inline const Vec2D& GetP1() const { return mP1; }
    inline void SetP0(const Vec2D& p0) { mP0 = p0; }
    inline void SetP1(const Vec2D& p1) { mP1 = p1; }
    
    bool operator==(const Line2D& line) const;
    float MinDistanceFrom(const Vec2D& p, bool limitToSegment = false) const;
    Vec2D ClosestPoint(const Vec2D& p, bool limitToSegment = false) const;
    Vec2D Midpoint() const;
    float Slope() const;
    float Length() const;
    
private:
    Vec2D mP0;
    Vec2D mP1;
};

#endif /* line2D_h */
