var surface = new GraphicsSurface("OpenWorlds", Size(800, 600), GraphicsSurface.GLWidget);
surface.background = Rgb(0, 110, 160);

if(!surface.hasOpenGL())
    throw "OpenGL Support Required: " + surface.lastOpenGLError();

var loader = new GraphicsContainer(surface);
loader.background = "rgba(0,0,0,0.8)";
loader.setSize(Size(600, 420));
loader.borderRadius = 8;

var glViewHolder = new GraphicsContainer(loader);
glViewHolder.background = "rgba(0,0,0,0.8)";
glViewHolder.setSize(480, 280);
glViewHolder.setPos(60, 40);
glViewHolder.borderRadius = 8;

var glView = new GLGraphicsView(loader);
glView.setSize(460, 260);
glView.setPos(70, 50);

var glScene = new GLScene();
glView.setScene(glScene);
glView.camZ = -4;

var glCube = new GLCubeModel();
glScene.addModel(glCube);


engine.tick.connect(function() {
    glCube.rotate(0, 1, 0.2);
});

var textOverlay = new GraphicsText("Select Content Package", Font("Arial", 16), loader);
textOverlay.setPos(300-textOverlay.width/2, 8);
textOverlay.foreground = "white";

function BaseButton(text) {
    var createPackageBtn = new GraphicsText(text, Font("Arial", 12), loader);
    createPackageBtn.mouseEntered.connect(function() {
        createPackageBtn.background = "rgba(0,0,0,0.6)";
    });
    createPackageBtn.mouseLeft.connect(function() {
        createPackageBtn.background = "rgba(0,0,0,0.8)";
    });
    createPackageBtn.background = "rgba(0,0,0,0.8)";
    createPackageBtn.foreground = "white";
    createPackageBtn.cursor = "pointer";

    return createPackageBtn;
}
function LargeButton(text, x) {
    var createPackageBtn = BaseButton(text);
    createPackageBtn.setSize(80, 80);
    createPackageBtn.setPos(510-x, 330);
    createPackageBtn.borderRadius = 8;

    return createPackageBtn;
}

var prev = BaseButton("<");
prev.setSize(40, 280);
prev.setPos(10, 40);

var next = BaseButton(">");
next.setSize(40, 280);
next.setPos(550, 40);

var btn = LargeButton("Launch", 0);
btn = LargeButton("Edit", 100);
btn = LargeButton("Get More", 400);
btn = LargeButton("Create", 500);

surface.resized.connect(function(size) {
    loader.setPos(Point(surface.width/2-300, surface.height/2-210));
});
