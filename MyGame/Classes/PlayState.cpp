#include "GameState.h"
#include "PlayState.h"
#include "Chip.h"
#include "Constants.h"

USING_NS_CC;

PlayState* PlayState::createPlayState(int curLevel, bool isTask) {
    PlayState* layer = PlayState::create();
    this->initPlayState(curLevel, isTask);
    return layer;
}


void PlayState::initPlayState(int curLevel, bool isTask) {  
    try {
        PlayState::g_curLevel = curLevel;
        auto s = this->getImage(Constants::IMAGE_BACK);
        this->addChild(s);

        this->chipTypesCount = GameData::getInstance()->getLevelDef(curLevel)->chip_types;
        this->field = new Chip* [this->fieldWidth][this->fieldHeight];
        //for (int o = 0; o < this->fieldWidth; o++) {
        //    this->field[o] = new Array();
        //}
        
        this->addChild(this->holeLayer);
        this->addChild(this->dirtLayer);
        this->addChild(this->edgesLayer);
        this->addChild(this->underChipsLayer);
        this->addChild(this->backChipsLayer);

        this->matchInARow = 0;

        //初始化match3 格子信息, this->field
        this->spawnDefinedChips(GameData::getInstance()->getLevelDef(curLevel)->chips);
        
        var u = GameData::getInstance()->getLevelDef(curLevel)->form;
        for (int a = 0; a < this->fieldWidth; a++){
            for (int f = 0; f < this->fieldHeight; f++){
                if (u[f][a] == 0) {
                    this->field[a][f]->convertToHole()；
                    this->holeLayer->addChild(this->field[a][f]);
                    var l = this->getXPosByXIndex(a) - Constants::CELL_SIZE / 2;
                    var c = this->getYPosByYIndex(f) - Constants::CELL_SIZE;
                    if (f > 0 && u[f - 1][a] != 0 && a > 0 && u[f][a - 1] != 0) {
                        auto h = this->getImage(Constants::IMAGE_BORDER_CORNER);
                        h.x = l - 4;
                        h.y = c - 4;
                        this->edgesLayer->addChild(h);
                    }
                    if (f > 0 && u[f - 1][a] != 0 && a < this->fieldWidth - 1 && u[f][a + 1] != 0) {
                        auto p = this->getImage(Constants::IMAGE_BORDER_CORNER);
                        p.x = l + Constants::CELL_SIZE + 8 - 4;
                        p.y = c - 4;
                        p.rotation = 90;
                        this->edgesLayer->addChild(p);
                    }
                    if (f < this->fieldHeight - 1 && u[f + 1][a] != 0 && a > 0 && u[f][a - 1] != 0) {
                        auto d = this->getImage(Constants::IMAGE_BORDER_CORNER);
                        d.x = l - 4;
                        d.y = c + Constants::CELL_SIZE + 8 - 4;
                        d.rotation = -90;
                        this->edgesLayer->addChild(d);
                    }
                    if (f < this->fieldHeight - 1 && u[f + 1][a] != 0 && a < this->fieldWidth - 1 && u[f][a + 1] != 0) {
                        auto v = this->getImage(Constants::IMAGE_BORDER_CORNER);
                        v.x = l + Constants::CELL_SIZE + 8 - 4; 
                        v.y = c + Constants::CELL_SIZE + 8 - 4; 
                        v.rotation = -180;
                        this->edgesLayer->addChild(v);
                    }
                } else {
                    auto m = this->getImage(Constants::IMAGE_CELL);
                    this->holeLayer->addChild(m);
                    m.x = this->getXPosByXIndex(a) - Constants::CELL_SIZE / 2;
                    m.y = this->getYPosByYIndex(f) - Constants::CELL_SIZE;
                    if (a > 0 && u[f][a - 1] == 0) {
                        auto g = this->getImage(Constants::IMAGE_BORDER_SIDE);
                        g.rotation = -90;
                        g.x = m.x - 4;
                        g.y = m.y + Constants::CELL_SIZE;
                        this->edgesLayer->addChildAt(g, 0);
                    }
                    if (a < this->fieldWidth - 1 && u[f][a + 1] == 0) {
                        auto y = this->getImage(Constants::IMAGE_BORDER_SIDE);
                        y.rotation = -90;
                        y.x = m.x + Constants::CELL_SIZE - 4;
                        y.y = m.y + Constants::CELL_SIZE;
                        this->edgesLayer->addChildAt(y, 0);
                    }
                    if (f > 0 && u[f - 1][a] == 0) {
                        auto b = this->getImage(Constants::IMAGE_BORDER_SIDE);
                        b.x = m.x;
                        b.y = m.y - 4;
                        this->edgesLayer->addChildAt(b, 0);
                    }
                    if (f < this->fieldHeight - 1 && u[f + 1][a] == 0) {
                        auto w = this->getImage(Constants::IMAGE_BORDER_SIDE);
                        w.x = m.x;
                        w.y = m.y + Constants::CELL_SIZE - 4;
                        this->edgesLayer->addChildAt(w, 0)
                    }
                    if (f > 0 && u[f - 1][a] == 0 && a > 0 && u[f][a - 1] == 0) {
                        auto h = this->getImage(Constants::IMAGE_BORDER_CORNER);
                        h.x = m.x - 4; 
                        h.y = m.y - 4; 
                        this->edgesLayer->addChild(h)
                    }
                    if (f > 0 && u[f - 1][a] == 0 && a < this->fieldWidth - 1 && u[f][a + 1] == 0) {
                        auto p = this->getImage(Constants::IMAGE_BORDER_CORNER);
                        p.x = m.x + Constants::CELL_SIZE + 8 - 4;
                        p.y = m.y - 4;
                        p.rotation = 90;
                        this->edgesLayer->addChild(p);
                    }
                    if (f < this->fieldHeight - 1 && u[f + 1][a] == 0 && a > 0 && u[f][a - 1] == 0) {
                        auto d = this->getImage(Constants::IMAGE_BORDER_CORNER);
                        d.x = m.x - 4;
                        d.y = m.y + Constants::CELL_SIZE + 8 - 4;
                        d.rotation = -90;
                        this->edgesLayer->addChild(d);
                    }
                    if (f < this->fieldHeight - 1 && u[f + 1][a] == 0 && a < this->fieldWidth - 1 && u[f][a + 1] == 0) {
                        auto v = this->getImage(Constants::IMAGE_BORDER_CORNER);
                        v.x = m.x + Constants::CELL_SIZE + 8 - 4;
                        v.y = m.y + Constants::CELL_SIZE + 8 - 4; 
                        v.rotation = -180;
                        this->edgesLayer->addChild(v);
                    }
                }
            }
        }
                
        this->holeLayer->cache(0, 0, Constants::ASSETS_WIDTH, Constants::ASSETS_HEIGHT, 1);
        this->edgesLayer->cache(0, 0, Constants::ASSETS_WIDTH, Constants::ASSETS_HEIGHT, 1);
        this->fieldDirt = new Sprite* [this->fieldWidth][this->fieldHeight];//new Array(this->fieldWidth);
        
        //for (int o = 0; o < this->fieldWidth; o++) {
        //    this->fieldDirt[o] = new Array(this->fieldHeight);
        //}
        
        var E = GameData::getInstance()->getLevelDef(curLevel)->dirt;
        if (E) {
            this->goal = t.GOAL_DIRT;
            for (int a = 0; a < this->fieldWidth; a++){
                for (int f = 0; f < this->fieldHeight; f++){
                    if (E[f][a] != 0) {
                        this->dirtCount++;
                        var S = AssetsManager.g_instance.getCenteredBitmapWithProxy(Constants::IMAGE_DIRT);
                        S.x = this->getXPosByXIndex(a) - 1;
                        S.y = this->getYPosByYIndex(f) - Constants::CELL_SIZE / 2 + 3;
                        this->dirtLayer->addChild(S);
                        this->fieldDirt[a][f] = S;
                    }
                }
            }
            this->goalLabel.setText(this->dirtCount.toString());
        }
        else {
            this->goal = t.GOAL_COUNT;
            this->goalChipID = GameData::getInstance()->getLevelDef(curLevel)->chip_goal; 
            this->chipGoalCount = GameData::getInstance()->getLevelDef(curLevel)->chip_goal_count; 
            this->goalLabel.setText(this->chipGoalCount.toString());
        }
        
        this->addChild(this->getImage(Constants::IMAGE_GUI));//gui.png
        
        var x = new createjs.Container;
        x.scaleX = x.scaleY = .7;
        var T = new DNButton(Constants::IMAGE_BUTTON_PAUSE, function() {
            return i.onPauseClick();
        });
        x.addChild(T);
        this->addGuiObject(T);
        x.x = 55;
        x.y = 154;
        this->addChild(x);
        
        this->addChild(this->scoreLabel);
        this->scoreLabel.x = 168;
        this->scoreLabel.y = 134;
        this->moves = GameData::getInstance()->getLevelDef(curLevel)->moves;
        this->addChild(this->movesLabel);
        this->movesLabel.x = 370;
        this->movesLabel.y = 134;
        this->movesLabel.setText(this->moves.toString());
        this->addChild(this->goalLabel);
        this->goalLabel.x = 570;
        this->goalLabel.y = 134;
        if (this->goal == GOAL_DIRT) {
            auto N = this->getImage(Constants::IMAGE_DIRT);
            N.scaleX = N.scaleY = .45;
            this->addChild(N);
            N.x = 506;
            N.y = 130;
        } else {
            auto C = getImage((std::stringstream()<<"cake_"<<this->goalChipID).str());
            C.scaleX = C.scaleY = .66;
            this->addChild(C);
            C.x = 525;
            C.y = 149;
        }
        if (isTask) {
            var k = new TaskEffect(this->goal, this->chipGoalCount, this->goalChipID);
            this->addGameObject(k);
            this->addChild(k);
        }
        
        this->configureYAlign();
    } catch (L) {
        console.log(L, "playstate::constructor")
    }
}

