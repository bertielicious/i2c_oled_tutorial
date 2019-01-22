#include "config.h"
#include "i2c_command.h"
#include "i2c_data.h"
void set_page_address(uchar add)
{
    add = 0xb0|add;
    i2c_command(add);    
    
}
