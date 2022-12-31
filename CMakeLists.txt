cmake_minimum_required(VERSION 3.21)

project(MyAmazingSksePlugin VERSION 0.0.1)

find_package(SkyrimScripting.CMake CONFIG REQUIRED)
find_package(SkyrimScripting.Plugin CONFIG REQUIRED)

add_skse_plugin(${PROJECT_NAME} SOURCES plugin.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE SkyrimScriptingPlugin::SkyrimScripting.Plugin)
