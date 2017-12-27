// TODO lihua
public class GameState extends createjs.Container {
        public void GameState() {
            e.call(this), 
            this.liveTime = 0, 
            this.gameObjects = new Array, 
            this.gui = new Array, 
            this.newGameObjects = new Array, 
            this.initiliazed = !1, 
            this.consoleH = 200
        }
 
        t.prototype.consolePrint = function(e) {
            var t = new createjs.Text(e, "bold 35px Arial", "#000000");
            this.addChild(t), t.x = 50, t.y = this.consoleH, this.consoleH += 40
        }, 
        t.prototype.isInitiliazed = function() {
            return this.initiliazed
        }, 
        t.prototype.onMouseDown = function(e, t) {
            for (var n = 0; n < this.gui.length; n++) this.gui[n].onMouseDown(e, t)
        }, 
        t.prototype.onMouseMove = function(e, t) {
            for (var n = 0; n < this.gui.length; n++) this.gui[n].onMouseMove(e, t)
        }, 
        t.prototype.onMouseUp = function(e, t) {
            for (var n = 0; n < this.gui.length; n++) this.gui[n].onMouseUp(e, t)
        }, 
        t.prototype.addGuiObject = function(e) {
            this.gui.push(e), this.addGameObject(e)
        }, 
        t.prototype.update = function(e) {
            this.liveTime += e, 
            this.newGameObjects = new Array;
            for (var t = 0; t < this.gameObjects.length; t++) {
                var n = this.gameObjects[t];
                n.update(e), 
                n.isDead() ? n.onDead() : this.newGameObjects.push(n)
            }
            this.gameObjects = this.newGameObjects
        }, 
        t.prototype.addGameObject = function(e) {
            this.gameObjects.push(e)
        }, 
        t.prototype.addGameObjectAt = function(e, t) {
            this.gameObjects.push(e), t && t.addChild(e)
        }, 
        t.prototype.addGameObjectAtPos = function(e, t, n, r) {
            this.gameObjects.push(e), t && (t.addChild(e), e.x = n, e.y = r)
        }, 
        t.prototype.cleanup = function() {}, 
        t.prototype.resume = function() {}, 
        t.prototype.init = function() {
            this.initiliazed = !0
        }, 
        t.prototype.onOrientationChanged = function(e) {
            //e && StateManager.g_instance.pushState(new PortraitLockState)//横屏竖屏
        }, t
}