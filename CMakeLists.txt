cmake_minimum_required(VERSION 3.16)
project(mkv)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_RELEASE "-march=native -mtune=native -O3 -mmmx -msse -msse2 -msse3 -pedantic -Wextra -Wshadow -Wnon-virtual-dtor -Wdelete-non-virtual-dtor -fgraphite-identity -floop-nest-optimize -fdevirtualize-at-ltrans -fipa-pta -fno-semantic-interposition -flto=9 -fuse-linker-plugin -pipe -falign-functions=32")

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(fmt REQUIRED)

add_definitions(-DKS_STR_ENCODING_NONE)

include_directories(.)

add_executable(Buenos-Aires main.cpp
               utils.h utils.cpp

               ksy_helper.h ksy_helper.cpp
               ksy/header4.h ksy/header4.cpp
               ksy/header8body.h ksy/header8body.cpp
               kaitai/kaitaistream.cpp)

target_link_libraries(Buenos-Aires fmt::fmt)
