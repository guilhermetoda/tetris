//
//  App.h
//  SDLTest
//
//  Created by Guilherme Toda on 18/02/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef App_h
#define App_h

#include "screen.h"
#include <stdint.h>
#include <vector>
#include <memory>
#include "InputController.h"
#include "BitmapFont.h"


struct SDL_Window;
class Scene;

class App
{
public:
    static App& Singleton();
    bool Init(uint32_t width, uint32_t height, uint32_t mag);
    void Run();
    
    inline uint32_t Width() const { return mScreen.GetWidth(); }
    inline uint32_t Height() const { return mScreen.GetHeight(); }
    
    void PushScene(std::unique_ptr<Scene> scene);
    void PopScene();
    Scene* TopScene(); // returns current scene
    
    static const std::string& GetBasePath();
    
    inline const BitmapFont& GetFont() const { return mFont; }
    
private:
    Screen mScreen;
    SDL_Window *mnoptrWindow;
    
    std::vector<std::unique_ptr<Scene>> mSceneStack;
    InputController mInputController;
    BitmapFont mFont;
};

#endif /* App_h */
