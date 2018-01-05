#ifndef __Match3_GameData_LAYER_H__
#define __Match3_GameData_LAYER_H__

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
    LevelDef* getLevelDef(int e);
    int getTotalLevels();

//public 变量    
public:
    int levelsCompleted = 0;
    int totalScore;// = 0;
    Vector<LevelDef*> levels;// = [];

//static var
private:
    static GameData* instance;
};

GameData::instance = nullptr;//"BONUS_4";
#endif // __Match3_GameData_LAYER_H__
//////