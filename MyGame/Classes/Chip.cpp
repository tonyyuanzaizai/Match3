#include "Chip.h"
#include "Constants.h"

USING_NS_CC;

Chip* Chip::createChip(int cake, int x, int y, int pos, float delay){
    Chip* layer = Chip::create();

    layer.wasClear = false, //bool
    layer.state = null, //std::string
    layer.rotationSpeed = 0, //int
    layer.selected = false, //bool
    layer.stateTime = 0,//int 
    layer.rotationTimeOffset = Utils.RandomRange(0, 20), //int
    layer.bonusType = null, //std::string
    layer.jellyAnim = false, //bool
    layer.doubleMatched = false, //bool
    layer.canBeMatched = true, //bool
    layer.matchReason = null, //std::string
    layer.hole = false, //bool
    layer.stoneHeart = false, //bool
    layer.spawnYPos = pos, //int
    layer.colorID = cake; //int
    layer.spawnDelay = delay; //float
    
    this.indexX = x;
    this.indexY = y;
    
    if(cake != 9 && cake != 0) {
        this.chipPicture = AssetsManager.g_instance.getImage("cake_" + cake), 
        this.addChild(this.chipPicture), 
        this.chipPicture.x = -this.chipPicture.getBounds().width / 2, 
        this.chipPicture.y = -Constants.CELL_SIZE
    }

    
    this.setState(STATE_SPAWN_NEW), 
    
    if(cake == 9){
        this.convertToStoneHeart();
    }
    
    return layer;
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
    return this.matchReason
}
bool Chip::isHorizontal() {
    return this.horizontal
}
int Chip::getBonusType = function() {
    return this.bonusType
}
int Chip::getColorID() {
    return this.colorID
}
//Point Chip::getIndeces() {
//    return new Point(this.indexX, this.indexY)
//}
int Chip::getIndexX() {
    return this.indexX
}
int Chip::getIndexY() {
    return this.indexY
}
void Chip::setIncexes(int x, int y) {
    this.indexX = x;
    this.indexY = y;
} 
bool Chip::isMatching() {
    return this.state == this.STATE_MATCH
}
void Chip::update(float e) {
    this.stateTime += e;
    switch (this.state) {
        case STATE_NORMAL:
            if (this.stoneHeart) {
                break;
            }
            var n = this.stateTime * 9;
            r = Math.sin(n) * .13;
            this.scaleX = 1 + r;
            this.scaleY = 1 - r;
            if(n >= Math.PI * 1) {
                this.scaleX = 1;
                this.scaleY = 1;
            }
            
            this.canBeMatched = true;
            break;
        case STATE_EXCHANGE:
            if(this.stateTime >= Constants.EXCHANGE_TIME){
                this.setState(this.STATE_NORMAL);
            }
            break;
        case STATE_SPAWN_NEW:
            this.spawnDelay -= e;
            if(this.spawnDelay < 0) {
                this.speed.y += this.acceleration.y * e;
                this.x += e * this.speed.x;
                this.y += e * this.speed.y;
                if(this.y >= this.spawnYPos) {
                    this.y = this.spawnYPos;this.setState(this.STATE_NORMAL);
                    PlayState.g_instance.onShiftEnded();
                }
            }
            break;
        case this.STATE_SHIFT_DOWN:
            this.speed.y += this.acceleration.y * e;
            this.x += e * this.speed.x;
            this.y += e * this.speed.y;
            if(this.y >= this.spawnYPos) {
                 this.y = this.spawnYPos;
                 this.setState(this.STATE_NORMAL);
                 PlayState.g_instance.onShiftEnded();
            }
            break;
        case t.STATE_FALL_DOWN:
            this.speed.y += this.acceleration.y * e;
            this.x += e * this.speed.x;
            this.y += e * this.speed.y;
            this.rotation += this.rotationSpeed * e;
            if(this.y >= 1e3){
                this.kill();
            }
            break;
        case this.STATE_MATCH:
            this.scaleY = 1 - this.stateTime * 1.5;
            this.scaleX = 1 + this.stateTime * 1.5;
            this.alpha = 1 - this.stateTime / Constants.MATCH_TIME;
            if(this.stateTime >= Constants.MATCH_TIME / 2 && !this.wasClear){
                PlayState.g_instance.addPointsAt(this, this.matchReason);
                PlayState.g_instance.clearCell(this);
                this.wasClear = true;
            }

            if(this.stateTime >= Constants.MATCH_TIME) {
                this.kill();
            }
    }
    if(this.shiningCircle){
        this.shiningCircle.rotation += e * 20;
    }
}

