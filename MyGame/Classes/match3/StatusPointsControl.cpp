public class StatusPointsControl extends createjs.Container {
        public StatusPointsControl(t, n) {
            e.call(this), 
            this.smallPoints = new Array, 
            this.offset = 50;
            var r = this.offset * (t - 1);
            for (var i = 0; i < t; i++) {
                var s = AssetsManager.g_instance.getCenteredImageWithProxy(Constants.IMAGE_POINTS_CONTROL_SMALL);
                this.smallPoints.push(s), 
                this.addChild(s), 
                s.x = i * this.offset - r / 2
            }
            
            this.bigPoint = AssetsManager.g_instance.getCenteredImageWithProxy(Constants.IMAGE_POINTS_CONTROL_BIG), 
            this.addChild(this.bigPoint), 
            this.forcedSetActiveElement(n)
        }
        
        t.prototype.setActiveElement = function(e) {
            if (!(this.curElement != e && e >= 0 && e < this.smallPoints.length)) return;
            this.bigPoint.scaleX = this.bigPoint.scaleY = .5;
            for (var t = 0; t < this.smallPoints.length; t++) this.smallPoints[t].visible = !0;
            this.curElement = e, 
            this.curElement < 0 && (this.curElement = 0), 
            this.curElement > this.smallPoints.length - 1 && (this.curElement = this.smallPoints.length - 1), 
            this.smallPoints[this.curElement].visible = !1, 
            this.bigPoint.x = this.smallPoints[this.curElement].x, 
            this.bigPoint.y = this.smallPoints[this.curElement].y, 
            this.bigPoint.scaleX = this.bigPoint.scaleY = .5, 
            createjs.Tween.get(this.bigPoint, {
                loop: !1
            }).to({
                scaleX: 1,
                scaleY: 1
            }, 300, createjs.Ease.backOut)
        }, 
        t.prototype.forcedSetActiveElement = function(e) {
            this.setActiveElement(e), this.bigPoint.scaleX = this.bigPoint.scaleY = 1
        }, 
        t.prototype.getActiveElement = function() {
            return this.curElement
        }
}