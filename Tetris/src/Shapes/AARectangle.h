//
//  AARectangle.h
//  SDLTest
//
//  Created by Guilherme Toda on 12/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef AARectangle_h
#define AARectangle_h

#include "Shape.h"
#include "Utils.h"
#include <cmath>

class AARectangle : public Shape
{
public:
    AARectangle();
    AARectangle(const Vec2D& topLeft, unsigned int width, unsigned int height);
    AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight);
    
    inline void SetTopLeftPoint(const Vec2D& topLeft) { mPoints[0] = topLeft; }
    inline void SetBottomRightPont(const Vec2D& bottomRight) { mPoints[1] = bottomRight; }
    
    Vec2D GetTopLeftPoint() const { return mPoints[0]; }
    Vec2D GetBottomRightPoint() const { return mPoints[1]; }
    
    float GetWidth() const;
    float GetHeight() const;
    
    virtual void MoveTo(const Vec2D& position) override;
    
    virtual Vec2D GetCenterPoint() const override;
    
    bool Intersects(const AARectangle& otherRect) const;
    bool ContainsPoint(const Vec2D& point) const;
    
    static AARectangle Inset(const AARectangle& rect, Vec2D& insets);
    
    virtual std::vector<Vec2D> GetPoints() const override;
    
};


#endif /* AARectangle_h */
