// TODO lihua
public class GameState extends createjs.Container {
        public void GameState() {
            this.liveTime = 0, 
            this.gameObjects = new Array, 
            this.gui = new Array, 
            this.newGameObjects = new Array, 
            this.initiliazed = !1, 
            this.consoleH = 200
        }
 
        public consolePrint(e) {
            var t = new createjs.Text(e, "bold 35px Arial", "#000000");
            this.addChild(t); 
            t.x = 50; 
            t.y = this.consoleH;
            this.consoleH += 40;
        }
        public isInitiliazed() {
            return this.initiliazed;
        }
        public onMouseDown(e, t) {
            for (var n = 0; n < this.gui.length; n++) this.gui[n].onMouseDown(e, t)
        }
        public onMouseMove(e, t) {
            for (var n = 0; n < this.gui.length; n++) this.gui[n].onMouseMove(e, t)
        }
        public onMouseUp(e, t) {
            for (var n = 0; n < this.gui.length; n++) this.gui[n].onMouseUp(e, t)
        }
        public addGuiObject(e) {
            this.gui.push(e);
            this.addGameObject(e);
        }
        public update(e) {
            this.liveTime += e; 
            this.newGameObjects = new Array;
            for (var t = 0; t < this.gameObjects.length; t++) {
                var n = this.gameObjects[t];
                n.update(e);
                n.isDead() ? n.onDead() : this.newGameObjects.push(n);
            }
            this.gameObjects = this.newGameObjects
        }
        public addGameObject(e) {
            this.gameObjects.push(e);
        }
        public addGameObjectAt(e, t) {
            this.gameObjects.push(e);
            t && t.addChild(e);
        }
        public addGameObjectAtPos(e, t, n, r) {
            this.gameObjects.push(e);
            t && (t.addChild(e), e.x = n, e.y = r);
        } 
        public cleanup() {}, 
        public resume() {}, 
        public init() {
            this.initiliazed = !0
        }
        public onOrientationChanged(e) {
            //e && StateManager.g_instance.pushState(new PortraitLockState)//横屏竖屏
        }
}