#include "max6675.h"
#include <stdio.h>
#include "pico/stdlib.h"

max6675::max6675(spi_inst_t* spi, uint8_t select){
    this->spi = spi;
    this->select = select;

    gpio_init(this->select);
    gpio_set_dir(this->select, true);
    gpio_put(this->select, true);
};

uint16_t max6675::read(){
    gpio_put(this->select, false);
    spi_read_blocking(this->spi, 0, buffer, 2);
    gpio_put(this->select, true);
    return (((uint16_t)buffer[0] << 8) | buffer[1]);
};

float max6675::getTemperature(){
    return (this->read() >> 3) * 0.25;
};

bool max6675::getStatus(){
    return !((bool)(this->read() & 0b100));
};