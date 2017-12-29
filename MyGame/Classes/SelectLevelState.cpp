#include "SelectLevelState.h"
#include "Constants.h"


USING_NS_CC;

// on "init" you need to initialize your instance
bool SelectLevelState::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    float g_width = Director::getInstance()->getWinSize().width;
    float g_height = Director::getInstance()->getWinSize().height;
    CCLOG("HelloWorld::init: %f, %f, %f, %f, %f", g_width, g_height, origin.x, origin.y, visibleSize.width);
    /////////////////////////////
    // 2. add level button
    auto levelItem = MenuItemImage::create(
                                           "assets/art/button_play.png",
                                           "assets/art/button_play.png",
                                           CC_CALLBACK_1(SelectLevelState::onLevelTouch, this));
	levelItem->setRotation(-90.0f);
    levelItem->setPosition(Vec2(origin.x + levelItem->getContentSize().width/2 ,
                                origin.y + levelItem->getContentSize().height/2));
    // create menu, it's an autorelease object
    auto menu = Menu::create(levelItem, NULL);
    menu->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    /**
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
    **/

    // add "SelectLevelState" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");
    auto sprite = Sprite::create("assets/art/global_map.jpg");
    //auto sprite = Sprite::create("main_menu_back.jpg");
    sprite->setRotation(-90.0f);
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void SelectLevelState::onLevelTouch(Ref* pSender)
{
    //进入PlayState
}

void SelectLevelState::onExitTouch(Ref* pSender)
{
    // 退回到MainMenuState
}
