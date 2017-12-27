
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

        public select() {
            this.selected || (createjs.Tween.removeTweens(this), createjs.Tween.get(this, {
                loop: !1
            }).to({
                scaleX: 1.15,
                scaleY: 1.15
            }, 150, createjs.Ease.linear), this.selected = !0)
        }, 
        public deselect() {
            this.selected && (createjs.Tween.removeTweens(this), createjs.Tween.get(this, {
                loop: !1
            }).to({
                scaleX: 1,
                scaleY: 1
            }, 150, createjs.Ease.linear), this.selected = !1)
        }, 
        public onMouseDown(e, n) {
            if (this.hitTestSmart(e, n)) {
                if (!!t.wasActionThisFrame) return;
                wasActionThisFrame = !0;
                this.liveTime = 0;
                this.select();
            }
        }, 
        public onMouseUp(e, n) {
            if (this.hitTestSmart(e, n) && this.selected) {
                if (!!wasActionThisFrame) return;
                wasActionThisFrame = !0;
                SoundManager.g_instance.play(SoundManager.SOUND_CLICK);
                this.runFunc();
            }
            this.deselect()
        }, 
        public runFunc = function() {
            this.func ? this.func() : console.log("error! DNButton without func")
        }, 
        public onMouseMove(e, n) {
            if (!this.hitTestSmart(e, n)) {
                if (!!wasActionThisFrame) return;
                wasActionThisFrame = !0, this.deselect()
            }
        }, 
        public hitTestSmart(e, t) {
            if (!this.parent || !this.visible) return !1;
            var n = this.localToGlobal(0, 0);
            return n.x /= Constants.SCREEN_SCALE, n.y /= Constants.SCREEN_SCALE, e > n.x - this.picWidth / 2 && e < n.x + this.picWidth / 2 && t > n.y - this.picHeight / 2 && t < n.y + this.picHeight / 2
        }, 
        private wasActionThisFrame = !1;//静态全局变量
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
 
        public setText(e) {
            this.removeAllChildren();
            var t = 0;
            for (var n = 0; n < e.length; n++) {
                var r = e.charAt(n),
                    i = AssetsManager.g_instance.getImage(this.fontNamePrefix + r);
                this.addChild(i), i.x = t, t += i.getBounds().width + this.letterDistance
            }
            this.textWidth = t
        }, 

        public getWidth() {
            return this.textWidth
        }
}