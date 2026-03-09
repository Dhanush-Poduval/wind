cmake_minimum_required(VERSION 3.20)

project(rmrc)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
target_sources(app PRIVATE src/main.c )
target_include_directories(app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
