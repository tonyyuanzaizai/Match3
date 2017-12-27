// TODO lihua
public class MainMenuState extends GameState {
        public MainMenuState() {
            this.someThing = true; 
            this.addChild(AssetsManager.g_instance.getImage(Constants.IMAGE_TITLE_MAIN_MENU_BACK));
            
            var n = new createjs.Container;
            this.addChild(n), 
            n.x = Constants.ASSETS_WIDTH / 2, n.y = 690, n.scaleX = n.scaleY = 1.35;
            
            var r = new DNButton(Constants.IMAGE_BUTTON_PLAY, function() {
                console.log("start button pressed"), 
                SG_Hooks.start(), 
                console.log("SG_Hooks triggered!"), 
                t.onPlayTouch()
            });
            n.addChild(r), 
            this.addGuiObject(r);
            
            // Play按钮刚出现时，抖一下
            /**
            createjs.Tween.get(r, {
                loop: !0
            }).to({
                scaleX: 1.05,
                scaleY: 1.05
            }, 150, createjs.Ease.linear).to({
                scaleX: .95,
                scaleY: .95
            }, 300, createjs.Ease.linear).to({
                scaleX: 1,
                scaleY: 1
            }, 150, createjs.Ease.linear).wait(4e3);
            **/
            
            /**
            var i = new DNButton(Constants.IMAGE_BUTTON_MORE_GAMES, function() {
                return t.onMoreGamesTouch()
            });
            this.addChild(i), 
            this.addGuiObject(i), 
            i.x = 150, i.y = 700, 
            this.setSoundButton();
            **/
            
            this.configureYAlign()
        }
        
        public configureYAlign() {
            if (Constants.SCREEN_HEIGHT > Constants.ASSETS_HEIGHT) {
                this.y = (Constants.SCREEN_HEIGHT - Constants.ASSETS_HEIGHT) / 2;
                
                var e = new createjs.Shape;
                e.graphics.beginFill("#ffffff");
                e.graphics.drawRect(0, Constants.ASSETS_HEIGHT, Constants.ASSETS_WIDTH, Constants.SCREEN_HEIGHT - Constants.ASSETS_HEIGHT + 1);
                e.graphics.endFill();
                this.addChild(e);
                
                var t = new createjs.Shape;
                t.graphics.beginFill("#ffffff");
                t.graphics.drawRect(0, Constants.ASSETS_HEIGHT - Constants.SCREEN_HEIGHT, Constants.ASSETS_WIDTH, Constants.SCREEN_HEIGHT - Constants.ASSETS_HEIGHT);
                t.graphics.endFill();
                this.addChild(t);
            }
        }

        public onOrientationChanged(t) {
            e.prototype.onOrientationChanged.call(this, t), t || this.configureYAlign()
        }

        public init() {
            e.prototype.init.call(this)
        }
        
        public runJelly() {
            this.liveTime = 0
        }
        
        public update(t) {
            e.prototype.update.call(this, t)
        }
        
        /**
        private onSoundTouch = function() {
            SoundManager.g_instance.setSoundEnabled(!SoundManager.g_instance.isSoundEnabled()), this.setSoundButton()
        }
        
        private setSoundButton = function() {
            var e = this;
            this.soundButton && this.soundButton.parent && this.soundButton.parent.removeChild(this.soundButton);
            var t = SoundManager.g_instance.isSoundEnabled();
            this.soundButton = new DNButton(t ? Constants.IMAGE_BUTTON_SOUND_ON : Constants.IMAGE_BUTTON_SOUND_OFF, function() {
                return e.onSoundTouch()
            }), this.addChild(this.soundButton), this.addGuiObject(this.soundButton), this.soundButton.x = 620, this.soundButton.y = 150
        }
        **/
        
        public onMouseDown(t, n) {
            e.prototype.onMouseDown.call(this, t, n)
        }
        
        public onCreditsTouch() {
            //StateManager.g_instance.pushState(new CreditsState)//作者信息弹窗
        }
        
        public onMoreGamesTouch() {
            //SG.redirectToPortal()
        }
        
        public onPlayTouch() {
            StateManager.g_instance.pushState(new ShadeInState(new SelectLevelState))
        }
        
        public resume() {
            this.configureYAlign()
        }
}