bool PlayState::init()
{
    // 1. super init first
    if(!GameState::init()) {
        return false;
    }
    
    this->matchInARow = 0;
    this->inputState = nullptr;
    this->goal = t.GOAL_DIRT;
    //this->goalLabel = new DNTextField("0", "font_", -3);
    this->dirtCount = 0;
    this->fieldWidth = 8;
    this->fieldHeight = 8;
    
    this->selectedChip = nullptr;
    this->swapChip1 = nullptr;
    this->swapChip2 = nullptr;
    this->lastMovedChip = nullptr;
    
    this->dirtLayer = new createjs.Container;
    this->underChipsLayer = new createjs.Container;
    this->backChipsLayer = new createjs.Container;
    this->holeLayer = new createjs.Container;
    this->edgesLayer = new createjs.Container;

    this->inputStateTime = 0;
    this->score = 0;
    this->tmpScore = 0;
    //this->scoreLabel = new DNTextField("00000", "font_", -3);
    this->moves = 30;
    //this->movesLabel = new DNTextField("50", "font_", -3);
    this->findedMatchPos1 = nullptr;
    this->findedMatchPos2 = nullptr;
    this->moveHint = nullptr;
    this->chipTypesCount = 5;
    this->awesomeEffectTime = 0;
    this->superbEffectTime = 0;
    this->waitLose = false;
    this->waitLoseTime = 0;
    this->waitWin = false;
    this->waitWinTime = 0;
    this->lastDropSoundTime = -10;
    this->lastDropID = -1;
    this->lastSound = null;
    this->g_curLevel = -1;

    return true;
}


