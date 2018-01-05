#ifndef __Match3_MainMenuState_LAYER_H__
#define __Match3_MainMenuState_LAYER_H__

#include "cocos2d.h"

class MainMenuState : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void onPlayTouch(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuState);
    
private:  
    // 声明  
    void gameStep(float dt);
    void startGame();
};

#endif // __Match3_MainMenuState_LAYER_H__
