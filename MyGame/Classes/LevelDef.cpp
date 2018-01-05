#include "LevelDef.h"
#include "Constants.h"

USING_NS_CC;


LevelDef::LevelDef() {
    this->chip_types = 0;
    this->moves = 0;
    this->chip_goal = 0;
    this->chip_goal_count = 0;

    this->form[0][0] =-1;
    this->dirt[0][0] = -1;
    this->chips[0][0] = -1;
}

LevelDef::~LevelDef() {
}

////////////////
