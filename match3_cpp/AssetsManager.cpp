public class AssetsManager extends createjs.Container {

        public AssetsManager(n) {
            this.maxWidth = 100;
            this.deltaY = 50;
            this.gameplaySprites = null;
            this.mainMenuSprites = null;

            this.maxWidth = 300; 
            this.manifest = n;
        }
        public startDownLoad() {
        }
 
        public handleComplete(e) {
            //
        }
        
        public getResult(e) {
            return this.loader.getResult(e)
        }

        public getBitmap(e) {
            return new createjs.Bitmap(this.loader.getResult(e))
        }

        public getCenteredBitmap(e) {
            var t = new createjs.Bitmap(this.loader.getResult(e));
            t.image || console.log("ERROR HERE", e); 
            t.x = -t.image.width / 2, 
            t.y = -t.image.height / 2, 
            return t;
        }

        public getImage(e) {
            var t = this.getBitmap(e);
            if (t.getBounds()) return t;
            var n = this.getSprite(e);
            return n.getBounds() ? n : null
        }

        public getCenteredImage(e) {
            var t = this.getImage(e);
            return t.x = -t.getBounds().width / 2, t.y = -t.getBounds().height / 2, t
        }

        public getCenteredImageWithProxy(e) {
            var t = new createjs.Container;
            return t.addChild(this.getCenteredImage(e)), t
        }

        public getCenteredBitmapWithProxy(e) {
            var t = new createjs.Container;
            return t.addChild(this.getCenteredBitmap(e)), t
        }
        public getSprite(e) {
            var t = new createjs.Sprite(this.gameplaySprites, e);
            return t.stop(), t
        }
        
        public getCenteredSprite(e) {
            var t = this.getSprite(e);
            t.x = -t.getBounds().width / 2; 
            t.y = -t.getBounds().height / 2;
            return t;
        }
        
        public onOrientationChanged(e) {
            //
        }
}