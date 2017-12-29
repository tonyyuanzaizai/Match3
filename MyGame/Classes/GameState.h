#ifndef __GameState_LAYER_H__
#define __GameState_LAYER_H__

#include "cocos2d.h"

class GameState : public GameObject
{
// 构造函数，默认参数
public:
    GameState():
    initiliazed(true){};    

//public 变量    
public:
    bool initiliazed = false;
    Vector<GameState*> GameStates;
    Vector<GameState*> newGameStates;
    Vector<GameState*> gui;

// public 方法
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

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



        public isInitiliazed() {
            return this.initiliazed;
        }
        public onMouseDown(e, t) {
            for (var n = 0; n < this.gui.length; n++) this.gui[n].onMouseDown(e, t)
        }
        public onMouseMove(e, t) {
            for (var n = 0; n < this.gui.length; n++) this.gui[n].onMouseMove(e, t)
        }
        public onMouseUp(e, t) {
            for (var n = 0; n < this.gui.length; n++) this.gui[n].onMouseUp(e, t)
        }
    
        public addGuiObject(e) {
            this.gui.push(e);
            this.addGameState(e);
        }
        public update(e) {
            this.liveTime += e; 
            this.newGameStates = new Array;
            for (var t = 0; t < this.GameStates.length; t++) {
                var n = this.GameStates[t];
                n.update(e);
                n.isDead() ? n.onDead() : this.newGameStates.push(n);
            }
            this.GameStates = this.newGameStates
        }
        public addGameState(e) {
            this.GameStates.push(e);
        }
        public addGameStateAt(e, t) {
            this.GameStates.push(e);
            t && t.addChild(e);
        }

        public cleanup() {}, 
        public resume() {}, 
        public init() {
            this.initiliazed = !0
        }
