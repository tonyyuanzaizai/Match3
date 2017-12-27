//TODO lihua 
public class TaskEffect extends GameObject {
        function TaskEffect(t, n, r) {
            var i = this;
            e.call(this);
            if (t == PlayState.GOAL_DIRT) {
                var s = AssetsManager.g_instance.getCenteredImageWithProxy(Constants.IMAGE_TASK_PANEL);
                this.addChild(s);
                var o = new createjs.Text(StringManager.getInstance().getString(StringManager.STRING_CLEAR), "bold 33px Times New Roman", "#6f6aa4");
                o.textAlign = "center", 
                o.y = -23, 
                s.addChild(o)
            } else {
                var s = AssetsManager.g_instance.getCenteredImageWithProxy(Constants.IMAGE_TASK_PANEL);
                this.addChild(s);
                var o = new createjs.Text(StringManager.getInstance().getString(StringManager.STRING_REMOVE), "bold 33px Times New Roman", "#6f6aa4");
                o.textAlign = "right", 
                o.y = -23, 
                s.addChild(o);
                var u = new DNTextField(n.toString(), "font_", -3);
                s.addChild(u), 
                u.x = 10, 
                u.y = -20;
                var a = AssetsManager.g_instance.getCenteredImageWithProxy("cake_" + r);
                a.scaleX = a.scaleY = .7, 
                s.addChild(a), 
                a.x = 92, 
                a.y = -2
            }
            this.y = -200, 
            this.x = Constants.ASSETS_WIDTH * .5, 
            this.alpha = 0, 
            
            createjs.Tween.get(this, {
                loop: !1
            }).wait(1300).to({
                y: Constants.ASSETS_HEIGHT * .5,
                alpha: 1
            }, 650, createjs.Ease.backOut).wait(2200).to({
                y: Constants.ASSETS_HEIGHT + 200,
                alpha: 0
            }, 400, createjs.Ease.backIn).call(function() {
                return i.kill()
            })
        }
        return __extends(t, e), t
}
    
public class  ConvertToBonusEffect extends GameObject {
        function ConvertToBonusEffect(t) {
            e.call(this), 
            this.chip = t, 
            this.addChild(AssetsManager.g_instance.getCenteredImage(Constants.IMAGE_SHINING)), 
            this.scaleX = this.scaleY = 2.5
        }

        t.prototype.update = function(t) {
            e.prototype.update.call(this, t), 
            this.rotation += t * Math.PI * 35, 
            this.scaleX > 1 && (this.scaleX -= t * 3, this.scaleY -= t * 3), 
            this.chip.isMatching() && (this.alpha -= t * 4), 
            this.x = this.chip.x, 
            this.y = this.chip.y - Constants.CELL_SIZE / 2, 
            this.chip.isDead() && this.kill()
        }
}
    
public class KillLineEffect extends GameObject {
        function t(t) {
            e.call(this), this.speed = t, this.addChild(AssetsManager.g_instance.getCenteredImage(Constants.IMAGE_SICKLE)), t.x < 0 && (this.rotation = 180), t.x > 0 && (this.rotation = 0), t.y < 0 && (this.rotation = -90), t.y > 0 && (this.rotation = 90)
        }
        return __extends(t, e), t.prototype.update = function(t) {
            e.prototype.update.call(this, t), this.x += t * this.speed.x, this.y += t * this.speed.y, this.x > Constants.ASSETS_WIDTH + 86 && this.kill(), this.x < -86 && this.kill(), this.y < 300 && this.speed.y < 0 && (this.alpha -= t * 6), this.y < -53 && this.kill(), this.y > Constants.SCREEN_HEIGHT + 53 && this.kill()
        }, t
}

public class KillColorEffect extends GameObject {
        function t(t, n) {
            e.call(this);
            var r = 2e3;
            this.addChild(AssetsManager.g_instance.getCenteredImage(Constants.IMAGE_DROP));
            var i = new createjs.Point(n.x - t.x, n.y - t.y);
            this.distance = Math.sqrt(i.x * i.x + i.y * i.y), this.maxTime = this.distance / r;
            var s = i.x / this.distance;
            this.speed = new createjs.Point(i.x / this.distance * r, i.y / this.distance * r), this.rotation = Utils.RadToGrad(Math.atan2(i.y, i.x))
        }
        return __extends(t, e), t.prototype.update = function(t) {
            e.prototype.update.call(this, t), this.liveTime < this.maxTime ? (this.x += t * this.speed.x, this.y += t * this.speed.y) : (this.alpha -= t * 3.5, this.alpha <= 0 && this.kill())
        }, t
}
    
public class TimeIsUpEffect extends GameObject {
        function t(t) {
            e.call(this), this.stage = 0, this.addChild(AssetsManager.g_instance.getCenteredImage(t)), this.x = 350, this.y = 400, this.setScale(0), this.alpha = -1
        }
        return __extends(t, e), t.prototype.update = function(t) {
            e.prototype.update.call(this, t);
            switch (this.stage) {
                case 0:
                    this.alpha += t * 4, this.setScale(this.scaleX + t * 2), this.scaleX > 1 && (this.setScale(1), this.alpha = 1, this.liveTime = 0, this.stage = 1, createjs.Tween.get(this, {
                        loop: !1
                    }).wait(1400).to({
                        alpha: 0
                    }, 500, createjs.Ease.linear));
                    break;
                case 1:
                    this.setScale(1 + Math.sin(this.liveTime * 5) * .07)
            }
        }, t.prototype.setScale = function(e) {
            this.scaleX = this.scaleY = e
        }, t
}

