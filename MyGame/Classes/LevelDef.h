#ifndef __LevelDef_LAYER_H__
#define __LevelDef_LAYER_H__

#include "cocos2d.h"

class LevelDef
{

// function
public:
    LevelDef();
    virtual ~LevelDef();
    
//public 变量    
public:
    int[8][8] form;//
    int[8][8] dirt;//: null,
    int[8][8] chips;//
    int chip_types;//: 5,
    int moves;//: 25,
    int chip_goal;//: 4,
    int chip_goal_count;//: 13

};

#endif // __LevelDef_LAYER_H__
//////
