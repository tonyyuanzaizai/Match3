#include "LevelDef.h"
#include "Constants.h"

USING_NS_CC;


LevelDef::LevelDef() {
    this->chip_types = 0;
    this->moves = 0;
    this->chip_goal = 0;
    this->chip_goal_count = 0;

    this->form = nullptr;
    this->dirt = nullptr;
    this->chips = nullptr;
}

LevelDef::~LevelDef() {
}

////////////////
