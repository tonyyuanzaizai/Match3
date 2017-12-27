//TODO lihua
public class StateManager {
        public StateManager(t) {
            this.statesConstainer = new createjs.Container, 
            this.isMouseDown = !1; 
            this.timeDevider = 1;
            this.lastTime = 0; 

            this.states = Array(); 
            this.canvas = viewporter.canvas; 
            this.stage = new createjs.Stage(this.canvas);
            this.stage.autoClear = !0; 
            createjs.Touch.enable(this.stage); 
            this.stage.enableMouseOver(5); 
            
            createjs.Ticker.setFPS(60), 
            createjs.Ticker.addEventListener("tick", function(e) {
                return StateManager.this.update(e)
            }), 
            
            var r = new AssetsManager(t);
            this.stage.addChild(r);
            r.startDownLoad();
            this.allAssetsLoaded(e);// show MainMenuState
            
            this.stage.addChild(this.statesConstainer), 
            Constants.PIXEL_RATIO = window.devicePixelRatio ? window.devicePixelRatio : 1; 
            
            window.addEventListener("viewportready", function() {
                return StateManager.this.onOrientationChanged()
            }); 
            window.addEventListener("viewportchange", function() {
                return StateManager.this.onOrientationChanged()
            });
 
            this.onOrientationChanged()
        }
        
        public isLandscape = function() {
            return viewporter.isLandscape()
        } 
        
        public allAssetsLoaded = function(t) {
            this.stage.addEventListener(Constants.MOUSE_MOVE, function(e) {
                return this.handleMouse(e)
            });
            this.stage.addEventListener(Constants.MOUSE_DOWN, function(e) {
                return this.handleMouse(e)
            });
            this.stage.addEventListener(Constants.MOUSE_UP, function(e) {
                return this.handleMouse(e)
            });
            
            StringManager.getInstance().loadStrings();
            try {
                var r = SG.lang;
                StringManager.getInstance().setLanguage(r), 
                
                SG_Hooks.setOrientationHandler(function(t) {
                    e.g_instance.onOrientationChanged()
                }), 
                SG_Hooks.setResizeHandler(function(t, n) {
                    t && n && (Constants.g_wasSetSize = !0, 
                    Constants.W = t, 
                    Constants.H = n, 
                    Constants.g_isPC ? e.g_instance.onResize(null) : e.g_instance.onOrientationChanged())
                })
            } catch (i) {
                console.log("SG_Hooks error")
            }
            
            window.onpagehide && (window.onpagehide = function(e) {
                return StateManager.this.onLostFocus(e)
            });
            window.onblur && (window.onblur = function(e) {
                return StateManager.this.onLostFocus(e)
            });
            window.onpageshow && (window.onpageshow = function(e) {
                return StateManager.this.onFocus(e)
            });
            window.onfocus && (window.onfocus = function(e) {
                return StateManager.this.onFocus(e)
            });
            AssetsManager.g_instance.parent && AssetsManager.g_instance.parent.removeChild(AssetsManager.g_instance);
            GameData.getInstance().load(); 
            this.pushState(new MainMenuState);//show state
            
            //this.isLandscape() && this.pushState(new PortraitLockState);
        }
        
        public update(e) {
            try {
                if (this.states.length != 0) {
                    var t = this.states[this.states.length - 1];
                    t.isInitiliazed() || t.init();
                    var n = createjs.Ticker.getTime(),
                        r = n - this.lastTime;
                    this.lastTime = n, t.update(r * .001 / this.timeDevider)
                }
            } catch (i) {
                console.log(i, "statemanager::update")
            }
            try {
                this.stage.update(e)
            } catch (i) {}
        }
        
        public changeState(e) {
            while (this.states.length != 0) this.popState();
            this.pushState(e)
        }
        
        // 显示此state
        public pushState(e) {
            this.states.push(e);
            this.statesConstainer.addChild(e);
        } 

        public popState() {
            this.states.length != 0 && (this.states[this.states.length - 1].cleanup(), 
            this.statesConstainer.removeChild(this.states[this.states.length - 1]), 
            this.states.pop(), 
            this.states.length != 0 && this.states[this.states.length - 1].resume())
        }
        
        public static getInnerWidth() {
            return Constants.g_isPC ? window.innerWidth : window.innerWidth
        }
        
        public static getInnerHeight() {
            return Constants.g_isPC ? window.innerHeight : window.innerHeight
        }
        
        //for PC
        public onResize(t) {
            //
        }
        
        public onOrientationChanged() {
            Constants.g_wasSetSize || (Constants.W = e.getInnerWidth(), Constants.H = e.getInnerHeight());
            var t = this.isLandscape(),
            n = Constants.W,
            r = Constants.H;
            
            this.canvas.width = n * Constants.PIXEL_RATIO, 
            this.canvas.height = r * Constants.PIXEL_RATIO, 
            this.canvas.style.width = n + "px", 
            this.canvas.style.height = r + "px", t ? (Constants.SCREEN_SCALE = r / Constants.ASSETS_HEIGHT * Constants.PIXEL_RATIO, Constants.SCREEN_HEIGHT = r) : (Constants.SCREEN_SCALE = n / Constants.ASSETS_WIDTH * Constants.PIXEL_RATIO, Constants.SCREEN_HEIGHT = r / Constants.SCREEN_SCALE * Constants.PIXEL_RATIO), this.statesConstainer.scaleX = this.statesConstainer.scaleY = Constants.SCREEN_SCALE, this.states.length != 0 && this.states[this.states.length - 1].onOrientationChanged(t), AssetsManager.g_instance.parent && AssetsManager.g_instance.onOrientationChanged(t)
        }
        
        public onLostFocus(e) {
            SoundManager.g_instance.onLostFocus()
        }
        
        public onFocus(e) {
            SoundManager.g_instance.onFocus()
        }
        
        public isMouseDownNow() {
            return this.isMouseDown
        }
        
        public handleMouse(e) {
            e.preventDefault();
            if (this.states.length == 0) return;
            var t = this.states[this.states.length - 1];
            switch (e.type) {
                case Constants.MOUSE_DOWN:
                    SoundManager.g_instance.init(), 
                    this.isMouseDown = !0, 
                    t.onMouseDown(e.stageX / Constants.SCREEN_SCALE, e.stageY / Constants.SCREEN_SCALE);
                    break;
                case Constants.MOUSE_UP:
                    this.isMouseDown = !1, 
                    t.onMouseUp(e.stageX / Constants.SCREEN_SCALE, e.stageY / Constants.SCREEN_SCALE);
                    break;
                case Constants.MOUSE_MOVE:
                    this.isMouseDown && t.onMouseMove(e.stageX / Constants.SCREEN_SCALE, e.stageY / Constants.SCREEN_SCALE)
            }
            DNButton.wasActionThisFrame = !1
        }
}