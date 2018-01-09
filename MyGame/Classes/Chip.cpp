#include "Chip.h"
#include "Utils.h"
#include "PlayState.h"
#include "Constants.h"

USING_NS_CC;

Chip* Chip::createChip(int cake, int x, int y, int pos, float delay){
    Chip* layer = Chip::create();

    layer->initChip(cake, x, y, pos, delay);
    return layer;
}

void Chip::initChip(int cake, int x, int y, int pos, float delay) {
    this->wasClear = false; //bool
    this->state = 0; //std::string --> int
    this->rotationSpeed = 0; //int
    this->selected = false; //bool
    this->stateTime = 0;//int
    this->rotationTimeOffset = 1;//Utils::RandomRange(0, 20), //int
    this->bonusType = 0; //std::string  --> int
    this->jellyAnim = false; //bool
    this->doubleMatched = false; //bool
    this->canBeMatched = true; //bool
    this->matchReason = 0; //std::string --> int
    this->hole = false; //bool
    this->stoneHeart = false; //bool
    this->spawnYPos = pos; //int
    this->colorID = cake; //int
    this->spawnDelay = delay; //float
    this->horizontal = false;
    
    // 格子位置
    this->indexX = x;
    this->indexY = y;
    
    if(cake != 9 && cake != 0) {
        //layer->chipPicture = AssetsManager::g_instance->getImage("cake_" + cake),
        //int to string
        //std::to_string(intValue);
        //(stringstream()<<intValue).str();
        //(stringstream()<<year<<"/"<<month<<"/"<<day).str();// 2014/10/24
        
        //std::string _pngpath = "assets/art/cake_";
        //_pngpath = _pngpath + std::to_string(cake) + ".png";
        std::string _pngpath = (std::stringstream()<<"assets/art/cake_"<<cake<<".png").str();
        auto sp = Sprite::create(_pngpath);
        this->addChild(sp, 0);
        
        this->chipPicture = sp;
        //layer->chipPicture.x = -layer->chipPicture.getContentSize().width / 2,
        //layer->chipPicture.y = -Constants::CELL_SIZE
    }
    
    
    this->setState(STATE_SPAWN_NEW);
    
    if(cake == 9){
        this->convertToStoneHeart();
    }
    
    //return this;
}

// on "init" you need to initialize your instance
bool Chip::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    

    return true;
}

