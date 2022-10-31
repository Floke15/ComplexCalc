Debug-Build Guide:

Linux:

1. sudo apt-get install libxcb-xinerama0 libgl1-mesa-dev
2. Download the QT-installer from https://www.qt.io/download-qt-installer
3. Assign execute rights with "chmod +x <download_path>/qt-unified-linux-x64-<version>-online.run
4. Log in or create an account (it is free and you can use throwaway credentials)
5. Agree to the GNU-License and check the box "not using QT for a company"
6. Disable statistics
7. Select "Custom Installation" and use the default path
8. Now select the following within the newest QT version (at time of writing 6.4.0):
    * gcc 64-bit
    * WebAssembly
9. Under "Additional Libraries" select:
    * Qt 3D
10. Under "Developer and Designer Tools" select:
    * Qt Design Studio 3.7.0
    * CMake
    * Ninja
11. Click next and agree to the license
12. Finish the Installation
13. QT Creator can be started by executing "<Qt-install-Dir>/Tools/QtCreator/bin/qtcreator.sh"

WebAssembly (Linux):

1. Python 3.6 or higher has to be installed
2. sudo apt-get install ninja-build gcc gdb clang git
3. execute git clone https://github.com/emscripten-core/emsdk.git
4. cd emsdk
5. ./emsdk install 3.1.14
6. ./emsdk activate 3.1.14
7. source ./emsdk_env.sh
8. Enable the Build in Qt Creator as described here https://doc.qt.io/qtcreator/creator-setup-webassembly.html

Windows:

1. Download the QT-installer from https://www.qt.io/download-qt-installer
2. Start the QT Installer and Log in or create an account (it is free and you can use throwaway credentials)
3. Agree to the GNU-License and check the box "not using QT for a company"
4. Disable statistics
5. Select "Custom Installation" and use the default path
6. Now select the following within the newest QT version (at time of writing 6.4.0):
    * WebAssembly
    * MSVC 2019 64-bit
    * MinGW 11.2.0 64-bit
7. Under "Additional Libraries" select:
    * Qt 3D
8. Under "Developer and Designer Tools" select:
    * Qt Creator 8.0.1 CDB Debugger Support
    * Debugging Tools for Windows
    * Qt Design Studio 3.7.0
    * MinGW 11.2.0 64-bit
    * CMake
    * Ninja
9. Click next and agree to the license
10. Finish the Installation

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
renderes/openglrendererd.dll
Qt6Cored.dll
Qt6Guid.dll
Qt6OpenGLd.dll
Qt6OpenGLWidgetsd.dll
Qt6Widgetsd.dll
Qt63DExtrasd.dll
Qt63Logicd.dll
Qt63DInputd.dll
Qt63DRenderd.dll
Qt63DCored.dll
Qt6Concurrentd.dll
Qt6Networkd.dll
