Generate Visual Studio Project:

1. Install cmake (GUI)
2. Open cmake and set <Project-Path> as Source and <Project-Path>/build as Build.
3. Click "Configure" and Select the VS Version and select "x64"
4. Click "Generate"
5. Click "Open Project"
6. In VS right-click "ComplexCalc" and select "Set as Startup Project"
7. Copy the following files from <Install-Dir>/Qt/<Version>/msvc2019_64/bin to <Project-Path>/build/Debug :

platforms/qwindowsd.dll
styles/qwindowsvistastyled.dll
Qt6Cored.dll
Qt6Guid.dll
Qt6OpenGLd.dll
Qt6OpenGLWidgetsd.dll
Qt6Widgetsd.dll