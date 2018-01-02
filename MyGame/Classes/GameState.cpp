#include "GameState.h"
#include "Constants.h"

USING_NS_CC;

bool GameState::init()
{
    // 1. super init first
    if(!Node::init()) {
        return false;
    }

    initiliazed = true;
    return true;
}

bool GameState::isInitiliazed() {
    return initiliazed;
}
/*
void GameState::onMouseDown(e, t) {
    for (var n = 0; n < this.gui.length; n++) this.gui[n].onMouseDown(e, t)
}
void GameState::onMouseMove(e, t) {
    for (var n = 0; n < this.gui.length; n++) this.gui[n].onMouseMove(e, t)
}
void GameState::onMouseUp(e, t) {
    for (var n = 0; n < this.gui.length; n++) this.gui[n].onMouseUp(e, t)
}
*/
void GameState::addGuiObject(GameState* e) {
    gui.pushBack(e);
    addGameObject(e);
}
void GameState::update(float e) {
    liveTime += e; 
    newGameObjects = new Array;
    for (var t = 0; t < this.gameObjects.length; t++) {
        var n = this.gameObjects[t];
        n.update(e);
        n.isDead() ? n.onDead() : this.newGameObjects.pushBack(n);
    }
    gameObjects = this.newGameObjects
}
void GameState::addGameObject(GameState* e) {
    gameObjects.pushBack(e);
}
void GameState::addGameObjectAt(GameState* e, Node* t) {
    gameObjects.pushBack(e);
    
    if(t){
        t.addChild(e);
    }
}
void GameState::addGameObjectAtPos(GameState* e, Node* t, float n, float r) {
    gameObjects.pushBack(e);
    
    if(t) {
        t.addChild(e);
        e.x = n;
        e.y = r;
    }
} 

void GameState::cleanup() {
    
}

void GameState::resume() {
    
}