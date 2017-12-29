//PlayState.h
#ifndef __PlayState_SCENE_H__
#define __PlayState_SCENE_H__

#include "cocos2d.h"


// TODO lihua
//PlayState.cpp
// 三消界面
public class PlayState extends GameState{
        public PlayState(n, r) {
            this.INPUT_STATE_WAIT_SELECTION = "INPUT_STATE_WAIT_SELECTION", 
            this.INPUT_STATE_LOCK = "INPUT_STATE_LOCK", 
            this.INPUT_STATE_WAIT_SPAWN = "INPUT_STATE_WAIT_SPAWN", 
            this.INPUT_STATE_SHIFT = "INPUT_STATE_SHIFT", 
            this.INPUT_STATE_MATCHING = "INPUT_STATE_MATCHING", 
            this.INPUT_STATE_WAIT_NEXT_ROUND = "INPUT_STATE_WAIT_NEXT_ROUND", 
            this.matchInARow = 0, 
            this.inputState = null, 
            this.goal = t.GOAL_DIRT, 
            this.goalLabel = new DNTextField("0", "font_", -3), 
            this.dirtCount = 0, 
            this.fieldWidth = 8, 
            this.fieldHeight = 8, 
            this.selectedChip = null, 
            this.swapChip1 = null, 
            this.swapChip2 = null, 
            this.lastMovedChip = null, 
            this.dirtLayer = new createjs.Container, 
            this.underChipsLayer = new createjs.Container, 
            this.backChipsLayer = new createjs.Container, 
            this.holeLayer = new createjs.Container, 
            this.edgesLayer = new createjs.Container, 

            this.inputStateTime = 0, this.score = 0, 
            this.tmpScore = 0, 
            this.scoreLabel = new DNTextField("00000", "font_", -3), 
            this.moves = 30, 
            this.movesLabel = new DNTextField("50", "font_", -3), 
            this.findedMatchPos1 = null, 
            this.findedMatchPos2 = null, 
            this.moveHint = null, 
            this.chipTypesCount = 5, 
            this.awesomeEffectTime = 0, 
            this.superbEffectTime = 0, 
            this.waitLose = !1, 
            this.waitLoseTime = 0, 
            this.waitWin = !1, 
            this.waitWinTime = 0, 
            this.lastDropSoundTime = -10, 
            this.lastDropID = -1, 
            this.lastSound = null;
            try {
                t.g_curLevel = n;
                var s = AssetsManager.g_instance.getImage(Constants.IMAGE_BACK);
                this.addChild(s), 
                t.g_instance = this, 
                this.chipTypesCount = GameData.getInstance().getLevelDef(n).chip_types, 
                this.field = new Array(this.fieldWidth);
                for (var o = 0; o < this.fieldWidth; o++) this.field[o] = new Array(this.fieldHeight);
                this.addChild(this.holeLayer), 
                this.addChild(this.dirtLayer), 
                this.addChild(this.edgesLayer), 
                this.addChild(this.underChipsLayer), 
                this.addChild(this.backChipsLayer), 

                this.matchInARow = 0, 
                this.spawnDefinedChips(GameData.getInstance().getLevelDef(n).chips);//初始化match3 格子信息
                
                var u = GameData.getInstance().getLevelDef(n).form;
                for (var a = 0; a < this.fieldWidth; a++){
                    for (var f = 0; f < this.fieldHeight; f++){
                        if (u[f][a] == 0) {
                            this.field[a][f].convertToHole(), this.holeLayer.addChild(this.field[a][f]);
                            var l = this.getXPosByXIndex(a) - Constants.CELL_SIZE / 2,
                                c = this.getYPosByYIndex(f) - Constants.CELL_SIZE;
                            if (f > 0 && u[f - 1][a] != 0 && a > 0 && u[f][a - 1] != 0) {
                                var h = AssetsManager.g_instance.getImage(Constants.IMAGE_BORDER_CORNER);
                                h.x = l - 4, 
                                h.y = c - 4, 
                                this.edgesLayer.addChild(h)
                            }
                            if (f > 0 && u[f - 1][a] != 0 && a < this.fieldWidth - 1 && u[f][a + 1] != 0) {
                                var p = AssetsManager.g_instance.getImage(Constants.IMAGE_BORDER_CORNER);
                                p.x = l + Constants.CELL_SIZE + 8 - 4, 
                                p.y = c - 4, p.rotation = 90, 
                                this.edgesLayer.addChild(p)
                            }
                            if (f < this.fieldHeight - 1 && u[f + 1][a] != 0 && a > 0 && u[f][a - 1] != 0) {
                                var d = AssetsManager.g_instance.getImage(Constants.IMAGE_BORDER_CORNER);
                                d.x = l - 4, 
                                d.y = c + Constants.CELL_SIZE + 8 - 4, 
                                d.rotation = -90, 
                                this.edgesLayer.addChild(d)
                            }
                            if (f < this.fieldHeight - 1 && u[f + 1][a] != 0 && a < this.fieldWidth - 1 && u[f][a + 1] != 0) {
                                var v = AssetsManager.g_instance.getImage(Constants.IMAGE_BORDER_CORNER);
                                v.x = l + Constants.CELL_SIZE + 8 - 4, 
                                v.y = c + Constants.CELL_SIZE + 8 - 4, 
                                v.rotation = -180, 
                                this.edgesLayer.addChild(v)
                            }
                        } else {
                            var m = AssetsManager.g_instance.getImage(Constants.IMAGE_CELL);
                            this.holeLayer.addChild(m), 
                            m.x = this.getXPosByXIndex(a) - Constants.CELL_SIZE / 2, 
                            m.y = this.getYPosByYIndex(f) - Constants.CELL_SIZE;
                            if (a > 0 && u[f][a - 1] == 0) {
                                var g = AssetsManager.g_instance.getImage(Constants.IMAGE_BORDER_SIDE);
                                g.rotation = -90, 
                                g.x = m.x - 4, 
                                g.y = m.y + Constants.CELL_SIZE, 
                                this.edgesLayer.addChildAt(g, 0)
                            }
                            if (a < this.fieldWidth - 1 && u[f][a + 1] == 0) {
                                var y = AssetsManager.g_instance.getImage(Constants.IMAGE_BORDER_SIDE);
                                y.rotation = -90, 
                                y.x = m.x + Constants.CELL_SIZE - 4, 
                                y.y = m.y + Constants.CELL_SIZE, 
                                this.edgesLayer.addChildAt(y, 0)
                            }
                            if (f > 0 && u[f - 1][a] == 0) {
                                var b = AssetsManager.g_instance.getImage(Constants.IMAGE_BORDER_SIDE);
                                b.x = m.x, b.y = m.y - 4, this.edgesLayer.addChildAt(b, 0)
                            }
                            if (f < this.fieldHeight - 1 && u[f + 1][a] == 0) {
                                var w = AssetsManager.g_instance.getImage(Constants.IMAGE_BORDER_SIDE);
                                w.x = m.x, 
                                w.y = m.y + Constants.CELL_SIZE - 4, 
                                this.edgesLayer.addChildAt(w, 0)
                            }
                            if (f > 0 && u[f - 1][a] == 0 && a > 0 && u[f][a - 1] == 0) {
                                var h = AssetsManager.g_instance.getImage(Constants.IMAGE_BORDER_CORNER);
                                h.x = m.x - 4, 
                                h.y = m.y - 4, 
                                this.edgesLayer.addChild(h)
                            }
                            if (f > 0 && u[f - 1][a] == 0 && a < this.fieldWidth - 1 && u[f][a + 1] == 0) {
                                var p = AssetsManager.g_instance.getImage(Constants.IMAGE_BORDER_CORNER);
                                p.x = m.x + Constants.CELL_SIZE + 8 - 4, 
                                p.y = m.y - 4, p.rotation = 90, 
                                this.edgesLayer.addChild(p)
                            }
                            if (f < this.fieldHeight - 1 && u[f + 1][a] == 0 && a > 0 && u[f][a - 1] == 0) {
                                var d = AssetsManager.g_instance.getImage(Constants.IMAGE_BORDER_CORNER);
                                d.x = m.x - 4, 
                                d.y = m.y + Constants.CELL_SIZE + 8 - 4, 
                                d.rotation = -90, 
                                this.edgesLayer.addChild(d)
                            }
                            if (f < this.fieldHeight - 1 && u[f + 1][a] == 0 && a < this.fieldWidth - 1 && u[f][a + 1] == 0) {
                                var v = AssetsManager.g_instance.getImage(Constants.IMAGE_BORDER_CORNER);
                                v.x = m.x + Constants.CELL_SIZE + 8 - 4, 
                                v.y = m.y + Constants.CELL_SIZE + 8 - 4, 
                                v.rotation = -180, 
                                this.edgesLayer.addChild(v)
                            }
                        }
                    }
                }
                        
                this.holeLayer.cache(0, 0, Constants.ASSETS_WIDTH, Constants.ASSETS_HEIGHT, 1), 
                this.edgesLayer.cache(0, 0, Constants.ASSETS_WIDTH, Constants.ASSETS_HEIGHT, 1), 
                this.fieldDirt = new Array(this.fieldWidth);
                
                for (var o = 0; o < this.fieldWidth; o++) this.fieldDirt[o] = new Array(this.fieldHeight);
                
                var E = GameData.getInstance().getLevelDef(n).dirt;
                if (E) {
                    this.goal = t.GOAL_DIRT;
                    for (var a = 0; a < this.fieldWidth; a++){
                        for (var f = 0; f < this.fieldHeight; f++){
                            if (E[f][a] != 0) {
                                this.dirtCount++;
                                var S = AssetsManager.g_instance.getCenteredBitmapWithProxy(Constants.IMAGE_DIRT);
                                S.x = this.getXPosByXIndex(a) - 1, S.y = this.getYPosByYIndex(f) - Constants.CELL_SIZE / 2 + 3, this.dirtLayer.addChild(S), this.fieldDirt[a][f] = S
                            }
                        }
                    }
                    this.goalLabel.setText(this.dirtCount.toString())
                }
                else {
                    this.goal = t.GOAL_COUNT, 
                    this.goalChipID = GameData.getInstance().getLevelDef(n).chip_goal, 
                    this.chipGoalCount = GameData.getInstance().getLevelDef(n).chip_goal_count, 
                    this.goalLabel.setText(this.chipGoalCount.toString());
                }
                
                this.addChild(AssetsManager.g_instance.getImage(Constants.IMAGE_GUI));//gui.png
                var x = new createjs.Container;
                x.scaleX = x.scaleY = .7;
                var T = new DNButton(Constants.IMAGE_BUTTON_PAUSE, function() {
                    return i.onPauseClick()
                });
                x.addChild(T), 
                this.addGuiObject(T), 
                x.x = 55, 
                x.y = 154, 
                this.addChild(x), 
                
                this.addChild(this.scoreLabel), this.scoreLabel.x = 168, this.scoreLabel.y = 134, 
                this.moves = GameData.getInstance().getLevelDef(n).moves, 
                this.addChild(this.movesLabel), this.movesLabel.x = 370, this.movesLabel.y = 134, 
                this.movesLabel.setText(this.moves.toString()), 
                this.addChild(this.goalLabel), this.goalLabel.x = 570, this.goalLabel.y = 134;
                if (this.goal == t.GOAL_DIRT) {
                    var N = AssetsManager.g_instance.getImage(Constants.IMAGE_DIRT);
                    N.scaleX = N.scaleY = .45, this.addChild(N), N.x = 506, N.y = 130
                } else {
                    var C = AssetsManager.g_instance.getCenteredImageWithProxy("cake_" + this.goalChipID);
                    C.scaleX = C.scaleY = .66, this.addChild(C), C.x = 525, C.y = 149
                }
                if (r) {
                    var k = new TaskEffect(this.goal, this.chipGoalCount, this.goalChipID);
                    this.addGameObject(k), this.addChild(k)
                }
                this.configureYAlign()
            } catch (L) {
                console.log(L, "playstate::constructor")
            }
        }

