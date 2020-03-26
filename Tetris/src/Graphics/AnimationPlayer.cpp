//
//  AnimationPlayer.cpp
//  Tetris
//
//  Created by Guilherme Toda on 26/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include "AnimationPlayer.h"

AnimationPlayer::AnimationPlayer(): mTime(0), mCurrentAnimation(0), mFrame(0), mLooped(false), mIsFinishedPlaying(false), mIsPlaying(false)
{
    
}
bool AnimationPlayer::Init(const std::string& animationsPath) {
    mAnimations = Animation::LoadAnimations(animationsPath);
    return mAnimations.size() > 0;
}

bool AnimationPlayer::Play(const std::string& animationName, bool looped)
{
    bool found = false;
    
    for (size_t i = 0; i < mAnimations.size(); ++i)
    {
        if (mAnimations[i].GetName() == animationName)
        {
            found = true;
            mCurrentAnimation = i;
            break;
        }
    }
    if (found)
    {
        mIsPlaying =true;
        mTime = 0;
        mFrame = 0;
        mLooped = looped;
        mIsFinishedPlaying = false;
    }
    return found;
}

void AnimationPlayer::Pause()
{
    if (mIsFinishedPlaying) {
        mIsPlaying = !mIsPlaying;
    }
}
void AnimationPlayer::Stop()
{
    mIsPlaying = false;
    mTime = 0;
    mFrame = 0;
    mIsFinishedPlaying = true;
}

void AnimationPlayer::Update(uint32_t dt)
{
    if (mIsPlaying)
    {
        mTime += dt;
        int fps = mAnimations[mCurrentAnimation].FPS();
        float millisecondsPerFrame = static_cast<float>(1000) / static_cast<float>(fps);
        if (static_cast<float>(mTime) > millisecondsPerFrame)
        {
            mTime -= static_cast<uint32_t>(millisecondsPerFrame);
            if (mFrame + 1 < mAnimations[mCurrentAnimation].NumFrames())
            {
                ++mFrame;
            }
            else if ((mFrame + 1 > mAnimations[mCurrentAnimation].NumFrames()) && mLooped)
            {
                mFrame = 0;
            }
            else
            {
                mIsFinishedPlaying = true;
            }
        }
    }
}

AnimationFrame AnimationPlayer::GetCurrentAnimationFrame() const
{
    if (mAnimations.empty())
    {
        return AnimationFrame();
    }
    return mAnimations[mCurrentAnimation].GetAnimationFrame(GetCurrentFrameNumber());
}