// public 函数
int Chip::getMatchReason() {
    return this->matchReason;
}
bool Chip::isHorizontal() {
    return this->horizontal;
}
int Chip::getBonusType() {
    return this->bonusType;
}
int Chip::getColorID() {
    return this->colorID;
}
//Point Chip::getIndeces() {
//    return new Point(this->indexX, this->indexY)
//}
int Chip::getIndexX() {
    return this->indexX;
}
int Chip::getIndexY() {
    return this->indexY;
}
void Chip::setIncexes(int x, int y) {
    this->indexX = x;
    this->indexY = y;
} 
bool Chip::isMatching() {
    return this->state == STATE_MATCH;
}
void Chip::update(float e) {
    this->stateTime += e;
    switch (this->state) {
        case STATE_NORMAL:
            if (this->stoneHeart) {
                break;
            }
            float n = this->stateTime * 9;
            float r = sin(n) * 0.13f;
            this->setScaleX(1 + r);
            this->setScaleY(1 - r);
            if(n >= M_PI * 1) {
                this->setScaleX(1);
                this->setScaleY(1);
            }
            
            this->canBeMatched = true;
            break;
        case STATE_EXCHANGE:
            if(this->stateTime >= Constants::EXCHANGE_TIME){
                this->setState(STATE_NORMAL);
            }
            break;
        case STATE_SPAWN_NEW:
            this->spawnDelay -= e;
            if(this->spawnDelay < 0) {
                this->speed.y += this->acceleration.y * e;
                this->setPositionX(this->getPositionX() + e * this->speed.x);
                this->setPositionY(this->getPositionY() + e * this->speed.y);
            
                
                if(this->getPositionY() >= this->spawnYPos) {
                    this->setPositionY(this->spawnYPos);
                    
                    this->setState(STATE_NORMAL);
                    PlayState::g_instance->onShiftEnded();
                }
            }
            break;
        case STATE_SHIFT_DOWN:
            this->speed.y += this->acceleration.y * e;
            this->setPositionX(this->getPositionX() + e * this->speed.x);
            this->setPositionY(this->getPositionY() + e * this->speed.y);
            
            if(this->getPositionY() >= this->spawnYPos) {
                 this->setPositionY(this->spawnYPos);
                 this->setState(this->STATE_NORMAL);
                 PlayState::g_instance->onShiftEnded();
            }
            break;
        case STATE_FALL_DOWN:
            this->speed.y += this->acceleration.y * e;
            this->setPositionX(this->getPositionX() + e * this->speed.x);
            this->setPositionY(this->getPositionY() + e * this->speed.y);
            this->setRotation(this->getRotation() + this->rotationSpeed * e);

            if(this->getPositionY() >= 1000){
                this->kill();
            }
            break;
        case STATE_MATCH:
            this->setScaleY(1 - this->stateTime * 1.5);
            this->setScaleX(1 + this->stateTime * 1.5);
            
            this->alpha = 1 - this->stateTime / Constants::MATCH_TIME;
            
            if(this->stateTime >= Constants::MATCH_TIME / 2 && !this->wasClear){
                PlayState::g_instance->addPointsAt(this, this->matchReason);
                PlayState::g_instance->clearCell(this);
                this->wasClear = true;
            }

            if(this->stateTime >= Constants::MATCH_TIME) {
                this->kill();
            }
    }
    if(this->shiningCircle){
        this->shiningCircle->setRotation(this->shiningCircle->getRotation() + e * 20);
    }
}

void Chip::setState(int e) {
    if (e == this->state) {
        return;
    }
    
    this->stateTime = 0;
    this->state = e;
    switch (e) {
        case STATE_NORMAL:
            this->jellyAnim = true;
            break;
        case STATE_EXCHANGE:
            break;
        case STATE_SHIFT_DOWN:
            /*
            Tween.get(this, {
                loop: false
            }).to({
                scaleX: 1,
                scaleY: 1
            }, 170, Ease.linear);
            */
            break;
        case STATE_SPAWN_NEW:
            this->speed = Point(0, 500);
            this->acceleration = Point(0, Constants::GRAVITY_ACC);//重力加速度
    }
}

void Chip::exchange(int x, int y) {
    this->deselect(); 
    this->setState(STATE_EXCHANGE);
    this->indexX = x;
    this->indexY = y;
}

void Chip::shiftDown(int y, int pos) {
    this->speed = Point(0, -250);
    this->deselect();
    this->indexY = y;
    this->spawnYPos = pos;
    this->setState(STATE_SHIFT_DOWN);
}

void Chip::match(int e) {
    if (this->stoneHeart) {
        this->fallDown();
        return;
    }
    if (this->isHole()) {
        return;
    }
    
    if(this->state == STATE_MATCH) {
         this->doubleMatched = true;
    }
    if (!this->canBeMatched) {
        return;
    }
    this->matchReason = e;
    this->setState(STATE_MATCH);
}

bool Chip::isDoubleMatched() {
    return this->doubleMatched;
}

void Chip::select() {
    this->stateTime = 0;
    this->jellyAnim = true;
    this->selected = true;
}

void Chip::deselect() {
    if(this->selected) {
        this->setScaleX(1);
        this->setScaleY(1);
        this->selected = false;
    }
}

bool Chip::isNormal() {
    return this->state == STATE_NORMAL || this->state == STATE_HOLE;
}

int Chip::getState() {
    return this->state;
}

bool Chip::isBonus() {
    return this->bonusType >0;
}

