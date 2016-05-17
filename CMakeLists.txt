project(screensaver.asteroids)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

enable_language(CXX)

find_package(Kodi REQUIRED)
find_package(CXX11 REQUIRED)

include_directories(${KODI_INCLUDE_DIR})

set(ASTEROIDS_SOURCES src/asteroid.cpp
                      src/Asteroids.cpp
                      src/bullet.cpp
                      src/main.cpp
                      src/ship.cpp)

set(DEPLIBS)

build_addon(screensaver.asteroids ASTEROIDS DEPLIBS)

include(CPack)
