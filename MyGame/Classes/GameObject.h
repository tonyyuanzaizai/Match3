#ifndef __GameObject_LAYER_H__
#define __GameObject_LAYER_H__

#include "cocos2d.h"

class GameObject : public cocos2d::Node
{
// 构造函数，默认参数
public:
    GameObject():
    liveTime(0),
    killed(false){};    

//public 变量    
public:
    int liveTime;
    bool killed

// public 方法
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    //virtual bool init();
    
    // a selector callback
    void update(float e);
    void kill();
    bool isDead();
    void onDead();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameObject);
};

#endif // __GameObject_LAYER_H__