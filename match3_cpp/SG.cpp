var SG_Lang = 'en';

public class SG {
    loaded : false,
	debug : false,
	lang 		   : 'en',
	gameJS 	 	   : [],
    loadScrnTimer  : 10,
	
	boot : function(){
        SG.initLangs(window.gameLangs);
        

		SG.startGame();
		
	},

	startGame : function(){
		
	},
   
	showLoadScrn : function(){
		
	},
	
	hideLoadScrn : function(){
        var loadscrn = SG.d.getElementById('sg-loadscrn');
        if( loadscrn )
            loadscrn.parentNode.removeChild(loadscrn);
	},
	
	
	trigger : function( data, callback ){
		
		return true;
	},
	
	initLangs : function( supported_languages ){
		var tmp_lang = typeof SG_getLang == 'function' ? SG_getLang() : 'en';
		var hasLanguages = (Object.prototype.toString.call(supported_languages)).toLowerCase() == "[object array]";
	    if( hasLanguages && supported_languages.indexOf(tmp_lang) >= 0 )
	    	SG.lang = tmp_lang;

	    SG_Lang = SG.lang; // support for old versions, that still use SG_Lang
	    return SG.lang;
	},
	
	getLang : function( ){
		return SG.lang;
	},

};

