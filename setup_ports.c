
#include <pic16f1459.h>

void setup_ports(void)
{
    ANSELA = 0x00;
    ANSELBbits.ANSB4 = 0;       // RB4 pin 13, AN10 disabled
    ANSELC = 0x00;  
}
