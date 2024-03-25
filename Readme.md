# Description

The ComplexCalculator shall support high school students and prospective electrical engineering students with getting to know the complex number range for the first time. The application represents arithmetic operations (at this point addition and substraction) in the complex plane. This two-dimensional illustration is supplemented by a third axis, which represents the time axis. In combination the relationship between Complex numbers, the Euler identity and the trigonometric functions is visualized. In the future more mathematical operations can be added and the usage of different circular frequencies could be added.

This application was initially developed as a bachelors project by Florian Köttl within the Institute of Interactive Systems and Data Science at the Graz University of Technology.

# Repository structure

  - source -> contains the cpp-files
  - headers -> contains the h-files
  - resources -> contains varios data resources

# Build Guide

## Setting up Qt

### Windows

1. Download the QT-installer from https://www.qt.io/download-qt-installer
2. Start the QT Installer and Log in or create an account (it is free and you can use throwaway credentials)
3. Agree to the GNU-License and check the box "not using QT for a company"
4. Disable statistics
5. Select "Custom Installation" and use the default path
6. Now select the following within the newest QT version (6.x.x):
    - MSVC 2019 64-bit
    - MinGW \<version\> 64-bit
7. Under "Additional Libraries" select:
    - Qt 3D
8. Under "Developer and Designer Tools" select:
    - Qt Creator \<version\>
    - Qt Creator \<version\> CDB Debugger Support
    - Debugging Tools for Windows
    - Qt Design Studio \<version\>
    - MinGW \<version\> 64-bit (note that this version number should be the same as the MinGW-Version above)
    - CMake
    - Ninja
9. Click next and agree to the license
10. Finish the Installation

### Ubuntu 22.04

1.     sudo apt-get update && apt-get install libxcb-xinerama0 libglu1-mesa-dev libx11-xcb-dev libxcb-randr0-dev libxcb-xtest0-dev libxcb-xinerama0-dev libxcb-shape0-dev libxcb-xkb-dev libxkbcommon-x11-0  libfreetype6 libfontconfig1 cmake ninja-build g++ gdb
2. Download the QT-installer from https://www.qt.io/download-qt-installer
3. Assign execute rights with

       chmod +x <download_path>/qt-unified-linux-x64-<version>-online.run"
4. Log in or create an account (it is free and you can use throwaway credentials)
5. Agree to the GNU-License and check the box "not using QT for a company"
6. Disable statistics
7. Select "Custom Installation" and use the default path
8. Now select the following within the newest QT version:
    - gcc 64-bit
9. Under "Additional Libraries" select:
    - Qt 3D
10. Under "Developer and Designer Tools" select:
    - Qt Creator \<version\>
    - Qt Creator \<version\> Debug Symbols
    - CMake
    - Ninja
11. Click next and agree to the license
12. Finish the Installation
13. QT Creator can be started by executing "<Qt-install-Dir>/Tools/QtCreator/bin/qtcreator.sh"

## Setting up the IDE and Build

Now QTCreator or Visual Studio can be used to open the project and build the source.

### QTCreator (Ubuntu 22.04 & Windows)
1. Start QTCreator
2. Select "File>Open File or Project..."
3. Select the "CMakeLists.txt" inside the Repo.
4. Tick "Desktop Qt \<version\> MinGW 64-bit" and "Desktop Qt \<version\> MinGW 64-bit" for Windows or "Desktop Qt \<version\> GCC 64-bit" for Linux
5. For each of these configurations you can select which targets you want to be able to build, though the following two are recommended:
    - Debug
    - Minimum Size Release
6. Click Configure Project
7. Now you are able to build the Release or Debug build. Debugging is also possible.


### Visual Studio (Windows)

1. Start Visual Studio and "Continue without code".
2. Go to "Extensions>Manage Extensions" and install the "Qt Visual Studio Tools" if they are not installed already.
3. After the installation is finished go to "Extensions>Qt VS Tools>Qt Versions", click on "+" in the table and click on the path field.
4. Select "C:\\Qt\\\<version\>\\msvc2019_64\\bin\\qmake.exe"
5. Select "File>Open>CMake..."
6. Select the "CMakeLists.txt" inside the Repo.
7. Now you are able to build the Release or Debug build. Debugging is also possible.

## Creating a standalone ZIP (Windows)

For the following instructions you should use PowerShell.

### MSVC2019
1.     cd C:\Qt\<version>\msvc2019_64\bin
2.     .\qtenv2.bat
3. Copy the ComplexCalc.exe which was built with MSVC2019 into an empty directory
4.     .\windeployqt6.exe <path>\ComplexCalc.exe
5.     Compress-Archive <path>\* <path>\<filename>.zip

### MinGW
1.     cd C:\Qt\<version>\mingw_64\bin
2.     .\qtenv2.bat
3. Copy the ComplexCalc.exe which was built with MinGW into an empty directory
4.     .\windeployqt6.exe <path>\ComplexCalc.exe
5.     Compress-Archive <path>\* <path>\<filename>.zip