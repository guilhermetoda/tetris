//
//  BMPImage.cpp
//  Tetris
//
//  Created by Guilherme Toda on 24/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include "BMPImage.h"
#include <SDL.h>

BMPImage::BMPImage():mWidth(0), mHeight(0)
{
    
}

bool BMPImage::LoadImageFromFile(const std::string& path)
{
    SDL_Surface * bmpSurface = SDL_LoadBMP(path.c_str());
    
    if (bmpSurface == nullptr)
    {
        return false;
    }
    
    mWidth = bmpSurface->w;
    mHeight = bmpSurface->h;
    
    size_t length = mWidth * mHeight;
    mPixels.reserve(length);
    SDL_LockSurface(bmpSurface);
    
    uint32_t * pixels = static_cast<uint32_t*>(bmpSurface->pixels);
    for (uint32_t i = 0; i < length; ++i)
    {
        mPixels.push_back(Color(pixels[i]));
    }
    
    SDL_UnlockSurface(bmpSurface);
    SDL_FreeSurface(bmpSurface);
    
    return true;
    
}
