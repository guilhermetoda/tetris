//
//  Score.h
//  Tetris
//
//  Created by Guilherme Toda on 24/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef Score_h
#define Score_h

class Score
{
public:
    static int points;
    static int lines;
    
    static void CheckAndIncreaseScore(int rowsCompleted);
    static void ResetScore();
};



#endif /* Score_h */
