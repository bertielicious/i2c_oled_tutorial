#include "comdat.h"
#include "config.h"
#include "i2c_start.h"
#include "i2c_write.h"
#include "i2c_stop.h"
void comdat(uchar OLED_addr, uchar ctrl_byte_hi, uchar data_byte_hi, uchar ctrl_byte_lo, uchar data_byte_lo)
{
    i2c_start();
    i2c_write(OLED_addr);       //0x78
    i2c_write(ctrl_byte_hi);    //0x00
    i2c_write(data_byte_hi);    //0x22
    i2c_write(ctrl_byte_lo);    //0x40
    i2c_write(data_byte_lo);    // P[i]]
    i2c_stop();
}