void PlayState::onPauseClick() {
    //StateManager.g_instance.pushState(new PauseState)//暂停按钮
}

void PlayState::createChip(int e, int t, float n) {
    var r = Utils.RandomRangeInt(1, this->chipTypesCount);
    Chip* i = Chip::createChip(r, e, t, this->getYPosByYIndex(t), n);
    i.setIncexes(e, t);
    this->addGameObjectAtPos(i, this->backChipsLayer, this->getXPosByXIndex(e), -Constants::CELL_SIZE);
    this->field[e][t] = i;
}

void PlayState::createChipWithColorID(int e, int t, float n, int r) {
    var i = Chip::createChip(r, e, t, this->getYPosByYIndex(t), n);
    i.setIncexes(e, t);
    this->addGameObjectAtPos(i, this->backChipsLayer, this->getXPosByXIndex(e), -Constants::CELL_SIZE);
    this->field[e][t] = i;
}

int PlayState::getXPosByXIndex(int e) {
    return e * Constants::CELL_SIZE + Constants::CELL_SIZE / 2 + Constants::FIELD_OFFSET_X;
}

int PlayState::getYPosByYIndex(int e) {
    return e * Constants::CELL_SIZE + Constants::CELL_SIZE / 2 + Constants::FIELD_OFFSET_Y;
}

void PlayState::update(float n) {
    e.prototype.update.call(this, n);
    
    //win
    if (this->waitWin) {
        this->waitWinTime += n;
        if (this->waitWinTime > 2.4) {
            StateManager.g_instance.pushState(new WinState(t.g_curLevel, this->score));
            return
        }
    }
    //lose
    if (this->waitLose) {
        this->waitLoseTime += n;
        if (this->waitLoseTime > 2.4) {
            StateManager.g_instance.pushState(new GameOverState(0, 0));
            return
        }
    }
    
    this->inputStateTime += n;
    if(this->inputState != INPUT_STATE_WAIT_SELECTION && this->moveHint){
        this->moveHint.isDead() ? this->moveHint = null : this->moveHint.hide();
    }
    
    switch (this->inputState) {
        case INPUT_STATE_WAIT_SELECTION:
            try {
                int r = 3;
                if(this->inputStateTime > r && this->moveHint && !this->moveHint.parent){
                     this->addGameObjectAt(this->moveHint, this);
                }
            } catch (i) {}
            break;
        case INPUT_STATE_WAIT_SPAWN:
            if(this->allChipsNormal()){
                this->matchMatches(this->findMatches());
            }
            break;
        case INPUT_STATE_SHIFT:
            if(this->allChipsNormal()){
                this->matchMatches(this->findMatches());
            }
            break;
        case INPUT_STATE_MATCHING:
            if(this->inputStateTime > Constants::MATCH_TIME / 2) {
                 this->shiftChips();
            }
    }
    if (this->tmpScore < this->score) {
        this->tmpScore += 17;
        if(this->tmpScore > this->score){
            this->tmpScore = this->score;
        }

        var s = this->tmpScore.toString();
        switch (s.length) {
            case 1:
                s = "0000" + s;
                break;
            case 2:
                s = "000" + s;
                break;
            case 3:
                s = "00" + s;
                break;
            case 4:
                s = "0" + s
        }
        this->scoreLabel.setText(s)
    }
}

bool PlayState::allChipsNormal() {
    for (int e = 0; e < this->fieldWidth; e++){
        for (int t = 0; t < this->fieldHeight; t++){
            if (this->field[e][t] != nullptr && !this->field[e][t]->isNormal()) return false;
        }
    }

    return true;
}

bool PlayState::canExchange(Chip* e, Chip* t) {
    try {
        if (e == t) return false;
        if (e->isHole() || t->isHole()) return false;
        int n = e->getIndexX() - t->getIndexX();
        int r = e->getIndexY() - t->getIndexY();
    } catch (i) {
        return false;
    }
    return Math.abs(n) == 1 && r == 0 || Math.abs(r) == 1 && n == 0;
}

void PlayState::exchangeChips(Chip* e, Chip* t) {
    var n = this;
    try {
        var r = e.x;
        var i = e.y;
        var s = e->getIndexX();
        var o = e->getIndexY();
        var u = t.x;
        var a = t.y;
        var f = t->getIndexX();
        var l = t->getIndexY();
        this->field[s][o] = t;
        this->field[f][l] = e;
        e.exchange(f, l);
        t.exchange(s, o);
        this->swapChip1 = e;
        this->swapChip2 = t;
        
        createjs.Tween.get(e, {
            loop: false
        }).to({
            x: u,
            y: a
        }, Constants::EXCHANGE_TIME * 1000, createjs.Ease.linear).call(function() {
            return n.onExchangeEnded();
        });
        
        createjs.Tween.get(t, {
            loop: false
        }).to({
            x: r,
            y: i
        }, Constants::EXCHANGE_TIME * 1000, createjs.Ease.linear);
        this->selectedChip = null;
        this->setInpunState(INPUT_STATE_LOCK);
    } catch (c) {}
}

