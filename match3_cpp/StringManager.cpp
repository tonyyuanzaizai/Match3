
    var g_strings = {
        en: {
            STRING_REMOVE: "Clear all",
            STRING_CLEAR: "Clear all ice cells"
        },
        es: {
            STRING_REMOVE: "Eliminar ",
            STRING_CLEAR: "Despeja todas las casillas de hielo"
        },
        pt: {
            STRING_REMOVE: "Eliminar",
            STRING_CLEAR: "Limpe todas as células de gelo"
        },
        tr: {
            STRING_REMOVE: "Ortadan Kaldır",
            STRING_CLEAR: "Tüm buz hücreleri sil"
        },
        de: {
            STRING_REMOVE: "Entferne",
            STRING_CLEAR: "Entferne alle Eis Kästchen"
        },
        ru: {
            STRING_REMOVE: "Удалите",
            STRING_CLEAR: "Удали все ледяные кубы"
        }
    }
    //g_allLanguages = ["en", "es", "pt", "tr", "de", "ru"],
    StringManager = function() {
        private strings = new Object, 
        private allStrings = null
        StringManager() {
            this.strings = new Object, 
            this.allStrings = null
        }
        public static getInstance() {
            return e.g_instance
        }, 
        public getString = function(e) {
            return this.strings[e]
        }, 
        public loadStrings = function() {
            this.allStrings = g_strings
        }, 
        public setLanguage = function(e) {
            this.strings = this.allStrings[e]
        }
        
        //静态全局变量
        private static StringManager g_instance = new StringManager(); 
        public static STRING_REMOVE = "STRING_REMOVE", 
        public static STRING_CLEAR = "STRING_CLEAR"
    }