        void PlayState::onPauseClick() {
            //StateManager.g_instance.pushState(new PauseState)//暂停按钮
        }, 
        void PlayState::createChip(e, t, n) {
            var r = Utils.RandomRangeInt(1, this.chipTypesCount),
            i = new Chip(r, e, t, this.getYPosByYIndex(t), n);
            i.setIncexes(e, t), 
            this.addGameObjectAtPos(i, this.backChipsLayer, this.getXPosByXIndex(e), -Constants.CELL_SIZE), 
            this.field[e][t] = i
        }, 
        void PlayState::createChipWithColorID(e, t, n, r) {
            var i = new Chip(r, e, t, this.getYPosByYIndex(t), n);
            i.setIncexes(e, t), 
            this.addGameObjectAtPos(i, this.backChipsLayer, this.getXPosByXIndex(e), -Constants.CELL_SIZE), 
            this.field[e][t] = i
        }, 
        void PlayState::getXPosByXIndex(e) {
            return e * Constants.CELL_SIZE + Constants.CELL_SIZE / 2 + Constants.FIELD_OFFSET_X
        }, 
        void PlayState::getYPosByYIndex(e) {
            return e * Constants.CELL_SIZE + Constants.CELL_SIZE / 2 + Constants.FIELD_OFFSET_Y
        }, 
        void PlayState::update(n) {
            e.prototype.update.call(this, n);
            
            //win
            if (this.waitWin) {
                this.waitWinTime += n;
                if (this.waitWinTime > 2.4) {
                    StateManager.g_instance.pushState(new WinState(t.g_curLevel, this.score));
                    return
                }
            }
            //lose
            if (this.waitLose) {
                this.waitLoseTime += n;
                if (this.waitLoseTime > 2.4) {
                    StateManager.g_instance.pushState(new GameOverState(0, 0));
                    return
                }
            }
            
            this.inputStateTime += n, this.inputState != this.INPUT_STATE_WAIT_SELECTION && this.moveHint && (this.moveHint.isDead() ? this.moveHint = null : this.moveHint.hide());
            switch (this.inputState) {
                case this.INPUT_STATE_WAIT_SELECTION:
                    try {
                        var r = 3;
                        this.inputStateTime > r && this.moveHint && !this.moveHint.parent && this.addGameObjectAt(this.moveHint, this)
                    } catch (i) {}
                    break;
                case this.INPUT_STATE_WAIT_SPAWN:
                    this.allChipsNormal() && this.matchMatches(this.findMatches());
                    break;
                case this.INPUT_STATE_SHIFT:
                    this.allChipsNormal() && this.matchMatches(this.findMatches());
                    break;
                case this.INPUT_STATE_MATCHING:
                    this.inputStateTime > Constants.MATCH_TIME / 2 && this.shiftChips()//初始化match3
            }
            if (this.tmpScore < this.score) {
                this.tmpScore += 17, this.tmpScore > this.score && (this.tmpScore = this.score);
                var s = this.tmpScore.toString();
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
                this.scoreLabel.setText(s)
            }
        }, 
        void PlayState::allChipsNormal() {
            for (var e = 0; e < this.fieldWidth; e++)
                for (var t = 0; t < this.fieldHeight; t++)
                    if (this.field[e][t] != null && !this.field[e][t].isNormal()) return !1;
            return !0
        }, 
        void PlayState::canExchange(e, t) {
            try {
                if (e == t) return !1;
                if (e.isHole() || t.isHole()) return !1;
                var n = e.getIndeces().x - t.getIndeces().x,
                    r = e.getIndeces().y - t.getIndeces().y
            } catch (i) {
                return !1
            }
            return Math.abs(n) == 1 && r == 0 || Math.abs(r) == 1 && n == 0
        }, 
        void PlayState::exchangeChips(e, t) {
            var n = this;
            try {
                var r = e.x,
                    i = e.y,
                    s = e.getIndexX(),
                    o = e.getIndexY(),
                    u = t.x,
                    a = t.y,
                    f = t.getIndexX(),
                    l = t.getIndexY();
                this.field[s][o] = t, this.field[f][l] = e, e.exchange(f, l), t.exchange(s, o), this.swapChip1 = e, this.swapChip2 = t, createjs.Tween.get(e, {
                    loop: !1
                }).to({
                    x: u,
                    y: a
                }, Constants.EXCHANGE_TIME * 1e3, createjs.Ease.linear).call(function() {
                    return n.onExchangeEnded()
                }), createjs.Tween.get(t, {
                    loop: !1
                }).to({
                    x: r,
                    y: i
                }, Constants.EXCHANGE_TIME * 1e3, createjs.Ease.linear), this.selectedChip = null, this.setInpunState(this.INPUT_STATE_LOCK)
            } catch (c) {}
        }, 
        void PlayState::addConverToBonusEffect(e) {
            var t = new ConvertToBonusEffect(e);
            this.addGameObjectAtPos(t, this.underChipsLayer, e.x, e.y - Constants.CELL_SIZE / 2)
        }, 
        void PlayState::matchMatches(e) {
            try {
                if (e.length != 0) {
                    switch (this.matchInARow) {
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
                    var t = !1;
                    for (var n = 0; n < e.length; n++) {
                        for (var r = 0; r < e[n].length; r++) e[n][r].match(Chip.MATCH_REASON_SIMPLE);
                        if (e[n].length == 4) {
                            var i = !1;
                            for (var s = 0; s < e[n].length; s++)
                                if (e[n][s] == this.lastMovedChip) {
                                    i = !0, t = !0, this.lastMovedChip.convertToBonus(Chip.BONUS_4, Math.random() < .5), this.lastMovedChip = null;
                                    break
                                }
                            i || (t = !0, e[n][Utils.RandomRangeInt(1, 2)].convertToBonus(Chip.BONUS_4))
                        }
                        if (e[n].length >= 5) {
                            var i = !1;
                            for (var s = 0; s < e[n].length; s++)
                                if (e[n][s] == this.lastMovedChip) {
                                    t = !0, i = !0, this.lastMovedChip.convertToBonus(Chip.BONUS_5), this.lastMovedChip = null;
                                    break
                                }
                            i || (t = !0, e[n][Utils.RandomRangeInt(1, e[n].length - 2)].convertToBonus(Chip.BONUS_5))
                        }
                    }
                    if (!t)
                        for (var n = 0; n < e.length; n++)
                            for (var r = 0; r < e[n].length; r++)
                                if (e[n][r].isDoubleMatched()) {
                                    e[n][r].convertToBonus(Chip.BONUS_BOMB), n = 100;
                                    break
                                }
                    this.setInpunState(this.INPUT_STATE_MATCHING)
                } else this.shiftChips()
            } catch (o) {
                console.log(o, "playstate::matchmatches")
            }
        }, 
        void PlayState::matchBonus(e, t) {
            try {
                if (e.getBonusType() == Chip.BONUS_4) {
                    SoundManager.g_instance.play(SoundManager.SOUND_LINE);
                    var n = e.isHorizontal();
                    if (n) {
                        var r = e.getIndexY();
                        for (var i = 0; i < this.fieldWidth; i++) this.field[i][r] != null && this.field[i][r].match(Chip.MATCH_REASON_BONUS_EFFECT_4_HOR);
                        this.addGameObjectAtPos(new KillLineEffect(new createjs.Point(1200, 0)), this, e.x, e.y - Constants.CELL_SIZE / 2), this.addGameObjectAtPos(new KillLineEffect(new createjs.Point(-1200, 0)), this, e.x, e.y - Constants.CELL_SIZE / 2)
                    } else {
                        var s = e.getIndexX();
                        for (var i = 0; i < this.fieldHeight; i++) this.field[s][i] != null && this.field[s][i].match(Chip.MATCH_REASON_BONUS_EFFECT_4_VERT);
                        this.addGameObjectAtPos(new KillLineEffect(new createjs.Point(0, -1200)), this, e.x, e.y - Constants.CELL_SIZE / 2), this.addGameObjectAtPos(new KillLineEffect(new createjs.Point(0, 1200)), this, e.x, e.y - Constants.CELL_SIZE / 2)
                    }
                }
                if (e.getBonusType() == Chip.BONUS_5) {
                    SoundManager.g_instance.play(SoundManager.SOUND_KILL_COLOR), e.match(Chip.MATCH_REASON_I_AM_BONUS);
                    var o = new createjs.Point(e.x, e.y),
                        u = t.getColorID();
                    if (u != -1)
                        for (var a = 0; a < this.fieldWidth; a++)
                            for (var f = 0; f < this.fieldHeight; f++)
                                if (this.field[a][f] != null && this.field[a][f].getColorID() == u) {
                                    var l = new createjs.Point(this.field[a][f].x, this.field[a][f].y - Constants.CELL_SIZE / 2);
                                    this.addGameObjectAtPos(new KillColorEffect(o, l), this, o.x, o.y), this.field[a][f].match(Chip.MATCH_REASON_BONUS_EFFECT_5)
                                }
                }
                e.getBonusType() == Chip.BONUS_BOMB && (this.boom(e), e.match(Chip.MATCH_REASON_I_AM_BONUS), t.match(Chip.MATCH_REASON_EXCHANGE_WIHT_BONUS)), this.setInpunState(this.INPUT_STATE_MATCHING)
            } catch (c) {}
        }, 
        void PlayState::boom(e) {
            try {
                SoundManager.g_instance.play(SoundManager.SOUND_BOOM);
                var t = e.getIndexX(),
                    n = e.getIndexY(),
                    r = 1;
                for (var i = t - r; i <= t + r; i++)
                    for (var s = n - r; s <= n + r; s++) this.validCoords(i, s) && this.field[i][s] != null && this.field[i][s].match(Chip.MATCH_REASON_BONUS_EFFECT_4_HOR);
                var o = new AutoreleaseEffect;
                this.addGameObjectAtPos(o, this, e.x, e.y)
            } catch (u) {}
        },
        void PlayState::validCoords(e, t) {
            return e >= 0 && e < this.fieldWidth && t >= 0 && t < this.fieldHeight
        }, 
        void PlayState::onExchangeEnded() {
            try {
                var e = this.swapChip1 != null || this.swapChip2 != null,
                    t = !1;
                e && (this.swapChip1.isBonus() && (t = !0), this.swapChip2.isBonus() && (t = !0));
                var n = this.findMatches();
                n.length == 0 ? t || (e ? (this.exchangeChips(this.swapChip1, this.swapChip2), this.swapChip1 = null, this.swapChip2 = null) : this.setInpunState(this.INPUT_STATE_WAIT_SELECTION)) : (this.decreseMoves(), this.matchMatches(n)), e && t && (this.swapChip1.isBonus() && this.matchBonus(this.swapChip1, this.swapChip2), this.swapChip2.isBonus() && this.matchBonus(this.swapChip2, this.swapChip1), this.decreseMoves())
            } catch (r) {
                console.log(r, "playstate::exchangeended")
            }
        }, 
        void PlayState::decreseMoves() {
            this.moves--, this.moves < 0 && (this.moves = 0), this.movesLabel.setText(this.moves.toString())
        }, 
        void PlayState::findMatches() {
            try {
                var e = Array();
                for (var t = 0; t < this.fieldHeight; t++) {
                    for (var n = 0; n < this.fieldWidth;) {
                        var r = -1,
                            i = 0,
                            s = new Array;
                        for (var o = n; o < this.fieldWidth; o++) {
                            if (this.field[o][t] == null || this.field[o][t].isBonus() || this.field[o][t].getColorID() == -1) break;
                            r == -1 && (r = this.field[o][t].getColorID());
                            if (this.field[o][t].getColorID() != r) break;
                            s.push(this.field[o][t]), i++
                        }
                        i >= 3 && e.push(s), i != 0 ? n += i : n++
                    }
                }
                for (var n = 0; n < this.fieldWidth; n++) {
                    for (var t = 0; t < this.fieldHeight; t) {
                        var r = -1,
                            i = 0,
                            s = new Array;
                        for (var o = t; o < this.fieldHeight; o++) {
                            if (this.field[n][o] == null || this.field[n][o].isBonus() || this.field[n][o].getColorID() == -1) break;
                            r == -1 && (r = this.field[n][o].getColorID());
                            if (this.field[n][o].getColorID() != r) break;
                            s.push(this.field[n][o]), i++
                        }
                        i >= 3 && e.push(s), i != 0 ? t += i : t++
                    }
                }
            } catch (u) {}
            return e
        }, 
        void PlayState::onMouseUp(t, n) {
            e.prototype.onMouseUp.call(this, t, n), this.selectedChip = null
        }, 
        void PlayState::onMouseDown(t, n) {
            e.prototype.onMouseDown.call(this, t, n), n -= this.y;
            if (this.inputState != this.INPUT_STATE_WAIT_SELECTION) return;
            var r = this.checkChipSelection(t, n);
            if (r) {
                if (r == this.selectedChip) return;
                this.selectedChip ? this.canExchange(this.selectedChip, r) ? (this.lastMovedChip = this.selectedChip, this.exchangeChips(this.selectedChip, r), SoundManager.g_instance.play(SoundManager.SOUND_EXCHANGE)) : (this.selectedChip.deselect(), this.selectedChip = r, this.selectedChip.select()) : (this.selectedChip = r, this.selectedChip.select())
            }
        }
        void PlayState::onMouseMove(t, n) {
            e.prototype.onMouseMove.call(this, t, n);
            if (this.inputState != this.INPUT_STATE_WAIT_SELECTION) return;
            this.onMouseDown(t, n)
        }
        void PlayState::shiftChips() {
            this.matchInARow++;
            var e = !1;
            for (var t = 0; t < this.fieldWidth; t++)
                for (var n = this.fieldHeight - 1; n >= 0; n--) {
                    var r = this.field[t][n];
                    if (!r) continue;
                    if (r.isHole()) continue;
                    for (var i = this.fieldHeight - 1; i > n; i--)
                        if (this.field[t][i] == null) {
                            e = !0;
                            var s = i;
                            this.field[t][n].shiftDown(s, this.getYPosByYIndex(s)), this.field[t][s] = this.field[t][n], this.field[t][n] = null;
                            break
                        }
                }
            e ? this.setInpunState(this.INPUT_STATE_SHIFT) : this.spawnNewChips()
        }, 
        void PlayState::spawnNewChips() {
            var e = 0;
            for (var t = 0; t < this.fieldWidth; t++) {
                var n = -1;
                for (var r = this.fieldHeight - 1; r >= 0; r--) {
                    this.field[t][r] == null && (n == -1 && (n = r), e++,
                } 
                this.createChip(t, r, (n - r) * .13))
            }
            e > 0 ? this.setInpunState(this.INPUT_STATE_WAIT_SPAWN) : this.setInpunState(this.INPUT_STATE_WAIT_SELECTION)
        }, 
        void PlayState::spawnDefinedChips(e) {
            for (var t = 0; t < this.fieldWidth; t++)
                for (var n = 0; n < this.fieldHeight; n++) {
                    this.createChipWithColorID(t, n, (7 - n) * .13 + t * .11, e[n][t]);
                }
            this.setInpunState(this.INPUT_STATE_WAIT_SPAWN)
        }, 
        void PlayState::checkChipSelection(e, t) {
            for (var n = 0; n < this.fieldWidth; n++)
                for (var r = 0; r < this.fieldHeight; r++) {
                    var i = this.field[n][r];
                    if (i && Math.abs(i.x - e) < Constants.CELL_SIZE / 2 && i.y > t && i.y < t + Constants.CELL_SIZE) return i
                }
            return null
        }, 
        void PlayState::setInpunState(e) {
            try {
                this.inputState = e, this.inputStateTime = 0;
                if (this.inputState == this.INPUT_STATE_WAIT_SELECTION) {
                    this.matchInARow = 0;
                    if (this.findMoves()) {
                        var t = this.field[this.findedMatchPos1.x][this.findedMatchPos1.y],
                            n = this.field[this.findedMatchPos2.x][this.findedMatchPos2.y];
                        this.moveHint = new MoveHint(this.findedMatchPos1.y != this.findedMatchPos2.y), 
                        this.moveHint.x = (t.x + n.x) / 2, 
                        this.moveHint.y = (t.y + n.y) / 2 - Constants.CELL_SIZE / 2
                    } else {
                        this.moveHint = null;
                        for (var r = 0; r < 100; r++) {
                            var i = this.field[Utils.RandomRangeInt(0, this.fieldWidth - 1)][Utils.RandomRangeInt(0, this.fieldHeight - 1)];
                            if (!i.isHole() && !i.isBonus() && !i.isStoneHeart()) {
                                i.convertToBonus([Chip.BONUS_BOMB, Chip.BONUS_4, Chip.BONUS_5][Utils.RandomRangeInt(0, 2)]);
                                break
                            }
                        }
                    }
                    this.moves <= 0 && this.lose()
                }
            } catch (s) {
                this.inputState = this.INPUT_STATE_WAIT_SELECTION
            }
        }, 
        void PlayState::takeStockMatch(e) {
            var n = e.getIndexX(),
                r = e.getIndexY();
            this.field[n][r] == e && this.goal == t.GOAL_COUNT && e.getColorID() == this.goalChipID && (this.chipGoalCount--, this.chipGoalCount <= 0 && (this.chipGoalCount = 0, this.win()), this.goalLabel.setText(this.chipGoalCount.toString()))
        }, 
        void PlayState::clearCell(e) {
            var n = e.getIndexX(),
                r = e.getIndexY();
            this.field[n][r] == e && (this.goal == t.GOAL_COUNT && e.getColorID() == this.goalChipID && (this.chipGoalCount--, this.chipGoalCount <= 0 && (this.chipGoalCount = 0, this.win()), this.goalLabel.setText(this.chipGoalCount.toString())), (e.getMatchReason() == Chip.MATCH_REASON_BONUS_EFFECT_5 || e.getMatchReason() == Chip.MATCH_REASON_BONUS_EFFECT_4_HOR || e.getMatchReason() == Chip.MATCH_REASON_BONUS_EFFECT_4_VERT) && this.runParticleEffect(e.x, e.y - Constants.CELL_SIZE / 2), this.field[n][r] = null), this.tryClearDirt(n, r), e.isStoneHeart() || this.tryClearStoneHeart(n, r)
        }, 
        void PlayState::tryClearDirt(e, n) {
            var r = this.fieldDirt[e][n];
            r && (createjs.Tween.get(r, {
                loop: !1
            }).to({
                alpha: 0
            }, 250, createjs.Ease.linear), this.fieldDirt[e][n] = null, --this.dirtCount == 0 && this.win()), this.goal == t.GOAL_DIRT && this.goalLabel.setText(this.dirtCount.toString())
        }, 
        void PlayState::tryClearStoneHeart(e, t) {
            try {
                var n;
                n = this.getChipAt(e + 1, t), n && n.isStoneHeart() && n.fallDown(), n = this.getChipAt(e - 1, t), n && n.isStoneHeart() && n.fallDown(), n = this.getChipAt(e, t + 1), n && n.isStoneHeart() && n.fallDown(), n = this.getChipAt(e, t - 1), n && n.isStoneHeart() && n.fallDown()
            } catch (r) {}
        }, 
        void PlayState::finishLevel() {
            for (var e = 0; e < this.fieldWidth; e++)
                for (var t = 0; t < this.fieldHeight; t++) this.field[e][t] != null && this.field[e][t].isNormal() && this.field[e][t].fallDown()
        }, 
        void PlayState::lose() {
            this.waitLose || (this.waitLose = !0, this.addGameObjectAt(new TimeIsUpEffect(Constants.IMAGE_OUT_OF_MOVES), this), SoundManager.g_instance.play(SoundManager.SOUND_LOSE))
        }, 
        void PlayState::win() {
            this.waitWin || (this.waitWin = !0, SoundManager.g_instance.play(SoundManager.SOUND_WIN))
        }, 
        void PlayState::addPointsAt(e, t) {
            if (e.getBonusType() == null) {
                var n = 40;
                switch (t) {
                    case Chip.MATCH_REASON_EXCHANGE_WIHT_BONUS:
                        n = 40;
                        break;
                    case Chip.MATCH_REASON_BONUS_EFFECT_5:
                        n = 100;
                        break;
                    case Chip.MATCH_REASON_BONUS_EFFECT_4_HOR:
                        n = 90;
                        break;
                    case Chip.MATCH_REASON_BONUS_EFFECT_4_VERT:
                        n = 120;
                        break;
                    case Chip.MATCH_REASON_I_AM_BONUS:
                        n = 150;
                        break;
                    default:
                        n = 40 + this.matchInARow * 20
                }
                var r = new FlyingPoints(n);
                this.score += n;
                var i = e.x - Constants.CELL_SIZE / 2,
                    s = e.y - Constants.CELL_SIZE / 2;
                this.tryShowAwesome(i, s), this.tryShowSuperb(i, s), this.addGameObjectAtPos(r, this, i, s)
            }
        }, 
        void PlayState::tryShowSuperb(e, t) {
            if (this.matchInARow >= 3 && this.superbEffectTime != this.liveTime) {
                this.superbEffectTime = this.liveTime;
                var n = new SuperbEffect;
                return this.addGameObjectAtPos(n, this, e, t), SoundManager.g_instance.play(SoundManager.SOUND_AWESOME), n.x < 120 && (n.x = 120), n.x > Constants.ASSETS_WIDTH - 120 && (n.x = Constants.ASSETS_WIDTH - 120), this.score += 500, !0
            }
            return !1
        }, 
        void PlayState::tryShowAwesome(e, t) {
            if (this.matchInARow == 2 && this.awesomeEffectTime != this.liveTime) {
                this.awesomeEffectTime = this.liveTime;
                var n = new ShowAwesomeEffect;
                return this.addGameObjectAtPos(n, this, e, t), SoundManager.g_instance.play(SoundManager.SOUND_AWESOME), n.x < 120 && (n.x = 120), n.x > Constants.ASSETS_WIDTH - 120 && (n.x = Constants.ASSETS_WIDTH - 120), this.score += 200, !0
            }
            return !1
        }, 
        void PlayState::findMoves() {
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
                for (var r = 0; r < this.fieldHeight; r++)
                    for (var i = 0; i < this.fieldWidth - 1; i++)
                        if (this.field[i][r].getColorID() == this.field[i + 1][r].getColorID()) {
                            if (this.findPattern(i, r, this.field[i][r].getColorID(), e, i + 2, r)) return !0;
                            if (this.findPattern(i, r, this.field[i][r].getColorID(), t, i - 1, r)) return !0
                        }
                for (var r = 0; r < this.fieldHeight; r++)
                    for (var i = 0; i < this.fieldWidth - 2; i++)
                        if (this.field[i][r].getColorID() == this.field[i + 2][r].getColorID() && this.findPattern(i, r, this.field[i][r].getColorID(), n, i + 1, r)) return !0;
                var s = [
                        [-1, 2],
                        [0, 3],
                        [1, 2]
                    ],
                    o = [
                        [-1, -1],
                        [0, -2],
                        [1, -1]
                    ],
                    u = [
                        [-1, 1],
                        [1, 1]
                    ];
                for (var r = 0; r < this.fieldHeight - 1; r++)
                    for (var i = 0; i < this.fieldWidth; i++)
                        if (this.field[i][r].getColorID() == this.field[i][r + 1].getColorID()) {
                            if (this.findPattern(i, r, this.field[i][r].getColorID(), s, i, r + 2)) return !0;
                            if (this.findPattern(i, r, this.field[i][r].getColorID(), o, i, r - 1)) return !0
                        }
                for (var r = 0; r < this.fieldHeight - 2; r++)
                    for (var i = 0; i < this.fieldWidth; i++)
                        if (this.field[i][r].getColorID() == this.field[i][r + 2].getColorID() && this.findPattern(i, r, this.field[i][r].getColorID(), u, i, r + 1)) return !0
            } catch (a) {
                return console.log(a, "playstate::findmoves"), !1
            }
            return !1
        }, 
        void PlayState::findPattern(e, t, n, r, i, s) {
            if (n <= 0) return !1;
            if (i < 0 || i >= this.fieldWidth || s < 0 || s >= this.fieldHeight) return !1;
            if (this.field[i][s] && this.field[i][s].isHole()) return !1;
            for (var o = 0; o < r.length; o++) {
                var u = this.getColorAt(e + r[o][0], t + r[o][1]);
                if (u <= 0) continue;
                if (u == n) return this.findedMatchPos1 = new createjs.Point(i, s), this.findedMatchPos2 = new createjs.Point(e + r[o][0], t + r[o][1]), !0
            }
            return !1
        }, 
        void PlayState::setHintIndeces(e, t, n, r) {
            this.findedMatchPos1 = new createjs.Point(e, t), this.findedMatchPos2 = new createjs.Point(n, r)
        }, 
        void PlayState::getChipAt(e, t) {
            return e < 0 || t < 0 || e >= this.fieldWidth || t >= this.fieldHeight || !this.field[e][t] || this.field[e][t].isHole() ? null : this.field[e][t]
        }, 
        void PlayState::getColorAt(e, t) {
            return e < 0 || t < 0 || e >= this.fieldWidth || t >= this.fieldHeight || !this.field[e][t] == null ? -1 : this.field[e][t].getColorID()
        }, 
        void PlayState::onShiftEnded() {
            if (this.liveTime != this.lastDropSoundTime) {
                this.lastDropSoundTime = this.liveTime;
                var e = Utils.RandomRangeInt(0, 2);
                for (var t = 0; e == this.lastDropID && t < 10; t++) e = Utils.RandomRangeInt(0, 2);
                this.lastDropID = e;
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
        }, 
        void PlayState::configureYAlign() {
            if (Constants.SCREEN_HEIGHT < Constants.ASSETS_HEIGHT) this.y = Constants.SCREEN_HEIGHT - Constants.ASSETS_HEIGHT;
            else if (Constants.SCREEN_HEIGHT > Constants.ASSETS_HEIGHT) {
                this.y = (Constants.SCREEN_HEIGHT - Constants.ASSETS_HEIGHT) / 2;
                var e = new createjs.Shape;
                e.graphics.beginFill("#b5389c"), e.graphics.drawRect(0, Constants.ASSETS_HEIGHT, Constants.ASSETS_WIDTH, Constants.SCREEN_HEIGHT - Constants.ASSETS_HEIGHT + 1), e.graphics.endFill(), this.addChild(e);
                var t = new createjs.Shape;
                t.graphics.beginFill("#b5389c"), t.graphics.drawRect(0, Constants.ASSETS_HEIGHT - Constants.SCREEN_HEIGHT, Constants.ASSETS_WIDTH, Constants.SCREEN_HEIGHT - Constants.ASSETS_HEIGHT), t.graphics.endFill(), this.addChild(t)
            }
        }, 
        void PlayState::runParticleEffect(e, t) {
            var n = 80,
                r = Utils.RandomRangeInt(3, 4);
            for (var i = 0; i < r; i++) {
                var s = Utils.RadToGrad(Utils.RandomRange(0, 360)),
                    o = new HeartParticle(Math.cos(s) * n, Math.sin(s) * n);
                this.addGameObject(o), this.addChild(o), o.x = e + Utils.RandomRange(-Constants.CELL_SIZE / 3, Constants.CELL_SIZE / 3), o.y = t + Utils.RandomRange(-Constants.CELL_SIZE / 3, Constants.CELL_SIZE / 3)
            }
        }, 
        t.g_curLevel = -1, 
        t.GOAL_DIRT = "GOAL_DIRT", 
        t.GOAL_COUNT = "GOAL_COUNT"
}   
    