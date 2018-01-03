
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
            StateManager.g_instance.pushState(new ShadeInCircleState(new PlayState(PlayState.g_curLevel, false)))
        }, 
        t.prototype.onExitTouch = function() {
            StateManager.g_instance.pushState(new ShadeInState(new SelectLevelState))
        }, 
        t.prototype.onNextTouch = function() {
            PlayState.g_curLevel + 1 < GameData.getInstance().levelsAvailable() ? StateManager.g_instance.pushState(new ShadeInState(new PlayState(PlayState.g_curLevel + 1, true))) : StateManager.g_instance.pushState(new ShadeInState(new SelectLevelState))
        }, t
}