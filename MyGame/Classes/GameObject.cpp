#include "GameObject.h"
#include "Constants.h"

USING_NS_CC;

bool GameObject::init()
{
    // 1. super init first
    if(!Layer::init()) {
        return false;
    }

    liveTime = 0;
    killed = false;
    return true;
}

void GameObject::update(float e)
{
    this->liveTime = this->liveTime + e;
}

void GameObject::kill()  
{  
    this->killed = true;
}  

bool GameObject::isDead()  
{  
    return this->killed;
}  
 
void GameObject::onDead()  
{  
    removeFromParent();
}
