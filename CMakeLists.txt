cmake_minimum_required(VERSION 3.25)

project(DungeonGeneratorDemo
LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

add_executable(dungeon_generator_demo)
target_sources(dungeon_generator_demo
    PRIVATE
        src/dungeon_types.h
        src/dungeon_generator.cpp
        src/dungeon.h
        src/dungeon.cpp
        src/generate_strategy.h
        src/generate_strategy.cpp
)