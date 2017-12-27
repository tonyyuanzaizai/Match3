public class AssetsManager extends createjs.Container {
        function init(n) {
            super.init(n);
            this.loadingShape = new createjs.Shape, 
            this.loadingShapeBack1 = new createjs.Shape, 
            this.loadingShapeBack2 = new createjs.Shape, 
            this.shader = null, 
            this.maxWidth = 100, 
            this.deltaY = 50, 
            this.gameplaySprites = null, 
            this.mainMenuSprites = null, 
         
            this.maxWidth = 300, 
            document.getElementById("loader").className = "loader", 
            createjs.EventDispatcher.initialize(t.prototype), 
            this.manifest = n, 
            this.shader = new createjs.Shape, 
            this.shader.graphics.beginFill("#4aa4c2"), 
            this.shader.graphics.drawRect(0, 0, this.maxWidth * 1.2, 130), 
            this.shader.graphics.endFill(), 
            this.addChild(this.shader), 
            this.labelPercentDownload = new createjs.Text("100%", "bold 45px Arial", "#ffffff"), 
            this.labelPercentDownload.textAlign = "center", 
            this.addChild(this.labelPercentDownload), 
            this.deltaY = this.labelPercentDownload.getBounds().height, 
            this.loadingShapeBack1.graphics.beginFill("#4a7dc2"), 
            this.loadingShapeBack1.graphics.drawRect(-4, -4, this.maxWidth + 8, this.deltaY + 8), 
            this.loadingShapeBack1.graphics.endFill(), 
            this.addChild(this.loadingShapeBack1), 
            this.loadingShape.graphics.beginFill("#ffffff"), 
            this.loadingShape.graphics.drawRect(0, 0, this.maxWidth, this.deltaY), 
            this.loadingShape.graphics.endFill(), 
            this.addChild(this.loadingShape), 
            this.loadingShape.scaleX = 0, 
            this.onOrientationChanged(StateManager.g_instance.isLandscape())
        }
        t.prototype.startDownLoad = function() {
            var e = this;
            this.loader = new createjs.LoadQueue, this.loader.addEventListener("progress", function(t) {
                return e.handleProgress(t)
            }), this.loader.addEventListener("complete", function(t) {
                return e.handleComplete(t)
            }), createjs.Sound.registerManifest(this.manifest, ""), this.loader.installPlugin(createjs.SoundJS), this.loader.loadManifest(this.manifest)
        }, 
        t.prototype.handleProgress = function(e) {
            this.labelPercentDownload.text = (e.loaded * 100).toFixed(1) + "%", this.loadingShape.scaleX = e.loaded
        }, 
        t.prototype.handleComplete = function(e) {
            this.removeChild(this.labelPercentDownload), this.dispatchEvent(Constants.LOAD_COMPLETE, this), document.getElementById("loader").className = ""
        }, 
        t.prototype.getResult = function(e) {
            return this.loader.getResult(e)
        }, 
        t.prototype.getBitmap = function(e) {
            return new createjs.Bitmap(this.loader.getResult(e))
        }, 
        t.prototype.getCenteredBitmap = function(e) {
            var t = new createjs.Bitmap(this.loader.getResult(e));
            return t.image || console.log("ERROR HERE", e), t.x = -t.image.width / 2, t.y = -t.image.height / 2, t
        }, 
        t.prototype.getImage = function(e) {
            var t = this.getBitmap(e);
            if (t.getBounds()) return t;
            var n = this.getSprite(e);
            return n.getBounds() ? n : null
        }, 
        t.prototype.getCenteredImage = function(e) {
            var t = this.getImage(e);
            return t.x = -t.getBounds().width / 2, t.y = -t.getBounds().height / 2, t
        }, 
        t.prototype.getCenteredImageWithProxy = function(e) {
            var t = new createjs.Container;
            return t.addChild(this.getCenteredImage(e)), t
        }, 
        t.prototype.getCenteredBitmapWithProxy = function(e) {
            var t = new createjs.Container;
            return t.addChild(this.getCenteredBitmap(e)), t
        }, 
        t.prototype.getSprite = function(e) {
            var t = new createjs.Sprite(this.gameplaySprites, e);
            return t.stop(), t
        }, 
        t.prototype.getCenteredSprite = function(e) {
            var t = this.getSprite(e);
            return t.x = -t.getBounds().width / 2, t.y = -t.getBounds().height / 2, t
        }, 
        t.prototype.onOrientationChanged = function(e) {
            Constants.g_isPC ? (this.labelPercentDownload.x = Constants.ASSETS_WIDTH / 2, this.labelPercentDownload.y = Constants.ASSETS_HEIGHT / 2) : (this.labelPercentDownload.x = Constants.W / 2 * Constants.PIXEL_RATIO, this.labelPercentDownload.y = Constants.H / 2 * Constants.PIXEL_RATIO), 
            
            this.loadingShape.x = this.labelPercentDownload.x - this.maxWidth / 2, 
            this.loadingShape.y = this.labelPercentDownload.y + this.deltaY * 1.5, 
            this.loadingShapeBack1.x = this.loadingShape.x, 
            this.loadingShapeBack1.y = this.loadingShape.y, 
            this.shader.x = this.labelPercentDownload.x - this.maxWidth * .6, 
            this.shader.y = this.labelPercentDownload.y
        } 
        
}