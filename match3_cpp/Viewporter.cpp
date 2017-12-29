public class Viewporter {
    public canvas = null;
    public loader = null;
    
    public Viewporter(){
        canvas = new Sprite();
        this.addChild(canvas);
        canvas.width = 600;
        canvas.height = 700;
        
        loader = new Sprite();
        this.addChild(loader);
    }

    public ACTIVE = true;

    public isLandscape() {
        return false
    },

    public refresh() {
        prepareVisualViewport()
    }

    // 阻止page scroll
    public preventPageScroll() {
        //
    }

    public prepareVisualViewport() {
        // 检测并调整主场景显示
        // 宽、高，方向横屏、竖屏
        //document.documentElement.style.minHeight = window.innerHeight + "px", 
        //document.getElementById("viewporter").style.position = "relative", 
        //document.getElementById("viewporter").style.height = window.innerHeight + "px"
    }
}