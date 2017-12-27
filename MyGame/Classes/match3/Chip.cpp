
//三消元素 实体类 TODO lihua
public class Chip extends GameObject {
        public Chip(n, r, i, s, o) {
            e.call(this), 
            this.STATE_NORMAL = "STATE_NORMAL", 
            this.STATE_EXCHANGE = "STATE_EXCHANGE", 
            this.STATE_SHIFT_DOWN = "STATE_SHIFT_DOWN", 
            this.STATE_MATCH = "STATE_MATCH", 
            this.wasClear = !1, 
            this.state = null, 
            this.rotationSpeed = 0, 
            this.selected = !1, 
            this.stateTime = 0, 
            this.rotationTimeOffset = Utils.RandomRange(0, 20), 
            this.bonusType = null, 
            this.jellyAnim = !1, 
            this.doubleMatched = !1, 
            this.canBeMatched = !0, 
            this.matchReason = null, 
            this.hole = !1, 
            this.stoneHeart = !1, 
            this.spawnYPos = s, 
            this.setIncexes(r, i), 
            n != 9 && n != 0 && (this.chipPicture = AssetsManager.g_instance.getImage("cake_" + n), 
            this.addChild(this.chipPicture), 
            this.chipPicture.x = -this.chipPicture.getBounds().width / 2, 
            this.chipPicture.y = -Constants.CELL_SIZE), 
            this.colorID = n, 
            this.setState(t.STATE_SPAWN_NEW), 
            this.spawnDelay = o, 
            n == 9 && this.convertToStoneHeart()
        }

