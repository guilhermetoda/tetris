//
//  HighScores.h
//  Tetris
//
//  Created by Guilherme Toda on 25/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#ifndef HighScores_h
#define HighScores_h

#include <string>
#include <stdint.h>
#include <vector>
#include <fstream>

struct PlayerScore {
    int score = 0;
    std::string playerName = "ABC";
};

class HighScores {
public:
    ~HighScores();
    void Init(const std::string& filename);
    bool AddPlayerScore(const PlayerScore& newPlayerScore);
    const PlayerScore GetTopScore() const;
    const PlayerScore GetLastScore() const;
    inline const std::vector<PlayerScore>& GetHighScores() const { return mScores; }
    inline const size_t GetHighScoreSize() const { return mScores.size(); }
    //Temp
    void PrintScores() const;
private:
    void ReOrderRanking();
    bool IsFileExist();
    bool WriteFile();
    bool LoadFile();
    
    
    static const size_t mTopRankingSize = 2;
    std::vector<PlayerScore> mScores;
    std::string mFileName;
    
};



#endif /* HighScores_h */
