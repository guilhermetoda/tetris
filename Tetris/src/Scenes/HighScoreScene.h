//
//  HighScoreScene.h
//  Tetris
//
//  Created by Guilherme Toda on 25/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef HighScoreScene_h
#define HighScoreScene_h

#include "Scene.h"
#include "HighScores.h"

class Screen;

class HighScoreScene: public Scene
{
public:
    HighScoreScene();
    virtual void Init() override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen& screen) override;
    virtual const std::string& GetSceneName() const override;
private:
    HighScores mHighScores;
};


#endif /* HighScoreScene_h */
