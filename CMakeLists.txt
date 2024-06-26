cmake_minimum_required(VERSION 3.5)

project(ComplexCalc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH $ENV{QTDIR})

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Gui Widgets LinguistTools OpenGL OpenGLWidgets 3DCore 3DRender 3DInput 3DExtras)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets LinguistTools OpenGL OpenGLWidgets 3DCore 3DRender 3DInput 3DExtras)

set(TS_FILES resources/ComplexCalc_en_150.ts)

set(PROJECT_SOURCES
        header/complexcalc.h
        header/openglwindow.h
        header/customarrow.h
        header/complexvar.h
        header/scrollwidget.h
        header/trace.h
        header/label.h
        source/main.cpp
        source/complexcalc.cpp
        source/openglwindow.cpp
        source/customarrow.cpp
        source/complexvar.cpp
        source/scrollwidget.cpp
        source/trace.cpp
        source/label.cpp
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ComplexCalc
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(ComplexCalc PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGL Qt${QT_VERSION_MAJOR}::OpenGLWidgets Qt${QT_VERSION_MAJOR}::3DCore Qt${QT_VERSION_MAJOR}::3DRender Qt${QT_VERSION_MAJOR}::3DInput Qt${QT_VERSION_MAJOR}::3DExtras ${OPENGL_LIBRARIES})

set_target_properties(ComplexCalc PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ComplexCalc
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ComplexCalc)
endif()
