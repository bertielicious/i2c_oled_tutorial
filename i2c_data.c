#include "config.h"
#include "i2c_start.h"
#include "i2c_write.h"
#include "i2c_stop.h"
void i2c_data (uchar data)
{
    i2c_start();
    i2c_write(0x78);        // OLED Data address, written to GDDRAM, ie oled screen
    i2c_write(0x40);        // 0b01000000 = 0x40 D/C = 1 (write data)
    i2c_write(data);
    i2c_stop();
}
