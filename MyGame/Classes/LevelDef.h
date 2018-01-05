#ifndef __Match3_LevelDef_LAYER_H__
#define __Match3_LevelDef_LAYER_H__

#include "cocos2d.h"
#define ROW 8
#define COLUMN 8

class LevelDef
{

// function
public:
    LevelDef();
    virtual ~LevelDef();
    
//public 变量 
public:
    int form[ROW][COLUMN];//
    int dirt[ROW][COLUMN];//: null,
    int chips[ROW][COLUMN];//
    int chip_types;//: 5,
    int moves;//: 25,
    int chip_goal;//: 4,
    int chip_goal_count;//: 13

};

#endif // __Match3_LevelDef_LAYER_H__
//////
