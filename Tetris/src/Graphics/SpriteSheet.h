//
//  SpriteSheet.h
//  Tetris
//
//  Created by Guilherme Toda on 24/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef SpriteSheet_h
#define SpriteSheet_h

#include "BMPImage.h"
#include <string>
#include <vector>
#include <stdint.h>

struct Sprite
{
    uint32_t xPos = 0;
    uint32_t yPos = 0;
    uint32_t width;
    uint32_t height;
};

class SpriteSheet
{
public:
    SpriteSheet();
    bool Load(const std::string& name);
    
    Sprite GetSprite(const std::string& spriteName) const;
    std::vector<std::string> SpriteNames() const;
    inline const BMPImage& GetImage() const { return mImage; }
    
    uint32_t GetWidth() const { return mImage.GetWidth(); }
    uint32_t GetHeight() const { return mImage.GetHeight(); }
private:
    
    bool LoadSpriteSections(const std::string& path);
    
    struct BMPImageSection {
        std::string key = "";
        Sprite sprite;
    };
    
    BMPImage mImage;
    std::vector<BMPImageSection> mSections;
};

#endif /* SpriteSheet_h */
