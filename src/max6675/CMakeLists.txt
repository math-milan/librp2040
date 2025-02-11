add_library(max6675
        max6675.cpp
        )

target_link_libraries(max6675
        pico_stdlib
        hardware_spi
        )

target_include_directories (max6675 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})