#pragma once

#include "hardware/spi.h"

class max6675 {
    public:
        max6675(
            spi_inst_t *spi,
            uint8_t select
        );

        /// @brief Read the Temperature from 0-1023.75
        /// @return Tempruter in C as 32 bit float
        float getTemperature();
        /// @brief Returns the stauts off Thermocouple
        /// @return If false connectet, true if connectet
        bool getStatus();
    private:
        spi_inst_t* spi;
        uint8_t select;
        uint8_t buffer[2];
        /// @brief Read the Sensor
        /// @return The 16 Bit number that the max6675 returns
        uint16_t read();
};