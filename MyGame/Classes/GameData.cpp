//TODO lihua
public class GameData {
        public GameData() {
            this.levelsCompleted = 0;
            this.totalScore = 0;
            this.levels = [
            {
                form: [
                    [0, 1, 1, 1, 1, 1, 1, 0],
                    [0, 1, 1, 1, 1, 1, 1, 0],
                    [0, 1, 1, 1, 1, 1, 1, 0],
                    [0, 1, 1, 1, 1, 1, 1, 0],
                    [0, 1, 1, 1, 1, 1, 1, 0],
                    [0, 1, 1, 1, 1, 1, 1, 0],
                    [0, 1, 1, 1, 1, 1, 1, 0],
                    [0, 0, 0, 0, 0, 0, 0, 0]
                ],
                dirt: null,
                chips: [
                    [0, 5, 3, 2, 1, 2, 5, 0],
                    [0, 1, 2, 1, 2, 1, 4, 0],
                    [0, 3, 1, 5, 1, 5, 1, 0],
                    [0, 1, 2, 3, 3, 2, 4, 0],
                    [0, 2, 3, 5, 1, 4, 1, 0],
                    [0, 2, 5, 3, 5, 1, 4, 0],
                    [0, 1, 2, 3, 1, 4, 1, 0],
                    [0, 0, 0, 0, 0, 0, 0, 0]
                ],
                chip_types: 5,
                moves: 25,
                chip_goal: 4,
                chip_goal_count: 13
            }, 
            {
                form: [
                    [0, 0, 1, 0, 0, 1, 0, 0],
                    [0, 1, 1, 1, 1, 1, 1, 0],
                    [1, 1, 1, 1, 1, 1, 1, 1],
                    [0, 1, 1, 1, 1, 1, 1, 0],
                    [0, 1, 1, 1, 1, 1, 1, 0],
                    [1, 1, 1, 1, 1, 1, 1, 1],
                    [0, 1, 1, 1, 1, 1, 1, 0],
                    [0, 0, 1, 0, 0, 1, 0, 0]
                ],
                dirt: null,
                chips: [
                    [0, 0, 4, 0, 0, 1, 0, 0],
                    [0, 1, 2, 2, 3, 4, 5, 0],
                    [2, 1, 3, 3, 4, 1, 2, 3],
                    [0, 4, 1, 5, 4, 4, 2, 0],
                    [0, 3, 4, 1, 2, 3, 1, 0],
                    [1, 2, 3, 5, 5, 3, 5, 2],
                    [0, 5, 1, 5, 4, 2, 2, 0],
                    [0, 0, 5, 0, 0, 1, 0, 0]
                ],
                chip_types: 5,
                moves: 30,
                chip_goal: 1,
                chip_goal_count: 20
            }, {
                form: [
                    [0, 0, 0, 0, 0, 0, 0, 0],
                    [0, 1, 1, 1, 1, 1, 1, 0],
                    [0, 1, 1, 1, 1, 1, 1, 0],
                    [0, 1, 1, 1, 1, 1, 1, 0],
                    [0, 1, 1, 1, 1, 1, 1, 0],
                    [0, 1, 1, 1, 1, 1, 1, 0],
                    [0, 1, 1, 1, 1, 1, 1, 0],
                    [0, 0, 0, 0, 0, 0, 0, 0]
                ],
                dirt: [
                    [0, 0, 0, 0, 0, 0, 0, 0],
                    [0, 0, 1, 1, 1, 1, 0, 0],
                    [0, 0, 1, 1, 1, 1, 0, 0],
                    [0, 0, 1, 1, 1, 1, 0, 0],
                    [0, 0, 1, 1, 1, 1, 0, 0],
                    [0, 0, 1, 1, 1, 1, 0, 0],
                    [0, 0, 1, 1, 1, 1, 0, 0],
                    [0, 0, 0, 0, 0, 0, 0, 0]
                ],
                chips: [
                    [0, 0, 0, 0, 0, 0, 0, 0],
                    [0, 1, 2, 4, 3, 4, 5, 0],
                    [0, 3, 3, 5, 2, 1, 5, 0],
                    [0, 2, 4, 1, 2, 6, 6, 0],
                    [0, 2, 4, 2, 3, 3, 4, 0],
                    [0, 1, 2, 3, 4, 6, 6, 0],
                    [0, 2, 1, 5, 5, 4, 2, 0],
                    [0, 0, 0, 0, 0, 0, 0, 0]
                ],
                chip_types: 6,
                moves: 40,
                chip_goal: 0,
                chip_goal_count: 0
            }
            
            ]
        }
        
        private static instance;
        public static getInstance() {
            return this.instance == null && (this.instance = new GameData), this.instance
        }
        
        // 存档 level
        public save() {
            //this.levelsCompleted
        }
        //恢复档位 level
        public load() {
            //this.levelsCompleted = 
        } 
        
        public onWinLevel(e, t) {
            this.totalScore += t, 
            if(e == this.levelsCompleted){
                this.levelsCompleted = e + 1;
                if(this.levelsCompleted > this.getTotalLevels()){
                    this.levelsCompleted = this.getTotalLevels();
                }
            }

            this.save()
        }
        
        public getTotalScore() {
            return this.totalScore
        }
        
        public levelsAvailable() {
            return Constants::g_DEBUG ? this.getTotalLevels() : this.levelsCompleted + 1
        }
        
        public getLevelDef(e) {
            return this.levels[e]
        }
        
        public getTotalLevels() {
            return this.levels.length
        }
}