void PlayState::addConverToBonusEffect(Chip* e) {
    var t = new ConvertToBonusEffect(e);
    this->addGameObjectAtPos(t, this->underChipsLayer, e.x, e.y - Constants::CELL_SIZE / 2);
}

void PlayState::matchMatches(Vector<Chip*> e) {
    try {
        if (e.length != 0) {
            switch (this->matchInARow) {
                case 0:
                    SoundManager.g_instance.play(SoundManager.SOUND_MATCH_1);
                    break;
                case 1:
                    SoundManager.g_instance.play(SoundManager.SOUND_MATCH_2);
                    break;
                case 2:
                    SoundManager.g_instance.play(SoundManager.SOUND_MATCH_3);
                    break;
                case 3:
                    SoundManager.g_instance.play(SoundManager.SOUND_MATCH_4);
                    break;
                default:
                    SoundManager.g_instance.play(SoundManager.SOUND_MATCH_5)
            }
            bool t = false;
            for (int n = 0; n < e.length; n++) {
                for (int r = 0; r < e[n].length; r++) {
                    e[n][r]->match(Chip::MATCH_REASON_SIMPLE);
                }
                if (e[n]->size() == 4) {
                    bool i = false;
                    for (int s = 0; s < e[n].length; s++){
                        if (e[n][s] == this->lastMovedChip) {
                            i = true;
                            t = true; 
                            this->lastMovedChip->convertToBonus(Chip::BONUS_4, Math.random() < .5);
                            this->lastMovedChip = nullptr;
                            break
                        }
                    }
                    i || (t = !0, e[n][Utils.RandomRangeInt(1, 2)]->convertToBonus(Chip::BONUS_4))
                }
                if (e[n].length >= 5) {
                    bool i = false;
                    for (int s = 0; s < e[n].length; s++)
                        if (e[n][s] == this->lastMovedChip) {
                            t = true;
                            i = true;
                            this->lastMovedChip->convertToBonus(Chip::BONUS_5);
                            this->lastMovedChip = nullptr;
                            break;
                        }
                    i || (t = true, e[n][Utils.RandomRangeInt(1, e[n].length - 2)]->convertToBonus(Chip::BONUS_5))
                }
            }
            if (!t){
                for (int n = 0; n < e.length; n++) {
                    for (int r = 0; r < e[n].length; r++){
                        if (e[n][r]->isDoubleMatched()) {
                            e[n][r]->convertToBonus(Chip::BONUS_BOMB);
                            n = 100;
                            break;
                        }
                    }
                }                
            }

            this->setInpunState(INPUT_STATE_MATCHING);
        } else {
            this->shiftChips();
        }
    } catch (o) {
        console.log(o, "playstate::matchmatches")
    }
}

void PlayState::matchBonus(Chip* e, Chip* t) {
    try {
        if (e->getBonusType() == Chip::BONUS_4) {
            SoundManager.g_instance.play(SoundManager.SOUND_LINE);
            var n = e->isHorizontal();
            if (n) {
                var r = e->getIndexY();
                for (int i = 0; i < this->fieldWidth; i++) this->field[i][r] != null && this->field[i][r]->match(Chip::MATCH_REASON_BONUS_EFFECT_4_HOR);
                this->addGameObjectAtPos(new KillLineEffect(new createjs.Point(1200, 0)), this, e.x, e.y - Constants::CELL_SIZE / 2);
                this->addGameObjectAtPos(new KillLineEffect(new createjs.Point(-1200, 0)), this, e.x, e.y - Constants::CELL_SIZE / 2);
            } else {
                var s = e->getIndexX();
                for (int i = 0; i < this->fieldHeight; i++) this->field[s][i] != null && this->field[s][i]->match(Chip::MATCH_REASON_BONUS_EFFECT_4_VERT);
                this->addGameObjectAtPos(new KillLineEffect(new createjs.Point(0, -1200)), this, e.x, e.y - Constants::CELL_SIZE / 2);
                this->addGameObjectAtPos(new KillLineEffect(new createjs.Point(0, 1200)), this, e.x, e.y - Constants::CELL_SIZE / 2);
            }
        }
        if (e->getBonusType() == Chip::BONUS_5) {
            SoundManager.g_instance.play(SoundManager.SOUND_KILL_COLOR);
            e->match(Chip::MATCH_REASON_I_AM_BONUS);
            var o = new createjs.Point(e.x, e.y),
            var u = t->getColorID();
            if (u != -1){
                for (int a = 0; a < this->fieldWidth; a++){
                    for (int f = 0; f < this->fieldHeight; f++){
                        if (this->field[a][f] != null && this->field[a][f]->getColorID() == u) {
                            var l = new createjs.Point(this->field[a][f].x, this->field[a][f].y - Constants::CELL_SIZE / 2);
                            this->addGameObjectAtPos(new KillColorEffect(o, l), this, o.x, o.y);
                            this->field[a][f]->match(Chip::MATCH_REASON_BONUS_EFFECT_5);
                        }
                    }
                }
            }
        }

        if(e->getBonusType() == Chip::BONUS_BOMB) {
            this->boom(e);
            e->match(Chip::MATCH_REASON_I_AM_BONUS);
            t->match(Chip::MATCH_REASON_EXCHANGE_WIHT_BONUS);
        }
        this->setInpunState(INPUT_STATE_MATCHING);
    } catch (c) {}
}

