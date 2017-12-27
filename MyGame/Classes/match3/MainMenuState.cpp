// TODO lihua
public class MainMenuState extends GameState {
        public MainMenuState() {
            var t = this;
            e.call(this), 
            this.someThing = !0, 
            this.addChild(AssetsManager.g_instance.getImage(Constants.IMAGE_TITLE_MAIN_MENU_BACK));
            var n = new createjs.Container;
            this.addChild(n), 
            n.x = Constants.ASSETS_WIDTH / 2, n.y = 690, n.scaleX = n.scaleY = 1.35;
            var r = new DNButton(Constants.IMAGE_BUTTON_PLAY, function() {
                console.log("start button pressed"), 
                SG_Hooks.start(), 
                console.log("SG_Hooks triggered!"), 
                t.onPlayTouch()
            });
            n.addChild(r), 
            this.addGuiObject(r), 
            createjs.Tween.get(r, {
                loop: !0
            }).to({
                scaleX: 1.05,
                scaleY: 1.05
            }, 150, createjs.Ease.linear).to({
                scaleX: .95,
                scaleY: .95
            }, 300, createjs.Ease.linear).to({
                scaleX: 1,
                scaleY: 1
            }, 150, createjs.Ease.linear).wait(4e3);
            
            var i = new DNButton(Constants.IMAGE_BUTTON_MORE_GAMES, function() {
                return t.onMoreGamesTouch()
            });
            this.addChild(i), 
            this.addGuiObject(i), 
            i.x = 150, i.y = 700, 
            this.setSoundButton(), 
            this.configureYAlign()
        }
        return __extends(t, e), t.prototype.configureYAlign = function() {
            if (Constants.g_isPC) return;
            if (Constants.SCREEN_HEIGHT > Constants.ASSETS_HEIGHT) {
                this.y = (Constants.SCREEN_HEIGHT - Constants.ASSETS_HEIGHT) / 2;
                var e = new createjs.Shape;
                e.graphics.beginFill("#ffffff"), e.graphics.drawRect(0, Constants.ASSETS_HEIGHT, Constants.ASSETS_WIDTH, Constants.SCREEN_HEIGHT - Constants.ASSETS_HEIGHT + 1), e.graphics.endFill(), this.addChild(e);
                var t = new createjs.Shape;
                t.graphics.beginFill("#ffffff"), t.graphics.drawRect(0, Constants.ASSETS_HEIGHT - Constants.SCREEN_HEIGHT, Constants.ASSETS_WIDTH, Constants.SCREEN_HEIGHT - Constants.ASSETS_HEIGHT), t.graphics.endFill(), this.addChild(t)
            }
        }, t.prototype.onOrientationChanged = function(t) {
            e.prototype.onOrientationChanged.call(this, t), t || this.configureYAlign()
        }, t.prototype.init = function() {
            e.prototype.init.call(this)
        }, t.prototype.runJelly = function() {
            this.liveTime = 0
        }, t.prototype.update = function(t) {
            e.prototype.update.call(this, t)
        }, t.prototype.onSoundTouch = function() {
            SoundManager.g_instance.setSoundEnabled(!SoundManager.g_instance.isSoundEnabled()), this.setSoundButton()
        }, t.prototype.setSoundButton = function() {
            var e = this;
            this.soundButton && this.soundButton.parent && this.soundButton.parent.removeChild(this.soundButton);
            var t = SoundManager.g_instance.isSoundEnabled();
            this.soundButton = new DNButton(t ? Constants.IMAGE_BUTTON_SOUND_ON : Constants.IMAGE_BUTTON_SOUND_OFF, function() {
                return e.onSoundTouch()
            }), this.addChild(this.soundButton), this.addGuiObject(this.soundButton), this.soundButton.x = 620, this.soundButton.y = 150
        }, 
        t.prototype.onMouseDown = function(t, n) {
            e.prototype.onMouseDown.call(this, t, n)
        }, 
        t.prototype.onCreditsTouch = function() {
            //StateManager.g_instance.pushState(new CreditsState)//作者信息弹窗
        }, 
        t.prototype.onMoreGamesTouch = function() {
            //SG.redirectToPortal()
        }, 
        t.prototype.onPlayTouch = function() {
            StateManager.g_instance.pushState(new ShadeInState(new SelectLevelState))
        }, 
        t.prototype.resume = function() {
            this.configureYAlign()
        }
}

