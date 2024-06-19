cmake_minimum_required(VERSION 3.16)
project(FJE_lmj)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(SOURCES
        src/main.cpp
        src/JsonNode.cpp
        src/Icon.cpp
        src/Style.cpp
        src/Draw.cpp
        src/JsonLoader.cpp
        src/Iterator.cpp
)

set(HEADERS
        include/JsonNode.h
        include/Icon.h
        include/Style.h
        include/Draw.h
        include/JsonLoader.h
        include/Iterator.h
)

add_executable(fje ${SOURCES} ${HEADERS})