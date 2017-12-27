public class Utils {
        public Utils() {}
        
        // 静态全局方法
        public static RandomRange(e, t) {
            return e + (t - e) * Math.random()
        }
        
        public static RandomRangeInt(e, t) {
            return Math.floor(Math.random() * (t - e + 1)) + e
        }
        
        public static IntToTimeString(e) {
            var t = Math.floor(e / 60),
                n = t.toString(),
                r = e % 60,
                i;
            return r < 10 ? i = "0" + r : i = r.toString(), n + "d" + i
        }
        
        public static RadToGrad(e) {
            return e * 180 / Math.PI
        }
        
        public static GradToRad(e) {
            return e * Math.PI / 180
        }
        
        public static IsMobileBrowser() {
            return true
        }
        
        public static ScaledOffset(e) {
            return (window.devicePixelRatio ? window.devicePixelRatio : 1) * e / Constants.SCREEN_SCALE
        }
        
        public static GetScoreString(e) {
            var t = e.toString();
            switch (t.length) {
                case 1:
                    t = "00000" + t;
                    break;
                case 2:
                    t = "0000" + t;
                    break;
                case 3:
                    t = "000" + t;
                    break;
                case 4:
                    t = "00" + t;
                    break;
                case 5:
                    t = "0" + t
            }
            return t
        }
}