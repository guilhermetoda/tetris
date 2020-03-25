//
//  ArcadePlayerName.cpp
//  Tetris
//
//  Created by Guilherme Toda on 25/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include "ArcadePlayerName.h"
#include <cassert>

void ArcadePlayerName::Init(const std::string& initialName)
{
    mPlayerName = initialName;
}

void ArcadePlayerName::ChangeLetter(int index, int next)
{
    assert(index >= 0 && index < mPlayerName.size());
    mPlayerName[index] = ClampLetters(char(mPlayerName[index] + next));
}

char ArcadePlayerName::ClampLetters(char letter)
{
    if (letter < char(65)) {
        return char(65);
    }
    else if (letter > char(90)) {
        return char(90);
    }
    return letter;
}
