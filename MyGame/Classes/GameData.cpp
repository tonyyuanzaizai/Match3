#include "GameData.h"
#include "LevelDef.h"
#include "Constants.h"

USING_NS_CC;


GameData::GameData() {
    this->levelsCompleted = 0;
    this->totalScore = 0;

    // level 1
    LevelDef* levelDef1 = new LevelDef();
    int form1[8][8] = {
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    memcpy(&levelDef1->form[0][0],&form1[0][0],sizeof(form1));
    levelDef1->dirt[0][0] = -1;
    int chips1[8][8] = {
        {0, 5, 3, 2, 1, 2, 5, 0},
        {0, 1, 2, 1, 2, 1, 4, 0},
        {0, 3, 1, 5, 1, 5, 1, 0},
        {0, 1, 2, 3, 3, 2, 4, 0},
        {0, 2, 3, 5, 1, 4, 1, 0},
        {0, 2, 5, 3, 5, 1, 4, 0},
        {0, 1, 2, 3, 1, 4, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    memcpy(&levelDef1->chips[0][0],&chips1[0][0],sizeof(chips1));
    levelDef1->chip_types = 5;
    levelDef1->moves = 25;
    levelDef1->chip_goal = 4;
    levelDef1->chip_goal_count = 13;

    // level 2
    LevelDef* levelDef2 = new LevelDef();
    int form2[8][8] = {
        {0, 0, 1, 0, 0, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 0, 0, 1, 0, 0}
    };
    memcpy(&levelDef2->form[0][0],&form2[0][0],sizeof(form2));
    levelDef2->dirt[0][0] = -1;
    int chips2[8][8] = {
        {0, 0, 4, 0, 0, 1, 0, 0},
        {0, 1, 2, 2, 3, 4, 5, 0},
        {2, 1, 3, 3, 4, 1, 2, 3},
        {0, 4, 1, 5, 4, 4, 2, 0},
        {0, 3, 4, 1, 2, 3, 1, 0},
        {1, 2, 3, 5, 5, 3, 5, 2},
        {0, 5, 1, 5, 4, 2, 2, 0},
        {0, 0, 5, 0, 0, 1, 0, 0}
    };
    memcpy(&levelDef2->chips[0][0],&chips2[0][0],sizeof(chips2));
    levelDef2->chip_types = 5;
    levelDef2->moves = 30;
    levelDef2->chip_goal = 1;
    levelDef2->chip_goal_count = 20;

    // level 3
    LevelDef* levelDef3 = new LevelDef();
    int form3[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    memcpy(&levelDef3->form[0][0],&form3[0][0],sizeof(form3));
    int dirt3[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    memcpy(&levelDef3->dirt[0][0],&dirt3[0][0],sizeof(dirt3));
    int chips3[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 2, 4, 3, 4, 5, 0},
        {0, 3, 3, 5, 2, 1, 5, 0},
        {0, 2, 4, 1, 2, 6, 6, 0},
        {0, 2, 4, 2, 3, 3, 4, 0},
        {0, 1, 2, 3, 4, 6, 6, 0},
        {0, 2, 1, 5, 5, 4, 2, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    memcpy(&levelDef3->chips[0][0],&chips3[0][0],sizeof(chips3));
    levelDef3->chip_types = 6;
    levelDef3->moves = 40;
    levelDef3->chip_goal = 0;
    levelDef3->chip_goal_count = 0;
    
    levels[0] = levelDef1;
    levels[1] = levelDef2;
    levels[2] = levelDef3;
}

GameData::~GameData() {
}

GameData* GameData::getInstance() {
    if(GameData::instance == nullptr) {
        GameData::instance = new GameData();
    }
    
    return GameData::instance;
}

// 存档 level
void GameData::save() {
    //this->levelsCompleted
}

//恢复档位 level
void GameData::load() {
    //this->levelsCompleted = 
} 

void GameData::onWinLevel(int lvl, int score) {
    /**
    this->totalScore += score, 
    if(lvl == this->levelsCompleted){
        this->levelsCompleted = lvl + 1;
        if(this->levelsCompleted > this->getTotalLevels()){
            this->levelsCompleted = this->getTotalLevels();
        }
    }

    this->save();
    **/
}

int GameData::getTotalScore() {
    return this->totalScore;
}

int GameData::levelsAvailable() {
    //return Constants::g_DEBUG ? this->getTotalLevels()
    return this->levelsCompleted + 1;
}

LevelDef* GameData::getLevelDef(int e) {
    return this->levels[e];
}

int GameData::getTotalLevels() {
    return LEVEL_COUNT;//this->levels.length
}
