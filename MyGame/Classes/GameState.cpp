#include "GameState.h"
#include "GameObject.h"
#include "Constants.h"

USING_NS_CC;

bool GameState::init()
{
    // 1. super init first
    if(!GameObject::init()) {
        return false;
    }

    initiliazed = true;
    //gameObjects = new std::vector<GameState*>();
    //newGameObjects = new std::vector<GameState*>();
    //gui = new std::vector<GameState*>();
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
    gui.push_back(e);
    addGameObject(e);
}
void GameState::update(float e) {
    liveTime += e;
    // TODO 这里有可能有内存泄露，需要删除旧的gameObjects 指针
    newGameObjects.clear();
    for (int t = 0; t < this->gameObjects.size(); t++) {
        GameState* n = gameObjects[t];
        n->update(e);
        n->isDead() ? n->onDead() : newGameObjects.push_back(n);
    }
    gameObjects = newGameObjects;
}
void GameState::addGameObject(GameState* e) {
    gameObjects.push_back(e);
}
void GameState::addGameObjectAt(GameState* e, Layer* t) {
    gameObjects.push_back(e);
    
    if(t){
        t->addChild(e);
    }
}
void GameState::addGameObjectAtPos(GameState* e, Layer* t, float n, float r) {
    gameObjects.push_back(e);
    
    if(t) {
        t->addChild(e);
        e->setPositionX(n);
        e->setPositionY(r);
    }
} 

void GameState::cleanup() {
    
}

void GameState::resume() {
    
}