void PlayState::boom(Chip* e) {
    try {
        SoundManager.g_instance.play(SoundManager.SOUND_BOOM);
        int t = e->getIndexX();
        int n = e->getIndexY();
        int r = 1;
        for (int i = t - r; i <= t + r; i++){
            for (int s = n - r; s <= n + r; s++) {
                if(this->validCoords(i, s) && this->field[i][s] != null) {
                    this->field[i][s]->match(Chip::MATCH_REASON_BONUS_EFFECT_4_HOR);
                }
            }
        }

        var o = new AutoreleaseEffect;
        this->addGameObjectAtPos(o, this, e.x, e.y);
    } catch (u) {}
}

bool PlayState::validCoords(int e, int t) {
    return e >= 0 && e < this->fieldWidth && t >= 0 && t < this->fieldHeight;
}

void PlayState::onExchangeEnded() {
    try {
        bool e = this->swapChip1 != null || this->swapChip2 != null;
        bool t = false;
        if(e){
            if(this->swapChip1 != null && this->swapChip1.isBonus()) {
                t = true;
            }
            if(this->swapChip2 != null && this->swapChip2.isBonus()) {
                t = true;
            }
        }
        
        var n = this->findMatches();
        if(n.length == 0){
            if(!t){
                if(e){
                    this->exchangeChips(this->swapChip1, this->swapChip2);
                    this->swapChip1 = null;
                    this->swapChip2 = null;
                }
                else {
                    this->setInpunState(INPUT_STATE_WAIT_SELECTION);
                }
            }
        }
        else {
            this->decreseMoves();
            this->matchMatches(n);
        }
        
        if(e && t) {
            if(this->swapChip1.isBonus()) {
                this->matchBonus(this->swapChip1, this->swapChip2);
            }
            if(this->swapChip2.isBonus()) {
                this->matchBonus(this->swapChip2, this->swapChip1);
            }
            this->decreseMoves();
        }
    } catch (r) {
        console.log(r, "playstate::exchangeended")
    }
}

void PlayState::decreseMoves() {
    this->moves--;
    if(this->moves < 0) {
        this->moves = 0;
    }
    this->movesLabel.setText(this->moves.toString());
}

Vector<Chip*> PlayState::findMatches() {
    try {
        Vector<Chip*> e = new Vector<Chip*>();
        for (int t = 0; t < this->fieldHeight; t++) {
            for (int n = 0; n < this->fieldWidth;) {
                int r = -1;
                int i = 0;

                Vector<Chip*> s = new Vector<Chip*>();
                for (int o = n; o < this->fieldWidth; o++) {
                    if (this->field[o][t] == null || this->field[o][t]->isBonus() || this->field[o][t]->getColorID() == -1) {
                        break;
                    }
                    if(r == -1){
                        r = this->field[o][t]->getColorID();
                    }
                    
                    if (this->field[o][t]->getColorID() != r) {
                        break;
                    }

                    s->pushBack(this->field[o][t]);
                    i++;
                }
                
                if(i >= 3) {
                    e->pushBack(s);
                }
                i != 0 ? n += i : n++;
            }
        }
        for (int n = 0; n < this->fieldWidth; n++) {
            for (int t = 0; t < this->fieldHeight; t) {
                int r = -1;
                int i = 0;

                Vector<Chip*> s = new Vector<Chip*>();
                for (int o = t; o < this->fieldHeight; o++) {
                    if (this->field[n][o] == null || this->field[n][o]->isBonus() || this->field[n][o]->getColorID() == -1) {
                        break;
                    }
                    if(r == -1){
                        r = this->field[n][o]->getColorID();
                    }

                    if (this->field[n][o]->getColorID() != r) {
                        break;
                    }
                    
                    s->pushBack(this->field[n][o]);
                    i++;
                }
                
                if(i >= 3) {
                    e->pushBack(s);
                }
                
                i != 0 ? t += i : t++;
            }
        }
    } catch (u) {}
    return e;
}

/*
void PlayState::onMouseUp(t, n) {
    e.prototype.onMouseUp.call(this, t, n), this->selectedChip = null
}

void PlayState::onMouseDown(t, n) {
    e.prototype.onMouseDown.call(this, t, n), n -= this->y;
    if (this->inputState != INPUT_STATE_WAIT_SELECTION) return;
    var r = this->checkChipSelection(t, n);
    if (r) {
        if (r == this->selectedChip) return;
        this->selectedChip ? this->canExchange(this->selectedChip, r) ? (this->lastMovedChip = this->selectedChip, this->exchangeChips(this->selectedChip, r), SoundManager.g_instance.play(SoundManager.SOUND_EXCHANGE)) : (this->selectedChip::deselect(), this->selectedChip = r, this->selectedChip::select()) : (this->selectedChip = r, this->selectedChip::select());
    }
}

void PlayState::onMouseMove(t, n) {
    e.prototype.onMouseMove.call(this, t, n);
    if (this->inputState != INPUT_STATE_WAIT_SELECTION) return;
    this->onMouseDown(t, n);
}
*/
void PlayState::shiftChips() {
    this->matchInARow++;
    bool e = false;
    for (int t = 0; t < this->fieldWidth; t++) {
        for (int n = this->fieldHeight - 1; n >= 0; n--) {
            Chip* r = this->field[t][n];
            if (!r) continue;
            if (r->isHole()) continue;
            for (int i = this->fieldHeight - 1; i > n; i--){
                if (this->field[t][i] == nullptr) {
                    e = true;
                    int s = i;
                    this->field[t][n]->shiftDown(s, this->getYPosByYIndex(s));
                    this->field[t][s] = this->field[t][n];
                    this->field[t][n] = nullptr;
                    break;
                }                
            }
        }
    }

    e ? this->setInpunState(INPUT_STATE_SHIFT) : this->spawnNewChips();
}

