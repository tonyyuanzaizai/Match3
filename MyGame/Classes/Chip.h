#ifndef __Match3_Chip_LAYER_H__
#define __Match3_Chip_LAYER_H__

#include "cocos2d.h"

class Chip : public cocos2d::Layer
{

// public static function
public:
    static Chip* createChip(int cake, int x, int y, int pos, float delay);

// public 方法
public:
    virtual bool init();
    int getMatchReason();
    bool isHorizontal();
    int getBonusType();
    int getColorID();
    //Point getIndeces();//格子位置
    int getIndexX(); //格子位置
    int getIndexY(); //格子位置
    void setIncexes(int x, int y);//格子位置
    //this.indexX = x, this.indexY = y
    bool isMatching();
    //return this.state == this.STATE_MATCH
    void update(float e);
    void setState(int e);
    void exchange(int x, int y);
    void shiftDown(int y, int sy);
    void match(int e);
    bool isDoubleMatched();
    //return this.doubleMatched
    void select();
    //this.stateTime = 0, this.jellyAnim = !0, this.selected = !0
    void deselect();
    //this.selected && (this.scaleX = this.scaleY = 1, this.selected = !1)
    bool isNormal();
    //return this.state == this.STATE_NORMAL || this.state == t.STATE_HOLE
    int getState();
    //return this.state
    bool isBonus();
    //return this.bonusType != null
    void convertToBonus(int bonusType, bool horizontal);
    void fallDown();
    bool isHole();
    void convertToHole();
    void convertToStoneHeart();
    bool isStoneHeart();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Chip);
    
private:
    void initChip(int cake, int x, int y, int pos, float delay);
    
//public 变量
public:
    bool wasClear; //bool
    int state; //std::string
    int rotationSpeed; //int
    bool selected; //bool
    int stateTime; //int 
    int rotationTimeOffset; //int
    int bonusType; //std::string
    bool jellyAnim; //bool
    bool doubleMatched; //bool
    bool canBeMatched; //bool
    int matchReason; //std::string
    bool hole; //bool
    bool stoneHeart; //bool
    bool horizontal;

private:    
    int indexX;
    int indexY;
    int spawnYPos; //int
    int colorID; //int
    float spawnDelay; //float
    cocos2d::Sprite* chipPicture;

//public static var
public:
    static int BONUS_4;// = "BONUS_4"; //1
    static int BONUS_5;// = "BONUS_5"; //2
    static int BONUS_BOMB;// = "BONUS_BOMB";//3 

    static int MATCH_REASON_SIMPLE;// = "MATCH_REASON_SIMPLE"; //1
    static int MATCH_REASON_EXCHANGE_WIHT_BONUS;// = "MATCH_REASON_EXCHANGE_WIHT_BONUS"; //2
    static int MATCH_REASON_BONUS_EFFECT_5;// = "MATCH_REASON_BONUS_EFFECT_5"; //3
    static int MATCH_REASON_BONUS_EFFECT_4_HOR;// = "MATCH_REASON_BONUS_EFFECT_4_HOR"; //4
    static int MATCH_REASON_BONUS_EFFECT_4_VERT;// = "MATCH_REASON_BONUS_EFFECT_4_VERT"; //5
    static int MATCH_REASON_I_AM_BONUS;// = "MATCH_REASON_I_AM_BONUS"; //6

    static int STATE_NORMAL;// = "STATE_NORMAL"; //1
    static int STATE_EXCHANGE;// = "STATE_EXCHANGE";//2 
    static int STATE_SHIFT_DOWN;// = "STATE_SHIFT_DOWN";//3 
    static int STATE_MATCH;// = "STATE_MATCH"; //4
    static int STATE_SPAWN_NEW;// = "STATE_SPAWN_NEW"; //5
    static int STATE_FALL_DOWN;// = "STATE_FALL_DOWN"; //6
    static int STATE_HOLE;// = "STATE_HOLE"; //7


};

int Chip::BONUS_4 = 1;//"BONUS_4";
int Chip::BONUS_5 = 2;//"BONUS_5"; 
int Chip::BONUS_BOMB = 3;//"BONUS_BOMB";

int Chip::MATCH_REASON_SIMPLE = 1;//"MATCH_REASON_SIMPLE";
int Chip::MATCH_REASON_EXCHANGE_WIHT_BONUS = 2;//"MATCH_REASON_EXCHANGE_WIHT_BONUS";
int Chip::MATCH_REASON_BONUS_EFFECT_5 = 3;//"MATCH_REASON_BONUS_EFFECT_5";
int Chip::MATCH_REASON_BONUS_EFFECT_4_HOR = 4;//"MATCH_REASON_BONUS_EFFECT_4_HOR";
int Chip::MATCH_REASON_BONUS_EFFECT_4_VERT = 5;//"MATCH_REASON_BONUS_EFFECT_4_VERT";
int Chip::MATCH_REASON_I_AM_BONUS = 6;//"MATCH_REASON_I_AM_BONUS";

int Chip::STATE_NORMAL = 1;//"STATE_NORMAL";
int Chip::STATE_EXCHANGE = 2;//"STATE_EXCHANGE";
int Chip::STATE_SHIFT_DOWN = 3;//"STATE_SHIFT_DOWN";
int Chip::STATE_MATCH = 4;//"STATE_MATCH";
int Chip::STATE_SPAWN_NEW = 5;//"STATE_SPAWN_NEW";
int Chip::STATE_FALL_DOWN = 6;//"STATE_FALL_DOWN"; 
int Chip::STATE_HOLE = 7;//"STATE_HOLE";

#endif // __Match3_Chip_LAYER_H__

//////
