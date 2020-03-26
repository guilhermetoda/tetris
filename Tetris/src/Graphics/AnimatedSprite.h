//
//  AnimatedSprite.h
//  Tetris
//
//  Created by Guilherme Toda on 26/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef AnimatedSprite_h
#define AnimatedSprite_h

#include "AnimationPlayer.h"
#include "Vec2D.h"
#include "color.h"
#include <stdint.h>
#include <string>

class AARectangle;
class Screen;
class SpriteSheet;

class AnimatedSprite
{
public:
    AnimatedSprite();
    void Init(const std::string& animationPath, const SpriteSheet& spriteSheet, const Color& color = Color::White());
    void Update(uint32_t dt);
    void Draw(Screen& screen);
    void SetAnimation(const std::string& animationName, bool looped);
    Vec2D Size() const;
    void Stop();
    const AARectangle GetBoundingBox() const;
    
    inline Vec2D Position() const { return mPosition; }
    inline void SetPosition(const Vec2D& newPosition) { mPosition = newPosition; }
    inline void MoveBy(const Vec2D& delta) { mPosition += delta; }
    inline bool IsFinishedPlayingAnimation() const  { return mAnimationPlayer.IsFinishedPlaying(); }
    inline const Color& GetColor() const { return mColor; }
    const SpriteSheet* GetSpriteSheet() const { return mnoptrSpriteSheet; }
     
private:
    const SpriteSheet * mnoptrSpriteSheet;
    AnimationPlayer mAnimationPlayer;
    Vec2D mPosition;
    Color mColor;
};


#endif /* AnimatedSprite_h */
