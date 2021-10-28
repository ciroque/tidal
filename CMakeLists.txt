cmake_minimum_required(VERSION 3.17)
project(tidal VERSION 0.2)

find_package(Boost 1.73 REQUIRED)
find_package(Catch2 3 REQUIRED)

configure_file(TidalConfig.h.in TidalConfig.h)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(tests)

add_executable(tidal
        include/nlohmann/json.hpp
        src/main.cpp
        src/app/Application.cpp
        src/app/Application.h
        src/app/retrievers/TideRetriever.cpp
        src/app/retrievers/TideRetriever.h
        src/app/retrievers/WeatherRetriever.cpp
        src/app/retrievers/WeatherRetriever.h
        src/app/Time.cpp src/app/Time.h
        src/app/retrievers/Retriever.cpp
        src/app/retrievers/Retriever.h
        src/app/root_certificates.h
        src/app/DisplayManager.cpp
        src/app/DisplayManager.h
        src/app/models/DisplayData.cpp
        src/app/models/DisplayData.h
        src/app/models/WeatherParser.cpp
        src/app/models/WeatherParser.h
        src/app/models/TideData.cpp
        src/app/models/TideData.h
        src/app/models/LunarData.cpp
        src/app/models/LunarData.h
        src/app/TimeSeriesDataPoint.cpp
        src/app/TimeSeriesDataPoint.h
        src/app/config/AppConfig.cpp
        src/app/config/AppConfig.h
        src/app/config/ConfigReader.cpp
        src/app/config/ConfigReader.h
        src/app/retrievers/LunarRetriever.cpp
        src/app/retrievers/LunarRetriever.h
        src/app/models/Predictions.cpp
        src/app/models/Predictions.h
        src/app/models/DailyPrediction.cpp
        src/app/models/DailyPrediction.h
        src/app/config/ConfigFileNotFoundException.cpp
        src/app/config/ConfigFileNotFoundException.h
        src/app/FrameBufferOpenException.cpp
        src/app/FrameBufferOpenException.h
        src/app/models/WeatherData.cpp
        src/app/models/WeatherData.h
        src/app/models/LunarPredictions.cpp
        src/app/models/LunarPredictions.h
        src/app/models/TidePredictions.cpp
        src/app/models/TidePredictions.h
        src/app/models/TideDataParser.cpp
        src/app/models/TideDataParser.h
        src/app/models/WeatherPredictions.cpp
        src/app/models/WeatherPredictions.h
        src/app/models/RawWeatherDatum.cpp
        src/app/models/RawWeatherDatum.h)

include_directories( ${Boost_INCLUDE_DIR} /usr/local/include /usr/local/Cellar/openssl@1.1/1.1.1g/include/)
target_include_directories(tidal PUBLIC "${PROJECT_BINARY_DIR}" /usr/local/include/lunar /usr/local/include/graphLib)

target_link_libraries(tidal
        PUBLIC
        /usr/local/lib/liblunarstatic.a
        /usr/local/lib/libgraphLib.a
        pthread)
target_link_libraries(tidal
    LINK_PUBLIC
    ${Boost_LIBRARIES}
    ssl
    crypto
)
