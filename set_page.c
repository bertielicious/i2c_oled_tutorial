#include "config.h"
#include "set_page.h"
#include "i2c_command.h"
void set_page(uchar memory_mode, uchar page_mode, uchar page_addr)
{
    i2c_command(memory_mode);    // set memory addressing mode
    i2c_command(page_mode);    // enter page addressing mode
    i2c_command(page_addr);    // set page address to page 3
}
