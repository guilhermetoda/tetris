//
//  Animation.h
//  Tetris
//
//  Created by Guilherme Toda on 26/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef Animation_h
#define Animation_h

#include <string>
#include <vector>
#include "Vec2D.h"
#include "color.h"

struct AnimationFrame
{
    std::string frame = "";
    std::string overlay = "";
    Color frameColor = Color::White();
    Color overlayColor = Color::White();
    Vec2D size;
    Vec2D offset = Vec2D::Zero;
    bool frameColorSet = false;
};


class Animation
{
public:
    Animation();
    AnimationFrame GetAnimationFrame(uint32_t frameNum) const;
    
    void AddFrame(const std::string& frame) { mFrames.push_back(frame); }
    void AddFrameColor(const Color& color) { mFrameColors.push_back(color); }
    void AddOverlayFrameColor(const Color& color) { mOverlayColors.push_back(color); }
    void AddFrameOffset(const Vec2D& offset) { mFrameOffsets.push_back(offset); }
    
    void SetSpriteSheetName(const std::string& spriteSheetName) { mSpriteSheetName = spriteSheetName; }
    const std::string& GetSpriteSheetName() const { return mSpriteSheetName; }
    
    void SetName(const std::string& name) { mAnimationName = name; }
    const std::string& GetName() const { return mAnimationName; }
    
    Vec2D Size() const { return mSize; }
    void SetSize(const Vec2D& size) { mSize = size; }
    
    void SetFPS(int fps) { mFPS = fps; }
    int FPS() const { return mFPS; }
    
    void SetOverlay(const std::string& overlayName) { mOverlay = overlayName; }
    const std::string& overlayName() const { return mOverlay; }
    
    inline size_t NumFrames() const { return mFrames.size(); }
    inline size_t NumFrameColors() const { return mFrameColors.size(); }
    inline size_t NumOverlayColors() const { return mOverlayColors.size(); }
    inline size_t NumFrameOffset() const { return mFrameOffsets.size(); }
    
    static std::vector<Animation> LoadAnimations(const std::string& animationFilePath);
    
private:
    std::string mAnimationName;
    std::string mSpriteSheetName;
    std::string mOverlay;
    std::vector<std::string> mFrames;
    std::vector<Color> mFrameColors;
    std::vector<Color> mOverlayColors;
    std::vector<Vec2D> mFrameOffsets;
    Vec2D mSize;
    int mFPS;
};
#endif /* Animation_h */