public class WinState extends GameState {
        public WinState(t, n) {
            var r = this;
            e.call(this), 
            this.panel = new createjs.Container, 
            this.hiddingNow = !1, 
            GameData.getInstance().onWinLevel(t, n), 
            this.shader = new createjs.Shape, 
            this.shader.graphics.beginFill("#000000"), 
            this.shader.graphics.drawRect(0, 0, Constants.ASSETS_WIDTH, Constants.SCREEN_HEIGHT), 
            this.shader.graphics.endFill(), 
            this.addChild(this.shader), 
            this.shader.alpha = 0, 
            
            this.shaderTween = createjs.Tween.get(this.shader, {
                loop: !1
            }).wait(400).to({
                alpha: .4
            }, 800, createjs.Ease.linear), 
            
            this.addChild(this.panel), 
            this.panel.x = Constants.ASSETS_WIDTH / 2, this.panel.y = Constants.SCREEN_HEIGHT / 2;
            var i = AssetsManager.g_instance.getCenteredImage(Constants.IMAGE_MESSAGE_WINDOW);
            this.panel.addChild(i);
            var s = new DNButton(Constants.IMAGE_BUTTON_RESTART, function() {
                return r.onRestartTouch()
            });
            this.panel.addChild(s), this.addGuiObject(s), s.x = 0, s.y = 125;
            var o = new DNButton(Constants.IMAGE_BUTTON_EXIT, function() {
                return r.onExitTouch()
            });
            this.panel.addChild(o), this.addGuiObject(o), o.x = -150, o.y = 125;
            var u = new DNButton(Constants.IMAGE_BUTTON_PLAY, function() {
                return r.onNextTouch()
            });
            this.panel.addChild(u), 
            this.addGuiObject(u), 
            u.x = 150, 
            u.y = 125;
            var a = AssetsManager.g_instance.getCenteredImageWithProxy(Constants.IMAGE_WIN_CAPTION);
            this.panel.addChild(a), 
            a.y = -270;
            var f = -180,
            l = 180;
            this.panel.alpha = 0, 
            
            createjs.Tween.get(this.panel, {
                loop: !1
            }).to({
                alpha: 1
            }, 200, createjs.Ease.linear), this.panel.scaleX = .7, this.panel.scaleY = .7, createjs.Tween.get(this.panel, {
                loop: !1
            }).to({
                scaleX: 1,
                scaleY: 1
            }, 400, createjs.Ease.backOut);
            
            var c = AssetsManager.g_instance.getImage(Constants.IMAGE_WIN_STRINGS);
            this.panel.addChild(c), c.x = -170, c.y = -120;
            var h = new DNTextField(Utils.GetScoreString(n), "font_", 0);
            this.panel.addChild(h), h.x = -68, h.y = -104, h.scaleX = h.scaleY = 1.15;
            var p = new DNTextField(Utils.GetScoreString(GameData.getInstance().getTotalScore()), "font_", 0);
            this.panel.addChild(p), p.x = -68, p.y = -17, p.scaleX = p.scaleY = 1.15;
            try {
                SG_Hooks.levelUp(t, n)
            } catch (d) {
                console.log("error SG_Hooks.levelUp(level, score);")
            }
        }
        return __extends(t, e), 
        t.prototype.hide = function() {
            this.hiddingNow || (createjs.Tween.get(this.shader, {
                loop: !1
            }).to({
                alpha: 0
            }, 400, createjs.Ease.linear).call(function() {
                StateManager.g_instance.popState()
            }), createjs.Tween.get(this.panel, {
                loop: !1
            }).to({
                y: -300
            }, 300, createjs.Ease.backIn), createjs.Tween.get(this.panel, {
                loop: !1
            }).to({
                alpha: 0
            }, 300, createjs.Ease.linear), this.hiddingNow = !0)
        }, 
        t.prototype.onRestartTouch = function() {
            StateManager.g_instance.pushState(new ShadeInCircleState(new PlayState(PlayState.g_curLevel, !1)))
        }, 
        t.prototype.onExitTouch = function() {
            StateManager.g_instance.pushState(new ShadeInState(new SelectLevelState))
        }, 
        t.prototype.onNextTouch = function() {
            PlayState.g_curLevel + 1 < GameData.getInstance().levelsAvailable() ? StateManager.g_instance.pushState(new ShadeInState(new PlayState(PlayState.g_curLevel + 1, !0))) : StateManager.g_instance.pushState(new ShadeInState(new SelectLevelState))
        }, t
}


