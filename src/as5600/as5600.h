#include "hardware/i2c.h"
#include "pico/stdlib.h"

#define AS5600_ADDRESS 0x36

typedef enum{
    ZMCO = 0x00,
    ZPOS = 0x01,
    MPOS = 0x03,
    MANG = 0x05,
    CONF = 0x07,
    RAW_ANGLE = 0x0C,
    ANGLE = 0x0E,
    STATUS = 0x0B,
    AGC = 0x1A,
    MAGNITUDE = 0x01C
} Register_Address;

typedef struct {
    uint8_t pm : 2;
    uint8_t hyst : 2;
    uint8_t outs : 2;
    uint8_t pwmf : 2;
    uint8_t sf : 2;
    uint8_t fth : 3;
    bool wd : 1;
} as5600_config_t;

void config_init(as5600_config_t *cfg, uint16_t value);    // Function to initialize the struct from a uint16_t
uint16_t config_to_uint16(const as5600_config_t *cfg);     // Function to convert struct to uint16_t
    
int16_t as5600_getRawAngel(i2c_inst_t *i2c);
int16_t as5600_getAngel(i2c_inst_t *i2c);

bool as5600_getConfig(i2c_inst_t *i2c, as5600_config_t *cfg);
bool as5600_setConfig(i2c_inst_t *i2c, as5600_config_t cfg);

bool as5600_writeInstruction(i2c_inst_t *i2c, Register_Address addr);
uint16_t as5600_read(i2c_inst_t *i2c, int len);