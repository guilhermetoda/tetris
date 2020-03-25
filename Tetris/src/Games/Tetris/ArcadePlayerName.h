//
//  ArcadePlayerName.h
//  Tetris
//
//  Created by Guilherme Toda on 25/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef ArcadePlayerName_h
#define ArcadePlayerName_h

#include <stdint.h>
#include <string>

class ArcadePlayerName
{
public:
    void Init(const std::string& initialName);
    void ChangeLetter(int index, int next = 1);
    inline const std::string& GetPlayerName() const { return mPlayerName; }
    inline const char GetLetterAtIndex(int index) const { return mPlayerName[index]; }
private:
    const size_t mNameSize = 3;
    std::string mPlayerName;
    char ClampLetters(char letter);
};

#endif /* ArcadePlayerName_h */
