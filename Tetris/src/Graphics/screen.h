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
#include <functional>
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
class BMPImage;
class SpriteSheet;
class BitmapFont;
struct Sprite;

struct SDL_Window;
struct SDL_Surface;

//Hardware Acceleration
struct SDL_Renderer;
struct SDL_PixelFormat;
struct SDL_Texture;



class Screen
{
public:
    Screen();
    ~Screen();
    SDL_Window* Init(uint32_t width, uint32_t height, uint32_t mag, bool fast = true);
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
    void Draw(const BMPImage& image, const Sprite& sprite, const Vec2D& position, const Color& overlayColor = Color::White());
    void Draw(const SpriteSheet& spriteSheet, const std::string& spriteName, const Vec2D& position, const Color& overlayColor = Color::White());
    void Draw(const BitmapFont& font, const std::string& text, const Vec2D& position, const Color& overlayColor = Color::White());
private:
    
    // This will not allow to copy
    Screen(const Screen& screen);
    Screen& operator=(const Screen& screen);
    
    
    void ClearScreen();
    
    using FillPollyFunc = std::function<Color (uint32_t x, uint32_t y)>;
    void FillPolly(const std::vector<Vec2D>& points, FillPollyFunc func);
    
    uint32_t mWidth;
    uint32_t mHeight;
    
    ScreenBuffer mBackBuffer;
    Color mClearColor;
    
    SDL_Window* mptrWindow;
    SDL_Surface* noptrWindowSurface;
    
    SDL_Renderer* mRenderer;
    SDL_PixelFormat* mPixelFormat;
    SDL_Texture* mTexture;
    
    bool mFast;
    
};

#endif /* Screen_hpp */
