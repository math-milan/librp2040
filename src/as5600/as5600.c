#include "as5600.h"

void config_init(as5600_config_t *cfg, uint16_t value) {
    cfg->pm = value & 0b11;
    cfg->hyst = (value >> 2) & 0b11;
    cfg->outs = (value >> 4) & 0b11;
    cfg->pwmf = (value >> 6) & 0b11;
    cfg->sf = (value >> 8) & 0b11;
    cfg->fth = (value >> 10) & 0b111;
    cfg->wd = (value >> 13) & 0b1;
}

uint16_t config_to_uint16(const as5600_config_t *cfg) {
    return (cfg->pm) |
           (cfg->hyst << 2) |
           (cfg->outs << 4) |
           (cfg->pwmf << 6) |
           (cfg->sf << 8) |
           (cfg->fth << 10) |
           (cfg->wd << 13);
}

int16_t as5600_getRawAngel(i2c_inst_t *i2c){
    if (!as5600_writeInstruction(i2c, RAW_ANGLE)){
            return PICO_ERROR_GENERIC;
    }
    uint16_t data = as5600_read(i2c, 2);      

    return data & 0xFFF; // Returns 12 bits
}

int16_t as5600_getAngel(i2c_inst_t *i2c){
    if (!as5600_writeInstruction(i2c, ANGLE)){
        return PICO_ERROR_GENERIC;
    }

    uint16_t data = as5600_read(i2c, 2);
    
    return data & 0xFFF; // Returns 12 bits
}

bool as5600_getConfig(i2c_inst_t *i2c, as5600_config_t *cfg){
    if (!as5600_writeInstruction(i2c, CONF)){
        return false;
    }
    int data = as5600_read(i2c, 2);
    config_init(cfg, data);

    return data != PICO_ERROR_GENERIC;
}

bool as5600_setConfig(i2c_inst_t *i2c, as5600_config_t cfg){
    if (!as5600_writeInstruction(i2c, CONF)){
        return false;
    }

    uint8_t src[3];
    src[0] = CONF;
    src[1] = (config_to_uint16(&cfg) | 0xFF00) >> 8;
    src[2] = config_to_uint16(&cfg) | 0xFF;

    return i2c_write_blocking(i2c, AS5600_ADDRESS, &src, 3, false) == 3;
}

bool as5600_writeInstruction(i2c_inst_t *i2c, Register_Address addr){
    uint8_t reg = (uint8_t)(addr);
    return (i2c_write_blocking(i2c, AS5600_ADDRESS, &reg, 1, true) == 1);
}

uint16_t as5600_read(i2c_inst_t *i2c, int len){
    int DST_BUFFER_LEN = 5;
    uint8_t dst[DST_BUFFER_LEN];
    if (len >= DST_BUFFER_LEN){            
        return false;
    }
    if (i2c_read_blocking(i2c, AS5600_ADDRESS, dst, len, false) != len){
        return PICO_ERROR_GENERIC;
    }
    return (dst[0] << 8) | dst[1];
}