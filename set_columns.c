#include "set_columns.h"
#include "i2c_command.h"
void set_columns (uchar column_mode, uchar lo_col_addr, uchar hi_col_addr)
{
    i2c_command(column_mode);
    i2c_command(lo_col_addr);
    i2c_command(hi_col_addr);
}
