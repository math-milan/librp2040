add_library(ws2812b
        ws2812.cpp
        )

pico_generate_pio_header(ws2812lib  
        ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio
)

target_link_libraries(
        ws2812lib
        pico_stdlib
        hardware_pio
        )

target_include_directories (ws2812lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})