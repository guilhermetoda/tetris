//
//  HighScores.cpp
//  Tetris
//
//  Created by Guilherme Toda on 25/03/20.
//  Copyright © 2020 Guilherme Toda. All rights reserved.
//

#include "HighScores.h"
#include <algorithm>
#include <iostream>

HighScores::~HighScores()
{
    WriteFile();
}

void HighScores::Init(const std::string& filename)
{
    mFileName = filename;
    mScores.clear();
    if (IsFileExist())
    {
        LoadFile();
    }
    PrintScores();
}

bool HighScores::AddPlayerScore(const PlayerScore& newPlayerScore)
{
    if (mScores.size() < HighScores::mTopRankingSize)
    {
        mScores.push_back(newPlayerScore);
        const PlayerScore last = GetLastScore();
        if (last.score < newPlayerScore.score) {
            ReOrderRanking();
        }
        return true;
    }
    else
    {
        const PlayerScore last = GetLastScore();
        if (last.score < newPlayerScore.score)
        {
            mScores.at(mTopRankingSize - 1) = newPlayerScore;
            return true;
        }
    }
    return false;
}
const PlayerScore HighScores::GetLastScore() const
{
    return mScores.back();
}

const PlayerScore HighScores::GetTopScore() const
{
    return mScores.front();
}

void HighScores::PrintScores() const
{
    for (auto& score : mScores) {
        std::cout << "Name: " << score.playerName << " | " << score.score << std::endl;
    }
}

bool compareByScore(const PlayerScore& a, const PlayerScore& b)
{
    return a.score > b.score;
}

bool HighScores::IsFileExist()
{
    std::ifstream file(mFileName);
    return file.good();
}

void HighScores::ReOrderRanking()
{
    std::sort(mScores.begin(), mScores.end(), compareByScore);
}

bool HighScores::LoadFile()
{
    int count = 0;
    std::fstream mFile(mFileName, std::fstream::in | std::fstream::binary);
    size_t vectorSize = 0;
    mFile.read((char*)&vectorSize, sizeof(size_t));
    while (!mFile.eof() && count < vectorSize)
    {
        PlayerScore rankedPlayer;
        try {
            mFile.read((char *) &rankedPlayer, sizeof(PlayerScore));
            mScores.push_back(rankedPlayer);
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        count++;
    }
    //std::cout << vectorSize << std::endl;
    mFile.close();
    if(!mFile.good()) {
        return false;
    }
    return true;
}

bool HighScores::WriteFile()
{
    std::fstream mFile(mFileName, std::fstream::out | std::fstream::binary);
    size_t vectorSize = mScores.size();
    mFile.write((char*)&vectorSize, sizeof(vectorSize));
    for(size_t i = 0; i < mScores.size(); ++i)
    {
        mFile.write((char *)&mScores[i], sizeof(PlayerScore));
    }
    mFile.close();
    if(!mFile.good()) {
        return false;
    }
    return true;
}
