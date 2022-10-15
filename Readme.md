Debug-Build Guide:

Windows:

1. Download the QT-installer from https://www.qt.io/download-qt-installer
2. Start the QT Installer and Log in or create an account (it is free and you can use throwaway credentials)
3. Agree to the GNU-License and check the box "not using QT for a company"
4. Disable statistics
5. Select "Custom Installation" and use the default path
6. Now select the following within the newest QT version (at time of writing 6.4.0):
    * gcc 64-bit
    * WebAssembly
7. Under "Developer and Designer Tools" select:
    * Qt Design Studio 3.7.0
    * CMake
    * Ninja
8. Click next and agree to the license
9. Finish the Installation

Linux:
1. sudo apt-get install libxcb-xinerama0
2. Download the QT-installer from https://www.qt.io/download-qt-installer
3. Assign execute rights with "chmod +x <download_path>/qt-unified-linux-x64-<version>-online.run
4. Log in or create an account (it is free and you can use throwaway credentials)
5. Agree to the GNU-License and check the box "not using QT for a company"
6. Disable statistics
7. Select "Custom Installation" and use the default path
8. Now select the following within the newest QT version (at time of writing 6.4.0):
    * WebAssembly
    * MSVC 2019 64-bit
    * MinGW 11.2.0 64-bit
9. Under "Developer and Designer Tools" select:
    * Qt Creator 8.0.1 CDB Debugger Support
    * Debugging Tools for Windows
    * Qt Design Studio 3.7.0
    * MinGW 11.2.0 64-bit
    * CMake
    * Ninja
10. Click next and agree to the license
11. Finish the Installation
12. QT Creator can be started by executing "<Qt-install-Dir>/Tools/QtCreator/bin/qtcreator.sh"

Generate Visual Studio Project:

1. Install cmake (GUI)
2. Open cmake and set <Project-Path> as Source and <Project-Path>/build as Build.
3. Click "Environment..."
4. Click "Add Entry"
5. Insert:
    * Name: QTDIR
    * Value C:\Qt\6.4.0\msvc2019_64\lib\cmake
6. Click Ok twice
3. In the main window click "Configure" and Select the VS Version and select "x64"
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

ToDo:

Fix WebAssembly (may work on Linux):

1. Python 3.6 or higher has to be installed
2. Install Emscripten as described here: https://emscripten.org/docs/getting_started/downloads.html
3. Enable the Build in Qt Creator as described here https://doc.qt.io/qtcreator/creator-setup-webassembly.html