public class ShowAwesomeEffect extends GameObject {
        function t() {
            e.call(this), this.addChild(AssetsManager.g_instance.getCenteredImage(Constants.IMAGE_AWESOME)), this.alpha = 0, createjs.Tween.get(this, {
                loop: !1
            }).to({
                alpha: 1
            }, 300, createjs.Ease.linear), this.scaleX = this.scaleY = .5, createjs.Tween.get(this, {
                loop: !1
            }).to({
                scaleX: 1,
                scaleY: 1
            }, 500, createjs.Ease.backOut)
        }
        return __extends(t, e), t.prototype.update = function(t) {
            e.prototype.update.call(this, t), this.liveTime > .7 && (this.alpha -= t * 3, this.scaleX += t, this.scaleY += t, this.alpha <= 0 && this.kill())
        }, t
}

public class SuperbEffect extends GameObject {
        function t() {
            e.call(this), this.addChild(AssetsManager.g_instance.getCenteredImage(Constants.IMAGE_SUPERB)), this.alpha = 0, createjs.Tween.get(this, {
                loop: !1
            }).to({
                alpha: 1
            }, 300, createjs.Ease.linear), this.scaleX = this.scaleY = .5, createjs.Tween.get(this, {
                loop: !1
            }).to({
                scaleX: 1,
                scaleY: 1
            }, 500, createjs.Ease.backOut)
        }
        return __extends(t, e), t.prototype.update = function(t) {
            e.prototype.update.call(this, t), this.liveTime > .7 && (this.alpha -= t * 3, this.scaleX += t, this.scaleY += t, this.alpha <= 0 && this.kill())
        }, t
}
    
public class AutoreleaseEffect extends GameObject {
        function t() {
            e.call(this), this.frames = new Array, this.frame = 0;
            for (var t = 1; t <= 11; t++) this.frames.push(AssetsManager.g_instance.getCenteredImageWithProxy("boom_" + t));
            this.update(10)
        }
        return __extends(t, e), t.prototype.update = function(t) {
            e.prototype.update.call(this, t);
            if (this.liveTime > .045) {
                this.liveTime = 0, this.frame++, this.frame >= this.frames.length && (this.frame = this.frames.length - 1, this.kill()), this.removeAllChildren();
                var n = this.frames[this.frame];
                this.addChild(n), n.y = -19, this.scaleX = this.scaleY = 2
            }
        }, t
}
    
    
    
public class FlyingPoints extends GameObject {
        function t(t) {
            e.call(this), this.label = new DNTextField("p" + t.toString(), "", -10), this.addChild(this.label)
        }
        return __extends(t, e), t.prototype.update = function(t) {
            e.prototype.update.call(this, t), this.y -= t * 150, this.liveTime > .5 && (this.alpha -= t * 3.5), this.liveTime >= 1.5 && this.kill()
        }, t
}
    
    
public class HeartParticle extends GameObject {
        function HeartParticle(t, n) {
            e.call(this), 
            this.rotSpeed = Utils.RandomRange(-120, 120), 
            this.speedX = t, 
            this.speedY = n, 
            this.addChild(AssetsManager.g_instance.getCenteredImage(Constants.IMAGE_HEART_PARTICLE)), 
            this.alpha = 0
        }
        
        t.prototype.update = function(t) {
            e.prototype.update.call(this, t), 
            this.rotation += this.rotSpeed * t,
            this.x += this.speedX * t, 
            this.y += this.speedY * t, 
            this.liveTime > .3 ? (this.alpha -= t * 3, this.alpha <= 0 && this.kill()) : this.alpha += t * 4
        }
}
    
    
public class MoveHint extends GameObject {
        function MoveHint(t) {
            e.call(this), 
            this.arrow1 = new createjs.Container, 
            this.arrow2 = new createjs.Container, 
            this.hidding = !1;
            var n = AssetsManager.g_instance.getCenteredImage(Constants.IMAGE_HINT_ARROW);
            this.arrow1.addChild(n), 
            this.addChild(this.arrow1), 
            this.arrow1.y -= 18;
            var r = AssetsManager.g_instance.getCenteredImage(Constants.IMAGE_HINT_ARROW);
            this.arrow2.addChild(r), 
            this.addChild(this.arrow2), 
            this.arrow2.y += 18, 
            this.arrow2.rotation = 180, 
            t && (this.rotation = 90), 
            this.alpha = 0
        }
        
        t.prototype.update = function(t) {
            this.liveTime <= .5 && (this.alpha = this.liveTime * 2), 
            e.prototype.update.call(this, t), 
            this.arrow1.x = Math.sin(this.liveTime * 7) * 5, 
            this.arrow2.x = -this.arrow1.x, 
            this.liveTime > 20 && this.hide(), 
            this.hidding && (this.alpha -= t * 3, this.alpha <= 0 && this.kill())
        }, 
        t.prototype.hide = function() {
            this.hidding = !0
        }
}
    