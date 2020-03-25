//
//  Screen.cpp
//  SDLTest
//
//  Created by Guilherme Toda on 06/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include "screen.h"
#include "line2D.h"
#include "Triangle.h"
#include "AARectangle.h"
#include "Circle.h"
#include "BMPImage.h"
#include "BitmapFont.h"
#include "SpriteSheet.h"
#include "../Utils/Vec2D.h"
#include <cassert>
#include <cmath>
#include <SDL.h>
#include <algorithm>

Screen::Screen(): mWidth(0), mHeight(0), mptrWindow(nullptr), noptrWindowSurface(nullptr), mRenderer(nullptr), mPixelFormat(nullptr), mTexture(nullptr)
{
    
}
Screen::~Screen()
{
    if (mPixelFormat)
    {
        SDL_FreeFormat(mPixelFormat);
        mPixelFormat = nullptr;
    }
    if (mRenderer)
    {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }
    if (mTexture)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
    }
    
    
    if (mptrWindow) {
        SDL_DestroyWindow(mptrWindow);
        mptrWindow =nullptr;
    }
    SDL_Quit();
}
SDL_Window* Screen::Init(uint32_t width, uint32_t height, uint32_t mag, bool fast)
{
    mFast = fast;
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "Error SDL_INIT" << std::endl;
        return nullptr;
    }
    
    mWidth = width;
    mHeight = height;
    
    mptrWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth * mag, mHeight * mag, 0);

    if (mptrWindow)
    {
        uint8_t rClear = 0;
        uint8_t gClear = 0;
        uint8_t bClear = 0;
        uint8_t aClear = 255;
        
        if (mFast)
        {
            mRenderer = SDL_CreateRenderer(mptrWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (mRenderer == nullptr)
            {
                std::cout << "SDL Renderer failed" << std::endl;
                return nullptr;
            }
            SDL_SetRenderDrawColor(mRenderer, rClear, gClear, bClear, aClear);
        }
        else
        {
            noptrWindowSurface = SDL_GetWindowSurface(mptrWindow);
        }
        
        mPixelFormat = SDL_AllocFormat(SDL_GetWindowPixelFormat(mptrWindow));
        if (mFast)
        {
            mTexture = SDL_CreateTexture(mRenderer, mPixelFormat->format, SDL_TEXTUREACCESS_STREAMING, width, height);
        }
        Color::InitColorFormat(mPixelFormat);
        mClearColor = Color(rClear, gClear, bClear, aClear);
        mBackBuffer.Init(mPixelFormat->format, mWidth, mHeight);
        mBackBuffer.Clear(mClearColor);
    }
    return mptrWindow;
}

void Screen::SwapScreen() {
    assert(mptrWindow);
    if (mptrWindow)
    {
        ClearScreen();
        if (mFast)
        {
            uint8_t* textureData = nullptr;
            int texturePitch = 0;
            if (SDL_LockTexture(mTexture, nullptr, (void**)&textureData, &texturePitch) >= 0)
            {
                SDL_Surface* surface = mBackBuffer.GetSurface();
                memcpy(textureData, surface->pixels, surface->w * surface->h * mPixelFormat->BytesPerPixel);
                SDL_UnlockTexture(mTexture);
                SDL_RenderCopy(mRenderer, mTexture, nullptr, nullptr);
                SDL_RenderPresent(mRenderer);
            }
        }
        else
        {
            SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, noptrWindowSurface, nullptr);
            SDL_UpdateWindowSurface(mptrWindow);
        }
        
        mBackBuffer.Clear(mClearColor);
    }
}


void Screen::Draw(int x, int y, const Color& color)
{
    assert(mptrWindow);
    if (mptrWindow)
    {
        mBackBuffer.SetPixel(color, x, y);
    }
}
void Screen::Draw(const Vec2D& point, const Color& color) {
    assert(mptrWindow);
    if (mptrWindow)
    {
        mBackBuffer.SetPixel(color, point.GetX(), point.GetY());
    }
}

