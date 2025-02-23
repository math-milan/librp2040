#include "hardware/i2c.h"
#include "pico/stdlib.h"

#ifndef at24c0xc_H
#define at24c0xc_H

struct at24c02c_inst{
    i2c_inst_t *i2c_inst;
    uint8_t device_addr;
};

bool at24c02c_init(at24c02c_inst *instance, i2c_inst_t *i2c_inst, uint8_t device_addr);
/// @brief Write one Byte of data to random addres
/// @param instance at24c02 instance
/// @param addr Word Address
/// @param data One Byte of Data
/// @return Returns true if succsess full
bool at24c02c_writeByte(at24c02c_inst *instance, uint8_t addr, uint8_t data);

/// @brief Write one Page of data the at24c02. Max Length is 8 Bytes but only for one page. Read the Datasheet 
/// @param instance at24c02 instance
/// @param addr Word Address
/// @param data Pointer to a buffer with data
/// @param len Buffer Length
/// @return Returns number of bytes of pico error generic (-2)
int8_t at24c02c_writePage(at24c02c_inst *instance, uint8_t addr, uint8_t *data, uint8_t len);

/// @brief Read a Random Address form Memory
/// @param instance at24c02 instance
/// @param addr Word Address
/// @return Returns number of bytes read or PICO GENERIC ERROR
int16_t at24c02c_readRandom(at24c02c_inst *instance, uint8_t addr);

/// @brief Read a n number of bytes sequential
/// @param addr Word Address
/// @param buffer Buffer for the data
/// @param len Number of Bytes to read
/// @return Returns number of bytes read or PICO GENERIC ERROR
int8_t at24c02c_readSequential(at24c02c_inst *instance, uint8_t addr, uint8_t *buffer, uint8_t len);
#endif