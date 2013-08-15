var surface = new GraphicsSurface("OpenWorlds", Size(800, 600), GraphicsSurface.GLWidget);
surface.background = Rgb(50, 0, 0);

if(!surface.hasOpenGL())
    throw "OpenGL Support Required: " + surface.lastOpenGLError();


