#include "MainMenuState.h"
#include "Constants.h"
#include "SelectLevelState.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool MainMenuState::init()
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
    CCLOG("HelloWorld::init: %f, %f, %f", g_width, g_height, visibleSize.width);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    //init viewporter    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto playItem = MenuItemImage::create(
                                           "assets/art/button_play.png",
                                           "assets/art/button_play.png",
                                           CC_CALLBACK_1(MainMenuState::onPlayTouch, this));
	playItem->setRotation(-90.0f);
    playItem->setPosition(Vec2(origin.x + playItem->getContentSize().width/2 ,
                                origin.y + playItem->getContentSize().height/2));
    // create menu, it's an autorelease object
    auto menu = Menu::create(playItem, NULL);
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

    // add "MainMenuState" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");
    auto sprite = Sprite::create("assets/art/main_menu_back.jpg");
    //auto sprite = Sprite::create("main_menu_back.jpg");
    sprite->setRotation(-90.0f);
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void MainMenuState::onPlayTouch(Ref* pSender)
{
    //进入 SelectLevelState
    //Director::getInstance()->end();
    //StateManager.g_instance.pushState(new ShadeInState(new SelectLevelState))
    
    auto scene = Scene::create();
    auto layer = SelectLevelState::create();
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);  
}

// 实现  
void MainMenuState::gameStep(float dt)  
{  
    //bg->move();  
}  
void MainMenuState::startGame()  
{  
    // 调用  
    this->schedule(SEL_SCHEDULE(&MainMenuState::gameStep), 0.02f);  
}  
