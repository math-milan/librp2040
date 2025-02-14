#include "hardware/i2c.h"
#include <string.h>

namespace i2c_flash{
    class at24c01c{
        public:
            at24c01c(i2c_inst_t *i2c_instance, uint8_t addr);
            ~at24c01c();

            bool writeByte(uint8_t addr, uint8_t data);
            bool writePage(uint8_t addr, uint8_t *buffer, int len);

            int16_t readCurrent(uint8_t *dst);
            int16_t readRandom(uint8_t addr, uint8_t *dst);
            int16_t readSequential(uint8_t addr, uint8_t *buffer, int len);
        private:
            bool writabel();

            int last_write;
            i2c_inst_t *i2c_inst;
            uint8_t device_addr;
            

    };
}