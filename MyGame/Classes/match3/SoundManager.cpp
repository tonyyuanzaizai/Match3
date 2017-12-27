public class SoundManager {
        public SoundManager() {
            this.soundEnabled = !0, 
            this.initiliazed = !1, 
            this.musicInstance = null, 
            this.focus = !0, 
            this.wasMusicPlay = !1
        }

        public onLostFocus = function() {
            if (this.focus) {
                this.focus = !1;
                if (this.soundEnabled) {
                    if (this.musicInstance) try {
                        this.musicInstance.stop()
                    } catch (e) {}
                    this.wasMusicPlay = !1
                }
            }
        }
        
        public onFocus = function() {
            this.focus || (this.focus = !0)
        }
        
        public init = function() {
            if (!this.initiliazed) {
                this.initiliazed = !0
            }
        }
        
        public isSoundEnabled = function() {
            return this.soundEnabled
        }
        
        public setSoundEnabled = function(e) {
            this.soundEnabled = e;
            if (!e) {
                if (this.musicInstance) {
                    try {
                        this.musicInstance.stop()
                    } catch (t) {}
                }
                this.wasMusicPlay = !1
            }
        }
        
        public play = function(e) {
            try {
                if (this.initiliazed && this.soundEnabled) try {
                    return createjs.Sound.play(e, createjs.Sound.INTERRUPT_NONE, 0, 0, 0, 1)
                } catch (t) {}
            } catch (t) {}
            return null
        }
        
        public playMusic = function() {
            if (this.initiliazed && this.soundEnabled && !this.wasMusicPlay) {
                this.wasMusicPlay = !0;
                try {
                    this.musicInstance = createjs.Sound.play(SOUND_MUSIC, createjs.Sound.INTERRUPT_NONE, 0, 0, -1, 1);
                    if (this.musicInstance.playState == "playFailed") return this.wasMusicPlay = !1, null
                } catch (t) {
                    return null
                }
                return this.musicInstance
            }
            return null
        }
        
        //SoundManager.g_instance
        public static g_instance = new SoundManager(); 
        public String SOUND_MUSIC = "music", 
        public String SOUND_CLICK = "click", 
        public String SOUND_MATCH_1 = "match_1", 
        public String SOUND_MATCH_2 = "match_2", 
        public String SOUND_MATCH_3 = "match_3", 
        public String SOUND_MATCH_4 = "match_4", 
        public String SOUND_MATCH_5 = "match_5", 
        public String SOUND_DROP_1 = "drop_1", 
        public String SOUND_DROP_2 = "drop_2", 
        public String SOUND_DROP_3 = "drop_3", 
        public String SOUND_LINE = "line", 
        public String SOUND_KILL_COLOR = "kill_color", 
        public String SOUND_LOSE = "lose", 
        public String SOUND_BOOM = "boom", 
        public String SOUND_AWESOME = "awesome", 
        public String SOUND_EXCHANGE = "exchange", 
        public String SOUND_WIN = "win"
}