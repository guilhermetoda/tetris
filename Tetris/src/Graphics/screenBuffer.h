//
//  screenBuffer.hpp
//  SDLTest
//
//  Created by Guilherme Toda on 06/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef screenBuffer_h
#define screenBuffer_h

#include "color.h"
#include <SDL.h>
#include <cassert>

struct SDL_Surface;

class ScreenBuffer
{
public:
    ScreenBuffer();
    ScreenBuffer(const ScreenBuffer& screenBuffer);
    ~ScreenBuffer();
    
    ScreenBuffer& operator=(const ScreenBuffer& screenBuffer);
    
    //Move Semantics
    ScreenBuffer(const ScreenBuffer && screenBuffer);
    ScreenBuffer& operator=(const ScreenBuffer && screenBuffer);
    void Init(uint32_t format, uint32_t width, uint32_t height);
    inline SDL_Surface * GetSurface() { return mSurface; }
    void Clear(const Color& c = Color::Black());
    void SetPixel(const Color& c, int x, int y);
private:
    SDL_Surface* mSurface;
    size_t GetIndex(int r, int c);
};

#endif /* screenBuffer_hpp */
