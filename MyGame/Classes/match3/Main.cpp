// TODO Application
function init() {
    var e = [];
        
    t = [Constants.IMAGE_TITLE_MAIN_MENU_BACK, Constants.IMAGE_GLOBAL_MAP, Constants.IMAGE_BACK];
        
    n = [Constants.IMAGE_BUTTON_MORE_GAMES, Constants.IMAGE_SELECT_LEVEL_BACK, Constants.IMAGE_BORDER_SIDE, Constants.IMAGE_BORDER_CORNER, Constants.IMAGE_WIN_STRINGS, Constants.IMAGE_HEART_PARTICLE, Constants.IMAGE_SHINING, Constants.IMAGE_BIG_SHINING, Constants.IMAGE_POINTS_CONTROL_BIG, Constants.IMAGE_POINTS_CONTROL_SMALL, Constants.IMAGE_LEVEL_BUTTON, Constants.IMAGE_BACK, Constants.IMAGE_ROTATE, Constants.IMAGE_TITLE_MAIN_MENU_BACK, "cake_1", "cake_2", "cake_3", "cake_4", "cake_5", "cake_6", "cake_7", "font_0", "font_1", "font_2", "font_3", "font_4", "font_5", "font_6", "font_7", "font_8", "font_9", "sel_0", "sel_1", "sel_2", "sel_3", "sel_4", "sel_5", "sel_6", "sel_7", "sel_8", "sel_9", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "p", "boom_1", "boom_2", "boom_3", "boom_4", "boom_5", "boom_6", "boom_7", "boom_8", "boom_9", "boom_10", "boom_11", Constants.IMAGE_CELL, Constants.IMAGE_AWESOME, Constants.IMAGE_SUPERB, Constants.IMAGE_SHINING, Constants.IMAGE_DROP, Constants.IMAGE_DONUT, Constants.IMAGE_ARROW_BONUS_VERT, Constants.IMAGE_ARROW_BONUS_HOR, Constants.IMAGE_BOMB, Constants.IMAGE_MESSAGE_WINDOW, Constants.IMAGE_HINT_ARROW, Constants.IMAGE_BUTTON_PLAY, Constants.IMAGE_BUTTON_SOUND_ON, Constants.IMAGE_BUTTON_SOUND_OFF, Constants.IMAGE_BUTTON_CLOSE, Constants.IMAGE_BUTTON_EXIT, Constants.IMAGE_BUTTON_PAUSE, Constants.IMAGE_BUTTON_RESTART, Constants.IMAGE_GAMEOVER_CAPTION, Constants.IMAGE_SICKLE, Constants.IMAGE_DIRT, Constants.IMAGE_GUI, Constants.IMAGE_LOCK, Constants.IMAGE_OUT_OF_MOVES, Constants.IMAGE_WIN_CAPTION, Constants.IMAGE_STONE_HEART, Constants.IMAGE_TASK_PANEL, Constants.IMAGE_GLOBAL_MAP];
        
    r = [SoundManager.SOUND_CLICK, SoundManager.SOUND_MATCH_1, SoundManager.SOUND_MATCH_2, SoundManager.SOUND_MATCH_3, SoundManager.SOUND_MATCH_4, SoundManager.SOUND_MATCH_5, SoundManager.SOUND_DROP_1, SoundManager.SOUND_DROP_2, SoundManager.SOUND_DROP_3, SoundManager.SOUND_LINE, SoundManager.SOUND_KILL_COLOR, SoundManager.SOUND_BOOM, SoundManager.SOUND_AWESOME, SoundManager.SOUND_EXCHANGE, SoundManager.SOUND_WIN, SoundManager.SOUND_LOSE];
    
    //初始化图片path
    for (var i = 0; i < n.length; i++) {
        if(t.indexOf(n[i]) == -1){
             e.push({
                src: "assets/art/" + n[i] + ".png",
                id: n[i]
             });
        }
        else {
            e.push({
                src: "assets/art/" + n[i] + ".jpg",
                id: n[i]
            });
        }
    }
    //初始化音效path
    for (var i = 0; i < r.length; i++) {
        e.push({
            src: "assets/sound/" + r[i] + ".mp3",
            id: r[i]
        });
        console.log("Loading " + r[i]);
    }
    
    Constants.g_isPC = !Utils.IsMobileBrowser();
    Constants.W = StateManager.getInnerWidth();
    Constants.H = StateManager.getInnerHeight();
    new StateManager(e);
    
    var viewporter = new Viewporter(); 
    viewporter.prepareVisualViewport()
}

init();