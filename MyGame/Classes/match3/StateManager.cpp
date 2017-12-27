//TODO lihua
public class StateManager {
        function StateManager(t) {
            var n = this;
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
                return n.update(e)
            }), 
            
            var r = new AssetsManager(t);
            
            this.stage.addChild(r), 
            r.addEventListener(Constants.LOAD_COMPLETE, function(e) {
                return n.allAssetsLoaded(e)
            }), 
            r.startDownLoad(), 
            this.stage.addChild(this.statesConstainer), 
            Constants.PIXEL_RATIO = window.devicePixelRatio ? window.devicePixelRatio : 1; 
            Constants.g_isPC ? (window.onresize = function(e) {
                return n.onResize(e)
            }, this.onResize(null)) : (viewporter.ACTIVE ? (window.addEventListener("viewportready", function() {
                return n.onOrientationChanged()
            }), window.addEventListener("viewportchange", function() {
                return n.onOrientationChanged()
            })) : window.addEventListener("orientationchange", function() {
                return n.onOrientationChanged()
            }), this.onOrientationChanged())
        }
        e.prototype.isLandscape = function() {
            return Constants.g_isPC ? !1 : viewporter.isLandscape()
        }, 
        e.prototype.allAssetsLoaded = function(t) {
            var n = this;
            t.target.removeEventListener(Constants.LOAD_COMPLETE, this.allAssetsLoaded), this.stage.addEventListener(Constants.MOUSE_MOVE, function(e) {
                return n.handleMouse(e)
            }), this.stage.addEventListener(Constants.MOUSE_DOWN, function(e) {
                return n.handleMouse(e)
            }), this.stage.addEventListener(Constants.MOUSE_UP, function(e) {
                return n.handleMouse(e)
            }), StringManager.getInstance().loadStrings();
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
                return n.onLostFocus(e)
            }), window.onblur && (window.onblur = function(e) {
                return n.onLostFocus(e)
            }), window.onpageshow && (window.onpageshow = function(e) {
                return n.onFocus(e)
            }), window.onfocus && (window.onfocus = function(e) {
                return n.onFocus(e)
            }), AssetsManager.g_instance.parent && AssetsManager.g_instance.parent.removeChild(AssetsManager.g_instance), GameData.getInstance().load(), this.pushState(new MainMenuState), this.isLandscape() && this.pushState(new PortraitLockState)
        }, 
        e.prototype.update = function(e) {
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
        }, 
        e.prototype.changeState = function(e) {
            while (this.states.length != 0) this.popState();
            this.pushState(e)
        }, 
        e.prototype.pushState = function(e) {
            this.states.push(e), this.statesConstainer.addChild(e)
        }, 
        e.prototype.popState = function() {
            this.states.length != 0 && (this.states[this.states.length - 1].cleanup(), 
            this.statesConstainer.removeChild(this.states[this.states.length - 1]), 
            this.states.pop(), 
            this.states.length != 0 && this.states[this.states.length - 1].resume())
        }, 
        e.getInnerWidth = function() {
            return Constants.g_isPC ? window.innerWidth : window.innerWidth
        }, 
        e.getInnerHeight = function() {
            return Constants.g_isPC ? window.innerHeight : window.innerHeight
        }, 
        e.prototype.onResize = function(t) {
            Constants.g_wasSetSize || (Constants.W = e.getInnerWidth(), Constants.H = e.getInnerHeight()), Constants.SCREEN_SCALE = Constants.H / Constants.ASSETS_HEIGHT *
                Constants.PIXEL_RATIO, Constants.SCREEN_HEIGHT = Constants.H / Constants.SCREEN_SCALE * Constants.PIXEL_RATIO, 
            this.canvas.width = Constants.ASSETS_WIDTH * Constants.SCREEN_SCALE, 
            this.canvas.height = Constants.ASSETS_HEIGHT * Constants.SCREEN_SCALE, 
            this.canvas.style.width = this.canvas.width + "px", 
            this.canvas.style.height = this.canvas.height + "px", 
            this.canvas.style.marginLeft = (Constants.W - this.canvas.width) / 2 + "px", 
            this.statesConstainer.scaleX = this.statesConstainer.scaleY = Constants.SCREEN_SCALE
        }, 
        e.prototype.onOrientationChanged = function() {
            Constants.g_wasSetSize || (Constants.W = e.getInnerWidth(), Constants.H = e.getInnerHeight());
            var t = this.isLandscape(),
            n = Constants.W,
            r = Constants.H;
            
            this.canvas.width = n * Constants.PIXEL_RATIO, 
            this.canvas.height = r * Constants.PIXEL_RATIO, 
            this.canvas.style.width = n + "px", 
            this.canvas.style.height = r + "px", t ? (Constants.SCREEN_SCALE = r / Constants.ASSETS_HEIGHT * Constants.PIXEL_RATIO, Constants.SCREEN_HEIGHT = r) : (Constants.SCREEN_SCALE = n / Constants.ASSETS_WIDTH * Constants.PIXEL_RATIO, Constants.SCREEN_HEIGHT = r / Constants.SCREEN_SCALE * Constants.PIXEL_RATIO), this.statesConstainer.scaleX = this.statesConstainer.scaleY = Constants.SCREEN_SCALE, this.states.length != 0 && this.states[this.states.length - 1].onOrientationChanged(t), AssetsManager.g_instance.parent && AssetsManager.g_instance.onOrientationChanged(t)
        }
        
        e.prototype.onLostFocus = function(e) {
            SoundManager.g_instance.onLostFocus()
        }
        
        e.prototype.onFocus = function(e) {
            SoundManager.g_instance.onFocus()
        }
        
        e.prototype.isMouseDownNow = function() {
            return this.isMouseDown
        }
        
        e.prototype.handleMouse = function(e) {
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