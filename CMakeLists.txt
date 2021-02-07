cmake_minimum_required(VERSION 3.17)
project(tidal VERSION 0.2)

find_package(Boost 1.73 REQUIRED)

find_package(raylib 3.0 QUIET)
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)

    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/master.tar.gz
    )

    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)

        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

        # build raylib
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

    endif()

endif()

configure_file(TidalConfig.h.in TidalConfig.h)

set(CMAKE_CXX_STANDARD 20)

add_executable(tidal
        include/nlohmann/json.hpp
        src/main.cpp
        src/app/Application.cpp
        src/app/Application.h
        src/app/TideRetriever.cpp
        src/app/TideRetriever.h
        src/app/WeatherRetriever.cpp
        src/app/WeatherRetriever.h
        src/app/Time.cpp src/app/Time.h
        src/app/Retriever.cpp
        src/app/Retriever.h
        src/app/root_certificates.h
        src/app/DisplayManager.cpp
        src/app/DisplayManager.h
        src/app/DisplayData.cpp
        src/app/DisplayData.h
        src/app/WeatherData.cpp
        src/app/WeatherData.h
        src/app/TideData.cpp
        src/app/TideData.h
        src/app/LunarData.cpp
        src/app/LunarData.h)

include_directories( ${Boost_INCLUDE_DIR} /usr/local/include /usr/local/Cellar/openssl@1.1/1.1.1g/include/)
target_include_directories(tidal PUBLIC "${PROJECT_BINARY_DIR}" /usr/local/include/lunar)

target_link_libraries(tidal PUBLIC /usr/local/lib/liblunarstatic.a pthread)
target_link_libraries(tidal
    LINK_PUBLIC
    ${Boost_LIBRARIES}
    libgraphLib.a
    ssl
    crypto
    SDL2
)
