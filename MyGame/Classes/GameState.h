#ifndef __GameState_LAYER_H__
#define __GameState_LAYER_H__

#include "cocos2d.h"

class GameState : public GameObject
{

//public init
public:
    virtual bool init();

//public 变量    
public:
    bool initiliazed;
    Vector<GameState*> GameStates;
    Vector<GameState*> newGameStates;
    Vector<GameState*> gui;

// public 方法
public:
    bool isInitiliazed();
    //void onMouseDown(e, t);
    //void onMouseMove(e, t);
    //void onMouseUp(e, t);
    void addGuiObject(e);
    void update(e);
    void addGameState(e);
    void addGameStateAt(e, t);
    void addGameObjectAtPos(e, t, n, r);
    void cleanup();
    void resume();//屏幕适应
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameState);
};

#endif // __GameState_LAYER_H__
/////