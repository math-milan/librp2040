add_library(at24c01c  STATIC
    at24c01c.cpp
)

target_link_libraries(at24c01c
    pico_stdlib
    hardware_i2c
)

target_include_directories (at24c01c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})