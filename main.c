/*
 * File:   main.c
 * Author: Phil Glazzard
 *
 * Created on 14 January 2019, 19:30
 */


#include <xc.h>
#include <stdio.h>
#include "config.h"
#include "main.h"
#include "setup_ports.h"
#include "config_osc.h"
#include "config_usart.h"
#include "putch.h"
#include "config_TMR1.h"
#include "config_TMR0.h"
#include "config_i2c.h"
#include "comdat.h"
#include "i2c_start.h"
#include "i2c_write.h"
#include "i2c_stop.h"
#include "i2c_command.h"
#include "config_OLED.h"
#include "i2c_data.h"
#include "set_page_address.h"
#include "set_page.h"
#include "set_columns.h"
#include "clear_OLED.h"


void main(void) 
{
    setup_ports();
    config_osc();
    config_usart();
    config_TMR1();
    config_TMR0();
    config_i2c();
    int i;
    /****Request data from am2302 sensor******/
    __delay_ms(2000);
    TRISAbits.TRISA4 = 0;       // RA4 is an output pin
    PORTAbits.RA4 = 1;          // Make RA4 go high momentarily
    __delay_ms(30);
    PORTAbits.RA4 = 0;          // Drive RA4 low for 1000us (start signal to sensor))
    __delay_ms(1);
    TRISAbits.TRISA4 = 1;   // release the data bus
    while(PORTAbits.RA4 == 1);  // wait allow release of bus pulse to pass
      
    while(PORTAbits.RA4 == 0);  //allow  low 80us sensor response signal to pass
    while(PORTAbits.RA4 == 1);  //allow  high 80us sensor response signal to pass
    
    for(i = 0; i <40; i++)
    {
        while(PORTAbits.RA4 == 0);  // wait if low
        while(PORTAbits.RA4 == 1)   // when the line goes high...
        {
            T1CONbits.TMR1ON = 1;   //...start TMR1 counting from zero
        }
        T1CONbits.TMR1ON = 0;       // stop TMR1 counting
        temp = TMR1H<<8 | TMR1L;    // store 16-bit tmr1 count in temp
        if(temp >=17 && temp <= 34) // measure the pulse widths to determine the serial binary data from the sensor
        {
            sensor[i] = 0;
        }
        else
        {
            sensor[i] = 1;
        }
       /* else if (temp >=60 && temp <= 80)
        {
            sensor[i] = 1;
        }*/
        temp = 0;                   // clear values ready for next decode
        TMR1H = 0x00;
        TMR1L = 0x00;
        
         __delay_ms(10);
        config_OLED();           // oled now talking to PIC via i2c protocol, but with garbage pixels illuminated on oled
       
        __delay_ms(2); 
        clear_OLED();
        __delay_ms(2); 
        //set_page_address(4);
        set_page(0x20,0x02,0xb0);       //(set mem addr mode, page addr mode, page start address)
        set_columns(0x21,0x00,0x07);    // page 0 col 0-7 (character is 8 pixels wide)
        
        for(i = 0; i < 8; i++)
        {
            i2c_data(P[i]);
        }
        
        set_columns(0x21,0x77,0x7f);     // page 0 col 119 - 127
        for(i = 0; i < 8; i++)
        {
            i2c_data(I[i]);
        }
        
        set_page(0x20,0x02,0xb7);       //(set mem command, page addr mode, page start)
        set_columns(0x21,0x00,0x07);    // page 0 col 0-7 (character is 8 pixels wide)
        
        for(i = 0; i < 8; i++)
        {
            i2c_data(H[i]);
        }
        
        set_columns(0x21,0x77,0x7f);     // page 0 col 119 - 127
        for(i = 0; i < 8; i++)
        {
            i2c_data(L[i]);
        }
    }
        
    
    
        /*Merge high and low bytes of temperature reading into variable 'centigrade_word'*/
        centigrade_low = sensor[24]*128 + sensor[25]*64 + sensor[26]*32 + sensor[27]*16 + sensor[28]*8 + sensor[29]*4 + sensor[30]*2 + sensor[31];
        centigrade_high = sensor[16]*128 + sensor[17]*64 + sensor[18]*32 + sensor[19]*16 + sensor[20]*8 + sensor[21]*4 + sensor[22]*2 + sensor[23];
        centigrade_word = centigrade_high<<8 | centigrade_low;  // merge two bytes of temp data to get 16-bit temp data
        printf("temperature = %1.1f°C\n", (float)centigrade_word/10);       // print 16-bit temperature value
        
        
        /*Merge high and low bytes of humidity reading into variable 'humidity_word'*/
        humidity_low = sensor[8]*128 + sensor[9]*64 + sensor[10]*32 + sensor[11]*16 + sensor[12]*8 + sensor[13]*4 + sensor[14]*2 + sensor[15];
        humidity_high = sensor[0]*128 + sensor[1]*64 + sensor[2]*32 + sensor[3]*16 + sensor[4]*8 + sensor[5]*4 + sensor[6]*2 + sensor[7];
        humidity_word = humidity_high<<8 | humidity_low;                    
        printf("humidity = %1.1f\%%", (float)humidity_word/10);     // escape sequence % needed to print % (%%))// print 16-bit humidity value
        printf("\n");
        printf("\n");
        //break;  
       // i2c_start();
      //  i2c_write(0x7A);            // address of OLED plus SA0 = 1(write data rather than command)
        //ack should now be received
       
        while(1);
    
    
}
