
    
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
    