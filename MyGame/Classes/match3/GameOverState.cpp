
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
