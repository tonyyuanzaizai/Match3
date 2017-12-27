
public DNButton extends GameObject {
        public DNButton(t, n) {
            e.call(this), 
            this.selected = !1, 
            this.func = null, 
            this.func = n, 
            this.picture = AssetsManager.g_instance.getCenteredImage(t), 
            this.addChild(this.picture), 
            this.picWidth = this.picture.getBounds().width * 1.15, 
            this.picHeight = this.picture.getBounds().height * 1.15
        }

        t.prototype.select = function() {
            this.selected || (createjs.Tween.removeTweens(this), createjs.Tween.get(this, {
                loop: !1
            }).to({
                scaleX: 1.15,
                scaleY: 1.15
            }, 150, createjs.Ease.linear), this.selected = !0)
        }, 
        t.prototype.deselect = function() {
            this.selected && (createjs.Tween.removeTweens(this), createjs.Tween.get(this, {
                loop: !1
            }).to({
                scaleX: 1,
                scaleY: 1
            }, 150, createjs.Ease.linear), this.selected = !1)
        }, 
        t.prototype.onMouseDown = function(e, n) {
            if (this.hitTestSmart(e, n)) {
                if (!!t.wasActionThisFrame) return;
                t.wasActionThisFrame = !0, this.liveTime = 0, this.select()
            }
        }, 
        t.prototype.onMouseUp = function(e, n) {
            if (this.hitTestSmart(e, n) && this.selected) {
                if (!!t.wasActionThisFrame) return;
                t.wasActionThisFrame = !0, SoundManager.g_instance.play(SoundManager.SOUND_CLICK), this.runFunc()
            }
            this.deselect()
        }, 
        t.prototype.runFunc = function() {
            this.func ? this.func() : console.log("error! DNButton without func")
        }, 
        t.prototype.onMouseMove = function(e, n) {
            if (!this.hitTestSmart(e, n)) {
                if (!!t.wasActionThisFrame) return;
                t.wasActionThisFrame = !0, this.deselect()
            }
        }, 
        t.prototype.hitTestSmart = function(e, t) {
            if (!this.parent || !this.visible) return !1;
            var n = this.localToGlobal(0, 0);
            return n.x /= Constants.SCREEN_SCALE, n.y /= Constants.SCREEN_SCALE, e > n.x - this.picWidth / 2 && e < n.x + this.picWidth / 2 && t > n.y - this.picHeight / 2 && t < n.y + this.picHeight / 2
        }, 
        t.wasActionThisFrame = !1;//静态全局变量
}

public DNTextField extends createjs.Container {
        public DNTextField(t, n, r) {
            e.call(this), 
            this.textWidth = 0, 
            this.fontNamePrefix = "", 
            this.letterDistance = 0, 
            n && (this.fontNamePrefix = n), 
            r && (this.letterDistance = r), 
            this.setText(t)
        }
 
        t.prototype.setText = function(e) {
            this.removeAllChildren();
            var t = 0;
            for (var n = 0; n < e.length; n++) {
                var r = e.charAt(n),
                    i = AssetsManager.g_instance.getImage(this.fontNamePrefix + r);
                this.addChild(i), i.x = t, t += i.getBounds().width + this.letterDistance
            }
            this.textWidth = t
        }, 

        t.prototype.getWidth = function() {
            return this.textWidth
        }
}