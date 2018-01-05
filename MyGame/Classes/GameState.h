#ifndef __Match3_GameState_LAYER_H__
#define __Match3_GameState_LAYER_H__

#include "cocos2d.h"

class GameState : public GameObject
{

//public init
public:
    virtual bool init();

//public 变量    
public:
    bool initiliazed;
    Vector<GameState*> gameObjects;
    Vector<GameState*> newGameObjects;
    Vector<GameState*> gui;

// public 方法
public:
    bool isInitiliazed();
    //void onMouseDown(e, t);
    //void onMouseMove(e, t);
    //void onMouseUp(e, t);
    void addGuiObject(GameState* e);
    void update(float e);
    void addGameState(GameState* e);
    void addGameStateAt(GameState* e, Layer* t);
    void addGameObjectAtPos(GameState* e, Layer* t, float n, float r);
    void cleanup();
    void resume();//屏幕适应
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameState);
};

#endif // __Match3_GameState_LAYER_H__
/////