void Chip::setState(int e) {
    if (e == this.state) {
        return;
    }
    
    this.stateTime = 0, 
    this.state = e;
    switch (e) {
        case this.STATE_NORMAL:
            this.jellyAnim = !0;
            break;
        case this.STATE_EXCHANGE:
            break;
        case this.STATE_SHIFT_DOWN:
            createjs.Tween.get(this, {
                loop: !1
            }).to({
                scaleX: 1,
                scaleY: 1
            }, 170, createjs.Ease.linear);
            break;
        case t.STATE_SPAWN_NEW:
            this.speed = new createjs.Point(0, 500), 
            this.acceleration = new createjs.Point(0, Constants.GRAVITY_ACC)
    }
}

void Chip::exchange(int x, int y) {
    this.deselect(); 
    this.setState(this.STATE_EXCHANGE);
    this.indexX = x;
    this.indexY = y;
}

void Chip::shiftDown(int y, int pos) {
    this.speed = new createjs.Point(0, -250);
    this.deselect();
    this.indexY = y;
    this.spawnYPos = pos;
    this.setState(this.STATE_SHIFT_DOWN);
}

void Chip::match(e) {
    if (this.stoneHeart) {
        this.fallDown();
        return
    }
    if (this.isHole()) {
        return;
    }
    
    if(this.state == this.STATE_MATCH) {
         this.doubleMatched = true;
    }
    if (!this.canBeMatched) {
        return;
    }
    this.matchReason = e, 
    this.setState(this.STATE_MATCH)
}

bool Chip::isDoubleMatched() {
    return this.doubleMatched
}

void Chip::select() {
    this.stateTime = 0;
    this.jellyAnim = true;
    this.selected = true;
}

void Chip::deselect() {
    if(this.selected) {
        this.scaleX = 1;
        this.scaleY = 1;
        this.selected = false;
    }
}

bool Chip::isNormal() {
    return this.state == this.STATE_NORMAL || this.state == t.STATE_HOLE;
}

int Chip::getState() {
    return this.state
}

bool Chip::isBonus() {
    return this.bonusType >0 ;
}

void Chip::convertToBonus(int bonusType, bool horizontal) {
    this.horizontal = horizontal;
    this.bonusType = bonusType;
    this.removeAllChildren();
    if (bonusType == t.BONUS_5) {
        var r = AssetsManager.g_instance.getImage("donut");
        this.addChild(r);
        r.x = -r.getBounds().width / 2;
        r.y = -r.getBounds().height
    }
    if (bonusType == t.BONUS_4) {
        var r = AssetsManager.g_instance.getImage(this.horizontal ? Constants.IMAGE_ARROW_BONUS_HOR : Constants.IMAGE_ARROW_BONUS_VERT);
        this.addChild(r);
        r.x = -r.getBounds().width / 2;
        r.y = -r.getBounds().height
    }
    if (bonusType == t.BONUS_BOMB) {
        var r = AssetsManager.g_instance.getImage(Constants.IMAGE_BOMB);
        this.addChild(r);
        r.x = -r.getBounds().width / 2, r.y = -r.getBounds().height
    }
    if(this.state != t.STATE_SPAWN_NEW) {
        PlayState.g_instance.addConverToBonusEffect(this);
    }
    this.canBeMatched = false; 
    PlayState.g_instance.takeStockMatch(this);
    this.colorID = -1;
    this.setState(this.STATE_NORMAL);
    PlayState.g_instance.tryClearDirt(this.indexX, this.indexY);
    PlayState.g_instance.tryClearStoneHeart(this.indexX, this.indexY);
}

void Chip::fallDown() {
    if (this.state == t.STATE_FALL_DOWN) {
        return;
    }
    
    this.setState(t.STATE_FALL_DOWN);
    this.chipPicture.y = -this.chipPicture.getBounds().height / 2;
    this.y -= this.chipPicture.getBounds().height / 2;
    this.speed = new createjs.Point(Utils.RandomRange(-100, 100), -250);
    this.rotationSpeed = Utils.RandomRange(-300, 300);
    PlayState.g_instance.addChild(this);
    if(!this.wasClear) {
        PlayState.g_instance.clearCell(this);
        this.wasClear = true;
    }
}

bool Chip::isHole() {
    return this.hole
}

void Chip::convertToHole() {
    this.removeAllChildren();
    this.hole = true;
    this.y = this.spawnYPos; 
    this.setState(t.STATE_HOLE);
    this.colorID = -1;
}

void Chip::convertToStoneHeart() {
    this.stoneHeart = true;
    this.colorID = -1;
    var e = Constants.IMAGE_STONE_HEART;
    this.chipPicture = AssetsManager.g_instance.getImage(e);
    this.addChild(this.chipPicture);
    this.chipPicture.x = -this.chipPicture.getBounds().width / 2;
    this.chipPicture.y = -83;
}
bool Chip::isStoneHeart() {
    return this.stoneHeart
}

////////////////////