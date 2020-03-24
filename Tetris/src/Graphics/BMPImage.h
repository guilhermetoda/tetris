//
//  BMPImage.h
//  Tetris
//
//  Created by Guilherme Toda on 24/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef BMPImage_h
#define BMPImage_h

#include "color.h"
#include <vector>
#include <string>
#include <stdint.h>

class BMPImage
{
public:
    BMPImage();
    bool LoadImageFromFile(const std::string& path);
    
    inline const std::vector<Color>& GetPixels() const { return mPixels; }
    
    inline uint32_t GetWidth() const { return mWidth; }
    inline uint32_t GetHeight() const { return mHeight; }
private:
    std::vector<Color> mPixels;
    uint32_t mWidth;
    uint32_t mHeight;
};

#endif /* BMPImage_h */
