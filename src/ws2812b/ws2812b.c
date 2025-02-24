#include "ws2812b.h"


void ws2812b_init(ws2812b_inst *inst, uint8_t pin, uint number_of_leds){\
    float freq = 800000;
    inst->number_of_leds = number_of_leds;
    uint offset = pio_add_program(PIO_INST, &ws2812_program);
    inst->state_maschine = pio_claim_unused_sm(PIO_INST, true);
    ws2812_program_init(PIO_INST, inst->state_maschine, offset, pin, freq, false);
}

void ws2812b_output_data(ws2812b_inst *inst, uint32_t buffer, int len){
    for (uint i = 0; i < len; i++)
    {
        pio_sm_put_blocking(PIO_INST, inst->state_maschine, buffer[i] << 8u);
    }
}

uint32_t ws2812b_convert_RGB(uint r, uint g, uint b){
    return ((uint32_t) (r) << 8) | ((uint32_t) (g) << 16) | (uint32_t)  (b);
}