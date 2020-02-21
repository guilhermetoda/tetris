//
//  Screen.hpp
//  SDLTest
//
//  Created by Guilherme Toda on 06/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef Screen_h
#define Screen_h

#include <stdint.h>
#include <vector>
#include "screenBuffer.h"
#include "color.h"

//foward declare
class Color;
class ScreenBuffer;
class Vec2D;
class Line2D;
class Triangle;
class AARectangle;
class Circle;
struct SDL_Window;
struct SDL_Surface;


class Screen
{
public:
    Screen();
    ~Screen();
    SDL_Window* Init(uint32_t width, uint32_t height, uint32_t mag);
    void SwapScreen();
    
    inline void SetClearColor(const Color& clearColor) { mClearColor = clearColor;}
    inline uint32_t GetWidth() const { return mWidth; }
    inline uint32_t GetHeight() const { return mHeight; }
    
    //DrawMethods go here
    void Draw(int x, int y, const Color& color);
    void Draw(const Vec2D& point, const Color& color);
    void Draw(const Line2D& line, const Color& color);
    void Draw(const Triangle& triangle, const Color& color, bool fill = false, const Color& fillColor = Color::White());
    void Draw(const AARectangle& rect, const Color& color, bool fill = false, const Color& fillColor = Color::White());
    void Draw(const Circle& circle, const Color& color, bool fill = false, const Color& fillColor = Color::White());
private:
    
    // This will not allow to copy
    Screen(const Screen& screen);
    Screen& operator=(const Screen& screen);
    
    
    void ClearScreen();
    void FillPolly(const std::vector<Vec2D>& points, const Color& color);
    
    uint32_t mWidth;
    uint32_t mHeight;
    
    ScreenBuffer mBackBuffer;
    Color mClearColor;
    
    SDL_Window* mptrWindow;
    SDL_Surface* noptrWindowSurface;
    
    
};

#endif /* Screen_hpp */