public class GameOverState extends GameState {
        public GameOverState(t, n) {
            var r = this;
            e.call(this), this.panel = new createjs.Container, this.shader = new createjs.Shape, this.shader.graphics.beginFill("#000000"), this.shader.graphics.drawRect(0, 0, Constants.ASSETS_WIDTH, Constants.SCREEN_HEIGHT), this.shader.graphics.endFill(), this.addChild(this.shader), this.shader.alpha = 0, this.shaderTween = createjs.Tween.get(this.shader, {
                loop: !1
            }).wait(400).to({
                alpha: .4
            }, 800, createjs.Ease.linear), this.addChild(this.panel), this.panel.x = Constants.ASSETS_WIDTH / 2, this.panel.y = Constants.SCREEN_HEIGHT / 2;
            var i = AssetsManager.g_instance.getCenteredImage(Constants.IMAGE_MESSAGE_WINDOW);
            this.panel.addChild(i);
            var s = new DNButton(Constants.IMAGE_BUTTON_RESTART, function() {
                return r.onRestartTouch()
            });
            this.panel.addChild(s), this.addGuiObject(s), s.x = -110, s.y = 100;
            var o = new DNButton(Constants.IMAGE_BUTTON_EXIT, function() {
                return r.onExitTouch()
            });
            this.panel.addChild(o), this.addGuiObject(o), o.x = 110, o.y = 100;
            var u = AssetsManager.g_instance.getCenteredImageWithProxy(Constants.IMAGE_GAMEOVER_CAPTION);
            this.panel.addChild(u), u.y = -210;
            var a = -180,
                f = 180;
            this.panel.alpha = 0, createjs.Tween.get(this.panel, {
                loop: !1
            }).to({
                alpha: 1
            }, 200, createjs.Ease.linear), this.panel.scaleX = .7, this.panel.scaleY = .7, createjs.Tween.get(this.panel, {
                loop: !1
            }).to({
                scaleX: 1,
                scaleY: 1
            }, 400, createjs.Ease.backOut);
            try {
                SG_Hooks.gameOver(PlayState.g_curLevel, n)
            } catch (l) {
                console.log("error SG_Hooks.gameOver(PlayState.g_curLevel, score);")
            }
        }
 
        t.prototype.onRestartTouch = function() {
            StateManager.g_instance.pushState(new ShadeInCircleState(new PlayState(PlayState.g_curLevel, !1)))
        }, 
        t.prototype.onExitTouch = function() {
            StateManager.g_instance.pushState(new ShadeInState(new MainMenuState))
        }
}

    
public class ShadeInState extends GameState{
        public ShadeInState(t) {
            var n = this;
            e.call(this), 
            this.nextState = null, 
            this.nextState = t, 
            this.shader = new createjs.Shape, 
            this.shader.graphics.beginFill("#ffffff"), 
            this.shader.graphics.drawRect(0, 0, Constants.ASSETS_WIDTH, Constants.SCREEN_HEIGHT), 
            this.shader.graphics.endFill(), 
            this.addChild(this.shader), 
            this.shader.alpha = 0, 
            
            createjs.Tween.get(this.shader, {
                loop: !1
            }).to({
                alpha: 1
            }, 400, createjs.Ease.linear).call(function() {
                return n.onFinishShade()
            })
        }
        
        t.prototype.onFinishShade = function() {
            StateManager.g_instance.changeState(this.nextState), StateManager.g_instance.pushState(new ShadeOutState)
        }, 
        t.prototype.setNextState = function(e) {
            this.nextState = e
        }
}
    
public class ShadeOutState extends GameState {
        public ShadeOutState() {
            var t = this;
            e.call(this), 
            this.shader = new createjs.Shape, 
            this.shader.graphics.beginFill("#ffffff"), 
            this.shader.graphics.drawRect(0, 0, Constants.ASSETS_WIDTH, Constants.SCREEN_HEIGHT), 
            this.shader.graphics.endFill(), 
            this.addChild(this.shader), 
            
            createjs.Tween.get(this.shader, {
                loop: !1
            }).to({
                alpha: 0
            }, 400, createjs.Ease.linear).call(function() {
                return t.onFinishShade()
            })
        }
        
        t.prototype.onFinishShade = function() {
            StateManager.g_instance.popState()
        }
}
    
public class ShadeInCircleState extends GameState {
        public ShadeInCircleState(t) {
            var n = this;
            e.call(this), this.nextState = null, this.nextState = t, this.shader = new createjs.Shape, this.shader.graphics.beginFill("#ffffff"), this.shader.graphics.drawRect(0, 0, Constants.ASSETS_WIDTH, Constants.SCREEN_HEIGHT), this.shader.graphics.endFill(), this.addChild(this.shader), this.shader.alpha = 0, createjs.Tween.get(this.shader, {
                loop: !1
            }).wait(400).to({
                alpha: 1
            }, 400, createjs.Ease.linear).call(function() {
                return n.onFinishShade()
            }), 
            this.shining = AssetsManager.g_instance.getCenteredImageWithProxy(Constants.IMAGE_BIG_SHINING), 
            this.addChild(this.shining), 
            this.shining.x = Constants.ASSETS_WIDTH / 2, 
            this.shining.y = Constants.ASSETS_HEIGHT / 2, 
            
            createjs.Tween.get(this.shining, {
                loop: !1
            }).to({
                scaleX: 3.5,
                scaleY: 3.5
            }, 800, createjs.Ease.linear), this.shining.alpha = 0, createjs.Tween.get(this.shining, {
                loop: !1
            }).to({
                alpha: 1
            }, 400, createjs.Ease.linear), createjs.Tween.get(this.shining, {
                loop: !1
            }).to({
                rotation: 100
            }, 800, createjs.Ease.linear)
        }

        
        t.prototype.onFinishShade = function() {
            StateManager.g_instance.changeState(this.nextState), StateManager.g_instance.pushState(new ShadeOutState)
        }, 
        t.prototype.setNextState = function(e) {
            this.nextState = e
        }, t
}
    