void PlayState::spawnNewChips() {
    int e = 0;
    for (int t = 0; t < this->fieldWidth; t++) {
        int n = -1;
        for (int r = this->fieldHeight - 1; r >= 0; r--) {
            if(this->field[t][r] == null){
                if(n == -1){
                    n = r;
                }
                e++;
                this->createChip(t, r, (n - r) * .13);
            }
        } 
    }
    
    e > 0 ? this->setInpunState(INPUT_STATE_WAIT_SPAWN) : this->setInpunState(INPUT_STATE_WAIT_SELECTION);
}

// 二维数组LevelDef
void PlayState::spawnDefinedChips(int* e) {
    for (int t = 0; t < this->fieldWidth; t++){
        for (int n = 0; n < this->fieldHeight; n++) {
            this->createChipWithColorID(t, n, (7 - n) * .13 + t * .11, e[n][t]);
        }        
    }

    this->setInpunState(INPUT_STATE_WAIT_SPAWN);
}

Chip* PlayState::checkChipSelection(int e, int t) {
    for (int n = 0; n < this->fieldWidth; n++)
        for (int r = 0; r < this->fieldHeight; r++) {
            var i = this->field[n][r];
            if (i && Math.abs(i.x - e) < Constants::CELL_SIZE / 2 && i.y > t && i.y < t + Constants::CELL_SIZE) {
                return i;
            }
        }
    return nullptr;
}

void PlayState::setInpunState(e) {
    try {
        this->inputState = e;
        this->inputStateTime = 0;
        if (this->inputState == INPUT_STATE_WAIT_SELECTION) {
            this->matchInARow = 0;
            if (this->findMoves()) {
                var t = this->field[this->findedMatchPos1.x][this->findedMatchPos1.y],
                var n = this->field[this->findedMatchPos2.x][this->findedMatchPos2.y];
                this->moveHint = new MoveHint(this->findedMatchPos1.y != this->findedMatchPos2.y);
                this->moveHint.x = (t.x + n.x) / 2;
                this->moveHint.y = (t.y + n.y) / 2 - Constants::CELL_SIZE / 2;
            } else {
                this->moveHint = nullptr;
                for (int r = 0; r < 100; r++) {
                    var i = this->field[Utils.RandomRangeInt(0, this->fieldWidth - 1)][Utils.RandomRangeInt(0, this->fieldHeight - 1)];
                    if (!i->isHole() && !i.isBonus() && !i.isStoneHeart()) {
                        i->convertToBonus([Chip::BONUS_BOMB, Chip::BONUS_4, Chip::BONUS_5][Utils.RandomRangeInt(0, 2)]);
                        break;
                    }
                }
            }
            if(this->moves <= 0) {
                this->lose();
            }
        }
    } catch (s) {
        this->inputState = INPUT_STATE_WAIT_SELECTION
    }
}

void PlayState::takeStockMatch(Chip* e) {
    var n = e->getIndexX(),
    var r = e->getIndexY();
    if(this->field[n][r] == e && this->goal == t.GOAL_COUNT && e.getColorID() == this->goalChipID) {
        this->chipGoalCount--;
        if(this->chipGoalCount <= 0) {
            this->chipGoalCount = 0;
            this->win();
        }

        this->goalLabel.setText(this->chipGoalCount.toString());
    }
}

void PlayState::clearCell(Chip* e) {
    var n = e->getIndexX(),
    var r = e->getIndexY();
    if(this->field[n][r] == e){
        if(this->goal == t.GOAL_COUNT && e->getColorID() == this->goalChipID){
            this->chipGoalCount--;
            if(this->chipGoalCount <= 0){
                this->chipGoalCount = 0;
                this->win();
            }

            this->goalLabel.setText(this->chipGoalCount.toString());
        }
        
        if(e->getMatchReason() == Chip::MATCH_REASON_BONUS_EFFECT_5 || 
            e->getMatchReason() == Chip::MATCH_REASON_BONUS_EFFECT_4_HOR || 
            e->getMatchReason() == Chip::MATCH_REASON_BONUS_EFFECT_4_VERT) {
            this->runParticleEffect(e->x, e->y - Constants::CELL_SIZE / 2);
        }
        
        this->field[n][r] = null;
    }
    
    this->tryClearDirt(n, r);
    if(e->isStoneHeart()){
        //
    }
    else {
        this->tryClearStoneHeart(n, r);
    }
}

