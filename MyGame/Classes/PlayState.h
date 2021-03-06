#ifndef __Match3_PlayState_LAYER_H__
#define __Match3_PlayState_LAYER_H__

#include "GameState.h"
#include "Chip.h"

#include "cocos2d.h"


#define ROW 8
#define COLUMN 8

class PlayState : public GameState
{

// public static function
public:
    static PlayState* createPlayState(int curLevel, bool isTask);
    void initPlayState(int curLevel, bool isTask);
//public init
public:
    virtual bool init();

//public 变量    
public:
    int matchInARow;// = 0, 
    int inputState;// = null, 
    int goal;// = GOAL_DIRT, 
    //TextField* goalLabel;// = new DNTextField("0", "font_", -3), 
    int dirtCount;// = 0, //需要消除的冰块数量
    int fieldWidth;// = 8, 
    int fieldHeight;// = 8,
    Chip* field[ROW][COLUMN];// ,
    cocos2d::Sprite* fieldDirt[ROW][COLUMN];

    Chip* selectedChip;// = null, 
    Chip* swapChip1;// = null, 
    Chip* swapChip2;// = null, 
    Chip* lastMovedChip;// = null, 

    Layer* dirtLayer;// = new createjs.Container, 
    Layer* underChipsLayer;// = new createjs.Container, 
    Layer* backChipsLayer;// = new createjs.Container, 
    Layer* holeLayer;// = new createjs.Container, 
    Layer* edgesLayer;// = new createjs.Container, 

    int inputStateTime;// = 0, 
    int score;// = 0, 
    int tmpScore;// = 0, 
    //TextField* scoreLabel = new DNTextField("00000", "font_", -3), 
    int moves;// = 30, 
    //TextField* movesLabel = new DNTextField("50", "font_", -3), 
    cocos2d::Point findedMatchPos1;// = null, 
    cocos2d::Point findedMatchPos2;// = null, 
    //MoveHint* moveHint;// = null, 
    int chipTypesCount;// = 5, 
    int awesomeEffectTime;// = 0, 
    int superbEffectTime;// = 0, 
    bool waitLose;// = false, 
    int waitLoseTime;// = 0, 
    bool waitWin;// = false, 
    int waitWinTime;// = 0, 
    int lastDropSoundTime;// = -10, 
    int lastDropID;// = -1,
    int goalChipID;
    int chipGoalCount;

//public static var
public:
    static int g_curLevel;// = -1;
    const static int GOAL_DIRT = 1;// = 1;//"GOAL_DIRT",
    const static int GOAL_COUNT = 2;// = 2;//"GOAL_COUNT"

    const static int INPUT_STATE_WAIT_SELECTION = 1;// = 1;//"INPUT_STATE_WAIT_SELECTION",
    const static int INPUT_STATE_LOCK = 2;// = 2;//"INPUT_STATE_LOCK",
    const static int INPUT_STATE_WAIT_SPAWN = 3;// = 3;//"INPUT_STATE_WAIT_SPAWN",
    const static int INPUT_STATE_SHIFT = 4;// = 4;//"INPUT_STATE_SHIFT",
    const static int INPUT_STATE_MATCHING = 5;// = 5;//"INPUT_STATE_MATCHING",
    const static int INPUT_STATE_WAIT_NEXT_ROUND = 6;// = 6;//"INPUT_STATE_WAIT_NEXT_ROUND",
    
    static PlayState* g_instance;

// public 方法
public:
    void onPauseClick();
    void createChip(int e, int t, float n);
    void createChipWithColorID(int e, int t, float n, int r);
    int getXPosByXIndex(int e);
    int getYPosByYIndex(int e);
    void update(float n);
    bool allChipsNormal();
    bool canExchange(Chip* e, Chip* t);
    void exchangeChips(Chip* e, Chip* t);
    void addConverToBonusEffect(Chip* e);
    void matchMatches(std::vector<std::vector<Chip*>> e);
    void matchBonus(Chip* e, Chip* t);
    void boom(Chip* e);
    bool validCoords(int e, int t);
    void onExchangeEnded();
    void decreseMoves();
    std::vector<std::vector<Chip*>> findMatches();
    /*
    void onMouseUp(t, n);
    void onMouseDown(t, n);
    void onMouseMove(t, n);
    */
    void shiftChips();
    void spawnNewChips();
    // 二维数组LevelDef
    void spawnDefinedChips(int e[ROW][COLUMN]);
    Chip* checkChipSelection(int e, int t);
    void setInpunState(int e);
    void takeStockMatch(Chip* e);
    void clearCell(Chip* e);
    void tryClearDirt(int e, int n);
    void tryClearStoneHeart(int e, int t);
    void finishLevel();
    void lose();
    void win();
    void addPointsAt(Chip* e, int t);
    bool tryShowSuperb(int e, int t);
    bool tryShowAwesome(int e, int t);
    bool findMoves();
    bool findPattern(int e, int t, int n, int r[][2], int i, int s);
    void setHintIndeces(int e, int t, int n, int r);
    Chip* getChipAt(int e, int t);
    int getColorAt(int e, int t);
    void onShiftEnded();
    void configureYAlign();
    void runParticleEffect(int x, int y);
    cocos2d::Sprite* getImage(char* img);
    
    // implement the "static create()" method manually
    CREATE_FUNC(PlayState);
};

int PlayState::g_curLevel = -1;
PlayState* PlayState::g_instance = nullptr;
//int PlayState::GOAL_DIRT = 1;//"GOAL_DIRT",
//int PlayState::GOAL_COUNT = 2;//"GOAL_COUNT"

//int PlayState::INPUT_STATE_WAIT_SELECTION = 1;//"INPUT_STATE_WAIT_SELECTION",
//int PlayState::INPUT_STATE_LOCK = 2;//"INPUT_STATE_LOCK",
//int PlayState::INPUT_STATE_WAIT_SPAWN = 3;//"INPUT_STATE_WAIT_SPAWN",
//int PlayState::INPUT_STATE_SHIFT = 4;//"INPUT_STATE_SHIFT",
//int PlayState::INPUT_STATE_MATCHING = 5;//"INPUT_STATE_MATCHING",
//int PlayState::INPUT_STATE_WAIT_NEXT_ROUND = 6;//"INPUT_STATE_WAIT_NEXT_ROUND",
#endif // __Match3_PlayState_LAYER_H__
/////////////////////////////////////


