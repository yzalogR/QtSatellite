cmake_minimum_required(VERSION 3.15)
project(Satellite
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets 3DCore 3DExtras 3DRender)

add_subdirectory(src)
