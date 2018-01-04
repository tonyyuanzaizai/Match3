#ifndef __GameObject_LAYER_H__
#define __GameObject_LAYER_H__

#include "cocos2d.h"

class GameObject : public cocos2d::Node
{
// 构造函数，默认参数
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    GameObject():
    liveTime(0),
    killed(false){};

    
    // a selector callback
    void update(float e);
    void kill();
    bool isDead();
    void onDead();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameObject);
    

//public 变量    
public:
    int liveTime;
    bool killed;

};

#endif // __GameObject_LAYER_H__
