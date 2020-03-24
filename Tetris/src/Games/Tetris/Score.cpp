//
//  Score.cpp
//  Tetris
//
//  Created by Guilherme Toda on 24/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include "Score.h"
int Score::points = 0;
int Score::lines = 0;

void Score::CheckAndIncreaseScore(int rowsCompleted)
{
    if (rowsCompleted > 0)
    {
        lines += rowsCompleted;
        points += rowsCompleted * 100;
    }
    if (rowsCompleted >= 4)
    {
        // extra points
        points += 1000;
    }
}

void Score::ResetScore()
{
    points = 0;
    lines = 0;
}
