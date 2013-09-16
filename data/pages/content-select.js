{

    tick: function() {
        this.glView.camZ += (-5 - this.glView.camZ)/28;
        this.glView.camRotate(0, -0.3, -0.1);
        this.glCube.rotate(0, 1, 0.3);

        //glView.camRotate(0, 0.1, 0);
    },

    setup: function() {
        var moeLogo = new GraphicsImage(this.widget);
        moeLogo.opacity = 0;
        var moeLogoDownload = ResourceRequest(Url("data://logo.png"));
        moeLogoDownload.receivedData.connect((function(data){
            moeLogo.load(data);
            moeLogo.animate("opacity", 1, 30);
            this.widget.animate("background", "black", 30);
        }).bind(this));
        moeLogoDownload.completed.connect(moeLogoDownload.deleteLater);


        var loader = new GraphicsContainer(this.widget);
        loader.background = VLinearGradient(GradientStop(0, "rgba(0,0,0,0.4)"), GradientStop(0.2, "rgba(0,0,0,0.9)"), GradientStop(0.4, "rgba(0,0,0,0.7)"), GradientStop(1, "rgba(0,0,0,0.7)"));
        loader.setSize(Size(600, 420));

        var glViewHolder = new GraphicsContainer(loader);
        glViewHolder.background = VLinearGradient(GradientStop(0, "rgba(0,0,0,0.4)"), GradientStop(0.2, "rgba(0,0,0,1)"), GradientStop(0.6, "rgba(0,0,0,1)"), GradientStop(1, "rgba(0,0,0,0.7)"));
        glViewHolder.setSize(480, 280);
        glViewHolder.setPos(60, 40);

        this.glView = new GLGraphicsView(loader);
        this.glView.setSize(460, 260);
        this.glView.setPos(70, 50);

        var glScene = new GLScene();
        this.glView.setScene(glScene);
        this.glView.camZ = -200;
        this.glView.shadow = 1;

        this.glCube = new GLCubeModel("rgb(115, 196, 115)");
        glScene.addModel(this.glCube);

        var terrainSpriteSheet = new GLSpriteSheet(Size(16, 16), Size(16, 16));
        var dirtTextureDownload = ResourceRequest(Url("/media/MediaHD/OpenWorlds/blocks/Dirt/dirt.png"));
        dirtTextureDownload.receivedData.connect((function(data) {
            terrainSpriteSheet.setSpriteData(Point(0, 0), data);
            this.glCube.setTexture(terrainSpriteSheet);
        }).bind(this));

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

        var textOverlay = new GraphicsText("OpenWorlds Default", Font("Arial", 14), loader);

        textOverlay.margin = 6;
        textOverlay.background = "rgba(0,0,0,0.8)";
        textOverlay.setPos(300-textOverlay.width/2, 280 - textOverlay.height);
        textOverlay.foreground = "white";

        this.widget.resized.connect(function(size) {
            moeLogo.setSize(size);
            loader.setPos(Point(size.width/2-300, size.height/2-210));
        });

    }
}
