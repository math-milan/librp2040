#include "ws2812.pio.h"

#ifndef ws2812b_H
#define ws2812b_H

#define PIO_INST pio0

typedef struct {
    uint state_maschine;
    uint number_of_leds;  
} ws2812b_inst_t;

void ws2812b_init(ws2812b_inst_t *inst, uint8_t pin, uint number_of_leds);
void ws2812b_output_data(ws2812b_inst_t *inst, uint32_t *buffer, int len);
uint32_t ws2812b_convert_RGB(uint r, uint g, uint b);

#endif