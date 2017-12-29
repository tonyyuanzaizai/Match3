
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