void Screen::Draw(const Line2D& line, const Color& color)
{
    assert(mptrWindow);
    if (mptrWindow)
    {
        int dx, dy;
        int x0 = roundf(line.GetP0().GetX());
        int y0 = roundf(line.GetP0().GetY());
        int x1 = roundf(line.GetP1().GetX());
        int y1 = roundf(line.GetP1().GetY());
        
        dx = x1 - x0;
        dy = y1 - y0;
        
        signed const char ix((dx > 0) - (dx < 0)); // evaluate to 1 or -1
        signed const char iy((dy > 0) - (dy < 0)); // evaluate to 1 or -1
        
        dx = abs(dx) * 2;
        dy = abs(dy) * 2;
        
        Draw(x0, y0, color);
        
        if (dx >= dy)
        {
            int d = dy - dx/2;
            while (x0 != x1)
            {
                if (d>=0)
                {
                    d-=dx;
                    y0 += iy;
                }
                d += dy;
                x0 += ix;
                Draw(x0, y0, color);
            }
        }
        else
        {
            int d = dx - dy/2;
            while (y0 != y1)
            {
                if (d>=0)
                {
                    d-=dy;
                    x0 += ix;
                }
                d += dx;
                y0 += iy;
                Draw(x0, y0, color);
            }
        }
        
    }
}

void Screen::Draw(const Triangle& triangle, const Color& color, bool fill, const Color& fillColor) {
    Line2D p0top1 = Line2D(triangle.GetP0(), triangle.GetP1());
    Line2D p1top2 = Line2D(triangle.GetP1(), triangle.GetP2());
    Line2D p2top0 = Line2D(triangle.GetP2(), triangle.GetP0());
    
    Draw(p0top1, color);
    Draw(p1top2, color);
    Draw(p2top0, color);
    
    if (fill)
    {
        FillPolly(triangle.GetPoints(), [fillColor](uint32_t x, uint32_t y){ return fillColor; });
    }
        
}

void Screen::Draw(const AARectangle& rect, const Color& color, bool fill, const Color& fillColor)
{
    std::vector<Vec2D> points = rect.GetPoints();
    Line2D p0p1 = Line2D(points[0], points[1]);
    Line2D p1p2 = Line2D(points[1], points[2]);
    Line2D p2p3 = Line2D(points[2], points[3]);
    Line2D p3p0 = Line2D(points[3], points[0]);
    
    Draw(p0p1, color);
    Draw(p1p2, color);
    Draw(p2p3, color);
    Draw(p3p0, color);
    
    if (fill)
    {
        FillPolly(rect.GetPoints(), [fillColor](uint32_t x, uint32_t y){ return fillColor; });
    }
}

void Screen::Draw(const Circle& circle, const Color& color, bool fill, const Color& fillColor)
{
    static unsigned int NUM_CIRCLE_SEGMENTS = 30;
    
    std::vector<Vec2D> circlePoints;
    std::vector<Line2D> lines;
    
    float angle = TWO_PI / float(NUM_CIRCLE_SEGMENTS);
    Vec2D p0 = Vec2D(circle.GetCenterPoint().GetX() + circle.GetRadius(), circle.GetCenterPoint().GetY());
    Vec2D p1 = p0;
    Line2D nextLineToDraw;
    
    for (unsigned int i = 0; i < NUM_CIRCLE_SEGMENTS; ++i)
    {
        p1.Rotate(angle, circle.GetCenterPoint());
        nextLineToDraw.SetP1(p1);
        nextLineToDraw.SetP0(p0);
        lines.push_back(nextLineToDraw);
        //Draw(nextLineToDraw, color);
        p0 = p1;
        circlePoints.push_back(p0);
    }
    
    if (fill)
    {
        FillPolly(circlePoints, [fillColor](uint32_t x, uint32_t y){ return fillColor; });
    }
    
    for (const Line2D& line: lines)
    {
        Draw(line, color);
    }
    
}

void Screen::Draw(const BMPImage& image, const Sprite& sprite, const Vec2D& position, const Color& overlayColor)
{
    float rVal = static_cast<float>(overlayColor.GetRed()) / 255.0f;
    float gVal = static_cast<float>(overlayColor.GetGreen()) / 255.0f;
    float bVal = static_cast<float>(overlayColor.GetBlue()) / 255.0f;
    float aVal = static_cast<float>(overlayColor.GetAlpha()) / 255.0f;
    
    uint32_t width = sprite.width;
    uint32_t height = sprite.height;
    
    const std::vector<Color>& pixels = image.GetPixels();
    auto topLeft = position;
    auto topRight = position + Vec2D(width, 0);
    auto bottomLeft = position + Vec2D(0,height);
    auto bottomRight = position + Vec2D(width, height);
    
    std::vector<Vec2D> points = { topLeft, bottomLeft , bottomRight, topRight};
    Vec2D xAxis = topRight - topLeft;
    Vec2D yAxis = bottomLeft - topLeft;
    
    const float invXAxisLengthSq = 1.0f / xAxis.Mag2();
    const float invYAxisLengthSq = 1.0f / yAxis.Mag2();
    
    FillPolly(points, [&](uint32_t px, uint32_t py){
        Vec2D p = {static_cast<float>(px), static_cast<float>(py)};
        Vec2D d = p - topLeft;
        float u = invXAxisLengthSq * d.Dot(xAxis);
        float v = invYAxisLengthSq * d.Dot(yAxis);
        u = Clamp(u, 0.0f, 1.0f);
        v = Clamp(v, 0.0f, 1.0f);
        
        float tx = roundf(u * static_cast<float>(sprite.width));
        float ty = roundf(v * static_cast<float>(sprite.height));
        
        Color imageColor = pixels[GetIndex(image.GetWidth(), ty + sprite.yPos, tx + sprite.xPos)];
        Color newColor = { static_cast<uint8_t>(imageColor.GetRed() * rVal), static_cast<uint8_t>(imageColor.GetGreen() * gVal), static_cast<uint8_t>(imageColor.GetBlue() * bVal), static_cast<uint8_t>(imageColor.GetAlpha() * aVal) };
        
        return newColor;
        
    });
}

