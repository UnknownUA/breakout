cmake_minimum_required(VERSION 3.14)

project(breakout LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(breakout
    ball.h
    ball.cpp
    gameengine.h
    gameengine.cpp
    platform.h
    platform.cpp
    timerthread.h
    timerthread.cpp
    main.cpp
)
