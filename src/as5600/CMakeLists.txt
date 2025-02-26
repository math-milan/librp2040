add_library(as5600  STATIC
    as5600.c
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(as5600
    pico_stdlib
    hardware_i2c
)

target_include_directories (as5600 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
