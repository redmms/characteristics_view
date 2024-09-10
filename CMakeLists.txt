cmake_minimum_required(VERSION 3.5)

project(characterictics_view VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        controllerdialog.cpp
        controllerdialog.h
        controllerdialog.ui
        detailmode.h
        detailmode.cpp
        detailitem.h
        detailitem.cpp
        material.h
        material.cpp
        detailmodel.h
        detailmodel.cpp
        enums.h
        enums.cpp
        helpers/abstracthelper.h
        helpers/methodhelper.h
        helpers/methodhelper.cpp
        helpers/masshelper.h
        helpers/masshelper.cpp
        helpers/densityhelper.h
        helpers/densityhelper.cpp
        helpers/centerhelper.h
        helpers/centerhelper.cpp
        helpers/materialhelper.h
        helpers/materialhelper.cpp
        helpers/stylehelper.h
        helpers/stylehelper.cpp
        helpers/anglehelper.h
        helpers/anglehelper.cpp
        media.qrc
        appicon.rc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(characterictics_view
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET characterictics_view APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(characterictics_view SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(characterictics_view
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(characterictics_view PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(characterictics_view PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS characterictics_view
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(characterictics_view)
endif()
