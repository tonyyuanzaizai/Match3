public class GameObject extends createjs.Container {
        function GameObject() {
            e.call(this), 
            this.liveTime = 0, 
            this.killed = !1
        }
                
        t.prototype.update = function(e) {
            this.liveTime += e
        }, 
        t.prototype.kill = function() {
            this.killed = !0
        }, 
        t.prototype.isDead = function() {
            return this.killed
        }, 
        t.prototype.onDead = function() {
            this.parent && this.parent.removeChild(this)
        }
}