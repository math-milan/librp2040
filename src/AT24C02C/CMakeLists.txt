add_library(at24c02c  STATIC
    at24c02c.c
)

target_link_libraries(at24c02c
    pico_stdlib
    hardware_i2c
)

target_include_directories (at24c02c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})