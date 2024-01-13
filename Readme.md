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

1. Start Visual Studio and "Continue without code".
2. Go to "Extensions>Manage Extensions" and install the "Qt Visual Studio Tools" if they are not installed already.
3. After the installation is finished go to "Extensions>Qt VS Tools>Qt Versions", click on "+" in the table and select the path
4. Select "C:\\Qt\\6.\<version\>\\msvc2019_64\\bin\\qmake.exe"
5. Install cmake (GUI)
6. Open cmake and set <Project-Path> as Source and <Project-Path>/build as Build.
7. Click "Environment..."
8. Click "Add Entry"
9. Insert:
    * Name: QTDIR
    * Value C:\Qt\6.\<version\>\msvc2019_64\lib\cmake
10. Click Ok twice
11. In the main window click "Configure" and Select the VS Version and select "x64"
12. Click "Generate"
13. Click "Open Project"
14. In VS right-click "ComplexCalc" and select "Set as Startup Project"