void Screen::Draw(const SpriteSheet& spriteSheet, const std::string& spriteName, const Vec2D& position, const Color& overlayColor)
{
    Draw(spriteSheet.GetImage(), spriteSheet.GetSprite(spriteName), position, overlayColor);
}

void Screen::Draw(const BitmapFont& font, const std::string& text, const Vec2D& position, const Color& overlayColor)
{
    uint32_t xPosition = position.GetX();
    
    const SpriteSheet& spriteSheet = font.GetSpriteSheet();
    for (char c : text)
    {
        if (c == ' ')
        {
            xPosition += font.GetFontSpacingBetweenWords();
            continue;
        }
        Sprite sprite =  spriteSheet.GetSprite(std::string("") + c);
        Draw(spriteSheet.GetImage(), sprite, Vec2D(xPosition, position.GetY()), overlayColor);
        xPosition += sprite.width;
        xPosition += font.GetFontSpacingBetweenLetters();
    }
}

void Screen::ClearScreen()
{
    assert(mptrWindow);
    if (mptrWindow)
    {
        if (mFast)
        {
            SDL_RenderClear(mRenderer);
        }
        else
        {
            SDL_FillRect(noptrWindowSurface, nullptr, mClearColor.GetPixelColor());
        }
    }
}

void Screen::FillPolly(const std::vector<Vec2D>& points, FillPollyFunc func)
{
    if (points.size() > 0)
    {
        float top = points[0].GetY();
        float bottom = points[0].GetY();
        float right = points[0].GetX();
        float left = points[0].GetX();
        
        for (size_t i = 1; i < points.size(); ++i)
        {
            if (points[i].GetY() < top)
            {
                top = points[i].GetY();
            }
            if (points[i].GetY() > bottom)
            {
                bottom = points[i].GetY();
            }
            if (points[i].GetX() < left)
            {
                left = points[i].GetX();
            }
            if (points[i].GetX() > right)
            {
                right = points[i].GetX();
            }
        }
        
        for (int pixelY = top; pixelY < bottom; ++pixelY)
        {
            std::vector<float> nodeXVec;
            
            size_t j = points.size() - 1;
            for (size_t i = 0; i < points.size(); ++i)
            {
                float pointiY = points[i].GetY();
                float pointjY = points[j].GetY();
                
                if ((pointiY <= (float)pixelY && pointjY > (float)pixelY) || (pointjY <= (float)pixelY && pointiY > (float)pixelY))
                {
                    float denom = pointjY - pointiY;
                    if (IsEqual(denom, 0))
                    {
                        continue;
                    }
                    float x = points[i].GetX() + (pixelY - pointiY)/(denom) * (points[j].GetX() - points[i].GetX());
                    nodeXVec.push_back(x);
                }
                j = i;
            }
            std::sort(nodeXVec.begin(), nodeXVec.end(), std::less<>());
            for (size_t k = 0; k < nodeXVec.size(); ++k)
            {
                if (nodeXVec[k] > right)
                {
                    break;
                }
                if (nodeXVec[k+1] > left )
                {
                    if (nodeXVec[k] < left)
                    {
                        nodeXVec[k] = left;
                    }
                    if (nodeXVec[k+1] > right)
                    {
                        nodeXVec[k+1] = right;
                    }
                    //Line2D line = { Vec2D(nodeXVec[k], pixelY), Vec2D(nodeXVec[k+1], pixelY)};
                    //Draw(line, color);
                    for (int pixelX = nodeXVec[k]; pixelX < nodeXVec[k+1]; ++pixelX)
                    {
                        Draw(pixelX, pixelY, func(pixelX, pixelY));
                    }
                }
            }
        }
    }
}
