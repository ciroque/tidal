cmake_minimum_required(VERSION 3.17)
project(tidal VERSION 0.1)

configure_file(TidalConfig.h.in TidalConfig.h)

set(CMAKE_CXX_STANDARD 20)

add_executable(tidal src/main.cpp src/app/Application.cpp src/app/Application.h)

target_include_directories(tidal PUBLIC "${PROJECT_BINARY_DIR}" /usr/local/include/lunar)

target_link_libraries(tidal PUBLIC /usr/local/lib/liblunarstatic-d.a)
