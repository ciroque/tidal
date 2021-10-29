
# These tests can use the Catch2-provided main
add_executable(
        tests
        RawWeatherDatumTests.cpp
        ../src/app/models/weather/RawWeatherDatum.cpp
        RunLengthEncodingTests.cpp
        ../src/app/models/weather/RunLengthEncoding.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