void PlayState::tryClearDirt(int e, int n) {
    Chip* r = this->fieldDirt[e][n];
    if(r){
        createjs.Tween.get(r, {
                loop: false
            }).to({
                alpha: 0
            }, 250, createjs.Ease.linear);
            
        this->fieldDirt[e][n] = null;
        if(--this->dirtCount == 0){
             this->win();
        }
    } 
    
    if(this->goal == t.GOAL_DIRT){
        this->goalLabel.setText(this->dirtCount.toString());
    }
}

void PlayState::tryClearStoneHeart(int e, int t) {
    try {
        Chip* n = nullptr;
        
        n = this->getChipAt(e + 1, t);
        if(n !- null && n.isStoneHeart()){
            n.fallDown();
        }
        
        n = this->getChipAt(e - 1, t)
        if(n !- null && n.isStoneHeart()){
            n.fallDown();
        }
        
        n = this->getChipAt(e, t + 1)
        if(n !- null && n.isStoneHeart()){
            n.fallDown();
        }
        
        n = this->getChipAt(e, t - 1)
        if(n !- null && n.isStoneHeart()){
            n.fallDown();
        }
    } catch (r) {}
}

void PlayState::finishLevel() {
    for (int e = 0; e < this->fieldWidth; e++){
        for (int t = 0; t < this->fieldHeight; t++) {
            if(this->field[e][t] != null && this->field[e][t]->isNormal()){
                this->field[e][t]->fallDown();
            }
        }
    }
}

void PlayState::lose() {
    if(this->waitLose){
        //
    } 
    else {
        this->waitLose = true;
        this->addGameObjectAt(new TimeIsUpEffect(Constants::IMAGE_OUT_OF_MOVES), this);
        SoundManager.g_instance.play(SoundManager.SOUND_LOSE);
    }
}

void PlayState::win() {
    if(this->waitWin){
        //
    } 
    else {
        this->waitWin = true;
        SoundManager.g_instance.play(SoundManager.SOUND_WIN));
    }
}

void PlayState::addPointsAt(Chip* e, int t) {
    if (e->getBonusType() == null) {
        var n = 40;
        switch (t) {
            case Chip::MATCH_REASON_EXCHANGE_WIHT_BONUS:
                n = 40;
                break;
            case Chip::MATCH_REASON_BONUS_EFFECT_5:
                n = 100;
                break;
            case Chip::MATCH_REASON_BONUS_EFFECT_4_HOR:
                n = 90;
                break;
            case Chip::MATCH_REASON_BONUS_EFFECT_4_VERT:
                n = 120;
                break;
            case Chip::MATCH_REASON_I_AM_BONUS:
                n = 150;
                break;
            default:
                n = 40 + this->matchInARow * 20
        }
        var r = new FlyingPoints(n);
        this->score += n;
        var i = e.x - Constants::CELL_SIZE / 2,
        var s = e.y - Constants::CELL_SIZE / 2;
        this->tryShowAwesome(i, s);
        this->tryShowSuperb(i, s);
        this->addGameObjectAtPos(r, this, i, s);
    }
}

bool PlayState::tryShowSuperb(int e, int t) {
    if (this->matchInARow >= 3 && this->superbEffectTime != this->liveTime) {
        this->superbEffectTime = this->liveTime;
        SuperbEffect* n = new SuperbEffect;
        
        this->addGameObjectAtPos(n, this, e, t);
        SoundManager.g_instance.play(SoundManager.SOUND_AWESOME);
        if(n.x < 120) {
            n.x = 120;
        }
        
        if(n.x > Constants::ASSETS_WIDTH - 120) {
            n.x = Constants::ASSETS_WIDTH - 120;
        }
        this->score += 500;
        
        return true;
    }
    return false;
}

bool PlayState::tryShowAwesome(int e, int t) {
    if (this->matchInARow == 2 && this->awesomeEffectTime != this->liveTime) {
        this->awesomeEffectTime = this->liveTime;
        var n = new ShowAwesomeEffect;

        this->addGameObjectAtPos(n, this, e, t);
        SoundManager.g_instance.play(SoundManager.SOUND_AWESOME);
        if(n.x < 120) {
            n.x = 120;
        }
        
        if(n.x > Constants::ASSETS_WIDTH - 120) {
            n.x = Constants::ASSETS_WIDTH - 120;
        }
        
        this->score += 200; 
        return true;
    }
    return false;
}

bool PlayState::findMoves() {
    try {
        var e = [
                [2, -1],
                [3, 0],
                [2, 1]
            ],
            t = [
                [-1, -1],
                [-2, 0],
                [-1, 1]
            ],
            n = [
                [1, -1],
                [1, 1]
            ];
        for (int r = 0; r < this->fieldHeight; r++){
            for (int i = 0; i < this->fieldWidth - 1; i++){
                if (this->field[i][r]->getColorID() == this->field[i + 1][r]->getColorID()) {
                    if (this->findPattern(i, r, this->field[i][r]->getColorID(), e, i + 2, r)) return true;
                    if (this->findPattern(i, r, this->field[i][r]->getColorID(), t, i - 1, r)) return true;
                }                
            }
        }

        for (int r = 0; r < this->fieldHeight; r++){
            for (int i = 0; i < this->fieldWidth - 2; i++){
                if (this->field[i][r]->getColorID() == this->field[i + 2][r]->getColorID() && this->findPattern(i, r, this->field[i][r]->getColorID(), n, i + 1, r)) return true;                
            }
        }

        var s = [
                [-1, 2],
                [0, 3],
                [1, 2]
            ];
        var o = [
                [-1, -1],
                [0, -2],
                [1, -1]
            ];
        var u = [
                [-1, 1],
                [1, 1]
            ];
        for (int r = 0; r < this->fieldHeight - 1; r++){
            for (int i = 0; i < this->fieldWidth; i++){
                if (this->field[i][r]->getColorID() == this->field[i][r + 1]->getColorID()) {
                    if (this->findPattern(i, r, this->field[i][r]->getColorID(), s, i, r + 2)) return true;
                    if (this->findPattern(i, r, this->field[i][r]->getColorID(), o, i, r - 1)) return true
                }
            }
        }

        for (int r = 0; r < this->fieldHeight - 2; r++){
            for (int i = 0; i < this->fieldWidth; i++){
                if (this->field[i][r]->getColorID() == this->field[i][r + 2]->getColorID() && this->findPattern(i, r, this->field[i][r]->getColorID(), u, i, r + 1)) return true;                
            }
        }
    } catch (a) {
        console.log(a, "playstate::findmoves");
        return false;
    }
    return false;
}

