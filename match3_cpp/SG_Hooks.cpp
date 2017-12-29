public class SG_Hooks {
    public static debug = true;
    
	public static getLanguage( supportedLanguages ){
		return SG.initLangs(supportedLanguages);
	}

	public static start(){
        SG_Hooks.debug && console.log('game started');
        SG.trigger({type:'start'});
	}

	public static levelUp( level, score, callback){
        SG_Hooks.debug && console.log('level up:' + level + '/' + score);
		SG.trigger({type:'levelUp', level:level, lastLevelScore:score}, callback);
	}

	public static gameOver( level, score, callback){
        SG_Hooks.debug && console.log('game over:' + level + '/' + score);
		SG.trigger({type:'gameOver', score:score}, callback);
	}

    public static gameCompleted( score, callback ){
        SG_Hooks.debug && console.log('game completed:' + score);
        SG.trigger({type:'gameCompleted', score:score}, callback);
    }
    
    public static gamePause( state, callback ){ // state: on|off
        SG_Hooks.debug && console.log('game pause:' + state);
        SG.trigger({type:'gamePause', state:state}, callback);
    }
    
    public static gameRestart( callback ){
        SG_Hooks.debug && console.log('game restart:');
        SG.trigger({type:'gameRestart'}, callback);
    }
    
    public static selectMainMenu(callback){
        SG_Hooks.debug && console.log('selectMainMenu:');
        SG.trigger({type:'selectMainMenu'}, callback);
    }
    
    public static selectLevel( level, callback ){
        SG_Hooks.debug && console.log('selectLevel:'+level);
        SG.trigger({type:'selectLevel', level:level}, callback);
    }
    
    public static setSound( state, callback ){ // state: on|off
        SG_Hooks.debug && console.log('setSound:'+state);
        SG.trigger({type:'gameCompleted', state:state}, callback);
    }
    
    public static setOrientationHandler( f ){
		SG.setOrientationHandler( f );
	}
	
	public static setResizeHandler( f ){
		SG.setResizeHandler(f);
	}
}