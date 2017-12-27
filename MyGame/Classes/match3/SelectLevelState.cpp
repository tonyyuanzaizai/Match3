public class SelectLevelButton extends DNButton {
        function SelectLevelButton(t, n, r) {
            e.call(this, t, n), 
            this.locked = !1, 
            this.levelNum = r;
            if (r < GameData.getInstance().levelsAvailable()) {
                var i = new DNTextField((r + 1).toString(), "sel_", -6);
                this.addChild(i);
                var s = .65;
                i.scaleX = i.scaleY = s, 
                i.x = -i.getBounds().width / 2 * s + 5, 
                i.y = -i.getBounds().height / 2 * s - 7
            } else {
                this.locked = !0;
                var o = AssetsManager.g_instance.getCenteredImage(Constants.IMAGE_LOCK);
                o.y -= 5, 
                o.x += 4, 
                this.addChild(o)
            }
        }

        t.prototype.onMouseDown = function(t, n) {
            if (this.locked) return;
            e.prototype.onMouseDown.call(this, t, n), this.touchY = n
        }
        
        t.prototype.onMouseUp = function(t, n) {
            if (Math.abs(n - this.touchY) > 30) {
                this.deselect();
                return
            }
            e.prototype.onMouseUp.call(this, t, n)
        } 

        t.prototype.runFunc = function() {
            StateManager.g_instance.pushState(new ShadeInState(new PlayState(this.levelNum, !0)))
        }
}
    
    
public class SelectLevelState extends GameState {
        function SelectLevelState() {
            var t = this;
            e.call(this), 
            this.touchPointY = 0, 
            this.layer = new createjs.Container, 
            this.tween = null, 
            this.ySpeed = 0, 
            this.yAcc = 1e3, 
            this.calcSpeedCache = 0, 
            this.slidePositions = new Array, 
            this.levelsPositions = [39, 1449, 188, 1445, 365, 1411, 465, 1338, 499, 1235, 385, 1166, 253, 1142, 113, 1086, 40, 968, 119, 851, 263, 818, 403, 800, 541, 750, 505, 630, 346, 578, 193, 548, 64, 480, 55, 352, 186, 303, 330, 348, 488, 350, 571, 252, 537, 137, 411, 87, 266, 85, 124, 97, 43, 10];
            var n = new DNButton(Constants.IMAGE_BUTTON_EXIT, function() {
                return t.onExitTouch()
            });
            this.addGuiObject(n), 
            this.addChild(this.layer);
            var r = AssetsManager.g_instance.getImage(Constants.IMAGE_GLOBAL_MAP);
            this.layer.addChild(r), 
            this.mapH = r.getBounds().height, 
            this.layer.y = -1e3;
            var i = 62,
                s = 200;
            for (var o = 0; o < this.levelsPositions.length / 2; o++) {
                var u = new SelectLevelButton(Constants.IMAGE_LEVEL_BUTTON, function() {}, o);
                this.addGuiObject(u), 
                this.layer.addChild(u), 
                u.x = Constants.ASSETS_WIDTH - (this.levelsPositions[o * 2] + i), 
                u.y = this.levelsPositions[o * 2 + 1] + s
            }
            var a = AssetsManager.g_instance.getImage(Constants.IMAGE_SELECT_LEVEL_BACK);
            this.addChild(a);
            var f = new createjs.Container;
            f.addChild(n), 
            f.x = 68, 
            f.y = 70, 
            f.scaleX = f.scaleY = .9, 
            this.addChild(f), 
            this.checkConstrains()
        }
        public onExitTouch = function() {
            StateManager.g_instance.pushState(new ShadeInState(new MainMenuState))
        }
        
        public onLevelTouch = function(e) {
            StateManager.g_instance.pushState(new ShadeInState(new PlayState(e, !0)))
        } 

        public onMouseDown = function(t, n) {
            e.prototype.onMouseDown.call(this, t, n), this.touchPointY = this.layer.y - n, this.slidePositions.length = 0, this.slidePositions.push({
                liveTime: this.liveTime,
                y: n
            })
        }
        
        public update = function(t) {
            e.prototype.update.call(this, t), 
            StateManager.g_instance.isMouseDownNow() || this.ySpeed != 0 && (this.layer.y += this.ySpeed * t, this.ySpeed > 0 ? (this.ySpeed -= t * this.yAcc, this.ySpeed < 0 && (this.ySpeed = 0)) : (this.ySpeed += t * this.yAcc, this.ySpeed > 0 && (this.ySpeed = 0))), 
            this.checkConstrains()
        }
        
        public onMouseMove = function(t, n) {
            e.prototype.onMouseMove.call(this, t, n), this.layer.y = n + this.touchPointY, this.checkConstrains(), this.slidePositions.push({
                liveTime: this.liveTime,
                y: n
            }), this.slidePositions.length > 100 && (this.calcSpeedCache = this.calcYSpeed(), this.slidePositions.length = 0)
        }
        
        public checkConstrains = function() {
            this.layer.y > 0 && (this.layer.y = 0, this.ySpeed = 0), Constants.g_isPC ? this.layer.y < Constants.ASSETS_HEIGHT - this.mapH && (this.layer.y = Constants.ASSETS_HEIGHT - this.mapH, this.ySpeed = 0) : this.layer.y < Constants.SCREEN_HEIGHT - this.mapH && (this.layer.y = Constants.SCREEN_HEIGHT - this.mapH, this.ySpeed = 0)
        }
        
        public onMouseUp = function(t, n) {
            e.prototype.onMouseUp.call(this, t, n), this.slidePositions.push({
                liveTime: this.liveTime,
                y: n
            }), this.ySpeed = this.calcYSpeed()
        }
        
        public calcYSpeed = function() {
            if (this.slidePositions.length < 2) return this.calcSpeedCache;
            var e = .2,
                t;
            for (t = this.slidePositions.length - 2; t > 0; --t)
                if (this.liveTime - this.slidePositions[t].liveTime >= e) break;
            var n = this.liveTime - this.slidePositions[t].liveTime;
            return n < 1e-5 ? 0 : (this.slidePositions[this.slidePositions.length - 1].y - this.slidePositions[t].y) / n
        }
}