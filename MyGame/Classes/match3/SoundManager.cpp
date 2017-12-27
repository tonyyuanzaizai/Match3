public class SoundManager {
        function SoundManager() {
            this.soundEnabled = !0, 
            this.initiliazed = !1, 
            this.musicInstance = null, 
            this.focus = !0, 
            this.wasMusicPlay = !1
        }

        e.prototype.onLostFocus = function() {
            if (this.focus) {
                this.focus = !1;
                if (this.soundEnabled) {
                    if (this.musicInstance) try {
                        this.musicInstance.stop()
                    } catch (e) {}
                    this.wasMusicPlay = !1
                }
            }
        }, 
        e.prototype.onFocus = function() {
            this.focus || (this.focus = !0)
        }, 
        e.prototype.init = function() {
            if (!this.initiliazed) {
                try {
                    if (!createjs.Sound.initializeDefaultPlugins()) return
                } catch (e) {}
                this.initiliazed = !0
            }
        }, 
        e.prototype.isSoundEnabled = function() {
            return this.soundEnabled
        }, 
        e.prototype.setSoundEnabled = function(e) {
            this.soundEnabled = e;
            if (!e) {
                if (this.musicInstance) try {
                    this.musicInstance.stop()
                } catch (t) {}
                this.wasMusicPlay = !1
            }
        }, 
        e.prototype.play = function(e) {
            try {
                if (this.initiliazed && this.soundEnabled) try {
                    return createjs.Sound.play(e, createjs.Sound.INTERRUPT_NONE, 0, 0, 0, 1)
                } catch (t) {}
            } catch (t) {}
            return null
        }, 
        e.prototype.playMusic = function() {
            if (this.initiliazed && this.soundEnabled && !this.wasMusicPlay) {
                this.wasMusicPlay = !0;
                try {
                    this.musicInstance = createjs.Sound.play(e.SOUND_MUSIC, createjs.Sound.INTERRUPT_NONE, 0, 0, -1, 1);
                    if (this.musicInstance.playState == "playFailed") return this.wasMusicPlay = !1, null
                } catch (t) {
                    return null
                }
                return this.musicInstance
            }
            return null
        }, 
        e.g_instance = new e, 
        e.SOUND_MUSIC = "music", 
        e.SOUND_CLICK = "click", 
        e.SOUND_MATCH_1 = "match_1", 
        e.SOUND_MATCH_2 = "match_2", 
        e.SOUND_MATCH_3 = "match_3", 
        e.SOUND_MATCH_4 = "match_4", 
        e.SOUND_MATCH_5 = "match_5", 
        e.SOUND_DROP_1 = "drop_1", 
        e.SOUND_DROP_2 = "drop_2", 
        e.SOUND_DROP_3 = "drop_3", 
        e.SOUND_LINE = "line", 
        e.SOUND_KILL_COLOR = "kill_color", 
        e.SOUND_LOSE = "lose", 
        e.SOUND_BOOM = "boom", 
        e.SOUND_AWESOME = "awesome", 
        e.SOUND_EXCHANGE = "exchange", 
        e.SOUND_WIN = "win"
}