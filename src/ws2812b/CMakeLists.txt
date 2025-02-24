add_library(ws2812b STATIC
        ws2812b.c
        )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


pico_generate_pio_header(ws2812b
        ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio
)

target_link_libraries(ws2812b
        pico_stdlib
        hardware_pio
        )

target_include_directories (ws2812b PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})