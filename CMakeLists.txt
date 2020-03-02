cmake_minimum_required(VERSION 3.15)
project(Satellite)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} C:/Qt/Qt5.14.1/5.14.1/msvc2017_64)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets 3DCore 3DExtras 3DRender)

add_executable(Satellite
        main.cpp
        MainWindow.cpp
        SceneWidget.cpp
        SatelliteModel.cpp
        StarFinderModel.cpp
        EarthModel.cpp
        CustomCameraController.cpp
        TorusModel.cpp
        ConeModel.cpp
        resources.qrc
        Light.cpp Light.h)

target_link_libraries(Satellite PRIVATE
        Qt5::Core
        Qt5::Widgets
        Qt5::3DCore
        Qt5::3DExtras
        Qt5::3DRender
        )