bool PlayState::findPattern(int e, int t, int n, int r, int i, int s) {
    if (n <= 0) {
        return false;
    }
    if (i < 0 || i >= this->fieldWidth || s < 0 || s >= this->fieldHeight) {
        return false;
    }
    if (this->field[i][s] && this->field[i][s]->isHole()) {
        return false;
    }
    for (int o = 0; o < r.length; o++) {
        var u = this->getColorAt(e + r[o][0], t + r[o][1]);
        if (u <= 0) {
            continue;
        }
        if (u == n) {
            this->findedMatchPos1 = new createjs.Point(i, s);
            this->findedMatchPos2 = new createjs.Point(e + r[o][0], t + r[o][1]);
            return true;
        }
    }
    return false;
}

void PlayState::setHintIndeces(int e, int t, int n, int r) {
    this->findedMatchPos1 = new createjs.Point(e, t);
    this->findedMatchPos2 = new createjs.Point(n, r);
}

Chip* PlayState::getChipAt(int e, int t) {
    if(e < 0 || t < 0 || e >= this->fieldWidth || t >= this->fieldHeight || !this->field[e][t] || this->field[e][t]->isHole()){
        return null;
    }
    else {
        return this->field[e][t];
    }
}

int PlayState::getColorAt(int e, int t) {
    if(e < 0 || t < 0 || e >= this->fieldWidth || t >= this->fieldHeight || !this->field[e][t] == null){
        return -1;
    }
    else {
        return this->field[e][t]->getColorID();
    }
}

void PlayState::onShiftEnded() {
    if (this->liveTime != this->lastDropSoundTime) {
        this->lastDropSoundTime = this->liveTime;
        var e = Utils.RandomRangeInt(0, 2);
        for (int t = 0; e == this->lastDropID && t < 10; t++) {
            e = Utils.RandomRangeInt(0, 2);
        }
        this->lastDropID = e;
        switch (e) {
            case 0:
                SoundManager.g_instance.play(SoundManager.SOUND_DROP_1);
                break;
            case 1:
                SoundManager.g_instance.play(SoundManager.SOUND_DROP_2);
                break;
            case 2:
                SoundManager.g_instance.play(SoundManager.SOUND_DROP_3)
        }
    }
}

void PlayState::configureYAlign() {
    if (Constants::SCREEN_HEIGHT < Constants::ASSETS_HEIGHT){
        this->y = Constants::SCREEN_HEIGHT - Constants::ASSETS_HEIGHT;
    }
    else if (Constants::SCREEN_HEIGHT > Constants::ASSETS_HEIGHT) {
        this->y = (Constants::SCREEN_HEIGHT - Constants::ASSETS_HEIGHT) / 2;
        var e = new createjs.Shape;
        e.graphics.beginFill("#b5389c");
        e.graphics.drawRect(0, Constants::ASSETS_HEIGHT, Constants::ASSETS_WIDTH, Constants::SCREEN_HEIGHT - Constants::ASSETS_HEIGHT + 1);
        e.graphics.endFill();
        this->addChild(e);
        var t = new createjs.Shape;
        t.graphics.beginFill("#b5389c");
        t.graphics.drawRect(0, Constants::ASSETS_HEIGHT - Constants::SCREEN_HEIGHT, Constants::ASSETS_WIDTH, Constants::SCREEN_HEIGHT - Constants::ASSETS_HEIGHT);
        t.graphics.endFill();
        this->addChild(t);
    }
}

void PlayState::runParticleEffect(int x, int y) {
    var n = 80;
    var r = Utils.RandomRangeInt(3, 4);
    for (int i = 0; i < r; i++) {
        var s = Utils.RadToGrad(Utils.RandomRange(0, 360));
        var o = new HeartParticle(Math.cos(s) * n, Math.sin(s) * n);
        this->addGameObject(o);
        this->addChild(o);
        o.x = x + Utils.RandomRange(-Constants::CELL_SIZE / 3, Constants::CELL_SIZE / 3);
        o.y = y + Utils.RandomRange(-Constants::CELL_SIZE / 3, Constants::CELL_SIZE / 3);
    }
}

Sprite* PlayState::getImage(char* img){
    std::string _pngpath = (std::stringstream()<<"assets/art/"<<img<<".png").str();
    auto sp = Sprite::create(_pngpath);
    return sp;
}