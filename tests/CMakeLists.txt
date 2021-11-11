
# These tests can use the Catch2-provided main
add_executable(
        tests
        RawWeatherDatumTests.cpp
        RunLengthEncodingTests.cpp
        TimeSeriesBackFillTests.cpp
        ../src/app/TimeSeriesDataPoint.cpp
        TimeSeriesTests.cpp
        ../src/app/Time.cpp
        ../src/app/models/utils/TimeSeries.h
        ../src/app/models/utils/TimeSeries.cpp
        ../src/app/TimeSeriesDataPoint.cpp
        ../src/app/models/weather/RawWeatherDatum.cpp
        ../src/app/models/weather/RunLengthEncoding.cpp
        ../src/app/models/weather/
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
