#ifndef __GameData_LAYER_H__
#define __GameData_LAYER_H__

#include "cocos2d.h"

class GameData
{

// static function
public:
    static GameData* getInstance();

// public 方法
public:
    GameData();
    virtual ~GameData();
    void save();
    void load();
    void onWinLevel(int lvl, int score);
    int getTotalScore();
    int levelsAvailable();
    LevelDef getLevelDef(int e);
    int getTotalLevels();

//public 变量    
public:
    int levelsCompleted = 0;
    int totalScore;// = 0;
    Vector<LevelDef*> levels;// = [];

//static var
private:
    static instance;
};

int GameData::instance = null;//"BONUS_4";
#endif // __GameData_LAYER_H__
//////