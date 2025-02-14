#include "at24c01c.h"

bool i2c_flash::at24c01c::writeByte(uint8_t addr, uint8_t data){
    while(!writabel()){
        sleep_ms(1);
    }
    last_write = time_us_64();

    uint8_t *src = new uint8_t[2];
    src[0] = addr;
    src[1] = data;

    bool response = i2c_write_blocking(i2c_inst, device_addr, src, 2, false) == 1;

    delete src;
    return response;
}

bool i2c_flash::at24c01c::writePage(uint8_t addr, uint8_t *buffer, int len){
    if (addr % 8 + len > 8 || !writabel()){ // You can only write a max of 8 bytes and only if they are on the same memmory page. the at24c01 has 16 banks wth 8 bytes each. Because partial writes with less then 8 bytes are possebill this filters all writes that are not possebile
        return false;
    }
    last_write = time_us_64();
    uint8_t *src = new uint8_t[len + 1];
    src[0] = addr;

    memcpy(&src[1], buffer, len);  // Copy data after address

    bool response = i2c_write_blocking(i2c_inst, device_addr, src, len, false);

    delete src;
    return response;
}

int16_t i2c_flash::at24c01c::readCurrent(uint8_t *dst)
{
    return i2c_read_blocking(i2c_inst, device_addr, dst, 1, false);
}

int16_t i2c_flash::at24c01c::readRandom(uint8_t addr, uint8_t *dst){
    if (i2c_write_blocking(i2c_inst, device_addr, &addr, 1, true) != 1){
        return PICO_ERROR_GENERIC;
    }
    return readCurrent(dst);
}

int16_t i2c_flash::at24c01c::readSequential(uint8_t addr, uint8_t *buffer, int len){
    if (i2c_write_blocking(i2c_inst, device_addr, &addr, 1, true) != 1){
        return PICO_ERROR_GENERIC;
    }
    int16_t total_bytes_read = 0;
    for (int i = 0; i < len; i++)
    {
        int16_t res = readCurrent(buffer + i);
        if (res != 1)  // Check if read was successful
        {
            return total_bytes_read > 0 ? total_bytes_read : PICO_ERROR_GENERIC; // Return bytes read or error
        }
        total_bytes_read += res;
    }
    return total_bytes_read; // Return total bytes read
}

bool i2c_flash::at24c01c::writabel(){
    if (last_write + 5 * 1000 < time_us_64()){
        // i2c_hw_t *i2c_hw = i2c_get_hw(i2c_inst);
        // i2c_hw->ack_general_call
        return false;
    }
    return true;
}