#include "config.h"
#include "i2c_command.h"
#include "set_page_address.h"
#include "i2c_data.h"
void clear_OLED(void)
{
    uchar row, seg;
   
    //for (row = 7; row >=0; row--)
     for (row = 0; row <8; row++)
    {
        set_page_address(row);
        for (seg = 0; seg < 128; seg++)
        {
            i2c_data(0x00);
        }
    }
}