void Chip::convertToBonus(int bonusType, bool horizontal) {
    this->horizontal = horizontal;
    this->bonusType = bonusType;
    this->removeAllChildren();
    if (bonusType == BONUS_5) {
        //var r = AssetsManager::g_instance->getImage("donut");
        std::string _pngpath = (std::stringstream()<<"assets/art/cake_"<<"donut"<<".png").str();
        auto r = Sprite::create(_pngpath);
        
        this->addChild(r);
        r->sePositionX(-r.getContentSize().width / 2);
        r->sePositionY(-r.getContentSize().height);
    }
    if (bonusType == BONUS_4) {
        //svar r = AssetsManager::g_instance->getImage(this->horizontal ? Constants::IMAGE_ARROW_BONUS_HOR : Constants::IMAGE_ARROW_BONUS_VERT);
        std::string img = this->horizontal ? Constants::IMAGE_ARROW_BONUS_HOR : Constants::IMAGE_ARROW_BONUS_VERT;
        std::string _pngpath = (std::stringstream()<<"assets/art/cake_"<<img<<".png").str();
        auto r = Sprite::create(_pngpath);
        
        this->addChild(r);
        r->sePositionX(-r.getContentSize().width / 2);
        r->sePositionY(-r.getContentSize().height);
    }
    if (bonusType == BONUS_BOMB) {
        //var r = AssetsManager::g_instance->getImage(Constants::IMAGE_BOMB);
        std::string _pngpath = (std::stringstream()<<"assets/art/cake_"<<Constants::IMAGE_BOMB<<".png").str();
        auto r = Sprite::create(_pngpath);
        this->addChild(r);
        r->sePositionX(-r.getContentSize().width / 2);
        r->sePositionY(-r.getContentSize().height);
    }
    if(this->state != STATE_SPAWN_NEW) {
        PlayState::g_instance->addConverToBonusEffect(this);
    }
    this->canBeMatched = false; 
    PlayState::g_instance->takeStockMatch(this);
    this->colorID = -1;
    this->setState(this->STATE_NORMAL);
    PlayState::g_instance->tryClearDirt(this->indexX, this->indexY);
    PlayState::g_instance->tryClearStoneHeart(this->indexX, this->indexY);
}

void Chip::fallDown() {
    if (this->state == STATE_FALL_DOWN) {
        return;
    }
    
    this->setState(STATE_FALL_DOWN);
    this->chipPicture->setPositionY(this->chipPicture->getPositionY() - this->chipPicture->getContentSize().height / 2);
    this->setPositionY(this->getPositionY() - this->chipPicture->getContentSize().height / 2);
    
    this->speed = Point(Utils::RandomRange(-100, 100), -250);
    
    this->rotationSpeed = Utils::RandomRange(-300, 300);
    PlayState::g_instance->addChild(this);
    if(!this->wasClear) {
        PlayState::g_instance->clearCell(this);
        this->wasClear = true;
    }
}

bool Chip::isHole() {
    return this->hole;
}

void Chip::convertToHole() {
    this->removeAllChildren();
    this->hole = true;
    this->setPositionY(this->spawnYPos); 
    this->setState(STATE_HOLE);
    this->colorID = -1;
}

void Chip::convertToStoneHeart() {
    this->stoneHeart = true;
    this->colorID = -1;
    //std::string e = Constants::IMAGE_STONE_HEART;
    //this->chipPicture = AssetsManager::g_instance->getImage(e);
    
    std::string _pngpath = (std::stringstream()<<"assets/art/"<<Constants::IMAGE_STONE_HEART<<".png").str();    
    auto sp = Sprite::create(_pngpath);
    this->chipPicture = sp;
    this->addChild(this->chipPicture);
    
    this->chipPicture->setRotation(-90.0f);
    Size visibleSize = sp->getContentSize();
    this->chipPicture->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
}

bool Chip::isStoneHeart() {
    return this->stoneHeart;
}
