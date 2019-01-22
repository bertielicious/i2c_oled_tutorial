#include "config.h"
#include "i2c_start.h"
#include "i2c_write.h"
#include "i2c_stop.h"
void i2c_command(uchar comm)
{
    i2c_start();
    i2c_write(0x78);        // OLED Command address
    i2c_write(0x00);        // control byte
    i2c_write(comm);
    
    i2c_stop();
}
