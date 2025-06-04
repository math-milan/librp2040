#include "at24c02c.h"

bool at24c02c_init(at24c02c_inst *instance, i2c_inst_t *i2c_inst, uint8_t device_addr)
{
    instance->i2c_inst = i2c_inst;
    instance->device_addr = device_addr;
    return true;
}

bool at24c02c_writeByte(at24c02c_inst *instance, uint8_t addr, uint8_t data)
{
    uint8_t src[2];
    src[0] = addr;
    src[1] = data;

    return i2c_write_blocking(instance->i2c_inst, instance->device_addr, src, 2, false) == 2;
}

int8_t at24c02c_writePage(at24c02c_inst *instance, uint8_t addr, uint8_t *data, uint8_t len){
    if (addr % 8 + len > 8){ // You can only write a max of 8 bytes and only if they are on the same memmory page. the at24c01 has 16 banks wth 8 bytes each. Because partial writes with less then 8 bytes are possebill this filters all writes that are not possebile
        return PICO_ERROR_GENERIC;
    }

    i2c_write_blocking(instance->i2c_inst, instance->device_addr, &addr, 1, true);
    return i2c_write_blocking(instance->i2c_inst, instance->device_addr, data, len, false) == len;
}

int16_t at24c02c_readRandom(at24c02c_inst *instance, uint8_t addr){
    if (i2c_write_blocking(instance->i2c_inst, instance->device_addr, &addr, 1, false) != 1){
        return PICO_ERROR_GENERIC;
    }

    uint8_t dst;

    if (i2c_read_blocking(instance->i2c_inst, instance->device_addr, &dst, 1, false) == PICO_ERROR_GENERIC){
        return PICO_ERROR_GENERIC;
    }

    return dst;
}

int8_t at24c02c_readSequential(at24c02c_inst *instance, uint8_t addr, uint8_t *buffer, uint8_t len){
    if (i2c_write_blocking(instance->i2c_inst, instance->device_addr, &addr, 1, false) != 1){
        return PICO_ERROR_GENERIC;
    }

    int16_t total_bytes_read = 0;

    for (int16_t i = 0; i < len; i++)
    {
        int8_t dst;

        if (i2c_read_blocking(instance->i2c_inst, instance->device_addr, &dst, 1, false) == PICO_ERROR_GENERIC){
            return total_bytes_read > 0 ? total_bytes_read : PICO_ERROR_GENERIC;
        }

        buffer[i] = dst;
    }
    return total_bytes_read;
}
