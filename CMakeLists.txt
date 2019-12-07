cmake_minimum_required(VERSION 3.3)

project(onceagain VERSION 0.1 LANGUAGES CXX)

find_package(KDDockWidgets REQUIRED)
find_package(Qt5Widgets)
find_package(Qt5Quick)

set(CMAKE_AUTOMOC ON)
add_subdirectory(src)