        t.prototype.getMatchReason = function() {
            return this.matchReason
        }, 
        t.prototype.isHorizontal = function() {
            return this.horizontal
        }, 
        t.prototype.getBonusType = function() {
            return this.bonusType
        }, 
        t.prototype.getColorID = function() {
            return this.colorID
        }, 
        t.prototype.getIndeces = function() {
            return new createjs.Point(this.indexX, this.indexY)
        }, 
        t.prototype.getIndexX = function() {
            return this.indexX
        }, 
        t.prototype.getIndexY = function() {
            return this.indexY
        }, 
        t.prototype.setIncexes = function(e, t) {
            this.indexX = e, this.indexY = t
        }, 
        t.prototype.isMatching = function() {
            return this.state == this.STATE_MATCH
        }, 
        t.prototype.update = function(e) {
            this.stateTime += e;
            switch (this.state) {
                case this.STATE_NORMAL:
                    if (this.stoneHeart) break;
                    var n = this.stateTime * 9,
                        r = Math.sin(n) * .13;
                    this.scaleX = 1 + r, this.scaleY = 1 - r, n >= Math.PI * 1 && (this.scaleX = this.scaleY = 1), this.canBeMatched = !0;
                    break;
                case this.STATE_EXCHANGE:
                    this.stateTime >= Constants.EXCHANGE_TIME && this.setState(this.STATE_NORMAL);
                    break;
                case t.STATE_SPAWN_NEW:
                    this.spawnDelay -= e, this.spawnDelay < 0 && (this.speed.y += this.acceleration.y * e, this.x += e * this.speed.x, this.y += e * this.speed.y, this.y >= this.spawnYPos && (this.y = this.spawnYPos, this.setState(this.STATE_NORMAL), PlayState.g_instance.onShiftEnded()));
                    break;
                case this.STATE_SHIFT_DOWN:
                    this.speed.y += this.acceleration.y * e, this.x += e * this.speed.x, this.y += e * this.speed.y, this.y >= this.spawnYPos && (this.y = this.spawnYPos, this.setState(this.STATE_NORMAL), PlayState.g_instance.onShiftEnded());
                    break;
                case t.STATE_FALL_DOWN:
                    this.speed.y += this.acceleration.y * e, this.x += e * this.speed.x, this.y += e * this.speed.y, this.rotation += this.rotationSpeed * e, this.y >= 1e3 && this.kill();
                    break;
                case this.STATE_MATCH:
                    this.scaleY = 1 - this.stateTime * 1.5, this.scaleX = 1 + this.stateTime * 1.5, this.alpha = 1 - this.stateTime / Constants.MATCH_TIME, this.stateTime >= Constants.MATCH_TIME / 2 && !this.wasClear && (PlayState.g_instance.addPointsAt(this, this.matchReason), PlayState.g_instance.clearCell(this), this.wasClear = !0), this.stateTime >= Constants.MATCH_TIME && this.kill()
            }
            this.shiningCircle && (this.shiningCircle.rotation += e * 20)
        }, 
        t.prototype.setState = function(e) {
            if (e == this.state) return;
            this.stateTime = 0, this.state = e;
            switch (e) {
                case this.STATE_NORMAL:
                    this.jellyAnim = !0;
                    break;
                case this.STATE_EXCHANGE:
                    break;
                case this.STATE_SHIFT_DOWN:
                    createjs.Tween.get(this, {
                        loop: !1
                    }).to({
                        scaleX: 1,
                        scaleY: 1
                    }, 170, createjs.Ease.linear);
                    break;
                case t.STATE_SPAWN_NEW:
                    this.speed = new createjs.Point(0, 500), this.acceleration = new createjs.Point(0, Constants.GRAVITY_ACC)
            }
        }, 
        t.prototype.exchange = function(e, t) {
            this.deselect(), this.setState(this.STATE_EXCHANGE), this.indexX = e, this.indexY = t
        }, 
        t.prototype.shiftDown = function(e, t) {
            this.speed = new createjs.Point(0, -250), this.deselect(), this.indexY = e, this.spawnYPos = t, this.setState(this.STATE_SHIFT_DOWN)
        }, 
        t.prototype.match = function(e) {
            if (this.stoneHeart) {
                this.fallDown();
                return
            }
            if (this.isHole()) return;
            this.state == this.STATE_MATCH && (this.doubleMatched = !0);
            if (!this.canBeMatched) return;
            this.matchReason = e, this.setState(this.STATE_MATCH)
        }, 
        t.prototype.isDoubleMatched = function() {
            return this.doubleMatched
        }, 
        t.prototype.select = function() {
            this.stateTime = 0, this.jellyAnim = !0, this.selected = !0
        }, 
        t.prototype.deselect = function() {
            this.selected && (this.scaleX = this.scaleY = 1, this.selected = !1)
        }, t.prototype.isNormal = function() {
            return this.state == this.STATE_NORMAL || this.state == t.STATE_HOLE
        }, t.prototype.getState = function() {
            return this.state
        }, t.prototype.isBonus = function() {
            return this.bonusType != null
        }, 
        t.prototype.convertToBonus = function(e, n) {
            this.horizontal = n, this.bonusType = e, this.removeAllChildren();
            if (e == t.BONUS_5) {
                var r = AssetsManager.g_instance.getImage("donut");
                this.addChild(r), r.x = -r.getBounds().width / 2, r.y = -r.getBounds().height
            }
            if (e == t.BONUS_4) {
                var r = AssetsManager.g_instance.getImage(this.horizontal ? Constants.IMAGE_ARROW_BONUS_HOR : Constants.IMAGE_ARROW_BONUS_VERT);
                this.addChild(r), r.x = -r.getBounds().width / 2, r.y = -r.getBounds().height
            }
            if (e == t.BONUS_BOMB) {
                var r = AssetsManager.g_instance.getImage(Constants.IMAGE_BOMB);
                this.addChild(r), r.x = -r.getBounds().width / 2, r.y = -r.getBounds().height
            }
            this.state != t.STATE_SPAWN_NEW && PlayState.g_instance.addConverToBonusEffect(this), 
            this.canBeMatched = !1, 
            PlayState.g_instance.takeStockMatch(this), 
            this.colorID = -1, 
            this.setState(this.STATE_NORMAL), 
            PlayState.g_instance.tryClearDirt(this.indexX, this.indexY), 
            PlayState.g_instance.tryClearStoneHeart(this.indexX, this.indexY)
        }, 
        t.prototype.fallDown = function() {
            if (this.state == t.STATE_FALL_DOWN) return;
            this.setState(t.STATE_FALL_DOWN), 
            this.chipPicture.y = -this.chipPicture.getBounds().height / 2, 
            this.y -= this.chipPicture.getBounds().height / 2, 
            this.speed = new createjs.Point(Utils.RandomRange(-100, 100), -250), 
            this.rotationSpeed = Utils.RandomRange(-300, 300), 
            PlayState.g_instance.addChild(this), 
            this.wasClear || (PlayState.g_instance.clearCell(this), this.wasClear = !0)
        }, 
        t.prototype.isHole = function() {
            return this.hole
        }, 
        t.prototype.convertToHole = function() {
            this.removeAllChildren(), this.hole = !0, this.y = this.spawnYPos, this.setState(t.STATE_HOLE), this.colorID = -1
        }, 
        t.prototype.convertToStoneHeart = function() {
            this.stoneHeart = !0, this.colorID = -1;
            var e = Constants.IMAGE_STONE_HEART;
            this.chipPicture = AssetsManager.g_instance.getImage(e), 
            this.addChild(this.chipPicture), 
            this.chipPicture.x = -this.chipPicture.getBounds().width / 2, 
            this.chipPicture.y = -83
        }, 
        t.prototype.isStoneHeart = function() {
            return this.stoneHeart
        }, 
        t.BONUS_4 = "BONUS_4", 
        t.BONUS_5 = "BONUS_5", 
        t.BONUS_BOMB = "BONUS_BOMB", 
        t.STATE_SPAWN_NEW = "STATE_SPAWN_NEW", 
        t.STATE_FALL_DOWN = "STATE_FALL_DOWN", 
        t.STATE_HOLE = "STATE_HOLE", 
        t.MATCH_REASON_SIMPLE = "MATCH_REASON_SIMPLE", 
        t.MATCH_REASON_EXCHANGE_WIHT_BONUS = "MATCH_REASON_EXCHANGE_WIHT_BONUS", 
        t.MATCH_REASON_BONUS_EFFECT_5 = "MATCH_REASON_BONUS_EFFECT_5", 
        t.MATCH_REASON_BONUS_EFFECT_4_HOR = "MATCH_REASON_BONUS_EFFECT_4_HOR", 
        t.MATCH_REASON_BONUS_EFFECT_4_VERT = "MATCH_REASON_BONUS_EFFECT_4_VERT", 
        t.MATCH_REASON_I_AM_BONUS = "MATCH_REASON_I_AM_BONUS"
}