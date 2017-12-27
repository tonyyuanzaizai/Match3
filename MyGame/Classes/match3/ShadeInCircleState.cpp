
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
    