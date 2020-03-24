//
//  App.cpp
//  SDLTest
//
//  Created by Guilherme Toda on 18/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include "App.h"
#include <SDL.h>
#include <iostream>
#include <memory>
#include <cassert>
#include "ArcadeScene.h"

#include "GameScene.h"
//#include "Breakout.h"
#include "TetrisGame.h"


App& App::Singleton()
{
    static App theApp;
    return theApp;
}
bool App::Init(uint32_t width, uint32_t height, uint32_t mag)
{
    
    if (!mFont.Load("ArcadeFont"))
    {
        std::cout << "Couldn't load the font" << std::endl;
        return false;
    }
    
    mnoptrWindow = mScreen.Init(width, height, mag);
    
    std::unique_ptr<ArcadeScene> arcadeScene = std::make_unique<ArcadeScene>();
    PushScene(std::move(arcadeScene));
    
    std::unique_ptr<TetrisGame> tetrisGame = std::make_unique<TetrisGame>();
    std::unique_ptr<GameScene> tetrisScene = std::make_unique<GameScene>(std::move(tetrisGame));
    PushScene(std::move(tetrisScene));
    
    return mnoptrWindow != nullptr;
}

void App::Run()
{
    if (mnoptrWindow)
    {
        
        bool running = true;
        
        uint32_t lastTick = SDL_GetTicks();
        uint32_t currentTick = lastTick;
        uint32_t dt = 10;
        uint32_t accumulator = 0;
        
        mInputController.Init([&running](uint32_t dt, InputState state) {
            running = false;
        });
        
        while (running)
        {
            currentTick = SDL_GetTicks();
            uint32_t frameTime = currentTick - lastTick;
            
            if (frameTime > 300)
            {
                frameTime = 300;
            }
            
            lastTick = currentTick;
            
            accumulator += frameTime;
            
            //Input
            mInputController.Update(dt);
            
            Scene* topScene = App::TopScene();
            assert(topScene && "Scene is required");
            if (topScene) {
                
                //Update
                while (accumulator >= dt)
                {
                    //Update current scene by dt
                    topScene->Update(dt);
                    accumulator -= dt;
                
                }
                
                //Render
                topScene->Draw(mScreen);
            }
            
            mScreen.SwapScreen();
        }
    }
}

void App::PushScene(std::unique_ptr<Scene> scene)
{
    assert(scene && "Don't Push nullptr");
    if (scene)
    {
        scene->Init();
        mInputController.SetGameController(scene->GetGameController());
        mSceneStack.emplace_back(std::move(scene));
        SDL_SetWindowTitle(mnoptrWindow, TopScene()->GetSceneName().c_str());
    }
}
void App::PopScene()
{
    if (mSceneStack.size() > 1)
    {
        mSceneStack.pop_back();
    }
    
    if (TopScene())
    {
        mInputController.SetGameController(TopScene()->GetGameController());
        SDL_SetWindowTitle(mnoptrWindow, TopScene()->GetSceneName().c_str());
    }
}
Scene* App::TopScene()
{
    if (mSceneStack.empty())
    {
        return nullptr;
    }
    //Gets the point from the unique pointer (.get())
    return mSceneStack.back().get();
}

const std::string& App::GetBasePath()
{
    static std::string basePath = SDL_GetBasePath();
    return basePath;
}
