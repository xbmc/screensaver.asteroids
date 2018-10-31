project(screensaver.asteroids)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

enable_language(CXX)

find_package(Kodi REQUIRED)
find_package(CXX11 REQUIRED)

if(NOT WIN32)
  find_package(EMBEDDED)
  if((APP_RENDER_SYSTEM STREQUAL "gl" OR NOT APP_RENDER_SYSTEM) AND NOT EMBEDDED_FOUND)
    find_package(OpenGL)
  endif()

  if(OPENGL_FOUND)
    set(APP_RENDER_SYSTEM gl)
    set(INCLUDES ${OPENGL_INCLUDE_DIR})
    set(DEPLIBS ${OPENGL_LIBRARIES})
    set(ASTEROIDS_SOURCES src/shaders/GUIShader.cpp
                          src/shaders/Matrix.cpp
                          src/shaders/Shader.cpp)
    set(ASTEROIDS_HEADERS src/shaders/GUIShader.h
                          src/shaders/Matrix.h
                          src/shaders/Shader.h)
    add_definitions(-DHAS_GL)
    message(STATUS "Asteroids screensaver via OpenGL")
  else()
    find_package(OpenGLES2)
    if(OPENGLES2_FOUND)
      set(APP_RENDER_SYSTEM gles)
      set(ASTEROIDS_SOURCES src/shaders/GUIShader.cpp
                            src/shaders/Matrix.cpp
                            src/shaders/Shader.cpp)
      set(ASTEROIDS_HEADERS src/shaders/GUIShader.h
                            src/shaders/Matrix.h
                            src/shaders/Shader.h)
      add_definitions(-DHAS_GLES2)
      set(INCLUDES ${OPENGLES2_INCLUDE_DIRS})
      set(DEPLIBS ${OPENGLES2_LIBRARIES})
      message(STATUS "Asteroids screensaver via OpenGLES")
    else()
      message(FATAL_ERROR "Asteroids screensaver OpenGL(ES) wasn't found")
    endif()
  endif()
endif()

include_directories(${KODI_INCLUDE_DIR}/..) # Hack way with "/..", need bigger Kodi cmake rework to match right include ways

list(APPEND ASTEROIDS_SOURCES src/asteroid.cpp
                              src/Asteroids.cpp
                              src/bullet.cpp
                              src/main.cpp
                              src/ship.cpp)

list(APPEND ASTEROIDS_HEADERS src/asteroid.h
                              src/Asteroids.h
                              src/bullet.h
                              src/main.h
                              src/ship.h
                              src/timer.h
                              src/types.h)

build_addon(screensaver.asteroids ASTEROIDS DEPLIBS)

include(CPack)
