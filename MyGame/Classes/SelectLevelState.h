#ifndef __SelectLevelState_LAYER_H__
#define __SelectLevelState_LAYER_H__

#include "cocos2d.h"

class SelectLevelState : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void onLevelTouch(cocos2d::Ref* pSender);
    void onExitTouch(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SelectLevelState);
};

#endif // __SelectLevelState_LAYER_H__
