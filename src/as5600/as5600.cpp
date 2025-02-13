#include "as5600.h"

namespace AS5600{
    
    AS5600::AS5600(i2c_inst_t *i2c_inst){
        this->i2c_inst = i2c_inst;
    }
    
    AS5600::~AS5600(){
    }


    int16_t AS5600::getRawAngel()
    {
        if (!writeInstruction(Register_Address::RAW_ANGLE)){
            setErrorFlag();
            return -1;
        }
        uint16_t data = read(2);
        
        return data & 0xFFF; // Returns 12 bits
    }

    int16_t AS5600::getAngel(){
        if (!writeInstruction(Register_Address::ANGLE)){
            setErrorFlag();
            return -1;
        }
        uint16_t data = read(2);
        
        return data & 0xFFF; // Returns 12 bits
    }

    config AS5600::getConfig(){
        if (!writeInstruction(Register_Address::CONF)){
            setErrorFlag();
            return (config)0xFFF;
        }
        uint16_t data = read(2);
        
        return (config)data;
    };

    bool AS5600::setConfig(config cfg){
        if (!writeInstruction(Register_Address::CONF)){
            setErrorFlag();
            return false;
        }
        writeData(cfg.toUInt16(), 2);
        return true;
    }

    void AS5600::setErrorFlag(){
        error_flag = true;
    }
    /// @brief Writes an Register Address Word to the AS5600
    bool AS5600::writeInstruction(Register_Address address)
    {
        uint8_t reg = static_cast<uint8_t>(address);
        return (i2c_write_blocking(i2c_inst, AS5600_ADDRESS, &reg, 1, true) == 1); // if the 1 byte is written return true
    }

    bool AS5600::writeData(uint16_t data, int len){
        uint8_t src[2];
        if (len == 1){
            src[0] = data & 0xFF;
        }
        else{
            src[0] = data & 0xF00;
            src[1] = data & 0xFF;
        }
        if ( i2c_write_blocking(i2c_inst, AS5600_ADDRESS, src, len, true) == len ){
            setErrorFlag();
            return false;
        }
        return true;
    }
    /// @brief Reads the specified number of bytes
    uint16_t AS5600::read(int len)
    {
        int DST_BUFFER_LEN = 5;
        uint8_t dst[DST_BUFFER_LEN];
        if (len >= DST_BUFFER_LEN){
            return false;
        }
        if (i2c_read_blocking(i2c_inst, AS5600_ADDRESS, dst, len, true) != len){
            setErrorFlag();
            return 0xFFFF;
        }
        return (dst[0] << 8) | dst[1];
    }
}