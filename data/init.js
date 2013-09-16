var surface = new GraphicsSurface("OpenWorlds", Size(800, 600), GraphicsSurface.GLWidget);

if(!surface.hasOpenGL())
    throw "OpenGL Support Required: " + surface.lastOpenGLError();

var pageLayer = new GraphicsContainer(surface);

var Page = Class.create("Page", {
     initialize: function(name) {
         this.widget = new GraphicsContainer(pageLayer);
         this.opacity = 0;

         if(Object.isFunction(this.tick))
             this.tick = this.tick.bind(this);

         this.setup();
     },

    disconnect: function() {
        this.widget.animate("opacity", 0);

        if(Object.isFunction(this.tick))
            engine.tick.disconnect(this.tick);

        this.hide();
    },

    hide: function() {},
    show: function() {},
    setup: function() {},

     makeActive: function() {
         if(Page.active)
             Page.active.disconnect();

         this.widget.setSize(surface.size());
         this.widget.animate("opacity", 1, 27);
         Page.active = this;
         this.show();

         if(Object.isFunction(this.tick))
             engine.tick.connect(this.tick);
     }
 });
Page.loadedPages = {}
Page.switchTo = function(name) {
    if(name in Page.loadedPages) {
        Page.loadedPages[name].makeActive();
        return;
    }

    if(Page.active) {
        Page.active.disconnect();
        Page.active = null;
    }

    loaderItem.text = name;
    loaderLayer.animate("opacity", 1);
    var pageSourceRequest = new ResourceRequest("./pages/" + name + ".js");
    pageSourceRequest.receivedString.connect(function(source) {
        var pageClass = Class.create(Page, eval("(" + source + ")"));
        loaderLayer.animate("opacity", 0, 27);

        var instance = new pageClass();
        Page.loadedPages[name] = instance;
        instance.makeActive();
    });
    Page.loadedPages[name] = true;
}

var loaderLayer = new GraphicsContainer(surface);
loaderLayer.background = "rgba(0, 0, 0, 0.8)";
loaderLayer.setSize(Size(240, 80));
loaderLayer.borderRadius = 8;
loaderLayer.opacity = 0;

var loaderText = new GraphicsText("Loading", Font("Arial", 16), loaderLayer);
loaderText.setPos(Point(loaderLayer.width/2 - loaderText.width/2, 2));
loaderText.foreground = "white";

var loaderItem = new GraphicsText("Current Item", Font("Arial", 12), loaderLayer);
loaderItem.setPos(Point(6, 34));
loaderItem.foreground = "white";

var loaderProgress = new GraphicsObject(loaderLayer);
loaderProgress.background = "white";
loaderProgress.setPos(Point(10, 58));
loaderProgress.height = 10;
loaderProgress.width = 100;

surface.resized.connect(function(size){
    loaderLayer.setPos(size.width /2 - loaderLayer.width/2,
                       size.height /2 - loaderLayer.height/2);
    pageLayer.setSize(size);

    if(Page.active)
        Page.active.widget.setSize(size);
});

surface.connected.connect(function() {
    surface.animate("background", "black", 27);
    Page.switchTo("content-select");
});

